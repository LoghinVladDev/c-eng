//
// Created by loghin on 9/5/20.
//

#include <src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/command/VCommandBuffer.h>
#include "VBuffer.h"

inline static void populateVertexBufferCreateInfo (
        VulkanBufferCreateInfo    * createInfo,
        VulkanDeviceSize            size,
        VulkanBufferUsageFlags      usageFlags,
        VulkanSharingMode           sharingMode
) noexcept {
    if ( createInfo == nullptr )
        return;

    * createInfo = VulkanBufferCreateInfo {
            .sType                  = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
            .pNext                  = nullptr,
            .flags                  = VULKAN_NULL_FLAGS,
            .size                   = size,
            .usage                  = usageFlags,
            .sharingMode            = sharingMode,
            .queueFamilyIndexCount  = 0U,
            .pQueueFamilyIndices    = nullptr
    };
}

inline static void populateVertexBufferMemoryAllocateInfo (
        VulkanMemoryAllocateInfo *  allocateInfo,
        VulkanDeviceSize            allocationSize,
        uint32                      memoryTypeIndex
) noexcept {
    if ( allocateInfo == nullptr )
        return;

    * allocateInfo = VulkanMemoryAllocateInfo {
            .sType              = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
            .pNext              = nullptr,
            .allocationSize     = allocationSize,
            .memoryTypeIndex    = memoryTypeIndex
    };
}

inline static uint32 findMemoryType ( uint32 typeFilter, VulkanMemoryPropertyFlags properties, const engine::VLogicalDevice * pLogicalDevice ) noexcept (false) {
    auto memoryProperties = pLogicalDevice->getBasePhysicalDevice()->getMemoryProperties();

    for ( uint32 memoryTypeIndex = 0; memoryTypeIndex < memoryProperties.memoryTypeCount; memoryTypeIndex++ ) {
        if (
                ( typeFilter & ( 1U << memoryTypeIndex ) ) &&
                ( ( memoryProperties.memoryTypes [ memoryTypeIndex ].propertyFlags & properties ) == properties )
                ) {
            return memoryTypeIndex;
        }
    }

    throw std::runtime_error ( "failed to find suitable memory type" );
}

VulkanResult engine::VBuffer::setup(
    const VLogicalDevice & device,
    std::size_t dataSize,
    VulkanBufferUsageFlags usageFlags,
    VulkanSharingMode sharingMode
) noexcept {
    this->_pLogicalDevice   = & device;
    this->_memorySize       = dataSize;
    this->_bufferUsageFlags = usageFlags;
    this->_sharingMode      = sharingMode;

    VulkanBufferCreateInfo createInfo { };

    populateVertexBufferCreateInfo(
        & createInfo,
        static_cast < VulkanDeviceSize > ( dataSize ),
        usageFlags,
        sharingMode
    );

    return vkCreateBuffer( this->_pLogicalDevice->data(), & createInfo, nullptr, & this->_handle );
}

void engine::VBuffer::cleanup() noexcept {
    vkDestroyBuffer( this->_pLogicalDevice->data(), this->_handle, nullptr );
}

VulkanResult engine::VBuffer::allocateMemory(
    VulkanMemoryPropertyFlags memoryPropertyFlags
) noexcept {
    VulkanMemoryRequirements memoryRequirements;
    vkGetBufferMemoryRequirements( this->_pLogicalDevice->data(), this->_handle, & memoryRequirements );

    VulkanMemoryAllocateInfo allocateInfo { };

    try {
        populateVertexBufferMemoryAllocateInfo(
            & allocateInfo,
            memoryRequirements.size,
            findMemoryType(
                memoryRequirements.memoryTypeBits,
                memoryPropertyFlags,
                this->_pLogicalDevice
            )
        );
    } catch ( std::runtime_error const & exception ) {
        return VulkanResult::VK_ERROR_INITIALIZATION_FAILED;
    }

    VulkanResult allocateResult = vkAllocateMemory(
        this->_pLogicalDevice->data(),
        & allocateInfo,
        nullptr,
        & this->_memoryHandle
    );

    if (allocateResult != VulkanResult::VK_SUCCESS )
        return allocateResult;

    return vkBindBufferMemory(
        this->_pLogicalDevice->data(),
        this->_handle,
        this->_memoryHandle,
        0ULL
    );
}

VulkanResult engine::VBuffer::copyOntoBuffer(const void * pData, std::size_t dataSize) noexcept {
    void * pBufferData;

    VulkanResult mapMemoryResult = vkMapMemory(
            this->_pLogicalDevice->data(),
            this->_memoryHandle,
            0ULL,
            this->_memorySize,
            0,
            & pBufferData
    );
    if ( mapMemoryResult != VulkanResult::VK_SUCCESS )
        return mapMemoryResult;

    memcpy ( pBufferData, pData, dataSize );

    vkUnmapMemory(
            this->_pLogicalDevice->data(),
            this->_memoryHandle
    );

    return VulkanResult::VK_SUCCESS;
}

void engine::VBuffer::free() noexcept {
    vkFreeMemory(
        this->_pLogicalDevice->data(),
        this->_memoryHandle,
        nullptr
    );
}

VulkanResult engine::VBuffer::copyFrom(
    const VBuffer & sourceBuffer,
    const VCommandPool & commandPool,
    VulkanDeviceSize size
) noexcept {
#ifndef NDEBUG
    if ( commandPool.isOptimizedForTransfers() && this->_sharingMode != VulkanSharingMode::VK_SHARING_MODE_CONCURRENT )
        std::cerr << "Transfer Buffer Pool Available, Resources not Concurrent!\n";
    else if ( commandPool.isOptimizedForTransfers() && sourceBuffer.getBufferSharingMode() != VulkanSharingMode::VK_SHARING_MODE_CONCURRENT )
        std::cerr << "Transfer Buffer Pool Available, given Source Buffer Resources not Concurrent!\n";
    else if ( ! commandPool.isOptimizedForTransfers() && sourceBuffer.getBufferSharingMode() == VulkanSharingMode::VK_SHARING_MODE_CONCURRENT && this->_sharingMode == VulkanSharingMode::VK_SHARING_MODE_CONCURRENT )
        std::cerr << "Both Buffers use Concurrent Resources, no Buffer with Transfer Optimisation Given!\n";
#endif

    bool transferThroughTransferQueue = commandPool.isOptimizedForTransfers() && this->_sharingMode == VulkanSharingMode::VK_SHARING_MODE_CONCURRENT && sourceBuffer._sharingMode == VulkanSharingMode::VK_SHARING_MODE_CONCURRENT;

    VCommandBufferCollection copyCommandBuffers;
    VulkanResult allocateCommandBuffersResult = copyCommandBuffers.allocate( commandPool, 1U );

    if ( allocateCommandBuffersResult != VulkanResult::VK_SUCCESS )
        return allocateCommandBuffersResult;

    const VQueue * pQueue = ( transferThroughTransferQueue ? this->_pLogicalDevice->getFirstTransferQueuePtr() : this->_pLogicalDevice->getFirstGraphicsQueuePtr() );

    if ( pQueue == nullptr )
        return VulkanResult::VK_ERROR_FEATURE_NOT_PRESENT;

    VulkanDeviceSize maxCopyMemory = std::min ( this->_memorySize, sourceBuffer._memorySize );

    VulkanResult startRecordResult = copyCommandBuffers.startRecord(
        * this,
        sourceBuffer,
        ( ( size == 0ULL ) ? ( maxCopyMemory ) : ( std::min ( maxCopyMemory, size ) ) )
    );

    if ( startRecordResult != VulkanResult::VK_SUCCESS )
        return startRecordResult;

    VulkanResult submitResult = copyCommandBuffers.submit( pQueue );

    if ( submitResult != VulkanResult::VK_SUCCESS )
        return submitResult;

    VulkanResult queueWaitResult = vkQueueWaitIdle( pQueue->data() );

    if ( queueWaitResult != VulkanResult::VK_SUCCESS )
        return queueWaitResult;

    copyCommandBuffers.free();

    return VulkanResult::VK_SUCCESS;
}
//
// Created by loghin on 9/5/20.
//
#include "VBuffer.h"
#include <src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/command/VCommandBuffer.h>
#include <iostream>

inline static void populateBufferCreateInfo (
    VulkanBufferCreateInfo    * createInfo,
    VulkanDeviceSize            size,
    VulkanBufferUsageFlags      usageFlags,
    VulkanSharingMode           sharingMode,
    uint32                      queueFamilyIndexCount,
    const uint32              * pQueueFamilyIndices
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
        .queueFamilyIndexCount  = queueFamilyIndexCount,
        .pQueueFamilyIndices    = pQueueFamilyIndices
    };
}

void populateMemoryAllocateInfo (
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

uint32 findMemoryType ( uint32 typeFilter, VulkanMemoryPropertyFlags properties, const engine::VLogicalDevice * pLogicalDevice ) noexcept (false) {
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
    VulkanSharingMode sharingMode,
    const uint32 * pQueueFamilyIndices,
    uint32 queueFamilyIndexCount
) noexcept {
    if ( sharingMode == VulkanSharingMode::VK_SHARING_MODE_CONCURRENT && (
            queueFamilyIndexCount == 0 ||
            pQueueFamilyIndices == nullptr
        )
    )
        return VulkanResult::VK_ERROR_INITIALIZATION_FAILED;

    this->_pLogicalDevice   = & device;
    this->_memorySize       = dataSize;
    this->_bufferUsageFlags = usageFlags;
    this->_sharingMode      = sharingMode;

    VulkanBufferCreateInfo createInfo { };

    populateBufferCreateInfo(
            &createInfo,
            static_cast < VulkanDeviceSize > ( dataSize ),
            usageFlags,
            sharingMode,
            queueFamilyIndexCount,
            pQueueFamilyIndices
    );

    return vkCreateBuffer( this->_pLogicalDevice->data(), & createInfo, nullptr, & this->_handle );
}

void engine::VBuffer::cleanup() noexcept {
    vkDestroyBuffer( this->_pLogicalDevice->data(), this->_handle, nullptr );
}

VulkanResult engine::VBuffer::allocateMemory(
    VulkanMemoryPropertyFlags memoryPropertyFlags
) noexcept {
    if ( this->_memoryAllocated )
        return VulkanResult::VK_SUCCESS;
    this->_memoryAllocated = true;

    this->_memoryPropertyFlags = memoryPropertyFlags;

    VulkanMemoryRequirements memoryRequirements;
    vkGetBufferMemoryRequirements( this->_pLogicalDevice->data(), this->_handle, & memoryRequirements );

    VulkanMemoryAllocateInfo allocateInfo { };

    try {
        populateMemoryAllocateInfo(
                &allocateInfo,
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

VulkanResult engine::VBuffer::load(const void * pData, std::size_t dataSize) noexcept {
    if ( ( this->_memoryPropertyFlags & (VulkanMemoryPropertyFlags) VBuffer::MEMORY_CPU_WRITEABLE ) == 0 )
        return VulkanResult::VK_ERROR_MEMORY_MAP_FAILED;

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

    std::memcpy ( pBufferData, pData, dataSize );

    vkUnmapMemory(
            this->_pLogicalDevice->data(),
            this->_memoryHandle
    );

    return VulkanResult::VK_SUCCESS;
}

void engine::VBuffer::free() noexcept {
    if ( ! this->_memoryAllocated )
        return;

    vkFreeMemory(
        this->_pLogicalDevice->data(),
        this->_memoryHandle,
        nullptr
    );

    this->_memoryAllocated = false;
}

VulkanResult engine::VBuffer::copyFrom(
    const VBuffer & sourceBuffer,
    const VCommandPool & commandPool,
    VulkanDeviceSize size
) noexcept {
    if ( ! ( this->isDestinationBuffer() && sourceBuffer.isSourceBuffer() ) ) {
        return VulkanResult::VK_ERROR_NOT_PERMITTED_EXT;
    }

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

    this->setElementCount( sourceBuffer.getElementCount() );

    return VulkanResult::VK_SUCCESS;
}
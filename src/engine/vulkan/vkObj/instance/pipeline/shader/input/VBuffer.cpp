//
// Created by loghin on 9/5/20.
//
#include "VBuffer.hpp"
#include <VCommandBuffer.hpp>
#include <iostream>

/**
 * @brief Internal Function populates a Buffer Create Info Structure
 *
 * @param createInfo : VulkanBufferCreateInfo ptr = Address to the Structure to populate
 * @param size : VulkanDeviceSize = Size of the buffer
 * @param usageFlags : VulkanBufferUsageFlags = usage of buffer ( vertex / index / ... )
 * @param sharingMode : VulkanSharingMode = memory sharing mode ( exclusive / concurrent )
 * @param queueFamilyIndexCount : uint32 = number of queue families that will have access to buffer ( in case of concurrency )
 * @param pQueueFamilyIndices: uint32 cptr = address to one / an array of queue family indices
 *
 * @static
 *
 * @exceptsafe
 */
inline static auto populateBufferCreateInfo (
    VulkanBufferCreateInfo    * createInfo,
    VulkanDeviceSize            size,
    VulkanBufferUsageFlags      usageFlags,
    VulkanSharingMode           sharingMode,
    uint32                      queueFamilyIndexCount,
    uint32              const * pQueueFamilyIndices
) noexcept -> void {
    if ( createInfo == nullptr )
        return;

    * createInfo = VulkanBufferCreateInfo {
        .sType                  = VulkanStructureType::VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .pNext                  = nullptr,
        .flags                  = VULKAN_NULL_FLAGS,
        .size                   = size,
        .usage                  = usageFlags,
        .sharingMode            = sharingMode,
        .queueFamilyIndexCount  = queueFamilyIndexCount,
        .pQueueFamilyIndices    = pQueueFamilyIndices
    };
}

/**
 * @brief Function used to populate Memory Allocate Info
 *
 * @param allocateInfo : VulkanMemoryAllocateInfo ptr = address to the Structure to populate
 * @param allocationSize : VulkanDeviceSize = Number of bytes to allocate
 * @param memoryTypeIndex : uint32 = index of memory type ( in arr. of memory types on gpu )
 *
 * @exceptsafe
 */
auto populateMemoryAllocateInfo (
        VulkanMemoryAllocateInfo *  allocateInfo,
        VulkanDeviceSize            allocationSize,
        uint32                      memoryTypeIndex
) noexcept -> void {
    if ( allocateInfo == nullptr )
        return;

    * allocateInfo = VulkanMemoryAllocateInfo {
            .sType              = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
            .pNext              = nullptr,
            .allocationSize     = allocationSize,
            .memoryTypeIndex    = memoryTypeIndex
    };
}

/**
 * @brief Function used to find memory type index of on-gpu memory by what is required
 *
 * @param typeFilter : uint32 = type of memory to request
 * @param properties : VulkanMemoryPropertyFlags = properties of requested memory type
 * @param pLogicalDevice : engine::VLogicalDevice cptr = Address to Constant Logical Device to get memory from
 *
 * @throws std::runtime_error if
 *      Requested memory type is unavailable
 *
 * @return uint32 = index of requested memory in the memory types array on GPU
 */
auto findMemoryType (
        uint32 typeFilter,
        VulkanMemoryPropertyFlags properties,
        engine::VLogicalDevice const * pLogicalDevice
) noexcept (false) -> uint32 {
    auto memoryProperties = pLogicalDevice->getBasePhysicalDevice()->getMemoryProperties(); /// acquire memory properties

    for ( uint32 memoryTypeIndex = 0; memoryTypeIndex < memoryProperties.memoryTypeCount; memoryTypeIndex++ ) /// go through all indices
        if (
                ( typeFilter & ( 1U << memoryTypeIndex ) ) && /// is in our index filter
                ( ( memoryProperties.memoryTypes [ memoryTypeIndex ].propertyFlags & properties ) == properties ) /// memory at index has required properties
        )
            return memoryTypeIndex;

    throw std::runtime_error ( "failed to find suitable memory type" ); /// throw if not found
}

auto engine::VBuffer::setup(
    VLogicalDevice          const & device,
    std::size_t                     dataSize,
    VulkanBufferUsageFlags          usageFlags,
    VulkanSharingMode               sharingMode,
    uint32                  const * pQueueFamilyIndices,
    uint32                          queueFamilyIndexCount
) noexcept -> VulkanResult {
    if (
            sharingMode == VulkanSharingMode::VK_SHARING_MODE_CONCURRENT && ( /// concurrency requested
                queueFamilyIndexCount == 0 ||  /// and no queue families to share buffer are given
                pQueueFamilyIndices == nullptr
        )
    )
        return VulkanResult::VK_ERROR_INITIALIZATION_FAILED; /// error

    this->_pLogicalDevice   = & device;
    this->_memorySize       = dataSize;
    this->_bufferUsageFlags = usageFlags;
    this->_sharingMode      = sharingMode;

    VulkanBufferCreateInfo createInfo { };

    populateBufferCreateInfo(
            & createInfo,  /// populate this structure
            static_cast < VulkanDeviceSize > ( dataSize ), /// with this size
            usageFlags, /// usage
            sharingMode, /// sharing
            queueFamilyIndexCount,
            pQueueFamilyIndices
    );

    /// return result of buffer creation
    return vkCreateBuffer( this->_pLogicalDevice->data(), & createInfo, nullptr, & this->_handle );
}

auto engine::VBuffer::cleanup() noexcept -> void {
    /// cleanup buffer
    vkDestroyBuffer( this->_pLogicalDevice->data(), this->_handle, nullptr );
}

auto engine::VBuffer::allocateMemory(
    VulkanMemoryPropertyFlags memoryPropertyFlags
) noexcept -> VulkanResult {
    if ( this->_memoryAllocated ) /// if memory already allocated, return
        return VulkanResult::VK_SUCCESS;
    this->_memoryAllocated = true;

    this->_memoryPropertyFlags = memoryPropertyFlags; /// save memory properties

    VulkanMemoryRequirements memoryRequirements; /// acquire memory requirements for buffer
    vkGetBufferMemoryRequirements( this->_pLogicalDevice->data(), this->_handle, & memoryRequirements );

    VulkanMemoryAllocateInfo allocateInfo { };

    try {
        populateMemoryAllocateInfo(
                & allocateInfo, /// populate  this structure
                memoryRequirements.size, /// size required
                findMemoryType( /// memory type required
                        memoryRequirements.memoryTypeBits,
                        memoryPropertyFlags, /// flags
                        this->_pLogicalDevice /// from this device
                )
        );
    } catch ( std::runtime_error const & ignored ) { /// if memory type not found, catch
#if defined(_MSC_VER)
        (void) ignored;
#endif
        return VulkanResult::VK_ERROR_INITIALIZATION_FAILED;
    }

    VulkanResult allocateResult = vkAllocateMemory(
        this->_pLogicalDevice->data(), /// allocate from this device's memory
        & allocateInfo, /// with parameters
        nullptr,
        & this->_memoryHandle /// save in this memory handle
    );

    if (allocateResult != VulkanResult::VK_SUCCESS )
        return allocateResult;

    return vkBindBufferMemory( /// bind memory
        this->_pLogicalDevice->data(), /// from device
        this->_handle, /// to this handle
        this->_memoryHandle, /// from memory handle
        0ULL /// offset to bind from
    );
}

auto engine::VBuffer::load(const void * pData, std::size_t dataSize) noexcept -> VulkanResult {
    /// if CPU cannot write in this buffer, return error
    if ( ( this->_memoryPropertyFlags & (VulkanMemoryPropertyFlags) VBuffer::MEMORY_CPU_WRITEABLE ) == 0 )
        return VulkanResult::VK_ERROR_MEMORY_MAP_FAILED;

    void * pBufferData; /// place to load the mapped address

    VulkanResult mapMemoryResult = vkMapMemory(
            this->_pLogicalDevice->data(), /// from device
            this->_memoryHandle, /// from this memory handle
            0ULL, /// offset to load from
            this->_memorySize, /// size to load
            VULKAN_NULL_FLAGS, /// mapping flags none
            & pBufferData /// address of address to load to
    );
    if ( mapMemoryResult != VulkanResult::VK_SUCCESS )
        return mapMemoryResult;

    std::memcpy ( pBufferData, pData, dataSize ); /// copy data at address

    vkUnmapMemory( /// unmap and flush
            this->_pLogicalDevice->data(),
            this->_memoryHandle /// this handle
    );

    return VulkanResult::VK_SUCCESS;
}

auto engine::VBuffer::free() noexcept -> void {
    if ( ! this->_memoryAllocated ) /// if no memory previously allocated, do not free. Also avoids double free
        return;

    vkFreeMemory(
        this->_pLogicalDevice->data(),
        this->_memoryHandle,
        nullptr
    );

    this->_memoryAllocated = false;
}

auto engine::VBuffer::copyFrom(
    VBuffer             const & sourceBuffer,
    VCommandPool        const & commandPool,
    VulkanDeviceSize            size,
    uint32                      destinationOffset,
    uint32                      sourceOffset
) noexcept -> VulkanResult {
    if ( ! ( this->isDestinationBuffer() && sourceBuffer.isSourceBuffer() ) ) { /// if this is not destination and given buffer is not source
        return VulkanResult::VK_ERROR_NOT_PERMITTED_EXT; /// error
    }

#ifndef NDEBUG
    /// debug checks
    if (
            commandPool.isOptimizedForTransfers() && /// if this pool is optimised for transfers
            this->_sharingMode != VulkanSharingMode::VK_SHARING_MODE_CONCURRENT /// this but buffer does not permit multiple queue types to operate on this ( by default, graphical is used )
    )
        std::cerr << "Transfer Buffer Pool Available, Resources not Concurrent!\n";
    else if (
            commandPool.isOptimizedForTransfers() && /// same as above, but for given buffer
            sourceBuffer.getBufferSharingMode() != VulkanSharingMode::VK_SHARING_MODE_CONCURRENT
    )
        std::cerr << "Transfer Buffer Pool Available, given Source Buffer Resources not Concurrent!\n";
    else if (
            ! commandPool.isOptimizedForTransfers() && //// if command pool not optimised for transfers
            sourceBuffer.getBufferSharingMode() == VulkanSharingMode::VK_SHARING_MODE_CONCURRENT && /// but this is concurrent buffer
            this->_sharingMode == VulkanSharingMode::VK_SHARING_MODE_CONCURRENT /// and source is concurrent
    )
        std::cerr << "Both Buffers use Concurrent Resources, no Buffer with Transfer Optimisation Given!\n";
#endif

    bool transferThroughTransferQueue =                                                 /// use transfer queue if
            commandPool.isOptimizedForTransfers() &&                                    /// pool is transfer optimised and
            this->_sharingMode == VulkanSharingMode::VK_SHARING_MODE_CONCURRENT &&      /// this buffer's memory is concurrently shared and
            sourceBuffer._sharingMode == VulkanSharingMode::VK_SHARING_MODE_CONCURRENT; /// given buffer's memory is concurrently shared

    VCommandBufferCollection copyCommandBuffers;  /// create pool of one copy buffer
    VulkanResult allocateCommandBuffersResult = copyCommandBuffers.allocate( commandPool, 1U ); /// allocate copy command buffer

    if ( allocateCommandBuffersResult != VulkanResult::VK_SUCCESS )
        return allocateCommandBuffersResult;

    const VQueue * pQueue =
            transferThroughTransferQueue ?                      /// if using transfer optimised command pool
            this->_pLogicalDevice->getFirstTransferQueuePtr() : /// pass command to transfer queue
            this->_pLogicalDevice->getFirstGraphicsQueuePtr() ; /// else pass to graphics

    if ( pQueue == nullptr )
        return VulkanResult::VK_ERROR_FEATURE_NOT_PRESENT;

    /// max copy memory = min between this size - this offset ( remaining size for this ) and given size - given offset ( remaining size for given )
    VulkanDeviceSize maxCopyMemory = std::min ( this->_memorySize - destinationOffset, sourceBuffer._memorySize - sourceOffset );

    VulkanResult startRecordResult = copyCommandBuffers.startRecord ( /// record a copy command
        * this, /// in this buffer
        sourceBuffer, /// from this buffer
        static_cast<uint32>( ( ( size == 0ULL ) ? ( maxCopyMemory ) : ( std::min ( maxCopyMemory, size ) ) ) ),  /// if no size requested, copy all, else copy minimum between requested size and max copy size
        destinationOffset, /// offset from dest
        sourceOffset /// offset from start
    );

    if ( startRecordResult != VulkanResult::VK_SUCCESS ) {
        copyCommandBuffers.free();
        return startRecordResult;
    }

    VulkanResult submitResult = copyCommandBuffers.submit( pQueue ); /// submit recorded command to queue

    if ( submitResult != VulkanResult::VK_SUCCESS ) {
        copyCommandBuffers.free();
        return submitResult;
    }

    VulkanResult queueWaitResult = vkQueueWaitIdle( pQueue->data() ); /// wait for command finish

    if ( queueWaitResult != VulkanResult::VK_SUCCESS ) {
        copyCommandBuffers.free();
        return queueWaitResult;
    }

    copyCommandBuffers.free();

    this->setElementCount( sourceBuffer.getElementCount() ); /// set element count to source buffer element count if success

    return VulkanResult::VK_SUCCESS;
}
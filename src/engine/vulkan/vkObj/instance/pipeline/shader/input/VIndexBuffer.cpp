//
// Created by vladl on 9/5/2020.
//

#include "VIndexBuffer.hpp"

VulkanResult engine::VIndexBuffer16::flush() noexcept {
    return this->copyFrom(
        this->_stagingBuffer,
        * this->_pCommandPool,
        this->_stagingBuffer.size()
    );
}

VulkanResult engine::VIndexBuffer32::flush() noexcept {
    return this->copyFrom(
        this->_stagingBuffer,
        * this->_pCommandPool,
        this->_stagingBuffer.size()
    );
}

void engine::VIndexBuffer16::free() noexcept {
    this->_stagingBuffer.free();
    engine::VIndexBufferBase::free();
}

void engine::VIndexBuffer16::cleanup() noexcept {
    this->_stagingBuffer.cleanup();
    engine::VIndexBufferBase::cleanup();
}

void engine::VIndexBuffer32::free() noexcept {
    this->_stagingBuffer.free();
    engine::VIndexBufferBase::free();
}

void engine::VIndexBuffer32::cleanup() noexcept {
    this->_stagingBuffer.cleanup();
    VBuffer::cleanup();
}

VulkanResult engine::VIndexBuffer16::allocateMemory() noexcept {
    VulkanResult allocateResult = VBuffer::allocateMemory( VBuffer::MEMORY_GPU_BUFFER_FLAGS );
    if ( allocateResult != VulkanResult::VK_SUCCESS )
        return allocateResult;

    allocateResult = this->_stagingBuffer.allocateMemory();
    if ( allocateResult != VulkanResult::VK_SUCCESS )
        return allocateResult;

    return this->flush();
}

VulkanResult engine::VIndexBuffer32::allocateMemory() noexcept {
    VulkanResult allocateResult = VBuffer::allocateMemory( VBuffer::MEMORY_GPU_BUFFER_FLAGS );
    if ( allocateResult != VulkanResult::VK_SUCCESS )
        return allocateResult;

    allocateResult = this->_stagingBuffer.allocateMemory();
    if ( allocateResult != VulkanResult::VK_SUCCESS )
        return allocateResult;

    return this->flush();
}

void engine::VIndexBufferBase::free() noexcept {
    VBuffer::free();
}

void engine::VIndexBufferBase::cleanup() noexcept {
    VBuffer::cleanup();
}

VulkanResult engine::VIndexBuffer16::setup(
    const engine::VLogicalDevice    & device,
    const std::vector<uint16>       & indices,
    const engine::VCommandPool      * pCommandPool,
    const uint32                    * pQueueFamilyIndices,
    uint32                            queueFamilyIndexCount,
    bool                              forceMemoryExclusivity
) noexcept {
    VulkanSharingMode sharingMode   = VBuffer::getOptimalSharingMode( forceMemoryExclusivity, queueFamilyIndexCount, device );
    this->_pCommandPool             = pCommandPool;

    VulkanResult setupStagingBufferResult = this->_stagingBuffer.setup(
        device,
        indices,
        sharingMode,
        pQueueFamilyIndices,
        queueFamilyIndexCount
    );

    if ( setupStagingBufferResult != VulkanResult::VK_SUCCESS )
        return setupStagingBufferResult;

    this->setElementCount( this->_stagingBuffer.getElementCount() );
    return VBuffer::setup(
        device,
        static_cast < std::size_t > ( this->_stagingBuffer.size() ),
        VBuffer::INDEX_BUFFER_GPU_LOCAL,
        sharingMode,
        pQueueFamilyIndices,
        queueFamilyIndexCount
    );
}

VulkanResult engine::VIndexBuffer16::setup(
    const engine::VLogicalDevice    & device,
    uint32                            vertexCount,
    const engine::VCommandPool      * pCommandPool,
    const uint32                    * pQueueFamilyIndices,
    uint32                            queueFamilyIndexCount,
    bool                              forceMemoryExclusivity
) noexcept {

    VulkanSharingMode sharingMode   = VBuffer::getOptimalSharingMode( forceMemoryExclusivity, queueFamilyIndexCount, device );
    this->_pCommandPool             = pCommandPool;

    VulkanResult setupStagingBufferResult = this->_stagingBuffer.setup(
            device,
            vertexCount,
            sharingMode,
            pQueueFamilyIndices,
            queueFamilyIndexCount
    );

    if ( setupStagingBufferResult != VulkanResult::VK_SUCCESS )
        return setupStagingBufferResult;

    this->setElementCount( this->_stagingBuffer.getElementCount() );
    return VBuffer::setup(
            device,
            static_cast < std::size_t > ( this->_stagingBuffer.size() ),
            VBuffer::INDEX_BUFFER_GPU_LOCAL,
            sharingMode,
            pQueueFamilyIndices,
            queueFamilyIndexCount
    );
}

VulkanResult engine::VIndexBuffer32::setup(
    const engine::VLogicalDevice    & device,
    const std::vector<uint32>       & indices,
    const engine::VCommandPool      * pCommandPool,
    const uint32                    * pQueueFamilyIndices,
    uint32                            queueFamilyIndexCount,
    bool                              forceMemoryExclusivity
) noexcept {
    VulkanSharingMode sharingMode   = VBuffer::getOptimalSharingMode( forceMemoryExclusivity, queueFamilyIndexCount, device );
    this->_pCommandPool             = pCommandPool;

    VulkanResult setupStagingBufferResult = this->_stagingBuffer.setup(
        device,
        indices,
        sharingMode,
        pQueueFamilyIndices,
        queueFamilyIndexCount
    );

    if ( setupStagingBufferResult != VulkanResult::VK_SUCCESS )
        return setupStagingBufferResult;

    this->setElementCount( this->_stagingBuffer.getElementCount() );
    return VBuffer::setup(
        device,
        static_cast < std::size_t > ( this->_stagingBuffer.size() ),
        VBuffer::INDEX_BUFFER_GPU_LOCAL,
        sharingMode,
        pQueueFamilyIndices,
        queueFamilyIndexCount
    );
}

VulkanResult engine::VIndexBuffer32::setup(
    const engine::VLogicalDevice    & device,
    uint32                            vertexCount,
    const engine::VCommandPool      * pCommandPool,
    const uint32                    * pQueueFamilyIndices,
    uint32                            queueFamilyIndexCount,
    bool                              forceMemoryExclusivity
) noexcept {

    VulkanSharingMode sharingMode   = VBuffer::getOptimalSharingMode( forceMemoryExclusivity, queueFamilyIndexCount, device );
    this->_pCommandPool             = pCommandPool;

    VulkanResult setupStagingBufferResult = this->_stagingBuffer.setup(
        device,
        vertexCount,
        sharingMode,
        pQueueFamilyIndices,
        queueFamilyIndexCount
    );

    if ( setupStagingBufferResult != VulkanResult::VK_SUCCESS )
        return setupStagingBufferResult;

    this->setElementCount( this->_stagingBuffer.getElementCount() );
    return VBuffer::setup(
        device,
        static_cast < std::size_t > ( this->_stagingBuffer.size() ),
        VBuffer::INDEX_BUFFER_GPU_LOCAL,
        sharingMode,
        pQueueFamilyIndices,
        queueFamilyIndexCount
    );
}

VulkanResult engine::VIndexBuffer16::load(const std::vector<uint16> & indices) noexcept {
    auto copyElementCount = std::min (
        static_cast < uint32 > ( this->_stagingBuffer.getElementCount() ),
        static_cast < uint32 > ( indices.size() )
    );

    for ( uint32 it = 0; it < copyElementCount; it++ )
        this->_stagingBuffer._data [it] = indices [it];

    this->_stagingBuffer.reload();
    this->_stagingBuffer.setElementCount( copyElementCount );
    this->setElementCount( copyElementCount );

    return this->flush();
}


VulkanResult engine::VIndexBuffer32::load(const std::vector<uint32> & indices) noexcept {
    auto copyElementCount = std::min (
        static_cast < uint32 > ( this->_stagingBuffer.getElementCount() ),
        static_cast < uint32 > ( indices.size() )
    );

    for ( uint32 it = 0; it < copyElementCount; it++ )
        this->_stagingBuffer._data [it] = indices [it];

    this->_stagingBuffer.reload();
    this->_stagingBuffer.setElementCount( copyElementCount );
    this->setElementCount( copyElementCount );

    return this->flush();
}


//
// Created by vladl on 9/5/2020.
//

#include "VIndexBuffer.hpp"

auto engine::VIndexBuffer16::flush() noexcept -> VulkanResult {
    /// flushing is just copying from CPU buffer to GPU buffer
    return this->copyFrom(
        this->_stagingBuffer,
        * this->_pCommandPool,
        this->_stagingBuffer.size()
    );
}

auto engine::VIndexBuffer32::flush() noexcept -> VulkanResult {
    /// flushing is just copying from CPU buffer to GPU buffer
    return this->copyFrom(
        this->_stagingBuffer,
        * this->_pCommandPool,
        this->_stagingBuffer.size()
    );
}

auto engine::VIndexBuffer16::free() noexcept -> void {
    this->_stagingBuffer.free();
    engine::VIndexBufferBase::free();
}

auto engine::VIndexBuffer16::clear() noexcept -> void {
    this->_stagingBuffer.clear();
    engine::VIndexBufferBase::clear();
}

auto engine::VIndexBuffer32::free() noexcept -> void {
    this->_stagingBuffer.free();
    engine::VIndexBufferBase::free();
}

auto engine::VIndexBuffer32::clear() noexcept -> void {
    this->_stagingBuffer.clear();
    engine::VIndexBufferBase::clear();
//    VBuffer::cleanup();
}

auto engine::VIndexBuffer16::allocateMemory() noexcept -> VulkanResult {
    /// allocate this object as GPU local memory
    VulkanResult allocateResult = VBuffer::allocateMemory( VBuffer::MEMORY_GPU_BUFFER_FLAGS );
    if ( allocateResult != VulkanResult::VK_SUCCESS )
        return allocateResult;

    /// allocate staging CPU buffer
    allocateResult = this->_stagingBuffer.allocateMemory();
    if ( allocateResult != VulkanResult::VK_SUCCESS )
        return allocateResult;

    /// flush
    return this->flush();
}

auto engine::VIndexBuffer32::allocateMemory() noexcept -> VulkanResult {
    /// allocate this object as GPU memory
    VulkanResult allocateResult = VBuffer::allocateMemory( VBuffer::MEMORY_GPU_BUFFER_FLAGS );
    if ( allocateResult != VulkanResult::VK_SUCCESS )
        return allocateResult;

    /// allocate staging CPU buffer
    allocateResult = this->_stagingBuffer.allocateMemory();
    if ( allocateResult != VulkanResult::VK_SUCCESS )
        return allocateResult;

    /// flush
    return this->flush();
}

auto engine::VIndexBufferBase::free() noexcept -> void {
    VBuffer::free();
}

auto engine::VIndexBufferBase::clear() noexcept -> void {
    VBuffer::clear();
}

auto engine::VIndexBuffer16::setup(
    engine::VLogicalDevice    const & device,
    std::vector<uint16>       const & indices,
    engine::VCommandPool      const * pCommandPool,
    uint32                    const * pQueueFamilyIndices,
    uint32                            queueFamilyIndexCount,
    bool                              forceMemoryExclusivity
) noexcept -> VulkanResult {
    VulkanSharingMode sharingMode   = VBuffer::getOptimalSharingMode( forceMemoryExclusivity, queueFamilyIndexCount, device );
    this->_pCommandPool             = pCommandPool;

    /// setup CPU staging buffer
    VulkanResult setupStagingBufferResult = this->_stagingBuffer.setup(
        device,
        indices,
        sharingMode,
        pQueueFamilyIndices,
        queueFamilyIndexCount
    );

    if ( setupStagingBufferResult != VulkanResult::VK_SUCCESS )
        return setupStagingBufferResult;

    /// set element count
    this->setElementCount( this->_stagingBuffer.getElementCount() );
    /// setup this buffer on GPU
    return VBuffer::setup(
        device,
        static_cast < std::size_t > ( this->_stagingBuffer.size() ), /// no. of elements that staging buffer has
        VBuffer::INDEX_BUFFER_GPU_LOCAL,
        sharingMode,
        pQueueFamilyIndices,
        queueFamilyIndexCount
    );
}

auto engine::VIndexBuffer16::setup(
    engine::VLogicalDevice    const & device,
    uint32                            indexCount,
    engine::VCommandPool      const * pCommandPool,
    uint32                    const * pQueueFamilyIndices,
    uint32                            queueFamilyIndexCount,
    bool                              forceMemoryExclusivity
) noexcept -> VulkanResult {

    VulkanSharingMode sharingMode   = VBuffer::getOptimalSharingMode( forceMemoryExclusivity, queueFamilyIndexCount, device );
    this->_pCommandPool             = pCommandPool;

    /// setup CPU staging buffer
    VulkanResult setupStagingBufferResult = this->_stagingBuffer.setup(
            device,
            indexCount,
            sharingMode,
            pQueueFamilyIndices,
            queueFamilyIndexCount
    );

    if ( setupStagingBufferResult != VulkanResult::VK_SUCCESS )
        return setupStagingBufferResult;

    /// set element count
    this->setElementCount( this->_stagingBuffer.getElementCount() );
    /// setup this buffer on GPU
    return VBuffer::setup(
            device,
            static_cast < std::size_t > ( this->_stagingBuffer.size() ),/// no. of elements that staging buffer has
            VBuffer::INDEX_BUFFER_GPU_LOCAL,
            sharingMode,
            pQueueFamilyIndices,
            queueFamilyIndexCount
    );
}

auto engine::VIndexBuffer32::setup(
    engine::VLogicalDevice    const & device,
    std::vector<uint32>       const & indices,
    engine::VCommandPool      const * pCommandPool,
    uint32                    const * pQueueFamilyIndices,
    uint32                            queueFamilyIndexCount,
    bool                              forceMemoryExclusivity
) noexcept -> VulkanResult {
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

auto engine::VIndexBuffer32::setup(
    engine::VLogicalDevice    const & device,
    uint32                            vertexCount,
    engine::VCommandPool      const * pCommandPool,
    uint32                    const * pQueueFamilyIndices,
    uint32                            queueFamilyIndexCount,
    bool                              forceMemoryExclusivity
) noexcept -> VulkanResult {

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

auto engine::VIndexBuffer16::load( std::vector<uint16> const & indices) noexcept -> VulkanResult {
    /// load how much is possible
    auto copyElementCount = std::min (
        static_cast < uint32 > ( this->_stagingBuffer.getElementCount() ),
        static_cast < uint32 > ( indices.size() )
    );

    /// copy into staging buffer local data
    for ( uint32 it = 0; it < copyElementCount; it++ )
        this->_stagingBuffer._data [it] = indices [it];

    /// reload the staging buffer
    this->_stagingBuffer.reload();
    /// adjust element count of staging and this buffer
    this->_stagingBuffer.setElementCount( copyElementCount );
    this->setElementCount( copyElementCount );

    /// finally, flush data
    return this->flush();
}


auto engine::VIndexBuffer32::load(const std::vector<uint32> & indices) noexcept -> VulkanResult {
    /// same as above
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

#include <sstream>

auto engine::VIndexBuffer16::toString() const noexcept -> String {
    std::stringstream oss;

    oss << "VIndexBuffer16 { " <<
        "base = " << VIndexBufferBase::toString() <<
        ", stagingBuffer = " << this->_stagingBuffer.toString() << " }";

    return oss.str();
}

auto engine::VIndexBuffer32::toString() const noexcept -> String {
    std::stringstream oss;

    oss << "VIndexBuffer32 { " <<
        "base = " << VIndexBufferBase::toString() <<
        ", stagingBuffer = " << this->_stagingBuffer.toString() << " }";

    return oss.str();
}
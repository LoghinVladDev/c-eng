//
// Created by vladl on 8/30/2020.
//

#include "VVertexBuffer.hpp"

inline static auto getPackedVertices ( engine::VVertex const * vertices, uint32 size ) noexcept -> std::vector < engine::VVertex::SVertexPack > {
    std::vector < engine::VVertex::SVertexPack > packedVertices (size) ;

    for ( uint32 i = 0; i < size; i++ )
        packedVertices[i] = vertices[i].getPackedData();

    return packedVertices;
}

auto engine::VVertexBuffer::setup(
    engine::VLogicalDevice    const & device,
    std::vector< VVertex >    const & vertices,
    engine::VCommandPool      const * pCommandPool,
    uint32                    const * pQueueFamilyIndices,
    uint32                            queueFamilyIndexCount,
    bool                              forceMemoryExclusivity
) noexcept -> VulkanResult {
    auto packedVertices = getPackedVertices( vertices.data(), static_cast<uint32>(vertices.size()) );
    return this->setup(
        device,
        packedVertices,
        pCommandPool,
        pQueueFamilyIndices,
        queueFamilyIndexCount,
        forceMemoryExclusivity
    );
}

auto engine::VVertexBuffer::setup(
    engine::VLogicalDevice                const & device,
    std::vector< VVertex::SVertexPack >   const & vertices,
    engine::VCommandPool                  const * pCommandPool,
    uint32                                const * pQueueFamilyIndices,
    uint32                                        queueFamilyIndexCount,
    bool                                          forceMemoryExclusivity
) noexcept -> VulkanResult {
    VulkanSharingMode sharingMode   = VBuffer::getOptimalSharingMode( forceMemoryExclusivity, queueFamilyIndexCount, device );
    this->_pCommandPool             = pCommandPool;

    VulkanResult setupStagingBufferResult = this->_stagingBuffer.setup(
        device,
        vertices,
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
        VBuffer::VERTEX_BUFFER_GPU_LOCAL,
        sharingMode,
        pQueueFamilyIndices,
        queueFamilyIndexCount
    );
}

auto engine::VVertexBuffer::setup(
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
        VBuffer::VERTEX_BUFFER_GPU_LOCAL,
        sharingMode,
        pQueueFamilyIndices,
        queueFamilyIndexCount
    );
}

auto engine::VVertexBuffer::load(std::vector<VVertex> const & vertices) noexcept -> VulkanResult {
    auto packedVertices = getPackedVertices( vertices.data(), static_cast<uint32>(vertices.size()) );
    return this->load( packedVertices );
}

auto engine::VVertexBuffer::load(std::vector<VVertex::SVertexPack> const & packedVertices) noexcept -> VulkanResult {
    auto copyElementCount = std::min (
        static_cast < uint32 > ( this->_stagingBuffer.getElementCount() ),
        static_cast < uint32 > ( packedVertices.size() )
    );

    for ( uint32 it = 0; it < copyElementCount; it++ )
        this->_stagingBuffer._data [it] = packedVertices [it];

    this->_stagingBuffer.reload();
    this->_stagingBuffer.setElementCount( copyElementCount );
    this->setElementCount( copyElementCount );

    return this->flush();
}

auto engine::VVertexBuffer::flush() noexcept -> VulkanResult {
    return this->copyFrom(
        this->_stagingBuffer,
        * this->_pCommandPool,
        this->_stagingBuffer.size()
    );
}

auto engine::VVertexBuffer::allocateMemory() noexcept -> VulkanResult {
    VulkanResult allocateResult = VBuffer::allocateMemory( VBuffer::MEMORY_GPU_BUFFER_FLAGS );
    if ( allocateResult != VulkanResult::VK_SUCCESS )
        return allocateResult;

    allocateResult = this->_stagingBuffer.allocateMemory();
    if ( allocateResult != VulkanResult::VK_SUCCESS )
        return allocateResult;

    return this->flush();
}

auto engine::VVertexBuffer::free() noexcept -> void {
    this->_stagingBuffer.free();
    VBuffer::free();
}

auto engine::VVertexBuffer::clear() noexcept -> void {
    this->_stagingBuffer.clear();
    VBuffer::clear();
}

#include <sstream>
auto engine::VVertexBuffer::toString() const noexcept -> String {
    std::stringstream oss;

    oss << "VVertexBuffer { " <<
        "pCommandPool = 0x" << std::hex << this->_pCommandPool <<
        ", base = " << VBuffer::toString() <<
        ", staging = " << this->_stagingBuffer.toString() << " }";

    return oss.str();
}
//
// Created by vladl on 8/30/2020.
//

#include "VVertexBuffer.hpp"

inline static std::vector < engine::VVertex::SVertexPack > getPackedVertices ( const engine::VVertex * vertices, uint32 size ) noexcept {
    std::vector < engine::VVertex::SVertexPack > packedVertices (size) ;

    for ( uint32 i = 0; i < size; i++ )
        packedVertices[i] = vertices[i].getPackedData();

    return packedVertices;
}

VulkanResult engine::VVertexBuffer::setup(
    const engine::VLogicalDevice    & device,
    const std::vector< VVertex >    & vertices,
    const engine::VCommandPool      * pCommandPool,
    const uint32                    * pQueueFamilyIndices,
    uint32                            queueFamilyIndexCount,
    bool                              forceMemoryExclusivity
) noexcept {
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

VulkanResult engine::VVertexBuffer::setup(
    const engine::VLogicalDevice                & device,
    const std::vector< VVertex::SVertexPack >   & vertices,
    const engine::VCommandPool                  * pCommandPool,
    const uint32                                * pQueueFamilyIndices,
    uint32                                        queueFamilyIndexCount,
    bool                                          forceMemoryExclusivity
) noexcept {
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

VulkanResult engine::VVertexBuffer::setup(
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
        VBuffer::VERTEX_BUFFER_GPU_LOCAL,
        sharingMode,
        pQueueFamilyIndices,
        queueFamilyIndexCount
    );
}

VulkanResult engine::VVertexBuffer::load(const std::vector<VVertex> & vertices) noexcept {
    auto packedVertices = getPackedVertices( vertices.data(), static_cast<uint32>(vertices.size()) );
    return this->load( packedVertices );
}

VulkanResult engine::VVertexBuffer::load(const std::vector<VVertex::SVertexPack> & packedVertices) noexcept {
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

VulkanResult engine::VVertexBuffer::flush() noexcept {
    return this->copyFrom(
        this->_stagingBuffer,
        * this->_pCommandPool,
        this->_stagingBuffer.size()
    );
}

VulkanResult engine::VVertexBuffer::allocateMemory() noexcept {
    VulkanResult allocateResult = VBuffer::allocateMemory( VBuffer::MEMORY_GPU_BUFFER_FLAGS );
    if ( allocateResult != VulkanResult::VK_SUCCESS )
        return allocateResult;

    allocateResult = this->_stagingBuffer.allocateMemory();
    if ( allocateResult != VulkanResult::VK_SUCCESS )
        return allocateResult;

    return this->flush();
}

void engine::VVertexBuffer::free() noexcept {
    this->_stagingBuffer.free();
    VBuffer::free();
}

void engine::VVertexBuffer::cleanup() noexcept {
    this->_stagingBuffer.cleanup();
    VBuffer::cleanup();
}

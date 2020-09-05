//
// Created by loghin on 9/5/20.
//

#include "VStagingBuffer.h"

inline static std::vector < engine::VVertex::SVertexPack > getPackedVertices ( const engine::VVertex * vertices, uint32 size ) noexcept {
    std::vector < engine::VVertex::SVertexPack > packedVertices (size) ;

    for ( uint32 i = 0; i < size; i++ )
        packedVertices[i] = vertices[i].getPackedData();

    return packedVertices;
}

VulkanResult engine::VStagingBuffer::setup(
    const VLogicalDevice        & device,
    const std::vector<VVertex>  & vertices,
    VulkanSharingMode             sharingMode,
    const uint32                * pQueueFamilyIndices,
    uint32                        queueFamilyIndexCount
) noexcept {
    this->_pVertices    = & vertices;
//    this->_vertexCount  = vertices.size();
    this->setElementCount( vertices.size() );

    this->_packedVertices = getPackedVertices(
        vertices.data(),
        static_cast < uint32 > ( vertices.size() )
    );

    return VBuffer::setup(
        device,
        static_cast < std::size_t > ( this->_packedVertices.size() * sizeof ( VVertex::SVertexPack ) ),
        VBuffer::STAGING_BUFFER_CPU_LOCAL,
        sharingMode,
        pQueueFamilyIndices,
        queueFamilyIndexCount
    );
}

void engine::VStagingBuffer::cleanup() noexcept {
    return VBuffer::cleanup();
}

VulkanResult engine::VStagingBuffer::allocateMemory() noexcept {
    VulkanResult allocateResult = VBuffer::allocateMemory( VBuffer::MEMORY_CPU_BUFFER_FLAGS );
    if ( allocateResult != VulkanResult::VK_SUCCESS )
        return allocateResult;

    return VBuffer::copyOntoBuffer(
        static_cast < void * > ( this->_packedVertices.data() ),
        static_cast < std::size_t > ( this->_packedVertices.size() * sizeof ( VVertex::SVertexPack ) )
    );
}

void engine::VStagingBuffer::free() noexcept {
    return VBuffer::free();
}
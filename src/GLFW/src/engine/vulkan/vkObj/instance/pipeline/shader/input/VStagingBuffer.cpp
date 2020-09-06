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

VulkanResult engine::VStagingBuffer::setup(
    const VLogicalDevice        & device,
    const std::vector<uint16>   & indices,
    VulkanSharingMode             sharingMode,
    const uint32                * pQueueFamilyIndices,
    uint32                        queueFamilyIndexCount
) noexcept {
    this->_pIndices16    = & indices;
//    this->_vertexCount  = vertices.size();
    this->setElementCount( indices.size() );

    return VBuffer::setup(
        device,
        static_cast < std::size_t > ( this->_pIndices16->size() * sizeof ( uint16 ) ),
        VBuffer::STAGING_BUFFER_CPU_LOCAL,
        sharingMode,
        pQueueFamilyIndices,
        queueFamilyIndexCount
    );
}

VulkanResult engine::VStagingBuffer::setup(
    const VLogicalDevice        & device,
    const std::vector<uint32>   & indices,
    VulkanSharingMode             sharingMode,
    const uint32                * pQueueFamilyIndices,
    uint32                        queueFamilyIndexCount
) noexcept {
    this->_pIndices32    = & indices;
//    this->_vertexCount  = vertices.size();
    this->setElementCount( indices.size() );

    return VBuffer::setup(
        device,
        static_cast < std::size_t > ( this->_pIndices32->size() * sizeof (uint32) ),
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

    if ( ! this->_packedVertices.empty() )
        return VBuffer::copyOntoBuffer(
            static_cast < const void * > ( this->_packedVertices.data() ),
            static_cast < std::size_t > ( this->_packedVertices.size() * sizeof ( VVertex::SVertexPack ) )
        );
    else if ( this->_pIndices16 != nullptr )
        return VBuffer::copyOntoBuffer(
            static_cast < const void * > ( this->_pIndices16->data() ),
            static_cast < std::size_t > ( this->_pIndices16->size() * sizeof ( uint16 ) )
        );
    else if ( this->_pIndices32 != nullptr )
        return VBuffer::copyOntoBuffer(
            static_cast < const void * > ( this->_pIndices32->data() ),
            static_cast < std::size_t > ( this->_pIndices32->size() * sizeof ( uint32 ) )
        );

    return VulkanResult::VK_ERROR_MEMORY_MAP_FAILED;
}

void engine::VStagingBuffer::free() noexcept {
    return VBuffer::free();
}
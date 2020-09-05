//
// Created by vladl on 8/30/2020.
//

#include "VVertexBuffer.h"

inline static std::vector < engine::VVertex::SVertexPack > getPackedVertices ( const engine::VVertex * vertices, uint32 size ) noexcept {
    std::vector < engine::VVertex::SVertexPack > packedVertices (size) ;

    for ( uint32 i = 0; i < size; i++ )
        packedVertices[i] = vertices[i].getPackedData();

    return packedVertices;
}

VulkanResult engine::VVertexBuffer::setup(
    const VLogicalDevice                    & device,
    const std::vector < engine::VVertex >   & vertices,
    VulkanSharingMode                         sharingMode,
    uint32                                    queueFamilyIndexCount,
    const uint32                            * pQueueFamilyIndices
) noexcept {
    this->_pVertices        = & vertices;
    this->setElementCount( vertices.size() );

    this->_packedVertices = getPackedVertices(
        vertices.data(),
        static_cast < uint32 > ( vertices.size() )
    );

    return VBuffer::setup(
        device,
        static_cast < std::size_t > ( this->_packedVertices.size() * sizeof ( VVertex::SVertexPack ) ),
        VBuffer::VERTEX_BUFFER_CPU_LOCAL,
        sharingMode,
        queueFamilyIndexCount,
        pQueueFamilyIndices
    );
}

VulkanResult engine::VVertexBuffer::setup(
    const VLogicalDevice &  device,
    std::size_t             size,
    VulkanSharingMode       sharingMode,
    uint32                  queueFamilyIndexCount,
    const uint32          * pQueueFamilyIndices
) noexcept {
    return VBuffer::setup(
        device,
        size,
        VBuffer::VERTEX_BUFFER_GPU_LOCAL,
        sharingMode,
        queueFamilyIndexCount,
        pQueueFamilyIndices
    );
}

void engine::VVertexBuffer::cleanup() noexcept {
    return VBuffer::cleanup();
}

VulkanResult engine::VVertexBuffer::allocateMemory() noexcept {
    if ( this->getBufferUsageFlags() == VBuffer::VERTEX_BUFFER_GPU_LOCAL )
        return VBuffer::allocateMemory( VBuffer::MEMORY_GPU_LOCAL );
    else if ( this->getBufferUsageFlags() == VBuffer::VERTEX_BUFFER_CPU_LOCAL ) {
        VulkanResult allocateResult = VBuffer::allocateMemory( VBuffer::MEMORY_CPU_BUFFER_FLAGS );
        if ( allocateResult != VulkanResult::VK_SUCCESS )
            return allocateResult;

        return copyOntoBuffer(
            static_cast < void * > ( this->_packedVertices.data() ),
            static_cast < std::size_t > ( this->_packedVertices.size() * sizeof ( VVertex::SVertexPack ) )
        );
    }

    return VulkanResult::VK_INCOMPLETE;
}

VulkanResult engine::VVertexBuffer::allocateMemory(
    VulkanMemoryPropertyFlags memoryPropertyFlags
) noexcept {
    if ( memoryPropertyFlags == VBuffer::MEMORY_CPU_BUFFER_FLAGS ) {
        VulkanResult allocateResult = VBuffer::allocateMemory( VBuffer::MEMORY_CPU_BUFFER_FLAGS );
        if ( allocateResult != VulkanResult::VK_SUCCESS )
            return allocateResult;

        return VBuffer::copyOntoBuffer(
                static_cast < void * > ( this->_packedVertices.data() ),
                static_cast < std::size_t > ( this->_packedVertices.size() * sizeof ( VVertex::SVertexPack ) )
        );
    }

    return VBuffer::allocateMemory( memoryPropertyFlags );
}

void engine::VVertexBuffer::free() noexcept {
    return VBuffer::free();
}
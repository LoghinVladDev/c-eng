//
// Created by vladl on 8/30/2020.
//

#include "VVertexBuffer.h"

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

inline static std::vector < engine::VVertex::SVertexPack > getPackedVertices ( const engine::VVertex * vertices, uint32 size ) noexcept {
    std::vector < engine::VVertex::SVertexPack > packedVertices (size) ;

    for ( uint32 i = 0; i < size; i++ )
        packedVertices[i] = vertices[i].getPackedData();

    return packedVertices;
}

VulkanResult engine::VVertexBuffer::setup(
    const VLogicalDevice                    & device,
    const std::vector < engine::VVertex >   & vertices,
    VulkanBufferUsageFlags                    usageFlags,
    VulkanSharingMode                         sharingMode
) noexcept {
    this->_pLogicalDevice = & device;
    this->_pVertices = & vertices;
    this->_vertexCount = vertices.size();

    VulkanBufferCreateInfo createInfo { };
    populateVertexBufferCreateInfo(
        & createInfo,
        static_cast < VulkanDeviceSize > (sizeof ( engine::VVertex::SVertexPack ) * vertices.size()),
        usageFlags,
        sharingMode
    );

    this->_memorySize = createInfo.size;

    return vkCreateBuffer( this->_pLogicalDevice->data(), & createInfo, nullptr, & this->_handle );
}

void engine::VVertexBuffer::cleanup() noexcept {
    vkDestroyBuffer( this->_pLogicalDevice->data(), this->_handle, nullptr );
}

VulkanResult engine::VVertexBuffer::allocateMemory(
    VulkanMemoryPropertyFlags memoryPropertyFlags
) noexcept {
    VulkanMemoryRequirements memoryRequirements;
    vkGetBufferMemoryRequirements( this->_pLogicalDevice->data(), this->_handle, & memoryRequirements );

    VulkanMemoryAllocateInfo allocateInfo { };

    try {
        populateVertexBufferMemoryAllocateInfo(
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

    VulkanResult allocateInfoResult = vkAllocateMemory (
            this->_pLogicalDevice->data(),
            & allocateInfo,
            nullptr,
            & this->_memoryHandle
    );

    if ( allocateInfoResult != VulkanResult::VK_SUCCESS )
        return allocateInfoResult;

    VulkanResult bindResult = vkBindBufferMemory(
            this->_pLogicalDevice->data(),
            this->_handle,
            this->_memoryHandle,
            0ULL
    );

    if ( bindResult != VulkanResult::VK_SUCCESS )
        return bindResult;

    auto packedVertices = getPackedVertices( this->_pVertices->data(), static_cast <uint32> (this->_pVertices->size()) );

    void * data;
    VulkanResult mapMemoryResult = vkMapMemory(this->_pLogicalDevice->data(), this->_memoryHandle,0ULL, this->_memorySize,0, & data );
    if ( mapMemoryResult != VulkanResult::VK_SUCCESS )
        return mapMemoryResult;

    memcpy ( data, packedVertices.data(), ( std::size_t ) this->_memorySize );

    vkUnmapMemory( this->_pLogicalDevice->data(), this->_memoryHandle );

    return VulkanResult::VK_SUCCESS;
}

void engine::VVertexBuffer::free() noexcept {
    vkFreeMemory( this->_pLogicalDevice->data(), this->_memoryHandle, nullptr );
}
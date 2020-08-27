//
// Created by vladl on 8/27/2020.
//

#include "VVertex.h"

inline static void populateVertexInputBindingDescription (
    VulkanVertexInputBindingDescription * description,
    uint32                                bindingIndex,
    uint32                                stride,
    VulkanVertexInputRate                 rate
) noexcept {
    if ( description == nullptr )
        return;

    * description = VulkanVertexInputBindingDescription  {
        .binding    = bindingIndex,
        .stride     = stride,
        .inputRate  = rate
    };
}

inline static void populateVertexInputAttributeDescription (
    VulkanVertexInputAttributeDescription * description,
    uint32                                  bindingIndex,
    uint32                                  location,
    VulkanFormat                            format,
    uint32                                  offset
) noexcept {
    if ( description == nullptr )
        return;

    * description = VulkanVertexInputAttributeDescription  {
        .location   = location,
        .binding    = bindingIndex,
        .format     = format,
        .offset     = offset
    };
}

inline static void populateVertexBufferCreateInfo (
    VulkanBufferCreateInfo    * createInfo,
    VulkanDeviceSize            size,
    VulkanBufferUsageFlags      usageFlags,
    VulkanSharingMode           sharingMode
) noexcept {
    if ( createInfo == nullptr )
        return;

    * createInfo = VulkanBufferCreateInfo {
        .sType          = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .size           = size,
        .usage          = usageFlags,
        .sharingMode    = sharingMode
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

inline static std::vector < engine::VVertex::SVertexPack > getPackedVertices ( const std::vector < engine::VVertex > & vertices ) noexcept {
    std::vector < engine::VVertex::SVertexPack > packedVertices;

    for ( const auto & vertex : vertices )
        packedVertices.emplace_back( vertex.getPackedData() );

    return packedVertices;
}

VulkanVertexInputBindingDescription engine::VVertex::getBindingDescription() noexcept {
    VulkanVertexInputBindingDescription bindingDescription { };

    populateVertexInputBindingDescription(
        & bindingDescription,
        0U,
        static_cast < uint32 > ( sizeof ( engine::VVertex::SVertexPack ) ),
        VulkanVertexInputRate::VK_VERTEX_INPUT_RATE_VERTEX
    );

    return bindingDescription;
}

std::array < VulkanVertexInputAttributeDescription, engine::VVertex::PACK_PROPERTIES_COUNT > engine::VVertex::getAttributeDescriptions() noexcept {
    std::array < VkVertexInputAttributeDescription, engine::VVertex::PACK_PROPERTIES_COUNT > attributeDescriptions { };

    populateVertexInputAttributeDescription(
        & attributeDescriptions[ 0 ],
        0U,
        0U,
        VVertex::FLOAT_VEC2_FORMAT,
        offsetof ( engine::VVertex::SVertexPack, position )
    );

    populateVertexInputAttributeDescription(
        & attributeDescriptions[ 1 ],
        0U,
        1U,
        VVertex::FLOAT_VEC3_FORMAT,
        offsetof ( engine::VVertex::SVertexPack, color )
    );

    return attributeDescriptions;
}

VulkanResult engine::VVertexBuffer::setup(const VLogicalDevice & device, const std::vector < engine::VVertex > & vertices ) noexcept {
    this->_pLogicalDevice = & device;
    this->_pVertices = & vertices;
    this->_vertexCount = vertices.size();

    VulkanBufferCreateInfo createInfo { };
    populateVertexBufferCreateInfo(
        & createInfo,
        static_cast < VulkanDeviceSize > (sizeof ( engine::VVertex::SVertexPack ) * vertices.size()),
        VulkanBufferUsageFlagBits::VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
        VulkanSharingMode::VK_SHARING_MODE_EXCLUSIVE
    );

    this->_memorySize = createInfo.size;

    return vkCreateBuffer( this->_pLogicalDevice->data(), & createInfo, nullptr, & this->_handle );
}

void engine::VVertexBuffer::cleanup() noexcept {
    vkDestroyBuffer( this->_pLogicalDevice->data(), this->_handle, nullptr );
}

VulkanResult engine::VVertexBuffer::allocateMemory() noexcept {
    VulkanMemoryRequirements memoryRequirements;
    vkGetBufferMemoryRequirements( this->_pLogicalDevice->data(), this->_handle, & memoryRequirements );

    VulkanMemoryAllocateInfo allocateInfo { };

    try {
        populateVertexBufferMemoryAllocateInfo(
                &allocateInfo,
                memoryRequirements.size,
                findMemoryType(
                        memoryRequirements.memoryTypeBits,
                        VulkanMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                        VulkanMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
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

    auto packedVertices = getPackedVertices( * this->_pVertices );

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
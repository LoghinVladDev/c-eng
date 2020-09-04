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

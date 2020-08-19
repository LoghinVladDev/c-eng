//
// Created by Vlad on 19/08/2020.
//

#include "VPipeline.h"

inline static void populateVertexInputStateCreateInfo (
    VulkanPipelineVertexInputStateCreateInfo * createInfo
) noexcept {
    if ( createInfo == nullptr )
        return;

    * createInfo = { };

    createInfo->sType                           = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    createInfo->vertexBindingDescriptionCount   = 0U;
    createInfo->pVertexBindingDescriptions      = nullptr;
    createInfo->vertexAttributeDescriptionCount = 0U;
    createInfo->pVertexAttributeDescriptions    = nullptr;
}

inline static void populateInputAssemblyStateCreateInfo (
    VkPipelineInputAssemblyStateCreateInfo * createInfo
) noexcept {
    if ( createInfo == nullptr )
        return;

    * createInfo = { };

    createInfo->sType                           = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    createInfo->topology                        = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    createInfo->primitiveRestartEnable          = VK_FALSE;
}

inline static void populateViewportStructure (
    VulkanViewport * viewport,
    float x,
    float y,
    float width,
    float height
) noexcept {
    if ( viewport == nullptr )
        return;

    * viewport = { };

    viewport->x         = x;
    viewport->y         = y;
    viewport->width     = width;
    viewport->height    = height;
    viewport->minDepth  = 0.0f;
    viewport->maxDepth  = 1.0f;
}

inline static void populateScissorStructure (
    VulkanRectangle2D * scissor,
    int32 xOffset,
    int32 yOffset,
    const VulkanExtent2D & extent
) noexcept {
    if( scissor == nullptr )
        return;

    * scissor = {};

    scissor->offset = { xOffset, yOffset };
    scissor->extent = extent;
}

inline static void populateViewportStateCreateInfo (
    VulkanPipelineViewportStateCreateInfo * createInfo,
    VulkanViewport * pViewports,
    uint32 viewportCount,
    VulkanRectangle2D * pScissors,
    uint32 scissorCount
) noexcept {
    if ( createInfo == nullptr )
        return;

    * createInfo = { };

    createInfo->sType           = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    createInfo->viewportCount   = viewportCount;
    createInfo->scissorCount    = scissorCount;
    createInfo->pViewports      = pViewports;
    createInfo->pScissors       = pScissors;
}

inline static void populateRasterizationStateCreateInfo (
    VulkanPipelineRasterizationStateCreateInfo * createInfo
) noexcept {
    if ( createInfo == nullptr )
        return;

    * createInfo = { };

    createInfo->sType                   = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    createInfo->depthClampEnable        = VK_FALSE;
    createInfo->rasterizerDiscardEnable = VK_FALSE;
    createInfo->polygonMode             = VK_POLYGON_MODE_FILL;
    createInfo->lineWidth               = 1.0f;
    createInfo->cullMode                = VK_CULL_MODE_BACK_BIT;
    createInfo->frontFace               = VK_FRONT_FACE_CLOCKWISE;

    createInfo->depthBiasEnable         = VK_FALSE;
    createInfo->depthBiasConstantFactor = 0.0f;
    createInfo->depthBiasClamp          = 0.0f;
    createInfo->depthBiasSlopeFactor    = 0.0f;
}

inline static void populateMultisampleStateCreateInfo (
    VulkanPipelineMultisampleStateCreateInfo * createInfo
) noexcept {
    if ( createInfo == nullptr )
        return;

    * createInfo = { };

    createInfo->sType                   = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    createInfo->sampleShadingEnable     = VK_FALSE;
    createInfo->rasterizationSamples    = VK_SAMPLE_COUNT_1_BIT;
    createInfo->minSampleShading        = 1.0f;
    createInfo->pSampleMask             = nullptr;
    createInfo->alphaToCoverageEnable   = VK_FALSE;
    createInfo->alphaToOneEnable        = VK_FALSE;
}

inline static void populateColorBlendAttachmentStateDisabled (
    VulkanPipelineColorBlendAttachmentState * colorBlendAttachment
) noexcept {
    if ( colorBlendAttachment == nullptr )
        return;

    * colorBlendAttachment = { };

    colorBlendAttachment->colorWriteMask =
            VK_COLOR_COMPONENT_R_BIT |
            VK_COLOR_COMPONENT_G_BIT |
            VK_COLOR_COMPONENT_B_BIT |
            VK_COLOR_COMPONENT_A_BIT;

    colorBlendAttachment->blendEnable = VK_FALSE;
}

inline static void populateColorBlendAttachmentStateEnabled (
    VulkanPipelineColorBlendAttachmentState * colorBlendAttachment
) noexcept {
    if ( colorBlendAttachment == nullptr )
        return;

    * colorBlendAttachment = { };

    colorBlendAttachment->blendEnable           = VK_TRUE;
    colorBlendAttachment->srcColorBlendFactor   = VK_BLEND_FACTOR_SRC_ALPHA;
    colorBlendAttachment->dstColorBlendFactor   = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    colorBlendAttachment->colorBlendOp          = VK_BLEND_OP_ADD;
    colorBlendAttachment->srcAlphaBlendFactor   = VK_BLEND_FACTOR_ONE;
    colorBlendAttachment->dstAlphaBlendFactor   = VK_BLEND_FACTOR_ZERO;
    colorBlendAttachment->alphaBlendOp          = VK_BLEND_OP_ADD;
}

inline static void populateColorBlendStateCreateInfo (
    VulkanPipelineColorBlendStateCreateInfo * createInfo,
    VulkanPipelineColorBlendAttachmentState * attachment
) noexcept {
    if ( createInfo == nullptr || attachment == nullptr )
        return;

    * createInfo = { };

    createInfo->sType               = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    createInfo->logicOpEnable       = ( ( attachment->blendEnable == VK_TRUE ) ? ( VK_FALSE ) : ( VK_TRUE ) );

    createInfo->logicOp             = VK_LOGIC_OP_COPY;
    createInfo->attachmentCount     = 1U;
    createInfo->pAttachments        = attachment;
    createInfo->blendConstants[0]   = 0.0f;
    createInfo->blendConstants[1]   = 0.0f;
    createInfo->blendConstants[2]   = 0.0f;
    createInfo->blendConstants[3]   = 0.0f;
}

inline static void populateDynamicStateCreateInfo (
    VulkanPipelineDynamicStateCreateInfo * createInfo,
    const VulkanDynamicState             * pDynamicStates,
    uint32                                 dynamicStateCount
) noexcept {
    if ( createInfo == nullptr )
        return;

    * createInfo = { };

    createInfo->sType               = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    createInfo->dynamicStateCount   = dynamicStateCount;
    createInfo->pDynamicStates      = pDynamicStates;
}

inline static void populateLayoutCreateInfo (
    VulkanPipelineLayoutCreateInfo * createInfo
) noexcept {
    if ( createInfo == nullptr )
        return;

    * createInfo = { };

    createInfo->sType                   = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    createInfo->setLayoutCount          = 0U;
    createInfo->pSetLayouts             = nullptr;
    createInfo->pushConstantRangeCount  = 0U;
    createInfo->pPushConstantRanges     = nullptr;
}

VulkanResult engine::VPipeline::setup(const std::vector<VulkanPipelineShaderStageCreateInfo> & shaderStages, const engine::VLogicalDevice & device) noexcept(false) {
    this->_pLogicalDevice = & device;
    VulkanPipelineLayoutCreateInfo layoutCreateInfo { };

    populateLayoutCreateInfo ( & layoutCreateInfo );

    VulkanResult createLayoutResult = vkCreatePipelineLayout( this->_pLogicalDevice->data(), & layoutCreateInfo, nullptr, & this->_layoutHandle );

    return createLayoutResult;
}

void engine::VPipeline::cleanup() noexcept {
    if ( this->_layoutHandle == nullptr )
        return;

    vkDestroyPipelineLayout( this->_pLogicalDevice->data(), this->_layoutHandle, nullptr );
}

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
    VulkanPipelineViewportStateCreateInfo   * createInfo,
    VulkanViewport                          * pViewports,
    uint32                                    viewportCount,
    VulkanRectangle2D                       * pScissors,
    uint32                                    scissorCount
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

constexpr static VulkanFlags COLOR_WRITE_MASK =
    ( uint32 ) VK_COLOR_COMPONENT_R_BIT |
    ( uint32 ) VK_COLOR_COMPONENT_G_BIT |
    ( uint32 ) VK_COLOR_COMPONENT_B_BIT |
    ( uint32 ) VK_COLOR_COMPONENT_A_BIT;

inline static void populateColorBlendAttachmentStateDisabled (
        VulkanPipelineColorBlendAttachmentState * colorBlendAttachment
) noexcept {
    if ( colorBlendAttachment == nullptr )
        return;

    * colorBlendAttachment = { };

    colorBlendAttachment->colorWriteMask = COLOR_WRITE_MASK;

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

[[maybe_unused]] inline static void populateDynamicStateCreateInfo (
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

inline static void populateGraphicsPipelineCreateInfo (
    VulkanGraphicsPipelineCreateInfo                    * createInfo,
    const VulkanPipelineShaderStageCreateInfo           * pShaderStages,
    uint32                                                shaderStageCount,
    const VulkanPipelineVertexInputStateCreateInfo      * pVertexInputState,
    const VulkanPipelineInputAssemblyStateCreateInfo    * pInputAssemblyState,
    const VulkanPipelineViewportStateCreateInfo         * pViewportState,
    const VulkanPipelineRasterizationStateCreateInfo    * pRasterizerState,
    const VulkanPipelineMultisampleStateCreateInfo      * pMultisampleState,
    const VulkanPipelineDepthStencilStateCreateInfo     * pDepthStencilState,
    const VulkanPipelineColorBlendStateCreateInfo       * pColorBlendState,
    const VulkanPipelineDynamicStateCreateInfo          * pDynamicState,
    VulkanPipelineLayout                                  layout,
    const engine::VRenderPass                           * pRenderPass,
    uint32                                                subpass,
    const engine::VPipeline                             * pBasePipeline         = nullptr,
    int32                                                 basePipelineIndex     = -1
) noexcept {
    if (
        createInfo          == nullptr ||
        pShaderStages       == nullptr ||
        pVertexInputState   == nullptr ||
        pInputAssemblyState == nullptr ||
        pViewportState      == nullptr ||
        pRasterizerState    == nullptr ||
        pMultisampleState   == nullptr ||
        pColorBlendState    == nullptr ||
        pRenderPass         == nullptr
    )
        return;

    * createInfo = { };

    createInfo->sType                   = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    createInfo->stageCount              = shaderStageCount;
    createInfo->pStages                 = pShaderStages;

    createInfo->pVertexInputState       = pVertexInputState;
    createInfo->pInputAssemblyState     = pInputAssemblyState;
    createInfo->pViewportState          = pViewportState;
    createInfo->pRasterizationState     = pRasterizerState;
    createInfo->pMultisampleState       = pMultisampleState;
    createInfo->pDepthStencilState      = pDepthStencilState;
    createInfo->pColorBlendState        = pColorBlendState;
    createInfo->pDynamicState           = pDynamicState;

    createInfo->layout                  = layout;

    createInfo->renderPass              = pRenderPass->data();
    createInfo->subpass                 = subpass;

    createInfo->basePipelineIndex       = basePipelineIndex;

    if ( pBasePipeline == nullptr )
        createInfo->basePipelineHandle  = VK_NULL_HANDLE;
    else
        createInfo->basePipelineHandle  = pBasePipeline->data();
}

void engine::VPipeline::createRenderPass() noexcept (false) {
    VulkanSubpassDependency waitForImageSubpassDependency;
    waitForImageSubpassDependency.srcSubpass    = VK_SUBPASS_EXTERNAL;
    waitForImageSubpassDependency.dstSubpass    = 0U;
    waitForImageSubpassDependency.dependencyFlags = 0U;
    waitForImageSubpassDependency.srcStageMask  = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    waitForImageSubpassDependency.srcAccessMask = 0U;

    waitForImageSubpassDependency.dstStageMask  = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    waitForImageSubpassDependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

    if ( this->_renderPass.setup( * this->_pLogicalDevice, & waitForImageSubpassDependency, 1U ) != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ("render pass creation failure");
}

void engine::VPipeline::cleanup() noexcept {
    if ( this->_handle != nullptr )
        vkDestroyPipeline ( this->_pLogicalDevice->data(), this->_handle, nullptr );
    this->_renderPass.cleanup();
    if ( this->_layoutHandle == nullptr )
        return;
    vkDestroyPipelineLayout( this->_pLogicalDevice->data(), this->_layoutHandle, nullptr );
}

VulkanResult engine::VPipeline::setup(const VulkanPipelineShaderStageCreateInfo * pShaderStages, uint32 shaderStageCount, const engine::VLogicalDevice & device ) noexcept(false) {
    this->_pLogicalDevice = & device;
    this->createRenderPass();

    auto extent = this->_pLogicalDevice->getSwapChain()->getImagesInfo().extent;

    VulkanPipelineLayoutCreateInfo              layoutCreateInfo                { };

    populateLayoutCreateInfo ( & layoutCreateInfo );

    VulkanResult createLayoutResult = vkCreatePipelineLayout( this->_pLogicalDevice->data(), & layoutCreateInfo, nullptr, & this->_layoutHandle );

    if( createLayoutResult != VK_SUCCESS )
        return createLayoutResult;

    VulkanPipelineVertexInputStateCreateInfo    vertexInputStateCreateInfo      { };
    VulkanPipelineInputAssemblyStateCreateInfo  inputAssemblyStateCreateInfo    { };
    VulkanViewport                              viewport                        { };
    VulkanRectangle2D                           scissor                         { };
    VulkanPipelineViewportStateCreateInfo       viewportStateCreateInfo         { };
    VulkanPipelineRasterizationStateCreateInfo  rasterizationStateCreateInfo    { };
    VulkanPipelineMultisampleStateCreateInfo    multisampleStateCreateInfo      { };
    VulkanPipelineColorBlendAttachmentState     colorBlendAttachmentState       { };
    VulkanPipelineColorBlendStateCreateInfo     colorBlendStateCreateInfo       { };
    // dynamic state here ..., nullptr for now

    VulkanGraphicsPipelineCreateInfo            createInfo                      { };

    populateVertexInputStateCreateInfo          ( & vertexInputStateCreateInfo );
    populateInputAssemblyStateCreateInfo        ( & inputAssemblyStateCreateInfo );
    populateViewportStructure                   ( & viewport,0.0f, 0.0f, (float) extent.width, (float) extent.height );
    populateScissorStructure                    ( & scissor,0,0, extent );
    populateViewportStateCreateInfo             ( & viewportStateCreateInfo, & viewport, 1U, & scissor, 1U );
    populateRasterizationStateCreateInfo        ( & rasterizationStateCreateInfo );
    populateMultisampleStateCreateInfo          ( & multisampleStateCreateInfo );
    populateColorBlendAttachmentStateEnabled    ( & colorBlendAttachmentState );
    populateColorBlendStateCreateInfo           ( & colorBlendStateCreateInfo, & colorBlendAttachmentState );
    // dynamic state populate call here

    populateGraphicsPipelineCreateInfo(
            & createInfo,
            pShaderStages,
            shaderStageCount,
            & vertexInputStateCreateInfo,
            & inputAssemblyStateCreateInfo,
            & viewportStateCreateInfo,
            & rasterizationStateCreateInfo,
            & multisampleStateCreateInfo,
            nullptr,
            & colorBlendStateCreateInfo,
            nullptr,
            this->_layoutHandle,
            & this->_renderPass,
            0U
    );

    VulkanResult createPipelineResult = vkCreateGraphicsPipelines(
            this->_pLogicalDevice->data(),
            VK_NULL_HANDLE,
            1U,
            & createInfo,
            nullptr,
            & this->_handle
    );

    return createPipelineResult;
}

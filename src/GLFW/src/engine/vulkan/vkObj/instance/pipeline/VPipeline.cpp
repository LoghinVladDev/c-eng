//
// Created by Vlad on 19/08/2020.
//

#include "VPipeline.h"

inline static void populateVertexInputStateCreateInfo (
    VulkanPipelineVertexInputStateCreateInfo * createInfo
) noexcept {
    if ( createInfo == nullptr )
        return;

    * createInfo = VulkanPipelineVertexInputStateCreateInfo {
        .sType                              = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
        .vertexBindingDescriptionCount      = 0,
        .pVertexBindingDescriptions         = nullptr,
        .vertexAttributeDescriptionCount    = 0,
        .pVertexAttributeDescriptions       = nullptr
    };
}

inline static void populateInputAssemblyStateCreateInfo (
    VulkanPipelineInputAssemblyStateCreateInfo * createInfo
) noexcept {
    if ( createInfo == nullptr )
        return;

    * createInfo = VulkanPipelineInputAssemblyStateCreateInfo {
        .sType                  = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
        .topology               = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
        .primitiveRestartEnable = VK_FALSE
    };
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

    * viewport = VulkanViewport {
        .x          = x,
        .y          = y,
        .width      = width,
        .height     = height,
        .minDepth   = 0.0f,
        .maxDepth   = 1.0f
    };
}

inline static void populateScissorStructure (
    VulkanRectangle2D * scissor,
    int32 xOffset,
    int32 yOffset,
    const VulkanExtent2D & extent
) noexcept {
    if( scissor == nullptr )
        return;

    * scissor = VulkanRectangle2D {
        .offset = { xOffset, yOffset },
        .extent = extent
    };
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

    * createInfo = VulkanPipelineViewportStateCreateInfo {
        .sType          = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
        .viewportCount  = viewportCount,
        .pViewports     = pViewports,
        .scissorCount   = scissorCount,
        .pScissors      = pScissors
    };
}

inline static void populateRasterizationStateCreateInfo (
    VulkanPipelineRasterizationStateCreateInfo * createInfo
) noexcept {
    if ( createInfo == nullptr )
        return;

    * createInfo = VulkanPipelineRasterizationStateCreateInfo {
        .sType                      = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
        .depthClampEnable           = VK_FALSE,
        .rasterizerDiscardEnable    = VK_FALSE,
        .polygonMode                = VK_POLYGON_MODE_FILL,
        .cullMode                   = VK_CULL_MODE_BACK_BIT,
        .frontFace                  = VK_FRONT_FACE_CLOCKWISE,
        .depthBiasEnable            = VK_FALSE,
        .depthBiasConstantFactor    = 0.0f,
        .depthBiasClamp             = 0.0f,
        .depthBiasSlopeFactor       = 0.0f,
        .lineWidth                  = 1.0f
    };
}

inline static void populateMultisampleStateCreateInfo (
    VulkanPipelineMultisampleStateCreateInfo * createInfo
) noexcept {
    if ( createInfo == nullptr )
        return;

    * createInfo = VulkanPipelineMultisampleStateCreateInfo {
        .sType                  = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
        .rasterizationSamples   = VK_SAMPLE_COUNT_1_BIT,
        .sampleShadingEnable    = VK_FALSE,
        .minSampleShading       = 1.0f,
        .pSampleMask            = nullptr,
        .alphaToCoverageEnable  = VK_FALSE,
        .alphaToOneEnable       = VK_FALSE
    };
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

    * colorBlendAttachment = VulkanPipelineColorBlendAttachmentState {
        .blendEnable    = VK_FALSE,
        .colorWriteMask = COLOR_WRITE_MASK
    };
}

inline static void populateColorBlendAttachmentStateEnabled (
    VulkanPipelineColorBlendAttachmentState * colorBlendAttachment
) noexcept {
    if ( colorBlendAttachment == nullptr )
        return;

    * colorBlendAttachment = VulkanPipelineColorBlendAttachmentState {
        .blendEnable            = VK_TRUE,
        .srcColorBlendFactor    = VK_BLEND_FACTOR_SRC_ALPHA,
        .dstColorBlendFactor    = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
        .colorBlendOp           = VK_BLEND_OP_ADD,
        .srcAlphaBlendFactor    = VK_BLEND_FACTOR_ONE,
        .dstAlphaBlendFactor    = VK_BLEND_FACTOR_ZERO,
        .alphaBlendOp           = VK_BLEND_OP_ADD
    };
}

inline static void populateColorBlendStateCreateInfo (
    VulkanPipelineColorBlendStateCreateInfo * createInfo,
    VulkanPipelineColorBlendAttachmentState * pAttachments,
    uint32                                    attachmentCount
) noexcept {
    if ( createInfo == nullptr || pAttachments == nullptr )
        return;

    * createInfo = VulkanPipelineColorBlendStateCreateInfo {
        .sType              = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
        .logicOpEnable      = static_cast<VkBool32>(( ( pAttachments->blendEnable == VK_TRUE ) ? ( VK_FALSE ) : ( VK_TRUE ) )),
        .logicOp            = VK_LOGIC_OP_COPY,
        .attachmentCount    = attachmentCount,
        .pAttachments       = pAttachments,
        .blendConstants     = { 0.0f, 0.0f, 0.0f, 0.0f }
    };
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

    * createInfo = VulkanGraphicsPipelineCreateInfo {
        .sType                  = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
        .stageCount             = shaderStageCount,
        .pStages                = pShaderStages,
        .pVertexInputState      = pVertexInputState,
        .pInputAssemblyState    = pInputAssemblyState,
        .pViewportState         = pViewportState,
        .pRasterizationState    = pRasterizerState,
        .pMultisampleState      = pMultisampleState,
        .pDepthStencilState     = pDepthStencilState,
        .pColorBlendState       = pColorBlendState,
        .pDynamicState          = pDynamicState,
        .layout                 = layout,
        .renderPass             = pRenderPass->data(),
        .subpass                = subpass,
        .basePipelineHandle     = ( pBasePipeline == nullptr ? nullptr : pBasePipeline->data() ) ,
        .basePipelineIndex      = basePipelineIndex
    };
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

    auto extent = this->_pLogicalDevice->getSwapChain()->getImagesInfo().extent;

    VulkanPipelineLayoutCreateInfo              layoutCreateInfo                { };

    populateLayoutCreateInfo ( & layoutCreateInfo );

    VulkanResult createLayoutResult = vkCreatePipelineLayout( this->_pLogicalDevice->data(), & layoutCreateInfo, nullptr, & this->_layoutHandle );

    if( createLayoutResult != VK_SUCCESS )
        return createLayoutResult;

    this->createRenderPass();

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
    populateColorBlendAttachmentStateDisabled   ( & colorBlendAttachmentState ); /// enabled doesn't work for now
    populateColorBlendStateCreateInfo           ( & colorBlendStateCreateInfo, & colorBlendAttachmentState, 1U );
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

    return vkCreateGraphicsPipelines(
            this->_pLogicalDevice->data(),
            VK_NULL_HANDLE,
            1U,
            & createInfo,
            nullptr,
            & this->_handle
    );
}

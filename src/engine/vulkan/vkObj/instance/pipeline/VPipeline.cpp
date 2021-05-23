//
// Created by Vlad on 19/08/2020.
//

#include "VPipeline.hpp"

inline static auto populateVertexInputStateCreateInfo (
    VulkanPipelineVertexInputStateCreateInfo       * createInfo,
    VulkanVertexInputBindingDescription      const * pVertexBindingDescriptions       = nullptr,
    uint32                                           vertexBindingDescriptionCount    = 0U,
    VulkanVertexInputAttributeDescription    const * pVertexAttributeDescriptions     = nullptr,
    uint32                                           vertexAttributeDescriptionCount  = 0U
) noexcept -> void {
    if ( createInfo == nullptr )
        return;

    * createInfo = VulkanPipelineVertexInputStateCreateInfo {
        .sType                              = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
        .pNext                              = nullptr,
        .flags                              = VULKAN_NULL_FLAGS,
        .vertexBindingDescriptionCount      = vertexBindingDescriptionCount,
        .pVertexBindingDescriptions         = pVertexBindingDescriptions,
        .vertexAttributeDescriptionCount    = vertexAttributeDescriptionCount,
        .pVertexAttributeDescriptions       = pVertexAttributeDescriptions
    };
}

inline static auto populateInputAssemblyStateCreateInfo (
    VulkanPipelineInputAssemblyStateCreateInfo * createInfo
) noexcept -> void {
    if ( createInfo == nullptr )
        return;

    * createInfo = VulkanPipelineInputAssemblyStateCreateInfo {
        .sType                  = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
        .pNext                  = nullptr,
        .flags                  = VULKAN_NULL_FLAGS,
        .topology               = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
        .primitiveRestartEnable = VK_FALSE
    };
}

inline static auto populateViewportStructure (
    VulkanViewport * viewport,
    float x,
    float y,
    float width,
    float height
) noexcept -> void {
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

inline static auto populateScissorStructure (
    VulkanRectangle2D * scissor,
    sint32 xOffset,
    sint32 yOffset,
    VulkanExtent2D const & extent
) noexcept -> void {
    if( scissor == nullptr )
        return;

    * scissor = VulkanRectangle2D {
        .offset = { xOffset, yOffset },
        .extent = extent
    };
}

inline static auto populateViewportStateCreateInfo (
    VulkanPipelineViewportStateCreateInfo         * createInfo,
    VulkanViewport                          const * pViewports,
    uint32                                          viewportCount,
    VulkanRectangle2D                       const * pScissors,
    uint32                                          scissorCount
) noexcept -> void {
    if ( createInfo == nullptr )
        return;

    * createInfo = VulkanPipelineViewportStateCreateInfo {
        .sType          = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
        .pNext          = nullptr,
        .flags          = VULKAN_NULL_FLAGS,
        .viewportCount  = viewportCount,
        .pViewports     = pViewports,
        .scissorCount   = scissorCount,
        .pScissors      = pScissors
    };
}

inline static auto populateRasterizationStateCreateInfo (
    VulkanPipelineRasterizationStateCreateInfo * createInfo
) noexcept -> void {
    if ( createInfo == nullptr )
        return;

    * createInfo = VulkanPipelineRasterizationStateCreateInfo {
        .sType                      = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
        .pNext                      = nullptr,
        .flags                      = VULKAN_NULL_FLAGS,
        .depthClampEnable           = VK_FALSE,
        .rasterizerDiscardEnable    = VK_FALSE,
        .polygonMode                = VK_POLYGON_MODE_FILL,
        .cullMode                   = VK_CULL_MODE_BACK_BIT,
//        .frontFace                  = VK_FRONT_FACE_CLOCKWISE,
        .frontFace                  = VK_FRONT_FACE_COUNTER_CLOCKWISE, //openGL used -1 for y axis in 3d, here we flip to account for GLM library automatically flipping when glm1::lookAt is called
        .depthBiasEnable            = VK_FALSE,
        .depthBiasConstantFactor    = 0.0f,
        .depthBiasClamp             = 0.0f,
        .depthBiasSlopeFactor       = 0.0f,
        .lineWidth                  = 1.0f
    };
}

inline static auto populateMultisampleStateCreateInfo (
    VulkanPipelineMultisampleStateCreateInfo * createInfo
) noexcept -> void {
    if ( createInfo == nullptr )
        return;

    * createInfo = VulkanPipelineMultisampleStateCreateInfo {
        .sType                  = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
        .pNext                  = nullptr,
        .flags                  = VULKAN_NULL_FLAGS,
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

inline static auto populateColorBlendAttachmentStateDisabled (
        VulkanPipelineColorBlendAttachmentState * colorBlendAttachment
) noexcept -> void {
    if ( colorBlendAttachment == nullptr )
        return;

    * colorBlendAttachment = VulkanPipelineColorBlendAttachmentState {
        .blendEnable            = VK_FALSE,
        .srcColorBlendFactor    = VulkanBlendFactor::VK_BLEND_FACTOR_ONE,
        .dstColorBlendFactor    = VulkanBlendFactor::VK_BLEND_FACTOR_ZERO,
        .colorBlendOp           = VulkanBlendOperation::VK_BLEND_OP_ADD,
        .srcAlphaBlendFactor    = VulkanBlendFactor::VK_BLEND_FACTOR_ONE,
        .dstAlphaBlendFactor    = VulkanBlendFactor::VK_BLEND_FACTOR_ZERO,
        .alphaBlendOp           = VulkanBlendOperation::VK_BLEND_OP_ADD,
        .colorWriteMask         = COLOR_WRITE_MASK
    };
}

inline static auto populateColorBlendAttachmentStateEnabled (
    VulkanPipelineColorBlendAttachmentState * colorBlendAttachment
) noexcept -> void {
    if ( colorBlendAttachment == nullptr )
        return;

    * colorBlendAttachment = VulkanPipelineColorBlendAttachmentState {
        .blendEnable            = VK_TRUE,
        .srcColorBlendFactor    = VK_BLEND_FACTOR_SRC_ALPHA,
        .dstColorBlendFactor    = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
        .colorBlendOp           = VK_BLEND_OP_ADD,
        .srcAlphaBlendFactor    = VK_BLEND_FACTOR_ONE,
        .dstAlphaBlendFactor    = VK_BLEND_FACTOR_ZERO,
        .alphaBlendOp           = VK_BLEND_OP_ADD,
        .colorWriteMask         = COLOR_WRITE_MASK
    };
}

inline static auto populateColorBlendStateCreateInfo (
    VulkanPipelineColorBlendStateCreateInfo       * createInfo,
    VulkanPipelineColorBlendAttachmentState const * pAttachments,
    uint32                                          attachmentCount
) noexcept -> void {
    if ( createInfo == nullptr || pAttachments == nullptr )
        return;

    * createInfo = VulkanPipelineColorBlendStateCreateInfo {
        .sType              = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
        .pNext              = nullptr,
        .flags              = VULKAN_NULL_FLAGS,
        .logicOpEnable      = static_cast<VkBool32>(( ( pAttachments->blendEnable == VK_TRUE ) ? ( VK_FALSE ) : ( VK_TRUE ) )),
        .logicOp            = VK_LOGIC_OP_COPY,
        .attachmentCount    = attachmentCount,
        .pAttachments       = pAttachments,
        .blendConstants     = { 0.0f, 0.0f, 0.0f, 0.0f }
    };
}

[[maybe_unused]] inline static auto populateDynamicStateCreateInfo (
    VulkanPipelineDynamicStateCreateInfo * createInfo,
    VulkanDynamicState             const * pDynamicStates,
    uint32                                 dynamicStateCount
) noexcept -> void {
    if ( createInfo == nullptr )
        return;

    * createInfo = VulkanPipelineDynamicStateCreateInfo {
        .sType              = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
        .pNext              = nullptr,
        .flags              = VULKAN_NULL_FLAGS,
        .dynamicStateCount  = dynamicStateCount,
        .pDynamicStates     = pDynamicStates
    };

//    createInfo->sType               = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
//    createInfo->dynamicStateCount   = dynamicStateCount;
//    createInfo->pDynamicStates      = pDynamicStates;
}

inline static auto populateLayoutCreateInfo (
    VulkanPipelineLayoutCreateInfo  * createInfo,
    VulkanDescriptorSetLayout const * pSetLayouts,
    uint32                            setLayoutCount
) noexcept -> void {
    if ( createInfo == nullptr )
        return;

    * createInfo = VulkanPipelineLayoutCreateInfo {
        .sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        .pNext                  = nullptr,
        .flags                  = VULKAN_NULL_FLAGS,
        .setLayoutCount         = setLayoutCount,
        .pSetLayouts            = pSetLayouts,
        .pushConstantRangeCount = 0U,
        .pPushConstantRanges    = nullptr
    };
}

inline static auto populateDepthStencilCreateInfo (
    VulkanPipelineDepthStencilStateCreateInfo * pCreateInfo
) noexcept -> void {
    if ( pCreateInfo == nullptr )
        return;

    * pCreateInfo = VulkanPipelineDepthStencilStateCreateInfo {
        .sType                  = VulkanStructureType::VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
        .pNext                  = nullptr,
        .flags                  = static_cast < VulkanPipelineDepthStencilStateCreateFlags > (0U),
        .depthTestEnable        = VK_TRUE,
        .depthWriteEnable       = VK_TRUE,
        .depthCompareOp         = VulkanCompareOp::VK_COMPARE_OP_LESS,
        .depthBoundsTestEnable  = VK_FALSE,
        .stencilTestEnable      = VK_FALSE,
        .front                  = VulkanStencilOpState {
            .failOp                 = VulkanStencilOp::VK_STENCIL_OP_KEEP,
            .passOp                 = VulkanStencilOp::VK_STENCIL_OP_KEEP,
            .depthFailOp            = VulkanStencilOp::VK_STENCIL_OP_KEEP,
            .compareOp              = VulkanCompareOp::VK_COMPARE_OP_NEVER,
            .compareMask            = 0U,
            .writeMask              = 0U,
            .reference              = 0U
        },
        .back                   = VulkanStencilOpState {
            .failOp                 = VulkanStencilOp::VK_STENCIL_OP_KEEP,
            .passOp                 = VulkanStencilOp::VK_STENCIL_OP_KEEP,
            .depthFailOp            = VulkanStencilOp::VK_STENCIL_OP_KEEP,
            .compareOp              = VulkanCompareOp::VK_COMPARE_OP_NEVER,
            .compareMask            = 0U,
            .writeMask              = 0U,
            .reference              = 0U
        },
        .minDepthBounds         = 0.0f,
        .maxDepthBounds         = 1.0f
    };
}

inline static auto populateGraphicsPipelineCreateInfo (
    VulkanGraphicsPipelineCreateInfo                    * createInfo,
    VulkanPipelineShaderStageCreateInfo           const * pShaderStages,
    uint32                                                shaderStageCount,
    VulkanPipelineVertexInputStateCreateInfo      const * pVertexInputState,
    VulkanPipelineInputAssemblyStateCreateInfo    const * pInputAssemblyState,
    VulkanPipelineViewportStateCreateInfo         const * pViewportState,
    VulkanPipelineRasterizationStateCreateInfo    const * pRasterizerState,
    VulkanPipelineMultisampleStateCreateInfo      const * pMultisampleState,
    VulkanPipelineDepthStencilStateCreateInfo     const * pDepthStencilState,
    VulkanPipelineColorBlendStateCreateInfo       const * pColorBlendState,
    VulkanPipelineDynamicStateCreateInfo          const * pDynamicState,
    VulkanPipelineLayout                                  layout,
    engine::VRenderPass                           const * pRenderPass,
    uint32                                                subpass,
    engine::VPipeline                             const * pBasePipeline         = nullptr,
    sint32                                                basePipelineIndex     = -1
) noexcept -> void {
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
        .pNext                  = nullptr,
        .flags                  = VULKAN_NULL_FLAGS,
        .stageCount             = shaderStageCount,
        .pStages                = pShaderStages,
        .pVertexInputState      = pVertexInputState,
        .pInputAssemblyState    = pInputAssemblyState,
        .pTessellationState     = nullptr,
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
        .basePipelineIndex      = basePipelineIndex,
    };
}

auto engine::VPipeline::createRenderPass() noexcept (false) -> void {
    VulkanSubpassDependency waitForImageSubpassDependency {
        .srcSubpass         = VK_SUBPASS_EXTERNAL,
        .dstSubpass         = VULKAN_NULL_FLAGS,
        .srcStageMask       = VulkanPipelineStageFlagBits::VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
        .dstStageMask       = VulkanPipelineStageFlagBits::VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
        .srcAccessMask      = VULKAN_NULL_FLAGS,
        .dstAccessMask      = VulkanAccessFlagBits::VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
        .dependencyFlags    = VULKAN_NULL_FLAGS,
    };

    if ( this->_renderPass.setup( * this->_pLogicalDevice, & waitForImageSubpassDependency, 1U ) != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ("render pass creation failure");
}

auto engine::VPipeline::clear() noexcept -> void {
    if ( this->_handle != nullptr )
        vkDestroyPipeline ( this->_pLogicalDevice->data(), this->_handle, nullptr );
    this->_renderPass.clear();
    if ( this->_layoutHandle == nullptr )
        return;
    vkDestroyPipelineLayout( this->_pLogicalDevice->data(), this->_layoutHandle, nullptr );

    this->_layoutHandle = VK_NULL_HANDLE;
    this->_handle = VK_NULL_HANDLE;
    this->_pLogicalDevice = nullptr;
}

auto engine::VPipeline::setup(
    engine::VLogicalDevice                  const & device,
    VulkanPipelineShaderStageCreateInfo     const * pShaderStages,
    uint32                                          shaderStageCount,
    VulkanVertexInputBindingDescription     const * pBindingDescriptions,
    uint32                                          bindingDescriptionCount,
    VulkanVertexInputAttributeDescription   const * pAttributeDescriptions,
    uint32                                          attributeDescriptionCount,
    VulkanDescriptorSetLayout               const * pDescriptorSetLayouts,
    uint32                                          descriptorSetLayoutCount
) noexcept(false) -> VulkanResult {
    this->_pLogicalDevice = & device;

    auto extent = this->_pLogicalDevice->getSwapChain()->getImagesInfo().extent;

    VulkanPipelineLayoutCreateInfo              layoutCreateInfo                { };

    populateLayoutCreateInfo ( & layoutCreateInfo, pDescriptorSetLayouts, descriptorSetLayoutCount );

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
    VulkanPipelineDepthStencilStateCreateInfo   depthStencilStateCreateInfo     { };
    // dynamic state here ..., nullptr for now

    VulkanGraphicsPipelineCreateInfo            createInfo                      { };

    populateVertexInputStateCreateInfo          ( & vertexInputStateCreateInfo, pBindingDescriptions, bindingDescriptionCount, pAttributeDescriptions, attributeDescriptionCount );
    populateInputAssemblyStateCreateInfo        ( & inputAssemblyStateCreateInfo );
    populateViewportStructure                   ( & viewport,0.0f, 0.0f, (float) extent.width, (float) extent.height );
    populateScissorStructure                    ( & scissor,0,0, extent );
    populateViewportStateCreateInfo             ( & viewportStateCreateInfo, & viewport, 1U, & scissor, 1U );
    populateRasterizationStateCreateInfo        ( & rasterizationStateCreateInfo );
    populateMultisampleStateCreateInfo          ( & multisampleStateCreateInfo );
    populateColorBlendAttachmentStateDisabled   ( & colorBlendAttachmentState ); /// enabled doesn't work for now
    populateColorBlendStateCreateInfo           ( & colorBlendStateCreateInfo, & colorBlendAttachmentState, 1U );
    populateDepthStencilCreateInfo              ( & depthStencilStateCreateInfo );
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
            & depthStencilStateCreateInfo,
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

#include <sstream>

auto engine::VPipeline::toString() const noexcept -> String {
    std::stringstream oss;

    oss << "VPipeline { " <<
           "handle = 0x" << std::hex << reinterpret_cast < AddressValueType > ( this->_handle ) <<
           ", layoutHandle = 0x" << reinterpret_cast < AddressValueType > ( this->_layoutHandle ) <<
           ", pLogicalDevice = 0x" << reinterpret_cast < AddressValueType > ( this->_pLogicalDevice ) <<
           ", renderPass = " << this->_renderPass.toString() + " }";

    return oss.str();
}
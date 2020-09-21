//
// Created by Vlad on 19/08/2020.
//

#include "VRenderPass.h"

extern VulkanFormat getDepthFormat (const engine::VPhysicalDevice * pPhysicalDevice) noexcept;

static inline void populateAttachmentDescription (
    VulkanAttachmentDescription     * colorAttachment,
    const engine::VSwapChain        * swapChain
) noexcept {
    if( colorAttachment == nullptr || swapChain == nullptr )
        return;

    * colorAttachment = { };

    colorAttachment->format         = swapChain->getImagesInfo().format;
    colorAttachment->samples        = VK_SAMPLE_COUNT_1_BIT;

    colorAttachment->loadOp         = VK_ATTACHMENT_LOAD_OP_CLEAR;
    colorAttachment->storeOp        = VK_ATTACHMENT_STORE_OP_STORE;
    colorAttachment->stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachment->stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    colorAttachment->initialLayout  = VK_IMAGE_LAYOUT_UNDEFINED;
    colorAttachment->finalLayout    = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
}

static inline void populateDepthBufferAttachmentDescription (
    VulkanAttachmentDescription     * pDepthAttachment,
    VulkanFormat                      format
) noexcept {
    if ( pDepthAttachment == nullptr )
        return;

    * pDepthAttachment = VulkanAttachmentDescription {
        .flags          = static_cast < VulkanAttachmentDescriptionFlags > (0U),
        .format         = format,
        .samples        = VulkanSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT,
        .loadOp         = VulkanAttachmentLoadOp::VK_ATTACHMENT_LOAD_OP_CLEAR,
        .storeOp        = VulkanAttachmentStoreOp::VK_ATTACHMENT_STORE_OP_DONT_CARE,
        .stencilLoadOp  = VulkanAttachmentLoadOp::VK_ATTACHMENT_LOAD_OP_DONT_CARE,
        .stencilStoreOp = VulkanAttachmentStoreOp::VK_ATTACHMENT_STORE_OP_DONT_CARE,
        .initialLayout  = VulkanImageLayout::VK_IMAGE_LAYOUT_UNDEFINED,
        .finalLayout    = VulkanImageLayout::VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
    };
}

static inline void populateAttachmentReference (
    VulkanAttachmentReference       * attachmentRef,
    uint32                            attachmentIndex,
    VulkanImageLayout                 imageLayout = VulkanImageLayout::VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
) noexcept {
    if ( attachmentRef == nullptr )
        return;

    * attachmentRef = VulkanAttachmentReference {
        .attachment = attachmentIndex,
        .layout     = imageLayout
    };
}

static inline void populateSubpassDescription (
    VulkanSubpassDescription        * subpass,
    const VulkanAttachmentReference * pColorAttachmentRefs,
    uint32                            colorAttachmentCount,
    const VulkanAttachmentReference * pDepthAttachmentRef = nullptr
) noexcept {
    if ( subpass == nullptr )
        return;

    * subpass = {
        .flags                      = static_cast < VulkanSubpassDescriptionFlags > ( 0U ),
        .pipelineBindPoint          = VulkanPipelineBindPoint::VK_PIPELINE_BIND_POINT_GRAPHICS,
        .inputAttachmentCount       = 0U,
        .pInputAttachments          = nullptr,
        .colorAttachmentCount       = colorAttachmentCount,
        .pColorAttachments          = pColorAttachmentRefs,
        .pResolveAttachments        = nullptr,
        .pDepthStencilAttachment    = pDepthAttachmentRef,
        .preserveAttachmentCount    = 0U,
        .pPreserveAttachments       = nullptr
    };
}

static inline void populateRenderPassCreateInfo (
    VulkanRenderPassCreateInfo          * createInfo,
    const VulkanAttachmentDescription   * pAttachments,
    uint32                                attachmentCount,
    const VulkanSubpassDescription      * pSubpasses,
    uint32                                subpassCount,
    const VulkanSubpassDependency       * pSubpassDependencies,
    uint32                                subpassDependencyCount
) noexcept {
    if ( createInfo == nullptr )
        return;

    * createInfo = { };

    createInfo->sType               = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    createInfo->attachmentCount     = attachmentCount;
    createInfo->subpassCount        = subpassCount;
    createInfo->pAttachments        = pAttachments;
    createInfo->pSubpasses          = pSubpasses;
    createInfo->dependencyCount     = subpassDependencyCount;
    createInfo->pDependencies       = pSubpassDependencies;
}

VulkanResult engine::VRenderPass::setup(
    const engine::VLogicalDevice & device,
    const VulkanSubpassDependency * pSubpassDependencies,
    uint32 subpassDependencyCount
) noexcept(false) {
    VulkanAttachmentDescription colorAttachmentDescription  { };
    VulkanAttachmentReference   colorAttachmentReference    { };
    VulkanSubpassDescription    subpassDescription          { };
    VulkanRenderPassCreateInfo  createInfo                  { };

    VulkanAttachmentDescription depthAttachmentDescription  { };
    VulkanAttachmentReference   depthAttachmentReference    { };

    this->_pLogicalDevice = & device;

    if ( this->_pLogicalDevice->getSwapChain() == nullptr )
        throw engine::EngineVRenderPassDeviceInvalidSwapChain();

    populateAttachmentDescription   ( & colorAttachmentDescription, this->_pLogicalDevice->getSwapChain() );
    populateAttachmentReference     ( & colorAttachmentReference, 0U );

    populateDepthBufferAttachmentDescription ( & depthAttachmentDescription, getDepthFormat( this->_pLogicalDevice->getBasePhysicalDevice() ) );
    populateAttachmentReference     ( & depthAttachmentReference, 1U, VulkanImageLayout::VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL );

    populateSubpassDescription      ( & subpassDescription, & colorAttachmentReference, 1U, & depthAttachmentReference );

    std::array < VulkanAttachmentDescription, 2 > attachmentDescriptions {
        colorAttachmentDescription,
        depthAttachmentDescription
    };

    populateRenderPassCreateInfo    (
        & createInfo,
        attachmentDescriptions.data(),
        static_cast < uint32 > ( attachmentDescriptions.size() ),
        & subpassDescription,
        1U,
        pSubpassDependencies,
        subpassDependencyCount
    );

    return vkCreateRenderPass( this->_pLogicalDevice->data(), & createInfo, nullptr, & this->_handle );
}

void engine::VRenderPass::cleanup () noexcept {
    if( this->_handle == nullptr )
        return;
    vkDestroyRenderPass( this->_pLogicalDevice->data(), this->_handle, nullptr );
    this->_handle = VK_NULL_HANDLE;
}

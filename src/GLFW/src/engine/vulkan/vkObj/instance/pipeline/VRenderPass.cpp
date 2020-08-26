//
// Created by Vlad on 19/08/2020.
//

#include "VRenderPass.h"

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

static inline void populateAttachmentReference (
    VulkanAttachmentReference       * colorAttachmentRef,
    uint32                            colorAttachmentIndex
) noexcept {
    if ( colorAttachmentRef == nullptr )
        return;

    * colorAttachmentRef = { };

    colorAttachmentRef->attachment  = colorAttachmentIndex;
    colorAttachmentRef->layout      = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
}

static inline void populateSubpassDescription (
    VulkanSubpassDescription        * subpass,
    const VulkanAttachmentReference * pAttachmentRefs,
    uint32                            attachmentRefCount
) noexcept {
    if ( subpass == nullptr )
        return;

    * subpass = { };

    subpass->pipelineBindPoint      = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass->colorAttachmentCount   = attachmentRefCount;
    subpass->pColorAttachments      = pAttachmentRefs;
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

    this->_pLogicalDevice = & device;

    if ( this->_pLogicalDevice->getSwapChain() == nullptr )
        throw engine::EngineVRenderPassDeviceInvalidSwapChain();

    populateAttachmentDescription   ( & colorAttachmentDescription, this->_pLogicalDevice->getSwapChain() );
    populateAttachmentReference     ( & colorAttachmentReference, 0U );
    populateSubpassDescription      ( & subpassDescription, & colorAttachmentReference, 1U );
    populateRenderPassCreateInfo    (
        & createInfo,
        & colorAttachmentDescription,
        1U,
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

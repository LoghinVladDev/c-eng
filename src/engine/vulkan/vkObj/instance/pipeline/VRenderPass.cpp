//
// Created by Vlad on 19/08/2020.
//

#include "VRenderPass.hpp"

extern VulkanFormat getDepthFormat (engine::VPhysicalDevice const * pPhysicalDevice) noexcept;

#include <VSwapChain.hpp>
static inline auto populateAttachmentDescription (
    VulkanAttachmentDescription     * colorAttachment,
    engine::VSwapChain        const * swapChain
) noexcept -> void {
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

static inline auto populateDepthBufferAttachmentDescription (
    VulkanAttachmentDescription     * pDepthAttachment,
    VulkanFormat                      format
) noexcept -> void {
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

static inline auto populateAttachmentReference (
    VulkanAttachmentReference       * attachmentRef,
    uint32                            attachmentIndex,
    VulkanImageLayout                 imageLayout = VulkanImageLayout::VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
) noexcept -> void {
    if ( attachmentRef == nullptr )
        return;

    * attachmentRef = VulkanAttachmentReference {
        .attachment = attachmentIndex,
        .layout     = imageLayout
    };
}

static inline auto populateSubpassDescription (
    VulkanSubpassDescription        * subpass,
    VulkanAttachmentReference const * pColorAttachmentRefs,
    uint32                            colorAttachmentCount,
    VulkanAttachmentReference const * pDepthAttachmentRef = nullptr
) noexcept -> void {
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

static inline auto populateRenderPassCreateInfo (
    VulkanRenderPassCreateInfo          * createInfo,
    VulkanAttachmentDescription   const * pAttachments,
    uint32                                attachmentCount,
    VulkanSubpassDescription      const * pSubpasses,
    uint32                                subpassCount,
    VulkanSubpassDependency       const * pSubpassDependencies,
    uint32                                subpassDependencyCount
) noexcept -> void {
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

#include <array>
auto engine::VRenderPass::setup(
    engine::VLogicalDevice  const & device,
    VulkanSubpassDependency const * pSubpassDependencies,
    uint32                          subpassDependencyCount
) noexcept(false) -> VulkanResult {
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

auto engine::VRenderPass::clear () noexcept -> void {
    if( this->_handle == nullptr )
        return;
    vkDestroyRenderPass( this->_pLogicalDevice->data(), this->_handle, nullptr );
    this->_handle = VK_NULL_HANDLE;
}

#include <sstream>

auto engine::VRenderPass::toString () const noexcept -> String {
    std::stringstream oss;
    oss << "VRenderPass { " <<
           "handle = 0x" << std::hex << reinterpret_cast< AddressValueType >(this->_handle) <<
           ", pLogicalDevice = 0x" << reinterpret_cast < AddressValueType > (this->_pLogicalDevice) << " }";

    return oss.str();
}
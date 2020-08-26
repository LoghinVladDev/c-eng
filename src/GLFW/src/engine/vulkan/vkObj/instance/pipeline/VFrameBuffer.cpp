//
// Created by Vlad on 19/08/2020.
//

#include "VFrameBuffer.h"

inline static void populateFrameBufferCreateInfo (
    VulkanFrameBufferCreateInfo * createInfo,
    const engine::VRenderPass   * pRenderPass,
    const VulkanImageView       * pAttachments,
    uint32                        attachmentCount
) noexcept {
    if ( createInfo == nullptr || pRenderPass == nullptr || pAttachments == nullptr )
        return;

    * createInfo = { };

    createInfo->sType               = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    createInfo->renderPass          = pRenderPass->data();
    createInfo->attachmentCount     = attachmentCount;
    createInfo->pAttachments        = pAttachments;
    createInfo->width               = pRenderPass->getLogicalDevicePtr()->getSwapChain()->getImagesInfo().extent.width;
    createInfo->height              = pRenderPass->getLogicalDevicePtr()->getSwapChain()->getImagesInfo().extent.height;
    createInfo->layers              = 1U;
}

VulkanResult engine::VFrameBufferCollection::setup(const engine::VRenderPass * pRenderPass) noexcept (false) {
    if( pRenderPass == nullptr )
        throw engine::EngineVFrameBufferInvalidRenderPass();

    this->_frameBuffers.clear();
    for ( const auto & imageView : pRenderPass->getLogicalDevicePtr()->getImageViewCollection()->getImageViews() ) {
        this->_frameBuffers.emplace_back( imageView, pRenderPass );

        if ( this->_frameBuffers.back().setup() != VK_SUCCESS )
            throw std::runtime_error ("Frame Buffer Initialization Error");
    }

    return VulkanResult::VK_SUCCESS;
}

void engine::VFrameBufferCollection::cleanup() noexcept {
    for ( auto & frameBuffer : this->_frameBuffers )
        frameBuffer.cleanup();

    this->_frameBuffers.clear();
}

VulkanResult engine::VFrameBuffer::setup() noexcept {
    if ( this->_pImageView == nullptr || this->_pImageView == nullptr )
        return VulkanResult::VK_ERROR_INITIALIZATION_FAILED;

    VulkanFrameBufferCreateInfo createInfo { };

    populateFrameBufferCreateInfo( & createInfo, this->_pRenderPass, &(this->_pImageView->data()), 1U);

    return vkCreateFramebuffer( this->_pRenderPass->getLogicalDevicePtr()->data(), & createInfo, nullptr, & this->_handle );
}

void engine::VFrameBuffer::cleanup() noexcept {
    vkDestroyFramebuffer( this->_pRenderPass->getLogicalDevicePtr()->data(), this->_handle, nullptr );
    this->_handle       = VK_NULL_HANDLE;
    this->_pImageView   = nullptr;
    this->_pRenderPass  = nullptr;
}


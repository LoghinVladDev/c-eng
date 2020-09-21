//
// Created by Vlad on 17/08/2020.
//

#include "VImageView.h"

static inline void populateImageViewCreateInfo (
    VulkanImageViewCreateInfo * createInfo,
    VulkanImage                 image,
    VulkanFormat                imageFormat,
    VulkanImageAspectFlags      aspectMask
) noexcept {
    if( createInfo == nullptr )
        return;

    * createInfo = {};

    createInfo->sType                           = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    createInfo->image                           = image;
    createInfo->viewType                        = VK_IMAGE_VIEW_TYPE_2D;
    createInfo->format                          = imageFormat;

    createInfo->components.r                    = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo->components.g                    = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo->components.b                    = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo->components.a                    = VK_COMPONENT_SWIZZLE_IDENTITY;

    createInfo->subresourceRange.aspectMask     = aspectMask;
    createInfo->subresourceRange.baseMipLevel   = 0U;
    createInfo->subresourceRange.levelCount     = 1U;
    createInfo->subresourceRange.baseArrayLayer = 0U;
    createInfo->subresourceRange.layerCount     = 1U;
}

VulkanResult engine::VImageView::setup(VulkanImage image, VulkanFormat format, const VLogicalDevice & device, VulkanImageAspectFlags aspectFlags) noexcept {
    this->_pLogicalDevice = & device;

    VulkanImageViewCreateInfo createInfo {};

    populateImageViewCreateInfo( & createInfo, image, format, aspectFlags );

    return vkCreateImageView ( this->_pLogicalDevice->data(), & createInfo ,nullptr, & this->_handle );
}

VulkanResult engine::VImageViewCollection::setup(const engine::VSwapChain * swapChain) noexcept {
    this->_imageViews.resize( swapChain->getImages().size() );
    this->_pSwapChain = swapChain;

    uint32 index = 0;

    for( auto & imageView : this->_imageViews ) {
        VulkanResult returnValue = imageView.setup(swapChain->getImages()[index++], swapChain->getImagesInfo().format, * this->_pSwapChain->getDevice());
        if( returnValue != VulkanResult::VK_SUCCESS ) {
            for ( uint32 clearIndex = 0; clearIndex < index - 1; clearIndex++ )
                this->_imageViews[clearIndex].cleanup();
            return returnValue;
        }
    }

    return VulkanResult::VK_SUCCESS;
}

void engine::VImageViewCollection::cleanup() noexcept {
    for ( auto imageView : this->_imageViews )
        imageView.cleanup();
    this->_imageViews.clear();
    this->_pSwapChain = nullptr;
}

engine::VImageViewCollection::VImageViewCollection(const engine::VImageViewCollection * pObj,const engine::VSwapChain * pSwapChain) noexcept {
    this->_imageViews.clear();
    this->_pSwapChain = pSwapChain;

    for ( const auto & imageView : pObj->_imageViews )
        this->_imageViews.emplace_back ( & imageView, pSwapChain->getDevice() );
}

void engine::VImageView::cleanup() noexcept {
    if ( this->_handle != VK_NULL_HANDLE )
        vkDestroyImageView ( this->_pLogicalDevice->data(), this->_handle, nullptr );
}

engine::VImageView::VImageView(const engine::VImageView * pObj, const engine::VLogicalDevice * pLogicalDevice) noexcept {
    this->_handle           = pObj->_handle;
    this->_index            = pObj->_index;
    this->_pLogicalDevice   = pLogicalDevice;
}

[[nodiscard]] const engine::VSwapChain * engine::VImageView::getSwapChain() const noexcept {
    return this->_pLogicalDevice->getSwapChain();
}
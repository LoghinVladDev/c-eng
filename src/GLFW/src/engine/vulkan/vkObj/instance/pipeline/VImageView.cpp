//
// Created by Vlad on 17/08/2020.
//

#include "VImageView.h"

static inline void populateImageViewCreateInfo (
    VulkanImageViewCreateInfo * createInfo,
    const engine::VSwapChain * swapChain,
    uint32 imageIndex
) noexcept {
    if( createInfo == nullptr )
        return;

    * createInfo = {};

    createInfo->sType                           = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    createInfo->image                           = swapChain->getImages()[imageIndex];
    createInfo->viewType                        = VK_IMAGE_VIEW_TYPE_2D;
    createInfo->format                          = swapChain->getImagesInfo().format;

    createInfo->components.r                    = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo->components.g                    = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo->components.b                    = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo->components.a                    = VK_COMPONENT_SWIZZLE_IDENTITY;

    createInfo->subresourceRange.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
    createInfo->subresourceRange.baseMipLevel   = 0U;
    createInfo->subresourceRange.levelCount     = 1U;
    createInfo->subresourceRange.baseArrayLayer = 0U;
    createInfo->subresourceRange.layerCount     = 1U;
}

VulkanResult engine::VImageView::setup(const engine::VSwapChain * swapChain, uint32 index) noexcept {
    this->_pSwapChain = swapChain;

    VulkanImageViewCreateInfo createInfo {};

    populateImageViewCreateInfo( & createInfo, swapChain, index );

    return vkCreateImageView ( swapChain->getDevice()->data(), & createInfo ,nullptr, & this->_handle );
}

VulkanResult engine::VImageViewCollection::setup(const engine::VSwapChain * swapChain) noexcept {
    this->_imageViews.resize( swapChain->getImages().size() );

    uint32 index = 0;

    for( auto & imageView : this->_imageViews ) {
        VulkanResult returnValue = imageView.setup(swapChain, index++);
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
}

engine::VImageViewCollection::VImageViewCollection(const engine::VImageViewCollection * pObj,const engine::VSwapChain * pSwapChain) noexcept {
    this->_imageViews.clear();

    for ( const auto & imageView : pObj->_imageViews )
        this->_imageViews.emplace_back ( & imageView, pSwapChain );
}

void engine::VImageView::cleanup() noexcept {
    vkDestroyImageView ( this->_pSwapChain->getDevice()->data(), this->_handle, nullptr );
}

engine::VImageView::VImageView(const engine::VImageView * pObj, const engine::VSwapChain * pSwapChain) noexcept {
    this->_handle = pObj->_handle;
    this->_index  = pObj->_index;
    this->_pSwapChain = pSwapChain;
}

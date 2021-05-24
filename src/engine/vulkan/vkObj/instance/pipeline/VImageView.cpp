//
// Created by Vlad on 17/08/2020.
//

#include "VImageView.hpp"

static inline auto populateImageViewCreateInfo (
    VulkanImageViewCreateInfo * createInfo,
    VulkanImage                 image,
    VulkanFormat                imageFormat,
    VulkanImageAspectFlags      aspectMask
) noexcept -> void {
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

auto engine::VImageView::setup(VulkanImage image, VulkanFormat format, VLogicalDevice const & device, VulkanImageAspectFlags aspectFlags) noexcept -> VulkanResult {
    this->_pLogicalDevice = & device;

    VulkanImageViewCreateInfo createInfo {};

    populateImageViewCreateInfo( & createInfo, image, format, aspectFlags );

    return vkCreateImageView ( this->_pLogicalDevice->data(), & createInfo ,nullptr, & this->_handle );
}

#include <VSwapChain.hpp>
auto engine::VImageViewCollection::setup(engine::VSwapChain const * swapChain) noexcept -> VulkanResult {
    this->_imageViews.resize( swapChain->getImages().size() );
    this->_pSwapChain = swapChain;

    uint32 index = 0;

    for( auto & imageView : this->_imageViews ) {
        VulkanResult returnValue = imageView.setup(swapChain->getImages()[index++], swapChain->getImagesInfo().format, * this->_pSwapChain->getDevice());
        if( returnValue != VulkanResult::VK_SUCCESS ) {
            for ( uint32 clearIndex = 0; clearIndex < index - 1; clearIndex++ )
                this->_imageViews[clearIndex].clear();
            return returnValue;
        }
    }

    return VulkanResult::VK_SUCCESS;
}

auto engine::VImageViewCollection::clear() noexcept -> void {
    for ( auto imageView : this->_imageViews )
        imageView.clear();
    this->_imageViews.clear();
    this->_pSwapChain = nullptr;
}

engine::VImageViewCollection::VImageViewCollection(engine::VImageViewCollection const * pObj, engine::VSwapChain const * pSwapChain) noexcept : VRenderObject() {
    this->_imageViews.clear();
    this->_pSwapChain = pSwapChain;

    for ( const auto & imageView : pObj->_imageViews )
        this->_imageViews.emplace_back ( & imageView, pSwapChain->getDevice() );
}

auto engine::VImageView::clear () noexcept -> void {
    if ( this->_handle != VK_NULL_HANDLE )
        vkDestroyImageView ( this->_pLogicalDevice->data(), this->_handle, nullptr );
}

engine::VImageView::VImageView(engine::VImageView const * pObj, engine::VLogicalDevice const * pLogicalDevice) noexcept : VRenderObject() {
    this->_handle           = pObj->_handle;
    this->_index            = pObj->_index;
    this->_pLogicalDevice   = pLogicalDevice;
}

auto engine::VImageView::getSwapChain() const noexcept -> engine::VSwapChain const * {
    return this->_pLogicalDevice->getSwapChain();
}

#include <sstream>

auto engine::VImageViewCollection::toString() const noexcept -> String {
    std::stringstream oss;
    oss << "VImageViewCollection { imageViews = [ ";
    for (auto const & item : this->_imageViews)
        oss << item.toString() << ", ";
    auto s = oss.str();
    return s.substr(s.size() - 2).append(" ]}");
}

auto engine::VImageView::toString () const noexcept -> String {
    std::stringstream oss;
    oss << "VImageView { " <<
           "handle = 0x" << std::hex << reinterpret_cast < AddressValueType > (this->_handle) <<
           ", index = " << std::dec << this->_index <<
           ", pLogicalDevice = 0x" << std::hex << reinterpret_cast < AddressValueType > (this->_pLogicalDevice) << " }";
    return oss.str();
}
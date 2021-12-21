//
// Created by Vlad on 17/08/2020.
//

#include "VImageView.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

static inline auto populateImageViewCreateInfo (
    VulkanImageViewCreateInfo * createInfo,
    VulkanImage                 image,
    VulkanFormat                imageFormat,
    VulkanImageAspectFlags      aspectMask
) noexcept -> void {
    if( createInfo == nullptr ) {
        return;
    }

    * createInfo = {
            .sType                           = VulkanStructureType :: VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
            .image                           = image,
            .viewType                        = VulkanImageViewType :: VK_IMAGE_VIEW_TYPE_2D,
            .format                          = imageFormat,

            .components = ( VulkanComponentMapping ) {
                .r                              = VulkanComponentSwizzle :: VK_COMPONENT_SWIZZLE_IDENTITY,
                .g                              = VulkanComponentSwizzle :: VK_COMPONENT_SWIZZLE_IDENTITY,
                .b                              = VulkanComponentSwizzle :: VK_COMPONENT_SWIZZLE_IDENTITY,
                .a                              = VulkanComponentSwizzle :: VK_COMPONENT_SWIZZLE_IDENTITY
            },

            .subresourceRange = ( VulkanImageSubresourceRange ) {
                .aspectMask                     = aspectMask,
                .baseMipLevel                   = 0U,
                .levelCount                     = 1U,
                .baseArrayLayer                 = 0U,
                .layerCount                     = 1U
            }
    };
}

auto VImageView :: setup(
        VulkanImage                     image,
        VulkanFormat                    format,
        VLogicalDevice          const & device,
        VulkanImageAspectFlags          aspectFlags
) noexcept -> VulkanResult {

    this->_pLogicalDevice = & device;

    VulkanImageViewCreateInfo createInfo {};

    populateImageViewCreateInfo( & createInfo, image, format, aspectFlags );

    return vkCreateImageView ( this->_pLogicalDevice->data(), & createInfo ,nullptr, & this->_handle );
}

#include <VSwapChain.hpp>
auto VImageViewCollection :: setup (
        VSwapChain const * swapChain
) noexcept -> VulkanResult {

    this->_imageViews.resize( swapChain->getImages().size() );
    this->_pSwapChain = swapChain;

    uint32 index = 0U;

    for( auto & imageView : this->_imageViews ) {
        VulkanResult returnValue = imageView.setup(swapChain->getImages()[index++], swapChain->getImagesInfo().format, * this->_pSwapChain->getDevice());
        if( returnValue != VulkanResult::VK_SUCCESS ) {
            for ( uint32 clearIndex = 0U; clearIndex < index - 1U; clearIndex++ ) {
                this->_imageViews[clearIndex].clear();
            }
            return returnValue;
        }
    }

    return VulkanResult::VK_SUCCESS;
}

auto VImageViewCollection :: clear() noexcept -> void {
    for ( auto imageView : this->_imageViews ) {
        imageView.clear();
    }

    this->_imageViews.clear();
    this->_pSwapChain = nullptr;
}

VImageViewCollection :: VImageViewCollection (
        VImageViewCollection    const * pObj,
        VSwapChain              const * pSwapChain
) noexcept :
        VRenderObject() {

    this->_imageViews.clear();
    this->_pSwapChain = pSwapChain;

    for ( const auto & imageView : pObj->_imageViews ) {
        (void) this->_imageViews.emplace_back ( & imageView, pSwapChain->getDevice() );
    }
}

auto VImageView :: clear () noexcept -> void {
    if ( this->_handle != VK_NULL_HANDLE ) {
        vkDestroyImageView ( this->_pLogicalDevice->data(), this->_handle, nullptr );
    }
}

VImageView :: VImageView (
        VImageView      const * pObj,
        VLogicalDevice  const * pLogicalDevice
) noexcept :
        VRenderObject() {

    this->_handle           = pObj->_handle;
    this->_index            = pObj->_index;
    this->_pLogicalDevice   = pLogicalDevice;
}

auto VImageView :: getSwapChain() const noexcept -> engine::VSwapChain const * {
    return this->_pLogicalDevice->getSwapChain();
}

#include <sstream>

auto VImageViewCollection :: toString() const noexcept -> String {
    std::stringstream oss;
    oss << "VImageViewCollection { imageViews = [ ";
    for (auto const & item : this->_imageViews) {
        oss << item.toString() << ", ";
    }

    auto s = oss.str();
    return s.substr(s.size() - 2U).append(" ]}");
}

auto VImageView :: toString () const noexcept -> String {
    std::stringstream oss;
    oss << "VImageView { " <<
           "handle = 0x" << std::hex << reinterpret_cast < AddressValueType > (this->_handle) <<
           ", index = " << std::dec << this->_index <<
           ", pLogicalDevice = 0x" << std::hex << reinterpret_cast < AddressValueType const > (this->_pLogicalDevice) << " }";
    return oss.str();
}
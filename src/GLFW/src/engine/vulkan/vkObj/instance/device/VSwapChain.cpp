//
// Created by Vlad on 16/08/2020.
//

#include "VSwapChain.h"
#include "VSwapChainDefs.h"

#include <obj/util/settings/SettingOptionGraphics.h>


static inline VulkanSurfaceFormatKhronos chooseSwapSurfaceFormat ( const std::vector < VulkanSurfaceFormatKhronos > & availableFormats ) noexcept {
    for ( const auto & availableFormat : availableFormats ) {
        if (
                availableFormat.format      == __VK_FORMAT_8BIT_BGRA_SRGB &&
                availableFormat.colorSpace  == __VK_COLORSPACE_NONLINEAR_SRGB
                )
            return availableFormat;
    }

    return availableFormats[0];
}

static inline VulkanPresentModeKhronos chooseSwapPresentMode ( const std::vector < VulkanPresentModeKhronos > & availablePresentModes ) noexcept {

    for ( const auto & availablePresentMode : availablePresentModes )
        if ( availablePresentMode == __VK_PRESENT_MODE_VSYNC_TRIPLE_BUFFER )
            return availablePresentMode;

    return __VK_PRESENT_MODE_VSYNC_DOUBLE_BUFFER;
}

static inline const engine::ResolutionSetting * getSharedResolutionSetting () noexcept {

    const auto * pSetting = engine::SettingsSharedContainer::getInstance().get( engine::SettingOption::RESOLUTION );

    if ( pSetting != nullptr ) {
        const auto * pResolutionSetting = dynamic_cast < engine::ResolutionSetting const * >( pSetting );

        if( pResolutionSetting != nullptr )
            return pResolutionSetting;
    }

    return nullptr;
}

static inline VulkanExtent2D chooseSwapExtent ( const VulkanSurfaceCapabilitiesKhronos & capabilitiesKhronos ) noexcept ( false ) {
    if (capabilitiesKhronos.currentExtent.width != UINT32_MAX )
        return capabilitiesKhronos.currentExtent;

    const auto * sharedResolutionSetting = getSharedResolutionSetting();

    if( sharedResolutionSetting == nullptr )
        throw std::runtime_error( "No Resolution Set in SettingsSharedContainer" );

    VulkanExtent2D actualExtent = {
            sharedResolutionSetting->getWidth(),
            sharedResolutionSetting->getHeight()
    };

    actualExtent.width = std::max (
            capabilitiesKhronos.minImageExtent.width,
            std::min (
                    capabilitiesKhronos.maxImageExtent.width,
                    actualExtent.width
            )
    );

    actualExtent.height = std::max (
            capabilitiesKhronos.minImageExtent.height,
            std::min (
                    capabilitiesKhronos.maxImageExtent.height,
                    actualExtent.height
            )
    );

    return actualExtent;
}

engine::VSwapChain::VSwapChain(const VLogicalDevice *device) noexcept(false) :
    _device( device ){
    if( ! device->isSwapChainAdequate() )
        throw engine::EngineVLogicalDeviceSwapChainIncompatible();
}

VulkanResult engine::VSwapChain::setup() noexcept {
    if( this->_handle != nullptr )
        return VulkanResult::VK_ERROR_TOO_MANY_OBJECTS;

    auto swapChainSupportDetails = this->_device->getBasePhysicalDevice()->querySwapChainOnSurfaceSupport( this->_device->getSwapChainSurface() );

    auto surfaceFormat  = chooseSwapSurfaceFormat   ( swapChainSupportDetails.formats );
    auto presentMode    = chooseSwapPresentMode     ( swapChainSupportDetails.presentModes );
    auto extent         = chooseSwapExtent          ( swapChainSupportDetails.capabilities );

    uint32 imageCount = swapChainSupportDetails.capabilities.minImageCount;
    if( swapChainSupportDetails.capabilities.maxImageCount != 0 && imageCount > swapChainSupportDetails.capabilities.maxImageCount ) // max img count = 0 => no max image count
        imageCount = swapChainSupportDetails.capabilities.maxImageCount;


}

VulkanResult engine::VSwapChain::setup( const engine::VLogicalDevice * device) noexcept (false) {
    if( this->_handle != nullptr )
        return VulkanResult::VK_ERROR_TOO_MANY_OBJECTS;

    if( ! this->_device->isSwapChainAdequate() ) {
        throw engine::EngineVLogicalDeviceSwapChainIncompatible();
    }

    this->_device = device;

    return this->setup();
}

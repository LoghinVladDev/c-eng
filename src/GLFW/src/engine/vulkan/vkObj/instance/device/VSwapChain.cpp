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

static inline void swapChainLinkQueueFamilies (
    VulkanSwapChainCreateInfoKhronos * createInfo,
    const engine::VLogicalDevice * device
) noexcept {

    if ( createInfo == nullptr )
        return;

    static uint32 queueFamilyIndices[2];

    int32 graphicsFamilyIndex   = -1;
    int32 presentFamilyIndex    = -1;

    for ( const auto * queueFamily : device->getQueueFamilies() ) {
        if( queueFamily->isPresentCapable() && queueFamily->isGraphicsCapable() ) {
            graphicsFamilyIndex = presentFamilyIndex = queueFamily->getQueueFamilyIndex();
            break;
        } else {
            if( queueFamily->isGraphicsCapable() && graphicsFamilyIndex == -1 )
                graphicsFamilyIndex = queueFamily->getQueueFamilyIndex();
            else if( queueFamily->isPresentCapable() && presentFamilyIndex == -1 )
                presentFamilyIndex = queueFamily->getQueueFamilyIndex();
        }
    }

//    queueFamilyIndices = {
//        static_cast < uint32 > (graphicsFamilyIndex),
//        static_cast < uint32 > (presentFamilyIndex)
//    };

    queueFamilyIndices[0] = static_cast < uint32 > ( graphicsFamilyIndex );
    queueFamilyIndices[1] = static_cast < uint32 > ( presentFamilyIndex );

    if ( graphicsFamilyIndex != presentFamilyIndex ) {
        createInfo->imageSharingMode        = VK_SHARING_MODE_CONCURRENT;
        createInfo->queueFamilyIndexCount   = 2U;
        createInfo->pQueueFamilyIndices     = queueFamilyIndices;
    } else {
        createInfo->imageSharingMode        = VK_SHARING_MODE_EXCLUSIVE;
        createInfo->queueFamilyIndexCount   = 0U;
        createInfo->pQueueFamilyIndices     = nullptr;
    }
}

static inline void populateSwapChainCreateInfoStructure (
    VulkanSwapChainCreateInfoKhronos * createInfo,
    const engine::VLogicalDevice* device,
    uint32 imageCount,
    const engine::VPhysicalDevice::SwapChainSupportDetails & swapChainSupportDetails,
    engine::VSwapChain::VSwapChainImageInfo * savedSwapChainInformation = nullptr
) noexcept {

    if( createInfo == nullptr )
        return;

    auto surfaceFormat  = chooseSwapSurfaceFormat   ( swapChainSupportDetails.formats );
    auto presentMode    = chooseSwapPresentMode     ( swapChainSupportDetails.presentModes );
    auto extent         = chooseSwapExtent          ( swapChainSupportDetails.capabilities );

    * createInfo = {};

    createInfo->sType               = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo->surface             = device->getSwapChainSurface()->data();
    createInfo->minImageCount       = imageCount;
    createInfo->imageFormat         = surfaceFormat.format;
    createInfo->imageColorSpace     = surfaceFormat.colorSpace;
    createInfo->imageExtent         = extent;
    createInfo->imageArrayLayers    = 1U;
    createInfo->imageUsage          = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    /// use VK_IMAGE_USAGE_TRANSFER_DST_BIT for post process

    swapChainLinkQueueFamilies ( createInfo, device );

    createInfo->preTransform        = swapChainSupportDetails.capabilities.currentTransform;
    createInfo->compositeAlpha      = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo->presentMode         = presentMode;
    createInfo->clipped             = VK_TRUE;
    createInfo->oldSwapchain        = VK_NULL_HANDLE; /// should come back to this. once window resizes, you should recreate swap chain.

    if( savedSwapChainInformation != nullptr ) {
        savedSwapChainInformation->format = surfaceFormat.format;
        savedSwapChainInformation->extent = extent;
    }
}

engine::VSwapChain::VSwapChain(const VLogicalDevice *device) noexcept(false) :
    _device( device ) {
    if( ! device->isSwapChainAdequate() )
        throw engine::EngineVLogicalDeviceSwapChainIncompatible();
}

VulkanResult engine::VSwapChain::setup() noexcept {
    if( this->_handle != VK_NULL_HANDLE )
        return VulkanResult::VK_ERROR_TOO_MANY_OBJECTS;

    auto swapChainSupportDetails = this->_device->getBasePhysicalDevice()->querySwapChainOnSurfaceSupport( this->_device->getSwapChainSurface() );

    uint32 imageCount = swapChainSupportDetails.capabilities.minImageCount + 1;
    if( swapChainSupportDetails.capabilities.maxImageCount != 0 && imageCount > swapChainSupportDetails.capabilities.maxImageCount ) // max img count = 0 => no max image count
        imageCount = swapChainSupportDetails.capabilities.maxImageCount;

    VulkanSwapChainCreateInfoKhronos createInfo {};
    populateSwapChainCreateInfoStructure( & createInfo, this->_device, imageCount, swapChainSupportDetails, & this->_imagesInfo );

    VulkanResult createSwapChainResult = vkCreateSwapchainKHR( this->_device->data(), & createInfo, nullptr, & this->_handle );

    vkGetSwapchainImagesKHR( this->_device->data(), this->_handle, & imageCount, nullptr );

    this->_images.resize( imageCount );
    vkGetSwapchainImagesKHR( this->_device->data(), this->_handle, & imageCount, this->_images.data() );

    return createSwapChainResult;
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

void engine::VSwapChain::cleanup() noexcept {
    vkDestroySwapchainKHR( this->_device->data(), this->_handle, nullptr );
}

engine::VSwapChain::VSwapChain(const engine::VSwapChain & obj, const engine::VLogicalDevice * device) noexcept {
    this->_handle       = obj._handle;
    this->_images       = obj._images;
    this->_device       = device;
    this->_imagesInfo   = obj._imagesInfo;
}

engine::VImageViewCollection engine::VSwapChain::getImageViewCollection() const noexcept {
    engine::VImageViewCollection collection;
    collection.setup( this );

    return collection;
}

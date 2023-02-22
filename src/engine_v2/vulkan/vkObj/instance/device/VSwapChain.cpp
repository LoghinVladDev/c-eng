//
// Created by Vlad on 16/08/2020.
//

#include "VSwapChain.hpp"
#include "VSwapChainDefs.h"

#include <obj/util/settings/SettingOptionGraphics.hpp>

/**
 * @brief internal function used to choose optimal Surface Format for Swap Chain
 *
 * @param availableFormats : std::vector < VulkanSurfaceFormatKhronos > cref = Constant Reference to a vector containing several formats
 *
 * @exceptsafe
 *
 * @static
 *
 * @return VulkanSurfaceFormatKhronos = optimally chosen format
 */
static inline auto chooseSwapSurfaceFormat (
        std::vector < VulkanSurfaceFormatKhronos > const & availableFormats
) noexcept -> VulkanSurfaceFormatKhronos {
    for ( const auto & availableFormat : availableFormats ) { /// parse formats
        if (
                availableFormat.format      == __VK_FORMAT_8BIT_BGRA_SRGB &&
                availableFormat.colorSpace  == __VK_COLORSPACE_NONLINEAR_SRGB
        ) /// if SRGB available, use SRGB
            return availableFormat;
    }

    return availableFormats[0]; /// else use the first
}

/**
 * @brief internal function used to choose optimal Present Mode for Swap Chain
 *
 * @param availablePresentModes : std::vector < VulkanPresentModeKhronos > cref = Constant Reference to a vector containing several present modes
 *
 * @exceptsafe
 *
 * @static
 *
 * Present Mode = Buffering
 *
 * @return VulkanPresentModeKhronos = optimally chosen present mode
 */
static inline auto chooseSwapPresentMode (
        std::vector < VulkanPresentModeKhronos > const & availablePresentModes
) noexcept -> VulkanPresentModeKhronos {
    for ( const auto & availablePresentMode : availablePresentModes ) /// parse present modes
        if ( availablePresentMode == __VK_PRESENT_MODE_VSYNC_TRIPLE_BUFFER ) /// bias triple-buffering
            return availablePresentMode;

    return __VK_PRESENT_MODE_VSYNC_DOUBLE_BUFFER; /// else just double-buffer
}

/**
 * @brief internal function used to acquire globally-saved surface resolution
 *
 * @exceptsafe
 *
 * @static
 *
 * @return engine::ResolutionSetting cptr = Address to the currently saved Resolution Setting
 */
static inline auto getSharedResolutionSetting () noexcept -> engine::ResolutionSetting const * {
    const auto * pSetting = engine::SettingsSharedContainer::getInstance().get( engine::VSettingOption::RESOLUTION );

    if ( pSetting != nullptr ) {
        const auto * pResolutionSetting = dynamic_cast < engine::ResolutionSetting const * >( pSetting );

        if( pResolutionSetting != nullptr ) /// setting can be something else, not resolution
            return pResolutionSetting;
    }

    return nullptr; /// if no resolution saved, just return nullptr
}

/**
 * @brief internal function for choosing a swap chain extent ( image size )
 *
 * @param capabilitiesKhronos : VulkanSurfaceCapabilitiesKhronos cref = Surface Information
 *
 * @throws std::runtime_error if no Resolution was saved by application
 *
 * @static
 *
 * @return VulkanExtent2D = Structure containing width + height for swap chain images
 */
static inline auto chooseSwapExtent (
        VulkanSurfaceCapabilitiesKhronos const & capabilitiesKhronos
) noexcept ( false ) -> VulkanExtent2D {
    if (capabilitiesKhronos.currentExtent.width != UINT32_MAX )
        return capabilitiesKhronos.currentExtent; /// if extent already existed, just return current value

    const auto * sharedResolutionSetting = getSharedResolutionSetting(); /// acquire saved resolution

    if( sharedResolutionSetting == nullptr ) /// if resolution was not saved, throw
        throw std::runtime_error( "No Resolution Set in SettingsSharedContainer" );

    VulkanExtent2D actualExtent = { /// get extent from saved resolution
            sharedResolutionSetting->getWidth(),
            sharedResolutionSetting->getHeight()
    };

    actualExtent.width = std::max (
            capabilitiesKhronos.minImageExtent.width,
            std::min (
                    capabilitiesKhronos.maxImageExtent.width,
                    actualExtent.width
            )
    ); /// ensure that extent is minExtent.width <= extent.width <= maxExtent.width

    actualExtent.height = std::max (
            capabilitiesKhronos.minImageExtent.height,
            std::min (
                    capabilitiesKhronos.maxImageExtent.height,
                    actualExtent.height
            )
    ); /// ensure that extent is minExtent.height <= extent.height <= maxExtent.height

    return actualExtent;
}

/**
 * @brief internal function used to configure swap chain image memory sharing based on queues on logical device
 *
 * @param createInfo : VulkanSwapChainCreateInfoKhronos ptr = Address to create info for Swap Chain
 * @param device : engine::VLogicalDevice cptr = Address to Constant Logical Device
 *
 * @static
 *
 * @exceptsafe
 */
static inline auto swapChainLinkQueueFamilies (
    VulkanSwapChainCreateInfoKhronos * createInfo,
    engine::VLogicalDevice const * device
) noexcept -> void {

    if ( createInfo == nullptr ) /// if no create info to populate, return
        return;

    static uint32 queueFamilyIndices[2]; /// need to check only two different queue family indices

    sint32 graphicsFamilyIndex   = -1; /// starts of invalid
    sint32 presentFamilyIndex    = -1;

    for ( const auto * queueFamily : device->getQueueFamilies() ) {
        if( queueFamily->isPresentCapable() && queueFamily->isGraphicsCapable() ) {
            graphicsFamilyIndex = presentFamilyIndex = queueFamily->getQueueFamilyIndex();
            break; /// if a queue family capable of both present and graphics -> go exclusive
        } else { /// else go concurrent ( better )
            if( queueFamily->isGraphicsCapable() && graphicsFamilyIndex == -1 )
                graphicsFamilyIndex = queueFamily->getQueueFamilyIndex();
            else if( queueFamily->isPresentCapable() && presentFamilyIndex == -1 )
                presentFamilyIndex = queueFamily->getQueueFamilyIndex();
        }
    }

    queueFamilyIndices[0] = static_cast < uint32 > ( graphicsFamilyIndex );
    queueFamilyIndices[1] = static_cast < uint32 > ( presentFamilyIndex );

    if ( graphicsFamilyIndex != presentFamilyIndex ) { /// if concurrent
        createInfo->imageSharingMode        = VK_SHARING_MODE_CONCURRENT;
        createInfo->queueFamilyIndexCount   = 2U; /// save for two queue families
        createInfo->pQueueFamilyIndices     = queueFamilyIndices;
    } else { /// else exclusive, no sharing between queues
        createInfo->imageSharingMode        = VK_SHARING_MODE_EXCLUSIVE;
        createInfo->queueFamilyIndexCount   = 0U;
        createInfo->pQueueFamilyIndices     = nullptr;
    }
}

/**
 * @brief internal function used to correctly populate Swap Chain create info structure
 *
 * @param createInfo : VulkanSwapChainCreateInfoKhronos ptr = Address to Structure to populate
 * @param device : engine::VLogicalDevice cptr = Address to Constant Logical Device
 * @param imageCount : uint32 = Number of images to create with Swap Chain
 * @param swapChainSupportDetails : engine::VPhysicalDevice::SwapChainSupportDetails cref = Details of Device's Swap Chain support capabilities
 * @param savedSwapChainInformation : engine::VSwapChain::ImageInfo ptr = Address to Swap Chain Image Information, if previously saved
 *
 * @static
 *
 * @exceptsafe
 */
static inline auto populateSwapChainCreateInfoStructure (
    VulkanSwapChainCreateInfoKhronos                       * createInfo,
    engine::VLogicalDevice                           const * device,
    uint32                                                   imageCount,
    engine::VPhysicalDevice::SwapChainSupportDetails const & swapChainSupportDetails,
    engine::VSwapChain::ImageInfo                * savedSwapChainInformation = nullptr
) noexcept -> void {

    if( createInfo == nullptr ) /// if nothing to populate, return
        return;

    /// from physical device details
    auto surfaceFormat  = chooseSwapSurfaceFormat   ( swapChainSupportDetails.formats );
    auto presentMode    = chooseSwapPresentMode     ( swapChainSupportDetails.presentModes );
    auto extent         = chooseSwapExtent          ( swapChainSupportDetails.capabilities );

    * createInfo = {};

    createInfo->sType               = VulkanStructureType::VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo->surface             = device->getSwapChainSurface()->data(); /// attach surface
    createInfo->minImageCount       = imageCount;
    createInfo->imageFormat         = surfaceFormat.format;
    createInfo->imageColorSpace     = surfaceFormat.colorSpace;
    createInfo->imageExtent         = extent;
    createInfo->imageArrayLayers    = 1U;  /// only one image layer. Once Transparency exists, implement
    createInfo->imageUsage          = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT; /// state to signal once render is done
    /// use VK_IMAGE_USAGE_TRANSFER_DST_BIT for post process. TBA later

    swapChainLinkQueueFamilies ( createInfo, device );

    createInfo->preTransform        = swapChainSupportDetails.capabilities.currentTransform; /// do not adjust images before
    createInfo->compositeAlpha      = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR; /// do not use alpha
    createInfo->presentMode         = presentMode;
    createInfo->clipped             = VK_TRUE; /// clipped to swap-chain size
    createInfo->oldSwapchain        = VK_NULL_HANDLE; /// should come back to this. once window resizes, you should recreate swap chain.

    if( savedSwapChainInformation != nullptr ) {
        savedSwapChainInformation->format = surfaceFormat.format;
        savedSwapChainInformation->extent = extent;
    }
}

/**
 * @brief internal function used in populating the present info structure
 *
 * @param presentInfo : VulkanPresentInfoKhronos ptr = Address to structure to populate
 * @param pWaitSemaphores : engine::VulkanSemaphore cptr = Address to one / an array of Vulkan Semaphore Handles
 * @param waitSemaphoreCount : uint32 = Number of Semaphore Handles found at address above
 * @param pSwapChains : VulkanSwapChainKhronos cptr = Address to one / an array of Vulkan Swap Chain Handles. Can have multiple swapchains ( present to more than one surface )
 * @param pImageIndices : uint32 cptr = Address to one / an array of image indices. Should be associated with Swap Chains from above ( Image Index 1 corresponds to Swap Chain index 1 )
 * @param swapChainCount : uint32 = Number of Swap Chains to present from
 * @param pResults : VulkanResult ptr = Address to one / an array of Vulkan Results. Used to store indiviual present results. i.e. if one is successful but another fails
 *
 * @static
 *
 * @exceptsafe
 */
inline static auto populatePresentInfo (
    VulkanPresentInfoKhronos        * presentInfo,
    VulkanSemaphore           const * pWaitSemaphores,
    uint32                            waitSemaphoreCount,
    VulkanSwapChainKhronos    const * pSwapChains,
    uint32                    const * pImageIndices,
    uint32                            swapChainCount,
    VulkanResult                    * pResults = nullptr
) noexcept -> void {
    if (
        presentInfo     == nullptr || /// if any given address is null, return
        pSwapChains     == nullptr ||
        pImageIndices   == nullptr ||
        pWaitSemaphores == nullptr
    )
        return;

    * presentInfo = (VulkanPresentInfoKhronos) {
        .sType              = VulkanStructureType::VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
        .pNext              = nullptr,
        .waitSemaphoreCount = waitSemaphoreCount,
        .pWaitSemaphores    = pWaitSemaphores,
        .swapchainCount     = swapChainCount,
        .pSwapchains        = pSwapChains,
        .pImageIndices      = pImageIndices,
        .pResults           = pResults
    };
}

engine::VSwapChain::VSwapChain( VLogicalDevice const * device ) noexcept(false) :
    VRenderObject(),
    _device( device ) {
    if( ! device->isSwapChainAdequate() )
        throw engine::EngineVLogicalDeviceSwapChainIncompatible();
}

auto engine::VSwapChain::setup() noexcept -> VulkanResult {
    if( this->_handle != VK_NULL_HANDLE )
        return VulkanResult::VK_ERROR_TOO_MANY_OBJECTS;

    auto swapChainSupportDetails = this->_device->getBasePhysicalDevice()->querySwapChainOnSurfaceSupport( this->_device->getSwapChainSurface() );

    /// have at least one more image than is required - for buffering
    uint32 imageCount = swapChainSupportDetails.capabilities.minImageCount + 1;
    /// truncate max image count if necessary
    if( swapChainSupportDetails.capabilities.maxImageCount != 0 && imageCount > swapChainSupportDetails.capabilities.maxImageCount ) // max img count = 0 => no max image count
        imageCount = swapChainSupportDetails.capabilities.maxImageCount;

    VulkanSwapChainCreateInfoKhronos createInfo {};
    populateSwapChainCreateInfoStructure(
            & createInfo, /// this is the create info
            this->_device, /// on this device
            imageCount,  /// this many images
            swapChainSupportDetails, /// formatted like this
            & this->_imagesInfo /// save images here
    );

    VulkanResult createSwapChainResult = vkCreateSwapchainKHR(
            this->_device->data(), /// on this device
            & createInfo,  /// with these parameters
            nullptr, /// no custom allocator
            & this->_handle /// save Swap Chain handle here
    );

    vkGetSwapchainImagesKHR(
            this->_device->data(),
            this->_handle, /// get for this Swap Chain
            & imageCount,  /// number of images created
            nullptr
    );

    this->_images.clear(); /// clear previous images
    this->_images.resize( imageCount );

    vkGetSwapchainImagesKHR(
            this->_device->data(),
            this->_handle,
            & imageCount,
            this->_images.data()  /// acquire images
    );

    return createSwapChainResult;
}

auto engine::VSwapChain::setup( engine::VLogicalDevice const * device) noexcept (false) -> VulkanResult {
    if( this->_handle != nullptr )
        return VulkanResult::VK_ERROR_TOO_MANY_OBJECTS; /// if Swap Chain was previously set up, return invalid

    this->_device = device;

    if( ! this->_device->isSwapChainAdequate() ) { /// if device does not support Swap Chain
        throw engine::EngineVLogicalDeviceSwapChainIncompatible(); /// throw
    }

    return this->setup();
}

auto engine::VSwapChain::clear() noexcept -> void {
    /// de-allocate swap chain
    vkDestroySwapchainKHR( this->_device->data(), this->_handle, nullptr );
    this->_handle = VK_NULL_HANDLE; /// clear everything
    this->_device = nullptr;
    this->_images.clear();
}

engine::VSwapChain::VSwapChain(
        engine::VSwapChain const & obj,
        engine::VLogicalDevice const * device
) noexcept : VRenderObject(obj) {
    this->_handle       = obj._handle;
    this->_images       = obj._images;
    this->_device       = device;
    this->_imagesInfo   = obj._imagesInfo;
}

auto engine::VSwapChain::getImageViewCollection() const noexcept -> engine::VImageViewCollection {
    engine::VImageViewCollection collection;
    collection.setup( this ); /// create collection of image views off of this Swap Chain

    return collection;
}

auto engine::VSwapChain::present(
        VSemaphore const * pWaitSemaphores,
        uint32 waitSemaphoreCount,
        uint32 imageIndex
) const noexcept -> VulkanResult {
    VulkanPresentInfoKhronos presentInfo { };

    /// handles of semaphores to wait for
#if !defined(_MSC_VER)
    VulkanSemaphore waitSemaphoreHandles [ waitSemaphoreCount ];
#else
    auto * waitSemaphoreHandles = new VulkanSemaphore [ waitSemaphoreCount ];
#endif

    for( uint32 i = 0; i < waitSemaphoreCount; i++ )
        waitSemaphoreHandles[i] = pWaitSemaphores[i].data(); /// obtain handles

    populatePresentInfo(
        & presentInfo, /// populate this structure
        waitSemaphoreHandles, /// these semaphore handles
        waitSemaphoreCount, /// this many semaphores
        & this->_handle, /// this swapchain
        & imageIndex, /// this image
        1U /// a single swap chain
    );

    auto pPresentQueue = this->_device->getFirstPresentQueuePtr(); /// acquire presentation queue

    VulkanResult result = VK_SUCCESS;

    if ( pPresentQueue == nullptr )
        result = VulkanResult::VK_ERROR_INITIALIZATION_FAILED; /// if no queue, return invalid
    else 
        result = vkQueuePresentKHR( pPresentQueue->data(), & presentInfo ); /// queue present data

#if defined(_MSC_VER)
    delete[] waitSemaphoreHandles;
#endif

    return result;
}

#include <sstream>

auto engine::VSwapChain::toString() const noexcept -> String {
    std::stringstream oss;

    oss << "VSwapChain " <<
        "{ handle = 0x" << std::hex << reinterpret_cast<AddressValueType>(this->_handle) <<
        ", pLogicalDevice = 0x" << reinterpret_cast<AddressValueType>(this->_device) <<
        ", imagesInfo = " <<
            "{ width = " << std::dec << this->_imagesInfo.extent.width <<
            ", height = " << this->_imagesInfo.extent.height <<
            ", format = " << static_cast<uint32>(this->_imagesInfo.format) << " }" <<
        ", images = [ ";

    for (auto const & item : this->_images)
        oss << std::hex << "0x" << reinterpret_cast<AddressValueType>(item) << ", ";

    auto s = oss.str();
    return s.substr(s.size() - 2).append(" ]}");
}
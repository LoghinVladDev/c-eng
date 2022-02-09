//
// Created by loghin on 03.02.2022.
//

#include "SwapChain.hpp"
#include <SwapChainPresentHandler.hpp>
#include <Device.hpp>
#include <PhysicalDevice.hpp>
#include <VulkanAPI.hpp>
#include <Logger.hpp>
#include <Settings.hpp>
#include <Allocator.hpp>
#include <CDS/Mutex>
#include <CDS/LockGuard>


using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace vulkan; // NOLINT(clion-misra-cpp2008-7-3-4)


#define C_ENG_MAP_START     CLASS ( SwapChain,  ENGINE_PARENT ( VulkanRenderObject ) )
#include <ObjectMapping.hpp>


struct SwapChainImages {
    Type ( ImageHandle )        imagesArray [ __C_ENG_VULKAN_CORE_SWAP_CHAIN_IMAGE_MAX_COUNT ];
    Type ( SwapChainHandle )    swapChainHandle;
};

static SwapChainImages  swapChainImageAreas [ __C_ENG_VULKAN_CORE_PHYSICAL_DEVICE_MAX_COUNT * __C_ENG_VULKAN_CORE_PHYSICAL_DEVICE_SURFACE_MAX_COUNT ];
static Mutex            areasLock;


static inline auto chooseFormat (
        Type ( PresentHandler ) :: SurfaceProperties const * pProperties
) noexcept -> Type ( SurfaceFormat ) const * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pProperties == nullptr ) {
        return nullptr;
    }

#endif

    for ( uint32 i = 0U; i < pProperties->formats.count; ++ i ) {
        if (
                pProperties->formats.pFormats[i].format     == Format_B8_G8_R8_A8_SRGB &&
                pProperties->formats.pFormats[i].colorSpace == ColorSpaceSRGBNonLinear
        ) {
            return & pProperties->formats.pFormats[i];
        }
    }

    return & pProperties->formats.pFormats[0];
}

static inline auto chooseExtent (
        Type ( PresentHandler ) :: SurfaceProperties const * pProperties
) noexcept -> Type ( Extent2D ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pProperties == nullptr ) {
        return {};
    }

#endif

    if ( pProperties->surfaceCapabilities.currentExtent.width != limits :: U32_MAX ) {
        return pProperties->surfaceCapabilities.currentExtent;
    }

    auto resolution = Type ( Settings ) :: instance().get( Type ( Settings ) :: keyResolution );

    return {
        .width  = std :: min (
                static_cast < uint32 > ( ( resolution >> 32 ) & 0xFFFFFFFFU ),
                pProperties->surfaceCapabilities.maxImageExtent.width
        ),
        .height = std :: min (
                static_cast < uint32 > ( resolution & 0xFFFFFFFFU ),
                pProperties->surfaceCapabilities.maxImageExtent.height
        )
    };
}

static inline auto chooseTransform (
        Type ( PresentHandler ) :: SurfaceProperties const * pProperties
) noexcept -> Type ( SurfaceTransformFlag ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pProperties == nullptr ) {
        return SurfaceTransformFlagIdentity;
    }

#endif

    return pProperties->surfaceCapabilities.currentTransform;
}

static inline auto choosePresentMode (
        Type ( PresentHandler ) :: SurfaceProperties const * pProperties
) noexcept -> Type ( PresentMode ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pProperties == nullptr ) {
        return PresentModeImmediate;
    }

#endif

    for ( uint32 i = 0U; i < pProperties->presentModes.count; ++ i ) {
        if ( pProperties->presentModes.pPresentModes[i] == PresentModeMailbox ) {
            return PresentModeMailbox;
        }
    }

    return PresentModeFifo;
}

static inline auto populateSwapChainCreateInfo (
        Type ( SwapChainCreateInfo )  * pCreateInfo,
        Type ( SurfaceHandle )          surfaceHandle,
        uint32                          imageCount,
        Type ( SurfaceFormat )  const * pSurfaceFormat,
        Type ( Extent2D )       const * pExtent,
        uint32                          imageArrayLayers,
        Type ( ImageUsageFlags )        imageUsageFlags,
        uint32                          queueFamilyIndexCount,
        uint32                  const * pQueueFamilyIndices,
        Type ( SurfaceTransformFlag )   transform,
        Type ( PresentMode )            presentMode,
        Type ( SwapChainHandle )        oldSwapChainHandle
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if (
            pCreateInfo             == nullptr  ||
            surfaceHandle           == nullptr  ||
            pSurfaceFormat          == nullptr  ||
            pExtent                 == nullptr  ||
            pQueueFamilyIndices     == nullptr  ||
            queueFamilyIndexCount   == 0U       ||
            imageCount              == 0U
    ) {
        return;
    }

#endif

    * pCreateInfo = {
            .structureType          = StructureTypeSwapChainCreateInfo,
            .pNext                  = nullptr,
            .flags                  = 0U,
            .surface                = surfaceHandle,
            .minImageCount          = imageCount,
            .imageFormat            = pSurfaceFormat->format,
            .imageColorSpace        = pSurfaceFormat->colorSpace,
            .imageExtent            = {
                .width                  = pExtent->width,
                .height                 = pExtent->height
            },
            .imageArrayLayers       = imageArrayLayers,
            .imageUsage             = imageUsageFlags,
            .imageSharingMode       = ( queueFamilyIndexCount == 1U ? SharingModeExclusive : SharingModeConcurrent ),
            .queueFamilyIndexCount  = queueFamilyIndexCount,
            .pQueueFamilyIndices    = pQueueFamilyIndices,
            .preTransform           = transform,
            .compositeAlpha         = CompositeAlphaFlagOpaque,
            .presentMode            = presentMode,
            .clipped                = VK_TRUE,
            .oldSwapChain           = oldSwapChainHandle
    };
}

static inline auto populateQueueFamilyIndices (
        Type ( Device ) const * pDevice,
        uint32                * pQueueFamilyIndexCount,
        uint32                * pQueueFamilyIndices
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if (
            pDevice                 == nullptr ||
            pQueueFamilyIndexCount  == nullptr ||
            pQueueFamilyIndices     == nullptr
    ) {
        return;
    }

#endif

    * pQueueFamilyIndexCount = 0U;

    for ( auto const & queue : pDevice->queues() ) {

        if (
                queue.type() == QueueFlagGraphics ||
                queue.type() == QueueFlagPresent
        ) {

            bool toAdd = true;
            for ( uint32 i = 0U; i < * pQueueFamilyIndexCount; ++ i ) {

                if ( pQueueFamilyIndices[i] == queue.queueFamily()->index() ) {
                    toAdd = false;
                    break;
                }
            }

            if ( toAdd ) {
                pQueueFamilyIndices [ ( * pQueueFamilyIndexCount ) ++ ] = queue.queueFamily()->index();
            }
        }
    }
}

auto Self :: init (
        Type ( Device )         const * pDevice,
        Type ( SurfaceHandle )          surfaceHandle
) noexcept (false) -> Self & {

    auto presentProperties = Type ( SwapChainPresentHandler ) :: propertiesForDevice (
            pDevice->physicalDevice()->handle(),
            surfaceHandle
    );

    if ( presentProperties == nullptr ) {
        throw Type ( VulkanAPIException ) ( "Device-Surface pair does not have properties. Check configuration for limit" );
    }

    uint32 swapChainImageCount = presentProperties->surfaceCapabilities.minImageCount + 1U;

    if (
            presentProperties->surfaceCapabilities.maxImageCount != 0U &&
            swapChainImageCount > presentProperties->surfaceCapabilities.maxImageCount
    ) {
        swapChainImageCount = presentProperties->surfaceCapabilities.maxImageCount;
    }


    Type ( SwapChainCreateInfo ) createInfo {};

    uint32 imageArrayLayers = 1U;

    auto pSurfaceFormat = chooseFormat ( presentProperties );
    auto extent         = chooseExtent ( presentProperties );
    auto transform      = chooseTransform ( presentProperties );
    auto presentMode    = choosePresentMode ( presentProperties );

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSurfaceFormat  == nullptr ) {
        throw Type ( VulkanAPIException ) ( "Unavailable SurfaceFormat / Extent for swap chain creation" );
    }

#endif

    uint32 queueFamilyIndexCount = 0U;
    uint32 queueFamilyIndices [ __C_ENG_VULKAN_CORE_QUEUE_FAMILY_MAX_COUNT ];

    populateQueueFamilyIndices (
            pDevice,
            & queueFamilyIndexCount,
            & queueFamilyIndices [0]
    );

    populateSwapChainCreateInfo (
            & createInfo,
            surfaceHandle,
            swapChainImageCount,
            pSurfaceFormat,
            & extent,
            imageArrayLayers,
            ImageUsageFlagColorAttachment,
            queueFamilyIndexCount,
            & queueFamilyIndices [0],
            transform,
            presentMode,
            nullptr
    );

    auto result = createSwapChain (
            pDevice->handle(),
            & createInfo,
            Type ( Allocator ) :: instance().callbacks(),
            & this->_handle
    );

    if ( result != ResultSuccess ) {
        __C_ENG_LOG_AND_THROW_DETAILED_API_CALL_EXCEPTION ( error, "createSwapChain", result );
    }

    this->_device = pDevice;
    this->_properties = {
        .imageExtent    = createInfo.imageExtent,
        .imageFormat    = createInfo.imageFormat
    };

    return this->reserveAndAcquireImages ();
}

auto Self :: clear () noexcept -> Self & {

    if ( this->handle() != nullptr ) {
        (void) this->freeImages ();

        auto result = destroySwapChain (
                this->_device->handle(),
                this->handle(),
                Type ( Allocator ) :: instance().callbacks()
        );

        if ( result != ResultSuccess ) {
            __C_ENG_LOG_DETAILED_API_CALL_EXCEPTION ( error, "destroySwapChain", result );
        }

        this->_handle           = nullptr;
        this->_device           = nullptr;
    }

    return * this;
}

auto Self :: reserveAndAcquireImages () noexcept(false) -> Self & {

    SwapChainImages * pArea = nullptr;

    LockGuard guard ( areasLock );

    for ( auto & swapChainImageArea : swapChainImageAreas ) {
        if ( swapChainImageArea.swapChainHandle == nullptr || swapChainImageArea.swapChainHandle == this->handle() ) {
            pArea = & swapChainImageArea;
            break;
        }
    }

    if ( pArea == nullptr ) {
        throw Type ( VulkanAPIException ) ( "No area to reserve images into. Check configuration size" );
    }

    uint32 imageCount = 0U;

    auto result = getSwapChainImages (
            this->device()->handle(),
            this->handle(),
            & imageCount
    );

    if ( result != ResultSuccess ) {
        __C_ENG_LOG_AND_THROW_DETAILED_API_CALL_EXCEPTION ( error, "getSwapChainImages", result );
    }

    result = getSwapChainImages (
            this->device()->handle(),
            this->handle(),
            & imageCount,
            & pArea->imagesArray[0]
    );

    if ( result != ResultSuccess ) {
        __C_ENG_LOG_AND_THROW_DETAILED_API_CALL_EXCEPTION ( error, "getSwapChainImages", result );
    }

    pArea->swapChainHandle = this->_handle;

    this->_images.count     = imageCount;
    this->_images.pImages   = & pArea->imagesArray[0];

    return * this;
}

auto Self :: freeImages() noexcept -> VSwapChain & {
    for ( auto & imageArea : swapChainImageAreas ) {
        if ( imageArea.swapChainHandle == this->_handle ) {

            imageArea.swapChainHandle = nullptr;
            this->_images.count     = 0U;
            this->_images.pImages   = nullptr;
            return * this;
        }
    }

    for ( auto & imageArea : swapChainImageAreas ) {
        if ( imageArea.imagesArray == this->_images.pImages ) {

            imageArea.swapChainHandle = nullptr;
            this->_images.count     = 0U;
            this->_images.pImages   = nullptr;
            return * this;
        }
    }

    return * this;
}

Self :: Destructor () noexcept {
    (void) this->Self :: clear();
}

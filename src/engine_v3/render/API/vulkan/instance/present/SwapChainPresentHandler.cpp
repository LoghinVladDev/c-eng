//
// Created by loghin on 07.02.2022.
//

#include "SwapChainPresentHandler.hpp"
#include <Device.hpp>
#include <PhysicalDevice.hpp>
#include <VulkanAPI.hpp>
#include <Logger.hpp>
#include <Allocator.hpp>

using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace vulkan; // NOLINT(clion-misra-cpp2008-7-3-4)

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE
#define C_ENG_MAP_START     CLASS ( SwapChainPresentHandler, ENGINE_PARENT ( PresentHandler ) )
#include <ObjectMapping.hpp>

static inline auto populateImageViewCreateInfo (
        Type ( ImageViewCreateInfo )  * pCreateInfo,
        Type ( ImageHandle )            imageHandle,
        Type ( Format )                 imageFormat,
        Type ( ImageAspectFlags )       aspectMask
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if (
            pCreateInfo == nullptr ||
            imageHandle == nullptr
    ) {
        return;
    }

#endif

    * pCreateInfo = {
            .structureType      = StructureTypeImageViewCreateInfo,
            .pNext              = nullptr,
            .flags              = 0U,
            .image              = imageHandle,
            .viewType           = ImageViewType2D,
            .format             = imageFormat,
            .components         = {
                    .r                  = ComponentSwizzleIdentity,
                    .g                  = ComponentSwizzleIdentity,
                    .b                  = ComponentSwizzleIdentity,
                    .a                  = ComponentSwizzleIdentity
            },
            .subresourceRange   = {
                    .aspectMask         = aspectMask,
                    .baseMipLevel       = 0U,
                    .levelCount         = 1U,
                    .baseArrayLayer     = 0U,
                    .layerCount         = 1U
            }
    };
}

auto Self :: init (
        Type ( Device ) const * pDevice
) noexcept (false) -> Self & {

    (void) this->_swapChain.init ( pDevice, this->_surface );

    auto pImageViews = this->Parent :: acquireImageViews();

    try {

        for ( uint32 imageIndex = 0U; imageIndex < this->swapChain().images().count; ++imageIndex ) {

            Type ( ImageViewCreateInfo ) imageViewCreateInfo { };
            Type ( ImageAspectFlags ) aspectMask = ImageAspectFlagColor;

            populateImageViewCreateInfo (
                    & imageViewCreateInfo,
                    this->swapChain().images().pImages [ imageIndex ],
                    this->swapChain().properties().imageFormat,
                    aspectMask
            );

            auto result = createImageView (
                    pDevice->handle(),
                    & imageViewCreateInfo,
                    Type ( Allocator ) :: instance().callbacks(),
                    & pImageViews [ imageIndex ]
            );

            if ( result != ResultSuccess ) {
                __C_ENG_LOG_AND_THROW_DETAILED_API_CALL_EXCEPTION ( error, "createImageView", result );
            }
        }

    } catch ( ... ) {
        this->Parent :: releaseImageViews();
        throw;
    }

    this->imageViews() = {
            .pImageViews    = pImageViews,
            .count          = this->swapChain().images().count
    };

    return * this;
}

auto Self :: clear () noexcept -> Self & {

    for ( uint32 i = 0U; i < this->imageViews().count; ++ i ) {

        auto result = destroyImageView (
                this->swapChain().device()->handle(),
                this->imageViews().pImageViews[i],
                Type ( Allocator ) :: instance().callbacks()
        );

        if ( result != ResultSuccess ) {
            __C_ENG_LOG_DETAILED_API_CALL_EXCEPTION ( warning, "destroyImageView", result );
        }
    }

    this->releaseImageViews();
    this->imageViews().count = 0U;

    (void) this->_swapChain.clear();

    return * this;
}

Self :: Destructor () noexcept {
    (void) this->Self :: clear();
}

Self :: Constructor (
        Type ( SurfaceHandle ) handle
) noexcept :
        _surface ( handle ) {

}
#endif

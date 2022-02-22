//
// Created by loghin on 03.02.2022.
//

#include "PresentHandler.hpp"
#include <SwapChainPresentHandler.hpp>
#include <VulkanAPI.hpp>
#include <CDS/Mutex>
#include <CDS/LockGuard>
#include <Logger.hpp>
#include <Device.hpp>
#include <PhysicalDevice.hpp>

using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace vulkan; // NOLINT(clion-misra-cpp2008-7-3-4)

#define C_ENG_MAP_START     CLASS ( PresentHandler, ENGINE_PARENT ( VulkanRenderObject ) )
#include <ObjectMapping.hpp>


struct DeviceSurfaceProperties {
    Self :: SurfaceProperties       properties;
    Type ( PhysicalDeviceHandle )   deviceHandle;
    Type ( SurfaceHandle )          surfaceHandle;
};

namespace globals {
    static Mutex propertiesLock;

    static Type ( SurfaceFormat ) surfaceFormats [ __C_ENG_VULKAN_CORE_PHYSICAL_DEVICE_MAX_COUNT * __C_ENG_VULKAN_CORE_PHYSICAL_DEVICE_SURFACE_MAX_COUNT ] [ __C_ENG_VULKAN_CORE_SURFACE_FORMAT_MAX_COUNT ];
    static Type ( PresentMode ) presentModes [ __C_ENG_VULKAN_CORE_PHYSICAL_DEVICE_MAX_COUNT * __C_ENG_VULKAN_CORE_PHYSICAL_DEVICE_SURFACE_MAX_COUNT ] [ __C_ENG_VULKAN_CORE_SURFACE_PRESENT_MODE_MAX_COUNT ];

    static DeviceSurfaceProperties properties [ __C_ENG_VULKAN_CORE_PHYSICAL_DEVICE_MAX_COUNT * __C_ENG_VULKAN_CORE_PHYSICAL_DEVICE_SURFACE_MAX_COUNT ];
    static uint32 propertyCount;

    static DeviceSurfaceProperties * pLastUsedDeviceProperties;
}


struct ImageViewArea {
    Type ( ImageViewHandle )    imageViewHandles [ __C_ENG_VULKAN_CORE_SWAP_CHAIN_IMAGE_MAX_COUNT ];
    Self                const * pOwner;
};

namespace globals {
    static Mutex imageViewsLock;
    static ImageViewArea imageViewAreas [ __C_ENG_VULKAN_CORE_PHYSICAL_DEVICE_MAX_COUNT * __C_ENG_VULKAN_CORE_PHYSICAL_DEVICE_SURFACE_MAX_COUNT ];
}


auto Self :: propertiesForDevice (
        Type ( PhysicalDeviceHandle )   deviceHandle,
        Type ( SurfaceHandle )          surfaceHandle
) noexcept (false) -> Self :: SurfaceProperties const * {

    if (
            deviceHandle    == nullptr ||
            surfaceHandle   == nullptr
    ) {
        return nullptr;
    }

    LockGuard guard ( globals :: propertiesLock );

    if (
            globals :: pLastUsedDeviceProperties                   != nullptr &&
            globals :: pLastUsedDeviceProperties->deviceHandle     == deviceHandle &&
            globals :: pLastUsedDeviceProperties->surfaceHandle    == surfaceHandle
    ) {
        return & globals :: pLastUsedDeviceProperties->properties;
    }

    for ( uint32 i = 0U; i < globals :: propertyCount; ++ i ) {
        if ( globals :: properties[i].deviceHandle == deviceHandle ) {

            globals :: pLastUsedDeviceProperties = & globals :: properties [i];
            return & globals :: properties[i].properties;
        }
    }

    if ( globals :: propertyCount >= __C_ENG_VULKAN_CORE_PHYSICAL_DEVICE_MAX_COUNT ) {
        return nullptr;
    }

    auto currentProperties = & globals :: properties [ globals :: propertyCount ];

    currentProperties->properties.formats.pFormats              = & globals :: surfaceFormats [ globals :: propertyCount ] [ 0 ];
    currentProperties->properties.presentModes.pPresentModes    = & globals :: presentModes [ globals :: propertyCount ] [ 0 ];

    auto result = getPhysicalDeviceSurfaceCapabilities (
            deviceHandle,
            surfaceHandle,
            & currentProperties->properties.surfaceCapabilities
    );

    if ( result != ResultSuccess ) {
        __C_ENG_LOG_AND_THROW_DETAILED_API_CALL_EXCEPTION ( error, "getPhysicalDeviceSurfaceCapabilities", result );
    }

    result = getPhysicalDeviceSurfaceFormats (
            deviceHandle,
            surfaceHandle,
            & currentProperties->properties.formats.count
    );

    if ( result != ResultSuccess ) {
        __C_ENG_LOG_AND_THROW_DETAILED_API_CALL_EXCEPTION ( error, "getPhysicalDeviceSurfaceFormats", result );
    }

    result = getPhysicalDeviceSurfaceFormats (
            deviceHandle,
            surfaceHandle,
            & currentProperties->properties.formats.count,
            & currentProperties->properties.formats.pFormats [0]
    );

    if ( result != ResultSuccess ) {
        __C_ENG_LOG_AND_THROW_DETAILED_API_CALL_EXCEPTION ( error, "getPhysicalDeviceSurfaceFormats", result );
    }

    result = getPhysicalDeviceSurfacePresentModes (
            deviceHandle,
            surfaceHandle,
            & currentProperties->properties.presentModes.count
    );

    if ( result != ResultSuccess ) {
        __C_ENG_LOG_AND_THROW_DETAILED_API_CALL_EXCEPTION ( error, "getPhysicalDeviceSurfacePresentModes", result );
    }

    result = getPhysicalDeviceSurfacePresentModes (
            deviceHandle,
            surfaceHandle,
            & currentProperties->properties.presentModes.count,
            & currentProperties->properties.presentModes.pPresentModes [ 0 ]
    );

    if ( result != ResultSuccess ) {
        __C_ENG_LOG_AND_THROW_DETAILED_API_CALL_EXCEPTION ( error, "getPhysicalDeviceSurfacePresentModes", result );
    }

    currentProperties->deviceHandle         = deviceHandle;
    currentProperties->surfaceHandle        = surfaceHandle;
    globals :: pLastUsedDeviceProperties    = currentProperties;

    return & globals :: properties [ globals :: propertyCount ++ ].properties;
}

auto Self :: deviceSupportsSurfacePresent (
        Type ( Device )         const * pDevice,
        Type ( SurfaceHandle )          surfaceHandle
) noexcept (false) -> bool {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDevice == nullptr ) {
        return false;
    }

#endif

    if ( surfaceHandle == nullptr ) {
        return false;
    }

    auto pProperties = Self :: propertiesForDevice (
            pDevice->physicalDevice()->handle(),
            surfaceHandle
    );

    return
        pProperties != nullptr          &&
        pProperties->formats.count > 0U &&
        pProperties->presentModes.count > 0U;
}

auto Self :: createSuitablePresentHandler (
        Type ( Device )         const * pDevice,
        Type ( SurfaceHandle )          surfaceHandle
) noexcept -> UniquePointer < Type ( PresentHandler ) > {

    if ( Self :: deviceSupportsSurfacePresent ( pDevice, surfaceHandle ) ) {
        return new Type ( SwapChainPresentHandler ) (surfaceHandle); // NOLINT(clion-misra-cpp2008-18-4-1)
    }

    return nullptr;
}

auto Self :: acquireImageViews () noexcept -> Type ( ImageViewHandle ) * {

    LockGuard guard ( globals :: imageViewsLock );

    for ( auto & area : globals :: imageViewAreas ) {
        if ( area.pOwner == nullptr ) {
            area.pOwner = this;
            return area.imageViewHandles;
        }
    }

    return nullptr;
}

auto Self :: releaseImageViews () noexcept -> void {

    LockGuard guard ( globals :: imageViewsLock );

    for ( auto & area : globals :: imageViewAreas ) {
        if ( area.pOwner == this ) {
            area.pOwner = nullptr;
            return;
        }
    }
}

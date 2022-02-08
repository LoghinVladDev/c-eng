//
// Created by loghin on 03.02.2022.
//

#include "PresentHandler.hpp"
#include <SwapChainPresentHandler.hpp>
#include <VulkanAPI.hpp>
#include <CDS/Mutex>
#include <CDS/LockGuard>
#include <VulkanAPI.hpp>
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

static Mutex propertiesLock;

static Type ( SurfaceFormat ) surfaceFormats [ __C_ENG_VULKAN_CORE_PHYSICAL_DEVICE_MAX_COUNT * __C_ENG_VULKAN_CORE_PHYSICAL_DEVICE_SURFACE_MAX_COUNT ] [ __C_ENG_VULKAN_CORE_SURFACE_FORMAT_MAX_COUNT ];
static Type ( PresentMode ) presentModes [ __C_ENG_VULKAN_CORE_PHYSICAL_DEVICE_MAX_COUNT * __C_ENG_VULKAN_CORE_PHYSICAL_DEVICE_SURFACE_MAX_COUNT ] [ __C_ENG_VULKAN_CORE_SURFACE_PRESENT_MODE_MAX_COUNT ];

static DeviceSurfaceProperties properties [ __C_ENG_VULKAN_CORE_PHYSICAL_DEVICE_MAX_COUNT * __C_ENG_VULKAN_CORE_PHYSICAL_DEVICE_SURFACE_MAX_COUNT ];
static uint32 propertyCount;

static DeviceSurfaceProperties * pLastUsedDeviceProperties;


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

    LockGuard guard ( propertiesLock );

    if (
            pLastUsedDeviceProperties                   != nullptr &&
            pLastUsedDeviceProperties->deviceHandle     == deviceHandle &&
            pLastUsedDeviceProperties->surfaceHandle    == surfaceHandle
    ) {
        return & pLastUsedDeviceProperties->properties;
    }

    for ( uint32 i = 0U; i < propertyCount; ++ i ) {
        if ( properties[i].deviceHandle == deviceHandle ) {

            pLastUsedDeviceProperties = & properties [i];
            return & properties[i].properties;
        }
    }

    if ( propertyCount >= __C_ENG_VULKAN_CORE_PHYSICAL_DEVICE_MAX_COUNT ) {
        return nullptr;
    }

    auto currentProperties = & properties [ propertyCount ];

    currentProperties->properties.formats.pFormats              = & surfaceFormats [ propertyCount ] [ 0 ];
    currentProperties->properties.presentModes.pPresentModes    = & presentModes [ propertyCount ] [ 0 ];

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

    currentProperties->deviceHandle     = deviceHandle;
    currentProperties->surfaceHandle    = surfaceHandle;
    pLastUsedDeviceProperties           = currentProperties;

    return & properties [ propertyCount ++ ].properties;
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

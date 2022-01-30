//
// Created by loghin on 30.01.2022.
//

#include "Device.hpp"
#include <VulkanAPIExceptions.hpp>
#include <PhysicalDevice.hpp>
#include <VulkanCoreConfig.hpp>


using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace vulkan; // NOLINT(clion-misra-cpp2008-7-3-4)


static __C_ENG_TYPE ( PhysicalDeviceExtendedFeatures ) extendedFeatures;

#define C_ENG_MAP_START     NESTED_CLASS ( Builder, ENGINE_TYPE ( Device ), PARENT ( cds :: Object ) )
#include <ObjectMapping.hpp>


static inline auto deviceCreateInfoAddAllFeatures (
        Type ( DeviceCreateInfo )       * pCreateInfo,
        Type ( PhysicalDevice )   const * pPhysicalDevice,
        bool                            * pProtectedMemoryEnabled
) noexcept -> void {

    if (
            pCreateInfo             == nullptr ||
            pPhysicalDevice         == nullptr ||
            pProtectedMemoryEnabled == nullptr
    ) {
        return;
    }

    (void) std :: memcpy ( & extendedFeatures.features, & pPhysicalDevice->details().basicFeatures, sizeof ( Type ( PhysicalDeviceFeatures ) ) );

    engine :: vulkan :: utility ::chainFeaturesFromDetails ( & extendedFeatures, & ( pPhysicalDevice->details() ) );

    * pProtectedMemoryEnabled =
            ( pPhysicalDevice->details().vulkan11Features.protectedMemory == VK_TRUE ) ||
            ( pPhysicalDevice->details().protectedMemoryFeatures.protectedMemory == VK_TRUE );
}

static inline auto deviceCreateInfoAddOnlyBasicFeatures (
        Type ( DeviceCreateInfo )       * pCreateInfo,
        Type ( PhysicalDevice )   const * pPhysicalDevice,
        bool                            * pProtectedMemoryEnabled
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if (
            pCreateInfo             == nullptr ||
            pPhysicalDevice         == nullptr ||
            pProtectedMemoryEnabled == nullptr
    ) {
        return;
    }

#endif

    pCreateInfo->pEnabledFeatures   = & pPhysicalDevice->details().basicFeatures;
    * pProtectedMemoryEnabled       = false;
}

static inline auto deviceCreateInfoAddFeatureSets (
        Type ( DeviceCreateInfo )       * pCreateInfo,
        Type ( PhysicalDevice )   const * pPhysicalDevice,
        bool                            * pProtectedMemoryEnabled
) noexcept -> void {
}


auto Self :: build () noexcept (false) -> Nester {
    if ( this->_surfaceHandle != nullptr && ! this->_extensionNames.contains ( VK_KHR_SWAPCHAIN_EXTENSION_NAME ) ) {
        this->_extensionNames.add ( VK_KHR_SWAPCHAIN_EXTENSION_NAME );
    }

    if (
            this->_surfaceHandle    != nullptr &&
            this->_physicalDevice   != nullptr
    ) {
        return this->buildSingleDeviceToSurface();
    }

    throw Type ( VulkanAPIException ) ( "Unable to build device from given objects" );
}

auto Self :: buildSingleDeviceToSurface () noexcept (false) -> Nester {
    Nester device;

    device._physicalDevice  = this->_physicalDevice;
    device._surfaceHandle   = this->_surfaceHandle;

    Type ( DeviceCreateInfo ) deviceCreateInfo {};

    bool protectedMemoryEnabled = false;

    uint32 featureOptionCount =
            (this->_allFeatures ? 1U : 0U) +
            (this->_onlyBasicFeatures ? 1U : 0U) +
            (this->_featureSets.empty() ? 0U : 1U);

    if ( featureOptionCount != 1U ) {
        throw Type ( VulkanAPIException ) ( "Must select one and only one option for feature sets to use from device. (allFeatures, onlyBasicFeatures, featureSets" );
    }

    if ( this->_allFeatures ) {
        deviceCreateInfoAddAllFeatures ( & deviceCreateInfo, device._physicalDevice, & protectedMemoryEnabled );
    } else if ( this->_onlyBasicFeatures ) {
        deviceCreateInfoAddOnlyBasicFeatures ( & deviceCreateInfo, device._physicalDevice, & protectedMemoryEnabled );
    } else {
        deviceCreateInfoAddFeatureSets ( & deviceCreateInfo, device._physicalDevice, & protectedMemoryEnabled );
    }

    return device;
}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     CLASS ( Device, ENGINE_PARENT ( VulkanRenderObject ) )
#include <ObjectMapping.hpp>

auto Self :: clear () noexcept -> Self & {
    return * this;
}

Self :: Destructor () noexcept {
    (void) this-> Self :: clear ();
}

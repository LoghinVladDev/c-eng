//
// Created by loghin on 16.01.2022.
//

#include "QueueFamily.hpp"
#include <Logger.hpp>
#include <PhysicalDevice.hpp>
#include <Instance.hpp>
#include <VulkanAPIExceptions.hpp>

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

#define C_ENG_MAP_START     CLASS ( QueueFamily,    PARENT ( cds :: Object ) )
#include <ObjectMapping.hpp>

auto vulkan :: Self :: init (
        __C_ENG_TYPE ( PhysicalDevice )     const * pPhysicalDevice,
        uint32                                      index,
        __C_ENG_TYPE ( QueueFamilyDetails ) const & details
) noexcept ( false ) -> Self & {

/// Requires Vulkan ICD Investigation

//    __C_ENG_TYPE ( PerformanceCounter )             * pPerformanceCounters              = nullptr;
//    __C_ENG_TYPE ( PerformanceCounterDescription )  * pPerformanceCounterDescriptions   = nullptr;

//    cds :: Array < PerformanceCounterProperties > newPerformanceCounterProperties;

    try {

//        uint32 performanceCounterCount;
//        auto result = vulkan :: enumeratePhysicalDeviceQueueFamilyPerformanceQueryCounters (
//                pPhysicalDevice->instance()->handle(),
//                pPhysicalDevice->handle(),
//                index,
//                & performanceCounterCount
//        );
//
//        if ( result != ResultSuccess ) {
//            __C_ENG_LOG_AND_THROW_DETAILED_API_CALL_EXCEPTION ( debug, "enumeratePhysicalDeviceQueueFamilyPerformanceQueryCounters", result );
//        }
//
//        pPerformanceCounters            = new __C_ENG_TYPE ( PerformanceCounter ) [ performanceCounterCount ];
//        pPerformanceCounterDescriptions = new __C_ENG_TYPE ( PerformanceCounterDescription ) [ performanceCounterCount ];
//
//        result = vulkan :: enumeratePhysicalDeviceQueueFamilyPerformanceQueryCounters (
//                pPhysicalDevice->instance()->handle(),
//                pPhysicalDevice->handle(),
//                index,
//                & performanceCounterCount,
//                pPerformanceCounters,
//                pPerformanceCounterDescriptions
//        );
//
//        if ( result != ResultSuccess ) {
//            __C_ENG_LOG_AND_THROW_DETAILED_API_CALL_EXCEPTION ( debug, "enumeratePhysicalDeviceQueueFamilyPerformanceQueryCounters", result );
//        }
//
//        newPerformanceCounterProperties.resize ( performanceCounterCount );
//        for ( uint32 i = 0U; i < performanceCounterCount; ++ i ) {
//            (void) std :: memcpy ( & newPerformanceCounterProperties[static_cast < Index > ( i )].counter,      & pPerformanceCounters[i],              sizeof ( pPerformanceCounters[0] ) );
//            (void) std :: memcpy ( & newPerformanceCounterProperties[static_cast < Index > ( i )].description,  & pPerformanceCounterDescriptions[i],   sizeof ( pPerformanceCounterDescriptions[0] ) );
//        }
//
//        delete[] pPerformanceCounters;
//        delete[] pPerformanceCounterDescriptions;

    } catch ( ... ) {
//        delete[] pPerformanceCounters;
//        delete[] pPerformanceCounterDescriptions;

        throw;
    }

    (void) std :: memcpy ( & this->_details, & details, sizeof ( details ) );
    this->_familyIndex                  = index;
    this->_physicalDevice               = pPhysicalDevice;
//    this->_performanceCounterProperties = std :: move ( newPerformanceCounterProperties );

    return * this;
}

auto vulkan :: Self :: clear () noexcept -> Self & {
    return * this;
}
//
// Created by loghin on 01.01.2022.
//

#include "PhysicalDevice.hpp"

#include <CDS/Array>
#include <Instance.hpp>
#include <VulkanCoreConfig.hpp>
#include <VulkanAPIExceptions.hpp>
#include <Logger.hpp>


using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)


#define C_ENG_MAP_START     CLASS ( PhysicalDevice,     PARENT ( cds :: Object ) )
#include <ObjectMapping.hpp>

static vulkan :: __C_ENG_TYPE ( Instance ) const * pLastQueriedInstance = nullptr;
static Array < vulkan :: Self const > physicalDevices;

static vulkan :: __C_ENG_TYPE ( PhysicalDeviceHandle ) physicalDeviceHandles [ __C_ENG_VULKAN_CORE_PHYSICAL_DEVICE_MAX_COUNT ];

#ifndef NDEBUG

static inline auto logPhysicalDevices () noexcept -> void {
    (void) __C_ENG_TYPE ( Logger ) :: instance().info ( "Found "_s + :: physicalDevices.size() + " vulkan compatible devices : " );

    for ( auto const & device : physicalDevices ) {

        auto deviceAsString = toString(device.details());

        int indent = 4;
        auto rows = deviceAsString.split(',');

        for ( auto & row : rows ) {
            (void) row.trim();

            if ( row.contains("{") || row.contains("[") ) {

                auto inlineRows = row.split("{[");
                bool first = true;

                for ( auto & inlineRow : inlineRows ) {

                    if ( ! first ) {
                        indent += 4;
                        (void) inlineRow.trim();
                    } else {
                        first = false;
                    }

                    (void) __C_ENG_TYPE ( Logger ) :: instance().info ( ( " "_s * indent ) + inlineRow );

                }

            } else {
                auto reduceCount = row.count('}');
                while ( row.contains("}") ) {
                    (void)row.trim().removeSuffix("}");
                }

                reduceCount += row.count(']');
                while ( row.contains("]") ) {
                    (void)row.trim().removeSuffix("]");
                }

                (void) __C_ENG_TYPE ( Logger ) :: instance().info ( ( " "_s * indent ) + row );

                if ( reduceCount > 0U ) {
                    indent -= reduceCount * 4U;
                }
            }
        }
    }
}

#endif

auto vulkan :: Self :: refreshPhysicalDevices (
        __C_ENG_TYPE ( Instance ) const * pInstance
) noexcept (false) -> void {

    if ( pInstance == nullptr ) {
        return;
    }

    uint32 physicalDeviceCount = 0U;

    :: physicalDevices.clear();

    auto result = vulkan :: enumeratePhysicalDevices (
            pInstance->handle(),
            & physicalDeviceCount
    );

    if ( result != ResultSuccess ) {
        __C_ENG_LOG_AND_THROW_DETAILED_API_CALL_EXCEPTION ( error, "enumeratePhysicalDevices", result );
    }

    result = vulkan :: enumeratePhysicalDevices (
            pInstance->handle(),
            & physicalDeviceCount,
            physicalDeviceHandles // NOLINT(clion-misra-cpp2008-5-2-12)
    );

    if ( result != ResultSuccess ) {
        __C_ENG_LOG_AND_THROW_DETAILED_API_CALL_EXCEPTION ( error, "enumeratePhysicalDevices", result );
    }

    for ( uint32 i = 0U; i < physicalDeviceCount; ++ i ) {

        try {

            Self device;

            device._handle = physicalDeviceHandles[i];

            result = vulkan :: getPhysicalDeviceDetails(
                    device.handle(),
                    & device._details
            );

            if (result != ResultSuccess) {
                __C_ENG_LOG_AND_THROW_DETAILED_API_CALL_EXCEPTION ( debug, "getPhysicalDeviceDetails", result );
            }

            (void) :: physicalDevices.pushBack(device);

        } catch ( Exception const & exception ) {
            (void) __C_ENG_TYPE ( Logger ) :: instance().debug ( "Properties acquisition for device failed" );
        }
    }

#ifndef NDEBUG

    logPhysicalDevices();

#endif

    pLastQueriedInstance = pInstance;
}

auto vulkan :: Self :: physicalDevices (
        __C_ENG_TYPE ( Instance ) const * pInstance
) noexcept (false) -> Array < Self const > const & {
    if ( pInstance != nullptr && pLastQueriedInstance != pInstance ) {
        Self :: refreshPhysicalDevices ( pInstance );
    }

    return :: physicalDevices;
}
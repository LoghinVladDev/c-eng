//
// Created by loghin on 01.01.2022.
//

#include "PhysicalDevice.hpp"

#include <CDS/Array>
#include <Instance.hpp>
#include <VulkanAPI.hpp>
#include <Logger.hpp>
#include <CDS/Mutex>
#include <CDS/LockGuard>
#include <Settings.hpp>


using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)


#define C_ENG_MAP_START     CLASS ( PhysicalDevice, ENGINE_PARENT ( VulkanRenderObject ) )
#include <ObjectMapping.hpp>

struct DeviceWithExtensions {
    vulkan :: Type ( PhysicalDeviceHandle )     handle;
    vulkan :: Self :: DeviceExtensionArray      extensionArray;
    bool                                        queried;
};

namespace globals {
    static vulkan :: Type ( Instance ) const * pLastQueriedInstance = nullptr;
    static Array < vulkan :: Self > physicalDevices;
    
    static vulkan :: Type ( PhysicalDeviceHandle )  physicalDeviceHandles [ engine :: vulkan :: config :: physicalDeviceCount ];
    
    static vulkan :: Type ( ExtensionProperties )   extensionPropertiesArray [ engine :: vulkan :: config :: layerExtensionCount ];
    static vulkan :: Self :: DeviceExtension        ungroupedExtensions [ engine :: vulkan :: config :: physicalDeviceCount ] [ engine :: vulkan :: config :: layerExtensionCount ];
    static DeviceWithExtensions                     devicesWithExtensions [ engine :: vulkan :: config :: physicalDeviceCount ];
    static uint32                                   devicesWithExtensionCount;
    static Mutex                                    deviceExtensionLock;
    
    static vulkan :: Type ( PhysicalDeviceHandle )  lastQueriedDevice;
    static DeviceWithExtensions                   * pLastQueriedDeviceExtensions;
};

#ifndef NDEBUG

static inline auto logPhysicalDevices () noexcept -> void {
    (void) __C_ENG_TYPE ( Logger ) :: instance().info ( "Found "_s + globals :: physicalDevices.size() + " vulkan compatible devices : " );

    for ( uint32 i = 0U; i < globals :: physicalDevices.size(); ++ i ) {

        (void) __C_ENG_TYPE ( Logger ) :: instance().info ( " "_s * 4 + "Device " + i );

        auto deviceAsString = toString(globals :: physicalDevices[static_cast < Index > ( i )].details());

        int indent = 8;
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
                    indent -= reduceCount * 4U; // NOLINT(cppcoreguidelines-narrowing-conversions)
                }
            }
        }

        (void) __C_ENG_TYPE ( Logger ) :: instance().info (" "_s * indent + "Device " + i + " Queue Family Properties : ");

        for ( uint32 j = 0U; j < globals :: physicalDevices[static_cast < Index > ( i )].queueFamilies().size(); ++ j ) {
            indent += 4;

            (void) __C_ENG_TYPE ( Logger ) :: instance().info (" "_s * indent + "Family " + j);

            auto queuePropertiesAsString = toString(globals :: physicalDevices[static_cast < Index > ( i )].queueFamilies()[static_cast < Index > ( j )].details());

            auto innerRows = queuePropertiesAsString.split(',');

            for ( auto & row : innerRows ) {
                (void) row.trim();

                if ( row.contains('[') && row.contains(']') ) {

                    auto count = row.count('}');
                    count += row.count(']');

                    (void) row.rtrim('}').rtrim(' ').rtrim(']').rtrim(' ').rtrim('}');

                    auto sides = row.split("=");

                    (void) __C_ENG_TYPE ( Logger ) :: instance().info ( " "_s * indent + sides[0] + " =" );

                    indent += 4;
                    (void) __C_ENG_TYPE ( Logger ) :: instance().info ( " "_s * indent + sides[1].ltrim().removePrefix("[ ").rtrim().removeSuffix(" ]") );

                    indent -= (count + 1U) * 4U; // NOLINT(cppcoreguidelines-narrowing-conversions)

                } else if ( row.contains("{") || row.contains("[") ) {

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
                        indent -= reduceCount * 4U; // NOLINT(cppcoreguidelines-narrowing-conversions)
                    }
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

    cds :: Array < Self > newPhysicalDevices;

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
            globals :: physicalDeviceHandles // NOLINT(clion-misra-cpp2008-5-2-12)
    );

    if ( result != ResultSuccess ) {
        __C_ENG_LOG_AND_THROW_DETAILED_API_CALL_EXCEPTION ( error, "enumeratePhysicalDevices", result );
    }

    for ( uint32 i = 0U; i < physicalDeviceCount; ++ i ) {

        try {

            Self device;

            device._handle      = globals :: physicalDeviceHandles[i];
            device._instance    = pInstance;

            result = vulkan :: getPhysicalDeviceDetails (
                    device.handle(),
                    & device._details
            );

            if (result != ResultSuccess) {
                __C_ENG_LOG_AND_THROW_DETAILED_API_CALL_EXCEPTION ( debug, "getPhysicalDeviceDetails", result );
            }

            (void) newPhysicalDevices.pushBack(device);
            (void) newPhysicalDevices.back().refreshQueueFamilies();

        } catch ( Exception const & exception ) {
            (void) __C_ENG_TYPE ( Logger ) :: instance().debug ( "Properties acquisition for device "_s + i + " failed" );
        }
    }

    globals :: pLastQueriedInstance = pInstance;
    globals :: physicalDevices = std :: move ( newPhysicalDevices );

    {
        LockGuard guard ( globals :: deviceExtensionLock );

        if ( globals :: physicalDevices.size() > engine :: vulkan :: config :: physicalDeviceCount ) {
            throw Type ( VulkanAPIException ) ( "Configuration Size for Physical Device Count is too small" );
        }

        for ( auto const & device : globals :: physicalDevices ) {

            bool addDevice = true;
            for ( uint32 i = 0U; i < globals :: devicesWithExtensionCount; ++ i ) {

                if ( device.handle() == globals :: devicesWithExtensions[i].handle ) {
                    addDevice = false;
                    break;
                }
            }

            if ( addDevice ) {
                globals :: devicesWithExtensions[ globals :: devicesWithExtensionCount ] = {
                        .handle             = device.handle(),
                        .extensionArray    = {
                                .pExtensions    = & globals :: ungroupedExtensions [ globals :: devicesWithExtensionCount ][0],
                                .count          = 0U
                        },
                        .queried            = false
                };

                ++ globals :: devicesWithExtensionCount;
            }
        }
    }

#ifndef NDEBUG

    logPhysicalDevices();

#endif
}

auto vulkan :: Self :: refreshQueueFamilies () noexcept (false) -> Self & {

    __C_ENG_TYPE ( QueueFamilyDetails ) * pQueueFamilyDetails = nullptr;

    try {

        uint32 queueFamilyCount;
        auto result = vulkan :: getPhysicalDeviceQueueFamilyDetails (
                this->handle(),
                & queueFamilyCount
        );

        if ( result != ResultSuccess ) {
            __C_ENG_LOG_AND_THROW_DETAILED_API_CALL_EXCEPTION ( debug, "getPhysicalDeviceQueueFamilyDetails", result );
        }

        pQueueFamilyDetails = new __C_ENG_TYPE ( QueueFamilyDetails ) [ queueFamilyCount ];
        result = vulkan :: getPhysicalDeviceQueueFamilyDetails(
                this->handle(),
                & queueFamilyCount,
                & pQueueFamilyDetails[0]
        );

        if ( result != ResultSuccess ) {
            __C_ENG_LOG_AND_THROW_DETAILED_API_CALL_EXCEPTION ( debug, "getPhysicalDeviceQueueFamilyDetails", result );
        }

        this->_queueFamilies.resize ( queueFamilyCount );
        for ( uint32 queueFamilyIndex = 0U; queueFamilyIndex < queueFamilyCount; ++ queueFamilyIndex ) {
            (void) this->_queueFamilies[static_cast < Index > ( queueFamilyIndex )].init(
                    this,
                    queueFamilyIndex,
                    pQueueFamilyDetails[queueFamilyIndex]
            );
        }

        delete[] pQueueFamilyDetails;

    } catch ( ... ) {
        delete[] pQueueFamilyDetails;
        throw;
    }

    return * this;
}

auto vulkan :: Self :: physicalDevices (
        __C_ENG_TYPE ( Instance ) const * pInstance
) noexcept (false) -> Array < Self > const & {
    if ( pInstance != nullptr && globals :: pLastQueriedInstance != pInstance ) {
        Self :: refreshPhysicalDevices ( pInstance );
    }

    return globals :: physicalDevices;
}

auto vulkan :: Self :: renderScore () const noexcept -> uint32 {
    uint32 score = 0U;

    if ( this->details().basicFeatures.geometryShader == VK_FALSE ) {
        return 0U;
    }

    if ( this->details().basicProperties.deviceType == PhysicalDeviceTypeDedicatedGPU ) {
        score += dedicatedGPUBias;
    }

    score += this->details().basicProperties.limits.maxImageDimension2D;

    return score;
}

static inline auto getDeviceExtensions (
        vulkan :: Type ( PhysicalDeviceHandle ) handle
) noexcept (false) -> DeviceWithExtensions & {

    if ( handle == nullptr ) {
        throw vulkan :: Type ( VulkanAPIException ) ( "Device not acquired. Cannot retrieve properties" );
    }

    if ( handle == globals :: lastQueriedDevice ) {
        return * globals :: pLastQueriedDeviceExtensions;
    }

    for ( uint32 i = 0U; i < globals :: devicesWithExtensionCount; ++ i ) {
        if ( globals :: devicesWithExtensions[i].handle == handle ) {

            globals :: lastQueriedDevice = handle;
            globals :: pLastQueriedDeviceExtensions = & globals :: devicesWithExtensions[i];

            return globals :: devicesWithExtensions[i];
        }
    }

    throw vulkan :: Type ( VulkanAPIException ) ( "Requested device not found. Cannot acquire extensions" );
}

static inline auto refreshExtensions (
        DeviceWithExtensions & rDeviceWithExtensions,
        StringLiteral          deviceName
) noexcept (false) -> void {

    using namespace vulkan; // NOLINT(clion-misra-cpp2008-7-3-4)
    LockGuard guard ( globals :: deviceExtensionLock );

    auto result = enumeratePhysicalDeviceExtensionProperties (
            rDeviceWithExtensions.handle,
            & rDeviceWithExtensions.extensionArray.count
    );

    if ( result != ResultSuccess ) {
        __C_ENG_LOG_AND_THROW_DETAILED_API_CALL_EXCEPTION ( error, "enumeratePhysicalDeviceExtensionProperties", result );
    }

    result = enumeratePhysicalDeviceExtensionProperties (
            rDeviceWithExtensions.handle,
            & rDeviceWithExtensions.extensionArray.count,
            & globals :: extensionPropertiesArray[0]
    );

    if ( result != ResultSuccess ) {
        __C_ENG_LOG_AND_THROW_DETAILED_API_CALL_EXCEPTION ( error, "enumeratePhysicalDeviceExtensionProperties", result );
    }

    for ( uint32 i = 0U; i < rDeviceWithExtensions.extensionArray.count; ++ i ) {
        (void) std :: memcpy (
                & rDeviceWithExtensions.extensionArray.pExtensions[i].properties,
                & globals :: extensionPropertiesArray[i],
                sizeof ( globals :: extensionPropertiesArray[i] )
        );

        rDeviceWithExtensions.extensionArray.pExtensions[i].enabled =
                Type ( Settings ) :: instance().get (
                        String ( deviceName ) +
                        "_Extension_" +
                        rDeviceWithExtensions.extensionArray.pExtensions[i].properties.name +
                        "_enabled"
                );
    }

    rDeviceWithExtensions.queried = true;
}

auto vulkan :: Self :: extensions () const noexcept (false) -> DeviceExtensionArray const & {
    auto & deviceExtensions = getDeviceExtensions ( this->handle() );

    if ( ! deviceExtensions.queried ) {
        :: refreshExtensions ( deviceExtensions, this->details().basicProperties.deviceName );
    }

    return deviceExtensions.extensionArray;
}

auto vulkan :: Self :: refreshExtensions () noexcept ( false ) -> Self & {
    :: refreshExtensions ( getDeviceExtensions ( this->handle() ),this->details().basicProperties.deviceName );
    return * this;
}

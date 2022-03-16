//
// Created by loghin on 16.02.2022.
//

#include <calls/VulkanAPICallsPrivate.hpp>
#include <calls/VulkanAPICallsConversion.hpp>
#include <CDS/Mutex>

#include <calls/util/AllocationHandler.hpp>
#include <calls/util/ContextManager.hpp>
#include <calls/util/APICaller.hpp>
#include <calls/util/LastCreatedInstance.hpp>

#define C_ENG_MAP_START     SOURCE
#include <ObjectMapping.hpp>

using namespace cds;
using namespace engine;
using namespace vulkan;


#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: enumerateInstanceVersion (
        uint32 * pVersion
) noexcept -> vulkan :: Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pVersion == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return static_cast < Type ( Result ) > (
            APICaller.vkEnumerateInstanceVersion (
                    pVersion
            )
    );
}
#endif


#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: getFunctionAddress (
        StringLiteral           functionName,
        FunctionHandleAddress   pFunctionHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if (
            pFunctionHandle == nullptr ||
            functionName    == nullptr
    ) {
        return ResultErrorIllegalArgument;
    }

#endif

    * pFunctionHandle = reinterpret_cast < void * > (
            vkGetInstanceProcAddr (
                    nullptr,
                    functionName
            )
    );

    if ( * pFunctionHandle == nullptr ) {
        return ResultErrorFunctionHandleNotFound;
    }

    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: getInstanceFunctionAddress (
        Type ( InstanceHandle ) instanceHandle,
        StringLiteral           functionName,
        FunctionHandleAddress   pFunctionHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if (
            pFunctionHandle == nullptr ||
            functionName    == nullptr
    ) {
        return ResultErrorIllegalArgument;
    }

#endif

    * pFunctionHandle = reinterpret_cast < void * > (
            vkGetInstanceProcAddr (
                    instanceHandle,
                    functionName
            )
    );

    if ( * pFunctionHandle == nullptr ) {
        return ResultErrorFunctionHandleNotFound;
    }

    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: getDeviceFunctionAddress (
        Type ( DeviceHandle )   deviceHandle,
        StringLiteral           functionName,
        FunctionHandleAddress   pFunctionHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if (
            pFunctionHandle == nullptr ||
            functionName    == nullptr ||
            deviceHandle    == nullptr
    ) {
        return ResultErrorIllegalArgument;
    }

#endif

    if (
            auto result = APICaller.vkGetDeviceProcAddr (
                    reinterpret_cast < void (**)() > ( pFunctionHandle ),
                    deviceHandle,
                    functionName
            ); result != ResultSuccess
    ) {
        return result;
    }

    if ( * pFunctionHandle == nullptr ) {
        return ResultErrorFunctionHandleNotFound;
    }

    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: createInstance (
        Type ( InstanceCreateInfo )     const * pCreateInfo,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks,
        Type ( InstanceHandle )               * pInstanceHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if (
            pCreateInfo     == nullptr ||
            pInstanceHandle == nullptr
    ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    if (
            auto result = APICaller.vkCreateInstance (
                    prepareContext ( & context->create.instance, pCreateInfo ),
                    AllocatorHandler :: apply ( pAllocationCallbacks ),
                    pInstanceHandle
            ); result != ResultSuccess
    ) {
        return result;
    }

    LastCreatedInstance :: set ( * pInstanceHandle );
    APICaller.setInstanceExtensions ( * pInstanceHandle, & context->create.instance.instance );
    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: enumerateInstanceLayerProperties (
        cds :: uint32               * pCount,
        Type ( LayerProperties )    * pProperties
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pCount == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    if ( pProperties == nullptr ) {
        return APICaller.vkEnumerateInstanceLayerProperties (
                pCount,
                nullptr
        );
    }

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( * pCount > engine :: vulkan :: config :: layerCount ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

    auto context = ContextManager :: acquire();

    if (
            auto result = APICaller.vkEnumerateInstanceLayerProperties (
                    pCount,
                    & context.data().enumerate.layerProperties.properties[0]
            ); result != ResultSuccess
    ) {
        return result;
    }

    for ( uint32 i = 0U; i < * pCount; ++ i ) {
        (void) fromVulkanFormat ( & pProperties[i], & context.data().enumerate.layerProperties.properties[i] );
    }

    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: enumeratePhysicalDeviceLayerProperties (
        Type ( PhysicalDeviceHandle ) physicalDeviceHandle,
        cds :: uint32               * pCount,
        Type ( LayerProperties )    * pProperties
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( physicalDeviceHandle == nullptr || pCount == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    if ( pProperties == nullptr ) {
        return APICaller.vkEnumerateDeviceLayerProperties (
                physicalDeviceHandle,
                pCount,
                nullptr
        );
    }

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( * pCount > engine :: vulkan :: config :: layerCount ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

    auto context = ContextManager :: acquire();

    if (
        auto result = APICaller.vkEnumerateDeviceLayerProperties (
                physicalDeviceHandle,
                pCount,
                & context.data().enumerate.layerProperties.properties[0]
        ); result != ResultSuccess
    ) {
        return result;
    }

    for ( uint32 i = 0U; i < * pCount; ++ i ) {
        (void) fromVulkanFormat ( & pProperties[i], & context.data().enumerate.layerProperties.properties[i] );
    }

    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: enumerateInstanceExtensionProperties (
        StringLiteral                   layerName,
        uint32                        * pCount,
        Type ( ExtensionProperties )  * pProperties
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( layerName == nullptr || pCount == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    if ( pProperties == nullptr ) {
        return APICaller.vkEnumerateInstanceExtensionProperties (
                layerName,
                pCount,
                nullptr
        );
    }

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( * pCount > engine :: vulkan :: config :: layerExtensionCount ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

    auto context = ContextManager :: acquire();

    if (
        auto result = APICaller.vkEnumerateInstanceExtensionProperties (
                layerName,
                pCount,
                & context.data().enumerate.extensionProperties.properties[0]
        ); result != ResultSuccess
    ) {
        return result;
    }

    for ( uint32 i = 0U; i < * pCount; ++ i ) {
        (void) fromVulkanFormat ( & pProperties[i], & context.data().enumerate.extensionProperties.properties[i] );
    }

    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: enumeratePhysicalDevices (
        Type ( InstanceHandle )           handle,
        uint32                          * pCount,
        Type ( PhysicalDeviceHandle )   * pDevices
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( handle == nullptr || pCount == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    if ( pDevices == nullptr ) {
        return APICaller.vkEnumeratePhysicalDevices (
                handle,
                pCount,
                nullptr
        );
    }

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( * pCount > engine :: vulkan :: config :: physicalDeviceCount ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

    auto context = ContextManager :: acquire();

    if (
            auto result = APICaller.vkEnumeratePhysicalDevices (
                    handle,
                    pCount,
                    & context.data().enumerate.physicalDevices.devices[0]
            ); result != ResultSuccess
    ) {
        return result;
    }

    (void) std :: memcpy ( & pDevices[0], & context.data().enumerate.physicalDevices.devices[0], sizeof ( Type ( PhysicalDeviceHandle ) ) * ( * pCount ) );

    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
auto engine :: vulkan :: enumeratePhysicalDeviceQueueFamilyPerformanceQueryCounters (
        Type ( PhysicalDeviceHandle )             physicalDeviceHandle,
        uint32                                    queueFamilyIndex,
        uint32                                  * pCount,
        Type ( PerformanceCounter )             * pCounters,
        Type ( PerformanceCounterDescription )  * pDescriptions
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( physicalDeviceHandle == nullptr || pCount == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    if ( pCounters == nullptr && pDescriptions == nullptr ) {
        return APICaller.vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR (
                physicalDeviceHandle,
                queueFamilyIndex,
                pCount,
                nullptr,
                nullptr
        );
    }

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( * pCount > engine :: vulkan :: config :: queueFamilyPerformanceCounterCount ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

    auto context = ContextManager :: acquire();

    if (
            auto result = APICaller.vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR (
                    physicalDeviceHandle,
                    queueFamilyIndex,
                    pCount,
                    & context.data().enumerate.physicalDeviceQueueFamilyPerformanceQueryCounters.counters[0],
                    & context.data().enumerate.physicalDeviceQueueFamilyPerformanceQueryCounters.descriptions[0]
            ); result != ResultSuccess
    ) {
        return result;
    }

    for ( uint32 i = 0U; i < * pCount; ++ i ) {
        (void) fromVulkanFormat ( & pCounters[i],       & context.data().enumerate.physicalDeviceQueueFamilyPerformanceQueryCounters.counters[i] );
        (void) fromVulkanFormat ( & pDescriptions[i],   & context.data().enumerate.physicalDeviceQueueFamilyPerformanceQueryCounters.descriptions[i] );
    }

    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto engine :: vulkan :: enumeratePhysicalDeviceGroups (
        Type ( InstanceHandle )                  instanceHandle,
        uint32                                 * pCount,
        Type ( PhysicalDeviceGroupProperties ) * pProperties
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( instanceHandle == nullptr || pProperties == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    if ( pProperties == nullptr ) {
        return APICaller.vkEnumeratePhysicalDeviceGroups (
                instanceHandle,
                pCount,
                nullptr
        );
    }

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( * pCount > engine :: vulkan :: config :: physicalDeviceGroupCount ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

    auto context = ContextManager :: acquire();

    if (
            auto result = APICaller.vkEnumeratePhysicalDeviceGroups (
                    instanceHandle,
                    pCount,
                    & context.data().enumerate.physicalDeviceGroups.properties [0]
            ); result != ResultSuccess
    ) {
        return result;
    }

    for ( uint32 i = 0U; i< * pCount; ++ i ) {
        (void) fromVulkanFormat ( & pProperties[i], & context.data().enumerate.physicalDeviceGroups.properties[i] );
    }

    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: enumeratePhysicalDeviceExtensionProperties (
        Type ( PhysicalDeviceHandle )   handle,
        uint32                        * pCount,
        Type ( ExtensionProperties )  * pProperties
) noexcept -> Type ( Result ) {

    return enumeratePhysicalDeviceExtensionProperties (
            handle,
            nullptr,
            pCount,
            pProperties
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: enumeratePhysicalDeviceExtensionProperties (
        Type ( PhysicalDeviceHandle )   handle,
        StringLiteral                   layerName,
        uint32                        * pCount,
        Type ( ExtensionProperties )  * pProperties
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( handle == nullptr || pCount == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    if ( pProperties == nullptr ) {
        return APICaller.vkEnumerateDeviceExtensionProperties (
                handle,
                layerName,
                pCount,
                nullptr
        );
    }

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( * pCount > engine :: vulkan :: config :: layerExtensionCount ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

    auto context = ContextManager :: acquire();

    if (
            auto result = APICaller.vkEnumerateDeviceExtensionProperties (
                    handle,
                    layerName,
                    pCount,
                    & context.data().enumerate.extensionProperties.properties[0]
            ); result != ResultSuccess
    ) {
        return result;
    }

    for ( uint32 i = 0U; i < * pCount; ++ i ) {
        (void) fromVulkanFormat ( & pProperties[i], & context.data().enumerate.extensionProperties.properties[i] );
    }

    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_UTILS_AVAILABLE
auto engine :: vulkan :: createDebugMessenger (
        Type ( InstanceHandle )                     instanceHandle,
        Type ( DebugMessengerCreateInfo )   const * pCreateInfo,
        Type ( AllocationCallbacks )        const * pAllocationCallbacks,
        Type ( DebugMessengerHandle )             * pHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( instanceHandle == nullptr || pCreateInfo == nullptr || pHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkCreateDebugUtilsMessengerEXT (
            instanceHandle,
            toVulkanFormat ( & context.data().create.instance.debugMessenger, pCreateInfo ),
            AllocatorHandler :: apply ( pAllocationCallbacks ),
            pHandle
    );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE
auto engine :: vulkan :: createSurface (
        Type ( InstanceHandle )                 instanceHandle,
        GLFWwindow                            * pWindowHandle,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks,
        Type ( SurfaceHandle )                * pSurfaceHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if (
            instanceHandle  == nullptr ||
            pWindowHandle   == nullptr ||
            pSurfaceHandle  == nullptr
    ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return static_cast < Type ( Result ) > (
            glfwCreateWindowSurface (
                    instanceHandle,
                    pWindowHandle,
                    AllocatorHandler :: apply ( pAllocationCallbacks ),
                    pSurfaceHandle
            )
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: createDevice (
        Type ( PhysicalDeviceHandle )           physicalDeviceHandle,
        Type ( DeviceCreateInfo )       const * pCreateInfo,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks,
        Type ( DeviceHandle )                 * pDeviceHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if (
            physicalDeviceHandle    == nullptr ||
            pCreateInfo             == nullptr ||
            pDeviceHandle           == nullptr
    ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkCreateDevice (
            physicalDeviceHandle,
            prepareContext ( & ContextManager :: acquire().data().create.device, pCreateInfo ),
            AllocatorHandler :: apply ( pAllocationCallbacks ),
            pDeviceHandle
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: destroyInstance (
        Type ( InstanceHandle )                 handle,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( handle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkDestroyInstance ( handle, AllocatorHandler :: apply ( pAllocationCallbacks ) );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_UTILS_AVAILABLE
auto engine :: vulkan :: destroyDebugMessenger (
        Type ( InstanceHandle )                 instanceHandle,
        Type ( DebugMessengerHandle )           debugMessengerHandle,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( instanceHandle == nullptr || debugMessengerHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkDestroyDebugUtilsMessengerEXT (
            instanceHandle,
            debugMessengerHandle,
            AllocatorHandler :: apply ( pAllocationCallbacks )
    );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE
auto engine :: vulkan :: destroySurface (
        Type ( InstanceHandle )                 instanceHandle,
        Type ( SurfaceHandle )                  surfaceHandle,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( instanceHandle == nullptr || surfaceHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkDestroySurfaceKHR (
            instanceHandle,
            surfaceHandle,
            AllocatorHandler :: apply ( pAllocationCallbacks )
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: destroyDevice (
        Type ( DeviceHandle )                   handle,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( handle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkDestroyDevice (
            handle,
            AllocatorHandler :: apply ( pAllocationCallbacks )
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: getPhysicalDeviceProperties (
        Type ( PhysicalDeviceHandle )       handle,
        Type ( PhysicalDeviceProperties ) * pProperties
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( handle == nullptr || pProperties == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif
    auto context = ContextManager :: acquire();

    if (
            auto result = APICaller.vkGetPhysicalDeviceProperties (
                    handle,
                    & context.data().get.physicalDevice.properties.properties.properties
            ); result != ResultSuccess
    ) {
        return result;
    }

    (void) fromVulkanFormat (
            pProperties,
            & context.data().get.physicalDevice.properties.properties.properties
    );

    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: getPhysicalDeviceFeatures (
        Type ( PhysicalDeviceHandle )       physicalDeviceHandle,
        Type ( PhysicalDeviceFeatures )   * pFeatures
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( physicalDeviceHandle == nullptr || pFeatures == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    if (
            auto result = APICaller.vkGetPhysicalDeviceFeatures (
                    physicalDeviceHandle,
                    & context.data().get.physicalDevice.features.features.features
            ); result != ResultSuccess
    ) {
        return result;
    }

    (void) fromVulkanFormat ( pFeatures, & context.data().get.physicalDevice.features.features.features );
    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto engine :: vulkan :: getPhysicalDeviceProperties (
        Type ( PhysicalDeviceHandle )                 handle,
        Type ( PhysicalDeviceExtendedProperties )   * pProperties
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( handle == nullptr || pProperties == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if (
            auto result = APICaller.vkGetPhysicalDeviceProperties (
                    handle,
                    & context.data().get.physicalDevice.properties.properties.properties
            ); result != ResultSuccess
    ) {
        return result;
    }

    if (
        auto version = uInt32ToInstanceVersion ( context.data().get.physicalDevice.properties.properties.properties.apiVersion );
            vulkan :: compare ( version, versionConstants :: version11 ) == CompareResultLess
    ) {
        return ResultErrorIncompatibleVersion;
    }

#endif

    if (
            auto result = APICaller.vkGetPhysicalDeviceProperties2 (
                    handle,
                    prepareContext ( & context.data().get.physicalDevice.properties, pProperties )
            ); result != ResultSuccess
    ) {
        return result;
    }

    extractContext ( pProperties, & context.data().get.physicalDevice.properties );
    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto engine :: vulkan :: getPhysicalDeviceFeatures (
        Type ( PhysicalDeviceHandle )               physicalDeviceHandle,
        Type ( PhysicalDeviceExtendedFeatures )   * pFeatures
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( physicalDeviceHandle == nullptr || pFeatures == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if (
            auto result = APICaller.vkGetPhysicalDeviceProperties (
                    physicalDeviceHandle,
                    & context.data().get.physicalDevice.properties.properties.properties
            ); result != ResultSuccess
    ) {
        return result;
    }

    if (
        auto version = uInt32ToInstanceVersion ( context.data().get.physicalDevice.properties.properties.properties.apiVersion );
            vulkan :: compare ( version, versionConstants :: version11 ) == CompareResultLess
    ) {
        return ResultErrorIncompatibleVersion;
    }

#endif

    if (
            auto result = APICaller.vkGetPhysicalDeviceFeatures2 (
                    physicalDeviceHandle,
                    prepareContext ( & context.data().get.physicalDevice.features, pFeatures )
            ); result != ResultSuccess
    ) {
        return result;
    }

    extractContext ( pFeatures, & context.data().get.physicalDevice.features );
    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto engine :: vulkan :: getPhysicalDeviceDetails (
        Type ( PhysicalDeviceHandle )     handle,
        Type ( PhysicalDeviceDetails )  * pDetails
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( handle == nullptr || pDetails == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    Type ( PhysicalDeviceExtendedProperties )   extendedProperties {};
    Type ( PhysicalDeviceExtendedFeatures )     extendedFeatures   {};

    createChain ( pDetails, & extendedProperties, & extendedFeatures );

    if (
            auto result = getPhysicalDeviceProperties ( handle, & extendedProperties );
            result != ResultSuccess
    ) {
        return result;
    }

    if (
            auto result = getPhysicalDeviceFeatures ( handle, & extendedFeatures );
            result != ResultSuccess
    ) {
        return result;
    }

    for (
            auto pCurrent = reinterpret_cast < Type ( GenericOutStructure ) * > ( & extendedProperties );
            pCurrent != nullptr;
    ) {
        auto pCopy = pCurrent;
        pCurrent = pCurrent->pNext;
        pCopy->pNext = nullptr;
    }

    for (
            auto pCurrent = reinterpret_cast < Type ( GenericOutStructure ) * > ( & extendedFeatures );
            pCurrent != nullptr;
    ) {
        auto pCopy = pCurrent;
        pCurrent = pCurrent->pNext;
        pCopy->pNext = nullptr;
    }

    (void) std :: memcpy ( & pDetails->basicProperties, & extendedProperties.properties, sizeof ( pDetails->basicProperties ) );
    (void) std :: memcpy ( & pDetails->basicFeatures,   & extendedFeatures.features,     sizeof ( pDetails->basicFeatures ) );

    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto engine :: vulkan :: utility :: chainFeaturesFromDetails (
        Type ( PhysicalDeviceExtendedFeatures )       * pExtendedFeatures,
        Type ( PhysicalDeviceDetails )                * pDetails
) noexcept -> void {
    createChain ( pDetails, nullptr, pExtendedFeatures ); // NOLINT(clion-misra-cpp2008-5-2-5)
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: getPhysicalDeviceQueueFamilyProperties (
        Type ( PhysicalDeviceHandle )     physicalDeviceHandle,
        uint32                          * pCount,
        Type ( QueueFamilyProperties )  * pProperties
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( physicalDeviceHandle == nullptr || pCount == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    if ( pProperties == nullptr ) {
        return APICaller.vkGetPhysicalDeviceQueueFamilyProperties (
                physicalDeviceHandle,
                pCount,
                nullptr
        );
    }

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( * pCount > engine :: vulkan :: config :: queueFamilyCount ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

    auto context = ContextManager :: acquire();

    if (
            auto result = APICaller.vkGetPhysicalDeviceQueueFamilyProperties (
                    physicalDeviceHandle,
                    pCount,
                    & context.data().get.physicalDevice.queueFamilyProperties.properties[0]
            ); result != ResultSuccess
    ) {
        return result;
    }

    for ( uint32 i = 0U; i < * pCount; ++ i ) {
        (void) fromVulkanFormat ( & pProperties[i], & context.data().get.physicalDevice.queueFamilyProperties.properties[i] );
    }

    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto engine :: vulkan :: getPhysicalDeviceQueueFamilyProperties (
        Type ( PhysicalDeviceHandle )             physicalDeviceHandle,
        uint32                                  * pCount,
        Type ( QueueFamilyExtendedProperties )  * pProperties
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( physicalDeviceHandle == nullptr || pCount == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    if ( pProperties == nullptr ) {
        return APICaller.vkGetPhysicalDeviceQueueFamilyProperties2 (
                physicalDeviceHandle,
                pCount,
                nullptr
        );
    }

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( * pCount > engine :: vulkan :: config :: queueFamilyCount ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

    auto context = ContextManager :: acquire();

    if (
            auto result = APICaller.vkGetPhysicalDeviceQueueFamilyProperties2 (
                    physicalDeviceHandle,
                    pCount,
                    prepareContext ( & context.data().get.physicalDevice.queueFamilyProperties, * pCount, pProperties )
            ); result != ResultSuccess
    ) {
        return result;
    }

    extractContext (
            * pCount,
            & pProperties[0],
            & context.data().get.physicalDevice.queueFamilyProperties
    );

    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto engine :: vulkan :: getPhysicalDeviceQueueFamilyDetails (
        Type ( PhysicalDeviceHandle )   handle,
        uint32                        * pCount,
        Type ( QueueFamilyDetails )   * pDetails
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( handle == nullptr || pCount == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    if ( pDetails == nullptr ) {
        return APICaller.vkGetPhysicalDeviceQueueFamilyProperties (
                handle,
                pCount,
                nullptr
        );

        return ResultSuccess;
    }

    Type ( QueueFamilyExtendedProperties ) extendedProperties [ engine :: vulkan :: config :: queueFamilyCount ];

    createChain ( * pCount, & pDetails[0], & extendedProperties[0] );

    if (
            auto result = getPhysicalDeviceQueueFamilyProperties (
                    handle,
                    pCount,
                    & extendedProperties[0]
            ); result != ResultSuccess
    ) {
        return result;
    }

    for ( uint32 i = 0U; i < * pCount; ++ i ) {
        auto pCurrent = reinterpret_cast < Type ( GenericOutStructure * ) > ( & extendedProperties[i] );
        while ( pCurrent != nullptr ) {
            auto pCopy = pCurrent;
            pCurrent = pCurrent->pNext;
            pCopy->pNext = nullptr;
        }

        (void) std :: memcpy ( & pDetails[i].properties, & extendedProperties[i].properties, sizeof ( pDetails[i].properties ) );
    }

    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE
auto engine :: vulkan :: getPhysicalDeviceSurfaceSupport (
        Type ( PhysicalDeviceHandle )       deviceHandle,
        cds :: uint32                       queueFamilyIndex,
        Type ( SurfaceHandle )              surfaceHandle,
        bool                              * pSupport
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if (
            deviceHandle    == nullptr ||
            surfaceHandle   == nullptr ||
            pSupport        == nullptr
    ) {
        return ResultErrorIllegalArgument;
    }

#endif

    Type ( Bool ) support = VK_FALSE;

    if (
            auto result = APICaller.vkGetPhysicalDeviceSurfaceSupportKHR (
                    deviceHandle,
                    queueFamilyIndex,
                    surfaceHandle,
                    & support
            ); result != ResultSuccess
    ) {
        return result;
    }

    * pSupport = support == VK_TRUE;

    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: getDeviceQueue (
        Type ( DeviceHandle )   deviceHandle,
        uint32                  queueFamilyIndex,
        uint32                  queueIndex,
        Type ( QueueHandle )  * pQueueHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pQueueHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkGetDeviceQueue (
            deviceHandle,
            queueFamilyIndex,
            queueIndex,
            pQueueHandle
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto engine :: vulkan :: getDeviceQueue (
        Type ( DeviceHandle )               deviceHandle,
        Type ( DeviceQueueInfo )    const * pQueueInfo,
        Type ( QueueHandle )              * pQueueHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pQueueHandle == nullptr || pQueueInfo == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkGetDeviceQueue2 (
            deviceHandle,
            toVulkanFormat ( & context.data().get.deviceQueue.info2, pQueueInfo ),
            pQueueHandle
    );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE
auto engine :: vulkan :: getPhysicalDeviceSurfaceCapabilities (
        Type ( PhysicalDeviceHandle )   deviceHandle,
        Type ( SurfaceHandle )          surfaceHandle,
        Type ( SurfaceCapabilities )  * pSurfaceCapabilities
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || surfaceHandle == nullptr || pSurfaceCapabilities == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    if (
            auto result = APICaller.vkGetPhysicalDeviceSurfaceCapabilitiesKHR (
                    deviceHandle,
                    surfaceHandle,
                    & context.data().get.surface.capabilities
            ); result != ResultSuccess
    ) {
        return result;
    }

    (void) fromVulkanFormat ( pSurfaceCapabilities, & context.data().get.surface.capabilities );
    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE
auto engine :: vulkan :: getPhysicalDeviceSurfaceFormats (
        Type ( PhysicalDeviceHandle )   deviceHandle,
        Type ( SurfaceHandle )          surfaceHandle,
        uint32                        * pCount,
        Type ( SurfaceFormat )        * pFormats
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || surfaceHandle == nullptr || pCount == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    if ( pFormats == nullptr ) {
        return APICaller.vkGetPhysicalDeviceSurfaceFormatsKHR (
                deviceHandle,
                surfaceHandle,
                pCount,
                nullptr
        );
    }

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( * pCount > engine :: vulkan :: config :: surfaceFormatCount ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

    auto context = ContextManager :: acquire();

    if (
            auto result = APICaller.vkGetPhysicalDeviceSurfaceFormatsKHR (
                    deviceHandle,
                    surfaceHandle,
                    pCount,
                    & context.data().get.surface.formats[0]
            ); result != ResultSuccess
    ) {
        return result;
    }

    for ( uint32 i = 0U; i < * pCount; ++ i ) {
        (void) fromVulkanFormat ( & pFormats [i], & context.data().get.surface.formats[i] );
    }

    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE
auto engine :: vulkan :: getPhysicalDeviceSurfacePresentModes (
        Type ( PhysicalDeviceHandle )   deviceHandle,
        Type ( SurfaceHandle )          surfaceHandle,
        uint32                        * pCount,
        Type ( PresentMode )          * pPresentModes
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || surfaceHandle == nullptr || pCount == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    if ( pPresentModes == nullptr ) {
        return APICaller.vkGetPhysicalDeviceSurfacePresentModesKHR (
                deviceHandle,
                surfaceHandle,
                pCount,
                nullptr
        );
    }

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( * pCount > engine :: vulkan :: config :: surfacePresentModeCount ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

    auto context = ContextManager :: acquire();

    if (
            auto result = APICaller.vkGetPhysicalDeviceSurfacePresentModesKHR (
                    deviceHandle,
                    surfaceHandle,
                    pCount,
                    & context.data().get.surface.presentModes[0]
            ); result != ResultSuccess
    ) {
        return result;
    }

    for ( uint32 i = 0U; i < * pCount; ++ i ) {
        pPresentModes[i] = static_cast < Type ( PresentMode ) > ( context.data().get.surface.presentModes[i] );
    }

    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISPLAY_SURFACE_COUNTER_AVAILABLE
auto engine :: vulkan :: getPhysicalDeviceSurfaceCapabilities (
        Type ( PhysicalDeviceHandle )   deviceHandle,
        Type ( SurfaceHandle )          surfaceHandle,
        Type ( SurfaceCapabilities2 ) * pSurfaceCapabilities
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || surfaceHandle == nullptr || pSurfaceCapabilities == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    if (
            auto result = APICaller.vkGetPhysicalDeviceSurfaceCapabilities2EXT (
                    deviceHandle,
                    surfaceHandle,
                    & context.data().get.surface.capabilities2
            ); result != ResultSuccess
    ) {
        return result;
    }

    (void) fromVulkanFormat ( pSurfaceCapabilities, & context.data().get.surface.capabilities2 );
    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_GET_SURFACE_CAPABILITIES_AVAILABLE
auto engine :: vulkan :: getPhysicalDeviceSurfaceFormats (
        Type ( PhysicalDeviceHandle )               deviceHandle,
        Type ( PhysicalDeviceSurfaceInfo )  const * pSurfaceInfo,
        uint32                                    * pCount,
        Type ( SurfaceFormat2 )                   * pFormats
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pSurfaceInfo == nullptr || pCount == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    if ( pFormats == nullptr ) {
        return APICaller.vkGetPhysicalDeviceSurfaceFormats2KHR (
                deviceHandle,
                prepareContext ( & context.data().get.surface, pSurfaceInfo ),
                pCount,
                nullptr
        );
    }

    if ( * pCount > engine :: vulkan :: config :: surfaceFormatCount ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

    if (
            auto result = APICaller.vkGetPhysicalDeviceSurfaceFormats2KHR (
                    deviceHandle,
                    prepareContext ( & context.data().get.surface, pSurfaceInfo ),
                    pCount,
                    & context.data().get.surface.formats2[0]
            ); result != ResultSuccess
    ) {
        return result;
    }

    for ( uint32 i = 0U; i < * pCount; ++ i ) {
        (void) fromVulkanFormat ( & pFormats[i], & context.data().get.surface.formats2[0] );
    }

    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FULL_SCREEN_EXCLUSIVE_AVAILABLE
auto engine :: vulkan :: getPhysicalDeviceSurfacePresentModes (
        Type ( PhysicalDeviceHandle )               deviceHandle,
        Type ( PhysicalDeviceSurfaceInfo )  const * pSurfaceInfo,
        uint32                                    * pCount,
        Type ( PresentMode )                      * pPresentModes
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pSurfaceInfo == nullptr || pPresentModeCount == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    if ( pPresentModes == nullptr ) {
        return APICaller.vkGetPhysicalDeviceSurfacePresentModes2EXT (
                deviceHandle,
                prepareContext ( & context.data().get.surface.surfaceInfo2, pSurfaceInfo ),
                pCount,
                nullptr
        );
    }

    if ( * pCount > __C_ENG_VULKAN_CORE_SURFACE_PRESENT_MODE_MAX_COUNT ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

    if (
            auto result = APICaller.vkGetPhysicalDeviceSurfacePresentModes2EXT (
                    deviceHandle,
                    prepareContext ( & context.data().get.surface.surfaceInfo2, pSurfaceInfo ),
                    pCount,
                    & context.data().get.surface.presentModes[0]
            ); result != ResultSuccess
    ) {
        return result;
    }

    for ( uint32 i = 0U; i < * pCount; ++ i ) {
        pPresentModes [i] = static_cast < Type ( PresentMode ) > ( context.data().get.surface.presentModes[i] );
    }

    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE
auto engine :: vulkan :: createSwapChain (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( SwapChainCreateInfo )    const * pCreateInfo,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks,
        Type ( SwapChainHandle )              * pHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pCreateInfo == nullptr || pHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkCreateSwapchainKHR (
            deviceHandle,
            prepareContext ( & context.data().create.swapChain, pCreateInfo ),
            AllocatorHandler :: apply ( pAllocationCallbacks ),
            pHandle
    );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE
auto engine :: vulkan :: destroySwapChain (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( SwapChainHandle )                handle,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || handle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkDestroySwapchainKHR (
            deviceHandle,
            handle,
            AllocatorHandler :: apply ( pAllocationCallbacks )
    );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE
auto engine :: vulkan :: getSwapChainImages (
        Type ( DeviceHandle )       deviceHandle,
        Type ( SwapChainHandle )    swapChainHandle,
        uint32                    * pCount,
        Type ( ImageHandle )      * pImageHandles
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || swapChainHandle == nullptr || pCount == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    if ( pImageHandles == nullptr ) {
        return APICaller.vkGetSwapchainImagesKHR (
                deviceHandle,
                swapChainHandle,
                pCount,
                nullptr
        );
    }

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( * pCount > engine :: vulkan :: config :: swapChainImageCount ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

    auto context = ContextManager :: acquire();

    if (
            auto result = APICaller.vkGetSwapchainImagesKHR (
                    deviceHandle,
                    swapChainHandle,
                    pCount,
                    & context.data().get.swapChain.images[0]
            ); result != ResultSuccess
    ) {
        return result;
    }

    for ( uint32 i = 0U; i < * pCount; ++ i ) {
        pImageHandles[i] = static_cast < Type ( ImageHandle ) > ( context.data().get.swapChain.images[i] );
    }

    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: createImageView (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( ImageViewCreateInfo )    const * pCreateInfo,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks,
        Type ( ImageViewHandle )              * pHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pCreateInfo == nullptr || pHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkCreateImageView (
            deviceHandle,
            prepareContext ( & context.data().create.image.view, pCreateInfo ),
            AllocatorHandler :: apply ( pAllocationCallbacks ),
            pHandle
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: destroyImageView (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( ImageViewHandle )                handle,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || handle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkDestroyImageView (
            deviceHandle,
            handle,
            AllocatorHandler :: apply ( pAllocationCallbacks )
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: createCommandPool (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( CommandPoolCreateInfo )  const * pCreateInfo,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks,
        Type ( CommandPoolHandle )            * pHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pCreateInfo == nullptr || pHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkCreateCommandPool (
            deviceHandle,
            toVulkanFormat ( & context.data().create.commandPool.createInfo, pCreateInfo ),
            AllocatorHandler :: apply ( pAllocationCallbacks ),
            pHandle
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: destroyCommandPool (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( CommandPoolHandle )              handle,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( deviceHandle == nullptr || handle == nullptr ) {
            return ResultErrorIllegalArgument;
        }

#endif

    return APICaller.vkDestroyCommandPool (
            deviceHandle,
            handle,
            AllocatorHandler :: apply ( pAllocationCallbacks )
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: resetCommandPool (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( CommandPoolHandle )              handle,
        Type ( CommandPoolResetFlags )          flags
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( deviceHandle == nullptr || handle == nullptr ) {
            return ResultErrorIllegalArgument;
        }

#endif

    return APICaller.vkResetCommandPool (
            deviceHandle,
            handle,
            flags
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: allocateCommandBuffers (
        Type ( DeviceHandle )                       deviceHandle,
        Type ( CommandBufferAllocateInfo )  const * pAllocateInfo,
        Type ( CommandBufferHandle )              * pHandles
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pHandles == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkAllocateCommandBuffers (
            deviceHandle,
            toVulkanFormat ( & context.data().allocate.commandBuffers.allocateInfo, pAllocateInfo ),
            & pHandles [0]
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: resetCommandBuffer (
        Type ( CommandBufferHandle )                handle,
        Type ( CommandBufferResetFlags )            flags
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( handle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkResetCommandBuffer (
            handle,
            flags
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: freeCommandBuffers (
        Type ( DeviceHandle )           deviceHandle,
        Type ( CommandPoolHandle )      commandPoolHandle,
        cds :: uint32                   commandBufferCount,
        Type ( CommandBufferHandle )  * pCommandBuffers
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || commandPoolHandle == nullptr || pCommandBuffers == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkFreeCommandBuffers (
            deviceHandle,
            commandPoolHandle,
            commandBufferCount,
            pCommandBuffers
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: beginCommandBuffer (
        Type ( CommandBufferHandle )            commandBufferHandle,
        Type ( CommandBufferBeginInfo ) const * pBeginInfo
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( commandBufferHandle == nullptr || pBeginInfo == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkBeginCommandBuffer (
            commandBufferHandle,
            prepareContext ( & context.data().begin.commandBuffer, pBeginInfo )
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: endCommandBuffer (
        Type ( CommandBufferHandle )    commandBufferHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( commandBufferHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkEndCommandBuffer ( commandBufferHandle );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto engine :: vulkan :: trimCommandPool (
        Type ( DeviceHandle )           deviceHandle,
        Type ( CommandPoolHandle )      handle,
        Type ( CommandPoolTrimFlags )   flags
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || handle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkTrimCommandPool (
            deviceHandle,
            handle,
            flags
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: queueSubmit (
        Type ( QueueHandle )        queueHandle,
        cds :: uint32               submitCount,
        Type ( SubmitInfo ) const * pSubmits,
        Type ( FenceHandle )        fenceHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( queueHandle == nullptr || pSubmits == nullptr || submitCount == 0U ) {
        return ResultErrorIllegalArgument;
    }

    if ( submitCount > engine :: vulkan :: config :: submitInfoCount ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkQueueSubmit (
            queueHandle,
            submitCount,
            prepareContext ( & context.data().submit.queue, submitCount, & pSubmits[0] ),
            fenceHandle
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: commandBufferExecuteCommands (
        Type ( CommandBufferHandle )            primaryCommandBufferHandle,
        uint32                                  commandBufferCount,
        Type ( CommandBufferHandle )    const * pSecondaryCommandBufferHandles
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( primaryCommandBufferHandle == nullptr || commandBufferCount == 0U || pSecondaryCommandBufferHandles == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkCmdExecuteCommands (
            primaryCommandBufferHandle,
            commandBufferCount,
            pSecondaryCommandBufferHandles
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
auto engine :: vulkan :: queueSubmit (
        Type ( QueueHandle )            queueHandle,
        uint32                          submitCount,
        Type ( SubmitInfo2 )    const * pSubmits,
        Type ( FenceHandle )            fenceHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( queueHandle == nullptr || submitCount == 0U || pSubmits == nullptr ) {
        return ResultErrorIllegalArgument;
    }

    if ( submitCount > engine :: vulkan :: config :: submitInfoCount ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

    auto context = ContextManager :: acquire();

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

    return APICaller.vkQueueSubmit2 (
            queueHandle,
            submitCount,
            prepareContext ( & context.data().submit.queue, submitCount, & pSubmits[0] ),
            fenceHandle
    );

#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE

    return APICaller.vkQueueSubmit2KHR (
            queueHandle,
            submitCount,
            prepareContext ( & context.data().submit.queue, submitCount, & pSubmits [0] ),
            fenceHandle
    );

#endif
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DEVICE_GROUP_AVAILABLE
auto engine :: vulkan :: commandBufferSetDeviceMask (
        Type ( CommandBufferHandle )    commandBufferHandle,
        uint32                          deviceMask
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( commandBufferHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkCmdSetDeviceMask ( commandBufferHandle, deviceMask );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: createFence (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( FenceCreateInfo )        const * pCreateInfo,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks,
        Type ( FenceHandle )                  * pHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pCreateInfo == nullptr || pHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkCreateFence (
            deviceHandle,
            prepareContext ( & context.data().create.fence, pCreateInfo ),
            AllocatorHandler :: apply ( pAllocationCallbacks ),
            pHandle
    );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_WIN32_AVAILABLE
auto engine :: vulkan :: getFenceWin32Handle (
        Type ( DeviceHandle )                       deviceHandle,
        Type ( FenceGetWin32HandleInfo )    const * pInfo,
        HANDLE                                    * pHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pInfo == nullptr || pHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire ();

    return APICaller.vkGetFenceWin32HandleKHR (
            deviceHandle,
            toVulkanFormat ( & context.data().get.fence.win32HandleInfo, pInfo ),
            pHandle
    );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_FD_AVAILABLE
auto engine :: vulkan :: getFenceFD (
        Type ( DeviceHandle )              deviceHandle,
        Type ( FenceGetFDInfo )    const * pInfo,
        int                              * pHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pInfo == nullptr || pHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire ();

    return APICaller.vkGetFenceFdKHR (
            deviceHandle,
            toVulkanFormat ( & context.data().get.fence.fdInfo, pInfo ),
            pHandle
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: destroyFence (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( FenceHandle )                    fenceHandle,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || fenceHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkDestroyFence (
            deviceHandle,
            fenceHandle,
            AllocatorHandler :: apply ( pAllocationCallbacks )
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: getFenceStatus (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( FenceHandle )                    fenceHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || fenceHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkGetFenceStatus ( deviceHandle, fenceHandle );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: resetFences (
        Type ( DeviceHandle )           deviceHandle,
        uint32                          count,
        Type ( FenceHandle )    const * pFences
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || count == 0U || pFences == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkResetFences (
            deviceHandle,
            count,
            pFences
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: waitForFences (
        Type ( DeviceHandle )           deviceHandle,
        uint32                          count,
        Type ( FenceHandle )    const * pFences,
        bool                            waitForAll,
        uint64                          timeout
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || count == 0U || pFences == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkWaitForFences (
            deviceHandle,
            count,
            pFences,
            waitForAll ? VK_TRUE : VK_FALSE,
            timeout
    );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISPLAY_CONTROL_AVAILABLE
auto engine :: vulkan :: registerDeviceEvent (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( DeviceEventInfo )        const * pEventInfo,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks,
        Type ( FenceHandle )                  * pHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pEventInfo == nullptr || pHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkRegisterDeviceEventEXT (
            deviceHandle,
            toVulkanFormat ( & context.data().other.registerEvent.deviceInfo, pEventInfo ),
            AllocatorHandler :: apply ( pAllocationCallbacks ),
            pHandle
    );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISPLAY_CONTROL_AVAILABLE
auto engine :: vulkan :: registerDisplayEvent (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( DisplayHandle )                  displayHandle,
        Type ( DisplayEventInfo )       const * pEventInfo,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks,
        Type ( FenceHandle )                  * pHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pEventInfo == nullptr || pHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkRegisterDisplayEventEXT (
            deviceHandle,
            displayHandle,
            toVulkanFormat ( & context.data().other.registerEvent.displayInfo, pEventInfo ),
            AllocatorHandler :: apply ( pAllocationCallbacks ),
            pHandle
    );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_WIN32_AVAILABLE
auto engine :: vulkan :: importFenceWin32Handle (
        Type ( DeviceHandle )                       deviceHandle,
        Type ( ImportFenceWin32HandleInfo ) const * pInfo
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pInfo == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkImportFenceWin32HandleKHR (
            deviceHandle,
            toVulkanFormat ( & context.data()._import.fence.win32.info, pInfo )
    );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_FD_AVAILABLE
auto engine :: vulkan :: importFenceFd (
        Type ( DeviceHandle )              deviceHandle,
        Type ( ImportFenceFdInfo ) const * pInfo
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pInfo == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkImportFenceFdKHR (
            deviceHandle,
            toVulkanFormat ( & context.data()._import.fence.fd.info, pInfo )
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: createSemaphore (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( SemaphoreCreateInfo )    const * pCreateInfo,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks,
        Type ( SemaphoreHandle )              * pHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pCreateInfo == nullptr || pHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkCreateSemaphore (
            deviceHandle,
            prepareContext ( & context.data().create.semaphore, pCreateInfo ),
            AllocatorHandler :: apply ( pAllocationCallbacks ),
            pHandle
    );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_WIN32_AVAILABLE
auto engine :: vulkan :: getSemaphoreWin32Handle (
        Type ( DeviceHandle )                           deviceHandle,
        Type ( SemaphoreGetWin32HandleInfo )    const * pInfo,
        HANDLE                                        * pHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pInfo == nullptr || pHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkGetSemaphoreWin32HandleKHR (
            deviceHandle,
            toVulkanFormat ( & context.data().get.semaphore.win32HandleInfo, pInfo ),
            pHandle
    );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_FD_AVAILABLE
auto engine :: vulkan :: getSemaphoreFd (
        Type ( DeviceHandle )               deviceHandle,
        Type ( SemaphoreGetFdInfo ) const * pInfo,
        int                               * pFd
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pInfo == nullptr || pFd == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkGetSemaphoreFdKHR (
            deviceHandle,
            toVulkanFormat ( & context.data().get.semaphore.fdInfo, pInfo ),
            pFd
    );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_SEMAPHORE_AVAILABLE
auto engine :: vulkan :: getSemaphoreZirconHandleGoogle (
        Type ( DeviceHandle )                               deviceHandle,
        Type ( SemaphoreGetZirconHandleInfoGoogle ) const * pInfo,
        zx_handle_t                                       * pHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pInfo == nullptr || pHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkGetSemaphoreZirconHandleFUCHSIA (
            deviceHandle,
            toVulkanFormat ( & context.data().get.semaphore.zirconHandleInfo, pInfo ),
            pHandle
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: destroySemaphore (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( SemaphoreHandle )                semaphoreHandle,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || semaphoreHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkDestroySemaphore (
            deviceHandle,
            semaphoreHandle,
            AllocatorHandler :: apply ( pAllocationCallbacks )
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
auto engine :: vulkan :: getSemaphoreCounterValue (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( SemaphoreHandle )                semaphoreHandle,
        uint64                                * pValue
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || semaphoreHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    uint64_t value = 0U;

    if (
            auto result = APICaller.vkGetSemaphoreCounterValue (
                    deviceHandle,
                    semaphoreHandle,
                    & value
            ); result != ResultSuccess
    ) {
        return static_cast < Type ( Result ) > ( result );
    }

    * pValue = value;

    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
auto engine :: vulkan :: waitSemaphores (
        Type ( DeviceHandle )               deviceHandle,
        Type ( SemaphoreWaitInfo )  const * pWaitInfo,
        uint64                              timeout
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pWaitInfo == nullptr ) {
        return ResultErrorIllegalArgument;
    }

    if ( pWaitInfo->semaphoreCount > engine :: vulkan :: config :: waitSemaphoreCount ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkWaitSemaphores (
            deviceHandle,
            prepareContext ( & context.data().wait.semaphore, pWaitInfo ),
            static_cast < uint64_t > ( timeout )
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
auto engine :: vulkan :: signalSemaphore (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( SemaphoreSignalInfo )    const * pSignalInfo
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pSignalInfo == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkSignalSemaphore (
            deviceHandle,
            toVulkanFormat ( & context.data().signal.semaphore.info, pSignalInfo )
    );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_WIN32_AVAILABLE
auto engine :: vulkan :: importSemaphoreWin32Handle (
        Type ( DeviceHandle )                           deviceHandle,
        Type ( ImportSemaphoreWin32HandleInfo ) const * pInfo
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pInfo == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkImportSemaphoreWin32HandleKHR (
            deviceHandle,
            toVulkanFormat ( & context.data()._import.semaphore.win32.info, pInfo )
    );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_FD_AVAILABLE
auto engine :: vulkan :: importSemaphoreFd (
        Type ( DeviceHandle )                  deviceHandle,
        Type ( ImportSemaphoreFdInfo ) const * pInfo
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pInfo == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkImportSemaphoreFdKHR (
            deviceHandle,
            toVulkanFormat ( & context.data()._import.semaphore.fd.info, pInfo )
    );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_SEMAPHORE_AVAILABLE
auto engine :: vulkan :: importSemaphoreZirconHandleGoogle (
        Type ( DeviceHandle )                                   deviceHandle,
        Type ( ImportSemaphoreZirconHandleInfoGoogle )  const * pInfo
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pInfo == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkImportSemaphoreZirconHandleFUCHSIA (
            deviceHandle,
            toVulkanFormat ( & context.data()._import.semaphore.zircon.info, pInfo )
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: createEvent (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( EventCreateInfo )        const * pCreateInfo,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks,
        Type ( EventHandle )                  * pHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pCreateInfo == nullptr || pHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkCreateEvent (
            deviceHandle,
            toVulkanFormat ( & context.data().create.event.createInfo, pCreateInfo ),
            AllocatorHandler :: apply ( pAllocationCallbacks ),
            pHandle
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: destroyEvent (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( EventHandle )                    handle,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || handle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkDestroyEvent (
            deviceHandle,
            handle,
            AllocatorHandler :: apply ( pAllocationCallbacks )
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: getEventStatus (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( EventHandle )                    handle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || handle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkGetEventStatus (
            deviceHandle,
            handle
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: setEvent (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( EventHandle )                    handle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || handle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkSetEvent (
            deviceHandle,
            handle
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: resetEvent (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( EventHandle )                    handle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || handle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkResetEvent (
            deviceHandle,
            handle
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
auto engine :: vulkan :: commandBufferSetEvent (
        Type ( CommandBufferHandle )    commandBufferHandle,
        Type ( EventHandle )            eventHandle,
        Type ( DependencyInfo ) const * pDependencyInfo
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( commandBufferHandle == nullptr || eventHandle == nullptr || pDependencyInfo == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

    return APICaller.vkCmdSetEvent2 (
            commandBufferHandle,
            eventHandle,
            prepareContext ( & context.data().set.commandBuffer.event, pDependencyInfo )
    );

#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE

    return APICaller.vkCmdSetEvent2KHR (
            commandBufferHandle,
            eventHandle,
            prepareContext ( & context.data().set.commandBuffer.event, pDependencyInfo )
    );

#endif
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: commandBufferSetEvent (
        Type ( CommandBufferHandle )    commandBufferHandle,
        Type ( EventHandle )            eventHandle,
        Type ( PipelineStageFlags )     flags
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( commandBufferHandle == nullptr || eventHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkCmdSetEvent (
            commandBufferHandle,
            eventHandle,
            flags
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: commandBufferResetEvent (
        Type ( CommandBufferHandle )    commandBufferHandle,
        Type ( EventHandle )            eventHandle,
        Type ( PipelineStageFlags )     flags
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( commandBufferHandle == nullptr || eventHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

    return APICaller.vkCmdResetEvent2 (
            commandBufferHandle,
            eventHandle,
            flags
    );

#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE

    return APICaller.vkCmdResetEvent2KHR (
            commandBufferHandle,
            eventHandle,
            flags
    );

#else

    return APICaller.vkCmdResetEvent (
            commandBufferHandle,
            eventHandle,
            flags
    );

#endif
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
auto engine :: vulkan :: commandBufferWaitEvents (
        Type ( CommandBufferHandle )            commandBufferHandle,
        cds :: uint32                           eventCount,
        Type ( EventHandle )            const * pEventHandles,
        Type ( DependencyInfo )         const * pDependencyInfos
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( commandBufferHandle == nullptr || pEventHandles == nullptr || pDependencyInfos == nullptr || eventCount == 0U ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

    return APICaller.vkCmdWaitEvents2 (
            commandBufferHandle,
            eventCount,
            pEventHandles,
            prepareContext ( & context.data().wait.commandBuffer.event2, eventCount, pDependencyInfos )
    );

#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE

    return APICaller.vkCmdWaitEvents2KHR (
            commandBufferHandle,
            eventCount,
            pEventHandles,
            prepareContext ( & context.data().wait.commandBuffer.event2, eventCount, pDependencyInfos )
    );

#endif
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: commandBufferWaitEvents (
        Type ( CommandBufferHandle )            commandBufferHandle,
        cds :: uint32                           eventCount,
        Type ( EventHandle )            const * pEventHandles,
        Type ( PipelineStageFlags )             sourceStageMask,
        Type ( PipelineStageFlags )             destinationStageMask,
        cds :: uint32                           memoryBarrierCount,
        Type ( MemoryBarrier )          const * pMemoryBarriers,
        cds :: uint32                           bufferMemoryBarrierCount,
        Type ( BufferMemoryBarrier )    const * pBufferMemoryBarriers,
        cds :: uint32                           imageMemoryBarrierCount,
        Type ( ImageMemoryBarrier )     const * pImageMemoryBarriers
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if (
            commandBufferHandle         == nullptr  ||
            eventCount                  == 0U       ||
            pEventHandles               == nullptr  ||
            memoryBarrierCount          == 0U       ||
            pMemoryBarriers             == nullptr  ||
            bufferMemoryBarrierCount    == 0U       ||
            pBufferMemoryBarriers       == nullptr  ||
            imageMemoryBarrierCount     == 0U       ||
            pImageMemoryBarriers        == nullptr
    ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkCmdWaitEvents (
            commandBufferHandle,
            eventCount,
            pEventHandles,
            sourceStageMask,
            destinationStageMask,
            memoryBarrierCount,
            prepareContext ( & context.data().wait.commandBuffer.event, memoryBarrierCount, pMemoryBarriers ),
            bufferMemoryBarrierCount,
            prepareContext ( & context.data().wait.commandBuffer.event, bufferMemoryBarrierCount, pBufferMemoryBarriers ),
            imageMemoryBarrierCount,
            prepareContext ( & context.data().wait.commandBuffer.event, imageMemoryBarrierCount, pImageMemoryBarriers )
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: queueWaitIdle (
        Type ( QueueHandle ) handle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( handle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkQueueWaitIdle ( handle );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: deviceWaitIdle (
        Type ( DeviceHandle ) handle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( handle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkDeviceWaitIdle ( handle );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE
auto engine :: vulkan :: commandBufferBeginRendering (
        Type ( CommandBufferHandle )        handle,
        Type ( RenderingInfo )      const * pRenderingInfo
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( handle == nullptr || pRenderingInfo == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

    return APICaller.vkCmdBeginRendering (
            handle,
            prepareContext ( & context.data().begin.commandBufferRendering, pRenderingInfo )
    );

#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE

    return APICaller.vkCmdBeginRenderingKHR (
            handle,
            prepareContext ( & context.data().begin.commandBufferRendering, pRenderingInfo )
    );

#endif
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE
auto engine :: vulkan :: commandBufferEndRendering (
        Type ( CommandBufferHandle )    handle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( handle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

    return APICaller.vkCmdEndRendering ( handle );

#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE

    return APICaller.vkCmdEndRenderingKHR ( handle );

#endif
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: createRenderPass (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( RenderPassCreateInfo )   const * pCreateInfo,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks,
        Type ( RenderPassHandle )             * pHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pCreateInfo == nullptr || pHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkCreateRenderPass (
            deviceHandle,
            prepareContext ( & context.data().create.renderPass, pCreateInfo ),
            AllocatorHandler :: apply ( pAllocationCallbacks ),
            pHandle
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
auto engine :: vulkan :: createRenderPass (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( RenderPassCreateInfo2 )  const * pCreateInfo,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks,
        Type ( RenderPassHandle )             * pHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pCreateInfo == nullptr || pHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkCreateRenderPass2 (
            deviceHandle,
            prepareContext ( & context.data().create.renderPass2, pCreateInfo ),
            AllocatorHandler :: apply ( pAllocationCallbacks ),
            pHandle
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: destroyRenderPass (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( RenderPassHandle )               renderPassHandle,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || renderPassHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkDestroyRenderPass (
            deviceHandle,
            renderPassHandle,
            AllocatorHandler :: apply ( pAllocationCallbacks )
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: createFrameBuffer (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( FrameBufferCreateInfo )  const * pCreateInfo,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks,
        Type ( FrameBufferHandle )            * pHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pCreateInfo == nullptr || pHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkCreateFramebuffer (
            deviceHandle,
            prepareContext ( & context.data().create.buffer.frame, pCreateInfo ),
            AllocatorHandler :: apply ( pAllocationCallbacks ),
            pHandle
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: destroyFrameBuffer (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( FrameBufferHandle )              handle,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || handle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkDestroyFramebuffer (
            deviceHandle,
            handle,
            AllocatorHandler :: apply ( pAllocationCallbacks )
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: commandBufferBeginRenderPass (
        Type ( CommandBufferHandle )            commandBufferHandle,
        Type ( RenderPassBeginInfo )    const * pInfo,
        Type ( SubpassContents )                subpassContents
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( commandBufferHandle == nullptr || pInfo == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkCmdBeginRenderPass (
            commandBufferHandle,
            prepareContext ( & context.data().begin.renderPass, pInfo ),
            static_cast < VkSubpassContents > ( subpassContents )
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
auto engine :: vulkan :: commandBufferBeginRenderPass (
        Type ( CommandBufferHandle )            commandBufferHandle,
        Type ( RenderPassBeginInfo )    const * pRenderPassBeginInfo,
        Type ( SubpassBeginInfo )       const * pSubpassBeginInfo
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( commandBufferHandle == nullptr || pRenderPassBeginInfo == nullptr || pSubpassBeginInfo == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkCmdBeginRenderPass2 (
            commandBufferHandle,
            prepareContext ( & context.data().begin.renderPass, pRenderPassBeginInfo ),
            prepareContext ( & context.data().begin.renderPass, pSubpassBeginInfo )
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: getRenderAreaGranularity (
        Type ( DeviceHandle )       deviceHandle,
        Type ( RenderPassHandle )   renderPassHandle,
        Type ( Extent2D )         * pGranularity
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || renderPassHandle == nullptr || pGranularity == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkGetRenderAreaGranularity (
            deviceHandle,
            renderPassHandle,
            pGranularity
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: commandBufferNextSubpass (
        Type ( CommandBufferHandle )    commandBufferHandle,
        Type ( SubpassContents )        contents
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( commandBufferHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkCmdNextSubpass (
            commandBufferHandle,
            static_cast < VkSubpassContents > ( contents )
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
auto engine :: vulkan :: commandBufferNextSubpass (
        Type ( CommandBufferHandle )        commandBufferHandle,
        Type ( SubpassBeginInfo )   const * pBeginInfo,
        Type ( SubpassEndInfo )     const * pEndInfo
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( commandBufferHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkCmdNextSubpass2 (
            commandBufferHandle,
            prepareContext ( & context.data().other.nextSubpass, pBeginInfo ),
            prepareContext ( & context.data().other.nextSubpass, pEndInfo )
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: commandBufferEndRenderPass (
        Type ( CommandBufferHandle )    handle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( handle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkCmdEndRenderPass ( handle );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
auto engine :: vulkan :: commandBufferEndRenderPass (
        Type ( CommandBufferHandle )        handle,
        Type ( SubpassEndInfo )     const * pInfo
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( handle == nullptr || pInfo == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkCmdEndRenderPass2 (
            handle,
            prepareContext ( & context.data().other.nextSubpass, pInfo )
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: createShaderModule (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( ShaderModuleCreateInfo ) const * pCreateInfo,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks,
        Type ( ShaderModuleHandle )           * pShaderModuleHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pCreateInfo == nullptr || pShaderModuleHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkCreateShaderModule (
            deviceHandle,
            prepareContext ( & context.data().create.shaderModule, pCreateInfo ),
            AllocatorHandler :: apply ( pAllocationCallbacks ),
            pShaderModuleHandle
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: destroyShaderModule (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( ShaderModuleHandle )             shaderModuleHandle,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || shaderModuleHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkDestroyShaderModule (
            deviceHandle,
            shaderModuleHandle,
            AllocatorHandler :: apply ( pAllocationCallbacks )
    );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_2_AVAILABLE
auto engine :: vulkan :: commandBufferSetPatchControlPoints (
        Type ( CommandBufferHandle )    commandBufferHandle,
        cds :: uint32                   patchControlPoints
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( commandBufferHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkCmdSetPatchControlPointsEXT ( commandBufferHandle, patchControlPoints );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE
auto engine :: vulkan :: getPhysicalDeviceCooperativeMatrixPropertiesNVidia (
        Type ( PhysicalDeviceHandle )                 physicalDeviceHandle,
        cds :: uint32                               * pCount,
        Type ( CooperativeMatrixPropertiesNVidia )  * pProperties
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( physicalDeviceHandle == nullptr || pCount == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    if ( pProperties == nullptr ) {
        return APICaller.vkGetPhysicalDeviceCooperativeMatrixPropertiesNV (
                physicalDeviceHandle,
                pCount,
                nullptr
        );
    }

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( * pCount > engine :: vulkan :: config :: cooperativeMatrixPropertiesCount ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

    auto context = ContextManager :: acquire();

    if (
            auto result = APICaller.vkGetPhysicalDeviceCooperativeMatrixPropertiesNV (
                    physicalDeviceHandle,
                    pCount,
                    & context.data().get.physicalDevice.cooperativeMatrixProperties.properties[0]
            ); result != ResultSuccess
    ) {
        return result;
    }

    for ( uint32 i = 0U; i < * pCount; ++ i ) {
        (void) fromVulkanFormat ( & pProperties[i], & context.data().get.physicalDevice.cooperativeMatrixProperties.properties[0] );
    }

    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_CACHE_AVAILABLE
auto engine :: vulkan :: createValidationCache (
        Type ( DeviceHandle )                       deviceHandle,
        Type ( ValidationCacheCreateInfo )  const * pCreateInfo,
        Type ( AllocationCallbacks )        const * pAllocationCallbacks,
        Type ( ValidationCacheHandle )            * pHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pCreateInfo == nullptr || pHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkCreateValidationCacheEXT (
            deviceHandle,
            toVulkanFormat ( & context.data().create.validationCache.createInfo, pCreateInfo ),
            AllocatorHandler :: apply ( pAllocationCallbacks ),
            pHandle
    );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_CACHE_AVAILABLE
auto engine :: vulkan :: mergeValidationCache (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( ValidationCacheHandle )          destinationCacheHandle,
        cds :: uint32                           sourceCacheCount,
        Type ( ValidationCacheHandle )  const * pSourceCacheHandles
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || destinationCacheHandle == nullptr || sourceCacheCount == 0U || pSourceCacheHandles == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkMergeValidationCachesEXT (
            deviceHandle,
            destinationCacheHandle,
            sourceCacheCount,
            pSourceCacheHandles
    );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_CACHE_AVAILABLE
auto engine :: vulkan :: getValidationCacheData (
        Type ( DeviceHandle )           deviceHandle,
        Type ( ValidationCacheHandle )  validationCacheHandle,
        cds :: uint64 *                 pDataSize,
        void *                          pData
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || validationCacheHandle == nullptr || pDataSize == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    std :: size_t size;

    if ( pData == nullptr ) {
        if (
                auto result = APICaller.vkGetValidationCacheDataEXT (
                        deviceHandle,
                        validationCacheHandle,
                        & size,
                        nullptr
                ); result != ResultSuccess
        ) {
            return result;
        }

        * pDataSize = size;
        return ResultSuccess;
    }

    size = * pDataSize;
    return APICaller.vkGetValidationCacheDataEXT (
            deviceHandle,
            validationCacheHandle,
            & size,
            pData
    );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_CACHE_AVAILABLE
auto engine :: vulkan :: destroyValidationCache (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( ValidationCacheHandle )          validationCacheHandle,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || validationCacheHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkDestroyValidationCacheEXT (
            deviceHandle,
            validationCacheHandle,
            AllocatorHandler :: apply ( pAllocationCallbacks )
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: createComputePipelines (
        Type ( DeviceHandle )                       deviceHandle,
        Type ( PipelineCacheHandle )                pipelineCacheHandle,
        cds :: uint32                               count,
        Type ( ComputePipelineCreateInfo )  const * pCreateInfos,
        Type ( AllocationCallbacks )        const * pAllocationCallbacks,
        Type ( PipelineHandle )                   * pPipelineHandles
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if (
            deviceHandle        == nullptr  ||
            count               == 0U       ||
            pCreateInfos        == nullptr  ||
            pPipelineHandles    == nullptr
    ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    if (
            auto result = APICaller.vkCreateComputePipelines (
                    deviceHandle,
                    pipelineCacheHandle,
                    count,
                    & prepareContext ( & context->create.pipeline.compute, count, & pCreateInfos[0] ) [0],
                    AllocatorHandler :: apply ( pAllocationCallbacks ),
                    & pPipelineHandles [0]
            ); result != ResultSuccess
    ) {
        return result;
    }

    extractContext ( count, & pCreateInfos[0], & context->create.pipeline.compute );

    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE
auto engine :: vulkan :: getDeviceSubpassShadingMaxWorkgroupSizeHuawei (
        Type ( DeviceHandle )       deviceHandle,
        Type ( RenderPassHandle )   renderPassHandle,
        Type ( Extent2D )         * pMaxWorkgroupSize
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || renderPassHandle == nullptr || pMaxWorkgroupSize == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI (
            deviceHandle,
            renderPassHandle,
            pMaxWorkgroupSize
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: createGraphicsPipelines (
        Type ( DeviceHandle )                       deviceHandle,
        Type ( PipelineCacheHandle )                pipelineCacheHandle,
        cds :: uint32                               count,
        Type ( GraphicsPipelineCreateInfo ) const * pCreateInfos,
        Type ( AllocationCallbacks )        const * pAllocationCallbacks,
        Type ( PipelineHandle )                   * pPipelineHandles
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || count == 0U || pCreateInfos == nullptr || pPipelineHandles == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    if (
            auto result = APICaller.vkCreateGraphicsPipelines (
                    deviceHandle,
                    pipelineCacheHandle,
                    count,
                    prepareContext ( & context->create.pipeline.graphics, count, & pCreateInfos[0] ),
                    AllocatorHandler :: apply ( pAllocationCallbacks ),
                    & pPipelineHandles [0]
            ); result != ResultSuccess
    ) {
        return result;
    }

    extractContext ( count,& pCreateInfos[0], & context->create.pipeline.graphics );

    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
auto engine :: vulkan :: createRayTracingPipelinesNVidia (
        Type ( DeviceHandle )                               deviceHandle,
        Type ( PipelineCacheHandle )                        pipelineCacheHandle,
        cds :: uint32                                       count,
        Type ( RayTracingPipelineCreateInfoNVidia ) const * pCreateInfos,
        Type ( AllocationCallbacks )                const * pAllocationCallbacks,
        Type ( PipelineHandle )                           * pPipelineHandles
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || count == 0U || pCreateInfos == nullptr || pPipelineHandles == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    if (
            auto result = APICaller.vkCreateRayTracingPipelinesNV (
                    deviceHandle,
                    pipelineCacheHandle,
                    count,
                    prepareContext ( & context->create.pipeline.rayTracing.nVidiaPipeline, count, & pCreateInfos[0] ),
                    AllocatorHandler :: apply ( pAllocationCallbacks ),
                    & pPipelineHandles [0]
            ); result != ResultSuccess
    ) {
        return result;
    }

    extractContext ( count, & pCreateInfos[0], & context->create.pipeline.rayTracing.nVidiaPipeline );

    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
auto engine :: vulkan :: createRayTracingPipelines (
        Type ( DeviceHandle )                               deviceHandle,
        Type ( DeferredOperationHandle )                    deferredOperationHandle,
        Type ( PipelineCacheHandle )                        pipelineCacheHandle,
        cds :: uint32                                       count,
        Type ( RayTracingPipelineCreateInfo )       const * pCreateInfos,
        Type ( AllocationCallbacks )                const * pAllocationCallbacks,
        Type ( PipelineHandle )                           * pPipelineHandles
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || count == 0U || pCreateInfos == nullptr || pPipelineHandles == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    if (
            auto result = APICaller.vkCreateRayTracingPipelinesKHR (
                    deviceHandle,
                    deferredOperationHandle,
                    pipelineCacheHandle,
                    count,
                    prepareContext ( & context->create.pipeline.rayTracing.pipeline, count, & pCreateInfos[0] ),
                    AllocatorHandler :: apply ( pAllocationCallbacks ),
                    & pPipelineHandles [0]
            ); result != ResultSuccess
    ) {
        return result;
    }

    extractContext ( count, & pCreateInfos[0], & context->create.pipeline.rayTracing.pipeline );

    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
auto engine :: vulkan :: getRayTracingShaderGroupHandles (
        Type ( DeviceHandle )   deviceHandle,
        Type ( PipelineHandle ) pipelineHandle,
        cds :: uint32           firstGroup,
        cds :: uint32           groupCount,
        cds :: uint64           dataSize,
        void                  * pData
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pipelineHandle == nullptr || pData == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkGetRayTracingShaderGroupHandlesKHR (
            deviceHandle,
            pipelineHandle,
            firstGroup,
            groupCount,
            dataSize,
            pData
    );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
auto engine :: vulkan :: getRayTracingCaptureReplayShaderGroupHandles (
        Type ( DeviceHandle )   deviceHandle,
        Type ( PipelineHandle ) pipelineHandle,
        cds :: uint32           firstGroup,
        cds :: uint32           groupCount,
        cds :: uint64           dataSize,
        void                  * pData
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pipelineHandle == nullptr || pData == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkGetRayTracingCaptureReplayShaderGroupHandlesKHR (
            deviceHandle,
            pipelineHandle,
            firstGroup,
            groupCount,
            dataSize,
            pData
    );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
auto engine :: vulkan :: compileDeferredNVidia (
        Type ( DeviceHandle )   deviceHandle,
        Type ( PipelineHandle ) pipelineHandle,
        cds :: uint32           shader
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pipelineHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkCompileDeferredNV (
            deviceHandle,
            pipelineHandle,
            shader
    );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
auto engine :: vulkan :: getRayTracingShaderGroupStackSize (
        Type ( DeviceHandle )       deviceHandle,
        Type ( PipelineHandle )     pipelineHandle,
        cds :: uint32               group,
        Type ( ShaderGroupShader )  groupShader,
        Type ( DeviceSize )       * pSize
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pipelineHandle == nullptr || pSize == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    VkDeviceSize size;

    if (
            auto result = APICaller.vkGetRayTracingShaderGroupStackSizeKHR (
                    & size,
                    deviceHandle,
                    pipelineHandle,
                    group,
                    static_cast < VkShaderGroupShaderKHR > ( groupShader )
            ); result != ResultSuccess
    ) {
        return result;
    }

    * pSize = size;

    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
auto engine :: vulkan :: commandBufferSetRayTracingPipelineStackSize (
        Type ( CommandBufferHandle )    commandBufferHandle,
        cds :: uint32                   pipelineStackSize
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( commandBufferHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkCmdSetRayTracingPipelineStackSizeKHR (
            commandBufferHandle,
            pipelineStackSize
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: destroyPipeline (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( PipelineHandle )                 pipelineHandle,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pipelineHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkDestroyPipeline (
            deviceHandle,
            pipelineHandle,
            AllocatorHandler :: apply ( pAllocationCallbacks )
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: createPipelineCache (
        Type ( DeviceHandle )                       deviceHandle,
        Type ( PipelineCacheCreateInfo )    const * pCreateInfo,
        Type ( AllocationCallbacks )        const * pAllocationCallbacks,
        Type ( PipelineCacheHandle )              * pHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pCreateInfo == nullptr || pHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkCreatePipelineCache (
            deviceHandle,
            prepareContext ( & context->create.pipeline.cache, pCreateInfo ),
            AllocatorHandler :: apply ( pAllocationCallbacks ),
            pHandle
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: mergePipelineCaches (
        Type ( DeviceHandle )                       deviceHandle,
        Type ( PipelineCacheHandle )                destinationCacheHandle,
        cds :: uint32                               sourceCacheCount,
        Type ( PipelineCacheHandle )        const * pSourceCacheHandles
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || destinationCacheHandle == nullptr || pSourceCacheHandles == nullptr || sourceCacheCount == 0U ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkMergePipelineCaches (
            deviceHandle,
            destinationCacheHandle,
            sourceCacheCount,
            pSourceCacheHandles
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: getPipelineCacheData (
        Type ( DeviceHandle )                       deviceHandle,
        Type ( PipelineCacheHandle )                cacheHandle,
        cds :: uint64                             * pSize,
        void                                      * pData
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || cacheHandle == nullptr || pSize == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    std :: size_t size = 0U;

    if ( pData == nullptr ) {

        if (
                auto result = APICaller.vkGetPipelineCacheData (
                        deviceHandle,
                        cacheHandle,
                        & size,
                        nullptr
                ); result != ResultSuccess
        ) {
            return result;
        }

        * pSize = size;
        return ResultSuccess;
    }

    size = * pSize;

    return APICaller.vkGetPipelineCacheData (
            deviceHandle,
            cacheHandle,
            & size,
            pData
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: destroyPipelineCache (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( PipelineCacheHandle )            cacheHandle,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || cacheHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkDestroyPipelineCache (
            deviceHandle,
            cacheHandle,
            AllocatorHandler :: apply ( pAllocationCallbacks )
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: commandBufferBindPipeline (
        Type ( CommandBufferHandle )    commandBufferHandle,
        Type ( PipelineBindPoint )      bindPoint,
        Type ( PipelineHandle )         pipelineHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( commandBufferHandle == nullptr || pipelineHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkCmdBindPipeline (
            commandBufferHandle,
            static_cast < VkPipelineBindPoint > ( bindPoint ),
            pipelineHandle
    );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE
auto engine :: vulkan :: commandBufferBindPipelineShaderGroup (
        Type ( CommandBufferHandle )    commandBufferHandle,
        Type ( PipelineBindPoint )      bindPoint,
        Type ( PipelineHandle )         pipelineHandle,
        cds :: uint32                   groupIndex
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( commandBufferHandle == nullptr || pipelineHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkCmdBindPipelineShaderGroupNV (
            commandBufferHandle,
            static_cast < VkPipelineBindPoint > ( bindPoint ),
            pipelineHandle,
            groupIndex
    );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
auto engine :: vulkan :: getPipelineExecutableProperties (
        Type ( DeviceHandle )                           deviceHandle,
        Type ( PipelineInfo )                   const * pPipelineInfo,
        cds :: uint32                                 * pCount,
        Type ( PipelineExecutableProperties )         * pProperties
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pPipelineInfo == nullptr || pCount == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    if ( pProperties == nullptr ) {
        return APICaller.vkGetPipelineExecutablePropertiesKHR (
                deviceHandle,
                prepareContext ( & context->get.pipeline.properties, pPipelineInfo ),
                pCount,
                nullptr
        );
    }

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( * pCount > engine :: vulkan :: config :: pipelineExecutablePropertiesCount ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

    if (
            auto result = APICaller.vkGetPipelineExecutablePropertiesKHR (
                    deviceHandle,
                    prepareContext ( & context->get.pipeline.properties, pPipelineInfo ),
                    pCount,
                    & context->get.pipeline.properties.properties[0]
            ); result != ResultSuccess
    ) {
        return result;
    }

    extractContext ( * pCount, & pProperties[0], & context->get.pipeline.properties );
    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
auto engine :: vulkan :: getPipelineExecutableStatistics (
        Type ( DeviceHandle )                           deviceHandle,
        Type ( PipelineExecutableInfo )         const * pPipelineExecutableInfo,
        cds :: uint32                                 * pCount,
        Type ( PipelineExecutableStatistic )          * pStatistics
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pPipelineExecutableInfo == nullptr || pCount == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    if ( pStatistics == nullptr ) {
        return APICaller.vkGetPipelineExecutableStatisticsKHR (
                deviceHandle,
                prepareContext ( & context->get.pipeline.statistics, pPipelineExecutableInfo ),
                pCount,
                nullptr
        );
    }

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( * pCount > engine :: vulkan :: config :: pipelineExecutableStatisticsCount ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

    if (
            auto result = APICaller.vkGetPipelineExecutableStatisticsKHR (
                    deviceHandle,
                    prepareContext ( & context->get.pipeline.statistics, pPipelineExecutableInfo ),
                    pCount,
                    & context->get.pipeline.statistics.statistics[0]
            ); result != ResultSuccess
    ) {
        return result;
    }

    extractContext ( * pCount, & pStatistics[0], & context->get.pipeline.statistics );
    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
auto engine :: vulkan :: getPipelineExecutableInternalRepresentations (
        Type ( DeviceHandle )                                   deviceHandle,
        Type ( PipelineExecutableInfo )                 const * pPipelineExecutableInfo,
        cds :: uint32                                         * pCount,
        Type ( PipelineExecutableInternalRepresentation )     * pRepresentations
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pPipelineExecutableInfo == nullptr || pCount == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    if ( pRepresentations == nullptr ) {
        return APICaller.vkGetPipelineExecutableInternalRepresentationsKHR (
                deviceHandle,
                prepareContext ( & context->get.pipeline.internalRepresentations, pPipelineExecutableInfo ),
                pCount,
                nullptr
        );
    }

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( * pCount > engine :: vulkan :: config :: pipelineExecutableInternalRepresentationCount ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

    if (
            auto result = APICaller.vkGetPipelineExecutableInternalRepresentationsKHR (
                    deviceHandle,
                    prepareContext ( & context->get.pipeline.internalRepresentations, pPipelineExecutableInfo ),
                    pCount,
                    prepareContext ( & context->get.pipeline.internalRepresentations, * pCount, pRepresentations )
            ); result != ResultSuccess
    ) {
        return result;
    }

    extractContext ( * pCount, & pRepresentations[0], & context->get.pipeline.internalRepresentations );
    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_INFO_AVAILABLE
auto engine :: vulkan :: getShaderInfoAMD (
        Type ( DeviceHandle )         deviceHandle,
        Type ( PipelineHandle )       pipelineHandle,
        Type ( ShaderStageFlag )      shaderStage,
        Type ( ShaderInfoTypeAMD )    infoType,
        cds :: uint64               * pDataSize,
        void                        * pData
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pipelineHandle == nullptr || pDataSize == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    if ( pData == nullptr ) {
        std :: size_t size;

        if (
                auto result = APICaller.vkGetShaderInfoAMD (
                        deviceHandle,
                        pipelineHandle,
                        static_cast < VkShaderStageFlagBits > ( shaderStage ),
                        static_cast < VkShaderInfoTypeAMD > ( infoType ),
                        & size,
                        nullptr
                ); result != ResultSuccess
        ) {
            return result;
        }

        * pDataSize = size;
        return ResultSuccess;
    }

    std :: size_t size = * pDataSize;

    return APICaller.vkGetShaderInfoAMD (
            deviceHandle,
            pipelineHandle,
            static_cast < VkShaderStageFlagBits > ( shaderStage ),
            static_cast < VkShaderInfoTypeAMD > ( infoType ),
            & size,
            pData
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: optimizeForSingleDevice (
        Type ( DeviceHandle )               handle,
        Type ( DeviceCreateInfo )   const * pCreateInfo
) noexcept -> Type ( Result ) {
    APICaller.acquireHandlesForDevice ( handle, pCreateInfo );
    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: getPhysicalDeviceMemoryProperties (
        Type ( PhysicalDeviceHandle )               physicalDeviceHandle,
        Type ( PhysicalDeviceMemoryProperties )   * pProperties
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( physicalDeviceHandle == nullptr || pProperties == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    if (
            auto result = APICaller.vkGetPhysicalDeviceMemoryProperties (
                    physicalDeviceHandle,
                    & context->get.physicalDevice.memory.properties
            ); result != ResultSuccess
    ) {
        return result;
    }

    (void) fromVulkanFormat ( pProperties, & context->get.physicalDevice.memory.properties );
    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto engine :: vulkan :: getPhysicalDeviceMemoryProperties (
        Type ( PhysicalDeviceHandle )               physicalDeviceHandle,
        Type ( PhysicalDeviceMemoryProperties2 )  * pProperties
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( physicalDeviceHandle == nullptr || pProperties == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    if (
            auto result = APICaller.vkGetPhysicalDeviceMemoryProperties2 (
                    physicalDeviceHandle,
                    prepareContext ( & context->get.physicalDevice.memory, pProperties )
            ); result != ResultSuccess
    ) {
        return result;
    }

    extractContext ( pProperties, & context->get.physicalDevice.memory );
    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: allocateMemory (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( MemoryAllocateInfo )     const * pAllocateInfo,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks,
        Type ( DeviceMemoryHandle )           * pHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pAllocateInfo == nullptr || pHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkAllocateMemory (
            deviceHandle,
            prepareContext ( & context->allocate.memory, pAllocateInfo ),
            AllocatorHandler :: apply ( pAllocationCallbacks ),
            pHandle
    );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PAGEABLE_DEVICE_LOCAL_MEMORY_AVAILABLE
auto engine :: vulkan :: setDeviceMemoryPriority (
        Type ( DeviceHandle )       deviceHandle,
        Type ( DeviceMemoryHandle ) memoryHandle,
        float                       priority
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || memoryHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkSetDeviceMemoryPriorityEXT (
            deviceHandle,
            memoryHandle,
            priority
    );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_WIN32_AVAILABLE
auto engine :: vulkan :: getMemoryWin32Handle (
                Type ( DeviceHandle )                       deviceHandle,
                Type ( MemoryGetWin32HandleInfo )   const * pInfo,
                HANDLE                                    * pHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pInfo == nullptr || pHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire ();

    return APICaller.vkGetMemoryWin32Handle (
            deviceHandle,
            toVulkanFormat ( & context->get.memory.win32.info, pInfo ),
            pHandle
    );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_WIN32_AVAILABLE
auto engine :: vulkan :: getMemoryWin32HandleNVidia (
                Type ( DeviceHandle )                       deviceHandle,
                Type ( DeviceMemoryHandle )                 memoryHandle,
                Type ( ExternalMemoryHandleTypeFlagNVidia ) type,
                HANDLE                                    * pHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || memoryHandle == nullptr || pHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkGetMemoryWin32HandleNV (
            deviceHandle,
            memoryHandle,
            static_cast < VkExternalMemoryHandleTypeFlagsNV > ( type ),
            pHandle
    );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_WIN32_AVAILABLE
auto engine :: vulkan :: getMemoryWin32HandleProperties (
                Type ( DeviceHandle )                   deviceHandle,
                Type ( ExternalmemoryHandleTypeFlag )   type,
                HANDLE                                  handle,
                Type ( MemoryWin32HandleProperties )  * pProperties
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || handle == nullptr || pProperties == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire ();

    if (
            auto result = APICaller.vkGetMemoryWin32Handle (
                    deviceHandle,
                    static_cast < VkExternalMemoryHandleTypeFlagBits > ( type ),
                    handle
                    & context->get.memory.win32.properties
            ); result != ResultSuccess
    ) {
        return result;
    }

    (void) fromVulkanFormat ( pProperties, & context->get.memory.win32.properties );
    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_FD_AVAILABLE
auto engine :: vulkan :: getMemoryFd (
        Type ( DeviceHandle )               deviceHandle,
        Type ( MemoryGetFdInfo )    const * pInfo,
        int                               * pFd
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pInfo == nullptr || pFd == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire ();

    return APICaller.vkGetMemoryFdKHR (
            deviceHandle,
            toVulkanFormat ( & context->get.memory.fd.info, pInfo ),
            pFd
    );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_FD_AVAILABLE
auto engine :: vulkan :: getMemoryFdProperties (
        Type ( DeviceHandle )                    deviceHandle,
        Type ( ExternalMemoryHandleTypeFlag )    type,
        int                                      fd,
        Type ( MemoryFdProperties )            * pProperties
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pProperties == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire ();

    if (
            auto result = APICaller.vkGetMemoryFdPropertiesKHR(
                    deviceHandle,
                    static_cast < VkExternalMemoryHandleTypeFlagBits > ( type ),
                    fd,
                    & context->get.memory.fd.properties
            ); result != ResultSuccess
    ) {
        return result;
    }

    (void) fromVulkanFormat ( pProperties, & context->get.memory.fd.properties );
    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTERNAL_MEMORY_HOST_AVAILABLE
auto engine :: vulkan :: getMemoryHostPointerProperties (
        Type ( DeviceHandle )                       deviceHandle,
        Type ( ExternalMemoryHandleTypeFlag )       type,
        void                                const * pHostPointer,
        Type ( MemoryHostPointerProperties )      * pProperties
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pProperties == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire ();

    if (
            auto result = APICaller.vkGetMemoryHostPointerPropertiesEXT (
                    deviceHandle,
                    static_cast < VkExternalMemoryHandleTypeFlagBits > ( type ),
                    pHostPointer,
                    & context->get.memory.platformIndependent.properties
            ); result != ResultSuccess
    ) {
        return result;
    }

    (void) fromVulkanFormat ( pProperties, & context->get.memory.platformIndependent.properties );
    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_RDMA_AVAILABLE
auto engine :: vulkan :: getMemoryRemoteAddressNVidia (
        Type ( DeviceHandle )                               deviceHandle,
        Type ( MemoryGetRemoteAddressInfoNVidia )   const * pInfo,
        Type ( RemoteAddressNVidia )                      * pAddress
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pInfo == nullptr || pAddress == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire ();

    return APICaller.vkGetMemoryRemoteAddressNV (
            deviceHandle,
            toVulkanFormat ( & context->get.memory.platformIndependent.remoteAddress, pInfo ),
            pAddress
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: freeMemory (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( DeviceMemoryHandle )             memoryHandle,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pAllocationCallbacks == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkFreeMemory (
            deviceHandle,
            memoryHandle,
            AllocatorHandler :: apply ( pAllocationCallbacks )
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: mapMemory (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( DeviceMemoryHandle )             memoryHandle,
        Type ( DeviceSize )                     offset,
        Type ( DeviceSize )                     size,
        Type ( MemoryMapFlags )                 flags,
        void                                 ** ppData
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || memoryHandle == nullptr || ppData == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkMapMemory (
            deviceHandle,
            memoryHandle,
            offset,
            size,
            flags,
            ppData
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: flushMappedMemoryRanges (
        Type ( DeviceHandle )               deviceHandle,
        cds :: uint32                       memoryRangeCount,
        Type ( MappedMemoryRange )  const * pMemoryRanges
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pMemoryRanges == nullptr || memoryRangeCount == 0U ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkFlushMappedMemoryRanges (
            deviceHandle,
            memoryRangeCount,
            prepareContext ( & context->other.flushMappedMemoryRanges, memoryRangeCount, pMemoryRanges )
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: invalidateMappedMemoryRanges (
        Type ( DeviceHandle )               deviceHandle,
        cds :: uint32                       memoryRangeCount,
        Type ( MappedMemoryRange )  const * pMemoryRanges
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pMemoryRanges == nullptr || memoryRangeCount == 0U ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkInvalidateMappedMemoryRanges (
            deviceHandle,
            memoryRangeCount,
            prepareContext ( & context->other.flushMappedMemoryRanges, memoryRangeCount, pMemoryRanges )
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: unmapMemory (
        Type ( DeviceHandle )               deviceHandle,
        Type ( DeviceMemoryHandle )         deviceMemoryHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || deviceMemoryHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkUnmapMemory (
            deviceHandle,
            deviceMemoryHandle
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: getDeviceMemoryCommitment (
        Type ( DeviceHandle )               deviceHandle,
        Type ( DeviceMemoryHandle )         deviceMemoryHandle,
        Type ( DeviceSize )               * pCommittedMemoryInBytes
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || deviceMemoryHandle == nullptr || pCommittedMemoryInBytes == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkGetDeviceMemoryCommitment (
            deviceHandle,
            deviceMemoryHandle,
            pCommittedMemoryInBytes
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto engine :: vulkan :: getDeviceGroupPeerMemoryFeatures (
        Type ( DeviceHandle )               deviceHandle,
        cds :: uint32                       heapIndex,
        cds :: uint32                       localDeviceIndex,
        cds :: uint32                       remoteDeviceIndex,
        Type ( PeerMemoryFeatureFlags )   * pPeerMemoryFeatures
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pPeerMemoryFeatures == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkGetDeviceGroupPeerMemoryFeatures (
            deviceHandle,
            heapIndex,
            localDeviceIndex,
            remoteDeviceIndex,
            pPeerMemoryFeatures
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
auto engine :: vulkan :: getDeviceMemoryOpaqueCaptureAddress (
        Type ( DeviceHandle )                                   deviceHandle,
        Type ( DeviceMemoryOpaqueCaptureAddressInfo )   const * pInfo,
        cds :: uint64                                         * pResult
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pInfo == nullptr || pResult == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    uint64_t result;

    if (
            auto lResult = APICaller.vkGetDeviceMemoryOpaqueCaptureAddress (
                    & result,
                    deviceHandle,
                    toVulkanFormat ( & context->get.memory.platformIndependent.opaqueInfo, pInfo )
            ); lResult != ResultSuccess
    ) {
        return lResult;
    }

    * pResult = result;
    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: createBuffer (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( BufferCreateInfo )       const * pCreateInfo,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks,
        Type ( BufferHandle )                 * pHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pCreateInfo == nullptr || pHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkCreateBuffer (
            deviceHandle,
            prepareContext ( & context->create.buffer.buffer, pCreateInfo ),
            AllocatorHandler ::apply ( pAllocationCallbacks ),
            pHandle
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: destroyBuffer (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( BufferHandle )                   bufferHandle,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || bufferHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkDestroyBuffer (
            deviceHandle,
            bufferHandle,
            AllocatorHandler ::apply ( pAllocationCallbacks )
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: createBufferView (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( BufferViewCreateInfo )   const * pCreateInfo,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks,
        Type ( BufferViewHandle )             * pHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pCreateInfo == nullptr || pHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkCreateBufferView (
            deviceHandle,
            toVulkanFormat ( & context->create.buffer.view.createInfo, pCreateInfo ),
            AllocatorHandler ::apply ( pAllocationCallbacks ),
            pHandle
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: destroyBufferView (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( BufferViewHandle )               viewHandle,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || viewHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkDestroyBufferView (
            deviceHandle,
            viewHandle,
            AllocatorHandler ::apply ( pAllocationCallbacks )
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: createImage (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( ImageCreateInfo )        const * pCreateInfo,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks,
        Type ( ImageHandle )                  * pHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pCreateInfo == nullptr || pHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    return APICaller.vkCreateImage (
            deviceHandle,
            prepareContext ( & context->create.image.image, pCreateInfo ),
            AllocatorHandler ::apply ( pAllocationCallbacks ),
            pHandle
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: getImageSubresourceLayout (
        Type ( DeviceHandle )               deviceHandle,
        Type ( ImageHandle )                imageHandle,
        Type ( ImageSubresource )   const * pSubresource,
        Type ( SubresourceLayout )        * pLayout
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || imageHandle == nullptr || pSubresource == nullptr || pLayout == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    if (
            auto result = APICaller.vkGetImageSubresourceLayout (
                    deviceHandle,
                    imageHandle,
                    toVulkanFormat ( & context->get.image.subresourceLayout.subresource, pSubresource ),
                    & context->get.image.subresourceLayout.layout
            ); result != ResultSuccess
    ) {
        return result;
    }

    (void) fromVulkanFormat ( pLayout, & context->get.image.subresourceLayout.layout );
    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_DRM_FORMAT_MODIFIER_AVAILABLE
auto engine :: vulkan :: getImageDrmFormatModifierProperties (
        Type ( DeviceHandle )                               deviceHandle,
        Type ( ImageHandle )                                imageHandle,
        Type ( ImageDrmFormatModifierProperties )         * pProperties
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || imageHandle == nullptr || pProperties == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    if (
            auto result = APICaller.vkGetImageDrmFormatModifierPropertiesEXT (
                    deviceHandle,
                    imageHandle,
                    & context->get.image.drmFormatModifier.properties
            ); result != ResultSuccess
    ) {
        return result;
    }

    (void) fromVulkanFormat ( pProperties, & context->get.image.drmFormatModifier.properties );
    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: destroyImage (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( ImageHandle )                    imageHandle,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || imageHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkDestroyImage (
            deviceHandle,
            imageHandle,
            AllocatorHandler :: apply ( pAllocationCallbacks )
    );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
auto engine :: vulkan :: createAccelerationStructureNVidia (
        Type ( DeviceHandle )                                   deviceHandle,
        Type ( AccelerationStructureCreateInfoNVidia )  const * pCreateInfo,
        Type ( AllocationCallbacks )                    const * pAllocationCallbacks,
        Type ( AccelerationStructureHandleNVidia )            * pHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pCreateInfo == nullptr || pHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkCreateAccelerationStructureNV (
            deviceHandle,
            prepareContext ( & ContextManager :: acquire()->create.accelerationStructure.nvidia, pCreateInfo ),
            AllocatorHandler :: apply ( pAllocationCallbacks ),
            pHandle
    );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
auto engine :: vulkan :: createAccelerationStructure (
        Type ( DeviceHandle )                                   deviceHandle,
        Type ( AccelerationStructureCreateInfo )        const * pCreateInfo,
        Type ( AllocationCallbacks )                    const * pAllocationCallbacks,
        Type ( AccelerationStructureHandle )                  * pHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pCreateInfo == nullptr || pHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkCreateAccelerationStructureKHR (
            deviceHandle,
            prepareContext ( & ContextManager :: acquire()->create.accelerationStructure.khronos, pCreateInfo ),
            AllocatorHandler :: apply ( pAllocationCallbacks ),
            pHandle
    );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
auto engine :: vulkan :: getAccelerationStructureBuildSizes (
        Type ( DeviceHandle )                                   deviceHandle,
        Type ( AccelerationStructureBuildType )                 buildType,
        Type ( AccelerationStructureBuildGeometryInfo ) const * pBuildInfo,
        cds :: uint32                                   const * pMaxPrimitiveCounts,
        Type ( AccelerationStructureBuildSizesInfo )          * pSizeInfo
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pBuildInfo == nullptr || pSizeInfo == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    if (
            auto result = APICaller.vkGetAccelerationStructureBuildSizesKHR (
                    deviceHandle,
                    static_cast < VkAccelerationStructureBuildTypeKHR > ( buildType ),
                    prepareContext ( & context->get.accelerationStructure.buildSizes, pBuildInfo ),
                    & pMaxPrimitiveCounts[0],
                    & context->get.accelerationStructure.buildSizes.sizesInfo
            ); result != ResultSuccess
    ) {
        return result;
    }

    (void) fromVulkanFormat ( pSizeInfo, & context->get.accelerationStructure.buildSizes.sizesInfo );
    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
auto engine :: vulkan :: destroyAccelerationStructureNVidia (
        Type ( DeviceHandle )                       deviceHandle,
        Type ( AccelerationStructureHandleNVidia )  accelerationStructureHandle,
        Type ( AllocationCallbacks )        const * pAllocationCallbacks
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || accelerationStructureHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkDestroyAccelerationStructureNV (
            deviceHandle,
            accelerationStructureHandle,
            AllocatorHandler :: apply ( pAllocationCallbacks )
    );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
auto engine :: vulkan :: destroyAccelerationStructure (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( AccelerationStructureHandle )    accelerationStructureHandle,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || accelerationStructureHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkDestroyAccelerationStructureKHR (
            deviceHandle,
            accelerationStructureHandle,
            AllocatorHandler :: apply ( pAllocationCallbacks )
    );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
auto engine :: vulkan :: getAccelerationStructureMemoryRequirementsNVidia (
        Type ( DeviceHandle )                                               deviceHandle,
        Type ( AccelerationStructureMemoryRequirementsInfoNVidia )  const * pInfo,
        Type ( MemoryRequirements2 )                                      * pRequirements
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pInfo == nullptr || pRequirements == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

    if (
            auto result = APICaller.vkGetAccelerationStructureMemoryRequirementsNV (
                    deviceHandle,
                    toVulkanFormat ( & context->get.accelerationStructure.memoryRequirements.requirements, pInfo ),
                    prepareContext ( & context->get.accelerationStructure.memoryRequirements, pRequirements )
            ); result != ResultSuccess
    ) {
        return result;
    }

    extractContext ( pRequirements, & context->get.accelerationStructure.memoryRequirements );
    return ResultSuccess;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
auto engine :: vulkan :: bindAccelerationStructureMemoryNVidia (
        Type ( DeviceHandle )                                       deviceHandle,
        cds :: uint32                                               count,
        Type ( BindAccelerationStructureMemoryInfoNVidia )  const * pInfos
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pInfos == nullptr || count == 0U ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkBindAccelerationStructureMemoryNV (
            deviceHandle,
            count,
            prepareContext ( & ContextManager :: acquire()->bind.accelerationStructureMemory, count, & pInfos[0] )
    );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
auto engine :: vulkan :: getAccelerationStructureHandleNVidia (
        Type ( DeviceHandle )                         deviceHandle,
        Type ( AccelerationStructureHandleNVidia )    accelerationStructureHandle,
        cds :: uint64                                 dataSize,
        void                                        * pData
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || accelerationStructureHandle == nullptr || pData == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkGetAccelerationStructureHandleNV (
            deviceHandle,
            accelerationStructureHandle,
            dataSize,
            pData
    );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
auto engine :: vulkan :: getAccelerationStructureDeviceAddress (
        Type ( DeviceHandle )                                   deviceHandle,
        Type ( AccelerationStructureDeviceAddressInfo ) const * pInfo,
        Type ( DeviceAddress )                                * pResult
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pInfo == nullptr || pResult == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    return APICaller.vkGetAccelerationStructureDeviceAddressKHR (
            pResult,
            deviceHandle,
            toVulkanFormat ( & ContextManager :: acquire()->get.accelerationStructure.deviceAddress.info, pInfo )
    );
}
#endif

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
#include <calls/util/DumpManager.hpp>

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkEnumerateInstanceVersion",
            "Queries the version of instance-level functionality supported by the implementation",
            pVersion
    );

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkGetInstanceProcAddr",
            "Obtains Function Pointers for all Vulkan commands",
            nullptr,
            functionName,
            pFunctionHandle
    );

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkGetInstanceProcAddr",
            "Obtains Function Pointers for all Vulkan commands",
            instanceHandle,
            functionName,
            pFunctionHandle
    );

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkGetDeviceProcAddr",
            "Obtains Function Pointers for all Vulkan Device commands",
            deviceHandle,
            functionName,
            pFunctionHandle
    );

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: CreateInstance,
            "vkCreateInstance",
            "Creates a Vulkan Instance Object",
            pCreateInfo,
            pAllocationCallbacks,
            pInstanceHandle
    );

#endif

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

    auto context = ContextManager :: acquire();
    auto arrayPack = DumpedArray {
        .pCount = pCount,
        .type   = ParameterType :: LayerProperties,
        .size   = sizeof ( Type ( LayerProperties ) ),
        .pArray = pProperties
    };

    prepareDump (
            context.data(),
            SharedContextType :: EnumerateLayerProperties,
            "vkEnumerateInstanceLayerProperties",
            "Queries Available Layers for instance creation",
            pCount,
            arrayPack
    );

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

#if ! __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    auto context = ContextManager :: acquire();

#endif

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

    auto context = ContextManager :: acquire();

    auto arrayPack = DumpedArray {
            .pCount = pCount,
            .type   = ParameterType :: LayerProperties,
            .size   = sizeof ( Type ( LayerProperties ) ),
            .pArray = pProperties
    };

    prepareDump (
            context.data(),
            SharedContextType :: EnumerateLayerProperties,
            "vkEnumerateDeviceLayerProperties",
            "Queries Available Layers for device creation. Based on supported physical device layers",
            physicalDeviceHandle,
            pCount,
            arrayPack
    );

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

#if ! __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    auto context = ContextManager :: acquire();

#endif

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

    auto context = ContextManager :: acquire();

    auto arrayPack = DumpedArray {
        .pCount = pCount,
        .type   = ParameterType :: ExtensionProperties,
        .size   = sizeof ( Type ( ExtensionProperties ) ),
        .pArray = pProperties
    };

    prepareDump (
            context.data(),
            SharedContextType :: EnumerateExtensionProperties,
            "vkEnumerateInstanceExtensionProperties",
            "Queries Available Instance Extensions",
            layerName,
            pCount,
            arrayPack
    );

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

#if ! __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    auto context = ContextManager :: acquire();

#endif

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

    auto context = ContextManager :: acquire();
    auto arrayPack = DumpedArray {
        .pCount = pCount,
        .type   = ParameterType::Handle,
        .size   = sizeof ( Type ( PhysicalDeviceHandle ) ),
        .pArray = pDevices
    };

    prepareDump (
            context.data(),
            SharedContextType :: EnumeratePhysicalDevices,
            "vkEnumeratePhysicalDevices",
            "Queries Available Physical Devices",
            handle,
            pCount,
            arrayPack
    );

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

#if ! __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    auto context = ContextManager :: acquire();

#endif

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

    auto context = ContextManager :: acquire();
    auto countersPack = DumpedArray {
        .pCount = pCount,
        .type   = ParameterType :: PerformanceCounter,
        .size   = sizeof ( Type ( PerformanceCounter ) ),
        .pArray = pCounters
    };

    auto descriptionsPack = DumpedArray {
        .pCount = pCount,
        .type   = ParameterType :: PerformanceCounterDescription,
        .size   = sizeof ( Type ( PerformanceCounterDescription ) ),
        .pArray = pDescriptions
    };

    prepareDump (
            context.data(),
            SharedContextType :: EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCounters,
            "vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR",
            "Queries Available Physical Device Queue Family Performance Query Counters",
            physicalDeviceHandle,
            queueFamilyIndex,
            pCount,
            countersPack,
            descriptionsPack
    );

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

#if ! __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    auto context = ContextManager :: acquire();

#endif

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

    auto context = ContextManager :: acquire();
    auto arrayPack = DumpedArray {
        .pCount = pCount,
        .type   = ParameterType :: PhysicalDeviceGroupProperties,
        .size   = sizeof ( Type ( PhysicalDeviceGroupProperties ) ),
        .pArray = pProperties
    };

    prepareDump (
            context.data(),
            SharedContextType :: EnumeratePhysicalDeviceGroups,
            "vkEnumeratePhysicalDeviceGroups",
            "Queries Available Physical Device Groups",
            instanceHandle,
            pCount,
            arrayPack
    );

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

#if ! __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    auto context = ContextManager :: acquire();

#endif

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

    auto context = ContextManager :: acquire();
    auto arrayPack = DumpedArray {
        .pCount = pCount,
        .type   = ParameterType :: ExtensionProperties,
        .size   = sizeof ( Type ( ExtensionProperties ) ),
        .pArray = pProperties
    };

    prepareDump (
            context.data(),
            SharedContextType :: EnumerateExtensionProperties,
            "vkEnumerateDeviceExtensionProperties",
            "Queries Available Device Extensions",
            handle,
            layerName,
            pCount,
            arrayPack
    );

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

#if ! __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    auto context = ContextManager :: acquire();

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: CreateInstance,
            "vkCreateDebugUtilsMessengerEXT",
            "Creates a Debug Messenger Object",
            instanceHandle,
            pCreateInfo,
            pAllocationCallbacks,
            pHandle
    );

#endif

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "glfwCreateWindowSurface",
            "Creates a Surface Object ( GLFW )",
            instanceHandle,
            pWindowHandle,
            pAllocationCallbacks,
            pSurfaceHandle
    );

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

    auto context = ContextManager :: acquire();

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType::CreateDevice,
            "vkCreateDevice",
            "Creates a Logical Device Object",
            physicalDeviceHandle,
            pCreateInfo,
            pAllocationCallbacks,
            pDeviceHandle
    );

#endif

    return APICaller.vkCreateDevice (
            physicalDeviceHandle,
            prepareContext ( & context.data().create.device, pCreateInfo ),
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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkDestroyInstance",
            "Destroys an Instance Object",
            handle,
            pAllocationCallbacks
    );

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkDestroyDebugUtilsMessengerEXT",
            "Destroys a Debug Messenger Object",
            instanceHandle,
            debugMessengerHandle,
            pAllocationCallbacks
    );

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkDestroySurfaceKHR",
            "Destroys a Surfce Object",
            instanceHandle,
            surfaceHandle,
            pAllocationCallbacks
    );

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkDestroyDevice",
            "Destroys a Logical Device Object",
            handle,
            pAllocationCallbacks
    );

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: GetPhysicalDeviceProperties,
            "vkGetPhysicalDeviceProperties",
            "Queries Physical Device Properties",
            handle,
            pProperties
    );

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: GetPhysicalDeviceFeatures,
            "vkGetPhysicalDeviceFeatures",
            "Queries Physical Device Features",
            physicalDeviceHandle,
            pFeatures
    );

#endif

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

    prepareDump (
            context.data(),
            SharedContextType :: GetPhysicalDeviceProperties,
            "vkGetPhysicalDeviceProperties2",
            "Queries Physical Device Properties",
            handle,
            pProperties
    );

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

    prepareDump (
            context.data(),
            SharedContextType :: GetPhysicalDeviceFeatures,
            "vkGetPhysicalDeviceFeatures2",
            "Queries Physical Device Features",
            physicalDeviceHandle,
            pFeatures
    );

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

    auto context = ContextManager :: acquire();
    auto arrayPack = DumpedArray {
        .pCount = pCount,
        .type   = ParameterType :: QueueFamilyProperties,
        .size   = sizeof ( Type ( QueueFamilyProperties ) ),
        .pArray = pProperties
    };

    prepareDump (
            context.data(),
            SharedContextType :: GetPhysicalDeviceQueueFamilyProperties,
            "vkGetPhysicalDeviceQueueFamilyProperties",
            "Queries Physical Device Queue Family Properties",
            physicalDeviceHandle,
            pCount,
            arrayPack
    );

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

#if ! __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    auto context = ContextManager :: acquire();

#endif

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

    auto context = ContextManager :: acquire();
    auto arrayPack = DumpedArray {
        .pCount = pCount,
        .type   = ParameterType :: Structure,
        .size   = sizeof ( Type ( QueueFamilyExtendedProperties ) ),
        .pArray = pProperties
    };

    prepareDump (
            context.data(),
            SharedContextType :: GetPhysicalDeviceQueueFamilyProperties,
            "vkGetPhysicalDeviceQueueFamilyProperties2",
            "Queries Physical Device Queue Family Properties",
            physicalDeviceHandle,
            pCount,
            arrayPack
    );

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

#if ! __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    auto context = ContextManager :: acquire();

#endif

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkGetPhysicalDeviceSurfaceSupportKHR",
            "Queries Physical Device Surface Support",
            deviceHandle,
            queueFamilyIndex,
            surfaceHandle,
            pSupport
    );

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkGetDeviceQueue",
            "Acquires a Queue Handle from a given Queue Family and a Device",
            deviceHandle,
            queueFamilyIndex,
            queueIndex,
            pQueueHandle
    );

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: GetDeviceQueue,
            "vkGetDeviceQueue2",
            "Acquires a Queue Handle from a given Queue Family and a Device",
            deviceHandle,
            pQueueInfo,
            pQueueHandle
    );

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: GetSurface,
            "vkGetPhysicalDeviceSurfaceCapabilitiesKHR",
            "Queries a Physical Device's Surface Capabilities",
            deviceHandle,
            surfaceHandle,
            pSurfaceCapabilities
    );

#endif

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

    auto context = ContextManager :: acquire();
    auto arrayPack = DumpedArray {
        .pCount = pCount,
        .type   = ParameterType :: SurfaceFormat,
        .size   = sizeof ( Type ( SurfaceFormat ) ),
        .pArray = pFormats
    };

    prepareDump (
            context.data(),
            SharedContextType :: GetSurface,
            "vkGetPhysicalDeviceSurfaceFormatsKHR",
            "Queries a Physical Device's Surface Formats",
            deviceHandle,
            surfaceHandle,
            pCount,
            arrayPack
    );

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

#if ! __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    auto context = ContextManager :: acquire();

#endif

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

    auto context = ContextManager :: acquire();
    auto arrayPack = DumpedArray {
        .pCount = pCount,
        .type   = ParameterType :: UInt32,
        .size   = sizeof ( Type ( PresentMode ) ),
        .pArray = pPresentModes
    };

    prepareDump (
            context.data(),
            SharedContextType :: GetSurface,
            "vkGetPhysicalDeviceSurfacePresentModesKHR",
            "Queries a Physical Device's Surface Present Modes",
            deviceHandle,
            surfaceHandle,
            pCount,
            arrayPack
    );

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

#if ! __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    auto context = ContextManager :: acquire();

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: GetSurface,
            "vkGetPhysicalDeviceSurfaceCapabilities2EXT",
            "Queries a Physical Device's Surface Capabilities",
            deviceHandle,
            surfaceHandle,
            pSurfaceCapabilities
    );

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    auto arrayPack = DumpedArray {
        .pCount = pCount,
        .type   = ParameterType::Structure,
        .size   = sizeof ( Type ( SurfaceFormat2 ) ),
        .pArray = pFormats
    };

    prepareDump (
            context.data(),
            SharedContextType :: GetSurface,
            "vkGetPhysicalDeviceSurfaceFormats2KHR",
            "Queries a Physical Device's Surface Formats",
            deviceHandle,
            pSurfaceInfo,
            pCount,
            arrayPack
    );

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: CreateSwapChain,
            "vkCreateSwapchainKHR",
            "Creates a Swap Chain Object",
            deviceHandle,
            pCreateInfo,
            pAllocationCallbacks,
            pHandle
    );

#endif

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkDestroySwapchainKHR",
            "Destroy a Swap Chain Object",
            deviceHandle,
            handle,
            pAllocationCallbacks
    );

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

    auto context = ContextManager :: acquire();
    auto arrayPack = DumpedArray {
        .pCount = pCount,
        .type   = ParameterType :: Handle,
        .size   = sizeof ( Type ( ImageHandle ) ),
        .pArray = pImageHandles
    };

    prepareDump (
            context.data(),
            SharedContextType :: GetSwapChain,
            "vkGetSwapchainImagesKHR",
            "Acquire the Image Handles of a SwapChain",
            deviceHandle,
            swapChainHandle,
            pCount,
            arrayPack
    );

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

#if ! __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    auto context = ContextManager :: acquire();

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: CreateImageView,
            "vkCreateImageView",
            "Creates an Image View object",
            deviceHandle,
            pCreateInfo,
            pAllocationCallbacks,
            pHandle
    );

#endif

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkDestroyImageView",
            "Destroys an Image View object",
            deviceHandle,
            handle,
            pAllocationCallbacks
    );

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: CreateCommandPool,
            "vkCreateCommandPool",
            "Creates a Command Pool Object",
            deviceHandle,
            pCreateInfo,
            pAllocationCallbacks,
            pHandle
    );

#endif

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkDestroyCommandPool",
            "Destroys a Command Pool object",
            deviceHandle,
            handle,
            pAllocationCallbacks
    );

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

    auto context = ContextManager :: acquire();
    auto flagsPack = Flags ( flags );

    prepareDump (
            context.data(),
            "vkResetCommandPool",
            "Resets a command pool's buffers",
            deviceHandle,
            handle,
            flagsPack
    );

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    auto arrayPack = DumpedArray {
        .pCount = & pAllocateInfo->commandBufferCount,
        .type   = ParameterType :: Handle,
        .size   = sizeof ( Type ( CommandBufferHandle ) ),
        .pArray = pHandles
    };

    prepareDump (
            context.data(),
            SharedContextType :: AllocateCommandBuffers,
            "vkAllocateCommandBuffers",
            "Allocates multiple command buffers from a command pool",
            deviceHandle,
            pAllocateInfo,
            arrayPack
    );

#endif

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

    auto context = ContextManager :: acquire();
    auto flagsPack = Flags ( flags );

    prepareDump (
            context.data(),
            "vkResetCommandBuffer",
            "Resets a command buffer",
            handle,
            flags
    );

#endif

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

    auto context = ContextManager :: acquire();
    auto arrayPack = DumpedArray {
        .pCount = & commandBufferCount,
        .type   = ParameterType :: Handle,
        .size   = sizeof ( Type ( CommandBufferHandle ) ),
        .pArray = pCommandBuffers
    };

    prepareDump (
            context.data(),
            "vkFreeCommandBuffers",
            "Frees several command buffers from a command pool",
            deviceHandle,
            commandPoolHandle,
            commandBufferCount,
            arrayPack
    );

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: BeginCommandBuffer,
            "vkBeginCommandBuffer",
            "Begins the recording of a command buffer",
            commandBufferHandle,
            pBeginInfo
    );

#endif

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkEndCommandBuffer",
            "Ends the recording of a command buffer",
            commandBufferHandle
    );

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

    auto context = ContextManager :: acquire();
    auto flagsPack = Flags ( flags );

    prepareDump (
            context.data(),
            "vkTrimCommandPool",
            "Trims a command pool, removing unused handles",
            deviceHandle,
            handle,
            flagsPack
    );

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    auto arrayPack = DumpedArray {
        .pCount = & submitCount,
        .type   = ParameterType :: Structure,
        .size   = sizeof ( Type ( SubmitInfo ) ),
        .pArray = pSubmits
    };

    prepareDump (
            context.data(),
            SharedContextType :: SubmitQueue,
            "vkQueueSubmit",
            "Submits a set of commands onto a queue",
            queueHandle,
            submitCount,
            arrayPack,
            fenceHandle
    );

#endif

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

    auto context = ContextManager :: acquire();
    auto arrayPack = DumpedArray {
        .pCount = & commandBufferCount,
        .type   = ParameterType :: Handle,
        .size   = sizeof ( Type ( CommandBufferHandle ) ),
        .pArray = pSecondaryCommandBufferHandles
    };

    prepareDump (
            context.data(),
            "vkCmdExecuteCommands",
            "Executes a set of secondary command buffers",
            primaryCommandBufferHandle,
            commandBufferCount,
            arrayPack
    );

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    auto arrayPack = DumpedArray {
        .pCount = & submitCount,
        .type   = ParameterType :: Structure,
        .size   = sizeof ( Type ( SubmitInfo2 ) ),
        .pArray = pSubmits
    };

    prepareDump (
            context.data(),
            SharedContextType :: SubmitQueue,
            "vkQueueSubmit2",
            "Submits a set of commands onto a queue",
            queueHandle,
            submitCount,
            arrayPack,
            fenceHandle
    );

#endif

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkCmdSetDeviceMask",
            "Sets a device mask for a command buffer",
            commandBufferHandle,
            deviceMask
    );

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: CreateFence,
            "vkCreateFence",
            "Creates a Fence Object",
            deviceHandle,
            pCreateInfo,
            pAllocationCallbacks,
            pHandle
    );

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: GetFence,
            "vkGetFenceWin32HandleKHR",
            "Acquires an external win32 fence",
            deviceHandle,
            pInfo,
            pHandle
    );

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: GetFence,
            "vkGetFenceFdKHR",
            "Acquires an external fd fence",
            deviceHandle,
            pInfo,
            pHandle
    );

#endif

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkDestroyFence",
            "Destroys a Fence Object",
            deviceHandle,
            fenceHandle,
            pAllocationCallbacks
    );

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkGetFenceStatus",
            "Gets the status of a Fence Object",
            deviceHandle,
            fenceHandle
    );

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

    auto context = ContextManager :: acquire();
    auto arrayPack = DumpedArray {
        .pCount = & count,
        .type   = ParameterType::Handle,
        .size   = sizeof ( Type ( FenceHandle ) ),
        .pArray = pFences
    };

    prepareDump (
            context.data(),
            "vkResetFences",
            "Resets the status of multiple Fence Objects",
            deviceHandle,
            count,
            arrayPack
    );

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

    auto context = ContextManager :: acquire();
    auto arrayPack = DumpedArray {
            .pCount = & count,
            .type   = ParameterType::Handle,
            .size   = sizeof ( Type ( FenceHandle ) ),
            .pArray = pFences
    };

    prepareDump (
            context.data(),
            "vkWaitForFences",
            "Waits for multiple Fence Objects",
            deviceHandle,
            count,
            arrayPack,
            waitForAll,
            timeout
    );

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: RegisterEvent,
            "vkRegisterDeviceEventEXT",
            "Registers a Device Event",
            deviceHandle,
            pEventInfo,
            pAllocationCallbacks,
            pHandle
    );

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: RegisterEvent,
            "vkRegisterDisplayEventEXT",
            "Registers a Display Event",
            deviceHandle,
            displayHandle,
            pEventInfo,
            pAllocationCallbacks,
            pHandle
    );

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: ImportFenceWin32,
            "vkImportFenceWin32HandleKHR",
            "Imports a Win32 Fence Handle",
            deviceHandle,
            pInfo
    );

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: ImportFenceFd,
            "vkImportFenceFdKHR",
            "Imports a fd Fence Handle",
            deviceHandle,
            pInfo
    );

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: CreateSemaphore,
            "vkCreateSemaphore",
            "Creates a Semaphore Object",
            deviceHandle,
            pCreateInfo,
            pAllocationCallbacks,
            pHandle
    );

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: GetSemaphore,
            "vkGetSemaphoreWin32HandleKHR",
            "Acquires a Win32 Semaphore Handle",
            deviceHandle,
            pInfo,
            pHandle
    );

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: GetSemaphore,
            "vkGetSemaphoreFdKHR",
            "Acquires a Fd Semaphore Handle",
            deviceHandle,
            pInfo,
            pFd
    );

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: GetSemaphore,
            "vkGetSemaphoreZirconHandleFUCHSIA",
            "Acquires a Zircon Semaphore Handle",
            deviceHandle,
            pInfo,
            pHandle
    );

#endif

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkDestroySemaphore",
            "Destroys a Semaphore Object",
            deviceHandle,
            semaphoreHandle,
            pAllocationCallbacks
    );

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkGetSemaphoreCounterValue",
            "Gets a Semaphore Object's Counter Value",
            deviceHandle,
            semaphoreHandle,
            pValue
    );

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: WaitSemaphore,
            "vkWaitSemaphores",
            "Waits for multiple Semaphore Objects",
            deviceHandle,
            pWaitInfo,
            timeout
    );

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: SignalSemaphore,
            "vkSignalSemaphore",
            "Signals a Semaphore Objects",
            deviceHandle,
            pSignalInfo
    );

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: ImportSemaphoreWin32,
            "vkImportSemaphoreWin32HandleKHR",
            "Imports a win32 Semaphore Objects",
            deviceHandle,
            pInfo
    );

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: ImportSemaphoreFd,
            "vkImportSemaphoreFdKHR",
            "Imports a fd Semaphore Objects",
            deviceHandle,
            pInfo
    );

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: ImportSemaphoreZirconHandleInfoGoogle,
            "vkImportSemaphoreZirconHandleFUCHSIA",
            "Imports a Zircon Semaphore Objects",
            deviceHandle,
            pInfo
    );

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: CreateEvent,
            "vkCreateEvent",
            "Creates an Event Object",
            deviceHandle,
            pCreateInfo,
            pAllocationCallbacks,
            pHandle
    );

#endif

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkDestroyEvent",
            "Destroys an Event Object",
            deviceHandle,
            handle,
            pAllocationCallbacks
    );

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkGetEventStatus",
            "Acquires the status of an event object",
            deviceHandle,
            handle
    );

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkSetEvent",
            "Sets an event to triggered status",
            deviceHandle,
            handle
    );

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkResetEvent",
            "Resets an event to un-triggered status",
            deviceHandle,
            handle
    );

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: SetCommandBufferEvent,
            "vkCmdSetEvent2",
            "Load a command buffer with a request to set an event to triggered status",
            commandBufferHandle,
            eventHandle,
            pDependencyInfo
    );

#endif

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

    auto context = ContextManager :: acquire();
    auto flagsPack = Flags ( flags );

    prepareDump (
            context.data(),
            "vkCmdSetEvent",
            "Load a command buffer with a request to set an event to triggered status",
            commandBufferHandle,
            eventHandle,
            flagsPack
    );

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

    auto context = ContextManager :: acquire();
    auto flagsPack = Flags ( flags );

    prepareDump (
            context.data(),
            "vkCmdSetEvent",
            "Load a command buffer with a request to reset an event to un-triggered status",
            commandBufferHandle,
            eventHandle,
            flagsPack
    );

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    auto eventHandlesPack = DumpedArray {
        .pCount = & eventCount,
        .type   = ParameterType :: Handle,
        .size   = sizeof ( Type ( EventHandle ) ),
        .pArray = pEventHandles
    };

    auto dependencyInfosPack = DumpedArray {
        .pCount = & eventCount,
        .type   = ParameterType :: Structure,
        .size   = sizeof ( Type ( DependencyInfo ) ),
        .pArray = pDependencyInfos
    };

    prepareDump (
            context.data(),
            SharedContextType :: WaitCommandBufferEvent2,
            "vkCmdWaitEvents2",
            "Load a command buffer with a request to wait for a set of events before execution",
            commandBufferHandle,
            eventCount,
            eventHandlesPack,
            dependencyInfosPack
    );

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    auto eventHandlesPack = DumpedArray {
            .pCount = & eventCount,
            .type   = ParameterType :: Handle,
            .size   = sizeof ( Type ( EventHandle ) ),
            .pArray = pEventHandles
    };

    auto sourceFlagsPack = Flags ( sourceStageMask );
    auto destinationFlagsPack = Flags ( destinationStageMask );

    auto memoryBarrierArrayPack = DumpedArray {
            .pCount = & memoryBarrierCount,
            .type   = ParameterType :: Structure,
            .size   = sizeof ( Type ( MemoryBarrier ) ),
            .pArray = pMemoryBarriers
    };

    auto bufferMemoryBarrierArrayPack = DumpedArray {
            .pCount = & bufferMemoryBarrierCount,
            .type   = ParameterType :: Structure,
            .size   = sizeof ( Type ( BufferMemoryBarrier ) ),
            .pArray = pBufferMemoryBarriers
    };

    auto imageMemoryBarrierArrayPack = DumpedArray {
            .pCount = & imageMemoryBarrierCount,
            .type   = ParameterType :: Structure,
            .size   = sizeof ( Type ( ImageMemoryBarrier ) ),
            .pArray = pImageMemoryBarriers
    };

    prepareDump (
            context.data(),
            SharedContextType :: WaitCommandBufferEvent,
            "vkCmdWaitEvents",
            "Load a command buffer with a request to wait for a set of events before execution",
            commandBufferHandle,
            eventCount,
            eventHandlesPack,
            sourceFlagsPack,
            destinationFlagsPack,
            memoryBarrierCount,
            memoryBarrierArrayPack,
            bufferMemoryBarrierCount,
            bufferMemoryBarrierArrayPack,
            imageMemoryBarrierCount,
            imageMemoryBarrierArrayPack
    );

#endif

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkQueueWaitIdle",
            "Waits until the queue is idle",
            handle
    );

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkDeviceWaitIdle",
            "Waits until the device is idle",
            handle
    );

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: BeginCommandBufferRendering,
            "vkCmdBeginRendering",
            "Begins a dynamic rendering recording of a command buffer",
            handle,
            pRenderingInfo
    );

#endif

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkCmdEndRendering",
            "Ends a dynamic rendering recording of a command buffer",
            handle
    );

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: CreateRenderPass,
            "vkCreateRenderPass",
            "Creates a Render Pass Object",
            deviceHandle,
            pCreateInfo,
            pAllocationCallbacks,
            pHandle
    );

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: CreateRenderPass2,
            "vkCreateRenderPass2",
            "Creates a Render Pass Object",
            deviceHandle,
            pCreateInfo,
            pAllocationCallbacks,
            pHandle
    );

#endif

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkDestroyRenderPass",
            "Destroys a Render Pass Object",
            deviceHandle,
            renderPassHandle,
            pAllocationCallbacks
    );

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: CreateFrameBuffer,
            "vkCreateFramebuffer",
            "Creates a Frame Buffer Object",
            deviceHandle,
            pCreateInfo,
            pAllocationCallbacks,
            pHandle
    );

#endif

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkDestroyFramebuffer",
            "Destroys a Frame Buffer Object",
            deviceHandle,
            handle,
            pAllocationCallbacks
    );

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    auto contentsAsInt = static_cast < cds :: uint32 > ( subpassContents );

    prepareDump (
            context.data(),
            SharedContextType :: BeginRenderPass,
            "vkCmdBeginRenderPass",
            "Begins the recording of a render pass commands in a command buffer",
            commandBufferHandle,
            pInfo,
            contentsAsInt
    );

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: BeginRenderPass,
            "vkCmdBeginRenderPass2",
            "Begins the recording of a render pass commands in a command buffer",
            commandBufferHandle,
            pRenderPassBeginInfo,
            pSubpassBeginInfo
    );

#endif

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkGetRenderAreaGranularity",
            "Acquires the Render Area Granularity from a Render Pass",
            deviceHandle,
            renderPassHandle,
            pGranularity
    );

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkCmdNextSubpass",
            "Loads a command buffer to jump to the next subpass upon execution",
            commandBufferHandle,
            contents
    );

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: NextSubpass,
            "vkCmdNextSubpass2",
            "Loads a command buffer to jump to the next subpass upon execution",
            commandBufferHandle,
            pBeginInfo,
            pEndInfo
    );

#endif

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkCmdEndRenderPass",
            "Loads a command buffer to end a render pass upon execution",
            handle
    );

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: NextSubpass,
            "vkCmdEndRenderPass2",
            "Loads a command buffer to ends a render pass upon execution",
            handle,
            pInfo
    );

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: CreateShaderModule,
            "vkCreateShaderModule",
            "Creates a Shader Module Object",
            deviceHandle,
            pCreateInfo,
            pAllocationCallbacks,
            pShaderModuleHandle
    );

#endif

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkDestroyShaderModule",
            "Destroys a Shader Module Object",
            deviceHandle,
            shaderModuleHandle,
            pAllocationCallbacks
    );

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkCmdSetPatchControlPointsEXT",
            "Loads a command buffer to execute a setting of patch control points upon execution",
            commandBufferHandle,
            patchControlPoints
    );

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

    auto context = ContextManager :: acquire();
    auto arrayPack = DumpedArray {
        .pCount = pCount,
        .type   = ParameterType::Structure,
        .size   = sizeof ( Type ( CooperativeMatrixPropertiesNVidia ) ),
        .pArray = pProperties
    };

    prepareDump (
            context.data(),
            SharedContextType :: GetPhysicalDeviceCooperativeMatrixProperties,
            "vkGetPhysicalDeviceCooperativeMatrixPropertiesNV",
            "Acquires the properties of cooperative matrices from a physical device",
            physicalDeviceHandle,
            pCount,
            arrayPack
    );

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

#if ! __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    auto context = ContextManager :: acquire();

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: CreateValidationCache,
            "vkCreateValidationCacheEXT",
            "Create Validation Cache",
            deviceHandle,
            pCreateInfo,
            pAllocationCallbacks,
            pHandle
    );

#endif

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

    auto context = ContextManager :: acquire();
    auto arrayPack = DumpedArray {
        .pCount = & sourceCacheCount,
        .type   = ParameterType :: Handle,
        .size   = sizeof ( Type ( ValidationCacheHandle ) ),
        .pArray = pSourceCacheHandles
    };

    prepareDump (
            context.data(),
            "vkMergeValidationCachesEXT",
            "Merges a set of validation caches Validation Cache",
            deviceHandle,
            destinationCacheHandle,
            sourceCacheCount,
            arrayPack
    );

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkGetValidationCacheDataEXT",
            "Gets the data from a validation cache",
            deviceHandle,
            validationCacheHandle,
            pDataSize,
            pData
    );

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkDestroyValidationCacheEXT",
            "Destroys a validation cache",
            deviceHandle,
            validationCacheHandle,
            pAllocationCallbacks
    );

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    auto createInfosArrayPack = DumpedArray {
        .pCount = & count,
        .type   = ParameterType :: Structure,
        .size   = sizeof ( Type ( ComputePipelineCreateInfo ) ),
        .pArray = pCreateInfos
    };

    auto handlesArrayPack = DumpedArray {
        .pCount = & count,
        .type   = ParameterType :: Handle,
        .size   = sizeof ( Type ( PipelineHandle ) ),
        .pArray = pPipelineHandles
    };

    prepareDump (
            context.data(),
            SharedContextType :: CreateComputePipeline,
            "vkCreateComputePipelines",
            "Creates a set of compute pipelines",
            deviceHandle,
            pipelineCacheHandle,
            count,
            createInfosArrayPack,
            pAllocationCallbacks,
            handlesArrayPack
    );

#endif

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI",
            "Acquires a device subpass shading max workgroup size",
            deviceHandle,
            renderPassHandle,
            pMaxWorkgroupSize
    );

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    auto createInfosArrayPack = DumpedArray {
            .pCount = & count,
            .type   = ParameterType :: Structure,
            .size   = sizeof ( Type ( GraphicsPipelineCreateInfo ) ),
            .pArray = pCreateInfos
    };

    auto handlesArrayPack = DumpedArray {
            .pCount = & count,
            .type   = ParameterType :: Handle,
            .size   = sizeof ( Type ( PipelineHandle ) ),
            .pArray = pPipelineHandles
    };

    prepareDump (
            context.data(),
            SharedContextType :: CreateGraphicsPipeline,
            "vkCreateGraphicsPipelines",
            "Creates a set of graphics pipelines",
            deviceHandle,
            pipelineCacheHandle,
            count,
            createInfosArrayPack,
            pAllocationCallbacks,
            handlesArrayPack
    );

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    auto createInfosArrayPack = DumpedArray {
            .pCount = & count,
            .type   = ParameterType :: Structure,
            .size   = sizeof ( Type ( RayTracingPipelineCreateInfoNVidia ) ),
            .pArray = pCreateInfos
    };

    auto handlesArrayPack = DumpedArray {
            .pCount = & count,
            .type   = ParameterType :: Handle,
            .size   = sizeof ( Type ( PipelineHandle ) ),
            .pArray = pPipelineHandles
    };

    prepareDump (
            context.data(),
            SharedContextType :: CreateRayTracingPipelineNVidia,
            "vkCreateRayTracingPipelinesNV",
            "Creates a set of ray tracing pipelines",
            deviceHandle,
            pipelineCacheHandle,
            count,
            createInfosArrayPack,
            pAllocationCallbacks,
            handlesArrayPack
    );

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    auto createInfosArrayPack = DumpedArray {
            .pCount = & count,
            .type   = ParameterType :: Structure,
            .size   = sizeof ( Type ( RayTracingPipelineCreateInfo ) ),
            .pArray = pCreateInfos
    };

    auto handlesArrayPack = DumpedArray {
            .pCount = & count,
            .type   = ParameterType :: Handle,
            .size   = sizeof ( Type ( PipelineHandle ) ),
            .pArray = pPipelineHandles
    };

    prepareDump (
            context.data(),
            SharedContextType :: CreateRayTracingPipeline,
            "vkCreateRayTracingPipelines",
            "Creates a set of ray tracing pipelines",
            deviceHandle,
            deferredOperationHandle,
            pipelineCacheHandle,
            count,
            createInfosArrayPack,
            pAllocationCallbacks,
            handlesArrayPack
    );

#endif

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkGetRayTracingShaderGroupHandlesKHR",
            "Acquires a ray tracing pipeline's shader group handles",
            deviceHandle,
            pipelineHandle,
            firstGroup,
            groupCount,
            dataSize,
            pData
    );

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkGetRayTracingCaptureReplayShaderGroupHandlesKHR",
            "Acquires a ray tracing pipeline's capture replay shader group handles",
            deviceHandle,
            pipelineHandle,
            firstGroup,
            groupCount,
            dataSize,
            pData
    );

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkCompileDeferredNV",
            "Set a shader index to be deferredly compiled",
            deviceHandle,
            pipelineHandle,
            shader
    );

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkGetRayTracingShaderGroupStackSizeKHR",
            "Acquire the stack size of a shader group of a pipeline",
            deviceHandle,
            pipelineHandle,
            group,
            groupShader,
            pSize
    );

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkCmdSetRayTracingPipelineStackSizeKHR",
            "Load a command buffer to set the stack size of a pipeline upon execution",
            commandBufferHandle,
            pipelineStackSize
    );

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkDestroyPipeline",
            "Destroys a pipeline object",
            deviceHandle,
            pipelineHandle,
            pAllocationCallbacks
    );

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            "vkCreatePipelineCache",
            "Creates a pipeline cache object",
            deviceHandle,
            pCreateInfo,
            pAllocationCallbacks,
            pHandle
    );

#endif

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

    auto context = ContextManager :: acquire();
    auto arrayPack = DumpedArray {
        .pCount = & sourceCacheCount,
        .type   = ParameterType :: Handle,
        .size   = sizeof ( Type ( PipelineCacheHandle ) ),
        .pArray = pSourceCacheHandles
    };

    prepareDump (
            context.data(),
            "vkMergePipelineCaches",
            "Merges a set of pipeline caches",
            deviceHandle,
            destinationCacheHandle,
            sourceCacheCount,
            arrayPack
    );

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkGetPipelineCacheData",
            "Gets the data of a pipeline cache",
            deviceHandle,
            cacheHandle,
            pSize,
            pData
    );

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkDestroyPipelineCache",
            "Destroys a pipeline cache",
            deviceHandle,
            cacheHandle,
            pAllocationCallbacks
    );

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkCmdBindPipeline",
            "Binds a pipeline to be used by the GPU upon a command buffer's execution",
            commandBufferHandle,
            bindPoint,
            pipelineHandle
    );

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkCmdBindPipelineShaderGroupNV",
            "Binds a pipeline shader group to be used by the GPU upon a command buffer's execution",
            commandBufferHandle,
            bindPoint,
            pipelineHandle,
            groupIndex
    );

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    auto arrayPack = DumpedArray {
        .pCount = pCount,
        .type   = ParameterType :: Structure,
        .size   = sizeof ( Type ( PipelineExecutableProperties ) ),
        .pArray = pProperties
    };

    prepareDump (
            context.data(),
            SharedContextType :: GetPipelineProperties,
            "vkGetPipelineExecutablePropertiesKHR",
            "Acquires a pipeline's executable properties",
            deviceHandle,
            pPipelineInfo,
            pCount,
            arrayPack
    );

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    auto arrayPack = DumpedArray {
            .pCount = pCount,
            .type   = ParameterType :: Structure,
            .size   = sizeof ( Type ( PipelineExecutableStatistic ) ),
            .pArray = pStatistics
    };

    prepareDump (
            context.data(),
            SharedContextType :: GetPipelineStatistics,
            "vkGetPipelineExecutableStatisticsKHR",
            "Acquires a pipeline's executable statistics",
            deviceHandle,
            pPipelineExecutableInfo,
            pCount,
            arrayPack
    );

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    auto arrayPack = DumpedArray {
            .pCount = pCount,
            .type   = ParameterType :: Structure,
            .size   = sizeof ( Type ( PipelineExecutableInternalRepresentation ) ),
            .pArray = pRepresentations
    };

    prepareDump (
            context.data(),
            SharedContextType :: GetPipelineInternalRepresentations,
            "vkGetPipelineExecutableInternalRepresentationsKHR",
            "Acquires a pipeline's executable internal reprepsentations",
            deviceHandle,
            pPipelineExecutableInfo,
            pCount,
            arrayPack
    );

#endif

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkGetShaderInfoAMD",
            "Acquires Shader Information",
            deviceHandle,
            pipelineHandle,
            shaderStage,
            pDataSize,
            pData
    );

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            "vkGetPhysicalDeviceMemoryProperties2",
            "Acquires Physical Device Memory Properties",
            physicalDeviceHandle,
            pProperties
    );

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            "vkAllocateMemory",
            "Allocates host/device memory",
            deviceHandle,
            pAllocateInfo,
            pAllocationCallbacks,
            pHandle
    );

#endif

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkSetDeviceMemoryPriorityEXT",
            "Sets host/device memory priority",
            deviceHandle,
            memoryHandle,
            priority
    );

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: GetMemoryWin32
            "vkGetMemoryWin32HandleKHR",
            "Acquires a win32 external memory handle",
            deviceHandle,
            pInfo,
            pHandle
    );

#endif

    return APICaller.vkGetMemoryWin32HandleKHR (
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

    auto context = ContextManager :: acquire ();

    prepareDump (
            context.data(),
            "vkGetMemoryWin32HandleNV",
            "Acquires a win32 external memory handle",
            deviceHandle,
            memoryHandle,
            type,
            pHandle
    );

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: GetMemoryWin32
            "vkGetMemoryWin32HandlePropertiesKHR",
            "Acquires a win32 external memory handle properties",
            deviceHandle,
            type,
            handle,
            pProperties
    );

#endif

    if (
            auto result = APICaller.vkGetMemoryWin32HandlePropertiesKHR (
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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: GetMemoryFd,
            "vkGetMemoryFdKHR",
            "Acquires a fd external memory handle",
            deviceHandle,
            pInfo,
            pFd
    );

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: GetMemoryFd,
            "vkGetMemoryFdPropertiesKHR",
            "Acquires a fd external memory handle properties",
            deviceHandle,
            type,
            fd,
            pProperties
    );

#endif

    if (
            auto result = APICaller.vkGetMemoryFdPropertiesKHR (
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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: GetMemoryPlatformIndependent,
            "vkGetMemoryHostPointerPropertiesEXT",
            "Acquires a host pointer's memory properties",
            deviceHandle,
            type,
            pHostPointer,
            pProperties
    );

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: GetMemoryPlatformIndependent,
            "vkGetMemoryRemoteAddressNV",
            "Acquires a remote memory address",
            deviceHandle,
            pInfo,
            pAddress
    );

#endif

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkFreeMemory",
            "Frees host/device memory",
            deviceHandle,
            memoryHandle,
            pAllocationCallbacks
    );

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkMapMemory",
            "Maps memory to given layout",
            deviceHandle,
            memoryHandle,
            offset,
            size,
            flags,
            ppData
    );

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    auto arrayPack = DumpedArray {
        .pCount = & memoryRangeCount,
        .type   = ParameterType :: Structure,
        .size   = sizeof ( Type ( MappedMemoryRange ) ),
        .pArray = pMemoryRanges
    };

    prepareDump (
            context.data(),
            SharedContextType :: FlushMappedMemoryRanges,
            "vkFlushMappedMemoryRanges",
            "Flushes mapped memory ranges",
            deviceHandle,
            memoryRangeCount,
            arrayPack
    );

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    auto arrayPack = DumpedArray {
            .pCount = & memoryRangeCount,
            .type   = ParameterType :: Structure,
            .size   = sizeof ( Type ( MappedMemoryRange ) ),
            .pArray = pMemoryRanges
    };

    prepareDump (
            context.data(),
            SharedContextType :: FlushMappedMemoryRanges,
            "vkInvalidateMappedMemoryRanges",
            "Invalidates mapped memory ranges",
            deviceHandle,
            memoryRangeCount,
            arrayPack
    );

#endif

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkUnmapMemory",
            "Unmaps memory",
            deviceHandle,
            deviceMemoryHandle
    );

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkGetDeviceMemoryCommitment",
            "Acquire device memory commitment",
            deviceHandle,
            deviceMemoryHandle,
            pCommittedMemoryInBytes
    );

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkGetDeviceGroupPeerMemoryFeatures",
            "Acquire device group peer memory features",
            deviceHandle,
            heapIndex,
            localDeviceIndex,
            remoteDeviceIndex,
            pPeerMemoryFeatures
    );

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: GetMemoryPlatformIndependent,
            "vkGetDeviceMemoryOpaqueCaptureAddress",
            "Acquire device group opaque capture address",
            deviceHandle,
            pInfo,
            pResult
    );

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: CreateBuffer,
            "vkCreateBuffer",
            "Creates a Buffer Object",
            deviceHandle,
            pCreateInfo,
            pAllocationCallbacks,
            pHandle
    );

#endif

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkDestroyBuffer",
            "Destroys a Buffer Object",
            deviceHandle,
            bufferHandle,
            pAllocationCallbacks
    );

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: CreateBufferView,
            "vkCreateBufferView",
            "Creates a Buffer View Object",
            deviceHandle,
            pCreateInfo,
            pAllocationCallbacks,
            pHandle
    );

#endif

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkDestroyBufferView",
            "Destroys a Buffer View Object",
            deviceHandle,
            viewHandle,
            pAllocationCallbacks
    );

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: CreateImage,
            "vkCreateImage",
            "Creates an Image Object",
            deviceHandle,
            pCreateInfo,
            pAllocationCallbacks,
            pHandle
    );

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: GetImageSubresourceLayout,
            "vkGetImageSubresourceLayout",
            "Acquires an image's subresource layout",
            deviceHandle,
            imageHandle,
            pSubresource,
            pLayout
    );

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: GetImageDrmFormatModifierProperties,
            "vkGetImageDrmFormatModifierPropertiesEXT",
            "Acquires an image's drm format modifier properties",
            deviceHandle,
            imageHandle,
            pProperties
    );

#endif

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkDestroyImage",
            "Destroys an Image Object",
            deviceHandle,
            imageHandle,
            pAllocationCallbacks
    );

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

    auto context = ContextManager :: acquire();

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: CreateAccelerationStructureNVidia,
            "vkCreateAccelerationStructureNV",
            "Creates an acceleration structure",
            deviceHandle,
            pCreateInfo,
            pAllocationCallbacks,
            pHandle
    );

#endif

    return APICaller.vkCreateAccelerationStructureNV (
            deviceHandle,
            prepareContext ( & context->create.accelerationStructure.nvidia, pCreateInfo ),
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

    auto context = ContextManager :: acquire();

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: CreateAccelerationStructureKhronos,
            "vkCreateAccelerationStructureKHR",
            "Creates an acceleration structure",
            deviceHandle,
            pCreateInfo,
            pAllocationCallbacks,
            pHandle
    );

#endif

    return APICaller.vkCreateAccelerationStructureKHR (
            deviceHandle,
            prepareContext ( & context->create.accelerationStructure.khronos, pCreateInfo ),
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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: GetAccelerationStructureBuildSizes,
            "vkGetAccelerationStructureBuildSizesKHR",
            "Acquires an acceleration structure's build sizes",
            deviceHandle,
            buildType,
            pBuildInfo,
            pMaxPrimitiveCounts,
            pSizeInfo
    );

#endif

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkDestroyAccelerationStructureNV",
            "Destroys an acceleration structure",
            deviceHandle,
            accelerationStructureHandle,
            pAllocationCallbacks
    );

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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkDestroyAccelerationStructureKHR",
            "Destroys an acceleration structure",
            deviceHandle,
            accelerationStructureHandle,
            pAllocationCallbacks
    );

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: GetAccelerationStructureBuildSizes,
            "vkGetAccelerationStructureMemoryRequirementsNV",
            "Acquires an acceleration structure's memory requirements",
            deviceHandle,
            pInfo,
            pRequirements
    );

#endif

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

    auto context = ContextManager :: acquire();

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    auto arrayPack = DumpedArray {
        .pCount = & count,
        .type   = ParameterType :: Structure,
        .size   = sizeof ( Type ( BindAccelerationStructureMemoryInfoNVidia ) ),
        .pArray = pInfos
    };

    prepareDump (
            context.data(),
            SharedContextType :: BindAccelerationStructureMemory,
            "vkBindAccelerationStructureMemoryNV",
            "Binds an acceleration structure's memory",
            deviceHandle,
            count,
            arrayPack
    );

#endif

    return APICaller.vkBindAccelerationStructureMemoryNV (
            deviceHandle,
            count,
            prepareContext ( & context->bind.accelerationStructureMemory, count, & pInfos[0] )
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

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkGetAccelerationStructureHandleNV",
            "Gets an acceleration structure's Handle",
            deviceHandle,
            accelerationStructureHandle,
            dataSize,
            pData
    );

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

    auto context = ContextManager :: acquire();

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: GetAccelerationStructureDeviceAddress,
            "vkGetAccelerationStructureDeviceAddressKHR",
            "Acquires an acceleration structure's device address",
            deviceHandle,
            pInfo,
            pResult
    );

#endif

    return APICaller.vkGetAccelerationStructureDeviceAddressKHR (
            pResult,
            deviceHandle,
            toVulkanFormat ( & context->get.accelerationStructure.deviceAddress.info, pInfo )
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: createSampler (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( SamplerCreateInfo )      const * pCreateInfo,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks,
        Type ( SamplerHandle )                * pHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pCreateInfo == nullptr || pHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: CreateSampler,
            "vkCreateSampler",
            "Creates a Sampler Object",
            deviceHandle,
            pCreateInfo,
            pAllocationCallbacks,
            pHandle
    );

#endif

    return APICaller.vkCreateSampler (
            deviceHandle,
            prepareContext ( & context->create.sampler, pCreateInfo ),
            AllocatorHandler :: apply ( pAllocationCallbacks ),
            pHandle
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: destroySampler (
        Type ( DeviceHandle )                   deviceHandle,
        Type ( SamplerHandle )                  samplerHandle,
        Type ( AllocationCallbacks )    const * pAllocationCallbacks
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || samplerHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkDestroySampler",
            "Destroys a sampler",
            deviceHandle,
            samplerHandle,
            pAllocationCallbacks
    );

#endif

    return APICaller.vkDestroySampler (
            deviceHandle,
            samplerHandle,
            AllocatorHandler :: apply ( pAllocationCallbacks )
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto engine :: vulkan :: createSamplerYCBCRConversion (
        Type ( DeviceHandle )                               deviceHandle,
        Type ( SamplerYCBCRConversionCreateInfo )   const * pCreateInfo,
        Type ( AllocationCallbacks )                const * pAllocationCallbacks,
        Type ( SamplerYCBCRConversionHandle )             * pHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pCreateInfo == nullptr || pHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: CreateSampler,
            "vkCreateSamplerYcbcrConversion",
            "Creates a Sampler YCBCR Conversion Object",
            deviceHandle,
            pCreateInfo,
            pAllocationCallbacks,
            pHandle
    );

#endif

    return APICaller.vkCreateSamplerYcbcrConversion (
            deviceHandle,
            prepareContext ( & context->create.sampler, pCreateInfo ),
            AllocatorHandler :: apply ( pAllocationCallbacks ),
            pHandle
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto engine :: vulkan :: destroySamplerYCBCRConversion (
        Type ( DeviceHandle )                           deviceHandle,
        Type ( SamplerYCBCRConversionHandle )           samplerConversionHandle,
        Type ( AllocationCallbacks )            const * pAllocationCallbacks
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || samplerConversionHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

    auto context = ContextManager :: acquire();

    prepareDump (
            context.data(),
            "vkDestroySamplerYcbcrConversion",
            "Destroys a sampler YCBCR Conversion",
            deviceHandle,
            samplerConversionHandle,
            pAllocationCallbacks
    );

#endif

    return APICaller.vkDestroySamplerYcbcrConversion (
            deviceHandle,
            samplerConversionHandle,
            AllocatorHandler :: apply ( pAllocationCallbacks )
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: createDescriptorSetLayout (
        Type ( DeviceHandle )                               deviceHandle,
        Type ( DescriptorSetLayoutCreateInfo )      const * pCreateInfo,
        Type ( AllocationCallbacks )                const * pAllocationCallbacks,
        Type ( DescriptorSetLayoutHandle )                * pHandle
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pCreateInfo == nullptr || pHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: CreateDescriptorSetLayout,
            "vkCreateDescriptorSetLayout",
            "Creates a Descriptor Set Layout",
            deviceHandle,
            pCreateInfo,
            pAllocationCallbacks,
            pHandle
    );

#endif

    return APICaller.vkCreateDescriptorSetLayout (
            deviceHandle,
            prepareContext ( & context->create.descriptor.set.layout, pCreateInfo ),
            AllocatorHandler :: apply ( pAllocationCallbacks ),
            pHandle
    );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto engine :: vulkan :: getDescriptorSetLayoutSupport (
        Type ( DeviceHandle )                               deviceHandle,
        Type ( DescriptorSetLayoutCreateInfo )      const * pCreateInfo,
        Type ( DescriptorSetLayoutSupport )               * pSupport
) noexcept -> Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( deviceHandle == nullptr || pCreateInfo == nullptr || pSupport == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    auto context = ContextManager :: acquire();

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    prepareDump (
            context.data(),
            SharedContextType :: GetDescriptorSetLayoutSupport,
            "vkGetDescriptorSetLayoutSupport",
            "Checks the support of a given Descriptor Set Layout",
            deviceHandle,
            pCreateInfo,
            pSupport
    );

#endif

    if (
            auto result = APICaller.vkGetDescriptorSetLayoutSupport (
                    deviceHandle,
                    prepareContext ( & context->get.descriptor.set.layout.support, pCreateInfo ),
                    prepareContext ( & context->get.descriptor.set.layout.support, pSupport )
            ); result != ResultSuccess
    ) {
        return result;
    }

    extractContext ( pSupport, & context->get.descriptor.set.layout.support );
    return ResultSuccess;
}
#endif

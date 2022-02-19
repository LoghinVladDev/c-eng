//
// Created by loghin on 16.02.2022.
//

#include <VulkanAPI.hpp>
#include <VulkanAPICallsPrivate.hpp>
#include <VulkanAPICallsConversion.hpp>
#include <CDS/Mutex>
#include <CDS/LockGuard>

#define C_ENG_MAP_START     SOURCE
#include <ObjectMapping.hpp>

using namespace cds;
using namespace engine;
using namespace vulkan;

extern VkInstance lastCreatedInstance;


#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
class ContextManager {
private:
    struct Context {
    private:
        bool            inUse;
        friend class ContextManager;

    public:
        SharedContext   data;
    };

    static inline Context   contexts [ __C_ENG_VULKAN_CORE_CONTEXT_COUNT ];
    static inline Mutex     contextLock;
    static inline bool      firstCall = true;

    class ContextHolder {
    private:
        friend class ContextManager;
        Context * pContext { nullptr };

        explicit ContextHolder ( Context * pContext ) noexcept :
                pContext ( pContext ) {

        }

    public:
        ~ContextHolder () noexcept {
            LockGuard guard ( contextLock );
            this->pContext->inUse = false;
        }

        ContextHolder ( ContextHolder && holder ) noexcept :
                pContext ( cds :: exchange ( holder.pContext, nullptr ) ) {

        }

        inline auto operator = ( ContextHolder && holder ) noexcept -> ContextHolder & {
            if ( this == & holder ) {
                return * this;
            }

            this->pContext = cds :: exchange ( holder.pContext, nullptr );
            return * this;
        }

        constexpr auto data () noexcept -> SharedContext & {
            return this->pContext->data;
        }
    };

public:
    static auto acquire () noexcept -> ContextHolder {

        if ( firstCall ) {
            LockGuard guard ( contextLock );

            if ( firstCall ) {
                for ( auto & context : contexts ) {
                    context.inUse = false;
                }
            }

            firstCall = false;
        }

        while ( true ) {
            LockGuard guard ( contextLock );
            for ( auto & context : contexts ) {
                if ( ! context.inUse ) {
                    context.inUse = true;
                    return ContextHolder ( & context );
                }
            }
        }
    }
};
#endif


#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
class LastCreatedInstance {
private:
    static inline Type ( InstanceHandle ) instance;
    static inline Mutex lock;

public:
    static inline auto acquire () noexcept -> Type ( InstanceHandle ) {
        /* read lock might be irrelevant, guarding against incomplete pointers to instance
         * a null instance / a valid instance = OK */
        LockGuard guard ( lock );
        return instance;
    }

    static inline auto set ( Type ( InstanceHandle ) handle ) noexcept -> void {
        LockGuard guard ( lock );
        lastCreatedInstance = handle; // TODO : remove
        instance = handle;
    }
};

class AllocatorHandler {
private:
    static inline VkAllocationCallbacks                 callbacks {};
    static inline Type ( AllocationCallbacks )  const * pApplicationAllocationCallbacks { nullptr };
    static inline Mutex                                 lock;

public:
    static inline auto applyCallbacks (
            Type ( AllocationCallbacks ) const * pAllocationCallbacks
    ) noexcept -> VkAllocationCallbacks const * {
        if ( pAllocationCallbacks == nullptr ) {
            return nullptr;
        }

        if ( pApplicationAllocationCallbacks == pAllocationCallbacks ) {
            return & callbacks;
        }

        LockGuard guard ( lock );
        pApplicationAllocationCallbacks = pAllocationCallbacks;
        return toVulkanFormat ( & callbacks, pApplicationAllocationCallbacks );
    }
};
#endif


#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto engine :: vulkan :: enumerateInstanceVersion (
        uint32 * pVersion
) noexcept -> vulkan :: Type ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pVersion == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    __C_ENG_LOOKUP_VULKAN_FUNCTION_R ( vkEnumerateInstanceVersion )
    return static_cast < vulkan :: Type ( Result ) > (
            vkEnumerateInstanceVersionHandle (
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R (
            LastCreatedInstance :: acquire(),
            vkGetDeviceProcAddr
    )

    * pFunctionHandle = reinterpret_cast < void * > (
            vkGetDeviceProcAddrHandle (
                    deviceHandle,
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

    __C_ENG_LOOKUP_VULKAN_FUNCTION_R ( vkCreateInstance )

    auto context = ContextManager :: acquire();

    if (
            auto result = vkCreateInstanceHandle (
                    prepareContext ( & context.data().create.instance, pCreateInfo ),
                    AllocatorHandler :: applyCallbacks ( pAllocationCallbacks ),
                    pInstanceHandle
            ); result != VK_SUCCESS
    ) {
        return static_cast < Type ( Result ) > ( result );
    }

    LastCreatedInstance :: set ( * pInstanceHandle );
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

    __C_ENG_LOOKUP_VULKAN_FUNCTION_R ( vkEnumerateInstanceLayerProperties )

    if ( pProperties == nullptr ) {
        return static_cast < Type ( Result ) > (
                vkEnumerateInstanceLayerPropertiesHandle (
                        pCount,
                        nullptr
                )
        );
    }

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( * pCount > __C_ENG_VULKAN_CORE_LAYER_MAX_COUNT ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

    auto context = ContextManager :: acquire();

    if (
            auto result = vkEnumerateInstanceLayerPropertiesHandle (
                    pCount,
                    & context.data().enumerate.layerProperties.properties[0]
            ); result != VK_SUCCESS
    ) {
        return static_cast < Type ( Result ) > ( result );
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkEnumerateDeviceLayerProperties )

    if ( pProperties == nullptr ) {
        return static_cast < Type ( Result ) > (
                vkEnumerateDeviceLayerPropertiesHandle (
                        physicalDeviceHandle,
                        pCount,
                        nullptr
                )
        );
    }

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( * pCount > __C_ENG_VULKAN_CORE_LAYER_MAX_COUNT ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

    auto context = ContextManager :: acquire();

    if (
        auto result = vkEnumerateDeviceLayerPropertiesHandle (
                physicalDeviceHandle,
                pCount,
                & context.data().enumerate.layerProperties.properties[0]
        ); result != VK_SUCCESS
    ) {
        return static_cast < Type ( Result ) > ( result );
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkEnumerateInstanceExtensionProperties )

    if ( pProperties == nullptr ) {
        return static_cast < Type ( Result ) > (
                vkEnumerateInstanceExtensionPropertiesHandle (
                        layerName,
                        pCount,
                        nullptr
                )
        );
    }

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( * pCount > __C_ENG_VULKAN_CORE_LAYER_EXTENSION_MAX_COUNT ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

    auto context = ContextManager :: acquire();

    if (
        auto result = vkEnumerateInstanceExtensionPropertiesHandle (
                layerName,
                pCount,
                & context.data().enumerate.extensionProperties.properties[0]
        ); result != VK_SUCCESS
    ) {
        return static_cast < Type ( Result ) > ( result );
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( handle, vkEnumeratePhysicalDevices )

    if ( pDevices == nullptr ) {
        return static_cast < Type ( Result ) > (
                vkEnumeratePhysicalDevicesHandle (
                        handle,
                        pCount,
                        nullptr
                )
        );
    }

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( * pCount > __C_ENG_VULKAN_CORE_PHYSICAL_DEVICE_MAX_COUNT ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

    auto context = ContextManager :: acquire();

    if (
            auto result = vkEnumeratePhysicalDevicesHandle (
                    handle,
                    pCount,
                    & context.data().enumerate.physicalDevices.devices[0]
            ); result != VK_SUCCESS
    ) {
        return static_cast < Type ( Result ) > ( result );
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR )

    if ( pCounters == nullptr && pDescriptions == nullptr ) {
        return static_cast < Type ( Result ) > (
                vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHRHandle (
                        physicalDeviceHandle,
                        queueFamilyIndex,
                        pCount,
                        nullptr,
                        nullptr
                )
        );
    }

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( * pCount > __C_ENG_VULKAN_CORE_QUEUE_FAMILY_PERFORMANCE_COUNTER_MAX_COUNT ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

    auto context = ContextManager :: acquire();

    if (
            auto result = vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHRHandle (
                    physicalDeviceHandle,
                    queueFamilyIndex,
                    pCount,
                    & context.data().enumerate.physicalDeviceQueueFamilyPerformanceQueryCounters.counters[0],
                    & context.data().enumerate.physicalDeviceQueueFamilyPerformanceQueryCounters.descriptions[0]
            ); result != VK_SUCCESS
    ) {
        return static_cast < Type ( Result ) > ( result );
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkEnumeratePhysicalDeviceGroups )

    if ( pProperties == nullptr ) {
        return static_cast < Type ( Result ) > (
                vkEnumeratePhysicalDeviceGroupsHandle (
                        instanceHandle,
                        pCount,
                        nullptr
                )
        );
    }

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( * pCount > __C_ENG_VULKAN_CORE_PHYSICAL_DEVICE_GROUP_MAX_COUNT ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

    auto context = ContextManager :: acquire();

    if (
            auto result = vkEnumeratePhysicalDeviceGroupsHandle (
                    instanceHandle,
                    pCount,
                    & context.data().enumerate.physicalDeviceGroups.properties [0]
            ); result != VK_SUCCESS
    ) {
        return static_cast < Type ( Result ) > ( result );
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkEnumerateDeviceExtensionProperties )

    if ( pProperties == nullptr ) {
        return static_cast < Type ( Result ) > (
                vkEnumerateDeviceExtensionPropertiesHandle (
                        handle,
                        layerName,
                        pCount,
                        nullptr
                )
        );
    }

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( * pCount > __C_ENG_VULKAN_CORE_LAYER_EXTENSION_MAX_COUNT ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

    auto context = ContextManager :: acquire();

    if (
            auto result = vkEnumerateDeviceExtensionPropertiesHandle (
                    handle,
                    layerName,
                    pCount,
                    & context.data().enumerate.extensionProperties.properties[0]
            ); result != VK_SUCCESS
    ) {
        return static_cast < Type ( Result ) > ( result );
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( instanceHandle, vkCreateDebugUtilsMessengerEXT )

    auto context = ContextManager :: acquire();

    return static_cast < Type ( Result ) > (
            vkCreateDebugUtilsMessengerEXTHandle (
                    instanceHandle,
                    toVulkanFormat ( & context.data().create.instance.debugMessenger, pCreateInfo ),
                    AllocatorHandler :: applyCallbacks ( pAllocationCallbacks ),
                    pHandle
            )
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
                    AllocatorHandler :: applyCallbacks ( pAllocationCallbacks ),
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkCreateDevice )

    auto context = ContextManager :: acquire();

    return static_cast < Type ( Result ) > (
            vkCreateDeviceHandle (
                    physicalDeviceHandle,
                    prepareContext ( & context.data().create.device, pCreateInfo ),
                    AllocatorHandler :: applyCallbacks ( pAllocationCallbacks ),
                    pDeviceHandle
            )
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( handle, vkDestroyInstance )

    vkDestroyInstanceHandle ( handle, AllocatorHandler :: applyCallbacks ( pAllocationCallbacks ) );
    return ResultSuccess;
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( instanceHandle, vkDestroyDebugUtilsMessengerEXT )

    vkDestroyDebugUtilsMessengerEXTHandle (
            instanceHandle,
            debugMessengerHandle,
            AllocatorHandler :: applyCallbacks ( pAllocationCallbacks )
    );

    return ResultSuccess;
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( instanceHandle, vkDestroySurfaceKHR )

    vkDestroySurfaceKHRHandle (
            instanceHandle,
            surfaceHandle,
            AllocatorHandler :: applyCallbacks ( pAllocationCallbacks )
    );

    return ResultSuccess;
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkDestroyDevice )

    vkDestroyDeviceHandle ( handle, AllocatorHandler :: applyCallbacks ( pAllocationCallbacks ) );
    return ResultSuccess;
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkGetPhysicalDeviceProperties )

    auto context = ContextManager :: acquire();

    vkGetPhysicalDevicePropertiesHandle (
            handle,
            & context.data().get.physicalDeviceProperties.properties.properties
    );

    (void) fromVulkanFormat (
            pProperties,
            & context.data().get.physicalDeviceProperties.properties.properties
    );

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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkGetPhysicalDeviceProperties )
    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkGetPhysicalDeviceProperties2 )

    auto context = ContextManager :: acquire();

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    vkGetPhysicalDevicePropertiesHandle (
            handle,
            & context.data().get.physicalDeviceProperties.properties.properties
    );

    if (
            auto version = uInt32ToInstanceVersion ( context.data().get.physicalDeviceProperties.properties.properties.apiVersion );
            vulkan :: compare ( version, versionConstants :: version11 ) == CompareResultLess
    ) {
        return ResultErrorIncompatibleVersion;
    }

#endif

    vkGetPhysicalDeviceProperties2Handle (
            handle,
            prepareContext ( & context.data().get.physicalDeviceProperties, pProperties )
    );

    extractContext ( pProperties, & context.data().get.physicalDeviceProperties );
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkGetPhysicalDeviceFeatures )

    auto context = ContextManager :: acquire();

    vkGetPhysicalDeviceFeaturesHandle (
            physicalDeviceHandle,
            & context.data().get.physicalDeviceFeatures.features.features
    );

    (void) fromVulkanFormat ( pFeatures, & context.data().get.physicalDeviceFeatures.features.features );
    return ResultSuccess;
}
#endif

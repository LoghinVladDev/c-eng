//
// Created by loghin on 16.02.2022.
//

#include <VulkanAPI.hpp>
#include <VulkanAPICallsPrivate.hpp>
#include <VulkanAPICallsConversion.hpp>
#include <VulkanAPICallsTypes.hpp>
#include <CDS/Mutex>
#include <CDS/LockGuard>
#include <Logger.hpp>

#define C_ENG_MAP_START     SOURCE
#include <ObjectMapping.hpp>

using namespace cds;
using namespace engine;
using namespace vulkan;


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

    static inline Context   contexts [ engine :: vulkan :: config :: contextCount ];
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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED
            if ( this->pContext->data.common.diag.error != ResultSuccess ) {
                Type ( Logger ) :: instance().error ( String::f (
                    "API Error logged in context at release : %s, in %s -> %s : %d ---> %s",
                    toString ( pContext->data.common.diag.error ),
                    pContext->data.common.diag.file,
                    pContext->data.common.diag.function,
                    pContext->data.common.diag.line,
                    pContext->data.common.diag.pMessage == nullptr ? "no details given" : pContext->data.common.diag.pMessage->cStr()
                ));

                cds :: Memory :: instance().destroy ( pContext->data.common.diag.pMessage );

                this->pContext->data.common.diag.error = ResultSuccess;
            }
#endif

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

        constexpr auto operator -> () noexcept -> SharedContext * {
            return & this->pContext->data;
        }
    };

public:
    static auto acquire () noexcept -> ContextHolder {

        if ( firstCall ) {
            LockGuard guard ( contextLock );

            if ( firstCall ) {
                for ( auto & context : contexts ) {
                    context.inUse = false;

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED
                    context.data.common.diag.error = ResultSuccess;
#endif

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
        instance = handle;
    }
};

class AllocatorHandler {
private:
    static inline VkAllocationCallbacks                 callbacks {};
    static inline Type ( AllocationCallbacks )  const * pApplicationAllocationCallbacks { nullptr };
    static inline Mutex                                 lock;

public:
    static inline auto apply (
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
                    AllocatorHandler :: apply ( pAllocationCallbacks ),
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

    if ( * pCount > engine :: vulkan :: config :: layerCount ) {
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

    if ( * pCount > engine :: vulkan :: config :: layerCount ) {
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

    if ( * pCount > engine :: vulkan :: config :: layerExtensionCount ) {
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

    if ( * pCount > engine :: vulkan :: config :: physicalDeviceCount ) {
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

    if ( * pCount > engine :: vulkan :: config :: queueFamilyPerformanceCounterCount ) {
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

    if ( * pCount > engine :: vulkan :: config :: physicalDeviceGroupCount ) {
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

    if ( * pCount > engine :: vulkan :: config :: layerExtensionCount ) {
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
                    AllocatorHandler :: apply ( pAllocationCallbacks ),
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkCreateDevice )

    auto context = ContextManager :: acquire();

    return static_cast < Type ( Result ) > (
            vkCreateDeviceHandle (
                    physicalDeviceHandle,
                    prepareContext ( & context.data().create.device, pCreateInfo ),
                    AllocatorHandler :: apply ( pAllocationCallbacks ),
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

    vkDestroyInstanceHandle ( handle, AllocatorHandler :: apply ( pAllocationCallbacks ) );
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
            AllocatorHandler :: apply ( pAllocationCallbacks )
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
            AllocatorHandler :: apply ( pAllocationCallbacks )
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

    vkDestroyDeviceHandle ( handle, AllocatorHandler :: apply ( pAllocationCallbacks ) );
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkGetPhysicalDeviceProperties )
    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkGetPhysicalDeviceFeatures2 )

    auto context = ContextManager :: acquire();

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    vkGetPhysicalDevicePropertiesHandle (
            physicalDeviceHandle,
            & context.data().get.physicalDeviceProperties.properties.properties
    );

    if (
        auto version = uInt32ToInstanceVersion ( context.data().get.physicalDeviceProperties.properties.properties.apiVersion );
            vulkan :: compare ( version, versionConstants :: version11 ) == CompareResultLess
    ) {
        return ResultErrorIncompatibleVersion;
    }

#endif

    vkGetPhysicalDeviceFeatures2Handle (
            physicalDeviceHandle,
            prepareContext ( & context.data().get.physicalDeviceFeatures, pFeatures )
    );

    extractContext ( pFeatures, & context.data().get.physicalDeviceFeatures );
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkGetPhysicalDeviceQueueFamilyProperties )

    if ( pProperties == nullptr ) {
        vkGetPhysicalDeviceQueueFamilyPropertiesHandle (
                physicalDeviceHandle,
                pCount,
                nullptr
        );

        return ResultSuccess;
    }

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( * pCount > engine :: vulkan :: config :: queueFamilyCount ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

    auto context = ContextManager :: acquire();

    vkGetPhysicalDeviceQueueFamilyPropertiesHandle (
            physicalDeviceHandle,
            pCount,
            & context.data().get.physicalDeviceQueueFamilyProperties.properties[0]
    );

    for ( uint32 i = 0U; i < * pCount; ++ i ) {
        (void) fromVulkanFormat ( & pProperties[i], & context.data().get.physicalDeviceQueueFamilyProperties.properties[i] );
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkGetPhysicalDeviceQueueFamilyProperties2 )

    if ( pProperties == nullptr ) {
        vkGetPhysicalDeviceQueueFamilyProperties2Handle (
                physicalDeviceHandle,
                pCount,
                nullptr
        );

        return ResultSuccess;
    }

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( * pCount > engine :: vulkan :: config :: queueFamilyCount ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

    auto context = ContextManager :: acquire();

    vkGetPhysicalDeviceQueueFamilyProperties2Handle (
            physicalDeviceHandle,
            pCount,
            prepareContext ( & context.data().get.physicalDeviceQueueFamilyProperties, * pCount, pProperties )
    );

    extractContext (
            * pCount,
            & pProperties[0],
            & context.data().get.physicalDeviceQueueFamilyProperties
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkGetPhysicalDeviceQueueFamilyProperties2 )

    if ( pDetails == nullptr ) {
        vkGetPhysicalDeviceQueueFamilyProperties2Handle (
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkGetPhysicalDeviceSurfaceSupportKHR )

    Type ( Bool ) support = VK_FALSE;

    if (
            auto result = vkGetPhysicalDeviceSurfaceSupportKHRHandle (
                    deviceHandle,
                    queueFamilyIndex,
                    surfaceHandle,
                    & support
            ); result != VK_SUCCESS
    ) {
        return static_cast < Type ( Result ) > ( result );
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkGetDeviceQueue )

    vkGetDeviceQueueHandle (
            deviceHandle,
            queueFamilyIndex,
            queueIndex,
            pQueueHandle
    );

    return ResultSuccess;
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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkGetDeviceQueue2 )

    auto context = ContextManager :: acquire();

    vkGetDeviceQueue2Handle (
            deviceHandle,
            toVulkanFormat ( & context.data().get.deviceQueue.info2, pQueueInfo ),
            pQueueHandle
    );

    return ResultSuccess;
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkGetPhysicalDeviceSurfaceCapabilitiesKHR )

    auto context = ContextManager :: acquire();

    if (
            auto result = vkGetPhysicalDeviceSurfaceCapabilitiesKHRHandle (
                    deviceHandle,
                    surfaceHandle,
                    & context.data().get.surface.capabilities
            ); result != VK_SUCCESS
    ) {
        return static_cast < Type ( Result ) > ( result );
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkGetPhysicalDeviceSurfaceFormatsKHR )

    if ( pFormats == nullptr ) {
        return static_cast < Type ( Result ) > (
                vkGetPhysicalDeviceSurfaceFormatsKHRHandle (
                        deviceHandle,
                        surfaceHandle,
                        pCount,
                        nullptr
                )
        );
    }

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( * pCount > engine :: vulkan :: config :: surfaceFormatCount ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

    auto context = ContextManager :: acquire();

    if (
            auto result = vkGetPhysicalDeviceSurfaceFormatsKHRHandle (
                    deviceHandle,
                    surfaceHandle,
                    pCount,
                    & context.data().get.surface.formats[0]
            ); result != VK_SUCCESS
    ) {
        return static_cast < Type ( Result ) > ( result );
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkGetPhysicalDeviceSurfacePresentModesKHR )

    if ( pPresentModes == nullptr ) {
        return static_cast < Type ( Result ) > (
                vkGetPhysicalDeviceSurfacePresentModesKHRHandle (
                        deviceHandle,
                        surfaceHandle,
                        pCount,
                        nullptr
                )
        );
    }

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( * pCount > engine :: vulkan :: config :: surfacePresentModeCount ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

    auto context = ContextManager :: acquire();

    if (
            auto result = vkGetPhysicalDeviceSurfacePresentModesKHRHandle (
                    deviceHandle,
                    surfaceHandle,
                    pCount,
                    & context.data().get.surface.presentModes[0]
            ); result != VK_SUCCESS
    ) {
        return static_cast < Type ( Result ) > ( result );
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkGetPhysicalDeviceSurfaceCapabilities2EXT )

    auto context = ContextManager :: acquire();

    if (
            auto result = vkGetPhysicalDeviceSurfaceCapabilities2EXTHandle (
                    deviceHandle,
                    surfaceHandle,
                    & context.data().get.surface.capabilities2
            ); result != VK_SUCCESS
    ) {
        return static_cast < Type ( Result ) > ( result );
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkGetPhysicalDeviceSurfaceFormats2KHR )

    auto context = ContextManager :: acquire();

    if ( pFormats == nullptr ) {
        return static_cast < Type ( Result ) > (
                vkGetPhysicalDeviceSurfaceFormats2KHRHandle (
                        deviceHandle,
                        prepareContext ( & context.data().get.surface, pSurfaceInfo ),
                        pCount,
                        nullptr
                )
        );
    }

    if ( * pCount > engine :: vulkan :: config :: surfaceFormatCount ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

    if (
            auto result = vkGetPhysicalDeviceSurfaceFormats2KHRHandle (
                    deviceHandle,
                    prepareContext ( & context.data().get.surface, pSurfaceInfo ),
                    pCount,
                    & context.data().get.surface.formats2[0]
            ); result != VK_SUCCESS
    ) {
        return static_cast < Type ( Result ) > ( result );
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkGetPhysicalDeviceSurfacePresentModes2EXT )

    auto context = ContextManager :: acquire();

    if ( pPresentModes == nullptr ) {
        return static_cast < Type ( Result ) > (
                vkGetPhysicalDeviceSurfacePresentModes2EXTHandle (
                        deviceHandle,
                        prepareContext ( & context.data().get.surface.surfaceInfo2, pSurfaceInfo ),
                        pCount,
                        nullptr
                )
        );
    }

    if ( * pCount > __C_ENG_VULKAN_CORE_SURFACE_PRESENT_MODE_MAX_COUNT ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

    if (
            auto result = vkGetPhysicalDeviceSurfacePresentModes2EXTHandle (
                    deviceHandle,
                    prepareContext ( & context.data().get.surface.surfaceInfo2, pSurfaceInfo ),
                    pCount,
                    & context.data().get.surface.presentModes[0]
            ); result != VK_SUCCESS
    ) {
        return static_cast < Type ( Result ) > ( result );
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkCreateSwapchainKHR )

    auto context = ContextManager :: acquire();

    return static_cast < Type ( Result ) > (
            vkCreateSwapchainKHRHandle (
                    deviceHandle,
                    prepareContext ( & context.data().create.swapChain, pCreateInfo ),
                    AllocatorHandler :: apply ( pAllocationCallbacks ),
                    pHandle
            )
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkDestroySwapchainKHR )

    vkDestroySwapchainKHRHandle (
            deviceHandle,
            handle,
            AllocatorHandler :: apply ( pAllocationCallbacks )
    );

    return ResultSuccess;
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkGetSwapchainImagesKHR )

    if ( pImageHandles == nullptr ) {
        return static_cast < Type ( Result ) > (
                vkGetSwapchainImagesKHRHandle (
                        deviceHandle,
                        swapChainHandle,
                        pCount,
                        nullptr
                )
        );
    }

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( * pCount > engine :: vulkan :: config :: swapChainImageCount ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

    auto context = ContextManager :: acquire();

    if (
            auto result = vkGetSwapchainImagesKHRHandle (
                    deviceHandle,
                    swapChainHandle,
                    pCount,
                    & context.data().get.swapChain.images[0]
            ); result != VK_SUCCESS
    ) {
        return static_cast < Type ( Result ) > ( result );
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkCreateImageView )

    auto context = ContextManager :: acquire();

    return static_cast < Type ( Result ) > (
            vkCreateImageViewHandle (
                    deviceHandle,
                    prepareContext ( & context.data().create.imageView, pCreateInfo ),
                    AllocatorHandler :: apply ( pAllocationCallbacks ),
                    pHandle
            )
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkDestroyImageView )

    vkDestroyImageViewHandle (
            deviceHandle,
            handle,
            AllocatorHandler :: apply ( pAllocationCallbacks )
    );

    return ResultSuccess;
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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkCreateCommandPool )

    auto context = ContextManager :: acquire();

    return static_cast < Type ( Result ) > (
            vkCreateCommandPoolHandle (
                    deviceHandle,
                    toVulkanFormat ( & context.data().create.commandPool.createInfo, pCreateInfo ),
                    AllocatorHandler :: apply ( pAllocationCallbacks ),
                    pHandle
            )
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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkDestroyCommandPool )

    vkDestroyCommandPoolHandle (
            deviceHandle,
            handle,
            AllocatorHandler :: apply ( pAllocationCallbacks )
    );

    return ResultSuccess;
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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkResetCommandPool )

    return static_cast < Type ( Result ) > (
            vkResetCommandPoolHandle (
                    deviceHandle,
                    handle,
                    flags
            )
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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkAllocateCommandBuffers )

    auto context = ContextManager :: acquire();

    return static_cast < Type ( Result ) > (
            vkAllocateCommandBuffersHandle (
                    deviceHandle,
                    toVulkanFormat ( & context.data().allocate.commandBuffers.allocateInfo, pAllocateInfo ),
                    & pHandles [0]
            )
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkResetCommandBuffer )

    auto context = ContextManager :: acquire();

    return static_cast < Type ( Result ) > (
            vkResetCommandBufferHandle (
                    handle,
                    flags
            )
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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkFreeCommandBuffers )

    vkFreeCommandBuffersHandle (
            deviceHandle,
            commandPoolHandle,
            commandBufferCount,
            pCommandBuffers
    );

    return ResultSuccess;
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkBeginCommandBuffer )

    auto context = ContextManager :: acquire();

    return static_cast < Type ( Result ) > (
            vkBeginCommandBufferHandle (
                    commandBufferHandle,
                    prepareContext ( & context.data().begin.commandBuffer, pBeginInfo )
            )
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkEndCommandBuffer )

    return static_cast < Type ( Result ) > ( vkEndCommandBufferHandle ( commandBufferHandle ) );
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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkTrimCommandPool )

    vkTrimCommandPoolHandle (
            deviceHandle,
            handle,
            flags
    );

    return ResultSuccess;
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkQueueSubmit )

    auto context = ContextManager :: acquire();

    return static_cast < Type ( Result ) > (
            vkQueueSubmitHandle (
                    queueHandle,
                    submitCount,
                    prepareContext ( & context.data().submit.queue, submitCount, & pSubmits[0] ),
                    fenceHandle
            )
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkCmdExecuteCommands )

    vkCmdExecuteCommandsHandle (
            primaryCommandBufferHandle,
            commandBufferCount,
            pSecondaryCommandBufferHandles
    );

    return ResultSuccess;
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

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_2_R ( LastCreatedInstance :: acquire(), vkQueueSubmit2, KHR )

    auto context = ContextManager :: acquire();

    if ( vkQueueSubmit2Handle != nullptr ) {
        return static_cast < Type ( Result ) > (
                vkQueueSubmit2Handle (
                        queueHandle,
                        submitCount,
                        prepareContext ( & context.data().submit.queue, submitCount, & pSubmits [0] ),
                        fenceHandle
                )
        );
    }

    return static_cast < Type ( Result ) > (
            vkQueueSubmit2KHRHandle (
                    queueHandle,
                    submitCount,
                    reinterpret_cast < VkSubmitInfo2KHR * > ( prepareContext ( & context.data().submit.queue, submitCount, & pSubmits [0] ) ),
                    fenceHandle
            )
    );

#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkQueueSubmit2 )

    auto context = ContextManager :: acquire();

    return static_cast < Type ( Result ) > (
                vkQueueSubmit2Handle (
                        queueHandle,
                        submitCount,
                        prepareContext ( & context.data().submit.queue, submitCount, & pSubmits [0] ),
                        fenceHandle
                )
        );

#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkQueueSubmit2KHR )

    auto context = ContextManager :: acquire();

    return static_cast < Type ( Result ) > (
                vkQueueSubmit2HandleKHR (
                        queueHandle,
                        submitCount,
                        prepareContext ( & context.data().submit.queue, submitCount, & pSubmits [0] ),
                        fenceHandle
                )
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkCmdSetDeviceMask )

    vkCmdSetDeviceMaskHandle ( commandBufferHandle, deviceMask );
    return ResultSuccess;
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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkCreateFence )

    auto context = ContextManager :: acquire();

    return static_cast < Type ( Result ) > (
            vkCreateFenceHandle (
                    deviceHandle,
                    prepareContext ( & context.data().create.fence, pCreateInfo ),
                    AllocatorHandler :: apply ( pAllocationCallbacks ),
                    pHandle
            )
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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkGetFenceWin32HandleKHR )

    auto context = ContextManager :: acquire ();

    return static_cast < Type ( Result ) > (
            vkGetFenceWin32HandleKHRHandle (
                    deviceHandle,
                    toVulkanFormat ( & context.data().get.fence.win32HandleInfo, pInfo ),
                    pHandle
            )
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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkGetFenceFdKHR )

    auto context = ContextManager :: acquire ();

    return static_cast < Type ( Result ) > (
            vkGetFenceFdKHRHandle (
                    deviceHandle,
                    toVulkanFormat ( & context.data().get.fence.fdInfo, pInfo ),
                    pHandle
            )
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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkDestroyFence )

    vkDestroyFenceHandle (
            deviceHandle,
            fenceHandle,
            AllocatorHandler :: apply ( pAllocationCallbacks )
    );

    return ResultSuccess;
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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkGetFenceStatus )

    return static_cast < Type ( Result ) > ( vkGetFenceStatusHandle ( deviceHandle, fenceHandle ) );
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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkResetFences )

    return static_cast < Type ( Result ) > (
            vkResetFencesHandle (
                    deviceHandle,
                    count,
                    pFences
            )
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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkWaitForFences )

    return static_cast < Type ( Result ) > (
            vkWaitForFencesHandle (
                    deviceHandle,
                    count,
                    pFences,
                    waitForAll ? VK_TRUE : VK_FALSE,
                    timeout
            )
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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkRegisterDeviceEventEXT )

    auto context = ContextManager :: acquire();

    return static_cast < Type ( Result ) > (
            vkRegisterDeviceEventEXTHandle (
                    deviceHandle,
                    toVulkanFormat ( & context.data().other.registerEvent.deviceInfo, pEventInfo ),
                    AllocatorHandler :: apply ( pAllocationCallbacks ),
                    pHandle
            )
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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkRegisterDisplayEventEXT )

    auto context = ContextManager :: acquire();

    return static_cast < Type ( Result ) > (
            vkRegisterDisplayEventEXTHandle (
                    deviceHandle,
                    displayHandle,
                    toVulkanFormat ( & context.data().other.registerEvent.displayInfo, pEventInfo ),
                    AllocatorHandler :: apply ( pAllocationCallbacks ),
                    pHandle
            )
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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkImportFenceWin32HandleKHR )

    auto context = ContextManager :: acquire();

    return static_cast < Type ( Result ) > (
            vkImportFenceWin32HandleKHRHandle (
                    deviceHandle,
                    toVulkanFormat ( & context.data()._import.fence.win32.info, pInfo )
            )
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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkImportFenceFdKHR )

    auto context = ContextManager :: acquire();

    return static_cast < Type ( Result ) > (
            vkImportFenceFdKHRHandle (
                    deviceHandle,
                    toVulkanFormat ( & context.data()._import.fence.fd.info, pInfo )
            )
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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkCreateSemaphore )

    auto context = ContextManager :: acquire();

    return static_cast < Type ( Result ) > (
            vkCreateSemaphoreHandle (
                    deviceHandle,
                    prepareContext ( & context.data().create.semaphore, pCreateInfo ),
                    AllocatorHandler :: apply ( pAllocationCallbacks ),
                    pHandle
            )
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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkGetSemaphoreWin32HandleKHR )

    auto context = ContextManager :: acquire();

    return static_cast < Type ( Result ) > (
            vkGetSemaphoreWin32HandleKHRHandle (
                    deviceHandle,
                    toVulkanFormat ( & context.data().get.semaphore.win32HandleInfo, pInfo ),
                    pHandle
            )
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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkGetSemaphoreFdKHR )

    auto context = ContextManager :: acquire();

    return static_cast < Type ( Result ) > (
            vkGetSemaphoreFdKHRHandle (
                    deviceHandle,
                    toVulkanFormat ( & context.data().get.semaphore.fdInfo, pInfo ),
                    pFd
            )
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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkGetSemaphoreZirconHandleFUCHSIA )

    auto context = ContextManager :: acquire();

    return static_cast < Type ( Result ) > (
            vkGetSemaphoreZirconHandleFUCHSIAHandle (
                    deviceHandle,
                    toVulkanFormat ( & context.data().get.semaphore.zirconHandleInfo, pInfo ),
                    pHandle
            )
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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkDestroySemaphore )

    vkDestroySemaphoreHandle (
            deviceHandle,
            semaphoreHandle,
            AllocatorHandler :: apply ( pAllocationCallbacks )
    );

    return ResultSuccess;
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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkGetSemaphoreCounterValue )

    uint64_t value = 0U;

    if (
            auto result = vkGetSemaphoreCounterValueHandle (
                    deviceHandle,
                    semaphoreHandle,
                    & value
            ); result != VK_SUCCESS
    ) {
        return static_cast < Type ( Result ) > ( result );
    }

    * pValue = static_cast < uint64 > ( value );

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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkWaitSemaphores )

    auto context = ContextManager :: acquire();

    return static_cast < Type ( Result ) > (
            vkWaitSemaphoresHandle (
                    deviceHandle,
                    prepareContext ( & context.data().wait.semaphore, pWaitInfo ),
                    static_cast < uint64_t > ( timeout )
            )
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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkSignalSemaphore )

    auto context = ContextManager :: acquire();

    return static_cast < Type ( Result ) > (
            vkSignalSemaphoreHandle (
                    deviceHandle,
                    toVulkanFormat ( & context.data().signal.semaphore.info, pSignalInfo )
            )
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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkImportSemaphoreWin32HandleKHR )

    auto context = ContextManager :: acquire();

    return static_cast < Type ( Result ) > (
            vkImportSemaphoreWin32HandleKHRHandle (
                    deviceHandle,
                    toVulkanFormat ( & context.data()._import.semaphore.win32.info, pInfo )
            )
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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkImportSemaphoreFdKHR )

    auto context = ContextManager :: acquire();

    return static_cast < Type ( Result ) > (
            vkImportSemaphoreFdKHRHandle (
                    deviceHandle,
                    toVulkanFormat ( & context.data()._import.semaphore.fd.info, pInfo )
            )
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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkImportSemaphoreZirconHandleFUCHSIA )

    auto context = ContextManager :: acquire();

    return static_cast < Type ( Result ) > (
            vkImportSemaphoreZirconHandleFUCHSIAHandle (
                    deviceHandle,
                    toVulkanFormat ( & context.data()._import.semaphore.zircon.info, pInfo )
            )
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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkCreateEvent )

    auto context = ContextManager :: acquire();

    return static_cast < Type ( Result ) > (
            vkCreateEventHandle (
                    deviceHandle,
                    toVulkanFormat ( & context.data().create.event.createInfo, pCreateInfo ),
                    AllocatorHandler :: apply ( pAllocationCallbacks ),
                    pHandle
            )
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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkDestroyEvent )

    vkDestroyEventHandle (
            deviceHandle,
            handle,
            AllocatorHandler :: apply ( pAllocationCallbacks )
    );

    return ResultSuccess;
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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkGetEventStatus )

    return static_cast < Type ( Result ) > (
            vkGetEventStatusHandle (
                    deviceHandle,
                    handle
            )
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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkSetEvent )

    return static_cast < Type ( Result ) > (
            vkSetEventHandle (
                    deviceHandle,
                    handle
            )
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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkResetEvent )

    return static_cast < Type ( Result ) > (
            vkResetEventHandle (
                    deviceHandle,
                    handle
            )
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

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_2_R ( LastCreatedInstance :: acquire(), vkCmdSetEvent2, KHR )

    auto context = ContextManager :: acquire();

    if ( vkCmdSetEvent2Handle != nullptr ) {
        vkCmdSetEvent2Handle (
                commandBufferHandle,
                eventHandle,
                prepareContext ( & context.data().set.commandBuffer.event, pDependencyInfo )
        );

        return ResultSuccess;
    }

    vkCmdSetEvent2KHRHandle (
            commandBufferHandle,
            eventHandle,
            prepareContext ( & context.data().set.commandBuffer.event, pDependencyInfo )
    );

    return ResultSuccess;

#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkCmdSetEvent2 )

    auto context = ContextManager :: acquire();

    vkCmdSetEvent2Handle (
            commandBufferHandle,
            eventHandle,
            prepareContext ( & context.data().set.commandBuffer.event, pDependencyInfo )
    );

    return ResultSuccess;

#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkCmdSetEvent2KHR )

    auto context = ContextManager :: acquire();

    vkCmdSetEvent2KHRHandle (
            commandBufferHandle,
            eventHandle,
            prepareContext ( & context.data().set.commandBuffer.event, pDependencyInfo )
    );

    return ResultSuccess;

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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkCmdSetEvent )

    vkCmdSetEventHandle (
            commandBufferHandle,
            eventHandle,
            flags
    );

    return ResultSuccess;
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

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_2_R ( LastCreatedInstance :: acquire(), vkCmdResetEvent2, KHR )

    if ( vkCmdResetEvent2Handle != nullptr ) {
        vkCmdResetEvent2Handle (
                commandBufferHandle,
                eventHandle,
                flags
        );

        return ResultSuccess;
    }

    vkCmdResetEvent2KHRHandle (
            commandBufferHandle,
            eventHandle,
            flags
    );

    return ResultSuccess;

#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkCmdResetEvent2 )

    vkCmdResetEvent2Handle (
            commandBufferHandle,
            eventHandle,
            flags
    );

    return ResultSuccess;

#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkCmdResetEvent2KHR )

    vkCmdResetEvent2KHRHandle (
            commandBufferHandle,
            eventHandle,
            flags
    );

    return ResultSuccess;

#else

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkCmdResetEvent )

    vkCmdResetEventHandle (
            commandBufferHandle,
            eventHandle,
            flags
    );

    return ResultSuccess;

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

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_2_R ( LastCreatedInstance :: acquire(), vkCmdWaitEvents2, KHR )

    auto context = ContextManager :: acquire();

    if ( vkCmdWaitEvents2Handle != nullptr ) {
        vkCmdWaitEvents2Handle (
                commandBufferHandle,
                eventCount,
                pEventHandles,
                prepareContext ( & context.data().wait.commandBuffer.event2, eventCount, pDependencyInfos )
        );

        return ResultSuccess;
    }

    vkCmdWaitEvents2KHRHandle (
            commandBufferHandle,
            eventCount,
            pEventHandles,
            prepareContext ( & context.data().wait.commandBuffer.event2, eventCount, pDependencyInfos )
    );

    return ResultSuccess;

#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkCmdWaitEvents2 )

    auto context = ContextManager :: acquire();

    if ( vkCmdWaitEvents2Handle != nullptr ) {
        vkCmdWaitEvents2Handle (
                commandBufferHandle,
                eventCount,
                pEventHandles,
                prepareContext ( & context.data().wait.commandBuffer.event2, eventCount, pDependencyInfos )
        );

        return ResultSuccess;
    }

    return ResultSuccess;

#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkCmdWaitEvents2KHR )

    auto context = ContextManager :: acquire();

    vkCmdWaitEvents2KHRHandle (
            commandBufferHandle,
            eventCount,
            pEventHandles,
            prepareContext ( & context.data().wait.commandBuffer.event2, eventCount, pDependencyInfos )
    );

    return ResultSuccess;

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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkCmdWaitEvents )

    auto context = ContextManager :: acquire();

    vkCmdWaitEventsHandle (
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

    return ResultSuccess;
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkQueueWaitIdle )

    return static_cast < Type ( Result ) > ( vkQueueWaitIdleHandle ( handle ) );
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkDeviceWaitIdle )

    return static_cast < Type ( Result ) > ( vkDeviceWaitIdleHandle ( handle ) );
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

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_2_R ( LastCreatedInstance :: acquire(), vkCmdBeginRendering, KHR )

    auto context = ContextManager :: acquire();

    if ( vkCmdBeginRenderingHandle != nullptr ) {
        vkCmdBeginRenderingHandle (
                handle,
                prepareContext ( & context.data().begin.commandBufferRendering, pRenderingInfo )
        );

        return ResultSuccess;
    }

    vkCmdBeginRenderingKHRHandle (
            handle,
            prepareContext ( & context.data().begin.commandBufferRendering, pRenderingInfo )
    );

    return ResultSuccess;

#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkCmdBeginRendering )

    auto context = ContextManager :: acquire();

    vkCmdBeginRenderingHandle (
                handle,
                prepareContext ( & context.data().begin.commandBufferRendering, pRenderingInfo )
    );

    return ResultSuccess;

#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkCmdBeginRenderingKHR )

    auto context = ContextManager :: acquire();

    vkCmdBeginRenderingKHRHandle (
                handle,
                prepareContext ( & context.data().begin.commandBufferRendering, pRenderingInfo )
    );

    return ResultSuccess;

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

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_2_R ( LastCreatedInstance :: acquire(), vkCmdEndRendering, KHR )

    if ( vkCmdEndRenderingHandle != nullptr ) {
        vkCmdEndRenderingHandle ( handle );
        return ResultSuccess;
    }

    vkCmdEndRenderingKHRHandle ( handle );
    return ResultSuccess;

#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkCmdEndRendering )

    vkCmdEndRenderingHandle ( handle );
    return ResultSuccess;

#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkCmdEndRenderingKHR )

    vkCmdEndRenderingKHRHandle ( handle );
    return ResultSuccess;

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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkCreateRenderPass )

    auto context = ContextManager :: acquire();

    return static_cast < Type ( Result ) > (
            vkCreateRenderPassHandle (
                    deviceHandle,
                    prepareContext ( & context.data().create.renderPass, pCreateInfo ),
                    AllocatorHandler :: apply ( pAllocationCallbacks ),
                    pHandle
            )
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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkCreateRenderPass2 )

    auto context = ContextManager :: acquire();

    return static_cast < Type ( Result ) > (
            vkCreateRenderPass2Handle (
                    deviceHandle,
                    prepareContext ( & context.data().create.renderPass2, pCreateInfo ),
                    AllocatorHandler :: apply ( pAllocationCallbacks ),
                    pHandle
            )
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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkDestroyRenderPass )

    vkDestroyRenderPassHandle (
            deviceHandle,
            renderPassHandle,
            AllocatorHandler :: apply ( pAllocationCallbacks )
    );

    return ResultSuccess;
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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkCreateFramebuffer )

    auto context = ContextManager :: acquire();

    return static_cast < Type ( Result ) > (
            vkCreateFramebufferHandle (
                    deviceHandle,
                    prepareContext ( & context.data().create.frameBuffer, pCreateInfo ),
                    AllocatorHandler :: apply ( pAllocationCallbacks ),
                    pHandle
            )
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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkDestroyFramebuffer )

    auto context = ContextManager :: acquire();

    vkDestroyFramebufferHandle (
            deviceHandle,
            handle,
            AllocatorHandler :: apply ( pAllocationCallbacks )
    );

    return ResultSuccess;
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkCmdBeginRenderPass )

    auto context = ContextManager :: acquire();

    vkCmdBeginRenderPassHandle (
            commandBufferHandle,
            prepareContext ( & context.data().begin.renderPass, pInfo ),
            static_cast < VkSubpassContents > ( subpassContents )
    );

    return ResultSuccess;
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkCmdBeginRenderPass2 )

    auto context = ContextManager :: acquire();

    vkCmdBeginRenderPass2Handle (
            commandBufferHandle,
            prepareContext ( & context.data().begin.renderPass, pRenderPassBeginInfo ),
            prepareContext ( & context.data().begin.renderPass, pSubpassBeginInfo )
    );

    return ResultSuccess;
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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkGetRenderAreaGranularity )

    vkGetRenderAreaGranularityHandle (
            deviceHandle,
            renderPassHandle,
            pGranularity
    );

    return ResultSuccess;
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkCmdNextSubpass )

    vkCmdNextSubpassHandle (
            commandBufferHandle,
            static_cast < VkSubpassContents > ( contents )
    );

    return ResultSuccess;
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkCmdNextSubpass2 )

    auto context = ContextManager :: acquire();

    vkCmdNextSubpass2Handle (
            commandBufferHandle,
            prepareContext ( & context.data().other.nextSubpass, pBeginInfo ),
            prepareContext ( & context.data().other.nextSubpass, pEndInfo )
    );

    return ResultSuccess;
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkCmdEndRenderPass )

    vkCmdEndRenderPassHandle ( handle );

    return ResultSuccess;
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkCmdEndRenderPass2 )

    auto context = ContextManager :: acquire();

    vkCmdEndRenderPass2Handle (
            handle,
            prepareContext ( & context.data().other.nextSubpass, pInfo )
    );

    return ResultSuccess;
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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkCreateShaderModule )

    auto context = ContextManager :: acquire();

    return static_cast < Type ( Result ) > (
            vkCreateShaderModuleHandle (
                    deviceHandle,
                    prepareContext ( & context.data().create.shaderModule, pCreateInfo ),
                    AllocatorHandler :: apply ( pAllocationCallbacks ),
                    pShaderModuleHandle
            )
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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkDestroyShaderModule )

    vkDestroyShaderModuleHandle (
            deviceHandle,
            shaderModuleHandle,
            AllocatorHandler :: apply ( pAllocationCallbacks )
    );

    return ResultSuccess;
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkCmdSetPatchControlPointsEXT )

    vkCmdSetPatchControlPointsEXTHandle ( commandBufferHandle, patchControlPoints );
    return ResultSuccess;
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkGetPhysicalDeviceCooperativeMatrixPropertiesNV )

    if ( pProperties == nullptr ) {
        return static_cast < Type ( Result ) > (
                vkGetPhysicalDeviceCooperativeMatrixPropertiesNVHandle (
                        physicalDeviceHandle,
                        pCount,
                        nullptr
                )
        );
    }

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( * pCount > engine :: vulkan :: config :: cooperativeMatrixPropertiesCount ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

    auto context = ContextManager :: acquire();

    if (
            auto result = vkGetPhysicalDeviceCooperativeMatrixPropertiesNVHandle (
                    physicalDeviceHandle,
                    pCount,
                    & context.data().get.physicalDeviceCooperativeMatrixProperties.properties[0]
            ); result != VK_SUCCESS
    ) {
        return static_cast < Type ( Result ) > ( result );
    }

    for ( uint32 i = 0U; i < * pCount; ++ i ) {
        (void) fromVulkanFormat ( & pProperties[i], & context.data().get.physicalDeviceCooperativeMatrixProperties.properties[0] );
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkCreateValidationCacheEXT )

    auto context = ContextManager :: acquire();

    return static_cast < Type ( Result ) > (
            vkCreateValidationCacheEXTHandle (
                    deviceHandle,
                    toVulkanFormat ( & context.data().create.validationCache.createInfo, pCreateInfo ),
                    AllocatorHandler :: apply ( pAllocationCallbacks ),
                    pHandle
            )
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkMergeValidationCachesEXT )

    return static_cast < Type ( Result ) > (
            vkMergeValidationCachesEXTHandle (
                    deviceHandle,
                    destinationCacheHandle,
                    sourceCacheCount,
                    pSourceCacheHandles
            )
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkGetValidationCacheDataEXT )

    std :: size_t size;

    if ( pData == nullptr ) {
        if (
                auto result = vkGetValidationCacheDataEXTHandle (
                        deviceHandle,
                        validationCacheHandle,
                        & size,
                        nullptr
                ); result != VK_SUCCESS
        ) {
            return static_cast < Type ( Result ) > ( result );
        }

        * pDataSize = size;
        return ResultSuccess;
    }

    size = * pDataSize;
    return static_cast < Type ( Result ) > (
            vkGetValidationCacheDataEXTHandle (
                    deviceHandle,
                    validationCacheHandle,
                    & size,
                    pData
            )
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

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION_R ( LastCreatedInstance :: acquire(), vkDestroyValidationCacheEXT )

    vkDestroyValidationCacheEXTHandle (
            deviceHandle,
            validationCacheHandle,
            AllocatorHandler :: apply ( pAllocationCallbacks )
    );

    return ResultSuccess;
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

    __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION_R ( deviceHandle, vkCreateComputePipelines )

    auto context = ContextManager :: acquire();

    if (
            auto result = vkCreateComputePipelinesHandle (
                    deviceHandle,
                    pipelineCacheHandle,
                    count,
                    & prepareContext ( & context->create.pipeline.compute, count, & pCreateInfos[0] ) [0],
                    AllocatorHandler :: apply ( pAllocationCallbacks ),
                    & pPipelineHandles [0]
            ); result != VK_SUCCESS
    ) {
        return static_cast < Type ( Result ) > ( result );
    }

    extractContext ( count, & pCreateInfos[0], & context->create.pipeline.compute );

    return ResultSuccess;
}
#endif

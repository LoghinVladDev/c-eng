//
// Created by loghin on 28.12.2021.
//

#ifndef __C_ENG_VULKAN_API_CALLS_HPP__
#define __C_ENG_VULKAN_API_CALLS_HPP__

namespace engine { // NOLINT(modernize-concat-nested-namespaces)

    namespace vulkan {

        __C_ENG_NO_DISCARD extern auto enumerateInstanceVersion (
                cds :: uint32 *
        ) noexcept -> __C_ENG_TYPE ( Result );

        __C_ENG_NO_DISCARD extern auto enumerateInstanceLayerProperties (
                cds :: uint32                    *,
                __C_ENG_TYPE ( LayerProperties ) * = nullptr
        ) noexcept -> __C_ENG_TYPE ( Result );

        __C_ENG_NO_DISCARD __C_ENG_MAYBE_UNUSED extern auto enumerateDeviceLayerProperties (
                __C_ENG_TYPE ( PhysicalDeviceHandle ),
                cds :: uint32 *,
                __C_ENG_TYPE ( LayerProperties ) * = nullptr
        ) noexcept -> __C_ENG_TYPE ( Result );

        __C_ENG_NO_DISCARD extern auto enumerateInstanceExtensionProperties (
                cds :: StringLiteral,
                cds :: uint32                        *,
                __C_ENG_TYPE ( ExtensionProperties ) * = nullptr
        ) noexcept -> __C_ENG_TYPE ( Result );

        __C_ENG_NO_DISCARD extern auto enumeratePhysicalDevices (
                __C_ENG_TYPE ( InstanceHandle ),
                cds :: uint32                         *,
                __C_ENG_TYPE ( PhysicalDeviceHandle ) * = nullptr
        ) noexcept -> __C_ENG_TYPE ( Result );

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

        __C_ENG_NO_DISCARD __C_ENG_MAYBE_UNUSED extern auto enumeratePhysicalDeviceQueueFamilyPerformanceQueryCounters (
                __C_ENG_TYPE ( InstanceHandle ),
                __C_ENG_TYPE ( PhysicalDeviceHandle ),
                cds :: uint32,
                cds :: uint32                                   *,
                __C_ENG_TYPE ( PerformanceCounter )             * = nullptr,
                __C_ENG_TYPE ( PerformanceCounterDescription )  * = nullptr
        ) noexcept -> __C_ENG_TYPE ( Result );

#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

        __C_ENG_NO_DISCARD __C_ENG_MAYBE_UNUSED extern auto enumeratePhysicalDeviceGroups (
                __C_ENG_TYPE ( InstanceHandle ),
                cds :: uint32                                   *,
                __C_ENG_TYPE ( PhysicalDeviceGroupProperties )  * = nullptr
        ) noexcept -> __C_ENG_TYPE ( Result );

#endif

        __C_ENG_NO_DISCARD extern auto createInstance (
                __C_ENG_TYPE ( InstanceCreateInfo )     const *,
                __C_ENG_TYPE ( AllocationCallbacks )    const *,
                __C_ENG_TYPE ( InstanceHandle )               *
        ) noexcept -> __C_ENG_TYPE ( Result );

        __C_ENG_NO_DISCARD extern auto createDebugMessenger (
                __C_ENG_TYPE ( InstanceHandle ),
                __C_ENG_TYPE ( DebugMessengerCreateInfo )   const *,
                __C_ENG_TYPE ( AllocationCallbacks )        const *,
                __C_ENG_TYPE ( DebugMessengerHandle )             *
        ) noexcept -> __C_ENG_TYPE ( Result );

        __C_ENG_NO_DISCARD extern auto createSurface (
                __C_ENG_TYPE ( InstanceHandle ),
                GLFWwindow                                  *,
                __C_ENG_TYPE ( AllocationCallbacks )  const *,
                __C_ENG_TYPE ( SurfaceHandle )              *
        ) noexcept -> __C_ENG_TYPE ( Result );

        __C_ENG_NO_DISCARD extern auto createDevice (
                __C_ENG_TYPE ( PhysicalDeviceHandle ),
                __C_ENG_TYPE ( DeviceCreateInfo )       const *,
                __C_ENG_TYPE ( AllocationCallbacks )    const *,
                __C_ENG_TYPE ( DeviceHandle )                 *
        ) noexcept -> __C_ENG_TYPE ( Result );

        __C_ENG_NO_DISCARD extern auto destroyInstance (
                __C_ENG_TYPE ( InstanceHandle ),
                __C_ENG_TYPE ( AllocationCallbacks ) const *
        ) noexcept -> __C_ENG_TYPE ( Result );

        __C_ENG_NO_DISCARD extern auto destroyDebugMessenger (
                __C_ENG_TYPE ( InstanceHandle ),
                __C_ENG_TYPE ( DebugMessengerHandle ),
                __C_ENG_TYPE ( AllocationCallbacks ) const *
        ) noexcept -> __C_ENG_TYPE ( Result );

        __C_ENG_NO_DISCARD extern auto destroySurface (
                __C_ENG_TYPE ( InstanceHandle ),
                __C_ENG_TYPE ( SurfaceHandle ),
                __C_ENG_TYPE ( AllocationCallbacks ) const *
        ) noexcept -> __C_ENG_TYPE ( Result );

        __C_ENG_NO_DISCARD __C_ENG_MAYBE_UNUSED extern auto getPhysicalDeviceProperties (
                __C_ENG_TYPE ( PhysicalDeviceHandle ),
                __C_ENG_TYPE ( PhysicalDeviceProperties ) *
        ) noexcept -> __C_ENG_TYPE ( Result );

        __C_ENG_NO_DISCARD extern auto getPhysicalDeviceProperties (
                __C_ENG_TYPE ( PhysicalDeviceHandle ),
                __C_ENG_TYPE ( PhysicalDeviceExtendedProperties ) *
        ) noexcept -> __C_ENG_TYPE ( Result );

        __C_ENG_NO_DISCARD extern auto getPhysicalDeviceFeatures (
                __C_ENG_TYPE ( PhysicalDeviceHandle ),
                __C_ENG_TYPE ( PhysicalDeviceFeatures ) *
        ) noexcept -> __C_ENG_TYPE ( Result );

        __C_ENG_NO_DISCARD extern auto getPhysicalDeviceFeatures (
                __C_ENG_TYPE ( PhysicalDeviceHandle ),
                __C_ENG_TYPE ( PhysicalDeviceExtendedFeatures ) *
        ) noexcept -> __C_ENG_TYPE ( Result );

        __C_ENG_NO_DISCARD extern auto getPhysicalDeviceDetails (
                __C_ENG_TYPE ( PhysicalDeviceHandle ),
                __C_ENG_TYPE ( PhysicalDeviceDetails ) *
        ) noexcept -> __C_ENG_TYPE ( Result );

        __C_ENG_NO_DISCARD __C_ENG_MAYBE_UNUSED extern auto getPhysicalDeviceQueueFamilyProperties (
                __C_ENG_TYPE ( PhysicalDeviceHandle ),
                cds :: uint32                           *,
                __C_ENG_TYPE ( QueueFamilyProperties )  * = nullptr
        ) noexcept -> __C_ENG_TYPE ( Result );

        __C_ENG_NO_DISCARD extern auto getPhysicalDeviceQueueFamilyProperties (
                __C_ENG_TYPE ( PhysicalDeviceHandle ),
                cds :: uint32                                   *,
                __C_ENG_TYPE ( QueueFamilyExtendedProperties )  * = nullptr
        ) noexcept -> __C_ENG_TYPE ( Result );

        __C_ENG_NO_DISCARD extern auto getPhysicalDeviceQueueFamilyDetails (
                __C_ENG_TYPE ( PhysicalDeviceHandle ),
                cds :: uint32                       *,
                __C_ENG_TYPE ( QueueFamilyDetails ) * = nullptr
        ) noexcept -> __C_ENG_TYPE ( Result );

        __C_ENG_NO_DISCARD __C_ENG_MAYBE_UNUSED extern auto getFunctionAddress (
                cds :: StringLiteral,
                void **
        ) noexcept -> __C_ENG_TYPE ( Result );

        __C_ENG_NO_DISCARD __C_ENG_MAYBE_UNUSED extern auto getInstanceFunctionAddress (
                __C_ENG_TYPE ( InstanceHandle ),
                cds :: StringLiteral,
                void **
        ) noexcept -> __C_ENG_TYPE ( Result );

        __C_ENG_NO_DISCARD __C_ENG_MAYBE_UNUSED extern auto getDeviceFunctionAddress (
                __C_ENG_TYPE ( DeviceHandle ),
                cds :: StringLiteral,
                void **
        ) noexcept -> __C_ENG_TYPE ( Result );

    }

}

#endif //__C_ENG_VULKAN_API_CALLS_HPP__

//
// Created by loghin on 28.12.2021.
//

#ifndef __C_ENG_VULKAN_API_CALLS_HPP__
#define __C_ENG_VULKAN_API_CALLS_HPP__

#include <Preprocess.hpp>
#include <CDS/Types>
#include <VulkanCore.hpp>


#define C_ENG_MAP_START     HEADER
#include <ObjectMapping.hpp>

namespace engine { // NOLINT(modernize-concat-nested-namespaces)

    namespace vulkan {

        NoDiscard extern auto enumerateInstanceVersion (
                cds :: uint32 *
        ) noexcept -> Type ( Result );

        NoDiscard extern auto enumerateInstanceLayerProperties (
                cds :: uint32            *,
                Type ( LayerProperties ) * = nullptr
        ) noexcept -> Type ( Result );

        NoDiscard MaybeUnused extern auto enumeratePhysicalDeviceLayerProperties (
                Type ( PhysicalDeviceHandle ),
                cds :: uint32                   *,
                Type ( LayerProperties )        * = nullptr
        ) noexcept -> Type ( Result );

        NoDiscard extern auto enumerateInstanceExtensionProperties (
                cds :: StringLiteral,
                cds :: uint32                *,
                Type ( ExtensionProperties ) * = nullptr
        ) noexcept -> Type ( Result );

        NoDiscard extern auto enumeratePhysicalDevices (
                Type ( InstanceHandle ),
                cds :: uint32                 *,
                Type ( PhysicalDeviceHandle ) * = nullptr
        ) noexcept -> Type ( Result );

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

        NoDiscard MaybeUnused extern auto enumeratePhysicalDeviceQueueFamilyPerformanceQueryCounters (
                Type ( InstanceHandle ),
                Type ( PhysicalDeviceHandle ),
                cds :: uint32,
                cds :: uint32                           *,
                Type ( PerformanceCounter )             * = nullptr,
                Type ( PerformanceCounterDescription )  * = nullptr
        ) noexcept -> Type ( Result );

#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

        NoDiscard MaybeUnused extern auto enumeratePhysicalDeviceGroups (
                Type ( InstanceHandle ),
                cds :: uint32                           *,
                Type ( PhysicalDeviceGroupProperties )  * = nullptr
        ) noexcept -> Type ( Result );

#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

        NoDiscard MaybeUnused extern auto enumeratePhysicalDeviceExtensionProperties (
                Type ( PhysicalDeviceHandle ),
                cds :: StringLiteral,
                cds :: uint32                   *,
                Type ( ExtensionProperties )    * = nullptr
        ) noexcept -> Type ( Result );

        NoDiscard MaybeUnused extern auto enumeratePhysicalDeviceExtensionProperties (
                Type ( PhysicalDeviceHandle ),
                cds :: uint32                   *,
                Type ( ExtensionProperties )    * = nullptr
        ) noexcept -> Type ( Result );

#endif

        NoDiscard extern auto createInstance (
                Type ( InstanceCreateInfo )     const *,
                Type ( AllocationCallbacks )    const *,
                Type ( InstanceHandle )               *
        ) noexcept -> Type ( Result );

        NoDiscard extern auto createDebugMessenger (
                Type ( InstanceHandle ),
                Type ( DebugMessengerCreateInfo )   const *,
                Type ( AllocationCallbacks )        const *,
                Type ( DebugMessengerHandle )             *
        ) noexcept -> Type ( Result );

        NoDiscard extern auto createSurface (
                Type ( InstanceHandle ),
                GLFWwindow                          *,
                Type ( AllocationCallbacks )  const *,
                Type ( SurfaceHandle )              *
        ) noexcept -> Type ( Result );

        NoDiscard extern auto createDevice (
                Type ( PhysicalDeviceHandle ),
                Type ( DeviceCreateInfo )       const *,
                Type ( AllocationCallbacks )    const *,
                Type ( DeviceHandle )                 *
        ) noexcept -> Type ( Result );

        NoDiscard extern auto destroyInstance (
                Type ( InstanceHandle ),
                Type ( AllocationCallbacks ) const *
        ) noexcept -> Type ( Result );

        NoDiscard extern auto destroyDebugMessenger (
                Type ( InstanceHandle ),
                Type ( DebugMessengerHandle ),
                Type ( AllocationCallbacks ) const *
        ) noexcept -> Type ( Result );

        NoDiscard extern auto destroySurface (
                Type ( InstanceHandle ),
                Type ( SurfaceHandle ),
                Type ( AllocationCallbacks ) const *
        ) noexcept -> Type ( Result );

        NoDiscard extern auto destroyDevice (
                Type ( DeviceHandle ),
                Type ( AllocationCallbacks ) const *
        ) noexcept -> Type ( Result );

        NoDiscard MaybeUnused extern auto getPhysicalDeviceProperties (
                Type ( PhysicalDeviceHandle ),
                Type ( PhysicalDeviceProperties ) *
        ) noexcept -> Type ( Result );

        NoDiscard extern auto getPhysicalDeviceProperties (
                Type ( PhysicalDeviceHandle ),
                Type ( PhysicalDeviceExtendedProperties ) *
        ) noexcept -> Type ( Result );

        NoDiscard extern auto getPhysicalDeviceFeatures (
                Type ( PhysicalDeviceHandle ),
                Type ( PhysicalDeviceFeatures ) *
        ) noexcept -> Type ( Result );

        NoDiscard extern auto getPhysicalDeviceFeatures (
                Type ( PhysicalDeviceHandle ),
                Type ( PhysicalDeviceExtendedFeatures ) *
        ) noexcept -> Type ( Result );

        NoDiscard extern auto getPhysicalDeviceDetails (
                Type ( PhysicalDeviceHandle ),
                Type ( PhysicalDeviceDetails ) *
        ) noexcept -> Type ( Result );

        NoDiscard MaybeUnused extern auto getPhysicalDeviceQueueFamilyProperties (
                Type ( PhysicalDeviceHandle ),
                cds :: uint32                   *,
                Type ( QueueFamilyProperties )  * = nullptr
        ) noexcept -> Type ( Result );

        NoDiscard extern auto getPhysicalDeviceQueueFamilyProperties (
                Type ( PhysicalDeviceHandle ),
                cds :: uint32                           *,
                Type ( QueueFamilyExtendedProperties )  * = nullptr
        ) noexcept -> Type ( Result );

        NoDiscard extern auto getPhysicalDeviceQueueFamilyDetails (
                Type ( PhysicalDeviceHandle ),
                cds :: uint32               *,
                Type ( QueueFamilyDetails ) * = nullptr
        ) noexcept -> Type ( Result );

        NoDiscard MaybeUnused extern auto getFunctionAddress (
                cds :: StringLiteral,
                void **
        ) noexcept -> Type ( Result );

        NoDiscard MaybeUnused extern auto getInstanceFunctionAddress (
                Type ( InstanceHandle ),
                cds :: StringLiteral,
                void **
        ) noexcept -> Type ( Result );

        NoDiscard MaybeUnused extern auto getDeviceFunctionAddress (
                Type ( DeviceHandle ),
                cds :: StringLiteral,
                void **
        ) noexcept -> Type ( Result );

        NoDiscard MaybeUnused extern auto getPhysicalDeviceSurfaceSupport (
                Type ( PhysicalDeviceHandle ),
                cds :: uint32,
                Type ( SurfaceHandle ),
                bool                            *
        ) noexcept -> Type ( Result );

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

        NoDiscard MaybeUnused extern auto getDeviceQueue (
                Type ( DeviceHandle ),
                cds :: uint32,
                cds :: uint32,
                Type ( QueueHandle ) *
        ) noexcept -> Type ( Result );

#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

        NoDiscard MaybeUnused extern auto getDeviceQueue (
                Type ( DeviceHandle ),
                Type ( DeviceQueueInfo )  const *,
                Type ( QueueHandle )            *
        ) noexcept -> Type ( Result );

#endif

        namespace utility {
            extern auto chainFeaturesFromDetails (
                    Type ( PhysicalDeviceExtendedFeatures )       *,
                    Type ( PhysicalDeviceDetails )          const *
            ) noexcept -> void;
        }

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE

        NoDiscard MaybeUnused extern auto getPhysicalDeviceSurfaceCapabilities (
                Type ( PhysicalDeviceHandle ),
                Type ( SurfaceHandle ),
                Type ( SurfaceCapabilities ) *
        ) noexcept -> Type ( Result );

        NoDiscard MaybeUnused extern auto getPhysicalDeviceSurfaceFormats (
                Type ( PhysicalDeviceHandle ),
                Type ( SurfaceHandle ),
                cds :: uint32                   *,
                Type ( SurfaceFormat )          * = nullptr
        ) noexcept -> Type ( Result );

        NoDiscard MaybeUnused extern auto getPhysicalDeviceSurfacePresentModes (
                Type ( PhysicalDeviceHandle ),
                Type ( SurfaceHandle ),
                cds :: uint32                   *,
                Type ( PresentMode )            * = nullptr
        ) noexcept -> Type ( Result );

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISPLAY_SURFACE_COUNTER_AVAILABLE

        NoDiscard MaybeUnused extern auto getPhysicalDeviceSurfaceCapabilities (
                Type ( PhysicalDeviceHandle ),
                Type ( SurfaceHandle ),
                Type ( SurfaceCapabilities2 ) *
        ) noexcept -> Type ( Result );

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_GET_SURFACE_CAPABILITIES_AVAILABLE

        NoDiscard MaybeUnused extern auto getPhysicalDeviceSurfaceFormats (
                Type ( PhysicalDeviceHandle ),
                Type ( PhysicalDeviceSurfaceInfo ) const *,
                cds :: uint32                            *,
                Type ( SurfaceFormat2 )                  * = nullptr
        ) noexcept -> Type ( Result );

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FULL_SCREEN_EXCLUSIVE_AVAILABLE

        NoDiscard MaybeUnused extern auto getPhysicalDeviceSurfacePresentModes (
                Type ( PhysicalDeviceHandle ),
                Type ( PhysicalDeviceSurfaceInfo ) const *,
                cds :: uint32                            *,
                Type ( PresentMode )                     * = nullptr
        ) noexcept -> Type ( Result );

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE

        NoDiscard MaybeUnused extern auto createSwapChain (
                Type ( DeviceHandle ),
                Type ( SwapChainCreateInfo )    const *,
                Type ( AllocationCallbacks )    const *,
                Type ( SwapChainHandle )              *
        ) noexcept -> Type ( Result );

        NoDiscard MaybeUnused extern auto destroySwapChain (
                Type ( DeviceHandle ),
                Type ( SwapChainHandle ),
                Type ( AllocationCallbacks ) const *
        ) noexcept -> Type ( Result );

        NoDiscard MaybeUnused extern auto getSwapChainImages (
                Type ( DeviceHandle ),
                Type ( SwapChainHandle ),
                cds :: uint32               *,
                Type ( ImageHandle )        * = nullptr
        ) noexcept -> Type ( Result );

#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

        NoDiscard MaybeUnused extern auto createImageView (
                Type ( DeviceHandle ),
                Type ( ImageViewCreateInfo )    const *,
                Type ( AllocationCallbacks )    const *,
                Type ( ImageViewHandle )              *
        ) noexcept -> Type ( Result );

        NoDiscard MaybeUnused extern auto destroyImageView (
                Type ( DeviceHandle ),
                Type ( ImageViewHandle ),
                Type ( AllocationCallbacks )    const *
        ) noexcept -> Type ( Result );

        NoDiscard MaybeUnused extern auto createCommandPool (
                Type ( DeviceHandle ),
                Type ( CommandPoolCreateInfo )  const *,
                Type ( AllocationCallbacks )    const *,
                Type ( CommandPoolHandle )            *
        ) noexcept -> Type ( Result );

        NoDiscard MaybeUnused extern auto destroyCommandPool (
                Type ( DeviceHandle ),
                Type ( CommandPoolHandle ),
                Type ( AllocationCallbacks )    const *
        ) noexcept -> Type ( Result );

        NoDiscard MaybeUnused extern auto resetCommandPool (
                Type ( DeviceHandle ),
                Type ( CommandPoolHandle ),
                Type ( CommandPoolResetFlags )
        ) noexcept -> Type ( Result );

        NoDiscard MaybeUnused extern auto allocateCommandBuffers (
                Type ( DeviceHandle ),
                Type ( CommandBufferAllocateInfo )  const *,
                Type ( CommandBufferHandle )              *
        ) noexcept -> Type ( Result );

        NoDiscard MaybeUnused extern auto resetCommandBuffer (
                Type ( CommandBufferHandle ),
                Type ( CommandBufferResetFlags )
        ) noexcept -> Type ( Result );

        NoDiscard MaybeUnused extern auto freeCommandBuffers (
                Type ( DeviceHandle ),
                Type ( CommandPoolHandle ),
                cds :: uint32,
                Type ( CommandBufferHandle )    *
        ) noexcept -> Type ( Result );

        NoDiscard MaybeUnused extern auto beginCommandBuffer (
                Type ( CommandBufferHandle ),
                Type ( CommandBufferBeginInfo ) const *
        ) noexcept -> Type ( Result );

        NoDiscard MaybeUnused extern auto endCommandBuffer (
                Type ( CommandBufferHandle )
        ) noexcept -> Type ( Result );

#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_AVAILABLE

        NoDiscard MaybeUnused extern auto trimCommandPool (
                Type ( DeviceHandle ),
                Type ( CommandPoolHandle ),
                Type ( CommandPoolTrimFlags )
        ) noexcept -> Type ( Result );

#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

        NoDiscard MaybeUnused extern auto queueSubmit (
                Type ( QueueHandle ),
                cds :: uint32,
                Type ( SubmitInfo ) const *,
                Type ( FenceHandle )
        ) noexcept -> Type ( Result );

        NoDiscard MaybeUnused extern auto commandBufferExecuteCommands (
                Type ( CommandBufferHandle ),
                cds :: uint32,
                Type ( CommandBufferHandle ) const *
        ) noexcept -> Type ( Result );

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE

        NoDiscard MaybeUnused extern auto queueSubmit (
                Type ( QueueHandle ),
                cds :: uint32,
                Type ( SubmitInfo2 ) const *,
                Type ( FenceHandle )
        ) noexcept -> Type ( Result );

#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DEVICE_GROUP_AVAILABLE

        NoDiscard MaybeUnused extern auto commandBufferSetDeviceMask (
                Type ( CommandBufferHandle ),
                cds :: uint32
        ) noexcept -> Type ( Result );

#endif

    }

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //__C_ENG_VULKAN_API_CALLS_HPP__

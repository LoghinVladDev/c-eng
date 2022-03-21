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

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard extern auto enumerateInstanceVersion (
                cds :: uint32 *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard extern auto enumerateInstanceLayerProperties (
                cds :: uint32            *,
                Type ( LayerProperties ) * = nullptr
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto enumeratePhysicalDeviceLayerProperties (
                Type ( PhysicalDeviceHandle ),
                cds :: uint32                   *,
                Type ( LayerProperties )        * = nullptr
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard extern auto enumerateInstanceExtensionProperties (
                cds :: StringLiteral,
                cds :: uint32                *,
                Type ( ExtensionProperties ) * = nullptr
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard extern auto enumeratePhysicalDevices (
                Type ( InstanceHandle ),
                cds :: uint32                 *,
                Type ( PhysicalDeviceHandle ) * = nullptr
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
        NoDiscard MaybeUnused extern auto enumeratePhysicalDeviceQueueFamilyPerformanceQueryCounters (
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

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard extern auto createInstance (
                Type ( InstanceCreateInfo )     const *,
                Type ( AllocationCallbacks )    const *,
                Type ( InstanceHandle )               *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_UTILS_AVAILABLE
        NoDiscard extern auto createDebugMessenger (
                Type ( InstanceHandle ),
                Type ( DebugMessengerCreateInfo )   const *,
                Type ( AllocationCallbacks )        const *,
                Type ( DebugMessengerHandle )             *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE
        NoDiscard extern auto createSurface (
                Type ( InstanceHandle ),
                GLFWwindow                          *,
                Type ( AllocationCallbacks )  const *,
                Type ( SurfaceHandle )              *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard extern auto createDevice (
                Type ( PhysicalDeviceHandle ),
                Type ( DeviceCreateInfo )       const *,
                Type ( AllocationCallbacks )    const *,
                Type ( DeviceHandle )                 *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard extern auto optimizeForSingleDevice (
                Type ( DeviceHandle ),
                Type ( DeviceCreateInfo )   const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard extern auto destroyInstance (
                Type ( InstanceHandle ),
                Type ( AllocationCallbacks ) const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_UTILS_AVAILABLE
        NoDiscard extern auto destroyDebugMessenger (
                Type ( InstanceHandle ),
                Type ( DebugMessengerHandle ),
                Type ( AllocationCallbacks ) const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE
        NoDiscard extern auto destroySurface (
                Type ( InstanceHandle ),
                Type ( SurfaceHandle ),
                Type ( AllocationCallbacks ) const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard extern auto destroyDevice (
                Type ( DeviceHandle ),
                Type ( AllocationCallbacks ) const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto getPhysicalDeviceProperties (
                Type ( PhysicalDeviceHandle ),
                Type ( PhysicalDeviceProperties ) *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
        NoDiscard extern auto getPhysicalDeviceProperties (
                Type ( PhysicalDeviceHandle ),
                Type ( PhysicalDeviceExtendedProperties ) *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard extern auto getPhysicalDeviceFeatures (
                Type ( PhysicalDeviceHandle ),
                Type ( PhysicalDeviceFeatures ) *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
        NoDiscard extern auto getPhysicalDeviceFeatures (
                Type ( PhysicalDeviceHandle ),
                Type ( PhysicalDeviceExtendedFeatures ) *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
        NoDiscard extern auto getPhysicalDeviceDetails (
                Type ( PhysicalDeviceHandle ),
                Type ( PhysicalDeviceDetails ) *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto getPhysicalDeviceQueueFamilyProperties (
                Type ( PhysicalDeviceHandle ),
                cds :: uint32                   *,
                Type ( QueueFamilyProperties )  * = nullptr
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
        NoDiscard extern auto getPhysicalDeviceQueueFamilyProperties (
                Type ( PhysicalDeviceHandle ),
                cds :: uint32                           *,
                Type ( QueueFamilyExtendedProperties )  * = nullptr
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
        NoDiscard extern auto getPhysicalDeviceQueueFamilyDetails (
                Type ( PhysicalDeviceHandle ),
                cds :: uint32               *,
                Type ( QueueFamilyDetails ) * = nullptr
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto getFunctionAddress (
                cds :: StringLiteral,
                void **
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto getInstanceFunctionAddress (
                Type ( InstanceHandle ),
                cds :: StringLiteral,
                void **
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto getDeviceFunctionAddress (
                Type ( DeviceHandle ),
                cds :: StringLiteral,
                void **
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE
        NoDiscard MaybeUnused extern auto getPhysicalDeviceSurfaceSupport (
                Type ( PhysicalDeviceHandle ),
                cds :: uint32,
                Type ( SurfaceHandle ),
                bool                            *
        ) noexcept -> Type ( Result );
#endif

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
                    Type ( PhysicalDeviceDetails )                *
            ) noexcept -> void;
        }

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE
        NoDiscard MaybeUnused extern auto getPhysicalDeviceSurfaceCapabilities (
                Type ( PhysicalDeviceHandle ),
                Type ( SurfaceHandle ),
                Type ( SurfaceCapabilities ) *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE
        NoDiscard MaybeUnused extern auto getPhysicalDeviceSurfaceFormats (
                Type ( PhysicalDeviceHandle ),
                Type ( SurfaceHandle ),
                cds :: uint32                   *,
                Type ( SurfaceFormat )          * = nullptr
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE
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
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE
        NoDiscard MaybeUnused extern auto destroySwapChain (
                Type ( DeviceHandle ),
                Type ( SwapChainHandle ),
                Type ( AllocationCallbacks ) const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE
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
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto destroyImageView (
                Type ( DeviceHandle ),
                Type ( ImageViewHandle ),
                Type ( AllocationCallbacks )    const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto createCommandPool (
                Type ( DeviceHandle ),
                Type ( CommandPoolCreateInfo )  const *,
                Type ( AllocationCallbacks )    const *,
                Type ( CommandPoolHandle )            *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto destroyCommandPool (
                Type ( DeviceHandle ),
                Type ( CommandPoolHandle ),
                Type ( AllocationCallbacks )    const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto resetCommandPool (
                Type ( DeviceHandle ),
                Type ( CommandPoolHandle ),
                Type ( CommandPoolResetFlags )
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto allocateCommandBuffers (
                Type ( DeviceHandle ),
                Type ( CommandBufferAllocateInfo )  const *,
                Type ( CommandBufferHandle )              *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto resetCommandBuffer (
                Type ( CommandBufferHandle ),
                Type ( CommandBufferResetFlags )
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto freeCommandBuffers (
                Type ( DeviceHandle ),
                Type ( CommandPoolHandle ),
                cds :: uint32,
                Type ( CommandBufferHandle )    *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto beginCommandBuffer (
                Type ( CommandBufferHandle ),
                Type ( CommandBufferBeginInfo ) const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
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
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
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

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto createFence (
                Type ( DeviceHandle ),
                Type ( FenceCreateInfo )        const *,
                Type ( AllocationCallbacks )    const *,
                Type ( FenceHandle )                  *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_WIN32_AVAILABLE
        NoDiscard MaybeUnused extern auto getFenceWin32Handle (
                Type ( DeviceHandle ),
                Type ( FenceGetWin32HandleInfo )    const *,
                HANDLE                                    *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_FD_AVAILABLE
        NoDiscard MaybeUnused extern auto getFenceFD (
                Type ( DeviceHandle ),
                Type ( FenceGetFDInfo ) const *,
                int                           *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto destroyFence (
                Type ( DeviceHandle ),
                Type ( FenceHandle ),
                Type ( AllocationCallbacks )    const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto getFenceStatus (
                Type ( DeviceHandle ),
                Type ( FenceHandle )
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto resetFences (
                Type ( DeviceHandle ),
                cds :: uint32,
                Type ( FenceHandle )    const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto waitForFences (
                Type ( DeviceHandle ),
                cds :: uint32,
                Type ( FenceHandle )    const *,
                bool,
                cds :: uint64
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISPLAY_CONTROL_AVAILABLE
        NoDiscard MaybeUnused extern auto registerDeviceEvent (
                Type ( DeviceHandle ),
                Type ( DeviceEventInfo )        const *,
                Type ( AllocationCallbacks )    const *,
                Type ( FenceHandle )                  *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISPLAY_CONTROL_AVAILABLE
        NoDiscard MaybeUnused extern auto registerDisplayEvent (
                Type ( DeviceHandle ),
                Type ( DisplayHandle ),
                Type ( DisplayEventInfo )       const *,
                Type ( AllocationCallbacks )    const *,
                Type ( FenceHandle )                  *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_WIN32_AVAILABLE
        NoDiscard MaybeUnused extern auto importFenceWin32Handle (
                Type ( DeviceHandle ),
                Type ( ImportFenceWin32HandleInfo ) const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_FD_AVAILABLE
        NoDiscard MaybeUnused extern auto importFenceFd (
                Type ( DeviceHandle ),
                Type ( ImportFenceFdInfo ) const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto createSemaphore (
                Type ( DeviceHandle ),
                Type ( SemaphoreCreateInfo )    const *,
                Type ( AllocationCallbacks )    const *,
                Type ( SemaphoreHandle )              *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_WIN32_AVAILABLE
        NoDiscard MaybeUnused extern auto getSemaphoreWin32Handle (
                Type ( DeviceHandle ),
                Type ( SemaphoreGetWin32HandleInfo )    const *,
                HANDLE                                        *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_FD_AVAILABLE
        NoDiscard MaybeUnused extern auto getSemaphoreFd (
                Type ( DeviceHandle ),
                Type ( SemaphoreGetFdInfo ) const *,
                int                               *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_SEMAPHORE_AVAILABLE
        NoDiscard MaybeUnused extern auto getSemaphoreZirconHandleGoogle (
                Type ( DeviceHandle ),
                Type ( SemaphoreGetZirconHandleInfoGoogle ) const *,
                zx_handle_t                                       *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto destroySemaphore (
                Type ( DeviceHandle ),
                Type ( SemaphoreHandle ),
                Type ( AllocationCallbacks ) const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
        NoDiscard MaybeUnused extern auto getSemaphoreCounterValue (
                Type ( DeviceHandle ),
                Type ( SemaphoreHandle ),
                cds :: uint64               *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
        NoDiscard MaybeUnused extern auto waitSemaphores (
                Type ( DeviceHandle ),
                Type ( SemaphoreWaitInfo )  const *,
                cds :: uint64
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
        NoDiscard MaybeUnused extern auto signalSemaphore (
                Type ( DeviceHandle ),
                Type ( SemaphoreSignalInfo )  const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_WIN32_AVAILABLE
        NoDiscard MaybeUnused extern auto importSemaphoreWin32Handle (
                Type ( DeviceHandle ),
                Type ( ImportSemaphoreWin32HandleInfo ) const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_FD_AVAILABLE
        NoDiscard MaybeUnused extern auto importSemaphoreFd (
                Type ( DeviceHandle ),
                Type ( ImportSemaphoreFdInfo ) const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_SEMAPHORE_AVAILABLE
        NoDiscard MaybeUnused extern auto importSemaphoreZirconHandleGoogle (
                Type ( DeviceHandle ),
                Type ( ImportSemaphoreZirconHandleInfoGoogle ) const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto createEvent (
                Type ( DeviceHandle ),
                Type ( EventCreateInfo )        const *,
                Type ( AllocationCallbacks )    const *,
                Type ( EventHandle )                  *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto destroyEvent (
                Type ( DeviceHandle ),
                Type ( EventHandle ),
                Type ( AllocationCallbacks )    const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto getEventStatus (
                Type ( DeviceHandle ),
                Type ( EventHandle )
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto setEvent (
                Type ( DeviceHandle ),
                Type ( EventHandle )
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto resetEvent (
                Type ( DeviceHandle ),
                Type ( EventHandle )
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
        NoDiscard MaybeUnused extern auto commandBufferSetEvent (
                Type ( CommandBufferHandle ),
                Type ( EventHandle ),
                Type ( DependencyInfo )         const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto commandBufferSetEvent (
                Type ( CommandBufferHandle ),
                Type ( EventHandle ),
                Type ( PipelineStageFlags )
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto commandBufferResetEvent (
                Type ( CommandBufferHandle ),
                Type ( EventHandle ),
                Type ( PipelineStageFlags )
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
        NoDiscard MaybeUnused extern auto commandBufferWaitEvents (
                Type ( CommandBufferHandle ),
                cds :: uint32,
                Type ( EventHandle )            const *,
                Type ( DependencyInfo )         const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto commandBufferWaitEvents (
                Type ( CommandBufferHandle ),
                cds :: uint32,
                Type ( EventHandle )            const *,
                Type ( PipelineStageFlags ),
                Type ( PipelineStageFlags ),
                cds :: uint32,
                Type ( MemoryBarrier )          const *,
                cds :: uint32,
                Type ( BufferMemoryBarrier )    const *,
                cds :: uint32,
                Type ( ImageMemoryBarrier )     const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto queueWaitIdle (
                Type ( QueueHandle )
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto deviceWaitIdle (
                Type ( DeviceHandle )
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE
        NoDiscard MaybeUnused extern auto commandBufferBeginRendering (
                Type ( CommandBufferHandle ),
                Type ( RenderingInfo )      const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE
        NoDiscard MaybeUnused extern auto commandBufferEndRendering (
                Type ( CommandBufferHandle )
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto createRenderPass (
                Type ( DeviceHandle ),
                Type ( RenderPassCreateInfo )   const *,
                Type ( AllocationCallbacks )    const *,
                Type ( RenderPassHandle )             *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
        NoDiscard MaybeUnused extern auto createRenderPass (
                Type ( DeviceHandle ),
                Type ( RenderPassCreateInfo2 )  const *,
                Type ( AllocationCallbacks )    const *,
                Type ( RenderPassHandle )             *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto destroyRenderPass (
                Type ( DeviceHandle ),
                Type ( RenderPassHandle ),
                Type ( AllocationCallbacks )    const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto createFrameBuffer (
                Type ( DeviceHandle ),
                Type ( FrameBufferCreateInfo )  const *,
                Type ( AllocationCallbacks )    const *,
                Type ( FrameBufferHandle )            *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto destroyFrameBuffer (
                Type ( DeviceHandle ),
                Type ( FrameBufferHandle ),
                Type ( AllocationCallbacks )    const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto commandBufferBeginRenderPass (
                Type ( CommandBufferHandle ),
                Type ( RenderPassBeginInfo )    const *,
                Type ( SubpassContents )
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
        NoDiscard MaybeUnused extern auto commandBufferBeginRenderPass (
                Type ( CommandBufferHandle ),
                Type ( RenderPassBeginInfo )    const *,
                Type ( SubpassBeginInfo )       const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto getRenderAreaGranularity (
                Type ( DeviceHandle ),
                Type ( RenderPassHandle ),
                Type ( Extent2D )           *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto commandBufferNextSubpass (
                Type ( CommandBufferHandle ),
                Type ( SubpassContents )
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
        NoDiscard MaybeUnused extern auto commandBufferNextSubpass (
                Type ( CommandBufferHandle ),
                Type ( SubpassBeginInfo )   const *,
                Type ( SubpassEndInfo )     const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto commandBufferEndRenderPass (
                Type ( CommandBufferHandle )
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
        NoDiscard MaybeUnused extern auto commandBufferEndRenderPass (
                Type ( CommandBufferHandle ),
                Type ( SubpassEndInfo )     const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto createShaderModule (
                Type ( DeviceHandle ),
                Type ( ShaderModuleCreateInfo ) const *,
                Type ( AllocationCallbacks )    const *,
                Type ( ShaderModuleHandle )           *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto destroyShaderModule (
                Type ( DeviceHandle ),
                Type ( ShaderModuleHandle ),
                Type ( AllocationCallbacks )    const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_2_AVAILABLE
        NoDiscard MaybeUnused extern auto commandBufferSetPatchControlPoints (
                Type ( CommandBufferHandle ),
                cds :: uint32
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE
        NoDiscard MaybeUnused extern auto getPhysicalDeviceCooperativeMatrixPropertiesNVidia (
                Type ( PhysicalDeviceHandle ),
                cds :: uint32                               *,
                Type ( CooperativeMatrixPropertiesNVidia )  * = nullptr
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_CACHE_AVAILABLE
        NoDiscard MaybeUnused extern auto createValidationCache (
                Type ( DeviceHandle ),
                Type ( ValidationCacheCreateInfo )  const *,
                Type ( AllocationCallbacks )        const *,
                Type ( ValidationCacheHandle )            *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_CACHE_AVAILABLE
        NoDiscard MaybeUnused extern auto mergeValidationCache (
                Type ( DeviceHandle ),
                Type ( ValidationCacheHandle ),
                cds :: uint32,
                Type ( ValidationCacheHandle )  const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_CACHE_AVAILABLE
        NoDiscard MaybeUnused extern auto getValidationCacheData (
                Type ( DeviceHandle ),
                Type ( ValidationCacheHandle ),
                cds :: uint64 *,
                void *                          = nullptr
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_CACHE_AVAILABLE
        NoDiscard MaybeUnused extern auto destroyValidationCache (
                Type ( DeviceHandle ),
                Type ( ValidationCacheHandle ),
                Type ( AllocationCallbacks )    const *
        ) noexcept -> Type ( Result );
#endif


#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE
        NoDiscard MaybeUnused extern auto getDeviceSubpassShadingMaxWorkgroupSizeHuawei (
                Type ( DeviceHandle ),
                Type ( RenderPassHandle ),
                Type ( Extent2D )           *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto createComputePipelines (
                Type ( DeviceHandle ),
                Type ( PipelineCacheHandle ),
                cds :: uint32,
                Type ( ComputePipelineCreateInfo )  const *,
                Type ( AllocationCallbacks )        const *,
                Type ( PipelineHandle )                   *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto createGraphicsPipelines (
                Type ( DeviceHandle ),
                Type ( PipelineCacheHandle ),
                cds :: uint32,
                Type ( GraphicsPipelineCreateInfo ) const *,
                Type ( AllocationCallbacks )        const *,
                Type ( PipelineHandle )                   *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
        NoDiscard MaybeUnused extern auto createRayTracingPipelinesNVidia (
                Type ( DeviceHandle ),
                Type ( PipelineCacheHandle ),
                cds :: uint32,
                Type ( RayTracingPipelineCreateInfoNVidia ) const *,
                Type ( AllocationCallbacks )                const *,
                Type ( PipelineHandle )                           *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
        NoDiscard MaybeUnused extern auto createRayTracingPipelines (
                Type ( DeviceHandle ),
                Type ( DeferredOperationHandle ),
                Type ( PipelineCacheHandle ),
                cds :: uint32,
                Type ( RayTracingPipelineCreateInfo )       const *,
                Type ( AllocationCallbacks )                const *,
                Type ( PipelineHandle )                           *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
        NoDiscard MaybeUnused extern auto getRayTracingShaderGroupHandles (
                Type ( DeviceHandle ),
                Type ( PipelineHandle ),
                cds :: uint32,
                cds :: uint32,
                cds :: uint64,
                void *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
        NoDiscard MaybeUnused extern auto getRayTracingCaptureReplayShaderGroupHandles (
                Type ( DeviceHandle ),
                Type ( PipelineHandle ),
                cds :: uint32,
                cds :: uint32,
                cds :: uint64,
                void *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
        NoDiscard MaybeUnused extern auto compileDeferredNVidia (
                Type ( DeviceHandle ),
                Type ( PipelineHandle ),
                cds :: uint32
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
        NoDiscard MaybeUnused extern auto getRayTracingShaderGroupStackSize (
                Type ( DeviceHandle ),
                Type ( PipelineHandle ),
                cds :: uint32,
                Type ( ShaderGroupShader ),
                Type ( DeviceSize )         *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
        NoDiscard MaybeUnused extern auto commandBufferSetRayTracingPipelineStackSize (
                Type ( CommandBufferHandle ),
                cds :: uint32
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto destroyPipeline (
                Type ( DeviceHandle ),
                Type ( PipelineHandle ),
                Type ( AllocationCallbacks )    const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto createPipelineCache (
                Type ( DeviceHandle ),
                Type ( PipelineCacheCreateInfo )    const *,
                Type ( AllocationCallbacks )        const *,
                Type ( PipelineCacheHandle )              *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto mergePipelineCaches (
                Type ( DeviceHandle ),
                Type ( PipelineCacheHandle ),
                cds :: uint32,
                Type ( PipelineCacheHandle )  const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto getPipelineCacheData (
                Type ( DeviceHandle ),
                Type ( PipelineCacheHandle ),
                cds :: uint64                   *,
                void                            * = nullptr
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto destroyPipelineCache (
                Type ( DeviceHandle ),
                Type ( PipelineCacheHandle ),
                Type ( AllocationCallbacks )    const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto commandBufferBindPipeline (
                Type ( CommandBufferHandle ),
                Type ( PipelineBindPoint ),
                Type ( PipelineHandle )
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE
        NoDiscard MaybeUnused extern auto commandBufferBindPipelineShaderGroup (
                Type ( CommandBufferHandle ),
                Type ( PipelineBindPoint ),
                Type ( PipelineHandle ),
                cds :: uint32
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
        NoDiscard MaybeUnused extern auto getPipelineExecutableProperties (
                Type ( DeviceHandle ),
                Type ( PipelineInfo )                   const *,
                cds :: uint32                                 *,
                Type ( PipelineExecutableProperties )         *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
        NoDiscard MaybeUnused extern auto getPipelineExecutableStatistics (
                Type ( DeviceHandle ),
                Type ( PipelineExecutableInfo )        const *,
                cds :: uint32                                *,
                Type ( PipelineExecutableStatistic )         *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
        NoDiscard MaybeUnused extern auto getPipelineExecutableInternalRepresentations (
                Type ( DeviceHandle ),
                Type ( PipelineExecutableInfo )                     const *,
                cds :: uint32                                             *,
                Type ( PipelineExecutableInternalRepresentation )         *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_INFO_AVAILABLE
        NoDiscard MaybeUnused extern auto getShaderInfoAMD (
                Type ( DeviceHandle ),
                Type ( PipelineHandle ),
                Type ( ShaderStageFlag ),
                Type ( ShaderInfoTypeAMD ),
                cds :: uint64               *,
                void                        *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto getPhysicalDeviceMemoryProperties (
                Type ( PhysicalDeviceHandle ),
                Type ( PhysicalDeviceMemoryProperties ) *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
        NoDiscard MaybeUnused extern auto getPhysicalDeviceMemoryProperties (
                Type ( PhysicalDeviceHandle ),
                Type ( PhysicalDeviceMemoryProperties2 ) *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto allocateMemory (
                Type ( DeviceHandle ),
                Type ( MemoryAllocateInfo )     const *,
                Type ( AllocationCallbacks )    const *,
                Type ( DeviceMemoryHandle )           *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PAGEABLE_DEVICE_LOCAL_MEMORY_AVAILABLE
        NoDiscard MaybeUnused extern auto setDeviceMemoryPriority (
                Type ( DeviceHandle ),
                Type ( DeviceMemoryHandle ),
                float
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_WIN32_AVAILABLE
        NoDiscard MaybeUnused extern auto getMemoryWin32Handle (
                Type ( DeviceHandle ),
                Type ( MemoryGetWin32HandleInfo )   const *,
                HANDLE                                    *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_WIN32_AVAILABLE
        NoDiscard MaybeUnused extern auto getMemoryWin32HandleNVidia (
                Type ( DeviceHandle ),
                Type ( DeviceMemoryHandle ),
                Type ( ExternalMemoryHandleTypeFlagNVidia ),
                HANDLE                                    *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_WIN32_AVAILABLE
        NoDiscard MaybeUnused extern auto getMemoryWin32HandleProperties (
                Type ( DeviceHandle ),
                Type ( ExternalmemoryHandleTypeFlag ),
                HANDLE,
                Type ( MemoryWin32HandleProperties )    *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_FD_AVAILABLE
        NoDiscard MaybeUnused extern auto getMemoryFd (
                Type ( DeviceHandle ),
                Type ( MemoryGetFdInfo )    const *,
                int                               *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_FD_AVAILABLE
        NoDiscard MaybeUnused extern auto getMemoryFdProperties (
                Type ( DeviceHandle ),
                Type ( ExternalMemoryHandleTypeFlag ),
                int,
                Type ( MemoryFdProperties )             *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTERNAL_MEMORY_HOST_AVAILABLE
        NoDiscard MaybeUnused extern auto getMemoryHostPointerProperties (
                Type ( DeviceHandle ),
                Type ( ExternalMemoryHandleTypeFlag ),
                void                                    const *,
                Type ( MemoryHostPointerProperties )          *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_AVAILABLE
        NoDiscard MaybeUnused extern auto getMemoryAndroidHardwareBufferInfoAndroid (
                Type ( DeviceHandle ),
                Type ( MemoryGetAndroidHardwareBufferInfoAndroid )  const *,
                AHardwareBuffer                                          **
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_AVAILABLE
        NoDiscard MaybeUnused extern auto getAndroidHardwareBufferPropertiesAndroid (
                Type ( DeviceHandle ),
                AHardwareBuffer                                 const *,
                Type ( AndroidHardwareBufferPropertiesAndroid )       *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_RDMA_AVAILABLE
        NoDiscard MaybeUnused extern auto getMemoryRemoteAddressNVidia (
                Type ( DeviceHandle ),
                Type ( MemoryGetRemoteAddressInfoNVidia )   const *,
                Type ( RemoteAddressNVidia )                      *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_MEMORY_AVAILABLE
        NoDiscard MaybeUnused extern auto getMemoryZirconHandlePropertiesFuchsia (
                Type ( DeviceHandle ),
                Type ( ExternalMemoryHandleTypeFlag ),
                zx_handle_t,
                Type ( MemoryZirconHandlePropertiesFuchsia ) *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_MEMORY_AVAILABLE
        NoDiscard MaybeUnused extern auto getMemoryZirconHandleFuchsia (
                Type ( DeviceHandle ),
                Type ( MemoryGetZirconHandleInfoFuchsia )   const *,
                zx_handle_t                                       *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto freeMemory (
                Type ( DeviceHandle ),
                Type ( DeviceMemoryHandle ),
                Type ( AllocationCallbacks )    const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto mapMemory (
                Type ( DeviceHandle ),
                Type ( DeviceMemoryHandle ),
                Type ( DeviceSize ),
                Type ( DeviceSize ),
                Type ( MemoryMapFlags ),
                void                        **
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto flushMappedMemoryRanges (
                Type ( DeviceHandle ),
                cds :: uint32,
                Type ( MappedMemoryRange )  const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto invalidateMappedMemoryRanges (
                Type ( DeviceHandle ),
                cds :: uint32,
                Type ( MappedMemoryRange )  const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto unmapMemory (
                Type ( DeviceHandle ),
                Type ( DeviceMemoryHandle )
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto getDeviceMemoryCommitment (
                Type ( DeviceHandle ),
                Type ( DeviceMemoryHandle ),
                Type ( DeviceSize )         *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
        NoDiscard MaybeUnused extern auto getDeviceGroupPeerMemoryFeatures (
                Type ( DeviceHandle ),
                cds :: uint32,
                cds :: uint32,
                cds :: uint32,
                Type ( PeerMemoryFeatureFlags ) *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
        NoDiscard MaybeUnused extern auto getDeviceMemoryOpaqueCaptureAddress (
                Type ( DeviceHandle ),
                Type ( DeviceMemoryOpaqueCaptureAddressInfo )   const *,
                cds :: uint64                                         *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto createBuffer (
                Type ( DeviceHandle ),
                Type ( BufferCreateInfo )       const *,
                Type ( AllocationCallbacks )    const *,
                Type ( BufferHandle )                 *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto destroyBuffer (
                Type ( DeviceHandle ),
                Type ( BufferHandle ),
                Type ( AllocationCallbacks )    const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto createBufferView (
                Type ( DeviceHandle ),
                Type ( BufferViewCreateInfo )   const *,
                Type ( AllocationCallbacks )    const *,
                Type ( BufferViewHandle )             *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto destroyBufferView (
                Type ( DeviceHandle ),
                Type ( BufferViewHandle ),
                Type ( AllocationCallbacks )    const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto createImage (
                Type ( DeviceHandle ),
                Type ( ImageCreateInfo )        const *,
                Type ( AllocationCallbacks )    const *,
                Type ( ImageHandle )                  *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto getImageSubresourceLayout (
                Type ( DeviceHandle ),
                Type ( ImageHandle ),
                Type ( ImageSubresource )   const *,
                Type ( SubresourceLayout )        *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_DRM_FORMAT_MODIFIER_AVAILABLE
        NoDiscard MaybeUnused extern auto getImageDrmFormatModifierProperties (
                Type ( DeviceHandle ),
                Type ( ImageHandle ),
                Type ( ImageDrmFormatModifierProperties )   *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto destroyImage (
                Type ( DeviceHandle ),
                Type ( ImageHandle ),
                Type ( AllocationCallbacks )    const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
        NoDiscard MaybeUnused extern auto createAccelerationStructureNVidia (
                Type ( DeviceHandle ),
                Type ( AccelerationStructureCreateInfoNVidia )  const *,
                Type ( AllocationCallbacks )                    const *,
                Type ( AccelerationStructureHandleNVidia )            *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
        NoDiscard MaybeUnused extern auto createAccelerationStructure (
                Type ( DeviceHandle ),
                Type ( AccelerationStructureCreateInfo )        const *,
                Type ( AllocationCallbacks )                    const *,
                Type ( AccelerationStructureHandle )                  *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
        NoDiscard MaybeUnused extern auto getAccelerationStructureBuildSizes (
                Type ( DeviceHandle ),
                Type ( AccelerationStructureBuildType ),
                Type ( AccelerationStructureBuildGeometryInfo ) const *,
                cds :: uint32                                   const *,
                Type ( AccelerationStructureBuildSizesInfo )          *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
        NoDiscard MaybeUnused extern auto destroyAccelerationStructureNVidia (
                Type ( DeviceHandle ),
                Type ( AccelerationStructureHandleNVidia ),
                Type ( AllocationCallbacks )                    const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
        NoDiscard MaybeUnused extern auto destroyAccelerationStructure (
                Type ( DeviceHandle ),
                Type ( AccelerationStructureHandle ),
                Type ( AllocationCallbacks )                    const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
        NoDiscard MaybeUnused extern auto getAccelerationStructureMemoryRequirementsNVidia (
                Type ( DeviceHandle ),
                Type ( AccelerationStructureMemoryRequirementsInfoNVidia )  const *,
                Type ( MemoryRequirements2 )                                      *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
        NoDiscard MaybeUnused extern auto bindAccelerationStructureMemoryNVidia (
                Type ( DeviceHandle ),
                cds :: uint32,
                Type ( BindAccelerationStructureMemoryInfoNVidia )  const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
        NoDiscard MaybeUnused extern auto getAccelerationStructureHandleNVidia (
                Type ( DeviceHandle ),
                Type ( AccelerationStructureHandleNVidia ),
                cds :: uint64,
                void                                        *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
        NoDiscard MaybeUnused extern auto getAccelerationStructureDeviceAddress (
                Type ( DeviceHandle ),
                Type ( AccelerationStructureDeviceAddressInfo ) const *,
                Type ( DeviceAddress )                                *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto createSampler (
                Type ( DeviceHandle ),
                Type ( SamplerCreateInfo )      const *,
                Type ( AllocationCallbacks )    const *,
                Type ( SamplerHandle )                *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused extern auto destroySampler (
                Type ( DeviceHandle ),
                Type ( SamplerHandle ),
                Type ( AllocationCallbacks )    const *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
        NoDiscard MaybeUnused extern auto createSamplerYCBCRConversion (
                Type ( DeviceHandle ),
                Type ( SamplerYCBCRConversionCreateInfo )   const *,
                Type ( AllocationCallbacks )                const *,
                Type ( SamplerYCBCRConversionHandle )             *
        ) noexcept -> Type ( Result );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
        NoDiscard MaybeUnused extern auto destroySamplerYCBCRConversion (
                Type ( DeviceHandle ),
                Type ( SamplerYCBCRConversionHandle ),
                Type ( AllocationCallbacks )            const *
        ) noexcept -> Type ( Result );
#endif

//#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
//        NoDiscard MaybeUnused extern auto createDescriptorSetLayout (
//                Type ( DeviceHandle ),
//                Type ( DescriptorSetLayoutCreateInfo )  const *,
//                Type ( AllocationCallbacks )            const *,
//                Type ( DescriptorSetLayoutHandle )            *
//        ) noexcept -> Type ( Result );
//#endif

    } /// namespace vulkan

} /// namespace engine

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //__C_ENG_VULKAN_API_CALLS_HPP__

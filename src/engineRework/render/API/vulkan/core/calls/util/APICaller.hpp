//
// Created by loghin on 08.03.2022.
//

#ifndef __C_ENG_API_CALLER_HPP__ // NOLINT(llvm-header-guard)
#define __C_ENG_API_CALLER_HPP__ // NOLINT(llvm-header-guard)

#include <Logger.hpp>
#include <CDS/Mutex>
#include <CDS/LockGuard>
#include <CDS/HashSet>
#include <CDS/HashMap>
#include <calls/util/LastCreatedInstance.hpp>
#include <CDS/Warnings>
#include <VulkanCore.hpp>

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START HEADER
#include <ObjectMapping.hpp>

namespace engine :: vulkan {

    static class {
    private:
        template < typename FunctionType >
        struct APICall {
            FunctionType handle;
            cds :: Mutex lock;
        };

        VkInstance  mutable instanceHandleToBeUsed  = nullptr;
        VkDevice    mutable deviceHandleToBeUsed    = nullptr;

        cds :: HashMap < VkInstance, cds :: HashSet < cds :: String > > mutable instanceAvailableExtensions;
        cds :: HashMap < VkDevice,   cds :: HashSet < cds :: String > > mutable deviceAvailableExtensions;

        template < typename APICallerType >
        class Cleaner { // NOLINT(cppcoreguidelines-special-member-functions)
        private:
            APICallerType * pObject;

        public:
            explicit Cleaner ( APICallerType * pObject ) noexcept : pObject ( pObject ) {}
            ~Cleaner () noexcept {
                pObject->instanceHandleToBeUsed = nullptr;
                pObject->deviceHandleToBeUsed   = nullptr;
            }
        };

    public:
        auto fromInstance ( VkInstance handle = LastCreatedInstance :: acquire() ) const noexcept -> decltype ( * this ) & {
            this->instanceHandleToBeUsed = handle;
            return * this;
        }

        auto fromDevice ( VkDevice handle ) const noexcept -> decltype ( * this ) {
            this->deviceHandleToBeUsed = handle;
            return * this;
        }

        auto setInstanceExtensions (
                VkInstance                      instanceHandle,
                VkInstanceCreateInfo    const * pInstanceCreateInfo
        ) const noexcept -> void {
            this->instanceAvailableExtensions[instanceHandle] = cds :: HashSet < cds :: String > ();

            auto & set = this->instanceAvailableExtensions[instanceHandle];
            for ( cds :: uint32 i = 0U; i < pInstanceCreateInfo->enabledExtensionCount; ++ i ) {
                (void) set.insert ( pInstanceCreateInfo->ppEnabledExtensionNames[i] );
            }
        }

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkEnumerateInstanceVersion, INDEPENDENT, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCreateInstance, INDEPENDENT, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkGetDeviceProcAddr, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkEnumerateInstanceLayerProperties, INDEPENDENT, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkEnumerateDeviceLayerProperties, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkEnumerateInstanceExtensionProperties, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkEnumeratePhysicalDevices, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define CALL_POINT CALL ( vkEnumeratePhysicalDeviceGroups, INSTANCE_OR_KHR, EXTENSION ( VK_KHR_DEVICE_GROUP ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkEnumerateDeviceExtensionProperties, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCreateDevice, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkDestroyDevice, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkDestroyInstance, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkGetPhysicalDeviceProperties, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define CALL_POINT CALL ( vkGetPhysicalDeviceProperties2, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkGetPhysicalDeviceFeatures, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define CALL_POINT CALL ( vkGetPhysicalDeviceFeatures2, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkGetDeviceQueue, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define CALL_POINT CALL ( vkGetDeviceQueue2, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkGetPhysicalDeviceQueueFamilyProperties, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCreateImageView, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkDestroyImageView, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCreateCommandPool, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkDestroyCommandPool, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkResetCommandPool, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkAllocateCommandBuffers, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkResetCommandBuffer, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkFreeCommandBuffers, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkBeginCommandBuffer, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkEndCommandBuffer, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define CALL_POINT CALL ( vkTrimCommandPool, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkQueueSubmit, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdExecuteCommands, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
#define CALL_POINT CALL ( vkQueueSubmit2, INSTANCE_OR_KHR, EXTENSION ( VK_KHR_SYNCHRONIZATION_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
#define CALL_POINT CALL ( vkQueueSubmit2, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetDeviceMask, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCreateFence, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_WIN32_AVAILABLE
#define CALL_POINT CALL ( vkGetFenceWin32HandleKHR, INSTANCE, EXTENSION ( VK_KHR_EXTERNAL_FENCE_WIN32 ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_FD_AVAILABLE
#define CALL_POINT CALL ( vkGetFenceFdKHR, INSTANCE, EXTENSION ( VK_KHR_EXTERNAL_FENCE_FD ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkDestroyFence, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkGetFenceStatus, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkResetFences, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkWaitForFences, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define CALL_POINT CALL ( vkGetPhysicalDeviceQueueFamilyProperties2, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISPLAY_CONTROL_AVAILABLE
#define CALL_POINT CALL ( vkRegisterDeviceEventEXT, INSTANCE, EXTENSION ( VK_EXT_DISPLAY_CONTROL ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISPLAY_CONTROL_AVAILABLE
#define CALL_POINT CALL ( vkRegisterDisplayEventEXT, INSTANCE, EXTENSION ( VK_EXT_DISPLAY_CONTROL ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_WIN32_AVAILABLE
#define CALL_POINT CALL ( vkImportFenceWin32HandleKHR, INSTANCE, EXTENSION ( VK_KHR_EXTERNAL_FENCE_WIN32 ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_FD_AVAILABLE
#define CALL_POINT CALL ( vkImportFenceFdKHR, INSTANCE, EXTENSION ( VK_KHR_EXTERNAL_FENCE_FD ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCreateSemaphore, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_WIN32_AVAILABLE
#define CALL_POINT CALL ( vkGetSemaphoreWin32HandleKHR, INSTANCE, EXTENSION ( VK_KHR_EXTERNAL_SEMAPHORE_WIN32 ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_FD_AVAILABLE
#define CALL_POINT CALL ( vkGetSemaphoreFdKHR, INSTANCE, EXTENSION ( VK_KHR_EXTERNAL_FENCE_FD ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_SEMAPHORE_AVAILABLE
#define CALL_POINT CALL ( vkGetSemaphoreZirconHandleFUCHSIA, INSTANCE, EXTENSION ( VK_KHR_EXTERNAL_SEMAPHORE_FUCHSIA ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_WIN32_AVAILABLE
#define CALL_POINT CALL ( vkImportSemaphoreWin32HandleKHR, INSTANCE, EXTENSION ( VK_KHR_EXTERNAL_SEMAPHORE_WIN32 ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_FD_AVAILABLE
#define CALL_POINT CALL ( vkImportSemaphoreFdKHR, INSTANCE, EXTENSION ( VK_KHR_EXTERNAL_FENCE_FD ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_SEMAPHORE_AVAILABLE
#define CALL_POINT CALL ( vkImportSemaphoreZirconHandleFUCHSIA, INSTANCE, EXTENSION ( VK_KHR_EXTERNAL_SEMAPHORE_FUCHSIA ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkDestroySemaphore, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
#define CALL_POINT CALL ( vkGetSemaphoreCounterValue, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
#define CALL_POINT CALL ( vkWaitSemaphores, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
#define CALL_POINT CALL ( vkSignalSemaphore, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCreateEvent, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkDestroyEvent, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkGetEventStatus, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkSetEvent, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkResetEvent, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetEvent2, INSTANCE_OR_KHR, EXTENSION ( VK_KHR_SYNCHRONIZATION_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetEvent2, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetEvent, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
#define CALL_POINT CALL ( vkCmdResetEvent2, INSTANCE_OR_KHR, EXTENSION ( VK_KHR_SYNCHRONIZATION_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
#define CALL_POINT CALL ( vkCmdResetEvent2, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdResetEvent, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
#define CALL_POINT CALL ( vkCmdWaitEvents2, INSTANCE_OR_KHR, EXTENSION ( VK_KHR_SYNCHRONIZATION_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
#define CALL_POINT CALL ( vkCmdWaitEvents2, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdWaitEvents, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkQueueWaitIdle, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkDeviceWaitIdle, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE
#define CALL_POINT CALL ( vkCmdBeginRendering, INSTANCE_OR_KHR, EXTENSION ( VK_KHR_DYNAMIC_RENDERING ) )
#include <calls/util/APICallerGenerator.hpp>
#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
#define CALL_POINT CALL ( vkCmdBeginRendering, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE
#define CALL_POINT CALL ( vkCmdEndRendering, INSTANCE_OR_KHR, EXTENSION ( VK_KHR_DYNAMIC_RENDERING ) )
#include <calls/util/APICallerGenerator.hpp>
#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
#define CALL_POINT CALL ( vkCmdEndRendering, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCreateRenderPass, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkDestroyRenderPass, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
#define CALL_POINT CALL ( vkCreateRenderPass2, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCreateFramebuffer, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkDestroyFramebuffer, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdBeginRenderPass, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
#define CALL_POINT CALL ( vkCmdBeginRenderPass2, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkGetRenderAreaGranularity, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdNextSubpass, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
#define CALL_POINT CALL ( vkCmdNextSubpass2, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdEndRenderPass, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
#define CALL_POINT CALL ( vkCmdEndRenderPass2, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCreateShaderModule, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkDestroyShaderModule, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_2_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetPatchControlPointsEXT, INSTANCE, EXTENSION ( VK_EXT_EXTENDED_DYNAMIC_STATE_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE
#define CALL_POINT CALL ( vkGetPhysicalDeviceCooperativeMatrixPropertiesNV, INSTANCE, EXTENSION ( VK_NV_COOPERATIVE_MATRIX ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCreateComputePipelines, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE
#define CALL_POINT CALL ( vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI, INSTANCE, EXTENSION ( VK_HUAWEI_SUBPASS_SHADING ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCreateGraphicsPipelines, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
#define CALL_POINT CALL ( vkCreateRayTracingPipelinesNV, INSTANCE, EXTENSION ( VK_NV_RAY_TRACING ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
#define CALL_POINT CALL ( vkBindAccelerationStructureMemoryNV, INSTANCE, EXTENSION ( VK_NV_RAY_TRACING ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
#define CALL_POINT CALL ( vkCmdBuildAccelerationStructureNV, INSTANCE, EXTENSION ( VK_NV_RAY_TRACING ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
#define CALL_POINT CALL ( vkCmdCopyAccelerationStructureNV, INSTANCE, EXTENSION ( VK_NV_RAY_TRACING ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
#define CALL_POINT CALL ( vkCmdWriteAccelerationStructuresPropertiesNV, INSTANCE, EXTENSION ( VK_NV_RAY_TRACING ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
#define CALL_POINT CALL ( vkCmdTraceRaysNV, INSTANCE, EXTENSION ( VK_NV_RAY_TRACING ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
#define CALL_POINT CALL ( vkCreateAccelerationStructureNV, INSTANCE, EXTENSION ( VK_NV_RAY_TRACING ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
#define CALL_POINT CALL ( vkDestroyAccelerationStructureNV, INSTANCE, EXTENSION ( VK_NV_RAY_TRACING ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
#define CALL_POINT CALL ( vkGetAccelerationStructureHandleNV, INSTANCE, EXTENSION ( VK_NV_RAY_TRACING ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
#define CALL_POINT CALL ( vkGetAccelerationStructureMemoryRequirementsNV, INSTANCE, EXTENSION ( VK_NV_RAY_TRACING ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
#define CALL_POINT CALL ( vkGetRayTracingShaderGroupHandlesNV, INSTANCE, EXTENSION ( VK_NV_RAY_TRACING ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
#define CALL_POINT CALL ( vkCreateRayTracingPipelinesKHR, INSTANCE, EXTENSION ( VK_KHR_RAY_TRACING_PIPELINE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
#define CALL_POINT CALL ( vkGetRayTracingShaderGroupHandlesKHR, INSTANCE, EXTENSION ( VK_KHR_RAY_TRACING_PIPELINE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
#define CALL_POINT CALL ( vkGetRayTracingCaptureReplayShaderGroupHandlesKHR, INSTANCE, EXTENSION ( VK_KHR_RAY_TRACING_PIPELINE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
#define CALL_POINT CALL ( vkCompileDeferredNV, INSTANCE, EXTENSION ( VK_NV_RAY_TRACING ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
#define CALL_POINT CALL ( vkGetRayTracingShaderGroupStackSizeKHR, INSTANCE, EXTENSION ( VK_KHR_RAY_TRACING_PIPELINE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetRayTracingPipelineStackSizeKHR, INSTANCE, EXTENSION ( VK_KHR_RAY_TRACING_PIPELINE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkDestroyPipeline, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCreatePipelineCache, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkMergePipelineCaches, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkGetPipelineCacheData, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkDestroyPipelineCache, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdBindPipeline, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE
#define CALL_POINT CALL ( vkCmdBindPipelineShaderGroupNV, INSTANCE, EXTENSION ( VK_NV_DEVICE_GENERATED_COMMANDS ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE
#define CALL_POINT CALL ( vkCmdExecuteGeneratedCommandsNV, INSTANCE, EXTENSION ( VK_NV_DEVICE_GENERATED_COMMANDS ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE
#define CALL_POINT CALL ( vkCmdPreprocessGeneratedCommandsNV, INSTANCE, EXTENSION ( VK_NV_DEVICE_GENERATED_COMMANDS ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE
#define CALL_POINT CALL ( vkCreateIndirectCommandsLayoutNV, INSTANCE, EXTENSION ( VK_NV_DEVICE_GENERATED_COMMANDS ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE
#define CALL_POINT CALL ( vkDestroyIndirectCommandsLayoutNV, INSTANCE, EXTENSION ( VK_NV_DEVICE_GENERATED_COMMANDS ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE
#define CALL_POINT CALL ( vkGetGeneratedCommandsMemoryRequirementsNV, INSTANCE, EXTENSION ( VK_NV_DEVICE_GENERATED_COMMANDS ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
#define CALL_POINT CALL ( vkGetPipelineExecutablePropertiesKHR, INSTANCE, EXTENSION ( VK_KHR_PIPELINE_EXECUTABLE_PROPERTIES ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
#define CALL_POINT CALL ( vkGetPipelineExecutableStatisticsKHR, INSTANCE, EXTENSION ( VK_KHR_PIPELINE_EXECUTABLE_PROPERTIES ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
#define CALL_POINT CALL ( vkGetPipelineExecutableInternalRepresentationsKHR, INSTANCE, EXTENSION ( VK_KHR_PIPELINE_EXECUTABLE_PROPERTIES ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_INFO_AVAILABLE
#define CALL_POINT CALL ( vkGetShaderInfoAMD, INSTANCE, EXTENSION ( VK_AMD_SHADER_INFO ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkAllocateDescriptorSets, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkAllocateMemory, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkBindBufferMemory, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkBindImageMemory, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdBeginQuery, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdBindDescriptorSets, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdBindIndexBuffer, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdBindVertexBuffers, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdBlitImage, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdClearAttachments, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdClearColorImage, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdClearDepthStencilImage, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdCopyBuffer, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdCopyBufferToImage, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdCopyImage, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdCopyImageToBuffer, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdCopyQueryPoolResults, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdDispatch, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdDispatchIndirect, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdDraw, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdDrawIndexed, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdDrawIndexedIndirect, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdDrawIndirect, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdEndQuery, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdFillBuffer, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdPipelineBarrier, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdPushConstants, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdResetQueryPool, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdResolveImage, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetBlendConstants, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetDepthBias, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetDepthBounds, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetLineWidth, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetScissor, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetStencilCompareMask, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetStencilReference, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetStencilWriteMask, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetViewport, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdUpdateBuffer, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCmdWriteTimestamp, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCreateBuffer, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCreateBufferView, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCreateDescriptorPool, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCreateDescriptorSetLayout, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCreateImage, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCreatePipelineLayout, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCreateQueryPool, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkCreateSampler, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkDestroyBuffer, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkDestroyBufferView, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkDestroyDescriptorPool, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkDestroyDescriptorSetLayout, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkDestroyImage, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkDestroyPipelineLayout, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkDestroyQueryPool, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkDestroySampler, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkFlushMappedMemoryRanges, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkFreeDescriptorSets, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkFreeMemory, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkGetBufferMemoryRequirements, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkGetDeviceMemoryCommitment, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkGetImageMemoryRequirements, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkGetImageSparseMemoryRequirements, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkGetImageSubresourceLayout, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkGetQueryPoolResults, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkInvalidateMappedMemoryRanges, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkMapMemory, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkQueueBindSparse, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkResetDescriptorPool, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkUnmapMemory, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkUpdateDescriptorSets, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define CALL_POINT CALL ( vkBindBufferMemory2, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define CALL_POINT CALL ( vkBindImageMemory2, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define CALL_POINT CALL ( vkCmdDispatchBase, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define CALL_POINT CALL ( vkCreateDescriptorUpdateTemplate, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define CALL_POINT CALL ( vkCreateSamplerYcbcrConversion, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define CALL_POINT CALL ( vkDestroyDescriptorUpdateTemplate, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define CALL_POINT CALL ( vkDestroySamplerYcbcrConversion, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define CALL_POINT CALL ( vkGetBufferMemoryRequirements2, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define CALL_POINT CALL ( vkGetDescriptorSetLayoutSupport, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define CALL_POINT CALL ( vkGetDeviceGroupPeerMemoryFeatures, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define CALL_POINT CALL ( vkGetImageMemoryRequirements2, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define CALL_POINT CALL ( vkGetImageSparseMemoryRequirements2, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define CALL_POINT CALL ( vkUpdateDescriptorSetWithTemplate, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
#define CALL_POINT CALL ( vkCmdDrawIndexedIndirectCount, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
#define CALL_POINT CALL ( vkCmdDrawIndirectCount, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
#define CALL_POINT CALL ( vkGetBufferDeviceAddress, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
#define CALL_POINT CALL ( vkGetBufferOpaqueCaptureAddress, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
#define CALL_POINT CALL ( vkGetDeviceMemoryOpaqueCaptureAddress, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
#define CALL_POINT CALL ( vkResetQueryPool, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE
#define CALL_POINT CALL ( vkCmdBindVertexBuffers2, INSTANCE_OR_EXT, EXTENSION ( VK_EXT_EXTENDED_DYNAMIC_STATE ) )
#include <calls/util/APICallerGenerator.hpp>
#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
#define CALL_POINT CALL ( vkCmdBindVertexBuffers2, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetCullMode, INSTANCE_OR_EXT, EXTENSION ( VK_EXT_EXTENDED_DYNAMIC_STATE ) )
#include <calls/util/APICallerGenerator.hpp>
#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetCullMode, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetDepthBoundsTestEnable, INSTANCE_OR_EXT, EXTENSION ( VK_EXT_EXTENDED_DYNAMIC_STATE ) )
#include <calls/util/APICallerGenerator.hpp>
#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetDepthBoundsTestEnable, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetDepthCompareOp, INSTANCE_OR_EXT, EXTENSION ( VK_EXT_EXTENDED_DYNAMIC_STATE ) )
#include <calls/util/APICallerGenerator.hpp>
#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetDepthCompareOp, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetDepthTestEnable, INSTANCE_OR_EXT, EXTENSION ( VK_EXT_EXTENDED_DYNAMIC_STATE ) )
#include <calls/util/APICallerGenerator.hpp>
#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetDepthTestEnable, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetDepthWriteEnable, INSTANCE_OR_EXT, EXTENSION ( VK_EXT_EXTENDED_DYNAMIC_STATE ) )
#include <calls/util/APICallerGenerator.hpp>
#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetDepthWriteEnable, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetFrontFace, INSTANCE_OR_EXT, EXTENSION ( VK_EXT_EXTENDED_DYNAMIC_STATE ) )
#include <calls/util/APICallerGenerator.hpp>
#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetFrontFace, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetPrimitiveTopology, INSTANCE_OR_EXT, EXTENSION ( VK_EXT_EXTENDED_DYNAMIC_STATE ) )
#include <calls/util/APICallerGenerator.hpp>
#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetPrimitiveTopology, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetScissorWithCount, INSTANCE_OR_EXT, EXTENSION ( VK_EXT_EXTENDED_DYNAMIC_STATE ) )
#include <calls/util/APICallerGenerator.hpp>
#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetScissorWithCount, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetStencilOp, INSTANCE_OR_EXT, EXTENSION ( VK_EXT_EXTENDED_DYNAMIC_STATE ) )
#include <calls/util/APICallerGenerator.hpp>
#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetStencilOp, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetStencilTestEnable, INSTANCE_OR_EXT, EXTENSION ( VK_EXT_EXTENDED_DYNAMIC_STATE ) )
#include <calls/util/APICallerGenerator.hpp>
#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetStencilTestEnable, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetViewportWithCount, INSTANCE_OR_EXT, EXTENSION ( VK_EXT_EXTENDED_DYNAMIC_STATE ) )
#include <calls/util/APICallerGenerator.hpp>
#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetViewportWithCount, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
#define CALL_POINT CALL ( vkCmdBlitImage2, INSTANCE_OR_KHR, EXTENSION ( VK_KHR_COPY_COMMANDS_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
#define CALL_POINT CALL ( vkCmdBlitImage2, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
#define CALL_POINT CALL ( vkCmdCopyBuffer2, INSTANCE_OR_KHR, EXTENSION ( VK_KHR_COPY_COMMANDS_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
#define CALL_POINT CALL ( vkCmdCopyBuffer2, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
#define CALL_POINT CALL ( vkCmdCopyBufferToImage2, INSTANCE_OR_KHR, EXTENSION ( VK_KHR_COPY_COMMANDS_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
#define CALL_POINT CALL ( vkCmdCopyBufferToImage2, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
#define CALL_POINT CALL ( vkCmdCopyImage2, INSTANCE_OR_KHR, EXTENSION ( VK_KHR_COPY_COMMANDS_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
#define CALL_POINT CALL ( vkCmdCopyImage2, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
#define CALL_POINT CALL ( vkCmdCopyImageToBuffer2, INSTANCE_OR_KHR, EXTENSION ( VK_KHR_COPY_COMMANDS_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
#define CALL_POINT CALL ( vkCmdCopyImageToBuffer2, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
#define CALL_POINT CALL ( vkCmdResolveImage2, INSTANCE_OR_KHR, EXTENSION ( VK_KHR_COPY_COMMANDS_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
#define CALL_POINT CALL ( vkCmdResolveImage2, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
#define CALL_POINT CALL ( vkCmdPipelineBarrier2, INSTANCE_OR_KHR, EXTENSION ( VK_KHR_SYNCHRONIZATION_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
#define CALL_POINT CALL ( vkCmdPipelineBarrier2, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
#define CALL_POINT CALL ( vkCmdWriteTimestamp2, INSTANCE_OR_KHR, EXTENSION ( VK_KHR_SYNCHRONIZATION_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
#define CALL_POINT CALL ( vkCmdWriteTimestamp2, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_2_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetDepthBiasEnable, INSTANCE_OR_EXT, EXTENSION ( VK_EXT_EXTENDED_DYNAMIC_STATE_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetDepthBiasEnable, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_2_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetPrimitiveRestartEnable, INSTANCE_OR_EXT, EXTENSION ( VK_EXT_EXTENDED_DYNAMIC_STATE_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetPrimitiveRestartEnable, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_2_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetRasterizerDiscardEnable, INSTANCE_OR_EXT, EXTENSION ( VK_EXT_EXTENDED_DYNAMIC_STATE_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetRasterizerDiscardEnable, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE
#define CALL_POINT CALL ( vkCreatePrivateDataSlot, INSTANCE_OR_EXT, EXTENSION ( VK_EXT_PRIVATE_DATA ) )
#include <calls/util/APICallerGenerator.hpp>
#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
#define CALL_POINT CALL ( vkCreatePrivateDataSlot, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE
#define CALL_POINT CALL ( vkDestroyPrivateDataSlot, INSTANCE_OR_EXT, EXTENSION ( VK_EXT_PRIVATE_DATA ) )
#include <calls/util/APICallerGenerator.hpp>
#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
#define CALL_POINT CALL ( vkDestroyPrivateDataSlot, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE
#define CALL_POINT CALL ( vkGetPrivateData, INSTANCE_OR_EXT, EXTENSION ( VK_EXT_PRIVATE_DATA ) )
#include <calls/util/APICallerGenerator.hpp>
#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
#define CALL_POINT CALL ( vkGetPrivateData, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE
#define CALL_POINT CALL ( vkSetPrivateData, INSTANCE_OR_EXT, EXTENSION ( VK_EXT_PRIVATE_DATA ) )
#include <calls/util/APICallerGenerator.hpp>
#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
#define CALL_POINT CALL ( vkSetPrivateData, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE
#define CALL_POINT CALL ( vkGetDeviceBufferMemoryRequirements, INSTANCE_OR_KHR, EXTENSION ( VK_KHR_MAINTENANCE_4 ) )
#include <calls/util/APICallerGenerator.hpp>
#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
#define CALL_POINT CALL ( vkGetDeviceBufferMemoryRequirements, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE
#define CALL_POINT CALL ( vkGetDeviceImageMemoryRequirements, INSTANCE_OR_KHR, EXTENSION ( VK_KHR_MAINTENANCE_4 ) )
#include <calls/util/APICallerGenerator.hpp>
#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
#define CALL_POINT CALL ( vkGetDeviceImageMemoryRequirements, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE
#define CALL_POINT CALL ( vkGetDeviceImageSparseMemoryRequirements, INSTANCE_OR_KHR, EXTENSION ( VK_KHR_MAINTENANCE_4 ) )
#include <calls/util/APICallerGenerator.hpp>
#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
#define CALL_POINT CALL ( vkGetDeviceImageSparseMemoryRequirements, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_BUFFER_MARKER_AVAILABLE
#define CALL_POINT CALL ( vkCmdWriteBufferMarkerAMD, INSTANCE, EXTENSION ( VK_AMD_BUFFER_MARKER ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_DISPLAY_NATIVE_HDR_AVAILABLE
#define CALL_POINT CALL ( vkSetLocalDimmingAMD, INSTANCE, EXTENSION ( VK_AMD_DISPLAY_NATIVE_HDR ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_DRAW_INDIRECT_COUNT_AVAILABLE
#define CALL_POINT CALL ( vkCmdDrawIndexedIndirectCountAMD, INSTANCE, EXTENSION ( VK_AMD_DRAW_INDIRECT_COUNT ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_DRAW_INDIRECT_COUNT_AVAILABLE
#define CALL_POINT CALL ( vkCmdDrawIndirectCountAMD, INSTANCE, EXTENSION ( VK_AMD_DRAW_INDIRECT_COUNT ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_AVAILABLE
#define CALL_POINT CALL ( vkGetAndroidHardwareBufferPropertiesANDROID, INSTANCE, EXTENSION ( VK_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_AVAILABLE
#define CALL_POINT CALL ( vkGetMemoryAndroidHardwareBufferANDROID, INSTANCE, EXTENSION ( VK_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_BUFFER_DEVICE_ADDRESS_AVAILABLE
#define CALL_POINT CALL ( vkGetBufferDeviceAddressEXT, INSTANCE, EXTENSION ( VK_EXT_BUFFER_DEVICE_ADDRESS ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CALIBRATED_TIMESTAMPS_AVAILABLE
#define CALL_POINT CALL ( vkGetCalibratedTimestampsEXT, INSTANCE, EXTENSION ( VK_EXT_CALIBRATED_TIMESTAMPS ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_COLOR_WRITE_ENABLE_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetColorWriteEnableEXT, INSTANCE, EXTENSION ( VK_EXT_COLOR_WRITE_ENABLE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE
#define CALL_POINT CALL ( vkCmdBeginConditionalRenderingEXT, INSTANCE, EXTENSION ( VK_EXT_CONDITIONAL_RENDERING ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE
#define CALL_POINT CALL ( vkCmdEndConditionalRenderingEXT, INSTANCE, EXTENSION ( VK_EXT_CONDITIONAL_RENDERING ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_MARKER_AVAILABLE
#define CALL_POINT CALL ( vkCmdDebugMarkerBeginEXT, INSTANCE, EXTENSION ( VK_EXT_DEBUG_MARKER ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_MARKER_AVAILABLE
#define CALL_POINT CALL ( vkCmdDebugMarkerEndEXT, INSTANCE, EXTENSION ( VK_EXT_DEBUG_MARKER ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_MARKER_AVAILABLE
#define CALL_POINT CALL ( vkCmdDebugMarkerInsertEXT, INSTANCE, EXTENSION ( VK_EXT_DEBUG_MARKER ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_MARKER_AVAILABLE
#define CALL_POINT CALL ( vkDebugMarkerSetObjectNameEXT, INSTANCE, EXTENSION ( VK_EXT_DEBUG_MARKER ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_MARKER_AVAILABLE
#define CALL_POINT CALL ( vkDebugMarkerSetObjectTagEXT, INSTANCE, EXTENSION ( VK_EXT_DEBUG_MARKER ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISCARD_RECTANGLES_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetDiscardRectangleEXT, INSTANCE, EXTENSION ( VK_EXT_DISCARD_RECTANGLES ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISPLAY_CONTROL_AVAILABLE
#define CALL_POINT CALL ( vkDisplayPowerControlEXT, INSTANCE, EXTENSION ( VK_EXT_DISPLAY_CONTROL ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISPLAY_CONTROL_AVAILABLE
#define CALL_POINT CALL ( vkGetSwapchainCounterEXT, INSTANCE, EXTENSION ( VK_EXT_DISPLAY_CONTROL ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE
#define CALL_POINT CALL ( vkCmdBindVertexBuffers2EXT, INSTANCE, EXTENSION ( VK_EXT_EXTENDED_DYNAMIC_STATE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetCullModeEXT, INSTANCE, EXTENSION ( VK_EXT_EXTENDED_DYNAMIC_STATE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetDepthBoundsTestEnableEXT, INSTANCE, EXTENSION ( VK_EXT_EXTENDED_DYNAMIC_STATE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetDepthCompareOpEXT, INSTANCE, EXTENSION ( VK_EXT_EXTENDED_DYNAMIC_STATE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetDepthTestEnableEXT, INSTANCE, EXTENSION ( VK_EXT_EXTENDED_DYNAMIC_STATE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetDepthWriteEnableEXT, INSTANCE, EXTENSION ( VK_EXT_EXTENDED_DYNAMIC_STATE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetFrontFaceEXT, INSTANCE, EXTENSION ( VK_EXT_EXTENDED_DYNAMIC_STATE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetPrimitiveTopologyEXT, INSTANCE, EXTENSION ( VK_EXT_EXTENDED_DYNAMIC_STATE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetScissorWithCountEXT, INSTANCE, EXTENSION ( VK_EXT_EXTENDED_DYNAMIC_STATE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetStencilOpEXT, INSTANCE, EXTENSION ( VK_EXT_EXTENDED_DYNAMIC_STATE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetStencilTestEnableEXT, INSTANCE, EXTENSION ( VK_EXT_EXTENDED_DYNAMIC_STATE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetViewportWithCountEXT, INSTANCE, EXTENSION ( VK_EXT_EXTENDED_DYNAMIC_STATE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_2_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetDepthBiasEnableEXT, INSTANCE, EXTENSION ( VK_EXT_EXTENDED_DYNAMIC_STATE_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_2_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetLogicOpEXT, INSTANCE, EXTENSION ( VK_EXT_EXTENDED_DYNAMIC_STATE_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_2_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetPrimitiveRestartEnableEXT, INSTANCE, EXTENSION ( VK_EXT_EXTENDED_DYNAMIC_STATE_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_2_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetRasterizerDiscardEnableEXT, INSTANCE, EXTENSION ( VK_EXT_EXTENDED_DYNAMIC_STATE_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTERNAL_MEMORY_HOST_AVAILABLE
#define CALL_POINT CALL ( vkGetMemoryHostPointerPropertiesEXT, INSTANCE, EXTENSION ( VK_EXT_EXTERNAL_MEMORY_HOST ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FULL_SCREEN_EXCLUSIVE_AVAILABLE
#define CALL_POINT CALL ( vkAcquireFullScreenExclusiveModeEXT, INSTANCE, EXTENSION ( VK_EXT_FULL_SCREEN_EXCLUSIVE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FULL_SCREEN_EXCLUSIVE_AVAILABLE
#define CALL_POINT CALL ( vkReleaseFullScreenExclusiveModeEXT, INSTANCE, EXTENSION ( VK_EXT_FULL_SCREEN_EXCLUSIVE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_HDR_METADATA_AVAILABLE
#define CALL_POINT CALL ( vkSetHdrMetadataEXT, INSTANCE, EXTENSION ( VK_EXT_HDR_METADATA ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_HOST_QUERY_RESET_AVAILABLE
#define CALL_POINT CALL ( vkResetQueryPoolEXT, INSTANCE, EXTENSION ( VK_EXT_HOST_QUERY_RESET ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_DRM_FORMAT_MODIFIER_AVAILABLE
#define CALL_POINT CALL ( vkGetImageDrmFormatModifierPropertiesEXT, INSTANCE, EXTENSION ( VK_EXT_IMAGE_DRM_FORMAT_MODIFIER ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetLineStippleEXT, INSTANCE, EXTENSION ( VK_EXT_LINE_RASTERIZATION ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE
#define CALL_POINT CALL ( vkCmdDrawMultiEXT, INSTANCE, EXTENSION ( VK_EXT_MULTI_DRAW ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE
#define CALL_POINT CALL ( vkCmdDrawMultiIndexedEXT, INSTANCE, EXTENSION ( VK_EXT_MULTI_DRAW ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PAGEABLE_DEVICE_LOCAL_MEMORY_AVAILABLE
#define CALL_POINT CALL ( vkSetDeviceMemoryPriorityEXT, INSTANCE, EXTENSION ( VK_EXT_PAGEABLE_DEVICE_LOCAL_MEMORY ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE
#define CALL_POINT CALL ( vkCreatePrivateDataSlotEXT, INSTANCE, EXTENSION ( VK_EXT_PRIVATE_DATA ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE
#define CALL_POINT CALL ( vkDestroyPrivateDataSlotEXT, INSTANCE, EXTENSION ( VK_EXT_PRIVATE_DATA ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE
#define CALL_POINT CALL ( vkGetPrivateDataEXT, INSTANCE, EXTENSION ( VK_EXT_PRIVATE_DATA ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE
#define CALL_POINT CALL ( vkSetPrivateDataEXT, INSTANCE, EXTENSION ( VK_EXT_PRIVATE_DATA ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetSampleLocationsEXT, INSTANCE, EXTENSION ( VK_EXT_SAMPLE_LOCATIONS ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE
#define CALL_POINT CALL ( vkCmdBeginQueryIndexedEXT, INSTANCE, EXTENSION ( VK_EXT_TRANSFORM_FEEDBACK ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE
#define CALL_POINT CALL ( vkCmdBeginTransformFeedbackEXT, INSTANCE, EXTENSION ( VK_EXT_TRANSFORM_FEEDBACK ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE
#define CALL_POINT CALL ( vkCmdBindTransformFeedbackBuffersEXT, INSTANCE, EXTENSION ( VK_EXT_TRANSFORM_FEEDBACK ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE
#define CALL_POINT CALL ( vkCmdDrawIndirectByteCountEXT, INSTANCE, EXTENSION ( VK_EXT_TRANSFORM_FEEDBACK ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE
#define CALL_POINT CALL ( vkCmdEndQueryIndexedEXT, INSTANCE, EXTENSION ( VK_EXT_TRANSFORM_FEEDBACK ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE
#define CALL_POINT CALL ( vkCmdEndTransformFeedbackEXT, INSTANCE, EXTENSION ( VK_EXT_TRANSFORM_FEEDBACK ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_CACHE_AVAILABLE
#define CALL_POINT CALL ( vkCreateValidationCacheEXT, INSTANCE, EXTENSION ( VK_EXT_VALIDATION_CACHE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_CACHE_AVAILABLE
#define CALL_POINT CALL ( vkDestroyValidationCacheEXT, INSTANCE, EXTENSION ( VK_EXT_VALIDATION_CACHE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_CACHE_AVAILABLE
#define CALL_POINT CALL ( vkGetValidationCacheDataEXT, INSTANCE, EXTENSION ( VK_EXT_VALIDATION_CACHE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_CACHE_AVAILABLE
#define CALL_POINT CALL ( vkMergeValidationCachesEXT, INSTANCE, EXTENSION ( VK_EXT_VALIDATION_CACHE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_INPUT_DYNAMIC_STATE_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetVertexInputEXT, INSTANCE, EXTENSION ( VK_EXT_VERTEX_INPUT_DYNAMIC_STATE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_BUFFER_COLLECTION_AVAILABLE
#define CALL_POINT CALL ( vkCreateBufferCollectionFUCHSIA, INSTANCE, EXTENSION ( VK_FUCHSIA_BUFFER_COLLECTION ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_BUFFER_COLLECTION_AVAILABLE
#define CALL_POINT CALL ( vkDestroyBufferCollectionFUCHSIA, INSTANCE, EXTENSION ( VK_FUCHSIA_BUFFER_COLLECTION ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_BUFFER_COLLECTION_AVAILABLE
#define CALL_POINT CALL ( vkGetBufferCollectionPropertiesFUCHSIA, INSTANCE, EXTENSION ( VK_FUCHSIA_BUFFER_COLLECTION ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_BUFFER_COLLECTION_AVAILABLE
#define CALL_POINT CALL ( vkSetBufferCollectionBufferConstraintsFUCHSIA, INSTANCE, EXTENSION ( VK_FUCHSIA_BUFFER_COLLECTION ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_BUFFER_COLLECTION_AVAILABLE
#define CALL_POINT CALL ( vkSetBufferCollectionImageConstraintsFUCHSIA, INSTANCE, EXTENSION ( VK_FUCHSIA_BUFFER_COLLECTION ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_MEMORY_AVAILABLE
#define CALL_POINT CALL ( vkGetMemoryZirconHandleFUCHSIA, INSTANCE, EXTENSION ( VK_FUCHSIA_EXTERNAL_MEMORY ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_MEMORY_AVAILABLE
#define CALL_POINT CALL ( vkGetMemoryZirconHandlePropertiesFUCHSIA, INSTANCE, EXTENSION ( VK_FUCHSIA_EXTERNAL_MEMORY ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_SEMAPHORE_AVAILABLE
#define CALL_POINT CALL ( vkGetSemaphoreZirconHandleFUCHSIA, INSTANCE, EXTENSION ( VK_FUCHSIA_EXTERNAL_SEMAPHORE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_SEMAPHORE_AVAILABLE
#define CALL_POINT CALL ( vkImportSemaphoreZirconHandleFUCHSIA, INSTANCE, EXTENSION ( VK_FUCHSIA_EXTERNAL_SEMAPHORE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_DISPLAY_TIMING_AVAILABLE
#define CALL_POINT CALL ( vkGetPastPresentationTimingGOOGLE, INSTANCE, EXTENSION ( VK_GOOGLE_DISPLAY_TIMING ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_DISPLAY_TIMING_AVAILABLE
#define CALL_POINT CALL ( vkGetRefreshCycleDurationGOOGLE, INSTANCE, EXTENSION ( VK_GOOGLE_DISPLAY_TIMING ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_INVOCATION_MASK_AVAILABLE
#define CALL_POINT CALL ( vkCmdBindInvocationMaskHUAWEI, INSTANCE, EXTENSION ( VK_HUAWEI_INVOCATION_MASK ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE
#define CALL_POINT CALL ( vkCmdSubpassShadingHUAWEI, INSTANCE, EXTENSION ( VK_HUAWEI_SUBPASS_SHADING ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
#define CALL_POINT CALL ( vkAcquirePerformanceConfigurationINTEL, INSTANCE, EXTENSION ( VK_INTEL_PERFORMANCE_QUERY ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetPerformanceMarkerINTEL, INSTANCE, EXTENSION ( VK_INTEL_PERFORMANCE_QUERY ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetPerformanceOverrideINTEL, INSTANCE, EXTENSION ( VK_INTEL_PERFORMANCE_QUERY ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetPerformanceStreamMarkerINTEL, INSTANCE, EXTENSION ( VK_INTEL_PERFORMANCE_QUERY ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
#define CALL_POINT CALL ( vkGetPerformanceParameterINTEL, INSTANCE, EXTENSION ( VK_INTEL_PERFORMANCE_QUERY ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
#define CALL_POINT CALL ( vkInitializePerformanceApiINTEL, INSTANCE, EXTENSION ( VK_INTEL_PERFORMANCE_QUERY ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
#define CALL_POINT CALL ( vkQueueSetPerformanceConfigurationINTEL, INSTANCE, EXTENSION ( VK_INTEL_PERFORMANCE_QUERY ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
#define CALL_POINT CALL ( vkReleasePerformanceConfigurationINTEL, INSTANCE, EXTENSION ( VK_INTEL_PERFORMANCE_QUERY ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
#define CALL_POINT CALL ( vkUninitializePerformanceApiINTEL, INSTANCE, EXTENSION ( VK_INTEL_PERFORMANCE_QUERY ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
#define CALL_POINT CALL ( vkBuildAccelerationStructuresKHR, INSTANCE, EXTENSION ( VK_KHR_ACCELERATION_STRUCTURE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
#define CALL_POINT CALL ( vkCmdBuildAccelerationStructuresIndirectKHR, INSTANCE, EXTENSION ( VK_KHR_ACCELERATION_STRUCTURE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
#define CALL_POINT CALL ( vkCmdBuildAccelerationStructuresKHR, INSTANCE, EXTENSION ( VK_KHR_ACCELERATION_STRUCTURE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
#define CALL_POINT CALL ( vkCmdCopyAccelerationStructureKHR, INSTANCE, EXTENSION ( VK_KHR_ACCELERATION_STRUCTURE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
#define CALL_POINT CALL ( vkCmdCopyAccelerationStructureToMemoryKHR, INSTANCE, EXTENSION ( VK_KHR_ACCELERATION_STRUCTURE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
#define CALL_POINT CALL ( vkCmdCopyMemoryToAccelerationStructureKHR, INSTANCE, EXTENSION ( VK_KHR_ACCELERATION_STRUCTURE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
#define CALL_POINT CALL ( vkCmdWriteAccelerationStructuresPropertiesKHR, INSTANCE, EXTENSION ( VK_KHR_ACCELERATION_STRUCTURE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
#define CALL_POINT CALL ( vkCopyAccelerationStructureKHR, INSTANCE, EXTENSION ( VK_KHR_ACCELERATION_STRUCTURE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
#define CALL_POINT CALL ( vkCopyAccelerationStructureToMemoryKHR, INSTANCE, EXTENSION ( VK_KHR_ACCELERATION_STRUCTURE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
#define CALL_POINT CALL ( vkCopyMemoryToAccelerationStructureKHR, INSTANCE, EXTENSION ( VK_KHR_ACCELERATION_STRUCTURE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
#define CALL_POINT CALL ( vkCreateAccelerationStructureKHR, INSTANCE, EXTENSION ( VK_KHR_ACCELERATION_STRUCTURE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
#define CALL_POINT CALL ( vkDestroyAccelerationStructureKHR, INSTANCE, EXTENSION ( VK_KHR_ACCELERATION_STRUCTURE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
#define CALL_POINT CALL ( vkGetAccelerationStructureBuildSizesKHR, INSTANCE, EXTENSION ( VK_KHR_ACCELERATION_STRUCTURE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
#define CALL_POINT CALL ( vkGetAccelerationStructureDeviceAddressKHR, INSTANCE, EXTENSION ( VK_KHR_ACCELERATION_STRUCTURE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
#define CALL_POINT CALL ( vkGetDeviceAccelerationStructureCompatibilityKHR, INSTANCE, EXTENSION ( VK_KHR_ACCELERATION_STRUCTURE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
#define CALL_POINT CALL ( vkWriteAccelerationStructuresPropertiesKHR, INSTANCE, EXTENSION ( VK_KHR_ACCELERATION_STRUCTURE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_BIND_MEMORY_2_AVAILABLE
#define CALL_POINT CALL ( vkBindBufferMemory2KHR, INSTANCE, EXTENSION ( VK_KHR_BIND_MEMORY_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_BIND_MEMORY_2_AVAILABLE
#define CALL_POINT CALL ( vkBindImageMemory2KHR, INSTANCE, EXTENSION ( VK_KHR_BIND_MEMORY_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_BUFFER_DEVICE_ADDRESS_AVAILABLE
#define CALL_POINT CALL ( vkGetBufferDeviceAddressKHR, INSTANCE, EXTENSION ( VK_KHR_BUFFER_DEVICE_ADDRESS ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_BUFFER_DEVICE_ADDRESS_AVAILABLE
#define CALL_POINT CALL ( vkGetBufferOpaqueCaptureAddressKHR, INSTANCE, EXTENSION ( VK_KHR_BUFFER_DEVICE_ADDRESS ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_BUFFER_DEVICE_ADDRESS_AVAILABLE
#define CALL_POINT CALL ( vkGetDeviceMemoryOpaqueCaptureAddressKHR, INSTANCE, EXTENSION ( VK_KHR_BUFFER_DEVICE_ADDRESS ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
#define CALL_POINT CALL ( vkCmdBlitImage2KHR, INSTANCE, EXTENSION ( VK_KHR_COPY_COMMANDS_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
#define CALL_POINT CALL ( vkCmdCopyBuffer2KHR, INSTANCE, EXTENSION ( VK_KHR_COPY_COMMANDS_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
#define CALL_POINT CALL ( vkCmdCopyBufferToImage2KHR, INSTANCE, EXTENSION ( VK_KHR_COPY_COMMANDS_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
#define CALL_POINT CALL ( vkCmdCopyImage2KHR, INSTANCE, EXTENSION ( VK_KHR_COPY_COMMANDS_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
#define CALL_POINT CALL ( vkCmdCopyImageToBuffer2KHR, INSTANCE, EXTENSION ( VK_KHR_COPY_COMMANDS_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
#define CALL_POINT CALL ( vkCmdResolveImage2KHR, INSTANCE, EXTENSION ( VK_KHR_COPY_COMMANDS_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_CREATE_RENDER_PASS_2_AVAILABLE
#define CALL_POINT CALL ( vkCmdBeginRenderPass2KHR, INSTANCE, EXTENSION ( VK_KHR_CREATE_RENDERPASS_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_CREATE_RENDER_PASS_2_AVAILABLE
#define CALL_POINT CALL ( vkCmdEndRenderPass2KHR, INSTANCE, EXTENSION ( VK_KHR_CREATE_RENDERPASS_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_CREATE_RENDER_PASS_2_AVAILABLE
#define CALL_POINT CALL ( vkCmdNextSubpass2KHR, INSTANCE, EXTENSION ( VK_KHR_CREATE_RENDERPASS_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_CREATE_RENDER_PASS_2_AVAILABLE
#define CALL_POINT CALL ( vkCreateRenderPass2KHR, INSTANCE, EXTENSION ( VK_KHR_CREATE_RENDERPASS_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DEFERRED_HOST_OPERATIONS_AVAILABLE
#define CALL_POINT CALL ( vkCreateDeferredOperationKHR, INSTANCE, EXTENSION ( VK_KHR_DEFERRED_HOST_OPERATIONS ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DEFERRED_HOST_OPERATIONS_AVAILABLE
#define CALL_POINT CALL ( vkDeferredOperationJoinKHR, INSTANCE, EXTENSION ( VK_KHR_DEFERRED_HOST_OPERATIONS ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DEFERRED_HOST_OPERATIONS_AVAILABLE
#define CALL_POINT CALL ( vkDestroyDeferredOperationKHR, INSTANCE, EXTENSION ( VK_KHR_DEFERRED_HOST_OPERATIONS ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DEFERRED_HOST_OPERATIONS_AVAILABLE
#define CALL_POINT CALL ( vkGetDeferredOperationMaxConcurrencyKHR, INSTANCE, EXTENSION ( VK_KHR_DEFERRED_HOST_OPERATIONS ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DEFERRED_HOST_OPERATIONS_AVAILABLE
#define CALL_POINT CALL ( vkGetDeferredOperationResultKHR, INSTANCE, EXTENSION ( VK_KHR_DEFERRED_HOST_OPERATIONS ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DESCRIPTOR_UPDATE_TEMPLATE_AVAILABLE
#define CALL_POINT CALL ( vkCreateDescriptorUpdateTemplateKHR, INSTANCE, EXTENSION ( VK_KHR_DESCRIPTOR_UPDATE_TEMPLATE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DESCRIPTOR_UPDATE_TEMPLATE_AVAILABLE
#define CALL_POINT CALL ( vkDestroyDescriptorUpdateTemplateKHR, INSTANCE, EXTENSION ( VK_KHR_DESCRIPTOR_UPDATE_TEMPLATE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DESCRIPTOR_UPDATE_TEMPLATE_AVAILABLE
#define CALL_POINT CALL ( vkUpdateDescriptorSetWithTemplateKHR, INSTANCE, EXTENSION ( VK_KHR_DESCRIPTOR_UPDATE_TEMPLATE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DEVICE_GROUP_AVAILABLE
#define CALL_POINT CALL ( vkCmdDispatchBaseKHR, INSTANCE, EXTENSION ( VK_KHR_DEVICE_GROUP ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DEVICE_GROUP_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetDeviceMaskKHR, INSTANCE, EXTENSION ( VK_KHR_DEVICE_GROUP ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DEVICE_GROUP_AVAILABLE
#define CALL_POINT CALL ( vkGetDeviceGroupPeerMemoryFeaturesKHR, INSTANCE, EXTENSION ( VK_KHR_DEVICE_GROUP ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DISPLAY_SWAP_CHAIN_AVAILABLE
#define CALL_POINT CALL ( vkCreateSharedSwapchainsKHR, INSTANCE, EXTENSION ( VK_KHR_DISPLAY_SWAPCHAIN ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DRAW_INDIRECT_COUNT_AVAILABLE
#define CALL_POINT CALL ( vkCmdDrawIndexedIndirectCountKHR, INSTANCE, EXTENSION ( VK_KHR_DRAW_INDIRECT_COUNT ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DRAW_INDIRECT_COUNT_AVAILABLE
#define CALL_POINT CALL ( vkCmdDrawIndirectCountKHR, INSTANCE, EXTENSION ( VK_KHR_DRAW_INDIRECT_COUNT ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE
#define CALL_POINT CALL ( vkCmdBeginRenderingKHR, INSTANCE, EXTENSION ( VK_KHR_DYNAMIC_RENDERING ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE
#define CALL_POINT CALL ( vkCmdEndRenderingKHR, INSTANCE, EXTENSION ( VK_KHR_DYNAMIC_RENDERING ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_FD_AVAILABLE
#define CALL_POINT CALL ( vkGetMemoryFdKHR, INSTANCE, EXTENSION ( VK_KHR_EXTERNAL_MEMORY_FD ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_FD_AVAILABLE
#define CALL_POINT CALL ( vkGetMemoryFdPropertiesKHR, INSTANCE, EXTENSION ( VK_KHR_EXTERNAL_MEMORY_FD ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_WIN32_AVAILABLE
#define CALL_POINT CALL ( vkGetMemoryWin32HandleKHR, INSTANCE, EXTENSION ( VK_KHR_EXTERNAL_MEMORY_WIN32 ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_WIN32_AVAILABLE
#define CALL_POINT CALL ( vkGetMemoryWin32HandlePropertiesKHR, INSTANCE, EXTENSION ( VK_KHR_EXTERNAL_MEMORY_WIN32 ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetFragmentShadingRateKHR, INSTANCE, EXTENSION ( VK_KHR_FRAGMENT_SHADING_RATE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_GET_MEMORY_REQUIREMENTS_2_AVAILABLE
#define CALL_POINT CALL ( vkGetBufferMemoryRequirements2KHR, INSTANCE, EXTENSION ( VK_KHR_GET_MEMORY_REQUIREMENTS_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_GET_MEMORY_REQUIREMENTS_2_AVAILABLE
#define CALL_POINT CALL ( vkGetImageMemoryRequirements2KHR, INSTANCE, EXTENSION ( VK_KHR_GET_MEMORY_REQUIREMENTS_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_GET_MEMORY_REQUIREMENTS_2_AVAILABLE
#define CALL_POINT CALL ( vkGetImageSparseMemoryRequirements2KHR, INSTANCE, EXTENSION ( VK_KHR_GET_MEMORY_REQUIREMENTS_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_AVAILABLE
#define CALL_POINT CALL ( vkTrimCommandPoolKHR, INSTANCE, EXTENSION ( VK_KHR_MAINTENANCE_1 ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_3_AVAILABLE
#define CALL_POINT CALL ( vkGetDescriptorSetLayoutSupportKHR, INSTANCE, EXTENSION ( VK_KHR_MAINTENANCE_3 ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE
#define CALL_POINT CALL ( vkGetDeviceBufferMemoryRequirementsKHR, INSTANCE, EXTENSION ( VK_KHR_MAINTENANCE_4 ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE
#define CALL_POINT CALL ( vkGetDeviceImageMemoryRequirementsKHR, INSTANCE, EXTENSION ( VK_KHR_MAINTENANCE_4 ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE
#define CALL_POINT CALL ( vkGetDeviceImageSparseMemoryRequirementsKHR, INSTANCE, EXTENSION ( VK_KHR_MAINTENANCE_4 ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
#define CALL_POINT CALL ( vkAcquireProfilingLockKHR, INSTANCE, EXTENSION ( VK_KHR_PERFORMANCE_QUERY ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
#define CALL_POINT CALL ( vkReleaseProfilingLockKHR, INSTANCE, EXTENSION ( VK_KHR_PERFORMANCE_QUERY ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_WAIT_AVAILABLE
#define CALL_POINT CALL ( vkWaitForPresentKHR, INSTANCE, EXTENSION ( VK_KHR_PRESENT_WAIT ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PUSH_DESCRIPTOR_AVAILABLE
#define CALL_POINT CALL ( vkCmdPushDescriptorSetKHR, INSTANCE, EXTENSION ( VK_KHR_PUSH_DESCRIPTOR ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
#define CALL_POINT CALL ( vkCmdTraceRaysIndirectKHR, INSTANCE, EXTENSION ( VK_KHR_RAY_TRACING_PIPELINE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
#define CALL_POINT CALL ( vkCmdTraceRaysKHR, INSTANCE, EXTENSION ( VK_KHR_RAY_TRACING_PIPELINE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SAMPLER_YCBCR_CONVERSION_AVAILABLE
#define CALL_POINT CALL ( vkCreateSamplerYcbcrConversionKHR, INSTANCE, EXTENSION ( VK_KHR_SAMPLER_YCBCR_CONVERSION ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SAMPLER_YCBCR_CONVERSION_AVAILABLE
#define CALL_POINT CALL ( vkDestroySamplerYcbcrConversionKHR, INSTANCE, EXTENSION ( VK_KHR_SAMPLER_YCBCR_CONVERSION ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHARED_PRESENTABLE_IMAGE_AVAILABLE
#define CALL_POINT CALL ( vkGetSwapchainStatusKHR, INSTANCE, EXTENSION ( VK_KHR_SHARED_PRESENTABLE_IMAGE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE
#define CALL_POINT CALL ( vkAcquireNextImageKHR, INSTANCE, EXTENSION ( VK_KHR_SWAPCHAIN ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE
#define CALL_POINT CALL ( vkQueuePresentKHR, INSTANCE, EXTENSION ( VK_KHR_SWAPCHAIN ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
#define CALL_POINT CALL ( vkCmdPipelineBarrier2KHR, INSTANCE, EXTENSION ( VK_KHR_SYNCHRONIZATION_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
#define CALL_POINT CALL ( vkCmdResetEvent2KHR, INSTANCE, EXTENSION ( VK_KHR_SYNCHRONIZATION_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetEvent2KHR, INSTANCE, EXTENSION ( VK_KHR_SYNCHRONIZATION_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
#define CALL_POINT CALL ( vkCmdWaitEvents2KHR, INSTANCE, EXTENSION ( VK_KHR_SYNCHRONIZATION_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
#define CALL_POINT CALL ( vkCmdWriteTimestamp2KHR, INSTANCE, EXTENSION ( VK_KHR_SYNCHRONIZATION_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
#define CALL_POINT CALL ( vkQueueSubmit2KHR, INSTANCE, EXTENSION ( VK_KHR_SYNCHRONIZATION_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_TIMELINE_SEMAPHORE_AVAILABLE
#define CALL_POINT CALL ( vkGetSemaphoreCounterValueKHR, INSTANCE, EXTENSION ( VK_KHR_TIMELINE_SEMAPHORE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_TIMELINE_SEMAPHORE_AVAILABLE
#define CALL_POINT CALL ( vkSignalSemaphoreKHR, INSTANCE, EXTENSION ( VK_KHR_TIMELINE_SEMAPHORE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_TIMELINE_SEMAPHORE_AVAILABLE
#define CALL_POINT CALL ( vkWaitSemaphoresKHR, INSTANCE, EXTENSION ( VK_KHR_TIMELINE_SEMAPHORE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_DECODE_QUEUE_AVAILABLE
#define CALL_POINT CALL ( vkCmdDecodeVideoKHR, INSTANCE, EXTENSION ( VK_KHR_VIDEO_DECODE_QUEUE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_ENCODE_QUEUE_AVAILABLE
#define CALL_POINT CALL ( vkCmdEncodeVideoKHR, INSTANCE, EXTENSION ( VK_KHR_VIDEO_ENCODE_QUEUE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE
#define CALL_POINT CALL ( vkBindVideoSessionMemoryKHR, INSTANCE, EXTENSION ( VK_KHR_VIDEO_QUEUE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE
#define CALL_POINT CALL ( vkCmdBeginVideoCodingKHR, INSTANCE, EXTENSION ( VK_KHR_VIDEO_QUEUE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE
#define CALL_POINT CALL ( vkCmdControlVideoCodingKHR, INSTANCE, EXTENSION ( VK_KHR_VIDEO_QUEUE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE
#define CALL_POINT CALL ( vkCmdEndVideoCodingKHR, INSTANCE, EXTENSION ( VK_KHR_VIDEO_QUEUE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE
#define CALL_POINT CALL ( vkCreateVideoSessionKHR, INSTANCE, EXTENSION ( VK_KHR_VIDEO_QUEUE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE
#define CALL_POINT CALL ( vkCreateVideoSessionParametersKHR, INSTANCE, EXTENSION ( VK_KHR_VIDEO_QUEUE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE
#define CALL_POINT CALL ( vkDestroyVideoSessionKHR, INSTANCE, EXTENSION ( VK_KHR_VIDEO_QUEUE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE
#define CALL_POINT CALL ( vkDestroyVideoSessionParametersKHR, INSTANCE, EXTENSION ( VK_KHR_VIDEO_QUEUE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE
#define CALL_POINT CALL ( vkGetVideoSessionMemoryRequirementsKHR, INSTANCE, EXTENSION ( VK_KHR_VIDEO_QUEUE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE
#define CALL_POINT CALL ( vkUpdateVideoSessionParametersKHR, INSTANCE, EXTENSION ( VK_KHR_VIDEO_QUEUE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_BINARY_IMPORT_AVAILABLE
#define CALL_POINT CALL ( vkCmdCuLaunchKernelNVX, INSTANCE, EXTENSION ( VK_NVX_BINARY_IMPORT ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_BINARY_IMPORT_AVAILABLE
#define CALL_POINT CALL ( vkCreateCuFunctionNVX, INSTANCE, EXTENSION ( VK_NVX_BINARY_IMPORT ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_BINARY_IMPORT_AVAILABLE
#define CALL_POINT CALL ( vkCreateCuModuleNVX, INSTANCE, EXTENSION ( VK_NVX_BINARY_IMPORT ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_BINARY_IMPORT_AVAILABLE
#define CALL_POINT CALL ( vkDestroyCuFunctionNVX, INSTANCE, EXTENSION ( VK_NVX_BINARY_IMPORT ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_BINARY_IMPORT_AVAILABLE
#define CALL_POINT CALL ( vkDestroyCuModuleNVX, INSTANCE, EXTENSION ( VK_NVX_BINARY_IMPORT ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_IMAGE_VIEW_HANDLE_AVAILABLE
#define CALL_POINT CALL ( vkGetImageViewAddressNVX, INSTANCE, EXTENSION ( VK_NVX_IMAGE_VIEW_HANDLE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_IMAGE_VIEW_HANDLE_AVAILABLE
#define CALL_POINT CALL ( vkGetImageViewHandleNVX, INSTANCE, EXTENSION ( VK_NVX_IMAGE_VIEW_HANDLE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CLIP_SPACE_W_SCALING_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetViewportWScalingNV, INSTANCE, EXTENSION ( VK_NV_CLIP_SPACE_W_SCALING ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTIC_CHECKPOINTS_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetCheckpointNV, INSTANCE, EXTENSION ( VK_NV_DEVICE_DIAGNOSTIC_CHECKPOINTS ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTIC_CHECKPOINTS_AVAILABLE
#define CALL_POINT CALL ( vkGetQueueCheckpointDataNV, INSTANCE, EXTENSION ( VK_NV_DEVICE_DIAGNOSTIC_CHECKPOINTS ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_RDMA_AVAILABLE
#define CALL_POINT CALL ( vkGetMemoryRemoteAddressNV, INSTANCE, EXTENSION ( VK_NV_EXTERNAL_MEMORY_RDMA ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_WIN32_AVAILABLE
#define CALL_POINT CALL ( vkGetMemoryWin32HandleNV, INSTANCE, EXTENSION ( VK_NV_EXTERNAL_MEMORY_WIN32 ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetFragmentShadingRateEnumNV, INSTANCE, EXTENSION ( VK_NV_FRAGMENT_SHADING_RATE_ENUMS ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE
#define CALL_POINT CALL ( vkCmdDrawMeshTasksIndirectCountNV, INSTANCE, EXTENSION ( VK_NV_MESH_SHADER ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE
#define CALL_POINT CALL ( vkCmdDrawMeshTasksIndirectNV, INSTANCE, EXTENSION ( VK_NV_MESH_SHADER ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE
#define CALL_POINT CALL ( vkCmdDrawMeshTasksNV, INSTANCE, EXTENSION ( VK_NV_MESH_SHADER ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE
#define CALL_POINT CALL ( vkDestroySurfaceKHR, INSTANCE, EXTENSION ( VK_KHR_SURFACE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE
#define CALL_POINT CALL ( vkGetPhysicalDeviceSurfaceSupportKHR, INSTANCE, EXTENSION ( VK_KHR_SURFACE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE
#define CALL_POINT CALL ( vkGetPhysicalDeviceSurfaceCapabilitiesKHR, INSTANCE, EXTENSION ( VK_KHR_SURFACE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE
#define CALL_POINT CALL ( vkGetPhysicalDeviceSurfaceFormatsKHR, INSTANCE, EXTENSION ( VK_KHR_SURFACE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE
#define CALL_POINT CALL ( vkGetPhysicalDeviceSurfacePresentModesKHR, INSTANCE, EXTENSION ( VK_KHR_SURFACE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE
#define CALL_POINT CALL ( vkCreateSwapchainKHR, INSTANCE, EXTENSION ( VK_KHR_SWAPCHAIN ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE
#define CALL_POINT CALL ( vkDestroySwapchainKHR, INSTANCE, EXTENSION ( VK_KHR_SWAPCHAIN ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE
#define CALL_POINT CALL ( vkGetSwapchainImagesKHR, INSTANCE, EXTENSION ( VK_KHR_SWAPCHAIN ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISPLAY_SURFACE_COUNTER_AVAILABLE
#define CALL_POINT CALL ( vkGetPhysicalDeviceSurfaceCapabilities2EXT, INSTANCE, EXTENSION ( VK_EXT_DISPLAY_SURFACE_COUNTER ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_GET_SURFACE_CAPABILITIES_AVAILABLE
#define CALL_POINT CALL ( vkGetPhysicalDeviceSurfaceFormats2KHR, INSTANCE, EXTENSION ( VK_KHR_GET_SURFACE_CAPABILITIES_2 ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FULL_SCREEN_EXCLUSIVE_AVAILABLE
#define CALL_POINT CALL ( vkGetPhysicalDeviceSurfacePresentModes2EXT, INSTANCE, EXTENSION ( VK_EXT_FULL_SCREEN_EXCLUSIVE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_UTILS_AVAILABLE
#define CALL_POINT CALL ( vkCreateDebugUtilsMessengerEXT, INSTANCE, EXTENSION ( VK_EXT_DEBUG_UTILS ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_UTILS_AVAILABLE
#define CALL_POINT CALL ( vkDestroyDebugUtilsMessengerEXT, INSTANCE, EXTENSION ( VK_EXT_DEBUG_UTILS ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
#define CALL_POINT CALL ( vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR, INSTANCE, EXTENSION ( VK_KHR_PERFORMANCE_QUERY ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SCISSOR_EXCLUSIVE_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetExclusiveScissorNV, INSTANCE, EXTENSION ( VK_NV_SCISSOR_EXCLUSIVE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE
#define CALL_POINT CALL ( vkCmdBindShadingRateImageNV, INSTANCE, EXTENSION ( VK_NV_SHADING_RATE_IMAGE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetCoarseSampleOrderNV, INSTANCE, EXTENSION ( VK_NV_SHADING_RATE_IMAGE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE
#define CALL_POINT CALL ( vkCmdSetViewportShadingRatePaletteNV, INSTANCE, EXTENSION ( VK_NV_SHADING_RATE_IMAGE ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define CALL_POINT CALL ( vkGetPhysicalDeviceMemoryProperties, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define CALL_POINT CALL ( vkGetPhysicalDeviceMemoryProperties2, INSTANCE, NO_EXTENSION )
#include <calls/util/APICallerGenerator.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PUSH_DESCRIPTOR_AVAILABLE
#define CALL_POINT CALL ( vkCmdPushDescriptorSetWithTemplateKHR, INSTANCE, EXTENSION ( VK_KHR_PUSH_DESCRIPTOR ) )
#include <calls/util/APICallerGenerator.hpp>
#endif

    public:
        inline auto acquireHandlesForDevice (
                engine :: vulkan :: Type ( DeviceHandle )               handle,
                engine :: vulkan :: Type ( DeviceCreateInfo )   const * pCreateInfo
        ) const noexcept -> void {

#define load(_fName)                                                                        \
            (void) this->vkGetDeviceProcAddr (                                              \
                    reinterpret_cast < void (**) () > ( & this->_fName ## Handle.handle ),  \
                    handle,                                                                 \
                    # _fName                                                                \
            );

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
            load(vkAllocateCommandBuffers)
            load(vkAllocateDescriptorSets)
            load(vkAllocateMemory)
            load(vkBeginCommandBuffer)
            load(vkBindBufferMemory)
            load(vkBindImageMemory)
            load(vkCmdBeginQuery)
            load(vkCmdBeginRenderPass)
            load(vkCmdBindDescriptorSets)
            load(vkCmdBindIndexBuffer)
            load(vkCmdBindPipeline)
            load(vkCmdBindVertexBuffers)
            load(vkCmdBlitImage)
            load(vkCmdClearAttachments)
            load(vkCmdClearColorImage)
            load(vkCmdClearDepthStencilImage)
            load(vkCmdCopyBuffer)
            load(vkCmdCopyBufferToImage)
            load(vkCmdCopyImage)
            load(vkCmdCopyImageToBuffer)
            load(vkCmdCopyQueryPoolResults)
            load(vkCmdDispatch)
            load(vkCmdDispatchIndirect)
            load(vkCmdDraw)
            load(vkCmdDrawIndexed)
            load(vkCmdDrawIndexedIndirect)
            load(vkCmdDrawIndirect)
            load(vkCmdEndQuery)
            load(vkCmdEndRenderPass)
            load(vkCmdExecuteCommands)
            load(vkCmdFillBuffer)
            load(vkCmdNextSubpass)
            load(vkCmdPipelineBarrier)
            load(vkCmdPushConstants)
            load(vkCmdResetEvent)
            load(vkCmdResetQueryPool)
            load(vkCmdResolveImage)
            load(vkCmdSetBlendConstants)
            load(vkCmdSetDepthBias)
            load(vkCmdSetDepthBounds)
            load(vkCmdSetEvent)
            load(vkCmdSetLineWidth)
            load(vkCmdSetScissor)
            load(vkCmdSetStencilCompareMask)
            load(vkCmdSetStencilReference)
            load(vkCmdSetStencilWriteMask)
            load(vkCmdSetViewport)
            load(vkCmdUpdateBuffer)
            load(vkCmdWaitEvents)
            load(vkCmdWriteTimestamp)
            load(vkCreateBuffer)
            load(vkCreateBufferView)
            load(vkCreateCommandPool)
            load(vkCreateComputePipelines)
            load(vkCreateDescriptorPool)
            load(vkCreateDescriptorSetLayout)
            load(vkCreateEvent)
            load(vkCreateFence)
            load(vkCreateFramebuffer)
            load(vkCreateGraphicsPipelines)
            load(vkCreateImage)
            load(vkCreateImageView)
            load(vkCreatePipelineCache)
            load(vkCreatePipelineLayout)
            load(vkCreateQueryPool)
            load(vkCreateRenderPass)
            load(vkCreateSampler)
            load(vkCreateSemaphore)
            load(vkCreateShaderModule)
            load(vkDestroyBuffer)
            load(vkDestroyBufferView)
            load(vkDestroyCommandPool)
            load(vkDestroyDescriptorPool)
            load(vkDestroyDescriptorSetLayout)
            load(vkDestroyDevice)
            load(vkDestroyEvent)
            load(vkDestroyFence)
            load(vkDestroyFramebuffer)
            load(vkDestroyImage)
            load(vkDestroyImageView)
            load(vkDestroyPipeline)
            load(vkDestroyPipelineCache)
            load(vkDestroyPipelineLayout)
            load(vkDestroyQueryPool)
            load(vkDestroyRenderPass)
            load(vkDestroySampler)
            load(vkDestroySemaphore)
            load(vkDestroyShaderModule)
            load(vkDeviceWaitIdle)
            load(vkEndCommandBuffer)
            load(vkFlushMappedMemoryRanges)
            load(vkFreeCommandBuffers)
            load(vkFreeDescriptorSets)
            load(vkFreeMemory)
            load(vkGetBufferMemoryRequirements)
            load(vkGetDeviceMemoryCommitment)
            load(vkGetDeviceQueue)
            load(vkGetEventStatus)
            load(vkGetFenceStatus)
            load(vkGetImageMemoryRequirements)
            load(vkGetImageSparseMemoryRequirements)
            load(vkGetImageSubresourceLayout)
            load(vkGetPipelineCacheData)
            load(vkGetQueryPoolResults)
            load(vkGetRenderAreaGranularity)
            load(vkInvalidateMappedMemoryRanges)
            load(vkMapMemory)
            load(vkMergePipelineCaches)
            load(vkQueueBindSparse)
            load(vkQueueSubmit)
            load(vkQueueWaitIdle)
            load(vkResetCommandBuffer)
            load(vkResetCommandPool)
            load(vkResetDescriptorPool)
            load(vkResetEvent)
            load(vkResetFences)
            load(vkSetEvent)
            load(vkUnmapMemory)
            load(vkUpdateDescriptorSets)
            load(vkWaitForFences)
#endif
#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
            load(vkBindBufferMemory2)
            load(vkBindImageMemory2)
            load(vkCmdDispatchBase)
            load(vkCmdSetDeviceMask)
            load(vkCreateDescriptorUpdateTemplate)
            load(vkCreateSamplerYcbcrConversion)
            load(vkDestroyDescriptorUpdateTemplate)
            load(vkDestroySamplerYcbcrConversion)
            load(vkGetBufferMemoryRequirements2)
            load(vkGetDescriptorSetLayoutSupport)
            load(vkGetDeviceGroupPeerMemoryFeatures)
            load(vkGetDeviceQueue2)
            load(vkGetImageMemoryRequirements2)
            load(vkGetImageSparseMemoryRequirements2)
            load(vkTrimCommandPool)
            load(vkUpdateDescriptorSetWithTemplate)
#endif
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
            load(vkCmdBeginRenderPass2)
            load(vkCmdDrawIndexedIndirectCount)
            load(vkCmdDrawIndirectCount)
            load(vkCmdEndRenderPass2)
            load(vkCmdNextSubpass2)
            load(vkCreateRenderPass2)
            load(vkGetBufferDeviceAddress)
            load(vkGetBufferOpaqueCaptureAddress)
            load(vkGetDeviceMemoryOpaqueCaptureAddress)
            load(vkGetSemaphoreCounterValue)
            load(vkResetQueryPool)
            load(vkSignalSemaphore)
            load(vkWaitSemaphores)
#endif
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
            load(vkCmdBeginRendering)
            load(vkCmdBindVertexBuffers2)
            load(vkCmdBlitImage2)
            load(vkCmdCopyBuffer2)
            load(vkCmdCopyBufferToImage2)
            load(vkCmdCopyImage2)
            load(vkCmdCopyImageToBuffer2)
            load(vkCmdEndRendering)
            load(vkCmdPipelineBarrier2)
            load(vkCmdResetEvent2)
            load(vkCmdResolveImage2)
            load(vkCmdSetCullMode)
            load(vkCmdSetDepthBiasEnable)
            load(vkCmdSetDepthBoundsTestEnable)
            load(vkCmdSetDepthCompareOp)
            load(vkCmdSetDepthTestEnable)
            load(vkCmdSetDepthWriteEnable)
            load(vkCmdSetEvent2)
            load(vkCmdSetFrontFace)
            load(vkCmdSetPrimitiveRestartEnable)
            load(vkCmdSetPrimitiveTopology)
            load(vkCmdSetRasterizerDiscardEnable)
            load(vkCmdSetScissorWithCount)
            load(vkCmdSetStencilOp)
            load(vkCmdSetStencilTestEnable)
            load(vkCmdSetViewportWithCount)
            load(vkCmdWaitEvents2)
            load(vkCmdWriteTimestamp2)
            load(vkCreatePrivateDataSlot)
            load(vkDestroyPrivateDataSlot)
            load(vkGetDeviceBufferMemoryRequirements)
            load(vkGetDeviceImageMemoryRequirements)
            load(vkGetDeviceImageSparseMemoryRequirements)
            load(vkGetPrivateData)
            load(vkQueueSubmit2)
            load(vkSetPrivateData)
#endif

            for ( cds :: uint32 i = 0U; i < pCreateInfo->enabledExtensionCount; ++ i ) {

#if __C_ENG_VULKAN_API_EXTENSION_AMD_BUFFER_MARKER_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_AMD_BUFFER_MARKER_EXTENSION_NAME ) == 0 ) {
                    load(vkCmdWriteBufferMarkerAMD)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_AMD_DISPLAY_NATIVE_HDR_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_AMD_DISPLAY_NATIVE_HDR_EXTENSION_NAME ) == 0 ) {
                    load(vkSetLocalDimmingAMD)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_AMD_DRAW_INDIRECT_COUNT_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_AMD_DRAW_INDIRECT_COUNT_EXTENSION_NAME ) == 0 ) {
                    load(vkCmdDrawIndexedIndirectCountAMD)
                    load(vkCmdDrawIndirectCountAMD)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_INFO_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_AMD_SHADER_INFO_EXTENSION_NAME ) == 0 ) {
                    load(vkGetShaderInfoAMD)
                }
#endif
#if __C_ENG_VULKAN_API_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_AMD_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_EXTENSION_NAME ) == 0 ) {
                    load(vkGetAndroidHardwareBufferPropertiesANDROID)
                    load(vkGetMemoryAndroidHardwareBufferANDROID)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_BUFFER_DEVICE_ADDRESS_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_EXT_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME ) == 0 ) {
                    load(vkGetBufferDeviceAddressEXT)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_CALIBRATED_TIMESTAMPS_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_EXT_CALIBRATED_TIMESTAMPS_EXTENSION_NAME ) == 0 ) {
                    load(vkGetCalibratedTimestampsEXT)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_COLOR_WRITE_ENABLE_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_EXT_COLOR_WRITE_ENABLE_EXTENSION_NAME ) == 0 ) {
                    load(vkCmdSetColorWriteEnableEXT)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_EXT_CONDITIONAL_RENDERING_EXTENSION_NAME ) == 0 ) {
                    load(vkCmdBeginConditionalRenderingEXT)
                    load(vkCmdEndConditionalRenderingEXT)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_MARKER_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_EXT_DEBUG_MARKER_EXTENSION_NAME ) == 0 ) {
                    load(vkCmdDebugMarkerBeginEXT)
                    load(vkCmdDebugMarkerEndEXT)
                    load(vkCmdDebugMarkerInsertEXT)
                    load(vkDebugMarkerSetObjectNameEXT)
                    load(vkDebugMarkerSetObjectTagEXT)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_DISCARD_RECTANGLES_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_EXT_DISCARD_RECTANGLES_EXTENSION_NAME ) == 0 ) {
                    load(vkCmdSetDiscardRectangleEXT)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_DISPLAY_CONTROL_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_EXT_DISPLAY_CONTROL_EXTENSION_NAME ) == 0 ) {
                    load(vkDisplayPowerControlEXT)
                    load(vkGetSwapchainCounterEXT)
                    load(vkRegisterDeviceEventEXT)
                    load(vkRegisterDisplayEventEXT)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_EXT_EXTENDED_DYNAMIC_STATE_EXTENSION_NAME ) == 0 ) {
                    load(vkCmdBindVertexBuffers2EXT)
                    load(vkCmdSetCullModeEXT)
                    load(vkCmdSetDepthBoundsTestEnableEXT)
                    load(vkCmdSetDepthCompareOpEXT)
                    load(vkCmdSetDepthTestEnableEXT)
                    load(vkCmdSetDepthWriteEnableEXT)
                    load(vkCmdSetFrontFaceEXT)
                    load(vkCmdSetPrimitiveTopologyEXT)
                    load(vkCmdSetScissorWithCountEXT)
                    load(vkCmdSetStencilOpEXT)
                    load(vkCmdSetStencilTestEnableEXT)
                    load(vkCmdSetViewportWithCountEXT)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_2_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_EXT_EXTENDED_DYNAMIC_STATE_2_EXTENSION_NAME ) == 0 ) {
                    load(vkCmdSetDepthBiasEnableEXT)
                    load(vkCmdSetLogicOpEXT)
                    load(vkCmdSetPatchControlPointsEXT)
                    load(vkCmdSetPrimitiveRestartEnableEXT)
                    load(vkCmdSetRasterizerDiscardEnableEXT)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_EXTERNAL_MEMORY_HOST_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_EXT_EXTERNAL_MEMORY_HOST_EXTENSION_NAME ) == 0 ) {
                    load(vkGetMemoryHostPointerPropertiesEXT)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_FULL_SCREEN_EXCLUSIVE_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_EXT_FULL_SCREEN_EXCLUSIVE_EXTENSION_NAME ) == 0 ) {
                    load(vkAcquireFullScreenExclusiveModeEXT)
                    load(vkReleaseFullScreenExclusiveModeEXT)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_HDR_METADATA_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_EXT_HDR_METADATA_EXTENSION_NAME ) == 0 ) {
                    load(vkSetHdrMetadataEXT)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_HOST_QUERY_RESET_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_EXT_HOST_QUERY_RESET_EXTENSION_NAME ) == 0 ) {
                    load(vkResetQueryPoolEXT)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_DRM_FORMAT_MODIFIER_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_EXT_IMAGE_DRM_FORMAT_MODIFIER_EXTENSION_NAME ) == 0 ) {
                    load(vkGetImageDrmFormatModifierPropertiesEXT)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_EXT_LINE_RASTERIZATION_EXTENSION_NAME ) == 0 ) {
                    load(vkCmdSetLineStippleEXT)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_EXT_MULTI_DRAW_EXTENSION_NAME ) == 0 ) {
                    load(vkCmdDrawMultiEXT)
                    load(vkCmdDrawMultiIndexedEXT)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_PAGEABLE_DEVICE_LOCAL_MEMORY_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_EXT_PAGEABLE_DEVICE_LOCAL_MEMORY_EXTENSION_NAME ) == 0 ) {
                    load(vkSetDeviceMemoryPriorityEXT)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_EXT_PRIVATE_DATA_EXTENSION_NAME ) == 0 ) {
                    load(vkCreatePrivateDataSlotEXT)
                    load(vkDestroyPrivateDataSlotEXT)
                    load(vkGetPrivateDataEXT)
                    load(vkSetPrivateDataEXT)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_EXT_SAMPLE_LOCATIONS_EXTENSION_NAME ) == 0 ) {
                    load(vkCmdSetSampleLocationsEXT)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_EXT_TRANSFORM_FEEDBACK_EXTENSION_NAME ) == 0 ) {
                    load(vkCmdBeginQueryIndexedEXT)
                    load(vkCmdBeginTransformFeedbackEXT)
                    load(vkCmdBindTransformFeedbackBuffersEXT)
                    load(vkCmdDrawIndirectByteCountEXT)
                    load(vkCmdEndQueryIndexedEXT)
                    load(vkCmdEndTransformFeedbackEXT)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_CACHE_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_EXT_VALIDATION_CACHE_EXTENSION_NAME ) == 0 ) {
                    load(vkCreateValidationCacheEXT)
                    load(vkDestroyValidationCacheEXT)
                    load(vkGetValidationCacheDataEXT)
                    load(vkMergeValidationCachesEXT)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_INPUT_DYNAMIC_STATE_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_EXT_VERTEX_INPUT_DYNAMIC_STATE_EXTENSION_NAME ) == 0 ) {
                    load(vkCmdSetVertexInputEXT)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_BUFFER_COLLECTION_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_FUCHSIA_BUFFER_COLLECTION_EXTENSION_NAME ) == 0 ) {
                    load(vkCreateBufferCollectionFUCHSIA)
                    load(vkDestroyBufferCollectionFUCHSIA)
                    load(vkGetBufferCollectionPropertiesFUCHSIA)
                    load(vkSetBufferCollectionBufferConstraintsFUCHSIA)
                    load(vkSetBufferCollectionImageConstraintsFUCHSIA)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_MEMORY_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_FUCHSIA_EXTERNAL_SEMAPHORE_EXTENSION_NAME ) == 0 ) {
                    load(vkGetMemoryZirconHandleFUCHSIA)
                    load(vkGetMemoryZirconHandlePropertiesFUCHSIA)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_SEMAPHORE_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_FUCHSIA_EXTERNAL_SEMAPHORE_EXTENSION_NAME ) == 0 ) {
                    load(vkGetSemaphoreZirconHandleFUCHSIA)
                    load(vkImportSemaphoreZirconHandleFUCHSIA)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_DISPLAY_TIMING_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_GOOGLE_DISPLAY_TIMING_EXTENSION_NAME ) == 0 ) {
                    load(vkGetPastPresentationTimingGOOGLE)
                    load(vkGetRefreshCycleDurationGOOGLE)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_INVOCATION_MASK_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_HUAWEI_INVOCATION_MASK_EXTENSION_NAME ) == 0 ) {
                    load(vkCmdBindInvocationMaskHUAWEI)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_HUAWEI_SUBPASS_SHADING_EXTENSION_NAME ) == 0 ) {
                    load(vkCmdSubpassShadingHUAWEI)
                    load(vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_INTEL_PERFORMANCE_QUERY_EXTENSION_NAME ) == 0 ) {
                    load(vkAcquirePerformanceConfigurationINTEL)
                    load(vkCmdSetPerformanceMarkerINTEL)
                    load(vkCmdSetPerformanceOverrideINTEL)
                    load(vkCmdSetPerformanceStreamMarkerINTEL)
                    load(vkGetPerformanceParameterINTEL)
                    load(vkInitializePerformanceApiINTEL)
                    load(vkQueueSetPerformanceConfigurationINTEL)
                    load(vkReleasePerformanceConfigurationINTEL)
                    load(vkUninitializePerformanceApiINTEL)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_KHR_ACCELERATION_STRUCTURE_EXTENSION_NAME ) == 0 ) {
                    load(vkBuildAccelerationStructuresKHR)
                    load(vkCmdBuildAccelerationStructuresIndirectKHR)
                    load(vkCmdBuildAccelerationStructuresKHR)
                    load(vkCmdCopyAccelerationStructureKHR)
                    load(vkCmdCopyAccelerationStructureToMemoryKHR)
                    load(vkCmdCopyMemoryToAccelerationStructureKHR)
                    load(vkCmdWriteAccelerationStructuresPropertiesKHR)
                    load(vkCopyAccelerationStructureKHR)
                    load(vkCopyAccelerationStructureToMemoryKHR)
                    load(vkCopyMemoryToAccelerationStructureKHR)
                    load(vkCreateAccelerationStructureKHR)
                    load(vkDestroyAccelerationStructureKHR)
                    load(vkGetAccelerationStructureBuildSizesKHR)
                    load(vkGetAccelerationStructureDeviceAddressKHR)
                    load(vkGetDeviceAccelerationStructureCompatibilityKHR)
                    load(vkWriteAccelerationStructuresPropertiesKHR)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_BIND_MEMORY_2_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_KHR_BIND_MEMORY_2_EXTENSION_NAME ) == 0 ) {
                    load(vkBindBufferMemory2KHR)
                    load(vkBindImageMemory2KHR)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_BUFFER_DEVICE_ADDRESS_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_KHR_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME ) == 0 ) {
                    load(vkGetBufferDeviceAddressKHR)
                    load(vkGetBufferOpaqueCaptureAddressKHR)
                    load(vkGetDeviceMemoryOpaqueCaptureAddressKHR)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_KHR_COPY_COMMANDS_2_EXTENSION_NAME ) == 0 ) {
                    load(vkCmdBlitImage2KHR)
                    load(vkCmdCopyBuffer2KHR)
                    load(vkCmdCopyBufferToImage2KHR)
                    load(vkCmdCopyImage2KHR)
                    load(vkCmdCopyImageToBuffer2KHR)
                    load(vkCmdResolveImage2KHR)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_CREATE_RENDER_PASS_2_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_KHR_CREATE_RENDERPASS_2_EXTENSION_NAME ) == 0 ) {
                    load(vkCmdBeginRenderPass2KHR)
                    load(vkCmdEndRenderPass2KHR)
                    load(vkCmdNextSubpass2KHR)
                    load(vkCreateRenderPass2KHR)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DEFERRED_HOST_OPERATIONS_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_KHR_DEFERRED_HOST_OPERATIONS_EXTENSION_NAME ) == 0 ) {
                    load(vkCreateDeferredOperationKHR)
                    load(vkDeferredOperationJoinKHR)
                    load(vkDestroyDeferredOperationKHR)
                    load(vkGetDeferredOperationMaxConcurrencyKHR)
                    load(vkGetDeferredOperationResultKHR)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DESCRIPTOR_UPDATE_TEMPLATE_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_KHR_DESCRIPTOR_UPDATE_TEMPLATE_EXTENSION_NAME ) == 0 ) {
                    load(vkCreateDescriptorUpdateTemplateKHR)
                    load(vkDestroyDescriptorUpdateTemplateKHR)
                    load(vkUpdateDescriptorSetWithTemplateKHR)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DEVICE_GROUP_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_KHR_DEVICE_GROUP_EXTENSION_NAME ) == 0 ) {
                    load(vkCmdDispatchBaseKHR)
                    load(vkCmdSetDeviceMaskKHR)
                    load(vkGetDeviceGroupPeerMemoryFeaturesKHR)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DISPLAY_SWAP_CHAIN_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_KHR_DISPLAY_SWAPCHAIN_EXTENSION_NAME ) == 0 ) {
                    load(vkCreateSharedSwapchainsKHR)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DRAW_INDIRECT_COUNT_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_KHR_DRAW_INDIRECT_COUNT_EXTENSION_NAME ) == 0 ) {
                    load(vkCmdDrawIndexedIndirectCountKHR)
                    load(vkCmdDrawIndirectCountKHR)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_KHR_DYNAMIC_RENDERING_EXTENSION_NAME ) == 0 ) {
                    load(vkCmdBeginRenderingKHR)
                    load(vkCmdEndRenderingKHR)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_FD_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_KHR_EXTERNAL_FENCE_FD_EXTENSION_NAME ) == 0 ) {
                    load(vkGetFenceFdKHR)
                    load(vkImportFenceFdKHR)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_WIN32_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_KHR_EXTERNAL_FENCE_WIN32_EXTENSION_NAME ) == 0 ) {
                    load(vkGetFenceWin32HandleKHR)
                    load(vkImportFenceWin32HandleKHR)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_FD_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_KHR_EXTERNAL_MEMORY_FD_EXTENSION_NAME ) == 0 ) {
                    load(vkGetMemoryFdKHR)
                    load(vkGetMemoryFdPropertiesKHR)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_WIN32_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_KHR_EXTERNAL_MEMORY_WIN32_EXTENSION_NAME ) == 0 ) {
                    load(vkGetMemoryWin32HandleKHR)
                    load(vkGetMemoryWin32HandlePropertiesKHR)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_FD_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_KHR_EXTERNAL_SEMAPHORE_FD_EXTENSION_NAME ) == 0 ) {
                    load(vkGetSemaphoreFdKHR)
                    load(vkImportSemaphoreFdKHR)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_WIN32_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_KHR_EXTERNAL_SEMAPHORE_WIN32_EXTENSION_NAME ) == 0 ) {
                    load(vkGetSemaphoreWin32HandleKHR)
                    load(vkImportSemaphoreWin32HandleKHR)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_KHR_FRAGMENT_SHADING_RATE_EXTENSION_NAME ) == 0 ) {
                    load(vkCmdSetFragmentShadingRateKHR)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_GET_MEMORY_REQUIREMENTS_2_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_KHR_GET_MEMORY_REQUIREMENTS_2_EXTENSION_NAME ) == 0 ) {
                    load(vkGetBufferMemoryRequirements2KHR)
                    load(vkGetImageMemoryRequirements2KHR)
                    load(vkGetImageSparseMemoryRequirements2KHR)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_KHR_MAINTENANCE_1_EXTENSION_NAME ) == 0 ) {
                    load(vkTrimCommandPoolKHR)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_3_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_KHR_MAINTENANCE_3_EXTENSION_NAME ) == 0 ) {
                    load(vkGetDescriptorSetLayoutSupportKHR)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_KHR_MAINTENANCE_4_EXTENSION_NAME ) == 0 ) {
                    load(vkGetDeviceBufferMemoryRequirementsKHR)
                    load(vkGetDeviceImageMemoryRequirementsKHR)
                    load(vkGetDeviceImageSparseMemoryRequirementsKHR)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_KHR_PERFORMANCE_QUERY_EXTENSION_NAME ) == 0 ) {
                    load(vkAcquireProfilingLockKHR)
                    load(vkReleaseProfilingLockKHR)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_KHR_PIPELINE_EXECUTABLE_PROPERTIES_EXTENSION_NAME ) == 0 ) {
                    load(vkGetPipelineExecutableInternalRepresentationsKHR)
                    load(vkGetPipelineExecutablePropertiesKHR)
                    load(vkGetPipelineExecutableStatisticsKHR)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_WAIT_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_KHR_PRESENT_WAIT_EXTENSION_NAME ) == 0 ) {
                    load(vkWaitForPresentKHR)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PUSH_DESCRIPTOR_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_KHR_PUSH_DESCRIPTOR_EXTENSION_NAME ) == 0 ) {
                    load(vkCmdPushDescriptorSetKHR)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_KHR_RAY_TRACING_PIPELINE_EXTENSION_NAME ) == 0 ) {
                    load(vkCmdSetRayTracingPipelineStackSizeKHR)
                    load(vkCmdTraceRaysIndirectKHR)
                    load(vkCmdTraceRaysKHR)
                    load(vkCreateRayTracingPipelinesKHR)
                    load(vkGetRayTracingCaptureReplayShaderGroupHandlesKHR)
                    load(vkGetRayTracingShaderGroupHandlesKHR)
                    load(vkGetRayTracingShaderGroupStackSizeKHR)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SAMPLER_YCBCR_CONVERSION_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_KHR_SAMPLER_YCBCR_CONVERSION_EXTENSION_NAME ) == 0 ) {
                    load(vkCreateSamplerYcbcrConversionKHR)
                    load(vkDestroySamplerYcbcrConversionKHR)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHARED_PRESENTABLE_IMAGE_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_KHR_SHARED_PRESENTABLE_IMAGE_EXTENSION_NAME ) == 0 ) {
                    load(vkGetSwapchainStatusKHR)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_KHR_SWAPCHAIN_EXTENSION_NAME ) == 0 ) {
                    load(vkAcquireNextImageKHR)
                    load(vkCreateSwapchainKHR)
                    load(vkDestroySwapchainKHR)
                    load(vkGetSwapchainImagesKHR)
                    load(vkQueuePresentKHR)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_KHR_SYNCHRONIZATION_2_EXTENSION_NAME ) == 0 ) {
                    load(vkCmdPipelineBarrier2KHR)
                    load(vkCmdResetEvent2KHR)
                    load(vkCmdSetEvent2KHR)
                    load(vkCmdWaitEvents2KHR)
                    load(vkCmdWriteTimestamp2KHR)
                    load(vkQueueSubmit2KHR)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_TIMELINE_SEMAPHORE_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_KHR_TIMELINE_SEMAPHORE_EXTENSION_NAME ) == 0 ) {
                    load(vkGetSemaphoreCounterValueKHR)
                    load(vkSignalSemaphoreKHR)
                    load(vkWaitSemaphoresKHR)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_DECODE_QUEUE_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_KHR_VIDEO_DECODE_QUEUE_EXTENSION_NAME ) == 0 ) {
                    load(vkCmdDecodeVideoKHR)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_ENCODE_QUEUE_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_KHR_VIDEO_ENCODE_QUEUE_EXTENSION_NAME ) == 0 ) {
                    load(vkCmdEncodeVideoKHR)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_KHR_VIDEO_QUEUE_EXTENSION_NAME ) == 0 ) {
                    load(vkBindVideoSessionMemoryKHR)
                    load(vkCmdBeginVideoCodingKHR)
                    load(vkCmdControlVideoCodingKHR)
                    load(vkCmdEndVideoCodingKHR)
                    load(vkCreateVideoSessionKHR)
                    load(vkCreateVideoSessionParametersKHR)
                    load(vkDestroyVideoSessionKHR)
                    load(vkDestroyVideoSessionParametersKHR)
                    load(vkGetVideoSessionMemoryRequirementsKHR)
                    load(vkUpdateVideoSessionParametersKHR)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_BINARY_IMPORT_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_NVX_BINARY_IMPORT_EXTENSION_NAME ) == 0 ) {
                    load(vkCmdCuLaunchKernelNVX)
                    load(vkCreateCuFunctionNVX)
                    load(vkCreateCuModuleNVX)
                    load(vkDestroyCuFunctionNVX)
                    load(vkDestroyCuModuleNVX)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_IMAGE_VIEW_HANDLE_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_NVX_IMAGE_VIEW_HANDLE_EXTENSION_NAME ) == 0 ) {
                    load(vkGetImageViewAddressNVX)
                    load(vkGetImageViewHandleNVX)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CLIP_SPACE_W_SCALING_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_NV_CLIP_SPACE_W_SCALING_EXTENSION_NAME ) == 0 ) {
                    load(vkCmdSetViewportWScalingNV)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTIC_CHECKPOINTS_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_NV_DEVICE_DIAGNOSTIC_CHECKPOINTS_EXTENSION_NAME ) == 0 ) {
                    load(vkCmdSetCheckpointNV)
                    load(vkGetQueueCheckpointDataNV)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_NV_DEVICE_GENERATED_COMMANDS_EXTENSION_NAME ) == 0 ) {
                    load(vkCmdBindPipelineShaderGroupNV)
                    load(vkCmdExecuteGeneratedCommandsNV)
                    load(vkCmdPreprocessGeneratedCommandsNV)
                    load(vkCreateIndirectCommandsLayoutNV)
                    load(vkDestroyIndirectCommandsLayoutNV)
                    load(vkGetGeneratedCommandsMemoryRequirementsNV)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_RDMA_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_NV_EXTERNAL_MEMORY_RDMA_EXTENSION_NAME ) == 0 ) {
                    load(vkGetMemoryRemoteAddressNV)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_WIN32_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_NV_EXTERNAL_MEMORY_WIN32_EXTENSION_NAME ) == 0 ) {
                    load(vkGetMemoryWin32HandleNV)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_NV_FRAGMENT_SHADING_RATE_ENUMS_EXTENSION_NAME ) == 0 ) {
                    load(vkCmdSetFragmentShadingRateEnumNV)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_NV_MESH_SHADER_EXTENSION_NAME ) == 0 ) {
                    load(vkCmdDrawMeshTasksIndirectCountNV)
                    load(vkCmdDrawMeshTasksIndirectNV)
                    load(vkCmdDrawMeshTasksNV)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_NV_RAY_TRACING_EXTENSION_NAME ) == 0 ) {
                    load(vkBindAccelerationStructureMemoryNV)
                    load(vkCmdBuildAccelerationStructureNV)
                    load(vkCmdCopyAccelerationStructureNV)
                    load(vkCmdTraceRaysNV)
                    load(vkCmdWriteAccelerationStructuresPropertiesNV)
                    load(vkCompileDeferredNV)
                    load(vkCreateAccelerationStructureNV)
                    load(vkCreateRayTracingPipelinesNV)
                    load(vkDestroyAccelerationStructureNV)
                    load(vkGetAccelerationStructureHandleNV)
                    load(vkGetAccelerationStructureMemoryRequirementsNV)
                    load(vkGetRayTracingShaderGroupHandlesNV)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SCISSOR_EXCLUSIVE_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_NV_SCISSOR_EXCLUSIVE_EXTENSION_NAME ) == 0 ) {
                    load(vkCmdSetExclusiveScissorNV)
                }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], VK_NV_SHADING_RATE_IMAGE_EXTENSION_NAME ) == 0 ) {
                    load(vkCmdBindShadingRateImageNV)
                    load(vkCmdSetCoarseSampleOrderNV)
                    load(vkCmdSetViewportShadingRatePaletteNV)
                }
#endif

            }

#undef load
        }

    } const APICaller;

} // namespace engine::vulkan

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#endif //__C_ENG_API_CALLER_HPP__

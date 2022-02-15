//
// Created by loghin on 01.01.2022.
//

#ifndef __C_ENG_VULKAN_CORE_CONFIG_HPP__
#define __C_ENG_VULKAN_CORE_CONFIG_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#if __CLION_IDE__
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"
#endif

#define __C_ENG_VULKAN_CORE_VALIDATION_FEATURE_ENABLE_MAX_COUNT     32U /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_VALIDATION_FEATURE_DISABLE_MAX_COUNT    32U /* NOLINT(bugprone-reserved-identifier) */

#define __C_ENG_VULKAN_CORE_LAYER_MAX_COUNT  64U /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_LAYER_EXTENSION_MAX_COUNT  128U /* NOLINT(bugprone-reserved-identifier) */

#define __C_ENG_VULKAN_CORE_PHYSICAL_DEVICE_MAX_COUNT 8U /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_PHYSICAL_DEVICE_SURFACE_MAX_COUNT 32U /* NOLINT(bugprone-reserved-identifier) */

#define __C_ENG_VULKAN_CORE_PHYSICAL_DEVICE_GROUP_MAX_COUNT 8U /* NOLINT(bugprone-reserved-identifier) */

#define __C_ENG_VULKAN_CORE_QUEUE_FAMILY_MAX_COUNT 32U /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_QUEUE_FAMILY_QUEUE_MAX_COUNT 256U /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_QUEUE_FAMILY_PERFORMANCE_COUNTER_MAX_COUNT 16U /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_DEVICE_QUEUE_FAMILY_CREATE_INFO_MAX_COUNT __C_ENG_VULKAN_CORE_QUEUE_FAMILY_MAX_COUNT /* NOLINT(bugprone-reserved-identifier) */

#define __C_ENG_VULKAN_CORE_SURFACE_FORMAT_MAX_COUNT 512U /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_SURFACE_PRESENT_MODE_MAX_COUNT 16U /* NOLINT(bugprone-reserved-identifier) */

#define __C_ENG_VULKAN_CORE_VIEW_FORMAT_MAX_COUNT 16U /* NOLINT(bugprone-reserved-identifier) */

#define __C_ENG_VULKAN_CORE_SWAP_CHAIN_IMAGE_MAX_COUNT 256U /* NOLINT(bugprone-reserved-identifier) */

#define __C_ENG_VULKAN_CORE_RENDERING_INFO_FORMATS_MAX_COUNT 256U /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_SAMPLE_COUNT_ATTACHMENT_SAMPLES_MAX_COUNT 256U /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_VIEWPORT_DEPTH_MAX_COUNT 16U /* NOLINT(bugprone-reserved-identifier) */

#define __C_ENG_VULKAN_CORE_SUBMIT_INFO_MAX_COUNT 32U /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_PIPELINE_STAGE_FLAGS_MAX_COUNT 64U /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_SUBMIT_SEMAPHORE_INFO_MAX_COUNT 16U /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_SUBMIT_COMMAND_BUFFER_INFO_MAX_COUNT 32U /* NOLINT(bugprone-reserved-identifier) */

#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_ENUMERATE_INSTANCE_VERSION                                        "vkEnumerateInstanceVersion" /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_ENUMERATE_INSTANCE_LAYER_PROPERTIES                               "vkEnumerateInstanceLayerProperties" /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_ENUMERATE_INSTANCE_EXTENSION_PROPERTIES                           "vkEnumerateInstanceExtensionProperties" /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_CREATE_INSTANCE                                                   "vkCreateInstance" /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_DESTROY_INSTANCE                                                  "vkDestroyInstance" /* NOLINT(bugprone-reserved-identifier) */

#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_GET_DEVICE_PROC_ADDR                                              "pVkGetDeviceProcAddr" /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_ENUMERATE_PHYSICAL_DEVICES                                        "vkEnumeratePhysicalDevices" /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_GET_PHYSICAL_DEVICE_PROPERTIES                                    "vkGetPhysicalDeviceProperties" /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_GET_PHYSICAL_DEVICE_PROPERTIES_2                                  "vkGetPhysicalDeviceProperties2" /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_GET_PHYSICAL_DEVICE_FEATURES                                      "vkGetPhysicalDeviceFeatures" /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_GET_PHYSICAL_DEVICE_FEATURES_2                                    "vkGetPhysicalDeviceFeatures2" /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_ENUMERATE_DEVICE_LAYER_PROPERTIES                                 "vkEnumerateDeviceLayerProperties" /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_ENUMERATE_DEVICE_EXTENSION_PROPERTIES                             "vkEnumerateDeviceExtensionProperties" /* NOLINT(bugprone-reserved-identifier) */

#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_ENUMERATE_PHYSICAL_DEVICE_GROUPS                                  "vkEnumeratePhysicalDeviceGroups" /* NOLINT(bugprone-reserved-identifier) */

#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_CREATE_DEBUG_UTILS_MESSENGER                                      "vkCreateDebugUtilsMessengerEXT" /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_DESTROY_DEBUG_UTILS_MESSENGER                                     "vkDestroyDebugUtilsMessengerEXT" /* NOLINT(bugprone-reserved-identifier) */

#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_GET_PHYSICAL_DEVICE_QUEUE_FAMILY_PROPERTIES                       "vkGetPhysicalDeviceQueueFamilyProperties" /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_GET_PHYSICAL_DEVICE_QUEUE_FAMILY_PROPERTIES_2                     "vkGetPhysicalDeviceQueueFamilyProperties2" /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_ENUMERATE_PHYSICAL_DEVICE_QUEUE_FAMILY_PERFORMANCE_QUERY_COUNTERS "vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR" /* NOLINT(bugprone-reserved-identifier) */

#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_DESTROY_SURFACE                                                   "vkDestroySurfaceKHR" /* NOLINT(bugprone-reserved-identifier) */

#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_GET_PHYSICAL_DEVICE_SURFACE_SUPPORT                               "vkGetPhysicalDeviceSurfaceSupportKHR" /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_GET_PHYSICAL_DEVICE_SURFACE_CAPABILITIES                          "vkGetPhysicalDeviceSurfaceCapabilitiesKHR" /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_GET_PHYSICAL_DEVICE_SURFACE_CAPABILITIES_2                        "vkGetPhysicalDeviceSurfaceCapabilities2EXT" /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_GET_PHYSICAL_DEVICE_SURFACE_FORMATS                               "vkGetPhysicalDeviceSurfaceFormatsKHR" /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_GET_PHYSICAL_DEVICE_SURFACE_FORMATS_2                             "vkGetPhysicalDeviceSurfaceFormats2KHR" /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_GET_PHYSICAL_DEVICE_SURFACE_PRESENT_MODES                         "vkGetPhysicalDeviceSurfacePresentModesKHR" /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_GET_PHYSICAL_DEVICE_SURFACE_PRESENT_MODES_2                       "vkGetPhysicalDeviceSurfacePresentModes2EXT" /* NOLINT(bugprone-reserved-identifier) */

#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_CREATE_SWAP_CHAIN                                                 "vkCreateSwapchainKHR" /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_DESTROY_SWAP_CHAIN                                                "vkDestroySwapchainKHR" /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_GET_SWAP_CHAIN_IMAGES                                             "vkGetSwapchainImagesKHR" /* NOLINT(bugprone-reserved-identifier) */

#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_CREATE_IMAGE_VIEW                                                 "vkCreateImageView" /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_DESTROY_IMAGE_VIEW                                                "vkDestroyImageView" /* NOLINT(bugprone-reserved-identifier) */

#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_CREATE_DEVICE                                                     "vkCreateDevice" /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_DESTROY_DEVICE                                                    "vkDestroyDevice" /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_GET_DEVICE_QUEUE                                                  "vkGetDeviceQueue" /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_GET_DEVICE_QUEUE_2                                                "vkGetDeviceQueue2" /* NOLINT(bugprone-reserved-identifier) */

#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_CREATE_COMMAND_POOL                                               "vkCreateCommandPool" /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_DESTROY_COMMAND_POOL                                              "vkDestroyCommandPool" /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_RESET_COMMAND_POOL                                                "vkResetCommandPool" /* NOLINT(bugprone-reserved-identifier) */

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_TRIM_COMMAND_POOL                                                 "vkTrimCommandPool" /* NOLINT(bugprone-reserved-identifier) */
#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_AVAILABLE
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_TRIM_COMMAND_POOL                                                 "vkTrimCommandPoolKHR" /* NOLINT(bugprone-reserved-identifier) */
#endif

#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_ALLOCATE_COMMAND_BUFFERS                                          "vkAllocateCommandBuffers" /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_RESET_COMMAND_BUFFER                                              "vkResetCommandBuffer" /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_FREE_COMMAND_BUFFERS                                              "vkFreeCommandBuffers" /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_BEGIN_COMMAND_BUFFER                                              "vkBeginCommandBuffer" /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_END_COMMAND_BUFFER                                                "vkEndCommandBuffer" /* NOLINT(bugprone-reserved-identifier) */

#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_CMD_EXECUTE_COMMANDS                                              "vkCmdExecuteCommands" /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_CMD_SET_DEVICE_MASK                                               "vkCmdSetDeviceMask" /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_CMD_SET_DEVICE_MASK_KHR                                           "vkCmdSetDeviceMaskKHR" /* NOLINT(bugprone-reserved-identifier) */

#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_QUEUE_SUBMIT                                                      "vkQueueSubmit" /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_QUEUE_SUBMIT_2                                                    "vkQueueSubmit2" /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_QUEUE_SUBMIT_2_KHR                                                "vkQueueSubmit2KHR" /* NOLINT(bugprone-reserved-identifier) */

#if defined ( __C_ENG_USE_DEFENSIVE_PROGRAMMING ) || !defined(NDEBUG)

#define __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED true /* NOLINT(bugprone-reserved-identifier) */

#else

#define __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED false

#endif

#if __CLION_IDE__
#pragma clang diagnostic pop
#endif

#endif //__C_ENG_VULKAN_CORE_CONFIG_HPP__
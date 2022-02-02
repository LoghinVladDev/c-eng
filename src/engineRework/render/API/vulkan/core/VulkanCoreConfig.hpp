//
// Created by loghin on 01.01.2022.
//

#ifndef __C_ENG_VULKAN_CORE_CONFIG_HPP__
#define __C_ENG_VULKAN_CORE_CONFIG_HPP__

#define __C_ENG_VULKAN_CORE_VALIDATION_FEATURE_ENABLE_MAX_COUNT     32U
#define __C_ENG_VULKAN_CORE_VALIDATION_FEATURE_DISABLE_MAX_COUNT    32U

#define __C_ENG_VULKAN_CORE_LAYER_MAX_COUNT  64U
#define __C_ENG_VULKAN_CORE_LAYER_EXTENSION_MAX_COUNT  128U

#define __C_ENG_VULKAN_CORE_PHYSICAL_DEVICE_MAX_COUNT 8U

#define __C_ENG_VULKAN_CORE_PHYSICAL_DEVICE_GROUP_MAX_COUNT 8U

#define __C_ENG_VULKAN_CORE_QUEUE_FAMILY_MAX_COUNT 32U
#define __C_ENG_VULKAN_CORE_QUEUE_FAMILY_PERFORMANCE_COUNTER_MAX_COUNT 16U
#define __C_ENG_VULKAN_CORE_DEVICE_QUEUE_FAMILY_CREATE_INFO_MAX_COUNT __C_ENG_VULKAN_CORE_QUEUE_FAMILY_MAX_COUNT

#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_ENUMERATE_INSTANCE_VERSION                                        "vkEnumerateInstanceVersion"
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_ENUMERATE_INSTANCE_LAYER_PROPERTIES                               "vkEnumerateInstanceLayerProperties"
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_ENUMERATE_INSTANCE_EXTENSION_PROPERTIES                           "vkEnumerateInstanceExtensionProperties"
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_CREATE_INSTANCE                                                   "vkCreateInstance"
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_DESTROY_INSTANCE                                                  "vkDestroyInstance"

#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_GET_DEVICE_PROC_ADDR                                              "pVkGetDeviceProcAddr"
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_ENUMERATE_PHYSICAL_DEVICES                                        "vkEnumeratePhysicalDevices"
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_GET_PHYSICAL_DEVICE_PROPERTIES                                    "vkGetPhysicalDeviceProperties"
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_GET_PHYSICAL_DEVICE_PROPERTIES_2                                  "vkGetPhysicalDeviceProperties2"
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_GET_PHYSICAL_DEVICE_FEATURES                                      "vkGetPhysicalDeviceFeatures"
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_GET_PHYSICAL_DEVICE_FEATURES_2                                    "vkGetPhysicalDeviceFeatures2"
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_ENUMERATE_DEVICE_LAYER_PROPERTIES                                 "vkEnumerateDeviceLayerProperties"
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_ENUMERATE_DEVICE_EXTENSION_PROPERTIES                             "vkEnumerateDeviceExtensionProperties"

#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_ENUMERATE_PHYSICAL_DEVICE_GROUPS                                  "vkEnumeratePhysicalDeviceGroups"

#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_CREATE_DEBUG_UTILS_MESSENGER                                      "vkCreateDebugUtilsMessengerEXT"
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_DESTROY_DEBUG_UTILS_MESSENGER                                     "vkDestroyDebugUtilsMessengerEXT"

#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_GET_PHYSICAL_DEVICE_QUEUE_FAMILY_PROPERTIES                       "vkGetPhysicalDeviceQueueFamilyProperties"
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_GET_PHYSICAL_DEVICE_QUEUE_FAMILY_PROPERTIES_2                     "vkGetPhysicalDeviceQueueFamilyProperties2"
#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_ENUMERATE_PHYSICAL_DEVICE_QUEUE_FAMILY_PERFORMANCE_QUERY_COUNTERS "vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR"

#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_DESTROY_SURFACE                                                   "vkDestroySurfaceKHR"

#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_GET_PHYSICAL_DEVICE_SURFACE_SUPPORT                               "vkGetPhysicalDeviceSurfaceSupportKHR"

#define __C_ENG_VULKAN_CORE_FUNCTION_NAME_CREATE_DEVICE                                                     "vkCreateDevice"

#if defined ( __C_ENG_USE_DEFENSIVE_PROGRAMMING ) || !defined(NDEBUG)

#define __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED true

#else

#define __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED false

#endif

#endif //__C_ENG_VULKAN_CORE_CONFIG_HPP__

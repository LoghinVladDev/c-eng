//
// Created by loghin on 16.02.2022.
//

#ifndef C_ENG_VULKANAPICALLSTYPES_HPP
#define C_ENG_VULKANAPICALLSTYPES_HPP

#include <VulkanAPICallsPrivate.hpp>

#define C_ENG_MAP_START HEADER
#include <ObjectMapping.hpp>

struct CommonContext {
    engine :: vulkan :: Type ( Result ) error;
};

struct CreateInstanceContext {
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    engine :: vulkan :: Type ( Result ) error;
    VkInstanceCreateInfo                instance;
    VkApplicationInfo                   applicationInfo;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_REPORT_AVAILABLE
    VkDebugReportCallbackCreateInfoEXT  debugReport;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_UTILS_AVAILABLE
    VkDebugUtilsMessengerCreateInfoEXT  debugMessenger;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_FEATURES_AVAILABLE
    VkValidationFeaturesEXT             validationFeatures;
    VkValidationFeatureEnableEXT        validationFeatureEnables [ __C_ENG_VULKAN_CORE_VALIDATION_FEATURE_ENABLE_MAX_COUNT ];
    VkValidationFeatureDisableEXT       validationFeatureDisables [ __C_ENG_VULKAN_CORE_VALIDATION_FEATURE_DISABLE_MAX_COUNT ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_FLAGS_AVAILABLE
    VkValidationFlagsEXT                validationFlags;
    VkValidationCheckEXT                validationChecks [ __C_ENG_VULKAN_CORE_VALIDATION_CHECK_MAX_COUNT ];
#endif
};

struct EnumerateLayerPropertiesContext {
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    engine :: vulkan :: Type ( Result ) error;
    VkLayerProperties                   properties [ __C_ENG_VULKAN_CORE_LAYER_MAX_COUNT ];
#endif
};

struct EnumerateExtensionPropertiesContext {
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    engine :: vulkan :: Type ( Result ) error;
    VkExtensionProperties               properties [ __C_ENG_VULKAN_CORE_LAYER_MAX_COUNT ];
#endif
};

struct EnumeratePhysicalDevicesContext {
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    engine :: vulkan :: Type ( Result ) error;
    VkPhysicalDevice                    devices [ __C_ENG_VULKAN_CORE_PHYSICAL_DEVICE_MAX_COUNT ];
#endif
};

struct EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersContext {
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    engine :: vulkan :: Type ( Result ) error;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
    VkPerformanceCounterKHR             counters [ __C_ENG_VULKAN_CORE_QUEUE_FAMILY_PERFORMANCE_COUNTER_MAX_COUNT ];
    VkPerformanceCounterDescriptionKHR  descriptions [ __C_ENG_VULKAN_CORE_QUEUE_FAMILY_PERFORMANCE_COUNTER_MAX_COUNT ];
#endif
};

struct EnumeratePhysicalDeviceGroupsContext {
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    engine :: vulkan :: Type ( Result ) error;
#endif
#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    VkPhysicalDeviceGroupProperties     properties [ __C_ENG_VULKAN_CORE_PHYSICAL_DEVICE_GROUP_MAX_COUNT ];
#endif
};

union EnumerateSharedContext {
    EnumerateLayerPropertiesContext                                     layerProperties;
    EnumerateExtensionPropertiesContext                                 extensionProperties;
    EnumeratePhysicalDevicesContext                                     physicalDevices;
    EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersContext   physicalDeviceQueueFamilyPerformanceQueryCounters;
    EnumeratePhysicalDeviceGroupsContext                                physicalDeviceGroups;
};

union CreateSharedContext {
    CreateInstanceContext                                               instance;
};

union SharedContext {
    CommonContext                                                       common;
    CreateSharedContext                                                 create;
    EnumerateSharedContext                                              enumerate;
};


#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif //C_ENG_VULKANAPICALLSTYPES_HPP

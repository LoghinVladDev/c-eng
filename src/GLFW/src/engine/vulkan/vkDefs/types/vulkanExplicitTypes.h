//
// Created by vladl on 05/08/2020.
//

#ifndef ENG1_VULKANEXPLICITTYPES_H
#define ENG1_VULKANEXPLICITTYPES_H

#include <engineVulkanPreproc.h>

typedef VkPhysicalDevice                            VulkanPhysicalDevice;
typedef VkPhysicalDeviceProperties                  VulkanPhysicalDeviceProperties;
typedef VkPhysicalDeviceFeatures                    VulkanPhysicalDeviceFeatures;

typedef VkBool32                                    VulkanBool32;

typedef VkInstance                                  VulkanInstance;
typedef VkApplicationInfo                           VulkanApplicationInfo;
typedef VkInstanceCreateInfo                        VulkanInstanceCreateInfo;

typedef VkResult                                    VulkanResult;

typedef VkExtensionProperties                       VulkanExtensionProperties;

typedef VkLayerProperties                           VulkanLayerProperties;

typedef const int8 *                                GLFWExtensionLiteral;
typedef const int8 **                               GLFWExtensionLiteralArray;


typedef VkDebugUtilsMessengerCreateInfoEXT          VulkanDebugMessengerCreateInfo;
typedef VkAllocationCallbacks                       VulkanAllocationCallbacks;
typedef VkDebugUtilsMessengerEXT                    VulkanDebugMessenger;

typedef VkDebugUtilsMessageSeverityFlagBitsEXT      VulkanDebugMessageSeverityFlagBits;
typedef VkDebugUtilsMessageSeverityFlagsEXT         VulkanDebugMessageSeverityFlags;

typedef VkDebugUtilsMessageTypeFlagBitsEXT          VulkanDebugMessageTypeFlagBits;
typedef VkDebugUtilsMessageTypeFlagsEXT             VulkanDebugMessageTypeFlags;

typedef VkDebugUtilsMessengerCallbackDataEXT        VulkanDebugMessengerCallbackData;
typedef VkDebugUtilsMessengerCallbackDataFlagsEXT   VulkanDebugMessengerCallbackDataFlags;

typedef VkFlags                                     VulkanFlags;

#endif //ENG1_VULKANEXPLICITTYPES_H

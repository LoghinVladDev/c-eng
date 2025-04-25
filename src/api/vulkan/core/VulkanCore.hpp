//
// Created by loghin on 11/14/24.
//

#pragma once

#include <vulkan/vulkan_core.h>


#ifdef VK_API_VERSION_1_4
#define VK_API_CURRENT_VERSION VK_API_VERSION_1_4
#elifdef VK_API_VERSION_1_3
#define VK_API_CURRENT_VERSION VK_API_VERSION_1_3
#elifdef VK_API_VERSION_1_2
#define VK_API_CURRENT_VERSION VK_API_VERSION_1_2
#elifdef VK_API_VERSION_1_1
#define VK_API_CURRENT_VERSION VK_API_VERSION_1_1
#elifdef VK_API_VERSION_1_0
#define VK_API_CURRENT_VERSION VK_API_VERSION_1_0
#else
#error Unable to discern VK_API_CURRENT_VERSION
#endif

namespace vk {
using AllocationCallbacks = VkAllocationCallbacks;
using ApplicationInfo = VkApplicationInfo;
using Bool32 = VkBool32;
using DeviceCreateInfo = VkDeviceCreateInfo;
using DeviceHandle = VkDevice;
using DeviceQueueCreateInfo = VkDeviceQueueCreateInfo;
using ExtensionProperties = VkExtensionProperties;
using LayerProperties = VkLayerProperties;
using InstanceHandle = VkInstance;
using InstanceCreateInfo = VkInstanceCreateInfo;
using PhysicalDeviceFeatures = VkPhysicalDeviceFeatures;
using PhysicalDeviceHandle = VkPhysicalDevice;
using PhysicalDeviceProperties = VkPhysicalDeviceProperties;
using PhysicalDeviceType = VkPhysicalDeviceType;
using QueueFamilyProperties = VkQueueFamilyProperties;
using QueueFlagBits = VkQueueFlagBits;
using Result = VkResult;
using StructureType = VkStructureType;

using UnavailableType = void*;

inline constexpr auto vkTrue = VK_TRUE;
inline constexpr auto vkFalse = VK_FALSE;

inline constexpr auto compiledVersion = VK_API_CURRENT_VERSION;

inline auto createInstance(
    InstanceCreateInfo const* pCreateInfo,
    AllocationCallbacks const* pAllocator,
    InstanceHandle* pInstance
) noexcept -> Result {
  return vkCreateInstance(pCreateInfo, pAllocator, pInstance);
}

inline auto destroyInstance(
    InstanceHandle instance,
    AllocationCallbacks const* pAllocator
) noexcept -> void {
  return vkDestroyInstance(instance, pAllocator);
}

inline auto enumerateInstanceLayerProperties(
    uint32_t* pPropertyCount,
    LayerProperties* pProperties
) noexcept -> Result {
  return vkEnumerateInstanceLayerProperties(pPropertyCount, pProperties);
}

inline auto enumerateInstanceVersion(uint32_t* pApiVersion) noexcept -> Result {
  return vkEnumerateInstanceVersion(pApiVersion);
}

inline auto enumeratePhysicalDevices(
    InstanceHandle instance,
    uint32_t* pDeviceCount,
    PhysicalDeviceHandle* pHandles
) noexcept -> Result {
  return vkEnumeratePhysicalDevices(instance, pDeviceCount, pHandles);
}

inline auto enumeratePhysicalDeviceExtensionProperties(
    PhysicalDeviceHandle device,
    char const* pLayerName,
    uint32_t* pExtensionCount,
    ExtensionProperties* pExtensionProperties
) noexcept -> Result {
  return vkEnumerateDeviceExtensionProperties(device, pLayerName, pExtensionCount, pExtensionProperties);
}

inline auto getPhysicalDeviceProperties(
    PhysicalDeviceHandle device,
    PhysicalDeviceProperties* pProperties
) noexcept -> void {
  return vkGetPhysicalDeviceProperties(device, pProperties);
}

inline auto getPhysicalDeviceFeatures(
    PhysicalDeviceHandle device,
    PhysicalDeviceFeatures* pFeatures
) noexcept -> void {
  return vkGetPhysicalDeviceFeatures(device, pFeatures);
}

inline auto getPhysicalDeviceQueueFamilyProperties(
    PhysicalDeviceHandle device,
    uint32_t* pQueueFamilyPropertyCount,
    QueueFamilyProperties* pQueueFamilyProperties
) noexcept -> void {
  return vkGetPhysicalDeviceQueueFamilyProperties(device, pQueueFamilyPropertyCount, pQueueFamilyProperties);
}

inline auto createDevice(
    PhysicalDeviceHandle physicalDevice,
    DeviceCreateInfo const* pCreateInfo,
    AllocationCallbacks const* pAllocator,
    DeviceHandle* pDevice
) noexcept -> Result {
  return vkCreateDevice(physicalDevice, pCreateInfo, pAllocator, pDevice);
}

inline auto destroyDevice(
    DeviceHandle device,
    AllocationCallbacks const* pAllocator
) noexcept -> void {
  vkDestroyDevice(device, pAllocator);
}
} // namespace vk

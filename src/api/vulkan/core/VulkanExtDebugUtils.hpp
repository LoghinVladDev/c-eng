//
// Created by loghin on 18.04.2025.
//

#pragma once

#include "VulkanCore.hpp"

namespace vk {
#ifdef VK_EXT_debug_utils
using DebugUtilsMessageSeverityFlagBits = VkDebugUtilsMessageSeverityFlagBitsEXT;
using DebugUtilsMessageTypeFlags = VkDebugUtilsMessageTypeFlagsEXT;
using DebugUtilsMessageTypeFlagBits = VkDebugUtilsMessageTypeFlagBitsEXT;
using DebugUtilsMessengerCallbackData = VkDebugUtilsMessengerCallbackDataEXT;

using DebugUtilsMessengerCreateInfo = VkDebugUtilsMessengerCreateInfoEXT;
using DebugUtilsMessengerHandle = VkDebugUtilsMessengerEXT;

namespace detail {
thread_local inline PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessengerExtBinding {nullptr};
thread_local inline PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessengerExtBinding {nullptr};
} // namespace detail

inline auto createDebugMessenger(
    InstanceHandle instance,
    DebugUtilsMessengerCreateInfo const* pCreateInfo,
    AllocationCallbacks const* pAllocator,
    DebugUtilsMessengerHandle* pHandle
) noexcept -> Result {
  using detail::vkCreateDebugUtilsMessengerExtBinding;
  using detail::vkDestroyDebugUtilsMessengerExtBinding;
  if (!vkCreateDebugUtilsMessengerExtBinding) {
    vkCreateDebugUtilsMessengerExtBinding = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(
        vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT")
    );
    vkDestroyDebugUtilsMessengerExtBinding = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(
        vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT")
    );

    if (!vkCreateDebugUtilsMessengerExtBinding || !vkDestroyDebugUtilsMessengerExtBinding) {
      return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
  }

  return vkCreateDebugUtilsMessengerExtBinding(instance, pCreateInfo, pAllocator, pHandle);
}

inline auto destroyDebugMessenger(
    InstanceHandle instance,
    DebugUtilsMessengerHandle handle,
    AllocationCallbacks const* pAllocator
) noexcept -> void {
  using detail::vkDestroyDebugUtilsMessengerExtBinding;
  if (!vkDestroyDebugUtilsMessengerExtBinding) {
    return;
  }

  return vkDestroyDebugUtilsMessengerExtBinding(instance, handle, pAllocator);
}
#else
using DebugUtilsMessengerCreateInfo = UnavailableType;
using DebugUtilsMessengerHandle = UnavailableType;

inline auto createDebugMessenger(
    InstanceHandle instance,
    DebugUtilsMessengerCreateInfo const* pCreateInfo,
    AllocationCallbacks const* pAllocator,
    DebugUtilsMessengerHandle* pHandle
) noexcept -> Result {
  (void) instance;
  (void) pCreateInfo;
  (void) pAllocator;
  (void) pHandle;
  return VK_ERROR_EXTENSION_NOT_PRESENT;
}

inline auto destroyDebugMessenger(
    InstanceHandle instance,
    DebugUtilsMessengerHandle handle,
    AllocationCallbacks const* pAllocator
) noexcept -> void {
  (void) instance;
  (void) handle;
  (void) pAllocator;
}
#endif
} // namespace vk

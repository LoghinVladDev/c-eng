//
// Created by loghin on 18.04.2025.
//

#pragma once

#include "VulkanCore.hpp"

namespace vk {
#ifdef VK_KHR_surface
using SurfaceHandle = VkSurfaceKHR;

inline auto destroySurface(
    InstanceHandle instance,
    SurfaceHandle handle,
    AllocationCallbacks const* pAllocator
) noexcept -> void {
  vkDestroySurfaceKHR(instance, handle, pAllocator);
}

inline auto getPhysicalDeviceSurfaceSupport(
    PhysicalDeviceHandle device,
    uint32_t queueFamilyIndex,
    SurfaceHandle surface,
    Bool32* pSupported
) noexcept -> Result {
  return vkGetPhysicalDeviceSurfaceSupportKHR(device, queueFamilyIndex, surface, pSupported);
}
#else
using SurfaceHandle = UnavailableType;

inline auto destroySurface(
    InstanceHandle instance,
    SurfaceHandle handle,
    AllocationCallbacks const* pAllocator
) noexcept -> void {
  (void) instance;
  (void) handle;
  (void) pAllocator;
}

inline auto getPhysicalDeviceSurfaceSupport(
    PhysicalDeviceHandle device,
    uint32_t queueFamilyIndex,
    SurfaceHandle surface,
    Bool32* pSupported
) noexcept -> Result {
  (void) device;
  (void) queueFamilyIndex;
  (void) surface;
  (void) pSupported;
}
#endif
} // namespace vk

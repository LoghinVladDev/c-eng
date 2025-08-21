//
// Created by loghin on 18.04.2025.
//

#include "VulkanSurface.hpp"

#include <instance/VulkanInstance.hpp>
#include "generic/api/WindowManagerApiComponent.hpp"

#include <platform/window/NativeWindowData.hpp>
#include <core/VulkanHandles.hpp>

namespace c_eng::api::vk::detail {
namespace {
using cds::Unexpected;
} // namespace

Surface::~Surface() noexcept {
  assert(instance().functions().vkDestroySurfaceKHR && "undefined behavior");
  instance().functions().vkDestroySurfaceKHR(
      instance().handle(),
      handle(),
      allocationCallbacks()
  );
}

auto Surface::createSurface(
    Instance const& instance,
    Window const& window,
    Optional<VkAllocationCallbacks const*> pAllocationCallbacks
) noexcept -> Expected<Surface, VkResult> {
  using enum native::detail::NativeWindowInfoType;
  auto const allocationCallbacks = pAllocationCallbacks.getOr(instance.allocationCallbacks());

#if !defined(VK_KHR_surface)
  return Unexpected{VK_ERROR_EXTENSION_NOT_PRESENT};
#endif

  VkSurfaceKHR handle{VK_NULL_HANDLE};
  auto const& fns = instance.functions();

#if defined(WIN32)
#if defined(VK_KHR_win32_surface)
  if (!fns.vkCreateWin32SurfaceKHR) {
    return Unexpected{VK_ERROR_EXTENSION_NOT_PRESENT};
  }

  native::NativeWin32WindowData win32WindowData{};
  win32WindowData.type = Win32;
  if (!window.acquireNativeWindowData(&win32WindowData)) {
    return Unexpected{VK_ERROR_UNKNOWN};
  }

  VkWin32SurfaceCreateInfo createInfo{
      .sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
      .pNext = nullptr,
      .flags = 0,
      .hinstance = win32WindowData.instanceHandle,
      .hwnd = win32WindowData.windowHandle
  };

  if (auto const result = fns.vkCreateWin32SurfaceKHR(instance.handle(), &createInfo, allocationCallbacks, &handle;
      result != VK_SUCCES) {
    return Unexpected{result};
  }
  return {instance, allocationCallbacks, handle};
#endif
  assert(false && "Unhandled native surface call on windows");
  return Unexpected{VK_ERROR_UNKNOWN};

#elif defined(__linux)
#if defined(VK_KHR_wayland_surface)
  native::NativeWaylandWindowData waylandWindowData{};
  waylandWindowData.type = Wayland;
  if (window.acquireNativeWindowData(&waylandWindowData)) {
    if (!fns.vkCreateWaylandSurfaceKHR) {
      return Unexpected{VK_ERROR_EXTENSION_NOT_PRESENT};
    }

    VkWaylandSurfaceCreateInfoKHR createInfo{
        .sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR,
        .pNext = nullptr,
        .flags = 0,
        .display = waylandWindowData.display,
        .surface = waylandWindowData.surface
    };

    if (auto const result = fns.vkCreateWaylandSurfaceKHR(instance.handle(), &createInfo, allocationCallbacks, &handle);
        result != VK_SUCCESS) {
      return Unexpected{result};
    }
    return {instance, allocationCallbacks, handle};
  }
#endif

#if defined(VK_KHR_xlib_surface)
  native::NativeX11WindowData x11WindowData{};
  x11WindowData.type = X11;
  if (window.acquireNativeWindowData(&x11WindowData)) {
    if (!fns.vkCreateXlibSurfaceKHR) {
      return Unexpected{VK_ERROR_EXTENSION_NOT_PRESENT};
    }

    VkXlibSurfaceCreateInfoKHR createInfo{
        .sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR,
        .pNext = nullptr,
        .flags = 0,
        .dpy = x11WindowData.display,
        .window = x11WindowData.window
    };

    if (auto const result = fns.vkCreateXlibSurfaceKHR(instance.handle(), &createInfo, allocationCallbacks, &handle);
        result != VK_SUCCESS) {
      return Unexpected{result};
    }
    return {instance, allocationCallbacks, handle};
  }
#endif
  assert(false && "Unhandled native surface call on linux");
  return Unexpected{VK_ERROR_UNKNOWN};

#elif defined(__APPLE__)
  assert(false && "Unhandled native surface call on apple");
  return Unexpected{VK_ERROR_UNKNOWN};
#else
  assert(false && "Unhandled native surface call on unknown platform");
  return Unexpected{VK_ERROR_UNKNOWN};
#endif
}
} // namespace c_eng::api::vk::detail

//
// Created by loghin on 5/23/25.
//

#pragma once
#include "VulkanExtensions.hpp"

#if defined(WIN32)
#include <windef.h>
#include <vulkan/vulkan_win32.h>
#elif defined(__linux)
#include <X11/Xlib.h>
#include <wayland-client.h>
#include <vulkan/vulkan_wayland.h>
#include <vulkan/vulkan_xlib.h>
#elif defined(__APPLE__)
#include <vulkan/vulkan_macos.h>
#endif

namespace c_eng::api::vk::detail {
enum class PFNHandleResolveType {ResolveNone, ResolveGlobal, ResolveInstance, ResolveDevice};

#define C_ENG_VULKAN_HANDLE(_resolve, _origin, _name) _name,
enum class PFN {
#include "VulkanHandles.def"
};
#undef C_ENG_VULKAN_HANDLE

template <PFN> struct HandleTraits {};

#define C_ENG_VULKAN_HANDLE(_resolve, _origin, _name)                     \
  template <> struct HandleTraits<PFN::_name> {                           \
    using Type = PFN_ ## _name;                                           \
    static constexpr auto name = #_name;                                  \
    static constexpr auto resolveMethod = PFNHandleResolveType::_resolve; \
    static constexpr auto origin = Extension::_origin;                    \
  };

#include "VulkanHandles.def"
#undef C_ENG_VULKAN_HANDLE

#define C_ENG_VULKAN_HANDLE(_resolve, _origin, _name) C_ENG_LATE_JOIN(C_ENG_VULKAN_HANDLE_ ## _resolve, _origin, _name)
#define C_ENG_LATE_JOIN(_a, _b, _c) _a(_b, _c)

#define C_ENG_VULKAN_HANDLE_ResolveGlobal(_origin, _name) PFN_ ## _name _name{nullptr};
#define C_ENG_VULKAN_HANDLE_ResolveNone(_origin, _name) PFN_ ## _name _name{&::_name};
#define C_ENG_VULKAN_HANDLE_ResolveInstance(_origin, _name)
#define C_ENG_VULKAN_HANDLE_ResolveDevice(_origin, _name)

struct GlobalFnPtrs {
#include "api/vulkan/core/VulkanHandles.def"
};

#undef C_ENG_VULKAN_HANDLE_ResolveGlobal
#undef C_ENG_VULKAN_HANDLE_ResolveNone
#undef C_ENG_VULKAN_HANDLE_ResolveInstance
#undef C_ENG_VULKAN_HANDLE_ResolveDevice

#define C_ENG_VULKAN_HANDLE_ResolveGlobal(_origin, _name)
#define C_ENG_VULKAN_HANDLE_ResolveNone(_origin, _name)
#define C_ENG_VULKAN_HANDLE_ResolveInstance(_origin, _name) PFN_ ## _name _name{nullptr};
#define C_ENG_VULKAN_HANDLE_ResolveDevice(_origin, _name)

struct InstanceFnPtrs {
#include "api/vulkan/core/VulkanHandles.def"
};

#undef C_ENG_VULKAN_HANDLE_ResolveGlobal
#undef C_ENG_VULKAN_HANDLE_ResolveNone
#undef C_ENG_VULKAN_HANDLE_ResolveInstance
#undef C_ENG_VULKAN_HANDLE_ResolveDevice

#define C_ENG_VULKAN_HANDLE_ResolveGlobal(_origin, _name)
#define C_ENG_VULKAN_HANDLE_ResolveNone(_origin, _name)
#define C_ENG_VULKAN_HANDLE_ResolveInstance(_origin, _name)
#define C_ENG_VULKAN_HANDLE_ResolveDevice(_origin, _name) PFN_ ## _name _name{nullptr};

struct DeviceFnPtrs {
#include "api/vulkan/core/VulkanHandles.def"
};

#undef C_ENG_VULKAN_HANDLE_ResolveGlobal
#undef C_ENG_VULKAN_HANDLE_ResolveNone
#undef C_ENG_VULKAN_HANDLE_ResolveInstance
#undef C_ENG_VULKAN_HANDLE_ResolveDevice

#undef C_ENG_VULKAN_HANDLE
#undef C_ENG_LATE_JOIN

template <PFN fn> concept GlobalPFN = HandleTraits<fn>::resolveMethod == PFNHandleResolveType::ResolveGlobal;
template <PFN fn> concept InstancePFN = HandleTraits<fn>::resolveMethod == PFNHandleResolveType::ResolveInstance;
template <PFN fn> concept DevicePFN = HandleTraits<fn>::resolveMethod == PFNHandleResolveType::ResolveDevice;

template <PFN fn> requires GlobalPFN<fn> auto resolveGlobalHandle(PFN_vkGetInstanceProcAddr const resolver) noexcept
    -> typename HandleTraits<fn>::Type {
  return reinterpret_cast<typename HandleTraits<fn>::Type>(
      resolver(VK_NULL_HANDLE, HandleTraits<fn>::name)
  );
}

template <PFN fn> requires InstancePFN<fn> auto resolveInstanceHandle(
    PFN_vkGetInstanceProcAddr const resolver,
    VkInstance const instance
) noexcept -> typename HandleTraits<fn>::Type {
  return reinterpret_cast<typename HandleTraits<fn>::Type>(
      resolver(instance, HandleTraits<fn>::name)
  );
}

template <PFN fn> requires DevicePFN<fn> auto resolveDeviceHandle(
    PFN_vkGetDeviceProcAddr const resolver,
    VkDevice const device
) noexcept -> typename HandleTraits<fn>::Type {
  return reinterpret_cast<typename HandleTraits<fn>::Type>(
      resolver(device, HandleTraits<fn>::name)
  );
}
} // namespace c_eng::api::vk::detail

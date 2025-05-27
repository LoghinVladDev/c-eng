//
// Created by loghin on 5/23/25.
//

#pragma once
#include "VulkanExtensions.hpp"

namespace c_eng::api::vk::detail {
enum class PFNHandleResolveType {Always, Global, Instance, Device};

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

template <PFN fn> concept GlobalPFN = HandleTraits<fn>::resolveMethod == PFNHandleResolveType::Global;
template <PFN fn> concept InstancePFN = HandleTraits<fn>::resolveMethod == PFNHandleResolveType::Instance;
template <PFN fn> concept DevicePFN = HandleTraits<fn>::resolveMethod == PFNHandleResolveType::Device;

template <PFN fn> requires GlobalPFN<fn> auto resolveGlobalHandle() noexcept -> typename HandleTraits<fn>::Type {
  return reinterpret_cast<typename HandleTraits<fn>::Type>(
      vkGetInstanceProcAddr(VK_NULL_HANDLE, HandleTraits<fn>::name)
  );
}

template <PFN fn> requires InstancePFN<fn> auto resolveInstanceHandle(VkInstance const instance) noexcept
    -> typename HandleTraits<fn>::Type {
  return reinterpret_cast<typename HandleTraits<fn>::Type>(
      vkGetInstanceProcAddr(instance, HandleTraits<fn>::name)
  );
}
} // namespace c_eng::api::vk::detail

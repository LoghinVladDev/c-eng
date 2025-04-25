//
// Created by loghin on 18.04.2025.
//

#pragma once

#include <cds/meta/Semantics>
#include <vulkan/vulkan_core.h>

namespace c_eng::api::vk::detail {
using cds::impl::xch;

#ifndef VK_EXT_debug_utils
VK_DEFINE_HANDLE(VkDebugUtilsMessengerEXT)
#endif

class DebugMessenger {
public:
  constexpr DebugMessenger(VkInstance instance, VkDebugUtilsMessengerEXT handle) noexcept :
      _instance{instance},
      _handle{handle} {}

  DebugMessenger(DebugMessenger const&) = delete;
  constexpr DebugMessenger(DebugMessenger&& messenger) noexcept :
      _instance{xch(messenger._instance, VK_NULL_HANDLE)},
      _handle{xch(messenger._handle, VK_NULL_HANDLE)} {}

  ~DebugMessenger() noexcept {
    if (_handle) {
      vkDestroyDebugUtilsMessengerEXT(_instance, _handle, nullptr);
    }
  }

private:
  VkInstance _instance {VK_NULL_HANDLE};
  VkDebugUtilsMessengerEXT _handle {VK_NULL_HANDLE};
};
} // namespace c_eng::api::vk::detail

namespace c_eng::api::vk {
using detail::DebugMessenger;
} // namespace c_eng::api::vk

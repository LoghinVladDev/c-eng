//
// Created by loghin on 18.04.2025.
//

#pragma once

#include <cds/collection/Vector>
#include <ext/cds/Expected.hpp>
#include <vulkan/vulkan_core.h>

namespace c_eng::api::vk::detail {
using cds::experimental::Expected;
using cds::Vector;

class Instance;

class PhysicalDevice {
public:
  constexpr PhysicalDevice(Instance const& instance, VkPhysicalDevice handle) noexcept :
      _instance{instance}, _handle{handle} {}

  PhysicalDevice(PhysicalDevice const&) = default;
  ~PhysicalDevice() = default;

  [[nodiscard]] auto extensionProperties() const noexcept -> Expected<Vector<VkExtensionProperties>, VkResult>;
  [[nodiscard]] auto properties() const noexcept -> VkPhysicalDeviceProperties;
  [[nodiscard]] auto features() const noexcept -> VkPhysicalDeviceFeatures;

  [[nodiscard]] constexpr auto handle() const noexcept {
    return _handle;
  }

  [[nodiscard]] constexpr auto const& instance() const noexcept {
    return _instance;
  }
private:
  Instance const& _instance;
  VkPhysicalDevice _handle{VK_NULL_HANDLE};
};
} // namespace c_eng::api::vk::detail

namespace c_eng::api::vk {
using detail::PhysicalDevice;
} // namespace c_eng::api::vk

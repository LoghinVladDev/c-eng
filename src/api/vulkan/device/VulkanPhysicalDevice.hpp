//
// Created by loghin on 18.04.2025.
//

#pragma once

#include <cds/Expected>
#include <cds/collection/Vector>
#include <core/VulkanSubunits.hpp>
#include "VulkanPhysicalDeviceExtendedFeatures.hpp"

namespace c_eng::api::vk::detail {
using cds::Expected;
using cds::Vector;

class Instance;
class QueueFamily;
class Surface;

#ifndef VK_KHR_surface
struct VkSurfaceCapabilitiesKHR{};
#endif

class PhysicalDevice : public VulkanObject<SubObject<Instance>, WrapsVulkanHandle<VkPhysicalDevice>> {
public:
  using VulkanObject::VulkanObject;

  PhysicalDevice(PhysicalDevice const&) = default;
  PhysicalDevice(PhysicalDevice&&) = default;
  ~PhysicalDevice() = default;

  [[nodiscard]] auto extensionProperties() const noexcept -> Expected<Vector<VkExtensionProperties>, VkResult>;
  [[nodiscard]] auto properties() const noexcept -> VkPhysicalDeviceProperties;
  [[nodiscard]] auto features() const noexcept -> VkPhysicalDeviceFeatures;
  [[nodiscard]] auto queueFamilies() const noexcept -> Vector<QueueFamily>;

  [[nodiscard]] auto surfaceCapabilities(Surface const& surface) const noexcept
      -> Expected<VkSurfaceCapabilitiesKHR, VkResult>;

  [[nodiscard]] auto surfaceFormats(Surface const& surface) const noexcept
      -> Expected<Vector<VkSurfaceFormatKHR>, VkResult>;

  [[nodiscard]] auto surfacePresentModes(Surface const& surface) const noexcept
      -> Expected<Vector<VkPresentModeKHR>, VkResult>;

#if defined(VK_VERSION_1_1)
  auto getFeatures(VkPhysicalDeviceFeatures2& features) const noexcept -> void;

  template <typename... Features> [[nodiscard]] auto features() const noexcept {
    PhysicalDeviceExtendedFeatures<Features...> features;
    getFeatures(static_cast<VkPhysicalDeviceFeatures2&>(features));
    return features;
  }
#endif
};
} // namespace c_eng::api::vk::detail

namespace c_eng::api::vk {
using detail::PhysicalDevice;
} // namespace c_eng::api::vk

//
// Created by loghin on 18.04.2025.
//

#pragma once

#include <cds/collection/Vector>
#include <core/VulkanSubunits.hpp>
#include <ext/cds/Expected.hpp>

namespace c_eng::api::vk::detail {
using cds::experimental::Expected;
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
};
} // namespace c_eng::api::vk::detail

namespace c_eng::api::vk {
using detail::PhysicalDevice;
} // namespace c_eng::api::vk

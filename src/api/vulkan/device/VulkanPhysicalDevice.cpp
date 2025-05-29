//
// Created by loghin on 18.04.2025.
//

#include "VulkanPhysicalDevice.hpp"
#include <device/VulkanQueue.hpp>
#include <instance/VulkanInstance.hpp>
#include <wsi/VulkanSurface.hpp>
#include "generic/lang/Range.hpp"

#include <core/VulkanHandles.hpp>

namespace c_eng::api::vk::detail {
namespace {
using cds::U32;
using cds::experimental::Unexpected;
using generic::indexedProject;
} // namespace

auto PhysicalDevice::extensionProperties() const noexcept -> Expected<Vector<VkExtensionProperties>, VkResult> {
  auto const& fns = instance().functions();
  assert(fns.vkEnumerateDeviceExtensionProperties && "undefined behavior");

  Vector<VkExtensionProperties> extensionProperties;
  std::uint32_t extensionCount = 0u;
  if (auto const result = fns.vkEnumerateDeviceExtensionProperties(handle(), nullptr, &extensionCount, nullptr);
      result != VK_SUCCESS) {
    return Unexpected{result};
  }

  extensionProperties.resize(extensionCount);
  if (auto const result = fns.vkEnumerateDeviceExtensionProperties(handle(), nullptr, &extensionCount, extensionProperties.data());
      result != VK_SUCCESS) {
    return Unexpected{result};
  }

  return extensionProperties;
}

auto PhysicalDevice::properties() const noexcept -> VkPhysicalDeviceProperties {
  assert(instance().functions().vkGetPhysicalDeviceProperties && "undefined behavior");
  VkPhysicalDeviceProperties properties{};
  instance().functions().vkGetPhysicalDeviceProperties(handle(), &properties);
  return properties;
}

auto PhysicalDevice::features() const noexcept -> VkPhysicalDeviceFeatures {
  assert(instance().functions().vkGetPhysicalDeviceFeatures && "undefined behavior");
  VkPhysicalDeviceFeatures features{};
  instance().functions().vkGetPhysicalDeviceFeatures(handle(), &features);
  return features;
}

auto PhysicalDevice::queueFamilies() const noexcept -> Vector<QueueFamily> {
  auto const& fns = instance().functions();
  assert(fns.vkGetPhysicalDeviceQueueFamilyProperties && "undefined behavior");

  Vector<VkQueueFamilyProperties> properties;
  std::uint32_t propertyCount = 0;
  fns.vkGetPhysicalDeviceQueueFamilyProperties(handle(), &propertyCount, nullptr);

  properties.resize(propertyCount);
  fns.vkGetPhysicalDeviceQueueFamilyProperties(handle(), &propertyCount, properties.data());
  return Vector<QueueFamily>{properties | indexedProject([this](U32 index, auto const& properties) {
    return QueueFamily{*this, index, properties};
  })};
}

auto PhysicalDevice::surfaceCapabilities(Surface const& surface) const noexcept
    -> Expected<VkSurfaceCapabilitiesKHR, VkResult> {
#ifndef VK_KHR_surface
  return Unexpected{VK_ERROR_EXTENSION_NOT_PRESENT};
#else
  auto const& fns = instance().functions();
  if (!fns.vkGetPhysicalDeviceSurfaceCapabilitiesKHR) {
    return Unexpected{VK_ERROR_EXTENSION_NOT_PRESENT};
  }

  VkSurfaceCapabilitiesKHR capabilities{};
  if (auto const result = fns.vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
          handle(),
          surface.handle(),
          &capabilities
      ); result != VK_SUCCESS) {
    return Unexpected{result};
  }

  return capabilities;
#endif
}

auto PhysicalDevice::surfaceFormats(Surface const& surface) const noexcept
    -> Expected<Vector<VkSurfaceFormatKHR>, VkResult> {
#ifndef VK_KHR_surface
  return Unexpected{VK_ERROR_EXTENSION_NOT_PRESENT};
#else
  auto const& fns = instance().functions();
  if (!fns.vkGetPhysicalDeviceSurfaceFormatsKHR) {
    return Unexpected{VK_ERROR_EXTENSION_NOT_PRESENT};
  }

  std::uint32_t formatCount;
  if (auto const result = fns.vkGetPhysicalDeviceSurfaceFormatsKHR(
          handle(),
          surface.handle(),
          &formatCount,
          nullptr
      ); result != VK_SUCCESS) {
    return Unexpected{result};
  }

  Vector<VkSurfaceFormatKHR> formats;
  formats.resize(formatCount);

  if (auto const result = fns.vkGetPhysicalDeviceSurfaceFormatsKHR(
          handle(),
          surface.handle(),
          &formatCount,
          formats.data()
      ); result != VK_SUCCESS) {
    return Unexpected{result};
  }

  return formats;
#endif
}

auto PhysicalDevice::surfacePresentModes(Surface const& surface) const noexcept
-> Expected<Vector<VkPresentModeKHR>, VkResult> {
#ifndef VK_KHR_surface
  return Unexpected{VK_ERROR_EXTENSION_NOT_PRESENT};
#else
  auto const& fns = instance().functions();
  if (!fns.vkGetPhysicalDeviceSurfacePresentModesKHR) {
    return Unexpected{VK_ERROR_EXTENSION_NOT_PRESENT};
  }

  std::uint32_t modeCount;
  if (auto const result = fns.vkGetPhysicalDeviceSurfacePresentModesKHR(
          handle(),
          surface.handle(),
          &modeCount,
          nullptr
      ); result != VK_SUCCESS) {
    return Unexpected{result};
  }

  Vector<VkPresentModeKHR> modes;
  modes.resize(modeCount);

  if (auto const result = fns.vkGetPhysicalDeviceSurfacePresentModesKHR(
          handle(),
          surface.handle(),
          &modeCount,
          modes.data()
      ); result != VK_SUCCESS) {
    return Unexpected{result};
  }

  return modes;
#endif
}

#ifdef VK_VERSION_1_1
auto PhysicalDevice::getFeatures(VkPhysicalDeviceFeatures2& features) const noexcept -> void {
  auto const& fns = instance().functions();
  assert(fns.vkGetPhysicalDeviceFeatures2 && "undefined behavior");
  fns.vkGetPhysicalDeviceFeatures2(handle(), &features);
}

#endif
} // namespace c_eng::api::vk::detail

//
// Created by loghin on 18.04.2025.
//

#include "VulkanPhysicalDevice.hpp"
#include <api/vulkan/instance/VulkanInstance.hpp>

namespace c_eng::api::vk::detail {
namespace {
using cds::experimental::Unexpected;
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
} // namespace c_eng::api::vk::detail

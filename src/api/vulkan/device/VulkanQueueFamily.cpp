//
// Created by loghin on 18.04.2025.
//

#include "VulkanQueueFamily.hpp"

#include <device/VulkanPhysicalDevice.hpp>
#include <instance/VulkanInstance.hpp>
#include <wsi/VulkanSurface.hpp>

#include "core/VulkanHandles.hpp"

namespace c_eng::api::vk::detail {
namespace {
using cds::Unexpected;
} // namespace

auto QueueFamily::supportsPresentOn(Surface const& surface) const noexcept -> Expected<bool, VkResult> {
  auto const& fns = device().instance().functions();
  if (!fns.vkGetPhysicalDeviceSurfaceSupportKHR) {
    return Unexpected{VK_ERROR_EXTENSION_NOT_PRESENT};
  }

  VkBool32 supported;
  if (auto const result = fns.vkGetPhysicalDeviceSurfaceSupportKHR(
          device().handle(), index(), surface.handle(), &supported
      ); result != VK_SUCCESS) {
    return Unexpected{result};
  }

  return supported == VK_TRUE;
}
} // namespace c_eng::api::vk::detail

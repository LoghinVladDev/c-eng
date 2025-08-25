//
// Created by loghin on 18.04.2025.
//

#include "VulkanQueue.hpp"

#include <device/VulkanLogicalDevice.hpp>
#include <sync/VulkanFence.hpp>
#include <core/VulkanHandles.hpp>

namespace c_eng::api::vk::detail {
namespace {
using cds::Unexpected;
} // namespace

auto Queue::submit(VectorView<VkSubmitInfo const> info, Fence const& fence) const noexcept -> VkResult {
  auto const fn = device().functions().vkQueueSubmit;
  assert(fn && "undefined behavior");
  return fn(handle(), static_cast<std::uint32_t>(info.size()), info.data(), fence.handle());
}

auto Queue::present(VkPresentInfoKHR const& info) const noexcept -> VkResult {
#ifndef VK_KHR_swapchain
  return VkResult::VK_ERROR_EXTENSION_NOT_PRESENT;
#else
  auto const fn = device().functions().vkQueuePresentKHR;
  assert(fn && "undefined behavior");
  return fn(handle(), &info);
#endif
}
} // namespace c_eng::api::vk::detail

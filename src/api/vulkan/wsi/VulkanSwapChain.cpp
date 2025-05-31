//
// Created by loghin on 5/29/25.
//

#include "VulkanSwapChain.hpp"

#include <device/VulkanLogicalDevice.hpp>
#include <device/VulkanPhysicalDevice.hpp>
#include <wsi/VulkanSurface.hpp>

#include "core/VulkanHandles.hpp"

namespace c_eng::api::vk::detail {
namespace {
using cds::experimental::Unexpected;
namespace cds_ex = cds::experimental;
} // namespace

auto SwapChainBuilder::build(Surface const& surface) const noexcept -> Expected<SwapChain, VkResult> {
#ifndef VK_KHR_swapchain
  return Unexpected{VK_ERROR_EXTENSION_NOT_PRESENT};
#else
  auto const capabilities = _device.device().surfaceCapabilities(surface);
  auto const formats = _device.device().surfaceFormats(surface);
  auto const presentModes = _device.device().surfacePresentModes(surface);

  return cds_ex::tie(capabilities, formats, presentModes).then([this, &surface](auto const& values)
      -> Expected<SwapChain, VkResult> {
    auto const& [capabilities, formats, presentModes] = values;
    auto const& fns = _device.functions();
    if (!fns.vkCreateSwapchainKHR || !fns.vkDestroySwapchainKHR) {
      return Unexpected{VK_ERROR_EXTENSION_NOT_PRESENT};
    }

    auto const allocationCallbacks = _pAllocationCallbacks.getOr(_device.allocationCallbacks());
    auto const minImageCount = capabilities.minImageCount;
    auto const maxImageCount = capabilities.maxImageCount;
    auto const targetImageCount = minImageCount + _bufferImageCount;
    auto const actualImageCount = maxImageCount == 0u
        ? targetImageCount
        : maxImageCount <= targetImageCount
        ? targetImageCount
        : maxImageCount;

    VkSwapchainCreateInfoKHR createInfo{
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .pNext = nullptr,
        .flags = 0u,
        .surface = surface.handle(),
        .minImageCount = actualImageCount,

    };
  });
#endif
}
} // namespace c_eng::api::vk::detail

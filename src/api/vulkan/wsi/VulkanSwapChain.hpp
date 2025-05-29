//
// Created by loghin on 5/29/25.
//

#pragma once

#include <core/VulkanSubunits.hpp>

namespace c_eng::api::vk::detail {
class LogicalDevice;
class SwapChainBuilder;

#ifndef VK_KHR_swapchain
VK_DEFINE_HANDLE(VkSwapchainKHR)
#endif

class SwapChain :
    public VulkanObject<SubObject<LogicalDevice>, WithAllocationCallbacks, WrapsVulkanHandle<VkSwapchainKHR>> {
public:
  using VulkanObject::VulkanObject;
  ~SwapChain() noexcept;

  [[nodiscard]] static constexpr auto builder(LogicalDevice const& device) noexcept -> SwapChainBuilder;
};

class SwapChainBuilder {
public:
  explicit constexpr SwapChainBuilder(LogicalDevice const& device) noexcept : _device{device} {}

private:
  LogicalDevice const& _device;
};

constexpr auto SwapChain::builder(LogicalDevice const& device) noexcept -> SwapChainBuilder {
  return SwapChainBuilder{device};
}
} // namespace c_eng::api::vk::detail

namespace c_eng::api::vk {
using detail::SwapChain;
using detail::SwapChainBuilder;
} // namespace c_eng::api::vk

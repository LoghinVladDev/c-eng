//
// Created by loghin on 5/29/25.
//

#pragma once

#include <cds/Optional>
#include <core/VulkanSubunits.hpp>
#include <ext/cds/Expected.hpp>

namespace c_eng::api::vk::detail {
class LogicalDevice;
class SwapChainBuilder;
class Surface;

using cds::Optional;
using cds::U32;
using cds::experimental::Expected;
using cds::nullopt;

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

  [[nodiscard]] auto build(Surface const& surface) const noexcept -> Expected<SwapChain, VkResult>;

  auto& withBufferImageCount(U32 const imageCount) noexcept {
    _bufferImageCount = imageCount;
    return *this;
  }

  auto& withAllocationCallbacks(VkAllocationCallbacks const* pAllocationCallbacks) noexcept {
    _pAllocationCallbacks = pAllocationCallbacks;
    return *this;
  }

private:
  LogicalDevice const& _device;
  Optional<VkAllocationCallbacks const*> _pAllocationCallbacks{nullopt};
  U32 _bufferImageCount{1u};
};

constexpr auto SwapChain::builder(LogicalDevice const& device) noexcept -> SwapChainBuilder {
  return SwapChainBuilder{device};
}
} // namespace c_eng::api::vk::detail

namespace c_eng::api::vk {
using detail::SwapChain;
using detail::SwapChainBuilder;
} // namespace c_eng::api::vk

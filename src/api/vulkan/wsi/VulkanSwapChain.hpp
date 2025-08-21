//
// Created by loghin on 5/29/25.
//

#pragma once

#include <cds/Expected>
#include <cds/Optional>
#include <cds/collection/Vector>
#include <core/VulkanSubunits.hpp>
#include <generic/lang/Concepts.hpp>

namespace c_eng::api::vk::detail {
class LogicalDevice;
class SwapChainBuilder;
class Surface;
class QueueFamily;
class FormattedImage;

using cds::Expected;
using cds::Optional;
using cds::U32;
using cds::Vector;
using cds::nullopt;
using cds::impl::forEach;
using cds::begin;
using cds::end;
using cds::fwd;

using generic::concepts::IterableOf;

#ifndef VK_KHR_swapchain
VK_DEFINE_HANDLE(VkSwapchainKHR)
struct VkSurfaceFormatKHR{};
enum class VkPresentModeKHR{};
#endif

class SwapChain :
    public VulkanObject<SubObject<LogicalDevice>, WithAllocationCallbacks, WrapsVulkanHandle<VkSwapchainKHR>> {
public:
  constexpr SwapChain(
      LogicalDevice const& device,
      VkAllocationCallbacks const* allocationCallbacks,
      VkSwapchainKHR handle,
      VkFormat imageFormat
  ) noexcept : VulkanObject{device, allocationCallbacks, handle}, _imageFormat{imageFormat} {}

  SwapChain(SwapChain&&) = default;
  ~SwapChain() noexcept;

  [[nodiscard]] static constexpr auto builder(LogicalDevice const& device) noexcept -> SwapChainBuilder;

  [[nodiscard]] auto images() const noexcept -> Expected<Vector<FormattedImage>, VkResult>;

  [[nodiscard]] constexpr auto imageFormat() const noexcept {
    return _imageFormat;
  }

private:
  VkFormat _imageFormat;
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

  auto& withSurfaceFormat(VkSurfaceFormatKHR const& format) noexcept {
    _surfaceFormat = format;
    return *this;
  }

  auto& withPresentMode(VkPresentModeKHR const presentMode) noexcept {
    _presentMode = presentMode;
    return *this;
  }

  auto& withExtent(VkExtent2D const extent) noexcept {
    _extent = extent;
    return *this;
  }

  auto& withImageLayerCount(U32 const count) noexcept {
    _imageLayerCount = count;
    return *this;
  }

  auto& withImageUsage(VkImageUsageFlags const flags) noexcept {
    _usageFlags = flags;
    return *this;
  }

  template <IterableOf<QueueFamily const&> QueueFamilies>
  auto& withImagesAccessedBy(QueueFamilies&& families) noexcept {
    forEach(begin(fwd<QueueFamilies>(families)), end(fwd<QueueFamilies>(families)), [this](auto const& family) {
      _familiesToGrantAccessTo.emplaceBack(&family);
    });
    return *this;
  }

private:
  LogicalDevice const& _device;
  Optional<VkAllocationCallbacks const*> _pAllocationCallbacks{nullopt};
  U32 _bufferImageCount{1u};
  Optional<VkSurfaceFormatKHR> _surfaceFormat{nullopt};
  Optional<VkPresentModeKHR> _presentMode{nullopt};
  Optional<VkExtent2D> _extent{nullopt};
  U32 _imageLayerCount{1u};
  VkImageUsageFlags _usageFlags{VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT};
  Vector<QueueFamily const*> _familiesToGrantAccessTo{};
};

constexpr auto SwapChain::builder(LogicalDevice const& device) noexcept -> SwapChainBuilder {
  return SwapChainBuilder{device};
}
} // namespace c_eng::api::vk::detail

namespace c_eng::api::vk {
using detail::SwapChain;
using detail::SwapChainBuilder;
} // namespace c_eng::api::vk

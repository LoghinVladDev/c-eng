//
// Created by loghin on 5/29/25.
//

#include "VulkanSwapChain.hpp"

#include <device/VulkanLogicalDevice.hpp>
#include <device/VulkanPhysicalDevice.hpp>
#include <device/VulkanQueueFamily.hpp>
#include <generic/lang/Range.hpp>
#include <memory/VulkanImage.hpp>
#include <wsi/VulkanSurface.hpp>

#include "core/VulkanHandles.hpp"

constexpr auto operator==(VkSurfaceFormatKHR const& lhs, VkSurfaceFormatKHR const& rhs) noexcept -> bool {
  return lhs.format == rhs.format && lhs.colorSpace == rhs.colorSpace;
}

namespace c_eng::api::vk::detail {
namespace {
using cds::clamp;
using cds::experimental::Unexpected;
namespace cds_ex = cds::experimental;

using generic::project;
} // namespace

SwapChain::~SwapChain() noexcept {
#ifdef VK_KHR_swapchain
  assert(device().functions().vkDestroySwapchainKHR && "undefined behavior");
  device().functions().vkDestroySwapchainKHR(device().handle(), handle(), allocationCallbacks());
#endif
}


auto SwapChainBuilder::build(Surface const& surface) const noexcept -> Expected<SwapChain, VkResult> {
#ifndef VK_KHR_swapchain
  return Unexpected{VK_ERROR_EXTENSION_NOT_PRESENT};
#else
  auto const expectedCapabilities = _device.device().surfaceCapabilities(surface);
  auto const expectedFormats = _device.device().surfaceFormats(surface);
  auto const expectedPresentModes = _device.device().surfacePresentModes(surface);

  auto const expectedFormat = expectedFormats.then([this](auto const& formats)
      -> Expected<VkSurfaceFormatKHR, VkResult> {
    if (_surfaceFormat) {
      if (!formats.contains(*_surfaceFormat)) {
        return Unexpected{VK_ERROR_FORMAT_NOT_SUPPORTED};
      }
      return *_surfaceFormat;
    }

    assert(formats && "Expected at least one format, compatibility of device-surface unchecked");
    auto constexpr srgbFormat = VkSurfaceFormatKHR{
        .format = VK_FORMAT_B8G8R8A8_SRGB,
        .colorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR
    };
    return formats.contains(srgbFormat)
        ? srgbFormat
        : formats.front();
  });

  auto const expectedPresentMode = expectedPresentModes.then([this](auto const& modes)
      -> Expected<VkPresentModeKHR, VkResult> {
    if (_presentMode) {
      if (!modes.contains(*_presentMode)) {
        return Unexpected{VK_ERROR_FORMAT_NOT_SUPPORTED};
      }
      return *_presentMode;
    }

    if (modes.contains(VK_PRESENT_MODE_MAILBOX_KHR)) {
      return VK_PRESENT_MODE_MAILBOX_KHR;
    }
    if (modes.contains(VK_PRESENT_MODE_FIFO_KHR)) {
      return VK_PRESENT_MODE_FIFO_KHR;
    }

    assert(modes && "Expected at least one preset mode, compatibility of device-surface unchecked");
    return modes.front();
  });

  auto const expectedExtent = expectedCapabilities.transform([this](auto const& capabilities) {
    if (capabilities.currentExtent.width != cds::limits::u32Max) {
      return capabilities.currentExtent;
    }

    auto const desiredExtent = _extent.getOr(capabilities.maxImageExtent);
    auto const [desiredWidth, desiredHeight] = desiredExtent;
    auto const [minWidth, minHeight] = capabilities.minImageExtent;
    auto const [maxWidth, maxHeight] = capabilities.maxImageExtent;
    return VkExtent2D{
        .width = clamp(desiredWidth, minWidth, maxWidth),
        .height = clamp(desiredHeight, minHeight, maxHeight),
    };
  });

  return cds_ex::tie(expectedFormat, expectedPresentMode, expectedExtent, expectedCapabilities).then([this, &surface](auto const& values)
      -> Expected<SwapChain, VkResult> {
    auto const& [format, presentMode, extent, capabilities] = values;
    auto const& fns = _device.functions();
    if (!fns.vkCreateSwapchainKHR || !fns.vkDestroySwapchainKHR || !fns.vkGetSwapchainImagesKHR) {
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

    Vector<U32> allowedQueueFamilyIndices{};
    auto imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    U32 observedFeatureCount = 0;
    for (auto const* family : _familiesToGrantAccessTo) {
      assert(family && "undefined behavior");
      auto const supportedFeatures = static_cast<U32>(family->supportsGraphics())
          + static_cast<U32>(family->supportsPresentOn(surface).valueOr(false));
      if (supportedFeatures == 0) {
        return Unexpected{VK_ERROR_NOT_PERMITTED};
      }

      if (constexpr auto graphicsAndPresentFeatureCount = 2u;
          supportedFeatures != graphicsAndPresentFeatureCount) {
        imageSharingMode = VK_SHARING_MODE_CONCURRENT;
      }
      observedFeatureCount = cds::maxOf(observedFeatureCount, supportedFeatures);
      allowedQueueFamilyIndices.emplaceBack(family->index());
    }

    if (imageSharingMode == VK_SHARING_MODE_EXCLUSIVE) {
      allowedQueueFamilyIndices.clear();
    }

    VkSwapchainCreateInfoKHR const createInfo{
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .pNext = nullptr,
        .flags = 0u,
        .surface = surface.handle(),
        .minImageCount = actualImageCount,
        .imageFormat = format.format,
        .imageColorSpace = format.colorSpace,
        .imageExtent = extent,
        .imageArrayLayers = _imageLayerCount,
        .imageUsage = _usageFlags,
        .imageSharingMode = imageSharingMode,
        .queueFamilyIndexCount = static_cast<std::uint32_t>(allowedQueueFamilyIndices.size()),
        .pQueueFamilyIndices = allowedQueueFamilyIndices.data(),
        .preTransform = capabilities.currentTransform,
        .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
        .presentMode = presentMode,
        .clipped = VK_TRUE,
        .oldSwapchain = VK_NULL_HANDLE,
    };

    VkSwapchainKHR handle;
    if (auto const result = fns.vkCreateSwapchainKHR(_device.handle(), &createInfo, allocationCallbacks, &handle);
        result != VK_SUCCESS) {
      return Unexpected{result};
    }

    return {_device, allocationCallbacks, handle, format.format};
  });
#endif
}

auto SwapChain::images() const noexcept -> Expected<Vector<FormattedImage>, VkResult> {
#ifndef VK_KHR_swapchain
  return Unexpected{VK_ERROR_EXTENSION_NOT_PRESENT};
#else
  auto const& fns = device().functions();
  assert(fns.vkGetSwapchainImagesKHR && "undefined behavior");

  Vector<VkImage> imageHandles;
  std::uint32_t imageCount;
  if (auto const result = fns.vkGetSwapchainImagesKHR(device().handle(), handle(), &imageCount, nullptr);
      result != VK_SUCCESS) {
    return Unexpected{result};
  }

  imageHandles.resize(imageCount);
  if (auto const result = fns.vkGetSwapchainImagesKHR(device().handle(), handle(), &imageCount, imageHandles.data());
      result != VK_SUCCESS) {
    return Unexpected{result};
  }

  return Vector<FormattedImage>{imageHandles | project([this](auto const handle) {
    return FormattedImage{device(), handle, imageFormat()};
  })};
#endif
}

} // namespace c_eng::api::vk::detail

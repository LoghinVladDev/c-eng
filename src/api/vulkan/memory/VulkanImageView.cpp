//
// Created by loghin on 6/7/25.
//

#include "VulkanImageView.hpp"

#include <device/VulkanLogicalDevice.hpp>
#include <memory/VulkanImage.hpp>

#include <core/VulkanHandles.hpp>

namespace c_eng::api::vk::detail {
namespace {
using cds::Unexpected;
} // namespace

ImageView::~ImageView() noexcept {
  assert(device().functions().vkDestroyImageView && "undefined behavior");
  if (handle()) {
    device().functions().vkDestroyImageView(device().handle(), handle(), allocationCallbacks());
  }
}

auto ImageViewBuilder::build(Image const& image, VkFormat format) noexcept -> Expected<ImageView, VkResult> {
  auto const& fns = _device.functions();
  assert(fns.vkCreateImageView && fns.vkDestroyImageView && "undefined behavior");

  auto const allocationCallbacks = _allocationCallbacks.getOr(_device.allocationCallbacks());

  VkImageViewCreateInfo createInfo {
      .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0u,
      .image = image.handle(),
      .viewType = VK_IMAGE_VIEW_TYPE_2D,
      .format = format,
      .components = {
          .r = VK_COMPONENT_SWIZZLE_IDENTITY,
          .g = VK_COMPONENT_SWIZZLE_IDENTITY,
          .b = VK_COMPONENT_SWIZZLE_IDENTITY,
          .a = VK_COMPONENT_SWIZZLE_IDENTITY,
      },
      .subresourceRange = {
          .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
          .baseMipLevel = 0u,
          .levelCount = 1u,
          .baseArrayLayer = 0u,
          .layerCount = 1u
      }
  };

  VkImageView handle;
  if (auto const result = fns.vkCreateImageView(_device.handle(), &createInfo, allocationCallbacks, &handle);
      result != VK_SUCCESS) {
    return Unexpected{result};
  }
  return {_device, image, allocationCallbacks, handle};
}

auto ImageViewBuilder::build(FormattedImage const& image) noexcept -> Expected<ImageView, VkResult> {
  return build(image, image.format());
}
} // namespace c_eng::api::vk::detail

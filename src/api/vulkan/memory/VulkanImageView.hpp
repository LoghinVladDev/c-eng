//
// Created by loghin on 6/7/25.
//

#pragma once

#include <cds/Optional>
#include <core/VulkanSubunits.hpp>
#include <ext/cds/Expected.hpp>

namespace c_eng::api::vk::detail {
class Image;
class ImageViewBuilder;
class LogicalDevice;

using cds::Optional;
using cds::experimental::Expected;
using cds::nullopt;

class ImageView :
    public VulkanObject<SubObject<LogicalDevice, Image>, WithAllocationCallbacks, WrapsVulkanHandle<VkImageView>> {
public:
  using VulkanObject::VulkanObject;
  ~ImageView() noexcept;

  [[nodiscard]] constexpr static auto builder(LogicalDevice const& device) noexcept -> ImageViewBuilder;
};

class ImageViewBuilder {
public:
  explicit constexpr ImageViewBuilder(LogicalDevice const& device) noexcept : _device{device} {}

  auto& withAllocationCallbacks(VkAllocationCallbacks const* pAllocationCallbacks) noexcept {
    _allocationCallbacks = pAllocationCallbacks;
    return *this;
  }

  [[nodiscard]] auto build(Image const& image) noexcept -> Expected<ImageView, VkResult>;

private:
  LogicalDevice const& _device;
  Optional<VkAllocationCallbacks const*> _allocationCallbacks{nullopt};
};

constexpr auto ImageView::builder(LogicalDevice const& device) noexcept -> ImageViewBuilder {
  return ImageViewBuilder{device};
}
} // namespace c_eng::api::vk::detail

namespace c_eng::api::vk {
using detail::ImageView;
} // namespace c_eng::api::vk

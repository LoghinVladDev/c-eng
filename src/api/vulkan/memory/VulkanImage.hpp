//
// Created by loghin on 6/3/25.
//

#pragma once

#include <core/VulkanSubunits.hpp>

namespace c_eng::api::vk::detail {
class LogicalDevice;

class Image : public VulkanObject<SubObject<LogicalDevice>, WrapsVulkanHandle<VkImage>> {
public:
  using VulkanObject::VulkanObject;
};

class FormattedImage : public Image {
public:
  constexpr FormattedImage(LogicalDevice const& device, VkImage handle, VkFormat format, VkExtent2D extent) noexcept :
      Image{device, handle}, _format{format}, _extent{extent} {}
  constexpr FormattedImage(Image const& image, VkFormat format, VkExtent2D extent) noexcept :
      Image{image}, _format{format}, _extent{extent} {}

  FormattedImage(FormattedImage const&) = default;
  FormattedImage(FormattedImage&&) = default;

  [[nodiscard]] constexpr auto format() const noexcept {
    return _format;
  }

  [[nodiscard]] constexpr auto extent() const noexcept {
    return _extent;
  }

private:
  VkFormat _format{VK_FORMAT_UNDEFINED};
  VkExtent2D _extent{0u, 0u};
};
} // namespace c_eng::api::vk::detail

namespace c_eng::api::vk {
using detail::Image;
} // namespace c_eng::api::vk

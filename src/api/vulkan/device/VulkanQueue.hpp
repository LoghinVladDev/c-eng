//
// Created by loghin on 18.04.2025.
//

#pragma once

#include <core/VulkanSubunits.hpp>
#include <ext/cds/Expected.hpp>

namespace c_eng::api::vk::detail {
using cds::U32;
using cds::experimental::Expected;

class PhysicalDevice;
class Surface;

class QueueFamily : public VulkanObject<SubObject<PhysicalDevice>> {
public:
  constexpr QueueFamily(
      PhysicalDevice const& device,
      U32 const index,
      VkQueueFamilyProperties const& properties
  ) noexcept : VulkanObject{device}, _index{index}, _properties{properties} {}

  [[nodiscard]] constexpr auto index() const noexcept {
    return _index;
  }

  [[nodiscard]] constexpr auto const& properties() const noexcept {
    return _properties;
  }

  [[nodiscard]] constexpr auto hasFlag(VkQueueFlagBits const flagBit) const noexcept {
    return 0 != (properties().queueFlags & flagBit);
  }

  [[nodiscard]] constexpr auto supportsGraphics() const noexcept {
    return hasFlag(VK_QUEUE_GRAPHICS_BIT);
  }

  [[nodiscard]] constexpr auto supportsTransfer() const noexcept {
    return hasFlag(VK_QUEUE_TRANSFER_BIT);
  }

  [[nodiscard]] auto supportsPresentOn(Surface const& surface) const noexcept -> Expected<bool, VkResult>;

private:
  U32 _index {0u};
  VkQueueFamilyProperties _properties{};
};
} // namespace c_eng::api::vk::detail

namespace c_eng::api::vk {
using detail::QueueFamily;
} // namespace c_eng::api::vk

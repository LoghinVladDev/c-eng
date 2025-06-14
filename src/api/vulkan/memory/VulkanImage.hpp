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
} // namespace c_eng::api::vk::detail

namespace c_eng::api::vk {
using detail::Image;
} // namespace c_eng::api::vk

//
// Created by loghin on 18.04.2025.
//

#pragma once

#include <api/vulkan/core/VulkanCorePredecl.hpp>
#include <generic/api/Api.hpp>

namespace c_eng::api::vk::detail {
using generic::Api;

class Instance : public Api {
public:
  // explicit Instance(vk::Instance handle) {}
};
} // namespace c_eng::api::vk::detail

namespace c_eng::api::vk {

} // namespace c_eng::api::vk

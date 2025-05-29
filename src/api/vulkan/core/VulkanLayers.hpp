//
// Created by loghin on 5/27/25.
//

#pragma once

#include <cds/functional/Hash>

namespace c_eng::api::vk::detail {

#define C_ENG_VULKAN_LAYER(_name) _name,

enum class Layer {
#include "VulkanLayers.def"
};
#undef C_ENG_VULKAN_LAYER

template <Layer> struct LayerTraits {};

#define C_ENG_VULKAN_LAYER(_name)               \
  template <> struct LayerTraits<Layer::_name> {\
    static constexpr auto name = "VK_" #_name;  \
  };

#include "VulkanLayers.def"

#undef C_ENG_VULKAN_LAYER
} // namespace c_eng::api::vk::detail

template <> struct cds::functional::Hash<c_eng::api::vk::detail::Layer> {
  [[nodiscard]] constexpr auto operator()(c_eng::api::vk::detail::Layer layer) const noexcept {
    return Hash<U64>{}(static_cast<U64>(layer));
  }
};

//
// Created by loghin on 11/14/24.
//

#pragma once

#include "VulkanTypes.hpp"
#include <generic/TypesToString.hpp>

namespace c_eng::generic::detail {
using cds::String;
using cds::U32;

template <> struct ToString<VkLayerProperties> : True {
  auto operator()(VkLayerProperties const& properties) const noexcept {
    return R"(VkLayerProperties{{name="{}", targetSpecVersion={}, revision={}, description="{}"}})"_f(
      static_cast<char const*>(properties.layerName), toVersion(properties.specVersion),
      properties.implementationVersion, static_cast<char const*>(properties.description)
    );
  }
};
} // namespace c_eng::genric::detail

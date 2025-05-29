//
// Created by loghin on 5/27/25.
//

#pragma once

#include <cds/functional/Hash>

namespace c_eng::api::vk::detail {
enum class ExtensionOriginType {Base, EXT, KHR, MVK};

template <ExtensionOriginType> struct OriginTraits {};


#define C_ENG_VULKAN_EXTENSION(_origin, _name) _origin ## _ ## _name,
enum class Extension {
  Base,
#include "VulkanExtensions.def"
  Count,
};
#undef C_ENG_VULKAN_EXTENSION

template <Extension> struct ExtensionTraits {};

template <> struct ExtensionTraits<Extension::Base> {
  static constexpr auto name = "base_vulkan";
  static constexpr auto origin = ExtensionOriginType::Base;
};

#define C_ENG_VULKAN_EXTENSION(_origin, _name)                            \
  template <> struct ExtensionTraits<Extension::_origin ## _ ## _name> {  \
    static constexpr auto name = "VK_" #_origin "_" #_name;               \
    static constexpr auto origin = ExtensionOriginType::_origin;          \
  };

#include "VulkanExtensions.def"

#undef C_ENG_VULKAN_EXTENSION
} // namespace c_eng::api::vk::detail

template <> struct cds::functional::Hash<c_eng::api::vk::detail::Extension> {
  [[nodiscard]] constexpr auto operator()(c_eng::api::vk::detail::Extension extension) const noexcept {
    return Hash<U64>{}(static_cast<U64>(extension));
  }
};

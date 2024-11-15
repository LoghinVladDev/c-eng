//
// Created by loghin on 11/14/24.
//

#pragma once

#include <cds/meta/Compiler>
#include <generic/Types.hpp>
#include <vulkan/vulkan_core.h>

namespace c_eng::generic::detail {
using cds::U32;

inline auto toVersion(U32 id) noexcept -> Version {
  return {
    .variant = VK_API_VERSION_VARIANT(id),
    .major = VK_API_VERSION_MAJOR(id),
    .minor = VK_API_VERSION_MINOR(id),
    .patch = VK_API_VERSION_PATCH(id)
  };
}

inline auto fromVersion(Version const& version) noexcept -> U32 {
  return VK_MAKE_API_VERSION(version.variant, version.major, version.minor, version.patch);
}
} // namespace c_eng::genric::detail

namespace c_eng::generic {
using detail::fromVersion;
using detail::toVersion;
}

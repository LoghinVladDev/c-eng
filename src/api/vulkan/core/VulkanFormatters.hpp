//
// Created by vloghin on 19.04.2025.
//

#pragma once

#include <cds/Format>
#include "VulkanString.hpp"

#ifdef VK_VERSION_1_0
template <typename C> struct cds::Formatter<VkResult, C> {
  template <typename Ctx> auto format(VkResult result, Ctx const& ctx) noexcept -> typename Ctx::Iterator {
    auto const asStr = vk::toString(result);
    return impl::copy(asStr.begin(), asStr.end(), ctx.out());
  }
};
#endif

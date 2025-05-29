//
// Created by loghin on 18.04.2025.
//

#pragma once

#include <cds/Optional>
#include <core/VulkanSubunits.hpp>
#include <ext/cds/Expected.hpp>

#ifndef VK_KHR_surface
VK_DEFINE_HANDLE(VkSurfaceKHR)
#endif

namespace c_eng::generic::detail {
class Window;
} // namespace c_eng::generic::detail

namespace c_eng::api::vk::detail {
class Instance;

using cds::Optional;
using cds::experimental::Expected;
using cds::nullopt;

using generic::detail::Window;

class Surface : public VulkanObject<SubObject<Instance>, WithAllocationCallbacks, WrapsVulkanHandle<VkSurfaceKHR>> {
public:
  using VulkanObject::VulkanObject;
  ~Surface() noexcept;

  [[nodiscard]] static auto createSurface(
      Instance const& instance,
      Window const& window,
      Optional<VkAllocationCallbacks const*> pAllocationCallbacks = nullopt
  ) noexcept -> Expected<Surface, VkResult>;
};
} // namespace c_eng::api::vk::detail

namespace c_eng::api::vk {
using detail::Surface;
} // namespace c_eng::api::vk

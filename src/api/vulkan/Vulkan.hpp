//
// Created by loghin on 18.04.2025.
//

#pragma once

#include <source_location>
#include <cds/Format>
#include <cds/collection/Vector>
#include <ext/cds/Expected.hpp>
#include <ext/cds/StdFormatters.hpp>
#include <generic/log/Logger.hpp>
#include <vulkan/vulkan_core.h>

#include <api/vulkan/core/VulkanFormatters.hpp>

namespace c_eng::api::vk::detail {
using cds::experimental::Expected;
using cds::experimental::Unexpected;
using cds::impl::mv;
using cds::Vector;
using cds::U32;
using generic::LoggerRef;
using generic::LogLevel;

using namespace cds::literals;

class Vulkan {
public:
  class Builder;
  class InstanceBuilder;

  constexpr Vulkan(
      LoggerRef const logger,
      PFN_vkGetInstanceProcAddr const pfnGetInstanceProcAddr,
      PFN_vkEnumerateInstanceLayerProperties const pfnEnumerateInstanceLayerProperties,
      VkAllocationCallbacks const* pAllocationCallbacks
  ) noexcept :
      _pAllocationCallbacks{pAllocationCallbacks}, _pfnGetInstanceProcAddr{pfnGetInstanceProcAddr},
      _pfnEnumerateInstanceLayerProperties{pfnEnumerateInstanceLayerProperties}, _logger{logger} {}

  constexpr ~Vulkan() noexcept = default;

  [[nodiscard]] static constexpr auto builder() noexcept -> Builder;
  [[nodiscard]] auto layerProperties() noexcept -> Expected<Vector<VkLayerProperties>, VkResult>;

private:
  VkAllocationCallbacks const* _pAllocationCallbacks {nullptr};
  PFN_vkGetInstanceProcAddr _pfnGetInstanceProcAddr {nullptr};
  PFN_vkEnumerateInstanceLayerProperties _pfnEnumerateInstanceLayerProperties {nullptr};

  LoggerRef _logger {};
};

class Vulkan::Builder {
public:
  [[nodiscard]] auto withLogger(LoggerRef logger) noexcept -> Builder& {
    _logger = mv(logger);
    return *this;
  }

  [[nodiscard]] constexpr auto withAllocationCallbacks(VkAllocationCallbacks const* pAllocationCallbacks) noexcept
      -> Builder& {
    _pAllocationCallbacks = pAllocationCallbacks;
    return *this;
  }

  [[nodiscard]] auto build() noexcept -> Expected<Vulkan, VkResult>;

private:
  VkAllocationCallbacks const* _pAllocationCallbacks {nullptr};
  LoggerRef _logger {};
};

constexpr auto Vulkan::builder() noexcept -> Builder {
  return {};
}

inline auto Vulkan::layerProperties() noexcept -> Expected<Vector<VkLayerProperties>, VkResult> {
  U32 count = 0;
  if (auto result = _pfnEnumerateInstanceLayerProperties(&count, nullptr);
      result != VK_SUCCESS) {
    _logger(LogLevel::Error) << _logger.invoke(
        "[{}] Failed to query number of layer properties: {}"_f,
        std::source_location::current(), result
    );
    return Unexpected{result};
  }
}

} // namespace c_eng::api::vk::detail

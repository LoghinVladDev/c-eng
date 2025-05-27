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
using cds::impl::xch;
using cds::Vector;
using cds::U32;

using generic::LoggerRef;
using generic::LogLevel;

using namespace cds::literals;

class VulkanBuilder;
class InstanceBuilder;

struct VulkanGlobalFnPtrs {
  PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr{&::vkGetInstanceProcAddr};
  PFN_vkEnumerateInstanceVersion vkEnumerateInstanceVersion{nullptr};
  PFN_vkEnumerateInstanceLayerProperties vkEnumerateInstanceLayerProperties{nullptr};
  PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties{nullptr};
  PFN_vkCreateInstance vkCreateInstance{nullptr};
};

class Vulkan {
public:
  constexpr Vulkan(
      LoggerRef const logger,
      VulkanGlobalFnPtrs const& pfns,
      VkAllocationCallbacks const* pAllocationCallbacks
  ) noexcept :
      _pAllocationCallbacks{pAllocationCallbacks}, _pfns{pfns}, _logger{logger} {}

  constexpr ~Vulkan() noexcept = default;

  [[nodiscard]] static constexpr auto builder() noexcept -> VulkanBuilder;
  [[nodiscard]] auto layerProperties() const noexcept -> Expected<Vector<VkLayerProperties>, VkResult>;
  [[nodiscard]] auto instanceBuilder() const noexcept -> InstanceBuilder;
  [[nodiscard]] constexpr auto allocationCallbacks() const noexcept {
    return _pAllocationCallbacks;
  }

  [[nodiscard]] constexpr auto functions() const noexcept -> VulkanGlobalFnPtrs const& {
    return _pfns;
  }

private:
  VkAllocationCallbacks const* _pAllocationCallbacks {nullptr};
  VulkanGlobalFnPtrs _pfns {};
  LoggerRef _logger {};
};

class VulkanBuilder {
public:
  [[nodiscard]] auto withLogger(LoggerRef logger) noexcept -> VulkanBuilder& {
    _logger = mv(logger);
    return *this;
  }

  [[nodiscard]] constexpr auto withAllocationCallbacks(VkAllocationCallbacks const* pAllocationCallbacks) noexcept
      -> VulkanBuilder& {
    _pAllocationCallbacks = pAllocationCallbacks;
    return *this;
  }

  [[nodiscard]] auto build() noexcept -> Expected<Vulkan, VkResult>;

private:
  VkAllocationCallbacks const* _pAllocationCallbacks {nullptr};
  LoggerRef _logger {};
};

constexpr auto Vulkan::builder() noexcept -> VulkanBuilder {
  return {};
}
} // namespace c_eng::api::vk::detail

namespace c_eng::api::vk {
using detail::Vulkan;
} // namespace c_eng::api::vk

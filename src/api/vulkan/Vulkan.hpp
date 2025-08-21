//
// Created by loghin on 18.04.2025.
//

#pragma once

#include <source_location>
#include <cds/Expected>
#include <cds/Format>
#include <cds/collection/Vector>
#include <ext/cds/StdFormatters.hpp>
#include <generic/log/Logger.hpp>
#include <vulkan/vulkan_core.h>

#include <api/vulkan/core/VulkanFormatters.hpp>

namespace c_eng::api::vk::detail {
using cds::Expected;
using cds::Vector;
using cds::U32;
using cds::impl::mv;
using cds::impl::xch;

using generic::LoggerRef;
using generic::LogLevel;

using namespace cds::literals;

class VulkanBuilder;
class InstanceBuilder;

struct GlobalFnPtrs;

class Vulkan {
public:
  constexpr Vulkan(
      LoggerRef const logger,
      GlobalFnPtrs const* pfns,
      VkAllocationCallbacks const* pAllocationCallbacks
  ) noexcept :
      _pAllocationCallbacks{pAllocationCallbacks}, _pfns{pfns}, _logger{logger} {}

  Vulkan(Vulkan const&) = delete;
  constexpr Vulkan(Vulkan&& vk) noexcept :
      _pAllocationCallbacks{xch(vk._pAllocationCallbacks, nullptr)},
      _pfns{xch(vk._pfns, nullptr)},
      _logger{mv(vk._logger)} {}

  ~Vulkan() noexcept;

  [[nodiscard]] static constexpr auto builder() noexcept -> VulkanBuilder;
  [[nodiscard]] auto layerProperties() const noexcept -> Expected<Vector<VkLayerProperties>, VkResult>;
  [[nodiscard]] auto instanceBuilder() const noexcept -> InstanceBuilder;
  [[nodiscard]] constexpr auto allocationCallbacks() const noexcept {
    return _pAllocationCallbacks;
  }

  [[nodiscard]] constexpr auto functions() const noexcept -> GlobalFnPtrs const& {
    assert(_pfns && "undefined behavior");
    return *_pfns;
  }

private:
  VkAllocationCallbacks const* _pAllocationCallbacks {nullptr};
  GlobalFnPtrs const* _pfns {nullptr};
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

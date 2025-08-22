//
// Created by loghin on 8/21/25.
//

#pragma once

#include <cds/Expected>
#include <cds/Optional>
#include <core/VulkanSubunits.hpp>

namespace c_eng::api::vk::detail {
using cds::Expected;
using cds::Optional;
using cds::nullopt;

class LogicalDevice;
class PipelineLayoutBuilder;

class PipelineLayout :
    public VulkanObject<SubObject<LogicalDevice>, WithAllocationCallbacks, WrapsVulkanHandle<VkPipelineLayout>> {
public:
  using VulkanObject::VulkanObject;
  PipelineLayout(PipelineLayout&&) = default;
  ~PipelineLayout() noexcept;

  [[nodiscard]] static constexpr auto builder(LogicalDevice const& device) noexcept -> PipelineLayoutBuilder;
};

class PipelineLayoutBuilder {
public:
  explicit constexpr PipelineLayoutBuilder(LogicalDevice const& device) noexcept : _device{device} {}

  auto& withAllocationCallbacks(VkAllocationCallbacks const* pAllocationCallbacks) noexcept {
    _allocationCallbacks = pAllocationCallbacks;
    return *this;
  }

  [[nodiscard]] auto build() const noexcept -> Expected<PipelineLayout, VkResult>;

private:
  LogicalDevice const& _device;
  Optional<VkAllocationCallbacks const*> _allocationCallbacks{nullopt};
};

constexpr auto PipelineLayout::builder(LogicalDevice const& device) noexcept -> PipelineLayoutBuilder {
  return PipelineLayoutBuilder{device};
}
} // namespace c_eng::api::vk::detail

namespace c_eng::api::vk {
using detail::PipelineLayout;
using detail::PipelineLayoutBuilder;
} // namespace c_eng::api::vk

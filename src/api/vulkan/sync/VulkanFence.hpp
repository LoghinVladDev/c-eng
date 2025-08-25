//
// Created by loghin on 8/25/25.
//

#pragma once

#include <cds/Expected>
#include <core/VulkanBuilders.hpp>
#include <core/VulkanSubunits.hpp>

namespace c_eng::api::vk::detail {
using cds::Expected;
using cds::Size;

class LogicalDevice;
class FenceBuilder;

class Fence :
    public VulkanObject<SubObject<LogicalDevice>, WithAllocationCallbacks, WrapsVulkanHandle<VkFence>>{
public:
  using VulkanObject::VulkanObject;
  Fence(Fence&&) = default;
  ~Fence() noexcept;

  auto reset() const noexcept -> VkResult;
  auto wait(Size timeout = cds::limits::u64Max) const noexcept -> VkResult;

  [[nodiscard]] static constexpr auto builder(LogicalDevice const& device) noexcept -> FenceBuilder;
};

class FenceBuilder :
    public VulkanObjectBuilder<FenceBuilder, Requiring<LogicalDevice>, WithAllocationCallbacks> {
public:
  using VulkanObjectBuilder::VulkanObjectBuilder;

  auto& signalled() noexcept {
    _signalled = true;
    return *this;
  }

  [[nodiscard]] auto build() const noexcept -> Expected<Fence, VkResult>;

private:
  bool _signalled{false};
};

constexpr auto Fence::builder(LogicalDevice const& device) noexcept -> FenceBuilder {
  return FenceBuilder{device};
}
} // namespace c_eng::api::vk::detail

namespace c_eng::api::vk {
using detail::Fence;
using detail::FenceBuilder;
} // namespace c_eng::api::vk

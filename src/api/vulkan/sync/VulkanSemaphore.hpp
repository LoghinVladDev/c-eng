//
// Created by loghin on 8/25/25.
//

#pragma once

#include <cds/Expected>
#include <core/VulkanBuilders.hpp>
#include <core/VulkanSubunits.hpp>

namespace c_eng::api::vk::detail {
using cds::Expected;

class LogicalDevice;
class SemaphoreBuilder;

class Semaphore :
    public VulkanObject<SubObject<LogicalDevice>, WithAllocationCallbacks, WrapsVulkanHandle<VkSemaphore>>{
public:
  using VulkanObject::VulkanObject;
  Semaphore(Semaphore&&) = default;
  ~Semaphore() noexcept;

  [[nodiscard]] static constexpr auto builder(LogicalDevice const& device) noexcept -> SemaphoreBuilder;
};

class SemaphoreBuilder :
    public VulkanObjectBuilder<SemaphoreBuilder, Requiring<LogicalDevice>, WithAllocationCallbacks> {
public:
  using VulkanObjectBuilder::VulkanObjectBuilder;

  [[nodiscard]] auto build() const noexcept -> Expected<Semaphore, VkResult>;
};

constexpr auto Semaphore::builder(LogicalDevice const& device) noexcept -> SemaphoreBuilder {
  return SemaphoreBuilder{device};
}
} // namespace c_eng::api::vk::detail

namespace c_eng::api::vk {
using detail::Semaphore;
using detail::SemaphoreBuilder;
} // namespace c_eng::api::vk

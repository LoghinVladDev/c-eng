//
// Created by loghin on 8/23/25.
//

#pragma once

#include <cds/Expected>
#include <cds/Optional>
#include <core/VulkanBuilders.hpp>
#include <core/VulkanSubunits.hpp>

namespace c_eng::api::vk::detail {
using cds::Expected;
using cds::Optional;
using cds::nullopt;

class CommandBufferAllocator;
class CommandPoolBuilder;
class LogicalDevice;
class QueueFamily;

class CommandPool : public VulkanObject<
    SubObject<LogicalDevice, QueueFamily>,
    WithAllocationCallbacks,
    WrapsVulkanHandle<VkCommandPool>
> {
public:
  using VulkanObject::VulkanObject;
  CommandPool(CommandPool&&) = default;
  ~CommandPool() noexcept;

  [[nodiscard]] auto allocator() const noexcept -> CommandBufferAllocator;

  [[nodiscard]] static constexpr auto builder(LogicalDevice const& device) noexcept -> CommandPoolBuilder;
};

class CommandPoolBuilder :
    public VulkanObjectBuilder<CommandPoolBuilder, Requiring<LogicalDevice>, WithAllocationCallbacks> {
public:
  using VulkanObjectBuilder::VulkanObjectBuilder;

  [[nodiscard]] auto build(QueueFamily const& graphicsFamily) const noexcept -> Expected<CommandPool, VkResult>;
};

constexpr auto CommandPool::builder(LogicalDevice const& device) noexcept -> CommandPoolBuilder {
  return CommandPoolBuilder{device};
}
} // namespace c_eng::api::vk::detail

namespace c_eng::api::vk {
using detail::CommandPool;
using detail::CommandPoolBuilder;
} // namespace c_eng::api::vk

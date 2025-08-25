//
// Created by loghin on 8/23/25.
//

#include "VulkanCommandPool.hpp"

#include <device/VulkanLogicalDevice.hpp>
#include <device/VulkanQueueFamily.hpp>
#include <renderer/command/VulkanCommandBuffer.hpp>
#include <core/VulkanHandles.hpp>

namespace c_eng::api::vk::detail {
namespace {
using cds::Unexpected;
} // namespace

CommandPool::~CommandPool() noexcept {
  assert(device().functions().vkDestroyCommandPool && "undefined behavior");
  device().functions().vkDestroyCommandPool(device().handle(), handle(), allocationCallbacks());
}

auto CommandPoolBuilder::build(QueueFamily const& graphicsFamily) const noexcept -> Expected<CommandPool, VkResult> {
  if (!graphicsFamily.supportsGraphics()) {
    return Unexpected{VkResult::VK_ERROR_NOT_PERMITTED};
  }

  auto const& fns = device().functions();
  assert(fns.vkCreateCommandPool && fns.vkDestroyCommandPool && "undefined behavior");
  auto const allocator = allocationCallbacks().getOr(device().allocationCallbacks());

  auto const createInfo = VkCommandPoolCreateInfo{
      .sType = VkStructureType::VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
      .pNext = nullptr,
      .flags = VkCommandPoolCreateFlagBits::VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
      .queueFamilyIndex = graphicsFamily.index()
  };

  VkCommandPool handle;
  if (auto const result = fns.vkCreateCommandPool(device().handle(), &createInfo, allocator, &handle);
      result != VkResult::VK_SUCCESS) {
    return Unexpected{result};
  }

  return {device(), graphicsFamily, allocator, handle};
}

auto CommandPool::allocator() const noexcept -> CommandBufferAllocator {
  return CommandBufferAllocator{*this};
}
} // namespace c_eng::api::vk::detail

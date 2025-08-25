//
// Created by loghin on 8/25/25.
//

#include "VulkanFence.hpp"
#include <device/VulkanLogicalDevice.hpp>
#include <core/VulkanHandles.hpp>

namespace c_eng::api::vk::detail {
namespace {
using cds::Unexpected;
} // namespace

Fence::~Fence() noexcept {
  assert(device().functions().vkDestroyFence && "undefined behavior");
  device().functions().vkDestroyFence(device().handle(), handle(), allocationCallbacks());
}

auto FenceBuilder::build() const noexcept -> Expected<Fence, VkResult> {
  auto const& fns = device().functions();
  assert(fns.vkCreateFence && fns.vkDestroyFence && "undefined behavior");
  auto const alloc = allocationCallbacks().getOr(device().allocationCallbacks());

  auto const createInfo = VkFenceCreateInfo {
      .sType = VkStructureType::VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
      .pNext = nullptr,
      .flags = _signalled ? VkFenceCreateFlagBits::VK_FENCE_CREATE_SIGNALED_BIT : 0u
  };

  VkFence handle;
  if (auto const result = fns.vkCreateFence(device().handle(), &createInfo, alloc, &handle);
      result != VkResult::VK_SUCCESS) {
    return Unexpected{result};
  }

  return {device(), alloc, handle};
}

auto Fence::reset() const noexcept -> VkResult {
  auto fence = handle();
  return device().resetFences(VectorView{&fence, &fence + 1});
}

auto Fence::wait(Size timeout) const noexcept -> VkResult {
  auto fence = handle();
  return device().waitForAllFences(timeout, VectorView{&fence, &fence + 1});
}
} // namespace c_eng::api::vk::detail

//
// Created by loghin on 8/25/25.
//

#include "VulkanSemaphore.hpp"
#include <device/VulkanLogicalDevice.hpp>
#include <core/VulkanHandles.hpp>

namespace c_eng::api::vk::detail {
namespace {
using cds::Unexpected;
} // namespace

Semaphore::~Semaphore() noexcept {
  assert(device().functions().vkDestroySemaphore && "undefined behavior");
  device().functions().vkDestroySemaphore(device().handle(), handle(), allocationCallbacks());
}

auto SemaphoreBuilder::build() const noexcept -> Expected<Semaphore, VkResult> {
  auto const& fns = device().functions();
  assert(fns.vkCreateSemaphore && fns.vkDestroySemaphore && "undefined behavior");
  auto const alloc = allocationCallbacks().getOr(device().allocationCallbacks());

  auto const createInfo = VkSemaphoreCreateInfo {
      .sType = VkStructureType::VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0u
  };

  VkSemaphore handle;
  if (auto const result = fns.vkCreateSemaphore(device().handle(), &createInfo, alloc, &handle);
      result != VkResult::VK_SUCCESS) {
    return Unexpected{result};
  }

  return {device(), alloc, handle};
}
} // namespace c_eng::api::vk::detail

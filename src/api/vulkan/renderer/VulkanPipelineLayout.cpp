//
// Created by loghin on 8/21/25.
//

#include "VulkanPipelineLayout.hpp"
#include <device/VulkanLogicalDevice.hpp>
#include <core/VulkanHandles.hpp>

namespace c_eng::api::vk::detail {
using cds::Unexpected;

PipelineLayout::~PipelineLayout() noexcept {
  assert(device().functions().vkDestroyPipelineLayout && "undefined behavior");
  device().functions().vkDestroyPipelineLayout(device().handle(), handle(), allocationCallbacks());
}

auto PipelineLayoutBuilder::build() const noexcept -> Expected<PipelineLayout, VkResult> {
  auto const& fns = _device.functions();
  auto const allocationCallbacks = _allocationCallbacks.getOr(_device.allocationCallbacks());

  auto const createInfo = VkPipelineLayoutCreateInfo {
      .sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0u,
      .setLayoutCount = 0u,
      .pSetLayouts = nullptr,
      .pushConstantRangeCount = 0u,
      .pPushConstantRanges = nullptr
  };

  VkPipelineLayout handle;
  if (auto const result = fns.vkCreatePipelineLayout(_device.handle(), &createInfo, allocationCallbacks, &handle);
      result != VkResult::VK_SUCCESS) {
    return Unexpected{result};
  }

  return {_device, allocationCallbacks, handle};
}
} // namespace c_eng::api::vk::detail

//
// Created by loghin on 8/23/25.
//

#include "VulkanCommandBuffer.hpp"

#include <device/VulkanLogicalDevice.hpp>
#include <memory/VulkanImage.hpp>
#include <renderer/command/VulkanCommandPool.hpp>
#include <renderer/VulkanPipeline.hpp>
#include <core/VulkanHandles.hpp>

namespace c_eng::api::vk::detail {
namespace {
using cds::Unexpected;

auto allocate(
    CommandPool const& pool,
    VkCommandBufferLevel level,
    Size count
) noexcept -> Expected<CommandBufferVector, VkResult> {
  auto const& fns = pool.device().functions();
  assert(fns.vkAllocateCommandBuffers && fns.vkFreeCommandBuffers && "undefined behavior");

  auto const allocateInfo = VkCommandBufferAllocateInfo {
      .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
      .pNext = nullptr,
      .commandPool = pool.handle(),
      .level = level,
      .commandBufferCount = static_cast<std::uint32_t>(count),
  };

  CommandBufferVector buffers{pool, count};
  if (auto const result = fns.vkAllocateCommandBuffers(pool.device().handle(), &allocateInfo, buffers.data());
      result != VkResult::VK_SUCCESS) {
    return Unexpected{result};
  }

  return mv(buffers);
}
} // namespace

CommandBufferVector::~CommandBufferVector() noexcept {
  assert(pool().device().functions().vkFreeCommandBuffers && "undefined behavior");
  if (!empty()) {
    pool().device().functions().vkFreeCommandBuffers(
        pool().device().handle(),
        pool().handle(),
        static_cast<std::uint32_t>(size()),
        data()
    );
  }
}

auto CommandBufferAllocator::allocatePrimary(Size count) const noexcept -> Expected<CommandBufferVector, VkResult> {
  return allocate(pool(), VkCommandBufferLevel::VK_COMMAND_BUFFER_LEVEL_PRIMARY, count);
}

auto CommandBufferAllocator::allocateSecondary(Size count) const noexcept -> Expected<CommandBufferVector, VkResult> {
  return allocate(pool(), VkCommandBufferLevel::VK_COMMAND_BUFFER_LEVEL_SECONDARY, count);
}

auto CommandBufferRef::record(FunctionRef<void(Recorder&)> recordCallback) const noexcept
    -> Expected<CommandBufferRef, VkResult> {
  auto const& fns = pool().device().functions();
  assert(fns.vkBeginCommandBuffer && fns.vkEndCommandBuffer && "undefined behavior");

  auto recorder = Recorder{*this};
  auto const beginInfo = VkCommandBufferBeginInfo{
      .sType = VkStructureType::VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
      .pNext = nullptr,
      .flags = 0u,
      .pInheritanceInfo = nullptr
  };

  if (auto const result = fns.vkBeginCommandBuffer(handle(), &beginInfo);
      result != VkResult::VK_SUCCESS) {
    return Unexpected{result};
  }

  recordCallback(recorder);
  if (auto const result = fns.vkEndCommandBuffer(handle());
      result != VkResult::VK_SUCCESS) {
    return Unexpected{result};
  }

  return *this;
}

auto CommandRecorder::transitionImageLayout(
    Image const& image,
    VkImageLayout oldLayout,
    VkImageLayout newLayout,
    VkAccessFlags2 srcAccessMask,
    VkAccessFlags2 dstAccessMask,
    VkPipelineStageFlags2 srcStageMask,
    VkPipelineStageFlags2 dstStageMask
) const noexcept -> void {
  assert(buffer().pool().device().functions().vkCmdPipelineBarrier2 && "undefined behavior");

  auto const barrier = VkImageMemoryBarrier2 {
      .sType = VkStructureType::VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
      .pNext = nullptr,
      .srcStageMask = srcStageMask,
      .srcAccessMask = srcAccessMask,
      .dstStageMask = dstStageMask,
      .dstAccessMask = dstAccessMask,
      .oldLayout = oldLayout,
      .newLayout = newLayout,
      .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
      .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
      .image = image.handle(),
      .subresourceRange = {
          .aspectMask = VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT,
          .baseMipLevel = 0u,
          .levelCount = 1u,
          .baseArrayLayer = 0u,
          .layerCount = 1u
      }
  };

  auto const dependencyInfo = VkDependencyInfo{
      .sType = VkStructureType::VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
      .pNext = nullptr,
      .dependencyFlags = 0u,
      .memoryBarrierCount = 0u,
      .pMemoryBarriers = nullptr,
      .bufferMemoryBarrierCount = 0u,
      .pBufferMemoryBarriers = nullptr,
      .imageMemoryBarrierCount = 1u,
      .pImageMemoryBarriers = &barrier,
  };

  buffer().pool().device().functions().vkCmdPipelineBarrier2(buffer().handle(), &dependencyInfo);
}

auto CommandRecorder::beginRendering(VkRenderingInfo const& renderingInfo) const noexcept -> void {
  assert(buffer().pool().device().functions().vkCmdBeginRendering && "undefined behavior");
  buffer().pool().device().functions().vkCmdBeginRendering(buffer().handle(), &renderingInfo);
}

auto CommandRecorder::endRendering() const noexcept -> void {
  assert(buffer().pool().device().functions().vkCmdEndRendering && "undefined behavior");
  buffer().pool().device().functions().vkCmdEndRendering(buffer().handle());
}

auto CommandRecorder::bindPipeline(Pipeline const& pipeline) const noexcept -> void {
  assert(buffer().pool().device().functions().vkCmdBindPipeline && "undefined behavior");
  buffer().pool().device().functions().vkCmdBindPipeline(
      buffer().handle(),
      VkPipelineBindPoint::VK_PIPELINE_BIND_POINT_GRAPHICS,
      pipeline.handle()
  );
}

auto CommandRecorder::setViewport(VkViewport const& viewport) const noexcept -> void {
  assert(buffer().pool().device().functions().vkCmdSetViewport && "undefined behavior");
  buffer().pool().device().functions().vkCmdSetViewport(
      buffer().handle(),
      0u,
      1u,
      &viewport
  );
}

auto CommandRecorder::setScissor(VkRect2D const& scissor) const noexcept -> void {
  assert(buffer().pool().device().functions().vkCmdSetScissor && "undefined behavior");
  buffer().pool().device().functions().vkCmdSetScissor(
      buffer().handle(),
      0u,
      1u,
      &scissor
  );
}

auto CommandRecorder::draw(
    Size vertexCount,
    Size instanceCount,
    Size firstVertex,
    Size firstInstance
) const noexcept -> void {
  assert(buffer().pool().device().functions().vkCmdDraw && "undefined behavior");
  buffer().pool().device().functions().vkCmdDraw(
      buffer().handle(),
      static_cast<std::uint32_t>(vertexCount),
      static_cast<std::uint32_t>(instanceCount),
      static_cast<std::uint32_t>(firstVertex),
      static_cast<std::uint32_t>(firstInstance)
  );
}
} // namespace c_eng::api::vk::detail

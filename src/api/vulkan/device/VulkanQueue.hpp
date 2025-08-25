//
// Created by loghin on 18.04.2025.
//

#pragma once

#include <cds/Expected>
#include <cds/collection/VectorView>
#include <core/VulkanSubunits.hpp>

namespace c_eng::api::vk::detail {
using cds::Expected;
using cds::U32;
using cds::VectorView;

class Fence;
class LogicalDevice;
class QueueFamily;

#ifndef VK_KHR_swapchain
struct VkPresentInfoKHR{};
#endif

class Queue : public VulkanObject<SubObject<LogicalDevice, QueueFamily>, WrapsVulkanHandle<VkQueue>> {
public:
  constexpr Queue(LogicalDevice const& device, QueueFamily const& family, VkQueue queue, float priority) noexcept :
      VulkanObject{device, family, queue}, _priority{priority} {}

  Queue(Queue const&) = default;
  ~Queue() = default;

  [[nodiscard]] constexpr auto priority() const noexcept {
    return _priority;
  }

  [[nodiscard]] auto submit(VectorView<VkSubmitInfo const> info, Fence const& fence) const noexcept -> VkResult;
  [[nodiscard]] auto present(VkPresentInfoKHR const& info) const noexcept -> VkResult;

private:
  float _priority{0.0f};
};
} // namespace c_eng::api::vk::detail

namespace c_eng::api::vk {
using detail::Queue;
} // namespace c_eng::api::vk

//
// Created by loghin on 18.04.2025.
//

#pragma once

#include <core/VulkanSubunits.hpp>
#include <ext/cds/Expected.hpp>

namespace c_eng::api::vk::detail {
using cds::U32;
using cds::experimental::Expected;

class LogicalDevice;
class QueueFamily;

class Queue : public VulkanObject<SubObject<LogicalDevice, QueueFamily>, WrapsVulkanHandle<VkQueue>> {
public:
  constexpr Queue(LogicalDevice const& device, QueueFamily const& family, VkQueue queue, float priority) noexcept :
      VulkanObject{device, family, queue}, _priority{priority} {}

  Queue(Queue const&) = default;
  ~Queue() = default;

  [[nodiscard]] constexpr auto priority() const noexcept {
    return _priority;
  }

private:
  float _priority{0.0f};
};
} // namespace c_eng::api::vk::detail

namespace c_eng::api::vk {
using detail::Queue;
} // namespace c_eng::api::vk

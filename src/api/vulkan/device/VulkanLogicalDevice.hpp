//
// Created by loghin on 18.04.2025.
//

#pragma once

#include <cds/Expected>
#include <cds/Optional>
#include <cds/String>
#include <cds/StringView>
#include <cds/collection/HashMap>
#include <cds/collection/Vector>
#include <core/VulkanSubunits.hpp>
#include <generic/lang/Concepts.hpp>

namespace c_eng::api::vk::detail {
class Instance;
class Queue;
class QueueFamily;
class Surface;
class LogicalDeviceBuilder;
class SwapChainBuilder;

using cds::Expected;
using cds::HashMap;
using cds::Optional;
using cds::String;
using cds::StringView;
using cds::U32;
using cds::Vector;
using cds::impl::mv;
using cds::impl::xch;
using cds::nullopt;

using generic::concepts::IterableOf;

struct DeviceFnPtrs;

struct QueueDefinitionRange {
  QueueFamily const* pFamily;
  U32 offset;
  U32 length;
  float priority;
};

class LogicalDevice :
    public VulkanObject<SubObject<Instance, PhysicalDevice>, WithAllocationCallbacks, WrapsVulkanHandle<VkDevice>> {

public:
  constexpr LogicalDevice(
      Instance const& instance,
      PhysicalDevice const& device,
      VkAllocationCallbacks const* pAllocationCallbacks,
      VkDevice handle,
      DeviceFnPtrs const* fnPtrs,
      Vector<QueueDefinitionRange>&& ranges
  ) noexcept :
      VulkanObject{instance, device, pAllocationCallbacks, handle}, _pfns{fnPtrs},
      _queueDefinitionRanges{mv(ranges)} {}

  LogicalDevice(LogicalDevice const&) = delete;
  LogicalDevice(LogicalDevice&& device) noexcept :
      VulkanObject{mv(device)},
      _pfns{xch(device._pfns, nullptr)} {}

  ~LogicalDevice() noexcept;

  [[nodiscard]] static constexpr auto builder(Instance const& instance) noexcept -> LogicalDeviceBuilder;

  [[nodiscard]] constexpr auto functions() const noexcept -> DeviceFnPtrs const& {
    assert(_pfns && "undefined behavior");
    return *_pfns;
  }

  [[nodiscard]] auto swapChainBuilder() const noexcept -> SwapChainBuilder;

  [[nodiscard]] auto queues() const noexcept -> HashMap<QueueFamily, Vector<Queue>>;

private:
  DeviceFnPtrs const* _pfns{nullptr};
  Vector<QueueDefinitionRange> _queueDefinitionRanges{};
};

class LogicalDeviceBuilder {
public:
  explicit constexpr LogicalDeviceBuilder(Instance const& instance) noexcept : _instance{instance} {}
  LogicalDeviceBuilder(LogicalDeviceBuilder&&) = default;

  auto& addQueueFrom(QueueFamily const& family, float priority) noexcept {
    _plannedQueues[&family].emplaceBack(priority);
    return *this;
  }

  auto& withAllocationCallbacks(VkAllocationCallbacks const* pAllocationCallbacks) noexcept {
    _pAllocationCallbacks = pAllocationCallbacks;
    return *this;
  }

  template <IterableOf<StringView> Layers> auto& withLayers(Layers&& layers) noexcept {
    _layers = fwd<Layers>(layers);
    return *this;
  }

  template <IterableOf<StringView> Extensions> auto& withExtensions(Extensions&& extensions) noexcept {
    _extensions = fwd<Extensions>(extensions);
    return *this;
  }

#if defined(VK_VERSION_1_1)
  auto& withFeatures(VkPhysicalDeviceFeatures2 const& features) noexcept {
    _features2 = features;
    return *this;
  }
#endif

  [[nodiscard]] auto build(PhysicalDevice const& device) const noexcept -> Expected<LogicalDevice, VkResult>;

private:
  Instance const& _instance;
  Optional<VkAllocationCallbacks const*> _pAllocationCallbacks {nullopt};

  Vector<String> _extensions;
  Vector<String> _layers;

  HashMap<QueueFamily const*, Vector<float>> _plannedQueues{};

#if defined(VK_VERSION_1_1)
  Optional<VkPhysicalDeviceFeatures2> _features2{nullopt};
#endif
};

constexpr auto LogicalDevice::builder(Instance const& instance) noexcept -> LogicalDeviceBuilder {
  return LogicalDeviceBuilder{instance};
}
} // namespace c_eng::api::vk::detail

namespace c_eng::api::vk {
using detail::LogicalDevice;
} // namespace c_eng::api::vk

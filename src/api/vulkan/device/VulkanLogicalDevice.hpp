//
// Created by loghin on 18.04.2025.
//

#pragma once

#include <cds/Optional>
#include <cds/String>
#include <cds/StringView>
#include <cds/collection/HashMap>
#include <cds/collection/Vector>
#include <core/VulkanSubunits.hpp>
#include <ext/cds/Expected.hpp>
#include <generic/lang/Concepts.hpp>

namespace c_eng::api::vk::detail {
class Instance;
class QueueFamily;
class Surface;
class LogicalDeviceBuilder;
class SwapChainBuilder;

using cds::Optional;
using cds::HashMap;
using cds::String;
using cds::StringView;
using cds::Vector;
using cds::experimental::Expected;
using cds::impl::mv;
using cds::impl::xch;
using cds::nullopt;

using generic::concepts::IterableOf;

struct DeviceFnPtrs;

class LogicalDevice :
    public VulkanObject<SubObject<Instance, PhysicalDevice>, WithAllocationCallbacks, WrapsVulkanHandle<VkDevice>> {
public:
  constexpr LogicalDevice(
      Instance const& instance,
      PhysicalDevice const& device,
      VkAllocationCallbacks const* pAllocationCallbacks,
      DeviceFnPtrs const* fnPtrs,
      VkDevice handle
  ) noexcept : VulkanObject{instance, device, pAllocationCallbacks, handle}, _pfns{fnPtrs} {}

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

private:
  DeviceFnPtrs const* _pfns;
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

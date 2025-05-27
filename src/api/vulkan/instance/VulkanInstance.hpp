//
// Created by loghin on 18.04.2025.
//

#pragma once

#include <cds/Optional>
#include <cds/collection/Vector>
#include <ext/cds/Expected.hpp>
#include <generic/api/Api.hpp>
#include <generic/lang/Concepts.hpp>
#include <generic/log/Logger.hpp>
#include <vulkan/vulkan_core.h>

namespace c_eng::api::vk::detail {
using cds::Optional;
using cds::String;
using cds::StringView;
using cds::Vector;
using cds::experimental::Expected;
using cds::impl::fwd;
using cds::impl::xch;
using cds::impl::mv;
using cds::nullopt;

using generic::Api;
using generic::ApiInfo;
using generic::LoggerRef;
using generic::Version;

using generic::concepts::IterableOf;

class Vulkan;
class InstanceBuilder;
class DebugMessengerBuilder;
class PhysicalDevice;

struct VulkanInstanceFnPtrs {
  PFN_vkDestroyInstance vkDestroyInstance{nullptr};
  PFN_vkEnumeratePhysicalDevices vkEnumeratePhysicalDevices{nullptr};
  PFN_vkEnumerateDeviceExtensionProperties vkEnumerateDeviceExtensionProperties{nullptr};
  PFN_vkGetPhysicalDeviceProperties vkGetPhysicalDeviceProperties{nullptr};
  PFN_vkGetPhysicalDeviceFeatures vkGetPhysicalDeviceFeatures{nullptr};

#ifdef VK_EXT_debug_utils
  PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessengerEXT{nullptr};
  PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessengerEXT{nullptr};
#endif
};

class Instance : public Api {
public:
  class Builder;

  Instance(
      Vulkan const& vulkan,
      VkInstance handle,
      VulkanInstanceFnPtrs const& fnPtrs,
      VkAllocationCallbacks const* pAllocationCallbacks
  ) noexcept :
      Api{{}}, _vulkan{vulkan}, _handle{handle}, _pAllocationCallbacks{pAllocationCallbacks},
      _pfns{fnPtrs} {}

  Instance(Instance const&) noexcept = delete;
  Instance(Instance&& instance) noexcept :
      Api{mv(instance)},
      _vulkan{instance._vulkan},
      _handle{xch(instance._handle, VK_NULL_HANDLE)},
      _pAllocationCallbacks{xch(instance._pAllocationCallbacks, nullptr)},
      _pfns{instance._pfns} {}

  ~Instance() noexcept override {
    assert(functions().vkDestroyInstance && "undefined behavior");
    functions().vkDestroyInstance(_handle, _pAllocationCallbacks);
  }

  auto operator=(Instance const&) noexcept -> Instance& = delete;
  auto operator=(Instance&& instance) noexcept -> Instance& {
    if (this == &instance) {
      return *this;
    }

    assert(&_vulkan == &instance._vulkan && "undefined behavior");
    _handle = xch(instance._handle, VK_NULL_HANDLE);
    _pAllocationCallbacks = xch(instance._pAllocationCallbacks, nullptr);
    _pfns = instance._pfns;
    return *this;
  }

  [[nodiscard]] static constexpr auto builder(Vulkan const& vulkan) noexcept -> InstanceBuilder;

  [[nodiscard]] auto info() const noexcept -> ApiInfo override;
  [[nodiscard]] auto compiledVersion() const noexcept -> Optional<Version> override;
  [[nodiscard]] auto runtimeVersion() const noexcept -> Optional<Version> override;

  [[nodiscard]] constexpr auto handle() const noexcept {
    return _handle;
  }

  [[nodiscard]] constexpr auto vulkan() const noexcept -> Vulkan const& {
    return _vulkan;
  }

  [[nodiscard]] constexpr auto functions() const noexcept -> VulkanInstanceFnPtrs const& {
    return _pfns;
  }

  [[nodiscard]] constexpr auto allocationCallbacks() const noexcept {
    return _pAllocationCallbacks;
  }

  [[nodiscard]] auto debugMessengerBuilder() const noexcept -> DebugMessengerBuilder;

  [[nodiscard]] auto physicalDevices() const noexcept -> Expected<Vector<PhysicalDevice>, VkResult>;

private:
  Vulkan const& _vulkan;
  VkInstance _handle{VK_NULL_HANDLE};
  VkAllocationCallbacks const* _pAllocationCallbacks{nullptr};

  VulkanInstanceFnPtrs _pfns{};
};

class InstanceBuilder {
public:
  static constexpr auto defaultVulkanVersion = Version{0, 1, 0, 0};

  explicit constexpr InstanceBuilder(Vulkan const& vulkan) noexcept : _vulkan{vulkan} {}

  template <IterableOf<StringView> Layers> auto& withLayers(Layers&& layers) noexcept {
    _layers = fwd<Layers>(layers);
    return *this;
  }

  template <IterableOf<StringView> Extensions> auto& withExtensions(Extensions&& extensions) noexcept {
    _extensions = fwd<Extensions>(extensions);
    return *this;
  }

  auto& withApplicationName(StringView name) noexcept {
    _applicationName = name;
    return *this;
  }

  auto& withEngineName(StringView name) noexcept {
    _engineName = name;
    return *this;
  }

  auto& withApplicationVersion(Version const& version) noexcept {
    _applicationVersion = version;
    return *this;
  }

  auto& withEngineVersion(Version const& version) noexcept {
    _engineVersion = version;
    return *this;
  }

  auto& withVulkanVersion(Version const& version) noexcept {
    _targetVkVersion = version;
    return *this;
  }

  auto& withVulkanLogger(LoggerRef const logger) noexcept {
    _debugLogger = logger;
    return *this;
  }

  auto& withAllocationCallbacks(VkAllocationCallbacks const* pAllocationCallbacks) noexcept {
    _pAllocationCallbacks = pAllocationCallbacks;
    return *this;
  }

  auto& withLogger(LoggerRef const logger) noexcept {
    _logger = logger;
    return *this;
  }

  [[nodiscard]] auto build() const noexcept -> Expected<Instance, VkResult>;

private:
  Vulkan const& _vulkan;

  Optional<VkAllocationCallbacks const*> _pAllocationCallbacks{nullopt};

  Vector<String> _layers{};
  Vector<String> _extensions{};

  String _applicationName{"Unnamed Application"};
  String _engineName{"Unnamed Engine"};
  Version _applicationVersion{0, 0, 0, 0};
  Version _engineVersion{0, 0, 0, 0};
  Version _targetVkVersion{defaultVulkanVersion};

  Optional<LoggerRef> _logger{};
  LoggerRef _debugLogger{};
};

constexpr auto Instance::builder(Vulkan const& vulkan) noexcept -> InstanceBuilder {
  return InstanceBuilder{vulkan};
}
} // namespace c_eng::api::vk::detail

namespace c_eng::api::vk {
using detail::Instance;
using detail::InstanceBuilder;
} // namespace c_eng::api::vk

//
// Created by loghin on 18.04.2025.
//

#pragma once

#include <cds/Optional>
#include <cds/collection/Vector>
#include <core/VulkanSubunits.hpp>
#include <ext/cds/Expected.hpp>
#include <generic/api/Api.hpp>
#include <generic/lang/Concepts.hpp>
#include <generic/log/Logger.hpp>

namespace c_eng::generic::detail {
class Window;
} // namespace c_eng::generic

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
using generic::detail::Window;

using generic::concepts::IterableOf;

class Vulkan;
class InstanceBuilder;
class DebugMessengerBuilder;
class LogicalDeviceBuilder;
class PhysicalDevice;
class Surface;

struct InstanceFnPtrs;

#ifndef VK_EXT_validation_features
enum VkValidationFeatureEnableEXT {};
#endif

#ifndef VK_EXT_layer_settings
struct VkLayerSettingEXT {};
#endif

class Instance :
    public Api, public VulkanObject<SubObject<Vulkan>, WithAllocationCallbacks, WrapsVulkanHandle<VkInstance>> {
public:
  Instance(
      Vulkan const& vulkan,
      VkAllocationCallbacks const* pAllocationCallbacks,
      InstanceFnPtrs const* fnPtrs,
      VkInstance handle
  ) noexcept :
      Api{{}}, VulkanObject{vulkan, pAllocationCallbacks, handle}, _pfns{fnPtrs} {}

  Instance(Instance const&) = delete;
  Instance(Instance&& instance) noexcept :
      Api{mv(instance)},
      VulkanObject{mv(instance)},
      _pfns{xch(instance._pfns, nullptr)} {}

  ~Instance() noexcept override;

  [[nodiscard]] static constexpr auto builder(Vulkan const& vulkan) noexcept -> InstanceBuilder;

  [[nodiscard]] auto info() const noexcept -> ApiInfo override;
  [[nodiscard]] auto compiledVersion() const noexcept -> Optional<Version> override;
  [[nodiscard]] auto runtimeVersion() const noexcept -> Optional<Version> override;

  [[nodiscard]] constexpr auto functions() const noexcept -> InstanceFnPtrs const& {
    assert(_pfns && "undefined behavior");
    return *_pfns;
  }

  [[nodiscard]] auto debugMessengerBuilder() const noexcept -> DebugMessengerBuilder;
  [[nodiscard]] auto logicalDeviceBuilder() const noexcept -> LogicalDeviceBuilder;

  [[nodiscard]] auto physicalDevices() const noexcept -> Expected<Vector<PhysicalDevice>, VkResult>;
  [[nodiscard]] auto createSurface(
      Window const& window,
      Optional<VkAllocationCallbacks const*> pAllocationCallbacks = nullopt
  ) const noexcept -> Expected<Surface, VkResult>;

private:
  InstanceFnPtrs const* _pfns{};
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

  template <IterableOf<VkValidationFeatureEnableEXT> Features>
  auto& withExtraValidationFeatures(Features&& features) noexcept {
    _extraValidationFeatures = fwd<Features>(features);
    return *this;
  }

  template <IterableOf<VkLayerSettingEXT> Settings>
  auto& withLayerSettings(Settings&& settings) noexcept {
    _layerSettings = fwd<Settings>(settings);
    return *this;
  }

  [[nodiscard]] auto build() const noexcept -> Expected<Instance, VkResult>;

private:
  Vulkan const& _vulkan;

  Optional<VkAllocationCallbacks const*> _pAllocationCallbacks{nullopt};

  Vector<String> _layers{};
  Vector<String> _extensions{};

  Vector<VkValidationFeatureEnableEXT> _extraValidationFeatures{};
  Vector<VkLayerSettingEXT> _layerSettings{};

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

//
// Created by loghin on 18.04.2025.
//

#include "VulkanInstance.hpp"

#include <cds/collection/HashMap>
#include <cds/collection/VectorView>

#include "Vulkan.hpp"
#include "api/vulkan/core/VulkanTypes.hpp"
#include "api/vulkan/device/VulkanPhysicalDevice.hpp"
#include "api/vulkan/device/VulkanLogicalDevice.hpp"
#include "api/vulkan/debug/VulkanDebug.hpp"
#include "api/vulkan/wsi/VulkanSurface.hpp"
#include "generic/lang/Range.hpp"

#include "api/vulkan/core/VulkanHandles.hpp"

namespace c_eng::api::vk::detail {
namespace {
using cds::HashMap;
using cds::VectorView;
using cds::ignore;
using cds::nullopt;
using cds::impl::unreachable;

using generic::LicenceType;
using generic::Logger;
using generic::project;

template <IterableOf<StringView> ExtensionNames> auto acquireInstanceFnPtrs(
    InstanceFnPtrs* instanceFnPtrs,
    Vulkan const& vulkan,
    LoggerRef logger,
    VkInstance instance,
    ExtensionNames&& extensions
) noexcept -> Expected<InstanceFnPtrs*, VkResult> {
  ignore = logger;
  ignore = instance;
  ignore = extensions;

  auto const& getInstanceProcAddr = vulkan.functions().vkGetInstanceProcAddr;
  assert(getInstanceProcAddr && "undefined behavior");
  ignore = getInstanceProcAddr;

  HashMap<Extension, bool> requestedExtensions;

#define C_ENG_VULKAN_HANDLE(_resolve, _origin, _name) C_ENG_LATE_JOIN(C_ENG_VULKAN_HANDLE_ ## _resolve, _origin, _name)
#define C_ENG_LATE_JOIN(_a, _b, _c) _a(_b, _c)

#define C_ENG_VULKAN_HANDLE_ResolveInstance(_origin, _name) {                                                 \
    auto constexpr fnHandle = PFN::_name;                                                                     \
    if constexpr (auto constexpr origin = HandleTraits<fnHandle>::origin; origin == Extension::Base) {        \
      instanceFnPtrs->_name = resolveInstanceHandle<fnHandle>(getInstanceProcAddr, instance);                 \
      if (!instanceFnPtrs->_name) {                                                                           \
        logger(LogLevel::Error) << logger.invoke(                                                             \
            "[{}] Error: Failed to acquire instance function handle for '{}'"_f,                              \
            std::source_location::current(), HandleTraits<PFN::_name>::name);                                 \
        return Unexpected{VK_ERROR_FEATURE_NOT_PRESENT};                                                      \
      }                                                                                                       \
    } else {                                                                                                  \
      auto const [it, inserted] = requestedExtensions.emplace(origin, false);                                 \
      auto constexpr extName = ExtensionTraits<origin>::name;                                                 \
      if (inserted) {                                                                                         \
        for (auto&& extension : extensions) {                                                                 \
          if (extension == extName) {                                                                         \
            it->value() = true;                                                                               \
          }                                                                                                   \
        }                                                                                                     \
      }                                                                                                       \
      if (it->value()) {                                                                                      \
        instanceFnPtrs->_name = resolveInstanceHandle<fnHandle>(getInstanceProcAddr, instance);               \
        if (!instanceFnPtrs->_name) {                                                                         \
          logger(LogLevel::Error) << logger.invoke(                                                           \
              "[{}] Error: Failed to acquire extension-dependent ('{}') instance function handle for '{}'"_f, \
              std::source_location::current(), extName, HandleTraits<PFN::_name>::name);                      \
          return Unexpected{VK_ERROR_FEATURE_NOT_PRESENT};                                                    \
        }                                                                                                     \
      }                                                                                                       \
    }                                                                                                         \
  }

#define C_ENG_VULKAN_HANDLE_ResolveNone(_origin, _name)
#define C_ENG_VULKAN_HANDLE_ResolveGlobal(_origin, _name)
#define C_ENG_VULKAN_HANDLE_ResolveDevice(_origin, _name)

#include "api/vulkan/core/VulkanHandles.def"

#undef C_ENG_VULKAN_HANDLE_ResolveGlobal
#undef C_ENG_VULKAN_HANDLE_ResolveNone
#undef C_ENG_VULKAN_HANDLE_ResolveInstance
#undef C_ENG_VULKAN_HANDLE_ResolveDevice

#undef C_ENG_VULKAN_HANDLE
#undef C_ENG_LATE_JOIN

  return instanceFnPtrs;
}

#if defined(VK_EXT_debug_utils)
auto debugMessengerCallbackFromCreateInstance(
    VkDebugUtilsMessageSeverityFlagBitsEXT const severity,
    VkDebugUtilsMessageTypeFlagsEXT const types,
    VkDebugUtilsMessengerCallbackDataEXT const* const pCallbackData,
    void* const pUserData
) noexcept -> VkBool32 {
  auto* pLogger = static_cast<Logger*>(pUserData);
  assert(pLogger && "undefined behavior");
  auto const ref = LoggerRef{*pLogger};
  auto const level = [severity]{
    switch (severity) {
      case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
      case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:   return Logger::Level::Info;
      case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:return Logger::Level::Warning;
      case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:  return Logger::Level::Error;
      default:
        assert(false && "Unhandled 'VkDebugUtilsMessageSeverityFlagBitsEXT' case");
        unreachable();
    }
  }();

  ref(level) << ref.invoke("[vkCreateInstance][{:a} - {:a}] {}:{} -> {}"_f,
                           VulkanFormattedFlags<VkDebugUtilsMessageSeverityFlagBitsEXT>(severity),
                           VulkanFormattedFlags<VkDebugUtilsMessageTypeFlagBitsEXT>(types),
                           pCallbackData->pMessageIdName, pCallbackData->messageIdNumber,
                           pCallbackData->pMessage);
  return VK_FALSE;
}
#endif
} // namespace

Instance::~Instance() noexcept {
  assert(functions().vkDestroyInstance && "undefined behavior");
  functions().vkDestroyInstance(handle(), allocationCallbacks());
  delete _pfns;
}

auto Instance::info() const noexcept -> ApiInfo {
  ignore = this;
  using enum LicenceType;
  return {
      .name = "Vulkan",
      .description = "Low-level, low-overhead cross-platform API and open standard for 3D graphics and computing",
      .vendor = "Khronos Group",
      .vendorId = nullopt,
      .licenceType = Apache2_0,
  };
}

auto Instance::compiledVersion() const noexcept -> Optional<Version> {
#if defined(VK_API_VERSION_1_4)
  return toVersion(VK_API_VERSION_1_4);
#elif defined(VK_API_VERSION_1_3)
  return toVersion(VK_API_VERSION_1_3);
#elif defined(VK_API_VERSION_1_2)
  return toVersion(VK_API_VERSION_1_2);
#elif defined(VK_API_VERSION_1_1)
  return toVersion(VK_API_VERSION_1_1);
#elif defined(VK_API_VERSION_1_0)
  return toVersion(VK_API_VERSION_1_0);
#else
  return nullopt;
#endif
}

auto Instance::runtimeVersion() const noexcept -> Optional<Version> {
  auto const& fns = vulkan().functions();
  assert(fns.vkEnumerateInstanceVersion && "undefined behavior");

  std::uint32_t runtimeVersion;
  if (fns.vkEnumerateInstanceVersion(&runtimeVersion) != VK_SUCCESS) {
    return nullopt;
  }
  return toVersion(runtimeVersion);
}

auto InstanceBuilder::build() const noexcept -> Expected<Instance, VkResult> {
  auto const logger = _logger.getOr(LoggerRef{});
  auto const& fns = _vulkan.functions();
  auto const* pAllocationCallbacks = _pAllocationCallbacks.getOr(_vulkan.allocationCallbacks());
  assert(fns.vkCreateInstance && "undefined behavior");

  VkApplicationInfo applicationInfo {
      .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
      .pNext = nullptr,
      .pApplicationName = _applicationName.data(),
      .applicationVersion = fromVersion(_applicationVersion),
      .pEngineName = _engineName.data(),
      .engineVersion = fromVersion(_engineVersion),
      .apiVersion = fromVersion(_targetVkVersion),
  };

  Vector<char const*> layers{_layers | project([](auto const& s) {return s.data();})};
  Vector<char const*> extensions{_extensions | project([](auto const& s) {return s.data();})};

  VkFlags flags = 0u;
  if (_extensions.contains(ExtensionTraits<Extension::KHR_portability_enumeration>::name)) {
    flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
  } else {
#if CDS_ATTR(apple)
    extensions.emplaceBack(ExtensionTraits<Extension::KHR_portability_enumeration>::name);
    flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
#endif
  }

  VkInstanceCreateInfo createInfo {
      .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
      .pNext = nullptr,
      .flags = flags,
      .pApplicationInfo = &applicationInfo,
      .enabledLayerCount = static_cast<std::uint32_t>(layers.size()),
      .ppEnabledLayerNames = layers.data(),
      .enabledExtensionCount = static_cast<std::uint32_t>(extensions.size()),
      .ppEnabledExtensionNames = extensions.data(),
  };

#if defined(VK_EXT_debug_utils)
  auto debugLogger = _debugLogger;
  if (debugLogger == LoggerRef{}) {
    debugLogger = logger;
  }

  VkDebugUtilsMessengerCreateInfoEXT debugUtilsMessengerCreateInfo{
      .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
      .pNext = nullptr,
      .flags = 0u,
      .messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
          | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT
          | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
          | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
      .messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
          | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
          | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
      .pfnUserCallback = &debugMessengerCallbackFromCreateInstance,
      .pUserData = static_cast<void*>(debugLogger.get())
  };
#endif

  auto* lastInCreateInfoChain = &createInfo.pNext;
  for (auto const& extension : _extensions) {
    if (extension == ExtensionTraits<Extension::EXT_debug_utils>::name) {
      if (debugLogger == LoggerRef{}) {
        logger(Logger::Level::Info) << logger.invoke(
          "[{}] VK_EXT_debug_utils requested, but no logger was passed to instance creation, therefore no "
          "validation will happen during it"_f, std::source_location::current());
      } else {
#if !defined(VK_EXT_debug_utils)
        logger() << logger.invoke("[{}] Cannot load extension '{}' as the headers for it have not been found"_f,
                                    std::source_location::current(), ExtensionTraits<Extension::EXT_debug_utils>::name);
#else
        assert(debugUtilsMessengerCreateInfo.pUserData && "undefined behavior");
        *lastInCreateInfoChain = &debugUtilsMessengerCreateInfo;
        lastInCreateInfoChain = &debugUtilsMessengerCreateInfo.pNext;
#endif
      }
    }
  }

#if defined(VK_EXT_layer_settings)
  VkLayerSettingsCreateInfoEXT layerSettings{
      .sType = VK_STRUCTURE_TYPE_LAYER_SETTINGS_CREATE_INFO_EXT,
      .pNext = nullptr,
      .settingCount = static_cast<std::uint32_t>(_layerSettings.size()),
      .pSettings = _layerSettings.data(),
  };

  if (!layers && _layerSettings) {
    logger(LogLevel::Warning) << logger.invoke(
        "[{}] Attempting to set layer settings, but no layers have been provided"_f,
        std::source_location::current()
    );
  }

  if (_layerSettings) {
    *lastInCreateInfoChain = &layerSettings;
    lastInCreateInfoChain = &layerSettings.pNext;
  }
#else
  if (_layerSettings) {
    logger(LogLevel::Warning) << logger.invoke(
        "[{}] Cannot set layer settings, missing extension '{}' headers."_f,
        std::source_location::current(), ExtensionTraits<Extension::EXT_layer_settings>::name
    );
  }
#endif

#if defined(VK_EXT_validation_features)
  VkValidationFeaturesEXT validationFeatures{
      .sType = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT,
      .pNext = nullptr,
      .enabledValidationFeatureCount = static_cast<std::uint32_t>(_extraValidationFeatures.size()),
      .pEnabledValidationFeatures = _extraValidationFeatures.data(),
      .disabledValidationFeatureCount = 0u,
      .pDisabledValidationFeatures = nullptr,
  };
#else
  if (_extraValidationFeatures) {
    logger(LogLevel::Warning) << logger.invoke(
        "[{}] Cannot add extra validation features {}, missing extension '{}' headers."_f,
        std::source_location::current(), _extraValidationFeatures,
        ExtensionTraits<Extension::EXT_validation_features>::name);
  }
#endif

  for (auto const& layer : _layers) {
    if (layer == LayerTraits<Layer::LAYER_KHRONOS_validation>::name && _extraValidationFeatures) {
#if defined(VK_EXT_validation_features)
      *lastInCreateInfoChain = &validationFeatures;
      lastInCreateInfoChain = &validationFeatures.pNext;
#endif
    }
  }

  VkInstance instanceHandle = VK_NULL_HANDLE;
  if (auto result = fns.vkCreateInstance(&createInfo, pAllocationCallbacks, &instanceHandle);
      result != VK_SUCCESS) {
    return Unexpected{result};
  }

  auto const pInstanceHandles = new InstanceFnPtrs{};
  auto const expectedInstanceFnPtrs =
      acquireInstanceFnPtrs(pInstanceHandles, _vulkan, logger, instanceHandle, _extensions);
  if (!expectedInstanceFnPtrs) {
    if (auto const backupVkDestroyInstance = resolveInstanceHandle<PFN::vkDestroyInstance>(
        _vulkan.functions().vkGetInstanceProcAddr, instanceHandle)) {
      delete pInstanceHandles;
      backupVkDestroyInstance(instanceHandle, pAllocationCallbacks);
    }
    return Unexpected{expectedInstanceFnPtrs.error()};
  }

  auto const& instanceFnPtrs = *expectedInstanceFnPtrs;
  return {_vulkan, pAllocationCallbacks, instanceFnPtrs, instanceHandle};
}

auto Instance::debugMessengerBuilder() const noexcept -> DebugMessengerBuilder {
  return DebugMessengerBuilder{*this};
}

auto Instance::physicalDevices() const noexcept -> Expected<Vector<PhysicalDevice>, VkResult> {
  auto const& fns = functions();
  assert(fns.vkEnumeratePhysicalDevices && "undefined behavior");

  Vector<VkPhysicalDevice> deviceHandles;
  std::uint32_t devCount = 0u;

  if (auto const result = fns.vkEnumeratePhysicalDevices(handle(), &devCount, nullptr);
      result != VK_SUCCESS) {
    return Unexpected{result};
  }

  deviceHandles.resize(devCount);
  if (auto const result = fns.vkEnumeratePhysicalDevices(handle(), &devCount, deviceHandles.data());
      result != VK_SUCCESS) {
    return Unexpected{result};
  }

  return deviceHandles | project([this](auto handle){return PhysicalDevice{*this, handle};});
}

auto Instance::createSurface(Window const& window, Optional<VkAllocationCallbacks const*> pAllocationCallbacks)
    const noexcept -> Expected<Surface, VkResult> {
  return Surface::createSurface(*this, window, pAllocationCallbacks);
}

auto Instance::logicalDeviceBuilder() const noexcept -> LogicalDeviceBuilder {
  return LogicalDeviceBuilder{*this};
}

} // namespace c_eng::api::vk::detail

//
// Created by loghin on 18.04.2025.
//

#include "VulkanInstance.hpp"

#include <cds/collection/HashMap>

#include "Vulkan.hpp"
#include "api/vulkan/core/VulkanTypes.hpp"
#include "api/vulkan/core/VulkanHandles.hpp"
#include "generic/lang/Range.hpp"

namespace c_eng::api::vk::detail {
namespace {
using cds::HashMap;
using cds::ignore;
using cds::nullopt;
using cds::impl::unreachable;

using generic::LicenceType;
using generic::Logger;
using generic::project;

template <IterableOf<StringView> ExtensionNames> auto acquireInstanceFnPtrs(
    Vulkan const& vulkan,
    LoggerRef logger,
    VkInstance instance,
    ExtensionNames&& extensions
) noexcept -> Expected<VulkanInstanceFnPtrs, VkResult> {
  ignore = logger;
  ignore = instance;
  ignore = extensions;

  VulkanInstanceFnPtrs instanceFnPtrs{};
  auto const& getInstanceProcAddr = vulkan.functions().vkGetInstanceProcAddr;
  assert(getInstanceProcAddr && "undefined behavior");

  HashMap<Extension, bool> requestedExtensions;

#define C_ENG_VULKAN_HANDLE(_resolve, _origin, _name) C_ENG_LATE_JOIN(C_ENG_VULKAN_HANDLE_ ## _resolve, _origin, _name)
#define C_ENG_LATE_JOIN(_a, _b, _c) _a(_b, _c)

#define C_ENG_VULKAN_HANDLE_Instance(_origin, _name)                                              \
  instanceFnPtrs._name = resolveInstanceHandle<PFN:: _name>(instance);                            \
  if (instanceFnPtrs._name == nullptr) {                                                          \
    if constexpr (Extension::_origin != Extension::Base) {                                        \
      auto constexpr origin = HandleTraits<PFN::_name>::origin;                                   \
      auto const [it, inserted] = requestedExtensions.emplace(Extension::_origin, false);         \
      auto const extName = ExtensionTraits<Extension::_origin>::name;                             \
      if (inserted) {                                                                             \
        for (auto&& extension : extensions) {                                                     \
          if (extension == extName) {                                                             \
            it->value() = true;                                                                   \
          }                                                                                       \
        }                                                                                         \
      }                                                                                           \
      if (!it->value()) {                                                                         \
        logger(LogLevel::Error) << logger.invoke(                                                 \
          "[{}] Error: Failed to acquire instance function '{}' due to missing extension '{}'"_f, \
          std::source_location::current(), HandleTraits<PFN::_name>::name, extName);              \
          return Unexpected{VK_ERROR_EXTENSION_NOT_PRESENT};                                      \
      }                                                                                           \
    }                                                                                             \
    logger(LogLevel::Error) << logger.invoke(                                                     \
        "[{}] Error: Failed to acquire instance function handle for '{}'"_f,                      \
        std::source_location::current(), HandleTraits<PFN::_name>::name);                         \
    return Unexpected{VK_ERROR_FEATURE_NOT_PRESENT};                                              \
  }

  C_ENG_VULKAN_HANDLE(Instance, Base, vkDestroyInstance)

#define C_ENG_VULKAN_HANDLE_Always(_origin, _name)
#define C_ENG_VULKAN_HANDLE_Global(_origin, _name)
#define C_ENG_VULKAN_HANDLE_Device(_origin, _name)

#include "api/vulkan/core/VulkanHandles.def"

#undef C_ENG_VULKAN_HANDLE_Global
#undef C_ENG_VULKAN_HANDLE_Always
#undef C_ENG_VULKAN_HANDLE_Instance
#undef C_ENG_VULKAN_HANDLE_Device

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

  ref(level) << ref.invoke("[vkCreateInstance][{a} - {a}] {}:{} -> {}"_f,
                           VulkanFormattedFlags<VkDebugUtilsMessageSeverityFlagBitsEXT>(severity),
                           VulkanFormattedFlags<VkDebugUtilsMessageTypeFlagBitsEXT>(types),
                           pCallbackData->pMessageIdName, pCallbackData->messageIdNumber,
                           pCallbackData->pMessage);
  return VK_FALSE;
}
#endif
} // namespace

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
  auto const& fns = _vulkan.functions();
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
  VkInstanceCreateInfo createInfo {
      .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0u,
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
    if (extension == ExtensionTraits<Extension::EXT_debug_utils>::name && debugLogger != LoggerRef{}) {
#if !defined(VK_EXT_debug_utils)
      _logger() << _logger.invoke("[{}] Cannot load extension '{}' as the headers for it have not been found"_f,
                                  std::source_location::current(), ExtensionTraits<Extension::EXT_debug_utils>::name);
#else
      assert(debugUtilsMessengerCreateInfo.pUserData && "undefined behavior");
      *lastInCreateInfoChain = &debugUtilsMessengerCreateInfo;
      lastInCreateInfoChain = &debugUtilsMessengerCreateInfo.pNext;
#endif
    }
  }

  VkInstance instanceHandle;
  if (auto result = fns.vkCreateInstance(&createInfo, pAllocationCallbacks, &instanceHandle);
      result != VK_SUCCESS) {
    return Unexpected{result};
  }

  return acquireInstanceFnPtrs(_vulkan, logger, instanceHandle, _extensions)
      .transform([this, logger, instanceHandle, pAllocationCallbacks](auto const& instanceFnPtrs) {
        return Instance{_vulkan, instanceHandle, logger, instanceFnPtrs, pAllocationCallbacks};
      });
}

} // namespace c_eng::api::vk::detail

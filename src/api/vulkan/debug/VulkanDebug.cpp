//
// Created by loghin on 18.04.2025.
//

#include "VulkanDebug.hpp"

#include <source_location>
#include <cds/Format>

#include <core/VulkanHandles.hpp>
#include <core/VulkanFormatters.hpp>
#include <ext/cds/StdFormatters.hpp>
#include <instance/VulkanInstance.hpp>

namespace c_eng::api::vk::detail {
namespace {
using namespace cds::literals;
using cds::Unexpected;
using cds::impl::unreachable;

using generic::Logger;

#if defined(VK_EXT_debug_utils)
auto debugMessengerCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT const severity,
    VkDebugUtilsMessageTypeFlagsEXT const types,
    VkDebugUtilsMessengerCallbackDataEXT const* const pCallbackData,
    void* const pUserData
) noexcept -> VkBool32 {
  auto* pLogger = static_cast<Logger*>(pUserData);
  if (!pLogger) {
    return VK_FALSE;
  }

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

  ref(level) << ref.invoke("[VkDebugMessenger][{:a} - {:a}] {}:{} -> {}"_f,
                           VulkanFormattedFlags<VkDebugUtilsMessageSeverityFlagBitsEXT>(severity),
                           VulkanFormattedFlags<VkDebugUtilsMessageTypeFlagBitsEXT>(types),
                           pCallbackData->pMessageIdName, pCallbackData->messageIdNumber,
                           pCallbackData->pMessage);
  return VK_FALSE;
}
#endif
} // namespace

DebugMessenger::~DebugMessenger() noexcept {
#ifdef VK_EXT_debug_utils
  assert(instance().functions().vkDestroyDebugUtilsMessengerEXT && "undefined behavior");
  instance().functions().vkDestroyDebugUtilsMessengerEXT(
      instance().handle(),
      handle(),
      allocationCallbacks()
  );
#endif
}

auto DebugMessengerBuilder::build(LoggerRef const logger) const noexcept -> Expected<DebugMessenger, VkResult> {
#ifndef VK_EXT_debug_utils
  logger(LoggerRef::Level::Warning) << logger.invoke(
      "[{}] Cannot create debug messenger, no debug messenger headers found."_f, std::source_location::current()
  );
  return Unexpected{VK_ERROR_EXTENSION_NOT_PRESENT};
#else

  if (logger == LoggerRef{}) {
    return {_instance, nullptr, VK_NULL_HANDLE};
  }

  auto const fns = _instance.functions();
  auto const allocationCallbacks = _pAllocationCallbacks.getOr(_instance.allocationCallbacks());

  if (!fns.vkCreateDebugUtilsMessengerEXT || !fns.vkDestroyDebugUtilsMessengerEXT) {
    logger(LoggerRef::Level::Error) << logger.invoke(
        "[{}] Functions for creating and destroying a debug messenger are not present. Extension '{}' is required in"
        " instance creation"_f, std::source_location::current(), ExtensionTraits<Extension::EXT_debug_utils>::name
    );
    return Unexpected{VK_ERROR_EXTENSION_NOT_PRESENT};
  }

  VkDebugUtilsMessengerCreateInfoEXT createInfo{
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
      .pfnUserCallback = &debugMessengerCallback,
      .pUserData = static_cast<void*>(logger.get())
  };

  VkDebugUtilsMessengerEXT handle = VK_NULL_HANDLE;
  if (auto const result =
          fns.vkCreateDebugUtilsMessengerEXT(_instance.handle(), &createInfo, allocationCallbacks, &handle);
      result != VK_SUCCESS) {
    return Unexpected{result};
  }
  return {_instance, allocationCallbacks, handle};
#endif
}
} // c_eng::api::vk::detail

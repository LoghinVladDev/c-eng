//
// Created by loghin on 18.04.2025.
//

#include "Vulkan.hpp"
#include "api/vulkan/core/VulkanHandles.hpp"
#include "instance/VulkanInstance.hpp"

namespace c_eng::api::vk::detail {
namespace {
using cds::Unexpected;
using cds::ignore;

auto acquireGlobalFnPtrs(GlobalFnPtrs* globalFnPtrs, LoggerRef logger) noexcept -> Expected<GlobalFnPtrs*, VkResult> {
  ignore = logger;
  auto const getInstanceProcAddr = globalFnPtrs->vkGetInstanceProcAddr;
  assert(getInstanceProcAddr && "undefined behavior");

#define C_ENG_VULKAN_HANDLE(_resolve, _origin, _name) C_ENG_LATE_JOIN(C_ENG_VULKAN_HANDLE_ ## _resolve, _origin, _name)
#define C_ENG_LATE_JOIN(_a, _b, _c) _a(_b, _c)

#define C_ENG_VULKAN_HANDLE_ResolveGlobal(_origin, _name)                                       \
  globalFnPtrs->_name = resolveGlobalHandle<PFN:: _name>(getInstanceProcAddr);                  \
  if (globalFnPtrs->_name == nullptr) {                                                         \
    logger(LogLevel::Error) << logger.invoke("[{}] Error: Failed to acquire handle for '{}'"_f, \
        std::source_location::current(), HandleTraits<PFN::_name>::name);                       \
    return Unexpected{VK_ERROR_FEATURE_NOT_PRESENT};                                            \
  }

#define C_ENG_VULKAN_HANDLE_ResolveNone(_origin, _name)
#define C_ENG_VULKAN_HANDLE_ResolveInstance(_origin, _name)
#define C_ENG_VULKAN_HANDLE_ResolveDevice(_origin, _name)

#include "api/vulkan/core/VulkanHandles.def"

#undef C_ENG_VULKAN_HANDLE_ResolveGlobal
#undef C_ENG_VULKAN_HANDLE_ResolveNone
#undef C_ENG_VULKAN_HANDLE_ResolveInstance
#undef C_ENG_VULKAN_HANDLE_ResolveDevice

#undef C_ENG_VULKAN_HANDLE
#undef C_ENG_LATE_JOIN

  return globalFnPtrs;
}
} // namespace

Vulkan::~Vulkan() noexcept {
  delete _pfns;
}

auto Vulkan::layerProperties() const noexcept -> Expected<Vector<VkLayerProperties>, VkResult> {
  auto const& fns = functions();
  assert(fns.vkEnumerateInstanceLayerProperties && "undefined behavior");

  U32 count = 0;
  if (auto const result = fns.vkEnumerateInstanceLayerProperties(&count, nullptr);
      result != VK_SUCCESS) {
    _logger(LogLevel::Error) << _logger.invoke(
        "[{}] Failed to query number of layer properties: {}"_f,
        std::source_location::current(), result
    );
    return Unexpected{result};
  }

  Vector<VkLayerProperties> layerProperties{count};
  if (auto const result = fns.vkEnumerateInstanceLayerProperties(&count, layerProperties.data());
      result != VK_SUCCESS) {
    _logger(LogLevel::Error) << _logger.invoke(
        "[{}] Failed to query layer properties: {}"_f,
        std::source_location::current(), result
    );
    return Unexpected{result};
  }

  return mv(layerProperties);
}

auto VulkanBuilder::build() noexcept -> Expected<Vulkan, VkResult> {
  auto const logger = xch(_logger, {});
  auto const pAllocationCallbacks = xch(_pAllocationCallbacks, nullptr);
  return acquireGlobalFnPtrs(new GlobalFnPtrs{}, logger).transform([logger, pAllocationCallbacks](auto const* globalFnPtrs) {
    return Vulkan{logger, globalFnPtrs, pAllocationCallbacks};
  });
}

auto Vulkan::instanceBuilder() const noexcept -> InstanceBuilder {
  return InstanceBuilder{*this};
}
} // namespace c_eng::api::vk::detail

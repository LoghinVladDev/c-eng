//
// Created by loghin on 18.04.2025.
//

#include "VulkanLogicalDevice.hpp"
#include <algorithm>
#include <source_location>
#include <cds/Format>
#include <cds/Tuple>
#include <device/VulkanPhysicalDevice.hpp>
#include <device/VulkanQueue.hpp>
#include <ext/cds/StdFormatters.hpp>
#include <generic/lang/Range.hpp>
#include <instance/VulkanInstance.hpp>
#include <wsi/VulkanSwapChain.hpp>

#include <core/VulkanHandles.hpp>

namespace c_eng::api::vk::detail {
namespace {
using cds::Tuple;
using cds::U32;
using cds::experimental::Unexpected;
using cds::ignore;
using namespace cds::literals;

using generic::project;
using generic::forEach;
using generic::LoggerRef;
using generic::LogLevel;

template <IterableOf<StringView> ExtensionNames> auto acquireDeviceFnPtrs(
    DeviceFnPtrs* deviceFnPtrs,
    Instance const& instance,
    LoggerRef logger,
    VkDevice device,
    ExtensionNames&& extensions
) noexcept -> Expected<DeviceFnPtrs*, VkResult> {
  ignore = logger;
  ignore = device;
  ignore = extensions;

  auto const& getDeviceProcAddr = instance.functions().vkGetDeviceProcAddr;
  assert(getDeviceProcAddr && "undefined behavior");
  ignore = getDeviceProcAddr;

  HashMap<Extension, bool> requestedExtensions;

#define C_ENG_VULKAN_HANDLE(_resolve, _origin, _name) C_ENG_LATE_JOIN(C_ENG_VULKAN_HANDLE_ ## _resolve, _origin, _name)
#define C_ENG_LATE_JOIN(_a, _b, _c) _a(_b, _c)

#define C_ENG_VULKAN_HANDLE_ResolveDevice(_origin, _name) {                                                   \
    auto constexpr fnHandle = PFN::_name;                                                                     \
    if constexpr (auto constexpr origin = HandleTraits<fnHandle>::origin; origin == Extension::Base) {        \
      deviceFnPtrs->_name = resolveDeviceHandle<fnHandle>(getDeviceProcAddr, device);                         \
      if (!deviceFnPtrs->_name) {                                                                             \
        logger(LogLevel::Error) << logger.invoke(                                                             \
            "[{}] Error: Failed to acquire device function handle for '{}'"_f,                                \
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
        deviceFnPtrs->_name = resolveDeviceHandle<fnHandle>(getDeviceProcAddr, device);                       \
        if (!deviceFnPtrs->_name) {                                                                           \
          logger(LogLevel::Error) << logger.invoke(                                                           \
              "[{}] Error: Failed to acquire extension-dependent ('{}') device function handle for '{}'"_f,   \
              std::source_location::current(), extName, HandleTraits<PFN::_name>::name);                      \
          return Unexpected{VK_ERROR_FEATURE_NOT_PRESENT};                                                    \
        }                                                                                                     \
      }                                                                                                       \
    }                                                                                                         \
  }

#define C_ENG_VULKAN_HANDLE_ResolveNone(_origin, _name)
#define C_ENG_VULKAN_HANDLE_ResolveGlobal(_origin, _name)
#define C_ENG_VULKAN_HANDLE_ResolveInstance(_origin, _name)

#include "api/vulkan/core/VulkanHandles.def"

#undef C_ENG_VULKAN_HANDLE_ResolveGlobal
#undef C_ENG_VULKAN_HANDLE_ResolveNone
#undef C_ENG_VULKAN_HANDLE_ResolveInstance
#undef C_ENG_VULKAN_HANDLE_ResolveDevice

#undef C_ENG_VULKAN_HANDLE
#undef C_ENG_LATE_JOIN

  return deviceFnPtrs;
}

auto makeQueueFamilyConfig(auto const& queueConfig) noexcept {
  Vector<Tuple<U32, Vector<float>>> result;
  queueConfig | project([](auto const& config) -> Tuple<U32, Vector<float>> {
    return {config.key()->index(), config.value()};
  }) | forEach([&result](auto&& entry) { result.emplaceBack(mv(entry)); });
  std::sort(result.data(), result.data() + result.size(), [](auto const& a, auto const& b) {
    return get<0>(a) < get<0>(b);
  });
  return result;
}

auto emplaceInto(auto const& configs, Vector<VkDeviceQueueCreateInfo>& createInfos) {
  configs | forEach([&createInfos](auto const& config) {
    createInfos.pushBack({
        .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0u,
        .queueFamilyIndex = get<0>(config),
        .queueCount = static_cast<U32>(get<1>(config).size()),
        .pQueuePriorities = get<1>(config).data()
    });
  });
}
} // namespace

LogicalDevice::~LogicalDevice() noexcept {
  assert(instance().functions().vkDestroyDevice && "undefined behavior");
  instance().functions().vkDestroyDevice(handle(), allocationCallbacks());
  delete _pfns;
}

auto LogicalDeviceBuilder::build(PhysicalDevice const& device) const noexcept
    -> Expected<LogicalDevice, VkResult> {
  auto const& fns = _instance.functions();
  assert(fns.vkCreateDevice && "undefined behavior");

  auto const allocationCallbacks = _pAllocationCallbacks.getOr(_instance.allocationCallbacks());
  auto const queueFamilyConfig = makeQueueFamilyConfig(_plannedQueues);
  Vector<VkDeviceQueueCreateInfo> queueCreateInfos;
  queueCreateInfos.reserve(queueFamilyConfig.size());
  emplaceInto(queueFamilyConfig, queueCreateInfos);

  Vector<char const*> extensions{_extensions | project([](auto const& ext) {return ext.data();})};

  // Deprecated
  // Vector<char const*> layers{_layers | project([](auto const& layer) {return layer.data();})};

  auto const features = device.features();

  VkDeviceCreateInfo const createInfo {
      .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0u,
      .queueCreateInfoCount = static_cast<U32>(queueCreateInfos.size()),
      .pQueueCreateInfos = queueCreateInfos.data(),
      .enabledLayerCount = 0u,        /* deprecated, uses instance layers */
      .ppEnabledLayerNames = nullptr, /* deprecated, uses instance layers */
      .enabledExtensionCount = static_cast<U32>(extensions.size()),
      .ppEnabledExtensionNames = extensions.data(),
      .pEnabledFeatures = &features,
  };

  VkDevice handle{VK_NULL_HANDLE};
  if (auto const result = fns.vkCreateDevice(device.handle(), &createInfo, allocationCallbacks, &handle);
      result != VK_SUCCESS) {
    return Unexpected{result};
  }

  auto const pDeviceFnPtrs = new DeviceFnPtrs{};
  auto const expectedInstanceFnPtrs = acquireDeviceFnPtrs(pDeviceFnPtrs, _instance, LoggerRef{}, handle, _extensions);
  if (!expectedInstanceFnPtrs) {
    delete pDeviceFnPtrs;
    assert(_instance.functions().vkDestroyDevice && "undefined behavior");
    _instance.functions().vkDestroyDevice(handle, allocationCallbacks);
    return Unexpected{expectedInstanceFnPtrs.error()};
  }

  auto const& deviceFnPtrs = *expectedInstanceFnPtrs;
  return {_instance, device, allocationCallbacks, deviceFnPtrs, handle};
}

auto LogicalDevice::swapChainBuilder() const noexcept -> SwapChainBuilder {
  return SwapChainBuilder(*this);
}
} // namespace c_eng::api::vk::detail

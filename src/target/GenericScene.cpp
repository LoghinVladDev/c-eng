//
// Created by loghin on 10/17/24.
//

#include <cstdlib>
#include <iostream>
#include <filesystem>

#include <cds/Format>
#include <cds/StringView>
#include <cds/collection/HashMap>

// #include "api/vulkan/core/VulkanTypesToString.hpp"

#include "generic/engine/Engine.hpp"
#include "generic/log/Logger.hpp"

#include "api/glfw/Glfw.hpp"
#include "api/vulkan/Vulkan.hpp"
#include "api/vulkan/debug/VulkanDebug.hpp"
#include "api/vulkan/device/VulkanPhysicalDevice.hpp"
#include "api/vulkan/device/VulkanLogicalDevice.hpp"
#include "api/vulkan/device/VulkanQueue.hpp"
#include "api/vulkan/instance/VulkanInstance.hpp"
#include "api/vulkan/wsi/VulkanSurface.hpp"

#include <ext/cds/Expected.hpp>
#include <generic/lang/Range.hpp>

#include "core/VulkanExtensions.hpp"
#include "core/VulkanLayers.hpp"

namespace {
using cds::HashMap;
using cds::Optional;
using cds::StringView;
using cds::U32;
using cds::U64;
using cds::Union;
using cds::Vector;
using cds::ignore;
using cds::nullopt;

using cds::experimental::Expected;
using cds::experimental::Unexpected;

using cds::impl::fwd;
using cds::impl::mv;

using cds::meta::ReturnOf;

using namespace cds::literals;

using c_eng::generic::Api;
using c_eng::generic::Engine;
using c_eng::generic::Logger;
using c_eng::generic::LoggerRef;
using c_eng::generic::LoggerOutput;

using c_eng::api::Glfw;
using c_eng::api::vk::Vulkan;
using c_eng::api::vk::Instance;
using c_eng::api::vk::QueueFamily;
using c_eng::api::vk::LogicalDevice;
using c_eng::api::vk::PhysicalDevice;
using c_eng::api::vk::Surface;
using enum c_eng::api::GlfwInitParameter;

using c_eng::generic::flatten;
using c_eng::generic::filter;
using c_eng::generic::forEach;
using c_eng::generic::findAny;
using c_eng::generic::project;

using c_eng::api::vk::detail::Extension;
using c_eng::api::vk::detail::ExtensionTraits;
using c_eng::api::vk::detail::Layer;
using c_eng::api::vk::detail::LayerTraits;

// using c_eng::api::vk::ApplicationInfo;
// using c_eng::api::vk::LogicalDevice;
// using c_eng::api::vk::LogicalDeviceFactory;
// using c_eng::api::vk::PhysicalDevice;
// using c_eng::api::vk::QueueFamily;
// using c_eng::api::vk::createInstance;
// using c_eng::api::vk::createSurface;
// using c_eng::api::vk::layerProperties;
// using c_eng::api::vk::physicalDevices;

struct MemBlock {
  U64 size;
  U64 alignment;
  VkSystemAllocationScope scope;
};

struct MemSizeBlock {
  LoggerRef logger;
  bool loggingEnabled;
  HashMap<void*, MemBlock> memBlocks;
  U64 totalUsage;

  ~MemSizeBlock() noexcept {
    if (loggingEnabled && !memBlocks.empty()) {
      logger(Logger::Level::Warning) << logger.invoke("Leak of {} blocks in memory allocated by Vulkan:"_f, memBlocks.size());
      for (auto const& [pMem, block]: memBlocks) {
        logger(Logger::Level::Warning) << logger.invoke("\tLeak of block {} of size {} and alignment {} with scope '{}'"_f, pMem, block.size, block.alignment, block.scope);
      }
    }
  }
};

auto localAlloc(
    void* pUserData,
    std::size_t size,
    std::size_t alignment,
    VkSystemAllocationScope scope
) noexcept -> void* {
  auto mem = malloc(size);
  if (auto const memBlock = static_cast<MemSizeBlock*>(pUserData); memBlock && memBlock->loggingEnabled) {
    auto const logger = memBlock->logger;
    logger() << logger.invoke("Vulkan allocated at {} {} bytes aligned at {} bytes in '{}'"_f, mem, size, alignment, scope);
    memBlock->memBlocks.emplace(mem, size, alignment, scope);
    memBlock->totalUsage += size;
  }

  return mem;
}

auto localRealloc(
    void* pUserData,
    void* pOriginal,
    std::size_t size,
    std::size_t alignment,
    VkSystemAllocationScope scope
) noexcept -> void* {
  auto mem = realloc(pOriginal, size);
  if (auto const memBlock = static_cast<MemSizeBlock*>(pUserData); memBlock && memBlock->loggingEnabled) {
    auto const logger = memBlock->logger;
    if (auto const it = memBlock->memBlocks.find(pOriginal); it == memBlock->memBlocks.end()) {
      logger(Logger::Level::Warning) << logger.invoke("Vulkan requested reallocation of {}, which was never allocated"_f, pOriginal);
    } else if (auto const& [pMem, block] = *it; pMem != mem) {
      logger() << logger.invoke("Vulkan reallocated from {} of {} bytes to {} of {} bytes, aligned at {} bytes in '{}'"_f, pOriginal, block.size, mem, size, alignment, scope);
      memBlock->totalUsage -= it->value().size;
      memBlock->memBlocks.remove(it);
      memBlock->totalUsage +=
          get<0>(memBlock->memBlocks.emplace(mem, size, alignment, scope))->value().size;
    } else {
      logger() << logger.invoke("Vulkan reallocated at {} from {} bytes to {} bytes, aligned at {} bytes in '{}'"_f, pOriginal, block.size, size, alignment, scope);
      memBlock->totalUsage -= it->value().size;
      it->value() = {size, alignment, scope};
      memBlock->totalUsage += it->value().size;
    }
  }

  return mem;
}

auto localFree(void* pUserData, void* pMemory) noexcept -> void {
  if (auto const memBlock = static_cast<MemSizeBlock*>(pUserData); pMemory && memBlock && memBlock->loggingEnabled) {
    auto const logger = memBlock->logger;
    if (auto const it = memBlock->memBlocks.find(pMemory); it == memBlock->memBlocks.end()) {
      logger(Logger::Level::Warning) << logger.invoke("Vulkan requested free of {}, which was never allocated"_f, pMemory);
    } else {
      memBlock->totalUsage -= it->value().size;
      memBlock->memBlocks.remove(it);
    }
  }

  free(pMemory);
}

auto localInternalAlloc(
    void* pUserData,
    std::size_t size,
    VkInternalAllocationType type,
    VkSystemAllocationScope scope
) noexcept -> void {
  if (auto const memBlock = static_cast<MemSizeBlock*>(pUserData); memBlock && memBlock->loggingEnabled) {
    auto const logger = memBlock->logger;
    logger() << logger.invoke("Vulkan Internal Allocation of size {}, type {}, scope {}"_f, size, type, scope);
  }
}

auto localInternalFree(
    void* pUserData,
    std::size_t size,
    VkInternalAllocationType type,
    VkSystemAllocationScope scope
) noexcept -> void {
  if (auto const memBlock = static_cast<MemSizeBlock*>(pUserData); memBlock && memBlock->loggingEnabled) {
    auto const logger = memBlock->logger;
    logger() << logger.invoke("Vulkan Internal Free of size {}, type {}, scope {}"_f, size, type, scope);
  }
}
} // namespace

auto main(int const argc, char const* const* argv) noexcept -> int {
  auto disableLogPresent = false;
  for (unsigned idx = 1; idx < argc; ++idx) {
    if (StringView{argv[idx]} == "-dl") {
      disableLogPresent = true;
    }
  }

  Logger l {Vector{{LoggerOutput{std::cout}}}};
  if (disableLogPresent) {
    l.setEnabled(false);
  }

  MemSizeBlock mem{
      .logger = l,
      .loggingEnabled = !disableLogPresent,
  };

  VkAllocationCallbacks const allocationCallbacks {
      .pUserData = &mem,
      .pfnAllocation = &localAlloc,
      .pfnReallocation = &localRealloc,
      .pfnFree = &localFree,
      .pfnInternalAllocation = &localInternalAlloc,
      .pfnInternalFree = &localInternalFree,
  };

  Glfw glfw{{PlatformX11}, l};
  auto requestedVulkanExtensions = glfw.vulkanExtensions();
  requestedVulkanExtensions.emplaceBack(ExtensionTraits<Extension::EXT_debug_utils>::name);

  auto expectedVk = Vulkan::builder()
      .withLogger(l)
      .withAllocationCallbacks(&allocationCallbacks)
      .build();

  auto expectedLayerProperties = expectedVk.then(&Vulkan::layerProperties);
  auto expectedRequiredLayers = mv(expectedLayerProperties).transform([](auto&& layers) {
    return Vector<VkLayerProperties>{mv(layers) | filter([](auto const& properties) {
      return static_cast<char const*>(properties.layerName)
          == StringView{LayerTraits<Layer::LAYER_KHRONOS_validation>::name};
    })};
  });

  auto expectedVkInstance = expectedVk
      .then([&expectedRequiredLayers, &l, &allocationCallbacks, &requestedVulkanExtensions](auto const& vk) {
        return expectedRequiredLayers.then([&](auto const& layers) {
          return vk.instanceBuilder()
              .withLogger(l)
              .withVulkanLogger(l)
              .withAllocationCallbacks(&allocationCallbacks)
              .withApplicationName("GenericScene")
              .withApplicationVersion({0, 0, 1, 0})
              .withEngineName("c-eng")
              .withEngineVersion({0, 0, 7, 1})
              .withVulkanVersion({0, 1, 4, 0})
              .withExtensions(requestedVulkanExtensions)
              .withLayers(layers | project([](auto const& layerProperties){return layerProperties.layerName;}))
              .build();
        });
      });

  auto expectedDebugMessenger = expectedVkInstance.then([&l](auto const& instance) {
    return instance.debugMessengerBuilder().build(l);
  });

  Vector<Api const*> apis {&glfw};
  if (expectedVkInstance) {
    apis.emplaceBack(&*expectedVkInstance);
  }

  Engine e {mv(apis)};

  auto window = glfw.windowManager()
      .windowBuilder()
      .withSize(1920, 1080)
      .windowed()
      // .windowedFullscreen(glfw.displayManager().primaryDisplay())
      .build();

  auto expectedSurface = expectedVkInstance.then([window](auto const& instance) {
    return instance.createSurface(*window);
  });

  auto expectedDevice = expectedSurface.then([&expectedVkInstance](auto const& surface) {
    return expectedVkInstance.then(&Instance::physicalDevices).transform([&surface](auto const& devices) {
      auto optDevice = devices | filter([&surface](PhysicalDevice const& device) {
        return device.features().geometryShader
            && device.properties().deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU
            && device.surfaceFormats(surface)
            && device.surfacePresentModes(surface);
      }) | findAny();

      if (!optDevice) {
        std::cerr << "No discrete GPU with present support";
        std::terminate();
      }

      return *optDevice;
    });
  });

  auto expectedLogicalDevice = expectedVkInstance.then([&expectedDevice, &expectedSurface, ref = LoggerRef{l}](Instance const& instance) {
    return expectedDevice.then([&instance, &expectedSurface, ref](PhysicalDevice const& device) {
      return expectedSurface.then([&instance, &device, ref](Surface const& surface)
          -> Expected<LogicalDevice, VkResult> {
        auto&& queueFamilies = device.queueFamilies();
        Vector<U32> remainingQueues {queueFamilies
            | project(&QueueFamily::properties)
            | project(&VkQueueFamilyProperties::queueCount)};
        ref() << "Selected Device Queue Family Properties:";
        queueFamilies
            | project(&QueueFamily::properties)
            | forEach([ref](auto const& properties) {
              ref() << ref.invoke("\t{:a}"_f, properties);
            });

        auto const queryQueuesFor = [&remainingQueues, &queueFamilies]<typename P>(P&& predicate) {
          return (queueFamilies
                | filter(fwd<P>(predicate))
                | filter([&remainingQueues](auto const& family) { return remainingQueues[family.index()] > 0; })
                | project([](auto const& family) { return &family; })
                | findAny()).getOr(nullptr);
        };

        auto const graphicsFamily = queryQueuesFor(&QueueFamily::supportsGraphics);
        if (!graphicsFamily) {
          ref() << "Unable to find a queue family supporting graphics";
          return Unexpected{VK_ERROR_UNKNOWN};
        }
        --remainingQueues[graphicsFamily->index()];

        auto const transferFamily = queryQueuesFor(&QueueFamily::supportsTransfer);
        if (!transferFamily) {
          ref() << "Unable to find a queue family supporting transfer";
          return Unexpected{VK_ERROR_UNKNOWN};
        }
        --remainingQueues[transferFamily->index()];

        auto const presentFamily = queryQueuesFor([&surface](auto const& family) {
          return family.supportsPresentOn(surface);
        });
        if (!presentFamily) {
          ref() << "Unable to find a queue family supporting present to surface";
          return Unexpected{VK_ERROR_UNKNOWN};
        }

        return instance.logicalDeviceBuilder()
            .addQueueFrom(*graphicsFamily, 1.0f)
            .addQueueFrom(*transferFamily, 1.0f)
            .addQueueFrom(*presentFamily, 1.0f)
            .withExtensions(Vector{ExtensionTraits<Extension::KHR_swapchain>::name})
            .build(device);
      });
    });
  });

  return e.run();
}

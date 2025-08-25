//
// Created by loghin on 10/17/24.
//

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <filesystem>

#include <cds/Expected>
#include <cds/Format>
#include <cds/StringView>
#include <cds/collection/HashMap>
#include <cds/collection/VectorView>

// #include "api/vulkan/core/VulkanTypesToString.hpp"

#include "generic/engine/Engine.hpp"
#include "generic/log/Logger.hpp"

#include "api/glfw/Glfw.hpp"
#include "api/vulkan/Vulkan.hpp"
#include "api/vulkan/debug/VulkanDebug.hpp"
#include "api/vulkan/device/VulkanPhysicalDevice.hpp"
#include "api/vulkan/device/VulkanLogicalDevice.hpp"
#include "api/vulkan/device/VulkanQueue.hpp"
#include "api/vulkan/device/VulkanQueueFamily.hpp"
#include "api/vulkan/memory/VulkanImage.hpp"
#include "api/vulkan/memory/VulkanImageView.hpp"
#include "api/vulkan/instance/VulkanInstance.hpp"
#include "api/vulkan/renderer/command/VulkanCommandBuffer.hpp"
#include "api/vulkan/renderer/command/VulkanCommandPool.hpp"
#include "api/vulkan/renderer/VulkanPipeline.hpp"
#include "api/vulkan/renderer/VulkanPipelineLayout.hpp"
#include "api/vulkan/shader/VulkanShaderModule.hpp"
#include "api/vulkan/sync/VulkanSemaphore.hpp"
#include "api/vulkan/sync/VulkanFence.hpp"
#include "api/vulkan/wsi/VulkanSwapChain.hpp"
#include "api/vulkan/wsi/VulkanSurface.hpp"

#include <generic/lang/Range.hpp>

#include "core/VulkanExtensions.hpp"
#include "core/VulkanLayers.hpp"

#include "api/vulkan/core/VulkanHandles.hpp"

namespace {
using cds::Expected;
using cds::HashMap;
using cds::Optional;
using cds::StringView;
using cds::U32;
using cds::U64;
using cds::Unexpected;
using cds::Union;
using cds::Vector;
using cds::VectorView;
using cds::ignore;
using cds::nullopt;

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
using c_eng::api::vk::CommandBufferRef;
using c_eng::api::vk::CommandRecorder;
using c_eng::api::vk::CommandPool;
using c_eng::api::vk::Fence;
using c_eng::api::vk::FenceBuilder;
using c_eng::api::vk::Vulkan;
using c_eng::api::vk::Image;
using c_eng::api::vk::ImageView;
using c_eng::api::vk::Instance;
using c_eng::api::vk::Queue;
using c_eng::api::vk::QueueFamily;
using c_eng::api::vk::LogicalDevice;
using c_eng::api::vk::PhysicalDevice;
using c_eng::api::vk::Pipeline;
using c_eng::api::vk::PipelineBuilder;
using c_eng::api::vk::PipelineLayout;
using c_eng::api::vk::PipelineLayoutBuilder;
using c_eng::api::vk::Semaphore;
using c_eng::api::vk::SemaphoreBuilder;
using c_eng::api::vk::Surface;
using c_eng::api::vk::ShaderModule;
using c_eng::api::vk::SwapChain;
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

struct MemBlock {
  U64 size;
  U64 alignment;
  VkSystemAllocationScope scope;
};

struct MemSizeBlock {
  LoggerRef logger;
  bool loggingEnabled;
  HashMap<void*, MemBlock> memBlocks;
  U64 totalUsage{0u};
  bool logAlloc{false};

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
    if (memBlock->logAlloc) {
      logger() << logger.invoke("Vulkan allocated at {} {} bytes aligned at {} bytes in '{}'"_f, mem, size, alignment, scope);
    }
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
      if (memBlock->logAlloc) {
        logger() << logger.invoke("Vulkan reallocated from {} of {} bytes to {} of {} bytes, aligned at {} bytes in '{}'"_f, pOriginal, block.size, mem, size, alignment, scope);
      }
      memBlock->totalUsage -= it->value().size;
      memBlock->memBlocks.remove(it);
      memBlock->totalUsage +=
          get<0>(memBlock->memBlocks.emplace(mem, size, alignment, scope))->value().size;
    } else {
      if (memBlock->logAlloc) {
        logger() << logger.invoke("Vulkan reallocated at {} from {} bytes to {} bytes, aligned at {} bytes in '{}'"_f, pOriginal, block.size, size, alignment, scope);
      }
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
  std::ios::sync_with_stdio(false);

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

  auto expectedVkInstance = cds::tie(expectedVk, expectedRequiredLayers)
      .appliedThen([&l, &allocationCallbacks, &requestedVulkanExtensions](Vulkan const& vk, auto const& layers) {
        VkBool32 disableRayQuerySetting = VK_FALSE;
        VkLayerSettingEXT disableRayQuery{
            .pLayerName = LayerTraits<Layer::LAYER_KHRONOS_validation>::name,
            .pSettingName = "gpuav_validate_ray_query",
            .type = VK_LAYER_SETTING_TYPE_BOOL32_EXT,
            .valueCount = 1u,
            .pValues = &disableRayQuerySetting
        };

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
            .withLayerSettings(Vector{disableRayQuery})
            .withExtraValidationFeatures(Vector{
                VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_EXT,
                VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_RESERVE_BINDING_SLOT_EXT,
                VK_VALIDATION_FEATURE_ENABLE_BEST_PRACTICES_EXT,
                VK_VALIDATION_FEATURE_ENABLE_DEBUG_PRINTF_EXT,
                VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT,
            }).withLayers(layers | project([](auto const& layerProperties){return layerProperties.layerName;}))
            .build();
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

  auto expectedDevice = cds::tie(expectedVkInstance.then(&Instance::physicalDevices), expectedSurface)
      .appliedTransform([](auto const& devices, Surface const& surface) {
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

  // From GPU assisted validation suggestions
  auto extraFeatureSuggestions = expectedDevice.transform([](PhysicalDevice const& device) {
    auto features = device.features<
        VkPhysicalDeviceVulkan11Features,
        VkPhysicalDeviceVulkan13Features,
        VkPhysicalDeviceTimelineSemaphoreFeatures,
        VkPhysicalDeviceVulkanMemoryModelFeatures,
        VkPhysicalDeviceBufferDeviceAddressFeatures,
        VkPhysicalDevice8BitStorageFeatures,
        VkPhysicalDeviceRayQueryFeaturesKHR,
        VkPhysicalDeviceRayTracingValidationFeaturesNV
    >();

    // required by slang -> SPIR_V for SV_vertexId
    get<VkPhysicalDeviceVulkan11Features>(features).shaderDrawParameters = VK_TRUE;
    get<VkPhysicalDeviceRayQueryFeaturesKHR>(features).rayQuery = VK_FALSE;
    get<VkPhysicalDeviceRayTracingValidationFeaturesNV>(features).rayTracingValidation = VK_FALSE;

    // dynamic rendering, nullptr render pass
    get<VkPhysicalDeviceVulkan13Features>(features).dynamicRendering = VK_TRUE;

    return features;
  });

  auto&& expectedQueueFamilies = expectedDevice.transform(&PhysicalDevice::queueFamilies);
  auto expectedLogicalDevice = cds::tie(expectedVkInstance, expectedDevice, expectedSurface, expectedQueueFamilies)
      .appliedThen([ref = LoggerRef{l}, &extraFeatureSuggestions](
          Instance const& instance,
          PhysicalDevice const& device,
          Surface const& surface,
          auto const& queueFamilies
      ) -> Expected<LogicalDevice, VkResult> {
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

        auto builder = instance.logicalDeviceBuilder();

        builder
            .addQueueFrom(*graphicsFamily, 1.0f)
            .addQueueFrom(*transferFamily, 1.0f)
            .addQueueFrom(*presentFamily, 1.0f)
            .withExtensions(Vector{ExtensionTraits<Extension::KHR_swapchain>::name});

        if (extraFeatureSuggestions) {
          builder.withFeatures(static_cast<VkPhysicalDeviceFeatures2 const&>(*extraFeatureSuggestions));
        }

        return builder.build(device);
      });

  auto expectedQueues = expectedLogicalDevice.transform(&LogicalDevice::queues);
  auto expectedSwapChainFamilies = cds::tie(expectedQueues, expectedSurface).appliedTransform([](auto const& queues, auto const& surface) {
    Vector<QueueFamily> families;
    for (auto const& [family, _] : queues) {
      if (family.supportsGraphics() && family.supportsPresentOn(surface)) {
        families.emplaceBack(family);
      }
    }
    return families;
  });

  auto expectedSwapChain = cds::tie(expectedLogicalDevice, expectedSurface, expectedSwapChainFamilies)
      .appliedThen([](auto const& device, auto const& surface, auto const& swapChainFamilies) {
        return SwapChain::builder(device)
            .withImagesAccessedBy(swapChainFamilies)
            .build(surface);
      });

  auto expectedSwapChainImages = expectedSwapChain.then(&SwapChain::images);
  auto expectedSwapChainImageViews = cds::tie(expectedLogicalDevice, expectedSwapChainImages)
      .appliedThen([](auto const& device, auto const& images) -> Expected<Vector<ImageView>, VkResult>  {
        Vector<ImageView> imageViews;
        for (auto const& image : images) {
          if (auto expectedView = ImageView::builder(device).build(image)) {
            imageViews.pushBack(*mv(expectedView));
          } else {
            return Unexpected{expectedView.error()};
          }
        }
        return imageViews;
      });

  auto triangleShaderModule = expectedLogicalDevice.transform(&ShaderModule::builder).then([](auto const& builder) {
    return builder.buildFromPrecompiledShaderAt("../triangle.spv");
  });

  auto layout = expectedLogicalDevice
      .transform(&PipelineLayout::builder)
      .then(&PipelineLayoutBuilder::build);

  auto pipeline = cds::tie(expectedLogicalDevice, triangleShaderModule, expectedSwapChain, layout).appliedThen([](
      LogicalDevice const& device,
      ShaderModule const& shaderModule,
      SwapChain const& swapChain,
      PipelineLayout const& layout
  ) {
    return Pipeline::builder(device)
        .withShader(shaderModule, VkShaderStageFlagBits::VK_SHADER_STAGE_VERTEX_BIT, "vertexShader")
        .withShader(shaderModule, VkShaderStageFlagBits::VK_SHADER_STAGE_FRAGMENT_BIT, "fragmentShader")
        .withPipelineLayout(layout)
        .renderOn(swapChain)
        .withDynamicStates({VkDynamicState::VK_DYNAMIC_STATE_VIEWPORT, VkDynamicState::VK_DYNAMIC_STATE_SCISSOR})
        .build();
  });

  auto commandPool = cds::tie(expectedLogicalDevice).appliedThen(
      [](LogicalDevice const& device)
          -> Expected<CommandPool, VkResult> {
        for (auto const& [family, queues] : device.queues()) {
          if (family.supportsGraphics()) {
            return CommandPool::builder(device).build(family);
          }
        }

        return Unexpected{VkResult::VK_ERROR_NOT_PERMITTED};
      });

  auto commandBuffers = commandPool.transform(&CommandPool::allocator).then([](auto const& allocator) {
    return allocator.allocatePrimary(1);
  });

  auto commandBuffer = commandBuffers.transform([](auto const& buffers) {
    return buffers[0];
  });

  auto drawImage = cds::tie(commandBuffer, expectedSwapChainImageViews, expectedSwapChain, pipeline).appliedTransform(
      [](auto buffer, auto const& imageViews, auto const& swapChain, auto const& pipeline) {
        return [buffer, &imageViews, &swapChain, &pipeline](cds::Size imageIndex) {
          return buffer.record([&imageViews, imageIndex, &swapChain, &pipeline](CommandRecorder& recorder) {
            recorder.transitionImageLayout(
                imageViews[imageIndex].image(),
                VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED,
                VkImageLayout::VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
                0u,
                VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT,
                VK_PIPELINE_STAGE_2_TOP_OF_PIPE_BIT,
                VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT
            );

            auto const attachmentInfo = VkRenderingAttachmentInfo{
                .sType = VkStructureType::VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO,
                .pNext = nullptr,
                .imageView = imageViews[imageIndex].handle(),
                .imageLayout = VkImageLayout::VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
                .resolveMode = VkResolveModeFlagBits::VK_RESOLVE_MODE_NONE,
                .resolveImageView = VK_NULL_HANDLE,
                .resolveImageLayout = VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED,
                .loadOp = VkAttachmentLoadOp::VK_ATTACHMENT_LOAD_OP_CLEAR,
                .storeOp = VkAttachmentStoreOp::VK_ATTACHMENT_STORE_OP_STORE,
                .clearValue = {.color = {.float32 = {0.0f, 0.0f, 0.0f, 1.0f}}},
            };

            auto const swapChainExtent = swapChain.imageExtent();
            recorder.beginRendering({
                .sType = VkStructureType::VK_STRUCTURE_TYPE_RENDERING_INFO,
                .pNext = nullptr,
                .flags = 0u,
                .renderArea = {
                    .offset = {0u, 0u},
                    .extent = swapChainExtent
                },
                .layerCount = 1u,
                .viewMask = 0u,
                .colorAttachmentCount = 1u,
                .pColorAttachments = &attachmentInfo,
                .pDepthAttachment = nullptr,
                .pStencilAttachment = nullptr,
            });

            recorder.bindPipeline(pipeline);
            recorder.setViewport(VkViewport{
                .x = 0.0f,
                .y = 0.0f,
                .width = static_cast<float>(swapChainExtent.width),
                .height = static_cast<float>(swapChainExtent.height),
                .minDepth = 0.0f,
                .maxDepth = 1.0f,
            });
            recorder.setScissor(VkRect2D{
                .offset = {
                    .x = 0,
                    .y = 0,
                },
                .extent = swapChainExtent,
            });
            recorder.draw(3, 1, 0, 0);
            recorder.endRendering();
            recorder.transitionImageLayout(
                imageViews[imageIndex].image(),
                VkImageLayout::VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
                VkImageLayout::VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
                VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT,
                0u,
                VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT,
                VK_PIPELINE_STAGE_2_BOTTOM_OF_PIPE_BIT
            );
          });
        };
      });

  auto presentComplete = expectedLogicalDevice.transform(&Semaphore::builder).then(&SemaphoreBuilder::build);
  auto renderFinished = expectedLogicalDevice.transform(&Semaphore::builder).then(&SemaphoreBuilder::build);
  auto drawFence = expectedLogicalDevice.transform(&Fence::builder).transform(&FenceBuilder::signalled).then(&FenceBuilder::build);
  auto graphicsQueue = cds::tie(expectedLogicalDevice, commandPool).appliedThen(
      [](LogicalDevice const& device, CommandPool const& buffer) -> Expected<Queue, VkResult> {
        for (auto const& [family, queues] : device.queues()) {
          if (family.index() == buffer.family().index() && queues) {
            return queues[0];
          }
        }

        return Unexpected{VkResult::VK_ERROR_OUT_OF_DEVICE_MEMORY};
      });
  auto presentQueue = cds::tie(expectedLogicalDevice, expectedSurface).appliedThen(
      [](auto const& device, auto const& surface) -> Expected<Queue, VkResult> {
        for (auto const& [family, queues] : device.queues()) {
          if (family.supportsPresentOn(surface) && queues) {
            return queues[0];
          }
        }

        return Unexpected{VkResult::VK_ERROR_OUT_OF_DEVICE_MEMORY};
      });

  auto preLoopWrapper = cds::tie(
      commandBuffer,
      drawImage,
      expectedSwapChain,
      presentComplete,
      renderFinished,
      drawFence,
      graphicsQueue,
      presentQueue
  ).appliedTransform([&e](
      CommandBufferRef buffer,
      auto const& drawImage,
      SwapChain const& swapChain,
      Semaphore const& presentComplete,
      Semaphore const& renderFinished,
      Fence const& drawFence,
      Queue const& graphicsQueue,
      Queue const& presentQueue
  ) {
    return e.run([&swapChain, &presentComplete, &drawImage, &drawFence, buffer, &graphicsQueue, &renderFinished, &presentQueue] -> Expected<void, int> {
      auto expectedIndex = swapChain.acquireNextImageIndex(cds::limits::u64Max, presentComplete);
      if (!expectedIndex) {
        return Unexpected{1};
      }

      std::uint32_t const index = *expectedIndex;
      if (!drawImage(index)) {
        return Unexpected{2};
      }

      if (drawFence.reset() != VkResult::VK_SUCCESS) {
        return Unexpected{3};
      }

      VkCommandBuffer bufHnd = buffer.handle();
      VkSemaphore presentCompleteSemaphore = presentComplete.handle();
      VkSemaphore renderFinishedSemaphore = renderFinished.handle();
      VkPipelineStageFlags waitDstMask = VkPipelineStageFlagBits::VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
      VkSubmitInfo submitInfo{
          .sType = VkStructureType::VK_STRUCTURE_TYPE_SUBMIT_INFO,
          .pNext = nullptr,
          .waitSemaphoreCount = 1u,
          .pWaitSemaphores = &presentCompleteSemaphore,
          .pWaitDstStageMask = &waitDstMask,
          .commandBufferCount = 1u,
          .pCommandBuffers = &bufHnd,
          .signalSemaphoreCount = 1u,
          .pSignalSemaphores = &renderFinishedSemaphore
      };
      if (graphicsQueue.submit(VectorView{&submitInfo, &submitInfo + 1}, drawFence) != VkResult::VK_SUCCESS) {
        return Unexpected{4};
      }

      while (VkResult::VK_TIMEOUT == drawFence.wait()) {}

      VkSwapchainKHR swapchainHandle = swapChain.handle();
      VkPresentInfoKHR const presentInfo{
          .sType = VkStructureType::VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
          .pNext = nullptr,
          .waitSemaphoreCount = 1u,
          .pWaitSemaphores = &renderFinishedSemaphore,
          .swapchainCount = 1u,
          .pSwapchains = &swapchainHandle,
          .pImageIndices = &index,
          .pResults = nullptr
      };

      if (VkResult::VK_SUCCESS != presentQueue.present(presentInfo)) {
        return Unexpected{5};
      }

      return {};
    });
  });

  auto res = preLoopWrapper.valueOr(1);
  cds::ignore = expectedLogicalDevice.transform(&LogicalDevice::waitIdle);
  return res;
}

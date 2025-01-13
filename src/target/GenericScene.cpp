//
// Created by loghin on 10/17/24.
//
#include <iostream>
#include <variant>

#include <cds/Format>
#include <cds/StringView>

#include "api/vulkan/core/VulkanTypesToString.hpp"

#include "generic/engine/Engine.hpp"
#include "generic/log/Logger.hpp"

#include "api/glfw/Glfw.hpp"

#include <generic/lang/Range.hpp>

import c_eng.api.vk;
import cds;

namespace {
using cds::Optional;
using cds::StringView;
using cds::U32;
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
using enum c_eng::api::GlfwInitParameter;

using c_eng::generic::flatten;
using c_eng::generic::filter;
using c_eng::generic::forEach;
using c_eng::generic::findAny;
using c_eng::generic::project;

using c_eng::api::vk::ApplicationInfo;
using c_eng::api::vk::LogicalDevice;
using c_eng::api::vk::LogicalDeviceFactory;
using c_eng::api::vk::PhysicalDevice;
using c_eng::api::vk::QueueFamily;
using c_eng::api::vk::createInstance;
using c_eng::api::vk::createSurface;
using c_eng::api::vk::layerProperties;
using c_eng::api::vk::physicalDevices;
} // namespace

auto main(int argc, char const* const* argv) noexcept -> int {
  bool disableLogPresent = false;
  for (unsigned idx = 1; idx < argc; ++idx) {
    if (StringView{argv[idx]} == "-dl") {
      disableLogPresent = true;
    }
  }

  Logger l {Vector{{LoggerOutput{std::cout}}}};
  if (disableLogPresent) {
    l.setEnabled(false);
  }

  Glfw glfw{Vector{PlatformX11}, l};
  auto requestedVulkanExtensions = glfw.vulkanExtensions();
  requestedVulkanExtensions.emplaceBack("VK_EXT_debug_utils");

  auto expectedVulkan = layerProperties({"VK_LAYER_KHRONOS_validation"})
      .then([&l, &requestedVulkanExtensions](auto const& layers) {
        ApplicationInfo info {
            .applicationName{"GenericScene"},
            .applicationVersion{0, 0, 1, 0},
            .engineName{"c_eng"},
            .engineVersion{0, 0, 7, 0},
            .targetVulkanApiVersion{0, 1, 3, 0}
        };
        return createInstance(l, layers, requestedVulkanExtensions, info);
      });

  Vector<Api const*> apis {&glfw};
  if (expectedVulkan) {
    apis.emplaceBack(&*expectedVulkan);
  }

  Engine e {mv(apis)};

  auto window = glfw.windowManager()
      .windowBuilder()
      .withSize(1920, 1080)
      .windowed()
      // .windowedFullscreen(glfw.displayManager().primaryDisplay())
      .build();

  auto expectedOptionalDevice = expectedVulkan.then(physicalDevices).transform([](auto const& devices) {
    return devices | filter([](auto const& device) {
        return device.features().geometryShader
            && device.properties().deviceType == PhysicalDevice::Type::VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU;
      }) | findAny();
  });

  auto expectedSurface = expectedVulkan.then([&window](auto const& instance) {
    return createSurface(instance, window);
  });

  auto optionalExpectedLogicalDevice = expectedVulkan.then([&expectedSurface, &expectedOptionalDevice, &l](auto const& instance) {
    return expectedSurface.then([&instance, &expectedOptionalDevice, &l](auto const& surface) {
      return expectedOptionalDevice.then([&surface, &instance, &l](auto const& optionalDevice) {
        return optionalDevice.then([&surface, &instance, &l](PhysicalDevice const& device)
            -> Optional<Expected<LogicalDevice, VkResult>> {
          auto&& queueFamilies = device.queueFamilies();
          Vector<U32> remainingQueues {queueFamilies
              | project(&QueueFamily::properties)
              | project(&QueueFamily::Properties::queueCount)};
          LoggerRef lr{l};
          lr() << "Selected Device Queue Family Properties:";
          queueFamilies
              | project(&QueueFamily::properties)
              | forEach([&lr](auto const& properties) {
                lr() << lr.invoke("\t{:#}"_f, properties);
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
            return nullopt;
          }
          --remainingQueues[graphicsFamily->index()];

          auto const transferFamily = queryQueuesFor(&QueueFamily::supportsTransfer);
          if (!transferFamily) {
            return nullopt;
          }
          --remainingQueues[transferFamily->index()];

          auto const presentFamily = queryQueuesFor([&surface](auto const& family) {
            return family.supportsPresentOn(surface);
          });
          if (!presentFamily) {
            return nullopt;
          }

          return LogicalDeviceFactory()
              .addQueueFrom(*graphicsFamily, 1.0f)
              .addQueueFrom(*transferFamily, 1.0f)
              .addQueueFrom(*presentFamily, 1.0f)
              .presentOn(surface)
              .build(device);
        });
      });
    });
  });

  // auto optionalExpectedRenderer = expectedVulkan.then([&window, &expectedOptionalDevice](auto const& instance) {
  //   return expectedOptionalDevice.then([&window, &instance](auto const& optionalDevice) {
  //     return optionalDevice.transform([&window, &instance](auto const& device) {
  //       return createRenderer(instance, window, device);
  //     });
  //   });
  // });

  return e.run();
}

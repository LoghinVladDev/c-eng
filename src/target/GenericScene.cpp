//
// Created by loghin on 10/17/24.
//
#include <iostream>

#include <cds/StringView>

#include "generic/engine/Engine.hpp"
#include "generic/log/Logger.hpp"

#include "api/glfw/Glfw.hpp"

#include <generic/lang/Range.hpp>

#include <vulkan/vulkan.h>

import c_eng.api.vk;
import cds;

namespace {
using cds::StringView;
using cds::Vector;
using cds::ignore;
using cds::experimental::Expected;
using cds::impl::mv;

using c_eng::generic::Api;
using c_eng::generic::Engine;
using c_eng::generic::Logger;
using c_eng::generic::LoggerRef;
using c_eng::generic::LoggerOutput;

using c_eng::api::Glfw;
using enum c_eng::api::GlfwInitParameter;

using c_eng::generic::flatten;
using c_eng::generic::filter;
using c_eng::generic::findAny;
using c_eng::generic::project;

using c_eng::api::vk::ApplicationInfo;
using c_eng::api::vk::PhysicalDevice;
using c_eng::api::vk::createInstance;
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

  auto expectedRenderer = expectedVulkan.then([&window, &expectedOptionalDevice](auto const& instance) {
    return expectedOptionalDevice.then([&window, &instance](auto const& optionalDevice) {
      return optionalDevice.transform([&window, &instance](auto const& device) {
        return createRenderer(instance, window, device);
      });
    });
  });

  return e.run();
}

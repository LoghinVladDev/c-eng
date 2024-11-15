//
// Created by loghin on 10/17/24.
//
#include <iostream>

#include <cds/StringView>

#include "api/vulkan/VulkanTypesToString.hpp"

#include "generic/engine/Engine.hpp"
#include "generic/log/Logger.hpp"

#include "api/glfw/Glfw.hpp"

#include <generic/lang/Range.hpp>

import c_eng.api.vk;
import cds;

namespace {
using cds::StringView;
using cds::Vector;
using cds::ignore;
using cds::experimental::Expected;

using c_eng::generic::Engine;
using c_eng::generic::Logger;
using c_eng::generic::LoggerRef;
using c_eng::generic::LoggerOutput;

using c_eng::api::Glfw;
using enum c_eng::api::GlfwInitParameter;

using c_eng::generic::flatten;
using c_eng::generic::filter;
using c_eng::generic::project;

using c_eng::api::vk::ApplicationInfo;
using c_eng::api::vk::createInstance;
using c_eng::api::vk::layerProperties;
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

  auto vulkan = layerProperties({"VK_LAYER_KHRONOS_validation"})
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

  //
  //
  // ignore = layerProperties({{"VK_LAYER_KHRONOS_validation"}})
  //     .transform([log = LoggerRef{l}](auto const& properties) {
  //       log() << "Vulkan - Available Instance Layer Properties:";
  //       for (auto const& property : properties) {
  //         log() << log.invoke("\t{}"_f, property);
  //       }
  //       return properties;
  //     });

  Engine e {{&glfw}};

  // auto window = glfw.windowManager()
  //     .windowBuilder()
  //     .withSize(1920, 1080)
  //     .windowed()
  //     // .windowedFullscreen(glfw.displayManager().primaryDisplay())
  //     .build();

  return e.run();
}

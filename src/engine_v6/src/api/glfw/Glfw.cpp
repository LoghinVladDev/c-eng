//
// Created by Vlad-Andrei Loghin on 14.06.23.
//

#include "Glfw.hpp"
#include <core/ResourceTracker.hpp>

#include <GLFW/glfw3.h>

#include <CDS/memory/UniquePointer>

using namespace engine;
using namespace cds;
using namespace cds::literals;

namespace {
Api::Info const defaultApiInfo = {
    .name         = "GLFW",
    .description  = "Platform Independent API for window management and event handling",
    .purpose      = "mandatory=[surface, controller, keyboard, mouse, system], optional=[window]",
    .vendor       = "The GLFW Organization, domain - glfw.org, Licence Holder of GLFW - zlib/libpng licence",
    .vendorId     = Api::unknownVendorId,
    .sourceType   = engine::Api::SourceType::OpenSource,
    .version      = {
        .variant      = variant::original,
        .major        = 0,
        .minor        = 0,
        .patch        = 0
    }
};

class GlfwInstanceTracker : public ResourceTracker <Glfw> {};

constexpr auto glfwCodeToString(int code) noexcept -> char const* {
  switch (code) {
    case GLFW_NOT_INITIALIZED:      return "GLFW_NOT_INITIALIZED";
    case GLFW_NO_CURRENT_CONTEXT:   return "GLFW_NO_CURRENT_CONTEXT";
    case GLFW_INVALID_ENUM:         return "GLFW_INVALID_ENUM";
    case GLFW_INVALID_VALUE:        return "GLFW_INVALID_VALUE";
    case GLFW_OUT_OF_MEMORY:        return "GLFW_OUT_OF_MEMORY";
    case GLFW_API_UNAVAILABLE:      return "GLFW_API_UNAVAILABLE";
    case GLFW_VERSION_UNAVAILABLE:  return "GLFW_VERSION_UNAVAILABLE";
    case GLFW_PLATFORM_ERROR:       return "GLFW_PLATFORM_ERROR";
    case GLFW_FORMAT_UNAVAILABLE:   return "GLFW_FORMAT_UNAVAILABLE";
    default:
      assert(false && "glfwCodeToString - Unmapped error code");
      return "";
  }
}

auto getGlfwError () noexcept {
  char const* pDescription;
  auto code = glfwGetError(&pDescription);
  return String() + glfwCodeToString(code) + ", " + pDescription;
}

auto errorCallback(int code, char const* pDescription) noexcept -> void {
  auto& logger = Logger::getLogger(Glfw::loggerName);
  logger() << Logger::Error << "Glfw Error: " << glfwCodeToString(code) << ", " << pDescription;
}

auto monitorCallback(GLFWmonitor* pDisplayHandle, int event) noexcept -> void {
  (void) pDisplayHandle;
  (void) event;
  for (auto* instance : GlfwInstanceTracker::tracker().instances()) {
    // TODO: pass to dm
  }
}

class GlfwException : public RuntimeException {
public:
  GlfwException() noexcept : RuntimeException ("Glfw Exception: "_s + getGlfwError()) {}
};
} // namespace

auto Glfw::apiInfo() const noexcept -> Info const& {
  return _apiInfo;
}

auto Glfw::getComponentList() noexcept -> Array<ApiComponent*> {
  return {};
}

Glfw::Glfw(Engine* pParent) noexcept(false) : Api(pParent), _apiInfo{defaultApiInfo} {
  logger() << "Initializing GLFW" << std::endl;

  if (GLFW_FALSE == glfwInit()) {
    throw GlfwException();
  }

  GlfwInstanceTracker::tracker().track(this);
  glfwSetErrorCallback(&errorCallback);
  glfwSetMonitorCallback(&monitorCallback);

  int runtimeMajor = 0;
  int runtimeMinor = 0;
  int runtimePatch = 0;
  glfwGetVersion(&runtimeMajor, &runtimeMinor, &runtimePatch);

  _apiInfo.version.major = static_cast <uint32> (runtimeMajor);
  _apiInfo.version.minor = static_cast <uint32> (runtimeMinor);
  _apiInfo.version.patch = static_cast <uint32> (runtimePatch);

  logger() << "GLFW Initialized Successfully" << std::endl;
}

Glfw::~Glfw() noexcept {
  logger() << "GLFW Shutting Down" << std::endl;

  try {
    GlfwInstanceTracker::tracker().untrack(this);
    if (GlfwInstanceTracker::tracker().instances().empty()) {
      glfwTerminate();
    }
  } catch (...) {
    std::terminate();
  }
}

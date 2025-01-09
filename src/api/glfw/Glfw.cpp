//
// Created by loghin on 10/27/24.
//

#include "Glfw.hpp"
#include "GlfwException.hpp"
#include "generic/TypesToString.hpp"

#include <GLFW/glfw3.h>

#include <cds/Format>
#include <cds/threading/Atomic>

namespace c_eng::api::detail {
namespace {
using std::ostream;

using namespace cds::literals;

using cds::Atomic;
using cds::StringView;
using cds::U32;
using cds::ignore;
using cds::nullopt;
using cds::impl::unreachable;
using enum cds::AtomicMemoryOrder;

using enum generic::detail::LicenceType;

Atomic<unsigned> instanceUsers = 0;

auto constexpr vulkanSurfaceExtensionName = "VK_KHR_surface";
auto constexpr vulkanSurfaceWin32ExtensionName = "VK_KHR_win32_surface";
auto constexpr vulkanSurfaceWaylandExtensionName = "VK_KHR_wayland_surface";
auto constexpr vulkanSurfaceXlibExtensionName = "VK_KHR_xlib_surface";

auto hintOf(GlfwInitParameter const parameter) noexcept {
  switch (parameter) {
    case GlfwInitParameter::PlatformAuto:
    case GlfwInitParameter::PlatformWin32:
    case GlfwInitParameter::PlatformWayland:
    case GlfwInitParameter::PlatformX11:
    case GlfwInitParameter::PlatformNone:
      return GLFW_PLATFORM;
    case GlfwInitParameter::WaylandDisableLibDecor:
      return GLFW_WAYLAND_LIBDECOR;
    case GlfwInitParameter::X11DisableXcbVulkanSurface:
      return GLFW_X11_XCB_VULKAN_SURFACE;
    default:
      assert(false && "Unhandled GlfwInitParameter hintOf case");
      unreachable();
  }
}

auto valueOf(GlfwInitParameter const parameter) noexcept {
  switch (parameter) {
    case GlfwInitParameter::PlatformAuto:
      return GLFW_ANY_PLATFORM;
    case GlfwInitParameter::PlatformWin32:
      return GLFW_PLATFORM_WIN32;
    case GlfwInitParameter::PlatformWayland:
      return GLFW_PLATFORM_WAYLAND;
    case GlfwInitParameter::PlatformX11:
      return GLFW_PLATFORM_X11;
    case GlfwInitParameter::PlatformNone:
      return GLFW_PLATFORM_NULL;
    case GlfwInitParameter::WaylandDisableLibDecor:
      return GLFW_WAYLAND_DISABLE_LIBDECOR;
    case GlfwInitParameter::X11DisableXcbVulkanSurface:
      return GLFW_FALSE;
    default:
      assert(false && "Unhandled GlfwInitParameter valueOf case");
      unreachable();
  }
}

auto isSupported(GlfwInitParameter const parameter) noexcept {
  switch (parameter) {
    case GlfwInitParameter::PlatformWin32:
    case GlfwInitParameter::PlatformWayland:
    case GlfwInitParameter::PlatformX11:
      return glfwPlatformSupported(valueOf(parameter)) == GLFW_TRUE;
    case GlfwInitParameter::PlatformAuto:
    case GlfwInitParameter::PlatformNone:
    case GlfwInitParameter::WaylandDisableLibDecor:
    case GlfwInitParameter::X11DisableXcbVulkanSurface:
      return true;
    default:
      assert(false && "Unhandled GlfwInitParameter isSupported case");
      unreachable();
  }
}

auto asString(GlfwInitParameter const parameter) noexcept {
  switch (parameter) {
    case GlfwInitParameter::PlatformAuto:
      return "GLFW_PLATFORM = GLFW_ANY_PLATFORM";
    case GlfwInitParameter::PlatformWin32:
      return "GLFW_PLATFORM = GLFW_PLATFORM_WIN32";
    case GlfwInitParameter::PlatformWayland:
      return "GLFW_PLATFORM = GLFW_PLATFORM_WAYLAND";
    case GlfwInitParameter::PlatformX11:
      return "GLFW_PLATFORM = GLFW_PLATFORM_X11";
    case GlfwInitParameter::PlatformNone:
      return "GLFW_PLATFORM = GLFW_PLATFORM_NULL";
    case GlfwInitParameter::WaylandDisableLibDecor:
      return "GLFW_WAYLAND_LIBDECOR = GLFW_WAYLAND_DISABLE_LIBDECOR";
    case GlfwInitParameter::X11DisableXcbVulkanSurface:
      return "GLFW_X11_XCB_VULCAN_SURFACE = GLFW_FALSE";
    default:
      assert(false && "Unhandled GlfwInitParameter asString case");
      unreachable();
  }
}

auto applyInitParameters(Vector<GlfwInitParameter> const& parameters, LoggerRef const logger) noexcept(false) {
  for (auto const& param : parameters) {
    if (!isSupported(param)) {
      throw GlfwException("Unsupported parameter: "_s + asString(param));
    }

    logger() << "Using GLFW Init Hint: " << logger.invoke(asString, param);
    glfwInitHint(hintOf(param), valueOf(param));
  }
}

enum class ErrorKind {
  None = GLFW_NO_ERROR,
  NotInitialized = GLFW_NOT_INITIALIZED,
  NoCurrentContext = GLFW_NO_CURRENT_CONTEXT,
  InvalidEnum = GLFW_INVALID_ENUM,
  InvalidValue = GLFW_INVALID_VALUE,
  OutOfMemory = GLFW_OUT_OF_MEMORY,
  ApiUnavailable = GLFW_API_UNAVAILABLE,
  VersionUnavailable = GLFW_VERSION_UNAVAILABLE,
  PlatformError = GLFW_PLATFORM_ERROR,
  FormatUnavailable = GLFW_FORMAT_UNAVAILABLE,
  NoWindowContext = GLFW_NO_WINDOW_CONTEXT,
  CursorUnavailable = GLFW_CURSOR_UNAVAILABLE,
  FeatureUnavailable = GLFW_FEATURE_UNAVAILABLE,
  FeatureUnimplemented = GLFW_FEATURE_UNIMPLEMENTED,
  PlatformUnavailable = GLFW_PLATFORM_UNAVAILABLE,
};

struct Error {
  ErrorKind kind;
  StringView description;
};

auto error() noexcept -> Error {
  char const* desc = nullptr;
  auto code = glfwGetError(&desc);
  return {.kind = static_cast<ErrorKind>(code), .description = desc};
}

auto asString(ErrorKind const kind) noexcept {
  using enum ErrorKind;
  switch (kind) {
    case None:
      return "GLFW_NO_ERROR";
    case NotInitialized:
      return "GLFW_NOT_INITIALIZED";
    case NoCurrentContext:
      return "GLFW_NO_CURRENT_CONTEXT";
    case InvalidEnum:
      return "GLFW_INVALID_ENUM";
    case InvalidValue:
      return "GLFW_INVALID_VALUE";
    case OutOfMemory:
      return "GLFW_OUT_OF_MEMORY";
    case ApiUnavailable:
      return "GLFW_API_UNAVAILABLE";
    case VersionUnavailable:
      return "GLFW_VERSION_UNAVAILABLE";
    case PlatformError:
      return "GLFW_PLATFORM_ERROR";
    case FormatUnavailable:
      return "GLFW_FORMAT_UNAVAILABLE";
    case NoWindowContext:
      return "GLFW_NO_WINDOW_CONTEXT";
    case CursorUnavailable:
      return "GLFW_CURSOR_UNAVAILABLE";
    case FeatureUnavailable:
      return "GLFW_FEATURE_UNAVAILABLE";
    case FeatureUnimplemented:
      return "GLFW_FEATURE_UNIMPLEMENTED";
    case PlatformUnavailable:
      return "GLFW_PLATFORM_UNAVAILABLE";
    default:
      assert(false && "Unhandled asString(ErrorKind) case");
      unreachable();
  }
}

auto errorAsString(Error const& error) noexcept -> String {
  return "{} -> {}"_f(asString(error.kind), error.description);
}

auto requiredVulkanSurfaceExtension(GlfwPlatform const platform) noexcept {
  switch (platform) {
    case GlfwPlatform::Win32:   return vulkanSurfaceWin32ExtensionName;
    case GlfwPlatform::Wayland: return vulkanSurfaceWaylandExtensionName;
    case GlfwPlatform::X11:     return vulkanSurfaceXlibExtensionName;
    default:
      assert(false && "Unhandled `requiredVulkanSurfaceExtension` platform case");
      unreachable();
  }
}
} // namespace

GlfwInstance::GlfwInstance(Vector<GlfwInitParameter> const& parameters, LoggerRef const logger) noexcept(false) :
    _logger{logger} {
  if (instanceUsers.fetchAdd(1u, AcqRel) != 0u) {
    _logger() << "GLFW already initialized, skipping initialization";
    return;
  }

  applyInitParameters(parameters, _logger);
  if (!glfwInit()) {
    auto err = error();
    _logger() << "Unable to initialize GLFW: " << _logger.invoke(errorAsString, err);
    throw GlfwException("Unable to initialize GLFW: "_s + asString(err.kind));
  }
  _logger() << _logger.invoke(
      "GLFW Initialized.\n\tCompiled Version: {}\n\tRuntime Version: {}"_f,
      compiledVersionImpl(), runtimeVersionImpl()
  );
}

GlfwInstance::~GlfwInstance() noexcept {
  if (instanceUsers.fetchSub(1u, AcqRel) == 1u) {
    glfwTerminate();
    _logger() << "GLFW terminated";
  }
}

auto Glfw::info() const noexcept -> ApiInfo {
  ignore = this;
  return {
    .name = "GLFW",
    .description = "GLFW is an Open Source, multi-platform library for OpenGL, "
                   "OpenGL ES and Vulkan development on the desktop.",
    .vendor = "glfw.org",
    .vendorId = nullopt,
    .licenceType = Zlib
  };
}

auto GlfwInstance::compiledVersionImpl() const noexcept -> Version {
  ignore = this;
  return Version {
    .variant = Version::baselineVariant,
    .major = static_cast<U32>(GLFW_VERSION_MAJOR),
    .minor = static_cast<U32>(GLFW_VERSION_MINOR),
    .patch = static_cast<U32>(GLFW_VERSION_REVISION)
  };
}

auto GlfwInstance::runtimeVersionImpl() const noexcept -> Version {
  ignore = this;
  int major;
  int minor;
  int patch;
  glfwGetVersion(&major, &minor, &patch);
  return Version {
    .variant = Version::baselineVariant,
    .major = static_cast<U32>(major),
    .minor = static_cast<U32>(minor),
    .patch = static_cast<U32>(patch)
  };
}

auto Glfw::compiledVersion() const noexcept -> Optional<Version> {
  return compiledVersionImpl();
}

auto Glfw::runtimeVersion() const noexcept -> Optional<Version> {
  return runtimeVersionImpl();
}

auto GlfwInstance::platform() const noexcept -> GlfwPlatform {
  ignore = this;
  using enum GlfwPlatform;
  switch (glfwGetPlatform()) {
    case GLFW_PLATFORM_WIN32:
      return Win32;
    case GLFW_PLATFORM_WAYLAND:
      return Wayland;
    case GLFW_PLATFORM_X11:
      return X11;
    case GLFW_PLATFORM_NULL:
      return None;
    default:
      assert(false && "Unhandled glfwGetPlatform case");
      unreachable();
  }
}

auto Glfw::vulkanExtensions() const noexcept -> Vector<StringView> {
  return {vulkanSurfaceExtensionName, requiredVulkanSurfaceExtension(platform())};
}
} // namespace c_eng::api::detail

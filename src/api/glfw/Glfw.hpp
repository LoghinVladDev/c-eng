//
// Created by loghin on 10/27/24.
//

#pragma once

#include <cds/Optional>
#include <cds/Tuple>
#include <cds/Union>
#include <cds/collection/Vector>

#include "generic/api/Api.hpp"
#include "generic/log/Logger.hpp"

#include "GlfwDisplay.hpp"
#include "GlfwWindow.hpp"
#include "GlfwEventPollingManager.hpp"

namespace c_eng::api::detail {
using cds::Optional;
using cds::StringView;
using cds::Tuple;
using cds::Union;
using cds::Vector;

using generic::Api;
using generic::ApiInfo;
using generic::Version;
using generic::LoggerRef;

enum class GlfwInitParameter {
  PlatformAuto,
  PlatformWin32,
  PlatformCocoa,
  PlatformWayland,
  PlatformX11,
  PlatformNone,
  WaylandDisableLibDecor,
  X11DisableXcbVulkanSurface,
};

enum class GlfwPlatform {
  Win32,
  Cocoa,
  Wayland,
  X11,
  None,
};

class GlfwInstance {
public:
  explicit GlfwInstance(Vector<GlfwInitParameter> const&, LoggerRef) noexcept(false);
  virtual ~GlfwInstance() noexcept;

  [[nodiscard]] auto platform() const noexcept -> GlfwPlatform;

protected:
  [[nodiscard]] auto compiledVersionImpl() const noexcept -> Version;
  [[nodiscard]] auto runtimeVersionImpl() const noexcept -> Version;

private:
  LoggerRef _logger;
};

class GlfwController : public GlfwInstance {
public:
  explicit GlfwController(Vector<GlfwInitParameter> const& params, LoggerRef logger) noexcept(false) :
      GlfwInstance{params, logger},
      _displayManager{this, logger},
      _windowManager{this, logger} {}

  ~GlfwController() noexcept override = default;

  [[nodiscard]] constexpr auto instance() const noexcept -> auto const& {
    return *static_cast<GlfwInstance const*>(this);
  }

  [[nodiscard]] constexpr auto instance() noexcept -> auto& {
    return *static_cast<GlfwInstance*>(this);
  }

  [[nodiscard]] constexpr auto displayManager() const noexcept -> auto const& {
    return _displayManager;
  }

  [[nodiscard]] constexpr auto displayManager() noexcept -> auto& {
    return _displayManager;
  }

  [[nodiscard]] constexpr auto windowManager() const noexcept -> auto const& {
    return _windowManager;
  }

  [[nodiscard]] constexpr auto windowManager() noexcept -> auto& {
    return _windowManager;
  }

  [[nodiscard]] constexpr auto eventPollingManager() const noexcept -> auto const& {
    return _eventPollingManager;
  }

  [[nodiscard]] constexpr auto eventPollingManager() noexcept -> auto& {
    return _eventPollingManager;
  }

private:
  GlfwDisplayManager _displayManager;
  GlfwWindowManager _windowManager;
  GlfwEventPollingManager _eventPollingManager;
};

class Glfw : public GlfwController, public Api {
public:
  explicit Glfw(Vector<GlfwInitParameter> const& params = {}, LoggerRef logger = {}) noexcept(false) :
      GlfwController{params, logger},
      Api{{&displayManager(), &windowManager(), &eventPollingManager()}} {}

  ~Glfw() noexcept override = default;
  [[nodiscard]] auto info() const noexcept -> ApiInfo override;
  [[nodiscard]] auto compiledVersion() const noexcept -> Optional<Version> override;
  [[nodiscard]] auto runtimeVersion() const noexcept -> Optional<Version> override;

  [[nodiscard]] auto vulkanExtensions() const noexcept -> Vector<StringView>;
};
} // namespace c_eng::api::detail

namespace c_eng::api {
using detail::GlfwInitParameter;
using detail::Glfw;
} // namespace c_eng::api

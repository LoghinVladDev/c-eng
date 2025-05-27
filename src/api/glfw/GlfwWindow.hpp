//
// Created by loghin on 11/9/24.
//

#pragma once

#include <cds/collection/Vector>
#include <cds/memory/UniquePtr>

#include <generic/api/WindowManagerApiComponent.hpp>
#include <generic/log/Logger.hpp>

namespace c_eng::api::detail {
using cds::UniquePtr;
using cds::Vector;

using generic::AbstractWindowBuilder;
using generic::LoggerRef;
using generic::Window;
using generic::WindowBuilderDecorator;
using generic::WindowManagerApiComponent;

class GlfwController;

class GlfwWindowManager : public WindowManagerApiComponent {
public:
  class GlfwWindowBuilder : public AbstractWindowBuilder, public WindowBuilderDecorator<GlfwWindowBuilder> {
    using Decorator = WindowBuilderDecorator;

  public:
    using Decorator::withX;
    using Decorator::withY;
    using Decorator::withPosition;
    using Decorator::withWidth;
    using Decorator::withHeight;
    using Decorator::withSize;
    using Decorator::withRect;
    using Decorator::withTitle;
    using Decorator::windowed;
    using Decorator::fullscreen;
    using Decorator::windowedFullscreen;

    explicit GlfwWindowBuilder(GlfwWindowManager& manager) noexcept : _manager{manager} {}
    ~GlfwWindowBuilder() noexcept override = default;

    [[nodiscard]] auto build() const noexcept(false) -> Window* override;

  private:
    GlfwWindowManager& _manager;
  };

  GlfwWindowManager(GlfwController const* instance, LoggerRef logger);
  ~GlfwWindowManager() noexcept override = default;

  [[nodiscard]] auto windowBuilder() noexcept -> GlfwWindowBuilder;
  [[nodiscard]] auto abstractWindowBuilder() noexcept -> UniquePtr<AbstractWindowBuilder> override;
  auto close(Window* window) noexcept -> void override;

  [[nodiscard]] auto instance() const noexcept -> GlfwInstance const*;

private:
  Vector<UniquePtr<Window>> _windows;
  GlfwController const* _controller;
  LoggerRef _logger;
};
} // namespace c_eng::api::detail

namespace c_eng::api {
using detail::GlfwWindowManager;
} // namespace c_eng::api

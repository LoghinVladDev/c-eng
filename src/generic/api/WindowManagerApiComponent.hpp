//
// Created by loghin on 10/27/24.
//

#pragma once

#include <cds/String>
#include <cds/Format>
#include <cds/memory/UniquePtr>

#include <generic/Types.hpp>
#include <generic/lang/Concepts.hpp>

#include "PersistentApiComponent.hpp"

namespace c_eng::native::detail {
struct NativeWindowData;
} // namespace c_eng::native

namespace c_eng::generic::detail {
using cds::RuntimeException;
using cds::Size;
using cds::String;
using cds::UniquePtr;

using native::detail::NativeWindowData;

using namespace cds::literals;

class Display;

class IncompatibleDisplayException : public RuntimeException {
public:
  explicit IncompatibleDisplayException(StringView required) noexcept :
      RuntimeException{"IncompatibleDisplayException: Display of '{}' type required."_f(required)} {}
};

class Window : public PersistentApiObject {
public:
  ~Window() noexcept override = default;
  virtual auto close() noexcept -> void = 0;
  virtual auto acquireNativeWindowData(NativeWindowData* pNativeData) const noexcept -> bool = 0;
};

class AbstractWindowBuilder {
public:
  static auto constexpr defaultWindowWidth = 1280u;
  static auto constexpr defaultWindowHeight = 720u;
  static auto constexpr defaultWindowX = 0;
  static auto constexpr defaultWindowY = 0;
  static auto constexpr defaultWindowTitle = "c_eng";

  auto withX(SSize x) noexcept -> AbstractWindowBuilder& {
    _rect.position.x = x;
    return *this;
  }

  auto withY(SSize y) noexcept -> AbstractWindowBuilder& {
    _rect.position.y = y;
    return *this;
  }

  auto withPosition(SSize x, SSize y) noexcept -> AbstractWindowBuilder& {
    _rect.position = {x, y};
    return *this;
  }

  auto withPosition(Point2D pos) noexcept -> AbstractWindowBuilder& {
    _rect.position = pos;
    return *this;
  }

  auto withWidth(Size width) noexcept -> AbstractWindowBuilder& {
    _rect.area.width = width;
    return *this;
  }

  auto withHeight(Size height) noexcept -> AbstractWindowBuilder& {
    _rect.area.height = height;
    return *this;
  }

  auto withSize(Area2D area) noexcept -> AbstractWindowBuilder& {
    _rect.area = area;
    return *this;
  }

  auto withSize(Size width, Size height) noexcept -> AbstractWindowBuilder& {
    _rect.area = {width, height};
    return *this;
  }

  auto withRect(Rect2D rect) noexcept -> AbstractWindowBuilder& {
    _rect = rect;
    return *this;
  }

  auto withRect(Point2D pos, Area2D area) noexcept -> AbstractWindowBuilder& {
    _rect = {pos, area};
    return *this;
  }

  auto withRect(SSize x, SSize y, Size width, Size height) noexcept -> AbstractWindowBuilder& {
    _rect = {{x, y}, {width, height}};
    return *this;
  }

  auto withTitle(StringView title) noexcept -> AbstractWindowBuilder& {
    _title = title;
    return *this;
  }

  auto windowed() noexcept -> AbstractWindowBuilder& {
    _display = nullptr;
    return *this;
  }

  auto fullscreen(Display const* display) noexcept -> AbstractWindowBuilder& {
    _display = display;
    return *this;
  }

  auto windowedFullscreen(Display const* display) noexcept -> AbstractWindowBuilder& {
    _display = display;
    _requestWindowedFullscreen = true;
    return *this;
  }

  virtual ~AbstractWindowBuilder() noexcept = default;

  [[nodiscard]] virtual auto build() const noexcept(false) -> Window* = 0;

protected:
  [[nodiscard]] auto rect() const noexcept -> Rect2D const& {
    return _rect;
  }

  [[nodiscard]] auto title() const noexcept -> StringView {
    return _title;
  }

  [[nodiscard]] auto display() const noexcept -> Display const* {
    return _display;
  }

  [[nodiscard]] auto windowedFullscreenRequested() const noexcept -> bool {
    return _requestWindowedFullscreen;
  }

private:
  Rect2D _rect {{defaultWindowX, defaultWindowY}, {defaultWindowWidth, defaultWindowHeight}};
  String _title {defaultWindowTitle};
  Display const* _display {nullptr};
  bool _requestWindowedFullscreen {false};
};

template <typename T> class WindowBuilderDecorator {
public:
  auto withX(SSize x) noexcept -> T& {
    return static_cast<T&>(static_cast<T*>(this)->AbstractWindowBuilder::withX(x));
  }

  auto withY(SSize y) noexcept -> T& {
    return static_cast<T&>(static_cast<T*>(this)->AbstractWindowBuilder::withY(y));
  }

  auto withPosition(Point2D pos) noexcept -> T& {
    return static_cast<T&>(static_cast<T*>(this)->AbstractWindowBuilder::withPosition(pos));
  }

  auto withPosition(SSize x, SSize y) noexcept -> T& {
    return static_cast<T&>(static_cast<T*>(this)->AbstractWindowBuilder::withPosition(x, y));
  }

  auto withWidth(Size width) noexcept -> T& {
    return static_cast<T&>(static_cast<T*>(this)->AbstractWindowBuilder::withWidth(width));
  }

  auto withHeight(Size height) noexcept -> T& {
    return static_cast<T&>(static_cast<T*>(this)->AbstractWindowBuilder::withHeight(height));
  }

  auto withSize(Area2D area) noexcept -> T& {
    return static_cast<T&>(static_cast<T*>(this)->AbstractWindowBuilder::withSize(area));
  }

  auto withSize(Size width, Size height) noexcept -> T& {
    return static_cast<T&>(static_cast<T*>(this)->AbstractWindowBuilder::withSize(width, height));
  }

  auto withRect(Rect2D rect) noexcept -> T& {
    return static_cast<T&>(static_cast<T*>(this)->AbstractWindowBuilder::withRect(rect));
  }

  auto withRect(Point2D pos, Area2D area) noexcept -> T& {
    return static_cast<T&>(static_cast<T*>(this)->AbstractWindowBuilder::withRect(pos, area));
  }

  auto withRect(SSize x, SSize y, Size width, Size height) noexcept -> T& {
    return static_cast<T&>(static_cast<T*>(this)->AbstractWindowBuilder::withRect(x, y, width, height));
  }

  auto withTitle(StringView title) noexcept -> T& {
    return static_cast<T&>(static_cast<T*>(this)->AbstractWindowBuilder::withTitle(title));
  }

  auto windowed() noexcept -> T& {
    return static_cast<T&>(static_cast<T*>(this)->AbstractWindowBuilder::windowed());
  }

  auto fullscreen(Display const* display) noexcept -> T& {
    return static_cast<T&>(static_cast<T*>(this)->AbstractWindowBuilder::fullscreen(display));
  }

  auto windowedFullscreen(Display const* display) noexcept -> T& {
    return static_cast<T&>(static_cast<T*>(this)->AbstractWindowBuilder::windowedFullscreen(display));
  }
};

class WindowManagerApiComponent : public PersistenceApiComponent {
public:
  ~WindowManagerApiComponent() noexcept override = default;

  [[nodiscard]] virtual auto abstractWindowBuilder() noexcept -> UniquePtr<AbstractWindowBuilder> = 0;
  virtual auto close(Window*) noexcept -> void = 0;
};
} // namespace c_eng::generic::detail

namespace c_eng::generic {
using detail::AbstractWindowBuilder;
using detail::IncompatibleDisplayException;
using detail::Window;
using detail::WindowBuilderDecorator;
using detail::WindowManagerApiComponent;
} // namespace c_eng::generic

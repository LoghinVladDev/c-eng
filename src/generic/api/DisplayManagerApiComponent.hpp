//
// Created by loghin on 10/27/24.
//

#pragma once

#include <cds/collection/Vector>

#include "ApiComponent.hpp"
#include <generic/Types.hpp>

namespace c_eng::generic::detail {
using cds::Vector;

class AbstractWindowBuilder;
class Window;

class Display {
public:
  virtual ~Display() noexcept = default;
  [[nodiscard]] virtual auto connected() const noexcept -> bool = 0;
  [[nodiscard]] virtual auto videoModes() const noexcept -> Vector<DisplayVideoMode> = 0;
  [[nodiscard]] virtual auto currentVideoMode() const noexcept -> DisplayVideoMode = 0;
  [[nodiscard]] virtual auto contentScale() const noexcept -> Scale2DF = 0;
  [[nodiscard]] virtual auto position() const noexcept -> Point2D = 0;
  [[nodiscard]] virtual auto availableAreaRect() const noexcept -> Rect2D = 0;

  virtual auto setGammaScale(float) noexcept -> void = 0;
};

class DisplayManagerApiComponent : public ApiComponent {
public:
  ~DisplayManagerApiComponent() noexcept override = default;

  [[nodiscard]] virtual auto primaryDisplay() const noexcept -> Display const* = 0;
  [[nodiscard]] virtual auto displays() const noexcept -> Vector<Display const*> = 0;
};
} // namespace c_eng::generic::detail

namespace c_eng::generic {
using detail::Display;
using detail::DisplayManagerApiComponent;
} // namespace c_eng::generic

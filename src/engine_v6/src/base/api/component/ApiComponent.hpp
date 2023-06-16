//
// Created by Vlad-Andrei Loghin on 14.06.23.
//

#ifndef C_ENG_APICOMPONENT_H
#define C_ENG_APICOMPONENT_H

#include "src/engine_v6/src/base/core/Object.hpp"

namespace engine {
class Api;

class ApiComponent : public Object {
public:
  enum class Type {
    Audio,
    Controller,
    Keyboard,
    Mouse,
    Present,
    Render,
    System,
  };

  [[nodiscard]] auto api() const noexcept -> Api const*;
  [[nodiscard]] auto api() noexcept -> Api*;

  [[nodiscard]] virtual auto type() const noexcept -> Type = 0;

protected:
  explicit ApiComponent(Api* parentApi) noexcept;
};
} // namespace engine

#endif //C_ENG_APICOMPONENT_H

//
// Created by Vlad-Andrei Loghin on 14.06.23.
//

#ifndef C_ENG_SYSTEMAPICOMPONENT_HPP
#define C_ENG_SYSTEMAPICOMPONENT_HPP

#include "ApiComponent.hpp"

namespace engine {
class SystemApiComponent : public ApiComponent {
public:
  [[nodiscard]] auto type() const noexcept -> Type override {
    return ApiComponent::Type::System;
  }

  auto requestShutdown() noexcept -> void;

protected:
  using ApiComponent::ApiComponent;
};
} // namespace engine

#endif //C_ENG_SYSTEMAPICOMPONENT_HPP

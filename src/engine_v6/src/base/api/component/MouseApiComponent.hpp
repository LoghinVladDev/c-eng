//
// Created by Vlad-Andrei Loghin on 14.06.23.
//

#ifndef C_ENG_MOUSEAPICOMPONENT_HPP
#define C_ENG_MOUSEAPICOMPONENT_HPP

#include "ApiComponent.hpp"

namespace engine {
class MouseApiComponent : public ApiComponent {
public:
  [[nodiscard]] auto type() const noexcept -> Type override {
    return ApiComponent::Type::Mouse;
  }

protected:
  using ApiComponent::ApiComponent;
};
} // namespace engine

#endif //C_ENG_MOUSEAPICOMPONENT_HPP

//
// Created by Vlad-Andrei Loghin on 14.06.23.
//

#ifndef C_ENG_KEYBOARDAPICOMPONENT_HPP
#define C_ENG_KEYBOARDAPICOMPONENT_HPP

#include "ApiComponent.hpp"

namespace engine {
class KeyboardApiComponent : public ApiComponent {
public:
  [[nodiscard]] auto type() const noexcept -> Type override {
    return ApiComponent::Type::Keyboard;
  }

protected:
  using ApiComponent::ApiComponent;
};
} // namespace engine

#endif //C_ENG_KEYBOARDAPICOMPONENT_HPP

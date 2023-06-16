//
// Created by Vlad-Andrei Loghin on 14.06.23.
//

#ifndef C_ENG_PRESENTAPICOMPONENT_HPP
#define C_ENG_PRESENTAPICOMPONENT_HPP

#include "ApiComponent.hpp"

namespace engine {
class PresentApiComponent : public ApiComponent {
public:
  [[nodiscard]] auto type() const noexcept -> Type override {
    return ApiComponent::Type::Present;
  }

protected:
  using ApiComponent::ApiComponent;
};
} // namespace engine

#endif //C_ENG_PRESENTAPICOMPONENT_HPP

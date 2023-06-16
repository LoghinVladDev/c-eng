//
// Created by Vlad-Andrei Loghin on 14.06.23.
//

#ifndef C_ENG_RENDERAPICOMPONENT_HPP
#define C_ENG_RENDERAPICOMPONENT_HPP

#include "ApiComponent.hpp"

namespace engine {
class RenderApiComponent : public ApiComponent {
public:
  [[nodiscard]] auto type() const noexcept -> Type override {
    return ApiComponent::Type::Render;
  }

protected:
  using ApiComponent::ApiComponent;
};
} // namespace engine

#endif //C_ENG_RENDERAPICOMPONENT_HPP

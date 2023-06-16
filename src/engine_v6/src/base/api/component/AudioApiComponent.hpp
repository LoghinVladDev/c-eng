//
// Created by Vlad-Andrei Loghin on 14.06.23.
//

#ifndef C_ENG_AUDIOAPICOMPONENT_HPP
#define C_ENG_AUDIOAPICOMPONENT_HPP

#include "ApiComponent.hpp"

namespace engine {
class AudioApiComponent : public ApiComponent {
public:
  [[nodiscard]] auto type() const noexcept -> Type override {
    return ApiComponent::Type::Audio;
  }

protected:
  using ApiComponent::ApiComponent;
};
} // namespace engine

#endif //C_ENG_AUDIOAPICOMPONENT_HPP

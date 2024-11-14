//
// Created by loghin on 10/27/24.
//

#pragma once

#include "ApiComponent.hpp"

namespace c_eng::generic::detail {
class AudioApiComponent : public ApiComponent {
public:
  ~AudioApiComponent() noexcept override = default;
};
} // namespace c_eng::generic::detail

namespace c_eng::generic {
using detail::AudioApiComponent;
} // namespace c_eng::generic

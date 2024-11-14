//
// Created by loghin on 10/27/24.
//

#pragma once

#include "ApiComponent.hpp"

namespace c_eng::generic::detail {
class KeyboardApiComponent : public ApiComponent {
public:
  ~KeyboardApiComponent() noexcept override = default;
};
} // namespace c_eng::generic::detail

namespace c_eng::generic {
using detail::KeyboardApiComponent;
} // namespace c_eng::generic

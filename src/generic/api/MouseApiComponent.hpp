//
// Created by loghin on 10/27/24.
//

#pragma once

#include "ApiComponent.hpp"

namespace c_eng::generic::detail {
class MouseApiComponent : public ApiComponent {
public:
  ~MouseApiComponent() noexcept override = default;
};
} // namespace c_eng::generic::detail

namespace c_eng::generic {
using detail::MouseApiComponent;
} // namespace c_eng::generic

//
// Created by loghin on 10/27/24.
//

#pragma once

#include "ApiComponent.hpp"

namespace c_eng::generic::detail {
class ControllerApiComponent : public ApiComponent {
public:
  ~ControllerApiComponent() noexcept override = default;
};
} // namespace c_eng::generic::detail

namespace c_eng::generic {
using detail::ControllerApiComponent;
} // namespace c_eng::generic

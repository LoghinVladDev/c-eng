//
// Created by loghin on 10/27/24.
//

#pragma once

#include "ApiComponent.hpp"

namespace c_eng::generic::detail {
class SystemApiComponent : public ApiComponent {
public:
  ~SystemApiComponent() noexcept override = default;
};
} // namespace c_eng::generic::detail

namespace c_eng::generic {
using detail::SystemApiComponent;
} // namespace c_eng::generic

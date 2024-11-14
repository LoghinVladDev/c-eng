//
// Created by loghin on 10/27/24.
//

#pragma once

#include "ApiComponent.hpp"

namespace c_eng::generic::detail {
class RenderApiComponent : public ApiComponent {
public:
  ~RenderApiComponent() noexcept override = default;
};
} // namespace c_eng::generic::detail

namespace c_eng::generic {
using detail::RenderApiComponent;
} // namespace c_eng::generic

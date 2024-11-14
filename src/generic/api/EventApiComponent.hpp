//
// Created by loghin on 11/9/24.
//

#pragma once

#include "ApiComponent.hpp"

namespace c_eng::generic::detail {
class EventPollingApiComponent : public ApiComponent {
public:
  ~EventPollingApiComponent() noexcept override = default;

  virtual auto poll() noexcept -> void = 0;
};
} // namespace c_eng::genric::detail

namespace c_eng::generic {
using detail::EventPollingApiComponent;
}

//
// Created by loghin on 11/9/24.
//

#pragma once

#include <generic/api/EventApiComponent.hpp>

namespace c_eng::api::detail {
using generic::EventPollingApiComponent;

class GlfwEventPollingManager : public EventPollingApiComponent {
public:
  ~GlfwEventPollingManager() noexcept override = default;

  auto poll() noexcept -> void override;
};
} // namespace c_eng::api::detail

namespace c_eng::api {
using detail::GlfwEventPollingManager;
} // namespace c_eng::api

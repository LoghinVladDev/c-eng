//
// Created by loghin on 11/2/24.
//

#pragma once

#include "generic/api/DisplayManagerApiComponent.hpp"
#include "generic/log/Logger.hpp"

namespace c_eng::api::detail {
class GlfwInstance;

using cds::Vector;
using cds::ignore;

using generic::DisplayManagerApiComponent;
using generic::LoggerRef;

using generic::Display;

class GlfwDisplayManager : public DisplayManagerApiComponent {
public:
  explicit GlfwDisplayManager(GlfwInstance const* instance, LoggerRef logger) noexcept;
  ~GlfwDisplayManager() noexcept override = default;

  [[nodiscard]] auto primaryDisplay() const noexcept -> Display const* override;
  [[nodiscard]] auto displays() const noexcept -> Vector<Display const*> override;

private:
  LoggerRef _logger;
  GlfwInstance const* _instance;
};
} // namespace c_eng::api::detail

namespace c_eng::api {
using detail::GlfwDisplayManager;
} // namespace c_eng::api

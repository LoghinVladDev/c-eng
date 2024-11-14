//
// Created by loghin on 11/1/24.
//

#pragma once

#include <cds/String>
#include <cds/exception/RuntimeException>

namespace c_eng::api::detail {
using cds::RuntimeException;
using cds::String;

using cds::impl::mv;

class GlfwException : public RuntimeException {
public:
  explicit GlfwException(String message) : RuntimeException{"GlfwException: " + mv(message)} {}
  ~GlfwException() noexcept override = default;
};
} // namespace c_eng::api::detail

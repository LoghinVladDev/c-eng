//
// Created by loghin on 10/27/24.
//

#pragma once

namespace c_eng::generic::detail {
class ApiComponent {
public:
  virtual ~ApiComponent() noexcept = default;
};
} // namespace c_eng::generic::detail

namespace c_eng::generic {
using detail::ApiComponent;
} // namespace c_eng::generic

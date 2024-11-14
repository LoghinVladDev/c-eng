//
// Created by loghin on 10/27/24.
//

#pragma once

#include <cds/Optional>
#include <cds/collection/Vector>

#include "generic/Types.hpp"
#include "ApiComponent.hpp"

namespace c_eng::generic::detail {
using cds::Vector;
using cds::Optional;

using cds::impl::mv;

class Api {
protected:
  explicit Api(Vector<ApiComponent*>&& components) : _components{mv(components)} {}
  constexpr Api(Api&& api) : _components{mv(api._components)} {}

public:
  Api() noexcept = delete;
  Api(Api const&) = delete;
  virtual ~Api() noexcept = default;
  [[nodiscard]] virtual auto info() const noexcept -> ApiInfo = 0;
  [[nodiscard]] virtual auto compiledVersion() const noexcept -> Optional<Version> = 0;
  [[nodiscard]] virtual auto runtimeVersion() const noexcept -> Optional<Version> = 0;

  [[nodiscard]] auto components() const noexcept -> Vector<ApiComponent*> const& {
    return _components;
  }

private:
  Vector<ApiComponent*> _components;
};
} // namespace c_eng::generic::detail

namespace c_eng::generic {
using detail::Api;
} // namespace c_eng::generic

//
// Created by loghin on 11/13/24.
//

#pragma once

#include <cds/functional/Invoke>

#include "Concepts.hpp"

namespace c_eng::generic::detail {
namespace fn = cds::functional;

using cds::impl::fwd;

template <typename Target> struct DynCast {
  template <concepts::BaseOf<Target> Base> [[nodiscard]] inline auto operator()(Base* obj) const noexcept -> Target* {
    return dynamic_cast<Target*>(obj);
  }

  template <concepts::BaseOf<Target> Base> [[nodiscard]] inline auto operator()(Base const* obj) const noexcept
      -> Target const* {
    return dynamic_cast<Target const*>(obj);
  }
};

struct NonNull {
  template <typename Obj> [[nodiscard]] inline auto operator()(Obj const* obj) const noexcept -> bool {
    return obj != nullptr;
  }
};

template <typename Target> constexpr DynCast<Target> dynCast;
constexpr NonNull notNull;
} // namespace c_eng::generic::detail

namespace c_eng::generic {
using detail::dynCast;
using detail::notNull;
} // namespace c_eng::generic

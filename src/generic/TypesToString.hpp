//
// Created by loghin on 10/27/24.
//

#pragma once

#include "Types.hpp"
#include <sstream>
#include <cds/Format>
#include <cds/meta/Compiler>

namespace c_eng::generic::detail {
using std::stringstream;
using std::hex;

using cds::U64;
using cds::bitCast;

using namespace cds::literals;
using cds::meta::False;
using cds::meta::RemoveCVRef;
using cds::meta::True;
using cds::impl::copy;
using cds::impl::fwd;
using cds::impl::unreachable;

template <typename = void> struct ToString : False {};

template <> struct ToString<void> {
  template <typename T> auto operator()(T&& data) const noexcept {
    return ToString<RemoveCVRef<T>>{}(fwd<T>(data));
  }
};
} // namespace c_eng::generic::detail

template <typename T, typename C> requires c_eng::generic::detail::ToString<T>::value
struct cds::Formatter<T, C> {
  template <typename Ctx> auto format(T const& obj, Ctx& ctx) const noexcept -> typename Ctx::Iterator {
    auto&& asStr = c_eng::generic::detail::ToString<>{}(obj);
    auto&& asSv = impl::BaseStringView<C>{asStr};
    return copy(asSv.begin(), asSv.end(), ctx.out());
  }
};

namespace c_eng::generic::detail {
template <> struct ToString<LicenceType> : True {
  auto operator()(LicenceType type) const noexcept {
    switch (type) {
      case LicenceType::Proprietary:
        return "Proprietary";
      case LicenceType::Zlib:
        return "Zlib";
      default:
        assert(false && "Unhandled ToString<LicenceType> case");
        unreachable();
    }
  }
};

template <> struct ToString<Version> : True {
  auto operator()(Version const& version) const noexcept {
    auto const [variant, major, minor, patch] = version;
    return cds::format("Version{{variant={}, major={}, minor={}, patch={}}}", variant, major, minor, patch);
  }
};

template <> struct ToString<ApiInfo> : True {
  auto operator()(ApiInfo const& info) const noexcept {
    auto const& [name, desc, vendor, vendorId, licence] = info;
    return cds::format(
        R"(ApiInfo{{name="{}", description="{}", vendor="{}", vendorId={}, licenceType={}}})",
        name, desc, vendor, vendorId, licence
    );
  }
};

template <> struct ToString<Point2D> : True {
  auto operator()(Point2D const& point) const noexcept {
    auto const [x, y] = point;
    return cds::format("Point2D{{x={}, y={}}}", x, y);
  }
};

template <> struct ToString<Area2D> : True {
  auto operator()(Area2D const& area) const noexcept {
    auto const [width, height] = area;
    return cds::format("Area2D{{width={}, height={}}}", width, height);
  }
};

template <> struct ToString<Rect2D> : True {
  auto operator()(Rect2D const& rect) const noexcept {
    auto const& [pos, area] = rect;
    return cds::format("Rect2D{{position={}, area={}}}", pos, area);
  }
};

template <> struct ToString<ColorChannelsDepth> : True {
  auto operator()(ColorChannelsDepth const& depth) const noexcept {
    auto const [red, green, blue] = depth;
    return cds::format("ColorChannelsDepth{{red={}, green={}, blue={}}}", red, green, blue);
  }
};

template <> struct ToString<DisplayVideoMode> : True {
  auto operator()(DisplayVideoMode const& mode) const noexcept {
    auto const& [area, depth, refRate] = mode;
    return cds::format("DisplayVideoMode{{area={}, depth={}, refreshRate={}}}", area, depth, refRate);
  }
};

template <> struct ToString<Scale2DF> : True {
  auto operator()(Scale2DF const& scale) const noexcept {
    auto const& [x, y] = scale;
    return cds::format("Scale2DF{{x={}, y={}}}", x, y);
  }
};

template <typename T> auto toString(T const& obj) noexcept {
  return ToString<T>{}(obj);
}
}; // namespace c_eng::generic::detail

namespace c_eng::generic {
using detail::toString;
} // namespace c_eng::generic

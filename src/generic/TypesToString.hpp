//
// Created by loghin on 10/27/24.
//

#pragma once

#include "Types.hpp"
#include <sstream>
#include <cds/experimental/Format>
#include <cds/meta/Compiler>

namespace c_eng::generic::detail {
using std::stringstream;
using std::hex;

using cds::U64;
using cds::bitCast;

using namespace cds::experimental::literals;
using cds::meta::False;
using cds::meta::RemoveCVRef;
using cds::meta::True;
using cds::impl::fwd;
using cds::impl::unreachable;

inline auto addressAsString(void const* addr) noexcept {
  // TODO: cds/StringStream
  // OR
  // TODO: cds/experimental/Format provide formatting literals support for address formatting
  stringstream oss;
  oss << "0x" << hex << bitCast<U64>(addr);
  return oss.str();
}

template <typename = void> struct ToString : False {};

template <> struct ToString<void> {
  template <typename T> auto operator()(T&& data) const noexcept {
    return ToString<RemoveCVRef<T>>{}(fwd<T>(data));
  }
};
} // namespace c_eng::generic::detail

template <typename T> requires c_eng::generic::detail::ToString<T>::value struct cds::experimental::impl::Formatter<T> {
  template <typename S> auto operator()(S& string, T const& obj) const noexcept {
    string += c_eng::generic::detail::ToString<>{}(obj);
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
    return "Version{{variant={}, major={}, minor={}, patch={}}}"_f(variant, major, minor, patch);
  }
};

template <> struct ToString<ApiInfo> : True {
  auto operator()(ApiInfo const& info) const noexcept {
    auto const& [name, desc, vendor, vendorId, licence] = info;
    return R"(ApiInfo{{name="{}", description="{}", vendor="{}", vendorId={}, licenceType={}}})"_f
        (name, desc, vendor, vendorId, licence);
  }
};

template <> struct ToString<Point2D> : True {
  auto operator()(Point2D const& point) const noexcept {
    auto const [x, y] = point;
    return "Point2D{{x={}, y={}}}"_f(x, y);
  }
};

template <> struct ToString<Area2D> : True {
  auto operator()(Area2D const& area) const noexcept {
    auto const [width, height] = area;
    return "Area2D{{width={}, height={}}}"_f(width, height);
  }
};

template <> struct ToString<Rect2D> : True {
  auto operator()(Rect2D const& rect) const noexcept {
    auto const& [pos, area] = rect;
    return "Rect2D{{position={}, area={}}}"_f(pos, area);
  }
};

template <> struct ToString<ColorChannelsDepth> : True {
  auto operator()(ColorChannelsDepth const& depth) const noexcept {
    auto const [red, green, blue] = depth;
    return "ColorChannelsDepth{{red={}, green={}, blue={}}}"_f(red, green, blue);
  }
};

template <> struct ToString<DisplayVideoMode> : True {
  auto operator()(DisplayVideoMode const& mode) const noexcept {
    auto const& [area, depth, refRate] = mode;
    return "DisplayVideoMode{{area={}, depth={}, refreshRate={}}}"_f(area, depth, refRate);
  }
};

template <> struct ToString<Scale2DF> : True {
  auto operator()(Scale2DF const& scale) const noexcept {
    auto const& [x, y] = scale;
    return "Scale2DF{{x={}, y={}}}"_f(x, y);
  }
};

template <typename T> auto toString(T const& obj) noexcept {
  return ToString<T>{}(obj);
}
}; // namespace c_eng::generic::detail

namespace c_eng::generic {
using detail::toString;
} // namespace c_eng::generic

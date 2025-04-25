//
// Created by vloghin on 19.04.2025.
//

#pragma once

#include <source_location>
#include <cds/Format>
#include <cds/StringView>

template <typename C> struct cds::Formatter<std::source_location, C> {
  bool file {false};
  bool path {true};

  bool line {true};
  bool column {false};

  bool methodName {false};
  bool method {false};

  template <typename Ctx> constexpr auto parse(Ctx& ctx) noexcept -> typename Ctx::Iterator {
    auto it = ctx.begin();
    auto end = ctx.end();

    if (it == end || *it == '}') {
      return it;
    }

    line = false;
    path = false;

    if (it != end && *it == 'f') {
      file = true;
      ++it;
    }

    if (it != end && *it == 'F') {
      if (file) {
        throw FormatException("Cannot specify both file and path");
      }
      path = true;
      ++it;
    }

    if (it != end && *it == 'l') {
      line = true;
      ++it;
    }

    if (it != end && *it == 'c') {
      column = true;
      ++it;
    }

    if (it != end && *it == 'm') {
      methodName = true;
      ++it;
    }

    if (it != end && *it == 'M') {
      if (methodName) {
        throw FormatException("Cannot specify both method name and method");
      }
      method = true;
      ++it;
    }

    if (it != end && *it != '}') {
      throw FormatException("Extraneous format specifiers for 'std::source_location'");
    }

    return it;
  }

  template <typename Ctx> auto format(std::source_location const& loc, Ctx const& ctx) noexcept
      -> typename Ctx::Iterator {
    auto theFile = StringView{loc.file_name()};
    auto the

    if (file) {

    }

    loc.
    auto const asStr = vk::toString(result);
    return impl::copy(asStr.begin(), asStr.end(), ctx.out());
  }
};

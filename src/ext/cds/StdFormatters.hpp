//
// Created by loghin on 19.04.2025.
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

  template <typename Ctx> constexpr auto parse(Ctx& ctx) noexcept(false) -> typename Ctx::Iterator {
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

  template <typename Ctx> auto format(std::source_location const& loc, Ctx& ctx) noexcept
      -> typename Ctx::Iterator {
    auto thePath = StringView{loc.file_name()};
    auto theMethod = StringView{loc.function_name()};
    bool anythingBefore = false;
    auto out = ctx.out();

    if (file) {
      auto const theLastSlashPos = thePath.findLast('/');
      auto theFile = thePath;
      if (theLastSlashPos != StringView::npos) {
        theFile = thePath.sub(theLastSlashPos + 1);
      }

      out = impl::copy(theFile.begin(), theFile.end(), out);
      anythingBefore = true;
    }

    if (path) {
      out = impl::copy(thePath.begin(), thePath.end(), out);
      anythingBefore = true;
    }

    if (method || /* method name does not do anything yet */ methodName) {
      if (anythingBefore) {
        auto const theSep = StringView{" - "};
        out = impl::copy(theSep.begin(), theSep.end(), out);
      }

      out = impl::copy(theMethod.begin(), theMethod.end(), out);
    }

    if (line) {
      if (anythingBefore) {
        auto const theSep = StringView{":"};
        out = impl::copy(theSep.begin(), theSep.end(), out);
      }

      auto const theLine = loc.line();
      using LineType = cds::meta::RemoveCVRef<decltype(theLine)>;
      using LineFormatter = cds::Formatter<LineType, C>;
      LineFormatter lineFormatter{};
      auto newCtx = ctx.from(out);
      out = lineFormatter.format(theLine, newCtx);
    }

    if (column) {
      if (anythingBefore) {
        auto const theSep = StringView{":"};
        out = impl::copy(theSep.begin(), theSep.end(), out);
      }

      auto const theColumn = loc.column();
      using ColumnType = cds::meta::RemoveCVRef<decltype(column)>;
      using ColumnFormatter = cds::Formatter<ColumnType, C>;
      ColumnFormatter columnFormatter{};
      auto newCtx = ctx.from(out);
      out = columnFormatter.format(theColumn, newCtx);
    }

    return out;
  }
};

//
// Created by loghin on 10/17/24.
//

#pragma once

#include <ostream>

#include <cds/String>
#include <cds/Union>

#include <cds/collection/Vector>

namespace c_eng::generic::detail {
using std::ostream;

using cds::InPlaceIndex;
using cds::Optional;
using cds::String;
using cds::Union;
using cds::Vector;

using cds::impl::fwd;
using cds::impl::mv;

using cds::ignore;
using cds::nullopt;
using cds::meta::InvokeReturnOf;

namespace fn = cds::functional;

class Logger;

enum class LogLevel {
  Critical, Error, Warning, Info, Debug,
};

class LoggerOutput {
public:
  explicit LoggerOutput(ostream& out) : _out{out} {}

  [[nodiscard]] auto& stream() const noexcept {
    return _out;
  }

private:
  ostream& _out;
};

class LogPrinter {
public:
  explicit LogPrinter(Logger const& logger) noexcept : _logger{logger} {}
  ~LogPrinter() noexcept;

  template <typename T> auto add(T&& data) noexcept -> void {
    _buffer += fwd<T>(data);
  }

  template <typename T> auto add(Optional<T>&& opt) noexcept -> void {
    _buffer += mv(*opt);
  }

private:
  Logger const& _logger;
  String _buffer;
};

class InactiveLogPrinter {
public:
  template <typename T> auto add(T&& data) noexcept -> void {
    ignore = fwd<T>(data);
  }
};

class Log {
public:
  Log() noexcept = default;
  explicit Log(Logger const& logger, LogLevel const level) noexcept : _printer{InPlaceIndex<0>{}, logger}, _level{level} {}

  template <typename T> auto operator<<(T&& data) noexcept -> Log& {
    // TODO: level
    _printer.visit([&data]<typename P>(P&& printer) {
      fwd<P>(printer).add(fwd<T>(data));
    });
    return *this;
  }

private:
  Union<LogPrinter, InactiveLogPrinter> _printer {InPlaceIndex<1>{}, InactiveLogPrinter{}};
  LogLevel _level {LogLevel::Info};
};

class Logger {
public:
  using Level = LogLevel;

  Logger() noexcept = delete;
  inline explicit Logger(Vector<LoggerOutput> outputs) noexcept : _outputs{mv(outputs)} {}

  [[nodiscard]] inline auto enabled() const noexcept {
    return _enabled;
  }

  inline auto setEnabled(bool toggle) noexcept {
    _enabled = toggle;
  }

  [[nodiscard]] inline auto const& outputs() const noexcept {
    return _outputs;
  }

  inline auto operator()(Level const level = Level::Info) const noexcept -> Log {
    if (enabled()) {
      return Log{*this, level};
    } else {
      return Log{};
    }
  }

private:
  bool _enabled {true};
  Vector<LoggerOutput> _outputs;
  String _name;
};

class LoggerRef {
public:
  using Level = LogLevel;

  LoggerRef() = default;
  LoggerRef(LoggerRef const&) = default;
  LoggerRef(LoggerRef&&) = default;
  explicit(false) inline LoggerRef(Logger& logger) : _logger{&logger} {}

  auto operator=(LoggerRef const& logger) noexcept -> LoggerRef& = default;
  auto operator=(LoggerRef&& logger) noexcept -> LoggerRef& = default;

  auto operator<=>(LoggerRef const&) const noexcept = default;

  [[nodiscard]] auto get() const noexcept -> Logger* {
    return _logger;
  }

  inline auto operator()(Level const level = Level::Info) const noexcept -> Log {
    if (_logger) {
      return (*_logger)(level);
    }
    return Log{};
  }

  template <typename Fn, typename... Args> inline auto invoke(Fn&& fn, Args&&... args)
      const noexcept(noexcept(fn::invoke(fwd<Fn>(fn), fwd<Args>(args)...))) -> Optional<InvokeReturnOf<Fn, Args...>> {
    if (_logger) {
      return {fn::invoke(fwd<Fn>(fn), fwd<Args>(args)...)};
    }
    return nullopt;
  }

private:
  Logger* _logger {nullptr};
};

inline LogPrinter::~LogPrinter() noexcept {
  _logger.outputs().forEach([this](auto const& out) {
    out.stream() << _buffer << '\n';
  });
}
} // namespace c_eng::generic::detail

namespace c_eng::generic {
using detail::LogLevel;
using detail::Logger;
using detail::LoggerOutput;
using detail::LoggerRef;
} // namespace c_eng::generic

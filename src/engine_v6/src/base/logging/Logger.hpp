#pragma once

#include <CDS/meta/TypeTraits>
#include <CDS/Object>
#include <core/Config.hpp>
#include <core/Object.hpp>
#include <source_location>
#include <ostream>
#include <format>
#include <CDS/Array>
#include <lang/FlagEnum.hpp>

namespace engine {
namespace meta {
class LoggerBaseCommon {
public:
  enum class Option {
    None = 0x00000000,
    Start = 0x00000001,

    Error = 0x00000002,
    Warning = 0x00000004,
    Debug = 0x00000008,
    Info = 0x00000010
  };

  using OptionFlags = std::underlying_type_t<Option>;
};

template<>
struct FlagEnum<LoggerBaseCommon::Option> : cds::meta::TrueType {
  using FlagsType = LoggerBaseCommon::OptionFlags;
};
}

class LoggerOutput : private meta::LoggerBaseCommon {
public:
  static constexpr auto const allowInfo    = meta::LoggerBaseCommon::Option::Info;
  static constexpr auto const allowWarning = meta::LoggerBaseCommon::Option::Warning;
  static constexpr auto const allowDebug   = meta::LoggerBaseCommon::Option::Debug;
  static constexpr auto const allowError   = meta::LoggerBaseCommon::Option::Error;
  static constexpr auto const allowAll     = allowInfo | allowWarning | allowDebug | allowError;

  explicit(false) LoggerOutput(std::ostream& output, OptionFlags filterFlags = allowAll) noexcept :
      pOutput(&output),
      filter(filterFlags & mask) {}

  explicit(false) LoggerOutput(std::ostream& output, Option filterLevel) noexcept :
      pOutput(&output),
      filter(static_cast<OptionFlags>(filterLevel) & mask) {}

  constexpr auto output() noexcept -> std::ostream& {
    return *pOutput;
  }

  constexpr auto allows(OptionFlags option) const noexcept -> bool {
    return (filter & option & mask) != 0u;
  }

private:
  std::ostream* pOutput;
  OptionFlags filter;
  static constexpr auto const mask = allowAll;
};

namespace meta {
template <bool = config::value <config::ParameterType::LoggingEnabled>>
class LoggerBase : public LoggerBaseCommon {
public:
  template <typename T>
  auto operator << (T && logged) noexcept -> LoggerBase & {
    (void) logged;
    return * this;
  }

protected:
  LoggerBase (cds::String const& name, LoggerOutput out) noexcept {
    (void) out;
    (void) name;
  }

  constexpr auto startLogItem () noexcept -> void {
    //empty on purpose. Logging deactivated
  }

  constexpr auto outputs() noexcept -> auto& {
    return _emptyOutputs;
  }

  constexpr auto outputs() const noexcept -> auto const& {
    return _emptyOutputs;
  }

  [[nodiscard]] constexpr auto name() const noexcept -> cds::StringView {
    return "";
  }

  using Level = Option;
  constexpr auto setDefaultLevel(Level level) noexcept -> void {
    (void) level;
  }

private:
  cds::Array <LoggerOutput> _emptyOutputs;
};

template <>
class LoggerBase <true> : public LoggerBaseCommon {
public:
  template <typename T>
  auto operator << (T && logged) noexcept -> LoggerBase & {

    auto started = isSet (Option::Start);
    set (ifOptionThen (std::forward <T> (logged)));
    if (! started && isSet (Option::Start)) {
        addHeader();
    }

    for (auto output : _outputs) {
      if (output.allows(flags)) {
        (output.output()) << ifOptionProcess(std::forward<T>(logged));
      }
    }
    return * this;
  }

protected:
  template <typename Range>
  LoggerBase (cds::String name, Range&& outputRange) noexcept :
      _outputs (std::forward<Range>(outputRange)),
      loggerName(std::move(name)) {}

  template <typename RangeIt>
  LoggerBase (cds::String name, RangeIt&& begin, RangeIt&& end) noexcept :
      _outputs(std::forward<RangeIt>(begin), std::forward<RangeIt>(end)),
      loggerName(std::move(name)) {}

  LoggerBase (cds::String name, LoggerOutput output) noexcept :
      _outputs(1, output),
      loggerName(std::move(name)) {}

  [[nodiscard]] constexpr auto name() const noexcept -> cds::StringView {
    return this->loggerName;
  }

  constexpr auto startLogItem () noexcept -> void {
    if (isSet (Option::Start)) {
      for (auto& output : _outputs) {
        output.output() << "\033[1;0m" << std::dec << std::endl;
      }
      clearFlags();
    }

    flags &= ~levelMask;
    set(defaultLevel);
  }

  constexpr auto outputs() noexcept-> auto& {
    return _outputs;
  }

  [[nodiscard]] constexpr auto outputs() const noexcept-> auto const& {
    return _outputs;
  }

  using Level = Option;
  constexpr auto setDefaultLevel(Level level) noexcept -> void {
    if ((level & levelMask) != 0u) {
      defaultLevel = level;
      flags = static_cast<OptionFlags>(defaultLevel);
    }
  }

private:
  cds::Array<LoggerOutput> _outputs;
  cds::String loggerName;
  Option defaultLevel = Option::Info;
  OptionFlags flags = static_cast<OptionFlags>(defaultLevel);

  constexpr static auto const levelMask =
      Option::Debug   |
      Option::Warning |
      Option::Error   |
      Option::Info;

  auto addHeader () noexcept -> void;
  [[nodiscard]] constexpr auto levelAsStr () const noexcept -> cds::StringLiteral {

    switch (static_cast <Option> (this->flags & levelMask)) {
      using enum Option;
      case Debug:     return "Debug";
      case Error:     return "Error";
      case Warning:   return "Warning";
      case Info:      return "Info";
      default:        return "Invalid";
    }
  }

  [[nodiscard]] constexpr auto isSet (Option option) const noexcept -> bool {
    return (flags & option) != 0U;
  }

  constexpr auto set (Option option) noexcept -> void {
    if ((levelMask & option) != 0U) {
      flags &= ~ levelMask;
    }

    flags |= option;
  }

  constexpr auto clearFlags () noexcept -> void { flags = static_cast<OptionFlags>(defaultLevel); }

  template <typename T>
  constexpr static auto ifOptionThen (T && obj) noexcept -> Option {
    (void) obj;
    return Option::Start;
  }

  constexpr static auto ifOptionThen (Option option) noexcept -> Option {
    return option;
  }

  constexpr static auto ifOptionThen (decltype(std::hex) unused) noexcept -> Option {
    (void) unused;
    return Option::None;
  }

  template <typename T>
  constexpr static auto ifOptionProcess (T && obj) noexcept -> T {
    return std::forward <T> (obj);
  }

  constexpr static auto ifOptionProcess (Option option) noexcept -> cds::StringLiteral {
    (void) option;
    return "";
  }

  inline static auto ifOptionProcess (std::source_location sourceLocation) noexcept -> std::string {
    return std::string(sourceLocation.file_name()) + ":" +
        std::to_string(sourceLocation.line()) + ":" +
        std::to_string(sourceLocation.column());
  }
};

class Logger : public meta::LoggerBase <> {
public:
  using Base = meta::LoggerBase <>;
  using Base::LoggerBase;

  using meta::LoggerBase <>::Option::Error;
  using meta::LoggerBase <>::Option::Warning;
  using meta::LoggerBase <>::Option::Debug;
  using meta::LoggerBase <>::Option::Info;

  using meta::LoggerBase <>::name;
  using meta::LoggerBase <>::outputs;

  constexpr auto endl () noexcept -> Logger & {
    Base::startLogItem();
    return * this;
  }
};
} // namespace meta

class Logger : protected meta::Logger {
public:
  using meta::Logger::Info;
  using meta::Logger::Warning;
  using meta::Logger::Debug;
  using meta::Logger::Error;
  using meta::Logger::name;
  using meta::Logger::outputs;
  using meta::Logger::setDefaultLevel;

  constexpr auto operator () () noexcept -> meta::Logger& {
    return this->endl();
  }

  constexpr static auto here (std::source_location const & location = std::source_location::current())
      noexcept -> std::source_location {
    return location;
  }

  template <typename...Outputs> requires (
      sizeof...(Outputs) > 1 &&
      cds::meta::All <cds::meta::Bind <cds::meta::IsConvertible, cds::meta::Ph<1>, LoggerOutput>::Type, Outputs...>::value
  ) static auto getLogger (cds::StringView name, Outputs&&... outputs) noexcept -> Logger& {
    auto& logger = getLogger(name);
    auto& loggerOutputs = logger.outputs();
    loggerOutputs.clear();
    loggerOutputs.insertAll(std::forward<Outputs>(outputs)...);
    return logger;
  }

  template <typename...Outputs> requires (
      sizeof...(Outputs) > 1 &&
      cds::meta::All <cds::meta::Bind <cds::meta::IsConvertible, cds::meta::Ph<1>, LoggerOutput>::Type, Outputs...>::value
  ) static auto getLogger (Outputs&&... outputs) noexcept -> Logger {
    auto logger = getLogger();
    auto& loggerOutputs = logger.outputs();
    loggerOutputs.clear();
    loggerOutputs.insertAll(std::forward<Outputs>(outputs)...);
    return logger;
  }

  static auto getLogger (cds::StringView name, LoggerOutput out) noexcept -> Logger&;
  static auto getLogger (cds::StringView name) noexcept -> Logger&;
  static auto getLogger (LoggerOutput out) noexcept -> Logger;
  static auto getLogger () noexcept -> Logger;

  static auto setDefaultLoggerOutput (std::ostream& out) noexcept -> void;

private:
  using meta::Logger::Logger;
};
} // namespace engine
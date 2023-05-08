#pragma once

#include <CDS/meta/TypeTraits>
#include <CDS/Object>
#include <core/Config.hpp>
#include <core/Object.hpp>
#include <source_location>
#include <ostream>
#include <format>

namespace engine {
namespace meta {
class LoggerBaseCommon {
public:
  enum class Option {
      None    = 0x00000000,
      Start   = 0x00000001,

      Error   = 0x00000002,
      Warning = 0x00000004,
      Debug   = 0x00000008,
      Info    = 0x00000010
  };
};

template <bool = config::value <config::ParameterType::LoggingEnabled>>
class LoggerBase : public LoggerBaseCommon {
public:
  template <typename T>
  auto operator << (T && logged) noexcept -> LoggerBase & {
    (void) logged;
    return * this;
  }

protected:
  LoggerBase (cds::String const& name, std::ostream & out) noexcept {
    (void) out;
    (void) name;
  }

  constexpr auto startLogItem () noexcept -> void {
    //empty on purpose. Logging deactivated
  }

  constexpr auto setOutput(std::ostream& out) noexcept -> void {
    (void) out;
  }

  [[nodiscard]] constexpr auto name() const noexcept -> cds::StringView {
    return "";
  }
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

    (*pBaseOut) << ifOptionProcess(std::forward <T> (logged));
    return * this;
  }

protected:
  LoggerBase (cds::String name, std::ostream & out) noexcept :
      pBaseOut (&out),
      loggerName(std::move(name)) {}

  [[nodiscard]] constexpr auto name() const noexcept -> cds::StringView {
    return this->loggerName;
  }

  constexpr auto startLogItem () noexcept -> void {
    if (isSet (Option::Start)) {
        (*pBaseOut) << "\033[1;0m" << std::dec << std::endl;
        clearFlags();
    }

    flags &= ~levelMask;
    set(Option::Info);
  }

  constexpr auto setOutput(std::ostream& out) noexcept -> void {
    pBaseOut = &out;
  }

private:
  std::ostream * pBaseOut;
  cds::String loggerName;
  cds::uint32 flags = defaultFlags;

  constexpr static cds::uint32 const levelMask =
      static_cast <cds::uint32> (Option::Debug)   |
      static_cast <cds::uint32> (Option::Warning) |
      static_cast <cds::uint32> (Option::Error)   |
      static_cast <cds::uint32> (Option::Info);

  constexpr static cds::uint32 const defaultFlags = static_cast <cds::uint32> (Option::Info);

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
    return (flags & static_cast <cds::uint32> (option)) != 0U;
  }

  constexpr auto set (Option option) noexcept -> void {
    if (auto const asFlag = static_cast <cds::uint32> (option); (levelMask & asFlag) != 0U) {
      flags &= ~ levelMask;
    }

    flags |= static_cast <cds::uint32> (option);
  }

  constexpr auto clearFlags () noexcept -> void { flags = defaultFlags; }

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
  using meta::LoggerBase <>::setOutput;

  constexpr auto endl () noexcept -> Logger & {
    Base::startLogItem();
    return * this;
  }
};
}

class Logger : protected meta::Logger {
public:
  using meta::Logger::Info;
  using meta::Logger::Warning;
  using meta::Logger::Debug;
  using meta::Logger::Error;
  using meta::Logger::name;
  using meta::Logger::setOutput;

  constexpr auto operator () () noexcept -> meta::Logger& {
    return this->endl();
  }

  constexpr static auto here (std::source_location const & location = std::source_location::current())
      noexcept -> std::source_location {
    return location;
  }

  static auto getLogger (cds::StringView name, std::ostream& out) noexcept -> Logger&;
  static auto getLogger (cds::StringView name) noexcept -> Logger&;
  static auto getLogger (std::ostream& out) noexcept -> Logger;
  static auto getLogger () noexcept -> Logger;

  static auto setDefaultLoggerOutput (std::ostream& out) noexcept -> void;

private:
  using meta::Logger::Logger;
};
}
//
// Created by Vlad-Andrei Loghin on 25.05.23.
//

#ifndef C_ENG_LOGGERSHARED_HPP
#define C_ENG_LOGGERSHARED_HPP

#include <sstream>
#include <source_location>
#include <tuple>

inline namespace logger_shared {
using std::stringstream;
using std::string;
using std::string_view;
using std::hex;
using std::dec;
using std::source_location;
using std::to_string;
using std::cout;
using engine::Logger;
using engine::LoggerOutput;
using engine::Logger::Info;
using engine::Logger::Warning;
using engine::Logger::Error;
using engine::Logger::Debug;
constexpr auto const npos = std::string::npos;

auto date () noexcept {
  int const timeBufferSize = 512U;
  using sys_clock = std::chrono::system_clock;

  auto timePoint = sys_clock::now();
  auto asTimeT = sys_clock::to_time_t(timePoint);
  tm timeInfo;
  localtime_r (& asTimeT, &timeInfo);

  string asString (timeBufferSize, '\0');
  asString.resize(std::strftime (asString.data(), timeBufferSize, "%d-%m-%Y", &timeInfo));
  asString.resize(asString.length());

  return asString;
}

template <typename...A>
auto getLogger(A&&...a) {return Logger::getLogger(std::forward<A>(a)...);}

inline auto contains(stringstream const& sstream, string_view sv) noexcept {
  return sstream.str().find(sv) != npos;
}

inline auto contains(std::string_view str, string_view sv) noexcept {
  return str.find(sv) != npos;
}

inline auto empty(stringstream const& sstream) noexcept {
  return sstream.str().empty();
}

auto filterIndividual() {
  using enum engine::meta::LoggerBaseCommon::Option;
  std::stringstream inf;
  std::stringstream wrn;
  std::stringstream err;
  std::stringstream dbg;
  auto logger = Logger::getLogger(
      LoggerOutput{inf, Info}, LoggerOutput{wrn, Warning},
      LoggerOutput{err, Error}, LoggerOutput{dbg, Debug}
  );

  logger() << Info << "test1";
  logger() << Warning << "test2";
  logger() << Error << "test3";
  logger() << Debug << "test4";
  return std::make_tuple(inf.str(), wrn.str(), err.str(), dbg.str());
}

auto filterMixedOut() {
  using enum engine::meta::LoggerBaseCommon::Option;
  std::stringstream infWrn;
  std::stringstream wrnErr;
  std::stringstream errDbg;
  auto logger = Logger::getLogger(
      LoggerOutput{infWrn, Info | Warning},
      LoggerOutput{wrnErr, Warning | Error},
      LoggerOutput{errDbg, Error | Debug}
  );

  logger() << Info << "test1";
  logger() << Warning << "test2";
  logger() << Error << "test3";
  logger() << Debug << "test4";
  return std::make_tuple(infWrn.str(), wrnErr.str(), errDbg.str());
}
} // namespace logger_shared

#endif //C_ENG_LOGGERSHARED_HPP

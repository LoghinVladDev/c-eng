//
// Created by loghin on 30/04/23.
//

#include "Test.hpp"
#include "logging/Logger.hpp"
#include <chrono>
#include <string>
#include <CDS/Long>
#include <CDS/threading/Thread>
#include <source_location>

namespace {
using engine::Logger;

auto date() noexcept {
  int const timeBufferSize = 512U;
  using sys_clock = std::chrono::system_clock;

  auto timePoint = sys_clock::now();
  auto asTimeT = sys_clock::to_time_t(timePoint);
  auto * timeInfo = std::localtime (& asTimeT);

  std::string asString (timeBufferSize, '\0');
  asString.resize(std::strftime (asString.data(), timeBufferSize, "%d-%m-%Y", timeInfo));

  return asString;
}
}

TEST(LoggerDisabled, basicOut) {
  std::stringstream outbuf;
  auto logger = Logger::getLogger(outbuf);

  logger() << "basic string output, followed by numeric: " << 123 << std::hex << 15 << std::dec << 24;
  ASSERT_TRUE(outbuf.str().empty());
  ASSERT_FALSE(outbuf.str().find(date()) != std::string::npos);
  ASSERT_FALSE(outbuf.str().find(("level = Info")) != std::string::npos);
  ASSERT_FALSE(outbuf.str().find(("thread = 0x" + cds::Long(
          static_cast<cds::sint64>(cds::Thread::currentThreadID())).toString(16)).cStr()) !=
          std::string::npos);
  ASSERT_FALSE(outbuf.str().find(("basic string output, followed by numeric: 123f24")) != std::string::npos);
}

TEST(LoggerDisabled, levelSwitch) {
  std::stringstream outbuf;
  auto logger = Logger::getLogger(outbuf);

  std::stringstream().swap(outbuf);
  logger() << 12345678;
  ASSERT_TRUE(outbuf.str().empty());
  ASSERT_FALSE(outbuf.str().find(("Info")) != std::string::npos);
  ASSERT_FALSE(outbuf.str().find(("12345678")) != std::string::npos);
  ASSERT_FALSE(outbuf.str().find(("Warning")) != std::string::npos);

  std::stringstream().swap(outbuf);
  logger() << engine::Logger::Warning << 12345678;
  ASSERT_TRUE(outbuf.str().empty());
  ASSERT_FALSE(outbuf.str().find(("Warning")) != std::string::npos);
  ASSERT_FALSE(outbuf.str().find(("12345678")) != std::string::npos);
  ASSERT_FALSE(outbuf.str().find(("Info")) != std::string::npos);

  std::stringstream().swap(outbuf);
  logger() << engine::Logger::Error << 12345678;
  ASSERT_TRUE(outbuf.str().empty());
  ASSERT_FALSE(outbuf.str().find(("Error")) != std::string::npos);
  ASSERT_FALSE(outbuf.str().find(("12345678")) != std::string::npos);
  ASSERT_FALSE(outbuf.str().find(("Info")) != std::string::npos);

  std::stringstream().swap(outbuf);
  logger() << engine::Logger::Debug << 12345678;
  ASSERT_TRUE(outbuf.str().empty());
  ASSERT_FALSE(outbuf.str().find(("Debug")) != std::string::npos);
  ASSERT_FALSE(outbuf.str().find(("12345678")) != std::string::npos);
  ASSERT_FALSE(outbuf.str().find(("Info")) != std::string::npos);

  std::stringstream().swap(outbuf);
  logger() << engine::Logger::Warning;
  ASSERT_TRUE(outbuf.str().empty());
  ASSERT_FALSE(outbuf.str().find(("Warning")) != std::string::npos);
  ASSERT_FALSE(outbuf.str().find(("12345678")) != std::string::npos);
  logger() << 12345678;
  ASSERT_TRUE(outbuf.str().empty());
  ASSERT_FALSE(outbuf.str().find(("Warning")) != std::string::npos);
  ASSERT_FALSE(outbuf.str().find(("Info")) != std::string::npos);
  ASSERT_FALSE(outbuf.str().find(("12345678")) != std::string::npos);

  std::stringstream().swap(outbuf);
  logger() << engine::Logger::Warning << "23456789";
  ASSERT_TRUE(outbuf.str().empty());
  ASSERT_FALSE(outbuf.str().find(("Warning")) != std::string::npos);
  ASSERT_FALSE(outbuf.str().find(("12345678")) != std::string::npos);
  ASSERT_FALSE(outbuf.str().find(("23456789")) != std::string::npos);
  std::stringstream().swap(outbuf);
  logger() << 12345678;
  ASSERT_TRUE(outbuf.str().empty());
  ASSERT_FALSE(outbuf.str().find(("Warning")) != std::string::npos);
  ASSERT_FALSE(outbuf.str().find(("Info")) != std::string::npos);
  ASSERT_FALSE(outbuf.str().find(("12345678")) != std::string::npos);
}

TEST(LoggerDisabled, colorSwitch) {
  std::stringstream outbuf;
  auto logger = Logger::getLogger(outbuf);

  std::stringstream().swap(outbuf);
  logger() << engine::Logger::Warning << 1234;
  ASSERT_TRUE(outbuf.str().empty());
  ASSERT_FALSE(outbuf.str().find(("\033[1;33m")) != std::string::npos);
  logger() << 1234;
  ASSERT_TRUE(outbuf.str().empty());
  ASSERT_FALSE(outbuf.str().find(("\033[1;0m")) != std::string::npos);
}

TEST(LoggerDisabled, sourceLocation) {
  std::stringstream outbuf;
  auto logger = Logger::getLogger(outbuf);

  logger() << engine::Logger::here(); auto loc = std::source_location::current();
  ASSERT_TRUE(outbuf.str().empty());
  ASSERT_FALSE(outbuf.str().find(std::string() + loc.file_name() + ":" + std::to_string(loc.line())) != std::string::npos);
}

TEST(LoggerDisabled, compatFnSet) {
  Logger::setDefaultLoggerOutput(std::cout);
}

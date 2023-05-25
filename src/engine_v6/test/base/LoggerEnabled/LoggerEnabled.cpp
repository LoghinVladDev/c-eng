//
// Created by loghin on 30/04/23.
//

#include "Test.hpp"
#include "logging/Logger.hpp"
#include <chrono>
#include <string>
#include <CDS/Long>
#include <CDS/threading/Thread>
#include "../shared/LoggerShared.hpp"


TEST(LoggerEnabled, basicOut) {
  std::stringstream outbuf;
  auto logger = Logger::getLogger(outbuf);

  logger() << "basic string output, followed by numeric: " << 123 << std::hex << 15 << std::dec << 24;
  ASSERT_TRUE(outbuf.str().find(date()) != npos);
  ASSERT_TRUE(outbuf.str().find(("level = Info")) != npos);
  ASSERT_TRUE(outbuf.str().find(("thread = 0x" + cds::Long(
    static_cast<cds::sint64>(cds::Thread::currentThreadID())).toString(16)).cStr()) != npos);
  ASSERT_TRUE(outbuf.str().find(("basic string output, followed by numeric: 123f24")) != npos);
}

TEST(LoggerEnabled, levelSwitch) {
  std::stringstream outbuf;
  auto logger = Logger::getLogger(outbuf);

  std::stringstream().swap(outbuf);
  logger() << 12345678;
  ASSERT_TRUE(outbuf.str().find(("Info")) != npos);
  ASSERT_TRUE(outbuf.str().find(("12345678")) != npos);
  ASSERT_FALSE(outbuf.str().find(("Warning")) != npos);

  std::stringstream().swap(outbuf);
  logger() << engine::Logger::Warning << 12345678;
  ASSERT_TRUE(outbuf.str().find(("Warning")) != npos);
  ASSERT_TRUE(outbuf.str().find(("12345678")) != npos);
  ASSERT_FALSE(outbuf.str().find(("Info")) != npos);

  std::stringstream().swap(outbuf);
  logger() << engine::Logger::Error << 12345678;
  ASSERT_TRUE(outbuf.str().find(("Error")) != npos);
  ASSERT_TRUE(outbuf.str().find(("12345678")) != npos);
  ASSERT_FALSE(outbuf.str().find(("Info")) != npos);

  std::stringstream().swap(outbuf);
  logger() << engine::Logger::Debug << 12345678;
  ASSERT_TRUE(outbuf.str().find(("Debug")) != npos);
  ASSERT_TRUE(outbuf.str().find(("12345678")) != npos);
  ASSERT_FALSE(outbuf.str().find(("Info")) != npos);

  std::stringstream().swap(outbuf);
  logger() << engine::Logger::Warning;
  ASSERT_FALSE(outbuf.str().find(("Warning")) != npos);
  ASSERT_FALSE(outbuf.str().find(("12345678")) != npos);
  logger() << 12345678;
  ASSERT_FALSE(outbuf.str().find(("Warning")) != npos);
  ASSERT_TRUE(outbuf.str().find(("Info")) != npos);
  ASSERT_TRUE(outbuf.str().find(("12345678")) != npos);

  std::stringstream().swap(outbuf);
  logger() << engine::Logger::Warning << "23456789";
  ASSERT_TRUE(outbuf.str().find(("Warning")) != npos);
  ASSERT_FALSE(outbuf.str().find(("12345678")) != npos);
  ASSERT_TRUE(outbuf.str().find(("23456789")) != npos);
  std::stringstream().swap(outbuf);
  logger() << 12345678;
  ASSERT_FALSE(outbuf.str().find(("Warning")) != npos);
  ASSERT_TRUE(outbuf.str().find(("Info")) != npos);
  ASSERT_TRUE(outbuf.str().find(("12345678")) != npos);
}

TEST(LoggerEnabled, colorSwitch) {
  std::stringstream outbuf;
  auto logger = Logger::getLogger(outbuf);

  std::stringstream().swap(outbuf);
  logger() << engine::Logger::Warning << 1234;
  ASSERT_TRUE(outbuf.str().find(("\033[1;33m")) != npos);
  logger() << 1234;
  ASSERT_TRUE(outbuf.str().find(("\033[1;0m")) != npos);
}

TEST(LoggerEnabled, sourceLocation) {
  std::stringstream outbuf;
  auto logger = Logger::getLogger(outbuf);

  logger() << engine::Logger::here(); auto loc = std::source_location::current();
  ASSERT_TRUE(
    outbuf.str().find(std::string() + loc.file_name() + ":" + std::to_string(loc.line())) !=
    npos
  );
}

TEST(LoggerEnabled, defaultOut) {
  std::stringstream outbuf;
  auto logger = Logger::getLogger();

  logger() << "test";
  ASSERT_TRUE(outbuf.str().empty());

  Logger::setDefaultLoggerOutput(outbuf);
  auto strLogger = Logger::getLogger();
  strLogger() << "test";
  ASSERT_TRUE(outbuf.str().find("test") != npos);
}

TEST(LoggerEnabled, overlappingLevel) {
  std::stringstream outbuf;
  auto logger = Logger::getLogger(outbuf);
  logger() << Logger::Warning << "test1" << Logger::Error << "test2";
  ASSERT_TRUE(outbuf.str().find("\033[1;33m") != npos);
  ASSERT_FALSE(outbuf.str().find("\033[1;31m") != npos);
}

TEST(LoggerEnabled, defaultLevel) {
  std::stringstream outbuf;
  auto logger = Logger::getLogger(outbuf);

  logger.setDefaultLevel(Logger::Error);
  logger() << "test";
  ASSERT_TRUE(outbuf.str().find("Error") != npos);
  ASSERT_TRUE(outbuf.str().find("\033[1;31m") != npos);
}

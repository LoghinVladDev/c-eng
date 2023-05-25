//
// Created by loghin on 30/04/23.
//

#include "Test.hpp"
#include "logging/Logger.hpp"
#include <string>
#include <CDS/Long>
#include <CDS/threading/Thread>
#include <source_location>
#include "../shared/LoggerShared.hpp"

TEST(LoggerDisabled, basicOut) {
  stringstream outbuf;
  auto logger = getLogger(outbuf);

  logger() << "basic string output, followed by numeric: " << 123 << hex << 15 << dec << 24;
  ASSERT_TRUE(empty(outbuf));
  ASSERT_FALSE(contains(outbuf, date()));
  ASSERT_FALSE(contains(outbuf, "level = Info"));
  ASSERT_FALSE(contains(outbuf, ("thread = 0x" + cds::Long(
          static_cast<cds::sint64>(cds::Thread::currentThreadID())).toString(16)).cStr()));
  ASSERT_FALSE(contains(outbuf, "basic string output, followed by numeric: 123f24"));
}

TEST(LoggerDisabled, levelSwitch) {
  stringstream outbuf;
  auto logger = getLogger(outbuf);

  stringstream().swap(outbuf);
  logger() << 12345678;
  ASSERT_TRUE(empty(outbuf));
  ASSERT_FALSE(outbuf.str().find(("Info")) != npos);
  ASSERT_FALSE(outbuf.str().find(("12345678")) != npos);
  ASSERT_FALSE(outbuf.str().find(("Warning")) != npos);

  stringstream().swap(outbuf);
  logger() << engine::Logger::Warning << 12345678;
  ASSERT_TRUE(outbuf.str().empty());
  ASSERT_FALSE(outbuf.str().find(("Warning")) != npos);
  ASSERT_FALSE(outbuf.str().find(("12345678")) != npos);
  ASSERT_FALSE(outbuf.str().find(("Info")) != npos);

  stringstream().swap(outbuf);
  logger() << engine::Logger::Error << 12345678;
  ASSERT_TRUE(outbuf.str().empty());
  ASSERT_FALSE(outbuf.str().find(("Error")) != npos);
  ASSERT_FALSE(outbuf.str().find(("12345678")) != npos);
  ASSERT_FALSE(outbuf.str().find(("Info")) != npos);

  stringstream().swap(outbuf);
  logger() << engine::Logger::Debug << 12345678;
  ASSERT_TRUE(outbuf.str().empty());
  ASSERT_FALSE(outbuf.str().find(("Debug")) != npos);
  ASSERT_FALSE(outbuf.str().find(("12345678")) != npos);
  ASSERT_FALSE(outbuf.str().find(("Info")) != npos);

  stringstream().swap(outbuf);
  logger() << engine::Logger::Warning;
  ASSERT_TRUE(outbuf.str().empty());
  ASSERT_FALSE(outbuf.str().find(("Warning")) != npos);
  ASSERT_FALSE(outbuf.str().find(("12345678")) != npos);
  logger() << 12345678;
  ASSERT_TRUE(outbuf.str().empty());
  ASSERT_FALSE(outbuf.str().find(("Warning")) != npos);
  ASSERT_FALSE(outbuf.str().find(("Info")) != npos);
  ASSERT_FALSE(outbuf.str().find(("12345678")) != npos);

  stringstream().swap(outbuf);
  logger() << engine::Logger::Warning << "23456789";
  ASSERT_TRUE(outbuf.str().empty());
  ASSERT_FALSE(outbuf.str().find(("Warning")) != npos);
  ASSERT_FALSE(outbuf.str().find(("12345678")) != npos);
  ASSERT_FALSE(outbuf.str().find(("23456789")) != npos);
  stringstream().swap(outbuf);
  logger() << 12345678;
  ASSERT_TRUE(outbuf.str().empty());
  ASSERT_FALSE(outbuf.str().find(("Warning")) != npos);
  ASSERT_FALSE(outbuf.str().find(("Info")) != npos);
  ASSERT_FALSE(outbuf.str().find(("12345678")) != npos);
}

TEST(LoggerDisabled, colorSwitch) {
  stringstream outbuf;
  auto logger = Logger::getLogger(outbuf);

  stringstream().swap(outbuf);
  logger() << engine::Logger::Warning << 1234;
  ASSERT_TRUE(outbuf.str().empty());
  ASSERT_FALSE(outbuf.str().find(("\033[1;33m")) != npos);
  logger() << 1234;
  ASSERT_TRUE(outbuf.str().empty());
  ASSERT_FALSE(outbuf.str().find(("\033[1;0m")) != npos);
}

TEST(LoggerDisabled, sourceLocation) {
  stringstream outbuf;
  auto logger = Logger::getLogger(outbuf);

  logger() << engine::Logger::here(); auto loc = source_location::current();
  ASSERT_TRUE(outbuf.str().empty());
  ASSERT_FALSE(outbuf.str().find(string() + loc.file_name() + ":" + to_string(loc.line())) != npos);
}

TEST(LoggerDisabled, compatFnSet) {
  Logger::setDefaultLoggerOutput(cout);
}

TEST(LoggerEnabled, overlappingLevel) {
  stringstream outbuf;
  auto logger = Logger::getLogger(outbuf);
  logger() << Logger::Warning << "test1" << Logger::Error << "test2";
  ASSERT_FALSE(outbuf.str().find("\033[1;33m") != npos);
  ASSERT_FALSE(outbuf.str().find("\033[1;31m") != npos);
  ASSERT_TRUE(outbuf.str().empty());
}

TEST(LoggerEnabled, defaultLevel) {
  stringstream outbuf;
  auto logger = Logger::getLogger(outbuf);

  logger.setDefaultLevel(Logger::Error);
  logger() << "test";
  ASSERT_TRUE(outbuf.str().empty());
  ASSERT_FALSE(outbuf.str().find("Error") != npos);
  ASSERT_FALSE(outbuf.str().find("\033[1;31m") != npos);
}

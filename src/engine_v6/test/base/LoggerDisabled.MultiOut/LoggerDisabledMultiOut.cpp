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

TEST(LoggerDisabledMultiOut, basic) {
  std::stringstream outbuf1;
  std::stringstream outbuf2;
  auto logger = Logger::getLogger(outbuf1, outbuf2);

  logger() << "basic string output, followed by numeric: " << 123 << std::hex << 15 << std::dec << 24;
  ASSERT_FALSE(outbuf1.str().find(date()) != std::string::npos);
  ASSERT_FALSE(outbuf1.str().find(("level = Info")) != std::string::npos);
  ASSERT_FALSE(outbuf1.str().find(("thread = 0x" + cds::Long(
      static_cast<cds::sint64>(cds::Thread::currentThreadID())).toString(16)).cStr()) != std::string::npos);
  ASSERT_FALSE(outbuf1.str().find(("basic string output, followed by numeric: 123f24")) != std::string::npos);
  ASSERT_FALSE(outbuf2.str().find(date()) != std::string::npos);
  ASSERT_FALSE(outbuf2.str().find(("level = Info")) != std::string::npos);
  ASSERT_FALSE(outbuf2.str().find(("thread = 0x" + cds::Long(
      static_cast<cds::sint64>(cds::Thread::currentThreadID())).toString(16)).cStr()) != std::string::npos);
  ASSERT_FALSE(outbuf2.str().find(("basic string output, followed by numeric: 123f24")) != std::string::npos);
}

TEST(LoggerDisabledMultiOut, levelSwitch) {
  std::stringstream outbuf1;
  std::stringstream outbuf2;
  auto logger = Logger::getLogger(outbuf1, outbuf2);

  std::stringstream().swap(outbuf1);
  std::stringstream().swap(outbuf2);
  logger() << 12345678;
  ASSERT_FALSE(outbuf1.str().find(("Info")) != std::string::npos);
  ASSERT_FALSE(outbuf1.str().find(("12345678")) != std::string::npos);
  ASSERT_FALSE(outbuf1.str().find(("Warning")) != std::string::npos);
  ASSERT_FALSE(outbuf2.str().find(("Info")) != std::string::npos);
  ASSERT_FALSE(outbuf2.str().find(("12345678")) != std::string::npos);
  ASSERT_FALSE(outbuf2.str().find(("Warning")) != std::string::npos);

  std::stringstream().swap(outbuf1);
  std::stringstream().swap(outbuf2);
  logger() << engine::Logger::Warning << 12345678;
  ASSERT_FALSE(outbuf1.str().find(("Warning")) != std::string::npos);
  ASSERT_FALSE(outbuf1.str().find(("12345678")) != std::string::npos);
  ASSERT_FALSE(outbuf1.str().find(("Info")) != std::string::npos);
  ASSERT_FALSE(outbuf2.str().find(("Warning")) != std::string::npos);
  ASSERT_FALSE(outbuf2.str().find(("12345678")) != std::string::npos);
  ASSERT_FALSE(outbuf2.str().find(("Info")) != std::string::npos);

  std::stringstream().swap(outbuf1);
  std::stringstream().swap(outbuf2);
  logger() << engine::Logger::Error << 12345678;
  ASSERT_FALSE(outbuf1.str().find(("Error")) != std::string::npos);
  ASSERT_FALSE(outbuf1.str().find(("12345678")) != std::string::npos);
  ASSERT_FALSE(outbuf1.str().find(("Info")) != std::string::npos);
  ASSERT_FALSE(outbuf2.str().find(("Error")) != std::string::npos);
  ASSERT_FALSE(outbuf2.str().find(("12345678")) != std::string::npos);
  ASSERT_FALSE(outbuf2.str().find(("Info")) != std::string::npos);

  std::stringstream().swap(outbuf1);
  std::stringstream().swap(outbuf2);
  logger() << engine::Logger::Debug << 12345678;
  ASSERT_FALSE(outbuf1.str().find(("Debug")) != std::string::npos);
  ASSERT_FALSE(outbuf1.str().find(("12345678")) != std::string::npos);
  ASSERT_FALSE(outbuf1.str().find(("Info")) != std::string::npos);
  ASSERT_FALSE(outbuf2.str().find(("Debug")) != std::string::npos);
  ASSERT_FALSE(outbuf2.str().find(("12345678")) != std::string::npos);
  ASSERT_FALSE(outbuf2.str().find(("Info")) != std::string::npos);

  std::stringstream().swap(outbuf1);
  std::stringstream().swap(outbuf2);
  logger() << engine::Logger::Warning;
  logger() << 12345678;
  ASSERT_FALSE(outbuf1.str().find(("Warning")) != std::string::npos);
  ASSERT_FALSE(outbuf1.str().find(("Info")) != std::string::npos);
  ASSERT_FALSE(outbuf1.str().find(("12345678")) != std::string::npos);
  ASSERT_FALSE(outbuf2.str().find(("Warning")) != std::string::npos);
  ASSERT_FALSE(outbuf2.str().find(("Info")) != std::string::npos);
  ASSERT_FALSE(outbuf2.str().find(("12345678")) != std::string::npos);

  std::stringstream().swap(outbuf1);
  std::stringstream().swap(outbuf2);
  logger() << engine::Logger::Warning << "23456789";
  ASSERT_FALSE(outbuf1.str().find(("Warning")) != std::string::npos);
  ASSERT_FALSE(outbuf1.str().find(("12345678")) != std::string::npos);
  ASSERT_FALSE(outbuf1.str().find(("23456789")) != std::string::npos);
  ASSERT_FALSE(outbuf2.str().find(("Warning")) != std::string::npos);
  ASSERT_FALSE(outbuf2.str().find(("12345678")) != std::string::npos);
  ASSERT_FALSE(outbuf2.str().find(("23456789")) != std::string::npos);
  std::stringstream().swap(outbuf1);
  std::stringstream().swap(outbuf2);
  logger() << 12345678;
  ASSERT_FALSE(outbuf1.str().find(("Warning")) != std::string::npos);
  ASSERT_FALSE(outbuf1.str().find(("Info")) != std::string::npos);
  ASSERT_FALSE(outbuf1.str().find(("12345678")) != std::string::npos);
  ASSERT_FALSE(outbuf2.str().find(("Warning")) != std::string::npos);
  ASSERT_FALSE(outbuf2.str().find(("Info")) != std::string::npos);
  ASSERT_FALSE(outbuf2.str().find(("12345678")) != std::string::npos);
}

TEST(LoggerDisabledMultiOut, colorSwitch) {
  std::stringstream outbuf1;
  std::stringstream outbuf2;
  auto logger = Logger::getLogger(outbuf1, outbuf2);

  std::stringstream().swap(outbuf1);
  std::stringstream().swap(outbuf2);
  logger() << engine::Logger::Warning << 1234;
  ASSERT_FALSE(outbuf1.str().find(("\033[1;33m")) != std::string::npos);
  ASSERT_FALSE(outbuf2.str().find(("\033[1;33m")) != std::string::npos);
  logger() << 1234;
  ASSERT_FALSE(outbuf1.str().find(("\033[1;0m")) != std::string::npos);
  ASSERT_FALSE(outbuf2.str().find(("\033[1;0m")) != std::string::npos);
}

TEST(LoggerDisabledMultiOut, isolation) {
  std::stringstream outbuf1;
  std::stringstream outbuf2;
  auto logger = Logger::getLogger(outbuf1, outbuf2);

  logger() << "test";
  std::stringstream().swap(outbuf2);
  ASSERT_TRUE(outbuf1.str().empty());
  ASSERT_TRUE(outbuf2.str().empty());
  ASSERT_FALSE(outbuf1.str().find("test") != std::string::npos);
  ASSERT_FALSE(outbuf2.str().find("test") != std::string::npos);
}


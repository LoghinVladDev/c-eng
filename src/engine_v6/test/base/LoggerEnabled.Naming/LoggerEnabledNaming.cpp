//
// Created by loghin on 30/04/23.
//

#include "core/Config.hpp"
#include "Test.hpp"
#include "logging/Logger.hpp"
#include <chrono>
#include <string>
#include <CDS/Long>
#include <CDS/threading/Thread>
#include "../shared/LoggerShared.hpp"


TEST(LoggerEnabledNaming, Anonymous) {
  std::stringstream outbuf1;
  auto logger1 = Logger::getLogger(outbuf1);
  std::stringstream outbuf2;
  auto logger2 = Logger::getLogger(outbuf2);
  auto logger3 = Logger::getLogger();

  ASSERT_NE(&logger1, &logger2);
  ASSERT_NE(&logger1, &logger3);
  ASSERT_NE(&logger2, &logger3);

  logger1() << "test";
  logger2() << "other";
  ASSERT_FALSE(outbuf1.str().empty());
  ASSERT_FALSE(outbuf2.str().empty());
  ASSERT_TRUE(outbuf1.str().find(("logger = anonymous_logger")) != std::string::npos);
  ASSERT_TRUE(outbuf2.str().find(("logger = anonymous_logger")) != std::string::npos);
  ASSERT_NE(outbuf1.str(), outbuf2.str());
  ASSERT_TRUE(outbuf1.str().find(("test")) != std::string::npos);
  ASSERT_TRUE(outbuf2.str().find(("other")) != std::string::npos);
}

TEST(LoggerEnabledNaming, Named) {
  std::stringstream outbuf1;
  std::stringstream outbuf2;
  std::stringstream outbuf3;
  auto& logger1 = Logger::getLogger("logger1", outbuf1);
  auto logger2 = Logger::getLogger("logger2", outbuf2);
  auto& logger3 = Logger::getLogger("logger1");
  auto logger4 = Logger::getLogger("logger1", outbuf3);

  ASSERT_NE(&logger1, &logger2);
  ASSERT_EQ(&logger1, &logger3);
  ASSERT_NE(&logger1, &logger4);
  ASSERT_NE(&logger2, &logger4);

  logger1() << "one test";
  logger2() << "another test";
  logger3() << "yet one more";
  logger4() << "final test";

  ASSERT_TRUE(outbuf1.str().find(("one test")) != std::string::npos);
  ASSERT_FALSE(outbuf1.str().find(("another test")) != std::string::npos);
  ASSERT_TRUE(outbuf1.str().find(("yet one more")) != std::string::npos);
  ASSERT_TRUE(outbuf1.str().find(("final test")) != std::string::npos);

  ASSERT_FALSE(outbuf2.str().find(("one test")) != std::string::npos);
  ASSERT_TRUE(outbuf2.str().find(("another test")) != std::string::npos);
  ASSERT_FALSE(outbuf2.str().find(("yet one more")) != std::string::npos);
  ASSERT_FALSE(outbuf2.str().find(("final test")) != std::string::npos);
  ASSERT_TRUE(outbuf3.str().empty());
}

TEST(LoggerEnabledNaming, Acq) {
  auto const& logger = Logger::getLogger("testLog");
  ASSERT_EQ(logger.name(), "testLog");
}

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
#include <source_location>
#include "core/Object.hpp"

namespace {
    using engine::Logger;
}

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
    ASSERT_TRUE(outbuf1.str().empty());
    ASSERT_TRUE(outbuf2.str().empty());
    ASSERT_FALSE(outbuf1.str().contains("logger = anonymous_logger"));
    ASSERT_FALSE(outbuf2.str().contains("logger = anonymous_logger"));
    ASSERT_EQ(outbuf1.str(), outbuf2.str());
    ASSERT_FALSE(outbuf1.str().contains("test"));
    ASSERT_FALSE(outbuf2.str().contains("other"));
}

TEST(LoggerEnabledNamic, Named) {
    std::stringstream outbuf1;
    std::stringstream outbuf2;
    std::stringstream outbuf3;
    auto& logger1 = Logger::getLogger("logger1", outbuf1);
    auto logger2 = Logger::getLogger("logger2", outbuf2);
    auto& logger3 = Logger::getLogger("logger1");
    auto logger4 = Logger::getLogger("logger1", outbuf3);
    auto& logger5 = Logger::getLogger("test");
    auto& logger6 = Logger::getLogger("test2", std::cout);

    ASSERT_NE(&logger1, &logger2);
    ASSERT_EQ(&logger1, &logger3);
    ASSERT_NE(&logger1, &logger4);
    ASSERT_NE(&logger2, &logger4);
    ASSERT_EQ(&logger1, &logger5);
    ASSERT_EQ(&logger1, &logger6);

    logger1() << "one test";
    logger2() << "another test";
    logger3() << "yet one more";
    logger4() << "final test";

    ASSERT_FALSE(outbuf1.str().contains("one test"));
    ASSERT_FALSE(outbuf1.str().contains("another test"));
    ASSERT_FALSE(outbuf1.str().contains("yet one more"));
    ASSERT_FALSE(outbuf1.str().contains("final test"));

    ASSERT_FALSE(outbuf2.str().contains("one test"));
    ASSERT_FALSE(outbuf2.str().contains("another test"));
    ASSERT_FALSE(outbuf2.str().contains("yet one more"));
    ASSERT_FALSE(outbuf2.str().contains("final test"));
}

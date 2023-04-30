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

TEST(LoggerDisabled, basicOut) {
    std::stringstream outbuf;
    engine::Logger logger(outbuf);

    logger << "basic string output, followed by numeric: " << 123 << std::hex << 15 << std::dec << 24;
    ASSERT_TRUE(outbuf.str().empty());
    ASSERT_FALSE(outbuf.str().contains(date()));
    ASSERT_FALSE(outbuf.str().contains("level = Info"));
    ASSERT_FALSE(outbuf.str().contains(("thread = 0x" + cds::Long(
            static_cast<cds::sint64>(cds::Thread::currentThreadID())).toString(16)).cStr()));
    ASSERT_FALSE(outbuf.str().contains("basic string output, followed by numeric: 123f24"));
}

TEST(LoggerDisabled, levelSwitch) {
    std::stringstream outbuf;
    engine::Logger logger(outbuf);

    std::stringstream().swap(outbuf);
    logger.endl() << 12345678;
    ASSERT_TRUE(outbuf.str().empty());
    ASSERT_FALSE(outbuf.str().contains("Info"));
    ASSERT_FALSE(outbuf.str().contains("12345678"));
    ASSERT_FALSE(outbuf.str().contains("Warning"));

    std::stringstream().swap(outbuf);
    logger.endl() << engine::Logger::Warning << 12345678;
    ASSERT_TRUE(outbuf.str().empty());
    ASSERT_FALSE(outbuf.str().contains("Warning"));
    ASSERT_FALSE(outbuf.str().contains("12345678"));
    ASSERT_FALSE(outbuf.str().contains("Info"));

    std::stringstream().swap(outbuf);
    logger.endl() << engine::Logger::Error << 12345678;
    ASSERT_TRUE(outbuf.str().empty());
    ASSERT_FALSE(outbuf.str().contains("Error"));
    ASSERT_FALSE(outbuf.str().contains("12345678"));
    ASSERT_FALSE(outbuf.str().contains("Info"));

    std::stringstream().swap(outbuf);
    logger.endl() << engine::Logger::Debug << 12345678;
    ASSERT_TRUE(outbuf.str().empty());
    ASSERT_FALSE(outbuf.str().contains("Debug"));
    ASSERT_FALSE(outbuf.str().contains("12345678"));
    ASSERT_FALSE(outbuf.str().contains("Info"));

    std::stringstream().swap(outbuf);
    logger.endl() << engine::Logger::Warning;
    ASSERT_TRUE(outbuf.str().empty());
    ASSERT_FALSE(outbuf.str().contains("Warning"));
    ASSERT_FALSE(outbuf.str().contains("12345678"));
    logger.endl() << 12345678;
    ASSERT_TRUE(outbuf.str().empty());
    ASSERT_FALSE(outbuf.str().contains("Warning"));
    ASSERT_FALSE(outbuf.str().contains("Info"));
    ASSERT_FALSE(outbuf.str().contains("12345678"));

    std::stringstream().swap(outbuf);
    logger.endl() << engine::Logger::Warning << "23456789";
    ASSERT_TRUE(outbuf.str().empty());
    ASSERT_FALSE(outbuf.str().contains("Warning"));
    ASSERT_FALSE(outbuf.str().contains("12345678"));
    ASSERT_FALSE(outbuf.str().contains("23456789"));
    std::stringstream().swap(outbuf);
    logger.endl() << 12345678;
    ASSERT_TRUE(outbuf.str().empty());
    ASSERT_FALSE(outbuf.str().contains("Warning"));
    ASSERT_FALSE(outbuf.str().contains("Info"));
    ASSERT_FALSE(outbuf.str().contains("12345678"));
}

TEST(LoggerDisabled, colorSwitch) {
    std::stringstream outbuf;
    engine::Logger logger(outbuf);

    std::stringstream().swap(outbuf);
    logger.endl() << engine::Logger::Warning << 1234;
    ASSERT_TRUE(outbuf.str().empty());
    ASSERT_FALSE(outbuf.str().contains("\033[1;33m"));
    logger.endl() << 1234;
    ASSERT_TRUE(outbuf.str().empty());
    ASSERT_FALSE(outbuf.str().contains("\033[1;0m"));
}

TEST(LoggerDisabled, sourceLocation) {
    std::stringstream outbuf;
    engine::Logger logger(outbuf);

    logger.endl() << engine::Logger::here(); auto loc = std::source_location::current();
    ASSERT_TRUE(outbuf.str().empty());
    ASSERT_FALSE(outbuf.str().contains(std::string() + loc.file_name() + ":" + std::to_string(loc.line())));
}


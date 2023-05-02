//
// Created by loghin on 25/04/23.
//

#include "Logger.hpp"
#include <sstream>
#include <chrono>
#include <CDS/threading/Thread>
#include <CDS/TreeMap>

namespace {
    using std::stringstream;
    using engine::config::value;
    using engine::config::ParameterType;
    using std::string;

    using cds::TreeMap;
    using cds::String;
    using cds::StringView;

    auto timestamp () noexcept {
        int const timeBufferSize = 512U;
        using sys_clock = std::chrono::system_clock;

        auto timePoint = sys_clock::now();
        auto asTimeT = sys_clock::to_time_t(timePoint);
        auto * timeInfo = std::localtime (& asTimeT);

        string asString (timeBufferSize, '\0');
        asString.resize(std::strftime (asString.data(), timeBufferSize, "%d-%m-%Y", timeInfo));
        asString.resize(asString.length());

        return asString;
    }
}

namespace engine {

    template <bool = value <ParameterType::LoggingEnabled>>
    class LoggerContainer: private TreeMap <StringView, Logger> {
    public:
        constexpr auto setDefaultOut(std::ostream& out) noexcept -> void {
            pDefaultOut = &out;
        }

        inline auto getLoggerHint(Logger&& hint, Logger const& disabled) noexcept -> Logger& {
            (void) disabled;
            return this->emplace(hint.name(), std::move(hint)).value();
        }

        constexpr auto defaultOut() noexcept -> std::ostream& {
            return *pDefaultOut;
        }

    private:
        std::ostream * pDefaultOut = &std::cout;
    };

    template <>
    class LoggerContainer<false> {
    public:
        constexpr auto setDefaultOut(std::ostream& out) noexcept -> void {
            (void) out;
        }

        inline auto getLoggerHint(Logger&& hint, Logger& disabled) noexcept -> Logger& {
            (void) hint;
            return disabled;
        }

        constexpr auto defaultOut() noexcept -> std::ostream& {
            return std::cout;
        }
    };

    namespace meta {
        auto LoggerBase<true>::addHeader () noexcept -> void {

            auto colorHeader = [option=static_cast<Option>(flags & levelMask)]{
                switch (option) {
                    default:
                    case Option::None:
                    case Option::Start:     return "";
                    case Option::Error:     return "\033[1;31m";
                    case Option::Warning:   return "\033[1;33m";
                    case Option::Debug:     return "\033[1;36m";
                    case Option::Info:      return "\033[1;37m";
                }
            };

            (*pBaseOut) <<
                    colorHeader() <<
                    "[time = " << timestamp() << "]"
                    "[logger = " << loggerName << "]"
                    "[level = " << levelAsStr () << "]"
                    "[thread = 0x" << std::hex << cds::Thread::currentThreadID() << "]"
                    " -> " << std::dec;
        }
    } // namespace meta

    namespace {
        LoggerContainer container;
    }

    auto Logger::getLogger(StringView name, std::ostream& out) noexcept -> Logger& {
        static auto persistentDisabledLogger = Logger {"anonymous_logger", std::cout};
        auto loggerHint = Logger {name, out};
        return container.getLoggerHint(std::move(loggerHint), persistentDisabledLogger);
    }

    auto Logger::getLogger(StringView name) noexcept -> Logger& {
        return getLogger(name, container.defaultOut());
    }

    auto Logger::getLogger(std::ostream& out) noexcept -> Logger {
        return {"anonymous_logger", out};
    }

    auto Logger::getLogger() noexcept -> Logger {
        return getLogger(container.defaultOut());
    }

    auto Logger::setDefaultLoggerOutput(std::ostream& out) noexcept -> void {
        container.setDefaultOut(out);
    }
} // namespace engine

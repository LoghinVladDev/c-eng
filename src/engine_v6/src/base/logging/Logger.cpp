//
// Created by loghin on 25/04/23.
//

#include "Logger.hpp"
#include <sstream>
#include <chrono>
#include <CDS/threading/Thread>

namespace engine::meta {

    using std::stringstream;
    using config::value;
    using config::ParameterType;
    using std::string;

    bool get () {return value<ParameterType::LoggingEnabled>;}

    template <bool = value <ParameterType::LoggingEnabled>>
    struct InlineLoggerOutBufferContainer {

    };

    template <>
    class InlineLoggerOutBufferContainer <false> {
    private:
        static auto init () noexcept -> stringstream {
            try {
                return {};
            } catch (...) {
                std::cerr << "Unable to create dummy logger output. The program will terminate\n";
                std::terminate();
            }
        }

    public:
        static inline stringstream dummyOut = init();
    };

    LoggingObjectDisabledContainer<false>::InlineLogger::InlineLogger() noexcept :
            Logger (InlineLoggerOutBufferContainer <false> :: dummyOut) {

    }

    namespace {
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

        baseOut <<
                colorHeader() <<
                "[time = " << timestamp() << "]"
                "[logger = " << "testLoggerReplace" << "]"
                "[level = " << levelAsStr () << "]"
                "[thread = 0x" << std::hex << cds::Thread::currentThreadID() << "]"
                " -> " << std::dec;
    }
}

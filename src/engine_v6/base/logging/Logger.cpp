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

    auto LoggerBase<true>::startLogItem () noexcept -> void {
        if (isSet (Option::Start)) {
            baseOut << std::dec << std::endl;
            clearFlags();
        }
    }

    namespace {
        auto timestamp () noexcept {
            int const timeBufferSize = 512U;
            using sys_clock = std::chrono::system_clock;

            auto timePoint = sys_clock::now();
            auto asTimeT = sys_clock::to_time_t(timePoint);
            auto * timeInfo = std::localtime (& asTimeT);

            string asString (timeBufferSize, '\0');
            (void) std::strftime (asString.data(), timeBufferSize, "%d-%m-%Y-%H:%M:%S", timeInfo);

            return asString;
        }
    }

    auto LoggerBase<true>::addHeader () noexcept -> void {

        baseOut <<
                "[time = " << timestamp() << "]"
                "[logger = " << "testLoggerReplace" << "]"
                "[level = " << levelAsStr () << "]"
                "[thread = 0x" << std::hex << cds::Thread::currentThreadID() << "]"
                " -> ";
    }
}

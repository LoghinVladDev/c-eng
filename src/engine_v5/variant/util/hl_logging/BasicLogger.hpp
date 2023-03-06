//
// Created by loghin on 06/03/23.
//

#ifndef __C_ENG_BASICLOGGER_HPP__
#define __C_ENG_BASICLOGGER_HPP__

#include <chrono>

#include <CDS/Array>
#include <CDS/String>
#include <CDS/threading/Thread>

#include <hl_core/Object.hpp>
#include <hl_logging/Logger.hpp>

namespace engine::io {

    class BasicLogger : public engine::io::Logger {
    private:
        cds::Array <std::ostream *> _outputs;
        cds::String                 _name;

    public:
        explicit BasicLogger (cds::String name) : _name (std::move(name)) {}
        auto addOutput (std::ostream & out) { this->_outputs.pushBack (& out); }

        auto log (Level level, cds::StringView message) const noexcept -> void override {

            char timeBuffer [512U];
            tm timeStruct;
            auto time = std::chrono::system_clock::to_time_t (std::chrono::system_clock::now());

    #if defined(__CDS_Platform_Linux)
            localtime_r ( & time, & timeStruct );
    #else
            localtime_s ( & timeStruct, & time );
    #endif

            (void) std::strftime (
                    timeBuffer, 512U,
                    "%d-%m-%Y-%H:%M:%S",
                    & timeStruct
            );

            auto msg = cds::String::f (
                    "[time = %s][logger = %s][level = %s][thread = 0x%llx] -> %s",
                    timeBuffer,
                    this->_name.cStr(),
                    levelToString (level),
                    cds::Thread::currentThreadID(),
                    message.cStr()
            );

            for (auto * pOut : this->_outputs) {
                auto & out = * pOut;
                out << msg << '\n';
            }
        }

        auto log (Level level, cds::StringView message, cds::StringView fileName, cds::StringView functionName, long long int lineNumber) const noexcept -> void override {

            char timeBuffer [512U];
            tm timeStruct;
            auto time = std::chrono::system_clock::to_time_t (std::chrono::system_clock::now());

    #if defined(__CDS_Platform_Linux)
            localtime_r ( & time, & timeStruct );
    #else
            localtime_s ( & timeStruct, & time );
    #endif

            (void) std::strftime (
                    timeBuffer, 512U,
                    "%d-%m-%Y-%H:%M:%S",
                    & timeStruct
            );

            auto msg = cds::String::f (
                    "[%s:%d -> %s][time = %s][logger = %s][level = %s][thread = 0x%llx] -> %s",
                    fileName.cStr(),
                    lineNumber,
                    functionName.cStr(),
                    timeBuffer,
                    this->_name.cStr(),
                    levelToString (level),
                    cds::Thread::currentThreadID(),
                    message.cStr()
            );

            for (auto * pOut : this->_outputs) {
                auto & out = * pOut;
                out << msg << '\n';
            }
        }

        auto log (Level level, cds::StringView message, cds::StringView fileName, cds::StringView functionName, long long int lineNumber, engine::Object const * pObject) const noexcept -> void override {

            char timeBuffer [512U];
            tm timeStruct;
            auto time = std::chrono::system_clock::to_time_t (std::chrono::system_clock::now());

    #if defined(__CDS_Platform_Linux)
            localtime_r ( & time, & timeStruct );
    #else
            localtime_s ( & timeStruct, & time );
    #endif

            (void) std::strftime (
                    timeBuffer, 512U,
                    "%d-%m-%Y-%H:%M:%S",
                    & timeStruct
            );

            auto msg = cds::String::f (
                    "[%s:%d -> %s][time = %s][logger = %s][level = %s][type = %s, object = 0x%llx, thread = 0x%llx] -> %s",
                    fileName.cStr(),
                    lineNumber,
                    functionName.cStr(),
                    timeBuffer,
                    this->_name.cStr(),
                    levelToString (level),
                    pObject->className().cStr(),
                    reinterpret_cast <cds::uint64> (pObject),
                    cds::Thread::currentThreadID(),
                    message.cStr()
            );

            for (auto * pOut : this->_outputs) {
                auto & out = * pOut;
                out << msg << '\n';
            }
        }
    };

}


#endif //__C_ENG_BASICLOGGER_HPP__

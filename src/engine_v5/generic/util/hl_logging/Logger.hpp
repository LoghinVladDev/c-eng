//
// Created by loghin on 26/02/23.
//

#ifndef __C_ENG_LOGGER_HPP__
#define __C_ENG_LOGGER_HPP__

#include <CDS/Object>
#include <hl_core/Toggles.hpp>

#if __C_ENG_LOGGING_ENABLED


#include <hl_core/Compiler.hpp>

#ifndef __C_ENG_LOG
#define __C_ENG_LOG(_logger, _level, _message) _logger->log(engine::io::Logger::Level::_level, _message, __C_ENG_E_FILE__, __C_ENG_E_FUNCTION__, __C_ENG_E_LINE__)
#endif


#else

#ifndef __C_ENG_LOG
#define __C_ENG_LOG(_logger, _level, _message)
#endif


#endif


namespace engine {
    class Object;
}

namespace engine::io {

    class Logger : public cds::Object {
    public:
        enum Level {
            Critical    = 0x01U,
            Error       = 0x02U,
            Warning     = 0x04U,
            Debug       = 0x08U,
            Info        = 0x10U
        };

    protected:
        __CDS_NoDiscard constexpr static auto levelToString (Level level) noexcept -> cds::StringLiteral {
            switch (level) {
                case Critical:  return "Critical";
                case Error:     return "Error";
                case Warning:   return "Warning";
                case Debug:     return "Debug";
                case Info:      return "Info";
            }

            return "Undefined";
        }

    public:
        ~Logger () noexcept override = default;

        virtual auto log (
                Level           level,
                cds::StringView message
        ) const noexcept -> void = 0;

        virtual auto log (
                Level           level,
                cds::StringView message,
                cds::StringView fileName,
                cds::StringView functionName,
                long long int   lineNumber
        ) const noexcept -> void;

        virtual auto log (
                Level                   level,
                cds::StringView         message,
                cds::StringView         fileName,
                cds::StringView         functionName,
                long long int           lineNumber,
                engine::Object  const * pObject
        ) const noexcept -> void;

        auto critical (cds::StringView message) const noexcept -> void {
            return this->log (Critical, message);
        }

        auto error (cds::StringView message) const noexcept -> void {
            return this->log (Error, message);
        }

        auto warning (cds::StringView message) const noexcept -> void {
            return this->log (Warning, message);
        }

        auto info (cds::StringView message) const noexcept -> void {
            return this->log (Info, message);
        }

        auto debug (cds::StringView message) const noexcept -> void {
            return this->log (Debug, message);
        }
    };

}


#endif //__C_ENG_LOGGER_HPP__

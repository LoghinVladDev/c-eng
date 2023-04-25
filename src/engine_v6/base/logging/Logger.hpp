#pragma once

#include <CDS/meta/TypeTraits>
#include <core/Config.hpp>
#include <source_location>
#include <ostream>

namespace engine {
    namespace meta {
        template <bool = config::value <config::ParameterType::LoggingEnabled>>
        class LoggerBase {
        public:
            explicit LoggerBase (std::ostream & out) noexcept {(void) out;}

            template <typename T>
            auto operator << (T && logged) noexcept -> LoggerBase & {
                (void) logged;
                return * this;
            }

        protected:
            auto startLogItem () noexcept -> void {}
        };

        template <>
        class LoggerBase <true> {
        public:
            enum class Option {
                None    = 0x00000000,
                Start   = 0x00000001,

                Error   = 0x00000002,
                Warning = 0x00000004,
                Debug   = 0x00000008,
                Info    = 0x00000010
            };

            explicit LoggerBase (std::ostream & out) noexcept : baseOut (out) {}

            template <typename T>
            auto operator << (T && logged) noexcept -> LoggerBase & {

                auto started = isSet (Option::Start);
                set (IfOption <T> :: then (std::forward <T> (logged)));
                if (! started && isSet (Option::Start)) {
                    addHeader();
                }

                baseOut << std::forward <T> (logged);
                return * this;
            }

        protected:
            auto startLogItem () noexcept -> void;

        private:
            std::ostream & baseOut;
            cds::uint32 flags = defaultFlags;

            constexpr static cds::uint32 const levelMask =
                    static_cast <cds::uint32> (Option::Debug)   |
                    static_cast <cds::uint32> (Option::Warning) |
                    static_cast <cds::uint32> (Option::Error)   |
                    static_cast <cds::uint32> (Option::Info);

            constexpr static cds::uint32 const defaultFlags =
                    static_cast <cds::uint32> (Option::Info);

            auto addHeader () noexcept -> void;
            [[nodiscard]] constexpr auto levelAsStr () const noexcept -> cds::StringLiteral {
                using enum Option;

                switch (static_cast <Option> (this->flags & levelMask)) {
                    case Debug:     return "Debug";
                    case Error:     return "Error";
                    case Warning:   return "Warning";
                    case Info:      return "Info";
                    default:        return "Invalid";
                }
            }

            [[nodiscard]] constexpr auto isSet (Option option) const noexcept -> bool {
                return (flags & static_cast <cds::uint32> (option)) != 0U;
            }

            constexpr auto set (Option option) noexcept -> void {
                auto const asFlag = static_cast <cds::uint32> (option);
                if ((levelMask & asFlag) != 0U) {
                    flags &= ~ levelMask;
                }

                flags |= static_cast <cds::uint32> (option);
            }

            constexpr auto clearFlags () noexcept -> void { flags = defaultFlags; }

            template <typename T>
            struct IfOption {
                constexpr static auto then (T && obj) noexcept -> Option {
                    (void) obj;
                    return Option::Start;
                }
            };

            template <>
            struct IfOption <Option> {
                constexpr static auto then (Option option) noexcept -> Option {
                    return option;
                }
            };

            template <>
            struct IfOption <decltype (std::hex)> {
                constexpr static auto then (decltype(std::hex) unused) noexcept -> Option {
                    (void) unused;
                    return Option::None;
                }
            };
        };
    }

    class Logger : public meta::LoggerBase <> {
    public:
        using Base = meta::LoggerBase <>;
        using Base::LoggerBase;

        auto endl () noexcept -> Logger & {
            Base::startLogItem();
            return * this;
        }
    };

    namespace meta {

        template <bool = config::value <config::ParameterType::LoggingEnabled>>
        struct LoggingObjectDisabledContainer {};

        template <>
        struct LoggingObjectDisabledContainer <false> {
            class InlineLogger : public Logger {
            public:
                InlineLogger () noexcept;
            };

            static inline InlineLogger inlineEmptyLogger;
        };

        enum class LoggingObjectType {
            Direct,
            Indirect,
            Both
        };

        template <typename T, LoggingObjectType, bool = config::value <config::ParameterType::LoggingEnabled>>
        struct LoggingObjectBase {
            [[nodiscard]] constexpr auto logger () const noexcept -> Logger & {
                return LoggingObjectDisabledContainer <false> :: inlineEmptyLogger;
            }
        };

        class LoggerOwner {
        public:
            constexpr auto setLogger (Logger * pNewLogger) noexcept -> void {
                pLogger = pNewLogger;
            }

        protected:
            [[nodiscard]] constexpr auto getLogger () const noexcept -> Logger * {
                return pLogger;
            }

        private:
            Logger * pLogger = nullptr;
        };

        template <>
        class LoggingObjectBase <void, LoggingObjectType::Direct, true> : public LoggerOwner {
        public:
            [[nodiscard]] constexpr auto logger () const noexcept -> Logger & {
                return LoggerOwner::getLogger()->endl();
            }
        };

        template <typename T>
        class LoggingObjectBase <T, LoggingObjectType::Indirect, true> {
        public:
            [[nodiscard]] constexpr auto logger () const noexcept -> Logger & {
                return static_cast <T const *> (this)->parent->logger().endl();
            }
        };

        template <typename T>
        class LoggingObjectBase <T, LoggingObjectType::Both, true> : public LoggerOwner {
            [[nodiscard]] constexpr auto logger () const noexcept -> Logger & {
                if (LoggerOwner::getLogger() != nullptr) {
                    return * LoggerOwner::getLogger();
                }

                return static_cast <T const *> (this)->parent()->logger().endl();
            }
        };
    }

    class DirectLoggingObject : public meta::LoggingObjectBase <void, meta::LoggingObjectType::Direct> {};

    template <typename T>
    class IndirectLoggingObject : public meta::LoggingObjectBase <T, meta::LoggingObjectType::Indirect> {};

    template <typename T>
    class LoggingObject : public meta::LoggingObjectBase <T, meta::LoggingObjectType::Both> {};
}
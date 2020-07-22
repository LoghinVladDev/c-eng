//
// Created by loghin on 7/20/20.
//

#ifndef ENG1_STRING_H
#define ENG1_STRING_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <obj/util/data/Array.h>

#include <cstdlib>

namespace engine { class String; }

bool operator == (const engine::String&, const engine::String&) noexcept;
bool operator == (const engine::String&, const std::string&) noexcept;
bool operator == (const std::string&, const engine::String&) noexcept;
bool operator == (const engine::String&, const char*) noexcept;
bool operator == (const char*, const engine::String&) noexcept;

bool operator != (const engine::String&, const engine::String&) noexcept;
bool operator != (const engine::String&, const std::string&) noexcept;
bool operator != (const std::string&, const engine::String&) noexcept;
bool operator != (const engine::String&, const char*) noexcept;
bool operator != (const char*, const engine::String&) noexcept;

bool operator < (const engine::String&, const engine::String&) noexcept;
bool operator < (const engine::String&, const std::string&) noexcept;
bool operator < (const std::string&, const engine::String&) noexcept;
bool operator < (const engine::String&, const char*) noexcept;
bool operator < (const char*, const engine::String&) noexcept;

bool operator > (const engine::String&, const engine::String&) noexcept;
bool operator > (const engine::String&, const std::string&) noexcept;
bool operator > (const std::string&, const engine::String&) noexcept;
bool operator > (const engine::String&, const char*) noexcept;
bool operator > (const char*, const engine::String&) noexcept;

bool operator <= (const engine::String&, const engine::String&) noexcept;
bool operator <= (const engine::String&, const std::string&) noexcept;
bool operator <= (const std::string&, const engine::String&) noexcept;
bool operator <= (const engine::String&, const char*) noexcept;
bool operator <= (const char*, const engine::String&) noexcept;

bool operator >= (const engine::String&, const engine::String&) noexcept;
bool operator >= (const engine::String&, const std::string&) noexcept;
bool operator >= (const std::string&, const engine::String&) noexcept;
bool operator >= (const engine::String&, const char*) noexcept;
bool operator >= (const char*, const engine::String&) noexcept;

engine::String operator+ (const engine::String&, const engine::String&) noexcept;
engine::String operator+ (const engine::String&, const std::string&) noexcept;
engine::String operator+ (const std::string&, const engine::String&) noexcept;
engine::String operator+ (const engine::String&, const char*) noexcept;
engine::String operator+ (const char*, const engine::String&) noexcept;
engine::String operator+ (char, const engine::String&) noexcept;
engine::String operator+ (const engine::String&, char) noexcept;

std::istream& operator >> (std::istream&, engine::String&)          noexcept (false);
std::ostream& operator << (std::ostream&, const engine::String&)    noexcept (false);

namespace engine {

    class StringAccessOutOfBounds : public std::exception {
    private:
        bool withMessage {false};
        std::string m_message {std::string()};
    public:
        StringAccessOutOfBounds(std::size_t _i, std::size_t _c) noexcept : std::exception() {
            this->withMessage = true;
            this->m_message = "Tried accessing index " + std::to_string(_i) + " out of " + std::to_string(_c) + " memory capacity!";
        }

        StringAccessOutOfBounds() noexcept = default;

        [[nodiscard]] const char * what() const noexcept override {
            return
                (this->withMessage) ?
                (this->m_message.c_str()) :
                ("Tried accessing index out of memory capacity!");
        }
    };

    class String {
    private:
        char* _str {nullptr};
        std::size_t _len {0};
        std::size_t _cap {0};

#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-reserved-identifier"
        constexpr static std::size_t _DEF_CTOR_SIZE = 0U;
        constexpr static std::size_t _DEF_MAX_STR_SIZE = UINT32_MAX;
        [[maybe_unused]] constexpr static std::size_t _DEF_MIN_INDEX = 0U;
#pragma clang diagnostic pop

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedGlobalDeclarationInspection"
        enum [[maybe_unused]] RegexRuleTypeCounter {
            ONLY_ONCE [[maybe_unused]],
            AT_LEAST_ONCE [[maybe_unused]],
            ANY [[maybe_unused]]
        };

        struct [[maybe_unused]] RegexMatchingInterval {
            char  start;
            char finish;

            RegexRuleTypeCounter rule;
        };

        struct [[maybe_unused]] RegexMatchingLiteral {
            char literal[256];
            uint8 literalLength;

            RegexRuleTypeCounter rule;
        };

        struct [[maybe_unused]] RegexMatchingStructure {
            RegexMatchingInterval* intervals;
            RegexMatchingLiteral* literals;
        };
#pragma clang diagnostic pop

        void _alloc(std::size_t) noexcept;
        void _relocateMemory(std::size_t) noexcept;

    public:

        constexpr static std::size_t npos = INT64_MAX;

        String() noexcept;
        String(const String&) noexcept;

        explicit String(std::size_t) noexcept;
        explicit String(const char*, std::size_t = engine::String::_DEF_CTOR_SIZE) noexcept;
        explicit String(const std::string&, std::size_t = engine::String::_DEF_CTOR_SIZE) noexcept;
        explicit String(const String&, std::size_t) noexcept;

        ~String() noexcept;

        explicit operator std::string() const noexcept;

        [[maybe_unused]] void shrink() noexcept;

        [[nodiscard]] std::string printInfo() const noexcept {
            return
                "{ length = " +
                std::to_string(this->_len) +
                ", capacity = " +
                std::to_string(this->_cap) +
                ", data : \"" +
                std::string(this->_str == nullptr ? "" : this->_str) +
                "\" }";
        }

        [[nodiscard]] const char* c_str() const noexcept {
            return this->_str;
        }

        [[maybe_unused]] [[nodiscard]] std::string stdString() const noexcept {
            return std::string(this->_str);
        }

        [[nodiscard]] std::size_t length() const noexcept {
            return this->_len;
        }

        [[nodiscard]] std::size_t capacity() const noexcept {
            return this->_cap;
        }

        static String& reverse(String& str) noexcept {
            return str.reverse();
        }

        [[maybe_unused]] static String getReversed(String& str) noexcept {
            return str.getReversed();
        }

        String& reverse() noexcept;
        [[nodiscard]] String getReversed() const noexcept;

        static String& append(String& str, const String& toAppend) noexcept {
            return str.append(toAppend);
        }

        static String& append(String& str, const std::string& toAppend) noexcept {
            return str.append(toAppend);
        }

        static String& append(String& str, const char* toAppend) noexcept {
            return str.append(toAppend);
        }

        static String& append(String& str, char toAppend) noexcept {
            return str.append(toAppend);
        }

        String& append(const String&) noexcept;
        String& append(const std::string&) noexcept;
        String& append(const char*) noexcept;
        String& append(char) noexcept;

        char operator[] (std::size_t index) const noexcept (false) {
            if( index >= this->_cap )
                throw engine::StringAccessOutOfBounds(index, this->_cap);

            return * (this->_str + index);
        }

        char&   operator[] (std::size_t) noexcept;

        static char get    (const String& obj, std::size_t index) noexcept {
            return obj.get(index);
        }

        [[nodiscard]] char get (std::size_t index) const noexcept (false) {
            if( index >= this->_cap )
                throw engine::StringAccessOutOfBounds(index, this->_cap);

            return * (this->_str + index);
        }

        static String substring(const String& str, std::size_t from, std::size_t to) noexcept {
            return str.substring(from, to);
        }

        [[nodiscard]] String substring (std::size_t, std::size_t) const noexcept (false);

        static engine::Array<engine::String> split(const String& str, char token) noexcept {
            return str.split(token);
        }

        static engine::Array<engine::String> split(const String& str, const char* tokens) noexcept {
            return str.split(tokens);
        }

        static engine::Array<engine::String> split(const String& str, const std::string& tokens) noexcept {
            return str.split(tokens);
        }

        static engine::Array<engine::String> split(const String& str, const String& tokens) noexcept {
            return str.split(tokens);
        }

        void clear() noexcept {
            if(this->_str != nullptr)
                std::memset(this->_str, 0, this->_cap);
            this->_len = 0;
        }

        [[nodiscard]] engine::Array<engine::String> split(char) const noexcept;
        [[nodiscard]] engine::Array<engine::String> split(const char*) const noexcept;
        [[nodiscard]] engine::Array<engine::String> split(const std::string&) const noexcept;
        [[nodiscard]] engine::Array<engine::String> split(const String&) const noexcept;

        static bool match(const String& str, const char* regex) noexcept {
            return str.match(regex);
        }

        static bool match(const String& str, const std::string& regex) noexcept {
            return str.match(regex);
        }

        static bool match(const String& str, const String& regex) noexcept {
            return str.match(regex);
        }


        [[nodiscard]] bool match(const char*) const noexcept;
        [[nodiscard]] bool match(const std::string&) const noexcept;
        [[nodiscard]] bool match(const String&) const noexcept;

        static bool contains(const String& str, char what) noexcept {
            return str.contains(what);
        }

        static bool contains(const String& str, const char* what) noexcept {
            return str.contains(what);
        }

        static bool contains(const String& str, const std::string& what) noexcept {
            return str.contains(what);
        }

        static bool contains(const String& str, const String& what) noexcept {
            return str.contains(what);
        }


        [[nodiscard]] bool contains(char)                const noexcept;
        [[nodiscard]] bool contains(const char*)         const noexcept;
        [[nodiscard]] bool contains(const std::string& str)  const noexcept {
            return this->contains(str.c_str());
        }

        [[nodiscard]] bool contains(const String& str)       const noexcept {
            return this->contains(str.c_str());
        }

        static std::size_t find(const String& str, char what)                noexcept {
            return str.find(what);
        }

        static std::size_t find(const String& str, const char* what)         noexcept {
            return str.find(what);
        }

        static std::size_t find(const String& str, const String& what)       noexcept {
            return str.find(what);
        }

        static std::size_t find(const String& str, const std::string& what)  noexcept {
            return str.find(what);
        }

        [[nodiscard]] std::size_t find(char what)                  const noexcept {
            return this->findFirst(what);
        }

        [[nodiscard]] std::size_t find(const char* what)           const noexcept {
            return this->findFirst(what);
        }

        [[nodiscard]] std::size_t find(const String& what)         const noexcept {
            return this->findFirst(what);
        }

        [[nodiscard]] std::size_t find(const std::string& what)    const noexcept {
            return this->findFirst(what);
        }


        [[maybe_unused]] static std::size_t findFirst(const String& str, char what) noexcept {
            return str.findFirst(what);
        }

        [[maybe_unused]] static std::size_t findFirst(const String& str, const char* what) noexcept {
            return str.findFirst(what);
        }

        [[maybe_unused]] static std::size_t findFirst(const String& str, const String& what) noexcept {
            return str.findFirst(what);
        }

        [[maybe_unused]] static std::size_t findFirst(const String& str, const std::string& what) noexcept {
            return str.findFirst(what);
        }

        [[maybe_unused]] static std::size_t findLast(const String& str, char what)                   noexcept {
            return str.findLast(what);
        }

        [[maybe_unused]] static std::size_t findLast(const String& str, const char* what)            noexcept {
            return str.findLast(what);
        }

        [[maybe_unused]] static std::size_t findLast(const String& str, const std::string& what)     noexcept {
            return str.findLast(what);
        }

        [[maybe_unused]] static std::size_t findLast(const String& str, const String& what)          noexcept {
            return str.findLast(what);
        }


        [[maybe_unused]] static engine::Array<std::size_t> findAll(const String& str, char what)                 noexcept {
            return str.findAll(what);
        }

        [[maybe_unused]] static engine::Array<std::size_t> findAll(const String& str, const char* what)          noexcept {
            return str.findAll(what);
        }

        [[maybe_unused]] static engine::Array<std::size_t> findAll(const String& str, const std::string& what)   noexcept {
            return str.findAll(what);
        }

        [[maybe_unused]] static engine::Array<std::size_t> findAll(const String& str, const String& what)        noexcept {
            return str.findAll(what);
        }


        [[nodiscard]] std::size_t findFirst(char)                 const noexcept;
        [[nodiscard]] std::size_t findFirst(const char*)          const noexcept;
        [[nodiscard]] std::size_t findFirst(const String&)        const noexcept;
        [[nodiscard]] std::size_t findFirst(const std::string&)   const noexcept;

        [[nodiscard]] std::size_t findLast(char)                  const noexcept;
        [[nodiscard]] std::size_t findLast(const char*)           const noexcept;
        [[nodiscard]] std::size_t findLast(const std::string&)    const noexcept;
        [[nodiscard]] std::size_t findLast(const String&)         const noexcept;

        [[nodiscard]] engine::Array<std::size_t> findAll(char)                const noexcept;
        [[nodiscard]] engine::Array<std::size_t> findAll(const char*)         const noexcept;
        [[nodiscard]] engine::Array<std::size_t> findAll(const std::string&)  const noexcept;
        [[nodiscard]] engine::Array<std::size_t> findAll(const String&)       const noexcept;

        static String& replace(String& str, char what, char with) noexcept {
            return str.replace(what, with);
        }

        static String& replace(String& str, char what, const char* with) noexcept {
            return str.replace(what, with);
        }

        static String& replace(String& str, char what, const std::string& with) noexcept {
            return str.replace(what, with);
        }

        static String& replace(String& str, char what, const String& with) noexcept {
            return str.replace(what, with);
        }

        static String& replace(String& str, const char* what, char with) noexcept {
            return str.replace(what, with);
        }

        static String& replace(String& str, const char* what, const char* with) noexcept {
            return str.replace(what, with);
        }

        static String& replace(String& str, const char* what, const std::string& with) noexcept {
            return str.replace(what, with);
        }

        static String& replace(String& str, const char* what, const String& with) noexcept {
            return str.replace(what, with);
        }

        static String& replace(String& str, const std::string& what, char with) noexcept {
            return str.replace(what, with);
        }

        static String& replace(String& str, const std::string& what, const char* with) noexcept {
            return str.replace(what, with);
        }

        static String& replace(String& str, const std::string& what, const std::string& with) noexcept {
            return str.replace(what, with);
        }

        static String& replace(String& str, const std::string& what, const String& with) noexcept {
            return str.replace(what, with);
        }

        static String& replace(String& str, const String& what, char with) noexcept {
            return str.replace(what, with);
        }

        static String& replace(String& str, const String& what, const char* with) noexcept {
            return str.replace(what, with);
        }

        static String& replace(String& str, const String& what, const std::string& with) noexcept {
            return str.replace(what, with);
        }

        static String& replace(String& str, const String& what, const String& with) noexcept {
            return str.replace(what, with);
        }


        String& replace(char, char) noexcept;
        String& replace(char, const char*) noexcept;
        String& replace(char, const std::string&) noexcept;
        String& replace(char, const String&) noexcept;
        String& replace(const char*, char) noexcept;
        String& replace(const char*, const char*) noexcept;
        String& replace(const char*, const std::string&) noexcept;
        String& replace(const char*, const String&) noexcept;
        String& replace(const std::string&, char) noexcept;
        String& replace(const std::string&, const char*) noexcept;
        String& replace(const std::string&, const std::string&) noexcept;
        String& replace(const std::string&, const String&) noexcept;
        String& replace(const String&, char) noexcept;
        String& replace(const String&, const char*) noexcept;
        String& replace(const String&, const std::string&) noexcept;
        String& replace(const String&, const String&) noexcept;

        static String& replace(String& str, std::size_t from, std::size_t to, char with) noexcept {
            return str.replace(from, to, with);
        }

        static String& replace(String& str, std::size_t from, std::size_t to, const char* with) noexcept {
            return str.replace(from, to, with);
        }

        static String& replace(String& str, std::size_t from, std::size_t to, const std::string& with) noexcept {
            return str.replace(from, to, with);
        }

        static String& replace(String& str, std::size_t from, std::size_t to, const String& with) noexcept {
            return str.replace(from, to, with);
        }


        String& replace(std::size_t, std::size_t, char) noexcept (false);
        String& replace(std::size_t, std::size_t, const char*) noexcept (false);
        String& replace(std::size_t, std::size_t, const std::string&) noexcept (false);
        String& replace(std::size_t, std::size_t, const String&) noexcept (false);

        [[maybe_unused]] static String& replaceFirst(String& str, char what, char with) noexcept {
            return str.replaceFirst(what, with);
        }

        [[maybe_unused]] static String& replaceFirst(String& str, char what, const char* with) noexcept {
            return str.replaceFirst(what, with);
        }

        [[maybe_unused]] static String& replaceFirst(String& str, char what, const std::string& with) noexcept {
            return str.replaceFirst(what, with);
        }

        [[maybe_unused]] static String& replaceFirst(String& str, char what, const String& with) noexcept {
            return str.replaceFirst(what, with);
        }

        [[maybe_unused]] static String& replaceFirst(String& str, const char* what, char with) noexcept {
            return str.replaceFirst(what, with);
        }

        [[maybe_unused]] static String& replaceFirst(String& str, const char* what, const char* with) noexcept {
            return str.replaceFirst(what, with);
        }

        [[maybe_unused]] static String& replaceFirst(String& str, const char* what, const std::string& with) noexcept {
            return str.replaceFirst(what, with);
        }

        [[maybe_unused]] static String& replaceFirst(String& str, const char* what, const String& with) noexcept {
            return str.replaceFirst(what, with);
        }

        [[maybe_unused]] static String& replaceFirst(String& str, const std::string& what, char with) noexcept {
            return str.replaceFirst(what, with);
        }

        [[maybe_unused]] static String& replaceFirst(String& str, const std::string& what, const char* with) noexcept {
            return str.replaceFirst(what, with);
        }

        [[maybe_unused]] static String& replaceFirst(String& str, const std::string& what, const std::string& with) noexcept {
            return str.replaceFirst(what, with);
        }

        [[maybe_unused]] static String& replaceFirst(String& str, const std::string& what, const String& with) noexcept {
            return str.replaceFirst(what, with);
        }

        [[maybe_unused]] static String& replaceFirst(String& str, const String& what, char with) noexcept {
            return str.replaceFirst(what, with);
        }

        [[maybe_unused]] static String& replaceFirst(String& str, const String& what, const char* with) noexcept {
            return str.replaceFirst(what, with);
        }

        [[maybe_unused]] static String& replaceFirst(String& str, const String& what, const std::string& with) noexcept {
            return str.replaceFirst(what, with);
        }

        [[maybe_unused]] static String& replaceFirst(String& str, const String& what, const String& with) noexcept {
            return str.replaceFirst(what, with);
        }


        String& replaceFirst(char, char) noexcept;
        String& replaceFirst(char, const char*) noexcept;
        String& replaceFirst(char, const std::string&) noexcept;
        String& replaceFirst(char, const String&) noexcept;
        String& replaceFirst(const char*, char) noexcept;
        String& replaceFirst(const char*, const char*) noexcept;
        String& replaceFirst(const char*, const std::string&) noexcept;
        String& replaceFirst(const char*, const String&) noexcept;
        String& replaceFirst(const std::string&, char) noexcept;
        String& replaceFirst(const std::string&, const char*) noexcept;
        String& replaceFirst(const std::string&, const std::string&) noexcept;
        String& replaceFirst(const std::string&, const String&) noexcept;
        String& replaceFirst(const String&, char) noexcept;
        String& replaceFirst(const String&, const char*) noexcept;
        String& replaceFirst(const String&, const std::string&) noexcept;
        String& replaceFirst(const String&, const String&) noexcept;

        [[maybe_unused]] static String& replaceLast(String& str, char what, char with) noexcept {
            return str.replaceLast(what, with);
        }

        [[maybe_unused]] static String& replaceLast(String& str, char what, const char* with) noexcept {
            return str.replaceLast(what, with);
        }

        [[maybe_unused]] static String& replaceLast(String& str, char what, const std::string& with) noexcept {
            return str.replaceLast(what, with);
        }

        [[maybe_unused]] static String& replaceLast(String& str, char what, const String& with) noexcept {
            return str.replaceLast(what, with);
        }

        [[maybe_unused]] static String& replaceLast(String& str, const char* what, char with) noexcept {
            return str.replaceLast(what, with);
        }

        [[maybe_unused]] static String& replaceLast(String& str, const char* what, const char* with) noexcept {
            return str.replaceLast(what, with);
        }

        [[maybe_unused]] static String& replaceLast(String& str, const char* what, const std::string& with) noexcept {
            return str.replaceLast(what, with);
        }

        [[maybe_unused]] static String& replaceLast(String& str, const char* what, const String& with) noexcept {
            return str.replaceLast(what, with);
        }

        [[maybe_unused]] static String& replaceLast(String& str, const std::string& what, char with) noexcept {
            return str.replaceLast(what, with);
        }

        [[maybe_unused]] static String& replaceLast(String& str, const std::string& what, const char* with) noexcept {
            return str.replaceLast(what, with);
        }

        [[maybe_unused]] static String& replaceLast(String& str, const std::string& what, const std::string& with) noexcept {
            return str.replaceLast(what, with);
        }

        [[maybe_unused]] static String& replaceLast(String& str, const std::string& what, const String& with) noexcept {
            return str.replaceLast(what, with);
        }

        [[maybe_unused]] static String& replaceLast(String& str, const String& what, char with) noexcept {
            return str.replaceLast(what, with);
        }

        [[maybe_unused]] static String& replaceLast(String& str, const String& what, const char* with) noexcept {
            return str.replaceLast(what, with);
        }

        [[maybe_unused]] static String& replaceLast(String& str, const String& what, const std::string& with) noexcept {
            return str.replaceLast(what, with);
        }

        [[maybe_unused]] static String& replaceLast(String& str, const String& what, const String& with) noexcept {
            return str.replaceLast(what, with);
        }


        String& replaceLast(char, char) noexcept;
        String& replaceLast(char, const char*) noexcept;
        String& replaceLast(char, const std::string&) noexcept;
        String& replaceLast(char, const String&) noexcept;
        String& replaceLast(const char*, char) noexcept;
        String& replaceLast(const char*, const char*) noexcept;
        String& replaceLast(const char*, const std::string&) noexcept;
        String& replaceLast(const char*, const String&) noexcept;
        String& replaceLast(const std::string&, char) noexcept;
        String& replaceLast(const std::string&, const char*) noexcept;
        String& replaceLast(const std::string&, const std::string&) noexcept;
        String& replaceLast(const std::string&, const String&) noexcept;
        String& replaceLast(const String&, char) noexcept;
        String& replaceLast(const String&, const char*) noexcept;
        String& replaceLast(const String&, const std::string&) noexcept;
        String& replaceLast(const String&, const String&) noexcept;

        [[maybe_unused]] static String& replaceRegex(String& str, const char* what, char with) noexcept {
            return str.replaceRegex(what, with);
        }

        [[maybe_unused]] static String& replaceRegex(String& str, const std::string& what, char with) noexcept {
            return str.replaceRegex(what, with);
        }

        [[maybe_unused]] static String& replaceRegex(String& str, const String& what, char with) noexcept {
            return str.replaceRegex(what, with);
        }

        [[maybe_unused]] static String& replaceRegex(String& str, const char* what, const char* with) noexcept {
            return str.replaceRegex(what, with);
        }

        [[maybe_unused]] static String& replaceRegex(String& str, const std::string& what, const char* with) noexcept {
            return str.replaceRegex(what, with);
        }

        [[maybe_unused]] static String& replaceRegex(String& str, const String& what, const char* with) noexcept {
            return str.replaceRegex(what, with);
        }

        [[maybe_unused]] static String& replaceRegex(String& str, const char* what, const std::string& with) noexcept {
            return str.replaceRegex(what, with);
        }

        [[maybe_unused]] static String& replaceRegex(String& str, const std::string& what, const std::string& with) noexcept {
            return str.replaceRegex(what, with);
        }

        [[maybe_unused]] static String& replaceRegex(String& str, const String& what, const std::string& with) noexcept {
            return str.replaceRegex(what, with);
        }

        [[maybe_unused]] static String& replaceRegex(String& str, const char* what, const String& with) noexcept {
            return str.replaceRegex(what, with);
        }

        [[maybe_unused]] static String& replaceRegex(String& str, const std::string& what, const String& with) noexcept {
            return str.replaceRegex(what, with);
        }

        [[maybe_unused]] static String& replaceRegex(String& str, const String& what, const String& with) noexcept {
            return str.replaceRegex(what, with);
        }


        String& replaceRegex(const char*, char) noexcept;
        String& replaceRegex(const std::string&, char) noexcept;
        String& replaceRegex(const String&, char) noexcept;
        String& replaceRegex(const char*, const char*) noexcept;
        String& replaceRegex(const std::string&, const char*) noexcept;
        String& replaceRegex(const String&, const char*) noexcept;
        String& replaceRegex(const char*, const std::string&) noexcept;
        String& replaceRegex(const std::string&, const std::string&) noexcept;
        String& replaceRegex(const String&, const std::string&) noexcept;
        String& replaceRegex(const char*, const String&) noexcept;
        String& replaceRegex(const std::string&, const String&) noexcept;
        String& replaceRegex(const String&, const String&) noexcept;

        [[maybe_unused]] static String& replaceAll(String& str, char what, char with) noexcept {
            return engine::String::replace(str, what, with);
        }

        [[maybe_unused]] static String& replaceAll(String& str, char what, const char* with) noexcept {
            return engine::String::replace(str, what, with);
        }

        [[maybe_unused]] static String& replaceAll(String& str, char what, const std::string& with) noexcept {
            return engine::String::replace(str, what, with);
        }

        [[maybe_unused]] static String& replaceAll(String& str, char what, const String& with) noexcept {
            return engine::String::replace(str, what, with);
        }

        [[maybe_unused]] static String& replaceAll(String& str, const char* what, char with) noexcept {
            return engine::String::replace(str, what, with);
        }

        [[maybe_unused]] static String& replaceAll(String& str, const char* what, const char* with) noexcept {
            return engine::String::replace(str, what, with);
        }

        [[maybe_unused]] static String& replaceAll(String& str, const char* what, const std::string& with) noexcept {
            return engine::String::replace(str, what, with);
        }

        [[maybe_unused]] static String& replaceAll(String& str, const char* what, const String& with) noexcept {
            return engine::String::replace(str, what, with);
        }

        [[maybe_unused]] static String& replaceAll(String& str, const std::string& what, char with) noexcept {
            return engine::String::replace(str, what, with);
        }

        [[maybe_unused]] static String& replaceAll(String& str, const std::string& what, const char* with) noexcept {
            return engine::String::replace(str, what, with);
        }

        [[maybe_unused]] static String& replaceAll(String& str, const std::string& what, const std::string& with) noexcept {
            return engine::String::replace(str, what, with);
        }

        [[maybe_unused]] static String& replaceAll(String& str, const std::string& what, const String& with) noexcept {
            return engine::String::replace(str, what, with);
        }

        [[maybe_unused]] static String& replaceAll(String& str, const String& what, char with) noexcept {
            return engine::String::replace(str, what, with);
        }

        [[maybe_unused]] static String& replaceAll(String& str, const String& what, const char* with) noexcept {
            return engine::String::replace(str, what, with);
        }

        [[maybe_unused]] static String& replaceAll(String& str, const String& what, const std::string& with) noexcept {
            return engine::String::replace(str, what, with);
        }

        [[maybe_unused]] static String& replaceAll(String& str, const String& what, const String& with) noexcept {
            return engine::String::replace(str, what, with);
        }

        [[maybe_unused]] String& replaceAll(char what, char with) noexcept {
            return this->replace(what, with);
        }

        [[maybe_unused]] String& replaceAll(char what, const char* with) noexcept {
            return this->replace(what, with);
        }

        [[maybe_unused]] String& replaceAll(char what, const std::string& with) noexcept {
            return this->replace(what, with);
        }

        [[maybe_unused]] String& replaceAll(char what, const String& with) noexcept {
            return this->replace(what, with);
        }

        [[maybe_unused]] String& replaceAll(const char* what, char with) noexcept {
            return this->replace(what, with);
        }

        [[maybe_unused]] String& replaceAll(const char* what, const char* with) noexcept {
            return this->replace(what, with);
        }

        [[maybe_unused]] String& replaceAll(const char* what, const std::string& with) noexcept {
            return this->replace(what, with);
        }

        [[maybe_unused]] String& replaceAll(const char* what, const String& with) noexcept {
            return this->replace(what, with);
        }

        [[maybe_unused]] String& replaceAll(const std::string& what, char with) noexcept {
            return this->replace(what, with);
        }

        [[maybe_unused]] String& replaceAll(const std::string& what, const char* with) noexcept {
            return this->replace(what, with);
        }

        [[maybe_unused]] String& replaceAll(const std::string& what, const std::string& with) noexcept {
            return this->replace(what, with);
        }

        [[maybe_unused]] String& replaceAll(const std::string& what, const String& with) noexcept {
            return this->replace(what, with);
        }

        [[maybe_unused]] String& replaceAll(const String& what, char with) noexcept {
            return this->replace(what, with);
        }

        [[maybe_unused]] String& replaceAll(const String& what, const char* with) noexcept {
            return this->replace(what, with);
        }

        [[maybe_unused]] String& replaceAll(const String& what, const std::string& with) noexcept {
            return this->replace(what, with);
        }

        [[maybe_unused]] String& replaceAll(const String& what, const String& with) noexcept {
            return this->replace(what, with);
        }


        static bool getline(std::istream&, String&) noexcept(false);
        static bool get(std::istream&, String&) noexcept(false);

        [[maybe_unused]] static String& trim(String& str, char what = ' ')            noexcept {
            return str.trim(what);
        }

        [[maybe_unused]] static String& trim(String& str, const char* what)           noexcept {
            return str.trim(what);
        }

        [[maybe_unused]] static String& trim(String& str, const std::string& what)    noexcept {
            return str.trim(what);
        }

        [[maybe_unused]] static String& trim(String& str, const String& what)         noexcept {
            return str.trim(what);
        }

        [[maybe_unused]] static String& rtrim(String& str, char what = ' ')           noexcept {
            return str.rtrim(what);
        }

        [[maybe_unused]] static String& rtrim(String& str, const char* what)          noexcept {
            return str.rtrim(what);
        }

        [[maybe_unused]] static String& rtrim(String& str, const std::string& what)   noexcept {
            return str.rtrim(what);
        }

        [[maybe_unused]] static String& rtrim(String& str, const String& what)        noexcept {
            return str.rtrim(what);
        }

        [[maybe_unused]] static String& ltrim(String& str, char what = ' ')           noexcept {
            return str.ltrim(what);
        }

        [[maybe_unused]] static String& ltrim(String& str, const char* what)          noexcept {
            return str.ltrim(what);
        }

        [[maybe_unused]] static String& ltrim(String& str, const std::string& what)   noexcept {
            return str.ltrim(what);
        }

        [[maybe_unused]] static String& ltrim(String& str, const String& what)        noexcept {
            return str.ltrim(what);
        }

        [[maybe_unused]] static String& rightTrim(String& str, char what = ' ')           noexcept {
            return engine::String::rtrim(str, what);
        }

        [[maybe_unused]] static String& rightTrim(String& str, const char* what)          noexcept {
            return engine::String::rtrim(str, what);
        }

        [[maybe_unused]] static String& rightTrim(String& str, const std::string& what)   noexcept {
            return engine::String::rtrim(str, what);
        }

        [[maybe_unused]] static String& rightTrim(String& str, const String& what)        noexcept {
            return engine::String::rtrim(str, what);
        }

        [[maybe_unused]] static String& leftTrim(String& str, char what = ' ')            noexcept {
            return engine::String::ltrim(str, what);
        }

        [[maybe_unused]] static String& leftTrim(String& str, const char* what)           noexcept {
            return engine::String::ltrim(str, what);
        }

        [[maybe_unused]] static String& leftTrim(String& str, const std::string& what)    noexcept {
            return engine::String::ltrim(str, what);
        }

        [[maybe_unused]] static String& leftTrim(String& str, const String& what)         noexcept {
            return engine::String::ltrim(str, what);
        }

        String& trim(char = ' ')            noexcept;
        String& trim(const char*)           noexcept;
        String& trim(const std::string&)    noexcept;
        String& trim(const String&)         noexcept;
        String& rtrim(char = ' ')           noexcept;
        String& rtrim(const char*)          noexcept;
        String& rtrim(const std::string&)   noexcept;
        String& rtrim(const String&)        noexcept;
        String& ltrim(char = ' ')           noexcept;
        String& ltrim(const char*)          noexcept;
        String& ltrim(const std::string&)   noexcept;
        String& ltrim(const String&)        noexcept;

        [[maybe_unused]] String& rightTrim(char what = ' ')          noexcept {
            return this->rtrim(what);
        }

        [[maybe_unused]] String& rightTrim(const char* what)         noexcept {
            return this->rtrim(what);
        }

        [[maybe_unused]] String& rightTrim(const std::string& what)  noexcept {
            return this->rtrim(what);
        }

        [[maybe_unused]] String& rightTrim(const String& what)       noexcept {
            return this->rtrim(what);
        }

        [[maybe_unused]] String& leftTrim(char what = ' ')           noexcept {
            return this->ltrim(what);
        }

        [[maybe_unused]] String& leftTrim(const char* what)          noexcept {
            return this->ltrim(what);
        }

        [[maybe_unused]] String& leftTrim(const std::string& what)   noexcept {
            return this->ltrim(what);
        }

        [[maybe_unused]] String& leftTrim(const String& what)        noexcept {
            return this->ltrim(what);
        }

        [[maybe_unused]] static String& capitalize(String& str) noexcept {
            return str.capitalize();
        }

        [[maybe_unused]] static String& toLower(String& str) noexcept {
            return str.toLower();
        }

        [[maybe_unused]] static String& toUpper(String& str) noexcept {
            return str.toUpper();
        }

        [[maybe_unused]] static String& revertLetterCase(String& str) noexcept {
            return str.revertLetterCase();
        }

        [[maybe_unused]] static bool isWord(String& str) noexcept {
            return str.isWord();
        }

        [[maybe_unused]] static bool isSentence(String& str) noexcept {
            return str.isSentence();
        }

        String& capitalize() noexcept;
        String& toLower() noexcept;
        String& toUpper() noexcept;
        String& revertLetterCase() noexcept;

        [[nodiscard]] bool isWord() const noexcept;
        [[nodiscard]] bool isSentence() const noexcept;

        String& operator = (char) noexcept;
        String& operator = (const char *) noexcept;
        String& operator = (const String&) noexcept;
        String& operator = (const std::string&) noexcept;

        String& operator+= (char) noexcept;
        String& operator+= (const char *) noexcept;
        String& operator+= (const String&) noexcept;
        String& operator+= (const std::string&) noexcept;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"
        friend bool             ( ::operator == ) (const engine::String&, const engine::String&)    noexcept;
        friend bool             ( ::operator == ) (const engine::String&, const std::string&)       noexcept;
        friend bool             ( ::operator == ) (const std::string&, const engine::String&)       noexcept;
        friend bool             ( ::operator == ) (const engine::String&, const char*)              noexcept;
        friend bool             ( ::operator == ) (const char*, const engine::String&)              noexcept;

        friend bool             ( ::operator != ) (const engine::String&, const engine::String&)    noexcept;
        friend bool             ( ::operator != ) (const engine::String&, const std::string&)       noexcept;
        friend bool             ( ::operator != ) (const std::string&, const engine::String&)       noexcept;
        friend bool             ( ::operator != ) (const engine::String&, const char*)              noexcept;
        friend bool             ( ::operator != ) (const char*, const engine::String&)              noexcept;

        friend bool             ( ::operator < ) (const engine::String&, const engine::String&)     noexcept;
        friend bool             ( ::operator < ) (const engine::String&, const std::string&)        noexcept;
        friend bool             ( ::operator < ) (const std::string&, const engine::String&)        noexcept;
        friend bool             ( ::operator < ) (const engine::String&, const char*)               noexcept;
        friend bool             ( ::operator < ) (const char*, const engine::String&)               noexcept;

        friend bool             ( ::operator > ) (const engine::String&, const engine::String&)     noexcept;
        friend bool             ( ::operator > ) (const engine::String&, const std::string&)        noexcept;
        friend bool             ( ::operator > ) (const std::string&, const engine::String&)        noexcept;
        friend bool             ( ::operator > ) (const engine::String&, const char*)               noexcept;
        friend bool             ( ::operator > ) (const char*, const engine::String&)               noexcept;

        friend bool             ( ::operator <= ) (const engine::String&, const engine::String&)    noexcept;
        friend bool             ( ::operator <= ) (const engine::String&, const std::string&)       noexcept;
        friend bool             ( ::operator <= ) (const std::string&, const engine::String&)       noexcept;
        friend bool             ( ::operator <= ) (const engine::String&, const char*)              noexcept;
        friend bool             ( ::operator <= ) (const char*, const engine::String&)              noexcept;

        friend bool             ( ::operator >= ) (const engine::String&, const engine::String&)    noexcept;
        friend bool             ( ::operator >= ) (const engine::String&, const std::string&)       noexcept;
        friend bool             ( ::operator >= ) (const std::string&, const engine::String&)       noexcept;
        friend bool             ( ::operator >= ) (const engine::String&, const char*)              noexcept;
        friend bool             ( ::operator >= ) (const char*, const engine::String&)              noexcept;

        friend engine::String   ( ::operator+ ) (const engine::String&, const engine::String&)      noexcept;
        friend engine::String   ( ::operator+ ) (const engine::String&, const std::string&)         noexcept;
        friend engine::String   ( ::operator+ ) (const std::string&, const engine::String&)         noexcept;
        friend engine::String   ( ::operator+ ) (const engine::String&, const char*)                noexcept;
        friend engine::String   ( ::operator+ ) (const char*, const engine::String&)                noexcept;
        friend engine::String   ( ::operator+ ) (char, const engine::String&)                       noexcept;
        friend engine::String   ( ::operator+ ) (const engine::String&, char)                       noexcept;

        friend std::istream& ( ::operator >> ) (std::istream&, String&) noexcept (false);
        friend std::ostream& ( ::operator << ) (std::ostream&, const String&) noexcept (false);
#pragma clang diagnostic pop

    };

}

#endif //ENG1_STRING_H

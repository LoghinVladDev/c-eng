//
// Created by loghin on 7/20/20.
//

#include "String.h"
#include <regex>

static inline std::size_t lengthCStr(const char* str) noexcept {
    std::size_t len = 0U;
    while(str[len++]);

    return len - 1;
}

void engine::String::_alloc(std::size_t reqSize) noexcept {
    if(reqSize + this->_len > 0 || this->_cap > 0)
        if(reqSize + this->_len <= this->_cap)
            return;

    std::size_t newSize = ( this->_len + reqSize > 2U * this->_cap ) ? ( this->_len + reqSize ) : ( 2U * this->_cap );

    if( newSize > engine::String::_DEF_MAX_STR_SIZE )
        newSize = engine::String::_DEF_MAX_STR_SIZE;

    this->_relocateMemory(newSize);
}

void engine::String::_relocateMemory(std::size_t blockSize) noexcept {
//    char* newMemLoc = new char [blockSize + 1U];
    char* newMemLoc = (char*)std::malloc((blockSize + 1U) * sizeof(char) );

    memset(newMemLoc, 0, blockSize + 1U);
    if(this->_str != nullptr)
        std::memcpy(newMemLoc, this->_str, this->_len + 1);

//    delete[] this->_str;
    std::free(this->_str);

    this->_str = newMemLoc;
    this->_cap = blockSize;
}

[[maybe_unused]] void engine::String::shrink() noexcept {
    this->_alloc(this->_len);
}

engine::String::String() noexcept : _len(0), _cap(0), _str(nullptr) {
    this->_alloc(0);
}

engine::String::String(const String& obj) noexcept {
    this->_alloc(obj._len);

    if(this->_str != nullptr)
        memcpy(this->_str, obj._str, obj._len + 1);
        // was memcpy(this->_str, obj._str, obj._cap). Caused heap pollution
    this->_len = obj._len;
}

engine::String::String(std::size_t len) noexcept {
    this->_alloc(len);
}

engine::String::String(const char* str, std::size_t len) noexcept {
    if(len == engine::String::_DEF_CTOR_SIZE)
        len = lengthCStr(str);

    this->_alloc(len);
    if(this->_str != nullptr)
        memcpy(this->_str, str, len + 1);
    this->_len = len;
}

engine::String::String(const std::string& str, std::size_t len) noexcept {
    if(len == engine::String::_DEF_CTOR_SIZE)
        len = str.length();

    this->_alloc(len);
    memcpy(this->_str, str.c_str(), len + 1);
    this->_len = len;
}

engine::String::String(const String& str, std::size_t len) noexcept {
    this->_alloc(len);
    memcpy(this->_str, str._str, len + 1);
    this->_len = len;
}

engine::String::~String() noexcept {
//    delete [] (this->_str);
//    this->_str = nullptr;
    std::free(this->_str);
}

engine::String::operator std::string() const noexcept {
    return std::string(this->_str == nullptr ? "null_string" : this->_str);
}

std::ostream& operator << (std::ostream& stream, const engine::String& string) noexcept (false) {
    return (stream << (string._str == nullptr ? "null_string" : string._str ));
}

engine::String& engine::String::append(const char* obj) noexcept {
    std::size_t len = lengthCStr(obj);
    this->_alloc(len);

    memcpy(this->_str + this->_len, obj, len + 1);
    this->_len += len;

    return *this;
}

engine::String& engine::String::append(const engine::String& obj) noexcept {
    this->_alloc(obj._len);

//    for(std::size_t iter = 0U; iter < obj._len; iter ++)
//        this->_str[this->_len + iter] = obj._str[iter];
//    this->_str[this->_len] = 0;

    if(this->_str != nullptr)
        memcpy(this->_str + this->_len, obj._str == nullptr ? "" : obj._str, obj._len + 1);
    this->_len += obj._len;

    return *this;
}

engine::String& engine::String::append(const std::string& obj) noexcept {
    this->_alloc(obj.length());

    memcpy(this->_str + this->_len, obj.c_str(), obj.length() + 1);
    this->_len += obj.length();

    return * this;
}

engine::String& engine::String::append(char obj) noexcept {
    this->_alloc(1);

    this->_str[this->_len++] = obj;
    this->_str[this->_len] = 0;

    return *this;
}

char& engine::String::operator[] (std::size_t index) noexcept {
    if( index >= this->_cap )
        this->_alloc(index - this->_cap + 1);

    if( index >= this->_len )
        this->_len = index + 1U;

    return * ( this->_str + index );
}

[[nodiscard]] engine::String engine::String::substring(std::size_t from, std::size_t to) const noexcept (false) {
//    if(to >= this->_cap ||
//    from < engine::String::_DEF_MIN_INDEX ||
//    (from > engine::String::_DEF_MAX_STR_SIZE || to > engine::String::_DEF_MAX_STR_SIZE)
//    )
    if(to > this->_cap)
        throw engine::StringAccessOutOfBounds(to, this->_cap);
    if(from > this->_cap)
        throw engine::StringAccessOutOfBounds(from, this->_cap);
    if(from > to) {
        return engine::String("");
    }


    String res;

    for(std::size_t iter = from; iter < to; iter++)
        res += this->_str[iter];

    return res;
}

engine::String& engine::String::operator+= (char c) noexcept {
    this->_alloc(1U);

    this->_str[this->_len++] = c;
    this->_str[this->_len] = 0;
    return *this;
}

engine::String& engine::String::operator+= (const char* str) noexcept {
    std::size_t len = lengthCStr(str);
    this->_alloc(len);

//    for(std::size_t it = 0; it < len; it++)
//        this->_str[this->_len++] = str[it];
//    this->_str[this->_len] = 0;

    std::memcpy(this->_str + this->_len, str, len + 1);
    this->_len += len;

    return *this;
}

engine::String& engine::String::operator+= (const std::string& str) noexcept {
//    return this->operator+= (str.c_str()); extra O(n) not req
    this->_alloc(str.length());

    std::memcpy(this->_str + this->_len, str.c_str(), str.length() + 1);
    this->_len += str.length();

    return *this;
}

engine::String& engine::String::operator+= (const engine::String& str) noexcept {
//    return this->operator+= (str.c_str()); extra O(n) not req, length encapsulated
    this->_alloc(str._len);

    std::memcpy(this->_str + this->_len, str._str == nullptr ? "" : str._str, str._len + 1);
    this->_len += str._len;

    return *this;
}

engine::String& engine::String::reverse() noexcept {
    char aux;
    for(std::size_t it = 0U, halfLen = this->_len / 2U; it < halfLen; it++){
        aux = this->_str[it];
        this->_str[it] = this->_str[this->_len - it - 1U];
        this->_str[this->_len - it - 1] = aux;
    }
    return *this;
}

[[nodiscard]] engine::String engine::String::getReversed() const noexcept {
    String res(this->_len);

    for(std::size_t it = 0U; it < this->_len; it++)
        res._str[it] = this->_str[this->_len - it - 1U];
    res._str[this->_len + 1U] = 0;
    res._len = this->_len;

    return res;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-convert-member-functions-to-static"
#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedLocalVariable"
// [A-Za-z0-9]* maybe some day
bool engine::String::match(const char* regex) const noexcept {
    return false;
}

//maybe some day
bool engine::String::match(const std::string& regex) const noexcept {
    return false;
}

//maybe some day
bool engine::String::match(const engine::String& regex) const noexcept {
    return false;
}
#pragma clang diagnostic pop
#pragma clang diagnostic pop

engine::String& engine::String::operator= (const char* str) noexcept {
    std::size_t len = lengthCStr(str);
//    if(len > 0)  c++ allows alloc of arr[0], must be deleted ( will happen at alloc )
//    arr* contains * (size_t) to start of arr, even if it is empty
    this->clear();
    this->_alloc(len);

    std::memcpy(this->_str, str, len + 1);
    this->_len = len;

    return *this;
}

engine::String& engine::String::operator= (const engine::String& str) noexcept {
    if( this == &str )
        return *this;

    this->clear();
    this->_alloc(str._len);

    if(this->_str != nullptr)
        std::memcpy(this->_str, str._str,str._len + 1);
    this->_len = str._len;

    return *this;
}

engine::String& engine::String::operator= (char character) noexcept {
    this->clear();
    this->_alloc(1);

    this->_str[this->_len++] = character;
    this->_str[this->_len] = 0;

    return *this;
}

engine::String& engine::String::operator= (const std::string& str) noexcept {
    this->clear();
    this->_alloc(str.length());

    std::memcpy(this->_str, str.c_str(), str.length() + 1);
    this->_len = str.length();

    return *this;
}

engine::Array<engine::String> engine::String::split(char token) const noexcept {
    engine::Array<engine::String> res;
    engine::String innerString;

    bool firstAppearance = true;

    for(std::size_t it = 0; it < this->_len; it++){
        if(this->_str[it] == token) {
            if( !firstAppearance && innerString.length() > 0 )
                res += innerString;
            innerString.clear();
        } else {
            firstAppearance = false;
            innerString += this->_str[it];
        }
    }

    if( !firstAppearance && innerString.length() > 0 )
        res += innerString;

    return res;
}

engine::Array<engine::String> engine::String::split(const String& tokens) const noexcept {
    engine::Array<engine::String> res;
    engine::String innerString;

    bool firstAppearance = true;

    for(std::size_t it = 0; it < this->_len; it++){
        if(tokens.contains(this->_str[it])) {
            if( !firstAppearance && innerString.length() > 0 )
                res += innerString;
            innerString.clear();
        } else {
            firstAppearance = false;
            innerString += this->_str[it];
        }
    }

    if( !firstAppearance && innerString.length() > 0 )
        res += innerString;

    return res;
}

engine::Array<engine::String> engine::String::split(const std::string& tokens) const noexcept {
    return this->split(engine::String(tokens));
}

engine::Array<engine::String> engine::String::split(const char* tokens) const noexcept {
    return this->split(engine::String(tokens));
}

bool engine::String::contains(char what) const noexcept {
    for(std::size_t it = 0U; it < this->_len; it++)
        if(this->_str[it] == what)
            return true;
    return false;
}

static void computeLongestPrefixSuffix(const int8* pattern, int32 n, int32* LPS) noexcept {
    int32 len = 0;
    LPS[0] = 0;

    int32 i = 1;
    while(i < n) {
        if(pattern[i] == pattern[len]) {
            len++;
            LPS[i++] = len;
        } else {
            if( len != 0 )
                len = LPS[len - 1];
            else
                LPS[i++] = 0;
        }
    }
}

bool engine::String::contains(const char* what) const noexcept {
    std::size_t m = lengthCStr(what);
    std::size_t n = this->_len;

    int32 LPS[m];

    computeLongestPrefixSuffix(what, m, LPS);

    int32 i = 0;
    int32 j = 0;
    while( i < n ) {
        if(what[j] == this->_str[i]) {
            i++; j++;
        }
        if(j == m) {
            return true;
        } else if( i < n && what[j] != this->_str[i] ) {
            if(j != 0)
                j = LPS[j-1];
            else
                i++;
        }
    }
    return false;
}

std::size_t engine::String::findFirst(char character) const noexcept {
    for(std::size_t it = 0; it < this->_len; it++)
        if(this->_str[it] == character)
            return it;
    return engine::String::npos;
}

std::size_t engine::String::findFirst(const char* what) const noexcept {
    std::size_t m = lengthCStr(what);
    std::size_t n = this->_len;

    int32 LPS[m];

    computeLongestPrefixSuffix(what, m, LPS);

    int32 i = 0;
    int32 j = 0;
    while( i < n ) {
        if(what[j] == this->_str[i]) {
            i++; j++;
        }
        if(j == m) {
            return i - j;
        } else if( i < n && what[j] != this->_str[i] ) {
            if(j != 0)
                j = LPS[j-1];
            else
                i++;
        }
    }
    return engine::String::npos;
}

std::size_t engine::String::findFirst(const String & what) const noexcept {
    return this->findFirst(what.c_str());
}

std::size_t engine::String::findFirst(const std::string & what) const noexcept {
    return this->findFirst(what.c_str());
}

engine::Array<std::size_t> engine::String::findAll(char character) const noexcept {
    engine::Array<std::size_t> res;

    for(std::size_t it = 0; it < this->_len; it++)
        if(this->_str[it] == character)
            res += it;

    return res;
}

engine::Array<std::size_t> engine::String::findAll(const char* what) const noexcept {
    std::size_t m = lengthCStr(what);
    std::size_t n = this->_len;

    engine::Array<std::size_t> res;

    int32 LPS[m];

    computeLongestPrefixSuffix(what, m, LPS);

    int32 i = 0;
    int32 j = 0;
    while( i < n ) {
        if(what[j] == this->_str[i]) {
            i++; j++;
        }
        if(j == m) {
            res += (i - j);
            j = LPS[j - 1];
        } else if( i < n && what[j] != this->_str[i] ) {
            if(j != 0)
                j = LPS[j-1];
            else
                i++;
        }
    }
    return res;
}

engine::Array<std::size_t> engine::String::findAll(const std::string& what) const noexcept {
    return this->findAll(what.c_str());
}

engine::Array<std::size_t> engine::String::findAll(const engine::String& what) const noexcept {
    return this->findAll(what.c_str());
}

std::size_t engine::String::findLast(char character) const noexcept {
    auto occurrences = this->findAll(character);

    if(occurrences.getLength() == 0)
        return engine::String::npos;

    return occurrences[occurrences.getLength() - 1];
}

std::size_t engine::String::findLast(const char* what) const noexcept {
    auto occurrences = this->findAll(what);

    if(occurrences.getLength() == 0)
        return engine::String::npos;

    return occurrences[occurrences.getLength() - 1];
}

std::size_t engine::String::findLast(const std::string& what) const noexcept {
    auto occurrences = this->findAll(what);

    if(occurrences.getLength() == 0)
        return engine::String::npos;

    return occurrences[occurrences.getLength() - 1];
}

std::size_t engine::String::findLast(const engine::String& what) const noexcept {
    auto occurrences = this->findAll(what);

    if(occurrences.getLength() == 0)
        return engine::String::npos;

    return occurrences[occurrences.getLength() - 1];
}

engine::String& engine::String::replace(char what, char with) noexcept {
    for(std::size_t it = 0; it < this->_len; it++)
        if(this->_str[it] == what)
            this->_str[it] = with;

    return *this;
}

engine::String& engine::String::replace(char what, const char* with) noexcept {
    String copy(*this);
    this->clear();

    for(std::size_t it = 0; it < copy._len; it++){
        if(copy._str[it] == what)
            (*this) += with;
        else
            (*this) += copy._str[it];
    }
    this->_str[this->_len] = 0;

    return *this;
}

engine::String& engine::String::replace(char what, const std::string& with) noexcept {
    return this->replace(what, with.c_str());
}

engine::String& engine::String::replace(char what, const engine::String& with) noexcept {
    return this->replace(what, with.c_str());
}

engine::String& engine::String::replace(const char* what, const char* with) noexcept {
    engine::Array<std::size_t> replaceSegmentsPositions = this->findAll(what);

    if(replaceSegmentsPositions.getLength() == 0)
        return *this;

    String copy(*this);
    this->clear();

    std::size_t segmentIndex = 0;
    std::size_t lengthOfSegment = lengthCStr(what);

    for(std::size_t it = 0; it < copy._len; it++) {
        if( it != replaceSegmentsPositions[segmentIndex] ) {
            (*this) += copy._str[it];
        } else {
            (*this) += with;
            it += lengthOfSegment - 1;
            segmentIndex++;
        }
    }

    return *this;
}

engine::String& engine::String::replace(const char* what, char with) noexcept {
    engine::Array<std::size_t> replaceSegmentsPositions = this->findAll(what);

    if(replaceSegmentsPositions.getLength() == 0)
        return *this;

    String copy(*this);
    this->clear();

    std::size_t segmentIndex = 0;
    std::size_t lengthOfSegment = 1;

    for(std::size_t it = 0; it < copy._len; it++) {
        if( it != replaceSegmentsPositions[segmentIndex] ) {
            (*this) += copy._str[it];
        } else {
            (*this) += with;
            it += lengthOfSegment - 1;
            segmentIndex++;
        }
    }

    return *this;
}

engine::String& engine::String::replace(const char* what, const std::string& with) noexcept {
    return this->replace(what, with.c_str());
}

engine::String& engine::String::replace(const char* what, const engine::String& with) noexcept {
    return this->replace(what, with.c_str());
}

engine::String& engine::String::replace(const std::string& what, char with) noexcept {
    return this->replace(what.c_str(), with);
}

engine::String& engine::String::replace(const std::string& what, const char* with) noexcept {
    return this->replace(what.c_str(), with);
}

engine::String& engine::String::replace(const std::string& what, const std::string& with) noexcept {
    return this->replace(what.c_str(), with.c_str());
}

engine::String& engine::String::replace(const std::string& what, const engine::String& with) noexcept {
    return this->replace(what.c_str(), with.c_str());
}

engine::String& engine::String::replace(const engine::String& what, char with) noexcept {
    return this->replace(what.c_str(), with);
}

engine::String& engine::String::replace(const engine::String& what, const char* with) noexcept {
    return this->replace(what.c_str(), with);
}

engine::String& engine::String::replace(const engine::String& what, const std::string& with) noexcept {
    return this->replace(what.c_str(), with.c_str());
}

engine::String& engine::String::replace(const engine::String& what, const engine::String& with) noexcept {
    return this->replace(what.c_str(), with.c_str());
}

engine::String& engine::String::replace(std::size_t from, std::size_t to, char what) noexcept (false) {
    if(to > this->_cap)
        throw engine::StringAccessOutOfBounds(to, this->_cap);
    if(from > this->_cap)
        throw engine::StringAccessOutOfBounds(from, this->_cap);

    engine::String left = this->substring(0, from);
    engine::String right = this->substring(to, this->_len);
    return (*this = left.append(what).append(right));
}

engine::String& engine::String::replace(std::size_t from, std::size_t to, const char* what) noexcept (false) {
    return this->replace(from, to, engine::String(what));
}

engine::String& engine::String::replace(std::size_t from, std::size_t to, const std::string& what) noexcept (false) {
    return this->replace(from, to, engine::String(what));
}

engine::String& engine::String::replace(std::size_t from, std::size_t to, const engine::String& what) noexcept (false) {
    if(to > this->_cap)
        throw engine::StringAccessOutOfBounds(to, this->_cap);
    if(from > this->_cap)
        throw engine::StringAccessOutOfBounds(from, this->_cap);

    engine::String left = this->substring(0, from);
    engine::String right = this->substring(to, this->_len);
    return (*this = left.append(what).append(right));
}

engine::String& engine::String::replaceFirst(char what, char with) noexcept {
    for(std::size_t it = 0; it < this->_len; it++)
        if(this->_str[it] == what) {
            this->_str[it] = with;
            break;
        }
    return *this;
}

engine::String& engine::String::replaceFirst(char what, const char* with) noexcept {
    String copy(*this);
    this->clear();

    bool replacedFirst = false;

    for(std::size_t it = 0; it < copy._len; it++){
        if(copy._str[it] == what && !replacedFirst) {
            (*this) += with;
            replacedFirst = true;
        }
        else
            (*this) += copy._str[it];
    }
    this->_str[this->_len] = 0;

    return *this;
}

engine::String& engine::String::replaceFirst(char what, const std::string& with) noexcept {
    return this->replaceFirst(what, with.c_str());
}

engine::String& engine::String::replaceFirst(char what, const engine::String& with) noexcept {
    return this->replaceFirst(what, with.c_str());
}

engine::String& engine::String::replaceFirst(const char* what, char with) noexcept {
    engine::Array<std::size_t> replaceSegmentsPositions = this->findAll(what);

    if(replaceSegmentsPositions.getLength() == 0)
        return *this;

    bool replacedFirst = false;
    String copy(*this);
    this->clear();

    std::size_t segmentIndex = 0;
    std::size_t lengthOfSegment = 1;

    for(std::size_t it = 0; it < copy._len; it++) {
        if( it != replaceSegmentsPositions[segmentIndex] || replacedFirst ) {
            (*this) += copy._str[it];
        } else {
            (*this) += with;
            it += lengthOfSegment - 1;
            segmentIndex++;
            replacedFirst = true;
        }
    }

    return *this;
}

engine::String& engine::String::replaceFirst(const char* what, const char* with) noexcept {
    engine::Array<std::size_t> replaceSegmentsPositions = this->findAll(what);

    if(replaceSegmentsPositions.getLength() == 0)
        return *this;

    bool replacedFirst = false;
    String copy(*this);
    this->clear();

    std::size_t segmentIndex = 0;
    std::size_t lengthOfSegment = lengthCStr(what);

    for(std::size_t it = 0; it < copy._len; it++) {
        if( it != replaceSegmentsPositions[segmentIndex] || replacedFirst ) {
            (*this) += copy._str[it];
        } else {
            (*this) += with;
            it += lengthOfSegment - 1;
            segmentIndex++;
            replacedFirst = true;
        }
    }

    return *this;
}

engine::String& engine::String::replaceFirst(const char* what, const std::string& with) noexcept {
    return this->replaceFirst(what, with.c_str());
}

engine::String& engine::String::replaceFirst(const char* what, const engine::String& with) noexcept {
    return this->replaceFirst(what, with.c_str());
}

engine::String& engine::String::replaceFirst(const std::string& what, char with) noexcept {
    return this->replaceFirst(what.c_str(), with);
}

engine::String& engine::String::replaceFirst(const std::string& what, const char* with) noexcept {
    return this->replaceFirst(what.c_str(), with);
}

engine::String& engine::String::replaceFirst(const std::string& what, const std::string& with) noexcept {
    return this->replaceFirst(what.c_str(), with.c_str());
}

engine::String& engine::String::replaceFirst(const std::string& what, const engine::String& with) noexcept {
    return this->replaceFirst(what.c_str(), with.c_str());
}

engine::String& engine::String::replaceFirst(const engine::String& what, char with) noexcept {
    return this->replaceFirst(what.c_str(), with);
}

engine::String& engine::String::replaceFirst(const engine::String& what, const char* with) noexcept {
    return this->replaceFirst(what.c_str(), with);
}

engine::String& engine::String::replaceFirst(const engine::String& what, const std::string& with) noexcept {
    return this->replaceFirst(what.c_str(), with.c_str());
}

engine::String& engine::String::replaceFirst(const engine::String& what, const engine::String& with) noexcept {
    return this->replaceFirst(what.c_str(), with.c_str());
}

engine::String& engine::String::replaceLast(char what, char with) noexcept {
    for(std::size_t it = this->_len - 1; it >= 0; it--)
        if(this->_str[it] == what) {
            this->_str[it] = with;
            break;
        }

    return *this;
}

engine::String& engine::String::replaceLast(char what, const char* with) noexcept {
    for(std::size_t it = this->_len - 1; it >= 0; it--)
        if(this->_str[it] == what){
            engine::String left = this->substring(0, it);
            engine::String right = this->substring(it + 1, this->_len);
            (*this) = left.append(with).append(right);
            break;
        }

    return *this;
}

engine::String& engine::String::replaceLast(char what, const std::string& with) noexcept {
    return this->replaceLast(what, with.c_str());
}

engine::String& engine::String::replaceLast(char what, const engine::String& with) noexcept {
    return this->replaceLast(what, with.c_str());
}

engine::String& engine::String::replaceLast(const char* what, char with) noexcept {
    engine::Array<std::size_t> replaceSegmentsPositions = this->findAll(what);

    if(replaceSegmentsPositions.getLength() == 0)
        return *this;

    std::size_t startPos = replaceSegmentsPositions[replaceSegmentsPositions.getLength() - 1];
    std::size_t lengthOfSegment = lengthCStr(what);

    engine::String left = this->substring(0, startPos);
    engine::String right = this->substring(startPos + lengthOfSegment, this->_len);

    return ((*this) = left.append(with).append(right));
}

engine::String& engine::String::replaceLast(const char* what, const char* with) noexcept {
    engine::Array<std::size_t> replaceSegmentsPositions = this->findAll(what);

    if(replaceSegmentsPositions.getLength() == 0)
        return *this;

    std::size_t startPos = replaceSegmentsPositions[replaceSegmentsPositions.getLength() - 1];
    std::size_t lengthOfSegment = lengthCStr(what);

    engine::String left = this->substring(0, startPos);
    engine::String right = this->substring(startPos + lengthOfSegment, this->_len);

    return ((*this) = left.append(with).append(right));
}

engine::String& engine::String::replaceLast(const char* what, const std::string& with) noexcept {
    return this->replaceLast(what, with.c_str());
}

engine::String& engine::String::replaceLast(const char* what, const engine::String& with) noexcept {
    return this->replaceLast(what, with.c_str());
}

engine::String& engine::String::replaceLast(const std::string& what, char with) noexcept {
    return this->replaceLast(what.c_str(), with);
}

engine::String& engine::String::replaceLast(const std::string& what, const char* with) noexcept {
    return this->replaceLast(what.c_str(), with);
}

engine::String& engine::String::replaceLast(const std::string& what, const std::string& with) noexcept {
    return this->replaceLast(what.c_str(), with.c_str());
}

engine::String& engine::String::replaceLast(const std::string& what, const engine::String& with) noexcept {
    return this->replaceLast(what.c_str(), with.c_str());
}

engine::String& engine::String::replaceLast(const engine::String& what, char with) noexcept {
    return this->replaceLast(what.c_str(), with);
}

engine::String& engine::String::replaceLast(const engine::String& what, const char* with) noexcept {
    return this->replaceLast(what.c_str(), with);
}

engine::String& engine::String::replaceLast(const engine::String& what, const std::string& with) noexcept {
    return this->replaceLast(what.c_str(), with.c_str());
}

engine::String& engine::String::replaceLast(const engine::String& what, const engine::String& with) noexcept {
    return this->replaceLast(what.c_str(), with.c_str());
}

//// #def TODO : after implementation of regex.
engine::String& engine::String::replaceRegex(const char*, char) noexcept { return *this; }
engine::String& engine::String::replaceRegex(const std::string&, char) noexcept { return *this; }
engine::String& engine::String::replaceRegex(const String&, char) noexcept { return *this; }
engine::String& engine::String::replaceRegex(const char*, const char*) noexcept { return *this; }
engine::String& engine::String::replaceRegex(const std::string&, const char*) noexcept { return *this; }
engine::String& engine::String::replaceRegex(const String&, const char*) noexcept { return *this; }
engine::String& engine::String::replaceRegex(const char*, const std::string&) noexcept { return *this; }
engine::String& engine::String::replaceRegex(const std::string&, const std::string&) noexcept { return *this; }
engine::String& engine::String::replaceRegex(const String&, const std::string&) noexcept { return *this; }
engine::String& engine::String::replaceRegex(const char*, const String&) noexcept { return *this; }
engine::String& engine::String::replaceRegex(const std::string&, const String&) noexcept { return *this; }
engine::String& engine::String::replaceRegex(const String&, const String&) noexcept { return *this; }
//// #undef

bool engine::String::getline(std::istream& f, String& str) noexcept(false) {
    str.clear();
    char c;

    try {
        do {
            c = f.get();
            if (f.eof() || c == '\n')
                break;

//        std::cout << c << '\n';

            str += c;
        } while (!f.eof() && c != '\n');
    } catch ( std::exception& e ) {
        std::cout << "File read exception : " << e.what() << "\nLast read string : " << str << "\nLast char : " << c <<  '\n';
    }

    return !f.eof();
}

bool engine::String::get(std::istream& f, String& str) noexcept(false) {
    str.clear();
    char c;

    bool firstChar = false;

    do{
        c = f.get();

        if(!firstChar && c == '\n')
            f.get();

        if(firstChar && ( c == ' ' || c == '\t' || c == '\n') )
            break;
        while(c == ' ' || c == '\t' || c == '\n') //TODO : other special chars?
            c = f.get();

        firstChar = true;

        if(f.eof())
            break;

        str += c;
    } while(!f.eof() && c != '\n');

    return !f.eof();
}

engine::String& engine::String::trim(char character) noexcept {
    return this->rtrim(character).ltrim(character);
}

engine::String& engine::String::trim(const char* characters) noexcept {
    return this->rtrim(characters).ltrim(characters);
}

engine::String& engine::String::trim(const std::string& characters) noexcept {
    return this->rtrim(characters.c_str()).ltrim(characters.c_str());
}

engine::String& engine::String::trim(const engine::String& characters) noexcept {
    return this->rtrim(characters.c_str()).ltrim(characters.c_str());
}

engine::String& engine::String::ltrim(char character) noexcept {
    std::size_t endPos = 0;

    while(this->_str[endPos] == character) endPos++;

    return this->replace(0, endPos, "");
}

engine::String& engine::String::ltrim(const char* characters) noexcept {
    return this->ltrim(engine::String(characters));
}

engine::String& engine::String::ltrim(const std::string& characters) noexcept {
    return this->ltrim(engine::String(characters));
}

engine::String& engine::String::ltrim(const engine::String& characters) noexcept {
    std::size_t endPos = 0;

    while(characters.contains(this->_str[endPos])) endPos++;

//    std::cout << endPos << '\n';
//    std::cout.flush();

    return this->replace(0, endPos, "");
}

engine::String& engine::String::rtrim(char character) noexcept {
    std::size_t startPos = this->_len - 1;

    while(this->_str[startPos] == character) startPos--;

    return this->replace(startPos + 1, this->_len, "");
}

engine::String& engine::String::rtrim(const char* characters) noexcept {
    return this->rtrim(engine::String(characters));
}

engine::String& engine::String::rtrim(const std::string& characters) noexcept {
    return this->rtrim(engine::String(characters));
}

engine::String& engine::String::rtrim(const engine::String& characters) noexcept {
    std::size_t startPos = this->_len - 1;

    while(startPos >= 0 && characters.contains(this->_str[startPos])) startPos--;

    return this->replace(startPos + 1, this->_len, "");
}

static inline bool isLetter(char character) noexcept {
    return ( ( character >= 'A' && character <= 'Z' ) || ( character >= 'a' && character <= 'z' ) );
}

static inline bool isUppercaseLetter(char character) noexcept {
    return ( character >= 'A' && character <= 'Z' );
}

static inline bool isLowercaseLetter(char character) noexcept {
    return ( character >= 'a' && character <= 'z' );
}

static inline bool isDigit(char character) noexcept {
    return ( character >= '0' && character <= '9' );
}

static inline char lower(char character) noexcept {
    return character + (char)32;
}

static inline char upper(char character) noexcept {
    return character - (char)32;
}

engine::String& engine::String::capitalize() noexcept {
    if(this->_str == nullptr)
        return *this;

    if(isLowercaseLetter(this->_str[0]))
        this->_str[0] = upper(this->_str[0]);

    return *this;
}

engine::String& engine::String::toLower() noexcept {
    for(std::size_t it = 0; it < this->_len; it++)
        if(isUppercaseLetter(this->_str[it]))
            this->_str[it] = lower(this->_str[it]);

    return *this;
}

engine::String& engine::String::toUpper() noexcept {
    for(std::size_t it = 0; it < this->_len; it++)
        if(isLowercaseLetter(this->_str[it]))
            this->_str[it] = upper(this->_str[it]);

    return *this;
}

engine::String& engine::String::revertLetterCase() noexcept {
    for(std::size_t it = 0; it < this->_len; it++)
        if(isUppercaseLetter(this->_str[it]))
            this->_str[it] = lower(this->_str[it]);
        else if(isLowercaseLetter(this->_str[it]))
            this->_str[it] = upper(this->_str[it]);

    return *this;
}

static inline bool isPartOfWord(char character) noexcept {
    return !(!isLowercaseLetter(character) && !isUppercaseLetter(character) && !isDigit(character));
}

bool engine::String::isWord() const noexcept {
    for(std::size_t it = 0; it < this->_len; it++)
        if( ! isPartOfWord(this->_str[it]) )
            return false;

    return true;
}

bool engine::String::isSentence() const noexcept {
    engine::String specialChars(" \t\r\n\"\'`,.;:?!()&@");

    for(std::size_t it = 0; it < this->_len; it++) {
        if( ! isPartOfWord(this->_str[it]) && ! specialChars.contains(this->_str[it]) )
            return false;
    }

    return true;
}

bool operator == (const engine::String& a, const engine::String& b) noexcept {
    return !(a != b);
}

bool operator == (const engine::String& a, const std::string& b) noexcept {
    return !(a != b);
}

bool operator == (const std::string& a, const engine::String& b) noexcept {
    return !(a != b);
}

bool operator == (const engine::String& a, const char* b) noexcept {
    return !(a != b);
}

bool operator == (const char* a, const engine::String& b) noexcept {
    return !(a != b);
}

bool operator != (const engine::String& a, const engine::String& b) noexcept {
    if(&a == &b)
        return false;

    if(a._len != b._len)
        return true;

    for(std::size_t it = 0; it < a._len; it++)
        if(a._str[it] != b._str[it])
            return true;

    return false;
}

bool operator != (const engine::String& a, const std::string& b) noexcept {
    if(a._len != b.length())
        return true;

    for(std::size_t it = 0; it < a._len; it++)
        if(a._str[it] != b[it])
            return true;

    return false;
}

bool operator != (const std::string& a, const engine::String& b) noexcept {
    if(a.length() != b._len)
        return true;

    for(std::size_t it = 0; it < a.length(); it++)
        if(a[it] != b._str[it])
            return true;

    return false;
}

bool operator != (const engine::String& a, const char* b) noexcept {
    std::size_t len = lengthCStr(b);

    if(a._len != len)
        return true;

    for(std::size_t it = 0; it < a._len; it++)
        if(a._str[it] != b[it])
            return true;

    return false;
}

bool operator != (const char* a, const engine::String& b) noexcept {
    std::size_t len = lengthCStr(a);

    if(len != b._len)
        return true;

    for(std::size_t it = 0; it < b._len; it++)
        if(b._str[it] != a[it])
            return true;

    return false;
}

bool operator < (const engine::String& a, const engine::String& b) noexcept {

    for(std::size_t it = 0, length = std::min(a._len, b._len); it < length; it++) {
        if( a._str[it] < b._str[it] )
            return true;
        else if( a._str[it] > b._str[it] )
            return false;
    }

    return a._len < b._len;
}

bool operator < (const engine::String& a, const std::string& b) noexcept {

    for(std::size_t it = 0, length = std::min(a._len, b.length()); it < length; it++) {
        if( a._str[it] < b[it] )
            return true;
        else if( a._str[it] > b[it] )
            return false;
    }

    return a._len < b.length();
}

bool operator < (const std::string& a, const engine::String& b) noexcept {

    for(std::size_t it = 0, length = std::min(a.length(), b._len); it < length; it++) {
        if( a[it] < b._str[it] )
            return true;
        else if( a[it] > b._str[it] )
            return false;
    }

    return a.length() < b._len;
}

bool operator < (const engine::String& a, const char* b) noexcept {
    std::size_t len = lengthCStr(b);

    for(std::size_t it = 0, length = std::min(a._len, len); it < length; it++) {
        if( a._str[it] < b[it] )
            return true;
        else if( a._str[it] > b[it] )
            return false;
    }

    return a._len < len;
}

bool operator < (const char* a, const engine::String& b) noexcept {
    std::size_t len = lengthCStr(a);

    for(std::size_t it = 0, length = std::min(len, b._len); it < length; it++) {
        if( a[it] < b._str[it] )
            return true;
        else if( a[it] > b._str[it] )
            return false;
    }

    return len < b._len;
}

bool operator > (const engine::String& a, const engine::String& b) noexcept {

    for(std::size_t it = 0, length = std::min(a._len, b._len); it < length; it++) {
        if( a._str[it] > b._str[it] )
            return true;
        else if( a._str[it] < b._str[it] )
            return false;
    }

    return a._len > b._len;
}

bool operator > (const engine::String& a, const std::string& b) noexcept {

    for(std::size_t it = 0, length = std::min(a._len, b.length()); it < length; it++) {
        if( a._str[it] > b[it] )
            return true;
        else if( a._str[it] < b[it] )
            return false;
    }

    return a._len > b.length();
}

bool operator > (const std::string& a, const engine::String& b) noexcept {

    for(std::size_t it = 0, length = std::min(a.length(), b._len); it < length; it++) {
        if( a[it] > b._str[it] )
            return true;
        else if( a[it] < b._str[it] )
            return false;
    }

    return a.length() > b._len;
}

bool operator > (const engine::String& a, const char* b) noexcept {
    std::size_t len = lengthCStr(b);

    for(std::size_t it = 0, length = std::min(a._len, len); it < length; it++) {
        if( a._str[it] > b[it] )
            return true;
        else if( a._str[it] < b[it] )
            return false;
    }

    return a._len > len;
}

bool operator > (const char* a, const engine::String& b) noexcept {
    std::size_t len = lengthCStr(a);

    for(std::size_t it = 0, length = std::min(len, b._len); it < length; it++) {
        if( a[it] > b._str[it] )
            return true;
        else if( a[it] < b._str[it] )
            return false;
    }

    return len > b._len;
}

bool operator <= (const engine::String& a, const engine::String& b) noexcept {
    return !(a > b);
}

bool operator <= (const engine::String& a, const std::string& b) noexcept {
    return !(a > b);
}

bool operator <= (const std::string& a, const engine::String& b) noexcept {
    return !(a > b);
}

bool operator <= (const engine::String& a, const char* b) noexcept {
    return !(a > b);
}

bool operator <= (const char* a, const engine::String& b) noexcept {
    return !(a > b);
}

bool operator >= (const engine::String& a, const engine::String& b) noexcept {
    return !(a < b);
}

bool operator >= (const engine::String& a, const std::string& b) noexcept {
    return !(a < b);
}

bool operator >= (const std::string& a, const engine::String& b) noexcept {
    return !(a < b);
}

bool operator >= (const engine::String& a, const char* b) noexcept {
    return !(a < b);
}

bool operator >= (const char* a, const engine::String& b) noexcept {
    return !(a < b);
}

engine::String operator+ (const engine::String& a, const engine::String& b) noexcept {
    engine::String res(a);
    return res.append(b);
}

engine::String operator+ (const engine::String& a, const std::string& b) noexcept {
    engine::String res(a);
    return res.append(b);
}

engine::String operator+ (const std::string& a, const engine::String& b) noexcept {
    engine::String res(a);
    return res.append(b);
}

engine::String operator+ (const engine::String& a, const char* b) noexcept {
    engine::String res(a);
    return res.append(b);
}

engine::String operator+ (const char* a, const engine::String& b) noexcept {
    engine::String res(a);
    return res.append(b);
}

engine::String operator+ (char a, const engine::String& b) noexcept {
    engine::String res;
    return res.append(a).append(b);
}

engine::String operator+ (const engine::String& a, char b) noexcept {
    engine::String res(a);
    return res.append(b);
}

std::istream& operator >> (std::istream& f, engine::String& str) noexcept (false) {
    engine::String::get(f, str);
    return f;
}




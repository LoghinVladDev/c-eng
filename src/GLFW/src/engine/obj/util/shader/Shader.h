//
// Created by vladl on 13/07/2020.
//

#ifndef ENG1_SHADER_H
#define ENG1_SHADER_H

#include <glad/glad.h>

#include <obj/util/data/String.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <types.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


typedef enum {
    REG_CODE_LINE,

    IF_DEF_CODE_LINE,
    IF_N_DEF_CODE_LINE,
    END_IF_CODE_LINE,
    DEF_TOKEN_CODE_LINE,
    UNDEF_TOKEN_CODE_LINE,
    INCLUDE_TOKEN_CODE_LINE,

    UNKNOWN
} INC_SHD_ENUM_LINE_TYPE;

typedef struct {
    INC_SHD_ENUM_LINE_TYPE lineType;
    engine::String * tokenName;
    engine::String * tokenReplaceValue;
    engine::String * includeFileRelativePath;
} INC_SHD_STR_LINE_PROP;

#define _INIT_INC_SHD_STR_LINE_PROP(_str)               \
    _str.lineType = INC_SHD_ENUM_LINE_TYPE::UNKNOWN;    \
    _str.tokenName = nullptr;                           \
    _str.tokenReplaceValue = nullptr;

#define _TOKEN_INCLUDE          "#include"
#define _TOKEN_DEFINE           "#define"
#define _TOKEN_UNDEFINE         "#undef"
#define _TOKEN_IF_DEFINED       "#ifdef"
#define _TOKEN_IF_NOT_DEFINED   "#ifndef"
#define _TOKEN_END_IF           "#endif"

#define _INC_SHD_STR_LINE_IS_TOKEN(_token)                      \
(                                                               \
    _token == _TOKEN_INCLUDE        ||                          \
    _token == _TOKEN_DEFINE         ||                          \
    _token == _TOKEN_UNDEFINE       ||                          \
    _token == _TOKEN_IF_DEFINED     ||                          \
    _token == _TOKEN_IF_NOT_DEFINED ||                          \
    _token == _TOKEN_END_IF                                     \
)

#define _INC_SHD_STR_LINE_PROP_ENDIF(_str,_tokens)                      \
{                                                                       \
    _str.lineType = (INC_SHD_ENUM_LINE_TYPE::END_IF_CODE_LINE);         \
    return _str;                                                        \
}

#define _INC_SHD_STR_LINE_PROP_IFNDEF(_str,_tokens)                     \
{                                                                       \
    _str.lineType = (INC_SHD_ENUM_LINE_TYPE::IF_N_DEF_CODE_LINE);       \
    _str.tokenName = new engine::String(_tokens[1]);                    \
    return _str;                                                        \
}

#define _INC_SHD_STR_LINE_PROP_IFDEF(_str,_tokens)                      \
{                                                                       \
    _str.lineType = (INC_SHD_ENUM_LINE_TYPE::IF_DEF_CODE_LINE);         \
    _str.tokenName = new engine::String(_tokens[1]);                    \
    return _str;                                                        \
}

#define _INC_SHD_STR_LINE_PROP_UNDEF(_str,_tokens)                  \
{                                                                   \
    _str.lineType = (INC_SHD_ENUM_LINE_TYPE::UNDEF_TOKEN_CODE_LINE);\
    _str.tokenName = new engine::String(_tokens[1]);                \
    return _str;                                                    \
}

#define _INC_SHD_STR_LINE_PROP_REG(_str)                        \
{                                                               \
    (_str.lineType) = (INC_SHD_ENUM_LINE_TYPE::REG_CODE_LINE);  \
    return _str;                                                \
}

#define _INC_SHD_STR_LINE_PROP_INC(_str,_tokens)                        \
{                                                                       \
    _str.lineType = (INC_SHD_ENUM_LINE_TYPE::INCLUDE_TOKEN_CODE_LINE);  \
    _str.includeFileRelativePath = new engine::String(_tokens[1]);      \
    return _str;                                                        \
}

#define _INC_SHD_STR_LINE_PROP_DEF(_str,_tokens)                                    \
{                                                                                   \
    _str.lineType = (INC_SHD_ENUM_LINE_TYPE::DEF_TOKEN_CODE_LINE);                  \
    _str.tokenName = new engine::String(_tokens[1]);                                \
    _str.tokenReplaceValue = new engine::String();                                  \
    for(std::size_t __it = 2, __len = _tokens.getLength(); __it < __len; __it++) {  \
        (*_str.tokenReplaceValue) += _tokens[__it];                                 \
    }                                                                               \
    return _str;                                                                    \
}

#define _INC_SHD_STR_PROP_IS_TOKEN(_str)                                \
(                                                                       \
    _str.lineType == INC_SHD_ENUM_LINE_TYPE::INCLUDE_TOKEN_CODE_LINE || \
    _str.lineType == INC_SHD_ENUM_LINE_TYPE::END_IF_CODE_LINE        || \
    _str.lineType == INC_SHD_ENUM_LINE_TYPE::IF_N_DEF_CODE_LINE      || \
    _str.lineType == INC_SHD_ENUM_LINE_TYPE::IF_DEF_CODE_LINE        || \
    _str.lineType == INC_SHD_ENUM_LINE_TYPE::UNDEF_TOKEN_CODE_LINE   || \
    _str.lineType == INC_SHD_ENUM_LINE_TYPE::DEF_TOKEN_CODE_LINE        \
)

#define _INC_SHD_STR_LINE_TYPE_STR_TO_ENUM(_str,_enum)                                      \
    if(_str == _TOKEN_INCLUDE)                                                              \
        _enum = INC_SHD_ENUM_LINE_TYPE::INCLUDE_TOKEN_CODE_LINE;                            \
    if(_str == _TOKEN_DEFINE)                                                               \
        _enum = INC_SHD_ENUM_LINE_TYPE::DEF_TOKEN_CODE_LINE;                                \
    if(_str == _TOKEN_UNDEFINE)                                                             \
        _enum = INC_SHD_ENUM_LINE_TYPE::UNDEF_TOKEN_CODE_LINE;                              \
    if(_str == _TOKEN_IF_DEFINED)                                                           \
        _enum = INC_SHD_ENUM_LINE_TYPE::IF_DEF_CODE_LINE;                                   \
    if(_str == _TOKEN_IF_NOT_DEFINED)                                                       \
        _enum = INC_SHD_ENUM_LINE_TYPE::IF_N_DEF_CODE_LINE;                                 \
    if(_str == _TOKEN_END_IF)                                                               \
        _enum = INC_SHD_ENUM_LINE_TYPE::END_IF_CODE_LINE;


#define _INC_SHD_STR_CLEAR_STR(_str)    \
    delete _str.tokenName;              \
    delete _str.tokenReplaceValue;      \
    delete _str.includeFileRelativePath;

#define _INC_SHD_STR_PRINT_STR(_str) std::cout << _str.lineType << ' ' << ( _str.tokenName == nullptr ? engine::String("null") : ( (*_str.tokenName) == "" ? engine::String("empty") : (*_str.tokenName) ) ) << ' ' << ( _str.tokenReplaceValue == nullptr ? engine::String("null") : ( (*_str.tokenReplaceValue) == "" ? engine::String("empty") : (*_str.tokenReplaceValue) ) ) << ' ' << ( _str.includeFileRelativePath == nullptr ? engine::String("null") : (*_str.includeFileRelativePath == "" ? engine::String("empty") : (*_str.includeFileRelativePath) ) ) << '\n'


namespace engine {

    class [[maybe_unused]] Shader {
    private:
        static std::string _pathToShadersFolder;
        std::string _fragmentFilename;
        std::string _vertexFilename;

        bool failed { false };

        uint32 ID {0U};

        [[maybe_unused]] static void diagnoseShaderCompilation(int, const std::string&) noexcept;
        [[maybe_unused]] static void diagnoseProgramCompilation(int) noexcept;

//        [[maybe_unused]] void includeSubShaders(const std::string&, std::stringstream&) noexcept;
    public:
        Shader() = delete;
        ~Shader();

        [[maybe_unused]] static void setShadersFolder(const std::string&) noexcept;
        [[maybe_unused]] static void setShadersFolder(const char*) noexcept;

        [[maybe_unused]] Shader(const char *, const char *, bool = false, bool = false) noexcept;
        [[maybe_unused]] Shader(const std::string&, const std::string&, bool = false, bool = false) noexcept;

        [[maybe_unused]] void use() const noexcept;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"

        [[maybe_unused]] Shader& setBool(const std::string &, bool) noexcept;
        [[maybe_unused]] Shader& setInt(const std::string &, int) noexcept;
        [[maybe_unused]] Shader& setFloat(const std::string &, float) noexcept;
        [[maybe_unused]] Shader& setDouble(const std::string &, double) noexcept;
        [[maybe_unused]] Shader& setVec3(const std::string &, const engine::VectorF&) noexcept;
        [[maybe_unused]] Shader& setVec4(const std::string &, const engine::Vector4F&) noexcept;
        [[maybe_unused]] Shader& setVec3d(const std::string &, const engine::VectorD&) noexcept;
        [[maybe_unused]] Shader& setVec4d(const std::string &, const engine::Vector4D&) noexcept;
        [[maybe_unused]] Shader& setVec3(const std::string &, const glm::vec3&) noexcept;
        [[maybe_unused]] Shader& setVec4(const std::string &, const glm::vec4&) noexcept;
        [[maybe_unused]] Shader& setMat3(const std::string &, const glm::mat3&) noexcept;
        [[maybe_unused]] Shader& setMat4(const std::string &, const glm::mat4&) noexcept;

#pragma clang diagnostic pop

        [[maybe_unused]] [[nodiscard]] int getID() const noexcept;
    };
}

#endif //ENG1_SHADER_H

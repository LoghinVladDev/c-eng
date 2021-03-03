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
#include <obj/util/data/Map.h>


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
    _str.tokenReplaceValue = nullptr;                   \
    _str.includeFileRelativePath = nullptr;

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

#define _SHD_HEADER_DATA_TYPE_STD_TYPE_START            0x00
#define _SHD_HEADER_DATA_TYPE_STD_TYPE_ARR_START        0x40
#define _SHD_HEADER_DATA_TYPE_STD_SHD_TYPE_START        0x80
#define _SHD_HEADER_DATA_TYPE_STD_SHD_TYPE_ARR_START    0xC0
#define _SHD_HEADER_DATA_TYPE_STD_STRUCT_TYPE_START     0xFD
#define _SHD_HEADER_DATA_TYPE_STD_STRUCT_TYPE_ARR_START 0xFE

#define _SHD_HEADER_DATA_TYPE_STD_TYPE_END          _SHD_HEADER_DATA_TYPE_STD_TYPE_ARR_START
#define _SHD_HEADER_DATA_TYPE_STD_TYPE_ARR_END      _SHD_HEADER_DATA_TYPE_STD_SHD_TYPE_START
#define _SHD_HEADER_DATA_TYPE_STD_SHD_TYPE_END      _SHD_HEADER_DATA_TYPE_STD_SHD_TYPE_ARR_START
#define _SHD_HEADER_DATA_TYPE_STD_SHD_TYPE_ARR_END  _SHD_HEADER_DATA_TYPE_STD_STRUCT_TYPE_START

#define _SHD_HEADER_DATA_TYPE_STD_TYPE(_vType)          ( _vType >= _SHD_HEADER_DATA_TYPE_STD_TYPE_START && _vType < _SHD_HEADER_DATA_TYPE_STD_TYPE_END )
#define _SHD_HEADER_DATA_TYPE_STD_SHD_TYPE(_vType)      ( _vType >= _SHD_HEADER_DATA_TYPE_STD_SHD_TYPE_START && _vType < _SHD_HEADER_DATA_TYPE_STD_SHD_TYPE_END )

#define _SHD_HEADER_DATA_TYPE_STD_TYPE_ARR(_vType)      ( _vType >= _SHD_HEADER_DATA_TYPE_STD_TYPE_ARR_START && _vType < _SHD_HEADER_DATA_TYPE_STD_TYPE_ARR_END )
#define _SHD_HEADER_DATA_TYPE_STD_SHD_TYPE_ARR(_vType)  ( _vType >= _SHD_HEADER_DATA_TYPE_STD_SHD_TYPE_ARR_START && _vType < _SHD_HEADER_DATA_TYPE_STD_SHD_TYPE_ARR_END )

#define _SHD_HEADER_DATA_IS_VAR_TYPE(_vType) ( _SHD_HEADER_DATA_TYPE_STD_TYPE(_vType) || _SHD_HEADER_DATA_TYPE_STD_SHD_TYPE(_vType) )
#define _SHD_HEADER_DATA_IS_VAR_ARR_TYPE(_vType) ( _SHD_HEADER_DATA_TYPE_STD_TYPE_ARR(_vType) || _SHD_HEADER_DATA_TYPE_STD_SHD_TYPE_ARR(_vType) )

#define _GLSL_TOKEN_UNIFORM     "uniform"
#define _GLSL_TOKEN_INPUT       "in"
#define _GLSL_TOKEN_OUTPUT      "out"

#define _GLSL_TYPE_UNSIGNED_INT "uint"
#define _GLSL_TYPE_INT          "int"
#define _GLSL_TYPE_FLOAT        "float"
#define _GLSL_TYPE_DOUBLE       "double"
#define _GLSL_TYPE_BOOL         "bool"
#define _GLSL_TYPE_SAMPLER_2D   "sampler2D"
#define _GLSL_TYPE_VEC_2        "vec2"
#define _GLSL_TYPE_VEC_3        "vec3"
#define _GLSL_TYPE_VEC_4        "vec4"
#define _GLSL_TYPE_MAT_3        "mat3"
#define _GLSL_TYPE_MAT_4        "mat4"
#define _GLSL_TYPE_STRUCT       "struct"

#define _GLSL_INCLUDE_FILE_EXTENSION ".glslh"

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

        class Header {
        public:
            enum DataTypeModifier : uint8 {
                NONE,
                INPUT,
                OUTPUT,
                UNIFORM
            };

            enum DataType : uint8 {
                SINT8                                               = _SHD_HEADER_DATA_TYPE_STD_TYPE_START,
                SINT16,
                SINT32,
                SINT64,
                BOOL, 
                UINT8,
                UINT16,
                UINT32,
                UINT64,
                FLOAT32,
                FLOAT64,

                CHAR                            [[maybe_unused]]    = SINT8,

                BYTE                            [[maybe_unused]]    = UINT8,

                SHORT                           [[maybe_unused]]    = SINT16,
                SHORT_INT                       [[maybe_unused]]    = SINT16,

                UNSIGNED_SHORT                  [[maybe_unused]]    = UINT16,
                UNSIGNED_SHORT_INT              [[maybe_unused]]    = UINT16,

                INT = SINT32,

                UNSIGNED                        [[maybe_unused]]    = UINT32,
                UNSIGNED_INT                    [[maybe_unused]]    = UINT32,

                LONG = SINT64,
                LONG_LONG                       [[maybe_unused]]    = SINT64,
                LONG_LONG_INT                   [[maybe_unused]]    = SINT64,

                UNSIGNED_LONG                   [[maybe_unused]]    = UINT64,
                UNSIGNED_LONG_LONG              [[maybe_unused]]    = UINT64,
                UNSIGNED_LONG_LONG_INT          [[maybe_unused]]    = UINT64,

                FLOAT                           [[maybe_unused]]    = FLOAT32,
                DOUBLE                          [[maybe_unused]]    = FLOAT64,
                
                SINT8_ARRAY                                         = _SHD_HEADER_DATA_TYPE_STD_TYPE_ARR_START,
                SINT16_ARRAY,
                SINT32_ARRAY,
                SINT64_ARRAY,
                BOOL_ARRAY,
                UINT8_ARRAY,
                UINT16_ARRAY,
                UINT32_ARRAY,
                UINT64_ARRAY,
                FLOAT32_ARRAY,
                FLOAT64_ARRAY,

                CHAR_ARRAY                      [[maybe_unused]]    = SINT8_ARRAY,

                BYTE_ARRAY                      [[maybe_unused]]    = UINT8_ARRAY,

                SHORT_ARRAY                     [[maybe_unused]]    = SINT16_ARRAY,
                SHORT_INT_ARRAY                 [[maybe_unused]]    = SINT16_ARRAY,

                UNSIGNED_SHORT_ARRAY            [[maybe_unused]]    = UINT16_ARRAY,
                UNSIGNED_SHORT_INT_ARRAY        [[maybe_unused]]    = UINT16_ARRAY,

                INT_ARRAY                       [[maybe_unused]]    = SINT32_ARRAY,

                UNSIGNED_ARRAY                  [[maybe_unused]]    = UINT32_ARRAY,
                UNSIGNED_INT_ARRAY              [[maybe_unused]]    = UINT32_ARRAY,

                LONG_ARRAY                      [[maybe_unused]]    = SINT64_ARRAY,
                LONG_LONG_ARRAY                 [[maybe_unused]]    = SINT64_ARRAY,
                LONG_LONG_INT_ARRAY             [[maybe_unused]]    = SINT64_ARRAY,

                UNSIGNED_LONG_ARRAY             [[maybe_unused]]    = UINT64_ARRAY,
                UNSIGNED_LONG_LONG_ARRAY        [[maybe_unused]]    = UINT64_ARRAY,
                UNSIGNED_LONG_LONG_INT_ARRAY    [[maybe_unused]]    = UINT64_ARRAY,

                FLOAT_ARRAY                     [[maybe_unused]]    = FLOAT32_ARRAY,
                DOUBLE_ARRAY                    [[maybe_unused]]    = FLOAT64_ARRAY,

                SAMPLER_2D                                          = _SHD_HEADER_DATA_TYPE_STD_SHD_TYPE_START,

                VEC_2,
                VEC_3,
                VEC_4,

                MAT_3,
                MAT_4,


                SAMPLER_2D_ARRAY                                    = _SHD_HEADER_DATA_TYPE_STD_SHD_TYPE_ARR_START,

                VEC_2_ARRAY,
                VEC_3_ARRAY,
                VEC_4_ARRAY,

                MAT_3_ARRAY,
                MAT_4_ARRAY,

                STRUCT                                              = _SHD_HEADER_DATA_TYPE_STD_STRUCT_TYPE_START,
                STRUCT_ARRAY                                        = _SHD_HEADER_DATA_TYPE_STD_STRUCT_TYPE_ARR_START
            };

            [[maybe_unused]] static engine::String dataTypeToString(DataType) noexcept;
            [[maybe_unused]] static engine::String dataTypeModifierToString(DataTypeModifier) noexcept;

            [[maybe_unused]] static engine::String dataTypeDeclaration(DataType) noexcept;
            [[maybe_unused]] static engine::String dataTypeModifierDeclaration(DataTypeModifier) noexcept;

            [[maybe_unused]] static engine::String toString(const glm::vec2&) noexcept;
            [[maybe_unused]] static engine::String toString(const glm::vec3&) noexcept;
            [[maybe_unused]] static engine::String toString(const glm::vec4&) noexcept;

            [[maybe_unused]] static engine::String toString(const glm::mat3&) noexcept;
            [[maybe_unused]] static engine::String toString(const glm::mat4&) noexcept;

            class Struct {
            private:

                engine::Array < engine::NonConstexprPair < uint8, engine::String > > _variables;

                // engine::HashMap < uint8, engine::String > _variables;
//                engine::HashMap < engine::Shader::Header::DataType , engine::String > _variables;
                engine::HashMap < engine::String, uint64 > _arraySizes;
                engine::HashMap < engine::String, engine::String> _structureTypeNames;

                engine::String _name;

            public:
                Struct() = delete;
                Struct(const Struct&) noexcept;
                explicit Struct(const char*) noexcept;
                explicit Struct(const engine::String&) noexcept;

                [[maybe_unused]] [[nodiscard]] engine::Array < engine::NonConstexprPair < uint8, engine::String > > & getVariables() noexcept;

                // engine::HashMap < uint8, engine::String > & getVariables() noexcept;
//                engine::HashMap < engine::Shader::Header::DataType, engine::String >& getVariables() noexcept;
                [[maybe_unused]] [[nodiscard]] engine::HashMap < engine::String, uint64 > & getArraySizes() noexcept;
                [[maybe_unused]] [[nodiscard]] engine::HashMap < engine::String, engine::String > & getStructureVariableTypes() noexcept;

                [[nodiscard]] engine::String getName() const noexcept;

                Struct& operator = (const Struct&) noexcept;

                [[maybe_unused]] Struct& addVariable(const engine::String&, DataType) noexcept;
                [[maybe_unused]] Struct& addVariable(const char*, DataType) noexcept;

                [[maybe_unused]] Struct& addVariable(const Struct&, const char*) noexcept;
                [[maybe_unused]] Struct& addStructVariable(const char*, const char*) noexcept;

                [[maybe_unused]] Struct& addVariableUInt8  (const engine::String&) noexcept;
                [[maybe_unused]] Struct& addVariableUInt16 (const engine::String&) noexcept;
                [[maybe_unused]] Struct& addVariableUInt32 (const engine::String&) noexcept;
                [[maybe_unused]] Struct& addVariableUInt64 (const engine::String&) noexcept;

                [[maybe_unused]] Struct& addVariableInt8   (const engine::String&) noexcept;
                [[maybe_unused]] Struct& addVariableInt16  (const engine::String&) noexcept;
                [[maybe_unused]] Struct& addVariableInt32  (const engine::String&) noexcept;
                [[maybe_unused]] Struct& addVariableInt64  (const engine::String&) noexcept;

                [[maybe_unused]] Struct& addVariableFloat  (const engine::String&) noexcept;
                [[maybe_unused]] Struct& addVariableDouble (const engine::String&) noexcept;
                [[maybe_unused]] Struct& addVariableBool   (const engine::String&) noexcept;

                [[maybe_unused]] Struct& addVariableSampler2D (const engine::String&) noexcept;

                [[maybe_unused]] Struct& addVariableVec2      (const engine::String&) noexcept;
                [[maybe_unused]] Struct& addVariableVec3      (const engine::String&) noexcept;
                [[maybe_unused]] Struct& addVariableVec4      (const engine::String&) noexcept;
                [[maybe_unused]] Struct& addVariableMat3      (const engine::String&) noexcept;
                [[maybe_unused]] Struct& addVariableMat4      (const engine::String&) noexcept;


                [[maybe_unused]] Struct& addArrayVariable(const engine::String&, DataType, std::size_t) noexcept;
                [[maybe_unused]] Struct& addArrayVariable(const Struct&, const char*, std::size_t) noexcept;
                [[maybe_unused]] Struct& addArrayVariable(const Struct&, const engine::String&, std::size_t) noexcept;
                [[maybe_unused]] Struct& addArrayStructVariable(const engine::String&, const engine::String&,std::size_t) noexcept;

                [[maybe_unused]] Struct& addArrayVariableUInt16(const engine::String&, std::size_t) noexcept;
                [[maybe_unused]] Struct& addArrayVariableUInt32(const engine::String&, std::size_t) noexcept;
                [[maybe_unused]] Struct& addArrayVariableUInt8 (const engine::String&, std::size_t) noexcept;
                [[maybe_unused]] Struct& addArrayVariableUInt64(const engine::String&, std::size_t) noexcept;

                [[maybe_unused]] Struct& addArrayVariableInt8  (const engine::String&, std::size_t) noexcept;
                [[maybe_unused]] Struct& addArrayVariableInt16 (const engine::String&, std::size_t) noexcept;
                [[maybe_unused]] Struct& addArrayVariableInt32 (const engine::String&, std::size_t) noexcept;
                [[maybe_unused]] Struct& addArrayVariableInt64 (const engine::String&, std::size_t) noexcept;

                [[maybe_unused]] Struct& addArrayVariableFloat (const engine::String&, std::size_t) noexcept;
                [[maybe_unused]] Struct& addArrayVariableDouble(const engine::String&, std::size_t) noexcept;
                [[maybe_unused]] Struct& addArrayVariableBool  (const engine::String&, std::size_t) noexcept;

                [[maybe_unused]] Struct& addArrayVariableSampler2D(const engine::String&, std::size_t) noexcept;
                [[maybe_unused]] Struct& addArrayVariableVec2     (const engine::String&, std::size_t) noexcept;
                [[maybe_unused]] Struct& addArrayVariableVec3     (const engine::String&, std::size_t) noexcept;
                [[maybe_unused]] Struct& addArrayVariableVec4     (const engine::String&, std::size_t) noexcept;
                [[maybe_unused]] Struct& addArrayVariableMat3     (const engine::String&, std::size_t) noexcept;
                [[maybe_unused]] Struct& addArrayVariableMat4     (const engine::String&, std::size_t) noexcept;


                [[maybe_unused]] Struct& addVariableUInt8  (const char*) noexcept;
                [[maybe_unused]] Struct& addVariableUInt16 (const char*) noexcept;
                [[maybe_unused]] Struct& addVariableUInt32 (const char*) noexcept;
                [[maybe_unused]] Struct& addVariableUInt64 (const char*) noexcept;

                [[maybe_unused]] Struct& addVariableInt8   (const char*) noexcept;
                [[maybe_unused]] Struct& addVariableInt16  (const char*) noexcept;
                [[maybe_unused]] Struct& addVariableInt32  (const char*) noexcept;
                [[maybe_unused]] Struct& addVariableInt64  (const char*) noexcept;

                [[maybe_unused]] Struct& addVariableFloat  (const char*) noexcept;
                [[maybe_unused]] Struct& addVariableDouble (const char*) noexcept;
                [[maybe_unused]] Struct& addVariableBool   (const char*) noexcept;

                [[maybe_unused]] Struct& addVariableSampler2D (const char*) noexcept;

                [[maybe_unused]] Struct& addVariableVec2      (const char*) noexcept;
                [[maybe_unused]] Struct& addVariableVec3      (const char*) noexcept;
                [[maybe_unused]] Struct& addVariableVec4      (const char*) noexcept;
                [[maybe_unused]] Struct& addVariableMat3      (const char*) noexcept;
                [[maybe_unused]] Struct& addVariableMat4      (const char*) noexcept;


                [[maybe_unused]] Struct& addArrayVariable(const char*, DataType, std::size_t) noexcept;
                [[maybe_unused]] Struct& addArrayStructVariable(const char*, const char*, std::size_t) noexcept;

                [[maybe_unused]] Struct& addArrayVariableUInt8 (const char*, std::size_t) noexcept;
                [[maybe_unused]] Struct& addArrayVariableUInt16(const char*, std::size_t) noexcept;
                [[maybe_unused]] Struct& addArrayVariableUInt32(const char*, std::size_t) noexcept;
                [[maybe_unused]] Struct& addArrayVariableUInt64(const char*, std::size_t) noexcept;

                [[maybe_unused]] Struct& addArrayVariableInt8  (const char*, std::size_t) noexcept;
                [[maybe_unused]] Struct& addArrayVariableInt16 (const char*, std::size_t) noexcept;
                [[maybe_unused]] Struct& addArrayVariableInt32 (const char*, std::size_t) noexcept;
                [[maybe_unused]] Struct& addArrayVariableInt64 (const char*, std::size_t) noexcept;

                [[maybe_unused]] Struct& addArrayVariableFloat (const char*, std::size_t) noexcept;
                [[maybe_unused]] Struct& addArrayVariableDouble(const char*, std::size_t) noexcept;
                [[maybe_unused]] Struct& addArrayVariableBool  (const char*, std::size_t) noexcept;

                [[maybe_unused]] Struct& addArrayVariableSampler2D(const char*, std::size_t) noexcept;
                [[maybe_unused]] Struct& addArrayVariableVec2     (const char*, std::size_t) noexcept;
                [[maybe_unused]] Struct& addArrayVariableVec3     (const char*, std::size_t) noexcept;
                [[maybe_unused]] Struct& addArrayVariableVec4     (const char*, std::size_t) noexcept;
                [[maybe_unused]] Struct& addArrayVariableMat3     (const char*, std::size_t) noexcept;
                [[maybe_unused]] Struct& addArrayVariableMat4     (const char*, std::size_t) noexcept;

                [[maybe_unused]] Struct& settleVariables() noexcept;

                [[nodiscard]] engine::String toString() const noexcept;
                
            };

        private:
            engine::String _declarations;
            engine::String _definitions;

            engine::String _name;
            engine::String _path {engine::String(__SHADERS_PATH__)};
            bool _generateIncludeGuards {true};

            engine::HashMap <engine::String, engine::Shader::Header::Struct> _definedStructures;

            [[maybe_unused]] [[nodiscard]] engine::String includeGuardTop() const noexcept;
            [[maybe_unused]] [[nodiscard]] engine::String includeGuardBottom() const noexcept;

            [[maybe_unused]] [[nodiscard]] engine::String generateCode() const noexcept;

        public:
            Header() = delete;
            explicit Header(const char*, bool = true) noexcept;
            explicit Header(const engine::String&, bool = true) noexcept;

            [[maybe_unused]] Header& setRelativePath(const char*) noexcept;
            [[maybe_unused]] Header& setAbsolutePath(const char*) noexcept;

            [[maybe_unused]] Header& clear() noexcept;

            [[maybe_unused]] Header& addDefine(const engine::String&, const engine::String& = engine::String("")) noexcept;

            [[maybe_unused]] Header& addIfDefined(const engine::String&) noexcept;
            [[maybe_unused]] Header& addIfNotDefined(const engine::String&) noexcept;
            [[maybe_unused]] Header& addEndIf() noexcept;

            [[maybe_unused]] Header& addStruct(const Shader::Header::Struct&) noexcept;

            [[maybe_unused]] Header& addCode(const char*) noexcept;
            [[maybe_unused]] Header& addCode(const engine::String&) noexcept;
            [[maybe_unused]] Header& addCode(const std::string&) noexcept;

            [[maybe_unused]] Header& addVariable(const engine::String&, DataType, DataTypeModifier = DataTypeModifier::NONE) noexcept;
            [[maybe_unused]] Header& addVariable(const engine::String&, const Struct&, DataTypeModifier = DataTypeModifier::NONE) noexcept;
            [[maybe_unused]] Header& addStructVariable(const engine::String&, const engine::String&, DataTypeModifier = DataTypeModifier::NONE) noexcept;

            [[maybe_unused]] Header& addVariableUInt8  (const engine::String&, DataTypeModifier = DataTypeModifier::NONE, uint8  = 0U ) noexcept;
            [[maybe_unused]] Header& addVariableUInt16 (const engine::String&, DataTypeModifier = DataTypeModifier::NONE, uint16 = 0U ) noexcept;
            [[maybe_unused]] Header& addVariableUInt32 (const engine::String&, DataTypeModifier = DataTypeModifier::NONE, uint32 = 0UL) noexcept;
            [[maybe_unused]] Header& addVariableUInt64 (const engine::String&, DataTypeModifier = DataTypeModifier::NONE, uint64 = 0UL) noexcept;

            [[maybe_unused]] Header& addVariableInt8   (const engine::String&, DataTypeModifier = DataTypeModifier::NONE, int8   = 0U ) noexcept;
            [[maybe_unused]] Header& addVariableInt16  (const engine::String&, DataTypeModifier = DataTypeModifier::NONE, int16  = 0U ) noexcept;
            [[maybe_unused]] Header& addVariableInt32  (const engine::String&, DataTypeModifier = DataTypeModifier::NONE, int32  = 0UL) noexcept;
            [[maybe_unused]] Header& addVariableInt64  (const engine::String&, DataTypeModifier = DataTypeModifier::NONE, int64  = 0UL) noexcept;

            [[maybe_unused]] Header& addVariableFloat  (const engine::String&, DataTypeModifier = DataTypeModifier::NONE, float = 0.0f) noexcept;
            [[maybe_unused]] Header& addVariableDouble (const engine::String&, DataTypeModifier = DataTypeModifier::NONE, double = 0.0) noexcept;
            [[maybe_unused]] Header& addVariableBool   (const engine::String&, DataTypeModifier = DataTypeModifier::NONE, bool = false) noexcept;

            [[maybe_unused]] Header& addVariableSampler2D (const engine::String&, DataTypeModifier = DataTypeModifier::NONE) noexcept;

            [[maybe_unused]] Header& addVariableVec2      (const engine::String&, DataTypeModifier = DataTypeModifier::NONE, const glm::vec2& = glm::vec2(0.0f)) noexcept;
            [[maybe_unused]] Header& addVariableVec3      (const engine::String&, DataTypeModifier = DataTypeModifier::NONE, const glm::vec3& = glm::vec3(0.0f)) noexcept;
            [[maybe_unused]] Header& addVariableVec4      (const engine::String&, DataTypeModifier = DataTypeModifier::NONE, const glm::vec4& = glm::vec4(0.0f)) noexcept;
            [[maybe_unused]] Header& addVariableMat3      (const engine::String&, DataTypeModifier = DataTypeModifier::NONE, const glm::mat3& = glm::mat3(0.0f)) noexcept;
            [[maybe_unused]] Header& addVariableMat4      (const engine::String&, DataTypeModifier = DataTypeModifier::NONE, const glm::mat4& = glm::mat4(0.0f)) noexcept;


            [[maybe_unused]] Header& addArrayVariable(const engine::String&, DataType, std::size_t, DataTypeModifier = DataTypeModifier::NONE) noexcept;
            [[maybe_unused]] Header& addArrayVariable(const engine::String&, const Struct&, std::size_t, DataTypeModifier = DataTypeModifier::NONE) noexcept;
            [[maybe_unused]] Header& addArrayStructVariable(const engine::String&, const engine::String& , std::size_t, DataTypeModifier = DataTypeModifier::NONE) noexcept;

            [[maybe_unused]] Header& addArrayVariableUInt16(const engine::String&, std::size_t, DataTypeModifier = DataTypeModifier::NONE) noexcept;
            [[maybe_unused]] Header& addArrayVariableUInt32(const engine::String&, std::size_t, DataTypeModifier = DataTypeModifier::NONE) noexcept;
            [[maybe_unused]] Header& addArrayVariableUInt8 (const engine::String&, std::size_t, DataTypeModifier = DataTypeModifier::NONE) noexcept;
            [[maybe_unused]] Header& addArrayVariableUInt64(const engine::String&, std::size_t, DataTypeModifier = DataTypeModifier::NONE) noexcept;

            [[maybe_unused]] Header& addArrayVariableInt8  (const engine::String&, std::size_t, DataTypeModifier = DataTypeModifier::NONE) noexcept;
            [[maybe_unused]] Header& addArrayVariableInt16 (const engine::String&, std::size_t, DataTypeModifier = DataTypeModifier::NONE) noexcept;
            [[maybe_unused]] Header& addArrayVariableInt32 (const engine::String&, std::size_t, DataTypeModifier = DataTypeModifier::NONE) noexcept;
            [[maybe_unused]] Header& addArrayVariableInt64 (const engine::String&, std::size_t, DataTypeModifier = DataTypeModifier::NONE) noexcept;

            [[maybe_unused]] Header& addArrayVariableFloat (const engine::String&, std::size_t, DataTypeModifier = DataTypeModifier::NONE) noexcept;
            [[maybe_unused]] Header& addArrayVariableDouble(const engine::String&, std::size_t, DataTypeModifier = DataTypeModifier::NONE) noexcept;
            [[maybe_unused]] Header& addArrayVariableBool  (const engine::String&, std::size_t, DataTypeModifier = DataTypeModifier::NONE) noexcept;

            [[maybe_unused]] Header& addArrayVariableSampler2D(const engine::String&, std::size_t, DataTypeModifier = DataTypeModifier::NONE) noexcept;
            [[maybe_unused]] Header& addArrayVariableVec2     (const engine::String&, std::size_t, DataTypeModifier = DataTypeModifier::NONE) noexcept;
            [[maybe_unused]] Header& addArrayVariableVec3     (const engine::String&, std::size_t, DataTypeModifier = DataTypeModifier::NONE) noexcept;
            [[maybe_unused]] Header& addArrayVariableVec4     (const engine::String&, std::size_t, DataTypeModifier = DataTypeModifier::NONE) noexcept;
            [[maybe_unused]] Header& addArrayVariableMat3     (const engine::String&, std::size_t, DataTypeModifier = DataTypeModifier::NONE) noexcept;
            [[maybe_unused]] Header& addArrayVariableMat4     (const engine::String&, std::size_t, DataTypeModifier = DataTypeModifier::NONE) noexcept;


            [[maybe_unused]] Header& addVariable(const char* varName, DataType dataType, DataTypeModifier modifier = DataTypeModifier::NONE) noexcept {
                return this->addVariable(engine::String(varName), dataType, modifier);
            }

            [[maybe_unused]] Header& addVariable(const char* varName, const Struct& structure, DataTypeModifier modifier = DataTypeModifier::NONE) noexcept {
                return this->addVariable(engine::String(varName), structure, modifier);
            }

            [[maybe_unused]] Header& addStructVariable(const char* varName, const char* structName, DataTypeModifier modifier = DataTypeModifier::NONE) noexcept {
                return this->addStructVariable(engine::String(varName), engine::String(structName), modifier);
            }

            [[maybe_unused]] Header& addVariableUInt8  (const char * varName, DataTypeModifier modifier = DataTypeModifier::NONE, uint8  defaultValue = 0U ) noexcept {
                return this->addVariableUInt8 ( engine::String(varName), modifier, defaultValue );
            }

            [[maybe_unused]] Header& addVariableUInt16 (const char * varName, DataTypeModifier modifier = DataTypeModifier::NONE, uint16 defaultValue = 0U ) noexcept{
                return this->addVariableUInt16 ( engine::String(varName), modifier, defaultValue );
            }

            [[maybe_unused]] Header& addVariableUInt32 (const char * varName, DataTypeModifier modifier = DataTypeModifier::NONE, uint32 defaultValue = 0UL) noexcept{
                return this->addVariableUInt32 ( engine::String(varName), modifier, defaultValue );
            }

            [[maybe_unused]] Header& addVariableUInt64 (const char * varName, DataTypeModifier modifier = DataTypeModifier::NONE, uint64 defaultValue = 0UL) noexcept{
                return this->addVariableUInt64 ( engine::String(varName), modifier, defaultValue );
            }


            [[maybe_unused]] Header& addVariableInt8   (const char * varName, DataTypeModifier modifier = DataTypeModifier::NONE, int8   defaultValue = 0U ) noexcept{
                return this->addVariableInt8 ( engine::String(varName), modifier, defaultValue );
            }

            [[maybe_unused]] Header& addVariableInt16  (const char * varName, DataTypeModifier modifier = DataTypeModifier::NONE, int16  defaultValue = 0U ) noexcept{
                return this->addVariableInt16 ( engine::String(varName), modifier, defaultValue );
            }

            [[maybe_unused]] Header& addVariableInt32  (const char * varName, DataTypeModifier modifier = DataTypeModifier::NONE, int32  defaultValue = 0UL) noexcept{
                return this->addVariableInt32 ( engine::String(varName), modifier, defaultValue );
            }

            [[maybe_unused]] Header& addVariableInt64  (const char * varName, DataTypeModifier modifier = DataTypeModifier::NONE, int64  defaultValue= 0UL) noexcept{
                return this->addVariableInt64 ( engine::String(varName), modifier, defaultValue );
            }


            [[maybe_unused]] Header& addVariableFloat  (const char * varName, DataTypeModifier modifier = DataTypeModifier::NONE, float  defaultValue= 0.0f) noexcept{
                return this->addVariableFloat ( engine::String(varName), modifier, defaultValue );
            }

            [[maybe_unused]] Header& addVariableDouble (const char * varName, DataTypeModifier modifier = DataTypeModifier::NONE, double defaultValue= 0.0) noexcept{
                return this->addVariableDouble ( engine::String(varName), modifier, defaultValue );
            }

            [[maybe_unused]] Header& addVariableBool   (const char * varName, DataTypeModifier modifier = DataTypeModifier::NONE, bool   defaultValue= false) noexcept{
                return this->addVariableBool ( engine::String(varName), modifier, defaultValue );
            }


            [[maybe_unused]] Header& addVariableSampler2D (const char * varName, DataTypeModifier modifier = DataTypeModifier::NONE) noexcept {
                return this->addVariableSampler2D( engine::String(varName), modifier );
            }

            [[maybe_unused]] Header& addVariableVec2      (const char * varName, DataTypeModifier modifier = DataTypeModifier::NONE, const glm::vec2& defaultValue= glm::vec2(0.0f)) noexcept{
                return this->addVariableVec2 ( engine::String(varName), modifier, defaultValue );
            }

            [[maybe_unused]] Header& addVariableVec3      (const char * varName, DataTypeModifier modifier = DataTypeModifier::NONE, const glm::vec3& defaultValue= glm::vec3(0.0f)) noexcept{
                return this->addVariableVec3 ( engine::String(varName), modifier, defaultValue );
            }

            [[maybe_unused]] Header& addVariableVec4      (const char * varName, DataTypeModifier modifier = DataTypeModifier::NONE, const glm::vec4& defaultValue= glm::vec4(0.0f)) noexcept{
                return this->addVariableVec4 ( engine::String(varName), modifier, defaultValue );
            }

            [[maybe_unused]] Header& addVariableMat3      (const char * varName, DataTypeModifier modifier = DataTypeModifier::NONE, const glm::mat3& defaultValue= glm::mat3(0.0f)) noexcept{
                return this->addVariableMat3 ( engine::String(varName), modifier, defaultValue );
            }

            [[maybe_unused]] Header& addVariableMat4      (const char * varName, DataTypeModifier modifier = DataTypeModifier::NONE, const glm::mat4& defaultValue= glm::mat4(0.0f)) noexcept{
                return this->addVariableMat4 ( engine::String(varName), modifier, defaultValue );
            }



            [[maybe_unused]] Header& addArrayVariable(const char * varName, DataType dataType, std::size_t length, DataTypeModifier modifier = DataTypeModifier::NONE) noexcept {
                return this->addArrayVariable( engine::String(varName), dataType, length, modifier );
            }

            [[maybe_unused]] Header& addArrayVariable(const char * varName, const Struct& structure, std::size_t length, DataTypeModifier modifier = DataTypeModifier::NONE) noexcept {
                return this->addArrayVariable( engine::String(varName), structure, length, modifier );
            }

            [[maybe_unused]] Header& addArrayStructVariable(const char * varName, const char* structureName, std::size_t length, DataTypeModifier modifier = DataTypeModifier::NONE) noexcept {
                return this->addArrayStructVariable( engine::String(varName), engine::String(structureName), length, modifier );
            }


            [[maybe_unused]] Header& addArrayVariableUInt8 (const char * varName, std::size_t length, DataTypeModifier modifier = DataTypeModifier::NONE) noexcept{
                return this->addArrayVariableUInt8( engine::String(varName), length, modifier );
            }

            [[maybe_unused]] Header& addArrayVariableUInt16(const char * varName, std::size_t length, DataTypeModifier modifier = DataTypeModifier::NONE) noexcept{
                return this->addArrayVariableUInt16( engine::String(varName), length, modifier );
            }

            [[maybe_unused]] Header& addArrayVariableUInt32(const char * varName, std::size_t length, DataTypeModifier modifier = DataTypeModifier::NONE) noexcept{
                return this->addArrayVariableUInt32( engine::String(varName), length, modifier );
            }

            [[maybe_unused]] Header& addArrayVariableUInt64(const char * varName, std::size_t length, DataTypeModifier modifier = DataTypeModifier::NONE) noexcept{
                return this->addArrayVariableUInt64( engine::String(varName), length, modifier );
            }


            [[maybe_unused]] Header& addArrayVariableInt8  (const char * varName, std::size_t length, DataTypeModifier modifier = DataTypeModifier::NONE) noexcept{
                return this->addArrayVariableInt8( engine::String(varName), length, modifier );
            }

            [[maybe_unused]] Header& addArrayVariableInt16 (const char * varName, std::size_t length, DataTypeModifier modifier = DataTypeModifier::NONE) noexcept{
                return this->addArrayVariableInt16( engine::String(varName), length, modifier );
            }

            [[maybe_unused]] Header& addArrayVariableInt32 (const char * varName, std::size_t length, DataTypeModifier modifier = DataTypeModifier::NONE) noexcept{
                return this->addArrayVariableInt32( engine::String(varName), length, modifier );
            }

            [[maybe_unused]] Header& addArrayVariableInt64 (const char * varName, std::size_t length, DataTypeModifier modifier = DataTypeModifier::NONE) noexcept{
                return this->addArrayVariableInt64( engine::String(varName), length, modifier );
            }


            [[maybe_unused]] Header& addArrayVariableFloat (const char * varName, std::size_t length, DataTypeModifier modifier = DataTypeModifier::NONE) noexcept{
                return this->addArrayVariableFloat( engine::String(varName), length, modifier );
            }

            [[maybe_unused]] Header& addArrayVariableDouble(const char * varName, std::size_t length, DataTypeModifier modifier = DataTypeModifier::NONE) noexcept{
                return this->addArrayVariableDouble( engine::String(varName), length, modifier );
            }

            [[maybe_unused]] Header& addArrayVariableBool  (const char * varName, std::size_t length, DataTypeModifier modifier = DataTypeModifier::NONE) noexcept{
                return this->addArrayVariableBool( engine::String(varName), length, modifier );
            }


            [[maybe_unused]] Header& addArrayVariableSampler2D(const char * varName, std::size_t length, DataTypeModifier modifier = DataTypeModifier::NONE) noexcept{
                return this->addArrayVariableSampler2D( engine::String(varName), length, modifier );
            }

            [[maybe_unused]] Header& addArrayVariableVec2     (const char * varName, std::size_t length, DataTypeModifier modifier = DataTypeModifier::NONE) noexcept{
                return this->addArrayVariableVec2( engine::String(varName), length, modifier );
            }

            [[maybe_unused]] Header& addArrayVariableVec3     (const char * varName, std::size_t length, DataTypeModifier modifier = DataTypeModifier::NONE) noexcept{
                return this->addArrayVariableVec3( engine::String(varName), length, modifier );
            }

            [[maybe_unused]] Header& addArrayVariableVec4     (const char * varName, std::size_t length, DataTypeModifier modifier = DataTypeModifier::NONE) noexcept{
                return this->addArrayVariableVec4( engine::String(varName), length, modifier );
            }

            [[maybe_unused]] Header& addArrayVariableMat3     (const char * varName, std::size_t length, DataTypeModifier modifier = DataTypeModifier::NONE) noexcept{
                return this->addArrayVariableMat3( engine::String(varName), length, modifier );
            }

            [[maybe_unused]] Header& addArrayVariableMat4     (const char * varName, std::size_t length, DataTypeModifier modifier = DataTypeModifier::NONE) noexcept{
                return this->addArrayVariableMat4( engine::String(varName), length, modifier );
            }


            //            engine::Array< engine::Shader::Header::Struct> & getDefinedStructures() noexcept;
            [[maybe_unused]] [[nodiscard]] engine::HashMap < engine::String, engine::Shader::Header::Struct > & getDefinedStructures() noexcept;

            [[maybe_unused]] void generate() const noexcept;
        };
    };
}

#endif //ENG1_SHADER_H

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
                SINT8 = _SHD_HEADER_DATA_TYPE_STD_TYPE_START,
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

                CHAR = SINT8,

                BYTE = UINT8,

                SHORT = SINT16,
                SHORT_INT = SINT16,

                UNSIGNED_SHORT = UINT16,
                UNSIGNED_SHORT_INT = UINT16,

                INT = SINT32,

                UNSIGNED = UINT32,
                UNSIGNED_INT = UINT32,

                LONG = SINT64,
                LONG_LONG = SINT64,
                LONG_LONG_INT = SINT64,

                UNSIGNED_LONG = UINT64,
                UNSIGNED_LONG_LONG = UINT64,
                UNSIGNED_LONG_LONG_INT = UINT64,

                FLOAT = FLOAT32,
                DOUBLE = FLOAT64,
                
                SINT8_ARRAY = _SHD_HEADER_DATA_TYPE_STD_TYPE_ARR_START,
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

                CHAR_ARRAY = SINT8_ARRAY,

                BYTE_ARRAY = UINT8_ARRAY,

                SHORT_ARRAY = SINT16_ARRAY,
                SHORT_INT_ARRAY = SINT16_ARRAY,

                UNSIGNED_SHORT_ARRAY = UINT16_ARRAY,
                UNSIGNED_SHORT_INT_ARRAY = UINT16_ARRAY,

                INT_ARRAY = SINT32_ARRAY,

                UNSIGNED_ARRAY = UINT32_ARRAY,
                UNSIGNED_INT_ARRAY = UINT32_ARRAY,

                LONG_ARRAY = SINT64_ARRAY,
                LONG_LONG_ARRAY = SINT64_ARRAY,
                LONG_LONG_INT_ARRAY = SINT64_ARRAY,

                UNSIGNED_LONG_ARRAY = UINT64_ARRAY,
                UNSIGNED_LONG_LONG_ARRAY = UINT64_ARRAY,
                UNSIGNED_LONG_LONG_INT_ARRAY = UINT64_ARRAY,

                FLOAT_ARRAY = FLOAT32_ARRAY,
                DOUBLE_ARRAY = FLOAT64_ARRAY,

                SAMPLER_2D = _SHD_HEADER_DATA_TYPE_STD_SHD_TYPE_START,

                VEC_2,
                VEC_3,
                VEC_4,

                MAT_3,
                MAT_4,


                SAMPLER_2D_ARRAY = _SHD_HEADER_DATA_TYPE_STD_SHD_TYPE_ARR_START,

                VEC_2_ARRAY,
                VEC_3_ARRAY,
                VEC_4_ARRAY,

                MAT_3_ARRAY,
                MAT_4_ARRAY,

                STRUCT = _SHD_HEADER_DATA_TYPE_STD_STRUCT_TYPE_START,
                STRUCT_ARRAY = _SHD_HEADER_DATA_TYPE_STD_STRUCT_TYPE_ARR_START
            };

            static engine::String dataTypeToString(DataType) noexcept;
            static engine::String dataTypeModifierToString(DataTypeModifier) noexcept;
            
            static engine::String dataTypeDeclaration(DataType) noexcept;
            static engine::String dataTypeModifierDeclaration(DataTypeModifier) noexcept;

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
                explicit Struct(const char*) noexcept;
                explicit Struct(const engine::String&) noexcept;

                engine::Array < engine::NonConstexprPair < uint8, engine::String > > & getVariables() noexcept;

                // engine::HashMap < uint8, engine::String > & getVariables() noexcept;
//                engine::HashMap < engine::Shader::Header::DataType, engine::String >& getVariables() noexcept;
                engine::HashMap < engine::String, uint64 > & getArraySizes() noexcept;
                engine::HashMap < engine::String, engine::String > & getStructureVariableTypes() noexcept;

                Struct& addVariable(const engine::String&, DataType) noexcept;
                Struct& addVariable(const char*, DataType) noexcept;
                Struct& addVariable(const Struct&, const char*) noexcept;
                Struct& addStructVariable(const char*, const char*) noexcept;

                Struct& addVariableUInt8  (const engine::String&) noexcept;
                Struct& addVariableUInt16 (const engine::String&) noexcept;
                Struct& addVariableUInt32 (const engine::String&) noexcept;
                Struct& addVariableUInt64 (const engine::String&) noexcept;

                Struct& addVariableInt8   (const engine::String&) noexcept;
                Struct& addVariableInt16  (const engine::String&) noexcept;
                Struct& addVariableInt32  (const engine::String&) noexcept;
                Struct& addVariableInt64  (const engine::String&) noexcept;

                Struct& addVariableFloat  (const engine::String&) noexcept;
                Struct& addVariableDouble (const engine::String&) noexcept;
                Struct& addVariableBool   (const engine::String&) noexcept;

                Struct& addVariableSampler2D (const engine::String&) noexcept;

                Struct& addVariableVec2      (const engine::String&) noexcept;
                Struct& addVariableVec3      (const engine::String&) noexcept;
                Struct& addVariableVec4      (const engine::String&) noexcept;
                Struct& addVariableMat3      (const engine::String&) noexcept;
                Struct& addVariableMat4      (const engine::String&) noexcept;


                Struct& addArrayVariable(const engine::String&, DataType, std::size_t) noexcept;
                Struct& addArrayVariable(const Struct&, const char*, std::size_t) noexcept;
                Struct& addArrayVariable(const Struct&, const engine::String&, std::size_t) noexcept;
                Struct& addArrayStructVariable(const engine::String&, const engine::String&,std::size_t) noexcept;

                Struct& addArrayVariableUInt16(const engine::String&, std::size_t) noexcept;
                Struct& addArrayVariableUInt32(const engine::String&, std::size_t) noexcept;
                Struct& addArrayVariableUInt8 (const engine::String&, std::size_t) noexcept;
                Struct& addArrayVariableUInt64(const engine::String&, std::size_t) noexcept;

                Struct& addArrayVariableInt8  (const engine::String&, std::size_t) noexcept;
                Struct& addArrayVariableInt16 (const engine::String&, std::size_t) noexcept;
                Struct& addArrayVariableInt32 (const engine::String&, std::size_t) noexcept;
                Struct& addArrayVariableInt64 (const engine::String&, std::size_t) noexcept;

                Struct& addArrayVariableFloat (const engine::String&, std::size_t) noexcept;
                Struct& addArrayVariableDouble(const engine::String&, std::size_t) noexcept;
                Struct& addArrayVariableBool  (const engine::String&, std::size_t) noexcept;

                Struct& addArrayVariableSampler2D(const engine::String&, std::size_t) noexcept;
                Struct& addArrayVariableVec2     (const engine::String&, std::size_t) noexcept;
                Struct& addArrayVariableVec3     (const engine::String&, std::size_t) noexcept;
                Struct& addArrayVariableVec4     (const engine::String&, std::size_t) noexcept;
                Struct& addArrayVariableMat3     (const engine::String&, std::size_t) noexcept;
                Struct& addArrayVariableMat4     (const engine::String&, std::size_t) noexcept;


                Struct& addVariableUInt8  (const char*) noexcept;
                Struct& addVariableUInt16 (const char*) noexcept;
                Struct& addVariableUInt32 (const char*) noexcept;
                Struct& addVariableUInt64 (const char*) noexcept;

                Struct& addVariableInt8   (const char*) noexcept;
                Struct& addVariableInt16  (const char*) noexcept;
                Struct& addVariableInt32  (const char*) noexcept;
                Struct& addVariableInt64  (const char*) noexcept;

                Struct& addVariableFloat  (const char*) noexcept;
                Struct& addVariableDouble (const char*) noexcept;
                Struct& addVariableBool   (const char*) noexcept;

                Struct& addVariableSampler2D (const char*) noexcept;

                Struct& addVariableVec2      (const char*) noexcept;
                Struct& addVariableVec3      (const char*) noexcept;
                Struct& addVariableVec4      (const char*) noexcept;
                Struct& addVariableMat3      (const char*) noexcept;
                Struct& addVariableMat4      (const char*) noexcept;


                Struct& addArrayVariable(const char*, DataType, std::size_t) noexcept;
                Struct& addArrayStructVariable(const char*, const char*, std::size_t) noexcept;

                Struct& addArrayVariableUInt8 (const char*, std::size_t) noexcept;
                Struct& addArrayVariableUInt16(const char*, std::size_t) noexcept;
                Struct& addArrayVariableUInt32(const char*, std::size_t) noexcept;
                Struct& addArrayVariableUInt64(const char*, std::size_t) noexcept;

                Struct& addArrayVariableInt8  (const char*, std::size_t) noexcept;
                Struct& addArrayVariableInt16 (const char*, std::size_t) noexcept;
                Struct& addArrayVariableInt32 (const char*, std::size_t) noexcept;
                Struct& addArrayVariableInt64 (const char*, std::size_t) noexcept;

                Struct& addArrayVariableFloat (const char*, std::size_t) noexcept;
                Struct& addArrayVariableDouble(const char*, std::size_t) noexcept;
                Struct& addArrayVariableBool  (const char*, std::size_t) noexcept;

                Struct& addArrayVariableSampler2D(const char*, std::size_t) noexcept;
                Struct& addArrayVariableVec2     (const char*, std::size_t) noexcept;
                Struct& addArrayVariableVec3     (const char*, std::size_t) noexcept;
                Struct& addArrayVariableVec4     (const char*, std::size_t) noexcept;
                Struct& addArrayVariableMat3     (const char*, std::size_t) noexcept;
                Struct& addArrayVariableMat4     (const char*, std::size_t) noexcept;

                Struct& settleVariables() noexcept;

                engine::String toString() const noexcept;
                
            };

        private:
            engine::String _code;
            engine::String _name;
            engine::String _path {engine::String(__SHADERS_PATH__)};
            bool _generateIncludeGuards {true};

            engine::HashMap <engine::String, engine::Shader::Header::Struct> _definedStructures;

            engine::String includeGuardTop() const noexcept;
            engine::String includeGuardBottom() const noexcept;

        public:
            Header() = delete;
            Header(const char*, bool = true) noexcept;
            Header(const engine::String&, bool = true) noexcept;

            Header& setRelativePath(const char*) noexcept;
            Header& setAbsolutePath(const char*) noexcept;

            Header& clear() noexcept;

            Header& addDefine(const engine::String&, const engine::String& = engine::String("")) noexcept;

            Header& addIfDefine(const engine::String&) noexcept;
            Header& addIfNotDefine(const engine::String&) noexcept;
            Header& addEndIf() noexcept;

            Header& addStruct(const Shader::Header::Struct&) noexcept;

            Header& addCode(const char*) noexcept;
            Header& addCode(const engine::String&) noexcept;
            Header& addCode(const std::string&) noexcept;

            Header& addVariable(const engine::String&, DataType, DataTypeModifier = DataTypeModifier::NONE) noexcept;
            Header& addVariable(const engine::String&, const Struct&, DataTypeModifier = DataTypeModifier::NONE) noexcept;
            Header& addStructVariable(const engine::String&, const char*, DataTypeModifier = DataTypeModifier::NONE) noexcept;

            Header& addVariableUInt8  (const engine::String&, DataTypeModifier = DataTypeModifier::NONE, uint8  = 0U ) noexcept;
            Header& addVariableUInt16 (const engine::String&, DataTypeModifier = DataTypeModifier::NONE, uint16 = 0U ) noexcept;
            Header& addVariableUInt32 (const engine::String&, DataTypeModifier = DataTypeModifier::NONE, uint32 = 0UL) noexcept;
            Header& addVariableUInt64 (const engine::String&, DataTypeModifier = DataTypeModifier::NONE, uint64 = 0UL) noexcept;

            Header& addVariableInt8   (const engine::String&, DataTypeModifier = DataTypeModifier::NONE, int8   = 0U ) noexcept;
            Header& addVariableInt16  (const engine::String&, DataTypeModifier = DataTypeModifier::NONE, int16  = 0U ) noexcept;
            Header& addVariableInt32  (const engine::String&, DataTypeModifier = DataTypeModifier::NONE, int32  = 0UL) noexcept;
            Header& addVariableInt64  (const engine::String&, DataTypeModifier = DataTypeModifier::NONE, int64  = 0UL) noexcept;

            Header& addVariableFloat  (const engine::String&, DataTypeModifier = DataTypeModifier::NONE, float = 0.0f) noexcept;
            Header& addVariableDouble (const engine::String&, DataTypeModifier = DataTypeModifier::NONE, double = 0.0) noexcept;
            Header& addVariableBool   (const engine::String&, DataTypeModifier = DataTypeModifier::NONE, bool = false) noexcept;

            Header& addVariableSampler2D (const engine::String&, DataTypeModifier = DataTypeModifier::NONE) noexcept;

            Header& addVariableVec2      (const engine::String&, DataTypeModifier = DataTypeModifier::NONE, const glm::vec2& = glm::vec2(0.0f)) noexcept;
            Header& addVariableVec3      (const engine::String&, DataTypeModifier = DataTypeModifier::NONE, const glm::vec3& = glm::vec3(0.0f)) noexcept;
            Header& addVariableVec4      (const engine::String&, DataTypeModifier = DataTypeModifier::NONE, const glm::vec4& = glm::vec4(0.0f)) noexcept;
            Header& addVariableMat3      (const engine::String&, DataTypeModifier = DataTypeModifier::NONE, const glm::mat3& = glm::mat3(0.0f)) noexcept;
            Header& addVariableMat4      (const engine::String&, DataTypeModifier = DataTypeModifier::NONE, const glm::mat4& = glm::mat4(0.0f)) noexcept;


            Header& addArrayVariable(const engine::String&, DataType, std::size_t, DataTypeModifier = DataTypeModifier::NONE) noexcept;
            Header& addArrayVariable(const engine::String&, const Struct&, std::size_t, DataTypeModifier = DataTypeModifier::NONE) noexcept;
            Header& addArrayStructVariable(const engine::String&, const char*, std::size_t, DataTypeModifier = DataTypeModifier::NONE) noexcept;

            Header& addArrayVariableUInt16(const engine::String&, std::size_t, DataTypeModifier = DataTypeModifier::NONE) noexcept;
            Header& addArrayVariableUInt32(const engine::String&, std::size_t, DataTypeModifier = DataTypeModifier::NONE) noexcept;
            Header& addArrayVariableUInt8 (const engine::String&, std::size_t, DataTypeModifier = DataTypeModifier::NONE) noexcept;
            Header& addArrayVariableUInt64(const engine::String&, std::size_t, DataTypeModifier = DataTypeModifier::NONE) noexcept;

            Header& addArrayVariableInt8  (const engine::String&, std::size_t, DataTypeModifier = DataTypeModifier::NONE) noexcept;
            Header& addArrayVariableInt16 (const engine::String&, std::size_t, DataTypeModifier = DataTypeModifier::NONE) noexcept;
            Header& addArrayVariableInt32 (const engine::String&, std::size_t, DataTypeModifier = DataTypeModifier::NONE) noexcept;
            Header& addArrayVariableInt64 (const engine::String&, std::size_t, DataTypeModifier = DataTypeModifier::NONE) noexcept;

            Header& addArrayVariableFloat (const engine::String&, std::size_t, DataTypeModifier = DataTypeModifier::NONE) noexcept;
            Header& addArrayVariableDouble(const engine::String&, std::size_t, DataTypeModifier = DataTypeModifier::NONE) noexcept;
            Header& addArrayVariableBool  (const engine::String&, std::size_t, DataTypeModifier = DataTypeModifier::NONE) noexcept;

            Header& addArrayVariableSampler2D(const engine::String&, std::size_t, DataTypeModifier = DataTypeModifier::NONE) noexcept;
            Header& addArrayVariableVec2     (const engine::String&, std::size_t, DataTypeModifier = DataTypeModifier::NONE) noexcept;
            Header& addArrayVariableVec3     (const engine::String&, std::size_t, DataTypeModifier = DataTypeModifier::NONE) noexcept;
            Header& addArrayVariableVec4     (const engine::String&, std::size_t, DataTypeModifier = DataTypeModifier::NONE) noexcept;
            Header& addArrayVariableMat3     (const engine::String&, std::size_t, DataTypeModifier = DataTypeModifier::NONE) noexcept;
            Header& addArrayVariableMat4     (const engine::String&, std::size_t, DataTypeModifier = DataTypeModifier::NONE) noexcept;

//            engine::Array< engine::Shader::Header::Struct> & getDefinedStructures() noexcept;
            engine::HashMap < engine::String, engine::Shader::Header::Struct > & getDefinedStructures() noexcept;

            void generate() noexcept;
        };
    };
}

#endif //ENG1_SHADER_H

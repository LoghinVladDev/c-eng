//
// Created by vladl on 13/07/2020.
//

#include "Shader.h"
#include <obj/util/data/Set.h>
#include <obj/util/data/Map.h>

std::string engine::Shader::_pathToShadersFolder = std::string(__NO_PATH_GIVEN__);

//static std::string& trimString(std::string& str) {
//    while(str[0] == ' ' && str.length() > 0)
//        str.erase(str.begin());
//    while(str[str.length()] == '\0' && str[str.length() - 1] == ' ' && str.length() > 0)
//        str.erase(str.end() - 1);
//
//    return str;
//}

/**
 *
 * Recursive Include Parser
 */

/**
 *
 * @param codeLine
 * @return
 */
[[maybe_unused]] static INC_SHD_STR_LINE_PROP includeFileInShaderAnalyseLine ( const engine::String& codeLine ) noexcept {
    INC_SHD_STR_LINE_PROP properties;
    _INIT_INC_SHD_STR_LINE_PROP(properties)

    engine::Array < engine::String > lineBits = codeLine.split(' ');
    if( ! _INC_SHD_STR_LINE_IS_TOKEN( lineBits[0] ) )
        _INC_SHD_STR_LINE_PROP_REG(properties)

    INC_SHD_ENUM_LINE_TYPE tokenType;

    _INC_SHD_STR_LINE_TYPE_STR_TO_ENUM(lineBits[0], tokenType)

    switch (tokenType) {
        case INCLUDE_TOKEN_CODE_LINE        : _INC_SHD_STR_LINE_PROP_INC(properties, lineBits)
        case END_IF_CODE_LINE               : _INC_SHD_STR_LINE_PROP_ENDIF(properties, lineBits)
        case IF_N_DEF_CODE_LINE             : _INC_SHD_STR_LINE_PROP_IFNDEF(properties, lineBits)
        case IF_DEF_CODE_LINE               : _INC_SHD_STR_LINE_PROP_IFDEF(properties, lineBits)
        case UNDEF_TOKEN_CODE_LINE          : _INC_SHD_STR_LINE_PROP_UNDEF(properties, lineBits)
        case DEF_TOKEN_CODE_LINE            : _INC_SHD_STR_LINE_PROP_DEF(properties, lineBits)
        default                             : break;
    }

    return properties;
}

/**
 * 
 * @return true if continue, else skip to corresponding endif;
 */
// [[maybe_unused]] static bool includeFileInShaderProcessToken(INC_SHD_STR_LINE_PROP lineProperties, engine::String& code, engine::SimpleSet < engine::NonConstexprPair < engine::String, engine::String > > & defineTokens) noexcept {
[[maybe_unused]] static bool includeFileInShaderProcessToken ( INC_SHD_STR_LINE_PROP lineProperties, engine::String& code, engine::HashMap < engine::String, engine::String> & defineTokens ) noexcept {
    switch ( lineProperties.lineType ) {
    //    case INCLUDE_TOKEN_CODE_LINE         : 
        case DEF_TOKEN_CODE_LINE : 

            // std::cout << "Define ! \n";

            code += ( engine::String(_TOKEN_DEFINE) + " " + (* lineProperties.tokenName ) + " " + (* lineProperties.tokenReplaceValue) );   
            // defineTokens.insert( engine::NonConstexprPair <engine::String, engine::String> ( (*lineProperties.tokenName), (*lineProperties.tokenReplaceValue) ) );
            defineTokens.put( *lineProperties.tokenName, *lineProperties.tokenReplaceValue );

            // std::cout << defineTokens << '\n';

            return true;
        
        case IF_DEF_CODE_LINE : 
            // std::cout << "If defined! \n";
            // return true;
            return defineTokens.contains(*lineProperties.tokenName);
        case IF_N_DEF_CODE_LINE : 
//            std::cout << "If not defined\n";
            return ! defineTokens.contains(*lineProperties.tokenName);

        case UNDEF_TOKEN_CODE_LINE :
            defineTokens.remove(*lineProperties.tokenName);
            return true;

        case END_IF_CODE_LINE : 
            // std::cout << "END IF\n";
            return true;

        default :
            break;
    }    
    return true;
}

// [[maybe_unused]] static engine::String includeFileInShaderRec(const char* path, engine::SimpleSet < engine::NonConstexprPair < engine::String, engine::String > >& defineTokens ) noexcept {
[[maybe_unused]] static engine::String includeFileInShaderRec(const char* path, engine::HashMap < engine::String, engine::String >& defineTokens ) noexcept {
    std::cout << "Include : " << path << '\n';

    engine::String code;
    engine::String codeLine;
    std::ifstream includedFile;

    int ifDepth = 0;

    includedFile.open(path);

    try {
        while(engine::String::getline(includedFile, codeLine)) {

            INC_SHD_STR_LINE_PROP lineProperties = includeFileInShaderAnalyseLine ( codeLine );

            if(_INC_SHD_STR_PROP_IS_TOKEN(lineProperties)) {
                // _INC_SHD_STR_PRINT_STR(lineProperties);

                if(lineProperties.lineType == INC_SHD_ENUM_LINE_TYPE::INCLUDE_TOKEN_CODE_LINE) {

                    engine::String dirPath(path);
                    code += includeFileInShaderRec(
                        ( dirPath.replace(dirPath.findLast("/"), dirPath.length(), "/") + (*lineProperties.includeFileRelativePath).trim("\" ") ).c_str(),
                        defineTokens 
                    );

                } else {

                    if (ifDepth == 0 && !includeFileInShaderProcessToken(lineProperties, code, defineTokens)) {
                        ifDepth++;
                    }

                    if (ifDepth > 0 && lineProperties.lineType == INC_SHD_ENUM_LINE_TYPE::END_IF_CODE_LINE)
                        ifDepth--;

                    std::cout << " if depth : " << ifDepth << '\n';

                    if (ifDepth > 0) {
                        _INC_SHD_STR_CLEAR_STR(lineProperties)
                        continue;
                    }
                }
            } else if(ifDepth == 0) {
                code += codeLine + "\n";
            }

            _INC_SHD_STR_CLEAR_STR(lineProperties)
        }
        INC_SHD_STR_LINE_PROP lineProperties = includeFileInShaderAnalyseLine( codeLine );

        if(_INC_SHD_STR_PROP_IS_TOKEN(lineProperties)) {
            // _INC_SHD_STR_PRINT_STR(lineProperties);

            includeFileInShaderProcessToken(lineProperties, code, defineTokens);
        } else {
            code += codeLine;
        }

        _INC_SHD_STR_CLEAR_STR(lineProperties)
    } catch (const std::exception& e) {
        std::cout << "File parse exception : " << e.what() << '\n';
    }

    std::cout << "Included File : " << path << '\n';

    std::cout << "\n\nFinalCode : \n" << code << '\n';

    return code;
}

/**
 * TODO : implement shader include folders.
 * TODO : implement once engine::List is done
 * @param path
 * @param codeContainer
 * @return
 */
[[maybe_unused]] static engine::String& includeFileRelativeInShaderRecInit(const char* includerPath, const char* relativePath, engine::String& codeContainer) noexcept {

    // engine::SimpleSet < engine::NonConstexprPair < engine::String, engine::String > > includeTokens;
    engine::HashMap < engine::String, engine::String > includeTokens;
    engine::String currentDir(includerPath);
    currentDir.replace(currentDir.findLast('/'), currentDir.length(), "/");

    std::cout << "Include file start : " << relativePath << ", requested from : " << currentDir << '\n';
    includeFileInShaderRec( (currentDir + relativePath).c_str(), includeTokens);

    exit(0);

    return codeContainer;
}

/**
 *
 * engine::Shader Definitions.
 */

/**
 *
 * @param vertexPath
 * @param fragmentPath
 * @param relativePath
 * @param enableDiagnostic
 */
[[maybe_unused]] engine::Shader::Shader(const char *vertexPath, const char *fragmentPath, bool relativePath, bool enableDiagnostic) noexcept {
    std::ifstream vertexFile;
    std::ifstream fragmentFile;

    engine::String vertexCode;
    engine::String fragmentCode;

    engine::String includesExpanded;
    engine::String includerPath;

    engine::String vertexCodeLine;

    this->_fragmentFilename = fragmentPath;
    this->_vertexFilename = vertexPath;

//    vertexFile.exceptions( std::ifstream::failbit | std::ifstream::badbit );
//    fragmentFile.exceptions( std::ifstream::failbit | std::ifstream::badbit );

    try{
        if( !relativePath ) {
            vertexFile.open( vertexPath );
//            fragmentFile.open( fragmentPath );
            includerPath = vertexPath;
        } else {
            vertexFile.open( Shader::_pathToShadersFolder + vertexPath );
//            fragmentFile.open( Shader::_pathToShadersFolder + fragmentPath );
            includerPath = (Shader::_pathToShadersFolder + vertexPath);
        }

        while(engine::String::getline(vertexFile, vertexCodeLine)) {
            vertexCodeLine.trim();

            if(vertexCodeLine.contains(_TOKEN_INCLUDE)) {
                vertexCodeLine.replaceFirst(_TOKEN_INCLUDE, "");
//                std::cout << "Include : " << vertexCodeLine.trim(" \"\r\n\t") << '\n';
                includeFileRelativeInShaderRecInit(includerPath.c_str(), vertexCodeLine.trim(" \"\r\n\t").c_str(), includesExpanded);
            }
            else
                std::cout << vertexCodeLine << '\n';

            if(vertexFile.eof())
                break;
        }

        vertexCodeLine.trim();
        std::cout << vertexCodeLine << '\n';

        vertexFile.close();
//        fragmentFile.close();
    } catch (std::ifstream::failure& exception) {
        std::cout << "Shader read exception : " << exception.what() << std::endl;
        this->failed = true;
        return;
    }

    return;

    int32 vertexID;
    int32 fragmentID;
    const char* vertexCodePtr = vertexCode.c_str();
    const char* fragmentCodePtr = fragmentCode.c_str();

    vertexID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexID, 1, &vertexCodePtr, nullptr);
    glCompileShader(vertexID);

    if(enableDiagnostic)
        Shader::diagnoseShaderCompilation(vertexID, this->_vertexFilename);

    fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentID, 1, &fragmentCodePtr, nullptr);
    glCompileShader(fragmentID);

    if(enableDiagnostic)
        Shader::diagnoseShaderCompilation(fragmentID, this->_fragmentFilename);

    this->ID = glCreateProgram();
    glAttachShader(this->ID, vertexID);
    glAttachShader(this->ID, fragmentID);
    glLinkProgram(this->ID);

    if(enableDiagnostic)
        Shader::diagnoseProgramCompilation(this->ID);

    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);
}

[[maybe_unused]] engine::Shader::Shader(const std::string & vertexPath, const std::string & fragmentPath, bool relativePath, bool enableDiagnostic) noexcept {
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vertexFile;
    std::ifstream fragmentFile;

    this->_fragmentFilename = fragmentPath;
    this->_vertexFilename = vertexPath;

    vertexFile.exceptions( std::ifstream::failbit | std::ifstream::badbit );
    fragmentFile.exceptions( std::ifstream::failbit | std::ifstream::badbit );

    try{
        if( !relativePath ) {
            vertexFile.open( vertexPath );
            fragmentFile.open( fragmentPath );
        } else {
            vertexFile.open( Shader::_pathToShadersFolder + vertexPath );
            fragmentFile.open( Shader::_pathToShadersFolder + fragmentPath );
        }
        std::stringstream vertexStream;
        std::stringstream fragmentStream;

        vertexStream << vertexFile.rdbuf();
        fragmentStream << fragmentFile.rdbuf();

        vertexFile.close();
        fragmentFile.close();

        vertexCode = vertexStream.str();
        fragmentCode = fragmentStream.str();
    } catch (std::ifstream::failure& exception) {
        std::cout << "Shader read exception : " << exception.what() << std::endl;
        this->failed = true;
        return;
    }

    int32 vertexID;
    int32 fragmentID;
    const char* vertexCodePtr = vertexCode.c_str();
    const char* fragmentCodePtr = fragmentCode.c_str();

    vertexID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexID, 1, &vertexCodePtr, nullptr);
    glCompileShader(vertexID);

    if(enableDiagnostic)
        Shader::diagnoseShaderCompilation(vertexID, this->_vertexFilename);

    fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentID, 1, &fragmentCodePtr, nullptr);
    glCompileShader(fragmentID);

    if(enableDiagnostic)
        Shader::diagnoseShaderCompilation(fragmentID, this->_fragmentFilename);

    this->ID = glCreateProgram();
    glAttachShader(this->ID, vertexID);
    glAttachShader(this->ID, fragmentID);
    glLinkProgram(this->ID);

    if(enableDiagnostic)
        Shader::diagnoseProgramCompilation(this->ID);

    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);
}

[[maybe_unused]] void engine::Shader::use() const noexcept {
    glUseProgram(this->ID);
}

[[maybe_unused]] engine::Shader& engine::Shader::setBool(const std::string & name, bool value) noexcept {
    glUniform1i ( glGetUniformLocation(ID, name.c_str()), (int) value );
    return *this;
}

[[maybe_unused]] engine::Shader& engine::Shader::setInt(const std::string & name, int value) noexcept {
    glUniform1i ( glGetUniformLocation(ID, name.c_str()), (int) value );
    return *this;
}

[[maybe_unused]] engine::Shader& engine::Shader::setFloat(const std::string & name, float value) noexcept {
    glUniform1f ( glGetUniformLocation(ID, name.c_str()), value );
    return *this;
}

[[maybe_unused]] engine::Shader& engine::Shader::setVec3(const std::string & name, const engine::VectorF & value) noexcept {
    glUniform3f ( glGetUniformLocation(ID, name.c_str()), value.getX(), value.getY(), value.getZ() );
    return *this;
}

[[maybe_unused]] engine::Shader& engine::Shader::setVec4(const std::string & name, const engine::Vector4F & value) noexcept {
    glUniform4f ( glGetUniformLocation(ID, name.c_str()), value.getX(), value.getY(), value.getZ(), value.getT() );
    return *this;
}

[[maybe_unused]] engine::Shader& engine::Shader::setVec3d(const std::string & name, const engine::VectorD & value) noexcept {
//    glUniform3d ( glGetUniformLocation(ID, name.c_str()), value.getX(), value.getY(), value.getZ() );
    return *this;
}

[[maybe_unused]] engine::Shader& engine::Shader::setVec4d(const std::string & name, const engine::Vector4D & value) noexcept {
//    glUniform4d ( glGetUniformLocation(ID, name.c_str()), value.getX(), value.getY(), value.getZ(), value.getT() );
    return *this;
}

[[maybe_unused]] engine::Shader& engine::Shader::setDouble(const std::string & name, double value) noexcept {
    glUniform1d ( glGetUniformLocation(ID, name.c_str()), value );
    return *this;
}

engine::Shader &engine::Shader::setVec3(const std::string & name, const glm::vec3 & value) noexcept {
    glUniform3f ( glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z );
    return *this;
}

[[maybe_unused]] engine::Shader &engine::Shader::setVec4(const std::string & name, const glm::vec4 & value) noexcept {
    glUniform4f ( glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z, value.w );
    return *this;
}

[[maybe_unused]] engine::Shader &engine::Shader::setMat3(const std::string & name, const glm::mat3 & value) noexcept {
    glUniformMatrix3fv ( glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value) );
    return *this;
}

engine::Shader &engine::Shader::setMat4(const std::string & name, const glm::mat4 & value) noexcept {
    glUniformMatrix4fv ( glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value) );
    return *this;
}

void engine::Shader::diagnoseProgramCompilation(int programID) noexcept {
    int32 successStatus;
    char infoLog[512];

    glGetProgramiv(programID, GL_LINK_STATUS, &successStatus);
    if( !successStatus ){
        glGetProgramInfoLog( programID, 512, nullptr, infoLog );
        std::cout << "Shader linking failed" << infoLog << std::endl;
    } else {
        std::cout << "Shader linking success" << std::endl;
    }
}

void engine::Shader::diagnoseShaderCompilation(int shaderID, const std::string& shaderFilename) noexcept {
    int32 successStatus;
    char infoLog[512];

    glGetShaderiv( shaderID, GL_COMPILE_STATUS, &successStatus );
    if( !successStatus ) {
        glGetShaderInfoLog( shaderID, 512, nullptr, infoLog );
        std::cout << shaderFilename << " : " << "Shader compilation failed : " << infoLog << std::endl;
    } else {
        std::cout << "Shader compilation success" << std::endl;
    }
}

[[maybe_unused]] [[nodiscard]] int engine::Shader::getID() const noexcept {
    return this->ID;
}

engine::Shader::~Shader() {
    if(this->ID != 0U)
        glDeleteProgram(this->ID);
}

void engine::Shader::setShadersFolder(const std::string & path) noexcept {
    Shader::_pathToShadersFolder = path;
}

void engine::Shader::setShadersFolder(const char * path) noexcept {
    Shader::_pathToShadersFolder = std::string(path);
}



/**
 * Shader Header Struct Definition start
 * 
 * 
 */
engine::Shader::Header::Struct::Struct(const char * name) noexcept {
    this->_name = engine::String(name);
}

engine::Shader::Header::Struct::Struct(const engine::String & name) noexcept {
    this->_name = name;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addVariable(const engine::String& varName, engine::Shader::Header::DataType dataType) noexcept {
    if( !_SHD_HEADER_DATA_IS_VAR_TYPE(dataType) )
        return *this;

    this->_variables += engine::NonConstexprPair < uint8, engine::String > ( dataType, varName );
    // this->_variables.put(dataType, varName);
    return *this;
}

engine::Shader::Header::Struct& engine::Shader::Header::Struct::addVariable(const char* varName, engine::Shader::Header::DataType dataType) noexcept {
    if( !_SHD_HEADER_DATA_IS_VAR_TYPE(dataType) )
        return *this;

    this->_variables += engine::NonConstexprPair < uint8, engine::String > ( dataType, engine::String(varName) );
    // this->_variables.put(dataType, engine::String(varName));
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addVariable(const Struct & varType, const char* varName) noexcept {

    this->_variables += engine::NonConstexprPair < uint8, engine::String > ( engine::Shader::Header::DataType::STRUCT, engine::String(varName) );
    this->_structureTypeNames.put( engine::String(varName), varType._name );

    // this->_variables.put(engine::Shader::Header::DataType::STRUCT, varType._name);
    return *this;
}

engine::Shader::Header::Struct& engine::Shader::Header::Struct::addStructVariable(const char* structName, const char* varName) noexcept {
    this->_variables += engine::NonConstexprPair < uint8, engine::String > ( engine::Shader::Header::DataType::STRUCT, engine::String(varName) );
    // this->_variables.put(engine::Shader::Header::DataType::STRUCT, engine::String(varName));
    this->_structureTypeNames.put(engine::String(varName), engine::String(structName));
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addVariableUInt8 (const engine::String& varName) noexcept {
    this->_variables += engine::NonConstexprPair < uint8, engine::String > ( engine::Shader::Header::DataType::UINT8, engine::String(varName) );
    // this->_variables.put(engine::Shader::Header::DataType::UINT8, varName);
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addVariableUInt16( const engine::String& varName ) noexcept {
    this->_variables += engine::NonConstexprPair < uint8, engine::String > ( engine::Shader::Header::DataType::UINT16, engine::String(varName) );
    // this->_variables.put(engine::Shader::Header::DataType::UINT16, varName); 
    return *this; 
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addVariableUInt32( const engine::String& varName ) noexcept {
    this->_variables += engine::NonConstexprPair < uint8, engine::String > ( engine::Shader::Header::DataType::UINT32, engine::String(varName) );
    // this->_variables.put(engine::Shader::Header::DataType::UINT32, varName);
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addVariableUInt64( const engine::String& varName ) noexcept {
    this->_variables += engine::NonConstexprPair < uint8, engine::String > ( engine::Shader::Header::DataType::UINT64, engine::String(varName) );
    // this->_variables.put(engine::Shader::Header::DataType::UINT64, varName);
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addVariableInt8( const engine::String& varName ) noexcept {
    this->_variables += engine::NonConstexprPair < uint8, engine::String > ( engine::Shader::Header::DataType::SINT8, engine::String(varName) );
    // this->_variables.put(engine::Shader::Header::DataType::SINT8, varName);
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addVariableInt16( const engine::String& varName ) noexcept {
    this->_variables += engine::NonConstexprPair < uint8, engine::String > ( engine::Shader::Header::DataType::SINT16, engine::String(varName) );
    // this->_variables.put(engine::Shader::Header::DataType::SINT16, varName);
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addVariableInt32( const engine::String& varName ) noexcept {
    this->_variables += engine::NonConstexprPair < uint8, engine::String > ( engine::Shader::Header::DataType::SINT32, engine::String(varName) );
    // this->_variables.put(engine::Shader::Header::DataType::SINT32, varName);
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addVariableInt64( const engine::String& varName ) noexcept {
    this->_variables += engine::NonConstexprPair < uint8, engine::String > ( engine::Shader::Header::DataType::SINT64, engine::String(varName) );
    // this->_variables.put(engine::Shader::Header::DataType::SINT64, varName);
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addVariableFloat( const engine::String& varName ) noexcept {
    this->_variables += engine::NonConstexprPair < uint8, engine::String > ( engine::Shader::Header::DataType::FLOAT32, engine::String(varName) );
    // this->_variables.put(engine::Shader::Header::DataType::FLOAT32, varName);
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addVariableDouble( const engine::String& varName ) noexcept {
    this->_variables += engine::NonConstexprPair < uint8, engine::String > ( engine::Shader::Header::DataType::FLOAT64, engine::String(varName) );
    // this->_variables.put(engine::Shader::Header::DataType::FLOAT64, varName);
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addVariableBool( const engine::String& varName ) noexcept {
    this->_variables += engine::NonConstexprPair < uint8, engine::String > ( engine::Shader::Header::DataType::BOOL, engine::String(varName) );
    // this->_variables.put(engine::Shader::Header::DataType::BOOL, varName);
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addVariableSampler2D( const engine::String& varName ) noexcept {
    this->_variables += engine::NonConstexprPair < uint8, engine::String > ( engine::Shader::Header::DataType::SAMPLER_2D, engine::String(varName) );
    // this->_variables.put(engine::Shader::Header::DataType::SAMPLER_2D, varName);
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addVariableVec2( const engine::String& varName ) noexcept {
    this->_variables += engine::NonConstexprPair < uint8, engine::String > ( engine::Shader::Header::DataType::VEC_2, engine::String(varName) );
    // this->_variables.put(engine::Shader::Header::DataType::VEC_2, varName);
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addVariableVec3( const engine::String& varName ) noexcept {
    this->_variables += engine::NonConstexprPair < uint8, engine::String > ( engine::Shader::Header::DataType::VEC_3, engine::String(varName) );
    // this->_variables.put(engine::Shader::Header::DataType::VEC_3, varName);
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addVariableVec4( const engine::String& varName ) noexcept {
    this->_variables += engine::NonConstexprPair < uint8, engine::String > ( engine::Shader::Header::DataType::VEC_4, engine::String(varName) );
    // this->_variables.put(engine::Shader::Header::DataType::VEC_4, varName);
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addVariableMat3( const engine::String& varName ) noexcept {
    this->_variables += engine::NonConstexprPair < uint8, engine::String > ( engine::Shader::Header::DataType::MAT_3, engine::String(varName) );
    // this->_variables.put(engine::Shader::Header::DataType::MAT_3, varName);
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addVariableMat4( const engine::String& varName ) noexcept {
    this->_variables += engine::NonConstexprPair < uint8, engine::String > ( engine::Shader::Header::DataType::MAT_4, engine::String(varName) );
    // this->_variables.put(engine::Shader::Header::DataType::MAT_4, varName);
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addArrayVariable( const engine::String& varName, engine::Shader::Header::DataType dataType, std::size_t arrSize ) noexcept {
    if( ! _SHD_HEADER_DATA_IS_VAR_ARR_TYPE(dataType) ) 
        return *this;

    this->_variables += engine::NonConstexprPair < uint8, engine::String > ( dataType, varName );
    // this->_variables.put(dataType, varName);
    this->_arraySizes.put(varName, arrSize);
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addArrayVariable(const engine::Shader::Header::Struct& str, const char* varName, std::size_t arrSize) noexcept {
    // this->_variables.put(engine::Shader::Header::DataType::STRUCT_ARRAY, engine::String(varName));
    this->_variables += engine::NonConstexprPair < uint8, engine::String > (engine::Shader::Header::DataType::STRUCT_ARRAY, engine::String(varName));
    this->_arraySizes.put(engine::String(varName), arrSize);
    this->_structureTypeNames.put(engine::String(varName), str._name);
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addArrayVariable(const engine::Shader::Header::Struct& str, const engine::String& varName, std::size_t arrSize) noexcept {
    // this->_variables.put(engine::Shader::Header::DataType::STRUCT_ARRAY, varName);
    this->_variables += engine::NonConstexprPair < uint8, engine::String > (engine::Shader::Header::DataType::STRUCT_ARRAY, varName);
    this->_arraySizes.put(varName, arrSize);
    this->_structureTypeNames.put(varName, str._name);
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addArrayStructVariable(const engine::String& structName, const engine::String& str, std::size_t arrSize) noexcept {
    // this->_variables.put(engine::Shader::Header::DataType::STRUCT_ARRAY, str);
    this->_variables += engine::NonConstexprPair < uint8, engine::String > (engine::Shader::Header::DataType::STRUCT_ARRAY, str);
    this->_arraySizes.put(str, arrSize);
    this->_structureTypeNames.put(str, structName);
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addArrayVariableUInt8(const engine::String& varName, std::size_t arrSize) noexcept {
    // this->_variables.put(engine::Shader::Header::DataType::UINT8_ARRAY, varName);
    this->_variables += engine::NonConstexprPair < uint8, engine::String > (engine::Shader::Header::DataType::UINT8_ARRAY, varName);
    this->_arraySizes.put(varName, arrSize);
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addArrayVariableUInt16(const engine::String& varName, std::size_t arrSize) noexcept {
    // this->_variables.put(engine::Shader::Header::DataType::UINT16_ARRAY, varName);
    this->_variables += engine::NonConstexprPair < uint8, engine::String > (engine::Shader::Header::DataType::UINT16_ARRAY, varName);
    this->_arraySizes.put(varName, arrSize);
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addArrayVariableUInt32(const engine::String& varName, std::size_t arrSize) noexcept {
    // this->_variables.put(engine::Shader::Header::DataType::UINT32_ARRAY, varName);
    this->_variables += engine::NonConstexprPair < uint8, engine::String > (engine::Shader::Header::DataType::UINT32_ARRAY, varName);
    this->_arraySizes.put(varName, arrSize);
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addArrayVariableUInt64(const engine::String& varName, std::size_t arrSize) noexcept {
    // this->_variables.put(engine::Shader::Header::DataType::UINT64_ARRAY, varName);
    this->_variables += engine::NonConstexprPair < uint8, engine::String > (engine::Shader::Header::DataType::UINT64_ARRAY, varName);
    this->_arraySizes.put(varName, arrSize);
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addArrayVariableInt8(const engine::String& varName, std::size_t arrSize) noexcept {
    // this->_variables.put(engine::Shader::Header::DataType::SINT8_ARRAY, varName);
    this->_variables += engine::NonConstexprPair < uint8, engine::String > (engine::Shader::Header::DataType::SINT8_ARRAY, varName);
    this->_arraySizes.put(varName, arrSize);
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addArrayVariableInt16(const engine::String& varName, std::size_t arrSize) noexcept {
    // this->_variables.put(engine::Shader::Header::DataType::SINT16_ARRAY, varName);
    this->_variables += engine::NonConstexprPair < uint8, engine::String > (engine::Shader::Header::DataType::SINT16_ARRAY, varName);
    this->_arraySizes.put(varName, arrSize);
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addArrayVariableInt32(const engine::String& varName, std::size_t arrSize) noexcept {
    // this->_variables.put(engine::Shader::Header::DataType::SINT32_ARRAY, varName);
    this->_variables += engine::NonConstexprPair < uint8, engine::String > (engine::Shader::Header::DataType::SINT32_ARRAY, varName);
    this->_arraySizes.put(varName, arrSize);
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addArrayVariableInt64(const engine::String& varName, std::size_t arrSize) noexcept {
    // this->_variables.put(engine::Shader::Header::DataType::SINT64_ARRAY, varName);
    this->_variables += engine::NonConstexprPair < uint8, engine::String > (engine::Shader::Header::DataType::SINT64_ARRAY, varName);
    this->_arraySizes.put(varName, arrSize);
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addArrayVariableFloat(const engine::String& varName, std::size_t arrSize) noexcept {
    // this->_variables.put(engine::Shader::Header::DataType::FLOAT32_ARRAY, varName);
    this->_variables += engine::NonConstexprPair < uint8, engine::String > (engine::Shader::Header::DataType::FLOAT32_ARRAY, varName);
    this->_arraySizes.put(varName, arrSize);
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addArrayVariableDouble(const engine::String& varName, std::size_t arrSize) noexcept {
    // this->_variables.put(engine::Shader::Header::DataType::FLOAT64_ARRAY, varName);
    this->_variables += engine::NonConstexprPair < uint8, engine::String > (engine::Shader::Header::DataType::FLOAT64_ARRAY, varName);
    this->_arraySizes.put(varName, arrSize);
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addArrayVariableBool(const engine::String& varName, std::size_t arrSize) noexcept {
    // this->_variables.put(engine::Shader::Header::DataType::BOOL_ARRAY, varName);
    this->_variables += engine::NonConstexprPair < uint8, engine::String > (engine::Shader::Header::DataType::BOOL_ARRAY, varName);
    this->_arraySizes.put(varName, arrSize);
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addArrayVariableSampler2D(const engine::String& varName, std::size_t arrSize) noexcept {
    // this->_variables.put(engine::Shader::Header::DataType::SAMPLER_2D_ARRAY, varName);
    this->_variables += engine::NonConstexprPair < uint8, engine::String > (engine::Shader::Header::DataType::SAMPLER_2D_ARRAY, varName);
    this->_arraySizes.put(varName, arrSize);
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addArrayVariableVec2(const engine::String& varName, std::size_t arrSize) noexcept {
    // this->_variables.put(engine::Shader::Header::DataType::VEC_2_ARRAY, varName);
    this->_variables += engine::NonConstexprPair < uint8, engine::String > (engine::Shader::Header::DataType::VEC_2_ARRAY, varName);
    this->_arraySizes.put(varName, arrSize);
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addArrayVariableVec3(const engine::String& varName, std::size_t arrSize) noexcept {
    // this->_variables.put(engine::Shader::Header::DataType::VEC_3_ARRAY, varName);
    this->_variables += engine::NonConstexprPair < uint8, engine::String > (engine::Shader::Header::DataType::VEC_3_ARRAY, varName);
    this->_arraySizes.put(varName, arrSize);
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addArrayVariableVec4(const engine::String& varName, std::size_t arrSize) noexcept {
    // this->_variables.put(engine::Shader::Header::DataType::VEC_4_ARRAY, varName);
    this->_variables += engine::NonConstexprPair < uint8, engine::String > (engine::Shader::Header::DataType::VEC_4_ARRAY, varName);
    this->_arraySizes.put(varName, arrSize);
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addArrayVariableMat3(const engine::String& varName, std::size_t arrSize) noexcept {
    // this->_variables.put(engine::Shader::Header::DataType::MAT_3_ARRAY, varName);
    this->_variables += engine::NonConstexprPair < uint8, engine::String > (engine::Shader::Header::DataType::MAT_3_ARRAY, varName);
    this->_arraySizes.put(varName, arrSize);
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addArrayVariableMat4(const engine::String& varName, std::size_t arrSize) noexcept {
    // this->_variables.put(engine::Shader::Header::DataType::MAT_4_ARRAY, varName);
    this->_variables += engine::NonConstexprPair < uint8, engine::String > (engine::Shader::Header::DataType::MAT_4_ARRAY, varName);
    this->_arraySizes.put(varName, arrSize);
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addVariableUInt8(const char* varName) noexcept {
    // this->_variables.put(engine::Shader::Header::DataType::UINT8, engine::String(varName));
    this->_variables += engine::NonConstexprPair < uint8, engine::String > (engine::Shader::Header::DataType::UINT8, engine::String(varName));
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addVariableUInt16(const char* varName) noexcept {
    // this->_variables.put(engine::Shader::Header::DataType::UINT16, engine::String(varName));
    this->_variables += engine::NonConstexprPair < uint8, engine::String > (engine::Shader::Header::DataType::UINT16, engine::String(varName));
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addVariableUInt32(const char* varName) noexcept {
    // this->_variables.put(engine::Shader::Header::DataType::UINT32, engine::String(varName));
    this->_variables += engine::NonConstexprPair < uint8, engine::String > (engine::Shader::Header::DataType::UINT32, engine::String(varName));
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addVariableUInt64(const char* varName) noexcept {
    // this->_variables.put(engine::Shader::Header::DataType::UINT64, engine::String(varName));
    this->_variables += engine::NonConstexprPair < uint8, engine::String > (engine::Shader::Header::DataType::UINT64, engine::String(varName));
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addVariableInt8(const char* varName) noexcept {
    // this->_variables.put(engine::Shader::Header::DataType::SINT8, engine::String(varName));
    this->_variables += engine::NonConstexprPair < uint8, engine::String > (engine::Shader::Header::DataType::SINT8, engine::String(varName));
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addVariableInt16(const char* varName) noexcept {
    // this->_variables.put(engine::Shader::Header::DataType::SINT16, engine::String(varName));
    this->_variables += engine::NonConstexprPair < uint8, engine::String > (engine::Shader::Header::DataType::SINT16, engine::String(varName));
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addVariableInt32(const char* varName) noexcept {
    // this->_variables.put(engine::Shader::Header::DataType::SINT32, engine::String(varName));
    this->_variables += engine::NonConstexprPair < uint8, engine::String > (engine::Shader::Header::DataType::SINT32, engine::String(varName));
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addVariableInt64(const char* varName) noexcept {
    // this->_variables.put(engine::Shader::Header::DataType::SINT64, engine::String(varName));
    this->_variables += engine::NonConstexprPair < uint8, engine::String > (engine::Shader::Header::DataType::SINT64, engine::String(varName));
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addVariableFloat(const char* varName) noexcept {
    // this->_variables.put(engine::Shader::Header::DataType::FLOAT32, engine::String(varName));
    this->_variables += engine::NonConstexprPair < uint8, engine::String > (engine::Shader::Header::DataType::FLOAT32, engine::String(varName));
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addVariableDouble(const char* varName) noexcept {
    // this->_variables.put(engine::Shader::Header::DataType::FLOAT64, engine::String(varName));
    this->_variables += engine::NonConstexprPair < uint8, engine::String > (engine::Shader::Header::DataType::FLOAT64, engine::String(varName));
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addVariableBool(const char* varName) noexcept {
    // this->_variables.put(engine::Shader::Header::DataType::BOOL, engine::String(varName));
    this->_variables += engine::NonConstexprPair < uint8, engine::String > (engine::Shader::Header::DataType::BOOL, engine::String(varName));
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addVariableSampler2D(const char* varName) noexcept {
    // this->_variables.put(engine::Shader::Header::DataType::SAMPLER_2D, engine::String(varName));
    this->_variables += engine::NonConstexprPair < uint8, engine::String > (engine::Shader::Header::DataType::SAMPLER_2D, engine::String(varName));
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addVariableVec2(const char* varName) noexcept {
    // this->_variables.put(engine::Shader::Header::DataType::VEC_2, engine::String(varName));
    this->_variables += engine::NonConstexprPair < uint8, engine::String > (engine::Shader::Header::DataType::VEC_2, engine::String(varName));
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addVariableVec3(const char* varName) noexcept {
    // this->_variables.put(engine::Shader::Header::DataType::VEC_3, engine::String(varName));
    this->_variables += engine::NonConstexprPair < uint8, engine::String > (engine::Shader::Header::DataType::VEC_3, engine::String(varName));
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addVariableVec4(const char* varName) noexcept {
    // this->_variables.put(engine::Shader::Header::DataType::VEC_4, engine::String(varName));
    this->_variables += engine::NonConstexprPair < uint8, engine::String > (engine::Shader::Header::DataType::VEC_4, engine::String(varName));
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addVariableMat3(const char* varName) noexcept {
    // this->_variables.put(engine::Shader::Header::DataType::MAT_3, engine::String(varName));
    this->_variables += engine::NonConstexprPair < uint8, engine::String > (engine::Shader::Header::DataType::MAT_3, engine::String(varName));
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addVariableMat4(const char* varName) noexcept {
    // this->_variables.put(engine::Shader::Header::DataType::MAT_4, engine::String(varName));
    this->_variables += engine::NonConstexprPair < uint8, engine::String > (engine::Shader::Header::DataType::MAT_4, engine::String(varName));
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addArrayVariable(const char* varName, engine::Shader::Header::DataType dataType, std::size_t arrLen) noexcept {
    if( ! _SHD_HEADER_DATA_IS_VAR_ARR_TYPE(dataType) ) 
        return *this;

    // this->_variables.put( dataType, engine::String(varName) );
    this->_variables += engine::NonConstexprPair < uint8, engine::String > ( dataType, engine::String(varName) );
    this->_arraySizes.put( engine::String(varName), arrLen );
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addArrayStructVariable(const char* structName,const char* varName, std::size_t arrLen) noexcept {
    // this->_variables.put( engine::Shader::Header::DataType::STRUCT_ARRAY, engine::String( varName ) );
    this->_variables += engine::NonConstexprPair < uint8, engine::String > ( engine::Shader::Header::DataType::STRUCT_ARRAY, engine::String( varName ) );
    this->_arraySizes.put( engine::String( varName ), arrLen );
    this->_structureTypeNames.put( engine::String( varName ), engine::String( structName ) );
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addArrayVariableUInt8 ( const char* varName, std::size_t arrLen ) noexcept {
    // this->_variables.put( engine::Shader::Header::DataType::UINT8_ARRAY, engine::String( varName ) );
    this->_variables += engine::NonConstexprPair < uint8, engine::String > ( engine::Shader::Header::DataType::UINT8_ARRAY, engine::String( varName ) );
    this->_arraySizes.put( engine::String( varName ), arrLen );
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addArrayVariableUInt16 ( const char* varName, std::size_t arrLen ) noexcept {
    // this->_variables.put( engine::Shader::Header::DataType::UINT16_ARRAY, engine::String( varName ) );
    this->_variables += engine::NonConstexprPair < uint8, engine::String > ( engine::Shader::Header::DataType::UINT16_ARRAY, engine::String( varName ) );
    this->_arraySizes.put( engine::String( varName ), arrLen );
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addArrayVariableUInt32 ( const char* varName, std::size_t arrLen ) noexcept {
    // this->_variables.put( engine::Shader::Header::DataType::UINT32_ARRAY, engine::String( varName ) );
    this->_variables += engine::NonConstexprPair < uint8, engine::String > ( engine::Shader::Header::DataType::UINT32_ARRAY, engine::String( varName ) );
    this->_arraySizes.put( engine::String( varName ), arrLen );
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addArrayVariableUInt64 ( const char* varName, std::size_t arrLen ) noexcept {
    // this->_variables.put( engine::Shader::Header::DataType::UINT64_ARRAY, engine::String( varName ) );
    this->_variables += engine::NonConstexprPair < uint8, engine::String > ( engine::Shader::Header::DataType::UINT64_ARRAY, engine::String( varName ) );
    this->_arraySizes.put( engine::String( varName ), arrLen );
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addArrayVariableInt8 ( const char* varName, std::size_t arrLen ) noexcept {
    // this->_variables.put( engine::Shader::Header::DataType::SINT8_ARRAY, engine::String( varName ) );
    this->_variables += engine::NonConstexprPair < uint8, engine::String > ( engine::Shader::Header::DataType::SINT8_ARRAY, engine::String( varName ) );
    this->_arraySizes.put( engine::String( varName ), arrLen );
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addArrayVariableInt16 ( const char* varName, std::size_t arrLen ) noexcept {
    // this->_variables.put( engine::Shader::Header::DataType::SINT16_ARRAY, engine::String( varName ) );
    this->_variables += engine::NonConstexprPair < uint8, engine::String > ( engine::Shader::Header::DataType::SINT16_ARRAY, engine::String( varName ) );
    this->_arraySizes.put( engine::String( varName ), arrLen );
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addArrayVariableInt32 ( const char* varName, std::size_t arrLen ) noexcept {
    // this->_variables.put( engine::Shader::Header::DataType::SINT32_ARRAY, engine::String( varName ) );
    this->_variables += engine::NonConstexprPair < uint8, engine::String > ( engine::Shader::Header::DataType::SINT32_ARRAY, engine::String( varName ) );
    this->_arraySizes.put( engine::String( varName ), arrLen );
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addArrayVariableInt64 ( const char* varName, std::size_t arrLen ) noexcept {
    // this->_variables.put( engine::Shader::Header::DataType::SINT64_ARRAY, engine::String( varName ) );
    this->_variables += engine::NonConstexprPair < uint8, engine::String > ( engine::Shader::Header::DataType::SINT64_ARRAY, engine::String( varName ) );
    this->_arraySizes.put( engine::String( varName ), arrLen );
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addArrayVariableFloat ( const char* varName, std::size_t arrLen ) noexcept {
    // this->_variables.put( engine::Shader::Header::DataType::FLOAT32_ARRAY, engine::String( varName ) );
    this->_variables += engine::NonConstexprPair < uint8, engine::String > ( engine::Shader::Header::DataType::FLOAT32_ARRAY, engine::String( varName ) );
    this->_arraySizes.put( engine::String( varName ), arrLen );
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addArrayVariableDouble ( const char* varName, std::size_t arrLen ) noexcept {
    // this->_variables.put( engine::Shader::Header::DataType::FLOAT64_ARRAY, engine::String( varName ) );
    this->_variables += engine::NonConstexprPair < uint8, engine::String > ( engine::Shader::Header::DataType::FLOAT64_ARRAY, engine::String( varName ) );
    this->_arraySizes.put( engine::String( varName ), arrLen );
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addArrayVariableBool ( const char* varName, std::size_t arrLen ) noexcept {
    // this->_variables.put( engine::Shader::Header::DataType::BOOL_ARRAY, engine::String( varName ) );
    this->_variables += engine::NonConstexprPair < uint8, engine::String > ( engine::Shader::Header::DataType::BOOL_ARRAY, engine::String( varName ) );
    this->_arraySizes.put( engine::String( varName ), arrLen );
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addArrayVariableSampler2D ( const char* varName, std::size_t arrLen ) noexcept {
    // this->_variables.put( engine::Shader::Header::DataType::SAMPLER_2D_ARRAY, engine::String( varName ) );
    this->_variables += engine::NonConstexprPair < uint8, engine::String > ( engine::Shader::Header::DataType::SAMPLER_2D_ARRAY, engine::String( varName ) );
    this->_arraySizes.put( engine::String( varName ), arrLen );
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addArrayVariableVec2 ( const char* varName, std::size_t arrLen ) noexcept {
    // this->_variables.put( engine::Shader::Header::DataType::VEC_2_ARRAY, engine::String( varName ) );
    this->_variables += engine::NonConstexprPair < uint8, engine::String > ( engine::Shader::Header::DataType::VEC_2_ARRAY, engine::String( varName ) );
    this->_arraySizes.put( engine::String( varName ), arrLen );
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addArrayVariableVec3 ( const char* varName, std::size_t arrLen ) noexcept {
    // this->_variables.put( engine::Shader::Header::DataType::VEC_3_ARRAY, engine::String( varName ) );
    this->_variables += engine::NonConstexprPair < uint8, engine::String > ( engine::Shader::Header::DataType::VEC_3_ARRAY, engine::String( varName ) );
    this->_arraySizes.put( engine::String( varName ), arrLen );
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addArrayVariableVec4 ( const char* varName, std::size_t arrLen ) noexcept {
    // this->_variables.put( engine::Shader::Header::DataType::VEC_4_ARRAY, engine::String( varName ) );
    this->_variables += engine::NonConstexprPair < uint8, engine::String > ( engine::Shader::Header::DataType::VEC_4_ARRAY, engine::String( varName ) );
    this->_arraySizes.put( engine::String( varName ), arrLen );
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addArrayVariableMat3 ( const char* varName, std::size_t arrLen ) noexcept {
    // this->_variables.put( engine::Shader::Header::DataType::MAT_3_ARRAY, engine::String( varName ) );
    this->_variables += engine::NonConstexprPair < uint8, engine::String > ( engine::Shader::Header::DataType::MAT_3_ARRAY, engine::String( varName ) );
    this->_arraySizes.put( engine::String( varName ), arrLen );
    return *this;
}

[[maybe_unused]] engine::Shader::Header::Struct& engine::Shader::Header::Struct::addArrayVariableMat4 ( const char* varName, std::size_t arrLen ) noexcept {
    // this->_variables.put( engine::Shader::Header::DataType::MAT_4_ARRAY, engine::String( varName ) );
    this->_variables += engine::NonConstexprPair < uint8, engine::String > ( engine::Shader::Header::DataType::MAT_4_ARRAY, engine::String( varName ) );
    this->_arraySizes.put( engine::String( varName ), arrLen );
    return *this;
}

[[maybe_unused]] [[nodiscard]] engine::Array < engine::NonConstexprPair < uint8, engine::String > > & engine::Shader::Header::Struct::getVariables() noexcept {
    return this->_variables;
}

[[maybe_unused]] [[nodiscard]] engine::HashMap < engine::String, uint64 > & engine::Shader::Header::Struct::getArraySizes() noexcept {
    return this->_arraySizes;
}

[[maybe_unused]] [[nodiscard]] engine::HashMap < engine::String, engine::String > & engine::Shader::Header::Struct::getStructureVariableTypes() noexcept {
    return this->_structureTypeNames;
}

[[maybe_unused]] [[nodiscard]] static engine::Array < engine::NonConstexprPair < uint8, engine::String > > & sortVarsByTypeAndName ( engine::Array < engine::NonConstexprPair < uint8, engine::String > > & varsArray ) noexcept {
    //TODO : add faster sorting method ? 

    for( std::size_t i = 0, len = varsArray.getLength(); i + 1 < len; i++ ) { 
        for( std::size_t j = i + 1; j < len; j++ ) {
            engine::NonConstexprPair < uint8, engine::String > left     = varsArray[i];
            engine::NonConstexprPair < uint8, engine::String > right    = varsArray[j];

            if( left.getFirst() > right.getFirst() ) {
                std::swap(left, right);
            } else if( left.getFirst() == right.getFirst() ) {
                if( left.getSecond() > right.getSecond() ) {
                    std::swap(left, right);
                } 
            }
        }
    }

    return varsArray;
}

engine::Shader::Header::Struct& engine::Shader::Header::Struct::settleVariables() noexcept {
    this->_variables = sortVarsByTypeAndName( this->_variables );
    return *this;
}

engine::String engine::Shader::Header::Struct::toString() const noexcept {
    engine::String res = "struct " + this->_name + " {\n";

    // engine::Array < engine::NonConstexprPair < uint8 *, engine::String * > * > variableArr = this->_variables.getEntries();

    for(std::size_t it = 0; it < this->_variables.getLength(); it++ ) {
        if( _SHD_HEADER_DATA_IS_VAR_TYPE((engine::Shader::Header::DataType) this->_variables[it].getFirst()) || _SHD_HEADER_DATA_IS_VAR_ARR_TYPE((engine::Shader::Header::DataType) this->_variables[it].getFirst()) ) {

            res
                    .append("\t")
                    .append(engine::Shader::Header::dataTypeDeclaration((engine::Shader::Header::DataType) this->_variables[it].getFirst()))
                    .append(" ")
                    .append(this->_variables[it].getSecond());

            if (_SHD_HEADER_DATA_IS_VAR_ARR_TYPE((engine::Shader::Header::DataType) this->_variables[it].getFirst())) {
                res
                        .append("[")
                        .append(std::to_string(*(this->_arraySizes[this->_variables[it].getSecond()])))
                        .append("]");
            }

            res.append(";\n");
        } else {
            if( this->_variables[it].getFirst() == engine::Shader::Header::DataType::STRUCT ) {
                res
                    .append("\t")
                    .append(*this->_structureTypeNames[this->_variables[it].getSecond()])
                    .append(" ")
                    .append(this->_variables[it].getSecond())
                    .append(";\n");
            } else if ( this->_variables[it].getFirst() == engine::Shader::Header::DataType::STRUCT_ARRAY ) {
                res
                    .append("\t")
                    .append(*this->_structureTypeNames[this->_variables[it].getSecond()])
                    .append(" ")
                    .append(this->_variables[it].getSecond())
                    .append("[")
                    .append(std::to_string(*(this->_arraySizes[this->_variables[it].getSecond()])))
                    .append("];\n");
            }
        }
    }

    res.append("};\n");

    return res;
}

// TODO : mem leak here, from both arrSizes and strTypeNames !!!!
engine::Shader::Header::Struct::Struct(const engine::Shader::Header::Struct& obj) noexcept {
    this->_variables = obj._variables;
    this->_arraySizes = obj._arraySizes;
    this->_structureTypeNames = obj._structureTypeNames;
    this->_name = obj._name;
}

engine::String engine::Shader::Header::Struct::getName() const noexcept {
    return this->_name;
}


/**
 * 
 * Utility functions
 */

[[maybe_unused]] [[nodiscard]] engine::String engine::Shader::Header::dataTypeModifierToString(DataTypeModifier dataModifier) noexcept {
    switch (dataModifier) {
        case NONE       : return engine::String("No modifier");
        case INPUT      : return engine::String("Input Variable");
        case OUTPUT     : return engine::String("Output Variable");
        case UNIFORM    : return engine::String("Uniform Variable, assign in code");
    }
}

[[maybe_unused]] [[nodiscard]] engine::String engine::Shader::Header::dataTypeModifierDeclaration(DataTypeModifier dataModifier) noexcept {
    switch (dataModifier) {
        case UNIFORM    : return engine::String(_GLSL_TOKEN_UNIFORM);
        case OUTPUT     : return engine::String(_GLSL_TOKEN_OUTPUT);
        case INPUT      : return engine::String(_GLSL_TOKEN_INPUT);
        case NONE       : return engine::String("");
    }
}

[[maybe_unused]] [[nodiscard]] engine::String engine::Shader::Header::dataTypeToString(DataType dataType) noexcept {
    switch(dataType) { 
        case UINT8              : return engine::String("Unsigned Int Size 8 (unsigned char)");
        case UINT16             : return engine::String("Unsigned Int Size 16 (unsigned short)");
        case UINT32             : return engine::String("Unsigned Int Size 32 (unsigned int)");
        case UINT64             : return engine::String("Unsigned Int Size 64 (unsigned long long)");

        case SINT8              : return engine::String("Int Size 8 (char)");
        case SINT16             : return engine::String("Int Size 16 (short)");
        case SINT32             : return engine::String("Int Size 32 (int)");
        case SINT64             : return engine::String("Int Size 64 (long long)");

        case FLOAT32            : return engine::String("Float Size 32(float)");
        case FLOAT64            : return engine::String("Float Size 64(double)");

        case BOOL               : return engine::String("Bool Size 8 (bool)");

        case SAMPLER_2D         : return engine::String("Sampler 2D");
        case VEC_2              : return engine::String("Vector Size 2");
        case VEC_3              : return engine::String("Vector Size 3");
        case VEC_4              : return engine::String("Vector Size 4");
        case MAT_3              : return engine::String("Matrix Size 3");
        case MAT_4              : return engine::String("Matrix Size 4");

        case STRUCT             : return engine::String("Defined Structure");


        case UINT8_ARRAY        : return engine::String("Unsigned Int Size 8 Array (unsigned char[])");
        case UINT16_ARRAY       : return engine::String("Unsigned Int Size 16 Array (unsigned short[])");
        case UINT32_ARRAY       : return engine::String("Unsigned Int Size 32 Array (unsigned int[])");
        case UINT64_ARRAY       : return engine::String("Unsigned Int Size 64 Array (unsigned long long[])");

        case SINT8_ARRAY        : return engine::String("Int Size 8 Array (char[])");
        case SINT16_ARRAY       : return engine::String("Int Size 16 Array (short[])");
        case SINT32_ARRAY       : return engine::String("Int Size 32 Array (int[])");
        case SINT64_ARRAY       : return engine::String("Int Size 64 Array (long long[])");

        case FLOAT32_ARRAY      : return engine::String("Float Size 32 Array (float[])");
        case FLOAT64_ARRAY      : return engine::String("Float Size 64 Array (double[])");

        case BOOL_ARRAY         : return engine::String("Bool Size 8 Array (bool[])");

        case SAMPLER_2D_ARRAY   : return engine::String("Sampler 2D Array");
        case VEC_2_ARRAY        : return engine::String("Vector Size 2 Array");
        case VEC_3_ARRAY        : return engine::String("Vector Size 3 Array");
        case VEC_4_ARRAY        : return engine::String("Vector Size 4 Array");
        case MAT_3_ARRAY        : return engine::String("Matrix Size 3 Array");
        case MAT_4_ARRAY        : return engine::String("Matrix Size 4 Array");

        case STRUCT_ARRAY       : return engine::String("Defined Structure Array");
    }
}

[[maybe_unused]] [[nodiscard]] engine::String engine::Shader::Header::dataTypeDeclaration(DataType dataType) noexcept {
    switch(dataType) {
        case UINT8              :
        case UINT16             :
        case UINT32             :
        case UINT64             :
        case UINT8_ARRAY        :
        case UINT16_ARRAY       :
        case UINT32_ARRAY       :
        case UINT64_ARRAY       : return engine::String(_GLSL_TYPE_UNSIGNED_INT);

        case SINT8              :
        case SINT16             :
        case SINT32             :
        case SINT64             :
        case SINT8_ARRAY        :
        case SINT16_ARRAY       :
        case SINT32_ARRAY       :
        case SINT64_ARRAY       : return engine::String(_GLSL_TYPE_INT);

        case FLOAT32            :
        case FLOAT32_ARRAY      : return engine::String(_GLSL_TYPE_FLOAT);

        case FLOAT64            :
        case FLOAT64_ARRAY      : return engine::String(_GLSL_TYPE_DOUBLE);

        case BOOL               :
        case BOOL_ARRAY         : return engine::String(_GLSL_TYPE_BOOL);


        case SAMPLER_2D         :
        case SAMPLER_2D_ARRAY   : return engine::String(_GLSL_TYPE_SAMPLER_2D);

        case VEC_2              :
        case VEC_2_ARRAY        : return engine::String(_GLSL_TYPE_VEC_2);

        case VEC_3              :
        case VEC_3_ARRAY        : return engine::String(_GLSL_TYPE_VEC_3);

        case VEC_4              :
        case VEC_4_ARRAY        : return engine::String(_GLSL_TYPE_VEC_4);

        case MAT_3              :
        case MAT_3_ARRAY        : return engine::String(_GLSL_TYPE_MAT_3);

        case MAT_4              :
        case MAT_4_ARRAY        : return engine::String(_GLSL_TYPE_MAT_4);

        case STRUCT             :
        case STRUCT_ARRAY       : return engine::String(_GLSL_TYPE_STRUCT);
    }
}

[[maybe_unused]] [[nodiscard]] engine::String engine::Shader::Header::toString(const glm::vec2& value) noexcept {
    return engine::String("vec2").append("(").append(std::to_string(value.x)).append(", ").append(std::to_string(value.y)).append(")");
}

[[maybe_unused]] [[nodiscard]] engine::String engine::Shader::Header::toString(const glm::vec3& value) noexcept {
    return engine::String("vec3").append("(").append(std::to_string(value.x)).append(", ").append(std::to_string(value.y)).append(", ").append(std::to_string(value.z)).append(")");
}

[[maybe_unused]] [[nodiscard]] engine::String engine::Shader::Header::toString(const glm::vec4& value) noexcept {
    return engine::String("vec4").append("(").append(std::to_string(value.x)).append(", ").append(std::to_string(value.y)).append(", ").append(std::to_string(value.z)).append(", ").append(std::to_string(value.w)).append(")");
}

[[maybe_unused]] [[nodiscard]] engine::String engine::Shader::Header::toString(const glm::mat3& value) noexcept {
    return engine::String("mat3").append("(")
        .append(engine::Shader::Header::toString(value[0])).append(", ")
        .append(engine::Shader::Header::toString(value[1])).append(", ")
        .append(engine::Shader::Header::toString(value[2])).append(")");
}

[[maybe_unused]] [[nodiscard]] engine::String engine::Shader::Header::toString(const glm::mat4& value) noexcept {
    return engine::String("mat4").append("(")
        .append(engine::Shader::Header::toString(value[0])).append(", ")
        .append(engine::Shader::Header::toString(value[1])).append(", ")
        .append(engine::Shader::Header::toString(value[2])).append(", ")
        .append(engine::Shader::Header::toString(value[3])).append(")");
}

/**
 * 
 * 
 * Shader Header Definitions
 */ 

engine::Shader::Header::Header(const char* fileName, bool generateIncludeGuards) noexcept : 
    _generateIncludeGuards(generateIncludeGuards), _name(engine::String(fileName)) {

}

engine::Shader::Header::Header(const engine::String& fileName, bool generateIncludeGuards) noexcept : 
    _generateIncludeGuards(generateIncludeGuards), _name(fileName) {

}

[[maybe_unused]] [[nodiscard]] engine::String engine::Shader::Header::includeGuardTop() const noexcept {
    engine::Array < engine::String > tokens;
    engine::String token;

    for(std::size_t it = 0; it < this->_name.length(); it++) {
        if( this->_name[it] >= 'A' && this->_name[it] <= 'Z' ) {
            tokens += token;
            token.clear();
            token += this->_name[it];
        } else 
            token += this->_name[it];
    }

    tokens += token;
    token.clear();

    for(std::size_t it = 0, len = tokens.getLength(); it < len; it++) {
        token.append(tokens[it]).toUpper().append("_");
    }

    token.append("GLSL_H");

    return engine::String(_TOKEN_IF_NOT_DEFINED).append(" ").append(token).append("\n").append(engine::String(_TOKEN_DEFINE)).append(" ").append(token).append("\n");// + " " + token + "\n" + engine::String(_TOKEN_DEFINE) + token;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-convert-member-functions-to-static"
[[maybe_unused]] [[nodiscard]] engine::String engine::Shader::Header::includeGuardBottom() const noexcept {
    return engine::String(_TOKEN_END_IF).append("\n");
}
#pragma clang diagnostic pop

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::setRelativePath(const char* path) noexcept {
    this->_path = engine::String( __SHADERS_PATH__ ) + path;
    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::setAbsolutePath(const char* path) noexcept {
    this->_path = path;
    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::clear() noexcept {
    this->_declarations.clear();
    this->_definitions.clear();
    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addDefine(const engine::String& tokenName, const engine::String& tokenValue) noexcept {
    this->_declarations += engine::String(_TOKEN_DEFINE).append(" ").append(tokenName).append(" ").append(tokenValue).append("\n");
    return *this; 
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addIfDefined(const engine::String& tokenName) noexcept {
    this->_declarations += engine::String(_TOKEN_IF_DEFINED).append(" ").append(tokenName).append("\n");
    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addIfNotDefined(const engine::String& tokenName) noexcept {
    this->_declarations += engine::String(_TOKEN_IF_NOT_DEFINED).append(" ").append(tokenName).append("\n");
    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addEndIf() noexcept {
    this->_declarations += engine::String(_TOKEN_END_IF).append("\n");
    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addStruct(const engine::Shader::Header::Struct& str) noexcept {
    this->_definedStructures.put( str.getName(), str );
    this->_declarations += str.toString().append("\n");
    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addCode(const char* code) noexcept {
    this->_definitions += engine::String(code).append("\n");
    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addCode(const engine::String& code) noexcept {
    this->_definitions += code + "\n";
    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addCode(const std::string& code) noexcept {
    this->_definitions += engine::String(code).append("\n");
    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addVariable(const engine::String& varName, engine::Shader::Header::DataType dataType, engine::Shader::Header::DataTypeModifier modifier) noexcept {
    if( ! _SHD_HEADER_DATA_IS_VAR_ARR_TYPE(dataType) && ! _SHD_HEADER_DATA_IS_VAR_TYPE(dataType) )
        return *this;

    this->_declarations += engine::Shader::Header::dataTypeModifierDeclaration(modifier).append(" ").append(engine::Shader::Header::dataTypeDeclaration(dataType)).append(" ").append(varName).append(";\n").trim();
    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addVariable(const engine::String& varName, const engine::Shader::Header::Struct& structure, engine::Shader::Header::DataTypeModifier modifier ) noexcept {
    this->_declarations += engine::Shader::Header::dataTypeModifierDeclaration(modifier).append(" ").append(structure.getName()).append(" ").append(varName).append(";\n").trim();
    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addStructVariable(const engine::String& varName, const engine::String& structName, engine::Shader::Header::DataTypeModifier modifier) noexcept {
    this->_declarations += engine::Shader::Header::dataTypeModifierDeclaration(modifier).append(" ").append(structName).append(" ").append(varName).append(";\n").trim();
    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addVariableUInt8(const engine::String& varName, engine::Shader::Header::DataTypeModifier modifier, uint8 defaultValue) noexcept {
    this->_declarations += engine::Shader::Header::dataTypeModifierDeclaration(modifier).append(" ").append(engine::Shader::Header::dataTypeDeclaration(engine::Shader::Header::DataType::UINT8)).append(" ").append(varName).trim();

    if(modifier == DataTypeModifier::NONE) {
        this->_declarations.append(" = ").append(std::to_string(defaultValue)).append(";\n");
    } else { 
        this->_declarations.append(";\n");
    }

    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addVariableUInt16(const engine::String& varName, engine::Shader::Header::DataTypeModifier modifier, uint16 defaultValue) noexcept {
    this->_declarations += engine::Shader::Header::dataTypeModifierDeclaration(modifier).append(" ").append(engine::Shader::Header::dataTypeDeclaration(engine::Shader::Header::DataType::UINT16)).append(" ").append(varName).trim();

    if(modifier == DataTypeModifier::NONE) {
        this->_declarations.append(" = ").append(std::to_string(defaultValue)).append(";\n");
    } else { 
        this->_declarations.append(";\n");
    }

    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addVariableUInt32(const engine::String& varName, engine::Shader::Header::DataTypeModifier modifier, uint32 defaultValue) noexcept {
    this->_declarations += engine::Shader::Header::dataTypeModifierDeclaration(modifier).append(" ").append(engine::Shader::Header::dataTypeDeclaration(engine::Shader::Header::DataType::UINT32)).append(" ").append(varName).trim();

    if(modifier == DataTypeModifier::NONE) {
        this->_declarations.append(" = ").append(std::to_string(defaultValue)).append(";\n");
    } else { 
        this->_declarations.append(";\n");
    }

    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addVariableUInt64(const engine::String& varName, engine::Shader::Header::DataTypeModifier modifier, uint64 defaultValue) noexcept {
    this->_declarations += engine::Shader::Header::dataTypeModifierDeclaration(modifier).append(" ").append(engine::Shader::Header::dataTypeDeclaration(engine::Shader::Header::DataType::UINT64)).append(" ").append(varName).trim();

    if(modifier == DataTypeModifier::NONE) {
        this->_declarations.append(" = ").append(std::to_string(defaultValue)).append(";\n");
    } else { 
        this->_declarations.append(";\n");
    }

    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addVariableInt8(const engine::String& varName, engine::Shader::Header::DataTypeModifier modifier, int8 defaultValue) noexcept {
    this->_declarations += engine::Shader::Header::dataTypeModifierDeclaration(modifier).append(" ").append(engine::Shader::Header::dataTypeDeclaration(engine::Shader::Header::DataType::SINT8)).append(" ").append(varName).trim();

    if(modifier == DataTypeModifier::NONE) {
        this->_declarations.append(" = ").append(std::to_string(defaultValue)).append(";\n");
    } else { 
        this->_declarations.append(";\n");
    }

    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addVariableInt16(const engine::String& varName, engine::Shader::Header::DataTypeModifier modifier, int16 defaultValue) noexcept {
    this->_declarations += engine::Shader::Header::dataTypeModifierDeclaration(modifier).append(" ").append(engine::Shader::Header::dataTypeDeclaration(engine::Shader::Header::DataType::SINT16)).append(" ").append(varName).trim();

    if(modifier == DataTypeModifier::NONE) {
        this->_declarations.append(" = ").append(std::to_string(defaultValue)).append(";\n");
    } else { 
        this->_declarations.append(";\n");
    }

    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addVariableInt32(const engine::String& varName, engine::Shader::Header::DataTypeModifier modifier, int32 defaultValue) noexcept {
    this->_declarations += engine::Shader::Header::dataTypeModifierDeclaration(modifier).append(" ").append(engine::Shader::Header::dataTypeDeclaration(engine::Shader::Header::DataType::SINT32)).append(" ").append(varName).trim();

    if(modifier == DataTypeModifier::NONE) {
        this->_declarations.append(" = ").append(std::to_string(defaultValue)).append(";\n");
    } else { 
        this->_declarations.append(";\n");
    }

    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addVariableInt64(const engine::String& varName, engine::Shader::Header::DataTypeModifier modifier, int64 defaultValue) noexcept {
    this->_declarations += engine::Shader::Header::dataTypeModifierDeclaration(modifier).append(" ").append(engine::Shader::Header::dataTypeDeclaration(engine::Shader::Header::DataType::SINT64)).append(" ").append(varName).trim();

    if(modifier == DataTypeModifier::NONE) {
        this->_declarations.append(" = ").append(std::to_string(defaultValue)).append(";\n");
    } else { 
        this->_declarations.append(";\n");
    }

    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addVariableFloat(const engine::String& varName, engine::Shader::Header::DataTypeModifier modifier, float defaultValue) noexcept {
    this->_declarations += engine::Shader::Header::dataTypeModifierDeclaration(modifier).append(" ").append(engine::Shader::Header::dataTypeDeclaration(engine::Shader::Header::DataType::FLOAT32)).append(" ").append(varName).trim();

    if(modifier == DataTypeModifier::NONE) {
        this->_declarations.append(" = ").append(std::to_string(defaultValue)).append(";\n");
    } else { 
        this->_declarations.append(";\n");
    }

    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addVariableDouble(const engine::String& varName, engine::Shader::Header::DataTypeModifier modifier, double defaultValue) noexcept {
    this->_declarations += engine::Shader::Header::dataTypeModifierDeclaration(modifier).append(" ").append(engine::Shader::Header::dataTypeDeclaration(engine::Shader::Header::DataType::FLOAT64)).append(" ").append(varName).trim();

    if(modifier == DataTypeModifier::NONE) {
        this->_declarations.append(" = ").append(std::to_string(defaultValue)).append(";\n");
    } else { 
        this->_declarations.append(";\n");
    }

    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addVariableBool(const engine::String& varName, engine::Shader::Header::DataTypeModifier modifier, bool defaultValue) noexcept {
    this->_declarations += engine::Shader::Header::dataTypeModifierDeclaration(modifier).append(" ").append(engine::Shader::Header::dataTypeDeclaration(engine::Shader::Header::DataType::BOOL)).append(" ").append(varName).trim();

    if(modifier == DataTypeModifier::NONE) {
        this->_declarations.append(" = ").append(std::to_string(defaultValue)).append(";\n");
    } else { 
        this->_declarations.append(";\n");
    }

    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addVariableSampler2D(const engine::String& varName, engine::Shader::Header::DataTypeModifier modifier) noexcept {
    this->_declarations += engine::Shader::Header::dataTypeModifierDeclaration(modifier).append(" ").append(engine::Shader::Header::dataTypeDeclaration(engine::Shader::Header::DataType::SAMPLER_2D)).append(" ").append(varName).append(";\n").trim();
    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addVariableVec2(const engine::String& varName, engine::Shader::Header::DataTypeModifier modifier, const glm::vec2& defaultValue) noexcept {
    this->_declarations += engine::Shader::Header::dataTypeModifierDeclaration(modifier).append(" ").append(engine::Shader::Header::dataTypeDeclaration(engine::Shader::Header::DataType::VEC_2)).append(" ").append(varName).trim();

    if(modifier == DataTypeModifier::NONE) {
        // this->_declarations.append(" = ").append(std::to_string(defaultValue)).append(";\n");
        this->_declarations.append(" = ").append(engine::Shader::Header::toString(defaultValue)).append(";\n");
    } else { 
        this->_declarations.append(";\n");
    }

    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addVariableVec3(const engine::String& varName, engine::Shader::Header::DataTypeModifier modifier, const glm::vec3& defaultValue) noexcept {
    this->_declarations += engine::Shader::Header::dataTypeModifierDeclaration(modifier).append(" ").append(engine::Shader::Header::dataTypeDeclaration(engine::Shader::Header::DataType::VEC_3)).append(" ").append(varName).trim();

    if(modifier == DataTypeModifier::NONE) {
        this->_declarations.append(" = ").append(engine::Shader::Header::toString(defaultValue)).append(";\n");
    } else { 
        this->_declarations.append(";\n");
    }

    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addVariableVec4(const engine::String& varName, engine::Shader::Header::DataTypeModifier modifier, const glm::vec4& defaultValue) noexcept {
    this->_declarations += engine::Shader::Header::dataTypeModifierDeclaration(modifier).append(" ").append(engine::Shader::Header::dataTypeDeclaration(engine::Shader::Header::DataType::VEC_4)).append(" ").append(varName).trim();

    if(modifier == DataTypeModifier::NONE) {
        this->_declarations.append(" = ").append(engine::Shader::Header::toString(defaultValue)).append(";\n");
    } else { 
        this->_declarations.append(";\n");
    }

    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addVariableMat3(const engine::String& varName, engine::Shader::Header::DataTypeModifier modifier, const glm::mat3& defaultValue) noexcept {
    this->_declarations += engine::Shader::Header::dataTypeModifierDeclaration(modifier).append(" ").append(engine::Shader::Header::dataTypeDeclaration(engine::Shader::Header::DataType::MAT_3)).append(" ").append(varName).trim();

    if(modifier == DataTypeModifier::NONE) {
        this->_declarations.append(" = ").append(engine::Shader::Header::toString(defaultValue)).append(";\n");
    } else { 
        this->_declarations.append(";\n");
    }

    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addVariableMat4(const engine::String& varName, engine::Shader::Header::DataTypeModifier modifier, const glm::mat4& defaultValue) noexcept {
    this->_declarations += engine::Shader::Header::dataTypeModifierDeclaration(modifier).append(" ").append(engine::Shader::Header::dataTypeDeclaration(engine::Shader::Header::DataType::MAT_4)).append(" ").append(varName).trim();

    if(modifier == DataTypeModifier::NONE) {
        this->_declarations.append(" = ").append(engine::Shader::Header::toString(defaultValue)).append(";\n");
    } else { 
        this->_declarations.append(";\n");
    }

    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addArrayVariable(const engine::String& varName, engine::Shader::Header::DataType dataType, std::size_t length, engine::Shader::Header::DataTypeModifier modifier) noexcept {
    if( ! _SHD_HEADER_DATA_IS_VAR_ARR_TYPE(dataType) && ! _SHD_HEADER_DATA_IS_VAR_TYPE(dataType))
        return *this;

    this->_declarations += engine::Shader::Header::dataTypeModifierDeclaration(modifier).append(" ").append(engine::Shader::Header::dataTypeDeclaration(dataType)).append(" ").append(varName).append("[").append(std::to_string(length)).append("];\n").trim();
    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addArrayVariable(const engine::String & varName, const Struct & dataType, std::size_t length, DataTypeModifier modifier) noexcept {
    this->_declarations += engine::Shader::Header::dataTypeModifierDeclaration(modifier).append(" ").append(dataType.getName()).append(" ").append(varName).append("[").append(std::to_string(length)).append("];\n").trim();
    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addArrayStructVariable(const engine::String & varName, const engine::String & dataType, std::size_t length, DataTypeModifier modifier) noexcept {
    this->_declarations += engine::Shader::Header::dataTypeModifierDeclaration(modifier).append(" ").append(dataType).append(" ").append(varName).append("[").append(std::to_string(length)).append("];\n").trim();
    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addArrayVariableUInt8(const engine::String & varName, std::size_t length, engine::Shader::Header::DataTypeModifier modifier) noexcept {
    this->_declarations += engine::Shader::Header::dataTypeModifierDeclaration(modifier).append(" ").append(engine::Shader::Header::dataTypeDeclaration(engine::Shader::Header::DataType::UINT8_ARRAY)).append(" ").append(varName).append("[").append(std::to_string(length)).append("];\n").trim();
    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addArrayVariableUInt16(const engine::String & varName, std::size_t length, engine::Shader::Header::DataTypeModifier modifier) noexcept {
    this->_declarations += engine::Shader::Header::dataTypeModifierDeclaration(modifier).append(" ").append(engine::Shader::Header::dataTypeDeclaration(engine::Shader::Header::DataType::UINT16_ARRAY)).append(" ").append(varName).append("[").append(std::to_string(length)).append("];\n").trim();
    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addArrayVariableUInt32(const engine::String & varName, std::size_t length, engine::Shader::Header::DataTypeModifier modifier) noexcept {
    this->_declarations += engine::Shader::Header::dataTypeModifierDeclaration(modifier).append(" ").append(engine::Shader::Header::dataTypeDeclaration(engine::Shader::Header::DataType::UINT32_ARRAY)).append(" ").append(varName).append("[").append(std::to_string(length)).append("];\n").trim();
    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addArrayVariableUInt64(const engine::String & varName, std::size_t length, engine::Shader::Header::DataTypeModifier modifier) noexcept {
    this->_declarations += engine::Shader::Header::dataTypeModifierDeclaration(modifier).append(" ").append(engine::Shader::Header::dataTypeDeclaration(engine::Shader::Header::DataType::UINT64_ARRAY)).append(" ").append(varName).append("[").append(std::to_string(length)).append("];\n").trim();
    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addArrayVariableInt8(const engine::String & varName, std::size_t length, engine::Shader::Header::DataTypeModifier modifier) noexcept {
    this->_declarations += engine::Shader::Header::dataTypeModifierDeclaration(modifier).append(" ").append(engine::Shader::Header::dataTypeDeclaration(engine::Shader::Header::DataType::SINT8_ARRAY)).append(" ").append(varName).append("[").append(std::to_string(length)).append("];\n").trim();
    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addArrayVariableInt16(const engine::String & varName, std::size_t length, engine::Shader::Header::DataTypeModifier modifier) noexcept {
    this->_declarations += engine::Shader::Header::dataTypeModifierDeclaration(modifier).append(" ").append(engine::Shader::Header::dataTypeDeclaration(engine::Shader::Header::DataType::SINT16_ARRAY)).append(" ").append(varName).append("[").append(std::to_string(length)).append("];\n").trim();
    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addArrayVariableInt32(const engine::String & varName, std::size_t length, engine::Shader::Header::DataTypeModifier modifier) noexcept {
    this->_declarations += engine::Shader::Header::dataTypeModifierDeclaration(modifier).append(" ").append(engine::Shader::Header::dataTypeDeclaration(engine::Shader::Header::DataType::SINT32_ARRAY)).append(" ").append(varName).append("[").append(std::to_string(length)).append("];\n").trim();
    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addArrayVariableInt64(const engine::String & varName, std::size_t length, engine::Shader::Header::DataTypeModifier modifier) noexcept {
    this->_declarations += engine::Shader::Header::dataTypeModifierDeclaration(modifier).append(" ").append(engine::Shader::Header::dataTypeDeclaration(engine::Shader::Header::DataType::SINT64_ARRAY)).append(" ").append(varName).append("[").append(std::to_string(length)).append("];\n").trim();
    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addArrayVariableFloat(const engine::String & varName, std::size_t length, engine::Shader::Header::DataTypeModifier modifier) noexcept {
    this->_declarations += engine::Shader::Header::dataTypeModifierDeclaration(modifier).append(" ").append(engine::Shader::Header::dataTypeDeclaration(engine::Shader::Header::DataType::FLOAT32_ARRAY)).append(" ").append(varName).append("[").append(std::to_string(length)).append("];\n").trim();
    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addArrayVariableDouble(const engine::String & varName, std::size_t length, engine::Shader::Header::DataTypeModifier modifier) noexcept {
    this->_declarations += engine::Shader::Header::dataTypeModifierDeclaration(modifier).append(" ").append(engine::Shader::Header::dataTypeDeclaration(engine::Shader::Header::DataType::FLOAT64_ARRAY)).append(" ").append(varName).append("[").append(std::to_string(length)).append("];\n").trim();
    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addArrayVariableBool(const engine::String & varName, std::size_t length, engine::Shader::Header::DataTypeModifier modifier) noexcept {
    this->_declarations += engine::Shader::Header::dataTypeModifierDeclaration(modifier).append(" ").append(engine::Shader::Header::dataTypeDeclaration(engine::Shader::Header::DataType::BOOL_ARRAY)).append(" ").append(varName).append("[").append(std::to_string(length)).append("];\n").trim();
    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addArrayVariableSampler2D(const engine::String & varName, std::size_t length, engine::Shader::Header::DataTypeModifier modifier) noexcept {
    this->_declarations += engine::Shader::Header::dataTypeModifierDeclaration(modifier).append(" ").append(engine::Shader::Header::dataTypeDeclaration(engine::Shader::Header::DataType::SAMPLER_2D_ARRAY)).append(" ").append(varName).append("[").append(std::to_string(length)).append("];\n").trim();
    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addArrayVariableVec2(const engine::String & varName, std::size_t length, engine::Shader::Header::DataTypeModifier modifier) noexcept {
    this->_declarations += engine::Shader::Header::dataTypeModifierDeclaration(modifier).append(" ").append(engine::Shader::Header::dataTypeDeclaration(engine::Shader::Header::DataType::VEC_2_ARRAY)).append(" ").append(varName).append("[").append(std::to_string(length)).append("];\n").trim();
    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addArrayVariableVec3(const engine::String & varName, std::size_t length, engine::Shader::Header::DataTypeModifier modifier) noexcept {
    this->_declarations += engine::Shader::Header::dataTypeModifierDeclaration(modifier).append(" ").append(engine::Shader::Header::dataTypeDeclaration(engine::Shader::Header::DataType::VEC_3_ARRAY)).append(" ").append(varName).append("[").append(std::to_string(length)).append("];\n").trim();
    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addArrayVariableVec4(const engine::String & varName, std::size_t length, engine::Shader::Header::DataTypeModifier modifier) noexcept {
    this->_declarations += engine::Shader::Header::dataTypeModifierDeclaration(modifier).append(" ").append(engine::Shader::Header::dataTypeDeclaration(engine::Shader::Header::DataType::VEC_4_ARRAY)).append(" ").append(varName).append("[").append(std::to_string(length)).append("];\n").trim();
    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addArrayVariableMat3(const engine::String & varName, std::size_t length, engine::Shader::Header::DataTypeModifier modifier) noexcept {
    this->_declarations += engine::Shader::Header::dataTypeModifierDeclaration(modifier).append(" ").append(engine::Shader::Header::dataTypeDeclaration(engine::Shader::Header::DataType::MAT_3_ARRAY)).append(" ").append(varName).append("[").append(std::to_string(length)).append("];\n").trim();
    return *this;
}

[[maybe_unused]] engine::Shader::Header& engine::Shader::Header::addArrayVariableMat4(const engine::String & varName, std::size_t length, engine::Shader::Header::DataTypeModifier modifier) noexcept {
    this->_declarations += engine::Shader::Header::dataTypeModifierDeclaration(modifier).append(" ").append(engine::Shader::Header::dataTypeDeclaration(engine::Shader::Header::DataType::MAT_4_ARRAY)).append(" ").append(varName).append("[").append(std::to_string(length)).append("];\n").trim();
    return *this;
}

[[maybe_unused]] engine::HashMap < engine::String, engine::Shader::Header::Struct > & engine::Shader::Header::getDefinedStructures() noexcept {
    return this->_definedStructures;
}

[[maybe_unused]] [[nodiscard]] engine::String engine::Shader::Header::generateCode() const noexcept {
    engine::String code;

    if(this->_generateIncludeGuards)
        code += this->includeGuardTop().append("\n");

    code += this->_declarations + "\n";

    code += this->_definitions + "\n";

    if(this->_generateIncludeGuards)
        code += this->includeGuardBottom();

    return code;
}

[[maybe_unused]] void engine::Shader::Header::generate() const noexcept {
    engine::String code = this->generateCode();
    std::fstream generatedFile;
    engine::String fileFullPath = this->_path + this->_name + _GLSL_INCLUDE_FILE_EXTENSION;

    generatedFile.open( fileFullPath.c_str(), std::fstream::out | std::fstream::trunc );

    generatedFile << code << '\n';

    generatedFile.close();

}

engine::Shader::Header::Struct& engine::Shader::Header::Struct::operator= (const engine::Shader::Header::Struct& obj) noexcept {
    if( this == &obj )
        return *this;

    this->_name = obj._name;
    this->_variables = obj._variables;
    this->_arraySizes = obj._arraySizes;
    this->_structureTypeNames = obj._structureTypeNames;

    return *this;
}

#undef _GLSL_TOKEN_UNIFORM
#undef _GLSL_TOKEN_OUTPUT
#undef _GLSL_TOKEN_INPUT

#undef _GLSL_TYPE_UNSIGNED_INT
#undef _GLSL_TYPE_INT
#undef _GLSL_TYPE_FLOAT
#undef _GLSL_TYPE_DOUBLE
#undef _GLSL_TYPE_BOOL
#undef _GLSL_TYPE_SAMPLER_2D
#undef _GLSL_TYPE_VEC_2
#undef _GLSL_TYPE_VEC_3
#undef _GLSL_TYPE_VEC_4
#undef _GLSL_TYPE_MAT_3
#undef _GLSL_TYPE_MAT_4
#undef _GLSL_TYPE_STRUCT

#undef _SHD_HEADER_DATA_IS_VAR_TYPE
#undef _SHD_HEADER_DATA_IS_VAR_ARR_TYPE

#undef _SHD_HEADER_DATA_TYPE_STD_TYPE
#undef _SHD_HEADER_DATA_TYPE_STD_SHD_TYPE
#undef _SHD_HEADER_DATA_TYPE_STD_TYPE_ARR
#undef _SHD_HEADER_DATA_TYPE_STD_SHD_TYPE_ARR

#undef _SHD_HEADER_DATA_TYPE_STD_TYPE_START
#undef _SHD_HEADER_DATA_TYPE_STD_TYPE_ARR_START
#undef _SHD_HEADER_DATA_TYPE_STD_SHD_TYPE_START
#undef _SHD_HEADER_DATA_TYPE_STD_SHD_TYPE_ARR_START
#undef _SHD_HEADER_DATA_TYPE_STD_STRUCT_TYPE_START
#undef _SHD_HEADER_DATA_TYPE_STD_STRUCT_TYPE_ARR_START

#undef _SHD_HEADER_DATA_TYPE_STD_TYPE_END
#undef _SHD_HEADER_DATA_TYPE_STD_TYPE_ARR_END
#undef _SHD_HEADER_DATA_TYPE_STD_SHD_TYPE_END
#undef _SHD_HEADER_DATA_TYPE_STD_SHD_TYPE_ARR_END

#undef _INC_SHD_STR_LINE_PROP_ENDIF
#undef _INC_SHD_STR_LINE_PROP_IFNDEF
#undef _INC_SHD_STR_LINE_PROP_IFDEF
#undef _INC_SHD_STR_LINE_PROP_UNDEF
#undef _INC_SHD_STR_LINE_PROP_INC
#undef _INC_SHD_STR_LINE_PROP_REG
#undef _INC_SHD_STR_LINE_PROP_DEF
#undef _INIT_INC_SHD_STR_LINE_PROP
#undef _INC_SHD_STR_LINE_IS_TOKEN
#undef _INC_SHD_STR_LINE_TYPE_STR_TO_ENUM

#undef _INC_SHD_STR_CLEAR_STR
#undef _INC_SHD_STR_PRINT_STR


#undef _TOKEN_INCLUDE
#undef _TOKEN_DEFINE
#undef _TOKEN_UNDEFINE
#undef _TOKEN_IF_DEFINED
#undef _TOKEN_IF_NOT_DEFINED
#undef _TOKEN_END_IF

#undef _INC_SHD_STR_PROP_IS_TOKEN

#undef _GLSL_INCLUDE_FILE_EXTENSION
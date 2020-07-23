//
// Created by vladl on 13/07/2020.
//

#include "Shader.h"
#include <obj/util/data/Set.h>
#include <obj/util/data/Map.h>

std::string engine::Shader::_pathToShadersFolder = std::string(__NO_PATH_GIVEN__);

static std::string& trimString(std::string& str) {
    while(str[0] == ' ' && str.length() > 0)
        str.erase(str.begin());
    while(str[str.length()] == '\0' && str[str.length() - 1] == ' ' && str.length() > 0)
        str.erase(str.end() - 1);

    return str;
}

[[maybe_unused]] static INC_SHD_STR_LINE_PROP includeFileInShaderAnalyseLine ( const engine::String& codeLine ) noexcept {
    INC_SHD_STR_LINE_PROP properties;
    _INIT_INC_SHD_STR_LINE_PROP(properties);

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

            std::cout << "Define ! \n";

            code += ( engine::String(_TOKEN_DEFINE) + " " + (* lineProperties.tokenName ) + " " + (* lineProperties.tokenReplaceValue) );   
            // defineTokens.insert( engine::NonConstexprPair <engine::String, engine::String> ( (*lineProperties.tokenName), (*lineProperties.tokenReplaceValue) ) );
            defineTokens.put( *lineProperties.tokenName, *lineProperties.tokenReplaceValue );

            std::cout << defineTokens << '\n';

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
            std::cout << "END IF\n";
            return true;
    }    
    return true;
}

// [[maybe_unused]] static engine::String includeFileInShaderRec(const char* path, engine::SimpleSet < engine::NonConstexprPair < engine::String, engine::String > >& defineTokens ) noexcept {
[[maybe_unused]] static engine::String includeFileInShaderRec(const char* path, engine::HashMap < engine::String, engine::String >& defineTokens ) noexcept {
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
                        ( dirPath.replace(dirPath.findLast("/"), dirPath.length(), "/") + (*lineProperties.includeFileRelativePath) ).c_str(), 
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
                        _INC_SHD_STR_CLEAR_STR(lineProperties);
                        continue;
                    }
                }
            } else if(ifDepth == 0) {
                code += codeLine + "\n";
            }

            _INC_SHD_STR_CLEAR_STR(lineProperties);
        }
        INC_SHD_STR_LINE_PROP lineProperties = includeFileInShaderAnalyseLine( codeLine );

        if(_INC_SHD_STR_PROP_IS_TOKEN(lineProperties)) {
            // _INC_SHD_STR_PRINT_STR(lineProperties);

            includeFileInShaderProcessToken(lineProperties, code, defineTokens);
        } else {
            code += codeLine;
        }

        _INC_SHD_STR_CLEAR_STR(lineProperties);
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

            if(vertexCodeLine.contains("#include")) {
                vertexCodeLine.replaceFirst("#include", "");
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

engine::Shader &engine::Shader::setVec4(const std::string & name, const glm::vec4 & value) noexcept {
    glUniform4f ( glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z, value.w );
    return *this;
}

engine::Shader &engine::Shader::setMat3(const std::string & name, const glm::mat3 & value) noexcept {
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
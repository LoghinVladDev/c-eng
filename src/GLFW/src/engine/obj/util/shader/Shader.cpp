//
// Created by vladl on 13/07/2020.
//

#include "Shader.h"

std::string engine::Shader::_pathToShadersFolder = std::string(__NO_PATH_GIVEN__);

[[maybe_unused]] engine::Shader::Shader(const char *vertexPath, const char *fragmentPath, bool relativePath, bool enableDiagnostic) noexcept {
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vertexFile;
    std::ifstream fragmentFile;

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
        Shader::diagnoseShaderCompilation(vertexID);

    fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentID, 1, &fragmentCodePtr, nullptr);
    glCompileShader(fragmentID);

    if(enableDiagnostic)
        Shader::diagnoseShaderCompilation(fragmentID);

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
        Shader::diagnoseShaderCompilation(vertexID);

    fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentID, 1, &fragmentCodePtr, nullptr);
    glCompileShader(fragmentID);

    if(enableDiagnostic)
        Shader::diagnoseShaderCompilation(fragmentID);

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
        std::cout << "Shader compilation success" << std::endl;
    }
}

void engine::Shader::diagnoseShaderCompilation(int shaderID) noexcept {
    int32 successStatus;
    char infoLog[512];

    glGetShaderiv( shaderID, GL_COMPILE_STATUS, &successStatus );
    if( !successStatus ) {
        glGetShaderInfoLog( shaderID, 512, nullptr, infoLog );
        std::cout << "Shader compilation failed : " << infoLog << std::endl;
    } else {
        std::cout << "Shader compilation success" << std::endl;
    }
}

[[maybe_unused]] [[nodiscard]] int engine::Shader::getID() const noexcept {
    return this->ID;
}

engine::Shader::~Shader() {
    glDeleteProgram(this->ID);
}

void engine::Shader::setShadersFolder(const std::string & path) noexcept {
    Shader::_pathToShadersFolder = path;
}

void engine::Shader::setShadersFolder(const char * path) noexcept {
    Shader::_pathToShadersFolder = std::string(path);
}



//
// Created by vladl on 12/07/2020.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <obj/util/shader/Shader.h>
#include <cmath>
#include <obj/util/diag/Diagnostic.h>


//
//float vertices[] = {
//        -0.5f, -0.5f, 0.0f,
//        0.5f, -0.5f, 0.0f,
//        0.0f, 0.5f, 0.0f
//};
//
float vertices[] = {
        -0.8f, 0.6f, 0.0f,  1.0f, 0.0f, 0.0f,
        -0.2f, 0.75f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.3f, -0.4f, 0.0f, 0.0f, 0.0f, 1.0f
};

//float vertices[] = {
//    0.4f, 0.8f, 0.0f, // tl
//    0.9f, 0.8f, 0.0f, // tr
//    0.8f, -0.5f, 0.0f,// br
//    0.3f, -0.5f, 0.0f,// bl
//
//    -0.8f, 0.0f, 0.0f,
//    -0.7f, 0.5f, 0.0f,
//    -0.5f, -0.6f, 0.0f,
//    -0.2f, 0.0f, 0.0f
//};

float pentagonVertices[] = {
        //-0.025f, -0.3f, 0.0f, // centre

        -0.3f, -0.8f, 0.0f,
        -0.6f, -0.2f, 0.0f,
        -0.275f, 0.6f, 0.0f,
        0.4f, 0.550f, 0.0f,
        0.7f, -0.35f, 0.0f
};

unsigned int pentagonIndices[] = {
        0, 1, 2,
        0, 2, 3,
        0, 3, 4
};

unsigned int indices[] = {
        0, 1, 2
};

unsigned int pentagonVBO;
unsigned int pentagonVAO;
unsigned int pentagonEBO;
unsigned int pentagonVertexShader;
unsigned int pentagonFragmentShader;
unsigned int pentagonShader;

unsigned int elementBufferObject;
unsigned int vertexArrayObject;
unsigned int vertexBufferObject;
unsigned int vertexShader;
unsigned int fragmentShader;
unsigned int shaderProgram;

const char* vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "layout (location = 1) in vec3 aColor;\n"
                                 "out vec3 colour;\n"
                                 "void main() {\n"
                                 "gl_Position = vec4(aPos, 1.0);\n"
                                 "colour = aColor;\n"
                                 "}\0";


const char* pentagonFragmentSource =  "#version 330 core\n"
                                      "out vec4 fragColor;\n"
                                      "in vec4 vertexColor;\n"
                                      "void main() {\n"
                                      "    fragColor = vertexColor;\n"
                                      "}\0";

const char* fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "in vec3 colour;\n"
                                   "void main() {\n"
                                   "FragColor = vec4(colour, 1.0);\n"
                                   "}\0";

engine::Shader *shader;

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInputCallback (GLFWwindow* window, int key, int scanCode, int action, int mods);
void render() noexcept;
void prepareVBO();
void prepareVertexShader();
void prepareFragmentShader();
void prepareShaderProgram();
void deleteShaders();

void linkVertexAttributes();
void linkElementBufferObject();

void checkShaderProgramCompileErrors(unsigned int shaderProgramID);
void checkShaderCompileErrors(unsigned int shaderID);

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "test", nullptr, nullptr);

    if(window == nullptr) {
        std::cout << "init window fail\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(! gladLoadGLLoader((GLADloadproc) glfwGetProcAddress )) {
        std::cout << "glad init fail\n";
        return -1;
    }

    glfwSetErrorCallback( (GLFWerrorfun) engine::Diagnostic::getErrorCallbackDiagFunc);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetKeyCallback(window, processInputCallback);

    prepareVBO();
//    prepareVertexShader();
//    prepareFragmentShader();
//    prepareShaderProgram();

//    shader = new engine::Shader(
//            R"(C:/Users/vladl/CLionProjects/c-eng/src/GLFW/src/shaders/triangle.vert)",
//            R"(C:/Users/vladl/CLionProjects/c-eng/src/GLFW/src/shaders/triangle.frag)",
//            false,
//            false
//    );
//
//    shader = new engine::Shader(
//            ( std::string(__SHADERS_PATH__) + "triangle.vert" ).c_str(),
//            ( std::string(__SHADERS_PATH__) + "triangle.frag" ).c_str(),
//            false,
//            true
//    );

    engine::Shader::setShadersFolder(__SHADERS_PATH__);

    shader = new engine::Shader(
            "triangle.vert",
            "triangle.frag",
            true,
            true
    );

    linkElementBufferObject();
    linkVertexAttributes();

//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while( !glfwWindowShouldClose(window) ) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vertexArrayObject);
    glDeleteBuffers(1, &vertexBufferObject);
    glDeleteBuffers(1, &elementBufferObject);

    glDeleteVertexArrays(1, &pentagonVAO);
    glDeleteBuffers(1, &pentagonVBO);
    glDeleteBuffers(1, &pentagonEBO);

    glDeleteProgram(shaderProgram);
    glDeleteProgram(pentagonShader);

    int nrAttrib;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttrib);

    delete shader;

    std::cout << nrAttrib << '\n';

    glfwTerminate();

    return 0;
}

void linkElementBufferObject(){
    glGenBuffers(1, &elementBufferObject);
    glGenBuffers(1, &pentagonEBO);
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nullptr"

/**
 * glVertexAttribPointer( vertexAttribNumber, size of vertexAttribute, vertexAttrib data type, normalizeData, stride, offset );
 *
 * vertexAttribNumber = which input for the shader program (inputs in shaders) => vertex shader compiled uses location = 0, hence param is 0
 * sizeof vertexAttribute = how many values represent one input val. Vector 3 => 3
 * data type = ...
 * normalizeData = if integer data type, can normalize to 0 for U and -1 for S data. otherwise, false
 * stride = space between consecutive data objects. 3 vectors of 3 coords, packed => 3 * sizeof datatype for jump
 * offset = where does the first param sit from the ptr.
 */
void linkVertexAttributes() {
    glGenVertexArrays(1, &vertexArrayObject);

    glBindVertexArray(vertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0 );
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glGenVertexArrays(1, &pentagonVAO);

    glBindVertexArray(pentagonVAO);
    glBindBuffer(GL_ARRAY_BUFFER, pentagonVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pentagonVertices), pentagonVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pentagonEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(pentagonIndices), pentagonIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0 );

    glEnableVertexAttribArray(0);
}

#pragma clang diagnostic pop

inline void render() noexcept {

    float greenValue = ( std::sin ( glfwGetTime() ) / 2.0f ) + 0.5f;
//    int vertexColorLocation = glGetUniformLocation(shaderProgram, "colour");

    shader->setVec3("colour", engine::VectorF().setY(greenValue));
    shader->use();

//    glUseProgram(shaderProgram);
    glBindVertexArray(vertexArrayObject);

//    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

//    glUseProgram(pentagonShader);
//    glBindVertexArray(pentagonVAO);
//    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
//    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void deleteShaders() {
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void prepareShaderProgram() {
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    checkShaderProgramCompileErrors(shaderProgram);

    deleteShaders();

    pentagonShader = glCreateProgram();
    glAttachShader(pentagonShader, pentagonVertexShader);
    glAttachShader(pentagonShader, pentagonFragmentShader);
    glLinkProgram(pentagonShader);

    checkShaderProgramCompileErrors(pentagonShader);

    glDeleteShader(pentagonVertexShader);
    glDeleteShader(pentagonFragmentShader);
}

void prepareFragmentShader() {
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    checkShaderCompileErrors(fragmentShader);

    pentagonFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(pentagonFragmentShader, 1, &pentagonFragmentSource, nullptr);
    glCompileShader(pentagonFragmentShader);

    checkShaderCompileErrors(pentagonFragmentShader);
}

/**
 * glBindBuffer 4'th param :
 *  GL_STATIC_DRAW = data set only once, used a lot
 *  GL_DYNAMIC_DRAW = data set and used a lot
 *  GL_STREAM_DRAW = data set only once and used a few times
 */
void prepareVBO() {
    glGenBuffers(1, &vertexBufferObject);
    glGenBuffers(1, &pentagonVBO);
//    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void prepareVertexShader() {
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    checkShaderCompileErrors(vertexShader);

    pentagonVertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(pentagonVertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(pentagonVertexShader);

    checkShaderCompileErrors(pentagonVertexShader);
}

void checkShaderProgramCompileErrors(unsigned int shaderProgramID) {
    int success;
    char infoLog[512];

    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);

    if(success) {
        std::cout << "Shader comp success\n";
    } else {
        glGetProgramInfoLog(shaderProgramID, 512, nullptr, infoLog);
        std::cout << "Error compiling vertex shader : " << infoLog << '\n';
    }
}

void checkShaderCompileErrors(unsigned int shaderID) {
    int success;
    char infoLog[512];

    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

    if(success) {
        std::cout << "Shader comp success\n";
    } else {
        glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
        std::cout << "Error compiling vertex shader : " << infoLog << '\n';
    }
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport ( 0, 0, width, height );
}

void processInputCallback (GLFWwindow* window, int key, int scanCode, int action, int mods) {
    if( action == GLFW_PRESS )
        if( key == GLFW_KEY_ESCAPE )
            glfwSetWindowShouldClose(window, true);
}
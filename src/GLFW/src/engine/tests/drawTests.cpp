//
// Created by vladl on 12/07/2020.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <obj/util/shader/Shader.h>
#include <cmath>
#include <obj/util/diag/Diagnostic.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb-image.h>

float vertices[] = {
    0.5f, 0.5f, 0.0f,      1.0f, 0.0f, 0.0f,      1.0f, 1.0f, //tr
    0.5f,-0.5f, 0.0f,      0.0f, 1.0f, 0.0f,      1.0f, 0.0f, //br
   -0.5f,-0.5f, 0.0f,      0.0f, 0.0f, 1.0f,      0.0f, 0.0f, //bl
   -0.5f, 0.5f, 0.0f,      1.0f, 1.0f, 0.0f,      0.0f, 1.0f  //br
};

unsigned int indices[] = {
    0, 1, 2,
    0, 2, 3
};

bool upPressed;
bool downPressed;

unsigned int elementBufferObject;
unsigned int vertexArrayObject;
unsigned int vertexBufferObject;
unsigned int vertexShader;
unsigned int fragmentShader;
unsigned int shaderProgram;

float interpolationVisibility = 0.2f;

uint32 texture1;
uint32 texture2;

engine::Shader *shader;

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInputCallback (GLFWwindow* window, int key, int scanCode, int action, int mods);
void render() noexcept;
void update() noexcept;
void prepareVBO();
void deleteShaders();

void linkVertexAttributes();
void linkElementBufferObject();

void checkShaderProgramCompileErrors(unsigned int shaderProgramID);
void checkShaderCompileErrors(unsigned int shaderID);

int imageWidth;
int imageHeight;
int numberOfChannels;
uint8* data;

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

    engine::Shader::setShadersFolder(__SHADERS_PATH__);

    shader = new engine::Shader(
        "triangle.vert",
        "triangle.frag",
        true,
        true
    );

    linkElementBufferObject();
    linkVertexAttributes();

    glGenTextures(1, &texture1);

    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // repeat width
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // repeat height

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //bi-linear filter for minimizing
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //bi-linear filter for magnifying

    stbi_set_flip_vertically_on_load(true);
    data = stbi_load( (std::string(__TEXTURES_PATH__) + "container.jpg").c_str(), &imageWidth, &imageHeight, &numberOfChannels, 0 );

    if(data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Image load failed" << std::endl;
    }
    stbi_image_free(data);

    glGenTextures(1, &texture2);

    glBindTexture(GL_TEXTURE_2D, texture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    data = stbi_load( (std::string(__TEXTURES_PATH__) + "awesomeface.png" ).c_str(), &imageWidth, &imageHeight, &numberOfChannels, 0);
    if(data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Image load failed" << std::endl;
    }
    stbi_image_free(data);

    shader->use();
    shader->setInt("texture1", 0);
    shader->setInt("texture2", 1);

    while( !glfwWindowShouldClose(window) ) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        update();
        render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vertexArrayObject);
    glDeleteBuffers(1, &vertexBufferObject);
    glDeleteBuffers(1, &elementBufferObject);

    glDeleteProgram(shaderProgram);

    int nrAttrib;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttrib);

    delete shader;

    std::cout << nrAttrib << '\n';

    glfwTerminate();

    return 0;
}

void linkElementBufferObject(){
    glGenBuffers(1, &elementBufferObject);
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0 );
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

#pragma clang diagnostic pop

void update() noexcept {
    if(upPressed && downPressed) {

    } else if(upPressed) {
        if (interpolationVisibility < 1.0f)
            interpolationVisibility += 0.01f;
    } else if(downPressed) {
        if (interpolationVisibility > 0.0f)
            interpolationVisibility -= 0.01f;
    }
}

inline void render() noexcept {
    shader->use();
    shader->setFloat("interpolation", interpolationVisibility);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glBindVertexArray(vertexArrayObject);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}

void deleteShaders() {
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}


/**
 * glBindBuffer 4'th param :
 *  GL_STATIC_DRAW = data set only once, used a lot
 *  GL_DYNAMIC_DRAW = data set and used a lot
 *  GL_STREAM_DRAW = data set only once and used a few times
 */
void prepareVBO() {
    glGenBuffers(1, &vertexBufferObject);
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
    if( action == GLFW_PRESS ) {
        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, true);

        if (key == GLFW_KEY_UP)
            upPressed = true;

        if (key == GLFW_KEY_DOWN)
            downPressed = true;
    } else if( action == GLFW_RELEASE ) {
        if (key == GLFW_KEY_UP)
            upPressed = false;

        if (key == GLFW_KEY_DOWN)
            downPressed = false;
    }
}
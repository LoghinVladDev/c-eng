//
// Created by loghin on 7/16/20.
//

#ifndef ENG1_LIGHTING_H
#include "../h/lighting.h"
#endif
#define STB_IMAGE_IMPLEMENTATION
#include <stb-image.h>

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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0 );
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

#pragma clang diagnostic pop

glm::vec3 forwardMovementVec;

bool up = false;
bool down = false;
bool left = false;
bool right = false;

float ratio = 800.0f / 600.0f;
float fov=85.0f;
void update() noexcept {
}

unsigned int transformLoc;

void initOpenGL() {
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
        std::cout << "glad1 init fail\n";
        return -1;
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetErrorCallback( (GLFWerrorfun) engine::Diagnostic::getErrorCallbackDiagFunc);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetKeyCallback(window, processInputCallback);

    glEnable(GL_DEPTH_TEST);
}

void initVars() {
    camera = new engine::Camera(glm::vec3(0.0f, 0.0f, 0.6f));
    engine::Shader::setShadersFolder(__SHADERS_PATH__);

    shader = new engine::Shader(
            "triangle.vert",
            "triangle.frag",
            true,
            true
    );
    shader->use();
    shader->setInt("texture1", 0);
    shader->setInt("texture2", 1);
}

void render() noexcept {
    int var = 0;
    std::cout << var++ << '\n';
    shader->use();
    std::cout << var++ << '\n';
    shader->setFloat("interpolation", interpolationVisibility);

    std::cout << var++ << '\n';
    glm::mat4 view = camera->getViewMatrix();

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(fov), ratio, 0.1f, 100.0f);

    std::cout << var++ << '\n';
    shader->setMat4("view", view);
    shader->setMat4("projection", projection);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);

    std::cout << var++ << '\n';
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glBindVertexArray(vertexArrayObject);

    std::cout << var++ << '\n';
    for(std::size_t i = 0; i < 10; i++) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        float angle = 20.0f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        shader->setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    std::cout << var++ << '\n';
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

void initTextures(){
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
        if (key == GLFW_KEY_ESCAPE) {
            glfwSetWindowShouldClose(window, true);
        }

        if( key == GLFW_KEY_W )
            up = true;
        if( key == GLFW_KEY_S )
            down = true;
        if( key == GLFW_KEY_A )
            left = true;
        if( key == GLFW_KEY_D )
            right = true;
    } else if ( action == GLFW_RELEASE ) {

        if( key == GLFW_KEY_W )
            up = false;
        if( key == GLFW_KEY_S )
            down = false;
        if( key == GLFW_KEY_A )
            left = false;
        if( key == GLFW_KEY_D )
            right = false;
    }
}

float lastX;
float lastY;


void mouseCallback(GLFWwindow* window, double xPos, double yPos){
    if (firstMouseCallback){
        lastX = (float) xPos;
        lastY = (float) yPos;
        firstMouseCallback = false;
    }
//
    auto xPosF = (float) xPos;
    auto yPosF = (float) yPos;
//
    float xOffset = xPosF - lastX;
    float yOffset = lastY - yPosF;
    lastX = xPosF;
    lastY = yPosF;
//
    constexpr float sensitivity = 0.1f;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    camera->processOrientation(xOffset, yOffset, true);
}
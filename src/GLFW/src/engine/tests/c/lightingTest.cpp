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

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <src/GLFW/src/engine/obj/util/obj/stdObj/Camera.h>

float deltaTime = 0.0f;
float lastFrame = 0.0f;
float currentFrame = 0.0f;


float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f,1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f, 1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f , 0.0f, 1.0f, 0.0f,  1.0f,  0.0f
};

float lightVertices[] = {
        -0.5f, -0.5f, -0.5f, // 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, // 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  //1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,//  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,//  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, // 0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f, // 0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  //1.0f, 0.0f,
        0.5f,  0.5f,  0.5f, // 1.0f, 1.0f,
        0.5f,  0.5f,  0.5f, // 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,//  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,//  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  //1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, // 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, // 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, // 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, // 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, // 1.0f, 0.0f,

        0.5f,  0.5f,  0.5f, // 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f, // 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  //0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, // 0.0f, 1.0f,
        0.5f, -0.5f,  0.5f, // 0.0f, 0.0f,
        0.5f,  0.5f,  0.5f, // 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, // 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  //1.0f, 1.0f,
        0.5f, -0.5f,  0.5f, // 1.0f, 0.0f,
        0.5f, -0.5f,  0.5f, // 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,//  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, // 0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f, // 0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  //1.0f, 1.0f,
        0.5f,  0.5f,  0.5f, // 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f, // 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, // 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f //, 0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
        glm::vec3( -1.0f,  0.0f,  0.0f),
        glm::vec3( 1.0f,  0.0f, 0.0f)
};

unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
};

bool firstMouseCallback = true;

unsigned int elementBufferObject;
unsigned int vertexArrayObject;
unsigned int vertexBufferObject;
unsigned int vertexShader;
unsigned int fragmentShader;
unsigned int shaderProgram;

unsigned int lightVAO;
unsigned int lightVBO;
unsigned int lightEBO;

float interpolationVisibility = 0.2f;

uint32 texture1;
uint32 texture2;

engine::Shader *shader;
engine::Shader *lightShader;
engine::Camera *camera;

void mouseCallback(GLFWwindow*, double, double);
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

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetErrorCallback( (GLFWerrorfun) engine::Diagnostic::getErrorCallbackDiagFunc);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetKeyCallback(window, processInputCallback);

    glEnable(GL_DEPTH_TEST);

    prepareVBO();

    camera = new engine::Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    engine::Shader::setShadersFolder(__SHADERS_PATH__);

    shader = new engine::Shader(
            "triangle.vert",
            "triangle.frag",
            true,
            true
    );

    lightShader = new engine::Shader(
            "light.vert",
            "light.frag",
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
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        update();
        render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete camera;

    glDeleteVertexArrays(1, &vertexArrayObject);
    glDeleteBuffers(1, &vertexBufferObject);
    glDeleteBuffers(1, &elementBufferObject);

    glDeleteProgram(shaderProgram);

    int nrAttrib;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttrib);

    delete shader;
    delete lightShader;

    std::cout << nrAttrib << '\n';

    glfwTerminate();

    return 0;
}

void linkElementBufferObject(){
    glGenBuffers(1, &elementBufferObject);
    glGenBuffers(1, &lightEBO);
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

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, lightVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(lightVertices), lightVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lightEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

}

#pragma clang diagnostic pop

glm::vec3 forwardMovementVec;

bool up = false;
bool down = false;
bool left = false;
bool right = false;

float ratio = 800.0f / 600.0f;
float fov=60.0f;
void update() noexcept {
    constexpr float movementSpeed = 2.5f;
    float velocity = movementSpeed * deltaTime;

    float origY = camera->getTransform().getLocation().y;

//    glm::vec3 front = camera->getFront();

    if(up && down) {

    } else if (up) {
        camera->getTransform().getLocation() += camera->getWorldFront() * velocity;
    } else if (down) {
        camera->getTransform().getLocation() -= camera->getWorldFront() * velocity;
    }

    if(left && right) {

    } else if(left) {
        camera->getTransform().getLocation() -= camera->getRight() * velocity;
    } else if(right) {
        camera->getTransform().getLocation() += camera->getRight() * velocity;
    }

    camera->getTransform().getLocation().y = origY;
}

unsigned int transformLoc;

constexpr float lightScaleConst = 0.1f;

glm::vec3 lightLoc = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 lightScale = glm::vec3(lightScaleConst, lightScaleConst, lightScaleConst);

inline void render() noexcept {
    int var = 0;
    shader->use();
//    shader->setFloat("interpolation", interpolationVisibility);

    glm::mat4 view = camera->getViewMatrix();

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(fov), ratio, 0.1f, 100.0f);

    shader->setMat4("view", view);
    shader->setMat4("projection", projection);
    shader->setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
    shader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    shader->setVec3("lightPos", lightLoc);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glBindVertexArray(vertexArrayObject);

    for(std::size_t i = 0; i < 2; i++) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
//        float angle = 20.0f * i;
//        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        shader->setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    lightShader->use();
    lightShader->setMat4("view", view);
    lightShader->setMat4("projection", projection);
    lightShader->setMat4("model", glm::scale(glm::translate(glm::mat4(1.0f), lightLoc), lightScale));

    double offset = glfwGetTime() * 40;

    lightLoc = glm::vec3(sin(glm::radians(offset)) * 2, sin(glm::radians(offset)), cos(glm::radians(offset)) * 2);

    glBindVertexArray(lightVAO);

    glDrawArrays(GL_TRIANGLES, 0, 36);
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
    glGenBuffers(1, &lightVBO);
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
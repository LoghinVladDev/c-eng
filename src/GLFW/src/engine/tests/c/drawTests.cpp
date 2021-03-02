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
#include <glm/gtc/type_ptr.hpp>

//float vertices[] = {
//    0.5f, 0.5f, 0.0f,      1.0f, 0.0f, 0.0f,      1.0f, 1.0f, //tr
//    0.5f,-0.5f, 0.0f,      0.0f, 1.0f, 0.0f,      1.0f, 0.0f, //br
//   -0.5f,-0.5f, 0.0f,      0.0f, 0.0f, 1.0f,      0.0f, 0.0f, //bl
//   -0.5f, 0.5f, 0.0f,      1.0f, 1.0f, 0.0f,      0.0f, 1.0f  //br
//};

float deltaTime = 0.0f;
float lastFrame = 0.0f;
float currentFrame = 0.0f;

float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

unsigned int indices[] = {
    0, 1, 2,
    0, 2, 3
};

bool upPressed;
bool downPressed;

bool firstMouseCallback = true;

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
float yaw = -90.0f;
float pitch;

//glm1::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
glm::mat4 trans = glm::mat4(1.0f);


glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

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
        std::cout << "glad1 init fail\n";
        return -1;
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetErrorCallback( (GLFWerrorfun) engine::Diagnostic::getErrorCallbackDiagFunc);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetKeyCallback(window, processInputCallback);

    glEnable(GL_DEPTH_TEST);

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

    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
    trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

    while( !glfwWindowShouldClose(window) ) {
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0 );
    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
//    glEnableVertexAttribArray(1);
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
float fov=45.0f;
void update() noexcept {
    float cameraSpeed = 2.5f * deltaTime;
//    constexpr float cameraSpeed = 0.05f;

    if( up && down ) {

    } else if( up )
        cameraPos += cameraSpeed * forwardMovementVec;
    else if( down )
        cameraPos -= cameraSpeed * forwardMovementVec;

    if( left && right ) {

    } else if( left )
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    else if ( right )
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

unsigned int transformLoc;


inline void render() noexcept {
    shader->use();
    shader->setFloat("interpolation", interpolationVisibility);

//    glm1::mat4 model = glm1::mat4(1.0f);
//    model = glm1::rotate(model, glm1::radians(-55.0f), glm1::vec3(1.0f, 0.0f, 0.0f));
//    trans = glm1::translate(trans, glm1::vec3(0.5f, -0.5f, 0.0f));
//    trans = glm1::rotate(trans, (float)glfwGetTime(), glm1::vec3(0.0, 0.0, 1.0));
//    trans = glm1::scale(trans, glm1::vec3(0.5f, 0.5f, 0.5f));
//    model = glm1::rotate(model, (float)glfwGetTime() * glm1::radians(50.0f), glm1::vec3(0.5f, 1.0f, 1.0f));

//    glm1::mat4 view = glm1::mat4(1.0f);
//    view = glm1::rotate(view, glm1::radians(cameraRotate), glm1::vec3(0.0f, 1.0f, 0.0f));
//    view = glm1::translate(view, glm1::vec3(0.0f, 0.0f, -3.0f)); // objects in front of camera => camera pos reversed

    constexpr float rad = 10.0f;

    float camX = std::sin((float)glfwGetTime()) * rad;
    float camZ = std::cos((float)glfwGetTime()) * rad;

    glm::mat4 view = glm::lookAt(
        glm::vec3(cameraPos.x, 0.0f, cameraPos.z), //pos
//        cameraPos + cameraFront, //tar,
        glm::vec3(cameraPos.x + cameraFront.x, cameraFront.y, cameraPos.z + cameraFront.z),
        cameraUp //up
    );

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(fov), ratio, 0.1f, 100.0f);

//    shader->setMat4("model", model);
    shader->setMat4("view", view);
    shader->setMat4("projection", projection);

//    std::cout << glfwGetTime() << '\n';

//    transformLoc = glGetUniformLocation(shader->getID(), "transform");
//    glUniformMatrix4fv (transformLoc, 1, GL_FALSE, glm1::value_ptr(trans));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glBindVertexArray(vertexArrayObject);

//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    for(std::size_t i = 0; i < 10; i++) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        float angle = 20.0f * i;
        if(i == 0 || i % 3 == 0)
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 1.0f));
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        shader->setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

//    shader->use();
//    shader->setFloat("interpolation", interpolationVisibility);
//
//    trans = glm1::mat4(1.0f);
//    trans = glm1::translate(trans, glm1::vec3(-0.5f, 0.5f, 0.0f));
//    trans = glm1::rotate(trans, (float)std::sin(glfwGetTime()), glm1::vec3(0.0, 0.0, 1.0));
//    trans = glm1::scale(trans, glm1::vec3(0.5f, 0.5f, 0.5f));
//
//    transformLoc = glGetUniformLocation(shader->getID(), "transform");
//    glUniformMatrix4fv (transformLoc, 1, GL_FALSE, glm1::value_ptr(trans));
//
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, texture1);
//
//    glActiveTexture(GL_TEXTURE1);
//    glBindTexture(GL_TEXTURE_2D, texture2);
//
//    glBindVertexArray(vertexArrayObject);
//
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
//    std::cout << xPos << ' ' << yPos << '\n';

    if (firstMouseCallback){
        lastX = (float) xPos;
        lastY = (float) yPos;
        firstMouseCallback = false;
    }

    auto xPosF = (float) xPos;
    auto yPosF = (float) yPos;

    float xOffset = xPosF - lastX;
    float yOffset = lastY - yPosF;
    lastX = xPosF;
    lastY = yPosF;

    constexpr float sensitivity = 0.1f;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    yaw += xOffset;
    pitch += yOffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

//    std::cout << yaw << ' ' << pitch << '\n';

    glm::vec3 direction;
//    direction.x = cos(glm1::radians(yaw)) * cos(glm1::radians(pitch));
//    direction.y = sin(glm1::radians(pitch));
//    direction.z = sin(glm1::radians(yaw)) * cos(glm1::radians(pitch));

    forwardMovementVec.x = cos(glm::radians(yaw));
    direction.y = sin(glm::radians(pitch));
    forwardMovementVec.z = sin(glm::radians(yaw));

    direction.x = forwardMovementVec.x * cos(glm::radians(pitch));
    direction.z = forwardMovementVec.z * cos(glm::radians(pitch));

    cameraFront = glm::normalize(direction);
}


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <types.h>
#include <src/GLFW/src/engine/obj/util/obj/stdObj/Camera.h>
#include <dependencies/stb_image/stb-image.h>
#include <src/GLFW/src/engine/obj/util/shader/Shader.h>
#include <src/GLFW/src/engine/obj/util/model/Model.h>

void framebufferSizeCallback(GLFWwindow*, int, int);
void mouseCallback(GLFWwindow*, double, double);
void scrollCallback(GLFWwindow*, double, double);
void processInputCallback(GLFWwindow*, int, int, int, int);
void processInput(GLFWwindow*);
void engineLoop(GLFWwindow*);

constexpr uint16 SCREEN_WIDTH = 800;
constexpr uint16 SCREEN_HEIGHT = 600;
constexpr float  SCREEN_RATIO = (float) SCREEN_WIDTH / (float) SCREEN_HEIGHT;

float lastX = SCREEN_WIDTH / 2.0f;
float lastY = SCREEN_HEIGHT/ 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

constexpr float FOV = 60.0f;

using namespace engine;
using namespace glm;

Camera* camera;
Shader* shader;
Model* modelObj;

void engineLoop(GLFWwindow* window) {
    float currentFrame = 0.0f;
    mat4 projection;
    mat4 view;
    mat4 model;

    while(!glfwWindowShouldClose(window)) {
        currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        ENG_CLEAR_FRAME();

        shader->use();

        projection = perspective(radians(FOV), SCREEN_RATIO, 0.1f, 100.0f);
        view = camera->getViewMatrix();

        shader->setMat4("projection", projection);
        shader->setMat4("view", view);

        model = mat4(1.0f);
        model = scale(
            translate(
                model, vec3(0.0f, 0.0f, 0.0f)
            ),
            vec3(1.0f, 1.0f, 1.0f)
        );

        shader->setMat4("model", model);

        modelObj->draw(*shader);

        ENG_FINISH_FRAME(window);
    }
}

int main(){
    glfwInit();

    ENG_SET_VERSION_LIMITATION(_GL_MIN_VER, _GL_MAX_VER);
    GLFWwindow* window;

    ENG_WINDOW_CREATE_WINDOW(window, SCREEN_WIDTH, SCREEN_HEIGHT);
    ENG_WINDOW_SET_CALLBACKS(window, framebufferSizeCallback, mouseCallback, scrollCallback);
    ENG_GLAD_INIT();

    stbi_set_flip_vertically_on_load(true);

    glEnable(GL_DEPTH_TEST);

    shader = new Shader(
            "triangle.vert",
            "triangle.frag",
            true,
            true
    );

    modelObj = new Model(std::string().append(__ASSETS_PATH__).append("backpackTestModel/backpack.obj"));

    camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

    engineLoop(window);

    glfwDestroyWindow(window);
    glfwTerminate();

    delete (camera);
    delete (shader);
    delete (modelObj);

    return 0;
}
//
// Created by loghin on 07/03/23.
//

#include "glfw_callbacks.h"
#include <engine.h>

void joystickConnectionCallback (int joystickId, int event) {

}

void monitorConnectionCallback (GLFWmonitor * pMonitor, int event) {

}

void windowCharCallback (GLFWwindow * pWindow, unsigned int code) {
    auto engine = static_cast < SLEngine > (glfwGetWindowUserPointer (pWindow));
}

void windowDropCallback (GLFWwindow * pWindow, int count, char const ** paths) {
    auto engine = static_cast < SLEngine > (glfwGetWindowUserPointer (pWindow));
}

void windowKeyCallback (GLFWwindow * pWindow, int key, int scancode, int action, int modifiers) {
    auto engine = static_cast < SLEngine > (glfwGetWindowUserPointer (pWindow));
}

void windowScrollCallback (GLFWwindow * pWindow, double xOffset, double yOffset) {
    auto engine = static_cast < SLEngine > (glfwGetWindowUserPointer (pWindow));
}

void windowCharModsCallback (GLFWwindow * pWindow, unsigned int code, int modifiers) {
    auto engine = static_cast < SLEngine > (glfwGetWindowUserPointer (pWindow));
}

void windowMouseEnterCallback (GLFWwindow * pWindow, int entered) {
    auto engine = static_cast < SLEngine > (glfwGetWindowUserPointer (pWindow));
}

void windowMouseMoveCallback (GLFWwindow * pWindow, double xPos, double yPos) {
    auto engine = static_cast < SLEngine > (glfwGetWindowUserPointer (pWindow));
}

void windowSurfaceResizeCallback (GLFWwindow * pWindow, int width, int height) {
    auto engine = static_cast < SLEngine > (glfwGetWindowUserPointer (pWindow));
}

void windowMouseButtonCallback (GLFWwindow * pWindow, int button, int action, int modifiers) {
    auto engine = static_cast < SLEngine > (glfwGetWindowUserPointer (pWindow));
}

void windowCloseCallback (GLFWwindow * pWindow) {
    auto engine = static_cast < SLEngine > (glfwGetWindowUserPointer (pWindow));

    slEngineRequestShutdown (engine);
}

void windowFocusCallback (GLFWwindow * pWindow, int focused) {
    auto engine = static_cast < SLEngine > (glfwGetWindowUserPointer (pWindow));
}

void windowIconifyCallback (GLFWwindow * pWindow, int iconified) {
    auto engine = static_cast < SLEngine > (glfwGetWindowUserPointer (pWindow));
}

void windowMaximizeCallback (GLFWwindow * pWindow, int maximized) {
    auto engine = static_cast < SLEngine > (glfwGetWindowUserPointer (pWindow));
}

void windowMoveCallback (GLFWwindow * pWindow, int xPos, int yPos) {
    auto engine = static_cast < SLEngine > (glfwGetWindowUserPointer (pWindow));
}

void windowRefreshCallback (GLFWwindow * pWindow) {
    auto engine = static_cast < SLEngine > (glfwGetWindowUserPointer (pWindow));
}

void windowResizeCallback (GLFWwindow * pWindow, int width, int height) {
    auto engine = static_cast < SLEngine > (glfwGetWindowUserPointer (pWindow));
}

void windowContentScaleCallback (GLFWwindow * pWindow, float xScale, float yScale) {
    auto engine = static_cast < SLEngine > (glfwGetWindowUserPointer (pWindow));
}

//
// Created by loghin on 07/03/23.
//

#ifndef __C_ENG_GLFW_CALLBACKS_H__
#define __C_ENG_GLFW_CALLBACKS_H__

#include <GLFW/glfw3.h>

void joystickConnectionCallback (int joystickId, int event);
void monitorConnectionCallback (GLFWmonitor * pMonitor, int event);
void windowCharCallback (GLFWwindow * pWindow, unsigned int code);
void windowDropCallback (GLFWwindow * pWindow, int count, char const ** paths);
void windowKeyCallback (GLFWwindow * pWindow, int key, int scancode, int action, int modifiers);
void windowScrollCallback (GLFWwindow * pWindow, double xOffset, double yOffset);
void windowCharModsCallback (GLFWwindow * pWindow, unsigned int code, int modifiers);
void windowMouseEnterCallback (GLFWwindow * pWindow, int entered);
void windowMouseMoveCallback (GLFWwindow * pWindow, double xPos, double yPos);
void windowSurfaceResizeCallback (GLFWwindow * pWindow, int width, int height);
void windowMouseButtonCallback (GLFWwindow * pWindow, int button, int action, int modifiers);
void windowCloseCallback (GLFWwindow * pWindow);
void windowFocusCallback (GLFWwindow * pWindow, int focused);
void windowIconifyCallback (GLFWwindow * pWindow, int iconified);
void windowMaximizeCallback (GLFWwindow * pWindow, int maximized);
void windowMoveCallback (GLFWwindow * pWindow, int xPos, int yPos);
void windowRefreshCallback (GLFWwindow * pWindow);
void windowResizeCallback (GLFWwindow * pWindow, int width, int height);
void windowContentScaleCallback (GLFWwindow * pWindow, float xScale, float yScale);

#endif //__C_ENG_GLFW_CALLBACKS_H__

//
// Created by vladl on 09/07/2020.
//

#include "Window.h"

#include <Engine.h>
#include <obj/util/struct/inputAxisFunc.h>

std::map <GLFWwindow*, engine::Window*> engine::Window::GLFWWindowToWindowMap = std::map <GLFWwindow*, engine::Window*>();

void engine::Window::init(int, char **) noexcept {
//    glfwSetKeyCallback( this->_window, this->_keyHandlerCallback );// TODO : put in engine init !!
}

void engine::Window::defaultHandlerKeyCallback(GLFWwindow * window, int key, int scanCode, int action, int mods) noexcept {
    Window* windowObj = Window::getWindowByGLFWWindow(window);

    if(action == KeyListener::KEY_PRESSED) {
        for (KeyListener *listener : windowObj->keyListeners)
            listener->keyPressed(key, scanCode, (KeyListener::KeyModifier) mods);
        return;
    }
    else if ( action == KeyListener::KEY_RELEASED ) {
        for (KeyListener *listener : windowObj->keyListeners)
            listener->keyReleased(key, scanCode, (KeyListener::KeyModifier) mods);
        return;
    }
    else if ( action == KeyListener::KEY_HELD ) {
        for (KeyListener *listener : windowObj->keyListeners)
            listener->keyHeld(key, scanCode, (KeyListener::KeyModifier) mods);
        return;
    }
}

void engine::Window::defaultMouseMoveHandlerCallback(GLFWwindow * window, double xPos, double yPos) noexcept {
    Window* windowObj = Window::getWindowByGLFWWindow(window);

    updateInputAxis((int) xPos, (int) yPos);

    for(MouseListener* listener : windowObj->mouseListeners)
        listener->mouseMoved(xPos, yPos);
}

void engine::Window::defaultMouseScrollHandlerCallback(GLFWwindow * window, double xOffset, double yOffset) noexcept {
    Window* windowObj = Window::getWindowByGLFWWindow(window);

    for(MouseListener* listener : windowObj->mouseListeners)
        listener->mouseScrolled(xOffset, yOffset);
}

void engine::Window::defaultMouseClickedHandlerCallback(GLFWwindow * window, int button, int action, int mods) noexcept {
    Window* windowObj = Window::getWindowByGLFWWindow(window);

    if(action == MouseListener::MOUSE_PRESSED) {
        for(MouseListener* listener : windowObj->mouseListeners)
            listener->mouseClicked(button, mods);
    } else {
        for(MouseListener* listener : windowObj->mouseListeners)
            listener->mouseReleased(button, mods);
    }
}

void engine::Window::run(int argc, char ** argv) noexcept(false) {
    this->init(argc, argv);

    this->_window = glfwCreateWindow(this->_size.getWidth(), this->_size.getHeight(), this->_title, nullptr, nullptr);

    if(this->_window == nullptr)
        throw WindowCreateNullException();

    Window::GLFWWindowToWindowMap.insert(std::pair<GLFWwindow*, Window*> ( this->_window, this ) );

    this->_setCallbacks();
    this->_setMouseOptions();
}

void engine::Window::_setCallbacks() noexcept {
    glfwSetKeyCallback( this->_window, this->_keyHandlerCallback );
    glfwSetFramebufferSizeCallback(this->_window, this->_resizeWindowCallback);
    glfwSetCursorPosCallback(this->_window, this->_mouseMoveCallback);
    glfwSetMouseButtonCallback(this->_window, this->_mouseClickCallback);
    glfwSetScrollCallback(this->_window, this->_mouseScrollCallback);
}

void engine::Window::defaultResizeWindowCallback(GLFWwindow * window, int width, int height) noexcept {
    Window* obj = Window::getWindowByGLFWWindow(window);

    obj->_viewportWidth = width;
    obj->_viewportHeight = height;

    glViewport(0, 0, width, height);
}

void engine::Window::_setMouseOptions() noexcept {
    if(this->_mouseModifiers & CURSOR_MOUSE_SHOWN)
        this->enableMouseCursor();
    if(this->_mouseModifiers & CURSOR_MOUSE_HIDDEN)
        this->hideMouseCursor();
    if(this->_mouseModifiers & CURSOR_MOUSE_DISABLED)
        this->disableMouseCursor();
    if(this->_mouseModifiers & CURSOR_RAW_INPUT)
        this->enableRawMouseInput();
}

[[maybe_unused]] void engine::Window::close() noexcept {
    glfwSetWindowShouldClose(this->_window, true);
}
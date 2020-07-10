//
// Created by vladl on 09/07/2020.
//

#include "Window.h"

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

    for(MouseListener* listener : windowObj->mouseListeners)
        listener->mouseMoved(xPos, yPos);
}

void engine::Window::defaultMouseScrolledHandlerCallback(GLFWwindow * window, double xOff, double yOff) noexcept {
    Window* windowObj = Window::getWindowByGLFWWindow(window);

    for(MouseListener* listener : windowObj->mouseListeners)
        listener->mouseScrolled(xOff, yOff);
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

    glfwSetKeyCallback( this->_window, this->_keyHandlerCallback );
    glfwSetFramebufferSizeCallback(this->_window, this->_resizeWindowCallback);
    glfwSetCursorPosCallback(this->_window, this->_mouseMoveCallback);
    glfwSetMouseButtonCallback(this->_window, this->_mouseClickCallback);
    glfwSetScrollCallback(this->_window, this->_mouseScrollCallback);

    this->disableMouseCursor();
    this->enableRawMouseInput();
}

void engine::Window::defaultResizeWindowCallback(GLFWwindow * window, int width, int height) noexcept {
    Window* obj = Window::getWindowByGLFWWindow(window);

    obj->_viewportWidth = width;
    obj->_viewportHeight = height;

    glViewport(0, 0, width, height);
}


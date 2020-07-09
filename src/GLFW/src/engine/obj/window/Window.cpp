//
// Created by vladl on 09/07/2020.
//

#include "Window.h"

std::map <GLFWwindow*, Engine::Window*> Engine::Window::GLFWWindowToWindowMap = std::map <GLFWwindow*, Engine::Window*>();

void Engine::Window::init(int, char **) noexcept {
    glfwSetKeyCallback( this->_window, this->_keyHandlerCallback );
}

void Engine::Window::defaultHandlerKeyCallback(GLFWwindow * window, int key, int scanCode, int action, int mods) noexcept {
    Window* windowObj = Window::getWindowByGLFWWindow(window);

    if(action == KeyListener::KEY_PRESSED)
        for( KeyListener* listener : windowObj->keyListeners ) {
            listener->keyPressed(key, scanCode, mods);
        }
    else
        for( KeyListener* listener : windowObj->keyListeners ) {
            listener->keyReleased(key, scanCode, mods);
        }
}

void Engine::Window::run(int argc, char ** argv) noexcept {
    this->init(argc, argv);
}

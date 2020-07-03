//
// Created by Vlad on 03/07/2020.
//

#include <iostream>
#include "Window.h"

std::list<KeyListener> Window::keyListeners = std::list<KeyListener> ();

[[maybe_unused]] Window::Window(int width, int height, int x, int y, const char * title) noexcept :
    _position(x, y),
    _size(width, height),
    _title(title)
{ }

void Window::defaultRedrawFunction() {
    Window::defaultDisplayFunction();
}

void Window::init(int argumentCounter, char** argumentVector) noexcept {
    glutInit(&argumentCounter, argumentVector);

    glutInitWindowPosition( this->_position.getX(), this->_position.getY() );
    glutInitWindowSize(this->_size.getWidth(), this->_size.getHeight() );

    glutInitDisplayMode( this->_displayMode );

    glutCreateWindow( this->_title );
}

void Window::defaultDisplayFunction() {
    glClear(DEFAULT_CLEAR_MASK_FLAGS);

    glutSwapBuffers();
}

void Window::defaultKeyboardHandlerFunction(uint8 key, int x, int y) {
    //TODO : figure out how to add handlers

    std::cout << "REG KEY, key = " << key << ", x = " << x << ", y = " << y << '\n';

    for(KeyListener listener : Window::keyListeners){
        listener.keyPressed(key);
    }
}

void Window::defaultSpecialKeyHandlerFunction(int key, int x, int y) {
    //TODO : figure out how to add handlers

//    std::cout << "REG KEY, key = " << key << ", x = " << x << ", y = " << y << '\n';

    for(KeyListener listener : Window::keyListeners){
        listener.keyPressed(key + sizeof(uint8));
    }
}

void Window::defaultKeyUpHandlerFunction(uint8 key, int x, int y) {
    for(KeyListener listener : Window::keyListeners){
        listener.keyReleased(key);
    }
}

void Window::defaultSpecUpHandlerFunction(int key, int x, int y) {
    for(KeyListener listener : Window::keyListeners){
        listener.keyReleased(key + sizeof(uint8));
    }
}

void Window::defaultReshapeFunction(int newWidth, int newHeight){
    if( newHeight == 0 )
        newHeight = 1;

    float aspectRatio = (float)newWidth / (float)newHeight;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, newWidth, newHeight);
    gluPerspective(45, aspectRatio, 1, 100);
    glMatrixMode(GL_MODELVIEW);
}

[[maybe_unused]] void Window::run(int argumentCounter, char** argumentVector) noexcept {
    this->init(argumentCounter, argumentVector);

    glutDisplayFunc(this->_displayFunction);
    glutReshapeFunc(this->_reshapeFunction);
    glutIdleFunc(this->_redrawFunction);

    glutKeyboardFunc(this->_keyHandlerFunction);
    glutKeyboardUpFunc(this->_keyUpHandlerFunction);

    glutSpecialFunc(this->_specialKeyHandlerFunction);
    glutSpecialUpFunc(this->_specKeyUpHandlerFunction);

    glutMainLoop();
}

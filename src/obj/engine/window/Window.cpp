//
// Created by Vlad on 03/07/2020.
//

#include <iostream>
#include "Window.h"

std::list<KeyListener*> Window::keyListeners = std::list<KeyListener*> ();
//bool Window::pressedKeysArray[KEYS_CNT];

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

void Window::_keyConversionFormatting(uint16 & key) {
    if(key >= 'A' && key <= 'Z'){
        key +=32;
        return;
    }
}

void Window::defaultKeyboardHandlerFunction(uint8 key, [[maybe_unused]] int x, [[maybe_unused]] int y) {
    uint16 _key = key;
    Window::_keyConversionFormatting(_key);

//    if(!Window::pressedKeysArray[key])
    for(KeyListener *listener : Window::keyListeners)
        listener->keyPressed(_key);

//    Window::pressedKeysArray[key] = true;
}

void Window::defaultSpecialKeyHandlerFunction(int key,[[maybe_unused]] int x,[[maybe_unused]] int y) {
    uint16 _key = key + UINT8_MAX;
    Window::_keyConversionFormatting(_key);

//    if(!Window::pressedKeysArray[key])
    for(KeyListener *listener : Window::keyListeners)
        listener->keyPressed(_key);

//    Window::pressedKeysArray[key] = true;
}

void Window::defaultKeyUpHandlerFunction(uint8 key,[[maybe_unused]] int x,[[maybe_unused]] int y) {
    uint16 _key = key;
    Window::_keyConversionFormatting(_key);

//    if(Window::pressedKeysArray[key])
    for(KeyListener *listener : Window::keyListeners)
        listener->keyReleased(_key);

//    Window::pressedKeysArray[key] = false;
}

void Window::defaultSpecUpHandlerFunction(int key,[[maybe_unused]] int x,[[maybe_unused]] int y) {
    uint16 _key = key + UINT8_MAX;
    Window::_keyConversionFormatting(_key);

//    if(Window::pressedKeysArray[key])
    for(KeyListener *listener : Window::keyListeners)
        listener->keyReleased(_key);

//    Window::pressedKeysArray[key] = false;
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

    glutIgnoreKeyRepeat(1);

    glutMainLoop();
}


//
// Created by Vlad on 03/07/2020.
//

#include <iostream>
#include "Window.h"

std::list<KeyListener*> Window::keyListeners = std::list<KeyListener*> ();
std::list<MouseListener*> Window::mouseListeners = std::list<MouseListener*> ();
bool Window::_mouseMoving = false;

[[maybe_unused]] inline Window::Window(int width, int height, int x, int y, const char * title) noexcept :
    _position(x, y),
    _size(width, height),
    _title(title)
{ }

void Window::defaultRedrawFunction() noexcept {
    Window::defaultDisplayFunction();
}

void Window::init(int argumentCounter, char** argumentVector) noexcept {
    glutInit(&argumentCounter, argumentVector);

    glutInitWindowPosition( this->_position.getX(), this->_position.getY() );
    glutInitWindowSize(this->_size.getWidth(), this->_size.getHeight() );

    glutInitDisplayMode( this->_displayMode );

    glutCreateWindow( this->_title );
}

[[maybe_unused]] inline void Window::setSize (int width, int height) noexcept {
    this->_size = Size(width, height);
}

[[maybe_unused]] inline void Window::setPosition (int x, int y) noexcept {
    this->_position = Point(x,y);
}

[[maybe_unused]] inline void Window::setDisplayMode (int displayMode) noexcept {
    this->_displayMode = displayMode;
}

[[maybe_unused]] void Window::setDisplayFunctionCallback ( void (*callback)() ) noexcept {
    this->_displayFunction = callback;
}

[[maybe_unused]] inline void Window::setReshapeFunctionCallback ( void (*callback) (int, int) ) noexcept {
    this->_reshapeFunction = callback;
}

[[maybe_unused]] void Window::setRedrawFunctionCallback ( void (*callback) () ) noexcept {
    this->_redrawFunction = callback;
}

[[maybe_unused]] inline void Window::setKeyHandlerCallback ( void (*callback) (uint8, int, int) ) noexcept {
    this->_keyHandlerFunction = callback;
}

[[maybe_unused]] inline void Window::setSpecialKeyHandlerCallback ( void (*callback) (int, int, int) ) noexcept {
    this->_specialKeyHandlerFunction = callback;
}

[[maybe_unused]] inline void Window::setKeyUpHandlerCallback ( void (*callback) (uint8, int, int) ) noexcept {
    this->_keyUpHandlerFunction = callback;
}

[[maybe_unused]] inline void Window::setSpecKeyUpHandlerCallback ( void (*callback) (int, int, int) ) noexcept {
    this->_specKeyUpHandlerFunction = callback;
}

[[maybe_unused]] inline void Window::setMouseButtonCallback(void (*callback)(int, int, int, int)) noexcept {
    this->_mouseButtonFunction = callback;
}

[[maybe_unused]] inline void Window::setMouseMoveCallback(void (*callback)(int, int)) noexcept {
    this->_mouseMoveFunction = callback;
}

[[maybe_unused]] [[nodiscard]] inline Size& Window::getSize() noexcept {
    return this->_size;
}

[[maybe_unused]] [[nodiscard]] inline Point& Window::getPosition() noexcept {
    return this->_position;
}

[[maybe_unused]] [[nodiscard]] inline const char* Window::getTitle() const noexcept {
    return this->_title;
}

[[maybe_unused]] inline void Window::disableKeyRepeats() noexcept {
    glutIgnoreKeyRepeat(1);
}

[[maybe_unused]] inline void Window::enableKeyRepeats() noexcept {
    glutIgnoreKeyRepeat(0);
}

void Window::defaultDisplayFunction() noexcept {
    glClear(DEFAULT_CLEAR_MASK_FLAGS);

    glutSwapBuffers();
}

void Window::_keyConversionFormatting(uint16 & key) noexcept {
    if(key >= 'A' && key <= 'Z'){
        key +=32;
        return;
    }
}

void Window::defaultKeyboardHandlerFunction(uint8 key, [[maybe_unused]] int x, [[maybe_unused]] int y) noexcept {
    uint16 _key = key;
    Window::_keyConversionFormatting(_key);

    for(KeyListener *listener : Window::keyListeners)
        listener->keyPressed(_key);
}

void Window::defaultSpecialKeyHandlerFunction(int key,[[maybe_unused]] int x,[[maybe_unused]] int y) noexcept {
    uint16 _key = key + UINT8_MAX;
    Window::_keyConversionFormatting(_key);

    for(KeyListener *listener : Window::keyListeners)
        listener->keyPressed(_key);
}

void Window::defaultKeyUpHandlerFunction(uint8 key,[[maybe_unused]] int x,[[maybe_unused]] int y) noexcept {
    uint16 _key = key;
    Window::_keyConversionFormatting(_key);

    for(KeyListener *listener : Window::keyListeners)
        listener->keyReleased(_key);
}

void Window::defaultMouseHandlerFunction(int button, int state, int x, int y) noexcept {
    for(MouseListener *listener : Window::mouseListeners)
        listener->buttonPressed( (uint16) button, (uint16) state, x, y);
}

void Window::defaultMouseMoveFunction(int x, int y) noexcept {
//    std::cout << x << ' ' << y << '\n';
    Window::_mouseMoving = true;
    for(MouseListener* listener : Window::mouseListeners){
        listener->moveEvent(x, y);
    }
}

void Window::defaultSpecUpHandlerFunction(int key,[[maybe_unused]] int x,[[maybe_unused]] int y) noexcept {
    uint16 _key = key + UINT8_MAX;
    Window::_keyConversionFormatting(_key);

    for(KeyListener *listener : Window::keyListeners)
        listener->keyReleased(_key);
}

void Window::defaultReshapeFunction(int newWidth, int newHeight) noexcept {
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

    glutMouseFunc(this->_mouseButtonFunction);
    glutMotionFunc(this->_mouseMoveFunction);
    glutPassiveMotionFunc(this->_mouseMoveFunction);

    glutIgnoreKeyRepeat(1);

    glutMainLoop();
}

[[maybe_unused]] std::list <KeyListener*> & Window::getActiveKeyListeners() noexcept  {
    return Window::keyListeners;
}

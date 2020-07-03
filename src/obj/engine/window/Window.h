//
// Created by Vlad on 03/07/2020.
//
#pragma once
#ifndef ENG1_WINDOW_H
#define ENG1_WINDOW_H

#include "../util/Size.h"
#include "../util/geom/Point.h"
#include "../util/defs/types.h"
#include "../util/event/KeyListener.h"
#include <GL/glu.h>
#include <list>

#include <GL/freeglut.h>

#ifndef DEFAULT_WINDOW_WIDTH
#define DEFAULT_WINDOW_WIDTH 1366
#endif
#ifndef DEFAULT_WINDOW_HEIGHT
#define DEFAULT_WINDOW_HEIGHT 768
#endif

#ifndef DEFAULT_WINDOW_TITLE
#define DEFAULT_WINDOW_TITLE "engineTest"
#endif

#ifndef DEFAULT_WINDOW_STARTING_POSITION_X
#define DEFAULT_WINDOW_STARTING_POSITION_X 100
#endif

#ifndef DEFAULT_WINDOW_STARTING_POSITION_Y
#define DEFAULT_WINDOW_STARTING_POSITION_Y 100
#endif

#ifndef DEFAULT_DISPLAY_MODE_FLAGS
#define DEFAULT_DISPLAY_MODE_FLAGS (uint32)GLUT_RGBA | (uint32)GLUT_DOUBLE | (uint32)GLUT_DEPTH
#endif

#ifndef DEFAULT_CLEAR_MASK_FLAGS
#define DEFAULT_CLEAR_MASK_FLAGS (uint32) GL_COLOR_BUFFER_BIT | (uint32) GL_DEPTH_BUFFER_BIT
#endif

class [[maybe_unused]] Window {
private:
    Point _position     { DEFAULT_WINDOW_STARTING_POSITION_X, DEFAULT_WINDOW_STARTING_POSITION_Y };
    Size _size          { DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT } ;

    const char* _title  { DEFAULT_WINDOW_TITLE};

    int _displayMode    { DEFAULT_DISPLAY_MODE_FLAGS};

    void init(int, char**) noexcept;

    static std::list<KeyListener> keyListeners;

    static void defaultDisplayFunction();
    static void defaultReshapeFunction(int, int);
    static void defaultRedrawFunction();

    static void defaultKeyboardHandlerFunction(uint8, int, int);
    static void defaultSpecialKeyHandlerFunction(int, int, int);

    static void defaultKeyUpHandlerFunction(uint8, int, int);
    static void defaultSpecUpHandlerFunction(int, int, int);

    void (*_displayFunction) () = defaultDisplayFunction;
    void (*_reshapeFunction) (int, int) = defaultReshapeFunction;
    void (*_redrawFunction)  () = defaultRedrawFunction;

    void (*_keyHandlerFunction)         (uint8, int, int)   = defaultKeyboardHandlerFunction;
    void (*_specialKeyHandlerFunction)  (int, int, int)     = defaultSpecialKeyHandlerFunction;
    void (*_keyUpHandlerFunction)       (uint8, int, int)   = defaultKeyUpHandlerFunction;
    void (*_specKeyUpHandlerFunction)   (int, int, int)     = defaultSpecUpHandlerFunction;

public:
    [[maybe_unused]] explicit Window(
        int = DEFAULT_WINDOW_WIDTH,
        int = DEFAULT_WINDOW_HEIGHT,
        int = DEFAULT_WINDOW_STARTING_POSITION_X,
        int = DEFAULT_WINDOW_STARTING_POSITION_Y,
        const char* = DEFAULT_WINDOW_TITLE
    ) noexcept;

    [[maybe_unused]] inline void setSize        (const Size& size)      noexcept { this->_size = size; }
    [[maybe_unused]] inline void setSize        (int width, int height) noexcept {this->_size = Size(width, height);}

    [[maybe_unused]] inline void setPosition    (const Point& point) noexcept { this->_position = point; }
    [[maybe_unused]] inline void setPosition    (int x, int y)       noexcept { this->_position = Point(x,y); }

    [[maybe_unused]] inline void setTitle       (const char* title)  noexcept { this->_title = title; }
    [[maybe_unused]] inline void setDisplayMode (int displayMode)    noexcept { this->_displayMode = displayMode; }

    [[maybe_unused]] inline void setDisplayFunctionCallback     ( void (*callback) ()                = defaultDisplayFunction )              noexcept { this->_displayFunction           = callback; }
    [[maybe_unused]] inline void setReshapeFunctionCallback     ( void (*callback) (int, int)        = defaultReshapeFunction )              noexcept { this->_reshapeFunction           = callback; }
    [[maybe_unused]] inline void setRedrawFunctionCallback      ( void (*callback) ()                = defaultRedrawFunction  )              noexcept { this->_redrawFunction            = callback; }

    [[maybe_unused]] inline void setKeyHandlerCallback          ( void (*callback) (uint8, int, int) = defaultKeyboardHandlerFunction )      noexcept { this->_keyHandlerFunction        = callback; }
    [[maybe_unused]] inline void setSpecialKeyHandlerCallback   ( void (*callback) (int, int, int)   = defaultSpecialKeyHandlerFunction )    noexcept { this->_specialKeyHandlerFunction = callback; }

    [[maybe_unused]] inline void setKeyUpHandlerCallback        ( void (*callback) (uint8, int, int) = defaultKeyUpHandlerFunction )         noexcept { this->_keyUpHandlerFunction      = callback; }
    [[maybe_unused]] inline void setSpecKeyUpHandlerCallback    ( void (*callback) (int, int, int)   = defaultSpecUpHandlerFunction )        noexcept { this->_specKeyUpHandlerFunction  = callback; }

    [[maybe_unused]] [[nodiscard]] inline Size&         getSize()        noexcept { return this->_size; }
    [[maybe_unused]] [[nodiscard]] inline Point&        getPosition()    noexcept { return this->_position; }
    [[maybe_unused]] [[nodiscard]] inline const char*   getTitle() const noexcept { return this->_title; }

    [[maybe_unused]] inline void addKeyListener(const KeyListener& listener) noexcept { Window::keyListeners.push_back(listener); }

    [[maybe_unused]] void run(int = 1, char** = nullptr) noexcept;
};

//std::list<KeyListener> keyListeners = std::list<KeyListener> ();

#endif //ENG1_WINDOW_H

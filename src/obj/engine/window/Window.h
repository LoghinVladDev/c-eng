//
// Created by Vlad on 03/07/2020.
//
#pragma once
#ifndef ENG1_WINDOW_H
#define ENG1_WINDOW_H


#include "../preCompiledHeaders.h"
#include "../util/defs/types.h"
#include "../util/event/KeyListener.h"

#include <GL/glu.h>
#include <GL/freeglut.h>

#include <list>
//#include <hash_set>

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

//#define KEYS_CNT 512

class [[maybe_unused]] Window {
private:
    Point _position     { DEFAULT_WINDOW_STARTING_POSITION_X, DEFAULT_WINDOW_STARTING_POSITION_Y };
    Size _size          { DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT } ;

    const char* _title  { DEFAULT_WINDOW_TITLE};

    int _displayMode    { DEFAULT_DISPLAY_MODE_FLAGS};

    void init(int, char**) noexcept;

    static std::list<KeyListener*> keyListeners;
//    static bool pressedKeysArray [KEYS_CNT];

    static void defaultDisplayFunction()            noexcept;
    static void defaultReshapeFunction(int, int)    noexcept;
    static void defaultRedrawFunction()             noexcept;

    static void defaultKeyboardHandlerFunction(uint8, [[maybe_unused]] int, int)    noexcept;
    static void defaultSpecialKeyHandlerFunction(int, int, int)                     noexcept;

    static void defaultKeyUpHandlerFunction(uint8, int, int)                        noexcept;
    static void defaultSpecUpHandlerFunction(int, int, int)                         noexcept;

    void (*_displayFunction) () = defaultDisplayFunction;
    void (*_reshapeFunction) (int, int) = defaultReshapeFunction;
    void (*_redrawFunction)  () = defaultRedrawFunction;

    void (*_keyHandlerFunction)         (uint8, int, int)   = defaultKeyboardHandlerFunction;
    void (*_specialKeyHandlerFunction)  (int, int, int)     = defaultSpecialKeyHandlerFunction;
    void (*_keyUpHandlerFunction)       (uint8, int, int)   = defaultKeyUpHandlerFunction;
    void (*_specKeyUpHandlerFunction)   (int, int, int)     = defaultSpecUpHandlerFunction;

    static void _keyConversionFormatting(uint16 &) noexcept;

public:
    [[maybe_unused]] explicit Window(
            int = DEFAULT_WINDOW_WIDTH,
            int = DEFAULT_WINDOW_HEIGHT,
            int = DEFAULT_WINDOW_STARTING_POSITION_X,
            int = DEFAULT_WINDOW_STARTING_POSITION_Y,
            const char* = DEFAULT_WINDOW_TITLE
    ) noexcept;

    [[maybe_unused]] explicit Window(
            const Size& resolution,
            const Point& location,
            const char* title= DEFAULT_WINDOW_TITLE
    ) noexcept :
        _position(location),
         _size(resolution),
         _title(title) {

    }

    [[maybe_unused]] void setSize        (const Size& size)  noexcept {
        this->_size = size;
    }

    [[maybe_unused]] void setSize        (int ,int)     noexcept;

    [[maybe_unused]] void setPosition    (const Point& point) noexcept {
        this->_position = point;
    }

    [[maybe_unused]] void setPosition    (int, int)     noexcept;

    [[maybe_unused]] void setTitle       (const char* title)  noexcept {
        this->_title = title;
    }

    [[maybe_unused]] void setDisplayMode (int)          noexcept;

    [[maybe_unused]] void setDisplayFunctionCallback     ( void (*) ()                = defaultDisplayFunction )              noexcept;
    [[maybe_unused]] void setReshapeFunctionCallback     ( void (*) (int, int)        = defaultReshapeFunction )              noexcept;
    [[maybe_unused]] void setRedrawFunctionCallback      ( void (*) ()                = defaultRedrawFunction  )              noexcept;

    [[maybe_unused]] void setKeyHandlerCallback          ( void (*) (uint8, int, int) = defaultKeyboardHandlerFunction )      noexcept;
    [[maybe_unused]] void setSpecialKeyHandlerCallback   ( void (*) (int, int, int)   = defaultSpecialKeyHandlerFunction )    noexcept;

    [[maybe_unused]] void setKeyUpHandlerCallback        ( void (*) (uint8, int, int) = defaultKeyUpHandlerFunction )         noexcept;
    [[maybe_unused]] void setSpecKeyUpHandlerCallback    ( void (*) (int, int, int)   = defaultSpecUpHandlerFunction )        noexcept;

    [[maybe_unused]] [[nodiscard]] Size&         getSize()        noexcept;
    [[maybe_unused]] [[nodiscard]] Point&        getPosition()    noexcept;
    [[maybe_unused]] [[nodiscard]] const char*   getTitle() const noexcept;

    [[maybe_unused]] void addKeyListener(KeyListener* listener) noexcept {
        listener->setParent(this);
        Window::keyListeners.push_back(listener);
    }

    [[maybe_unused]] static std::list <KeyListener*> & getActiveKeyListeners () noexcept {
        return Window::keyListeners;
    }

    [[maybe_unused]] static void disableKeyRepeats() noexcept;
    [[maybe_unused]] static void enableKeyRepeats()  noexcept;

    [[maybe_unused]] void run(int = 1, char** = nullptr) noexcept;
};

//std::list<KeyListener> keyListeners = std::list<KeyListener> ();

#endif //ENG1_WINDOW_H

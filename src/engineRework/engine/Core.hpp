//
// Created by loghin on 20.12.2021.
//

#ifndef __C_ENG_CORE_HPP
#define __C_ENG_CORE_HPP

#include <CDS/Types>

namespace engine {

    __C_ENG_ENUM ( EngineState, cds :: uint8 ) {
        __C_ENG_ENUM_FIELD ( EngineState, Inactive,                 0x00U ),    // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( EngineState, Startup,                  0x01U ),    // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( EngineState, StartupAcquiringSettings, 0x02U ),    // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( EngineState, Running,                  0x03U ),    // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( EngineState, Shutdown,                 0x04U )     // NOLINT(clion-misra-cpp2008-5-0-6)
    };

    __C_ENG_ENUM ( LogLevel, cds :: uint8 ) {
        __C_ENG_ENUM_FIELD ( LogLevel, Forced,      0x00U ), // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( LogLevel, System,      0x01U ), // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( LogLevel, Fatal,       0x02U ), // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( LogLevel, Critical,    0x03U ), // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( LogLevel, Error,       0x04U ), // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( LogLevel, Warning,     0x05U ), // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( LogLevel, Debug,       0x06U ), // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( LogLevel, Info,        0x07U )  // NOLINT(clion-misra-cpp2008-5-0-6)
    };

    __C_ENG_ENUM ( EventType, cds :: uint8 ) {
        __C_ENG_ENUM_FIELD ( EventType, Custom,                         0x00U ), // NOLINT(clion-misra-cpp2008-5-0-6)

        __C_ENG_ENUM_FIELD ( EventType, CustomKeyEvent,                 0x01U ), // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( EventType, KeyPressEvent,                  0x02U ), // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( EventType, KeyReleaseEvent,                0x03U ), // NOLINT(clion-misra-cpp2008-5-0-6)

        __C_ENG_ENUM_FIELD ( EventType, CustomMouseEvent,               0x04U ), // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( EventType, MouseMoveEvent,                 0x05U ), // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( EventType, MouseEnterEvent,                0x06U ), // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( EventType, MouseLeaveEvent,                0x07U ), // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( EventType, MouseScrollEvent,               0x08U ), // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( EventType, MousePressEvent,                0x09U ), // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( EventType, MouseReleaseEvent,              0x0aU ), // NOLINT(clion-misra-cpp2008-5-0-6)

        __C_ENG_ENUM_FIELD ( EventType, CustomWindowEvent,              0x0bU ), // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( EventType, WindowResizeEvent,              0x0cU ), // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( EventType, WindowFrameBufferResizeEvent,   0x0dU ), // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( EventType, WindowCloseEvent,               0x0eU ), // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( EventType, WindowContentScaleEvent,        0x0fU ), // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( EventType, WindowMoveEvent,                0x10U ), // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( EventType, WindowRestoreEvent,             0x11U ), // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( EventType, WindowMinimizeEvent,            0x12U ), // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( EventType, WindowMaximizeEvent,            0x13U ), // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( EventType, WindowGainFocusEvent,           0x14U ), // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( EventType, WindowLoseFocusEvent,           0x15U ), // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( EventType, WindowRefreshRequestEvent,      0x16U ), // NOLINT(clion-misra-cpp2008-5-0-6)

        __C_ENG_ENUM_FIELD ( EventType, CustomControllerEvent,          0x17U ), // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( EventType, ControllerConnectEvent,         0x18U ), // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( EventType, ControllerDisconnectEvent,      0x19U ), // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( EventType, ControllerAxisEvent,            0x1aU ), // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( EventType, ControllerButtonPressEvent,     0x1bU ), // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( EventType, ControllerButtonReleaseEvent,   0x1cU ), // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( EventType, ControllerHatEvent,             0x1dU )  // NOLINT(clion-misra-cpp2008-5-0-6)
    };

    __C_ENG_ENUM ( KeyModifier, cds :: uint16 ) {
        __C_ENG_ENUM_FIELD ( KeyModifier, None,     0x0000U ),                                              // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( KeyModifier, Shift,    static_cast < cds :: uint16 > ( GLFW_MOD_SHIFT ) ),
        __C_ENG_ENUM_FIELD ( KeyModifier, Control,  static_cast < cds :: uint16 > ( GLFW_MOD_CONTROL ) ),
        __C_ENG_ENUM_FIELD ( KeyModifier, Alt,      static_cast < cds :: uint16 > ( GLFW_MOD_ALT ) ),
        __C_ENG_ENUM_FIELD ( KeyModifier, Super,    static_cast < cds :: uint16 > ( GLFW_MOD_SUPER ) ),
        __C_ENG_ENUM_FIELD ( KeyModifier, CapsLock, static_cast < cds :: uint16 > ( GLFW_MOD_CAPS_LOCK ) ),
        __C_ENG_ENUM_FIELD ( KeyModifier, NumLock,  static_cast < cds :: uint16 > ( GLFW_MOD_NUM_LOCK ) ),

        __C_ENG_ENUM_FIELD ( KeyModifier, MaxValue, KeyModifierNumLock )
    };

    __C_ENG_ENUM ( Key, cds :: sint16 ) {
        __C_ENG_ENUM_FIELD ( Key, Unknown,          static_cast < cds :: sint16 > ( GLFW_KEY_UNKNOWN ) ),
        __C_ENG_ENUM_FIELD ( Key, Space,            static_cast < cds :: sint16 > ( GLFW_KEY_SPACE ) ),
        __C_ENG_ENUM_FIELD ( Key, Apostrophe,       static_cast < cds :: sint16 > ( GLFW_KEY_APOSTROPHE ) ),
        __C_ENG_ENUM_FIELD ( Key, Comma,            static_cast < cds :: sint16 > ( GLFW_KEY_COMMA ) ), /* , */
        __C_ENG_ENUM_FIELD ( Key, Minus,            static_cast < cds :: sint16 > ( GLFW_KEY_MINUS ) ), /* - */
        __C_ENG_ENUM_FIELD ( Key, Period,           static_cast < cds :: sint16 > ( GLFW_KEY_PERIOD ) ), /* . */
        __C_ENG_ENUM_FIELD ( Key, Slash,            static_cast < cds :: sint16 > ( GLFW_KEY_SLASH ) ), /* / */
        __C_ENG_ENUM_FIELD ( Key, 0,                static_cast < cds :: sint16 > ( GLFW_KEY_0 ) ),
        __C_ENG_ENUM_FIELD ( Key, 1,                static_cast < cds :: sint16 > ( GLFW_KEY_1 ) ),
        __C_ENG_ENUM_FIELD ( Key, 2,                static_cast < cds :: sint16 > ( GLFW_KEY_2 ) ),
        __C_ENG_ENUM_FIELD ( Key, 3,                static_cast < cds :: sint16 > ( GLFW_KEY_3 ) ),
        __C_ENG_ENUM_FIELD ( Key, 4,                static_cast < cds :: sint16 > ( GLFW_KEY_4 ) ),
        __C_ENG_ENUM_FIELD ( Key, 5,                static_cast < cds :: sint16 > ( GLFW_KEY_5 ) ),
        __C_ENG_ENUM_FIELD ( Key, 6,                static_cast < cds :: sint16 > ( GLFW_KEY_6 ) ),
        __C_ENG_ENUM_FIELD ( Key, 7,                static_cast < cds :: sint16 > ( GLFW_KEY_7 ) ),
        __C_ENG_ENUM_FIELD ( Key, 8,                static_cast < cds :: sint16 > ( GLFW_KEY_8 ) ),
        __C_ENG_ENUM_FIELD ( Key, 9,                static_cast < cds :: sint16 > ( GLFW_KEY_9 ) ),
        __C_ENG_ENUM_FIELD ( Key, Semicolon,        static_cast < cds :: sint16 > ( GLFW_KEY_SEMICOLON ) ), /* ; */
        __C_ENG_ENUM_FIELD ( Key, Equal,            static_cast < cds :: sint16 > ( GLFW_KEY_EQUAL ) ), /* = */
        __C_ENG_ENUM_FIELD ( Key, A,                static_cast < cds :: sint16 > ( GLFW_KEY_A ) ),
        __C_ENG_ENUM_FIELD ( Key, B,                static_cast < cds :: sint16 > ( GLFW_KEY_B ) ),
        __C_ENG_ENUM_FIELD ( Key, C,                static_cast < cds :: sint16 > ( GLFW_KEY_C ) ),
        __C_ENG_ENUM_FIELD ( Key, D,                static_cast < cds :: sint16 > ( GLFW_KEY_D ) ),
        __C_ENG_ENUM_FIELD ( Key, E,                static_cast < cds :: sint16 > ( GLFW_KEY_E ) ),
        __C_ENG_ENUM_FIELD ( Key, F,                static_cast < cds :: sint16 > ( GLFW_KEY_F ) ),
        __C_ENG_ENUM_FIELD ( Key, G,                static_cast < cds :: sint16 > ( GLFW_KEY_G ) ),
        __C_ENG_ENUM_FIELD ( Key, H,                static_cast < cds :: sint16 > ( GLFW_KEY_H ) ),
        __C_ENG_ENUM_FIELD ( Key, I,                static_cast < cds :: sint16 > ( GLFW_KEY_I ) ),
        __C_ENG_ENUM_FIELD ( Key, J,                static_cast < cds :: sint16 > ( GLFW_KEY_J ) ),
        __C_ENG_ENUM_FIELD ( Key, K,                static_cast < cds :: sint16 > ( GLFW_KEY_K ) ),
        __C_ENG_ENUM_FIELD ( Key, L,                static_cast < cds :: sint16 > ( GLFW_KEY_L ) ),
        __C_ENG_ENUM_FIELD ( Key, M,                static_cast < cds :: sint16 > ( GLFW_KEY_M ) ),
        __C_ENG_ENUM_FIELD ( Key, N,                static_cast < cds :: sint16 > ( GLFW_KEY_N ) ),
        __C_ENG_ENUM_FIELD ( Key, O,                static_cast < cds :: sint16 > ( GLFW_KEY_O ) ),
        __C_ENG_ENUM_FIELD ( Key, P,                static_cast < cds :: sint16 > ( GLFW_KEY_P ) ),
        __C_ENG_ENUM_FIELD ( Key, Q,                static_cast < cds :: sint16 > ( GLFW_KEY_Q ) ),
        __C_ENG_ENUM_FIELD ( Key, R,                static_cast < cds :: sint16 > ( GLFW_KEY_R ) ),
        __C_ENG_ENUM_FIELD ( Key, S,                static_cast < cds :: sint16 > ( GLFW_KEY_S ) ),
        __C_ENG_ENUM_FIELD ( Key, T,                static_cast < cds :: sint16 > ( GLFW_KEY_T ) ),
        __C_ENG_ENUM_FIELD ( Key, U,                static_cast < cds :: sint16 > ( GLFW_KEY_U ) ),
        __C_ENG_ENUM_FIELD ( Key, V,                static_cast < cds :: sint16 > ( GLFW_KEY_V ) ),
        __C_ENG_ENUM_FIELD ( Key, W,                static_cast < cds :: sint16 > ( GLFW_KEY_W ) ),
        __C_ENG_ENUM_FIELD ( Key, X,                static_cast < cds :: sint16 > ( GLFW_KEY_X ) ),
        __C_ENG_ENUM_FIELD ( Key, Y,                static_cast < cds :: sint16 > ( GLFW_KEY_Y ) ),
        __C_ENG_ENUM_FIELD ( Key, Z,                static_cast < cds :: sint16 > ( GLFW_KEY_Z ) ),
        __C_ENG_ENUM_FIELD ( Key, LeftBracket,      static_cast < cds :: sint16 > ( GLFW_KEY_LEFT_BRACKET ) ), /* [ */
        __C_ENG_ENUM_FIELD ( Key, Backslash,        static_cast < cds :: sint16 > ( GLFW_KEY_BACKSLASH ) ), /* \ */
        __C_ENG_ENUM_FIELD ( Key, RightBracket,     static_cast < cds :: sint16 > ( GLFW_KEY_RIGHT_BRACKET ) ), /* ] */
        __C_ENG_ENUM_FIELD ( Key, GraveAccent,      static_cast < cds :: sint16 > ( GLFW_KEY_GRAVE_ACCENT ) ), /* ` */
        __C_ENG_ENUM_FIELD ( Key, World1,           static_cast < cds :: sint16 > ( GLFW_KEY_WORLD_1 ) ), /* non-US #1 */
        __C_ENG_ENUM_FIELD ( Key, World2,           static_cast < cds :: sint16 > ( GLFW_KEY_WORLD_2 ) ), /* non-US #2 */
        __C_ENG_ENUM_FIELD ( Key, Escape,           static_cast < cds :: sint16 > ( GLFW_KEY_ESCAPE ) ),
        __C_ENG_ENUM_FIELD ( Key, Enter,            static_cast < cds :: sint16 > ( GLFW_KEY_ENTER ) ),
        __C_ENG_ENUM_FIELD ( Key, Tab,              static_cast < cds :: sint16 > ( GLFW_KEY_TAB ) ),
        __C_ENG_ENUM_FIELD ( Key, Backspace,        static_cast < cds :: sint16 > ( GLFW_KEY_BACKSPACE ) ),
        __C_ENG_ENUM_FIELD ( Key, Insert,           static_cast < cds :: sint16 > ( GLFW_KEY_INSERT ) ),
        __C_ENG_ENUM_FIELD ( Key, Delete,           static_cast < cds :: sint16 > ( GLFW_KEY_DELETE ) ),
        __C_ENG_ENUM_FIELD ( Key, Right,            static_cast < cds :: sint16 > ( GLFW_KEY_RIGHT ) ),
        __C_ENG_ENUM_FIELD ( Key, Left,             static_cast < cds :: sint16 > ( GLFW_KEY_LEFT ) ),
        __C_ENG_ENUM_FIELD ( Key, Down,             static_cast < cds :: sint16 > ( GLFW_KEY_DOWN ) ),
        __C_ENG_ENUM_FIELD ( Key, Up,               static_cast < cds :: sint16 > ( GLFW_KEY_UP ) ),
        __C_ENG_ENUM_FIELD ( Key, PageUp,           static_cast < cds :: sint16 > ( GLFW_KEY_PAGE_UP ) ),
        __C_ENG_ENUM_FIELD ( Key, PageDown,         static_cast < cds :: sint16 > ( GLFW_KEY_PAGE_DOWN ) ),
        __C_ENG_ENUM_FIELD ( Key, Home,             static_cast < cds :: sint16 > ( GLFW_KEY_HOME ) ),
        __C_ENG_ENUM_FIELD ( Key, End,              static_cast < cds :: sint16 > ( GLFW_KEY_END ) ),
        __C_ENG_ENUM_FIELD ( Key, CapsLock,         static_cast < cds :: sint16 > ( GLFW_KEY_CAPS_LOCK ) ),
        __C_ENG_ENUM_FIELD ( Key, ScrollLock,       static_cast < cds :: sint16 > ( GLFW_KEY_SCROLL_LOCK ) ),
        __C_ENG_ENUM_FIELD ( Key, NumLock,          static_cast < cds :: sint16 > ( GLFW_KEY_NUM_LOCK ) ),
        __C_ENG_ENUM_FIELD ( Key, PrintScreen,      static_cast < cds :: sint16 > ( GLFW_KEY_PRINT_SCREEN ) ),
        __C_ENG_ENUM_FIELD ( Key, Pause,            static_cast < cds :: sint16 > ( GLFW_KEY_PAUSE ) ),
        __C_ENG_ENUM_FIELD ( Key, F1,               static_cast < cds :: sint16 > ( GLFW_KEY_F1 ) ),
        __C_ENG_ENUM_FIELD ( Key, F2,               static_cast < cds :: sint16 > ( GLFW_KEY_F2 ) ),
        __C_ENG_ENUM_FIELD ( Key, F3,               static_cast < cds :: sint16 > ( GLFW_KEY_F3 ) ),
        __C_ENG_ENUM_FIELD ( Key, F4,               static_cast < cds :: sint16 > ( GLFW_KEY_F4 ) ),
        __C_ENG_ENUM_FIELD ( Key, F5,               static_cast < cds :: sint16 > ( GLFW_KEY_F5 ) ),
        __C_ENG_ENUM_FIELD ( Key, F6,               static_cast < cds :: sint16 > ( GLFW_KEY_F6 ) ),
        __C_ENG_ENUM_FIELD ( Key, F7,               static_cast < cds :: sint16 > ( GLFW_KEY_F7 ) ),
        __C_ENG_ENUM_FIELD ( Key, F8,               static_cast < cds :: sint16 > ( GLFW_KEY_F8 ) ),
        __C_ENG_ENUM_FIELD ( Key, F9,               static_cast < cds :: sint16 > ( GLFW_KEY_F9 ) ),
        __C_ENG_ENUM_FIELD ( Key, F10,              static_cast < cds :: sint16 > ( GLFW_KEY_F10 ) ),
        __C_ENG_ENUM_FIELD ( Key, F11,              static_cast < cds :: sint16 > ( GLFW_KEY_F11 ) ),
        __C_ENG_ENUM_FIELD ( Key, F12,              static_cast < cds :: sint16 > ( GLFW_KEY_F12 ) ),
        __C_ENG_ENUM_FIELD ( Key, F13,              static_cast < cds :: sint16 > ( GLFW_KEY_F13 ) ),
        __C_ENG_ENUM_FIELD ( Key, F14,              static_cast < cds :: sint16 > ( GLFW_KEY_F14 ) ),
        __C_ENG_ENUM_FIELD ( Key, F15,              static_cast < cds :: sint16 > ( GLFW_KEY_F15 ) ),
        __C_ENG_ENUM_FIELD ( Key, F16,              static_cast < cds :: sint16 > ( GLFW_KEY_F16 ) ),
        __C_ENG_ENUM_FIELD ( Key, F17,              static_cast < cds :: sint16 > ( GLFW_KEY_F17 ) ),
        __C_ENG_ENUM_FIELD ( Key, F18,              static_cast < cds :: sint16 > ( GLFW_KEY_F18 ) ),
        __C_ENG_ENUM_FIELD ( Key, F19,              static_cast < cds :: sint16 > ( GLFW_KEY_F19 ) ),
        __C_ENG_ENUM_FIELD ( Key, F20,              static_cast < cds :: sint16 > ( GLFW_KEY_F20 ) ),
        __C_ENG_ENUM_FIELD ( Key, F21,              static_cast < cds :: sint16 > ( GLFW_KEY_F21 ) ),
        __C_ENG_ENUM_FIELD ( Key, F22,              static_cast < cds :: sint16 > ( GLFW_KEY_F22 ) ),
        __C_ENG_ENUM_FIELD ( Key, F23,              static_cast < cds :: sint16 > ( GLFW_KEY_F23 ) ),
        __C_ENG_ENUM_FIELD ( Key, F24,              static_cast < cds :: sint16 > ( GLFW_KEY_F24 ) ),
        __C_ENG_ENUM_FIELD ( Key, F25,              static_cast < cds :: sint16 > ( GLFW_KEY_F25 ) ),
        __C_ENG_ENUM_FIELD ( Key, Keypad0,          static_cast < cds :: sint16 > ( GLFW_KEY_KP_0 ) ),
        __C_ENG_ENUM_FIELD ( Key, Keypad1,          static_cast < cds :: sint16 > ( GLFW_KEY_KP_1 ) ),
        __C_ENG_ENUM_FIELD ( Key, Keypad2,          static_cast < cds :: sint16 > ( GLFW_KEY_KP_2 ) ),
        __C_ENG_ENUM_FIELD ( Key, Keypad3,          static_cast < cds :: sint16 > ( GLFW_KEY_KP_3 ) ),
        __C_ENG_ENUM_FIELD ( Key, Keypad4,          static_cast < cds :: sint16 > ( GLFW_KEY_KP_4 ) ),
        __C_ENG_ENUM_FIELD ( Key, Keypad5,          static_cast < cds :: sint16 > ( GLFW_KEY_KP_5 ) ),
        __C_ENG_ENUM_FIELD ( Key, Keypad6,          static_cast < cds :: sint16 > ( GLFW_KEY_KP_6 ) ),
        __C_ENG_ENUM_FIELD ( Key, Keypad7,          static_cast < cds :: sint16 > ( GLFW_KEY_KP_7 ) ),
        __C_ENG_ENUM_FIELD ( Key, Keypad8,          static_cast < cds :: sint16 > ( GLFW_KEY_KP_8 ) ),
        __C_ENG_ENUM_FIELD ( Key, Keypad9,          static_cast < cds :: sint16 > ( GLFW_KEY_KP_9 ) ),
        __C_ENG_ENUM_FIELD ( Key, KeypadDecimal,    static_cast < cds :: sint16 > ( GLFW_KEY_KP_DECIMAL ) ),
        __C_ENG_ENUM_FIELD ( Key, KeypadDivide,     static_cast < cds :: sint16 > ( GLFW_KEY_KP_DIVIDE ) ),
        __C_ENG_ENUM_FIELD ( Key, KeypadMultiply,   static_cast < cds :: sint16 > ( GLFW_KEY_KP_MULTIPLY ) ),
        __C_ENG_ENUM_FIELD ( Key, KeypadSubtract,   static_cast < cds :: sint16 > ( GLFW_KEY_KP_SUBTRACT ) ),
        __C_ENG_ENUM_FIELD ( Key, KeypadAdd,        static_cast < cds :: sint16 > ( GLFW_KEY_KP_ADD ) ),
        __C_ENG_ENUM_FIELD ( Key, KeypadEnter,      static_cast < cds :: sint16 > ( GLFW_KEY_KP_ENTER ) ),
        __C_ENG_ENUM_FIELD ( Key, KeypadEqual,      static_cast < cds :: sint16 > ( GLFW_KEY_KP_EQUAL ) ),
        __C_ENG_ENUM_FIELD ( Key, LeftShift,        static_cast < cds :: sint16 > ( GLFW_KEY_LEFT_SHIFT ) ),
        __C_ENG_ENUM_FIELD ( Key, LeftControl,      static_cast < cds :: sint16 > ( GLFW_KEY_LEFT_CONTROL ) ),
        __C_ENG_ENUM_FIELD ( Key, LeftAlt,          static_cast < cds :: sint16 > ( GLFW_KEY_LEFT_ALT ) ),
        __C_ENG_ENUM_FIELD ( Key, LeftSuper,        static_cast < cds :: sint16 > ( GLFW_KEY_LEFT_SUPER ) ),
        __C_ENG_ENUM_FIELD ( Key, RightShift,       static_cast < cds :: sint16 > ( GLFW_KEY_RIGHT_SHIFT ) ),
        __C_ENG_ENUM_FIELD ( Key, RightControl,     static_cast < cds :: sint16 > ( GLFW_KEY_RIGHT_CONTROL ) ),
        __C_ENG_ENUM_FIELD ( Key, RightAlt,         static_cast < cds :: sint16 > ( GLFW_KEY_RIGHT_ALT ) ),
        __C_ENG_ENUM_FIELD ( Key, RightSuper,       static_cast < cds :: sint16 > ( GLFW_KEY_RIGHT_SUPER ) ),
        __C_ENG_ENUM_FIELD ( Key, Menu,             static_cast < cds :: sint16 > ( GLFW_KEY_MENU ) )
    };

    __C_ENG_ENUM ( MouseButton, cds :: uint8 ) {
        __C_ENG_ENUM_FIELD ( MouseButton, 1,            static_cast < cds :: uint8 > ( GLFW_MOUSE_BUTTON_1 ) ),
        __C_ENG_ENUM_FIELD ( MouseButton, 2,            static_cast < cds :: uint8 > ( GLFW_MOUSE_BUTTON_2 ) ),
        __C_ENG_ENUM_FIELD ( MouseButton, 3,            static_cast < cds :: uint8 > ( GLFW_MOUSE_BUTTON_3 ) ),
        __C_ENG_ENUM_FIELD ( MouseButton, 4,            static_cast < cds :: uint8 > ( GLFW_MOUSE_BUTTON_4 ) ),
        __C_ENG_ENUM_FIELD ( MouseButton, 5,            static_cast < cds :: uint8 > ( GLFW_MOUSE_BUTTON_5 ) ),
        __C_ENG_ENUM_FIELD ( MouseButton, 6,            static_cast < cds :: uint8 > ( GLFW_MOUSE_BUTTON_6 ) ),
        __C_ENG_ENUM_FIELD ( MouseButton, 7,            static_cast < cds :: uint8 > ( GLFW_MOUSE_BUTTON_7 ) ),
        __C_ENG_ENUM_FIELD ( MouseButton, 8,            static_cast < cds :: uint8 > ( GLFW_MOUSE_BUTTON_8 ) ),

        __C_ENG_ENUM_FIELD ( MouseButton, Left,         MouseButton1 ),
        __C_ENG_ENUM_FIELD ( MouseButton, Right,        MouseButton2 ),
        __C_ENG_ENUM_FIELD ( MouseButton, Middle,       MouseButton3 ),

        __C_ENG_ENUM_FIELD ( MouseButton, Undefined,    0xffU ) // NOLINT(clion-misra-cpp2008-5-0-6)
    };

    __C_ENG_ENUM ( WindowFlag, cds :: uint16 ) {
        __C_ENG_ENUM_FIELD ( WindowFlag, None,                      0x0000U ),                  // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( WindowFlag, Resizable,                 0x0001U ),                  // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( WindowFlag, Borderless,                0x0002U ),                  // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( WindowFlag, StartMinimized,            0x0004U ),                  // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( WindowFlag, GrabFocusOnOpen,           0x0008U ),                  // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( WindowFlag, RestorePreviousMode,       0x0010U ),                  // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( WindowFlag, StayOnTop,                 0x0020U ),                  // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( WindowFlag, StartMaximized,            0x0040U ),                  // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( WindowFlag, CenterCursorOnCreate,      0x0080U ),                  // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( WindowFlag, TransparentFramebuffer,    0x0100U ),                  // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( WindowFlag, GrabFocusOnRaise,          0x0200U ),                  // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( WindowFlag, ScaleToMonitor,            0x0400U ),                  // NOLINT(clion-misra-cpp2008-5-0-6)

        __C_ENG_ENUM_FIELD ( WindowFlag, MaxValue,                  WindowFlagScaleToMonitor )
    };

    __C_ENG_ENUM ( WindowType, cds :: uint8 ) {
        __C_ENG_ENUM_FIELD ( WindowType, Windowed,              0x00U ), // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( WindowType, Fullscreen,            0x01U ), // NOLINT(clion-misra-cpp2008-5-0-6)
        __C_ENG_ENUM_FIELD ( WindowType, WindowedFullscreen,    0x02U )  // NOLINT(clion-misra-cpp2008-5-0-6)
    };

    __C_ENG_ENUM ( ControllerHatState, cds :: uint8 ) {
        __C_ENG_ENUM_FIELD ( ControllerHatState, Centered,  static_cast < cds :: uint8 > ( GLFW_HAT_CENTERED ) ),
        __C_ENG_ENUM_FIELD ( ControllerHatState, Up,        static_cast < cds :: uint8 > ( GLFW_HAT_UP ) ),
        __C_ENG_ENUM_FIELD ( ControllerHatState, Left,      static_cast < cds :: uint8 > ( GLFW_HAT_LEFT ) ),
        __C_ENG_ENUM_FIELD ( ControllerHatState, Right,     static_cast < cds :: uint8 > ( GLFW_HAT_RIGHT ) ),
        __C_ENG_ENUM_FIELD ( ControllerHatState, Down,      static_cast < cds :: uint8 > ( GLFW_HAT_DOWN ) ),
        __C_ENG_ENUM_FIELD ( ControllerHatState, LeftUp,    static_cast < cds :: uint8 > ( GLFW_HAT_LEFT_UP ) ),
        __C_ENG_ENUM_FIELD ( ControllerHatState, LeftDown,  static_cast < cds :: uint8 > ( GLFW_HAT_LEFT_DOWN ) ),
        __C_ENG_ENUM_FIELD ( ControllerHatState, RightUp,   static_cast < cds :: uint8 > ( GLFW_HAT_RIGHT_UP ) ),
        __C_ENG_ENUM_FIELD ( ControllerHatState, RightDown, static_cast < cds :: uint8 > ( GLFW_HAT_RIGHT_DOWN ) )
    };


    __C_ENG_STRUCT ( Position ) {
        cds :: uint32 x;
        cds :: uint32 y;
    };

    __C_ENG_STRUCT ( Size ) {
        cds :: uint32 width;
        cds :: uint32 height;
    };

    __C_ENG_STRUCT ( ColorChannelsDepth ) {
        cds :: uint32 red;
        cds :: uint32 green;
        cds :: uint32 blue;
    };

    __C_ENG_STRUCT ( MonitorVideoModeProperties ) {
        __C_ENG_TYPE ( Size )               size;
        __C_ENG_TYPE ( ColorChannelsDepth ) colorChannelsDepth;
        cds :: uint32                       refreshRate;
    };

    __C_ENG_STRUCT ( ContentScale ) {
        float x;
        float y;
    };

    __C_ENG_STRUCT ( MonitorWorkArea ) {
        __C_ENG_TYPE ( Position )   position;
        __C_ENG_TYPE ( Size )       size;
    };

    __C_ENG_ALIAS ( MonitorName,            cds :: StringLiteral );
    __C_ENG_ALIAS ( MonitorGammaRampValue,  cds :: uint16 * );
    __C_ENG_ALIAS ( Flags,                  cds :: uint32 );
    __C_ENG_ALIAS ( KeyModifiers,           __C_ENG_TYPE ( Flags ) );
    __C_ENG_ALIAS ( MonitorContentScale,    __C_ENG_TYPE ( ContentScale ) );
    __C_ENG_ALIAS ( WindowContentScale,     __C_ENG_TYPE ( ContentScale ) );
    __C_ENG_ALIAS ( WindowFlags,            __C_ENG_TYPE ( Flags ) );

    __C_ENG_STRUCT ( MonitorGammaRamp ) {
        cds :: uint32                           size;
        __C_ENG_TYPE ( MonitorGammaRampValue )  red;
        __C_ENG_TYPE ( MonitorGammaRampValue )  green;
        __C_ENG_TYPE ( MonitorGammaRampValue )  blue;
    };

    __C_ENG_STRUCT ( MonitorProperties ) {
        __C_ENG_TYPE ( MonitorName )                name;
        __C_ENG_TYPE ( Size )                       physicalSizeMM;
        __C_ENG_TYPE ( MonitorContentScale )        contentScale;
        __C_ENG_TYPE ( MonitorWorkArea )            workArea;
        __C_ENG_TYPE ( MonitorGammaRamp )           gammaRamp;
        __C_ENG_TYPE ( MonitorVideoModeProperties ) activeVideoMode;
    };


    __C_ENG_NO_DISCARD auto toString ( bool ) noexcept -> cds :: StringLiteral;
    __C_ENG_NO_DISCARD auto toString ( void const * ) noexcept -> cds :: String;

    __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( EngineState ) ) noexcept -> cds :: StringLiteral;
    __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( LogLevel ) ) noexcept -> cds :: StringLiteral;
    __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( EventType ) ) noexcept -> cds :: StringLiteral;
    __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( KeyModifier ) ) noexcept -> cds :: StringLiteral;
    __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( Key ) ) noexcept -> cds :: StringLiteral;
    __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( MouseButton ) ) noexcept -> cds :: StringLiteral;
    __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( WindowType ) ) noexcept -> cds :: StringLiteral;
    __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( WindowFlag ) ) noexcept -> cds :: StringLiteral;
    __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( ControllerHatState ) ) noexcept -> cds :: StringLiteral;

    __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( Position ) const & ) noexcept -> cds :: String;
    __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( Size ) const & ) noexcept -> cds :: String;
    __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( ColorChannelsDepth ) const & ) noexcept -> cds :: String;
    __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( MonitorVideoModeProperties ) const & ) noexcept -> cds :: String;
    __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( ContentScale ) const & ) noexcept -> cds :: String;
    __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( MonitorWorkArea ) const & ) noexcept -> cds :: String;
    __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( MonitorGammaRamp ) const & ) noexcept -> cds :: String;
    __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( MonitorProperties ) const & ) noexcept -> cds :: String;

    __C_ENG_NO_DISCARD auto keyModifiersToString ( __C_ENG_TYPE ( KeyModifiers ) ) noexcept -> cds :: String;
    __C_ENG_NO_DISCARD auto windowFlagsToString ( __C_ENG_TYPE ( WindowFlags ) ) noexcept -> cds :: String;


    __C_ENG_NO_DISCARD constexpr auto equals (
            __C_ENG_TYPE ( Position ) const & left,
            __C_ENG_TYPE ( Position ) const & right
    ) noexcept -> bool {

        return
            left.x == right.x &&
            left.y == right.y;
    }

    __C_ENG_NO_DISCARD constexpr auto equals (
            __C_ENG_TYPE ( Size ) const & left,
            __C_ENG_TYPE ( Size ) const & right
    ) noexcept -> bool {

        return
            left.width  == right.width &&
            left.height == right.height;
    }

    __C_ENG_NO_DISCARD constexpr auto equals (
            __C_ENG_TYPE ( ColorChannelsDepth ) const & left,
            __C_ENG_TYPE ( ColorChannelsDepth ) const & right
    ) noexcept -> bool {

        return
            left.red    == right.red &&
            left.green  == right.green &&
            left.blue   == right.blue;
    }

    __C_ENG_NO_DISCARD constexpr auto equals (
            __C_ENG_TYPE ( MonitorVideoModeProperties ) const & left,
            __C_ENG_TYPE ( MonitorVideoModeProperties ) const & right
    ) noexcept -> bool {

        return
            equals ( left.size, right.size ) &&
            equals ( left.colorChannelsDepth, right.colorChannelsDepth ) &&
            left.refreshRate == right.refreshRate;
    }

    __C_ENG_NO_DISCARD constexpr auto equals (
            __C_ENG_TYPE ( ContentScale ) const & left,
            __C_ENG_TYPE ( ContentScale ) const & right
    ) noexcept -> bool {

        return
            left.x == right.x &&
            left.y == right.y;
    }

    __C_ENG_NO_DISCARD constexpr auto equals (
            __C_ENG_TYPE ( MonitorWorkArea ) const & left,
            __C_ENG_TYPE ( MonitorWorkArea ) const & right
    ) noexcept -> bool {

        return
            equals ( left.position, right.position ) &&
            equals ( left.size, right.size );
    }

    __C_ENG_NO_DISCARD constexpr auto equals (
            __C_ENG_TYPE ( MonitorGammaRamp ) const & left,
            __C_ENG_TYPE ( MonitorGammaRamp ) const & right
    ) noexcept -> bool {

        return
            left.size == right.size &&
            std :: char_traits < cds :: uint16 > :: compare ( left.red, right.red, left.size ) == 0 &&
            std :: char_traits < cds :: uint16 > :: compare ( left.green, right.green, left.size ) == 0 &&
            std :: char_traits < cds :: uint16 > :: compare ( left.blue, right.blue, left.size ) == 0;
    }

    __C_ENG_NO_DISCARD constexpr auto equals (
            __C_ENG_TYPE ( MonitorProperties ) const & left,
            __C_ENG_TYPE ( MonitorProperties ) const & right
    ) noexcept -> bool {

        return
            left.name == right.name &&
            equals ( left.physicalSizeMM, right.physicalSizeMM ) &&
            equals ( left.contentScale, right.contentScale ) &&
            equals ( left.workArea, right.workArea ) &&
            equals ( left.gammaRamp, right.gammaRamp ) &&
            equals ( left.activeVideoMode, right.activeVideoMode );
    }

}

#endif //__C_ENG_CORE_HPP

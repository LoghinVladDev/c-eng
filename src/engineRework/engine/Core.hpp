//
// Created by loghin on 20.12.2021.
//

#ifndef __C_ENG_CORE_HPP
#define __C_ENG_CORE_HPP

#include <CDS/Types>

namespace engine {

#pragma push_macro("__C_ENG_OBJECT_NAME")
#pragma push_macro("__C_ENG_OBJECT_TYPE")

#undef  __C_ENG_OBJECT_NAME
#undef  __C_ENG_OBJECT_TYPE
#define __C_ENG_OBJECT_NAME EngineState /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_OBJECT_TYPE cds :: uint8 /* NOLINT(bugprone-reserved-identifier) */

    __C_ENG_ENUM {
        __C_ENG_ENUM_FIELD ( Inactive,                 0x00U ),
        __C_ENG_ENUM_FIELD ( Startup,                  0x01U ),
        __C_ENG_ENUM_FIELD ( StartupAcquiringSettings, 0x02U ),
        __C_ENG_ENUM_FIELD ( Running,                  0x03U ),
        __C_ENG_ENUM_FIELD ( Shutdown,                 0x04U )
    };

#pragma pop_macro("__C_ENG_OBJECT_TYPE")
#pragma pop_macro("__C_ENG_OBJECT_NAME")


#pragma push_macro("__C_ENG_OBJECT_NAME")
#pragma push_macro("__C_ENG_OBJECT_TYPE")

#undef  __C_ENG_OBJECT_NAME
#undef  __C_ENG_OBJECT_TYPE
#define __C_ENG_OBJECT_NAME LogLevel /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_OBJECT_TYPE cds :: uint8 /* NOLINT(bugprone-reserved-identifier) */

    __C_ENG_ENUM {
        __C_ENG_ENUM_FIELD ( Forced,    0x00 ),
        __C_ENG_ENUM_FIELD ( System,    0x01 ),
        __C_ENG_ENUM_FIELD ( Fatal,     0x02 ),
        __C_ENG_ENUM_FIELD ( Critical,  0x03 ),
        __C_ENG_ENUM_FIELD ( Error,     0x04 ),
        __C_ENG_ENUM_FIELD ( Warning,   0x05 ),
        __C_ENG_ENUM_FIELD ( Debug,     0x06 ),
        __C_ENG_ENUM_FIELD ( Info,      0x07 )
    };

#pragma pop_macro("__C_ENG_OBJECT_TYPE")
#pragma pop_macro("__C_ENG_OBJECT_NAME")


#pragma push_macro("__C_ENG_OBJECT_NAME")
#pragma push_macro("__C_ENG_OBJECT_TYPE")

#undef  __C_ENG_OBJECT_NAME
#undef  __C_ENG_OBJECT_TYPE
#define __C_ENG_OBJECT_NAME EventType /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_OBJECT_TYPE cds :: uint8 /* NOLINT(bugprone-reserved-identifier) */

    __C_ENG_ENUM {
        __C_ENG_ENUM_FIELD ( Custom,                        0x00 ),

        __C_ENG_ENUM_FIELD ( CustomKeyEvent,                0x01 ),
        __C_ENG_ENUM_FIELD ( KeyPressEvent,                 0x02 ),
        __C_ENG_ENUM_FIELD ( KeyReleaseEvent,               0x03 ),

        __C_ENG_ENUM_FIELD ( CustomMouseEvent,              0x04 ),
        __C_ENG_ENUM_FIELD ( MouseMoveEvent,                0x05 ),
        __C_ENG_ENUM_FIELD ( MouseEnterEvent,               0x06 ),
        __C_ENG_ENUM_FIELD ( MouseLeaveEvent,               0x07 ),
        __C_ENG_ENUM_FIELD ( MouseScrollEvent,              0x08 ),
        __C_ENG_ENUM_FIELD ( MousePressEvent,               0x09 ),
        __C_ENG_ENUM_FIELD ( MouseReleaseEvent,             0x0A ),

        __C_ENG_ENUM_FIELD ( CustomWindowEvent,             0x0B ),
        __C_ENG_ENUM_FIELD ( WindowResizeEvent,             0x0C ),
        __C_ENG_ENUM_FIELD ( WindowFrameBufferResizeEvent,  0x0D ),
        __C_ENG_ENUM_FIELD ( WindowCloseEvent,              0x0E ),
        __C_ENG_ENUM_FIELD ( WindowContentScaleEvent,       0x0F ),
        __C_ENG_ENUM_FIELD ( WindowMoveEvent,               0x10 ),
        __C_ENG_ENUM_FIELD ( WindowRestoreEvent,            0x11 ),
        __C_ENG_ENUM_FIELD ( WindowMinimizeEvent,           0x12 ),
        __C_ENG_ENUM_FIELD ( WindowMaximizeEvent,           0x13 ),
        __C_ENG_ENUM_FIELD ( WindowGainFocusEvent,          0x14 ),
        __C_ENG_ENUM_FIELD ( WindowLoseFocusEvent,          0x15 ),
        __C_ENG_ENUM_FIELD ( WindowRefreshRequestEvent,     0x16 ),

        __C_ENG_ENUM_FIELD ( CustomControllerEvent,         0x17 ),
        __C_ENG_ENUM_FIELD ( ControllerConnectEvent,        0x18 ),
        __C_ENG_ENUM_FIELD ( ControllerDisconnectEvent,     0x19 ),
        __C_ENG_ENUM_FIELD ( ControllerAxisEvent,           0x1A ),
        __C_ENG_ENUM_FIELD ( ControllerButtonPressEvent,    0x1B ),
        __C_ENG_ENUM_FIELD ( ControllerButtonReleaseEvent,  0x1C ),
        __C_ENG_ENUM_FIELD ( ControllerHatEvent,            0x1D )
    };

#pragma pop_macro("__C_ENG_OBJECT_TYPE")
#pragma pop_macro("__C_ENG_OBJECT_NAME")


#pragma push_macro("__C_ENG_OBJECT_NAME")
#pragma push_macro("__C_ENG_OBJECT_TYPE")

#undef  __C_ENG_OBJECT_NAME
#undef  __C_ENG_OBJECT_TYPE
#define __C_ENG_OBJECT_NAME KeyModifier /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_OBJECT_TYPE cds :: uint16 /* NOLINT(bugprone-reserved-identifier) */

    __C_ENG_ENUM {
        __C_ENG_ENUM_FIELD ( None,     0x0000 ),
        __C_ENG_ENUM_FIELD ( Shift,    GLFW_MOD_SHIFT ),
        __C_ENG_ENUM_FIELD ( Control,  GLFW_MOD_CONTROL ),
        __C_ENG_ENUM_FIELD ( Alt,      GLFW_MOD_ALT ),
        __C_ENG_ENUM_FIELD ( Super,    GLFW_MOD_SUPER ),
        __C_ENG_ENUM_FIELD ( CapsLock, GLFW_MOD_CAPS_LOCK ),
        __C_ENG_ENUM_FIELD ( NumLock,  GLFW_MOD_NUM_LOCK ),

        __C_ENG_ENUM_FIELD ( MaxValue, KeyModifierNumLock )
    };

#pragma pop_macro("__C_ENG_OBJECT_TYPE")
#pragma pop_macro("__C_ENG_OBJECT_NAME")


#pragma push_macro("__C_ENG_OBJECT_NAME")
#pragma push_macro("__C_ENG_OBJECT_TYPE")

#undef  __C_ENG_OBJECT_NAME
#undef  __C_ENG_OBJECT_TYPE
#define __C_ENG_OBJECT_NAME Key /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_OBJECT_TYPE cds :: sint16 /* NOLINT(bugprone-reserved-identifier) */

    __C_ENG_ENUM {
        __C_ENG_ENUM_FIELD ( Unknown,           GLFW_KEY_UNKNOWN ),
        __C_ENG_ENUM_FIELD ( Space,             GLFW_KEY_SPACE ),
        __C_ENG_ENUM_FIELD ( Apostrophe,        GLFW_KEY_APOSTROPHE ),
        __C_ENG_ENUM_FIELD ( Comma,             GLFW_KEY_COMMA ), /* , */
        __C_ENG_ENUM_FIELD ( Minus,             GLFW_KEY_MINUS ), /* - */
        __C_ENG_ENUM_FIELD ( Period,            GLFW_KEY_PERIOD ), /* . */
        __C_ENG_ENUM_FIELD ( Slash,             GLFW_KEY_SLASH ), /* / */
        __C_ENG_ENUM_FIELD ( 0,                 GLFW_KEY_0 ),
        __C_ENG_ENUM_FIELD ( 1,                 GLFW_KEY_1 ),
        __C_ENG_ENUM_FIELD ( 2,                 GLFW_KEY_2 ),
        __C_ENG_ENUM_FIELD ( 3,                 GLFW_KEY_3 ),
        __C_ENG_ENUM_FIELD ( 4,                 GLFW_KEY_4 ),
        __C_ENG_ENUM_FIELD ( 5,                 GLFW_KEY_5 ),
        __C_ENG_ENUM_FIELD ( 6,                 GLFW_KEY_6 ),
        __C_ENG_ENUM_FIELD ( 7,                 GLFW_KEY_7 ),
        __C_ENG_ENUM_FIELD ( 8,                 GLFW_KEY_8 ),
        __C_ENG_ENUM_FIELD ( 9,                 GLFW_KEY_9 ),
        __C_ENG_ENUM_FIELD ( Semicolon,         GLFW_KEY_SEMICOLON ), /* ; */
        __C_ENG_ENUM_FIELD ( Equal,             GLFW_KEY_EQUAL ), /* = */
        __C_ENG_ENUM_FIELD ( A,                 GLFW_KEY_A ),
        __C_ENG_ENUM_FIELD ( B,                 GLFW_KEY_B ),
        __C_ENG_ENUM_FIELD ( C,                 GLFW_KEY_C ),
        __C_ENG_ENUM_FIELD ( D,                 GLFW_KEY_D ),
        __C_ENG_ENUM_FIELD ( E,                 GLFW_KEY_E ),
        __C_ENG_ENUM_FIELD ( F,                 GLFW_KEY_F ),
        __C_ENG_ENUM_FIELD ( G,                 GLFW_KEY_G ),
        __C_ENG_ENUM_FIELD ( H,                 GLFW_KEY_H ),
        __C_ENG_ENUM_FIELD ( I,                 GLFW_KEY_I ),
        __C_ENG_ENUM_FIELD ( J,                 GLFW_KEY_J ),
        __C_ENG_ENUM_FIELD ( K,                 GLFW_KEY_K ),
        __C_ENG_ENUM_FIELD ( L,                 GLFW_KEY_L ),
        __C_ENG_ENUM_FIELD ( M,                 GLFW_KEY_M ),
        __C_ENG_ENUM_FIELD ( N,                 GLFW_KEY_N ),
        __C_ENG_ENUM_FIELD ( O,                 GLFW_KEY_O ),
        __C_ENG_ENUM_FIELD ( P,                 GLFW_KEY_P ),
        __C_ENG_ENUM_FIELD ( Q,                 GLFW_KEY_Q ),
        __C_ENG_ENUM_FIELD ( R,                 GLFW_KEY_R ),
        __C_ENG_ENUM_FIELD ( S,                 GLFW_KEY_S ),
        __C_ENG_ENUM_FIELD ( T,                 GLFW_KEY_T ),
        __C_ENG_ENUM_FIELD ( U,                 GLFW_KEY_U ),
        __C_ENG_ENUM_FIELD ( V,                 GLFW_KEY_V ),
        __C_ENG_ENUM_FIELD ( W,                 GLFW_KEY_W ),
        __C_ENG_ENUM_FIELD ( X,                 GLFW_KEY_X ),
        __C_ENG_ENUM_FIELD ( Y,                 GLFW_KEY_Y ),
        __C_ENG_ENUM_FIELD ( Z,                 GLFW_KEY_Z ),
        __C_ENG_ENUM_FIELD ( LeftBracket,       GLFW_KEY_LEFT_BRACKET ), /* [ */
        __C_ENG_ENUM_FIELD ( Backslash,         GLFW_KEY_BACKSLASH ), /* \ */
        __C_ENG_ENUM_FIELD ( RightBracket,      GLFW_KEY_RIGHT_BRACKET ), /* ] */
        __C_ENG_ENUM_FIELD ( GraveAccent,       GLFW_KEY_GRAVE_ACCENT ), /* ` */
        __C_ENG_ENUM_FIELD ( World1,            GLFW_KEY_WORLD_1 ), /* non-US #1 */
        __C_ENG_ENUM_FIELD ( World2,            GLFW_KEY_WORLD_2 ), /* non-US #2 */
        __C_ENG_ENUM_FIELD ( Escape,            GLFW_KEY_ESCAPE ),
        __C_ENG_ENUM_FIELD ( Enter,             GLFW_KEY_ENTER ),
        __C_ENG_ENUM_FIELD ( Tab,               GLFW_KEY_TAB ),
        __C_ENG_ENUM_FIELD ( Backspace,         GLFW_KEY_BACKSPACE ),
        __C_ENG_ENUM_FIELD ( Insert,            GLFW_KEY_INSERT ),
        __C_ENG_ENUM_FIELD ( Delete,            GLFW_KEY_DELETE ),
        __C_ENG_ENUM_FIELD ( Right,             GLFW_KEY_RIGHT ),
        __C_ENG_ENUM_FIELD ( Left,              GLFW_KEY_LEFT ),
        __C_ENG_ENUM_FIELD ( Down,              GLFW_KEY_DOWN ),
        __C_ENG_ENUM_FIELD ( Up,                GLFW_KEY_UP ),
        __C_ENG_ENUM_FIELD ( PageUp,            GLFW_KEY_PAGE_UP ),
        __C_ENG_ENUM_FIELD ( PageDown,          GLFW_KEY_PAGE_DOWN ),
        __C_ENG_ENUM_FIELD ( Home,              GLFW_KEY_HOME ),
        __C_ENG_ENUM_FIELD ( End,               GLFW_KEY_END ),
        __C_ENG_ENUM_FIELD ( CapsLock,          GLFW_KEY_CAPS_LOCK ),
        __C_ENG_ENUM_FIELD ( ScrollLock,        GLFW_KEY_SCROLL_LOCK ),
        __C_ENG_ENUM_FIELD ( NumLock,           GLFW_KEY_NUM_LOCK ),
        __C_ENG_ENUM_FIELD ( PrintScreen,       GLFW_KEY_PRINT_SCREEN ),
        __C_ENG_ENUM_FIELD ( Pause,             GLFW_KEY_PAUSE ),
        __C_ENG_ENUM_FIELD ( F1,                GLFW_KEY_F1 ),
        __C_ENG_ENUM_FIELD ( F2,                GLFW_KEY_F2 ),
        __C_ENG_ENUM_FIELD ( F3,                GLFW_KEY_F3 ),
        __C_ENG_ENUM_FIELD ( F4,                GLFW_KEY_F4 ),
        __C_ENG_ENUM_FIELD ( F5,                GLFW_KEY_F5 ),
        __C_ENG_ENUM_FIELD ( F6,                GLFW_KEY_F6 ),
        __C_ENG_ENUM_FIELD ( F7,                GLFW_KEY_F7 ),
        __C_ENG_ENUM_FIELD ( F8,                GLFW_KEY_F8 ),
        __C_ENG_ENUM_FIELD ( F9,                GLFW_KEY_F9 ),
        __C_ENG_ENUM_FIELD ( F10,               GLFW_KEY_F10 ),
        __C_ENG_ENUM_FIELD ( F11,               GLFW_KEY_F11 ),
        __C_ENG_ENUM_FIELD ( F12,               GLFW_KEY_F12 ),
        __C_ENG_ENUM_FIELD ( F13,               GLFW_KEY_F13 ),
        __C_ENG_ENUM_FIELD ( F14,               GLFW_KEY_F14 ),
        __C_ENG_ENUM_FIELD ( F15,               GLFW_KEY_F15 ),
        __C_ENG_ENUM_FIELD ( F16,               GLFW_KEY_F16 ),
        __C_ENG_ENUM_FIELD ( F17,               GLFW_KEY_F17 ),
        __C_ENG_ENUM_FIELD ( F18,               GLFW_KEY_F18 ),
        __C_ENG_ENUM_FIELD ( F19,               GLFW_KEY_F19 ),
        __C_ENG_ENUM_FIELD ( F20,               GLFW_KEY_F20 ),
        __C_ENG_ENUM_FIELD ( F21,               GLFW_KEY_F21 ),
        __C_ENG_ENUM_FIELD ( F22,               GLFW_KEY_F22 ),
        __C_ENG_ENUM_FIELD ( F23,               GLFW_KEY_F23 ),
        __C_ENG_ENUM_FIELD ( F24,               GLFW_KEY_F24 ),
        __C_ENG_ENUM_FIELD ( F25,               GLFW_KEY_F25 ),
        __C_ENG_ENUM_FIELD ( Keypad0,           GLFW_KEY_KP_0 ),
        __C_ENG_ENUM_FIELD ( Keypad1,           GLFW_KEY_KP_1 ),
        __C_ENG_ENUM_FIELD ( Keypad2,           GLFW_KEY_KP_2 ),
        __C_ENG_ENUM_FIELD ( Keypad3,           GLFW_KEY_KP_3 ),
        __C_ENG_ENUM_FIELD ( Keypad4,           GLFW_KEY_KP_4 ),
        __C_ENG_ENUM_FIELD ( Keypad5,           GLFW_KEY_KP_5 ),
        __C_ENG_ENUM_FIELD ( Keypad6,           GLFW_KEY_KP_6 ),
        __C_ENG_ENUM_FIELD ( Keypad7,           GLFW_KEY_KP_7 ),
        __C_ENG_ENUM_FIELD ( Keypad8,           GLFW_KEY_KP_8 ),
        __C_ENG_ENUM_FIELD ( Keypad9,           GLFW_KEY_KP_9 ),
        __C_ENG_ENUM_FIELD ( KeypadDecimal,     GLFW_KEY_KP_DECIMAL ),
        __C_ENG_ENUM_FIELD ( KeypadDivide,      GLFW_KEY_KP_DIVIDE ),
        __C_ENG_ENUM_FIELD ( KeypadMultiply,    GLFW_KEY_KP_MULTIPLY ),
        __C_ENG_ENUM_FIELD ( KeypadSubtract,    GLFW_KEY_KP_SUBTRACT ),
        __C_ENG_ENUM_FIELD ( KeypadAdd,         GLFW_KEY_KP_ADD ),
        __C_ENG_ENUM_FIELD ( KeypadEnter,       GLFW_KEY_KP_ENTER ),
        __C_ENG_ENUM_FIELD ( KeypadEqual,       GLFW_KEY_KP_EQUAL ),
        __C_ENG_ENUM_FIELD ( LeftShift,         GLFW_KEY_LEFT_SHIFT ),
        __C_ENG_ENUM_FIELD ( LeftControl,       GLFW_KEY_LEFT_CONTROL ),
        __C_ENG_ENUM_FIELD ( LeftAlt,           GLFW_KEY_LEFT_ALT ),
        __C_ENG_ENUM_FIELD ( LeftSuper,         GLFW_KEY_LEFT_SUPER ),
        __C_ENG_ENUM_FIELD ( RightShift,        GLFW_KEY_RIGHT_SHIFT ),
        __C_ENG_ENUM_FIELD ( RightControl,      GLFW_KEY_RIGHT_CONTROL ),
        __C_ENG_ENUM_FIELD ( RightAlt,          GLFW_KEY_RIGHT_ALT ),
        __C_ENG_ENUM_FIELD ( RightSuper,        GLFW_KEY_RIGHT_SUPER ),
        __C_ENG_ENUM_FIELD ( Menu,              GLFW_KEY_MENU )
    };

#pragma pop_macro("__C_ENG_OBJECT_TYPE")
#pragma pop_macro("__C_ENG_OBJECT_NAME")


#pragma push_macro("__C_ENG_OBJECT_NAME")
#pragma push_macro("__C_ENG_OBJECT_TYPE")

#undef  __C_ENG_OBJECT_NAME
#undef  __C_ENG_OBJECT_TYPE
#define __C_ENG_OBJECT_NAME MouseButton /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_OBJECT_TYPE cds :: sint16 /* NOLINT(bugprone-reserved-identifier) */

    __C_ENG_ENUM {
        __C_ENG_ENUM_FIELD ( 1,            GLFW_MOUSE_BUTTON_1 ),
        __C_ENG_ENUM_FIELD ( 2,            GLFW_MOUSE_BUTTON_2 ),
        __C_ENG_ENUM_FIELD ( 3,            GLFW_MOUSE_BUTTON_3 ),
        __C_ENG_ENUM_FIELD ( 4,            GLFW_MOUSE_BUTTON_4 ),
        __C_ENG_ENUM_FIELD ( 5,            GLFW_MOUSE_BUTTON_5 ),
        __C_ENG_ENUM_FIELD ( 6,            GLFW_MOUSE_BUTTON_6 ),
        __C_ENG_ENUM_FIELD ( 7,            GLFW_MOUSE_BUTTON_7 ),
        __C_ENG_ENUM_FIELD ( 8,            GLFW_MOUSE_BUTTON_8 ),

        __C_ENG_ENUM_FIELD ( Left,         MouseButton1 ),
        __C_ENG_ENUM_FIELD ( Right,        MouseButton2 ),
        __C_ENG_ENUM_FIELD ( Middle,       MouseButton3 ),

        __C_ENG_ENUM_FIELD ( Undefined,    0xffu )
    };

#pragma pop_macro("__C_ENG_OBJECT_TYPE")
#pragma pop_macro("__C_ENG_OBJECT_NAME")


#pragma push_macro("__C_ENG_OBJECT_NAME")
#pragma push_macro("__C_ENG_OBJECT_TYPE")

#undef  __C_ENG_OBJECT_NAME
#undef  __C_ENG_OBJECT_TYPE
#define __C_ENG_OBJECT_NAME WindowFlag /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_OBJECT_TYPE cds :: sint16 /* NOLINT(bugprone-reserved-identifier) */

    __C_ENG_ENUM {
        __C_ENG_ENUM_FIELD ( None,                      0x0000 ),
        __C_ENG_ENUM_FIELD ( Resizable,                 0x0001 ),
        __C_ENG_ENUM_FIELD ( Borderless,                0x0002 ),
        __C_ENG_ENUM_FIELD ( StartMinimized,            0x0004 ),
        __C_ENG_ENUM_FIELD ( GrabFocusOnOpen,           0x0008 ),
        __C_ENG_ENUM_FIELD ( RestorePreviousMode,       0x0010 ),
        __C_ENG_ENUM_FIELD ( StayOnTop,                 0x0020 ),
        __C_ENG_ENUM_FIELD ( StartMaximized,            0x0040 ),
        __C_ENG_ENUM_FIELD ( CenterCursorOnCreate,      0x0080 ),
        __C_ENG_ENUM_FIELD ( TransparentFramebuffer,    0x0100 ),
        __C_ENG_ENUM_FIELD ( GrabFocusOnRaise,          0x0200 ),
        __C_ENG_ENUM_FIELD ( ScaleToMonitor,            0x0400 ),

        __C_ENG_ENUM_FIELD ( MaxValue,                  WindowFlagScaleToMonitor )
    };

#pragma pop_macro("__C_ENG_OBJECT_TYPE")
#pragma pop_macro("__C_ENG_OBJECT_NAME")


#pragma push_macro("__C_ENG_OBJECT_NAME")
#pragma push_macro("__C_ENG_OBJECT_TYPE")

#undef  __C_ENG_OBJECT_NAME
#undef  __C_ENG_OBJECT_TYPE
#define __C_ENG_OBJECT_NAME WindowType /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_OBJECT_TYPE cds :: sint16 /* NOLINT(bugprone-reserved-identifier) */

    __C_ENG_ENUM {
        __C_ENG_ENUM_FIELD ( Windowed,              0x00 ),
        __C_ENG_ENUM_FIELD ( Fullscreen,            0x01 ),
        __C_ENG_ENUM_FIELD ( WindowedFullscreen,    0x02 )
    };

#pragma pop_macro("__C_ENG_OBJECT_TYPE")
#pragma pop_macro("__C_ENG_OBJECT_NAME")


#pragma push_macro("__C_ENG_OBJECT_NAME")
#pragma push_macro("__C_ENG_OBJECT_TYPE")

#undef  __C_ENG_OBJECT_NAME
#undef  __C_ENG_OBJECT_TYPE
#define __C_ENG_OBJECT_NAME ControllerHatState /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_OBJECT_TYPE cds :: sint16 /* NOLINT(bugprone-reserved-identifier) */

    __C_ENG_ENUM {
        __C_ENG_ENUM_FIELD ( Centered,  GLFW_HAT_CENTERED ),
        __C_ENG_ENUM_FIELD ( Up,        GLFW_HAT_UP ),
        __C_ENG_ENUM_FIELD ( Left,      GLFW_HAT_LEFT ),
        __C_ENG_ENUM_FIELD ( Right,     GLFW_HAT_RIGHT ),
        __C_ENG_ENUM_FIELD ( Down,      GLFW_HAT_DOWN ),
        __C_ENG_ENUM_FIELD ( LeftUp,    GLFW_HAT_LEFT_UP ),
        __C_ENG_ENUM_FIELD ( LeftDown,  GLFW_HAT_LEFT_DOWN ),
        __C_ENG_ENUM_FIELD ( RightUp,   GLFW_HAT_RIGHT_UP ),
        __C_ENG_ENUM_FIELD ( RightDown, GLFW_HAT_RIGHT_DOWN )
    };

#pragma pop_macro("__C_ENG_OBJECT_TYPE")
#pragma pop_macro("__C_ENG_OBJECT_NAME")


#pragma push_macro ("__C_ENG_OBJECT_NAME")

#undef __C_ENG_OBJECT_NAME
#define __C_ENG_OBJECT_NAME Position /* NOLINT(bugprone-reserved-identifier) */

    __C_ENG_STRUCT {
        cds :: uint32 x;
        cds :: uint32 y;
    };

#pragma pop_macro ("__C_ENG_OBJECT_NAME")


#pragma push_macro ("__C_ENG_OBJECT_NAME")

#undef __C_ENG_OBJECT_NAME
#define __C_ENG_OBJECT_NAME Size /* NOLINT(bugprone-reserved-identifier) */

    __C_ENG_STRUCT {
        cds :: uint32 width;
        cds :: uint32 height;
    };

#pragma pop_macro ("__C_ENG_OBJECT_NAME")


#pragma push_macro ("__C_ENG_OBJECT_NAME")

#undef __C_ENG_OBJECT_NAME
#define __C_ENG_OBJECT_NAME ColorChannelsDepth /* NOLINT(bugprone-reserved-identifier) */

    __C_ENG_STRUCT {
        cds :: uint32 red;
        cds :: uint32 green;
        cds :: uint32 blue;
    };

#pragma pop_macro ("__C_ENG_OBJECT_NAME")


#pragma push_macro ("__C_ENG_OBJECT_NAME")

#undef __C_ENG_OBJECT_NAME
#define __C_ENG_OBJECT_NAME MonitorVideoModeProperties /* NOLINT(bugprone-reserved-identifier) */

    __C_ENG_STRUCT {
        __C_ENG_TYPE ( Size )               size;
        __C_ENG_TYPE ( ColorChannelsDepth ) colorChannelsDepth;
        cds :: uint32                       refreshRate;
    };

#pragma pop_macro ("__C_ENG_OBJECT_NAME")


#pragma push_macro ("__C_ENG_OBJECT_NAME")

#undef __C_ENG_OBJECT_NAME
#define __C_ENG_OBJECT_NAME ContentScale /* NOLINT(bugprone-reserved-identifier) */

    __C_ENG_STRUCT {
        float x;
        float y;
    };

#pragma pop_macro ("__C_ENG_OBJECT_NAME")


#pragma push_macro ("__C_ENG_OBJECT_NAME")

#undef __C_ENG_OBJECT_NAME
#define __C_ENG_OBJECT_NAME MonitorWorkArea /* NOLINT(bugprone-reserved-identifier) */

    __C_ENG_STRUCT {
        __C_ENG_TYPE ( Position )   position;
        __C_ENG_TYPE ( Size )       size;
    };

#pragma pop_macro ("__C_ENG_OBJECT_NAME")


    __C_ENG_ALIAS ( MonitorName,            cds :: StringLiteral );
    __C_ENG_ALIAS ( MonitorGammaRampValue,  cds :: uint16 * );
    __C_ENG_ALIAS ( Flags,                  cds :: uint32 );
    __C_ENG_ALIAS ( KeyModifiers,           __C_ENG_TYPE ( Flags ) );
    __C_ENG_ALIAS ( MonitorContentScale,    __C_ENG_TYPE ( ContentScale ) );
    __C_ENG_ALIAS ( WindowContentScale,     __C_ENG_TYPE ( ContentScale ) );
    __C_ENG_ALIAS ( WindowFlags,            __C_ENG_TYPE ( Flags ) );



#pragma push_macro ("__C_ENG_OBJECT_NAME")

#undef __C_ENG_OBJECT_NAME
#define __C_ENG_OBJECT_NAME MonitorGammaRamp /* NOLINT(bugprone-reserved-identifier) */

    __C_ENG_STRUCT {
        cds :: uint32                           size;
        __C_ENG_TYPE ( MonitorGammaRampValue )  red;
        __C_ENG_TYPE ( MonitorGammaRampValue )  green;
        __C_ENG_TYPE ( MonitorGammaRampValue )  blue;
    };

#pragma pop_macro ("__C_ENG_OBJECT_NAME")


#pragma push_macro ("__C_ENG_OBJECT_NAME")

#undef __C_ENG_OBJECT_NAME
#define __C_ENG_OBJECT_NAME MonitorProperties /* NOLINT(bugprone-reserved-identifier) */

    __C_ENG_STRUCT {
        __C_ENG_TYPE ( MonitorName )                name;
        __C_ENG_TYPE ( Size )                       physicalSizeMM;
        __C_ENG_TYPE ( MonitorContentScale )        contentScale;
        __C_ENG_TYPE ( MonitorWorkArea )            workArea;
        __C_ENG_TYPE ( MonitorGammaRamp )           gammaRamp;
        __C_ENG_TYPE ( MonitorVideoModeProperties ) activeVideoMode;
    };

#pragma pop_macro ("__C_ENG_OBJECT_NAME")


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

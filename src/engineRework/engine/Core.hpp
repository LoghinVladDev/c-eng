//
// Created by loghin on 20.12.2021.
//

#ifndef __C_ENG_CORE_HPP
#define __C_ENG_CORE_HPP

#include <CDS/Types>

namespace engine {


#define C_ENG_MAP_START     ENUM ( EngineState, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

    Enum {
        Field ( Inactive,                 0x00 ),
        Field ( Startup,                  0x01 ),
        Field ( StartupAcquiringSettings, 0x02 ),
        Field ( Running,                  0x03 ),
        Field ( Shutdown,                 0x04 )
    };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
    

#define C_ENG_MAP_START     ENUM ( LogLevel, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

    Enum {
        Field ( Forced,    0x00 ),
        Field ( System,    0x01 ),
        Field ( Fatal,     0x02 ),
        Field ( Critical,  0x03 ),
        Field ( Error,     0x04 ),
        Field ( Warning,   0x05 ),
        Field ( Debug,     0x06 ),
        Field ( Info,      0x07 )
    };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     ENUM ( EventType, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

    Enum {
        Field ( Custom,                        0x00 ),

        Field ( CustomKeyEvent,                0x01 ),
        Field ( KeyPressEvent,                 0x02 ),
        Field ( KeyReleaseEvent,               0x03 ),

        Field ( CustomMouseEvent,              0x04 ),
        Field ( MouseMoveEvent,                0x05 ),
        Field ( MouseEnterEvent,               0x06 ),
        Field ( MouseLeaveEvent,               0x07 ),
        Field ( MouseScrollEvent,              0x08 ),
        Field ( MousePressEvent,               0x09 ),
        Field ( MouseReleaseEvent,             0x0A ),

        Field ( CustomWindowEvent,             0x0B ),
        Field ( WindowResizeEvent,             0x0C ),
        Field ( WindowFrameBufferResizeEvent,  0x0D ),
        Field ( WindowCloseEvent,              0x0E ),
        Field ( WindowContentScaleEvent,       0x0F ),
        Field ( WindowMoveEvent,               0x10 ),
        Field ( WindowRestoreEvent,            0x11 ),
        Field ( WindowMinimizeEvent,           0x12 ),
        Field ( WindowMaximizeEvent,           0x13 ),
        Field ( WindowGainFocusEvent,          0x14 ),
        Field ( WindowLoseFocusEvent,          0x15 ),
        Field ( WindowRefreshRequestEvent,     0x16 ),

        Field ( CustomControllerEvent,         0x17 ),
        Field ( ControllerConnectEvent,        0x18 ),
        Field ( ControllerDisconnectEvent,     0x19 ),
        Field ( ControllerAxisEvent,           0x1A ),
        Field ( ControllerButtonPressEvent,    0x1B ),
        Field ( ControllerButtonReleaseEvent,  0x1C ),
        Field ( ControllerHatEvent,            0x1D )
    };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     ENUM ( KeyModifier, TYPE ( cds :: uint16 ) )
#include <ObjectMapping.hpp>

    Enum {
        Field ( None,     0x0000 ),
        Field ( Shift,    GLFW_MOD_SHIFT ),
        Field ( Control,  GLFW_MOD_CONTROL ),
        Field ( Alt,      GLFW_MOD_ALT ),
        Field ( Super,    GLFW_MOD_SUPER ),
        Field ( CapsLock, GLFW_MOD_CAPS_LOCK ),
        Field ( NumLock,  GLFW_MOD_NUM_LOCK ),

        Field ( MaxValue, KeyModifierNumLock )
    };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     ENUM ( Key, TYPE ( cds :: sint16 ) )
#include <ObjectMapping.hpp>

    Enum {
        Field ( Unknown,           GLFW_KEY_UNKNOWN ),
        Field ( Space,             GLFW_KEY_SPACE ),
        Field ( Apostrophe,        GLFW_KEY_APOSTROPHE ),
        Field ( Comma,             GLFW_KEY_COMMA ), /* , */
        Field ( Minus,             GLFW_KEY_MINUS ), /* - */
        Field ( Period,            GLFW_KEY_PERIOD ), /* . */
        Field ( Slash,             GLFW_KEY_SLASH ), /* / */
        Field ( 0,                 GLFW_KEY_0 ),
        Field ( 1,                 GLFW_KEY_1 ),
        Field ( 2,                 GLFW_KEY_2 ),
        Field ( 3,                 GLFW_KEY_3 ),
        Field ( 4,                 GLFW_KEY_4 ),
        Field ( 5,                 GLFW_KEY_5 ),
        Field ( 6,                 GLFW_KEY_6 ),
        Field ( 7,                 GLFW_KEY_7 ),
        Field ( 8,                 GLFW_KEY_8 ),
        Field ( 9,                 GLFW_KEY_9 ),
        Field ( Semicolon,         GLFW_KEY_SEMICOLON ), /* ; */
        Field ( Equal,             GLFW_KEY_EQUAL ), /* = */
        Field ( A,                 GLFW_KEY_A ),
        Field ( B,                 GLFW_KEY_B ),
        Field ( C,                 GLFW_KEY_C ),
        Field ( D,                 GLFW_KEY_D ),
        Field ( E,                 GLFW_KEY_E ),
        Field ( F,                 GLFW_KEY_F ),
        Field ( G,                 GLFW_KEY_G ),
        Field ( H,                 GLFW_KEY_H ),
        Field ( I,                 GLFW_KEY_I ),
        Field ( J,                 GLFW_KEY_J ),
        Field ( K,                 GLFW_KEY_K ),
        Field ( L,                 GLFW_KEY_L ),
        Field ( M,                 GLFW_KEY_M ),
        Field ( N,                 GLFW_KEY_N ),
        Field ( O,                 GLFW_KEY_O ),
        Field ( P,                 GLFW_KEY_P ),
        Field ( Q,                 GLFW_KEY_Q ),
        Field ( R,                 GLFW_KEY_R ),
        Field ( S,                 GLFW_KEY_S ),
        Field ( T,                 GLFW_KEY_T ),
        Field ( U,                 GLFW_KEY_U ),
        Field ( V,                 GLFW_KEY_V ),
        Field ( W,                 GLFW_KEY_W ),
        Field ( X,                 GLFW_KEY_X ),
        Field ( Y,                 GLFW_KEY_Y ),
        Field ( Z,                 GLFW_KEY_Z ),
        Field ( LeftBracket,       GLFW_KEY_LEFT_BRACKET ), /* [ */
        Field ( Backslash,         GLFW_KEY_BACKSLASH ), /* \ */
        Field ( RightBracket,      GLFW_KEY_RIGHT_BRACKET ), /* ] */
        Field ( GraveAccent,       GLFW_KEY_GRAVE_ACCENT ), /* ` */
        Field ( World1,            GLFW_KEY_WORLD_1 ), /* non-US #1 */
        Field ( World2,            GLFW_KEY_WORLD_2 ), /* non-US #2 */
        Field ( Escape,            GLFW_KEY_ESCAPE ),
        Field ( Enter,             GLFW_KEY_ENTER ),
        Field ( Tab,               GLFW_KEY_TAB ),
        Field ( Backspace,         GLFW_KEY_BACKSPACE ),
        Field ( Insert,            GLFW_KEY_INSERT ),
        Field ( Delete,            GLFW_KEY_DELETE ),
        Field ( Right,             GLFW_KEY_RIGHT ),
        Field ( Left,              GLFW_KEY_LEFT ),
        Field ( Down,              GLFW_KEY_DOWN ),
        Field ( Up,                GLFW_KEY_UP ),
        Field ( PageUp,            GLFW_KEY_PAGE_UP ),
        Field ( PageDown,          GLFW_KEY_PAGE_DOWN ),
        Field ( Home,              GLFW_KEY_HOME ),
        Field ( End,               GLFW_KEY_END ),
        Field ( CapsLock,          GLFW_KEY_CAPS_LOCK ),
        Field ( ScrollLock,        GLFW_KEY_SCROLL_LOCK ),
        Field ( NumLock,           GLFW_KEY_NUM_LOCK ),
        Field ( PrintScreen,       GLFW_KEY_PRINT_SCREEN ),
        Field ( Pause,             GLFW_KEY_PAUSE ),
        Field ( F1,                GLFW_KEY_F1 ),
        Field ( F2,                GLFW_KEY_F2 ),
        Field ( F3,                GLFW_KEY_F3 ),
        Field ( F4,                GLFW_KEY_F4 ),
        Field ( F5,                GLFW_KEY_F5 ),
        Field ( F6,                GLFW_KEY_F6 ),
        Field ( F7,                GLFW_KEY_F7 ),
        Field ( F8,                GLFW_KEY_F8 ),
        Field ( F9,                GLFW_KEY_F9 ),
        Field ( F10,               GLFW_KEY_F10 ),
        Field ( F11,               GLFW_KEY_F11 ),
        Field ( F12,               GLFW_KEY_F12 ),
        Field ( F13,               GLFW_KEY_F13 ),
        Field ( F14,               GLFW_KEY_F14 ),
        Field ( F15,               GLFW_KEY_F15 ),
        Field ( F16,               GLFW_KEY_F16 ),
        Field ( F17,               GLFW_KEY_F17 ),
        Field ( F18,               GLFW_KEY_F18 ),
        Field ( F19,               GLFW_KEY_F19 ),
        Field ( F20,               GLFW_KEY_F20 ),
        Field ( F21,               GLFW_KEY_F21 ),
        Field ( F22,               GLFW_KEY_F22 ),
        Field ( F23,               GLFW_KEY_F23 ),
        Field ( F24,               GLFW_KEY_F24 ),
        Field ( F25,               GLFW_KEY_F25 ),
        Field ( Keypad0,           GLFW_KEY_KP_0 ),
        Field ( Keypad1,           GLFW_KEY_KP_1 ),
        Field ( Keypad2,           GLFW_KEY_KP_2 ),
        Field ( Keypad3,           GLFW_KEY_KP_3 ),
        Field ( Keypad4,           GLFW_KEY_KP_4 ),
        Field ( Keypad5,           GLFW_KEY_KP_5 ),
        Field ( Keypad6,           GLFW_KEY_KP_6 ),
        Field ( Keypad7,           GLFW_KEY_KP_7 ),
        Field ( Keypad8,           GLFW_KEY_KP_8 ),
        Field ( Keypad9,           GLFW_KEY_KP_9 ),
        Field ( KeypadDecimal,     GLFW_KEY_KP_DECIMAL ),
        Field ( KeypadDivide,      GLFW_KEY_KP_DIVIDE ),
        Field ( KeypadMultiply,    GLFW_KEY_KP_MULTIPLY ),
        Field ( KeypadSubtract,    GLFW_KEY_KP_SUBTRACT ),
        Field ( KeypadAdd,         GLFW_KEY_KP_ADD ),
        Field ( KeypadEnter,       GLFW_KEY_KP_ENTER ),
        Field ( KeypadEqual,       GLFW_KEY_KP_EQUAL ),
        Field ( LeftShift,         GLFW_KEY_LEFT_SHIFT ),
        Field ( LeftControl,       GLFW_KEY_LEFT_CONTROL ),
        Field ( LeftAlt,           GLFW_KEY_LEFT_ALT ),
        Field ( LeftSuper,         GLFW_KEY_LEFT_SUPER ),
        Field ( RightShift,        GLFW_KEY_RIGHT_SHIFT ),
        Field ( RightControl,      GLFW_KEY_RIGHT_CONTROL ),
        Field ( RightAlt,          GLFW_KEY_RIGHT_ALT ),
        Field ( RightSuper,        GLFW_KEY_RIGHT_SUPER ),
        Field ( Menu,              GLFW_KEY_MENU )
    };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     ENUM ( MouseButton, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

    Enum {
        Field ( 1,            GLFW_MOUSE_BUTTON_1 ),
        Field ( 2,            GLFW_MOUSE_BUTTON_2 ),
        Field ( 3,            GLFW_MOUSE_BUTTON_3 ),
        Field ( 4,            GLFW_MOUSE_BUTTON_4 ),
        Field ( 5,            GLFW_MOUSE_BUTTON_5 ),
        Field ( 6,            GLFW_MOUSE_BUTTON_6 ),
        Field ( 7,            GLFW_MOUSE_BUTTON_7 ),
        Field ( 8,            GLFW_MOUSE_BUTTON_8 ),

        Field ( Left,         MouseButton1 ),
        Field ( Right,        MouseButton2 ),
        Field ( Middle,       MouseButton3 ),

        Field ( Undefined,    0xffu )
    };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     ENUM ( WindowFlag, TYPE ( cds :: uint16 ) )
#include <ObjectMapping.hpp>

    Enum {
        Field ( None,                      0x0000 ),
        Field ( Resizable,                 0x0001 ),
        Field ( Borderless,                0x0002 ),
        Field ( StartMinimized,            0x0004 ),
        Field ( GrabFocusOnOpen,           0x0008 ),
        Field ( RestorePreviousMode,       0x0010 ),
        Field ( StayOnTop,                 0x0020 ),
        Field ( StartMaximized,            0x0040 ),
        Field ( CenterCursorOnCreate,      0x0080 ),
        Field ( TransparentFramebuffer,    0x0100 ),
        Field ( GrabFocusOnRaise,          0x0200 ),
        Field ( ScaleToMonitor,            0x0400 ),

        Field ( MaxValue,                  WindowFlagScaleToMonitor )
    };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     ENUM ( WindowType, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

    Enum {
        Field ( Windowed,              0x00 ),
        Field ( Fullscreen,            0x01 ),
        Field ( WindowedFullscreen,    0x02 )
    };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     ENUM ( ControllerHatState, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

    Enum {
        Field ( Centered,  GLFW_HAT_CENTERED ),
        Field ( Up,        GLFW_HAT_UP ),
        Field ( Left,      GLFW_HAT_LEFT ),
        Field ( Right,     GLFW_HAT_RIGHT ),
        Field ( Down,      GLFW_HAT_DOWN ),
        Field ( LeftUp,    GLFW_HAT_LEFT_UP ),
        Field ( LeftDown,  GLFW_HAT_LEFT_DOWN ),
        Field ( RightUp,   GLFW_HAT_RIGHT_UP ),
        Field ( RightDown, GLFW_HAT_RIGHT_DOWN )
    };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     ENUM ( CompareResult,   TYPE ( cds :: sint8 ) )
#include <ObjectMapping.hpp>

    Enum {
        Field ( Less,       -1 ),
        Field ( Equals,     0 ),
        Field ( Greater,    1 )
    };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>



#define C_ENG_MAP_START     STRUCT ( Position, NO_PARENT )
#include <ObjectMapping.hpp>

    Struct {
        cds :: uint32 x;
        cds :: uint32 y;
    };
    
#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( Size, NO_PARENT )
#include <ObjectMapping.hpp>

    Struct {
        cds :: uint32 width;
        cds :: uint32 height;
    };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( ColorChannelsDepth, NO_PARENT )
#include <ObjectMapping.hpp>

    Struct {
        cds :: uint32 red;
        cds :: uint32 green;
        cds :: uint32 blue;
    };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( MonitorVideoModeProperties, NO_PARENT )
#include <ObjectMapping.hpp>

    Struct {
        __C_ENG_TYPE ( Size )               size;
        __C_ENG_TYPE ( ColorChannelsDepth ) colorChannelsDepth;
        cds :: uint32                       refreshRate;
    };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( ContentScale, NO_PARENT )
#include <ObjectMapping.hpp>

    Struct {
        float x;
        float y;
    };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( MonitorWorkArea, NO_PARENT )
#include <ObjectMapping.hpp>

    Struct {
        __C_ENG_TYPE ( Position )   position;
        __C_ENG_TYPE ( Size )       size;
    };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


    __C_ENG_ALIAS ( MonitorName,            cds :: StringLiteral );
    __C_ENG_ALIAS ( MonitorGammaRampValue,  cds :: uint16 * );
    __C_ENG_ALIAS ( Flags,                  cds :: uint32 );
    __C_ENG_ALIAS ( KeyModifiers,           __C_ENG_TYPE ( Flags ) );
    __C_ENG_ALIAS ( MonitorContentScale,    __C_ENG_TYPE ( ContentScale ) );
    __C_ENG_ALIAS ( WindowContentScale,     __C_ENG_TYPE ( ContentScale ) );
    __C_ENG_ALIAS ( WindowFlags,            __C_ENG_TYPE ( Flags ) );


#define C_ENG_MAP_START     STRUCT ( MonitorGammaRamp, NO_PARENT )
#include <ObjectMapping.hpp>

    Struct {
        cds :: uint32                           size;
        __C_ENG_TYPE ( MonitorGammaRampValue )  red;
        __C_ENG_TYPE ( MonitorGammaRampValue )  green;
        __C_ENG_TYPE ( MonitorGammaRampValue )  blue;
    };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( MonitorProperties, NO_PARENT )
#include <ObjectMapping.hpp>

    Struct {
        __C_ENG_TYPE ( MonitorName )                name;
        __C_ENG_TYPE ( Size )                       physicalSizeMM;
        __C_ENG_TYPE ( MonitorContentScale )        contentScale;
        __C_ENG_TYPE ( MonitorWorkArea )            workArea;
        __C_ENG_TYPE ( MonitorGammaRamp )           gammaRamp;
        __C_ENG_TYPE ( MonitorVideoModeProperties ) activeVideoMode;
    };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


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
    __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( CompareResult ) ) noexcept -> cds :: StringLiteral;

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

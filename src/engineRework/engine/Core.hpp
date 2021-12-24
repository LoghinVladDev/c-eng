//
// Created by loghin on 20.12.2021.
//

#ifndef C_ENG_CORE_HPP
#define C_ENG_CORE_HPP

#include <CDS/Types>

namespace engine {

    enum EngineState : cds :: uint8 {
        EngineStateInactive                 = 0x00U,
        EngineStateStartup                  = 0x01U,
        EngineStateStartupAcquiringSettings = 0x02U,
        EngineStateRunning                  = 0x03U,
        EngineStateShutdown                 = 0x04U
    };

    enum LogLevel : cds :: uint8 {
        LogLevelForced      = 0x00U,
        LogLevelSystem      = 0x01U,
        LogLevelFatal       = 0x02U,
        LogLevelCritical    = 0x03U,
        LogLevelError       = 0x04U,
        LogLevelWarning     = 0x05U,
        LogLevelDebug       = 0x06U,
        LogLevelInfo        = 0x07U
    };

    enum EventType : cds :: uint8 {
        EventTypeCustom                         = 0x00U,

        EventTypeCustomKeyEvent                 = 0x01U,
        EventTypeKeyPressEvent                  = 0x02U,
        EventTypeKeyReleaseEvent                = 0x03U,

        EventTypeCustomMouseEvent               = 0x04U,
        EventTypeMouseMoveEvent                 = 0x05U,
        EventTypeMouseEnterEvent                = 0x06U,
        EventTypeMouseLeaveEvent                = 0x07U,
        EventTypeMouseScrollEvent               = 0x08U,
        EventTypeMousePressEvent                = 0x09U,
        EventTypeMouseReleaseEvent              = 0x0aU,

        EventTypeCustomWindowEvent              = 0x0bU,
        EventTypeWindowResizeEvent              = 0x0cU,
        EventTypeWindowFrameBufferResizeEvent   = 0x0dU,
        EventTypeWindowCloseEvent               = 0x0eU,
        EventTypeWindowContentScaleEvent        = 0x0fU,
        EventTypeWindowMoveEvent                = 0x10U,
        EventTypeWindowRestoreEvent             = 0x11U,
        EventTypeWindowMinimizeEvent            = 0x12U,
        EventTypeWindowMaximizeEvent            = 0x13U,
        EventTypeWindowGainFocusEvent           = 0x14U,
        EventTypeWindowLoseFocusEvent           = 0x15U,
        EventTypeWindowRefreshRequestEvent      = 0x16U,

        EventTypeCustomControllerEvent          = 0x17U,
        EventTypeControllerConnectEvent         = 0x18U,
        EventTypeControllerDisconnectEvent      = 0x19U,
        EventTypeControllerAxisEvent            = 0x1aU,
        EventTypeControllerButtonPressEvent     = 0x1bU,
        EventTypeControllerButtonReleaseEvent   = 0x1cU,
        EventTypeControllerHatEvent             = 0x1dU
    };

    enum KeyModifier : cds :: uint16 {
        KeyModifierNone     = 0x0000U,
        KeyModifierShift    = static_cast < cds :: uint16 > ( GLFW_MOD_SHIFT ),
        KeyModifierControl  = static_cast < cds :: uint16 > ( GLFW_MOD_CONTROL ),
        KeyModifierAlt      = static_cast < cds :: uint16 > ( GLFW_MOD_ALT ),
        KeyModifierSuper    = static_cast < cds :: uint16 > ( GLFW_MOD_SUPER ),
        KeyModifierCapsLock = static_cast < cds :: uint16 > ( GLFW_MOD_CAPS_LOCK ),
        KeyModifierNumLock  = static_cast < cds :: uint16 > ( GLFW_MOD_NUM_LOCK ),

        KeyModifierMaxValue = KeyModifierNumLock
    };

    enum Key : cds :: sint16 {
        KeyUnknown              = static_cast < cds :: sint16 > ( GLFW_KEY_UNKNOWN ),
        KeySpace                = static_cast < cds :: sint16 > ( GLFW_KEY_SPACE ),
        KeyApostrophe           = static_cast < cds :: sint16 > ( GLFW_KEY_APOSTROPHE ),
        KeyComma                = static_cast < cds :: sint16 > ( GLFW_KEY_COMMA ), /* , */
        KeyMinus                = static_cast < cds :: sint16 > ( GLFW_KEY_MINUS ), /* - */
        KeyPeriod               = static_cast < cds :: sint16 > ( GLFW_KEY_PERIOD ), /* . */
        KeySlash                = static_cast < cds :: sint16 > ( GLFW_KEY_SLASH ), /* / */
        Key0                    = static_cast < cds :: sint16 > ( GLFW_KEY_0 ),
        Key1                    = static_cast < cds :: sint16 > ( GLFW_KEY_1 ),
        Key2                    = static_cast < cds :: sint16 > ( GLFW_KEY_2 ),
        Key3                    = static_cast < cds :: sint16 > ( GLFW_KEY_3 ),
        Key4                    = static_cast < cds :: sint16 > ( GLFW_KEY_4 ),
        Key5                    = static_cast < cds :: sint16 > ( GLFW_KEY_5 ),
        Key6                    = static_cast < cds :: sint16 > ( GLFW_KEY_6 ),
        Key7                    = static_cast < cds :: sint16 > ( GLFW_KEY_7 ),
        Key8                    = static_cast < cds :: sint16 > ( GLFW_KEY_8 ),
        Key9                    = static_cast < cds :: sint16 > ( GLFW_KEY_9 ),
        KeySemicolon            = static_cast < cds :: sint16 > ( GLFW_KEY_SEMICOLON ), /* ; */
        KeyEqual                = static_cast < cds :: sint16 > ( GLFW_KEY_EQUAL ), /* = */
        KeyA                    = static_cast < cds :: sint16 > ( GLFW_KEY_A ),
        KeyB                    = static_cast < cds :: sint16 > ( GLFW_KEY_B ),
        KeyC                    = static_cast < cds :: sint16 > ( GLFW_KEY_C ),
        KeyD                    = static_cast < cds :: sint16 > ( GLFW_KEY_D ),
        KeyE                    = static_cast < cds :: sint16 > ( GLFW_KEY_E ),
        KeyF                    = static_cast < cds :: sint16 > ( GLFW_KEY_F ),
        KeyG                    = static_cast < cds :: sint16 > ( GLFW_KEY_G ),
        KeyH                    = static_cast < cds :: sint16 > ( GLFW_KEY_H ),
        KeyI                    = static_cast < cds :: sint16 > ( GLFW_KEY_I ),
        KeyJ                    = static_cast < cds :: sint16 > ( GLFW_KEY_J ),
        KeyK                    = static_cast < cds :: sint16 > ( GLFW_KEY_K ),
        KeyL                    = static_cast < cds :: sint16 > ( GLFW_KEY_L ),
        KeyM                    = static_cast < cds :: sint16 > ( GLFW_KEY_M ),
        KeyN                    = static_cast < cds :: sint16 > ( GLFW_KEY_N ),
        KeyO                    = static_cast < cds :: sint16 > ( GLFW_KEY_O ),
        KeyP                    = static_cast < cds :: sint16 > ( GLFW_KEY_P ),
        KeyQ                    = static_cast < cds :: sint16 > ( GLFW_KEY_Q ),
        KeyR                    = static_cast < cds :: sint16 > ( GLFW_KEY_R ),
        KeyS                    = static_cast < cds :: sint16 > ( GLFW_KEY_S ),
        KeyT                    = static_cast < cds :: sint16 > ( GLFW_KEY_T ),
        KeyU                    = static_cast < cds :: sint16 > ( GLFW_KEY_U ),
        KeyV                    = static_cast < cds :: sint16 > ( GLFW_KEY_V ),
        KeyW                    = static_cast < cds :: sint16 > ( GLFW_KEY_W ),
        KeyX                    = static_cast < cds :: sint16 > ( GLFW_KEY_X ),
        KeyY                    = static_cast < cds :: sint16 > ( GLFW_KEY_Y ),
        KeyZ                    = static_cast < cds :: sint16 > ( GLFW_KEY_Z ),
        KeyLeftBracket          = static_cast < cds :: sint16 > ( GLFW_KEY_LEFT_BRACKET ), /* [ */
        KeyBackslash            = static_cast < cds :: sint16 > ( GLFW_KEY_BACKSLASH ), /* \ */
        KeyRightBracket         = static_cast < cds :: sint16 > ( GLFW_KEY_RIGHT_BRACKET ), /* ] */
        KeyGraveAccent          = static_cast < cds :: sint16 > ( GLFW_KEY_GRAVE_ACCENT ), /* ` */
        KeyWorld1               = static_cast < cds :: sint16 > ( GLFW_KEY_WORLD_1 ), /* non-US #1 */
        KeyWorld2               = static_cast < cds :: sint16 > ( GLFW_KEY_WORLD_2 ), /* non-US #2 */
        KeyEscape               = static_cast < cds :: sint16 > ( GLFW_KEY_ESCAPE ),
        KeyEnter                = static_cast < cds :: sint16 > ( GLFW_KEY_ENTER ),
        KeyTab                  = static_cast < cds :: sint16 > ( GLFW_KEY_TAB ),
        KeyBackspace            = static_cast < cds :: sint16 > ( GLFW_KEY_BACKSPACE ),
        KeyInsert               = static_cast < cds :: sint16 > ( GLFW_KEY_INSERT ),
        KeyDelete               = static_cast < cds :: sint16 > ( GLFW_KEY_DELETE ),
        KeyRight                = static_cast < cds :: sint16 > ( GLFW_KEY_RIGHT ),
        KeyLeft                 = static_cast < cds :: sint16 > ( GLFW_KEY_LEFT ),
        KeyDown                 = static_cast < cds :: sint16 > ( GLFW_KEY_DOWN ),
        KeyUp                   = static_cast < cds :: sint16 > ( GLFW_KEY_UP ),
        KeyPageUp               = static_cast < cds :: sint16 > ( GLFW_KEY_PAGE_UP ),
        KeyPageDown             = static_cast < cds :: sint16 > ( GLFW_KEY_PAGE_DOWN ),
        KeyHome                 = static_cast < cds :: sint16 > ( GLFW_KEY_HOME ),
        KeyEnd                  = static_cast < cds :: sint16 > ( GLFW_KEY_END ),
        KeyCapsLock             = static_cast < cds :: sint16 > ( GLFW_KEY_CAPS_LOCK ),
        KeyScrollLock           = static_cast < cds :: sint16 > ( GLFW_KEY_SCROLL_LOCK ),
        KeyNumLock              = static_cast < cds :: sint16 > ( GLFW_KEY_NUM_LOCK ),
        KeyPrintScreen          = static_cast < cds :: sint16 > ( GLFW_KEY_PRINT_SCREEN ),
        KeyPause                = static_cast < cds :: sint16 > ( GLFW_KEY_PAUSE ),
        KeyF1                   = static_cast < cds :: sint16 > ( GLFW_KEY_F1 ),
        KeyF2                   = static_cast < cds :: sint16 > ( GLFW_KEY_F2 ),
        KeyF3                   = static_cast < cds :: sint16 > ( GLFW_KEY_F3 ),
        KeyF4                   = static_cast < cds :: sint16 > ( GLFW_KEY_F4 ),
        KeyF5                   = static_cast < cds :: sint16 > ( GLFW_KEY_F5 ),
        KeyF6                   = static_cast < cds :: sint16 > ( GLFW_KEY_F6 ),
        KeyF7                   = static_cast < cds :: sint16 > ( GLFW_KEY_F7 ),
        KeyF8                   = static_cast < cds :: sint16 > ( GLFW_KEY_F8 ),
        KeyF9                   = static_cast < cds :: sint16 > ( GLFW_KEY_F9 ),
        KeyF10                  = static_cast < cds :: sint16 > ( GLFW_KEY_F10 ),
        KeyF11                  = static_cast < cds :: sint16 > ( GLFW_KEY_F11 ),
        KeyF12                  = static_cast < cds :: sint16 > ( GLFW_KEY_F12 ),
        KeyF13                  = static_cast < cds :: sint16 > ( GLFW_KEY_F13 ),
        KeyF14                  = static_cast < cds :: sint16 > ( GLFW_KEY_F14 ),
        KeyF15                  = static_cast < cds :: sint16 > ( GLFW_KEY_F15 ),
        KeyF16                  = static_cast < cds :: sint16 > ( GLFW_KEY_F16 ),
        KeyF17                  = static_cast < cds :: sint16 > ( GLFW_KEY_F17 ),
        KeyF18                  = static_cast < cds :: sint16 > ( GLFW_KEY_F18 ),
        KeyF19                  = static_cast < cds :: sint16 > ( GLFW_KEY_F19 ),
        KeyF20                  = static_cast < cds :: sint16 > ( GLFW_KEY_F20 ),
        KeyF21                  = static_cast < cds :: sint16 > ( GLFW_KEY_F21 ),
        KeyF22                  = static_cast < cds :: sint16 > ( GLFW_KEY_F22 ),
        KeyF23                  = static_cast < cds :: sint16 > ( GLFW_KEY_F23 ),
        KeyF24                  = static_cast < cds :: sint16 > ( GLFW_KEY_F24 ),
        KeyF25                  = static_cast < cds :: sint16 > ( GLFW_KEY_F25 ),
        KeyKeypad0              = static_cast < cds :: sint16 > ( GLFW_KEY_KP_0 ),
        KeyKeypad1              = static_cast < cds :: sint16 > ( GLFW_KEY_KP_1 ),
        KeyKeypad2              = static_cast < cds :: sint16 > ( GLFW_KEY_KP_2 ),
        KeyKeypad3              = static_cast < cds :: sint16 > ( GLFW_KEY_KP_3 ),
        KeyKeypad4              = static_cast < cds :: sint16 > ( GLFW_KEY_KP_4 ),
        KeyKeypad5              = static_cast < cds :: sint16 > ( GLFW_KEY_KP_5 ),
        KeyKeypad6              = static_cast < cds :: sint16 > ( GLFW_KEY_KP_6 ),
        KeyKeypad7              = static_cast < cds :: sint16 > ( GLFW_KEY_KP_7 ),
        KeyKeypad8              = static_cast < cds :: sint16 > ( GLFW_KEY_KP_8 ),
        KeyKeypad9              = static_cast < cds :: sint16 > ( GLFW_KEY_KP_9 ),
        KeyKeypadDecimal        = static_cast < cds :: sint16 > ( GLFW_KEY_KP_DECIMAL ),
        KeyKeypadDivide         = static_cast < cds :: sint16 > ( GLFW_KEY_KP_DIVIDE ),
        KeyKeypadMultiply       = static_cast < cds :: sint16 > ( GLFW_KEY_KP_MULTIPLY ),
        KeyKeypadSubtract       = static_cast < cds :: sint16 > ( GLFW_KEY_KP_SUBTRACT ),
        KeyKeypadAdd            = static_cast < cds :: sint16 > ( GLFW_KEY_KP_ADD ),
        KeyKeypadEnter          = static_cast < cds :: sint16 > ( GLFW_KEY_KP_ENTER ),
        KeyKeypadEqual          = static_cast < cds :: sint16 > ( GLFW_KEY_KP_EQUAL ),
        KeyLeftShift            = static_cast < cds :: sint16 > ( GLFW_KEY_LEFT_SHIFT ),
        KeyLeftControl          = static_cast < cds :: sint16 > ( GLFW_KEY_LEFT_CONTROL ),
        KeyLeftAlt              = static_cast < cds :: sint16 > ( GLFW_KEY_LEFT_ALT ),
        KeyLeftSuper            = static_cast < cds :: sint16 > ( GLFW_KEY_LEFT_SUPER ),
        KeyRightShift           = static_cast < cds :: sint16 > ( GLFW_KEY_RIGHT_SHIFT ),
        KeyRightControl         = static_cast < cds :: sint16 > ( GLFW_KEY_RIGHT_CONTROL ),
        KeyRightAlt             = static_cast < cds :: sint16 > ( GLFW_KEY_RIGHT_ALT ),
        KeyRightSuper           = static_cast < cds :: sint16 > ( GLFW_KEY_RIGHT_SUPER ),
        KeyMenu                 = static_cast < cds :: sint16 > ( GLFW_KEY_MENU ),
    };

    enum MouseButton : cds :: uint8 {
        MouseButton1                            = static_cast < cds :: uint8 > ( GLFW_MOUSE_BUTTON_1 ),
        MouseButton2                            = static_cast < cds :: uint8 > ( GLFW_MOUSE_BUTTON_2 ),
        MouseButton3                            = static_cast < cds :: uint8 > ( GLFW_MOUSE_BUTTON_3 ),
        MouseButton4                            = static_cast < cds :: uint8 > ( GLFW_MOUSE_BUTTON_4 ),
        MouseButton5                            = static_cast < cds :: uint8 > ( GLFW_MOUSE_BUTTON_5 ),
        MouseButton6                            = static_cast < cds :: uint8 > ( GLFW_MOUSE_BUTTON_6 ),
        MouseButton7                            = static_cast < cds :: uint8 > ( GLFW_MOUSE_BUTTON_7 ),
        MouseButton8                            = static_cast < cds :: uint8 > ( GLFW_MOUSE_BUTTON_8 ),

        MouseButtonLeft      C_ENG_MAYBE_UNUSED = MouseButton1,
        MouseButtonRight     C_ENG_MAYBE_UNUSED = MouseButton2,
        MouseButtonMiddle    C_ENG_MAYBE_UNUSED = MouseButton3,

        MouseButtonUndefined                    = 0xffU
    };

    enum WindowFlag : cds :: uint16 {
        WindowFlagNone                      = 0x0000U,
        WindowFlagResizable                 = 0x0001U,
        WindowFlagBorderless                = 0x0002U,
        WindowFlagStartMinimized            = 0x0004U,
        WindowFlagGrabFocusOnOpen           = 0x0008U,
        WindowFlagRestorePreviousMode       = 0x0010U,
        WindowFlagStayOnTop                 = 0x0020U,
        WindowFlagStartMaximized            = 0x0040U,
        WindowFlagCenterCursorOnCreate      = 0x0080U,
        WindowFlagTransparentFramebuffer    = 0x0100U,
        WindowFlagGrabFocusOnRaise          = 0x0200U,
        WindowFlagScaleToMonitor            = 0x0400U,

        WindowFlagMaxValue                  = WindowFlagScaleToMonitor
    };

    enum WindowType {
        WindowTypeWindowed              = 0x00U,
        WindowTypeFullscreen            = 0x01U,
        WindowTypeWindowedFullscreen    = 0x02U
    };

    enum ControllerHatState : cds :: uint8 {
        ControllerHatStateCentered  = static_cast < cds :: uint8 > ( GLFW_HAT_CENTERED ),
        ControllerHatStateUp        = static_cast < cds :: uint8 > ( GLFW_HAT_UP ),
        ControllerHatStateLeft      = static_cast < cds :: uint8 > ( GLFW_HAT_LEFT ),
        ControllerHatStateRight     = static_cast < cds :: uint8 > ( GLFW_HAT_RIGHT ),
        ControllerHatStateDown      = static_cast < cds :: uint8 > ( GLFW_HAT_DOWN ),
        ControllerHatStateLeftUp    = static_cast < cds :: uint8 > ( GLFW_HAT_LEFT_UP ),
        ControllerHatStateLeftDown  = static_cast < cds :: uint8 > ( GLFW_HAT_LEFT_DOWN ),
        ControllerHatStateRightUp   = static_cast < cds :: uint8 > ( GLFW_HAT_RIGHT_UP ),
        ControllerHatStateRightDown = static_cast < cds :: uint8 > ( GLFW_HAT_RIGHT_DOWN )
    };


    struct Position {
        cds :: uint32 x;
        cds :: uint32 y;
    };

    struct RectangleSize {
        cds :: uint32 width;
        cds :: uint32 height;
    };

    struct ColorChannelsDepth {
        cds :: uint32 red;
        cds :: uint32 green;
        cds :: uint32 blue;
    };

    struct MonitorVideoModeProperties {
        RectangleSize       size;
        ColorChannelsDepth  colorChannelsDepth;
        cds :: uint32       refreshRate;
    };

    struct ContentScale {
        float x;
        float y;
    };

    struct MonitorWorkArea {
        Position        position;
        RectangleSize   size;
    };

    using MonitorName = cds :: StringLiteral;
    using MonitorGammaRampValue = cds :: uint16 *;
    using Flags                 = cds :: uint32;
    using KeyModifiers          = Flags;
    using MonitorContentScale   = ContentScale;
    using WindowContentScale    = ContentScale;
    using WindowFlags           = Flags;

    struct MonitorGammaRamp {
        cds :: uint32           size;
        MonitorGammaRampValue   red;
        MonitorGammaRampValue   green;
        MonitorGammaRampValue   blue;
    };

    struct MonitorProperties {
        MonitorName                 name;
        RectangleSize               physicalSizeMM;
        MonitorContentScale         contentScale;
        MonitorWorkArea             workArea;
        MonitorGammaRamp            gammaRamp;
        MonitorVideoModeProperties  activeVideoMode;
    };


    C_ENG_NO_DISCARD auto toString ( bool ) noexcept -> cds :: StringLiteral;
    C_ENG_NO_DISCARD auto toString ( void const * ) noexcept -> cds :: String;

    C_ENG_NO_DISCARD auto toString ( EngineState ) noexcept -> cds :: StringLiteral;
    C_ENG_NO_DISCARD auto toString ( LogLevel ) noexcept -> cds :: StringLiteral;
    C_ENG_NO_DISCARD auto toString ( EventType ) noexcept -> cds :: StringLiteral;
    C_ENG_NO_DISCARD auto toString ( KeyModifier ) noexcept -> cds :: StringLiteral;
    C_ENG_NO_DISCARD auto toString ( Key ) noexcept -> cds :: StringLiteral;
    C_ENG_NO_DISCARD auto toString ( MouseButton ) noexcept -> cds :: StringLiteral;
    C_ENG_NO_DISCARD auto toString ( WindowType ) noexcept -> cds :: StringLiteral;
    C_ENG_NO_DISCARD auto toString ( WindowFlag ) noexcept -> cds :: StringLiteral;
    C_ENG_NO_DISCARD auto toString ( ControllerHatState ) noexcept -> cds :: StringLiteral;

    C_ENG_NO_DISCARD auto toString ( Position const & ) noexcept -> cds :: String;
    C_ENG_NO_DISCARD auto toString ( RectangleSize const & ) noexcept -> cds :: String;
    C_ENG_NO_DISCARD auto toString ( ColorChannelsDepth const & ) noexcept -> cds :: String;
    C_ENG_NO_DISCARD auto toString ( MonitorVideoModeProperties const & ) noexcept -> cds :: String;
    C_ENG_NO_DISCARD auto toString ( ContentScale const & ) noexcept -> cds :: String;
    C_ENG_NO_DISCARD auto toString ( MonitorWorkArea const & ) noexcept -> cds :: String;
    C_ENG_NO_DISCARD auto toString ( MonitorGammaRamp const & ) noexcept -> cds :: String;
    C_ENG_NO_DISCARD auto toString ( MonitorProperties const & ) noexcept -> cds :: String;

    C_ENG_NO_DISCARD auto keyModifiersToString ( KeyModifiers ) noexcept -> cds :: String;
    C_ENG_NO_DISCARD auto windowFlagsToString ( WindowFlags ) noexcept -> cds :: String;


    C_ENG_NO_DISCARD constexpr auto equals (
            Position const & left,
            Position const & right
    ) noexcept -> bool {

        return
            left.x == right.x &&
            left.y == right.y;
    }

    C_ENG_NO_DISCARD constexpr auto equals (
            RectangleSize const & left,
            RectangleSize const & right
    ) noexcept -> bool {

        return
            left.width == right.width &&
            left.height == right.height;
    }

    C_ENG_NO_DISCARD constexpr auto equals (
            ColorChannelsDepth const & left,
            ColorChannelsDepth const & right
    ) noexcept -> bool {

        return
            left.red == right.red &&
            left.green == right.green &&
            left.blue == right.blue;
    }

    C_ENG_NO_DISCARD constexpr auto equals (
            MonitorVideoModeProperties const & left,
            MonitorVideoModeProperties const & right
    ) noexcept -> bool {

        return
            equals ( left.size, right.size ) &&
            equals ( left.colorChannelsDepth, right.colorChannelsDepth ) &&
            left.refreshRate == right.refreshRate;
    }

    C_ENG_NO_DISCARD constexpr auto equals (
            ContentScale const & left,
            ContentScale const & right
    ) noexcept -> bool {

        return
            left.x == right.x &&
            left.y == right.y;
    }

    C_ENG_NO_DISCARD constexpr auto equals (
            MonitorWorkArea const & left,
            MonitorWorkArea const & right
    ) noexcept -> bool {

        return
            equals ( left.position, right.position ) &&
            equals ( left.size, right.size );
    }

    C_ENG_NO_DISCARD constexpr auto equals (
            MonitorGammaRamp const & left,
            MonitorGammaRamp const & right
    ) noexcept -> bool {

        return
            left.size == right.size &&
            std :: char_traits < cds :: uint16 > :: compare ( left.red, right.red, left.size ) == 0 &&
            std :: char_traits < cds :: uint16 > :: compare ( left.green, right.green, left.size ) == 0 &&
            std :: char_traits < cds :: uint16 > :: compare ( left.blue, right.blue, left.size ) == 0;
    }

    C_ENG_NO_DISCARD constexpr auto equals (
            MonitorProperties const & left,
            MonitorProperties const & right
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

#endif //C_ENG_CORE_HPP

//
// Created by loghin on 20.12.2021.
//

#ifndef C_ENG_CORE_HPP
#define C_ENG_CORE_HPP

#include <CDS/Types>

namespace engine {

    using Flags = cds :: uint32;

    enum EngineState : cds :: uint8 {
        EngineStateInactive                 = 0x00U,
        EngineStateStartup                  = 0x01U,
        EngineStateStartupAcquiringSettings = 0x02U,
        EngineStateRunning                  = 0x03U,
        EngineStateShutdown                 = 0x04U
    };

    C_ENG_NO_DISCARD constexpr auto toString ( EngineState state ) noexcept -> cds :: StringLiteral {
        cds :: StringLiteral asString;

        switch ( state ) {
            case EngineStateInactive:                   { asString = "Inactive";                    break; }
            case EngineStateStartupAcquiringSettings:   { asString = "Acquiring Settings";          break; }
            case EngineStateStartup:                    { asString = "Starting Up";                 break; }
            case EngineStateRunning:                    { asString = "Running";                     break; }
            case EngineStateShutdown:                   { asString = "Shutdown";                    break; }
        }

        return asString;
    }


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

    C_ENG_NO_DISCARD constexpr auto toString ( LogLevel level ) noexcept -> cds :: StringLiteral {
        cds :: StringLiteral asString = "";

        switch ( level ) {
            case LogLevelForced:    { asString = "Forced";      break; }
            case LogLevelSystem:    { asString = "System";      break; }
            case LogLevelFatal:     { asString = "Fatal";       break; }
            case LogLevelCritical:  { asString = "Critical";    break; }
            case LogLevelError:     { asString = "Error";       break; }
            case LogLevelWarning:   { asString = "Warning";     break; }
            case LogLevelDebug:     { asString = "Debug";       break; }
            case LogLevelInfo:      { asString = "Info";        break; }
        }

        return asString;
    }


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
        EventTypeControllerAxisChangeEvent      = 0x1aU,
        EventTypeControllerButtonPressEvent     = 0x1bU,
        EventTypeControllerButtonReleaseEvent   = 0x1cU,
        EventTypeControllerHatChangeEvent       = 0x1dU
    };

    C_ENG_NO_DISCARD constexpr auto toString ( EventType type ) noexcept -> cds :: StringLiteral {
        cds :: StringLiteral asString = "";

        switch ( type ) {
            case EventTypeCustom:                       { asString = "CustomEvent";                     break; }

            case EventTypeCustomKeyEvent:               { asString = "CustomKeyEvent";                  break; }
            case EventTypeKeyPressEvent:                { asString = "KeyPressEvent";                   break; }
            case EventTypeKeyReleaseEvent:              { asString = "KeyReleaseEvent";                 break; }

            case EventTypeCustomMouseEvent:             { asString = "CustomMouseEvent";                break; }
            case EventTypeMouseMoveEvent:               { asString = "MouseMoveEvent";                  break; }
            case EventTypeMouseEnterEvent:              { asString = "MouseEnterEvent";                 break; }
            case EventTypeMouseLeaveEvent:              { asString = "MouseLeaveEvent";                 break; }
            case EventTypeMouseScrollEvent:             { asString = "MouseScrollEvent";                break; }
            case EventTypeMousePressEvent:              { asString = "MousePressEvent";                 break; }
            case EventTypeMouseReleaseEvent:            { asString = "MouseReleaseEvent";               break; }

            case EventTypeCustomWindowEvent:            { asString = "CustomWindowEvent";               break; }
            case EventTypeWindowResizeEvent:            { asString = "WindowResizeEvent";               break; }
            case EventTypeWindowFrameBufferResizeEvent: { asString = "WindowFrameBufferResizeEvent";    break; }
            case EventTypeWindowCloseEvent:             { asString = "WindowCloseEvent";                break; }
            case EventTypeWindowContentScaleEvent:      { asString = "WindowContentScaleEvent";         break; }
            case EventTypeWindowMoveEvent:              { asString = "WindowMoveEvent";                 break; }
            case EventTypeWindowRestoreEvent:           { asString = "WindowRestoreEvent";              break; }
            case EventTypeWindowMinimizeEvent:          { asString = "WindowMinimizeEvent";             break; }
            case EventTypeWindowMaximizeEvent:          { asString = "WindowMaximizeEvent";             break; }
            case EventTypeWindowGainFocusEvent:         { asString = "WindowGainFocusEvent";            break; }
            case EventTypeWindowLoseFocusEvent:         { asString = "WindowLoseFocusEvent";            break; }
            case EventTypeWindowRefreshRequestEvent:    { asString = "WindowRefreshRequestEvent";       break; }

            case EventTypeCustomControllerEvent:        { asString = "CustomControllerEvent";           break; }
            case EventTypeControllerConnectEvent:       { asString = "ControllerConnectEvent";          break; }
            case EventTypeControllerDisconnectEvent:    { asString = "ControllerDisconnectEvent";       break; }
            case EventTypeControllerAxisChangeEvent:    { asString = "ControllerAxisChangeEvent";       break; }
            case EventTypeControllerHatChangeEvent:     { asString = "ControllerHatChangeEvent";        break; }
            case EventTypeControllerButtonPressEvent:   { asString = "ControllerButtonPressEvent";      break; }
            case EventTypeControllerButtonReleaseEvent: { asString = "ControllerButtonReleaseEvent";    break; }
        }

        return asString;
    }


    enum KeyModifier : cds :: uint16 {
        KeyModifierNone     = 0x0000U,
        KeyModifierShift    = static_cast < cds :: uint16 > ( GLFW_MOD_SHIFT ),
        KeyModifierControl  = static_cast < cds :: uint16 > ( GLFW_MOD_CONTROL ),
        KeyModifierAlt      = static_cast < cds :: uint16 > ( GLFW_MOD_ALT ),
        KeyModifierSuper    = static_cast < cds :: uint16 > ( GLFW_MOD_SUPER ),
        KeyModifierCapsLock = static_cast < cds :: uint16 > ( GLFW_MOD_CAPS_LOCK ),
        KeyModifierNumLock  = static_cast < cds :: uint16 > ( GLFW_MOD_NUM_LOCK )
    };

    using KeyModifiers = Flags;

    C_ENG_NO_DISCARD constexpr auto toString ( KeyModifier modifier ) noexcept -> cds :: StringLiteral {
        cds :: StringLiteral asString = "";

        switch ( modifier ) {
            case KeyModifierNone:       { asString = "None";        break; }
            case KeyModifierShift:      { asString = "Shift";       break; }
            case KeyModifierControl:    { asString = "Control";     break; }
            case KeyModifierAlt:        { asString = "Alt";         break; }
            case KeyModifierSuper:      { asString = "Super";       break; }
            case KeyModifierCapsLock:   { asString = "Caps Lock";   break; }
            case KeyModifierNumLock:    { asString = "Num Lock";    break; }
        }

        return asString;
    }


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

    C_ENG_NO_DISCARD constexpr auto toString ( Key key ) noexcept -> cds :: StringLiteral {
        cds :: StringLiteral asString = "";

        switch ( key ) {
            case KeyUnknown:        { asString = "Unknown Key";             break; }
            case KeySpace:          { asString = "Space ( )";               break; }
            case KeyApostrophe:     { asString = "Apostrophe (')";          break; }
            case KeyComma:          { asString = "Comma (,)";               break; }
            case KeyMinus:          { asString = "Minus (-)";               break; }
            case KeyPeriod:         { asString = "Period (.)";              break; }
            case KeySlash:          { asString = "Slash (/)";               break; }
            case Key0:              { asString = "Zero (0)";                break; }
            case Key1:              { asString = "One (1)";                 break; }
            case Key2:              { asString = "Two (2)";                 break; }
            case Key3:              { asString = "Three (3)";               break; }
            case Key4:              { asString = "Four (4)";                break; }
            case Key5:              { asString = "Five (5)";                break; }
            case Key6:              { asString = "Six (6)";                 break; }
            case Key7:              { asString = "Seven (7)";               break; }
            case Key8:              { asString = "Eight (8)";               break; }
            case Key9:              { asString = "Nine (9)";                break; }
            case KeySemicolon:      { asString = "Semicolon (;)";           break; }
            case KeyEqual:          { asString = "Equal (=)";               break; }
            case KeyA:              { asString = "Letter A (A)";            break; }
            case KeyB:              { asString = "Letter B (B)";            break; }
            case KeyC:              { asString = "Letter C (C)";            break; }
            case KeyD:              { asString = "Letter D (D)";            break; }
            case KeyE:              { asString = "Letter E (E)";            break; }
            case KeyF:              { asString = "Letter F (F)";            break; }
            case KeyG:              { asString = "Letter G (G)";            break; }
            case KeyH:              { asString = "Letter H (H)";            break; }
            case KeyI:              { asString = "Letter I (I)";            break; }
            case KeyJ:              { asString = "Letter J (J)";            break; }
            case KeyK:              { asString = "Letter K (K)";            break; }
            case KeyL:              { asString = "Letter L (L)";            break; }
            case KeyM:              { asString = "Letter M (M)";            break; }
            case KeyN:              { asString = "Letter N (N)";            break; }
            case KeyO:              { asString = "Letter O (O)";            break; }
            case KeyP:              { asString = "Letter P (P)";            break; }
            case KeyQ:              { asString = "Letter Q (Q)";            break; }
            case KeyR:              { asString = "Letter R (R)";            break; }
            case KeyS:              { asString = "Letter S (S)";            break; }
            case KeyT:              { asString = "Letter T (T)";            break; }
            case KeyU:              { asString = "Letter U (U)";            break; }
            case KeyV:              { asString = "Letter V (V)";            break; }
            case KeyW:              { asString = "Letter W (W)";            break; }
            case KeyX:              { asString = "Letter X (X)";            break; }
            case KeyY:              { asString = "Letter Y (Y)";            break; }
            case KeyZ:              { asString = "Letter Z (Z)";            break; }
            case KeyLeftBracket:    { asString = "Left Bracket ([)";        break; }
            case KeyBackslash:      { asString = "Backslash (\\)";          break; } // NOLINT(clion-misra-cpp2008-2-13-1)
            case KeyRightBracket:   { asString = "Right Bracket (])";       break; }
            case KeyGraveAccent:    { asString = "Grave Accent (`)";        break; }
            case KeyWorld1:         { asString = "World 1 (Non-US #)";      break; }
            case KeyWorld2:         { asString = "World 2 (Non-US #)";      break; }
            case KeyEscape:         { asString = "Escape";                  break; }
            case KeyEnter:          { asString = "Enter";                   break; }
            case KeyTab:            { asString = "Tab";                     break; }
            case KeyBackspace:      { asString = "Backspace";               break; }
            case KeyInsert:         { asString = "Insert";                  break; }
            case KeyDelete:         { asString = "Delete";                  break; }
            case KeyRight:          { asString = "Right Arrow";             break; }
            case KeyLeft:           { asString = "Left Arrow";              break; }
            case KeyDown:           { asString = "Down Arrow";              break; }
            case KeyUp:             { asString = "Up Arrow";                break; }
            case KeyPageUp:         { asString = "Page Up";                 break; }
            case KeyPageDown:       { asString = "Page Down";               break; }
            case KeyHome:           { asString = "Home";                    break; }
            case KeyEnd:            { asString = "End";                     break; }
            case KeyCapsLock:       { asString = "Caps Lock";               break; }
            case KeyScrollLock:     { asString = "Scroll Lock";             break; }
            case KeyNumLock:        { asString = "Num Lock";                break; }
            case KeyPrintScreen:    { asString = "Print Screen";            break; }
            case KeyPause:          { asString = "Pause";                   break; }
            case KeyF1:             { asString = "Function Key 1 (F1)";     break; }
            case KeyF2:             { asString = "Function Key 2 (F2)";     break; }
            case KeyF3:             { asString = "Function Key 3 (F3)";     break; }
            case KeyF4:             { asString = "Function Key 4 (F4)";     break; }
            case KeyF5:             { asString = "Function Key 5 (F5)";     break; }
            case KeyF6:             { asString = "Function Key 6 (F6)";     break; }
            case KeyF7:             { asString = "Function Key 7 (F7)";     break; }
            case KeyF8:             { asString = "Function Key 8 (F8)";     break; }
            case KeyF9:             { asString = "Function Key 9 (F9)";     break; }
            case KeyF10:            { asString = "Function Key 10 (F10)";   break; }
            case KeyF11:            { asString = "Function Key 11 (F11)";   break; }
            case KeyF12:            { asString = "Function Key 12 (F12)";   break; }
            case KeyF13:            { asString = "Function Key 13 (F13)";   break; }
            case KeyF14:            { asString = "Function Key 14 (F14)";   break; }
            case KeyF15:            { asString = "Function Key 15 (F15)";   break; }
            case KeyF16:            { asString = "Function Key 16 (F16)";   break; }
            case KeyF17:            { asString = "Function Key 17 (F17)";   break; }
            case KeyF18:            { asString = "Function Key 18 (F18)";   break; }
            case KeyF19:            { asString = "Function Key 19 (F19)";   break; }
            case KeyF20:            { asString = "Function Key 20 (F20)";   break; }
            case KeyF21:            { asString = "Function Key 21 (F21)";   break; }
            case KeyF22:            { asString = "Function Key 22 (F22)";   break; }
            case KeyF23:            { asString = "Function Key 23 (F23)";   break; }
            case KeyF24:            { asString = "Function Key 24 (F24)";   break; }
            case KeyF25:            { asString = "Function Key 25 (F25)";   break; }
            case KeyKeypad0:        { asString = "Keypad Zero (0)";         break; }
            case KeyKeypad1:        { asString = "Keypad One (1)";          break; }
            case KeyKeypad2:        { asString = "Keypad Two (2)";          break; }
            case KeyKeypad3:        { asString = "Keypad Three (3)";        break; }
            case KeyKeypad4:        { asString = "Keypad Four (4)";         break; }
            case KeyKeypad5:        { asString = "Keypad Five (5)";         break; }
            case KeyKeypad6:        { asString = "Keypad Six (6)";          break; }
            case KeyKeypad7:        { asString = "Keypad Seven (7)";        break; }
            case KeyKeypad8:        { asString = "Keypad Eight (8)";        break; }
            case KeyKeypad9:        { asString = "Keypad Nine (9)";         break; }
            case KeyKeypadDecimal:  { asString = "Keypad Decimal (.)";      break; }
            case KeyKeypadDivide:   { asString = "Keypad Divide (/)";       break; }
            case KeyKeypadMultiply: { asString = "Keypad Multiply (*)";     break; }
            case KeyKeypadSubtract: { asString = "Keypad Subtract (-)";     break; }
            case KeyKeypadAdd:      { asString = "Keypad Add (+)";          break; }
            case KeyKeypadEnter:    { asString = "Keypad Enter";            break; }
            case KeyKeypadEqual:    { asString = "Keypad Equal (=)";        break; }
            case KeyLeftShift:      { asString = "Left Shift";              break; }
            case KeyLeftControl:    { asString = "Left Control";            break; }
            case KeyLeftAlt:        { asString = "Left Alt";                break; }
            case KeyLeftSuper:      { asString = "Left Super";              break; }
            case KeyRightShift:     { asString = "Right Shift";             break; }
            case KeyRightControl:   { asString = "Right Control";           break; }
            case KeyRightAlt:       { asString = "Right Alt";               break; }
            case KeyRightSuper:     { asString = "Right Super";             break; }
            case KeyMenu:           { asString = "Menu";                    break; }
        }

        return asString;
    }


    enum MouseButton : cds :: uint8 {
        MouseButton1                            = static_cast < cds :: uint8 > ( GLFW_MOUSE_BUTTON_1 ),
        MouseButton2                            = static_cast < cds :: uint8 > ( GLFW_MOUSE_BUTTON_2 ),
        MouseButton3                            = static_cast < cds :: uint8 > ( GLFW_MOUSE_BUTTON_3 ),
        MouseButton4                            = static_cast < cds :: uint8 > ( GLFW_MOUSE_BUTTON_4 ),
        MouseButton5                            = static_cast < cds :: uint8 > ( GLFW_MOUSE_BUTTON_5 ),
        MouseButton6                            = static_cast < cds :: uint8 > ( GLFW_MOUSE_BUTTON_6 ),
        MouseButton7                            = static_cast < cds :: uint8 > ( GLFW_MOUSE_BUTTON_7 ),
        MouseButton8                            = static_cast < cds :: uint8 > ( GLFW_MOUSE_BUTTON_8 ),

        MouseButtonLeft     C_ENG_MAYBE_UNUSED  = MouseButton1,
        MouseButtonRight    C_ENG_MAYBE_UNUSED  = MouseButton2,
        MouseButtonMiddle   C_ENG_MAYBE_UNUSED  = MouseButton3,

        MouseButtonUndefined                    = 0xffU
    };

    C_ENG_NO_DISCARD constexpr auto toString ( MouseButton mouseButton ) noexcept -> cds :: StringLiteral {
        cds :: StringLiteral asString = "";

        switch ( mouseButton ) {
            case MouseButton1:          { asString = "Mouse Button 1 ( Left Click )";   break; }
            case MouseButton2:          { asString = "Mouse Button 2 ( Right Click )";  break; }
            case MouseButton3:          { asString = "Mouse Button 3 ( Middle Click )"; break; }
            case MouseButton4:          { asString = "Mouse Button 4";                  break; }
            case MouseButton5:          { asString = "Mouse Button 5";                  break; }
            case MouseButton6:          { asString = "Mouse Button 6";                  break; }
            case MouseButton7:          { asString = "Mouse Button 7";                  break; }
            case MouseButton8:          { asString = "Mouse Button 8";                  break; }
            case MouseButtonUndefined:  { asString = "Undefined Mouse Button";          break; }
        }

        return asString;
    }


    enum WindowType {
        WindowTypeWindowed = 0x00U,
        WindowTypeFullscreen = 0x01U,
        WindowTypeWindowedFullscreen = 0x02U
    };

    C_ENG_NO_DISCARD constexpr auto toString ( WindowType type ) noexcept -> cds :: StringLiteral {
        cds :: StringLiteral asString = "";

        switch ( type ) {
            case WindowTypeWindowed:            { asString = "Windowed";            break; }
            case WindowTypeFullscreen:          { asString = "Fullscreen";          break; }
            case WindowTypeWindowedFullscreen:  { asString = "Windowed Fullscreen"; break; }
        }

        return asString;
    }

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

    struct MonitorContentScale {
        float x;
        float y;
    };

    struct WindowContentScale {
        float x;
        float y;
    };

    struct MonitorWorkArea {
        Position        position;
        RectangleSize   size;
    };

    using MonitorName = cds :: StringLiteral;

    using MonitorGammaRampValue = cds :: uint16 *;

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

    using WindowFlags = Flags;

    C_ENG_NO_DISCARD constexpr auto toString ( WindowFlag flag ) noexcept -> cds :: StringLiteral {
        cds :: StringLiteral asString = "";

        switch ( flag ) {
            case WindowFlagNone:                    { asString = "No Flag";                                 break; }
            case WindowFlagResizable:               { asString = "Is Resizable";                            break; }
            case WindowFlagBorderless:              { asString = "Borderless Window, Undecorated";          break; }
            case WindowFlagStartMinimized:          { asString = "Start Minimized";                         break; }
            case WindowFlagGrabFocusOnOpen:         { asString = "Grab Input Focus on Open";                break; }
            case WindowFlagRestorePreviousMode:     { asString = "Fullscreen Restore Video Mode on Focus";  break; }
            case WindowFlagStayOnTop:               { asString = "Force On Top";                            break; }
            case WindowFlagStartMaximized:          { asString = "Start Window Maximized";                  break; }
            case WindowFlagCenterCursorOnCreate:    { asString = "Center Mouse Cursor on Create";           break; }
            case WindowFlagTransparentFramebuffer:  { asString = "Transparent Framebuffer";                 break; }
            case WindowFlagGrabFocusOnRaise:        { asString = "Grab Input Focus On Raise";               break; }
            case WindowFlagScaleToMonitor:          { asString = "Scale Content to Monitor Content Scale";  break; }
        }

        return asString;
    }

}

#endif //C_ENG_CORE_HPP

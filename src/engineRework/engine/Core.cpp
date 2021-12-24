//
// Created by loghin on 23.12.2021.
//

#include <Preprocess.hpp>
#include <CDS/String>
#include <Core.hpp>

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

#include <CDS/Long>

namespace engine {

    C_ENG_NO_DISCARD auto toString (
            bool value
    ) noexcept -> StringLiteral {
        return value ? "true" : "false";
    }

    C_ENG_NO_DISCARD auto toString (
            void const * address
    ) noexcept -> String {
        return
            address == nullptr ? "null" : (
                    "0x"_s +
                    Long ( reinterpret_cast < AddressValueType const > ( address ) ).toString(16) // NOLINT(clion-misra-cpp2008-5-2-9)
            ).cStr();
    }

    C_ENG_NO_DISCARD auto toString (
            EngineState state
    ) noexcept -> StringLiteral {

        StringLiteral asString;

        switch ( state ) {
            case EngineStateInactive:                   { asString = "Inactive";                    break; }
            case EngineStateStartupAcquiringSettings:   { asString = "Acquiring Settings";          break; }
            case EngineStateStartup:                    { asString = "Starting Up";                 break; }
            case EngineStateRunning:                    { asString = "Running";                     break; }
            case EngineStateShutdown:                   { asString = "Shutdown";                    break; }
        }

        return asString;
    }

    C_ENG_NO_DISCARD auto toString (
            LogLevel level
    ) noexcept -> StringLiteral {

        StringLiteral asString = "";

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

    C_ENG_NO_DISCARD auto toString (
            EventType type
    ) noexcept -> StringLiteral {

        StringLiteral asString = "";

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
            case EventTypeControllerAxisEvent:          { asString = "ControllerAxisEvent";             break; }
            case EventTypeControllerHatEvent:           { asString = "ControllerHatEvent";              break; }
            case EventTypeControllerButtonPressEvent:   { asString = "ControllerButtonPressEvent";      break; }
            case EventTypeControllerButtonReleaseEvent: { asString = "ControllerButtonReleaseEvent";    break; }
        }

        return asString;
    }

    C_ENG_NO_DISCARD auto toString (
            KeyModifier modifier
    ) noexcept -> StringLiteral {

        StringLiteral asString = "";

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

    C_ENG_NO_DISCARD auto toString (
            Key key
    ) noexcept -> StringLiteral {

        StringLiteral asString = "";

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

    C_ENG_NO_DISCARD auto toString (
            MouseButton mouseButton
    ) noexcept -> StringLiteral {

        StringLiteral asString = "";

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

    C_ENG_NO_DISCARD auto toString (
            WindowType type
    ) noexcept -> StringLiteral {

        StringLiteral asString = "";

        switch ( type ) {
            case WindowTypeWindowed:            { asString = "Windowed";            break; }
            case WindowTypeFullscreen:          { asString = "Fullscreen";          break; }
            case WindowTypeWindowedFullscreen:  { asString = "Windowed Fullscreen"; break; }
        }

        return asString;
    }

    C_ENG_NO_DISCARD auto toString (
            WindowFlag flag
    ) noexcept -> StringLiteral {

        StringLiteral asString = "";

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

    C_ENG_NO_DISCARD auto toString (
            ControllerHatState state
    ) noexcept -> StringLiteral {

        StringLiteral asString = "";

        switch ( state ) {
            case ControllerHatStateCentered:    { asString = "ControllerHatCentered";   break; }
            case ControllerHatStateUp:          { asString = "ControllerHatUp";         break; }
            case ControllerHatStateLeft:        { asString = "ControllerHatLeft";       break; }
            case ControllerHatStateRight:       { asString = "ControllerHatRight";      break; }
            case ControllerHatStateDown:        { asString = "ControllerHatDown";       break; }
            case ControllerHatStateLeftUp:      { asString = "ControllerHatLeftUp";     break; }
            case ControllerHatStateLeftDown:    { asString = "ControllerHatLeftDown";   break; }
            case ControllerHatStateRightUp:     { asString = "ControllerHatRightUp";    break; }
            case ControllerHatStateRightDown:   { asString = "ControllerHatRightDown";  break; }
        }

        return asString;
    }


    C_ENG_NO_DISCARD auto toString (
            Position const & position
    ) noexcept -> String {

        return "Position "
               "{ x = "_s   + position.x +
               ", y = "     + position.y +
               " }";
    }

    C_ENG_NO_DISCARD auto toString (
            RectangleSize const & size
    ) noexcept -> String {

        return "RectangleSize "
               "{ width = "_s   + size.width +
               ", height = "    + size.height +
               " }";
    }

    C_ENG_NO_DISCARD auto toString (
            ColorChannelsDepth const & depth
    ) noexcept -> String {

        return "ColorChannelsDepth "
               "{ red = "_s + depth.red +
               ", green = " + depth.green +
               ", blue = "  + depth.blue +
               " }";
    }

    C_ENG_NO_DISCARD auto toString (
            MonitorVideoModeProperties const & properties
    ) noexcept -> String {

        return "MonitorVideoModeProperties "
               "{ size = "                  + toString ( properties.size ) +
               ", colorChannelsDepth = "    + toString ( properties.colorChannelsDepth ) +
               ", refreshRate = "           + properties.refreshRate + "Hz"
                                                                       " }";
    }

    C_ENG_NO_DISCARD auto toString (
            ContentScale const & scale
    ) noexcept -> String {

        return "ContentScale "
               "{ x = "_s   + scale.x +
               ", y = "     + scale.y +
               " }";
    }

    C_ENG_NO_DISCARD auto toString (
            MonitorGammaRamp const & ramp
    ) noexcept -> String {

        auto rampToString = [ size = ramp.size ]( MonitorGammaRampValue ramp ) noexcept -> String {
            String asString;
            for ( uint32 i = 0U; i < size; ++ i ) {
                asString += ramp [ i ] + ", "_s;
            }

            return asString.removeSuffix(", ");
        };

        return "MonitorGammaRamp "
               "{ size = "_s    + ramp.size +
               ", red = "       + rampToString ( ramp.red ) +
               ", green = "     + rampToString ( ramp.green ) +
               ", blue = "      + rampToString ( ramp.blue ) +
               " }";
    }

    C_ENG_NO_DISCARD auto toString (
            MonitorWorkArea const & area
    ) noexcept -> String {

        return "MonitorWorkArea "
               "{ position = "  + toString ( area.position ) +
               ", size = "      + toString ( area.size ) +
               " }";
    }

    C_ENG_NO_DISCARD auto toString (
            MonitorProperties const & properties
    ) noexcept -> String {

        return "MonitorProperties "
               "{ name = "_s            + properties.name +
               ", physicalSize = "      + toString ( properties.physicalSizeMM ) +
               ", contentScale = "      + toString ( properties.contentScale ) +
               ", workArea = "          + toString ( properties.workArea ) +
               ", gammaRamp = "         + toString ( properties.gammaRamp ) +
               ", activeVideoMode = "   + toString ( properties.activeVideoMode ) +
               " }";
    }


    C_ENG_NO_DISCARD auto keyModifiersToString (
            KeyModifiers modifiers
    ) noexcept -> String {

        String asString = "";

        for ( uint32 f = 0x01U; true; f <<= 1 ) { // NOLINT(clion-misra-cpp2008-6-5-1)
            if ( ( f & modifiers ) != 0U ) {
                asString += toString ( static_cast < KeyModifier > ( f ) ) + ", "_s;
            }

            if ( f == KeyModifier :: KeyModifierMaxValue ) {
                break;
            }
        }

        return asString.removeSuffix(", ");
    }

    C_ENG_NO_DISCARD auto windowFlagsToString (
            WindowFlags modifiers
    ) noexcept -> String {

        String asString = "";

        for ( uint32 f = 0x01U; true; f <<= 1 ) { // NOLINT(clion-misra-cpp2008-6-5-1)
            if ( ( f & modifiers ) != 0U ) {
                asString += toString ( static_cast < KeyModifier > ( f ) ) + ", "_s;
            }

            if ( f == WindowFlag :: WindowFlagMaxValue ) {
                break;
            }
        }

        return asString.removeSuffix(", ");
    }

}
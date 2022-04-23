//
// Created by loghin on 23.12.2021.
//

#include <Preprocess.hpp>
#include <CDS/String>
#include <Core.hpp>

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

#include <CDS/Long>


#define C_ENG_MAP_START SOURCE
#include <ObjectMapping.hpp>

namespace engine {

    __C_ENG_NO_DISCARD auto toString (
            bool value
    ) noexcept -> StringLiteral {
        return value ? "true" : "false";
    }

    __C_ENG_NO_DISCARD auto toString (
            void const * address
    ) noexcept -> String {
        return
            address == nullptr ? "null" : (
                    "0x"_s +
                    Long ( reinterpret_cast < AddressValueType const > ( address ) ).toString(16) // NOLINT(clion-misra-cpp2008-5-2-9)
            ).cStr();
    }

    __C_ENG_NO_DISCARD auto toString (
            __C_ENG_TYPE ( EngineState ) state
    ) noexcept -> StringLiteral {

        StringLiteral asString;

        switch ( state ) {
            case __C_ENG_TYPE ( EngineState ) :: EngineStateInactive:                           { asString = "Inactive";                    break; }
            case __C_ENG_TYPE ( EngineState ) :: EngineStateStartupAcquiringSettings:           { asString = "Acquiring Settings";          break; }
            case __C_ENG_TYPE ( EngineState ) :: EngineStateStartupInitializingRenderEngine:    { asString = "Initializing Render Engine";  break; }
            case __C_ENG_TYPE ( EngineState ) :: EngineStateStartup:                            { asString = "Starting Up";                 break; }
            case __C_ENG_TYPE ( EngineState ) :: EngineStateRunning:                            { asString = "Running";                     break; }
            case __C_ENG_TYPE ( EngineState ) :: EngineStateShutdown:                           { asString = "Shutdown";                    break; }
        }

        return asString;
    }

    __C_ENG_NO_DISCARD auto toString (
            __C_ENG_TYPE ( LogLevel ) level
    ) noexcept -> StringLiteral {

        StringLiteral asString = "";

        switch ( level ) {
            case __C_ENG_TYPE ( LogLevel ) :: LogLevelForced:    { asString = "Forced";      break; }
            case __C_ENG_TYPE ( LogLevel ) :: LogLevelSystem:    { asString = "System";      break; }
            case __C_ENG_TYPE ( LogLevel ) :: LogLevelFatal:     { asString = "Fatal";       break; }
            case __C_ENG_TYPE ( LogLevel ) :: LogLevelCritical:  { asString = "Critical";    break; }
            case __C_ENG_TYPE ( LogLevel ) :: LogLevelError:     { asString = "Error";       break; }
            case __C_ENG_TYPE ( LogLevel ) :: LogLevelWarning:   { asString = "Warning";     break; }
            case __C_ENG_TYPE ( LogLevel ) :: LogLevelDebug:     { asString = "Debug";       break; }
            case __C_ENG_TYPE ( LogLevel ) :: LogLevelInfo:      { asString = "Info";        break; }
        }

        return asString;
    }

    __C_ENG_NO_DISCARD auto toString (
            __C_ENG_TYPE ( EventType ) type
    ) noexcept -> StringLiteral {

        StringLiteral asString = "";

        switch ( type ) {
            case __C_ENG_TYPE ( EventType ) :: EventTypeCustom:                       { asString = "CustomEvent";                     break; }

            case __C_ENG_TYPE ( EventType ) :: EventTypeCustomKeyEvent:               { asString = "CustomKeyEvent";                  break; }
            case __C_ENG_TYPE ( EventType ) :: EventTypeKeyPressEvent:                { asString = "KeyPressEvent";                   break; }
            case __C_ENG_TYPE ( EventType ) :: EventTypeKeyReleaseEvent:              { asString = "KeyReleaseEvent";                 break; }

            case __C_ENG_TYPE ( EventType ) :: EventTypeCustomMouseEvent:             { asString = "CustomMouseEvent";                break; }
            case __C_ENG_TYPE ( EventType ) :: EventTypeMouseMoveEvent:               { asString = "MouseMoveEvent";                  break; }
            case __C_ENG_TYPE ( EventType ) :: EventTypeMouseEnterEvent:              { asString = "MouseEnterEvent";                 break; }
            case __C_ENG_TYPE ( EventType ) :: EventTypeMouseLeaveEvent:              { asString = "MouseLeaveEvent";                 break; }
            case __C_ENG_TYPE ( EventType ) :: EventTypeMouseScrollEvent:             { asString = "MouseScrollEvent";                break; }
            case __C_ENG_TYPE ( EventType ) :: EventTypeMousePressEvent:              { asString = "MousePressEvent";                 break; }
            case __C_ENG_TYPE ( EventType ) :: EventTypeMouseReleaseEvent:            { asString = "MouseReleaseEvent";               break; }

            case __C_ENG_TYPE ( EventType ) :: EventTypeCustomWindowEvent:            { asString = "CustomWindowEvent";               break; }
            case __C_ENG_TYPE ( EventType ) :: EventTypeWindowResizeEvent:            { asString = "WindowResizeEvent";               break; }
            case __C_ENG_TYPE ( EventType ) :: EventTypeWindowFrameBufferResizeEvent: { asString = "WindowFrameBufferResizeEvent";    break; }
            case __C_ENG_TYPE ( EventType ) :: EventTypeWindowCloseEvent:             { asString = "WindowCloseEvent";                break; }
            case __C_ENG_TYPE ( EventType ) :: EventTypeWindowContentScaleEvent:      { asString = "WindowContentScaleEvent";         break; }
            case __C_ENG_TYPE ( EventType ) :: EventTypeWindowMoveEvent:              { asString = "WindowMoveEvent";                 break; }
            case __C_ENG_TYPE ( EventType ) :: EventTypeWindowRestoreEvent:           { asString = "WindowRestoreEvent";              break; }
            case __C_ENG_TYPE ( EventType ) :: EventTypeWindowMinimizeEvent:          { asString = "WindowMinimizeEvent";             break; }
            case __C_ENG_TYPE ( EventType ) :: EventTypeWindowMaximizeEvent:          { asString = "WindowMaximizeEvent";             break; }
            case __C_ENG_TYPE ( EventType ) :: EventTypeWindowGainFocusEvent:         { asString = "WindowGainFocusEvent";            break; }
            case __C_ENG_TYPE ( EventType ) :: EventTypeWindowLoseFocusEvent:         { asString = "WindowLoseFocusEvent";            break; }
            case __C_ENG_TYPE ( EventType ) :: EventTypeWindowRefreshRequestEvent:    { asString = "WindowRefreshRequestEvent";       break; }

            case __C_ENG_TYPE ( EventType ) :: EventTypeCustomControllerEvent:        { asString = "CustomControllerEvent";           break; }
            case __C_ENG_TYPE ( EventType ) :: EventTypeControllerConnectEvent:       { asString = "ControllerConnectEvent";          break; }
            case __C_ENG_TYPE ( EventType ) :: EventTypeControllerDisconnectEvent:    { asString = "ControllerDisconnectEvent";       break; }
            case __C_ENG_TYPE ( EventType ) :: EventTypeControllerAxisEvent:          { asString = "ControllerAxisEvent";             break; }
            case __C_ENG_TYPE ( EventType ) :: EventTypeControllerHatEvent:           { asString = "ControllerHatEvent";              break; }
            case __C_ENG_TYPE ( EventType ) :: EventTypeControllerButtonPressEvent:   { asString = "ControllerButtonPressEvent";      break; }
            case __C_ENG_TYPE ( EventType ) :: EventTypeControllerButtonReleaseEvent: { asString = "ControllerButtonReleaseEvent";    break; }
        }

        return asString;
    }

    __C_ENG_NO_DISCARD auto toString (
            __C_ENG_TYPE ( KeyModifier ) modifier
    ) noexcept -> StringLiteral {

        StringLiteral asString = "";

        switch ( modifier ) {
            case __C_ENG_TYPE ( KeyModifier ) :: KeyModifierNone:       { asString = "None";        break; }
            case __C_ENG_TYPE ( KeyModifier ) :: KeyModifierShift:      { asString = "Shift";       break; }
            case __C_ENG_TYPE ( KeyModifier ) :: KeyModifierControl:    { asString = "Control";     break; }
            case __C_ENG_TYPE ( KeyModifier ) :: KeyModifierAlt:        { asString = "Alt";         break; }
            case __C_ENG_TYPE ( KeyModifier ) :: KeyModifierSuper:      { asString = "Super";       break; }
            case __C_ENG_TYPE ( KeyModifier ) :: KeyModifierCapsLock:   { asString = "Caps Lock";   break; }
            case __C_ENG_TYPE ( KeyModifier ) :: KeyModifierNumLock:    { asString = "Num Lock";    break; }
        }

        return asString;
    }

    __C_ENG_NO_DISCARD auto toString (
            __C_ENG_TYPE ( Key ) key
    ) noexcept -> StringLiteral {

        StringLiteral asString = "";

        switch ( key ) {
            case __C_ENG_TYPE ( Key ) :: KeyUnknown:        { asString = "Unknown Key";             break; }
            case __C_ENG_TYPE ( Key ) :: KeySpace:          { asString = "Space ( )";               break; }
            case __C_ENG_TYPE ( Key ) :: KeyApostrophe:     { asString = "Apostrophe (')";          break; }
            case __C_ENG_TYPE ( Key ) :: KeyComma:          { asString = "Comma (,)";               break; }
            case __C_ENG_TYPE ( Key ) :: KeyMinus:          { asString = "Minus (-)";               break; }
            case __C_ENG_TYPE ( Key ) :: KeyPeriod:         { asString = "Period (.)";              break; }
            case __C_ENG_TYPE ( Key ) :: KeySlash:          { asString = "Slash (/)";               break; }
            case __C_ENG_TYPE ( Key ) :: Key0:              { asString = "Zero (0)";                break; }
            case __C_ENG_TYPE ( Key ) :: Key1:              { asString = "One (1)";                 break; }
            case __C_ENG_TYPE ( Key ) :: Key2:              { asString = "Two (2)";                 break; }
            case __C_ENG_TYPE ( Key ) :: Key3:              { asString = "Three (3)";               break; }
            case __C_ENG_TYPE ( Key ) :: Key4:              { asString = "Four (4)";                break; }
            case __C_ENG_TYPE ( Key ) :: Key5:              { asString = "Five (5)";                break; }
            case __C_ENG_TYPE ( Key ) :: Key6:              { asString = "Six (6)";                 break; }
            case __C_ENG_TYPE ( Key ) :: Key7:              { asString = "Seven (7)";               break; }
            case __C_ENG_TYPE ( Key ) :: Key8:              { asString = "Eight (8)";               break; }
            case __C_ENG_TYPE ( Key ) :: Key9:              { asString = "Nine (9)";                break; }
            case __C_ENG_TYPE ( Key ) :: KeySemicolon:      { asString = "Semicolon (;)";           break; }
            case __C_ENG_TYPE ( Key ) :: KeyEqual:          { asString = "Equal (=)";               break; }
            case __C_ENG_TYPE ( Key ) :: KeyA:              { asString = "Letter A (A)";            break; }
            case __C_ENG_TYPE ( Key ) :: KeyB:              { asString = "Letter B (B)";            break; }
            case __C_ENG_TYPE ( Key ) :: KeyC:              { asString = "Letter C (C)";            break; }
            case __C_ENG_TYPE ( Key ) :: KeyD:              { asString = "Letter D (D)";            break; }
            case __C_ENG_TYPE ( Key ) :: KeyE:              { asString = "Letter E (E)";            break; }
            case __C_ENG_TYPE ( Key ) :: KeyF:              { asString = "Letter F (F)";            break; }
            case __C_ENG_TYPE ( Key ) :: KeyG:              { asString = "Letter G (G)";            break; }
            case __C_ENG_TYPE ( Key ) :: KeyH:              { asString = "Letter H (H)";            break; }
            case __C_ENG_TYPE ( Key ) :: KeyI:              { asString = "Letter I (I)";            break; }
            case __C_ENG_TYPE ( Key ) :: KeyJ:              { asString = "Letter J (J)";            break; }
            case __C_ENG_TYPE ( Key ) :: KeyK:              { asString = "Letter K (K)";            break; }
            case __C_ENG_TYPE ( Key ) :: KeyL:              { asString = "Letter L (L)";            break; }
            case __C_ENG_TYPE ( Key ) :: KeyM:              { asString = "Letter M (M)";            break; }
            case __C_ENG_TYPE ( Key ) :: KeyN:              { asString = "Letter N (N)";            break; }
            case __C_ENG_TYPE ( Key ) :: KeyO:              { asString = "Letter O (O)";            break; }
            case __C_ENG_TYPE ( Key ) :: KeyP:              { asString = "Letter P (P)";            break; }
            case __C_ENG_TYPE ( Key ) :: KeyQ:              { asString = "Letter Q (Q)";            break; }
            case __C_ENG_TYPE ( Key ) :: KeyR:              { asString = "Letter R (R)";            break; }
            case __C_ENG_TYPE ( Key ) :: KeyS:              { asString = "Letter S (S)";            break; }
            case __C_ENG_TYPE ( Key ) :: KeyT:              { asString = "Letter T (T)";            break; }
            case __C_ENG_TYPE ( Key ) :: KeyU:              { asString = "Letter U (U)";            break; }
            case __C_ENG_TYPE ( Key ) :: KeyV:              { asString = "Letter V (V)";            break; }
            case __C_ENG_TYPE ( Key ) :: KeyW:              { asString = "Letter W (W)";            break; }
            case __C_ENG_TYPE ( Key ) :: KeyX:              { asString = "Letter X (X)";            break; }
            case __C_ENG_TYPE ( Key ) :: KeyY:              { asString = "Letter Y (Y)";            break; }
            case __C_ENG_TYPE ( Key ) :: KeyZ:              { asString = "Letter Z (Z)";            break; }
            case __C_ENG_TYPE ( Key ) :: KeyLeftBracket:    { asString = "Left Bracket ([)";        break; }
            case __C_ENG_TYPE ( Key ) :: KeyBackslash:      { asString = "Backslash (\\)";          break; } // NOLINT(clion-misra-cpp2008-2-13-1)
            case __C_ENG_TYPE ( Key ) :: KeyRightBracket:   { asString = "Right Bracket (])";       break; }
            case __C_ENG_TYPE ( Key ) :: KeyGraveAccent:    { asString = "Grave Accent (`)";        break; }
            case __C_ENG_TYPE ( Key ) :: KeyWorld1:         { asString = "World 1 (Non-US #)";      break; }
            case __C_ENG_TYPE ( Key ) :: KeyWorld2:         { asString = "World 2 (Non-US #)";      break; }
            case __C_ENG_TYPE ( Key ) :: KeyEscape:         { asString = "Escape";                  break; }
            case __C_ENG_TYPE ( Key ) :: KeyEnter:          { asString = "Enter";                   break; }
            case __C_ENG_TYPE ( Key ) :: KeyTab:            { asString = "Tab";                     break; }
            case __C_ENG_TYPE ( Key ) :: KeyBackspace:      { asString = "Backspace";               break; }
            case __C_ENG_TYPE ( Key ) :: KeyInsert:         { asString = "Insert";                  break; }
            case __C_ENG_TYPE ( Key ) :: KeyDelete:         { asString = "Delete";                  break; }
            case __C_ENG_TYPE ( Key ) :: KeyRight:          { asString = "Right Arrow";             break; }
            case __C_ENG_TYPE ( Key ) :: KeyLeft:           { asString = "Left Arrow";              break; }
            case __C_ENG_TYPE ( Key ) :: KeyDown:           { asString = "Down Arrow";              break; }
            case __C_ENG_TYPE ( Key ) :: KeyUp:             { asString = "Up Arrow";                break; }
            case __C_ENG_TYPE ( Key ) :: KeyPageUp:         { asString = "Page Up";                 break; }
            case __C_ENG_TYPE ( Key ) :: KeyPageDown:       { asString = "Page Down";               break; }
            case __C_ENG_TYPE ( Key ) :: KeyHome:           { asString = "Home";                    break; }
            case __C_ENG_TYPE ( Key ) :: KeyEnd:            { asString = "End";                     break; }
            case __C_ENG_TYPE ( Key ) :: KeyCapsLock:       { asString = "Caps Lock";               break; }
            case __C_ENG_TYPE ( Key ) :: KeyScrollLock:     { asString = "Scroll Lock";             break; }
            case __C_ENG_TYPE ( Key ) :: KeyNumLock:        { asString = "Num Lock";                break; }
            case __C_ENG_TYPE ( Key ) :: KeyPrintScreen:    { asString = "Print Screen";            break; }
            case __C_ENG_TYPE ( Key ) :: KeyPause:          { asString = "Pause";                   break; }
            case __C_ENG_TYPE ( Key ) :: KeyF1:             { asString = "Function Key 1 (F1)";     break; }
            case __C_ENG_TYPE ( Key ) :: KeyF2:             { asString = "Function Key 2 (F2)";     break; }
            case __C_ENG_TYPE ( Key ) :: KeyF3:             { asString = "Function Key 3 (F3)";     break; }
            case __C_ENG_TYPE ( Key ) :: KeyF4:             { asString = "Function Key 4 (F4)";     break; }
            case __C_ENG_TYPE ( Key ) :: KeyF5:             { asString = "Function Key 5 (F5)";     break; }
            case __C_ENG_TYPE ( Key ) :: KeyF6:             { asString = "Function Key 6 (F6)";     break; }
            case __C_ENG_TYPE ( Key ) :: KeyF7:             { asString = "Function Key 7 (F7)";     break; }
            case __C_ENG_TYPE ( Key ) :: KeyF8:             { asString = "Function Key 8 (F8)";     break; }
            case __C_ENG_TYPE ( Key ) :: KeyF9:             { asString = "Function Key 9 (F9)";     break; }
            case __C_ENG_TYPE ( Key ) :: KeyF10:            { asString = "Function Key 10 (F10)";   break; }
            case __C_ENG_TYPE ( Key ) :: KeyF11:            { asString = "Function Key 11 (F11)";   break; }
            case __C_ENG_TYPE ( Key ) :: KeyF12:            { asString = "Function Key 12 (F12)";   break; }
            case __C_ENG_TYPE ( Key ) :: KeyF13:            { asString = "Function Key 13 (F13)";   break; }
            case __C_ENG_TYPE ( Key ) :: KeyF14:            { asString = "Function Key 14 (F14)";   break; }
            case __C_ENG_TYPE ( Key ) :: KeyF15:            { asString = "Function Key 15 (F15)";   break; }
            case __C_ENG_TYPE ( Key ) :: KeyF16:            { asString = "Function Key 16 (F16)";   break; }
            case __C_ENG_TYPE ( Key ) :: KeyF17:            { asString = "Function Key 17 (F17)";   break; }
            case __C_ENG_TYPE ( Key ) :: KeyF18:            { asString = "Function Key 18 (F18)";   break; }
            case __C_ENG_TYPE ( Key ) :: KeyF19:            { asString = "Function Key 19 (F19)";   break; }
            case __C_ENG_TYPE ( Key ) :: KeyF20:            { asString = "Function Key 20 (F20)";   break; }
            case __C_ENG_TYPE ( Key ) :: KeyF21:            { asString = "Function Key 21 (F21)";   break; }
            case __C_ENG_TYPE ( Key ) :: KeyF22:            { asString = "Function Key 22 (F22)";   break; }
            case __C_ENG_TYPE ( Key ) :: KeyF23:            { asString = "Function Key 23 (F23)";   break; }
            case __C_ENG_TYPE ( Key ) :: KeyF24:            { asString = "Function Key 24 (F24)";   break; }
            case __C_ENG_TYPE ( Key ) :: KeyF25:            { asString = "Function Key 25 (F25)";   break; }
            case __C_ENG_TYPE ( Key ) :: KeyKeypad0:        { asString = "Keypad Zero (0)";         break; }
            case __C_ENG_TYPE ( Key ) :: KeyKeypad1:        { asString = "Keypad One (1)";          break; }
            case __C_ENG_TYPE ( Key ) :: KeyKeypad2:        { asString = "Keypad Two (2)";          break; }
            case __C_ENG_TYPE ( Key ) :: KeyKeypad3:        { asString = "Keypad Three (3)";        break; }
            case __C_ENG_TYPE ( Key ) :: KeyKeypad4:        { asString = "Keypad Four (4)";         break; }
            case __C_ENG_TYPE ( Key ) :: KeyKeypad5:        { asString = "Keypad Five (5)";         break; }
            case __C_ENG_TYPE ( Key ) :: KeyKeypad6:        { asString = "Keypad Six (6)";          break; }
            case __C_ENG_TYPE ( Key ) :: KeyKeypad7:        { asString = "Keypad Seven (7)";        break; }
            case __C_ENG_TYPE ( Key ) :: KeyKeypad8:        { asString = "Keypad Eight (8)";        break; }
            case __C_ENG_TYPE ( Key ) :: KeyKeypad9:        { asString = "Keypad Nine (9)";         break; }
            case __C_ENG_TYPE ( Key ) :: KeyKeypadDecimal:  { asString = "Keypad Decimal (.)";      break; }
            case __C_ENG_TYPE ( Key ) :: KeyKeypadDivide:   { asString = "Keypad Divide (/)";       break; }
            case __C_ENG_TYPE ( Key ) :: KeyKeypadMultiply: { asString = "Keypad Multiply (*)";     break; }
            case __C_ENG_TYPE ( Key ) :: KeyKeypadSubtract: { asString = "Keypad Subtract (-)";     break; }
            case __C_ENG_TYPE ( Key ) :: KeyKeypadAdd:      { asString = "Keypad Add (+)";          break; }
            case __C_ENG_TYPE ( Key ) :: KeyKeypadEnter:    { asString = "Keypad Enter";            break; }
            case __C_ENG_TYPE ( Key ) :: KeyKeypadEqual:    { asString = "Keypad Equal (=)";        break; }
            case __C_ENG_TYPE ( Key ) :: KeyLeftShift:      { asString = "Left Shift";              break; }
            case __C_ENG_TYPE ( Key ) :: KeyLeftControl:    { asString = "Left Control";            break; }
            case __C_ENG_TYPE ( Key ) :: KeyLeftAlt:        { asString = "Left Alt";                break; }
            case __C_ENG_TYPE ( Key ) :: KeyLeftSuper:      { asString = "Left Super";              break; }
            case __C_ENG_TYPE ( Key ) :: KeyRightShift:     { asString = "Right Shift";             break; }
            case __C_ENG_TYPE ( Key ) :: KeyRightControl:   { asString = "Right Control";           break; }
            case __C_ENG_TYPE ( Key ) :: KeyRightAlt:       { asString = "Right Alt";               break; }
            case __C_ENG_TYPE ( Key ) :: KeyRightSuper:     { asString = "Right Super";             break; }
            case __C_ENG_TYPE ( Key ) :: KeyMenu:           { asString = "Menu";                    break; }
        }

        return asString;
    }

    __C_ENG_NO_DISCARD auto toString (
            __C_ENG_TYPE ( MouseButton ) mouseButton
    ) noexcept -> StringLiteral {

        StringLiteral asString = "";

        switch ( mouseButton ) {
            case __C_ENG_TYPE ( MouseButton ) :: MouseButton1:          { asString = "Mouse Button 1 ( Left Click )";   break; }
            case __C_ENG_TYPE ( MouseButton ) :: MouseButton2:          { asString = "Mouse Button 2 ( Right Click )";  break; }
            case __C_ENG_TYPE ( MouseButton ) :: MouseButton3:          { asString = "Mouse Button 3 ( Middle Click )"; break; }
            case __C_ENG_TYPE ( MouseButton ) :: MouseButton4:          { asString = "Mouse Button 4";                  break; }
            case __C_ENG_TYPE ( MouseButton ) :: MouseButton5:          { asString = "Mouse Button 5";                  break; }
            case __C_ENG_TYPE ( MouseButton ) :: MouseButton6:          { asString = "Mouse Button 6";                  break; }
            case __C_ENG_TYPE ( MouseButton ) :: MouseButton7:          { asString = "Mouse Button 7";                  break; }
            case __C_ENG_TYPE ( MouseButton ) :: MouseButton8:          { asString = "Mouse Button 8";                  break; }
            case __C_ENG_TYPE ( MouseButton ) :: MouseButtonUndefined:  { asString = "Undefined Mouse Button";          break; }
        }

        return asString;
    }

    __C_ENG_NO_DISCARD auto toString (
            __C_ENG_TYPE ( WindowType ) type
    ) noexcept -> StringLiteral {

        StringLiteral asString = "";

        switch ( type ) {
            case __C_ENG_TYPE ( WindowType ) :: WindowTypeWindowed:            { asString = "Windowed";            break; }
            case __C_ENG_TYPE ( WindowType ) :: WindowTypeFullscreen:          { asString = "Fullscreen";          break; }
            case __C_ENG_TYPE ( WindowType ) :: WindowTypeWindowedFullscreen:  { asString = "Windowed Fullscreen"; break; }
        }

        return asString;
    }

    __C_ENG_NO_DISCARD auto toString (
            __C_ENG_TYPE ( WindowFlag ) flag
    ) noexcept -> StringLiteral {

        StringLiteral asString = "";

        switch ( flag ) {
            case __C_ENG_TYPE ( WindowFlag ) :: WindowFlagNone:                    { asString = "No Flag";                                 break; }
            case __C_ENG_TYPE ( WindowFlag ) :: WindowFlagResizable:               { asString = "Is Resizable";                            break; }
            case __C_ENG_TYPE ( WindowFlag ) :: WindowFlagBorderless:              { asString = "Borderless Window, Undecorated";          break; }
            case __C_ENG_TYPE ( WindowFlag ) :: WindowFlagStartMinimized:          { asString = "Start Minimized";                         break; }
            case __C_ENG_TYPE ( WindowFlag ) :: WindowFlagGrabFocusOnOpen:         { asString = "Grab Input Focus on Open";                break; }
            case __C_ENG_TYPE ( WindowFlag ) :: WindowFlagRestorePreviousMode:     { asString = "Fullscreen Restore Video Mode on Focus";  break; }
            case __C_ENG_TYPE ( WindowFlag ) :: WindowFlagStayOnTop:               { asString = "Force On Top";                            break; }
            case __C_ENG_TYPE ( WindowFlag ) :: WindowFlagStartMaximized:          { asString = "Start Window Maximized";                  break; }
            case __C_ENG_TYPE ( WindowFlag ) :: WindowFlagCenterCursorOnCreate:    { asString = "Center Mouse Cursor on Create";           break; }
            case __C_ENG_TYPE ( WindowFlag ) :: WindowFlagTransparentFramebuffer:  { asString = "Transparent Framebuffer";                 break; }
            case __C_ENG_TYPE ( WindowFlag ) :: WindowFlagGrabFocusOnRaise:        { asString = "Grab Input Focus On Raise";               break; }
            case __C_ENG_TYPE ( WindowFlag ) :: WindowFlagScaleToMonitor:          { asString = "Scale Content to Monitor Content Scale";  break; }
        }

        return asString;
    }

    __C_ENG_NO_DISCARD auto toString (
            __C_ENG_TYPE ( ControllerHatState ) state
    ) noexcept -> StringLiteral {

        StringLiteral asString = "";

        switch ( state ) {
            case __C_ENG_TYPE ( ControllerHatState ) :: ControllerHatStateCentered:    { asString = "ControllerHatCentered";   break; }
            case __C_ENG_TYPE ( ControllerHatState ) :: ControllerHatStateUp:          { asString = "ControllerHatUp";         break; }
            case __C_ENG_TYPE ( ControllerHatState ) :: ControllerHatStateLeft:        { asString = "ControllerHatLeft";       break; }
            case __C_ENG_TYPE ( ControllerHatState ) :: ControllerHatStateRight:       { asString = "ControllerHatRight";      break; }
            case __C_ENG_TYPE ( ControllerHatState ) :: ControllerHatStateDown:        { asString = "ControllerHatDown";       break; }
            case __C_ENG_TYPE ( ControllerHatState ) :: ControllerHatStateLeftUp:      { asString = "ControllerHatLeftUp";     break; }
            case __C_ENG_TYPE ( ControllerHatState ) :: ControllerHatStateLeftDown:    { asString = "ControllerHatLeftDown";   break; }
            case __C_ENG_TYPE ( ControllerHatState ) :: ControllerHatStateRightUp:     { asString = "ControllerHatRightUp";    break; }
            case __C_ENG_TYPE ( ControllerHatState ) :: ControllerHatStateRightDown:   { asString = "ControllerHatRightDown";  break; }
        }

        return asString;
    }

    __C_ENG_NO_DISCARD auto toString (
            __C_ENG_TYPE ( CompareResult ) result
    ) noexcept -> StringLiteral {

        StringLiteral asString = "";

        switch ( result ) {
            case __C_ENG_TYPE ( CompareResult ) :: CompareResultLess:     { asString = "Less";    break; }
            case __C_ENG_TYPE ( CompareResult ) :: CompareResultEquals:   { asString = "Equals";  break; }
            case __C_ENG_TYPE ( CompareResult ) :: CompareResultGreater:  { asString = "Greater"; break; }
        }

        return asString;
    }

    __C_ENG_NO_DISCARD auto toString (
            __C_ENG_TYPE ( RenderAPIType ) result
    ) noexcept -> StringLiteral {

        StringLiteral asString = "";

        switch ( result ) {
            case __C_ENG_TYPE ( RenderAPIType ) :: RenderAPITypeNone:     { asString = "Unknown/No Render API";     break; }
            case __C_ENG_TYPE ( RenderAPIType ) :: RenderAPITypeVulkan:   { asString = "Vulkan Render API";         break; }
        }

        return asString;
    }


    __C_ENG_NO_DISCARD auto toString (
            __C_ENG_TYPE ( Position ) const & position
    ) noexcept -> String {

        return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( Position ) ) " "
               "{ x = "_s   + position.x +
               ", y = "     + position.y +
               " }";
    }

    __C_ENG_NO_DISCARD auto toString (
            __C_ENG_TYPE ( Size ) const & size
    ) noexcept -> String {

        return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( Size ) ) " "
               "{ width = "_s   + size.width +
               ", height = "    + size.height +
               " }";
    }

    __C_ENG_NO_DISCARD auto toString (
            __C_ENG_TYPE ( ColorChannelsDepth ) const & depth
    ) noexcept -> String {

        return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( ColorChannelsDepth ) ) " "
               "{ red = "_s + depth.red +
               ", green = " + depth.green +
               ", blue = "  + depth.blue +
               " }";
    }

    __C_ENG_NO_DISCARD auto toString (
            __C_ENG_TYPE ( MonitorVideoModeProperties ) const & properties
    ) noexcept -> String {

        return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( MonitorVideoModeProperties ) ) " "
               "{ size = "                  + toString ( properties.size ) +
               ", colorChannelsDepth = "    + toString ( properties.colorChannelsDepth ) +
               ", refreshRate = "           + properties.refreshRate + "Hz"
                                                                       " }";
    }

    __C_ENG_NO_DISCARD auto toString (
            __C_ENG_TYPE ( ContentScale ) const & scale
    ) noexcept -> String {

        return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( ContentScale ) ) " "
               "{ x = "_s   + scale.x +
               ", y = "     + scale.y +
               " }";
    }

    __C_ENG_NO_DISCARD auto toString (
            __C_ENG_TYPE ( MonitorGammaRamp ) const & ramp
    ) noexcept -> String {

        auto rampToString = [ size = ramp.size ]( __C_ENG_TYPE ( MonitorGammaRampValue ) ramp ) noexcept -> String {
            String asString;
            for ( uint32 i = 0U; i < size; ++ i ) {
                asString += ramp [ i ] + ", "_s;
            }

            return asString.removeSuffix(", ");
        };

        return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( MonitorGammaRamp ) ) " "
               "{ size = "_s    + ramp.size +
               ", red = "       + rampToString ( ramp.red ) +
               ", green = "     + rampToString ( ramp.green ) +
               ", blue = "      + rampToString ( ramp.blue ) +
               " }";
    }

    __C_ENG_NO_DISCARD auto toString (
            __C_ENG_TYPE ( MonitorWorkArea ) const & area
    ) noexcept -> String {

        return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( MonitorWorkArea ) ) " "
               "{ position = "  + toString ( area.position ) +
               ", size = "      + toString ( area.size ) +
               " }";
    }

    __C_ENG_NO_DISCARD auto toString (
            __C_ENG_TYPE ( MonitorProperties ) const & properties
    ) noexcept -> String {

        return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( MonitorProperties ) ) " "
               "{ name = "_s            + properties.name +
               ", physicalSize = "      + toString ( properties.physicalSizeMM ) +
               ", contentScale = "      + toString ( properties.contentScale ) +
               ", workArea = "          + toString ( properties.workArea ) +
               ", gammaRamp = "         + toString ( properties.gammaRamp ) +
               ", activeVideoMode = "   + toString ( properties.activeVideoMode ) +
               " }";
    }

    __C_ENG_NO_DISCARD auto toString (
            __C_ENG_TYPE ( RenderInstanceSurfaceAttachData ) const & callbackData
    ) noexcept -> String {

        return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( RenderInstanceSurfaceAttachData ) ) " "
               "{ renderAPIType = "_s   + toString ( callbackData.renderAPIType ) +
               ", pAPIData = "          + toString ( callbackData.pAPIData ) +
               ", surfaceHandle = "     + toString ( callbackData.pSurfaceHandle ) +
               ", pUserData = "         + toString ( callbackData.pUserData ) +
               " }";
    }

    __C_ENG_NO_DISCARD auto toString (
            __C_ENG_TYPE ( RenderInstanceSurfaceDetachData ) const & callbackData
    ) noexcept -> String {

        return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( RenderInstanceSurfaceDetachData ) ) " "
               "{ renderAPIType = "_s   + toString ( callbackData.renderAPIType ) +
               ", pAPIData = "          + toString ( callbackData.pAPIData ) +
               ", surfaceHandle = "     + toString ( callbackData.pSurfaceHandle ) +
               ", pUserData = "         + toString ( callbackData.pUserData ) +
               " }";
    }

    __C_ENG_NO_DISCARD auto toString (
            __C_ENG_TYPE ( RenderInstanceSurfaceCallbackInfo ) const & callbackData
    ) noexcept -> String {

        return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( RenderInstanceSurfaceAttachCallbackInfo ) ) " "
               "{ attachCallback = "_s  + toString ( callbackData.attachCallback ) +
               ", detachCallback = "    + toString ( callbackData.detachCallback ) +
               ", pUserData = "         + toString ( callbackData.pUserData ) +
               " }";
    }


    __C_ENG_NO_DISCARD auto keyModifiersToString (
            __C_ENG_TYPE ( KeyModifiers ) modifiers
    ) noexcept -> String {

        String asString = "";

        for ( uint32 f = 0x01U; true; f <<= 1 ) { // NOLINT(clion-misra-cpp2008-6-5-1)
            if ( ( f & modifiers ) != 0U ) {
                asString += toString ( static_cast < __C_ENG_TYPE ( KeyModifier ) > ( f ) ) + ", "_s;
            }

            if ( f == __C_ENG_TYPE ( KeyModifier ) :: KeyModifierMaxValue ) {
                break;
            }
        }

        return asString.removeSuffix(", ");
    }

    __C_ENG_NO_DISCARD auto windowFlagsToString (
            __C_ENG_TYPE ( WindowFlags ) modifiers
    ) noexcept -> String {

        String asString = "";

        for ( uint32 f = 0x01U; true; f <<= 1 ) { // NOLINT(clion-misra-cpp2008-6-5-1)
            if ( ( f & modifiers ) != 0U ) {
                asString += toString ( static_cast < __C_ENG_TYPE ( KeyModifier ) > ( f ) ) + ", "_s;
            }

            if ( f == __C_ENG_TYPE ( WindowFlag ) :: WindowFlagMaxValue ) {
                break;
            }
        }

        return asString.removeSuffix(", ");
    }

    auto toString (
            Type ( ComponentTypeFlag )  flag
    ) noexcept -> StringLiteral {

        switch ( flag ) {
            case ComponentTypeFlagNone:         return "None";
            case ComponentTypeFlagTransform:    return "Transform";
            case ComponentTypeFlagMesh:         return "Mesh";
            case ComponentTypeFlagMeshRenderer: return "MeshRenderer";
            case ComponentTypeFlagCustom:       return "Custom";
        }

        return "Unknown";
    }

    auto toString (
            Type ( SceneLoaderState ) state
    ) noexcept -> StringLiteral {

        switch ( state ) {
            case SceneLoaderStateIdle:          return "Idle";
            case SceneLoaderStateLoading:       return "Loading";
            case SceneLoaderStateSceneReady:    return "SceneReady";
        }

        return "Unknown";
    }

    auto stringToComponentTypeFlag ( StringLiteral component ) noexcept -> Type ( ComponentTypeFlag ) {

        if ( std :: strcmp ( component, "Transform" ) == 0 )    { return ComponentTypeFlagTransform; }
        if ( std :: strcmp ( component, "Mesh" ) == 0 )         { return ComponentTypeFlagMesh; }
        if ( std :: strcmp ( component, "MeshRenderer" ) == 0 ) { return ComponentTypeFlagMeshRenderer; }
        if ( std :: strcmp ( component, "Custom" ) == 0 )       { return ComponentTypeFlagCustom; }

        return ComponentTypeFlagCustom;
    }

}

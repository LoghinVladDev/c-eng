//
// Created by loghin on 23.05.2021.
//

#ifndef C_ENG_VKEYEVENT_HPP
#define C_ENG_VKEYEVENT_HPP

#include <VEvent.hpp>
#include <CDS/LinkedList>

namespace engine {

    class __CDS_MaybeUnused VKeyEvent : public VEvent {
    private:
        //// private variables

        //// private functions

    public:
        //// public variables
        enum VKey : uint16 {
            VKEY_UNKNOWN        = 0x0000u,

            VKEY_SPACE          = 0x0020u,
            VKEY_APOSTROPHE     = 0x0027u,
            VKEY_COMMA          = 0x002Cu,
            VKEY_MINUS          = 0x002Du,
            VKEY_PERIOD         = 0x002Eu,
            VKEY_SLASH          = 0x002Fu,

            VKEY_0              = 0x0030u,
            VKEY_1              = 0x0031u,
            VKEY_2              = 0x0032u,
            VKEY_3              = 0x0033u,
            VKEY_4              = 0x0034u,
            VKEY_5              = 0x0035u,
            VKEY_6              = 0x0036u,
            VKEY_7              = 0x0037u,
            VKEY_8              = 0x0038u,
            VKEY_9              = 0x0039u,

            VKEY_SEMICOLON      = 0x003Bu,
            VKEY_EQUAL          = 0x003Du,

            VKEY_A              = 0x0041u,
            VKEY_B              = 0x0042u,
            VKEY_C              = 0x0043u,
            VKEY_D              = 0x0044u,
            VKEY_E              = 0x0045u,
            VKEY_F              = 0x0046u,
            VKEY_G              = 0x0047u,
            VKEY_H              = 0x0048u,
            VKEY_I              = 0x0049u,
            VKEY_J              = 0x004Au,
            VKEY_K              = 0x004Bu,
            VKEY_L              = 0x004Cu,
            VKEY_M              = 0x004Du,
            VKEY_N              = 0x004Eu,
            VKEY_O              = 0x004Fu,
            VKEY_P              = 0x0050u,
            VKEY_Q              = 0x0051u,
            VKEY_R              = 0x0052u,
            VKEY_S              = 0x0053u,
            VKEY_T              = 0x0054u,
            VKEY_U              = 0x0055u,
            VKEY_V              = 0x0056u,
            VKEY_W              = 0x0057u,
            VKEY_X              = 0x0058u,
            VKEY_Y              = 0x0059u,
            VKEY_Z              = 0x005Au,

            VKEY_LEFT_BRACKET   = 0x005Bu,
            VKEY_BACKSLASH      = 0x005Cu,
            VKEY_RIGHT_BRACKET  = 0x005Du,

            VKEY_GRAVE_ACCENT   = 0x0060u,

            VKEY_WORLD_1        = 0x00A1u,
            VKEY_WORLD_2        = 0x00A2u,

            VKEY_ESCAPE         = 0x0100u,
            VKEY_ENTER          = 0x0101u,
            VKEY_TAB            = 0x0102u,
            VKEY_BACKSPACE      = 0x0103u,
            VKEY_INSERT         = 0x0104u,
            VKEY_DELETE         = 0x0105u,
            VKEY_RIGHT          = 0x0106u,
            VKEY_LEFT           = 0x0107u,
            VKEY_DOWN           = 0x0108u,
            VKEY_UP             = 0x0109u,
            VKEY_PAGE_UP        = 0x010Au,
            VKEY_PAGE_DOWN      = 0x010Bu,
            VKEY_HOME           = 0x010Cu,
            VKEY_END            = 0x010Du,

            VKEY_CAPS_LOCK      = 0x0118u,
            VKEY_SCROLL_LOCK    = 0x0119u,
            VKEY_NUM_LOCK       = 0x011Au,
            VKEY_PRINT_SCREEN   = 0x011Bu,
            VKEY_PAUSE          = 0x011Cu,

            VKEY_F1             = 0x0122u,
            VKEY_F2             = 0x0123u,
            VKEY_F3             = 0x0124u,
            VKEY_F4             = 0x0125u,
            VKEY_F5             = 0x0126u,
            VKEY_F6             = 0x0127u,
            VKEY_F7             = 0x0128u,
            VKEY_F8             = 0x0129u,
            VKEY_F9             = 0x012Au,
            VKEY_F10            = 0x012Bu,
            VKEY_F11            = 0x012Cu,
            VKEY_F12            = 0x012Du,
            VKEY_F13            = 0x012Eu,
            VKEY_F14            = 0x012Fu,
            VKEY_F15            = 0x0130u,
            VKEY_F16            = 0x0131u,
            VKEY_F17            = 0x0132u,
            VKEY_F18            = 0x0133u,
            VKEY_F19            = 0x0134u,
            VKEY_F20            = 0x0135u,
            VKEY_F21            = 0x0136u,
            VKEY_F22            = 0x0137u,
            VKEY_F23            = 0x0138u,
            VKEY_F24            = 0x0139u,
            VKEY_F25            = 0x013Au,

            VKEY_NUM_0          = 0x0140u,
            VKEY_NUM_1          = 0x0141u,
            VKEY_NUM_2          = 0x0142u,
            VKEY_NUM_3          = 0x0143u,
            VKEY_NUM_4          = 0x0144u,
            VKEY_NUM_5          = 0x0145u,
            VKEY_NUM_6          = 0x0146u,
            VKEY_NUM_7          = 0x0147u,
            VKEY_NUM_8          = 0x0148u,
            VKEY_NUM_9          = 0x0149u,

            VKEY_NUM_DECIMAL    = 0x014Au,
            VKEY_NUM_DIVIDE     = 0x014Bu,
            VKEY_NUM_MULTIPLY   = 0x014Cu,
            VKEY_NUM_SUBTRACT   = 0x014Du,
            VKEY_NUM_ADD        = 0x014Eu,
            VKEY_NUM_ENTER      = 0x014Fu,
            VKEY_NUM_EQUAL      = 0x0150u,

            VKEY_LEFT_SHIFT     = 0x0154u,
            VKEY_LEFT_CONTROL   = 0x0155u,
            VKEY_LEFT_ALT       = 0x0156u,
            VKEY_LEFT_SUPER     = 0x0157u,
            VKEY_RIGHT_SHIFT    = 0x0158u,
            VKEY_RIGHT_CONTROL  = 0x0159u,
            VKEY_RIGHT_ALT      = 0x015Au,
            VKEY_RIGHT_SUPER    = 0x015Bu,
            VKEY_MENU           = 0x015Cu
        };

        enum VKeyModifierFlag : uint8 {
            VKEY_MODIFIER_NONE      = 0x00,
            VKEY_MODIFIER_SHIFT     = 0x01,
            VKEY_MODIFIER_CONTROL   = 0x02,
            VKEY_MODIFIER_ALT       = 0x04,
            VKEY_MODIFIER_SUPER     = 0x08,
            VKEY_MODIFIER_CAPS_LOCK = 0x10,
            VKEY_MODIFIER_NUM_LOCK  = 0x20
        };

        enum VKeyAction : uint8 {
            VKEY_ACTION_NONE    = 0x00,
            VKEY_ACTION_PRESS   = 0x01,
            VKEY_ACTION_RELEASE = 0x02
        };

        using VKeyModifiers = uint8;

        //// public functions

        [[nodiscard]] constexpr static auto toString(VKey key) noexcept -> StringLiteral {
            switch (key) {
                case VKEY_UNKNOWN:          return "Key Unknown";
                case VKEY_SPACE:            return "Space ( )";
                case VKEY_APOSTROPHE:       return "Apostrophe (')";
                case VKEY_COMMA:            return "Comma (,)";
                case VKEY_MINUS:            return "Minus (-)";
                case VKEY_PERIOD:           return "Period (.)";
                case VKEY_SLASH:            return "Slash (/)";
                case VKEY_0:                return "Zero (0)";
                case VKEY_1:                return "One (1)";
                case VKEY_2:                return "Two (2)";
                case VKEY_3:                return "Three (3)";
                case VKEY_4:                return "Four (4)";
                case VKEY_5:                return "Five (5)";
                case VKEY_6:                return "Six (6)";
                case VKEY_7:                return "Seven (7)";
                case VKEY_8:                return "Eight (8)";
                case VKEY_9:                return "Nine (9)";
                case VKEY_SEMICOLON:        return "Semicolon (;)";
                case VKEY_EQUAL:            return "Equal (=)";
                case VKEY_A:                return "Letter A (A)";
                case VKEY_B:                return "Letter B (B)";
                case VKEY_C:                return "Letter C (C)";
                case VKEY_D:                return "Letter D (D)";
                case VKEY_E:                return "Letter E (E)";
                case VKEY_F:                return "Letter F (F)";
                case VKEY_G:                return "Letter G (G)";
                case VKEY_H:                return "Letter H (H)";
                case VKEY_I:                return "Letter I (I)";
                case VKEY_J:                return "Letter J (J)";
                case VKEY_K:                return "Letter K (K)";
                case VKEY_L:                return "Letter L (L)";
                case VKEY_M:                return "Letter M (M)";
                case VKEY_N:                return "Letter N (N)";
                case VKEY_O:                return "Letter O (O)";
                case VKEY_P:                return "Letter P (P)";
                case VKEY_Q:                return "Letter Q (Q)";
                case VKEY_R:                return "Letter R (R)";
                case VKEY_S:                return "Letter S (S)";
                case VKEY_T:                return "Letter T (T)";
                case VKEY_U:                return "Letter U (U)";
                case VKEY_V:                return "Letter V (V)";
                case VKEY_W:                return "Letter W (W)";
                case VKEY_X:                return "Letter X (X)";
                case VKEY_Y:                return "Letter Y (Y)";
                case VKEY_Z:                return "Letter Z (Z)";
                case VKEY_LEFT_BRACKET:     return "Left Bracket ([)";
                case VKEY_BACKSLASH:        return "Backslash (\\)";
                case VKEY_RIGHT_BRACKET:    return "Right Bracket (])";
                case VKEY_GRAVE_ACCENT:     return "Grave Accent (`)";
                case VKEY_WORLD_1:          return "World 1 (Non-US #)";
                case VKEY_WORLD_2:          return "World 2 (Non-US #)";
                case VKEY_ESCAPE:           return "Escape";
                case VKEY_ENTER:            return "Enter";
                case VKEY_TAB:              return "Tab";
                case VKEY_BACKSPACE:        return "Backspace";
                case VKEY_INSERT:           return "Insert";
                case VKEY_DELETE:           return "Delete";
                case VKEY_RIGHT:            return "Right Arrow";
                case VKEY_LEFT:             return "Left Arrow";
                case VKEY_DOWN:             return "Down Arrow";
                case VKEY_UP:               return "Up Arrow";
                case VKEY_PAGE_UP:          return "Page Up";
                case VKEY_PAGE_DOWN:        return "Page Down";
                case VKEY_HOME:             return "Home";
                case VKEY_END:              return "End";
                case VKEY_CAPS_LOCK:        return "Caps Lock";
                case VKEY_SCROLL_LOCK:      return "Scroll Lock";
                case VKEY_NUM_LOCK:         return "Num Lock";
                case VKEY_PRINT_SCREEN:     return "Print Screen";
                case VKEY_PAUSE:            return "Pause";
                case VKEY_F1:               return "F1";
                case VKEY_F2:               return "F2";
                case VKEY_F3:               return "F3";
                case VKEY_F4:               return "F4";
                case VKEY_F5:               return "F5";
                case VKEY_F6:               return "F6";
                case VKEY_F7:               return "F7";
                case VKEY_F8:               return "F8";
                case VKEY_F9:               return "F9";
                case VKEY_F10:              return "F10";
                case VKEY_F11:              return "F11";
                case VKEY_F12:              return "F12";
                case VKEY_F13:              return "F13";
                case VKEY_F14:              return "F14";
                case VKEY_F15:              return "F15";
                case VKEY_F16:              return "F16";
                case VKEY_F17:              return "F17";
                case VKEY_F18:              return "F18";
                case VKEY_F19:              return "F19";
                case VKEY_F20:              return "F20";
                case VKEY_F21:              return "F21";
                case VKEY_F22:              return "F22";
                case VKEY_F23:              return "F23";
                case VKEY_F24:              return "F24";
                case VKEY_F25:              return "F25";
                case VKEY_NUM_0:            return "Numpad 0 (0)";
                case VKEY_NUM_1:            return "Numpad 1 (1)";
                case VKEY_NUM_2:            return "Numpad 2 (2)";
                case VKEY_NUM_3:            return "Numpad 3 (3)";
                case VKEY_NUM_4:            return "Numpad 4 (4)";
                case VKEY_NUM_5:            return "Numpad 5 (5)";
                case VKEY_NUM_6:            return "Numpad 6 (6)";
                case VKEY_NUM_7:            return "Numpad 7 (7)";
                case VKEY_NUM_8:            return "Numpad 8 (8)";
                case VKEY_NUM_9:            return "Numpad 9 (9)";
                case VKEY_NUM_DECIMAL:      return "Numpad Decimal (.)";
                case VKEY_NUM_DIVIDE:       return "Numpad Divide (/)";
                case VKEY_NUM_MULTIPLY:     return "Numpad Multiply (*)";
                case VKEY_NUM_SUBTRACT:     return "Numpad Subtract (-)";
                case VKEY_NUM_ADD:          return "Numpad Add (+)";
                case VKEY_NUM_ENTER:        return "Numpad Enter";
                case VKEY_NUM_EQUAL:        return "Numpad Equal (=)";
                case VKEY_LEFT_SHIFT:       return "Left Shift";
                case VKEY_LEFT_CONTROL:     return "Left Control";
                case VKEY_LEFT_ALT:         return "Left Alt";
                case VKEY_LEFT_SUPER:       return "Left Super";
                case VKEY_RIGHT_SHIFT:      return "Right Shift";
                case VKEY_RIGHT_CONTROL:    return "Right Control";
                case VKEY_RIGHT_ALT:        return "Right Alt";
                case VKEY_RIGHT_SUPER:      return "Right Super";
                case VKEY_MENU:             return "Menu";
            }

            return "Unknown";
        }

        [[nodiscard]] constexpr static auto toString (VKeyModifierFlag flag) noexcept -> StringLiteral {
            switch (flag) {
                case VKEY_MODIFIER_NONE:        return "None";
                case VKEY_MODIFIER_SHIFT:       return "Shift";
                case VKEY_MODIFIER_CONTROL:     return "Control";
                case VKEY_MODIFIER_ALT:         return "Alt";
                case VKEY_MODIFIER_SUPER:       return "Super";
                case VKEY_MODIFIER_CAPS_LOCK:   return "Caps Lock";
                case VKEY_MODIFIER_NUM_LOCK:    return "Num Lock";
            }

            return "None";
        }

        [[nodiscard]] constexpr static auto toString (VKeyAction action) noexcept -> StringLiteral {
            switch (action) {
                case VKEY_ACTION_NONE:      return "None";
                case VKEY_ACTION_PRESS:     return "Pressed";
                case VKEY_ACTION_RELEASE:   return "Released";
            }

            return "Unknown";
        }

        [[nodiscard]] static auto toString (VKeyModifiers flags) noexcept -> String {
            LinkedList < VKeyModifierFlag > flagsIn;

            for ( uint8 i = 1; i <= 0x20; i <<= 1 )
                if ( flags & i )
                    flagsIn.append(static_cast<VKeyModifierFlag>(i));

            return flagsIn.toString();
        }

        [[nodiscard]] constexpr auto key () const noexcept -> VKey { return this->_key; }
        [[nodiscard]] constexpr auto modifiers () const noexcept -> VKeyModifiers { return this->_modifiers; }
        [[nodiscard]] constexpr auto action () const noexcept -> VKeyAction { return this->_action; }

        [[nodiscard]] constexpr auto key () noexcept -> VKey & { return this->_key; }
        [[nodiscard]] constexpr auto modifiers () noexcept -> VKeyModifiers & { return this->_modifiers; }
        [[nodiscard]] constexpr auto action () noexcept -> VKeyAction & { return this->_action; }

        [[nodiscard]] auto toString () const noexcept -> String override {
            return String ("VKeyEvent { ") +
                "key = " + toString(this->_key) +
                ", modifiers = " + toString(this->_modifiers) +
                ", action = " + toString(this->_action) +
                ", base = " + VEvent::toString() +" }";
        }

        [[nodiscard]] auto hash () const noexcept -> Index override {
            return (((dataTypes::hash(static_cast<uint16>(this->_key)) << 8) | dataTypes::hash(static_cast<uint8>(this->_modifiers))) << 24) | VEvent::hash();
        }

        [[nodiscard]] auto copy () const noexcept -> VKeyEvent * override {
            return new VKeyEvent (* this);
        }

        [[nodiscard]] inline auto operator == (VKeyEvent const & o) const noexcept -> bool {
            if ( this == & o ) return true;

            return
                    VEvent::operator==(o) &&
                    this->_key == o._key &&
                    this->_modifiers == o._modifiers;
        }

        [[nodiscard]] auto equals (Object const & o) const noexcept -> bool override {
            if ( this == & o ) return true;
            auto p = dynamic_cast < decltype (this) > (& o);
            if ( p == nullptr ) return false;
            return this->operator==(*p);
        }

        VKeyEvent () noexcept : VEvent (VEvent::Type::VEVENT_KEY) { }
        VKeyEvent (VKeyEvent const &) noexcept = default;
        VKeyEvent (VKeyEvent && o) noexcept :
                VEvent ((VEvent&&)o),
                _key(std::exchange(o._key, VKey::VKEY_UNKNOWN)),
                _modifiers(std::exchange(o._modifiers, VKeyModifierFlag::VKEY_MODIFIER_NONE)),
                _action(std::exchange(o._action, VKeyAction::VKEY_ACTION_NONE)) {

        }

        ~VKeyEvent () noexcept override = default;

    private:
        VKey            _key        {VKey::VKEY_UNKNOWN};
        VKeyModifiers   _modifiers  {VKeyModifierFlag::VKEY_MODIFIER_NONE};
        VKeyAction      _action     {VKeyAction::VKEY_ACTION_NONE};
    };

}

#endif //C_ENG_VKEYEVENT_HPP

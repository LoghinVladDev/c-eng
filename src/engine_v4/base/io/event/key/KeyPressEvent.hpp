//
// Created by loghin on 20.12.2021.
//

#ifndef __C_ENG_KEY_PRESS_EVENT_HPP__
#define __C_ENG_KEY_PRESS_EVENT_HPP__


#include <base/io/event/key/KeyEvent.hpp>

namespace engine::io {

    class KeyPressEvent : public KeyEvent {
    public:
        KeyPressEvent (
                Window      const * pWindow,
                KeyType             key,
                KeyModifierFlags    modifierFlags
        ) noexcept;

        ~KeyPressEvent () noexcept override = default;

        __CDS_NoDiscard constexpr auto className () const noexcept -> cds::StringView override {
            return "KeyPressEvent";
        }

        __CDS_NoDiscard constexpr auto typeFlags () const noexcept -> TypeFlags override {
            return
                    TypeFlagBits::KeyEventBit   |
                    TypeFlagBits::PressEventBit ;
        }
    };

}


#endif //__C_ENG_KEY_PRESS_EVENT_HPP__

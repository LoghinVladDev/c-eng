//
// Created by loghin on 20.12.2021.
//

#ifndef __C_ENG_KEY_EVENT_HPP__
#define __C_ENG_KEY_EVENT_HPP__

#include <base/io/event/Event.hpp>
#include <base/core/Core.hpp>

namespace engine::io {
    class Window;
}

namespace engine::io {

    class KeyEvent : public Event {
    private:
        KeyType             _key            {KeyUnknown};
        KeyModifierFlags    _modifierFlags  {KeyModifierNone};

    protected:
        KeyEvent (
                Window      const * pWindow,
                KeyType             key,
                KeyModifierFlags    modifierFlags
        ) noexcept;

    public:
        __CDS_NoDiscard constexpr auto key () const noexcept -> KeyType {
            return this->_key;
        }

        __CDS_NoDiscard constexpr auto modifierFlags () const noexcept -> KeyModifierFlags {
            return this->_modifierFlags;
        }

        ~KeyEvent () noexcept override = default;

        __CDS_NoDiscard constexpr auto className () const noexcept -> cds::StringView override {
            return "KeyEvent";
        }

        __CDS_NoDiscard constexpr auto typeFlags () const noexcept -> TypeFlags override {
            return
                    TypeFlagBits::CustomEventBit    |
                    TypeFlagBits::KeyEventBit       ;
        }
    };

}


#endif //__C_ENG_KEY_EVENT_HPP__

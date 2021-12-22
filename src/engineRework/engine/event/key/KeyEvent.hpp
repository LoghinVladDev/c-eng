//
// Created by loghin on 20.12.2021.
//

#ifndef C_ENG_KEYEVENT_HPP
#define C_ENG_KEYEVENT_HPP

#include <Event.hpp>

namespace engine {

    class C_ENG_CLASS ( KeyEvent ) : public C_ENG_CLASS ( Event ) {

        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( Key, key, Key :: KeyUnknown )
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( KeyModifiers, modifiers, KeyModifier :: KeyModifierNone )

    protected:
        C_ENG_CONSTRUCTOR ( KeyEvent ) (
                C_ENG_TYPE ( Window ) * window,
                Key                     key,
                KeyModifiers            modifiers
        ) noexcept :
                C_ENG_CONSTRUCTOR ( Event ) ( window ),
                _key ( key ),
                _modifiers ( modifiers ) {

        }

    public:
        C_ENG_DESTRUCTOR ( KeyEvent ) () noexcept override = default;

        C_ENG_NO_DISCARD constexpr auto type () const noexcept -> EventType override {
            return EventType :: EventTypeCustomKeyEvent;
        }
    };

}


#endif //C_ENG_KEYEVENT_HPP

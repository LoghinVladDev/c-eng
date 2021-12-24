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

        C_ENG_NO_DISCARD auto copy () const noexcept -> C_ENG_TYPE ( KeyEvent ) * override = 0;

        C_ENG_NO_DISCARD inline auto hash () const noexcept -> cds :: Index override {
            return
                ( static_cast < cds :: Index > ( this->key() ) );
        }

        C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
        C_ENG_NO_DISCARD auto equals ( cds :: Object const & ) const noexcept -> bool override;
    };

}


#endif //C_ENG_KEYEVENT_HPP

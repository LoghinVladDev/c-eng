//
// Created by loghin on 20.12.2021.
//

#ifndef C_ENG_MOUSEPRESSEVENT_HPP
#define C_ENG_MOUSEPRESSEVENT_HPP

#include <MouseEvent.hpp>

namespace engine {

    class C_ENG_CLASS ( MousePressEvent ) : public C_ENG_CLASS ( MouseEvent ) {
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( MouseButton, button, MouseButton :: MouseButtonUndefined )
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( KeyModifiers, modifiers, KeyModifier :: KeyModifierNone )

    public:
        C_ENG_DESTRUCTOR ( MousePressEvent ) () noexcept override = default;

        C_ENG_CONSTRUCTOR ( MousePressEvent ) (
                C_ENG_TYPE ( Window ) * window,
                Position        const & position,
                MouseButton             button,
                KeyModifiers            modifiers
        ) noexcept :
                C_ENG_CONSTRUCTOR ( MouseEvent ) (
                        window,
                        position
                ),
                _button ( button ),
                _modifiers ( modifiers ) {

        }

        C_ENG_NO_DISCARD constexpr auto type () const noexcept -> EventType override {
            return EventType :: EventTypeMousePressEvent;
        }

        C_ENG_NO_DISCARD inline auto copy () const noexcept -> C_ENG_TYPE ( MousePressEvent ) * override {
            return new C_ENG_TYPE ( MousePressEvent ) ( * this );
        }

        C_ENG_NO_DISCARD inline auto hash () const noexcept -> cds :: Index override {
            return
                ( static_cast < cds :: Index > ( this->button() ) );
        }

        C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
        C_ENG_NO_DISCARD auto equals ( cds :: Object const & ) const noexcept -> bool override;
    };

}

#endif //C_ENG_MOUSEPRESSEVENT_HPP

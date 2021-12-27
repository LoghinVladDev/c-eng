//
// Created by loghin on 20.12.2021.
//

#ifndef __C_ENG_MOUSEPRESSEVENT_HPP
#define __C_ENG_MOUSEPRESSEVENT_HPP

#include <MouseEvent.hpp>

namespace engine {

    __C_ENG_CLASS ( MousePressEvent ) : public __C_ENG_TYPE ( MouseEvent ) {
        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( __C_ENG_TYPE ( MouseButton ), button, __C_ENG_TYPE ( MouseButton ) :: MouseButtonUndefined )
        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( __C_ENG_TYPE ( KeyModifiers ), modifiers, __C_ENG_TYPE ( KeyModifier ) :: KeyModifierNone )

    public:
        __C_ENG_DESTRUCTOR ( MousePressEvent ) () noexcept override = default;

        __C_ENG_CONSTRUCTOR ( MousePressEvent ) (
                __C_ENG_TYPE ( Window )               * window,
                __C_ENG_TYPE ( Position )       const & position,
                __C_ENG_TYPE ( MouseButton )            button,
                __C_ENG_TYPE ( KeyModifiers )           modifiers
        ) noexcept :
                __C_ENG_CONSTRUCTOR ( MouseEvent ) (
                        window,
                        position
                ),
                _button ( button ),
                _modifiers ( modifiers ) {

        }

        __C_ENG_NO_DISCARD constexpr auto type () const noexcept -> __C_ENG_TYPE ( EventType ) override {
            return __C_ENG_TYPE ( EventType ) :: EventTypeMousePressEvent;
        }

        __C_ENG_NO_DISCARD inline auto copy () const noexcept -> __C_ENG_TYPE ( MousePressEvent ) * override {
            return new __C_ENG_TYPE ( MousePressEvent ) ( * this );
        }

        __C_ENG_NO_DISCARD inline auto hash () const noexcept -> cds :: Index override {
            return
                ( static_cast < cds :: Index > ( this->button() ) );
        }

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
        __C_ENG_NO_DISCARD auto equals ( cds :: Object const & ) const noexcept -> bool override;
    };

}

#endif //__C_ENG_MOUSEPRESSEVENT_HPP

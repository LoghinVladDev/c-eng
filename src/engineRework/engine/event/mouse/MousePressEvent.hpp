//
// Created by loghin on 20.12.2021.
//

#ifndef __C_ENG_MOUSEPRESSEVENT_HPP
#define __C_ENG_MOUSEPRESSEVENT_HPP

#include <MouseEvent.hpp>


#define C_ENG_MAP_START     CLASS ( MousePressEvent, ENGINE_PARENT ( MouseEvent ) )
#include <ObjectMapping.hpp>

namespace engine {

    Class {
        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( __C_ENG_TYPE ( MouseButton ), button, __C_ENG_TYPE ( MouseButton ) :: MouseButtonUndefined )
        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( __C_ENG_TYPE ( KeyModifiers ), modifiers, __C_ENG_TYPE ( KeyModifier ) :: KeyModifierNone )

    public:
        Destructor () noexcept override = default;

        Constructor (
                __C_ENG_TYPE ( Window )               * window,
                __C_ENG_TYPE ( Position )       const & position,
                __C_ENG_TYPE ( MouseButton )            button,
                __C_ENG_TYPE ( KeyModifiers )           modifiers
        ) noexcept :
                Parent (
                        window,
                        position
                ),
                _button ( button ),
                _modifiers ( modifiers ) {

        }

        __C_ENG_NO_DISCARD constexpr auto type () const noexcept -> __C_ENG_TYPE ( EventType ) override {
            return __C_ENG_TYPE ( EventType ) :: EventTypeMousePressEvent;
        }

        __C_ENG_NO_DISCARD inline auto copy () const noexcept -> Self * override {
            return new Self ( * this );
        }

        __C_ENG_NO_DISCARD inline auto hash () const noexcept -> cds :: Index override {
            return
                ( static_cast < cds :: Index > ( this->button() ) );
        }

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
        __C_ENG_NO_DISCARD auto equals ( cds :: Object const & ) const noexcept -> bool override;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //__C_ENG_MOUSEPRESSEVENT_HPP

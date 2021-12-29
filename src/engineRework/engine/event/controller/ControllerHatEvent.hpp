//
// Created by loghin on 22.12.2021.
//

#ifndef __C_ENG_CONTROLLERHATEVENT_HPP
#define __C_ENG_CONTROLLERHATEVENT_HPP


#include <ControllerEvent.hpp>


#define C_ENG_MAP_START     CLASS ( ControllerHatEvent, ENGINE_PARENT ( ControllerEvent ) )
#include <ObjectMapping.hpp>

namespace engine {

    Class {
        Field ( PRIMITIVE_TYPE ( cds :: uint16 ),               hat,    DEFAULT_VALUE ( 0u ),                           GET_DEFAULT, SET_NONE )
        Field ( ENGINE_PRIMITIVE_TYPE ( ControllerHatState ),   state,  DEFAULT_VALUE ( ControllerHatStateCentered ),   GET_DEFAULT, SET_NONE )

    public:
        explicit Constructor (
                __C_ENG_TYPE ( Controller )       * controller,
                cds :: uint16                       hat,
                __C_ENG_TYPE ( ControllerHatState ) state
        ) noexcept :
                Parent ( nullptr ),
                _hat ( hat ),
                _state ( state ) {

        }

        Destructor () noexcept override = default;

        __C_ENG_NO_DISCARD constexpr auto type () const noexcept -> __C_ENG_TYPE ( EventType ) override {
            return __C_ENG_TYPE ( EventType ) :: EventTypeControllerHatEvent;
        }

        __C_ENG_NO_DISCARD inline auto copy () const noexcept -> Self * override {
            return new Self ( * this );
        }

        __C_ENG_NO_DISCARD inline auto hash () const noexcept -> cds :: Index override {
            return
                    ( this-> Parent :: hash() & 0xFF ) +
                    ( static_cast < cds :: Index > ( this->hat() ) << 8 );
        }

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
        __C_ENG_NO_DISCARD auto equals ( cds :: Object const & ) const noexcept -> bool override;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //__C_ENG_CONTROLLERHATEVENT_HPP

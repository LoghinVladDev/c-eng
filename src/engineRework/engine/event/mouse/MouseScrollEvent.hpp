//
// Created by loghin on 20.12.2021.
//

#ifndef __C_ENG_MOUSE_SCROLL_EVENT_HPP__
#define __C_ENG_MOUSE_SCROLL_EVENT_HPP__

#include <MouseEvent.hpp>


#define C_ENG_MAP_START     CLASS ( MouseScrollEvent, ENGINE_PARENT ( MouseEvent ) )
#include <ObjectMapping.hpp>

namespace engine {

    Class {
        Field ( PRIMITIVE_TYPE ( double ), xOffset, DEFAULT_VALUE ( 0.0 ), GET_DEFAULT, SET_NONE )
        Field ( PRIMITIVE_TYPE ( double ), yOffset, DEFAULT_VALUE ( 0.0 ), GET_DEFAULT, SET_NONE )

    public:
        Destructor () noexcept override = default;

        Constructor (
                __C_ENG_TYPE ( Window )           * window,
                __C_ENG_TYPE ( Position )   const & position,
                double                              xOffset,
                double                              yOffset
        ) noexcept :
                Parent (
                        window,
                        position
                ),
                _xOffset ( xOffset ),
                _yOffset ( yOffset ) {

        }

        __C_ENG_NO_DISCARD constexpr auto type () const noexcept -> __C_ENG_TYPE ( EventType ) override {
            return __C_ENG_TYPE ( EventType ) :: EventTypeMouseScrollEvent;
        }

        __C_ENG_NO_DISCARD inline auto copy () const noexcept -> Self * override {
            return new Self ( * this );
        }

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
        __C_ENG_NO_DISCARD auto equals ( cds :: Object const & ) const noexcept -> bool override;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //__C_ENG_MOUSE_SCROLL_EVENT_HPP__

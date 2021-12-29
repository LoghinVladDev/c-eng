//
// Created by loghin on 20.12.2021.
//

#ifndef __C_ENG_MOUSEMOVEEVENT_HPP
#define __C_ENG_MOUSEMOVEEVENT_HPP

#include <MouseEvent.hpp>


#define C_ENG_MAP_START     CLASS ( MouseMoveEvent, ENGINE_PARENT ( MouseEvent ) )
#include <ObjectMapping.hpp>

namespace engine {

    Class {
        Field ( ENGINE_TYPE ( Position ), oldPosition, DEFAULT_VALUE ( 0u, 0u ), GET_DEFAULT, SET_NONE )

    public:
        Constructor (
                __C_ENG_TYPE ( Window )           * window,
                __C_ENG_TYPE ( Position )   const & position,
                __C_ENG_TYPE ( Position )   const & oldPosition
        ) noexcept :
                Parent (
                        window,
                        position
                ),
                _oldPosition ( oldPosition ) {


        }

        Destructor () noexcept override = default;

        __C_ENG_NO_DISCARD constexpr auto type () const noexcept -> __C_ENG_TYPE ( EventType ) override {
            return __C_ENG_TYPE ( EventType ) :: EventTypeMousePressEvent;
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


#endif //__C_ENG_MOUSEMOVEEVENT_HPP

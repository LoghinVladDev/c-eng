//
// Created by loghin on 21.12.2021.
//

#ifndef __C_ENG_WINDOW_MOVE_EVENT_HPP__
#define __C_ENG_WINDOW_MOVE_EVENT_HPP__


#include <WindowEvent.hpp>


#define C_ENG_MAP_START     CLASS ( WindowMoveEvent, ENGINE_PARENT ( WindowEvent ) )
#include <ObjectMapping.hpp>

namespace engine {

    Class {
        Field ( ENGINE_TYPE ( Position ), position,     DEFAULT_VALUE ( 0u, 0u ), GET_DEFAULT, SET_NONE )
        Field ( ENGINE_TYPE ( Position ), oldPosition,  DEFAULT_VALUE ( 0u, 0u ), GET_DEFAULT, SET_NONE )

    public:
        Destructor () noexcept override = default;

        Constructor (
                __C_ENG_TYPE ( Window )           * window,
                __C_ENG_TYPE ( Position )   const & position,
                __C_ENG_TYPE ( Position )   const & oldPosition
        ) noexcept :
                Parent ( window ),
                _position ( position ),
                _oldPosition ( oldPosition ) {

        }

        __C_ENG_NO_DISCARD constexpr auto type () const noexcept -> __C_ENG_TYPE ( EventType ) override {
            return __C_ENG_TYPE ( EventType ) :: EventTypeWindowMoveEvent;
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


#endif //__C_ENG_WINDOW_MOVE_EVENT_HPP__

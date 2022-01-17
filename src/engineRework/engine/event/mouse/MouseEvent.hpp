//
// Created by loghin on 20.12.2021.
//

#ifndef __C_ENG_MOUSE_EVENT_HPP__
#define __C_ENG_MOUSE_EVENT_HPP__


#include <Event.hpp>


#define C_ENG_MAP_START     CLASS ( MouseEvent, ENGINE_PARENT ( Event ) )
#include <ObjectMapping.hpp>

namespace engine {

    Class {
        Field ( ENGINE_TYPE ( Position ), position, DEFAULT_VALUE ( 0u, 0u ), GET_DEFAULT, SET_NONE )

    protected:
        Constructor (
                __C_ENG_TYPE ( Window )           * window,
                __C_ENG_TYPE ( Position )   const & position
        ) noexcept :
                Parent ( window ),
                _position ( position ) {

        }

    public:
        Destructor () noexcept override = default;

        __C_ENG_NO_DISCARD constexpr auto type () const noexcept -> __C_ENG_TYPE ( EventType ) override {
            return __C_ENG_TYPE ( EventType ) :: EventTypeCustomMouseEvent;
        }

        __C_ENG_NO_DISCARD auto copy () const noexcept -> Self * override = 0;

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
        __C_ENG_NO_DISCARD auto equals ( cds :: Object const & ) const noexcept -> bool override;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //__C_ENG_MOUSE_EVENT_HPP__

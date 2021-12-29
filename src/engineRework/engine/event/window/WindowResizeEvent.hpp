//
// Created by loghin on 20.12.2021.
//

#ifndef __C_ENG_WINDOWRESIZEEVENT_HPP
#define __C_ENG_WINDOWRESIZEEVENT_HPP


#include <WindowEvent.hpp>


#define C_ENG_MAP_START     CLASS ( WindowResizeEvent, ENGINE_PARENT ( WindowEvent ) )
#include <ObjectMapping.hpp>

namespace engine {

    Class {
        Field ( ENGINE_TYPE ( Size ),   size,       DEFAULT_VALUE ( 0u, 0u ), GET_DEFAULT, SET_NONE )
        Field ( ENGINE_TYPE ( Size ),   oldSize,    DEFAULT_VALUE ( 0u, 0u ), GET_DEFAULT, SET_NONE )

    public:
        Destructor () noexcept override = default;

        Constructor (
                __C_ENG_TYPE ( Window )       * window,
                __C_ENG_TYPE ( Size )   const & size,
                __C_ENG_TYPE ( Size )   const & oldSize
        ) noexcept :
                Parent ( window ),
                _size ( size ),
                _oldSize ( oldSize ) {

        }

        __C_ENG_NO_DISCARD constexpr auto type () const noexcept -> __C_ENG_TYPE ( EventType ) override {
            return __C_ENG_TYPE ( EventType ) :: EventTypeWindowResizeEvent;
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


#endif //__C_ENG_WINDOWRESIZEEVENT_HPP

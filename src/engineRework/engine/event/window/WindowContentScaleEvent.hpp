//
// Created by loghin on 21.12.2021.
//

#ifndef __C_ENG_WINDOWCONTENTSCALEEVENT_HPP
#define __C_ENG_WINDOWCONTENTSCALEEVENT_HPP


#include <WindowEvent.hpp>


#define C_ENG_MAP_START     CLASS ( WindowContentScaleEvent, ENGINE_PARENT ( WindowEvent ) )
#include <ObjectMapping.hpp>

namespace engine {

    Class {
        Field ( ENGINE_TYPE ( WindowContentScale ), scale, DEFAULT_VALUE ( 0.0f, 0.0f ), GET_DEFAULT, SET_NONE )

    public:
        Destructor () noexcept override = default;

        Constructor (
                __C_ENG_TYPE ( Window )                   * window,
                __C_ENG_TYPE ( WindowContentScale ) const & scale
        ) noexcept :
                Parent ( window ),
                _scale ( scale ) {

        }

        __C_ENG_NO_DISCARD constexpr auto type () const noexcept -> __C_ENG_TYPE ( EventType ) override {
            return __C_ENG_TYPE ( EventType ) :: EventTypeWindowContentScaleEvent;
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


#endif //__C_ENG_WINDOWCONTENTSCALEEVENT_HPP

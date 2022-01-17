//
// Created by loghin on 22.12.2021.
//

#ifndef __C_ENG_CONTROLLER_EVENT_HPP__
#define __C_ENG_CONTROLLER_EVENT_HPP__


#include <Event.hpp>


#define C_ENG_MAP_START     CLASS ( ControllerEvent, ENGINE_PARENT ( Event ) )
#include <ObjectMapping.hpp>

namespace engine {

    __C_ENG_PRE_DECLARE_CLASS ( Controller );

    Class {
        Field ( ENGINE_PRIMITIVE_TYPE ( Controller * ), controller, DEFAULT_VALUE ( nullptr ), GET_DEFAULT, SET_NONE )

    public:
        explicit Constructor (
                __C_ENG_TYPE ( Controller ) * controller
        ) noexcept :
                Parent ( nullptr ),
                _controller ( controller ) {

        }

        Destructor () noexcept override = default;

        __C_ENG_NO_DISCARD constexpr auto type () const noexcept -> __C_ENG_TYPE ( EventType ) override {
            return __C_ENG_TYPE ( EventType ) :: EventTypeCustomControllerEvent;
        }

        __C_ENG_NO_DISCARD auto copy () const noexcept -> Self * override = 0;

        __C_ENG_NO_DISCARD auto hash () const noexcept -> cds :: Index override;
        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;

        __C_ENG_NO_DISCARD auto equals ( cds :: Object const & ) const noexcept -> bool override;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //__C_ENG_CONTROLLER_EVENT_HPP__

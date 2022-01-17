//
// Created by loghin on 22.12.2021.
//

#ifndef __C_ENG_JOYSTICK_HPP__
#define __C_ENG_JOYSTICK_HPP__


#include <Controller.hpp>


#define C_ENG_MAP_START     CLASS ( Joystick, ENGINE_PARENT ( Controller ) )
#include <ObjectMapping.hpp>

namespace engine {

    Class {
        Field ( PRIMITIVE_TYPE ( cds :: uint32 ),   axisCount,      DEFAULT_VALUE ( 0 ),        GET_DEFAULT, SET_NONE )
        Field ( PRIMITIVE_TYPE ( float * ),         axes,           DEFAULT_VALUE ( nullptr ),  GET_DEFAULT, SET_NONE )
        Field ( PRIMITIVE_TYPE ( cds :: uint32 ),   buttonCount,    DEFAULT_VALUE ( 0 ),        GET_DEFAULT, SET_NONE )
        Field ( PRIMITIVE_TYPE ( bool * ),          buttons,        DEFAULT_VALUE ( nullptr ),  GET_DEFAULT, SET_NONE )
        Field ( PRIMITIVE_TYPE ( cds :: uint32 ),   hatCount,       DEFAULT_VALUE ( 0 ),        GET_DEFAULT, SET_NONE )
        Field ( PRIMITIVE_TYPE ( cds :: uint8 * ),  hats,           DEFAULT_VALUE ( nullptr ),  GET_DEFAULT, SET_NONE )

        auto update () noexcept -> void override;

    public:
        constexpr auto isGamepad () noexcept -> bool override {
            return false;
        };

        Destructor () noexcept override;

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //__C_ENG_JOYSTICK_HPP__

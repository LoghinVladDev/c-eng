//
// Created by loghin on 22.12.2021.
//

#ifndef __C_ENG_GAMEPAD_HPP
#define __C_ENG_GAMEPAD_HPP


#include <Controller.hpp>


#define C_ENG_MAP_START     CLASS ( Gamepad, ENGINE_PARENT ( Controller ) )
#include <ObjectMapping.hpp>

namespace engine {

    Class {
        Const ( PRIMITIVE_TYPE ( cds :: uint8 ), axesCount,     VALUE ( 6 ) )
        Const ( PRIMITIVE_TYPE ( cds :: uint8 ), buttonCount,   VALUE ( 15 ) )

        Field ( PRIMITIVE_TYPE ( cds :: StringLiteral ),        gamepadName,    DEFAULT_VALUE ( nullptr ),  GET_DEFAULT,    SET_NONE )
        Field ( PRIMITIVE_TYPE ( bool ),                        firstUpdate,    DEFAULT_VALUE ( false ),    GET_NONE,       SET_NONE )

        Field ( PRIMITIVE_TYPE_ARRAY ( float,   axesCount ),    axes,           NO_INIT,                    GET_NONE,       SET_NONE )
        Field ( PRIMITIVE_TYPE_ARRAY ( bool,    buttonCount ),  buttons,        NO_INIT,                    GET_NONE,       SET_NONE )

        __C_ENG_FRIEND_STRUCT ( ControllerHandler );
    private:
        auto update () noexcept -> void override;

    public:
        constexpr auto isGamepad () noexcept -> bool override {
            return true;
        };

        Destructor () noexcept override = default;

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //__C_ENG_GAMEPAD_HPP

//
// Created by loghin on 22.12.2021.
//

#ifndef __C_ENG_JOYSTICK_HPP
#define __C_ENG_JOYSTICK_HPP


#include <Controller.hpp>


#define C_ENG_MAP_START     CLASS ( Joystick, ENGINE_PARENT ( Controller ) )
#include <ObjectMapping.hpp>

namespace engine {

    Class {
    private:
        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint32, axisCount, 0u )
        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( float *, axes, nullptr )

        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint32, buttonCount, 0u )
        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( bool *, buttons, nullptr )

        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint32, hatCount, 0u )
        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint8 *, hats, nullptr )

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


#endif //__C_ENG_JOYSTICK_HPP

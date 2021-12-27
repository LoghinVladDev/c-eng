//
// Created by loghin on 22.12.2021.
//

#ifndef __C_ENG_JOYSTICK_HPP
#define __C_ENG_JOYSTICK_HPP


#include <Controller.hpp>

namespace engine {


#pragma push_macro ("__C_ENG_OBJECT_NAME")

#undef __C_ENG_OBJECT_NAME
#define __C_ENG_OBJECT_NAME Joystick /* NOLINT(bugprone-reserved-identifier) */

    __C_ENG_CLASS : public __C_ENG_TYPE ( Controller ) {
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

        __C_ENG_DESTRUCTOR () noexcept override;

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

#pragma pop_macro ("__C_ENG_OBJECT_NAME")


}


#endif //__C_ENG_JOYSTICK_HPP

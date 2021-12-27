//
// Created by loghin on 22.12.2021.
//

#ifndef __C_ENG_GAMEPAD_HPP
#define __C_ENG_GAMEPAD_HPP


#include <Controller.hpp>

namespace engine {


#pragma push_macro ("__C_ENG_OBJECT_NAME")

#undef __C_ENG_OBJECT_NAME
#define __C_ENG_OBJECT_NAME Gamepad /* NOLINT(bugprone-reserved-identifier) */

    __C_ENG_CLASS : public __C_ENG_TYPE ( Controller ) {
        __C_ENG_CLASS_PRIMITIVE_CONSTANT ( cds :: uint8, axesCount, 6U ) // NOLINT(clion-misra-cpp2008-5-0-4,clion-misra-cpp2008-5-0-6)
        __C_ENG_CLASS_PRIMITIVE_CONSTANT ( cds :: uint8, buttonCount, 15U ) // NOLINT(clion-misra-cpp2008-5-0-4,clion-misra-cpp2008-5-0-6)

    private:
        __C_ENG_FRIEND_STRUCT ( ControllerHandler );

        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: StringLiteral, gamepadName, nullptr );

        float   _axes[axesCount];
        bool    _buttons[buttonCount];

        bool    _firstUpdate { false };

    private:
        auto update () noexcept -> void override;

    public:
        constexpr auto isGamepad () noexcept -> bool override {
            return true;
        };

        __C_ENG_DESTRUCTOR () noexcept override = default;

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

#pragma pop_macro ("__C_ENG_OBJECT_NAME")


}


#endif //__C_ENG_GAMEPAD_HPP

//
// Created by loghin on 22.12.2021.
//

#ifndef C_ENG_GAMEPAD_HPP
#define C_ENG_GAMEPAD_HPP


#include <Controller.hpp>

namespace engine {

    class C_ENG_CLASS ( Gamepad ) : public C_ENG_CLASS ( Controller ) {
        C_ENG_CLASS_PRIMITIVE_CONSTANT ( cds :: uint8, axesCount, 6u )
        C_ENG_CLASS_PRIMITIVE_CONSTANT ( cds :: uint8, buttonCount, 15u )

    private:
        friend struct ControllerHandler;

        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: StringLiteral, gamepadName, nullptr );

        float   _axes[axesCount];
        bool    _buttons[buttonCount];

        bool    _firstUpdate { false };

    private:
        auto update () noexcept -> void override;

    public:
        constexpr auto isGamepad () noexcept -> bool override {
            return true;
        };

        C_ENG_DESTRUCTOR ( Gamepad ) () noexcept override;
    };

}


#endif //C_ENG_GAMEPAD_HPP

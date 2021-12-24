//
// Created by loghin on 22.12.2021.
//

#ifndef C_ENG_GAMEPAD_HPP
#define C_ENG_GAMEPAD_HPP


#include <Controller.hpp>

namespace engine {

    class C_ENG_CLASS ( Gamepad ) : public C_ENG_CLASS ( Controller ) {
        C_ENG_CLASS_PRIMITIVE_CONSTANT ( cds :: uint8, axesCount, 6U ) // NOLINT(clion-misra-cpp2008-5-0-4,clion-misra-cpp2008-5-0-6)
        C_ENG_CLASS_PRIMITIVE_CONSTANT ( cds :: uint8, buttonCount, 15U ) // NOLINT(clion-misra-cpp2008-5-0-4,clion-misra-cpp2008-5-0-6)

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

        C_ENG_DESTRUCTOR ( Gamepad ) () noexcept override = default;

        C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

}


#endif //C_ENG_GAMEPAD_HPP

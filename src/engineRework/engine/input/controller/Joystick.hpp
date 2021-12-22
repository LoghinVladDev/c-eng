//
// Created by loghin on 22.12.2021.
//

#ifndef C_ENG_JOYSTICK_HPP
#define C_ENG_JOYSTICK_HPP


#include <Controller.hpp>

namespace engine {

    class C_ENG_CLASS ( Joystick ) : public C_ENG_CLASS ( Controller ) {
    private:
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint32, axisCount, 0u )
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( float *, axes, nullptr )

        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint32, buttonCount, 0u )
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( bool *, buttons, nullptr )

        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint32, hatCount, 0u )
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint8 *, hats, nullptr )

        auto update () noexcept -> void override;

    public:
        constexpr auto isGamepad () noexcept -> bool override {
            return false;
        };

        C_ENG_DESTRUCTOR ( Joystick ) () noexcept override;
    };

}


#endif //C_ENG_JOYSTICK_HPP

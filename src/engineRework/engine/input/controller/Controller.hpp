//
// Created by loghin on 22.12.2021.
//

#ifndef C_ENG_CONTROLLER_HPP
#define C_ENG_CONTROLLER_HPP

#include <Preprocess.hpp>
#include <CDS/Array>

namespace engine {

    class C_ENG_CLASS ( Engine );

    class C_ENG_CLASS ( Controller ) : public cds :: Object {
    public:
        using Handle = cds :: sint32;

    private:
        friend struct ControllerHandler;

        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( Handle, handle, 0 )
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: StringLiteral, name, nullptr )

    protected:
        virtual auto update () noexcept -> void = 0;

    public:
        virtual auto isGamepad () noexcept -> bool = 0;

        static auto setEngine ( C_ENG_TYPE ( Engine ) * ) noexcept -> void;

        C_ENG_DESTRUCTOR ( Controller ) () noexcept override = default;

        C_ENG_NO_DISCARD static auto connectedControllers () noexcept -> cds :: Array < C_ENG_TYPE ( Controller ) * > const &;

        static auto updateEvents () noexcept -> void;
        static auto pollEvents () noexcept -> void;
    };

}


#endif //C_ENG_CONTROLLER_HPP

//
// Created by loghin on 22.12.2021.
//

#ifndef C_ENG_CONTROLLER_HPP
#define C_ENG_CONTROLLER_HPP

#include <Preprocess.hpp>
#include <CDS/Array>

namespace engine {

    class C_ENG_CLASS ( Engine );
    class C_ENG_CLASS ( ControllerEvent );

    class C_ENG_CLASS ( Controller ) : public cds :: Object {
    public:
        using Handle = cds :: sint32;
        C_ENG_CLASS_PRIMITIVE_CONSTANT ( cds :: uint32, controllerCapacity, 16u )

    private:
        friend struct ControllerHandler;

        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( Handle, handle, 0 )
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: StringLiteral, name, nullptr )

    protected:
        virtual auto update () noexcept -> void = 0;

    public:
        C_ENG_MAYBE_UNUSED virtual auto isGamepad () noexcept -> bool = 0;

        static auto setEngine ( C_ENG_TYPE ( Engine ) * ) noexcept -> void;

        C_ENG_DESTRUCTOR ( Controller ) () noexcept override = default;

        C_ENG_NO_DISCARD C_ENG_MAYBE_UNUSED static auto connectedControllerCount () noexcept -> cds :: uint32;
        C_ENG_NO_DISCARD C_ENG_MAYBE_UNUSED static auto connectedControllers () noexcept -> C_ENG_TYPE ( Controller ) **;

        C_ENG_MAYBE_UNUSED static auto handleEvent ( C_ENG_TYPE ( ControllerEvent ) const & ) noexcept -> void;
        static auto updateEvents () noexcept -> void;
        static auto pollEvents () noexcept -> void;

        C_ENG_NO_DISCARD inline auto copy () const noexcept -> C_ENG_TYPE ( Controller ) * override {
            return nullptr;
        }

        C_ENG_NO_DISCARD inline auto hash () const noexcept -> cds :: Index override {
            return static_cast < cds :: Index > ( this->handle() );
        }

        C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
        C_ENG_NO_DISCARD auto equals ( cds :: Object const & ) const noexcept -> bool override;
    };

}


#endif //C_ENG_CONTROLLER_HPP

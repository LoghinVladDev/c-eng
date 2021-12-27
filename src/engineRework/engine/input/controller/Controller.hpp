//
// Created by loghin on 22.12.2021.
//

#ifndef __C_ENG_CONTROLLER_HPP
#define __C_ENG_CONTROLLER_HPP

#include <Preprocess.hpp>
#include <CDS/Array>

namespace engine {

    __C_ENG_PRE_DECLARE_CLASS ( Engine );
    __C_ENG_PRE_DECLARE_CLASS ( ControllerEvent );


#pragma push_macro ("__C_ENG_OBJECT_NAME")

#undef __C_ENG_OBJECT_NAME
#define __C_ENG_OBJECT_NAME Controller /* NOLINT(bugprone-reserved-identifier) */

    __C_ENG_CLASS : public cds :: Object {
    public:
        using Handle = cds :: sint32;
        __C_ENG_CLASS_PRIMITIVE_CONSTANT ( cds :: uint32, controllerCapacity, 16u )

    private:
        __C_ENG_FRIEND_STRUCT ( ControllerHandler );

        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( Handle, handle, 0 )
        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: StringLiteral, name, nullptr )

    protected:
        virtual auto update () noexcept -> void = 0;

    public:
        __C_ENG_MAYBE_UNUSED virtual auto isGamepad () noexcept -> bool = 0;

        static auto setEngine ( __C_ENG_TYPE ( Engine ) * ) noexcept -> void;

        __C_ENG_DESTRUCTOR () noexcept override = default;

        __C_ENG_NO_DISCARD __C_ENG_MAYBE_UNUSED static auto connectedControllerCount () noexcept -> cds :: uint32;
        __C_ENG_NO_DISCARD __C_ENG_MAYBE_UNUSED static auto connectedControllers () noexcept -> __C_ENG_SELF **;

        __C_ENG_MAYBE_UNUSED static auto handleEvent ( __C_ENG_TYPE ( ControllerEvent ) const & ) noexcept -> void;
        static auto updateEvents () noexcept -> void;
        static auto pollEvents () noexcept -> void;

        __C_ENG_NO_DISCARD inline auto copy () const noexcept -> __C_ENG_SELF * override {
            return nullptr;
        }

        __C_ENG_NO_DISCARD inline auto hash () const noexcept -> cds :: Index override {
            return static_cast < cds :: Index > ( this->handle() );
        }

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
        __C_ENG_NO_DISCARD auto equals ( cds :: Object const & ) const noexcept -> bool override;
    };

#pragma pop_macro ("__C_ENG_OBJECT_NAME")


}


#endif //__C_ENG_CONTROLLER_HPP

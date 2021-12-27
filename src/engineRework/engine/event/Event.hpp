//
// Created by loghin on 20.12.2021.
//

#ifndef __C_ENG_EVENT_HPP
#define __C_ENG_EVENT_HPP

#include <Preprocess.hpp>
#include <CDS/Object>

#include <Core.hpp>

namespace engine {

    __C_ENG_PRE_DECLARE_CLASS ( Window );


#pragma push_macro ("__C_ENG_OBJECT_NAME")

#undef __C_ENG_OBJECT_NAME
#define __C_ENG_OBJECT_NAME Event /* NOLINT(bugprone-reserved-identifier) */

    __C_ENG_CLASS : public cds :: Object {
        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( __C_ENG_TYPE ( Window ) *, window, nullptr );

    protected:
        explicit __C_ENG_CONSTRUCTOR ( __C_ENG_TYPE ( Window ) * window ) noexcept :
                _window ( window ) {

        }

    public:
        __C_ENG_DESTRUCTOR () noexcept override = default;

        __C_ENG_NO_DISCARD constexpr virtual auto type () const noexcept -> __C_ENG_TYPE ( EventType ) {
            return __C_ENG_TYPE ( EventType ) :: EventTypeCustom;
        }

        __C_ENG_NO_DISCARD auto copy () const noexcept -> __C_ENG_SELF * override = 0;

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;

        __C_ENG_NO_DISCARD auto equals ( cds :: Object const & ) const noexcept -> bool override;
    };

#pragma pop_macro ("__C_ENG_OBJECT_NAME")


}

#endif //__C_ENG_EVENT_HPP

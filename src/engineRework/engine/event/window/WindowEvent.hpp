//
// Created by loghin on 21.12.2021.
//

#ifndef __C_ENG_WINDOWEVENT_HPP
#define __C_ENG_WINDOWEVENT_HPP


#include <Event.hpp>

namespace engine {


#pragma push_macro ("__C_ENG_OBJECT_NAME")

#undef __C_ENG_OBJECT_NAME
#define __C_ENG_OBJECT_NAME WindowEvent /* NOLINT(bugprone-reserved-identifier) */

    __C_ENG_CLASS : public __C_ENG_TYPE ( Event ) {
    protected:
        explicit __C_ENG_CONSTRUCTOR (
                __C_ENG_TYPE ( Window ) * window
        ) noexcept :
                __C_ENG_TYPE ( Event ) ( window ) {

        }

    public:
        __C_ENG_DESTRUCTOR () noexcept override = default;

        __C_ENG_NO_DISCARD constexpr auto type () const noexcept -> __C_ENG_TYPE ( EventType ) override {
            return __C_ENG_TYPE ( EventType ) :: EventTypeCustomWindowEvent;
        }

        __C_ENG_NO_DISCARD auto copy () const noexcept -> __C_ENG_SELF * override = 0;

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

#pragma pop_macro ("__C_ENG_OBJECT_NAME")


}

#endif //__C_ENG_WINDOWEVENT_HPP

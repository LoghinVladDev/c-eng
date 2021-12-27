//
// Created by loghin on 21.12.2021.
//

#ifndef __C_ENG_WINDOWMAXIMIZEEVENT_HPP
#define __C_ENG_WINDOWMAXIMIZEEVENT_HPP


#include <WindowEvent.hpp>

namespace engine {


#pragma push_macro ("__C_ENG_OBJECT_NAME")

#undef __C_ENG_OBJECT_NAME
#define __C_ENG_OBJECT_NAME WindowMaximizeEvent /* NOLINT(bugprone-reserved-identifier) */

    __C_ENG_CLASS : public __C_ENG_TYPE ( WindowEvent ) {

    public:
        __C_ENG_DESTRUCTOR () noexcept override = default;

        explicit __C_ENG_CONSTRUCTOR (
                __C_ENG_TYPE ( Window ) * window
        ) noexcept :
                __C_ENG_TYPE ( WindowEvent ) ( window ) {

        }

    public:
        __C_ENG_NO_DISCARD constexpr auto type () const noexcept -> __C_ENG_TYPE ( EventType ) override {
            return __C_ENG_TYPE ( EventType ) :: EventTypeWindowMaximizeEvent;
        }

        __C_ENG_NO_DISCARD inline auto copy () const noexcept -> __C_ENG_SELF * override {
            return new __C_ENG_SELF ( * this );
        }

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

#pragma pop_macro ("__C_ENG_OBJECT_NAME")


}


#endif //__C_ENG_WINDOWMAXIMIZEEVENT_HPP

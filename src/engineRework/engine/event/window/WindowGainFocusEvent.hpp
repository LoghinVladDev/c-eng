//
// Created by loghin on 21.12.2021.
//

#ifndef __C_ENG_WINDOWGAINFOCUSEVENT_HPP
#define __C_ENG_WINDOWGAINFOCUSEVENT_HPP


#include <WindowEvent.hpp>

namespace engine {

    __C_ENG_CLASS ( WindowGainFocusEvent ) : public __C_ENG_TYPE ( WindowEvent ) {

    public:
        __C_ENG_DESTRUCTOR ( WindowGainFocusEvent ) () noexcept override = default;

        explicit __C_ENG_CONSTRUCTOR ( WindowGainFocusEvent ) (
                __C_ENG_TYPE ( Window ) * window
        ) noexcept :
                __C_ENG_CONSTRUCTOR ( WindowEvent ) ( window ) {

        }

    public:
        __C_ENG_NO_DISCARD constexpr auto type () const noexcept -> __C_ENG_TYPE ( EventType ) override {
            return __C_ENG_TYPE ( EventType ) :: EventTypeWindowGainFocusEvent;
        }

        __C_ENG_NO_DISCARD inline auto copy () const noexcept -> __C_ENG_TYPE ( WindowGainFocusEvent ) * override {
            return new __C_ENG_TYPE ( WindowGainFocusEvent ) ( * this );
        }

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

}


#endif //__C_ENG_WINDOWGAINFOCUSEVENT_HPP

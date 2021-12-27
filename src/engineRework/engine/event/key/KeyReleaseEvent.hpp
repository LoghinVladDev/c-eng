//
// Created by loghin on 20.12.2021.
//

#ifndef __C_ENG_KEYRELEASEEVENT_HPP
#define __C_ENG_KEYRELEASEEVENT_HPP


#include <KeyEvent.hpp>

namespace engine {

    __C_ENG_CLASS ( KeyReleaseEvent ) : public __C_ENG_TYPE ( KeyEvent ) {
    public:
        __C_ENG_DESTRUCTOR ( KeyReleaseEvent ) () noexcept override = default;

        __C_ENG_CONSTRUCTOR ( KeyReleaseEvent ) (
                __C_ENG_TYPE ( Window )       * window,
                __C_ENG_TYPE ( Key )            key,
                __C_ENG_TYPE ( KeyModifiers )   modifiers
        ) noexcept :
                __C_ENG_CONSTRUCTOR ( KeyEvent ) (
                        window,
                        key,
                        modifiers
                ) {

        }

        __C_ENG_NO_DISCARD constexpr auto type () const noexcept -> __C_ENG_TYPE ( EventType ) override {
            return __C_ENG_TYPE ( EventType ) :: EventTypeKeyReleaseEvent;
        }

        __C_ENG_NO_DISCARD inline auto copy () const noexcept -> __C_ENG_TYPE ( KeyReleaseEvent ) * override {
            return new __C_ENG_TYPE ( KeyReleaseEvent ) ( * this );
        }

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

}


#endif //__C_ENG_KEYRELEASEEVENT_HPP

//
// Created by loghin on 20.12.2021.
//

#ifndef __C_ENG_KEYPRESSEVENT_HPP
#define __C_ENG_KEYPRESSEVENT_HPP

#include <KeyEvent.hpp>

namespace engine {

    __C_ENG_CLASS ( KeyPressEvent ) : public __C_ENG_TYPE ( KeyEvent ) {
    public:
        __C_ENG_DESTRUCTOR ( KeyPressEvent ) () noexcept override = default;

        __C_ENG_CONSTRUCTOR ( KeyPressEvent ) (
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
            return __C_ENG_TYPE ( EventType ) :: EventTypeKeyPressEvent;
        }

        __C_ENG_NO_DISCARD inline auto copy () const noexcept -> __C_ENG_TYPE ( KeyPressEvent ) * override {
            return new __C_ENG_TYPE ( KeyPressEvent ) ( * this );
        }

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

}


#endif //__C_ENG_KEYPRESSEVENT_HPP

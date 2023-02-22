//
// Created by loghin on 20.12.2021.
//

#ifndef __C_ENG_KEY_PRESS_EVENT_HPP__
#define __C_ENG_KEY_PRESS_EVENT_HPP__

#include <KeyEvent.hpp>


#define C_ENG_MAP_START     CLASS ( KeyPressEvent, ENGINE_PARENT ( KeyEvent ) )
#include <ObjectMapping.hpp>

namespace engine {

    Class {
    public:
        Destructor () noexcept override = default;

        Constructor (
                __C_ENG_TYPE ( Window )       * window,
                __C_ENG_TYPE ( Key )            key,
                __C_ENG_TYPE ( KeyModifiers )   modifiers
        ) noexcept :
                Parent (
                        window,
                        key,
                        modifiers
                ) {

        }

        __C_ENG_NO_DISCARD constexpr auto type () const noexcept -> __C_ENG_TYPE ( EventType ) override {
            return __C_ENG_TYPE ( EventType ) :: EventTypeKeyPressEvent;
        }

        __C_ENG_NO_DISCARD inline auto copy () const noexcept -> Self * override {
            return new Self ( * this );
        }

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //__C_ENG_KEY_PRESS_EVENT_HPP__

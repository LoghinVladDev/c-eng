//
// Created by loghin on 20.12.2021.
//

#ifndef __C_ENG_KEYRELEASEEVENT_HPP
#define __C_ENG_KEYRELEASEEVENT_HPP


#include <KeyEvent.hpp>


#define C_ENG_MAP_START     CLASS ( KeyReleaseEvent, ENGINE_PARENT ( KeyEvent ) )
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
            return __C_ENG_TYPE ( EventType ) :: EventTypeKeyReleaseEvent;
        }

        __C_ENG_NO_DISCARD inline auto copy () const noexcept -> Self * override {
            return new Self ( * this );
        }

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };
    
}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //__C_ENG_KEYRELEASEEVENT_HPP

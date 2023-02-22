//
// Created by loghin on 20.12.2021.
//

#ifndef __C_ENG_KEY_EVENT_HPP__
#define __C_ENG_KEY_EVENT_HPP__

#include <Event.hpp>


#define C_ENG_MAP_START     CLASS ( KeyEvent, ENGINE_PARENT ( Event ) )
#include <ObjectMapping.hpp>

namespace engine {

    Class {
        Field ( ENGINE_PRIMITIVE_TYPE ( Key ),          key,        DEFAULT_VALUE ( KeyUnknown ),       GET_DEFAULT, SET_NONE )
        Field ( ENGINE_PRIMITIVE_TYPE ( KeyModifiers ), modifiers,  DEFAULT_VALUE ( KeyModifierNone ),  GET_DEFAULT, SET_NONE )

    protected:
        Constructor (
                __C_ENG_TYPE ( Window )       * window,
                __C_ENG_TYPE ( Key )            key,
                __C_ENG_TYPE ( KeyModifiers )   modifiers
        ) noexcept :
                Parent ( window ),
                _key ( key ),
                _modifiers ( modifiers ) {

        }

    public:
        Destructor () noexcept override = default;

        __C_ENG_NO_DISCARD constexpr auto type () const noexcept -> __C_ENG_TYPE ( EventType ) override {
            return __C_ENG_TYPE ( EventType ) :: EventTypeCustomKeyEvent;
        }

        __C_ENG_NO_DISCARD auto copy () const noexcept -> Self * override = 0;

        __C_ENG_NO_DISCARD inline auto hash () const noexcept -> cds :: Index override {
            return
                ( static_cast < cds :: Index > ( this->key() ) );
        }

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
        __C_ENG_NO_DISCARD auto equals ( cds :: Object const & ) const noexcept -> bool override;
    };
    
}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //__C_ENG_KEY_EVENT_HPP__

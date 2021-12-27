//
// Created by loghin on 20.12.2021.
//

#ifndef __C_ENG_KEYEVENT_HPP
#define __C_ENG_KEYEVENT_HPP

#include <Event.hpp>

namespace engine {


#pragma push_macro ("__C_ENG_OBJECT_NAME")

#undef __C_ENG_OBJECT_NAME
#define __C_ENG_OBJECT_NAME KeyEvent /* NOLINT(bugprone-reserved-identifier) */

    __C_ENG_CLASS : public __C_ENG_TYPE ( Event ) {

        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( __C_ENG_TYPE ( Key ), key, __C_ENG_TYPE ( Key ) :: KeyUnknown )
        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( __C_ENG_TYPE ( KeyModifiers ), modifiers, __C_ENG_TYPE ( KeyModifier ) :: KeyModifierNone )

    protected:
        __C_ENG_CONSTRUCTOR (
                __C_ENG_TYPE ( Window )       * window,
                __C_ENG_TYPE ( Key )            key,
                __C_ENG_TYPE ( KeyModifiers )   modifiers
        ) noexcept :
                __C_ENG_TYPE ( Event ) ( window ),
                _key ( key ),
                _modifiers ( modifiers ) {

        }

    public:
        __C_ENG_DESTRUCTOR () noexcept override = default;

        __C_ENG_NO_DISCARD constexpr auto type () const noexcept -> __C_ENG_TYPE ( EventType ) override {
            return __C_ENG_TYPE ( EventType ) :: EventTypeCustomKeyEvent;
        }

        __C_ENG_NO_DISCARD auto copy () const noexcept -> __C_ENG_SELF * override = 0;

        __C_ENG_NO_DISCARD inline auto hash () const noexcept -> cds :: Index override {
            return
                ( static_cast < cds :: Index > ( this->key() ) );
        }

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
        __C_ENG_NO_DISCARD auto equals ( cds :: Object const & ) const noexcept -> bool override;
    };

#pragma pop_macro ("__C_ENG_OBJECT_NAME")


}


#endif //__C_ENG_KEYEVENT_HPP

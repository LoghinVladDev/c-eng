//
// Created by loghin on 22.12.2021.
//

#ifndef __C_ENG_CONTROLLERHATEVENT_HPP
#define __C_ENG_CONTROLLERHATEVENT_HPP


#include <ControllerEvent.hpp>

namespace engine {


#pragma push_macro ("__C_ENG_OBJECT_NAME")

#undef __C_ENG_OBJECT_NAME
#define __C_ENG_OBJECT_NAME ControllerHatEvent /* NOLINT(bugprone-reserved-identifier) */

    __C_ENG_CLASS : public __C_ENG_TYPE ( ControllerEvent ) {
    private:
        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint16, hat, 0u )
        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( __C_ENG_TYPE ( ControllerHatState ), state, __C_ENG_TYPE ( ControllerHatState ) :: ControllerHatStateCentered )

    public:
        explicit __C_ENG_CONSTRUCTOR (
                __C_ENG_TYPE ( Controller )       * controller,
                cds :: uint16                       hat,
                __C_ENG_TYPE ( ControllerHatState ) state
        ) noexcept :
                __C_ENG_TYPE ( ControllerEvent ) ( nullptr ),
                _hat ( hat ),
                _state ( state ) {

        }

        __C_ENG_DESTRUCTOR () noexcept override = default;

        __C_ENG_NO_DISCARD constexpr auto type () const noexcept -> __C_ENG_TYPE ( EventType ) override {
            return __C_ENG_TYPE ( EventType ) :: EventTypeControllerHatEvent;
        }

        __C_ENG_NO_DISCARD inline auto copy () const noexcept -> __C_ENG_SELF * override {
            return new __C_ENG_SELF ( * this );
        }

        __C_ENG_NO_DISCARD inline auto hash () const noexcept -> cds :: Index override {
            return
                    ( this->__C_ENG_TYPE(ControllerEvent)::hash() & 0xFF ) +
                    ( static_cast < cds :: Index > ( this->hat() ) << 8 );
        }

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
        __C_ENG_NO_DISCARD auto equals ( cds :: Object const & ) const noexcept -> bool override;
    };

#pragma pop_macro ("__C_ENG_OBJECT_NAME")


}


#endif //__C_ENG_CONTROLLERHATEVENT_HPP

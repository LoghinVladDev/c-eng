//
// Created by loghin on 22.12.2021.
//

#ifndef __C_ENG_CONTROLLERAXISEVENT_HPP
#define __C_ENG_CONTROLLERAXISEVENT_HPP


#include <ControllerEvent.hpp>

namespace engine {


#pragma push_macro ("__C_ENG_OBJECT_NAME")

#undef __C_ENG_OBJECT_NAME
#define __C_ENG_OBJECT_NAME ControllerAxisEvent /* NOLINT(bugprone-reserved-identifier) */

    __C_ENG_CLASS : public __C_ENG_TYPE ( ControllerEvent ) {
    private:
        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint16, axis, 0u )
        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( float, value, 0.0f )
        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( float, oldValue, 0.0f )

    public:
        explicit __C_ENG_CONSTRUCTOR (
                __C_ENG_TYPE ( Controller )   * controller,
                cds :: uint16                   axis,
                float                           value,
                float                           oldValue
        ) noexcept :
                __C_ENG_TYPE ( ControllerEvent ) ( nullptr ),
                _axis ( axis ),
                _value ( value ),
                _oldValue ( oldValue ) {

        }

        __C_ENG_DESTRUCTOR () noexcept override = default;

        __C_ENG_NO_DISCARD constexpr auto type () const noexcept -> __C_ENG_TYPE ( EventType ) override {
            return __C_ENG_TYPE ( EventType ) :: EventTypeControllerAxisEvent;
        }

        __C_ENG_NO_DISCARD inline auto copy () const noexcept -> __C_ENG_SELF * override {
            return new __C_ENG_SELF ( * this );
        }

        __C_ENG_NO_DISCARD inline auto hash () const noexcept -> cds :: Index override {
            return
                ( this->__C_ENG_TYPE(ControllerEvent)::hash() & 0xFF ) +
                ( static_cast < cds :: Index > ( this->axis() ) << 8 );
        }

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
        __C_ENG_NO_DISCARD auto equals ( cds :: Object const & ) const noexcept -> bool override;
    };

#pragma pop_macro ("__C_ENG_OBJECT_NAME")
    

}


#endif //__C_ENG_CONTROLLERAXISEVENT_HPP

//
// Created by loghin on 22.12.2021.
//

#ifndef __C_ENG_CONTROLLERBUTTONRAISEEVENT_HPP
#define __C_ENG_CONTROLLERBUTTONRAISEEVENT_HPP


#include <ControllerEvent.hpp>

namespace engine {

    __C_ENG_CLASS ( ControllerButtonReleaseEvent ) : public __C_ENG_TYPE ( ControllerEvent ) {
    private:
        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint16, button, 0u )

    public:
        explicit __C_ENG_CONSTRUCTOR ( ControllerButtonReleaseEvent ) (
                __C_ENG_TYPE ( Controller ) * controller,
                cds :: uint16                 button
        ) noexcept :
                __C_ENG_CONSTRUCTOR ( ControllerEvent ) ( nullptr ),
                _button ( button ) {

        }

        __C_ENG_DESTRUCTOR ( ControllerButtonReleaseEvent ) () noexcept override = default;

        __C_ENG_NO_DISCARD constexpr auto type () const noexcept -> __C_ENG_TYPE ( EventType ) override {
            return __C_ENG_TYPE ( EventType ) :: EventTypeControllerButtonReleaseEvent;
        }

        __C_ENG_NO_DISCARD inline auto copy () const noexcept -> __C_ENG_TYPE ( ControllerButtonReleaseEvent ) * override {
            return new __C_ENG_TYPE ( ControllerButtonReleaseEvent ) ( * this );
        }

        __C_ENG_NO_DISCARD inline auto hash () const noexcept -> cds :: Index override {
            return
                    ( this->__C_ENG_TYPE(ControllerEvent)::hash() & 0xFF ) +
                    ( static_cast < cds :: Index > ( this->button() ) << 8 );
        }

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
        __C_ENG_NO_DISCARD auto equals ( cds :: Object const & ) const noexcept -> bool override;
    };

}


#endif //__C_ENG_CONTROLLERBUTTONRAISEEVENT_HPP

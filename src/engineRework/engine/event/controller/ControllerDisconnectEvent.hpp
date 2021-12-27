//
// Created by loghin on 22.12.2021.
//

#ifndef __C_ENG_CONTROLLERDISCONNECTEVENT_HPP
#define __C_ENG_CONTROLLERDISCONNECTEVENT_HPP


#include <ControllerEvent.hpp>

namespace engine {

    __C_ENG_CLASS ( ControllerDisconnectEvent ) : public __C_ENG_TYPE ( ControllerEvent ) {
    public:
        explicit __C_ENG_CONSTRUCTOR ( ControllerDisconnectEvent ) (
                __C_ENG_TYPE ( Controller ) * controller
        ) noexcept :
                __C_ENG_CONSTRUCTOR ( ControllerEvent ) ( nullptr ) {

        }

        __C_ENG_DESTRUCTOR ( ControllerDisconnectEvent ) () noexcept override = default;

        __C_ENG_NO_DISCARD constexpr auto type () const noexcept -> __C_ENG_TYPE ( EventType ) override {
            return __C_ENG_TYPE ( EventType ) :: EventTypeControllerDisconnectEvent;
        }

        __C_ENG_NO_DISCARD inline auto copy () const noexcept -> __C_ENG_TYPE ( ControllerDisconnectEvent ) * override {
            return new __C_ENG_TYPE ( ControllerDisconnectEvent ) ( * this );
        }

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

}


#endif //__C_ENG_CONTROLLERDISCONNECTEVENT_HPP

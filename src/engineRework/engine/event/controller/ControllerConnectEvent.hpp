//
// Created by loghin on 22.12.2021.
//

#ifndef __C_ENG_CONTROLLERCONNECTEVENT_HPP
#define __C_ENG_CONTROLLERCONNECTEVENT_HPP

#include <ControllerEvent.hpp>

namespace engine {

    __C_ENG_CLASS ( ControllerConnectEvent ) : public __C_ENG_TYPE ( ControllerEvent ) {
    public:
        explicit __C_ENG_CONSTRUCTOR ( ControllerConnectEvent ) (
                __C_ENG_TYPE ( Controller ) * controller
        ) noexcept :
                __C_ENG_CONSTRUCTOR ( ControllerEvent ) ( nullptr ) {

        }

        __C_ENG_DESTRUCTOR ( ControllerConnectEvent ) () noexcept override = default;

        __C_ENG_NO_DISCARD constexpr auto type () const noexcept -> __C_ENG_TYPE ( EventType ) override {
            return __C_ENG_TYPE ( EventType ) :: EventTypeControllerConnectEvent;
        }

        __C_ENG_NO_DISCARD inline auto copy () const noexcept -> __C_ENG_TYPE ( ControllerConnectEvent ) * override {
            return new __C_ENG_TYPE ( ControllerConnectEvent ) ( * this );
        }

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

}


#endif //__C_ENG_CONTROLLERCONNECTEVENT_HPP

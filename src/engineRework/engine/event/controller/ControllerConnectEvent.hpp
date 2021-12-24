//
// Created by loghin on 22.12.2021.
//

#ifndef C_ENG_CONTROLLERCONNECTEVENT_HPP
#define C_ENG_CONTROLLERCONNECTEVENT_HPP

#include <ControllerEvent.hpp>

namespace engine {

    class C_ENG_CLASS ( ControllerConnectEvent ) : public C_ENG_CLASS ( ControllerEvent ) {
    public:
        explicit C_ENG_CONSTRUCTOR ( ControllerConnectEvent ) (
                C_ENG_TYPE ( Controller ) * controller
        ) noexcept :
                C_ENG_CONSTRUCTOR ( ControllerEvent ) ( nullptr ) {

        }

        C_ENG_DESTRUCTOR ( ControllerConnectEvent ) () noexcept override = default;

        C_ENG_NO_DISCARD constexpr auto type () const noexcept -> EventType override {
            return EventType :: EventTypeControllerConnectEvent;
        }

        C_ENG_NO_DISCARD inline auto copy () const noexcept -> C_ENG_TYPE ( ControllerConnectEvent ) * override {
            return new C_ENG_TYPE ( ControllerConnectEvent ) ( * this );
        }

        C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

}


#endif //C_ENG_CONTROLLERCONNECTEVENT_HPP

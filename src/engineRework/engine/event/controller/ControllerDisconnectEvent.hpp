//
// Created by loghin on 22.12.2021.
//

#ifndef C_ENG_CONTROLLERDISCONNECTEVENT_HPP
#define C_ENG_CONTROLLERDISCONNECTEVENT_HPP


#include <ControllerEvent.hpp>

namespace engine {

    class C_ENG_CLASS ( ControllerDisconnectEvent ) : public C_ENG_CLASS ( ControllerEvent ) {
    public:
        explicit C_ENG_CONSTRUCTOR ( ControllerDisconnectEvent ) (
                C_ENG_TYPE ( Controller ) * controller
        ) noexcept :
                C_ENG_CONSTRUCTOR ( ControllerEvent ) ( nullptr ) {

        }

        C_ENG_DESTRUCTOR ( ControllerDisconnectEvent ) () noexcept override = default;

        C_ENG_NO_DISCARD constexpr auto type () const noexcept -> EventType override {
            return EventType :: EventTypeControllerDisconnectEvent;
        }

        C_ENG_NO_DISCARD inline auto copy () const noexcept -> C_ENG_TYPE ( ControllerDisconnectEvent ) * override {
            return new C_ENG_TYPE ( ControllerDisconnectEvent ) ( * this );
        }

        C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

}


#endif //C_ENG_CONTROLLERDISCONNECTEVENT_HPP

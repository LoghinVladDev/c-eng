//
// Created by loghin on 22.12.2021.
//

#ifndef C_ENG_CONTROLLERHATEVENT_HPP
#define C_ENG_CONTROLLERHATEVENT_HPP


#include <ControllerEvent.hpp>

namespace engine {

    class C_ENG_CLASS ( ControllerHatEvent ) : public C_ENG_CLASS ( ControllerEvent ) {
    private:
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint16, hat, 0u )
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( ControllerHatState, state, ControllerHatState :: ControllerHatStateCentered )

    public:
        explicit C_ENG_CONSTRUCTOR ( ControllerHatEvent ) (
                C_ENG_TYPE ( Controller ) * controller,
                cds :: uint16               hat,
                ControllerHatState          state
        ) noexcept :
                C_ENG_CONSTRUCTOR ( ControllerEvent ) ( nullptr ),
                _hat ( hat ),
                _state ( state ) {

        }

        C_ENG_DESTRUCTOR ( ControllerHatEvent ) () noexcept override = default;

        C_ENG_NO_DISCARD constexpr auto type () const noexcept -> EventType override {
            return EventType :: EventTypeControllerHatEvent;
        }

        C_ENG_NO_DISCARD inline auto copy () const noexcept -> C_ENG_TYPE ( ControllerHatEvent ) * override {
            return new C_ENG_TYPE ( ControllerHatEvent ) ( * this );
        }

        C_ENG_NO_DISCARD inline auto hash () const noexcept -> cds :: Index override {
            return
                    ( this->C_ENG_CLASS(ControllerEvent)::hash() & 0xFF ) +
                    ( static_cast < cds :: Index > ( this->hat() ) << 8 );
        }

        C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
        C_ENG_NO_DISCARD auto equals ( cds :: Object const & ) const noexcept -> bool override;
    };

}


#endif //C_ENG_CONTROLLERHATEVENT_HPP

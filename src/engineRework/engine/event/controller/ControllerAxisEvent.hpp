//
// Created by loghin on 22.12.2021.
//

#ifndef C_ENG_CONTROLLERAXISEVENT_HPP
#define C_ENG_CONTROLLERAXISEVENT_HPP


#include <ControllerEvent.hpp>

namespace engine {

    class C_ENG_CLASS ( ControllerAxisEvent ) : public C_ENG_CLASS ( ControllerEvent ) {
    private:
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint16, axis, 0u )
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( float, value, 0.0f )
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( float, oldValue, 0.0f )

    public:
        explicit C_ENG_CONSTRUCTOR ( ControllerAxisEvent ) (
                C_ENG_TYPE ( Controller ) * controller,
                cds :: uint16               axis,
                float                       value,
                float                       oldValue
        ) noexcept :
                C_ENG_CONSTRUCTOR ( ControllerEvent ) ( nullptr ),
                _axis ( axis ),
                _value ( value ),
                _oldValue ( oldValue ) {

        }

        C_ENG_DESTRUCTOR ( ControllerAxisEvent ) () noexcept override = default;

        C_ENG_NO_DISCARD constexpr auto type () const noexcept -> EventType override {
            return EventType :: EventTypeControllerAxisEvent;
        }

        C_ENG_NO_DISCARD inline auto copy () const noexcept -> C_ENG_TYPE ( ControllerAxisEvent ) * override {
            return new C_ENG_TYPE ( ControllerAxisEvent ) ( * this );
        }

        C_ENG_NO_DISCARD inline auto hash () const noexcept -> cds :: Index override {
            return
                ( this->C_ENG_CLASS(ControllerEvent)::hash() & 0xFF ) +
                ( static_cast < cds :: Index > ( this->axis() ) << 8 );
        }

        C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
        C_ENG_NO_DISCARD auto equals ( cds :: Object const & ) const noexcept -> bool override;
    };

}


#endif //C_ENG_CONTROLLERAXISEVENT_HPP

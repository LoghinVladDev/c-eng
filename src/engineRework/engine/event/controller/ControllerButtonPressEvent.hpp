//
// Created by loghin on 22.12.2021.
//

#ifndef C_ENG_CONTROLLERBUTTONPRESSEVENT_HPP
#define C_ENG_CONTROLLERBUTTONPRESSEVENT_HPP


#include <ControllerEvent.hpp>

namespace engine {

    class C_ENG_CLASS ( ControllerButtonPressEvent ) : public C_ENG_CLASS ( ControllerEvent ) {
    private:
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint16, button, 0u )

    public:
        explicit C_ENG_CONSTRUCTOR ( ControllerButtonPressEvent ) (
                C_ENG_TYPE ( Controller ) * controller,
                cds :: uint16               button
        ) noexcept :
                C_ENG_CONSTRUCTOR ( ControllerEvent ) ( nullptr ),
                _button ( button ) {

        }

        C_ENG_DESTRUCTOR ( ControllerButtonPressEvent ) () noexcept override = default;

        C_ENG_NO_DISCARD constexpr auto type () const noexcept -> EventType override {
            return EventType :: EventTypeControllerButtonPressEvent;
        }

        C_ENG_NO_DISCARD inline auto copy () const noexcept -> C_ENG_TYPE ( ControllerButtonPressEvent ) * override {
            return new C_ENG_TYPE ( ControllerButtonPressEvent ) ( * this );
        }

        C_ENG_NO_DISCARD inline auto hash () const noexcept -> cds :: Index override {
            return
                    ( this->C_ENG_CLASS(ControllerEvent)::hash() & 0xFF ) +
                    ( static_cast < cds :: Index > ( this->button() ) << 8 );
        }

        C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
        C_ENG_NO_DISCARD auto equals ( cds :: Object const & ) const noexcept -> bool override;
    };

}


#endif //C_ENG_CONTROLLERBUTTONPRESSEVENT_HPP

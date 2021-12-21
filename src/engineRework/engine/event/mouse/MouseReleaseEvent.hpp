//
// Created by loghin on 20.12.2021.
//

#ifndef C_ENG_MOUSERELEASEEVENT_HPP
#define C_ENG_MOUSERELEASEEVENT_HPP


#include <MouseEvent.hpp>

namespace engine {

    class C_ENG_CLASS ( MouseReleaseEvent ) : public C_ENG_CLASS ( MouseEvent ) {
    C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( MouseButton, button, MouseButton :: MouseButtonUndefined )
    C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( KeyModifiers, modifiers, KeyModifier :: KeyModifierNone )

    public:
        C_ENG_DESTRUCTOR ( MouseReleaseEvent ) () noexcept override = default;

        C_ENG_CONSTRUCTOR ( MouseReleaseEvent ) (
                cds :: uint32           x,
                cds :: uint32           y,
                MouseButton             button,
                KeyModifiers            modifiers,
                C_ENG_TYPE ( Window ) * window
        ) noexcept :
                C_ENG_CONSTRUCTOR ( MouseEvent ) (
                        x,
                        y,
                        window
                ),
                _button ( button ),
                _modifiers ( modifiers ) {

        }

        C_ENG_NO_DISCARD constexpr auto type () const noexcept -> EventType override {
            return EventType :: EventTypeMouseReleaseEvent;
        }
    };

}


#endif //C_ENG_MOUSERELEASEEVENT_HPP

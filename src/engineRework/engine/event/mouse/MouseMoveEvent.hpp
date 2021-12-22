//
// Created by loghin on 20.12.2021.
//

#ifndef C_ENG_MOUSEMOVEEVENT_HPP
#define C_ENG_MOUSEMOVEEVENT_HPP

#include <MouseEvent.hpp>

namespace engine {

    class C_ENG_CLASS ( MouseMoveEvent ) : public C_ENG_CLASS ( MouseEvent ) {
        C_ENG_CLASS_IMMUTABLE_FIELD ( Position, oldPosition, 0u, 0u )

    public:
        C_ENG_CONSTRUCTOR ( MouseMoveEvent ) (
                C_ENG_TYPE ( Window ) * window,
                Position        const & position,
                Position        const & oldPosition
        ) noexcept :
                C_ENG_CONSTRUCTOR ( MouseEvent ) (
                        window,
                        position
                ),
                _oldPosition ( oldPosition ) {


        }

        C_ENG_DESTRUCTOR ( MouseMoveEvent ) () noexcept override = default;

        C_ENG_NO_DISCARD constexpr auto type () const noexcept -> EventType override {
            return EventType :: EventTypeMousePressEvent;
        }
    };

}

#endif //C_ENG_MOUSEMOVEEVENT_HPP

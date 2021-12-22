//
// Created by loghin on 21.12.2021.
//

#ifndef C_ENG_WINDOWMOVEEVENT_HPP
#define C_ENG_WINDOWMOVEEVENT_HPP


#include <WindowEvent.hpp>

namespace engine {

    class C_ENG_CLASS ( WindowMoveEvent ) : public C_ENG_CLASS ( WindowEvent ) {
        C_ENG_CLASS_IMMUTABLE_FIELD ( Position, position, 0u, 0u )
        C_ENG_CLASS_IMMUTABLE_FIELD ( Position, oldPosition, 0u, 0u )

    public:
        C_ENG_DESTRUCTOR ( WindowMoveEvent ) () noexcept override = default;

        C_ENG_CONSTRUCTOR ( WindowMoveEvent ) (
                C_ENG_TYPE ( Window ) * window,
                Position        const & position,
                Position        const & oldPosition
        ) noexcept :
                C_ENG_CONSTRUCTOR ( WindowEvent ) ( window ),
                _position ( position ),
                _oldPosition ( oldPosition ) {

        }

        C_ENG_NO_DISCARD constexpr auto type () const noexcept -> EventType override {
            return EventType :: EventTypeWindowMoveEvent;
        }
    };

}

#endif //C_ENG_WINDOWMOVEEVENT_HPP

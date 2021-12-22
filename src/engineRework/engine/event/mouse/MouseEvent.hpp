//
// Created by loghin on 20.12.2021.
//

#ifndef C_ENG_MOUSEEVENT_HPP
#define C_ENG_MOUSEEVENT_HPP


#include <Event.hpp>

namespace engine {

    class C_ENG_CLASS ( MouseEvent ) : public C_ENG_CLASS ( Event ) {

        C_ENG_CLASS_IMMUTABLE_FIELD ( Position, position, 0u, 0u )

    protected:
        C_ENG_CONSTRUCTOR ( MouseEvent ) (
                C_ENG_TYPE ( Window ) * window,
                Position        const & position
        ) noexcept :
                C_ENG_CONSTRUCTOR ( Event ) ( window ),
                _position ( position ) {

        }

    public:
        C_ENG_DESTRUCTOR ( MouseEvent ) () noexcept override = default;

        C_ENG_NO_DISCARD constexpr auto type () const noexcept -> EventType override {
            return EventType :: EventTypeCustomMouseEvent;
        }
    };

}


#endif //C_ENG_MOUSEEVENT_HPP

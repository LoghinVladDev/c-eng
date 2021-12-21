//
// Created by loghin on 20.12.2021.
//

#ifndef C_ENG_MOUSEMOVEEVENT_HPP
#define C_ENG_MOUSEMOVEEVENT_HPP

#include <MouseEvent.hpp>

namespace engine {

    class C_ENG_CLASS ( MouseMoveEvent ) : public C_ENG_CLASS ( MouseEvent ) {
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint32, oldX, 0U )
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint32, oldY, 0U )

    public:
        C_ENG_CONSTRUCTOR ( MouseMoveEvent ) (
                cds :: uint32           x,
                cds :: uint32           y,
                cds :: uint32           oldX,
                cds :: uint32           oldY,

                C_ENG_TYPE ( Window ) * window
        ) noexcept :
                C_ENG_CONSTRUCTOR ( MouseEvent ) (
                        x,
                        y,
                        window
                ),
                _oldX ( oldX ),
                _oldY ( oldY ) {


        }

        C_ENG_DESTRUCTOR ( MouseMoveEvent ) () noexcept override = default;

        C_ENG_NO_DISCARD constexpr auto type () const noexcept -> EventType override {
            return EventType :: EventTypeMousePressEvent;
        }
    };

}

#endif //C_ENG_MOUSEMOVEEVENT_HPP

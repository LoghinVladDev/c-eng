//
// Created by loghin on 20.12.2021.
//

#ifndef C_ENG_MOUSEEVENT_HPP
#define C_ENG_MOUSEEVENT_HPP


#include <Event.hpp>

namespace engine {

    class C_ENG_CLASS ( MouseEvent ) : public C_ENG_CLASS ( Event ) {

        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint32, x, 0U )
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint32, y, 0U )

    protected:
        C_ENG_CONSTRUCTOR ( MouseEvent ) (
                cds :: uint32           x,
                cds :: uint32           y,
                C_ENG_TYPE ( Window ) * window
        ) noexcept :
                C_ENG_CONSTRUCTOR ( Event ) ( window ),
                _x ( x ),
                _y ( y ) {

        }

        C_ENG_DESTRUCTOR ( MouseEvent ) () noexcept override = default;

    public:
        C_ENG_NO_DISCARD constexpr auto type () const noexcept -> EventType override {
            return EventType :: EventTypeCustomMouseEvent;
        }
    };

}


#endif //C_ENG_MOUSEEVENT_HPP

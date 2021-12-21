//
// Created by loghin on 20.12.2021.
//

#ifndef C_ENG_MOUSESCROLLEVENT_HPP
#define C_ENG_MOUSESCROLLEVENT_HPP

#include <MouseEvent.hpp>

namespace engine {

    class C_ENG_CLASS ( MouseScrollEvent ) : public C_ENG_CLASS ( MouseEvent ) {
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( double, yOffset, 0.0 )

    public:
        C_ENG_DESTRUCTOR ( MouseScrollEvent ) () noexcept override = default;

        C_ENG_CONSTRUCTOR ( MouseScrollEvent ) (
                cds :: uint32           x,
                cds :: uint32           y,
                double                  yOffset,
                C_ENG_TYPE ( Window ) * window
        ) noexcept :
                C_ENG_CONSTRUCTOR ( MouseEvent ) (
                        x,
                        y,
                        window
                ),
                _yOffset ( yOffset ) {

        }

        C_ENG_NO_DISCARD constexpr auto type () const noexcept -> EventType override {
            return EventType :: EventTypeMouseScrollEvent;
        }
    };

}


#endif //C_ENG_MOUSESCROLLEVENT_HPP

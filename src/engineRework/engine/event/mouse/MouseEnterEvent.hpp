//
// Created by loghin on 20.12.2021.
//

#ifndef C_ENG_MOUSEENTEREVENT_HPP
#define C_ENG_MOUSEENTEREVENT_HPP

#include <MouseEvent.hpp>

namespace engine {

    class C_ENG_CLASS ( MouseEnterEvent ) : public C_ENG_CLASS ( MouseEvent ) {
    public:
        C_ENG_DESTRUCTOR ( MouseEnterEvent ) () noexcept override = default;

        C_ENG_CONSTRUCTOR ( MouseEnterEvent ) (
                cds :: uint32           x,
                cds :: uint32           y,
                C_ENG_TYPE ( Window ) * window
        ) noexcept :
                C_ENG_CONSTRUCTOR ( MouseEvent ) (
                        x,
                        y,
                        window
                ) {

        }

        C_ENG_NO_DISCARD constexpr auto type () const noexcept -> EventType override {
            return EventType :: EventTypeMouseEnterEvent;
        }
    };

}

#endif //C_ENG_MOUSEENTEREVENT_HPP

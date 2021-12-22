//
// Created by loghin on 21.12.2021.
//

#ifndef C_ENG_WINDOWMAXIMIZEEVENT_HPP
#define C_ENG_WINDOWMAXIMIZEEVENT_HPP


#include <WindowEvent.hpp>

namespace engine {

    class C_ENG_CLASS ( WindowMaximizeEvent ) : public C_ENG_CLASS ( WindowEvent ) {

    public:
        C_ENG_DESTRUCTOR ( WindowMaximizeEvent ) () noexcept override = default;

        explicit C_ENG_CONSTRUCTOR ( WindowMaximizeEvent ) (
                C_ENG_TYPE ( Window ) * window
        ) noexcept :
                C_ENG_CONSTRUCTOR ( WindowEvent ) ( window ) {

        }

    public:
        C_ENG_NO_DISCARD constexpr auto type () const noexcept -> EventType override {
            return EventType :: EventTypeWindowMaximizeEvent;
        }
    };

}


#endif //C_ENG_WINDOWMAXIMIZEEVENT_HPP

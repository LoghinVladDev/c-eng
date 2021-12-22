//
// Created by loghin on 20.12.2021.
//

#ifndef C_ENG_WINDOWRESIZEEVENT_HPP
#define C_ENG_WINDOWRESIZEEVENT_HPP


#include <WindowEvent.hpp>

namespace engine {

    class C_ENG_CLASS ( WindowResizeEvent ) : public C_ENG_CLASS ( WindowEvent ) {

        C_ENG_CLASS_IMMUTABLE_FIELD ( RectangleSize, size, 0u, 0u )
        C_ENG_CLASS_IMMUTABLE_FIELD ( RectangleSize, oldSize, 0u, 0u )

    public:
        C_ENG_DESTRUCTOR ( WindowResizeEvent ) () noexcept override = default;

        C_ENG_CONSTRUCTOR ( WindowResizeEvent ) (
                C_ENG_TYPE ( Window ) * window,
                RectangleSize   const & size,
                RectangleSize   const & oldSize
        ) noexcept :
                C_ENG_CONSTRUCTOR ( WindowEvent ) ( window ),
                _size ( size ),
                _oldSize ( oldSize ) {

        }

    public:
        C_ENG_NO_DISCARD constexpr auto type () const noexcept -> EventType override {
            return EventType :: EventTypeWindowResizeEvent;
        }
    };

}


#endif //C_ENG_WINDOWRESIZEEVENT_HPP

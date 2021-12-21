//
// Created by loghin on 20.12.2021.
//

#ifndef C_ENG_RESIZEEVENT_HPP
#define C_ENG_RESIZEEVENT_HPP


#include <Event.hpp>

namespace engine {

    class C_ENG_CLASS ( ResizeEvent ) : public C_ENG_CLASS ( Event ) {

        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint32, width, 0u )
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint32, height, 0u )

        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint32, oldWidth, 0u )
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint32, oldHeight, 0u )

    public:
        C_ENG_DESTRUCTOR ( ResizeEvent ) () noexcept override = default;

        C_ENG_CONSTRUCTOR ( ResizeEvent ) (
                cds :: uint32           width,
                cds :: uint32           height,
                cds :: uint32           oldWidth,
                cds :: uint32           oldHeight,

                C_ENG_TYPE ( Window ) * window
        ) noexcept :
                C_ENG_CONSTRUCTOR ( Event ) ( window ),
                _width ( width ),
                _height ( height ),
                _oldWidth ( oldWidth ),
                _oldHeight ( oldHeight ) {

        }

    public:
        C_ENG_NO_DISCARD constexpr auto type () const noexcept -> EventType override {
            return EventType :: EventTypeResizeEvent;
        }
    };

}


#endif //C_ENG_RESIZEEVENT_HPP

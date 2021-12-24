//
// Created by loghin on 21.12.2021.
//

#ifndef C_ENG_WINDOWFRAMEBUFFERRESIZEEVENT_HPP
#define C_ENG_WINDOWFRAMEBUFFERRESIZEEVENT_HPP


#include <WindowEvent.hpp>

namespace engine {

    class C_ENG_CLASS ( WindowFrameBufferResizeEvent ) : public C_ENG_CLASS ( WindowEvent ) {

    C_ENG_CLASS_IMMUTABLE_FIELD ( RectangleSize, size, 0u, 0u )
    C_ENG_CLASS_IMMUTABLE_FIELD ( RectangleSize, oldSize, 0u, 0u )

    public:
        C_ENG_DESTRUCTOR ( WindowFrameBufferResizeEvent ) () noexcept override = default;

        C_ENG_CONSTRUCTOR ( WindowFrameBufferResizeEvent ) (
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
            return EventType :: EventTypeWindowFrameBufferResizeEvent;
        }

        C_ENG_NO_DISCARD inline auto copy () const noexcept -> C_ENG_TYPE ( WindowFrameBufferResizeEvent ) * override {
            return new C_ENG_TYPE ( WindowFrameBufferResizeEvent ) ( * this );
        }

        C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
        C_ENG_NO_DISCARD auto equals ( cds :: Object const & ) const noexcept -> bool override;
    };

}


#endif //C_ENG_WINDOWFRAMEBUFFERRESIZEEVENT_HPP

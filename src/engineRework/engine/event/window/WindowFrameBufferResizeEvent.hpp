//
// Created by loghin on 21.12.2021.
//

#ifndef __C_ENG_WINDOWFRAMEBUFFERRESIZEEVENT_HPP
#define __C_ENG_WINDOWFRAMEBUFFERRESIZEEVENT_HPP


#include <WindowEvent.hpp>

namespace engine {

    __C_ENG_CLASS ( WindowFrameBufferResizeEvent ) : public __C_ENG_TYPE ( WindowEvent ) {

        __C_ENG_CLASS_IMMUTABLE_FIELD ( __C_ENG_TYPE ( Size ), size, 0u, 0u )
        __C_ENG_CLASS_IMMUTABLE_FIELD ( __C_ENG_TYPE ( Size ), oldSize, 0u, 0u )

    public:
        __C_ENG_DESTRUCTOR ( WindowFrameBufferResizeEvent ) () noexcept override = default;

        __C_ENG_CONSTRUCTOR ( WindowFrameBufferResizeEvent ) (
                __C_ENG_TYPE ( Window )       * window,
                __C_ENG_TYPE ( Size )   const & size,
                __C_ENG_TYPE ( Size )   const & oldSize
        ) noexcept :
                __C_ENG_CONSTRUCTOR ( WindowEvent ) ( window ),
                _size ( size ),
                _oldSize ( oldSize ) {

        }

    public:
        __C_ENG_NO_DISCARD constexpr auto type () const noexcept -> __C_ENG_TYPE ( EventType ) override {
            return __C_ENG_TYPE ( EventType ) :: EventTypeWindowFrameBufferResizeEvent;
        }

        __C_ENG_NO_DISCARD inline auto copy () const noexcept -> __C_ENG_TYPE ( WindowFrameBufferResizeEvent ) * override {
            return new __C_ENG_TYPE ( WindowFrameBufferResizeEvent ) ( * this );
        }

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
        __C_ENG_NO_DISCARD auto equals ( cds :: Object const & ) const noexcept -> bool override;
    };

}


#endif //__C_ENG_WINDOWFRAMEBUFFERRESIZEEVENT_HPP

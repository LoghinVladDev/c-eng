//
// Created by loghin on 20.12.2021.
//

#ifndef __C_ENG_WINDOWRESIZEEVENT_HPP
#define __C_ENG_WINDOWRESIZEEVENT_HPP


#include <WindowEvent.hpp>

namespace engine {

    __C_ENG_CLASS ( WindowResizeEvent ) : public __C_ENG_TYPE ( WindowEvent ) {

        __C_ENG_CLASS_IMMUTABLE_FIELD ( __C_ENG_TYPE ( Size ), size, 0u, 0u )
        __C_ENG_CLASS_IMMUTABLE_FIELD ( __C_ENG_TYPE ( Size ), oldSize, 0u, 0u )

    public:
        __C_ENG_DESTRUCTOR ( WindowResizeEvent ) () noexcept override = default;

        __C_ENG_CONSTRUCTOR ( WindowResizeEvent ) (
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
            return __C_ENG_TYPE ( EventType ) :: EventTypeWindowResizeEvent;
        }

        __C_ENG_NO_DISCARD inline auto copy () const noexcept -> __C_ENG_TYPE ( WindowResizeEvent ) * override {
            return new __C_ENG_TYPE ( WindowResizeEvent ) ( * this );
        }

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
        __C_ENG_NO_DISCARD auto equals ( cds :: Object const & ) const noexcept -> bool override;
    };

}


#endif //__C_ENG_WINDOWRESIZEEVENT_HPP

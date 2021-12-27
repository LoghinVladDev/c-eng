//
// Created by loghin on 20.12.2021.
//

#ifndef __C_ENG_MOUSEMOVEEVENT_HPP
#define __C_ENG_MOUSEMOVEEVENT_HPP

#include <MouseEvent.hpp>

namespace engine {

    __C_ENG_CLASS ( MouseMoveEvent ) : public __C_ENG_TYPE ( MouseEvent ) {
        __C_ENG_CLASS_IMMUTABLE_FIELD ( __C_ENG_TYPE ( Position ), oldPosition, 0u, 0u )

    public:
        __C_ENG_CONSTRUCTOR ( MouseMoveEvent ) (
                __C_ENG_TYPE ( Window )           * window,
                __C_ENG_TYPE ( Position )   const & position,
                __C_ENG_TYPE ( Position )   const & oldPosition
        ) noexcept :
                __C_ENG_CONSTRUCTOR ( MouseEvent ) (
                        window,
                        position
                ),
                _oldPosition ( oldPosition ) {


        }

        __C_ENG_DESTRUCTOR ( MouseMoveEvent ) () noexcept override = default;

        __C_ENG_NO_DISCARD constexpr auto type () const noexcept -> __C_ENG_TYPE ( EventType ) override {
            return __C_ENG_TYPE ( EventType ) :: EventTypeMousePressEvent;
        }

        __C_ENG_NO_DISCARD inline auto copy () const noexcept -> __C_ENG_TYPE ( MouseMoveEvent ) * override {
            return new __C_ENG_TYPE ( MouseMoveEvent ) ( * this );
        }

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
        __C_ENG_NO_DISCARD auto equals ( cds :: Object const & ) const noexcept -> bool override;
    };

}

#endif //__C_ENG_MOUSEMOVEEVENT_HPP

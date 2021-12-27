//
// Created by loghin on 21.12.2021.
//

#ifndef __C_ENG_WINDOWMOVEEVENT_HPP
#define __C_ENG_WINDOWMOVEEVENT_HPP


#include <WindowEvent.hpp>

namespace engine {

    __C_ENG_CLASS ( WindowMoveEvent ) : public __C_ENG_TYPE ( WindowEvent ) {
        __C_ENG_CLASS_IMMUTABLE_FIELD ( __C_ENG_TYPE ( Position ), position, 0u, 0u )
        __C_ENG_CLASS_IMMUTABLE_FIELD ( __C_ENG_TYPE ( Position ), oldPosition, 0u, 0u )

    public:
        __C_ENG_DESTRUCTOR ( WindowMoveEvent ) () noexcept override = default;

        __C_ENG_CONSTRUCTOR ( WindowMoveEvent ) (
                __C_ENG_TYPE ( Window )           * window,
                __C_ENG_TYPE ( Position )   const & position,
                __C_ENG_TYPE ( Position )   const & oldPosition
        ) noexcept :
                __C_ENG_CONSTRUCTOR ( WindowEvent ) ( window ),
                _position ( position ),
                _oldPosition ( oldPosition ) {

        }

        __C_ENG_NO_DISCARD constexpr auto type () const noexcept -> __C_ENG_TYPE ( EventType ) override {
            return __C_ENG_TYPE ( EventType ) :: EventTypeWindowMoveEvent;
        }

        __C_ENG_NO_DISCARD inline auto copy () const noexcept -> __C_ENG_TYPE ( WindowMoveEvent ) * override {
            return new __C_ENG_TYPE ( WindowMoveEvent ) ( * this );
        }

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
        __C_ENG_NO_DISCARD auto equals ( cds :: Object const & ) const noexcept -> bool override;
    };

}

#endif //__C_ENG_WINDOWMOVEEVENT_HPP

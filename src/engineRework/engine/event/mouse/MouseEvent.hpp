//
// Created by loghin on 20.12.2021.
//

#ifndef __C_ENG_MOUSEEVENT_HPP
#define __C_ENG_MOUSEEVENT_HPP


#include <Event.hpp>

namespace engine {

    __C_ENG_CLASS ( MouseEvent ) : public __C_ENG_TYPE ( Event ) {

        __C_ENG_CLASS_IMMUTABLE_FIELD ( __C_ENG_TYPE ( Position ), position, 0u, 0u )

    protected:
        __C_ENG_CONSTRUCTOR ( MouseEvent ) (
                __C_ENG_TYPE ( Window )           * window,
                __C_ENG_TYPE ( Position )   const & position
        ) noexcept :
                __C_ENG_CONSTRUCTOR ( Event ) ( window ),
                _position ( position ) {

        }

    public:
        __C_ENG_DESTRUCTOR ( MouseEvent ) () noexcept override = default;

        __C_ENG_NO_DISCARD constexpr auto type () const noexcept -> __C_ENG_TYPE ( EventType ) override {
            return __C_ENG_TYPE ( EventType ) :: EventTypeCustomMouseEvent;
        }

        __C_ENG_NO_DISCARD auto copy () const noexcept -> __C_ENG_TYPE ( MouseEvent ) * override = 0;

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
        __C_ENG_NO_DISCARD auto equals ( cds :: Object const & ) const noexcept -> bool override;
    };

}


#endif //__C_ENG_MOUSEEVENT_HPP

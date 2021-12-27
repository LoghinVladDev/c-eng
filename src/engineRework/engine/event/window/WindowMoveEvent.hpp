//
// Created by loghin on 21.12.2021.
//

#ifndef __C_ENG_WINDOWMOVEEVENT_HPP
#define __C_ENG_WINDOWMOVEEVENT_HPP


#include <WindowEvent.hpp>

namespace engine {


#pragma push_macro ("__C_ENG_OBJECT_NAME")

#undef __C_ENG_OBJECT_NAME
#define __C_ENG_OBJECT_NAME WindowMoveEvent /* NOLINT(bugprone-reserved-identifier) */


    __C_ENG_CLASS : public __C_ENG_TYPE ( WindowEvent ) {
        __C_ENG_CLASS_IMMUTABLE_FIELD ( __C_ENG_TYPE ( Position ), position, 0u, 0u )
        __C_ENG_CLASS_IMMUTABLE_FIELD ( __C_ENG_TYPE ( Position ), oldPosition, 0u, 0u )

    public:
        __C_ENG_DESTRUCTOR () noexcept override = default;

        __C_ENG_CONSTRUCTOR (
                __C_ENG_TYPE ( Window )           * window,
                __C_ENG_TYPE ( Position )   const & position,
                __C_ENG_TYPE ( Position )   const & oldPosition
        ) noexcept :
                __C_ENG_TYPE ( WindowEvent ) ( window ),
                _position ( position ),
                _oldPosition ( oldPosition ) {

        }

        __C_ENG_NO_DISCARD constexpr auto type () const noexcept -> __C_ENG_TYPE ( EventType ) override {
            return __C_ENG_TYPE ( EventType ) :: EventTypeWindowMoveEvent;
        }

        __C_ENG_NO_DISCARD inline auto copy () const noexcept -> __C_ENG_SELF * override {
            return new __C_ENG_SELF ( * this );
        }

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
        __C_ENG_NO_DISCARD auto equals ( cds :: Object const & ) const noexcept -> bool override;
    };

#pragma pop_macro ("__C_ENG_OBJECT_NAME")
    

}

#endif //__C_ENG_WINDOWMOVEEVENT_HPP

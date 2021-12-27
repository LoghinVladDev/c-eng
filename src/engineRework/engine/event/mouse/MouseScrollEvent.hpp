//
// Created by loghin on 20.12.2021.
//

#ifndef __C_ENG_MOUSESCROLLEVENT_HPP
#define __C_ENG_MOUSESCROLLEVENT_HPP

#include <MouseEvent.hpp>

namespace engine {


#pragma push_macro ("__C_ENG_OBJECT_NAME")

#undef __C_ENG_OBJECT_NAME
#define __C_ENG_OBJECT_NAME MouseScrollEvent /* NOLINT(bugprone-reserved-identifier) */

    __C_ENG_CLASS : public __C_ENG_TYPE ( MouseEvent ) {
        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( double, xOffset, 0.0 )
        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( double, yOffset, 0.0 )

    public:
        __C_ENG_DESTRUCTOR () noexcept override = default;

        __C_ENG_CONSTRUCTOR (
                __C_ENG_TYPE ( Window )           * window,
                __C_ENG_TYPE ( Position )   const & position,
                double                              xOffset,
                double                              yOffset
        ) noexcept :
                __C_ENG_TYPE ( MouseEvent ) (
                        window,
                        position
                ),
                _xOffset ( xOffset ),
                _yOffset ( yOffset ) {

        }

        __C_ENG_NO_DISCARD constexpr auto type () const noexcept -> __C_ENG_TYPE ( EventType ) override {
            return __C_ENG_TYPE ( EventType ) :: EventTypeMouseScrollEvent;
        }

        __C_ENG_NO_DISCARD inline auto copy () const noexcept -> __C_ENG_SELF * override {
            return new __C_ENG_SELF ( * this );
        }

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
        __C_ENG_NO_DISCARD auto equals ( cds :: Object const & ) const noexcept -> bool override;
    };

#pragma pop_macro ("__C_ENG_OBJECT_NAME")


}


#endif //__C_ENG_MOUSESCROLLEVENT_HPP

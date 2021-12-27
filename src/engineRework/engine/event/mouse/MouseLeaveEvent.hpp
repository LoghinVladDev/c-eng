//
// Created by loghin on 20.12.2021.
//

#ifndef __C_ENG_MOUSELEAVEEVENT_HPP
#define __C_ENG_MOUSELEAVEEVENT_HPP


#include <MouseEvent.hpp>

namespace engine {

    __C_ENG_CLASS ( MouseLeaveEvent ) : public __C_ENG_TYPE ( MouseEvent ) {
    public:
        __C_ENG_DESTRUCTOR ( MouseLeaveEvent ) () noexcept override = default;

        __C_ENG_CONSTRUCTOR ( MouseLeaveEvent ) (
                __C_ENG_TYPE ( Window )           * window,
                __C_ENG_TYPE ( Position )   const & position
        ) noexcept :
                __C_ENG_CONSTRUCTOR ( MouseEvent ) (
                        window,
                        position
                ) {

        }

        __C_ENG_NO_DISCARD constexpr auto type () const noexcept -> __C_ENG_TYPE ( EventType ) override {
            return __C_ENG_TYPE ( EventType ) :: EventTypeMouseLeaveEvent;
        }

        __C_ENG_NO_DISCARD inline auto copy () const noexcept -> __C_ENG_TYPE ( MouseLeaveEvent ) * override {
            return new __C_ENG_TYPE ( MouseLeaveEvent ) ( * this );
        }

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

}


#endif //__C_ENG_MOUSELEAVEEVENT_HPP

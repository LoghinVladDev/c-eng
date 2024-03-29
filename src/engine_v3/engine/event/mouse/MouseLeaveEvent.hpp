//
// Created by loghin on 20.12.2021.
//

#ifndef __C_ENG_MOUSE_LEAVE_EVENT_HPP__
#define __C_ENG_MOUSE_LEAVE_EVENT_HPP__


#include <MouseEvent.hpp>


#define C_ENG_MAP_START     CLASS ( MouseLeaveEvent, ENGINE_PARENT ( MouseEvent ) )
#include <ObjectMapping.hpp>

namespace engine {

    Class {
    public:
        Destructor () noexcept override = default;

        Constructor (
                __C_ENG_TYPE ( Window )           * window,
                __C_ENG_TYPE ( Position )   const & position
        ) noexcept :
                Parent (
                        window,
                        position
                ) {

        }

        __C_ENG_NO_DISCARD constexpr auto type () const noexcept -> __C_ENG_TYPE ( EventType ) override {
            return __C_ENG_TYPE ( EventType ) :: EventTypeMouseLeaveEvent;
        }

        __C_ENG_NO_DISCARD inline auto copy () const noexcept -> Self * override {
            return new Self ( * this );
        }

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //__C_ENG_MOUSE_LEAVE_EVENT_HPP__

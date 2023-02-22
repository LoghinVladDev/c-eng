//
// Created by loghin on 21.12.2021.
//

#ifndef __C_ENG_WINDOW_REFRESH_REQUEST_EVENT_HPP__
#define __C_ENG_WINDOW_REFRESH_REQUEST_EVENT_HPP__


#include <WindowEvent.hpp>


#define C_ENG_MAP_START     CLASS ( WindowRefreshRequestEvent, ENGINE_PARENT ( WindowEvent ) )
#include <ObjectMapping.hpp>

namespace engine {

    Class {
    public:
        Destructor () noexcept override = default;

        explicit Constructor (
                __C_ENG_TYPE ( Window ) * window
        ) noexcept :
                Parent ( window ) {

        }

        __C_ENG_NO_DISCARD constexpr auto type () const noexcept -> __C_ENG_TYPE ( EventType ) override {
            return __C_ENG_TYPE ( EventType ) :: EventTypeWindowRefreshRequestEvent;
        }

        __C_ENG_NO_DISCARD inline auto copy () const noexcept -> Self * override {
            return new Self ( * this );
        }

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //__C_ENG_WINDOW_REFRESH_REQUEST_EVENT_HPP__

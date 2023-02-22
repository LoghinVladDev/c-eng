//
// Created by loghin on 22.12.2021.
//

#ifndef __C_ENG_CONTROLLER_CONNECT_EVENT_HPP__
#define __C_ENG_CONTROLLER_CONNECT_EVENT_HPP__

#include <ControllerEvent.hpp>


#define C_ENG_MAP_START     CLASS ( ControllerConnectEvent, ENGINE_PARENT ( ControllerEvent ) )
#include <ObjectMapping.hpp>

namespace engine {

    Class {
    public:
        explicit Constructor (
                __C_ENG_TYPE ( Controller ) * controller
        ) noexcept :
                Parent ( nullptr ) {

        }

        Destructor () noexcept override = default;

        __C_ENG_NO_DISCARD constexpr auto type () const noexcept -> __C_ENG_TYPE ( EventType ) override {
            return __C_ENG_TYPE ( EventType ) :: EventTypeControllerConnectEvent;
        }

        __C_ENG_NO_DISCARD inline auto copy () const noexcept -> Self * override {
            return new Self ( * this );
        }

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //__C_ENG_CONTROLLER_CONNECT_EVENT_HPP__

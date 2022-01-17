//
// Created by loghin on 21.12.2021.
//

#ifndef __C_ENG_WINDOW_EVENT_HPP__
#define __C_ENG_WINDOW_EVENT_HPP__


#include <Event.hpp>


#define C_ENG_MAP_START     CLASS ( WindowEvent, ENGINE_PARENT ( Event ) )
#include <ObjectMapping.hpp>

namespace engine {

    Class {
    protected:
        explicit Constructor (
                __C_ENG_TYPE ( Window ) * window
        ) noexcept :
                Parent ( window ) {

        }

    public:
        Destructor () noexcept override = default;

        __C_ENG_NO_DISCARD constexpr auto type () const noexcept -> __C_ENG_TYPE ( EventType ) override {
            return __C_ENG_TYPE ( EventType ) :: EventTypeCustomWindowEvent;
        }

        __C_ENG_NO_DISCARD auto copy () const noexcept -> Self * override = 0;

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //__C_ENG_WINDOW_EVENT_HPP__

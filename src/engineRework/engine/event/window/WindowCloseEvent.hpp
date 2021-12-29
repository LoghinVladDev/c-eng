//
// Created by loghin on 21.12.2021.
//

#ifndef __C_ENG_WINDOWCLOSEEVENT_HPP
#define __C_ENG_WINDOWCLOSEEVENT_HPP


#include <WindowEvent.hpp>


#define C_ENG_MAP_START     CLASS ( WindowCloseEvent, ENGINE_PARENT ( WindowEvent ) )
#include <ObjectMapping.hpp>

namespace engine {

    Class {
        __C_ENG_CLASS_MUTABLE_PRIMITIVE_FIELD ( bool, cancelClose, false )

    public:
        Destructor () noexcept override = default;

        explicit Constructor (
                __C_ENG_TYPE ( Window ) * window
        ) noexcept :
                Parent ( window ) {

        }

        __C_ENG_NO_DISCARD constexpr auto type () const noexcept -> __C_ENG_TYPE ( EventType ) override {
            return __C_ENG_TYPE ( EventType ) :: EventTypeWindowCloseEvent;
        }

        __C_ENG_NO_DISCARD inline auto copy () const noexcept -> Self * override {
            return new Self ( * this );
        }

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //__C_ENG_WINDOWCLOSEEVENT_HPP

//
// Created by loghin on 21.12.2021.
//

#ifndef __C_ENG_WINDOWCLOSEEVENT_HPP
#define __C_ENG_WINDOWCLOSEEVENT_HPP


#include <WindowEvent.hpp>

namespace engine {

    __C_ENG_CLASS ( WindowCloseEvent ) : public __C_ENG_TYPE ( WindowEvent ) {
        __C_ENG_CLASS_MUTABLE_PRIMITIVE_FIELD ( bool, cancelClose, false )

    public:
        __C_ENG_DESTRUCTOR ( WindowCloseEvent ) () noexcept override = default;

        explicit __C_ENG_CONSTRUCTOR ( WindowCloseEvent ) (
                __C_ENG_TYPE ( Window ) * window
        ) noexcept :
                __C_ENG_CONSTRUCTOR ( WindowEvent ) ( window ) {

        }

        __C_ENG_NO_DISCARD constexpr auto type () const noexcept -> __C_ENG_TYPE ( EventType ) override {
            return __C_ENG_TYPE ( EventType ) :: EventTypeWindowCloseEvent;
        }

        __C_ENG_NO_DISCARD inline auto copy () const noexcept -> __C_ENG_TYPE ( WindowCloseEvent ) * override {
            return new __C_ENG_TYPE ( WindowCloseEvent ) ( * this );
        }

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

}


#endif //__C_ENG_WINDOWCLOSEEVENT_HPP

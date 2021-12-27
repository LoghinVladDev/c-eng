//
// Created by loghin on 21.12.2021.
//

#ifndef __C_ENG_WINDOWRESTOREEVENT_HPP
#define __C_ENG_WINDOWRESTOREEVENT_HPP


#include <WindowEvent.hpp>

namespace engine {

    __C_ENG_CLASS ( WindowRestoreEvent ) : public __C_ENG_TYPE ( WindowEvent ) {

    public:
        __C_ENG_DESTRUCTOR ( WindowRestoreEvent ) () noexcept override = default;

        explicit __C_ENG_CONSTRUCTOR ( WindowRestoreEvent ) (
                __C_ENG_TYPE ( Window ) * window
        ) noexcept :
                __C_ENG_CONSTRUCTOR ( WindowEvent ) ( window ) {

        }

    public:
        __C_ENG_NO_DISCARD constexpr auto type () const noexcept -> __C_ENG_TYPE ( EventType ) override {
            return __C_ENG_TYPE ( EventType ) :: EventTypeWindowRestoreEvent;
        }

        __C_ENG_NO_DISCARD inline auto copy () const noexcept -> __C_ENG_TYPE ( WindowRestoreEvent ) * override {
            return new __C_ENG_TYPE ( WindowRestoreEvent ) ( * this );
        }

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

}


#endif //__C_ENG_WINDOWRESTOREEVENT_HPP

//
// Created by loghin on 21.12.2021.
//

#ifndef __C_ENG_WINDOWEVENT_HPP
#define __C_ENG_WINDOWEVENT_HPP


#include <Event.hpp>

namespace engine {

    __C_ENG_CLASS ( WindowEvent ) : public __C_ENG_TYPE ( Event ) {
    protected:
        explicit __C_ENG_CONSTRUCTOR ( WindowEvent ) (
                __C_ENG_TYPE ( Window ) * window
        ) noexcept :
                __C_ENG_CONSTRUCTOR ( Event ) ( window ) {

        }

    public:
        __C_ENG_DESTRUCTOR ( WindowEvent ) () noexcept override = default;

        __C_ENG_NO_DISCARD constexpr auto type () const noexcept -> __C_ENG_TYPE ( EventType ) override {
            return __C_ENG_TYPE ( EventType ) :: EventTypeCustomWindowEvent;
        }

        __C_ENG_NO_DISCARD auto copy () const noexcept -> __C_ENG_TYPE ( WindowEvent ) * override = 0;

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

}

#endif //__C_ENG_WINDOWEVENT_HPP

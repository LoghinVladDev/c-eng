//
// Created by loghin on 22.12.2021.
//

#ifndef __C_ENG_CONTROLLERCONNECTEVENT_HPP
#define __C_ENG_CONTROLLERCONNECTEVENT_HPP

#include <ControllerEvent.hpp>

namespace engine {


#pragma push_macro ("__C_ENG_OBJECT_NAME")

#undef __C_ENG_OBJECT_NAME
#define __C_ENG_OBJECT_NAME ControllerConnectEvent /* NOLINT(bugprone-reserved-identifier) */

    __C_ENG_CLASS : public __C_ENG_TYPE ( ControllerEvent ) {
    public:
        explicit __C_ENG_CONSTRUCTOR (
                __C_ENG_TYPE ( Controller ) * controller
        ) noexcept :
                __C_ENG_TYPE ( ControllerEvent ) ( nullptr ) {

        }

        __C_ENG_DESTRUCTOR () noexcept override = default;

        __C_ENG_NO_DISCARD constexpr auto type () const noexcept -> __C_ENG_TYPE ( EventType ) override {
            return __C_ENG_TYPE ( EventType ) :: EventTypeControllerConnectEvent;
        }

        __C_ENG_NO_DISCARD inline auto copy () const noexcept -> __C_ENG_SELF * override {
            return new __C_ENG_SELF ( * this );
        }

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

#pragma pop_macro ("__C_ENG_OBJECT_NAME")
    

}


#endif //__C_ENG_CONTROLLERCONNECTEVENT_HPP

//
// Created by loghin on 22.12.2021.
//

#ifndef __C_ENG_CONTROLLEREVENT_HPP
#define __C_ENG_CONTROLLEREVENT_HPP


#include <Event.hpp>

namespace engine {

    __C_ENG_CLASS ( Controller );

    __C_ENG_CLASS ( ControllerEvent ) : public __C_ENG_TYPE ( Event ) {
    private:
        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( __C_ENG_TYPE ( Controller ) *, controller, nullptr );

    public:
        explicit __C_ENG_CONSTRUCTOR ( ControllerEvent ) (
                __C_ENG_TYPE ( Controller ) * controller
        ) noexcept :
                __C_ENG_CONSTRUCTOR ( Event ) ( nullptr ),
                _controller ( controller ) {

        }

        __C_ENG_DESTRUCTOR ( ControllerEvent ) () noexcept override = default;

        __C_ENG_NO_DISCARD constexpr auto type () const noexcept -> __C_ENG_TYPE ( EventType ) override {
            return __C_ENG_TYPE ( EventType ) :: EventTypeCustomControllerEvent;
        }

        __C_ENG_NO_DISCARD auto copy () const noexcept -> __C_ENG_TYPE ( ControllerEvent ) * override = 0;

        __C_ENG_NO_DISCARD auto hash () const noexcept -> cds :: Index override;
        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;

        __C_ENG_NO_DISCARD auto equals ( cds :: Object const & ) const noexcept -> bool override;
    };

}


#endif //__C_ENG_CONTROLLEREVENT_HPP

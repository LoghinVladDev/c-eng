//
// Created by loghin on 22.12.2021.
//

#ifndef C_ENG_CONTROLLEREVENT_HPP
#define C_ENG_CONTROLLEREVENT_HPP


#include <Event.hpp>

namespace engine {

    class C_ENG_CLASS ( Controller );

    class C_ENG_CLASS ( ControllerEvent ) : public C_ENG_CLASS ( Event ) {
    private:
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( C_ENG_TYPE ( Controller ) *, controller, nullptr );

    public:
        explicit C_ENG_CONSTRUCTOR ( ControllerEvent ) (
                C_ENG_TYPE ( Controller ) * controller
        ) noexcept :
                C_ENG_CONSTRUCTOR ( Event ) ( nullptr ),
                _controller ( controller ) {

        }

        C_ENG_DESTRUCTOR ( ControllerEvent ) () noexcept override = default;

        C_ENG_NO_DISCARD constexpr auto type () const noexcept -> EventType override {
            return EventType :: EventTypeCustomControllerEvent;
        }

        C_ENG_NO_DISCARD auto copy () const noexcept -> C_ENG_TYPE ( ControllerEvent ) * override = 0;

        C_ENG_NO_DISCARD auto hash () const noexcept -> cds :: Index override;
        C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;

        C_ENG_NO_DISCARD auto equals ( cds :: Object const & ) const noexcept -> bool override;
    };

}


#endif //C_ENG_CONTROLLEREVENT_HPP

//
// Created by loghin on 21.12.2021.
//

#ifndef C_ENG_WINDOWEVENT_HPP
#define C_ENG_WINDOWEVENT_HPP


#include <Event.hpp>

namespace engine {

    class C_ENG_CLASS ( WindowEvent ) : public C_ENG_CLASS ( Event ) {
    protected:
        explicit C_ENG_CONSTRUCTOR ( WindowEvent ) (
                C_ENG_TYPE ( Window ) * window
        ) noexcept :
                C_ENG_CONSTRUCTOR ( Event ) ( window ) {

        }

    public:
        C_ENG_DESTRUCTOR ( WindowEvent ) () noexcept override = default;

        C_ENG_NO_DISCARD constexpr auto type () const noexcept -> EventType override {
            return EventType :: EventTypeCustomWindowEvent;
        }
    };

}

#endif //C_ENG_WINDOWEVENT_HPP

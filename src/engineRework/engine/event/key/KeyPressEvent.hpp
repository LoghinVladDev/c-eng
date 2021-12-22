//
// Created by loghin on 20.12.2021.
//

#ifndef C_ENG_KEYPRESSEVENT_HPP
#define C_ENG_KEYPRESSEVENT_HPP

#include <KeyEvent.hpp>

namespace engine {

    class C_ENG_CLASS ( KeyPressEvent ) : public C_ENG_CLASS ( KeyEvent ) {
    public:
        C_ENG_DESTRUCTOR ( KeyPressEvent ) () noexcept override = default;

        C_ENG_CONSTRUCTOR ( KeyPressEvent ) (
                C_ENG_TYPE ( Window ) * window,
                Key                     key,
                KeyModifiers            modifiers
        ) noexcept :
                C_ENG_CONSTRUCTOR ( KeyEvent ) (
                        window,
                        key,
                        modifiers
                ) {

        }

        C_ENG_NO_DISCARD constexpr auto type () const noexcept -> EventType override {
            return EventType :: EventTypeKeyPressEvent;
        }
    };

}


#endif //C_ENG_KEYPRESSEVENT_HPP

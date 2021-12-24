//
// Created by loghin on 20.12.2021.
//

#ifndef C_ENG_KEYRELEASEEVENT_HPP
#define C_ENG_KEYRELEASEEVENT_HPP


#include <KeyEvent.hpp>

namespace engine {

    class C_ENG_CLASS ( KeyReleaseEvent ) : public C_ENG_CLASS ( KeyEvent ) {
    public:
        C_ENG_DESTRUCTOR ( KeyReleaseEvent ) () noexcept override = default;

        C_ENG_CONSTRUCTOR ( KeyReleaseEvent ) (
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
            return EventType :: EventTypeKeyReleaseEvent;
        }

        C_ENG_NO_DISCARD inline auto copy () const noexcept -> C_ENG_TYPE ( KeyReleaseEvent ) * override {
            return new C_ENG_TYPE ( KeyReleaseEvent ) ( * this );
        }

        C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

}


#endif //C_ENG_KEYRELEASEEVENT_HPP

//
// Created by loghin on 21.12.2021.
//

#ifndef C_ENG_WINDOWGAINFOCUSEVENT_HPP
#define C_ENG_WINDOWGAINFOCUSEVENT_HPP


#include <WindowEvent.hpp>

namespace engine {

    class C_ENG_CLASS ( WindowGainFocusEvent ) : public C_ENG_CLASS ( WindowEvent ) {

    public:
        C_ENG_DESTRUCTOR ( WindowGainFocusEvent ) () noexcept override = default;

        explicit C_ENG_CONSTRUCTOR ( WindowGainFocusEvent ) (
                C_ENG_TYPE ( Window ) * window
        ) noexcept :
                C_ENG_CONSTRUCTOR ( WindowEvent ) ( window ) {

        }

    public:
        C_ENG_NO_DISCARD constexpr auto type () const noexcept -> EventType override {
            return EventType :: EventTypeWindowGainFocusEvent;
        }

        C_ENG_NO_DISCARD inline auto copy () const noexcept -> C_ENG_TYPE ( WindowGainFocusEvent ) * override {
            return new C_ENG_TYPE ( WindowGainFocusEvent ) ( * this );
        }

        C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

}


#endif //C_ENG_WINDOWGAINFOCUSEVENT_HPP

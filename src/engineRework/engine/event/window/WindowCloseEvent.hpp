//
// Created by loghin on 21.12.2021.
//

#ifndef C_ENG_WINDOWCLOSEEVENT_HPP
#define C_ENG_WINDOWCLOSEEVENT_HPP


#include <WindowEvent.hpp>

namespace engine {

    class C_ENG_CLASS ( WindowCloseEvent ) : public C_ENG_CLASS ( WindowEvent ) {
        C_ENG_CLASS_MUTABLE_PRIMITIVE_FIELD ( bool, cancelClose, false )

    public:
        C_ENG_DESTRUCTOR ( WindowCloseEvent ) () noexcept override = default;

        explicit C_ENG_CONSTRUCTOR ( WindowCloseEvent ) (
                C_ENG_TYPE ( Window ) * window
        ) noexcept :
                C_ENG_CONSTRUCTOR ( WindowEvent ) ( window ) {

        }

        C_ENG_NO_DISCARD constexpr auto type () const noexcept -> EventType override {
            return EventType :: EventTypeWindowCloseEvent;
        }

        C_ENG_NO_DISCARD inline auto copy () const noexcept -> C_ENG_TYPE ( WindowCloseEvent ) * override {
            return new C_ENG_TYPE ( WindowCloseEvent ) ( * this );
        }

        C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

}


#endif //C_ENG_WINDOWCLOSEEVENT_HPP

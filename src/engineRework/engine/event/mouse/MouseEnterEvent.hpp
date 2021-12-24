//
// Created by loghin on 20.12.2021.
//

#ifndef C_ENG_MOUSEENTEREVENT_HPP
#define C_ENG_MOUSEENTEREVENT_HPP

#include <MouseEvent.hpp>

namespace engine {

    class C_ENG_CLASS ( MouseEnterEvent ) : public C_ENG_CLASS ( MouseEvent ) {
    public:
        C_ENG_DESTRUCTOR ( MouseEnterEvent ) () noexcept override = default;

        C_ENG_CONSTRUCTOR ( MouseEnterEvent ) (
                C_ENG_TYPE ( Window ) * window,
                Position        const & position
        ) noexcept :
                C_ENG_CONSTRUCTOR ( MouseEvent ) (
                        window,
                        position
                ) {

        }

        C_ENG_NO_DISCARD constexpr auto type () const noexcept -> EventType override {
            return EventType :: EventTypeMouseEnterEvent;
        }

        C_ENG_NO_DISCARD inline auto copy () const noexcept -> C_ENG_TYPE ( MouseEnterEvent ) * override {
            return new C_ENG_TYPE ( MouseEnterEvent ) ( * this );
        }

        C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

}

#endif //C_ENG_MOUSEENTEREVENT_HPP

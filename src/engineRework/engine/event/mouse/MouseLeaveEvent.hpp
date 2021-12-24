//
// Created by loghin on 20.12.2021.
//

#ifndef C_ENG_MOUSELEAVEEVENT_HPP
#define C_ENG_MOUSELEAVEEVENT_HPP


#include <MouseEvent.hpp>

namespace engine {

    class C_ENG_CLASS ( MouseLeaveEvent ) : public C_ENG_CLASS ( MouseEvent ) {
    public:
        C_ENG_DESTRUCTOR ( MouseLeaveEvent ) () noexcept override = default;

        C_ENG_CONSTRUCTOR ( MouseLeaveEvent ) (
                C_ENG_TYPE ( Window ) * window,
                Position        const & position
        ) noexcept :
                C_ENG_CONSTRUCTOR ( MouseEvent ) (
                        window,
                        position
                ) {

        }

        C_ENG_NO_DISCARD constexpr auto type () const noexcept -> EventType override {
            return EventType :: EventTypeMouseLeaveEvent;
        }

        C_ENG_NO_DISCARD inline auto copy () const noexcept -> C_ENG_TYPE ( MouseLeaveEvent ) * override {
            return new C_ENG_TYPE ( MouseLeaveEvent ) ( * this );
        }

        C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

}


#endif //C_ENG_MOUSELEAVEEVENT_HPP

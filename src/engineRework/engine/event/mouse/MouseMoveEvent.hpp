//
// Created by loghin on 20.12.2021.
//

#ifndef C_ENG_MOUSEMOVEEVENT_HPP
#define C_ENG_MOUSEMOVEEVENT_HPP

#include <MouseEvent.hpp>

namespace engine {

    class C_ENG_CLASS ( MouseMoveEvent ) : public C_ENG_CLASS ( MouseEvent ) {
        C_ENG_CLASS_IMMUTABLE_FIELD ( Position, oldPosition, 0u, 0u )

    public:
        C_ENG_CONSTRUCTOR ( MouseMoveEvent ) (
                C_ENG_TYPE ( Window ) * window,
                Position        const & position,
                Position        const & oldPosition
        ) noexcept :
                C_ENG_CONSTRUCTOR ( MouseEvent ) (
                        window,
                        position
                ),
                _oldPosition ( oldPosition ) {


        }

        C_ENG_DESTRUCTOR ( MouseMoveEvent ) () noexcept override = default;

        C_ENG_NO_DISCARD constexpr auto type () const noexcept -> EventType override {
            return EventType :: EventTypeMousePressEvent;
        }

        C_ENG_NO_DISCARD inline auto copy () const noexcept -> C_ENG_TYPE ( MouseMoveEvent ) * override {
            return new C_ENG_TYPE ( MouseMoveEvent ) ( * this );
        }

        C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
        C_ENG_NO_DISCARD auto equals ( cds :: Object const & ) const noexcept -> bool override;
    };

}

#endif //C_ENG_MOUSEMOVEEVENT_HPP

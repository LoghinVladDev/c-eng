//
// Created by loghin on 20.12.2021.
//

#ifndef C_ENG_MOUSESCROLLEVENT_HPP
#define C_ENG_MOUSESCROLLEVENT_HPP

#include <MouseEvent.hpp>

namespace engine {

    class C_ENG_CLASS ( MouseScrollEvent ) : public C_ENG_CLASS ( MouseEvent ) {
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( double, xOffset, 0.0 )
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( double, yOffset, 0.0 )

    public:
        C_ENG_DESTRUCTOR ( MouseScrollEvent ) () noexcept override = default;

        C_ENG_CONSTRUCTOR ( MouseScrollEvent ) (
                C_ENG_TYPE ( Window ) * window,
                Position        const & position,
                double                  xOffset,
                double                  yOffset
        ) noexcept :
                C_ENG_CONSTRUCTOR ( MouseEvent ) (
                        window,
                        position
                ),
                _xOffset ( xOffset ),
                _yOffset ( yOffset ) {

        }

        C_ENG_NO_DISCARD constexpr auto type () const noexcept -> EventType override {
            return EventType :: EventTypeMouseScrollEvent;
        }

        C_ENG_NO_DISCARD inline auto copy () const noexcept -> C_ENG_TYPE ( MouseScrollEvent ) * override {
            return new C_ENG_TYPE ( MouseScrollEvent ) ( * this );
        }

        C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
        C_ENG_NO_DISCARD auto equals ( cds :: Object const & ) const noexcept -> bool override;
    };

}


#endif //C_ENG_MOUSESCROLLEVENT_HPP

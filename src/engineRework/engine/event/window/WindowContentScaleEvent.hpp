//
// Created by loghin on 21.12.2021.
//

#ifndef C_ENG_WINDOWCONTENTSCALEEVENT_HPP
#define C_ENG_WINDOWCONTENTSCALEEVENT_HPP


#include <WindowEvent.hpp>

namespace engine {

    class C_ENG_CLASS ( WindowContentScaleEvent ) : public C_ENG_CLASS ( WindowEvent ) {

        C_ENG_CLASS_IMMUTABLE_FIELD ( WindowContentScale, scale, 0.0f, 0.0f )

    public:
        C_ENG_DESTRUCTOR ( WindowContentScaleEvent ) () noexcept override = default;

        C_ENG_CONSTRUCTOR ( WindowContentScaleEvent ) (
                C_ENG_TYPE ( Window )       * window,
                WindowContentScale    const & scale
        ) noexcept :
                C_ENG_CONSTRUCTOR ( WindowEvent ) ( window ),
                _scale ( scale ) {

        }

        C_ENG_NO_DISCARD constexpr auto type () const noexcept -> EventType override {
            return EventType :: EventTypeWindowContentScaleEvent;
        }

    };

}


#endif //C_ENG_WINDOWCONTENTSCALEEVENT_HPP

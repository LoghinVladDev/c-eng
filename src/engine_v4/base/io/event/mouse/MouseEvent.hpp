//
// Created by loghin on 20.12.2021.
//

#ifndef __C_ENG_MOUSE_EVENT_HPP__
#define __C_ENG_MOUSE_EVENT_HPP__

#include <base/io/event/Event.hpp>
#include <base/core/Core.hpp>

namespace engine::io {
    class Window;
}

namespace engine::io {

    class MouseEvent : public Event {
    private:
        Point2D _position {0U, 0U};

    protected:
        MouseEvent (
                Window  const * pWindow,
                Point2D         position
        ) noexcept;

    public:
        __CDS_NoDiscard constexpr auto position () const noexcept -> Point2D {
            return this->_position;
        }

        ~MouseEvent () noexcept override = default;

        __CDS_NoDiscard constexpr auto className () const noexcept -> cds::StringView override {
            return "MouseEvent";
        }

        __CDS_NoDiscard constexpr auto typeFlags () const noexcept -> TypeFlags override {
            return
                    TypeFlagBits::CustomEventBit |
                    TypeFlagBits::MouseEventBit;
        }
    };

}


#endif //__C_ENG_MOUSE_EVENT_HPP__

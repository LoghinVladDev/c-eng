//
// Created by loghin on 20.12.2021.
//

#ifndef __C_ENG_MOUSE_MOVE_EVENT_HPP__
#define __C_ENG_MOUSE_MOVE_EVENT_HPP__


#include <base/io/event/mouse/MouseEvent.hpp>

namespace engine::io {

    class MouseMoveEvent : public MouseEvent {
    private:
        Point2D _oldPosition {0U, 0U};

    public:
        __CDS_NoDiscard constexpr auto oldPosition () const noexcept -> Point2D {
            return this->_oldPosition;
        }

        ~MouseMoveEvent () noexcept override = default;
        MouseMoveEvent (
                Window  const * pWindow,
                Point2D         position,
                Point2D         oldPosition
        ) noexcept;

        __CDS_NoDiscard constexpr auto className () const noexcept -> cds::StringView override {
            return "MouseMoveEvent";
        }

        __CDS_NoDiscard constexpr auto typeFlags () const noexcept -> TypeFlags override {
            return
                    TypeFlagBits::MouseEventBit |
                    TypeFlagBits::MoveEventBit  ;
        }
    };

}


#endif //__C_ENG_MOUSE_MOVE_EVENT_HPP__

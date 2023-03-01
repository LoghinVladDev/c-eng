//
// Created by loghin on 20.12.2021.
//

#ifndef __C_ENG_MOUSE_LEAVE_EVENT_HPP__
#define __C_ENG_MOUSE_LEAVE_EVENT_HPP__


#include <base/io/event/mouse/MouseEvent.hpp>

namespace engine::io {

    class MouseLeaveEvent : public MouseEvent {
    public:
        ~MouseLeaveEvent () noexcept override = default;
        MouseLeaveEvent (
                Window  const * pWindow,
                Point2D         position
        ) noexcept;

        __CDS_NoDiscard constexpr auto className () const noexcept -> cds::StringView override {
            return "MouseLeaveEvent";
        }

        __CDS_NoDiscard constexpr auto typeFlags () const noexcept -> TypeFlags override {
            return
                    TypeFlagBits::MouseEventBit         |
                    TypeFlagBits::MouseLeaveEventBit    ;
        }
    };

}


#endif //__C_ENG_MOUSE_LEAVE_EVENT_HPP__

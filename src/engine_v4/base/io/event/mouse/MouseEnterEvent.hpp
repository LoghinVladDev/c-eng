//
// Created by loghin on 20.12.2021.
//

#ifndef __C_ENG_MOUSE_ENTER_EVENT_HPP__
#define __C_ENG_MOUSE_ENTER_EVENT_HPP__


#include <base/io/event/mouse/MouseEvent.hpp>

namespace engine::io {

    class MouseEnterEvent : public MouseEvent {
    public:
        ~MouseEnterEvent () noexcept override = default;
        MouseEnterEvent (
                Window  const * pWindow,
                Point2D         position
        ) noexcept;

        __CDS_NoDiscard constexpr auto className () const noexcept -> cds::StringView override {
            return "MouseEnterEvent";
        }

        __CDS_NoDiscard constexpr auto typeFlags () const noexcept -> TypeFlags override {
            return
                    TypeFlagBits::MouseEventBit         |
                    TypeFlagBits::MouseEnterEventBit    ;
        }
    };

}


#endif //__C_ENG_MOUSE_ENTER_EVENT_HPP__

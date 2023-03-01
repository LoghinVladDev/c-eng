//
// Created by loghin on 20.12.2021.
//

#ifndef __C_ENG_MOUSE_SCROLL_EVENT_HPP__
#define __C_ENG_MOUSE_SCROLL_EVENT_HPP__


#include <base/io/event/mouse/MouseEvent.hpp>

namespace engine::io {

    class MouseScrollEvent : public MouseEvent {
    private:
        Scale2DF            _offset         {0.0F, 0.0F};
        KeyModifierFlags    _keyModifiers   {KeyModifierNone};

    public:
        __CDS_NoDiscard constexpr auto keyModifiers () const noexcept -> KeyModifierFlags {
            return this->_keyModifiers;
        }

        __CDS_NoDiscard constexpr auto offset () const noexcept -> Scale2DF {
            return this->_offset;
        }

        ~MouseScrollEvent () noexcept override = default;
        MouseScrollEvent (
                Window      const * pWindow,
                Point2D             position,
                Scale2DF            offset,
                KeyModifierFlags    keyModifierFlags
        ) noexcept;

        __CDS_NoDiscard constexpr auto className () const noexcept -> cds::StringView override {
            return "MouseScrollEvent";
        }

        __CDS_NoDiscard constexpr auto typeFlags () const noexcept -> TypeFlags override {
            return
                    TypeFlagBits::MouseEventBit         |
                    TypeFlagBits::MouseScrollEventBit   ;
        }
    };

}


#endif //__C_ENG_MOUSE_SCROLL_EVENT_HPP__

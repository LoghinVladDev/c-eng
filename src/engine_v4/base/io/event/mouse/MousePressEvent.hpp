//
// Created by loghin on 20.12.2021.
//

#ifndef __C_ENG_MOUSE_PRESS_EVENT_HPP__
#define __C_ENG_MOUSE_PRESS_EVENT_HPP__


#include <base/io/event/mouse/MouseEvent.hpp>

namespace engine::io {

    class MousePressEvent : public MouseEvent {
    private:
        MouseButtonType     _button         {MouseButtonUnknown};
        KeyModifierFlags    _keyModifiers   {KeyModifierNone};

    public:
        __CDS_NoDiscard constexpr auto modifierFlags () const noexcept -> KeyModifierFlags {
            return this->_keyModifiers;
        }

        __CDS_NoDiscard constexpr auto button () const noexcept -> MouseButtonType {
            return this->_button;
        }

        ~MousePressEvent () noexcept override = default;
        MousePressEvent (
                Window      const * pWindow,
                Point2D             position,
                MouseButtonType     button,
                KeyModifierFlags    keyModifierFlags
        ) noexcept;

        __CDS_NoDiscard constexpr auto className () const noexcept -> cds::StringView override {
            return "MousePressEvent";
        }

        __CDS_NoDiscard constexpr auto typeFlags () const noexcept -> TypeFlags override {
            return
                    TypeFlagBits::MouseEventBit |
                    TypeFlagBits::PressEventBit ;
        }
    };

}


#endif //__C_ENG_MOUSE_PRESS_EVENT_HPP__

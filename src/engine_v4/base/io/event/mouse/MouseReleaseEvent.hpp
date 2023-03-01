//
// Created by loghin on 20.12.2021.
//

#ifndef __C_ENG_MOUSE_RELEASE_EVENT_HPP__
#define __C_ENG_MOUSE_RELEASE_EVENT_HPP__


#include <base/io/event/mouse/MouseEvent.hpp>

namespace engine::io {

    class MouseReleaseEvent : public MouseEvent {
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

        ~MouseReleaseEvent () noexcept override = default;
        MouseReleaseEvent (
                Window      const * pWindow,
                Point2D             position,
                MouseButtonType     button,
                KeyModifierFlags    keyModifierFlags
        ) noexcept;

        __CDS_NoDiscard constexpr auto className () const noexcept -> cds::StringView override {
            return "MouseReleaseEvent";
        }

        __CDS_NoDiscard constexpr auto typeFlags () const noexcept -> TypeFlags override {
            return
                    TypeFlagBits::MouseEventBit     |
                    TypeFlagBits::ReleaseEventBit   ;
        }
    };

}


#endif //__C_ENG_MOUSE_RELEASE_EVENT_HPP__

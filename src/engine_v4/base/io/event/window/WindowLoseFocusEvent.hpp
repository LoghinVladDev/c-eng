//
// Created by loghin on 21.12.2021.
//

#ifndef __C_ENG_WINDOW_LOSE_FOCUS_EVENT_HPP__
#define __C_ENG_WINDOW_LOSE_FOCUS_EVENT_HPP__


#include <base/io/event/window/WindowEvent.hpp>

namespace engine::io {

    class WindowLoseFocusEvent : public WindowEvent {
    public:
        ~WindowLoseFocusEvent () noexcept override = default;
        explicit WindowLoseFocusEvent (Window const * pWindow) noexcept;

        __CDS_NoDiscard constexpr auto className () const noexcept -> cds::StringView override {
            return "WindowLoseFocusEvent";
        }

        __CDS_NoDiscard constexpr auto typeFlags () const noexcept -> TypeFlags override {
            return
                    TypeFlagBits::WindowEventBit            |
                    TypeFlagBits::WindowLoseFocusEventBit   ;
        }
    };

}


#endif //__C_ENG_WINDOW_LOSE_FOCUS_EVENT_HPP__

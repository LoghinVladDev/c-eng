//
// Created by loghin on 21.12.2021.
//

#ifndef __C_ENG_WINDOW_GAIN_FOCUS_EVENT_HPP__
#define __C_ENG_WINDOW_GAIN_FOCUS_EVENT_HPP__


#include <base/io/event/window/WindowEvent.hpp>

namespace engine::io {
    
    class WindowGainFocusEvent : public WindowEvent {
    public:
        ~WindowGainFocusEvent () noexcept override = default;
        explicit WindowGainFocusEvent (Window const * pWindow) noexcept;

        __CDS_NoDiscard constexpr auto className () const noexcept -> cds::StringView override {
            return "WindowGainFocusEvent";
        }

        __CDS_NoDiscard constexpr auto typeFlags () const noexcept -> TypeFlags override {
            return
                    TypeFlagBits::WindowEventBit            |
                    TypeFlagBits::WindowGainFocusEventBit   ;
        }
    };

}


#endif //__C_ENG_WINDOW_GAIN_FOCUS_EVENT_HPP__

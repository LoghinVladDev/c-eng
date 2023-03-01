//
// Created by loghin on 21.12.2021.
//

#ifndef __C_ENG_WINDOW_MAXIMIZE_EVENT_HPP__
#define __C_ENG_WINDOW_MAXIMIZE_EVENT_HPP__


#include <base/io/event/window/WindowEvent.hpp>

namespace engine::io {

    class WindowMaximizeEvent : public WindowEvent {
    public:
        ~WindowMaximizeEvent () noexcept override = default;
        explicit WindowMaximizeEvent (Window const * pWindow) noexcept;

        __CDS_NoDiscard constexpr auto className () const noexcept -> cds::StringView override {
            return "WindowMaximizeEvent";
        }

        __CDS_NoDiscard constexpr auto typeFlags () const noexcept -> TypeFlags override {
            return
                    TypeFlagBits::WindowEventBit            |
                    TypeFlagBits::WindowMaximizeEventBit    ;
        }
    };

}


#endif //__C_ENG_WINDOW_MAXIMIZE_EVENT_HPP__

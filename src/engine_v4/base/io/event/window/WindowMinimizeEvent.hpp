//
// Created by loghin on 21.12.2021.
//

#ifndef __C_ENG_WINDOW_MINIMIZE_EVENT_HPP__
#define __C_ENG_WINDOW_MINIMIZE_EVENT_HPP__


#include <base/io/event/window/WindowEvent.hpp>

namespace engine::io {

    class WindowMinimizeEvent : public WindowEvent {
    public:
        ~WindowMinimizeEvent () noexcept override = default;
        explicit WindowMinimizeEvent (Window const * pWindow) noexcept;

        __CDS_NoDiscard constexpr auto className () const noexcept -> cds::StringView override {
            return "WindowMinimizeEvent";
        }

        __CDS_NoDiscard constexpr auto typeFlags () const noexcept -> TypeFlags override {
            return
                    TypeFlagBits::WindowEventBit            |
                    TypeFlagBits::WindowMinimizeEventBit    ;
        }
    };

}


#endif //__C_ENG_WINDOW_MINIMIZE_EVENT_HPP__

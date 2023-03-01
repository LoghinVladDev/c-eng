//
// Created by loghin on 21.12.2021.
//

#ifndef __C_ENG_WINDOW_EVENT_HPP__
#define __C_ENG_WINDOW_EVENT_HPP__

#include <base/io/event/Event.hpp>

namespace engine::io {
    class Window;
}

namespace engine::io {

    class WindowEvent : public Event {
    protected:
        explicit WindowEvent (Window const * pWindow) noexcept;

    public:
        ~WindowEvent () noexcept override = default;

        __CDS_NoDiscard constexpr auto className () const noexcept -> cds::StringView override {
            return "WindowEvent";
        }

        __CDS_NoDiscard constexpr auto typeFlags () const noexcept -> TypeFlags override {
            return
                    TypeFlagBits::CustomEventBit |
                    TypeFlagBits::WindowEventBit;
        }
    };

}


#endif //__C_ENG_WINDOW_EVENT_HPP__

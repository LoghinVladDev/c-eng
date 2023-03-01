//
// Created by loghin on 21.12.2021.
//

#ifndef __C_ENG_WINDOW_REFRESH_REQUEST_EVENT_HPP__
#define __C_ENG_WINDOW_REFRESH_REQUEST_EVENT_HPP__


#include <base/io/event/window/WindowEvent.hpp>

namespace engine::io {

    class WindowRefreshRequestEvent : public WindowEvent {
    public:
        ~WindowRefreshRequestEvent () noexcept override = default;
        explicit WindowRefreshRequestEvent (Window const * pWindow) noexcept;

        __CDS_NoDiscard constexpr auto className () const noexcept -> cds::StringView override {
            return "WindowRefreshRequestEvent";
        }

        __CDS_NoDiscard constexpr auto typeFlags () const noexcept -> TypeFlags override {
            return
                    TypeFlagBits::WindowEventBit                |
                    TypeFlagBits::WindowRefreshRequestEventBit  ;
        }
    };

}


#endif //__C_ENG_WINDOW_REFRESH_REQUEST_EVENT_HPP__

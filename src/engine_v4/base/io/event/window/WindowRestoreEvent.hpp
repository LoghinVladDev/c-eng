//
// Created by loghin on 21.12.2021.
//

#ifndef __C_ENG_WINDOW_RESTORE_EVENT_HPP__
#define __C_ENG_WINDOW_RESTORE_EVENT_HPP__


#include <base/io/event/window/WindowEvent.hpp>

namespace engine::io {

    class WindowRestoreEvent : public WindowEvent {
    public:
        ~WindowRestoreEvent () noexcept override = default;
        explicit WindowRestoreEvent (Window const * pWindow) noexcept;

        __CDS_NoDiscard constexpr auto className () const noexcept -> cds::StringView override {
            return "WindowRestoreEvent";
        }

        __CDS_NoDiscard constexpr auto typeFlags () const noexcept -> TypeFlags override {
            return
                    TypeFlagBits::WindowEventBit        |
                    TypeFlagBits::WindowRestoreEventBit ;
        }
    };

}


#endif //__C_ENG_WINDOW_RESTORE_EVENT_HPP__

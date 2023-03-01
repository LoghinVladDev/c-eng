//
// Created by loghin on 21.12.2021.
//

#ifndef __C_ENG_WINDOW_CLOSE_EVENT_HPP__
#define __C_ENG_WINDOW_CLOSE_EVENT_HPP__


#include <base/io/event/window/WindowEvent.hpp>

namespace engine::io {

    class WindowCloseEvent : public WindowEvent {
    private:
        bool _cancelClose {false};

    public:
        auto cancelClose () noexcept -> void {
            this->_cancelClose = true;
        }

        __CDS_NoDiscard constexpr auto isCloseCancelled () const noexcept -> bool {
            return this->_cancelClose;
        }

        explicit WindowCloseEvent (Window const * pWindow) noexcept;
        ~WindowCloseEvent () noexcept override = default;

        __CDS_NoDiscard constexpr auto className () const noexcept -> cds::StringView override {
            return "WindowCloseEvent";
        }

        __CDS_NoDiscard constexpr auto typeFlags () const noexcept -> TypeFlags override {
            return
                    TypeFlagBits::WindowEventBit        |
                    TypeFlagBits::WindowCloseEventBit   ;
        }
    };

}


#endif //__C_ENG_WINDOW_CLOSE_EVENT_HPP__

//
// Created by loghin on 21.12.2021.
//

#ifndef __C_ENG_WINDOW_FRAME_BUFFER_RESIZE_EVENT_HPP__
#define __C_ENG_WINDOW_FRAME_BUFFER_RESIZE_EVENT_HPP__


#include <base/io/event/window/WindowEvent.hpp>
#include <base/core/Core.hpp>

namespace engine::io {

    class WindowFrameBufferResizeEvent : public WindowEvent {
    private:
        Size2D _size    {0U, 0U};
        Size2D _oldSize {0U, 0U};

    public:
        __CDS_NoDiscard constexpr auto size () const noexcept -> Size2D { return this->_size; }
        __CDS_NoDiscard constexpr auto oldSize () const noexcept -> Size2D { return this->_oldSize; }

        ~WindowFrameBufferResizeEvent () noexcept override = default;

        explicit WindowFrameBufferResizeEvent (
                Window  const * pWindow,
                Size2D          size,
                Size2D          oldSize
        ) noexcept;

        __CDS_NoDiscard constexpr auto className () const noexcept -> cds::StringView override {
            return "WindowFrameBufferResizeEvent";
        }

        __CDS_NoDiscard constexpr auto typeFlags () const noexcept -> TypeFlags override {
            return
                    TypeFlagBits::WindowEventBit                    |
                    TypeFlagBits::WindowFrameBufferResizeEventBit   ;
        }
    };

}


#endif //__C_ENG_WINDOW_FRAME_BUFFER_RESIZE_EVENT_HPP__

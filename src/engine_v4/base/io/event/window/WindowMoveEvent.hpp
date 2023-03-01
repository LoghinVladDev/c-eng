//
// Created by loghin on 21.12.2021.
//

#ifndef __C_ENG_WINDOW_MOVE_EVENT_HPP__
#define __C_ENG_WINDOW_MOVE_EVENT_HPP__


#include <base/io/event/window/WindowEvent.hpp>
#include <base/core/Core.hpp>

namespace engine::io {

    class WindowMoveEvent : public WindowEvent {
    private:
        Point2D _position       {0U, 0U};
        Point2D _oldPosition    {0U, 0U};

    public:
        __CDS_NoDiscard constexpr auto position () const noexcept -> Point2D { return this->_position; }
        __CDS_NoDiscard constexpr auto oldPosition () const noexcept -> Point2D { return this->_oldPosition; }

        WindowMoveEvent (
                Window  const * pWindow,
                Point2D         position,
                Point2D         oldPosition
        ) noexcept;

        ~WindowMoveEvent () noexcept override = default;

        __CDS_NoDiscard constexpr auto className () const noexcept -> cds::StringView override {
            return "WindowGainFocusEvent";
        }

        __CDS_NoDiscard constexpr auto typeFlags () const noexcept -> TypeFlags override {
            return
                    TypeFlagBits::WindowEventBit    |
                    TypeFlagBits::MoveEventBit      ;
        }
    };

}


#endif //__C_ENG_WINDOW_MOVE_EVENT_HPP__

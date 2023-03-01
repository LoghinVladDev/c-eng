//
// Created by loghin on 21.12.2021.
//

#ifndef __C_ENG_WINDOW_CONTENT_SCALE_EVENT_HPP__
#define __C_ENG_WINDOW_CONTENT_SCALE_EVENT_HPP__


#include <base/io/event/window/WindowEvent.hpp>
#include <base/core/Core.hpp>

namespace engine::io {

    class WindowContentScaleEvent : public WindowEvent {
    private:
        Scale2DF    _scale {0.0F, 0.0F};

    public:
        __CDS_NoDiscard constexpr auto scale () const noexcept -> Scale2DF {
            return this->_scale;
        }

        ~WindowContentScaleEvent () noexcept override = default;

        WindowContentScaleEvent (
                Window  const * pWindow,
                Scale2DF        scale
        ) noexcept;

        __CDS_NoDiscard constexpr auto className () const noexcept -> cds::StringView override {
            return "WindowContentScaleEvent";
        }

        __CDS_NoDiscard constexpr auto typeFlags () const noexcept -> TypeFlags override {
            return
                    TypeFlagBits::WindowEventBit                |
                    TypeFlagBits::WindowContentScaleEventBit    ;
        }
    };

}


#endif //__C_ENG_WINDOW_CONTENT_SCALE_EVENT_HPP__

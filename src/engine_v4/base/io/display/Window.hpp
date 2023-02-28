/*
 * Created by loghin on 24/02/23.
 */

#ifndef __C_ENG_WINDOW_HPP__
#define __C_ENG_WINDOW_HPP__

#include <CDS/Array>
#include <CDS/memory/UniquePointer>

#include <base/core/Object.hpp>

#include "Display.hpp"
#include "Surface.hpp"

namespace engine::io {

    class Monitor;
    class WindowManager;


    class Window : public Object {
    private:

        friend class WindowManager;

        WindowManager                         * _pManager           {nullptr};

        cds::Function <void(Window const *)>    _onCloseCallback    {[](auto){}};

    public:

        enum class Mode {
            Windowed,
            Fullscreen,
            WindowedFullscreen
        };

        enum WindowFlagBits {
            None                    = 0x00000000U,
            Resizable               = 0x00000001U,
            Borderless              = 0x00000002U,
            StartMinimized          = 0x00000004U,
            GrabFocusOnOpen         = 0x00000008U,
            RestorePreviousMode     = 0x00000010U,
            StayOnTop               = 0x00000020U,
            StartMaximized          = 0x00000040U,
            CenterCursorOnCreate    = 0x00000080U,
            TransparentFramebuffer  = 0x00000100U,
            GrabFocusOnRaise        = 0x00000200U,
            ScaleToMonitor          = 0x00000400U,
        };

        using WindowFlags = cds::uint32;

        explicit Window (Object const * pParent = nullptr) noexcept;
        ~Window () noexcept override;
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto className () const noexcept -> cds::StringView override {
            return "Window";
        }

        __CDS_NoDiscard virtual auto surface () const noexcept -> Surface const * = 0;

        auto close () noexcept -> void;

        auto setOnCloseCallback (cds::Function <void(Window const *)> callback) noexcept -> void;
    };


    class WindowManager : public Object {
    private:
        cds::Array <cds::UniquePointer <Window>>    _windows;
        cds::Function <void(void)>                  _onAllClosedCallback {[]{}};

        auto addWindow (Window * pWindow) noexcept -> void;

    protected:
        class WindowBuilder : public Object {
        private:
            friend class WindowManager;
            WindowManager * _pManager   {nullptr};

            Rect2D          _geom       {0U, 0U, 100U, 100U};
            cds::StringView _title      {"Engine Window"};
            Window::Mode    _mode       {Window::Mode::Windowed};
            Display const * _pDisplay   {nullptr};

        protected:
            __CDS_NoDiscard constexpr auto geometry () const noexcept -> Rect2D const & { return this->_geom; }
            __CDS_NoDiscard constexpr auto size () const noexcept -> Point2D const & { return this->_geom.position; }
            __CDS_NoDiscard constexpr auto position () const noexcept -> Size2D const & { return this->_geom.size; }
            __CDS_NoDiscard constexpr auto title () const noexcept -> cds::StringView { return this->_title; }
            __CDS_NoDiscard constexpr auto display () const noexcept -> Display const * { return this->_pDisplay; }
            __CDS_NoDiscard constexpr auto manager () const noexcept -> WindowManager const * { return this->_pManager; }

            __CDS_NoDiscard virtual auto _build () const noexcept (false) -> Window * = 0;

        public:
            auto windowed (Point2D position, Size2D size) noexcept -> WindowBuilder &;
            auto windowed (Rect2D const & geometry) noexcept -> WindowBuilder &;
            auto windowed (cds::uint32 x, cds::uint32 y, cds::uint32 width, cds::uint32 height) noexcept -> WindowBuilder &;

            auto fullscreen (Display const * pDisplay = nullptr) noexcept -> WindowBuilder &;
            auto fullscreen (Display::VideoModeProperties const & videoMode, Display const * pDisplay = nullptr) noexcept -> WindowBuilder &;

            auto exclusiveFullscreen (Display const * pDisplay = nullptr) noexcept -> WindowBuilder &;

            explicit WindowBuilder (Object const * pParent = nullptr) noexcept;
            ~WindowBuilder() noexcept override = default;

            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto className () const noexcept -> cds::StringView override {
                return "WindowBuilder";
            }

            __CDS_NoDiscard auto build () const noexcept (false) -> Window *;
        };

        __CDS_NoDiscard virtual auto _windowBuilder (Object const * pParent) const noexcept -> cds::UniquePointer <WindowBuilder> = 0;

    public:
        explicit WindowManager (Object const * pParent = nullptr) noexcept;
        ~WindowManager () noexcept override;
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto className () const noexcept -> cds::StringView override {
            return "WindowManager";
        }

        __CDS_NoDiscard auto windowBuilder () noexcept -> cds::UniquePointer <WindowBuilder>;

        auto removeWindow (Window * pWindow) noexcept -> void;

        auto setOnAllWindowsClosedCallback (cds::Function <void(void)> callback) noexcept -> void;
    };

}


#endif /* __C_ENG_WINDOW_HPP__ */

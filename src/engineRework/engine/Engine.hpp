//
// Created by loghin on 18.12.2021.
//

#ifndef C_ENG_ENGINE_HPP
#define C_ENG_ENGINE_HPP

#include <Preprocess.hpp>
#include <CDS/Pointer>

#include <Core.hpp>

namespace engine {

    class C_ENG_CLASS ( Window );

    class C_ENG_CLASS ( Event );

    class C_ENG_CLASS ( ControllerEvent );

    class C_ENG_CLASS ( ControllerAxisChangeEvent );
    class C_ENG_CLASS ( ControllerButtonPressEvent );
    class C_ENG_CLASS ( ControllerButtonReleaseEvent );
    class C_ENG_CLASS ( ControllerConnectEvent );
    class C_ENG_CLASS ( ControllerDisconnectEvent );
    class C_ENG_CLASS ( ControllerHatChangeEvent );

    class C_ENG_CLASS ( WindowEvent );

    class C_ENG_CLASS ( WindowResizeEvent );
    class C_ENG_CLASS ( WindowCloseEvent );
    class C_ENG_CLASS ( WindowFrameBufferResizeEvent );
    class C_ENG_CLASS ( WindowContentScaleEvent );
    class C_ENG_CLASS ( WindowMoveEvent );
    class C_ENG_CLASS ( WindowRestoreEvent );
    class C_ENG_CLASS ( WindowMinimizeEvent );
    class C_ENG_CLASS ( WindowMaximizeEvent );
    class C_ENG_CLASS ( WindowGainFocusEvent );
    class C_ENG_CLASS ( WindowLoseFocusEvent );
    class C_ENG_CLASS ( WindowRefreshRequestEvent );

    class C_ENG_CLASS ( KeyEvent );

    class C_ENG_CLASS ( KeyPressEvent );
    class C_ENG_CLASS ( KeyReleaseEvent );

    class C_ENG_CLASS ( MouseEvent );

    class C_ENG_CLASS ( MouseMoveEvent );
    class C_ENG_CLASS ( MouseEnterEvent );
    class C_ENG_CLASS ( MouseLeaveEvent );
    class C_ENG_CLASS ( MousePressEvent );
    class C_ENG_CLASS ( MouseReleaseEvent );
    class C_ENG_CLASS ( MouseScrollEvent );

    class C_ENG_CLASS ( Engine ) : public cds :: Object {
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( EngineState, state, EngineState :: EngineStateInactive )
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( C_ENG_TYPE ( Window ) *, window, nullptr )

        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( double, frameDeltaTime, 0.0 )
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( bool, logFPSToConsole, false )
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint64, fpsUpdateFrameTime, 512ULL )
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint64, showFpsEveryTick, 8192ULL )
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint64, frameCount, 0ULL )

        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( double, fps, 0.0f )

    private:
        auto initializeSettings () noexcept -> C_ENG_TYPE ( Engine & );
        auto startup () noexcept -> C_ENG_TYPE ( Engine ) &;
        auto run () noexcept -> C_ENG_TYPE ( Engine ) &;
        auto shutdown () noexcept -> C_ENG_TYPE ( Engine ) &;

        C_ENG_CONSTRUCTOR ( Engine ) () noexcept;

        constexpr auto setState ( EngineState state ) noexcept -> void {
            this->_state = state;
        }

    public:
        auto static instance () noexcept -> C_ENG_TYPE ( Engine ) &;
        auto start () noexcept -> C_ENG_TYPE ( Engine ) &;

        auto setWindow ( C_ENG_TYPE ( Window ) * ) noexcept -> C_ENG_TYPE ( Engine ) &;

        auto customEvent ( C_ENG_TYPE ( Event ) * ) noexcept -> C_ENG_TYPE ( Engine ) &;

        auto controllerCustomEvent ( C_ENG_TYPE ( ControllerEvent ) * ) noexcept -> C_ENG_TYPE ( Engine ) &;
        auto controllerAxisChangeEvent ( C_ENG_TYPE ( ControllerAxisChangeEvent ) * ) noexcept -> C_ENG_TYPE ( Engine ) &;
        auto controllerButtonPressEvent ( C_ENG_TYPE ( ControllerButtonPressEvent ) * ) noexcept -> C_ENG_TYPE ( Engine ) &;
        auto controllerButtonReleaseEvent ( C_ENG_TYPE ( ControllerButtonReleaseEvent ) * ) noexcept -> C_ENG_TYPE ( Engine ) &;
        auto controllerConnectEvent ( C_ENG_TYPE ( ControllerConnectEvent ) * ) noexcept -> C_ENG_TYPE ( Engine ) &;
        auto controllerDisconnectEvent ( C_ENG_TYPE ( ControllerDisconnectEvent ) * ) noexcept -> C_ENG_TYPE ( Engine ) &;
        auto controllerHatChangeEvent ( C_ENG_TYPE ( ControllerHatChangeEvent ) * ) noexcept -> C_ENG_TYPE ( Engine ) &;

        auto windowCustomEvent ( C_ENG_TYPE ( WindowEvent ) * ) noexcept -> C_ENG_TYPE ( Engine ) &;
        auto windowResizeEvent ( C_ENG_TYPE ( WindowResizeEvent ) * ) noexcept -> C_ENG_TYPE ( Engine ) &;
        auto windowCloseEvent ( C_ENG_TYPE ( WindowCloseEvent ) * ) noexcept -> C_ENG_TYPE ( Engine ) &;
        auto windowFrameBufferResizeEvent ( C_ENG_TYPE ( WindowFrameBufferResizeEvent ) * ) noexcept -> C_ENG_TYPE ( Engine ) &;
        auto windowContentScaleEvent ( C_ENG_TYPE ( WindowContentScaleEvent ) * ) noexcept -> C_ENG_TYPE ( Engine ) &;
        auto windowMoveEvent ( C_ENG_TYPE ( WindowMoveEvent ) * ) noexcept -> C_ENG_TYPE ( Engine ) &;
        auto windowRestoreEvent ( C_ENG_TYPE ( WindowRestoreEvent ) * ) noexcept -> C_ENG_TYPE ( Engine ) &;
        auto windowMinimizeEvent ( C_ENG_TYPE ( WindowMinimizeEvent ) * ) noexcept -> C_ENG_TYPE ( Engine ) &;
        auto windowMaximizeEvent ( C_ENG_TYPE ( WindowMaximizeEvent ) * ) noexcept -> C_ENG_TYPE ( Engine ) &;
        auto windowGainFocusEvent ( C_ENG_TYPE ( WindowGainFocusEvent ) * ) noexcept -> C_ENG_TYPE ( Engine ) &;
        auto windowLoseFocusEvent ( C_ENG_TYPE ( WindowLoseFocusEvent ) * ) noexcept -> C_ENG_TYPE ( Engine ) &;
        auto windowRefreshRequestEvent ( C_ENG_TYPE ( WindowRefreshRequestEvent ) * ) noexcept -> C_ENG_TYPE ( Engine ) &;

        auto keyCustomEvent ( C_ENG_TYPE ( KeyEvent ) * ) noexcept -> C_ENG_TYPE ( Engine ) &;
        auto keyPressEvent ( C_ENG_TYPE ( KeyPressEvent ) * ) noexcept -> C_ENG_TYPE ( Engine ) &;
        auto keyReleaseEvent ( C_ENG_TYPE ( KeyReleaseEvent ) * ) noexcept -> C_ENG_TYPE ( Engine ) &;

        auto mouseCustomEvent ( C_ENG_TYPE ( MouseEvent ) * ) noexcept -> C_ENG_TYPE ( Engine ) &;
        auto mouseMoveEvent ( C_ENG_TYPE ( MouseMoveEvent ) * ) noexcept -> C_ENG_TYPE ( Engine ) &;
        auto mousePressEvent ( C_ENG_TYPE ( MousePressEvent ) * ) noexcept -> C_ENG_TYPE ( Engine ) &;
        auto mouseReleaseEvent ( C_ENG_TYPE ( MouseReleaseEvent ) * ) noexcept -> C_ENG_TYPE ( Engine ) &;
        auto mouseEnterEvent ( C_ENG_TYPE ( MouseEnterEvent ) * ) noexcept -> C_ENG_TYPE ( Engine ) &;
        auto mouseLeaveEvent ( C_ENG_TYPE ( MouseLeaveEvent ) * ) noexcept -> C_ENG_TYPE ( Engine ) &;
        auto mouseScrollEvent ( C_ENG_TYPE ( MouseScrollEvent ) * ) noexcept -> C_ENG_TYPE ( Engine ) &;

        auto shutdownRequested () noexcept -> bool;
    };

}

#endif //C_ENG_ENGINE_HPP

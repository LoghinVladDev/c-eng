//
// Created by loghin on 22.12.2021.
//

#ifndef C_ENG_EVENTHANDLER_HPP
#define C_ENG_EVENTHANDLER_HPP

#include <Preprocess.hpp>
#include <CDS/Utility>

namespace engine {

    class C_ENG_CLASS ( Event );

    class C_ENG_CLASS ( ControllerEvent );

    class C_ENG_CLASS ( ControllerAxisEvent );
    class C_ENG_CLASS ( ControllerButtonPressEvent );
    class C_ENG_CLASS ( ControllerButtonReleaseEvent );
    class C_ENG_CLASS ( ControllerConnectEvent );
    class C_ENG_CLASS ( ControllerDisconnectEvent );
    class C_ENG_CLASS ( ControllerHatEvent );

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

    class C_ENG_CLASS ( EventHandler ) : public cds :: Object {
    public:
        auto customEvent ( C_ENG_TYPE ( Event ) * ) const noexcept -> C_ENG_TYPE ( EventHandler ) const &;

        auto controllerCustomEvent ( C_ENG_TYPE ( ControllerEvent ) * ) const noexcept -> C_ENG_TYPE ( EventHandler ) const &;
        auto controllerAxisEvent ( C_ENG_TYPE ( ControllerAxisEvent ) * ) const noexcept -> C_ENG_TYPE ( EventHandler ) const &;
        auto controllerButtonPressEvent ( C_ENG_TYPE ( ControllerButtonPressEvent ) * ) const noexcept -> C_ENG_TYPE ( EventHandler ) const &;
        auto controllerButtonReleaseEvent ( C_ENG_TYPE ( ControllerButtonReleaseEvent ) * ) const noexcept -> C_ENG_TYPE ( EventHandler ) const &;
        auto controllerConnectEvent ( C_ENG_TYPE ( ControllerConnectEvent ) * ) const noexcept -> C_ENG_TYPE ( EventHandler ) const &;
        auto controllerDisconnectEvent ( C_ENG_TYPE ( ControllerDisconnectEvent ) * ) const noexcept -> C_ENG_TYPE ( EventHandler ) const &;
        auto controllerHatEvent ( C_ENG_TYPE ( ControllerHatEvent ) * ) const noexcept -> C_ENG_TYPE ( EventHandler ) const &;

        auto windowCustomEvent ( C_ENG_TYPE ( WindowEvent ) * ) const noexcept -> C_ENG_TYPE ( EventHandler ) const &;
        auto windowResizeEvent ( C_ENG_TYPE ( WindowResizeEvent ) * ) const noexcept -> C_ENG_TYPE ( EventHandler ) const &;
        auto windowCloseEvent ( C_ENG_TYPE ( WindowCloseEvent ) * ) const noexcept -> C_ENG_TYPE ( EventHandler ) const &;
        auto windowFrameBufferResizeEvent ( C_ENG_TYPE ( WindowFrameBufferResizeEvent ) * ) const noexcept -> C_ENG_TYPE ( EventHandler ) const &;
        auto windowContentScaleEvent ( C_ENG_TYPE ( WindowContentScaleEvent ) * ) const noexcept -> C_ENG_TYPE ( EventHandler ) const &;
        auto windowMoveEvent ( C_ENG_TYPE ( WindowMoveEvent ) * ) const noexcept -> C_ENG_TYPE ( EventHandler ) const &;
        auto windowRestoreEvent ( C_ENG_TYPE ( WindowRestoreEvent ) * ) const noexcept -> C_ENG_TYPE ( EventHandler ) const &;
        auto windowMinimizeEvent ( C_ENG_TYPE ( WindowMinimizeEvent ) * ) const noexcept -> C_ENG_TYPE ( EventHandler ) const &;
        auto windowMaximizeEvent ( C_ENG_TYPE ( WindowMaximizeEvent ) * ) const noexcept -> C_ENG_TYPE ( EventHandler ) const &;
        auto windowGainFocusEvent ( C_ENG_TYPE ( WindowGainFocusEvent ) * ) const noexcept -> C_ENG_TYPE ( EventHandler ) const &;
        auto windowLoseFocusEvent ( C_ENG_TYPE ( WindowLoseFocusEvent ) * ) const noexcept -> C_ENG_TYPE ( EventHandler ) const &;
        auto windowRefreshRequestEvent ( C_ENG_TYPE ( WindowRefreshRequestEvent ) * ) const noexcept -> C_ENG_TYPE ( EventHandler ) const &;

        auto keyCustomEvent ( C_ENG_TYPE ( KeyEvent ) * ) const noexcept -> C_ENG_TYPE ( EventHandler ) const &;
        auto keyPressEvent ( C_ENG_TYPE ( KeyPressEvent ) * ) const noexcept -> C_ENG_TYPE ( EventHandler ) const &;
        auto keyReleaseEvent ( C_ENG_TYPE ( KeyReleaseEvent ) * ) const noexcept -> C_ENG_TYPE ( EventHandler ) const &;

        auto mouseCustomEvent ( C_ENG_TYPE ( MouseEvent ) * ) const noexcept -> C_ENG_TYPE ( EventHandler ) const &;
        auto mouseMoveEvent ( C_ENG_TYPE ( MouseMoveEvent ) * ) const noexcept -> C_ENG_TYPE ( EventHandler ) const &;
        auto mousePressEvent ( C_ENG_TYPE ( MousePressEvent ) * ) const noexcept -> C_ENG_TYPE ( EventHandler ) const &;
        auto mouseReleaseEvent ( C_ENG_TYPE ( MouseReleaseEvent ) * ) const noexcept -> C_ENG_TYPE ( EventHandler ) const &;
        auto mouseEnterEvent ( C_ENG_TYPE ( MouseEnterEvent ) * ) const noexcept -> C_ENG_TYPE ( EventHandler ) const &;
        auto mouseLeaveEvent ( C_ENG_TYPE ( MouseLeaveEvent ) * ) const noexcept -> C_ENG_TYPE ( EventHandler ) const &;
        auto mouseScrollEvent ( C_ENG_TYPE ( MouseScrollEvent ) * ) const noexcept -> C_ENG_TYPE ( EventHandler ) const &;

        C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

}

#endif //C_ENG_EVENTHANDLER_HPP

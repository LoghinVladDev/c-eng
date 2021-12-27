//
// Created by loghin on 22.12.2021.
//

#ifndef __C_ENG_EVENTHANDLER_HPP
#define __C_ENG_EVENTHANDLER_HPP

#include <Preprocess.hpp>
#include <CDS/Utility>

namespace engine {

    __C_ENG_CLASS ( Event );

    __C_ENG_CLASS ( ControllerEvent );

    __C_ENG_CLASS ( ControllerAxisEvent );
    __C_ENG_CLASS ( ControllerButtonPressEvent );
    __C_ENG_CLASS ( ControllerButtonReleaseEvent );
    __C_ENG_CLASS ( ControllerConnectEvent );
    __C_ENG_CLASS ( ControllerDisconnectEvent );
    __C_ENG_CLASS ( ControllerHatEvent );

    __C_ENG_CLASS ( WindowEvent );

    __C_ENG_CLASS ( WindowResizeEvent );
    __C_ENG_CLASS ( WindowCloseEvent );
    __C_ENG_CLASS ( WindowFrameBufferResizeEvent );
    __C_ENG_CLASS ( WindowContentScaleEvent );
    __C_ENG_CLASS ( WindowMoveEvent );
    __C_ENG_CLASS ( WindowRestoreEvent );
    __C_ENG_CLASS ( WindowMinimizeEvent );
    __C_ENG_CLASS ( WindowMaximizeEvent );
    __C_ENG_CLASS ( WindowGainFocusEvent );
    __C_ENG_CLASS ( WindowLoseFocusEvent );
    __C_ENG_CLASS ( WindowRefreshRequestEvent );

    __C_ENG_CLASS ( KeyEvent );

    __C_ENG_CLASS ( KeyPressEvent );
    __C_ENG_CLASS ( KeyReleaseEvent );

    __C_ENG_CLASS ( MouseEvent );

    __C_ENG_CLASS ( MouseMoveEvent );
    __C_ENG_CLASS ( MouseEnterEvent );
    __C_ENG_CLASS ( MouseLeaveEvent );
    __C_ENG_CLASS ( MousePressEvent );
    __C_ENG_CLASS ( MouseReleaseEvent );
    __C_ENG_CLASS ( MouseScrollEvent );

    __C_ENG_CLASS ( EventHandler ) : public cds :: Object {
    public:
        auto customEvent ( __C_ENG_TYPE ( Event ) * ) const noexcept -> __C_ENG_TYPE ( EventHandler ) const &;

        auto controllerCustomEvent ( __C_ENG_TYPE ( ControllerEvent ) * ) const noexcept -> __C_ENG_TYPE ( EventHandler ) const &;
        auto controllerAxisEvent ( __C_ENG_TYPE ( ControllerAxisEvent ) * ) const noexcept -> __C_ENG_TYPE ( EventHandler ) const &;
        auto controllerButtonPressEvent ( __C_ENG_TYPE ( ControllerButtonPressEvent ) * ) const noexcept -> __C_ENG_TYPE ( EventHandler ) const &;
        auto controllerButtonReleaseEvent ( __C_ENG_TYPE ( ControllerButtonReleaseEvent ) * ) const noexcept -> __C_ENG_TYPE ( EventHandler ) const &;
        auto controllerConnectEvent ( __C_ENG_TYPE ( ControllerConnectEvent ) * ) const noexcept -> __C_ENG_TYPE ( EventHandler ) const &;
        auto controllerDisconnectEvent ( __C_ENG_TYPE ( ControllerDisconnectEvent ) * ) const noexcept -> __C_ENG_TYPE ( EventHandler ) const &;
        auto controllerHatEvent ( __C_ENG_TYPE ( ControllerHatEvent ) * ) const noexcept -> __C_ENG_TYPE ( EventHandler ) const &;

        auto windowCustomEvent ( __C_ENG_TYPE ( WindowEvent ) * ) const noexcept -> __C_ENG_TYPE ( EventHandler ) const &;
        auto windowResizeEvent ( __C_ENG_TYPE ( WindowResizeEvent ) * ) const noexcept -> __C_ENG_TYPE ( EventHandler ) const &;
        auto windowCloseEvent ( __C_ENG_TYPE ( WindowCloseEvent ) * ) const noexcept -> __C_ENG_TYPE ( EventHandler ) const &;
        auto windowFrameBufferResizeEvent ( __C_ENG_TYPE ( WindowFrameBufferResizeEvent ) * ) const noexcept -> __C_ENG_TYPE ( EventHandler ) const &;
        auto windowContentScaleEvent ( __C_ENG_TYPE ( WindowContentScaleEvent ) * ) const noexcept -> __C_ENG_TYPE ( EventHandler ) const &;
        auto windowMoveEvent ( __C_ENG_TYPE ( WindowMoveEvent ) * ) const noexcept -> __C_ENG_TYPE ( EventHandler ) const &;
        auto windowRestoreEvent ( __C_ENG_TYPE ( WindowRestoreEvent ) * ) const noexcept -> __C_ENG_TYPE ( EventHandler ) const &;
        auto windowMinimizeEvent ( __C_ENG_TYPE ( WindowMinimizeEvent ) * ) const noexcept -> __C_ENG_TYPE ( EventHandler ) const &;
        auto windowMaximizeEvent ( __C_ENG_TYPE ( WindowMaximizeEvent ) * ) const noexcept -> __C_ENG_TYPE ( EventHandler ) const &;
        auto windowGainFocusEvent ( __C_ENG_TYPE ( WindowGainFocusEvent ) * ) const noexcept -> __C_ENG_TYPE ( EventHandler ) const &;
        auto windowLoseFocusEvent ( __C_ENG_TYPE ( WindowLoseFocusEvent ) * ) const noexcept -> __C_ENG_TYPE ( EventHandler ) const &;
        auto windowRefreshRequestEvent ( __C_ENG_TYPE ( WindowRefreshRequestEvent ) * ) const noexcept -> __C_ENG_TYPE ( EventHandler ) const &;

        auto keyCustomEvent ( __C_ENG_TYPE ( KeyEvent ) * ) const noexcept -> __C_ENG_TYPE ( EventHandler ) const &;
        auto keyPressEvent ( __C_ENG_TYPE ( KeyPressEvent ) * ) const noexcept -> __C_ENG_TYPE ( EventHandler ) const &;
        auto keyReleaseEvent ( __C_ENG_TYPE ( KeyReleaseEvent ) * ) const noexcept -> __C_ENG_TYPE ( EventHandler ) const &;

        auto mouseCustomEvent ( __C_ENG_TYPE ( MouseEvent ) * ) const noexcept -> __C_ENG_TYPE ( EventHandler ) const &;
        auto mouseMoveEvent ( __C_ENG_TYPE ( MouseMoveEvent ) * ) const noexcept -> __C_ENG_TYPE ( EventHandler ) const &;
        auto mousePressEvent ( __C_ENG_TYPE ( MousePressEvent ) * ) const noexcept -> __C_ENG_TYPE ( EventHandler ) const &;
        auto mouseReleaseEvent ( __C_ENG_TYPE ( MouseReleaseEvent ) * ) const noexcept -> __C_ENG_TYPE ( EventHandler ) const &;
        auto mouseEnterEvent ( __C_ENG_TYPE ( MouseEnterEvent ) * ) const noexcept -> __C_ENG_TYPE ( EventHandler ) const &;
        auto mouseLeaveEvent ( __C_ENG_TYPE ( MouseLeaveEvent ) * ) const noexcept -> __C_ENG_TYPE ( EventHandler ) const &;
        auto mouseScrollEvent ( __C_ENG_TYPE ( MouseScrollEvent ) * ) const noexcept -> __C_ENG_TYPE ( EventHandler ) const &;

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

}

#endif //__C_ENG_EVENTHANDLER_HPP

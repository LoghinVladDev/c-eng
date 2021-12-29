//
// Created by loghin on 22.12.2021.
//

#ifndef __C_ENG_EVENTHANDLER_HPP
#define __C_ENG_EVENTHANDLER_HPP

#include <Preprocess.hpp>
#include <CDS/Utility>


#define C_ENG_MAP_START     CLASS ( EventHandler, PARENT ( cds :: Object ) )
#include <ObjectMapping.hpp>

namespace engine {

    __C_ENG_PRE_DECLARE_CLASS ( Event );

    __C_ENG_PRE_DECLARE_CLASS ( ControllerEvent );

    __C_ENG_PRE_DECLARE_CLASS ( ControllerAxisEvent );
    __C_ENG_PRE_DECLARE_CLASS ( ControllerButtonPressEvent );
    __C_ENG_PRE_DECLARE_CLASS ( ControllerButtonReleaseEvent );
    __C_ENG_PRE_DECLARE_CLASS ( ControllerConnectEvent );
    __C_ENG_PRE_DECLARE_CLASS ( ControllerDisconnectEvent );
    __C_ENG_PRE_DECLARE_CLASS ( ControllerHatEvent );

    __C_ENG_PRE_DECLARE_CLASS ( WindowEvent );

    __C_ENG_PRE_DECLARE_CLASS ( WindowResizeEvent );
    __C_ENG_PRE_DECLARE_CLASS ( WindowCloseEvent );
    __C_ENG_PRE_DECLARE_CLASS ( WindowFrameBufferResizeEvent );
    __C_ENG_PRE_DECLARE_CLASS ( WindowContentScaleEvent );
    __C_ENG_PRE_DECLARE_CLASS ( WindowMoveEvent );
    __C_ENG_PRE_DECLARE_CLASS ( WindowRestoreEvent );
    __C_ENG_PRE_DECLARE_CLASS ( WindowMinimizeEvent );
    __C_ENG_PRE_DECLARE_CLASS ( WindowMaximizeEvent );
    __C_ENG_PRE_DECLARE_CLASS ( WindowGainFocusEvent );
    __C_ENG_PRE_DECLARE_CLASS ( WindowLoseFocusEvent );
    __C_ENG_PRE_DECLARE_CLASS ( WindowRefreshRequestEvent );

    __C_ENG_PRE_DECLARE_CLASS ( KeyEvent );

    __C_ENG_PRE_DECLARE_CLASS ( KeyPressEvent );
    __C_ENG_PRE_DECLARE_CLASS ( KeyReleaseEvent );

    __C_ENG_PRE_DECLARE_CLASS ( MouseEvent );

    __C_ENG_PRE_DECLARE_CLASS ( MouseMoveEvent );
    __C_ENG_PRE_DECLARE_CLASS ( MouseEnterEvent );
    __C_ENG_PRE_DECLARE_CLASS ( MouseLeaveEvent );
    __C_ENG_PRE_DECLARE_CLASS ( MousePressEvent );
    __C_ENG_PRE_DECLARE_CLASS ( MouseReleaseEvent );
    __C_ENG_PRE_DECLARE_CLASS ( MouseScrollEvent );

    Class {
    public:
        auto customEvent ( __C_ENG_TYPE ( Event ) * ) const noexcept -> Self const &;

        auto controllerCustomEvent ( __C_ENG_TYPE ( ControllerEvent ) * ) const noexcept -> Self const &;
        auto controllerAxisEvent ( __C_ENG_TYPE ( ControllerAxisEvent ) * ) const noexcept -> Self const &;
        auto controllerButtonPressEvent ( __C_ENG_TYPE ( ControllerButtonPressEvent ) * ) const noexcept -> Self const &;
        auto controllerButtonReleaseEvent ( __C_ENG_TYPE ( ControllerButtonReleaseEvent ) * ) const noexcept -> Self const &;
        auto controllerConnectEvent ( __C_ENG_TYPE ( ControllerConnectEvent ) * ) const noexcept -> Self const &;
        auto controllerDisconnectEvent ( __C_ENG_TYPE ( ControllerDisconnectEvent ) * ) const noexcept -> Self const &;
        auto controllerHatEvent ( __C_ENG_TYPE ( ControllerHatEvent ) * ) const noexcept -> Self const &;

        auto windowCustomEvent ( __C_ENG_TYPE ( WindowEvent ) * ) const noexcept -> Self const &;
        auto windowResizeEvent ( __C_ENG_TYPE ( WindowResizeEvent ) * ) const noexcept -> Self const &;
        auto windowCloseEvent ( __C_ENG_TYPE ( WindowCloseEvent ) * ) const noexcept -> Self const &;
        auto windowFrameBufferResizeEvent ( __C_ENG_TYPE ( WindowFrameBufferResizeEvent ) * ) const noexcept -> Self const &;
        auto windowContentScaleEvent ( __C_ENG_TYPE ( WindowContentScaleEvent ) * ) const noexcept -> Self const &;
        auto windowMoveEvent ( __C_ENG_TYPE ( WindowMoveEvent ) * ) const noexcept -> Self const &;
        auto windowRestoreEvent ( __C_ENG_TYPE ( WindowRestoreEvent ) * ) const noexcept -> Self const &;
        auto windowMinimizeEvent ( __C_ENG_TYPE ( WindowMinimizeEvent ) * ) const noexcept -> Self const &;
        auto windowMaximizeEvent ( __C_ENG_TYPE ( WindowMaximizeEvent ) * ) const noexcept -> Self const &;
        auto windowGainFocusEvent ( __C_ENG_TYPE ( WindowGainFocusEvent ) * ) const noexcept -> Self const &;
        auto windowLoseFocusEvent ( __C_ENG_TYPE ( WindowLoseFocusEvent ) * ) const noexcept -> Self const &;
        auto windowRefreshRequestEvent ( __C_ENG_TYPE ( WindowRefreshRequestEvent ) * ) const noexcept -> Self const &;

        auto keyCustomEvent ( __C_ENG_TYPE ( KeyEvent ) * ) const noexcept -> Self const &;
        auto keyPressEvent ( __C_ENG_TYPE ( KeyPressEvent ) * ) const noexcept -> Self const &;
        auto keyReleaseEvent ( __C_ENG_TYPE ( KeyReleaseEvent ) * ) const noexcept -> Self const &;

        auto mouseCustomEvent ( __C_ENG_TYPE ( MouseEvent ) * ) const noexcept -> Self const &;
        auto mouseMoveEvent ( __C_ENG_TYPE ( MouseMoveEvent ) * ) const noexcept -> Self const &;
        auto mousePressEvent ( __C_ENG_TYPE ( MousePressEvent ) * ) const noexcept -> Self const &;
        auto mouseReleaseEvent ( __C_ENG_TYPE ( MouseReleaseEvent ) * ) const noexcept -> Self const &;
        auto mouseEnterEvent ( __C_ENG_TYPE ( MouseEnterEvent ) * ) const noexcept -> Self const &;
        auto mouseLeaveEvent ( __C_ENG_TYPE ( MouseLeaveEvent ) * ) const noexcept -> Self const &;
        auto mouseScrollEvent ( __C_ENG_TYPE ( MouseScrollEvent ) * ) const noexcept -> Self const &;

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //__C_ENG_EVENTHANDLER_HPP

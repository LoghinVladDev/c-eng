//
// Created by loghin on 22.12.2021.
//

#ifndef __C_ENG_EVENT_HANDLER_HPP__
#define __C_ENG_EVENT_HANDLER_HPP__

#include <Preprocess.hpp>
#include <CDS/Utility>
#include <CDS/Array>


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

    __C_ENG_PRE_DECLARE_CLASS ( EntityEventAdapter );
    __C_ENG_PRE_DECLARE_CLASS ( EntityEventAdapterKeyComponent );
    __C_ENG_PRE_DECLARE_CLASS ( EntityEventAdapterMouseComponent );
    __C_ENG_PRE_DECLARE_CLASS ( EntityEventAdapterControllerComponent );

    __C_ENG_PRE_DECLARE_CLASS ( Scene );

    Class {
    private:
        using MouseEventAdapterList = cds :: Array < Type ( EntityEventAdapterMouseComponent ) * >;
        using KeyEventAdapterList = cds :: Array < Type ( EntityEventAdapterKeyComponent ) * >;
        using ControllerEventAdapterList = cds :: Array < Type ( EntityEventAdapterControllerComponent ) * >;

        Field ( TYPE ( MouseEventAdapterList ),         mouseEventAdapters,         NO_INIT, GET_NONE, SET_NONE )
        Field ( TYPE ( KeyEventAdapterList ),           keyEventAdapters,           NO_INIT, GET_NONE, SET_NONE )
        Field ( TYPE ( ControllerEventAdapterList ),    controllerEventAdapters,    NO_INIT, GET_NONE, SET_NONE )

        Field ( ENGINE_PRIMITIVE_TYPE ( Scene * ),      sceneToStreamTo,            DEFAULT_VALUE ( nullptr ),  GET_NONE,   SET_NONE )

    public:
        auto registerAdapter ( Type ( EntityEventAdapter ) * ) noexcept -> Self &;

        auto startStreamingEventsTo ( Type ( Scene ) * ) noexcept -> Self &;
        auto stopStreamingEventsTo ( Type ( Scene ) * ) noexcept -> Self &;

        auto customEvent ( Type ( Event ) * ) const noexcept -> Self const &;

        auto controllerCustomEvent ( Type ( ControllerEvent ) * ) const noexcept -> Self const &;
        auto controllerAxisEvent ( Type ( ControllerAxisEvent ) * ) const noexcept -> Self const &;
        auto controllerButtonPressEvent ( Type ( ControllerButtonPressEvent ) * ) const noexcept -> Self const &;
        auto controllerButtonReleaseEvent ( Type ( ControllerButtonReleaseEvent ) * ) const noexcept -> Self const &;
        auto controllerConnectEvent ( Type ( ControllerConnectEvent ) * ) const noexcept -> Self const &;
        auto controllerDisconnectEvent ( Type ( ControllerDisconnectEvent ) * ) const noexcept -> Self const &;
        auto controllerHatEvent ( Type ( ControllerHatEvent ) * ) const noexcept -> Self const &;

        auto windowCustomEvent ( Type ( WindowEvent ) * ) const noexcept -> Self const &;
        auto windowResizeEvent ( Type ( WindowResizeEvent ) * ) const noexcept -> Self const &;
        auto windowCloseEvent ( Type ( WindowCloseEvent ) * ) const noexcept -> Self const &;
        auto windowFrameBufferResizeEvent ( Type ( WindowFrameBufferResizeEvent ) * ) const noexcept -> Self const &;
        auto windowContentScaleEvent ( Type ( WindowContentScaleEvent ) * ) const noexcept -> Self const &;
        auto windowMoveEvent ( Type ( WindowMoveEvent ) * ) const noexcept -> Self const &;
        auto windowRestoreEvent ( Type ( WindowRestoreEvent ) * ) const noexcept -> Self const &;
        auto windowMinimizeEvent ( Type ( WindowMinimizeEvent ) * ) const noexcept -> Self const &;
        auto windowMaximizeEvent ( Type ( WindowMaximizeEvent ) * ) const noexcept -> Self const &;
        auto windowGainFocusEvent ( Type ( WindowGainFocusEvent ) * ) const noexcept -> Self const &;
        auto windowLoseFocusEvent ( Type ( WindowLoseFocusEvent ) * ) const noexcept -> Self const &;
        auto windowRefreshRequestEvent ( Type ( WindowRefreshRequestEvent ) * ) const noexcept -> Self const &;

        auto keyCustomEvent ( Type ( KeyEvent ) * ) const noexcept -> Self const &;
        auto keyPressEvent ( Type ( KeyPressEvent ) * ) const noexcept -> Self const &;
        auto keyReleaseEvent ( Type ( KeyReleaseEvent ) * ) const noexcept -> Self const &;

        auto mouseCustomEvent ( Type ( MouseEvent ) * ) const noexcept -> Self const &;
        auto mouseMoveEvent ( Type ( MouseMoveEvent ) * ) const noexcept -> Self const &;
        auto mousePressEvent ( Type ( MousePressEvent ) * ) const noexcept -> Self const &;
        auto mouseReleaseEvent ( Type ( MouseReleaseEvent ) * ) const noexcept -> Self const &;
        auto mouseEnterEvent ( Type ( MouseEnterEvent ) * ) const noexcept -> Self const &;
        auto mouseLeaveEvent ( Type ( MouseLeaveEvent ) * ) const noexcept -> Self const &;
        auto mouseScrollEvent ( Type ( MouseScrollEvent ) * ) const noexcept -> Self const &;

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //__C_ENG_EVENT_HANDLER_HPP__

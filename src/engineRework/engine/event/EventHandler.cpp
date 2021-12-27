//
// Created by loghin on 22.12.2021.
//

#include "EventHandler.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

#include <Event.hpp>
auto __C_ENG_TYPE ( EventHandler ) :: customEvent (
        __C_ENG_TYPE ( Event ) * pEvent
) const noexcept -> __C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

#include <ControllerEvent.hpp>
auto __C_ENG_TYPE ( EventHandler ) :: controllerCustomEvent (
        __C_ENG_TYPE ( ControllerEvent ) * pEvent
) const noexcept -> __C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

#include <ControllerAxisEvent.hpp>
auto __C_ENG_TYPE ( EventHandler ) :: controllerAxisEvent (
        __C_ENG_TYPE ( ControllerAxisEvent ) * pEvent
) const noexcept -> __C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

#include <ControllerButtonPressEvent.hpp>
auto __C_ENG_TYPE ( EventHandler ) :: controllerButtonPressEvent (
        __C_ENG_TYPE ( ControllerButtonPressEvent ) * pEvent
) const noexcept -> __C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

#include <ControllerButtonReleaseEvent.hpp>
auto __C_ENG_TYPE ( EventHandler ) :: controllerButtonReleaseEvent (
        __C_ENG_TYPE ( ControllerButtonReleaseEvent ) * pEvent
) const noexcept -> __C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

#include <ControllerConnectEvent.hpp>
auto __C_ENG_TYPE ( EventHandler ) :: controllerConnectEvent (
        __C_ENG_TYPE ( ControllerConnectEvent ) * pEvent
) const noexcept -> __C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

#include <ControllerDisconnectEvent.hpp>
auto __C_ENG_TYPE ( EventHandler ) :: controllerDisconnectEvent (
        __C_ENG_TYPE ( ControllerDisconnectEvent ) * pEvent
) const noexcept -> __C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

#include <ControllerHatEvent.hpp>
auto __C_ENG_TYPE ( EventHandler ) :: controllerHatEvent (
        __C_ENG_TYPE ( ControllerHatEvent ) * pEvent
) const noexcept -> __C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

#include <WindowEvent.hpp>
auto __C_ENG_TYPE ( EventHandler ) :: windowCustomEvent (
        __C_ENG_TYPE ( WindowEvent ) * pEvent
) const noexcept -> __C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

#include <WindowResizeEvent.hpp>
auto __C_ENG_TYPE ( EventHandler ) :: windowResizeEvent (
        __C_ENG_TYPE ( WindowResizeEvent ) * pEvent
) const noexcept -> __C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

#include <WindowCloseEvent.hpp>
auto __C_ENG_TYPE ( EventHandler ) :: windowCloseEvent (
        __C_ENG_TYPE ( WindowCloseEvent ) * pEvent
) const noexcept -> __C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

#include <WindowFrameBufferResizeEvent.hpp>
auto __C_ENG_TYPE ( EventHandler ) :: windowFrameBufferResizeEvent (
        __C_ENG_TYPE ( WindowFrameBufferResizeEvent ) * pEvent
) const noexcept -> __C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

#include <WindowContentScaleEvent.hpp>
auto __C_ENG_TYPE ( EventHandler ) :: windowContentScaleEvent (
        __C_ENG_TYPE ( WindowContentScaleEvent ) * pEvent
) const noexcept -> __C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

#include <WindowMoveEvent.hpp>
auto __C_ENG_TYPE ( EventHandler ) :: windowMoveEvent (
        __C_ENG_TYPE ( WindowMoveEvent ) * pEvent
) const noexcept -> __C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

#include <WindowRestoreEvent.hpp>
auto __C_ENG_TYPE ( EventHandler ) :: windowRestoreEvent (
        __C_ENG_TYPE ( WindowRestoreEvent ) * pEvent
) const noexcept -> __C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

#include <WindowMinimizeEvent.hpp>
auto __C_ENG_TYPE ( EventHandler ) :: windowMinimizeEvent (
        __C_ENG_TYPE ( WindowMinimizeEvent ) * pEvent
) const noexcept -> __C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

#include <WindowMaximizeEvent.hpp>
auto __C_ENG_TYPE ( EventHandler ) :: windowMaximizeEvent (
        __C_ENG_TYPE ( WindowMaximizeEvent ) * pEvent
) const noexcept -> __C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

#include <WindowGainFocusEvent.hpp>
auto __C_ENG_TYPE ( EventHandler ) :: windowGainFocusEvent (
        __C_ENG_TYPE ( WindowGainFocusEvent ) * pEvent
) const noexcept -> __C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

#include <WindowLoseFocusEvent.hpp>
auto __C_ENG_TYPE ( EventHandler ) :: windowLoseFocusEvent (
        __C_ENG_TYPE ( WindowLoseFocusEvent ) * pEvent
) const noexcept -> __C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

#include <WindowRefreshRequestEvent.hpp>
auto __C_ENG_TYPE ( EventHandler ) :: windowRefreshRequestEvent (
        __C_ENG_TYPE ( WindowRefreshRequestEvent ) * pEvent
) const noexcept -> __C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

#include <KeyEvent.hpp>
auto __C_ENG_TYPE ( EventHandler ) :: keyCustomEvent (
        __C_ENG_TYPE ( KeyEvent ) * pEvent
) const noexcept -> __C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

#include <KeyPressEvent.hpp>
auto __C_ENG_TYPE ( EventHandler ) :: keyPressEvent (
        __C_ENG_TYPE ( KeyPressEvent ) * pEvent
) const noexcept -> __C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

#include <KeyReleaseEvent.hpp>
auto __C_ENG_TYPE ( EventHandler ) :: keyReleaseEvent (
        __C_ENG_TYPE ( KeyReleaseEvent ) * pEvent
) const noexcept -> __C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

#include <MouseEvent.hpp>
auto __C_ENG_TYPE ( EventHandler ) :: mouseCustomEvent (
        __C_ENG_TYPE ( MouseEvent ) * pEvent
) const noexcept -> __C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

#include <MouseMoveEvent.hpp>
auto __C_ENG_TYPE ( EventHandler ) :: mouseMoveEvent (
        __C_ENG_TYPE ( MouseMoveEvent ) * pEvent
) const noexcept -> __C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

#include <MousePressEvent.hpp>
auto __C_ENG_TYPE ( EventHandler ) :: mousePressEvent (
        __C_ENG_TYPE ( MousePressEvent ) * pEvent
) const noexcept -> __C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

#include <MouseReleaseEvent.hpp>
auto __C_ENG_TYPE ( EventHandler ) :: mouseReleaseEvent (
        __C_ENG_TYPE ( MouseReleaseEvent ) * pEvent
) const noexcept -> __C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

#include <MouseEnterEvent.hpp>
auto __C_ENG_TYPE ( EventHandler ) :: mouseEnterEvent (
        __C_ENG_TYPE ( MouseEnterEvent ) * pEvent
) const noexcept -> __C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

#include <MouseLeaveEvent.hpp>
auto __C_ENG_TYPE ( EventHandler ) :: mouseLeaveEvent (
        __C_ENG_TYPE ( MouseLeaveEvent ) * pEvent
) const noexcept -> __C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

#include <MouseScrollEvent.hpp>
auto __C_ENG_TYPE ( EventHandler ) :: mouseScrollEvent (
        __C_ENG_TYPE ( MouseScrollEvent ) * pEvent
) const noexcept -> __C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

auto __C_ENG_TYPE ( EventHandler ) :: toString () const noexcept -> String {
    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( EventHandler ) ) " {}";
}
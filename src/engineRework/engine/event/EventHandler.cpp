//
// Created by loghin on 22.12.2021.
//

#include "EventHandler.hpp"

#include <Event.hpp>

#include <ControllerEvent.hpp>
#include <ControllerAxisEvent.hpp>
#include <ControllerButtonPressEvent.hpp>
#include <ControllerButtonReleaseEvent.hpp>
#include <ControllerConnectEvent.hpp>
#include <ControllerDisconnectEvent.hpp>
#include <ControllerHatEvent.hpp>

#include <WindowEvent.hpp>
#include <WindowResizeEvent.hpp>
#include <WindowCloseEvent.hpp>
#include <WindowFrameBufferResizeEvent.hpp>
#include <WindowContentScaleEvent.hpp>
#include <WindowMoveEvent.hpp>
#include <WindowRestoreEvent.hpp>
#include <WindowMinimizeEvent.hpp>
#include <WindowMaximizeEvent.hpp>
#include <WindowGainFocusEvent.hpp>
#include <WindowLoseFocusEvent.hpp>
#include <WindowRefreshRequestEvent.hpp>

#include <KeyEvent.hpp>
#include <KeyPressEvent.hpp>
#include <KeyReleaseEvent.hpp>

#include <MouseEvent.hpp>
#include <MouseMoveEvent.hpp>
#include <MousePressEvent.hpp>
#include <MouseReleaseEvent.hpp>
#include <MouseEnterEvent.hpp>
#include <MouseLeaveEvent.hpp>
#include <MouseScrollEvent.hpp>


using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)


#undef __C_ENG_OBJECT_NAME
#define __C_ENG_OBJECT_NAME EventHandler /* NOLINT(bugprone-reserved-identifier) */


auto __C_ENG_SELF :: customEvent (
        __C_ENG_TYPE ( Event ) * pEvent
) const noexcept -> __C_ENG_SELF const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

auto __C_ENG_SELF :: controllerCustomEvent (
        __C_ENG_TYPE ( ControllerEvent ) * pEvent
) const noexcept -> __C_ENG_SELF const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

auto __C_ENG_SELF :: controllerAxisEvent (
        __C_ENG_TYPE ( ControllerAxisEvent ) * pEvent
) const noexcept -> __C_ENG_SELF const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

auto __C_ENG_SELF :: controllerButtonPressEvent (
        __C_ENG_TYPE ( ControllerButtonPressEvent ) * pEvent
) const noexcept -> __C_ENG_SELF const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

auto __C_ENG_SELF :: controllerButtonReleaseEvent (
        __C_ENG_TYPE ( ControllerButtonReleaseEvent ) * pEvent
) const noexcept -> __C_ENG_SELF const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

auto __C_ENG_SELF :: controllerConnectEvent (
        __C_ENG_TYPE ( ControllerConnectEvent ) * pEvent
) const noexcept -> __C_ENG_SELF const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

auto __C_ENG_SELF :: controllerDisconnectEvent (
        __C_ENG_TYPE ( ControllerDisconnectEvent ) * pEvent
) const noexcept -> __C_ENG_SELF const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

auto __C_ENG_SELF :: controllerHatEvent (
        __C_ENG_TYPE ( ControllerHatEvent ) * pEvent
) const noexcept -> __C_ENG_SELF const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

auto __C_ENG_SELF :: windowCustomEvent (
        __C_ENG_TYPE ( WindowEvent ) * pEvent
) const noexcept -> __C_ENG_SELF const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

auto __C_ENG_SELF :: windowResizeEvent (
        __C_ENG_TYPE ( WindowResizeEvent ) * pEvent
) const noexcept -> __C_ENG_SELF const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

auto __C_ENG_SELF :: windowCloseEvent (
        __C_ENG_TYPE ( WindowCloseEvent ) * pEvent
) const noexcept -> __C_ENG_SELF const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

auto __C_ENG_SELF :: windowFrameBufferResizeEvent (
        __C_ENG_TYPE ( WindowFrameBufferResizeEvent ) * pEvent
) const noexcept -> __C_ENG_SELF const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

auto __C_ENG_SELF :: windowContentScaleEvent (
        __C_ENG_TYPE ( WindowContentScaleEvent ) * pEvent
) const noexcept -> __C_ENG_SELF const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

auto __C_ENG_SELF :: windowMoveEvent (
        __C_ENG_TYPE ( WindowMoveEvent ) * pEvent
) const noexcept -> __C_ENG_SELF const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

auto __C_ENG_SELF :: windowRestoreEvent (
        __C_ENG_TYPE ( WindowRestoreEvent ) * pEvent
) const noexcept -> __C_ENG_SELF const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

auto __C_ENG_SELF :: windowMinimizeEvent (
        __C_ENG_TYPE ( WindowMinimizeEvent ) * pEvent
) const noexcept -> __C_ENG_SELF const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

auto __C_ENG_SELF :: windowMaximizeEvent (
        __C_ENG_TYPE ( WindowMaximizeEvent ) * pEvent
) const noexcept -> __C_ENG_SELF const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

auto __C_ENG_SELF :: windowGainFocusEvent (
        __C_ENG_TYPE ( WindowGainFocusEvent ) * pEvent
) const noexcept -> __C_ENG_SELF const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

auto __C_ENG_SELF :: windowLoseFocusEvent (
        __C_ENG_TYPE ( WindowLoseFocusEvent ) * pEvent
) const noexcept -> __C_ENG_SELF const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

auto __C_ENG_SELF :: windowRefreshRequestEvent (
        __C_ENG_TYPE ( WindowRefreshRequestEvent ) * pEvent
) const noexcept -> __C_ENG_SELF const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

auto __C_ENG_SELF :: keyCustomEvent (
        __C_ENG_TYPE ( KeyEvent ) * pEvent
) const noexcept -> __C_ENG_SELF const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

auto __C_ENG_SELF :: keyPressEvent (
        __C_ENG_TYPE ( KeyPressEvent ) * pEvent
) const noexcept -> __C_ENG_SELF const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

auto __C_ENG_SELF :: keyReleaseEvent (
        __C_ENG_TYPE ( KeyReleaseEvent ) * pEvent
) const noexcept -> __C_ENG_SELF const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

auto __C_ENG_SELF :: mouseCustomEvent (
        __C_ENG_TYPE ( MouseEvent ) * pEvent
) const noexcept -> __C_ENG_SELF const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

auto __C_ENG_SELF :: mouseMoveEvent (
        __C_ENG_TYPE ( MouseMoveEvent ) * pEvent
) const noexcept -> __C_ENG_SELF const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

auto __C_ENG_SELF :: mousePressEvent (
        __C_ENG_TYPE ( MousePressEvent ) * pEvent
) const noexcept -> __C_ENG_SELF const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

auto __C_ENG_SELF :: mouseReleaseEvent (
        __C_ENG_TYPE ( MouseReleaseEvent ) * pEvent
) const noexcept -> __C_ENG_SELF const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

auto __C_ENG_SELF :: mouseEnterEvent (
        __C_ENG_TYPE ( MouseEnterEvent ) * pEvent
) const noexcept -> __C_ENG_SELF const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

auto __C_ENG_SELF :: mouseLeaveEvent (
        __C_ENG_TYPE ( MouseLeaveEvent ) * pEvent
) const noexcept -> __C_ENG_SELF const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

auto __C_ENG_SELF :: mouseScrollEvent (
        __C_ENG_TYPE ( MouseScrollEvent ) * pEvent
) const noexcept -> __C_ENG_SELF const & {
    std :: cout << pEvent->toString() << '\n';

    return * this;
}

auto __C_ENG_SELF :: toString () const noexcept -> String {
    return __C_ENG_STRINGIFY ( __C_ENG_SELF ) " {}";
}
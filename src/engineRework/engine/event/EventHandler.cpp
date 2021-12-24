//
// Created by loghin on 22.12.2021.
//

#include "EventHandler.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

auto C_ENG_CLASS ( EventHandler ) :: customEvent (
        C_ENG_TYPE ( Event ) * pEvent
) const noexcept -> C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << "Custom Event\n";

    return * this;
}

auto C_ENG_CLASS ( EventHandler ) :: controllerCustomEvent (
        C_ENG_TYPE ( ControllerEvent ) * pEvent
) const noexcept -> C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << "Controller Custom Event\n";

    return * this;
}

auto C_ENG_CLASS ( EventHandler ) :: controllerAxisEvent (
        C_ENG_TYPE ( ControllerAxisEvent ) * pEvent
) const noexcept -> C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << "Controller Axis Event\n";

    return * this;
}

auto C_ENG_CLASS ( EventHandler ) :: controllerButtonPressEvent (
        C_ENG_TYPE ( ControllerButtonPressEvent ) * pEvent
) const noexcept -> C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << "Controller Button Press Event\n";

    return * this;
}

auto C_ENG_CLASS ( EventHandler ) :: controllerButtonReleaseEvent (
        C_ENG_TYPE ( ControllerButtonReleaseEvent ) * pEvent
) const noexcept -> C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << "Controller Button Release Event\n";

    return * this;
}

auto C_ENG_CLASS ( EventHandler ) :: controllerConnectEvent (
        C_ENG_TYPE ( ControllerConnectEvent ) * pEvent
) const noexcept -> C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << "Controller Connect Event\n";

    return * this;
}

auto C_ENG_CLASS ( EventHandler ) :: controllerDisconnectEvent (
        C_ENG_TYPE ( ControllerDisconnectEvent ) * pEvent
) const noexcept -> C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << "Controller Disconnect Event\n";

    return * this;
}

auto C_ENG_CLASS ( EventHandler ) :: controllerHatEvent (
        C_ENG_TYPE ( ControllerHatEvent ) * pEvent
) const noexcept -> C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << "Controller Hat Event\n";

    return * this;
}

auto C_ENG_CLASS ( EventHandler ) :: windowCustomEvent (
        C_ENG_TYPE ( WindowEvent ) * pEvent
) const noexcept -> C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << "Window Custom Event\n";

    return * this;
}

auto C_ENG_CLASS ( EventHandler ) :: windowResizeEvent (
        C_ENG_TYPE ( WindowResizeEvent ) * pEvent
) const noexcept -> C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << "Window Resize Event\n";

    return * this;
}

auto C_ENG_CLASS ( EventHandler ) :: windowCloseEvent (
        C_ENG_TYPE ( WindowCloseEvent ) * pEvent
) const noexcept -> C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << "Window Close Event\n";

    return * this;
}

auto C_ENG_CLASS ( EventHandler ) :: windowFrameBufferResizeEvent (
        C_ENG_TYPE ( WindowFrameBufferResizeEvent ) * pEvent
) const noexcept -> C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << "Window Frame Buffer Resize Event\n";

    return * this;
}

auto C_ENG_CLASS ( EventHandler ) :: windowContentScaleEvent (
        C_ENG_TYPE ( WindowContentScaleEvent ) * pEvent
) const noexcept -> C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << "Window Content Scale Event\n";

    return * this;
}

auto C_ENG_CLASS ( EventHandler ) :: windowMoveEvent (
        C_ENG_TYPE ( WindowMoveEvent ) * pEvent
) const noexcept -> C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << "Window Move Event\n";

    return * this;
}

auto C_ENG_CLASS ( EventHandler ) :: windowRestoreEvent (
        C_ENG_TYPE ( WindowRestoreEvent ) * pEvent
) const noexcept -> C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << "Window Restore Event\n";

    return * this;
}

auto C_ENG_CLASS ( EventHandler ) :: windowMinimizeEvent (
        C_ENG_TYPE ( WindowMinimizeEvent ) * pEvent
) const noexcept -> C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << "Window Minimize Event\n";

    return * this;
}

auto C_ENG_CLASS ( EventHandler ) :: windowMaximizeEvent (
        C_ENG_TYPE ( WindowMaximizeEvent ) * pEvent
) const noexcept -> C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << "Window Maximize Event\n";

    return * this;
}

auto C_ENG_CLASS ( EventHandler ) :: windowGainFocusEvent (
        C_ENG_TYPE ( WindowGainFocusEvent ) * pEvent
) const noexcept -> C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << "Window Gain Focus Event\n";

    return * this;
}

auto C_ENG_CLASS ( EventHandler ) :: windowLoseFocusEvent (
        C_ENG_TYPE ( WindowLoseFocusEvent ) * pEvent
) const noexcept -> C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << "Window Lose Focus Event\n";

    return * this;
}

auto C_ENG_CLASS ( EventHandler ) :: windowRefreshRequestEvent (
        C_ENG_TYPE ( WindowRefreshRequestEvent ) * pEvent
) const noexcept -> C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << "Window Refresh Request Event\n";

    return * this;
}

auto C_ENG_CLASS ( EventHandler ) :: keyCustomEvent (
        C_ENG_TYPE ( KeyEvent ) * pEvent
) const noexcept -> C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << "Key Custom Event\n";

    return * this;
}

auto C_ENG_CLASS ( EventHandler ) :: keyPressEvent (
        C_ENG_TYPE ( KeyPressEvent ) * pEvent
) const noexcept -> C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << "Key Press Event\n";

    return * this;
}

auto C_ENG_CLASS ( EventHandler ) :: keyReleaseEvent (
        C_ENG_TYPE ( KeyReleaseEvent ) * pEvent
) const noexcept -> C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << "Key Release Event\n";

    return * this;
}

auto C_ENG_CLASS ( EventHandler ) :: mouseCustomEvent (
        C_ENG_TYPE ( MouseEvent ) * pEvent
) const noexcept -> C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << "Mouse Custom Event\n";

    return * this;
}

auto C_ENG_CLASS ( EventHandler ) :: mouseMoveEvent (
        C_ENG_TYPE ( MouseMoveEvent ) * pEvent
) const noexcept -> C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << "Mouse Move Event\n";

    return * this;
}

auto C_ENG_CLASS ( EventHandler ) :: mousePressEvent (
        C_ENG_TYPE ( MousePressEvent ) * pEvent
) const noexcept -> C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << "Mouse Press Event\n";

    return * this;
}

auto C_ENG_CLASS ( EventHandler ) :: mouseReleaseEvent (
        C_ENG_TYPE ( MouseReleaseEvent ) * pEvent
) const noexcept -> C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << "Mouse Release Event\n";

    return * this;
}

auto C_ENG_CLASS ( EventHandler ) :: mouseEnterEvent (
        C_ENG_TYPE ( MouseEnterEvent ) * pEvent
) const noexcept -> C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << "Mouse Enter Event\n";

    return * this;
}

auto C_ENG_CLASS ( EventHandler ) :: mouseLeaveEvent (
        C_ENG_TYPE ( MouseLeaveEvent ) * pEvent
) const noexcept -> C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << "Mouse Leave Event\n";

    return * this;
}

auto C_ENG_CLASS ( EventHandler ) :: mouseScrollEvent (
        C_ENG_TYPE ( MouseScrollEvent ) * pEvent
) const noexcept -> C_ENG_TYPE ( EventHandler ) const & {
    std :: cout << "Mouse Scroll Event\n";

    return * this;
}

auto C_ENG_CLASS ( EventHandler ) :: toString () const noexcept -> String {
    return "EventHandler {}";
}
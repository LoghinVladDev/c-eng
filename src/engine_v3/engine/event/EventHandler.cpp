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

#include <scene/ECM/components/eventAdapter/EntityEventAdapter.hpp>
#include <src/engineRework/engine/scene/ECM/components/eventAdapter/component/EntityEventAdapterMouseComponent.hpp>
#include <src/engineRework/engine/scene/ECM/components/eventAdapter/component/EntityEventAdapterKeyComponent.hpp>
#include <src/engineRework/engine/scene/ECM/components/eventAdapter/component/EntityEventAdapterControllerComponent.hpp>

#include <scene/Scene.hpp>


using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)


#define C_ENG_MAP_START     CLASS ( EventHandler, EXTERNAL_PARENT ( cds :: Object ) )
#include <ObjectMapping.hpp>

auto Self :: customEvent (
        __C_ENG_TYPE ( Event ) * pEvent
) const noexcept -> Self const & {

    return * this;
}

auto Self :: controllerCustomEvent (
        __C_ENG_TYPE ( ControllerEvent ) * pEvent
) const noexcept -> Self const & {

    return * this;
}

auto Self :: controllerAxisEvent (
        __C_ENG_TYPE ( ControllerAxisEvent ) * pEvent
) const noexcept -> Self const & {

    for ( auto adapterIndex = 0; adapterIndex < this->_controllerEventAdapters.size(); ++ adapterIndex ) {
        this->_controllerEventAdapters [ adapterIndex ]->controllerAxisEvent ( pEvent );
    }

    return * this;
}

auto Self :: controllerButtonPressEvent (
        __C_ENG_TYPE ( ControllerButtonPressEvent ) * pEvent
) const noexcept -> Self const & {

    for ( auto adapterIndex = 0; adapterIndex < this->_controllerEventAdapters.size(); ++ adapterIndex ) {
        this->_controllerEventAdapters [ adapterIndex ]->controllerButtonPressEvent ( pEvent );
    }

    return * this;
}

auto Self :: controllerButtonReleaseEvent (
        __C_ENG_TYPE ( ControllerButtonReleaseEvent ) * pEvent
) const noexcept -> Self const & {

    for ( auto adapterIndex = 0; adapterIndex < this->_controllerEventAdapters.size(); ++ adapterIndex ) {
        this->_controllerEventAdapters [ adapterIndex ]->controllerButtonReleaseEvent ( pEvent );
    }

    return * this;
}

auto Self :: controllerConnectEvent (
        __C_ENG_TYPE ( ControllerConnectEvent ) * pEvent
) const noexcept -> Self const & {

    return * this;
}

auto Self :: controllerDisconnectEvent (
        __C_ENG_TYPE ( ControllerDisconnectEvent ) * pEvent
) const noexcept -> Self const & {

    return * this;
}

auto Self :: controllerHatEvent (
        __C_ENG_TYPE ( ControllerHatEvent ) * pEvent
) const noexcept -> Self const & {

    for ( auto adapterIndex = 0; adapterIndex < this->_controllerEventAdapters.size(); ++ adapterIndex ) {
        this->_controllerEventAdapters [ adapterIndex ]->controllerHatEvent ( pEvent );
    }

    return * this;
}

auto Self :: windowCustomEvent (
        __C_ENG_TYPE ( WindowEvent ) * pEvent
) const noexcept -> Self const & {

    return * this;
}

auto Self :: windowResizeEvent (
        __C_ENG_TYPE ( WindowResizeEvent ) * pEvent
) const noexcept -> Self const & {

    return * this;
}

auto Self :: windowCloseEvent (
        __C_ENG_TYPE ( WindowCloseEvent ) * pEvent
) const noexcept -> Self const & {

    return * this;
}

auto Self :: windowFrameBufferResizeEvent (
        __C_ENG_TYPE ( WindowFrameBufferResizeEvent ) * pEvent
) const noexcept -> Self const & {

    return * this;
}

auto Self :: windowContentScaleEvent (
        __C_ENG_TYPE ( WindowContentScaleEvent ) * pEvent
) const noexcept -> Self const & {

    return * this;
}

auto Self :: windowMoveEvent (
        __C_ENG_TYPE ( WindowMoveEvent ) * pEvent
) const noexcept -> Self const & {

    return * this;
}

auto Self :: windowRestoreEvent (
        __C_ENG_TYPE ( WindowRestoreEvent ) * pEvent
) const noexcept -> Self const & {

    return * this;
}

auto Self :: windowMinimizeEvent (
        __C_ENG_TYPE ( WindowMinimizeEvent ) * pEvent
) const noexcept -> Self const & {

    return * this;
}

auto Self :: windowMaximizeEvent (
        __C_ENG_TYPE ( WindowMaximizeEvent ) * pEvent
) const noexcept -> Self const & {

    return * this;
}

auto Self :: windowGainFocusEvent (
        __C_ENG_TYPE ( WindowGainFocusEvent ) * pEvent
) const noexcept -> Self const & {

    return * this;
}

auto Self :: windowLoseFocusEvent (
        __C_ENG_TYPE ( WindowLoseFocusEvent ) * pEvent
) const noexcept -> Self const & {

    return * this;
}

auto Self :: windowRefreshRequestEvent (
        __C_ENG_TYPE ( WindowRefreshRequestEvent ) * pEvent
) const noexcept -> Self const & {

    return * this;
}

auto Self :: keyCustomEvent (
        __C_ENG_TYPE ( KeyEvent ) * pEvent
) const noexcept -> Self const & {

    return * this;
}

auto Self :: keyPressEvent (
        __C_ENG_TYPE ( KeyPressEvent ) * pEvent
) const noexcept -> Self const & {

    for ( auto adapterIndex = 0; adapterIndex < this->_keyEventAdapters.size(); ++ adapterIndex ) {
        this->_keyEventAdapters [ adapterIndex ]->keyPressEvent ( pEvent );
    }

    return * this;
}

auto Self :: keyReleaseEvent (
        __C_ENG_TYPE ( KeyReleaseEvent ) * pEvent
) const noexcept -> Self const & {

    for ( auto adapterIndex = 0; adapterIndex < this->_keyEventAdapters.size(); ++ adapterIndex ) {
        this->_keyEventAdapters [ adapterIndex ]->keyReleaseEvent ( pEvent );
    }

    return * this;
}

auto Self :: mouseCustomEvent (
        __C_ENG_TYPE ( MouseEvent ) * pEvent
) const noexcept -> Self const & {

    return * this;
}

auto Self :: mouseMoveEvent (
        __C_ENG_TYPE ( MouseMoveEvent ) * pEvent
) const noexcept -> Self const & {

    for ( auto adapterIndex = 0; adapterIndex < this->_mouseEventAdapters.size(); ++ adapterIndex ) {
        this->_mouseEventAdapters [ adapterIndex ]->mouseMoveEvent ( pEvent );
    }

    return * this;
}

auto Self :: mousePressEvent (
        __C_ENG_TYPE ( MousePressEvent ) * pEvent
) const noexcept -> Self const & {

    for ( auto adapterIndex = 0; adapterIndex < this->_mouseEventAdapters.size(); ++ adapterIndex ) {
        this->_mouseEventAdapters [ adapterIndex ]->mousePressEvent ( pEvent );
    }

    return * this;
}

auto Self :: mouseReleaseEvent (
        __C_ENG_TYPE ( MouseReleaseEvent ) * pEvent
) const noexcept -> Self const & {

    for ( auto adapterIndex = 0; adapterIndex < this->_mouseEventAdapters.size(); ++ adapterIndex ) {
        this->_mouseEventAdapters [ adapterIndex ]->mouseReleaseEvent ( pEvent );
    }

    return * this;
}

auto Self :: mouseEnterEvent (
        __C_ENG_TYPE ( MouseEnterEvent ) * pEvent
) const noexcept -> Self const & {

    return * this;
}

auto Self :: mouseLeaveEvent (
        __C_ENG_TYPE ( MouseLeaveEvent ) * pEvent
) const noexcept -> Self const & {

    return * this;
}

auto Self :: mouseScrollEvent (
        __C_ENG_TYPE ( MouseScrollEvent ) * pEvent
) const noexcept -> Self const & {

    for ( auto adapterIndex = 0; adapterIndex < this->_mouseEventAdapters.size(); ++ adapterIndex ) {
        this->_mouseEventAdapters [ adapterIndex ]->mouseScrollEvent ( pEvent );
    }

    return * this;
}

auto Self :: toString () const noexcept -> String {
    return __C_ENG_STRINGIFY ( Self ) " {}";
}

auto Self :: registerAdapter ( Type ( EntityEventAdapter ) * pEventAdapter ) noexcept -> Self & {

    if ( pEventAdapter->mouseEventAdapter() != nullptr ) {
        (void) this->_mouseEventAdapters.pushBack ( pEventAdapter->mouseEventAdapter() );
    }

    if ( pEventAdapter->keyEventAdapter() != nullptr ) {
        (void) this->_keyEventAdapters.pushBack ( pEventAdapter->keyEventAdapter() );
    }

    if ( pEventAdapter->controllerEventAdapter() != nullptr ) {
        (void) this->_controllerEventAdapters.pushBack ( pEventAdapter->controllerEventAdapter() );
    }

    return * this;
}

auto Self :: startStreamingEventsTo ( Type ( Scene ) * pScene ) noexcept -> Self & {

    for ( auto & entity : pScene->entities() ) {
        if ( entity->eventAdapter() != nullptr ) {
            if ( entity->eventAdapter()->controllerEventAdapter() != nullptr ) {
                (void) this->_controllerEventAdapters.pushBack ( entity->eventAdapter()->controllerEventAdapter() );
            }

            if ( entity->eventAdapter()->keyEventAdapter() != nullptr ) {
                (void) this->_keyEventAdapters.pushBack ( entity->eventAdapter()->keyEventAdapter() );
            }

            if ( entity->eventAdapter()->mouseEventAdapter() != nullptr ) {
                (void) this->_mouseEventAdapters.pushBack ( entity->eventAdapter()->mouseEventAdapter() );
            }
        }
    }

    return * this;
}

auto Self :: stopStreamingEventsTo ( Type ( Scene ) * pScene ) noexcept -> Self & {

    if ( this->_sceneToStreamTo == pScene ) {
        this->_sceneToStreamTo = nullptr;

        (void) this->_mouseEventAdapters.clear();
        (void) this->_keyEventAdapters.clear();
        (void) this->_controllerEventAdapters.clear();
    }

    return * this;
}

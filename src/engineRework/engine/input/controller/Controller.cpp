//
// Created by loghin on 22.12.2021.
//

#include "Controller.hpp"

#include <Gamepad.hpp>
#include <Joystick.hpp>

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

static auto controllerConnectEventRootCallback (
    sint32,
    sint32
) noexcept -> void;

namespace engine {

    struct ControllerHandler {
        Array < C_ENG_TYPE ( Controller ) * > connectedControllers; // NOLINT(clion-misra-cpp2008-11-0-1)

        inline auto connectController ( sint32 ) noexcept -> void;
        inline auto disconnectController ( sint32 ) noexcept -> void;

        ControllerHandler () noexcept {
            (void) glfwSetJoystickCallback ( & controllerConnectEventRootCallback );

            for ( sint32 joystickID = 0; joystickID <= GLFW_JOYSTICK_LAST; ++ joystickID ) {
                if ( static_cast < bool > ( glfwJoystickPresent ( joystickID ) ) ) { // NOLINT(clion-misra-cpp2008-5-0-13)
                    if ( static_cast < bool > ( glfwJoystickIsGamepad ( joystickID ) ) ) { // NOLINT(clion-misra-cpp2008-5-0-13)

                        (void) connectedControllers.pushBack ( new C_ENG_TYPE ( Gamepad ) );
                        reinterpret_cast < C_ENG_TYPE ( Gamepad ) * > ( connectedControllers.back() )->_gamepadName =
                                glfwGetGamepadName ( joystickID );

                    } else {

                        (void) connectedControllers.pushBack ( new C_ENG_TYPE ( Joystick ) );

                    }

                    connectedControllers.back()->_handle = joystickID;
                    connectedControllers.back()->_name = glfwGetJoystickName ( joystickID );

                }
            }
        }

        ~ControllerHandler() noexcept {
            for ( auto * pController : connectedControllers ) {
                delete pController;
            }
        }
    };

}

static ControllerHandler handler;
static C_ENG_TYPE ( Engine ) * pGlobalEngine;

auto C_ENG_CLASS ( Controller ) :: setEngine (
        C_ENG_TYPE ( Engine ) * pEngine
) noexcept -> void {
    pGlobalEngine = pEngine;
}

#include <Engine.hpp>

auto controllerConnectEventRootCallback (
        sint32  controllerID,
        sint32  connectEvent
) noexcept -> void {
    if ( connectEvent == GLFW_CONNECTED ) {

        handler.connectController ( controllerID );

    } else if ( connectEvent == GLFW_DISCONNECTED ) {

        handler.disconnectController ( controllerID );

    } else {
        // do nothing
    }
}

#include <ControllerConnectEvent.hpp>

auto ControllerHandler :: connectController (
        sint32 controllerID
) noexcept -> void {

    C_ENG_TYPE ( Controller ) * pNewController = nullptr;
    if ( static_cast < bool > ( glfwJoystickIsGamepad ( controllerID ) ) ) { // NOLINT(clion-misra-cpp2008-5-0-13)

        pNewController = new C_ENG_TYPE ( Gamepad );
        reinterpret_cast < C_ENG_TYPE ( Gamepad ) * > ( pNewController )->_gamepadName = glfwGetGamepadName ( controllerID );

    } else {

        pNewController = new C_ENG_TYPE ( Joystick );

    }

    pNewController->_handle = controllerID;
    pNewController->_name = glfwGetJoystickName ( controllerID );

    (void) connectedControllers.pushBack ( pNewController );

    if ( pGlobalEngine != nullptr ) {

        C_ENG_TYPE ( ControllerConnectEvent ) event ( pNewController );
        (void) pGlobalEngine->controllerConnectEvent ( & event );

    }
}

#include <ControllerDisconnectEvent.hpp>

auto ControllerHandler :: disconnectController (
        sint32 controllerID
) noexcept -> void {

    C_ENG_TYPE ( Controller ) * pController = nullptr;
    for ( auto * pConnectedController : connectedControllers ) {
        if ( controllerID == pConnectedController->handle() ) {
            pController = pConnectedController;
            break;
        }
    }

    if ( pController == nullptr ) {
        return;
    }

    if ( pGlobalEngine != nullptr ) {

        C_ENG_TYPE ( ControllerDisconnectEvent ) event ( pController );
        (void) pGlobalEngine->controllerDisconnectEvent ( & event );

    }

}

auto C_ENG_CLASS ( Controller ) :: updateEvents () noexcept -> void {

    for ( auto * pController : handler.connectedControllers ) {
        pController->update();
    }

}

enum ControllerEventType : uint8 {
    Axis    = 0x00U,
    Button  = 0x01U,
    Hat     = 0x02U
};

struct ButtonEvent {
    bool                state;
    uint16              buttonID;
};

struct AxisEvent {
    uint16              axisID;
    float               oldValue;
    float               newValue;
};

struct HatEvent {
    uint8               hatState;
    uint16              hatID;
};

struct ControllerEvent { // NOLINT(clion-misra-cpp2008-0-1-7)
    C_ENG_TYPE ( Controller ) :: Handle handle;
    ControllerEventType                 type;

    union { // NOLINT(clion-misra-cpp2008-9-5-1)
        ButtonEvent buttonEvent;
        AxisEvent axisEvent;
        HatEvent hatEvent;
    };
};

ControllerEvent activeEvents[512];
uint32          activeEventCount;

auto C_ENG_CLASS ( Gamepad ) :: update () noexcept -> void {
    GLFWgamepadstate currentState;

    (void) glfwGetGamepadState ( this->handle(), & currentState );

    if ( this->_firstUpdate ) {
        (void) std :: memcpy ( this->_axes, currentState.axes, sizeof ( this->_axes ) ); // NOLINT(clion-misra-cpp2008-5-2-12)
        for ( uint32 i = 0U; i < buttonCount; ++ i ) {
            if ( static_cast < sint32 > ( currentState.buttons[i] ) == GLFW_PRESS ) {
                this->_buttons[i] = true;
            } else {
                this->_buttons[i] = false;
            }
        }

        this->_firstUpdate = false;
    } else {

        for ( uint32 i = 0U; i < axesCount; ++ i ) {
            if ( this->_axes[i] != currentState.axes[i] ) {

                activeEvents[activeEventCount ++] = (ControllerEvent) {
                    .handle     = this->handle(),
                    .type       = ControllerEventType :: Axis,
                    .axisEvent  = (AxisEvent) {
                        .axisID     = static_cast < uint16 > ( i ),
                        .oldValue   = this->_axes[i],
                        .newValue   = currentState.axes[i]
                    }
                };

                this->_axes[i] = currentState.axes[i];

            }
        }

        for ( uint32 i = 0U; i < buttonCount; ++ i ) {

            bool current = false;
            if ( static_cast < sint32 > ( currentState.buttons[i] ) == GLFW_PRESS ) {
                current = true;
            }

            if ( this->_buttons[i] != current ) {

                activeEvents[activeEventCount ++] = (ControllerEvent) {
                    .handle         = this->handle(),
                    .type           = ControllerEventType :: Button,
                    .buttonEvent    = (ButtonEvent) {
                        .state          = current,
                        .buttonID       = static_cast < uint16 > ( i )
                    }
                };

                this->_buttons[i] = current;
            }
        }

    }
}

auto C_ENG_CLASS ( Joystick ) :: update () noexcept -> void {
    sint32 readAxisCount;
    sint32 readButtonCount;
    sint32 readHatCount;

    float const * readAxes;
    uint8 const * readButtons;
    uint8 const * readHats;

    readAxes = glfwGetJoystickAxes ( this->handle(), & readAxisCount );
    readButtons = glfwGetJoystickButtons ( this->handle(), & readButtonCount );
    readHats = glfwGetJoystickHats ( this->handle(), & readHatCount );

    if ( static_cast < uint32 > ( readAxisCount ) != this->axisCount() ) {
        delete[] this->_axes;

        this->_axisCount = static_cast < uint32 > ( readAxisCount );
        this->_axes = new float [this->_axisCount];
        (void) std :: memcpy ( this->_axes, readAxes, sizeof ( float ) * this->_axisCount );
    } else {

        for ( sint32 i = 0; i < readAxisCount; ++ i ) {
            if ( this->_axes[i] != readAxes[i] ) {

                activeEvents[activeEventCount ++] = (ControllerEvent) {
                    .handle     = this->handle(),
                    .type       = ControllerEventType :: Axis,
                    .axisEvent  = (AxisEvent) {
                        .axisID     = static_cast < uint16 > ( i ),
                        .oldValue   = this->_axes[i],
                        .newValue   = readAxes[i]
                    }
                };

                this->_axes[i] = readAxes[i];
            }
        }

    }

    if ( static_cast < uint32 > ( readButtonCount ) != this->buttonCount() ) {
        delete[] this->_buttons;

        this->_buttonCount = static_cast < uint32 > ( readButtonCount );
        this->_buttons = new bool [this->_buttonCount];
        for ( int i = 0; i < readButtonCount; ++ i ) {
            if ( static_cast < sint32 > ( readButtons[i] ) == GLFW_PRESS ) {
                this->_buttons[i] = true;
            } else {
                this->_buttons[i] = false;
            }
        }
    } else {

        for ( sint32 i = 0; i < readButtonCount; ++ i ) {
            bool current = false;
            if ( static_cast < sint32 > ( readButtons[i] ) == GLFW_PRESS ) {
                current = true;
            }

            if ( this->_buttons[i] != current ) {

                activeEvents[activeEventCount ++] = (ControllerEvent) {
                    .handle         = this->handle(),
                    .type           = ControllerEventType :: Button,
                    .buttonEvent    = (ButtonEvent) {
                        .state          = current,
                        .buttonID       = static_cast < uint16 > ( i )
                    }
                };

                this->_buttons[i] = current;
            }
        }

    }

    if ( static_cast < uint32 > ( readHatCount ) != this->hatCount() ) {
        delete[] this->_hats;

        this->_hatCount = static_cast < uint32 > ( readHatCount );
        this->_hats = new uint8 [this->_buttonCount];
        (void) std :: memcpy ( this->_hats, readHats, sizeof ( uint8 ) * this->_hatCount );
    } else {

        for ( sint32 i = 0; i < readHatCount; ++ i ) {
            if ( this->_hats[i] != readHats[i] ) { // NOLINT(clion-misra-cpp2008-5-0-4)

                activeEvents[activeEventCount ++] = ( ControllerEvent ) {
                    .handle     = this->handle(),
                    .type       = ControllerEventType :: Hat,
                    .hatEvent   = (HatEvent) {
                        .hatState   = readHats[i],
                        .hatID      = static_cast < uint16 > ( i )
                    }
                };

                this->_hats[i] = readHats[i];
            }
        }

    }
}

static inline auto controllerAxisEventRootCallback (
        C_ENG_TYPE ( Controller ) :: Handle handle,
        uint16                              axis,
        float                               newValue,
        float                               oldValue
) noexcept -> void {

}

static inline auto controllerButtonEventRootCallback (
        C_ENG_TYPE ( Controller ) :: Handle handle,
        uint16                              button,
        bool                                pressed
) noexcept -> void {

}

static inline auto controllerHatEventRootCallback (
        C_ENG_TYPE ( Controller ) :: Handle handle,
        uint16                              hat,
        uint8                               state
) noexcept -> void {

}

auto C_ENG_CLASS ( Controller ) :: pollEvents() noexcept -> void {

    for ( uint32 i = 0U; i < activeEventCount; ++ i ) {
        if ( activeEvents[i].type == ControllerEventType :: Axis ) {

            controllerAxisEventRootCallback(
                    activeEvents[i].handle,
                    activeEvents[i].axisEvent.axisID,
                    activeEvents[i].axisEvent.newValue,
                    activeEvents[i].axisEvent.oldValue
            );

        } else if ( activeEvents[i].type == ControllerEventType :: Button ) {

            controllerButtonEventRootCallback(
                    activeEvents[i].handle,
                    activeEvents[i].buttonEvent.buttonID,
                    activeEvents[i].buttonEvent.state
            );

        } else if ( activeEvents[i].type == ControllerEventType :: Hat ) {

            controllerHatEventRootCallback(
                    activeEvents[i].handle,
                    activeEvents[i].hatEvent.hatID,
                    activeEvents[i].hatEvent.hatState
            );

        } else {
            /// do nothing
        }
    }

    activeEventCount = 0U;
}
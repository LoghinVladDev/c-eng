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
        __C_ENG_TYPE ( Controller ) * connectedControllers [__C_ENG_TYPE(Controller) :: controllerCapacity] { nullptr }; // NOLINT(clion-misra-cpp2008-11-0-1)
        uint32 connectedControllerCount {0U}; // NOLINT(clion-misra-cpp2008-11-0-1)

        inline auto connectController ( sint32 ) noexcept -> void;
        inline auto disconnectController ( sint32 ) noexcept -> void;

        ControllerHandler () noexcept {
            (void) glfwSetJoystickCallback ( & controllerConnectEventRootCallback );

            for ( sint32 joystickID = 0; joystickID <= GLFW_JOYSTICK_LAST; ++ joystickID ) {
                if ( static_cast < bool > ( glfwJoystickPresent ( joystickID ) ) ) { // NOLINT(clion-misra-cpp2008-5-0-13)

                    __C_ENG_TYPE ( Controller ) * pNewController = nullptr;

                    if ( static_cast < bool > ( glfwJoystickIsGamepad ( joystickID ) ) ) { // NOLINT(clion-misra-cpp2008-5-0-13)

                        pNewController = new __C_ENG_TYPE ( Gamepad );
                        reinterpret_cast < __C_ENG_TYPE ( Gamepad ) * > ( pNewController )->_gamepadName =
                                glfwGetGamepadName ( joystickID );

                    } else {

                        pNewController = new __C_ENG_TYPE ( Joystick );

                    }

                    pNewController->_handle = joystickID;
                    pNewController->_name = glfwGetJoystickName ( joystickID );

                    glfwSetJoystickUserPointer ( joystickID, reinterpret_cast < void * > ( pNewController ) );
                    connectedControllers[connectedControllerCount ++] = pNewController;

                }
            }
        }

        ~ControllerHandler() noexcept {
            for ( uint32 i = 0U; i < connectedControllerCount; ++ i ) {
                delete connectedControllers[ static_cast < sint32 > ( i ) ];
            }
        }
    };

}

static ControllerHandler handler;
static __C_ENG_TYPE ( Engine ) * pGlobalEngine;

auto __C_ENG_TYPE ( Controller ) :: setEngine (
        __C_ENG_TYPE ( Engine ) * pEngine
) noexcept -> void {
    pGlobalEngine = pEngine;
}

#include <Engine.hpp>

static auto controllerConnectEventRootCallback (
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

__C_ENG_MAYBE_UNUSED auto __C_ENG_TYPE ( Controller ) :: connectedControllerCount () noexcept -> uint32 {
    return handler.connectedControllerCount;
}

__C_ENG_MAYBE_UNUSED auto __C_ENG_TYPE ( Controller ) :: connectedControllers () noexcept -> __C_ENG_TYPE ( Controller ) ** {
    return handler.connectedControllers;
}

#include <ControllerConnectEvent.hpp>
#include <Logger.hpp>

auto ControllerHandler :: connectController (
        sint32 controllerID
) noexcept -> void {

    __C_ENG_TYPE ( Controller ) * pNewController = nullptr;
    if ( static_cast < bool > ( glfwJoystickIsGamepad ( controllerID ) ) ) { // NOLINT(clion-misra-cpp2008-5-0-13)

        pNewController = new __C_ENG_TYPE ( Gamepad );
        reinterpret_cast < __C_ENG_TYPE ( Gamepad ) * > ( pNewController )->_gamepadName = glfwGetGamepadName ( controllerID );

    } else {

        pNewController = new __C_ENG_TYPE ( Joystick );

    }

    pNewController->_handle = controllerID;
    pNewController->_name = glfwGetJoystickName ( controllerID );

    connectedControllers [ connectedControllerCount ++ ] = pNewController;

    glfwSetJoystickUserPointer ( controllerID, reinterpret_cast < void * > ( pNewController ) );

    if ( pGlobalEngine != nullptr ) {

        __C_ENG_TYPE ( ControllerConnectEvent ) event ( pNewController );
        (void) pGlobalEngine->eventHandler().controllerConnectEvent ( & event );

    }

    (void) __C_ENG_TYPE ( Logger ) :: instance ().info ( "Controller "_s + controllerID + " Connected" );
}

#include <ControllerDisconnectEvent.hpp>

auto ControllerHandler :: disconnectController (
        sint32 controllerID
) noexcept -> void {

    __C_ENG_TYPE ( Controller ) * pController = nullptr;
    __C_ENG_TYPE ( Controller ) * pTempBuffer [ __C_ENG_TYPE ( Controller ) :: controllerCapacity ] { nullptr };
    uint32 tempBufferLength = 0U;

    for ( uint32 i = 0U; i < connectedControllerCount; ++ i ) {
        if ( controllerID == connectedControllers[i]->handle() ) {
            pController = connectedControllers[i];
        } else {
            pTempBuffer[tempBufferLength ++] = connectedControllers[i];
        }
    }

    if ( pController == nullptr ) {
        return;
    } else {
        (void) std :: memcpy ( connectedControllers, pTempBuffer, sizeof ( __C_ENG_TYPE ( Controller ) * ) * __C_ENG_TYPE ( Controller ) :: controllerCapacity ); // NOLINT(clion-misra-cpp2008-5-2-12,bugprone-sizeof-expression)
        -- connectedControllerCount;
    }

    if ( pGlobalEngine != nullptr ) {

        __C_ENG_TYPE ( ControllerDisconnectEvent ) event ( pController );
        (void) pGlobalEngine->eventHandler().controllerDisconnectEvent ( & event );

    }

    (void) __C_ENG_TYPE ( Logger ) :: instance ().info ( "Controller "_s + controllerID + " Disconnected" );

}

auto __C_ENG_TYPE ( Controller ) :: updateEvents () noexcept -> void {

    for ( uint32 i = 0U; i < handler.connectedControllerCount; ++ i ) {
        handler.connectedControllers[i]->update();
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
    __C_ENG_TYPE ( Controller ) :: Handle handle;
    ControllerEventType                 type;

    union { // NOLINT(clion-misra-cpp2008-9-5-1)
        ButtonEvent buttonEvent;
        AxisEvent   axisEvent;
        HatEvent    hatEvent;
    };
};

ControllerEvent activeEvents[512];
uint32          activeEventCount;

auto __C_ENG_TYPE ( Gamepad ) :: update () noexcept -> void {
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

auto __C_ENG_TYPE ( Joystick ) :: update () noexcept -> void {
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

#include <ControllerAxisEvent.hpp>

static inline auto controllerAxisEventRootCallback (
        __C_ENG_TYPE ( Controller ) :: Handle handle,
        uint16                              axis,
        float                               newValue,
        float                               oldValue
) noexcept -> void {
    auto pObject = reinterpret_cast < __C_ENG_TYPE ( Controller ) * > ( glfwGetJoystickUserPointer ( handle ) );
    if ( pGlobalEngine != nullptr ) {

        __C_ENG_TYPE ( ControllerAxisEvent ) event (
                pObject,
                axis,
                newValue,
                oldValue
        );

        (void) pGlobalEngine->eventHandler().controllerAxisEvent ( & event );

    }
}

#include <ControllerButtonPressEvent.hpp>
#include <ControllerButtonReleaseEvent.hpp>

static inline auto controllerButtonEventRootCallback (
        __C_ENG_TYPE ( Controller ) :: Handle handle,
        uint16                              button,
        bool                                pressed
) noexcept -> void {
    auto pObject = reinterpret_cast < __C_ENG_TYPE ( Controller ) * > ( glfwGetJoystickUserPointer ( handle ) );
    if ( pGlobalEngine != nullptr ) {

        if ( pressed ) {

            __C_ENG_TYPE ( ControllerButtonPressEvent ) event (
                    pObject,
                    button
            );

            (void) pGlobalEngine->eventHandler().controllerButtonPressEvent ( & event );

        } else {

            __C_ENG_TYPE ( ControllerButtonReleaseEvent ) event (
                    pObject,
                    button
            );

            (void) pGlobalEngine->eventHandler().controllerButtonReleaseEvent ( & event );

        }

    }
}

#include <ControllerHatEvent.hpp>

static inline auto controllerHatEventRootCallback (
        __C_ENG_TYPE ( Controller ) :: Handle handle,
        uint16                              hat,
        uint8                               state
) noexcept -> void {
    auto pObject = reinterpret_cast < __C_ENG_TYPE ( Controller ) * > ( glfwGetJoystickUserPointer ( handle ) );
    if ( pGlobalEngine != nullptr ) {

        __C_ENG_TYPE ( ControllerHatEvent ) event (
                pObject,
                hat,
                static_cast < __C_ENG_TYPE ( ControllerHatState ) > ( state )
        );

        (void) pGlobalEngine->eventHandler().controllerHatEvent ( & event );

    }
}

#include <SimpleEventQueue.hpp>
static engine :: utility :: SimpleEventQueue < __C_ENG_TYPE ( ControllerEvent ) * > customEvents;

__C_ENG_MAYBE_UNUSED auto __C_ENG_TYPE ( Controller ) :: handleEvent (
        __C_ENG_TYPE ( ControllerEvent ) const & event
) noexcept -> void {
    (void) customEvents.push( event.copy() );
}

auto __C_ENG_TYPE ( Controller ) :: pollEvents() noexcept -> void {

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

    while ( ! customEvents.empty() ) {
        auto currentEvent = customEvents.pop();
        
        if ( pGlobalEngine != nullptr ) {
            (void) pGlobalEngine->eventHandler().controllerCustomEvent ( currentEvent );
        }

        delete currentEvent;
    }

    activeEventCount = 0U;
}

auto __C_ENG_TYPE ( Controller ) :: toString () const noexcept -> String {
    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( Controller ) ) " "
           "{ handle = "_s      + this->handle() +
           ", name = "          + this->name() +
           " }";
}

auto __C_ENG_TYPE ( Controller ) :: equals (
        Object const & object
) const noexcept -> bool {

    if ( this == & object ) {
        return true;
    }

    auto pController = dynamic_cast < decltype ( this ) > ( & object );

    return this->handle() == pController->handle();
}
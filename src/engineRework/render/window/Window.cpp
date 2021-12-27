//
// Created by loghin on 19.12.2021.
//

#include "Window.hpp"

#include <CDS/Array>

#include <Logger.hpp>
#include <Settings.hpp>
#include <Monitor.hpp>
#include <Engine.hpp>

#include <WindowFrameBufferResizeEvent.hpp>
#include <WindowResizeEvent.hpp>
#include <WindowCloseEvent.hpp>
#include <WindowContentScaleEvent.hpp>
#include <WindowMoveEvent.hpp>
#include <WindowMinimizeEvent.hpp>
#include <WindowRestoreEvent.hpp>
#include <WindowMaximizeEvent.hpp>
#include <WindowGainFocusEvent.hpp>
#include <WindowLoseFocusEvent.hpp>
#include <WindowRefreshRequestEvent.hpp>
#include <KeyPressEvent.hpp>
#include <KeyReleaseEvent.hpp>
#include <MouseMoveEvent.hpp>
#include <MouseEnterEvent.hpp>
#include <MouseLeaveEvent.hpp>
#include <MousePressEvent.hpp>
#include <MouseReleaseEvent.hpp>
#include <MouseScrollEvent.hpp>


using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)


#undef __C_ENG_OBJECT_NAME
#define __C_ENG_OBJECT_NAME Window /* NOLINT(bugprone-reserved-identifier) */


bool __GLFWActive = false; // NOLINT(bugprone-reserved-identifier)
static Array < __C_ENG_SELF const * > activeWindows;

constexpr static auto GLFWErrorCodeName ( int errorCode ) noexcept -> StringLiteral {
    StringLiteral errorName;

    switch ( errorCode ) {
        case GLFW_NOT_INITIALIZED:      { errorName = "GLFW_NOT_INITIALIZED";       break; }
        case GLFW_NO_CURRENT_CONTEXT:   { errorName = "GLFW_NO_CURRENT_CONTEXT";    break; }
        case GLFW_INVALID_ENUM:         { errorName = "GLFW_INVALID_ENUM";          break; }
        case GLFW_INVALID_VALUE:        { errorName = "GLFW_INVALID_VALUE";         break; }
        case GLFW_OUT_OF_MEMORY:        { errorName = "GLFW_OUT_OF_MEMORY";         break; }
        case GLFW_API_UNAVAILABLE:      { errorName = "GLFW_API_UNAVAILABLE";       break; }
        case GLFW_VERSION_UNAVAILABLE:  { errorName = "GLFW_VERSION_UNAVAILABLE";   break; }
        case GLFW_PLATFORM_ERROR:       { errorName = "GLFW_PLATFORM_ERROR";        break; }
        case GLFW_FORMAT_UNAVAILABLE:   { errorName = "GLFW_FORMAT_UNAVAILABLE";    break; }
        default:                        { errorName = "Unknown";                    break; }
    }

    return errorName;
}

static auto GLFWErrorCallback ( int errorCode, StringLiteral errorMessage ) noexcept -> void {
    (void) __C_ENG_TYPE ( Logger ) :: instance().error (
            "GLFW Error : "_s + GLFWErrorCodeName ( errorCode ) + " -> " + errorMessage
    );
}

auto __initializeGLFW () noexcept (false) -> void { // NOLINT(bugprone-reserved-identifier)
    if ( __GLFWActive ) {
        return;
    }

    (void) __C_ENG_TYPE ( Logger ) :: instance ().info ("Initializing GLFW");

    if ( glfwInit () == GLFW_FALSE ) {
        (void) __C_ENG_TYPE ( Logger ) :: instance ().fatal ("GLFW Could not be initialized");
        throw RuntimeException ( "GLFW Initialization Failure" );
    }

    (void) glfwSetErrorCallback ( & GLFWErrorCallback );

    (void) __C_ENG_TYPE ( Logger ) :: instance ().info ("GLFW Initialized");
    (void) __C_ENG_TYPE ( Logger ) :: instance ().info (
            "Compiled GLFW : "_s +
            GLFW_VERSION_MAJOR +
            "." +
            GLFW_VERSION_MINOR +
            "." +
            GLFW_VERSION_REVISION
    );

    sint32 runtimeMajor;
    sint32 runtimeMinor;
    sint32 runtimeRevision;
    glfwGetVersion ( & runtimeMajor, & runtimeMinor, & runtimeRevision );

    (void) __C_ENG_TYPE ( Logger ) :: instance ().info (
            "Runtime GLFW : "_s +
            runtimeMajor +
            "." +
            runtimeMinor +
            "." +
            runtimeRevision
    );

    __GLFWActive = true;
}

static auto terminateGLFW () noexcept -> void {
    if ( ! __GLFWActive ) {
        return;
    }

    glfwTerminate();
}

static auto windowFrameBufferResizeEventRootCallback (
        __C_ENG_SELF :: Handle,
        sint32,
        sint32
) noexcept -> void;

static auto windowResizeEventRootCallback (
        __C_ENG_SELF :: Handle,
        sint32,
        sint32
) noexcept -> void;

static auto windowCloseEventRootCallback (
        __C_ENG_SELF :: Handle
) noexcept -> void;

static auto windowContentScaleEventRootCallback (
        __C_ENG_SELF :: Handle,
        float,
        float
) noexcept -> void;

static auto windowMoveEventRootCallback (
        __C_ENG_SELF :: Handle,
        sint32,
        sint32
) noexcept -> void;

static auto windowMinimizeEventRootCallback (
        __C_ENG_SELF :: Handle,
        sint32
) noexcept -> void;

static auto windowMaximizeEventRootCallback (
        __C_ENG_SELF :: Handle,
        sint32
) noexcept -> void;

static auto windowFocusEventRootCallback (
        __C_ENG_SELF :: Handle,
        sint32
) noexcept -> void;

static auto windowRefreshRequestEventRootCallback (
        __C_ENG_SELF :: Handle
) noexcept -> void;

static auto keyEventRootCallback (
        __C_ENG_SELF :: Handle,
        sint32,
        sint32,
        sint32,
        sint32
) noexcept -> void;

static auto mouseMoveEventRootCallback (
        __C_ENG_SELF :: Handle,
        double,
        double
) noexcept -> void;

static auto mouseEnterEventRootCallback (
        __C_ENG_SELF :: Handle,
        sint32
) noexcept -> void;

static auto mousePressEventRootCallback (
        __C_ENG_SELF :: Handle,
        sint32,
        sint32,
        sint32
) noexcept -> void;

static auto mouseScrollEventRootCallback (
        __C_ENG_SELF :: Handle,
        double,
        double
) noexcept -> void;

auto __C_ENG_SELF :: init () noexcept (false) -> __C_ENG_SELF & {
    __initializeGLFW();

    (void) __C_ENG_TYPE ( Logger ) :: instance().info("Initializing Window");

    if ( this->_handle != nullptr ) {
        (void) __C_ENG_TYPE ( Logger ) :: instance().debug("Window Already Initialized, returning");
        return * this;
    }

    auto resolution = __C_ENG_TYPE ( Settings ) :: instance().get( __C_ENG_TYPE ( Settings ) :: keyResolution );

    this->_size = ( __C_ENG_TYPE ( Size ) ) {
        .width  = static_cast < uint32 > ( ( resolution >> 32 ) & 0xFFFFFFFFU ),
        .height = static_cast < uint32 > ( resolution & 0xFFFFFFFFU )
    };

    glfwWindowHint ( GLFW_CLIENT_API, GLFW_NO_API );

    __C_ENG_TYPE ( Monitor ) :: Handle pMonitorHandle = nullptr;

    if ( this->_type != __C_ENG_TYPE ( WindowType ) :: WindowTypeWindowed ) {
        pMonitorHandle = this->_monitor->handle();

        if ( this->_type == __C_ENG_TYPE ( WindowType ) :: WindowTypeWindowedFullscreen ) {

            glfwWindowHint ( GLFW_RED_BITS,     static_cast < sint32 > ( this->_monitor->properties().activeVideoMode.colorChannelsDepth.red ) );
            glfwWindowHint ( GLFW_GREEN_BITS,   static_cast < sint32 > ( this->_monitor->properties().activeVideoMode.colorChannelsDepth.green ) );
            glfwWindowHint ( GLFW_BLUE_BITS,    static_cast < sint32 > ( this->_monitor->properties().activeVideoMode.colorChannelsDepth.blue ) );
            glfwWindowHint ( GLFW_REFRESH_RATE, static_cast < sint32 > ( this->_monitor->properties().activeVideoMode.refreshRate ) );

            this->_size = ( __C_ENG_TYPE ( Size ) ) {
                .width  = static_cast < uint32 > ( this->_monitor->properties().activeVideoMode.size.width ),
                .height = static_cast < uint32 > ( this->_monitor->properties().activeVideoMode.size.height )
            };

            (void) __C_ENG_TYPE ( Settings ) :: instance().set (
                    __C_ENG_TYPE ( Settings ) :: keyResolution,
                    ( static_cast < uint64 > ( this->_size.width ) << 32 ) | static_cast < uint64 > ( this->_size.height )
            );

        }

        this->_monitor->_windowOnMonitor = this;
    }

    this->applyFlagHints();
    this->_handle = glfwCreateWindow (
            static_cast < sint32 > ( this->size().width ),
            static_cast < sint32 > ( this->size().height ),
            this->_title.cStr(),
            nullptr,
            nullptr
    );

    glfwSetWindowUserPointer ( this->handle(), reinterpret_cast < void * > ( this ) );
    glfwDefaultWindowHints();

    (void) glfwSetWindowSizeCallback            ( this->handle(), & windowResizeEventRootCallback );
    (void) glfwSetFramebufferSizeCallback       ( this->handle(), & windowFrameBufferResizeEventRootCallback );
    (void) glfwSetWindowCloseCallback           ( this->handle(), & windowCloseEventRootCallback );
    (void) glfwSetWindowContentScaleCallback    ( this->handle(), & windowContentScaleEventRootCallback );
    (void) glfwSetWindowPosCallback             ( this->handle(), & windowMoveEventRootCallback );
    (void) glfwSetWindowIconifyCallback         ( this->handle(), & windowMinimizeEventRootCallback );
    (void) glfwSetWindowMaximizeCallback        ( this->handle(), & windowMaximizeEventRootCallback );
    (void) glfwSetWindowFocusCallback           ( this->handle(), & windowFocusEventRootCallback );
    (void) glfwSetWindowRefreshCallback         ( this->handle(), & windowRefreshRequestEventRootCallback );

    (void) glfwSetKeyCallback                   ( this->handle(), & keyEventRootCallback );

    (void) glfwSetCursorPosCallback             ( this->handle(), & mouseMoveEventRootCallback );
    (void) glfwSetCursorEnterCallback           ( this->handle(), & mouseEnterEventRootCallback );
    (void) glfwSetMouseButtonCallback           ( this->handle(), & mousePressEventRootCallback );
    (void) glfwSetScrollCallback                ( this->handle(), & mouseScrollEventRootCallback );

    glfwSetInputMode ( this->handle(), GLFW_LOCK_KEY_MODS, GLFW_TRUE );

    if ( static_cast < bool > ( __C_ENG_TYPE ( Settings ) :: instance().get( __C_ENG_TYPE ( Settings ) :: keyMouseCursorEnabled ) ) ) { // NOLINT(clion-misra-cpp2008-5-0-13)
        (void) this->releaseMouseCursor();
    } else {
        (void) this->grabMouseCursor();
    }

    sint32 xPos;
    sint32 yPos;
    glfwGetWindowPos ( this->handle(), & xPos, & yPos );

    this->_position = ( __C_ENG_TYPE ( Position ) ) {
        .x =    static_cast < uint32 > ( xPos ),
        .y =    static_cast < uint32 > ( yPos )
    };

    activeWindows.add (this);
    return * this;
}

auto __C_ENG_SELF :: setEngine ( __C_ENG_TYPE ( Engine ) * engine ) noexcept -> __C_ENG_SELF & {
    this->_engine = engine;
    return * this;
}

auto __C_ENG_SELF :: grabMouseCursor () noexcept -> __C_ENG_SELF & {
    glfwSetInputMode ( this->_handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
    if ( glfwRawMouseMotionSupported() ) { // NOLINT(clion-misra-cpp2008-5-0-13)
        glfwSetInputMode ( this->_handle, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE );
    }

    return * this;
}

auto __C_ENG_SELF :: releaseMouseCursor () noexcept -> __C_ENG_SELF & {
    glfwSetInputMode ( this->_handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL );
    return * this;
}

auto __C_ENG_SELF :: clear () noexcept -> __C_ENG_SELF & {
    if ( this->_handle == nullptr ) {
        return * this;
    }

    glfwDestroyWindow ( this->_handle );
    this->_handle = nullptr;

    (void) activeWindows.removeFirst ( this );

    if ( activeWindows.empty() ) {
        terminateGLFW ();
    }

    return * this;
}

__C_ENG_MAYBE_UNUSED auto __C_ENG_SELF :: setTitle (
        String const & title
) noexcept -> __C_ENG_SELF & {

    this->_title = title;

    if ( this->_handle != nullptr ) {
        glfwSetWindowTitle ( this->_handle, this->_title.cStr() );
    }

    return * this;
}

__C_ENG_MAYBE_UNUSED auto __C_ENG_SELF :: setWindowType (
        __C_ENG_TYPE ( WindowType )         windowType,
        __C_ENG_TYPE ( Monitor )    const * pMonitor
) noexcept -> __C_ENG_SELF & {

    this->_type     = windowType;
    this->_monitor  = pMonitor;

    if ( this->_handle != nullptr ) {

        switch ( this->_type ) {
            case WindowTypeWindowed:            { (void) this->makeWindowed();                      break; }
            case WindowTypeFullscreen:          { (void) this->makeFullscreen(pMonitor);            break; }
            case WindowTypeWindowedFullscreen:  { (void) this->makeWindowedFullscreen(pMonitor);    break; }
        }

    }

    return * this;
}

auto __C_ENG_SELF :: resize (
        __C_ENG_TYPE ( Size ) const & size
) noexcept -> __C_ENG_SELF & {

    this->_size = size;

    (void) __C_ENG_TYPE ( Settings ) :: instance().set (
            __C_ENG_TYPE ( Settings ) :: keyResolution,
            ( static_cast < uint64 > ( this->size().width ) << 32 ) | static_cast < uint64 > ( this->size().height )
    );

    if ( this->_handle != nullptr ) {
        glfwSetWindowSize (
                this->_handle,
                static_cast < sint32 > ( this->size().width ),
                static_cast < sint32 > ( this->size().height )
        );
    }

    return * this;
}

auto __C_ENG_SELF :: move (
        __C_ENG_TYPE ( Position ) const & position
) noexcept -> __C_ENG_SELF & {

    this->_position = position;

    if ( this->handle() != nullptr ) {
        glfwSetWindowPos (
                this->handle(),
                static_cast < sint32 > ( this->position().x ),
                static_cast < sint32 > ( this->position().y )
        );
    }

    return * this;
}

auto __C_ENG_SELF :: makeWindowed () noexcept -> __C_ENG_SELF & {
    if ( this->_type == __C_ENG_TYPE ( WindowType ) :: WindowTypeWindowed ) {
        return * this;
    } else {
        this->_monitor->_windowOnMonitor = nullptr;
        this->_monitor = nullptr;
    }

    if ( this->_handle == nullptr ) {
        return * this;
    }

    auto resolution = __C_ENG_TYPE ( Settings ) :: instance().get ( __C_ENG_TYPE ( Settings ) :: keyResolution );

    this->_size = ( __C_ENG_TYPE ( Size ) ) {
        .width = static_cast < uint32 > ((resolution >> 32) & 0xFFFFFFFFU ),
        .height   = static_cast < uint32 > ( resolution & 0xFFFFFFFFU )
    };

    auto primaryMonitor = __C_ENG_TYPE ( Monitor ) :: primaryMonitor();

    auto positionX =
            primaryMonitor->properties().workArea.position.x +
            ( primaryMonitor->properties().workArea.size.width - this->size().width ) / 2U;
    auto positionY =
            primaryMonitor->properties().workArea.position.y +
            ( primaryMonitor->properties().workArea.size.height - this->size().height ) / 2U;

    if (
            positionX >
                primaryMonitor->properties().workArea.position.x +
                primaryMonitor->properties().workArea.size.width
    ) {
        positionX = primaryMonitor->properties().workArea.position.x;
    }

    if (
            positionY >
                primaryMonitor->properties().workArea.position.y +
                primaryMonitor->properties().workArea.size.height
    ) {
        positionY = primaryMonitor->properties().workArea.position.y;
    }

    glfwSetWindowMonitor (
            this->handle(),
            nullptr,
            static_cast < sint32 > ( positionX ),
            static_cast < sint32 > ( positionY ),
            static_cast < sint32 > ( this->size().width ),
            static_cast < sint32 > ( this->size().height ),
            static_cast < sint32 > ( primaryMonitor->properties().activeVideoMode.refreshRate )
    );

    return * this;
}

auto __C_ENG_SELF :: makeFullscreen (
        __C_ENG_TYPE ( Monitor ) const * pMonitor
) noexcept -> __C_ENG_SELF & {

    if ( this->_type == __C_ENG_TYPE ( WindowType ) :: WindowTypeFullscreen && this->_monitor == pMonitor ) {
        return * this;
    }

    this->_type = __C_ENG_TYPE ( WindowType ) :: WindowTypeFullscreen;

    if ( pMonitor == nullptr ) {
        pMonitor = __C_ENG_TYPE ( Monitor ) :: primaryMonitor();
    }

    this->_monitor = pMonitor;
    this->_monitor->_windowOnMonitor = this;

    if ( this->_handle == nullptr ) {
        return * this;
    }

    glfwSetWindowMonitor(
            this->handle(),
            this->monitor()->handle(),
            0,
            0,
            static_cast < sint32 > ( this->size().width ),
            static_cast < sint32 > ( this->size().height ),
            static_cast < sint32 > ( this->refreshRate() )
    );

    return * this;
}

auto __C_ENG_SELF :: makeWindowedFullscreen (
        __C_ENG_TYPE ( Monitor ) const * pMonitor
) noexcept -> __C_ENG_SELF & {

    if ( this->_type == __C_ENG_TYPE ( WindowType ) :: WindowTypeWindowedFullscreen && this->_monitor == pMonitor ) {
        return * this;
    }

    this->_type = __C_ENG_TYPE ( WindowType ) :: WindowTypeWindowedFullscreen;

    if ( pMonitor == nullptr ) {
        pMonitor = __C_ENG_TYPE ( Monitor ) :: primaryMonitor();
    }

    this->_monitor = pMonitor;
    this->_monitor->_windowOnMonitor = this;

    if ( this->_handle == nullptr ) {
        return * this;
    }

    this->_size = ( __C_ENG_TYPE ( Size ) ) {
        .width = this->monitor()->properties().activeVideoMode.size.width,
        .height = this->monitor()->properties().activeVideoMode.size.height
    };

    (void) __C_ENG_TYPE ( Settings ) :: instance().set (
            __C_ENG_TYPE ( Settings ) :: keyResolution,
            ( static_cast < uint64 > ( this->size().width ) << 32 ) | static_cast < uint64 > ( this->size().height )
    );

    glfwWindowHint ( GLFW_RED_BITS,     static_cast < sint32 > ( this->monitor()->properties().activeVideoMode.colorChannelsDepth.red ) );
    glfwWindowHint ( GLFW_GREEN_BITS,   static_cast < sint32 > ( this->monitor()->properties().activeVideoMode.colorChannelsDepth.green ) );
    glfwWindowHint ( GLFW_BLUE_BITS,    static_cast < sint32 > ( this->monitor()->properties().activeVideoMode.colorChannelsDepth.blue ) );

    glfwSetWindowMonitor (
            this->handle(),
            this->monitor()->handle(),
            0,
            0,
            static_cast < sint32 > ( this->monitor()->properties().activeVideoMode.size.width ),
            static_cast < sint32 > ( this->monitor()->properties().activeVideoMode.size.height ),
            static_cast < sint32 > ( this->monitor()->properties().activeVideoMode.refreshRate )
    );

    return * this;
}

namespace engine {

    auto __updateWindowSize (
            __C_ENG_SELF * pWindow,
            cds :: uint32 width,
            cds :: uint32 height
    ) noexcept -> void {

        pWindow->_size = ( __C_ENG_TYPE ( Size ) ) {
            .width = width,
            .height = height
        };
    }

}

static auto windowFrameBufferResizeEventRootCallback (
        __C_ENG_SELF :: Handle  handle,
        sint32                  width,
        sint32                  height
) noexcept -> void {
    auto pObject = reinterpret_cast < __C_ENG_SELF * > ( glfwGetWindowUserPointer ( handle ) );
    if ( pObject->engine() != nullptr ) {
        __C_ENG_TYPE ( WindowFrameBufferResizeEvent ) event (
                pObject,
                ( __C_ENG_TYPE ( Size ) ) {
                    .width  = static_cast < uint32 > ( width ),
                    .height = static_cast < uint32 > ( height )
                },
                pObject->size()
        );

        (void) pObject->engine()->eventHandler().windowFrameBufferResizeEvent ( & event );
    }
}

static auto windowResizeEventRootCallback (
        __C_ENG_SELF :: Handle  handle,
        sint32                  width,
        sint32                  height
) noexcept -> void {
    auto pObject = reinterpret_cast < __C_ENG_SELF * > ( glfwGetWindowUserPointer ( handle ) );
    if ( pObject->engine() != nullptr ) {
        __C_ENG_TYPE ( WindowResizeEvent ) event (
                pObject,
                ( __C_ENG_TYPE ( Size ) ) {
                    .width  = static_cast < uint32 > ( width ),
                    .height = static_cast < uint32 > ( height ),
                },
                pObject->size()
        );

        (void) pObject->engine()->eventHandler().windowResizeEvent ( & event );
    }

    __updateWindowSize (
            pObject,
            static_cast < uint32 > ( width ),
            static_cast < uint32 > ( height )
    );
}

static auto windowCloseEventRootCallback (
        __C_ENG_SELF :: Handle handle
) noexcept -> void {
    auto pObject = reinterpret_cast < __C_ENG_SELF * > ( glfwGetWindowUserPointer ( handle ) );
    if ( pObject->engine() != nullptr ) {

        __C_ENG_TYPE ( WindowCloseEvent ) event ( pObject );
        (void) pObject->engine()->eventHandler().windowCloseEvent ( & event );

        if ( event.cancelClose() ) {
            glfwSetWindowShouldClose ( handle, GLFW_FALSE );
        }

    }
}

static auto windowContentScaleEventRootCallback (
        __C_ENG_SELF :: Handle  handle,
        float                   xScale,
        float                   yScale
) noexcept -> void {
    auto pObject = reinterpret_cast < __C_ENG_SELF * > ( glfwGetWindowUserPointer ( handle ) );
    if ( pObject->engine() != nullptr ) {

        __C_ENG_TYPE ( WindowContentScaleEvent ) event (
                pObject,
                ( __C_ENG_TYPE ( WindowContentScale ) ) {
                    .x = xScale,
                    .y = yScale
                }
        );

        (void) pObject->engine()->eventHandler().windowContentScaleEvent ( & event );

    }
}

static auto windowMoveEventRootCallback (
        __C_ENG_SELF :: Handle  handle,
        sint32                  xPos,
        sint32                  yPos
) noexcept -> void {
    auto pObject = reinterpret_cast < __C_ENG_SELF * > ( glfwGetWindowUserPointer ( handle ) );
    if ( pObject->engine() != nullptr ) {

        __C_ENG_TYPE ( WindowMoveEvent ) event (
                pObject,
                ( __C_ENG_TYPE ( Position ) ) {
                    .x = static_cast < uint32 > ( xPos ),
                    .y = static_cast < uint32 > ( yPos )
                },
                pObject->position()
        );

        (void) pObject->engine()->eventHandler().windowMoveEvent ( & event );

    }
}

static auto windowMinimizeEventRootCallback (
        __C_ENG_SELF :: Handle  handle,
        sint32                  minimized
) noexcept -> void {
    auto pObject = reinterpret_cast < __C_ENG_SELF * > ( glfwGetWindowUserPointer ( handle ) );
    if ( pObject->engine() != nullptr ) {

        if ( static_cast < bool > ( minimized ) ) { // NOLINT(clion-misra-cpp2008-5-0-13)

            __C_ENG_TYPE ( WindowMinimizeEvent ) event (
                    pObject
            );

            (void) pObject->engine()->eventHandler().windowMinimizeEvent ( & event );

        } else {

            __C_ENG_TYPE ( WindowRestoreEvent ) event (
                    pObject
            );

            (void) pObject->engine()->eventHandler().windowRestoreEvent ( & event );

        }
    }
}

static auto windowMaximizeEventRootCallback (
        __C_ENG_SELF :: Handle  handle,
        sint32                  maximized
) noexcept -> void {
    auto pObject = reinterpret_cast < __C_ENG_SELF * > ( glfwGetWindowUserPointer ( handle ) );
    if ( pObject->engine() != nullptr ) {

        if ( static_cast < bool > ( maximized ) ) { // NOLINT(clion-misra-cpp2008-5-0-13)

            __C_ENG_TYPE ( WindowMaximizeEvent ) event (
                    pObject
            );

            (void) pObject->engine()->eventHandler().windowMaximizeEvent ( & event );

        } else {

            __C_ENG_TYPE ( WindowRestoreEvent ) event (
                    pObject
            );

            (void) pObject->engine()->eventHandler().windowRestoreEvent ( & event );

        }
    }
}

static auto windowFocusEventRootCallback (
        __C_ENG_SELF :: Handle  handle,
        sint32                  focusGained
) noexcept -> void {
    auto pObject = reinterpret_cast < __C_ENG_SELF * > ( glfwGetWindowUserPointer ( handle ) );
    if ( pObject->engine() != nullptr ) {

        if ( static_cast < bool > ( focusGained ) ) { // NOLINT(clion-misra-cpp2008-5-0-13)

            __C_ENG_TYPE ( WindowGainFocusEvent ) event (
                    pObject
            );

            (void) pObject->engine()->eventHandler().windowGainFocusEvent ( & event );

        } else {

            __C_ENG_TYPE ( WindowLoseFocusEvent ) event (
                    pObject
            );

            (void) pObject->engine()->eventHandler().windowLoseFocusEvent ( & event );

        }
    }
}

static auto windowRefreshRequestEventRootCallback (
        __C_ENG_SELF :: Handle handle
) noexcept -> void {
    auto pObject = reinterpret_cast < __C_ENG_SELF * > ( glfwGetWindowUserPointer ( handle ) );
    if ( pObject->engine() != nullptr ) {

        __C_ENG_TYPE ( WindowRefreshRequestEvent ) event (
                pObject
        );

        (void) pObject->engine()->eventHandler().windowRefreshRequestEvent ( & event );

    }
}

static auto keyEventRootCallback (
        __C_ENG_SELF :: Handle  handle,
        sint32                  key,
        sint32                  scanCode __C_ENG_MAYBE_UNUSED,
        sint32                  action,
        sint32                  modifiers
) noexcept -> void {
    auto pObject = reinterpret_cast < __C_ENG_SELF * > ( glfwGetWindowUserPointer ( handle ) );
    if ( pObject->engine() != nullptr ) {

        if ( action == GLFW_PRESS ) {
            __C_ENG_TYPE ( KeyPressEvent ) event (
                    pObject,
                    static_cast < __C_ENG_TYPE ( Key ) > ( key ),
                    static_cast < __C_ENG_TYPE ( KeyModifiers ) > ( modifiers )
            );

            (void) pObject->engine()->eventHandler().keyPressEvent ( & event );

        } else if ( action == GLFW_RELEASE ) {

            __C_ENG_TYPE ( KeyReleaseEvent ) event (
                    pObject,
                    static_cast < __C_ENG_TYPE ( Key ) > ( key ),
                    static_cast < __C_ENG_TYPE ( KeyModifiers ) > ( modifiers )
            );

            (void) pObject->engine()->eventHandler().keyReleaseEvent ( & event );

        } else {
            /// do nothing
        }
    }
}

namespace engine {

    auto __updateCursorPos (
            __C_ENG_SELF  * window,
            uint32          xPos,
            uint32          yPos
    ) noexcept -> void {

        window->_mousePosition = ( __C_ENG_TYPE ( Position ) ) {
            .x = xPos,
            .y = yPos
        };
    }

}

static auto mouseMoveEventRootCallback (
        __C_ENG_SELF :: Handle  handle,
        double                  xPos,
        double                  yPos
) noexcept -> void {
    auto pObject = reinterpret_cast < __C_ENG_SELF * > ( glfwGetWindowUserPointer ( handle ) );
    if ( pObject->engine() != nullptr ) {
        auto castedXPos = static_cast < uint32 > ( xPos );
        auto castedYPos = static_cast < uint32 > ( yPos );

        __C_ENG_TYPE ( MouseMoveEvent ) event (
                pObject,
                ( __C_ENG_TYPE ( Position ) ) {
                    .x  = castedXPos,
                    .y  = castedYPos,
                },
                pObject->mousePosition()
        );

        (void) pObject->engine()->eventHandler().mouseMoveEvent( & event );

        __updateCursorPos (
                pObject,
                castedXPos,
                castedYPos
        );
    }
}

static auto mouseEnterEventRootCallback (
        __C_ENG_SELF :: Handle  handle,
        sint32                  entered
) noexcept -> void {
    auto pObject = reinterpret_cast < __C_ENG_SELF * > ( glfwGetWindowUserPointer ( handle ) );
    if ( pObject->engine() != nullptr ) {
        if ( static_cast < bool > ( entered ) ) { // NOLINT(clion-misra-cpp2008-5-0-13)

            __C_ENG_TYPE ( MouseEnterEvent ) event (
                    pObject,
                    pObject->mousePosition()
            );

            (void) pObject->engine()->eventHandler().mouseEnterEvent ( & event );

        } else {

            __C_ENG_TYPE ( MouseLeaveEvent ) event (
                    pObject,
                    pObject->mousePosition()
            );

            (void) pObject->engine()->eventHandler().mouseLeaveEvent ( & event );

        }
    }
}

static auto mousePressEventRootCallback (
        __C_ENG_SELF :: Handle  handle,
        sint32                  button,
        sint32                  action,
        sint32                  modifiers
) noexcept -> void {
    auto pObject = reinterpret_cast < __C_ENG_SELF * > ( glfwGetWindowUserPointer ( handle ) );
    if ( pObject->engine() != nullptr ) {
        if ( action == GLFW_PRESS ) {

            __C_ENG_TYPE ( MousePressEvent ) event (
                    pObject,
                    pObject->mousePosition(),
                    static_cast < __C_ENG_TYPE ( MouseButton ) > ( button ),
                    static_cast < __C_ENG_TYPE ( KeyModifiers ) > ( modifiers )
            );

            (void) pObject->engine()->eventHandler().mousePressEvent ( & event );

        } else if ( action == GLFW_RELEASE ) {

            __C_ENG_TYPE ( MouseReleaseEvent ) event (
                    pObject,
                    pObject->mousePosition(),
                    static_cast < __C_ENG_TYPE ( MouseButton ) > ( button ),
                    static_cast < __C_ENG_TYPE ( KeyModifiers ) > ( modifiers )
            );

            (void) pObject->engine()->eventHandler().mouseReleaseEvent ( & event );

        } else {
            /// do nothing
        }
    }
}

static auto mouseScrollEventRootCallback (
        __C_ENG_SELF :: Handle  handle,
        double                  xOffset,
        double                  yOffset
) noexcept -> void {
    auto pObject = reinterpret_cast < __C_ENG_SELF * > ( glfwGetWindowUserPointer ( handle ) );
    if ( pObject->engine() != nullptr ) {

        __C_ENG_TYPE ( MouseScrollEvent ) event (
                pObject,
                pObject->mousePosition(),
                xOffset,
                yOffset
        );

        (void) pObject->engine()->eventHandler().mouseScrollEvent ( & event );

    }
}

auto __C_ENG_SELF :: monitorDisconnectedEvent () noexcept -> __C_ENG_SELF & {

    return * this;
}

static auto windowFlagGLFWHint ( __C_ENG_TYPE ( WindowFlag ) flag ) noexcept -> sint32 {
    sint32 GLFWHint = GLFW_DONT_CARE;

    switch ( flag ) {
        case WindowFlagNone:                    { GLFWHint = GLFW_DONT_CARE;                break; }
        case WindowFlagResizable:               { GLFWHint = GLFW_RESIZABLE;                break; }
        case WindowFlagBorderless:              { GLFWHint = GLFW_DECORATED;                break; }
        case WindowFlagStartMinimized:          { GLFWHint = GLFW_VISIBLE;                  break; }
        case WindowFlagGrabFocusOnOpen:         { GLFWHint = GLFW_FOCUSED;                  break; }
        case WindowFlagRestorePreviousMode:     { GLFWHint = GLFW_AUTO_ICONIFY;             break; }
        case WindowFlagStayOnTop:               { GLFWHint = GLFW_FLOATING;                 break; }
        case WindowFlagStartMaximized:          { GLFWHint = GLFW_MAXIMIZED;                break; }
        case WindowFlagCenterCursorOnCreate:    { GLFWHint = GLFW_CENTER_CURSOR;            break; }
        case WindowFlagTransparentFramebuffer:  { GLFWHint = GLFW_TRANSPARENT_FRAMEBUFFER;  break; }
        case WindowFlagGrabFocusOnRaise:        { GLFWHint = GLFW_FOCUS_ON_SHOW;            break; }
        case WindowFlagScaleToMonitor:          { GLFWHint = GLFW_SCALE_TO_MONITOR;         break; }
    }

    return GLFWHint;
}

static auto windowFlagGLFWValue ( __C_ENG_TYPE ( WindowFlag ) flag ) noexcept -> sint32 {
    sint32 GLFWValue = GLFW_FALSE;

    switch ( flag ) {
        case WindowFlagNone:
        case WindowFlagBorderless:              { GLFWValue = GLFW_FALSE;   break; }
        case WindowFlagResizable:
        case WindowFlagStartMinimized:
        case WindowFlagGrabFocusOnOpen:
        case WindowFlagRestorePreviousMode:
        case WindowFlagStayOnTop:
        case WindowFlagStartMaximized:
        case WindowFlagCenterCursorOnCreate:
        case WindowFlagTransparentFramebuffer:
        case WindowFlagGrabFocusOnRaise:
        case WindowFlagScaleToMonitor:          { GLFWValue = GLFW_TRUE;    break; }
    }

    return GLFWValue;
}

auto __C_ENG_SELF :: applyFlagHints () const noexcept -> void {
    for ( cds :: uint16 flag = 0x0001U; true; flag <<= 1 ) { // NOLINT(clion-misra-cpp2008-6-5-1)
        if ( ( flag & this->_flags ) != 0U ) {
            glfwWindowHint (
                    windowFlagGLFWHint (    static_cast < __C_ENG_TYPE ( WindowFlag ) > ( flag ) ),
                    windowFlagGLFWValue (   static_cast < __C_ENG_TYPE ( WindowFlag ) > ( flag ) )
            );
        }

        if ( static_cast < __C_ENG_TYPE ( WindowFlag ) > ( flag ) == WindowFlagMaxValue ) {
            break;
        }
    }
}

auto __C_ENG_SELF :: updateWindowLimits () noexcept -> void { // NOLINT(readability-make-member-function-const)
    if ( this->handle() == nullptr ) {
        return;
    }

    auto minWidth   = static_cast < sint32 > ( this->minimumSize().width );
    auto minHeight  = static_cast < sint32 > ( this->minimumSize().height );

    auto maxWidth   = static_cast < sint32 > ( this->maximumSize().width );
    auto maxHeight  = static_cast < sint32 > ( this->maximumSize().height );

    if ( this->maximumSize().width == limits :: U32_MAX ) {
        maxWidth = GLFW_DONT_CARE;
    }

    if ( this->maximumSize().height == limits :: U32_MAX ) {
        maxHeight = GLFW_DONT_CARE;
    }

    glfwSetWindowSizeLimits (
            this->handle(),
            minWidth,
            minHeight,
            maxWidth,
            maxHeight
    );
}

auto __C_ENG_SELF :: setMinimumSize (
        __C_ENG_TYPE ( Size ) const & size
) noexcept -> __C_ENG_SELF & {

    this->_minimumSize = size;
    this->updateWindowLimits();

    return * this;
}

auto __C_ENG_SELF :: setMaximumSize (
        __C_ENG_TYPE ( Size ) const & size
) noexcept -> __C_ENG_SELF & {

    this->_maximumSize = size;
    this->updateWindowLimits();

    return * this;
}

auto __C_ENG_SELF :: maximize () noexcept -> __C_ENG_SELF & {
    if ( this->handle() == nullptr ) {
        return * this;
    }

    glfwMaximizeWindow ( this->handle() );

    return * this;
}

auto __C_ENG_SELF :: minimize () noexcept -> __C_ENG_SELF & {
    if ( this->handle() == nullptr ) {
        return * this;
    }

    glfwIconifyWindow ( this->handle() );

    return * this;
}

auto __C_ENG_SELF :: hide () noexcept -> __C_ENG_SELF & {
    if ( this->handle() == nullptr ) {
        return * this;
    }

    glfwHideWindow ( this->handle() );

    return * this;
}

__C_ENG_MAYBE_UNUSED auto __C_ENG_SELF :: show () noexcept -> __C_ENG_SELF & {
    if ( this->handle() == nullptr ) {
        return * this;
    }

    glfwShowWindow ( this->handle() );

    return * this;
}

__C_ENG_MAYBE_UNUSED auto __C_ENG_SELF :: grabInputFocus () noexcept -> __C_ENG_SELF & {
    if ( this->handle() == nullptr ) {
        return * this;
    }

    glfwFocusWindow ( this->handle() );

    return * this;
}

__C_ENG_MAYBE_UNUSED auto __C_ENG_SELF :: requestAttention () noexcept -> __C_ENG_SELF & {
    if ( this->handle() == nullptr ) {
        return * this;
    }

    glfwRequestWindowAttention ( this->handle() );

    return * this;
}

auto __C_ENG_SELF :: pollEvents () noexcept -> __C_ENG_SELF & {
    glfwPollEvents();

    if ( this->engine() != nullptr ) {

        while ( ! this->_customWindowEvents.empty() ) {
            auto pEvent = this->_customWindowEvents.pop();
            (void) this->engine()->eventHandler().windowCustomEvent ( pEvent );
            delete pEvent;
        }

        while ( ! this->_customMouseEvents.empty() ) {
            auto pEvent = this->_customMouseEvents.pop();
            (void) this->engine()->eventHandler().mouseCustomEvent ( pEvent );
            delete pEvent;
        }

        while ( ! this->_customKeyEvents.empty() ) {
            auto pEvent = this->_customKeyEvents.pop();
            (void) this->engine()->eventHandler().keyCustomEvent ( pEvent );
            delete pEvent;
        }

        while ( ! this->_customEvents.empty() ) {
            auto pEvent = this->_customEvents.pop();
            (void) this->engine()->eventHandler().customEvent ( pEvent );
            delete pEvent;
        }

    } else {

        while ( ! this->_customWindowEvents.empty() ) {
            delete this->_customWindowEvents.pop();
        }

        while ( ! this->_customMouseEvents.empty() ) {
            delete this->_customMouseEvents.pop();
        }

        while ( ! this->_customKeyEvents.empty() ) {
            delete this->_customKeyEvents.pop();
        }

        while ( ! this->_customEvents.empty() ) {
            delete this->_customEvents.pop();
        }

    }

    return * this;
}

__C_ENG_MAYBE_UNUSED auto __C_ENG_SELF :: handleEvent (
        __C_ENG_TYPE ( WindowEvent ) const & event
) noexcept -> __C_ENG_SELF & {
    (void) this->_customWindowEvents.push ( event.copy() );
    return * this;
}

__C_ENG_MAYBE_UNUSED auto __C_ENG_SELF :: handleEvent (
        __C_ENG_TYPE ( MouseEvent ) const & event
) noexcept -> __C_ENG_SELF & {
    (void) this->_customMouseEvents.push ( event.copy() );
    return * this;
}

__C_ENG_MAYBE_UNUSED auto __C_ENG_SELF :: handleEvent (
        __C_ENG_TYPE ( KeyEvent ) const & event
) noexcept -> __C_ENG_SELF & {
    (void) this->_customKeyEvents.push ( event.copy() );
    return * this;
}

__C_ENG_MAYBE_UNUSED auto __C_ENG_SELF :: handleEvent (
        __C_ENG_TYPE ( Event ) const & event
) noexcept -> __C_ENG_SELF & {
    (void) this->_customEvents.push ( event.copy() );
    return * this;
}

auto __C_ENG_SELF :: toString () const noexcept -> String {
    return __C_ENG_STRINGIFY ( __C_ENG_SELF ) " "
           "{ handle = "_s              + :: toString ( this->handle() ) +
           ", title = "                 + this->_title +
           ", position = "              + :: toString ( this->position() ) +
           ", size = "                  + :: toString ( this->size() ) +
           ", mousePosition = "         + :: toString ( this->mousePosition() ) +
           ", refreshRate = "           + this->refreshRate() +
           ", engine = "                + :: toString ( this->engine() ) +
           ", monitor = "               + :: toString ( this->monitor() ) +
           ", type = "                  + :: toString ( this->type() ) +
           ", flags = "                 + :: windowFlagsToString ( this->flags() ) +
           ", minimumSize = "           + :: toString ( this->minimumSize() ) +
           ", maximumSize = "           + :: toString ( this->maximumSize() ) +
           ", customEvents = "          + this->_customEvents.toString () +
           ", customWindowEvents = "    + this->_customWindowEvents.toString () +
           ", customMouseEvents = "     + this->_customMouseEvents.toString () +
           ", customKeyEvents = "       + this->_customKeyEvents.toString () +
           " }";
}

auto __C_ENG_SELF :: equals (
        Object const & object
) const noexcept -> bool {

    if ( this == & object ) {
        return true;
    }

    auto pWindow = dynamic_cast < decltype ( this ) > ( & object );
    if ( pWindow == nullptr ) {
        return false;
    }

    return this->handle() == pWindow->handle();
}
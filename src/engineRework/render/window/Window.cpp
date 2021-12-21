//
// Created by loghin on 19.12.2021.
//

#include "Window.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

#include <Logger.hpp>
#include <CDS/Array>

bool __GLFWActive = false; // NOLINT(bugprone-reserved-identifier)
static Array < C_ENG_CLASS ( Window ) const * > activeWindows;

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
    (void) C_ENG_CLASS ( Logger ) :: instance().error (
            "GLFW Error : "_s + GLFWErrorCodeName ( errorCode ) + " -> " + errorMessage
    );
}

auto __initializeGLFW () noexcept (false) -> void { // NOLINT(bugprone-reserved-identifier)
    if ( __GLFWActive ) {
        return;
    }

    (void) C_ENG_CLASS ( Logger ) :: instance ().info ("Initializing GLFW");

    if ( glfwInit () == GLFW_FALSE ) {
        (void) C_ENG_CLASS ( Logger ) :: instance ().fatal ("GLFW Could not be initialized");
        throw RuntimeException ( "GLFW Initialization Failure" );
    }

    (void) glfwSetErrorCallback ( & GLFWErrorCallback );

    (void) C_ENG_CLASS ( Logger ) :: instance ().info ("GLFW Initialized");
    (void) C_ENG_CLASS ( Logger ) :: instance ().info (
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

    (void) C_ENG_CLASS ( Logger ) :: instance ().info (
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

static auto resizeEventRootCallback (
        C_ENG_CLASS ( Window ) :: WindowHandle,
        sint32,
        sint32
) noexcept -> void;

static auto keyEventRootCallback (
        C_ENG_CLASS ( Window ) :: WindowHandle,
        sint32,
        sint32,
        sint32,
        sint32
) noexcept -> void;

static auto mouseMoveEventRootCallback (
        C_ENG_CLASS ( Window ) :: WindowHandle,
        double,
        double
) noexcept -> void;

static auto mouseEnterEventRootCallback (
        C_ENG_CLASS ( Window ) :: WindowHandle,
        sint32
) noexcept -> void;

static auto mousePressEventRootCallback (
        C_ENG_CLASS ( Window ) :: WindowHandle,
        sint32,
        sint32,
        sint32
) noexcept -> void;

static auto mouseScrollEventRootCallback (
        C_ENG_CLASS ( Window ) :: WindowHandle,
        double,
        double
) noexcept -> void;

#include <Settings.hpp>
#include <Monitor.hpp>

auto C_ENG_CLASS ( Window ) :: init () noexcept (false) -> C_ENG_TYPE ( Window ) & {
    __initializeGLFW();

    (void) C_ENG_CLASS ( Logger ) :: instance().info("Initializing Window");

    if ( this->_handle != nullptr ) {
        (void) C_ENG_CLASS ( Logger ) :: instance().debug("Window Already Initialized, returning");
        return * this;
    }

    auto resolution = C_ENG_CLASS ( Settings ) :: instance().get( C_ENG_CLASS ( Settings ) :: keyResolution );

    this->_width = static_cast < uint32 > ( ( resolution >> 32 ) & 0xFFFFFFFFU );
    this->_height = static_cast < uint32 > ( resolution & 0xFFFFFFFFU );

    glfwWindowHint ( GLFW_CLIENT_API, GLFW_NO_API );

    C_ENG_CLASS ( Monitor ) :: Handle pMonitorHandle = nullptr;

    if ( this->_type != WindowType :: WindowTypeWindowed ) {
        pMonitorHandle = this->_monitor->handle();

        if ( this->_type == WindowType :: WindowTypeWindowedFullscreen ) {

            glfwWindowHint ( GLFW_RED_BITS,     static_cast < sint32 > ( this->_monitor->properties().activeVideoMode.colorChannelsDepth.red ) );
            glfwWindowHint ( GLFW_GREEN_BITS,   static_cast < sint32 > ( this->_monitor->properties().activeVideoMode.colorChannelsDepth.green ) );
            glfwWindowHint ( GLFW_BLUE_BITS,    static_cast < sint32 > ( this->_monitor->properties().activeVideoMode.colorChannelsDepth.blue ) );
            glfwWindowHint ( GLFW_REFRESH_RATE, static_cast < sint32 > ( this->_monitor->properties().activeVideoMode.refreshRate ) );

            this->_width    = static_cast < uint32 > ( this->_monitor->properties().activeVideoMode.size.width );
            this->_height   = static_cast < uint32 > ( this->_monitor->properties().activeVideoMode.size.height );

            (void) C_ENG_CLASS ( Settings ) :: instance().set (
                    C_ENG_CLASS ( Settings ) :: keyResolution,
                    ( static_cast < uint64 > ( this->_width ) << 32 ) | static_cast < uint64 > ( this->_height )
            );

        }

        this->_monitor->_windowOnMonitor = this;
    }

    this->_handle = glfwCreateWindow (
            static_cast < sint32 > ( this->width() ),
            static_cast < sint32 > ( this->height() ),
            this->_title.cStr(),
            nullptr,
            nullptr
    );

    glfwSetWindowUserPointer ( this->_handle, reinterpret_cast < void * > ( this ) );
    glfwDefaultWindowHints();

    (void) glfwSetFramebufferSizeCallback   ( this->_handle, & resizeEventRootCallback );
    (void) glfwSetKeyCallback               ( this->_handle, & keyEventRootCallback );
    (void) glfwSetCursorPosCallback         ( this->_handle, & mouseMoveEventRootCallback );
    (void) glfwSetCursorEnterCallback       ( this->_handle, & mouseEnterEventRootCallback );
    (void) glfwSetMouseButtonCallback       ( this->_handle, & mousePressEventRootCallback );
    (void) glfwSetScrollCallback            ( this->_handle, & mouseScrollEventRootCallback );

    glfwSetInputMode ( this->_handle, GLFW_LOCK_KEY_MODS, GLFW_TRUE );

    if ( static_cast < bool > ( C_ENG_CLASS ( Settings ) :: instance().get( C_ENG_CLASS ( Settings ) :: keyMouseCursorEnabled ) ) ) { // NOLINT(clion-misra-cpp2008-5-0-13)
        (void) this->releaseMouseCursor();
    } else {
        (void) this->grabMouseCursor();
    }

    sint32 xPos;
    sint32 yPos;
    glfwGetWindowPos ( this->handle(), & xPos, & yPos );

    this->_x = static_cast < uint32 > ( xPos );
    this->_y = static_cast < uint32 > ( yPos );

    activeWindows.add (this);
    return * this;
}

auto C_ENG_CLASS ( Window ) :: setEngine ( C_ENG_TYPE ( Engine ) * engine ) noexcept -> C_ENG_TYPE ( Window ) & {
    this->_engine = engine;
    return * this;
}

auto C_ENG_CLASS ( Window ) :: grabMouseCursor () noexcept -> C_ENG_TYPE ( Window ) & {
    glfwSetInputMode ( this->_handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
    if ( glfwRawMouseMotionSupported() ) { // NOLINT(clion-misra-cpp2008-5-0-13)
        glfwSetInputMode ( this->_handle, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE );
    }

    return * this;
}

auto C_ENG_CLASS ( Window ) :: releaseMouseCursor () noexcept -> C_ENG_TYPE ( Window ) & {
    glfwSetInputMode ( this->_handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL );
    return * this;
}

auto C_ENG_CLASS ( Window ) :: clear () noexcept -> C_ENG_TYPE ( Window ) & {
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

auto C_ENG_CLASS ( Window ) :: setTitle (
        String const & title
) noexcept -> C_ENG_TYPE ( Window ) & {

    this->_title = title;

    if ( this->_handle != nullptr ) {
        glfwSetWindowTitle ( this->_handle, this->_title.cStr() );
    }

    return * this;
}

auto C_ENG_CLASS ( Window ) :: setWindowType (
        WindowType                      windowType,
        C_ENG_TYPE ( Monitor )  const * pMonitor
) noexcept -> C_ENG_TYPE ( Window ) & {

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

auto C_ENG_CLASS ( Window ) :: resize (
        RectangleSize const & size
) noexcept -> C_ENG_TYPE ( Window ) & {

    this->_width = size.width;
    this->_height = size.height;

    (void) C_ENG_CLASS ( Settings ) :: instance().set (
            C_ENG_CLASS ( Settings ) :: keyResolution,
            ( static_cast < uint64 > ( this->_width ) << 32 ) | static_cast < uint64 > ( this->_height )
    );

    if ( this->_handle != nullptr ) {
        glfwSetWindowSize (
                this->_handle,
                static_cast < sint32 > ( this->_width ),
                static_cast < sint32 > ( this->_height )
        );
    }

    return * this;
}

auto C_ENG_CLASS ( Window ) :: move (
        Position const & position
) noexcept -> C_ENG_TYPE ( Window ) & {

    this->_x = position.x;
    this->_y = position.y;

    glfwSetWindowPos (
            this->handle(),
            static_cast < sint32 > ( this->_x ),
            static_cast < sint32 > ( this->_y )
    );

    return * this;
}

auto C_ENG_CLASS ( Window ) :: makeWindowed () noexcept -> C_ENG_TYPE ( Window ) & {
    if ( this->_type == WindowType :: WindowTypeWindowed ) {
        return * this;
    } else {
        this->_monitor->_windowOnMonitor = nullptr;
        this->_monitor = nullptr;
    }

    if ( this->_handle == nullptr ) {
        return * this;
    }

    auto resolution = C_ENG_CLASS ( Settings ) :: instance().get ( C_ENG_CLASS ( Settings ) :: keyResolution );

    this->_width    = static_cast < uint32 > ( ( resolution >> 32 ) & 0xFFFFFFFFU );
    this->_height   = static_cast < uint32 > ( resolution & 0xFFFFFFFFU );

    auto primaryMonitor = C_ENG_CLASS ( Monitor ) :: primaryMonitor();

    auto positionX =
            primaryMonitor->properties().workArea.position.x +
            ( primaryMonitor->properties().workArea.size.width - this->_width ) / 2U;
    auto positionY =
            primaryMonitor->properties().workArea.position.y +
            ( primaryMonitor->properties().workArea.size.height - this->_height ) / 2U;

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
            static_cast < sint32 > ( this->_width ),
            static_cast < sint32 > ( this->_height ),
            static_cast < sint32 > ( primaryMonitor->properties().activeVideoMode.refreshRate )
    );

    return * this;
}

auto C_ENG_CLASS ( Window ) :: makeFullscreen (
        C_ENG_TYPE ( Monitor ) const * pMonitor
) noexcept -> C_ENG_TYPE ( Window ) & {

    if ( this->_type == WindowType :: WindowTypeFullscreen && this->_monitor == pMonitor ) {
        return * this;
    }

    this->_type = WindowType :: WindowTypeFullscreen;

    if ( pMonitor == nullptr ) {
        pMonitor = C_ENG_CLASS ( Monitor ) :: primaryMonitor();
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
            static_cast < sint32 > ( this->width() ),
            static_cast < sint32 > ( this->height() ),
            static_cast < sint32 > ( this->refreshRate() )
    );

    return * this;
}

auto C_ENG_CLASS ( Window ) :: makeWindowedFullscreen (
        C_ENG_TYPE ( Monitor ) const * pMonitor
) noexcept -> C_ENG_TYPE ( Window ) & {

    if ( this->_type == WindowType :: WindowTypeWindowedFullscreen && this->_monitor == pMonitor ) {
        return * this;
    }

    this->_type = WindowType :: WindowTypeWindowedFullscreen;

    if ( pMonitor == nullptr ) {
        pMonitor = C_ENG_CLASS ( Monitor ) :: primaryMonitor();
    }

    this->_monitor = pMonitor;
    this->_monitor->_windowOnMonitor = this;

    if ( this->_handle == nullptr ) {
        return * this;
    }

    this->_width = this->monitor()->properties().activeVideoMode.size.width;
    this->_height = this->monitor()->properties().activeVideoMode.size.height;

    (void) C_ENG_CLASS ( Settings ) :: instance().set (
            C_ENG_CLASS ( Settings ) :: keyResolution,
            ( static_cast < uint64 > ( this->_width ) << 32 ) | static_cast < uint64 > ( this->_height )
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

#include <Engine.hpp>

#include <src/engineRework/engine/event/window/ResizeEvent.hpp>

namespace engine {

    auto __updateWindowSize (
            C_ENG_TYPE ( Window ) * pWindow,
            cds :: uint32 width,
            cds :: uint32 height
    ) noexcept -> void {

        pWindow->_width = width;
        pWindow->_height = height;
    }

}

auto resizeEventRootCallback (
        C_ENG_CLASS ( Window ) :: WindowHandle  handle,
        sint32                                  width,
        sint32                                  height
) noexcept -> void {
    auto pObject = reinterpret_cast < C_ENG_CLASS ( Window ) * > ( glfwGetWindowUserPointer ( handle ) );
    if ( pObject->engine() != nullptr ) {
        C_ENG_TYPE ( ResizeEvent ) event (
                pObject->width(),
                pObject->height(),
                static_cast < uint32 > ( width ),
                static_cast < uint32 > ( height ),
                pObject
        );

        (void) pObject->engine()->resizeEvent ( & event );
    }

    __updateWindowSize (
            pObject,
            static_cast < uint32 > ( width ),
            static_cast < uint32 > ( height )
    );
}

#include <KeyPressEvent.hpp>
#include <KeyReleaseEvent.hpp>

auto keyEventRootCallback (
        C_ENG_CLASS ( Window ) :: WindowHandle  handle,
        sint32                                  key,
        sint32                                  scanCode C_ENG_MAYBE_UNUSED,
        sint32                                  action,
        sint32                                  modifiers
) noexcept -> void {
    auto pObject = reinterpret_cast < C_ENG_TYPE ( Window ) * > ( glfwGetWindowUserPointer ( handle ) );
    if ( pObject != nullptr ) {

        if ( action == GLFW_PRESS ) {
            C_ENG_TYPE ( KeyPressEvent ) event (
                    static_cast < Key > ( key ),
                    static_cast < KeyModifiers > ( modifiers ),
                    pObject
            );

            (void) pObject->engine()->keyPressEvent ( & event );

        } else if ( action == GLFW_RELEASE ) {

            C_ENG_TYPE ( KeyReleaseEvent ) event (
                    static_cast < Key > ( key ),
                    static_cast < KeyModifiers > ( modifiers ),
                    pObject
            );

            (void) pObject->engine()->keyReleaseEvent ( & event );

        } else {
            /// do nothing
        }
    }
}

namespace engine {

    auto __updateCursorPos (
            C_ENG_TYPE ( Window ) * window,
            uint32                  xPos,
            uint32                  yPos
    ) noexcept -> void {
        window->_mouseX = xPos;
        window->_mouseY = yPos;
    }

}

#include <MouseMoveEvent.hpp>

auto mouseMoveEventRootCallback (
        C_ENG_CLASS ( Window ) :: WindowHandle  handle,
        double                                  xPos,
        double                                  yPos
) noexcept -> void {
    auto pObject = reinterpret_cast < C_ENG_TYPE ( Window ) * > ( glfwGetWindowUserPointer ( handle ) );
    if ( pObject->engine() != nullptr ) {
        auto castedXPos = static_cast < uint32 > ( xPos );
        auto castedYPos = static_cast < uint32 > ( yPos );

        C_ENG_TYPE ( MouseMoveEvent ) event (
                castedXPos,
                castedYPos,
                pObject->mouseX(),
                pObject->mouseY(),
                pObject
        );

        (void) pObject->engine()->mouseMoveEvent( & event );

        __updateCursorPos (
                pObject,
                castedXPos,
                castedYPos
        );
    }
}

#include <MouseEnterEvent.hpp>
#include <MouseLeaveEvent.hpp>

auto mouseEnterEventRootCallback (
        C_ENG_CLASS ( Window ) :: WindowHandle  handle,
        sint32                                  entered
) noexcept -> void {
    auto pObject = reinterpret_cast < C_ENG_CLASS ( Window ) * > ( glfwGetWindowUserPointer ( handle ) );
    if ( pObject->engine() != nullptr ) {
        if ( static_cast < bool > ( entered ) ) { // NOLINT(clion-misra-cpp2008-5-0-13)

            C_ENG_TYPE ( MouseEnterEvent ) event (
                    pObject->mouseX(),
                    pObject->mouseY(),
                    pObject
            );

            (void) pObject->engine()->mouseEnterEvent ( & event );

        } else {

            C_ENG_TYPE ( MouseLeaveEvent ) event (
                    pObject->mouseX(),
                    pObject->mouseY(),
                    pObject
            );

            (void) pObject->engine()->mouseLeaveEvent ( & event );

        }
    }
}

#include <MousePressEvent.hpp>
#include <MouseReleaseEvent.hpp>

auto mousePressEventRootCallback (
        C_ENG_CLASS ( Window ) :: WindowHandle  handle,
        sint32                                  button,
        sint32                                  action,
        sint32                                  modifiers
) noexcept -> void {
    auto pObject = reinterpret_cast < C_ENG_CLASS ( Window ) * > ( glfwGetWindowUserPointer ( handle ) );
    if ( pObject->engine() != nullptr ) {
        if ( action == GLFW_PRESS ) {

            C_ENG_TYPE ( MousePressEvent ) event (
                    pObject->mouseX(),
                    pObject->mouseY(),
                    static_cast < MouseButton > ( button ),
                    static_cast < KeyModifiers > ( modifiers ),
                    pObject
            );

            (void) pObject->engine()->mousePressEvent ( & event );

        } else if ( action == GLFW_RELEASE ) {

            C_ENG_TYPE ( MouseReleaseEvent ) event (
                    pObject->mouseX(),
                    pObject->mouseY(),
                    static_cast < MouseButton > ( button ),
                    static_cast < KeyModifiers > ( modifiers ),
                    pObject
            );

            (void) pObject->engine()->mouseReleaseEvent ( & event );

        } else {
            /// do nothing
        }
    }
}

#include <MouseScrollEvent.hpp>

auto mouseScrollEventRootCallback (
        C_ENG_CLASS ( Window ) :: WindowHandle  handle,
        double                                  xOffset C_ENG_MAYBE_UNUSED,
        double                                  yOffset
) noexcept -> void {
    auto pObject = reinterpret_cast < C_ENG_CLASS ( Window ) * > ( glfwGetWindowUserPointer ( handle ) );
    if ( pObject->engine() != nullptr ) {

        C_ENG_TYPE ( MouseScrollEvent ) event (
                pObject->mouseX(),
                pObject->mouseY(),
                yOffset,
                pObject
        );

        (void) pObject->engine()->mouseScrollEvent ( & event );

    }
}

auto C_ENG_CLASS ( Window ) :: monitorDisconnectedEvent () noexcept -> C_ENG_TYPE ( Window ) & {

    return * this;
}
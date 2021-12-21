//
// Created by loghin on 18.12.2021.
//

#include "Engine.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

#include <Logger.hpp>
#include <CDS/Long>

C_ENG_CLASS ( Engine ) :: C_ENG_CONSTRUCTOR ( Engine ) () noexcept = default;

auto C_ENG_CLASS ( Engine ) :: instance () noexcept -> C_ENG_TYPE ( Engine ) & {
    static C_ENG_TYPE ( Engine ) instance;
    return instance;
}

auto C_ENG_CLASS ( Engine ) :: start () noexcept -> C_ENG_TYPE ( Engine ) & {
    (void) C_ENG_CLASS ( Logger ) :: instance().debug(
            "Engine Created at 0x" +
            Long ( reinterpret_cast < AddressValueType const > ( this ) ).toString(16) + " and booting up"
    );

    return this->startup().run().shutdown();
}

auto C_ENG_CLASS ( Engine ) :: startup () noexcept -> C_ENG_TYPE ( Engine ) & {
    this->setState ( EngineState :: EngineStateStartup );

    return this->initializeSettings();
}

auto C_ENG_CLASS ( Engine ) :: initializeSettings () noexcept -> C_ENG_TYPE ( Engine ) & {
    this->setState ( EngineState :: EngineStateStartupAcquiringSettings );

    return * this;
}

auto C_ENG_CLASS ( Engine ) :: run () noexcept -> C_ENG_TYPE ( Engine ) & {
    this->setState ( EngineState :: EngineStateRunning );

    while ( ! this->shutdownRequested() ) {

        if ( this->window() != nullptr ) {
            glfwPollEvents();
        }

    }

    return * this;
}

#include <Window.hpp>
auto C_ENG_CLASS ( Engine ) :: shutdownRequested() noexcept -> bool {
    if ( this->window() != nullptr && this->window()->shouldClose() ) {
        return true;
    }

    return false;
}

auto C_ENG_CLASS ( Engine ) :: shutdown () noexcept -> C_ENG_TYPE ( Engine ) & {
    this->setState ( EngineState :: EngineStateShutdown );

    return * this;
}

auto C_ENG_CLASS ( Engine ) :: setWindow ( C_ENG_TYPE ( Window ) * window ) noexcept -> C_ENG_TYPE ( Engine ) & {
    if ( this->_window != nullptr ) {
        (void) this->_window->setEngine ( nullptr );
        /// if setting different window, maybe res change, or fullscreen / windowed ...
    }

    this->_window = window;
    (void) this->_window->setEngine ( this );

    (void) C_ENG_CLASS ( Logger ) :: instance().info (
            "Window " +
            Long ( reinterpret_cast < AddressValueType const > ( window ) ).toString(16) +
            " bound to engine"
    );

    return * this;
}

auto C_ENG_CLASS ( Engine ) :: resizeEvent (
        C_ENG_TYPE ( ResizeEvent ) * pEvent
) noexcept -> C_ENG_TYPE ( Engine ) & {
    std :: cout << "re\n";

    return * this;
}

auto C_ENG_CLASS ( Engine ) :: keyPressEvent (
        C_ENG_TYPE ( KeyPressEvent ) * pEvent
) noexcept -> C_ENG_TYPE ( Engine ) & {
    std :: cout << "kpe\n";

    return * this;
}

auto C_ENG_CLASS ( Engine ) :: keyReleaseEvent (
        C_ENG_TYPE ( KeyReleaseEvent ) * pEvent
) noexcept -> C_ENG_TYPE ( Engine ) & {
    std :: cout << "kre\n";

    return * this;
}

auto C_ENG_CLASS ( Engine ) :: mouseMoveEvent (
        C_ENG_TYPE ( MouseMoveEvent ) * pEvent
) noexcept -> C_ENG_TYPE ( Engine ) & {
    std :: cout << "mme\n";

    return * this;
}

auto C_ENG_CLASS ( Engine ) :: mousePressEvent (
        C_ENG_TYPE ( MousePressEvent ) * pEvent
) noexcept -> C_ENG_TYPE ( Engine ) & {
    std :: cout << "mpe\n";

    return * this;
}

auto C_ENG_CLASS ( Engine ) :: mouseReleaseEvent (
        C_ENG_TYPE ( MouseReleaseEvent ) * pEvent
) noexcept -> C_ENG_TYPE ( Engine ) & {
    std :: cout << "mre\n";

    return * this;
}

auto C_ENG_CLASS ( Engine ) :: mouseEnterEvent (
        C_ENG_TYPE ( MouseEnterEvent ) * pEvent
) noexcept -> C_ENG_TYPE ( Engine ) & {
    std :: cout << "mee\n";

    return * this;
}

auto C_ENG_CLASS ( Engine ) :: mouseLeaveEvent (
        C_ENG_TYPE ( MouseLeaveEvent ) * pEvent
) noexcept -> C_ENG_TYPE ( Engine ) & {
    std :: cout << "mle\n";

    return * this;
}

auto C_ENG_CLASS ( Engine ) :: mouseScrollEvent (
        C_ENG_TYPE ( MouseScrollEvent ) * pEvent
) noexcept -> C_ENG_TYPE ( Engine ) & {
    std :: cout << "mse\n";

    return * this;
}
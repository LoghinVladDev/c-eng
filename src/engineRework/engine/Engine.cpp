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
            :: toString ( this ) + " and booting up" // NOLINT(clion-misra-cpp2008-5-2-9)
    );

    return this->startup().run().shutdown();
}

#include <Controller.hpp>
#include <Monitor.hpp>
auto C_ENG_CLASS ( Engine ) :: startup () noexcept -> C_ENG_TYPE ( Engine ) & {
    this->setState ( EngineState :: EngineStateStartup );

    C_ENG_TYPE ( Controller ) :: setEngine ( this );
    C_ENG_TYPE ( Monitor ) :: initMonitorHandler ();

    return this->initializeSettings();
}

auto C_ENG_CLASS ( Engine ) :: initializeSettings () noexcept -> C_ENG_TYPE ( Engine ) & {
    this->setState ( EngineState :: EngineStateStartupAcquiringSettings );

    return * this;
}

#include <Window.hpp>

auto C_ENG_CLASS ( Engine ) :: run () noexcept -> C_ENG_TYPE ( Engine ) & {
    this->setState ( EngineState :: EngineStateRunning );

    double startTime = glfwGetTime();
    double lastFPSUpdateTime = 0.0;

    while ( ! this->shutdownRequested() ) {

        if ( this->window() != nullptr ) {
            double frameStartTime = glfwGetTime();

            C_ENG_CLASS ( Controller ) :: updateEvents();
            (void) this->window()->pollEvents();
            C_ENG_CLASS ( Controller ) :: pollEvents();

            double frameEndTime = glfwGetTime();

            this->_frameDeltaTime = frameEndTime - frameStartTime;

            if ( (this->frameCount() + 1ULL) % this->_fpsUpdateFrameTime == 0ULL ) {
                this->_fps = 1000.0 / ( ( frameEndTime - lastFPSUpdateTime ) / static_cast < double > (this->_fpsUpdateFrameTime) );
                lastFPSUpdateTime = frameEndTime;
            }

            if ( this->logFPSToConsole() && ( this->frameCount() + 1ULL) % this->_showFpsEveryTick == 0ULL ) {
                std :: cout << "FPS : " << this->_fps << '\n';
            }

            this->_frameCount ++;
        }

    }

    return * this;
}

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

auto C_ENG_CLASS ( Engine ) :: setWindow (
        C_ENG_TYPE ( Window ) * window
) noexcept -> C_ENG_TYPE ( Engine ) & {

    if ( this->_window != nullptr ) {
        (void) this->_window->setEngine ( nullptr );
        /// if setting different window, maybe res change, or fullscreen / windowed ...
    }

    this->_window = window;
    (void) this->_window->setEngine ( this );

    (void) C_ENG_CLASS ( Logger ) :: instance().info (
            "Window " +
            :: toString ( this->window() ) +
            " bound to engine"
    );

    return * this;
}

auto C_ENG_CLASS ( Engine ) :: toString () const noexcept -> String {
    return "Engine "
           "{ state = "_s           + :: toString ( this->state() ) +
           ", lastFrameDelta = "    + this->frameDeltaTime() +
           ", frameCount = "        + this->frameCount() +
           ", fpsUpdateEvery = "    + this->fpsUpdateFrameTime() + " ticks" +
           ", showFpsEvery = "      + this->showFpsEveryTick() + " ticks" +
           ", logFpsToConsole = "   + :: toString ( this->logFPSToConsole() ) +
           ", fps = "               + this->fps() +
           ", attachedWindow = "    + :: toString ( this->window() ) +
           " }";
}
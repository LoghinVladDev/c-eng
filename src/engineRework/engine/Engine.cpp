//
// Created by loghin on 18.12.2021.
//

#include "Engine.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

#include <Logger.hpp>
#include <CDS/Long>

__C_ENG_TYPE ( Engine ) :: __C_ENG_CONSTRUCTOR ( Engine ) () noexcept = default;

auto __C_ENG_TYPE ( Engine ) :: instance () noexcept -> __C_ENG_TYPE ( Engine ) & {
    static __C_ENG_TYPE ( Engine ) instance;
    return instance;
}

auto __C_ENG_TYPE ( Engine ) :: start () noexcept -> __C_ENG_TYPE ( Engine ) & {
    (void) __C_ENG_TYPE ( Logger ) :: instance().debug(
            "Engine Created at 0x" +
            :: toString ( this ) + " and booting up" // NOLINT(clion-misra-cpp2008-5-2-9)
    );

    return this->startup().run().shutdown();
}

#include <Controller.hpp>
#include <Monitor.hpp>
auto __C_ENG_TYPE ( Engine ) :: startup () noexcept -> __C_ENG_TYPE ( Engine ) & {
    this->setState ( __C_ENG_TYPE ( EngineState ) :: EngineStateStartup );

    __C_ENG_TYPE ( Controller ) :: setEngine ( this );
    __C_ENG_TYPE ( Monitor ) :: initMonitorHandler ();

    return this->initializeSettings();
}

auto __C_ENG_TYPE ( Engine ) :: initializeSettings () noexcept -> __C_ENG_TYPE ( Engine ) & {
    this->setState ( __C_ENG_TYPE ( EngineState ) :: EngineStateStartupAcquiringSettings );

    return * this;
}

#include <Window.hpp>

auto __C_ENG_TYPE ( Engine ) :: run () noexcept -> __C_ENG_TYPE ( Engine ) & {
    this->setState ( __C_ENG_TYPE ( EngineState ) :: EngineStateRunning );

    double startTime = glfwGetTime();
    double lastFPSUpdateTime = 0.0;

    while ( ! this->shutdownRequested() ) {

        if ( this->window() != nullptr ) {
            double frameStartTime = glfwGetTime();

            __C_ENG_TYPE ( Controller ) :: updateEvents();
            (void) this->window()->pollEvents();
            __C_ENG_TYPE ( Controller ) :: pollEvents();

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

auto __C_ENG_TYPE ( Engine ) :: shutdownRequested() noexcept -> bool {
    if ( this->window() != nullptr && this->window()->shouldClose() ) {
        return true;
    }

    return false;
}

auto __C_ENG_TYPE ( Engine ) :: shutdown () noexcept -> __C_ENG_TYPE ( Engine ) & {
    this->setState ( __C_ENG_TYPE ( EngineState ) :: EngineStateShutdown );

    return * this;
}

auto __C_ENG_TYPE ( Engine ) :: setWindow (
        __C_ENG_TYPE ( Window ) * window
) noexcept -> __C_ENG_TYPE ( Engine ) & {

    if ( this->_window != nullptr ) {
        (void) this->_window->setEngine ( nullptr );
        /// if setting different window, maybe res change, or fullscreen / windowed ...
    }

    this->_window = window;
    (void) this->_window->setEngine ( this );

    (void) __C_ENG_TYPE ( Logger ) :: instance().info (
            "Window " +
            :: toString ( this->window() ) +
            " bound to engine"
    );

    return * this;
}

auto __C_ENG_TYPE ( Engine ) :: toString () const noexcept -> String {
    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( Engine ) ) " "
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
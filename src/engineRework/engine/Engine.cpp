//
// Created by loghin on 18.12.2021.
//

#include "Engine.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

#include <Logger.hpp>
#include <CDS/Long>
#include <Controller.hpp>
#include <Monitor.hpp>
#include <Window.hpp>


#undef __C_ENG_OBJECT_NAME
#define __C_ENG_OBJECT_NAME Engine /* NOLINT(bugprone-reserved-identifier) */


__C_ENG_SELF :: __C_ENG_CONSTRUCTOR () noexcept = default;

auto __C_ENG_SELF :: instance () noexcept -> __C_ENG_SELF & {
    static __C_ENG_TYPE ( Engine ) instance;
    return instance;
}

auto __C_ENG_SELF :: start () noexcept -> __C_ENG_SELF & {
    (void) __C_ENG_TYPE ( Logger ) :: instance().debug(
            "Engine Created at 0x" +
            :: toString ( this ) + " and booting up" // NOLINT(clion-misra-cpp2008-5-2-9)
    );

    return this->startup().run().shutdown();
}
auto __C_ENG_SELF :: startup () noexcept -> __C_ENG_SELF & {
    this->setState ( __C_ENG_TYPE ( EngineState ) :: EngineStateStartup );

    __C_ENG_TYPE ( Controller ) :: setEngine ( this );
    __C_ENG_TYPE ( Monitor ) :: initMonitorHandler ();

    return this->initializeSettings();
}

auto __C_ENG_SELF :: initializeSettings () noexcept -> __C_ENG_SELF & {
    this->setState ( __C_ENG_TYPE ( EngineState ) :: EngineStateStartupAcquiringSettings );

    return * this;
}

auto __C_ENG_SELF :: run () noexcept -> __C_ENG_SELF & {
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

auto __C_ENG_SELF :: shutdownRequested() noexcept -> bool {
    if ( this->window() != nullptr && this->window()->shouldClose() ) {
        return true;
    }

    return false;
}

auto __C_ENG_SELF :: shutdown () noexcept -> __C_ENG_SELF & {
    this->setState ( __C_ENG_TYPE ( EngineState ) :: EngineStateShutdown );

    return * this;
}

auto __C_ENG_SELF :: setWindow (
        __C_ENG_TYPE ( Window ) * window
) noexcept -> __C_ENG_SELF & {

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

auto __C_ENG_SELF :: toString () const noexcept -> String {
    return __C_ENG_STRINGIFY ( __C_ENG_SELF ) " "
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
//
// Created by loghin on 18.12.2021.
//

#include "Engine.hpp"
#include <VulkanAPI.hpp>

#include <Logger.hpp>
#include <CDS/Long>
#include <Controller.hpp>
#include <Monitor.hpp>
#include <Window.hpp>
#include <RenderEngine.hpp>
#include <VulkanRenderEngine.hpp>

#include <VulkanCore.hpp>
#include <Allocator.hpp>

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

static auto renderSurfaceAttachCallback (
        __C_ENG_TYPE ( RenderInstanceSurfaceAttachData ) const * pCallbackData
) noexcept -> bool {
    auto pEngine = reinterpret_cast < __C_ENG_TYPE ( Engine ) * > ( pCallbackData->pUserData );

    if ( pCallbackData->renderAPIType == engine :: RenderAPITypeVulkan ) {

        auto instanceHandle = reinterpret_cast < vulkan :: __C_ENG_TYPE ( InstanceHandle ) > ( pCallbackData->pAPIData );
        auto surfaceHandle = reinterpret_cast < vulkan :: __C_ENG_TYPE ( SurfaceHandle ) * > ( pCallbackData->pSurfaceHandle );

        auto pCallbacks = vulkan :: __C_ENG_TYPE ( Allocator ) :: instance().callbacks();

        return vulkan :: ResultSuccess == vulkan :: createSurface (
                instanceHandle,
                pEngine->window()->handle(),
                pCallbacks,
                surfaceHandle
        );
    }

    return true;
}

static auto renderSurfaceDetachCallback (
        __C_ENG_TYPE ( RenderInstanceSurfaceDetachData ) const * pCallbackData
) noexcept -> bool {
    auto pEngine = reinterpret_cast < __C_ENG_TYPE ( Engine ) * > ( pCallbackData->pUserData );

    if ( pCallbackData->renderAPIType == engine :: RenderAPITypeVulkan ) {
        auto instanceHandle = reinterpret_cast < vulkan :: __C_ENG_TYPE ( InstanceHandle ) > ( pCallbackData->pAPIData );
        auto surfaceHandle = reinterpret_cast < vulkan :: __C_ENG_TYPE ( SurfaceHandle ) > ( pCallbackData->pSurfaceHandle );

        auto pCallbacks = vulkan :: __C_ENG_TYPE ( Allocator ) :: instance().callbacks();

        return vulkan :: ResultSuccess == vulkan :: destroySurface (
                instanceHandle,
                surfaceHandle,
                pCallbacks
        );
    }

    return true;
}


#define C_ENG_MAP_START     CLASS ( Engine, PARENT ( Object ) )
#include <ObjectMapping.hpp>

Self :: Constructor () noexcept = default;

auto Self :: instance () noexcept -> Self & {
    static __C_ENG_TYPE ( Engine ) instance;
    return instance;
}

auto Self :: start () noexcept -> Self & {
    (void) __C_ENG_TYPE ( Logger ) :: instance().debug(
            "Engine Created at 0x" +
            :: toString ( this ) + " and booting up" // NOLINT(clion-misra-cpp2008-5-2-9)
    );

    return this->startup().run().shutdown();
}

auto Self :: startup () noexcept -> Self & {
    this->setState ( __C_ENG_TYPE ( EngineState ) :: EngineStateStartup );

    __C_ENG_TYPE ( Controller ) :: setEngine ( this );
    __C_ENG_TYPE ( Monitor ) :: initMonitorHandler ();

    return this
        ->initializeSettings()
        .initializeRenderEngine();
}

auto Self :: initializeRenderEngine () noexcept -> Self & {
    this->setState ( __C_ENG_TYPE ( EngineState ) :: EngineStateStartupInitializingRenderEngine );

    if ( this->renderEngine() == nullptr ) {
        (void) __C_ENG_TYPE ( Logger ) :: instance ().info ("No Render Engine present, using default (Vulkan)");

        this->_renderEngine = new vulkan :: __C_ENG_TYPE ( VulkanRenderEngine );
        this->_externalRenderEngine = false;
    }

    (void) this->renderEngine()->setRenderSurfaceCallbacks({
        .attachCallback = & renderSurfaceAttachCallback,
        .detachCallback = & renderSurfaceDetachCallback,
        .pUserData      = this
    });

    (void) this->renderEngine()->init();

    return * this;
}

auto Self :: initializeSettings () noexcept -> Self & {
    this->setState ( __C_ENG_TYPE ( EngineState ) :: EngineStateStartupAcquiringSettings );

    return * this;
}

auto Self :: run () noexcept -> Self & {
    this->setState ( __C_ENG_TYPE ( EngineState ) :: EngineStateRunning );

    (void) __C_ENG_TYPE ( Logger ) :: instance().info ( "Initialization Complete, running Application" );

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

auto Self :: shutdownRequested() noexcept -> bool {
    if ( this->window() != nullptr && this->window()->shouldClose() ) {
        return true;
    }

    (void) this;

    return false;
}

auto Self :: shutdown () noexcept -> Self & {
    this->setState ( __C_ENG_TYPE ( EngineState ) :: EngineStateShutdown );

    if ( this->renderEngine() != nullptr && ! this->externalRenderEngine() ) {
        (void) this->renderEngine()->clear();
    }

    return * this;
}

auto Self :: setWindow (
        __C_ENG_TYPE ( Window ) * window
) noexcept -> Self & {

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

auto Self :: setRenderEngine (
        __C_ENG_TYPE ( RenderEngine ) * renderEngine
) noexcept -> Self & {

    if ( this->renderEngine() != nullptr ) {
        /// detach old render engine

        if ( ! this->externalRenderEngine() ) {
            delete this->renderEngine();
        }
    }

    this->_renderEngine = renderEngine;
    this->_externalRenderEngine = true;

    (void) __C_ENG_TYPE ( Logger ) :: instance().info (
            "Render Engine '"_s +
            this->_renderEngine->name() +
            "' attached to engine"
    );

    return * this;
}

Self :: Destructor () noexcept {
    if ( ! this->externalRenderEngine() ) {
        delete this->renderEngine();
    }
}

auto Self :: toString () const noexcept -> String {
    return __C_ENG_STRINGIFY ( Self ) " "
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

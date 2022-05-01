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
#include <threadIdentification/ThreadIdentification.hpp>

#include <VulkanCore.hpp>
#include <Allocator.hpp>

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE
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
#endif


#define C_ENG_MAP_START     CLASS ( Engine, PARENT ( Object ) )
#include <ObjectMapping.hpp>

Self :: Constructor () noexcept = default;

auto Self :: instance () noexcept -> Self & {
    static __C_ENG_TYPE ( Engine ) instance;
    return instance;
}

auto Self :: start () noexcept -> Self & {
    engine :: storeThreadIdentificationString ( Thread :: currentThreadID(), engine :: engineThreadIdentificationString );

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

    try {
        return this
                ->initializeSettings()
                .initializeRenderEngine();
    } catch ( std :: exception const & e ) {
        Type ( Logger ) :: instance().fatal ( "Failed to initialize render engine : "_s + e.what() );
        return * this;
    }
}

auto Self :: initializeRenderEngine () noexcept (false) -> Self & {
    this->setState ( __C_ENG_TYPE ( EngineState ) :: EngineStateStartupInitializingRenderEngine );

    if ( this->renderEngine() == nullptr ) {
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        (void) __C_ENG_TYPE ( Logger ) :: instance ().info ("No Render Engine present, using default (Vulkan)");

        this->_renderEngine = new vulkan :: __C_ENG_TYPE ( VulkanRenderEngine );
        this->_externalRenderEngine = false;
#endif
    }

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE
    if ( dynamic_cast < vulkan :: Type ( VulkanRenderEngine ) const * > ( this->renderEngine () ) != nullptr ) {
        (void) this->renderEngine()->setRenderSurfaceCallbacks({
            .attachCallback = & renderSurfaceAttachCallback,
            .detachCallback = & renderSurfaceDetachCallback,
            .pUserData      = this
        });
    }
#endif

    if ( this->renderEngine() != nullptr ) {
        (void) this->renderEngine()->init();
    } else {
        Type ( Logger ) :: instance().fatal ( "No Render Engine available, no default value could be chosen" );
    }

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

        (void) this->prepareNextScene ();

        if ( this->window() != nullptr ) {
            double frameStartTime = glfwGetTime();

            __C_ENG_TYPE ( Controller ) :: updateEvents();
            (void) this->window()->pollEvents();
            __C_ENG_TYPE ( Controller ) :: pollEvents();

            double frameEndTime = glfwGetTime();

            this->_frameDeltaTime = frameEndTime - frameStartTime;

            if ( (this->frameCount() + 1ULL) % this->FPSUpdateFrameTime() == 0ULL ) {
                this->_fps = 1000.0 / ( ( frameEndTime - lastFPSUpdateTime ) / static_cast < double > (this->FPSUpdateFrameTime()) );
                lastFPSUpdateTime = frameEndTime;
            }

            if ( this->logFPSToConsole() && ( this->frameCount() + 1ULL) % this->FPSUpdateTickValue() == 0ULL ) {
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
           ", fpsUpdateEvery = "    + this->FPSUpdateFrameTime() + " ticks" +
           ", showFpsEvery = "      + this->FPSUpdateTickValue() + " ticks" +
           ", logFpsToConsole = "   + :: toString ( this->logFPSToConsole() ) +
           ", fps = "               + this->fps() +
           ", attachedWindow = "    + :: toString ( this->window() ) +
           " }";
}

auto Self :: loadNextSceneFrom ( Path const & path ) noexcept -> Self & {

    (void) this->_sceneLoader.start ( path );
    return * this;
}

auto Self :: prepareNextScene () noexcept -> Self & {

    /// init next scene in background
    if ( this->_sceneLoader.state() != SceneLoaderStateSceneReady ) {
        return * this;
    }

    /// loading scene required, insert into Self :: loadNextSceneFrom

    if ( this->_activeScene != nullptr ) {
        /// do this on another thread as well!!!
        (void) this->_activeScene->clear();
    }

    this->_activeScene = this->_sceneLoader.acquire();

    /// transition until move should be introduced as well later

    return * this;
}

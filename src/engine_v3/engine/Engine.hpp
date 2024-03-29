//
// Created by loghin on 18.12.2021.
//

#ifndef __C_ENG_ENGINE_HPP__
#define __C_ENG_ENGINE_HPP__

#include <Preprocess.hpp>
#include <CDS/Pointer>
#include <CDS/Path>

#include <Core.hpp>

#include <EventHandler.hpp>
#include <scene/Scene.hpp>


#define C_ENG_MAP_START     CLASS ( Engine, PARENT ( cds :: Object ) )
#include <ObjectMapping.hpp>

namespace engine {

    __C_ENG_PRE_DECLARE_CLASS ( Window );
    __C_ENG_PRE_DECLARE_CLASS ( RenderEngine );

    Class {
        using SceneType = cds :: UniquePointer < Type ( Scene ) >;

        Const ( PRIMITIVE_TYPE ( cds :: uint64 ),           defaultFPSUpdateTickValue,  VALUE ( 8192 ) )
        Const ( PRIMITIVE_TYPE ( cds :: uint64 ),           defaultFPSUpdateFrameTime,  VALUE ( 512 ) )
        Const ( PRIMITIVE_TYPE ( bool ),                    defaultLogFPSToConsole,     VALUE ( false ) )

        Const ( PRIMITIVE_TYPE ( cds :: uint8 ),            versionVariant,         VALUE ( 0 ) )
        Const ( PRIMITIVE_TYPE ( cds :: uint8 ),            versionMajor,           VALUE ( 0 ) )
        Const ( PRIMITIVE_TYPE ( cds :: uint8 ),            versionMinor,           VALUE ( 3 ) )
        Const ( PRIMITIVE_TYPE ( cds :: uint8 ),            versionPatch,           VALUE ( 277 ) )

        Field ( ENGINE_PRIMITIVE_TYPE ( EngineState ),      state,                  DEFAULT_VALUE ( EngineStateInactive ),          GET_DEFAULT, SET_NONE )
        Field ( ENGINE_PRIMITIVE_TYPE ( Window * ),         window,                 DEFAULT_VALUE ( nullptr ),                      GET_DEFAULT, SET ( setWindow ) )
        Field ( ENGINE_PRIMITIVE_TYPE ( RenderEngine * ),   renderEngine,           DEFAULT_VALUE ( nullptr ),                      GET_DEFAULT, SET ( setRenderEngine ) )
        Field ( PRIMITIVE_TYPE ( bool ),                    externalRenderEngine,   DEFAULT_VALUE ( false ),                        GET_DEFAULT, SET_NONE )

        Field ( PRIMITIVE_TYPE ( bool ),                    logFPSToConsole,        DEFAULT_VALUE ( defaultLogFPSToConsole ),       GET_DEFAULT, SET_DEFAULT )
        Field ( PRIMITIVE_TYPE ( cds :: uint64 ),           FPSUpdateFrameTime,     DEFAULT_VALUE ( defaultFPSUpdateFrameTime ),    GET_DEFAULT, SET_DEFAULT )
        Field ( PRIMITIVE_TYPE ( cds :: uint64 ),           FPSUpdateTickValue,     DEFAULT_VALUE ( defaultFPSUpdateTickValue ),    GET_DEFAULT, SET_DEFAULT )

        Field ( PRIMITIVE_TYPE ( double ),                  frameDeltaTime,         DEFAULT_VALUE ( 0.0 ),                          GET_DEFAULT, SET_NONE )
        Field ( PRIMITIVE_TYPE ( cds :: uint64 ),           frameCount,             DEFAULT_VALUE ( 0 ),                            GET_DEFAULT, SET_NONE )
        Field ( PRIMITIVE_TYPE ( double ),                  fps,                    DEFAULT_VALUE ( 0.0 ),                          GET_DEFAULT, SET_NONE )

        Field ( ENGINE_TYPE ( EventHandler ),               eventHandler,           NO_INIT,                                        GET_DEFAULT, SET_NONE )

        Field ( TYPE ( SceneType ),                         activeScene,            DEFAULT_VALUE ( nullptr ),                      GET_DEFAULT, SET_NONE )

        Field ( TYPE ( Type ( Scene ) :: Loader ),          sceneLoader,            NO_INIT,                                        GET_NONE,    SET_NONE )

    private:
        auto initializeSettings () noexcept -> Self &;
        auto initializeRenderEngine () noexcept (false) -> Self &;
        auto startup () noexcept -> Self &;
        auto run () noexcept -> Self &;
        auto shutdown () noexcept -> Self &;

        auto prepareNextScene () noexcept -> Self &;

        Constructor () noexcept;
        Destructor () noexcept override;

        constexpr auto setState ( __C_ENG_TYPE ( EngineState ) state ) noexcept -> void {
            this->_state = state;
        }

    public:
        auto static instance () noexcept -> Self &;
        auto start () noexcept -> Self &;
        auto shutdownRequested () noexcept -> bool;

        auto loadNextSceneFrom ( cds :: Path const & ) noexcept -> Self &;

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //__C_ENG_ENGINE_HPP__

//
// Created by loghin on 4/6/22.
//

#ifndef __C_ENG_SCENE_HPP__
#define __C_ENG_SCENE_HPP__

#include <Preprocess.hpp>
#include <Core.hpp>
#include <CDS/Array>
#include <CDS/Pointer>
#include <CDS/experimental/JSON>
#include <scene/ECM/Entity.hpp>

#define C_ENG_MAP_START     CLASS ( Scene, ENGINE_PARENT ( EngineObject ) )
#include <ObjectMapping.hpp>

namespace engine {

    __C_ENG_PRE_DECLARE_CLASS ( Shader );

    Class {
        ClassDefs

        Const ( TYPE ( cds :: String ),    sceneNameKey,       VALUE ( "sceneName" ) )
        Const ( TYPE ( cds :: String ),    rootEntitiesKey,    VALUE ( "rootEntities" ) )

    private:
        friend class Type ( SceneLoader );

        auto loadEntity ( cds :: json :: standard :: JsonObject const & ) noexcept (false) -> cds :: UniquePointer < Type ( Entity ) >;

        using DirectEntities    = cds :: Array < cds :: UniquePointer < Type ( Entity ) > >;
        using IndirectEntities  = cds :: DoubleLinkedList < cds :: ForeignPointer < Type ( Entity ) > >;
        using Shaders           = cds :: Array < cds :: UniquePointer < Type ( Shader ) > >;

        Field ( TYPE ( IndirectEntities ),      entities,       NO_INIT, GET_DEFAULT, SET_NONE )
        Field ( TYPE ( DirectEntities ),        rootEntities,   NO_INIT, GET_DEFAULT, SET_NONE )

        Field ( TYPE ( cds :: String ),         name,           NO_INIT, GET_DEFAULT, SET_DEFAULT )

        auto removeNonRoot ( cds :: ForeignPointer < Type ( Entity ) > const & ) noexcept -> Self &;

    public:
        Constructor () noexcept = default;
        Constructor ( Self const & ) noexcept = delete;
        Constructor ( Self && ) noexcept;

        auto operator = ( Self const & ) noexcept -> Self & = delete;
        auto operator = ( Self && ) noexcept -> Self &;

        Destructor () noexcept override;

        auto loadFrom ( cds :: json :: standard :: JsonObject const & ) noexcept (false) -> Self &;
        auto dumpTo ( cds :: json :: standard :: JsonObject & ) noexcept -> Self &;
        auto clear () noexcept -> Self & override;

        auto remove ( cds :: ForeignPointer < Type ( Entity ) > const & ) noexcept -> Self &;

        class Loader;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START NESTED_CLASS ( Loader, ENGINE_TYPE ( Scene ), ENGINE_PARENT ( EngineObject ) )
#include <ObjectMapping.hpp>

namespace engine {

    Class {
        ClassDefs

        using SceneLoaderStateType  = cds :: Atomic < Type ( SceneLoaderState ) >;
        using SceneLoaderThreadType = cds :: UniquePointer < cds :: Thread >;
        using SceneType             = cds :: UniquePointer < Type ( Scene ) >;

        Field ( TYPE ( SceneLoaderStateType ),      state,              DEFAULT_VALUE ( SceneLoaderStateIdle ), GET_DEFAULT, SET_NONE )
        Field ( TYPE ( SceneLoaderThreadType ),     thread,             NO_INIT,                                GET_NONE,    SET_NONE )
        Field ( TYPE ( SceneType ),                 scene,              NO_INIT,                                GET_NONE,    SET_NONE )
        Field ( TYPE ( cds :: Boolean :: Atomic ),  threadKeepAlive,    DEFAULT_VALUE ( true ),                 GET_NONE,    SET_NONE )

    public:
        auto start ( cds :: Path const & ) noexcept -> Self &;
        auto cancel () noexcept -> Self &;
        auto acquire () noexcept -> Nester *;

        auto clear () noexcept -> Self & override;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif // __C_ENG_SCENE_HPP__

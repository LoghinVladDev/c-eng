//
// Created by loghin on 4/6/22.
//

#ifndef __C_ENG_SCENE_HPP__
#define __C_ENG_SCENE_HPP__

#include <Preprocess.hpp>
#include <Core.hpp>
#include <CDS/Array>
#include <CDS/Pointer>
#include <CDS/Queue>
#include <CDS/HashMap>
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

        using DirectEntities        = cds :: Array < cds :: UniquePointer < Type ( Entity ) > >;
        using IndirectEntities      = cds :: DoubleLinkedList < cds :: ForeignPointer < Type ( Entity ) > >;
        using NameMappedEntities    = cds :: HashMap < cds :: String, cds :: ForeignPointer < Type ( Entity ) > >;
        using Shaders               = cds :: Array < cds :: UniquePointer < Type ( Shader ) > >;


        Field ( TYPE ( IndirectEntities ),      entities,           NO_INIT, GET_DEFAULT, SET_NONE )
        Field ( TYPE ( DirectEntities ),        rootEntities,       NO_INIT, GET_DEFAULT, SET_NONE )
        Field ( TYPE ( NameMappedEntities ),    nameMappedEntities, NO_INIT, GET_DEFAULT, SET_NONE )

        Field ( TYPE ( cds :: String ),         name,               NO_INIT, GET_DEFAULT, SET_DEFAULT )
        Field ( TYPE ( cds :: String ),         unusedEntityName,   NO_INIT, GET_DEFAULT, SET_DEFAULT )

        auto removeNonRoot ( cds :: ForeignPointer < Type ( Entity ) > const & ) noexcept -> Self &;

    public:
        auto generateUnusedEntityName () noexcept -> cds :: String const &;

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

    private:
        using LoaderThreadStateFunction = auto (Self :: *) () noexcept -> void;

        auto loaderThreadIdle () noexcept -> void;
        auto loaderThreadLoadingJsonFile () noexcept -> void;
        auto loaderThreadLoadingSceneProperties () noexcept -> void;
        auto loaderThreadLoadingSceneRootEntityArray () noexcept -> void;
        auto loaderThreadLoadingSceneEntity () noexcept -> void;
        auto loaderThreadLoadingSceneEntityChildren () noexcept -> void;
        auto loaderThreadError () noexcept -> void;
        auto loaderThreadCleanup () noexcept -> void;

        auto validationStateCheckDuplicateName () noexcept -> void;

        enum class LoaderThreadState {
            Idle,
            LoadingJsonFile,
            LoadingSceneProperties,
            LoadingSceneRootEntityArray,
            LoadingSceneEntity,
            LoadingSceneEntityChildren,
            Error,
            Cleanup,
            Done,

            ValidationStateCheckDuplicateName,
        };

        constexpr static auto stateFunction ( LoaderThreadState state ) noexcept -> LoaderThreadStateFunction {
            switch ( state ) {
                case LoaderThreadState :: Idle:                                 return & Self :: loaderThreadIdle;
                case LoaderThreadState :: LoadingJsonFile:                      return & Self :: loaderThreadLoadingJsonFile;
                case LoaderThreadState :: LoadingSceneProperties:               return & Self :: loaderThreadLoadingSceneProperties;
                case LoaderThreadState :: LoadingSceneRootEntityArray:          return & Self :: loaderThreadLoadingSceneRootEntityArray;
                case LoaderThreadState :: LoadingSceneEntity:                   return & Self :: loaderThreadLoadingSceneEntity;
                case LoaderThreadState :: LoadingSceneEntityChildren:           return & Self :: loaderThreadLoadingSceneEntityChildren;
                case LoaderThreadState :: Error:                                return & Self :: loaderThreadError;
                case LoaderThreadState :: Cleanup:                              return & Self :: loaderThreadCleanup;
                case LoaderThreadState :: ValidationStateCheckDuplicateName:    return & Self :: validationStateCheckDuplicateName;
                case LoaderThreadState :: Done:                                 return nullptr;
            }
        }

        constexpr static auto stateToString ( LoaderThreadState state ) noexcept -> cds :: StringLiteral {
            switch ( state ) {
                case LoaderThreadState :: Idle:                                 return "Idle";
                case LoaderThreadState :: LoadingJsonFile:                      return "LoadingJsonFile";
                case LoaderThreadState :: LoadingSceneProperties:               return "LoadingSceneProperties";
                case LoaderThreadState :: LoadingSceneRootEntityArray:          return "LoadingSceneRootEntityArray";
                case LoaderThreadState :: LoadingSceneEntity:                   return "LoadingSceneEntity";
                case LoaderThreadState :: LoadingSceneEntityChildren:           return "LoadingSceneEntityChildren";
                case LoaderThreadState :: Error:                                return "Error";
                case LoaderThreadState :: Cleanup:                              return "Cleanup";
                case LoaderThreadState :: ValidationStateCheckDuplicateName:    return "ValidationStateCheckDuplicateName";
                case LoaderThreadState :: Done:                                 return "Done";
            }
        }

        inline auto setNextState ( LoaderThreadState state ) noexcept -> void {
            this->_loaderThreadControl.state    = state;
            this->_loaderThreadControl.function = Self :: stateFunction ( this->_loaderThreadControl.state );
            this->resetValidationState();
        }

        inline auto setNextValidationState ( LoaderThreadState state ) noexcept -> void {
            this->_loaderThreadControl.validationData.state     = state;
            this->_loaderThreadControl.validationData.function  = Self :: stateFunction ( this->_loaderThreadControl.validationData.state );
        }

        inline auto resetValidationState () noexcept -> void {
            this->_loaderThreadControl.validationData.function  = nullptr;
            this->_loaderThreadControl.validationData.passed    = true;
        }

        inline auto setError ( cds :: String const & errorReason ) noexcept -> void {
            this->_loaderThreadControl.data.errorReason = errorReason;
            this->_loaderThreadControl.data.errorState  = this->_loaderThreadControl.state;
            this->setNextState ( LoaderThreadState :: Error );
        }

        struct LoaderThreadInput {
            cds :: Path     path;
            Nester        * pScene;
        };

        using SceneEntityQueueData          = cds :: Reference < cds :: json :: standard :: JsonObject const >;
        using SceneEntityParentQueueData    = cds :: ForeignPointer < Type ( Entity ) >;
        using SceneEntityQueueEntry         = cds :: Pair < SceneEntityQueueData, SceneEntityParentQueueData >;
        using SceneEntityQueue              = cds :: Queue < SceneEntityQueueEntry >;
        using LateLoadComponents            = cds :: DoubleLinkedList < Type ( Component ) * >;

        struct LoaderThreadData {
            cds :: json :: standard :: JsonObject                       sceneJson;
            SceneEntityQueue                                            queue;
            LateLoadComponents                                          lateLoadComponents;

            cds :: json :: standard :: JsonArray                const * pCurrentChildrenArray;
            cds :: json :: standard :: JsonArray :: ConstIterator       entityIterator;
            cds :: ForeignPointer < Type ( Entity ) >                   childrenParent;

            cds :: String                                               errorReason;
            LoaderThreadState                                           errorState;
        };

#ifndef NDEBUG

        struct LoaderThreadTestingData {
            cds :: uint32       idleStateCount                          = 0U;
            cds :: uint32       loadingJsonFileStateCount               = 0U;
            cds :: uint32       loadingScenePropertiesStateCount        = 0U;
            cds :: uint32       loadingSceneRootEntityArrayStateCount   = 0U;
            cds :: uint32       loadingSceneEntityStateCount            = 0U;
            cds :: uint32       loadingSceneEntityChildrenStateCount    = 0U;
            cds :: uint32       errorStateCount                         = 0U;
            cds :: uint32       cleanupStateCount                       = 0U;
            cds :: uint32       doneStateCount                          = 0U;
            cds :: uint32       validationStateCount                    = 0U;
        };

        inline auto stateCount ( LoaderThreadState state ) noexcept -> cds :: uint32 & {
            switch ( state ) {
                case LoaderThreadState :: Idle:                                 return this->_loaderThreadControl.test.idleStateCount;
                case LoaderThreadState :: LoadingJsonFile:                      return this->_loaderThreadControl.test.loadingJsonFileStateCount;
                case LoaderThreadState :: LoadingSceneProperties:               return this->_loaderThreadControl.test.loadingScenePropertiesStateCount;
                case LoaderThreadState :: LoadingSceneRootEntityArray:          return this->_loaderThreadControl.test.loadingSceneRootEntityArrayStateCount;
                case LoaderThreadState :: LoadingSceneEntity:                   return this->_loaderThreadControl.test.loadingSceneEntityStateCount;
                case LoaderThreadState :: LoadingSceneEntityChildren:           return this->_loaderThreadControl.test.loadingSceneEntityChildrenStateCount;
                case LoaderThreadState :: Error:                                return this->_loaderThreadControl.test.errorStateCount;
                case LoaderThreadState :: Cleanup:                              return this->_loaderThreadControl.test.cleanupStateCount;
                case LoaderThreadState :: Done:                                 return this->_loaderThreadControl.test.doneStateCount;
                case LoaderThreadState :: ValidationStateCheckDuplicateName:    return this->_loaderThreadControl.test.validationStateCount;
            }
        }

#endif

        struct LoaderThreadValidationData {
            LoaderThreadState           state;
            LoaderThreadStateFunction   function;
            bool                        passed;
        };

        struct LoaderThreadControl {
            LoaderThreadState           state;
            LoaderThreadStateFunction   function;
            LoaderThreadInput           input;
            LoaderThreadData            data;
            LoaderThreadValidationData  validationData;
#ifndef NDEBUG
            LoaderThreadTestingData     test;
#endif
        };

        Field ( TYPE ( LoaderThreadControl ),       loaderThreadControl, NO_INIT, GET_NONE, SET_NONE )

    public:
        auto start ( cds :: Path const & ) noexcept -> Self &;
        auto cancel () noexcept -> Self &;
        auto acquire () noexcept -> Nester *;

        auto clear () noexcept -> Self & override;

        Destructor () noexcept;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif // __C_ENG_SCENE_HPP__

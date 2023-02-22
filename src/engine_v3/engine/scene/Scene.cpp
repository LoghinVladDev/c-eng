//
// Created by loghin on 4/6/22.
//

#include "Scene.hpp"
#include <scene/ECM/Entity.hpp>
#include <Logger.hpp>
#include <CDS/Queue>
#include <CDS/Thread>
#include <CDS/Path>
#include <threadIdentification/ThreadIdentification.hpp>
#include <scene/loader/SceneComponentLoader.hpp>

using namespace cds;
using namespace engine;


#define C_ENG_MAP_START CLASS ( Scene, ENGINE_PARENT ( EngineObject ) )
#include <ObjectMapping.hpp>

Self :: Constructor ( Self && object ) noexcept :
        _entities ( std :: move ( object._entities ) ),
        _rootEntities ( std :: move ( object._rootEntities ) ) {

}

Self :: Destructor () noexcept {
    (void) this-> Self :: clear ();
}

auto Self :: operator = ( Self && object ) noexcept -> Self & {

    if ( this == & object ) {
        return * this;
    }

    for ( auto const & rootEntity : this->rootEntities() ) {
        (void) rootEntity->clear ();
    }

    this->_rootEntities = std :: move ( object._rootEntities );
    this->_entities     = std :: move ( object._entities );

    return * this;
}

auto Self :: clear () noexcept -> Self & {

    for ( auto & entity : this->_entities ) {
        entity->_scene = nullptr;
    }

    this->_rootEntities.clear();
    this->_entities.clear();

    return * this;
}

auto Self :: loadFrom ( json :: standard :: JsonObject const & json ) noexcept (false) -> Self & {

    (void) this->clear();

    try {
        this->name() = json.getString ( Self :: sceneNameKey );
    } catch ( KeyException const & keyException ) {
        log :: warn() << "Key '" << Self :: sceneNameKey << "' does not exist : " << keyException.toString();
    } catch ( TypeException const & ) {
        log :: warn() << "Invalid Type for key '" << Self :: sceneNameKey << "'";
    }

    try {
        auto const & rootEntityArray = json.getArray ( Self :: rootEntitiesKey );
        for ( auto const & entityObject : rootEntityArray ) {

            try {
                auto const & entityJson = entityObject.getJson();

                try {
                    (void) this->_rootEntities.pushBack ( this->loadEntity ( entityJson ) );
                } catch ( Exception const & ) {
                    log :: warn() << "Entity could not be added to scene";
                }

            } catch ( TypeException const & ) {
                log :: warn() << "Invalid Type for entity'" << Self :: rootEntitiesKey << "'";
            }
        }

    } catch ( KeyException const & keyException ) {
        log :: warn() << "Key '" << Self :: rootEntitiesKey << "' does not exist : " << keyException.toString();
    } catch ( TypeException const & ) {
        log :: warn() << "Invalid Type for key '" << Self :: rootEntitiesKey << "'";
    }

    return * this;
}

auto Self :: dumpTo ( json :: standard :: JsonObject & json ) noexcept -> Self & {

    json.clear ();
    (void) json.put ( Self :: sceneNameKey, this->name() );

    json :: standard :: JsonArray rootEntityArray;

    for ( auto const & entity : this->rootEntities() ) {

        json :: standard :: JsonObject rootEntityObject;
        (void) entity->dumpTo ( rootEntityObject );

        (void) rootEntityArray.add ( rootEntityObject );
    }

    (void) json.put ( Self :: rootEntitiesKey, rootEntityArray );

    return * this;
}

auto Self :: loadEntity ( json :: standard :: JsonObject const & json ) noexcept (false) -> UniquePointer < Type ( Entity ) > { // NOLINT(misc-no-recursion)

    try {
        auto const & entityType = json.getString ( Type ( Entity ) :: typeKey );

        try {
            auto entity = Type ( Entity ) :: instantiateByClassName ( entityType );

            try {
                (void) entity->loadFrom ( json );

                try {
                    auto const & childrenArray = json.getArray ( Type ( Entity ) :: childrenKey );
                    for ( auto const & childObject : childrenArray ) {

                        try {
                            (void) entity->add ( this->loadEntity ( childObject.getJson() ) );

                        } catch ( TypeException const & ) {
                            log :: warn() << "Entity Child not formatted properly, it will not be added to Entity";
                        } catch ( Exception const & ) {
                            log :: warn() << "Entity Child could not be loaded";
                        }
                    }

                } catch ( KeyException const & ) {
                    /* do nothing */
                } catch ( TypeException const & ) {
                    log :: warn() << "Entity has a '" << Type ( Entity ) :: childrenKey << "' key, but it is not formatted properly ( expected array )";
                }

                entity->_scene = this;
                (void) this->_entities.pushFront ( entity );

            } catch ( Exception const & ) {
                log :: warn() << "Failed to load Entity properties";
            }

            return entity;

        } catch ( Exception const & exception ) {
            log :: err() << "Failed to construct Entity : " << exception.toString();
            throw;
        }

    } catch ( KeyException const & ) {
        log :: err() << "Key '" << Type ( Entity ) :: typeKey << "' does not exist, and cannot construct entity because of it";
        throw;
    } catch ( TypeException const & ) {
        log :: err() << "Object marked as Entity Type is not String, cannot construct entity because of it";
        throw;
    }
}

auto Self :: remove ( ForeignPointer < Type ( Entity ) > const & entity ) noexcept -> Self & {

    for ( auto const & rootEntity : this->rootEntities() ) {
        if ( rootEntity.equals(entity) ) {
            (void) this->_rootEntities.removeFirst ( rootEntity );
            break;
        }
    }

    (void) this->_entities.removeFirst ( entity );
    entity->_parent = nullptr;

    for ( auto const & child : entity->children() ) {
        (void) this->removeNonRoot( child );
    }

    return * this;
}

auto Self :: removeNonRoot ( ForeignPointer < Type ( Entity ) > const & entity ) noexcept -> Self & { // NOLINT(misc-no-recursion)

    (void) this->_entities.removeFirst ( entity );
    entity->_parent = nullptr;

    for ( auto const & child : entity->children() ) {
        (void) this->removeNonRoot( child );
    }

    return * this;
}

auto Self :: generateUnusedEntityName () noexcept -> String const & {
    static uint32 counter = 1U;

    this->_unusedEntityName = "Entity "_s + counter ++;
    while ( this->_nameMappedEntities.containsKey ( this->_unusedEntityName ) ) {
        this->_unusedEntityName = "Entity "_s + counter ++;
    }

    return this->_unusedEntityName;
}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START NESTED_CLASS ( Loader, ENGINE_TYPE ( Scene ), ENGINE_PARENT ( EngineObject ) )
#include <ObjectMapping.hpp>

auto Self :: start ( Path const & path ) noexcept -> Self & {
    if ( this->state() != SceneLoaderStateIdle ) {
        (void) this->cancel();
    }

    this->_threadKeepAlive  = true;
    this->_scene            = new Type ( Scene );

    this->setNextState ( Self :: startingState );
    this->_loaderThreadControl.input    = {
            .path   = path,
            .pScene = this->_scene.get()
    };

    this->_thread = new Runnable ([this]{

        engine :: storeThreadIdentificationString ( Thread :: currentThreadID(), engine :: sceneLoaderThreadIdentificationString );

        while ( this->_threadKeepAlive ) {

#ifndef NDEBUG
            if ( this->_loaderThreadControl.validationData.function != nullptr ) {
                this->_loaderThreadControl.validationData.passed = true;
                (this->*this->_loaderThreadControl.validationData.function)();
            }
#endif

            if ( this->_loaderThreadControl.function == nullptr ) {
                this->setError ( "No State Function to Call in Loader Thread Runtime" );
            }

#ifndef NDEBUG
            auto state = this->_loaderThreadControl.state;
#endif

            (this->*this->_loaderThreadControl.function)();

#ifndef NDEBUG
            ++ this->stateCount ( state );
#endif

        }
    });

    this->_state = SceneLoaderStateLoading;
    this->_thread->start();

    return * this;
}

auto Self :: loaderThreadIdle () noexcept -> void {

    if ( this->_loaderThreadControl.input.pScene == nullptr ) {
        this->setError ( "Failed to Load Scene due to input scene being null" );
    }

    this->_loaderThreadControl.data.pLoader = new Type ( SceneComponentLoader );

    this->setNextState ( LoaderThreadState :: LoadingJsonFile );
}

auto Self :: loaderThreadLoadingJsonFile () noexcept -> void {

    try {
        this->_loaderThreadControl.data.sceneJson = json :: loadJson ( this->_loaderThreadControl.input.path );
        this->setNextState ( LoaderThreadState :: LoadingSceneProperties );
    } catch ( Exception const & exception ) {

        this->setError (
                cds :: String :: f (
                        "Failure to load scene at '%s', reason = %s",
                        this->_loaderThreadControl.input.path.toString().cStr(),
                        exception.toString().cStr()
                )
        );
    }
}

auto Self :: loaderThreadLoadingSceneProperties () noexcept -> void {

    try {
        this->_loaderThreadControl.input.pScene->name() = this->_loaderThreadControl.data.sceneJson.getString ( Nester :: sceneNameKey );
    } catch ( KeyException const & keyException ) {
        log :: warn() << "Key '" << Nester :: sceneNameKey << "' does not exist : " << keyException.toString();
    } catch ( TypeException const & ) {
        log :: warn() << "Invalid Type for key '" << Nester :: sceneNameKey << "'";
    }

    this->setNextState ( LoaderThreadState :: LoadingSceneRootEntityArray );
}

auto Self :: loaderThreadLoadingSceneRootEntityArray () noexcept -> void {

    try {
        this->_loaderThreadControl.data.pCurrentChildrenArray   =
                & ( this->_loaderThreadControl.data.sceneJson.getArray ( Nester :: rootEntitiesKey ) );

        this->_loaderThreadControl.data.entityIterator          =
                this->_loaderThreadControl.data.pCurrentChildrenArray->begin();

        this->_loaderThreadControl.data.childrenParent          = nullptr;

        this->setNextState ( LoaderThreadState :: LoadingSceneEntityChildren );
        return;
    } catch ( KeyException const & keyException ) {
        log :: warn() << "Key '" << Nester :: rootEntitiesKey << "' does not exist : " << keyException.toString();
    } catch ( TypeException const & ) {
        log :: warn() << "Invalid Type for key '" << Nester :: rootEntitiesKey << "'";
    }

    this->setNextState ( LoaderThreadState :: Cleanup );
}

auto Self :: loaderThreadLoadingSceneEntityChildren () noexcept -> void {

    if ( this->_loaderThreadControl.data.entityIterator == this->_loaderThreadControl.data.pCurrentChildrenArray->end() ) {
        this->setNextState ( LoaderThreadState :: LoadingSceneEntityComponents );
        return;
    }

    try {
        auto const & entityJson = this->_loaderThreadControl.data.entityIterator->getJson();

        (void) this->_loaderThreadControl.data.queue.push ({
                Reference ( entityJson ),
                this->_loaderThreadControl.data.childrenParent
        });

    } catch ( TypeException const & ) {
        log :: warn() << "Invalid Type for entity'" << Nester :: rootEntitiesKey << "'";
    }

    ++ this->_loaderThreadControl.data.entityIterator;
}

auto Self :: loaderThreadLoadingSceneEntity () noexcept -> void {

    if ( this->_loaderThreadControl.data.queue.empty() ) {

        this->setNextState ( LoaderThreadState :: WaitingForComponentLoading );
        return;
    }

    auto entityJsonEntry        = this->_loaderThreadControl.data.queue.pop();
    auto const & entityJson     = entityJsonEntry.getFirst().get();
    auto const & entityParent   = entityJsonEntry.getSecond();

    if ( ! this->_loaderThreadControl.validationData.passed ) {
        return;
    }

    try {
        auto const & entityType = entityJson.getString ( Type ( Entity ) :: typeKey );

        try {
            auto newEntity = Type ( Entity ) :: instantiateByClassName ( entityType );
            newEntity->_scene   = this->_loaderThreadControl.input.pScene;
            newEntity->_parent  = entityParent;

            try {
                (void) newEntity->loadFrom ( entityJson );
            } catch ( Exception const & ) {
                log :: warn() << "Failed to load Entity properties";
            }

            (void) this->_loaderThreadControl.input.pScene->_entities.pushBack ( newEntity );
            (void) this->_loaderThreadControl.input.pScene->_nameMappedEntities.emplace ( newEntity->name(), newEntity );

            for ( auto const & component : newEntity->_components ) {
                (void) this->_loaderThreadControl.data.lateLoadComponents.pushBack ( component.second() );
            }

            try {
                this->_loaderThreadControl.data.pCurrentChildrenArray   =
                        & ( entityJson.getArray( Type ( Entity ) :: childrenKey ) );

                this->_loaderThreadControl.data.entityIterator          =
                        this->_loaderThreadControl.data.pCurrentChildrenArray->begin();

                this->_loaderThreadControl.data.childrenParent          = newEntity.get();

                this->setNextState ( LoaderThreadState :: LoadingSceneEntityChildren );
            } catch ( KeyException const & ) {
                /* do nothing */
            } catch ( TypeException const & ) {
                log :: warn() << "Entity has a '" << Type ( Entity ) :: childrenKey << "' key, but it is not formatted properly ( expected array )";
            }

            List < UniquePointer < Type ( Entity ) > > * pEntityList = & this->_loaderThreadControl.input.pScene->_rootEntities;
            if ( entityParent != nullptr ) {
                pEntityList = & entityParent->_children;
            }

            (void) pEntityList->pushBack ( std :: move ( newEntity ) );

        } catch ( Exception const & exception ) {
            log :: err() << "Failed to construct Entity : " << exception.toString();
        }
    } catch ( KeyException const & ) {
        log :: err() << "Key '" << Type ( Entity ) :: typeKey << "' does not exist, and cannot construct entity because of it";
    } catch ( TypeException const & ) {
        log :: err() << "Object marked as Entity Type is not String, cannot construct entity because of it";
    }
}

auto Self :: validationStateCheckDuplicateName () noexcept -> void {

    auto const & entityJsonQueue    = this->_loaderThreadControl.data.queue;

    if ( entityJsonQueue.empty() ) {
        return;
    }

    auto const & entityJsonEntry    = entityJsonQueue.front();
    auto const & entityJson         = entityJsonEntry.getFirst().get();

    try {
        if ( this->_scene->_nameMappedEntities.containsKey ( entityJson.getString ( Type ( Entity ) :: nameKey ) ) ) {
            log :: warn()
                    << "Entity Validation Passed before being added to scene. Reason : "
                    << "Name '"
                    << entityJson.getString ( Type ( Entity ) :: nameKey )
                    << "' duplicate in Scene";

            this->_loaderThreadControl.validationData.passed = false;
        }
    } catch ( KeyException const & ) {
        /* do nothing */
    } catch ( TypeException const & ) {
        /* do nothing */
    }
}

auto Self :: loaderThreadError () noexcept -> void {

    log :: err()
            << "Loader Thread encountered an error in state '"
            << Self :: stateToString ( this->_loaderThreadControl.data.errorState )
            << "', reason = "
            << this->_loaderThreadControl.data.errorReason;

    this->_loaderThreadControl.data.errorReason.clear();
    this->_loaderThreadControl.data.errorState  = LoaderThreadState :: Error;

    this->_state            = SceneLoaderStateReadyError;

    this->setNextState ( LoaderThreadState :: Cleanup );
}

auto Self :: loaderThreadLoadingSceneEntityComponents () noexcept -> void {

    this->_loaderThreadControl.data.pLoader->update ( this->_loaderThreadControl.data.lateLoadComponents );

    this->setNextState ( LoaderThreadState :: LoadingSceneEntity );
    this->setNextValidationState ( LoaderThreadState :: ValidationStateCheckDuplicateName );
}

auto Self :: loaderThreadWaitingForComponentLoading () noexcept -> void {

    if ( this->_loaderThreadControl.data.pLoader->done() ) {
        this->setNextState ( LoaderThreadState :: Cleanup );
    }
}

auto Self :: loaderThreadCleanup () noexcept -> void {

    this->_loaderThreadControl.data.sceneJson.clear();
    this->_loaderThreadControl.data.queue.clear();
    this->_loaderThreadControl.data.lateLoadComponents.clear();
    this->_loaderThreadControl.input.pScene                 = nullptr;
    this->_loaderThreadControl.data.pCurrentChildrenArray   = nullptr;
    this->_loaderThreadControl.data.childrenParent          = nullptr;

    this->_loaderThreadControl.data.pLoader->clear();
    delete exchange ( this->_loaderThreadControl.data.pLoader, nullptr );

#ifndef NDEBUG

    this->_loaderThreadControl.test = {
            .idleStateCount                         = 0U,
            .loadingJsonFileStateCount              = 0U,
            .loadingScenePropertiesStateCount       = 0U,
            .loadingSceneRootEntityArrayStateCount  = 0U,
            .loadingSceneEntityStateCount           = 0U,
            .loadingSceneEntityChildrenStateCount   = 0U,
            .loadingSceneEntityComponentsStateCount = 0U,
            .errorStateCount                        = 0U,
            .cleanupStateCount                      = 0U,
            .doneStateCount                         = 0U,
            .validationStateCount                   = 0U,
            .otherStates                            = 0U
    };

#endif

    this->_threadKeepAlive  = false;

    if ( this->_state != SceneLoaderStateReadyError ) {
        this->_state = SceneLoaderStateSceneReady;

#ifndef NDEBUG

        this->_loaderThreadControl.test.doneStateCount = 1U;

#endif

    }

    this->setNextState ( LoaderThreadState :: Done );
}

auto Self :: acquire () noexcept -> Nester * {
    if ( this->_state == SceneLoaderStateLoading ) {
        log :: warn() <<
                "Acquired Scene while it was still loading. This can lead to crashes";

        (void) this->cancel();
    }

    this->_state = SceneLoaderStateIdle;

    return this->_scene.release();
}

auto Self :: cancel () noexcept -> Self & {
    this->_threadKeepAlive = false;
    this->_thread->join();
    return * this;
}

auto Self :: clear () noexcept -> Self & {
    (void) this->cancel();
    return * this;
}

Self :: Destructor () noexcept {
    (void) this->Self :: clear();
}

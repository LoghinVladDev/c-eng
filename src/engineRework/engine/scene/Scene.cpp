//
// Created by loghin on 4/6/22.
//

#include "Scene.hpp"
#include <scene/ECM/Entity.hpp>
#include <Logger.hpp>

using namespace cds;
using namespace engine;


#define C_ENG_MAP_START CLASS ( Scene, ENGINE_PARENT ( EngineObject ) )
#include <ObjectMapping.hpp>

Self :: Constructor ( Self && object ) noexcept :
        _entities ( std :: move ( object._entities ) ),
        _rootEntities ( std :: move ( object._rootEntities ) ) {

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
        for ( auto entityObject : rootEntityArray ) {

            try {
                auto const & entityJson = entityObject.getJson();

                try {
                    (void) this->_rootEntities.pushBack ( this->loadEntity ( entityObject.getJson() ) );
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
                            (void) entity->addChild ( this->loadEntity ( childObject.getJson() ) );

                        } catch ( TypeException const & ) {
                            log :: warn() << "Entity Child not formatted properly, it will not be added to Entity";
                        } catch ( Exception const & ) {
                            log :: warn() << "Entity Child could not be loaded";
                        }
                    }

                } catch ( KeyException const & ) {
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

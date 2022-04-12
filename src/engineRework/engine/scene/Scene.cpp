//
// Created by loghin on 4/6/22.
//

#include "Scene.hpp"
#include <scene/ECM/Entity.hpp>

using namespace cds;
using namespace engine;


#define C_ENG_MAP_START CLASS ( Scene, ENGINE_PARENT ( EngineObject ) )
#include <ObjectMapping.hpp>

Self :: Constructor ( Self && object ) noexcept :
        _entities ( std :: forward < IndirectEntities > ( object._entities ) ),
        _rootEntities ( std :: forward < DirectEntities > ( object._rootEntities ) ) {

}

auto Self :: operator = ( Self && object ) noexcept -> Self & {

    if ( this == & object ) {
        return * this;
    }

    for ( auto & rootEntity : this->rootEntities() ) {
        rootEntity->clear ();
    }

    this->_rootEntities = std :: forward < DirectEntities > ( object._rootEntities );
    this->_entities     = std :: forward < IndirectEntities > ( object._entities );

    return * this;
}

auto Self :: clear () noexcept -> Self & {
    this->_rootEntities.clear();
    this->_entities.clear();

    return * this;
}

auto Self :: loadFrom ( json :: standard :: JsonObject const & json ) noexcept (false) -> Self & {

    return * this;
}

auto Self :: dumpTo ( json :: standard :: JsonObject & json ) noexcept -> Self & {

    json.clear ();
    json.put ( "sceneName", this->name() );

    json :: standard :: JsonArray rootEntityArray;

    for ( auto const & entity : this->rootEntities() ) {

        json :: standard :: JsonObject rootEntityObject;
        entity->dumpTo ( rootEntityObject );

        rootEntityArray.add ( rootEntityObject );
    }

    json.put ( "rootEntities", rootEntityArray );

    return * this;
}

//
// Created by loghin on 4/6/22.
//

#include "Entity.hpp"
#include <scene/Scene.hpp>
#include <Logger.hpp>
#include <scene/ECM/Component.hpp>

using namespace cds;
using namespace engine;

#define C_ENG_MAP_START CLASS ( Entity, ENGINE_PARENT ( EngineObject ) )
#include <ObjectMapping.hpp>

auto Self :: addChild ( UniquePointer < Type ( Entity ) > && entity ) noexcept -> Self & {

    this->_children.add ( std :: forward < UniquePointer < Type ( Entity ) > > ( entity ) );
    entity->_parent = this;

    return * this;
}

Self :: Constructor ( Self const & entity ) noexcept :
        _parent ( nullptr ) {

    for ( auto const & component : entity._components ) {
        (void) this->_components.emplace ( component.first(), component.second()->copy() );
    }
}

Self :: Constructor ( Self && entity ) noexcept :
        _parent ( std :: move ( entity._parent ) ),
        _children ( std :: move ( entity._children ) ),
        _components ( std :: move ( entity._components ) ) {

}

auto Self :: operator = ( Self const & entity ) noexcept -> Self & {
    if ( this == & entity ) {
        return * this;
    }

    (void) this->clear();

    for ( auto const & component : entity._components ) {
        (void) this->_components.emplace ( component.first(), component.second()->copy() );
    }

    return * this;
}

auto Self :: operator = ( Self && entity ) noexcept -> Self & {
    if ( this == & entity ) {
        return * this;
    }

    (void) this->clear();

    this->_parent       = std :: move ( entity._parent );
    this->_children     = std :: move ( entity._children );
    this->_components   = std :: move ( entity._components );

    return * this;
}

Self :: Destructor () noexcept {
    (void) this-> Self :: clear();
}

auto Self :: clear () noexcept -> Self & { // NOLINT(misc-no-recursion)
    for ( auto const & child : this->children() ) {
        if ( this->scene() != nullptr ) {
            (void) this->_scene->remove( child );
        }

        (void) child->clear();
    }

    for ( auto const & component : this->_components ) {
        delete component.second();
    }

    return * this;
}

auto Self :: loadFrom ( json :: standard :: JsonObject const & json ) noexcept -> Self & {

    try {
        this->name() = json.getString ( Self :: nameKey );

    } catch ( KeyException const & ) {
        log :: info() << "Unnamed Entity in scene, assigning default name";

        static int nameCounter = 1;
        this->name() = "Unnamed Entity "_s + nameCounter ++;

    } catch ( TypeException const & typeException ) {
        log :: warn() << "Entity Has Name Field, format not ok : " << typeException.toString();
    }

    try {
        auto const & componentsArray = json.getArray ( Self :: componentsKey );
        for ( auto const & componentObject : componentsArray ) {

            try {
                auto const & componentJson = componentObject.getJson();

                try {
                    auto component = Type ( Component ) :: instantiate ( componentJson );

                    (void) this->_components.emplace (
                            reduceComponentTypeFlag ( component->type() ),
                            component.release()
                    );

                } catch ( Exception const & ) {
                    log :: warn() << "Component Could not be created from configuration, it will not be added to Entity";
                }

            } catch ( TypeException const & typeException ) {
                log :: warn() << "Component Element in the Entity's Components array is not formatted properly : " << typeException.toString();
            }
        }

    } catch ( KeyException const & ) {
    } catch ( TypeException const & typeException ) {
        log :: warn() << "Key for components - '" << Self :: componentsKey << "' found, format not ok : " << typeException.toString();
    }

    return * this;
}

auto Self :: dumpTo ( json :: standard :: JsonObject & json ) noexcept -> Self const & { // NOLINT(misc-no-recursion)

    json :: standard :: JsonArray componentsArray;
    for ( auto const & component : this->_components ) {

        json :: standard :: JsonObject componentObject;
        (void) component.second()->dumpTo ( componentObject );
        (void) componentsArray.add ( componentObject );
    }

    json :: standard :: JsonArray childrenArray;
    for ( auto const & child : this->children() ) {

        json :: standard :: JsonObject childObject;
        (void) child->dumpTo ( childObject );
        (void) childrenArray.add ( childObject );
    }

    (void) json
        .put ( Self :: nameKey, this->name() )
        .put ( Self :: typeKey, this->className() )
        .put ( Self :: componentsKey, componentsArray )
        .put ( Self :: childrenKey, childrenArray );

    return * this;
}

auto Self :: instantiateByClassName ( cds :: String const & string ) noexcept (false) -> cds :: UniquePointer < Self > {
    throw Exception ( "Unknown Entity Class Name '" + string + "'" );
}

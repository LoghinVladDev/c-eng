//
// Created by loghin on 4/6/22.
//

#include "Entity.hpp"
#include <scene/Scene.hpp>
#include <Logger.hpp>
#include <scene/ECM/Component.hpp>
#include <scene/ECM/components/transform/Transform.hpp>
#include <scene/specializedObjects/gameObjects/GameObject.hpp>

using namespace cds;
using namespace engine;

#define C_ENG_MAP_START CLASS ( Entity, ENGINE_PARENT ( EngineObject ) )
#include <ObjectMapping.hpp>

auto Self :: add ( Type ( Entity ) * pEntity ) noexcept -> Self & {

    pEntity->_parent = this;
    this->_children.add ( pEntity );

    return * this;
}

auto Self :: remove ( Type ( Entity ) * pEntity ) noexcept -> Self & {

    pEntity->_parent = nullptr;

    for ( auto iterator = this->_children.begin(), end = this->_children.end(); iterator != end; ++ iterator ) {
        if ( iterator->get() == pEntity ) {
            (void) this->_children.remove ( iterator );
            return * this;
        }
    }

    return * this;
}

Self :: Constructor ( Self const & entity ) noexcept {

    for ( auto const & component : entity._components ) {
        (void) this->Self :: add ( component.second()->copy() );
    }
}

Self :: Constructor ( Self && entity ) noexcept :
        _parent ( cds :: exchange ( entity._parent, nullptr ) ),
        _children ( std :: move ( entity._children ) ),
        _components ( std :: move ( entity._components ) ),
        _transform ( cds :: exchange ( entity._transform, nullptr ) ),
        _eventAdapter ( cds :: exchange ( entity._eventAdapter, nullptr ) ) {

    for ( auto & component : this->_components ) {
        component.second()->_entity = this;
    }
}

auto Self :: operator = ( Self const & entity ) noexcept -> Self & {
    if ( this == & entity ) {
        return * this;
    }

    (void) this->clear();

    for ( auto const & component : entity._components ) {
        (void) this->add ( component.second()->copy() );
    }

    return * this;
}

auto Self :: operator = ( Self && entity ) noexcept -> Self & {
    if ( this == & entity ) {
        return * this;
    }

    (void) this->clear();

    this->_parent               = cds :: exchange ( entity._parent, nullptr );
    this->_children             = std :: move ( entity._children );
    this->_components           = std :: move ( entity._components );
    this->_transform            = cds :: exchange ( entity._transform, nullptr );
    this->_eventAdapter         = cds :: exchange ( entity._eventAdapter, nullptr );

    for ( auto & component : this->_components ) {
        component.second()->_entity = this;
    }

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
        component.second()->_entity = nullptr;
        delete component.second();
    }

    this->_children.clear();
    this->_components.clear();

    this->_transform            = nullptr;
    this->_eventAdapter         = nullptr;

    return * this;
}

auto Self :: loadFrom ( json :: standard :: JsonObject const & json ) noexcept -> Self & {

    try {
        this->name() = json.getString ( Self :: nameKey );

    } catch ( KeyException const & ) {
        log :: info() << "Unnamed Entity in scene, assigning default name";
        this->name() = this->scene()->generateUnusedEntityName();

    } catch ( TypeException const & typeException ) {
        log :: warn() << "Entity Has Name Field, format not ok : " << typeException.toString();
    }

    try {
        auto const & componentsArray = json.getArray ( Self :: componentsKey );
        for ( auto const & componentObject : componentsArray ) {

            try {
                auto const & componentJson = componentObject.getJson();

                try {
                    (void) this->add ( Type ( Component ) :: instantiate ( componentJson ).release() );

                } catch ( Exception const & ) {
                    log :: warn() << "Component Could not be created from configuration, it will not be added to Entity";
                }

            } catch ( TypeException const & typeException ) {
                log :: warn() << "Component Element in the Entity's Components array is not formatted properly : " << typeException.toString();
            }
        }

    } catch ( KeyException const & ) {
        /* do nothing */
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

auto Self :: add ( Type ( Component ) * pComponent ) noexcept -> Self & {

    if ( this->_transform == nullptr ) {
        this->_transform = pComponent->cast < ComponentTypeFlagTransform > ();
    }

    if ( this->_eventAdapter == nullptr ) {
        this->_eventAdapter = pComponent->cast < ComponentTypeFlagEntityEventAdapter > ();
    }

    pComponent->_entity = this;

    (void) this->_components.emplace (
            reduceComponentTypeFlag ( pComponent->type() ),
            pComponent
    );

    return * this;
}

auto Self :: remove ( Type ( Component ) * pComponent ) noexcept -> Self & {

    if ( pComponent->type() == ComponentTypeFlagTransform ) {
        this->_transform = nullptr;
    }

    pComponent->_entity = nullptr;

    this->_components.remove ( reduceComponentTypeFlag ( pComponent->type() ) );
    return * this;
}

template < typename T >
static inline auto tryInstantiate ( Type ( Entity ) * & pEntity, String const & className ) noexcept -> bool {
    pEntity = new T ();
    if ( pEntity->className() == className ) {
        return true;
    }

    delete pEntity;
    return false;
}

auto Self :: instantiateByClassName ( String const & className ) noexcept (false) -> cds :: UniquePointer < Self > {

    Self * pEntity = nullptr;

    if ( tryInstantiate < Type ( GameObject ) > ( pEntity, className ) ) {
        return pEntity;
    }

    throw Exception ( "Unknown Entity Class Name '" + className + "'" );
}

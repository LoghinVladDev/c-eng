//
// Created by loghin on 4/30/22.
//

#include "GameObject.hpp"
#include <scene/ECM/Component.hpp>

using namespace cds;
using namespace engine;

#define C_ENG_MAP_START CLASS ( GameObject, ENGINE_PARENT ( Entity ) )
#include <ObjectMapping.hpp>

auto Self :: copy () const noexcept -> Self * {
    return new Self ( * this );
}

auto Self :: toString () const noexcept -> String {

    return __C_ENG_STRINGIFY ( Self ) +
            "{ entity = "_s     + this->Parent :: toString() +
            ", mesh = "         + engine :: toString ( this->_mesh ) +
            ", meshRenderer = " + engine :: toString ( this->_meshRenderer ) +
            " }";
}

auto Self :: clear () noexcept -> Self & {
    this->Parent :: clear();

    this->_meshRenderer = nullptr;
    this->_mesh         = nullptr;

    return * this;
}

auto Self :: add ( Type ( Component ) * pComponent ) noexcept -> Self & {

    if ( this->_mesh == nullptr ) {
        this->_mesh         = reinterpret_cast < Type ( Mesh ) * >          ( pComponent->cast < ComponentTypeFlagMesh > () );
    }

    if ( this->_meshRenderer == nullptr ) {
        this->_meshRenderer = reinterpret_cast < Type ( MeshRenderer ) * >  ( pComponent->cast < ComponentTypeFlagMeshRenderer > () );
    }

    (void) this->Parent :: add ( pComponent );
    return * this;
}

auto Self :: remove ( Type ( Component ) * pComponent ) noexcept -> Self & {

    if ( pComponent->type() == ComponentTypeFlagMesh ) {
        this->_mesh = nullptr;
    }

    if ( pComponent->type() == ComponentTypeFlagMeshRenderer ) {
        this->_meshRenderer = nullptr;
    }

    (void) this->Parent :: add ( pComponent );
    return * this;
}

//
// Created by loghin on 04.03.2021.
//

#include "VEntity.h"

engine::VEntity::VEntity(const VEntity * pParent) noexcept : _pParentEntity(pParent) {
    if ( pParent != nullptr )
        pParent->addChild(this);
}

auto engine::VEntity::siblings() const noexcept -> Array< VEntity * > {
    if ( this->_pParentEntity == nullptr )
        return { };

    decltype ( this->_children ) parentChildren;

    for ( auto * pChild : this->_pParentEntity->_children )
        if ( pChild != this )
            parentChildren.pushBack( pChild );

    return parentChildren;
}

auto engine::VEntity::addComponent(VComponent * pComponent) noexcept -> void {
    this->_components.pushBack(pComponent);
    pComponent->_pParentEntity = this;
}

auto engine::VEntity::addChild(VEntity * pChild) const noexcept -> void {
    this->_children.pushBack(pChild);
    pChild->_pParentEntity = this;
}

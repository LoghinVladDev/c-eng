//
// Created by loghin on 04.03.2021.
//

#include "VComponent.h"
#include <gobj/ecm/VEntity.h>

uint64 engine::VComponent::_IDCounter = 1llu;

auto engine::VComponent::toString() const noexcept -> String {
    return String().append("VComponent { id = ").append(this->_ID).append(" }");
}

engine::VComponent::VComponent(VEntity * pParentEntity) noexcept : _pParentEntity(pParentEntity) {
    if ( pParentEntity != nullptr )
        pParentEntity->addComponent(this);
}

void * engine::VComponent::operator new(std::size_t s) noexcept(false) {
    return ::operator new(s);
}

void engine::VComponent::operator delete(void * pToDelete) noexcept(false) {
    auto self = reinterpret_cast < VComponent * > (pToDelete);
    if ( self->_pParentEntity == nullptr )
        throw VComponent::RootComponentDeleteException();

    if ( self->_pParentEntity != nullptr )
        const_cast < VEntity * > ( self->_pParentEntity )->removeComponent( self );

    ::operator delete(pToDelete);
}


//
// Created by loghin on 04.03.2021.
//

#include "VComponent.h"
#include <gobj/ecm/VEntity.h>

auto engine::VComponent::toString() const noexcept -> String {
    return String() + "<VComponent : " + reinterpret_cast < Size > ( this ) + "(dec)>";
}

engine::VComponent::VComponent(VEntity * pParentEntity) noexcept : _pParentEntity(pParentEntity) {
    if ( pParentEntity != nullptr )
        pParentEntity->addComponent(this);
}

void * engine::VComponent::operator new(std::size_t s) noexcept(false) {
    return ::operator new(s);
}

void engine::VComponent::operator delete(void * pToDelete) noexcept(false) {
    if ( reinterpret_cast < VComponent * > (pToDelete)->_pParentEntity == nullptr )
        throw VComponent::RootComponentDeleteException();

    ::operator delete(pToDelete);
}
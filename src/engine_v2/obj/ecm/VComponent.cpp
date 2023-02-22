//
// Created by loghin on 04.03.2021.
//

#include "VComponent.hpp"
#include <src/engine/obj/ecm/VEntity.hpp>

uint64 engine::VComponent::_IDCounter = 1llu;

auto engine::VComponent::toString() const noexcept -> String {
    return String().append("VComponent { id = ").append(this->_ID).append(" }");
}

engine::VComponent::VComponent(Tags tags, VEntity * pParentEntity) noexcept : _pParentEntity(pParentEntity), _tags(tags) {
    if ( pParentEntity != nullptr )
        pParentEntity->add(this);
}

engine::VComponent::VComponent(Tags tags, uint64 ignoredIDConstructor __CDS_MaybeUnused) noexcept : _pParentEntity(nullptr), _tags(tags), _ID(UINT64_MAX) {

}

void * engine::VComponent::operator new(std::size_t s) noexcept(false) {
    return ::operator new(s);
}

void engine::VComponent::operator delete(void * pToDelete) noexcept(false) {
    if ( pToDelete == nullptr ) return;

    auto self = reinterpret_cast < VComponent * > (pToDelete);
    if ( self->_pParentEntity != nullptr && self->_pParentEntity->parentPtr() == nullptr )
        throw VComponent::RootComponentDeleteException();

    if ( self->_pParentEntity != nullptr )
        const_cast < VEntity * > ( self->_pParentEntity )->remove( self );

    ::operator delete(pToDelete);
}

auto engine::VComponent::operator==(VComponent const & o) const noexcept -> bool {
    if (this == & o) return true;
    return this->_ID == o._ID;
}

auto engine::VComponent::equals(Object const & o) const noexcept -> bool {
    if (this == & o) return true;
    auto p = dynamic_cast < decltype (this) > (& o);
    if ( p == nullptr ) return false;

    return this->operator==(*p);
}
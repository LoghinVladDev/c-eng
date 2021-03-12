//
// Created by loghin on 04.03.2021.
//

#include "VEntity.h"

uint64 engine::VEntity::_IDCounter = 1llu;

#include <scene/VScene.h>

engine::VEntity::VEntity(VEntity const * pParent) noexcept : _pParentEntity(pParent) {
    pParent->add(this);
}

engine::VEntity::VEntity(VScene * pScene) noexcept : _pScene(pScene), _pParentEntity(nullptr) {
    pScene->add(this);
}

engine::VEntity::VEntity(uint64 ignoredIDConstructor) noexcept : _pParentEntity(nullptr), _pScene(nullptr), _ID(UINT64_MAX) {}

auto engine::VEntity::siblings() const noexcept -> Array< VEntity * > {
    if ( this->_pParentEntity == nullptr )
        return { };

    decltype ( this->_children ) parentChildren;

    for ( auto * pChild : this->_pParentEntity->_children )
        if ( pChild != this )
            parentChildren.pushBack( pChild );

    return parentChildren;
}

auto engine::VEntity::add(VComponent * pComponent) noexcept -> bool {
    if ( pComponent->hasTag(VComponent::DISTINCT) )
        for ( auto * p : this->_components )
            if ( p->hasTag(VComponent::DISTINCT) && p->className() == pComponent->className() )
                return false;

    this->_components.pushBack(pComponent);
    pComponent->_pParentEntity = this;

    if ( this->_pScene != nullptr )
        this->_pScene->index(pComponent);

    return true;
}

auto engine::VEntity::add(VEntity * pChild) const noexcept -> bool {
    this->_children.pushBack(pChild);
    pChild->_pParentEntity = this;

    if ( pChild->_pScene != this->_pScene ) {
        if ( pChild->_pScene != nullptr )
            pChild->_pScene->unIndex(pChild);

        pChild->_pScene = this->_pScene;

        if ( this->_pScene != nullptr )
            this->_pScene->index(pChild, true);
    }

    return true;
}

auto engine::VEntity::toString() const noexcept -> String {
//    return String().append("VEntity { id = ").append(this->_ID).append(" }");
    String res;

    res.append("VEntity {\n\tid = ").append(this->_ID).append(",\n\tcomponents = [");
    if ( ! this->_components.empty() ) res.append("\n");
    for ( Index i = 0; auto & e : this->_components ) {
        res.append("\t\t").append(e->toString());
        if ( i + 1 < this->_components.size() ) res.append(",");
        res.append("\n");
    }

    if ( ! this->_components.empty() ) res.append("\t");

    res.append("],\n\tchildren = [");
    if ( ! this->_children.empty() ) res.append("\n");
    for ( Index i = 0; auto & c : this->_children ) {
        res.append("\t\t").append(c->toString());
        if ( i + 1 < this->_children.size() ) res.append(",");
        res.append("\n");
    }

    if ( ! this->_children.empty() ) res.append("\t");
    res.append("]\n}");
    return res;
}

engine::VEntity::~VEntity() noexcept {
    if ( this->_pScene != nullptr )
        this->_pScene->unIndex( this );

    for ( auto * p : this->_components ) {
        p->_pParentEntity = nullptr;
        delete p;
    }

    for ( auto * p : this->_children ) {
        p->_pParentEntity = nullptr;
        delete p;
    }

    this->_components.clear();
    this->_children.clear();
}

auto engine::VEntity::remove(VComponent * pComponent) noexcept -> bool {
    if ( this->_components.removeFirst(pComponent) ) {
        if ( this->_pScene != nullptr )
            this->_pScene->unIndex(pComponent);
        return true;
    }

    return false;
}

auto engine::VEntity::remove(VEntity * pChild) const noexcept -> bool {
    if ( this->_children.removeFirst(pChild) ) {
        if ( this->_pScene != nullptr )
            this->_pScene->unIndex(pChild, true);

        pChild->_pParentEntity = nullptr;
        pChild->_pScene = nullptr;
        return true;
    }

    return false;
}

auto engine::VEntity::getComponentByClassName(const VComponent::ClassName & className) noexcept -> VComponent * {
    VComponent * pComponent = nullptr;

    for ( auto * p : this->_components )
        if ( p->className() == className ) {
            if (p->hasTag(VComponent::DISTINCT) && pComponent != nullptr)
                return nullptr;
            else
                pComponent = p;
        }

    return pComponent;
}

auto engine::VEntity::getComponentByClassName(const VComponent::ClassName & className) const noexcept -> VComponent const * {
    VComponent const * pComponent = nullptr;

    for ( auto * p : this->_components )
        if ( p->className() == className ) {
            if (p->hasTag(VComponent::DISTINCT) && pComponent != nullptr)
                return nullptr;
            else
                pComponent = p;
        }

    return pComponent;
}

auto engine::VEntity::getComponentsByClassName(const VComponent::ClassName & className) noexcept -> Array < VComponent * > {
    Array < VComponent * > componentAddresses;

    for ( auto * p : this->_components )
        if ( p->className() == className )
            componentAddresses.pushBack(p);

    return componentAddresses;
}

auto engine::VEntity::getComponentsByClassName(const VComponent::ClassName & className) const noexcept -> Array< VComponent const * > {
    Array < VComponent const * > componentAddresses;

    for ( auto * p : this->_components )
        if ( p->className() == className )
            componentAddresses.pushBack(p);

    return componentAddresses;
}

void * engine::VEntity::operator new(std::size_t s) noexcept(false) {
    return ::operator new(s);
}

void engine::VEntity::operator delete(void * pToDelete) noexcept(false) {
    if ( pToDelete == nullptr ) return;

    auto self = reinterpret_cast< VEntity * > (pToDelete);

    if ( self->_pScene != nullptr ) {
        if ( self->_pParentEntity == nullptr ) {
            for ( auto & c : self->_children ) {
                self->remove(c);
                const_cast < VScene * > ( self->_pScene )->add(c);
            }
        } else {
            for ( auto & c : self->_children ) {
                self->remove(c);
                const_cast < VEntity * > (self->_pParentEntity)->add(c);
            }
        }
    }

    ::operator delete(pToDelete);
}
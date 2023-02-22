//
// Created by loghin on 04.03.2021.
//

#include "VGameObject.hpp"

uint64 engine::VGameObject::_IDCounter = 1llu;

const engine::VGameObject engine::VGameObject::EMPTY = engine::VGameObject(UINT64_MAX);

auto engine::VGameObject::add ( VComponent * pComponent ) noexcept -> bool {
    if ( VEntity::add(pComponent) ) {
//        if ( pComponent->className() == VTransform::EMPTY.className() )
//            this->_pTransform = dynamic_cast < VTransform * > (pComponent);
        if ( pComponent->className() == VMesh::EMPTY.className() )
            this->_pMesh = dynamic_cast < VMesh * > (pComponent);
        else if ( pComponent->className() == VMeshRenderer::EMPTY.className() )
            this->_pMeshRenderer = dynamic_cast < VMeshRenderer * > (pComponent);

        return true;
    }

    return false;
}

auto engine::VGameObject::remove ( VComponent * pComponent ) noexcept -> bool {
    if ( VEntity::remove(pComponent) ) {
        if ( pComponent->className() == VTransform().className() )
            this->_pTransform = nullptr;
        else if ( pComponent->className() == VMesh().className() )
            this->_pMesh = nullptr;
        else if ( pComponent->className() == VMeshRenderer().className() )
            this->_pMeshRenderer = nullptr;

        return true;
    }

    return false;
}

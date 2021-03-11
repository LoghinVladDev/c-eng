//
// Created by loghin on 04.03.2021.
//

#include "VGameObject.h"

auto engine::VGameObject::addComponent ( VComponent * pComponent ) noexcept -> bool {
    if ( VEntity::addComponent(pComponent) ) {
        if ( pComponent->className() == VTransform().className() )
            this->_pTransform = dynamic_cast < VTransform * > (pComponent);
        else if ( pComponent->className() == VMesh().className() )
            this->_pMesh = dynamic_cast < VMesh * > (pComponent);
        else if ( pComponent->className() == VMeshRenderer().className() )
            this->_pMeshRenderer = dynamic_cast < VMeshRenderer * > (pComponent);

        return true;
    }

    return false;
}

auto engine::VGameObject::removeComponent ( VComponent * pComponent ) noexcept -> bool {
    if ( VEntity::removeComponent(pComponent) ) {
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

//
// Created by loghin on 04.03.2021.
//

#include "VScene.h"

engine::VScene::~VScene() noexcept {
    for ( auto * p : this->_rootEntities )
        delete p;

    this->_rootEntities.clear();
}

auto engine::VScene::setEntitySceneRoot (engine::VEntity * pEntity, engine::VScene * pScene) noexcept -> void {
    pEntity->_pScene = pScene;

    pScene != nullptr ? this->index(pEntity) : this->unIndex(pEntity);

    for ( auto & e : pEntity->children() )
        this->setEntitySceneRoot(e, pScene);
}

auto engine::VScene::index( VEntity * pEntity, bool recurseChildren ) const noexcept -> void {
    if ( ! this->_indexedEntities.containsKey( pEntity->ID() ) ) {
        this->_indexedEntities.emplace( pEntity->ID(), pEntity );

        for ( auto * c : pEntity->components() )
            this->index(c);
    }

    if ( recurseChildren )
        for ( auto * c : pEntity->children() )
            this->index(c, recurseChildren);
}

auto engine::VScene::index(VComponent * pComponent) const noexcept -> void {
    if ( ! this->_indexedComponents.containsKey(pComponent->ID()) )
        this->_indexedComponents.emplace( pComponent->ID(), pComponent );
}

auto engine::VScene::unIndex(VEntity * pEntity, bool recuseChildren) const noexcept -> void {
    this->_indexedEntities.remove(pEntity->ID());

    for ( auto * c : pEntity->components() )
        this->unIndex(c);

    if ( recuseChildren )
        for ( auto * c : pEntity->children() )
            this->unIndex(c, recuseChildren);
}

auto engine::VScene::unIndex(VComponent * pComponent) const noexcept -> void {
    this->_indexedComponents.remove(pComponent->ID());
}

auto engine::VScene::add(VEntity * pEntity) noexcept -> bool {
    if ( pEntity->_pScene != nullptr || pEntity->_pParentEntity != nullptr ) return false;

    this->_rootEntities.pushBack(pEntity);
    this->setEntitySceneRoot(pEntity, this);
    return true;
}

auto engine::VScene::remove(VEntity * pEntity) noexcept -> bool {
    if ( this->_rootEntities.removeFirst(pEntity) ) {
        this->setEntitySceneRoot(pEntity, nullptr);
        return true;
    }
    return false;
}

auto static entityTreeParse ( engine::VEntity * pEntity, uint64 ID ) noexcept -> engine::VEntity * {
    if ( pEntity->ID() == ID ) return pEntity;

    for ( auto & e : pEntity->children() ) {
        auto p = entityTreeParse(e, ID);
        if ( p != nullptr ) return p;
    }

    return nullptr;
}


auto static entityTreeParseComponent ( engine::VEntity * pEntity, uint64 ID ) noexcept -> engine::VComponent * {
    for ( auto & c : pEntity->components() )
        if ( c->ID() == ID ) return c;

    for ( auto & e : pEntity->children() ) {
        auto p = entityTreeParseComponent(e, ID);
        if ( p != nullptr ) return p;
    }

    return nullptr;
}

auto engine::VScene::getEntityByID(uint64 ID) noexcept -> VEntity * {
    auto indexedEntity = this->_indexedEntities.find(ID);
    if ( indexedEntity.hasValue() ) return indexedEntity->get();

    for ( auto & e : this->_rootEntities ) {
        auto p = entityTreeParse(e, ID);
        if ( p != nullptr ) return p;
    }

    return nullptr;
}

auto engine::VScene::getEntityByID(uint64 ID) const noexcept -> const VEntity * {
    auto indexedEntity = this->_indexedEntities.find(ID);
    if ( indexedEntity.hasValue() ) return indexedEntity->get();

    for ( auto & e : this->_rootEntities ) {
        const auto p = entityTreeParse(e, ID);
        if ( p != nullptr ) return p;
    }

    return nullptr;
}

auto engine::VScene::getComponentByID(uint64 ID) noexcept -> VComponent * {
    auto indexedComponent = this->_indexedComponents.find(ID);
    if ( indexedComponent.hasValue() ) return indexedComponent->get();

    for ( auto & e : this->_rootEntities ) {
        auto p = entityTreeParseComponent(e, ID);
        if ( p != nullptr ) return p;
    }

    return nullptr;
}

auto engine::VScene::getComponentByID(uint64 ID) const noexcept -> VComponent const * {
    auto indexedComponent = this->_indexedComponents.find(ID);
    if ( indexedComponent.hasValue() ) return indexedComponent->get();

    for ( auto & e : this->_rootEntities ) {
        const auto p = entityTreeParseComponent(e, ID);
        if ( p != nullptr ) return p;
    }

    return nullptr;
}

auto engine::VScene::rootEntities() const noexcept -> Array < const VEntity * > {
    Array < VEntity const * > entities;

    for ( auto & p : this->_rootEntities )
        entities.pushBack(p);

    return entities;
}

auto engine::VScene::toString() const noexcept -> String {
    String result;

    result.append("VScene { \n")
        .append("\trootEntities = [");

    if ( ! this->_rootEntities.empty() ) result.append("\n");

    for ( auto & e : this->_rootEntities )
        result.append("\t\t").append(e->toString()).append("\n");

    if ( ! this->_rootEntities.empty() ) result.append("\t");
    result.append("],\n");

    return result
        .append("\tindexedEntities = ").append(this->_indexedEntities.toString()).append("\n")
        .append("\tindexedComponents = ").append(this->_indexedComponents.toString()).append("\n}");
}

auto static gatherEntities ( engine::VEntity * pEntity ) noexcept -> Array < engine::VEntity * > {
    Array < engine::VEntity * > entityAddressArray;
    entityAddressArray.pushBack(pEntity);

    for ( auto * pSubEntity : pEntity->children() ) {
        if ( pSubEntity->children().empty()) {
            entityAddressArray.pushBack(pSubEntity);
            continue;
        }

        auto subEntityChildren = gatherEntities(pSubEntity);

        for ( auto * pSubChildEntity : subEntityChildren )
            entityAddressArray.pushBack(pSubChildEntity);
    }

    return entityAddressArray;
}

auto static gatherEntities ( engine::VEntity const * pEntity ) noexcept -> Array < engine::VEntity const * > {
    Array < engine::VEntity const * > entityAddressArray;
    entityAddressArray.pushBack(pEntity);

    for ( auto * pSubEntity : pEntity->children() ) {
        if ( pSubEntity->children().empty()) {
            entityAddressArray.pushBack(pSubEntity);
            continue;
        }

        auto subEntityChildren = gatherEntities(pSubEntity);

        for ( auto * pSubChildEntity : subEntityChildren )
            entityAddressArray.pushBack(pSubChildEntity);
    }

    return entityAddressArray;
}

auto engine::VScene::allEntities() noexcept -> Array<VEntity *> {
    Array < engine::VEntity * > entityAddressArray;

    for ( auto * pEntity : this->_rootEntities ) {
        if ( pEntity->children().empty()) {
            entityAddressArray.pushBack(pEntity);
            continue;
        }

        auto subEntityChildren = gatherEntities(pEntity);

        for ( auto * pSubEntity : subEntityChildren )
            entityAddressArray.pushBack(pSubEntity);
    }

    return entityAddressArray;
}

auto engine::VScene::allEntities() const noexcept -> Array<VEntity const *> {
    Array < engine::VEntity const * > entityAddressArray;

    for ( auto * pEntity : this->_rootEntities ) {
        if ( pEntity->children().empty()) {
            entityAddressArray.pushBack(pEntity);
            continue;
        }

        auto subEntityChildren = gatherEntities(pEntity);

        for ( auto * pSubEntity : subEntityChildren )
            entityAddressArray.pushBack(pSubEntity);
    }

    return entityAddressArray;
}

auto static gatherEntitiesWithComponentsOfClass ( engine::VEntity * pEntity, String const & className ) noexcept -> Array < engine::VEntity * > {
    Array < engine::VEntity * > entityAddressArray;

    for ( auto * pSubEntity : pEntity->children() ) {
#if defined(__cpp_concepts) && !defined(_MSC_VER)
        if (pSubEntity->components().any([&className](auto & c)noexcept -> bool{return c->className() == className;}) )
            entityAddressArray.pushBack(pSubEntity);
#else
        for ( auto * pComponent : pSubEntity->components() )
            if ( pComponent->className () == className ) {
                entityAddressArray.pushBack ( pSubEntity );
                break;
            }

#endif

        if (pSubEntity->children().empty())
            continue;

        auto subEntityChildren = gatherEntities(pSubEntity);

        for ( auto * pSubChildEntity : subEntityChildren )
            entityAddressArray.pushBack(pSubChildEntity);
    }

    return entityAddressArray;
}

auto engine::VScene::entitiesWithComponentsOfClass(String const & className) noexcept -> Array<VEntity *> {
    Array < engine::VEntity * > entityAddressArray;

    for ( auto * pEntity : this->_rootEntities ) {
#if defined(__cpp_concepts) && !defined(_MSC_VER)
        if (pEntity->components().any([&className](auto & c)noexcept -> bool{return c->className() == className;}) )
            entityAddressArray.pushBack(pEntity);
#else
        for ( auto * pComponent : pEntity->components() )
            if ( pComponent->className () == className ) {
                entityAddressArray.pushBack ( pEntity );
                break;
            }
#endif

        if (pEntity->children().empty())
            continue;

        auto subEntityChildren = gatherEntitiesWithComponentsOfClass(pEntity, className);

        for ( auto * pSubEntity : subEntityChildren )
            entityAddressArray.pushBack(pSubEntity);
    }

    return entityAddressArray;
}

auto static gatherEntitiesWithComponentsOfClass ( engine::VEntity const * pEntity, String const & className ) noexcept -> Array < engine::VEntity const * > {
    Array < engine::VEntity const * > entityAddressArray;

//    if ( pEntity->components().any([&className](auto & c)noexcept -> bool{return c->className() == className; }))
//        entityAddressArray.pushBack(pEntity);
#if defined(__cpp_concepts) && !defined(_MSC_VER)
    if (pEntity->components().any([&className](auto & c)noexcept -> bool{return c->className() == className;}) )
            entityAddressArray.pushBack(pEntity);
#else
    for ( auto * pComponent : pEntity->components() )
        if ( pComponent->className () == className ) {
            entityAddressArray.pushBack ( pEntity );
            break;
        }
#endif

    for ( auto * pSubEntity : pEntity->children() ) {
//        if (
//                pSubEntity->children().empty() &&
//                pSubEntity->components().any([&className](auto & c)noexcept -> bool{return c->className() == className;})
//        ) {
//            entityAddressArray.pushBack(pEntity);
//            continue;
//        }
#if defined(__cpp_concepts) && !defined(_MSC_VER)
        if (pSubEntity->components().any([&className](auto & c)noexcept -> bool{return c->className() == className;}) )
            entityAddressArray.pushBack(pSubEntity);
#else
        for ( auto * pComponent : pSubEntity->components() )
            if ( pComponent->className () == className ) {
                entityAddressArray.pushBack ( pSubEntity );
                break;
            }
#endif
        if ( pSubEntity->children().empty() )
            continue;

        auto subEntityChildren = gatherEntities(pSubEntity);

        for ( auto * pSubChildEntity : subEntityChildren )
            entityAddressArray.pushBack(pSubChildEntity);
    }

    return entityAddressArray;
}

auto engine::VScene::entitiesWithComponentsOfClass(String const & className) const noexcept -> Array<VEntity const *> {
    Array < engine::VEntity const * > entityAddressArray;

    for ( auto * pEntity : this->_rootEntities ) {
//        if (
//                pEntity->children().empty() &&
//                pEntity->components().any([&className](auto & c)noexcept -> bool{return c->className() == className;})
//        ) {
//            entityAddressArray.pushBack(pEntity);
//            continue;
//        }
#if defined(__cpp_concepts) && !defined(_MSC_VER)
        if (pEntity->components().any([&className](auto & c)noexcept -> bool{return c->className() == className;}) )
            entityAddressArray.pushBack(pEntity);
#else
        for ( auto * pComponent : pEntity->components() )
            if ( pComponent->className () == className ) {
                entityAddressArray.pushBack ( pEntity );
                break;
            }
#endif
        if ( pEntity->children().empty() )
            continue;

        auto subEntityChildren = gatherEntitiesWithComponentsOfClass(pEntity, className);

        for ( auto * pSubEntity : subEntityChildren )
            entityAddressArray.pushBack(pSubEntity);
    }

    return entityAddressArray;
}

auto static gatherComponentsFromChildrenByClass ( engine::VEntity * pEntity, String const & className ) noexcept -> Array < engine::VComponent * > {
    Array < engine::VComponent * > componentAddressArray;

    for ( auto * pChildEntity: pEntity->children() ) {
        for ( auto * pComponent : pChildEntity->components() )
            if ( pComponent->className() == className ) componentAddressArray.pushBack(pComponent);

        if ( ! pEntity->children().empty() ) {
            auto componentsOfChildren = gatherComponentsFromChildrenByClass( pChildEntity, className );
            for ( auto * pComponent : componentsOfChildren )
                componentAddressArray.pushBack(pComponent );
        }
    }

    return componentAddressArray;
}

auto engine::VScene::componentsOfClass(const String & className) noexcept -> Array<VComponent *> {
    Array < VComponent * > componentAddressArray;

    for ( auto * pEntity : this->_rootEntities ) {
        for ( auto * pComponent : pEntity->components() )
            if ( pComponent->className() == className ) componentAddressArray.pushBack(pComponent);

        if ( ! pEntity->children().empty() ) {
            auto componentsOfChildren = gatherComponentsFromChildrenByClass (pEntity, className);
            for ( auto * pComponent : componentsOfChildren )
                componentAddressArray.pushBack(pComponent );
        }
    }

    return componentAddressArray;
}

auto static gatherComponentsFromChildrenByClass ( engine::VEntity const * pEntity, String const & className ) noexcept -> Array < engine::VComponent const * > {
    Array < engine::VComponent const * > componentAddressArray;

    for ( auto * pChildEntity: pEntity->children() ) {
        for ( auto * pComponent : pChildEntity->components() )
            if ( pComponent->className() == className ) componentAddressArray.pushBack(pComponent);

        if ( ! pEntity->children().empty() ) {
            auto componentsOfChildren = gatherComponentsFromChildrenByClass( pChildEntity, className );
            for ( auto * pComponent : componentsOfChildren )
                componentAddressArray.pushBack(pComponent );
        }
    }

    return componentAddressArray;
}

auto engine::VScene::componentsOfClass(const String & className) const noexcept -> Array<VComponent const *> {
    Array < VComponent const * > componentAddressArray;

    for ( auto * pEntity : this->_rootEntities ) {
        for ( auto * pComponent : pEntity->components() )
            if ( pComponent->className() == className ) componentAddressArray.pushBack(pComponent);

        if ( ! pEntity->children().empty() ) {
            auto componentsOfChildren = gatherComponentsFromChildrenByClass (pEntity, className);
            for ( auto * pComponent : componentsOfChildren )
                componentAddressArray.pushBack(pComponent );
        }
    }

    return componentAddressArray;
}

auto static gatherEntitiesByClassName( engine::VEntity * pEntity, String const & className ) noexcept -> Array < engine::VEntity * > {
    Array < engine::VEntity * > entityAddressArray;

    for ( auto * pSubEntity : pEntity->children() ) {
        if ( pSubEntity->className() == className )
            entityAddressArray.pushBack(pSubEntity);

        if ( ! pSubEntity->children().empty() ) {
            auto children = gatherEntitiesByClassName ( pSubEntity, className );
            for ( auto * pChild : children )
                entityAddressArray.pushBack(pChild);
        }
    }

    return entityAddressArray;
}

auto engine::VScene::entitiesOfClass(const String & className) noexcept -> Array<VEntity *> {
    Array < VEntity * > entityAddressArray;

    for ( auto * pEntity : this->_rootEntities ) {
        if ( pEntity->className() == className )
            entityAddressArray.pushBack(pEntity);

        if ( ! pEntity->children().empty() ) {
            auto children = gatherEntitiesByClassName ( pEntity, className );
            for ( auto * pChild : children )
                entityAddressArray.pushBack(pChild);
        }
    }

    return entityAddressArray;
}

auto engine::VScene::getGameObjectByName(const String & name) noexcept -> VGameObject * {
    auto gameObjects = this->entitiesOfClass("VGameObject");
    for ( auto * o : gameObjects ) {
        auto pGameObject = dynamic_cast < VGameObject * > (o);

        if ( pGameObject->getName() == name ) return pGameObject;
    }

    return nullptr;
}
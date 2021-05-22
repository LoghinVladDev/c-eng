//
// Created by loghin on 04.03.2021.
//

#include "VScene.hpp"

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

auto engine::VScene::setActiveCamera(VCamera * pCamera) noexcept -> bool {
    if ( ! this->_rootEntities.contains( pCamera ) )
        if ( ! this->add(pCamera) ) return false;

    this->_activeCamera = pCamera;
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

auto engine::VScene::locationInScene(VEntity * pEntity) const noexcept -> glm::vec3 {
    VTransform * pTransform = nullptr;
    if ( pEntity->className() == "VGameObject" )
        pTransform = ((VGameObject *)pEntity)->transform();
    else {
        pEntity->components().forEach([& pTransform](VComponent * pComp) -> void {
            if ( pComp->className() == "VTransform" ) pTransform = (VTransform *) pComp;
        });
    }

    if ( pEntity->parentPtr() == nullptr )
        return pTransform == nullptr ? glm::vec3(0.0f, 0.0f, 0.0f) : pTransform->location();

    return pTransform == nullptr ? glm::vec3(0.0f, 0.0f, 0.0f) : pTransform->location() + this->locationInScene(const_cast<VEntity *>(pEntity->_pParentEntity));
}

auto engine::VScene::transformInScene(VEntity * pEntity) const noexcept -> VTransform {
    VTransform * pTransform = nullptr;
    if ( pEntity->className() == "VGameObject" )
        pTransform = ((VGameObject *)pEntity)->transform();
    else
        pEntity->components().forEach([ & pTransform ](VComponent * pComponent) -> void { if ( pComponent->className() == "VTransform" ) pTransform = (VTransform *) pComponent; });

    if ( pEntity->parentPtr() == nullptr ) {
        return pTransform == nullptr ? VTransform() : ( * pTransform );
    }

    VTransform result = pTransform == nullptr ? VTransform() : ( * pTransform );
    auto parentTransform = transformInScene(const_cast < VEntity * > (pEntity->parentPtr()));


    //    result.location() += parentTransform.location();

    result.rotation() += parentTransform.rotation();

//    result.location().x += parentTransform.location().x;
//    result.location().y += parentTransform.location().y;
//   result.location().z += parentTransform.location().z;

    float xyDist = std::sqrt ( result.location().x * result.location().x + result.location().y * result.location().y );
    float zxDist = std::sqrt ( result.location().x * result.location().x + result.location().z * result.location().z );
    float yzDist = std::sqrt ( result.location().y * result.location().y + result.location().z * result.location().z );
//
//    result.location().x

//    result.location().x = parentTransform.location().x +
//            std::sin ( glm::radians(parentTransform.rotation().yaw()) ) * zxDist * std::cos ( glm::radians(parentTransform.rotation().pitch()) );
//
//    result.location().y = parentTransform.location().y +
//            std::sin ( glm::radians(parentTransform.rotation().pitch()) ) * xyDist * std::cos ( glm::radians(parentTransform.rotation().roll()) );

//    result.location().z = parentTransform.location().z +
//            std::sin ( glm::radians(parentTransform.rotation().roll()) ) * yzDist * std::cos ( glm::radians(parentTransform.rotation().yaw()) );

//    auto & r = result;
    auto cL = result.location();
    auto & l = result.location();
    auto & r = result.rotation();

    auto & pL = parentTransform.location();
    auto & pR = parentTransform.rotation();

    auto & c = cosf;
    auto & s = sinf;

    auto u = glm::radians(pR.pitch());
    auto v = glm::radians(pR.yaw());
    auto w = glm::radians(pR.roll());

//    float rm [3] [3] = {
//            { c(v) * c(w) , s(u) * s(v) * c(w) - c(u) * s(w) , s(u) * s(w) + c(u) * s(v) * c(w) },
//            { c(v) * s(w) , c(u) * c(w) + s(u) * s(v) * s(w) , c(u) * s(v) * s(w) - s(u) * c(w) },
//            { - s(v) , s(u) * c(v) , c(u) * c(v) }
//    };
//
//    l.z = cL.z * rm[0][0] + cL.x * rm[0][1] + cL.y * rm[0][2];
//    l.x = cL.z * rm[1][0] + cL.x * rm[1][1] + cL.y * rm[1][2];
//    l.y = cL.z * rm[2][0] + cL.x * rm[2][1] + cL.y * rm[2][2];


    auto m = glm::mat4(1.0f);
//    m[0][0] = 1.0f;
//    auto m = glm::mat4(glm::vec4(l.x, l.y, l.z, 1.0f));
//    m = glm::translate(m, glm::vec3(1.0f, 0.0f, 0.0f));

//    m = glm::translate(m, l);

    m = glm::rotate(m, u, glm::vec3(1.0f, 0.0f, 0.0f));
    m = glm::rotate(m, v, glm::vec3(0.0f, 1.0f, 0.0f));
    m = glm::rotate(m, w, glm::vec3(0.0f, 0.0f, 1.0f));
    m = glm::scale(m, l);

//    m = glm::translate(m, )

//    m = glm::translate(m, pL);

    l.x = (m[0].x + m[1].x + m[2].x) + pL.x;
    l.y = (m[0].y + m[1].y + m[2].y) + pL.y;
    l.z = (m[0].z + m[1].z + m[2].z) + pL.z;
//    l.x = m[0][0] * l.x + m[0][3];
//    l.y = m[1][1] * l.y + m[1][3];
//    l.z = m[2][2] * l.z + m[2][3];

    
    ///// DO NOT TOUCH, ONLY COMMENT
////    l.x = pL.x +
////            std::cos ( glm::radians( pR.yaw() ) ) * cL.x * std::cos ( glm::radians ( pR.roll() ) );
////
////    l.z = pL.z -
////           std::sin ( glm::radians( pR.yaw() ) ) * cL.x * std::cos ( glm::radians ( pR.roll() ) );

//    l.x = pL.x +
//            std::cos ( glm::radians( pR.yaw() ) ) * cL.x * std::cos ( glm::radians ( pR.roll() ) );
//
//    l.y = pL.y +
//            std::sin ( glm::radians( pR.roll() ) ) * cL.x; // + std::cos ( glm::radians( pR.pitch() ) )  * cL.x;
//
//    l.z = pL.z -
//           std::sin ( glm::radians( pR.yaw() ) ) * cL.x * std::cos ( glm::radians ( pR.roll() ) );

//    l.x = pL.x +
//            std::cos ( glm::radians( pR.yaw() ) ) * cL.x * std::cos ( glm::radians ( pR.roll() ) );
//            std::sin ( glm::radians( pR.pitch() ) ) * cL.x;

//    l.y = pL.y +
//            std::sin ( glm::radians(pR.pitch()) ) * cL.x * std::sin ( glm::radians ( pR.yaw() ) ) +
//            std::cos ( glm::radians(pR.pitch())) * cL.x * (std::sin (glm::radians(pR.roll())));
//            std::sin ( glm::radians(pR.pitch()) ) * cL.x * std::cos ( glm::radians ( pR.roll() ) );// * ( - std::cos (glm::radians(pR.roll()))); // * (-std::sin ( pR.roll() ));
//    l.y = pL.y -
//            std::sin ( glm::radians( pR.pitch() ) ) * cL.x;
//    l.z = pL.z +
//            std::sin ( glm::radians( pR.pitch() ) ) * cL.x; // + std::cos ( glm::radians( pR.pitch() ) ) * cL.x;

//    l.z = pL.z -
//           std::sin ( glm::radians( pR.yaw() ) ) * cL.x * std::cos ( glm::radians ( pR.pitch() ) ) * std::cos(glm::radians(pR.roll())) ;// * cL.x * std::cos ( glm::radians ( pR.pitch() ) );


//    l.z = pL.z -
//            std::sin ( glm::radians( pR.yaw() ) ) * cL.x * std::cos ( glm::radians(pR.pitch()) ) +
//            std::sin ( glm::radians( pR.pitch() ) ) * cL.x * ( std::sin ( glm::radians ( pR.roll() ) )) * std::cos(glm::radians(pR.yaw())) +
//            std::sin ( glm::radians( pR.pitch() ) ) * cL.x  * std::cos(glm::radians(pR.yaw())) * ( 1 - std::cos ( glm::radians ( pR.roll() ) ) ) +
//            std::sin ( glm::radians( pR.yaw() ) ) * cL.x * (1-std::cos ( glm::radians ( pR.roll() ) ));
//            std::sin ( glm::radians( pR.pitch() ) ) * cL.x * std::sin ( glm::radians( pR.roll() ) );
//            std::sin( glm::radians( pR.yaw() ) ) * cL.x * std::cos ( glm::radians ( pR.roll() ) );
//            std::sin ( glm::radians(pR.pitch()) ) * cL.x;
//            std::cos ( glm::radians ( pR.yaw() ) ) * cL.x * std::cos ( glm::radians ( pR.roll() ) );

//    l.x = pL.x +
//            std::cos ( glm::radians ( pR.roll() ) ) * l.x * std::cos ( glm::radians( pR.yaw() ) );

//    l.z = pL.z +
//            std::sin ( glm::radians( pR.yaw() ) ) * l.z * std::cos ( glm::radians( pR.pitch() ) );
//            std::cos( glm::radians ( pR.yaw() ) ) * zxDist * std::sin ( glm::radians(pR.roll()) );
//            std::cos ( glm::radians ( pR.roll() ) ) * xyDist * std::sin ( glm::radians(pR.roll()) );
//            std::cos ( glm::radians ( pR.roll() ) );
//            std::cos ( glm::radians(pR.pitch()) ) * xyDist;// + std::sin ( glm::radians(pR.yaw()) ) * zxDist;

    /// roll = z => xy
    /// pitch = x => yz
    /// yaw = y => zx
//    result.location().z = parentTransform.location().z +
//            std::sin ( glm::radians() )

//    result.location().x = parentTransform.location().x +
//            std::sin ( glm::radians() )
//        std::sin ( glm::radians(parentTransform.rotation().yaw()) ) * std::cos ( glm::radians(parentTransform.rotation().pitch()) ) * zxDist +
//        std::cos ( glm::radians(parentTransform.rotation().roll()) ) * std::sin ( glm::radians(parentTransform.rotation().pitch()) ) * xyDist;

//    result.location().z = parentTransform.location().z +
//        std::sin ( glm::radians(parentTransform.rotation().pitch()) ) * std::cos ( glm::radians(parentTransform.rotation().roll()) ) * yzDist +
//        std::cos ( glm::radians(parentTransform.rotation().yaw()) ) * std::sin ( glm::radians(parentTransform.rotation().roll()) ) * zxDist;
//
//    result.location().y = parentTransform.location().y +
//        std::sin ( glm::radians(parentTransform.rotation().roll()) ) * std::cos ( glm::radians(parentTransform.rotation().yaw()) ) * xyDist +
//        std::cos ( glm::radians(parentTransform.rotation().pitch()) ) * std::sin ( glm::radians(parentTransform.rotation().yaw()) ) * yzDist;
//        std::sin ( glm::radians(parentTransform.rotation().yaw()) ) * std::cos ( glm::radians(parentTransform.rotation().roll()) ) * (xzDist + xyDist);


//    result.location().y = parentTransform.location().y +
//        std::sin ( glm::radians(parentTransform.rotation().roll()) ) * std::cos ( glm::radians(parentTransform.rotation().yaw()) ) * xyDist;

//    result.location().z = parentTransform.location().z +
//        std::sin ( glm::radians(parentTransform.rotation().pitch()) ) * std::cos ( glm::radians(parentTransform.rotation().roll()) ) * xzDist;
//    result.location().z = parentTransform.location().z +
//        std::sin ( glm::radians(parentTransform.rotation().pitch()) ) * std::cos ( glm::radians(parentTransform.rotation().yaw()) ) * (xzDist + yzDist);

//        std::sin ( glm::radians(parentTransform.rotation().roll()) ) * xyDist;
//        std::sin ( glm::radians(parentTransform.rotation().roll()) ) * xyDist;
//        std::cos ( glm::radians(parentTransform.rotation().roll()) ) * xyDist;

//    result.location().z = parentTransform.location().z +
//        std::cos ( glm::radians(parentTransform.rotation().yaw()) ) * xzDist +
//        std::cos ( glm::radians(parentTransform.rotation().pitch()) ) * yzDist;

//    result.location().y = parentTransform.location().y +
//        std::sin ( glm::radians(parentTransform.rotation().pitch()) ) * yzDist +
//        std::cos ( glm::radians(parentTransform.rotation().roll()) ) * xyDist;


    /// pitch = z => xy
    /// roll = x => yz
    /// yaw = y => zx
//    result.location() = parentTransform.location() + glm::vec3 {
//        result.location().x * ( std::cos(glm::radians(result.rotation().roll())) + std::sin(glm::radians(result.rotation().yaw())) ),
//        result.location().y * ( std::cos(glm::radians(result.rotation().pitch())) + std::sin(glm::radians(result.rotation().roll())) ),
//        result.location().z * ( std::cos(glm::radians(result.rotation().yaw())) + std::sin(glm::radians(result.rotation().pitch())) )
//    };

    return result;
}
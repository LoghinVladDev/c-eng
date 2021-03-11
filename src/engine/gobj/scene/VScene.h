//
// Created by loghin on 04.03.2021.
//

#ifndef ENG1_VSCENE_H
#define ENG1_VSCENE_H

#include <CDS/Object>
#include <CDS/Array>
#include <CDS/HashMap>
#include <ecm/VEntity.h>
#include <VGameObject.h>

namespace engine {

    class VScene : public Object {
    private:
        auto setEntitySceneRoot ( VEntity *, VScene * ) noexcept -> void;
    private:
        //// private variables
        Array < VEntity * >                         _rootEntities;
        HashMap < uint64, VEntity * >    mutable    _indexedEntities;
        HashMap < uint64, VComponent * > mutable    _indexedComponents;

        //TODO : name indexing

        //// private functions

    public:
        //// public variables

        //// public functions
        VScene () noexcept = default;
        ~VScene() noexcept override;

        auto index ( VEntity *, bool = false ) const noexcept -> void;
        auto index ( VComponent * ) const noexcept -> void;
        auto index ( std::nullptr_t ) const noexcept -> void {}

        auto unIndex ( VEntity *, bool = false ) const noexcept -> void;
        auto unIndex ( VComponent * ) const noexcept -> void;
        auto unIndex ( std::nullptr_t ) const noexcept -> void {}

        auto add ( VEntity * ) noexcept -> bool;
        auto remove ( VEntity * ) noexcept -> bool;

        [[nodiscard]] auto getEntityByID ( uint64 ) noexcept -> VEntity *;
        [[nodiscard]] auto getEntityByID ( uint64 ) const noexcept -> VEntity const *;
        [[nodiscard]] auto getComponentByID ( uint64 ) noexcept -> VComponent *;
        [[nodiscard]] auto getComponentByID ( uint64 ) const noexcept -> VComponent const *;

        [[nodiscard]] auto rootEntities () noexcept -> Array < VEntity * > const & { return this->_rootEntities; }
        [[nodiscard]] auto rootEntities () const noexcept -> Array < VEntity const * >;

        [[nodiscard]] auto allEntities () noexcept -> Array < VEntity * >;
        [[nodiscard]] auto allEntities () const noexcept -> Array < VEntity const * >;

        [[nodiscard]] auto entitiesWithComponentsOfClass (String const & ) noexcept -> Array < VEntity * >;
        [[nodiscard]] auto entitiesWithComponentsOfClass (String const & ) const noexcept -> Array < VEntity const * >;

        // TODO: all components of class ?

        [[nodiscard]] auto componentsOfClass (String const &) noexcept -> Array < VComponent * >;
        [[nodiscard]] auto componentsOfClass (String const &) const noexcept -> Array < VComponent const * >;

        [[nodiscard]] auto entitiesOfClass (String const &) noexcept -> Array < VEntity * >;

        [[nodiscard]] auto getGameObjectByName (String const &) noexcept -> VGameObject *;

        [[nodiscard]] auto toString () const noexcept -> String override;
    };
}

#endif //ENG1_VSCENE_H

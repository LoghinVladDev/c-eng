//
// Created by loghin on 04.03.2021.
//

#ifndef ENG1_VSCENE_H
#define ENG1_VSCENE_H

#include <VObject.hpp>
#include <CDS/Array>
#include <CDS/HashMap>
#include <ecm/VEntity.hpp>
#include <VGameObject.hpp>
#include <VCamera.hpp>

namespace engine {

    class VScene : public VObject {
    private:
        auto setEntitySceneRoot ( VEntity *, VScene * ) noexcept -> void;
    private:
        //// private variables
        Array < VEntity * >                         _rootEntities;
        HashMap < uint64, VEntity * >    mutable    _indexedEntities;
        HashMap < uint64, VComponent * > mutable    _indexedComponents;

        VCamera                                   * _activeCamera {nullptr};

        bool                                        _periodicCachingEnabled      = false;
        bool                                        _immediateCachingEnabled     = false;

        uint32                                      _cacheReconstructionInterval = 512;

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

        auto setActiveCamera ( VCamera * ) noexcept -> bool;
        constexpr auto activeCamera () noexcept -> VCamera * { return this->_activeCamera; }
        constexpr auto activeCamera () const noexcept -> VCamera const * { return this->_activeCamera; }

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
        [[nodiscard]] auto copy () const noexcept -> VScene * override {
            return new VScene(* this);
        }

        [[nodiscard]] auto operator == (VScene const & o) const noexcept -> bool {
            if ( this == & o ) return true;

            return this->_activeCamera == o._activeCamera && this->_rootEntities == o._rootEntities;
        }

        [[nodiscard]] auto equals (Object const & o) const noexcept -> bool override {
            if ( this == & o ) return true;
            auto p = dynamic_cast < decltype (this) > (& o);
            if ( p == nullptr ) return false;

            return this->operator==(* p);
        }

        [[nodiscard]] auto hash () const noexcept -> Index override {
            return this->_rootEntities.hash();
        }

        [[nodiscard]] auto locationInScene (VEntity *) const noexcept -> glm::vec3;
        [[nodiscard]] auto transformInScene (VEntity *) const noexcept -> VTransform;

        auto clearCaches () noexcept -> void;
        auto reconstructCaches () noexcept -> void;

        constexpr auto setPeriodicCacheReconstructionInterval (uint32 value) noexcept -> void {
            this->_cacheReconstructionInterval = value;
        }

        constexpr auto setPeriodicCachingEnabled (bool toggle) noexcept -> void {
            this->_periodicCachingEnabled = toggle;
        }

        constexpr auto isPeriodicCachingEnabled () const noexcept -> bool {
            return this->_periodicCachingEnabled;
        }

        constexpr auto setImmediateCachingEnabled (bool toggle) noexcept -> void {
            this->_immediateCachingEnabled = toggle;
        }

        constexpr auto isImmediateCachingEnabled () const noexcept -> bool {
            return this->_immediateCachingEnabled;
        }
    };
}

#endif //ENG1_VSCENE_H

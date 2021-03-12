//
// Created by loghin on 04.03.2021.
//

#ifndef ENG1_VGAMEOBJECT_H
#define ENG1_VGAMEOBJECT_H

#include <gobj/ecm/VEntity.h>

#include <transform/VTransform.h>
#include <model/VMeshRenderer.h>
#include <model/VMesh.h>
#include <cmath>

namespace engine {

    class VGameObject: public VEntity {
    private:
        //// private variables
        VTransform      * _pTransform     {nullptr};
        VMesh           * _pMesh          {nullptr};
        VMeshRenderer   * _pMeshRenderer  {nullptr};

        String            _name;

        static uint64     _IDCounter; //NOLINT(bugprone-reserved-identifier)

        //// private functions
        static auto nextID () noexcept -> String { return String("GameObject").append( VGameObject::_IDCounter ++); }

        explicit VGameObject(uint64 ignoredID) noexcept : VEntity(ignoredID), _name("EMPTY") {}

    public:
        //// public variables
        const static VGameObject EMPTY;

        //// public functions
        explicit VGameObject ( std::nullptr_t = nullptr ) noexcept : VEntity(nullptr), _name(nextID()) { }
        explicit VGameObject ( VEntity * pParentEntity ) noexcept : VEntity(pParentEntity), _name(nextID()) { }
        explicit VGameObject ( VScene * pScene ) noexcept : VEntity ( pScene ), _name(nextID()) { }

        explicit VGameObject ( String const & name, std::nullptr_t = nullptr ) noexcept : VEntity(nullptr), _name(name) { }
        explicit VGameObject ( String const & name, VEntity * pParentEntity ) noexcept : VEntity(pParentEntity), _name(name) { }
        explicit VGameObject ( String const & name, VScene * pScene ) noexcept : VEntity(pScene), _name(name) { }

        virtual auto update (float deltaTime = 0.0f) noexcept -> void {
            //this -> _pTransform -> getScale().x *= 1.0f + deltaTime / 100.0f;
            //this -> _pTransform -> getScale().y *= 1.0f + deltaTime / 100.0f;
            // this -> _pTransform -> getScale().z *= 1.0f + deltaTime / 100.0f;

//            static float angle = 0.0f;
//            if ( this -> _name == "star" ){
//                this -> _pTransform -> getLocation().x = 0.0f + cosf ( angle ) * 1.0f;
//                this -> _pTransform -> getLocation().y = 0.0f + sinf ( angle ) * 1.0f;
//                angle += deltaTime;
//            }
        }

        [[nodiscard]] auto className () const noexcept -> ClassName override {
            return "VGameObject";
        }

        [[nodiscard]] auto toString () const noexcept -> String override {
            return String().append("VGameObject { \n")
                .append("\tname = ").append(this->_name).append("\n")
                .append("\tbase = ").append(VEntity::toString()).append("\n")
                .append("\ttransform address = ").append(reinterpret_cast<uint64>(this->_pTransform)).append("\n")
                .append("\tmesh address = ").append(reinterpret_cast<uint64>(this->_pMesh)).append("\n")
                .append("\tmeshRenderer address = ").append(reinterpret_cast<uint64>(this->_pMeshRenderer)).append("\n")
                .append("}");
        }

        auto setName ( String const & name ) noexcept -> void {
            this->_name = name;
        }

        inline auto getName() const noexcept -> String const & { return this->_name; }

        auto add ( VComponent * ) noexcept -> bool override;
        inline auto add ( VEntity * pEntity ) const noexcept -> bool override { return VEntity::add(pEntity); }
        inline auto add ( std::nullptr_t ) const noexcept -> bool override { return VEntity::add(nullptr); }

        auto remove ( VComponent * ) noexcept -> bool override;
        inline auto remove ( VEntity * pEntity ) const noexcept -> bool override { return VEntity::remove(pEntity); }
        inline auto remove ( std::nullptr_t ) const noexcept -> bool override { return VEntity::remove(nullptr); }

        constexpr auto transformPtr () noexcept -> VTransform * { return this->_pTransform; }
        constexpr auto transformPtr () const noexcept -> VTransform const * { return this->_pTransform; }

        constexpr auto meshPtr () noexcept -> VMesh * { return this->_pMesh; }
        constexpr auto meshPtr () const noexcept -> VMesh const * { return this->_pMesh; }

        constexpr auto meshRendererPtr () noexcept -> VMeshRenderer * { return this->_pMeshRenderer; }
        constexpr auto meshRendererPtr () const noexcept -> VMeshRenderer const * { return this->_pMeshRenderer; }
    };
}

#endif //ENG1_VGAMEOBJECT_H

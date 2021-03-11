//
// Created by loghin on 04.03.2021.
//

#ifndef ENG1_VGAMEOBJECT_H
#define ENG1_VGAMEOBJECT_H

#include <gobj/ecm/VEntity.h>

#include <transform/VTransform.h>
#include <model/VMeshRenderer.h>
#include <model/VMesh.h>

namespace engine {

    class VGameObject: public VEntity {
    private:
        //// private variables
        VTransform      * _pTransform     {nullptr};
        VMesh           * _pMesh          {nullptr};
        VMeshRenderer   * _pMeshRenderer  {nullptr};

        //// private functions

    public:
        //// public variables

        //// public functions
        [[nodiscard]] auto toString () const noexcept -> String override {
            return String().append("VGameObject { \n")
                .append("\tbase = ").append(VEntity::toString()).append("\n")
                .append("\ttransform address = ").append(reinterpret_cast<uint64>(this->_pTransform)).append("\n")
                .append("\tmesh address = ").append(reinterpret_cast<uint64>(this->_pMesh)).append("\n")
                .append("\tmeshRenderer address = ").append(reinterpret_cast<uint64>(this->_pMeshRenderer)).append("\n")
                .append("}");
        }

        auto addComponent ( VComponent * ) noexcept -> bool override;
        auto removeComponent ( VComponent * ) noexcept -> bool override;

        constexpr auto transformPtr () noexcept -> VTransform * { return this->_pTransform; }
        constexpr auto transformPtr () const noexcept -> VTransform const * { return this->_pTransform; }

        constexpr auto meshPtr () noexcept -> VMesh * { return this->_pMesh; }
        constexpr auto meshPtr () const noexcept -> VMesh const * { return this->_pMesh; }

        constexpr auto meshRendererPtr () noexcept -> VMeshRenderer * { return this->_pMeshRenderer; }
        constexpr auto meshRendererPtr () const noexcept -> VMeshRenderer const * { return this->_pMeshRenderer; }
    };

}

#endif //ENG1_VGAMEOBJECT_H

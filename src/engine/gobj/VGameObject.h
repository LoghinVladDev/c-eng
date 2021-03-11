//
// Created by loghin on 04.03.2021.
//

#ifndef ENG1_VGAMEOBJECT_H
#define ENG1_VGAMEOBJECT_H

#include <gobj/ecm/VEntity.h>

namespace engine {

    class VGameObject: public VEntity {
    private:
        //// private variables

        //// private functions

    public:
        //// public variables

        //// public functions
        [[nodiscard]] auto toString () const noexcept -> String override {
            return String().append("VGameObject { \n")
                .append("\tbase = ").append(VEntity::toString()).append("\n")
                .append("}");
        }
    };

}

#endif //ENG1_VGAMEOBJECT_H

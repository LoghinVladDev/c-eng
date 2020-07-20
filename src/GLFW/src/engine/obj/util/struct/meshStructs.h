//
// Created by loghin on 7/20/20.
//

#ifndef ENG1_MESHSTRUCTS_H
#define ENG1_MESHSTRUCTS_H

#include <glm/glm.hpp>

struct SVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 textureCoordinates;
};

struct STexture {
    uint32 id;
    std::string type;
};

#endif //ENG1_MESHSTRUCTS_H

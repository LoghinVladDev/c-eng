//
// Created by loghin on 7/20/20.
//

#ifndef ENG1_MESH_STRUCTS_H
#define ENG1_MESH_STRUCTS_H

#include <glm/glm.hpp>

struct SVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 coordinates;
    glm::vec3 tangent;
    glm::vec3 bitangent;
};

struct STexture {
    uint32 id;
    std::string type;
    std::string path;
};

#define _TEXTURE_TYPE_DIFFUSE       "textureDiffuse"
#define _TEXTURE_TYPE_SPECULAR      "textureSpecular"
#define _TEXTURE_TYPE_NORMAL        "textureNormal"
#define _TEXTURE_TYPE_AMBIENT       "textureAmbient"

#endif //ENG1_MESH_STRUCTS_H

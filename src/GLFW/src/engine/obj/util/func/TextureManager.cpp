//
// Created by vladl on 31/07/2020.
//

#include <iostream>
#include "TextureManager.h"
//#include

uint32 engine::TextureManager::loadTextureFromFile(const char *path, const std::string &directory, bool gamma) noexcept {
    std::string fileName = std::string(path);
    fileName = directory + '/' + fileName;

    uint32 textureID = 0;
    glGenTextures(1, &textureID);

    int32 width;
    int32 height;
    int32 numberOfComponents;
    uint8 * data = stbi_load(fileName.c_str(), &width, &height, &numberOfComponents, 0);
    if(data != nullptr) {
        GLenum format;
        if(numberOfComponents == 1)
            format = GL_RED;
        else if (numberOfComponents == 3)
            format = GL_RGB;
        else if (numberOfComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0 ,format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    } else {
        std::cout << "Texture failed to load from : " << path << '\n';
    }

    stbi_image_free(data);
    return textureID;
}
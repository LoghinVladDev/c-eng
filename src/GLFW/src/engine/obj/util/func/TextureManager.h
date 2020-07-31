//
// Created by vladl on 31/07/2020.
//

#ifndef ENG1_TEXTUREMANAGER_H
#define ENG1_TEXTUREMANAGER_H

#include <types.h>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include <stb-image.h>
#endif

namespace engine {

    class TextureManager {
    public:
        TextureManager() = delete;

        static uint32 loadTextureFromFile(const char *, const std::string &, bool = false) noexcept;
    };

}

#endif //ENG1_TEXTUREMANAGER_H

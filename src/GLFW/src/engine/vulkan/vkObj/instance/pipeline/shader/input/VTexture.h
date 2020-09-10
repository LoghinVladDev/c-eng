//
// Created by Vlad on 9/11/2020.
//

#ifndef ENG1_VTEXTURE_H
#define ENG1_VTEXTURE_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/instance/device/VLogicalDevice.h>
#include <vkObj/instance/pipeline/shader/input/VStagingBuffer.h>
#include <vkObj/instance/pipeline/command/VCommandPool.h>

namespace engine {

    template <class T>
    class VStagingBuffer;

    class VTexture {

        typedef struct STexturePack {
            uint8             * _pImageData;
            VulkanDeviceSize    _imageSize;
        };

    private:

        //// private variables
        uint32                          _textureWidth       {0U};
        uint32                          _textureHeight      {0U};
        uint32                          _textureChannels    {0U};
        uint8                         * _pImagePixelData    {nullptr};

        VStagingBuffer <VTexutrePack>   _stagingBuffer;
        VCommandPool                  * _pCommandPool       {nullptr};

        //// private functions

    public:
        //// public variables
        VTexture() noexcept = default;
        explicit VTexture(const char*) noexcept;

        void load(const char*, int = STBI_rgb_alpha) noexcept(false);

        //// public functions

    };

}


#endif //ENG1_VTEXTURE_H

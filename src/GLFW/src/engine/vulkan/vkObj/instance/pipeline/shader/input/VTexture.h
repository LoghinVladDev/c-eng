//
// Created by Vlad on 9/11/2020.
//

#ifndef ENG1_VTEXTURE_H
#define ENG1_VTEXTURE_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/instance/device/VLogicalDevice.h>
#include <vkObj/instance/pipeline/command/VCommandPool.h>
#include <vkObj/instance/pipeline/shader/input/VBuffer.h>
namespace engine {
    class VTexture {

    private:
        typedef struct {
            uint8             * _pImageData;
            VulkanDeviceSize    _imageSize;
        } STexturePack;

        class VTextureStagingBuffer : public VBuffer {
        private:
            //// private variables
            STexturePack    _texturePack    {
                STexturePack {
                    ._pImageData    = nullptr,
                    ._imageSize     = 0ULL
                }
            };

            //// private functions

        public:
            //// public variables

            //// public functions
            VTextureStagingBuffer () noexcept = default;
            VulkanResult setup(
                const VLogicalDevice&,
                VulkanSharingMode = VBuffer::TRANSFER_EXCLUSIVITY,
                const uint32 * = nullptr,
                uint32 = 0U
            ) noexcept;

            VulkanResult allocateMemory() noexcept;
            VulkanResult reload() noexcept;

            [[nodiscard]] constexpr const STexturePack & getBufferData () const noexcept {
                return this->_texturePack;
            }

            [[nodiscard]] constexpr STexturePack& getBufferData () noexcept {
                return this->_texturePack;
            }

            void free () noexcept override;
            void cleanup () noexcept override;

        };

        //// private variables
        uint32                          _textureWidth       {0U};
        uint32                          _textureHeight      {0U};
        uint32                          _textureChannels    {0U};
        VulkanFormat                    _textureFormat      {VulkanFormat::VK_FORMAT_R8G8B8A8_SRGB};

        VTextureStagingBuffer           _stagingBuffer;
        VulkanImage                     _handle             {VK_NULL_HANDLE};
        VulkanDeviceMemory              _memoryHandle       {VK_NULL_HANDLE};

        const VCommandPool            * _pCommandPool       {nullptr};

        //// private functions
        void load ( const char*, int32 = STBI_rgb_alpha ) noexcept (false);
        void unload() noexcept;

    public:
        //// public variables
        constexpr static VulkanFormat IMAGE_FORMAT_SRGBA_32BIT = VulkanFormat::VK_FORMAT_R8G8B8A8_SRGB;
        constexpr static VulkanFormat IMAGE_FORMAT_SRGB_24BIT = VulkanFormat::VK_FORMAT_R8G8B8_SRGB;

        constexpr static VulkanImageUsageFlagBits TRANSFER_DESTINATION = VulkanImageUsageFlagBits::VK_IMAGE_USAGE_TRANSFER_DST_BIT;
        constexpr static VulkanImageUsageFlagBits SAMPLED = VulkanImageUsageFlagBits::VK_IMAGE_USAGE_SAMPLED_BIT;

        constexpr static VulkanImageUsageFlags TEXTURE_GPU_LOCAL =
                static_cast < VulkanImageUsageFlags > ( VTexture::TRANSFER_DESTINATION ) |
                static_cast < VulkanImageUsageFlags > ( VTexture::SAMPLED );

        //// public functions

        VTexture() noexcept = default;

        VulkanResult setup (
                const char*,
                const VCommandPool &,
                const uint32 * = nullptr,
                uint32 = 0U,
                bool = false
        ) noexcept;

        VulkanResult allocateMemory () noexcept;

        void free() noexcept;
        void cleanup () noexcept;
    };

}


#endif //ENG1_VTEXTURE_H

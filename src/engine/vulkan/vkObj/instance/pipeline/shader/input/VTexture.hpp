//
// Created by Vlad on 9/11/2020.
//

#ifndef ENG1_VTEXTURE_HPP
#define ENG1_VTEXTURE_HPP

#include <VRenderObject.hpp>
#include <VLogicalDevice.hpp>
#include <VCommandPool.hpp>
#include <VBuffer.hpp>
#include <VImageView.hpp>
namespace engine {

    /**
     * @class engine::VTexture
     *
     * @brief Represents a Texture to be loaded into the GPU memory for shaders
     */
    class VTexture : public VRenderObject {
    private:

        /**
         * @struct engine::VTexture::STexturePack
         *
         * @brief Represents an Image's Data representation
         */
        typedef struct {
            /// byte array
            uint8             * _pImageData;
            /// array size
            VulkanDeviceSize    _imageSize;
        } STexturePack;

        /**
         * @class engine::VTexture::StagingBuffer, inherits VBuffer
         *
         * @brief Represents a Texture's Staging Buffer
         */
        class StagingBuffer : public VBuffer {
        private:
            //// private variables

            /// CPU data for Staging Buffer
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

            /**
             * @brief Default Constructor
             *
             * @exceptsafe
             */
            StagingBuffer () noexcept = default;

            ~StagingBuffer() noexcept override = default;

            /**
             * @brief Function initialises the Texture Staging Buffer
             *
             * @param device : engine::VLogicalDevice cref = Constant Reference to a Logical Device
             * @param sharingMode : VulkanSharingMode = Requested Sharing Mode for Memory
             * @param pQueueFamilyIndices : uint32 cptr = Address to one / an array of Queue Family Indices, used when sharing mode requested is CONCURRENT
             * @param queueFamilyIndexCount : uint32 = Number of Queue Family Indices at address above
             *
             * @exceptsafe
             *
             * @return VulkanResult::VK_SUCCESS if initialisation was successful OR
             * @return VulkanResult::VK_ERROR_INITIALIZATION_FAILED if Concurrency Mode Chosen but not supported OR
             * @return VulkanResult returned vkCreateBuffer on error occurrence - internal vulkan function
             */
            auto setup (
                VLogicalDevice      const &,
                VulkanSharingMode           = VBuffer::TRANSFER_EXCLUSIVITY,
                uint32              const * = nullptr,
                uint32                      = 0U
            ) noexcept -> VulkanResult;

            /**
             * @brief Function Allocates Staging Buffer Memory
             *
             * @exceptsafe
             *
             * @return VulkanResult::VK_SUCCESS if allocate of memory was successful OR
             * @return VulkanResult::VK_ERROR_INITIALIZATION_FAILED if memory type requested is not available OR
             * @return VulkanResult returned by vkAllocateMemory on error occurrence - internal vulkan function OR
             * @return VulkanResult returned by vkBindBufferMemory on error occurrence - internal vulkan function
             */
            auto allocateMemory() noexcept -> VulkanResult;

            /**
             * @brief Function reloads Data into GPU memory
             *
             * @exceptsafe
             *
             * @return VulkanResult::VK_SUCCESS if loading of memory onto buffer was successful OR
             * @return VulkanResult::VK_ERROR_MEMORY_MAP_FAILED if Memory was not allocated with flag MEMORY_CPU_WRITABLE OR
             * @return VulkanResult returned by vkMapMemory on error occurrence - internal vulkan function
             */
            auto reload() noexcept -> VulkanResult;

            /**
             * @brief Function Returns the Texture Pack stored inside the Object
             *
             * @exceptsafe
             *
             * @return engine::VTexture::STexturePack cref = Constant Reference to Texture Pack
             */
            [[nodiscard]] constexpr auto getBufferData () const noexcept -> STexturePack const & {
                return this->_texturePack;
            }

            /**
             * @brief Function Returns the Texture Pack stored inside the Object
             *
             * @exceptsafe
             *
             * @return engine::VTexture::STexturePack ref = Reference to Texture Pack
             */
            [[nodiscard]] constexpr STexturePack& getBufferData () noexcept {
                return this->_texturePack;
            }

            /**
             *
             */
            auto free () noexcept -> void override;
            auto clear () noexcept -> void override;

            [[nodiscard]] auto toString () const noexcept -> String override;
            [[nodiscard]] auto copy () const noexcept -> VTexture::StagingBuffer * override {
                return new VTexture::StagingBuffer(* this);
            }

            [[nodiscard]] auto operator == (Object const & o) const noexcept -> bool override {
                return VBuffer::operator==(o);
            }

            [[nodiscard]] auto hash () const noexcept -> Index override {
                return dataTypes::hash(this->_texturePack._imageSize) + VBuffer::hash();
            }
        };

        //// private variables
        uint32                          _textureWidth       {0U};
        uint32                          _textureHeight      {0U};
        uint32                          _textureChannels    {0U};
        VulkanFormat                    _textureFormat      {VulkanFormat::VK_FORMAT_R8G8B8A8_SRGB};

        VulkanImageLayout               _currentLayout      {VulkanImageLayout::VK_IMAGE_LAYOUT_UNDEFINED};
        VulkanSharingMode               _sharingMode        {VulkanSharingMode::VK_SHARING_MODE_EXCLUSIVE};
        StagingBuffer                   _stagingBuffer;
        VulkanImage                     _handle             {VK_NULL_HANDLE};
        VulkanDeviceMemory              _memoryHandle       {VK_NULL_HANDLE};

        VImageView                      _imageView;

        VCommandPool            const * _pCommandPool       {nullptr};

        //// private functions
        auto load ( StringLiteral, sint32 = STBI_rgb_alpha ) noexcept (false) -> void;
        auto unload() noexcept -> void;
        auto copy() noexcept -> VulkanResult;
        auto transitionImageLayout ( VulkanImageLayout ) noexcept -> VulkanResult;
        auto flush() noexcept -> VulkanResult;
        auto allocateMemory () noexcept -> VulkanResult;

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
        ~VTexture () noexcept override = default;

        [[nodiscard]] constexpr auto data () const noexcept -> VulkanImage const & {
            return this->_handle;
        }

        [[nodiscard]] constexpr auto getImageView () const noexcept -> VImageView const & {
            return this->_imageView;
        }

        [[nodiscard]] constexpr auto getLayout () const noexcept -> VulkanImageLayout {
            return this->_currentLayout;
        }

        auto setup (
                StringLiteral,
                VCommandPool    const &,
                uint32          const * = nullptr,
                uint32                  = 0U,
                bool                    = false
        ) noexcept -> VulkanResult;

        auto free() noexcept -> void;
        auto clear() noexcept -> void override;

        [[nodiscard]] auto toString () const noexcept -> String override;
        [[nodiscard]] auto operator == (Object const & o) const noexcept -> bool override {
            if ( this == & o ) return true;
            auto p = dynamic_cast < decltype (this) > (& o);
            if ( p == nullptr ) return false;

            return
                this->_handle == p->_handle &&
                this->_memoryHandle == p->_memoryHandle;
        }

        [[nodiscard]] auto hash () const noexcept -> Index override {
            return
                dataTypes::hash(reinterpret_cast<AddressValueType>(this->_handle)) +
                dataTypes::hash(reinterpret_cast<AddressValueType>(this->_memoryHandle));
        }

        [[nodiscard]] auto copy () const noexcept -> VTexture * override {
            return new VTexture (*this);
        }
    };

}


#endif //ENG1_VTEXTURE_HPP

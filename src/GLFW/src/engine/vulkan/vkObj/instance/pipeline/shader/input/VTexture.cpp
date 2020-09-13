//
// Created by Vlad on 9/11/2020.
//

#include <bits/ios_base.h>
#include "VTexture.h"
#include "VTextureDefs.h"

inline static void populateImageCreateInfo (
        VulkanImageCreateInfo * pCreateInfo,
        uint32 width,
        uint32 height,
        VulkanFormat format,
        VulkanSharingMode sharingMode
) noexcept {

}

void engine::VTexture::load(const char * pImagePath, int32 desiredChannels) noexcept(false) {
    int32 textureWidth;
    int32 textureHeight;
    int32 textureChannels;

    this->_stagingBuffer.getBufferData()._pImageData = stbi_load( pImagePath, & textureWidth, & textureHeight, & textureChannels, desiredChannels );

    if ( this->_stagingBuffer.getBufferData()._pImageData == nullptr )
        throw std::runtime_error ("Image load failure");

    this->_textureWidth     = static_cast < uint32 > ( textureWidth );
    this->_textureHeight    = static_cast < uint32 > ( textureHeight );
    this->_textureChannels  = static_cast < uint32 > ( textureChannels );

    this->_stagingBuffer.getBufferData()._imageSize =
            this->_textureWidth *
            this->_textureHeight *
            __IMAGE_BYTE_PER_PIXEL( desiredChannels );

    this->_textureFormat = desiredChannels == STBI_rgb_alpha
            ? VulkanFormat::VK_FORMAT_R8G8B8A8_SRGB
            : VulkanFormat::VK_FORMAT_R8G8B8_SRGB;
}

VulkanResult engine::VTexture::setup(
        const char          * pImagePath,
        const VCommandPool  & commandPool,
        const uint32        * pQueueFamilyIndices,
        uint32                queueFamilyIndexCount,
        bool                  forceMemoryExclusivity
) noexcept {
    this->_pCommandPool = & commandPool;

    try {
        this->load( pImagePath, STBI_rgb_alpha );
    } catch ( std::runtime_error & exception ) {
        return VulkanResult::VK_ERROR_INITIALIZATION_FAILED;
    }

    VulkanResult setupStagingBufferResult = this->_stagingBuffer.setup(
            * this->_pCommandPool->getLogicalDevicePtr(),
            VBuffer::getOptimalSharingMode( forceMemoryExclusivity, queueFamilyIndexCount, * this->_pCommandPool->getLogicalDevicePtr() ),
            pQueueFamilyIndices,
            queueFamilyIndexCount
    );

    if ( setupStagingBufferResult != VulkanResult::VK_SUCCESS ) {
        stbi_image_free( this->_stagingBuffer.getBufferData()._pImageData );
        this->_stagingBuffer.getBufferData() = VTexture::STexturePack  {
            ._pImageData = nullptr,
            ._imageSize  = 0ULL
        };
        return setupStagingBufferResult;
    }

    VulkanResult allocateResult = this->allocateMemory();
    if ( allocateResult != VulkanResult::VK_SUCCESS )
        return allocateResult;

}

VulkanResult engine::VTexture::allocateMemory() noexcept {
    VulkanResult allocateResult = this->_stagingBuffer.allocateMemory();
    if ( allocateResult != VulkanResult::VK_SUCCESS ) {
        stbi_image_free( this->_stagingBuffer.getBufferData()._pImageData );
        this->_stagingBuffer.getBufferData() = VTexture::STexturePack  {
                ._pImageData = nullptr,
                ._imageSize  = 0ULL
        };
        return allocateResult;
    }

    VulkanResult loadStagingBufferResult = this->_stagingBuffer.load( this->_stagingBuffer.getBufferData()._pImageData, this->_stagingBuffer.getBufferData()._imageSize );
    if( loadStagingBufferResult != VulkanResult::VK_SUCCESS )
        return loadStagingBufferResult;

    extern uint32 findMemoryType( uint32, VulkanMemoryPropertyFlags, const engine::VLogicalDevice * );
}

void engine::VTexture::free() noexcept {
    this->_stagingBuffer.free();
}

void engine::VTexture::cleanup() noexcept {
    this->free();

    stbi_image_free( this->_stagingBuffer.getBufferData()._pImageData );
    this->_stagingBuffer.getBufferData() =  VTexture::STexturePack  {
            ._pImageData = nullptr,
            ._imageSize  = 0ULL
    };

    this->_stagingBuffer.cleanup();
}

void engine::VTexture::VTextureStagingBuffer::free() noexcept {
    return VBuffer::free();
}

void engine::VTexture::VTextureStagingBuffer::cleanup() noexcept {
    return VBuffer::cleanup();
}

VulkanResult engine::VTexture::VTextureStagingBuffer::allocateMemory() noexcept {
    return VBuffer::allocateMemory( VBuffer::MEMORY_CPU_BUFFER_FLAGS );
}

VulkanResult engine::VTexture::VTextureStagingBuffer::reload() noexcept {
    return VBuffer::load (
            static_cast < const void * > ( this->_texturePack._pImageData ),
            static_cast < std::size_t  > ( this->_texturePack._imageSize )
    );
}

VulkanResult engine::VTexture::VTextureStagingBuffer::setup(
        const VLogicalDevice  & device,
        VulkanSharingMode       sharingMode,
        const uint32 *          pQueueFamilyIndices,
        uint32                  queueFamilyIndexCount
) noexcept {
    this->setElementCount( 1U );

    return VBuffer::setup(
        device,
        static_cast < std::size_t > ( this->_texturePack._imageSize ),
        VBuffer::STAGING_BUFFER_CPU_LOCAL,
        sharingMode,
        pQueueFamilyIndices,
        queueFamilyIndexCount
    );
}

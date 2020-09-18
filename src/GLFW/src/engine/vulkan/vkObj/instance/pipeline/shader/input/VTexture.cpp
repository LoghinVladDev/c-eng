//
// Created by Vlad on 9/11/2020.
//

#include <bits/ios_base.h>
#include "VTexture.h"
#include "VTextureDefs.h"
#include <vkUtils/VStdUtilsDefs.h>

inline static void populateImageCreateInfo (
        VulkanImageCreateInfo * pCreateInfo,
        uint32 width,
        uint32 height,
        VulkanFormat format,
        VulkanSharingMode sharingMode,
        const uint32* pQueueFamilyIndices,
        uint32 queueFamilyIndexCount,
        VulkanImageLayout initialLayout = VulkanImageLayout::VK_IMAGE_LAYOUT_UNDEFINED
) noexcept {
    if ( pCreateInfo == nullptr )
        return;

    * pCreateInfo = VulkanImageCreateInfo {
        .sType                  = VulkanStructureType::VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        .pNext                  = nullptr,
        .flags                  = VULKAN_NULL_FLAGS,
        .imageType              = VulkanImageType::VK_IMAGE_TYPE_2D,
        .format                 = format,
        .extent                 = VulkanExtent3D {
            .width                  = width,
            .height                 = height,
            .depth                  = 1U
        },
        .mipLevels              = 1U,
        .arrayLayers            = 1U,
        .samples                = VulkanSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT,
        .usage                  = engine::VTexture::TEXTURE_GPU_LOCAL,
        .sharingMode            = sharingMode,
        .queueFamilyIndexCount  = queueFamilyIndexCount,
        .pQueueFamilyIndices    = pQueueFamilyIndices,
        .initialLayout          = initialLayout
    };
}

inline static void populateImageMemoryBarrier (
    VulkanImageMemoryBarrier * pMemoryBarrier,
    VulkanImageLayout          oldLayout,
    VulkanImageLayout          newLayout,
    VulkanImage                image,
    VulkanAccessFlags          sourceAccessMask = 0U,
    VulkanAccessFlags          destinationAccessMask = 0U
) noexcept {
    if ( pMemoryBarrier == nullptr )
        return;

    * pMemoryBarrier = VulkanImageMemoryBarrier {
        .sType                  = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
        .pNext                  = nullptr,
        .srcAccessMask          = sourceAccessMask,
        .dstAccessMask          = destinationAccessMask,
        .oldLayout              = oldLayout,
        .newLayout              = newLayout,
        .srcQueueFamilyIndex    = VK_QUEUE_FAMILY_IGNORED,
        .dstQueueFamilyIndex    = VK_QUEUE_FAMILY_IGNORED,
        .image                  = image,
        .subresourceRange       = VulkanImageSubresourceRange {
            .aspectMask             = (VulkanImageAspectFlags) VulkanImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT,
            .baseMipLevel           = 0U,
            .levelCount             = 1U,
            .baseArrayLayer         = 0U,
            .layerCount             = 1U
        }
    };
}

inline static void populateBufferImageCopy (
    VulkanBufferImageCopy * pBufferImageCopy,
    uint32 width,
    uint32 height
) noexcept {
    if ( pBufferImageCopy == nullptr )
        return;

    * pBufferImageCopy = VulkanBufferImageCopy {
        .bufferOffset       = 0U,
        .bufferRowLength    = 0U,
        .bufferImageHeight  = 0U,
        .imageSubresource   = VulkanImageSubresourceLayers {
            .aspectMask         = (VulkanImageAspectFlags) VulkanImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT,
            .mipLevel           = 0U,
            .baseArrayLayer     = 0U,
            .layerCount         = 1U
        },
        .imageOffset        = VulkanOffset3D {
            .x                  = 0U,
            .y                  = 0U,
            .z                  = 0U
        },
        .imageExtent        = VulkanExtent3D {
            .width              = width,
            .height             = height,
            .depth              = 1U
        }
    };
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

void engine::VTexture::unload() noexcept {
    stbi_image_free( this->_stagingBuffer.getBufferData()._pImageData );
    this->_stagingBuffer.getBufferData() = VTexture::STexturePack {
        ._pImageData = nullptr,
        ._imageSize  = 0ULL
    };
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

    ENG_RETURN_IF_NOT_SUCCESS_2 (
        this->_stagingBuffer.setup(
                * this->_pCommandPool->getLogicalDevicePtr(),
            VBuffer::getOptimalSharingMode( forceMemoryExclusivity, queueFamilyIndexCount, * this->_pCommandPool->getLogicalDevicePtr() ),
            pQueueFamilyIndices,
            queueFamilyIndexCount
        ),
        0,
        this->unload()
    )

    VulkanImageCreateInfo createInfo {};
    populateImageCreateInfo(
            & createInfo,
            this->_textureWidth,
            this->_textureHeight,
            this->_textureFormat,
            (this->_sharingMode = VBuffer::getOptimalSharingMode( forceMemoryExclusivity, queueFamilyIndexCount, * this->_pCommandPool->getLogicalDevicePtr() ) ),
            pQueueFamilyIndices,
            queueFamilyIndexCount,
            this->_currentLayout
    );

    ENG_RETURN_IF_NOT_SUCCESS_2(
        vkCreateImage (
            this->_pCommandPool->getLogicalDevicePtr()->data(),
            & createInfo,
            nullptr,
            & this->_handle
        ),
        1,
        this->unload()
    )

    ENG_RETURN_IF_NOT_SUCCESS(this->allocateMemory(), 2);

    return this->flush();
}

VulkanResult engine::VTexture::flush() noexcept {
    ENG_RETURN_IF_NOT_SUCCESS(this->transitionImageLayout(VulkanImageLayout::VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL), 0);
    ENG_RETURN_IF_NOT_SUCCESS(this->copy(), 1);
    return this->transitionImageLayout(VulkanImageLayout::VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
}

#include <vkObj/instance/pipeline/command/VCommandBuffer.h>
VulkanResult engine::VTexture::transitionImageLayout(VulkanImageLayout newLayout) noexcept {
    bool isTransferOptimized =
            this->_pCommandPool->isOptimizedForTransfers() &&
            this->_sharingMode == VulkanSharingMode::VK_SHARING_MODE_CONCURRENT &&
            this->_stagingBuffer.getBufferSharingMode() == VulkanSharingMode::VK_SHARING_MODE_CONCURRENT;

    const VQueue * pQueue = isTransferOptimized
            ? this->_pCommandPool->getLogicalDevicePtr()->getFirstTransferQueuePtr()
            : this->_pCommandPool->getLogicalDevicePtr()->getFirstGraphicsQueuePtr();

    if ( pQueue == nullptr )
        return VulkanResult::VK_ERROR_DEVICE_LOST;

    auto oneTimeUseBuffer = VCommandBuffer::getOneTimeUseBuffer( * this->_pCommandPool );
    ENG_RETURN_IF_NOT_SUCCESS(oneTimeUseBuffer.beginOneTimeUse(),0);

    VulkanImageMemoryBarrier barrier {};

    populateImageMemoryBarrier(
        & barrier,
        this->_currentLayout,
        newLayout,
        this->_handle,
        0U, // TODO
        0U  // TODO
    );

    vkCmdPipelineBarrier(
        oneTimeUseBuffer.data(),
        0U, // TODO
        0U, // TODO
        0U,
        0U,
        nullptr,
        0U,
        nullptr,
        1U,
        & barrier
    );

    this->_currentLayout = newLayout;

    return oneTimeUseBuffer.submitOneTimeUse( pQueue );
}

VulkanResult engine::VTexture::copy () noexcept {
    bool isTransferOptimized =
        this->_pCommandPool->isOptimizedForTransfers() &&
        this->_sharingMode == VulkanSharingMode::VK_SHARING_MODE_CONCURRENT &&
        this->_stagingBuffer.getBufferSharingMode() == VulkanSharingMode::VK_SHARING_MODE_CONCURRENT;

    const VQueue * pQueue = isTransferOptimized
                            ? this->_pCommandPool->getLogicalDevicePtr()->getFirstTransferQueuePtr()
                            : this->_pCommandPool->getLogicalDevicePtr()->getFirstGraphicsQueuePtr();

    if ( pQueue == nullptr )
        return VulkanResult::VK_ERROR_DEVICE_LOST;

    auto oneTimeUseBuffer = VCommandBuffer::getOneTimeUseBuffer( * this->_pCommandPool );
    ENG_RETURN_IF_NOT_SUCCESS( oneTimeUseBuffer.beginOneTimeUse(), 0 );

    VulkanBufferImageCopy region {};
    populateBufferImageCopy(
        & region,
        this->_textureWidth,
        this->_textureHeight
    );

    vkCmdCopyBufferToImage(
        oneTimeUseBuffer.data(),
        this->_stagingBuffer.data(),
        this->_handle,
        VulkanImageLayout::VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
        1U,
        & region
    );



    return oneTimeUseBuffer.submitOneTimeUse( pQueue );
}



VulkanResult engine::VTexture::allocateMemory() noexcept {
    ENG_RETURN_IF_NOT_SUCCESS_2(
        this->_stagingBuffer.allocateMemory(),
        0,
        this->unload()
    );

    ENG_RETURN_IF_NOT_SUCCESS_2(
        this->_stagingBuffer.load(
                this->_stagingBuffer.getBufferData()._pImageData,
                this->_stagingBuffer.getBufferData()._imageSize
        ),
        1,
        this->unload()
    );

    extern uint32 findMemoryType( uint32, VulkanMemoryPropertyFlags, const engine::VLogicalDevice * ) noexcept;
    extern void populateMemoryAllocateInfo ( VulkanMemoryAllocateInfo *, VulkanDeviceSize, uint32 ) noexcept;

    VulkanMemoryRequirements memoryRequirements;
    vkGetImageMemoryRequirements(
            this->_pCommandPool->getLogicalDevicePtr()->data(),
            this->_handle,
            & memoryRequirements
    );

    VulkanMemoryAllocateInfo allocateInfo {};
    populateMemoryAllocateInfo(
        & allocateInfo,
        memoryRequirements.size,
        findMemoryType(
            memoryRequirements.memoryTypeBits,
            static_cast < VulkanMemoryPropertyFlags > ( VulkanMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT ),
            this->_pCommandPool->getLogicalDevicePtr()
        )
    );

    ENG_RETURN_IF_NOT_SUCCESS(
        vkAllocateMemory(
            this->_pCommandPool->getLogicalDevicePtr()->data(),
            & allocateInfo,
            nullptr,
            & this->_memoryHandle
        ),
        2
    );

    ENG_RETURN_IF_NOT_SUCCESS(
        vkBindImageMemory(
            this->_pCommandPool->getLogicalDevicePtr()->data(),
            this->_handle,
            this->_memoryHandle,
            0
        ),
        3
    );

    return result3;
}

void engine::VTexture::free() noexcept {
    this->unload();
    this->_stagingBuffer.free();
}

void engine::VTexture::cleanup() noexcept {
    this->free();
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

//
// Created by Vlad on 9/11/2020.
//

#if !defined(_MSC_VER)
#include <bits/ios_base.h>
#endif
#include "VTexture.hpp"
#include "VTextureDefs.h"
#include <vkUtils/VStdUtilsDefs.h>


inline static auto populateImageCreateInfo (
        VulkanImageCreateInfo         * pCreateInfo,
        uint32                          width,
        uint32                          height,
        VulkanFormat                    format,
        VulkanSharingMode               sharingMode,
        uint32                  const * pQueueFamilyIndices,
        uint32                          queueFamilyIndexCount,
        VulkanImageLayout               initialLayout = VulkanImageLayout::VK_IMAGE_LAYOUT_UNDEFINED
) noexcept -> void {
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
        .tiling                 = VulkanImageTiling::VK_IMAGE_TILING_OPTIMAL,
        .usage                  = engine::VTexture::TEXTURE_GPU_LOCAL,
        .sharingMode            = sharingMode,
        .queueFamilyIndexCount  = queueFamilyIndexCount,
        .pQueueFamilyIndices    = pQueueFamilyIndices,
        .initialLayout          = initialLayout,
    };
}

auto populateImageMemoryBarrier (
    VulkanImageMemoryBarrier * pMemoryBarrier,
    VulkanImageLayout          oldLayout,
    VulkanImageLayout          newLayout,
    VulkanImage                image,
    VulkanAccessFlags          sourceAccessMask = 0U,
    VulkanAccessFlags          destinationAccessMask = 0U,
    VulkanImageAspectFlags     imageAspectMask = VulkanImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT
) noexcept -> void {
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
            .aspectMask             = static_cast < VulkanImageAspectFlags > (imageAspectMask),
            .baseMipLevel           = 0U,
            .levelCount             = 1U,
            .baseArrayLayer         = 0U,
            .layerCount             = 1U
        }
    };
}

inline static auto populateBufferImageCopy (
    VulkanBufferImageCopy * pBufferImageCopy,
    uint32                  width,
    uint32                  height
) noexcept -> void {
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

auto engine::VTexture::load(StringLiteral pImagePath, sint32 desiredChannels) noexcept(false) -> void {
    sint32 textureWidth;
    sint32 textureHeight;
    sint32 textureChannels;

    stbi_set_flip_vertically_on_load(true);
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

auto engine::VTexture::unload() noexcept -> void {
    stbi_image_free( this->_stagingBuffer.getBufferData()._pImageData );
    this->_stagingBuffer.getBufferData() = VTexture::STexturePack {
        ._pImageData = nullptr,
        ._imageSize  = 0ULL
    };
}

auto engine::VTexture::setup(
        StringLiteral           pImagePath,
        VCommandPool    const & commandPool,
        uint32          const * pQueueFamilyIndices,
        uint32                  queueFamilyIndexCount,
        bool                    forceMemoryExclusivity
) noexcept -> VulkanResult {
    this->_pCommandPool = & commandPool;

    try {
        this->load( pImagePath, STBI_rgb_alpha );
    } catch ( std::runtime_error & exception ) {
#if defined(_MSC_VER)
        (void)exception;
#endif
        return VulkanResult::VK_ERROR_INITIALIZATION_FAILED;
    }

    ENG_RETURN_IF_NOT_SUCCESS_2 (
        this->_stagingBuffer.setup(
                * this->_pCommandPool->getLogicalDevicePtr(),
            VBuffer::getOptimalSharingMode( forceMemoryExclusivity, queueFamilyIndexCount, * this->_pCommandPool->getLogicalDevicePtr() ),
            pQueueFamilyIndices,
            queueFamilyIndexCount
        ),
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
        this->unload()
    )

    ENG_RETURN_IF_NOT_SUCCESS(this->allocateMemory())
    ENG_RETURN_IF_NOT_SUCCESS(this->flush())

    ENG_RETURN_IF_NOT_SUCCESS(
        this->_imageView.setup(
            this->_handle,
            VTexture::IMAGE_FORMAT_SRGBA_32BIT,
            * this->_pCommandPool->getLogicalDevicePtr()
        )
    )

    return VulkanResult::VK_SUCCESS;
}

auto engine::VTexture::flush() noexcept -> VulkanResult {
    ENG_RETURN_IF_NOT_SUCCESS(this->transitionImageLayout(VulkanImageLayout::VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL))
    ENG_RETURN_IF_NOT_SUCCESS(this->copy())
    ENG_RETURN_IF_NOT_SUCCESS(this->transitionImageLayout(VulkanImageLayout::VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL))

    this->_stagingBuffer.free();
    this->_stagingBuffer.clear();

    return VulkanResult::VK_SUCCESS;
}

#include <VCommandBuffer.hpp>
auto engine::VTexture::transitionImageLayout(VulkanImageLayout newLayout) noexcept -> VulkanResult {
    bool isTransferOptimized =
            this->_pCommandPool->isOptimizedForTransfers() &&
            this->_sharingMode == VulkanSharingMode::VK_SHARING_MODE_CONCURRENT; // &&
//            this->_stagingBuffer.getBufferSharingMode() == VulkanSharingMode::VK_SHARING_MODE_CONCURRENT;

    const VQueue * pQueue = isTransferOptimized
            ? this->_pCommandPool->getLogicalDevicePtr()->getFirstTransferQueuePtr()
            : this->_pCommandPool->getLogicalDevicePtr()->getFirstGraphicsQueuePtr();

    if ( pQueue == nullptr )
        return VulkanResult::VK_ERROR_DEVICE_LOST;

    auto oneTimeUseBuffer = VCommandBuffer::getOneTimeUseBuffer( * this->_pCommandPool );
    ENG_RETURN_IF_NOT_SUCCESS(oneTimeUseBuffer.beginOneTimeUse())

    VulkanPipelineStageFlags    sourceStage;
    VulkanPipelineStageFlags    destinationStage;
    VulkanAccessFlags           sourceAccessMask;
    VulkanAccessFlags           destinationAccessMask;
    if (
            this->_currentLayout    == VulkanImageLayout::VK_IMAGE_LAYOUT_UNDEFINED &&
            newLayout               == VulkanImageLayout::VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL
    ) {
        sourceStage             = VulkanPipelineStageFlagBits::VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        destinationStage        = VulkanPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT;

        sourceAccessMask        = 0U;
        destinationAccessMask   = VulkanAccessFlagBits::VK_ACCESS_TRANSFER_WRITE_BIT;
    } else if (
            this->_currentLayout    == VulkanImageLayout::VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL &&
            newLayout               == VulkanImageLayout::VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
    ) {
        sourceStage             = VulkanPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT;
        destinationStage        = VulkanPipelineStageFlagBits::VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;

        sourceAccessMask        = VulkanAccessFlagBits::VK_ACCESS_TRANSFER_WRITE_BIT;
        destinationAccessMask   = VulkanAccessFlagBits::VK_ACCESS_SHADER_READ_BIT;
    } else
        return VulkanResult::VK_ERROR_INITIALIZATION_FAILED;

    VulkanImageMemoryBarrier barrier {};

    populateImageMemoryBarrier(
        & barrier,
        this->_currentLayout,
        newLayout,
        this->_handle,
        sourceAccessMask,
        destinationAccessMask
    );

    vkCmdPipelineBarrier(
        oneTimeUseBuffer.data(),
        sourceStage,
        destinationStage,
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

auto engine::VTexture::copy () noexcept -> VulkanResult {
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
    ENG_RETURN_IF_NOT_SUCCESS( oneTimeUseBuffer.beginOneTimeUse())

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

extern uint32 findMemoryType( uint32, VulkanMemoryPropertyFlags, const engine::VLogicalDevice * ) noexcept;
extern void populateMemoryAllocateInfo ( VulkanMemoryAllocateInfo *, VulkanDeviceSize, uint32 ) noexcept;

auto engine::VTexture::allocateMemory() noexcept -> VulkanResult {
    ENG_RETURN_IF_NOT_SUCCESS_2(
        this->_stagingBuffer.allocateMemory(),
        this->unload()
    )

    ENG_RETURN_IF_NOT_SUCCESS_2(
        this->_stagingBuffer.load(
                this->_stagingBuffer.getBufferData()._pImageData,
                this->_stagingBuffer.getBufferData()._imageSize
        ),
        this->unload()
    )

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
        )
    )

    ENG_RETURN_IF_NOT_SUCCESS(
        vkBindImageMemory(
            this->_pCommandPool->getLogicalDevicePtr()->data(),
            this->_handle,
            this->_memoryHandle,
            0
        )
    )

    return VulkanResult::VK_SUCCESS;
}

auto engine::VTexture::free() noexcept -> void {
    this->unload();
    vkFreeMemory( this->_pCommandPool->getLogicalDevicePtr()->data(), this->_memoryHandle, nullptr );
}

auto engine::VTexture::clear() noexcept -> void {
    this->free();
    this->_imageView.clear();
    vkDestroyImage( this->_pCommandPool->getLogicalDevicePtr()->data(), this->_handle, nullptr );
}

auto engine::VTexture::StagingBuffer::free() noexcept -> void {
    return VBuffer::free();
}

auto engine::VTexture::StagingBuffer::clear() noexcept -> void {
    return VBuffer::clear();
}

auto engine::VTexture::StagingBuffer::allocateMemory() noexcept -> VulkanResult {
    return VBuffer::allocateMemory( VBuffer::MEMORY_CPU_BUFFER_FLAGS );
}

auto engine::VTexture::StagingBuffer::reload() noexcept -> VulkanResult {
    return VBuffer::load (
            static_cast < void const * > ( this->_texturePack._pImageData ),
            static_cast < std::size_t  > ( this->_texturePack._imageSize )
    );
}

auto engine::VTexture::StagingBuffer::setup(
        VLogicalDevice      const & device,
        VulkanSharingMode           sharingMode,
        uint32              const * pQueueFamilyIndices,
        uint32                      queueFamilyIndexCount
) noexcept -> VulkanResult {
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

#include <sstream>
auto engine::VTexture::StagingBuffer::toString() const noexcept -> String {
    std::stringstream oss;

    oss << "VTexture::StagingBuffer { " <<
        "pTextureData = 0x" << std::hex << reinterpret_cast < AddressValueType > (this->_texturePack._pImageData ) <<
        ", imageSize = " << std::dec << this->_texturePack._imageSize <<
        ", bufferBase = " << VBuffer::toString() << " }";
    return oss.str();
}

auto engine::VTexture::toString() const noexcept -> String {
    std::stringstream oss;

    oss << "VTexture " <<
        "{ handle = 0x" << std::hex << reinterpret_cast<AddressValueType>(this->_handle) <<
        ", memoryHandle = 0x" << std::hex << reinterpret_cast<AddressValueType>(this->_memoryHandle) <<
        ", pCommandPool = 0x" << std::hex << reinterpret_cast<AddressValueType>(this->_pCommandPool) <<
        ", textureWidth = " << std::dec << this->_textureWidth <<
        ", textureHeight = " << this->_textureHeight <<
        ", textureChannels = " << this->_textureChannels <<
        ", textureFormat = " << static_cast < uint32 > (this->_textureFormat) <<
        ", currentLayout = " << static_cast < uint32 > (this->_currentLayout) <<
        ", sharingMode = " << static_cast < uint32 > (this->_sharingMode) <<
        ", stagingBuffer = " << this->_stagingBuffer.toString() << " }";

    return oss.str();
}
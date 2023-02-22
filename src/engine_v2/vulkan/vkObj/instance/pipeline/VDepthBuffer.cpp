//
// Created by vladl on 9/21/2020.
//

#include "VDepthBuffer.hpp"
#include <VBuffer.hpp>

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

static auto findSupportedFormat(
        std :: vector < VulkanFormat >  const & candidates,
        VulkanImageTiling                       tiling,
        VulkanFormatFeatureFlags                features,
        VPhysicalDevice                 const * pPhysicalDevice
) noexcept -> VulkanFormat {
    for ( VulkanFormat format : candidates ) {
        VulkanFormatProperties properties;
        vkGetPhysicalDeviceFormatProperties( pPhysicalDevice->data(), format, & properties );

        if (
                tiling == VulkanImageTiling::VK_IMAGE_TILING_LINEAR         &&
                (properties.linearTilingFeatures & features) == features
                                                                            ||
                tiling == VulkanImageTiling::VK_IMAGE_TILING_OPTIMAL        &&
                (properties.optimalTilingFeatures & features) == features
        ) {
            return format;
        }
    }

    return VulkanFormat :: VK_FORMAT_UNDEFINED;
}

auto getDepthFormat (
        VPhysicalDevice const * pPhysicalDevice
) noexcept -> VulkanFormat {

    return findSupportedFormat(
            {
                VulkanFormat :: VK_FORMAT_D32_SFLOAT,
                VulkanFormat :: VK_FORMAT_D32_SFLOAT_S8_UINT,
                VulkanFormat :: VK_FORMAT_D24_UNORM_S8_UINT
            },
            VulkanImageTiling :: VK_IMAGE_TILING_OPTIMAL,
            VulkanFormatFeatureFlagBits :: VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT,
            pPhysicalDevice
    );
}

constexpr static auto hasStencilComponent ( VulkanFormat format ) noexcept -> bool {
    return
        format == VulkanFormat :: VK_FORMAT_D32_SFLOAT_S8_UINT ||
        format == VulkanFormat :: VK_FORMAT_D24_UNORM_S8_UINT;
}

inline static auto populateCreateImageInfo (
    VulkanImageCreateInfo * pCreateInfo,
    uint32                  width,
    uint32                  height,
    VulkanFormat            format,
    VulkanImageTiling       tiling,
    VulkanImageUsageFlags   usage,
    VulkanSharingMode       sharingMode,
    uint32          const * pQueueFamilyIndices,
    uint32                  queueFamilyIndexCount
) noexcept -> void {
    if ( pCreateInfo == nullptr ) {
        return;
    }

    * pCreateInfo = VulkanImageCreateInfo {
        .sType                  = VulkanStructureType :: VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        .pNext                  = nullptr,
        .flags                  = VULKAN_NULL_FLAGS,
        .imageType              = VulkanImageType :: VK_IMAGE_TYPE_2D,
        .format                 = format,
        .extent                 = VulkanExtent3D {
            .width                  = width,
            .height                 = height,
            .depth                  = 1U
        },
        .mipLevels              = 1U,
        .arrayLayers            = 1U,
        .samples                = VulkanSampleCountFlagBits :: VK_SAMPLE_COUNT_1_BIT,
        .tiling                 = tiling,
        .usage                  = usage,
        .sharingMode            = sharingMode,
        .queueFamilyIndexCount  = queueFamilyIndexCount,
        .pQueueFamilyIndices    = pQueueFamilyIndices,
        .initialLayout          = VulkanImageLayout :: VK_IMAGE_LAYOUT_UNDEFINED
    };
}

extern uint32 findMemoryType(
        uint32,
        VulkanMemoryPropertyFlags,
        VLogicalDevice const *
) noexcept;

extern void populateMemoryAllocateInfo (
        VulkanMemoryAllocateInfo *,
        VulkanDeviceSize,
        uint32
) noexcept;

#include <vkUtils/VStdUtilsDefs.h>
#include <VSwapChain.hpp>

auto VDepthBuffer :: setup(
        VCommandPool  const & commandPool,
        uint32        const * pQueueFamilyIndices,
        uint32                queueFamilyIndexCount,
        bool                  forceMemoryExclusivity __CDS_MaybeUnused
) noexcept -> VulkanResult {

    this->_pCommandPool = & commandPool;
    auto * pLogicalDevice = this->_pCommandPool->getLogicalDevicePtr();
    auto * pSwapChain = pLogicalDevice->getSwapChain();
    this->_format = getDepthFormat( pLogicalDevice->getBasePhysicalDevice() );

    this->_sharingMode = VBuffer :: getOptimalSharingMode( forceMemoryExclusivity, queueFamilyIndexCount,  * pLogicalDevice );

    VulkanImageCreateInfo createInfo {};
    populateCreateImageInfo (
        & createInfo,
        pSwapChain->getImagesInfo().extent.width,
        pSwapChain->getImagesInfo().extent.height,
        this->_format,
        VulkanImageTiling :: VK_IMAGE_TILING_OPTIMAL,
        VulkanImageUsageFlagBits :: VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
        this->_sharingMode,
        pQueueFamilyIndices,
        queueFamilyIndexCount
    );

    VulkanResult result;

    result = vkCreateImage(
        pLogicalDevice->data(),
        & createInfo,
        nullptr,
        & this->_image
    );

    if ( result != VulkanResult :: VK_SUCCESS ) {
        return result;
    }

    VulkanMemoryRequirements memoryRequirements;
    vkGetImageMemoryRequirements (
            pLogicalDevice->data(),
            this->_image,
            & memoryRequirements
    );

    VulkanMemoryAllocateInfo allocateInfo {};
    populateMemoryAllocateInfo (
        & allocateInfo,
        memoryRequirements.size,
        findMemoryType(
            memoryRequirements.memoryTypeBits,
            VBuffer :: MEMORY_GPU_LOCAL,
            pLogicalDevice
        )
    );

    result = vkAllocateMemory(
        pLogicalDevice->data(),
        & allocateInfo,
        nullptr,
        & this->_imageMemory
    );

    if ( result != VulkanResult :: VK_SUCCESS ) {
        vkFreeMemory ( pLogicalDevice->data(), this->_imageMemory, nullptr );
        return result;
    }

    result = vkBindImageMemory(
        pLogicalDevice->data(),
        this->_image,
        this->_imageMemory,
        0U
    );

    if ( result != VulkanResult :: VK_SUCCESS ) {
        vkDestroyImage( this->_pCommandPool->getLogicalDevicePtr()->data(), this->_image, nullptr );
        vkFreeMemory ( pLogicalDevice->data(), this->_imageMemory, nullptr );
        return result;
    }


    result = this->_imageView.setup(
        this->_image,
        this->_format,
        * pLogicalDevice,
        VulkanImageAspectFlagBits::VK_IMAGE_ASPECT_DEPTH_BIT
    );

    if ( result != VulkanResult :: VK_SUCCESS ) {
        this->_imageView.clear();
        vkDestroyImage( this->_pCommandPool->getLogicalDevicePtr()->data(), this->_image, nullptr );
        vkFreeMemory ( pLogicalDevice->data(), this->_imageMemory, nullptr );
        return result;
    }

    result = this->transitionImageLayout(
        VulkanImageLayout :: VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
    );

    if ( result != VulkanResult :: VK_SUCCESS ) {
        this->_imageView.clear();
        vkDestroyImage( this->_pCommandPool->getLogicalDevicePtr()->data(), this->_image, nullptr );
        vkFreeMemory ( pLogicalDevice->data(), this->_imageMemory, nullptr );
        return result;
    }

    return VulkanResult :: VK_SUCCESS;
}

auto VDepthBuffer :: clear() noexcept -> void {
    this->_imageView.clear();

    vkDestroyImage( this->_pCommandPool->getLogicalDevicePtr()->data(), this->_image, nullptr );
    vkFreeMemory( this->_pCommandPool->getLogicalDevicePtr()->data(), this->_imageMemory, nullptr );

    this->_image            = VK_NULL_HANDLE;
    this->_imageMemory      = VK_NULL_HANDLE;
    this->_currentLayout    = VulkanImageLayout :: VK_IMAGE_LAYOUT_UNDEFINED;
    this->_pCommandPool     = nullptr;
    this->_sharingMode      = VulkanSharingMode :: VK_SHARING_MODE_EXCLUSIVE;
    this->_format           = VulkanFormat :: VK_FORMAT_D32_SFLOAT;
}

#include <VCommandBuffer.hpp>
extern auto populateImageMemoryBarrier (
        VulkanImageMemoryBarrier * pMemoryBarrier,
        VulkanImageLayout          oldLayout,
        VulkanImageLayout          newLayout,
        VulkanImage                image,
        VulkanAccessFlags          sourceAccessMask = 0U,
        VulkanAccessFlags          destinationAccessMask = 0U,
        VulkanImageAspectFlags     imageAspectMask = VulkanImageAspectFlagBits :: VK_IMAGE_ASPECT_COLOR_BIT
) -> void;

__CDS_MaybeUnused auto engine :: VDepthBuffer :: transitionImageLayout (
        VulkanImageLayout newLayout
) noexcept -> VulkanResult {

    bool isTransferOptimized =
            this->_pCommandPool->isOptimizedForTransfers() &&
            this->_sharingMode == VulkanSharingMode :: VK_SHARING_MODE_CONCURRENT;

    const VQueue * pQueue = isTransferOptimized
            ? this->_pCommandPool->getLogicalDevicePtr()->getFirstTransferQueuePtr()
            : this->_pCommandPool->getLogicalDevicePtr()->getFirstGraphicsQueuePtr();

    if ( pQueue == nullptr ) {
        return VulkanResult::VK_ERROR_DEVICE_LOST;
    }

    auto oneTimeUseBuffer = VCommandBuffer :: getOneTimeUseBuffer( * this->_pCommandPool );

    VulkanResult result;

    result = oneTimeUseBuffer.beginOneTimeUse();

    if ( result != VulkanResult :: VK_SUCCESS ) {
        return result;
    }

    VulkanPipelineStageFlags    sourceStage;
    VulkanPipelineStageFlags    destinationStage;
    VulkanAccessFlags           sourceAccessMask;
    VulkanAccessFlags           destinationAccessMask;
    VulkanImageAspectFlags      aspectFlags;

    aspectFlags =
            static_cast < VulkanImageAspectFlags > (
                    VulkanImageAspectFlagBits::VK_IMAGE_ASPECT_DEPTH_BIT | ( // NOLINT(clion-misra-cpp2008-4-5-2)
                        hasStencilComponent( this->_format )
                        ? VulkanImageAspectFlagBits::VK_IMAGE_ASPECT_STENCIL_BIT
                        : static_cast < VulkanImageAspectFlagBits > ( 0U )
                    )
            );

    if (
            this->_currentLayout    == VulkanImageLayout::VK_IMAGE_LAYOUT_UNDEFINED &&
            newLayout               == VulkanImageLayout::VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
    ) {
        sourceStage             = VulkanPipelineStageFlagBits::VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        destinationStage        = VulkanPipelineStageFlagBits::VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;

        sourceAccessMask        = 0U;
        destinationAccessMask   =
            VulkanAccessFlagBits::VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | // NOLINT(clion-misra-cpp2008-4-5-2)
            VulkanAccessFlagBits::VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
    } else {
        return VulkanResult::VK_ERROR_INITIALIZATION_FAILED;
    }

    VulkanImageMemoryBarrier barrier {};
    populateImageMemoryBarrier(
        & barrier,
        this->_currentLayout,
        newLayout,
        this->_image,
        sourceAccessMask,
        destinationAccessMask,
        aspectFlags
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

#include <sstream>
auto engine::VDepthBuffer::toString () const noexcept -> String {
    std::stringstream oss;

    oss <<"VDepthBuffer { " <<
        "handle = 0x" << std::hex << reinterpret_cast < AddressValueType > (this->_image) <<
        ", memory = 0x" <<  reinterpret_cast < AddressValueType > (this->_imageMemory) <<
        ", imageView = " << std::dec << this->_imageView.toString() <<
        ", currentLayout = " << static_cast < Size > (this->_currentLayout) <<
        ", pCommandPool = 0x" << std::hex << reinterpret_cast < AddressValueType > (this->_pCommandPool) <<
        ", sharingMode = " << std::dec << static_cast < Size > (this->_sharingMode) <<
        ", format = " << static_cast < Size > (this->_format) << " }";

    return oss.str();
}
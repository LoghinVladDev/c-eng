//
// Created by loghin on 01.01.2022.
//

#ifndef __C_ENG_VULKAN_CORE_CONFIG_HPP__
#define __C_ENG_VULKAN_CORE_CONFIG_HPP__ /* NOLINT(bugprone-reserved-identifier) */


namespace engine :: vulkan :: config {
    constexpr cds :: uint32 contextCount = 16U;

    constexpr cds :: uint32 validationFeatureEnableCount    = 32U;
    constexpr cds :: uint32 validationFeatureDisableCount   = 32U;
    constexpr cds :: uint32 validationCheckCount            = 16U;

    constexpr cds :: uint32 layerCount          = 128U;
    constexpr cds :: uint32 layerExtensionCount = 512U;

    constexpr cds :: uint32 physicalDeviceCount         = 8U;
    constexpr cds :: uint32 physicalDeviceSurfaceCount  = 32U;
    constexpr cds :: uint32 physicalDeviceGroupCount    = 8U;

    constexpr cds :: uint32 queueFamilyCount                    = 32U;
    constexpr cds :: uint32 queueFamilyQueueCount               = 256U;
    constexpr cds :: uint32 queueFamilyPerformanceCounterCount  = 16U;
    constexpr cds :: uint32 queueFamilyCreateInfoCount          = queueFamilyCount;

    constexpr cds :: uint32 surfaceFormatCount      = 512U;
    constexpr cds :: uint32 surfacePresentModeCount = 16U;

    constexpr cds :: uint32 viewFormatCount = 16U;

    constexpr cds :: uint32 swapChainImageCount = 256U;

    constexpr cds :: uint32 renderingInfoFormatsCount           = 256U;
    constexpr cds :: uint32 sampleCountAttachmentSamplesCount   = 256U;
    constexpr cds :: uint32 viewportDepthCount                  = 16U;

    constexpr cds :: uint32 submitInfoCount                 = 32U;
    constexpr cds :: uint32 pipelineStageFlagsCount         = 64U;
    constexpr cds :: uint32 submitSemaphoreInfoCount        = 16U;
    constexpr cds :: uint32 submitCommandBufferInfoCount    = 32U;
    constexpr cds :: uint32 waitSemaphoreCount              = 128U;

    constexpr cds :: uint32 memoryBarrierCount              = 32U;
    constexpr cds :: uint32 bufferMemoryBarrierCount        = memoryBarrierCount;
    constexpr cds :: uint32 imageMemoryBarrierCount         = memoryBarrierCount;

    constexpr cds :: uint32 dependencyInfoMemoryBarrierCount        = memoryBarrierCount;
    constexpr cds :: uint32 dependencyInfoBufferMemoryBarrierCount  = bufferMemoryBarrierCount;
    constexpr cds :: uint32 dependencyInfoImageMemoryBarrierCount   = imageMemoryBarrierCount;

    constexpr cds :: uint32 sampleLocationsInfoSampleLocationsCount = 512U;

    constexpr cds :: uint32 commandBufferWaitEventsDependencyInfoCount  = 16U;

    constexpr cds :: uint32 renderingInfoColorAttachmentCount               = 16U;
    constexpr cds :: uint32 deviceGroupRenderPassBeginDeviceRenderAreaCount = physicalDeviceGroupCount * 4U;

    constexpr cds :: uint32 renderPassInputAttachmentAspectReferenceCount       = 64U;
    constexpr cds :: uint32 renderPassAttachmentDescriptionCount                = 32U;
    constexpr cds :: uint32 renderPassSubpassDescriptionCount                   = 32U;
    constexpr cds :: uint32 renderPassSubpassDependencyCount                    = 32U;
    constexpr cds :: uint32 renderPassSubpassDescriptionInputAttachmentCount    = 128U;
    constexpr cds :: uint32 renderPassSubpassDescriptionColorAttachmentCount    = 128U;

    constexpr cds :: uint32 frameBufferAttachmentsImageInfoCount    = 256U;

    constexpr cds :: uint32 renderPassBeginInfoClearValueCount                  = 64U;
    constexpr cds :: uint32 renderPassSampleLocationsAttachmentInitialCount     = 32U;
    constexpr cds :: uint32 renderPassSampleLocationsPostSubpassCount           = 32U;

    constexpr cds :: uint32 subpassFragmentDensityMapOffsetEndInfoOffsetCount   = 256U;

    constexpr cds :: uint32 cooperativeMatrixPropertiesCount                    = 512U;
}

#if defined ( __C_ENG_USE_DEFENSIVE_PROGRAMMING ) || !defined(NDEBUG)

#define __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED true /* NOLINT(bugprone-reserved-identifier) */

#else

#define __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED false

#endif

#endif //__C_ENG_VULKAN_CORE_CONFIG_HPP__
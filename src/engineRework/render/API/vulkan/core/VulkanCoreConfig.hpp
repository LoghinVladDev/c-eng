//
// Created by loghin on 01.01.2022.
//

#ifndef __C_ENG_VULKAN_CORE_CONFIG_HPP__
#define __C_ENG_VULKAN_CORE_CONFIG_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#include <CDS/Types>

namespace engine :: vulkan :: config {

    enum class CoreDumpType {
        NoDump,
        DumpOnError,
        DumpAll
    };

    constexpr CoreDumpType  coreDumpType = CoreDumpType :: DumpOnError;

    constexpr cds :: uint32 contextCount = 16U;
    constexpr cds :: uint32 dumpParameterCount = 256U;

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

    constexpr cds :: uint32 pipelineCount                                       = 8U;
    constexpr cds :: uint32 pipelineStageCreationFeedbackCount                  = 64U;
    constexpr cds :: uint32 pipelineShaderStageCount                            = 16U;
    constexpr cds :: uint32 pipelineSpecializationMapEntryCount                 = 128U;
    constexpr cds :: uint32 pipelineDynamicStateCount                           = 256U;

    constexpr cds :: uint32 computePipelineCount                                = pipelineCount;
    constexpr cds :: uint32 computePipelineStageCreationFeedbackCount           = pipelineStageCreationFeedbackCount;
    constexpr cds :: uint32 computePipelineSpecializationMapEntryCount          = pipelineSpecializationMapEntryCount;

    constexpr cds :: uint32 graphicsPipelineCount                                   = pipelineCount;
    constexpr cds :: uint32 graphicsPipelineShaderStageCount                        = pipelineShaderStageCount;
    constexpr cds :: uint32 graphicsPipelineSpecializationMapEntryCount             = pipelineSpecializationMapEntryCount;
    constexpr cds :: uint32 graphicsPipelineVertexInputBindingCount                 = 32U;
    constexpr cds :: uint32 graphicsPipelineVertexInputAttributeCount               = 32U;
    constexpr cds :: uint32 graphicsPipelineVertexInputBindingDivisorCount          = 64U;
    constexpr cds :: uint32 graphicsPipelineViewportCount                           = 8U;
    constexpr cds :: uint32 graphicsPipelineScissorCount                            = 16U;
    constexpr cds :: uint32 graphicsPipelineViewportCustomSampleOrderCount          = 32U;
    constexpr cds :: uint32 graphicsPipelineViewportCustomSampleLocationCount       = 4U;
    constexpr cds :: uint32 graphicsPipelineViewportShadingRatePaletteEntryCount    = 8U;
    constexpr cds :: uint32 graphicsPipelineMultisampleSampleLocations              = 64U;
    constexpr cds :: uint32 graphicsPipelineColorBlendAttachmentCount               = 32U;
    constexpr cds :: uint32 graphicsPipelineShaderGroupCount                        = 6U;
    constexpr cds :: uint32 graphicsPipelineStageCreationFeedbackCount              = pipelineStageCreationFeedbackCount;
    constexpr cds :: uint32 graphicsPipelineDiscardRectanglesCount                  = 128U;
    constexpr cds :: uint32 graphicsPipelineDynamicRenderingColorAttachmentCount    = 128U;
    constexpr cds :: uint32 graphicsPipelineDynamicStateCount                       = pipelineDynamicStateCount;

    constexpr cds :: uint32 rayTracingPipelineCount                                 = pipelineCount;
    constexpr cds :: uint32 rayTracingPipelineStageCreationFeedbackCount            = pipelineStageCreationFeedbackCount;
    constexpr cds :: uint32 rayTracingPipelineShaderStageCount                      = pipelineShaderStageCount;
    constexpr cds :: uint32 rayTracingPipelineSpecializationMapEntryCount           = pipelineSpecializationMapEntryCount;
    constexpr cds :: uint32 rayTracingPipelineShaderGroupCount                      = 64U;
    constexpr cds :: uint32 rayTracingPipelineDynamicStateCount                     = pipelineDynamicStateCount;

    constexpr cds :: uint32 pipelineExecutableItemCount                             = 256U;
    constexpr cds :: uint32 pipelineExecutablePropertiesCount                       = pipelineExecutableItemCount;
    constexpr cds :: uint32 pipelineExecutableStatisticsCount                       = pipelineExecutableItemCount;
    constexpr cds :: uint32 pipelineExecutableInternalRepresentationCount           = pipelineExecutableItemCount;


    constexpr cds :: uint32 flushMappedRangeCount                                   = 2048U;

    constexpr cds :: uint32 videoProfileCount                                       = 128U;

    constexpr cds :: uint32 imageDrmFormatSubresourceLayoutCount                    = 32U;
    constexpr cds :: uint32 imageFormatListFormatCount                              = 128U;

    constexpr cds :: uint32 accelerationStructureGeometryCount                      = 256U;

    constexpr cds :: uint32 accelerationStructureNVidiaGeometryCount                = accelerationStructureGeometryCount;

    constexpr cds :: uint32 bindAccelerationStructureCount                          = 512U;
} // namespace engine :: vulkan :: config

#if defined ( __C_ENG_USE_DEFENSIVE_PROGRAMMING ) || ! defined ( NDEBUG )

#define __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED true /* NOLINT(bugprone-reserved-identifier,cert-dcl37-c) */

#else

#define __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED false

#endif

#endif //__C_ENG_VULKAN_CORE_CONFIG_HPP__
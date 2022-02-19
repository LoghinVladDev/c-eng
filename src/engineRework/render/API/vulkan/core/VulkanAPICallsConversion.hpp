//
// Created by loghin on 16.02.2022.
//

#ifndef C_ENG_VULKANAPICALLSCONVERSION_HPP
#define C_ENG_VULKANAPICALLSCONVERSION_HPP

#include <VulkanAPICallsPrivate.hpp>
#include <VulkanAPICallsTypes.hpp>

#define C_ENG_MAP_START     HEADER
#include <ObjectMapping.hpp>


namespace engine :: vulkan {

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    static inline auto toVulkanFormat (
            VkAllocationCallbacks                 * pDestination,
            Type ( AllocationCallbacks )    const * pSource
    ) noexcept -> VkAllocationCallbacks * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .pUserData              = pSource->pUserData,
                .pfnAllocation          = pSource->allocationCallback,
                .pfnReallocation        = pSource->reallocationCallback,
                .pfnFree                = pSource->freeCallback,
                .pfnInternalAllocation  = pSource->internalAllocationNotificationCallback,
                .pfnInternalFree        = pSource->internalFreeNotificationCallback
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_REPORT_AVAILABLE
    static inline auto toVulkanFormat (
            VkDebugReportCallbackCreateInfoEXT        * pDestination,
            Type ( DebugReportCreateInfo )      const * pSource
    ) noexcept -> VkDebugReportCallbackCreateInfoEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType          = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT,
                .pNext          = nullptr,
                .flags          = pSource->flags,
                .pfnCallback    = pSource->callback,
                .pUserData      = pSource->pUserData
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_UTILS_AVAILABLE
    static inline auto toVulkanFormat (
            VkDebugUtilsMessengerCreateInfoEXT         * pDestination,
            Type ( DebugMessengerCreateInfo )    const * pSource
    ) noexcept -> VkDebugUtilsMessengerCreateInfoEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
                .pNext                  = nullptr,
                .flags                  = pSource->flags,
                .messageSeverity        = pSource->messageSeverityFlags,
                .messageType            = pSource->messageTypeFlags,
                .pfnUserCallback        = pSource->callback,
                .pUserData              = pSource->pCallbackUserData
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_FEATURES_AVAILABLE
    static inline auto toVulkanFormat (
            VkValidationFeaturesEXT           * pDestination,
            Type ( ValidationFeatures ) const * pSource
    ) noexcept -> VkValidationFeaturesEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                          = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT,
                .pNext                          = nullptr,
                .enabledValidationFeatureCount  = pSource->enabledValidationFeatureCount,
                .pEnabledValidationFeatures     = nullptr,
                .disabledValidationFeatureCount = pSource->disabledValidationFeatureCount,
                .pDisabledValidationFeatures    = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_FLAGS_AVAILABLE
    static inline auto toVulkanFormat (
            VkValidationFlagsEXT              * pDestination,
            Type ( ValidationFlags )    const * pSource
    ) noexcept -> VkValidationFlagsEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                          = VK_STRUCTURE_TYPE_VALIDATION_FLAGS_EXT,
                .pNext                          = nullptr,
                .disabledValidationCheckCount   = pSource->disabledValidationCheckCount,
                .pDisabledValidationChecks      = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceProperties )         * pDestination,
            VkPhysicalDeviceProperties          const * pSource
    ) noexcept -> Type ( PhysicalDeviceProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->apiVersion                                                 = vulkan :: uInt32ToInstanceVersion ( pSource->apiVersion );
        pDestination->driverVersion                                              = pSource->driverVersion;
        pDestination->vendorID                                                   = pSource->vendorID;
        pDestination->deviceID                                                   = pSource->deviceID;
        pDestination->deviceType                                                 = static_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceType ) > ( pSource->deviceType );

        pDestination->limits.maxImageDimension1D                                 = pSource->limits.maxImageDimension1D;
        pDestination->limits.maxImageDimension2D                                 = pSource->limits.maxImageDimension2D;
        pDestination->limits.maxImageDimension3D                                 = pSource->limits.maxImageDimension3D;
        pDestination->limits.maxImageDimensionCube                               = pSource->limits.maxImageDimensionCube;
        pDestination->limits.maxImageArrayLayers                                 = pSource->limits.maxImageArrayLayers;

        pDestination->limits.maxTexelBufferElements                              = pSource->limits.maxTexelBufferElements;

        pDestination->limits.maxUniformBufferRange                               = pSource->limits.maxUniformBufferRange;
        pDestination->limits.maxStorageBufferRange                               = pSource->limits.maxStorageBufferRange;

        pDestination->limits.maxPushConstantsSize                                = pSource->limits.maxPushConstantsSize;

        pDestination->limits.maxMemoryAllocationCount                            = pSource->limits.maxMemoryAllocationCount;
        pDestination->limits.maxSamplerAllocationCount                           = pSource->limits.maxSamplerAllocationCount;

        pDestination->limits.bufferImageGranularity                              = pSource->limits.bufferImageGranularity;
        pDestination->limits.sparseAddressSpaceSize                              = pSource->limits.sparseAddressSpaceSize;

        pDestination->limits.maxBoundDescriptorSets                              = pSource->limits.maxBoundDescriptorSets;

        pDestination->limits.maxPerStageDescriptorSamplers                       = pSource->limits.maxPerStageDescriptorSamplers;
        pDestination->limits.maxPerStageDescriptorUniformBuffers                 = pSource->limits.maxPerStageDescriptorUniformBuffers;
        pDestination->limits.maxPerStageDescriptorStorageBuffers                 = pSource->limits.maxPerStageDescriptorStorageBuffers;
        pDestination->limits.maxPerStageDescriptorSampledImages                  = pSource->limits.maxPerStageDescriptorSampledImages;
        pDestination->limits.maxPerStageDescriptorStorageImages                  = pSource->limits.maxPerStageDescriptorStorageImages;
        pDestination->limits.maxPerStageDescriptorInputAttachments               = pSource->limits.maxPerStageDescriptorInputAttachments;
        pDestination->limits.maxPerStageResources                                = pSource->limits.maxPerStageResources;

        pDestination->limits.maxDescriptorSetSamplers                            = pSource->limits.maxDescriptorSetSamplers;
        pDestination->limits.maxDescriptorSetUniformBuffers                      = pSource->limits.maxDescriptorSetUniformBuffers;
        pDestination->limits.maxDescriptorSetUniformBuffersDynamic               = pSource->limits.maxDescriptorSetUniformBuffersDynamic;
        pDestination->limits.maxDescriptorSetStorageBuffers                      = pSource->limits.maxDescriptorSetStorageBuffers;
        pDestination->limits.maxDescriptorSetStorageBuffersDynamic               = pSource->limits.maxDescriptorSetStorageBuffersDynamic;
        pDestination->limits.maxDescriptorSetSampledImages                       = pSource->limits.maxDescriptorSetSampledImages;
        pDestination->limits.maxDescriptorSetStorageImages                       = pSource->limits.maxDescriptorSetStorageImages;
        pDestination->limits.maxDescriptorSetInputAttachments                    = pSource->limits.maxDescriptorSetInputAttachments;

        pDestination->limits.maxVertexInputAttributes                            = pSource->limits.maxVertexInputAttributes;
        pDestination->limits.maxVertexInputBindings                              = pSource->limits.maxVertexInputBindings;
        pDestination->limits.maxVertexInputAttributeOffset                       = pSource->limits.maxVertexInputAttributeOffset;
        pDestination->limits.maxVertexInputBindingStride                         = pSource->limits.maxVertexInputBindingStride;
        pDestination->limits.maxVertexOutputComponents                           = pSource->limits.maxVertexOutputComponents;

        pDestination->limits.maxTessellationGenerationLevel                      = pSource->limits.maxTessellationGenerationLevel;
        pDestination->limits.maxTessellationPatchSize                            = pSource->limits.maxTessellationPatchSize;
        pDestination->limits.maxTessellationControlPerVertexInputComponents      = pSource->limits.maxTessellationControlPerVertexInputComponents;
        pDestination->limits.maxTessellationControlPerVertexOutputComponents     = pSource->limits.maxTessellationControlPerVertexOutputComponents;
        pDestination->limits.maxTessellationControlPerPatchOutputComponents      = pSource->limits.maxTessellationControlPerPatchOutputComponents;
        pDestination->limits.maxTessellationControlTotalOutputComponents         = pSource->limits.maxTessellationControlTotalOutputComponents;
        pDestination->limits.maxTessellationEvaluationInputComponents            = pSource->limits.maxTessellationEvaluationInputComponents;
        pDestination->limits.maxTessellationEvaluationOutputComponents           = pSource->limits.maxTessellationEvaluationOutputComponents;

        pDestination->limits.maxGeometryShaderInvocations                        = pSource->limits.maxGeometryShaderInvocations;
        pDestination->limits.maxGeometryInputComponents                          = pSource->limits.maxGeometryInputComponents;
        pDestination->limits.maxGeometryOutputComponents                         = pSource->limits.maxGeometryOutputComponents;
        pDestination->limits.maxGeometryOutputVertices                           = pSource->limits.maxGeometryOutputVertices;
        pDestination->limits.maxGeometryTotalOutputComponents                    = pSource->limits.maxGeometryTotalOutputComponents;

        pDestination->limits.maxFragmentInputComponents                          = pSource->limits.maxFragmentInputComponents;
        pDestination->limits.maxFragmentOutputAttachments                        = pSource->limits.maxFragmentOutputAttachments;
        pDestination->limits.maxFragmentDualSourceAttachments                    = pSource->limits.maxFragmentDualSrcAttachments;
        pDestination->limits.maxFragmentCombinedOutputResources                  = pSource->limits.maxFragmentCombinedOutputResources;

        pDestination->limits.maxComputeSharedMemorySize                          = pSource->limits.maxComputeSharedMemorySize;
        pDestination->limits.maxComputeWorkGroupInvocations                      = pSource->limits.maxComputeWorkGroupInvocations;

        pDestination->limits.subPixelPrecisionBits                               = pSource->limits.subPixelPrecisionBits;
        pDestination->limits.subTexelPrecisionBits                               = pSource->limits.subTexelPrecisionBits;

        pDestination->limits.mipmapPrecisionBits                                 = pSource->limits.mipmapPrecisionBits;

        pDestination->limits.maxDrawIndexedIndexValue                            = pSource->limits.maxDrawIndexedIndexValue;
        pDestination->limits.maxDrawIndirectCount                                = pSource->limits.maxDrawIndirectCount;

        pDestination->limits.maxSamplerLodBias                                   = pSource->limits.maxSamplerLodBias;
        pDestination->limits.maxSamplerAnisotropy                                = pSource->limits.maxSamplerAnisotropy;

        pDestination->limits.maxViewports                                        = pSource->limits.maxViewports;
        pDestination->limits.viewportSubPixelBits                                = pSource->limits.viewportSubPixelBits;

        pDestination->limits.minMemoryMapAlignment                               = pSource->limits.minMemoryMapAlignment;

        pDestination->limits.minTexelBufferOffsetAlignment                       = pSource->limits.minTexelBufferOffsetAlignment;
        pDestination->limits.minUniformBufferOffsetAlignment                     = pSource->limits.minUniformBufferOffsetAlignment;
        pDestination->limits.minStorageBufferOffsetAlignment                     = pSource->limits.minStorageBufferOffsetAlignment;

        pDestination->limits.minTexelOffset                                      = pSource->limits.minTexelOffset;
        pDestination->limits.maxTexelOffset                                      = pSource->limits.maxTexelOffset;
        pDestination->limits.minTexelGatherOffset                                = pSource->limits.minTexelGatherOffset;
        pDestination->limits.maxTexelGatherOffset                                = pSource->limits.maxTexelGatherOffset;

        pDestination->limits.minInterpolationOffset                              = pSource->limits.minInterpolationOffset;
        pDestination->limits.maxInterpolationOffset                              = pSource->limits.maxInterpolationOffset;
        pDestination->limits.subPixelInterpolationOffsetBits                     = pSource->limits.subPixelInterpolationOffsetBits;

        pDestination->limits.maxFramebufferWidth                                 = pSource->limits.maxFramebufferWidth;
        pDestination->limits.maxFramebufferHeight                                = pSource->limits.maxFramebufferHeight;
        pDestination->limits.maxFramebufferLayers                                = pSource->limits.maxFramebufferLayers;

        pDestination->limits.framebufferColorSampleCounts                        = pSource->limits.framebufferColorSampleCounts;
        pDestination->limits.framebufferDepthSampleCounts                        = pSource->limits.framebufferDepthSampleCounts;
        pDestination->limits.framebufferStencilSampleCounts                      = pSource->limits.framebufferStencilSampleCounts;
        pDestination->limits.framebufferNoAttachmentsSampleCounts                = pSource->limits.framebufferNoAttachmentsSampleCounts;

        pDestination->limits.maxColorAttachments                                 = pSource->limits.maxColorAttachments;

        pDestination->limits.sampledImageColorSampleCounts                       = pSource->limits.sampledImageColorSampleCounts;
        pDestination->limits.sampledImageIntegerSampleCounts                     = pSource->limits.sampledImageIntegerSampleCounts;
        pDestination->limits.sampledImageDepthSampleCounts                       = pSource->limits.sampledImageDepthSampleCounts;
        pDestination->limits.sampledImageStencilSampleCounts                     = pSource->limits.sampledImageStencilSampleCounts;
        pDestination->limits.storageImageSampleCounts                            = pSource->limits.storageImageSampleCounts;

        pDestination->limits.maxSampleMaskWords                                  = pSource->limits.maxSampleMaskWords;

        pDestination->limits.timestampComputeAndGraphics                         = pSource->limits.timestampComputeAndGraphics;
        pDestination->limits.timestampPeriod                                     = pSource->limits.timestampPeriod;

        pDestination->limits.maxClipDistances                                    = pSource->limits.maxClipDistances;
        pDestination->limits.maxCullDistances                                    = pSource->limits.maxCullDistances;
        pDestination->limits.maxCombinedClipAndCullDistances                     = pSource->limits.maxCombinedClipAndCullDistances;

        pDestination->limits.discreteQueuePriorities                             = pSource->limits.discreteQueuePriorities;

        pDestination->limits.pointSizeGranularity                                = pSource->limits.pointSizeGranularity;
        pDestination->limits.lineWidthGranularity                                = pSource->limits.lineWidthGranularity;
        pDestination->limits.strictLines                                         = pSource->limits.strictLines;

        pDestination->limits.standardSampleLocations                             = pSource->limits.standardSampleLocations;

        pDestination->limits.optimalBufferCopyOffsetAlignment                    = pSource->limits.optimalBufferCopyOffsetAlignment;
        pDestination->limits.optimalBufferCopyRowPitchAlignment                  = pSource->limits.optimalBufferCopyRowPitchAlignment;

        pDestination->limits.nonCoherentAtomSize                                 = pSource->limits.nonCoherentAtomSize;

        pDestination->sparseProperties.residencyStandard2DBlockShape             = pSource->sparseProperties.residencyStandard2DBlockShape;
        pDestination->sparseProperties.residencyStandard2DMultisampleBlockShape  = pSource->sparseProperties.residencyStandard2DMultisampleBlockShape;
        pDestination->sparseProperties.residencyStandard3DBlockShape             = pSource->sparseProperties.residencyStandard3DBlockShape;
        pDestination->sparseProperties.residencyAlignedMipSize                   = pSource->sparseProperties.residencyAlignedMipSize;
        pDestination->sparseProperties.residencyNonResidentStrict                = pSource->sparseProperties.residencyNonResidentStrict;

        (void) std :: memcpy ( & pDestination->deviceName[0],                         & pSource->deviceName[0],                      static_cast < cds :: uint32 > ( VK_MAX_PHYSICAL_DEVICE_NAME_SIZE ) ); // NOLINT(clion-misra-cpp2008-5-2-12)
        (void) std :: memcpy ( & pDestination->pipelineCacheUUID[0],                  & pSource->pipelineCacheUUID[0],               VK_UUID_SIZE ); // NOLINT(clion-misra-cpp2008-5-2-12)

        (void) std :: memcpy ( & pDestination->limits.maxComputeWorkGroupCount[0],    & pSource->limits.maxComputeWorkGroupCount[0], sizeof ( pSource->limits.maxComputeWorkGroupCount[0] ) * 3U ); // NOLINT(clion-misra-cpp2008-5-2-12)
        (void) std :: memcpy ( & pDestination->limits.maxComputeWorkGroupSize[0],     & pSource->limits.maxComputeWorkGroupSize[0],  sizeof ( pSource->limits.maxComputeWorkGroupSize[0] ) * 3U ); // NOLINT(clion-misra-cpp2008-5-2-12)

        (void) std :: memcpy ( & pDestination->limits.maxViewportDimensions[0],       & pSource->limits.maxViewportDimensions[0],    sizeof ( pSource->limits.maxViewportDimensions[0] ) * 2U ); // NOLINT(clion-misra-cpp2008-5-2-12)
        (void) std :: memcpy ( & pDestination->limits.viewportBoundsRange[0],         & pSource->limits.viewportBoundsRange[0],      sizeof ( pSource->limits.viewportBoundsRange[0] ) * 2U ); // NOLINT(clion-misra-cpp2008-5-2-12)

        (void) std :: memcpy ( & pDestination->limits.pointSizeRange[0],              & pSource->limits.pointSizeRange[0],           sizeof ( pSource->limits.pointSizeRange[0] ) * 2U ); // NOLINT(clion-misra-cpp2008-5-2-12)
        (void) std :: memcpy ( & pDestination->limits.lineWidthRange[0],              & pSource->limits.lineWidthRange[0],           sizeof ( pSource->limits.lineWidthRange[0] ) * 2U ); // NOLINT(clion-misra-cpp2008-5-2-12)

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceExtendedProperties )         * pDestination,
            VkPhysicalDeviceProperties2                 const * pSource
    ) noexcept -> Type ( PhysicalDeviceExtendedProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceProperties;
        pDestination->pNext = nullptr;

        (void) fromVulkanFormat ( & pDestination->properties, & pSource->properties );

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    static inline auto toVulkanFormat (
            VkApplicationInfo                 * pDestination,
            Type ( ApplicationInfo )    const * pSource
    ) noexcept -> VkApplicationInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr ) {
            return nullptr;
        }

#endif

        if ( pSource == nullptr ) {
            return nullptr;
        }

        * pDestination = {
                .sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO,
                .pNext              = nullptr,
                .pApplicationName   = pSource->name,
                .applicationVersion = instanceVersionToUInt32 ( pSource->version ),
                .pEngineName        = pSource->engineName,
                .engineVersion      = instanceVersionToUInt32 ( pSource->engineVersion ),
                .apiVersion         = instanceVersionToUInt32 ( pSource->apiVersion )
        };

        return pDestination;
    }

    static inline auto toVulkanFormat (
            VkInstanceCreateInfo              * pDestination,
            Type ( InstanceCreateInfo ) const * pSource
    ) noexcept -> VkInstanceCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if (
                pDestination    == nullptr ||
                pSource         == nullptr
        ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                      = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
                .pNext                      = nullptr,
                .flags                      = pSource->flags,
                .pApplicationInfo           = pDestination->pApplicationInfo,
                .enabledLayerCount          = pSource->enabledLayerCount,
                .ppEnabledLayerNames        = pSource->pEnabledLayerNames,
                .enabledExtensionCount      = pSource->enabledExtensionCount,
                .ppEnabledExtensionNames    = pSource->pEnabledExtensionNames
        };

        return pDestination;
    }

    static inline auto prepareContext (
            CreateInstanceContext             * pContext,
            Type ( InstanceCreateInfo ) const * pSource
    ) noexcept -> VkInstanceCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pContext->instance.pApplicationInfo = toVulkanFormat ( & pContext->applicationInfo, pSource->pApplicationInfo );

        auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource );
        auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->instance, pSource ) );

        while ( pCurrent != nullptr ) {

            switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_REPORT_AVAILABLE
                case StructureTypeDebugReportCallbackCreateInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->debugReport,
                                    reinterpret_cast < Type ( DebugReportCreateInfo ) const * > ( pCurrent )
                            )
                    );
                    break;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_UTILS_AVAILABLE
                case StructureTypeDebugUtilsMessengerCreateInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->debugMessenger,
                                    reinterpret_cast < Type ( DebugMessengerCreateInfo ) const * > ( pCurrent )
                            )
                    );
                    break;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_FEATURES_AVAILABLE
                case StructureTypeValidationFeatures: {

                    auto pValidationFeatures = reinterpret_cast < Type ( ValidationFeatures ) const * > ( pCurrent );
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->validationFeatures,
                                    pValidationFeatures
                            )
                    );

                    if ( pContext->validationFeatures.enabledValidationFeatureCount > __C_ENG_VULKAN_CORE_VALIDATION_FEATURE_ENABLE_MAX_COUNT ) {
                        pContext->validationFeatures.enabledValidationFeatureCount = __C_ENG_VULKAN_CORE_VALIDATION_FEATURE_ENABLE_MAX_COUNT;
                        pContext->error = ResultErrorConfigurationArraySizeSmall;
                    }

                    for ( cds :: uint32 i = 0U; i < pContext->validationFeatures.enabledValidationFeatureCount; ++ i ) {
                        pContext->validationFeatureEnables[i] = static_cast < VkValidationFeatureEnableEXT > ( pValidationFeatures->pEnabledValidationFeatures[i] );
                    }

                    pContext->validationFeatures.pEnabledValidationFeatures = & pContext->validationFeatureEnables[0];

                    if ( pContext->validationFeatures.disabledValidationFeatureCount > __C_ENG_VULKAN_CORE_VALIDATION_FEATURE_DISABLE_MAX_COUNT ) {
                        pContext->validationFeatures.disabledValidationFeatureCount = __C_ENG_VULKAN_CORE_VALIDATION_FEATURE_DISABLE_MAX_COUNT;
                        pContext->error = ResultErrorConfigurationArraySizeSmall;
                    }

                    for ( cds :: uint32 i = 0U; i < pContext->validationFeatures.disabledValidationFeatureCount; ++ i ) {
                        pContext->validationFeatureDisables[i] = static_cast < VkValidationFeatureDisableEXT > ( pValidationFeatures->pDisabledValidationFeatures[i] );
                    }

                    pContext->validationFeatures.pDisabledValidationFeatures = & pContext->validationFeatureDisables[0];

                    break;
                }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_FLAGS_AVAILABLE
                case StructureTypeValidationFlags: {

                    auto pValidationFlags = reinterpret_cast < Type ( ValidationFlags ) const * > ( pCurrent );
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->validationFlags,
                                    pValidationFlags
                            )
                    );

                    if ( pValidationFlags->disabledValidationCheckCount > __C_ENG_VULKAN_CORE_VALIDATION_CHECK_MAX_COUNT ) {
                        pContext->validationFlags.disabledValidationCheckCount = __C_ENG_VULKAN_CORE_VALIDATION_CHECK_MAX_COUNT;
                        pContext->error = ResultErrorConfigurationArraySizeSmall;
                    }

                    for ( cds :: uint32 i = 0U; i < pContext->validationFlags.disabledValidationCheckCount; ++ i ) {
                        pContext->validationChecks[i] = static_cast <VkValidationCheckEXT > ( pValidationFlags->pDisabledValidationChecks[i] );
                    }

                    pContext->validationFlags.pDisabledValidationChecks = & pContext->validationChecks[0];

                    break;
                }
#endif

                default:
                    break;
            }

            pCurrentVk  = pCurrentVk->pNext != nullptr ? pCurrentVk->pNext : pCurrentVk;
            pCurrent    = pCurrent->pNext;
        }

        pCurrentVk->pNext = nullptr;

        return & pContext->instance;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto fromVulkanFormat (
            Type ( LayerProperties )      * pDestination,
            VkLayerProperties       const * pSource
    ) noexcept -> Type ( LayerProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        (void) std :: memcpy ( & pDestination->layerName[0],    & pSource->layerName[0],    VK_MAX_EXTENSION_NAME_SIZE );
        (void) std :: memcpy ( & pDestination->description[0],  & pSource->description[0],  VK_MAX_DESCRIPTION_SIZE );
        pDestination->implementationVersion = pSource->implementationVersion;
        pDestination->specVersion           = uInt32ToInstanceVersion ( pSource->specVersion );

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto fromVulkanFormat (
            Type ( ExtensionProperties )      * pDestination,
            VkExtensionProperties       const * pSource
    ) noexcept -> Type ( ExtensionProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif
        (void) std :: memcpy ( & pDestination->name[0], & pSource->extensionName[0], VK_MAX_EXTENSION_NAME_SIZE );
        pDestination->specVersion = pSource->specVersion;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
    auto fromVulkanFormat (
            Type ( PerformanceCounter )         * pDestination,
            VkPerformanceCounterKHR       const * pSource
    ) noexcept -> Type ( PerformanceCounter ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePerformanceCounter;
        pDestination->pNext         = nullptr;
        pDestination->unit          = static_cast < Type ( PerformanceCounterUnit ) > ( pSource->unit );
        pDestination->scope         = static_cast < Type ( PerformanceCounterScope ) > ( pSource->scope );
        pDestination->storage       = static_cast < Type ( PerformanceCounterStorage ) > ( pSource->storage );
        (void) std :: memcpy ( & pDestination->uuid[0], & pSource->uuid[0], sizeof ( pDestination->uuid[0] ) * VK_UUID_SIZE );

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
    auto fromVulkanFormat (
            Type ( PerformanceCounterDescription )         * pDestination,
            VkPerformanceCounterDescriptionKHR       const * pSource
    ) noexcept -> Type ( PerformanceCounterDescription ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePerformanceCounterDescription;
        pDestination->pNext         = nullptr;
        pDestination->flags         = static_cast < Type ( PerformanceCounterDescriptionFlags ) > ( pSource->flags );
        (void) std :: memcpy ( & pDestination->name[0],         & pSource->name[0],         sizeof ( pDestination->name[0] ) * VK_MAX_DESCRIPTION_SIZE );
        (void) std :: memcpy ( & pDestination->category[0],     & pSource->category[0],     sizeof ( pDestination->category[0] ) * VK_MAX_DESCRIPTION_SIZE );
        (void) std :: memcpy ( & pDestination->description[0],  & pSource->description[0],  sizeof ( pDestination->description[0] ) * VK_MAX_DESCRIPTION_SIZE );

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceGroupProperties )        * pDestination,
            VkPhysicalDeviceGroupProperties         const * pSource
    ) noexcept -> Type ( PhysicalDeviceGroupProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType         = vulkan :: StructureTypePhysicalDeviceGroupProperties;
        pDestination->pNext                 = nullptr;
        pDestination->physicalDeviceCount   = pSource->physicalDeviceCount;
        pDestination->subsetAllocation      = pSource->subsetAllocation;

        (void) std :: memcpy ( & pDestination->physicalDevices[0], & pSource->physicalDevices[0], sizeof ( pSource->physicalDevices[0] ) * VK_MAX_DEVICE_GROUP_SIZE ); // NOLINT(bugprone-sizeof-expression)

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEVICE_MEMORY_REPORT_AVAILABLE
    static inline auto toVulkanFormat (
            VkDeviceDeviceMemoryReportCreateInfoEXT               * pDestination,
            Type ( DeviceDeviceMemoryReportCreateInfo )     const * pSource
    ) noexcept -> VkDeviceDeviceMemoryReportCreateInfoEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType             = VK_STRUCTURE_TYPE_DEVICE_DEVICE_MEMORY_REPORT_CREATE_INFO_EXT;
        pDestination->pNext             = nullptr;

        pDestination->flags             = pSource->flags;
        pDestination->pfnUserCallback   = pSource->callback;
        pDestination->pUserData         = pSource->pUserData;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTICS_CONFIG_AVAILABLE
    static inline auto toVulkanFormat (
            VkDeviceDiagnosticsConfigCreateInfoNV                     * pDestination,
            Type ( DeviceDiagnosticsConfigCreateInfoNVidia )    const * pSource
    ) noexcept -> VkDeviceDiagnosticsConfigCreateInfoNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType             = VK_STRUCTURE_TYPE_DEVICE_DIAGNOSTICS_CONFIG_CREATE_INFO_NV;
        pDestination->pNext             = nullptr;

        pDestination->flags             = pSource->flags;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DEVICE_GROUP_AVAILABLE
    static inline auto toVulkanFormat (
            VkDeviceGroupDeviceCreateInfo_t               * pDestination,
            Type ( DeviceGroupDeviceCreateInfo )    const * pSource
    ) noexcept -> VkDeviceGroupDeviceCreateInfo_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType                 = VK_STRUCTURE_TYPE_DEVICE_GROUP_DEVICE_CREATE_INFO;
        pDestination->pNext                 = nullptr;

        pDestination->physicalDeviceCount   = pSource->physicalDeviceCount;
        pDestination->pPhysicalDevices      = pSource->pPhysicalDevices;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_MEMORY_OVERALLOCATION_BEHAVIOUR_AVAILABLE
    static inline auto toVulkanFormat (
            VkDeviceMemoryOverallocationCreateInfoAMD                 * pDestination,
            Type ( DeviceMemoryOverallocationCreateInfoAMD )    const * pSource
    ) noexcept -> VkDeviceMemoryOverallocationCreateInfoAMD * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType                     = VK_STRUCTURE_TYPE_DEVICE_MEMORY_OVERALLOCATION_CREATE_INFO_AMD;
        pDestination->pNext                     = nullptr;

        pDestination->overallocationBehavior    = static_cast < VkMemoryOverallocationBehaviorAMD > ( pSource->overallocationBehavior );

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    static inline auto toVulkanFormat (
            VkDevicePrivateDataCreateInfo_t               * pDestination,
            Type ( DevicePrivateDataCreateInfo )    const * pSource
    ) noexcept -> VkDevicePrivateDataCreateInfo_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType                         = VK_STRUCTURE_TYPE_DEVICE_PRIVATE_DATA_CREATE_INFO_EXT;
        pDestination->pNext                         = nullptr;

        pDestination->privateDataSlotRequestCount   = pSource->privateDataSlotRequestCount;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceFeatures              * pDestination,
            Type ( PhysicalDeviceFeatures ) const * pSource
    ) noexcept -> VkPhysicalDeviceFeatures * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->robustBufferAccess                        = pSource->robustBufferAccess;
        pDestination->fullDrawIndexUint32                       = pSource->fullDrawIndexUint32;
        pDestination->imageCubeArray                            = pSource->imageCubeArray;
        pDestination->independentBlend                          = pSource->independentBlend;
        pDestination->geometryShader                            = pSource->geometryShader;
        pDestination->tessellationShader                        = pSource->tessellationShader;
        pDestination->sampleRateShading                         = pSource->sampleRateShading;
        pDestination->dualSrcBlend                              = pSource->dualSrcBlend;
        pDestination->logicOp                                   = pSource->logicOp;
        pDestination->multiDrawIndirect                         = pSource->multiDrawIndirect;
        pDestination->drawIndirectFirstInstance                 = pSource->drawIndirectFirstInstance;
        pDestination->depthClamp                                = pSource->depthClamp;
        pDestination->depthBiasClamp                            = pSource->depthBiasClamp;
        pDestination->fillModeNonSolid                          = pSource->fillModeNonSolid;
        pDestination->depthBounds                               = pSource->depthBounds;
        pDestination->wideLines                                 = pSource->wideLines;
        pDestination->largePoints                               = pSource->largePoints;
        pDestination->alphaToOne                                = pSource->alphaToOne;
        pDestination->multiViewport                             = pSource->multiViewport;
        pDestination->samplerAnisotropy                         = pSource->samplerAnisotropy;
        pDestination->textureCompressionETC2                    = pSource->textureCompressionETC2;
        pDestination->textureCompressionASTC_LDR                = pSource->textureCompressionASTC_LDR;
        pDestination->textureCompressionBC                      = pSource->textureCompressionBC;
        pDestination->occlusionQueryPrecise                     = pSource->occlusionQueryPrecise;
        pDestination->pipelineStatisticsQuery                   = pSource->pipelineStatisticsQuery;
        pDestination->vertexPipelineStoresAndAtomics            = pSource->vertexPipelineStoresAndAtomics;
        pDestination->fragmentStoresAndAtomics                  = pSource->fragmentStoresAndAtomics;
        pDestination->shaderTessellationAndGeometryPointSize    = pSource->shaderTessellationAndGeometryPointSize;
        pDestination->shaderImageGatherExtended                 = pSource->shaderImageGatherExtended;
        pDestination->shaderStorageImageExtendedFormats         = pSource->shaderStorageImageExtendedFormats;
        pDestination->shaderStorageImageMultisample             = pSource->shaderStorageImageMultisample;
        pDestination->shaderStorageImageReadWithoutFormat       = pSource->shaderStorageImageReadWithoutFormat;
        pDestination->shaderStorageImageWriteWithoutFormat      = pSource->shaderStorageImageWriteWithoutFormat;
        pDestination->shaderUniformBufferArrayDynamicIndexing   = pSource->shaderUniformBufferArrayDynamicIndexing;
        pDestination->shaderSampledImageArrayDynamicIndexing    = pSource->shaderSampledImageArrayDynamicIndexing;
        pDestination->shaderStorageBufferArrayDynamicIndexing   = pSource->shaderStorageBufferArrayDynamicIndexing;
        pDestination->shaderStorageImageArrayDynamicIndexing    = pSource->shaderStorageImageArrayDynamicIndexing;
        pDestination->shaderClipDistance                        = pSource->shaderClipDistance;
        pDestination->shaderCullDistance                        = pSource->shaderCullDistance;
        pDestination->shaderFloat64                             = pSource->shaderFloat64;
        pDestination->shaderInt64                               = pSource->shaderInt64;
        pDestination->shaderInt16                               = pSource->shaderInt16;
        pDestination->shaderResourceResidency                   = pSource->shaderResourceResidency;
        pDestination->shaderResourceMinLod                      = pSource->shaderResourceMinLod;
        pDestination->sparseBinding                             = pSource->sparseBinding;
        pDestination->sparseResidencyBuffer                     = pSource->sparseResidencyBuffer;
        pDestination->sparseResidencyImage2D                    = pSource->sparseResidencyImage2D;
        pDestination->sparseResidencyImage3D                    = pSource->sparseResidencyImage3D;
        pDestination->sparseResidency2Samples                   = pSource->sparseResidency2Samples;
        pDestination->sparseResidency4Samples                   = pSource->sparseResidency4Samples;
        pDestination->sparseResidency8Samples                   = pSource->sparseResidency8Samples;
        pDestination->sparseResidency16Samples                  = pSource->sparseResidency16Samples;
        pDestination->sparseResidencyAliased                    = pSource->sparseResidencyAliased;
        pDestination->variableMultisampleRate                   = pSource->variableMultisampleRate;
        pDestination->inheritedQueries                          = pSource->inheritedQueries;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceFeatures )       * pDestination,
            VkPhysicalDeviceFeatures        const * pSource
    ) noexcept -> Type ( PhysicalDeviceFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->robustBufferAccess                        = pSource->robustBufferAccess;
        pDestination->fullDrawIndexUint32                       = pSource->fullDrawIndexUint32;
        pDestination->imageCubeArray                            = pSource->imageCubeArray;
        pDestination->independentBlend                          = pSource->independentBlend;
        pDestination->geometryShader                            = pSource->geometryShader;
        pDestination->tessellationShader                        = pSource->tessellationShader;
        pDestination->sampleRateShading                         = pSource->sampleRateShading;
        pDestination->dualSrcBlend                              = pSource->dualSrcBlend;
        pDestination->logicOp                                   = pSource->logicOp;
        pDestination->multiDrawIndirect                         = pSource->multiDrawIndirect;
        pDestination->drawIndirectFirstInstance                 = pSource->drawIndirectFirstInstance;
        pDestination->depthClamp                                = pSource->depthClamp;
        pDestination->depthBiasClamp                            = pSource->depthBiasClamp;
        pDestination->fillModeNonSolid                          = pSource->fillModeNonSolid;
        pDestination->depthBounds                               = pSource->depthBounds;
        pDestination->wideLines                                 = pSource->wideLines;
        pDestination->largePoints                               = pSource->largePoints;
        pDestination->alphaToOne                                = pSource->alphaToOne;
        pDestination->multiViewport                             = pSource->multiViewport;
        pDestination->samplerAnisotropy                         = pSource->samplerAnisotropy;
        pDestination->textureCompressionETC2                    = pSource->textureCompressionETC2;
        pDestination->textureCompressionASTC_LDR                = pSource->textureCompressionASTC_LDR;
        pDestination->textureCompressionBC                      = pSource->textureCompressionBC;
        pDestination->occlusionQueryPrecise                     = pSource->occlusionQueryPrecise;
        pDestination->pipelineStatisticsQuery                   = pSource->pipelineStatisticsQuery;
        pDestination->vertexPipelineStoresAndAtomics            = pSource->vertexPipelineStoresAndAtomics;
        pDestination->fragmentStoresAndAtomics                  = pSource->fragmentStoresAndAtomics;
        pDestination->shaderTessellationAndGeometryPointSize    = pSource->shaderTessellationAndGeometryPointSize;
        pDestination->shaderImageGatherExtended                 = pSource->shaderImageGatherExtended;
        pDestination->shaderStorageImageExtendedFormats         = pSource->shaderStorageImageExtendedFormats;
        pDestination->shaderStorageImageMultisample             = pSource->shaderStorageImageMultisample;
        pDestination->shaderStorageImageReadWithoutFormat       = pSource->shaderStorageImageReadWithoutFormat;
        pDestination->shaderStorageImageWriteWithoutFormat      = pSource->shaderStorageImageWriteWithoutFormat;
        pDestination->shaderUniformBufferArrayDynamicIndexing   = pSource->shaderUniformBufferArrayDynamicIndexing;
        pDestination->shaderSampledImageArrayDynamicIndexing    = pSource->shaderSampledImageArrayDynamicIndexing;
        pDestination->shaderStorageBufferArrayDynamicIndexing   = pSource->shaderStorageBufferArrayDynamicIndexing;
        pDestination->shaderStorageImageArrayDynamicIndexing    = pSource->shaderStorageImageArrayDynamicIndexing;
        pDestination->shaderClipDistance                        = pSource->shaderClipDistance;
        pDestination->shaderCullDistance                        = pSource->shaderCullDistance;
        pDestination->shaderFloat64                             = pSource->shaderFloat64;
        pDestination->shaderInt64                               = pSource->shaderInt64;
        pDestination->shaderInt16                               = pSource->shaderInt16;
        pDestination->shaderResourceResidency                   = pSource->shaderResourceResidency;
        pDestination->shaderResourceMinLod                      = pSource->shaderResourceMinLod;
        pDestination->sparseBinding                             = pSource->sparseBinding;
        pDestination->sparseResidencyBuffer                     = pSource->sparseResidencyBuffer;
        pDestination->sparseResidencyImage2D                    = pSource->sparseResidencyImage2D;
        pDestination->sparseResidencyImage3D                    = pSource->sparseResidencyImage3D;
        pDestination->sparseResidency2Samples                   = pSource->sparseResidency2Samples;
        pDestination->sparseResidency4Samples                   = pSource->sparseResidency4Samples;
        pDestination->sparseResidency8Samples                   = pSource->sparseResidency8Samples;
        pDestination->sparseResidency16Samples                  = pSource->sparseResidency16Samples;
        pDestination->sparseResidencyAliased                    = pSource->sparseResidencyAliased;
        pDestination->variableMultisampleRate                   = pSource->variableMultisampleRate;
        pDestination->inheritedQueries                          = pSource->inheritedQueries;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceFeatures2                     * pDestination,
            Type ( PhysicalDeviceExtendedFeatures ) const * pSource
    ) noexcept -> VkPhysicalDeviceFeatures2 * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
        pDestination->pNext = nullptr;

        (void) toVulkanFormat ( & pDestination->features, & pSource->features );

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceExtendedFeatures )       * pDestination,
            VkPhysicalDeviceFeatures2               const * pSource
    ) noexcept -> Type ( PhysicalDeviceExtendedFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceFeatures;
        pDestination->pNext = nullptr;

        (void) fromVulkanFormat ( & pDestination->features, & pSource->features );

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceVulkan11Properties ) * pDestination,
            VkPhysicalDeviceVulkan11Properties  const * pSource
    ) noexcept -> Type ( PhysicalDeviceVulkan11Properties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceVulkan_1_1_Properties;
        pDestination->pNext         = nullptr;

        pDestination->deviceNodeMask                    = pSource->deviceNodeMask;
        pDestination->subgroupSize                      = pSource->subgroupSize;
        pDestination->maxMultiviewViewCount             = pSource->maxMultiviewViewCount;
        pDestination->maxMultiviewInstanceIndex         = pSource->maxMultiviewInstanceIndex;
        pDestination->maxPerSetDescriptors              = pSource->maxPerSetDescriptors;

        pDestination->deviceLUIDValid                   = pSource->deviceLUIDValid;
        pDestination->subgroupQuadOperationsInAllStages = pSource->subgroupQuadOperationsInAllStages;
        pDestination->protectedNoFault                  = pSource->protectedNoFault;

        pDestination->subgroupSupportedStages           = pSource->subgroupSupportedStages;

        pDestination->subgroupSupportedOperations       = pSource->subgroupSupportedOperations;

        pDestination->pointClippingBehavior             = static_cast < vulkan :: __C_ENG_TYPE ( PointClippingBehavior ) > ( pSource->pointClippingBehavior );

        pDestination->maxMemoryAllocationSize           = pSource->maxMemoryAllocationSize;

        (void) std :: memcpy ( pDestination->deviceUUID, pSource->deviceUUID, sizeof ( pSource->deviceUUID[0] ) * VK_UUID_SIZE ); // NOLINT(clion-misra-cpp2008-5-2-12)
        (void) std :: memcpy ( pDestination->driverUUID, pSource->driverUUID, sizeof ( pSource->driverUUID[0] ) * VK_UUID_SIZE ); // NOLINT(clion-misra-cpp2008-5-2-12)
        (void) std :: memcpy ( pDestination->deviceLUID, pSource->deviceLUID, sizeof ( pSource->deviceLUID[0] ) * VK_LUID_SIZE ); // NOLINT(clion-misra-cpp2008-5-2-12)

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDevice16BitStorageFeatures ) * pDestination,
            VkPhysicalDevice16BitStorageFeatures  const * pSource
    ) noexcept -> Type ( PhysicalDevice16BitStorageFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDevice16BitStorageFeatures;
        pDestination->pNext         = nullptr;

        pDestination->storageBuffer16BitAccess              = pSource->storageBuffer16BitAccess;
        pDestination->uniformAndStorageBuffer16BitAccess    = pSource->uniformAndStorageBuffer16BitAccess;
        pDestination->storagePushConstant16                 = pSource->storagePushConstant16;
        pDestination->storageInputOutput16                  = pSource->storageInputOutput16;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceMultiviewFeatures ) * pDestination,
            VkPhysicalDeviceMultiviewFeatures  const * pSource
    ) noexcept -> Type ( PhysicalDeviceMultiviewFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceMultiviewFeatures;
        pDestination->pNext         = nullptr;

        pDestination->multiview                     = pSource->multiview;
        pDestination->multiviewGeometryShader       = pSource->multiviewGeometryShader;
        pDestination->multiviewTessellationShader   = pSource->multiviewTessellationShader;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceProtectedMemoryFeatures ) * pDestination,
            VkPhysicalDeviceProtectedMemoryFeatures  const * pSource
    ) noexcept -> Type ( PhysicalDeviceProtectedMemoryFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceProtectedMemoryFeatures;
        pDestination->pNext         = nullptr;

        pDestination->protectedMemory                     = pSource->protectedMemory;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceSamplerYCBCRConversionFeatures ) * pDestination,
            VkPhysicalDeviceSamplerYcbcrConversionFeatures  const * pSource
    ) noexcept -> Type ( PhysicalDeviceSamplerYCBCRConversionFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceSamplerYCBCRConversionFeatures;
        pDestination->pNext         = nullptr;

        pDestination->samplerYCBCRConversion                     = pSource->samplerYcbcrConversion;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceShaderDrawParametersFeatures ) * pDestination,
            VkPhysicalDeviceShaderDrawParametersFeatures  const * pSource
    ) noexcept -> Type ( PhysicalDeviceShaderDrawParametersFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceShaderDrawParametersFeatures;
        pDestination->pNext         = nullptr;

        pDestination->shaderDrawParameters                     = pSource->shaderDrawParameters;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceVariablePointersFeatures ) * pDestination,
            VkPhysicalDeviceVariablePointersFeatures  const * pSource
    ) noexcept -> Type ( PhysicalDeviceVariablePointersFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceVariablePointersFeatures;
        pDestination->pNext         = nullptr;

        pDestination->variablePointersStorageBuffer = pSource->variablePointersStorageBuffer;
        pDestination->variablePointers              = pSource->variablePointers;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDevicePointClippingProperties ) * pDestination,
            VkPhysicalDevicePointClippingProperties  const * pSource
    ) noexcept -> Type ( PhysicalDevicePointClippingProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDevicePointClippingProperties;
        pDestination->pNext         = nullptr;

        pDestination->pointClippingBehavior             = static_cast < vulkan :: __C_ENG_TYPE ( PointClippingBehavior ) > ( pSource->pointClippingBehavior );

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceSubgroupProperties ) * pDestination,
            VkPhysicalDeviceSubgroupProperties  const * pSource
    ) noexcept -> Type ( PhysicalDeviceSubgroupProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceSubgroupProperties;
        pDestination->pNext         = nullptr;

        pDestination->subgroupSize                      = pSource->subgroupSize;
        pDestination->quadOperationsInAllStages         = pSource->quadOperationsInAllStages;
        pDestination->supportedStages                   = pSource->supportedStages;
        pDestination->supportedOperations               = pSource->supportedOperations;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceProtectedMemoryProperties ) * pDestination,
            VkPhysicalDeviceProtectedMemoryProperties  const * pSource
    ) noexcept -> Type ( PhysicalDeviceProtectedMemoryProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceProtectedMemoryProperties;
        pDestination->pNext         = nullptr;

        pDestination->protectedNoFault  = pSource->protectedNoFault;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceMaintenanceProperties )  * pDestination,
            VkPhysicalDeviceMaintenance3Properties  const * pSource
    ) noexcept -> Type ( PhysicalDeviceMaintenanceProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceMaintenanceProperties;
        pDestination->pNext         = nullptr;

        pDestination->maxPerSetDescriptors              = pSource->maxPerSetDescriptors;
        pDestination->maxMemoryAllocationSize           = pSource->maxMemoryAllocationSize;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceMultiviewProperties ) * pDestination,
            VkPhysicalDeviceMultiviewProperties  const * pSource
    ) noexcept -> Type ( PhysicalDeviceMultiviewProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceMultiviewProperties;
        pDestination->pNext         = nullptr;

        pDestination->maxMultiviewViewCount             = pSource->maxMultiviewViewCount;
        pDestination->maxMultiviewInstanceIndex         = pSource->maxMultiviewInstanceIndex;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceIDProperties ) * pDestination,
            VkPhysicalDeviceIDProperties  const * pSource
    ) noexcept -> Type ( PhysicalDeviceIDProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceIDProperties;
        pDestination->pNext         = nullptr;

        pDestination->deviceNodeMask                    = pSource->deviceNodeMask;
        pDestination->deviceLUIDValid                   = pSource->deviceLUIDValid;

        (void) std :: memcpy ( pDestination->deviceUUID, pSource->deviceUUID, sizeof ( pSource->deviceUUID[0] ) * VK_UUID_SIZE ); // NOLINT(clion-misra-cpp2008-5-2-12)
        (void) std :: memcpy ( pDestination->driverUUID, pSource->driverUUID, sizeof ( pSource->driverUUID[0] ) * VK_UUID_SIZE ); // NOLINT(clion-misra-cpp2008-5-2-12)
        (void) std :: memcpy ( pDestination->deviceLUID, pSource->deviceLUID, sizeof ( pSource->deviceLUID[0] ) * VK_LUID_SIZE ); // NOLINT(clion-misra-cpp2008-5-2-12)

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceVulkan11Features ) * pDestination,
            VkPhysicalDeviceVulkan11Features  const * pSource
    ) noexcept -> Type ( PhysicalDeviceVulkan11Features ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType                         = StructureTypePhysicalDeviceVulkan_1_1_Features;
        pDestination->pNext                                 = nullptr;

        pDestination->storageBuffer16BitAccess              = pSource->storageBuffer16BitAccess;
        pDestination->uniformAndStorageBuffer16BitAccess    = pSource->uniformAndStorageBuffer16BitAccess;
        pDestination->storagePushConstant16                 = pSource->storagePushConstant16;
        pDestination->storageInputOutput16                  = pSource->storageInputOutput16;
        pDestination->multiview                             = pSource->multiview;
        pDestination->multiviewGeometryShader               = pSource->multiviewGeometryShader;
        pDestination->multiviewTessellationShader           = pSource->multiviewTessellationShader;
        pDestination->variablePointersStorageBuffer         = pSource->variablePointersStorageBuffer;
        pDestination->variablePointers                      = pSource->variablePointers;
        pDestination->protectedMemory                       = pSource->protectedMemory;
        pDestination->samplerYCBCRConversion                = pSource->samplerYcbcrConversion;
        pDestination->shaderDrawParameters                  = pSource->shaderDrawParameters;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceVulkan11Features              * pDestination,
            Type ( PhysicalDeviceVulkan11Features ) const * pSource
    ) noexcept -> VkPhysicalDeviceVulkan11Features * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType                                 = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES;
        pDestination->pNext                                 = nullptr;

        pDestination->storageBuffer16BitAccess              = pSource->storageBuffer16BitAccess;
        pDestination->uniformAndStorageBuffer16BitAccess    = pSource->uniformAndStorageBuffer16BitAccess;
        pDestination->storagePushConstant16                 = pSource->storagePushConstant16;
        pDestination->storageInputOutput16                  = pSource->storageInputOutput16;
        pDestination->multiview                             = pSource->multiview;
        pDestination->multiviewGeometryShader               = pSource->multiviewGeometryShader;
        pDestination->multiviewTessellationShader           = pSource->multiviewTessellationShader;
        pDestination->variablePointersStorageBuffer         = pSource->variablePointersStorageBuffer;
        pDestination->variablePointers                      = pSource->variablePointers;
        pDestination->protectedMemory                       = pSource->protectedMemory;
        pDestination->samplerYcbcrConversion                = pSource->samplerYCBCRConversion;
        pDestination->shaderDrawParameters                  = pSource->shaderDrawParameters;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceMultiviewFeatures              * pDestination,
            Type ( PhysicalDeviceMultiviewFeatures ) const * pSource
    ) noexcept -> VkPhysicalDeviceMultiviewFeatures * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType                                 = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_FEATURES;
        pDestination->pNext                                 = nullptr;

        pDestination->multiview                             = pSource->multiview;
        pDestination->multiviewGeometryShader               = pSource->multiviewGeometryShader;
        pDestination->multiviewTessellationShader           = pSource->multiviewTessellationShader;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDevice16BitStorageFeatures              * pDestination,
            Type ( PhysicalDevice16BitStorageFeatures ) const * pSource
    ) noexcept -> VkPhysicalDevice16BitStorageFeatures * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType                                 = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_16BIT_STORAGE_FEATURES;
        pDestination->pNext                                 = nullptr;

        pDestination->storageBuffer16BitAccess              = pSource->storageBuffer16BitAccess;
        pDestination->uniformAndStorageBuffer16BitAccess    = pSource->uniformAndStorageBuffer16BitAccess;
        pDestination->storagePushConstant16                 = pSource->storagePushConstant16;
        pDestination->storageInputOutput16                  = pSource->storageInputOutput16;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceProtectedMemoryFeatures              * pDestination,
            Type ( PhysicalDeviceProtectedMemoryFeatures ) const * pSource
    ) noexcept -> VkPhysicalDeviceProtectedMemoryFeatures * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType                                 = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROTECTED_MEMORY_FEATURES;
        pDestination->pNext                                 = nullptr;

        pDestination->protectedMemory                       = pSource->protectedMemory;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceSamplerYcbcrConversionFeatures              * pDestination,
            Type ( PhysicalDeviceSamplerYCBCRConversionFeatures ) const * pSource
    ) noexcept -> VkPhysicalDeviceSamplerYcbcrConversionFeatures * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType                                 = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLER_YCBCR_CONVERSION_FEATURES;
        pDestination->pNext                                 = nullptr;

        pDestination->samplerYcbcrConversion                = pSource->samplerYCBCRConversion;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceVariablePointersFeatures              * pDestination,
            Type ( PhysicalDeviceVariablePointersFeatures ) const * pSource
    ) noexcept -> VkPhysicalDeviceVariablePointersFeatures * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType                         = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VARIABLE_POINTERS_FEATURES;
        pDestination->pNext                         = nullptr;

        pDestination->variablePointersStorageBuffer = pSource->variablePointersStorageBuffer;
        pDestination->variablePointers              = pSource->variablePointers;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceShaderDrawParametersFeatures              * pDestination,
            Type ( PhysicalDeviceShaderDrawParametersFeatures ) const * pSource
    ) noexcept -> VkPhysicalDeviceShaderDrawParametersFeatures * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType                         = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_DRAW_PARAMETERS_FEATURES;
        pDestination->pNext                         = nullptr;

        pDestination->shaderDrawParameters          = pSource->shaderDrawParameters;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( ConformanceVersion )       * pDestination,
            VkConformanceVersion        const * pSource
    ) noexcept -> Type ( ConformanceVersion ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->patch      = pSource->patch;
        pDestination->major      = pSource->major;
        pDestination->minor      = pSource->minor;
        pDestination->subminor   = pSource->subminor;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceVulkan12Properties )       * pDestination,
            VkPhysicalDeviceVulkan12Properties        const * pSource
    ) noexcept -> Type ( PhysicalDeviceVulkan12Properties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceVulkan_1_2_Properties;

        pDestination->driverID                                                  = static_cast < vulkan :: __C_ENG_TYPE ( DriverID ) > ( pSource->driverID );
        (void) std :: memcpy ( pDestination->driverName,                        pSource->driverName, sizeof ( pSource->driverName[0] ) * VK_MAX_DRIVER_NAME_SIZE ); // NOLINT(clion-misra-cpp2008-5-2-12)
        (void) std :: memcpy ( pDestination->driverInfo,                        pSource->driverInfo, sizeof ( pSource->driverInfo[0] ) * VK_MAX_DRIVER_INFO_SIZE ); // NOLINT(clion-misra-cpp2008-5-2-12)
        fromVulkanFormat ( & pDestination->conformanceVersion,                  & pSource->conformanceVersion );

        pDestination->denormBehaviorIndependence                                = static_cast < vulkan :: __C_ENG_TYPE ( ShaderFloatControlsIndependence ) > ( pSource->denormBehaviorIndependence );
        pDestination->roundingModeIndependence                                  = static_cast < vulkan :: __C_ENG_TYPE ( ShaderFloatControlsIndependence ) > ( pSource->roundingModeIndependence );

        pDestination->shaderSignedZeroInfNanPreserveFloat16                     = pSource->shaderSignedZeroInfNanPreserveFloat16;
        pDestination->shaderSignedZeroInfNanPreserveFloat32                     = pSource->shaderSignedZeroInfNanPreserveFloat32;
        pDestination->shaderSignedZeroInfNanPreserveFloat64                     = pSource->shaderSignedZeroInfNanPreserveFloat64;

        pDestination->shaderDenormPreserveFloat16                               = pSource->shaderDenormPreserveFloat16;
        pDestination->shaderDenormPreserveFloat32                               = pSource->shaderDenormPreserveFloat32;
        pDestination->shaderDenormPreserveFloat64                               = pSource->shaderDenormPreserveFloat64;
        pDestination->shaderDenormFlushToZeroFloat16                            = pSource->shaderDenormFlushToZeroFloat16;
        pDestination->shaderDenormFlushToZeroFloat32                            = pSource->shaderDenormFlushToZeroFloat32;
        pDestination->shaderDenormFlushToZeroFloat64                            = pSource->shaderDenormFlushToZeroFloat64;

        pDestination->shaderRoundingModeRTEFloat16                              = pSource->shaderRoundingModeRTEFloat16;
        pDestination->shaderRoundingModeRTEFloat32                              = pSource->shaderRoundingModeRTEFloat32;
        pDestination->shaderRoundingModeRTEFloat64                              = pSource->shaderRoundingModeRTEFloat64;
        pDestination->shaderRoundingModeRTZFloat16                              = pSource->shaderRoundingModeRTZFloat16;
        pDestination->shaderRoundingModeRTZFloat32                              = pSource->shaderRoundingModeRTZFloat32;
        pDestination->shaderRoundingModeRTZFloat64                              = pSource->shaderRoundingModeRTZFloat64;

        pDestination->maxUpdateAfterBindDescriptorsInAllPools                   = pSource->maxUpdateAfterBindDescriptorsInAllPools;

        pDestination->shaderUniformBufferArrayNonUniformIndexingNative          = pSource->shaderUniformBufferArrayNonUniformIndexingNative;
        pDestination->shaderSampledImageArrayNonUniformIndexingNative           = pSource->shaderSampledImageArrayNonUniformIndexingNative;
        pDestination->shaderStorageBufferArrayNonUniformIndexingNative          = pSource->shaderStorageBufferArrayNonUniformIndexingNative;
        pDestination->shaderStorageImageArrayNonUniformIndexingNative           = pSource->shaderStorageImageArrayNonUniformIndexingNative;
        pDestination->shaderInputAttachmentArrayNonUniformIndexingNative        = pSource->shaderInputAttachmentArrayNonUniformIndexingNative;

        pDestination->robustBufferAccessUpdateAfterBind                         = pSource->robustBufferAccessUpdateAfterBind;

        pDestination->quadDivergentImplicitLod                                  = pSource->quadDivergentImplicitLod;

        pDestination->maxPerStageDescriptorUpdateAfterBindSamplers              = pSource->maxPerStageDescriptorUpdateAfterBindSamplers;
        pDestination->maxPerStageDescriptorUpdateAfterBindUniformBuffers        = pSource->maxPerStageDescriptorUpdateAfterBindUniformBuffers;
        pDestination->maxPerStageDescriptorUpdateAfterBindStorageBuffers        = pSource->maxPerStageDescriptorUpdateAfterBindStorageBuffers;
        pDestination->maxPerStageDescriptorUpdateAfterBindSampledImages         = pSource->maxPerStageDescriptorUpdateAfterBindSampledImages;
        pDestination->maxPerStageDescriptorUpdateAfterBindStorageImages         = pSource->maxPerStageDescriptorUpdateAfterBindStorageImages;
        pDestination->maxPerStageDescriptorUpdateAfterBindInputAttachments      = pSource->maxPerStageDescriptorUpdateAfterBindInputAttachments;

        pDestination->maxPerStageUpdateAfterBindResources                       = pSource->maxPerStageUpdateAfterBindResources;

        pDestination->maxDescriptorSetUpdateAfterBindSamplers                   = pSource->maxDescriptorSetUpdateAfterBindSamplers;
        pDestination->maxDescriptorSetUpdateAfterBindUniformBuffers             = pSource->maxDescriptorSetUpdateAfterBindUniformBuffers;
        pDestination->maxDescriptorSetUpdateAfterBindUniformBuffersDynamic      = pSource->maxDescriptorSetUpdateAfterBindUniformBuffersDynamic;
        pDestination->maxDescriptorSetUpdateAfterBindStorageBuffers             = pSource->maxDescriptorSetUpdateAfterBindStorageBuffers;
        pDestination->maxDescriptorSetUpdateAfterBindStorageBuffersDynamic      = pSource->maxDescriptorSetUpdateAfterBindStorageBuffersDynamic;
        pDestination->maxDescriptorSetUpdateAfterBindSampledImages              = pSource->maxDescriptorSetUpdateAfterBindSampledImages;
        pDestination->maxDescriptorSetUpdateAfterBindStorageImages              = pSource->maxDescriptorSetUpdateAfterBindStorageImages;
        pDestination->maxDescriptorSetUpdateAfterBindInputAttachments           = pSource->maxDescriptorSetUpdateAfterBindInputAttachments;

        pDestination->supportedDepthResolveModes                                = pSource->supportedDepthResolveModes;
        pDestination->supportedStencilResolveModes                              = pSource->supportedStencilResolveModes;

        pDestination->independentResolveNone                                    = pSource->independentResolveNone;
        pDestination->independentResolve                                        = pSource->independentResolve;

        pDestination->filterMinmaxSingleComponentFormats                        = pSource->filterMinmaxSingleComponentFormats;
        pDestination->filterMinmaxImageComponentMapping                         = pSource->filterMinmaxImageComponentMapping;

        pDestination->maxTimelineSemaphoreValueDifference                       = pSource->maxTimelineSemaphoreValueDifference;

        pDestination->framebufferIntegerColorSampleCounts                       = pSource->framebufferIntegerColorSampleCounts;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceDepthStencilResolveProperties )       * pDestination,
            VkPhysicalDeviceDepthStencilResolveProperties        const * pSource
    ) noexcept -> Type ( PhysicalDeviceDepthStencilResolveProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceDepthStencilResolveProperties;

        pDestination->supportedDepthResolveModes                                = pSource->supportedDepthResolveModes;
        pDestination->supportedStencilResolveModes                              = pSource->supportedStencilResolveModes;

        pDestination->independentResolveNone                                    = pSource->independentResolveNone;
        pDestination->independentResolve                                        = pSource->independentResolve;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceDescriptorIndexingProperties )       * pDestination,
            VkPhysicalDeviceDescriptorIndexingProperties        const * pSource
    ) noexcept -> Type ( PhysicalDeviceDescriptorIndexingProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceDescriptorIndexingProperties;
        pDestination->pNext = nullptr;

        pDestination->maxUpdateAfterBindDescriptorsInAllPools                   = pSource->maxUpdateAfterBindDescriptorsInAllPools;

        pDestination->shaderUniformBufferArrayNonUniformIndexingNative          = pSource->shaderUniformBufferArrayNonUniformIndexingNative;
        pDestination->shaderSampledImageArrayNonUniformIndexingNative           = pSource->shaderSampledImageArrayNonUniformIndexingNative;
        pDestination->shaderStorageBufferArrayNonUniformIndexingNative          = pSource->shaderStorageBufferArrayNonUniformIndexingNative;
        pDestination->shaderStorageImageArrayNonUniformIndexingNative           = pSource->shaderStorageImageArrayNonUniformIndexingNative;
        pDestination->shaderInputAttachmentArrayNonUniformIndexingNative        = pSource->shaderInputAttachmentArrayNonUniformIndexingNative;

        pDestination->robustBufferAccessUpdateAfterBind                         = pSource->robustBufferAccessUpdateAfterBind;

        pDestination->quadDivergentImplicitLod                                  = pSource->quadDivergentImplicitLod;

        pDestination->maxPerStageDescriptorUpdateAfterBindSamplers              = pSource->maxPerStageDescriptorUpdateAfterBindSamplers;
        pDestination->maxPerStageDescriptorUpdateAfterBindUniformBuffers        = pSource->maxPerStageDescriptorUpdateAfterBindUniformBuffers;
        pDestination->maxPerStageDescriptorUpdateAfterBindStorageBuffers        = pSource->maxPerStageDescriptorUpdateAfterBindStorageBuffers;
        pDestination->maxPerStageDescriptorUpdateAfterBindSampledImages         = pSource->maxPerStageDescriptorUpdateAfterBindSampledImages;
        pDestination->maxPerStageDescriptorUpdateAfterBindStorageImages         = pSource->maxPerStageDescriptorUpdateAfterBindStorageImages;
        pDestination->maxPerStageDescriptorUpdateAfterBindInputAttachments      = pSource->maxPerStageDescriptorUpdateAfterBindInputAttachments;

        pDestination->maxPerStageUpdateAfterBindResources                       = pSource->maxPerStageUpdateAfterBindResources;

        pDestination->maxDescriptorSetUpdateAfterBindSamplers                   = pSource->maxDescriptorSetUpdateAfterBindSamplers;
        pDestination->maxDescriptorSetUpdateAfterBindUniformBuffers             = pSource->maxDescriptorSetUpdateAfterBindUniformBuffers;
        pDestination->maxDescriptorSetUpdateAfterBindUniformBuffersDynamic      = pSource->maxDescriptorSetUpdateAfterBindUniformBuffersDynamic;
        pDestination->maxDescriptorSetUpdateAfterBindStorageBuffers             = pSource->maxDescriptorSetUpdateAfterBindStorageBuffers;
        pDestination->maxDescriptorSetUpdateAfterBindStorageBuffersDynamic      = pSource->maxDescriptorSetUpdateAfterBindStorageBuffersDynamic;
        pDestination->maxDescriptorSetUpdateAfterBindSampledImages              = pSource->maxDescriptorSetUpdateAfterBindSampledImages;
        pDestination->maxDescriptorSetUpdateAfterBindStorageImages              = pSource->maxDescriptorSetUpdateAfterBindStorageImages;
        pDestination->maxDescriptorSetUpdateAfterBindInputAttachments           = pSource->maxDescriptorSetUpdateAfterBindInputAttachments;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceDriverProperties )       * pDestination,
            VkPhysicalDeviceDriverProperties        const * pSource
    ) noexcept -> Type ( PhysicalDeviceDriverProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceDriverProperties;
        pDestination->pNext = nullptr;

        pDestination->driverID                                                  = static_cast < vulkan :: __C_ENG_TYPE ( DriverID ) > ( pSource->driverID );
        (void) std :: memcpy ( pDestination->driverName,                        pSource->driverName, sizeof ( pSource->driverName[0] ) * VK_MAX_DRIVER_NAME_SIZE ); // NOLINT(clion-misra-cpp2008-5-2-12)
        (void) std :: memcpy ( pDestination->driverInfo,                        pSource->driverInfo, sizeof ( pSource->driverInfo[0] ) * VK_MAX_DRIVER_INFO_SIZE ); // NOLINT(clion-misra-cpp2008-5-2-12)
        fromVulkanFormat ( & pDestination->conformanceVersion,                  & pSource->conformanceVersion );

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceFloatControlsProperties )       * pDestination,
            VkPhysicalDeviceFloatControlsProperties        const * pSource
    ) noexcept -> Type ( PhysicalDeviceFloatControlsProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceFloatControlsProperties;
        pDestination->pNext = nullptr;

        pDestination->denormBehaviorIndependence                                = static_cast < vulkan :: __C_ENG_TYPE ( ShaderFloatControlsIndependence ) > ( pSource->denormBehaviorIndependence );
        pDestination->roundingModeIndependence                                  = static_cast < vulkan :: __C_ENG_TYPE ( ShaderFloatControlsIndependence ) > ( pSource->roundingModeIndependence );

        pDestination->shaderSignedZeroInfNanPreserveFloat16                     = pSource->shaderSignedZeroInfNanPreserveFloat16;
        pDestination->shaderSignedZeroInfNanPreserveFloat32                     = pSource->shaderSignedZeroInfNanPreserveFloat32;
        pDestination->shaderSignedZeroInfNanPreserveFloat64                     = pSource->shaderSignedZeroInfNanPreserveFloat64;

        pDestination->shaderDenormPreserveFloat16                               = pSource->shaderDenormPreserveFloat16;
        pDestination->shaderDenormPreserveFloat32                               = pSource->shaderDenormPreserveFloat32;
        pDestination->shaderDenormPreserveFloat64                               = pSource->shaderDenormPreserveFloat64;
        pDestination->shaderDenormFlushToZeroFloat16                            = pSource->shaderDenormFlushToZeroFloat16;
        pDestination->shaderDenormFlushToZeroFloat32                            = pSource->shaderDenormFlushToZeroFloat32;
        pDestination->shaderDenormFlushToZeroFloat64                            = pSource->shaderDenormFlushToZeroFloat64;

        pDestination->shaderRoundingModeRTEFloat16                              = pSource->shaderRoundingModeRTEFloat16;
        pDestination->shaderRoundingModeRTEFloat32                              = pSource->shaderRoundingModeRTEFloat32;
        pDestination->shaderRoundingModeRTEFloat64                              = pSource->shaderRoundingModeRTEFloat64;
        pDestination->shaderRoundingModeRTZFloat16                              = pSource->shaderRoundingModeRTZFloat16;
        pDestination->shaderRoundingModeRTZFloat32                              = pSource->shaderRoundingModeRTZFloat32;
        pDestination->shaderRoundingModeRTZFloat64                              = pSource->shaderRoundingModeRTZFloat64;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceSamplerFilterMinmaxProperties )       * pDestination,
            VkPhysicalDeviceSamplerFilterMinmaxProperties        const * pSource
    ) noexcept -> Type ( PhysicalDeviceSamplerFilterMinmaxProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceSamplerFilterMinMaxProperties;
        pDestination->pNext = nullptr;

        pDestination->filterMinmaxSingleComponentFormats                        = pSource->filterMinmaxSingleComponentFormats;
        pDestination->filterMinmaxImageComponentMapping                         = pSource->filterMinmaxImageComponentMapping;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceTimelineSemaphoreProperties )       * pDestination,
            VkPhysicalDeviceTimelineSemaphoreProperties        const * pSource
    ) noexcept -> Type ( PhysicalDeviceTimelineSemaphoreProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceTimelineSemaphoreProperties;
        pDestination->pNext = nullptr;

        pDestination->maxTimelineSemaphoreValueDifference                       = pSource->maxTimelineSemaphoreValueDifference;


        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDevice8BitStorageFeatures )       * pDestination,
            VkPhysicalDevice8BitStorageFeatures        const * pSource
    ) noexcept -> Type ( PhysicalDevice8BitStorageFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDevice8BitStorageFeatures;
        pDestination->pNext = nullptr;

        pDestination->storageBuffer8BitAccess           = pSource->storageBuffer8BitAccess;
        pDestination->uniformAndStorageBuffer8BitAccess = pSource->uniformAndStorageBuffer8BitAccess;
        pDestination->storagePushConstant8              = pSource->storagePushConstant8;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceBufferDeviceAddressFeatures )       * pDestination,
            VkPhysicalDeviceBufferDeviceAddressFeatures        const * pSource
    ) noexcept -> Type ( PhysicalDeviceBufferDeviceAddressFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceBufferDeviceAddressFeatures;
        pDestination->pNext = nullptr;

        pDestination->bufferDeviceAddress               = pSource->bufferDeviceAddress;
        pDestination->bufferDeviceAddressCaptureReplay  = pSource->bufferDeviceAddressCaptureReplay;
        pDestination->bufferDeviceAddressMultiDevice    = pSource->bufferDeviceAddressMultiDevice;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceDescriptorIndexingFeatures )       * pDestination,
            VkPhysicalDeviceDescriptorIndexingFeatures        const * pSource
    ) noexcept -> Type ( PhysicalDeviceDescriptorIndexingFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceDescriptorIndexingFeatures;
        pDestination->pNext = nullptr;

        pDestination->shaderInputAttachmentArrayDynamicIndexing             = pSource->shaderInputAttachmentArrayDynamicIndexing;
        pDestination->shaderUniformTexelBufferArrayDynamicIndexing          = pSource->shaderUniformTexelBufferArrayDynamicIndexing;
        pDestination->shaderStorageTexelBufferArrayDynamicIndexing          = pSource->shaderStorageTexelBufferArrayDynamicIndexing;
        pDestination->shaderUniformBufferArrayNonUniformIndexing            = pSource->shaderUniformBufferArrayNonUniformIndexing;
        pDestination->shaderSampledImageArrayNonUniformIndexing             = pSource->shaderSampledImageArrayNonUniformIndexing;
        pDestination->shaderStorageBufferArrayNonUniformIndexing            = pSource->shaderStorageBufferArrayNonUniformIndexing;
        pDestination->shaderStorageImageArrayNonUniformIndexing             = pSource->shaderStorageImageArrayNonUniformIndexing;
        pDestination->shaderInputAttachmentArrayNonUniformIndexing          = pSource->shaderInputAttachmentArrayNonUniformIndexing;
        pDestination->shaderUniformTexelBufferArrayNonUniformIndexing       = pSource->shaderUniformTexelBufferArrayNonUniformIndexing;
        pDestination->shaderStorageTexelBufferArrayNonUniformIndexing       = pSource->shaderStorageTexelBufferArrayNonUniformIndexing;
        pDestination->descriptorBindingUniformBufferUpdateAfterBind         = pSource->descriptorBindingUniformBufferUpdateAfterBind;
        pDestination->descriptorBindingSampledImageUpdateAfterBind          = pSource->descriptorBindingSampledImageUpdateAfterBind;
        pDestination->descriptorBindingStorageImageUpdateAfterBind          = pSource->descriptorBindingStorageImageUpdateAfterBind;
        pDestination->descriptorBindingStorageBufferUpdateAfterBind         = pSource->descriptorBindingStorageBufferUpdateAfterBind;
        pDestination->descriptorBindingUniformTexelBufferUpdateAfterBind    = pSource->descriptorBindingUniformTexelBufferUpdateAfterBind;
        pDestination->descriptorBindingStorageTexelBufferUpdateAfterBind    = pSource->descriptorBindingStorageTexelBufferUpdateAfterBind;
        pDestination->descriptorBindingUpdateUnusedWhilePending             = pSource->descriptorBindingUpdateUnusedWhilePending;
        pDestination->descriptorBindingPartiallyBound                       = pSource->descriptorBindingPartiallyBound;
        pDestination->descriptorBindingVariableDescriptorCount              = pSource->descriptorBindingVariableDescriptorCount;
        pDestination->runtimeDescriptorArray                                = pSource->runtimeDescriptorArray;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceImagelessFramebufferFeatures )       * pDestination,
            VkPhysicalDeviceImagelessFramebufferFeatures        const * pSource
    ) noexcept -> Type ( PhysicalDeviceImagelessFramebufferFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceImagelessFramebufferFeatures;
        pDestination->pNext = nullptr;

        pDestination->imagelessFramebuffer             = pSource->imagelessFramebuffer;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceScalarBlockLayoutFeatures )       * pDestination,
            VkPhysicalDeviceScalarBlockLayoutFeatures        const * pSource
    ) noexcept -> Type ( PhysicalDeviceScalarBlockLayoutFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceScalarBlockLayoutFeatures;
        pDestination->pNext = nullptr;

        pDestination->scalarBlockLayout             = pSource->scalarBlockLayout;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceShaderAtomicInt64Features )       * pDestination,
            VkPhysicalDeviceShaderAtomicInt64Features        const * pSource
    ) noexcept -> Type ( PhysicalDeviceShaderAtomicInt64Features ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceShaderAtomicInt64Features;
        pDestination->pNext = nullptr;

        pDestination->shaderBufferInt64Atomics             = pSource->shaderBufferInt64Atomics;
        pDestination->shaderSharedInt64Atomics             = pSource->shaderSharedInt64Atomics;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceShaderFloat16Int8Features )       * pDestination,
            VkPhysicalDeviceShaderFloat16Int8Features        const * pSource
    ) noexcept -> Type ( PhysicalDeviceShaderFloat16Int8Features ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceShaderFloat16Int8Features;
        pDestination->pNext = nullptr;

        pDestination->shaderFloat16                 = pSource->shaderFloat16;
        pDestination->shaderInt8                    = pSource->shaderInt8;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceShaderSubgroupExtendedTypesFeatures )       * pDestination,
            VkPhysicalDeviceShaderSubgroupExtendedTypesFeatures        const * pSource
    ) noexcept -> Type ( PhysicalDeviceShaderSubgroupExtendedTypesFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceShaderSubgroupExtendedTypesFeatures;
        pDestination->pNext = nullptr;

        pDestination->shaderSubgroupExtendedTypes   = pSource->shaderSubgroupExtendedTypes;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceUniformBufferStandardLayoutFeatures )       * pDestination,
            VkPhysicalDeviceUniformBufferStandardLayoutFeatures        const * pSource
    ) noexcept -> Type ( PhysicalDeviceUniformBufferStandardLayoutFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceUniformBufferStandardLayoutFeatures;
        pDestination->pNext = nullptr;

        pDestination->uniformBufferStandardLayout   = pSource->uniformBufferStandardLayout;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceVulkanMemoryModelFeatures )       * pDestination,
            VkPhysicalDeviceVulkanMemoryModelFeatures        const * pSource
    ) noexcept -> Type ( PhysicalDeviceVulkanMemoryModelFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceVulkanMemoryModelFeatures;
        pDestination->pNext = nullptr;

        pDestination->vulkanMemoryModel                             = pSource->vulkanMemoryModel;
        pDestination->vulkanMemoryModelDeviceScope                  = pSource->vulkanMemoryModelDeviceScope;
        pDestination->vulkanMemoryModelAvailabilityVisibilityChains = pSource->vulkanMemoryModelAvailabilityVisibilityChains;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceVulkan12Features )       * pDestination,
            VkPhysicalDeviceVulkan12Features        const * pSource
    ) noexcept -> Type ( PhysicalDeviceVulkan12Features ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceVulkan_1_2_Features;
        pDestination->pNext = nullptr;

        pDestination->samplerMirrorClampToEdge                              = pSource->samplerMirrorClampToEdge;
        pDestination->drawIndirectCount                                     = pSource->drawIndirectCount;
        pDestination->storageBuffer8BitAccess                               = pSource->storageBuffer8BitAccess;
        pDestination->uniformAndStorageBuffer8BitAccess                     = pSource->uniformAndStorageBuffer8BitAccess;
        pDestination->storagePushConstant8                                  = pSource->storagePushConstant8;
        pDestination->shaderBufferInt64Atomics                              = pSource->shaderBufferInt64Atomics;
        pDestination->shaderSharedInt64Atomics                              = pSource->shaderSharedInt64Atomics;
        pDestination->shaderFloat16                                         = pSource->shaderFloat16;
        pDestination->shaderInt8                                            = pSource->shaderInt8;
        pDestination->descriptorIndexing                                    = pSource->descriptorIndexing;
        pDestination->shaderInputAttachmentArrayDynamicIndexing             = pSource->shaderInputAttachmentArrayDynamicIndexing;
        pDestination->shaderUniformTexelBufferArrayDynamicIndexing          = pSource->shaderUniformTexelBufferArrayDynamicIndexing;
        pDestination->shaderStorageTexelBufferArrayDynamicIndexing          = pSource->shaderStorageTexelBufferArrayDynamicIndexing;
        pDestination->shaderUniformBufferArrayNonUniformIndexing            = pSource->shaderUniformBufferArrayNonUniformIndexing;
        pDestination->shaderSampledImageArrayNonUniformIndexing             = pSource->shaderSampledImageArrayNonUniformIndexing;
        pDestination->shaderStorageBufferArrayNonUniformIndexing            = pSource->shaderStorageBufferArrayNonUniformIndexing;
        pDestination->shaderStorageImageArrayNonUniformIndexing             = pSource->shaderStorageImageArrayNonUniformIndexing;
        pDestination->shaderInputAttachmentArrayNonUniformIndexing          = pSource->shaderInputAttachmentArrayNonUniformIndexing;
        pDestination->shaderUniformTexelBufferArrayNonUniformIndexing       = pSource->shaderUniformTexelBufferArrayNonUniformIndexing;
        pDestination->shaderStorageTexelBufferArrayNonUniformIndexing       = pSource->shaderStorageTexelBufferArrayNonUniformIndexing;
        pDestination->descriptorBindingUniformBufferUpdateAfterBind         = pSource->descriptorBindingUniformBufferUpdateAfterBind;
        pDestination->descriptorBindingSampledImageUpdateAfterBind          = pSource->descriptorBindingSampledImageUpdateAfterBind;
        pDestination->descriptorBindingStorageImageUpdateAfterBind          = pSource->descriptorBindingStorageImageUpdateAfterBind;
        pDestination->descriptorBindingStorageBufferUpdateAfterBind         = pSource->descriptorBindingStorageBufferUpdateAfterBind;
        pDestination->descriptorBindingUniformTexelBufferUpdateAfterBind    = pSource->descriptorBindingUniformTexelBufferUpdateAfterBind;
        pDestination->descriptorBindingStorageTexelBufferUpdateAfterBind    = pSource->descriptorBindingStorageTexelBufferUpdateAfterBind;
        pDestination->descriptorBindingUpdateUnusedWhilePending             = pSource->descriptorBindingUpdateUnusedWhilePending;
        pDestination->descriptorBindingPartiallyBound                       = pSource->descriptorBindingPartiallyBound;
        pDestination->descriptorBindingVariableDescriptorCount              = pSource->descriptorBindingVariableDescriptorCount;
        pDestination->runtimeDescriptorArray                                = pSource->runtimeDescriptorArray;
        pDestination->samplerFilterMinmax                                   = pSource->samplerFilterMinmax;
        pDestination->scalarBlockLayout                                     = pSource->scalarBlockLayout;
        pDestination->imagelessFramebuffer                                  = pSource->imagelessFramebuffer;
        pDestination->uniformBufferStandardLayout                           = pSource->uniformBufferStandardLayout;
        pDestination->shaderSubgroupExtendedTypes                           = pSource->shaderSubgroupExtendedTypes;
        pDestination->separateDepthStencilLayouts                           = pSource->separateDepthStencilLayouts;
        pDestination->hostQueryReset                                        = pSource->hostQueryReset;
        pDestination->timelineSemaphore                                     = pSource->timelineSemaphore;
        pDestination->bufferDeviceAddress                                   = pSource->bufferDeviceAddress;
        pDestination->bufferDeviceAddressCaptureReplay                      = pSource->bufferDeviceAddressCaptureReplay;
        pDestination->bufferDeviceAddressMultiDevice                        = pSource->bufferDeviceAddressMultiDevice;
        pDestination->vulkanMemoryModel                                     = pSource->vulkanMemoryModel;
        pDestination->vulkanMemoryModelDeviceScope                          = pSource->vulkanMemoryModelDeviceScope;
        pDestination->vulkanMemoryModelAvailabilityVisibilityChains         = pSource->vulkanMemoryModelAvailabilityVisibilityChains;
        pDestination->shaderOutputViewportIndex                             = pSource->shaderOutputViewportIndex;
        pDestination->shaderOutputLayer                                     = pSource->shaderOutputLayer;
        pDestination->subgroupBroadcastDynamicId                            = pSource->subgroupBroadcastDynamicId;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceVulkan12Features              * pDestination,
            Type ( PhysicalDeviceVulkan12Features ) const * pSource
    ) noexcept -> VkPhysicalDeviceVulkan12Features * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;
        pDestination->pNext = nullptr;

        pDestination->samplerMirrorClampToEdge                              = pSource->samplerMirrorClampToEdge;
        pDestination->drawIndirectCount                                     = pSource->drawIndirectCount;
        pDestination->storageBuffer8BitAccess                               = pSource->storageBuffer8BitAccess;
        pDestination->uniformAndStorageBuffer8BitAccess                     = pSource->uniformAndStorageBuffer8BitAccess;
        pDestination->storagePushConstant8                                  = pSource->storagePushConstant8;
        pDestination->shaderBufferInt64Atomics                              = pSource->shaderBufferInt64Atomics;
        pDestination->shaderSharedInt64Atomics                              = pSource->shaderSharedInt64Atomics;
        pDestination->shaderFloat16                                         = pSource->shaderFloat16;
        pDestination->shaderInt8                                            = pSource->shaderInt8;
        pDestination->descriptorIndexing                                    = pSource->descriptorIndexing;
        pDestination->shaderInputAttachmentArrayDynamicIndexing             = pSource->shaderInputAttachmentArrayDynamicIndexing;
        pDestination->shaderUniformTexelBufferArrayDynamicIndexing          = pSource->shaderUniformTexelBufferArrayDynamicIndexing;
        pDestination->shaderStorageTexelBufferArrayDynamicIndexing          = pSource->shaderStorageTexelBufferArrayDynamicIndexing;
        pDestination->shaderUniformBufferArrayNonUniformIndexing            = pSource->shaderUniformBufferArrayNonUniformIndexing;
        pDestination->shaderSampledImageArrayNonUniformIndexing             = pSource->shaderSampledImageArrayNonUniformIndexing;
        pDestination->shaderStorageBufferArrayNonUniformIndexing            = pSource->shaderStorageBufferArrayNonUniformIndexing;
        pDestination->shaderStorageImageArrayNonUniformIndexing             = pSource->shaderStorageImageArrayNonUniformIndexing;
        pDestination->shaderInputAttachmentArrayNonUniformIndexing          = pSource->shaderInputAttachmentArrayNonUniformIndexing;
        pDestination->shaderUniformTexelBufferArrayNonUniformIndexing       = pSource->shaderUniformTexelBufferArrayNonUniformIndexing;
        pDestination->shaderStorageTexelBufferArrayNonUniformIndexing       = pSource->shaderStorageTexelBufferArrayNonUniformIndexing;
        pDestination->descriptorBindingUniformBufferUpdateAfterBind         = pSource->descriptorBindingUniformBufferUpdateAfterBind;
        pDestination->descriptorBindingSampledImageUpdateAfterBind          = pSource->descriptorBindingSampledImageUpdateAfterBind;
        pDestination->descriptorBindingStorageImageUpdateAfterBind          = pSource->descriptorBindingStorageImageUpdateAfterBind;
        pDestination->descriptorBindingStorageBufferUpdateAfterBind         = pSource->descriptorBindingStorageBufferUpdateAfterBind;
        pDestination->descriptorBindingUniformTexelBufferUpdateAfterBind    = pSource->descriptorBindingUniformTexelBufferUpdateAfterBind;
        pDestination->descriptorBindingStorageTexelBufferUpdateAfterBind    = pSource->descriptorBindingStorageTexelBufferUpdateAfterBind;
        pDestination->descriptorBindingUpdateUnusedWhilePending             = pSource->descriptorBindingUpdateUnusedWhilePending;
        pDestination->descriptorBindingPartiallyBound                       = pSource->descriptorBindingPartiallyBound;
        pDestination->descriptorBindingVariableDescriptorCount              = pSource->descriptorBindingVariableDescriptorCount;
        pDestination->runtimeDescriptorArray                                = pSource->runtimeDescriptorArray;
        pDestination->samplerFilterMinmax                                   = pSource->samplerFilterMinmax;
        pDestination->scalarBlockLayout                                     = pSource->scalarBlockLayout;
        pDestination->imagelessFramebuffer                                  = pSource->imagelessFramebuffer;
        pDestination->uniformBufferStandardLayout                           = pSource->uniformBufferStandardLayout;
        pDestination->shaderSubgroupExtendedTypes                           = pSource->shaderSubgroupExtendedTypes;
        pDestination->separateDepthStencilLayouts                           = pSource->separateDepthStencilLayouts;
        pDestination->hostQueryReset                                        = pSource->hostQueryReset;
        pDestination->timelineSemaphore                                     = pSource->timelineSemaphore;
        pDestination->bufferDeviceAddress                                   = pSource->bufferDeviceAddress;
        pDestination->bufferDeviceAddressCaptureReplay                      = pSource->bufferDeviceAddressCaptureReplay;
        pDestination->bufferDeviceAddressMultiDevice                        = pSource->bufferDeviceAddressMultiDevice;
        pDestination->vulkanMemoryModel                                     = pSource->vulkanMemoryModel;
        pDestination->vulkanMemoryModelDeviceScope                          = pSource->vulkanMemoryModelDeviceScope;
        pDestination->vulkanMemoryModelAvailabilityVisibilityChains         = pSource->vulkanMemoryModelAvailabilityVisibilityChains;
        pDestination->shaderOutputViewportIndex                             = pSource->shaderOutputViewportIndex;
        pDestination->shaderOutputLayer                                     = pSource->shaderOutputLayer;
        pDestination->subgroupBroadcastDynamicId                            = pSource->subgroupBroadcastDynamicId;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDevice8BitStorageFeatures              * pDestination,
            Type ( PhysicalDevice8BitStorageFeatures ) const * pSource
    ) noexcept -> VkPhysicalDevice8BitStorageFeatures * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_8BIT_STORAGE_FEATURES;
        pDestination->pNext = nullptr;

        pDestination->storageBuffer8BitAccess                               = pSource->storageBuffer8BitAccess;
        pDestination->uniformAndStorageBuffer8BitAccess                     = pSource->uniformAndStorageBuffer8BitAccess;
        pDestination->storagePushConstant8                                  = pSource->storagePushConstant8;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceBufferDeviceAddressFeatures              * pDestination,
            Type ( PhysicalDeviceBufferDeviceAddressFeatures ) const * pSource
    ) noexcept -> VkPhysicalDeviceBufferDeviceAddressFeatures * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BUFFER_DEVICE_ADDRESS_FEATURES;
        pDestination->pNext = nullptr;

        pDestination->bufferDeviceAddress               = pSource->bufferDeviceAddress;
        pDestination->bufferDeviceAddressCaptureReplay  = pSource->bufferDeviceAddressCaptureReplay;
        pDestination->bufferDeviceAddressMultiDevice    = pSource->bufferDeviceAddressMultiDevice;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceDescriptorIndexingFeatures              * pDestination,
            Type ( PhysicalDeviceDescriptorIndexingFeatures ) const * pSource
    ) noexcept -> VkPhysicalDeviceDescriptorIndexingFeatures * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_FEATURES;
        pDestination->pNext = nullptr;

        pDestination->shaderInputAttachmentArrayDynamicIndexing             = pSource->shaderInputAttachmentArrayDynamicIndexing;
        pDestination->shaderUniformTexelBufferArrayDynamicIndexing          = pSource->shaderUniformTexelBufferArrayDynamicIndexing;
        pDestination->shaderStorageTexelBufferArrayDynamicIndexing          = pSource->shaderStorageTexelBufferArrayDynamicIndexing;
        pDestination->shaderUniformBufferArrayNonUniformIndexing            = pSource->shaderUniformBufferArrayNonUniformIndexing;
        pDestination->shaderSampledImageArrayNonUniformIndexing             = pSource->shaderSampledImageArrayNonUniformIndexing;
        pDestination->shaderStorageBufferArrayNonUniformIndexing            = pSource->shaderStorageBufferArrayNonUniformIndexing;
        pDestination->shaderStorageImageArrayNonUniformIndexing             = pSource->shaderStorageImageArrayNonUniformIndexing;
        pDestination->shaderInputAttachmentArrayNonUniformIndexing          = pSource->shaderInputAttachmentArrayNonUniformIndexing;
        pDestination->shaderUniformTexelBufferArrayNonUniformIndexing       = pSource->shaderUniformTexelBufferArrayNonUniformIndexing;
        pDestination->shaderStorageTexelBufferArrayNonUniformIndexing       = pSource->shaderStorageTexelBufferArrayNonUniformIndexing;
        pDestination->descriptorBindingUniformBufferUpdateAfterBind         = pSource->descriptorBindingUniformBufferUpdateAfterBind;
        pDestination->descriptorBindingSampledImageUpdateAfterBind          = pSource->descriptorBindingSampledImageUpdateAfterBind;
        pDestination->descriptorBindingStorageImageUpdateAfterBind          = pSource->descriptorBindingStorageImageUpdateAfterBind;
        pDestination->descriptorBindingStorageBufferUpdateAfterBind         = pSource->descriptorBindingStorageBufferUpdateAfterBind;
        pDestination->descriptorBindingUniformTexelBufferUpdateAfterBind    = pSource->descriptorBindingUniformTexelBufferUpdateAfterBind;
        pDestination->descriptorBindingStorageTexelBufferUpdateAfterBind    = pSource->descriptorBindingStorageTexelBufferUpdateAfterBind;
        pDestination->descriptorBindingUpdateUnusedWhilePending             = pSource->descriptorBindingUpdateUnusedWhilePending;
        pDestination->descriptorBindingPartiallyBound                       = pSource->descriptorBindingPartiallyBound;
        pDestination->descriptorBindingVariableDescriptorCount              = pSource->descriptorBindingVariableDescriptorCount;
        pDestination->runtimeDescriptorArray                                = pSource->runtimeDescriptorArray;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceHostQueryResetFeatures              * pDestination,
            Type ( PhysicalDeviceHostQueryResetFeatures ) const * pSource
    ) noexcept -> VkPhysicalDeviceHostQueryResetFeatures * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_HOST_QUERY_RESET_FEATURES;
        pDestination->pNext = nullptr;

        pDestination->hostQueryReset             = pSource->hostQueryReset;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceImagelessFramebufferFeatures              * pDestination,
            Type ( PhysicalDeviceImagelessFramebufferFeatures ) const * pSource
    ) noexcept -> VkPhysicalDeviceImagelessFramebufferFeatures * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGELESS_FRAMEBUFFER_FEATURES;
        pDestination->pNext = nullptr;

        pDestination->imagelessFramebuffer             = pSource->imagelessFramebuffer;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceScalarBlockLayoutFeatures              * pDestination,
            Type ( PhysicalDeviceScalarBlockLayoutFeatures ) const * pSource
    ) noexcept -> VkPhysicalDeviceScalarBlockLayoutFeatures * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SCALAR_BLOCK_LAYOUT_FEATURES;
        pDestination->pNext = nullptr;

        pDestination->scalarBlockLayout             = pSource->scalarBlockLayout;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceSeparateDepthStencilLayoutsFeatures              * pDestination,
            Type ( PhysicalDeviceSeparateDepthStencilLayoutsFeatures ) const * pSource
    ) noexcept -> VkPhysicalDeviceSeparateDepthStencilLayoutsFeatures * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SEPARATE_DEPTH_STENCIL_LAYOUTS_FEATURES;
        pDestination->pNext = nullptr;

        pDestination->separateDepthStencilLayouts   = pSource->separateDepthStencilLayouts;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceShaderAtomicInt64Features              * pDestination,
            Type ( PhysicalDeviceShaderAtomicInt64Features ) const * pSource
    ) noexcept -> VkPhysicalDeviceShaderAtomicInt64Features * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_INT64_FEATURES;
        pDestination->pNext = nullptr;

        pDestination->shaderBufferInt64Atomics             = pSource->shaderBufferInt64Atomics;
        pDestination->shaderSharedInt64Atomics             = pSource->shaderSharedInt64Atomics;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceShaderFloat16Int8Features              * pDestination,
            Type ( PhysicalDeviceShaderFloat16Int8Features ) const * pSource
    ) noexcept -> VkPhysicalDeviceShaderFloat16Int8Features * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_FLOAT16_INT8_FEATURES;
        pDestination->pNext = nullptr;

        pDestination->shaderFloat16                 = pSource->shaderFloat16;
        pDestination->shaderInt8                    = pSource->shaderInt8;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceShaderSubgroupExtendedTypesFeatures              * pDestination,
            Type ( PhysicalDeviceShaderSubgroupExtendedTypesFeatures ) const * pSource
    ) noexcept -> VkPhysicalDeviceShaderSubgroupExtendedTypesFeatures * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SUBGROUP_EXTENDED_TYPES_FEATURES;
        pDestination->pNext = nullptr;

        pDestination->shaderSubgroupExtendedTypes                 = pSource->shaderSubgroupExtendedTypes;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceTimelineSemaphoreFeatures              * pDestination,
            Type ( PhysicalDeviceTimelineSemaphoreFeatures ) const * pSource
    ) noexcept -> VkPhysicalDeviceTimelineSemaphoreFeatures * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TIMELINE_SEMAPHORE_FEATURES;
        pDestination->pNext = nullptr;

        pDestination->timelineSemaphore                 = pSource->timelineSemaphore;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceUniformBufferStandardLayoutFeatures              * pDestination,
            Type ( PhysicalDeviceUniformBufferStandardLayoutFeatures ) const * pSource
    ) noexcept -> VkPhysicalDeviceUniformBufferStandardLayoutFeatures * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_UNIFORM_BUFFER_STANDARD_LAYOUT_FEATURES;
        pDestination->pNext = nullptr;

        pDestination->uniformBufferStandardLayout                 = pSource->uniformBufferStandardLayout;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceVulkanMemoryModelFeatures              * pDestination,
            Type ( PhysicalDeviceVulkanMemoryModelFeatures ) const * pSource
    ) noexcept -> VkPhysicalDeviceVulkanMemoryModelFeatures * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_MEMORY_MODEL_FEATURES;
        pDestination->pNext = nullptr;

        pDestination->vulkanMemoryModel                             = pSource->vulkanMemoryModel;
        pDestination->vulkanMemoryModelDeviceScope                  = pSource->vulkanMemoryModelDeviceScope;
        pDestination->vulkanMemoryModelAvailabilityVisibilityChains = pSource->vulkanMemoryModelAvailabilityVisibilityChains;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceVulkan13Properties )        * pDestination,
            VkPhysicalDeviceVulkan13Properties         const * pSource
    ) noexcept -> Type ( PhysicalDeviceVulkan13Properties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceVulkan_1_3_Properties;
        pDestination->pNext = nullptr;

        pDestination->minSubgroupSize                                                               = pSource->minSubgroupSize;
        pDestination->maxSubgroupSize                                                               = pSource->maxSubgroupSize;
        pDestination->maxComputeWorkgroupSubgroups                                                  = pSource->maxComputeWorkgroupSubgroups;
        pDestination->requiredSubgroupSizeStages                                                    = pSource->requiredSubgroupSizeStages;
        pDestination->maxInlineUniformBlockSize                                                     = pSource->maxInlineUniformBlockSize;
        pDestination->maxPerStageDescriptorInlineUniformBlocks                                      = pSource->maxPerStageDescriptorInlineUniformBlocks;
        pDestination->maxPerStageDescriptorUpdateAfterBindInlineUniformBlocks                       = pSource->maxPerStageDescriptorUpdateAfterBindInlineUniformBlocks;
        pDestination->maxDescriptorSetInlineUniformBlocks                                           = pSource->maxDescriptorSetInlineUniformBlocks;
        pDestination->maxDescriptorSetUpdateAfterBindInlineUniformBlocks                            = pSource->maxDescriptorSetUpdateAfterBindInlineUniformBlocks;
        pDestination->maxInlineUniformTotalSize                                                     = pSource->maxInlineUniformTotalSize;
        pDestination->integerDotProduct8BitUnsignedAccelerated                                      = pSource->integerDotProduct8BitUnsignedAccelerated;
        pDestination->integerDotProduct8BitSignedAccelerated                                        = pSource->integerDotProduct8BitSignedAccelerated;
        pDestination->integerDotProduct8BitMixedSignednessAccelerated                               = pSource->integerDotProduct8BitMixedSignednessAccelerated;
        pDestination->integerDotProduct4x8BitPackedUnsignedAccelerated                              = pSource->integerDotProduct4x8BitPackedUnsignedAccelerated;
        pDestination->integerDotProduct4x8BitPackedSignedAccelerated                                = pSource->integerDotProduct4x8BitPackedSignedAccelerated;
        pDestination->integerDotProduct4x8BitPackedMixedSignednessAccelerated                       = pSource->integerDotProduct4x8BitPackedMixedSignednessAccelerated;
        pDestination->integerDotProduct16BitUnsignedAccelerated                                     = pSource->integerDotProduct16BitUnsignedAccelerated;
        pDestination->integerDotProduct16BitSignedAccelerated                                       = pSource->integerDotProduct16BitSignedAccelerated;
        pDestination->integerDotProduct16BitMixedSignednessAccelerated                              = pSource->integerDotProduct16BitMixedSignednessAccelerated;
        pDestination->integerDotProduct32BitUnsignedAccelerated                                     = pSource->integerDotProduct32BitUnsignedAccelerated;
        pDestination->integerDotProduct32BitSignedAccelerated                                       = pSource->integerDotProduct32BitSignedAccelerated;
        pDestination->integerDotProduct32BitMixedSignednessAccelerated                              = pSource->integerDotProduct32BitMixedSignednessAccelerated;
        pDestination->integerDotProduct64BitUnsignedAccelerated                                     = pSource->integerDotProduct64BitUnsignedAccelerated;
        pDestination->integerDotProduct64BitSignedAccelerated                                       = pSource->integerDotProduct64BitSignedAccelerated;
        pDestination->integerDotProduct64BitMixedSignednessAccelerated                              = pSource->integerDotProduct64BitMixedSignednessAccelerated;
        pDestination->integerDotProductAccumulatingSaturating8BitUnsignedAccelerated                = pSource->integerDotProductAccumulatingSaturating8BitUnsignedAccelerated;
        pDestination->integerDotProductAccumulatingSaturating8BitSignedAccelerated                  = pSource->integerDotProductAccumulatingSaturating8BitSignedAccelerated;
        pDestination->integerDotProductAccumulatingSaturating8BitMixedSignednessAccelerated         = pSource->integerDotProductAccumulatingSaturating8BitMixedSignednessAccelerated;
        pDestination->integerDotProductAccumulatingSaturating4x8BitPackedUnsignedAccelerated        = pSource->integerDotProductAccumulatingSaturating4x8BitPackedUnsignedAccelerated;
        pDestination->integerDotProductAccumulatingSaturating4x8BitPackedSignedAccelerated          = pSource->integerDotProductAccumulatingSaturating4x8BitPackedSignedAccelerated;
        pDestination->integerDotProductAccumulatingSaturating4x8BitPackedMixedSignednessAccelerated = pSource->integerDotProductAccumulatingSaturating4x8BitPackedMixedSignednessAccelerated;
        pDestination->integerDotProductAccumulatingSaturating16BitUnsignedAccelerated               = pSource->integerDotProductAccumulatingSaturating16BitUnsignedAccelerated;
        pDestination->integerDotProductAccumulatingSaturating16BitSignedAccelerated                 = pSource->integerDotProductAccumulatingSaturating16BitSignedAccelerated;
        pDestination->integerDotProductAccumulatingSaturating16BitMixedSignednessAccelerated        = pSource->integerDotProductAccumulatingSaturating16BitMixedSignednessAccelerated;
        pDestination->integerDotProductAccumulatingSaturating32BitUnsignedAccelerated               = pSource->integerDotProductAccumulatingSaturating32BitUnsignedAccelerated;
        pDestination->integerDotProductAccumulatingSaturating32BitSignedAccelerated                 = pSource->integerDotProductAccumulatingSaturating32BitSignedAccelerated;
        pDestination->integerDotProductAccumulatingSaturating32BitMixedSignednessAccelerated        = pSource->integerDotProductAccumulatingSaturating32BitMixedSignednessAccelerated;
        pDestination->integerDotProductAccumulatingSaturating64BitUnsignedAccelerated               = pSource->integerDotProductAccumulatingSaturating64BitUnsignedAccelerated;
        pDestination->integerDotProductAccumulatingSaturating64BitSignedAccelerated                 = pSource->integerDotProductAccumulatingSaturating64BitSignedAccelerated;
        pDestination->integerDotProductAccumulatingSaturating64BitMixedSignednessAccelerated        = pSource->integerDotProductAccumulatingSaturating64BitMixedSignednessAccelerated;
        pDestination->storageTexelBufferOffsetAlignmentBytes                                        = pSource->storageTexelBufferOffsetAlignmentBytes;
        pDestination->storageTexelBufferOffsetSingleTexelAlignment                                  = pSource->storageTexelBufferOffsetSingleTexelAlignment;
        pDestination->uniformTexelBufferOffsetAlignmentBytes                                        = pSource->uniformTexelBufferOffsetAlignmentBytes;
        pDestination->uniformTexelBufferOffsetSingleTexelAlignment                                  = pSource->uniformTexelBufferOffsetSingleTexelAlignment;
        pDestination->maxBufferSize                                                                 = pSource->maxBufferSize;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceVulkan13Features )        * pDestination,
            VkPhysicalDeviceVulkan13Features         const * pSource
    ) noexcept -> Type ( PhysicalDeviceVulkan13Features ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceVulkan_1_3_Features;
        pDestination->pNext = nullptr;

        pDestination->robustImageAccess                                     = pSource->robustImageAccess;
        pDestination->inlineUniformBlock                                    = pSource->inlineUniformBlock;
        pDestination->descriptorBindingInlineUniformBlockUpdateAfterBind    = pSource->descriptorBindingInlineUniformBlockUpdateAfterBind;
        pDestination->pipelineCreationCacheControl                          = pSource->pipelineCreationCacheControl;
        pDestination->privateData                                           = pSource->privateData;
        pDestination->shaderDemoteToHelperInvocation                        = pSource->shaderDemoteToHelperInvocation;
        pDestination->shaderTerminateInvocation                             = pSource->shaderTerminateInvocation;
        pDestination->subgroupSizeControl                                   = pSource->subgroupSizeControl;
        pDestination->computeFullSubgroups                                  = pSource->computeFullSubgroups;
        pDestination->synchronization2                                      = pSource->synchronization2;
        pDestination->textureCompressionASTC_HDR                            = pSource->textureCompressionASTC_HDR;
        pDestination->shaderZeroInitializeWorkgroupMemory                   = pSource->shaderZeroInitializeWorkgroupMemory;
        pDestination->dynamicRendering                                      = pSource->dynamicRendering;
        pDestination->shaderIntegerDotProduct                               = pSource->shaderIntegerDotProduct;
        pDestination->maintenance4                                          = pSource->maintenance4;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceBlendOperationAdvancedProperties )            * pDestination,
            VkPhysicalDeviceBlendOperationAdvancedPropertiesEXT         const * pSource
    ) noexcept -> Type ( PhysicalDeviceBlendOperationAdvancedProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceBlendOperationAdvancedProperties;
        pDestination->pNext = nullptr;

        pDestination->advancedBlendMaxColorAttachments          = pSource->advancedBlendMaxColorAttachments;
        pDestination->advancedBlendIndependentBlend             = pSource->advancedBlendIndependentBlend;
        pDestination->advancedBlendNonPremultipliedSrcColor     = pSource->advancedBlendNonPremultipliedSrcColor;
        pDestination->advancedBlendNonPremultipliedDstColor     = pSource->advancedBlendNonPremultipliedDstColor;
        pDestination->advancedBlendCorrelatedOverlap            = pSource->advancedBlendCorrelatedOverlap;
        pDestination->advancedBlendAllOperations                = pSource->advancedBlendAllOperations;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONSERVATIVE_RASTERIZATION_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceConservativeRasterizationProperties )           * pDestination,
            VkPhysicalDeviceConservativeRasterizationPropertiesEXT         const * pSource
    ) noexcept -> Type ( PhysicalDeviceConservativeRasterizationProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceConservativeRasterizationProperties;
        pDestination->pNext = nullptr;

        pDestination->primitiveOverestimationSize                   = pSource->primitiveOverestimationSize;
        pDestination->maxExtraPrimitiveOverestimationSize           = pSource->maxExtraPrimitiveOverestimationSize;
        pDestination->extraPrimitiveOverestimationSizeGranularity   = pSource->extraPrimitiveOverestimationSizeGranularity;
        pDestination->primitiveUnderestimation                      = pSource->primitiveUnderestimation;
        pDestination->conservativePointAndLineRasterization         = pSource->conservativePointAndLineRasterization;
        pDestination->degenerateTrianglesRasterized                 = pSource->degenerateTrianglesRasterized;
        pDestination->degenerateLinesRasterized                     = pSource->degenerateLinesRasterized;
        pDestination->fullyCoveredFragmentShaderInputVariable       = pSource->fullyCoveredFragmentShaderInputVariable;
        pDestination->conservativeRasterizationPostDepthCoverage    = pSource->conservativeRasterizationPostDepthCoverage;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceCustomBorderColorProperties )           * pDestination,
            VkPhysicalDeviceCustomBorderColorPropertiesEXT         const * pSource
    ) noexcept -> Type ( PhysicalDeviceCustomBorderColorProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceCustomBorderColorProperties;
        pDestination->pNext = nullptr;

        pDestination->maxCustomBorderColorSamplers                   = pSource->maxCustomBorderColorSamplers;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISCARD_RECTANGLES_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceDiscardRectangleProperties )           * pDestination,
            VkPhysicalDeviceDiscardRectanglePropertiesEXT         const * pSource
    ) noexcept -> Type ( PhysicalDeviceDiscardRectangleProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceDiscardRectangleProperties;
        pDestination->pNext = nullptr;

        pDestination->maxDiscardRectangles  = pSource->maxDiscardRectangles;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTERNAL_MEMORY_HOST_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceExternalMemoryHostProperties )           * pDestination,
            VkPhysicalDeviceExternalMemoryHostPropertiesEXT         const * pSource
    ) noexcept -> Type ( PhysicalDeviceExternalMemoryHostProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceExternalMemoryHostProperties;
        pDestination->pNext = nullptr;

        pDestination->minImportedHostPointerAlignment  = pSource->minImportedHostPointerAlignment;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceFragmentDensityMapProperties )           * pDestination,
            VkPhysicalDeviceFragmentDensityMapPropertiesEXT         const * pSource
    ) noexcept -> Type ( PhysicalDeviceFragmentDensityMapProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceFragmentDensityMapProperties;
        pDestination->pNext = nullptr;

        pDestination->minFragmentDensityTexelSize                   = pSource->minFragmentDensityTexelSize;
        pDestination->maxFragmentDensityTexelSize                   = pSource->maxFragmentDensityTexelSize;
        pDestination->fragmentDensityInvocations                    = pSource->fragmentDensityInvocations;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceFragmentDensityMap2Properties )           * pDestination,
            VkPhysicalDeviceFragmentDensityMap2PropertiesEXT         const * pSource
    ) noexcept -> Type ( PhysicalDeviceFragmentDensityMap2Properties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceFragmentDensityMap2Properties;
        pDestination->pNext = nullptr;

        pDestination->subsampledLoads                           = pSource->subsampledLoads;
        pDestination->subsampledCoarseReconstructionEarlyAccess = pSource->subsampledCoarseReconstructionEarlyAccess;
        pDestination->maxSubsampledArrayLayers                  = pSource->maxSubsampledArrayLayers;
        pDestination->maxDescriptorSetSubsampledSamplers        = pSource->maxDescriptorSetSubsampledSamplers;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceInlineUniformBlockProperties )           * pDestination,
            VkPhysicalDeviceInlineUniformBlockProperties_t          const * pSource
    ) noexcept -> Type ( PhysicalDeviceInlineUniformBlockProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceInlineUniformBlockProperties;
        pDestination->pNext = nullptr;

        pDestination->maxInlineUniformBlockSize                                 = pSource->maxInlineUniformBlockSize;
        pDestination->maxPerStageDescriptorInlineUniformBlocks                  = pSource->maxPerStageDescriptorInlineUniformBlocks;
        pDestination->maxPerStageDescriptorUpdateAfterBindInlineUniformBlocks   = pSource->maxPerStageDescriptorUpdateAfterBindInlineUniformBlocks;
        pDestination->maxDescriptorSetInlineUniformBlocks                       = pSource->maxDescriptorSetInlineUniformBlocks;
        pDestination->maxDescriptorSetUpdateAfterBindInlineUniformBlocks        = pSource->maxDescriptorSetUpdateAfterBindInlineUniformBlocks;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceLineRasterizationProperties )            * pDestination,
            VkPhysicalDeviceLineRasterizationPropertiesEXT          const * pSource
    ) noexcept -> Type ( PhysicalDeviceLineRasterizationProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceLineRasterizationProperties;
        pDestination->pNext = nullptr;

        pDestination->lineSubPixelPrecisionBits                                 = pSource->lineSubPixelPrecisionBits;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceMultiDrawProperties )            * pDestination,
            VkPhysicalDeviceMultiDrawPropertiesEXT          const * pSource
    ) noexcept -> Type ( PhysicalDeviceMultiDrawProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceMultiDrawProperties;
        pDestination->pNext = nullptr;

        pDestination->maxMultiDrawCount = pSource->maxMultiDrawCount;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PCI_BUS_INFO_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDevicePCIBusInfoProperties )            * pDestination,
            VkPhysicalDevicePCIBusInfoPropertiesEXT          const * pSource
    ) noexcept -> Type ( PhysicalDevicePCIBusInfoProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDevicePCIBusInfoProperties;
        pDestination->pNext = nullptr;

        pDestination->pciDomain    = pSource->pciDomain;
        pDestination->pciBus       = pSource->pciBus;
        pDestination->pciDevice    = pSource->pciDevice;
        pDestination->pciFunction  = pSource->pciFunction;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PHYSICAL_DEVICE_DRM_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceDRMProperties )            * pDestination,
            VkPhysicalDeviceDrmPropertiesEXT          const * pSource
    ) noexcept -> Type ( PhysicalDeviceDRMProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceDRMProperties;
        pDestination->pNext = nullptr;

        pDestination->hasPrimary    = pSource->hasPrimary;
        pDestination->hasRender     = pSource->hasRender;
        pDestination->primaryMajor  = pSource->primaryMajor;
        pDestination->primaryMinor  = pSource->primaryMinor;
        pDestination->renderMajor   = pSource->renderMajor;
        pDestination->renderMinor   = pSource->renderMinor;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceProvokingVertexProperties )            * pDestination,
            VkPhysicalDeviceProvokingVertexPropertiesEXT          const * pSource
    ) noexcept -> Type ( PhysicalDeviceProvokingVertexProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceProvokingVertexProperties;
        pDestination->pNext = nullptr;

        pDestination->provokingVertexModePerPipeline                        = pSource->provokingVertexModePerPipeline;
        pDestination->transformFeedbackPreservesTriangleFanProvokingVertex  = pSource->transformFeedbackPreservesTriangleFanProvokingVertex;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceRobustnessProperties )            * pDestination,
            VkPhysicalDeviceRobustness2PropertiesEXT          const * pSource
    ) noexcept -> Type ( PhysicalDeviceRobustnessProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceRobustnessProperties;
        pDestination->pNext = nullptr;

        pDestination->robustStorageBufferAccessSizeAlignment                        = pSource->robustStorageBufferAccessSizeAlignment;
        pDestination->robustUniformBufferAccessSizeAlignment                        = pSource->robustUniformBufferAccessSizeAlignment;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceSampleLocationsProperties )            * pDestination,
            VkPhysicalDeviceSampleLocationsPropertiesEXT          const * pSource
    ) noexcept -> Type ( PhysicalDeviceSampleLocationsProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceSampleLocationsProperties;
        pDestination->pNext = nullptr;

        pDestination->sampleLocationSampleCounts                        = pSource->sampleLocationSampleCounts;
        pDestination->maxSampleLocationGridSize                         = pSource->maxSampleLocationGridSize;
        pDestination->sampleLocationSubPixelBits                        = pSource->sampleLocationSubPixelBits;
        pDestination->variableSampleLocations                           = pSource->variableSampleLocations;

        pDestination->sampleLocationCoordinateRange[0]                  = pSource->sampleLocationCoordinateRange[0];
        pDestination->sampleLocationCoordinateRange[1]                  = pSource->sampleLocationCoordinateRange[1];

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceSubgroupSizeControlProperties )            * pDestination,
            VkPhysicalDeviceSubgroupSizeControlProperties_t           const * pSource
    ) noexcept -> Type ( PhysicalDeviceSubgroupSizeControlProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceSubgroupSizeControlProperties;
        pDestination->pNext = nullptr;

        pDestination->minSubgroupSize                               = pSource->minSubgroupSize;
        pDestination->maxSubgroupSize                               = pSource->maxSubgroupSize;
        pDestination->maxComputeWorkgroupSubgroups                  = pSource->maxComputeWorkgroupSubgroups;
        pDestination->requiredSubgroupSizeStages                    = pSource->requiredSubgroupSizeStages;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceTexelBufferAlignmentProperties )            * pDestination,
            VkPhysicalDeviceTexelBufferAlignmentProperties_t           const * pSource
    ) noexcept -> Type ( PhysicalDeviceTexelBufferAlignmentProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceTexelBufferAlignmentProperties;
        pDestination->pNext = nullptr;

        pDestination->storageTexelBufferOffsetAlignmentBytes        = pSource->storageTexelBufferOffsetAlignmentBytes;
        pDestination->storageTexelBufferOffsetSingleTexelAlignment  = pSource->storageTexelBufferOffsetSingleTexelAlignment;
        pDestination->uniformTexelBufferOffsetAlignmentBytes        = pSource->uniformTexelBufferOffsetAlignmentBytes;
        pDestination->uniformTexelBufferOffsetSingleTexelAlignment  = pSource->uniformTexelBufferOffsetSingleTexelAlignment;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceTransformFeedbackProperties )             * pDestination,
            VkPhysicalDeviceTransformFeedbackPropertiesEXT           const * pSource
    ) noexcept -> Type ( PhysicalDeviceTransformFeedbackProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceTransformFeedbackProperties;
        pDestination->pNext = nullptr;

        pDestination->maxTransformFeedbackStreams                   = pSource->maxTransformFeedbackStreams;
        pDestination->maxTransformFeedbackBuffers                   = pSource->maxTransformFeedbackBuffers;
        pDestination->maxTransformFeedbackBufferSize                = pSource->maxTransformFeedbackBufferSize;
        pDestination->maxTransformFeedbackStreamDataSize            = pSource->maxTransformFeedbackStreamDataSize;
        pDestination->maxTransformFeedbackBufferDataSize            = pSource->maxTransformFeedbackBufferDataSize;
        pDestination->maxTransformFeedbackBufferDataStride          = pSource->maxTransformFeedbackBufferDataStride;
        pDestination->transformFeedbackQueries                      = pSource->transformFeedbackQueries;
        pDestination->transformFeedbackStreamsLinesTriangles        = pSource->transformFeedbackStreamsLinesTriangles;
        pDestination->transformFeedbackRasterizationStreamSelect    = pSource->transformFeedbackRasterizationStreamSelect;
        pDestination->transformFeedbackDraw                         = pSource->transformFeedbackDraw;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceVertexAttributeDivisorProperties )             * pDestination,
            VkPhysicalDeviceVertexAttributeDivisorPropertiesEXT           const * pSource
    ) noexcept -> Type ( PhysicalDeviceVertexAttributeDivisorProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceVertexAttributeDivisorProperties;
        pDestination->pNext = nullptr;

        pDestination->maxVertexAttribDivisor                         = pSource->maxVertexAttribDivisor;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceAccelerationStructureProperties )             * pDestination,
            VkPhysicalDeviceAccelerationStructurePropertiesKHR           const * pSource
    ) noexcept -> Type ( PhysicalDeviceAccelerationStructureProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceAccelerationStructureProperties;
        pDestination->pNext = nullptr;

        pDestination->maxGeometryCount                                           = pSource->maxGeometryCount;
        pDestination->maxInstanceCount                                           = pSource->maxInstanceCount;
        pDestination->maxPrimitiveCount                                          = pSource->maxPrimitiveCount;
        pDestination->maxPerStageDescriptorAccelerationStructures                = pSource->maxPerStageDescriptorAccelerationStructures;
        pDestination->maxPerStageDescriptorUpdateAfterBindAccelerationStructures = pSource->maxPerStageDescriptorUpdateAfterBindAccelerationStructures;
        pDestination->maxDescriptorSetAccelerationStructures                     = pSource->maxDescriptorSetAccelerationStructures;
        pDestination->maxDescriptorSetUpdateAfterBindAccelerationStructures      = pSource->maxDescriptorSetUpdateAfterBindAccelerationStructures;
        pDestination->minAccelerationStructureScratchOffsetAlignment             = pSource->minAccelerationStructureScratchOffsetAlignment;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceFragmentShadingRateProperties )             * pDestination,
            VkPhysicalDeviceFragmentShadingRatePropertiesKHR           const * pSource
    ) noexcept -> Type ( PhysicalDeviceFragmentShadingRateProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceFragmentShadingRateProperties;
        pDestination->pNext = nullptr;

        pDestination->maxFragmentShadingRateAttachmentTexelSize                 = pSource->maxFragmentShadingRateAttachmentTexelSize;
        pDestination->minFragmentShadingRateAttachmentTexelSize                 = pSource->minFragmentShadingRateAttachmentTexelSize;
        pDestination->maxFragmentShadingRateAttachmentTexelSizeAspectRatio      = pSource->maxFragmentShadingRateAttachmentTexelSizeAspectRatio;
        pDestination->primitiveFragmentShadingRateWithMultipleViewports         = pSource->primitiveFragmentShadingRateWithMultipleViewports;
        pDestination->layeredShadingRateAttachments                             = pSource->layeredShadingRateAttachments;

        pDestination->fragmentShadingRateNonTrivialCombinerOps                  = pSource->fragmentShadingRateNonTrivialCombinerOps;
        pDestination->maxFragmentSize                                           = pSource->maxFragmentSize;
        pDestination->maxFragmentSizeAspectRatio                                = pSource->maxFragmentSizeAspectRatio;
        pDestination->maxFragmentShadingRateCoverageSamples                     = pSource->maxFragmentShadingRateCoverageSamples;
        pDestination->maxFragmentShadingRateRasterizationSamples                = static_cast < vulkan :: __C_ENG_TYPE ( SampleCountFlag ) > ( pSource->maxFragmentShadingRateRasterizationSamples );

        pDestination->fragmentShadingRateWithShaderDepthStencilWrites           = pSource->fragmentShadingRateWithShaderDepthStencilWrites;
        pDestination->fragmentShadingRateWithSampleMask                         = pSource->fragmentShadingRateWithSampleMask;
        pDestination->fragmentShadingRateWithShaderSampleMask                   = pSource->fragmentShadingRateWithShaderSampleMask;
        pDestination->fragmentShadingRateWithConservativeRasterization          = pSource->fragmentShadingRateWithConservativeRasterization;
        pDestination->fragmentShadingRateWithFragmentShaderInterlock            = pSource->fragmentShadingRateWithFragmentShaderInterlock;

        pDestination->fragmentShadingRateWithCustomSampleLocations              = pSource->fragmentShadingRateWithCustomSampleLocations;
        pDestination->fragmentShadingRateStrictMultiplyCombiner                 = pSource->fragmentShadingRateStrictMultiplyCombiner;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceMaintenance4Properties )             * pDestination,
            VkPhysicalDeviceMaintenance4Properties_t            const * pSource
    ) noexcept -> Type ( PhysicalDeviceMaintenance4Properties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceMaintenance4Properties;
        pDestination->pNext = nullptr;

        pDestination->maxBufferSize                 = pSource->maxBufferSize;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDevicePerformanceQueryProperties )              * pDestination,
            VkPhysicalDevicePerformanceQueryPropertiesKHR            const * pSource
    ) noexcept -> Type ( PhysicalDevicePerformanceQueryProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDevicePerformanceQueryProperties;
        pDestination->pNext = nullptr;

        pDestination->allowCommandBufferQueryCopies                 = pSource->allowCommandBufferQueryCopies;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDevicePortabilitySubsetProperties )              * pDestination,
            VkPhysicalDevicePortabilitySubsetPropertiesKHR            const * pSource
    ) noexcept -> Type ( PhysicalDevicePortabilitySubsetProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDevicePortabilitySubsetProperties;
        pDestination->pNext = nullptr;

        pDestination->minVertexInputBindingStrideAlignment = pSource->minVertexInputBindingStrideAlignment;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PUSH_DESCRIPTOR_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDevicePushDescriptorProperties )              * pDestination,
            VkPhysicalDevicePushDescriptorPropertiesKHR            const * pSource
    ) noexcept -> Type ( PhysicalDevicePushDescriptorProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDevicePushDescriptorProperties;
        pDestination->pNext = nullptr;

        pDestination->maxPushDescriptors = pSource->maxPushDescriptors;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceRayTracingPipelineProperties )              * pDestination,
            VkPhysicalDeviceRayTracingPipelinePropertiesKHR            const * pSource
    ) noexcept -> Type ( PhysicalDeviceRayTracingPipelineProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceRayTracingPipelineProperties;
        pDestination->pNext = nullptr;

        pDestination->shaderGroupHandleSize                = pSource->shaderGroupHandleSize;
        pDestination->maxRayRecursionDepth                 = pSource->maxRayRecursionDepth;
        pDestination->maxShaderGroupStride                 = pSource->maxShaderGroupStride;
        pDestination->shaderGroupBaseAlignment             = pSource->shaderGroupBaseAlignment;
        pDestination->shaderGroupHandleCaptureReplaySize   = pSource->shaderGroupHandleCaptureReplaySize;
        pDestination->maxRayDispatchInvocationCount        = pSource->maxRayDispatchInvocationCount;
        pDestination->shaderGroupHandleAlignment           = pSource->shaderGroupHandleAlignment;
        pDestination->maxRayHitAttributeSize               = pSource->maxRayHitAttributeSize;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceShaderIntegerDotProductProperties )              * pDestination,
            VkPhysicalDeviceShaderIntegerDotProductProperties_t             const * pSource
    ) noexcept -> Type ( PhysicalDeviceShaderIntegerDotProductProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceShaderIntegerDotProductProperties;
        pDestination->pNext = nullptr;

        pDestination->integerDotProduct8BitUnsignedAccelerated                                      = pSource->integerDotProduct8BitUnsignedAccelerated;
        pDestination->integerDotProduct8BitSignedAccelerated                                        = pSource->integerDotProduct8BitSignedAccelerated;
        pDestination->integerDotProduct8BitMixedSignednessAccelerated                               = pSource->integerDotProduct8BitMixedSignednessAccelerated;

        pDestination->integerDotProduct4x8BitPackedUnsignedAccelerated                              = pSource->integerDotProduct4x8BitPackedUnsignedAccelerated;
        pDestination->integerDotProduct4x8BitPackedSignedAccelerated                                = pSource->integerDotProduct4x8BitPackedSignedAccelerated;
        pDestination->integerDotProduct4x8BitPackedMixedSignednessAccelerated                       = pSource->integerDotProduct4x8BitPackedMixedSignednessAccelerated;

        pDestination->integerDotProduct16BitUnsignedAccelerated                                     = pSource->integerDotProduct16BitUnsignedAccelerated;
        pDestination->integerDotProduct16BitSignedAccelerated                                       = pSource->integerDotProduct16BitSignedAccelerated;
        pDestination->integerDotProduct16BitMixedSignednessAccelerated                              = pSource->integerDotProduct16BitMixedSignednessAccelerated;

        pDestination->integerDotProduct32BitUnsignedAccelerated                                     = pSource->integerDotProduct32BitUnsignedAccelerated;
        pDestination->integerDotProduct32BitSignedAccelerated                                       = pSource->integerDotProduct32BitSignedAccelerated;
        pDestination->integerDotProduct32BitMixedSignednessAccelerated                              = pSource->integerDotProduct32BitMixedSignednessAccelerated;

        pDestination->integerDotProduct64BitUnsignedAccelerated                                     = pSource->integerDotProduct64BitUnsignedAccelerated;
        pDestination->integerDotProduct64BitSignedAccelerated                                       = pSource->integerDotProduct64BitSignedAccelerated;
        pDestination->integerDotProduct64BitMixedSignednessAccelerated                              = pSource->integerDotProduct64BitMixedSignednessAccelerated;

        pDestination->integerDotProductAccumulatingSaturating8BitUnsignedAccelerated                = pSource->integerDotProductAccumulatingSaturating8BitUnsignedAccelerated;
        pDestination->integerDotProductAccumulatingSaturating8BitSignedAccelerated                  = pSource->integerDotProductAccumulatingSaturating8BitSignedAccelerated;
        pDestination->integerDotProductAccumulatingSaturating8BitMixedSignednessAccelerated         = pSource->integerDotProductAccumulatingSaturating8BitMixedSignednessAccelerated;

        pDestination->integerDotProductAccumulatingSaturating4x8BitPackedUnsignedAccelerated        = pSource->integerDotProductAccumulatingSaturating4x8BitPackedUnsignedAccelerated;
        pDestination->integerDotProductAccumulatingSaturating4x8BitPackedSignedAccelerated          = pSource->integerDotProductAccumulatingSaturating4x8BitPackedSignedAccelerated;
        pDestination->integerDotProductAccumulatingSaturating4x8BitPackedMixedSignednessAccelerated = pSource->integerDotProductAccumulatingSaturating4x8BitPackedMixedSignednessAccelerated;

        pDestination->integerDotProductAccumulatingSaturating16BitUnsignedAccelerated               = pSource->integerDotProductAccumulatingSaturating16BitUnsignedAccelerated;
        pDestination->integerDotProductAccumulatingSaturating16BitSignedAccelerated                 = pSource->integerDotProductAccumulatingSaturating16BitSignedAccelerated;
        pDestination->integerDotProductAccumulatingSaturating16BitMixedSignednessAccelerated        = pSource->integerDotProductAccumulatingSaturating16BitMixedSignednessAccelerated;

        pDestination->integerDotProductAccumulatingSaturating32BitUnsignedAccelerated               = pSource->integerDotProductAccumulatingSaturating32BitUnsignedAccelerated;
        pDestination->integerDotProductAccumulatingSaturating32BitSignedAccelerated                 = pSource->integerDotProductAccumulatingSaturating32BitSignedAccelerated;
        pDestination->integerDotProductAccumulatingSaturating32BitMixedSignednessAccelerated        = pSource->integerDotProductAccumulatingSaturating32BitMixedSignednessAccelerated;

        pDestination->integerDotProductAccumulatingSaturating64BitUnsignedAccelerated               = pSource->integerDotProductAccumulatingSaturating64BitUnsignedAccelerated;
        pDestination->integerDotProductAccumulatingSaturating64BitSignedAccelerated                 = pSource->integerDotProductAccumulatingSaturating64BitSignedAccelerated;
        pDestination->integerDotProductAccumulatingSaturating64BitMixedSignednessAccelerated        = pSource->integerDotProductAccumulatingSaturating64BitMixedSignednessAccelerated;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceCooperativeMatrixPropertiesNVidia )        * pDestination,
            VkPhysicalDeviceCooperativeMatrixPropertiesNV             const * pSource
    ) noexcept -> Type ( PhysicalDeviceCooperativeMatrixPropertiesNVidia ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceCooperativeMatrixPropertiesNVidia;
        pDestination->pNext = nullptr;

        pDestination->cooperativeMatrixSupportedStages        = pSource->cooperativeMatrixSupportedStages;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceDeviceGeneratedCommandsPropertiesNVidia )        * pDestination,
            VkPhysicalDeviceDeviceGeneratedCommandsPropertiesNV             const * pSource
    ) noexcept -> Type ( PhysicalDeviceDeviceGeneratedCommandsPropertiesNVidia ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceDeviceGeneratedCommandsPropertiesNVidia;
        pDestination->pNext = nullptr;

        pDestination->maxGraphicsShaderGroupCount               = pSource->maxGraphicsShaderGroupCount;
        pDestination->maxIndirectSequenceCount                  = pSource->maxIndirectSequenceCount;
        pDestination->maxIndirectCommandsTokenCount             = pSource->maxIndirectCommandsTokenCount;
        pDestination->maxIndirectCommandsStreamCount            = pSource->maxIndirectCommandsStreamCount;
        pDestination->maxIndirectCommandsTokenOffset            = pSource->maxIndirectCommandsTokenOffset;
        pDestination->maxIndirectCommandsStreamStride           = pSource->maxIndirectCommandsStreamStride;
        pDestination->minSequencesCountBufferOffsetAlignment    = pSource->minSequencesCountBufferOffsetAlignment;
        pDestination->minSequencesIndexBufferOffsetAlignment    = pSource->minSequencesIndexBufferOffsetAlignment;
        pDestination->minIndirectCommandsBufferOffsetAlignment  = pSource->minIndirectCommandsBufferOffsetAlignment;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceFragmentShadingRateEnumsPropertiesNVidia )        * pDestination,
            VkPhysicalDeviceFragmentShadingRateEnumsPropertiesNV             const * pSource
    ) noexcept -> Type ( PhysicalDeviceFragmentShadingRateEnumsPropertiesNVidia ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceFragmentShadingRateEnumsPropertiesNVidia;
        pDestination->pNext = nullptr;

        pDestination->maxFragmentShadingRateInvocationCount  = static_cast < vulkan :: __C_ENG_TYPE ( SampleCountFlag ) > ( pSource->maxFragmentShadingRateInvocationCount );

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceMeshShaderPropertiesNVidia )        * pDestination,
            VkPhysicalDeviceMeshShaderPropertiesNV             const * pSource
    ) noexcept -> Type ( PhysicalDeviceMeshShaderPropertiesNVidia ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceMeshShaderPropertiesNVidia;
        pDestination->pNext = nullptr;

        pDestination->maxDrawMeshTasksCount             = pSource->maxDrawMeshTasksCount;
        pDestination->maxTaskWorkGroupInvocations       = pSource->maxTaskWorkGroupInvocations;
        pDestination->maxTaskTotalMemorySize            = pSource->maxTaskTotalMemorySize;
        pDestination->maxTaskOutputCount                = pSource->maxTaskOutputCount;
        pDestination->maxMeshWorkGroupInvocations       = pSource->maxMeshWorkGroupInvocations;
        pDestination->maxMeshTotalMemorySize            = pSource->maxMeshTotalMemorySize;
        pDestination->maxMeshOutputVertices             = pSource->maxMeshOutputVertices;
        pDestination->maxMeshOutputPrimitives           = pSource->maxMeshOutputPrimitives;
        pDestination->maxMeshMultiviewViewCount         = pSource->maxMeshMultiviewViewCount;
        pDestination->meshOutputPerVertexGranularity    = pSource->meshOutputPerVertexGranularity;
        pDestination->meshOutputPerPrimitiveGranularity = pSource->meshOutputPerPrimitiveGranularity;

        pDestination->maxTaskWorkGroupSize[0]           = pSource->maxTaskWorkGroupSize[0];
        pDestination->maxTaskWorkGroupSize[1]           = pSource->maxTaskWorkGroupSize[1];
        pDestination->maxTaskWorkGroupSize[2]           = pSource->maxTaskWorkGroupSize[2];

        pDestination->maxMeshWorkGroupSize[0]           = pSource->maxMeshWorkGroupSize[0];
        pDestination->maxMeshWorkGroupSize[1]           = pSource->maxMeshWorkGroupSize[1];
        pDestination->maxMeshWorkGroupSize[2]           = pSource->maxMeshWorkGroupSize[2];

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceRayTracingPropertiesNVidia )        * pDestination,
            VkPhysicalDeviceRayTracingPropertiesNV             const * pSource
    ) noexcept -> Type ( PhysicalDeviceRayTracingPropertiesNVidia ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceRayTracingPropertiesNVidia;
        pDestination->pNext = nullptr;

        pDestination->shaderGroupHandleSize                     = pSource->shaderGroupHandleSize;
        pDestination->maxRecursionDepth                         = pSource->maxRecursionDepth;
        pDestination->maxShaderGroupStride                      = pSource->maxShaderGroupStride;
        pDestination->shaderGroupBaseAlignment                  = pSource->shaderGroupBaseAlignment;
        pDestination->maxGeometryCount                          = pSource->maxGeometryCount;
        pDestination->maxInstanceCount                          = pSource->maxInstanceCount;
        pDestination->maxTriangleCount                          = pSource->maxTriangleCount;
        pDestination->maxDescriptorSetAccelerationStructures    = pSource->maxDescriptorSetAccelerationStructures;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceShaderSMBuiltinsPropertiesNVidia )        * pDestination,
            VkPhysicalDeviceShaderSMBuiltinsPropertiesNV             const * pSource
    ) noexcept -> Type ( PhysicalDeviceShaderSMBuiltinsPropertiesNVidia ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceShaderSmBuiltinsPropertiesNVidia;
        pDestination->pNext = nullptr;

        pDestination->shaderSMCount         = pSource->shaderSMCount;
        pDestination->shaderWarpsPerSM      = pSource->shaderWarpsPerSM;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceShadingRateImagePropertiesNVidia )        * pDestination,
            VkPhysicalDeviceShadingRateImagePropertiesNV             const * pSource
    ) noexcept -> Type ( PhysicalDeviceShadingRateImagePropertiesNVidia ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceShadingRateImagePropertiesNVidia;
        pDestination->pNext = nullptr;

        pDestination->shadingRateTexelSize          = pSource->shadingRateTexelSize;
        pDestination->shadingRatePaletteSize        = pSource->shadingRatePaletteSize;
        pDestination->shadingRateMaxCoarseSamples   = pSource->shadingRateMaxCoarseSamples;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceMultiviewPerViewAttributesPropertiesNVidia )         * pDestination,
            VkPhysicalDeviceMultiviewPerViewAttributesPropertiesNVX             const * pSource
    ) noexcept -> Type ( PhysicalDeviceMultiviewPerViewAttributesPropertiesNVidia ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceMultiviewPerViewAttributesPropertiesNVidiaExperimental;
        pDestination->pNext = nullptr;

        pDestination->perViewPositionAllComponents   = pSource->perViewPositionAllComponents;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceShaderCorePropertiesAMD )            * pDestination,
            VkPhysicalDeviceShaderCorePropertiesAMD             const * pSource
    ) noexcept -> Type ( PhysicalDeviceShaderCorePropertiesAMD ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceShaderCorePropertiesAMD;
        pDestination->pNext = nullptr;

        pDestination->shaderEngineCount             = pSource->shaderEngineCount;
        pDestination->shaderArraysPerEngineCount    = pSource->shaderArraysPerEngineCount;
        pDestination->computeUnitsPerShaderArray    = pSource->computeUnitsPerShaderArray;
        pDestination->simdPerComputeUnit            = pSource->simdPerComputeUnit;
        pDestination->wavefrontsPerSimd             = pSource->wavefrontsPerSimd;
        pDestination->wavefrontSize                 = pSource->wavefrontSize;
        pDestination->sgprsPerSimd                  = pSource->sgprsPerSimd;
        pDestination->minSgprAllocation             = pSource->minSgprAllocation;
        pDestination->maxSgprAllocation             = pSource->maxSgprAllocation;
        pDestination->sgprAllocationGranularity     = pSource->sgprAllocationGranularity;
        pDestination->vgprsPerSimd                  = pSource->vgprsPerSimd;
        pDestination->minVgprAllocation             = pSource->minVgprAllocation;
        pDestination->maxVgprAllocation             = pSource->maxVgprAllocation;
        pDestination->vgprAllocationGranularity     = pSource->vgprAllocationGranularity;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_2_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceShaderCoreProperties2AMD )            * pDestination,
            VkPhysicalDeviceShaderCoreProperties2AMD             const * pSource
    ) noexcept -> Type ( PhysicalDeviceShaderCoreProperties2AMD ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceShaderCoreProperties2AMD;
        pDestination->pNext = nullptr;

        pDestination->shaderCoreFeatures            = pSource->shaderCoreFeatures;
        pDestination->activeComputeUnitCount        = pSource->activeComputeUnitCount;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceFragmentDensityMapOffsetPropertiesQualcomm )            * pDestination,
            VkPhysicalDeviceFragmentDensityMapOffsetPropertiesQCOM                 const * pSource
    ) noexcept -> Type ( PhysicalDeviceFragmentDensityMapOffsetPropertiesQualcomm ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceFragmentDensityMapOffsetPropertiesQualcomm;
        pDestination->pNext = nullptr;

        pDestination->fragmentDensityOffsetGranularity = pSource->fragmentDensityOffsetGranularity;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceSubpassShadingPropertiesHuawei )            * pDestination,
            VkPhysicalDeviceSubpassShadingPropertiesHUAWEI                 const * pSource
    ) noexcept -> Type ( PhysicalDeviceSubpassShadingPropertiesHuawei ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceSubpassShadingPropertiesHuawei;
        pDestination->pNext = nullptr;

        pDestination->maxSubpassShadingWorkgroupSizeAspectRatio = pSource->maxSubpassShadingWorkgroupSizeAspectRatio;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_4444_FORMATS_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDevice4444FormatsFeatures )           * pDestination,
            VkPhysicalDevice4444FormatsFeaturesEXT         const * pSource
    ) noexcept -> Type ( PhysicalDevice4444FormatsFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDevice4444FormatsFeatures;
        pDestination->pNext = nullptr;

        pDestination->formatA4R4G4B4            = pSource->formatA4R4G4B4;
        pDestination->formatA4B4G4R4            = pSource->formatA4B4G4R4;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_4444_FORMATS_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDevice4444FormatsFeaturesEXT               * pDestination,
            Type ( PhysicalDevice4444FormatsFeatures )  const * pSource
    ) noexcept -> VkPhysicalDevice4444FormatsFeaturesEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_4444_FORMATS_FEATURES_EXT;
        pDestination->pNext = nullptr;

        pDestination->formatA4R4G4B4            = pSource->formatA4R4G4B4;
        pDestination->formatA4B4G4R4            = pSource->formatA4B4G4R4;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceVulkan13Features               * pDestination,
            Type ( PhysicalDeviceVulkan13Features )  const * pSource
    ) noexcept -> VkPhysicalDeviceVulkan13Features * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES;
        pDestination->pNext = nullptr;

        pDestination->robustImageAccess                                     = pSource->robustImageAccess;
        pDestination->inlineUniformBlock                                    = pSource->inlineUniformBlock;
        pDestination->descriptorBindingInlineUniformBlockUpdateAfterBind    = pSource->descriptorBindingInlineUniformBlockUpdateAfterBind;
        pDestination->pipelineCreationCacheControl                          = pSource->pipelineCreationCacheControl;
        pDestination->privateData                                           = pSource->privateData;
        pDestination->shaderDemoteToHelperInvocation                        = pSource->shaderDemoteToHelperInvocation;
        pDestination->shaderTerminateInvocation                             = pSource->shaderTerminateInvocation;
        pDestination->subgroupSizeControl                                   = pSource->subgroupSizeControl;
        pDestination->computeFullSubgroups                                  = pSource->computeFullSubgroups;
        pDestination->synchronization2                                      = pSource->synchronization2;
        pDestination->textureCompressionASTC_HDR                            = pSource->textureCompressionASTC_HDR;
        pDestination->shaderZeroInitializeWorkgroupMemory                   = pSource->shaderZeroInitializeWorkgroupMemory;
        pDestination->dynamicRendering                                      = pSource->dynamicRendering;
        pDestination->shaderIntegerDotProduct                               = pSource->shaderIntegerDotProduct;
        pDestination->maintenance4                                          = pSource->maintenance4;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXTURE_COMPRESSION_ASTC_HDR_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceASTCDecodeFeatures )           * pDestination,
            VkPhysicalDeviceASTCDecodeFeaturesEXT         const * pSource
    ) noexcept -> Type ( PhysicalDeviceASTCDecodeFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceASTCDecodeFeatures;
        pDestination->pNext = nullptr;

        pDestination->decodeModeSharedExponent            = pSource->decodeModeSharedExponent;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXTURE_COMPRESSION_ASTC_HDR_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceASTCDecodeFeaturesEXT               * pDestination,
            Type ( PhysicalDeviceASTCDecodeFeatures )  const * pSource
    ) noexcept -> VkPhysicalDeviceASTCDecodeFeaturesEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ASTC_DECODE_FEATURES_EXT;
        pDestination->pNext = nullptr;

        pDestination->decodeModeSharedExponent            = pSource->decodeModeSharedExponent;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceBlendOperationAdvancedFeatures )           * pDestination,
            VkPhysicalDeviceBlendOperationAdvancedFeaturesEXT         const * pSource
    ) noexcept -> Type ( PhysicalDeviceBlendOperationAdvancedFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceBlendOperationAdvancedFeatures;
        pDestination->pNext = nullptr;

        pDestination->advancedBlendCoherentOperations            = pSource->advancedBlendCoherentOperations;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceBlendOperationAdvancedFeaturesEXT               * pDestination,
            Type ( PhysicalDeviceBlendOperationAdvancedFeatures )  const * pSource
    ) noexcept -> VkPhysicalDeviceBlendOperationAdvancedFeaturesEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BLEND_OPERATION_ADVANCED_FEATURES_EXT;
        pDestination->pNext = nullptr;

        pDestination->advancedBlendCoherentOperations            = pSource->advancedBlendCoherentOperations;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_BORDER_COLOR_SWIZZLE_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceBorderColorSwizzleFeatures )           * pDestination,
            VkPhysicalDeviceBorderColorSwizzleFeaturesEXT         const * pSource
    ) noexcept -> Type ( PhysicalDeviceBorderColorSwizzleFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceBorderColorSwizzleFeatures;
        pDestination->pNext = nullptr;

        pDestination->borderColorSwizzle                = pSource->borderColorSwizzle;
        pDestination->borderColorSwizzleFromImage       = pSource->borderColorSwizzleFromImage;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_BORDER_COLOR_SWIZZLE_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceBorderColorSwizzleFeaturesEXT               * pDestination,
            Type ( PhysicalDeviceBorderColorSwizzleFeatures )  const * pSource
    ) noexcept -> VkPhysicalDeviceBorderColorSwizzleFeaturesEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BORDER_COLOR_SWIZZLE_FEATURES_EXT;
        pDestination->pNext = nullptr;

        pDestination->borderColorSwizzle                = pSource->borderColorSwizzle;
        pDestination->borderColorSwizzleFromImage       = pSource->borderColorSwizzleFromImage;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_COLOR_WRITE_ENABLE_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceColorWriteEnableFeatures )           * pDestination,
            VkPhysicalDeviceColorWriteEnableFeaturesEXT         const * pSource
    ) noexcept -> Type ( PhysicalDeviceColorWriteEnableFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceColorWriteEnableFeatures;
        pDestination->pNext = nullptr;

        pDestination->colorWriteEnable                  = pSource->colorWriteEnable;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_COLOR_WRITE_ENABLE_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceColorWriteEnableFeaturesEXT               * pDestination,
            Type ( PhysicalDeviceColorWriteEnableFeatures )  const * pSource
    ) noexcept -> VkPhysicalDeviceColorWriteEnableFeaturesEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COLOR_WRITE_ENABLE_FEATURES_EXT;
        pDestination->pNext = nullptr;

        pDestination->colorWriteEnable                  = pSource->colorWriteEnable;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceConditionalRenderingFeatures )           * pDestination,
            VkPhysicalDeviceConditionalRenderingFeaturesEXT         const * pSource
    ) noexcept -> Type ( PhysicalDeviceConditionalRenderingFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceConditionalRenderingFeatures;
        pDestination->pNext = nullptr;

        pDestination->conditionalRendering              = pSource->conditionalRendering;
        pDestination->inheritedConditionalRendering     = pSource->inheritedConditionalRendering;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceConditionalRenderingFeaturesEXT            * pDestination,
            Type ( PhysicalDeviceConditionalRenderingFeatures )  const * pSource
    ) noexcept -> VkPhysicalDeviceConditionalRenderingFeaturesEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CONDITIONAL_RENDERING_FEATURES_EXT;
        pDestination->pNext = nullptr;

        pDestination->conditionalRendering              = pSource->conditionalRendering;
        pDestination->inheritedConditionalRendering     = pSource->inheritedConditionalRendering;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceCustomBorderColorFeatures )           * pDestination,
            VkPhysicalDeviceCustomBorderColorFeaturesEXT         const * pSource
    ) noexcept -> Type ( PhysicalDeviceCustomBorderColorFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceCustomBorderColorFeatures;
        pDestination->pNext = nullptr;

        pDestination->customBorderColors                = pSource->customBorderColors;
        pDestination->customBorderColorWithoutFormat    = pSource->customBorderColorWithoutFormat;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceCustomBorderColorFeaturesEXT            * pDestination,
            Type ( PhysicalDeviceCustomBorderColorFeatures )  const * pSource
    ) noexcept -> VkPhysicalDeviceCustomBorderColorFeaturesEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CUSTOM_BORDER_COLOR_FEATURES_EXT;
        pDestination->pNext = nullptr;

        pDestination->customBorderColors                = pSource->customBorderColors;
        pDestination->customBorderColorWithoutFormat    = pSource->customBorderColorWithoutFormat;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_CONTROL_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceDepthClipControlFeatures )           * pDestination,
            VkPhysicalDeviceDepthClipControlFeaturesEXT         const * pSource
    ) noexcept -> Type ( PhysicalDeviceDepthClipControlFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceDepthClipControlFeatures;
        pDestination->pNext = nullptr;

        pDestination->depthClipControl                = pSource->depthClipControl;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_CONTROL_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceDepthClipControlFeaturesEXT            * pDestination,
            Type ( PhysicalDeviceDepthClipControlFeatures )  const * pSource
    ) noexcept -> VkPhysicalDeviceDepthClipControlFeaturesEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_CLIP_CONTROL_FEATURES_EXT;
        pDestination->pNext = nullptr;

        pDestination->depthClipControl                = pSource->depthClipControl;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_ENABLE_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceDepthClipEnableFeatures )           * pDestination,
            VkPhysicalDeviceDepthClipEnableFeaturesEXT         const * pSource
    ) noexcept -> Type ( PhysicalDeviceDepthClipEnableFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceDepthClipEnableFeatures;
        pDestination->pNext = nullptr;

        pDestination->depthClipEnable                = pSource->depthClipEnable;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_ENABLE_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceDepthClipEnableFeaturesEXT            * pDestination,
            Type ( PhysicalDeviceDepthClipEnableFeatures )  const * pSource
    ) noexcept -> VkPhysicalDeviceDepthClipEnableFeaturesEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_CLIP_ENABLE_FEATURES_EXT;
        pDestination->pNext = nullptr;

        pDestination->depthClipEnable                = pSource->depthClipEnable;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEVICE_MEMORY_REPORT_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceDeviceMemoryReportFeatures )           * pDestination,
            VkPhysicalDeviceDeviceMemoryReportFeaturesEXT         const * pSource
    ) noexcept -> Type ( PhysicalDeviceDeviceMemoryReportFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceDeviceMemoryReportFeatures;
        pDestination->pNext = nullptr;

        pDestination->deviceMemoryReport                = pSource->deviceMemoryReport;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEVICE_MEMORY_REPORT_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceDeviceMemoryReportFeaturesEXT            * pDestination,
            Type ( PhysicalDeviceDeviceMemoryReportFeatures )  const * pSource
    ) noexcept -> VkPhysicalDeviceDeviceMemoryReportFeaturesEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEVICE_MEMORY_REPORT_FEATURES_EXT;
        pDestination->pNext = nullptr;

        pDestination->deviceMemoryReport                = pSource->deviceMemoryReport;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceExtendedDynamicStateFeatures )           * pDestination,
            VkPhysicalDeviceExtendedDynamicStateFeaturesEXT         const * pSource
    ) noexcept -> Type ( PhysicalDeviceExtendedDynamicStateFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceExtendedDynamicStateFeatures;
        pDestination->pNext = nullptr;

        pDestination->extendedDynamicState  = pSource->extendedDynamicState;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceExtendedDynamicStateFeaturesEXT            * pDestination,
            Type ( PhysicalDeviceExtendedDynamicStateFeatures )  const * pSource
    ) noexcept -> VkPhysicalDeviceExtendedDynamicStateFeaturesEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_DYNAMIC_STATE_FEATURES_EXT;
        pDestination->pNext = nullptr;

        pDestination->extendedDynamicState  = pSource->extendedDynamicState;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_2_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceExtendedDynamicState2Features )           * pDestination,
            VkPhysicalDeviceExtendedDynamicState2FeaturesEXT         const * pSource
    ) noexcept -> Type ( PhysicalDeviceExtendedDynamicState2Features ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceExtendedDynamicState2Features;
        pDestination->pNext = nullptr;

        pDestination->extendedDynamicState2                     = pSource->extendedDynamicState2;
        pDestination->extendedDynamicState2LogicOp              = pSource->extendedDynamicState2LogicOp;
        pDestination->extendedDynamicState2PatchControlPoints   = pSource->extendedDynamicState2PatchControlPoints;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_2_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceExtendedDynamicState2FeaturesEXT            * pDestination,
            Type ( PhysicalDeviceExtendedDynamicState2Features )  const * pSource
    ) noexcept -> VkPhysicalDeviceExtendedDynamicState2FeaturesEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_DYNAMIC_STATE_2_FEATURES_EXT;
        pDestination->pNext = nullptr;

        pDestination->extendedDynamicState2                     = pSource->extendedDynamicState2;
        pDestination->extendedDynamicState2LogicOp              = pSource->extendedDynamicState2LogicOp;
        pDestination->extendedDynamicState2PatchControlPoints   = pSource->extendedDynamicState2PatchControlPoints;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceFragmentDensityMapFeatures )           * pDestination,
            VkPhysicalDeviceFragmentDensityMapFeaturesEXT         const * pSource
    ) noexcept -> Type ( PhysicalDeviceFragmentDensityMapFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceFragmentDensityMapFeatures;
        pDestination->pNext = nullptr;

        pDestination->fragmentDensityMap                    = pSource->fragmentDensityMap;
        pDestination->fragmentDensityMapDynamic             = pSource->fragmentDensityMapDynamic;
        pDestination->fragmentDensityMapNonSubsampledImages = pSource->fragmentDensityMapNonSubsampledImages;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceFragmentDensityMapFeaturesEXT            * pDestination,
            Type ( PhysicalDeviceFragmentDensityMapFeatures )  const * pSource
    ) noexcept -> VkPhysicalDeviceFragmentDensityMapFeaturesEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_FEATURES_EXT;
        pDestination->pNext = nullptr;

        pDestination->fragmentDensityMap                    = pSource->fragmentDensityMap;
        pDestination->fragmentDensityMapDynamic             = pSource->fragmentDensityMapDynamic;
        pDestination->fragmentDensityMapNonSubsampledImages = pSource->fragmentDensityMapNonSubsampledImages;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceFragmentDensityMap2Features )           * pDestination,
            VkPhysicalDeviceFragmentDensityMap2FeaturesEXT         const * pSource
    ) noexcept -> Type ( PhysicalDeviceFragmentDensityMap2Features ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceFragmentDensityMap2Features;
        pDestination->pNext = nullptr;

        pDestination->fragmentDensityMapDeferred = pSource->fragmentDensityMapDeferred;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceFragmentDensityMap2FeaturesEXT            * pDestination,
            Type ( PhysicalDeviceFragmentDensityMap2Features )  const * pSource
    ) noexcept -> VkPhysicalDeviceFragmentDensityMap2FeaturesEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_2_FEATURES_EXT;
        pDestination->pNext = nullptr;

        pDestination->fragmentDensityMapDeferred = pSource->fragmentDensityMapDeferred;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_SHADER_INTERLOCK_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceFragmentShaderInterlockFeatures )           * pDestination,
            VkPhysicalDeviceFragmentShaderInterlockFeaturesEXT         const * pSource
    ) noexcept -> Type ( PhysicalDeviceFragmentShaderInterlockFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceFragmentShaderInterlockFeatures;
        pDestination->pNext = nullptr;

        pDestination->fragmentShaderSampleInterlock         = pSource->fragmentShaderSampleInterlock;
        pDestination->fragmentShaderPixelInterlock          = pSource->fragmentShaderPixelInterlock;
        pDestination->fragmentShaderShadingRateInterlock    = pSource->fragmentShaderShadingRateInterlock;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_SHADER_INTERLOCK_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceFragmentShaderInterlockFeaturesEXT            * pDestination,
            Type ( PhysicalDeviceFragmentShaderInterlockFeatures )  const * pSource
    ) noexcept -> VkPhysicalDeviceFragmentShaderInterlockFeaturesEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADER_INTERLOCK_FEATURES_EXT;
        pDestination->pNext = nullptr;

        pDestination->fragmentShaderSampleInterlock         = pSource->fragmentShaderSampleInterlock;
        pDestination->fragmentShaderPixelInterlock          = pSource->fragmentShaderPixelInterlock;
        pDestination->fragmentShaderShadingRateInterlock    = pSource->fragmentShaderShadingRateInterlock;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceGlobalPriorityQueryFeatures )           * pDestination,
            VkPhysicalDeviceGlobalPriorityQueryFeaturesEXT         const * pSource
    ) noexcept -> Type ( PhysicalDeviceGlobalPriorityQueryFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceGlobalPriorityQueryFeatures;
        pDestination->pNext = nullptr;

        pDestination->globalPriorityQuery         = pSource->globalPriorityQuery;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceGlobalPriorityQueryFeaturesEXT            * pDestination,
            Type ( PhysicalDeviceGlobalPriorityQueryFeatures )  const * pSource
    ) noexcept -> VkPhysicalDeviceGlobalPriorityQueryFeaturesEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GLOBAL_PRIORITY_QUERY_FEATURES_EXT;
        pDestination->pNext = nullptr;

        pDestination->globalPriorityQuery         = pSource->globalPriorityQuery;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_ROBUSTNESS_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceImageRobustnessFeatures )           * pDestination,
            VkPhysicalDeviceImageRobustnessFeatures_t          const * pSource
    ) noexcept -> Type ( PhysicalDeviceImageRobustnessFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceImageRobustnessFeatures;
        pDestination->pNext = nullptr;

        pDestination->robustImageAccess         = pSource->robustImageAccess;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_ROBUSTNESS_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceImageRobustnessFeatures_t             * pDestination,
            Type ( PhysicalDeviceImageRobustnessFeatures )  const * pSource
    ) noexcept -> VkPhysicalDeviceImageRobustnessFeatures_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_ROBUSTNESS_FEATURES;
#elif __C_ENG_VULKAN_API_EXTENSION_IMAGE_ROBUSTNESS_AVAILABLE
        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_ROBUSTNESS_FEATURES_EXT;
#endif
        pDestination->pNext = nullptr;

        pDestination->robustImageAccess         = pSource->robustImageAccess;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_VIEW_MIN_LOD_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceImageViewMinLODFeatures )            * pDestination,
            VkPhysicalDeviceImageViewMinLodFeaturesEXT          const * pSource
    ) noexcept -> Type ( PhysicalDeviceImageViewMinLODFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceImageViewMinLODFeatures;
        pDestination->pNext = nullptr;

        pDestination->minLOD         = pSource->minLod;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_VIEW_MIN_LOD_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceImageViewMinLodFeaturesEXT             * pDestination,
            Type ( PhysicalDeviceImageViewMinLODFeatures )   const * pSource
    ) noexcept -> VkPhysicalDeviceImageViewMinLodFeaturesEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_VIEW_MIN_LOD_FEATURES_EXT;
        pDestination->pNext = nullptr;

        pDestination->minLod         = pSource->minLOD;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INDEX_TYPE_UINT8_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceIndexTypeUInt8Features )            * pDestination,
            VkPhysicalDeviceIndexTypeUint8FeaturesEXT          const * pSource
    ) noexcept -> Type ( PhysicalDeviceIndexTypeUInt8Features ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceIndexTypeUInt8Features;
        pDestination->pNext = nullptr;

        pDestination->indexTypeUInt8         = pSource->indexTypeUint8;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INDEX_TYPE_UINT8_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceIndexTypeUint8FeaturesEXT             * pDestination,
            Type ( PhysicalDeviceIndexTypeUInt8Features )   const * pSource
    ) noexcept -> VkPhysicalDeviceIndexTypeUint8FeaturesEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INDEX_TYPE_UINT8_FEATURES_EXT;
        pDestination->pNext = nullptr;

        pDestination->indexTypeUint8         = pSource->indexTypeUInt8;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceInlineUniformBlockFeatures )            * pDestination,
            VkPhysicalDeviceInlineUniformBlockFeatures_t           const * pSource
    ) noexcept -> Type ( PhysicalDeviceInlineUniformBlockFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceInlineUniformBlockFeatures;
        pDestination->pNext = nullptr;

        pDestination->inlineUniformBlock                                    = pSource->inlineUniformBlock;
        pDestination->descriptorBindingInlineUniformBlockUpdateAfterBind    = pSource->descriptorBindingInlineUniformBlockUpdateAfterBind;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceInlineUniformBlockFeatures_t              * pDestination,
            Type ( PhysicalDeviceInlineUniformBlockFeatures )   const * pSource
    ) noexcept -> VkPhysicalDeviceInlineUniformBlockFeatures_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INLINE_UNIFORM_BLOCK_FEATURES;
#elif __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE
        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INLINE_UNIFORM_BLOCK_FEATURES_EXT;
#endif
        pDestination->pNext = nullptr;

        pDestination->inlineUniformBlock                                    = pSource->inlineUniformBlock;
        pDestination->descriptorBindingInlineUniformBlockUpdateAfterBind    = pSource->descriptorBindingInlineUniformBlockUpdateAfterBind;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceLineRasterizationFeatures )             * pDestination,
            VkPhysicalDeviceLineRasterizationFeaturesEXT           const * pSource
    ) noexcept -> Type ( PhysicalDeviceLineRasterizationFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceLineRasterizationFeatures;
        pDestination->pNext = nullptr;

        pDestination->rectangularLines          = pSource->rectangularLines;
        pDestination->bresenhamLines            = pSource->bresenhamLines;
        pDestination->smoothLines               = pSource->smoothLines;
        pDestination->stippledRectangularLines  = pSource->stippledRectangularLines;
        pDestination->stippledBresenhamLines    = pSource->stippledBresenhamLines;
        pDestination->stippledSmoothLines       = pSource->stippledSmoothLines;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceLineRasterizationFeaturesEXT              * pDestination,
            Type ( PhysicalDeviceLineRasterizationFeatures )    const * pSource
    ) noexcept -> VkPhysicalDeviceLineRasterizationFeaturesEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_LINE_RASTERIZATION_FEATURES_EXT;
        pDestination->pNext = nullptr;

        pDestination->rectangularLines          = pSource->rectangularLines;
        pDestination->bresenhamLines            = pSource->bresenhamLines;
        pDestination->smoothLines               = pSource->smoothLines;
        pDestination->stippledRectangularLines  = pSource->stippledRectangularLines;
        pDestination->stippledBresenhamLines    = pSource->stippledBresenhamLines;
        pDestination->stippledSmoothLines       = pSource->stippledSmoothLines;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PAGEABLE_DEVICE_LOCAL_MEMORY_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDevicePageableDeviceLocalMemoryFeatures )             * pDestination,
            VkPhysicalDevicePageableDeviceLocalMemoryFeaturesEXT           const * pSource
    ) noexcept -> Type ( PhysicalDevicePageableDeviceLocalMemoryFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDevicePageableDeviceLocalMemoryFeatures;
        pDestination->pNext = nullptr;

        pDestination->pageableDeviceLocalMemory          = pSource->pageableDeviceLocalMemory;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PAGEABLE_DEVICE_LOCAL_MEMORY_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDevicePageableDeviceLocalMemoryFeaturesEXT              * pDestination,
            Type ( PhysicalDevicePageableDeviceLocalMemoryFeatures )    const * pSource
    ) noexcept -> VkPhysicalDevicePageableDeviceLocalMemoryFeaturesEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PAGEABLE_DEVICE_LOCAL_MEMORY_FEATURES_EXT;
        pDestination->pNext = nullptr;

        pDestination->pageableDeviceLocalMemory          = pSource->pageableDeviceLocalMemory;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_PRIORITY_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceMemoryPriorityFeatures )             * pDestination,
            VkPhysicalDeviceMemoryPriorityFeaturesEXT           const * pSource
    ) noexcept -> Type ( PhysicalDeviceMemoryPriorityFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceMemoryPriorityFeatures;
        pDestination->pNext = nullptr;

        pDestination->memoryPriority          = pSource->memoryPriority;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_PRIORITY_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceMemoryPriorityFeaturesEXT              * pDestination,
            Type ( PhysicalDeviceMemoryPriorityFeatures )    const * pSource
    ) noexcept -> VkPhysicalDeviceMemoryPriorityFeaturesEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PRIORITY_FEATURES_EXT;
        pDestination->pNext = nullptr;

        pDestination->memoryPriority          = pSource->memoryPriority;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceMultiDrawFeatures )             * pDestination,
            VkPhysicalDeviceMultiDrawFeaturesEXT           const * pSource
    ) noexcept -> Type ( PhysicalDeviceMultiDrawFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceMultiDrawFeatures;
        pDestination->pNext = nullptr;

        pDestination->multiDraw          = pSource->multiDraw;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_PRIORITY_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceMultiDrawFeaturesEXT              * pDestination,
            Type ( PhysicalDeviceMultiDrawFeatures )    const * pSource
    ) noexcept -> VkPhysicalDeviceMultiDrawFeaturesEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTI_DRAW_FEATURES_EXT;
        pDestination->pNext = nullptr;

        pDestination->multiDraw          = pSource->multiDraw;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDevicePipelineCreationCacheControlFeatures )             * pDestination,
            VkPhysicalDevicePipelineCreationCacheControlFeatures_t            const * pSource
    ) noexcept -> Type ( PhysicalDevicePipelineCreationCacheControlFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDevicePipelineCreationCacheControlFeatures;
        pDestination->pNext = nullptr;

        pDestination->pipelineCreationCacheControl          = pSource->pipelineCreationCacheControl;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDevicePipelineCreationCacheControlFeatures_t               * pDestination,
            Type ( PhysicalDevicePipelineCreationCacheControlFeatures )    const * pSource
    ) noexcept -> VkPhysicalDevicePipelineCreationCacheControlFeatures_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_CREATION_CACHE_CONTROL_FEATURES;
#elif __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE
        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_CREATION_CACHE_CONTROL_FEATURES_EXT;
#endif
        pDestination->pNext = nullptr;

        pDestination->pipelineCreationCacheControl          = pSource->pipelineCreationCacheControl;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIMITIVE_TOPOLOGY_LIST_RESTART_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDevicePrimitiveTopologyListRestartFeatures )             * pDestination,
            VkPhysicalDevicePrimitiveTopologyListRestartFeaturesEXT           const * pSource
    ) noexcept -> Type ( PhysicalDevicePrimitiveTopologyListRestartFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDevicePrimitiveTopologyListRestartFeatures;
        pDestination->pNext = nullptr;

        pDestination->primitiveTopologyListRestart          = pSource->primitiveTopologyListRestart;
        pDestination->primitiveTopologyPatchListRestart     = pSource->primitiveTopologyPatchListRestart;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIMITIVE_TOPOLOGY_LIST_RESTART_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDevicePrimitiveTopologyListRestartFeaturesEXT               * pDestination,
            Type ( PhysicalDevicePrimitiveTopologyListRestartFeatures )     const * pSource
    ) noexcept -> VkPhysicalDevicePrimitiveTopologyListRestartFeaturesEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRIMITIVE_TOPOLOGY_LIST_RESTART_FEATURES_EXT;
        pDestination->pNext = nullptr;

        pDestination->primitiveTopologyListRestart          = pSource->primitiveTopologyListRestart;
        pDestination->primitiveTopologyPatchListRestart     = pSource->primitiveTopologyPatchListRestart;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDevicePrivateDataFeatures )             * pDestination,
            VkPhysicalDevicePrivateDataFeatures_t            const * pSource
    ) noexcept -> Type ( PhysicalDevicePrivateDataFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDevicePrivateDataFeatures;
        pDestination->pNext = nullptr;

        pDestination->privateData          = pSource->privateData;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDevicePrivateDataFeatures_t                * pDestination,
            Type ( PhysicalDevicePrivateDataFeatures )     const * pSource
    ) noexcept -> VkPhysicalDevicePrivateDataFeatures_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRIVATE_DATA_FEATURES;
#elif __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE
        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRIVATE_DATA_FEATURES_EXT;
#endif
        pDestination->pNext = nullptr;

        pDestination->privateData          = pSource->privateData;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceProvokingVertexFeatures )              * pDestination,
            VkPhysicalDeviceProvokingVertexFeaturesEXT            const * pSource
    ) noexcept -> Type ( PhysicalDeviceProvokingVertexFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceProvokingVertexFeatures;
        pDestination->pNext = nullptr;

        pDestination->provokingVertexLast                       = pSource->provokingVertexLast;
        pDestination->transformFeedbackPreservesProvokingVertex = pSource->transformFeedbackPreservesProvokingVertex;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceProvokingVertexFeaturesEXT                * pDestination,
            Type ( PhysicalDeviceProvokingVertexFeatures )      const * pSource
    ) noexcept -> VkPhysicalDeviceProvokingVertexFeaturesEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROVOKING_VERTEX_FEATURES_EXT;
        pDestination->pNext = nullptr;

        pDestination->provokingVertexLast                       = pSource->provokingVertexLast;
        pDestination->transformFeedbackPreservesProvokingVertex = pSource->transformFeedbackPreservesProvokingVertex;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_RGBA_10_X_6_FORMATS_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceRGBA10x6FormatsFeatures )              * pDestination,
            VkPhysicalDeviceRGBA10X6FormatsFeaturesEXT            const * pSource
    ) noexcept -> Type ( PhysicalDeviceRGBA10x6FormatsFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceRGBA10x6FormatsFeatures;
        pDestination->pNext = nullptr;

        pDestination->formatRGBA10x6WithoutYCBCRSampler                       = pSource->formatRgba10x6WithoutYCbCrSampler;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_RGBA_10_X_6_FORMATS_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceRGBA10X6FormatsFeaturesEXT                * pDestination,
            Type ( PhysicalDeviceRGBA10x6FormatsFeatures )      const * pSource
    ) noexcept -> VkPhysicalDeviceRGBA10X6FormatsFeaturesEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RGBA10X6_FORMATS_FEATURES_EXT;
        pDestination->pNext = nullptr;

        pDestination->formatRgba10x6WithoutYCbCrSampler                       = pSource->formatRGBA10x6WithoutYCBCRSampler;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceRobustnessFeatures )               * pDestination,
            VkPhysicalDeviceRobustness2FeaturesEXT            const * pSource
    ) noexcept -> Type ( PhysicalDeviceRobustnessFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceRobustnessFeatures;
        pDestination->pNext = nullptr;

        pDestination->robustBufferAccess                        = pSource->robustBufferAccess2;
        pDestination->robustImageAccess                         = pSource->robustImageAccess2;
        pDestination->nullDescriptor                            = pSource->nullDescriptor;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceRobustness2FeaturesEXT                * pDestination,
            Type ( PhysicalDeviceRobustnessFeatures )       const * pSource
    ) noexcept -> VkPhysicalDeviceRobustness2FeaturesEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ROBUSTNESS_2_FEATURES_EXT;
        pDestination->pNext = nullptr;

        pDestination->robustBufferAccess2                       = pSource->robustBufferAccess;
        pDestination->robustImageAccess2                        = pSource->robustImageAccess;
        pDestination->nullDescriptor                            = pSource->nullDescriptor;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceShaderAtomicFloatFeatures )              * pDestination,
            VkPhysicalDeviceShaderAtomicFloatFeaturesEXT            const * pSource
    ) noexcept -> Type ( PhysicalDeviceShaderAtomicFloatFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceShaderAtomicFloatFeatures;
        pDestination->pNext = nullptr;

        pDestination->shaderBufferFloat32Atomics                            = pSource->shaderBufferFloat32Atomics;
        pDestination->shaderBufferFloat32AtomicAdd                          = pSource->shaderBufferFloat32AtomicAdd;
        pDestination->shaderBufferFloat64Atomics                            = pSource->shaderBufferFloat64Atomics;
        pDestination->shaderBufferFloat64AtomicAdd                          = pSource->shaderBufferFloat64AtomicAdd;
        pDestination->shaderSharedFloat32Atomics                            = pSource->shaderSharedFloat32Atomics;
        pDestination->shaderSharedFloat32AtomicAdd                          = pSource->shaderSharedFloat32AtomicAdd;
        pDestination->shaderSharedFloat64Atomics                            = pSource->shaderSharedFloat64Atomics;
        pDestination->shaderSharedFloat64AtomicAdd                          = pSource->shaderSharedFloat64AtomicAdd;
        pDestination->shaderImageFloat32Atomics                             = pSource->shaderImageFloat32Atomics;
        pDestination->shaderImageFloat32AtomicAdd                           = pSource->shaderImageFloat32AtomicAdd;
        pDestination->sparseImageFloat32Atomics                             = pSource->sparseImageFloat32Atomics;
        pDestination->sparseImageFloat32AtomicAdd                           = pSource->sparseImageFloat32AtomicAdd;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceShaderAtomicFloatFeaturesEXT                * pDestination,
            Type ( PhysicalDeviceShaderAtomicFloatFeatures )       const * pSource
    ) noexcept -> VkPhysicalDeviceShaderAtomicFloatFeaturesEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT_FEATURES_EXT;
        pDestination->pNext = nullptr;

        pDestination->shaderBufferFloat32Atomics                            = pSource->shaderBufferFloat32Atomics;
        pDestination->shaderBufferFloat32AtomicAdd                          = pSource->shaderBufferFloat32AtomicAdd;
        pDestination->shaderBufferFloat64Atomics                            = pSource->shaderBufferFloat64Atomics;
        pDestination->shaderBufferFloat64AtomicAdd                          = pSource->shaderBufferFloat64AtomicAdd;
        pDestination->shaderSharedFloat32Atomics                            = pSource->shaderSharedFloat32Atomics;
        pDestination->shaderSharedFloat32AtomicAdd                          = pSource->shaderSharedFloat32AtomicAdd;
        pDestination->shaderSharedFloat64Atomics                            = pSource->shaderSharedFloat64Atomics;
        pDestination->shaderSharedFloat64AtomicAdd                          = pSource->shaderSharedFloat64AtomicAdd;
        pDestination->shaderImageFloat32Atomics                             = pSource->shaderImageFloat32Atomics;
        pDestination->shaderImageFloat32AtomicAdd                           = pSource->shaderImageFloat32AtomicAdd;
        pDestination->sparseImageFloat32Atomics                             = pSource->sparseImageFloat32Atomics;
        pDestination->sparseImageFloat32AtomicAdd                           = pSource->sparseImageFloat32AtomicAdd;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_2_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceShaderAtomicFloat2Features )              * pDestination,
            VkPhysicalDeviceShaderAtomicFloat2FeaturesEXT            const * pSource
    ) noexcept -> Type ( PhysicalDeviceShaderAtomicFloat2Features ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceShaderAtomicFloat2Features;
        pDestination->pNext = nullptr;

        pDestination->shaderBufferFloat16Atomics                                = pSource->shaderBufferFloat16Atomics;
        pDestination->shaderBufferFloat16AtomicAdd                              = pSource->shaderBufferFloat16AtomicAdd;
        pDestination->shaderBufferFloat16AtomicMinMax                           = pSource->shaderBufferFloat16AtomicMinMax;
        pDestination->shaderBufferFloat32AtomicMinMax                           = pSource->shaderBufferFloat32AtomicMinMax;
        pDestination->shaderBufferFloat64AtomicMinMax                           = pSource->shaderBufferFloat64AtomicMinMax;
        pDestination->shaderSharedFloat16Atomics                                = pSource->shaderSharedFloat16Atomics;
        pDestination->shaderSharedFloat16AtomicAdd                              = pSource->shaderSharedFloat16AtomicAdd;
        pDestination->shaderSharedFloat16AtomicMinMax                           = pSource->shaderSharedFloat16AtomicMinMax;
        pDestination->shaderSharedFloat32AtomicMinMax                           = pSource->shaderSharedFloat32AtomicMinMax;
        pDestination->shaderSharedFloat64AtomicMinMax                           = pSource->shaderSharedFloat64AtomicMinMax;
        pDestination->shaderImageFloat32AtomicMinMax                            = pSource->shaderImageFloat32AtomicMinMax;
        pDestination->sparseImageFloat32AtomicMinMax                            = pSource->sparseImageFloat32AtomicMinMax;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_2_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceShaderAtomicFloat2FeaturesEXT                * pDestination,
            Type ( PhysicalDeviceShaderAtomicFloat2Features )       const * pSource
    ) noexcept -> VkPhysicalDeviceShaderAtomicFloat2FeaturesEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT_2_FEATURES_EXT;
        pDestination->pNext = nullptr;

        pDestination->shaderBufferFloat16Atomics                                = pSource->shaderBufferFloat16Atomics;
        pDestination->shaderBufferFloat16AtomicAdd                              = pSource->shaderBufferFloat16AtomicAdd;
        pDestination->shaderBufferFloat16AtomicMinMax                           = pSource->shaderBufferFloat16AtomicMinMax;
        pDestination->shaderBufferFloat32AtomicMinMax                           = pSource->shaderBufferFloat32AtomicMinMax;
        pDestination->shaderBufferFloat64AtomicMinMax                           = pSource->shaderBufferFloat64AtomicMinMax;
        pDestination->shaderSharedFloat16Atomics                                = pSource->shaderSharedFloat16Atomics;
        pDestination->shaderSharedFloat16AtomicAdd                              = pSource->shaderSharedFloat16AtomicAdd;
        pDestination->shaderSharedFloat16AtomicMinMax                           = pSource->shaderSharedFloat16AtomicMinMax;
        pDestination->shaderSharedFloat32AtomicMinMax                           = pSource->shaderSharedFloat32AtomicMinMax;
        pDestination->shaderSharedFloat64AtomicMinMax                           = pSource->shaderSharedFloat64AtomicMinMax;
        pDestination->shaderImageFloat32AtomicMinMax                            = pSource->shaderImageFloat32AtomicMinMax;
        pDestination->sparseImageFloat32AtomicMinMax                            = pSource->sparseImageFloat32AtomicMinMax;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_DEMOTE_TO_HELPER_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceShaderDemoteToHelperInvocationFeatures )              * pDestination,
            VkPhysicalDeviceShaderDemoteToHelperInvocationFeatures_t             const * pSource
    ) noexcept -> Type ( PhysicalDeviceShaderDemoteToHelperInvocationFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceShaderDemoteToHelperInvocationFeatures;
        pDestination->pNext = nullptr;

        pDestination->shaderDemoteToHelperInvocation    = pSource->shaderDemoteToHelperInvocation;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_DEMOTE_TO_HELPER_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceShaderDemoteToHelperInvocationFeatures_t                 * pDestination,
            Type ( PhysicalDeviceShaderDemoteToHelperInvocationFeatures )       const * pSource
    ) noexcept -> VkPhysicalDeviceShaderDemoteToHelperInvocationFeatures_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_DEMOTE_TO_HELPER_INVOCATION_FEATURES;
#elif __C_ENG_VULKAN_API_EXTENSION_SHADER_DEMOTE_TO_HELPER_INVOCATION_AVAILABLE
        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_DEMOTE_TO_HELPER_INVOCATION_FEATURES_EXT;
#endif
        pDestination->pNext = nullptr;

        pDestination->shaderDemoteToHelperInvocation    = pSource->shaderDemoteToHelperInvocation;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_IMAGE_ATOMIC_INT64_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceShaderImageAtomicInt64Features )               * pDestination,
            VkPhysicalDeviceShaderImageAtomicInt64FeaturesEXT             const * pSource
    ) noexcept -> Type ( PhysicalDeviceShaderImageAtomicInt64Features ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceShaderImageAtomicInt64Features;
        pDestination->pNext = nullptr;

        pDestination->shaderImageInt64Atomics    = pSource->shaderImageInt64Atomics;
        pDestination->sparseImageInt64Atomics    = pSource->sparseImageInt64Atomics;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_IMAGE_ATOMIC_INT64_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceShaderImageAtomicInt64FeaturesEXT                 * pDestination,
            Type ( PhysicalDeviceShaderImageAtomicInt64Features )       const * pSource
    ) noexcept -> VkPhysicalDeviceShaderImageAtomicInt64FeaturesEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_IMAGE_ATOMIC_INT64_FEATURES_EXT;
        pDestination->pNext = nullptr;

        pDestination->shaderImageInt64Atomics    = pSource->shaderImageInt64Atomics;
        pDestination->sparseImageInt64Atomics    = pSource->sparseImageInt64Atomics;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceSubgroupSizeControlFeatures )              * pDestination,
            VkPhysicalDeviceSubgroupSizeControlFeatures_t             const * pSource
    ) noexcept -> Type ( PhysicalDeviceSubgroupSizeControlFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceSubgroupSizeControlFeatures;
        pDestination->pNext = nullptr;

        pDestination->subgroupSizeControl       = pSource->subgroupSizeControl;
        pDestination->computeFullSubgroups      = pSource->computeFullSubgroups;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceSubgroupSizeControlFeatures_t                  * pDestination,
            Type ( PhysicalDeviceSubgroupSizeControlFeatures )       const * pSource
    ) noexcept -> VkPhysicalDeviceSubgroupSizeControlFeatures_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_SIZE_CONTROL_FEATURES;
#elif __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE
        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_SIZE_CONTROL_FEATURES_EXT;
#endif
        pDestination->pNext = nullptr;

        pDestination->subgroupSizeControl       = pSource->subgroupSizeControl;
        pDestination->computeFullSubgroups      = pSource->computeFullSubgroups;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceTexelBufferAlignmentFeatures )              * pDestination,
            VkPhysicalDeviceTexelBufferAlignmentFeatures_t             const * pSource
    ) noexcept -> Type ( PhysicalDeviceTexelBufferAlignmentFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceTexelBufferAlignmentFeatures;
        pDestination->pNext = nullptr;

        pDestination->texelBufferAlignment       = pSource->texelBufferAlignment;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceTexelBufferAlignmentFeatures_t                  * pDestination,
            Type ( PhysicalDeviceTexelBufferAlignmentFeatures )       const * pSource
    ) noexcept -> VkPhysicalDeviceTexelBufferAlignmentFeatures_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TEXEL_BUFFER_ALIGNMENT_FEATURES_EXT;
#elif __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE
        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TEXEL_BUFFER_ALIGNMENT_FEATURES_EXT;
#endif
        pDestination->pNext = nullptr;

        pDestination->texelBufferAlignment       = pSource->texelBufferAlignment;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXTURE_COMPRESSION_ASTC_HDR_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceTextureCompressionASTCHDRFeatures )              * pDestination,
            VkPhysicalDeviceTextureCompressionASTCHDRFeatures_t             const * pSource
    ) noexcept -> Type ( PhysicalDeviceTextureCompressionASTCHDRFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceTextureCompressionASTCHDRFeatures;
        pDestination->pNext = nullptr;

        pDestination->textureCompressionASTCHDR       = pSource->textureCompressionASTC_HDR;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXTURE_COMPRESSION_ASTC_HDR_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceTextureCompressionASTCHDRFeatures_t                  * pDestination,
            Type ( PhysicalDeviceTextureCompressionASTCHDRFeatures )       const * pSource
    ) noexcept -> VkPhysicalDeviceTextureCompressionASTCHDRFeatures_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TEXTURE_COMPRESSION_ASTC_HDR_FEATURES;
#elif __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE
        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TEXTURE_COMPRESSION_ASTC_HDR_FEATURES_EXT;
#endif
        pDestination->pNext = nullptr;

        pDestination->textureCompressionASTC_HDR       = pSource->textureCompressionASTCHDR;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceTransformFeedbackFeatures )               * pDestination,
            VkPhysicalDeviceTransformFeedbackFeaturesEXT             const * pSource
    ) noexcept -> Type ( PhysicalDeviceTransformFeedbackFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceTransformFeedbackFeatures;
        pDestination->pNext = nullptr;

        pDestination->transformFeedback         = pSource->transformFeedback;
        pDestination->geometryStreams           = pSource->geometryStreams;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceTransformFeedbackFeaturesEXT                  * pDestination,
            Type ( PhysicalDeviceTransformFeedbackFeatures )        const * pSource
    ) noexcept -> VkPhysicalDeviceTransformFeedbackFeaturesEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TRANSFORM_FEEDBACK_FEATURES_EXT;
        pDestination->pNext = nullptr;

        pDestination->transformFeedback         = pSource->transformFeedback;
        pDestination->geometryStreams           = pSource->geometryStreams;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceVertexAttributeDivisorFeatures )               * pDestination,
            VkPhysicalDeviceVertexAttributeDivisorFeaturesEXT             const * pSource
    ) noexcept -> Type ( PhysicalDeviceVertexAttributeDivisorFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceVertexAttributeDivisorFeatures;
        pDestination->pNext = nullptr;

        pDestination->vertexAttributeInstanceRateDivisor         = pSource->vertexAttributeInstanceRateDivisor;
        pDestination->vertexAttributeInstanceRateZeroDivisor     = pSource->vertexAttributeInstanceRateZeroDivisor;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceVertexAttributeDivisorFeaturesEXT                  * pDestination,
            Type ( PhysicalDeviceVertexAttributeDivisorFeatures )        const * pSource
    ) noexcept -> VkPhysicalDeviceVertexAttributeDivisorFeaturesEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VERTEX_ATTRIBUTE_DIVISOR_FEATURES_EXT;
        pDestination->pNext = nullptr;

        pDestination->vertexAttributeInstanceRateDivisor         = pSource->vertexAttributeInstanceRateDivisor;
        pDestination->vertexAttributeInstanceRateZeroDivisor     = pSource->vertexAttributeInstanceRateZeroDivisor;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_INPUT_DYNAMIC_STATE_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceVertexInputDynamicStateFeatures )               * pDestination,
            VkPhysicalDeviceVertexInputDynamicStateFeaturesEXT             const * pSource
    ) noexcept -> Type ( PhysicalDeviceVertexInputDynamicStateFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceVertexInputDynamicStateFeatures;
        pDestination->pNext = nullptr;

        pDestination->vertexInputDynamicState         = pSource->vertexInputDynamicState;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_INPUT_DYNAMIC_STATE_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceVertexInputDynamicStateFeaturesEXT                  * pDestination,
            Type ( PhysicalDeviceVertexInputDynamicStateFeatures )        const * pSource
    ) noexcept -> VkPhysicalDeviceVertexInputDynamicStateFeaturesEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VERTEX_INPUT_DYNAMIC_STATE_FEATURES_EXT;
        pDestination->pNext = nullptr;

        pDestination->vertexInputDynamicState         = pSource->vertexInputDynamicState;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_2_PLANE_444_FORMATS_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceYCBCR2Plane444FormatsFeatures )               * pDestination,
            VkPhysicalDeviceYcbcr2Plane444FormatsFeaturesEXT             const * pSource
    ) noexcept -> Type ( PhysicalDeviceYCBCR2Plane444FormatsFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceYCBCR2Plane444FormatsFeatures;
        pDestination->pNext = nullptr;

        pDestination->YCBCR2Plane444Formats         = pSource->ycbcr2plane444Formats;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_2_PLANE_444_FORMATS_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceYcbcr2Plane444FormatsFeaturesEXT                  * pDestination,
            Type ( PhysicalDeviceYCBCR2Plane444FormatsFeatures )        const * pSource
    ) noexcept -> VkPhysicalDeviceYcbcr2Plane444FormatsFeaturesEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_YCBCR_2_PLANE_444_FORMATS_FEATURES_EXT;
        pDestination->pNext = nullptr;

        pDestination->ycbcr2plane444Formats         = pSource->YCBCR2Plane444Formats;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_IMAGE_ARRAYS_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceYCBCRImageArraysFeatures )               * pDestination,
            VkPhysicalDeviceYcbcrImageArraysFeaturesEXT             const * pSource
    ) noexcept -> Type ( PhysicalDeviceYCBCRImageArraysFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceYCBCRImageArraysFeatures;
        pDestination->pNext = nullptr;

        pDestination->YCBCRImageArrays         = pSource->ycbcrImageArrays;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_IMAGE_ARRAYS_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceYcbcrImageArraysFeaturesEXT                  * pDestination,
            Type ( PhysicalDeviceYCBCRImageArraysFeatures )        const * pSource
    ) noexcept -> VkPhysicalDeviceYcbcrImageArraysFeaturesEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_YCBCR_IMAGE_ARRAYS_FEATURES_EXT;
        pDestination->pNext = nullptr;

        pDestination->ycbcrImageArrays         = pSource->YCBCRImageArrays;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceAccelerationStructureFeatures )               * pDestination,
            VkPhysicalDeviceAccelerationStructureFeaturesKHR             const * pSource
    ) noexcept -> Type ( PhysicalDeviceAccelerationStructureFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceAccelerationStructureFeatures;
        pDestination->pNext = nullptr;

        pDestination->accelerationStructure                                 = pSource->accelerationStructure;
        pDestination->accelerationStructureCaptureReplay                    = pSource->accelerationStructureCaptureReplay;
        pDestination->accelerationStructureIndirectBuild                    = pSource->accelerationStructureIndirectBuild;
        pDestination->accelerationStructureHostCommands                     = pSource->accelerationStructureHostCommands;
        pDestination->descriptorBindingAccelerationStructureUpdateAfterBind = pSource->descriptorBindingAccelerationStructureUpdateAfterBind;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceAccelerationStructureFeaturesKHR                  * pDestination,
            Type ( PhysicalDeviceAccelerationStructureFeatures )        const * pSource
    ) noexcept -> VkPhysicalDeviceAccelerationStructureFeaturesKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_FEATURES_KHR;
        pDestination->pNext = nullptr;

        pDestination->accelerationStructure                                 = pSource->accelerationStructure;
        pDestination->accelerationStructureCaptureReplay                    = pSource->accelerationStructureCaptureReplay;
        pDestination->accelerationStructureIndirectBuild                    = pSource->accelerationStructureIndirectBuild;
        pDestination->accelerationStructureHostCommands                     = pSource->accelerationStructureHostCommands;
        pDestination->descriptorBindingAccelerationStructureUpdateAfterBind = pSource->descriptorBindingAccelerationStructureUpdateAfterBind;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceDynamicRenderingFeatures )               * pDestination,
            VkPhysicalDeviceDynamicRenderingFeatures_t              const * pSource
    ) noexcept -> Type ( PhysicalDeviceDynamicRenderingFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceDynamicRenderingFeatures;
        pDestination->pNext = nullptr;

        pDestination->dynamicRendering                                 = pSource->dynamicRendering;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceDynamicRenderingFeatures_t                   * pDestination,
            Type ( PhysicalDeviceDynamicRenderingFeatures )        const * pSource
    ) noexcept -> VkPhysicalDeviceDynamicRenderingFeatures_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DYNAMIC_RENDERING_FEATURES;
#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DYNAMIC_RENDERING_FEATURES_KHR;
#endif
        pDestination->pNext = nullptr;

        pDestination->dynamicRendering                                 = pSource->dynamicRendering;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceFragmentShadingRateFeatures )                * pDestination,
            VkPhysicalDeviceFragmentShadingRateFeaturesKHR              const * pSource
    ) noexcept -> Type ( PhysicalDeviceFragmentShadingRateFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceFragmentShadingRateFeatures;
        pDestination->pNext = nullptr;

        pDestination->pipelineFragmentShadingRate   = pSource->pipelineFragmentShadingRate;
        pDestination->primitiveFragmentShadingRate  = pSource->primitiveFragmentShadingRate;
        pDestination->attachmentFragmentShadingRate = pSource->attachmentFragmentShadingRate;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceFragmentShadingRateFeaturesKHR                   * pDestination,
            Type ( PhysicalDeviceFragmentShadingRateFeatures )         const * pSource
    ) noexcept -> VkPhysicalDeviceFragmentShadingRateFeaturesKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_FEATURES_KHR;
        pDestination->pNext = nullptr;

        pDestination->pipelineFragmentShadingRate   = pSource->pipelineFragmentShadingRate;
        pDestination->primitiveFragmentShadingRate  = pSource->primitiveFragmentShadingRate;
        pDestination->attachmentFragmentShadingRate = pSource->attachmentFragmentShadingRate;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceMaintenance4Features )                * pDestination,
            VkPhysicalDeviceMaintenance4Features_t               const * pSource
    ) noexcept -> Type ( PhysicalDeviceMaintenance4Features ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceMaintenance4Features;
        pDestination->pNext = nullptr;

        pDestination->maintenance4   = pSource->maintenance4;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceMaintenance4Features_t                    * pDestination,
            Type ( PhysicalDeviceMaintenance4Features )         const * pSource
    ) noexcept -> VkPhysicalDeviceMaintenance4Features_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_4_FEATURES;
#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE
        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_4_FEATURES_KHR;
#endif
        pDestination->pNext = nullptr;

        pDestination->maintenance4   = pSource->maintenance4;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDevicePerformanceQueryFeatures )                 * pDestination,
            VkPhysicalDevicePerformanceQueryFeaturesKHR               const * pSource
    ) noexcept -> Type ( PhysicalDevicePerformanceQueryFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDevicePerformanceQueryFeatures;
        pDestination->pNext = nullptr;

        pDestination->performanceCounterQueryPools          = pSource->performanceCounterQueryPools;
        pDestination->performanceCounterMultipleQueryPools  = pSource->performanceCounterMultipleQueryPools;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDevicePerformanceQueryFeaturesKHR                    * pDestination,
            Type ( PhysicalDevicePerformanceQueryFeatures )          const * pSource
    ) noexcept -> VkPhysicalDevicePerformanceQueryFeaturesKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PERFORMANCE_QUERY_FEATURES_KHR;
        pDestination->pNext = nullptr;

        pDestination->performanceCounterQueryPools          = pSource->performanceCounterQueryPools;
        pDestination->performanceCounterMultipleQueryPools  = pSource->performanceCounterMultipleQueryPools;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDevicePipelineExecutablePropertiesFeatures )                 * pDestination,
            VkPhysicalDevicePipelineExecutablePropertiesFeaturesKHR               const * pSource
    ) noexcept -> Type ( PhysicalDevicePipelineExecutablePropertiesFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDevicePipelineExecutablePropertiesFeatures;
        pDestination->pNext = nullptr;

        pDestination->pipelineExecutableInfo          = pSource->pipelineExecutableInfo;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDevicePipelineExecutablePropertiesFeaturesKHR                    * pDestination,
            Type ( PhysicalDevicePipelineExecutablePropertiesFeatures )          const * pSource
    ) noexcept -> VkPhysicalDevicePipelineExecutablePropertiesFeaturesKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_EXECUTABLE_PROPERTIES_FEATURES_KHR;
        pDestination->pNext = nullptr;

        pDestination->pipelineExecutableInfo          = pSource->pipelineExecutableInfo;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_ID_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDevicePresentIDFeatures )                 * pDestination,
            VkPhysicalDevicePresentIdFeaturesKHR               const * pSource
    ) noexcept -> Type ( PhysicalDevicePresentIDFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDevicePresentIDFeatures;
        pDestination->pNext = nullptr;

        pDestination->presentID          = pSource->presentId;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_ID_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDevicePresentIdFeaturesKHR                    * pDestination,
            Type ( PhysicalDevicePresentIDFeatures )          const * pSource
    ) noexcept -> VkPhysicalDevicePresentIdFeaturesKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRESENT_ID_FEATURES_KHR;
        pDestination->pNext = nullptr;

        pDestination->presentId          = pSource->presentID;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_WAIT_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDevicePresentWaitFeatures )                 * pDestination,
            VkPhysicalDevicePresentWaitFeaturesKHR               const * pSource
    ) noexcept -> Type ( PhysicalDevicePresentWaitFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDevicePresentWaitFeatures;
        pDestination->pNext = nullptr;

        pDestination->presentWait          = pSource->presentWait;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_WAIT_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDevicePresentWaitFeaturesKHR                    * pDestination,
            Type ( PhysicalDevicePresentWaitFeatures )          const * pSource
    ) noexcept -> VkPhysicalDevicePresentWaitFeaturesKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRESENT_WAIT_FEATURES_KHR;
        pDestination->pNext = nullptr;

        pDestination->presentWait          = pSource->presentWait;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_QUERY_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceRayQueryFeatures )                 * pDestination,
            VkPhysicalDeviceRayQueryFeaturesKHR               const * pSource
    ) noexcept -> Type ( PhysicalDeviceRayQueryFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceRayQueryFeatures;
        pDestination->pNext = nullptr;

        pDestination->rayQuery          = pSource->rayQuery;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_QUERY_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceRayQueryFeaturesKHR                    * pDestination,
            Type ( PhysicalDeviceRayQueryFeatures )          const * pSource
    ) noexcept -> VkPhysicalDeviceRayQueryFeaturesKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_QUERY_FEATURES_KHR;
        pDestination->pNext = nullptr;

        pDestination->rayQuery          = pSource->rayQuery;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_CLOCK_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceShaderClockFeatures )                 * pDestination,
            VkPhysicalDeviceShaderClockFeaturesKHR               const * pSource
    ) noexcept -> Type ( PhysicalDeviceShaderClockFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceShaderClockFeatures;
        pDestination->pNext = nullptr;

        pDestination->shaderSubgroupClock           = pSource->shaderSubgroupClock;
        pDestination->shaderDeviceClock             = pSource->shaderDeviceClock;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_CLOCK_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceShaderClockFeaturesKHR                    * pDestination,
            Type ( PhysicalDeviceShaderClockFeatures )          const * pSource
    ) noexcept -> VkPhysicalDeviceShaderClockFeaturesKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CLOCK_FEATURES_KHR;
        pDestination->pNext = nullptr;

        pDestination->shaderSubgroupClock           = pSource->shaderSubgroupClock;
        pDestination->shaderDeviceClock             = pSource->shaderDeviceClock;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceRayTracingPipelineFeatures )                 * pDestination,
            VkPhysicalDeviceRayTracingPipelineFeaturesKHR               const * pSource
    ) noexcept -> Type ( PhysicalDeviceRayTracingPipelineFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceRayTracingPipelineFeatures;
        pDestination->pNext = nullptr;

        pDestination->rayTracingPipeline                                    = pSource->rayTracingPipeline;
        pDestination->rayTracingPipelineShaderGroupHandleCaptureReplay      = pSource->rayTracingPipelineShaderGroupHandleCaptureReplay;
        pDestination->rayTracingPipelineShaderGroupHandleCaptureReplayMixed = pSource->rayTracingPipelineShaderGroupHandleCaptureReplayMixed;
        pDestination->rayTracingPipelineTraceRaysIndirect                   = pSource->rayTracingPipelineTraceRaysIndirect;
        pDestination->rayTraversalPrimitiveCulling                          = pSource->rayTraversalPrimitiveCulling;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceRayTracingPipelineFeaturesKHR                    * pDestination,
            Type ( PhysicalDeviceRayTracingPipelineFeatures )          const * pSource
    ) noexcept -> VkPhysicalDeviceRayTracingPipelineFeaturesKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_FEATURES_KHR;
        pDestination->pNext = nullptr;

        pDestination->rayTracingPipeline                                    = pSource->rayTracingPipeline;
        pDestination->rayTracingPipelineShaderGroupHandleCaptureReplay      = pSource->rayTracingPipelineShaderGroupHandleCaptureReplay;
        pDestination->rayTracingPipelineShaderGroupHandleCaptureReplayMixed = pSource->rayTracingPipelineShaderGroupHandleCaptureReplayMixed;
        pDestination->rayTracingPipelineTraceRaysIndirect                   = pSource->rayTracingPipelineTraceRaysIndirect;
        pDestination->rayTraversalPrimitiveCulling                          = pSource->rayTraversalPrimitiveCulling;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_SUBGROUP_UNIFORM_CONTROL_FLOW_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceShaderSubgroupUniformControlFlowFeatures )                 * pDestination,
            VkPhysicalDeviceShaderSubgroupUniformControlFlowFeaturesKHR               const * pSource
    ) noexcept -> Type ( PhysicalDeviceShaderSubgroupUniformControlFlowFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceShaderSubgroupUniformControlFlowFeatures;
        pDestination->pNext = nullptr;

        pDestination->shaderSubgroupUniformControlFlow  = pSource->shaderSubgroupUniformControlFlow;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_SUBGROUP_UNIFORM_CONTROL_FLOW_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceShaderSubgroupUniformControlFlowFeaturesKHR                    * pDestination,
            Type ( PhysicalDeviceShaderSubgroupUniformControlFlowFeatures )          const * pSource
    ) noexcept -> VkPhysicalDeviceShaderSubgroupUniformControlFlowFeaturesKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SUBGROUP_UNIFORM_CONTROL_FLOW_FEATURES_KHR;
        pDestination->pNext = nullptr;

        pDestination->shaderSubgroupUniformControlFlow  = pSource->shaderSubgroupUniformControlFlow;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_TERMINATE_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceShaderTerminateInvocationFeatures )                 * pDestination,
            VkPhysicalDeviceShaderTerminateInvocationFeatures_t                const * pSource
    ) noexcept -> Type ( PhysicalDeviceShaderTerminateInvocationFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceShaderTerminateInvocationFeatures;
        pDestination->pNext = nullptr;

        pDestination->shaderTerminateInvocation  = pSource->shaderTerminateInvocation;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_TERMINATE_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceShaderTerminateInvocationFeatures_t                     * pDestination,
            Type ( PhysicalDeviceShaderTerminateInvocationFeatures )          const * pSource
    ) noexcept -> VkPhysicalDeviceShaderTerminateInvocationFeatures_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_TERMINATE_INVOCATION_FEATURES;
#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_TERMINATE_INVOCATION_AVAILABLE
        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_TERMINATE_INVOCATION_FEATURES_KHR;
#endif
        pDestination->pNext = nullptr;

        pDestination->shaderTerminateInvocation  = pSource->shaderTerminateInvocation;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceSynchronizationFeatures )                  * pDestination,
            VkPhysicalDeviceSynchronization2Features_t                const * pSource
    ) noexcept -> Type ( PhysicalDeviceSynchronizationFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceSynchronizationFeatures;
        pDestination->pNext = nullptr;

        pDestination->synchronization  = pSource->synchronization2;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceSynchronization2Features_t                     * pDestination,
            Type ( PhysicalDeviceSynchronizationFeatures )           const * pSource
    ) noexcept -> VkPhysicalDeviceSynchronization2Features_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SYNCHRONIZATION_2_FEATURES;
#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_TERMINATE_INVOCATION_AVAILABLE
        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SYNCHRONIZATION_2_FEATURES_KHR;
#endif
        pDestination->pNext = nullptr;

        pDestination->synchronization2  = pSource->synchronization;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceShaderIntegerDotProductFeatures )                  * pDestination,
            VkPhysicalDeviceShaderIntegerDotProductFeatures_t                 const * pSource
    ) noexcept -> Type ( PhysicalDeviceShaderIntegerDotProductFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceShaderIntegerDotProductFeatures;
        pDestination->pNext = nullptr;

        pDestination->shaderIntegerDotProduct  = pSource->shaderIntegerDotProduct;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceShaderIntegerDotProductFeatures_t                      * pDestination,
            Type ( PhysicalDeviceShaderIntegerDotProductFeatures )           const * pSource
    ) noexcept -> VkPhysicalDeviceShaderIntegerDotProductFeatures_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_INTEGER_DOT_PRODUCT_FEATURES;
#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_TERMINATE_INVOCATION_AVAILABLE
        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_INTEGER_DOT_PRODUCT_FEATURES_KHR;
#endif
        pDestination->pNext = nullptr;

        pDestination->shaderIntegerDotProduct  = pSource->shaderIntegerDotProduct;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceWorkgroupMemoryExplicitLayoutFeatures )                   * pDestination,
            VkPhysicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR                 const * pSource
    ) noexcept -> Type ( PhysicalDeviceWorkgroupMemoryExplicitLayoutFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceWorkgroupMemoryExplicitLayoutFeatures;
        pDestination->pNext = nullptr;

        pDestination->workgroupMemoryExplicitLayout                     = pSource->workgroupMemoryExplicitLayout;
        pDestination->workgroupMemoryExplicitLayoutScalarBlockLayout    = pSource->workgroupMemoryExplicitLayoutScalarBlockLayout;
        pDestination->workgroupMemoryExplicitLayout8BitAccess           = pSource->workgroupMemoryExplicitLayout8BitAccess;
        pDestination->workgroupMemoryExplicitLayout16BitAccess          = pSource->workgroupMemoryExplicitLayout16BitAccess;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR                      * pDestination,
            Type ( PhysicalDeviceWorkgroupMemoryExplicitLayoutFeatures )            const * pSource
    ) noexcept -> VkPhysicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_FEATURES_KHR;
        pDestination->pNext = nullptr;

        pDestination->workgroupMemoryExplicitLayout                     = pSource->workgroupMemoryExplicitLayout;
        pDestination->workgroupMemoryExplicitLayoutScalarBlockLayout    = pSource->workgroupMemoryExplicitLayoutScalarBlockLayout;
        pDestination->workgroupMemoryExplicitLayout8BitAccess           = pSource->workgroupMemoryExplicitLayout8BitAccess;
        pDestination->workgroupMemoryExplicitLayout16BitAccess          = pSource->workgroupMemoryExplicitLayout16BitAccess;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ZERO_INITIALIZE_WORKGROUP_MEMORY_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceZeroInitializeWorkgroupMemoryFeatures )                   * pDestination,
            VkPhysicalDeviceZeroInitializeWorkgroupMemoryFeatures_t                  const * pSource
    ) noexcept -> Type ( PhysicalDeviceZeroInitializeWorkgroupMemoryFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceZeroInitializeWorkgroupMemoryFeatures;
        pDestination->pNext = nullptr;

        pDestination->shaderZeroInitializeWorkgroupMemory   = pSource->shaderZeroInitializeWorkgroupMemory;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ZERO_INITIALIZE_WORKGROUP_MEMORY_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceZeroInitializeWorkgroupMemoryFeatures_t                       * pDestination,
            Type ( PhysicalDeviceZeroInitializeWorkgroupMemoryFeatures )            const * pSource
    ) noexcept -> VkPhysicalDeviceZeroInitializeWorkgroupMemoryFeatures_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ZERO_INITIALIZE_WORKGROUP_MEMORY_FEATURES;
#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ZERO_INITIALIZE_WORKGROUP_MEMORY_AVAILABLE
        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ZERO_INITIALIZE_WORKGROUP_MEMORY_FEATURES_KHR;
#endif
        pDestination->pNext = nullptr;

        pDestination->shaderZeroInitializeWorkgroupMemory   = pSource->shaderZeroInitializeWorkgroupMemory;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COMPUTE_SHADER_DERIVATIVES_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceComputeShaderDerivativesFeaturesNVidia )             * pDestination,
            VkPhysicalDeviceComputeShaderDerivativesFeaturesNV                  const * pSource
    ) noexcept -> Type ( PhysicalDeviceComputeShaderDerivativesFeaturesNVidia ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceComputeShaderDerivativesFeaturesNVidia;
        pDestination->pNext = nullptr;

        pDestination->computeDerivativeGroupQuads       = pSource->computeDerivativeGroupQuads;
        pDestination->computeDerivativeGroupLinear      = pSource->computeDerivativeGroupLinear;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COMPUTE_SHADER_DERIVATIVES_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceComputeShaderDerivativesFeaturesNV                       * pDestination,
            Type ( PhysicalDeviceComputeShaderDerivativesFeaturesNVidia )      const * pSource
    ) noexcept -> VkPhysicalDeviceComputeShaderDerivativesFeaturesNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COMPUTE_SHADER_DERIVATIVES_FEATURES_NV;
        pDestination->pNext = nullptr;

        pDestination->computeDerivativeGroupQuads       = pSource->computeDerivativeGroupQuads;
        pDestination->computeDerivativeGroupLinear      = pSource->computeDerivativeGroupLinear;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceCooperativeMatrixFeaturesNVidia )             * pDestination,
            VkPhysicalDeviceCooperativeMatrixFeaturesNV                  const * pSource
    ) noexcept -> Type ( PhysicalDeviceCooperativeMatrixFeaturesNVidia ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceCooperativeMatrixFeaturesNVidia;
        pDestination->pNext = nullptr;

        pDestination->cooperativeMatrix                     = pSource->cooperativeMatrix;
        pDestination->cooperativeMatrixRobustBufferAccess   = pSource->cooperativeMatrixRobustBufferAccess;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceCooperativeMatrixFeaturesNV                       * pDestination,
            Type ( PhysicalDeviceCooperativeMatrixFeaturesNVidia )      const * pSource
    ) noexcept -> VkPhysicalDeviceCooperativeMatrixFeaturesNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_FEATURES_NV;
        pDestination->pNext = nullptr;

        pDestination->cooperativeMatrix                     = pSource->cooperativeMatrix;
        pDestination->cooperativeMatrixRobustBufferAccess   = pSource->cooperativeMatrixRobustBufferAccess;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CORNER_SAMPLED_IMAGE_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceCornerSampledImageFeaturesNVidia )             * pDestination,
            VkPhysicalDeviceCornerSampledImageFeaturesNV                  const * pSource
    ) noexcept -> Type ( PhysicalDeviceCornerSampledImageFeaturesNVidia ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceCornerSampledImageFeaturesNVidia;
        pDestination->pNext = nullptr;

        pDestination->cornerSampledImage                     = pSource->cornerSampledImage;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CORNER_SAMPLED_IMAGE_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceCornerSampledImageFeaturesNV                       * pDestination,
            Type ( PhysicalDeviceCornerSampledImageFeaturesNVidia )      const * pSource
    ) noexcept -> VkPhysicalDeviceCornerSampledImageFeaturesNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CORNER_SAMPLED_IMAGE_FEATURES_NV;
        pDestination->pNext = nullptr;

        pDestination->cornerSampledImage                     = pSource->cornerSampledImage;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COVERAGE_REDUCTION_MODE_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceCoverageReductionModeFeaturesNVidia )             * pDestination,
            VkPhysicalDeviceCoverageReductionModeFeaturesNV                  const * pSource
    ) noexcept -> Type ( PhysicalDeviceCoverageReductionModeFeaturesNVidia ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceCoverageReductionModeFeaturesNVidia;
        pDestination->pNext = nullptr;

        pDestination->coverageReductionMode = pSource->coverageReductionMode;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COVERAGE_REDUCTION_MODE_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceCoverageReductionModeFeaturesNV                       * pDestination,
            Type ( PhysicalDeviceCoverageReductionModeFeaturesNVidia )      const * pSource
    ) noexcept -> VkPhysicalDeviceCoverageReductionModeFeaturesNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COVERAGE_REDUCTION_MODE_FEATURES_NV;
        pDestination->pNext = nullptr;

        pDestination->coverageReductionMode = pSource->coverageReductionMode;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceDeviceGeneratedCommandsFeaturesNVidia )             * pDestination,
            VkPhysicalDeviceDeviceGeneratedCommandsFeaturesNV                  const * pSource
    ) noexcept -> Type ( PhysicalDeviceDeviceGeneratedCommandsFeaturesNVidia ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceDeviceGeneratedCommandsFeaturesNVidia;
        pDestination->pNext = nullptr;

        pDestination->deviceGeneratedCommands = pSource->deviceGeneratedCommands;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceDeviceGeneratedCommandsFeaturesNV                       * pDestination,
            Type ( PhysicalDeviceDeviceGeneratedCommandsFeaturesNVidia )      const * pSource
    ) noexcept -> VkPhysicalDeviceDeviceGeneratedCommandsFeaturesNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEVICE_GENERATED_COMMANDS_FEATURES_NV;
        pDestination->pNext = nullptr;

        pDestination->deviceGeneratedCommands = pSource->deviceGeneratedCommands;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_IMAGE_ALIASING_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNVidia )             * pDestination,
            VkPhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV                  const * pSource
    ) noexcept -> Type ( PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNVidia ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceDedicatedAllocationImageAliasingFeaturesNVidia;
        pDestination->pNext = nullptr;

        pDestination->dedicatedAllocationImageAliasing = pSource->dedicatedAllocationImageAliasing;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_IMAGE_ALIASING_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV                       * pDestination,
            Type ( PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNVidia )      const * pSource
    ) noexcept -> VkPhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEDICATED_ALLOCATION_IMAGE_ALIASING_FEATURES_NV;
        pDestination->pNext = nullptr;

        pDestination->dedicatedAllocationImageAliasing = pSource->dedicatedAllocationImageAliasing;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTICS_CONFIG_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceDiagnosticsConfigFeaturesNVidia )             * pDestination,
            VkPhysicalDeviceDiagnosticsConfigFeaturesNV                  const * pSource
    ) noexcept -> Type ( PhysicalDeviceDiagnosticsConfigFeaturesNVidia ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceDiagnosticsConfigFeaturesNVidia;
        pDestination->pNext = nullptr;

        pDestination->diagnosticsConfig = pSource->diagnosticsConfig;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTICS_CONFIG_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceDiagnosticsConfigFeaturesNV                       * pDestination,
            Type ( PhysicalDeviceDiagnosticsConfigFeaturesNVidia )      const * pSource
    ) noexcept -> VkPhysicalDeviceDiagnosticsConfigFeaturesNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DIAGNOSTICS_CONFIG_FEATURES_NV;
        pDestination->pNext = nullptr;

        pDestination->diagnosticsConfig = pSource->diagnosticsConfig;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SCISSOR_EXCLUSIVE_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceExclusiveScissorFeaturesNVidia )             * pDestination,
            VkPhysicalDeviceExclusiveScissorFeaturesNV                  const * pSource
    ) noexcept -> Type ( PhysicalDeviceExclusiveScissorFeaturesNVidia ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceExclusiveScissorFeaturesNVidia;
        pDestination->pNext = nullptr;

        pDestination->exclusiveScissor = pSource->exclusiveScissor;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SCISSOR_EXCLUSIVE_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceExclusiveScissorFeaturesNV                       * pDestination,
            Type ( PhysicalDeviceExclusiveScissorFeaturesNVidia )      const * pSource
    ) noexcept -> VkPhysicalDeviceExclusiveScissorFeaturesNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXCLUSIVE_SCISSOR_FEATURES_NV;
        pDestination->pNext = nullptr;

        pDestination->exclusiveScissor = pSource->exclusiveScissor;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_RDMA_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceExternalMemoryRDMAFeaturesNVidia )             * pDestination,
            VkPhysicalDeviceExternalMemoryRDMAFeaturesNV                  const * pSource
    ) noexcept -> Type ( PhysicalDeviceExternalMemoryRDMAFeaturesNVidia ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceExternalMemoryRDMAFeaturesNVidia;
        pDestination->pNext = nullptr;

        pDestination->externalMemoryRDMA = pSource->externalMemoryRDMA;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_RDMA_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceExternalMemoryRDMAFeaturesNV                       * pDestination,
            Type ( PhysicalDeviceExternalMemoryRDMAFeaturesNVidia )      const * pSource
    ) noexcept -> VkPhysicalDeviceExternalMemoryRDMAFeaturesNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_MEMORY_RDMA_FEATURES_NV;
        pDestination->pNext = nullptr;

        pDestination->externalMemoryRDMA = pSource->externalMemoryRDMA;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADER_BARYCENTRIC_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceFragmentShaderBarycentricFeaturesNVidia )             * pDestination,
            VkPhysicalDeviceFragmentShaderBarycentricFeaturesNV                  const * pSource
    ) noexcept -> Type ( PhysicalDeviceFragmentShaderBarycentricFeaturesNVidia ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceFragmentShaderBarycentricFeaturesNVidia;
        pDestination->pNext = nullptr;

        pDestination->fragmentShaderBarycentric = pSource->fragmentShaderBarycentric;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADER_BARYCENTRIC_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceFragmentShaderBarycentricFeaturesNV                       * pDestination,
            Type ( PhysicalDeviceFragmentShaderBarycentricFeaturesNVidia )      const * pSource
    ) noexcept -> VkPhysicalDeviceFragmentShaderBarycentricFeaturesNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADER_BARYCENTRIC_FEATURES_NV;
        pDestination->pNext = nullptr;

        pDestination->fragmentShaderBarycentric = pSource->fragmentShaderBarycentric;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceFragmentShadingRateEnumsFeaturesNVidia )             * pDestination,
            VkPhysicalDeviceFragmentShadingRateEnumsFeaturesNV                  const * pSource
    ) noexcept -> Type ( PhysicalDeviceFragmentShadingRateEnumsFeaturesNVidia ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceFragmentShadingRateEnumsFeaturesNVidia;
        pDestination->pNext = nullptr;

        pDestination->fragmentShadingRateEnums          = pSource->fragmentShadingRateEnums;
        pDestination->supersampleFragmentShadingRates   = pSource->supersampleFragmentShadingRates;
        pDestination->noInvocationFragmentShadingRates  = pSource->noInvocationFragmentShadingRates;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceFragmentShadingRateEnumsFeaturesNV                       * pDestination,
            Type ( PhysicalDeviceFragmentShadingRateEnumsFeaturesNVidia )      const * pSource
    ) noexcept -> VkPhysicalDeviceFragmentShadingRateEnumsFeaturesNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_ENUMS_FEATURES_NV;
        pDestination->pNext = nullptr;

        pDestination->fragmentShadingRateEnums          = pSource->fragmentShadingRateEnums;
        pDestination->supersampleFragmentShadingRates   = pSource->supersampleFragmentShadingRates;
        pDestination->noInvocationFragmentShadingRates  = pSource->noInvocationFragmentShadingRates;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_INHERITED_VIEWPORT_SCISSOR_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceInheritedViewportScissorFeaturesNVidia )             * pDestination,
            VkPhysicalDeviceInheritedViewportScissorFeaturesNV                  const * pSource
    ) noexcept -> Type ( PhysicalDeviceInheritedViewportScissorFeaturesNVidia ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceInheritedViewportScissorFeaturesNVidia;
        pDestination->pNext = nullptr;

        pDestination->inheritedViewportScissor2D          = pSource->inheritedViewportScissor2D;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_INHERITED_VIEWPORT_SCISSOR_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceInheritedViewportScissorFeaturesNV                       * pDestination,
            Type ( PhysicalDeviceInheritedViewportScissorFeaturesNVidia )      const * pSource
    ) noexcept -> VkPhysicalDeviceInheritedViewportScissorFeaturesNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INHERITED_VIEWPORT_SCISSOR_FEATURES_NV;
        pDestination->pNext = nullptr;

        pDestination->inheritedViewportScissor2D          = pSource->inheritedViewportScissor2D;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_LINEAR_COLOR_ATTACHMENT_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceLinearColorAttachmentFeaturesNVidia )             * pDestination,
            VkPhysicalDeviceLinearColorAttachmentFeaturesNV                  const * pSource
    ) noexcept -> Type ( PhysicalDeviceLinearColorAttachmentFeaturesNVidia ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceLinearColorAttachmentFeaturesNVidia;
        pDestination->pNext = nullptr;

        pDestination->linearColorAttachment          = pSource->linearColorAttachment;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_LINEAR_COLOR_ATTACHMENT_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceLinearColorAttachmentFeaturesNV                       * pDestination,
            Type ( PhysicalDeviceLinearColorAttachmentFeaturesNVidia )      const * pSource
    ) noexcept -> VkPhysicalDeviceLinearColorAttachmentFeaturesNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_LINEAR_COLOR_ATTACHMENT_FEATURES_NV;
        pDestination->pNext = nullptr;

        pDestination->linearColorAttachment          = pSource->linearColorAttachment;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceMeshShaderFeaturesNVidia )             * pDestination,
            VkPhysicalDeviceMeshShaderFeaturesNV                  const * pSource
    ) noexcept -> Type ( PhysicalDeviceMeshShaderFeaturesNVidia ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceMeshShaderFeaturesNVidia;
        pDestination->pNext = nullptr;

        pDestination->taskShader          = pSource->taskShader;
        pDestination->meshShader          = pSource->meshShader;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceMeshShaderFeaturesNV                       * pDestination,
            Type ( PhysicalDeviceMeshShaderFeaturesNVidia )      const * pSource
    ) noexcept -> VkPhysicalDeviceMeshShaderFeaturesNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_FEATURES_NV;
        pDestination->pNext = nullptr;

        pDestination->taskShader          = pSource->taskShader;
        pDestination->meshShader          = pSource->meshShader;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceRayTracingMotionBlurFeaturesNVidia )             * pDestination,
            VkPhysicalDeviceRayTracingMotionBlurFeaturesNV                  const * pSource
    ) noexcept -> Type ( PhysicalDeviceRayTracingMotionBlurFeaturesNVidia ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceRayTracingMotionBlurFeaturesNVidia;
        pDestination->pNext = nullptr;

        pDestination->rayTracingMotionBlur                          = pSource->rayTracingMotionBlur;
        pDestination->rayTracingMotionBlurPipelineTraceRaysIndirect = pSource->rayTracingMotionBlurPipelineTraceRaysIndirect;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceRayTracingMotionBlurFeaturesNV                       * pDestination,
            Type ( PhysicalDeviceRayTracingMotionBlurFeaturesNVidia )      const * pSource
    ) noexcept -> VkPhysicalDeviceRayTracingMotionBlurFeaturesNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_MOTION_BLUR_FEATURES_NV;
        pDestination->pNext = nullptr;

        pDestination->rayTracingMotionBlur                          = pSource->rayTracingMotionBlur;
        pDestination->rayTracingMotionBlurPipelineTraceRaysIndirect = pSource->rayTracingMotionBlurPipelineTraceRaysIndirect;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_REPRESENTATIVE_FRAGMENT_TEST_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceRepresentativeFragmentTestFeaturesNVidia )             * pDestination,
            VkPhysicalDeviceRepresentativeFragmentTestFeaturesNV                  const * pSource
    ) noexcept -> Type ( PhysicalDeviceRepresentativeFragmentTestFeaturesNVidia ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceRepresentativeFragmentTestFeaturesNVidia;
        pDestination->pNext = nullptr;

        pDestination->representativeFragmentTest  = pSource->representativeFragmentTest;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_REPRESENTATIVE_FRAGMENT_TEST_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceRepresentativeFragmentTestFeaturesNV                       * pDestination,
            Type ( PhysicalDeviceRepresentativeFragmentTestFeaturesNVidia )      const * pSource
    ) noexcept -> VkPhysicalDeviceRepresentativeFragmentTestFeaturesNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_REPRESENTATIVE_FRAGMENT_TEST_FEATURES_NV;
        pDestination->pNext = nullptr;

        pDestination->representativeFragmentTest  = pSource->representativeFragmentTest;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_IMAGE_FOOTPRINT_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceShaderImageFootprintFeaturesNVidia )             * pDestination,
            VkPhysicalDeviceShaderImageFootprintFeaturesNV                  const * pSource
    ) noexcept -> Type ( PhysicalDeviceShaderImageFootprintFeaturesNVidia ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceShaderImageFootprintFeaturesNVidia;
        pDestination->pNext = nullptr;

        pDestination->imageFootprint  = pSource->imageFootprint;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_IMAGE_FOOTPRINT_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceShaderImageFootprintFeaturesNV                       * pDestination,
            Type ( PhysicalDeviceShaderImageFootprintFeaturesNVidia )      const * pSource
    ) noexcept -> VkPhysicalDeviceShaderImageFootprintFeaturesNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_IMAGE_FOOTPRINT_FEATURES_NV;
        pDestination->pNext = nullptr;

        pDestination->imageFootprint  = pSource->imageFootprint;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceShaderSMBuiltinsFeaturesNVidia )             * pDestination,
            VkPhysicalDeviceShaderSMBuiltinsFeaturesNV                  const * pSource
    ) noexcept -> Type ( PhysicalDeviceShaderSMBuiltinsFeaturesNVidia ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceShaderSmBuiltinsFeaturesNVidia;
        pDestination->pNext = nullptr;

        pDestination->shaderSMBuiltins  = pSource->shaderSMBuiltins;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceShaderSMBuiltinsFeaturesNV                       * pDestination,
            Type ( PhysicalDeviceShaderSMBuiltinsFeaturesNVidia )      const * pSource
    ) noexcept -> VkPhysicalDeviceShaderSMBuiltinsFeaturesNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SM_BUILTINS_FEATURES_NV;
        pDestination->pNext = nullptr;

        pDestination->shaderSMBuiltins  = pSource->shaderSMBuiltins;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceShadingRateImageFeaturesNVidia )             * pDestination,
            VkPhysicalDeviceShadingRateImageFeaturesNV                  const * pSource
    ) noexcept -> Type ( PhysicalDeviceShadingRateImageFeaturesNVidia ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceShadingRateImageFeaturesNVidia;
        pDestination->pNext = nullptr;

        pDestination->shadingRateImage              = pSource->shadingRateImage;
        pDestination->shadingRateCoarseSampleOrder  = pSource->shadingRateCoarseSampleOrder;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceShadingRateImageFeaturesNV                       * pDestination,
            Type ( PhysicalDeviceShadingRateImageFeaturesNVidia )      const * pSource
    ) noexcept -> VkPhysicalDeviceShadingRateImageFeaturesNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADING_RATE_IMAGE_FEATURES_NV;
        pDestination->pNext = nullptr;

        pDestination->shadingRateImage              = pSource->shadingRateImage;
        pDestination->shadingRateCoarseSampleOrder  = pSource->shadingRateCoarseSampleOrder;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_DEVICE_COHERENT_MEMORY_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceCoherentMemoryFeaturesAMD )             * pDestination,
            VkPhysicalDeviceCoherentMemoryFeaturesAMD                  const * pSource
    ) noexcept -> Type ( PhysicalDeviceCoherentMemoryFeaturesAMD ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceCoherentMemoryFeaturesAMD;
        pDestination->pNext = nullptr;

        pDestination->deviceCoherentMemory    = pSource->deviceCoherentMemory;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_DEVICE_COHERENT_MEMORY_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceCoherentMemoryFeaturesAMD                       * pDestination,
            Type ( PhysicalDeviceCoherentMemoryFeaturesAMD )      const * pSource
    ) noexcept -> VkPhysicalDeviceCoherentMemoryFeaturesAMD * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COHERENT_MEMORY_FEATURES_AMD;
        pDestination->pNext = nullptr;

        pDestination->deviceCoherentMemory    = pSource->deviceCoherentMemory;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceFragmentDensityMapOffsetFeaturesQualcomm )             * pDestination,
            VkPhysicalDeviceFragmentDensityMapOffsetFeaturesQCOM                  const * pSource
    ) noexcept -> Type ( PhysicalDeviceFragmentDensityMapOffsetFeaturesQualcomm ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceFragmentDensityMapOffsetFeaturesQualcomm;
        pDestination->pNext = nullptr;

        pDestination->fragmentDensityMapOffset    = pSource->fragmentDensityMapOffset;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceFragmentDensityMapOffsetFeaturesQCOM                       * pDestination,
            Type ( PhysicalDeviceFragmentDensityMapOffsetFeaturesQualcomm )      const * pSource
    ) noexcept -> VkPhysicalDeviceFragmentDensityMapOffsetFeaturesQCOM * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_OFFSET_FEATURES_QCOM;
        pDestination->pNext = nullptr;

        pDestination->fragmentDensityMapOffset    = pSource->fragmentDensityMapOffset;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceSubpassShadingFeaturesHuawei )             * pDestination,
            VkPhysicalDeviceSubpassShadingFeaturesHUAWEI                  const * pSource
    ) noexcept -> Type ( PhysicalDeviceSubpassShadingFeaturesHuawei ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceSubpassShadingFeaturesHuawei;
        pDestination->pNext = nullptr;

        pDestination->subpassShading        = pSource->subpassShading;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceSubpassShadingFeaturesHUAWEI                       * pDestination,
            Type ( PhysicalDeviceSubpassShadingFeaturesHuawei )      const * pSource
    ) noexcept -> VkPhysicalDeviceSubpassShadingFeaturesHUAWEI * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBPASS_SHADING_FEATURES_HUAWEI;
        pDestination->pNext = nullptr;

        pDestination->subpassShading    = pSource->subpassShading;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_INVOCATION_MASK_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceInvocationMaskFeaturesHuawei )             * pDestination,
            VkPhysicalDeviceInvocationMaskFeaturesHUAWEI                  const * pSource
    ) noexcept -> Type ( PhysicalDeviceInvocationMaskFeaturesHuawei ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceInvocationMaskFeaturesHuawei;
        pDestination->pNext = nullptr;

        pDestination->invocationMask    = pSource->invocationMask;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_INVOCATION_MASK_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceInvocationMaskFeaturesHUAWEI                       * pDestination,
            Type ( PhysicalDeviceInvocationMaskFeaturesHuawei )      const * pSource
    ) noexcept -> VkPhysicalDeviceInvocationMaskFeaturesHUAWEI * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INVOCATION_MASK_FEATURES_HUAWEI;
        pDestination->pNext = nullptr;

        pDestination->invocationMask    = pSource->invocationMask;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceMutableDescriptorTypeFeaturesValve )             * pDestination,
            VkPhysicalDeviceMutableDescriptorTypeFeaturesVALVE                  const * pSource
    ) noexcept -> Type ( PhysicalDeviceMutableDescriptorTypeFeaturesValve ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceMutableDescriptorTypeFeaturesValve;
        pDestination->pNext = nullptr;

        pDestination->mutableDescriptorType    = pSource->mutableDescriptorType;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceMutableDescriptorTypeFeaturesVALVE                       * pDestination,
            Type ( PhysicalDeviceMutableDescriptorTypeFeaturesValve )      const * pSource
    ) noexcept -> VkPhysicalDeviceMutableDescriptorTypeFeaturesVALVE * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MUTABLE_DESCRIPTOR_TYPE_FEATURES_VALVE;
        pDestination->pNext = nullptr;

        pDestination->mutableDescriptorType    = pSource->mutableDescriptorType;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_SHADER_INTEGER_FUNCTIONS_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceShaderIntegerFunctionsFeaturesIntel )                  * pDestination,
            VkPhysicalDeviceShaderIntegerFunctions2FeaturesINTEL                  const * pSource
    ) noexcept -> Type ( PhysicalDeviceShaderIntegerFunctionsFeaturesIntel ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceShaderIntegerFunctionsFeaturesIntel;
        pDestination->pNext = nullptr;

        pDestination->shaderIntegerFunctions    = pSource->shaderIntegerFunctions2;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_SHADER_INTEGER_FUNCTIONS_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceShaderIntegerFunctions2FeaturesINTEL                  * pDestination,
            Type ( PhysicalDeviceShaderIntegerFunctionsFeaturesIntel )      const * pSource
    ) noexcept -> VkPhysicalDeviceShaderIntegerFunctions2FeaturesINTEL * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_INTEGER_FUNCTIONS_2_FEATURES_INTEL;
        pDestination->pNext = nullptr;

        pDestination->shaderIntegerFunctions2    = pSource->shaderIntegerFunctions;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_ARM_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_AVAILABLE
    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM )                 * pDestination,
            VkPhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM                  const * pSource
    ) noexcept -> Type ( PhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM;
        pDestination->pNext = nullptr;

        pDestination->rasterizationOrderColorAttachmentAccess       = pSource->rasterizationOrderColorAttachmentAccess;
        pDestination->rasterizationOrderDepthAttachmentAccess       = pSource->rasterizationOrderDepthAttachmentAccess;
        pDestination->rasterizationOrderStencilAttachmentAccess     = pSource->rasterizationOrderStencilAttachmentAccess;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_ARM_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_AVAILABLE
    static inline auto toVulkanFormat (
            VkPhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM                   * pDestination,
            Type ( PhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM )      const * pSource
    ) noexcept -> VkPhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_FEATURES_ARM;
        pDestination->pNext = nullptr;

        pDestination->rasterizationOrderColorAttachmentAccess       = pSource->rasterizationOrderColorAttachmentAccess;
        pDestination->rasterizationOrderDepthAttachmentAccess       = pSource->rasterizationOrderDepthAttachmentAccess;
        pDestination->rasterizationOrderStencilAttachmentAccess     = pSource->rasterizationOrderStencilAttachmentAccess;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    static inline auto toVulkanFormat (
            VkDeviceCreateInfo                * pDestination,
            Type ( DeviceCreateInfo )   const * pSource
    ) noexcept -> VkDeviceCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pSource == nullptr || pDestination == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType                     = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        pDestination->pNext                     = nullptr;
        pDestination->flags                     = pSource->flags;
        pDestination->queueCreateInfoCount      = pSource->queueCreateInfoCount;
        pDestination->pQueueCreateInfos         = pDestination->pQueueCreateInfos;
        pDestination->enabledExtensionCount     = pSource->enabledExtensionCount;
        pDestination->ppEnabledExtensionNames   = pSource->pEnabledExtensionNames;
        pDestination->pEnabledFeatures          = pDestination->pEnabledFeatures;

#if ! __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
        pDestination->enabledLayerCount         = pSource->enabledLayerCount;
        pDestination->ppEnabledLayerNames       = pSource->pEnabledLayerNames;
#endif

        return pDestination;
    }

    static inline auto featureToVulkanFormat (
            VkBaseOutStructure                * pDestination,
            Type ( GenericInStructure ) const * pSource,
            DeviceFeaturesContext             * pContext
    ) noexcept -> void {

        switch ( pSource->structureType ) {

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

            case StructureTypePhysicalDeviceFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->features2,
                                reinterpret_cast < Type ( PhysicalDeviceExtendedFeatures ) const * > ( pSource )
                        )
                );
                break;

            case StructureTypePhysicalDeviceVulkan_1_1_Features:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->vulkan11,
                                reinterpret_cast < Type ( PhysicalDeviceVulkan11Features ) const * > ( pSource )
                        )
                );
                break;

            case StructureTypePhysicalDevice16BitStorageFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->_16BitStorage,
                                reinterpret_cast < Type ( PhysicalDevice16BitStorageFeatures ) const * > ( pSource )
                        )
                );
                break;

            case StructureTypePhysicalDeviceMultiviewFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->multiview,
                                reinterpret_cast < Type ( PhysicalDeviceMultiviewFeatures ) const * > ( pSource )
                        )
                );
                break;

            case StructureTypePhysicalDeviceProtectedMemoryFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->protectedMemory,
                                reinterpret_cast < Type ( PhysicalDeviceProtectedMemoryFeatures ) const * > ( pSource )
                        )
                );
                break;

            case StructureTypePhysicalDeviceSamplerYCBCRConversionFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->samplerYcbcrConversion,
                                reinterpret_cast < Type ( PhysicalDeviceSamplerYCBCRConversionFeatures ) const * > ( pSource )
                        )
                );
                break;

            case StructureTypePhysicalDeviceShaderDrawParametersFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->shaderDrawParameters,
                                reinterpret_cast < Type ( PhysicalDeviceShaderDrawParametersFeatures ) const * > ( pSource )
                        )
                );
                break;

            case StructureTypePhysicalDeviceVariablePointersFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->variablePointers,
                                reinterpret_cast < Type ( PhysicalDeviceVariablePointersFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

            case StructureTypePhysicalDeviceVulkan_1_2_Features:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->vulkan12,
                                reinterpret_cast < Type ( PhysicalDeviceVulkan12Features ) const * > ( pSource )
                        )
                );
                break;

            case StructureTypePhysicalDevice8BitStorageFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->_8BitStorage,
                                reinterpret_cast < Type ( PhysicalDevice8BitStorageFeatures ) const * > ( pSource )
                        )
                );
                break;

            case StructureTypePhysicalDeviceBufferDeviceAddressFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->bufferDeviceAddress,
                                reinterpret_cast < Type ( PhysicalDeviceBufferDeviceAddressFeatures ) const * > ( pSource )
                        )
                );
                break;

            case StructureTypePhysicalDeviceDescriptorIndexingFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->descriptorIndexing,
                                reinterpret_cast < Type ( PhysicalDeviceDescriptorIndexingFeatures ) const * > ( pSource )
                        )
                );
                break;

            case StructureTypePhysicalDeviceHostQueryResetFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->hostQueryReset,
                                reinterpret_cast < Type ( PhysicalDeviceHostQueryResetFeatures ) const * > ( pSource )
                        )
                );
                break;

            case StructureTypePhysicalDeviceImagelessFramebufferFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->imagelessFramebuffer,
                                reinterpret_cast < Type ( PhysicalDeviceImagelessFramebufferFeatures ) const * > ( pSource )
                        )
                );
                break;

            case StructureTypePhysicalDeviceScalarBlockLayoutFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->scalarBlockLayout,
                                reinterpret_cast < Type ( PhysicalDeviceScalarBlockLayoutFeatures ) const * > ( pSource )
                        )
                );
                break;

            case StructureTypePhysicalDeviceSeparateDepthStencilLayoutsFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->separateDepthStencilLayouts,
                                reinterpret_cast < Type ( PhysicalDeviceSeparateDepthStencilLayoutsFeatures ) const * > ( pSource )
                        )
                );
                break;

            case StructureTypePhysicalDeviceShaderAtomicInt64Features:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->shaderAtomicInt64,
                                reinterpret_cast < Type ( PhysicalDeviceShaderAtomicInt64Features ) const * > ( pSource )
                        )
                );
                break;

            case StructureTypePhysicalDeviceShaderFloat16Int8Features:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->shaderFloat16Int8,
                                reinterpret_cast < Type ( PhysicalDeviceShaderFloat16Int8Features ) const * > ( pSource )
                        )
                );
                break;

            case StructureTypePhysicalDeviceShaderSubgroupExtendedTypesFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->shaderSubgroupExtendedTypes,
                                reinterpret_cast < Type ( PhysicalDeviceShaderSubgroupExtendedTypesFeatures ) const * > ( pSource )
                        )
                );
                break;

            case StructureTypePhysicalDeviceTimelineSemaphoreFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->timelineSemaphore,
                                reinterpret_cast < Type ( PhysicalDeviceTimelineSemaphoreFeatures ) const * > ( pSource )
                        )
                );
                break;

            case StructureTypePhysicalDeviceUniformBufferStandardLayoutFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->uniformBufferStandardLayout,
                                reinterpret_cast < Type ( PhysicalDeviceUniformBufferStandardLayoutFeatures ) const * > ( pSource )
                        )
                );
                break;

            case StructureTypePhysicalDeviceVulkanMemoryModelFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->vulkanMemoryModel,
                                reinterpret_cast < Type ( PhysicalDeviceVulkanMemoryModelFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case StructureTypePhysicalDeviceVulkan_1_3_Features:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->vulkan13,
                                reinterpret_cast < Type ( PhysicalDeviceVulkan13Features ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_4444_FORMATS_AVAILABLE

            case StructureTypePhysicalDevice4444FormatsFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->_4444Formats,
                                reinterpret_cast < Type ( PhysicalDevice4444FormatsFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ASTC_DECODE_MODE_AVAILABLE

            case StructureTypePhysicalDeviceASTCDecodeFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->astcDecode,
                                reinterpret_cast < Type ( PhysicalDeviceASTCDecodeFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE

            case StructureTypePhysicalDeviceAccelerationStructureFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->accelerationStructure,
                                reinterpret_cast < Type ( PhysicalDeviceAccelerationStructureFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE

            case StructureTypePhysicalDeviceBlendOperationAdvancedFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->blendOperationAdvanced,
                                reinterpret_cast < Type ( PhysicalDeviceBlendOperationAdvancedFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BORDER_COLOR_SWIZZLE_AVAILABLE

            case StructureTypePhysicalDeviceBorderColorSwizzleFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->borderColorSwizzle,
                                reinterpret_cast < Type ( PhysicalDeviceBorderColorSwizzleFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_DEVICE_COHERENT_MEMORY_AVAILABLE

            case StructureTypePhysicalDeviceCoherentMemoryFeaturesAMD:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->coherentMemory,
                                reinterpret_cast < Type ( PhysicalDeviceCoherentMemoryFeaturesAMD ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_COLOR_WRITE_ENABLE_AVAILABLE

            case StructureTypePhysicalDeviceColorWriteEnableFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->colorWriteEnable,
                                reinterpret_cast < Type ( PhysicalDeviceColorWriteEnableFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COMPUTE_SHADER_DERIVATIVES_AVAILABLE

            case StructureTypePhysicalDeviceComputeShaderDerivativesFeaturesNVidia:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->computerShaderDerivatives,
                                reinterpret_cast < Type ( PhysicalDeviceComputeShaderDerivativesFeaturesNVidia ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE

            case StructureTypePhysicalDeviceConditionalRenderingFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->conditionalRendering,
                                reinterpret_cast < Type ( PhysicalDeviceConditionalRenderingFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE

            case StructureTypePhysicalDeviceCooperativeMatrixFeaturesNVidia:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->cooperativeMatrix,
                                reinterpret_cast < Type ( PhysicalDeviceCooperativeMatrixFeaturesNVidia ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CORNER_SAMPLED_IMAGE_AVAILABLE

            case StructureTypePhysicalDeviceCornerSampledImageFeaturesNVidia:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->cornerSampledImage,
                                reinterpret_cast < Type ( PhysicalDeviceCornerSampledImageFeaturesNVidia ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COVERAGE_REDUCTION_MODE_AVAILABLE

            case StructureTypePhysicalDeviceCoverageReductionModeFeaturesNVidia:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->coverageReduction,
                                reinterpret_cast < Type ( PhysicalDeviceCoverageReductionModeFeaturesNVidia ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE

            case StructureTypePhysicalDeviceCustomBorderColorFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->customBorderColor,
                                reinterpret_cast < Type ( PhysicalDeviceCustomBorderColorFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_IMAGE_ALIASING_AVAILABLE

            case StructureTypePhysicalDeviceDedicatedAllocationImageAliasingFeaturesNVidia:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->dedicatedAllocationImageAliasingFeatures,
                                reinterpret_cast < Type ( PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNVidia ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_CONTROL_AVAILABLE

            case StructureTypePhysicalDeviceDepthClipControlFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->depthClipControl,
                                reinterpret_cast < Type ( PhysicalDeviceDepthClipControlFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_ENABLE_AVAILABLE

            case StructureTypePhysicalDeviceDepthClipEnableFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->depthClipEnable,
                                reinterpret_cast < Type ( PhysicalDeviceDepthClipEnableFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE

            case StructureTypePhysicalDeviceDeviceGeneratedCommandsFeaturesNVidia:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->deviceGeneratedCommands,
                                reinterpret_cast < Type ( PhysicalDeviceDeviceGeneratedCommandsFeaturesNVidia ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEVICE_MEMORY_REPORT_AVAILABLE

            case StructureTypePhysicalDeviceDeviceMemoryReportFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->deviceMemoryReport,
                                reinterpret_cast < Type ( PhysicalDeviceDeviceMemoryReportFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTICS_CONFIG_AVAILABLE

            case StructureTypePhysicalDeviceDiagnosticsConfigFeaturesNVidia:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->diagnosticsConfig,
                                reinterpret_cast < Type ( PhysicalDeviceDiagnosticsConfigFeaturesNVidia ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case StructureTypePhysicalDeviceDynamicRenderingFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->dynamicRendering,
                                reinterpret_cast < Type ( PhysicalDeviceDynamicRenderingFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SCISSOR_EXCLUSIVE_AVAILABLE

            case StructureTypePhysicalDeviceExclusiveScissorFeaturesNVidia:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->exclusiveScissor,
                                reinterpret_cast < Type ( PhysicalDeviceExclusiveScissorFeaturesNVidia ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE

            case StructureTypePhysicalDeviceExtendedDynamicStateFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->extendedDynamicState,
                                reinterpret_cast < Type ( PhysicalDeviceExtendedDynamicStateFeatures ) const * > ( pSource )
                        )
                );
                break;

            case StructureTypePhysicalDeviceExtendedDynamicState2Features:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->extendedDynamicState2,
                                reinterpret_cast < Type ( PhysicalDeviceExtendedDynamicState2Features ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_RDMA_AVAILABLE

            case StructureTypePhysicalDeviceExternalMemoryRDMAFeaturesNVidia:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->externalMemoryRDMA,
                                reinterpret_cast < Type ( PhysicalDeviceExternalMemoryRDMAFeaturesNVidia ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

            case StructureTypePhysicalDeviceFragmentDensityMapFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->fragmentDensityMap,
                                reinterpret_cast < Type ( PhysicalDeviceFragmentDensityMapFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE

            case StructureTypePhysicalDeviceFragmentDensityMap2Features:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->fragmentDensityMap2,
                                reinterpret_cast < Type ( PhysicalDeviceFragmentDensityMap2Features ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE

            case StructureTypePhysicalDeviceFragmentDensityMapOffsetFeaturesQualcomm:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->fragmentDensityMapOffset,
                                reinterpret_cast < Type ( PhysicalDeviceFragmentDensityMapOffsetFeaturesQualcomm ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADER_BARYCENTRIC_AVAILABLE

            case StructureTypePhysicalDeviceFragmentShaderBarycentricFeaturesNVidia:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->fragmentShaderBarycentric,
                                reinterpret_cast < Type ( PhysicalDeviceFragmentShaderBarycentricFeaturesNVidia ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_SHADER_INTERLOCK_AVAILABLE

            case StructureTypePhysicalDeviceFragmentShaderInterlockFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->fragmentShaderInterlock,
                                reinterpret_cast < Type ( PhysicalDeviceFragmentShaderInterlockFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE

            case StructureTypePhysicalDeviceFragmentShadingRateEnumsFeaturesNVidia:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->fragmentShadingRateEnums,
                                reinterpret_cast < Type ( PhysicalDeviceFragmentShadingRateEnumsFeaturesNVidia ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE

            case StructureTypePhysicalDeviceFragmentShadingRateFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->fragmentShadingRate,
                                reinterpret_cast < Type ( PhysicalDeviceFragmentShadingRateFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE

            case StructureTypePhysicalDeviceGlobalPriorityQueryFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->globalPriorityQuery,
                                reinterpret_cast < Type ( PhysicalDeviceGlobalPriorityQueryFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_ROBUSTNESS_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case StructureTypePhysicalDeviceImageRobustnessFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->imageRobustness,
                                reinterpret_cast < Type ( PhysicalDeviceImageRobustnessFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_VIEW_MIN_LOD_AVAILABLE

            case StructureTypePhysicalDeviceImageViewMinLODFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->imageViewMinLOD,
                                reinterpret_cast < Type ( PhysicalDeviceImageViewMinLODFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INDEX_TYPE_UINT8_AVAILABLE

            case StructureTypePhysicalDeviceIndexTypeUInt8Features:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->indexTypeUInt8,
                                reinterpret_cast < Type ( PhysicalDeviceIndexTypeUInt8Features ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_INHERITED_VIEWPORT_SCISSOR_AVAILABLE

            case StructureTypePhysicalDeviceInheritedViewportScissorFeaturesNVidia:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->inheritedViewportScissor,
                                reinterpret_cast < Type ( PhysicalDeviceInheritedViewportScissorFeaturesNVidia ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case StructureTypePhysicalDeviceInlineUniformBlockFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->inlineUniformBlock,
                                reinterpret_cast < Type ( PhysicalDeviceInlineUniformBlockFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_INVOCATION_MASK_AVAILABLE

            case StructureTypePhysicalDeviceInvocationMaskFeaturesHuawei:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->invocationMask,
                                reinterpret_cast < Type ( PhysicalDeviceInvocationMaskFeaturesHuawei ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE

            case StructureTypePhysicalDeviceLineRasterizationFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->lineRasterization,
                                reinterpret_cast < Type ( PhysicalDeviceLineRasterizationFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_LINEAR_COLOR_ATTACHMENT_AVAILABLE

            case StructureTypePhysicalDeviceLinearColorAttachmentFeaturesNVidia:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->linearColorAttachment,
                                reinterpret_cast < Type ( PhysicalDeviceLinearColorAttachmentFeaturesNVidia ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case StructureTypePhysicalDeviceMaintenance4Features:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->maintenance4,
                                reinterpret_cast < Type ( PhysicalDeviceMaintenance4Features ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_PRIORITY_AVAILABLE

            case StructureTypePhysicalDeviceMemoryPriorityFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->memoryPriority,
                                reinterpret_cast < Type ( PhysicalDeviceMemoryPriorityFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE

            case StructureTypePhysicalDeviceMeshShaderFeaturesNVidia:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->meshShader,
                                reinterpret_cast < Type ( PhysicalDeviceMeshShaderFeaturesNVidia ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE

            case StructureTypePhysicalDeviceMultiDrawFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->multiDraw,
                                reinterpret_cast < Type ( PhysicalDeviceMultiDrawFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE

            case StructureTypePhysicalDeviceMutableDescriptorTypeFeaturesValve:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->mutableDescriptorType,
                                reinterpret_cast < Type ( PhysicalDeviceMutableDescriptorTypeFeaturesValve ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PAGEABLE_DEVICE_LOCAL_MEMORY_AVAILABLE

            case StructureTypePhysicalDevicePageableDeviceLocalMemoryFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->pageableDeviceLocalMemory,
                                reinterpret_cast < Type ( PhysicalDevicePageableDeviceLocalMemoryFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

            case StructureTypePhysicalDevicePerformanceQueryFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->performanceQuery,
                                reinterpret_cast < Type ( PhysicalDevicePerformanceQueryFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case StructureTypePhysicalDevicePipelineCreationCacheControlFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->pipelineCreationCacheControl,
                                reinterpret_cast < Type ( PhysicalDevicePipelineCreationCacheControlFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE

            case StructureTypePhysicalDevicePipelineExecutablePropertiesFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->pipelineExecutableProperties,
                                reinterpret_cast < Type ( PhysicalDevicePipelineExecutablePropertiesFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE

            case StructureTypePhysicalDevicePortabilitySubsetFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->portabilitySubset,
                                reinterpret_cast < Type ( PhysicalDevicePortabilitySubsetFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_ID_AVAILABLE

            case StructureTypePhysicalDevicePresentIDFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->presentID,
                                reinterpret_cast < Type ( PhysicalDevicePresentIDFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_WAIT_AVAILABLE

            case StructureTypePhysicalDevicePresentWaitFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->presentWait,
                                reinterpret_cast < Type ( PhysicalDevicePresentWaitFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIMITIVE_TOPOLOGY_LIST_RESTART_AVAILABLE

            case StructureTypePhysicalDevicePrimitiveTopologyListRestartFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->primitiveTopologyListRestart,
                                reinterpret_cast < Type ( PhysicalDevicePrimitiveTopologyListRestartFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case StructureTypePhysicalDevicePrivateDataFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->privateData,
                                reinterpret_cast < Type ( PhysicalDevicePrivateDataFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE

            case StructureTypePhysicalDeviceProvokingVertexFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->provokingVertex,
                                reinterpret_cast < Type ( PhysicalDeviceProvokingVertexFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_RGBA_10_X_6_FORMATS_AVAILABLE

            case StructureTypePhysicalDeviceRGBA10x6FormatsFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->rgba10x6FormatsFeaturesExt,
                                reinterpret_cast < Type ( PhysicalDeviceRGBA10x6FormatsFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ARM_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_AVAILABLE

            case StructureTypePhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->rasterizationOrderAttachmentAccess,
                                reinterpret_cast < Type ( PhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_QUERY_AVAILABLE

            case StructureTypePhysicalDeviceRayQueryFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->rayQuery,
                                reinterpret_cast < Type ( PhysicalDeviceRayQueryFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE

            case StructureTypePhysicalDeviceRayTracingMotionBlurFeaturesNVidia:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->rayTracingMotionBlur,
                                reinterpret_cast < Type ( PhysicalDeviceRayTracingMotionBlurFeaturesNVidia ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE

            case StructureTypePhysicalDeviceRayTracingPipelineFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->rayTracingPipeline,
                                reinterpret_cast < Type ( PhysicalDeviceRayTracingPipelineFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_REPRESENTATIVE_FRAGMENT_TEST_AVAILABLE

            case StructureTypePhysicalDeviceRepresentativeFragmentTestFeaturesNVidia:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->representativeFragmentText,
                                reinterpret_cast < Type ( PhysicalDeviceRepresentativeFragmentTestFeaturesNVidia ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE

            case StructureTypePhysicalDeviceRobustnessFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->robustness2,
                                reinterpret_cast < Type ( PhysicalDeviceRobustnessFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_AVAILABLE

            case StructureTypePhysicalDeviceShaderAtomicFloatFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->shaderAtomicFloat,
                                reinterpret_cast < Type ( PhysicalDeviceShaderAtomicFloatFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_2_AVAILABLE

            case StructureTypePhysicalDeviceShaderAtomicFloat2Features:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->shaderAtomicFloat2,
                                reinterpret_cast < Type ( PhysicalDeviceShaderAtomicFloat2Features ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_CLOCK_AVAILABLE

            case StructureTypePhysicalDeviceShaderClockFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->shaderDeviceShaderClock,
                                reinterpret_cast < Type ( PhysicalDeviceShaderClockFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_DEMOTE_TO_HELPER_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case StructureTypePhysicalDeviceShaderDemoteToHelperInvocationFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->shaderDemoteToHelperInvocation,
                                reinterpret_cast < Type ( PhysicalDeviceShaderDemoteToHelperInvocationFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_IMAGE_ATOMIC_INT64_AVAILABLE

            case StructureTypePhysicalDeviceShaderImageAtomicInt64Features:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->shaderImageAtomicInt64,
                                reinterpret_cast < Type ( PhysicalDeviceShaderImageAtomicInt64Features ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_IMAGE_FOOTPRINT_AVAILABLE

            case StructureTypePhysicalDeviceShaderImageFootprintFeaturesNVidia:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->shaderImageFootprint,
                                reinterpret_cast < Type ( PhysicalDeviceShaderImageFootprintFeaturesNVidia ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE

            case StructureTypePhysicalDeviceShaderSmBuiltinsFeaturesNVidia:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->shaderSMBuiltins,
                                reinterpret_cast < Type ( PhysicalDeviceShaderSMBuiltinsFeaturesNVidia ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_SUBGROUP_UNIFORM_CONTROL_FLOW_AVAILABLE

            case StructureTypePhysicalDeviceShaderSubgroupUniformControlFlowFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->shaderSubgroupUniformControlFlow,
                                reinterpret_cast < Type ( PhysicalDeviceShaderSubgroupUniformControlFlowFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_TERMINATE_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case StructureTypePhysicalDeviceShaderTerminateInvocationFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->shaderTerminateInvocation,
                                reinterpret_cast < Type ( PhysicalDeviceShaderTerminateInvocationFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE

            case StructureTypePhysicalDeviceShadingRateImageFeaturesNVidia:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->shadingRateImage,
                                reinterpret_cast < Type ( PhysicalDeviceShadingRateImageFeaturesNVidia ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case StructureTypePhysicalDeviceSubgroupSizeControlFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->subgroupSizeControl,
                                reinterpret_cast < Type ( PhysicalDeviceSubgroupSizeControlFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE

            case StructureTypePhysicalDeviceSubpassShadingFeaturesHuawei:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->subpassShading,
                                reinterpret_cast < Type ( PhysicalDeviceSubpassShadingFeaturesHuawei ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case StructureTypePhysicalDeviceSynchronizationFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->synchronization2,
                                reinterpret_cast < Type ( PhysicalDeviceSynchronizationFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case StructureTypePhysicalDeviceTexelBufferAlignmentFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->texelBufferAlignment,
                                reinterpret_cast < Type ( PhysicalDeviceTexelBufferAlignmentFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXTURE_COMPRESSION_ASTC_HDR_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case StructureTypePhysicalDeviceTextureCompressionASTCHDRFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->textureCompressionAstcHdr,
                                reinterpret_cast < Type ( PhysicalDeviceTextureCompressionASTCHDRFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE

            case StructureTypePhysicalDeviceTransformFeedbackFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->transformFeedback,
                                reinterpret_cast < Type ( PhysicalDeviceTransformFeedbackFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE

            case StructureTypePhysicalDeviceVertexAttributeDivisorFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->vertexAttributeDivisor,
                                reinterpret_cast < Type ( PhysicalDeviceVertexAttributeDivisorFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_INPUT_DYNAMIC_STATE_AVAILABLE

            case StructureTypePhysicalDeviceVertexInputDynamicStateFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->vertexInputDynamicState,
                                reinterpret_cast < Type ( PhysicalDeviceVertexInputDynamicStateFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case StructureTypePhysicalDeviceShaderIntegerDotProductFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->shaderIntegerDotProduct,
                                reinterpret_cast < Type ( PhysicalDeviceShaderIntegerDotProductFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_SHADER_INTEGER_FUNCTIONS_AVAILABLE

            case StructureTypePhysicalDeviceShaderIntegerFunctionsFeaturesIntel:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->shaderIntegerFunctions2,
                                reinterpret_cast < Type ( PhysicalDeviceShaderIntegerFunctionsFeaturesIntel ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_AVAILABLE

            case StructureTypePhysicalDeviceWorkgroupMemoryExplicitLayoutFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->workgroupMemoryExplicitLayout,
                                reinterpret_cast < Type ( PhysicalDeviceWorkgroupMemoryExplicitLayoutFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_2_PLANE_444_FORMATS_AVAILABLE

            case StructureTypePhysicalDeviceYCBCR2Plane444FormatsFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->ycbcr2Plane444Formats,
                                reinterpret_cast < Type ( PhysicalDeviceYCBCR2Plane444FormatsFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_IMAGE_ARRAYS_AVAILABLE

            case StructureTypePhysicalDeviceYCBCRImageArraysFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->ycbcrImageArrays,
                                reinterpret_cast < Type ( PhysicalDeviceYCBCRImageArraysFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ZERO_INITIALIZE_WORKGROUP_MEMORY_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case StructureTypePhysicalDeviceZeroInitializeWorkgroupMemoryFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->zeroInitializeWorkgroupMemory,
                                reinterpret_cast < Type ( PhysicalDeviceZeroInitializeWorkgroupMemoryFeatures ) const * > ( pSource )
                        )
                );
                break;

#endif

            default:
                break;
        }
    }

    static inline auto toVulkanFormat (
            VkDeviceQueueCreateInfo                                 * pDestination,
            vulkan :: __C_ENG_TYPE ( DeviceQueueCreateInfo )  const * pSource
    ) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return;
        }

#endif

        pDestination->sType             = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        pDestination->pNext             = nullptr;

        pDestination->flags             = pSource->flags;
        pDestination->queueFamilyIndex  = pSource->queueFamilyIndex;
        pDestination->queueCount        = pSource->queueCount;
        pDestination->pQueuePriorities  = pSource->pQueuePriorities;
    }

    static inline auto prepareContext (
            CreateDeviceContext             * pContext,
            Type ( DeviceCreateInfo ) const * pSource
    ) noexcept -> VkDeviceCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pSource == nullptr || pContext == nullptr ) {
            return nullptr;
        }

#endif

        auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource );
        auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->device, pSource ) );

        if ( pSource->pEnabledFeatures != nullptr ) {
            pContext->device.pEnabledFeatures = toVulkanFormat ( & pContext->features.features, pSource->pEnabledFeatures );
        }

        pContext->device.pQueueCreateInfos = & pContext->queues [0];

        if ( pContext->device.queueCreateInfoCount > __C_ENG_VULKAN_CORE_DEVICE_QUEUE_FAMILY_CREATE_INFO_MAX_COUNT ) {
            pContext->device.queueCreateInfoCount = __C_ENG_VULKAN_CORE_DEVICE_QUEUE_FAMILY_CREATE_INFO_MAX_COUNT;
            pContext->error = ResultErrorConfigurationArraySizeSmall;
        }

        for ( cds :: uint32 i = 0U; i < pContext->device.queueCreateInfoCount; ++ i ) {
            (void) toVulkanFormat ( & pContext->queues[i], & pSource->pQueueCreateInfos[i] );
        }

        while ( pCurrent != nullptr ) {

            switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_EXTENSION_DEVICE_MEMORY_REPORT_AVAILABLE
                case StructureTypeDeviceDeviceMemoryReportCreateInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->memoryReport,
                                    reinterpret_cast < Type ( DeviceDeviceMemoryReportCreateInfo ) const * > ( pCurrent )
                            )
                    );
                    break;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTICS_CONFIG_AVAILABLE
                case StructureTypeDeviceDiagnosticsConfigCreateInfoNVidia:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->diagnosticsConfig,
                                    reinterpret_cast < Type ( DeviceDiagnosticsConfigCreateInfoNVidia ) const * > ( pCurrent )
                            )
                    );
                    break;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DEVICE_GROUP_AVAILABLE
                case StructureTypeDeviceGroupDeviceCreateInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->group,
                                    reinterpret_cast < Type ( DeviceGroupDeviceCreateInfo ) const * > ( pCurrent )
                            )
                    );
                    break;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_MEMORY_OVERALLOCATION_BEHAVIOUR_AVAILABLE
                case StructureTypeDeviceMemoryOverAllocationCreateInfoAMD:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->overallocation,
                                    reinterpret_cast < Type ( DeviceMemoryOverallocationCreateInfoAMD ) const * > ( pCurrent )
                            )
                    );
                    break;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE
                case StructureTypeDevicePrivateDataCreateInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->privateData,
                                    reinterpret_cast < Type ( DevicePrivateDataCreateInfo ) const * > ( pCurrent )
                            )
                    );
                    break;
#endif

                default:
                    featureToVulkanFormat ( pCurrentVk, pCurrent, & pContext->features );
            }

            pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
            pCurrent    = pCurrent->pNext;
        }

        pCurrentVk->pNext = nullptr;

        return & pContext->device;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    static inline auto prepareContext (
            GetPhysicalDevicePropertiesContext                * pContext,
            Type ( PhysicalDeviceExtendedProperties )   const * pSource
    ) noexcept -> VkPhysicalDeviceProperties2 * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pContext->properties.properties2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;

        auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pNext );
        auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.properties2 );

        while ( pCurrent != nullptr ) {

            switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

                case StructureTypePhysicalDeviceVulkan_1_1_Properties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.vulkan11 );
                    break;

                case StructureTypePhysicalDeviceIDProperties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.deviceID );
                    break;

                case StructureTypePhysicalDeviceMaintenanceProperties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.maintenance3 );
                    break;

                case StructureTypePhysicalDeviceMultiviewProperties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.multiview );
                    break;

                case StructureTypePhysicalDevicePointClippingProperties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.pointClipping );
                    break;

                case StructureTypePhysicalDeviceProtectedMemoryProperties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.protectedMemory );
                    break;

                case StructureTypePhysicalDeviceSubgroupProperties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.subgroup );
                    break;

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

                case StructureTypePhysicalDeviceVulkan_1_2_Properties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.vulkan12 );
                    break;

                case StructureTypePhysicalDeviceDepthStencilResolveProperties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.depthStencilResolve );
                    break;

                case StructureTypePhysicalDeviceDescriptorIndexingProperties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.descriptorIndexing );
                    break;

                case StructureTypePhysicalDeviceDriverProperties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.driver );
                    break;

                case StructureTypePhysicalDeviceFloatControlsProperties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.floatControls );
                    break;

                case StructureTypePhysicalDeviceSamplerFilterMinMaxProperties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.samplerFilterMinmax );
                    break;

                case StructureTypePhysicalDeviceTimelineSemaphoreProperties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.timelineSemaphore );
                    break;

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceVulkan_1_3_Properties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.vulkan13 );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE

                case StructureTypePhysicalDeviceBlendOperationAdvancedProperties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.blendOperationAdvanced );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONSERVATIVE_RASTERIZATION_AVAILABLE

                case StructureTypePhysicalDeviceConservativeRasterizationProperties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.conservativeRasterization );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE

                case StructureTypePhysicalDeviceCustomBorderColorProperties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.customBorderColor );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISCARD_RECTANGLES_AVAILABLE

                case StructureTypePhysicalDeviceDiscardRectangleProperties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.discardRectangle );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTERNAL_MEMORY_HOST_AVAILABLE

                case StructureTypePhysicalDeviceExternalMemoryHostProperties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.externalMemoryHost );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

                case StructureTypePhysicalDeviceFragmentDensityMapProperties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.fragmentDensityMap );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE

                case StructureTypePhysicalDeviceFragmentDensityMap2Properties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.fragmentDensityMap2 );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceInlineUniformBlockProperties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.inlineUniformBlock );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE

                case StructureTypePhysicalDeviceLineRasterizationProperties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.lineRasterization );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE

                case StructureTypePhysicalDeviceMultiDrawProperties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.multiDraw );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PCI_BUS_INFO_AVAILABLE

                case StructureTypePhysicalDevicePCIBusInfoProperties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.pciBusInfo );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PHYSICAL_DEVICE_DRM_AVAILABLE

                case StructureTypePhysicalDeviceDRMProperties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.deviceDrm );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE

                case StructureTypePhysicalDeviceProvokingVertexProperties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.provokingVertex );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE

                case StructureTypePhysicalDeviceRobustnessProperties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.robustness2 );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE

                case StructureTypePhysicalDeviceSampleLocationsProperties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.sampleLocations );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceSubgroupSizeControlProperties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.subgroupSizeControl );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceTexelBufferAlignmentProperties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.texelBufferAlignment );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE

                case StructureTypePhysicalDeviceTransformFeedbackProperties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.transformFeedback );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE

                case StructureTypePhysicalDeviceVertexAttributeDivisorProperties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.vertexAttributeDivisor );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE

                case StructureTypePhysicalDeviceAccelerationStructureProperties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.accelerationStructure );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE

                case StructureTypePhysicalDeviceFragmentShadingRateProperties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.fragmentShadingRate );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceMaintenance4Properties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.maintenance4 );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

                case StructureTypePhysicalDevicePerformanceQueryProperties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.performanceQuery );
                    break;

#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE

                case StructureTypePhysicalDevicePortabilitySubsetProperties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.portabilitySubset );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PUSH_DESCRIPTOR_AVAILABLE

                case StructureTypePhysicalDevicePushDescriptorProperties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.pushDescriptor );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE

                case StructureTypePhysicalDeviceRayTracingPipelineProperties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.rayTracingPipeline );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE

                case StructureTypePhysicalDeviceShaderIntegerDotProductProperties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.shaderIntegerDotProduct );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE

                case StructureTypePhysicalDeviceCooperativeMatrixPropertiesNVidia:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.cooperativeMatrix );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE

                case StructureTypePhysicalDeviceDeviceGeneratedCommandsPropertiesNVidia:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.deviceDeviceGeneratedCommands );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE

                case StructureTypePhysicalDeviceFragmentShadingRateEnumsPropertiesNVidia:
                    pContext->properties.fragmentShadingRateEnums.maxFragmentShadingRateInvocationCount = VkSampleCountFlagBits :: VK_SAMPLE_COUNT_1_BIT;
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.fragmentShadingRateEnums );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE

                case StructureTypePhysicalDeviceMeshShaderPropertiesNVidia:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.meshShader );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE

                case StructureTypePhysicalDeviceRayTracingPropertiesNVidia:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.rayTracing );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE

                case StructureTypePhysicalDeviceShaderSmBuiltinsPropertiesNVidia:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.shaderSmBuiltins );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE

                case StructureTypePhysicalDeviceShadingRateImagePropertiesNVidia:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.shadingRateImage );
                    break;

#endif

#if ( __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE ) && __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE

                case StructureTypePhysicalDeviceMultiviewPerViewAttributesPropertiesNVidiaExperimental:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.multiviewPerViewattributes );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_AVAILABLE

                case StructureTypePhysicalDeviceShaderCorePropertiesAMD:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.shaderCore );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_2_AVAILABLE

                case StructureTypePhysicalDeviceShaderCoreProperties2AMD:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.shaderCore2 );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE

                case StructureTypePhysicalDeviceFragmentDensityMapOffsetPropertiesQualcomm:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.fragmentDensityMapOffset );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE

                case StructureTypePhysicalDeviceSubpassShadingPropertiesHuawei:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties.subpassShading );
                    break;

#endif

                default:
                    break;
            }

            if ( pCurrentVk->pNext != nullptr ) {
                pCurrentVk = pCurrentVk->pNext;
                pCurrentVk->sType = static_cast < VkStructureType > ( pCurrent->structureType );
            }

            pCurrent    = pCurrent->pNext;
        }

        pCurrentVk->pNext = nullptr;

        return & pContext->properties.properties2;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    static inline auto extractContext (
            Type ( PhysicalDeviceExtendedProperties )       * pDestination,
            GetPhysicalDevicePropertiesContext        const * pContext
    ) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pDestination == nullptr ) {
            return;
        }

#endif

        auto pCurrent = reinterpret_cast < Type ( GenericOutStructure ) * > ( pDestination );
        while ( pCurrent != nullptr ) {

            auto pNext = pCurrent->pNext;

            switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

                case StructureTypePhysicalDeviceProperties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceExtendedProperties ) * > ( pCurrent ), & pContext->properties.properties2 );
                    break;

                case StructureTypePhysicalDeviceVulkan_1_1_Properties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceVulkan11Properties ) * > ( pCurrent ), & pContext->properties.vulkan11 );
                    break;

                case StructureTypePhysicalDeviceIDProperties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceIDProperties ) * > ( pCurrent ), & pContext->properties.deviceID );
                    break;

                case StructureTypePhysicalDeviceMaintenanceProperties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceMaintenanceProperties ) * > ( pCurrent ), & pContext->properties.maintenance3 );
                    break;

                case StructureTypePhysicalDeviceMultiviewProperties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceMultiviewProperties ) * > ( pCurrent ), & pContext->properties.multiview );
                    break;

                case StructureTypePhysicalDevicePointClippingProperties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDevicePointClippingProperties ) * > ( pCurrent ), & pContext->properties.pointClipping );
                    break;

                case StructureTypePhysicalDeviceProtectedMemoryProperties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceProtectedMemoryProperties ) * > ( pCurrent ), & pContext->properties.protectedMemory );
                    break;

                case StructureTypePhysicalDeviceSubgroupProperties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceSubgroupProperties ) * > ( pCurrent ), & pContext->properties.subgroup );
                    break;

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

                case StructureTypePhysicalDeviceVulkan_1_2_Properties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceVulkan12Properties ) * > ( pCurrent ), & pContext->properties.vulkan12 );
                    break;

                case StructureTypePhysicalDeviceDepthStencilResolveProperties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceDepthStencilResolveProperties ) * > ( pCurrent ), & pContext->properties.depthStencilResolve );
                    break;

                case StructureTypePhysicalDeviceDescriptorIndexingProperties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceDescriptorIndexingProperties ) * > ( pCurrent ), & pContext->properties.descriptorIndexing );
                    break;

                case StructureTypePhysicalDeviceDriverProperties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceDriverProperties ) * > ( pCurrent ), & pContext->properties.driver );
                    break;

                case StructureTypePhysicalDeviceFloatControlsProperties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceFloatControlsProperties ) * > ( pCurrent ), & pContext->properties.floatControls );
                    break;

                case StructureTypePhysicalDeviceSamplerFilterMinMaxProperties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceSamplerFilterMinmaxProperties ) * > ( pCurrent ), & pContext->properties.samplerFilterMinmax );
                    break;

                case StructureTypePhysicalDeviceTimelineSemaphoreProperties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceTimelineSemaphoreProperties ) * > ( pCurrent ), & pContext->properties.timelineSemaphore );
                    break;

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceVulkan_1_3_Properties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceVulkan13Properties ) * > ( pCurrent ), & pContext->properties.vulkan13 );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE

                case StructureTypePhysicalDeviceBlendOperationAdvancedProperties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceBlendOperationAdvancedProperties ) * > ( pCurrent ), & pContext->properties.blendOperationAdvanced );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONSERVATIVE_RASTERIZATION_AVAILABLE

                case StructureTypePhysicalDeviceConservativeRasterizationProperties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceConservativeRasterizationProperties ) * > ( pCurrent ), & pContext->properties.conservativeRasterization );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE

                case StructureTypePhysicalDeviceCustomBorderColorProperties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceCustomBorderColorProperties ) * > ( pCurrent ), & pContext->properties.customBorderColor );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISCARD_RECTANGLES_AVAILABLE

                case StructureTypePhysicalDeviceDiscardRectangleProperties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceDiscardRectangleProperties ) * > ( pCurrent ), & pContext->properties.discardRectangle );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTERNAL_MEMORY_HOST_AVAILABLE

                case StructureTypePhysicalDeviceExternalMemoryHostProperties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceExternalMemoryHostProperties ) * > ( pCurrent ), & pContext->properties.externalMemoryHost );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

                case StructureTypePhysicalDeviceFragmentDensityMapProperties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceFragmentDensityMapProperties ) * > ( pCurrent ), & pContext->properties.fragmentDensityMap );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE

                case StructureTypePhysicalDeviceFragmentDensityMap2Properties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceFragmentDensityMap2Properties ) * > ( pCurrent ), & pContext->properties.fragmentDensityMap2 );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceInlineUniformBlockProperties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceInlineUniformBlockProperties ) * > ( pCurrent ), & pContext->properties.inlineUniformBlock );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE

                case StructureTypePhysicalDeviceLineRasterizationProperties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceLineRasterizationProperties ) * > ( pCurrent ), & pContext->properties.lineRasterization );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE

                case StructureTypePhysicalDeviceMultiDrawProperties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceMultiDrawProperties ) * > ( pCurrent ), & pContext->properties.multiDraw );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PCI_BUS_INFO_AVAILABLE

                case StructureTypePhysicalDevicePCIBusInfoProperties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDevicePCIBusInfoProperties ) * > ( pCurrent ), & pContext->properties.pciBusInfo );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PHYSICAL_DEVICE_DRM_AVAILABLE

                case StructureTypePhysicalDeviceDRMProperties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceDRMProperties ) * > ( pCurrent ), & pContext->properties.deviceDrm );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE

                case StructureTypePhysicalDeviceProvokingVertexProperties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceProvokingVertexProperties ) * > ( pCurrent ), & pContext->properties.provokingVertex );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE

                case StructureTypePhysicalDeviceRobustnessProperties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceRobustnessProperties ) * > ( pCurrent ), & pContext->properties.robustness2 );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE

                case StructureTypePhysicalDeviceSampleLocationsProperties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceSampleLocationsProperties ) * > ( pCurrent ), & pContext->properties.sampleLocations );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceSubgroupSizeControlProperties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceSubgroupSizeControlProperties ) * > ( pCurrent ), & pContext->properties.subgroupSizeControl );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceTexelBufferAlignmentProperties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceTexelBufferAlignmentProperties ) * > ( pCurrent ), & pContext->properties.texelBufferAlignment );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE

                case StructureTypePhysicalDeviceTransformFeedbackProperties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceTransformFeedbackProperties ) * > ( pCurrent ), & pContext->properties.transformFeedback );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE

                case StructureTypePhysicalDeviceVertexAttributeDivisorProperties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceVertexAttributeDivisorProperties ) * > ( pCurrent ), & pContext->properties.vertexAttributeDivisor );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE

                case StructureTypePhysicalDeviceAccelerationStructureProperties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceAccelerationStructureProperties ) * > ( pCurrent ), & pContext->properties.accelerationStructure );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE

                case StructureTypePhysicalDeviceFragmentShadingRateProperties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceFragmentShadingRateProperties ) * > ( pCurrent ), & pContext->properties.fragmentShadingRate );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceMaintenance4Properties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceMaintenance4Properties ) * > ( pCurrent ), & pContext->properties.maintenance4 );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

                case StructureTypePhysicalDevicePerformanceQueryProperties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDevicePerformanceQueryProperties ) * > ( pCurrent ), & pContext->properties.performanceQuery );
                    break;

#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE

                case StructureTypePhysicalDevicePortabilitySubsetProperties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDevicePortabilitySubsetProperties ) * > ( pCurrent ), & pContext->properties.portabilitySubset );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PUSH_DESCRIPTOR_AVAILABLE

                case StructureTypePhysicalDevicePushDescriptorProperties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDevicePushDescriptorProperties ) * > ( pCurrent ), & pContext->properties.pushDescriptor );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE

                case StructureTypePhysicalDeviceRayTracingPipelineProperties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceRayTracingPipelineProperties ) * > ( pCurrent ), & pContext->properties.rayTracingPipeline );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE

                case StructureTypePhysicalDeviceShaderIntegerDotProductProperties:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceShaderIntegerDotProductProperties ) * > ( pCurrent ), & pContext->properties.shaderIntegerDotProduct );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE

                case StructureTypePhysicalDeviceCooperativeMatrixPropertiesNVidia:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceCooperativeMatrixPropertiesNVidia ) * > ( pCurrent ), & pContext->properties.cooperativeMatrix );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE

                case StructureTypePhysicalDeviceDeviceGeneratedCommandsPropertiesNVidia:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceDeviceGeneratedCommandsPropertiesNVidia ) * > ( pCurrent ), & pContext->properties.deviceDeviceGeneratedCommands );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE

                case StructureTypePhysicalDeviceFragmentShadingRateEnumsPropertiesNVidia:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceFragmentShadingRateEnumsPropertiesNVidia ) * > ( pCurrent ), & pContext->properties.fragmentShadingRateEnums );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE

                case StructureTypePhysicalDeviceMeshShaderPropertiesNVidia:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceMeshShaderPropertiesNVidia ) * > ( pCurrent ), & pContext->properties.meshShader );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE

                case StructureTypePhysicalDeviceRayTracingPropertiesNVidia:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceRayTracingPropertiesNVidia ) * > ( pCurrent ), & pContext->properties.rayTracing );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE

                case StructureTypePhysicalDeviceShaderSmBuiltinsPropertiesNVidia:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceShaderSMBuiltinsPropertiesNVidia ) * > ( pCurrent ), & pContext->properties.shaderSmBuiltins );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE

                case StructureTypePhysicalDeviceShadingRateImagePropertiesNVidia:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceShadingRateImagePropertiesNVidia ) * > ( pCurrent ), & pContext->properties.shadingRateImage );
                    break;

#endif

#if ( __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE ) && __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE

                case StructureTypePhysicalDeviceMultiviewPerViewAttributesPropertiesNVidiaExperimental:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceMultiviewPerViewAttributesPropertiesNVidia ) * > ( pCurrent ), & pContext->properties.multiviewPerViewattributes );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_AVAILABLE

                case StructureTypePhysicalDeviceShaderCorePropertiesAMD:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceShaderCorePropertiesAMD ) * > ( pCurrent ), & pContext->properties.shaderCore );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_2_AVAILABLE

                case StructureTypePhysicalDeviceShaderCoreProperties2AMD:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceShaderCoreProperties2AMD ) * > ( pCurrent ), & pContext->properties.shaderCore2 );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE

                case StructureTypePhysicalDeviceFragmentDensityMapOffsetPropertiesQualcomm:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceFragmentDensityMapOffsetPropertiesQualcomm ) * > ( pCurrent ), & pContext->properties.fragmentDensityMapOffset );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE

                case StructureTypePhysicalDeviceSubpassShadingPropertiesHuawei:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceSubpassShadingPropertiesHuawei ) * > ( pCurrent ), & pContext->properties.subpassShading );
                    break;

#endif

                default:
                    break;
            }

            pCurrent->pNext = pNext;
            pCurrent        = pCurrent->pNext;
        }
    }
#endif

}


#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif //C_ENG_VULKANAPICALLSCONVERSION_HPP

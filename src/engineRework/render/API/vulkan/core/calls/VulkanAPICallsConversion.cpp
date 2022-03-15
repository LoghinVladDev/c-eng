//
// Created by loghin on 16.02.2022.
//

#include <calls/VulkanAPICallsConversion.hpp>
#include <calls/VulkanAPICallsPrivate.hpp>
#include <calls/VulkanAPICallsTypes.hpp>
#include <calls/VulkanAPICallsConversionContextDiagnosis.hpp>
#include <CDS/String>

#define C_ENG_MAP_START     SOURCE
#include <ObjectMapping.hpp>


namespace engine :: vulkan {

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
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
    auto toVulkanFormat (
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
    auto toVulkanFormat (
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
    auto toVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
        pDestination->deviceType                                                 = static_cast < vulkan :: Type ( PhysicalDeviceType ) > ( pSource->deviceType );

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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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

    auto toVulkanFormat (
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

    auto prepareContext (
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

                    if ( pContext->validationFeatures.enabledValidationFeatureCount > engine :: vulkan :: config :: validationFeatureEnableCount ) {
                        __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                                "config :: validationFeatureEnableCount = %d. Minimum Required = %d",
                                engine :: vulkan :: config :: validationFeatureEnableCount,
                                pContext->validationFeatures.enabledValidationFeatureCount
                        ))

                        pContext->validationFeatures.enabledValidationFeatureCount = engine :: vulkan :: config :: validationFeatureEnableCount;
                    }

                    for ( cds :: uint32 i = 0U; i < pContext->validationFeatures.enabledValidationFeatureCount; ++ i ) {
                        pContext->validationFeatureEnables[i] = static_cast < VkValidationFeatureEnableEXT > ( pValidationFeatures->pEnabledValidationFeatures[i] );
                    }

                    pContext->validationFeatures.pEnabledValidationFeatures = & pContext->validationFeatureEnables[0];

                    if ( pContext->validationFeatures.disabledValidationFeatureCount > engine :: vulkan :: config :: validationFeatureDisableCount ) {
                        __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                                "config :: validationFeatureDisableCount = %d. Minimum Required = %d",
                                engine :: vulkan :: config :: validationFeatureDisableCount,
                                pContext->validationFeatures.disabledValidationFeatureCount
                        ))

                        pContext->validationFeatures.disabledValidationFeatureCount = engine :: vulkan :: config :: validationFeatureDisableCount;
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

                    if ( pValidationFlags->disabledValidationCheckCount > engine :: vulkan :: config :: validationCheckCount ) {
                        __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                                "config :: validationCheckCount = %d. Minimum Required = %d",
                                engine :: vulkan :: config :: validationCheckCount,
                                pValidationFlags->disabledValidationCheckCount
                        ))

                        pContext->validationFlags.disabledValidationCheckCount = engine :: vulkan :: config :: validationCheckCount;
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

    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto toVulkanFormat (
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
    auto toVulkanFormat (
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
    auto toVulkanFormat (
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
    auto toVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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

        pDestination->pointClippingBehavior             = static_cast < vulkan :: Type ( PointClippingBehavior ) > ( pSource->pointClippingBehavior );

        pDestination->maxMemoryAllocationSize           = pSource->maxMemoryAllocationSize;

        (void) std :: memcpy ( pDestination->deviceUUID, pSource->deviceUUID, sizeof ( pSource->deviceUUID[0] ) * VK_UUID_SIZE ); // NOLINT(clion-misra-cpp2008-5-2-12)
        (void) std :: memcpy ( pDestination->driverUUID, pSource->driverUUID, sizeof ( pSource->driverUUID[0] ) * VK_UUID_SIZE ); // NOLINT(clion-misra-cpp2008-5-2-12)
        (void) std :: memcpy ( pDestination->deviceLUID, pSource->deviceLUID, sizeof ( pSource->deviceLUID[0] ) * VK_LUID_SIZE ); // NOLINT(clion-misra-cpp2008-5-2-12)

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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

        pDestination->pointClippingBehavior             = static_cast < vulkan :: Type ( PointClippingBehavior ) > ( pSource->pointClippingBehavior );

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto toVulkanFormat (
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
    auto toVulkanFormat (
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
    auto toVulkanFormat (
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
    auto toVulkanFormat (
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
    auto toVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
            Type ( PhysicalDeviceVulkan12Properties )       * pDestination,
            VkPhysicalDeviceVulkan12Properties        const * pSource
    ) noexcept -> Type ( PhysicalDeviceVulkan12Properties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceVulkan_1_2_Properties;

        pDestination->driverID                                                  = static_cast < vulkan :: Type ( DriverID ) > ( pSource->driverID );
        (void) std :: memcpy ( pDestination->driverName,                        pSource->driverName, sizeof ( pSource->driverName[0] ) * VK_MAX_DRIVER_NAME_SIZE ); // NOLINT(clion-misra-cpp2008-5-2-12)
        (void) std :: memcpy ( pDestination->driverInfo,                        pSource->driverInfo, sizeof ( pSource->driverInfo[0] ) * VK_MAX_DRIVER_INFO_SIZE ); // NOLINT(clion-misra-cpp2008-5-2-12)
        fromVulkanFormat ( & pDestination->conformanceVersion,                  & pSource->conformanceVersion );

        pDestination->denormBehaviorIndependence                                = static_cast < vulkan :: Type ( ShaderFloatControlsIndependence ) > ( pSource->denormBehaviorIndependence );
        pDestination->roundingModeIndependence                                  = static_cast < vulkan :: Type ( ShaderFloatControlsIndependence ) > ( pSource->roundingModeIndependence );

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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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

        pDestination->driverID                                                  = static_cast < vulkan :: Type ( DriverID ) > ( pSource->driverID );
        (void) std :: memcpy ( pDestination->driverName,                        pSource->driverName, sizeof ( pSource->driverName[0] ) * VK_MAX_DRIVER_NAME_SIZE ); // NOLINT(clion-misra-cpp2008-5-2-12)
        (void) std :: memcpy ( pDestination->driverInfo,                        pSource->driverInfo, sizeof ( pSource->driverInfo[0] ) * VK_MAX_DRIVER_INFO_SIZE ); // NOLINT(clion-misra-cpp2008-5-2-12)
        fromVulkanFormat ( & pDestination->conformanceVersion,                  & pSource->conformanceVersion );

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    auto fromVulkanFormat (
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

        pDestination->denormBehaviorIndependence                                = static_cast < vulkan :: Type ( ShaderFloatControlsIndependence ) > ( pSource->denormBehaviorIndependence );
        pDestination->roundingModeIndependence                                  = static_cast < vulkan :: Type ( ShaderFloatControlsIndependence ) > ( pSource->roundingModeIndependence );

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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
            Type ( PhysicalDeviceImagelessFrameBufferFeatures )       * pDestination,
            VkPhysicalDeviceImagelessFramebufferFeatures        const * pSource
    ) noexcept -> Type ( PhysicalDeviceImagelessFrameBufferFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceImagelessFrameBufferFeatures;
        pDestination->pNext = nullptr;

        pDestination->imagelessFramebuffer             = pSource->imagelessFramebuffer;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto toVulkanFormat (
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
    auto toVulkanFormat (
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
    auto toVulkanFormat (
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
    auto toVulkanFormat (
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
    auto toVulkanFormat (
            VkPhysicalDeviceImagelessFramebufferFeatures              * pDestination,
            Type ( PhysicalDeviceImagelessFrameBufferFeatures ) const * pSource
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
    auto fromVulkanFormat (
            Type ( PhysicalDeviceHostQueryResetFeatures )       * pDestination,
            VkPhysicalDeviceHostQueryResetFeatures        const * pSource
    ) noexcept -> Type ( PhysicalDeviceHostQueryResetFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pSource == nullptr || pDestination == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceHostQueryResetFeatures;
        pDestination->pNext         = nullptr;

        pDestination->hostQueryReset             = pSource->hostQueryReset;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    auto fromVulkanFormat (
            Type ( PhysicalDeviceSeparateDepthStencilLayoutsFeatures )       * pDestination,
            VkPhysicalDeviceSeparateDepthStencilLayoutsFeatures        const * pSource
    ) noexcept -> Type ( PhysicalDeviceSeparateDepthStencilLayoutsFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pSource == nullptr || pDestination == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceSeparateDepthStencilLayoutsFeatures;
        pDestination->pNext         = nullptr;

        pDestination->separateDepthStencilLayouts             = pSource->separateDepthStencilLayouts;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    auto fromVulkanFormat (
            Type ( PhysicalDeviceTimelineSemaphoreFeatures )       * pDestination,
            VkPhysicalDeviceTimelineSemaphoreFeatures        const * pSource
    ) noexcept -> Type ( PhysicalDeviceTimelineSemaphoreFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pSource == nullptr || pDestination == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceTimelineSemaphoreFeatures;
        pDestination->pNext         = nullptr;

        pDestination->timelineSemaphore                 = pSource->timelineSemaphore;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    auto toVulkanFormat (
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
    auto toVulkanFormat (
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
    auto toVulkanFormat (
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
    auto toVulkanFormat (
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
    auto toVulkanFormat (
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
    auto toVulkanFormat (
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
    auto toVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
        pDestination->maxFragmentShadingRateRasterizationSamples                = static_cast < vulkan :: Type ( SampleCountFlag ) > ( pSource->maxFragmentShadingRateRasterizationSamples );

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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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

        pDestination->maxFragmentShadingRateInvocationCount  = static_cast < vulkan :: Type ( SampleCountFlag ) > ( pSource->maxFragmentShadingRateInvocationCount );

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto fromVulkanFormat (
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
    auto toVulkanFormat (
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
    auto toVulkanFormat (
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

    auto featureToVulkanFormat (
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

            case StructureTypePhysicalDeviceImagelessFrameBufferFeatures:
                pDestination->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->imagelessFramebuffer,
                                reinterpret_cast < Type ( PhysicalDeviceImagelessFrameBufferFeatures ) const * > ( pSource )
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

    auto toVulkanFormat (
            VkDeviceQueueCreateInfo                                 * pDestination,
            vulkan :: Type ( DeviceQueueCreateInfo )  const * pSource
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

    auto prepareContext (
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

        if ( pContext->device.queueCreateInfoCount > engine :: vulkan :: config :: queueFamilyCreateInfoCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                    "config :: queueFamilyCreateInfoCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: queueFamilyCreateInfoCount,
                    pContext->device.queueCreateInfoCount
            ))

            pContext->device.queueCreateInfoCount = engine :: vulkan :: config :: queueFamilyCreateInfoCount;
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
    auto prepareContext (
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
    auto extractContext (
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

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto prepareContext (
            GetPhysicalDeviceFeaturesContext                  * pContext,
            Type ( PhysicalDeviceExtendedFeatures )   const * pSource
    ) noexcept -> VkPhysicalDeviceFeatures2 * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pContext->features.features2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;

        auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pNext );
        auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.features2 );

        while ( pCurrent != nullptr ) {

            switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

                case StructureTypePhysicalDeviceVulkan_1_1_Features:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.vulkan11 );
                    break;

                case StructureTypePhysicalDevice16BitStorageFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features._16BitStorage );
                    break;

                case StructureTypePhysicalDeviceMultiviewFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.multiview );
                    break;

                case StructureTypePhysicalDeviceProtectedMemoryFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.protectedMemory );
                    break;

                case StructureTypePhysicalDeviceSamplerYCBCRConversionFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.samplerYcbcrConversion );
                    break;

                case StructureTypePhysicalDeviceShaderDrawParametersFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.shaderDrawParameters );
                    break;

                case StructureTypePhysicalDeviceVariablePointersFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.variablePointers );
                    break;

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

                case StructureTypePhysicalDeviceVulkan_1_2_Features:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.vulkan12 );
                    break;

                case StructureTypePhysicalDevice8BitStorageFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features._8BitStorage );
                    break;

                case StructureTypePhysicalDeviceBufferDeviceAddressFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.bufferDeviceAddress );
                    break;

                case StructureTypePhysicalDeviceDescriptorIndexingFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.descriptorIndexing );
                    break;

                case StructureTypePhysicalDeviceHostQueryResetFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.hostQueryReset );
                    break;

                case StructureTypePhysicalDeviceImagelessFrameBufferFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.imagelessFramebuffer );
                    break;

                case StructureTypePhysicalDeviceScalarBlockLayoutFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.scalarBlockLayout );
                    break;

                case StructureTypePhysicalDeviceSeparateDepthStencilLayoutsFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.separateDepthStencilLayouts );
                    break;

                case StructureTypePhysicalDeviceShaderAtomicInt64Features:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.shaderAtomicInt64 );
                    break;

                case StructureTypePhysicalDeviceShaderFloat16Int8Features:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.shaderFloat16Int8 );
                    break;

                case StructureTypePhysicalDeviceShaderSubgroupExtendedTypesFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.shaderSubgroupExtendedTypes );
                    break;

                case StructureTypePhysicalDeviceTimelineSemaphoreFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.timelineSemaphore );
                    break;

                case StructureTypePhysicalDeviceUniformBufferStandardLayoutFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.uniformBufferStandardLayout );
                    break;

                case StructureTypePhysicalDeviceVulkanMemoryModelFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.vulkanMemoryModel );
                    break;

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceVulkan_1_3_Features:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.vulkan13 );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_4444_FORMATS_AVAILABLE

                case StructureTypePhysicalDevice4444FormatsFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features._4444Formats );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ASTC_DECODE_MODE_AVAILABLE

                case StructureTypePhysicalDeviceASTCDecodeFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.astcDecode );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE

                case StructureTypePhysicalDeviceAccelerationStructureFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.accelerationStructure );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE

                case StructureTypePhysicalDeviceBlendOperationAdvancedFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.blendOperationAdvanced );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BORDER_COLOR_SWIZZLE_AVAILABLE

                case StructureTypePhysicalDeviceBorderColorSwizzleFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.borderColorSwizzle );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_DEVICE_COHERENT_MEMORY_AVAILABLE

                case StructureTypePhysicalDeviceCoherentMemoryFeaturesAMD:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.coherentMemory );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_COLOR_WRITE_ENABLE_AVAILABLE

                case StructureTypePhysicalDeviceColorWriteEnableFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.colorWriteEnable );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COMPUTE_SHADER_DERIVATIVES_AVAILABLE

                case StructureTypePhysicalDeviceComputeShaderDerivativesFeaturesNVidia:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.computerShaderDerivatives );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE

                case StructureTypePhysicalDeviceConditionalRenderingFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.conditionalRendering );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE

                case StructureTypePhysicalDeviceCooperativeMatrixFeaturesNVidia:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.cooperativeMatrix );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CORNER_SAMPLED_IMAGE_AVAILABLE

                case StructureTypePhysicalDeviceCornerSampledImageFeaturesNVidia:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.cornerSampledImage );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COVERAGE_REDUCTION_MODE_AVAILABLE

                case StructureTypePhysicalDeviceCoverageReductionModeFeaturesNVidia:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.coverageReduction );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE

                case StructureTypePhysicalDeviceCustomBorderColorFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.customBorderColor );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_IMAGE_ALIASING_AVAILABLE

                case StructureTypePhysicalDeviceDedicatedAllocationImageAliasingFeaturesNVidia:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.dedicatedAllocationImageAliasingFeatures );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_CONTROL_AVAILABLE

                case StructureTypePhysicalDeviceDepthClipControlFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.depthClipControl );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_ENABLE_AVAILABLE

                case StructureTypePhysicalDeviceDepthClipEnableFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.depthClipEnable );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE

                case StructureTypePhysicalDeviceDeviceGeneratedCommandsFeaturesNVidia:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.deviceGeneratedCommands );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEVICE_MEMORY_REPORT_AVAILABLE

                case StructureTypePhysicalDeviceDeviceMemoryReportFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.deviceMemoryReport );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTICS_CONFIG_AVAILABLE

                case StructureTypePhysicalDeviceDiagnosticsConfigFeaturesNVidia:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.diagnosticsConfig );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceDynamicRenderingFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.dynamicRendering );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SCISSOR_EXCLUSIVE_AVAILABLE

                case StructureTypePhysicalDeviceExclusiveScissorFeaturesNVidia:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.exclusiveScissor );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE

                case StructureTypePhysicalDeviceExtendedDynamicStateFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.extendedDynamicState );
                    break;

                case StructureTypePhysicalDeviceExtendedDynamicState2Features:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.extendedDynamicState2 );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_RDMA_AVAILABLE

                case StructureTypePhysicalDeviceExternalMemoryRDMAFeaturesNVidia:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.externalMemoryRDMA );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

                case StructureTypePhysicalDeviceFragmentDensityMapFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.fragmentDensityMap );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE

                case StructureTypePhysicalDeviceFragmentDensityMap2Features:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.fragmentDensityMap2 );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE

                case StructureTypePhysicalDeviceFragmentDensityMapOffsetFeaturesQualcomm:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.fragmentDensityMapOffset );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADER_BARYCENTRIC_AVAILABLE

                case StructureTypePhysicalDeviceFragmentShaderBarycentricFeaturesNVidia:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.fragmentShaderBarycentric );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_SHADER_INTERLOCK_AVAILABLE

                case StructureTypePhysicalDeviceFragmentShaderInterlockFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.fragmentShaderInterlock );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE

                case StructureTypePhysicalDeviceFragmentShadingRateEnumsFeaturesNVidia:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.fragmentShadingRateEnums );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE

                case StructureTypePhysicalDeviceFragmentShadingRateFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.fragmentShadingRate );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE

                case StructureTypePhysicalDeviceGlobalPriorityQueryFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.globalPriorityQuery );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_ROBUSTNESS_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceImageRobustnessFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.imageRobustness );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_VIEW_MIN_LOD_AVAILABLE

                case StructureTypePhysicalDeviceImageViewMinLODFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.imageViewMinLOD );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INDEX_TYPE_UINT8_AVAILABLE

                case StructureTypePhysicalDeviceIndexTypeUInt8Features:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.indexTypeUInt8 );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_INHERITED_VIEWPORT_SCISSOR_AVAILABLE

                case StructureTypePhysicalDeviceInheritedViewportScissorFeaturesNVidia:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.inheritedViewportScissor );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceInlineUniformBlockFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.inlineUniformBlock );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_INVOCATION_MASK_AVAILABLE

                case StructureTypePhysicalDeviceInvocationMaskFeaturesHuawei:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.invocationMask );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE

                case StructureTypePhysicalDeviceLineRasterizationFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.lineRasterization );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_LINEAR_COLOR_ATTACHMENT_AVAILABLE

                case StructureTypePhysicalDeviceLinearColorAttachmentFeaturesNVidia:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.linearColorAttachment );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceMaintenance4Features:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.maintenance4 );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_PRIORITY_AVAILABLE

                case StructureTypePhysicalDeviceMemoryPriorityFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.memoryPriority );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE

                case StructureTypePhysicalDeviceMeshShaderFeaturesNVidia:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.meshShader );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE

                case StructureTypePhysicalDeviceMultiDrawFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.multiDraw );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE

                case StructureTypePhysicalDeviceMutableDescriptorTypeFeaturesValve:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.mutableDescriptorType );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PAGEABLE_DEVICE_LOCAL_MEMORY_AVAILABLE

                case StructureTypePhysicalDevicePageableDeviceLocalMemoryFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.pageableDeviceLocalMemory );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

                case StructureTypePhysicalDevicePerformanceQueryFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.performanceQuery );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDevicePipelineCreationCacheControlFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.pipelineCreationCacheControl );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE

                case StructureTypePhysicalDevicePipelineExecutablePropertiesFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.pipelineExecutableProperties );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE

                case StructureTypePhysicalDevicePortabilitySubsetFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.portabilitySubset );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_ID_AVAILABLE

                case StructureTypePhysicalDevicePresentIDFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.presentID );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_WAIT_AVAILABLE

                case StructureTypePhysicalDevicePresentWaitFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.presentWait );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIMITIVE_TOPOLOGY_LIST_RESTART_AVAILABLE

                case StructureTypePhysicalDevicePrimitiveTopologyListRestartFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.primitiveTopologyListRestart );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDevicePrivateDataFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.privateData );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE

                case StructureTypePhysicalDeviceProvokingVertexFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.provokingVertex );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_RGBA_10_X_6_FORMATS_AVAILABLE

                case StructureTypePhysicalDeviceRGBA10x6FormatsFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.rgba10x6FormatsFeaturesExt );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ARM_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_AVAILABLE

                case StructureTypePhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.rasterizationOrderAttachmentAccess );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_QUERY_AVAILABLE

                case StructureTypePhysicalDeviceRayQueryFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.rayQuery );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE

                case StructureTypePhysicalDeviceRayTracingMotionBlurFeaturesNVidia:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.rayTracingMotionBlur );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE

                case StructureTypePhysicalDeviceRayTracingPipelineFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.rayTracingPipeline );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_REPRESENTATIVE_FRAGMENT_TEST_AVAILABLE

                case StructureTypePhysicalDeviceRepresentativeFragmentTestFeaturesNVidia:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.representativeFragmentText );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE

                case StructureTypePhysicalDeviceRobustnessFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.robustness2 );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_AVAILABLE

                case StructureTypePhysicalDeviceShaderAtomicFloatFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.shaderAtomicFloat );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_2_AVAILABLE

                case StructureTypePhysicalDeviceShaderAtomicFloat2Features:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.shaderAtomicFloat2 );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_CLOCK_AVAILABLE

                case StructureTypePhysicalDeviceShaderClockFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.shaderDeviceShaderClock );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_DEMOTE_TO_HELPER_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceShaderDemoteToHelperInvocationFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.shaderDemoteToHelperInvocation );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_IMAGE_ATOMIC_INT64_AVAILABLE

                case StructureTypePhysicalDeviceShaderImageAtomicInt64Features:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.shaderImageAtomicInt64 );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_IMAGE_FOOTPRINT_AVAILABLE

                case StructureTypePhysicalDeviceShaderImageFootprintFeaturesNVidia:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.shaderImageFootprint );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE

                case StructureTypePhysicalDeviceShaderSmBuiltinsFeaturesNVidia:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.shaderSMBuiltins );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_SUBGROUP_UNIFORM_CONTROL_FLOW_AVAILABLE

                case StructureTypePhysicalDeviceShaderSubgroupUniformControlFlowFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.shaderSubgroupUniformControlFlow );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_TERMINATE_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceShaderTerminateInvocationFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.shaderTerminateInvocation );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE

                case StructureTypePhysicalDeviceShadingRateImageFeaturesNVidia:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.shadingRateImage );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceSubgroupSizeControlFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.subgroupSizeControl );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE

                case StructureTypePhysicalDeviceSubpassShadingFeaturesHuawei:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.subpassShading );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceSynchronizationFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.synchronization2 );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceTexelBufferAlignmentFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.texelBufferAlignment );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXTURE_COMPRESSION_ASTC_HDR_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceTextureCompressionASTCHDRFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.textureCompressionAstcHdr );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE

                case StructureTypePhysicalDeviceTransformFeedbackFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.transformFeedback );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE

                case StructureTypePhysicalDeviceVertexAttributeDivisorFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.vertexAttributeDivisor );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_INPUT_DYNAMIC_STATE_AVAILABLE

                case StructureTypePhysicalDeviceVertexInputDynamicStateFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.vertexInputDynamicState );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceShaderIntegerDotProductFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.shaderIntegerDotProduct );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_SHADER_INTEGER_FUNCTIONS_AVAILABLE

                case StructureTypePhysicalDeviceShaderIntegerFunctionsFeaturesIntel:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.shaderIntegerFunctions2 );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_AVAILABLE

                case StructureTypePhysicalDeviceWorkgroupMemoryExplicitLayoutFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.workgroupMemoryExplicitLayout );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_2_PLANE_444_FORMATS_AVAILABLE

                case StructureTypePhysicalDeviceYCBCR2Plane444FormatsFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.ycbcr2Plane444Formats );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_IMAGE_ARRAYS_AVAILABLE

                case StructureTypePhysicalDeviceYCBCRImageArraysFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.ycbcrImageArrays );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ZERO_INITIALIZE_WORKGROUP_MEMORY_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceZeroInitializeWorkgroupMemoryFeatures:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->features.zeroInitializeWorkgroupMemory );
                    break;

#endif

                default:
                    break;

            }

            if ( pCurrentVk->pNext != nullptr ) {
                pCurrentVk = pCurrentVk->pNext;
                pCurrentVk->sType = static_cast < VkStructureType > ( pCurrent->structureType );
            }

            pCurrent = pCurrent->pNext;
        }

        pCurrentVk->pNext = nullptr;

        return & pContext->features.features2;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto extractContext (
            Type ( PhysicalDeviceExtendedFeatures )       * pDestination,
            GetPhysicalDeviceFeaturesContext        const * pContext
    ) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pDestination == nullptr ) {
            return;
        }

#endif

        auto pCurrent   = reinterpret_cast < Type ( GenericOutStructure ) * > ( pDestination );

        while ( pCurrent != nullptr ) {

            auto pNext = pCurrent->pNext;

            switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

                case StructureTypePhysicalDeviceFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceExtendedFeatures ) * >( pCurrent ), & pContext->features.features2 );
                    break;

                case StructureTypePhysicalDeviceVulkan_1_1_Features:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceVulkan11Features ) * > ( pCurrent ), & pContext->features.vulkan11 );
                    break;

                case StructureTypePhysicalDevice16BitStorageFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDevice16BitStorageFeatures ) * > ( pCurrent ), & pContext->features._16BitStorage );
                    break;

                case StructureTypePhysicalDeviceMultiviewFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceMultiviewFeatures ) * > ( pCurrent ), & pContext->features.multiview );
                    break;

                case StructureTypePhysicalDeviceProtectedMemoryFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceProtectedMemoryFeatures ) * > ( pCurrent ), & pContext->features.protectedMemory );
                    break;

                case StructureTypePhysicalDeviceSamplerYCBCRConversionFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceSamplerYCBCRConversionFeatures ) * > ( pCurrent ), & pContext->features.samplerYcbcrConversion );
                    break;

                case StructureTypePhysicalDeviceShaderDrawParametersFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceShaderDrawParametersFeatures ) * > ( pCurrent ), & pContext->features.shaderDrawParameters );
                    break;

                case StructureTypePhysicalDeviceVariablePointersFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceVariablePointersFeatures ) * > ( pCurrent ), & pContext->features.variablePointers );
                    break;

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

                case StructureTypePhysicalDeviceVulkan_1_2_Features:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceVulkan12Features ) * > ( pCurrent ), & pContext->features.vulkan12 );
                    break;

                case StructureTypePhysicalDevice8BitStorageFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDevice8BitStorageFeatures ) * > ( pCurrent ), & pContext->features._8BitStorage );
                    break;

                case StructureTypePhysicalDeviceBufferDeviceAddressFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceBufferDeviceAddressFeatures ) * > ( pCurrent ), & pContext->features.bufferDeviceAddress );
                    break;

                case StructureTypePhysicalDeviceDescriptorIndexingFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceDescriptorIndexingFeatures ) * > ( pCurrent ), & pContext->features.descriptorIndexing );
                    break;

                case StructureTypePhysicalDeviceHostQueryResetFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceHostQueryResetFeatures ) * > ( pCurrent ), & pContext->features.hostQueryReset );
                    break;

                case StructureTypePhysicalDeviceImagelessFrameBufferFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceImagelessFrameBufferFeatures ) * > ( pCurrent ), & pContext->features.imagelessFramebuffer );
                    break;

                case StructureTypePhysicalDeviceScalarBlockLayoutFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceScalarBlockLayoutFeatures ) * > ( pCurrent ), & pContext->features.scalarBlockLayout );
                    break;

                case StructureTypePhysicalDeviceSeparateDepthStencilLayoutsFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceSeparateDepthStencilLayoutsFeatures ) * > ( pCurrent ), & pContext->features.separateDepthStencilLayouts );
                    break;

                case StructureTypePhysicalDeviceShaderAtomicInt64Features:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceShaderAtomicInt64Features ) * > ( pCurrent ), & pContext->features.shaderAtomicInt64 );
                    break;

                case StructureTypePhysicalDeviceShaderFloat16Int8Features:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceShaderFloat16Int8Features ) * > ( pCurrent ), & pContext->features.shaderFloat16Int8 );
                    break;

                case StructureTypePhysicalDeviceShaderSubgroupExtendedTypesFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceShaderSubgroupExtendedTypesFeatures ) * > ( pCurrent ), & pContext->features.shaderSubgroupExtendedTypes );
                    break;

                case StructureTypePhysicalDeviceTimelineSemaphoreFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceTimelineSemaphoreFeatures ) * > ( pCurrent ), & pContext->features.timelineSemaphore );
                    break;

                case StructureTypePhysicalDeviceUniformBufferStandardLayoutFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceUniformBufferStandardLayoutFeatures ) * > ( pCurrent ), & pContext->features.uniformBufferStandardLayout );
                    break;

                case StructureTypePhysicalDeviceVulkanMemoryModelFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceVulkanMemoryModelFeatures ) * > ( pCurrent ), & pContext->features.vulkanMemoryModel );
                    break;

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceVulkan_1_3_Features:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceVulkan13Features ) * > ( pCurrent ), & pContext->features.vulkan13 );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_4444_FORMATS_AVAILABLE

                case StructureTypePhysicalDevice4444FormatsFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDevice4444FormatsFeatures ) * > ( pCurrent ), & pContext->features._4444Formats );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ASTC_DECODE_MODE_AVAILABLE

                case StructureTypePhysicalDeviceASTCDecodeFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceASTCDecodeFeatures ) * > ( pCurrent ), & pContext->features.astcDecode );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE

                case StructureTypePhysicalDeviceAccelerationStructureFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceAccelerationStructureFeatures ) * > ( pCurrent ), & pContext->features.accelerationStructure );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE

                case StructureTypePhysicalDeviceBlendOperationAdvancedFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceBlendOperationAdvancedFeatures ) * > ( pCurrent ), & pContext->features.blendOperationAdvanced );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BORDER_COLOR_SWIZZLE_AVAILABLE

                case StructureTypePhysicalDeviceBorderColorSwizzleFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceBorderColorSwizzleFeatures ) * > ( pCurrent ), & pContext->features.borderColorSwizzle );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_DEVICE_COHERENT_MEMORY_AVAILABLE

                case StructureTypePhysicalDeviceCoherentMemoryFeaturesAMD:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceCoherentMemoryFeaturesAMD ) * > ( pCurrent ), & pContext->features.coherentMemory );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_COLOR_WRITE_ENABLE_AVAILABLE

                case StructureTypePhysicalDeviceColorWriteEnableFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceColorWriteEnableFeatures ) * > ( pCurrent ), & pContext->features.colorWriteEnable );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COMPUTE_SHADER_DERIVATIVES_AVAILABLE

                case StructureTypePhysicalDeviceComputeShaderDerivativesFeaturesNVidia:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceComputeShaderDerivativesFeaturesNVidia ) * > ( pCurrent ), & pContext->features.computerShaderDerivatives );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE

                case StructureTypePhysicalDeviceConditionalRenderingFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceConditionalRenderingFeatures ) * > ( pCurrent ), & pContext->features.conditionalRendering );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE

                case StructureTypePhysicalDeviceCooperativeMatrixFeaturesNVidia:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceCooperativeMatrixFeaturesNVidia ) * > ( pCurrent ), & pContext->features.cooperativeMatrix );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CORNER_SAMPLED_IMAGE_AVAILABLE

                case StructureTypePhysicalDeviceCornerSampledImageFeaturesNVidia:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceCornerSampledImageFeaturesNVidia ) * > ( pCurrent ), & pContext->features.cornerSampledImage );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COVERAGE_REDUCTION_MODE_AVAILABLE

                case StructureTypePhysicalDeviceCoverageReductionModeFeaturesNVidia:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceCoverageReductionModeFeaturesNVidia ) * > ( pCurrent ), & pContext->features.coverageReduction );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE

                case StructureTypePhysicalDeviceCustomBorderColorFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceCustomBorderColorFeatures ) * > ( pCurrent ), & pContext->features.customBorderColor );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_IMAGE_ALIASING_AVAILABLE

                case StructureTypePhysicalDeviceDedicatedAllocationImageAliasingFeaturesNVidia:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNVidia ) * > ( pCurrent ), & pContext->features.dedicatedAllocationImageAliasingFeatures );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_CONTROL_AVAILABLE

                case StructureTypePhysicalDeviceDepthClipControlFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceDepthClipControlFeatures ) * > ( pCurrent ), & pContext->features.depthClipControl );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_ENABLE_AVAILABLE

                case StructureTypePhysicalDeviceDepthClipEnableFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceDepthClipEnableFeatures ) * > ( pCurrent ), & pContext->features.depthClipEnable );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE

                case StructureTypePhysicalDeviceDeviceGeneratedCommandsFeaturesNVidia:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceDeviceGeneratedCommandsFeaturesNVidia ) * > ( pCurrent ), & pContext->features.deviceGeneratedCommands );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEVICE_MEMORY_REPORT_AVAILABLE

                case StructureTypePhysicalDeviceDeviceMemoryReportFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceDeviceMemoryReportFeatures ) * > ( pCurrent ), & pContext->features.deviceMemoryReport );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTICS_CONFIG_AVAILABLE

                case StructureTypePhysicalDeviceDiagnosticsConfigFeaturesNVidia:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceDiagnosticsConfigFeaturesNVidia ) * > ( pCurrent ), & pContext->features.diagnosticsConfig );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceDynamicRenderingFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceDynamicRenderingFeatures ) * > ( pCurrent ), & pContext->features.dynamicRendering );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SCISSOR_EXCLUSIVE_AVAILABLE

                case StructureTypePhysicalDeviceExclusiveScissorFeaturesNVidia:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceExclusiveScissorFeaturesNVidia ) * > ( pCurrent ), & pContext->features.exclusiveScissor );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE

                case StructureTypePhysicalDeviceExtendedDynamicStateFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceExtendedDynamicStateFeatures ) * > ( pCurrent ), & pContext->features.extendedDynamicState );
                    break;

                case StructureTypePhysicalDeviceExtendedDynamicState2Features:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceExtendedDynamicState2Features ) * > ( pCurrent ), & pContext->features.extendedDynamicState2 );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_RDMA_AVAILABLE

                case StructureTypePhysicalDeviceExternalMemoryRDMAFeaturesNVidia:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceExternalMemoryRDMAFeaturesNVidia ) * > ( pCurrent ), & pContext->features.externalMemoryRDMA );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

                case StructureTypePhysicalDeviceFragmentDensityMapFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceFragmentDensityMapFeatures ) * > ( pCurrent ), & pContext->features.fragmentDensityMap );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE

                case StructureTypePhysicalDeviceFragmentDensityMap2Features:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceFragmentDensityMap2Features ) * > ( pCurrent ), & pContext->features.fragmentDensityMap2 );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE

                case StructureTypePhysicalDeviceFragmentDensityMapOffsetFeaturesQualcomm:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceFragmentDensityMapOffsetFeaturesQualcomm ) * > ( pCurrent ), & pContext->features.fragmentDensityMapOffset );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADER_BARYCENTRIC_AVAILABLE

                case StructureTypePhysicalDeviceFragmentShaderBarycentricFeaturesNVidia:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceFragmentShaderBarycentricFeaturesNVidia ) * > ( pCurrent ), & pContext->features.fragmentShaderBarycentric );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_SHADER_INTERLOCK_AVAILABLE

                case StructureTypePhysicalDeviceFragmentShaderInterlockFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceFragmentShaderInterlockFeatures ) * > ( pCurrent ), & pContext->features.fragmentShaderInterlock );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE

                case StructureTypePhysicalDeviceFragmentShadingRateEnumsFeaturesNVidia:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceFragmentShadingRateEnumsFeaturesNVidia ) * > ( pCurrent ), & pContext->features.fragmentShadingRateEnums );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE

                case StructureTypePhysicalDeviceFragmentShadingRateFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceFragmentShadingRateFeatures ) * > ( pCurrent ), & pContext->features.fragmentShadingRate );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE

                case StructureTypePhysicalDeviceGlobalPriorityQueryFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceGlobalPriorityQueryFeatures ) * > ( pCurrent ), & pContext->features.globalPriorityQuery );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_ROBUSTNESS_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceImageRobustnessFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceImageRobustnessFeatures ) * > ( pCurrent ), & pContext->features.imageRobustness );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_VIEW_MIN_LOD_AVAILABLE

                case StructureTypePhysicalDeviceImageViewMinLODFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceImageViewMinLODFeatures ) * > ( pCurrent ), & pContext->features.imageViewMinLOD );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INDEX_TYPE_UINT8_AVAILABLE

                case StructureTypePhysicalDeviceIndexTypeUInt8Features:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceIndexTypeUInt8Features ) * > ( pCurrent ), & pContext->features.indexTypeUInt8 );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_INHERITED_VIEWPORT_SCISSOR_AVAILABLE

                case StructureTypePhysicalDeviceInheritedViewportScissorFeaturesNVidia:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceInheritedViewportScissorFeaturesNVidia ) * > ( pCurrent ), & pContext->features.inheritedViewportScissor );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceInlineUniformBlockFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceInlineUniformBlockFeatures ) * > ( pCurrent ), & pContext->features.inlineUniformBlock );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_INVOCATION_MASK_AVAILABLE

                case StructureTypePhysicalDeviceInvocationMaskFeaturesHuawei:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceInvocationMaskFeaturesHuawei ) * > ( pCurrent ), & pContext->features.invocationMask );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE

                case StructureTypePhysicalDeviceLineRasterizationFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceLineRasterizationFeatures ) * > ( pCurrent ), & pContext->features.lineRasterization );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_LINEAR_COLOR_ATTACHMENT_AVAILABLE

                case StructureTypePhysicalDeviceLinearColorAttachmentFeaturesNVidia:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceLinearColorAttachmentFeaturesNVidia ) * > ( pCurrent ), & pContext->features.linearColorAttachment );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceMaintenance4Features:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceMaintenance4Features ) * > ( pCurrent ), & pContext->features.maintenance4 );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_PRIORITY_AVAILABLE

                case StructureTypePhysicalDeviceMemoryPriorityFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceMemoryPriorityFeatures ) * > ( pCurrent ), & pContext->features.memoryPriority );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE

                case StructureTypePhysicalDeviceMeshShaderFeaturesNVidia:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceMeshShaderFeaturesNVidia ) * > ( pCurrent ), & pContext->features.meshShader );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE

                case StructureTypePhysicalDeviceMultiDrawFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceMultiDrawFeatures ) * > ( pCurrent ), & pContext->features.multiDraw );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE

                case StructureTypePhysicalDeviceMutableDescriptorTypeFeaturesValve:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceMutableDescriptorTypeFeaturesValve ) * > ( pCurrent ), & pContext->features.mutableDescriptorType );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PAGEABLE_DEVICE_LOCAL_MEMORY_AVAILABLE

                case StructureTypePhysicalDevicePageableDeviceLocalMemoryFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDevicePageableDeviceLocalMemoryFeatures ) * > ( pCurrent ), & pContext->features.pageableDeviceLocalMemory );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

                case StructureTypePhysicalDevicePerformanceQueryFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDevicePerformanceQueryFeatures ) * > ( pCurrent ), & pContext->features.performanceQuery );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDevicePipelineCreationCacheControlFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDevicePipelineCreationCacheControlFeatures ) * > ( pCurrent ), & pContext->features.pipelineCreationCacheControl );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE

                case StructureTypePhysicalDevicePipelineExecutablePropertiesFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDevicePipelineExecutablePropertiesFeatures ) * > ( pCurrent ), & pContext->features.pipelineExecutableProperties );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE

                case StructureTypePhysicalDevicePortabilitySubsetFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDevicePortabilitySubsetFeatures ) * > ( pCurrent ), & pContext->features.portabilitySubset );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_ID_AVAILABLE

                case StructureTypePhysicalDevicePresentIDFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDevicePresentIDFeatures ) * > ( pCurrent ), & pContext->features.presentID );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_WAIT_AVAILABLE

                case StructureTypePhysicalDevicePresentWaitFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDevicePresentWaitFeatures ) * > ( pCurrent ), & pContext->features.presentWait );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIMITIVE_TOPOLOGY_LIST_RESTART_AVAILABLE

                case StructureTypePhysicalDevicePrimitiveTopologyListRestartFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDevicePrimitiveTopologyListRestartFeatures ) * > ( pCurrent ), & pContext->features.primitiveTopologyListRestart );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDevicePrivateDataFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDevicePrivateDataFeatures ) * > ( pCurrent ), & pContext->features.privateData );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE

                case StructureTypePhysicalDeviceProvokingVertexFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceProvokingVertexFeatures ) * > ( pCurrent ), & pContext->features.provokingVertex );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_RGBA_10_X_6_FORMATS_AVAILABLE

                case StructureTypePhysicalDeviceRGBA10x6FormatsFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceRGBA10x6FormatsFeatures ) * > ( pCurrent ), & pContext->features.rgba10x6FormatsFeaturesExt );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ARM_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_AVAILABLE

                case StructureTypePhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM ) * > ( pCurrent ), & pContext->features.rasterizationOrderAttachmentAccess );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_QUERY_AVAILABLE

                case StructureTypePhysicalDeviceRayQueryFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceRayQueryFeatures ) * > ( pCurrent ), & pContext->features.rayQuery );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE

                case StructureTypePhysicalDeviceRayTracingMotionBlurFeaturesNVidia:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceRayTracingMotionBlurFeaturesNVidia ) * > ( pCurrent ), & pContext->features.rayTracingMotionBlur );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE

                case StructureTypePhysicalDeviceRayTracingPipelineFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceRayTracingPipelineFeatures ) * > ( pCurrent ), & pContext->features.rayTracingPipeline );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_REPRESENTATIVE_FRAGMENT_TEST_AVAILABLE

                case StructureTypePhysicalDeviceRepresentativeFragmentTestFeaturesNVidia:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceRepresentativeFragmentTestFeaturesNVidia ) * > ( pCurrent ), & pContext->features.representativeFragmentText );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE

                case StructureTypePhysicalDeviceRobustnessFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceRobustnessFeatures ) * > ( pCurrent ), & pContext->features.robustness2 );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_AVAILABLE

                case StructureTypePhysicalDeviceShaderAtomicFloatFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceShaderAtomicFloatFeatures ) * > ( pCurrent ), & pContext->features.shaderAtomicFloat );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_2_AVAILABLE

                case StructureTypePhysicalDeviceShaderAtomicFloat2Features:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceShaderAtomicFloat2Features ) * > ( pCurrent ), & pContext->features.shaderAtomicFloat2 );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_CLOCK_AVAILABLE

                case StructureTypePhysicalDeviceShaderClockFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceShaderClockFeatures ) * > ( pCurrent ), & pContext->features.shaderDeviceShaderClock );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_DEMOTE_TO_HELPER_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceShaderDemoteToHelperInvocationFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceShaderDemoteToHelperInvocationFeatures ) * > ( pCurrent ), & pContext->features.shaderDemoteToHelperInvocation );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_IMAGE_ATOMIC_INT64_AVAILABLE

                case StructureTypePhysicalDeviceShaderImageAtomicInt64Features:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceShaderImageAtomicInt64Features ) * > ( pCurrent ), & pContext->features.shaderImageAtomicInt64 );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_IMAGE_FOOTPRINT_AVAILABLE

                case StructureTypePhysicalDeviceShaderImageFootprintFeaturesNVidia:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceShaderImageFootprintFeaturesNVidia ) * > ( pCurrent ), & pContext->features.shaderImageFootprint );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE

                case StructureTypePhysicalDeviceShaderSmBuiltinsFeaturesNVidia:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceShaderSMBuiltinsFeaturesNVidia ) * > ( pCurrent ), & pContext->features.shaderSMBuiltins );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_SUBGROUP_UNIFORM_CONTROL_FLOW_AVAILABLE

                case StructureTypePhysicalDeviceShaderSubgroupUniformControlFlowFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceShaderSubgroupUniformControlFlowFeatures ) * > ( pCurrent ), & pContext->features.shaderSubgroupUniformControlFlow );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_TERMINATE_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceShaderTerminateInvocationFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceShaderTerminateInvocationFeatures ) * > ( pCurrent ), & pContext->features.shaderTerminateInvocation );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE

                case StructureTypePhysicalDeviceShadingRateImageFeaturesNVidia:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceShadingRateImageFeaturesNVidia ) * > ( pCurrent ), & pContext->features.shadingRateImage );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceSubgroupSizeControlFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceSubgroupSizeControlFeatures ) * > ( pCurrent ), & pContext->features.subgroupSizeControl );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE

                case StructureTypePhysicalDeviceSubpassShadingFeaturesHuawei:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceSubpassShadingFeaturesHuawei ) * > ( pCurrent ), & pContext->features.subpassShading );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceSynchronizationFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceSynchronizationFeatures ) * > ( pCurrent ), & pContext->features.synchronization2 );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceTexelBufferAlignmentFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceTexelBufferAlignmentFeatures ) * > ( pCurrent ), & pContext->features.texelBufferAlignment );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXTURE_COMPRESSION_ASTC_HDR_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceTextureCompressionASTCHDRFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceTextureCompressionASTCHDRFeatures ) * > ( pCurrent ), & pContext->features.textureCompressionAstcHdr );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE

                case StructureTypePhysicalDeviceTransformFeedbackFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceTransformFeedbackFeatures ) * > ( pCurrent ), & pContext->features.transformFeedback );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE

                case StructureTypePhysicalDeviceVertexAttributeDivisorFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceVertexAttributeDivisorFeatures ) * > ( pCurrent ), & pContext->features.vertexAttributeDivisor );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_INPUT_DYNAMIC_STATE_AVAILABLE

                case StructureTypePhysicalDeviceVertexInputDynamicStateFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceVertexInputDynamicStateFeatures ) * > ( pCurrent ), & pContext->features.vertexInputDynamicState );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceShaderIntegerDotProductFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceShaderIntegerDotProductFeatures ) * > ( pCurrent ), & pContext->features.shaderIntegerDotProduct );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_SHADER_INTEGER_FUNCTIONS_AVAILABLE

                case StructureTypePhysicalDeviceShaderIntegerFunctionsFeaturesIntel:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceShaderIntegerFunctionsFeaturesIntel ) * > ( pCurrent ), & pContext->features.shaderIntegerFunctions2 );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_AVAILABLE

                case StructureTypePhysicalDeviceWorkgroupMemoryExplicitLayoutFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceWorkgroupMemoryExplicitLayoutFeatures ) * > ( pCurrent ), & pContext->features.workgroupMemoryExplicitLayout );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_2_PLANE_444_FORMATS_AVAILABLE

                case StructureTypePhysicalDeviceYCBCR2Plane444FormatsFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceYCBCR2Plane444FormatsFeatures ) * > ( pCurrent ), & pContext->features.ycbcr2Plane444Formats );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_IMAGE_ARRAYS_AVAILABLE

                case StructureTypePhysicalDeviceYCBCRImageArraysFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceYCBCRImageArraysFeatures ) * > ( pCurrent ), & pContext->features.ycbcrImageArrays );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ZERO_INITIALIZE_WORKGROUP_MEMORY_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceZeroInitializeWorkgroupMemoryFeatures:
                    (void) fromVulkanFormat ( reinterpret_cast < Type ( PhysicalDeviceZeroInitializeWorkgroupMemoryFeatures ) * > ( pCurrent ), & pContext->features.zeroInitializeWorkgroupMemory );
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

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto createChain (
            vulkan :: Type ( PhysicalDeviceDetails )            * details,
            vulkan :: Type ( PhysicalDeviceExtendedProperties ) * extendedProperties,
            vulkan :: Type ( PhysicalDeviceExtendedFeatures )   * extendedFeatures
    ) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( details == nullptr ) {
            return;
        }

#endif

        if ( extendedProperties != nullptr ) {

            auto currentInChain = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( extendedProperties );
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceProperties;

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->vulkan11Properties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceVulkan_1_1_Properties;

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->IDProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceIDProperties;

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->maintenanceProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceMaintenanceProperties;

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->multiviewProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceMultiviewProperties;

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->pointClippingProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDevicePointClippingProperties;

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->protectedMemoryProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceProtectedMemoryProperties;

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->subgroupProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceSubgroupProperties;

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->vulkan12Properties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceVulkan_1_2_Properties;

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->driverProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceDriverProperties;

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->depthStencilResolveProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceDepthStencilResolveProperties;

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->descriptorIndexingProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceDescriptorIndexingProperties;

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->deviceFloatControlsProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceFloatControlsProperties;

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->samplerFilterMinmaxProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceSamplerFilterMinMaxProperties;

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->timelineSemaphoreProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceTimelineSemaphoreProperties;

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->vulkan13Properties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceVulkan_1_3_Properties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PCI_BUS_INFO_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->pciBusInfoProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDevicePCIBusInfoProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PHYSICAL_DEVICE_DRM_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->DRMProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceDRMProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->accelerationStructureProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceAccelerationStructureProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->blendOperationAdvancedProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceBlendOperationAdvancedProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONSERVATIVE_RASTERIZATION_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->conservativeRasterizationProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceConservativeRasterizationProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->cooperativeMatrixPropertiesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceCooperativeMatrixPropertiesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->customBorderColorProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceCustomBorderColorProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->deviceGeneratedCommandsProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceDeviceGeneratedCommandsPropertiesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISCARD_RECTANGLES_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->externalMemoryHostProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceExternalMemoryHostProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->fragmentDensityMap2Properties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceFragmentDensityMap2Properties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->fragmentDensityMapOffsetPropertiesQualcomm ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceFragmentDensityMapOffsetPropertiesQualcomm;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->fragmentDensityMapProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceFragmentDensityMapProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->fragmentShadingRateEnumsPropertiesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceFragmentShadingRateEnumsPropertiesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->fragmentShadingRateProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceFragmentShadingRateProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->inlineUniformBlockProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceInlineUniformBlockProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->lineRasterizationProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceLineRasterizationProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->maintenance4Properties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceMaintenance4Properties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->meshShaderPropertiesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceMeshShaderPropertiesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->multiDrawProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceMultiDrawProperties;

#endif

#if ( __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE ) && __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->multiviewPerViewAttributesPropertiesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceMultiviewPerViewAttributesPropertiesNVidiaExperimental;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->performanceQueryProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDevicePerformanceQueryProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->portabilitySubsetProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDevicePortabilitySubsetProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->provokingVertexProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceProvokingVertexProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PUSH_DESCRIPTOR_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->pushDescriptorProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDevicePushDescriptorProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->rayTracingPipelineProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceRayTracingPipelineProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->robustnessProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceRobustnessProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->sampleLocationsProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceSampleLocationsProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->shaderCorePropertiesAMD ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceShaderCorePropertiesAMD;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_2_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->shaderCoreProperties2AMD ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceShaderCoreProperties2AMD;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->shaderSmBuiltinsPropertiesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceShaderSmBuiltinsPropertiesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->shadingRateImagePropertiesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceShadingRateImagePropertiesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->subgroupSizeControlProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceSubgroupSizeControlProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->subpassShadingPropertiesHuawei ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceSubpassShadingPropertiesHuawei;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->texelBufferAlignmentProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceTexelBufferAlignmentProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->transformFeedbackProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceTransformFeedbackProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->vertexAttributeDivisorProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceVertexAttributeDivisorProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->rayTracingPropertiesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceRayTracingPropertiesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->shaderIntegerDotProductProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceShaderIntegerDotProductProperties;

#endif

            currentInChain->pNext = nullptr;

        }


        if ( extendedFeatures != nullptr ) {

            auto currentInChain = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( extendedFeatures );
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceFeatures;


#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->vulkan11Features ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceVulkan_1_1_Features;

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->_16BitStorageFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDevice16BitStorageFeatures;

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->multiviewFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceMultiviewFeatures;

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->protectedMemoryFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceProtectedMemoryFeatures;

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->samplerYCBCRConversionFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceSamplerYCBCRConversionFeatures;

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->shaderDrawParametersFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceShaderDrawParametersFeatures;

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->variablePointersFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceVariablePointersFeatures;

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->vulkan12Features ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceVulkan_1_2_Features;

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->_8BitStorageFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDevice8BitStorageFeatures;

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->bufferDeviceAddressFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceBufferDeviceAddressFeatures;

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->descriptorIndexingFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceDescriptorIndexingFeatures;

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->hostQueryResetFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceHostQueryResetFeatures;

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->imagelessFramebufferFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceImagelessFrameBufferFeatures;

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->scalarBlockLayoutFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceScalarBlockLayoutFeatures;

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->separateDepthStencilLayoutsFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceSeparateDepthStencilLayoutsFeatures;

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->shaderAtomicInt64Features ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceShaderAtomicInt64Features;

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->shaderFloat16Int8Features ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceShaderFloat16Int8Features;

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->shaderSubgroupExtendedTypesFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceShaderSubgroupExtendedTypesFeatures;

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->timelineSemaphoreFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceTimelineSemaphoreFeatures;

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->uniformBufferStandardLayoutFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceUniformBufferStandardLayoutFeatures;

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->vulkanMemoryModelFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceVulkanMemoryModelFeatures;

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->vulkan13Features ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceVulkan_1_3_Features;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_4444_FORMATS_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->_4444FormatsFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDevice4444FormatsFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ASTC_DECODE_MODE_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->ASTCDecodeFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceASTCDecodeFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->accelerationStructureFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceAccelerationStructureFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->blendOperationAdvancedFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceBlendOperationAdvancedFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BORDER_COLOR_SWIZZLE_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->borderColorSwizzleFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceBorderColorSwizzleFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_DEVICE_COHERENT_MEMORY_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->coherentMemoryFeaturesAMD ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceCoherentMemoryFeaturesAMD;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_COLOR_WRITE_ENABLE_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->colorWriteEnabledFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceColorWriteEnableFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COMPUTE_SHADER_DERIVATIVES_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->computeShaderDerivativesFeaturesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceComputeShaderDerivativesFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->conditionalRenderingFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceConditionalRenderingFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->cooperativeMatrixFeaturesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceCooperativeMatrixFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CORNER_SAMPLED_IMAGE_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->cornerSampledImageFeaturesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceCornerSampledImageFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COVERAGE_REDUCTION_MODE_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->coverageReductionModeFeaturesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceCoverageReductionModeFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->customBorderColorFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceCustomBorderColorFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_IMAGE_ALIASING_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->dedicatedAllocationImageAliasingFeaturesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceDedicatedAllocationImageAliasingFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_CONTROL_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->depthClipControlFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceDepthClipControlFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_ENABLE_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->depthClipEnableFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceDepthClipEnableFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->deviceGeneratedCommandsFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceDeviceGeneratedCommandsFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEVICE_MEMORY_REPORT_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->deviceMemoryReportFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceDeviceMemoryReportFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTICS_CONFIG_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->diagnosticsConfigFeaturesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceDiagnosticsConfigFeaturesNVidia;

#endif

#if ( __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE ) || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->dynamicRenderingFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceDynamicRenderingFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SCISSOR_EXCLUSIVE_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->exclusiveScissorFeaturesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceExclusiveScissorFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->extendedDynamicStateFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceExtendedDynamicStateFeatures;

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->extendedDynamicState2Features ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceExtendedDynamicState2Features;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_RDMA_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->externalMemoryRDMAFeaturesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceExternalMemoryRDMAFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->fragmentDensityMapFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceFragmentDensityMapFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->fragmentDensityMap2Features ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceFragmentDensityMap2Features;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->fragmentDensityMapOffsetFeaturesQualcomm ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceFragmentDensityMapOffsetFeaturesQualcomm;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADER_BARYCENTRIC_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->fragmentShaderBarycentricFeaturesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceFragmentShaderBarycentricFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_SHADER_INTERLOCK_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->fragmentShaderInterlockFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceFragmentShaderInterlockFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->fragmentShadingRateEnumsFeaturesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceFragmentShadingRateEnumsFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->fragmentShadingRateFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceFragmentShadingRateFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->globalPriorityQueryFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceGlobalPriorityQueryFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_ROBUSTNESS_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->imageRobustnessFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceImageRobustnessFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_VIEW_MIN_LOD_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->imageViewMinLODFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceImageViewMinLODFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INDEX_TYPE_UINT8_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->indexTypeUInt8Features ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceIndexTypeUInt8Features;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_INHERITED_VIEWPORT_SCISSOR_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->inheritedViewportScissorFeaturesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceInheritedViewportScissorFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->inlineUniformBlockFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceInlineUniformBlockFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_INVOCATION_MASK_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->invocationMaskFeaturesHuawei ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceInvocationMaskFeaturesHuawei;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->lineRasterizationFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceLineRasterizationFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_LINEAR_COLOR_ATTACHMENT_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->linearColorAttachmentFeaturesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceLinearColorAttachmentFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->maintenance4Features ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceMaintenance4Features;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_PRIORITY_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->memoryPriorityFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceMemoryPriorityFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->meshShaderFeaturesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceMeshShaderFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->multiDrawFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceMultiDrawFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->mutableDescriptorTypeFeaturesValve ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceMutableDescriptorTypeFeaturesValve;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PAGEABLE_DEVICE_LOCAL_MEMORY_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->pageableDeviceLocalMemoryFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDevicePageableDeviceLocalMemoryFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->performanceQueryFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDevicePerformanceQueryFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->pipelineCreationCacheControlFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDevicePipelineCreationCacheControlFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->pipelineExecutablePropertiesFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDevicePipelineExecutablePropertiesFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->portabilitySubsetFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDevicePortabilitySubsetFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_ID_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->presentIDFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDevicePresentIDFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_WAIT_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->presentWaitFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDevicePresentWaitFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIMITIVE_TOPOLOGY_LIST_RESTART_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->primitiveTopologyListRestartFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDevicePrimitiveTopologyListRestartFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->privateDataFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDevicePrivateDataFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->provokingVertexFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceProvokingVertexFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_RGBA_10_X_6_FORMATS_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->RGBA10x6FormatsFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceRGBA10x6FormatsFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ARM_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->rasterizationOrderAttachmentAccessFeaturesARM ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_QUERY_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->rayQueryFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceRayQueryFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->rayTracingMotionBlurFeaturesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceRayTracingMotionBlurFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->rayTracingPipelineFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceRayTracingPipelineFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_REPRESENTATIVE_FRAGMENT_TEST_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->representativeFragmentTestFeaturesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceRepresentativeFragmentTestFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->robustnessFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceRobustnessFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->shaderAtomicFloatFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceShaderAtomicFloatFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_2_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->shaderAtomicFloat2Features ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceShaderAtomicFloat2Features;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_CLOCK_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->shaderClockFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceShaderClockFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_DEMOTE_TO_HELPER_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->shaderDemoteToHelperInvocationFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceShaderDemoteToHelperInvocationFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_IMAGE_ATOMIC_INT64_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->shaderImageAtomicInt64Features ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceShaderImageAtomicInt64Features;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_IMAGE_FOOTPRINT_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->shaderImageFootprintFeaturesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceShaderImageFootprintFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->shaderSmBuiltinsFeaturesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceShaderSmBuiltinsFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_SUBGROUP_UNIFORM_CONTROL_FLOW_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->shaderSubgroupUniformControlFlowFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceShaderSubgroupUniformControlFlowFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_TERMINATE_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->shaderTerminateInvocationFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceShaderTerminateInvocationFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->shadingRateImageFeaturesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceShadingRateImageFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->subgroupSizeControlFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceSubgroupSizeControlFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->subpassShadingFeaturesHuawei ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceSubpassShadingFeaturesHuawei;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->synchronizationFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceSynchronizationFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->texelBufferAlignmentFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceTexelBufferAlignmentFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXTURE_COMPRESSION_ASTC_HDR_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->textureCompressionASTCHDRFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceTextureCompressionASTCHDRFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->transformFeedbackFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceTransformFeedbackFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->vertexAttributeDivisorFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceVertexAttributeDivisorFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_INPUT_DYNAMIC_STATE_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->vertexInputDynamicStateFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceVertexInputDynamicStateFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->shaderIntegerDotProductFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceShaderIntegerDotProductFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_SHADER_INTEGER_FUNCTIONS_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->shaderIntegerFunctionsFeaturesIntel ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceShaderIntegerFunctionsFeaturesIntel;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->workgroupMemoryExplicitLayoutFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceWorkgroupMemoryExplicitLayoutFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_2_PLANE_444_FORMATS_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->YCBCR2Plane444FormatFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceYCBCR2Plane444FormatsFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_IMAGE_ARRAYS_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->YCBCRImageArraysFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceYCBCRImageArraysFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ZERO_INITIALIZE_WORKGROUP_MEMORY_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & details->zeroInitializeWorkgroupMemoryFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceZeroInitializeWorkgroupMemoryFeatures;

#endif

            currentInChain->pNext = nullptr;

        }
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto fromVulkanFormat (
            Type ( QueueFamilyProperties )        * pDestination,
            VkQueueFamilyProperties         const * pSource
    ) noexcept -> Type ( QueueFamilyProperties ) * {

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .queueFlags                     = pSource->queueFlags,
                .queueCount                     = pSource->queueCount,
                .timestampValidBits             = pSource->timestampValidBits,
                .minImageTransferGranularity    = pSource->minImageTransferGranularity
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto prepareContext (
            GetPhysicalDeviceQueueFamilyPropertiesContext         * pContext,
            cds :: uint32                                           count,
            Type ( QueueFamilyExtendedProperties )          const * pProperties
    ) noexcept -> VkQueueFamilyProperties2 * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pProperties == nullptr ) {
            return nullptr;
        }

#endif

        for ( cds :: uint32 i = 0U; i < count; ++i ) {
            pContext->properties2[i].sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2;

            auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pProperties[i].pNext );
            auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( & pContext->properties2[i] );

            while ( pCurrent != nullptr ) {

                switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTIC_CHECKPOINTS_AVAILABLE

                    case StructureTypeQueueFamilyCheckpointPropertiesNVidia:
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->checkpoints[i] );
                        break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE

                    case StructureTypeQueueFamilyGlobalPriorityProperties:
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->globalPriorities[i] );
                        break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE

                    case StructureTypeQueueFamilyQueryResultStatusProperties:
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->queryResultStatuses[i] );
                        break;

                    case StructureTypeVideoQueueFamilyProperties:
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > ( & pContext->videoQueues[i] );
                        break;

#endif

                    default:
                        break;
                }

                if ( pCurrentVk->pNext != nullptr ) {
                    pCurrentVk          = pCurrentVk->pNext;
                    pCurrentVk->sType   = static_cast < VkStructureType > ( pCurrent->structureType );
                }

                pCurrent = pCurrent->pNext;
            }

            pCurrentVk->pNext = nullptr;
        }

        return & pContext->properties2[0];
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto fromVulkanFormat (
            Type ( QueueFamilyExtendedProperties )        * pDestination,
            VkQueueFamilyProperties2                const * pSource
    ) noexcept -> Type ( QueueFamilyExtendedProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypeQueueFamilyProperties;
        pDestination->pNext         = nullptr;

        (void) fromVulkanFormat ( & pDestination->properties, & pSource->queueFamilyProperties );

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTIC_CHECKPOINTS_AVAILABLE
    auto fromVulkanFormat (
            Type ( QueueFamilyCheckpointPropertiesNVidia )        * pDestination,
            VkQueueFamilyCheckpointPropertiesNV             const * pSource
    ) noexcept -> Type ( QueueFamilyCheckpointPropertiesNVidia ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .structureType                  = StructureTypeQueueFamilyCheckpointPropertiesNVidia,
                .pNext                          = nullptr,
                .checkpointExecutionStageMask   = pSource->checkpointExecutionStageMask
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE
    auto fromVulkanFormat (
            Type ( QueueFamilyGlobalPriorityProperties )        * pDestination,
            VkQueueFamilyGlobalPriorityPropertiesEXT      const * pSource
    ) noexcept -> Type ( QueueFamilyGlobalPriorityProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypeQueueFamilyGlobalPriorityProperties;
        pDestination->pNext         = nullptr;
        pDestination->priorityCount = pSource->priorityCount;

        for ( cds :: uint32 i = 0U; i < pDestination->priorityCount; ++ i ) {
            pDestination->priorities[i] = static_cast < Type ( QueueGlobalPriority ) > ( pSource->priorities[i] );
        }

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE
    auto fromVulkanFormat (
            Type ( QueueFamilyQueryResultStatusProperties )         * pDestination,
            VkQueueFamilyQueryResultStatusProperties2KHR      const * pSource
    ) noexcept -> Type ( QueueFamilyQueryResultStatusProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypeQueueFamilyQueryResultStatusProperties;
        pDestination->pNext         = nullptr;
        pDestination->supported     = pSource->supported;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE
    auto fromVulkanFormat (
            Type ( VideoQueueFamilyProperties )         * pDestination,
            VkVideoQueueFamilyProperties2KHR      const * pSource
    ) noexcept -> Type ( VideoQueueFamilyProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType         = StructureTypeVideoQueueFamilyProperties;
        pDestination->pNext                 = nullptr;
        pDestination->videoCodecOperations  = pSource->videoCodecOperations;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto extractContext (
            cds :: uint32                                         count,
            Type ( QueueFamilyExtendedProperties )              * pProperties,
            GetPhysicalDeviceQueueFamilyPropertiesContext const * pContext
    ) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pProperties == nullptr || pContext == nullptr ) {
            return;
        }

#endif

        for ( cds :: uint32 i = 0U; i < count; ++ i ) {

            auto pCurrent = reinterpret_cast < Type (GenericOutStructure) * > ( & pProperties[i] );
            while (pCurrent != nullptr) {

                auto pNext = pCurrent->pNext;
                switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

                    case StructureTypeQueueFamilyProperties:
                        (void) fromVulkanFormat ( reinterpret_cast < Type ( QueueFamilyExtendedProperties ) * > ( pCurrent ), & pContext->properties2[i] );
                        break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTIC_CHECKPOINTS_AVAILABLE

                    case StructureTypeQueueFamilyCheckpointPropertiesNVidia:
                        (void) fromVulkanFormat ( reinterpret_cast < Type ( QueueFamilyCheckpointPropertiesNVidia ) * > ( pCurrent ), & pContext->checkpoints[i] );
                        break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE

                    case StructureTypeQueueFamilyGlobalPriorityProperties:
                        (void) fromVulkanFormat ( reinterpret_cast < Type ( QueueFamilyGlobalPriorityProperties ) * > ( pCurrent ), & pContext->globalPriorities[i] );
                        break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE

                    case StructureTypeQueueFamilyQueryResultStatusProperties:
                        (void) fromVulkanFormat ( reinterpret_cast < Type ( QueueFamilyQueryResultStatusProperties ) * > ( pCurrent ), & pContext->queryResultStatuses[i] );
                        break;

                    case StructureTypeVideoQueueFamilyProperties:
                        (void) fromVulkanFormat ( reinterpret_cast < Type ( VideoQueueFamilyProperties ) * > ( pCurrent ), & pContext->videoQueues[i] );
                        break;

#endif

                    default:
                        break;
                }

                pCurrent->pNext = pNext;
                pCurrent        = pCurrent->pNext;
            }
        }
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto createChain (
            cds :: uint32                                       queueFamilyCount,
            vulkan :: Type ( QueueFamilyDetails )             * pDetails,
            vulkan :: Type ( QueueFamilyExtendedProperties )  * pExtendedProperties
    ) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDetails == nullptr || pExtendedProperties == nullptr ) {
            return;
        }

#endif

        for ( cds :: uint32 i = 0U; i < queueFamilyCount; ++ i ) {

            auto currentInChain = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & pExtendedProperties[i] );
            currentInChain->structureType = vulkan :: StructureTypeQueueFamilyProperties;

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTIC_CHECKPOINTS_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & pDetails[i].checkpointPropertiesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypeQueueFamilyCheckpointPropertiesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & pDetails[i].globalPriorityProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypeQueueFamilyGlobalPriorityProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & pDetails[i].queryResultStatusProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypeQueueFamilyQueryResultStatusProperties;

            currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: Type ( GenericOutStructure ) * > ( & pDetails[i].videoProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
            currentInChain->structureType = vulkan :: StructureTypeVideoQueueFamilyProperties;

#endif

            currentInChain->pNext = nullptr;

        }
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto toVulkanFormat (
            VkDeviceQueueInfo2                * pDestination,
            Type ( DeviceQueueInfo )    const * pSource
    ) noexcept -> VkDeviceQueueInfo2 * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType              = VK_STRUCTURE_TYPE_DEVICE_QUEUE_INFO_2,
                .pNext              = nullptr,
                .flags              = pSource->flags,
                .queueFamilyIndex   = pSource->queueFamilyIndex,
                .queueIndex         = pSource->queueIndex
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE
    auto fromVulkanFormat (
            Type ( SurfaceCapabilities )      * pDestination,
            VkSurfaceCapabilitiesKHR    const * pSource
    ) noexcept -> Type ( SurfaceCapabilities ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .minImageCount              = pSource->minImageCount,
                .maxImageCount              = pSource->maxImageCount,
                .currentExtent              = {
                        .width                      = pSource->currentExtent.width,
                        .height                     = pSource->currentExtent.height
                },
                .minImageExtent             = {
                        .width                      = pSource->minImageExtent.width,
                        .height                     = pSource->minImageExtent.height
                },
                .maxImageExtent             = {
                        .width                      = pSource->maxImageExtent.width,
                        .height                     = pSource->maxImageExtent.height
                },
                .maxImageArrayLayers        = pSource->maxImageArrayLayers,
                .supportedTransforms        = pSource->supportedTransforms,
                .currentTransform           = static_cast < Type ( SurfaceTransformFlag ) > ( pSource->currentTransform ),
                .supportedCompositeAlpha    = pSource->supportedCompositeAlpha,
                .supportedUsageFlags        = pSource->supportedUsageFlags
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE
    auto fromVulkanFormat (
            Type ( SurfaceFormat )      * pDestination,
            VkSurfaceFormatKHR    const * pSource
    ) noexcept -> Type ( SurfaceFormat ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .format     = static_cast < Type ( Format ) > ( pSource->format ),
                .colorSpace = static_cast < Type ( ColorSpace ) > ( pSource->colorSpace )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISPLAY_SURFACE_COUNTER_AVAILABLE
    auto fromVulkanFormat (
            Type ( SurfaceCapabilities2 )      * pDestination,
            VkSurfaceCapabilities2EXT    const * pSource
    ) noexcept -> Type ( SurfaceCapabilities2 ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .structureType              = StructureTypeSurfaceCapabilities2,
                .pNext                      = nullptr,
                .minImageCount              = pSource->minImageCount,
                .maxImageCount              = pSource->maxImageCount,
                .currentExtent              = {
                        .width                      = pSource->currentExtent.width,
                        .height                     = pSource->currentExtent.height
                },
                .minImageExtent             = {
                        .width                      = pSource->minImageExtent.width,
                        .height                     = pSource->minImageExtent.height
                },
                .maxImageExtent             = {
                        .width                      = pSource->maxImageExtent.width,
                        .height                     = pSource->maxImageExtent.height
                },
                .maxImageArrayLayers        = pSource->maxImageArrayLayers,
                .supportedTransforms        = pSource->supportedTransforms,
                .currentTransform           = static_cast < Type ( SurfaceTransformFlag ) > ( pSource->currentTransform ),
                .supportedCompositeAlpha    = pSource->supportedCompositeAlpha,
                .supportedUsageFlags        = pSource->supportedUsageFlags
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_GET_SURFACE_CAPABILITIES_AVAILABLE
    auto fromVulkanFormat (
            Type ( SurfaceFormat2 )      * pDestination,
            VkSurfaceFormat2KHR    const * pSource
    ) noexcept -> Type ( SurfaceFormat2 ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType     = vulkan :: StructureTypeSurfaceFormat;
        pDestination->pNext             = nullptr;
        fromVulkanFormat ( & pDestination->surfaceFormat, & pSource->surfaceFormat );

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FULL_SCREEN_EXCLUSIVE_AVAILABLE
    auto toVulkanFormat (
        VkSurfaceFullScreenExclusiveInfoEXT           * pDestination,
        Type ( SurfaceFullScreenExclusiveInfo ) const * pSource
    ) noexcept -> VkSurfaceFullScreenExclusiveInfoEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return nullptr;
    }

#endif

        * pDestination = {
            .sType                  = VK_STRUCTURE_TYPE_SURFACE_FULL_SCREEN_EXCLUSIVE_INFO_EXT,
            .pNext                  = nullptr,
            .fullScreenExclusive    = static_cast < VkFullScreenExclusiveEXT > ( pSource->fullScreenExclusive )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_GET_SURFACE_CAPABILITIES_AVAILABLE
    auto prepareContext (
            GetSurfaceContext                         * pContext,
            Type ( PhysicalDeviceSurfaceInfo )  const * pSource
    ) noexcept -> VkPhysicalDeviceSurfaceInfo2KHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pContext->surfaceInfo2.sType    = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SURFACE_INFO_2_KHR;
        pContext->surfaceInfo2.surface  = pSource->surface;

        auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pNext );
        auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( & pContext->surfaceInfo2 );

        while ( pCurrent != nullptr ) {

            switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_EXTENSION_FULL_SCREEN_EXCLUSIVE_AVAILABLE

                case StructureTypeSurfaceFullScreenExclusiveInfo:
                    pCurrentVk->pNext = toVulkanFormat (
                            & pContext->fullScreenExclusive,
                            pCurrent
                    );
                    break;

#endif

                default:
                    break;
            }

            if ( pCurrentVk->pNext != nullptr ) {
                pCurrentVk = pCurrentVk->pNext;
            }

            pCurrent = pCurrent->pNext;
        }

        pCurrentVk->pNext = nullptr;

        return & pContext->surfaceInfo2;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE
    auto toVulkanFormat (
            VkSwapchainCreateInfoKHR              * pDestination,
            Type ( SwapChainCreateInfo )    const * pSource
    ) noexcept -> VkSwapchainCreateInfoKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
                .pNext                  = nullptr,
                .flags                  = pSource->flags,
                .surface                = pSource->surface,
                .minImageCount          = pSource->minImageCount,
                .imageFormat            = static_cast < VkFormat > ( pSource->imageFormat ),
                .imageColorSpace        = static_cast < VkColorSpaceKHR > ( pSource->imageColorSpace ),
                .imageExtent            = {
                        .width                  = pSource->imageExtent.width,
                        .height                 = pSource->imageExtent.height
                },
                .imageArrayLayers       = pSource->imageArrayLayers,
                .imageUsage             = pSource->imageUsage,
                .imageSharingMode       = static_cast < VkSharingMode > ( pSource->imageSharingMode ),
                .queueFamilyIndexCount  = pSource->queueFamilyIndexCount,
                .pQueueFamilyIndices    = pSource->pQueueFamilyIndices,
                .preTransform           = static_cast < VkSurfaceTransformFlagBitsKHR > ( pSource->preTransform ),
                .compositeAlpha         = static_cast < VkCompositeAlphaFlagBitsKHR > ( pSource->compositeAlpha ),
                .presentMode            = static_cast < VkPresentModeKHR > ( pSource->presentMode ),
                .clipped                = pSource->clipped,
                .oldSwapchain           = pSource->oldSwapChain
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    auto toVulkanFormat (
            VkImageFormatListCreateInfo                 * pDestination,
            Type ( ImageFormatListCreateInfo )    const * pSource
    ) noexcept -> VkImageFormatListCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_IMAGE_FORMAT_LIST_CREATE_INFO,
                .pNext                  = nullptr,
                .viewFormatCount        = pSource->viewFormatCount,
                .pViewFormats           = pDestination->pViewFormats
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WIN32_SURFACE_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_FULL_SCREEN_EXCLUSIVE_AVAILABLE
    auto toVulkanFormat (
            VkSurfaceFullScreenExclusiveWin32InfoEXT              * pDestination,
            Type ( SurfaceFullScreenExclusiveWin32Info )    const * pSource
    ) noexcept -> VkSurfaceFullScreenExclusiveWin32InfoEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_SURFACE_FULL_SCREEN_EXCLUSIVE_WIN32_INFO_EXT,
                .pNext                  = nullptr,
                .hmonitor               = pSource->monitorHandle
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE
    auto prepareContext (
            CreateSwapChainContext                * pContext,
            Type ( SwapChainCreateInfo )    const * pSource
    ) noexcept -> VkSwapchainCreateInfoKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pNext );
        auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->createInfo, pSource ) );

        while ( pCurrent != nullptr ) {

            switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

                case StructureTypeImageFormatListCreateInfo: {

                    auto pFormatListCreateInfo = reinterpret_cast < Type ( ImageFormatListCreateInfo ) const * > ( pCurrent );
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                & pContext->formatListCreateInfo,
                                pFormatListCreateInfo
                            )
                    );

                    pContext->formatListCreateInfo.pViewFormats = & pContext->viewFormats [0];

                    if ( pContext->formatListCreateInfo.viewFormatCount > engine :: vulkan :: config :: viewFormatCount ) {
                        __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                                "config :: viewFormatCount = %d. Minimum Required = %d",
                                engine :: vulkan :: config :: viewFormatCount,
                                pContext->formatListCreateInfo.viewFormatCount
                        ))

                        pContext->formatListCreateInfo.viewFormatCount = engine :: vulkan :: config :: viewFormatCount;
                    }

                    for ( cds :: uint32 i = 0U; i < pContext->formatListCreateInfo.viewFormatCount; ++ i ) {
                        pContext->viewFormats[i] = static_cast < VkFormat > ( pFormatListCreateInfo->pViewFormats[i] );
                    }

                    break;
                }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WIN32_SURFACE_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_FULL_SCREEN_EXCLUSIVE_AVAILABLE

                case StructureTypeSurfaceFullScreenExclusiveWin32Info:
                    pCurrentVk->pNext = toVulkanFormat (
                            & pContext->fullScreenExclusiveWin32Info,
                            reinterpret_cast < Type ( SurfaceFullScreenExclusiveWin32Info ) const * > ( pCurrent )
                    );
                    break;

#endif

                default:
                    break;
            }

            pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
            pCurrent    = pCurrent->pNext;
        }

        pCurrentVk->pNext = nullptr;

        return & pContext->createInfo;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkImageViewCreateInfo                 * pDestination,
            Type ( ImageViewCreateInfo )    const * pSource
    ) noexcept -> VkImageViewCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType              = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
                .pNext              = nullptr,
                .flags              = pSource->flags,
                .image              = pSource->image,
                .viewType           = static_cast < VkImageViewType > ( pSource->viewType ),
                .format             = static_cast < VkFormat > ( pSource->format ),
                .components         = {
                        .r                  = static_cast < VkComponentSwizzle > ( pSource->components.r ),
                        .g                  = static_cast < VkComponentSwizzle > ( pSource->components.g ),
                        .b                  = static_cast < VkComponentSwizzle > ( pSource->components.b ),
                        .a                  = static_cast < VkComponentSwizzle > ( pSource->components.a )
                },
                .subresourceRange   = {
                        .aspectMask         = pSource->subresourceRange.aspectMask,
                        .baseMipLevel       = pSource->subresourceRange.baseMipLevel,
                        .levelCount         = pSource->subresourceRange.levelCount,
                        .baseArrayLayer     = pSource->subresourceRange.baseArrayLayer,
                        .layerCount         = pSource->subresourceRange.layerCount
                }
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto toVulkanFormat (
            VkImageViewUsageCreateInfo                 * pDestination,
            Type ( ImageViewUsageCreateInfo )    const * pSource
    ) noexcept -> VkImageViewUsageCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType              = VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO,
                .pNext              = nullptr,
                .usage              = pSource->usage
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto toVulkanFormat (
            VkSamplerYcbcrConversionInfo                 * pDestination,
            Type ( SamplerYCBCRConversionInfo )    const * pSource
    ) noexcept -> VkSamplerYcbcrConversionInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType              = VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_INFO,
                .pNext              = nullptr,
                .conversion         = pSource->conversion
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto prepareContext (
            CreateImageViewContext                * pContext,
            Type ( ImageViewCreateInfo )    const * pSource
    ) noexcept -> VkImageViewCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pNext );
        auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->createInfo, pSource ) );

        while ( pCurrent != nullptr ) {

            switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

                case StructureTypeImageViewUsageCreateInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->usageCreateInfo,
                                    reinterpret_cast < Type ( ImageViewUsageCreateInfo ) const * > ( pCurrent )
                            )
                    );
                    break;

                case StructureTypeSamplerYCBCRConversionInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->samplerYcbcrConversionInfo,
                                    reinterpret_cast < Type ( SamplerYCBCRConversionInfo ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

                default:
                    break;
            }

            pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
            pCurrent    = pCurrent->pNext;
        }

        pCurrentVk->pNext = nullptr;
        return & pContext->createInfo;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkCommandPoolCreateInfo                 * pDestination,
            Type ( CommandPoolCreateInfo )    const * pSource
    ) noexcept -> VkCommandPoolCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType              = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
                .pNext              = nullptr,
                .flags              = pSource->flags,
                .queueFamilyIndex   = pSource->queueFamilyIndex
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkCommandBufferAllocateInfo                 * pDestination,
            Type ( CommandBufferAllocateInfo )    const * pSource
    ) noexcept -> VkCommandBufferAllocateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
                .pNext              = nullptr,
                .commandPool        = pSource->commandPool,
                .level              = static_cast < VkCommandBufferLevel > ( pSource->level ),
                .commandBufferCount = pSource->commandBufferCount
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkCommandBufferBeginInfo                 * pDestination,
            Type ( CommandBufferBeginInfo )    const * pSource
    ) noexcept -> VkCommandBufferBeginInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO,
                .pNext              = nullptr,
                .flags              = pSource->flags,
                .pInheritanceInfo   = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkCommandBufferInheritanceInfo                 * pDestination,
            Type ( CommandBufferInheritanceInfo )    const * pSource
    ) noexcept -> VkCommandBufferInheritanceInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO,
                .pNext                  = nullptr,
                .renderPass             = pSource->renderPass,
                .subpass                = pSource->subpass,
                .framebuffer            = pSource->frameBuffer,
                .occlusionQueryEnable   = pSource->occlusionQueryEnable,
                .queryFlags             = pSource->queryFlags,
                .pipelineStatistics     = pSource->pipelineStatistics
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto toVulkanFormat (
            VkDeviceGroupCommandBufferBeginInfo                 * pDestination,
            Type ( DeviceGroupCommandBufferBeginInfo )    const * pSource
    ) noexcept -> VkDeviceGroupCommandBufferBeginInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_DEVICE_GROUP_COMMAND_BUFFER_BEGIN_INFO,
                .pNext                  = nullptr,
                .deviceMask             = pSource->deviceMask
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    auto toVulkanFormat (
            VkCommandBufferInheritanceRenderingInfo_t               * pDestination,
            Type ( CommandBufferInheritanceRenderingInfo )    const * pSource
    ) noexcept -> VkCommandBufferInheritanceRenderingInfo_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE
                .sType                      = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_RENDERING_INFO_KHR,
#elif __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
                .sType                      = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_RENDERING_INFO,
#endif
                .pNext                      = nullptr,
                .flags                      = pSource->flags,
                .viewMask                   = pSource->viewMask,
                .colorAttachmentCount       = pSource->colorAttachmentCount,
                .pColorAttachmentFormats    = nullptr,
                .depthAttachmentFormat      = static_cast < VkFormat > ( pSource->depthAttachmentFormat ),
                .stencilAttachmentFormat    = static_cast < VkFormat > ( pSource->stencilAttachmentFormat ),
                .rasterizationSamples       = static_cast < VkSampleCountFlagBits > ( pSource->rasterizationSamples )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_AMD_MIXED_ATTACHMENT_SAMPLES_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAMEBUFFER_MIXED_SAMPLES_AVAILABLE
    auto toVulkanFormat (
            VkAttachmentSampleCountInfoAMD                           * pDestination,
            vulkan :: hidden :: __AttachmentSampleCountInfo    const * pSource
    ) noexcept -> VkAttachmentSampleCountInfoAMD * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                          = VK_STRUCTURE_TYPE_ATTACHMENT_SAMPLE_COUNT_INFO_AMD,
                .pNext                          = nullptr,
                .colorAttachmentCount           = pSource->colorAttachmentCount,
                .pColorAttachmentSamples        = nullptr,
                .depthStencilAttachmentSamples  = static_cast < VkSampleCountFlagBits > ( pSource->depthStencilAttachmentSamples )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE
    auto toVulkanFormat (
            VkMultiviewPerViewAttributesInfoNVX                   * pDestination,
            Type ( MultiviewPerViewAttributesInfoNVidia )   const * pSource
    ) noexcept -> VkMultiviewPerViewAttributesInfoNVX * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                          = VK_STRUCTURE_TYPE_ATTACHMENT_SAMPLE_COUNT_INFO_AMD,
                .pNext                          = nullptr,
                .perViewAttributes              = pSource->perViewAttributes,
                .perViewAttributesPositionXOnly = pSource->perViewAttributesPositionXOnly
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE
    auto toVulkanFormat (
            VkCommandBufferInheritanceConditionalRenderingInfoEXT             * pDestination,
            Type ( CommandBufferInheritanceConditionalRenderingInfo )   const * pSource
    ) noexcept -> VkCommandBufferInheritanceConditionalRenderingInfoEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                          = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_CONDITIONAL_RENDERING_INFO_EXT,
                .pNext                          = nullptr,
                .conditionalRenderingEnable     = pSource->conditionalRenderingEnable
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_RENDER_PASS_TRANSFORM_AVAILABLE
    auto toVulkanFormat (
            VkCommandBufferInheritanceRenderPassTransformInfoQCOM                    * pDestination,
            Type ( CommandBufferInheritanceRenderPassTransformInfoQualcomm )   const * pSource
    ) noexcept -> VkCommandBufferInheritanceRenderPassTransformInfoQCOM * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType      = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_RENDER_PASS_TRANSFORM_INFO_QCOM,
                .pNext      = nullptr,
                .transform  = static_cast < VkSurfaceTransformFlagBitsKHR > ( pSource->transform ),
                .renderArea = {
                        .offset     = {
                                .x          = pSource->renderArea.offset.x,
                                .y          = pSource->renderArea.offset.y
                        },
                        .extent     = {
                                .width      = pSource->renderArea.extent.width,
                                .height     = pSource->renderArea.extent.height
                        }
                }
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkViewport                * pDestination,
            Type ( Viewport )   const * pSource
    ) noexcept -> VkViewport * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .x          = pSource->x,
                .y          = pSource->y,
                .width      = pSource->width,
                .height     = pSource->height,
                .minDepth   = pSource->minDepth,
                .maxDepth   = pSource->maxDepth
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_INHERITED_VIEWPORT_SCISSOR_AVAILABLE
    auto toVulkanFormat (
            VkCommandBufferInheritanceViewportScissorInfoNV                    * pDestination,
            Type ( CommandBufferInheritanceViewportScissorInfoNVidia )   const * pSource
    ) noexcept -> VkCommandBufferInheritanceViewportScissorInfoNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_RENDER_PASS_TRANSFORM_INFO_QCOM,
                .pNext              = nullptr,
                .viewportScissor2D  = pSource->viewportScissor2D,
                .viewportDepthCount = pSource->viewportDepthCount,
                .pViewportDepths    = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto prepareContext (
            BeginCommandBufferContext             * pContext,
            Type ( CommandBufferBeginInfo ) const * pSource
    ) noexcept -> VkCommandBufferBeginInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pNext );
        auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->beginInfo, pSource ) );

        while ( pCurrent != nullptr ) {

            switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

                case StructureTypeDeviceGroupCommandBufferBeginInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->deviceGroupBeginInfo,
                                    reinterpret_cast < Type ( DeviceGroupCommandBufferBeginInfo ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

                default:
                    break;
            }

            pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
            pCurrent    = pCurrent->pNext;
        }

        pCurrentVk->pNext = nullptr;

        if ( pSource->pInheritanceInfo != nullptr ) {

            pContext->beginInfo.pInheritanceInfo = & pContext->inheritanceInfo;

            pCurrent    = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pInheritanceInfo->pNext );
            pCurrentVk  = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->inheritanceInfo, pSource->pInheritanceInfo ) );

            while ( pCurrent != nullptr ) {

                switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                    case StructureTypeCommandBufferInheritanceRenderingInfo: {

                        auto pInheritanceRenderingInfo = reinterpret_cast < Type ( CommandBufferInheritanceRenderingInfo ) const * > ( pCurrent );
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->inheritanceRenderingInfo,
                                        pInheritanceRenderingInfo
                                )
                        );

                        pContext->inheritanceRenderingInfo.pColorAttachmentFormats = & pContext->renderingInfoFormats[0];

                        if ( pContext->inheritanceRenderingInfo.colorAttachmentCount > engine :: vulkan :: config :: renderingInfoFormatsCount ) {
                            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                                    "config :: renderingInfoFormatsCount = %d. Minimum Required = %d",
                                    engine :: vulkan :: config :: renderingInfoFormatsCount,
                                    pContext->inheritanceRenderingInfo.colorAttachmentCount
                            ))

                            pContext->inheritanceRenderingInfo.colorAttachmentCount = engine :: vulkan :: config :: renderingInfoFormatsCount;
                        }

                        for ( cds :: uint32 i = 0U; i < pContext->inheritanceRenderingInfo.colorAttachmentCount; ++ i ) {
                            pContext->renderingInfoFormats[i] = static_cast < VkFormat > ( pInheritanceRenderingInfo->pColorAttachmentFormats[i] );
                        }

                        break;
                    }

#if __C_ENG_VULKAN_API_EXTENSION_AMD_MIXED_ATTACHMENT_SAMPLES_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAMEBUFFER_MIXED_SAMPLES_AVAILABLE

                    case StructureTypeAttachmentSampleCountInfoAMD: {

                        auto pAttachmentSampleCountInfo = reinterpret_cast < Type ( AttachmentSampleCountInfoAMD ) const * > ( pCurrent );
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->attachmentSampleCountInfo,
                                        pAttachmentSampleCountInfo
                                )
                        );

                        pContext->attachmentSampleCountInfo.pColorAttachmentSamples = & pContext->sampleCountAttachmentSamples[0];

                        if ( pContext->attachmentSampleCountInfo.colorAttachmentCount > engine :: vulkan :: config :: sampleCountAttachmentSamplesCount ) {
                            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                                    "config :: sampleCountAttachmentSamplesCount = %d. Minimum Required = %d",
                                    engine :: vulkan :: config :: sampleCountAttachmentSamplesCount,
                                    pContext->attachmentSampleCountInfo.colorAttachmentCount
                            ))

                            pContext->attachmentSampleCountInfo.colorAttachmentCount = engine :: vulkan :: config :: sampleCountAttachmentSamplesCount;
                        }

                        for ( cds :: uint32 i = 0U; i < pContext->attachmentSampleCountInfo.colorAttachmentCount; ++ i ) {
                            pContext->sampleCountAttachmentSamples[i] = static_cast < VkSampleCountFlagBits > ( pAttachmentSampleCountInfo->pColorAttachmentSamples[i] );
                        }

                        break;
                    }

#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE

                    case StructureTypeMultiviewPerViewAttributesInfoNVidiaExperimental:
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->multiviewPerViewAttributesInfo,
                                        reinterpret_cast < Type ( MultiviewPerViewAttributesInfoNVidia ) const * > ( pCurrent )
                                )
                        );
                        break;

#endif
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE

                    case StructureTypeCommandBufferInheritanceConditionalRenderingInfo:
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->inheritanceConditionalRenderingInfo,
                                        reinterpret_cast < Type ( CommandBufferInheritanceConditionalRenderingInfo ) const * > ( pCurrent )
                                )
                        );
                        break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_RENDER_PASS_TRANSFORM_AVAILABLE

                    case StructureTypeCommandBufferInheritanceRenderPassTransformInfoQualcomm:
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->inheritanceRenderpassTransformInfo,
                                        reinterpret_cast < Type ( CommandBufferInheritanceRenderPassTransformInfoQualcomm ) const * > ( pCurrent )
                                )
                        );
                        break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_INHERITED_VIEWPORT_SCISSOR_AVAILABLE

                    case StructureTypeCommandBufferInheritanceViewportScissorInfoNVidia: {

                        auto pInheritanceViewportScissorInfo = reinterpret_cast < Type ( CommandBufferInheritanceViewportScissorInfoNVidia ) const * > ( pCurrent );
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->inheritanceViewportScissorInfo,
                                        pInheritanceViewportScissorInfo
                                )
                        );

                        pContext->inheritanceViewportScissorInfo.pViewportDepths = & pContext->viewportDepths[0];

                        if ( pContext->inheritanceViewportScissorInfo.viewportDepthCount > engine :: vulkan :: config :: viewportDepthCount ) {
                            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                                    "config :: viewportDepthCount = %d. Minimum Required = %d",
                                    engine :: vulkan :: config :: viewportDepthCount,
                                    pContext->inheritanceViewportScissorInfo.viewportDepthCount
                            ))

                            pContext->inheritanceViewportScissorInfo.viewportDepthCount = engine :: vulkan :: config :: viewportDepthCount;
                        }

                        for ( cds :: uint32 i = 0U; i < pContext->inheritanceViewportScissorInfo.viewportDepthCount; ++ i ) {
                            (void) toVulkanFormat ( & pContext->viewportDepths[i], & pInheritanceViewportScissorInfo->pViewportDepths[i] );
                        }

                        break;
                    }

#endif

                    default:
                        break;
                }

                pCurrent    = pCurrent->pNext;
                pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
            }

            pCurrentVk->pNext = nullptr;
        }

        return & pContext->beginInfo;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto toVulkanFormat (
            VkDeviceGroupSubmitInfo               * pDestination,
            Type ( DeviceGroupSubmitInfo )  const * pSource
    ) noexcept -> VkDeviceGroupSubmitInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if (
                pDestination    == nullptr ||
                pSource         == nullptr
        ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                          = VK_STRUCTURE_TYPE_DEVICE_GROUP_SUBMIT_INFO,
                .pNext                          = nullptr,
                .waitSemaphoreCount             = pSource->waitSemaphoreCount,
                .pWaitSemaphoreDeviceIndices    = pSource->pWaitSemaphoreDeviceIndices,
                .commandBufferCount             = pSource->commandBufferCount,
                .pCommandBufferDeviceMasks      = pSource->pCommandBufferDeviceMasks,
                .signalSemaphoreCount           = pSource->signalSemaphoreCount,
                .pSignalSemaphoreDeviceIndices  = pSource->pSignalSemaphoreDeviceIndices
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto toVulkanFormat (
            VkProtectedSubmitInfo               * pDestination,
            Type ( ProtectedSubmitInfo )  const * pSource
    ) noexcept -> VkProtectedSubmitInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if (
                pDestination    == nullptr ||
                pSource         == nullptr
        ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType              = VK_STRUCTURE_TYPE_PROTECTED_SUBMIT_INFO,
                .pNext              = nullptr,
                .protectedSubmit    = pSource->protectedSubmit
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    auto toVulkanFormat (
            VkTimelineSemaphoreSubmitInfo               * pDestination,
            Type ( TimelineSemaphoreSubmitInfo )  const * pSource
    ) noexcept -> VkTimelineSemaphoreSubmitInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if (
                pDestination    == nullptr ||
                pSource         == nullptr
        ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                      = VK_STRUCTURE_TYPE_TIMELINE_SEMAPHORE_SUBMIT_INFO,
                .pNext                      = nullptr,
                .waitSemaphoreValueCount    = pSource->waitSemaphoreValueCount,
                .pWaitSemaphoreValues       = reinterpret_cast < decltype ( pDestination->pWaitSemaphoreValues ) > ( pSource->pWaitSemaphoreValues ),
                .signalSemaphoreValueCount  = pSource->signalSemaphoreValueCount,
                .pSignalSemaphoreValues     = reinterpret_cast < decltype ( pDestination->pSignalSemaphoreValues ) > ( pSource->signalSemaphoreValueCount )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
    auto toVulkanFormat (
            VkPerformanceQuerySubmitInfoKHR            * pDestination,
            Type ( PerformanceQuerySubmitInfo )  const * pSource
    ) noexcept -> VkPerformanceQuerySubmitInfoKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if (
                pDestination    == nullptr ||
                pSource         == nullptr
        ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                      = VK_STRUCTURE_TYPE_PERFORMANCE_QUERY_SUBMIT_INFO_KHR,
                .pNext                      = nullptr,
                .counterPassIndex           = pSource->counterPassIndex
        };

        return pDestination;
    }
#endif

#if VK_STRUCTURE_TYPE_PERFORMANCE_QUERY_SUBMIT_INFO_KHR
    auto toVulkanFormat (
            VkWin32KeyedMutexAcquireReleaseInfoKHR            * pDestination,
            Type ( Win32KeyedMutexAcquireReleaseInfo )  const * pSource
    ) noexcept -> VkWin32KeyedMutexAcquireReleaseInfoKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if (
                pDestination    == nullptr ||
                pSource         == nullptr
        ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                      = VK_STRUCTURE_TYPE_WIN32_KEYED_MUTEX_ACQUIRE_RELEASE_INFO_KHR,
                .pNext                      = nullptr,
                .acquireCount               = pSource->acquireCount,
                .pAcquireSyncs              = pSource->pAcquireSyncs,
                .pAcquireKeys               = reinterpret_cast < decltype ( pDestination->pAcquireKeys ) > ( pSource->pAcquireKeys ),
                .pAcquireTimeouts           = pSource->pAcquireTimeouts,
                .releaseCount               = pSource->releaseCount,
                .pReleaseSyncs              = pSource->pReleaseSyncs,
                .pReleaseKeys               = reinterpret_cast < decltype ( pDestination->pReleaseKeys ) > ( pSource->pReleaseKeys )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_WIN32_KEYED_MUTEX_AVAILABLE
    auto toVulkanFormat (
            VkWin32KeyedMutexAcquireReleaseInfoNV            * pDestination,
            Type ( Win32KeyedMutexAcquireReleaseInfoNVidia )  const * pSource
    ) noexcept -> VkWin32KeyedMutexAcquireReleaseInfoNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if (
                pDestination    == nullptr ||
                pSource         == nullptr
        ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                          = VK_STRUCTURE_TYPE_WIN32_KEYED_MUTEX_ACQUIRE_RELEASE_INFO_NV,
                .pNext                          = nullptr,
                .acquireCount                   = pSource->acquireCount,
                .pAcquireSyncs                  = pSource->pAcquireSyncs,
                .pAcquireKeys                   = reinterpret_cast < decltype ( pDestination->pAcquireKeys ) > ( pSource->pAcquireKeys ),
                .pAcquireTimeoutMilliseconds    = pSource->pAcquireTimeoutsMilliseconds,
                .releaseCount                   = pSource->releaseCount,
                .pReleaseSyncs                  = pSource->pReleaseSyncs,
                .pReleaseKeys                   = reinterpret_cast < decltype ( pDestination->pReleaseKeys ) > ( pSource->pReleaseKeys )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_WIN32_AVAILABLE
    auto toVulkanFormat (
            VkD3D12FenceSubmitInfoKHR               * pDestination,
            Type ( D3D12FenceSubmitInfo )     const * pSource
    ) noexcept -> VkTimelineSemaphoreSubmitInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if (
                pDestination    == nullptr ||
                pSource         == nullptr
        ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                      = VK_STRUCTURE_TYPE_D3D12_FENCE_SUBMIT_INFO_KHR,
                .pNext                      = nullptr,
                .waitSemaphoreValueCount    = pSource->waitSemaphoreValueCount,
                .pWaitSemaphoreValues       = reinterpret_cast < decltype ( pDestination->pWaitSemaphoreValues ) > ( pSource->pWaitSemaphoreValues ),
                .signalSemaphoreValueCount  = pSource->signalSemaphoreValueCount,
                .pSignalSemaphoreValues     = reinterpret_cast < decltype ( pDestination->pSignalSemaphoreValues ) > ( pSource->signalSemaphoreValueCount )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkSubmitInfo              * pDestination,
            Type ( SubmitInfo ) const * pSource
    ) noexcept -> VkSubmitInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if (
                pDestination    == nullptr ||
                pSource         == nullptr
        ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                      = VK_STRUCTURE_TYPE_SUBMIT_INFO,
                .pNext                      = nullptr,
                .waitSemaphoreCount         = pSource->waitSemaphoreCount,
                .pWaitSemaphores            = pSource->pWaitSemaphores,
                .pWaitDstStageMask          = nullptr,
                .commandBufferCount         = pSource->commandBufferCount,
                .pCommandBuffers            = pSource->pCommandBuffers,
                .signalSemaphoreCount       = pSource->signalSemaphoreCount,
                .pSignalSemaphores          = pSource->pSignalSemaphores
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto prepareContext (
            SubmitQueueContext        * pContext,
            cds :: uint32               count,
            Type ( SubmitInfo ) const * pInfos
    ) noexcept -> VkSubmitInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pInfos == nullptr || count == 0U ) {
            return nullptr;
        }

#endif

        for ( cds :: uint32 i = 0U; i < count; ++ i ) {

            auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pInfos[i].pNext );
            auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->submitInfos[i], & pInfos[i] ) );

            while ( pCurrent != nullptr ) {

                switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

                    case StructureTypeDeviceGroupSubmitInfo:
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->deviceGroupSubmitInfos[i],
                                        reinterpret_cast < Type ( DeviceGroupSubmitInfo ) const * > ( pCurrent )
                                )
                        );
                        break;

                    case StructureTypeProtectedSubmitInfo:
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->protectedSubmitInfos[i],
                                        reinterpret_cast < Type ( ProtectedSubmitInfo ) const * > ( pCurrent )
                                )
                        );
                        break;

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

                    case StructureTypeTimelineSemaphoreSubmitInfo:
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->timelineSemaphoreSubmitInfos[i],
                                        reinterpret_cast < Type ( TimelineSemaphoreSubmitInfo ) const * > ( pCurrent )
                                )
                        );
                        break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

                    case StructureTypePerformanceQuerySubmitInfo:
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->performanceQuerySubmitInfos[i],
                                        reinterpret_cast < Type ( PerformanceQuerySubmitInfo ) const * > ( pCurrent )
                                )
                        );
                        break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WIN32_KEYED_MUTEX_AVAILABLE

                    case StructureTypeWin32KeyedMutexAcquireReleaseInfo:
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->win32KeyedMutexAcquireReleaseInfos[i],
                                        reinterpret_cast < Type ( Win32KeyedMutexAcquireReleaseInfo ) const * > ( pCurrent )
                                )
                        );
                        break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_WIN32_KEYED_MUTEX_AVAILABLE

                    case StructureTypeWin32KeyedMutexAcquireReleaseInfoNVidia:
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->win32KeyedMutexAcquireReleaseInfosNVidia[i],
                                        reinterpret_cast < Type ( Win32KeyedMutexAcquireReleaseInfoNVidia ) const * > ( pCurrent )
                                )
                        );
                        break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_WIN32_AVAILABLE

                    case StructureTypeD3D12FenceSubmitInfo:
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->d3d12FenceSubmitInfos[i],
                                        reinterpret_cast < Type ( D3D12FenceSubmitInfo ) const * > ( pCurrent )
                                )
                        );
                        break;

#endif

                    default:
                        break;
                }

                pCurrent    = pCurrent->pNext;
                pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
            }

            pCurrentVk->pNext = nullptr;

            pContext->submitInfos[i].pWaitDstStageMask = & pContext->stageFlags[i][0];

            if ( pContext->submitInfos[i].waitSemaphoreCount > engine :: vulkan :: config :: pipelineStageFlagsCount ) {
                __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                        "config :: pipelineStageFlagsCount = %d. Minimum Required = %d",
                        engine :: vulkan :: config :: pipelineStageFlagsCount,
                        pContext->submitInfos[i].waitSemaphoreCount
                ))

                pContext->submitInfos[i].waitSemaphoreCount = engine :: vulkan :: config :: pipelineStageFlagsCount;
            }

            for ( cds :: uint32 j = 0U; j < pContext->submitInfos[i].waitSemaphoreCount; ++ j ) {
                pContext->stageFlags[i][j] = static_cast < VkPipelineStageFlags > ( pInfos[i].pWaitDestinationStageMasks[j] );
            }
        }

        return & pContext->submitInfos[0];
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
    auto toVulkanFormat (
            VkSubmitInfo2_t            * pDestination,
            Type ( SubmitInfo2 ) const * pSource
    ) noexcept -> VkSubmitInfo2_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
                .sType                     = VK_STRUCTURE_TYPE_SUBMIT_INFO_2,
#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
                .sType                     = VK_STRUCTURE_TYPE_SUBMIT_INFO_2_KHR,
#endif
                .pNext                     = nullptr,
                .flags                     = pSource->flags,
                .waitSemaphoreInfoCount    = pSource->waitSemaphoreInfoCount,
                .pWaitSemaphoreInfos       = nullptr,
                .commandBufferInfoCount    = pSource->commandBufferInfoCount,
                .pCommandBufferInfos       = nullptr,
                .signalSemaphoreInfoCount  = pSource->signalSemaphoreInfoCount,
                .pSignalSemaphoreInfos     = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
    auto toVulkanFormat (
            VkSemaphoreSubmitInfo_t            * pDestination,
            Type ( SemaphoreSubmitInfo ) const * pSource
    ) noexcept -> VkSemaphoreSubmitInfo_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
                .sType                     = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
                .sType                     = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO_KHR,
#endif
                .pNext                     = nullptr,
                .semaphore                 = pSource->semaphore,
                .value                     = pSource->value,
                .stageMask                 = pSource->stageMask,
                .deviceIndex               = pSource->deviceIndex
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
    auto toVulkanFormat (
            VkCommandBufferSubmitInfo_t            * pDestination,
            Type ( CommandBufferSubmitInfo ) const * pSource
    ) noexcept -> VkCommandBufferSubmitInfo_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
                .sType                     = VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO,
#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
                .sType                     = VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO_KHR,
#endif
                .pNext                     = nullptr,
                .commandBuffer             = pSource->commandBuffer,
                .deviceMask                = pSource->deviceMask
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
    auto prepareContext (
            SubmitQueueContext            * pContext,
            cds :: uint32                   count,
            Type ( SubmitInfo2 )    const * pInfos
    ) noexcept -> VkSubmitInfo2_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || count == 0U || pInfos == nullptr ) {
            return nullptr;
        }

#endif

        for ( cds :: uint32 i = 0U; i < count; ++ i ) {

            auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pInfos[i].pNext );
            auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->submitInfos2[i], & pInfos[i] ) );

            while ( pCurrent != nullptr ) {

                switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

                    case StructureTypePerformanceQuerySubmitInfo:
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->performanceQuerySubmitInfos [i],
                                        reinterpret_cast < Type ( PerformanceQuerySubmitInfo ) const * > ( pCurrent )
                                )
                        );
                        break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WIN32_KEYED_MUTEX_AVAILABLE

                    case StructureTypeWin32KeyedMutexAcquireReleaseInfo:
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->win32KeyedMutexAcquireReleaseInfos [i],
                                        reinterpret_cast < Type ( Win32KeyedMutexAcquireReleaseInfo ) const * > ( pCurrent )
                                )
                        );
                        break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_WIN32_KEYED_MUTEX_AVAILABLE

                    case StructureTypeWin32KeyedMutexAcquireReleaseInfoNVidia:
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->win32KeyedMutexAcquireReleaseInfosNVidia [i],
                                        reinterpret_cast < Type ( Win32KeyedMutexAcquireReleaseInfoNVidia ) const * > ( pCurrent )
                                )
                        );
                        break;

#endif

                    default:
                        break;
                }

                pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
                pCurrent    = pCurrent->pNext;
            }

            pCurrentVk->pNext = nullptr;

            pContext->submitInfos2[i].pWaitSemaphoreInfos = & pContext->waitSemaphoreSubmitInfos[i][0];

            if ( pContext->submitInfos2[i].waitSemaphoreInfoCount > engine :: vulkan :: config :: submitSemaphoreInfoCount ) {
                __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                        "config :: submitSemaphoreInfoCount = %d. Minimum Required = %d",
                        engine :: vulkan :: config :: submitSemaphoreInfoCount,
                        pContext->submitInfos2[i].waitSemaphoreInfoCount
                ))

                pContext->submitInfos2[i].waitSemaphoreInfoCount = engine :: vulkan :: config :: submitSemaphoreInfoCount;
            }

            for ( cds :: uint32 j = 0U; j < pContext->submitInfos2[i].waitSemaphoreInfoCount; ++ j ) {
                (void) toVulkanFormat ( & pContext->waitSemaphoreSubmitInfos[i][j], & pInfos[i].pWaitSemaphoreInfos[j] );
            }

            pContext->submitInfos2[i].pCommandBufferInfos = & pContext->commandBufferSubmitInfos[i][0];

            if ( pContext->submitInfos2[i].commandBufferInfoCount > engine :: vulkan :: config :: submitCommandBufferInfoCount ) {
                __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                        "config :: submitCommandBufferInfoCount = %d. Minimum Required = %d",
                        engine :: vulkan :: config :: submitCommandBufferInfoCount,
                        pContext->submitInfos2[i].commandBufferInfoCount
                ))

                pContext->submitInfos2[i].commandBufferInfoCount = engine :: vulkan :: config :: submitCommandBufferInfoCount;
            }

            for ( cds :: uint32 j = 0U; j < pContext->submitInfos2[i].commandBufferInfoCount; ++ j ) {
                (void) toVulkanFormat ( & pContext->commandBufferSubmitInfos[i][j], & pInfos[i].pCommandBufferInfos[j] );
            }

            pContext->submitInfos2[i].pSignalSemaphoreInfos = & pContext->signalSemaphoreSubmitInfos[i][0];

            if ( pContext->submitInfos2[i].signalSemaphoreInfoCount > engine :: vulkan :: config :: submitSemaphoreInfoCount ) {
                __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                        "config :: submitSemaphoreInfoCount = %d. Minimum Required = %d",
                        engine :: vulkan :: config :: submitSemaphoreInfoCount,
                        pContext->submitInfos2[i].signalSemaphoreInfoCount
                ))

                pContext->submitInfos2[i].signalSemaphoreInfoCount = engine :: vulkan :: config :: submitSemaphoreInfoCount;
            }

            for ( cds :: uint32 j = 0U; j < pContext->submitInfos2[i].signalSemaphoreInfoCount; ++ j ) {
                (void) toVulkanFormat ( & pContext->signalSemaphoreSubmitInfos[i][j], & pInfos[i].pSignalSemaphoreInfos[j] );
            }
        }

        return & pContext->submitInfos2[0];
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkFenceCreateInfo            * pDestination,
            Type ( FenceCreateInfo ) const * pSource
    ) noexcept -> VkFenceCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                      = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
                .pNext                      = nullptr,
                .flags                      = pSource->flags
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto toVulkanFormat (
            VkExportFenceCreateInfo            * pDestination,
            Type ( ExportFenceCreateInfo ) const * pSource
    ) noexcept -> VkExportFenceCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                      = VK_STRUCTURE_TYPE_EXPORT_FENCE_CREATE_INFO,
                .pNext                      = nullptr,
                .handleTypes                = pSource->handleTypes
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_WIN32_AVAILABLE
    auto toVulkanFormat (
            VkExportFenceWin32HandleInfoKHR            * pDestination,
            Type ( ExportFenceWin32HandleInfo ) const * pSource
    ) noexcept -> VkExportFenceWin32HandleInfoKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                      = VK_STRUCTURE_TYPE_EXPORT_FENCE_WIN32_HANDLE_INFO_KHR,
                .pNext                      = nullptr,
                .pAttributes                = pSource->pAttributes,
                .dwAccess                   = pSource->dwAccess,
                .name                       = pSource->name
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto prepareContext (
            CreateFenceContext                * pContext,
            Type ( FenceCreateInfo )    const * pSource
    ) noexcept -> VkFenceCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pNext );
        auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->createInfo, pSource ) );

        while ( pCurrent != nullptr ) {

            switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

                case StructureTypeExportFenceCreateInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->exportCreateInfo,
                                    reinterpret_cast < Type ( ExportFenceCreateInfo ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_WIN32_AVAILABLE

                case StructureTypeExportFenceWin32HandleInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->exportCreateInfo,
                                    reinterpret_cast < Type ( ExportFenceWin32HandleInfo ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

                default:
                    break;
            }

            pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
            pCurrent    = pCurrent->pNext;
        }

        pCurrentVk->pNext = nullptr;

        return & pContext->createInfo;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_WIN32_AVAILABLE
    auto toVulkanFormat (
            VkFenceGetWin32HandleInfoKHR           * pDestination,
            Type ( FenceGetWin32HandleInfo ) const * pSource
    ) noexcept -> VkFenceGetWin32HandleInfoKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                      = VK_STRUCTURE_TYPE_FENCE_GET_WIN32_HANDLE_INFO_KHR,
                .pNext                      = nullptr,
                .pAttributes                = pSource->pAttributes,
                .dwAccess                   = pSource->dwAccess,
                .name                       = pSource->name
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_FD_AVAILABLE
    auto toVulkanFormat (
            VkFenceGetFdInfoKHR           * pDestination,
            Type ( FenceGetFDInfo ) const * pSource
    ) noexcept -> VkFenceGetFdInfoKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                      = VK_STRUCTURE_TYPE_FENCE_GET_FD_INFO_KHR,
                .pNext                      = nullptr,
                .fence                      = pSource->fence,
                .handleType                 = static_cast < VkExternalFenceHandleTypeFlagBitsKHR > ( pSource->handleType )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISPLAY_CONTROL_AVAILABLE
    auto toVulkanFormat (
            VkDeviceEventInfoEXT              * pDestination,
            Type ( DeviceEventInfo )    const * pSource
    ) noexcept -> VkDeviceEventInfoEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType          = VK_STRUCTURE_TYPE_DEVICE_EVENT_INFO_EXT,
                .pNext          = nullptr,
                .deviceEvent    = static_cast < VkDeviceEventTypeEXT > ( pSource->deviceEvent )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISPLAY_CONTROL_AVAILABLE
    auto toVulkanFormat (
            VkDisplayEventInfoEXT              * pDestination,
            Type ( DisplayEventInfo )    const * pSource
    ) noexcept -> VkDisplayEventInfoEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType          = VK_STRUCTURE_TYPE_DISPLAY_EVENT_INFO_EXT,
                .pNext          = nullptr,
                .displayEvent   = static_cast < VkDisplayEventTypeEXT > ( pSource->displayEvent )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_WIN32_AVAILABLE
    auto toVulkanFormat (
            VkImportFenceWin32HandleInfoKHR              * pDestination,
            Type ( ImportFenceWin32HandleInfo )    const * pSource
    ) noexcept -> VkImportFenceWin32HandleInfoKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType          = VK_STRUCTURE_TYPE_IMPORT_FENCE_WIN32_HANDLE_INFO_KHR,
                .pNext          = nullptr,
                .fence          = pSource->fence,
                .flags          = pSource->flags,
                .handleType     = static_cast < VkExternalFenceHandleTypeFlagBits > ( pSource->handleType ),
                .handle         = pSource->handle,
                .name           = pSource->name
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_FD_AVAILABLE
    auto toVulkanFormat (
            VkImportFenceFdInfoKHR              * pDestination,
            Type ( ImportFenceFdInfo )    const * pSource
    ) noexcept -> VkImportFenceFdInfoKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType          = VK_STRUCTURE_TYPE_IMPORT_FENCE_FD_INFO_KHR,
                .pNext          = nullptr,
                .fence          = pSource->fence,
                .flags          = pSource->flags,
                .handleType     = static_cast < VkExternalFenceHandleTypeFlagBits > ( pSource->handleType ),
                .fd             = pSource->fd
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkSemaphoreCreateInfo                  * pDestination,
            Type ( SemaphoreCreateInfo )     const * pSource
    ) noexcept -> VkSemaphoreCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType          = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
                .pNext          = nullptr,
                .flags          = pSource->flags
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto toVulkanFormat (
            VkExportSemaphoreCreateInfo                  * pDestination,
            Type ( ExportSemaphoreCreateInfo )     const * pSource
    ) noexcept -> VkExportSemaphoreCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType          = VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_CREATE_INFO,
                .pNext          = nullptr,
                .handleTypes    = pSource->handleTypes
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    auto toVulkanFormat (
            VkSemaphoreTypeCreateInfo                  * pDestination,
            Type ( SemaphoreTypeCreateInfo )     const * pSource
    ) noexcept -> VkSemaphoreTypeCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType          = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
                .pNext          = nullptr,
                .semaphoreType  = static_cast < VkSemaphoreType > ( pSource->semaphoreType ),
                .initialValue   = pSource->initialValue
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_WIN32_AVAILABLE
    auto toVulkanFormat (
            VkExportSemaphoreWin32HandleInfoKHR                  * pDestination,
            Type ( ExportSemaphoreWin32HandleInfo )        const * pSource
    ) noexcept -> VkExportSemaphoreWin32HandleInfoKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType          = VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_WIN32_HANDLE_INFO_KHR,
                .pNext          = nullptr,
                .pAttributes    = pSource->pAttributes,
                .dwAccess       = pSource->dwAccess,
                .name           = pSource->name
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto prepareContext (
            CreateSemaphoreContext                * pContext,
            Type ( SemaphoreCreateInfo )    const * pSource
    ) noexcept -> VkSemaphoreCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pNext );
        auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->createInfo, pSource ) );

        while ( pCurrent != nullptr ) {

            switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

                case StructureTypeExportSemaphoreCreateInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->exportCreateInfo,
                                    reinterpret_cast < Type ( ExportSemaphoreCreateInfo ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

                case StructureTypeSemaphoreTypeCreateInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->typeCreateInfo,
                                    reinterpret_cast < Type ( SemaphoreTypeCreateInfo ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_WIN32_AVAILABLE

                case StructureTypeExportSemaphoreWin32HandleInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->exportWin32HandleInfo,
                                    reinterpret_cast < Type ( ExportSemaphoreWin32HandleInfo ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

                default:
                    break;
            }

            pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
            pCurrent    = pCurrent->pNext;
        }

        pCurrentVk = nullptr;

        return & pContext->createInfo;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_WIN32_AVAILABLE
    auto toVulkanFormat (
            VkSemaphoreGetWin32HandleInfoKHR                  * pDestination,
            Type ( SemaphoreGetWin32HandleInfo )        const * pSource
    ) noexcept -> VkSemaphoreGetWin32HandleInfoKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType          = VK_STRUCTURE_TYPE_SEMAPHORE_GET_WIN32_HANDLE_INFO_KHR,
                .pNext          = nullptr,
                .semaphore      = pSource->semaphore,
                .handleType     = static_cast < VkExternalSemaphoreHandleTypeFlagBits > ( pSource->handleType )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_FD_AVAILABLE
    auto toVulkanFormat (
            VkSemaphoreGetFdInfoKHR                  * pDestination,
            Type ( SemaphoreGetFdInfo )        const * pSource
    ) noexcept -> VkSemaphoreGetFdInfoKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType          = VK_STRUCTURE_TYPE_SEMAPHORE_GET_FD_INFO_KHR,
                .pNext          = nullptr,
                .semaphore      = pSource->semaphore,
                .handleType     = static_cast < VkExternalSemaphoreHandleTypeFlagBits > ( pSource->handleType )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_SEMAPHORE_AVAILABLE
    auto toVulkanFormat (
            VkSemaphoreGetZirconHandleInfoFUCHSIA                    * pDestination,
            Type ( SemaphoreGetZirconHandleInfoGoogle )        const * pSource
    ) noexcept -> VkSemaphoreGetZirconHandleInfoFUCHSIA * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType          = VK_STRUCTURE_TYPE_SEMAPHORE_GET_ZIRCON_HANDLE_INFO_FUCHSIA,
                .pNext          = nullptr,
                .semaphore      = pSource->semaphore,
                .handleType     = static_cast < VkExternalSemaphoreHandleTypeFlagBits > ( pSource->handleType )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    auto toVulkanFormat (
            VkSemaphoreWaitInfo                     * pDestination,
            Type ( SemaphoreWaitInfo )        const * pSource
    ) noexcept -> VkSemaphoreWaitInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType          = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
                .pNext          = nullptr,
                .flags          = pSource->flags,
                .semaphoreCount = pSource->semaphoreCount,
                .pSemaphores    = pSource->pSemaphores,
                .pValues        = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto prepareContext (
            WaitSemaphoreContext                * pContext,
            Type ( SemaphoreWaitInfo )    const * pSource
    ) noexcept -> VkSemaphoreWaitInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        (void) toVulkanFormat ( & pContext->info, pSource );

        pContext->info.pValues = & pContext->values[0];

        if ( pContext->info.semaphoreCount > engine :: vulkan :: config :: waitSemaphoreCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                    "config :: waitSemaphoreCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: waitSemaphoreCount,
                    pContext->info.semaphoreCount
            ))

            pContext->info.semaphoreCount   = engine :: vulkan :: config :: waitSemaphoreCount;
        }

        for ( cds :: uint32 i = 0U; i < pContext->info.semaphoreCount; ++ i ) {
            pContext->values[i] = static_cast < uint64_t > ( pSource->pValues[i] );
        }

        return & pContext->info;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    auto toVulkanFormat (
            VkSemaphoreSignalInfo                     * pDestination,
            Type ( SemaphoreSignalInfo )        const * pSource
    ) noexcept -> VkSemaphoreSignalInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType          = VK_STRUCTURE_TYPE_SEMAPHORE_SIGNAL_INFO,
                .pNext          = nullptr,
                .semaphore      = pSource->semaphore,
                .value          = static_cast < uint64_t > ( pSource->value )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_WIN32_AVAILABLE
    auto toVulkanFormat (
            VkImportSemaphoreWin32HandleInfoKHR                  * pDestination,
            Type ( ImportSemaphoreWin32HandleInfo )        const * pSource
    ) noexcept -> VkImportSemaphoreWin32HandleInfoKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType          = VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_WIN32_HANDLE_INFO_KHR,
                .pNext          = nullptr,
                .semaphore      = pSource->semaphore,
                .flags          = pSource->flags,
                .handleType     = static_cast < VkExternalSemaphoreHandleTypeFlagBits > ( pSource->handleType ),
                .handle         = pSource->handle,
                .name           = pSource->name
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_FD_AVAILABLE
    auto toVulkanFormat (
            VkImportSemaphoreFdInfoKHR                  * pDestination,
            Type ( ImportSemaphoreFdInfo )        const * pSource
    ) noexcept -> VkImportSemaphoreFdInfoKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType          = VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_FD_INFO_KHR,
                .pNext          = nullptr,
                .semaphore      = pSource->semaphore,
                .flags          = pSource->flags,
                .handleType     = static_cast < VkExternalSemaphoreHandleTypeFlagBits > ( pSource->handleType ),
                .fd             = pSource->fd
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_SEMAPHORE_AVAILABLE
    auto toVulkanFormat (
            VkImportSemaphoreZirconHandleInfoFUCHSIA                    * pDestination,
            Type ( ImportSemaphoreZirconHandleInfoGoogle )        const * pSource
    ) noexcept -> VkImportSemaphoreZirconHandleInfoFUCHSIA * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType          = VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_ZIRCON_HANDLE_INFO_FUCHSIA,
                .pNext          = nullptr,
                .semaphore      = pSource->semaphore,
                .flags          = pSource->flags,
                .handleType     = static_cast < VkExternalSemaphoreHandleTypeFlagBits > ( pSource->handleType ),
                .zirconHandle   = pSource->zirconHandle
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkEventCreateInfo                     * pDestination,
            Type ( EventCreateInfo )        const * pSource
    ) noexcept -> VkEventCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType          = VK_STRUCTURE_TYPE_EVENT_CREATE_INFO,
                .pNext          = nullptr,
                .flags          = pSource->flags
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
    auto toVulkanFormat (
            VkDependencyInfo_t            * pDestination,
            Type ( DependencyInfo ) const * pSource
    ) noexcept -> VkDependencyInfo_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
                .sType                      = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
                .sType                      = VK_STRUCTURE_TYPE_DEPENDENCY_INFO_KHR,
#endif
                .pNext                      = nullptr,
                .dependencyFlags            = pSource->dependencyFlags,
                .memoryBarrierCount         = pSource->memoryBarrierCount,
                .pMemoryBarriers            = nullptr,
                .bufferMemoryBarrierCount   = pSource->bufferMemoryBarrierCount,
                .pBufferMemoryBarriers      = nullptr,
                .imageMemoryBarrierCount    = pSource->imageMemoryBarrierCount,
                .pImageMemoryBarriers       = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
    auto toVulkanFormat (
            VkMemoryBarrier2_t            * pDestination,
            Type ( MemoryBarrier2 ) const * pSource
    ) noexcept -> VkMemoryBarrier2_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
                .sType                      = VK_STRUCTURE_TYPE_MEMORY_BARRIER_2,
#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
                .sType                      = VK_STRUCTURE_TYPE_MEMORY_BARRIER_2_KHR,
#endif
                .pNext                      = nullptr,
                .srcStageMask               = pSource->sourceStageMask,
                .srcAccessMask              = pSource->sourceAccessMask,
                .dstStageMask               = pSource->destinationStageMask,
                .dstAccessMask              = pSource->destinationAccessMask
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
    auto toVulkanFormat (
            VkBufferMemoryBarrier2_t            * pDestination,
            Type ( BufferMemoryBarrier2 ) const * pSource
    ) noexcept -> VkBufferMemoryBarrier2_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
                .sType                      = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER_2,
#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
                .sType                      = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER_2_KHR,
#endif
                .pNext                      = nullptr,
                .srcStageMask               = pSource->sourceStageMask,
                .srcAccessMask              = pSource->sourceAccessMask,
                .dstStageMask               = pSource->destinationStageMask,
                .dstAccessMask              = pSource->destinationAccessMask,
                .srcQueueFamilyIndex        = pSource->sourceQueueFamilyIndex,
                .dstQueueFamilyIndex        = pSource->destinationQueueFamilyIndex,
                .buffer                     = pSource->buffer,
                .offset                     = pSource->offset,
                .size                       = pSource->size
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
    auto toVulkanFormat (
            VkImageMemoryBarrier2_t            * pDestination,
            Type ( ImageMemoryBarrier2 ) const * pSource
    ) noexcept -> VkImageMemoryBarrier2_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
                .sType                      = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
                .sType                      = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2_KHR,
#endif
                .pNext                      = nullptr,
                .srcStageMask               = pSource->sourceStageMask,
                .srcAccessMask              = pSource->sourceAccessMask,
                .dstStageMask               = pSource->destinationStageMask,
                .dstAccessMask              = pSource->destinationAccessMask,
                .oldLayout                  = static_cast < VkImageLayout > ( pSource->oldLayout ),
                .newLayout                  = static_cast < VkImageLayout > ( pSource->newLayout ),
                .srcQueueFamilyIndex        = pSource->sourceQueueFamilyIndex,
                .dstQueueFamilyIndex        = pSource->destinationQueueFamilyIndex,
                .image                      = pSource->image,
                .subresourceRange           = {
                        .aspectMask                 = pSource->subresourceRange.aspectMask,
                        .baseMipLevel               = pSource->subresourceRange.baseMipLevel,
                        .levelCount                 = pSource->subresourceRange.levelCount,
                        .baseArrayLayer             = pSource->subresourceRange.baseArrayLayer,
                        .layerCount                 = pSource->subresourceRange.layerCount,
                }
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkMemoryBarrier              * pDestination,
            Type ( MemoryBarrier ) const * pSource
    ) noexcept -> VkMemoryBarrier * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                      = VK_STRUCTURE_TYPE_MEMORY_BARRIER,
                .pNext                      = nullptr,
                .srcAccessMask              = static_cast < VkAccessFlags > ( pSource->sourceAccessMask ),
                .dstAccessMask              = static_cast < VkAccessFlags > ( pSource->destinationAccessMask )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkBufferMemoryBarrier              * pDestination,
            Type ( BufferMemoryBarrier ) const * pSource
    ) noexcept -> VkBufferMemoryBarrier * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                      = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER,
                .pNext                      = nullptr,
                .srcAccessMask              = static_cast < VkAccessFlags > ( pSource->sourceAccessMask ),
                .dstAccessMask              = static_cast < VkAccessFlags > ( pSource->destinationAccessMask ),
                .srcQueueFamilyIndex        = pSource->sourceQueueFamilyIndex,
                .dstQueueFamilyIndex        = pSource->destinationQueueFamilyIndex,
                .buffer                     = pSource->buffer,
                .offset                     = pSource->offset,
                .size                       = pSource->size
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkImageMemoryBarrier              * pDestination,
            Type ( ImageMemoryBarrier ) const * pSource
    ) noexcept -> VkImageMemoryBarrier * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                      = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
                .pNext                      = nullptr,
                .srcAccessMask              = static_cast < VkAccessFlags > ( pSource->sourceAccessMask ),
                .dstAccessMask              = static_cast < VkAccessFlags > ( pSource->destinationAccessMask ),
                .oldLayout                  = static_cast < VkImageLayout > ( pSource->oldLayout ),
                .newLayout                  = static_cast < VkImageLayout > ( pSource->newLayout ),
                .srcQueueFamilyIndex        = pSource->sourceQueueFamilyIndex,
                .dstQueueFamilyIndex        = pSource->destinationQueueFamilyIndex,
                .image                      = pSource->image,
                .subresourceRange           = {
                        .aspectMask                 = pSource->subresourceRange.aspectMask,
                        .baseMipLevel               = pSource->subresourceRange.baseMipLevel,
                        .levelCount                 = pSource->subresourceRange.levelCount,
                        .baseArrayLayer             = pSource->subresourceRange.baseArrayLayer,
                        .layerCount                 = pSource->subresourceRange.layerCount,
                }
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE
    auto toVulkanFormat (
            VkSampleLocationsInfoEXT           * pDestination,
            Type ( SampleLocationsInfo ) const * pSource
    ) noexcept -> VkSampleLocationsInfoEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                      = VK_STRUCTURE_TYPE_SAMPLE_LOCATIONS_INFO_EXT,
                .pNext                      = nullptr,
                .sampleLocationsPerPixel    = static_cast < VkSampleCountFlagBits > ( pSource->sampleLocationsPerPixel ),
                .sampleLocationGridSize     = {
                        .width                      = pSource->sampleLocationGridSize.width,
                        .height                     = pSource->sampleLocationGridSize.height
                },
                .sampleLocationsCount       = pSource->sampleLocationsCount,
                .pSampleLocations           = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
    auto prepareContext (
            SetCommandBufferEventContext          * pContext,
            Type ( DependencyInfo )         const * pSource
    ) noexcept -> VkDependencyInfo_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        (void) toVulkanFormat ( & pContext->dependencyInfo, pSource );

        pContext->dependencyInfo.pMemoryBarriers = & pContext->memoryBarriers[0];

        if ( pContext->dependencyInfo.memoryBarrierCount > engine :: vulkan :: config :: dependencyInfoMemoryBarrierCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                    "config :: dependencyInfoMemoryBarrierCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: dependencyInfoMemoryBarrierCount,
                    pContext->dependencyInfo.memoryBarrierCount
            ))

            pContext->dependencyInfo.memoryBarrierCount = engine :: vulkan :: config :: dependencyInfoMemoryBarrierCount;
        }

        for ( cds :: uint32 i = 0U; i < pContext->dependencyInfo.memoryBarrierCount; ++ i ) {
            (void) toVulkanFormat ( & pContext->memoryBarriers[i], & pSource->pMemoryBarriers[i] );
        }

        pContext->dependencyInfo.pBufferMemoryBarriers = & pContext->bufferMemoryBarriers[0];

        if ( pContext->dependencyInfo.bufferMemoryBarrierCount > engine :: vulkan :: config :: dependencyInfoBufferMemoryBarrierCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                    "config :: dependencyInfoBufferMemoryBarrierCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: dependencyInfoBufferMemoryBarrierCount,
                    pContext->dependencyInfo.bufferMemoryBarrierCount
            ))

            pContext->dependencyInfo.bufferMemoryBarrierCount = engine :: vulkan :: config :: dependencyInfoBufferMemoryBarrierCount;
        }

        for ( cds :: uint32 i = 0U; i < pContext->dependencyInfo.bufferMemoryBarrierCount; ++ i ) {
            (void) toVulkanFormat ( & pContext->bufferMemoryBarriers[i], & pSource->pBufferMemoryBarriers[i] );
        }

        pContext->dependencyInfo.pImageMemoryBarriers = & pContext->imageMemoryBarriers[0];

        if ( pContext->dependencyInfo.imageMemoryBarrierCount > engine :: vulkan :: config :: dependencyInfoImageMemoryBarrierCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                    "config :: dependencyInfoImageMemoryBarrierCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: dependencyInfoImageMemoryBarrierCount,
                    pContext->dependencyInfo.imageMemoryBarrierCount
            ))

            pContext->dependencyInfo.imageMemoryBarrierCount = engine :: vulkan :: config :: dependencyInfoImageMemoryBarrierCount;
        }

        for ( cds :: uint32 i = 0U; i < pContext->dependencyInfo.imageMemoryBarrierCount; ++ i ) {

            auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pNext );
            auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->imageMemoryBarriers[i], & pSource->pImageMemoryBarriers[i] ) );

            while ( pCurrent != nullptr ) {

                switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE

                    case StructureTypeSampleLocationsInfo: {

                        auto pSampleLocationsInfo = reinterpret_cast < Type ( SampleLocationsInfo ) const * > ( pCurrent );
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->sampleLocationsInfos[i],
                                        pSampleLocationsInfo
                                )
                        );

                        pContext->sampleLocationsInfos[i].pSampleLocations = & pContext->sampleLocations[i][0];

                        if ( pContext->sampleLocationsInfos[i].sampleLocationsCount > engine :: vulkan :: config :: sampleLocationsInfoSampleLocationsCount ) {
                            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                                    "config :: sampleLocationsInfoSampleLocationsCount = %d. Minimum Required = %d",
                                    engine :: vulkan :: config :: sampleLocationsInfoSampleLocationsCount,
                                    pContext->sampleLocationsInfos[i].sampleLocationsCount
                            ))

                            pContext->sampleLocationsInfos[i].sampleLocationsCount = engine :: vulkan :: config :: sampleLocationsInfoSampleLocationsCount;
                        }

                        for ( cds :: uint32 j = 0U; j < pContext->sampleLocationsInfos[i].sampleLocationsCount; ++ j ) {
                            pContext->sampleLocations[i][j] = {
                                    pSampleLocationsInfo->pSampleLocations[j].x,
                                    pSampleLocationsInfo->pSampleLocations[j].y
                            };
                        }

                        break;

                    }

#endif

                    default:
                        break;
                }

                pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
                pCurrent    = pCurrent->pNext;
            }

            pCurrentVk->pNext = nullptr;
        }

        return & pContext->dependencyInfo;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
    auto prepareContext (
            WaitCommandBufferEvent2Context        * pContext,
            cds :: uint32                           count,
            Type ( DependencyInfo )         const * pDependencyInfos
    ) noexcept -> VkDependencyInfo_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pDependencyInfos == nullptr ) {
            return nullptr;
        }

#endif

        if ( count > engine :: vulkan :: config :: commandBufferWaitEventsDependencyInfoCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                    "config :: commandBufferWaitEventsDependencyInfoCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: commandBufferWaitEventsDependencyInfoCount,
                    count
            ))

            count = engine :: vulkan :: config :: commandBufferWaitEventsDependencyInfoCount;
        }

        for ( cds :: uint32 i = 0U; i < count; ++ i ) {

            (void) toVulkanFormat ( & pContext->dependencyInfos[i], & pDependencyInfos[i] );

            pContext->dependencyInfos[i].pMemoryBarriers = & pContext->memoryBarriers[i][0];

            if ( pContext->dependencyInfos[i].memoryBarrierCount > engine :: vulkan :: config :: dependencyInfoMemoryBarrierCount ) {
                __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                        "config :: dependencyInfoMemoryBarrierCount = %d. Minimum Required = %d",
                        engine :: vulkan :: config :: dependencyInfoMemoryBarrierCount,
                        pContext->dependencyInfos[i].memoryBarrierCount
                ))

                pContext->dependencyInfos[i].memoryBarrierCount = engine :: vulkan :: config :: dependencyInfoMemoryBarrierCount;
            }

            for ( cds :: uint32 j = 0U; j < pContext->dependencyInfos[i].memoryBarrierCount; ++ j ) {
                (void) toVulkanFormat ( & pContext->memoryBarriers[i][j], & pDependencyInfos[i].pMemoryBarriers[j] );
            }

            pContext->dependencyInfos[i].pBufferMemoryBarriers = & pContext->bufferMemoryBarriers[i][0];

            if ( pContext->dependencyInfos[i].bufferMemoryBarrierCount > engine :: vulkan :: config :: dependencyInfoBufferMemoryBarrierCount ) {
                __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                        "config :: dependencyInfoBufferMemoryBarrierCount = %d. Minimum Required = %d",
                        engine :: vulkan :: config :: dependencyInfoBufferMemoryBarrierCount,
                        pContext->dependencyInfos[i].bufferMemoryBarrierCount
                ))

                pContext->dependencyInfos[i].bufferMemoryBarrierCount = engine :: vulkan :: config :: dependencyInfoBufferMemoryBarrierCount;
            }

            for ( cds :: uint32 j = 0U; j < pContext->dependencyInfos[i].bufferMemoryBarrierCount; ++ j ) {
                (void) toVulkanFormat ( & pContext->bufferMemoryBarriers[i][j], & pDependencyInfos[i].pBufferMemoryBarriers[j] );
            }

            pContext->dependencyInfos[i].pImageMemoryBarriers = & pContext->imageMemoryBarriers[i][0];

            if ( pContext->dependencyInfos[i].imageMemoryBarrierCount > engine :: vulkan :: config :: dependencyInfoImageMemoryBarrierCount ) {
                __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                        "config :: dependencyInfoImageMemoryBarrierCount = %d. Minimum Required = %d",
                        engine :: vulkan :: config :: dependencyInfoImageMemoryBarrierCount,
                        pContext->dependencyInfos[i].imageMemoryBarrierCount
                ))

                pContext->dependencyInfos[i].imageMemoryBarrierCount = engine :: vulkan :: config :: dependencyInfoImageMemoryBarrierCount;
            }

            for ( cds :: uint32 j = 0U; j < pContext->dependencyInfos[i].imageMemoryBarrierCount; ++ j ) {

                auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pDependencyInfos[i].pNext );
                auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->imageMemoryBarriers[i][j], & pDependencyInfos[i].pImageMemoryBarriers[j] ) );

                while ( pCurrent != nullptr ) {

                    switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE

                        case StructureTypeSampleLocationsInfo: {

                            auto pSampleLocationsInfo = reinterpret_cast < Type ( SampleLocationsInfo ) const * > ( pCurrent );
                            pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                    toVulkanFormat (
                                            & pContext->sampleLocationsInfos[i][j],
                                            pSampleLocationsInfo
                                    )
                            );

                            pContext->sampleLocationsInfos[i][j].pSampleLocations = & pContext->sampleLocations[i][j][0];

                            if ( pContext->sampleLocationsInfos[i][j].sampleLocationsCount > engine :: vulkan :: config :: sampleLocationsInfoSampleLocationsCount ) {
                                __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                                        "config :: sampleLocationsInfoSampleLocationsCount = %d. Minimum Required = %d",
                                        engine :: vulkan :: config :: sampleLocationsInfoSampleLocationsCount,
                                        pContext->sampleLocationsInfos[i][j].sampleLocationsCount
                                ))

                                pContext->sampleLocationsInfos[i][j].sampleLocationsCount = engine :: vulkan :: config :: sampleLocationsInfoSampleLocationsCount;
                            }

                            for ( cds :: uint32 k = 0U; k < pContext->sampleLocationsInfos[j][k].sampleLocationsCount; ++ k ) {
                                pContext->sampleLocations[i][j][k] = {
                                        pSampleLocationsInfo->pSampleLocations[k].x,
                                        pSampleLocationsInfo->pSampleLocations[k].y
                                };
                            }

                            break;

                        }

#endif

                        default:
                            break;
                    }

                    pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
                    pCurrent    = pCurrent->pNext;
                }

                pCurrentVk->pNext = nullptr;
            }

        }

        return & pContext->dependencyInfos[0];
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto prepareContext (
            WaitCommandBufferEventContext         * pContext,
            cds :: uint32                           count,
            Type ( MemoryBarrier )          const * pMemoryBarriers
    ) noexcept -> VkMemoryBarrier * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || count == 0U || pMemoryBarriers == nullptr ) {
            return nullptr;
        }

#endif

        if ( count > engine :: vulkan :: config :: memoryBarrierCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                    "config :: memoryBarrierCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: memoryBarrierCount,
                    count
            ))

            count = engine :: vulkan :: config :: memoryBarrierCount;
        }

        for ( cds :: uint32 i = 0U; i < count; ++ i ) {
            (void) toVulkanFormat ( & pContext->memoryBarriers[i], & pMemoryBarriers[i] );
        }

        return & pContext->memoryBarriers[0];
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto prepareContext (
            WaitCommandBufferEventContext         * pContext,
            cds :: uint32                           count,
            Type ( BufferMemoryBarrier )    const * pBufferMemoryBarriers
    ) noexcept -> VkBufferMemoryBarrier * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || count == 0U || pBufferMemoryBarriers == nullptr ) {
            return nullptr;
        }

#endif

        if ( count > engine :: vulkan :: config :: bufferMemoryBarrierCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                    "config :: bufferMemoryBarrierCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: bufferMemoryBarrierCount,
                    count
            ))

            count = engine :: vulkan :: config :: bufferMemoryBarrierCount;
        }

        for ( cds :: uint32 i = 0U; i < count; ++ i ) {
            (void) toVulkanFormat ( & pContext->bufferMemoryBarriers[i], & pBufferMemoryBarriers[i] );
        }

        return & pContext->bufferMemoryBarriers[0];
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto prepareContext (
            WaitCommandBufferEventContext         * pContext,
            cds :: uint32                           count,
            Type ( ImageMemoryBarrier )     const * pImageMemoryBarriers
    ) noexcept -> VkImageMemoryBarrier * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || count == 0U || pImageMemoryBarriers == nullptr ) {
            return nullptr;
        }

#endif

        if ( count > engine :: vulkan :: config :: imageMemoryBarrierCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                    "config :: imageMemoryBarrierCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: imageMemoryBarrierCount,
                    count
            ))

            count = engine :: vulkan :: config :: imageMemoryBarrierCount;
        }

        for ( cds :: uint32 i = 0U; i < count; ++ i ) {

            auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( & pImageMemoryBarriers[i] );
            auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->imageMemoryBarriers[i], & pImageMemoryBarriers[i] ) );

            while ( pCurrent != nullptr ) {

                switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE

                    case StructureTypeSampleLocationsInfo: {

                        auto pSampleLocationsInfo = reinterpret_cast < Type ( SampleLocationsInfo ) const * > ( pCurrent );
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->sampleLocationsInfos[i],
                                        pSampleLocationsInfo
                                )
                        );

                        pContext->sampleLocationsInfos[i].pSampleLocations = & pContext->sampleLocations[i][0];

                        if ( pContext->sampleLocationsInfos[i].sampleLocationsCount > engine :: vulkan :: config :: sampleLocationsInfoSampleLocationsCount ) {
                            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                                    "config :: sampleLocationsInfoSampleLocationsCount = %d. Minimum Required = %d",
                                    engine :: vulkan :: config :: sampleLocationsInfoSampleLocationsCount,
                                    pContext->sampleLocationsInfos[i].sampleLocationsCount
                            ))

                            pContext->sampleLocationsInfos[i].sampleLocationsCount = engine :: vulkan :: config :: sampleLocationsInfoSampleLocationsCount;
                        }

                        for ( cds :: uint32 j = 0U; j < pContext->sampleLocationsInfos[j].sampleLocationsCount; ++ j ) {
                            pContext->sampleLocations[i][j] = {
                                    pSampleLocationsInfo->pSampleLocations[j].x,
                                    pSampleLocationsInfo->pSampleLocations[j].y
                            };
                        }

                        break;

                    }

#endif

                    default:
                        break;
                }

                pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
                pCurrent    = pCurrent->pNext;
            }

            pCurrentVk->pNext = nullptr;
        }

        return & pContext->imageMemoryBarriers[0];
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE
    auto toVulkanFormat (
            VkRenderingInfo_t            * pDestination,
            Type ( RenderingInfo ) const * pSource
    ) noexcept -> VkRenderingInfo_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                      = VK_STRUCTURE_TYPE_RENDERING_INFO,
                .pNext                      = nullptr,
                .flags                      = pSource->flags,
                .renderArea                 = {
                        .offset                     = {
                                .x                          = pSource->renderArea.offset.x,
                                .y                          = pSource->renderArea.offset.y
                        },
                        .extent                     = {
                                .width                      = pSource->renderArea.extent.width,
                                .height                     = pSource->renderArea.extent.height
                        }
                },
                .layerCount                 = pSource->layerCount,
                .viewMask                   = pSource->viewMask,
                .colorAttachmentCount       = pSource->colorAttachmentCount,
                .pColorAttachments          = nullptr,
                .pDepthAttachment           = nullptr,
                .pStencilAttachment         = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE
    auto toVulkanFormat (
            VkRenderingAttachmentInfo_t            * pDestination,
            Type ( RenderingAttachmentInfo ) const * pSource
    ) noexcept -> VkRenderingAttachmentInfo_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType                      = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO;
        pDestination->pNext                      = nullptr;
        pDestination->imageView                  = pSource->imageView;
        pDestination->imageLayout                = static_cast < VkImageLayout > ( pSource->imageLayout );
        pDestination->resolveMode                = static_cast < VkResolveModeFlagBits > ( pSource->resolveMode );
        pDestination->resolveImageView           = pSource->resolveImageView;
        pDestination->resolveImageLayout         = static_cast < VkImageLayout > ( pSource->resolveImageLayout );
        pDestination->loadOp                     = static_cast < VkAttachmentLoadOp > ( pSource->loadOperation );
        pDestination->storeOp                    = static_cast < VkAttachmentStoreOp > ( pSource->storeOperation );

        (void) std :: memcpy ( & pDestination->clearValue, & pSource->clearValue, sizeof ( VkClearValue ) );

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto toVulkanFormat (
            VkDeviceGroupRenderPassBeginInfo              * pDestination,
            Type ( DeviceGroupRenderPassBeginInfo ) const * pSource
    ) noexcept -> VkDeviceGroupRenderPassBeginInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                      = VK_STRUCTURE_TYPE_DEVICE_GROUP_RENDER_PASS_BEGIN_INFO,
                .pNext                      = nullptr,
                .deviceMask                 = pSource->deviceMask,
                .deviceRenderAreaCount      = pSource->deviceRenderAreaCount,
                .pDeviceRenderAreas         = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE && ( __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE )
    auto toVulkanFormat (
            VkRenderingFragmentDensityMapAttachmentInfoEXT           * pDestination,
            Type ( RenderingFragmentDensityMapAttachmentInfo ) const * pSource
    ) noexcept -> VkRenderingFragmentDensityMapAttachmentInfoEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                      = VK_STRUCTURE_TYPE_RENDERING_FRAGMENT_DENSITY_MAP_ATTACHMENT_INFO_EXT,
                .pNext                      = nullptr,
                .imageView                  = pSource->imageView,
                .imageLayout                = static_cast < VkImageLayout > ( pSource->imageLayout )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE && ( __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE )
    auto toVulkanFormat (
            VkRenderingFragmentShadingRateAttachmentInfoKHR           * pDestination,
            Type ( RenderingFragmentShadingRateAttachmentInfo ) const * pSource
    ) noexcept -> VkRenderingFragmentShadingRateAttachmentInfoKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                          = VK_STRUCTURE_TYPE_RENDERING_FRAGMENT_SHADING_RATE_ATTACHMENT_INFO_KHR,
                .pNext                          = nullptr,
                .imageView                      = pSource->imageView,
                .imageLayout                    = static_cast < VkImageLayout > ( pSource->imageLayout ),
                .shadingRateAttachmentTexelSize = {
                        .width                          = pSource->shadingRateAttachmentTexelSize.width,
                        .height                         = pSource->shadingRateAttachmentTexelSize.height
                }
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE
    auto prepareContext (
            BeginCommandBufferRenderingContext        * pContext,
            Type ( RenderingInfo )              const * pRenderingInfo
    ) noexcept -> VkRenderingInfo_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pRenderingInfo == nullptr ) {
            return nullptr;
        }

#endif

        auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pRenderingInfo->pNext );
        auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->info, pRenderingInfo ) );

        while ( pCurrent != nullptr ) {

            switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

                case StructureTypeDeviceGroupRenderPassBeginInfo: {

                    auto pDeviceGroupRenderPassBeginInfo = reinterpret_cast < Type ( DeviceGroupRenderPassBeginInfo ) const * > ( pCurrent );
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->deviceGroupRenderPassBeginInfo,
                                    pDeviceGroupRenderPassBeginInfo
                            )
                    );

                    pContext->deviceGroupRenderPassBeginInfo.pDeviceRenderAreas = & pContext->deviceRenderAreas[0];

                    if ( pContext->deviceGroupRenderPassBeginInfo.deviceRenderAreaCount > engine :: vulkan :: config :: deviceGroupRenderPassBeginDeviceRenderAreaCount ) {
                        __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                                "config :: deviceGroupRenderPassBeginDeviceRenderAreaCount = %d. Minimum Required = %d",
                                engine :: vulkan :: config :: deviceGroupRenderPassBeginDeviceRenderAreaCount,
                                pContext->deviceGroupRenderPassBeginInfo.deviceRenderAreaCount
                        ))

                        pContext->deviceGroupRenderPassBeginInfo.deviceRenderAreaCount = engine :: vulkan :: config :: deviceGroupRenderPassBeginDeviceRenderAreaCount;
                    }

                    for ( cds :: uint32 i = 0U; i < pContext->deviceGroupRenderPassBeginInfo.deviceRenderAreaCount; ++ i ) {
                        pContext->deviceRenderAreas[i] = {
                                .offset = {
                                        .x      = pDeviceGroupRenderPassBeginInfo->pDeviceRenderAreas[i].offset.x,
                                        .y      = pDeviceGroupRenderPassBeginInfo->pDeviceRenderAreas[i].offset.y
                                },
                                .extent = {
                                        .width  = pDeviceGroupRenderPassBeginInfo->pDeviceRenderAreas[i].extent.width,
                                        .height = pDeviceGroupRenderPassBeginInfo->pDeviceRenderAreas[i].extent.height
                                }
                        };
                    }

                    break;
                }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE && ( __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE )

                case StructureTypeMultiviewPerViewAttributesInfoNVidiaExperimental:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->multiviewPerViewAttributesInfo,
                                    reinterpret_cast < Type ( MultiviewPerViewAttributesInfoNVidia ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE && ( __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE )

                case StructureTypeRenderingFragmentDensityMapAttachmentInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->densityMapAttachmentInfo,
                                    reinterpret_cast < Type ( RenderingFragmentDensityMapAttachmentInfo ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE && ( __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE )

                case StructureTypeRenderingFragmentShadingRateAttachmentInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->fragmentShadingRateAttachmentInfo,
                                    reinterpret_cast < Type ( RenderingFragmentShadingRateAttachmentInfo ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

                default:
                    break;
            }

            pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
            pCurrent    = pCurrent->pNext;
        }

        pCurrentVk->pNext = nullptr;

        pContext->info.pColorAttachments = & pContext->colorAttachments[0];

        if ( pContext->info.colorAttachmentCount > engine :: vulkan :: config :: renderingInfoColorAttachmentCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                    "config :: renderingInfoColorAttachmentCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: renderingInfoColorAttachmentCount,
                    pContext->info.colorAttachmentCount
            ))

            pContext->info.colorAttachmentCount = engine :: vulkan :: config :: renderingInfoColorAttachmentCount;
        }

        for ( cds :: uint32 i = 0U; i < pContext->info.colorAttachmentCount; ++ i ) {
            (void) toVulkanFormat ( & pContext->colorAttachments[i], & pRenderingInfo->pColorAttachments[i] );
        }

        if ( pRenderingInfo->pDepthAttachment != nullptr ) {
            pContext->info.pDepthAttachment = & pContext->depthAttachment;
            (void) toVulkanFormat ( & pContext->depthAttachment, pRenderingInfo->pDepthAttachment );
        }

        if ( pRenderingInfo->pStencilAttachment != nullptr ) {
            pContext->info.pStencilAttachment = & pContext->stencilAttachment;
            (void) toVulkanFormat ( & pContext->stencilAttachment, pRenderingInfo->pStencilAttachment );
        }

        return & pContext->info;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkRenderPassCreateInfo              * pDestination,
            Type ( RenderPassCreateInfo ) const * pSource
    ) noexcept -> VkRenderPassCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                          = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
                .pNext                          = nullptr,
                .flags                          = pSource->flags,
                .attachmentCount                = pSource->attachmentCount,
                .pAttachments                   = nullptr,
                .subpassCount                   = pSource->subpassCount,
                .pSubpasses                     = nullptr,
                .dependencyCount                = pSource->dependencyCount,
                .pDependencies                  = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE
    auto toVulkanFormat (
            VkRenderPassFragmentDensityMapCreateInfoEXT           * pDestination,
            Type ( RenderPassFragmentDensityMapCreateInfo ) const * pSource
    ) noexcept -> VkRenderPassFragmentDensityMapCreateInfoEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                          = VK_STRUCTURE_TYPE_RENDER_PASS_FRAGMENT_DENSITY_MAP_CREATE_INFO_EXT,
                .pNext                          = nullptr,
                .fragmentDensityMapAttachment   = {
                        .attachment                     = pSource->fragmentDensityMapAttachment.attachment,
                        .layout                         = static_cast < VkImageLayout > ( pSource->fragmentDensityMapAttachment.layout )
                }
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto toVulkanFormat (
            VkRenderPassInputAttachmentAspectCreateInfo              * pDestination,
            Type ( RenderPassInputAttachmentAspectCreateInfo ) const * pSource
    ) noexcept -> VkRenderPassInputAttachmentAspectCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                          = VK_STRUCTURE_TYPE_RENDER_PASS_INPUT_ATTACHMENT_ASPECT_CREATE_INFO,
                .pNext                          = nullptr,
                .aspectReferenceCount           = pSource->aspectReferenceCount,
                .pAspectReferences              = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto toVulkanFormat (
            VkInputAttachmentAspectReference              * pDestination,
            Type ( InputAttachmentAspectReference ) const * pSource
    ) noexcept -> VkInputAttachmentAspectReference * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .subpass                = pSource->subpass,
                .inputAttachmentIndex   = pSource->inputAttachmentIndex,
                .aspectMask             = pSource->aspectMask
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto toVulkanFormat (
            VkRenderPassMultiviewCreateInfo              * pDestination,
            Type ( RenderPassMultiviewCreateInfo ) const * pSource
    ) noexcept -> VkRenderPassMultiviewCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_RENDER_PASS_MULTIVIEW_CREATE_INFO,
                .pNext                  = nullptr,
                .subpassCount           = pSource->subpassCount,
                .pViewMasks             = pSource->pViewMasks,
                .dependencyCount        = pSource->dependencyCount,
                .pViewOffsets           = pSource->pViewOffsets,
                .correlationMaskCount   = pSource->correlationMaskCount,
                .pCorrelationMasks      = pSource->pCorrelationMasks
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkAttachmentDescription              * pDestination,
            Type ( AttachmentDescription ) const * pSource
    ) noexcept -> VkAttachmentDescription * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .flags          = pSource->flags,
                .format         = static_cast < VkFormat > ( pSource->format ),
                .samples        = static_cast < VkSampleCountFlagBits > ( pSource->samples ),
                .loadOp         = static_cast < VkAttachmentLoadOp > ( pSource->loadOperation ),
                .storeOp        = static_cast < VkAttachmentStoreOp > ( pSource->storeOperation ),
                .stencilLoadOp  = static_cast < VkAttachmentLoadOp > ( pSource->stencilLoadOperation ),
                .stencilStoreOp = static_cast < VkAttachmentStoreOp > ( pSource->stencilStoreOperation ),
                .initialLayout  = static_cast < VkImageLayout > ( pSource->initialLayout ),
                .finalLayout    = static_cast < VkImageLayout > ( pSource->finalLayout )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkSubpassDescription              * pDestination,
            Type ( SubpassDescription ) const * pSource
    ) noexcept -> VkSubpassDescription * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .flags                      = pSource->flags,
                .pipelineBindPoint          = static_cast < VkPipelineBindPoint > ( pSource->pipelineBindPoint ),
                .inputAttachmentCount       = pSource->inputAttachmentCount,
                .pInputAttachments          = nullptr,
                .colorAttachmentCount       = pSource->colorAttachmentsCount,
                .pColorAttachments          = nullptr,
                .pResolveAttachments        = nullptr,
                .pDepthStencilAttachment    = nullptr,
                .preserveAttachmentCount    = pSource->preserveAttachmentCount,
                .pPreserveAttachments       = pSource->pPreserveAttachments
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkSubpassDependency              * pDestination,
            Type ( SubpassDependency ) const * pSource
    ) noexcept -> VkSubpassDependency * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .srcSubpass         = pSource->sourceSubpass,
                .dstSubpass         = pSource->destinationSubpass,
                .srcStageMask       = static_cast < VkPipelineStageFlags > ( pSource->sourceStageMask ),
                .dstStageMask       = static_cast < VkPipelineStageFlags > ( pSource->destinationStageMask ),
                .srcAccessMask      = static_cast < VkAccessFlags > ( pSource->sourceAccessMask ),
                .dstAccessMask      = static_cast < VkAccessFlags > ( pSource->destinationAccessMask ),
                .dependencyFlags    = pSource->dependencyFlags
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkAttachmentReference              * pDestination,
            Type ( AttachmentReference ) const * pSource
    ) noexcept -> VkAttachmentReference * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .attachment = pSource->attachment,
                .layout     = static_cast < VkImageLayout > ( pSource->layout )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    auto toVulkanFormat (
            VkRenderPassCreateInfo2              * pDestination,
            Type ( RenderPassCreateInfo2 ) const * pSource
    ) noexcept -> VkRenderPassCreateInfo2 * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                      = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO_2,
                .pNext                      = nullptr,
                .flags                      = pSource->flags,
                .attachmentCount            = pSource->attachmentCount,
                .pAttachments               = nullptr,
                .subpassCount               = pSource->subpassCount,
                .pSubpasses                 = nullptr,
                .dependencyCount            = pSource->dependencyCount,
                .pDependencies              = nullptr,
                .correlatedViewMaskCount    = pSource->correlatedViewMaskCount,
                .pCorrelatedViewMasks       = pSource->pCorrelatedViewMasks
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    auto toVulkanFormat (
            VkAttachmentDescription2              * pDestination,
            Type ( AttachmentDescription2 ) const * pSource
    ) noexcept -> VkAttachmentDescription2 * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                      = VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_2,
                .pNext                      = nullptr,
                .flags                      = pSource->flags,
                .format                     = static_cast < VkFormat > ( pSource->format ),
                .samples                    = static_cast < VkSampleCountFlagBits > ( pSource->samples ),
                .loadOp                     = static_cast < VkAttachmentLoadOp > ( pSource->loadOperation ),
                .storeOp                    = static_cast < VkAttachmentStoreOp > ( pSource->storeOperation ),
                .stencilLoadOp              = static_cast < VkAttachmentLoadOp > ( pSource->stencilLoadOperation ),
                .stencilStoreOp             = static_cast < VkAttachmentStoreOp > ( pSource->stencilStoreOperation ),
                .initialLayout              = static_cast < VkImageLayout > ( pSource->initialLayout ),
                .finalLayout                = static_cast < VkImageLayout > ( pSource->finalLayout )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    auto toVulkanFormat (
            VkAttachmentDescriptionStencilLayout              * pDestination,
            Type ( AttachmentDescriptionStencilLayout ) const * pSource
    ) noexcept -> VkAttachmentDescriptionStencilLayout * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                      = VK_STRUCTURE_TYPE_ATTACHMENT_DESCRIPTION_STENCIL_LAYOUT,
                .pNext                      = nullptr,
                .stencilInitialLayout       = static_cast < VkImageLayout > ( pSource->stencilInitialLayout ),
                .stencilFinalLayout         = static_cast < VkImageLayout > ( pSource->stencilFinalLayout )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    auto toVulkanFormat (
            VkAttachmentReferenceStencilLayout              * pDestination,
            Type ( AttachmentReferenceStencilLayout ) const * pSource
    ) noexcept -> VkAttachmentReferenceStencilLayout * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                      = VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_STENCIL_LAYOUT,
                .pNext                      = nullptr,
                .stencilLayout              = static_cast < VkImageLayout > ( pSource->stencilLayout )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    auto toVulkanFormat (
            VkAttachmentReference2              * pDestination,
            Type ( AttachmentReference2 ) const * pSource
    ) noexcept -> VkAttachmentReference2 * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                      = VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_2,
                .pNext                      = nullptr,
                .attachment                 = pSource->attachment,
                .layout                     = static_cast < VkImageLayout > ( pSource->layout ),
                .aspectMask                 = pSource->aspectMask
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    auto toVulkanFormat (
            VkSubpassDescription2              * pDestination,
            Type ( SubpassDescription2 ) const * pSource
    ) noexcept -> VkSubpassDescription2 * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                      = VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_2,
                .pNext                      = nullptr,
                .flags                      = pSource->flags,
                .pipelineBindPoint          = static_cast < VkPipelineBindPoint > ( pSource->pipelineBindPoint ),
                .viewMask                   = pSource->viewMask,
                .inputAttachmentCount       = pSource->inputAttachmentCount,
                .pInputAttachments          = nullptr,
                .colorAttachmentCount       = pSource->colorAttachmentsCount,
                .pColorAttachments          = nullptr,
                .pResolveAttachments        = nullptr,
                .pDepthStencilAttachment    = nullptr,
                .preserveAttachmentCount    = pSource->preserveAttachmentCount,
                .pPreserveAttachments       = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    auto toVulkanFormat (
            VkSubpassDescriptionDepthStencilResolve              * pDestination,
            Type ( SubpassDescriptionDepthStencilResolve ) const * pSource
    ) noexcept -> VkSubpassDescriptionDepthStencilResolve * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                          = VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_DEPTH_STENCIL_RESOLVE,
                .pNext                          = nullptr,
                .depthResolveMode               = static_cast < VkResolveModeFlagBits > ( pSource->depthResolveMode ),
                .stencilResolveMode             = static_cast < VkResolveModeFlagBits > ( pSource->stencilResolveMode ),
                .pDepthStencilResolveAttachment = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    auto toVulkanFormat (
            VkSubpassDependency2              * pDestination,
            Type ( SubpassDependency2 ) const * pSource
    ) noexcept -> VkSubpassDependency2 * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                          = VK_STRUCTURE_TYPE_SUBPASS_DEPENDENCY_2,
                .pNext                          = nullptr,
                .srcSubpass                     = pSource->sourceSubpass,
                .dstSubpass                     = pSource->destinationSubpass,
                .srcStageMask                   = static_cast < VkPipelineStageFlags > ( pSource->sourceStageMask ),
                .dstStageMask                   = static_cast < VkPipelineStageFlags > ( pSource->destinationStageMask ),
                .srcAccessMask                  = static_cast < VkAccessFlags > ( pSource->sourceAccessMask ),
                .dstAccessMask                  = static_cast < VkAccessFlags > ( pSource->destinationAccessMask ),
                .dependencyFlags                = pSource->dependencyFlags,
                .viewOffset                     = pSource->viewOffset
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE
    auto toVulkanFormat (
            VkFragmentShadingRateAttachmentInfoKHR              * pDestination,
            Type ( FragmentShadingRateAttachmentInfo ) const * pSource
    ) noexcept -> VkFragmentShadingRateAttachmentInfoKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                          = VK_STRUCTURE_TYPE_FRAGMENT_SHADING_RATE_ATTACHMENT_INFO_KHR,
                .pNext                          = nullptr,
                .pFragmentShadingRateAttachment = nullptr,
                .shadingRateAttachmentTexelSize = {
                        .width                          = pSource->shadingRateAttachmentTexelSize.width,
                        .height                         = pSource->shadingRateAttachmentTexelSize.height
                }
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto prepareContext (
            CreateRenderPassContext               * pContext,
            Type ( RenderPassCreateInfo )   const * pSource
    ) noexcept -> VkRenderPassCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pNext );
        auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->createInfo, pSource ) );

        while ( pCurrent != nullptr ) {

            switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

                case StructureTypeRenderPassFragmentDensityMapCreateInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->fragmentDensityMapCreateInfo,
                                    reinterpret_cast < Type ( RenderPassFragmentDensityMapCreateInfo ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

                case StructureTypeRenderPassInputAttachmentAspectCreateInfo: {

                    auto pInputAttachmentAspectCreateInfo = reinterpret_cast < Type ( RenderPassInputAttachmentAspectCreateInfo ) const * > ( pCurrent );
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->inputAttachmentAspectCreateInfo,
                                    pInputAttachmentAspectCreateInfo
                            )
                    );

                    pContext->inputAttachmentAspectCreateInfo.pAspectReferences = & pContext->inputAttachmentAspectReferences[0];

                    if ( pContext->inputAttachmentAspectCreateInfo.aspectReferenceCount > engine :: vulkan :: config :: renderPassInputAttachmentAspectReferenceCount ) {
                        __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                                "config :: renderPassInputAttachmentAspectReferenceCount = %d. Minimum Required = %d",
                                engine :: vulkan :: config :: renderPassInputAttachmentAspectReferenceCount,
                                pContext->inputAttachmentAspectCreateInfo.aspectReferenceCount
                        ))

                        pContext->inputAttachmentAspectCreateInfo.aspectReferenceCount = engine :: vulkan :: config :: renderPassInputAttachmentAspectReferenceCount;
                    }

                    for ( cds :: uint32 i = 0U; i < pContext->inputAttachmentAspectCreateInfo.aspectReferenceCount; ++ i ) {
                        (void) toVulkanFormat ( & pContext->inputAttachmentAspectReferences[i], & pInputAttachmentAspectCreateInfo->pAspectReferences[i] );
                    }

                    break;
                }

                case StructureTypeRenderPassMultiviewCreateInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->multiviewCreateInfo,
                                    reinterpret_cast < Type ( RenderPassMultiviewCreateInfo ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

                default:
                    break;
            }

            pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
            pCurrent    = pCurrent->pNext;
        }

        pCurrentVk->pNext = nullptr;

        pContext->createInfo.pAttachments = & pContext->attachmentDescriptions[0];

        if ( pContext->createInfo.attachmentCount > engine :: vulkan :: config :: renderPassAttachmentDescriptionCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                    "config :: renderPassAttachmentDescriptionCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: renderPassAttachmentDescriptionCount,
                    pContext->createInfo.attachmentCount
            ))

            pContext->createInfo.attachmentCount = engine :: vulkan :: config :: renderPassAttachmentDescriptionCount;
        }

        for ( cds :: uint32 i = 0U; i < pContext->createInfo.attachmentCount; ++ i ) {
            (void) toVulkanFormat ( & pContext->attachmentDescriptions[i], & pSource->pAttachments[i] );
        }

        pContext->createInfo.pSubpasses = & pContext->subpassDescriptions[0];

        if ( pContext->createInfo.subpassCount > engine :: vulkan :: config :: renderPassSubpassDescriptionCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                    "config :: renderPassSubpassDescriptionCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: renderPassSubpassDescriptionCount,
                    pContext->createInfo.subpassCount
            ))

            pContext->createInfo.subpassCount = engine :: vulkan :: config :: renderPassSubpassDescriptionCount;
        }

        for ( cds :: uint32 i = 0U; i < pContext->createInfo.subpassCount; ++ i ) {
            (void) toVulkanFormat ( & pContext->subpassDescriptions[i], & pSource->pSubpasses[i] );

            pContext->subpassDescriptions[i].pInputAttachments = & pContext->inputAttachments[i][0];

            if ( pContext->subpassDescriptions[i].inputAttachmentCount > engine :: vulkan :: config :: renderPassSubpassDescriptionInputAttachmentCount ) {
                __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                        "config :: renderPassSubpassDescriptionInputAttachmentCount = %d. Minimum Required = %d",
                        engine :: vulkan :: config :: renderPassSubpassDescriptionInputAttachmentCount,
                        pContext->subpassDescriptions[i].inputAttachmentCount
                ))

                pContext->subpassDescriptions[i].inputAttachmentCount = engine :: vulkan :: config :: renderPassSubpassDescriptionInputAttachmentCount;
            }

            for ( cds :: uint32 j = 0U; j < pContext->subpassDescriptions[i].inputAttachmentCount; ++ j ) {
                (void) toVulkanFormat ( & pContext->inputAttachments[i][j], & pSource->pSubpasses[i].pInputAttachments[j] );
            }

            pContext->subpassDescriptions[i].pColorAttachments = & pContext->colorAttachments[i][0];
            pContext->subpassDescriptions[i].pResolveAttachments = & pContext->resolveAttachments[i][0];

            if ( pContext->subpassDescriptions[i].colorAttachmentCount > engine :: vulkan :: config :: renderPassSubpassDescriptionColorAttachmentCount ) {
                __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                        "config :: renderPassSubpassDescriptionColorAttachmentCount = %d. Minimum Required = %d",
                        engine :: vulkan :: config :: renderPassSubpassDescriptionColorAttachmentCount,
                        pContext->subpassDescriptions[i].colorAttachmentCount
                ))

                pContext->subpassDescriptions[i].colorAttachmentCount = engine :: vulkan :: config :: renderPassSubpassDescriptionColorAttachmentCount;
            }

            for ( cds :: uint32 j = 0U; j < pContext->subpassDescriptions[i].colorAttachmentCount; ++ j ) {
                (void) toVulkanFormat ( & pContext->colorAttachments[i][j], & pSource->pSubpasses[i].pColorAttachments[j] );
                (void) toVulkanFormat ( & pContext->resolveAttachments[i][j], & pSource->pSubpasses[i].pResolveAttachments[j] );
            }

            if ( pSource->pSubpasses[i].pDepthStencilAttachment != nullptr ) {
                pContext->subpassDescriptions[i].pDepthStencilAttachment = toVulkanFormat ( & pContext->depthStencilAttachments[i], pSource->pSubpasses[i].pDepthStencilAttachment );
            }
        }

        pContext->createInfo.pDependencies = & pContext->subpassDependencies[0];

        if ( pContext->createInfo.dependencyCount > engine :: vulkan :: config :: renderPassSubpassDependencyCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                    "config :: renderPassSubpassDependencyCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: renderPassSubpassDependencyCount,
                    pContext->createInfo.dependencyCount
            ))

            pContext->createInfo.dependencyCount = engine :: vulkan :: config :: renderPassSubpassDependencyCount;
        }

        for ( cds :: uint32 i = 0U; i < pContext->createInfo.dependencyCount; ++ i ) {
            (void) toVulkanFormat ( & pContext->subpassDependencies[i], & pSource->pDependencies[i] );
        }

        return & pContext->createInfo;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    auto prepareContext (
            CreateRenderPass2Context               * pContext,
            Type ( RenderPassCreateInfo2 )   const * pSource
    ) noexcept -> VkRenderPassCreateInfo2 * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pNext );
        auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->createInfo, pSource ) );

        while ( pCurrent != nullptr ) {

            switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

                case StructureTypeRenderPassFragmentDensityMapCreateInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->fragmentDensityMapCreateInfo,
                                    reinterpret_cast < Type ( RenderPassFragmentDensityMapCreateInfo ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

                default:
                    break;
            }

            pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
            pCurrent    = pCurrent->pNext;
        }

        pCurrentVk->pNext = nullptr;

        pContext->createInfo.pAttachments = & pContext->attachmentDescriptions[0];

        if ( pContext->createInfo.attachmentCount > engine :: vulkan :: config :: renderPassAttachmentDescriptionCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                    "config :: renderPassAttachmentDescriptionCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: renderPassAttachmentDescriptionCount,
                    pContext->createInfo.attachmentCount
            ))

            pContext->createInfo.attachmentCount = engine :: vulkan :: config :: renderPassAttachmentDescriptionCount;
        }

        for ( cds :: uint32 i = 0U; i < pContext->createInfo.attachmentCount; ++ i ) {

            pCurrent    = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pAttachments[i].pNext );
            pCurrentVk  = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->attachmentDescriptions[i], & pSource->pAttachments[i] ) );

            while ( pCurrent != nullptr ) {

                switch ( pCurrent->structureType ) {

                    case StructureTypeAttachmentDescriptionStencilLayout:
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->attachmentDescriptionStencilLayouts[i],
                                        reinterpret_cast < Type ( AttachmentDescriptionStencilLayout ) const * > ( pCurrent )
                                )
                        );
                        break;

                    default:
                        break;
                }

                pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
                pCurrent    = pCurrent->pNext;
            }

            pCurrentVk->pNext = nullptr;
        }

        pContext->createInfo.pSubpasses = & pContext->subpassDescriptions[0];

        if ( pContext->createInfo.subpassCount > engine :: vulkan :: config :: renderPassSubpassDescriptionCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                    "config :: renderPassSubpassDescriptionCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: renderPassSubpassDescriptionCount,
                    pContext->createInfo.subpassCount
            ))

            pContext->createInfo.subpassCount = engine :: vulkan :: config :: renderPassSubpassDescriptionCount;
        }

        for ( cds :: uint32 i = 0U; i < pContext->createInfo.subpassCount; ++ i ) {

            pCurrentVk  = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->subpassDescriptions[i], & pSource->pSubpasses[i] ) );
            pCurrent    = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pSubpasses[i].pNext );

            while ( pCurrent != nullptr ) {

                switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE

                    case StructureTypeFragmentShadingRateAttachmentInfo: {

                        auto pFragmentShadingRateAttachmentInfo = reinterpret_cast < Type ( FragmentShadingRateAttachmentInfo ) const * > ( pCurrent );
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->fragmentShadingRateAttachmentInfos[i],
                                        pFragmentShadingRateAttachmentInfo
                                )
                        );

                        if ( pFragmentShadingRateAttachmentInfo->pFragmentShadingRateAttachment != nullptr ) {
                            pContext->fragmentShadingRateAttachmentInfos[i].pFragmentShadingRateAttachment = toVulkanFormat ( & pContext->fragmentShadingRateAttachmentReferences[i], pFragmentShadingRateAttachmentInfo->pFragmentShadingRateAttachment );
                        }

                        break;
                    }

#endif

                    case StructureTypeSubpassDescriptionDepthStencilResolve: {

                        auto pSubpassDescriptionDepthStencilResolve = reinterpret_cast < Type ( SubpassDescriptionDepthStencilResolve ) const * > ( pCurrent );
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->subpassDescriptionDepthStencilResolve[i],
                                        pSubpassDescriptionDepthStencilResolve
                                )
                        );

                        if ( pSubpassDescriptionDepthStencilResolve->pDepthStencilResolveAttachment != nullptr ) {
                            pContext->subpassDescriptionDepthStencilResolve[i].pDepthStencilResolveAttachment = toVulkanFormat ( & pContext->subpassDescriptionDepthStencilReferences[i], pSubpassDescriptionDepthStencilResolve->pDepthStencilResolveAttachment );
                        }

                        break;
                    }

                    default:
                        break;
                }

                pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
                pCurrent    = pCurrent->pNext;
            }

            pCurrentVk->pNext = nullptr;

            pContext->subpassDescriptions[i].pInputAttachments = & pContext->inputAttachments[i][0];

            if ( pContext->subpassDescriptions[i].inputAttachmentCount > engine :: vulkan :: config :: renderPassSubpassDescriptionInputAttachmentCount ) {
                __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                        "config :: renderPassSubpassDescriptionInputAttachmentCount = %d. Minimum Required = %d",
                        engine :: vulkan :: config :: renderPassSubpassDescriptionInputAttachmentCount,
                        pContext->subpassDescriptions[i].inputAttachmentCount
                ))

                pContext->subpassDescriptions[i].inputAttachmentCount = engine :: vulkan :: config :: renderPassSubpassDescriptionInputAttachmentCount;
            }

            for ( cds :: uint32 j = 0U; j < pContext->subpassDescriptions[i].inputAttachmentCount; ++ j ) {

                pCurrentVk  = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->inputAttachments[i][j], & pSource->pSubpasses[i].pInputAttachments[j] ) );
                pCurrent    = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pSubpasses[i].pInputAttachments[j].pNext );

                while ( pCurrent != nullptr ) {

                    switch ( pCurrent->structureType ) {

                        case StructureTypeAttachmentReferenceStencilLayout:
                            pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                    toVulkanFormat (
                                            & pContext->inputAttachmentsReferenceStencilLayouts[i][j],
                                            reinterpret_cast < Type ( AttachmentReferenceStencilLayout ) const * > ( pCurrent )
                                    )
                            );
                            break;

                        default:
                            break;
                    }

                    pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
                    pCurrent    = pCurrent->pNext;
                }

                pCurrentVk->pNext = nullptr;
            }

            pContext->subpassDescriptions[i].pColorAttachments = & pContext->colorAttachments[i][0];
            pContext->subpassDescriptions[i].pResolveAttachments = & pContext->resolveAttachments[i][0];

            if ( pContext->subpassDescriptions[i].colorAttachmentCount > engine :: vulkan :: config :: renderPassSubpassDescriptionColorAttachmentCount ) {
                __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                        "config :: renderPassSubpassDescriptionColorAttachmentCount = %d. Minimum Required = %d",
                        engine :: vulkan :: config :: renderPassSubpassDescriptionColorAttachmentCount,
                        pContext->subpassDescriptions[i].colorAttachmentCount
                ))

                pContext->subpassDescriptions[i].colorAttachmentCount = engine :: vulkan :: config :: renderPassSubpassDescriptionColorAttachmentCount;
            }

            for ( cds :: uint32 j = 0U; j < pContext->subpassDescriptions[i].colorAttachmentCount; ++ j ) {

                pCurrentVk  = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->colorAttachments[i][j], & pSource->pSubpasses[i].pColorAttachments[j] ) );
                pCurrent    = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pSubpasses[i].pColorAttachments[j].pNext );

                while ( pCurrent != nullptr ) {

                    switch ( pCurrent->structureType ) {

                        case StructureTypeAttachmentReferenceStencilLayout:
                            pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                    toVulkanFormat (
                                            & pContext->colorAttachmentsReferenceStencilLayouts[i][j],
                                            reinterpret_cast < Type ( AttachmentReferenceStencilLayout ) const * > ( pCurrent )
                                    )
                            );
                            break;

                        default:
                            break;
                    }

                    pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
                    pCurrent    = pCurrent->pNext;
                }

                pCurrentVk->pNext = nullptr;

                pCurrentVk  = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->resolveAttachments[i][j], & pSource->pSubpasses[i].pResolveAttachments[j] ) );
                pCurrent    = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pSubpasses[i].pResolveAttachments[j].pNext );

                while ( pCurrent != nullptr ) {

                    switch ( pCurrent->structureType ) {

                        case StructureTypeAttachmentReferenceStencilLayout:
                            pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                    toVulkanFormat (
                                            & pContext->resolveAttachmentsReferenceStencilLayouts[i][j],
                                            reinterpret_cast < Type ( AttachmentReferenceStencilLayout ) const * > ( pCurrent )
                                    )
                            );
                            break;

                        default:
                            break;
                    }

                    pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
                    pCurrent    = pCurrent->pNext;
                }

                pCurrentVk->pNext = nullptr;
            }

            if ( pSource->pSubpasses[i].pDepthStencilAttachment != nullptr ) {
                pContext->subpassDescriptions[i].pDepthStencilAttachment = toVulkanFormat ( & pContext->depthStencilAttachments[i], pSource->pSubpasses[i].pDepthStencilAttachment );

                pCurrentVk  = reinterpret_cast < VkBaseOutStructure * > ( & pContext->depthStencilAttachments[i] );
                pCurrent    = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pSubpasses[i].pDepthStencilAttachment );

                while ( pCurrent != nullptr ) {

                    switch ( pCurrent->structureType ) {

                        case StructureTypeAttachmentReferenceStencilLayout:
                            pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                    toVulkanFormat (
                                            & pContext->depthStencilAttachmentsReferenceStencilLayouts[i],
                                            reinterpret_cast < Type ( AttachmentReferenceStencilLayout ) const * > ( pCurrent )
                                    )
                            );
                            break;

                        default:
                            break;
                    }

                    pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
                    pCurrent    = pCurrent->pNext;
                }

                pCurrentVk->pNext = nullptr;
            }
        }

        pContext->createInfo.pDependencies = & pContext->subpassDependencies[0];

        if ( pContext->createInfo.dependencyCount > engine :: vulkan :: config :: renderPassSubpassDependencyCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                    "config :: renderPassSubpassDependencyCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: renderPassSubpassDependencyCount,
                    pContext->createInfo.dependencyCount
            ))

            pContext->createInfo.dependencyCount = engine :: vulkan :: config :: renderPassSubpassDependencyCount;
        }

        for ( cds :: uint32 i = 0U; i < pContext->createInfo.dependencyCount; ++ i ) {

            pCurrentVk  = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->subpassDependencies[i], & pSource->pDependencies[i] ) );
            pCurrent    = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pDependencies[i].pNext );

            while ( pCurrent != nullptr ) {

                switch ( pCurrent->structureType ) {

                    case StructureTypeMemoryBarrier2:
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->memoryBarriers[i],
                                        reinterpret_cast < Type ( MemoryBarrier2 ) const * > ( pCurrent )
                                )
                        );
                        break;

                    default:
                        break;
                }

                pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
                pCurrent    = pCurrent->pNext;
            }

            pCurrentVk->pNext = nullptr;
        }

        return & pContext->createInfo;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkFramebufferCreateInfo              * pDestination,
            Type ( FrameBufferCreateInfo ) const * pSource
    ) noexcept -> VkFramebufferCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                          = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
                .pNext                          = nullptr,
                .flags                          = pSource->flags,
                .renderPass                     = pSource->renderPass,
                .attachmentCount                = pSource->attachmentCount,
                .pAttachments                   = pSource->pAttachments,
                .width                          = pSource->width,
                .height                         = pSource->height,
                .layers                         = pSource->layers
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    auto toVulkanFormat (
            VkFramebufferAttachmentsCreateInfo              * pDestination,
            Type ( FrameBufferAttachmentsCreateInfo ) const * pSource
    ) noexcept -> VkFramebufferAttachmentsCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                          = VK_STRUCTURE_TYPE_FRAMEBUFFER_ATTACHMENTS_CREATE_INFO,
                .pNext                          = nullptr,
                .attachmentImageInfoCount       = pSource->attachmentImageInfoCount,
                .pAttachmentImageInfos          = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    auto toVulkanFormat (
            VkFramebufferAttachmentImageInfo              * pDestination,
            Type ( FrameBufferAttachmentImageInfo ) const * pSource
    ) noexcept -> VkFramebufferAttachmentImageInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                          = VK_STRUCTURE_TYPE_FRAMEBUFFER_ATTACHMENT_IMAGE_INFO,
                .pNext                          = nullptr,
                .flags                          = pSource->flags,
                .usage                          = pSource->usage,
                .width                          = pSource->width,
                .height                         = pSource->height,
                .layerCount                     = pSource->layerCount,
                .viewFormatCount                = pSource->viewFormatCount,
                .pViewFormats                   = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto prepareContext (
            CreateFrameBufferContext              * pContext,
            Type ( FrameBufferCreateInfo )  const * pSource
    ) noexcept -> VkFramebufferCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pNext );
        auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->createInfo, pSource ) );

        while ( pCurrent != nullptr ) {

            switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

                case StructureTypeFrameBufferAttachmentsCreateInfo: {
                    auto pFrameBufferAttachmentsCreateInfo = reinterpret_cast < Type ( FrameBufferAttachmentsCreateInfo ) const * > ( pCurrent );
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->attachmentsCreateInfo,
                                    pFrameBufferAttachmentsCreateInfo
                            )
                    );

                    pContext->attachmentsCreateInfo.pAttachmentImageInfos = & pContext->attachmentImageInfos[0];

                    if ( pContext->attachmentsCreateInfo.attachmentImageInfoCount > engine :: vulkan :: config :: frameBufferAttachmentsImageInfoCount ) {
                        __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                                "config :: frameBufferAttachmentsImageInfoCount = %d. Minimum Required = %d",
                                engine :: vulkan :: config :: frameBufferAttachmentsImageInfoCount,
                                pContext->attachmentsCreateInfo.attachmentImageInfoCount
                        ))

                        pContext->attachmentsCreateInfo.attachmentImageInfoCount = engine :: vulkan :: config :: frameBufferAttachmentsImageInfoCount;
                    }

                    for ( cds :: uint32 i = 0U; i < pContext->attachmentsCreateInfo.attachmentImageInfoCount; ++ i ) {
                        (void) toVulkanFormat ( & pContext->attachmentImageInfos[i], & pFrameBufferAttachmentsCreateInfo->pAttachmentImageInfos[i] );
                    }

                    break;
                }

#endif

                default:
                    break;
            }

            pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
            pCurrent    = pCurrent->pNext;
        }

        pCurrentVk->pNext = nullptr;

        return & pContext->createInfo;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkRenderPassBeginInfo              * pDestination,
            Type ( RenderPassBeginInfo ) const * pSource
    ) noexcept -> VkRenderPassBeginInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                          = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
                .pNext                          = nullptr,
                .renderPass                     = pSource->renderPass,
                .framebuffer                    = pSource->frameBuffer,
                .renderArea                     = {
                        .offset                         = {
                                .x                              = pSource->renderArea.offset.x,
                                .y                              = pSource->renderArea.offset.y
                        },
                        .extent                         = {
                                .width                          = pSource->renderArea.extent.width,
                                .height                         = pSource->renderArea.extent.height
                        }
                },
                .clearValueCount                = pSource->clearValueCount,
                .pClearValues                   = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    auto toVulkanFormat (
            VkRenderPassAttachmentBeginInfo              * pDestination,
            Type ( RenderPassAttachmentBeginInfo ) const * pSource
    ) noexcept -> VkRenderPassAttachmentBeginInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                          = VK_STRUCTURE_TYPE_RENDER_PASS_ATTACHMENT_BEGIN_INFO,
                .pNext                          = nullptr,
                .attachmentCount                = pSource->attachmentCount,
                .pAttachments                   = pSource->pAttachments
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE
    auto toVulkanFormat (
            VkRenderPassSampleLocationsBeginInfoEXT              * pDestination,
            Type ( RenderPassSampleLocationsBeginInfo ) const * pSource
    ) noexcept -> VkRenderPassSampleLocationsBeginInfoEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                                  = VK_STRUCTURE_TYPE_RENDER_PASS_SAMPLE_LOCATIONS_BEGIN_INFO_EXT,
                .pNext                                  = nullptr,
                .attachmentInitialSampleLocationsCount  = pSource->attachmentInitialSampleLocationsCount,
                .pAttachmentInitialSampleLocations      = nullptr,
                .postSubpassSampleLocationsCount        = pSource->postSubpassSampleLocationsCount,
                .pPostSubpassSampleLocations            = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_RENDER_PASS_TRANSFORM_AVAILABLE
    auto toVulkanFormat (
            VkRenderPassTransformBeginInfoQCOM              * pDestination,
            Type ( RenderPassTransformBeginInfoQualcomm ) const * pSource
    ) noexcept -> VkRenderPassTransformBeginInfoQCOM * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                                  = VK_STRUCTURE_TYPE_RENDER_PASS_TRANSFORM_BEGIN_INFO_QCOM,
                .pNext                                  = nullptr,
                .transform                              = static_cast < VkSurfaceTransformFlagBitsKHR > ( pSource->transform )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE
    auto toVulkanFormat (
            VkAttachmentSampleLocationsEXT              * pDestination,
            Type ( AttachmentSampleLocations ) const * pSource
    ) noexcept -> VkAttachmentSampleLocationsEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .attachmentIndex            = pSource->attachmentIndex,
                .sampleLocationsInfo        = {
                        .sType                      = VK_STRUCTURE_TYPE_SAMPLE_LOCATIONS_INFO_EXT,
                        .pNext                      = nullptr,
                        .sampleLocationsPerPixel    = static_cast < VkSampleCountFlagBits > ( pSource->sampleLocationsInfo.sampleLocationsPerPixel ),
                        .sampleLocationGridSize     = {
                                .width                      = pSource->sampleLocationsInfo.sampleLocationGridSize.width,
                                .height                     = pSource->sampleLocationsInfo.sampleLocationGridSize.height
                        },
                        .sampleLocationsCount       = pSource->sampleLocationsInfo.sampleLocationsCount,
                        .pSampleLocations           = nullptr
                }
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE
    auto toVulkanFormat (
            VkSubpassSampleLocationsEXT              * pDestination,
            Type ( SubpassSampleLocations ) const * pSource
    ) noexcept -> VkSubpassSampleLocationsEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .subpassIndex               = pSource->subpassIndex,
                .sampleLocationsInfo        = {
                        .sType                      = VK_STRUCTURE_TYPE_SAMPLE_LOCATIONS_INFO_EXT,
                        .pNext                      = nullptr,
                        .sampleLocationsPerPixel    = static_cast < VkSampleCountFlagBits > ( pSource->sampleLocationsInfo.sampleLocationsPerPixel ),
                        .sampleLocationGridSize     = {
                                .width                      = pSource->sampleLocationsInfo.sampleLocationGridSize.width,
                                .height                     = pSource->sampleLocationsInfo.sampleLocationGridSize.height
                        },
                        .sampleLocationsCount       = pSource->sampleLocationsInfo.sampleLocationsCount,
                        .pSampleLocations           = nullptr
                }
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto prepareContext (
            BeginRenderPassContext               * pContext,
            Type ( RenderPassBeginInfo )   const * pSource
    ) noexcept -> VkRenderPassBeginInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pNext );
        auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->beginInfo, pSource ) );

        while ( pCurrent != nullptr ) {

            switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

            case StructureTypeDeviceGroupRenderPassBeginInfo: {
                auto pDeviceGroupRenderPassBeginInfo = reinterpret_cast < Type ( DeviceGroupRenderPassBeginInfo ) const * > ( pCurrent );
                pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->deviceGroupRenderPassBeginInfo,
                                pDeviceGroupRenderPassBeginInfo
                        )
                );

                pContext->deviceGroupRenderPassBeginInfo.pDeviceRenderAreas = & pContext->deviceGroupDeviceRenderAreas[0];

                if ( pContext->deviceGroupRenderPassBeginInfo.deviceRenderAreaCount > engine :: vulkan :: config :: deviceGroupRenderPassBeginDeviceRenderAreaCount ) {
                    __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                            "config :: deviceGroupRenderPassBeginDeviceRenderAreaCount = %d. Minimum Required = %d",
                            engine :: vulkan :: config :: deviceGroupRenderPassBeginDeviceRenderAreaCount,
                            pContext->deviceGroupRenderPassBeginInfo.deviceRenderAreaCount
                    ))

                    pContext->deviceGroupRenderPassBeginInfo.deviceRenderAreaCount = engine :: vulkan :: config :: deviceGroupRenderPassBeginDeviceRenderAreaCount;
                }

                for ( cds :: uint32 i = 0U; i < pContext->deviceGroupRenderPassBeginInfo.deviceRenderAreaCount; ++ i ) {
                    pContext->deviceGroupDeviceRenderAreas[i] = {
                            .offset = {
                                    .x      = pDeviceGroupRenderPassBeginInfo->pDeviceRenderAreas[i].offset.x,
                                    .y      = pDeviceGroupRenderPassBeginInfo->pDeviceRenderAreas[i].offset.y
                            },
                            .extent = {
                                    .width  = pDeviceGroupRenderPassBeginInfo->pDeviceRenderAreas[i].extent.width,
                                    .height = pDeviceGroupRenderPassBeginInfo->pDeviceRenderAreas[i].extent.height
                            }
                    };
                }

                break;
            }

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

            case StructureTypeRenderPassAttachmentBeginInfo:
                pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->attachmentBeginInfo,
                                reinterpret_cast < Type ( RenderPassAttachmentBeginInfo ) const * > ( pCurrent )
                        )
                );
                break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE

            case StructureTypeRenderPassSampleLocationsBeginInfo: {
                auto pRenderPassSampleLocationsBeginInfo = reinterpret_cast < Type ( RenderPassSampleLocationsBeginInfo ) const * > ( pCurrent );
                pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->sampleLocationsBeginInfo,
                                pRenderPassSampleLocationsBeginInfo
                        )
                );

                pContext->sampleLocationsBeginInfo.pAttachmentInitialSampleLocations = & pContext->attachmentInitialSampleLocations[0];

                if ( pContext->sampleLocationsBeginInfo.attachmentInitialSampleLocationsCount > engine :: vulkan :: config :: renderPassSampleLocationsAttachmentInitialCount ) {
                    __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                            "config :: renderPassSampleLocationsAttachmentInitialCount = %d. Minimum Required = %d",
                            engine :: vulkan :: config :: renderPassSampleLocationsAttachmentInitialCount,
                            pContext->sampleLocationsBeginInfo.attachmentInitialSampleLocationsCount
                    ))

                    pContext->sampleLocationsBeginInfo.attachmentInitialSampleLocationsCount = engine :: vulkan :: config :: renderPassSampleLocationsAttachmentInitialCount;
                }

                for ( cds :: uint32 i = 0U; i < pContext->sampleLocationsBeginInfo.attachmentInitialSampleLocationsCount; ++ i ) {
                    (void) toVulkanFormat ( & pContext->attachmentInitialSampleLocations[i], & pRenderPassSampleLocationsBeginInfo->pAttachmentInitialSampleLocations[i] );

                    pContext->attachmentInitialSampleLocations[i].sampleLocationsInfo.pSampleLocations = & pContext->attachmentInitialSampleLocationsLocations[i][0];

                    if ( pContext->attachmentInitialSampleLocations[i].sampleLocationsInfo.sampleLocationsCount > engine :: vulkan :: config :: sampleLocationsInfoSampleLocationsCount ) {
                        __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                                "config :: sampleLocationsInfoSampleLocationsCount = %d. Minimum Required = %d",
                                engine :: vulkan :: config :: sampleLocationsInfoSampleLocationsCount,
                                pContext->attachmentInitialSampleLocations[i].sampleLocationsInfo.sampleLocationsCount
                        ))

                        pContext->attachmentInitialSampleLocations[i].sampleLocationsInfo.sampleLocationsCount = engine :: vulkan :: config :: sampleLocationsInfoSampleLocationsCount;
                    }

                    for ( cds :: uint32 j = 0U; j < pContext->attachmentInitialSampleLocations[i].sampleLocationsInfo.sampleLocationsCount; ++ j ) {
                        pContext->attachmentInitialSampleLocationsLocations[i][j] = {
                                .x  = pRenderPassSampleLocationsBeginInfo->pAttachmentInitialSampleLocations[i].sampleLocationsInfo.pSampleLocations[j].x,
                                .y  = pRenderPassSampleLocationsBeginInfo->pAttachmentInitialSampleLocations[i].sampleLocationsInfo.pSampleLocations[j].y
                        };
                    }
                }

                pContext->sampleLocationsBeginInfo.pPostSubpassSampleLocations = & pContext->postSubpassSampleLocations[0];

                if ( pContext->sampleLocationsBeginInfo.postSubpassSampleLocationsCount > engine :: vulkan :: config :: renderPassSampleLocationsPostSubpassCount ) {
                    __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                            "config :: renderPassSampleLocationsPostSubpassCount = %d. Minimum Required = %d",
                            engine :: vulkan :: config :: renderPassSampleLocationsPostSubpassCount,
                            pContext->sampleLocationsBeginInfo.postSubpassSampleLocationsCount
                    ))

                    pContext->sampleLocationsBeginInfo.postSubpassSampleLocationsCount = engine :: vulkan :: config :: renderPassSampleLocationsPostSubpassCount;
                }

                for ( cds :: uint32 i = 0U; i < pContext->sampleLocationsBeginInfo.postSubpassSampleLocationsCount; ++ i ) {
                    (void) toVulkanFormat ( & pContext->postSubpassSampleLocations[i], & pRenderPassSampleLocationsBeginInfo->pPostSubpassSampleLocations[i] );

                    pContext->postSubpassSampleLocations[i].sampleLocationsInfo.pSampleLocations = & pContext->postSubpassSampleLocationsLocations[i][0];

                    if ( pContext->postSubpassSampleLocations[i].sampleLocationsInfo.sampleLocationsCount > engine :: vulkan :: config :: sampleLocationsInfoSampleLocationsCount ) {
                        __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                                "config :: sampleLocationsInfoSampleLocationsCount = %d. Minimum Required = %d",
                                engine :: vulkan :: config :: sampleLocationsInfoSampleLocationsCount,
                                pContext->postSubpassSampleLocations[i].sampleLocationsInfo.sampleLocationsCount
                        ))

                        pContext->postSubpassSampleLocations[i].sampleLocationsInfo.sampleLocationsCount = engine :: vulkan :: config :: sampleLocationsInfoSampleLocationsCount;
                    }

                    for ( cds :: uint32 j = 0U; j < pContext->postSubpassSampleLocations[i].sampleLocationsInfo.sampleLocationsCount; ++ j ) {
                        pContext->postSubpassSampleLocationsLocations[i][j] = {
                                .x  = pRenderPassSampleLocationsBeginInfo->pPostSubpassSampleLocations[i].sampleLocationsInfo.pSampleLocations[j].x,
                                .y  = pRenderPassSampleLocationsBeginInfo->pPostSubpassSampleLocations[i].sampleLocationsInfo.pSampleLocations[j].y
                        };
                    }
                }

                break;
            }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_RENDER_PASS_TRANSFORM_AVAILABLE

            case StructureTypeRenderPassTransformBeginInfoQualcomm:
                pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                        toVulkanFormat (
                                & pContext->transformBeginInfo,
                                reinterpret_cast < Type ( RenderPassTransformBeginInfoQualcomm ) const * > ( pCurrent )
                        )
                );
                break;

#endif

                default:
                    break;
            }

            pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
            pCurrent    = pCurrent->pNext;
        }

        pCurrentVk->pNext = nullptr;

        pContext->beginInfo.pClearValues = & pContext->clearValues[0];

        if ( pContext->beginInfo.clearValueCount > engine :: vulkan :: config :: renderPassBeginInfoClearValueCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                    "config :: renderPassBeginInfoClearValueCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: renderPassBeginInfoClearValueCount,
                    pContext->beginInfo.clearValueCount
            ))

            pContext->beginInfo.clearValueCount = engine :: vulkan :: config :: renderPassBeginInfoClearValueCount;
        }

        for ( cds :: uint32 i = 0U; i < pContext->beginInfo.clearValueCount; ++ i ) {
            (void) std :: memcpy ( & pContext->clearValues[i], & pSource->pClearValues[i], sizeof ( pContext->clearValues[i] ) );
        }

        return & pContext->beginInfo;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    auto toVulkanFormat (
            VkSubpassBeginInfo              * pDestination,
            Type ( SubpassBeginInfo ) const * pSource
    ) noexcept -> VkSubpassBeginInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType      = VK_STRUCTURE_TYPE_SUBPASS_BEGIN_INFO,
                .pNext      = nullptr,
                .contents   = static_cast < VkSubpassContents > ( pSource->contents )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    auto prepareContext (
            BeginRenderPassContext               * pContext,
            Type ( SubpassBeginInfo )      const * pSource
    ) noexcept -> VkSubpassBeginInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        return toVulkanFormat ( & pContext->subpassBeginInfo, pSource );
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    auto prepareContext (
            NextSubpassContext                   * pContext,
            Type ( SubpassBeginInfo )      const * pSource
    ) noexcept -> VkSubpassBeginInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        return toVulkanFormat ( & pContext->beginInfo, pSource );
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    auto toVulkanFormat (
            VkSubpassEndInfo              * pDestination,
            Type ( SubpassEndInfo ) const * pSource
    ) noexcept -> VkSubpassEndInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType      = VK_STRUCTURE_TYPE_SUBPASS_END_INFO,
                .pNext      = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE
    auto toVulkanFormat (
            VkSubpassFragmentDensityMapOffsetEndInfoQCOM                  * pDestination,
            Type ( SubpassFragmentDensityMapOffsetEndInfoQualcomm ) const * pSource
    ) noexcept -> VkSubpassFragmentDensityMapOffsetEndInfoQCOM * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                      = VK_STRUCTURE_TYPE_SUBPASS_FRAGMENT_DENSITY_MAP_OFFSET_END_INFO_QCOM,
                .pNext                      = nullptr,
                .fragmentDensityOffsetCount = pSource->fragmentDensityOffsetCount,
                .pFragmentDensityOffsets    = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    auto prepareContext (
            NextSubpassContext                 * pContext,
            Type ( SubpassEndInfo )      const * pSource
    ) noexcept -> VkSubpassEndInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pNext );
        auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->endInfo, pSource ) );

        while ( pCurrent != nullptr ) {

            switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE

                case StructureTypeSubpassFragmentDensityMapOffsetEndInfoQualcomm: {
                    auto pSubpassFragmentDensityMapOffsetEndInfo = reinterpret_cast < Type ( SubpassFragmentDensityMapOffsetEndInfoQualcomm ) const * > ( pCurrent );
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->fragmentDensityMapOffsetEndInfo,
                                    pSubpassFragmentDensityMapOffsetEndInfo
                            )
                    );

                    pContext->fragmentDensityMapOffsetEndInfo.pFragmentDensityOffsets = & pContext->fragmentDensityOffsets[0];

                    if ( pContext->fragmentDensityMapOffsetEndInfo.fragmentDensityOffsetCount > engine :: vulkan :: config :: subpassFragmentDensityMapOffsetEndInfoOffsetCount ) {
                        __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                                "config :: subpassFragmentDensityMapOffsetEndInfoOffsetCount = %d. Minimum Required = %d",
                                engine :: vulkan :: config :: subpassFragmentDensityMapOffsetEndInfoOffsetCount,
                                pContext->fragmentDensityMapOffsetEndInfo.fragmentDensityOffsetCount
                        ))

                        pContext->fragmentDensityMapOffsetEndInfo.fragmentDensityOffsetCount = engine :: vulkan :: config :: subpassFragmentDensityMapOffsetEndInfoOffsetCount;
                    }

                    for ( cds :: uint32 i = 0U; i < pContext->fragmentDensityMapOffsetEndInfo.fragmentDensityOffsetCount; ++ i ) {
                        pContext->fragmentDensityOffsets[i] = {
                                .x  = pSubpassFragmentDensityMapOffsetEndInfo->pFragmentDensityOffsets[i].x,
                                .y  = pSubpassFragmentDensityMapOffsetEndInfo->pFragmentDensityOffsets[i].y
                        };
                    }

                    break;
                }

#endif

                default:
                    break;
            }

            pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
            pCurrent    = pCurrent->pNext;
        }

        pCurrentVk->pNext = nullptr;

        return & pContext->endInfo;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkShaderModuleCreateInfo              * pDestination,
            Type ( ShaderModuleCreateInfo ) const * pSource
    ) noexcept -> VkShaderModuleCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                      = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
                .pNext                      = nullptr,
                .flags                      = pSource->flags,
                .codeSize                   = static_cast < std :: size_t > ( pSource->codeSize ),
                .pCode                      = pSource->pCode
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_CACHE_AVAILABLE
    auto toVulkanFormat (
            VkShaderModuleValidationCacheCreateInfoEXT              * pDestination,
            Type ( ShaderModuleValidationCacheCreateInfo ) const * pSource
    ) noexcept -> VkShaderModuleValidationCacheCreateInfoEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                      = VK_STRUCTURE_TYPE_SHADER_MODULE_VALIDATION_CACHE_CREATE_INFO_EXT,
                .pNext                      = nullptr,
                .validationCache            = pSource->validationCache
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto prepareContext (
            CreateShaderModuleContext             * pContext,
            Type ( ShaderModuleCreateInfo ) const * pSource
    ) noexcept -> VkShaderModuleCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pNext );
        auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->createInfo, pSource ) );

        while ( pCurrent != nullptr ) {

            switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_CACHE_AVAILABLE

                case StructureTypeShaderModuleValidationCacheCreateInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->validationCacheCreateInfo,
                                    reinterpret_cast < Type ( ShaderModuleValidationCacheCreateInfo ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

                default:
                    break;
            }

            pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
            pCurrent    = pCurrent->pNext;
        }

        pCurrentVk->pNext = nullptr;

        return & pContext->createInfo;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE
    auto fromVulkanFormat (
            Type ( CooperativeMatrixPropertiesNVidia )        * pDestination,
            VkCooperativeMatrixPropertiesNV             const * pSource
    ) noexcept -> Type ( CooperativeMatrixPropertiesNVidia ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .structureType  = StructureTypeCooperativeMatrixPropertiesNVidia,
                .pNext          = nullptr,
                .MSize          = pSource->MSize,
                .NSize          = pSource->NSize,
                .KSize          = pSource->KSize,
                .AType          = static_cast < Type ( ComponentTypeNVidia ) > ( pSource->AType ),
                .BType          = static_cast < Type ( ComponentTypeNVidia ) > ( pSource->BType ),
                .CType          = static_cast < Type ( ComponentTypeNVidia ) > ( pSource->CType ),
                .DType          = static_cast < Type ( ComponentTypeNVidia ) > ( pSource->DType ),
                .scope          = static_cast < Type ( ScopeNVidia ) > ( pSource->scope )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_CACHE_AVAILABLE
    auto toVulkanFormat (
            VkValidationCacheCreateInfoEXT              * pDestination,
            Type ( ValidationCacheCreateInfo ) const * pSource
    ) noexcept -> VkValidationCacheCreateInfoEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                      = VK_STRUCTURE_TYPE_VALIDATION_CACHE_CREATE_INFO_EXT,
                .pNext                      = nullptr,
                .flags                      = pSource->flags,
                .initialDataSize            = pSource->initialDataSize,
                .pInitialData               = pSource->pInitialData
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto prepareContext (
            CreateComputePipelineContext             * pContext,
            cds :: uint32                              count,
            Type ( ComputePipelineCreateInfo ) const * pCreateInfos
    ) noexcept -> VkComputePipelineCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pCreateInfos == nullptr || count == 0U ) {
            return nullptr;
        }

#endif

        if ( count > engine :: vulkan :: config :: computePipelineCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                    "config :: computePipelineCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: computePipelineCount,
                    count
            ))

            count = engine :: vulkan :: config :: computePipelineCount;
        }

        for ( cds :: uint32 i = 0U; i < count; ++ i ) {

            auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pCreateInfos[i].pNext );
            auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->createInfos[i], & pCreateInfos[i] ) );

            while ( pCurrent != nullptr ) {

                switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_EXTENSION_AMD_PIPELINE_COMPILER_CONTROL_AVAILABLE

                    case StructureTypePipelineCompilerControlCreateInfoAMD:
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->compilerControlCreateInfos[i],
                                        reinterpret_cast < Type ( PipelineCompilerControlCreateInfoAMD ) const * > ( pCurrent )
                                )
                        );
                        break;

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_FEEDBACK_AVAILABLE

                    case StructureTypePipelineCreationFeedbackCreateInfo: {
                        auto pFeedbackCreateInfo = reinterpret_cast < Type ( PipelineCreationFeedbackCreateInfo ) const * > ( pCurrent );
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * >(
                                toVulkanFormat (
                                        & pContext->feedbackCreateInfos[i],
                                        pFeedbackCreateInfo
                                )
                        );

                        if ( pFeedbackCreateInfo->pPipelineCreationFeedback != nullptr ) {
                            pContext->feedbackCreateInfos[i].pPipelineCreationFeedback = toVulkanFormat ( & pContext->feedbacks[i], pFeedbackCreateInfo->pPipelineCreationFeedback );
                        }

                        pContext->feedbackCreateInfos[i].pPipelineStageCreationFeedbacks = & pContext->feedbackStageFeedbacks[i][0];

                        if ( pContext->feedbackCreateInfos[i].pipelineStageCreationFeedbackCount > engine :: vulkan :: config :: computePipelineStageCreationFeedbackCount ) {
                            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                                    "config :: computePipelineStageCreationFeedbackCount = %d. Minimum Required = %d",
                                    engine :: vulkan :: config :: computePipelineStageCreationFeedbackCount,
                                    pContext->feedbackCreateInfos[i].pipelineStageCreationFeedbackCount
                            ))

                            pContext->feedbackCreateInfos[i].pipelineStageCreationFeedbackCount = engine :: vulkan :: config :: computePipelineStageCreationFeedbackCount;
                        }

                        for ( cds :: uint32 j = 0U; j < pContext->feedbackCreateInfos[i].pipelineStageCreationFeedbackCount; ++ j ) {
                            (void) toVulkanFormat ( & pContext->feedbackStageFeedbacks[i][j], & pFeedbackCreateInfo->pPipelineStageCreationFeedbacks[j] );
                        }

                        break;
                    }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE

                    case StructureTypeSubpassShadingPipelineCreateInfoHuawei:
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->subpassShadingCreateInfos[i],
                                        reinterpret_cast < Type ( SubpassShadingPipelineCreateInfoHuawei ) const * > ( pCurrent )
                                )
                        );
                        break;

#endif

                    default:
                        break;
                }

                pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
                pCurrent    = pCurrent->pNext;
            }

            pCurrentVk->pNext = nullptr;

            pCurrent    = reinterpret_cast < Type ( GenericInStructure ) const * > ( pCreateInfos[i].stage.pNext );
            pCurrentVk  = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->createInfos[i].stage, & pCreateInfos[i].stage ) );

            while ( pCurrent != nullptr ) {

                switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE

                    case StructureTypePipelineShaderStageRequiredSubgroupSizeCreateInfo:
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->requiredSubgroupSizeCreateInfos[i],
                                        reinterpret_cast < Type ( PipelineShaderStageRequiredSubgroupSizeCreateInfo ) const * > ( pCurrent )
                                )
                        );
                        break;

#endif

                    default:
                        break;
                }

                pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
                pCurrent    = pCurrent->pNext;
            }

            pCurrentVk->pNext = nullptr;

            if ( pCreateInfos[i].stage.pSpecializationInfo != nullptr ) {
                pContext->createInfos[i].stage.pSpecializationInfo = toVulkanFormat ( & pContext->specializationInfos[i], pCreateInfos[i].stage.pSpecializationInfo );
                pContext->specializationInfos[i].pMapEntries = & pContext->specializationMapEntries[i][0];

                if ( pContext->specializationInfos[i].mapEntryCount > engine :: vulkan :: config :: computePipelineSpecializationMapEntryCount ) {
                    __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, cds :: String :: f (
                            "config :: computePipelineSpecializationMapEntryCount = %d. Minimum Required = %d",
                            engine :: vulkan :: config :: computePipelineSpecializationMapEntryCount,
                            pContext->specializationInfos[i].mapEntryCount
                    ))

                    pContext->specializationInfos[i].mapEntryCount = engine :: vulkan :: config :: computePipelineSpecializationMapEntryCount;
                }

                for ( cds :: uint32 j = 0U; j < pContext->specializationInfos[i].mapEntryCount; ++ j ) {
                    (void) toVulkanFormat ( & pContext->specializationMapEntries[i][j], & pCreateInfos[i].stage.pSpecializationInfo->pMapEntries[j] );
                }
            }
        }

        return & pContext->createInfos[0];
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto extractContext (
            cds :: uint32                               count,
            Type ( ComputePipelineCreateInfo )  const * pCreateInfos,
            CreateComputePipelineContext        const * pContext
    ) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( count == 0U || pCreateInfos == nullptr || pContext == nullptr ) {
            return;
        }

#endif

        for ( cds :: uint32 i = 0U; i < count; ++ i ) {
            auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pCreateInfos[i].pNext );

            while ( pCurrent != nullptr ) {

                switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_FEEDBACK_AVAILABLE

                    case StructureTypePipelineCreationFeedbackCreateInfo: {
                        auto pFeedbackCreateInfo = reinterpret_cast < Type ( PipelineCreationFeedbackCreateInfo ) const * > ( pCurrent );

                        if ( pFeedbackCreateInfo->pPipelineCreationFeedback != nullptr ) {
                            (void) fromVulkanFormat ( pFeedbackCreateInfo->pPipelineCreationFeedback, & pContext->feedbacks[i] );
                        }

                        for ( cds :: uint32 j = 0U; j < pFeedbackCreateInfo->pipelineStageCreationFeedbackCount; ++ j ) {
                            (void) fromVulkanFormat ( & pFeedbackCreateInfo->pPipelineStageCreationFeedbacks[j], & pContext->feedbackStageFeedbacks[i][j] );
                        }

                        break;
                    }

#endif

                    default:
                        break;
                }

                pCurrent = pCurrent->pNext;
            }
        }
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkComputePipelineCreateInfo              * pDestination,
            Type ( ComputePipelineCreateInfo ) const * pSource
    ) noexcept -> VkComputePipelineCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType                 = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
        pDestination->pNext                 = nullptr;
        pDestination->flags                 = pSource->flags;
        pDestination->layout                = pSource->layout;
        pDestination->basePipelineHandle    = pSource->basePipelineHandle;
        pDestination->basePipelineIndex     = pSource->basePipelineIndex;

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_PIPELINE_COMPILER_CONTROL_AVAILABLE
    auto toVulkanFormat (
            VkPipelineCompilerControlCreateInfoAMD              * pDestination,
            Type ( PipelineCompilerControlCreateInfoAMD ) const * pSource
    ) noexcept -> VkPipelineCompilerControlCreateInfoAMD * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                      = VK_STRUCTURE_TYPE_PIPELINE_COMPILER_CONTROL_CREATE_INFO_AMD,
                .pNext                      = nullptr,
                .compilerControlFlags       = pSource->compilerControlFlags
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_FEEDBACK_AVAILABLE
    auto toVulkanFormat (
            VkPipelineCreationFeedbackCreateInfo_t            * pDestination,
            Type ( PipelineCreationFeedbackCreateInfo ) const * pSource
    ) noexcept -> VkPipelineCreationFeedbackCreateInfo_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
                .sType                              = VK_STRUCTURE_TYPE_PIPELINE_CREATION_FEEDBACK_CREATE_INFO,
#elif __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_FEEDBACK_AVAILABLE
                .sType                              = VK_STRUCTURE_TYPE_PIPELINE_CREATION_FEEDBACK_CREATE_INFO_EXT,
#endif
                .pNext                              = nullptr,
                .pPipelineCreationFeedback          = nullptr,
                .pipelineStageCreationFeedbackCount = pSource->pipelineStageCreationFeedbackCount,
                .pPipelineStageCreationFeedbacks    = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_FEEDBACK_AVAILABLE
    auto toVulkanFormat (
            VkPipelineCreationFeedback_t            * pDestination,
            Type ( PipelineCreationFeedback ) const * pSource
    ) noexcept -> VkPipelineCreationFeedback_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .flags      = pSource->flags,
                .duration   = pSource->duration
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_FEEDBACK_AVAILABLE
    auto fromVulkanFormat (
            Type ( PipelineCreationFeedback )         * pDestination,
            VkPipelineCreationFeedback_t        const * pSource
    ) noexcept -> Type ( PipelineCreationFeedback ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .flags      = pSource->flags,
                .duration   = pSource->duration
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE
    auto toVulkanFormat (
            VkSubpassShadingPipelineCreateInfoHUAWEI              * pDestination,
            Type ( SubpassShadingPipelineCreateInfoHuawei ) const * pSource
    ) noexcept -> VkSubpassShadingPipelineCreateInfoHUAWEI * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                      = VK_STRUCTURE_TYPE_SUBPASS_SHADING_PIPELINE_CREATE_INFO_HUAWEI,
                .pNext                      = nullptr,
                .renderPass                 = pSource->renderPass,
                .subpass                    = pSource->subpass
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkPipelineShaderStageCreateInfo              * pDestination,
            Type ( PipelineShaderStageCreateInfo ) const * pSource
    ) noexcept -> VkPipelineShaderStageCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                      = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
                .pNext                      = nullptr,
                .flags                      = pSource->flags,
                .stage                      = static_cast < VkShaderStageFlagBits > ( pSource->stage ),
                .module                     = pSource->module,
                .pName                      = pSource->pName,
                .pSpecializationInfo        = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE
    auto toVulkanFormat (
            VkPipelineShaderStageRequiredSubgroupSizeCreateInfo_t            * pDestination,
            Type ( PipelineShaderStageRequiredSubgroupSizeCreateInfo ) const * pSource
    ) noexcept -> VkPipelineShaderStageRequiredSubgroupSizeCreateInfo_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
                .sType                      = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_REQUIRED_SUBGROUP_SIZE_CREATE_INFO,
#elif __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_FEEDBACK_AVAILABLE
                .sType                      = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_REQUIRED_SUBGROUP_SIZE_CREATE_INFO_EXT,
#endif
                .pNext                      = nullptr,
                .requiredSubgroupSize       = pSource->requiredSubgroupSize
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkSpecializationInfo              * pDestination,
            Type ( SpecializationInfo ) const * pSource
    ) noexcept -> VkSpecializationInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .mapEntryCount  = pSource->mapEntryCount,
                .pMapEntries    = nullptr,
                .dataSize       = pSource->dataSize,
                .pData          = pSource->pData
        };
        
        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkSpecializationMapEntry              * pDestination,
            Type ( SpecializationMapEntry ) const * pSource
    ) noexcept -> VkSpecializationMapEntry * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .constantID = pSource->constantID,
                .offset     = pSource->offset,
                .size       = pSource->size
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE
    auto toVulkanFormat (
            VkPhysicalDevicePortabilitySubsetFeaturesKHR           * pDestination,
            Type ( PhysicalDevicePortabilitySubsetFeatures ) const * pSource
    ) noexcept -> VkPhysicalDevicePortabilitySubsetFeaturesKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                                  = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PORTABILITY_SUBSET_FEATURES_KHR,
                .pNext                                  = nullptr,
                .constantAlphaColorBlendFactors         = pSource->constantAlphaColorBlendFactors,
                .events                                 = pSource->events,
                .imageViewFormatReinterpretation        = pSource->imageViewFormatReinterpretation,
                .imageViewFormatSwizzle                 = pSource->imageViewFormatSwizzle,
                .imageView2DOn3DImage                   = pSource->imageView2DOn3DImage,
                .multisampleArrayImage                  = pSource->multisampleArrayImage,
                .mutableComparisonSamplers              = pSource->mutableComparisonSamplers,
                .pointPolygons                          = pSource->pointPolygons,
                .samplerMipLodBias                      = pSource->samplerMipLodBias,
                .separateStencilMaskRef                 = pSource->separateStencilMaskRef,
                .shaderSampleRateInterpolationFunctions = pSource->shaderSampleRateInterpolationFunctions,
                .tessellationIsolines                   = pSource->tessellationIsolines,
                .tessellationPointMode                  = pSource->tessellationPointMode,
                .triangleFans                           = pSource->triangleFans,
                .vertexAttributeAccessBeyondStride      = pSource->vertexAttributeAccessBeyondStride,
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE
    auto fromVulkanFormat (
            Type ( PhysicalDevicePortabilitySubsetFeatures )       * pDestination,
            VkPhysicalDevicePortabilitySubsetFeaturesKHR     const * pSource
    ) noexcept -> Type ( PhysicalDevicePortabilitySubsetFeatures ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .structureType                          = StructureTypePhysicalDevicePortabilitySubsetFeatures,
                .pNext                                  = nullptr,
                .constantAlphaColorBlendFactors         = pSource->constantAlphaColorBlendFactors,
                .events                                 = pSource->events,
                .imageViewFormatReinterpretation        = pSource->imageViewFormatReinterpretation,
                .imageViewFormatSwizzle                 = pSource->imageViewFormatSwizzle,
                .imageView2DOn3DImage                   = pSource->imageView2DOn3DImage,
                .multisampleArrayImage                  = pSource->multisampleArrayImage,
                .mutableComparisonSamplers              = pSource->mutableComparisonSamplers,
                .pointPolygons                          = pSource->pointPolygons,
                .samplerMipLodBias                      = pSource->samplerMipLodBias,
                .separateStencilMaskRef                 = pSource->separateStencilMaskRef,
                .shaderSampleRateInterpolationFunctions = pSource->shaderSampleRateInterpolationFunctions,
                .tessellationIsolines                   = pSource->tessellationIsolines,
                .tessellationPointMode                  = pSource->tessellationPointMode,
                .triangleFans                           = pSource->triangleFans,
                .vertexAttributeAccessBeyondStride      = pSource->vertexAttributeAccessBeyondStride,
        };

        return pDestination;
    }
#endif

}


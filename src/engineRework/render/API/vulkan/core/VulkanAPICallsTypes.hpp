//
// Created by loghin on 16.02.2022.
//

#ifndef C_ENG_VULKANAPICALLSTYPES_HPP
#define C_ENG_VULKANAPICALLSTYPES_HPP

#include <VulkanAPICallsPrivate.hpp>

#define C_ENG_MAP_START HEADER
#include <ObjectMapping.hpp>

struct CommonContext {
    engine :: vulkan :: Type ( Result ) error;
};

struct CreateInstanceContext {
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    engine :: vulkan :: Type ( Result ) error;
    VkInstanceCreateInfo                instance;
    VkApplicationInfo                   applicationInfo;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_REPORT_AVAILABLE
    VkDebugReportCallbackCreateInfoEXT  debugReport;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_UTILS_AVAILABLE
    VkDebugUtilsMessengerCreateInfoEXT  debugMessenger;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_FEATURES_AVAILABLE
    VkValidationFeaturesEXT             validationFeatures;
    VkValidationFeatureEnableEXT        validationFeatureEnables [ __C_ENG_VULKAN_CORE_VALIDATION_FEATURE_ENABLE_MAX_COUNT ];
    VkValidationFeatureDisableEXT       validationFeatureDisables [ __C_ENG_VULKAN_CORE_VALIDATION_FEATURE_DISABLE_MAX_COUNT ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_FLAGS_AVAILABLE
    VkValidationFlagsEXT                validationFlags;
    VkValidationCheckEXT                validationChecks [ __C_ENG_VULKAN_CORE_VALIDATION_CHECK_MAX_COUNT ];
#endif
};

struct EnumerateLayerPropertiesContext {
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    engine :: vulkan :: Type ( Result ) error;
    VkLayerProperties                   properties [ __C_ENG_VULKAN_CORE_LAYER_MAX_COUNT ];
#endif
};

struct EnumerateExtensionPropertiesContext {
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    engine :: vulkan :: Type ( Result ) error;
    VkExtensionProperties               properties [ __C_ENG_VULKAN_CORE_LAYER_MAX_COUNT ];
#endif
};

struct EnumeratePhysicalDevicesContext {
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    engine :: vulkan :: Type ( Result ) error;
    VkPhysicalDevice                    devices [ __C_ENG_VULKAN_CORE_PHYSICAL_DEVICE_MAX_COUNT ];
#endif
};

struct EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersContext {
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    engine :: vulkan :: Type ( Result ) error;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
    VkPerformanceCounterKHR             counters [ __C_ENG_VULKAN_CORE_QUEUE_FAMILY_PERFORMANCE_COUNTER_MAX_COUNT ];
    VkPerformanceCounterDescriptionKHR  descriptions [ __C_ENG_VULKAN_CORE_QUEUE_FAMILY_PERFORMANCE_COUNTER_MAX_COUNT ];
#endif
};

struct EnumeratePhysicalDeviceGroupsContext {
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    engine :: vulkan :: Type ( Result ) error;
#endif
#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    VkPhysicalDeviceGroupProperties     properties [ __C_ENG_VULKAN_CORE_PHYSICAL_DEVICE_GROUP_MAX_COUNT ];
#endif
};

struct DevicePropertiesContext {
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkPhysicalDeviceProperties                                  properties;
#endif
#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    VkPhysicalDeviceProperties2                                 properties2;
    VkPhysicalDeviceVulkan11Properties                          vulkan11;
    VkPhysicalDeviceIDProperties                                deviceID;
    VkPhysicalDeviceMaintenance3Properties                      maintenance3;
    VkPhysicalDeviceMultiviewProperties                         multiview;
    VkPhysicalDevicePointClippingProperties                     pointClipping;
    VkPhysicalDeviceProtectedMemoryProperties                   protectedMemory;
    VkPhysicalDeviceSubgroupProperties                          subgroup;
#endif
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    VkPhysicalDeviceVulkan12Properties                          vulkan12;
    VkPhysicalDeviceDepthStencilResolveProperties               depthStencilResolve;
    VkPhysicalDeviceDescriptorIndexingProperties                descriptorIndexing;
    VkPhysicalDeviceDriverProperties                            driver;
    VkPhysicalDeviceFloatControlsProperties                     floatControls;
    VkPhysicalDeviceSamplerFilterMinmaxProperties               samplerFilterMinmax;
    VkPhysicalDeviceTimelineSemaphoreProperties                 timelineSemaphore;
#endif
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    VkPhysicalDeviceVulkan13Properties                          vulkan13;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE
    VkPhysicalDeviceBlendOperationAdvancedPropertiesEXT         blendOperationAdvanced;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_CONSERVATIVE_RASTERIZATION_AVAILABLE
    VkPhysicalDeviceConservativeRasterizationPropertiesEXT      conservativeRasterization;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE
    VkPhysicalDeviceCustomBorderColorPropertiesEXT              customBorderColor;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_DISCARD_RECTANGLES_AVAILABLE
    VkPhysicalDeviceDiscardRectanglePropertiesEXT               discardRectangle;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_EXTERNAL_MEMORY_HOST_AVAILABLE
    VkPhysicalDeviceExternalMemoryHostPropertiesEXT             externalMemoryHost;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE
    VkPhysicalDeviceFragmentDensityMapPropertiesEXT             fragmentDensityMap;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE
    VkPhysicalDeviceFragmentDensityMap2PropertiesEXT            fragmentDensityMap2;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    VkPhysicalDeviceInlineUniformBlockProperties_t              inlineUniformBlock;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE
    VkPhysicalDeviceLineRasterizationPropertiesEXT              lineRasterization;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE
    VkPhysicalDeviceMultiDrawPropertiesEXT                      multiDraw;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_PCI_BUS_INFO_AVAILABLE
    VkPhysicalDevicePCIBusInfoPropertiesEXT                     pciBusInfo;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_PHYSICAL_DEVICE_DRM_AVAILABLE
    VkPhysicalDeviceDrmPropertiesEXT                            deviceDrm;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE
    VkPhysicalDeviceProvokingVertexPropertiesEXT                provokingVertex;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE
    VkPhysicalDeviceRobustness2PropertiesEXT                    robustness2;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE
    VkPhysicalDeviceSampleLocationsPropertiesEXT                sampleLocations;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    VkPhysicalDeviceSubgroupSizeControlProperties_t             subgroupSizeControl;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    VkPhysicalDeviceTexelBufferAlignmentProperties_t            texelBufferAlignment;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE
    VkPhysicalDeviceTransformFeedbackPropertiesEXT              transformFeedback;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE
    VkPhysicalDeviceVertexAttributeDivisorPropertiesEXT         vertexAttributeDivisor;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
    VkPhysicalDeviceAccelerationStructurePropertiesKHR          accelerationStructure;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE
    VkPhysicalDeviceFragmentShadingRatePropertiesKHR            fragmentShadingRate;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    VkPhysicalDeviceMaintenance4Properties_t                    maintenance4;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
    VkPhysicalDevicePerformanceQueryPropertiesKHR               performanceQuery;
#endif
#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE
    VkPhysicalDevicePortabilitySubsetPropertiesKHR              portabilitySubset;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PUSH_DESCRIPTOR_AVAILABLE
    VkPhysicalDevicePushDescriptorPropertiesKHR                 pushDescriptor;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
    VkPhysicalDeviceRayTracingPipelinePropertiesKHR             rayTracingPipeline;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE
    VkPhysicalDeviceShaderIntegerDotProductPropertiesKHR        shaderIntegerDotProduct;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE
    VkPhysicalDeviceCooperativeMatrixPropertiesNV               cooperativeMatrix;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE
    VkPhysicalDeviceDeviceGeneratedCommandsPropertiesNV         deviceDeviceGeneratedCommands;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE
    VkPhysicalDeviceFragmentShadingRateEnumsPropertiesNV        fragmentShadingRateEnums;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE
    VkPhysicalDeviceMeshShaderPropertiesNV                      meshShader;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
    VkPhysicalDeviceRayTracingPropertiesNV                      rayTracing;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE
    VkPhysicalDeviceShaderSMBuiltinsPropertiesNV                shaderSmBuiltins;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE
    VkPhysicalDeviceShadingRateImagePropertiesNV                shadingRateImage;
#endif
#if ( __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE ) && __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE
    VkPhysicalDeviceMultiviewPerViewAttributesPropertiesNVX     multiviewPerViewattributes;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_AVAILABLE
    VkPhysicalDeviceShaderCorePropertiesAMD                     shaderCore;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_2_AVAILABLE
    VkPhysicalDeviceShaderCoreProperties2AMD                    shaderCore2;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE
    VkPhysicalDeviceFragmentDensityMapOffsetPropertiesQCOM      fragmentDensityMapOffset;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE
    VkPhysicalDeviceSubpassShadingPropertiesHUAWEI              subpassShading;
#endif
};

struct DeviceFeaturesContext {
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkPhysicalDeviceFeatures                                    features;
#endif
#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    VkPhysicalDeviceFeatures2                                   features2;
    VkPhysicalDeviceVulkan11Features                            vulkan11;
    VkPhysicalDevice16BitStorageFeatures                        _16BitStorage;
    VkPhysicalDeviceMultiviewFeatures                           multiview;
    VkPhysicalDeviceProtectedMemoryFeatures                     protectedMemory;
    VkPhysicalDeviceSamplerYcbcrConversionFeatures              samplerYcbcrConversion;
    VkPhysicalDeviceShaderDrawParametersFeatures                shaderDrawParameters;
    VkPhysicalDeviceVariablePointersFeatures                    variablePointers;
#endif
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    VkPhysicalDeviceVulkan12Features                            vulkan12;
    VkPhysicalDevice8BitStorageFeatures                         _8BitStorage;
    VkPhysicalDeviceBufferDeviceAddressFeatures                 bufferDeviceAddress;
    VkPhysicalDeviceDescriptorIndexingFeatures                  descriptorIndexing;
    VkPhysicalDeviceHostQueryResetFeatures                      hostQueryReset;
    VkPhysicalDeviceImagelessFramebufferFeatures                imagelessFramebuffer;
    VkPhysicalDeviceScalarBlockLayoutFeatures                   scalarBlockLayout;
    VkPhysicalDeviceSeparateDepthStencilLayoutsFeatures         separateDepthStencilLayouts;
    VkPhysicalDeviceShaderAtomicInt64Features                   shaderAtomicInt64;
    VkPhysicalDeviceShaderFloat16Int8Features                   shaderFloat16Int8;
    VkPhysicalDeviceShaderSubgroupExtendedTypesFeatures         shaderSubgroupExtendedTypes;
    VkPhysicalDeviceTimelineSemaphoreFeatures                   timelineSemaphore;
    VkPhysicalDeviceUniformBufferStandardLayoutFeatures         uniformBufferStandardLayout;
    VkPhysicalDeviceVulkanMemoryModelFeatures                   vulkanMemoryModel;
#endif
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    VkPhysicalDeviceVulkan13Features                            vulkan13;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_4444_FORMATS_AVAILABLE
    VkPhysicalDevice4444FormatsFeaturesEXT                      _4444Formats;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_ASTC_DECODE_MODE_AVAILABLE
    VkPhysicalDeviceASTCDecodeFeaturesEXT                       astcDecode;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
    VkPhysicalDeviceAccelerationStructureFeaturesKHR            accelerationStructure;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE
    VkPhysicalDeviceBlendOperationAdvancedFeaturesEXT           blendOperationAdvanced;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_BORDER_COLOR_SWIZZLE_AVAILABLE
    VkPhysicalDeviceBorderColorSwizzleFeaturesEXT               borderColorSwizzle;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_AMD_DEVICE_COHERENT_MEMORY_AVAILABLE
    VkPhysicalDeviceCoherentMemoryFeaturesAMD                   coherentMemory;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_COLOR_WRITE_ENABLE_AVAILABLE
    VkPhysicalDeviceColorWriteEnableFeaturesEXT                 colorWriteEnable;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COMPUTE_SHADER_DERIVATIVES_AVAILABLE
    VkPhysicalDeviceComputeShaderDerivativesFeaturesNV          computerShaderDerivatives;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE
    VkPhysicalDeviceConditionalRenderingFeaturesEXT             conditionalRendering;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE
    VkPhysicalDeviceCooperativeMatrixFeaturesNV                 cooperativeMatrix;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CORNER_SAMPLED_IMAGE_AVAILABLE
    VkPhysicalDeviceCornerSampledImageFeaturesNV                cornerSampledImage;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COVERAGE_REDUCTION_MODE_AVAILABLE
    VkPhysicalDeviceCoverageReductionModeFeaturesNV             coverageReduction;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE
    VkPhysicalDeviceCustomBorderColorFeaturesEXT                customBorderColor;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_IMAGE_ALIASING_AVAILABLE
    VkPhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV  dedicatedAllocationImageAliasingFeatures;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_CONTROL_AVAILABLE
    VkPhysicalDeviceDepthClipControlFeaturesEXT                 depthClipControl;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_ENABLE_AVAILABLE
    VkPhysicalDeviceDepthClipEnableFeaturesEXT                  depthClipEnable;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE
    VkPhysicalDeviceDeviceGeneratedCommandsFeaturesNV           deviceGeneratedCommands;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_DEVICE_MEMORY_REPORT_AVAILABLE
    VkPhysicalDeviceDeviceMemoryReportFeaturesEXT               deviceMemoryReport;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTICS_CONFIG_AVAILABLE
    VkPhysicalDeviceDiagnosticsConfigFeaturesNV                 diagnosticsConfig;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    VkPhysicalDeviceDynamicRenderingFeatures_t                  dynamicRendering;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SCISSOR_EXCLUSIVE_AVAILABLE
    VkPhysicalDeviceExclusiveScissorFeaturesNV                  exclusiveScissor;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE
    VkPhysicalDeviceExtendedDynamicStateFeaturesEXT             extendedDynamicState;
    VkPhysicalDeviceExtendedDynamicState2FeaturesEXT            extendedDynamicState2;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_RDMA_AVAILABLE
    VkPhysicalDeviceExternalMemoryRDMAFeaturesNV                externalMemoryRDMA;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE
    VkPhysicalDeviceFragmentDensityMapFeaturesEXT               fragmentDensityMap;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE
    VkPhysicalDeviceFragmentDensityMap2FeaturesEXT              fragmentDensityMap2;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE
    VkPhysicalDeviceFragmentDensityMapOffsetFeaturesQCOM        fragmentDensityMapOffset;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADER_BARYCENTRIC_AVAILABLE
    VkPhysicalDeviceFragmentShaderBarycentricFeaturesNV         fragmentShaderBarycentric;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_SHADER_INTERLOCK_AVAILABLE
    VkPhysicalDeviceFragmentShaderInterlockFeaturesEXT          fragmentShaderInterlock;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE
    VkPhysicalDeviceFragmentShadingRateEnumsFeaturesNV          fragmentShadingRateEnums;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE
    VkPhysicalDeviceFragmentShadingRateFeaturesKHR              fragmentShadingRate;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE
    VkPhysicalDeviceGlobalPriorityQueryFeaturesEXT              globalPriorityQuery;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_ROBUSTNESS_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    VkPhysicalDeviceImageRobustnessFeatures_t                   imageRobustness;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_VIEW_MIN_LOD_AVAILABLE
    VkPhysicalDeviceImageViewMinLodFeaturesEXT                  imageViewMinLOD;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_INDEX_TYPE_UINT8_AVAILABLE
    VkPhysicalDeviceIndexTypeUint8FeaturesEXT                   indexTypeUInt8;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_INHERITED_VIEWPORT_SCISSOR_AVAILABLE
    VkPhysicalDeviceInheritedViewportScissorFeaturesNV          inheritedViewportScissor;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    VkPhysicalDeviceInlineUniformBlockFeatures_t                inlineUniformBlock;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_INVOCATION_MASK_AVAILABLE
    VkPhysicalDeviceInvocationMaskFeaturesHUAWEI                invocationMask;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE
    VkPhysicalDeviceLineRasterizationFeaturesEXT                lineRasterization;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_LINEAR_COLOR_ATTACHMENT_AVAILABLE
    VkPhysicalDeviceLinearColorAttachmentFeaturesNV             linearColorAttachment;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    VkPhysicalDeviceMaintenance4Features_t                      maintenance4;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_PRIORITY_AVAILABLE
    VkPhysicalDeviceMemoryPriorityFeaturesEXT                   memoryPriority;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE
    VkPhysicalDeviceMeshShaderFeaturesNV                        meshShader;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE
    VkPhysicalDeviceMultiDrawFeaturesEXT                        multiDraw;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE
    VkPhysicalDeviceMutableDescriptorTypeFeaturesVALVE          mutableDescriptorType;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_PAGEABLE_DEVICE_LOCAL_MEMORY_AVAILABLE
    VkPhysicalDevicePageableDeviceLocalMemoryFeaturesEXT        pageableDeviceLocalMemory;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
    VkPhysicalDevicePerformanceQueryFeaturesKHR                 performanceQuery;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    VkPhysicalDevicePipelineCreationCacheControlFeatures_t      pipelineCreationCacheControl;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
    VkPhysicalDevicePipelineExecutablePropertiesFeaturesKHR     pipelineExecutableProperties;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE
    VkPhysicalDevicePortabilitySubsetFeaturesKHR                portabilitySubset;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_ID_AVAILABLE
    VkPhysicalDevicePresentIdFeaturesKHR                        presentID;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_WAIT_AVAILABLE
    VkPhysicalDevicePresentWaitFeaturesKHR                      presentWait;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_PRIMITIVE_TOPOLOGY_LIST_RESTART_AVAILABLE
    VkPhysicalDevicePrimitiveTopologyListRestartFeaturesEXT     primitiveTopologyListRestart;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    VkPhysicalDevicePrivateDataFeatures_t                       privateData;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE
    VkPhysicalDeviceProvokingVertexFeaturesEXT                  provokingVertex;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_RGBA_10_X_6_FORMATS_AVAILABLE
    VkPhysicalDeviceRGBA10X6FormatsFeaturesEXT                  rgba10x6FormatsFeaturesExt;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_ARM_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_AVAILABLE
    VkPhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM   rasterizationOrderAttachmentAccess;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_QUERY_AVAILABLE
    VkPhysicalDeviceRayQueryFeaturesKHR                         rayQuery;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE
    VkPhysicalDeviceRayTracingMotionBlurFeaturesNV              rayTracingMotionBlur;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
    VkPhysicalDeviceRayTracingPipelineFeaturesKHR               rayTracingPipeline;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_REPRESENTATIVE_FRAGMENT_TEST_AVAILABLE
    VkPhysicalDeviceRepresentativeFragmentTestFeaturesNV        representativeFragmentText;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE
    VkPhysicalDeviceRobustness2FeaturesEXT                      robustness2;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_AVAILABLE
    VkPhysicalDeviceShaderAtomicFloatFeaturesEXT                shaderAtomicFloat;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_2_AVAILABLE
    VkPhysicalDeviceShaderAtomicFloat2FeaturesEXT               shaderAtomicFloat2;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_CLOCK_AVAILABLE
    VkPhysicalDeviceShaderClockFeaturesKHR                      shaderDeviceShaderClock;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_SHADER_DEMOTE_TO_HELPER_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE0
    VkPhysicalDeviceShaderDemoteToHelperInvocationFeatures_t    shaderDemoteToHelperInvocation;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_SHADER_IMAGE_ATOMIC_INT64_AVAILABLE
    VkPhysicalDeviceShaderImageAtomicInt64FeaturesEXT           shaderImageAtomicInt64;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_IMAGE_FOOTPRINT_AVAILABLE
    VkPhysicalDeviceShaderImageFootprintFeaturesNV              shaderImageFootprint;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE
    VkPhysicalDeviceShaderSMBuiltinsFeaturesNV                  shaderSMBuiltins;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_SUBGROUP_UNIFORM_CONTROL_FLOW_AVAILABLE
    VkPhysicalDeviceShaderSubgroupUniformControlFlowFeaturesKHR shaderSubgroupUniformControlFlow;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_TERMINATE_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    VkPhysicalDeviceShaderTerminateInvocationFeatures_t         shaderTerminateInvocation;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE
    VkPhysicalDeviceShadingRateImageFeaturesNV                  shadingRateImage;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    VkPhysicalDeviceSubgroupSizeControlFeatures_t               subgroupSizeControl;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE
    VkPhysicalDeviceSubpassShadingFeaturesHUAWEI                subpassShading;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    VkPhysicalDeviceSynchronization2Features_t                  synchronization2;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    VkPhysicalDeviceTexelBufferAlignmentFeatures_t              texelBufferAlignment;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_TEXTURE_COMPRESSION_ASTC_HDR_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    VkPhysicalDeviceTextureCompressionASTCHDRFeatures_t         textureCompressionAstcHdr;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE
    VkPhysicalDeviceTransformFeedbackFeaturesEXT                transformFeedback;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE
    VkPhysicalDeviceVertexAttributeDivisorFeaturesEXT           vertexAttributeDivisor;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_INPUT_DYNAMIC_STATE_AVAILABLE
    VkPhysicalDeviceVertexInputDynamicStateFeaturesEXT          vertexInputDynamicState;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    VkPhysicalDeviceShaderIntegerDotProductFeatures_t           shaderIntegerDotProduct;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_INTEL_SHADER_INTEGER_FUNCTIONS_AVAILABLE
    VkPhysicalDeviceShaderIntegerFunctions2FeaturesINTEL        shaderIntegerFunctions2;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_AVAILABLE
    VkPhysicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR    workgroupMemoryExplicitLayout;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_2_PLANE_444_FORMATS_AVAILABLE
    VkPhysicalDeviceYcbcr2Plane444FormatsFeaturesEXT            ycbcr2Plane444Formats;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_IMAGE_ARRAYS_AVAILABLE
    VkPhysicalDeviceYcbcrImageArraysFeaturesEXT                 ycbcrImageArrays;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ZERO_INITIALIZE_WORKGROUP_MEMORY_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    VkPhysicalDeviceZeroInitializeWorkgroupMemoryFeatures_t     zeroInitializeWorkgroupMemory;
#endif
};

struct CreateDeviceContext {
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    engine :: vulkan :: Type ( Result )         error;
    VkDeviceCreateInfo                          device;
    VkDeviceQueueCreateInfo                     queues [ __C_ENG_VULKAN_CORE_DEVICE_QUEUE_FAMILY_CREATE_INFO_MAX_COUNT ];
#endif
    DeviceFeaturesContext                       features;
#if __C_ENG_VULKAN_API_EXTENSION_DEVICE_MEMORY_REPORT_AVAILABLE
    VkDeviceDeviceMemoryReportCreateInfoEXT     memoryReport;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTICS_CONFIG_AVAILABLE
    VkDeviceDiagnosticsConfigCreateInfoNV       diagnosticsConfig;
#endif
#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DEVICE_GROUP_AVAILABLE
    VkDeviceGroupDeviceCreateInfo_t             group;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_AMD_MEMORY_OVERALLOCATION_BEHAVIOUR_AVAILABLE
    VkDeviceMemoryOverallocationCreateInfoAMD   overallocation;
#endif
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE
    VkDevicePrivateDataCreateInfo_t             privateData;
#endif
};

struct GetPhysicalDevicePropertiesContext {
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    engine :: vulkan :: Type ( Result )         error;
#endif
    DevicePropertiesContext                     properties;
};

struct GetPhysicalDeviceFeaturesContext {
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    engine :: vulkan :: Type ( Result )         error;
#endif
    DeviceFeaturesContext                       features;
};

struct GetPhysicalDeviceQueueFamilyPropertiesContext {
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    engine :: vulkan :: Type ( Result )         error;
    VkQueueFamilyProperties                     properties [ __C_ENG_VULKAN_CORE_QUEUE_FAMILY_MAX_COUNT ];
#endif
#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    VkQueueFamilyProperties2                    properties2 [ __C_ENG_VULKAN_CORE_QUEUE_FAMILY_MAX_COUNT ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTIC_CHECKPOINTS_AVAILABLE
    VkQueueFamilyCheckpointPropertiesNV         checkpoints [ __C_ENG_VULKAN_CORE_QUEUE_FAMILY_MAX_COUNT ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE
    VkQueueFamilyGlobalPriorityPropertiesEXT    globalPriorities [ __C_ENG_VULKAN_CORE_QUEUE_FAMILY_MAX_COUNT ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE
    VkQueueFamilyQueryResultStatusPropertiesKHR queryResultStatuses [ __C_ENG_VULKAN_CORE_QUEUE_FAMILY_MAX_COUNT ];
    VkVideoQueueFamilyPropertiesKHR             videoQueues [ __C_ENG_VULKAN_CORE_QUEUE_FAMILY_MAX_COUNT ];
#endif
};

struct GetDeviceQueueContext {
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    engine :: vulkan :: Type ( Result )         error;
#endif
#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    VkDeviceQueueInfo2                          info2;
#endif
};

struct GetSurfaceContext {
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    engine :: vulkan :: Type ( Result )         error;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE
    VkSurfaceCapabilitiesKHR                    capabilities;
    VkSurfaceFormatKHR                          formats [ __C_ENG_VULKAN_CORE_SURFACE_FORMAT_MAX_COUNT ];
    VkPresentModeKHR                            presentModes [ __C_ENG_VULKAN_CORE_SURFACE_PRESENT_MODE_MAX_COUNT ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_DISPLAY_SURFACE_COUNTER_AVAILABLE
    VkSurfaceCapabilities2EXT                   capabilities2;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_GET_SURFACE_CAPABILITIES_AVAILABLE
    VkPhysicalDeviceSurfaceInfo2KHR             surfaceInfo2;
    VkSurfaceFormat2KHR                         formats2 [ __C_ENG_VULKAN_CORE_SURFACE_FORMAT_MAX_COUNT ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_FULL_SCREEN_EXCLUSIVE_AVAILABLE
    VkSurfaceFullScreenExclusiveInfoEXT         fullScreenExclusive;
#endif
};

struct CreateSwapChainContext {
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    engine :: vulkan :: Type ( Result )         error;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE
    VkSwapchainCreateInfoKHR                    createInfo;
#endif
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    VkImageFormatListCreateInfo                 formatListCreateInfo;
    VkFormat                                    viewFormats [ __C_ENG_VULKAN_CORE_VIEW_FORMAT_MAX_COUNT ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WIN32_SURFACE_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_FULL_SCREEN_EXCLUSIVE_AVAILABLE
    VkSurfaceFullScreenExclusiveWin32Info       fullScreenExclusiveWin32Info;
#endif
};

struct GetSwapChainContext {
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    engine :: vulkan :: Type ( Result )         error;
    VkImage                                     images [ __C_ENG_VULKAN_CORE_SWAP_CHAIN_IMAGE_MAX_COUNT ];
#endif
};

struct CreateImageViewContext {
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    engine :: vulkan :: Type ( Result )         error;
    VkImageViewCreateInfo                       createInfo;
#endif
#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    VkImageViewUsageCreateInfo                  usageCreateInfo;
    VkSamplerYcbcrConversionInfo                samplerYcbcrConversionInfo;
#endif
};

struct CreateCommandPoolContext {
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    engine :: vulkan :: Type ( Result )         error;
    VkCommandPoolCreateInfo                     createInfo;
#endif
};

struct AllocateCommandBuffersContext {
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    engine :: vulkan :: Type ( Result )         error;
    VkCommandBufferAllocateInfo                 allocateInfo;
#endif
};

struct BeginCommandBufferContext {
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    engine :: vulkan :: Type ( Result )                     error;
    VkCommandBufferBeginInfo                                beginInfo;
    VkCommandBufferInheritanceInfo                          inheritanceInfo;
#endif
#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    VkDeviceGroupCommandBufferBeginInfo                     deviceGroupBeginInfo;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    VkCommandBufferInheritanceRenderingInfo_t               inheritanceRenderingInfo;
    VkFormat                                                renderingInfoFormats [ __C_ENG_VULKAN_CORE_RENDERING_INFO_FORMATS_MAX_COUNT ];
#if __C_ENG_VULKAN_API_EXTENSION_AMD_MIXED_ATTACHMENT_SAMPLES_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAMEBUFFER_MIXED_SAMPLES_AVAILABLE
    VkAttachmentSampleCountInfoAMD                          attachmentSampleCountInfo;
    VkSampleCountFlagBits                                   sampleCountAttachmentSamples [ __C_ENG_VULKAN_CORE_SAMPLE_COUNT_ATTACHMENT_SAMPLES_MAX_COUNT ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE
    VkMultiviewPerViewAttributesInfoNVX                     multiviewPerViewAttributesInfo;
#endif
#endif
#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE
    VkCommandBufferInheritanceConditionalRenderingInfoEXT   inheritanceConditionalRenderingInfo;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_RENDER_PASS_TRANSFORM_AVAILABLE
    VkCommandBufferInheritanceRenderPassTransformInfoQCOM   inheritanceRenderpassTransformInfo;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_INHERITED_VIEWPORT_SCISSOR_AVAILABLE
    VkCommandBufferInheritanceViewportScissorInfoNV         inheritanceViewportScissorInfo;
    VkViewport                                              viewportDepths [ __C_ENG_VULKAN_CORE_VIEWPORT_DEPTH_MAX_COUNT ];
#endif
};

struct SubmitQueueContext {
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    engine :: vulkan :: Type ( Result )                     error;
    VkSubmitInfo                                            submitInfos [ __C_ENG_VULKAN_CORE_SUBMIT_INFO_MAX_COUNT ];
    VkPipelineStageFlags                                    stageFlags [ __C_ENG_VULKAN_CORE_SUBMIT_INFO_MAX_COUNT ] [ __C_ENG_VULKAN_CORE_PIPELINE_STAGE_FLAGS_MAX_COUNT ];
#endif
#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    VkDeviceGroupSubmitInfo                                 deviceGroupSubmitInfos [ __C_ENG_VULKAN_CORE_SUBMIT_INFO_MAX_COUNT ];
    VkProtectedSubmitInfo                                   protectedSubmitInfos [ __C_ENG_VULKAN_CORE_SUBMIT_INFO_MAX_COUNT ];
#endif
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    VkTimelineSemaphoreSubmitInfo                           timelineSemaphoreSubmitInfos [ __C_ENG_VULKAN_CORE_SUBMIT_INFO_MAX_COUNT ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
    VkPerformanceQuerySubmitInfoKHR                         performanceQuerySubmitInfos [ __C_ENG_VULKAN_CORE_SUBMIT_INFO_MAX_COUNT ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WIN32_KEYED_MUTEX_AVAILABLE
    Win32KeyedMutexAcquireReleaseInfoKHR                    win32KeyedMutexAcquireReleaseInfos [ __C_ENG_VULKAN_CORE_SUBMIT_INFO_MAX_COUNT ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_WIN32_KEYED_MUTEX_AVAILABLE
    Win32KeyedMutexAcquireReleaseInfoNV                     win32KeyedMutexAcquireReleaseInfosNVidia [ __C_ENG_VULKAN_CORE_SUBMIT_INFO_MAX_COUNT ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_WIN32_AVAILABLE
    D3D12FenceSubmitInfo                                    d3d12FenceSubmitInfos [ __C_ENG_VULKAN_CORE_SUBMIT_INFO_MAX_COUNT ];
#endif
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
    VkSubmitInfo2_t                                         submitInfos2 [ __C_ENG_VULKAN_CORE_SUBMIT_INFO_MAX_COUNT ];
    VkSemaphoreSubmitInfo_t                                 waitSemaphoreSubmitInfos [ __C_ENG_VULKAN_CORE_SUBMIT_INFO_MAX_COUNT ][ __C_ENG_VULKAN_CORE_SUBMIT_SEMAPHORE_INFO_MAX_COUNT ];
    VkSemaphoreSubmitInfo_t                                 signalSemaphoreSubmitInfos [ __C_ENG_VULKAN_CORE_SUBMIT_INFO_MAX_COUNT ][ __C_ENG_VULKAN_CORE_SUBMIT_SEMAPHORE_INFO_MAX_COUNT ];
    VkCommandBufferSubmitInfo_t                             commandBufferSubmitInfos [ __C_ENG_VULKAN_CORE_SUBMIT_INFO_MAX_COUNT ][ __C_ENG_VULKAN_CORE_SUBMIT_COMMAND_BUFFER_INFO_MAX_COUNT ];
#endif
};

struct CreateFenceContext {
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    engine :: vulkan :: Type ( Result )                     error;
    VkFenceCreateInfo                                       createInfo;
#endif
#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    VkExportFenceCreateInfo                                 exportCreateInfo;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_WIN32_AVAILABLE
    VkExportFenceWin32HandleInfo                            exportWin32HandleInfo;
#endif
};

struct GetFenceContext {
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    engine :: vulkan :: Type ( Result )                     error;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_WIN32_AVAILABLE
    VkFenceGetWin32HandleInfoKHR                            win32HandleInfo;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_FD_AVAILABLE
    VkFenceGetFdInfoKHR                                     fdInfo;
#endif
};

union EnumerateSharedContext {
    EnumerateLayerPropertiesContext                                     layerProperties;
    EnumerateExtensionPropertiesContext                                 extensionProperties;
    EnumeratePhysicalDevicesContext                                     physicalDevices;
    EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersContext   physicalDeviceQueueFamilyPerformanceQueryCounters;
    EnumeratePhysicalDeviceGroupsContext                                physicalDeviceGroups;
};

union CreateSharedContext {
    CreateInstanceContext                                               instance;
    CreateDeviceContext                                                 device;
    CreateSwapChainContext                                              swapChain;
    CreateImageViewContext                                              imageView;
    CreateCommandPoolContext                                            commandPool;
    CreateFenceContext                                                  fence;
};

union GetSharedContext {
    GetPhysicalDevicePropertiesContext                                  physicalDeviceProperties;
    GetPhysicalDeviceFeaturesContext                                    physicalDeviceFeatures;
    GetPhysicalDeviceQueueFamilyPropertiesContext                       physicalDeviceQueueFamilyProperties;
    GetDeviceQueueContext                                               deviceQueue;
    GetSurfaceContext                                                   surface;
    GetSwapChainContext                                                 swapChain;
    GetFenceContext                                                     fence;
};

union AllocateSharedContext {
    AllocateCommandBuffersContext                                       commandBuffers;
};

union BeginSharedContext {
    BeginCommandBufferContext                                           commandBuffer;
};

union SubmitSharedContext {
    SubmitQueueContext                                                  queue;
};

union SharedContext {
    CommonContext                                                       common;
    CreateSharedContext                                                 create;
    EnumerateSharedContext                                              enumerate;
    GetSharedContext                                                    get;
    AllocateSharedContext                                               allocate;
    BeginSharedContext                                                  begin;
    SubmitSharedContext                                                 submit;
};


#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif //C_ENG_VULKANAPICALLSTYPES_HPP

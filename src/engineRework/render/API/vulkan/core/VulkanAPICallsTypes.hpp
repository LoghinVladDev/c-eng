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
};

union SharedContext {
    CommonContext                                                       common;
    CreateSharedContext                                                 create;
    EnumerateSharedContext                                              enumerate;
};


#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif //C_ENG_VULKANAPICALLSTYPES_HPP

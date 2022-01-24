//
// Created by loghin on 01.01.2022.
//

#include <VulkanCore.hpp>
#include <VulkanAPICalls.hpp>
#include <VulkanCoreConfig.hpp>
#include <VulkanAPICallsValidUsage.hpp>

/**
 * VkPhysicalDeviceVertexAttributeDivisorPropertiesEXT
 */
using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

static VkResult                             result = VK_SUCCESS;

static VkDebugUtilsMessengerCreateInfoEXT   messengerCreateInfo;
static VkAllocationCallbacks                allocationCallbacks;
static VkApplicationInfo                    applicationInfo;
static VkInstanceCreateInfo                 instanceCreateInfo;
static VkValidationFeaturesEXT              validationFeatures;

static VkPhysicalDeviceProperties           deviceProperties;
static VkPhysicalDeviceFeatures             deviceFeatures;

static VkValidationFeatureEnableEXT         validationFeatureEnables    [ __C_ENG_VULKAN_CORE_VALIDATION_FEATURE_ENABLE_MAX_COUNT ];
static VkValidationFeatureDisableEXT        validationFeatureDisables   [ __C_ENG_VULKAN_CORE_VALIDATION_FEATURE_DISABLE_MAX_COUNT ];

static VkLayerProperties                    layerProperties             [ __C_ENG_VULKAN_CORE_LAYER_MAX_COUNT ];
static VkExtensionProperties                extensionProperties         [ __C_ENG_VULKAN_CORE_LAYER_EXTENSION_MAX_COUNT ];

static VkPhysicalDevice                     physicalDevices             [ __C_ENG_VULKAN_CORE_PHYSICAL_DEVICE_MAX_COUNT ];


/**
 * ---------------------------------------------------------
 * ---------------------------------------------------------
 * -------- Vulkan 1.1 Device Properties & Features --------
 * ---------------------------------------------------------
 * ---------------------------------------------------------
 */
#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
static VkPhysicalDeviceProperties2                                  deviceExtendedProperties;
static VkPhysicalDeviceVulkan11Properties                           deviceVulkan11Properties;
static VkPhysicalDeviceIDProperties                                 deviceIDProperties;
static VkPhysicalDeviceMaintenance3Properties                       deviceMaintenance3Properties;
static VkPhysicalDeviceMultiviewProperties                          deviceMultiviewProperties;
static VkPhysicalDevicePointClippingProperties                      devicePointClippingProperties;
static VkPhysicalDeviceProtectedMemoryProperties                    deviceProtectedMemoryProperties;
static VkPhysicalDeviceSubgroupProperties                           deviceSubgroupProperties;

static VkPhysicalDeviceFeatures2                                    deviceExtendedFeatures;
static VkPhysicalDeviceVulkan11Features                             deviceVulkan11Features;
static VkPhysicalDevice16BitStorageFeatures                         device16BitStorageFeatures;
static VkPhysicalDeviceMultiviewFeatures                            deviceMultiviewFeatures;
static VkPhysicalDeviceProtectedMemoryFeatures                      deviceProtectedMemoryFeatures;
static VkPhysicalDeviceSamplerYcbcrConversionFeatures               deviceSamplerYCBCRConversionFeatures;
static VkPhysicalDeviceShaderDrawParametersFeatures                 deviceShaderDrawParametersFeatures;
static VkPhysicalDeviceVariablePointersFeatures                     deviceVariablePointersFeatures;
#endif

/**
 * ---------------------------------------------------------
 * ---------------------------------------------------------
 * -------- Vulkan 1.2 Device Properties & Features --------
 * ---------------------------------------------------------
 * ---------------------------------------------------------
 */
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
static VkPhysicalDeviceVulkan12Properties                           deviceVulkan12Properties;
static VkPhysicalDeviceDepthStencilResolveProperties                deviceDepthStencilResolveProperties;
static VkPhysicalDeviceDescriptorIndexingProperties                 deviceDescriptorIndexingProperties;
static VkPhysicalDeviceDriverProperties                             deviceDriverProperties;
static VkPhysicalDeviceFloatControlsProperties                      deviceFloatControlsProperties;
static VkPhysicalDeviceSamplerFilterMinmaxProperties                deviceSamplerFilterMinmaxProperties;
static VkPhysicalDeviceTimelineSemaphoreProperties                  deviceTimelineSemaphoreProperties;

static VkPhysicalDeviceVulkan12Features                             deviceVulkan12Features;
static VkPhysicalDevice8BitStorageFeatures                          device8BitStorageFeatures;
static VkPhysicalDeviceBufferDeviceAddressFeatures                  deviceBufferDeviceAddressFeatures;
static VkPhysicalDeviceDescriptorIndexingFeatures                   deviceDescriptorIndexingFeatures;
static VkPhysicalDeviceHostQueryResetFeatures                       deviceHostQueryResetFeatures;
static VkPhysicalDeviceImagelessFramebufferFeatures                 deviceImagelessFramebufferFeatures;
static VkPhysicalDeviceScalarBlockLayoutFeatures                    deviceScalarBlockLayoutFeatures;
static VkPhysicalDeviceSeparateDepthStencilLayoutsFeatures          deviceSeparateDepthStencilLayoutsFeatures;
static VkPhysicalDeviceShaderAtomicInt64Features                    deviceShaderAtomicInt64Features;
static VkPhysicalDeviceShaderFloat16Int8Features                    deviceShaderFloat16Int8Features;
static VkPhysicalDeviceShaderSubgroupExtendedTypesFeatures          deviceSubgroupExtendedTypesFeatures;
static VkPhysicalDeviceTimelineSemaphoreFeatures                    deviceTimelineSemaphoreFeatures;
static VkPhysicalDeviceUniformBufferStandardLayoutFeatures          deviceUniformBufferStandardLayoutFeatures;
static VkPhysicalDeviceVulkanMemoryModelFeatures                    deviceVulkanMemoryModelFeatures;
#endif


/**
 * --------------------------------------------------------
 * --------------------------------------------------------
 * ---- Vulkan Extensions Device Properties & Features ----
 * --------------------------------------------------------
 * --------------------------------------------------------
 */
#if __C_ENG_VULKAN_API_EXTENSION_4444_FORMATS_AVAILABLE
static VkPhysicalDevice4444FormatsFeaturesEXT                       device4444FormatsFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_ASTC_DECODE_MODE_AVAILABLE
static VkPhysicalDeviceASTCDecodeFeaturesEXT                        deviceAstcDecodeFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE
static VkPhysicalDeviceBlendOperationAdvancedPropertiesEXT          deviceBlendOperationAdvancedProperties;
static VkPhysicalDeviceBlendOperationAdvancedFeaturesEXT            deviceBlendOperationAdvancedFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_BORDER_COLOR_SWIZZLE_AVAILABLE
static VkPhysicalDeviceBorderColorSwizzleFeaturesEXT                deviceBorderColorSwizzleFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_COLOR_WRITE_ENABLE_AVAILABLE
static VkPhysicalDeviceColorWriteEnableFeaturesEXT                  deviceColorWriteEnableFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE
static VkPhysicalDeviceConditionalRenderingFeaturesEXT              deviceConditionalRenderingFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONSERVATIVE_RASTERIZATION_AVAILABLE
static VkPhysicalDeviceConservativeRasterizationPropertiesEXT       deviceConservativeRasterizationProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE
static VkPhysicalDeviceCustomBorderColorPropertiesEXT               deviceCustomBorderColorProperties;
static VkPhysicalDeviceCustomBorderColorFeaturesEXT                 deviceCustomBorderColorFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_CONTROL_AVAILABLE
static VkPhysicalDeviceDepthClipControlFeaturesEXT                  deviceDepthClipControlFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_ENABLE_AVAILABLE
static VkPhysicalDeviceDepthClipEnableFeaturesEXT                   deviceDepthClipEnableFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEVICE_MEMORY_REPORT_AVAILABLE
static VkPhysicalDeviceDeviceMemoryReportFeaturesEXT                deviceDeviceMemoryReportFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE
static VkPhysicalDeviceExtendedDynamicStateFeaturesEXT              deviceExtendedDynamicStateFeatures;
static VkPhysicalDeviceExtendedDynamicState2FeaturesEXT             deviceExtendedDynamicState2Features;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISCARD_RECTANGLES_AVAILABLE
static VkPhysicalDeviceDiscardRectanglePropertiesEXT                deviceDiscardRectangleProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTERNAL_MEMORY_HOST_AVAILABLE
static VkPhysicalDeviceExternalMemoryHostPropertiesEXT              deviceExternalMemoryHostProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE
static VkPhysicalDeviceFragmentDensityMapPropertiesEXT              deviceFragmentDensityMapProperties;
static VkPhysicalDeviceFragmentDensityMapFeaturesEXT                deviceFragmentDensityMapFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE
static VkPhysicalDeviceFragmentDensityMap2PropertiesEXT             deviceFragmentDensityMap2Properties;
static VkPhysicalDeviceFragmentDensityMap2FeaturesEXT               deviceFragmentDensityMap2Features;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_SHADER_INTERLOCK_AVAILABLE
static VkPhysicalDeviceFragmentShaderInterlockFeaturesEXT           deviceFragmentShaderInterlockFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE
static VkPhysicalDeviceGlobalPriorityQueryFeaturesEXT               deviceGlobalPriorityQueryFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_ROBUSTNESS_AVAILABLE
static VkPhysicalDeviceImageRobustnessFeaturesEXT                   deviceImageRobustnessFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_VIEW_MIN_LOD_AVAILABLE
static VkPhysicalDeviceImageViewMinLodFeaturesEXT                   deviceImageViewMinLODFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INDEX_TYPE_UINT8_AVAILABLE
static VkPhysicalDeviceIndexTypeUint8FeaturesEXT                    deviceIndexTypeUInt8Features;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE
static VkPhysicalDeviceInlineUniformBlockPropertiesEXT              deviceInlineUniformBlockProperties;
static VkPhysicalDeviceInlineUniformBlockFeaturesEXT                deviceInlineUniformBlockFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE
static VkPhysicalDeviceLineRasterizationPropertiesEXT               deviceLineRasterizationProperties;
static VkPhysicalDeviceLineRasterizationFeaturesEXT                 deviceLineRasterizationFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PAGEABLE_DEVICE_LOCAL_MEMORY_AVAILABLE
static VkPhysicalDevicePageableDeviceLocalMemoryFeaturesEXT         devicePageableDeviceLocalMemoryFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_PRIORITY_AVAILABLE
static VkPhysicalDeviceMemoryPriorityFeaturesEXT                    deviceMemoryPriorityFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE
static VkPhysicalDeviceMultiDrawPropertiesEXT                       deviceMultiDrawProperties;
static VkPhysicalDeviceMultiDrawFeaturesEXT                         deviceMultiDrawFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE
static VkPhysicalDevicePipelineCreationCacheControlFeaturesEXT      devicePipelineCreationCacheControlFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PCI_BUS_INFO_AVAILABLE
static VkPhysicalDevicePCIBusInfoPropertiesEXT                      devicePciBusInfoProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIMITIVE_TOPOLOGY_LIST_RESTART_AVAILABLE
static VkPhysicalDevicePrimitiveTopologyListRestartFeaturesEXT      devicePrimitiveTopologyListRestartFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE
static VkPhysicalDevicePrivateDataFeaturesEXT                       devicePrivateDataFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PHYSICAL_DEVICE_DRM_AVAILABLE
static VkPhysicalDeviceDrmPropertiesEXT                             deviceDrmProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE
static VkPhysicalDeviceProvokingVertexPropertiesEXT                 deviceProvokingVertexProperties;
static VkPhysicalDeviceProvokingVertexFeaturesEXT                   deviceProvokingVertexFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE
static VkPhysicalDeviceRobustness2PropertiesEXT                     deviceRobustness2Properties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE
static VkPhysicalDeviceSampleLocationsPropertiesEXT                 deviceSampleLocationsProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE
static VkPhysicalDeviceSubgroupSizeControlPropertiesEXT             deviceSubgroupSizeControlProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE
static VkPhysicalDeviceTexelBufferAlignmentPropertiesEXT            deviceTexelBufferAlignmentProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE
static VkPhysicalDeviceTransformFeedbackPropertiesEXT               deviceTransformFeedbackProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE
static VkPhysicalDeviceVertexAttributeDivisorPropertiesEXT          deviceVertexAttributeDivisorProperties;
#endif


/**
 * ----------------------------------------------------------------
 * ----------------------------------------------------------------
 * ---- Vulkan Khronos Extensions Device Properties & Features ----
 * ----------------------------------------------------------------
 * ----------------------------------------------------------------
 */
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
static VkPhysicalDeviceAccelerationStructurePropertiesKHR           deviceAccelerationStructureProperties;
static VkPhysicalDeviceAccelerationStructureFeaturesKHR             deviceAccelerationStructureFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE
static VkPhysicalDeviceDynamicRenderingFeaturesKHR                  deviceDynamicRenderingFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE
static VkPhysicalDeviceFragmentShadingRatePropertiesKHR             deviceFragmentShadingRateProperties;
static VkPhysicalDeviceFragmentShadingRateFeaturesKHR               deviceFragmentShadingRateFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE
static VkPhysicalDeviceMaintenance4PropertiesKHR                    deviceMaintenance4Properties;
static VkPhysicalDeviceMaintenance4FeaturesKHR                      deviceMaintenance4Features;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
static VkPhysicalDevicePerformanceQueryPropertiesKHR                devicePerformanceQueryProperties;
static VkPhysicalDevicePerformanceQueryFeaturesKHR                  devicePerformanceQueryFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
static VkPhysicalDevicePipelineExecutablePropertiesFeaturesKHR      devicePipelineExecutablePropertiesFeatures;
#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE
static VkPhysicalDevicePortabilitySubsetPropertiesKHR               devicePortabilitySubsetProperties;
static VkPhysicalDevicePortabilitySubsetFeaturesKHR                 devicePortabilitySubsetFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_ID_AVAILABLE
static VkPhysicalDevicePresentIdFeaturesKHR                         devicePresentIDFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_WAIT_AVAILABLE
static VkPhysicalDevicePresentWaitFeaturesKHR                       devicePresentWaitFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PUSH_DESCRIPTOR_AVAILABLE
static VkPhysicalDevicePushDescriptorPropertiesKHR                  devicePushDescriptorProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
static VkPhysicalDeviceRayTracingPipelinePropertiesKHR              deviceRayTracingPipelineProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE
static VkPhysicalDeviceShaderIntegerDotProductPropertiesKHR         deviceShaderIntegerDotProductProperties;
#endif


/**
 * ---------------------------------------------------------------
 * ---------------------------------------------------------------
 * ---- Vulkan NVidia Extensions Device Properties & Features ----
 * ---------------------------------------------------------------
 * ---------------------------------------------------------------
 */
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COMPUTE_SHADER_DERIVATIVES_AVAILABLE
static VkPhysicalDeviceComputeShaderDerivativesFeaturesNV           deviceComputeShaderDerivativesFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE
static VkPhysicalDeviceCooperativeMatrixPropertiesNV                deviceCooperativeMatrixProperties;
static VkPhysicalDeviceCooperativeMatrixFeaturesNV                  deviceCooperativeMatrixFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CORNER_SAMPLED_IMAGE_AVAILABLE
static VkPhysicalDeviceCornerSampledImageFeaturesNV                 deviceDeviceCornerSampledImageFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COVERAGE_REDUCTION_MODE_AVAILABLE
static VkPhysicalDeviceCoverageReductionModeFeaturesNV              deviceCoverageReductionModeFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE
static VkPhysicalDeviceDeviceGeneratedCommandsPropertiesNV          deviceDeviceGeneratedCommandsProperties;
static VkPhysicalDeviceDeviceGeneratedCommandsFeaturesNV            deviceDeviceGeneratedCommandsFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_IMAGE_ALIASING_AVAILABLE
static VkPhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV   deviceDedicatedAllocationImageAliasingFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTICS_CONFIG_AVAILABLE
static VkPhysicalDeviceDiagnosticsConfigFeaturesNV                  deviceDiagnosticsConfigFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SCISSOR_EXCLUSIVE_AVAILABLE
static VkPhysicalDeviceExclusiveScissorFeaturesNV                   deviceExclusiveScissorFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_RDMA_AVAILABLE
static VkPhysicalDeviceExternalMemoryRDMAFeaturesNV                 deviceExternalMemoryRDMAFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADER_BARYCENTRIC_AVAILABLE
static VkPhysicalDeviceFragmentShaderBarycentricFeaturesNV          deviceFragmentShaderBarycentricFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE
static VkPhysicalDeviceFragmentShadingRateEnumsPropertiesNV         deviceFragmentShadingRateEnumsProperties;
static VkPhysicalDeviceFragmentShadingRateEnumsFeaturesNV           deviceFragmentShadingRateEnumsFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_INHERITED_VIEWPORT_SCISSOR_AVAILABLE
static VkPhysicalDeviceInheritedViewportScissorFeaturesNV           deviceInheritedViewportScissorFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_LINEAR_COLOR_ATTACHMENT_AVAILABLE
static VkPhysicalDeviceLinearColorAttachmentFeaturesNV              deviceLinearColorAttachmentFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE
static VkPhysicalDeviceMeshShaderPropertiesNV                       deviceMeshShaderProperties;
static VkPhysicalDeviceMeshShaderFeaturesNV                         deviceMeshShaderFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
static VkPhysicalDeviceRayTracingPropertiesNV                       deviceRayTracingProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE
static VkPhysicalDeviceShaderSMBuiltinsPropertiesNV                 deviceShaderSmBuiltinsProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE
static VkPhysicalDeviceShadingRateImagePropertiesNV                 deviceShadingRateImageProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE
static VkPhysicalDeviceMultiviewPerViewAttributesPropertiesNVX      deviceMultiviewPerViewAttributesProperties;
#endif


/**
 * ------------------------------------------------------------
 * ------------------------------------------------------------
 * ---- Vulkan AMD Extensions Device Properties & Features ----
 * ------------------------------------------------------------
 * ------------------------------------------------------------
 */
#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_AVAILABLE
static VkPhysicalDeviceShaderCorePropertiesAMD                      deviceShaderCoreProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_2_AVAILABLE
static VkPhysicalDeviceShaderCoreProperties2AMD                     deviceShaderCoreProperties2;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_DEVICE_COHERENT_MEMORY_AVAILABLE
static VkPhysicalDeviceCoherentMemoryFeaturesAMD                    deviceCoherentMemoryFeatures;
#endif


/**
 * -----------------------------------------------------------------
 * -----------------------------------------------------------------
 * ---- Vulkan Qualcomm Extensions Device Properties & Features ----
 * -----------------------------------------------------------------
 * -----------------------------------------------------------------
 */
#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE
static VkPhysicalDeviceFragmentDensityMapOffsetPropertiesQCOM       deviceFragmentDensityMapOffsetProperties;
static VkPhysicalDeviceFragmentDensityMapOffsetFeaturesQCOM         deviceFragmentDensityMapOffsetFeatures;
#endif


/**
 * ---------------------------------------------------------------
 * ---------------------------------------------------------------
 * ---- Vulkan Huawei Extensions Device Properties & Features ----
 * ---------------------------------------------------------------
 * ---------------------------------------------------------------
 */
#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE
static VkPhysicalDeviceSubpassShadingPropertiesHUAWEI               deviceSubpassShadingProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_INVOCATION_MASK_AVAILABLE
static VkPhysicalDeviceInvocationMaskFeaturesHUAWEI                 deviceInvocationMaskFeatures;
#endif


/**
 * --------------------------------------------------------------
 * --------------------------------------------------------------
 * ---- Vulkan Valve Extensions Device Properties & Features ----
 * --------------------------------------------------------------
 * --------------------------------------------------------------
 */
#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE
static VkPhysicalDeviceMutableDescriptorTypeFeaturesVALVE           deviceMutableDescriptorTypeFeatures;
#endif


static VkQueueFamilyProperties                                      queueFamilyProperties [ __C_ENG_VULKAN_CORE_QUEUE_FAMILY_MAX_COUNT ];

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

static VkQueueFamilyProperties2                                     queueFamilyExtendedProperties [ __C_ENG_VULKAN_CORE_QUEUE_FAMILY_MAX_COUNT ];

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTIC_CHECKPOINTS_AVAILABLE

static VkQueueFamilyCheckpointPropertiesNV                          queueFamilyCheckpointProperties [ __C_ENG_VULKAN_CORE_QUEUE_FAMILY_MAX_COUNT ];

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE

static VkQueueFamilyGlobalPriorityPropertiesEXT                     queueFamilyGlobalPriorityProperties [ __C_ENG_VULKAN_CORE_QUEUE_FAMILY_MAX_COUNT ];

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE

static VkQueueFamilyQueryResultStatusPropertiesKHR                  queueFamilyQueryResultStatusProperties [ __C_ENG_VULKAN_CORE_QUEUE_FAMILY_MAX_COUNT ];
static VkVideoQueueFamilyPropertiesKHR                              videoQueueFamilyProperties [ __C_ENG_VULKAN_CORE_QUEUE_FAMILY_MAX_COUNT ];

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

static VkPerformanceCounterKHR                                      counters [ __C_ENG_VULKAN_CORE_QUEUE_FAMILY_PERFORMANCE_COUNTER_MAX_COUNT ];
static VkPerformanceCounterDescriptionKHR                           counterDescriptions [ __C_ENG_VULKAN_CORE_QUEUE_FAMILY_PERFORMANCE_COUNTER_MAX_COUNT ];

#endif


#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

static VkPhysicalDeviceGroupProperties                              physicalDeviceGroupProperties [ __C_ENG_VULKAN_CORE_PHYSICAL_DEVICE_GROUP_MAX_COUNT ];

#endif

static VkDeviceCreateInfo                                           deviceCreateInfo;


static PFN_vkCreateDebugUtilsMessengerEXT                                   pVkInstanceProcessCreateDebugMessenger                                       = nullptr;
static PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR  pVkInstanceProcessEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCounters = nullptr;


/**
 * ---------------------------------------------------------
 * ---------------------------------------------------------
 * -------- Vulkan 1.1 Device Properties Convertors --------
 * ---------------------------------------------------------
 * ---------------------------------------------------------
 */
#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceVulkan11Properties ) * pOut,
        VkPhysicalDeviceVulkan11Properties                    const * pIn
) noexcept -> void {

    if ( pOut == nullptr || pIn == nullptr ) {
        return;
    }

    pOut->deviceNodeMask                    = pIn->deviceNodeMask;
    pOut->subgroupSize                      = pIn->subgroupSize;
    pOut->maxMultiviewViewCount             = pIn->maxMultiviewViewCount;
    pOut->maxMultiviewInstanceIndex         = pIn->maxMultiviewInstanceIndex;
    pOut->maxPerSetDescriptors              = pIn->maxPerSetDescriptors;

    pOut->deviceLUIDValid                   = pIn->deviceLUIDValid;
    pOut->subgroupQuadOperationsInAllStages = pIn->subgroupQuadOperationsInAllStages;
    pOut->protectedNoFault                  = pIn->protectedNoFault;

    pOut->subgroupSupportedStages           = pIn->subgroupSupportedStages;

    pOut->subgroupSupportedOperations       = pIn->subgroupSupportedOperations;

    pOut->pointClippingBehavior             = static_cast < vulkan :: __C_ENG_TYPE ( PointClippingBehavior ) > ( pIn->pointClippingBehavior );

    pOut->maxMemoryAllocationSize           = pIn->maxMemoryAllocationSize;

    (void) std :: memcpy ( pOut->deviceUUID, pIn->deviceUUID, sizeof ( pIn->deviceUUID[0] ) * VK_UUID_SIZE ); // NOLINT(clion-misra-cpp2008-5-2-12)
    (void) std :: memcpy ( pOut->driverUUID, pIn->driverUUID, sizeof ( pIn->driverUUID[0] ) * VK_UUID_SIZE ); // NOLINT(clion-misra-cpp2008-5-2-12)
    (void) std :: memcpy ( pOut->deviceLUID, pIn->deviceLUID, sizeof ( pIn->deviceLUID[0] ) * VK_LUID_SIZE ); // NOLINT(clion-misra-cpp2008-5-2-12)
}

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceIDProperties ) * pOut,
        VkPhysicalDeviceIDProperties                    const * pIn
) noexcept -> void {

    if ( pOut == nullptr || pIn == nullptr ) {
        return;
    }

    pOut->deviceNodeMask                    = pIn->deviceNodeMask;
    pOut->deviceLUIDValid                   = pIn->deviceLUIDValid;

    (void) std :: memcpy ( pOut->deviceUUID, pIn->deviceUUID, sizeof ( pIn->deviceUUID[0] ) * VK_UUID_SIZE ); // NOLINT(clion-misra-cpp2008-5-2-12)
    (void) std :: memcpy ( pOut->driverUUID, pIn->driverUUID, sizeof ( pIn->driverUUID[0] ) * VK_UUID_SIZE ); // NOLINT(clion-misra-cpp2008-5-2-12)
    (void) std :: memcpy ( pOut->deviceLUID, pIn->deviceLUID, sizeof ( pIn->deviceLUID[0] ) * VK_LUID_SIZE ); // NOLINT(clion-misra-cpp2008-5-2-12)
}

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceMaintenanceProperties ) * pOut,
        VkPhysicalDeviceMaintenance3Properties                   const * pIn
) noexcept -> void {

    if ( pOut == nullptr || pIn == nullptr ) {
        return;
    }

    pOut->maxPerSetDescriptors              = pIn->maxPerSetDescriptors;
    pOut->maxMemoryAllocationSize           = pIn->maxMemoryAllocationSize;
}

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceMultiviewProperties ) * pOut,
        VkPhysicalDeviceMultiviewProperties                    const * pIn
) noexcept -> void {

    if ( pOut == nullptr || pIn == nullptr ) {
        return;
    }

    pOut->maxMultiviewViewCount             = pIn->maxMultiviewViewCount;
    pOut->maxMultiviewInstanceIndex         = pIn->maxMultiviewInstanceIndex;
}

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDevicePointClippingProperties ) * pOut,
        VkPhysicalDevicePointClippingProperties                    const * pIn
) noexcept -> void {

    if ( pOut == nullptr || pIn == nullptr ) {
        return;
    }

    pOut->pointClippingBehavior             = static_cast < vulkan :: __C_ENG_TYPE ( PointClippingBehavior ) > ( pIn->pointClippingBehavior );
}

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceProtectedMemoryProperties ) * pOut,
        VkPhysicalDeviceProtectedMemoryProperties                    const * pIn
) noexcept -> void {

    if ( pOut == nullptr || pIn == nullptr ) {
        return;
    }

    pOut->protectedNoFault             = pIn->protectedNoFault;
}

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceSubgroupProperties ) * pOut,
        VkPhysicalDeviceSubgroupProperties                    const * pIn
) noexcept -> void {

    if ( pOut == nullptr || pIn == nullptr ) {
        return;
    }

    pOut->subgroupSize              = pIn->subgroupSize;
    pOut->supportedStages           = pIn->supportedStages;
    pOut->supportedOperations       = pIn->supportedOperations;
    pOut->quadOperationsInAllStages = pIn->quadOperationsInAllStages;
}

#endif

/**
 * ---------------------------------------------------------
 * ---------------------------------------------------------
 * -------- Vulkan 1.2 Device Properties Convertors --------
 * ---------------------------------------------------------
 * ---------------------------------------------------------
 */
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( ConformanceVersion ) * pIn,
        VkConformanceVersion                    const * pOut
) noexcept -> void {

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

    pIn->patch      = pOut->patch;
    pIn->major      = pOut->major;
    pIn->minor      = pOut->minor;
    pIn->subminor   = pOut->subminor;
}

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceVulkan12Properties ) * pOut,
        VkPhysicalDeviceVulkan12Properties                    const * pIn
) noexcept -> void {

    if ( pOut == nullptr || pIn == nullptr ) {
        return;
    }

    pOut->driverID                                                  = static_cast < vulkan :: __C_ENG_TYPE ( DriverID ) > ( pIn->driverID );
    (void) std :: memcpy ( pOut->driverName,                        pIn->driverName, sizeof ( pIn->driverName[0] ) * VK_MAX_DRIVER_NAME_SIZE ); // NOLINT(clion-misra-cpp2008-5-2-12)
    (void) std :: memcpy ( pOut->driverInfo,                        pIn->driverInfo, sizeof ( pIn->driverInfo[0] ) * VK_MAX_DRIVER_INFO_SIZE ); // NOLINT(clion-misra-cpp2008-5-2-12)
    fromVulkanFormat ( & pOut->conformanceVersion,                  & pIn->conformanceVersion );

    pOut->denormBehaviorIndependence                                = static_cast < vulkan :: __C_ENG_TYPE ( ShaderFloatControlsIndependence ) > ( pIn->denormBehaviorIndependence );
    pOut->roundingModeIndependence                                  = static_cast < vulkan :: __C_ENG_TYPE ( ShaderFloatControlsIndependence ) > ( pIn->roundingModeIndependence );

    pOut->shaderSignedZeroInfNanPreserveFloat16                     = pIn->shaderSignedZeroInfNanPreserveFloat16;
    pOut->shaderSignedZeroInfNanPreserveFloat32                     = pIn->shaderSignedZeroInfNanPreserveFloat32;
    pOut->shaderSignedZeroInfNanPreserveFloat64                     = pIn->shaderSignedZeroInfNanPreserveFloat64;

    pOut->shaderDenormPreserveFloat16                               = pIn->shaderDenormPreserveFloat16;
    pOut->shaderDenormPreserveFloat32                               = pIn->shaderDenormPreserveFloat32;
    pOut->shaderDenormPreserveFloat64                               = pIn->shaderDenormPreserveFloat64;
    pOut->shaderDenormFlushToZeroFloat16                            = pIn->shaderDenormFlushToZeroFloat16;
    pOut->shaderDenormFlushToZeroFloat32                            = pIn->shaderDenormFlushToZeroFloat32;
    pOut->shaderDenormFlushToZeroFloat64                            = pIn->shaderDenormFlushToZeroFloat64;

    pOut->shaderRoundingModeRTEFloat16                              = pIn->shaderRoundingModeRTEFloat16;
    pOut->shaderRoundingModeRTEFloat32                              = pIn->shaderRoundingModeRTEFloat32;
    pOut->shaderRoundingModeRTEFloat64                              = pIn->shaderRoundingModeRTEFloat64;
    pOut->shaderRoundingModeRTZFloat16                              = pIn->shaderRoundingModeRTZFloat16;
    pOut->shaderRoundingModeRTZFloat32                              = pIn->shaderRoundingModeRTZFloat32;
    pOut->shaderRoundingModeRTZFloat64                              = pIn->shaderRoundingModeRTZFloat64;

    pOut->maxUpdateAfterBindDescriptorsInAllPools                   = pIn->maxUpdateAfterBindDescriptorsInAllPools;

    pOut->shaderUniformBufferArrayNonUniformIndexingNative          = pIn->shaderUniformBufferArrayNonUniformIndexingNative;
    pOut->shaderSampledImageArrayNonUniformIndexingNative           = pIn->shaderSampledImageArrayNonUniformIndexingNative;
    pOut->shaderStorageBufferArrayNonUniformIndexingNative          = pIn->shaderStorageBufferArrayNonUniformIndexingNative;
    pOut->shaderStorageImageArrayNonUniformIndexingNative           = pIn->shaderStorageImageArrayNonUniformIndexingNative;
    pOut->shaderInputAttachmentArrayNonUniformIndexingNative        = pIn->shaderInputAttachmentArrayNonUniformIndexingNative;

    pOut->robustBufferAccessUpdateAfterBind                         = pIn->robustBufferAccessUpdateAfterBind;

    pOut->quadDivergentImplicitLod                                  = pIn->quadDivergentImplicitLod;

    pOut->maxPerStageDescriptorUpdateAfterBindSamplers              = pIn->maxPerStageDescriptorUpdateAfterBindSamplers;
    pOut->maxPerStageDescriptorUpdateAfterBindUniformBuffers        = pIn->maxPerStageDescriptorUpdateAfterBindUniformBuffers;
    pOut->maxPerStageDescriptorUpdateAfterBindStorageBuffers        = pIn->maxPerStageDescriptorUpdateAfterBindStorageBuffers;
    pOut->maxPerStageDescriptorUpdateAfterBindSampledImages         = pIn->maxPerStageDescriptorUpdateAfterBindSampledImages;
    pOut->maxPerStageDescriptorUpdateAfterBindStorageImages         = pIn->maxPerStageDescriptorUpdateAfterBindStorageImages;
    pOut->maxPerStageDescriptorUpdateAfterBindInputAttachments      = pIn->maxPerStageDescriptorUpdateAfterBindInputAttachments;

    pOut->maxPerStageUpdateAfterBindResources                       = pIn->maxPerStageUpdateAfterBindResources;

    pOut->maxDescriptorSetUpdateAfterBindSamplers                   = pIn->maxDescriptorSetUpdateAfterBindSamplers;
    pOut->maxDescriptorSetUpdateAfterBindUniformBuffers             = pIn->maxDescriptorSetUpdateAfterBindUniformBuffers;
    pOut->maxDescriptorSetUpdateAfterBindUniformBuffersDynamic      = pIn->maxDescriptorSetUpdateAfterBindUniformBuffersDynamic;
    pOut->maxDescriptorSetUpdateAfterBindStorageBuffers             = pIn->maxDescriptorSetUpdateAfterBindStorageBuffers;
    pOut->maxDescriptorSetUpdateAfterBindStorageBuffersDynamic      = pIn->maxDescriptorSetUpdateAfterBindStorageBuffersDynamic;
    pOut->maxDescriptorSetUpdateAfterBindSampledImages              = pIn->maxDescriptorSetUpdateAfterBindSampledImages;
    pOut->maxDescriptorSetUpdateAfterBindStorageImages              = pIn->maxDescriptorSetUpdateAfterBindStorageImages;
    pOut->maxDescriptorSetUpdateAfterBindInputAttachments           = pIn->maxDescriptorSetUpdateAfterBindInputAttachments;

    pOut->supportedDepthResolveModes                                = pIn->supportedDepthResolveModes;
    pOut->supportedStencilResolveModes                              = pIn->supportedStencilResolveModes;

    pOut->independentResolveNone                                    = pIn->independentResolveNone;
    pOut->independentResolve                                        = pIn->independentResolve;

    pOut->filterMinmaxSingleComponentFormats                        = pIn->filterMinmaxSingleComponentFormats;
    pOut->filterMinmaxImageComponentMapping                         = pIn->filterMinmaxImageComponentMapping;

    pOut->maxTimelineSemaphoreValueDifference                       = pIn->maxTimelineSemaphoreValueDifference;

    pOut->framebufferIntegerColorSampleCounts                       = pIn->framebufferIntegerColorSampleCounts;
}

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceDepthStencilResolveProperties ) * pOut,
        VkPhysicalDeviceDepthStencilResolveProperties                    const * pIn
) noexcept -> void {

    if ( pOut == nullptr || pIn == nullptr ) {
        return;
    }

    pOut->supportedDepthResolveModes                                = pIn->supportedDepthResolveModes;
    pOut->supportedStencilResolveModes                              = pIn->supportedStencilResolveModes;

    pOut->independentResolveNone                                    = pIn->independentResolveNone;
    pOut->independentResolve                                        = pIn->independentResolve;
}

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceDescriptorIndexingProperties ) * pOut,
        VkPhysicalDeviceDescriptorIndexingProperties                    const * pIn
) noexcept -> void {

    if ( pOut == nullptr || pIn == nullptr ) {
        return;
    }

    pOut->maxUpdateAfterBindDescriptorsInAllPools                   = pIn->maxUpdateAfterBindDescriptorsInAllPools;

    pOut->shaderUniformBufferArrayNonUniformIndexingNative          = pIn->shaderUniformBufferArrayNonUniformIndexingNative;
    pOut->shaderSampledImageArrayNonUniformIndexingNative           = pIn->shaderSampledImageArrayNonUniformIndexingNative;
    pOut->shaderStorageBufferArrayNonUniformIndexingNative          = pIn->shaderStorageBufferArrayNonUniformIndexingNative;
    pOut->shaderStorageImageArrayNonUniformIndexingNative           = pIn->shaderStorageImageArrayNonUniformIndexingNative;
    pOut->shaderInputAttachmentArrayNonUniformIndexingNative        = pIn->shaderInputAttachmentArrayNonUniformIndexingNative;

    pOut->robustBufferAccessUpdateAfterBind                         = pIn->robustBufferAccessUpdateAfterBind;

    pOut->quadDivergentImplicitLod                                  = pIn->quadDivergentImplicitLod;

    pOut->maxPerStageDescriptorUpdateAfterBindSamplers              = pIn->maxPerStageDescriptorUpdateAfterBindSamplers;
    pOut->maxPerStageDescriptorUpdateAfterBindUniformBuffers        = pIn->maxPerStageDescriptorUpdateAfterBindUniformBuffers;
    pOut->maxPerStageDescriptorUpdateAfterBindStorageBuffers        = pIn->maxPerStageDescriptorUpdateAfterBindStorageBuffers;
    pOut->maxPerStageDescriptorUpdateAfterBindSampledImages         = pIn->maxPerStageDescriptorUpdateAfterBindSampledImages;
    pOut->maxPerStageDescriptorUpdateAfterBindStorageImages         = pIn->maxPerStageDescriptorUpdateAfterBindStorageImages;
    pOut->maxPerStageDescriptorUpdateAfterBindInputAttachments      = pIn->maxPerStageDescriptorUpdateAfterBindInputAttachments;

    pOut->maxPerStageUpdateAfterBindResources                       = pIn->maxPerStageUpdateAfterBindResources;

    pOut->maxDescriptorSetUpdateAfterBindSamplers                   = pIn->maxDescriptorSetUpdateAfterBindSamplers;
    pOut->maxDescriptorSetUpdateAfterBindUniformBuffers             = pIn->maxDescriptorSetUpdateAfterBindUniformBuffers;
    pOut->maxDescriptorSetUpdateAfterBindUniformBuffersDynamic      = pIn->maxDescriptorSetUpdateAfterBindUniformBuffersDynamic;
    pOut->maxDescriptorSetUpdateAfterBindStorageBuffers             = pIn->maxDescriptorSetUpdateAfterBindStorageBuffers;
    pOut->maxDescriptorSetUpdateAfterBindStorageBuffersDynamic      = pIn->maxDescriptorSetUpdateAfterBindStorageBuffersDynamic;
    pOut->maxDescriptorSetUpdateAfterBindSampledImages              = pIn->maxDescriptorSetUpdateAfterBindSampledImages;
    pOut->maxDescriptorSetUpdateAfterBindStorageImages              = pIn->maxDescriptorSetUpdateAfterBindStorageImages;
    pOut->maxDescriptorSetUpdateAfterBindInputAttachments           = pIn->maxDescriptorSetUpdateAfterBindInputAttachments;
}

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceDriverProperties ) * pOut,
        VkPhysicalDeviceDriverProperties                    const * pIn
) noexcept -> void {

    if ( pOut == nullptr || pIn == nullptr ) {
        return;
    }

    pOut->driverID                                                  = static_cast < vulkan :: __C_ENG_TYPE ( DriverID ) > ( pIn->driverID );
    (void) std :: memcpy ( pOut->driverName,                        pIn->driverName, sizeof ( pIn->driverName[0] ) * VK_MAX_DRIVER_NAME_SIZE ); // NOLINT(clion-misra-cpp2008-5-2-12)
    (void) std :: memcpy ( pOut->driverInfo,                        pIn->driverInfo, sizeof ( pIn->driverInfo[0] ) * VK_MAX_DRIVER_INFO_SIZE ); // NOLINT(clion-misra-cpp2008-5-2-12)
    fromVulkanFormat ( & pOut->conformanceVersion,                  & pIn->conformanceVersion );
}

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceFloatControlsProperties ) * pOut,
        VkPhysicalDeviceFloatControlsProperties                    const * pIn
) noexcept -> void {

    if ( pOut == nullptr || pIn == nullptr ) {
        return;
    }

    pOut->denormBehaviorIndependence                                = static_cast < vulkan :: __C_ENG_TYPE ( ShaderFloatControlsIndependence ) > ( pIn->denormBehaviorIndependence );
    pOut->roundingModeIndependence                                  = static_cast < vulkan :: __C_ENG_TYPE ( ShaderFloatControlsIndependence ) > ( pIn->roundingModeIndependence );

    pOut->shaderSignedZeroInfNanPreserveFloat16                     = pIn->shaderSignedZeroInfNanPreserveFloat16;
    pOut->shaderSignedZeroInfNanPreserveFloat32                     = pIn->shaderSignedZeroInfNanPreserveFloat32;
    pOut->shaderSignedZeroInfNanPreserveFloat64                     = pIn->shaderSignedZeroInfNanPreserveFloat64;

    pOut->shaderDenormPreserveFloat16                               = pIn->shaderDenormPreserveFloat16;
    pOut->shaderDenormPreserveFloat32                               = pIn->shaderDenormPreserveFloat32;
    pOut->shaderDenormPreserveFloat64                               = pIn->shaderDenormPreserveFloat64;
    pOut->shaderDenormFlushToZeroFloat16                            = pIn->shaderDenormFlushToZeroFloat16;
    pOut->shaderDenormFlushToZeroFloat32                            = pIn->shaderDenormFlushToZeroFloat32;
    pOut->shaderDenormFlushToZeroFloat64                            = pIn->shaderDenormFlushToZeroFloat64;

    pOut->shaderRoundingModeRTEFloat16                              = pIn->shaderRoundingModeRTEFloat16;
    pOut->shaderRoundingModeRTEFloat32                              = pIn->shaderRoundingModeRTEFloat32;
    pOut->shaderRoundingModeRTEFloat64                              = pIn->shaderRoundingModeRTEFloat64;
    pOut->shaderRoundingModeRTZFloat16                              = pIn->shaderRoundingModeRTZFloat16;
    pOut->shaderRoundingModeRTZFloat32                              = pIn->shaderRoundingModeRTZFloat32;
    pOut->shaderRoundingModeRTZFloat64                              = pIn->shaderRoundingModeRTZFloat64;
}

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceSamplerFilterMinmaxProperties ) * pOut,
        VkPhysicalDeviceSamplerFilterMinmaxProperties                    const * pIn
) noexcept -> void {

    if ( pOut == nullptr || pIn == nullptr ) {
        return;
    }

    pOut->filterMinmaxSingleComponentFormats                        = pIn->filterMinmaxSingleComponentFormats;
    pOut->filterMinmaxImageComponentMapping                         = pIn->filterMinmaxImageComponentMapping;
}

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceTimelineSemaphoreProperties ) * pOut,
        VkPhysicalDeviceTimelineSemaphoreProperties                    const * pIn
) noexcept -> void {

    if ( pOut == nullptr || pIn == nullptr ) {
        return;
    }

    pOut->maxTimelineSemaphoreValueDifference                       = pIn->maxTimelineSemaphoreValueDifference;
}


#endif


/**
 * ---------------------------------------------------------
 * ---------------------------------------------------------
 * ---- Vulkan Extensions Device Properties Converters -----
 * ---------------------------------------------------------
 * ---------------------------------------------------------
 */
#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceBlendOperationAdvancedProperties ) * pOut,
        VkPhysicalDeviceBlendOperationAdvancedPropertiesEXT                 const * pIn
) noexcept -> void {

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

    pOut->advancedBlendMaxColorAttachments          = pIn->advancedBlendMaxColorAttachments;
    pOut->advancedBlendIndependentBlend             = pIn->advancedBlendIndependentBlend;
    pOut->advancedBlendNonPremultipliedSrcColor     = pIn->advancedBlendNonPremultipliedSrcColor;
    pOut->advancedBlendNonPremultipliedDstColor     = pIn->advancedBlendNonPremultipliedDstColor;
    pOut->advancedBlendCorrelatedOverlap            = pIn->advancedBlendCorrelatedOverlap;
    pOut->advancedBlendAllOperations                = pIn->advancedBlendAllOperations;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONSERVATIVE_RASTERIZATION_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceConservativeRasterizationProperties ) * pOut,
        VkPhysicalDeviceConservativeRasterizationPropertiesEXT                 const * pIn
) noexcept -> void {

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

    pOut->primitiveOverestimationSize                   = pIn->primitiveOverestimationSize;
    pOut->maxExtraPrimitiveOverestimationSize           = pIn->maxExtraPrimitiveOverestimationSize;
    pOut->extraPrimitiveOverestimationSizeGranularity   = pIn->extraPrimitiveOverestimationSizeGranularity;
    pOut->primitiveUnderestimation                      = pIn->primitiveUnderestimation;
    pOut->conservativePointAndLineRasterization         = pIn->conservativePointAndLineRasterization;
    pOut->degenerateTrianglesRasterized                 = pIn->degenerateTrianglesRasterized;
    pOut->degenerateLinesRasterized                     = pIn->degenerateLinesRasterized;
    pOut->fullyCoveredFragmentShaderInputVariable       = pIn->fullyCoveredFragmentShaderInputVariable;
    pOut->conservativeRasterizationPostDepthCoverage    = pIn->conservativeRasterizationPostDepthCoverage;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceCustomBorderColorProperties ) * pOut,
        VkPhysicalDeviceCustomBorderColorPropertiesEXT                 const * pIn
) noexcept -> void {

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

    pOut->maxCustomBorderColorSamplers                  = pIn->maxCustomBorderColorSamplers;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISCARD_RECTANGLES_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceDiscardRectangleProperties ) * pOut,
        VkPhysicalDeviceDiscardRectanglePropertiesEXT                 const * pIn
) noexcept -> void {

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

    pOut->maxDiscardRectangles                  = pIn->maxDiscardRectangles;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTERNAL_MEMORY_HOST_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceExternalMemoryHostProperties ) * pOut,
        VkPhysicalDeviceExternalMemoryHostPropertiesEXT                 const * pIn
) noexcept -> void {

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

    pOut->minImportedHostPointerAlignment                  = pIn->minImportedHostPointerAlignment;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMapProperties ) * pOut,
        VkPhysicalDeviceFragmentDensityMapPropertiesEXT                 const * pIn
) noexcept -> void {

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

    pOut->minFragmentDensityTexelSize                   = pIn->minFragmentDensityTexelSize;
    pOut->maxFragmentDensityTexelSize                   = pIn->maxFragmentDensityTexelSize;
    pOut->fragmentDensityInvocations                    = pIn->fragmentDensityInvocations;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMap2Properties ) * pOut,
        VkPhysicalDeviceFragmentDensityMap2PropertiesEXT                 const * pIn
) noexcept -> void {

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

    pOut->subsampledLoads                           = pIn->subsampledLoads;
    pOut->subsampledCoarseReconstructionEarlyAccess = pIn->subsampledCoarseReconstructionEarlyAccess;
    pOut->maxSubsampledArrayLayers                  = pIn->maxSubsampledArrayLayers;
    pOut->maxDescriptorSetSubsampledSamplers        = pIn->maxDescriptorSetSubsampledSamplers;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceInlineUniformBlockProperties ) * pOut,
        VkPhysicalDeviceInlineUniformBlockPropertiesEXT                 const * pIn
) noexcept -> void {

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

    pOut->maxInlineUniformBlockSize                                 = pIn->maxInlineUniformBlockSize;
    pOut->maxPerStageDescriptorInlineUniformBlocks                  = pIn->maxPerStageDescriptorInlineUniformBlocks;
    pOut->maxPerStageDescriptorUpdateAfterBindInlineUniformBlocks   = pIn->maxPerStageDescriptorUpdateAfterBindInlineUniformBlocks;
    pOut->maxDescriptorSetInlineUniformBlocks                       = pIn->maxDescriptorSetInlineUniformBlocks;
    pOut->maxDescriptorSetUpdateAfterBindInlineUniformBlocks        = pIn->maxDescriptorSetUpdateAfterBindInlineUniformBlocks;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceLineRasterizationProperties ) * pOut,
        VkPhysicalDeviceLineRasterizationPropertiesEXT                 const * pIn
) noexcept -> void {

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

    pOut->lineSubPixelPrecisionBits                                 = pIn->lineSubPixelPrecisionBits;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceMultiDrawProperties ) * pOut,
        VkPhysicalDeviceMultiDrawPropertiesEXT                 const * pIn
) noexcept -> void {

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

    pOut->maxMultiDrawCount                                 = pIn->maxMultiDrawCount;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PCI_BUS_INFO_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDevicePCIBusInfoProperties ) * pOut,
        VkPhysicalDevicePCIBusInfoPropertiesEXT                 const * pIn
) noexcept -> void {

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

    pOut->pciDomain    = pIn->pciDomain;
    pOut->pciBus       = pIn->pciBus;
    pOut->pciDevice    = pIn->pciDevice;
    pOut->pciFunction  = pIn->pciFunction;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PHYSICAL_DEVICE_DRM_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceDRMProperties ) * pOut,
        VkPhysicalDeviceDrmPropertiesEXT                 const * pIn
) noexcept -> void {

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

    pOut->hasPrimary    = pIn->hasPrimary;
    pOut->hasRender     = pIn->hasRender;
    pOut->primaryMajor  = pIn->primaryMajor;
    pOut->primaryMinor  = pIn->primaryMinor;
    pOut->renderMajor   = pIn->renderMajor;
    pOut->renderMinor   = pIn->renderMinor;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceProvokingVertexProperties ) * pOut,
        VkPhysicalDeviceProvokingVertexPropertiesEXT                 const * pIn
) noexcept -> void {

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

    pOut->provokingVertexModePerPipeline                        = pIn->provokingVertexModePerPipeline;
    pOut->transformFeedbackPreservesTriangleFanProvokingVertex  = pIn->transformFeedbackPreservesTriangleFanProvokingVertex;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceRobustnessProperties ) * pOut,
        VkPhysicalDeviceRobustness2PropertiesEXT                const * pIn
) noexcept -> void {

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

    pOut->robustStorageBufferAccessSizeAlignment                        = pIn->robustStorageBufferAccessSizeAlignment;
    pOut->robustUniformBufferAccessSizeAlignment                        = pIn->robustUniformBufferAccessSizeAlignment;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceSampleLocationsProperties ) * pOut,
        VkPhysicalDeviceSampleLocationsPropertiesEXT                 const * pIn
) noexcept -> void {

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

    pOut->sampleLocationSampleCounts                        = pIn->sampleLocationSampleCounts;
    pOut->maxSampleLocationGridSize                         = pIn->maxSampleLocationGridSize;
    pOut->sampleLocationSubPixelBits                        = pIn->sampleLocationSubPixelBits;
    pOut->variableSampleLocations                           = pIn->variableSampleLocations;

    pOut->sampleLocationCoordinateRange[0]                  = pIn->sampleLocationCoordinateRange[0];
    pOut->sampleLocationCoordinateRange[1]                  = pIn->sampleLocationCoordinateRange[1];
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceSubgroupSizeControlProperties ) * pOut,
        VkPhysicalDeviceSubgroupSizeControlPropertiesEXT                 const * pIn
) noexcept -> void {

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

    pOut->minSubgroupSize                               = pIn->minSubgroupSize;
    pOut->maxSubgroupSize                               = pIn->maxSubgroupSize;
    pOut->maxComputeWorkgroupSubgroups                  = pIn->maxComputeWorkgroupSubgroups;
    pOut->requiredSubgroupSizeStages                    = pIn->requiredSubgroupSizeStages;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceTexelBufferAlignmentProperties ) * pOut,
        VkPhysicalDeviceTexelBufferAlignmentPropertiesEXT                 const * pIn
) noexcept -> void {

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

    pOut->storageTexelBufferOffsetAlignmentBytes        = pIn->storageTexelBufferOffsetAlignmentBytes;
    pOut->storageTexelBufferOffsetSingleTexelAlignment  = pIn->storageTexelBufferOffsetSingleTexelAlignment;
    pOut->uniformTexelBufferOffsetAlignmentBytes        = pIn->uniformTexelBufferOffsetAlignmentBytes;
    pOut->uniformTexelBufferOffsetSingleTexelAlignment  = pIn->uniformTexelBufferOffsetSingleTexelAlignment;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceTransformFeedbackProperties ) * pOut,
        VkPhysicalDeviceTransformFeedbackPropertiesEXT                 const * pIn
) noexcept -> void {

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

    pOut->maxTransformFeedbackStreams                   = pIn->maxTransformFeedbackStreams;
    pOut->maxTransformFeedbackBuffers                   = pIn->maxTransformFeedbackBuffers;
    pOut->maxTransformFeedbackBufferSize                = pIn->maxTransformFeedbackBufferSize;
    pOut->maxTransformFeedbackStreamDataSize            = pIn->maxTransformFeedbackStreamDataSize;
    pOut->maxTransformFeedbackBufferDataSize            = pIn->maxTransformFeedbackBufferDataSize;
    pOut->maxTransformFeedbackBufferDataStride          = pIn->maxTransformFeedbackBufferDataStride;
    pOut->transformFeedbackQueries                      = pIn->transformFeedbackQueries;
    pOut->transformFeedbackStreamsLinesTriangles        = pIn->transformFeedbackStreamsLinesTriangles;
    pOut->transformFeedbackRasterizationStreamSelect    = pIn->transformFeedbackRasterizationStreamSelect;
    pOut->transformFeedbackDraw                         = pIn->transformFeedbackDraw;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceVertexAttributeDivisorProperties ) * pOut,
        VkPhysicalDeviceVertexAttributeDivisorPropertiesEXT                 const * pIn
) noexcept -> void {

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

    pOut->maxVertexAttribDivisor                         = pIn->maxVertexAttribDivisor;
}

#endif


/**
 * ----------------------------------------------------------------
 * ----------------------------------------------------------------
 * ---- Vulkan Khronos Extensions Device Properties Convertors ----
 * ----------------------------------------------------------------
 * ----------------------------------------------------------------
 */
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceAccelerationStructureProperties ) * pOut,
        VkPhysicalDeviceAccelerationStructurePropertiesKHR                 const * pIn
) noexcept -> void {

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

    pOut->maxGeometryCount                                           = pIn->maxGeometryCount;
    pOut->maxInstanceCount                                           = pIn->maxInstanceCount;
    pOut->maxPrimitiveCount                                          = pIn->maxPrimitiveCount;
    pOut->maxPerStageDescriptorAccelerationStructures                = pIn->maxPerStageDescriptorAccelerationStructures;
    pOut->maxPerStageDescriptorUpdateAfterBindAccelerationStructures = pIn->maxPerStageDescriptorUpdateAfterBindAccelerationStructures;
    pOut->maxDescriptorSetAccelerationStructures                     = pIn->maxDescriptorSetAccelerationStructures;
    pOut->maxDescriptorSetUpdateAfterBindAccelerationStructures      = pIn->maxDescriptorSetUpdateAfterBindAccelerationStructures;
    pOut->minAccelerationStructureScratchOffsetAlignment             = pIn->minAccelerationStructureScratchOffsetAlignment;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceFragmentShadingRateProperties ) * pOut,
        VkPhysicalDeviceFragmentShadingRatePropertiesKHR                 const * pIn
) noexcept -> void {

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

    pOut->maxFragmentShadingRateAttachmentTexelSize                 = pIn->maxFragmentShadingRateAttachmentTexelSize;
    pOut->minFragmentShadingRateAttachmentTexelSize                 = pIn->minFragmentShadingRateAttachmentTexelSize;
    pOut->maxFragmentShadingRateAttachmentTexelSizeAspectRatio      = pIn->maxFragmentShadingRateAttachmentTexelSizeAspectRatio;
    pOut->primitiveFragmentShadingRateWithMultipleViewports         = pIn->primitiveFragmentShadingRateWithMultipleViewports;
    pOut->layeredShadingRateAttachments                             = pIn->layeredShadingRateAttachments;

    pOut->fragmentShadingRateNonTrivialCombinerOps                  = pIn->fragmentShadingRateNonTrivialCombinerOps;
    pOut->maxFragmentSize                                           = pIn->maxFragmentSize;
    pOut->maxFragmentSizeAspectRatio                                = pIn->maxFragmentSizeAspectRatio;
    pOut->maxFragmentShadingRateCoverageSamples                     = pIn->maxFragmentShadingRateCoverageSamples;
    pOut->maxFragmentShadingRateRasterizationSamples                = static_cast < vulkan :: __C_ENG_TYPE ( SampleCountFlag ) > ( pIn->maxFragmentShadingRateRasterizationSamples );

    pOut->fragmentShadingRateWithShaderDepthStencilWrites           = pIn->fragmentShadingRateWithShaderDepthStencilWrites;
    pOut->fragmentShadingRateWithSampleMask                         = pIn->fragmentShadingRateWithSampleMask;
    pOut->fragmentShadingRateWithShaderSampleMask                   = pIn->fragmentShadingRateWithShaderSampleMask;
    pOut->fragmentShadingRateWithConservativeRasterization          = pIn->fragmentShadingRateWithConservativeRasterization;
    pOut->fragmentShadingRateWithFragmentShaderInterlock            = pIn->fragmentShadingRateWithFragmentShaderInterlock;

    pOut->fragmentShadingRateWithCustomSampleLocations              = pIn->fragmentShadingRateWithCustomSampleLocations;
    pOut->fragmentShadingRateStrictMultiplyCombiner                 = pIn->fragmentShadingRateStrictMultiplyCombiner;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceMaintenance4Properties ) * pOut,
        VkPhysicalDeviceMaintenance4PropertiesKHR                 const * pIn
) noexcept -> void {

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

    pOut->maxBufferSize                 = pIn->maxBufferSize;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDevicePerformanceQueryProperties ) * pOut,
        VkPhysicalDevicePerformanceQueryPropertiesKHR                 const * pIn
) noexcept -> void {

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

    pOut->allowCommandBufferQueryCopies                 = pIn->allowCommandBufferQueryCopies;
}

#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDevicePortabilitySubsetProperties ) * pOut,
        VkPhysicalDevicePortabilitySubsetPropertiesKHR                 const * pIn
) noexcept -> void {

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

    pOut->minVertexInputBindingStrideAlignment                 = pIn->minVertexInputBindingStrideAlignment;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PUSH_DESCRIPTOR_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDevicePushDescriptorProperties ) * pOut,
        VkPhysicalDevicePushDescriptorPropertiesKHR                 const * pIn
) noexcept -> void {

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

    pOut->maxPushDescriptors                 = pIn->maxPushDescriptors;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceRayTracingPipelineProperties ) * pOut,
        VkPhysicalDeviceRayTracingPipelinePropertiesKHR                 const * pIn
) noexcept -> void {

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

    pOut->shaderGroupHandleSize                = pIn->shaderGroupHandleSize;
    pOut->maxRayRecursionDepth                 = pIn->maxRayRecursionDepth;
    pOut->maxShaderGroupStride                 = pIn->maxShaderGroupStride;
    pOut->shaderGroupBaseAlignment             = pIn->shaderGroupBaseAlignment;
    pOut->shaderGroupHandleCaptureReplaySize   = pIn->shaderGroupHandleCaptureReplaySize;
    pOut->maxRayDispatchInvocationCount        = pIn->maxRayDispatchInvocationCount;
    pOut->shaderGroupHandleAlignment           = pIn->shaderGroupHandleAlignment;
    pOut->maxRayHitAttributeSize               = pIn->maxRayHitAttributeSize;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderIntegerDotProductProperties ) * pOut,
        VkPhysicalDeviceShaderIntegerDotProductPropertiesKHR                 const * pIn
) noexcept -> void {

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

    pOut->integerDotProduct8BitUnsignedAccelerated                                      = pIn->integerDotProduct8BitUnsignedAccelerated;
    pOut->integerDotProduct8BitSignedAccelerated                                        = pIn->integerDotProduct8BitSignedAccelerated;
    pOut->integerDotProduct8BitMixedSignednessAccelerated                               = pIn->integerDotProduct8BitMixedSignednessAccelerated;

    pOut->integerDotProduct4x8BitPackedUnsignedAccelerated                              = pIn->integerDotProduct4x8BitPackedUnsignedAccelerated;
    pOut->integerDotProduct4x8BitPackedSignedAccelerated                                = pIn->integerDotProduct4x8BitPackedSignedAccelerated;
    pOut->integerDotProduct4x8BitPackedMixedSignednessAccelerated                       = pIn->integerDotProduct4x8BitPackedMixedSignednessAccelerated;

    pOut->integerDotProduct16BitUnsignedAccelerated                                     = pIn->integerDotProduct16BitUnsignedAccelerated;
    pOut->integerDotProduct16BitSignedAccelerated                                       = pIn->integerDotProduct16BitSignedAccelerated;
    pOut->integerDotProduct16BitMixedSignednessAccelerated                              = pIn->integerDotProduct16BitMixedSignednessAccelerated;

    pOut->integerDotProduct32BitUnsignedAccelerated                                     = pIn->integerDotProduct32BitUnsignedAccelerated;
    pOut->integerDotProduct32BitSignedAccelerated                                       = pIn->integerDotProduct32BitSignedAccelerated;
    pOut->integerDotProduct32BitMixedSignednessAccelerated                              = pIn->integerDotProduct32BitMixedSignednessAccelerated;

    pOut->integerDotProduct64BitUnsignedAccelerated                                     = pIn->integerDotProduct64BitUnsignedAccelerated;
    pOut->integerDotProduct64BitSignedAccelerated                                       = pIn->integerDotProduct64BitSignedAccelerated;
    pOut->integerDotProduct64BitMixedSignednessAccelerated                              = pIn->integerDotProduct64BitMixedSignednessAccelerated;

    pOut->integerDotProductAccumulatingSaturating8BitUnsignedAccelerated                = pIn->integerDotProductAccumulatingSaturating8BitUnsignedAccelerated;
    pOut->integerDotProductAccumulatingSaturating8BitSignedAccelerated                  = pIn->integerDotProductAccumulatingSaturating8BitSignedAccelerated;
    pOut->integerDotProductAccumulatingSaturating8BitMixedSignednessAccelerated         = pIn->integerDotProductAccumulatingSaturating8BitMixedSignednessAccelerated;

    pOut->integerDotProductAccumulatingSaturating4x8BitPackedUnsignedAccelerated        = pIn->integerDotProductAccumulatingSaturating4x8BitPackedUnsignedAccelerated;
    pOut->integerDotProductAccumulatingSaturating4x8BitPackedSignedAccelerated          = pIn->integerDotProductAccumulatingSaturating4x8BitPackedSignedAccelerated;
    pOut->integerDotProductAccumulatingSaturating4x8BitPackedMixedSignednessAccelerated = pIn->integerDotProductAccumulatingSaturating4x8BitPackedMixedSignednessAccelerated;

    pOut->integerDotProductAccumulatingSaturating16BitUnsignedAccelerated               = pIn->integerDotProductAccumulatingSaturating16BitUnsignedAccelerated;
    pOut->integerDotProductAccumulatingSaturating16BitSignedAccelerated                 = pIn->integerDotProductAccumulatingSaturating16BitSignedAccelerated;
    pOut->integerDotProductAccumulatingSaturating16BitMixedSignednessAccelerated        = pIn->integerDotProductAccumulatingSaturating16BitMixedSignednessAccelerated;

    pOut->integerDotProductAccumulatingSaturating32BitUnsignedAccelerated               = pIn->integerDotProductAccumulatingSaturating32BitUnsignedAccelerated;
    pOut->integerDotProductAccumulatingSaturating32BitSignedAccelerated                 = pIn->integerDotProductAccumulatingSaturating32BitSignedAccelerated;
    pOut->integerDotProductAccumulatingSaturating32BitMixedSignednessAccelerated        = pIn->integerDotProductAccumulatingSaturating32BitMixedSignednessAccelerated;

    pOut->integerDotProductAccumulatingSaturating64BitUnsignedAccelerated               = pIn->integerDotProductAccumulatingSaturating64BitUnsignedAccelerated;
    pOut->integerDotProductAccumulatingSaturating64BitSignedAccelerated                 = pIn->integerDotProductAccumulatingSaturating64BitSignedAccelerated;
    pOut->integerDotProductAccumulatingSaturating64BitMixedSignednessAccelerated        = pIn->integerDotProductAccumulatingSaturating64BitMixedSignednessAccelerated;
}

#endif


/**
 * ---------------------------------------------------------------
 * ---------------------------------------------------------------
 * ---- Vulkan NVidia Extensions Device Properties Converters ----
 * ---------------------------------------------------------------
 * ---------------------------------------------------------------
 */
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceCooperativeMatrixPropertiesNVidia ) * pOut,
        VkPhysicalDeviceCooperativeMatrixPropertiesNV                        const * pIn
) noexcept -> void {

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

    pOut->cooperativeMatrixSupportedStages        = pIn->cooperativeMatrixSupportedStages;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceDeviceGeneratedCommandsPropertiesNVidia ) * pOut,
        VkPhysicalDeviceDeviceGeneratedCommandsPropertiesNV                        const * pIn
) noexcept -> void {

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

    pOut->maxGraphicsShaderGroupCount               = pIn->maxGraphicsShaderGroupCount;
    pOut->maxIndirectSequenceCount                  = pIn->maxIndirectSequenceCount;
    pOut->maxIndirectCommandsTokenCount             = pIn->maxIndirectCommandsTokenCount;
    pOut->maxIndirectCommandsStreamCount            = pIn->maxIndirectCommandsStreamCount;
    pOut->maxIndirectCommandsTokenOffset            = pIn->maxIndirectCommandsTokenOffset;
    pOut->maxIndirectCommandsStreamStride           = pIn->maxIndirectCommandsStreamStride;
    pOut->minSequencesCountBufferOffsetAlignment    = pIn->minSequencesCountBufferOffsetAlignment;
    pOut->minSequencesIndexBufferOffsetAlignment    = pIn->minSequencesIndexBufferOffsetAlignment;
    pOut->minIndirectCommandsBufferOffsetAlignment  = pIn->minIndirectCommandsBufferOffsetAlignment;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceFragmentShadingRateEnumsPropertiesNVidia ) * pOut,
        VkPhysicalDeviceFragmentShadingRateEnumsPropertiesNV                        const * pIn
) noexcept -> void {

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

    pOut->maxFragmentShadingRateInvocationCount  = static_cast < vulkan :: __C_ENG_TYPE ( SampleCountFlag ) > ( pIn->maxFragmentShadingRateInvocationCount );
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceMeshShaderPropertiesNVidia ) * pOut,
        VkPhysicalDeviceMeshShaderPropertiesNV                        const * pIn
) noexcept -> void {

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

    pOut->maxDrawMeshTasksCount             = pIn->maxDrawMeshTasksCount;
    pOut->maxTaskWorkGroupInvocations       = pIn->maxTaskWorkGroupInvocations;
    pOut->maxTaskTotalMemorySize            = pIn->maxTaskTotalMemorySize;
    pOut->maxTaskOutputCount                = pIn->maxTaskOutputCount;
    pOut->maxMeshWorkGroupInvocations       = pIn->maxMeshWorkGroupInvocations;
    pOut->maxMeshTotalMemorySize            = pIn->maxMeshTotalMemorySize;
    pOut->maxMeshOutputVertices             = pIn->maxMeshOutputVertices;
    pOut->maxMeshOutputPrimitives           = pIn->maxMeshOutputPrimitives;
    pOut->maxMeshMultiviewViewCount         = pIn->maxMeshMultiviewViewCount;
    pOut->meshOutputPerVertexGranularity    = pIn->meshOutputPerVertexGranularity;
    pOut->meshOutputPerPrimitiveGranularity = pIn->meshOutputPerPrimitiveGranularity;

    pOut->maxTaskWorkGroupSize[0]           = pIn->maxTaskWorkGroupSize[0];
    pOut->maxTaskWorkGroupSize[1]           = pIn->maxTaskWorkGroupSize[1];
    pOut->maxTaskWorkGroupSize[2]           = pIn->maxTaskWorkGroupSize[2];

    pOut->maxMeshWorkGroupSize[0]           = pIn->maxMeshWorkGroupSize[0];
    pOut->maxMeshWorkGroupSize[1]           = pIn->maxMeshWorkGroupSize[1];
    pOut->maxMeshWorkGroupSize[2]           = pIn->maxMeshWorkGroupSize[2];
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceRayTracingPropertiesNVidia ) * pOut,
        VkPhysicalDeviceRayTracingPropertiesNV                        const * pIn
) noexcept -> void {

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

    pOut->shaderGroupHandleSize                     = pIn->shaderGroupHandleSize;
    pOut->maxRecursionDepth                         = pIn->maxRecursionDepth;
    pOut->maxShaderGroupStride                      = pIn->maxShaderGroupStride;
    pOut->shaderGroupBaseAlignment                  = pIn->shaderGroupBaseAlignment;
    pOut->maxGeometryCount                          = pIn->maxGeometryCount;
    pOut->maxInstanceCount                          = pIn->maxInstanceCount;
    pOut->maxTriangleCount                          = pIn->maxTriangleCount;
    pOut->maxDescriptorSetAccelerationStructures    = pIn->maxDescriptorSetAccelerationStructures;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderSMBuiltinsPropertiesNVidia ) * pOut,
        VkPhysicalDeviceShaderSMBuiltinsPropertiesNV                        const * pIn
) noexcept -> void {

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

    pOut->shaderSMCount         = pIn->shaderSMCount;
    pOut->shaderWarpsPerSM      = pIn->shaderWarpsPerSM;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceShadingRateImagePropertiesNVidia ) * pOut,
        VkPhysicalDeviceShadingRateImagePropertiesNV                        const * pIn
) noexcept -> void {

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

    pOut->shadingRateTexelSize          = pIn->shadingRateTexelSize;
    pOut->shadingRatePaletteSize        = pIn->shadingRatePaletteSize;
    pOut->shadingRateMaxCoarseSamples   = pIn->shadingRateMaxCoarseSamples;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceMultiviewPerViewAttributesPropertiesNVidia ) * pOut,
        VkPhysicalDeviceMultiviewPerViewAttributesPropertiesNVX                       const * pIn
) noexcept -> void {

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

    pOut->perViewPositionAllComponents   = pIn->perViewPositionAllComponents;
}

#endif


/**
 * ------------------------------------------------------------
 * ------------------------------------------------------------
 * ---- Vulkan AMD Extensions Device Properties Converters ----
 * ------------------------------------------------------------
 * ------------------------------------------------------------
 */
#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderCorePropertiesAMD ) * pOut,
        VkPhysicalDeviceShaderCorePropertiesAMD                    const * pIn
) noexcept -> void {

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

    pOut->shaderEngineCount             = pIn->shaderEngineCount;
    pOut->shaderArraysPerEngineCount    = pIn->shaderArraysPerEngineCount;
    pOut->computeUnitsPerShaderArray    = pIn->computeUnitsPerShaderArray;
    pOut->simdPerComputeUnit            = pIn->simdPerComputeUnit;
    pOut->wavefrontsPerSimd             = pIn->wavefrontsPerSimd;
    pOut->wavefrontSize                 = pIn->wavefrontSize;
    pOut->sgprsPerSimd                  = pIn->sgprsPerSimd;
    pOut->minSgprAllocation             = pIn->minSgprAllocation;
    pOut->maxSgprAllocation             = pIn->maxSgprAllocation;
    pOut->sgprAllocationGranularity     = pIn->sgprAllocationGranularity;
    pOut->vgprsPerSimd                  = pIn->vgprsPerSimd;
    pOut->minVgprAllocation             = pIn->minVgprAllocation;
    pOut->maxVgprAllocation             = pIn->maxVgprAllocation;
    pOut->vgprAllocationGranularity     = pIn->vgprAllocationGranularity;

}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_2_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderCoreProperties2AMD ) * pOut,
        VkPhysicalDeviceShaderCoreProperties2AMD                    const * pIn
) noexcept -> void {

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

    pOut->shaderCoreFeatures            = pIn->shaderCoreFeatures;
    pOut->activeComputeUnitCount        = pIn->activeComputeUnitCount;
}

#endif


/**
 * -----------------------------------------------------------------
 * -----------------------------------------------------------------
 * ---- Vulkan Qualcomm Extensions Device Properties Converters ----
 * -----------------------------------------------------------------
 * -----------------------------------------------------------------
 */
#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMapOffsetPropertiesQualcomm ) * pOut,
        VkPhysicalDeviceFragmentDensityMapOffsetPropertiesQCOM                        const * pIn
) noexcept -> void {

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

    pOut->fragmentDensityOffsetGranularity        = pIn->fragmentDensityOffsetGranularity;
}

#endif


/**
 * ---------------------------------------------------------------
 * ---------------------------------------------------------------
 * ---- Vulkan Huawei Extensions Device Properties Converters ----
 * ---------------------------------------------------------------
 * ---------------------------------------------------------------
 */
#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceSubpassShadingPropertiesHuawei ) * pOut,
        VkPhysicalDeviceSubpassShadingPropertiesHUAWEI                    const * pIn
) noexcept -> void {

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

    pOut->maxSubpassShadingWorkgroupSizeAspectRatio        = pIn->maxSubpassShadingWorkgroupSizeAspectRatio;
}

#endif


inline static auto toVulkanFormat (
        vulkan :: __C_ENG_TYPE ( ApplicationInfo )  const * pApplicationInfo,
        VkApplicationInfo                                 * pVkApplicationInfo
) noexcept -> void {

    if ( pApplicationInfo == nullptr || pVkApplicationInfo == nullptr ) {
        return;
    }

    * pVkApplicationInfo = {
            .sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO,
            .pNext              = nullptr,
            .pApplicationName   = pApplicationInfo->name,
            .applicationVersion = instanceVersionToUInt32 ( pApplicationInfo->version ),
            .pEngineName        = pApplicationInfo->engineName,
            .engineVersion      = instanceVersionToUInt32 ( pApplicationInfo->engineVersion ),
            .apiVersion         = instanceVersionToUInt32 ( pApplicationInfo->apiVersion )
    };
}

inline static auto toVulkanFormat (
        vulkan :: __C_ENG_TYPE ( AllocationCallbacks )  const * pAllocationCallbacks,
        VkAllocationCallbacks                                 * pVkAllocationCallbacks
) noexcept -> void {

    if ( pAllocationCallbacks == nullptr || pVkAllocationCallbacks == nullptr ) {
        return;
    }

    * pVkAllocationCallbacks = {
            .pUserData              = pAllocationCallbacks->pUserData,
            .pfnAllocation          = pAllocationCallbacks->allocationCallback,
            .pfnReallocation        = pAllocationCallbacks->reallocationCallback,
            .pfnFree                = pAllocationCallbacks->freeCallback,
            .pfnInternalAllocation  = pAllocationCallbacks->internalAllocationNotificationCallback,
            .pfnInternalFree        = pAllocationCallbacks->internalFreeNotificationCallback
    };
}

inline static auto toVulkanFormat (
        vulkan :: __C_ENG_TYPE ( InstanceCreateInfo )   const * pCreateInfo,
        VkInstanceCreateInfo                                  * pVkCreateInfo,
        VkApplicationInfo                               const * pVkApplicationInfo,
        void                                            const * pNext
) noexcept -> void {

    if ( pCreateInfo == nullptr || pVkCreateInfo == nullptr ) {
        return;
    }

    * pVkCreateInfo = {
            .sType                      = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
            .pNext                      = pNext,
            .flags                      = pCreateInfo->flags,
            .pApplicationInfo           = pVkApplicationInfo,
            .enabledLayerCount          = pCreateInfo->enabledLayerCount,
            .ppEnabledLayerNames        = pCreateInfo->pEnabledLayerNames,
            .enabledExtensionCount      = pCreateInfo->enabledExtensionCount,
            .ppEnabledExtensionNames    = pCreateInfo->pEnabledExtensionNames
    };
}

inline static auto toVulkanFormat (
        vulkan :: __C_ENG_TYPE ( DebugMessengerCreateInfo ) const * pCreateInfo,
        VkDebugUtilsMessengerCreateInfoEXT                        * pVkCreateInfo
) noexcept -> void {

    if ( pCreateInfo == nullptr || pVkCreateInfo == nullptr ) {
        return;
    }

    * pVkCreateInfo = {
            .sType                  = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
            .pNext                  = nullptr,
            .flags                  = pCreateInfo->flags,
            .messageSeverity        = pCreateInfo->messageSeverityFlags,
            .messageType            = pCreateInfo->messageTypeFlags,
            .pfnUserCallback        = pCreateInfo->callback,
            .pUserData              = pCreateInfo->pCallbackUserData
    };
}

inline static auto toVulkanFormat (
        vulkan :: __C_ENG_TYPE ( ValidationFeatures )   const * pValidationFeatures,
        VkValidationFeaturesEXT                               * pVkValidationFeatures
) noexcept -> void {

    if ( pValidationFeatures == nullptr || pVkValidationFeatures == nullptr ) {
        return;
    }

    for ( uint32 i = 0U; i < pValidationFeatures->enabledValidationFeatureCount; ++ i ) {
        validationFeatureEnables[i] = static_cast < VkValidationFeatureEnableEXT > ( pValidationFeatures->pEnabledValidationFeatures[i] );
    }

    for ( uint32 i = 0U; i < pValidationFeatures->disabledValidationFeatureCount; ++ i ) {
        validationFeatureDisables[i] = static_cast < VkValidationFeatureDisableEXT > ( pValidationFeatures->pDisabledValidationFeatures[i] );
    }

    * pVkValidationFeatures = {
            .sType                          = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT,
            .pNext                          = nullptr,
            .enabledValidationFeatureCount  = pValidationFeatures->enabledValidationFeatureCount,
            .pEnabledValidationFeatures     = validationFeatureEnables,
            .disabledValidationFeatureCount = pValidationFeatures->disabledValidationFeatureCount,
            .pDisabledValidationFeatures    = validationFeatureDisables
    };
}

auto vulkan :: enumerateInstanceVersion (
        uint32 * pOutRawVersion
) noexcept -> vulkan :: __C_ENG_TYPE ( Result ) {

    return static_cast < vulkan :: __C_ENG_TYPE ( Result ) > ( vkEnumerateInstanceVersion ( pOutRawVersion ) );
}

auto vulkan :: enumerateInstanceLayerProperties (
        uint32                              * pLayerPropertiesCount,
        __C_ENG_TYPE ( LayerProperties )    * pProperties
) noexcept -> __C_ENG_TYPE ( Result ) {

    if ( pLayerPropertiesCount == nullptr ) {
        return __C_ENG_TYPE ( Result ) :: ResultErrorIllegalArgument;
    }

    if ( pProperties == nullptr ) {
        return static_cast < __C_ENG_TYPE ( Result ) > ( vkEnumerateInstanceLayerProperties (
                pLayerPropertiesCount,
                nullptr
        ));
    }

    if ( * pLayerPropertiesCount > __C_ENG_VULKAN_CORE_LAYER_MAX_COUNT ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

    result = vkEnumerateInstanceLayerProperties (
            pLayerPropertiesCount,
            & layerProperties[0]
    );

    if ( result != VkResult :: VK_SUCCESS ) {
        return static_cast < __C_ENG_TYPE ( Result ) > ( result );
    }

    for ( uint32 i = 0U; i < * pLayerPropertiesCount; ++ i ) {
        (void) std :: memcpy ( pProperties[i].layerName,   layerProperties[i].layerName,   VK_MAX_EXTENSION_NAME_SIZE ); // NOLINT(clion-misra-cpp2008-5-2-12)
        (void) std :: memcpy ( pProperties[i].description, layerProperties[i].description, VK_MAX_DESCRIPTION_SIZE ); // NOLINT(clion-misra-cpp2008-5-2-12)
        pProperties[i].implementationVersion    = layerProperties[i].implementationVersion;
        pProperties[i].specVersion              = uInt32ToInstanceVersion ( layerProperties[i].specVersion );
    }

    return __C_ENG_TYPE ( Result ) :: ResultSuccess;
}

__C_ENG_MAYBE_UNUSED auto vulkan :: enumerateDeviceLayerProperties (
        __C_ENG_TYPE ( PhysicalDeviceHandle )   handle,
        uint32                                * pLayerPropertiesCount,
        __C_ENG_TYPE ( LayerProperties )      * pProperties
) noexcept -> __C_ENG_TYPE ( Result ) {

    if (
            handle                  == nullptr ||
            pLayerPropertiesCount   == nullptr
    ) {
        return __C_ENG_TYPE ( Result ) :: ResultErrorIllegalArgument;
    }

    if ( pProperties == nullptr ) {
        return static_cast < __C_ENG_TYPE ( Result ) > (
                vkEnumerateDeviceLayerProperties (
                        handle,
                        pLayerPropertiesCount,
                        nullptr
        ));
    }

    if ( * pLayerPropertiesCount > __C_ENG_VULKAN_CORE_LAYER_MAX_COUNT ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

    result = vkEnumerateDeviceLayerProperties (
            handle,
            pLayerPropertiesCount,
            & layerProperties[0]
    );

    if ( result != VkResult :: VK_SUCCESS ) {
        return static_cast < __C_ENG_TYPE ( Result ) > ( result );
    }

    for ( uint32 i = 0U; i < * pLayerPropertiesCount; ++ i ) {
        (void) std :: memcpy ( pProperties[i].layerName,   layerProperties[i].layerName,   VK_MAX_EXTENSION_NAME_SIZE ); // NOLINT(clion-misra-cpp2008-5-2-12)
        (void) std :: memcpy ( pProperties[i].description, layerProperties[i].description, VK_MAX_DESCRIPTION_SIZE ); // NOLINT(clion-misra-cpp2008-5-2-12)
        pProperties[i].implementationVersion    = layerProperties[i].implementationVersion;
        pProperties[i].specVersion              = uInt32ToInstanceVersion ( layerProperties[i].specVersion );
    }

    return __C_ENG_TYPE ( Result ) :: ResultSuccess;
}

auto vulkan :: enumerateInstanceExtensionProperties (
        StringLiteral                           layerName,
        uint32                                * pPropertyCount,
        __C_ENG_TYPE ( ExtensionProperties )  * pProperties
) noexcept -> __C_ENG_TYPE ( Result ) {

    if ( pPropertyCount == nullptr ) {
        return ResultErrorIllegalArgument;
    }

    if ( pProperties == nullptr ) {
        return static_cast < __C_ENG_TYPE ( Result ) > ( vkEnumerateInstanceExtensionProperties (
                layerName,
                pPropertyCount,
                nullptr
        ));
    }

    if ( * pPropertyCount > __C_ENG_VULKAN_CORE_LAYER_EXTENSION_MAX_COUNT ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

    result = vkEnumerateInstanceExtensionProperties(
            layerName,
            pPropertyCount,
            & extensionProperties[0]
    );

    if ( result != VkResult :: VK_SUCCESS ) {
        return static_cast < __C_ENG_TYPE ( Result ) > ( result );
    }

    for ( uint32 i = 0U; i < * pPropertyCount; ++ i ) {
        (void) std :: memcpy ( pProperties[i].name, extensionProperties[i].extensionName, VK_MAX_EXTENSION_NAME_SIZE ); // NOLINT(clion-misra-cpp2008-5-2-12)
        pProperties[i].specVersion = extensionProperties[i].specVersion;
    }

    return ResultSuccess;
}

auto vulkan :: createInstance (
        __C_ENG_TYPE ( InstanceCreateInfo )     const * pCreateInfo,
        __C_ENG_TYPE ( AllocationCallbacks )    const * pAllocationCallbacks,
        __C_ENG_TYPE ( InstanceHandle )               * pInstanceHandle
) noexcept -> __C_ENG_TYPE ( Result ) {

    if (
            pCreateInfo     == nullptr ||
            pInstanceHandle == nullptr
    ) {
        return ResultErrorIllegalArgument;
    }

    VkAllocationCallbacks             * pUsedAllocationCallbacks = nullptr;
    VkBaseInStructure                 * pPreviousInChain = nullptr;

    void                        const * pInstanceNext = nullptr;

    if ( pAllocationCallbacks != nullptr ) {
        pUsedAllocationCallbacks = & allocationCallbacks;
        toVulkanFormat ( pAllocationCallbacks, pUsedAllocationCallbacks );
    }

    auto currentGenericStructure = reinterpret_cast < __C_ENG_TYPE ( GenericInStructure ) const * > ( pCreateInfo->pNext );

    while ( currentGenericStructure != nullptr ) {
        VkBaseInStructure * pCurrentInChain = nullptr;

        if ( currentGenericStructure->structureType == StructureTypeDebugUtilsMessengerCreateInfo ) {
            auto currentStructure = reinterpret_cast < __C_ENG_TYPE ( DebugMessengerCreateInfo ) const * > ( currentGenericStructure );
            toVulkanFormat ( currentStructure, & messengerCreateInfo );
            pCurrentInChain = reinterpret_cast < VkBaseInStructure * > ( & messengerCreateInfo );
        }

        if ( currentGenericStructure->structureType == StructureTypeValidationFeatures ) {
            auto currentStructure = reinterpret_cast < __C_ENG_TYPE ( ValidationFeatures ) const * > ( currentGenericStructure );

            if (
                    validationFeatures.enabledValidationFeatureCount    > __C_ENG_VULKAN_CORE_VALIDATION_FEATURE_ENABLE_MAX_COUNT ||
                    validationFeatures.disabledValidationFeatureCount   > __C_ENG_VULKAN_CORE_VALIDATION_FEATURE_DISABLE_MAX_COUNT
            ) {
                return ResultErrorConfigurationArraySizeSmall;
            }

            toVulkanFormat ( currentStructure, & validationFeatures );
            pCurrentInChain = reinterpret_cast < VkBaseInStructure * > ( & validationFeatures );
        }

        if ( pInstanceNext == nullptr ) {
            pInstanceNext = pCurrentInChain;
        }

        if ( pPreviousInChain != nullptr ) {
            pPreviousInChain->pNext = pCurrentInChain;
        }

        pPreviousInChain = pCurrentInChain;
        currentGenericStructure = reinterpret_cast < __C_ENG_TYPE ( GenericInStructure ) const * > ( currentGenericStructure->pNext );
    }

    toVulkanFormat ( pCreateInfo->pApplicationInfo, & applicationInfo );
    toVulkanFormat ( pCreateInfo, & instanceCreateInfo, & applicationInfo, pInstanceNext );

    return static_cast < __C_ENG_TYPE ( Result ) > (
            vkCreateInstance (
                    & instanceCreateInfo,
                    pUsedAllocationCallbacks,
                    pInstanceHandle
            )
    );
}

auto vulkan :: destroyInstance (
        __C_ENG_TYPE ( InstanceHandle )                 handle,
        __C_ENG_TYPE ( AllocationCallbacks )    const * pAllocatorCallbacks
) noexcept -> __C_ENG_TYPE ( Result ) {

    if ( handle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

    VkAllocationCallbacks * pUsedCallbacks = nullptr;

    if ( pAllocatorCallbacks != nullptr ) {
        pUsedCallbacks = & allocationCallbacks;
        toVulkanFormat ( pAllocatorCallbacks, pUsedCallbacks );
    }

    vkDestroyInstance ( handle, pUsedCallbacks );
    return ResultSuccess;
}

auto vulkan :: createDebugMessenger (
        __C_ENG_TYPE ( InstanceHandle )                     instanceHandle,
        __C_ENG_TYPE ( DebugMessengerCreateInfo )   const * pMessengerCreateInfo,
        __C_ENG_TYPE ( AllocationCallbacks )        const * pAllocationCallbacks,
        __C_ENG_TYPE ( DebugMessengerHandle )             * pHandle
) noexcept -> __C_ENG_TYPE ( Result ) {

    if ( pMessengerCreateInfo == nullptr || pHandle == nullptr || instanceHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

    VkAllocationCallbacks             * pUsedAllocationCallbacks = nullptr;

    if ( pVkInstanceProcessCreateDebugMessenger == nullptr ) {

        auto lResult = vulkan :: getInstanceFunctionAddress (
                instanceHandle,
                __C_ENG_VULKAN_CORE_FUNCTION_NAME_CREATE_DEBUG_MESSENGER,
                reinterpret_cast < void ** > ( & pVkInstanceProcessCreateDebugMessenger )
        );
    }

    if ( pAllocationCallbacks != nullptr ) {
        pUsedAllocationCallbacks = & allocationCallbacks;
        toVulkanFormat ( pAllocationCallbacks, pUsedAllocationCallbacks );
    }

    toVulkanFormat (
            pMessengerCreateInfo,
            & messengerCreateInfo
    );

    return static_cast < __C_ENG_TYPE ( Result ) > ( pVkInstanceProcessCreateDebugMessenger (
            instanceHandle,
            & messengerCreateInfo,
            pUsedAllocationCallbacks,
            pHandle
    ));
}

auto vulkan :: destroyDebugMessenger (
        __C_ENG_TYPE ( InstanceHandle )                 instanceHandle,
        __C_ENG_TYPE ( DebugMessengerHandle )           debugMessengerHandle,
        __C_ENG_TYPE ( AllocationCallbacks )    const * pAllocationCallbacks
) noexcept -> __C_ENG_TYPE ( Result ) {

    if ( instanceHandle == nullptr || debugMessengerHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

    PFN_vkDestroyDebugUtilsMessengerEXT function = nullptr;
    VkAllocationCallbacks             * pUsedCallbacks = nullptr;

    function = reinterpret_cast < PFN_vkDestroyDebugUtilsMessengerEXT > (
            vkGetInstanceProcAddr ( instanceHandle, __C_ENG_VULKAN_CORE_FUNCTION_NAME_DESTROY_DEBUG_MESSENGER )
    );

    if ( function == nullptr ) {
        return ResultErrorFunctionHandleNotFound;
    }

    if ( pAllocationCallbacks != nullptr ) {
        pUsedCallbacks = & allocationCallbacks;
        toVulkanFormat ( pAllocationCallbacks, pUsedCallbacks );
    }

    function ( instanceHandle, debugMessengerHandle, pUsedCallbacks );
    return ResultSuccess;
}

auto vulkan :: enumeratePhysicalDevices (
        __C_ENG_TYPE ( InstanceHandle )             handle,
        uint32                                    * pPhysicalDeviceCount,
        __C_ENG_TYPE ( PhysicalDeviceHandle )     * pPhysicalDevices
) noexcept -> __C_ENG_TYPE ( Result ) {

    if ( pPhysicalDeviceCount == nullptr || handle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

    if ( pPhysicalDevices == nullptr ) {
        return static_cast < __C_ENG_TYPE ( Result ) > ( vkEnumeratePhysicalDevices (
                handle,
                pPhysicalDeviceCount,
                nullptr
        ));
    }

    if ( * pPhysicalDeviceCount > __C_ENG_VULKAN_CORE_PHYSICAL_DEVICE_MAX_COUNT ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

    result = vkEnumeratePhysicalDevices (
            handle,
            pPhysicalDeviceCount,
            & physicalDevices[0]
    );

    if ( result != VkResult :: VK_SUCCESS ) {
        return static_cast < __C_ENG_TYPE ( Result ) > ( result );
    }

    (void) std :: memcpy ( pPhysicalDevices, physicalDevices, sizeof ( VkPhysicalDevice ) * ( * pPhysicalDeviceCount ) ); // NOLINT(clion-misra-cpp2008-5-2-12)

    return ResultSuccess;
}

auto vulkan :: createSurface (
        __C_ENG_TYPE ( InstanceHandle )                 handle,
        GLFWwindow                                    * pWindowHandle,
        __C_ENG_TYPE ( AllocationCallbacks )    const * pAllocationCallbacks,
        __C_ENG_TYPE ( SurfaceHandle )                * pSurfaceHandle
) noexcept -> __C_ENG_TYPE ( Result ) {

    VkAllocationCallbacks * pUsedCallbacks = nullptr;
    if ( pAllocationCallbacks != nullptr ) {
        pUsedCallbacks = & allocationCallbacks;
        toVulkanFormat ( pAllocationCallbacks, pUsedCallbacks );
    }

    return static_cast < __C_ENG_TYPE ( Result ) > (
            glfwCreateWindowSurface (
                    handle,
                    pWindowHandle,
                    pUsedCallbacks,
                    pSurfaceHandle
            )
    );
}

auto vulkan :: destroySurface (
        __C_ENG_TYPE ( InstanceHandle )                 instanceHandle,
        __C_ENG_TYPE ( SurfaceHandle )                  surfaceHandle,
        __C_ENG_TYPE ( AllocationCallbacks )    const * pAllocationCallbacks
) noexcept -> __C_ENG_TYPE ( Result ) {

    VkAllocationCallbacks * pUsedCallbacks = nullptr;
    if ( pAllocationCallbacks != nullptr ) {
        pUsedCallbacks = & allocationCallbacks;
        toVulkanFormat ( pAllocationCallbacks, pUsedCallbacks );
    }

    vkDestroySurfaceKHR (
            instanceHandle,
            surfaceHandle,
            pUsedCallbacks
    );

    return ResultSuccess;
}

static inline auto fromVulkanFormat (
        VkPhysicalDeviceProperties                          const * pVkProperties,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceProperties )       * pProperties
) noexcept -> void {

    if ( pProperties == nullptr || pVkProperties == nullptr ) {
        return;
    }

    pProperties->apiVersion                                                 = vulkan :: uInt32ToInstanceVersion ( pVkProperties->apiVersion );
    pProperties->driverVersion                                              = pVkProperties->driverVersion;
    pProperties->vendorID                                                   = pVkProperties->vendorID;
    pProperties->deviceID                                                   = pVkProperties->deviceID;
    pProperties->deviceType                                                 = static_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceType ) > ( pVkProperties->deviceType );

    pProperties->limits.maxImageDimension1D                                 = pVkProperties->limits.maxImageDimension1D;
    pProperties->limits.maxImageDimension2D                                 = pVkProperties->limits.maxImageDimension2D;
    pProperties->limits.maxImageDimension3D                                 = pVkProperties->limits.maxImageDimension3D;
    pProperties->limits.maxImageDimensionCube                               = pVkProperties->limits.maxImageDimensionCube;
    pProperties->limits.maxImageArrayLayers                                 = pVkProperties->limits.maxImageArrayLayers;

    pProperties->limits.maxTexelBufferElements                              = pVkProperties->limits.maxTexelBufferElements;

    pProperties->limits.maxUniformBufferRange                               = pVkProperties->limits.maxUniformBufferRange;
    pProperties->limits.maxStorageBufferRange                               = pVkProperties->limits.maxStorageBufferRange;

    pProperties->limits.maxPushConstantsSize                                = pVkProperties->limits.maxPushConstantsSize;

    pProperties->limits.maxMemoryAllocationCount                            = pVkProperties->limits.maxMemoryAllocationCount;
    pProperties->limits.maxSamplerAllocationCount                           = pVkProperties->limits.maxSamplerAllocationCount;

    pProperties->limits.bufferImageGranularity                              = pVkProperties->limits.bufferImageGranularity;
    pProperties->limits.sparseAddressSpaceSize                              = pVkProperties->limits.sparseAddressSpaceSize;

    pProperties->limits.maxBoundDescriptorSets                              = pVkProperties->limits.maxBoundDescriptorSets;

    pProperties->limits.maxPerStageDescriptorSamplers                       = pVkProperties->limits.maxPerStageDescriptorSamplers;
    pProperties->limits.maxPerStageDescriptorUniformBuffers                 = pVkProperties->limits.maxPerStageDescriptorUniformBuffers;
    pProperties->limits.maxPerStageDescriptorStorageBuffers                 = pVkProperties->limits.maxPerStageDescriptorStorageBuffers;
    pProperties->limits.maxPerStageDescriptorSampledImages                  = pVkProperties->limits.maxPerStageDescriptorSampledImages;
    pProperties->limits.maxPerStageDescriptorStorageImages                  = pVkProperties->limits.maxPerStageDescriptorStorageImages;
    pProperties->limits.maxPerStageDescriptorInputAttachments               = pVkProperties->limits.maxPerStageDescriptorInputAttachments;
    pProperties->limits.maxPerStageResources                                = pVkProperties->limits.maxPerStageResources;

    pProperties->limits.maxDescriptorSetSamplers                            = pVkProperties->limits.maxDescriptorSetSamplers;
    pProperties->limits.maxDescriptorSetUniformBuffers                      = pVkProperties->limits.maxDescriptorSetUniformBuffers;
    pProperties->limits.maxDescriptorSetUniformBuffersDynamic               = pVkProperties->limits.maxDescriptorSetUniformBuffersDynamic;
    pProperties->limits.maxDescriptorSetStorageBuffers                      = pVkProperties->limits.maxDescriptorSetStorageBuffers;
    pProperties->limits.maxDescriptorSetStorageBuffersDynamic               = pVkProperties->limits.maxDescriptorSetStorageBuffersDynamic;
    pProperties->limits.maxDescriptorSetSampledImages                       = pVkProperties->limits.maxDescriptorSetSampledImages;
    pProperties->limits.maxDescriptorSetStorageImages                       = pVkProperties->limits.maxDescriptorSetStorageImages;
    pProperties->limits.maxDescriptorSetInputAttachments                    = pVkProperties->limits.maxDescriptorSetInputAttachments;

    pProperties->limits.maxVertexInputAttributes                            = pVkProperties->limits.maxVertexInputAttributes;
    pProperties->limits.maxVertexInputBindings                              = pVkProperties->limits.maxVertexInputBindings;
    pProperties->limits.maxVertexInputAttributeOffset                       = pVkProperties->limits.maxVertexInputAttributeOffset;
    pProperties->limits.maxVertexInputBindingStride                         = pVkProperties->limits.maxVertexInputBindingStride;
    pProperties->limits.maxVertexOutputComponents                           = pVkProperties->limits.maxVertexOutputComponents;

    pProperties->limits.maxTessellationGenerationLevel                      = pVkProperties->limits.maxTessellationGenerationLevel;
    pProperties->limits.maxTessellationPatchSize                            = pVkProperties->limits.maxTessellationPatchSize;
    pProperties->limits.maxTessellationControlPerVertexInputComponents      = pVkProperties->limits.maxTessellationControlPerVertexInputComponents;
    pProperties->limits.maxTessellationControlPerVertexOutputComponents     = pVkProperties->limits.maxTessellationControlPerVertexOutputComponents;
    pProperties->limits.maxTessellationControlPerPatchOutputComponents      = pVkProperties->limits.maxTessellationControlPerPatchOutputComponents;
    pProperties->limits.maxTessellationControlTotalOutputComponents         = pVkProperties->limits.maxTessellationControlTotalOutputComponents;
    pProperties->limits.maxTessellationEvaluationInputComponents            = pVkProperties->limits.maxTessellationEvaluationInputComponents;
    pProperties->limits.maxTessellationEvaluationOutputComponents           = pVkProperties->limits.maxTessellationEvaluationOutputComponents;

    pProperties->limits.maxGeometryShaderInvocations                        = pVkProperties->limits.maxGeometryShaderInvocations;
    pProperties->limits.maxGeometryInputComponents                          = pVkProperties->limits.maxGeometryInputComponents;
    pProperties->limits.maxGeometryOutputComponents                         = pVkProperties->limits.maxGeometryOutputComponents;
    pProperties->limits.maxGeometryOutputVertices                           = pVkProperties->limits.maxGeometryOutputVertices;
    pProperties->limits.maxGeometryTotalOutputComponents                    = pVkProperties->limits.maxGeometryTotalOutputComponents;

    pProperties->limits.maxFragmentInputComponents                          = pVkProperties->limits.maxFragmentInputComponents;
    pProperties->limits.maxFragmentOutputAttachments                        = pVkProperties->limits.maxFragmentOutputAttachments;
    pProperties->limits.maxFragmentDualSourceAttachments                    = pVkProperties->limits.maxFragmentDualSrcAttachments;
    pProperties->limits.maxFragmentCombinedOutputResources                  = pVkProperties->limits.maxFragmentCombinedOutputResources;

    pProperties->limits.maxComputeSharedMemorySize                          = pVkProperties->limits.maxComputeSharedMemorySize;
    pProperties->limits.maxComputeWorkGroupInvocations                      = pVkProperties->limits.maxComputeWorkGroupInvocations;

    pProperties->limits.subPixelPrecisionBits                               = pVkProperties->limits.subPixelPrecisionBits;
    pProperties->limits.subTexelPrecisionBits                               = pVkProperties->limits.subTexelPrecisionBits;

    pProperties->limits.mipmapPrecisionBits                                 = pVkProperties->limits.mipmapPrecisionBits;

    pProperties->limits.maxDrawIndexedIndexValue                            = pVkProperties->limits.maxDrawIndexedIndexValue;
    pProperties->limits.maxDrawIndirectCount                                = pVkProperties->limits.maxDrawIndirectCount;

    pProperties->limits.maxSamplerLodBias                                   = pVkProperties->limits.maxSamplerLodBias;
    pProperties->limits.maxSamplerAnisotropy                                = pVkProperties->limits.maxSamplerAnisotropy;

    pProperties->limits.maxViewports                                        = pVkProperties->limits.maxViewports;
    pProperties->limits.viewportSubPixelBits                                = pVkProperties->limits.viewportSubPixelBits;

    pProperties->limits.minMemoryMapAlignment                               = pVkProperties->limits.minMemoryMapAlignment;

    pProperties->limits.minTexelBufferOffsetAlignment                       = pVkProperties->limits.minTexelBufferOffsetAlignment;
    pProperties->limits.minUniformBufferOffsetAlignment                     = pVkProperties->limits.minUniformBufferOffsetAlignment;
    pProperties->limits.minStorageBufferOffsetAlignment                     = pVkProperties->limits.minStorageBufferOffsetAlignment;

    pProperties->limits.minTexelOffset                                      = pVkProperties->limits.minTexelOffset;
    pProperties->limits.maxTexelOffset                                      = pVkProperties->limits.maxTexelOffset;
    pProperties->limits.minTexelGatherOffset                                = pVkProperties->limits.minTexelGatherOffset;
    pProperties->limits.maxTexelGatherOffset                                = pVkProperties->limits.maxTexelGatherOffset;

    pProperties->limits.minInterpolationOffset                              = pVkProperties->limits.minInterpolationOffset;
    pProperties->limits.maxInterpolationOffset                              = pVkProperties->limits.maxInterpolationOffset;
    pProperties->limits.subPixelInterpolationOffsetBits                     = pVkProperties->limits.subPixelInterpolationOffsetBits;

    pProperties->limits.maxFramebufferWidth                                 = pVkProperties->limits.maxFramebufferWidth;
    pProperties->limits.maxFramebufferHeight                                = pVkProperties->limits.maxFramebufferHeight;
    pProperties->limits.maxFramebufferLayers                                = pVkProperties->limits.maxFramebufferLayers;

    pProperties->limits.framebufferColorSampleCounts                        = pVkProperties->limits.framebufferColorSampleCounts;
    pProperties->limits.framebufferDepthSampleCounts                        = pVkProperties->limits.framebufferDepthSampleCounts;
    pProperties->limits.framebufferStencilSampleCounts                      = pVkProperties->limits.framebufferStencilSampleCounts;
    pProperties->limits.framebufferNoAttachmentsSampleCounts                = pVkProperties->limits.framebufferNoAttachmentsSampleCounts;

    pProperties->limits.maxColorAttachments                                 = pVkProperties->limits.maxColorAttachments;

    pProperties->limits.sampledImageColorSampleCounts                       = pVkProperties->limits.sampledImageColorSampleCounts;
    pProperties->limits.sampledImageIntegerSampleCounts                     = pVkProperties->limits.sampledImageIntegerSampleCounts;
    pProperties->limits.sampledImageDepthSampleCounts                       = pVkProperties->limits.sampledImageDepthSampleCounts;
    pProperties->limits.sampledImageStencilSampleCounts                     = pVkProperties->limits.sampledImageStencilSampleCounts;
    pProperties->limits.storageImageSampleCounts                            = pVkProperties->limits.storageImageSampleCounts;

    pProperties->limits.maxSampleMaskWords                                  = pVkProperties->limits.maxSampleMaskWords;

    pProperties->limits.timestampComputeAndGraphics                         = pVkProperties->limits.timestampComputeAndGraphics;
    pProperties->limits.timestampPeriod                                     = pVkProperties->limits.timestampPeriod;

    pProperties->limits.maxClipDistances                                    = pVkProperties->limits.maxClipDistances;
    pProperties->limits.maxCullDistances                                    = pVkProperties->limits.maxCullDistances;
    pProperties->limits.maxCombinedClipAndCullDistances                     = pVkProperties->limits.maxCombinedClipAndCullDistances;

    pProperties->limits.discreteQueuePriorities                             = pVkProperties->limits.discreteQueuePriorities;

    pProperties->limits.pointSizeGranularity                                = pVkProperties->limits.pointSizeGranularity;
    pProperties->limits.lineWidthGranularity                                = pVkProperties->limits.lineWidthGranularity;
    pProperties->limits.strictLines                                         = pVkProperties->limits.strictLines;

    pProperties->limits.standardSampleLocations                             = pVkProperties->limits.standardSampleLocations;

    pProperties->limits.optimalBufferCopyOffsetAlignment                    = pVkProperties->limits.optimalBufferCopyOffsetAlignment;
    pProperties->limits.optimalBufferCopyRowPitchAlignment                  = pVkProperties->limits.optimalBufferCopyRowPitchAlignment;

    pProperties->limits.nonCoherentAtomSize                                 = pVkProperties->limits.nonCoherentAtomSize;

    pProperties->sparseProperties.residencyStandard2DBlockShape             = pVkProperties->sparseProperties.residencyStandard2DBlockShape;
    pProperties->sparseProperties.residencyStandard2DMultisampleBlockShape  = pVkProperties->sparseProperties.residencyStandard2DMultisampleBlockShape;
    pProperties->sparseProperties.residencyStandard3DBlockShape             = pVkProperties->sparseProperties.residencyStandard3DBlockShape;
    pProperties->sparseProperties.residencyAlignedMipSize                   = pVkProperties->sparseProperties.residencyAlignedMipSize;
    pProperties->sparseProperties.residencyNonResidentStrict                = pVkProperties->sparseProperties.residencyNonResidentStrict;

    (void) std :: memcpy ( pProperties->deviceName,                         pVkProperties->deviceName,                      static_cast < uint32 > ( VK_MAX_PHYSICAL_DEVICE_NAME_SIZE ) ); // NOLINT(clion-misra-cpp2008-5-2-12)
    (void) std :: memcpy ( pProperties->pipelineCacheUUID,                  pVkProperties->pipelineCacheUUID,               VK_UUID_SIZE ); // NOLINT(clion-misra-cpp2008-5-2-12)

    (void) std :: memcpy ( pProperties->limits.maxComputeWorkGroupCount,    pVkProperties->limits.maxComputeWorkGroupCount, sizeof ( pVkProperties->limits.maxComputeWorkGroupCount[0] ) * 3U ); // NOLINT(clion-misra-cpp2008-5-2-12)
    (void) std :: memcpy ( pProperties->limits.maxComputeWorkGroupSize,     pVkProperties->limits.maxComputeWorkGroupSize,  sizeof ( pVkProperties->limits.maxComputeWorkGroupSize[0] ) * 3U ); // NOLINT(clion-misra-cpp2008-5-2-12)

    (void) std :: memcpy ( pProperties->limits.maxViewportDimensions,       pVkProperties->limits.maxViewportDimensions,    sizeof ( pVkProperties->limits.maxViewportDimensions[0] ) * 3U ); // NOLINT(clion-misra-cpp2008-5-2-12)
    (void) std :: memcpy ( pProperties->limits.viewportBoundsRange,         pVkProperties->limits.viewportBoundsRange,      sizeof ( pVkProperties->limits.viewportBoundsRange[0] ) * 3U ); // NOLINT(clion-misra-cpp2008-5-2-12)

    (void) std :: memcpy ( pProperties->limits.pointSizeRange,              pVkProperties->limits.pointSizeRange,           sizeof ( pVkProperties->limits.pointSizeRange[0] ) * 2U ); // NOLINT(clion-misra-cpp2008-5-2-12)
    (void) std :: memcpy ( pProperties->limits.lineWidthRange,              pVkProperties->limits.lineWidthRange,           sizeof ( pVkProperties->limits.lineWidthRange[0] ) * 2U ); // NOLINT(clion-misra-cpp2008-5-2-12)
}

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceFeatures )         * pDestination,
        VkPhysicalDeviceFeatures                            const * pSource
) noexcept -> void {

    if (
            pDestination    == nullptr ||
            pSource         == nullptr
    ) {
        return;
    }

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
}

__C_ENG_MAYBE_UNUSED auto vulkan :: getPhysicalDeviceProperties (
        __C_ENG_TYPE ( PhysicalDeviceHandle )       handle,
        __C_ENG_TYPE ( PhysicalDeviceProperties ) * pProperties
) noexcept -> __C_ENG_TYPE ( Result ) {

    if ( handle == nullptr || pProperties == nullptr ) {
        return ResultErrorIllegalArgument;
    }

    vkGetPhysicalDeviceProperties (
        handle,
        & deviceProperties
    );

    fromVulkanFormat ( & deviceProperties, pProperties );

    return ResultSuccess;
}

auto vulkan :: getPhysicalDeviceFeatures (
        __C_ENG_TYPE ( PhysicalDeviceHandle )       physicalDeviceHandle,
        __C_ENG_TYPE ( PhysicalDeviceFeatures )   * pPhysicalDeviceFeatures
) noexcept -> __C_ENG_TYPE ( Result ) {

    if (
            physicalDeviceHandle == nullptr ||
                    pPhysicalDeviceFeatures == nullptr
    ) {
        return ResultErrorIllegalArgument;
    }

    vkGetPhysicalDeviceFeatures (
            physicalDeviceHandle,
            & deviceFeatures
    );

    fromVulkanFormat ( pPhysicalDeviceFeatures, & deviceFeatures );

    return ResultSuccess;
}

static inline auto toVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceExtendedProperties ) const * pExtendedProperties
) noexcept -> void {

    if ( pExtendedProperties == nullptr ) {
        return;
    }

    deviceExtendedProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;

    auto currentInChain     = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericInStructure ) const * > ( pExtendedProperties->pNext );
    auto currentInVkChain   = reinterpret_cast < VkBaseOutStructure * > ( & deviceExtendedProperties );

    while ( currentInChain != nullptr ) {
        switch ( currentInChain->structureType ) {

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceVulkan_1_1_Properties:                                  { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceVulkan11Properties );                   break; }
            case engine :: vulkan :: StructureTypePhysicalDeviceIDProperties:                                           { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceIDProperties );                         break; }
            case engine :: vulkan :: StructureTypePhysicalDeviceMaintenanceProperties:                                  { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceMaintenance3Properties );               break; }
            case engine :: vulkan :: StructureTypePhysicalDeviceMultiviewProperties:                                    { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceMultiviewProperties );                  break; }
            case engine :: vulkan :: StructureTypePhysicalDevicePointClippingProperties:                                { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & devicePointClippingProperties );              break; }
            case engine :: vulkan :: StructureTypePhysicalDeviceProtectedMemoryProperties:                              { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceProtectedMemoryProperties );            break; }
            case engine :: vulkan :: StructureTypePhysicalDeviceSubgroupProperties:                                     { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceSubgroupProperties );                   break; }
                                                                                                                        
#endif                                                                                                                  
                                                                                                                        
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE                                                                            
                                                                                                                        
            case engine :: vulkan :: StructureTypePhysicalDeviceVulkan_1_2_Properties:                                  { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceVulkan12Properties );                   break; }
            case engine :: vulkan :: StructureTypePhysicalDeviceDepthStencilResolveProperties:                          { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceDepthStencilResolveProperties );        break; }
            case engine :: vulkan :: StructureTypePhysicalDeviceDescriptorIndexingProperties:                           { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceDescriptorIndexingProperties );         break; }
            case engine :: vulkan :: StructureTypePhysicalDeviceDriverProperties:                                       { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceDriverProperties );                     break; }
            case engine :: vulkan :: StructureTypePhysicalDeviceFloatControlsProperties:                                { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceFloatControlsProperties );              break; }
            case engine :: vulkan :: StructureTypePhysicalDeviceSamplerFilterMinMaxProperties:                          { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceSamplerFilterMinmaxProperties );        break; }
            case engine :: vulkan :: StructureTypePhysicalDeviceTimelineSemaphoreProperties:                            { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceTimelineSemaphoreProperties );          break; }
                                                                                                                        
#endif                                                                                                                  
                                                                                                                        
#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE                                                     
                                                                                                                        
            case engine :: vulkan :: StructureTypePhysicalDeviceBlendOperationAdvancedProperties:                       { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceBlendOperationAdvancedProperties );     break; }
                                                                                                                        
#endif                                                                                                                  
                                                                                                                        
#if __C_ENG_VULKAN_API_EXTENSION_CONSERVATIVE_RASTERIZATION_AVAILABLE                                                   
                                                                                                                        
            case engine :: vulkan :: StructureTypePhysicalDeviceConservativeRasterizationProperties:                    { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceConservativeRasterizationProperties );  break; }
                                                                                                                        
#endif                                                                                                                  
                                                                                                                        
#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE                                                          
                                                                                                                        
            case engine :: vulkan :: StructureTypePhysicalDeviceCustomBorderColorProperties:                            { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceCustomBorderColorProperties );          break; }
                                                                                                                        
#endif                                                                                                                  
                                                                                                                        
#if __C_ENG_VULKAN_API_EXTENSION_DISCARD_RECTANGLES_AVAILABLE                                                           
                                                                                                                        
            case engine :: vulkan :: StructureTypePhysicalDeviceDiscardRectangleProperties:                             { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceDiscardRectangleProperties );           break; }
                                                                                                                        
#endif                                                                                                                  
                                                                                                                        
#if __C_ENG_VULKAN_API_EXTENSION_EXTERNAL_MEMORY_HOST_AVAILABLE                                                         
                                                                                                                        
            case engine :: vulkan :: StructureTypePhysicalDeviceExternalMemoryHostProperties:                           { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceExternalMemoryHostProperties );         break; }
                                                                                                                        
#endif                                                                                                                  
                                                                                                                        
#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE                                                         
                                                                                                                        
            case engine :: vulkan :: StructureTypePhysicalDeviceFragmentDensityMapProperties:                           { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceFragmentDensityMapProperties );         break; }
                                                                                                                        
#endif                                                                                                                  
                                                                                                                        
#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE                                                       
                                                                                                                        
            case engine :: vulkan :: StructureTypePhysicalDeviceFragmentDensityMap2Properties:                          { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceFragmentDensityMap2Properties );        break; }
                                                                                                                        
#endif                                                                                                                  
                                                                                                                        
#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE                                                         
                                                                                                                        
            case engine :: vulkan :: StructureTypePhysicalDeviceInlineUniformBlockProperties:                           { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceInlineUniformBlockProperties );         break; }
                                                                                                                        
#endif                                                                                                                  
                                                                                                                        
#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE                                                           
                                                                                                                        
            case engine :: vulkan :: StructureTypePhysicalDeviceLineRasterizationProperties:                            { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceLineRasterizationProperties );          break; }
                                                                                                                        
#endif                                                                                                                  
                                                                                                                        
#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE                                                                   
                                                                                                                        
            case engine :: vulkan :: StructureTypePhysicalDeviceMultiDrawProperties:                                    { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceMultiDrawProperties );                  break; }
                                                                                                                        
#endif                                                                                                                  
                                                                                                                        
#if __C_ENG_VULKAN_API_EXTENSION_PCI_BUS_INFO_AVAILABLE                                                                 
                                                                                                                        
            case engine :: vulkan :: StructureTypePhysicalDevicePCIBusInfoProperties:                                   { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & devicePciBusInfoProperties );                 break; }
                                                                                                                        
#endif                                                                                                                  
                                                                                                                        
#if __C_ENG_VULKAN_API_EXTENSION_PHYSICAL_DEVICE_DRM_AVAILABLE                                                          
                                                                                                                        
            case engine :: vulkan :: StructureTypePhysicalDeviceDRMProperties:                                          { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceDrmProperties );                        break; }
                                                                                                                        
#endif                                                                                                                  
                                                                                                                        
#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE                                                             
                                                                                                                        
            case engine :: vulkan :: StructureTypePhysicalDeviceProvokingVertexProperties:                              { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceProvokingVertexProperties );            break; }
                                                                                                                        
#endif                                                                                                                  
                                                                                                                        
#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE                                                                   
                                                                                                                        
            case engine :: vulkan :: StructureTypePhysicalDeviceRobustnessProperties:                                   { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceRobustness2Properties );                break; }
                                                                                                                        
#endif                                                                                                                  
                                                                                                                        
#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE                                                             
                                                                                                                        
            case engine :: vulkan :: StructureTypePhysicalDeviceSampleLocationsProperties:                              { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceSampleLocationsProperties );            break; }
                                                                                                                        
#endif                                                                                                                  
                                                                                                                        
#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE                                                        
                                                                                                                        
            case engine :: vulkan :: StructureTypePhysicalDeviceSubgroupSizeControlProperties:                          { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceSubgroupSizeControlProperties );        break; }
                                                                                                                        
#endif                                                                                                                  
                                                                                                                        
#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE                                                       
                                                                                                                        
            case engine :: vulkan :: StructureTypePhysicalDeviceTexelBufferAlignmentProperties:                         { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceTexelBufferAlignmentProperties );       break; }
                                                                                                                        
#endif                                                                                                                  
                                                                                                                        
#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE                                                           
                                                                                                                        
            case engine :: vulkan :: StructureTypePhysicalDeviceTransformFeedbackProperties:                            { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceTransformFeedbackProperties );          break; }
                                                                                                                        
#endif                                                                                                                  
                                                                                                                        
#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE                                                     
                                                                                                                        
            case engine :: vulkan :: StructureTypePhysicalDeviceVertexAttributeDivisorProperties:                       { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceVertexAttributeDivisorProperties );     break; }
                                                                                                                        
#endif                                                                                                                  
                                                                                                                        
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE                                               
                                                                                                                        
            case engine :: vulkan :: StructureTypePhysicalDeviceAccelerationStructureProperties:                        { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceAccelerationStructureProperties );      break; }
                                                                                                                        
#endif                                                                                                                  
                                                                                                                        
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE                                                
                                                                                                                        
            case engine :: vulkan :: StructureTypePhysicalDeviceFragmentShadingRateProperties:                          { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceFragmentShadingRateProperties );        break; }
                                                                                                                        
#endif                                                                                                                  
                                                                                                                        
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE                                                        
                                                                                                                        
            case engine :: vulkan :: StructureTypePhysicalDeviceMaintenance4Properties:                                 { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceMaintenance4Properties );               break; }
                                                                                                                        
#endif                                                                                                                  
                                                                                                                        
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE                                                    
                                                                                                                        
            case engine :: vulkan :: StructureTypePhysicalDevicePerformanceQueryProperties:                             { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & devicePerformanceQueryProperties );           break; }

#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDevicePortabilitySubsetProperties:                            { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & devicePortabilitySubsetProperties );          break; }
                                                                                                                        
#endif                                                                                                                  
                                                                                                                        
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PUSH_DESCRIPTOR_AVAILABLE                                                      
                                                                                                                        
            case engine :: vulkan :: StructureTypePhysicalDevicePushDescriptorProperties:                               { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & devicePushDescriptorProperties );             break; }
                                                                                                                        
#endif                                                                                                                  
                                                                                                                        
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE                                                 
                                                                                                                        
            case engine :: vulkan :: StructureTypePhysicalDeviceRayTracingPipelineProperties:                           { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceRayTracingPipelineProperties );         break; }
                                                                                                                        
#endif                                                                                                                  
                                                                                                                        
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE                                           
                                                                                                                        
            case engine :: vulkan :: StructureTypePhysicalDeviceShaderIntegerDotProductProperties:                      { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceShaderIntegerDotProductProperties );    break; }
                                                                                                                        
#endif                                                                                                                  
                                                                                                                        
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE                                                    
                                                                                                                        
            case engine :: vulkan :: StructureTypePhysicalDeviceCooperativeMatrixPropertiesNVidia:                      { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceCooperativeMatrixProperties );          break; }
                                                                                                                        
#endif                                                                                                                  
                                                                                                                        
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE                                             
                                                                                                                        
            case engine :: vulkan :: StructureTypePhysicalDeviceDeviceGeneratedCommandsPropertiesNVidia:                { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceDeviceGeneratedCommandsProperties );    break; }
                                                                                                                        
#endif                                                                                                                  
                                                                                                                        
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE                                           
                                                                                                                        
            case engine :: vulkan :: StructureTypePhysicalDeviceFragmentShadingRateEnumsPropertiesNVidia:               {

                deviceFragmentShadingRateEnumsProperties.maxFragmentShadingRateInvocationCount = VkSampleCountFlagBits :: VK_SAMPLE_COUNT_1_BIT;
                currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceFragmentShadingRateEnumsProperties );   break;
            }
                                                                                                                        
#endif                                                                                                                  
                                                                                                                        
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE                                                           
                                                                                                                        
            case engine :: vulkan :: StructureTypePhysicalDeviceMeshShaderPropertiesNVidia:                             { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceMeshShaderProperties );                 break; }
                                                                                                                        
#endif                                                                                                                  
                                                                                                                        
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE                                                           
                                                                                                                        
            case engine :: vulkan :: StructureTypePhysicalDeviceRayTracingPropertiesNVidia:                             { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceRayTracingProperties );                 break; }
                                                                                                                        
#endif                                                                                                                  
                                                                                                                        
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE                                                    
                                                                                                                        
            case engine :: vulkan :: StructureTypePhysicalDeviceShaderSmBuiltinsPropertiesNVidia:                       { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceShaderSmBuiltinsProperties );           break; }
                                                                                                                        
#endif                                                                                                                  
                                                                                                                        
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE                                                    
                                                                                                                        
            case engine :: vulkan :: StructureTypePhysicalDeviceShadingRateImagePropertiesNVidia:                       { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceShadingRateImageProperties );           break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceMultiviewPerViewAttributesPropertiesNVidiaExperimental: { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceMultiviewPerViewAttributesProperties ); break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceShaderCorePropertiesAMD:                                { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceShaderCoreProperties );                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_2_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceShaderCoreProperties2AMD:                               { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceShaderCoreProperties2 );                break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceFragmentDensityMapOffsetPropertiesQualcomm:             { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceFragmentDensityMapOffsetProperties );   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceSubpassShadingPropertiesHuawei:                         { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceSubpassShadingProperties );             break; }

#endif

            default:                                                                                                    { currentInVkChain->pNext = nullptr;                                                                                    break; }
        }

        if ( currentInVkChain->pNext != nullptr ) {
            currentInVkChain->pNext->sType  = static_cast < VkStructureType > ( currentInChain->structureType );
            currentInVkChain                = currentInVkChain->pNext;
        }

        currentInChain                  = currentInChain->pNext;
    }
}

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceExtendedProperties ) * pOut,
        VkPhysicalDeviceProperties2                           const * pIn
) noexcept -> void {

    if ( pOut == nullptr || pIn == nullptr ) {
        return;
    }

    fromVulkanFormat ( & pIn->properties, & pOut->properties );
}

static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceExtendedProperties ) * pExtendedProperties
) noexcept -> void {

    if ( pExtendedProperties == nullptr ) {
        return;
    }

    if ( pExtendedProperties->structureType != vulkan :: StructureTypePhysicalDeviceProperties ) {
        return;
    }

    auto currentInChain = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( pExtendedProperties );

    while ( currentInChain != nullptr ) {
        switch ( currentInChain->structureType ) {

            case engine :: vulkan :: StructureTypePhysicalDeviceProperties:                                             { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceExtendedProperties ) * > ( currentInChain ), & deviceExtendedProperties );                                               break; }

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceVulkan_1_1_Properties:                                  { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceVulkan11Properties ) * > ( currentInChain ), & deviceVulkan11Properties );                                               break; }
            case engine :: vulkan :: StructureTypePhysicalDeviceIDProperties:                                           { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceIDProperties ) * > ( currentInChain ), & deviceIDProperties );                                                           break; }
            case engine :: vulkan :: StructureTypePhysicalDeviceMaintenanceProperties:                                  { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceMaintenanceProperties ) * > ( currentInChain ), & deviceMaintenance3Properties );                                        break; }
            case engine :: vulkan :: StructureTypePhysicalDeviceMultiviewProperties:                                    { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceMultiviewProperties ) * > ( currentInChain ), & deviceMultiviewProperties );                                             break; }
            case engine :: vulkan :: StructureTypePhysicalDevicePointClippingProperties:                                { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDevicePointClippingProperties ) * > ( currentInChain ), & devicePointClippingProperties );                                     break; }
            case engine :: vulkan :: StructureTypePhysicalDeviceProtectedMemoryProperties:                              { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceProtectedMemoryProperties ) * > ( currentInChain ), & deviceProtectedMemoryProperties );                                 break; }
            case engine :: vulkan :: StructureTypePhysicalDeviceSubgroupProperties:                                     { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceSubgroupProperties ) * > ( currentInChain ), & deviceSubgroupProperties );                                               break; }

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceVulkan_1_2_Properties:                                  { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceVulkan12Properties ) * > ( currentInChain ), & deviceVulkan12Properties );                                               break; }
            case engine :: vulkan :: StructureTypePhysicalDeviceDriverProperties:                                       { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceDriverProperties ) * > ( currentInChain ), & deviceDriverProperties );                                                   break; }
            case engine :: vulkan :: StructureTypePhysicalDeviceDepthStencilResolveProperties:                          { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceDepthStencilResolveProperties ) * > ( currentInChain ), & deviceDepthStencilResolveProperties );                         break; }
            case engine :: vulkan :: StructureTypePhysicalDeviceDescriptorIndexingProperties:                           { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceDescriptorIndexingProperties ) * > ( currentInChain ), & deviceDescriptorIndexingProperties );                           break; }
            case engine :: vulkan :: StructureTypePhysicalDeviceFloatControlsProperties:                                { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceFloatControlsProperties ) * > ( currentInChain ), & deviceFloatControlsProperties );                                     break; }
            case engine :: vulkan :: StructureTypePhysicalDeviceSamplerFilterMinMaxProperties:                          { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceSamplerFilterMinmaxProperties ) * > ( currentInChain ), & deviceSamplerFilterMinmaxProperties );                         break; }
            case engine :: vulkan :: StructureTypePhysicalDeviceTimelineSemaphoreProperties:                            { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceTimelineSemaphoreProperties ) * > ( currentInChain ), & deviceTimelineSemaphoreProperties );                             break; }

#endif
#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceBlendOperationAdvancedProperties:                       { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceBlendOperationAdvancedProperties ) * > ( currentInChain ), & deviceBlendOperationAdvancedProperties );                   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONSERVATIVE_RASTERIZATION_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceConservativeRasterizationProperties:                    { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceConservativeRasterizationProperties ) * > ( currentInChain ), & deviceConservativeRasterizationProperties );             break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceCustomBorderColorProperties:                            { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceCustomBorderColorProperties ) * > ( currentInChain ), & deviceCustomBorderColorProperties );                             break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISCARD_RECTANGLES_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceDiscardRectangleProperties:                             { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceDiscardRectangleProperties ) * > ( currentInChain ), & deviceDiscardRectangleProperties );                               break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTERNAL_MEMORY_HOST_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceExternalMemoryHostProperties:                           { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceExternalMemoryHostProperties ) * > ( currentInChain ), & deviceExternalMemoryHostProperties );                           break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceFragmentDensityMapProperties:                           { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMapProperties ) * > ( currentInChain ), & deviceFragmentDensityMapProperties );                           break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceFragmentDensityMap2Properties:                          { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMap2Properties ) * > ( currentInChain ), & deviceFragmentDensityMap2Properties );                         break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceInlineUniformBlockProperties:                           { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceInlineUniformBlockProperties ) * > ( currentInChain ), & deviceInlineUniformBlockProperties );                           break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceLineRasterizationProperties:                            { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceLineRasterizationProperties ) * > ( currentInChain ), & deviceLineRasterizationProperties );                             break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceMultiDrawProperties:                                    { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceMultiDrawProperties ) * > ( currentInChain ), & deviceMultiDrawProperties );                                             break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PCI_BUS_INFO_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDevicePCIBusInfoProperties:                                   { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDevicePCIBusInfoProperties ) * > ( currentInChain ), & devicePciBusInfoProperties );                                           break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PHYSICAL_DEVICE_DRM_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceDRMProperties:                                          { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceDRMProperties ) * > ( currentInChain ), & deviceDrmProperties );                                                         break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceProvokingVertexProperties:                              { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceProvokingVertexProperties ) * > ( currentInChain ), & deviceProvokingVertexProperties );                                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceRobustnessProperties:                                   { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceRobustnessProperties ) * > ( currentInChain ), & deviceRobustness2Properties );                                          break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceSampleLocationsProperties:                              { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceSampleLocationsProperties ) * > ( currentInChain ), & deviceSampleLocationsProperties );                                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceSubgroupSizeControlProperties:                          { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceSubgroupSizeControlProperties ) * > ( currentInChain ), & deviceSubgroupSizeControlProperties );                         break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceTexelBufferAlignmentProperties:                         { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceTexelBufferAlignmentProperties ) * > ( currentInChain ), & deviceTexelBufferAlignmentProperties );                       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceTransformFeedbackProperties:                            { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceTransformFeedbackProperties ) * > ( currentInChain ), & deviceTransformFeedbackProperties );                             break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceVertexAttributeDivisorProperties:                       { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceVertexAttributeDivisorProperties ) * > ( currentInChain ), & deviceVertexAttributeDivisorProperties );                   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceAccelerationStructureProperties:                        { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceAccelerationStructureProperties ) * > ( currentInChain ), & deviceAccelerationStructureProperties );                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceFragmentShadingRateProperties:                          { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceFragmentShadingRateProperties ) * > ( currentInChain ), & deviceFragmentShadingRateProperties );                         break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceMaintenance4Properties:                                 { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceMaintenance4Properties ) * > ( currentInChain ), & deviceMaintenance4Properties );                                       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDevicePerformanceQueryProperties:                             { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDevicePerformanceQueryProperties ) * > ( currentInChain ), & devicePerformanceQueryProperties );                               break; }

#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDevicePortabilitySubsetProperties:                            { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDevicePortabilitySubsetProperties ) * > ( currentInChain ), & devicePortabilitySubsetProperties );                             break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PUSH_DESCRIPTOR_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDevicePushDescriptorProperties:                               { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDevicePushDescriptorProperties ) * > ( currentInChain ), & devicePushDescriptorProperties );                                   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceRayTracingPipelineProperties:                           { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceRayTracingPipelineProperties ) * > ( currentInChain ), & deviceRayTracingPipelineProperties );                           break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceShaderIntegerDotProductProperties:                      { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderIntegerDotProductProperties ) * > ( currentInChain ), & deviceShaderIntegerDotProductProperties );                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceCooperativeMatrixPropertiesNVidia:                      { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceCooperativeMatrixPropertiesNVidia ) * > ( currentInChain ), & deviceCooperativeMatrixProperties );                       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceDeviceGeneratedCommandsPropertiesNVidia:                { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceDeviceGeneratedCommandsPropertiesNVidia ) * > ( currentInChain ), & deviceDeviceGeneratedCommandsProperties );                       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceFragmentShadingRateEnumsPropertiesNVidia:               { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceFragmentShadingRateEnumsPropertiesNVidia ) * > ( currentInChain ), & deviceFragmentShadingRateEnumsProperties );                       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceMeshShaderPropertiesNVidia:                             { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceMeshShaderPropertiesNVidia ) * > ( currentInChain ), & deviceMeshShaderProperties );                                                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceRayTracingPropertiesNVidia:                             { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceRayTracingPropertiesNVidia ) * > ( currentInChain ), & deviceRayTracingProperties );                                                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceShaderSmBuiltinsPropertiesNVidia:                       { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderSMBuiltinsPropertiesNVidia ) * > ( currentInChain ), & deviceShaderSmBuiltinsProperties );                                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceShadingRateImagePropertiesNVidia:                       { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceShadingRateImagePropertiesNVidia ) * > ( currentInChain ), & deviceShadingRateImageProperties );                                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceMultiviewPerViewAttributesPropertiesNVidiaExperimental: { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceMultiviewPerViewAttributesPropertiesNVidia ) * > ( currentInChain ), & deviceMultiviewPerViewAttributesProperties );                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceShaderCorePropertiesAMD:                                { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderCorePropertiesAMD ) * > ( currentInChain ), & deviceShaderCoreProperties );                                                    break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_2_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceShaderCoreProperties2AMD:                               { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderCoreProperties2AMD ) * > ( currentInChain ), & deviceShaderCoreProperties2 );                                                  break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceFragmentDensityMapOffsetPropertiesQualcomm:             { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMapOffsetPropertiesQualcomm ) * > ( currentInChain ), & deviceFragmentDensityMapOffsetProperties );                   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceSubpassShadingPropertiesHuawei:                         { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceSubpassShadingPropertiesHuawei ) * > ( currentInChain ), & deviceSubpassShadingProperties );                                         break; }

#endif

            default: {
                break;
            }

        }

        currentInChain = currentInChain->pNext;
    }
}

auto vulkan :: getPhysicalDeviceProperties (
        __C_ENG_TYPE ( PhysicalDeviceHandle )               handle,
        __C_ENG_TYPE ( PhysicalDeviceExtendedProperties ) * pProperties
) noexcept -> __C_ENG_TYPE ( Result ) {

    if ( handle == nullptr || pProperties == nullptr ) {
        return ResultErrorIllegalArgument;
    }

    vkGetPhysicalDeviceProperties (
            handle,
            & deviceProperties
    );

    auto version = vulkan :: uInt32ToInstanceVersion ( deviceProperties.apiVersion );
    if ( vulkan :: compare ( version, versionConstants :: version11 ) == CompareResultLess ) {
        return ResultErrorIncompatibleVersion;
    }

    toVulkanFormat ( pProperties );

    vkGetPhysicalDeviceProperties2 (
        handle,
        & deviceExtendedProperties
    );

    fromVulkanFormat ( pProperties );

    return ResultSuccess;
}

static auto createChain (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceDetails )            * details,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceExtendedProperties ) * extendedProperties
) noexcept -> void {

    if ( details == nullptr || extendedProperties == nullptr ) {
        return;
    }

    auto currentInChain = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( extendedProperties );
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceProperties;

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->vulkan11Properties ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceVulkan_1_1_Properties;

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->IDProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceIDProperties;

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->maintenanceProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceMaintenanceProperties;

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->multiviewProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceMultiviewProperties;

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->pointClippingProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDevicePointClippingProperties;

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->protectedMemoryProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceProtectedMemoryProperties;

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->subgroupProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceSubgroupProperties;

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->vulkan12Properties ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceVulkan_1_2_Properties;

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->driverProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceDriverProperties;

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->depthStencilResolveProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceDepthStencilResolveProperties;

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->descriptorIndexingProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceDescriptorIndexingProperties;

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->deviceFloatControlsProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceFloatControlsProperties;

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->samplerFilterMinmaxProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceSamplerFilterMinMaxProperties;

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->timelineSemaphoreProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceTimelineSemaphoreProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PCI_BUS_INFO_AVAILABLE

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->pciBusInfoProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDevicePCIBusInfoProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PHYSICAL_DEVICE_DRM_AVAILABLE

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->DRMProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceDRMProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->accelerationStructureProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceAccelerationStructureProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->blendOperationAdvancedProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceBlendOperationAdvancedProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONSERVATIVE_RASTERIZATION_AVAILABLE

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->conservativeRasterizationProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceConservativeRasterizationProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->cooperativeMatrixPropertiesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceCooperativeMatrixPropertiesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->customBorderColorProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceCustomBorderColorProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->deviceGeneratedCommandsProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceDeviceGeneratedCommandsPropertiesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISCARD_RECTANGLES_AVAILABLE

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->externalMemoryHostProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceExternalMemoryHostProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->fragmentDensityMap2Properties ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceFragmentDensityMap2Properties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->fragmentDensityMapOffsetPropertiesQualcomm ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceFragmentDensityMapOffsetPropertiesQualcomm;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->fragmentDensityMapProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceFragmentDensityMapProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->fragmentShadingRateEnumsPropertiesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceFragmentShadingRateEnumsPropertiesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->fragmentShadingRateProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceFragmentShadingRateProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->inlineUniformBlockProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceInlineUniformBlockProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->lineRasterizationProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceLineRasterizationProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->maintenance4Properties ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceMaintenance4Properties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->meshShaderPropertiesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceMeshShaderPropertiesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->multiDrawProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceMultiDrawProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->multiviewPerViewAttributesPropertiesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceMultiviewPerViewAttributesPropertiesNVidiaExperimental;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->performanceQueryProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDevicePerformanceQueryProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->portabilitySubsetProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDevicePortabilitySubsetProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->provokingVertexProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceProvokingVertexProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PUSH_DESCRIPTOR_AVAILABLE

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->pushDescriptorProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDevicePushDescriptorProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->rayTracingPipelineProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceRayTracingPipelineProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->robustnessProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceRobustnessProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->sampleLocationsProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceSampleLocationsProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_AVAILABLE

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->shaderCorePropertiesAMD ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceShaderCorePropertiesAMD;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_2_AVAILABLE

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->shaderCoreProperties2AMD ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceShaderCoreProperties2AMD;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->shaderSmBuiltinsPropertiesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceShaderSmBuiltinsPropertiesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->shadingRateImagePropertiesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceShadingRateImagePropertiesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->subgroupSizeControlProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceSubgroupSizeControlProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->subpassShadingPropertiesHuawei ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceSubpassShadingPropertiesHuawei;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->texelBufferAlignmentProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceTexelBufferAlignmentProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->transformFeedbackProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceTransformFeedbackProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->vertexAttributeDivisorProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceVertexAttributeDivisorProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->rayTracingPropertiesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceRayTracingPropertiesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE

    currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->shaderIntegerDotProductProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
    currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceShaderIntegerDotProductProperties;

#endif

    currentInChain->pNext = nullptr;

}

auto vulkan :: getPhysicalDeviceDetails (
        __C_ENG_TYPE ( PhysicalDeviceHandle )       handle,
        __C_ENG_TYPE ( PhysicalDeviceDetails )    * properties
) noexcept -> __C_ENG_TYPE ( Result ) {

    if ( handle == nullptr || properties == nullptr ) {
        return ResultErrorIllegalArgument;
    }

    __C_ENG_TYPE ( PhysicalDeviceExtendedProperties ) extendedProperties { };

    createChain ( properties, & extendedProperties );

    auto lResult = getPhysicalDeviceProperties ( handle, & extendedProperties );
    if ( lResult != ResultSuccess ) {
        return lResult;
    }

    auto currentInChain = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure * ) > ( & extendedProperties );
    while ( currentInChain->pNext != nullptr ) {
        auto current = currentInChain;
        currentInChain = currentInChain->pNext;
        current->pNext = nullptr;
    }

    (void) std :: memcpy ( & properties->basicProperties, & extendedProperties.properties, sizeof ( __C_ENG_TYPE ( PhysicalDeviceProperties ) ) );

    return ResultSuccess;
}

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( QueueFamilyProperties ) * pDest,
        VkQueueFamilyProperties                    const * pSrc
) noexcept -> void {

    if (pDest == nullptr || pSrc == nullptr ) {
        return;
    }

    pDest->queueFlags                     = pSrc->queueFlags;
    pDest->queueCount                     = pSrc->queueCount;
    pDest->timestampValidBits             = pSrc->timestampValidBits;
    pDest->minImageTransferGranularity    = pSrc->minImageTransferGranularity;
}

__C_ENG_MAYBE_UNUSED auto vulkan :: getPhysicalDeviceQueueFamilyProperties (
        __C_ENG_TYPE ( PhysicalDeviceHandle )       handle,
        cds :: uint32                             * pQueueFamilyPropertyCount,
        __C_ENG_TYPE ( QueueFamilyProperties )    * pQueueFamilyProperties
) noexcept -> __C_ENG_TYPE ( Result ) {

    if ( handle == nullptr || pQueueFamilyPropertyCount == nullptr ) {
        return ResultErrorIllegalArgument;
    }

    if ( pQueueFamilyProperties == nullptr ) {
        vkGetPhysicalDeviceQueueFamilyProperties (
                handle,
                pQueueFamilyPropertyCount,
                nullptr
        );

        return ResultSuccess;
    }

    if ( * pQueueFamilyPropertyCount > __C_ENG_VULKAN_CORE_QUEUE_FAMILY_MAX_COUNT ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

    vkGetPhysicalDeviceQueueFamilyProperties (
            handle,
            pQueueFamilyPropertyCount,
            & queueFamilyProperties[0]
    );

    for ( uint32 i = 0U; i < * pQueueFamilyPropertyCount; ++ i ) {
        fromVulkanFormat ( & pQueueFamilyProperties[i], & queueFamilyProperties[i] );
    }

    return ResultSuccess;
}

static inline auto toVulkanFormat (
        uint32                                                              queueFamilyCount,
        vulkan :: __C_ENG_TYPE ( QueueFamilyExtendedProperties )    const * pExtendedProperties
) noexcept -> void {

    if ( pExtendedProperties == nullptr ) {
        return;
    }

    for ( uint32 i = 0U; i < queueFamilyCount; ++ i ) {
        queueFamilyExtendedProperties[i].sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2;

        auto currentInChain     = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericInStructure ) const * > ( pExtendedProperties->pNext );
        auto currentInVkChain   = reinterpret_cast < VkBaseOutStructure * > ( & queueFamilyExtendedProperties[i] );

        while ( currentInChain != nullptr ) {
            switch ( currentInChain->structureType ) {

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTIC_CHECKPOINTS_AVAILABLE

                case engine :: vulkan :: StructureTypeQueueFamilyCheckpointPropertiesNVidia:    { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & queueFamilyCheckpointProperties[i] );         break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE

                case engine :: vulkan :: StructureTypeQueueFamilyGlobalPriorityProperties:      { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & queueFamilyGlobalPriorityProperties[i] );     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE

                case engine :: vulkan :: StructureTypeQueueFamilyQueryResultStatusProperties:   { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & queueFamilyQueryResultStatusProperties[i] );  break; }
                case engine :: vulkan :: StructureTypeVideoQueueFamilyProperties:               { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & videoQueueFamilyProperties[i] );              break; }

#endif

                default:                                                                        { currentInVkChain->pNext = nullptr;                                                                                    break; }

            }

            if ( currentInVkChain->pNext != nullptr ) {
                currentInVkChain->pNext->sType  = static_cast < VkStructureType > ( currentInChain->structureType );
                currentInVkChain                = currentInVkChain->pNext;
            }

            currentInChain                  = currentInChain->pNext;
        }
    }
}

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTIC_CHECKPOINTS_AVAILABLE

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( QueueFamilyCheckpointPropertiesNVidia )          * pDestination,
        VkQueueFamilyCheckpointPropertiesNV                                 const * pSource
) noexcept -> void {

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

    pDestination->checkpointExecutionStageMask  = pSource->checkpointExecutionStageMask;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( QueueFamilyGlobalPriorityProperties )        * pDestination,
        VkQueueFamilyGlobalPriorityPropertiesEXT                        const * pSource
) noexcept -> void {

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

    pDestination->priorityCount = pSource->priorityCount;

    for ( uint32 i = 0U; i < pDestination->priorityCount; ++ i ) {
        pDestination->priorities[i] = static_cast < vulkan :: __C_ENG_TYPE ( QueueGlobalPriority ) > ( pSource->priorities[i] ) ;
    }
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( QueueFamilyQueryResultStatusProperties )          * pDestination,
        VkQueueFamilyQueryResultStatusPropertiesKHR                          const * pSource
) noexcept -> void {

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

    pDestination->supported = pSource->supported;
}

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( VideoQueueFamilyProperties )          * pDestination,
        VkVideoQueueFamilyPropertiesKHR                          const * pSource
) noexcept -> void {

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

    pDestination->videoCodecOperations = pSource->videoCodecOperations;
}

#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( QueueFamilyExtendedProperties )          * pDestination,
        VkQueueFamilyProperties2                                    const * pSource
) noexcept -> void {

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

    fromVulkanFormat ( & pDestination->properties, & pSource->queueFamilyProperties );
}

#endif

static inline auto fromVulkanFormat (
        uint32                                                              queueFamilyCount,
        vulkan :: __C_ENG_TYPE ( QueueFamilyExtendedProperties )          * pDestination
) noexcept -> void {

    if ( pDestination == nullptr ) {
        return;
    }

    if ( pDestination->structureType != vulkan :: StructureTypeQueueFamilyProperties ) {
        return;
    }

    for ( uint32 i = 0U; i < queueFamilyCount; ++ i ) {
        auto currentInChain = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & pDestination[i] );

        while ( currentInChain != nullptr ) {
            switch ( currentInChain->structureType ) {

                case engine :: vulkan :: StructureTypeQueueFamilyProperties:                    { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( QueueFamilyExtendedProperties ) * > ( currentInChain ), & queueFamilyExtendedProperties[i] );                      break; }

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTIC_CHECKPOINTS_AVAILABLE

                case engine :: vulkan :: StructureTypeQueueFamilyCheckpointPropertiesNVidia:    { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( QueueFamilyCheckpointPropertiesNVidia ) * > ( currentInChain ), & queueFamilyCheckpointProperties[i] );            break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE

                case engine :: vulkan :: StructureTypeQueueFamilyGlobalPriorityProperties:      { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( QueueFamilyGlobalPriorityProperties ) * > ( currentInChain ), & queueFamilyGlobalPriorityProperties[i] );          break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE

                case engine :: vulkan :: StructureTypeQueueFamilyQueryResultStatusProperties:   { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( QueueFamilyQueryResultStatusProperties ) * > ( currentInChain ), & queueFamilyQueryResultStatusProperties[i] );    break; }
                case engine :: vulkan :: StructureTypeVideoQueueFamilyProperties:               { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( VideoQueueFamilyProperties ) * > ( currentInChain ), & videoQueueFamilyProperties[i] );                            break; }

#endif

                default: {
                    break;
                }

            }

            currentInChain = currentInChain->pNext;
        }
    }
}

auto vulkan :: getPhysicalDeviceQueueFamilyProperties (
        __C_ENG_TYPE ( PhysicalDeviceHandle )               handle,
        uint32                                            * pQueueFamilyPropertyCount,
        __C_ENG_TYPE ( QueueFamilyExtendedProperties )    * pQueueFamilyProperties
) noexcept -> __C_ENG_TYPE ( Result ) {

    if ( handle == nullptr || pQueueFamilyPropertyCount == nullptr ) {
        return ResultErrorIllegalArgument;
    }

    if ( pQueueFamilyProperties == nullptr ) {
        vkGetPhysicalDeviceQueueFamilyProperties2 (
                handle,
                pQueueFamilyPropertyCount,
                nullptr
        );

        return ResultSuccess;
    }

    vkGetPhysicalDeviceProperties (
            handle,
            & deviceProperties
    );

    auto version = vulkan :: uInt32ToInstanceVersion ( deviceProperties.apiVersion );
    if ( vulkan :: compare ( version, versionConstants :: version11 ) == CompareResultLess ) {
        return ResultErrorIncompatibleVersion;
    }

    if ( * pQueueFamilyPropertyCount > __C_ENG_VULKAN_CORE_QUEUE_FAMILY_MAX_COUNT ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

    toVulkanFormat ( * pQueueFamilyPropertyCount, pQueueFamilyProperties );

    vkGetPhysicalDeviceQueueFamilyProperties2 (
            handle,
            pQueueFamilyPropertyCount,
            & queueFamilyExtendedProperties[0]
    );

    fromVulkanFormat ( * pQueueFamilyPropertyCount, pQueueFamilyProperties );

    return ResultSuccess;
}

static inline auto createChain (
        uint32                                                      queueFamilyCount,
        vulkan :: __C_ENG_TYPE ( QueueFamilyDetails )             * pDetails,
        vulkan :: __C_ENG_TYPE ( QueueFamilyExtendedProperties )  * pExtendedProperties
) noexcept -> void {

    if ( pDetails == nullptr || pExtendedProperties == nullptr ) {
        return;
    }

    for ( uint32 i = 0U; i < queueFamilyCount; ++ i ) {

        auto currentInChain = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & pExtendedProperties[i] );
        currentInChain->structureType = vulkan :: StructureTypeQueueFamilyProperties;

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTIC_CHECKPOINTS_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & pDetails[i].checkpointPropertiesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypeQueueFamilyCheckpointPropertiesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & pDetails[i].globalPriorityProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypeQueueFamilyGlobalPriorityProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & pDetails[i].queryResultStatusProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypeQueueFamilyQueryResultStatusProperties;

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & pDetails[i].videoProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypeVideoQueueFamilyProperties;

#endif

        currentInChain->pNext = nullptr;

    }
}

auto vulkan :: getPhysicalDeviceQueueFamilyDetails (
        __C_ENG_TYPE ( PhysicalDeviceHandle )   handle,
        uint32                                * pQueueFamilyCount,
        __C_ENG_TYPE ( QueueFamilyDetails )   * pQueueFamilyDetails
) noexcept -> __C_ENG_TYPE ( Result ) {

    if ( handle == nullptr || pQueueFamilyCount == nullptr ) {
        return ResultErrorIllegalArgument;
    }

    if ( pQueueFamilyDetails == nullptr ) {
        vkGetPhysicalDeviceQueueFamilyProperties2 (
                handle,
                pQueueFamilyCount,
                nullptr
        );

        return ResultSuccess;
    }

    if ( * pQueueFamilyCount > __C_ENG_VULKAN_CORE_QUEUE_FAMILY_MAX_COUNT ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

    __C_ENG_TYPE ( QueueFamilyExtendedProperties ) extendedProperties [ __C_ENG_VULKAN_CORE_QUEUE_FAMILY_MAX_COUNT ];

    createChain ( * pQueueFamilyCount, pQueueFamilyDetails, & extendedProperties[0] );

    auto lResult = vulkan :: getPhysicalDeviceQueueFamilyProperties (
            handle,
            pQueueFamilyCount,
            & extendedProperties[0]
    );

    if ( lResult != ResultSuccess ) {
        return lResult;
    }

    for ( uint32 i = 0U; i < * pQueueFamilyCount; ++ i ) {
        auto currentInChain = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & extendedProperties[i] );
        while ( currentInChain->pNext != nullptr ) {
            auto current = currentInChain;
            currentInChain = currentInChain->pNext;
            current->pNext = nullptr;
        }

        (void) std :: memcpy ( & pQueueFamilyDetails->properties, & extendedProperties[i].properties, sizeof ( __C_ENG_TYPE ( QueueFamilyProperties ) ) );
    }

    return ResultSuccess;
}

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

__C_ENG_MAYBE_UNUSED auto vulkan :: enumeratePhysicalDeviceQueueFamilyPerformanceQueryCounters (
        __C_ENG_TYPE ( InstanceHandle )                     instanceHandle,
        __C_ENG_TYPE ( PhysicalDeviceHandle )               physicalDeviceHandle,
        uint32                                              queueFamilyIndex,
        uint32                                            * pCounterCount,
        __C_ENG_TYPE ( PerformanceCounter )               * pCounters,
        __C_ENG_TYPE ( PerformanceCounterDescription )    * pCounterDescriptions
) noexcept -> __C_ENG_TYPE ( Result ) {

    if ( instanceHandle == nullptr || physicalDeviceHandle == nullptr || pCounterCount == nullptr ) {
        return ResultErrorIllegalArgument;
    }

    if ( pVkInstanceProcessEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCounters == nullptr ) {

        auto lResult = vulkan ::getInstanceFunctionAddress (
                instanceHandle,
                __C_ENG_VULKAN_CORE_FUNCTION_NAME_ENUMERATE_PHYSICAL_DEVICE_QUEUE_FAMILY_PERFORMANCE_QUERY_COUNTERS,
                reinterpret_cast < void ** > ( & pVkInstanceProcessEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCounters )
        );

        if ( lResult != ResultSuccess ) {
            return lResult;
        }
    }

    if ( pCounters == nullptr && pCounterDescriptions == nullptr ) {

        return static_cast < __C_ENG_TYPE ( Result ) > (
                pVkInstanceProcessEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCounters (
                        physicalDeviceHandle,
                        queueFamilyIndex,
                        pCounterCount,
                        nullptr,
                        nullptr
                )
        );
    }

    if ( * pCounterCount > __C_ENG_VULKAN_CORE_QUEUE_FAMILY_PERFORMANCE_COUNTER_MAX_COUNT ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

    result = pVkInstanceProcessEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCounters (
            physicalDeviceHandle,
            queueFamilyIndex,
            pCounterCount,
            & counters[0],
            & counterDescriptions[0]
    );

    if ( result != VkResult :: VK_SUCCESS ) {
        return static_cast < __C_ENG_TYPE ( Result ) > ( result );
    }

    for ( uint32 i = 0U; i < * pCounterCount; ++ i ) {

        pCounters[i].structureType  = StructureTypePerformanceCounter;
        pCounters[i].pNext          = nullptr;
        pCounters[i].unit           = static_cast < __C_ENG_TYPE ( PerformanceCounterUnit ) > ( counters[i].unit );
        pCounters[i].scope          = static_cast < __C_ENG_TYPE ( PerformanceCounterScope ) > ( counters[i].scope );
        pCounters[i].storage        = static_cast < __C_ENG_TYPE ( PerformanceCounterStorage ) > ( counters[i].storage );
        (void) std :: memcpy ( & pCounters[i].uuid[0], & counters[i].uuid[0], sizeof ( counters[i].uuid[0] ) * VK_UUID_SIZE );

        pCounterDescriptions[i].structureType   = StructureTypePerformanceCounterDescription;
        pCounterDescriptions[i].pNext           = nullptr;
        pCounterDescriptions[i].flags           = static_cast < __C_ENG_TYPE ( PerformanceCounterDescriptionFlags ) > ( counterDescriptions[i].flags );
        (void) std :: memcpy ( & pCounterDescriptions[i].name[0], & counterDescriptions[i].name[0], sizeof ( counterDescriptions[i].name[0] ) * VK_MAX_DESCRIPTION_SIZE );
        (void) std :: memcpy ( & pCounterDescriptions[i].category[0], & counterDescriptions[i].category[0], sizeof ( counterDescriptions[i].category[0] ) * VK_MAX_DESCRIPTION_SIZE );
        (void) std :: memcpy ( & pCounterDescriptions[i].description[0], & counterDescriptions[i].description[0], sizeof ( counterDescriptions[i].description[0] ) * VK_MAX_DESCRIPTION_SIZE );

    }

    return ResultSuccess;
}

#endif

__C_ENG_MAYBE_UNUSED auto vulkan :: getFunctionAddress (
        StringLiteral   functionName,
        void         ** ppFunction
) noexcept -> __C_ENG_TYPE ( Result ) {

    if ( ppFunction == nullptr ) {
        return ResultErrorIllegalArgument;
    }

    * ppFunction = reinterpret_cast < void * > ( vkGetInstanceProcAddr ( nullptr, functionName ) );

    if ( * ppFunction == nullptr ) {
        return ResultErrorFunctionHandleNotFound;
    }

    return ResultSuccess;
}

auto vulkan :: getInstanceFunctionAddress (
        __C_ENG_TYPE ( InstanceHandle ) instanceHandle,
        StringLiteral                   functionName,
        void                         ** ppFunction
) noexcept -> __C_ENG_TYPE ( Result ) {

    if ( ppFunction == nullptr ) {
        return ResultErrorIllegalArgument;
    }

    * ppFunction = reinterpret_cast < void * > ( vkGetInstanceProcAddr ( instanceHandle, functionName ) );

    if ( * ppFunction == nullptr ) {
        return ResultErrorFunctionHandleNotFound;
    }

    return ResultSuccess;
}

auto vulkan :: getDeviceFunctionAddress (
        __C_ENG_TYPE ( DeviceHandle )   deviceHandle,
        StringLiteral                   functionName,
        void                         ** ppFunction
) noexcept -> __C_ENG_TYPE ( Result ) {

    if ( ppFunction == nullptr ) {
        return ResultErrorIllegalArgument;
    }

    * ppFunction = reinterpret_cast < void * > ( vkGetDeviceProcAddr ( deviceHandle, functionName ) );

    if ( * ppFunction == nullptr ) {
        return ResultErrorFunctionHandleNotFound;
    }

    return ResultSuccess;
}

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceGroupProperties )          * pDestination,
        VkPhysicalDeviceGroupProperties                             const * pSource
) noexcept -> void {

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

    pDestination->structureType         = vulkan :: StructureTypePhysicalDeviceGroupProperties;
    pDestination->pNext                 = nullptr;
    pDestination->physicalDeviceCount   = pSource->physicalDeviceCount;
    pDestination->subsetAllocation      = pSource->subsetAllocation;

    (void) std :: memcpy ( & pDestination->physicalDevices[0], & pSource->physicalDevices[0], sizeof ( pSource->physicalDevices[0] ) * VK_MAX_DEVICE_GROUP_SIZE ); // NOLINT(bugprone-sizeof-expression)
}

__C_ENG_NO_DISCARD __C_ENG_MAYBE_UNUSED auto vulkan :: enumeratePhysicalDeviceGroups (
        __C_ENG_TYPE ( InstanceHandle )                   instanceHandle,
        cds :: uint32                                   * pPhysicalDeviceGroupCount,
        __C_ENG_TYPE ( PhysicalDeviceGroupProperties )  * pPhysicalDeviceGroupProperties
) noexcept -> __C_ENG_TYPE ( Result ) {

    if ( instanceHandle == nullptr || pPhysicalDeviceGroupCount == nullptr ) {
        return ResultErrorIllegalArgument;
    }

    if ( pPhysicalDeviceGroupProperties == nullptr ) {
        return static_cast < __C_ENG_TYPE ( Result ) > (
                vkEnumeratePhysicalDeviceGroups (
                        instanceHandle,
                        pPhysicalDeviceGroupCount,
                        nullptr
                )
        );
    }

    if ( * pPhysicalDeviceGroupCount > __C_ENG_VULKAN_CORE_PHYSICAL_DEVICE_GROUP_MAX_COUNT ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

    result = vkEnumeratePhysicalDeviceGroups (
            instanceHandle,
            pPhysicalDeviceGroupCount,
            & physicalDeviceGroupProperties[0]
    );

    if ( result != VK_SUCCESS ) {
        return static_cast < __C_ENG_TYPE ( Result ) > ( result );
    }

    for ( uint32 i = 0U; i < * pPhysicalDeviceGroupCount; ++ i ) {
        fromVulkanFormat ( & pPhysicalDeviceGroupProperties[i], & physicalDeviceGroupProperties[0] );
    }

    return ResultSuccess;
}

#endif

auto toVulkanFormat (
        VkDeviceCreateInfo                                  * pDestination,
        vulkan :: __C_ENG_TYPE ( DeviceCreateInfo ) const   * pSource
) noexcept -> void {

}

auto vulkan :: createDevice (
        __C_ENG_TYPE ( PhysicalDeviceHandle )           physicalDeviceHandle,
        __C_ENG_TYPE ( DeviceCreateInfo )       const * pDeviceCreateInfo,
        __C_ENG_TYPE ( AllocationCallbacks )    const * pAllocationCallbacks,
        __C_ENG_TYPE ( DeviceHandle )                 * pDeviceHandle
) noexcept -> __C_ENG_TYPE ( Result ) {

    if (
            physicalDeviceHandle    == nullptr ||
            pDeviceCreateInfo       == nullptr ||
            pDeviceHandle           == nullptr
    ) {
        return ResultErrorIllegalArgument;
    }

    if ( ! validate ( pDeviceCreateInfo ) ) {
        return ResultErrorInvalidUsage;
    }

    VkAllocationCallbacks * pUsedAllocationCallback = nullptr;

    if ( pAllocationCallbacks != nullptr ) {
        pUsedAllocationCallback = & allocationCallbacks;
        toVulkanFormat ( pAllocationCallbacks, pUsedAllocationCallback );
    }

    toVulkanFormat ( & deviceCreateInfo, pDeviceCreateInfo );

    return static_cast < __C_ENG_TYPE ( Result ) > (
            vkCreateDevice (
                    physicalDeviceHandle,
                    & deviceCreateInfo,
                    pUsedAllocationCallback,
                    pDeviceHandle
            )
    );
}
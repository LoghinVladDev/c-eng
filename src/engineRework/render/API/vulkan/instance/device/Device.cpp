//
// Created by loghin on 30.01.2022.
//

#include "Device.hpp"
#include <VulkanAPIExceptions.hpp>
#include <PhysicalDevice.hpp>
#include <VulkanAPI.hpp>
#include <Allocator.hpp>
#include <Logger.hpp>
#include <CDS/Mutex>
#include <CDS/LockGuard>
#include <CDS/HashMap>


using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace vulkan; // NOLINT(clion-misra-cpp2008-7-3-4)


struct StructureWithSize {
    __C_ENG_TYPE ( GenericOutStructure )  * pStructure;
    uint32                                  size;
};


namespace globals {
static __C_ENG_TYPE ( PhysicalDeviceExtendedFeatures ) extendedFeatures {
    .structureType  = StructureTypePhysicalDeviceFeatures
};


static __C_ENG_TYPE ( PhysicalDeviceFeatures ) basicFeatures;

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceVulkan11Features ) vulkan11Features {
    .structureType  = StructureTypePhysicalDeviceVulkan_1_1_Features
};

static __C_ENG_TYPE ( PhysicalDevice16BitStorageFeatures ) _16BitStorageFeatures {  // NOLINT(bugprone-reserved-identifier)
    .structureType  = StructureTypePhysicalDevice16BitStorageFeatures
};

static __C_ENG_TYPE ( PhysicalDeviceMultiviewFeatures ) multiviewFeatures {
    .structureType  = StructureTypePhysicalDeviceMultiviewFeatures
};

static __C_ENG_TYPE ( PhysicalDeviceProtectedMemoryFeatures ) protectedMemoryFeatures {
    .structureType  = StructureTypePhysicalDeviceProtectedMemoryFeatures
};

static __C_ENG_TYPE ( PhysicalDeviceSamplerYCBCRConversionFeatures ) samplerYCBCRConversionFeatures {
    .structureType  = StructureTypePhysicalDeviceSamplerYCBCRConversionFeatures
};

static __C_ENG_TYPE ( PhysicalDeviceShaderDrawParametersFeatures ) shaderDrawParametersFeatures {
    .structureType  = StructureTypePhysicalDeviceShaderDrawParametersFeatures
};

static __C_ENG_TYPE ( PhysicalDeviceVariablePointersFeatures ) variablePointersFeatures {
    .structureType  = StructureTypePhysicalDeviceVariablePointersFeatures
};
#endif


#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceVulkan12Features ) vulkan12Features {
    .structureType  = engine::vulkan::StructureTypePhysicalDeviceVulkan_1_2_Features
};

static __C_ENG_TYPE ( PhysicalDevice8BitStorageFeatures ) _8BitStorageFeatures { // NOLINT(bugprone-reserved-identifier)
    .structureType  = StructureTypePhysicalDevice8BitStorageFeatures
};

static __C_ENG_TYPE ( PhysicalDeviceBufferDeviceAddressFeatures ) bufferDeviceAddressFeatures {
    .structureType  = StructureTypePhysicalDeviceBufferDeviceAddressFeatures
};

static __C_ENG_TYPE ( PhysicalDeviceDescriptorIndexingFeatures ) descriptorIndexingFeatures {
    .structureType  = StructureTypePhysicalDeviceDescriptorIndexingFeatures
};

static __C_ENG_TYPE ( PhysicalDeviceHostQueryResetFeatures ) hostQueryResetFeatures {
    .structureType  = StructureTypePhysicalDeviceHostQueryResetFeatures
};

static __C_ENG_TYPE ( PhysicalDeviceImagelessFrameBufferFeatures ) imagelessFramebufferFeatures {
    .structureType  = StructureTypePhysicalDeviceImagelessFrameBufferFeatures
};

static __C_ENG_TYPE ( PhysicalDeviceScalarBlockLayoutFeatures ) scalarBlockLayoutFeatures {
    .structureType  = StructureTypePhysicalDeviceScalarBlockLayoutFeatures
};

static __C_ENG_TYPE ( PhysicalDeviceSeparateDepthStencilLayoutsFeatures ) separateDepthStencilLayoutsFeatures {
    .structureType  = StructureTypePhysicalDeviceSeparateDepthStencilLayoutsFeatures
};

static __C_ENG_TYPE ( PhysicalDeviceShaderAtomicInt64Features ) shaderAtomicInt64Features {
    .structureType  = StructureTypePhysicalDeviceShaderAtomicInt64Features
};

static __C_ENG_TYPE ( PhysicalDeviceShaderFloat16Int8Features ) shaderFloat16Int8Features {
    .structureType  = StructureTypePhysicalDeviceShaderFloat16Int8Features
};

static __C_ENG_TYPE ( PhysicalDeviceShaderSubgroupExtendedTypesFeatures ) shaderSubgroupExtendedTypesFeatures {
    .structureType  = StructureTypePhysicalDeviceShaderSubgroupExtendedTypesFeatures
};

static __C_ENG_TYPE ( PhysicalDeviceTimelineSemaphoreFeatures ) timelineSemaphoreFeatures {
    .structureType  = StructureTypePhysicalDeviceTimelineSemaphoreFeatures
};

static __C_ENG_TYPE ( PhysicalDeviceUniformBufferStandardLayoutFeatures ) uniformBufferStandardLayoutFeatures {
    .structureType  = StructureTypePhysicalDeviceUniformBufferStandardLayoutFeatures
};

static __C_ENG_TYPE ( PhysicalDeviceVulkanMemoryModelFeatures ) vulkanMemoryModelFeatures {
    .structureType  = StructureTypePhysicalDeviceVulkanMemoryModelFeatures
};
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceVulkan13Features ) vulkan13Features {
    .structureType  = StructureTypePhysicalDeviceVulkan_1_3_Features
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_4444_FORMATS_AVAILABLE
static __C_ENG_TYPE ( PhysicalDevice4444FormatsFeatures ) _4444FormatsFeatures { // NOLINT(bugprone-reserved-identifier)
    .structureType  = StructureTypePhysicalDevice4444FormatsFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_ASTC_DECODE_MODE_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceASTCDecodeFeatures ) ASTCDecodeFeatures {
    .structureType  = StructureTypePhysicalDeviceASTCDecodeFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceAccelerationStructureFeatures ) accelerationStructureFeatures {
    .structureType  = StructureTypePhysicalDeviceAccelerationStructureFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceBlendOperationAdvancedFeatures ) blendOperationAdvancedFeatures {
    .structureType  = StructureTypePhysicalDeviceBlendOperationAdvancedFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_BORDER_COLOR_SWIZZLE_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceBorderColorSwizzleFeatures ) borderColorSwizzleFeatures {
    .structureType  = StructureTypePhysicalDeviceBorderColorSwizzleFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_DEVICE_COHERENT_MEMORY_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceCoherentMemoryFeaturesAMD ) coherentMemoryFeaturesAMD {
    .structureType  = StructureTypePhysicalDeviceCoherentMemoryFeaturesAMD
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_COLOR_WRITE_ENABLE_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceColorWriteEnableFeatures ) colorWriteEnabledFeatures {
    .structureType  = StructureTypePhysicalDeviceColorWriteEnableFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COMPUTE_SHADER_DERIVATIVES_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceComputeShaderDerivativesFeaturesNVidia ) computeShaderDerivativesFeaturesNVidia {
    .structureType  = StructureTypePhysicalDeviceComputeShaderDerivativesFeaturesNVidia
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceConditionalRenderingFeatures ) conditionalRenderingFeatures {
    .structureType  = StructureTypePhysicalDeviceConditionalRenderingFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceCooperativeMatrixFeaturesNVidia ) cooperativeMatrixFeaturesNVidia {
    .structureType  = StructureTypePhysicalDeviceCooperativeMatrixFeaturesNVidia
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CORNER_SAMPLED_IMAGE_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceCornerSampledImageFeaturesNVidia ) cornerSampledImageFeaturesNVidia {
    .structureType  = StructureTypePhysicalDeviceCornerSampledImageFeaturesNVidia
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COVERAGE_REDUCTION_MODE_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceCoverageReductionModeFeaturesNVidia ) coverageReductionModeFeaturesNVidia {
    .structureType  = StructureTypePhysicalDeviceCoverageReductionModeFeaturesNVidia
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceCustomBorderColorFeatures ) customBorderColorFeatures {
    .structureType  = StructureTypePhysicalDeviceCustomBorderColorFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_IMAGE_ALIASING_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNVidia ) dedicatedAllocationImageAliasingFeaturesNVidia {
    .structureType  = StructureTypePhysicalDeviceDedicatedAllocationImageAliasingFeaturesNVidia
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_CONTROL_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceDepthClipControlFeatures ) depthClipControlFeatures {
    .structureType  = StructureTypePhysicalDeviceDepthClipControlFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_ENABLE_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceDepthClipEnableFeatures ) depthClipEnableFeatures {
    .structureType  = StructureTypePhysicalDeviceDepthClipEnableFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceDeviceGeneratedCommandsFeaturesNVidia ) deviceGeneratedCommandsFeatures {
    .structureType  = StructureTypePhysicalDeviceDeviceGeneratedCommandsFeaturesNVidia
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEVICE_MEMORY_REPORT_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceDeviceMemoryReportFeatures ) deviceMemoryReportFeatures {
    .structureType  = StructureTypePhysicalDeviceDeviceMemoryReportFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTICS_CONFIG_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceDiagnosticsConfigFeaturesNVidia ) diagnosticsConfigFeaturesNVidia {
    .structureType  = StructureTypePhysicalDeviceDiagnosticsConfigFeaturesNVidia
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceDynamicRenderingFeatures ) dynamicRenderingFeatures {
    .structureType  = StructureTypePhysicalDeviceDynamicRenderingFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SCISSOR_EXCLUSIVE_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceExclusiveScissorFeaturesNVidia ) exclusiveScissorFeaturesNVidia {
    .structureType  = StructureTypePhysicalDeviceExclusiveScissorFeaturesNVidia
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceExtendedDynamicStateFeatures ) extendedDynamicStateFeatures {
    .structureType  = StructureTypePhysicalDeviceExtendedDynamicStateFeatures
};

static __C_ENG_TYPE ( PhysicalDeviceExtendedDynamicState2Features ) extendedDynamicState2Features {
    .structureType  = StructureTypePhysicalDeviceExtendedDynamicState2Features
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_RDMA_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceExternalMemoryRDMAFeaturesNVidia ) externalMemoryRDMAFeaturesNVidia {
    .structureType  = StructureTypePhysicalDeviceExternalMemoryRDMAFeaturesNVidia
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMapFeatures ) fragmentDensityMapFeatures {
    .structureType  = StructureTypePhysicalDeviceFragmentDensityMapFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMap2Features ) fragmentDensityMap2Features {
    .structureType  = StructureTypePhysicalDeviceFragmentDensityMap2Features
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMapOffsetFeaturesQualcomm ) fragmentDensityMapOffsetFeaturesQualcomm {
    .structureType  = StructureTypePhysicalDeviceFragmentDensityMapOffsetFeaturesQualcomm
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADER_BARYCENTRIC_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceFragmentShaderBarycentricFeaturesNVidia ) fragmentShaderBarycentricFeaturesNVidia {
    .structureType  = StructureTypePhysicalDeviceFragmentShaderBarycentricFeaturesNVidia
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_SHADER_INTERLOCK_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceFragmentShaderInterlockFeatures ) fragmentShaderInterlockFeatures {
    .structureType  = StructureTypePhysicalDeviceFragmentShaderInterlockFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceFragmentShadingRateEnumsFeaturesNVidia ) fragmentShadingRateEnumsFeaturesNVidia {
    .structureType  = StructureTypePhysicalDeviceFragmentShadingRateEnumsFeaturesNVidia
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceFragmentShadingRateFeatures ) fragmentShadingRateFeatures {
    .structureType  = StructureTypePhysicalDeviceFragmentShadingRateFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceGlobalPriorityQueryFeatures ) globalPriorityQueryFeatures {
    .structureType  = StructureTypePhysicalDeviceGlobalPriorityQueryFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_ROBUSTNESS_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceImageRobustnessFeatures ) imageRobustnessFeatures {
    .structureType  = StructureTypePhysicalDeviceImageRobustnessFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_VIEW_MIN_LOD_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceImageViewMinLODFeatures ) imageViewMinLODFeatures {
    .structureType  = StructureTypePhysicalDeviceImageViewMinLODFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INDEX_TYPE_UINT8_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceIndexTypeUInt8Features ) indexTypeUInt8Features {
    .structureType  = StructureTypePhysicalDeviceIndexTypeUInt8Features
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_INHERITED_VIEWPORT_SCISSOR_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceInheritedViewportScissorFeaturesNVidia ) inheritedViewportScissorFeaturesNVidia {
    .structureType  = StructureTypePhysicalDeviceInheritedViewportScissorFeaturesNVidia
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceInlineUniformBlockFeatures ) inlineUniformBlockFeatures {
    .structureType  = StructureTypePhysicalDeviceInlineUniformBlockFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_INVOCATION_MASK_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceInvocationMaskFeaturesHuawei ) invocationMaskFeaturesHuawei {
    .structureType  = StructureTypePhysicalDeviceInvocationMaskFeaturesHuawei
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceLineRasterizationFeatures ) lineRasterizationFeatures {
    .structureType  = StructureTypePhysicalDeviceLineRasterizationFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_LINEAR_COLOR_ATTACHMENT_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceLinearColorAttachmentFeaturesNVidia ) linearColorAttachmentFeaturesNVidia {
    .structureType  = StructureTypePhysicalDeviceLinearColorAttachmentFeaturesNVidia
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceMaintenance4Features ) maintenance4Features {
    .structureType  = StructureTypePhysicalDeviceMaintenance4Features
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_PRIORITY_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceMemoryPriorityFeatures ) memoryPriorityFeatures {
    .structureType  = StructureTypePhysicalDeviceMemoryPriorityFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceMeshShaderFeaturesNVidia ) meshShaderFeaturesNVidia {
    .structureType  = StructureTypePhysicalDeviceMeshShaderFeaturesNVidia
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceMultiDrawFeatures ) multiDrawFeatures {
    .structureType  = StructureTypePhysicalDeviceMultiDrawFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceMutableDescriptorTypeFeaturesValve ) mutableDescriptorTypeFeaturesValve {
    .structureType  = StructureTypePhysicalDeviceMutableDescriptorTypeFeaturesValve
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PAGEABLE_DEVICE_LOCAL_MEMORY_AVAILABLE
static __C_ENG_TYPE ( PhysicalDevicePageableDeviceLocalMemoryFeatures ) pageableDeviceLocalMemoryFeatures {
    .structureType  = StructureTypePhysicalDevicePageableDeviceLocalMemoryFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
static __C_ENG_TYPE ( PhysicalDevicePerformanceQueryFeatures ) performanceQueryFeatures {
    .structureType  = StructureTypePhysicalDevicePerformanceQueryFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
static __C_ENG_TYPE ( PhysicalDevicePipelineCreationCacheControlFeatures ) pipelineCreationCacheControlFeatures {
    .structureType  = StructureTypePhysicalDevicePipelineCreationCacheControlFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
static __C_ENG_TYPE ( PhysicalDevicePipelineExecutablePropertiesFeatures ) pipelineExecutablePropertiesFeatures {
    .structureType  = StructureTypePhysicalDevicePipelineExecutablePropertiesFeatures
};
#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE
static __C_ENG_TYPE ( PhysicalDevicePortabilitySubsetFeatures ) portabilitySubsetFeatures {
    .structureType  = StructureTypePhysicalDevicePortabilitySubsetFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_ID_AVAILABLE
static __C_ENG_TYPE ( PhysicalDevicePresentIDFeatures ) presentIDFeatures {
    .structureType  = StructureTypePhysicalDevicePresentIDFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_WAIT_AVAILABLE
static __C_ENG_TYPE ( PhysicalDevicePresentWaitFeatures ) presentWaitFeatures {
    .structureType  = StructureTypePhysicalDevicePresentWaitFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIMITIVE_TOPOLOGY_LIST_RESTART_AVAILABLE
static __C_ENG_TYPE ( PhysicalDevicePrimitiveTopologyListRestartFeatures ) primitiveTopologyListRestartFeatures {
    .structureType  = StructureTypePhysicalDevicePrimitiveTopologyListRestartFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
static __C_ENG_TYPE ( PhysicalDevicePrivateDataFeatures ) privateDataFeatures {
    .structureType  = StructureTypePhysicalDevicePrivateDataFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceProvokingVertexFeatures ) provokingVertexFeatures {
    .structureType  = StructureTypePhysicalDeviceProvokingVertexFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_RGBA_10_X_6_FORMATS_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceRGBA10x6FormatsFeatures ) RGBA10x6FormatsFeatures {
    .structureType  = StructureTypePhysicalDeviceRGBA10x6FormatsFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_ARM_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM ) rasterizationOrderAttachmentAccessFeaturesARM {
    .structureType  = StructureTypePhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_QUERY_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceRayQueryFeatures ) rayQueryFeatures {
    .structureType  = StructureTypePhysicalDeviceRayQueryFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceRayTracingMotionBlurFeaturesNVidia ) rayTracingMotionBlurFeaturesNVidia {
    .structureType  = StructureTypePhysicalDeviceRayTracingMotionBlurFeaturesNVidia
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceRayTracingPipelineFeatures ) rayTracingPipelineFeatures {
    .structureType  = StructureTypePhysicalDeviceRayTracingPipelineFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_REPRESENTATIVE_FRAGMENT_TEST_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceRepresentativeFragmentTestFeaturesNVidia ) representativeFragmentTestFeaturesNVidia {
    .structureType  = StructureTypePhysicalDeviceRepresentativeFragmentTestFeaturesNVidia
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceRobustnessFeatures ) robustnessFeatures {
    .structureType  = StructureTypePhysicalDeviceRobustnessFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceShaderAtomicFloatFeatures ) shaderAtomicFloatFeatures {
    .structureType  = StructureTypePhysicalDeviceShaderAtomicFloatFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_2_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceShaderAtomicFloat2Features ) shaderAtomicFloat2Features {
    .structureType  = StructureTypePhysicalDeviceShaderAtomicFloat2Features
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_CLOCK_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceShaderClockFeatures ) shaderClockFeatures {
    .structureType  = StructureTypePhysicalDeviceShaderClockFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_DEMOTE_TO_HELPER_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceShaderDemoteToHelperInvocationFeatures ) shaderDemoteToHelperInvocationFeatures {
    .structureType  = StructureTypePhysicalDeviceShaderDemoteToHelperInvocationFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_IMAGE_ATOMIC_INT64_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceShaderImageAtomicInt64Features ) shaderImageAtomicInt64Features {
    .structureType  = StructureTypePhysicalDeviceShaderImageAtomicInt64Features
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_IMAGE_FOOTPRINT_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceShaderImageFootprintFeaturesNVidia ) shaderImageFootprintFeaturesNVidia {
    .structureType  = StructureTypePhysicalDeviceShaderImageFootprintFeaturesNVidia
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceShaderSMBuiltinsFeaturesNVidia ) shaderSmBuiltinsFeaturesNVidia {
    .structureType  = StructureTypePhysicalDeviceShaderSmBuiltinsFeaturesNVidia
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_SUBGROUP_UNIFORM_CONTROL_FLOW_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceShaderSubgroupUniformControlFlowFeatures ) shaderSubgroupUniformControlFlowFeatures {
    .structureType  = StructureTypePhysicalDeviceShaderSubgroupUniformControlFlowFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_TERMINATE_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceShaderTerminateInvocationFeatures ) shaderTerminateInvocationFeatures {
    .structureType  = StructureTypePhysicalDeviceShaderTerminateInvocationFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceShadingRateImageFeaturesNVidia ) shadingRateImageFeaturesNVidia {
    .structureType  = StructureTypePhysicalDeviceShadingRateImageFeaturesNVidia
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceSubgroupSizeControlFeatures ) subgroupSizeControlFeatures {
    .structureType  = StructureTypePhysicalDeviceSubgroupSizeControlFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceSubpassShadingFeaturesHuawei ) subpassShadingFeaturesHuawei {
    .structureType  = StructureTypePhysicalDeviceSubpassShadingFeaturesHuawei
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceSynchronizationFeatures ) synchronizationFeatures {
    .structureType  = StructureTypePhysicalDeviceSynchronizationFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceTexelBufferAlignmentFeatures ) texelBufferAlignmentFeatures {
    .structureType  = StructureTypePhysicalDeviceTexelBufferAlignmentFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXTURE_COMPRESSION_ASTC_HDR_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceTextureCompressionASTCHDRFeatures ) textureCompressionASTCHDRFeatures {
    .structureType  = StructureTypePhysicalDeviceTextureCompressionASTCHDRFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceTransformFeedbackFeatures ) transformFeedbackFeatures {
    .structureType  = StructureTypePhysicalDeviceTransformFeedbackFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceVertexAttributeDivisorFeatures ) vertexAttributeDivisorFeatures {
    .structureType  = StructureTypePhysicalDeviceVertexAttributeDivisorFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_INPUT_DYNAMIC_STATE_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceVertexInputDynamicStateFeatures ) vertexInputDynamicStateFeatures {
    .structureType  = StructureTypePhysicalDeviceVertexInputDynamicStateFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceShaderIntegerDotProductFeatures ) shaderIntegerDotProductFeatures {
    .structureType  = StructureTypePhysicalDeviceShaderIntegerDotProductFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_SHADER_INTEGER_FUNCTIONS_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceShaderIntegerFunctionsFeaturesIntel ) shaderIntegerFunctionsFeaturesIntel {
    .structureType  = StructureTypePhysicalDeviceShaderIntegerFunctionsFeaturesIntel
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceWorkgroupMemoryExplicitLayoutFeatures ) workgroupMemoryExplicitLayoutFeatures {
    .structureType  = StructureTypePhysicalDeviceWorkgroupMemoryExplicitLayoutFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_2_PLANE_444_FORMATS_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceYCBCR2Plane444FormatsFeatures ) YCBCR2Plane444FormatFeatures {
    .structureType  = StructureTypePhysicalDeviceYCBCR2Plane444FormatsFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_IMAGE_ARRAYS_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceYCBCRImageArraysFeatures ) YCBCRImageArraysFeatures {
    .structureType  = StructureTypePhysicalDeviceYCBCRImageArraysFeatures
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ZERO_INITIALIZE_WORKGROUP_MEMORY_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
static __C_ENG_TYPE ( PhysicalDeviceZeroInitializeWorkgroupMemoryFeatures ) zeroInitializeWorkgroupMemoryFeatures {
    .structureType  = StructureTypePhysicalDeviceZeroInitializeWorkgroupMemoryFeatures
};
#endif

static StructureWithSize deviceCreationStructures [] = {

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & vulkan11Features ),                                                     .size = static_cast < uint32 > ( sizeof ( vulkan11Features ) ) },
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & _16BitStorageFeatures ),                                                .size = static_cast < uint32 > ( sizeof ( _16BitStorageFeatures ) ) },
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & multiviewFeatures ),                                                    .size = static_cast < uint32 > ( sizeof ( multiviewFeatures ) ) },
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & protectedMemoryFeatures ),                                              .size = static_cast < uint32 > ( sizeof ( protectedMemoryFeatures ) ) },
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & samplerYCBCRConversionFeatures ),                                       .size = static_cast < uint32 > ( sizeof ( samplerYCBCRConversionFeatures ) ) },
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & shaderDrawParametersFeatures ),                                         .size = static_cast < uint32 > ( sizeof ( shaderDrawParametersFeatures ) ) },
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & variablePointersFeatures ),                                             .size = static_cast < uint32 > ( sizeof ( variablePointersFeatures ) ) },
#endif


#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & vulkan12Features ) ,                                                    .size = static_cast < uint32 > ( sizeof ( vulkan12Features ) ) },
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & _8BitStorageFeatures ) ,                                                .size = static_cast < uint32 > ( sizeof ( _8BitStorageFeatures ) ) },
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & bufferDeviceAddressFeatures ) ,                                         .size = static_cast < uint32 > ( sizeof ( bufferDeviceAddressFeatures ) ) },
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & descriptorIndexingFeatures ) ,                                          .size = static_cast < uint32 > ( sizeof ( descriptorIndexingFeatures ) ) },
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & hostQueryResetFeatures ) ,                                              .size = static_cast < uint32 > ( sizeof ( hostQueryResetFeatures ) ) },
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & imagelessFramebufferFeatures ) ,                                        .size = static_cast < uint32 > ( sizeof ( imagelessFramebufferFeatures ) ) },
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & scalarBlockLayoutFeatures ) ,                                           .size = static_cast < uint32 > ( sizeof ( scalarBlockLayoutFeatures ) ) },
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & separateDepthStencilLayoutsFeatures ) ,                                 .size = static_cast < uint32 > ( sizeof ( separateDepthStencilLayoutsFeatures ) ) },
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & shaderAtomicInt64Features ) ,                                           .size = static_cast < uint32 > ( sizeof ( shaderAtomicInt64Features ) ) },
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & shaderFloat16Int8Features ) ,                                           .size = static_cast < uint32 > ( sizeof ( shaderFloat16Int8Features ) ) },
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & shaderSubgroupExtendedTypesFeatures ) ,                                 .size = static_cast < uint32 > ( sizeof ( shaderSubgroupExtendedTypesFeatures ) ) },
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & timelineSemaphoreFeatures ) ,                                           .size = static_cast < uint32 > ( sizeof ( timelineSemaphoreFeatures ) ) },
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & uniformBufferStandardLayoutFeatures ) ,                                 .size = static_cast < uint32 > ( sizeof ( uniformBufferStandardLayoutFeatures ) ) },
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & vulkanMemoryModelFeatures ) ,                                           .size = static_cast < uint32 > ( sizeof ( vulkanMemoryModelFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & vulkan13Features ),                                                   .size = static_cast < uint32 > ( sizeof ( vulkan13Features ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_4444_FORMATS_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & _4444FormatsFeatures ),                                                 .size = static_cast < uint32 > ( sizeof ( _4444FormatsFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_ASTC_DECODE_MODE_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & ASTCDecodeFeatures ),                                                   .size = static_cast < uint32 > ( sizeof ( ASTCDecodeFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & accelerationStructureFeatures ),                                        .size = static_cast < uint32 > ( sizeof ( accelerationStructureFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & blendOperationAdvancedFeatures ),                                       .size = static_cast < uint32 > ( sizeof ( blendOperationAdvancedFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_BORDER_COLOR_SWIZZLE_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & borderColorSwizzleFeatures ),                                           .size = static_cast < uint32 > ( sizeof ( borderColorSwizzleFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_DEVICE_COHERENT_MEMORY_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & coherentMemoryFeaturesAMD ),                                            .size = static_cast < uint32 > ( sizeof ( coherentMemoryFeaturesAMD ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_COLOR_WRITE_ENABLE_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & colorWriteEnabledFeatures ),                                            .size = static_cast < uint32 > ( sizeof ( colorWriteEnabledFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COMPUTE_SHADER_DERIVATIVES_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & computeShaderDerivativesFeaturesNVidia ),                               .size = static_cast < uint32 > ( sizeof ( computeShaderDerivativesFeaturesNVidia ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & conditionalRenderingFeatures ),                                         .size = static_cast < uint32 > ( sizeof ( conditionalRenderingFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & cooperativeMatrixFeaturesNVidia ),                                      .size = static_cast < uint32 > ( sizeof ( cooperativeMatrixFeaturesNVidia ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CORNER_SAMPLED_IMAGE_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & cornerSampledImageFeaturesNVidia ),                                     .size = static_cast < uint32 > ( sizeof ( cornerSampledImageFeaturesNVidia ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COVERAGE_REDUCTION_MODE_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & coverageReductionModeFeaturesNVidia ),                                  .size = static_cast < uint32 > ( sizeof ( coverageReductionModeFeaturesNVidia ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & customBorderColorFeatures ),                                            .size = static_cast < uint32 > ( sizeof ( customBorderColorFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_IMAGE_ALIASING_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & dedicatedAllocationImageAliasingFeaturesNVidia ),                       .size = static_cast < uint32 > ( sizeof ( dedicatedAllocationImageAliasingFeaturesNVidia ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_CONTROL_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & depthClipControlFeatures ),                                             .size = static_cast < uint32 > ( sizeof ( depthClipControlFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_ENABLE_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & depthClipEnableFeatures ),                                              .size = static_cast < uint32 > ( sizeof ( depthClipEnableFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & deviceGeneratedCommandsFeatures ),                                      .size = static_cast < uint32 > ( sizeof ( deviceGeneratedCommandsFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEVICE_MEMORY_REPORT_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & deviceMemoryReportFeatures ),                                           .size = static_cast < uint32 > ( sizeof ( deviceMemoryReportFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTICS_CONFIG_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & diagnosticsConfigFeaturesNVidia ),                                      .size = static_cast < uint32 > ( sizeof ( diagnosticsConfigFeaturesNVidia ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & dynamicRenderingFeatures ),                                             .size = static_cast < uint32 > ( sizeof ( dynamicRenderingFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SCISSOR_EXCLUSIVE_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & exclusiveScissorFeaturesNVidia ),                                       .size = static_cast < uint32 > ( sizeof ( exclusiveScissorFeaturesNVidia ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & extendedDynamicStateFeatures ),                                         .size = static_cast < uint32 > ( sizeof ( extendedDynamicStateFeatures ) ) },
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & extendedDynamicState2Features ),                                        .size = static_cast < uint32 > ( sizeof ( extendedDynamicState2Features ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_RDMA_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & externalMemoryRDMAFeaturesNVidia ),                                     .size = static_cast < uint32 > ( sizeof ( externalMemoryRDMAFeaturesNVidia ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & fragmentDensityMapFeatures ),                                           .size = static_cast < uint32 > ( sizeof ( fragmentDensityMapFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & fragmentDensityMap2Features ),                                          .size = static_cast < uint32 > ( sizeof ( fragmentDensityMap2Features ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & fragmentDensityMapOffsetFeaturesQualcomm ),                             .size = static_cast < uint32 > ( sizeof ( fragmentDensityMapOffsetFeaturesQualcomm ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADER_BARYCENTRIC_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & fragmentShaderBarycentricFeaturesNVidia ),                              .size = static_cast < uint32 > ( sizeof ( fragmentShaderBarycentricFeaturesNVidia ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & fragmentShadingRateEnumsFeaturesNVidia ),                               .size = static_cast < uint32 > ( sizeof ( fragmentShadingRateEnumsFeaturesNVidia ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & fragmentShadingRateFeatures ),                                          .size = static_cast < uint32 > ( sizeof ( fragmentShadingRateFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & globalPriorityQueryFeatures ),                                          .size = static_cast < uint32 > ( sizeof ( globalPriorityQueryFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_ROBUSTNESS_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & imageRobustnessFeatures ),                                              .size = static_cast < uint32 > ( sizeof ( imageRobustnessFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_VIEW_MIN_LOD_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & imageViewMinLODFeatures ),                                              .size = static_cast < uint32 > ( sizeof ( imageViewMinLODFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INDEX_TYPE_UINT8_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & indexTypeUInt8Features ),                                               .size = static_cast < uint32 > ( sizeof ( indexTypeUInt8Features ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_INHERITED_VIEWPORT_SCISSOR_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & inheritedViewportScissorFeaturesNVidia ),                               .size = static_cast < uint32 > ( sizeof ( inheritedViewportScissorFeaturesNVidia ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & inlineUniformBlockFeatures ),                                           .size = static_cast < uint32 > ( sizeof ( inlineUniformBlockFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_INVOCATION_MASK_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & invocationMaskFeaturesHuawei ),                                         .size = static_cast < uint32 > ( sizeof ( invocationMaskFeaturesHuawei ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & lineRasterizationFeatures ),                                            .size = static_cast < uint32 > ( sizeof ( lineRasterizationFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_LINEAR_COLOR_ATTACHMENT_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & linearColorAttachmentFeaturesNVidia ),                                  .size = static_cast < uint32 > ( sizeof ( linearColorAttachmentFeaturesNVidia ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & maintenance4Features ),                                                 .size = static_cast < uint32 > ( sizeof ( maintenance4Features ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_PRIORITY_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & memoryPriorityFeatures ),                                               .size = static_cast < uint32 > ( sizeof ( memoryPriorityFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & meshShaderFeaturesNVidia ),                                             .size = static_cast < uint32 > ( sizeof ( meshShaderFeaturesNVidia ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & multiDrawFeatures ),                                                    .size = static_cast < uint32 > ( sizeof ( multiDrawFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & mutableDescriptorTypeFeaturesValve ),                                   .size = static_cast < uint32 > ( sizeof ( mutableDescriptorTypeFeaturesValve ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PAGEABLE_DEVICE_LOCAL_MEMORY_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & pageableDeviceLocalMemoryFeatures ),                                    .size = static_cast < uint32 > ( sizeof ( pageableDeviceLocalMemoryFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & performanceQueryFeatures ),                                             .size = static_cast < uint32 > ( sizeof ( performanceQueryFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & pipelineCreationCacheControlFeatures ),                                 .size = static_cast < uint32 > ( sizeof ( pipelineCreationCacheControlFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & pipelineExecutablePropertiesFeatures ),                                 .size = static_cast < uint32 > ( sizeof ( pipelineExecutablePropertiesFeatures ) ) },
#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & portabilitySubsetFeatures ),                                            .size = static_cast < uint32 > ( sizeof ( portabilitySubsetFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_ID_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & presentIDFeatures ),                                                    .size = static_cast < uint32 > ( sizeof ( presentIDFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_WAIT_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & presentWaitFeatures ),                                                  .size = static_cast < uint32 > ( sizeof ( presentWaitFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIMITIVE_TOPOLOGY_LIST_RESTART_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & primitiveTopologyListRestartFeatures ),                                 .size = static_cast < uint32 > ( sizeof ( primitiveTopologyListRestartFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & privateDataFeatures ),                                                  .size = static_cast < uint32 > ( sizeof ( privateDataFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & provokingVertexFeatures ),                                              .size = static_cast < uint32 > ( sizeof ( provokingVertexFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_RGBA_10_X_6_FORMATS_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & RGBA10x6FormatsFeatures ),                                              .size = static_cast < uint32 > ( sizeof ( RGBA10x6FormatsFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_ARM_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & rasterizationOrderAttachmentAccessFeaturesARM ),                        .size = static_cast < uint32 > ( sizeof ( rasterizationOrderAttachmentAccessFeaturesARM ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_QUERY_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & rayQueryFeatures ),                                                     .size = static_cast < uint32 > ( sizeof ( rayQueryFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & rayTracingMotionBlurFeaturesNVidia ),                                   .size = static_cast < uint32 > ( sizeof ( rayTracingMotionBlurFeaturesNVidia ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & rayTracingPipelineFeatures ),                                           .size = static_cast < uint32 > ( sizeof ( rayTracingPipelineFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_REPRESENTATIVE_FRAGMENT_TEST_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & representativeFragmentTestFeaturesNVidia ),                             .size = static_cast < uint32 > ( sizeof ( representativeFragmentTestFeaturesNVidia ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & robustnessFeatures ),                                                   .size = static_cast < uint32 > ( sizeof ( robustnessFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & shaderAtomicFloatFeatures ),                                            .size = static_cast < uint32 > ( sizeof ( shaderAtomicFloatFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_2_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & shaderAtomicFloat2Features ),                                           .size = static_cast < uint32 > ( sizeof ( shaderAtomicFloat2Features ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_CLOCK_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & shaderClockFeatures ),                                                  .size = static_cast < uint32 > ( sizeof ( shaderClockFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_DEMOTE_TO_HELPER_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & shaderDemoteToHelperInvocationFeatures ),                               .size = static_cast < uint32 > ( sizeof ( shaderDemoteToHelperInvocationFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_IMAGE_ATOMIC_INT64_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & shaderImageAtomicInt64Features ),                                       .size = static_cast < uint32 > ( sizeof ( shaderImageAtomicInt64Features ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_IMAGE_FOOTPRINT_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & shaderImageFootprintFeaturesNVidia ),                                   .size = static_cast < uint32 > ( sizeof ( shaderImageFootprintFeaturesNVidia ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & shaderSmBuiltinsFeaturesNVidia ),                                       .size = static_cast < uint32 > ( sizeof ( shaderSmBuiltinsFeaturesNVidia ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_SUBGROUP_UNIFORM_CONTROL_FLOW_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & shaderSubgroupUniformControlFlowFeatures ),                             .size = static_cast < uint32 > ( sizeof ( shaderSubgroupUniformControlFlowFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_TERMINATE_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & shaderTerminateInvocationFeatures ),                                    .size = static_cast < uint32 > ( sizeof ( shaderTerminateInvocationFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & shadingRateImageFeaturesNVidia ),                                       .size = static_cast < uint32 > ( sizeof ( shadingRateImageFeaturesNVidia ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & subgroupSizeControlFeatures ),                                          .size = static_cast < uint32 > ( sizeof ( subgroupSizeControlFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & subpassShadingFeaturesHuawei ),                                         .size = static_cast < uint32 > ( sizeof ( subpassShadingFeaturesHuawei ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & synchronizationFeatures ),                                              .size = static_cast < uint32 > ( sizeof ( synchronizationFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & texelBufferAlignmentFeatures ),                                         .size = static_cast < uint32 > ( sizeof ( texelBufferAlignmentFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXTURE_COMPRESSION_ASTC_HDR_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & textureCompressionASTCHDRFeatures ),                                    .size = static_cast < uint32 > ( sizeof ( textureCompressionASTCHDRFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & transformFeedbackFeatures ),                                            .size = static_cast < uint32 > ( sizeof ( transformFeedbackFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & vertexAttributeDivisorFeatures ),                                       .size = static_cast < uint32 > ( sizeof ( vertexAttributeDivisorFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_INPUT_DYNAMIC_STATE_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & vertexInputDynamicStateFeatures ),                                      .size = static_cast < uint32 > ( sizeof ( vertexInputDynamicStateFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & shaderIntegerDotProductFeatures ),                                      .size = static_cast < uint32 > ( sizeof ( shaderIntegerDotProductFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_SHADER_INTEGER_FUNCTIONS_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & shaderIntegerFunctionsFeaturesIntel ),                                  .size = static_cast < uint32 > ( sizeof ( shaderIntegerFunctionsFeaturesIntel ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & workgroupMemoryExplicitLayoutFeatures ),                                .size = static_cast < uint32 > ( sizeof ( workgroupMemoryExplicitLayoutFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_2_PLANE_444_FORMATS_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & YCBCR2Plane444FormatFeatures ),                                         .size = static_cast < uint32 > ( sizeof ( YCBCR2Plane444FormatFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_IMAGE_ARRAYS_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & YCBCRImageArraysFeatures ),                                             .size = static_cast < uint32 > ( sizeof ( YCBCRImageArraysFeatures ) ) },
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ZERO_INITIALIZE_WORKGROUP_MEMORY_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
        { .pStructure = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( & zeroInitializeWorkgroupMemoryFeatures ),                                .size = static_cast < uint32 > ( sizeof ( zeroInitializeWorkgroupMemoryFeatures ) ) },
#endif

};
}

using QueueFamilyIndex = uint32;

namespace globals {
    static __C_ENG_TYPE ( PhysicalDeviceDetails ) physicalDeviceDetails;

    static Mutex deviceCreationLock;
    static StringLiteral    extensionNames [ engine :: vulkan :: config :: layerExtensionCount ];
    static uint32           extensionCount;

    static HashMap < vulkan :: __C_ENG_TYPE ( QueueFlag ), HashMap < QueueFamilyIndex, uint32 > > typeFamilyCount;

    static vulkan :: __C_ENG_TYPE ( DeviceQueueCreateInfo ) queueCreateInfos [ engine :: vulkan :: config :: queueFamilyCount ];
    static float                                            queuePriorities [ engine :: vulkan :: config :: queueFamilyCount ][ engine :: vulkan :: config :: queueFamilyQueueCount ];
    static uint32                                           queueCreateInfoCount;
}

#define C_ENG_MAP_START     NESTED_CLASS ( Builder, ENGINE_TYPE ( Device ), PARENT ( cds :: Object ) )
#include <ObjectMapping.hpp>


static inline auto deviceCreateInfoAddAllFeatures (
        Type ( DeviceCreateInfo )       * pCreateInfo,
        Type ( PhysicalDevice )   const * pPhysicalDevice,
        bool                            * pProtectedMemoryEnabled
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if (
            pCreateInfo             == nullptr ||
            pPhysicalDevice         == nullptr ||
            pProtectedMemoryEnabled == nullptr
    ) {
        return;
    }

#endif

    static Type ( PhysicalDeviceDetails )   details;

    (void) std :: memcpy ( & globals :: extendedFeatures.features, & pPhysicalDevice->details().basicFeatures, sizeof ( Type ( PhysicalDeviceFeatures ) ) );
    (void) std :: memcpy ( & details, & ( pPhysicalDevice->details() ), sizeof ( details ) );

    vulkan :: utility :: chainFeaturesFromDetails ( & globals :: extendedFeatures, & details );

    * pProtectedMemoryEnabled =
            ( pPhysicalDevice->details().vulkan11Features.protectedMemory == VK_TRUE ) ||
            ( pPhysicalDevice->details().protectedMemoryFeatures.protectedMemory == VK_TRUE );

    pCreateInfo->pNext = & globals :: extendedFeatures;
}

static inline auto deviceCreateInfoAddOnlyBasicFeatures (
        Type ( DeviceCreateInfo )       * pCreateInfo,
        Type ( PhysicalDevice )   const * pPhysicalDevice,
        bool                            * pProtectedMemoryEnabled
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if (
            pCreateInfo             == nullptr ||
            pPhysicalDevice         == nullptr ||
            pProtectedMemoryEnabled == nullptr
    ) {
        return;
    }

#endif

    (void) std :: memcpy ( & globals :: basicFeatures, & pPhysicalDevice->details().basicFeatures, sizeof ( globals :: basicFeatures ) );
    pCreateInfo->pEnabledFeatures   = & globals :: basicFeatures;

    * pProtectedMemoryEnabled       = false;
}

static inline auto deviceCreateInfoAddFeatureSets (
        Type ( DeviceCreateInfo )                                 * pCreateInfo,
        Type ( PhysicalDevice )                             const * pPhysicalDevice,
        Collection < Type ( GenericInStructure ) const * >  const & featureSets,
        bool                                                      * pProtectedMemoryEnabled
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if (
            pCreateInfo             == nullptr ||
            pProtectedMemoryEnabled == nullptr
    ) {
        return;
    }

#endif

    auto pCurrentStr = reinterpret_cast < Type ( GenericOutStructure ) * > ( & globals :: extendedFeatures );
    (void) std :: memcpy (
            & globals :: extendedFeatures.features,
            & pPhysicalDevice->details().basicFeatures,
            sizeof ( globals :: extendedFeatures.features )
    );

    for ( auto const & featureSet : featureSets ) {

        if (
                featureSet->structureType == StructureTypePhysicalDeviceVulkan_1_1_Features &&
                ! * pProtectedMemoryEnabled && reinterpret_cast < Type ( PhysicalDeviceVulkan11Features ) const * > ( featureSet )->protectedMemory == VK_TRUE      ||
                featureSet->structureType == StructureTypePhysicalDeviceProtectedMemoryFeatures &&
                ! * pProtectedMemoryEnabled && reinterpret_cast < Type ( PhysicalDeviceProtectedMemoryFeatures ) const * > ( featureSet )->protectedMemory == VK_TRUE
        ) {
            * pProtectedMemoryEnabled = true;
        }

        if ( featureSet->structureType == StructureTypePhysicalDeviceFeatures ) {

            (void) std :: memcpy (
                    & globals :: extendedFeatures.features,
                    & reinterpret_cast < Type ( PhysicalDeviceExtendedFeatures ) const * > ( featureSet )->features,
                    sizeof ( globals :: extendedFeatures.features )
            );
        } else {

            for ( auto & featureStructure : globals :: deviceCreationStructures ) {

                if ( featureStructure.pStructure->structureType == featureSet->structureType ) {

                    (void) std :: memcpy (
                            reinterpret_cast < Byte * >         ( featureStructure.pStructure ) + sizeof ( Type ( GenericOutStructure ) ),
                            reinterpret_cast < Byte const * >   ( & featureSet )                + sizeof ( Type ( GenericOutStructure ) ),
                            featureStructure.size - static_cast < uint32 > ( sizeof ( Type ( GenericOutStructure ) ) )
                    );

                    pCurrentStr = pCurrentStr->pNext = featureStructure.pStructure; // NOLINT(clion-misra-cpp2008-6-2-1)
                }
            }
        }
    }

    pCurrentStr->pNext = nullptr;
    pCreateInfo->pNext = & globals :: extendedFeatures;
}

auto Self :: build () noexcept (false) -> Nester {
    this->_extensionNames.add ( VK_KHR_SWAPCHAIN_EXTENSION_NAME );

    LockGuard deviceCreationGuard ( globals :: deviceCreationLock );

    if (
            this->_surfaceHandle    != nullptr &&
            this->_physicalDevice   != nullptr
    ) {
        return this->buildSingleDeviceToSurface();
    }

    throw Type ( VulkanAPIException ) ( "Unable to build device from given objects" );
}

auto Self :: deviceCreateInfoAddFeatures (
        Type ( DeviceCreateInfo ) * pCreateInfo,
        bool                      * pProtectedMemoryEnabled
) noexcept (false) -> Self & {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if (
            pCreateInfo             == nullptr ||
            pProtectedMemoryEnabled == nullptr
    ) {
        return * this;
    }

#endif

    uint32 featureOptionCount =
            (this->_allFeatures ? 1U : 0U) +
            (this->_onlyBasicFeatures ? 1U : 0U) +
            (this->_featureSets.empty() ? 0U : 1U);

    if ( featureOptionCount > 1U ) {
        throw Type ( VulkanAPIException ) ( "Must select one and only one option for feature sets to use from device. (allFeatures, onlyBasicFeatures, featureSets" );
    }

    if ( this->_allFeatures ) {
        deviceCreateInfoAddAllFeatures ( pCreateInfo, this->_physicalDevice, pProtectedMemoryEnabled );
    } else if ( ! this->_featureSets.empty() ) {
        deviceCreateInfoAddFeatureSets ( pCreateInfo, this->_physicalDevice, this->_featureSets,  pProtectedMemoryEnabled );
    } else {
        deviceCreateInfoAddOnlyBasicFeatures ( pCreateInfo, this->_physicalDevice, pProtectedMemoryEnabled );
    }

    return * this;
}

auto Self :: deviceCreateInfoAddExtensions (
        Type ( DeviceCreateInfo ) * pCreateInfo
) noexcept (false) -> Self & {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pCreateInfo == nullptr ) {
        return * this;
    }

#endif

    globals :: extensionCount = 0U;

    for ( auto const & extensionName : this->_extensionNames ) {
        globals :: extensionNames [ globals :: extensionCount ++ ] = extensionName.cStr();
    }

    pCreateInfo->enabledExtensionCount  = globals :: extensionCount;
    pCreateInfo->pEnabledExtensionNames = & globals :: extensionNames[0];

    return * this;
}

auto Self :: deviceCreateInfoAddQueueCreateInfos (
        Type ( DeviceCreateInfo )                                   * pCreateInfo,
        bool                                                          protectedMemoryEnabled,
        bool                                                          preferExclusivity
) noexcept (false) -> Self & {

    HashMap < Type ( QueueFlag ), uint32 > requiredQueueCounts;
    HashMap < QueueFamilyIndex, Type ( QueueFlags ) > queueFamilyFlags;
    HashMap < QueueFamilyIndex, uint32 > totalFamilyCounts;
    HashMap < QueueFamilyIndex, uint32 > usedFamilyCounts;

    globals :: typeFamilyCount.clear();

    requiredQueueCounts [ QueueFlagGraphics ]   = this->_graphicsQueueCount;
    requiredQueueCounts [ QueueFlagTransfer ]   = this->_transferQueueCount;
    requiredQueueCounts [ QueueFlagPresent ]    = this->_presentQueueCount;

    for ( auto const & family : this->_physicalDevice->queueFamilies() ) {
        queueFamilyFlags [ family.index() ] = family.query()
                .select < Type ( QueueFlags ) > ()
                .withSurface ( this->_surfaceHandle )
                .execute();

        totalFamilyCounts [ family.index() ] = family.details().properties.queueCount;
    }

    for ( auto type : Array < __C_ENG_TYPE ( QueueFlag ) > { QueueFlagGraphics, QueueFlagTransfer, QueueFlagPresent } ) {

        HashMap < uint32, uint32 > familyCounts;
        uint32 totalCount = 0U;

        for ( auto const & family : this->_physicalDevice->queueFamilies() ) {
            if ( ( queueFamilyFlags [ family.index() ] & static_cast < uint32 > ( type ) ) != 0U ) {
                totalCount += family.details().properties.queueCount;
                familyCounts [ family.index() ] = family.details().properties.queueCount;
            }
        }

        uint32 totalForType = 0U;

        for ( auto const & familyCount : familyCounts ) {
            auto ratio = static_cast < float > ( familyCount.second() ) / static_cast < float > ( totalCount );
            globals :: typeFamilyCount [ type ] [ familyCount.first() ] = static_cast < uint32 > ( ratio * static_cast < float > ( requiredQueueCounts [ type ] ) );
            totalForType += globals :: typeFamilyCount [ type ] [ familyCount.first() ];
        }

        if ( totalForType < requiredQueueCounts [ type ] ) {
            familyCounts.sequence()
                .maxBy( []( auto const & familyCount ){ return familyCount.second(); } )
                .ifPresent ( [type, & requiredQueueCounts, & totalForType] ( auto & familyCount ) {
                    globals :: typeFamilyCount [ type ] [ familyCount.first() ] += requiredQueueCounts [ type ] - totalForType;
                    totalForType = requiredQueueCounts [ type ];
                });
        }
    }

    for ( auto & familyCounts : globals :: typeFamilyCount ) {
        uint32 carryToOtherFamily = 0U;

        for ( auto & familyCount : familyCounts.second() ) {
            if ( usedFamilyCounts [ familyCount.first() ] + familyCount.second() <= totalFamilyCounts [ familyCount.first() ] ) {
                usedFamilyCounts [ familyCount.first() ] += familyCount.second();
            } else {

                uint32 ableToUse = totalFamilyCounts [ familyCount.first() ] - usedFamilyCounts [ familyCount.first() ];
                usedFamilyCounts [ familyCount.first() ] = totalFamilyCounts [ familyCount.first() ];

                uint32 remainingOutside = familyCount.second() - ableToUse;
                familyCount.second() = ableToUse;

                carryToOtherFamily += remainingOutside;
            }
        }

        for ( auto & familyCount : familyCounts.second() ) {
            if ( usedFamilyCounts [ familyCount.first() ] < totalFamilyCounts [ familyCount.first() ] ) {

                uint32 ableToFit = totalFamilyCounts [ familyCount.first() ] - usedFamilyCounts [ familyCount.first() ];

                if ( ableToFit >= carryToOtherFamily ) {
                    ableToFit = carryToOtherFamily;
                    carryToOtherFamily = 0U;
                } else {
                    carryToOtherFamily -= ableToFit;
                }

                usedFamilyCounts [ familyCount.first() ] += ableToFit;
                familyCount.second() += ableToFit;

                if ( carryToOtherFamily == 0U ) {
                    break;
                }
            }
        }
    }


    globals :: queueCreateInfoCount = 0U;
    for ( auto & usedFamilyCount : usedFamilyCounts ) {

        if ( usedFamilyCount.second() > engine :: vulkan :: config :: queueFamilyQueueCount ) {
            throw Type ( VulkanAPIException ) ( "Too many queues reserved from family '"_s + usedFamilyCount.first() + "'. Increase capacity in configuration" );
        }

        if ( usedFamilyCount.second() == 0U ) {
            continue;
        }

        for ( uint32 i = 0U; i < usedFamilyCount.second(); ++ i ) {
            globals :: queuePriorities [ usedFamilyCount.first() ][ i ] = 1.0F; // temp value
        }

        globals :: queueCreateInfos [ globals :: queueCreateInfoCount ++ ] = {
                .structureType      = StructureTypeDeviceQueueCreateInfo,
                .pNext              = nullptr,
                .flags              = 0U,
                .queueFamilyIndex   = usedFamilyCount.first(),
                .queueCount         = usedFamilyCount.second(),
                .pQueuePriorities   = & globals :: queuePriorities [ usedFamilyCount.first() ][0]
        };
    }

    pCreateInfo->queueCreateInfoCount   = globals :: queueCreateInfoCount;
    pCreateInfo->pQueueCreateInfos      = & globals :: queueCreateInfos[0];

    return * this;
}

auto Self :: buildSingleDeviceToSurface () noexcept (false) -> Nester {
    Nester device;

    device._physicalDevice  = this->_physicalDevice;
    device._surfaceHandle   = this->_surfaceHandle;

    Type ( DeviceCreateInfo ) deviceCreateInfo {
        .structureType  = StructureTypeDeviceCreateInfo,
        .pNext          = nullptr,
        .flags          = 0U
    };

    bool protectedMemoryEnabled = false;

    (void) this->addImplicitDeviceExtensions();
    (void) this->filterUnsupportedExtensions();

    (void) this->deviceCreateInfoAddFeatures ( & deviceCreateInfo, & protectedMemoryEnabled );
    (void) this->deviceCreateInfoAddExtensions ( & deviceCreateInfo );

    (void) this->deviceCreateInfoAddQueueCreateInfos (
            & deviceCreateInfo,
            protectedMemoryEnabled,
            this->_preferExclusiveOperations
    );

    auto result = vulkan :: createDevice (
            this->_physicalDevice->handle(),
            & deviceCreateInfo,
            Type ( Allocator ) :: instance().callbacks(),
            & device._handle
    );

    if ( result != ResultSuccess ) {
        __C_ENG_LOG_AND_THROW_DETAILED_API_CALL_EXCEPTION ( error, "createDevice", result );
    } else {
        (void) Type ( Logger ) :: instance ().info (
                "Created Logical Device with handle '"_s + :: toString ( device._handle ) +
                "' from Physical Device " + this->_physicalDevice->details().basicProperties.deviceName
        );
    }

    uint32 totalUsedQueues = 0U;
    for ( uint32 i = 0U; i < globals :: queueCreateInfoCount; ++ i ) {
        totalUsedQueues += globals :: queueCreateInfos[i].queueCount;
    }

    (void) device._queues.resize ( totalUsedQueues );
    uint32 currentQueueIndex = 0U;

    HashMap < QueueFamilyIndex, uint32 > usedSoFar;

    for ( auto const & type : globals :: typeFamilyCount ) {
        for ( auto const & familyAndCounts : type.second() ) {
            for ( uint32 queueIndex = 0U; queueIndex < familyAndCounts.second(); ++ queueIndex ) {
                (void) device._queues [ static_cast < Index > ( currentQueueIndex ++ ) ].init (
                    & device,
                    & this->_physicalDevice->queueFamilies() [ static_cast < Index > ( familyAndCounts.first() ) ],
                    queueIndex + usedSoFar [ familyAndCounts.first() ],
                    type.first()
                );
            }

            usedSoFar [ familyAndCounts.first() ] += familyAndCounts.second();
        }
    }

    (void) Type ( Logger ) :: instance().debug (
            "Using "_s + totalUsedQueues + " queues: "
    );

    for ( auto const & queue : device.queues() ) {
        (void) Type ( Logger ) :: instance().debug (
            "Queue -> index = "_s + queue.index() + ", type = " + :: toString ( queue.type() ) + ", family = " + queue.queueFamily()->index()
        );
    }

    return device;
}

auto Self :: addImplicitDeviceExtensions () noexcept (false) -> Self & {
    if ( this->_useImplicitExtensions ) {
        for ( uint32 i = 0U; i < this->_physicalDevice->extensions().count; ++ i ) {
            if ( this->_physicalDevice->extensions().pExtensions[i].enabled ) {
                this->_extensionNames.add ( this->_physicalDevice->extensions().pExtensions[i].properties.name );
            }
        }
    }

    return * this;
}

auto Self :: filterUnsupportedExtensions ( Collection < String > const & mandatoryExtensions ) noexcept (false) -> Self & {
    HashSet < String > newExtensions;

    for ( auto & extensionName : this->_extensionNames ) {
        bool supported = false;

        for ( uint32 i = 0U; i < this->_physicalDevice->extensions().count; ++i ) {
            if ( extensionName == this->_physicalDevice->extensions().pExtensions[i].properties.name ) {
                supported = true;
                break;
            }
        }

        if ( supported ) {
            newExtensions.insert ( extensionName );
        } else if ( mandatoryExtensions.contains ( extensionName ) ) {
            throw Type ( VulkanAPIException ( "Device requires '" + extensionName + "' extension, but it is not supported" ) );
        } else {
            /* do nothing */
        }
    }

    this->_extensionNames = std :: move ( newExtensions );

    return * this;
}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     CLASS ( Device, ENGINE_PARENT ( VulkanRenderObject ) )
#include <ObjectMapping.hpp>

auto Self :: clear () noexcept (false) -> Self & {

    if ( this->_handle != nullptr ) {

        auto result = vulkan :: destroyDevice (
                this->_handle,
                Type ( Allocator ) :: instance().callbacks()
        );

        if ( result != ResultSuccess ) {
            __C_ENG_LOG_AND_THROW_DETAILED_API_CALL_EXCEPTION ( warning, "destroyDevice", result );
        }

        this->_handle = nullptr;
        this->_queues.clear();
    }

    return * this;
}

Self :: Destructor () noexcept {
    (void) this-> Self :: clear ();
}

Self :: Constructor (
        Self && deviceRef
) noexcept :
        _handle ( exchange ( deviceRef._handle, nullptr ) ),
        _surfaceHandle ( exchange ( deviceRef._surfaceHandle, nullptr ) ),
        _physicalDevice ( exchange ( deviceRef._physicalDevice, nullptr ) ),
        _queues ( std :: move ( deviceRef._queues ) ) {

}

auto Self :: operator = (
        Self && deviceRef
) noexcept -> Self & {

    if ( this == & deviceRef ) {
        return * this;
    }

    this->_handle           = exchange ( deviceRef._handle, nullptr );
    this->_surfaceHandle    = exchange ( deviceRef._surfaceHandle, nullptr );
    this->_physicalDevice   = exchange ( deviceRef._physicalDevice, nullptr );
    this->_queues           = std :: move ( deviceRef._queues );

    return * this;
}

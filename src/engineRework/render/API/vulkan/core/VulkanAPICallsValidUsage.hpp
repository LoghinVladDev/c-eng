//
// Created by loghin on 17.01.2022.
//

#ifndef __C_ENG_VULKAN_API_CALLS_VALID_USAGE_HPP__
#define __C_ENG_VULKAN_API_CALLS_VALID_USAGE_HPP__

#include <CDS/HashSet>

namespace engine { // NOLINT(modernize-concat-nested-namespaces)
    namespace vulkan {

        struct ExtraValidationCallbackData {
            cds :: StringLiteral message;
        };

        using ExtraValidationCallback = void ( * ) ( ExtraValidationCallbackData const & );

        namespace hidden {
            static inline ExtraValidationCallback validationCallback = nullptr;

            static inline bool portabilitySubsetQueried = false;
            static inline bool portabilitySubsetExists = false;
        }

        static inline auto reportError (
            cds :: StringLiteral message
        ) noexcept -> void {

            if ( hidden :: validationCallback != nullptr ) {
                ExtraValidationCallbackData data {
                    .message = message
                };

                hidden :: validationCallback ( data );
            }
        }

        static inline auto setExtraValidationCallback (
                ExtraValidationCallback callback
        ) noexcept -> void {
            hidden :: validationCallback = callback;
        }

        static inline auto validateImplicit (
                __C_ENG_TYPE ( DeviceCreateInfo ) const * pCreateInfo
        ) noexcept -> bool {

            __C_ENG_TYPE ( StructureType ) acceptedStructureTypesInChain [] = {

#if __C_ENG_VULKAN_API_EXTENSION_DEVICE_MEMORY_REPORT_AVAILABLE
                    StructureTypeDeviceDeviceMemoryReportCreateInfo,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTICS_CONFIG_AVAILABLE
                    StructureTypeDeviceDiagnosticsConfigCreateInfoNVidia,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DEVICE_GROUP_AVAILABLE
                    StructureTypeDeviceGroupDeviceCreateInfo,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_MEMORY_OVERALLOCATION_BEHAVIOUR_AVAILABLE
                    StructureTypeDeviceMemoryOverAllocationCreateInfoAMD,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE
                    StructureTypeDevicePrivateDataCreateInfo,
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
                    StructureTypePhysicalDeviceVulkan_1_1_Features,
                    StructureTypePhysicalDevice16BitStorageFeatures,
                    StructureTypePhysicalDeviceMultiviewFeatures,
                    StructureTypePhysicalDeviceProtectedMemoryFeatures,
                    StructureTypePhysicalDeviceSamplerYCBCRConversionFeatures,
                    StructureTypePhysicalDeviceShaderDrawParametersFeatures,
                    StructureTypePhysicalDeviceVariablePointersFeatures,
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
                    StructureTypePhysicalDeviceVulkan_1_2_Features,
                    StructureTypePhysicalDevice8BitStorageFeatures,
                    StructureTypePhysicalDeviceBufferDeviceAddressFeatures,
                    StructureTypePhysicalDeviceDescriptorIndexingFeatures,
                    StructureTypePhysicalDeviceHostQueryResetFeatures,
                    StructureTypePhysicalDeviceImagelessFramebufferFeatures,
                    StructureTypePhysicalDeviceScalarBlockLayoutFeatures,
                    StructureTypePhysicalDeviceSeparateDepthStencilLayoutsFeatures,
                    StructureTypePhysicalDeviceShaderAtomicInt64Features,
                    StructureTypePhysicalDeviceShaderFloat16Int8Features,
                    StructureTypePhysicalDeviceShaderSubgroupExtendedTypesFeatures,
                    StructureTypePhysicalDeviceTimelineSemaphoreFeatures,
                    StructureTypePhysicalDeviceUniformBufferStandardLayoutFeatures,
                    StructureTypePhysicalDeviceVulkanMemoryModelFeatures,

                    StructureTypePhysicalDeviceFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_4444_FORMATS_AVAILABLE
                    StructureTypePhysicalDevice4444FormatsFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_ASTC_DECODE_MODE_AVAILABLE
                    StructureTypePhysicalDeviceASTCDecodeFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
                    StructureTypePhysicalDeviceAccelerationStructureFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE
                    StructureTypePhysicalDeviceBlendOperationAdvancedFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_BORDER_COLOR_SWIZZLE_AVAILABLE
                    StructureTypePhysicalDeviceBorderColorSwizzleFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_DEVICE_COHERENT_MEMORY_AVAILABLE
                    StructureTypePhysicalDeviceCoherentMemoryFeaturesAMD,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_COLOR_WRITE_ENABLE_AVAILABLE
                    StructureTypePhysicalDeviceColorWriteEnableFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COMPUTE_SHADER_DERIVATIVES_AVAILABLE
                    StructureTypePhysicalDeviceComputeShaderDerivativesFeaturesNVidia,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE
                    StructureTypePhysicalDeviceConditionalRenderingFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE
                    StructureTypePhysicalDeviceCooperativeMatrixFeaturesNVidia,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CORNER_SAMPLED_IMAGE_AVAILABLE
                    StructureTypePhysicalDeviceCornerSampledImageFeaturesNVidia,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COVERAGE_REDUCTION_MODE_AVAILABLE
                    StructureTypePhysicalDeviceCoverageReductionModeFeaturesNVidia,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE
                    StructureTypePhysicalDeviceCustomBorderColorFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_IMAGE_ALIASING_AVAILABLE
                    StructureTypePhysicalDeviceDedicatedAllocationImageAliasingFeaturesNVidia,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_CONTROL_AVAILABLE
                    StructureTypePhysicalDeviceDepthClipControlFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_ENABLE_AVAILABLE
                    StructureTypePhysicalDeviceDepthClipEnableFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE
                    StructureTypePhysicalDeviceDeviceGeneratedCommandsFeaturesNVidia,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEVICE_MEMORY_REPORT_AVAILABLE
                    StructureTypePhysicalDeviceDeviceMemoryReportFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTICS_CONFIG_AVAILABLE
                    StructureTypePhysicalDeviceDiagnosticsConfigFeaturesNVidia,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE
                    StructureTypePhysicalDeviceDynamicRenderingFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SCISSOR_EXCLUSIVE_AVAILABLE
                    StructureTypePhysicalDeviceExclusiveScissorFeaturesNVidia,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE
                    StructureTypePhysicalDeviceExtendedDynamicStateFeatures,
                    StructureTypePhysicalDeviceExtendedDynamicState2Features,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_RDMA_AVAILABLE
                    StructureTypePhysicalDeviceExternalMemoryRDMAFeaturesNVidia,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE
                    StructureTypePhysicalDeviceFragmentDensityMapFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE
                    StructureTypePhysicalDeviceFragmentDensityMap2Features,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE
                    StructureTypePhysicalDeviceFragmentDensityMapOffsetFeaturesQualcomm,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADER_BARYCENTRIC_AVAILABLE
                    StructureTypePhysicalDeviceFragmentShaderBarycentricFeaturesNVidia,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_SHADER_INTERLOCK_AVAILABLE
                    StructureTypePhysicalDeviceFragmentShaderInterlockFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE
                    StructureTypePhysicalDeviceFragmentShadingRateEnumsFeaturesNVidia,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE
                    StructureTypePhysicalDeviceFragmentShadingRateFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE
                    StructureTypePhysicalDeviceGlobalPriorityQueryFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_ROBUSTNESS_AVAILABLE
                    StructureTypePhysicalDeviceImageRobustnessFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_VIEW_MIN_LOD_AVAILABLE
                    StructureTypePhysicalDeviceImageViewMinLODFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INDEX_TYPE_UINT8_AVAILABLE
                    StructureTypePhysicalDeviceIndexTypeUInt8Features,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_INHERITED_VIEWPORT_SCISSOR_AVAILABLE
                    StructureTypePhysicalDeviceInheritedViewportScissorFeaturesNVidia,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE
                    StructureTypePhysicalDeviceInlineUniformBlockFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_INVOCATION_MASK_AVAILABLE
                    StructureTypePhysicalDeviceInvocationMaskFeaturesHuawei,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE
                    StructureTypePhysicalDeviceLineRasterizationFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_LINEAR_COLOR_ATTACHMENT_AVAILABLE
                    StructureTypePhysicalDeviceLinearColorAttachmentFeaturesNVidia,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE
                    StructureTypePhysicalDeviceMaintenance4Features,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_PRIORITY_AVAILABLE
                    StructureTypePhysicalDeviceMemoryPriorityFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE
                    StructureTypePhysicalDeviceMeshShaderFeaturesNVidia,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE
                    StructureTypePhysicalDeviceMultiDrawFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE
                    StructureTypePhysicalDeviceMutableDescriptorTypeFeaturesValve,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PAGEABLE_DEVICE_LOCAL_MEMORY_AVAILABLE
                    StructureTypePhysicalDevicePageableDeviceLocalMemoryFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
                    StructureTypePhysicalDevicePerformanceQueryFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE
                    StructureTypePhysicalDevicePipelineCreationCacheControlFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
                    StructureTypePhysicalDevicePipelineExecutablePropertiesFeatures,
#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE
                    StructureTypePhysicalDevicePortabilitySubsetFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_ID_AVAILABLE
                    StructureTypePhysicalDevicePresentIDFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_WAIT_AVAILABLE
                    StructureTypePhysicalDevicePresentWaitFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIMITIVE_TOPOLOGY_LIST_RESTART_AVAILABLE
                    StructureTypePhysicalDevicePrimitiveTopologyListRestartFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE
                    StructureTypePhysicalDevicePrivateDataFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE
                    StructureTypePhysicalDeviceProvokingVertexFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_RGBA_10_X_6_FORMATS_AVAILABLE
                    StructureTypePhysicalDeviceRGBA10x6FormatsFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_ARM_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_AVAILABLE
                    StructureTypePhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_QUERY_AVAILABLE
                    StructureTypePhysicalDeviceRayQueryFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE
                    StructureTypePhysicalDeviceRayTracingMotionBlurFeaturesNVidia,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
                    StructureTypePhysicalDeviceRayTracingPipelineFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_REPRESENTATIVE_FRAGMENT_TEST_AVAILABLE
                    StructureTypePhysicalDeviceRepresentativeFragmentTestFeaturesNVidia,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE
                    StructureTypePhysicalDeviceRobustnessFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_AVAILABLE
                    StructureTypePhysicalDeviceShaderAtomicFloatFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_2_AVAILABLE
                    StructureTypePhysicalDeviceShaderAtomicFloat2Features,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_CLOCK_AVAILABLE
                    StructureTypePhysicalDeviceShaderClockFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_DEMOTE_TO_HELPER_INVOCATION_AVAILABLE
                    StructureTypePhysicalDeviceShaderDemoteToHelperInvocationFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_IMAGE_ATOMIC_INT64_AVAILABLE
                    StructureTypePhysicalDeviceShaderImageAtomicInt64Features,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_IMAGE_FOOTPRINT_AVAILABLE
                    StructureTypePhysicalDeviceShaderImageFootprintFeaturesNVidia,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE
                    StructureTypePhysicalDeviceShaderSmBuiltinsFeaturesNVidia,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_SUBGROUP_UNIFORM_CONTROL_FLOW_AVAILABLE
                    StructureTypePhysicalDeviceShaderSubgroupUniformControlFlowFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_TERMINATE_INVOCATION_AVAILABLE
                    StructureTypePhysicalDeviceShaderTerminateInvocationFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE
                    StructureTypePhysicalDeviceShadingRateImageFeaturesNVidia,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE
                    StructureTypePhysicalDeviceSubgroupSizeControlFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE
                    StructureTypePhysicalDeviceSubpassShadingFeaturesHuawei,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
                    StructureTypePhysicalDeviceSynchronizationFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE
                    StructureTypePhysicalDeviceTexelBufferAlignmentFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXTURE_COMPRESSION_ASTC_HDR_AVAILABLE
                    StructureTypePhysicalDeviceTextureCompressionASTCHDRFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE
                    StructureTypePhysicalDeviceTransformFeedbackFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE
                    StructureTypePhysicalDeviceVertexAttributeDivisorFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_INPUT_DYNAMIC_STATE_AVAILABLE
                    StructureTypePhysicalDeviceVertexInputDynamicStateFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE
                    StructureTypePhysicalDeviceShaderIntegerDotProductFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_SHADER_INTEGER_FUNCTIONS_AVAILABLE
                    StructureTypePhysicalDeviceShaderIntegerFunctionsFeaturesIntel,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_AVAILABLE
                    StructureTypePhysicalDeviceWorkgroupMemoryExplicitLayoutFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_2_PLANE_444_FORMATS_AVAILABLE
                    StructureTypePhysicalDeviceYCBCR2Plane444FormatsFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_IMAGE_ARRAYS_AVAILABLE
                    StructureTypePhysicalDeviceYCBCRImageArraysFeatures,
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ZERO_INITIALIZE_WORKGROUP_MEMORY_AVAILABLE
                    StructureTypePhysicalDeviceZeroInitializeWorkgroupMemoryFeatures,
#endif

            };

            if ( pCreateInfo->structureType != StructureTypeDeviceCreateInfo ) {
                reportError ( "VUID-VkDeviceCreateInfo-sType-sType: "
                              "sType must be VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO" );

                return false;
            }

            cds :: HashSet < __C_ENG_TYPE ( StructureType ) > occurrences;

            auto chainElement = reinterpret_cast < __C_ENG_TYPE ( GenericInStructure ) const * > ( pCreateInfo->pNext );
            while ( chainElement != nullptr ) {
                bool validStructureType = false;
                for ( auto type : acceptedStructureTypesInChain ) {
                    if ( chainElement->structureType == type ) {
                        validStructureType = true;
                        break;
                    }
                }

                if ( ! validStructureType ) {
                    reportError ( "VUID-VkDeviceCreateInfo-pNext-pNext: "
                                  "Each pNext member of any structure (including this one) "
                                  "in the pNext chain must be either NULL or a pointer to a valid instance of "
                                  "VkDeviceDeviceMemoryReportCreateInfoEXT, VkDeviceDiagnosticsConfigCreateInfoNV, "
                                  "VkDeviceGroupDeviceCreateInfo, VkDeviceMemoryOverallocationCreateInfoAMD, "
                                  "VkDevicePrivateDataCreateInfoEXT, VkPhysicalDevice16BitStorageFeatures, "
                                  "VkPhysicalDevice4444FormatsFeaturesEXT, VkPhysicalDevice8BitStorageFeatures, "
                                  "VkPhysicalDeviceASTCDecodeFeaturesEXT, VkPhysicalDeviceAccelerationStructureFeaturesKHR, "
                                  "VkPhysicalDeviceBlendOperationAdvancedFeaturesEXT, VkPhysicalDeviceBorderColorSwizzleFeaturesEXT, "
                                  "VkPhysicalDeviceBufferDeviceAddressFeatures, VkPhysicalDeviceBufferDeviceAddressFeaturesEXT, "
                                  "VkPhysicalDeviceCoherentMemoryFeaturesAMD, VkPhysicalDeviceColorWriteEnableFeaturesEXT, "
                                  "VkPhysicalDeviceComputeShaderDerivativesFeaturesNV, VkPhysicalDeviceConditionalRenderingFeaturesEXT, "
                                  "VkPhysicalDeviceCooperativeMatrixFeaturesNV, VkPhysicalDeviceCornerSampledImageFeaturesNV, "
                                  "VkPhysicalDeviceCoverageReductionModeFeaturesNV, VkPhysicalDeviceCustomBorderColorFeaturesEXT, "
                                  "VkPhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV, VkPhysicalDeviceDepthClipControlFeaturesEXT, "
                                  "VkPhysicalDeviceDepthClipEnableFeaturesEXT, VkPhysicalDeviceDescriptorIndexingFeatures, "
                                  "VkPhysicalDeviceDeviceGeneratedCommandsFeaturesNV, VkPhysicalDeviceDeviceMemoryReportFeaturesEXT, "
                                  "VkPhysicalDeviceDiagnosticsConfigFeaturesNV, VkPhysicalDeviceDynamicRenderingFeaturesKHR, "
                                  "VkPhysicalDeviceExclusiveScissorFeaturesNV, VkPhysicalDeviceExtendedDynamicState2FeaturesEXT, "
                                  "VkPhysicalDeviceExtendedDynamicStateFeaturesEXT, VkPhysicalDeviceExternalMemoryRDMAFeaturesNV, "
                                  "VkPhysicalDeviceFeatures2, VkPhysicalDeviceFragmentDensityMap2FeaturesEXT, "
                                  "VkPhysicalDeviceFragmentDensityMapFeaturesEXT, VkPhysicalDeviceFragmentDensityMapOffsetFeaturesQCOM, "
                                  "VkPhysicalDeviceFragmentShaderBarycentricFeaturesNV, VkPhysicalDeviceFragmentShaderInterlockFeaturesEXT, "
                                  "VkPhysicalDeviceFragmentShadingRateEnumsFeaturesNV, VkPhysicalDeviceFragmentShadingRateFeaturesKHR, "
                                  "VkPhysicalDeviceGlobalPriorityQueryFeaturesEXT, VkPhysicalDeviceHostQueryResetFeatures, "
                                  "VkPhysicalDeviceImageRobustnessFeaturesEXT, VkPhysicalDeviceImageViewMinLodFeaturesEXT, "
                                  "VkPhysicalDeviceImagelessFramebufferFeatures, VkPhysicalDeviceIndexTypeUint8FeaturesEXT, "
                                  "VkPhysicalDeviceInheritedViewportScissorFeaturesNV, VkPhysicalDeviceInlineUniformBlockFeaturesEXT, "
                                  "VkPhysicalDeviceInvocationMaskFeaturesHUAWEI, VkPhysicalDeviceLineRasterizationFeaturesEXT, "
                                  "VkPhysicalDeviceLinearColorAttachmentFeaturesNV, VkPhysicalDeviceMaintenance4FeaturesKHR, "
                                  "VkPhysicalDeviceMemoryPriorityFeaturesEXT, VkPhysicalDeviceMeshShaderFeaturesNV, "
                                  "VkPhysicalDeviceMultiDrawFeaturesEXT, VkPhysicalDeviceMultiviewFeatures, "
                                  "VkPhysicalDeviceMutableDescriptorTypeFeaturesVALVE, VkPhysicalDevicePageableDeviceLocalMemoryFeaturesEXT, "
                                  "VkPhysicalDevicePerformanceQueryFeaturesKHR, VkPhysicalDevicePipelineCreationCacheControlFeaturesEXT, "
                                  "VkPhysicalDevicePipelineExecutablePropertiesFeaturesKHR, VkPhysicalDevicePortabilitySubsetFeaturesKHR, "
                                  "VkPhysicalDevicePresentIdFeaturesKHR, VkPhysicalDevicePresentWaitFeaturesKHR, "
                                  "VkPhysicalDevicePrimitiveTopologyListRestartFeaturesEXT, VkPhysicalDevicePrivateDataFeaturesEXT, "
                                  "VkPhysicalDeviceProtectedMemoryFeatures, VkPhysicalDeviceProvokingVertexFeaturesEXT, "
                                  "VkPhysicalDeviceRGBA10X6FormatsFeaturesEXT, VkPhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM, "
                                  "VkPhysicalDeviceRayQueryFeaturesKHR, VkPhysicalDeviceRayTracingMotionBlurFeaturesNV, "
                                  "VkPhysicalDeviceRayTracingPipelineFeaturesKHR, VkPhysicalDeviceRepresentativeFragmentTestFeaturesNV, "
                                  "VkPhysicalDeviceRobustness2FeaturesEXT, VkPhysicalDeviceSamplerYcbcrConversionFeatures, "
                                  "VkPhysicalDeviceScalarBlockLayoutFeatures, VkPhysicalDeviceSeparateDepthStencilLayoutsFeatures, "
                                  "VkPhysicalDeviceShaderAtomicFloat2FeaturesEXT, VkPhysicalDeviceShaderAtomicFloatFeaturesEXT, "
                                  "VkPhysicalDeviceShaderAtomicInt64Features, VkPhysicalDeviceShaderClockFeaturesKHR, "
                                  "VkPhysicalDeviceShaderDemoteToHelperInvocationFeaturesEXT, VkPhysicalDeviceShaderDrawParametersFeatures, "
                                  "VkPhysicalDeviceShaderFloat16Int8Features, VkPhysicalDeviceShaderImageAtomicInt64FeaturesEXT, "
                                  "VkPhysicalDeviceShaderImageFootprintFeaturesNV, VkPhysicalDeviceShaderIntegerDotProductFeaturesKHR, "
                                  "VkPhysicalDeviceShaderIntegerFunctions2FeaturesINTEL, VkPhysicalDeviceShaderSMBuiltinsFeaturesNV, "
                                  "VkPhysicalDeviceShaderSubgroupExtendedTypesFeatures, VkPhysicalDeviceShaderSubgroupUniformControlFlowFeaturesKHR, "
                                  "VkPhysicalDeviceShaderTerminateInvocationFeaturesKHR, VkPhysicalDeviceShadingRateImageFeaturesNV, "
                                  "VkPhysicalDeviceSubgroupSizeControlFeaturesEXT, VkPhysicalDeviceSubpassShadingFeaturesHUAWEI, "
                                  "VkPhysicalDeviceSynchronization2FeaturesKHR, VkPhysicalDeviceTexelBufferAlignmentFeaturesEXT, "
                                  "VkPhysicalDeviceTextureCompressionASTCHDRFeaturesEXT, VkPhysicalDeviceTimelineSemaphoreFeatures, "
                                  "VkPhysicalDeviceTransformFeedbackFeaturesEXT, VkPhysicalDeviceUniformBufferStandardLayoutFeatures, "
                                  "VkPhysicalDeviceVariablePointersFeatures, VkPhysicalDeviceVertexAttributeDivisorFeaturesEXT, "
                                  "VkPhysicalDeviceVertexInputDynamicStateFeaturesEXT, VkPhysicalDeviceVulkan11Features, "
                                  "VkPhysicalDeviceVulkan12Features, VkPhysicalDeviceVulkanMemoryModelFeatures, "
                                  "VkPhysicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR, VkPhysicalDeviceYcbcr2Plane444FormatsFeaturesEXT, "
                                  "VkPhysicalDeviceYcbcrImageArraysFeaturesEXT, or VkPhysicalDeviceZeroInitializeWorkgroupMemoryFeaturesKHR" );

                    return false;
                }

                if (
                        occurrences.contains ( chainElement->structureType ) &&
                        chainElement->structureType != StructureTypeDeviceDeviceMemoryReportCreateInfo &&
                        chainElement->structureType != StructureTypeDevicePrivateDataCreateInfo
                ) {
                    reportError ( "VUID-VkDeviceCreateInfo-sType-unique: "
                                  "The sType value of each struct in the pNext chain must be unique, "
                                  "with the exception of structures of type VkDeviceDeviceMemoryReportCreateInfoEXT or "
                                  "VkDevicePrivateDataCreateInfoEXT" );

                    return false;
                }

                occurrences.insert ( chainElement->structureType );

                chainElement = reinterpret_cast < __C_ENG_TYPE ( GenericInStructure ) const * > ( chainElement->pNext );
            }

            if ( pCreateInfo->flags != 0U ) {
                reportError ("VUID-VkDeviceCreateInfo-flags-zerobitmask: "
                             "flags must be 0");

                return false;
            }

            if ( pCreateInfo->pQueueCreateInfos == nullptr ) {
                reportError ( "VUID-VkDeviceCreateInfo-pQueueCreateInfos-parameter: "
                              "pQueueCreateInfos must be a valid pointer to an array of "
                              "queueCreateInfoCount valid VkDeviceQueueCreateInfo structures" );

                return false;
            }

            if ( pCreateInfo->enabledExtensionCount != 0U && pCreateInfo->pEnabledExtensionNames == nullptr ) {
                reportError ( "VUID-VkDeviceCreateInfo-ppEnabledExtensionNames-parameter: "
                              "If enabledExtensionCount is not 0, ppEnabledExtensionNames must "
                              "be a valid pointer to an array of ppEnabledExtensionNames null-terminated UTF-8 strings" );

                return false;
            }

            if ( pCreateInfo->queueCreateInfoCount == 0U ) {
                reportError ( "VUID-VkDeviceCreateInfo-queueCreateInfoCount-arraylength: "
                              "queueCreateInfoCount must be greater than 0" );

                return false;
            }

            return true;
        }

        static inline auto validate (
                __C_ENG_TYPE ( DeviceCreateInfo ) const * pCreateInfo
        ) noexcept -> bool {

            using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
            using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

#ifdef NDEBUG
            return true;
#endif

            struct QueueInfoWithProtected {
                uint32  index;
                bool    protectedExists;
            };

            QueueInfoWithProtected queueValidationArray [ 128U ];
            uint32 queueValidationElementCount = 0U;

            for ( uint32 i = 0U; i < pCreateInfo->queueCreateInfoCount; ++ i ) {
                auto pQueueCreateInfo = & pCreateInfo->pQueueCreateInfos[i];

                for ( uint32 j = 0U; j < queueValidationElementCount; ++ j ) {
                    if ( queueValidationArray[j].index == pQueueCreateInfo->queueFamilyIndex ) {
                        if (
                                (
                                        queueValidationArray[j].protectedExists &&
                                        ( pQueueCreateInfo->flags & static_cast < uint32 > ( vulkan :: __C_ENG_TYPE ( DeviceQueueCreateFlag ) :: DeviceQueueCreateFlagProtected ) ) != 0U
                                ) || (
                                        ! queueValidationArray[j].protectedExists &&
                                        ( pQueueCreateInfo->flags & static_cast < uint32 > ( vulkan :: __C_ENG_TYPE ( DeviceQueueCreateFlag ) :: DeviceQueueCreateFlagProtected ) ) == 0U
                                )
                        ) {
                            reportError("VUID-VkDeviceCreateInfo-queueFamilyIndex-02802: "
                                        "The queueFamilyIndex member of each element of pQueueCreateInfos "
                                        "must be unique within pQueueCreateInfos, "
                                        "except that two members can share the same queueFamilyIndex if one is a protected-capable queue "
                                        "and one is not a protected-capable queue");

                            return false;
                        } else {
                            continue;
                        }
                    }

                    queueValidationArray [ queueValidationElementCount ++ ] = ( QueueInfoWithProtected ) {
                        .index = pQueueCreateInfo->queueFamilyIndex,
                        .protectedExists = ( pQueueCreateInfo->flags & static_cast < uint32 > ( vulkan :: __C_ENG_TYPE ( DeviceQueueCreateFlag ) :: DeviceQueueCreateFlagProtected ) ) != 0U
                    };
                }
            }

            bool negativeViewportAMDPresent = false;
            bool bufferDeviceAddressKHRPresent = false;
            bool bufferDeviceAddressEXTPresent = false;

            bool shaderDrawParametersKHRPresent = false;
            bool drawIndirectCountKHRPresent = false;
            bool samplerMirrorClampToEdgeKHRPresent = false;
            bool descriptorIndexingEXTPresent = false;
            bool samplerFilterMinmaxEXTPresent = false;
            bool shaderViewportIndexLayerEXTPresent = false;
            bool portabilitySubsetKHRPresent = false;

            for ( uint32 i = 0U; i < pCreateInfo->enabledExtensionCount; ++ i ) {
                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], "VK_AMD_negative_viewport_height" ) == 0 ) {
                    negativeViewportAMDPresent = true;
                }

                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], "VK_KHR_buffer_device_address" ) == 0 ) {
                    bufferDeviceAddressKHRPresent = true;
                }

                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], "VK_EXT_buffer_device_address" ) == 0 ) {
                    bufferDeviceAddressEXTPresent = true;
                }

                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], "VK_KHR_shader_draw_parameters" ) == 0 ) {
                    shaderDrawParametersKHRPresent = true;
                }

                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], "VK_KHR_draw_indirect_count" ) == 0 ) {
                    drawIndirectCountKHRPresent = true;
                }

                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], "VK_KHR_sampler_mirror_clamp_to_edge" ) == 0 ) {
                    samplerMirrorClampToEdgeKHRPresent = true;
                }

                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], "VK_EXT_descriptor_indexing" ) == 0 ) {
                    descriptorIndexingEXTPresent = true;
                }

                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], "VK_EXT_sampler_filter_minmax" ) == 0 ) {
                    samplerFilterMinmaxEXTPresent = true;
                }

                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], "VK_EXT_shader_viewport_index_layer" ) == 0 ) {
                    shaderViewportIndexLayerEXTPresent = true;
                }

                if ( std :: strcmp ( pCreateInfo->pEnabledExtensionNames[i], "VK_KHR_portability_subset" ) == 0 ) {
                    portabilitySubsetKHRPresent = true;
                }
            }

            bool featuresPresent = pCreateInfo->pEnabledFeatures != nullptr;
            bool extendedFeaturesPresent = false;

            bool vulkan11FeaturesPresent = false;
            bool vulkan11FeaturesShaderDrawParameters = false;


            bool vulkan12FeaturesPresent = false;
            bool vulkan12FeaturesBufferDeviceAddress = false;
            bool vulkan12FeaturesDrawIndirectCount = false;
            bool vulkan12FeaturesSamplerMirrorClampToEdge = false;
            bool vulkan12FeaturesDescriptorIndexing = false;
            bool vulkan12FeaturesSamplerFilterMinmax = false;
            bool vulkan12FeaturesShaderOutputViewportLayer = false;
            bool vulkan12FeaturesShaderOutputLayer = false;

            bool device16BitStorageFeaturesPresent = false;
            bool deviceMultiviewFeaturesPresent = false;
            bool deviceVariablePointersFeaturesPresent = false;
            bool deviceProtectedMemoryFeaturesPresent = false;
            bool deviceSamplerYCBCRConversionFeaturesPresent = false;
            bool deviceShaderDrawParametersFeaturesPresent = false;

            bool device8BitStorageFeaturesPresent = false;
            bool deviceShaderAtomicInt64FeaturesPresent = false;
            bool deviceShaderFloat16Int8FeaturesPresent = false;
            bool deviceDescriptorIndexingFeaturesPresent = false;
            bool deviceScalarBlockFeaturesPresent = false;
            bool deviceImagelessFramebufferFeaturesPresent = false;
            bool deviceUniformBufferStandardLayoutFeaturesPresent = false;
            bool deviceShaderSubgroupExtendedTypesFeaturesPresent = false;
            bool deviceSeparateDepthStencilLayoutsFeaturesPresent = false;
            bool deviceHostQueryResetFeaturesPresent = false;
            bool deviceTimelineSemaphoreFeaturesPresent = false;
            bool deviceBufferDeviceAddressFeaturesPresent = false;
            bool deviceVulkanMemoryModelFeaturesPresent = false;

            bool shadingRateImage = false;
            bool fragmentDensityMap = false;
            bool pipelineFragmentShadingRate = false;
            bool primitiveFragmentShadingRate = false;
            bool attachmentFragmentShadingRate = false;

            bool sparseImageInt64Atomics = false;
            bool shaderImageInt64Atomics = false;

            bool sparseImageFloat32Atomics = false;
            bool shaderImageFloat32Atomics = false;

            bool sparseImageFloat32AtomicsAdd = false;
            bool shaderImageFloat32AtomicsAdd = false;

            bool sparseImageFloat32AtomicsMinMax = false;
            bool shaderImageFloat32AtomicsMinMax = false;

            auto chainElement = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericInStructure ) const * > ( pCreateInfo->pNext );
            while ( chainElement != nullptr ) {

                if ( chainElement->structureType == vulkan :: StructureTypePhysicalDeviceFeatures ) {
                    extendedFeaturesPresent = true;
                }

                if ( chainElement->structureType == vulkan :: StructureTypePhysicalDeviceVulkan_1_1_Features ) {
                    vulkan11FeaturesPresent = true;

                    auto vulkan11Features = reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceVulkan11Features ) const * > ( chainElement );
                    vulkan11FeaturesShaderDrawParameters = vulkan11Features->shaderDrawParameters == VK_TRUE;
                }

                if ( chainElement->structureType == vulkan :: StructureTypePhysicalDeviceVulkan_1_2_Features ) {
                    vulkan12FeaturesPresent = true;

                    auto vulkan12Features = reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceVulkan12Features ) const * > ( chainElement );
                    vulkan12FeaturesBufferDeviceAddress         = vulkan12Features->bufferDeviceAddress == VK_TRUE;
                    vulkan12FeaturesDrawIndirectCount           = vulkan12Features->drawIndirectCount == VK_TRUE;
                    vulkan12FeaturesSamplerMirrorClampToEdge    = vulkan12Features->drawIndirectCount == VK_TRUE;
                    vulkan12FeaturesDescriptorIndexing          = vulkan12Features->drawIndirectCount == VK_TRUE;
                    vulkan12FeaturesSamplerFilterMinmax         = vulkan12Features->drawIndirectCount == VK_TRUE;
                    vulkan12FeaturesShaderOutputViewportLayer   = vulkan12Features->drawIndirectCount == VK_TRUE;
                    vulkan12FeaturesShaderOutputLayer           = vulkan12Features->drawIndirectCount == VK_TRUE;
                }

                if ( chainElement->structureType == vulkan :: StructureTypePhysicalDevice16BitStorageFeatures ) {
                    device16BitStorageFeaturesPresent = true;
                }

                if ( chainElement->structureType == vulkan :: StructureTypePhysicalDeviceMultiviewFeatures ) {
                    deviceMultiviewFeaturesPresent = true;
                }

                if ( chainElement->structureType == vulkan :: StructureTypePhysicalDeviceVariablePointersFeatures ) {
                    deviceVariablePointersFeaturesPresent = true;
                }

                if ( chainElement->structureType == vulkan :: StructureTypePhysicalDeviceProtectedMemoryFeatures ) {
                    deviceProtectedMemoryFeaturesPresent = true;
                }

                if ( chainElement->structureType == vulkan :: StructureTypePhysicalDeviceSamplerYCBCRConversionFeatures ) {
                    deviceSamplerYCBCRConversionFeaturesPresent = true;
                }

                if ( chainElement->structureType == vulkan :: StructureTypePhysicalDeviceShaderDrawParametersFeatures) {
                    deviceShaderDrawParametersFeaturesPresent = true;
                }

                if ( chainElement->structureType == vulkan :: StructureTypePhysicalDevice8BitStorageFeatures ) {
                    device8BitStorageFeaturesPresent = true;
                }

                if ( chainElement->structureType == vulkan :: StructureTypePhysicalDeviceShaderAtomicInt64Features ) {
                    deviceShaderAtomicInt64FeaturesPresent = true;
                }

                if ( chainElement->structureType == vulkan :: StructureTypePhysicalDeviceShaderFloat16Int8Features ) {
                    deviceShaderFloat16Int8FeaturesPresent = true;
                }

                if ( chainElement->structureType == vulkan :: StructureTypePhysicalDeviceDescriptorIndexingFeatures ) {
                    deviceDescriptorIndexingFeaturesPresent = true;
                }

                if ( chainElement->structureType == vulkan :: StructureTypePhysicalDeviceScalarBlockLayoutFeatures ) {
                    deviceScalarBlockFeaturesPresent = true;
                }

                if ( chainElement->structureType == vulkan :: StructureTypePhysicalDeviceImagelessFramebufferFeatures ) {
                    deviceImagelessFramebufferFeaturesPresent = true;
                }

                if ( chainElement->structureType == vulkan :: StructureTypePhysicalDeviceUniformBufferStandardLayoutFeatures ) {
                    deviceUniformBufferStandardLayoutFeaturesPresent = true;
                }

                if ( chainElement->structureType == vulkan :: StructureTypePhysicalDeviceShaderSubgroupExtendedTypesFeatures ) {
                    deviceShaderSubgroupExtendedTypesFeaturesPresent = true;
                }

                if ( chainElement->structureType == vulkan :: StructureTypePhysicalDeviceSeparateDepthStencilLayoutsFeatures ) {
                    deviceSeparateDepthStencilLayoutsFeaturesPresent = true;
                }

                if ( chainElement->structureType == vulkan :: StructureTypePhysicalDeviceHostQueryResetFeatures ) {
                    deviceHostQueryResetFeaturesPresent = true;
                }

                if ( chainElement->structureType == vulkan :: StructureTypePhysicalDeviceTimelineSemaphoreFeatures ) {
                    deviceTimelineSemaphoreFeaturesPresent = true;
                }

                if ( chainElement->structureType == vulkan :: StructureTypePhysicalDeviceBufferDeviceAddressFeatures ) {
                    deviceBufferDeviceAddressFeaturesPresent = true;
                }

                if ( chainElement->structureType == vulkan :: StructureTypePhysicalDeviceVulkanMemoryModelFeatures ) {
                    deviceVulkanMemoryModelFeaturesPresent = true;
                }

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE

                if ( chainElement->structureType == vulkan :: StructureTypePhysicalDeviceShadingRateImageFeaturesNVidia ) {
                    auto shadingRateFeatures = reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceShadingRateImageFeaturesNVidia ) const * > ( chainElement );

                    shadingRateImage = shadingRateFeatures->shadingRateImage == VK_TRUE;
                }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE

                if ( chainElement->structureType == vulkan :: StructureTypePhysicalDeviceFragmentShadingRateFeatures ) {
                    auto fragmentShadingFeatures = reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceFragmentShadingRateFeatures ) const * > ( chainElement );

                    pipelineFragmentShadingRate     = fragmentShadingFeatures->pipelineFragmentShadingRate      == VK_TRUE;
                    primitiveFragmentShadingRate    = fragmentShadingFeatures->primitiveFragmentShadingRate     == VK_TRUE;
                    attachmentFragmentShadingRate   = fragmentShadingFeatures->attachmentFragmentShadingRate    == VK_TRUE;
                }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

                if ( chainElement->structureType == vulkan :: StructureTypePhysicalDeviceFragmentDensityMapFeatures ) {
                    auto fragmentDensityFeatures = reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMapFeatures ) const * > ( chainElement );

                    fragmentDensityMap = fragmentDensityFeatures->fragmentDensityMap == VK_TRUE;
                }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_IMAGE_ATOMIC_INT64_AVAILABLE

                if ( chainElement->structureType == vulkan :: StructureTypePhysicalDeviceShaderImageAtomicInt64Features ) {
                    auto shaderImageFeatures = reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceShaderImageAtomicInt64Features ) const * > ( chainElement );

                    shaderImageInt64Atomics = shaderImageFeatures->shaderImageInt64Atomics == VK_TRUE;
                    sparseImageInt64Atomics = shaderImageFeatures->sparseImageInt64Atomics == VK_TRUE;
                }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_AVAILABLE

                if ( chainElement->structureType == vulkan :: StructureTypePhysicalDeviceShaderAtomicFloatFeatures ) {
                    auto shaderImageFeatures = reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceShaderAtomicFloatFeatures ) const * > ( chainElement );

                    shaderImageFloat32Atomics       = shaderImageFeatures->shaderImageFloat32Atomics    == VK_TRUE;
                    shaderImageFloat32AtomicsAdd    = shaderImageFeatures->shaderImageFloat32AtomicAdd  == VK_TRUE;
                    sparseImageFloat32Atomics       = shaderImageFeatures->sparseImageFloat32Atomics    == VK_TRUE;
                    sparseImageFloat32AtomicsAdd    = shaderImageFeatures->sparseImageFloat32AtomicAdd  == VK_TRUE;
                }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_2_AVAILABLE

                if ( chainElement->structureType == vulkan :: StructureTypePhysicalDeviceShaderAtomicFloat2Features ) {
                    auto shaderImageFeatures = reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceShaderAtomicFloat2Features ) const * > ( chainElement );

                    shaderImageFloat32AtomicsMinMax     = shaderImageFeatures->shaderImageFloat32AtomicMinMax  == VK_TRUE;
                    sparseImageFloat32AtomicsMinMax     = shaderImageFeatures->sparseImageFloat32AtomicMinMax  == VK_TRUE;
                }

#endif

                chainElement = chainElement->pNext;
            }

            if ( extendedFeaturesPresent && featuresPresent ) {
                reportError ( "VUID-VkDeviceCreateInfo-pNext-00373: "
                              "If the pNext chain includes a VkPhysicalDeviceFeatures2 structure, "
                              "then pEnabledFeatures must be NULL" );

                return false;
            }

            if ( negativeViewportAMDPresent ) {
                reportError ( "VUID-VkDeviceCreateInfo-ppEnabledExtensionNames-01840: "
                              "ppEnabledExtensionNames must not contain VK_AMD_negative_viewport_height" );

                return false;
            }

            if ( vulkan12FeaturesBufferDeviceAddress && bufferDeviceAddressEXTPresent ) {
                reportError ( "VUID-VkDeviceCreateInfo-pNext-04748: "
                              "if the pNext chain includes a VkPhysicalDeviceVulkan12Features structure and "
                              "VkPhysicalDeviceVulkan12Features::bufferDeviceAddress is VK_TRUE, ppEnabledExtensionNames "
                              "must not contain VK_EXT_buffer_device_address" );

                return false;
            }

            if (
                    vulkan11FeaturesPresent && (
                        device16BitStorageFeaturesPresent           ||
                        deviceMultiviewFeaturesPresent              ||
                        deviceVariablePointersFeaturesPresent       ||
                        deviceProtectedMemoryFeaturesPresent        ||
                        deviceSamplerYCBCRConversionFeaturesPresent ||
                        deviceShaderDrawParametersFeaturesPresent
                   )
            ) {
                reportError("VUID-VkDeviceCreateInfo-pNext-02829: "
                            "If the pNext chain includes a VkPhysicalDeviceVulkan11Features structure, "
                            "then it must not include a "
                            "VkPhysicalDevice16BitStorageFeatures, "
                            "VkPhysicalDeviceMultiviewFeatures, "
                            "VkPhysicalDeviceVariablePointersFeatures, "
                            "VkPhysicalDeviceProtectedMemoryFeatures, "
                            "VkPhysicalDeviceSamplerYcbcrConversionFeatures, or "
                            "VkPhysicalDeviceShaderDrawParametersFeatures structure");

                return false;
            }

            if (
                    vulkan12FeaturesPresent && (
                            device8BitStorageFeaturesPresent                    ||
                            deviceShaderAtomicInt64FeaturesPresent              ||
                            deviceShaderFloat16Int8FeaturesPresent              ||
                            deviceDescriptorIndexingFeaturesPresent             ||
                            deviceScalarBlockFeaturesPresent                    ||
                            deviceImagelessFramebufferFeaturesPresent           ||
                            deviceUniformBufferStandardLayoutFeaturesPresent    ||
                            deviceShaderSubgroupExtendedTypesFeaturesPresent    ||
                            deviceSeparateDepthStencilLayoutsFeaturesPresent    ||
                            deviceHostQueryResetFeaturesPresent                 ||
                            deviceTimelineSemaphoreFeaturesPresent              ||
                            deviceBufferDeviceAddressFeaturesPresent            ||
                            deviceVulkanMemoryModelFeaturesPresent
                    )
            ) {
                reportError ( "VUID-VkDeviceCreateInfo-pNext-02830: "
                              "If the pNext chain includes a VkPhysicalDeviceVulkan12Features structure, "
                              "then it must not include a "
                              "VkPhysicalDevice8BitStorageFeatures, "
                              "VkPhysicalDeviceShaderAtomicInt64Features, "
                              "VkPhysicalDeviceShaderFloat16Int8Features, "
                              "VkPhysicalDeviceDescriptorIndexingFeatures, "
                              "VkPhysicalDeviceScalarBlockLayoutFeatures, "
                              "VkPhysicalDeviceImagelessFramebufferFeatures, "
                              "VkPhysicalDeviceUniformBufferStandardLayoutFeatures, "
                              "VkPhysicalDeviceShaderSubgroupExtendedTypesFeatures, "
                              "VkPhysicalDeviceSeparateDepthStencilLayoutsFeatures, "
                              "VkPhysicalDeviceHostQueryResetFeatures, "
                              "VkPhysicalDeviceTimelineSemaphoreFeatures, "
                              "VkPhysicalDeviceBufferDeviceAddressFeatures, or "
                              "VkPhysicalDeviceVulkanMemoryModelFeatures structure" );

                return false;
            }

            if ( bufferDeviceAddressKHRPresent && bufferDeviceAddressEXTPresent ) {
                reportError("VUID-VkDeviceCreateInfo-ppEnabledExtensionNames-03328: "
                            "ppEnabledExtensionNames must not contain both "
                            "VK_KHR_buffer_device_address and VK_EXT_buffer_device_address");

                return false;
            }

            if ( shaderDrawParametersKHRPresent && vulkan11FeaturesPresent && ! vulkan11FeaturesShaderDrawParameters ) {
                reportError ( "VUID-VkDeviceCreateInfo-ppEnabledExtensionNames-02831: "
                              "If ppEnabledExtensionNames contains \"VK_KHR_draw_indirect_count\" "
                              "and the pNext chain includes a VkPhysicalDeviceVulkan12Features structure, "
                              "then VkPhysicalDeviceVulkan12Features::drawIndirectCount must be VK_TRUE" );

                return false;
            }

            if ( drawIndirectCountKHRPresent && vulkan12FeaturesPresent && ! vulkan12FeaturesDrawIndirectCount ) {
                reportError ( "VUID-VkDeviceCreateInfo-ppEnabledExtensionNames-04476: "
                              "If ppEnabledExtensionNames contains \"VK_KHR_shader_draw_parameters\" and the pNext chain includes a "
                              "VkPhysicalDeviceVulkan11Features structure, then VkPhysicalDeviceVulkan11Features::shaderDrawParameters must be VK_TRUE" );

                return false;
            }

            if ( samplerMirrorClampToEdgeKHRPresent && vulkan12FeaturesPresent && ! vulkan12FeaturesSamplerMirrorClampToEdge ) {
                reportError ( "VUID-VkDeviceCreateInfo-ppEnabledExtensionNames-02832: "
                              "If ppEnabledExtensionNames contains \"VK_KHR_sampler_mirror_clamp_to_edge\" and "
                              "the pNext chain includes a VkPhysicalDeviceVulkan12Features structure, "
                              "then VkPhysicalDeviceVulkan12Features::samplerMirrorClampToEdge must be VK_TRUE" );

                return false;
            }

            if ( descriptorIndexingEXTPresent && vulkan12FeaturesPresent && ! vulkan12FeaturesDescriptorIndexing ) {
                reportError ( "VUID-VkDeviceCreateInfo-ppEnabledExtensionNames-02833: "
                              "If ppEnabledExtensionNames contains \"VK_EXT_descriptor_indexing\" "
                              "and the pNext chain includes a VkPhysicalDeviceVulkan12Features structure, "
                              "then VkPhysicalDeviceVulkan12Features::descriptorIndexing must be VK_TRUE" );

                return false;
            }

            if ( samplerFilterMinmaxEXTPresent && vulkan12FeaturesPresent && ! vulkan12FeaturesSamplerFilterMinmax ) {
                reportError ( "VUID-VkDeviceCreateInfo-ppEnabledExtensionNames-02834: "
                              "If ppEnabledExtensionNames contains \"VK_EXT_sampler_filter_minmax\" "
                              "and the pNext chain includes a VkPhysicalDeviceVulkan12Features structure, "
                              "then VkPhysicalDeviceVulkan12Features::samplerFilterMinmax must be VK_TRUE" );

                return false;
            }

            if ( shaderViewportIndexLayerEXTPresent && vulkan12FeaturesPresent && ! ( vulkan12FeaturesShaderOutputLayer && vulkan12FeaturesShaderOutputViewportLayer ) ) {
                reportError ( "VUID-VkDeviceCreateInfo-ppEnabledExtensionNames-02835: "
                              "If ppEnabledExtensionNames contains \"VK_EXT_shader_viewport_index_layer\" "
                              "and the pNext chain includes a VkPhysicalDeviceVulkan12Features structure, "
                              "then VkPhysicalDeviceVulkan12Features::shaderOutputViewportIndex and "
                              "VkPhysicalDeviceVulkan12Features::shaderOutputLayer must both be VK_TRUE" );

                return false;
            }

            if ( hidden :: portabilitySubsetQueried && hidden :: portabilitySubsetExists && ! portabilitySubsetKHRPresent ) {
                reportError ( "VUID-VkDeviceCreateInfo-pProperties-04451: "
                              "If the VK_KHR_portability_subset extension is included in pProperties of vkEnumerateDeviceExtensionProperties, "
                              "ppEnabledExtensionNames must include \"VK_KHR_portability_subset\"" );

                return false;
            }

            if ( shadingRateImage && pipelineFragmentShadingRate ) {
                reportError ( "VUID-VkDeviceCreateInfo-shadingRateImage-04478: "
                              "If shadingRateImage is enabled, pipelineFragmentShadingRate must not be enabled" );

                return false;
            }

            if ( shadingRateImage && primitiveFragmentShadingRate ) {
                reportError ( "VUID-VkDeviceCreateInfo-shadingRateImage-04479: "
                              "If shadingRateImage is enabled, primitiveFragmentShadingRate must not be enabled" );

                return false;
            }

            if ( shadingRateImage && attachmentFragmentShadingRate ) {
                reportError ( "VUID-VkDeviceCreateInfo-shadingRateImage-04480: "
                              "If shadingRateImage is enabled, attachmentFragmentShadingRate must not be enabled" );

                return false;
            }

            if ( fragmentDensityMap && pipelineFragmentShadingRate ) {
                reportError ( "VUID-VkDeviceCreateInfo-fragmentDensityMap-04481: "
                              "If fragmentDensityMap is enabled, pipelineFragmentShadingRate must not be enabled" );

                return false;
            }

            if ( fragmentDensityMap && primitiveFragmentShadingRate ) {
                reportError ( "VUID-VkDeviceCreateInfo-fragmentDensityMap-04482: "
                              "If fragmentDensityMap is enabled, primitiveFragmentShadingRate must not be enabled" );

                return false;
            }

            if ( fragmentDensityMap && attachmentFragmentShadingRate ) {
                reportError ( "VUID-VkDeviceCreateInfo-fragmentDensityMap-04483: "
                              "If fragmentDensityMap is enabled, attachmentFragmentShadingRate must not be enabled" );

                return false;
            }

            if ( sparseImageInt64Atomics && ! shaderImageInt64Atomics ) {
                reportError ( "VUID-VkDeviceCreateInfo-None-04896: "
                              "If sparseImageInt64Atomics is enabled, shaderImageInt64Atomics must be enabled" );

                return false;
            }

            if ( sparseImageFloat32Atomics && ! shaderImageFloat32Atomics ) {
                reportError ( "VUID-VkDeviceCreateInfo-None-04897: "
                              "If sparseImageFloat32Atomics is enabled, shaderImageFloat32Atomics must be enabled" );

                return false;
            }

            if ( sparseImageFloat32AtomicsAdd && ! shaderImageFloat32AtomicsAdd ) {
                reportError ( "VUID-VkDeviceCreateInfo-None-04898: "
                              "If sparseImageFloat32AtomicAdd is enabled, shaderImageFloat32AtomicAdd must be enabled" );

                return false;
            }

            if ( sparseImageFloat32AtomicsMinMax && ! shaderImageFloat32AtomicsMinMax ) {
                reportError ( "VUID-VkDeviceCreateInfo-sparseImageFloat32AtomicMinMax-04975: "
                              "If sparseImageFloat32AtomicMinMax is enabled, shaderImageFloat32AtomicMinMax must be enabled" );

                return false;
            }

            return validateImplicit ( pCreateInfo );
        }

    }
}

#endif //__C_ENG_VULKAN_API_CALLS_VALID_USAGE_HPP__

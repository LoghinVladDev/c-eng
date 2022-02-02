//
// Created by loghin on 01.01.2022.
//

#include <VulkanCore.hpp>
#include <VulkanAPICalls.hpp>
#include <VulkanCoreConfig.hpp>
#include <VulkanAPICallsValidUsage.hpp>


#define __C_ENG_CREATE_FUNCTION_NAME(_fName) __C_ENG_VULKAN_CORE_FUNCTION_NAME_ ## _fName

#define __C_ENG_LOOKUP_VULKAN_FUNCTION(_handle, _fName)                     \
    if ( _handle == nullptr ) {                                             \
                                                                            \
        auto lResult = vulkan :: getFunctionAddress (                       \
                __C_ENG_CREATE_FUNCTION_NAME(_fName),                       \
                reinterpret_cast < FunctionHandleAddress > ( & _handle )    \
        );                                                                  \
                                                                            \
        if ( lResult != vulkan :: ResultSuccess ) {                         \
            return lResult;                                                 \
        }                                                                   \
    }

#define __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION(_instance, _handle, _fName) \
    if ( _handle == nullptr ) {                                             \
                                                                            \
        auto lResult = vulkan :: getInstanceFunctionAddress (               \
                _instance,                                                  \
                __C_ENG_CREATE_FUNCTION_NAME(_fName),                       \
                reinterpret_cast < FunctionHandleAddress > ( & _handle )    \
        );                                                                  \
                                                                            \
        if ( lResult != vulkan :: ResultSuccess ) {                         \
            return lResult;                                                 \
        }                                                                   \
    }

#define __C_ENG_LOOKUP_VULKAN_DEVICE_FUNCTION(_device, _handle, _fName)     \
    if ( _handle == nullptr ) {                                             \
                                                                            \
        auto lResult = vulkan :: getDeviceFunctionAddress (                 \
                _device,                                                    \
                __C_ENG_CREATE_FUNCTION_NAME(_fName),                       \
                reinterpret_cast < FunctionHandleAddress > ( & _handle )    \
        );                                                                  \
                                                                            \
        if ( lResult != vulkan :: ResultSuccess ) {                         \
            return lResult;                                                 \
        }                                                                   \
    }



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
static VkPhysicalDeviceProperties2                                      deviceExtendedProperties;
static VkPhysicalDeviceVulkan11Properties                               deviceVulkan11Properties;
static VkPhysicalDeviceIDProperties                                     deviceIDProperties;
static VkPhysicalDeviceMaintenance3Properties                           deviceMaintenance3Properties;
static VkPhysicalDeviceMultiviewProperties                              deviceMultiviewProperties;
static VkPhysicalDevicePointClippingProperties                          devicePointClippingProperties;
static VkPhysicalDeviceProtectedMemoryProperties                        deviceProtectedMemoryProperties;
static VkPhysicalDeviceSubgroupProperties                               deviceSubgroupProperties;

static VkPhysicalDeviceFeatures2                                        deviceExtendedFeatures;
static VkPhysicalDeviceVulkan11Features                                 deviceVulkan11Features;
static VkPhysicalDevice16BitStorageFeatures                             device16BitStorageFeatures;
static VkPhysicalDeviceMultiviewFeatures                                deviceMultiviewFeatures;
static VkPhysicalDeviceProtectedMemoryFeatures                          deviceProtectedMemoryFeatures;
static VkPhysicalDeviceSamplerYcbcrConversionFeatures                   deviceSamplerYCBCRConversionFeatures;
static VkPhysicalDeviceShaderDrawParametersFeatures                     deviceShaderDrawParametersFeatures;
static VkPhysicalDeviceVariablePointersFeatures                         deviceVariablePointersFeatures;
#endif

/**
 * ---------------------------------------------------------
 * ---------------------------------------------------------
 * -------- Vulkan 1.2 Device Properties & Features --------
 * ---------------------------------------------------------
 * ---------------------------------------------------------
 */
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
static VkPhysicalDeviceVulkan12Properties                               deviceVulkan12Properties;
static VkPhysicalDeviceDepthStencilResolveProperties                    deviceDepthStencilResolveProperties;
static VkPhysicalDeviceDescriptorIndexingProperties                     deviceDescriptorIndexingProperties;
static VkPhysicalDeviceDriverProperties                                 deviceDriverProperties;
static VkPhysicalDeviceFloatControlsProperties                          deviceFloatControlsProperties;
static VkPhysicalDeviceSamplerFilterMinmaxProperties                    deviceSamplerFilterMinmaxProperties;
static VkPhysicalDeviceTimelineSemaphoreProperties                      deviceTimelineSemaphoreProperties;

static VkPhysicalDeviceVulkan12Features                                 deviceVulkan12Features;
static VkPhysicalDevice8BitStorageFeatures                              device8BitStorageFeatures;
static VkPhysicalDeviceBufferDeviceAddressFeatures                      deviceBufferDeviceAddressFeatures;
static VkPhysicalDeviceDescriptorIndexingFeatures                       deviceDescriptorIndexingFeatures;
static VkPhysicalDeviceHostQueryResetFeatures                           deviceHostQueryResetFeatures;
static VkPhysicalDeviceImagelessFramebufferFeatures                     deviceImagelessFramebufferFeatures;
static VkPhysicalDeviceScalarBlockLayoutFeatures                        deviceScalarBlockLayoutFeatures;
static VkPhysicalDeviceSeparateDepthStencilLayoutsFeatures              deviceSeparateDepthStencilLayoutsFeatures;
static VkPhysicalDeviceShaderAtomicInt64Features                        deviceShaderAtomicInt64Features;
static VkPhysicalDeviceShaderFloat16Int8Features                        deviceShaderFloat16Int8Features;
static VkPhysicalDeviceShaderSubgroupExtendedTypesFeatures              deviceShaderSubgroupExtendedTypesFeatures;
static VkPhysicalDeviceTimelineSemaphoreFeatures                        deviceTimelineSemaphoreFeatures;
static VkPhysicalDeviceUniformBufferStandardLayoutFeatures              deviceUniformBufferStandardLayoutFeatures;
static VkPhysicalDeviceVulkanMemoryModelFeatures                        deviceVulkanMemoryModelFeatures;
#endif


#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDeviceShaderTerminateInvocationFeatures_t             = VkPhysicalDeviceShaderTerminateInvocationFeatures;
using VkPhysicalDeviceShaderDemoteToHelperInvocationFeatures_t        = VkPhysicalDeviceShaderDemoteToHelperInvocationFeatures;
using VkPhysicalDevicePrivateDataFeatures_t                           = VkPhysicalDevicePrivateDataFeatures;
using VkDevicePrivateDataCreateInfo_t                                 = VkDevicePrivateDataCreateInfo;
using VkPhysicalDevicePipelineCreationCacheControlFeatures_t          = VkPhysicalDevicePipelineCreationCacheControlFeatures;
using VkPhysicalDeviceSynchronization2Features_t                      = VkPhysicalDeviceSynchronization2Features;
using VkPhysicalDeviceZeroInitializeWorkgroupMemoryFeatures_t         = VkPhysicalDeviceZeroInitializeWorkgroupMemoryFeatures;
using VkPhysicalDeviceImageRobustnessFeatures_t                       = VkPhysicalDeviceImageRobustnessFeatures;
using VkPhysicalDeviceSubgroupSizeControlProperties_t                 = VkPhysicalDeviceSubgroupSizeControlProperties;
using VkPhysicalDeviceSubgroupSizeControlFeatures_t                   = VkPhysicalDeviceSubgroupSizeControlFeatures;
using VkPhysicalDeviceInlineUniformBlockProperties_t                  = VkPhysicalDeviceInlineUniformBlockProperties;
using VkPhysicalDeviceInlineUniformBlockFeatures_t                    = VkPhysicalDeviceInlineUniformBlockFeatures;
using VkPhysicalDeviceTextureCompressionASTCHDRFeatures_t             = VkPhysicalDeviceTextureCompressionASTCHDRFeatures;
using VkPhysicalDeviceDynamicRenderingFeatures_t                      = VkPhysicalDeviceDynamicRenderingFeatures;
using VkPhysicalDeviceShaderIntegerDotProductProperties_t             = VkPhysicalDeviceShaderIntegerDotProductProperties;
using VkPhysicalDeviceShaderIntegerDotProductFeatures_t               = VkPhysicalDeviceShaderIntegerDotProductFeatures;
using VkPhysicalDeviceTexelBufferAlignmentProperties_t                = VkPhysicalDeviceTexelBufferAlignmentProperties;
using VkPhysicalDeviceTexelBufferAlignmentFeatures_t                  = VkPhysicalDeviceTexelBufferAlignmentFeatures;
using VkPhysicalDeviceMaintenance4Properties_t                        = VkPhysicalDeviceMaintenance4Properties;
using VkPhysicalDeviceMaintenance4Features_t                          = VkPhysicalDeviceMaintenance4Features;

static VkPhysicalDeviceVulkan13Properties_t                             deviceVulkan13Properties;
static VkPhysicalDeviceSubgroupSizeControlProperties_t                  deviceSubgroupSizeControlProperties;
static VkPhysicalDeviceInlineUniformBlockProperties_t                   deviceInlineUniformBlockProperties;
static VkPhysicalDeviceShaderIntegerDotProductProperties_t              deviceShaderIntegerDotProductProperties;
static VkPhysicalDeviceTexelBufferAlignmentProperties_t                 deviceTexelBufferAlignmentProperties;
static VkPhysicalDeviceMaintenance4Properties_t                         deviceMaintenance4Properties;

static VkPhysicalDeviceVulkan13Features_t                               deviceVulkan13Features;
static VkPhysicalDeviceShaderTerminateInvocationFeatures_t              deviceShaderTerminateInvocationFeatures;
static VkPhysicalDeviceShaderDemoteToHelperInvocationFeatures_t         deviceShaderDemoteToHelperInvocationFeatures;
static VkPhysicalDevicePrivateDataFeatures_t                            devicePrivateDataFeatures;
static VkPhysicalDevicePipelineCreationCacheControlFeatures_t           devicePipelineCreationCacheControlFeatures;
static VkPhysicalDeviceSynchronization2Features_t                       deviceSynchronization2Features;
static VkPhysicalDeviceZeroInitializeWorkgroupMemoryFeatures_t          deviceZeroInitializeWorkgroupMemoryFeatures;
static VkPhysicalDeviceImageRobustnessFeatures_t                        deviceImageRobustnessFeatures;
static VkPhysicalDeviceSubgroupSizeControlFeatures_t                    deviceSubgroupSizeControlFeatures;
static VkPhysicalDeviceInlineUniformBlockFeatures_t                     deviceInlineUniformBlockFeatures;
static VkPhysicalDeviceTextureCompressionASTCHDRFeatures_t              deviceTextureCompressionASTCHDRFeatures;
static VkPhysicalDeviceDynamicRenderingFeatures_t                       deviceDynamicRenderingFeatures;
static VkPhysicalDeviceShaderIntegerDotProductFeatures_t                deviceShaderIntegerDotProductFeatures;
static VkPhysicalDeviceTexelBufferAlignmentFeatures_t                   deviceTexelBufferAlignmentFeatures;
static VkPhysicalDeviceMaintenance4Features_t                           deviceMaintenance4Features;

static VkDevicePrivateDataCreateInfo_t                                  devicePrivateDataCreateInfo;
#endif


/**
 * --------------------------------------------------------
 * --------------------------------------------------------
 * ---- Vulkan Extensions Device Properties & Features ----
 * --------------------------------------------------------
 * --------------------------------------------------------
 */
#if __C_ENG_VULKAN_API_EXTENSION_4444_FORMATS_AVAILABLE
static VkPhysicalDevice4444FormatsFeaturesEXT                           device4444FormatsFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_ASTC_DECODE_MODE_AVAILABLE
static VkPhysicalDeviceASTCDecodeFeaturesEXT                            deviceAstcDecodeFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE
static VkPhysicalDeviceBlendOperationAdvancedPropertiesEXT              deviceBlendOperationAdvancedProperties;
static VkPhysicalDeviceBlendOperationAdvancedFeaturesEXT                deviceBlendOperationAdvancedFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_BORDER_COLOR_SWIZZLE_AVAILABLE
static VkPhysicalDeviceBorderColorSwizzleFeaturesEXT                    deviceBorderColorSwizzleFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_COLOR_WRITE_ENABLE_AVAILABLE
static VkPhysicalDeviceColorWriteEnableFeaturesEXT                      deviceColorWriteEnableFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE
static VkPhysicalDeviceConditionalRenderingFeaturesEXT                  deviceConditionalRenderingFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONSERVATIVE_RASTERIZATION_AVAILABLE
static VkPhysicalDeviceConservativeRasterizationPropertiesEXT           deviceConservativeRasterizationProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE
static VkPhysicalDeviceCustomBorderColorPropertiesEXT                   deviceCustomBorderColorProperties;
static VkPhysicalDeviceCustomBorderColorFeaturesEXT                     deviceCustomBorderColorFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_CONTROL_AVAILABLE
static VkPhysicalDeviceDepthClipControlFeaturesEXT                      deviceDepthClipControlFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_ENABLE_AVAILABLE
static VkPhysicalDeviceDepthClipEnableFeaturesEXT                       deviceDepthClipEnableFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEVICE_MEMORY_REPORT_AVAILABLE
static VkPhysicalDeviceDeviceMemoryReportFeaturesEXT                    deviceDeviceMemoryReportFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE
static VkPhysicalDeviceExtendedDynamicStateFeaturesEXT                  deviceExtendedDynamicStateFeatures;
static VkPhysicalDeviceExtendedDynamicState2FeaturesEXT                 deviceExtendedDynamicState2Features;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISCARD_RECTANGLES_AVAILABLE
static VkPhysicalDeviceDiscardRectanglePropertiesEXT                    deviceDiscardRectangleProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTERNAL_MEMORY_HOST_AVAILABLE
static VkPhysicalDeviceExternalMemoryHostPropertiesEXT                  deviceExternalMemoryHostProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE
static VkPhysicalDeviceFragmentDensityMapPropertiesEXT                  deviceFragmentDensityMapProperties;
static VkPhysicalDeviceFragmentDensityMapFeaturesEXT                    deviceFragmentDensityMapFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE
static VkPhysicalDeviceFragmentDensityMap2PropertiesEXT                 deviceFragmentDensityMap2Properties;
static VkPhysicalDeviceFragmentDensityMap2FeaturesEXT                   deviceFragmentDensityMap2Features;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_SHADER_INTERLOCK_AVAILABLE
static VkPhysicalDeviceFragmentShaderInterlockFeaturesEXT               deviceFragmentShaderInterlockFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE
static VkPhysicalDeviceGlobalPriorityQueryFeaturesEXT                   deviceGlobalPriorityQueryFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_ROBUSTNESS_AVAILABLE && ! __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDeviceImageRobustnessFeatures_t                       = VkPhysicalDeviceImageRobustnessFeaturesEXT;

static VkPhysicalDeviceImageRobustnessFeatures_t                        deviceImageRobustnessFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_VIEW_MIN_LOD_AVAILABLE
static VkPhysicalDeviceImageViewMinLodFeaturesEXT                       deviceImageViewMinLODFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INDEX_TYPE_UINT8_AVAILABLE
static VkPhysicalDeviceIndexTypeUint8FeaturesEXT                        deviceIndexTypeUInt8Features;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE && ! __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDeviceInlineUniformBlockProperties_t                  = VkPhysicalDeviceInlineUniformBlockPropertiesEXT;
using VkPhysicalDeviceInlineUniformBlockFeatures_t                    = VkPhysicalDeviceInlineUniformBlockFeaturesEXT;

static VkPhysicalDeviceInlineUniformBlockProperties_t                   deviceInlineUniformBlockProperties;
static VkPhysicalDeviceInlineUniformBlockFeatures_t                     deviceInlineUniformBlockFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE
static VkPhysicalDeviceLineRasterizationPropertiesEXT                   deviceLineRasterizationProperties;
static VkPhysicalDeviceLineRasterizationFeaturesEXT                     deviceLineRasterizationFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PAGEABLE_DEVICE_LOCAL_MEMORY_AVAILABLE
static VkPhysicalDevicePageableDeviceLocalMemoryFeaturesEXT             devicePageableDeviceLocalMemoryFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_PRIORITY_AVAILABLE
static VkPhysicalDeviceMemoryPriorityFeaturesEXT                        deviceMemoryPriorityFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE
static VkPhysicalDeviceMultiDrawPropertiesEXT                           deviceMultiDrawProperties;
static VkPhysicalDeviceMultiDrawFeaturesEXT                             deviceMultiDrawFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE && ! __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDevicePipelineCreationCacheControlFeatures_t          = VkPhysicalDevicePipelineCreationCacheControlFeaturesEXT;

static VkPhysicalDevicePipelineCreationCacheControlFeatures_t           devicePipelineCreationCacheControlFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PCI_BUS_INFO_AVAILABLE
static VkPhysicalDevicePCIBusInfoPropertiesEXT                          devicePciBusInfoProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIMITIVE_TOPOLOGY_LIST_RESTART_AVAILABLE
static VkPhysicalDevicePrimitiveTopologyListRestartFeaturesEXT          devicePrimitiveTopologyListRestartFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE && ! __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDevicePrivateDataFeatures_t                           = VkPhysicalDevicePrivateDataFeaturesEXT;

static VkPhysicalDevicePrivateDataFeatures_t                            devicePrivateDataFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PHYSICAL_DEVICE_DRM_AVAILABLE
static VkPhysicalDeviceDrmPropertiesEXT                                 deviceDrmProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE
static VkPhysicalDeviceProvokingVertexPropertiesEXT                     deviceProvokingVertexProperties;
static VkPhysicalDeviceProvokingVertexFeaturesEXT                       deviceProvokingVertexFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_RGBA_10_X_6_FORMATS_AVAILABLE
static VkPhysicalDeviceRGBA10X6FormatsFeaturesEXT                       deviceRgba10X6FormatsFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE
static VkPhysicalDeviceRobustness2PropertiesEXT                         deviceRobustness2Properties;
static VkPhysicalDeviceRobustness2FeaturesEXT                           deviceRobustness2Features;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE
static VkPhysicalDeviceSampleLocationsPropertiesEXT                     deviceSampleLocationsProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_AVAILABLE
static VkPhysicalDeviceShaderAtomicFloatFeaturesEXT                     deviceShaderAtomicFloatFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_2_AVAILABLE
static VkPhysicalDeviceShaderAtomicFloat2FeaturesEXT                    deviceShaderAtomicFloat2Features;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_DEMOTE_TO_HELPER_INVOCATION_AVAILABLE && ! __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDeviceShaderDemoteToHelperInvocationFeatures_t        = VkPhysicalDeviceShaderDemoteToHelperInvocationFeaturesEXT;

static VkPhysicalDeviceShaderDemoteToHelperInvocationFeatures_t         deviceShaderDemoteToHelperInvocationFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_IMAGE_ATOMIC_INT64_AVAILABLE
static VkPhysicalDeviceShaderImageAtomicInt64FeaturesEXT                deviceShaderImageAtomicInt64Features;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE && ! __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDeviceSubgroupSizeControlProperties_t                 = VkPhysicalDeviceSubgroupSizeControlPropertiesEXT;
using VkPhysicalDeviceSubgroupSizeControlFeatures_t                   = VkPhysicalDeviceSubgroupSizeControlFeaturesEXT;

static VkPhysicalDeviceSubgroupSizeControlProperties_t                  deviceSubgroupSizeControlProperties;
static VkPhysicalDeviceSubgroupSizeControlFeatures_t                    deviceSubgroupSizeControlFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE && ! __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDeviceTexelBufferAlignmentProperties_t                = VkPhysicalDeviceTexelBufferAlignmentPropertiesEXT;
using VkPhysicalDeviceTexelBufferAlignmentFeatures_t                  = VkPhysicalDeviceTexelBufferAlignmentFeaturesEXT;

static VkPhysicalDeviceTexelBufferAlignmentProperties_t                 deviceTexelBufferAlignmentProperties;
static VkPhysicalDeviceTexelBufferAlignmentFeatures_t                   deviceTexelBufferAlignmentFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXTURE_COMPRESSION_ASTC_HDR_AVAILABLE && ! __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDeviceTextureCompressionASTCHDRFeatures_t             = VkPhysicalDeviceTextureCompressionASTCHDRFeaturesEXT;

static VkPhysicalDeviceTextureCompressionASTCHDRFeatures_t              deviceTextureCompressionASTCHDRFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE
static VkPhysicalDeviceTransformFeedbackPropertiesEXT                   deviceTransformFeedbackProperties;
static VkPhysicalDeviceTransformFeedbackFeaturesEXT                     deviceTransformFeedbackFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE
static VkPhysicalDeviceVertexAttributeDivisorPropertiesEXT              deviceVertexAttributeDivisorProperties;
static VkPhysicalDeviceVertexAttributeDivisorFeaturesEXT                deviceVertexAttributeDivisorFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_INPUT_DYNAMIC_STATE_AVAILABLE
static VkPhysicalDeviceVertexInputDynamicStateFeaturesEXT               deviceVertexInputDynamicStateFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_2_PLANE_444_FORMATS_AVAILABLE
static VkPhysicalDeviceYcbcr2Plane444FormatsFeaturesEXT                 deviceYCBCR2Plane444FormatsFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_IMAGE_ARRAYS_AVAILABLE
static VkPhysicalDeviceYcbcrImageArraysFeaturesEXT                      deviceYCBCRImageArraysFeatures;
#endif


/**
 * ----------------------------------------------------------------
 * ----------------------------------------------------------------
 * ---- Vulkan Khronos Extensions Device Properties & Features ----
 * ----------------------------------------------------------------
 * ----------------------------------------------------------------
 */
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
static VkPhysicalDeviceAccelerationStructurePropertiesKHR               deviceAccelerationStructureProperties;
static VkPhysicalDeviceAccelerationStructureFeaturesKHR                 deviceAccelerationStructureFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE && ! __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDeviceDynamicRenderingFeatures_t                      = VkPhysicalDeviceDynamicRenderingFeaturesKHR;

static VkPhysicalDeviceDynamicRenderingFeatures_t                       deviceDynamicRenderingFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE
static VkPhysicalDeviceFragmentShadingRatePropertiesKHR                 deviceFragmentShadingRateProperties;
static VkPhysicalDeviceFragmentShadingRateFeaturesKHR                   deviceFragmentShadingRateFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE && ! __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDeviceMaintenance4Properties_t                        = VkPhysicalDeviceMaintenance4PropertiesKHR;
using VkPhysicalDeviceMaintenance4Features_t                          = VkPhysicalDeviceMaintenance4FeaturesKHR;

static VkPhysicalDeviceMaintenance4Properties_t                         deviceMaintenance4Properties;
static VkPhysicalDeviceMaintenance4Features_t                           deviceMaintenance4Features;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
static VkPhysicalDevicePerformanceQueryPropertiesKHR                    devicePerformanceQueryProperties;
static VkPhysicalDevicePerformanceQueryFeaturesKHR                      devicePerformanceQueryFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
static VkPhysicalDevicePipelineExecutablePropertiesFeaturesKHR          devicePipelineExecutablePropertiesFeatures;
#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE
static VkPhysicalDevicePortabilitySubsetPropertiesKHR                   devicePortabilitySubsetProperties;
static VkPhysicalDevicePortabilitySubsetFeaturesKHR                     devicePortabilitySubsetFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_ID_AVAILABLE
static VkPhysicalDevicePresentIdFeaturesKHR                             devicePresentIDFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_WAIT_AVAILABLE
static VkPhysicalDevicePresentWaitFeaturesKHR                           devicePresentWaitFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_QUERY_AVAILABLE
static VkPhysicalDeviceRayQueryFeaturesKHR                              deviceRayQueryFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_CLOCK_AVAILABLE
static VkPhysicalDeviceShaderClockFeaturesKHR                           deviceShaderClockFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PUSH_DESCRIPTOR_AVAILABLE
static VkPhysicalDevicePushDescriptorPropertiesKHR                      devicePushDescriptorProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
static VkPhysicalDeviceRayTracingPipelinePropertiesKHR                  deviceRayTracingPipelineProperties;
static VkPhysicalDeviceRayTracingPipelineFeaturesKHR                    deviceRayTracingPipelineFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_SUBGROUP_UNIFORM_CONTROL_FLOW_AVAILABLE
static VkPhysicalDeviceShaderSubgroupUniformControlFlowFeaturesKHR      deviceShaderSubgroupUniformControlFlowFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_TERMINATE_INVOCATION_AVAILABLE && ! __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDeviceShaderTerminateInvocationFeatures_t             = VkPhysicalDeviceShaderTerminateInvocationFeaturesKHR;

static VkPhysicalDeviceShaderTerminateInvocationFeatures_t              deviceShaderTerminateInvocationFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE && ! __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDeviceSynchronization2Features_t                      = VkPhysicalDeviceSynchronization2FeaturesKHR;

static VkPhysicalDeviceSynchronization2Features_t                       deviceSynchronization2Features;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE && ! __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDeviceShaderIntegerDotProductProperties_t             = VkPhysicalDeviceShaderIntegerDotProductPropertiesKHR;
using VkPhysicalDeviceShaderIntegerDotProductFeatures_t               = VkPhysicalDeviceShaderIntegerDotProductFeaturesKHR;

static VkPhysicalDeviceShaderIntegerDotProductProperties_t              deviceShaderIntegerDotProductProperties;
static VkPhysicalDeviceShaderIntegerDotProductFeatures_t                deviceShaderIntegerDotProductFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_AVAILABLE
static VkPhysicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR         deviceWorkgroupMemoryExplicitLayoutFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ZERO_INITIALIZE_WORKGROUP_MEMORY_AVAILABLE && ! __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDeviceZeroInitializeWorkgroupMemoryFeatures_t         = VkPhysicalDeviceZeroInitializeWorkgroupMemoryFeaturesKHR;

static VkPhysicalDeviceZeroInitializeWorkgroupMemoryFeatures_t          deviceZeroInitializeWorkgroupMemoryFeatures;
#endif


/**
 * ---------------------------------------------------------------
 * ---------------------------------------------------------------
 * ---- Vulkan NVidia Extensions Device Properties & Features ----
 * ---------------------------------------------------------------
 * ---------------------------------------------------------------
 */
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COMPUTE_SHADER_DERIVATIVES_AVAILABLE
static VkPhysicalDeviceComputeShaderDerivativesFeaturesNV               deviceComputeShaderDerivativesFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE
static VkPhysicalDeviceCooperativeMatrixPropertiesNV                    deviceCooperativeMatrixProperties;
static VkPhysicalDeviceCooperativeMatrixFeaturesNV                      deviceCooperativeMatrixFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CORNER_SAMPLED_IMAGE_AVAILABLE
static VkPhysicalDeviceCornerSampledImageFeaturesNV                     deviceDeviceCornerSampledImageFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COVERAGE_REDUCTION_MODE_AVAILABLE
static VkPhysicalDeviceCoverageReductionModeFeaturesNV                  deviceCoverageReductionModeFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE
static VkPhysicalDeviceDeviceGeneratedCommandsPropertiesNV              deviceDeviceGeneratedCommandsProperties;
static VkPhysicalDeviceDeviceGeneratedCommandsFeaturesNV                deviceDeviceGeneratedCommandsFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_IMAGE_ALIASING_AVAILABLE
static VkPhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV       deviceDedicatedAllocationImageAliasingFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTICS_CONFIG_AVAILABLE
static VkPhysicalDeviceDiagnosticsConfigFeaturesNV                      deviceDiagnosticsConfigFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SCISSOR_EXCLUSIVE_AVAILABLE
static VkPhysicalDeviceExclusiveScissorFeaturesNV                       deviceExclusiveScissorFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_RDMA_AVAILABLE
static VkPhysicalDeviceExternalMemoryRDMAFeaturesNV                     deviceExternalMemoryRDMAFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADER_BARYCENTRIC_AVAILABLE
static VkPhysicalDeviceFragmentShaderBarycentricFeaturesNV              deviceFragmentShaderBarycentricFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE
static VkPhysicalDeviceFragmentShadingRateEnumsPropertiesNV             deviceFragmentShadingRateEnumsProperties;
static VkPhysicalDeviceFragmentShadingRateEnumsFeaturesNV               deviceFragmentShadingRateEnumsFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_INHERITED_VIEWPORT_SCISSOR_AVAILABLE
static VkPhysicalDeviceInheritedViewportScissorFeaturesNV               deviceInheritedViewportScissorFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_LINEAR_COLOR_ATTACHMENT_AVAILABLE
static VkPhysicalDeviceLinearColorAttachmentFeaturesNV                  deviceLinearColorAttachmentFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE
static VkPhysicalDeviceMeshShaderPropertiesNV                           deviceMeshShaderProperties;
static VkPhysicalDeviceMeshShaderFeaturesNV                             deviceMeshShaderFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
static VkPhysicalDeviceRayTracingPropertiesNV                           deviceRayTracingProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE
static VkPhysicalDeviceRayTracingMotionBlurFeaturesNV                   deviceRayTracingMotionBlurFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_REPRESENTATIVE_FRAGMENT_TEST_AVAILABLE
static VkPhysicalDeviceRepresentativeFragmentTestFeaturesNV             deviceRepresentativeFragmentTestFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_IMAGE_FOOTPRINT_AVAILABLE
static VkPhysicalDeviceShaderImageFootprintFeaturesNV                   deviceShaderImageFootprintFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE
static VkPhysicalDeviceShaderSMBuiltinsPropertiesNV                     deviceShaderSmBuiltinsProperties;
static VkPhysicalDeviceShaderSMBuiltinsFeaturesNV                       deviceShaderSmBuiltinsFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE
static VkPhysicalDeviceShadingRateImagePropertiesNV                     deviceShadingRateImageProperties;
static VkPhysicalDeviceShadingRateImageFeaturesNV                       deviceShadingRateImageFeatures;
#endif

#if ( __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE ) && __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE
static VkPhysicalDeviceMultiviewPerViewAttributesPropertiesNVX          deviceMultiviewPerViewAttributesProperties;
#endif


/**
 * ------------------------------------------------------------
 * ------------------------------------------------------------
 * ---- Vulkan AMD Extensions Device Properties & Features ----
 * ------------------------------------------------------------
 * ------------------------------------------------------------
 */
#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_AVAILABLE
static VkPhysicalDeviceShaderCorePropertiesAMD                          deviceShaderCoreProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_2_AVAILABLE
static VkPhysicalDeviceShaderCoreProperties2AMD                         deviceShaderCoreProperties2;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_DEVICE_COHERENT_MEMORY_AVAILABLE
static VkPhysicalDeviceCoherentMemoryFeaturesAMD                        deviceCoherentMemoryFeatures;
#endif


/**
 * -----------------------------------------------------------------
 * -----------------------------------------------------------------
 * ---- Vulkan Qualcomm Extensions Device Properties & Features ----
 * -----------------------------------------------------------------
 * -----------------------------------------------------------------
 */
#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE
static VkPhysicalDeviceFragmentDensityMapOffsetPropertiesQCOM           deviceFragmentDensityMapOffsetProperties;
static VkPhysicalDeviceFragmentDensityMapOffsetFeaturesQCOM             deviceFragmentDensityMapOffsetFeatures;
#endif


/**
 * ---------------------------------------------------------------
 * ---------------------------------------------------------------
 * ---- Vulkan Huawei Extensions Device Properties & Features ----
 * ---------------------------------------------------------------
 * ---------------------------------------------------------------
 */
#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE
static VkPhysicalDeviceSubpassShadingPropertiesHUAWEI                   deviceSubpassShadingProperties;
static VkPhysicalDeviceSubpassShadingFeaturesHUAWEI                     deviceSubpassShadingFeatures;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_INVOCATION_MASK_AVAILABLE
static VkPhysicalDeviceInvocationMaskFeaturesHUAWEI                     deviceInvocationMaskFeatures;
#endif


/**
 * --------------------------------------------------------------
 * --------------------------------------------------------------
 * ---- Vulkan Valve Extensions Device Properties & Features ----
 * --------------------------------------------------------------
 * --------------------------------------------------------------
 */
#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE
static VkPhysicalDeviceMutableDescriptorTypeFeaturesVALVE               deviceMutableDescriptorTypeFeatures;
#endif


/**
 * --------------------------------------------------------------
 * --------------------------------------------------------------
 * ---- Vulkan Intel Extensions Device Properties & Features ----
 * --------------------------------------------------------------
 * --------------------------------------------------------------
 */
#if __C_ENG_VULKAN_API_EXTENSION_INTEL_SHADER_INTEGER_FUNCTIONS_AVAILABLE
static VkPhysicalDeviceShaderIntegerFunctions2FeaturesINTEL             deviceShaderIntegerFunctions2Features;
#endif


/**
 * ------------------------------------------------------------
 * ------------------------------------------------------------
 * ---- Vulkan ARM Extensions Device Properties & Features ----
 * ------------------------------------------------------------
 * ------------------------------------------------------------
 */
#if __C_ENG_VULKAN_API_EXTENSION_ARM_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_AVAILABLE
static VkPhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM    deviceRasterizationOrderAttachmentAccessFeatures;
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
static VkDeviceQueueCreateInfo                                      deviceQueueCreateInfos [ __C_ENG_VULKAN_CORE_DEVICE_QUEUE_FAMILY_CREATE_INFO_MAX_COUNT ];

#if __C_ENG_VULKAN_API_EXTENSION_DEVICE_MEMORY_REPORT_AVAILABLE
static VkDeviceDeviceMemoryReportCreateInfoEXT                      deviceDeviceMemoryReportCreateInfo;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTICS_CONFIG_AVAILABLE
static VkDeviceDiagnosticsConfigCreateInfoNV                        deviceDiagnosticsConfigCreateInfo;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
static VkDeviceGroupDeviceCreateInfo                                deviceGroupDeviceCreateInfo;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_MEMORY_OVERALLOCATION_BEHAVIOUR_AVAILABLE
static VkDeviceMemoryOverallocationCreateInfoAMD                    deviceMemoryOverallocationCreateInfo;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE && ! __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
static VkDevicePrivateDataCreateInfoEXT                             devicePrivateDataCreateInfo;

using VkDevicePrivateDataCreateInfo_t                             = VkDevicePrivateDataCreateInfoEXT;
#endif


static VkInstance lastCreatedInstance;

using FunctionHandleAddress = void **;


static PFN_vkEnumerateInstanceVersion                                       pVkEnumerateInstanceVersion;
static PFN_vkEnumerateInstanceLayerProperties                               pVkEnumerateInstanceLayerProperties;
static PFN_vkEnumerateInstanceExtensionProperties                           pVkEnumerateInstanceExtensionProperties;
static PFN_vkCreateInstance                                                 pVkCreateInstance;
static PFN_vkDestroyInstance                                                pVkDestroyInstance;

static PFN_vkGetDeviceProcAddr                                              pVkGetDeviceProcAddr;
static PFN_vkEnumeratePhysicalDevices                                       pVkEnumeratePhysicalDevices;
static PFN_vkGetPhysicalDeviceProperties                                    pVkGetPhysicalDeviceProperties;
static PFN_vkGetPhysicalDeviceProperties2                                   pVkGetPhysicalDeviceProperties2;
static PFN_vkGetPhysicalDeviceFeatures                                      pVkGetPhysicalDeviceFeatures;
static PFN_vkGetPhysicalDeviceFeatures2                                     pVkGetPhysicalDeviceFeatures2;
static PFN_vkEnumerateDeviceLayerProperties                                 pVkEnumerateDeviceLayerProperties;
static PFN_vkEnumerateDeviceExtensionProperties                             pVkEnumerateDeviceExtensionProperties;

static PFN_vkEnumeratePhysicalDeviceGroups                                  pVkEnumeratePhysicalDeviceGroups;

static PFN_vkCreateDebugUtilsMessengerEXT                                   pVkCreateDebugUtilsMessenger;
static PFN_vkDestroyDebugUtilsMessengerEXT                                  pVkDestroyDebugUtilsMessenger;

static PFN_vkGetPhysicalDeviceQueueFamilyProperties                         pVkGetPhysicalDeviceQueueFamilyProperties;
static PFN_vkGetPhysicalDeviceQueueFamilyProperties2                        pVkGetPhysicalDeviceQueueFamilyProperties2;
static PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR  pVkInstanceProcessEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCounters;

static PFN_vkDestroySurfaceKHR                                              pVkDestroySurface;

static PFN_vkGetPhysicalDeviceSurfaceSupportKHR                             pVkGetPhysicalDeviceSurfaceSupport;

static PFN_vkCreateDevice                                                   pVkCreateDevice;

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pOut == nullptr || pIn == nullptr ) {
        return;
    }

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pOut == nullptr || pIn == nullptr ) {
        return;
    }

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pOut == nullptr || pIn == nullptr ) {
        return;
    }

#endif

    pOut->maxPerSetDescriptors              = pIn->maxPerSetDescriptors;
    pOut->maxMemoryAllocationSize           = pIn->maxMemoryAllocationSize;
}

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceMultiviewProperties ) * pOut,
        VkPhysicalDeviceMultiviewProperties                    const * pIn
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pOut == nullptr || pIn == nullptr ) {
        return;
    }

#endif

    pOut->maxMultiviewViewCount             = pIn->maxMultiviewViewCount;
    pOut->maxMultiviewInstanceIndex         = pIn->maxMultiviewInstanceIndex;
}

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDevicePointClippingProperties ) * pOut,
        VkPhysicalDevicePointClippingProperties                    const * pIn
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pOut == nullptr || pIn == nullptr ) {
        return;
    }

#endif

    pOut->pointClippingBehavior             = static_cast < vulkan :: __C_ENG_TYPE ( PointClippingBehavior ) > ( pIn->pointClippingBehavior );
}

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceProtectedMemoryProperties ) * pOut,
        VkPhysicalDeviceProtectedMemoryProperties                    const * pIn
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pOut == nullptr || pIn == nullptr ) {
        return;
    }

#endif

    pOut->protectedNoFault             = pIn->protectedNoFault;
}

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceSubgroupProperties ) * pOut,
        VkPhysicalDeviceSubgroupProperties                    const * pIn
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pOut == nullptr || pIn == nullptr ) {
        return;
    }

#endif

    pOut->subgroupSize              = pIn->subgroupSize;
    pOut->supportedStages           = pIn->supportedStages;
    pOut->supportedOperations       = pIn->supportedOperations;
    pOut->quadOperationsInAllStages = pIn->quadOperationsInAllStages;
}

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDevice16BitStorageFeatures ) * pDestination,
        VkPhysicalDevice16BitStorageFeatures                    const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

    pDestination->storageBuffer16BitAccess              = pSource->storageBuffer16BitAccess;
    pDestination->uniformAndStorageBuffer16BitAccess    = pSource->uniformAndStorageBuffer16BitAccess;
    pDestination->storagePushConstant16                 = pSource->storagePushConstant16;
    pDestination->storageInputOutput16                  = pSource->storageInputOutput16;
}

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceMultiviewFeatures ) * pDestination,
        VkPhysicalDeviceMultiviewFeatures                    const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

    pDestination->multiview                     = pSource->multiview;
    pDestination->multiviewGeometryShader       = pSource->multiviewGeometryShader;
    pDestination->multiviewTessellationShader   = pSource->multiviewTessellationShader;
}

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceProtectedMemoryFeatures ) * pDestination,
        VkPhysicalDeviceProtectedMemoryFeatures                    const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

    pDestination->protectedMemory                     = pSource->protectedMemory;
}

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceSamplerYCBCRConversionFeatures ) * pDestination,
        VkPhysicalDeviceSamplerYcbcrConversionFeatures                    const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

    pDestination->samplerYCBCRConversion                     = pSource->samplerYcbcrConversion;
}

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderDrawParametersFeatures ) * pDestination,
        VkPhysicalDeviceShaderDrawParametersFeatures                    const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

    pDestination->shaderDrawParameters                     = pSource->shaderDrawParameters;
}

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceVariablePointersFeatures ) * pDestination,
        VkPhysicalDeviceVariablePointersFeatures                    const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

    pDestination->variablePointersStorageBuffer = pSource->variablePointersStorageBuffer;
    pDestination->variablePointers              = pSource->variablePointers;
}

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceVulkan11Features ) * pDestination,
        VkPhysicalDeviceVulkan11Features                    const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

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
}

static inline auto toVulkanFormat (
        VkPhysicalDevice16BitStorageFeatures                                * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDevice16BitStorageFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

    pDestination->storageBuffer16BitAccess              = pSource->storageBuffer16BitAccess;
    pDestination->uniformAndStorageBuffer16BitAccess    = pSource->uniformAndStorageBuffer16BitAccess;
    pDestination->storagePushConstant16                 = pSource->storagePushConstant16;
    pDestination->storageInputOutput16                  = pSource->storageInputOutput16;
}

static inline auto toVulkanFormat (
        VkPhysicalDeviceMultiviewFeatures                                * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceMultiviewFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

    pDestination->multiview                     = pSource->multiview;
    pDestination->multiviewGeometryShader       = pSource->multiviewGeometryShader;
    pDestination->multiviewTessellationShader   = pSource->multiviewTessellationShader;
}

static inline auto toVulkanFormat (
        VkPhysicalDeviceProtectedMemoryFeatures                                 * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceProtectedMemoryFeatures )  const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

    pDestination->protectedMemory                     = pSource->protectedMemory;
}

static inline auto toVulkanFormat (
        VkPhysicalDeviceSamplerYcbcrConversionFeatures                                * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceSamplerYCBCRConversionFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

    pDestination->samplerYcbcrConversion                     = pSource->samplerYCBCRConversion;
}

static inline auto toVulkanFormat (
        VkPhysicalDeviceShaderDrawParametersFeatures                                * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderDrawParametersFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

    pDestination->shaderDrawParameters                     = pSource->shaderDrawParameters;
}

static inline auto toVulkanFormat (
        VkPhysicalDeviceVariablePointersFeatures                                * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceVariablePointersFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

    pDestination->variablePointersStorageBuffer = pSource->variablePointersStorageBuffer;
    pDestination->variablePointers              = pSource->variablePointers;
}

static inline auto toVulkanFormat (
        VkPhysicalDeviceVulkan11Features                                * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceVulkan11Features ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

#endif

    pIn->patch      = pOut->patch;
    pIn->major      = pOut->major;
    pIn->minor      = pOut->minor;
    pIn->subminor   = pOut->subminor;
}

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceVulkan12Properties ) * pOut,
        VkPhysicalDeviceVulkan12Properties                    const * pIn
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pOut == nullptr || pIn == nullptr ) {
        return;
    }

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pOut == nullptr || pIn == nullptr ) {
        return;
    }

#endif

    pOut->supportedDepthResolveModes                                = pIn->supportedDepthResolveModes;
    pOut->supportedStencilResolveModes                              = pIn->supportedStencilResolveModes;

    pOut->independentResolveNone                                    = pIn->independentResolveNone;
    pOut->independentResolve                                        = pIn->independentResolve;
}

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceDescriptorIndexingProperties ) * pOut,
        VkPhysicalDeviceDescriptorIndexingProperties                    const * pIn
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pOut == nullptr || pIn == nullptr ) {
        return;
    }

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pOut == nullptr || pIn == nullptr ) {
        return;
    }

#endif

    pOut->driverID                                                  = static_cast < vulkan :: __C_ENG_TYPE ( DriverID ) > ( pIn->driverID );
    (void) std :: memcpy ( pOut->driverName,                        pIn->driverName, sizeof ( pIn->driverName[0] ) * VK_MAX_DRIVER_NAME_SIZE ); // NOLINT(clion-misra-cpp2008-5-2-12)
    (void) std :: memcpy ( pOut->driverInfo,                        pIn->driverInfo, sizeof ( pIn->driverInfo[0] ) * VK_MAX_DRIVER_INFO_SIZE ); // NOLINT(clion-misra-cpp2008-5-2-12)
    fromVulkanFormat ( & pOut->conformanceVersion,                  & pIn->conformanceVersion );
}

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceFloatControlsProperties ) * pOut,
        VkPhysicalDeviceFloatControlsProperties                    const * pIn
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pOut == nullptr || pIn == nullptr ) {
        return;
    }

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pOut == nullptr || pIn == nullptr ) {
        return;
    }

#endif

    pOut->filterMinmaxSingleComponentFormats                        = pIn->filterMinmaxSingleComponentFormats;
    pOut->filterMinmaxImageComponentMapping                         = pIn->filterMinmaxImageComponentMapping;
}

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceTimelineSemaphoreProperties ) * pOut,
        VkPhysicalDeviceTimelineSemaphoreProperties                    const * pIn
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pOut == nullptr || pIn == nullptr ) {
        return;
    }

#endif

    pOut->maxTimelineSemaphoreValueDifference                       = pIn->maxTimelineSemaphoreValueDifference;
}

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDevice8BitStorageFeatures ) * pDestination,
        VkPhysicalDevice8BitStorageFeatures                    const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

    pDestination->storageBuffer8BitAccess           = pSource->storageBuffer8BitAccess;
    pDestination->uniformAndStorageBuffer8BitAccess = pSource->uniformAndStorageBuffer8BitAccess;
    pDestination->storagePushConstant8              = pSource->storagePushConstant8;
}

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceBufferDeviceAddressFeatures ) * pDestination,
        VkPhysicalDeviceBufferDeviceAddressFeatures                    const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

    pDestination->bufferDeviceAddress               = pSource->bufferDeviceAddress;
    pDestination->bufferDeviceAddressCaptureReplay  = pSource->bufferDeviceAddressCaptureReplay;
    pDestination->bufferDeviceAddressMultiDevice    = pSource->bufferDeviceAddressMultiDevice;
}

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceDescriptorIndexingFeatures ) * pDestination,
        VkPhysicalDeviceDescriptorIndexingFeatures                    const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

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
}

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceHostQueryResetFeatures ) * pDestination,
        VkPhysicalDeviceHostQueryResetFeatures                    const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

    pDestination->hostQueryReset             = pSource->hostQueryReset;
}

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceImagelessFramebufferFeatures ) * pDestination,
        VkPhysicalDeviceImagelessFramebufferFeatures                    const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

    pDestination->imagelessFramebuffer             = pSource->imagelessFramebuffer;
}

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceScalarBlockLayoutFeatures ) * pDestination,
        VkPhysicalDeviceScalarBlockLayoutFeatures                    const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

    pDestination->scalarBlockLayout             = pSource->scalarBlockLayout;
}

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceSeparateDepthStencilLayoutsFeatures ) * pDestination,
        VkPhysicalDeviceSeparateDepthStencilLayoutsFeatures                    const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

    pDestination->separateDepthStencilLayouts             = pSource->separateDepthStencilLayouts;
}

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderAtomicInt64Features ) * pDestination,
        VkPhysicalDeviceShaderAtomicInt64Features                    const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

    pDestination->shaderBufferInt64Atomics             = pSource->shaderBufferInt64Atomics;
    pDestination->shaderSharedInt64Atomics             = pSource->shaderSharedInt64Atomics;
}

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderFloat16Int8Features ) * pDestination,
        VkPhysicalDeviceShaderFloat16Int8Features                    const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

    pDestination->shaderFloat16                 = pSource->shaderFloat16;
    pDestination->shaderInt8                    = pSource->shaderInt8;
}

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderSubgroupExtendedTypesFeatures ) * pDestination,
        VkPhysicalDeviceShaderSubgroupExtendedTypesFeatures                    const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

    pDestination->shaderSubgroupExtendedTypes                 = pSource->shaderSubgroupExtendedTypes;
}

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceTimelineSemaphoreFeatures ) * pDestination,
        VkPhysicalDeviceTimelineSemaphoreFeatures                    const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

    pDestination->timelineSemaphore                 = pSource->timelineSemaphore;
}

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceUniformBufferStandardLayoutFeatures ) * pDestination,
        VkPhysicalDeviceUniformBufferStandardLayoutFeatures                    const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

    pDestination->uniformBufferStandardLayout                 = pSource->uniformBufferStandardLayout;
}

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceVulkanMemoryModelFeatures ) * pDestination,
        VkPhysicalDeviceVulkanMemoryModelFeatures                    const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

    pDestination->vulkanMemoryModel                             = pSource->vulkanMemoryModel;
    pDestination->vulkanMemoryModelDeviceScope                  = pSource->vulkanMemoryModelDeviceScope;
    pDestination->vulkanMemoryModelAvailabilityVisibilityChains = pSource->vulkanMemoryModelAvailabilityVisibilityChains;
}

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceVulkan12Features ) * pDestination,
        VkPhysicalDeviceVulkan12Features                    const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

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
}

static inline auto toVulkanFormat (
        VkPhysicalDevice8BitStorageFeatures                                 * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDevice8BitStorageFeatures )  const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

    pDestination->storageBuffer8BitAccess           = pSource->storageBuffer8BitAccess;
    pDestination->uniformAndStorageBuffer8BitAccess = pSource->uniformAndStorageBuffer8BitAccess;
    pDestination->storagePushConstant8              = pSource->storagePushConstant8;
}

static inline auto toVulkanFormat (
        VkPhysicalDeviceBufferDeviceAddressFeatures                                * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceBufferDeviceAddressFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

    pDestination->bufferDeviceAddress               = pSource->bufferDeviceAddress;
    pDestination->bufferDeviceAddressCaptureReplay  = pSource->bufferDeviceAddressCaptureReplay;
    pDestination->bufferDeviceAddressMultiDevice    = pSource->bufferDeviceAddressMultiDevice;
}

static inline auto toVulkanFormat (
        VkPhysicalDeviceDescriptorIndexingFeatures                                * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceDescriptorIndexingFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

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
}

static inline auto toVulkanFormat (
        VkPhysicalDeviceHostQueryResetFeatures                                * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceHostQueryResetFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

    pDestination->hostQueryReset             = pSource->hostQueryReset;
}

static inline auto toVulkanFormat (
        VkPhysicalDeviceImagelessFramebufferFeatures                                * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceImagelessFramebufferFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

    pDestination->imagelessFramebuffer             = pSource->imagelessFramebuffer;
}

static inline auto toVulkanFormat (
        VkPhysicalDeviceScalarBlockLayoutFeatures                                * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceScalarBlockLayoutFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

    pDestination->scalarBlockLayout             = pSource->scalarBlockLayout;
}

static inline auto toVulkanFormat (
        VkPhysicalDeviceSeparateDepthStencilLayoutsFeatures                                * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceSeparateDepthStencilLayoutsFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

    pDestination->separateDepthStencilLayouts             = pSource->separateDepthStencilLayouts;
}

static inline auto toVulkanFormat (
        VkPhysicalDeviceShaderAtomicInt64Features                                * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderAtomicInt64Features ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

    pDestination->shaderBufferInt64Atomics             = pSource->shaderBufferInt64Atomics;
    pDestination->shaderSharedInt64Atomics             = pSource->shaderSharedInt64Atomics;
}

static inline auto toVulkanFormat (
        VkPhysicalDeviceShaderFloat16Int8Features                                * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderFloat16Int8Features ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

    pDestination->shaderFloat16                 = pSource->shaderFloat16;
    pDestination->shaderInt8                    = pSource->shaderInt8;
}

static inline auto toVulkanFormat (
        VkPhysicalDeviceShaderSubgroupExtendedTypesFeatures                                * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderSubgroupExtendedTypesFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

    pDestination->shaderSubgroupExtendedTypes                 = pSource->shaderSubgroupExtendedTypes;
}

static inline auto toVulkanFormat (
        VkPhysicalDeviceTimelineSemaphoreFeatures                                * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceTimelineSemaphoreFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

    pDestination->timelineSemaphore                 = pSource->timelineSemaphore;
}

static inline auto toVulkanFormat (
        VkPhysicalDeviceUniformBufferStandardLayoutFeatures                                * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceUniformBufferStandardLayoutFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

    pDestination->uniformBufferStandardLayout                 = pSource->uniformBufferStandardLayout;
}

static inline auto toVulkanFormat (
        VkPhysicalDeviceVulkanMemoryModelFeatures                                * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceVulkanMemoryModelFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

    pDestination->vulkanMemoryModel                             = pSource->vulkanMemoryModel;
    pDestination->vulkanMemoryModelDeviceScope                  = pSource->vulkanMemoryModelDeviceScope;
    pDestination->vulkanMemoryModelAvailabilityVisibilityChains = pSource->vulkanMemoryModelAvailabilityVisibilityChains;
}

static inline auto toVulkanFormat (
        VkPhysicalDeviceVulkan12Features                                * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceVulkan12Features ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

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
}


#endif


/**
 * ---------------------------------------------------------
 * ---------------------------------------------------------
 * -------- Vulkan 1.3 Device Properties Convertors --------
 * ---------------------------------------------------------
 * ---------------------------------------------------------
 */
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceVulkan13Properties ) * pDestination,
        VkPhysicalDeviceVulkan13Properties_t                  const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if (
            pDestination    == nullptr ||
            pSource         == nullptr
    ) {
        return;
    }

#endif

    pDestination->structureType = StructureTypePhysicalDeviceVulkan_1_3_Properties;
    pDestination->pNext         = nullptr;

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
}

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceVulkan13Features ) * pDestination,
        VkPhysicalDevice13Features_t                        const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

    pDestination->structureType                                         = StructureTypePhysicalDeviceVulkan_1_3_Features;
    pDestination->pNext                                                 = nullptr;

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
}

static inline auto toVulkanFormat (
        VkPhysicalDevice13Features_t                                    * pSource,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceVulkan13Features ) const * pDestination
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pSource == nullptr || pDestination == nullptr ) {
        return;
    }

#endif

    pDestination->sType                                                 = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES;
    pDestination->pNext                                                 = nullptr;

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
}

#endif


/**
 * ---------------------------------------------------------
 * ---------------------------------------------------------
 * ---- Vulkan Extensions Device Properties Convertors -----
 * ---------------------------------------------------------
 * ---------------------------------------------------------
 */
#if __C_ENG_VULKAN_API_EXTENSION_4444_FORMATS_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDevice4444FormatsFeatures ) * pDestination,
        VkPhysicalDevice4444FormatsFeaturesEXT                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->formatA4R4G4B4            = pSource->formatA4R4G4B4;
    pDestination->formatA4B4G4R4            = pSource->formatA4B4G4R4;
}

inline static auto toVulkanFormat (
        VkPhysicalDevice4444FormatsFeaturesEXT                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDevice4444FormatsFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->formatA4R4G4B4            = pSource->formatA4R4G4B4;
    pDestination->formatA4B4G4R4            = pSource->formatA4B4G4R4;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ASTC_DECODE_MODE_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceASTCDecodeFeatures ) * pDestination,
        VkPhysicalDeviceASTCDecodeFeaturesEXT                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->decodeModeSharedExponent            = pSource->decodeModeSharedExponent;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceASTCDecodeFeaturesEXT                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceASTCDecodeFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->decodeModeSharedExponent            = pSource->decodeModeSharedExponent;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceBlendOperationAdvancedFeatures ) * pDestination,
        VkPhysicalDeviceBlendOperationAdvancedFeaturesEXT                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->advancedBlendCoherentOperations            = pSource->advancedBlendCoherentOperations;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceBlendOperationAdvancedFeaturesEXT                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceBlendOperationAdvancedFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->advancedBlendCoherentOperations            = pSource->advancedBlendCoherentOperations;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BORDER_COLOR_SWIZZLE_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceBorderColorSwizzleFeatures ) * pDestination,
        VkPhysicalDeviceBorderColorSwizzleFeaturesEXT                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->borderColorSwizzle                = pSource->borderColorSwizzle;
    pDestination->borderColorSwizzleFromImage       = pSource->borderColorSwizzleFromImage;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceBorderColorSwizzleFeaturesEXT                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceBorderColorSwizzleFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->borderColorSwizzle                = pSource->borderColorSwizzle;
    pDestination->borderColorSwizzleFromImage       = pSource->borderColorSwizzleFromImage;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_COLOR_WRITE_ENABLE_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceColorWriteEnableFeatures ) * pDestination,
        VkPhysicalDeviceColorWriteEnableFeaturesEXT                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->colorWriteEnable                  = pSource->colorWriteEnable;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceColorWriteEnableFeaturesEXT                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceColorWriteEnableFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->colorWriteEnable                  = pSource->colorWriteEnable;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceConditionalRenderingFeatures ) * pDestination,
        VkPhysicalDeviceConditionalRenderingFeaturesEXT                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->conditionalRendering              = pSource->conditionalRendering;
    pDestination->inheritedConditionalRendering     = pSource->inheritedConditionalRendering;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceConditionalRenderingFeaturesEXT                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceConditionalRenderingFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->conditionalRendering              = pSource->conditionalRendering;
    pDestination->inheritedConditionalRendering     = pSource->inheritedConditionalRendering;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceCustomBorderColorFeatures ) * pDestination,
        VkPhysicalDeviceCustomBorderColorFeaturesEXT                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->customBorderColors                = pSource->customBorderColors;
    pDestination->customBorderColorWithoutFormat    = pSource->customBorderColorWithoutFormat;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceCustomBorderColorFeaturesEXT                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceCustomBorderColorFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->customBorderColors                = pSource->customBorderColors;
    pDestination->customBorderColorWithoutFormat    = pSource->customBorderColorWithoutFormat;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_CONTROL_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceDepthClipControlFeatures ) * pDestination,
        VkPhysicalDeviceDepthClipControlFeaturesEXT                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->depthClipControl                = pSource->depthClipControl;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceDepthClipControlFeaturesEXT                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceDepthClipControlFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->depthClipControl                = pSource->depthClipControl;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_ENABLE_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceDepthClipEnableFeatures ) * pDestination,
        VkPhysicalDeviceDepthClipEnableFeaturesEXT                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->depthClipEnable                = pSource->depthClipEnable;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceDepthClipEnableFeaturesEXT                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceDepthClipEnableFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->depthClipEnable                = pSource->depthClipEnable;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEVICE_MEMORY_REPORT_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceDeviceMemoryReportFeatures ) * pDestination,
        VkPhysicalDeviceDeviceMemoryReportFeaturesEXT                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->deviceMemoryReport                = pSource->deviceMemoryReport;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceDeviceMemoryReportFeaturesEXT                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceDeviceMemoryReportFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->deviceMemoryReport                = pSource->deviceMemoryReport;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceExtendedDynamicStateFeatures ) * pDestination,
        VkPhysicalDeviceExtendedDynamicStateFeaturesEXT                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->extendedDynamicState  = pSource->extendedDynamicState;
}

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceExtendedDynamicState2Features ) * pDestination,
        VkPhysicalDeviceExtendedDynamicState2FeaturesEXT                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->extendedDynamicState2                     = pSource->extendedDynamicState2;
    pDestination->extendedDynamicState2LogicOp              = pSource->extendedDynamicState2LogicOp;
    pDestination->extendedDynamicState2PatchControlPoints   = pSource->extendedDynamicState2PatchControlPoints;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceExtendedDynamicStateFeaturesEXT                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceExtendedDynamicStateFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->extendedDynamicState  = pSource->extendedDynamicState;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceExtendedDynamicState2FeaturesEXT                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceExtendedDynamicState2Features ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->extendedDynamicState2                     = pSource->extendedDynamicState2;
    pDestination->extendedDynamicState2LogicOp              = pSource->extendedDynamicState2LogicOp;
    pDestination->extendedDynamicState2PatchControlPoints   = pSource->extendedDynamicState2PatchControlPoints;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMapFeatures ) * pDestination,
        VkPhysicalDeviceFragmentDensityMapFeaturesEXT                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->fragmentDensityMap                    = pSource->fragmentDensityMap;
    pDestination->fragmentDensityMapDynamic             = pSource->fragmentDensityMapDynamic;
    pDestination->fragmentDensityMapNonSubsampledImages = pSource->fragmentDensityMapNonSubsampledImages;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceFragmentDensityMapFeaturesEXT                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMapFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->fragmentDensityMap                    = pSource->fragmentDensityMap;
    pDestination->fragmentDensityMapDynamic             = pSource->fragmentDensityMapDynamic;
    pDestination->fragmentDensityMapNonSubsampledImages = pSource->fragmentDensityMapNonSubsampledImages;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMap2Features ) * pDestination,
        VkPhysicalDeviceFragmentDensityMap2FeaturesEXT                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->fragmentDensityMapDeferred = pSource->fragmentDensityMapDeferred;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceFragmentDensityMap2FeaturesEXT                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMap2Features ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->fragmentDensityMapDeferred = pSource->fragmentDensityMapDeferred;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_SHADER_INTERLOCK_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceFragmentShaderInterlockFeatures ) * pDestination,
        VkPhysicalDeviceFragmentShaderInterlockFeaturesEXT                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->fragmentShaderSampleInterlock         = pSource->fragmentShaderSampleInterlock;
    pDestination->fragmentShaderPixelInterlock          = pSource->fragmentShaderPixelInterlock;
    pDestination->fragmentShaderShadingRateInterlock    = pSource->fragmentShaderShadingRateInterlock;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceFragmentShaderInterlockFeaturesEXT                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceFragmentShaderInterlockFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->fragmentShaderSampleInterlock         = pSource->fragmentShaderSampleInterlock;
    pDestination->fragmentShaderPixelInterlock          = pSource->fragmentShaderPixelInterlock;
    pDestination->fragmentShaderShadingRateInterlock    = pSource->fragmentShaderShadingRateInterlock;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceGlobalPriorityQueryFeatures ) * pDestination,
        VkPhysicalDeviceGlobalPriorityQueryFeaturesEXT                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->globalPriorityQuery         = pSource->globalPriorityQuery;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceGlobalPriorityQueryFeaturesEXT                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceGlobalPriorityQueryFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->globalPriorityQuery         = pSource->globalPriorityQuery;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_ROBUSTNESS_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceImageRobustnessFeatures ) * pDestination,
        VkPhysicalDeviceImageRobustnessFeatures_t                  const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->robustImageAccess         = pSource->robustImageAccess;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceImageRobustnessFeatures_t                              * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceImageRobustnessFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->robustImageAccess         = pSource->robustImageAccess;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_VIEW_MIN_LOD_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceImageViewMinLODFeatures ) * pDestination,
        VkPhysicalDeviceImageViewMinLodFeaturesEXT                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->minLOD         = pSource->minLod;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceImageViewMinLodFeaturesEXT                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceImageViewMinLODFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->minLod         = pSource->minLOD;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INDEX_TYPE_UINT8_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceIndexTypeUInt8Features ) * pDestination,
        VkPhysicalDeviceIndexTypeUint8FeaturesEXT                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->indexTypeUInt8         = pSource->indexTypeUint8;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceIndexTypeUint8FeaturesEXT                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceIndexTypeUInt8Features ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->indexTypeUint8         = pSource->indexTypeUInt8;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceInlineUniformBlockFeatures ) * pDestination,
        VkPhysicalDeviceInlineUniformBlockFeatures_t                  const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->inlineUniformBlock                                    = pSource->inlineUniformBlock;
    pDestination->descriptorBindingInlineUniformBlockUpdateAfterBind    = pSource->descriptorBindingInlineUniformBlockUpdateAfterBind;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceInlineUniformBlockFeatures_t                              * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceInlineUniformBlockFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->inlineUniformBlock                                    = pSource->inlineUniformBlock;
    pDestination->descriptorBindingInlineUniformBlockUpdateAfterBind    = pSource->descriptorBindingInlineUniformBlockUpdateAfterBind;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceLineRasterizationFeatures ) * pDestination,
        VkPhysicalDeviceLineRasterizationFeaturesEXT                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->rectangularLines          = pSource->rectangularLines;
    pDestination->bresenhamLines            = pSource->bresenhamLines;
    pDestination->smoothLines               = pSource->smoothLines;
    pDestination->stippledRectangularLines  = pSource->stippledRectangularLines;
    pDestination->stippledBresenhamLines    = pSource->stippledBresenhamLines;
    pDestination->stippledSmoothLines       = pSource->stippledSmoothLines;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceLineRasterizationFeaturesEXT                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceLineRasterizationFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->rectangularLines          = pSource->rectangularLines;
    pDestination->bresenhamLines            = pSource->bresenhamLines;
    pDestination->smoothLines               = pSource->smoothLines;
    pDestination->stippledRectangularLines  = pSource->stippledRectangularLines;
    pDestination->stippledBresenhamLines    = pSource->stippledBresenhamLines;
    pDestination->stippledSmoothLines       = pSource->stippledSmoothLines;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PAGEABLE_DEVICE_LOCAL_MEMORY_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDevicePageableDeviceLocalMemoryFeatures ) * pDestination,
        VkPhysicalDevicePageableDeviceLocalMemoryFeaturesEXT                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->pageableDeviceLocalMemory          = pSource->pageableDeviceLocalMemory;
}

inline static auto toVulkanFormat (
        VkPhysicalDevicePageableDeviceLocalMemoryFeaturesEXT                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDevicePageableDeviceLocalMemoryFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->pageableDeviceLocalMemory          = pSource->pageableDeviceLocalMemory;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_PRIORITY_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceMemoryPriorityFeatures ) * pDestination,
        VkPhysicalDeviceMemoryPriorityFeaturesEXT                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->memoryPriority          = pSource->memoryPriority;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceMemoryPriorityFeaturesEXT                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceMemoryPriorityFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->memoryPriority          = pSource->memoryPriority;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceMultiDrawFeatures ) * pDestination,
        VkPhysicalDeviceMultiDrawFeaturesEXT                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->multiDraw          = pSource->multiDraw;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceMultiDrawFeaturesEXT                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceMultiDrawFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->multiDraw          = pSource->multiDraw;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDevicePipelineCreationCacheControlFeatures ) * pDestination,
        VkPhysicalDevicePipelineCreationCacheControlFeatures_t                  const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->pipelineCreationCacheControl          = pSource->pipelineCreationCacheControl;
}

inline static auto toVulkanFormat (
        VkPhysicalDevicePipelineCreationCacheControlFeatures_t                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDevicePipelineCreationCacheControlFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->pipelineCreationCacheControl          = pSource->pipelineCreationCacheControl;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIMITIVE_TOPOLOGY_LIST_RESTART_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDevicePrimitiveTopologyListRestartFeatures ) * pDestination,
        VkPhysicalDevicePrimitiveTopologyListRestartFeaturesEXT                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->primitiveTopologyListRestart          = pSource->primitiveTopologyListRestart;
    pDestination->primitiveTopologyPatchListRestart     = pSource->primitiveTopologyPatchListRestart;
}

inline static auto toVulkanFormat (
        VkPhysicalDevicePrimitiveTopologyListRestartFeaturesEXT                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDevicePrimitiveTopologyListRestartFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->primitiveTopologyListRestart          = pSource->primitiveTopologyListRestart;
    pDestination->primitiveTopologyPatchListRestart     = pSource->primitiveTopologyPatchListRestart;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDevicePrivateDataFeatures ) * pDestination,
        VkPhysicalDevicePrivateDataFeatures_t                  const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->privateData          = pSource->privateData;
}

inline static auto toVulkanFormat (
        VkPhysicalDevicePrivateDataFeatures_t                              * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDevicePrivateDataFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->privateData          = pSource->privateData;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceProvokingVertexFeatures ) * pDestination,
        VkPhysicalDeviceProvokingVertexFeaturesEXT                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->provokingVertexLast                       = pSource->provokingVertexLast;
    pDestination->transformFeedbackPreservesProvokingVertex = pSource->transformFeedbackPreservesProvokingVertex;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceProvokingVertexFeaturesEXT                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceProvokingVertexFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->provokingVertexLast                       = pSource->provokingVertexLast;
    pDestination->transformFeedbackPreservesProvokingVertex = pSource->transformFeedbackPreservesProvokingVertex;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_RGBA_10_X_6_FORMATS_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceRGBA10x6FormatsFeatures ) * pDestination,
        VkPhysicalDeviceRGBA10X6FormatsFeaturesEXT                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->formatRGBA10x6WithoutYCBCRSampler                       = pSource->formatRgba10x6WithoutYCbCrSampler;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceRGBA10X6FormatsFeaturesEXT                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceRGBA10x6FormatsFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->formatRgba10x6WithoutYCbCrSampler                       = pSource->formatRGBA10x6WithoutYCBCRSampler;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceRobustnessFeatures ) * pDestination,
        VkPhysicalDeviceRobustness2FeaturesEXT                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->robustBufferAccess                        = pSource->robustBufferAccess2;
    pDestination->robustImageAccess                         = pSource->robustImageAccess2;
    pDestination->nullDescriptor                            = pSource->nullDescriptor;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceRobustness2FeaturesEXT                            * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceRobustnessFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->robustBufferAccess2                       = pSource->robustBufferAccess;
    pDestination->robustImageAccess2                        = pSource->robustImageAccess;
    pDestination->nullDescriptor                            = pSource->nullDescriptor;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderAtomicFloatFeatures ) * pDestination,
        VkPhysicalDeviceShaderAtomicFloatFeaturesEXT                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

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
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceShaderAtomicFloatFeaturesEXT                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderAtomicFloatFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

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
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_2_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderAtomicFloat2Features ) * pDestination,
        VkPhysicalDeviceShaderAtomicFloat2FeaturesEXT                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

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
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceShaderAtomicFloat2FeaturesEXT                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderAtomicFloat2Features ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

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
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_DEMOTE_TO_HELPER_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderDemoteToHelperInvocationFeatures ) * pDestination,
        VkPhysicalDeviceShaderDemoteToHelperInvocationFeatures_t                  const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->shaderDemoteToHelperInvocation    = pSource->shaderDemoteToHelperInvocation;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceShaderDemoteToHelperInvocationFeatures_t                              * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderDemoteToHelperInvocationFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->shaderDemoteToHelperInvocation    = pSource->shaderDemoteToHelperInvocation;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_IMAGE_ATOMIC_INT64_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderImageAtomicInt64Features ) * pDestination,
        VkPhysicalDeviceShaderImageAtomicInt64FeaturesEXT                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->shaderImageInt64Atomics    = pSource->shaderImageInt64Atomics;
    pDestination->sparseImageInt64Atomics    = pSource->sparseImageInt64Atomics;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceShaderImageAtomicInt64FeaturesEXT                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderImageAtomicInt64Features ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->shaderImageInt64Atomics    = pSource->shaderImageInt64Atomics;
    pDestination->sparseImageInt64Atomics    = pSource->sparseImageInt64Atomics;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceSubgroupSizeControlFeatures ) * pDestination,
        VkPhysicalDeviceSubgroupSizeControlFeatures_t                  const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->subgroupSizeControl       = pSource->subgroupSizeControl;
    pDestination->computeFullSubgroups      = pSource->computeFullSubgroups;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceSubgroupSizeControlFeatures_t                              * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceSubgroupSizeControlFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->subgroupSizeControl       = pSource->subgroupSizeControl;
    pDestination->computeFullSubgroups      = pSource->computeFullSubgroups;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceTexelBufferAlignmentFeatures ) * pDestination,
        VkPhysicalDeviceTexelBufferAlignmentFeatures_t                  const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->texelBufferAlignment       = pSource->texelBufferAlignment;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceTexelBufferAlignmentFeatures_t                              * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceTexelBufferAlignmentFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->texelBufferAlignment       = pSource->texelBufferAlignment;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXTURE_COMPRESSION_ASTC_HDR_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceTextureCompressionASTCHDRFeatures ) * pDestination,
        VkPhysicalDeviceTextureCompressionASTCHDRFeatures_t                  const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->textureCompressionASTCHDR       = pSource->textureCompressionASTC_HDR;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceTextureCompressionASTCHDRFeatures_t                              * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceTextureCompressionASTCHDRFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->textureCompressionASTC_HDR       = pSource->textureCompressionASTCHDR;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceTransformFeedbackFeatures ) * pDestination,
        VkPhysicalDeviceTransformFeedbackFeaturesEXT                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->transformFeedback         = pSource->transformFeedback;
    pDestination->geometryStreams           = pSource->geometryStreams;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceTransformFeedbackFeaturesEXT                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceTransformFeedbackFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->transformFeedback         = pSource->transformFeedback;
    pDestination->geometryStreams           = pSource->geometryStreams;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceVertexAttributeDivisorFeatures ) * pDestination,
        VkPhysicalDeviceVertexAttributeDivisorFeaturesEXT                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->vertexAttributeInstanceRateDivisor         = pSource->vertexAttributeInstanceRateDivisor;
    pDestination->vertexAttributeInstanceRateZeroDivisor     = pSource->vertexAttributeInstanceRateZeroDivisor;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceVertexAttributeDivisorFeaturesEXT                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceVertexAttributeDivisorFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->vertexAttributeInstanceRateDivisor         = pSource->vertexAttributeInstanceRateDivisor;
    pDestination->vertexAttributeInstanceRateZeroDivisor     = pSource->vertexAttributeInstanceRateZeroDivisor;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_INPUT_DYNAMIC_STATE_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceVertexInputDynamicStateFeatures ) * pDestination,
        VkPhysicalDeviceVertexInputDynamicStateFeaturesEXT                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->vertexInputDynamicState         = pSource->vertexInputDynamicState;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceVertexInputDynamicStateFeaturesEXT                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceVertexInputDynamicStateFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->vertexInputDynamicState         = pSource->vertexInputDynamicState;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_2_PLANE_444_FORMATS_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceYCBCR2Plane444FormatsFeatures ) * pDestination,
        VkPhysicalDeviceYcbcr2Plane444FormatsFeaturesEXT                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->YCBCR2Plane444Formats         = pSource->ycbcr2plane444Formats;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceYcbcr2Plane444FormatsFeaturesEXT                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceYCBCR2Plane444FormatsFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->ycbcr2plane444Formats         = pSource->YCBCR2Plane444Formats;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_IMAGE_ARRAYS_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceYCBCRImageArraysFeatures ) * pDestination,
        VkPhysicalDeviceYcbcrImageArraysFeaturesEXT                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->YCBCRImageArrays         = pSource->ycbcrImageArrays;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceYcbcrImageArraysFeaturesEXT                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceYCBCRImageArraysFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->ycbcrImageArrays         = pSource->YCBCRImageArrays;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceBlendOperationAdvancedProperties ) * pOut,
        VkPhysicalDeviceBlendOperationAdvancedPropertiesEXT                 const * pIn
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

#endif

    pOut->maxCustomBorderColorSamplers                  = pIn->maxCustomBorderColorSamplers;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISCARD_RECTANGLES_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceDiscardRectangleProperties ) * pOut,
        VkPhysicalDeviceDiscardRectanglePropertiesEXT                 const * pIn
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

#endif

    pOut->maxDiscardRectangles                  = pIn->maxDiscardRectangles;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTERNAL_MEMORY_HOST_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceExternalMemoryHostProperties ) * pOut,
        VkPhysicalDeviceExternalMemoryHostPropertiesEXT                 const * pIn
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

#endif

    pOut->minImportedHostPointerAlignment                  = pIn->minImportedHostPointerAlignment;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMapProperties ) * pOut,
        VkPhysicalDeviceFragmentDensityMapPropertiesEXT                 const * pIn
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

#endif

    pOut->subsampledLoads                           = pIn->subsampledLoads;
    pOut->subsampledCoarseReconstructionEarlyAccess = pIn->subsampledCoarseReconstructionEarlyAccess;
    pOut->maxSubsampledArrayLayers                  = pIn->maxSubsampledArrayLayers;
    pOut->maxDescriptorSetSubsampledSamplers        = pIn->maxDescriptorSetSubsampledSamplers;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceInlineUniformBlockProperties ) * pOut,
        VkPhysicalDeviceInlineUniformBlockProperties_t                  const * pIn
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

#endif

    pOut->lineSubPixelPrecisionBits                                 = pIn->lineSubPixelPrecisionBits;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceMultiDrawProperties ) * pOut,
        VkPhysicalDeviceMultiDrawPropertiesEXT                 const * pIn
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

#endif

    pOut->maxMultiDrawCount                                 = pIn->maxMultiDrawCount;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PCI_BUS_INFO_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDevicePCIBusInfoProperties ) * pOut,
        VkPhysicalDevicePCIBusInfoPropertiesEXT                 const * pIn
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

#endif

    pOut->provokingVertexModePerPipeline                        = pIn->provokingVertexModePerPipeline;
    pOut->transformFeedbackPreservesTriangleFanProvokingVertex  = pIn->transformFeedbackPreservesTriangleFanProvokingVertex;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceRobustnessProperties ) * pOut,
        VkPhysicalDeviceRobustness2PropertiesEXT                const * pIn
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

#endif

    pOut->robustStorageBufferAccessSizeAlignment                        = pIn->robustStorageBufferAccessSizeAlignment;
    pOut->robustUniformBufferAccessSizeAlignment                        = pIn->robustUniformBufferAccessSizeAlignment;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceSampleLocationsProperties ) * pOut,
        VkPhysicalDeviceSampleLocationsPropertiesEXT                 const * pIn
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

#endif

    pOut->sampleLocationSampleCounts                        = pIn->sampleLocationSampleCounts;
    pOut->maxSampleLocationGridSize                         = pIn->maxSampleLocationGridSize;
    pOut->sampleLocationSubPixelBits                        = pIn->sampleLocationSubPixelBits;
    pOut->variableSampleLocations                           = pIn->variableSampleLocations;

    pOut->sampleLocationCoordinateRange[0]                  = pIn->sampleLocationCoordinateRange[0];
    pOut->sampleLocationCoordinateRange[1]                  = pIn->sampleLocationCoordinateRange[1];
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceSubgroupSizeControlProperties ) * pOut,
        VkPhysicalDeviceSubgroupSizeControlProperties_t                  const * pIn
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

#endif

    pOut->minSubgroupSize                               = pIn->minSubgroupSize;
    pOut->maxSubgroupSize                               = pIn->maxSubgroupSize;
    pOut->maxComputeWorkgroupSubgroups                  = pIn->maxComputeWorkgroupSubgroups;
    pOut->requiredSubgroupSizeStages                    = pIn->requiredSubgroupSizeStages;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceTexelBufferAlignmentProperties ) * pOut,
        VkPhysicalDeviceTexelBufferAlignmentProperties_t                  const * pIn
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

#endif

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

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceMaintenance4Properties ) * pOut,
        VkPhysicalDeviceMaintenance4Properties_t                  const * pIn
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

#endif

    pOut->maxBufferSize                 = pIn->maxBufferSize;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDevicePerformanceQueryProperties ) * pOut,
        VkPhysicalDevicePerformanceQueryPropertiesKHR                 const * pIn
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

#endif

    pOut->allowCommandBufferQueryCopies                 = pIn->allowCommandBufferQueryCopies;
}

#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDevicePortabilitySubsetProperties ) * pOut,
        VkPhysicalDevicePortabilitySubsetPropertiesKHR                 const * pIn
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

#endif

    pOut->minVertexInputBindingStrideAlignment                 = pIn->minVertexInputBindingStrideAlignment;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PUSH_DESCRIPTOR_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDevicePushDescriptorProperties ) * pOut,
        VkPhysicalDevicePushDescriptorPropertiesKHR                 const * pIn
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

#endif

    pOut->maxPushDescriptors                 = pIn->maxPushDescriptors;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceRayTracingPipelineProperties ) * pOut,
        VkPhysicalDeviceRayTracingPipelinePropertiesKHR                 const * pIn
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

#endif

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

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderIntegerDotProductProperties ) * pOut,
        VkPhysicalDeviceShaderIntegerDotProductProperties_t                  const * pIn
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

#endif

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

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceAccelerationStructureFeatures ) * pDestination,
        VkPhysicalDeviceAccelerationStructureFeaturesKHR                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->accelerationStructure                                 = pSource->accelerationStructure;
    pDestination->accelerationStructureCaptureReplay                    = pSource->accelerationStructureCaptureReplay;
    pDestination->accelerationStructureIndirectBuild                    = pSource->accelerationStructureIndirectBuild;
    pDestination->accelerationStructureHostCommands                     = pSource->accelerationStructureHostCommands;
    pDestination->descriptorBindingAccelerationStructureUpdateAfterBind = pSource->descriptorBindingAccelerationStructureUpdateAfterBind;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceAccelerationStructureFeaturesKHR                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceAccelerationStructureFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->accelerationStructure                                 = pSource->accelerationStructure;
    pDestination->accelerationStructureCaptureReplay                    = pSource->accelerationStructureCaptureReplay;
    pDestination->accelerationStructureIndirectBuild                    = pSource->accelerationStructureIndirectBuild;
    pDestination->accelerationStructureHostCommands                     = pSource->accelerationStructureHostCommands;
    pDestination->descriptorBindingAccelerationStructureUpdateAfterBind = pSource->descriptorBindingAccelerationStructureUpdateAfterBind;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceDynamicRenderingFeatures ) * pDestination,
        VkPhysicalDeviceDynamicRenderingFeatures_t                  const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->dynamicRendering                                 = pSource->dynamicRendering;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceDynamicRenderingFeatures_t                              * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceDynamicRenderingFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->dynamicRendering                                 = pSource->dynamicRendering;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceFragmentShadingRateFeatures ) * pDestination,
        VkPhysicalDeviceFragmentShadingRateFeaturesKHR                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->pipelineFragmentShadingRate   = pSource->pipelineFragmentShadingRate;
    pDestination->primitiveFragmentShadingRate  = pSource->primitiveFragmentShadingRate;
    pDestination->attachmentFragmentShadingRate = pSource->attachmentFragmentShadingRate;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceFragmentShadingRateFeaturesKHR                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceFragmentShadingRateFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->pipelineFragmentShadingRate   = pSource->pipelineFragmentShadingRate;
    pDestination->primitiveFragmentShadingRate  = pSource->primitiveFragmentShadingRate;
    pDestination->attachmentFragmentShadingRate = pSource->attachmentFragmentShadingRate;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceMaintenance4Features ) * pDestination,
        VkPhysicalDeviceMaintenance4Features_t                  const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->maintenance4   = pSource->maintenance4;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceMaintenance4Features_t                              * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceMaintenance4Features ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->maintenance4   = pSource->maintenance4;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDevicePerformanceQueryFeatures ) * pDestination,
        VkPhysicalDevicePerformanceQueryFeaturesKHR                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->performanceCounterQueryPools          = pSource->performanceCounterQueryPools;
    pDestination->performanceCounterMultipleQueryPools  = pSource->performanceCounterMultipleQueryPools;
}

inline static auto toVulkanFormat (
        VkPhysicalDevicePerformanceQueryFeaturesKHR                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDevicePerformanceQueryFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->performanceCounterQueryPools          = pSource->performanceCounterQueryPools;
    pDestination->performanceCounterMultipleQueryPools  = pSource->performanceCounterMultipleQueryPools;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDevicePipelineExecutablePropertiesFeatures ) * pDestination,
        VkPhysicalDevicePipelineExecutablePropertiesFeaturesKHR                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->pipelineExecutableInfo          = pSource->pipelineExecutableInfo;
}

inline static auto toVulkanFormat (
        VkPhysicalDevicePipelineExecutablePropertiesFeaturesKHR                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDevicePipelineExecutablePropertiesFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->pipelineExecutableInfo          = pSource->pipelineExecutableInfo;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_ID_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDevicePresentIDFeatures ) * pDestination,
        VkPhysicalDevicePresentIdFeaturesKHR                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->presentID          = pSource->presentId;
}

inline static auto toVulkanFormat (
        VkPhysicalDevicePresentIdFeaturesKHR                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDevicePresentIDFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->presentId          = pSource->presentID;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_WAIT_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDevicePresentWaitFeatures ) * pDestination,
        VkPhysicalDevicePresentWaitFeaturesKHR                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->presentWait          = pSource->presentWait;
}

inline static auto toVulkanFormat (
        VkPhysicalDevicePresentWaitFeaturesKHR                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDevicePresentWaitFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->presentWait          = pSource->presentWait;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_QUERY_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceRayQueryFeatures ) * pDestination,
        VkPhysicalDeviceRayQueryFeaturesKHR                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->rayQuery          = pSource->rayQuery;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceRayQueryFeaturesKHR                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceRayQueryFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->rayQuery          = pSource->rayQuery;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_CLOCK_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderClockFeatures ) * pDestination,
        VkPhysicalDeviceShaderClockFeaturesKHR                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->shaderSubgroupClock           = pSource->shaderSubgroupClock;
    pDestination->shaderDeviceClock             = pSource->shaderDeviceClock;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceShaderClockFeaturesKHR                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderClockFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->shaderSubgroupClock           = pSource->shaderSubgroupClock;
    pDestination->shaderDeviceClock             = pSource->shaderDeviceClock;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceRayTracingPipelineFeatures ) * pDestination,
        VkPhysicalDeviceRayTracingPipelineFeaturesKHR                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->rayTracingPipeline                                    = pSource->rayTracingPipeline;
    pDestination->rayTracingPipelineShaderGroupHandleCaptureReplay      = pSource->rayTracingPipelineShaderGroupHandleCaptureReplay;
    pDestination->rayTracingPipelineShaderGroupHandleCaptureReplayMixed = pSource->rayTracingPipelineShaderGroupHandleCaptureReplayMixed;
    pDestination->rayTracingPipelineTraceRaysIndirect                   = pSource->rayTracingPipelineTraceRaysIndirect;
    pDestination->rayTraversalPrimitiveCulling                          = pSource->rayTraversalPrimitiveCulling;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceRayTracingPipelineFeaturesKHR                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceRayTracingPipelineFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->rayTracingPipeline                                    = pSource->rayTracingPipeline;
    pDestination->rayTracingPipelineShaderGroupHandleCaptureReplay      = pSource->rayTracingPipelineShaderGroupHandleCaptureReplay;
    pDestination->rayTracingPipelineShaderGroupHandleCaptureReplayMixed = pSource->rayTracingPipelineShaderGroupHandleCaptureReplayMixed;
    pDestination->rayTracingPipelineTraceRaysIndirect                   = pSource->rayTracingPipelineTraceRaysIndirect;
    pDestination->rayTraversalPrimitiveCulling                          = pSource->rayTraversalPrimitiveCulling;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_SUBGROUP_UNIFORM_CONTROL_FLOW_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderSubgroupUniformControlFlowFeatures ) * pDestination,
        VkPhysicalDeviceShaderSubgroupUniformControlFlowFeaturesKHR                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->shaderSubgroupUniformControlFlow  = pSource->shaderSubgroupUniformControlFlow;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceShaderSubgroupUniformControlFlowFeaturesKHR                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderSubgroupUniformControlFlowFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->shaderSubgroupUniformControlFlow  = pSource->shaderSubgroupUniformControlFlow;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_TERMINATE_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderTerminateInvocationFeatures ) * pDestination,
        VkPhysicalDeviceShaderTerminateInvocationFeatures_t                  const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->shaderTerminateInvocation  = pSource->shaderTerminateInvocation;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceShaderTerminateInvocationFeatures_t                              * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderTerminateInvocationFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->shaderTerminateInvocation  = pSource->shaderTerminateInvocation;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceSynchronizationFeatures )  * pDestination,
        VkPhysicalDeviceSynchronization2Features_t                  const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->synchronization  = pSource->synchronization2;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceSynchronization2Features_t                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceSynchronizationFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->synchronization2  = pSource->synchronization;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderIntegerDotProductFeatures ) * pDestination,
        VkPhysicalDeviceShaderIntegerDotProductFeatures_t                  const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->shaderIntegerDotProduct  = pSource->shaderIntegerDotProduct;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceShaderIntegerDotProductFeatures_t                              * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderIntegerDotProductFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->shaderIntegerDotProduct  = pSource->shaderIntegerDotProduct;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceWorkgroupMemoryExplicitLayoutFeatures ) * pDestination,
        VkPhysicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR                 const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->workgroupMemoryExplicitLayout                     = pSource->workgroupMemoryExplicitLayout;
    pDestination->workgroupMemoryExplicitLayoutScalarBlockLayout    = pSource->workgroupMemoryExplicitLayoutScalarBlockLayout;
    pDestination->workgroupMemoryExplicitLayout8BitAccess           = pSource->workgroupMemoryExplicitLayout8BitAccess;
    pDestination->workgroupMemoryExplicitLayout16BitAccess          = pSource->workgroupMemoryExplicitLayout16BitAccess;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR                             * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceWorkgroupMemoryExplicitLayoutFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->workgroupMemoryExplicitLayout                     = pSource->workgroupMemoryExplicitLayout;
    pDestination->workgroupMemoryExplicitLayoutScalarBlockLayout    = pSource->workgroupMemoryExplicitLayoutScalarBlockLayout;
    pDestination->workgroupMemoryExplicitLayout8BitAccess           = pSource->workgroupMemoryExplicitLayout8BitAccess;
    pDestination->workgroupMemoryExplicitLayout16BitAccess          = pSource->workgroupMemoryExplicitLayout16BitAccess;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ZERO_INITIALIZE_WORKGROUP_MEMORY_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceZeroInitializeWorkgroupMemoryFeatures ) * pDestination,
        VkPhysicalDeviceZeroInitializeWorkgroupMemoryFeatures_t                  const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->shaderZeroInitializeWorkgroupMemory   = pSource->shaderZeroInitializeWorkgroupMemory;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceZeroInitializeWorkgroupMemoryFeatures_t                              * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceZeroInitializeWorkgroupMemoryFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->shaderZeroInitializeWorkgroupMemory   = pSource->shaderZeroInitializeWorkgroupMemory;
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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

#endif

    pOut->cooperativeMatrixSupportedStages        = pIn->cooperativeMatrixSupportedStages;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceDeviceGeneratedCommandsPropertiesNVidia ) * pOut,
        VkPhysicalDeviceDeviceGeneratedCommandsPropertiesNV                        const * pIn
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

#endif

    pOut->maxFragmentShadingRateInvocationCount  = static_cast < vulkan :: __C_ENG_TYPE ( SampleCountFlag ) > ( pIn->maxFragmentShadingRateInvocationCount );
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceMeshShaderPropertiesNVidia ) * pOut,
        VkPhysicalDeviceMeshShaderPropertiesNV                        const * pIn
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

#endif

    pOut->shaderSMCount         = pIn->shaderSMCount;
    pOut->shaderWarpsPerSM      = pIn->shaderWarpsPerSM;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceShadingRateImagePropertiesNVidia ) * pOut,
        VkPhysicalDeviceShadingRateImagePropertiesNV                        const * pIn
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

#endif

    pOut->perViewPositionAllComponents   = pIn->perViewPositionAllComponents;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COMPUTE_SHADER_DERIVATIVES_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceComputeShaderDerivativesFeaturesNVidia ) * pDestination,
        VkPhysicalDeviceComputeShaderDerivativesFeaturesNV                        const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->computeDerivativeGroupQuads       = pSource->computeDerivativeGroupQuads;
    pDestination->computeDerivativeGroupLinear      = pSource->computeDerivativeGroupLinear;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceComputeShaderDerivativesFeaturesNV                                    * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceComputeShaderDerivativesFeaturesNVidia ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->computeDerivativeGroupQuads       = pSource->computeDerivativeGroupQuads;
    pDestination->computeDerivativeGroupLinear      = pSource->computeDerivativeGroupLinear;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceCooperativeMatrixFeaturesNVidia ) * pDestination,
        VkPhysicalDeviceCooperativeMatrixFeaturesNV                        const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->cooperativeMatrix                     = pSource->cooperativeMatrix;
    pDestination->cooperativeMatrixRobustBufferAccess   = pSource->cooperativeMatrixRobustBufferAccess;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceCooperativeMatrixFeaturesNV                                    * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceCooperativeMatrixFeaturesNVidia ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->cooperativeMatrix                     = pSource->cooperativeMatrix;
    pDestination->cooperativeMatrixRobustBufferAccess   = pSource->cooperativeMatrixRobustBufferAccess;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CORNER_SAMPLED_IMAGE_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceCornerSampledImageFeaturesNVidia ) * pDestination,
        VkPhysicalDeviceCornerSampledImageFeaturesNV                        const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->cornerSampledImage                     = pSource->cornerSampledImage;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceCornerSampledImageFeaturesNV                                    * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceCornerSampledImageFeaturesNVidia ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->cornerSampledImage                     = pSource->cornerSampledImage;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COVERAGE_REDUCTION_MODE_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceCoverageReductionModeFeaturesNVidia ) * pDestination,
        VkPhysicalDeviceCoverageReductionModeFeaturesNV                        const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->coverageReductionMode = pSource->coverageReductionMode;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceCoverageReductionModeFeaturesNV                                    * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceCoverageReductionModeFeaturesNVidia ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->coverageReductionMode = pSource->coverageReductionMode;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceDeviceGeneratedCommandsFeaturesNVidia ) * pDestination,
        VkPhysicalDeviceDeviceGeneratedCommandsFeaturesNV                        const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->deviceGeneratedCommands = pSource->deviceGeneratedCommands;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceDeviceGeneratedCommandsFeaturesNV                                    * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceDeviceGeneratedCommandsFeaturesNVidia ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->deviceGeneratedCommands = pSource->deviceGeneratedCommands;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_IMAGE_ALIASING_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNVidia ) * pDestination,
        VkPhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV                        const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->dedicatedAllocationImageAliasing = pSource->dedicatedAllocationImageAliasing;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV                                    * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNVidia ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->dedicatedAllocationImageAliasing = pSource->dedicatedAllocationImageAliasing;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTICS_CONFIG_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceDiagnosticsConfigFeaturesNVidia ) * pDestination,
        VkPhysicalDeviceDiagnosticsConfigFeaturesNV                        const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->diagnosticsConfig = pSource->diagnosticsConfig;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceDiagnosticsConfigFeaturesNV                                    * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceDiagnosticsConfigFeaturesNVidia ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->diagnosticsConfig = pSource->diagnosticsConfig;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SCISSOR_EXCLUSIVE_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceExclusiveScissorFeaturesNVidia ) * pDestination,
        VkPhysicalDeviceExclusiveScissorFeaturesNV                        const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->exclusiveScissor = pSource->exclusiveScissor;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceExclusiveScissorFeaturesNV                                    * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceExclusiveScissorFeaturesNVidia ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->exclusiveScissor = pSource->exclusiveScissor;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_RDMA_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceExternalMemoryRDMAFeaturesNVidia ) * pDestination,
        VkPhysicalDeviceExternalMemoryRDMAFeaturesNV                        const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->externalMemoryRDMA = pSource->externalMemoryRDMA;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceExternalMemoryRDMAFeaturesNV                                    * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceExternalMemoryRDMAFeaturesNVidia ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->externalMemoryRDMA = pSource->externalMemoryRDMA;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADER_BARYCENTRIC_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceFragmentShaderBarycentricFeaturesNVidia ) * pDestination,
        VkPhysicalDeviceFragmentShaderBarycentricFeaturesNV                        const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->fragmentShaderBarycentric = pSource->fragmentShaderBarycentric;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceFragmentShaderBarycentricFeaturesNV                                    * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceFragmentShaderBarycentricFeaturesNVidia ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->fragmentShaderBarycentric = pSource->fragmentShaderBarycentric;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceFragmentShadingRateEnumsFeaturesNVidia ) * pDestination,
        VkPhysicalDeviceFragmentShadingRateEnumsFeaturesNV                        const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->fragmentShadingRateEnums          = pSource->fragmentShadingRateEnums;
    pDestination->supersampleFragmentShadingRates   = pSource->supersampleFragmentShadingRates;
    pDestination->noInvocationFragmentShadingRates  = pSource->noInvocationFragmentShadingRates;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceFragmentShadingRateEnumsFeaturesNV                                    * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceFragmentShadingRateEnumsFeaturesNVidia ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->fragmentShadingRateEnums          = pSource->fragmentShadingRateEnums;
    pDestination->supersampleFragmentShadingRates   = pSource->supersampleFragmentShadingRates;
    pDestination->noInvocationFragmentShadingRates  = pSource->noInvocationFragmentShadingRates;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_INHERITED_VIEWPORT_SCISSOR_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceInheritedViewportScissorFeaturesNVidia ) * pDestination,
        VkPhysicalDeviceInheritedViewportScissorFeaturesNV                        const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->inheritedViewportScissor2D          = pSource->inheritedViewportScissor2D;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceInheritedViewportScissorFeaturesNV                                    * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceInheritedViewportScissorFeaturesNVidia ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->inheritedViewportScissor2D          = pSource->inheritedViewportScissor2D;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_LINEAR_COLOR_ATTACHMENT_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceLinearColorAttachmentFeaturesNVidia ) * pDestination,
        VkPhysicalDeviceLinearColorAttachmentFeaturesNV                        const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->linearColorAttachment          = pSource->linearColorAttachment;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceLinearColorAttachmentFeaturesNV                                    * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceLinearColorAttachmentFeaturesNVidia ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->linearColorAttachment          = pSource->linearColorAttachment;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceMeshShaderFeaturesNVidia ) * pDestination,
        VkPhysicalDeviceMeshShaderFeaturesNV                        const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->taskShader          = pSource->taskShader;
    pDestination->meshShader          = pSource->meshShader;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceMeshShaderFeaturesNV                                    * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceMeshShaderFeaturesNVidia ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->taskShader          = pSource->taskShader;
    pDestination->meshShader          = pSource->meshShader;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceRayTracingMotionBlurFeaturesNVidia ) * pDestination,
        VkPhysicalDeviceRayTracingMotionBlurFeaturesNV                        const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->rayTracingMotionBlur                          = pSource->rayTracingMotionBlur;
    pDestination->rayTracingMotionBlurPipelineTraceRaysIndirect = pSource->rayTracingMotionBlurPipelineTraceRaysIndirect;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceRayTracingMotionBlurFeaturesNV                                    * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceRayTracingMotionBlurFeaturesNVidia ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->rayTracingMotionBlur                          = pSource->rayTracingMotionBlur;
    pDestination->rayTracingMotionBlurPipelineTraceRaysIndirect = pSource->rayTracingMotionBlurPipelineTraceRaysIndirect;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_REPRESENTATIVE_FRAGMENT_TEST_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceRepresentativeFragmentTestFeaturesNVidia ) * pDestination,
        VkPhysicalDeviceRepresentativeFragmentTestFeaturesNV                        const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->representativeFragmentTest  = pSource->representativeFragmentTest;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceRepresentativeFragmentTestFeaturesNV                                    * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceRepresentativeFragmentTestFeaturesNVidia ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->representativeFragmentTest  = pSource->representativeFragmentTest;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_IMAGE_FOOTPRINT_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderImageFootprintFeaturesNVidia ) * pDestination,
        VkPhysicalDeviceShaderImageFootprintFeaturesNV                        const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->imageFootprint  = pSource->imageFootprint;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceShaderImageFootprintFeaturesNV                                    * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderImageFootprintFeaturesNVidia ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->imageFootprint  = pSource->imageFootprint;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderSMBuiltinsFeaturesNVidia ) * pDestination,
        VkPhysicalDeviceShaderSMBuiltinsFeaturesNV                        const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->shaderSMBuiltins  = pSource->shaderSMBuiltins;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceShaderSMBuiltinsFeaturesNV                                    * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderSMBuiltinsFeaturesNVidia ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->shaderSMBuiltins  = pSource->shaderSMBuiltins;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceShadingRateImageFeaturesNVidia ) * pDestination,
        VkPhysicalDeviceShadingRateImageFeaturesNV                        const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->shadingRateImage              = pSource->shadingRateImage;
    pDestination->shadingRateCoarseSampleOrder  = pSource->shadingRateCoarseSampleOrder;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceShadingRateImageFeaturesNV                                    * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceShadingRateImageFeaturesNVidia ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->shadingRateImage              = pSource->shadingRateImage;
    pDestination->shadingRateCoarseSampleOrder  = pSource->shadingRateCoarseSampleOrder;
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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

#endif

    pOut->shaderCoreFeatures            = pIn->shaderCoreFeatures;
    pOut->activeComputeUnitCount        = pIn->activeComputeUnitCount;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_DEVICE_COHERENT_MEMORY_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceCoherentMemoryFeaturesAMD ) * pDestination,
        VkPhysicalDeviceCoherentMemoryFeaturesAMD                    const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->deviceCoherentMemory    = pSource->deviceCoherentMemory;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceCoherentMemoryFeaturesAMD                                * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceCoherentMemoryFeaturesAMD ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->deviceCoherentMemory    = pSource->deviceCoherentMemory;
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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

#endif

    pOut->fragmentDensityOffsetGranularity        = pIn->fragmentDensityOffsetGranularity;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMapOffsetFeaturesQualcomm ) * pDestination,
        VkPhysicalDeviceFragmentDensityMapOffsetFeaturesQCOM                        const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->fragmentDensityMapOffset    = pSource->fragmentDensityMapOffset;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceFragmentDensityMapOffsetFeaturesQCOM                                    * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMapOffsetFeaturesQualcomm ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->fragmentDensityMapOffset    = pSource->fragmentDensityMapOffset;
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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pIn == nullptr || pOut == nullptr ) {
        return;
    }

#endif

    pOut->maxSubpassShadingWorkgroupSizeAspectRatio        = pIn->maxSubpassShadingWorkgroupSizeAspectRatio;
}

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceSubpassShadingFeaturesHuawei ) * pDestination,
        VkPhysicalDeviceSubpassShadingFeaturesHUAWEI                    const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->subpassShading        = pSource->subpassShading;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceSubpassShadingFeaturesHUAWEI                                * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceSubpassShadingFeaturesHuawei ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->subpassShading        = pSource->subpassShading;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_INVOCATION_MASK_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceInvocationMaskFeaturesHuawei )     * pDestination,
        VkPhysicalDeviceInvocationMaskFeaturesHUAWEI                        const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->invocationMask    = pSource->invocationMask;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceInvocationMaskFeaturesHUAWEI                                * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceInvocationMaskFeaturesHuawei ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->invocationMask    = pSource->invocationMask;
}

#endif


/**
 * --------------------------------------------------------------
 * --------------------------------------------------------------
 * ---- Vulkan Valve Extensions Device Properties Converters ----
 * --------------------------------------------------------------
 * --------------------------------------------------------------
 */
#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceMutableDescriptorTypeFeaturesValve ) * pDestination,
        VkPhysicalDeviceMutableDescriptorTypeFeaturesVALVE                    const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->mutableDescriptorType    = pSource->mutableDescriptorType;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceMutableDescriptorTypeFeaturesVALVE                                * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceMutableDescriptorTypeFeaturesValve ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->mutableDescriptorType    = pSource->mutableDescriptorType;
}

#endif


/**
 * --------------------------------------------------------------
 * --------------------------------------------------------------
 * ---- Vulkan Intel Extensions Device Properties Converters ----
 * --------------------------------------------------------------
 * --------------------------------------------------------------
 */
#if __C_ENG_VULKAN_API_EXTENSION_INTEL_SHADER_INTEGER_FUNCTIONS_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderIntegerFunctionsFeaturesIntel )  * pDestination,
        VkPhysicalDeviceShaderIntegerFunctions2FeaturesINTEL                    const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->shaderIntegerFunctions    = pSource->shaderIntegerFunctions2;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceShaderIntegerFunctions2FeaturesINTEL                               * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderIntegerFunctionsFeaturesIntel ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->shaderIntegerFunctions2    = pSource->shaderIntegerFunctions;
}

#endif


/**
 * ------------------------------------------------------------
 * ------------------------------------------------------------
 * ---- Vulkan ARM Extensions Device Properties Converters ----
 * ------------------------------------------------------------
 * ------------------------------------------------------------
 */
#if __C_ENG_VULKAN_API_EXTENSION_ARM_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_AVAILABLE

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM )  * pDestination,
        VkPhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM                     const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->rasterizationOrderColorAttachmentAccess       = pSource->rasterizationOrderColorAttachmentAccess;
    pDestination->rasterizationOrderDepthAttachmentAccess       = pSource->rasterizationOrderDepthAttachmentAccess;
    pDestination->rasterizationOrderStencilAttachmentAccess     = pSource->rasterizationOrderStencilAttachmentAccess;
}

inline static auto toVulkanFormat (
        VkPhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM                                * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->rasterizationOrderColorAttachmentAccess       = pSource->rasterizationOrderColorAttachmentAccess;
    pDestination->rasterizationOrderDepthAttachmentAccess       = pSource->rasterizationOrderDepthAttachmentAccess;
    pDestination->rasterizationOrderStencilAttachmentAccess     = pSource->rasterizationOrderStencilAttachmentAccess;
}

#endif



inline static auto toVulkanFormat (
        vulkan :: __C_ENG_TYPE ( ApplicationInfo )  const * pApplicationInfo,
        VkApplicationInfo                                 * pVkApplicationInfo
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pApplicationInfo == nullptr || pVkApplicationInfo == nullptr ) {
        return;
    }

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pAllocationCallbacks == nullptr || pVkAllocationCallbacks == nullptr ) {
        return;
    }

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pCreateInfo == nullptr || pVkCreateInfo == nullptr ) {
        return;
    }

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pCreateInfo == nullptr || pVkCreateInfo == nullptr ) {
        return;
    }

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pValidationFeatures == nullptr || pVkValidationFeatures == nullptr ) {
        return;
    }

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pOutRawVersion == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    __C_ENG_LOOKUP_VULKAN_FUNCTION (
            pVkEnumerateInstanceVersion,
            ENUMERATE_INSTANCE_VERSION
    )

    return static_cast < vulkan :: __C_ENG_TYPE ( Result ) > (
            pVkEnumerateInstanceVersion (
                    pOutRawVersion
            )
    );
}

auto vulkan :: enumerateInstanceLayerProperties (
        uint32                              * pLayerPropertiesCount,
        __C_ENG_TYPE ( LayerProperties )    * pProperties
) noexcept -> __C_ENG_TYPE ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pLayerPropertiesCount == nullptr ) {
        return __C_ENG_TYPE ( Result ) :: ResultErrorIllegalArgument;
    }

#endif

    __C_ENG_LOOKUP_VULKAN_FUNCTION (
            pVkEnumerateInstanceLayerProperties,
            ENUMERATE_INSTANCE_LAYER_PROPERTIES
    )

    if ( pProperties == nullptr ) {
        return static_cast < __C_ENG_TYPE ( Result ) > (
                pVkEnumerateInstanceLayerProperties (
                    pLayerPropertiesCount,
                    nullptr
                )
        );
    }

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( * pLayerPropertiesCount > __C_ENG_VULKAN_CORE_LAYER_MAX_COUNT ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

    result = pVkEnumerateInstanceLayerProperties (
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

__C_ENG_MAYBE_UNUSED auto vulkan :: enumeratePhysicalDeviceLayerProperties (
        __C_ENG_TYPE ( PhysicalDeviceHandle )   handle,
        uint32                                * pLayerPropertiesCount,
        __C_ENG_TYPE ( LayerProperties )      * pProperties
) noexcept -> __C_ENG_TYPE ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if (
            handle                  == nullptr ||
            pLayerPropertiesCount   == nullptr
    ) {
        return __C_ENG_TYPE ( Result ) :: ResultErrorIllegalArgument;
    }

#endif

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION (
            lastCreatedInstance,
            pVkEnumerateDeviceLayerProperties,
            ENUMERATE_DEVICE_LAYER_PROPERTIES
    )

    if ( pProperties == nullptr ) {
        return static_cast < __C_ENG_TYPE ( Result ) > (
                pVkEnumerateDeviceLayerProperties (
                        handle,
                        pLayerPropertiesCount,
                        nullptr
                )
        );
    }

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( * pLayerPropertiesCount > __C_ENG_VULKAN_CORE_LAYER_MAX_COUNT ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

    result = pVkEnumerateDeviceLayerProperties (
            handle,
            pLayerPropertiesCount,
            & layerProperties[0]
    );

    if ( result != VkResult :: VK_SUCCESS ) {
        return static_cast < __C_ENG_TYPE ( Result ) > ( result );
    }

    for ( uint32 i = 0U; i < * pLayerPropertiesCount; ++ i ) {
        (void) std :: memcpy ( & pProperties[i].layerName[0],   & layerProperties[i].layerName[0],   VK_MAX_EXTENSION_NAME_SIZE );
        (void) std :: memcpy ( & pProperties[i].description[0], & layerProperties[i].description[0], VK_MAX_DESCRIPTION_SIZE );
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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pPropertyCount == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION (
            lastCreatedInstance,
            pVkEnumerateInstanceExtensionProperties,
            ENUMERATE_INSTANCE_EXTENSION_PROPERTIES
    )

    if ( pProperties == nullptr ) {
        return static_cast < __C_ENG_TYPE ( Result ) > (
                pVkEnumerateInstanceExtensionProperties (
                        layerName,
                        pPropertyCount,
                        nullptr
            )
        );
    }

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( * pPropertyCount > __C_ENG_VULKAN_CORE_LAYER_EXTENSION_MAX_COUNT ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

    result = pVkEnumerateInstanceExtensionProperties (
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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if (
            pCreateInfo     == nullptr ||
            pInstanceHandle == nullptr
    ) {
        return ResultErrorIllegalArgument;
    }

#endif

    __C_ENG_LOOKUP_VULKAN_FUNCTION (
            pVkCreateInstance,
            CREATE_INSTANCE
    )

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

            if (
                    validationFeatures.enabledValidationFeatureCount    > __C_ENG_VULKAN_CORE_VALIDATION_FEATURE_ENABLE_MAX_COUNT ||
                    validationFeatures.disabledValidationFeatureCount   > __C_ENG_VULKAN_CORE_VALIDATION_FEATURE_DISABLE_MAX_COUNT
            ) {
                return ResultErrorConfigurationArraySizeSmall;
            }

#endif

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

    auto lResult = static_cast < __C_ENG_TYPE ( Result ) > (
            pVkCreateInstance (
                    & instanceCreateInfo,
                    pUsedAllocationCallbacks,
                    pInstanceHandle
            )
    );

    if ( lResult != ResultSuccess ) {
        return lResult;
    }

    lastCreatedInstance = * pInstanceHandle;
    return ResultSuccess;
}

auto vulkan :: destroyInstance (
        __C_ENG_TYPE ( InstanceHandle )                 handle,
        __C_ENG_TYPE ( AllocationCallbacks )    const * pAllocatorCallbacks
) noexcept -> __C_ENG_TYPE ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( handle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION (
            handle,
            pVkDestroyInstance,
            DESTROY_INSTANCE
    )

    VkAllocationCallbacks * pUsedCallbacks = nullptr;

    if ( pAllocatorCallbacks != nullptr ) {
        pUsedCallbacks = & allocationCallbacks;
        toVulkanFormat ( pAllocatorCallbacks, pUsedCallbacks );
    }

    pVkDestroyInstance ( handle, pUsedCallbacks );
    lastCreatedInstance = nullptr;

    return ResultSuccess;
}

auto vulkan :: createDebugMessenger (
        __C_ENG_TYPE ( InstanceHandle )                     instanceHandle,
        __C_ENG_TYPE ( DebugMessengerCreateInfo )   const * pMessengerCreateInfo,
        __C_ENG_TYPE ( AllocationCallbacks )        const * pAllocationCallbacks,
        __C_ENG_TYPE ( DebugMessengerHandle )             * pHandle
) noexcept -> __C_ENG_TYPE ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pMessengerCreateInfo == nullptr || pHandle == nullptr || instanceHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION (
            instanceHandle,
            pVkCreateDebugUtilsMessenger,
            CREATE_DEBUG_UTILS_MESSENGER
    )

    VkAllocationCallbacks             * pUsedAllocationCallbacks = nullptr;

    if ( pAllocationCallbacks != nullptr ) {
        pUsedAllocationCallbacks = & allocationCallbacks;
        toVulkanFormat ( pAllocationCallbacks, pUsedAllocationCallbacks );
    }

    toVulkanFormat (
            pMessengerCreateInfo,
            & messengerCreateInfo
    );

    return static_cast < __C_ENG_TYPE ( Result ) > (
            pVkCreateDebugUtilsMessenger (
                    instanceHandle,
                    & messengerCreateInfo,
                    pUsedAllocationCallbacks,
                    pHandle
            )
    );
}

auto vulkan :: destroyDebugMessenger (
        __C_ENG_TYPE ( InstanceHandle )                 instanceHandle,
        __C_ENG_TYPE ( DebugMessengerHandle )           debugMessengerHandle,
        __C_ENG_TYPE ( AllocationCallbacks )    const * pAllocationCallbacks
) noexcept -> __C_ENG_TYPE ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( instanceHandle == nullptr || debugMessengerHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION (
            instanceHandle,
            pVkDestroyDebugUtilsMessenger,
            DESTROY_DEBUG_UTILS_MESSENGER
    )

    VkAllocationCallbacks             * pUsedCallbacks = nullptr;

    if ( pAllocationCallbacks != nullptr ) {
        pUsedCallbacks = & allocationCallbacks;
        toVulkanFormat ( pAllocationCallbacks, pUsedCallbacks );
    }

    pVkDestroyDebugUtilsMessenger ( instanceHandle, debugMessengerHandle, pUsedCallbacks );
    return ResultSuccess;
}

auto vulkan :: enumeratePhysicalDevices (
        __C_ENG_TYPE ( InstanceHandle )             handle,
        uint32                                    * pPhysicalDeviceCount,
        __C_ENG_TYPE ( PhysicalDeviceHandle )     * pPhysicalDevices
) noexcept -> __C_ENG_TYPE ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pPhysicalDeviceCount == nullptr || handle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION (
            handle,
            pVkEnumeratePhysicalDevices,
            ENUMERATE_PHYSICAL_DEVICES
    )

    if ( pPhysicalDevices == nullptr ) {
        return static_cast < __C_ENG_TYPE ( Result ) > ( pVkEnumeratePhysicalDevices (
                handle,
                pPhysicalDeviceCount,
                nullptr
        ));
    }

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( * pPhysicalDeviceCount > __C_ENG_VULKAN_CORE_PHYSICAL_DEVICE_MAX_COUNT ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

    result = pVkEnumeratePhysicalDevices (
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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if (
            handle          == nullptr ||
            pWindowHandle   == nullptr ||
            pSurfaceHandle  == nullptr
    ) {
        return ResultErrorIllegalArgument;
    }

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if (
            instanceHandle  == nullptr ||
            surfaceHandle   == nullptr
    ) {
        return ResultErrorIllegalArgument;
    }

#endif

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION (
            instanceHandle,
            pVkDestroySurface,
            DESTROY_SURFACE
    )

    VkAllocationCallbacks * pUsedCallbacks = nullptr;
    if ( pAllocationCallbacks != nullptr ) {
        pUsedCallbacks = & allocationCallbacks;
        toVulkanFormat ( pAllocationCallbacks, pUsedCallbacks );
    }

    pVkDestroySurface (
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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pProperties == nullptr || pVkProperties == nullptr ) {
        return;
    }

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if (
            pDestination    == nullptr ||
            pSource         == nullptr
    ) {
        return;
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
}

__C_ENG_MAYBE_UNUSED auto vulkan :: getPhysicalDeviceProperties (
        __C_ENG_TYPE ( PhysicalDeviceHandle )       handle,
        __C_ENG_TYPE ( PhysicalDeviceProperties ) * pProperties
) noexcept -> __C_ENG_TYPE ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( handle == nullptr || pProperties == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION (
            lastCreatedInstance,
            pVkGetPhysicalDeviceProperties,
            GET_PHYSICAL_DEVICE_PROPERTIES
    )

    pVkGetPhysicalDeviceProperties (
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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if (
            physicalDeviceHandle == nullptr ||
                    pPhysicalDeviceFeatures == nullptr
    ) {
        return ResultErrorIllegalArgument;
    }

#endif

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION (
            lastCreatedInstance,
            pVkGetPhysicalDeviceFeatures,
            GET_PHYSICAL_DEVICE_FEATURES
    )

    pVkGetPhysicalDeviceFeatures (
            physicalDeviceHandle,
            & deviceFeatures
    );

    fromVulkanFormat ( pPhysicalDeviceFeatures, & deviceFeatures );

    return ResultSuccess;
}

static inline auto toVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceExtendedProperties ) const * pExtendedProperties
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pExtendedProperties == nullptr ) {
        return;
    }

#endif

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

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceVulkan_1_3_Properties:                                  { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceVulkan13Properties );                   break; }

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
                                                                                                                        
#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
                                                                                                                        
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
                                                                                                                        
#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
                                                                                                                        
            case engine :: vulkan :: StructureTypePhysicalDeviceSubgroupSizeControlProperties:                          { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceSubgroupSizeControlProperties );        break; }
                                                                                                                        
#endif                                                                                                                  
                                                                                                                        
#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
                                                                                                                        
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
                                                                                                                        
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
                                                                                                                        
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
                                                                                                                        
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
                                                                                                                        
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

#if ( __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE ) && __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pOut == nullptr || pIn == nullptr ) {
        return;
    }

#endif

    fromVulkanFormat ( & pIn->properties, & pOut->properties );
}

static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceExtendedProperties ) * pExtendedProperties
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pExtendedProperties == nullptr ) {
        return;
    }

    if ( pExtendedProperties->structureType != vulkan :: StructureTypePhysicalDeviceProperties ) {
        return;
    }

#endif

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

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceVulkan_1_3_Properties:                                  { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceVulkan13Properties ) * > ( currentInChain ), & deviceVulkan13Properties );                                                   break; }

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

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

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

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case engine :: vulkan :: StructureTypePhysicalDeviceSubgroupSizeControlProperties:                          { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceSubgroupSizeControlProperties ) * > ( currentInChain ), & deviceSubgroupSizeControlProperties );                         break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

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

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

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

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

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

#if ( __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE ) && __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( handle == nullptr || pProperties == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION (
            lastCreatedInstance,
            pVkGetPhysicalDeviceProperties,
            GET_PHYSICAL_DEVICE_PROPERTIES
    )

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION (
            lastCreatedInstance,
            pVkGetPhysicalDeviceProperties2,
            GET_PHYSICAL_DEVICE_PROPERTIES_2
    )

    pVkGetPhysicalDeviceProperties (
            handle,
            & deviceProperties
    );

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    auto version = vulkan :: uInt32ToInstanceVersion ( deviceProperties.apiVersion );
    if ( vulkan :: compare ( version, versionConstants :: version11 ) == CompareResultLess ) {
        return ResultErrorIncompatibleVersion;
    }

#endif

    toVulkanFormat ( pProperties );

    pVkGetPhysicalDeviceProperties2 (
        handle,
        & deviceExtendedProperties
    );

    fromVulkanFormat ( pProperties );

    return ResultSuccess;
}

static inline auto toVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceExtendedFeatures ) const * pExtendedFeatures
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pExtendedFeatures == nullptr ) {
        return;
    }

#endif

    deviceExtendedFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;

    auto currentInChain     = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericInStructure ) const * > ( pExtendedFeatures->pNext );
    auto currentInVkChain   = reinterpret_cast < VkBaseOutStructure * > ( & deviceExtendedFeatures );

    while ( currentInChain != nullptr ) {
        switch ( currentInChain->structureType ){

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceVulkan_1_1_Features:                              { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceVulkan11Features );                             break; }
            case vulkan :: StructureTypePhysicalDevice16BitStorageFeatures:                             { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & device16BitStorageFeatures );                         break; }
            case vulkan :: StructureTypePhysicalDeviceMultiviewFeatures:                                { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceMultiviewFeatures );                            break; }
            case vulkan :: StructureTypePhysicalDeviceProtectedMemoryFeatures:                          { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceProtectedMemoryFeatures );                      break; }
            case vulkan :: StructureTypePhysicalDeviceSamplerYCBCRConversionFeatures:                   { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceSamplerYCBCRConversionFeatures );               break; }
            case vulkan :: StructureTypePhysicalDeviceShaderDrawParametersFeatures:                     { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceShaderDrawParametersFeatures );                 break; }
            case vulkan :: StructureTypePhysicalDeviceVariablePointersFeatures:                         { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceVariablePointersFeatures );                     break; }

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceVulkan_1_2_Features:                              { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceVulkan12Features );                             break; }
            case vulkan :: StructureTypePhysicalDevice8BitStorageFeatures:                              { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & device8BitStorageFeatures );                          break; }
            case vulkan :: StructureTypePhysicalDeviceBufferDeviceAddressFeatures:                      { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceBufferDeviceAddressFeatures );                  break; }
            case vulkan :: StructureTypePhysicalDeviceDescriptorIndexingFeatures:                       { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceDescriptorIndexingFeatures );                   break; }
            case vulkan :: StructureTypePhysicalDeviceHostQueryResetFeatures:                           { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceHostQueryResetFeatures );                       break; }
            case vulkan :: StructureTypePhysicalDeviceImagelessFramebufferFeatures:                     { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceImagelessFramebufferFeatures );                 break; }
            case vulkan :: StructureTypePhysicalDeviceScalarBlockLayoutFeatures:                        { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceScalarBlockLayoutFeatures );                    break; }
            case vulkan :: StructureTypePhysicalDeviceSeparateDepthStencilLayoutsFeatures:              { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceSeparateDepthStencilLayoutsFeatures );          break; }
            case vulkan :: StructureTypePhysicalDeviceShaderAtomicInt64Features:                        { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceShaderAtomicInt64Features );                    break; }
            case vulkan :: StructureTypePhysicalDeviceShaderFloat16Int8Features:                        { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceShaderFloat16Int8Features );                    break; }
            case vulkan :: StructureTypePhysicalDeviceShaderSubgroupExtendedTypesFeatures:              { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceShaderSubgroupExtendedTypesFeatures );          break; }
            case vulkan :: StructureTypePhysicalDeviceTimelineSemaphoreFeatures:                        { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceTimelineSemaphoreFeatures );                    break; }
            case vulkan :: StructureTypePhysicalDeviceUniformBufferStandardLayoutFeatures:              { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceUniformBufferStandardLayoutFeatures );          break; }
            case vulkan :: StructureTypePhysicalDeviceVulkanMemoryModelFeatures:                        { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceVulkanMemoryModelFeatures );                    break; }

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceVulkan_1_3_Features:                              { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceVulkan13Features );                             break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_4444_FORMATS_AVAILABLE

            case vulkan :: StructureTypePhysicalDevice4444FormatsFeatures:                              { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & device4444FormatsFeatures );                          break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ASTC_DECODE_MODE_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceASTCDecodeFeatures:                               { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceAstcDecodeFeatures );                           break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceAccelerationStructureFeatures:                    { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceAccelerationStructureFeatures );                break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceBlendOperationAdvancedFeatures:                   { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceBlendOperationAdvancedFeatures );               break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BORDER_COLOR_SWIZZLE_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceBorderColorSwizzleFeatures:                       { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceBorderColorSwizzleFeatures );                   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_DEVICE_COHERENT_MEMORY_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceCoherentMemoryFeaturesAMD:                        { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceCoherentMemoryFeatures );                       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_COLOR_WRITE_ENABLE_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceColorWriteEnableFeatures:                         { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceColorWriteEnableFeatures );                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COMPUTE_SHADER_DERIVATIVES_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceComputeShaderDerivativesFeaturesNVidia:           { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceComputeShaderDerivativesFeatures );             break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceConditionalRenderingFeatures:                     { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceConditionalRenderingFeatures );                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceCooperativeMatrixFeaturesNVidia:                  { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceCooperativeMatrixFeatures );                    break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CORNER_SAMPLED_IMAGE_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceCornerSampledImageFeaturesNVidia:                 { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceDeviceCornerSampledImageFeatures );             break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COVERAGE_REDUCTION_MODE_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceCoverageReductionModeFeaturesNVidia:              { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceCoverageReductionModeFeatures );                break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceCustomBorderColorFeatures:                        { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceCustomBorderColorFeatures );                    break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_IMAGE_ALIASING_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceDedicatedAllocationImageAliasingFeaturesNVidia:   { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceDedicatedAllocationImageAliasingFeatures );     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_CONTROL_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceDepthClipControlFeatures:                         { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceDepthClipControlFeatures );                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_ENABLE_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceDepthClipEnableFeatures:                          { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceDepthClipEnableFeatures );                      break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceDeviceGeneratedCommandsFeaturesNVidia:            { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceDeviceGeneratedCommandsFeatures );              break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEVICE_MEMORY_REPORT_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceDeviceMemoryReportFeatures:                       { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceDeviceMemoryReportFeatures );                   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTICS_CONFIG_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceDiagnosticsConfigFeaturesNVidia:                  { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceDiagnosticsConfigFeatures );                    break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceDynamicRenderingFeatures:                         { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceDynamicRenderingFeatures );                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SCISSOR_EXCLUSIVE_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceExclusiveScissorFeaturesNVidia:                   { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceExclusiveScissorFeatures );                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceExtendedDynamicStateFeatures:                     { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceExtendedDynamicStateFeatures );                 break; }
            case vulkan :: StructureTypePhysicalDeviceExtendedDynamicState2Features:                    { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceExtendedDynamicState2Features );                break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_RDMA_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceExternalMemoryRDMAFeaturesNVidia:                 { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceExternalMemoryRDMAFeatures );                   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceFragmentDensityMapFeatures:                       { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceFragmentDensityMapFeatures );                   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceFragmentDensityMap2Features:                      { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceFragmentDensityMap2Features );                  break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceFragmentDensityMapOffsetFeaturesQualcomm:         { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceFragmentDensityMapOffsetFeatures );             break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADER_BARYCENTRIC_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceFragmentShaderBarycentricFeaturesNVidia:          { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceFragmentShaderBarycentricFeatures );            break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_SHADER_INTERLOCK_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceFragmentShaderInterlockFeatures:                  { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceFragmentShaderInterlockFeatures );              break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceFragmentShadingRateEnumsFeaturesNVidia:           { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceFragmentShadingRateEnumsFeatures );             break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceFragmentShadingRateFeatures:                      { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceFragmentShadingRateFeatures );                  break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceGlobalPriorityQueryFeatures:                      { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceGlobalPriorityQueryFeatures );                  break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_ROBUSTNESS_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceImageRobustnessFeatures:                          { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceImageRobustnessFeatures );                      break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_VIEW_MIN_LOD_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceImageViewMinLODFeatures:                          { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceImageViewMinLODFeatures );                      break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INDEX_TYPE_UINT8_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceIndexTypeUInt8Features:                           { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceIndexTypeUInt8Features );                       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_INHERITED_VIEWPORT_SCISSOR_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceInheritedViewportScissorFeaturesNVidia:           { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceInheritedViewportScissorFeatures );             break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceInlineUniformBlockFeatures:                       { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceInlineUniformBlockFeatures );                   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_INVOCATION_MASK_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceInvocationMaskFeaturesHuawei:                     { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceInvocationMaskFeatures );                       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceLineRasterizationFeatures:                        { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceLineRasterizationFeatures );                    break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_LINEAR_COLOR_ATTACHMENT_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceLinearColorAttachmentFeaturesNVidia:              { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceLinearColorAttachmentFeatures );                break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceMaintenance4Features:                             { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceMaintenance4Features );                         break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_PRIORITY_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceMemoryPriorityFeatures:                           { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceMemoryPriorityFeatures );                       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceMeshShaderFeaturesNVidia:                         { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceMeshShaderFeatures );                           break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceMultiDrawFeatures:                                { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceMultiDrawFeatures );                            break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceMutableDescriptorTypeFeaturesValve:               { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceMutableDescriptorTypeFeatures );                break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PAGEABLE_DEVICE_LOCAL_MEMORY_AVAILABLE

            case vulkan :: StructureTypePhysicalDevicePageableDeviceLocalMemoryFeatures:                { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & devicePageableDeviceLocalMemoryFeatures );            break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

            case vulkan :: StructureTypePhysicalDevicePerformanceQueryFeatures:                         { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & devicePerformanceQueryFeatures );                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case vulkan :: StructureTypePhysicalDevicePipelineCreationCacheControlFeatures:             { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & devicePipelineCreationCacheControlFeatures );         break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE

            case vulkan :: StructureTypePhysicalDevicePipelineExecutablePropertiesFeatures:             { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & devicePipelineExecutablePropertiesFeatures );         break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE

            case vulkan :: StructureTypePhysicalDevicePortabilitySubsetFeatures:                        { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & devicePortabilitySubsetFeatures );                    break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_ID_AVAILABLE

            case vulkan :: StructureTypePhysicalDevicePresentIDFeatures:                                { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & devicePresentIDFeatures );                            break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_WAIT_AVAILABLE

            case vulkan :: StructureTypePhysicalDevicePresentWaitFeatures:                              { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & devicePresentWaitFeatures );                          break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIMITIVE_TOPOLOGY_LIST_RESTART_AVAILABLE

            case vulkan :: StructureTypePhysicalDevicePrimitiveTopologyListRestartFeatures:             { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & devicePrimitiveTopologyListRestartFeatures );         break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case vulkan :: StructureTypePhysicalDevicePrivateDataFeatures:                              { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & devicePrivateDataFeatures );                          break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceProvokingVertexFeatures:                          { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceProvokingVertexFeatures );                      break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_RGBA_10_X_6_FORMATS_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceRGBA10x6FormatsFeatures:                          { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceRgba10X6FormatsFeatures );                      break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ARM_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM:    { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceRasterizationOrderAttachmentAccessFeatures );   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_QUERY_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceRayQueryFeatures:                                 { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceRayQueryFeatures );                             break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceRayTracingMotionBlurFeaturesNVidia:               { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceRayTracingMotionBlurFeatures );                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceRayTracingPipelineFeatures:                       { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceRayTracingPipelineFeatures );                   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_REPRESENTATIVE_FRAGMENT_TEST_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceRepresentativeFragmentTestFeaturesNVidia:         { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceRepresentativeFragmentTestFeatures );           break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceRobustnessFeatures:                               { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceRobustness2Features );                          break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceShaderAtomicFloatFeatures:                        { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceShaderAtomicFloatFeatures );                    break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_2_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceShaderAtomicFloat2Features:                       { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceShaderAtomicFloat2Features );                   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_CLOCK_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceShaderClockFeatures:                              { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceShaderClockFeatures );                          break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_DEMOTE_TO_HELPER_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceShaderDemoteToHelperInvocationFeatures:           { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceShaderDemoteToHelperInvocationFeatures );       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_IMAGE_ATOMIC_INT64_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceShaderImageAtomicInt64Features:                   { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceShaderImageAtomicInt64Features );               break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_IMAGE_FOOTPRINT_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceShaderImageFootprintFeaturesNVidia:               { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceShaderImageFootprintFeatures );                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceShaderSmBuiltinsFeaturesNVidia:                   { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceShaderSmBuiltinsFeatures );                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_SUBGROUP_UNIFORM_CONTROL_FLOW_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceShaderSubgroupUniformControlFlowFeatures:         { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceShaderSubgroupUniformControlFlowFeatures );     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_TERMINATE_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceShaderTerminateInvocationFeatures:                { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceShaderTerminateInvocationFeatures );            break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceShadingRateImageFeaturesNVidia:                   { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceShadingRateImageFeatures );                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceSubgroupSizeControlFeatures:                      { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceSubgroupSizeControlFeatures );                  break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceSubpassShadingFeaturesHuawei:                     { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceSubpassShadingFeatures );                       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceSynchronizationFeatures:                          { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceSynchronization2Features );                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceTexelBufferAlignmentFeatures:                     { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceTexelBufferAlignmentFeatures );                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXTURE_COMPRESSION_ASTC_HDR_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceTextureCompressionASTCHDRFeatures:                { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceTextureCompressionASTCHDRFeatures );            break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceTransformFeedbackFeatures:                        { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceTransformFeedbackFeatures );                    break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceVertexAttributeDivisorFeatures:                   { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceVertexAttributeDivisorFeatures );               break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_INPUT_DYNAMIC_STATE_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceVertexInputDynamicStateFeatures:                  { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceVertexInputDynamicStateFeatures );              break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceShaderIntegerDotProductFeatures:                  { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceShaderIntegerDotProductFeatures );              break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_SHADER_INTEGER_FUNCTIONS_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceShaderIntegerFunctionsFeaturesIntel:              { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceShaderIntegerFunctions2Features );              break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceWorkgroupMemoryExplicitLayoutFeatures:            { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceWorkgroupMemoryExplicitLayoutFeatures );        break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_2_PLANE_444_FORMATS_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceYCBCR2Plane444FormatsFeatures:                    { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceYCBCR2Plane444FormatsFeatures );                break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_IMAGE_ARRAYS_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceYCBCRImageArraysFeatures:                         { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceYCBCRImageArraysFeatures );                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ZERO_INITIALIZE_WORKGROUP_MEMORY_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceZeroInitializeWorkgroupMemoryFeatures:            { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceZeroInitializeWorkgroupMemoryFeatures );        break; }

#endif

            default:                                                                                    { currentInVkChain->pNext = nullptr;                                                                                            break; }
        }

        if ( currentInVkChain->pNext != nullptr ) {
            currentInVkChain->pNext->sType  = static_cast < VkStructureType > ( currentInChain->structureType );
            currentInVkChain                = currentInVkChain->pNext;
        }

        currentInChain                  = currentInChain->pNext;
    }
}

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceExtendedFeatures ) * pDestination,
        VkPhysicalDeviceFeatures2                           const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    fromVulkanFormat ( & pDestination->features, & pSource->features );
}

static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceExtendedFeatures ) * pExtendedFeatures
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pExtendedFeatures == nullptr ) {
        return;
    }

    if ( pExtendedFeatures->structureType != vulkan :: StructureTypePhysicalDeviceFeatures ) {
        return;
    }

#endif

    auto currentInChain = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( pExtendedFeatures );

    while ( currentInChain != nullptr ) {
        switch ( currentInChain->structureType ) {

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceFeatures:                                         { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceExtendedFeatures ) * > ( currentInChain ), & deviceExtendedFeatures );                                                       break; }

            case vulkan :: StructureTypePhysicalDeviceVulkan_1_1_Features:                              { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceVulkan11Features ) * > ( currentInChain ), & deviceVulkan11Features );                                                       break; }
            case vulkan :: StructureTypePhysicalDevice16BitStorageFeatures:                             { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDevice16BitStorageFeatures ) * > ( currentInChain ), & device16BitStorageFeatures );                                               break; }
            case vulkan :: StructureTypePhysicalDeviceMultiviewFeatures:                                { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceMultiviewFeatures ) * > ( currentInChain ), & deviceMultiviewFeatures );                                                     break; }
            case vulkan :: StructureTypePhysicalDeviceProtectedMemoryFeatures:                          { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceProtectedMemoryFeatures ) * > ( currentInChain ), & deviceProtectedMemoryFeatures );                                         break; }
            case vulkan :: StructureTypePhysicalDeviceSamplerYCBCRConversionFeatures:                   { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceSamplerYCBCRConversionFeatures ) * > ( currentInChain ), & deviceSamplerYCBCRConversionFeatures );                           break; }
            case vulkan :: StructureTypePhysicalDeviceShaderDrawParametersFeatures:                     { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderDrawParametersFeatures ) * > ( currentInChain ), & deviceShaderDrawParametersFeatures );                               break; }
            case vulkan :: StructureTypePhysicalDeviceVariablePointersFeatures:                         { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceVariablePointersFeatures ) * > ( currentInChain ), & deviceVariablePointersFeatures );                                       break; }

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceVulkan_1_2_Features:                              { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceVulkan12Features ) * > ( currentInChain ), & deviceVulkan12Features );                                                       break; }
            case vulkan :: StructureTypePhysicalDevice8BitStorageFeatures:                              { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDevice8BitStorageFeatures ) * > ( currentInChain ), & device8BitStorageFeatures );                                                 break; }
            case vulkan :: StructureTypePhysicalDeviceBufferDeviceAddressFeatures:                      { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceBufferDeviceAddressFeatures ) * > ( currentInChain ), & deviceBufferDeviceAddressFeatures );                                 break; }
            case vulkan :: StructureTypePhysicalDeviceDescriptorIndexingFeatures:                       { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceDescriptorIndexingFeatures ) * > ( currentInChain ), & deviceDescriptorIndexingFeatures );                                   break; }
            case vulkan :: StructureTypePhysicalDeviceHostQueryResetFeatures:                           { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceHostQueryResetFeatures ) * > ( currentInChain ), & deviceHostQueryResetFeatures );                                           break; }
            case vulkan :: StructureTypePhysicalDeviceImagelessFramebufferFeatures:                     { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceImagelessFramebufferFeatures ) * > ( currentInChain ), & deviceImagelessFramebufferFeatures );                               break; }
            case vulkan :: StructureTypePhysicalDeviceScalarBlockLayoutFeatures:                        { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceScalarBlockLayoutFeatures ) * > ( currentInChain ), & deviceScalarBlockLayoutFeatures );                                     break; }
            case vulkan :: StructureTypePhysicalDeviceSeparateDepthStencilLayoutsFeatures:              { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceSeparateDepthStencilLayoutsFeatures ) * > ( currentInChain ), & deviceSeparateDepthStencilLayoutsFeatures );                 break; }
            case vulkan :: StructureTypePhysicalDeviceShaderAtomicInt64Features:                        { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderAtomicInt64Features ) * > ( currentInChain ), & deviceShaderAtomicInt64Features );                                     break; }
            case vulkan :: StructureTypePhysicalDeviceShaderFloat16Int8Features:                        { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderFloat16Int8Features ) * > ( currentInChain ), & deviceShaderFloat16Int8Features );                                     break; }
            case vulkan :: StructureTypePhysicalDeviceShaderSubgroupExtendedTypesFeatures:              { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderSubgroupExtendedTypesFeatures ) * > ( currentInChain ), & deviceShaderSubgroupExtendedTypesFeatures );                 break; }
            case vulkan :: StructureTypePhysicalDeviceTimelineSemaphoreFeatures:                        { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceTimelineSemaphoreFeatures ) * > ( currentInChain ), & deviceTimelineSemaphoreFeatures );                                     break; }
            case vulkan :: StructureTypePhysicalDeviceUniformBufferStandardLayoutFeatures:              { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceUniformBufferStandardLayoutFeatures ) * > ( currentInChain ), & deviceUniformBufferStandardLayoutFeatures );                 break; }
            case vulkan :: StructureTypePhysicalDeviceVulkanMemoryModelFeatures:                        { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceVulkanMemoryModelFeatures ) * > ( currentInChain ), & deviceVulkanMemoryModelFeatures );                                     break; }

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceVulkan_1_3_Features:                              { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceVulkan13Features ) * > ( currentInChain ), & deviceVulkan13Features );                                                                   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_4444_FORMATS_AVAILABLE

            case vulkan :: StructureTypePhysicalDevice4444FormatsFeatures:                              { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDevice4444FormatsFeatures ) * > ( currentInChain ), & device4444FormatsFeatures );                                                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ASTC_DECODE_MODE_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceASTCDecodeFeatures:                               { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceASTCDecodeFeatures ) * > ( currentInChain ), & deviceAstcDecodeFeatures );                                                   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceAccelerationStructureFeatures:                    { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceAccelerationStructureFeatures ) * > ( currentInChain ), & deviceAccelerationStructureFeatures );                             break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceBlendOperationAdvancedFeatures:                   { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceBlendOperationAdvancedFeatures ) * > ( currentInChain ), & deviceBlendOperationAdvancedFeatures );                           break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BORDER_COLOR_SWIZZLE_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceBorderColorSwizzleFeatures:                       { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceBorderColorSwizzleFeatures ) * > ( currentInChain ), & deviceBorderColorSwizzleFeatures );                                   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_DEVICE_COHERENT_MEMORY_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceCoherentMemoryFeaturesAMD:                        { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceCoherentMemoryFeaturesAMD ) * > ( currentInChain ), & deviceCoherentMemoryFeatures );                                        break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_COLOR_WRITE_ENABLE_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceColorWriteEnableFeatures:                         { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceColorWriteEnableFeatures ) * > ( currentInChain ), & deviceColorWriteEnableFeatures );                                       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COMPUTE_SHADER_DERIVATIVES_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceComputeShaderDerivativesFeaturesNVidia:           { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceComputeShaderDerivativesFeaturesNVidia ) * > ( currentInChain ), & deviceComputeShaderDerivativesFeatures );                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceConditionalRenderingFeatures:                     { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceConditionalRenderingFeatures ) * > ( currentInChain ), & deviceConditionalRenderingFeatures );                               break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceCooperativeMatrixFeaturesNVidia:                  { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceCooperativeMatrixFeaturesNVidia ) * > ( currentInChain ), & deviceCooperativeMatrixFeatures );                               break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CORNER_SAMPLED_IMAGE_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceCornerSampledImageFeaturesNVidia:                 { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceCornerSampledImageFeaturesNVidia ) * > ( currentInChain ), & deviceDeviceCornerSampledImageFeatures );                       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COVERAGE_REDUCTION_MODE_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceCoverageReductionModeFeaturesNVidia:              { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceCoverageReductionModeFeaturesNVidia ) * > ( currentInChain ), & deviceCoverageReductionModeFeatures );                       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceCustomBorderColorFeatures:                        { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceCustomBorderColorFeatures ) * > ( currentInChain ), & deviceCustomBorderColorFeatures );                                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_IMAGE_ALIASING_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceDedicatedAllocationImageAliasingFeaturesNVidia:   { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNVidia ) * > ( currentInChain ), & deviceDedicatedAllocationImageAliasingFeatures ); break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_CONTROL_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceDepthClipControlFeatures:                         { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceDepthClipControlFeatures ) * > ( currentInChain ), & deviceDepthClipControlFeatures );                                       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_ENABLE_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceDepthClipEnableFeatures:                          { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceDepthClipEnableFeatures ) * > ( currentInChain ), & deviceDepthClipEnableFeatures );                                         break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceDeviceGeneratedCommandsFeaturesNVidia:            { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceDeviceGeneratedCommandsFeaturesNVidia ) * > ( currentInChain ), & deviceDeviceGeneratedCommandsFeatures );                   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEVICE_MEMORY_REPORT_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceDeviceMemoryReportFeatures:                       { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceDeviceMemoryReportFeatures ) * > ( currentInChain ), & deviceDeviceMemoryReportFeatures );                                   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTICS_CONFIG_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceDiagnosticsConfigFeaturesNVidia:                  { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceDiagnosticsConfigFeaturesNVidia ) * > ( currentInChain ), & deviceDiagnosticsConfigFeatures );                               break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceDynamicRenderingFeatures:                         { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceDynamicRenderingFeatures ) * > ( currentInChain ), & deviceDynamicRenderingFeatures );                                       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SCISSOR_EXCLUSIVE_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceExclusiveScissorFeaturesNVidia:                   { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceExclusiveScissorFeaturesNVidia ) * > ( currentInChain ), & deviceExclusiveScissorFeatures );                                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceExtendedDynamicStateFeatures:                     { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceExtendedDynamicStateFeatures ) * > ( currentInChain ), & deviceExtendedDynamicStateFeatures );                               break; }
            case vulkan :: StructureTypePhysicalDeviceExtendedDynamicState2Features:                    { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceExtendedDynamicState2Features ) * > ( currentInChain ), & deviceExtendedDynamicState2Features );                             break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_RDMA_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceExternalMemoryRDMAFeaturesNVidia:                 { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceExternalMemoryRDMAFeaturesNVidia ) * > ( currentInChain ), & deviceExternalMemoryRDMAFeatures );                             break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceFragmentDensityMapFeatures:                       { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMapFeatures ) * > ( currentInChain ), & deviceFragmentDensityMapFeatures );                                   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceFragmentDensityMap2Features:                      { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMap2Features ) * > ( currentInChain ), & deviceFragmentDensityMap2Features );                                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceFragmentDensityMapOffsetFeaturesQualcomm:         { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMapOffsetFeaturesQualcomm ) * > ( currentInChain ), & deviceFragmentDensityMapOffsetFeatures );               break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADER_BARYCENTRIC_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceFragmentShaderBarycentricFeaturesNVidia:          { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceFragmentShaderBarycentricFeaturesNVidia ) * > ( currentInChain ), & deviceFragmentShaderBarycentricFeatures );               break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_SHADER_INTERLOCK_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceFragmentShaderInterlockFeatures:                  { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceFragmentShaderInterlockFeatures ) * > ( currentInChain ), & deviceFragmentShaderInterlockFeatures );                         break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceFragmentShadingRateEnumsFeaturesNVidia:           { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceFragmentShadingRateEnumsFeaturesNVidia ) * > ( currentInChain ), & deviceFragmentShadingRateEnumsFeatures );                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceFragmentShadingRateFeatures:                      { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceFragmentShadingRateFeatures ) * > ( currentInChain ), & deviceFragmentShadingRateFeatures );                                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceGlobalPriorityQueryFeatures:                      { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceGlobalPriorityQueryFeatures ) * > ( currentInChain ), & deviceGlobalPriorityQueryFeatures );                                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_ROBUSTNESS_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceImageRobustnessFeatures:                          { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceImageRobustnessFeatures ) * > ( currentInChain ), & deviceImageRobustnessFeatures );                                         break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_VIEW_MIN_LOD_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceImageViewMinLODFeatures:                          { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceImageViewMinLODFeatures ) * > ( currentInChain ), & deviceImageViewMinLODFeatures );                                         break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INDEX_TYPE_UINT8_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceIndexTypeUInt8Features:                           { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceIndexTypeUInt8Features ) * > ( currentInChain ), & deviceIndexTypeUInt8Features );                                           break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_INHERITED_VIEWPORT_SCISSOR_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceInheritedViewportScissorFeaturesNVidia:           { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceInheritedViewportScissorFeaturesNVidia ) * > ( currentInChain ), & deviceInheritedViewportScissorFeatures );                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceInlineUniformBlockFeatures:                       { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceInlineUniformBlockFeatures ) * > ( currentInChain ), & deviceInlineUniformBlockFeatures );                                   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_INVOCATION_MASK_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceInvocationMaskFeaturesHuawei:                     { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceInvocationMaskFeaturesHuawei ) * > ( currentInChain ), & deviceInvocationMaskFeatures );                                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceLineRasterizationFeatures:                        { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceLineRasterizationFeatures ) * > ( currentInChain ), & deviceLineRasterizationFeatures );                                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_LINEAR_COLOR_ATTACHMENT_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceLinearColorAttachmentFeaturesNVidia:              { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceLinearColorAttachmentFeaturesNVidia ) * > ( currentInChain ), & deviceLinearColorAttachmentFeatures );                       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceMaintenance4Features:                             { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceMaintenance4Features ) * > ( currentInChain ), & deviceMaintenance4Features );                                               break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_PRIORITY_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceMemoryPriorityFeatures:                           { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceMemoryPriorityFeatures ) * > ( currentInChain ), & deviceMemoryPriorityFeatures );                                           break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceMeshShaderFeaturesNVidia:                         { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceMeshShaderFeaturesNVidia ) * > ( currentInChain ), & deviceMeshShaderFeatures );                                             break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceMultiDrawFeatures:                                { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceMultiDrawFeatures ) * > ( currentInChain ), & deviceMultiDrawFeatures );                                                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceMutableDescriptorTypeFeaturesValve:               { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceMutableDescriptorTypeFeaturesValve ) * > ( currentInChain ), & deviceMutableDescriptorTypeFeatures );                        break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PAGEABLE_DEVICE_LOCAL_MEMORY_AVAILABLE

            case vulkan :: StructureTypePhysicalDevicePageableDeviceLocalMemoryFeatures:                { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDevicePageableDeviceLocalMemoryFeatures ) * > ( currentInChain ), & devicePageableDeviceLocalMemoryFeatures );                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

            case vulkan :: StructureTypePhysicalDevicePerformanceQueryFeatures:                         { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDevicePerformanceQueryFeatures ) * > ( currentInChain ), & devicePerformanceQueryFeatures );                                       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case vulkan :: StructureTypePhysicalDevicePipelineCreationCacheControlFeatures:             { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDevicePipelineCreationCacheControlFeatures ) * > ( currentInChain ), & devicePipelineCreationCacheControlFeatures );               break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE

            case vulkan :: StructureTypePhysicalDevicePipelineExecutablePropertiesFeatures:             { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDevicePipelineExecutablePropertiesFeatures ) * > ( currentInChain ), & devicePipelineExecutablePropertiesFeatures );               break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE

            case vulkan :: StructureTypePhysicalDevicePortabilitySubsetFeatures:                        { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDevicePortabilitySubsetFeatures ) * > ( currentInChain ), & devicePortabilitySubsetFeatures );                                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_ID_AVAILABLE

            case vulkan :: StructureTypePhysicalDevicePresentIDFeatures:                                { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDevicePresentIDFeatures ) * > ( currentInChain ), & devicePresentIDFeatures );                                                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_WAIT_AVAILABLE

            case vulkan :: StructureTypePhysicalDevicePresentWaitFeatures:                              { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDevicePresentWaitFeatures ) * > ( currentInChain ), & devicePresentWaitFeatures );                                                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIMITIVE_TOPOLOGY_LIST_RESTART_AVAILABLE

            case vulkan :: StructureTypePhysicalDevicePrimitiveTopologyListRestartFeatures:             { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDevicePrimitiveTopologyListRestartFeatures ) * > ( currentInChain ), & devicePrimitiveTopologyListRestartFeatures );               break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case vulkan :: StructureTypePhysicalDevicePrivateDataFeatures:                              { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDevicePrivateDataFeatures ) * > ( currentInChain ), & devicePrivateDataFeatures );                                                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceProvokingVertexFeatures:                          { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceProvokingVertexFeatures ) * > ( currentInChain ), & deviceProvokingVertexFeatures );                                         break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_RGBA_10_X_6_FORMATS_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceRGBA10x6FormatsFeatures:                          { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceRGBA10x6FormatsFeatures ) * > ( currentInChain ), & deviceRgba10X6FormatsFeatures );                                         break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ARM_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM:    { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM ) * > ( currentInChain ), & deviceRasterizationOrderAttachmentAccessFeatures );break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_QUERY_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceRayQueryFeatures:                                 { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceRayQueryFeatures ) * > ( currentInChain ), & deviceRayQueryFeatures );                                                       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceRayTracingMotionBlurFeaturesNVidia:               { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceRayTracingMotionBlurFeaturesNVidia ) * > ( currentInChain ), & deviceRayTracingMotionBlurFeatures );                         break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceRayTracingPipelineFeatures:                       { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceRayTracingPipelineFeatures ) * > ( currentInChain ), & deviceRayTracingPipelineFeatures );                                   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_REPRESENTATIVE_FRAGMENT_TEST_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceRepresentativeFragmentTestFeaturesNVidia:         { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceRepresentativeFragmentTestFeaturesNVidia ) * > ( currentInChain ), & deviceRepresentativeFragmentTestFeatures );             break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceRobustnessFeatures:                               { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceRobustnessFeatures ) * > ( currentInChain ), & deviceRobustness2Features );                                                  break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceShaderAtomicFloatFeatures:                        { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderAtomicFloatFeatures ) * > ( currentInChain ), & deviceShaderAtomicFloatFeatures );                                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_2_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceShaderAtomicFloat2Features:                       { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderAtomicFloat2Features ) * > ( currentInChain ), & deviceShaderAtomicFloat2Features );                                   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_CLOCK_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceShaderClockFeatures:                              { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderClockFeatures ) * > ( currentInChain ), & deviceShaderClockFeatures );                                                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_DEMOTE_TO_HELPER_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceShaderDemoteToHelperInvocationFeatures:           { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderDemoteToHelperInvocationFeatures ) * > ( currentInChain ), & deviceShaderDemoteToHelperInvocationFeatures );           break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_IMAGE_ATOMIC_INT64_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceShaderImageAtomicInt64Features:                   { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderImageAtomicInt64Features ) * > ( currentInChain ), & deviceShaderImageAtomicInt64Features );                           break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_IMAGE_FOOTPRINT_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceShaderImageFootprintFeaturesNVidia:               { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderImageFootprintFeaturesNVidia ) * > ( currentInChain ), & deviceShaderImageFootprintFeatures );                         break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceShaderSmBuiltinsFeaturesNVidia:                   { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderSMBuiltinsFeaturesNVidia ) * > ( currentInChain ), & deviceShaderSmBuiltinsFeatures );                                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_SUBGROUP_UNIFORM_CONTROL_FLOW_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceShaderSubgroupUniformControlFlowFeatures:         { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderSubgroupUniformControlFlowFeatures ) * > ( currentInChain ), & deviceShaderSubgroupUniformControlFlowFeatures );       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_TERMINATE_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceShaderTerminateInvocationFeatures:                { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderTerminateInvocationFeatures ) * > ( currentInChain ), & deviceShaderTerminateInvocationFeatures );                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceShadingRateImageFeaturesNVidia:                   { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceShadingRateImageFeaturesNVidia ) * > ( currentInChain ), & deviceShadingRateImageFeatures );                                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceSubgroupSizeControlFeatures:                      { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceSubgroupSizeControlFeatures ) * > ( currentInChain ), & deviceSubgroupSizeControlFeatures );                                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceSubpassShadingFeaturesHuawei:                     { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceSubpassShadingFeaturesHuawei ) * > ( currentInChain ), & deviceSubpassShadingFeatures );                                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceSynchronizationFeatures:                          { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceSynchronizationFeatures ) * > ( currentInChain ), & deviceSynchronization2Features );                                        break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceTexelBufferAlignmentFeatures:                     { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceTexelBufferAlignmentFeatures ) * > ( currentInChain ), & deviceTexelBufferAlignmentFeatures );                               break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXTURE_COMPRESSION_ASTC_HDR_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceTextureCompressionASTCHDRFeatures:                { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceTextureCompressionASTCHDRFeatures ) * > ( currentInChain ), & deviceTextureCompressionASTCHDRFeatures );                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceTransformFeedbackFeatures:                        { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceTransformFeedbackFeatures ) * > ( currentInChain ), & deviceTransformFeedbackFeatures );                                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceVertexAttributeDivisorFeatures:                   { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceVertexAttributeDivisorFeatures ) * > ( currentInChain ), & deviceVertexAttributeDivisorFeatures );                           break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_INPUT_DYNAMIC_STATE_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceVertexInputDynamicStateFeatures:                  { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceVertexInputDynamicStateFeatures ) * > ( currentInChain ), & deviceVertexInputDynamicStateFeatures );                         break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceShaderIntegerDotProductFeatures:                  { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderIntegerDotProductFeatures ) * > ( currentInChain ), & deviceShaderIntegerDotProductFeatures );                         break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_SHADER_INTEGER_FUNCTIONS_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceShaderIntegerFunctionsFeaturesIntel:              { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceShaderIntegerFunctionsFeaturesIntel ) * > ( currentInChain ), & deviceShaderIntegerFunctions2Features );                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceWorkgroupMemoryExplicitLayoutFeatures:            { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceWorkgroupMemoryExplicitLayoutFeatures ) * > ( currentInChain ), & deviceWorkgroupMemoryExplicitLayoutFeatures );             break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_2_PLANE_444_FORMATS_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceYCBCR2Plane444FormatsFeatures:                    { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceYCBCR2Plane444FormatsFeatures ) * > ( currentInChain ), & deviceYCBCR2Plane444FormatsFeatures );                             break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_IMAGE_ARRAYS_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceYCBCRImageArraysFeatures:                         { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceYCBCRImageArraysFeatures ) * > ( currentInChain ), & deviceYCBCRImageArraysFeatures );                                       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ZERO_INITIALIZE_WORKGROUP_MEMORY_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            case vulkan :: StructureTypePhysicalDeviceZeroInitializeWorkgroupMemoryFeatures:            { fromVulkanFormat ( reinterpret_cast < vulkan :: __C_ENG_TYPE ( PhysicalDeviceZeroInitializeWorkgroupMemoryFeatures ) * > ( currentInChain ), & deviceZeroInitializeWorkgroupMemoryFeatures );             break; }

#endif

            default: {
                break;
            }
        }

        currentInChain = currentInChain->pNext;
    }
}

auto vulkan :: getPhysicalDeviceFeatures (
        __C_ENG_TYPE ( PhysicalDeviceHandle )               handle,
        __C_ENG_TYPE ( PhysicalDeviceExtendedFeatures )   * pExtendedFeatures
) noexcept -> __C_ENG_TYPE ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if (
            handle              == nullptr ||
            pExtendedFeatures   == nullptr
    ) {
        return ResultErrorIllegalArgument;
    }

#endif

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION (
            lastCreatedInstance,
            pVkGetPhysicalDeviceProperties,
            GET_PHYSICAL_DEVICE_PROPERTIES
    )

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION (
            lastCreatedInstance,
            pVkGetPhysicalDeviceFeatures2,
            GET_PHYSICAL_DEVICE_FEATURES_2
    )

    pVkGetPhysicalDeviceProperties (
            handle,
            & deviceProperties
    );

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    auto version = vulkan :: uInt32ToInstanceVersion ( deviceProperties.apiVersion );
    if ( vulkan :: compare ( version, versionConstants :: version11 ) == CompareResultLess ) {
        return ResultErrorIncompatibleVersion;
    }

#endif

    toVulkanFormat ( pExtendedFeatures );

    pVkGetPhysicalDeviceFeatures2 (
            handle,
            & deviceExtendedFeatures
    );

    fromVulkanFormat ( pExtendedFeatures );

    return ResultSuccess;
}

static auto createChain (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceDetails )            * details,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceExtendedProperties ) * extendedProperties,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceExtendedFeatures )   * extendedFeatures
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( details == nullptr ) {
        return;
    }

#endif

    if ( extendedProperties != nullptr ) {

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

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->vulkan13Properties ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceVulkan_1_3_Properties;

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

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->inlineUniformBlockProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceInlineUniformBlockProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->lineRasterizationProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceLineRasterizationProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

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

#if ( __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE ) && __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE

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

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->subgroupSizeControlProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceSubgroupSizeControlProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->subpassShadingPropertiesHuawei ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceSubpassShadingPropertiesHuawei;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

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

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->shaderIntegerDotProductProperties ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = engine :: vulkan :: StructureTypePhysicalDeviceShaderIntegerDotProductProperties;

#endif

        currentInChain->pNext = nullptr;

    }


    if ( extendedFeatures != nullptr ) {

        auto currentInChain = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( extendedFeatures );
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceFeatures;


#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->vulkan11Features ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceVulkan_1_1_Features;

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->_16BitStorageFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDevice16BitStorageFeatures;

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->multiviewFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceMultiviewFeatures;

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->protectedMemoryFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceProtectedMemoryFeatures;

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->samplerYCBCRConversionFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceSamplerYCBCRConversionFeatures;

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->shaderDrawParametersFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceShaderDrawParametersFeatures;

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->variablePointersFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceVariablePointersFeatures;

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->vulkan12Features ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceVulkan_1_2_Features;

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->_8BitStorageFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDevice8BitStorageFeatures;

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->bufferDeviceAddressFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceBufferDeviceAddressFeatures;

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->descriptorIndexingFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceDescriptorIndexingFeatures;

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->hostQueryResetFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceHostQueryResetFeatures;

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->imagelessFramebufferFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceImagelessFramebufferFeatures;

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->scalarBlockLayoutFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceScalarBlockLayoutFeatures;

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->separateDepthStencilLayoutsFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceSeparateDepthStencilLayoutsFeatures;

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->shaderAtomicInt64Features ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceShaderAtomicInt64Features;

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->shaderFloat16Int8Features ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceShaderFloat16Int8Features;

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->shaderSubgroupExtendedTypesFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceShaderSubgroupExtendedTypesFeatures;

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->timelineSemaphoreFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceTimelineSemaphoreFeatures;

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->uniformBufferStandardLayoutFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceUniformBufferStandardLayoutFeatures;

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->vulkanMemoryModelFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceVulkanMemoryModelFeatures;

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->vulkan13Features ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceVulkan_1_3_Features;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_4444_FORMATS_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->_4444FormatsFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDevice4444FormatsFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ASTC_DECODE_MODE_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->ASTCDecodeFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceASTCDecodeFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->accelerationStructureFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceAccelerationStructureFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->blendOperationAdvancedFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceBlendOperationAdvancedFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BORDER_COLOR_SWIZZLE_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->borderColorSwizzleFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceBorderColorSwizzleFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_DEVICE_COHERENT_MEMORY_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->coherentMemoryFeaturesAMD ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceCoherentMemoryFeaturesAMD;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_COLOR_WRITE_ENABLE_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->colorWriteEnabledFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceColorWriteEnableFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COMPUTE_SHADER_DERIVATIVES_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->computeShaderDerivativesFeaturesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceComputeShaderDerivativesFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->conditionalRenderingFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceConditionalRenderingFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->cooperativeMatrixFeaturesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceCooperativeMatrixFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CORNER_SAMPLED_IMAGE_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->cornerSampledImageFeaturesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceCornerSampledImageFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COVERAGE_REDUCTION_MODE_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->coverageReductionModeFeaturesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceCoverageReductionModeFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->customBorderColorFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceCustomBorderColorFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_IMAGE_ALIASING_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->dedicatedAllocationImageAliasingFeaturesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceDedicatedAllocationImageAliasingFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_CONTROL_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->depthClipControlFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceDepthClipControlFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_ENABLE_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->depthClipEnableFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceDepthClipEnableFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->deviceGeneratedCommandsFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceDeviceGeneratedCommandsFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEVICE_MEMORY_REPORT_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->deviceMemoryReportFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceDeviceMemoryReportFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTICS_CONFIG_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->diagnosticsConfigFeaturesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceDiagnosticsConfigFeaturesNVidia;

#endif

#if ( __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE ) || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->dynamicRenderingFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceDynamicRenderingFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SCISSOR_EXCLUSIVE_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->exclusiveScissorFeaturesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceExclusiveScissorFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->extendedDynamicStateFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceExtendedDynamicStateFeatures;

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->extendedDynamicState2Features ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceExtendedDynamicState2Features;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_RDMA_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->externalMemoryRDMAFeaturesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceExternalMemoryRDMAFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->fragmentDensityMapFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceFragmentDensityMapFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->fragmentDensityMap2Features ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceFragmentDensityMap2Features;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->fragmentDensityMapOffsetFeaturesQualcomm ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceFragmentDensityMapOffsetFeaturesQualcomm;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADER_BARYCENTRIC_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->fragmentShaderBarycentricFeaturesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceFragmentShaderBarycentricFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_SHADER_INTERLOCK_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->fragmentShaderInterlockFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceFragmentShaderInterlockFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->fragmentShadingRateEnumsFeaturesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceFragmentShadingRateEnumsFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->fragmentShadingRateFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceFragmentShadingRateFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->globalPriorityQueryFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceGlobalPriorityQueryFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_ROBUSTNESS_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->imageRobustnessFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceImageRobustnessFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_VIEW_MIN_LOD_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->imageViewMinLODFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceImageViewMinLODFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INDEX_TYPE_UINT8_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->indexTypeUInt8Features ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceIndexTypeUInt8Features;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_INHERITED_VIEWPORT_SCISSOR_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->inheritedViewportScissorFeaturesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceInheritedViewportScissorFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->inlineUniformBlockFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceInlineUniformBlockFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_INVOCATION_MASK_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->invocationMaskFeaturesHuawei ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceInvocationMaskFeaturesHuawei;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->lineRasterizationFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceLineRasterizationFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_LINEAR_COLOR_ATTACHMENT_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->linearColorAttachmentFeaturesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceLinearColorAttachmentFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->maintenance4Features ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceMaintenance4Features;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_PRIORITY_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->memoryPriorityFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceMemoryPriorityFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->meshShaderFeaturesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceMeshShaderFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->multiDrawFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceMultiDrawFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->mutableDescriptorTypeFeaturesValve ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceMutableDescriptorTypeFeaturesValve;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PAGEABLE_DEVICE_LOCAL_MEMORY_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->pageableDeviceLocalMemoryFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDevicePageableDeviceLocalMemoryFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->performanceQueryFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDevicePerformanceQueryFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->pipelineCreationCacheControlFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDevicePipelineCreationCacheControlFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->pipelineExecutablePropertiesFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDevicePipelineExecutablePropertiesFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details.portabilitySubsetFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDevicePortabilitySubsetFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_ID_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->presentIDFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDevicePresentIDFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_WAIT_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->presentWaitFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDevicePresentWaitFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIMITIVE_TOPOLOGY_LIST_RESTART_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->primitiveTopologyListRestartFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDevicePrimitiveTopologyListRestartFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->privateDataFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDevicePrivateDataFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->provokingVertexFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceProvokingVertexFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_RGBA_10_X_6_FORMATS_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->RGBA10x6FormatsFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceRGBA10x6FormatsFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ARM_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->rasterizationOrderAttachmentAccessFeaturesARM ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_QUERY_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->rayQueryFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceRayQueryFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->rayTracingMotionBlurFeaturesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceRayTracingMotionBlurFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->rayTracingPipelineFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceRayTracingPipelineFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_REPRESENTATIVE_FRAGMENT_TEST_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->representativeFragmentTestFeaturesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceRepresentativeFragmentTestFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->robustnessFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceRobustnessFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->shaderAtomicFloatFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceShaderAtomicFloatFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_2_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->shaderAtomicFloat2Features ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceShaderAtomicFloat2Features;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_CLOCK_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->shaderClockFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceShaderClockFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_DEMOTE_TO_HELPER_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->shaderDemoteToHelperInvocationFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceShaderDemoteToHelperInvocationFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_IMAGE_ATOMIC_INT64_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->shaderImageAtomicInt64Features ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceShaderImageAtomicInt64Features;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_IMAGE_FOOTPRINT_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->shaderImageFootprintFeaturesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceShaderImageFootprintFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->shaderSmBuiltinsFeaturesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceShaderSmBuiltinsFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_SUBGROUP_UNIFORM_CONTROL_FLOW_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->shaderSubgroupUniformControlFlowFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceShaderSubgroupUniformControlFlowFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_TERMINATE_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->shaderTerminateInvocationFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceShaderTerminateInvocationFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->shadingRateImageFeaturesNVidia ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceShadingRateImageFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->subgroupSizeControlFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceSubgroupSizeControlFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->subpassShadingFeaturesHuawei ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceSubpassShadingFeaturesHuawei;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->synchronizationFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceSynchronizationFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->texelBufferAlignmentFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceTexelBufferAlignmentFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXTURE_COMPRESSION_ASTC_HDR_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->textureCompressionASTCHDRFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceTextureCompressionASTCHDRFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->transformFeedbackFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceTransformFeedbackFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->vertexAttributeDivisorFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceVertexAttributeDivisorFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_INPUT_DYNAMIC_STATE_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->vertexInputDynamicStateFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceVertexInputDynamicStateFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->shaderIntegerDotProductFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceShaderIntegerDotProductFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_SHADER_INTEGER_FUNCTIONS_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->shaderIntegerFunctionsFeaturesIntel ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceShaderIntegerFunctionsFeaturesIntel;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->workgroupMemoryExplicitLayoutFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceWorkgroupMemoryExplicitLayoutFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_2_PLANE_444_FORMATS_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->YCBCR2Plane444FormatFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceYCBCR2Plane444FormatsFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_IMAGE_ARRAYS_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->YCBCRImageArraysFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceYCBCRImageArraysFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ZERO_INITIALIZE_WORKGROUP_MEMORY_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        currentInChain = currentInChain->pNext = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * > ( & details->zeroInitializeWorkgroupMemoryFeatures ); // NOLINT(clion-misra-cpp2008-6-2-1)
        currentInChain->structureType = vulkan :: StructureTypePhysicalDeviceZeroInitializeWorkgroupMemoryFeatures;

#endif

        currentInChain->pNext = nullptr;

    }
}

auto vulkan :: getPhysicalDeviceDetails (
        __C_ENG_TYPE ( PhysicalDeviceHandle )       handle,
        __C_ENG_TYPE ( PhysicalDeviceDetails )    * properties
) noexcept -> __C_ENG_TYPE ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( handle == nullptr || properties == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    __C_ENG_TYPE ( PhysicalDeviceExtendedProperties ) extendedProperties { };
    __C_ENG_TYPE ( PhysicalDeviceExtendedFeatures ) extendedFeatures { };

    createChain ( properties, & extendedProperties, & extendedFeatures );

    auto lResult = getPhysicalDeviceProperties ( handle, & extendedProperties );
    if ( lResult != ResultSuccess ) {
        return lResult;
    }

    lResult = getPhysicalDeviceFeatures ( handle, & extendedFeatures );
    if ( lResult != ResultSuccess ) {
        return lResult;
    }

    auto currentInChain = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure * ) > ( & extendedProperties );
    while ( currentInChain->pNext != nullptr ) {
        auto current = currentInChain;
        currentInChain = currentInChain->pNext;
        current->pNext = nullptr;
    }

    currentInChain = reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure * ) > ( & extendedFeatures );
    while ( currentInChain->pNext != nullptr ) {
        auto current = currentInChain;
        currentInChain = currentInChain->pNext;
        current->pNext = nullptr;
    }

    (void) std :: memcpy ( & properties->basicProperties,   & extendedProperties.properties,    sizeof ( __C_ENG_TYPE ( PhysicalDeviceProperties ) ) );
    (void) std :: memcpy ( & properties->basicFeatures,     & extendedFeatures.features,        sizeof ( __C_ENG_TYPE ( PhysicalDeviceFeatures ) ) );

    return ResultSuccess;
}

inline static auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( QueueFamilyProperties ) * pDest,
        VkQueueFamilyProperties                    const * pSrc
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if (pDest == nullptr || pSrc == nullptr ) {
        return;
    }

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( handle == nullptr || pQueueFamilyPropertyCount == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION (
            lastCreatedInstance,
            pVkGetPhysicalDeviceQueueFamilyProperties,
            GET_PHYSICAL_DEVICE_QUEUE_FAMILY_PROPERTIES
    )

    if ( pQueueFamilyProperties == nullptr ) {
        pVkGetPhysicalDeviceQueueFamilyProperties (
                handle,
                pQueueFamilyPropertyCount,
                nullptr
        );

        return ResultSuccess;
    }

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( * pQueueFamilyPropertyCount > __C_ENG_VULKAN_CORE_QUEUE_FAMILY_MAX_COUNT ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

    pVkGetPhysicalDeviceQueueFamilyProperties (
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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pExtendedProperties == nullptr ) {
        return;
    }

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->checkpointExecutionStageMask  = pSource->checkpointExecutionStageMask;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( QueueFamilyGlobalPriorityProperties )        * pDestination,
        VkQueueFamilyGlobalPriorityPropertiesEXT                        const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->supported = pSource->supported;
}

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( VideoQueueFamilyProperties )          * pDestination,
        VkVideoQueueFamilyPropertiesKHR                          const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    pDestination->videoCodecOperations = pSource->videoCodecOperations;
}

#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( QueueFamilyExtendedProperties )          * pDestination,
        VkQueueFamilyProperties2                                    const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

    fromVulkanFormat ( & pDestination->properties, & pSource->queueFamilyProperties );
}

#endif

static inline auto fromVulkanFormat (
        uint32                                                              queueFamilyCount,
        vulkan :: __C_ENG_TYPE ( QueueFamilyExtendedProperties )          * pDestination
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr ) {
        return;
    }

    if ( pDestination->structureType != vulkan :: StructureTypeQueueFamilyProperties ) {
        return;
    }

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( handle == nullptr || pQueueFamilyPropertyCount == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION (
            lastCreatedInstance,
            pVkGetPhysicalDeviceProperties,
            GET_PHYSICAL_DEVICE_PROPERTIES
    )

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION (
            lastCreatedInstance,
            pVkGetPhysicalDeviceQueueFamilyProperties2,
            GET_PHYSICAL_DEVICE_QUEUE_FAMILY_PROPERTIES_2
    )

    if ( pQueueFamilyProperties == nullptr ) {
        pVkGetPhysicalDeviceQueueFamilyProperties2 (
                handle,
                pQueueFamilyPropertyCount,
                nullptr
        );

        return ResultSuccess;
    }

    pVkGetPhysicalDeviceProperties (
            handle,
            & deviceProperties
    );

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    auto version = vulkan :: uInt32ToInstanceVersion ( deviceProperties.apiVersion );
    if ( vulkan :: compare ( version, versionConstants :: version11 ) == CompareResultLess ) {
        return ResultErrorIncompatibleVersion;
    }

    if ( * pQueueFamilyPropertyCount > __C_ENG_VULKAN_CORE_QUEUE_FAMILY_MAX_COUNT ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

    toVulkanFormat ( * pQueueFamilyPropertyCount, pQueueFamilyProperties );

    pVkGetPhysicalDeviceQueueFamilyProperties2 (
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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDetails == nullptr || pExtendedProperties == nullptr ) {
        return;
    }

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( handle == nullptr || pQueueFamilyCount == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION (
            lastCreatedInstance,
            pVkGetPhysicalDeviceQueueFamilyProperties2,
            GET_PHYSICAL_DEVICE_QUEUE_FAMILY_PROPERTIES_2
    )

    if ( pQueueFamilyDetails == nullptr ) {
        pVkGetPhysicalDeviceQueueFamilyProperties2 (
                handle,
                pQueueFamilyCount,
                nullptr
        );

        return ResultSuccess;
    }

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( * pQueueFamilyCount > __C_ENG_VULKAN_CORE_QUEUE_FAMILY_MAX_COUNT ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

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

        (void) std :: memcpy ( & pQueueFamilyDetails[i].properties, & extendedProperties[i].properties, sizeof ( __C_ENG_TYPE ( QueueFamilyProperties ) ) );
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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( instanceHandle == nullptr || physicalDeviceHandle == nullptr || pCounterCount == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION (
            lastCreatedInstance,
            pVkInstanceProcessEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCounters,
            ENUMERATE_PHYSICAL_DEVICE_QUEUE_FAMILY_PERFORMANCE_QUERY_COUNTERS
    )

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( * pCounterCount > __C_ENG_VULKAN_CORE_QUEUE_FAMILY_PERFORMANCE_COUNTER_MAX_COUNT ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

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
        StringLiteral           functionName,
        FunctionHandleAddress   pFunctionHandle
) noexcept -> __C_ENG_TYPE ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pFunctionHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    * pFunctionHandle = reinterpret_cast < void * > ( vkGetInstanceProcAddr ( nullptr, functionName ) );

    if ( * pFunctionHandle == nullptr ) {
        return ResultErrorFunctionHandleNotFound;
    }

    return ResultSuccess;
}

auto vulkan :: getInstanceFunctionAddress (
        __C_ENG_TYPE ( InstanceHandle ) instanceHandle,
        StringLiteral                   functionName,
        FunctionHandleAddress           pFunctionHandle
) noexcept -> __C_ENG_TYPE ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pFunctionHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    * pFunctionHandle = reinterpret_cast < void * > ( vkGetInstanceProcAddr ( instanceHandle, functionName ) );

    if ( * pFunctionHandle == nullptr ) {
        return ResultErrorFunctionHandleNotFound;
    }

    return ResultSuccess;
}

auto vulkan :: getDeviceFunctionAddress (
        __C_ENG_TYPE ( DeviceHandle )   deviceHandle,
        StringLiteral                   functionName,
        FunctionHandleAddress           pFunctionHandle
) noexcept -> __C_ENG_TYPE ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pFunctionHandle == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION (
            lastCreatedInstance,
            pVkGetDeviceProcAddr,
            GET_DEVICE_PROC_ADDR
    )

    * pFunctionHandle = reinterpret_cast < void * > ( pVkGetDeviceProcAddr ( deviceHandle, functionName ) );

    if ( * pFunctionHandle == nullptr ) {
        return ResultErrorFunctionHandleNotFound;
    }

    return ResultSuccess;
}

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

static inline auto fromVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceGroupProperties )          * pDestination,
        VkPhysicalDeviceGroupProperties                             const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( pDestination == nullptr || pSource == nullptr ) {
        return;
    }

#endif

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

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( instanceHandle == nullptr || pPhysicalDeviceGroupCount == nullptr ) {
        return ResultErrorIllegalArgument;
    }

#endif

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION (
            instanceHandle,
            pVkEnumeratePhysicalDeviceGroups,
            ENUMERATE_PHYSICAL_DEVICE_GROUPS
    )

    if ( pPhysicalDeviceGroupProperties == nullptr ) {
        return static_cast < __C_ENG_TYPE ( Result ) > (
                pVkEnumeratePhysicalDeviceGroups (
                        instanceHandle,
                        pPhysicalDeviceGroupCount,
                        nullptr
                )
        );
    }

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( * pPhysicalDeviceGroupCount > __C_ENG_VULKAN_CORE_PHYSICAL_DEVICE_GROUP_MAX_COUNT ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

    result = pVkEnumeratePhysicalDeviceGroups (
            instanceHandle,
            pPhysicalDeviceGroupCount,
            & physicalDeviceGroupProperties[0]
    );

    if ( result != VK_SUCCESS ) {
        return static_cast < __C_ENG_TYPE ( Result ) > ( result );
    }

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    saveQueriedDeviceGroupInfo (
            * pPhysicalDeviceGroupCount,
            & physicalDeviceGroupProperties[0]
    );

#endif

    for ( uint32 i = 0U; i < * pPhysicalDeviceGroupCount; ++ i ) {
        fromVulkanFormat ( & pPhysicalDeviceGroupProperties[i], & physicalDeviceGroupProperties[0] );
    }

    return ResultSuccess;
}

#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

static inline auto toVulkanFormat (
        VkPhysicalDeviceFeatures                                * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if (
            pDestination    == nullptr ||
            pSource         == nullptr
    ) {
        return;
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
}

static inline auto toVulkanFormat (
        VkDeviceQueueCreateInfo                                 * pDestination,
        vulkan :: __C_ENG_TYPE ( DeviceQueueCreateInfo )  const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if (
            pDestination    == nullptr ||
            pSource         == nullptr
            ) {
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

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEVICE_MEMORY_REPORT_AVAILABLE

static inline auto toVulkanFormat (
        VkDeviceDeviceMemoryReportCreateInfoEXT                             * pDestination,
        vulkan :: __C_ENG_TYPE ( DeviceDeviceMemoryReportCreateInfo ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if (
            pDestination    == nullptr ||
            pSource         == nullptr
    ) {
        return;
    }

#endif

    pDestination->sType             = VK_STRUCTURE_TYPE_DEVICE_DEVICE_MEMORY_REPORT_CREATE_INFO_EXT;
    pDestination->pNext             = nullptr;

    pDestination->flags             = pSource->flags;
    pDestination->pfnUserCallback   = pSource->callback;
    pDestination->pUserData         = pSource->pUserData;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTICS_CONFIG_AVAILABLE

static inline auto toVulkanFormat (
        VkDeviceDiagnosticsConfigCreateInfoNV                                    * pDestination,
        vulkan :: __C_ENG_TYPE ( DeviceDiagnosticsConfigCreateInfoNVidia ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if (
            pDestination    == nullptr ||
            pSource         == nullptr
    ) {
        return;
    }

#endif

    pDestination->sType             = VK_STRUCTURE_TYPE_DEVICE_DIAGNOSTICS_CONFIG_CREATE_INFO_NV;
    pDestination->pNext             = nullptr;

    pDestination->flags             = pSource->flags;
}

#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

static inline auto toVulkanFormat (
        VkDeviceGroupDeviceCreateInfo                                * pDestination,
        vulkan :: __C_ENG_TYPE ( DeviceGroupDeviceCreateInfo ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if (
            pDestination    == nullptr ||
            pSource         == nullptr
    ) {
        return;
    }

#endif

    pDestination->sType                 = VK_STRUCTURE_TYPE_DEVICE_GROUP_DEVICE_CREATE_INFO;
    pDestination->pNext                 = nullptr;

    pDestination->physicalDeviceCount   = pSource->physicalDeviceCount;
    pDestination->pPhysicalDevices      = pSource->pPhysicalDevices;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_MEMORY_OVERALLOCATION_BEHAVIOUR_AVAILABLE

static inline auto toVulkanFormat (
        VkDeviceMemoryOverallocationCreateInfoAMD                                * pDestination,
        vulkan :: __C_ENG_TYPE ( DeviceMemoryOverallocationCreateInfoAMD ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if (
            pDestination    == nullptr ||
            pSource         == nullptr
    ) {
        return;
    }

#endif

    pDestination->sType                     = VK_STRUCTURE_TYPE_DEVICE_MEMORY_OVERALLOCATION_CREATE_INFO_AMD;
    pDestination->pNext                     = nullptr;

    pDestination->overallocationBehavior    = static_cast < VkMemoryOverallocationBehaviorAMD > ( pSource->overallocationBehavior );
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

static inline auto toVulkanFormat (
        VkDevicePrivateDataCreateInfo_t                              * pDestination,
        vulkan :: __C_ENG_TYPE ( DevicePrivateDataCreateInfo ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if (
            pDestination    == nullptr ||
            pSource         == nullptr
    ) {
        return;
    }

#endif

    pDestination->sType                         = VK_STRUCTURE_TYPE_DEVICE_PRIVATE_DATA_CREATE_INFO_EXT;
    pDestination->pNext                         = nullptr;

    pDestination->privateDataSlotRequestCount   = pSource->privateDataSlotRequestCount;
}

#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

static inline auto toVulkanFormat (
        VkPhysicalDeviceFeatures2                                       * pDestination,
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceExtendedFeatures ) const * pSource
) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if (
            pDestination    == nullptr ||
            pSource         == nullptr
    ) {
        return;
    }

#endif

    pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
    pDestination->pNext = nullptr;

    toVulkanFormat ( & pDestination->features, & pSource->features );
}

#endif

auto toVulkanFormat (
        VkDeviceCreateInfo                                  * pDestination,
        vulkan :: __C_ENG_TYPE ( DeviceCreateInfo ) const   * pSource
) noexcept -> void {

    using namespace vulkan; // NOLINT(clion-misra-cpp2008-7-3-4)

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if (
            pSource         == nullptr ||
            pDestination    == nullptr
    ) {
        return;
    }

#endif

    pDestination->sType                     = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    pDestination->flags                     = pSource->flags;

    pDestination->queueCreateInfoCount      = pSource->queueCreateInfoCount;
    pDestination->enabledExtensionCount     = pSource->enabledExtensionCount;
    pDestination->ppEnabledExtensionNames   = pSource->pEnabledExtensionNames;

    if ( pSource->pEnabledFeatures != nullptr ) {
        pDestination->pEnabledFeatures = & deviceFeatures;
        toVulkanFormat ( & deviceFeatures, pSource->pEnabledFeatures );
    }

#if ! __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

    pDestination->enabledLayerCount     = pSource->enabledLayerCount;
    pDestination->ppEnabledLayerNames   = pSource->pEnabledLayerNames;

#endif

    pDestination->pQueueCreateInfos = & deviceQueueCreateInfos [0];
    for ( uint32 i = 0U; i < pSource->queueCreateInfoCount; ++ i ) {
        toVulkanFormat ( & deviceQueueCreateInfos[i], & pSource->pQueueCreateInfos[i] );
    }

    if ( pSource->pNext != nullptr ) {

        auto currentInVkChain   = reinterpret_cast < VkBaseOutStructure * > ( pDestination );
        auto currentInChain     = reinterpret_cast < __C_ENG_TYPE ( GenericInStructure ) const * > ( pSource->pNext );

        while ( currentInChain != nullptr ) {
            VkBaseOutStructure * nextInVkChain = nullptr;

            switch ( currentInChain->structureType ) {

#if __C_ENG_VULKAN_API_EXTENSION_DEVICE_MEMORY_REPORT_AVAILABLE

                case StructureTypeDeviceDeviceMemoryReportCreateInfo:                             { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceDeviceMemoryReportCreateInfo );                 toVulkanFormat ( & deviceDeviceMemoryReportCreateInfo,                  reinterpret_cast < __C_ENG_TYPE ( DeviceDeviceMemoryReportCreateInfo ) const * > ( currentInChain ) );                              break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTICS_CONFIG_AVAILABLE

                case StructureTypeDeviceDiagnosticsConfigCreateInfoNVidia:                        { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceDiagnosticsConfigCreateInfo );                  toVulkanFormat ( & deviceDiagnosticsConfigCreateInfo,                   reinterpret_cast < __C_ENG_TYPE ( DeviceDiagnosticsConfigCreateInfoNVidia ) const * > ( currentInChain ) );                         break; }

#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

                case StructureTypeDeviceGroupDeviceCreateInfo:                                    { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceGroupDeviceCreateInfo );                        toVulkanFormat ( & deviceGroupDeviceCreateInfo,                         reinterpret_cast < __C_ENG_TYPE ( DeviceGroupDeviceCreateInfo ) const * > ( currentInChain ) );                                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_MEMORY_OVERALLOCATION_BEHAVIOUR_AVAILABLE

                case StructureTypeDeviceMemoryOverAllocationCreateInfoAMD:                        { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceMemoryOverallocationCreateInfo );               toVulkanFormat ( & deviceMemoryOverallocationCreateInfo,                reinterpret_cast < __C_ENG_TYPE ( DeviceMemoryOverallocationCreateInfoAMD ) const * > ( currentInChain ) );                         break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypeDevicePrivateDataCreateInfo:                                    { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & devicePrivateDataCreateInfo );                        toVulkanFormat ( & devicePrivateDataCreateInfo,                         reinterpret_cast < __C_ENG_TYPE ( DevicePrivateDataCreateInfo ) const * > ( currentInChain ) );                                     break; }

#endif



#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

                case StructureTypePhysicalDeviceFeatures:                                         { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceExtendedFeatures );                             toVulkanFormat ( & deviceExtendedFeatures,                              reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceExtendedFeatures ) const * > ( currentInChain ) );                                  break; }

                case StructureTypePhysicalDeviceVulkan_1_1_Features:                              { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceVulkan11Features );                             toVulkanFormat ( & deviceVulkan11Features,                              reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceVulkan11Features ) const * > ( currentInChain ) );                                  break; }
                case StructureTypePhysicalDevice16BitStorageFeatures:                             { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & device16BitStorageFeatures );                         toVulkanFormat ( & device16BitStorageFeatures,                          reinterpret_cast < __C_ENG_TYPE ( PhysicalDevice16BitStorageFeatures ) const * > ( currentInChain ) );                              break; }
                case StructureTypePhysicalDeviceMultiviewFeatures:                                { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceMultiviewFeatures );                            toVulkanFormat ( & deviceMultiviewFeatures,                             reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceMultiviewFeatures ) const * > ( currentInChain ) );                                 break; }
                case StructureTypePhysicalDeviceProtectedMemoryFeatures:                          { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceProtectedMemoryFeatures );                      toVulkanFormat ( & deviceProtectedMemoryFeatures,                       reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceProtectedMemoryFeatures ) const * > ( currentInChain ) );                           break; }
                case StructureTypePhysicalDeviceSamplerYCBCRConversionFeatures:                   { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceSamplerYCBCRConversionFeatures );               toVulkanFormat ( & deviceSamplerYCBCRConversionFeatures,                reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceSamplerYCBCRConversionFeatures ) const * > ( currentInChain ) );                    break; }
                case StructureTypePhysicalDeviceShaderDrawParametersFeatures:                     { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceShaderDrawParametersFeatures );                 toVulkanFormat ( & deviceShaderDrawParametersFeatures,                  reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceShaderDrawParametersFeatures ) const * > ( currentInChain ) );                      break; }
                case StructureTypePhysicalDeviceVariablePointersFeatures:                         { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceVariablePointersFeatures );                     toVulkanFormat ( & deviceVariablePointersFeatures,                      reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceVariablePointersFeatures ) const * > ( currentInChain ) );                          break; }

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

                case StructureTypePhysicalDeviceVulkan_1_2_Features:                              { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceVulkan12Features );                             toVulkanFormat ( & deviceVulkan12Features,                              reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceVulkan12Features ) const * > ( currentInChain ) );                                  break; }
                case StructureTypePhysicalDevice8BitStorageFeatures:                              { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & device8BitStorageFeatures );                          toVulkanFormat ( & device8BitStorageFeatures,                           reinterpret_cast < __C_ENG_TYPE ( PhysicalDevice8BitStorageFeatures ) const * > ( currentInChain ) );                               break; }
                case StructureTypePhysicalDeviceBufferDeviceAddressFeatures:                      { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceBufferDeviceAddressFeatures );                  toVulkanFormat ( & deviceBufferDeviceAddressFeatures,                   reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceBufferDeviceAddressFeatures ) const * > ( currentInChain ) );                       break; }
                case StructureTypePhysicalDeviceDescriptorIndexingFeatures:                       { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceDescriptorIndexingFeatures );                   toVulkanFormat ( & deviceDescriptorIndexingFeatures,                    reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceDescriptorIndexingFeatures ) const * > ( currentInChain ) );                        break; }
                case StructureTypePhysicalDeviceHostQueryResetFeatures:                           { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceHostQueryResetFeatures );                       toVulkanFormat ( & deviceHostQueryResetFeatures,                        reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceHostQueryResetFeatures ) const * > ( currentInChain ) );                            break; }
                case StructureTypePhysicalDeviceImagelessFramebufferFeatures:                     { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceImagelessFramebufferFeatures );                 toVulkanFormat ( & deviceImagelessFramebufferFeatures,                  reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceImagelessFramebufferFeatures ) const * > ( currentInChain ) );                      break; }
                case StructureTypePhysicalDeviceScalarBlockLayoutFeatures:                        { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceScalarBlockLayoutFeatures );                    toVulkanFormat ( & deviceScalarBlockLayoutFeatures,                     reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceScalarBlockLayoutFeatures ) const * > ( currentInChain ) );                         break; }
                case StructureTypePhysicalDeviceSeparateDepthStencilLayoutsFeatures:              { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceSeparateDepthStencilLayoutsFeatures );          toVulkanFormat ( & deviceSeparateDepthStencilLayoutsFeatures,           reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceSeparateDepthStencilLayoutsFeatures ) const * > ( currentInChain ) );               break; }
                case StructureTypePhysicalDeviceShaderAtomicInt64Features:                        { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceShaderAtomicInt64Features );                    toVulkanFormat ( & deviceShaderAtomicInt64Features,                     reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceShaderAtomicInt64Features ) const * > ( currentInChain ) );                         break; }
                case StructureTypePhysicalDeviceShaderFloat16Int8Features:                        { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceShaderFloat16Int8Features );                    toVulkanFormat ( & deviceShaderFloat16Int8Features,                     reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceShaderFloat16Int8Features ) const * > ( currentInChain ) );                         break; }
                case StructureTypePhysicalDeviceShaderSubgroupExtendedTypesFeatures:              { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceShaderSubgroupExtendedTypesFeatures );          toVulkanFormat ( & deviceShaderSubgroupExtendedTypesFeatures,           reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceShaderSubgroupExtendedTypesFeatures ) const * > ( currentInChain ) );               break; }
                case StructureTypePhysicalDeviceTimelineSemaphoreFeatures:                        { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceTimelineSemaphoreFeatures );                    toVulkanFormat ( & deviceTimelineSemaphoreFeatures,                     reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceTimelineSemaphoreFeatures ) const * > ( currentInChain ) );                         break; }
                case StructureTypePhysicalDeviceUniformBufferStandardLayoutFeatures:              { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceUniformBufferStandardLayoutFeatures );          toVulkanFormat ( & deviceUniformBufferStandardLayoutFeatures,           reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceUniformBufferStandardLayoutFeatures ) const * > ( currentInChain ) );               break; }
                case StructureTypePhysicalDeviceVulkanMemoryModelFeatures:                        { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceVulkanMemoryModelFeatures );                    toVulkanFormat ( & deviceVulkanMemoryModelFeatures,                     reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceVulkanMemoryModelFeatures ) const * > ( currentInChain ) );                         break; }

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceVulkan_1_3_Features:                              { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceVulkan13Features );                             toVulkanFormat ( & deviceVulkan13Features,                              reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceVulkan13Features ) const * > ( currentInChain ) );                                  break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_4444_FORMATS_AVAILABLE

                case StructureTypePhysicalDevice4444FormatsFeatures:                              { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & device4444FormatsFeatures );                          toVulkanFormat ( & device4444FormatsFeatures,                           reinterpret_cast < __C_ENG_TYPE ( PhysicalDevice4444FormatsFeatures ) const * > ( currentInChain ) );                               break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ASTC_DECODE_MODE_AVAILABLE

                case StructureTypePhysicalDeviceASTCDecodeFeatures:                               { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceAstcDecodeFeatures );                           toVulkanFormat ( & deviceAstcDecodeFeatures,                            reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceASTCDecodeFeatures ) const * > ( currentInChain ) );                                break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE

                case StructureTypePhysicalDeviceAccelerationStructureFeatures:                    { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceAccelerationStructureFeatures );                toVulkanFormat ( & deviceAccelerationStructureFeatures,                 reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceAccelerationStructureFeatures ) const * > ( currentInChain ) );                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE

                case StructureTypePhysicalDeviceBlendOperationAdvancedFeatures:                   { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceBlendOperationAdvancedFeatures );               toVulkanFormat ( & deviceBlendOperationAdvancedFeatures,                reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceBlendOperationAdvancedFeatures ) const * > ( currentInChain ) );                    break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BORDER_COLOR_SWIZZLE_AVAILABLE

                case StructureTypePhysicalDeviceBorderColorSwizzleFeatures:                       { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceBorderColorSwizzleFeatures );                   toVulkanFormat ( & deviceBorderColorSwizzleFeatures,                    reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceBorderColorSwizzleFeatures ) const * > ( currentInChain ) );                        break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_DEVICE_COHERENT_MEMORY_AVAILABLE

                case StructureTypePhysicalDeviceCoherentMemoryFeaturesAMD:                        { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceCoherentMemoryFeatures );                       toVulkanFormat ( & deviceCoherentMemoryFeatures,                        reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceCoherentMemoryFeaturesAMD ) const * > ( currentInChain ) );                         break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_COLOR_WRITE_ENABLE_AVAILABLE

                case StructureTypePhysicalDeviceColorWriteEnableFeatures:                         { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceColorWriteEnableFeatures );                     toVulkanFormat ( & deviceColorWriteEnableFeatures,                      reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceColorWriteEnableFeatures ) const * > ( currentInChain ) );                          break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COMPUTE_SHADER_DERIVATIVES_AVAILABLE

                case StructureTypePhysicalDeviceComputeShaderDerivativesFeaturesNVidia:           { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceComputeShaderDerivativesFeatures );             toVulkanFormat ( & deviceComputeShaderDerivativesFeatures,              reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceComputeShaderDerivativesFeaturesNVidia ) const * > ( currentInChain ) );            break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE

                case StructureTypePhysicalDeviceConditionalRenderingFeatures:                     { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceConditionalRenderingFeatures );                 toVulkanFormat ( & deviceConditionalRenderingFeatures,                  reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceConditionalRenderingFeatures ) const * > ( currentInChain ) );                      break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE

                case StructureTypePhysicalDeviceCooperativeMatrixFeaturesNVidia:                  { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceCooperativeMatrixFeatures );                    toVulkanFormat ( & deviceCooperativeMatrixFeatures,                     reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceCooperativeMatrixFeaturesNVidia ) const * > ( currentInChain ) );                   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CORNER_SAMPLED_IMAGE_AVAILABLE

                case StructureTypePhysicalDeviceCornerSampledImageFeaturesNVidia:                 { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceDeviceCornerSampledImageFeatures );             toVulkanFormat ( & deviceDeviceCornerSampledImageFeatures,              reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceCornerSampledImageFeaturesNVidia ) const * > ( currentInChain ) );                  break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COVERAGE_REDUCTION_MODE_AVAILABLE

                case StructureTypePhysicalDeviceCoverageReductionModeFeaturesNVidia:              { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceCoverageReductionModeFeatures );                toVulkanFormat ( & deviceCoverageReductionModeFeatures,                 reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceCoverageReductionModeFeaturesNVidia ) const * > ( currentInChain ) );               break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE

                case StructureTypePhysicalDeviceCustomBorderColorFeatures:                        { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceCustomBorderColorFeatures );                    toVulkanFormat ( & deviceCustomBorderColorFeatures,                     reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceCustomBorderColorFeatures ) const * > ( currentInChain ) );                         break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_IMAGE_ALIASING_AVAILABLE

                case StructureTypePhysicalDeviceDedicatedAllocationImageAliasingFeaturesNVidia:   { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceDedicatedAllocationImageAliasingFeatures );     toVulkanFormat ( & deviceDedicatedAllocationImageAliasingFeatures,      reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNVidia ) const * > ( currentInChain ) );    break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_CONTROL_AVAILABLE

                case StructureTypePhysicalDeviceDepthClipControlFeatures:                         { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceDepthClipControlFeatures );                     toVulkanFormat ( & deviceDepthClipControlFeatures,                      reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceDepthClipControlFeatures ) const * > ( currentInChain ) );                          break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_ENABLE_AVAILABLE

                case StructureTypePhysicalDeviceDepthClipEnableFeatures:                          { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceDepthClipEnableFeatures );                      toVulkanFormat ( & deviceDepthClipEnableFeatures,                       reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceDepthClipEnableFeatures ) const * > ( currentInChain ) );                           break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE

                case StructureTypePhysicalDeviceDeviceGeneratedCommandsFeaturesNVidia:            { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceDeviceGeneratedCommandsFeatures );              toVulkanFormat ( & deviceDeviceGeneratedCommandsFeatures,               reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceDeviceGeneratedCommandsFeaturesNVidia ) const * > ( currentInChain ) );             break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEVICE_MEMORY_REPORT_AVAILABLE

                case StructureTypePhysicalDeviceDeviceMemoryReportFeatures:                       { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceDeviceMemoryReportFeatures );                   toVulkanFormat ( & deviceDeviceMemoryReportFeatures,                    reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceDeviceMemoryReportFeatures ) const * > ( currentInChain ) );                        break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTICS_CONFIG_AVAILABLE

                case StructureTypePhysicalDeviceDiagnosticsConfigFeaturesNVidia:                  { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceDiagnosticsConfigFeatures );                    toVulkanFormat ( & deviceDiagnosticsConfigFeatures,                     reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceDiagnosticsConfigFeaturesNVidia ) const * > ( currentInChain ) );                   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceDynamicRenderingFeatures:                         { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceDynamicRenderingFeatures );                     toVulkanFormat ( & deviceDynamicRenderingFeatures,                      reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceDynamicRenderingFeatures ) const * > ( currentInChain ) );                          break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SCISSOR_EXCLUSIVE_AVAILABLE

                case StructureTypePhysicalDeviceExclusiveScissorFeaturesNVidia:                   { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceExclusiveScissorFeatures );                     toVulkanFormat ( & deviceExclusiveScissorFeatures,                      reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceExclusiveScissorFeaturesNVidia ) const * > ( currentInChain ) );                    break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE

                case StructureTypePhysicalDeviceExtendedDynamicStateFeatures:                     { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceExtendedDynamicStateFeatures );                 toVulkanFormat ( & deviceExtendedDynamicStateFeatures,                  reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceExtendedDynamicStateFeatures ) const * > ( currentInChain ) );                      break; }
                case StructureTypePhysicalDeviceExtendedDynamicState2Features:                    { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceExtendedDynamicState2Features );                toVulkanFormat ( & deviceExtendedDynamicState2Features,                 reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceExtendedDynamicState2Features ) const * > ( currentInChain ) );                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_RDMA_AVAILABLE

                case StructureTypePhysicalDeviceExternalMemoryRDMAFeaturesNVidia:                 { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceExternalMemoryRDMAFeatures );                   toVulkanFormat ( & deviceExternalMemoryRDMAFeatures,                    reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceExternalMemoryRDMAFeaturesNVidia ) const * > ( currentInChain ) );                  break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

                case StructureTypePhysicalDeviceFragmentDensityMapFeatures:                       { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceFragmentDensityMapFeatures );                   toVulkanFormat ( & deviceFragmentDensityMapFeatures,                    reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMapFeatures ) const * > ( currentInChain ) );                        break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE

                case StructureTypePhysicalDeviceFragmentDensityMap2Features:                      { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceFragmentDensityMap2Features );                  toVulkanFormat ( & deviceFragmentDensityMap2Features,                   reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMap2Features ) const * > ( currentInChain ) );                       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE

                case StructureTypePhysicalDeviceFragmentDensityMapOffsetFeaturesQualcomm:         { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceFragmentDensityMapOffsetFeatures );             toVulkanFormat ( & deviceFragmentDensityMapOffsetFeatures,              reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMapOffsetFeaturesQualcomm ) const * > ( currentInChain ) );          break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADER_BARYCENTRIC_AVAILABLE

                case StructureTypePhysicalDeviceFragmentShaderBarycentricFeaturesNVidia:          { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceFragmentShaderBarycentricFeatures );            toVulkanFormat ( & deviceFragmentShaderBarycentricFeatures,             reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceFragmentShaderBarycentricFeaturesNVidia ) const * > ( currentInChain ) );           break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_SHADER_INTERLOCK_AVAILABLE

                case StructureTypePhysicalDeviceFragmentShaderInterlockFeatures:                  { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceFragmentShaderInterlockFeatures );              toVulkanFormat ( & deviceFragmentShaderInterlockFeatures,               reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceFragmentShaderInterlockFeatures ) const * > ( currentInChain ) );                   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE

                case StructureTypePhysicalDeviceFragmentShadingRateEnumsFeaturesNVidia:           { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceFragmentShadingRateEnumsFeatures );             toVulkanFormat ( & deviceFragmentShadingRateEnumsFeatures,              reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceFragmentShadingRateEnumsFeaturesNVidia ) const * > ( currentInChain ) );            break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE

                case StructureTypePhysicalDeviceFragmentShadingRateFeatures:                      { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceFragmentShadingRateFeatures );                  toVulkanFormat ( & deviceFragmentShadingRateFeatures,                   reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceFragmentShadingRateFeatures ) const * > ( currentInChain ) );                       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE

                case StructureTypePhysicalDeviceGlobalPriorityQueryFeatures:                      { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceGlobalPriorityQueryFeatures );                  toVulkanFormat ( & deviceGlobalPriorityQueryFeatures,                   reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceGlobalPriorityQueryFeatures ) const * > ( currentInChain ) );                       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_ROBUSTNESS_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceImageRobustnessFeatures:                          { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceImageRobustnessFeatures );                      toVulkanFormat ( & deviceImageRobustnessFeatures,                       reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceImageRobustnessFeatures ) const * > ( currentInChain ) );                           break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_VIEW_MIN_LOD_AVAILABLE

                case StructureTypePhysicalDeviceImageViewMinLODFeatures:                          { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceImageViewMinLODFeatures );                      toVulkanFormat ( & deviceImageViewMinLODFeatures,                       reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceImageViewMinLODFeatures ) const * > ( currentInChain ) );                           break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INDEX_TYPE_UINT8_AVAILABLE

                case StructureTypePhysicalDeviceIndexTypeUInt8Features:                           { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceIndexTypeUInt8Features );                       toVulkanFormat ( & deviceIndexTypeUInt8Features,                        reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceIndexTypeUInt8Features ) const * > ( currentInChain ) );                            break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_INHERITED_VIEWPORT_SCISSOR_AVAILABLE

                case StructureTypePhysicalDeviceInheritedViewportScissorFeaturesNVidia:           { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceInheritedViewportScissorFeatures );             toVulkanFormat ( & deviceInheritedViewportScissorFeatures,              reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceInheritedViewportScissorFeaturesNVidia ) const * > ( currentInChain ) );            break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceInlineUniformBlockFeatures:                       { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceInlineUniformBlockFeatures );                   toVulkanFormat ( & deviceInlineUniformBlockFeatures,                    reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceInlineUniformBlockFeatures ) const * > ( currentInChain ) );                        break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_INVOCATION_MASK_AVAILABLE

                case StructureTypePhysicalDeviceInvocationMaskFeaturesHuawei:                     { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceInvocationMaskFeatures );                       toVulkanFormat ( & deviceInvocationMaskFeatures,                        reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceInvocationMaskFeaturesHuawei ) const * > ( currentInChain ) );                      break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE

                case StructureTypePhysicalDeviceLineRasterizationFeatures:                        { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceLineRasterizationFeatures );                    toVulkanFormat ( & deviceLineRasterizationFeatures,                     reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceLineRasterizationFeatures ) const * > ( currentInChain ) );                         break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_LINEAR_COLOR_ATTACHMENT_AVAILABLE

                case StructureTypePhysicalDeviceLinearColorAttachmentFeaturesNVidia:              { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceLinearColorAttachmentFeatures );                toVulkanFormat ( & deviceLinearColorAttachmentFeatures,                 reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceLinearColorAttachmentFeaturesNVidia ) const * > ( currentInChain ) );               break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceMaintenance4Features:                             { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceMaintenance4Features );                         toVulkanFormat ( & deviceMaintenance4Features,                          reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceMaintenance4Features ) const * > ( currentInChain ) );                              break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_PRIORITY_AVAILABLE

                case StructureTypePhysicalDeviceMemoryPriorityFeatures:                           { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceMemoryPriorityFeatures );                       toVulkanFormat ( & deviceMemoryPriorityFeatures,                        reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceMemoryPriorityFeatures ) const * > ( currentInChain ) );                            break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE

                case StructureTypePhysicalDeviceMeshShaderFeaturesNVidia:                         { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceMeshShaderFeatures );                           toVulkanFormat ( & deviceMeshShaderFeatures,                            reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceMeshShaderFeaturesNVidia ) const * > ( currentInChain ) );                          break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE

                case StructureTypePhysicalDeviceMultiDrawFeatures:                                { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceMultiDrawFeatures );                            toVulkanFormat ( & deviceMultiDrawFeatures,                             reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceMultiDrawFeatures ) const * > ( currentInChain ) );                                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE

                case StructureTypePhysicalDeviceMutableDescriptorTypeFeaturesValve:               { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceMutableDescriptorTypeFeatures );                toVulkanFormat ( & deviceMutableDescriptorTypeFeatures,                 reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceMutableDescriptorTypeFeaturesValve ) const * > ( currentInChain ) );                break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PAGEABLE_DEVICE_LOCAL_MEMORY_AVAILABLE

                case StructureTypePhysicalDevicePageableDeviceLocalMemoryFeatures:                { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & devicePageableDeviceLocalMemoryFeatures );            toVulkanFormat ( & devicePageableDeviceLocalMemoryFeatures,             reinterpret_cast < __C_ENG_TYPE ( PhysicalDevicePageableDeviceLocalMemoryFeatures ) const * > ( currentInChain ) );                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

                case StructureTypePhysicalDevicePerformanceQueryFeatures:                         { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & devicePerformanceQueryFeatures );                     toVulkanFormat ( & devicePerformanceQueryFeatures,                      reinterpret_cast < __C_ENG_TYPE ( PhysicalDevicePerformanceQueryFeatures ) const * > ( currentInChain ) );                          break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDevicePipelineCreationCacheControlFeatures:             { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & devicePipelineCreationCacheControlFeatures );         toVulkanFormat ( & devicePipelineCreationCacheControlFeatures,          reinterpret_cast < __C_ENG_TYPE ( PhysicalDevicePipelineCreationCacheControlFeatures ) const * > ( currentInChain ) );              break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE

                case StructureTypePhysicalDevicePipelineExecutablePropertiesFeatures:             { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & devicePipelineExecutablePropertiesFeatures );         toVulkanFormat ( & devicePipelineExecutablePropertiesFeatures,          reinterpret_cast < __C_ENG_TYPE ( PhysicalDevicePipelineExecutablePropertiesFeatures ) const * > ( currentInChain ) );              break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE

                case StructureTypePhysicalDevicePortabilitySubsetFeatures:                        { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & devicePortabilitySubsetFeatures );                    toVulkanFormat ( & devicePortabilitySubsetFeatures,                     reinterpret_cast < __C_ENG_TYPE ( PhysicalDevicePortabilitySubsetFeatures ) const * > ( currentInChain ) );                         break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_ID_AVAILABLE

                case StructureTypePhysicalDevicePresentIDFeatures:                                { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & devicePresentIDFeatures );                            toVulkanFormat ( & devicePresentIDFeatures,                             reinterpret_cast < __C_ENG_TYPE ( PhysicalDevicePresentIDFeatures ) const * > ( currentInChain ) );                                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_WAIT_AVAILABLE

                case StructureTypePhysicalDevicePresentWaitFeatures:                              { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & devicePresentWaitFeatures );                          toVulkanFormat ( & devicePresentWaitFeatures,                           reinterpret_cast < __C_ENG_TYPE ( PhysicalDevicePresentWaitFeatures ) const * > ( currentInChain ) );                               break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIMITIVE_TOPOLOGY_LIST_RESTART_AVAILABLE

                case StructureTypePhysicalDevicePrimitiveTopologyListRestartFeatures:             { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & devicePrimitiveTopologyListRestartFeatures );         toVulkanFormat ( & devicePrimitiveTopologyListRestartFeatures,          reinterpret_cast < __C_ENG_TYPE ( PhysicalDevicePrimitiveTopologyListRestartFeatures ) const * > ( currentInChain ) );              break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDevicePrivateDataFeatures:                              { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & devicePrivateDataFeatures );                          toVulkanFormat ( & devicePrivateDataFeatures,                           reinterpret_cast < __C_ENG_TYPE ( PhysicalDevicePrivateDataFeatures ) const * > ( currentInChain ) );                               break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE

                case StructureTypePhysicalDeviceProvokingVertexFeatures:                          { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceProvokingVertexFeatures );                      toVulkanFormat ( & deviceProvokingVertexFeatures,                       reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceProvokingVertexFeatures ) const * > ( currentInChain ) );                           break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_RGBA_10_X_6_FORMATS_AVAILABLE

                case StructureTypePhysicalDeviceRGBA10x6FormatsFeatures:                          { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceRgba10X6FormatsFeatures );                      toVulkanFormat ( & deviceRgba10X6FormatsFeatures,                       reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceRGBA10x6FormatsFeatures ) const * > ( currentInChain ) );                           break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ARM_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_AVAILABLE

                case StructureTypePhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM:    { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceRasterizationOrderAttachmentAccessFeatures );   toVulkanFormat ( & deviceRasterizationOrderAttachmentAccessFeatures,    reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM ) const * > ( currentInChain ) );     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_QUERY_AVAILABLE

                case StructureTypePhysicalDeviceRayQueryFeatures:                                 { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceRayQueryFeatures );                             toVulkanFormat ( & deviceRayQueryFeatures,                              reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceRayQueryFeatures ) const * > ( currentInChain ) );                                  break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE

                case StructureTypePhysicalDeviceRayTracingMotionBlurFeaturesNVidia:               { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceRayTracingMotionBlurFeatures );                 toVulkanFormat ( & deviceRayTracingMotionBlurFeatures,                  reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceRayTracingMotionBlurFeaturesNVidia ) const * > ( currentInChain ) );                break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE

                case StructureTypePhysicalDeviceRayTracingPipelineFeatures:                       { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceRayTracingPipelineFeatures );                   toVulkanFormat ( & deviceRayTracingPipelineFeatures,                    reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceRayTracingPipelineFeatures ) const * > ( currentInChain ) );                        break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_REPRESENTATIVE_FRAGMENT_TEST_AVAILABLE

                case StructureTypePhysicalDeviceRepresentativeFragmentTestFeaturesNVidia:         { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceRepresentativeFragmentTestFeatures );           toVulkanFormat ( & deviceRepresentativeFragmentTestFeatures,            reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceRepresentativeFragmentTestFeaturesNVidia ) const * > ( currentInChain ) );          break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE

                case StructureTypePhysicalDeviceRobustnessFeatures:                               { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceRobustness2Features );                          toVulkanFormat ( & deviceRobustness2Features,                           reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceRobustnessFeatures ) const * > ( currentInChain ) );                                break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_AVAILABLE

                case StructureTypePhysicalDeviceShaderAtomicFloatFeatures:                        { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceShaderAtomicFloatFeatures );                    toVulkanFormat ( & deviceShaderAtomicFloatFeatures,                     reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceShaderAtomicFloatFeatures ) const * > ( currentInChain ) );                         break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_2_AVAILABLE

                case StructureTypePhysicalDeviceShaderAtomicFloat2Features:                       { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceShaderAtomicFloat2Features );                   toVulkanFormat ( & deviceShaderAtomicFloat2Features,                    reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceShaderAtomicFloat2Features ) const * > ( currentInChain ) );                        break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_CLOCK_AVAILABLE

                case StructureTypePhysicalDeviceShaderClockFeatures:                              { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceShaderClockFeatures );                          toVulkanFormat ( & deviceShaderClockFeatures,                           reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceShaderClockFeatures ) const * > ( currentInChain ) );                               break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_DEMOTE_TO_HELPER_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceShaderDemoteToHelperInvocationFeatures:           { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceShaderDemoteToHelperInvocationFeatures );       toVulkanFormat ( & deviceShaderDemoteToHelperInvocationFeatures,        reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceShaderDemoteToHelperInvocationFeatures ) const * > ( currentInChain ) );            break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_IMAGE_ATOMIC_INT64_AVAILABLE

                case StructureTypePhysicalDeviceShaderImageAtomicInt64Features:                   { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceShaderImageAtomicInt64Features );               toVulkanFormat ( & deviceShaderImageAtomicInt64Features,                reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceShaderImageAtomicInt64Features ) const * > ( currentInChain ) );                    break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_IMAGE_FOOTPRINT_AVAILABLE

                case StructureTypePhysicalDeviceShaderImageFootprintFeaturesNVidia:               { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceShaderImageFootprintFeatures );                 toVulkanFormat ( & deviceShaderImageFootprintFeatures,                  reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceShaderImageFootprintFeaturesNVidia ) const * > ( currentInChain ) );                break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE

                case StructureTypePhysicalDeviceShaderSmBuiltinsFeaturesNVidia:                   { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceShaderSmBuiltinsFeatures );                     toVulkanFormat ( & deviceShaderSmBuiltinsFeatures,                      reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceShaderSMBuiltinsFeaturesNVidia ) const * > ( currentInChain ) );                    break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_SUBGROUP_UNIFORM_CONTROL_FLOW_AVAILABLE

                case StructureTypePhysicalDeviceShaderSubgroupUniformControlFlowFeatures:         { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceShaderSubgroupUniformControlFlowFeatures );     toVulkanFormat ( & deviceShaderSubgroupUniformControlFlowFeatures,      reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceShaderSubgroupUniformControlFlowFeatures ) const * > ( currentInChain ) );          break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_TERMINATE_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceShaderTerminateInvocationFeatures:                { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceShaderTerminateInvocationFeatures );            toVulkanFormat ( & deviceShaderTerminateInvocationFeatures,             reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceShaderTerminateInvocationFeatures ) const * > ( currentInChain ) );                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE

                case StructureTypePhysicalDeviceShadingRateImageFeaturesNVidia:                   { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceShadingRateImageFeatures );                     toVulkanFormat ( & deviceShadingRateImageFeatures,                      reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceShadingRateImageFeaturesNVidia ) const * > ( currentInChain ) );                    break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceSubgroupSizeControlFeatures:                      { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceSubgroupSizeControlFeatures );                  toVulkanFormat ( & deviceSubgroupSizeControlFeatures,                   reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceSubgroupSizeControlFeatures ) const * > ( currentInChain ) );                       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE

                case StructureTypePhysicalDeviceSubpassShadingFeaturesHuawei:                     { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceSubpassShadingFeatures );                       toVulkanFormat ( & deviceSubpassShadingFeatures,                        reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceSubpassShadingFeaturesHuawei ) const * > ( currentInChain ) );                      break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceSynchronizationFeatures:                          { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceSynchronization2Features );                     toVulkanFormat ( & deviceSynchronization2Features,                      reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceSynchronizationFeatures ) const * > ( currentInChain ) );                           break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceTexelBufferAlignmentFeatures:                     { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceTexelBufferAlignmentFeatures );                 toVulkanFormat ( & deviceTexelBufferAlignmentFeatures,                  reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceTexelBufferAlignmentFeatures ) const * > ( currentInChain ) );                      break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXTURE_COMPRESSION_ASTC_HDR_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceTextureCompressionASTCHDRFeatures:                { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceTextureCompressionASTCHDRFeatures );            toVulkanFormat ( & deviceTextureCompressionASTCHDRFeatures,             reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceTextureCompressionASTCHDRFeatures ) const * > ( currentInChain ) );                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE

                case StructureTypePhysicalDeviceTransformFeedbackFeatures:                        { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceTransformFeedbackFeatures );                    toVulkanFormat ( & deviceTransformFeedbackFeatures,                     reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceTransformFeedbackFeatures ) const * > ( currentInChain ) );                         break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE

                case StructureTypePhysicalDeviceVertexAttributeDivisorFeatures:                   { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceVertexAttributeDivisorFeatures );               toVulkanFormat ( & deviceVertexAttributeDivisorFeatures,                reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceVertexAttributeDivisorFeatures ) const * > ( currentInChain ) );                    break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_INPUT_DYNAMIC_STATE_AVAILABLE

                case StructureTypePhysicalDeviceVertexInputDynamicStateFeatures:                  { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceVertexInputDynamicStateFeatures );              toVulkanFormat ( & deviceVertexInputDynamicStateFeatures,               reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceVertexInputDynamicStateFeatures ) const * > ( currentInChain ) );                   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceShaderIntegerDotProductFeatures:                  { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceShaderIntegerDotProductFeatures );              toVulkanFormat ( & deviceShaderIntegerDotProductFeatures,               reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceShaderIntegerDotProductFeatures ) const * > ( currentInChain ) );                   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_SHADER_INTEGER_FUNCTIONS_AVAILABLE

                case StructureTypePhysicalDeviceShaderIntegerFunctionsFeaturesIntel:              { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceShaderIntegerFunctions2Features );              toVulkanFormat ( & deviceShaderIntegerFunctions2Features,               reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceShaderIntegerFunctionsFeaturesIntel ) const * > ( currentInChain ) );               break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_AVAILABLE

                case StructureTypePhysicalDeviceWorkgroupMemoryExplicitLayoutFeatures:            { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceWorkgroupMemoryExplicitLayoutFeatures );        toVulkanFormat ( & deviceWorkgroupMemoryExplicitLayoutFeatures,         reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceWorkgroupMemoryExplicitLayoutFeatures ) const * > ( currentInChain ) );             break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_2_PLANE_444_FORMATS_AVAILABLE

                case StructureTypePhysicalDeviceYCBCR2Plane444FormatsFeatures:                    { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceYCBCR2Plane444FormatsFeatures );                toVulkanFormat ( & deviceYCBCR2Plane444FormatsFeatures,                 reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceYCBCR2Plane444FormatsFeatures ) const * > ( currentInChain ) );                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_IMAGE_ARRAYS_AVAILABLE

                case StructureTypePhysicalDeviceYCBCRImageArraysFeatures:                         { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceYCBCRImageArraysFeatures );                     toVulkanFormat ( & deviceYCBCRImageArraysFeatures,                      reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceYCBCRImageArraysFeatures ) const * > ( currentInChain ) );                          break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ZERO_INITIALIZE_WORKGROUP_MEMORY_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                case StructureTypePhysicalDeviceZeroInitializeWorkgroupMemoryFeatures:            { nextInVkChain = reinterpret_cast < VkBaseOutStructure * > ( & deviceZeroInitializeWorkgroupMemoryFeatures );        toVulkanFormat ( & deviceZeroInitializeWorkgroupMemoryFeatures,         reinterpret_cast < __C_ENG_TYPE ( PhysicalDeviceZeroInitializeWorkgroupMemoryFeatures ) const * > ( currentInChain ) );             break; }

#endif

                default:                                                                          { break; }

            }

            currentInChain = currentInChain->pNext;
            currentInVkChain = currentInVkChain->pNext = nextInVkChain; // NOLINT(clion-misra-cpp2008-6-2-1)
        }

        if ( currentInVkChain != nullptr ) {
            currentInVkChain->pNext = nullptr;
        }
    }
}

auto vulkan :: createDevice (
        __C_ENG_TYPE ( PhysicalDeviceHandle )           physicalDeviceHandle,
        __C_ENG_TYPE ( DeviceCreateInfo )       const * pDeviceCreateInfo,
        __C_ENG_TYPE ( AllocationCallbacks )    const * pAllocationCallbacks,
        __C_ENG_TYPE ( DeviceHandle )                 * pDeviceHandle
) noexcept -> __C_ENG_TYPE ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if (
            physicalDeviceHandle    == nullptr ||
            pDeviceCreateInfo       == nullptr ||
            pDeviceHandle           == nullptr
    ) {
        return ResultErrorIllegalArgument;
    }

#endif

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( ! validate ( pDeviceCreateInfo, physicalDeviceHandle ) ) {
        return ResultErrorInvalidUsage;
    }

    if ( pDeviceCreateInfo->queueCreateInfoCount > __C_ENG_VULKAN_CORE_DEVICE_QUEUE_FAMILY_CREATE_INFO_MAX_COUNT ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION (
            lastCreatedInstance,
            pVkCreateDevice,
            CREATE_DEVICE
    )

    VkAllocationCallbacks * pUsedAllocationCallback = nullptr;

    if ( pAllocationCallbacks != nullptr ) {
        pUsedAllocationCallback = & allocationCallbacks;
        toVulkanFormat ( pAllocationCallbacks, pUsedAllocationCallback );
    }

    toVulkanFormat ( & deviceCreateInfo, pDeviceCreateInfo );

    return static_cast < __C_ENG_TYPE ( Result ) > (
            pVkCreateDevice (
                    physicalDeviceHandle,
                    & deviceCreateInfo,
                    pUsedAllocationCallback,
                    pDeviceHandle
            )
    );
}

auto vulkan :: utility :: chainFeaturesFromDetails (
        __C_ENG_TYPE ( PhysicalDeviceExtendedFeatures )       * pExtendedFeatures,
        __C_ENG_TYPE ( PhysicalDeviceDetails )          const * pDetails
) noexcept -> void {
    createChain ( const_cast < __C_ENG_TYPE ( PhysicalDeviceDetails ) * > ( pDetails ), nullptr, pExtendedFeatures ); // NOLINT(clion-misra-cpp2008-5-2-5)
}

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

auto vulkan :: enumeratePhysicalDeviceExtensionProperties (
        __C_ENG_TYPE ( PhysicalDeviceHandle )   handle,
        uint32                                * pExtensionCount,
        __C_ENG_TYPE ( ExtensionProperties )  * pExtensions
) noexcept -> __C_ENG_TYPE ( Result ) {

    return enumeratePhysicalDeviceExtensionProperties (
            handle,
            nullptr,
            pExtensionCount,
            pExtensions
    );
}

auto vulkan :: enumeratePhysicalDeviceExtensionProperties (
        __C_ENG_TYPE ( PhysicalDeviceHandle )   handle,
        StringLiteral                           layerName,
        uint32                                * pExtensionCount,
        __C_ENG_TYPE ( ExtensionProperties )  * pExtensions
) noexcept -> __C_ENG_TYPE ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if (
            handle          == nullptr ||
            pExtensionCount == nullptr
    ) {
        return ResultErrorIllegalArgument;
    }

#endif

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION (
            lastCreatedInstance,
            pVkEnumerateDeviceExtensionProperties,
            ENUMERATE_DEVICE_EXTENSION_PROPERTIES
    )

    if ( pExtensions == nullptr ) {
        return static_cast < __C_ENG_TYPE ( Result ) > (
                pVkEnumerateDeviceExtensionProperties (
                        handle,
                        layerName,
                        pExtensionCount,
                        nullptr
                )
        );
    }

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if ( * pExtensionCount > __C_ENG_VULKAN_CORE_LAYER_EXTENSION_MAX_COUNT ) {
        return ResultErrorConfigurationArraySizeSmall;
    }

#endif

    result = pVkEnumerateDeviceExtensionProperties (
            handle,
            layerName,
            pExtensionCount,
            & extensionProperties[0]
    );

    if ( result != VkResult :: VK_SUCCESS ) {
        return static_cast < __C_ENG_TYPE ( Result ) > ( result );
    }

    for ( uint32 i = 0U; i < * pExtensionCount; ++ i ) {
        (void) std :: memcpy ( & pExtensions[i].name[0], & extensionProperties[i].extensionName[0], sizeof ( extensionProperties[i].extensionName[0] ) * VK_MAX_EXTENSION_NAME_SIZE );
        pExtensions[i].specVersion = extensionProperties[i].specVersion;
    }

    return ResultSuccess;
}

#endif

auto vulkan :: getPhysicalDeviceSurfaceSupport (
        __C_ENG_TYPE ( PhysicalDeviceHandle )   deviceHandle,
        cds :: uint32                           queueFamilyIndex,
        __C_ENG_TYPE ( SurfaceHandle )          surfaceHandle,
        bool                                  * pSupport
) noexcept -> __C_ENG_TYPE ( Result ) {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

    if (
            deviceHandle    == nullptr ||
            surfaceHandle   == nullptr ||
            pSupport        == nullptr
    ) {
        return ResultErrorIllegalArgument;
    }

#endif

    __C_ENG_LOOKUP_VULKAN_INSTANCE_FUNCTION (
            lastCreatedInstance,
            pVkGetPhysicalDeviceSurfaceSupport,
            GET_PHYSICAL_DEVICE_SURFACE_SUPPORT
    )

    __C_ENG_TYPE ( Bool ) support = VK_FALSE;

    result = pVkGetPhysicalDeviceSurfaceSupport (
            deviceHandle,
            queueFamilyIndex,
            surfaceHandle,
            & support
    );

    if ( result != VK_SUCCESS ) {
        return static_cast < __C_ENG_TYPE ( Result ) > ( result );
    }

    * pSupport = support == VK_TRUE;

    return ResultSuccess;
}
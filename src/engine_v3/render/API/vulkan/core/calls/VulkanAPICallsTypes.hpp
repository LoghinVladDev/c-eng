//
// Created by loghin on 16.02.2022.
//

#ifndef C_ENG_VULKANAPICALLSTYPES_HPP
#define C_ENG_VULKANAPICALLSTYPES_HPP

#include "VulkanAPICallsPrivate.hpp"

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED
#include <CDS/String>
#include <CDS/Long>
#endif

#define C_ENG_MAP_START HEADER
#include <ObjectMapping.hpp>

using GenericContext = void;

using ContextAction = void (*) ( GenericContext * ) noexcept;

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED
class Flags {
private:
    cds :: uint64 _v;

public:
    template < typename T >
    explicit Flags ( T value ) noexcept : _v ( value ) { }
    template < typename T >
    explicit operator T () const noexcept { return _v; }
    inline auto toString () const noexcept -> cds :: String { return "0x" + cds :: Long ( _v ).toString(16); }
};
#endif

enum class ContextType {
    None,
    Shared
};

enum class SharedContextType {
    Unknown,
    Common,
    CreateInstance,
    EnumerateLayerProperties,
    EnumerateExtensionProperties,
    EnumeratePhysicalDevices,
    EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCounters,
    EnumeratePhysicalDeviceGroups,
    CreateDevice,
    GetPhysicalDeviceProperties,
    GetPhysicalDeviceFeatures,
    GetPhysicalDeviceQueueFamilyProperties,
    GetDeviceQueue,
    GetSurface,
    CreateSwapChain,
    GetSwapChain,
    CreateImageView,
    CreateCommandPool,
    AllocateCommandBuffers,
    BeginCommandBuffer,
    SubmitQueue,
    CreateFence,
    GetFence,
    RegisterEvent,
    ImportFenceWin32,
    ImportFenceFd,
    CreateSemaphore,
    GetSemaphore,
    WaitSemaphore,
    SignalSemaphore,
    ImportSemaphoreWin32,
    ImportSemaphoreFd,
    ImportSemaphoreZirconHandleInfoGoogle,
    CreateEvent,
    SetCommandBufferEvent,
    WaitCommandBufferEvent2,
    WaitCommandBufferEvent,
    BeginCommandBufferRendering,
    CreateRenderPass,
    CreateRenderPass2,
    CreateFrameBuffer,
    BeginRenderPass,
    NextSubpass,
    CreateShaderModule,
    GetPhysicalDeviceCooperativeMatrixProperties,
    CreateValidationCache,
    CreateComputePipeline,
    CreateGraphicsPipeline,
    CreateRayTracingPipelineNVidia,
    CreateRayTracingPipeline,
    CreatePipelineCache,
    GetPipelineCommon,
    GetPipelineProperties,
    GetPipelineStatistics,
    GetPipelineInternalRepresentations,
    GetPhysicalDeviceMemoryProperties,
    AllocateMemory,
    GetMemoryWin32,
    GetMemoryFd,
    GetMemoryPlatformIndependent,
    FlushMappedMemoryRanges,
    CreateBuffer,
    CreateBufferView,
    CreateImage,
    GetImageSubresourceLayout,
    GetImageDrmFormatModifierProperties,
    CreateAccelerationStructureKhronos,
    CreateAccelerationStructureNVidia,
    GetAccelerationStructureBuildSizes,
    GetAccelerationStructureMemoryRequirements,
    BindAccelerationStructureMemory,
    GetAccelerationStructureDeviceAddress,
    CreateSampler,
    CreateDescriptorSetLayout,
    GetDescriptorSetLayoutSupport,
    CreatePipelineLayout,
    CreateDescriptorPool,
    AllocateDescriptorSets,
    UpdateDescriptorSets,
    CreateDescriptorUpdateTemplate,
    GetDeviceBufferAddress,
    CreateQueryPool,
    ClearColorImage,
    ClearDepthStencilImage,
    ClearAttachments,
    CopyBuffer,
    CopyBuffer2,
    CopyImage,
    CopyImage2,
    CopyBufferToImageOrImageToBuffer,
    CopyBufferToImageOrImageToBuffer2,
    BlitImage,
    BlitImage2,
    ResolveImage,
};

union SpecializedContextType {
    SharedContextType shared;
};

enum class ParameterType {
    Unknown,

    BoolPtr,
    UInt32,
    UInt32Ptr,
    UInt64,
    UInt64Ptr,
    Float,
    StringLiteral,
    Flags,

    Handle,
    HandlePtr,

    LayerProperties,
    ExtensionProperties,
    PerformanceCounter,
    PerformanceCounterDescription,
    PhysicalDeviceGroupProperties,
    QueueFamilyProperties,
    SurfaceFormat,
    Extent2DPtr,
    CooperativeMatrixPropertiesNVidia,
    ImageSubresourceRange,
    ClearAttachment,
    ClearRect,
    BufferCopy,
    ImageCopy,
    BufferImageCopy,
    ImageBlit,
    ImageResolve,

    PhysicalDevicePropertiesPtr,
    PhysicalDeviceFeaturesPtr,
    AllocationCallbacksPtr,

    Structure,
    StructurePtr,

    DumpArrayPack
};

struct DumpedArray {
    cds :: uint32   const * pCount;
    ParameterType           type;
    cds :: uint32           size;
    void            const * pArray;
};

struct Parameter {
    ParameterType           type;
    void            const * pParam;
};

struct DiagnosticContext {
#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED
    engine :: vulkan :: Type ( Result )     error;
    cds :: StringLiteral                    file;
    cds :: StringLiteral                    function;
    cds :: uint32                           line;
    cds :: String                         * pMessage;
#endif
};

struct DumpContext {
#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED
    ContextType                             contextType;
    SpecializedContextType                  specializedContextType;
    cds :: StringLiteral                    apiFunction;
    cds :: StringLiteral                    apiFunctionDescription;
    cds :: uint32                           paramCount;
    Parameter                               params [ engine :: vulkan :: config :: dumpParameterCount ];
#endif
};

struct RuleSetContext {
    ContextAction onDelete;
};

struct CommonItems {
    DiagnosticContext                   diag;
    DumpContext                         dump;
    RuleSetContext                      ruleSet;
};

struct CommonContext {
    CommonItems                         common;
};

struct CreateInstanceContext {
    CommonItems                         common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
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
    VkValidationFeatureEnableEXT        validationFeatureEnables [ engine :: vulkan :: config :: validationFeatureEnableCount ];
    VkValidationFeatureDisableEXT       validationFeatureDisables [ engine :: vulkan :: config :: validationFeatureDisableCount ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_FLAGS_AVAILABLE
    VkValidationFlagsEXT                validationFlags;
    VkValidationCheckEXT                validationChecks [ engine :: vulkan :: config :: validationCheckCount ];
#endif
};

struct EnumerateLayerPropertiesContext {
    CommonItems                         common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkLayerProperties                   properties [ engine :: vulkan :: config :: layerCount ];
#endif
};

struct EnumerateExtensionPropertiesContext {
    CommonItems                         common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkExtensionProperties               properties [ engine :: vulkan :: config :: layerExtensionCount ];
#endif
};

struct EnumeratePhysicalDevicesContext {
    CommonItems                         common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkPhysicalDevice                    devices [ engine :: vulkan :: config :: physicalDeviceCount ];
#endif
};

struct EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersContext {
    CommonItems                         common;
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
    VkPerformanceCounterKHR             counters [ engine :: vulkan :: config :: queueFamilyPerformanceCounterCount ];
    VkPerformanceCounterDescriptionKHR  descriptions [ engine :: vulkan :: config :: queueFamilyPerformanceCounterCount ];
#endif
};

struct EnumeratePhysicalDeviceGroupsContext {
    CommonItems                         common;
#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    VkPhysicalDeviceGroupProperties     properties [ engine :: vulkan :: config :: physicalDeviceGroupCount ];
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
#if __C_ENG_VULKAN_API_EXTENSION_SHADER_DEMOTE_TO_HELPER_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
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
    CommonItems                                 common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkDeviceCreateInfo                          device;
    VkDeviceQueueCreateInfo                     queues [ engine :: vulkan :: config :: queueFamilyCreateInfoCount ];
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
    CommonItems                                 common;
    DevicePropertiesContext                     properties;
};

struct GetPhysicalDeviceFeaturesContext {
    CommonItems                                 common;
    DeviceFeaturesContext                       features;
};

struct GetPhysicalDeviceQueueFamilyPropertiesContext {
    CommonItems                                     common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkQueueFamilyProperties                         properties [ engine :: vulkan :: config :: queueFamilyCount ];
#endif
#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    VkQueueFamilyProperties2                        properties2 [ engine :: vulkan :: config :: queueFamilyCount ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTIC_CHECKPOINTS_AVAILABLE
    VkQueueFamilyCheckpointPropertiesNV             checkpoints [ engine :: vulkan :: config :: queueFamilyCount ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE
    VkQueueFamilyGlobalPriorityPropertiesEXT        globalPriorities [ engine :: vulkan :: config :: queueFamilyCount ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE
    VkQueueFamilyQueryResultStatusProperties2KHR    queryResultStatuses [ engine :: vulkan :: config :: queueFamilyCount ];
    VkVideoQueueFamilyProperties2KHR                videoQueues [ engine :: vulkan :: config :: queueFamilyCount ];
#endif
};

struct GetDeviceQueueContext {
    CommonItems                                 common;
#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    VkDeviceQueueInfo2                          info2;
#endif
};

struct GetSurfaceContext {
    CommonItems                                 common;
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE
    VkSurfaceCapabilitiesKHR                    capabilities;
    VkSurfaceFormatKHR                          formats [ engine :: vulkan :: config :: surfaceFormatCount ];
    VkPresentModeKHR                            presentModes [ engine :: vulkan :: config :: surfacePresentModeCount ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_DISPLAY_SURFACE_COUNTER_AVAILABLE
    VkSurfaceCapabilities2EXT                   capabilities2;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_GET_SURFACE_CAPABILITIES_AVAILABLE
    VkPhysicalDeviceSurfaceInfo2KHR             surfaceInfo2;
    VkSurfaceFormat2KHR                         formats2 [ engine :: vulkan :: config :: surfaceFormatCount ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_FULL_SCREEN_EXCLUSIVE_AVAILABLE
    VkSurfaceFullScreenExclusiveInfoEXT         fullScreenExclusive;
#endif
};

struct CreateSwapChainContext {
    CommonItems                                 common;
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE
    VkSwapchainCreateInfoKHR                    createInfo;
#endif
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    VkImageFormatListCreateInfo                 formatListCreateInfo;
    VkFormat                                    viewFormats [ engine :: vulkan :: config :: viewFormatCount ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WIN32_SURFACE_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_FULL_SCREEN_EXCLUSIVE_AVAILABLE
    VkSurfaceFullScreenExclusiveWin32Info       fullScreenExclusiveWin32Info;
#endif
};

struct GetSwapChainContext {
    CommonItems                                 common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkImage                                     images [ engine :: vulkan :: config :: swapChainImageCount ];
#endif
};

struct CreateImageViewContext {
    CommonItems                                                 common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkImageViewCreateInfo                                       createInfo;
#endif
#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    VkImageViewUsageCreateInfo                                  usageCreateInfo;
    VkSamplerYcbcrConversionInfo                                samplerYcbcrConversionInfo;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_ASTC_DECODE_MODE_AVAILABLE
    VkImageViewASTCDecodeModeEXT                                astcDecodeMode;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_VIEW_MIN_LOD_AVAILABLE
    VkImageViewMinLodCreateInfoEXT                              minLodCreateInfo;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_DECODE_H264_AVAILABLE
    VkVideoDecodeH264ProfileEXT                                 decodeH264Profile;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_DECODE_H265_AVAILABLE
    VkVideoDecodeH265ProfileEXT                                 decodeH265Profile;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_ENCODE_H264_AVAILABLE
    VkVideoEncodeH264ProfileEXT                                 encodeH264Profile;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_ENCODE_H265_AVAILABLE
    VkVideoEncodeH265ProfileEXT                                 encodeH265Profile;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE
    VkVideoProfileKHR                                           videoProfile;
    VkVideoProfileKHR                                           videoProfilesProfiles [ engine :: vulkan :: config :: videoProfileCount ];
    VkVideoProfilesKHR                                          videoProfiles;
#endif
};

struct CreateCommandPoolContext {
    CommonItems                                 common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkCommandPoolCreateInfo                     createInfo;
#endif
};

struct AllocateCommandBuffersContext {
    CommonItems                                 common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkCommandBufferAllocateInfo                 allocateInfo;
#endif
};

struct BeginCommandBufferContext {
    CommonItems                                             common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkCommandBufferBeginInfo                                beginInfo;
    VkCommandBufferInheritanceInfo                          inheritanceInfo;
#endif
#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    VkDeviceGroupCommandBufferBeginInfo                     deviceGroupBeginInfo;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    VkCommandBufferInheritanceRenderingInfo_t               inheritanceRenderingInfo;
    VkFormat                                                renderingInfoFormats [ engine :: vulkan :: config :: renderingInfoFormatsCount ];
#if __C_ENG_VULKAN_API_EXTENSION_AMD_MIXED_ATTACHMENT_SAMPLES_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAMEBUFFER_MIXED_SAMPLES_AVAILABLE
    VkAttachmentSampleCountInfoAMD                          attachmentSampleCountInfo;
    VkSampleCountFlagBits                                   sampleCountAttachmentSamples [ engine :: vulkan :: config :: sampleCountAttachmentSamplesCount ];
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
    VkViewport                                              viewportDepths [ engine :: vulkan :: config :: viewportDepthCount ];
#endif
};

struct SubmitQueueContext {
    CommonItems                                             common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkSubmitInfo                                            submitInfos [ engine :: vulkan :: config :: submitInfoCount ];
    VkPipelineStageFlags                                    stageFlags [ engine :: vulkan :: config :: submitInfoCount ] [ engine :: vulkan :: config :: pipelineStageFlagsCount ];
#endif
#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    VkDeviceGroupSubmitInfo                                 deviceGroupSubmitInfos [ engine :: vulkan :: config :: submitInfoCount ];
    VkProtectedSubmitInfo                                   protectedSubmitInfos [ engine :: vulkan :: config :: submitInfoCount ];
#endif
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    VkTimelineSemaphoreSubmitInfo                           timelineSemaphoreSubmitInfos [ engine :: vulkan :: config :: submitInfoCount ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
    VkPerformanceQuerySubmitInfoKHR                         performanceQuerySubmitInfos [ engine :: vulkan :: config :: submitInfoCount ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WIN32_KEYED_MUTEX_AVAILABLE
    Win32KeyedMutexAcquireReleaseInfoKHR                    win32KeyedMutexAcquireReleaseInfos [ engine :: vulkan :: config :: submitInfoCount ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_WIN32_KEYED_MUTEX_AVAILABLE
    Win32KeyedMutexAcquireReleaseInfoNV                     win32KeyedMutexAcquireReleaseInfosNVidia [ engine :: vulkan :: config :: submitInfoCount ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_WIN32_AVAILABLE
    D3D12FenceSubmitInfo                                    d3d12FenceSubmitInfos [ engine :: vulkan :: config :: submitInfoCount ];
#endif
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
    VkSubmitInfo2_t                                         submitInfos2 [ engine :: vulkan :: config :: submitInfoCount ];
    VkSemaphoreSubmitInfo_t                                 waitSemaphoreSubmitInfos [ engine :: vulkan :: config :: submitInfoCount ][ engine :: vulkan :: config :: submitSemaphoreInfoCount ];
    VkSemaphoreSubmitInfo_t                                 signalSemaphoreSubmitInfos [ engine :: vulkan :: config :: submitInfoCount ][ engine :: vulkan :: config :: submitSemaphoreInfoCount ];
    VkCommandBufferSubmitInfo_t                             commandBufferSubmitInfos [ engine :: vulkan :: config :: submitInfoCount ][ engine :: vulkan :: config :: submitCommandBufferInfoCount ];
#endif
};

struct CreateFenceContext {
    CommonItems                                             common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
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
    CommonItems                                             common;
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_WIN32_AVAILABLE
    VkFenceGetWin32HandleInfoKHR                            win32HandleInfo;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_FD_AVAILABLE
    VkFenceGetFdInfoKHR                                     fdInfo;
#endif
};

struct RegisterEventContext {
    CommonItems                                             common;
#if __C_ENG_VULKAN_API_EXTENSION_DISPLAY_CONTROL_AVAILABLE
    VkDeviceEventInfoEXT                                    deviceInfo;
    VkDisplayEventInfoEXT                                   displayInfo;
#endif
};

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_WIN32_AVAILABLE
struct ImportFenceWin32Context {
    CommonItems                                             common;
    VkImportFenceWin32HandleInfoKHR                         info;
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_FD_AVAILABLE
struct ImportFenceFdContext {
    CommonItems                                             common;
    VkImportFenceFdInfoKHR                                  info;
};
#endif

struct CreateSemaphoreContext {
    CommonItems                                             common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkSemaphoreCreateInfo                                   createInfo;
#endif
#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    VkExportSemaphoreCreateInfo                             exportCreateInfo;
#endif
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    VkSemaphoreTypeCreateInfo                               typeCreateInfo;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_WIN32_AVAILABLE
    VkExportSemaphoreWin32HandleInfoKHR                     exportWin32HandleInfo;
#endif
};

struct GetSemaphoreContext {
    CommonItems                                             common;
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_WIN32_AVAILABLE
    VkSemaphoreGetWin32HandleInfoKHR                        win32HandleInfo;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_FD_AVAILABLE
    VkSemaphoreGetFdInfoKHR                                 fdInfo;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_SEMAPHORE_AVAILABLE
    VkSemaphoreGetZirconHandleInfoFUCHSIA                   zirconHandleInfo;
#endif
};

struct WaitSemaphoreContext {
    CommonItems                                             common;
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    VkSemaphoreWaitInfo                                     info;
    uint64_t                                                values [ engine :: vulkan :: config :: waitSemaphoreCount ];
#endif
};

struct SignalSemaphoreContext {
    CommonItems                                             common;
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    VkSemaphoreSignalInfo                                   info;
#endif
};

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_WIN32_AVAILABLE
struct ImportSemaphoreWin32Context {
    CommonItems                                             common;
    VkImportSemaphoreWin32HandleInfoKHR                     info;
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_FD_AVAILABLE
struct ImportSemaphoreFdContext {
    CommonItems                                             common;
    VkImportSemaphoreFdInfoKHR                              info;
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_SEMAPHORE_AVAILABLE
struct ImportSemaphoreZirconHandleInfoGoogleContext {
    CommonItems                                             common;
    VkImportSemaphoreZirconHandleInfoGoogle                 info;
};
#endif

struct CreateEventContext {
    CommonItems                                             common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkEventCreateInfo                                       createInfo;
#endif
};

struct SetCommandBufferEventContext {
    CommonItems                                             common;
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
    VkDependencyInfo_t                                      dependencyInfo;
    VkMemoryBarrier2_t                                      memoryBarriers [ engine :: vulkan :: config :: dependencyInfoMemoryBarrierCount ];
    VkBufferMemoryBarrier2_t                                bufferMemoryBarriers [ engine :: vulkan :: config :: dependencyInfoBufferMemoryBarrierCount ];
    VkImageMemoryBarrier2_t                                 imageMemoryBarriers [ engine :: vulkan :: config :: dependencyInfoImageMemoryBarrierCount ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE
    VkSampleLocationsInfoEXT                                sampleLocationsInfos [ engine :: vulkan :: config :: dependencyInfoImageMemoryBarrierCount ];
    VkSampleLocationEXT                                     sampleLocations [ engine :: vulkan :: config :: dependencyInfoImageMemoryBarrierCount ] [ engine :: vulkan :: config :: sampleLocationsInfoSampleLocationsCount ];
#endif
};

struct WaitCommandBufferEvent2Context {
    CommonItems                                             common;
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
    VkDependencyInfo_t                                      dependencyInfos [ engine :: vulkan :: config :: commandBufferWaitEventsDependencyInfoCount ];
    VkMemoryBarrier2_t                                      memoryBarriers [ engine :: vulkan :: config :: commandBufferWaitEventsDependencyInfoCount ] [ engine :: vulkan :: config :: dependencyInfoMemoryBarrierCount ];
    VkBufferMemoryBarrier2_t                                bufferMemoryBarriers [ engine :: vulkan :: config :: commandBufferWaitEventsDependencyInfoCount ] [ engine :: vulkan :: config :: dependencyInfoBufferMemoryBarrierCount ];
    VkImageMemoryBarrier2_t                                 imageMemoryBarriers [ engine :: vulkan :: config :: commandBufferWaitEventsDependencyInfoCount ] [ engine :: vulkan :: config :: dependencyInfoImageMemoryBarrierCount ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE
    VkSampleLocationsInfoEXT                                sampleLocationsInfos [ engine :: vulkan :: config :: commandBufferWaitEventsDependencyInfoCount ] [ engine :: vulkan :: config :: dependencyInfoImageMemoryBarrierCount ];
    VkSampleLocationEXT                                     sampleLocations [ engine :: vulkan :: config :: commandBufferWaitEventsDependencyInfoCount ] [ engine :: vulkan :: config :: dependencyInfoImageMemoryBarrierCount ] [ engine :: vulkan :: config :: sampleLocationsInfoSampleLocationsCount ];
#endif
};

struct WaitCommandBufferEventContext {
    CommonItems                                             common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkMemoryBarrier                                         memoryBarriers [ engine :: vulkan :: config :: memoryBarrierCount ];
    VkBufferMemoryBarrier                                   bufferMemoryBarriers [ engine :: vulkan :: config :: bufferMemoryBarrierCount ];
    VkImageMemoryBarrier                                    imageMemoryBarriers [ engine :: vulkan :: config :: imageMemoryBarrierCount ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE
    VkSampleLocationsInfoEXT                                sampleLocationsInfos [ engine :: vulkan :: config :: imageMemoryBarrierCount ];
    VkSampleLocationEXT                                     sampleLocations [ engine :: vulkan :: config :: imageMemoryBarrierCount ] [ engine :: vulkan :: config :: sampleLocationsInfoSampleLocationsCount ];
#endif
};

struct BeginCommandBufferRenderingContext {
    CommonItems                                             common;
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE
    VkRenderingInfo_t                                       info;
    VkRenderingAttachmentInfo_t                             colorAttachments [ engine :: vulkan :: config :: renderingInfoColorAttachmentCount ];
    VkRenderingAttachmentInfo_t                             depthAttachment;
    VkRenderingAttachmentInfo_t                             stencilAttachment;
#endif
#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    VkDeviceGroupRenderPassBeginInfo                        deviceGroupRenderPassBeginInfo;
    VkRect2D                                                deviceRenderAreas [ engine :: vulkan :: config :: deviceGroupRenderPassBeginDeviceRenderAreaCount ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE && ( __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE )
    VkMultiviewPerViewAttributesInfoNVX                     multiviewPerViewAttributesInfo;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE && ( __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE )
    VkRenderingFragmentDensityMapAttachmentInfoEXT          densityMapAttachmentInfo;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE && ( __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE )
    VkRenderingFragmentShadingRateAttachmentInfoKHR         fragmentShadingRateAttachmentInfo;
#endif
};

struct CreateRenderPassContext {
    CommonItems                                             common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkRenderPassCreateInfo                                  createInfo;
    VkAttachmentDescription                                 attachmentDescriptions [ engine :: vulkan :: config :: renderPassAttachmentDescriptionCount ];
    VkSubpassDescription                                    subpassDescriptions [ engine :: vulkan :: config :: renderPassSubpassDescriptionCount ];
    VkAttachmentReference                                   inputAttachments [ engine :: vulkan :: config :: renderPassSubpassDescriptionCount ] [ engine :: vulkan :: config :: renderPassSubpassDescriptionInputAttachmentCount ];
    VkAttachmentReference                                   colorAttachments [ engine :: vulkan :: config :: renderPassSubpassDescriptionCount ] [ engine :: vulkan :: config :: renderPassSubpassDescriptionColorAttachmentCount ];
    VkAttachmentReference                                   resolveAttachments [ engine :: vulkan :: config :: renderPassSubpassDescriptionCount ] [ engine :: vulkan :: config :: renderPassSubpassDescriptionColorAttachmentCount ];
    VkAttachmentReference                                   depthStencilAttachments [ engine :: vulkan :: config :: renderPassSubpassDescriptionCount ];
    VkSubpassDependency                                     subpassDependencies [ engine :: vulkan :: config :: renderPassSubpassDependencyCount ];
#endif
#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    VkRenderPassInputAttachmentAspectCreateInfo             inputAttachmentAspectCreateInfo;
    VkInputAttachmentAspectReference                        inputAttachmentAspectReferences [ engine :: vulkan :: config :: renderPassInputAttachmentAspectReferenceCount ];
    VkRenderPassMultiviewCreateInfo                         multiviewCreateInfo;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE
    VkRenderPassFragmentDensityMapCreateInfoEXT             fragmentDensityMapCreateInfo;
#endif
};

struct CreateRenderPass2Context {
    CommonItems                                             common;
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    VkRenderPassCreateInfo2                                 createInfo;
    VkAttachmentDescription2                                attachmentDescriptions [ engine :: vulkan :: config :: renderPassAttachmentDescriptionCount ];
    VkAttachmentDescriptionStencilLayout                    attachmentDescriptionStencilLayouts [ engine :: vulkan :: config :: renderPassAttachmentDescriptionCount ];
    VkSubpassDescription2                                   subpassDescriptions [ engine :: vulkan :: config :: renderPassSubpassDescriptionCount ];
    VkAttachmentReference2                                  inputAttachments [ engine :: vulkan :: config :: renderPassSubpassDescriptionCount ] [ engine :: vulkan :: config :: renderPassSubpassDescriptionInputAttachmentCount ];
    VkAttachmentReferenceStencilLayout                      inputAttachmentsReferenceStencilLayouts [ engine :: vulkan :: config :: renderPassSubpassDescriptionCount ] [ engine :: vulkan :: config :: renderPassSubpassDescriptionInputAttachmentCount ];
    VkAttachmentReference2                                  colorAttachments [ engine :: vulkan :: config :: renderPassSubpassDescriptionCount ] [ engine :: vulkan :: config :: renderPassSubpassDescriptionColorAttachmentCount ];
    VkAttachmentReferenceStencilLayout                      colorAttachmentsReferenceStencilLayouts [ engine :: vulkan :: config :: renderPassSubpassDescriptionCount ] [ engine :: vulkan :: config :: renderPassSubpassDescriptionColorAttachmentCount ];
    VkAttachmentReference2                                  resolveAttachments [ engine :: vulkan :: config :: renderPassSubpassDescriptionCount ] [ engine :: vulkan :: config :: renderPassSubpassDescriptionColorAttachmentCount ];
    VkAttachmentReferenceStencilLayout                      resolveAttachmentsReferenceStencilLayouts [ engine :: vulkan :: config :: renderPassSubpassDescriptionCount ] [ engine :: vulkan :: config :: renderPassSubpassDescriptionColorAttachmentCount ];
    VkAttachmentReference2                                  depthStencilAttachments [ engine :: vulkan :: config :: renderPassSubpassDescriptionCount ];
    VkAttachmentReferenceStencilLayout                      depthStencilAttachmentsReferenceStencilLayouts [ engine :: vulkan :: config :: renderPassSubpassDescriptionCount ];
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE
    VkFragmentShadingRateAttachmentInfoKHR                  fragmentShadingRateAttachmentInfos [ engine :: vulkan :: config :: renderPassSubpassDescriptionCount ];
    VkAttachmentReference2                                  fragmentShadingRateAttachmentReferences [ engine :: vulkan :: config :: renderPassSubpassDescriptionCount ];
#endif
    VkSubpassDescriptionDepthStencilResolve                 subpassDescriptionDepthStencilResolve [ engine :: vulkan :: config :: renderPassSubpassDescriptionCount ];
    VkAttachmentReference2                                  subpassDescriptionDepthStencilReferences [ engine :: vulkan :: config :: renderPassSubpassDescriptionCount ];
    VkSubpassDependency2                                    subpassDependencies [ engine :: vulkan :: config :: renderPassSubpassDependencyCount ];
    VkMemoryBarrier2_t                                      memoryBarriers [ engine :: vulkan :: config :: renderPassSubpassDependencyCount ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE
    VkRenderPassFragmentDensityMapCreateInfoEXT             fragmentDensityMapCreateInfo;
#endif
};

struct CreateFrameBufferContext {
    CommonItems                                             common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkFramebufferCreateInfo                                 createInfo;
#endif
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    VkFramebufferAttachmentsCreateInfo                      attachmentsCreateInfo;
    VkFramebufferAttachmentImageInfo                        attachmentImageInfos [ engine :: vulkan :: config :: frameBufferAttachmentsImageInfoCount ];
#endif
};

struct BeginRenderPassContext {
    CommonItems                                             common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkRenderPassBeginInfo                                   beginInfo;
    VkClearValue                                            clearValues [ engine :: vulkan :: config :: renderPassBeginInfoClearValueCount ];
#endif
#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    VkDeviceGroupRenderPassBeginInfo                        deviceGroupRenderPassBeginInfo;
    VkRect2D                                                deviceGroupDeviceRenderAreas [ engine :: vulkan :: config :: deviceGroupRenderPassBeginDeviceRenderAreaCount ];
#endif
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    VkRenderPassAttachmentBeginInfo                         attachmentBeginInfo;
    VkSubpassBeginInfo                                      subpassBeginInfo;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE
    VkRenderPassSampleLocationsBeginInfoEXT                 sampleLocationsBeginInfo;
    VkAttachmentSampleLocationsEXT                          attachmentInitialSampleLocations [ engine :: vulkan :: config :: renderPassSampleLocationsAttachmentInitialCount ];
    VkSampleLocationEXT                                     attachmentInitialSampleLocationsLocations [ engine :: vulkan :: config :: renderPassSampleLocationsAttachmentInitialCount ] [ engine :: vulkan :: config :: sampleLocationsInfoSampleLocationsCount ];
    VkSubpassSampleLocationsEXT                             postSubpassSampleLocations [ engine :: vulkan :: config :: renderPassSampleLocationsPostSubpassCount ];
    VkSampleLocationEXT                                     postSubpassSampleLocationsLocations [ engine :: vulkan :: config :: renderPassSampleLocationsPostSubpassCount ] [ engine :: vulkan :: config :: sampleLocationsInfoSampleLocationsCount ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_RENDER_PASS_TRANSFORM_AVAILABLE
    VkRenderPassTransformBeginInfoQCOM                      transformBeginInfo;
#endif
};

struct NextSubpassContext {
    CommonItems                                             common;
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    VkSubpassBeginInfo                                      beginInfo;
    VkSubpassEndInfo                                        endInfo;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE
    VkSubpassFragmentDensityMapOffsetEndInfoQCOM            fragmentDensityMapOffsetEndInfo;
    VkOffset2D                                              fragmentDensityOffsets [ engine :: vulkan :: config :: subpassFragmentDensityMapOffsetEndInfoOffsetCount ];
#endif
};

struct CreateShaderModuleContext {
    CommonItems                                             common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkShaderModuleCreateInfo                                createInfo;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_CACHE_AVAILABLE
    VkShaderModuleValidationCacheCreateInfoEXT              validationCacheCreateInfo;
#endif
};

struct GetPhysicalDeviceCooperativeMatrixPropertiesContext {
    CommonItems                                             common;
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE
    VkCooperativeMatrixPropertiesNV                         properties [ engine :: vulkan :: config :: cooperativeMatrixPropertiesCount ];
#endif
};

struct CreateValidationCacheContext {
    CommonItems                                             common;
#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_CACHE_AVAILABLE
    VkValidationCacheCreateInfoEXT                          createInfo;
#endif
};

struct CreateComputePipelineContext {
    CommonItems                                             common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkComputePipelineCreateInfo                             createInfos [ engine :: vulkan :: config :: computePipelineCount ];
    VkSpecializationInfo                                    specializationInfos [ engine :: vulkan :: config :: computePipelineCount ];
    VkSpecializationMapEntry                                specializationMapEntries [ engine :: vulkan :: config :: computePipelineCount ] [ engine :: vulkan :: config :: computePipelineCount ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_AMD_PIPELINE_COMPILER_CONTROL_AVAILABLE
    VkPipelineCompilerControlCreateInfoAMD                  compilerControlCreateInfos [ engine :: vulkan :: config :: computePipelineCount ];
#endif
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_FEEDBACK_AVAILABLE
    VkPipelineCreationFeedbackCreateInfo_t                  feedbackCreateInfos [ engine :: vulkan :: config :: computePipelineCount ];
    VkPipelineCreationFeedback_t                            feedbacks [ engine :: vulkan :: config :: computePipelineCount ];
    VkPipelineCreationFeedback_t                            feedbackStageFeedbacks [ engine :: vulkan :: config :: computePipelineCount ] [ engine :: vulkan :: config :: computePipelineStageCreationFeedbackCount ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE
    VkSubpassShadingPipelineCreateInfoHUAWEI                subpassShadingCreateInfos [ engine :: vulkan :: config :: computePipelineCount ];
#endif
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE
    VkPipelineShaderStageRequiredSubgroupSizeCreateInfo_t   requiredSubgroupSizeCreateInfos [ engine :: vulkan :: config :: computePipelineCount ];
#endif
};

struct CreateGraphicsPipelineContext {
    CommonItems                                                 common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkGraphicsPipelineCreateInfo                                createInfos [ engine :: vulkan :: config :: graphicsPipelineCount ];
    VkPipelineShaderStageCreateInfo                             shaderStageCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ] [ engine :: vulkan :: config :: graphicsPipelineShaderStageCount ];
    VkSpecializationInfo                                        shaderStageSpecializationInfos [ engine :: vulkan :: config :: graphicsPipelineCount ] [ engine :: vulkan :: config :: graphicsPipelineShaderStageCount ];
    VkSpecializationMapEntry                                    shaderStageSpecializationMapEntries [ engine :: vulkan :: config :: graphicsPipelineCount ] [ engine :: vulkan :: config :: graphicsPipelineShaderStageCount ] [ engine :: vulkan :: config :: graphicsPipelineSpecializationMapEntryCount ];
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE
    VkPipelineShaderStageRequiredSubgroupSizeCreateInfo_t       requiredSubgroupSizeCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ] [ engine :: vulkan :: config :: graphicsPipelineShaderStageCount ];
#endif

    VkPipelineVertexInputStateCreateInfo                        vertexInputStateCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ];
    VkVertexInputBindingDescription                             vertexInputBindingDescriptions [ engine :: vulkan :: config :: graphicsPipelineCount ] [ engine :: vulkan :: config :: graphicsPipelineVertexInputBindingCount ];
    VkVertexInputAttributeDescription                           vertexInputAttributeDescriptions [ engine :: vulkan :: config :: graphicsPipelineCount ] [ engine :: vulkan :: config :: graphicsPipelineVertexInputAttributeCount ];
#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE
    VkPipelineVertexInputDivisorStateCreateInfoEXT              vertexInputDivisorStateCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ];
    VkVertexInputBindingDivisorDescriptionEXT                   vertexInputDivisorDescriptions [ engine :: vulkan :: config :: graphicsPipelineCount ] [ engine :: vulkan :: config :: graphicsPipelineVertexInputBindingDivisorCount ];
#endif

    VkPipelineInputAssemblyStateCreateInfo                      inputAssemblyStateCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ];

    VkPipelineTessellationStateCreateInfo                       tessellationStateCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ];
#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    VkPipelineTessellationDomainOriginStateCreateInfo           tessellationDomainOriginStateCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ];
#endif

    VkPipelineViewportStateCreateInfo                           viewportStateCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ];
    VkViewport                                                  viewportStateViewports [ engine :: vulkan :: config :: graphicsPipelineCount ] [ engine :: vulkan :: config :: graphicsPipelineViewportCount ];
    VkRect2D                                                    viewportStateScissors [ engine :: vulkan :: config :: graphicsPipelineCount ] [ engine :: vulkan :: config :: graphicsPipelineScissorCount ];
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE
    VkPipelineViewportCoarseSampleOrderStateCreateInfoNV        viewportCoarseSampleOrderStateCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ];
    VkCoarseSampleOrderCustomNV                                 viewportCoarseSampleCustomOrders [ engine :: vulkan :: config :: graphicsPipelineCount ] [ engine :: vulkan :: config :: graphicsPipelineViewportCustomSampleOrderCount ];
    VkCoarseSampleLocationNV                                    viewportCoarseSampleCustomLocations [ engine :: vulkan :: config :: graphicsPipelineCount ] [ engine :: vulkan :: config :: graphicsPipelineViewportCustomSampleOrderCount ] [ engine :: vulkan :: config :: graphicsPipelineViewportCustomSampleLocationCount ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_CONTROL_AVAILABLE
    VkPipelineViewportDepthClipControlCreateInfoEXT             viewportDepthClipControlCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SCISSOR_EXCLUSIVE_AVAILABLE
    VkPipelineViewportExclusiveScissorStateCreateInfoNV         viewportExclusiveScissorStateCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ];
    VkRect2D                                                    viewportExclusiveScissors [ engine :: vulkan :: config :: graphicsPipelineCount ] [ engine :: vulkan :: config :: graphicsPipelineScissorCount ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE
    VkPipelineViewportShadingRateImageStateCreateInfoNV         viewportShadingRateImageStateCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ];
    VkShadingRatePaletteNV                                      viewportShadingRatePalettes [ engine :: vulkan :: config :: graphicsPipelineCount ] [ engine :: vulkan :: config :: graphicsPipelineViewportCount ];
    VkShadingRatePaletteEntryNV                                 viewportShadingRatePaletteEntries [ engine :: vulkan :: config :: graphicsPipelineCount ] [ engine :: vulkan :: config :: graphicsPipelineViewportCount ] [ engine :: vulkan :: config :: graphicsPipelineViewportShadingRatePaletteEntryCount ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_VIEWPORT_SWIZZLE_AVAILABLE
    VkPipelineViewportSwizzleStateCreateInfoNV                  viewportSwizzleStateCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ];
    VkViewportSwizzleNV                                         viewportSwizzles [ engine :: vulkan :: config :: graphicsPipelineCount ] [ engine :: vulkan :: config :: graphicsPipelineViewportCount ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CLIP_SPACE_W_SCALING_AVAILABLE
    VkPipelineViewportWScalingStateCreateInfoNV                 viewportWScalingStateCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ];
    VkViewportWScalingNV                                        viewportWScalings [ engine :: vulkan :: config :: graphicsPipelineCount ] [ engine :: vulkan :: config :: graphicsPipelineViewportCount ];
#endif

    VkPipelineRasterizationStateCreateInfo                      rasterizationStateCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ];
#if __C_ENG_VULKAN_API_EXTENSION_CONSERVATIVE_RASTERIZATION_AVAILABLE
    VkPipelineRasterizationConservativeStateCreateInfoEXT       rasterizationConservativeStateCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_ENABLE_AVAILABLE
    VkPipelineRasterizationDepthClipStateCreateInfoEXT          rasterizationDepthClipStateCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE
    VkPipelineRasterizationLineStateCreateInfoEXT               rasterizationLineStateCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE
    VkPipelineRasterizationProvokingVertexStateCreateInfoEXT    rasterizationProvokingVertexStateCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_AMD_RASTERIZATION_ORDER_AVAILABLE
    VkPipelineRasterizationStateRasterizationOrderAMD           rasterizationStateRasterizationOrders [ engine :: vulkan :: config :: graphicsPipelineCount ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE
    VkPipelineRasterizationStateStreamCreateInfoEXT             rasterizationStateStreamCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ];
#endif

    VkPipelineMultisampleStateCreateInfo                        multisampleStateCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ];
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAMEBUFFER_MIXED_SAMPLES_AVAILABLE
    VkPipelineCoverageModulationStateCreateInfoNV               multisampleCoverageModulationCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COVERAGE_REDUCTION_MODE_AVAILABLE
    VkPipelineCoverageReductionStateCreateInfoNV                multisampleCoverageReductionCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_COVERAGE_TO_COLOR_AVAILABLE
    VkPipelineCoverageToColorStateCreateInfoNV                  multisampleCoverageToColorCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE
    VkPipelineSampleLocationsStateCreateInfoEXT                 multisampleSampleLocationsCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ];
    VkSampleLocationEXT                                         multisampleSampleLocations [ engine :: vulkan :: config :: graphicsPipelineCount ] [ engine :: vulkan :: config :: graphicsPipelineMultisampleSampleLocations ];
#endif

    VkPipelineDepthStencilStateCreateInfo                       depthStencilStateCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ];

    VkPipelineColorBlendStateCreateInfo                         colorBlendStateCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ];
    VkPipelineColorBlendAttachmentState                         colorBlendStateAttachments [ engine :: vulkan :: config :: graphicsPipelineCount ] [ engine :: vulkan :: config :: graphicsPipelineColorBlendAttachmentCount ];
#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE
    VkPipelineColorBlendAdvancedStateCreateInfoEXT              colorBlendAdvancedStateCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_COLOR_WRITE_ENABLE_AVAILABLE
    VkPipelineColorWriteCreateInfoEXT                           colorBlendColorWriteCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ];
#endif

    VkPipelineDynamicStateCreateInfo                            dynamicStateCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ];
    VkDynamicState                                              dynamicStateStates [ engine :: vulkan :: config :: graphicsPipelineCount ] [ engine :: vulkan :: config :: graphicsPipelineDynamicStateCount ];


#if ( __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE ) && ( __C_ENG_VULKAN_API_EXTENSION_AMD_MIXED_ATTACHMENT_SAMPLES_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAMEBUFFER_MIXED_SAMPLES_AVAILABLE )
    VkAttachmentSampleCountInfoAMD                              attachmentSampleCountInfos [ engine :: vulkan :: config :: graphicsPipelineCount ];
    VkSampleCountFlagBits                                       attachmentSamples [ engine :: vulkan :: config :: graphicsPipelineCount ][ engine :: vulkan :: config :: sampleCountAttachmentSamplesCount ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE
    VkGraphicsPipelineShaderGroupsCreateInfoNV                  pipelineShaderGroupsCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ];
    VkGraphicsShaderGroupCreateInfoNV                           graphicsShaderGroupCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ] [ engine :: vulkan :: config :: graphicsPipelineShaderGroupCount ];

    VkPipelineShaderStageCreateInfo                             shaderGroupStageCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ] [ engine :: vulkan :: config :: graphicsPipelineShaderGroupCount ] [ engine :: vulkan :: config :: graphicsPipelineShaderStageCount ];
    VkSpecializationInfo                                        shaderGroupShaderStageSpecializationInfos [ engine :: vulkan :: config :: graphicsPipelineCount ] [ engine :: vulkan :: config :: graphicsPipelineShaderGroupCount ] [ engine :: vulkan :: config :: graphicsPipelineShaderStageCount ];
    VkSpecializationMapEntry                                    shaderGroupShaderStageSpecializationMapEntries [ engine :: vulkan :: config :: graphicsPipelineCount ] [ engine :: vulkan :: config :: graphicsPipelineShaderGroupCount ] [ engine :: vulkan :: config :: graphicsPipelineShaderStageCount ] [ engine :: vulkan :: config :: graphicsPipelineSpecializationMapEntryCount ];
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE
    VkPipelineShaderStageRequiredSubgroupSizeCreateInfo_t       shaderGroupRequiredSubgroupSizeCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ] [ engine :: vulkan :: config :: graphicsPipelineShaderGroupCount ] [ engine :: vulkan :: config :: graphicsPipelineShaderStageCount ];
#endif

    VkPipelineVertexInputStateCreateInfo                        shaderGroupVertexInputStateCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ] [ engine :: vulkan :: config :: graphicsPipelineShaderGroupCount ];
    VkVertexInputBindingDescription                             shaderGroupVertexInputBindingDescriptions [ engine :: vulkan :: config :: graphicsPipelineCount ] [ engine :: vulkan :: config :: graphicsPipelineShaderGroupCount ] [ engine :: vulkan :: config :: graphicsPipelineVertexInputBindingCount ];
    VkVertexInputAttributeDescription                           shaderGroupVertexInputAttributeDescriptions [ engine :: vulkan :: config :: graphicsPipelineCount ] [ engine :: vulkan :: config :: graphicsPipelineShaderGroupCount ] [ engine :: vulkan :: config :: graphicsPipelineVertexInputAttributeCount ];
#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE
    VkPipelineVertexInputDivisorStateCreateInfoEXT              shaderGroupVertexInputDivisorStateCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ] [ engine :: vulkan :: config :: graphicsPipelineShaderGroupCount ];
    VkVertexInputBindingDivisorDescriptionEXT                   shaderGroupVertexInputDivisorDescriptions [ engine :: vulkan :: config :: graphicsPipelineCount ] [ engine :: vulkan :: config :: graphicsPipelineShaderGroupCount ] [ engine :: vulkan :: config :: graphicsPipelineVertexInputBindingDivisorCount ];
#endif

    VkPipelineTessellationStateCreateInfo                       shaderGroupTessellationStateCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ] [ engine :: vulkan :: config :: graphicsPipelineShaderGroupCount ];
#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    VkPipelineTessellationDomainOriginStateCreateInfo           shaderGroupTessellationDomainOriginStateCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ] [ engine :: vulkan :: config :: graphicsPipelineShaderGroupCount ];
#endif
#endif
#if ( __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE ||__C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE ) && __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE
    VkMultiviewPerViewAttributesInfoNVX                         multiviewPerViewAttributesInfos [ engine :: vulkan :: config :: graphicsPipelineCount ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_AMD_PIPELINE_COMPILER_CONTROL_AVAILABLE
    VkPipelineCompilerControlCreateInfoAMD                      pipelineCompilerControlCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ];
#endif
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_FEEDBACK_AVAILABLE
    VkPipelineCreationFeedbackCreateInfo_t                      pipelineCreationFeedbackCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ];
    VkPipelineCreationFeedback_t                                pipelineCreationFeedbacks [ engine :: vulkan :: config :: graphicsPipelineCount ];
    VkPipelineCreationFeedback_t                                pipelineCreationStageFeedbacks [ engine :: vulkan :: config :: graphicsPipelineCount ] [ engine :: vulkan :: config :: graphicsPipelineStageCreationFeedbackCount ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_DISCARD_RECTANGLES_AVAILABLE
    VkPipelineDiscardRectangleStateCreateInfoEXT                discardRectangleStateCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ];
    VkRect2D                                                    discardRectanglesRectangles [ engine :: vulkan :: config :: graphicsPipelineCount ] [ engine :: vulkan :: config :: graphicsPipelineDiscardRectanglesCount ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE
    VkPipelineFragmentShadingRateEnumStateCreateInfoNV          fragmentShadingRateEnumStateCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE
    VkPipelineFragmentShadingRateStateCreateInfoKHR             fragmentShadingRateStateCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ];
#endif
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE
    VkPipelineRenderingCreateInfo_t                             dynamicRenderingCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ];
    VkFormat                                                    dynamicRenderingColorAttachmentFormats [ engine :: vulkan :: config :: graphicsPipelineCount ] [ engine :: vulkan :: config :: graphicsPipelineDynamicRenderingColorAttachmentCount ];
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_REPRESENTATIVE_FRAGMENT_TEST_AVAILABLE
    VkPipelineRepresentativeFragmentTestStateCreateInfoNV       representativeFragmentTestStateCreateInfos [ engine :: vulkan :: config :: graphicsPipelineCount ];
#endif

#endif
};

struct CreateRayTracingPipelineNVidiaContext {
    CommonItems                                                 common;
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
    VkRayTracingPipelineCreateInfoNV                            createInfos [ engine :: vulkan :: config :: rayTracingPipelineCount ];
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkPipelineShaderStageCreateInfo                             shaderStageCreateInfos [ engine :: vulkan :: config :: rayTracingPipelineCount ] [ engine :: vulkan :: config :: rayTracingPipelineShaderStageCount ];
    VkSpecializationInfo                                        shaderStageSpecializationInfos [ engine :: vulkan :: config :: rayTracingPipelineCount ] [ engine :: vulkan :: config :: rayTracingPipelineShaderStageCount ];
    VkSpecializationMapEntry                                    shaderStageSpecializationMapEntries [ engine :: vulkan :: config :: rayTracingPipelineCount ] [ engine :: vulkan :: config :: rayTracingPipelineShaderStageCount ] [ engine :: vulkan :: config :: rayTracingPipelineSpecializationMapEntryCount ];
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE
    VkPipelineShaderStageRequiredSubgroupSizeCreateInfo_t       requiredSubgroupSizeCreateInfos [ engine :: vulkan :: config :: rayTracingPipelineCount ] [ engine :: vulkan :: config :: rayTracingPipelineShaderStageCount ];
#endif
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
    VkRayTracingShaderGroupCreateInfoNV                         shaderGroupCreateInfos [ engine :: vulkan :: config :: rayTracingPipelineCount ] [ engine :: vulkan :: config :: rayTracingPipelineShaderGroupCount ];
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_FEEDBACK_AVAILABLE
    VkPipelineCreationFeedbackCreateInfo_t                      pipelineCreationFeedbackCreateInfos [ engine :: vulkan :: config :: rayTracingPipelineCount ];
    VkPipelineCreationFeedback_t                                pipelineCreationFeedbacks [ engine :: vulkan :: config :: rayTracingPipelineCount ];
    VkPipelineCreationFeedback_t                                pipelineCreationStageFeedbacks [ engine :: vulkan :: config :: rayTracingPipelineCount ] [ engine :: vulkan :: config :: rayTracingPipelineStageCreationFeedbackCount ];
#endif
};

struct CreateRayTracingPipelineContext {
    CommonItems                                                 common;
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
    VkRayTracingPipelineCreateInfoKHR                           createInfos [ engine :: vulkan :: config :: rayTracingPipelineCount ];
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkPipelineShaderStageCreateInfo                             shaderStageCreateInfos [ engine :: vulkan :: config :: rayTracingPipelineCount ] [ engine :: vulkan :: config :: rayTracingPipelineShaderStageCount ];
    VkSpecializationInfo                                        shaderStageSpecializationInfos [ engine :: vulkan :: config :: rayTracingPipelineCount ] [ engine :: vulkan :: config :: rayTracingPipelineShaderStageCount ];
    VkSpecializationMapEntry                                    shaderStageSpecializationMapEntries [ engine :: vulkan :: config :: rayTracingPipelineCount ] [ engine :: vulkan :: config :: rayTracingPipelineShaderStageCount ] [ engine :: vulkan :: config :: rayTracingPipelineSpecializationMapEntryCount ];
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE
    VkPipelineShaderStageRequiredSubgroupSizeCreateInfo_t       requiredSubgroupSizeCreateInfos [ engine :: vulkan :: config :: rayTracingPipelineCount ] [ engine :: vulkan :: config :: rayTracingPipelineShaderStageCount ];
#endif
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
    VkRayTracingShaderGroupCreateInfoKHR                        shaderGroupCreateInfos [ engine :: vulkan :: config :: rayTracingPipelineCount ] [ engine :: vulkan :: config :: rayTracingPipelineShaderGroupCount ];
    VkPipelineLibraryCreateInfoKHR                              libraryCreateInfos [ engine :: vulkan :: config :: rayTracingPipelineCount ];
    VkRayTracingPipelineInterfaceCreateInfoKHR                  interfaceCreateInfos [ engine :: vulkan :: config :: rayTracingPipelineCount ];
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkPipelineDynamicStateCreateInfo                            dynamicStateCreateInfos [ engine :: vulkan :: config :: rayTracingPipelineCount ];
    VkDynamicState                                              dynamicStateStates [ engine :: vulkan :: config :: rayTracingPipelineCount ] [ engine :: vulkan :: config :: rayTracingPipelineDynamicStateCount ];
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_FEEDBACK_AVAILABLE
    VkPipelineCreationFeedbackCreateInfo_t                      pipelineCreationFeedbackCreateInfos [ engine :: vulkan :: config :: rayTracingPipelineCount ];
    VkPipelineCreationFeedback_t                                pipelineCreationFeedbacks [ engine :: vulkan :: config :: rayTracingPipelineCount ];
    VkPipelineCreationFeedback_t                                pipelineCreationStageFeedbacks [ engine :: vulkan :: config :: rayTracingPipelineCount ] [ engine :: vulkan :: config :: rayTracingPipelineStageCreationFeedbackCount ];
#endif
};

struct CreatePipelineCacheContext {
    CommonItems                                                 common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkPipelineCacheCreateInfo                                   createInfo;
#endif
};

struct GetPipelineCommonContext {
    CommonItems                                                 common;
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
    VkPipelineInfoKHR                                           info;
#endif
};

struct GetPipelinePropertiesContext {
    CommonItems                                                 common;
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
    VkPipelineInfoKHR                                           info;
    VkPipelineExecutablePropertiesKHR                           properties [ engine :: vulkan :: config :: pipelineExecutablePropertiesCount ];
#endif
};

struct GetPipelineStatisticsContext {
    CommonItems                                                 common;
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
    VkPipelineExecutableInfoKHR                                 info;
    VkPipelineExecutableStatisticKHR                            statistics [ engine :: vulkan :: config :: pipelineExecutableStatisticsCount ];
#endif
};

struct GetPipelineInternalRepresentationsContext {
    CommonItems                                                 common;
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
    VkPipelineExecutableInfoKHR                                 info;
    VkPipelineExecutableInternalRepresentationKHR               internalRepresentations [ engine :: vulkan :: config :: pipelineExecutableInternalRepresentationCount ];
#endif
};

struct GetPhysicalDeviceMemoryPropertiesContext {
    CommonItems                                                 common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkPhysicalDeviceMemoryProperties                            properties;
#endif
#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    VkPhysicalDeviceMemoryProperties2                           properties2;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_BUDGET_AVAILABLE
    VkPhysicalDeviceMemoryBudgetPropertiesEXT                   budgetProperties;
#endif
};

struct AllocateMemoryContext {
    CommonItems                                                 common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkMemoryAllocateInfo                                        info;
#endif
#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    VkMemoryAllocateFlagsInfo                                   flagsInfo;
    VkMemoryDedicatedAllocateInfo                               dedicatedInfo;
    VkExportMemoryAllocateInfo                                  exportInfo;
#endif
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    VkMemoryOpaqueCaptureAddressAllocateInfo                    opaqueCaptureAddressInfo;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_PRIORITY_AVAILABLE
    VkMemoryPriorityAllocateInfoEXT                             priorityInfo;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_AVAILABLE
    VkExportMemoryAllocateInfoNV                                exportInfoNVidia;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_WIN32_AVAILABLE
    VkExportMemoryWin32HandleInfoKHR                            exportInfoWin32;
    VkImportMemoryWin32HandleInfoKHR                            importInfoWin32;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_WIN32_AVAILABLE
    VkExportMemoryWin32HandleInfoNV                             exportInfoWin32NVidia;
    VkImportMemoryWin32HandleInfoNV                             importInfoWin32NVidia;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_FD_AVAILABLE
    VkImportMemoryFdInfoKHR                                     importInfoFd;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_EXTERNAL_MEMORY_HOST_AVAILABLE
    VkImportMemoryHostPointerInfoEXT                            importHostInfo;
#endif
#if __C_ENG_VULKAN_API_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_AVAILABLE
    VkImportAndroidHardwareBufferInfoANDROID                    importHardwareBufferAndroid;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_BUFFER_COLLECTION_AVAILABLE
    VkImportMemoryBufferCollectionFUCHSIA                       importBufferCollectionFuchsia;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_MEMORY_AVAILABLE
    VkImportMemoryZirconHandleInfoFUCHSIA                       importInfoFuchsia;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_AVAILABLE
    VkDedicatedAllocationMemoryAllocateInfoNV                   dedicatedInfoNVidia;
#endif
};

struct GetMemoryWin32Context {
    CommonItems                                                 common;
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_WIN32_AVAILABLE
    VkMemoryGetWin32HandleInfoKHR                               info;
    VkMemoryWin32HandlePropertiesKHR                            properties;
#endif
};

struct GetMemoryFdContext {
    CommonItems                                                 common;
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_FD_AVAILABLE
    VkMemoryGetFdInfoKHR                                        info;
    VkMemoryFdPropertiesKHR                                     properties;
#endif
};

struct GetMemoryPlatformIndependentContext {
    CommonItems                                                 common;
#if __C_ENG_VULKAN_API_EXTENSION_EXTERNAL_MEMORY_HOST_AVAILABLE
    VkMemoryHostPointerPropertiesEXT                            properties;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_RDMA_AVAILABLE
    VkMemoryGetRemoteAddressInfoNV                              remoteAddress;
#endif
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    VkDeviceMemoryOpaqueCaptureAddressInfo                      opaqueInfo;
#endif
};

struct FlushMappedMemoryRangesContext {
    CommonItems                                                 common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkMappedMemoryRange                                         ranges [ engine :: vulkan :: config :: flushMappedRangeCount ];
#endif
};

struct CreateBufferContext {
    CommonItems                                                 common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkBufferCreateInfo                                          createInfo;
#endif
#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    VkExternalMemoryBufferCreateInfo                            externalMemoryCreateInfo;
#endif
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    VkBufferOpaqueCaptureAddressCreateInfo                      opaqueCaptureAddressCreateInfo;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_BUFFER_COLLECTION_AVAILABLE
    VkBufferCollectionBufferCreateInfoFUCHSIA                   bufferCollectionCreateInfo;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_BUFFER_DEVICE_ADDRESS_AVAILABLE
    VkBufferDeviceAddressCreateInfoEXT                          deviceAddressCreateInfo;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_AVAILABLE
    VkDedicatedAllocationBufferCreateInfoNV                     dedicatedAllocationCreateInfo;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_DECODE_H264_AVAILABLE
    VkVideoDecodeH264ProfileEXT                                 decodeH264Profile;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_DECODE_H265_AVAILABLE
    VkVideoDecodeH265ProfileEXT                                 decodeH265Profile;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_ENCODE_H264_AVAILABLE
    VkVideoEncodeH264ProfileEXT                                 encodeH264Profile;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_ENCODE_H265_AVAILABLE
    VkVideoEncodeH265ProfileEXT                                 encodeH265Profile;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE
    VkVideoProfileKHR                                           videoProfile;
    VkVideoProfileKHR                                           videoProfilesProfiles [ engine :: vulkan :: config :: videoProfileCount ];
    VkVideoProfilesKHR                                          videoProfiles;
#endif
};

struct CreateBufferViewContext {
    CommonItems                                                 common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkBufferViewCreateInfo                                      createInfo;
#endif
};

struct CreateImageContext {
    CommonItems                                                 common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkImageCreateInfo                                           createInfo;
#endif
#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    VkExternalMemoryImageCreateInfo                             externalMemoryCreateInfo;
#endif
#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE
    VkImageSwapchainCreateInfoKHR                               swapchainCreateInfo;
#endif
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    VkImageFormatListCreateInfo                                 formatListCreateInfo;
    VkFormat                                                    formatListFormats [ engine :: vulkan :: config :: imageFormatListFormatCount ];
    VkImageStencilUsageCreateInfo                               stencilUsageCreateInfo;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_AVAILABLE
    VkExternalMemoryImageCreateInfoNV                           externalMemoryCreateInfoNVidia;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_BUFFER_COLLECTION_AVAILABLE
    VkBufferCollectionImageCreateInfoFUCHSIA                    bufferCollectionImageCreateInfo;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_AVAILABLE
    VkDedicatedAllocationImageCreateInfoNV                      dedicatedAllocationImageCreateInfo;
#endif
#if __C_ENG_VULKAN_API_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_AVAILABLE
    VkExternalFormatANDROID                                     externalFormat;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_DRM_FORMAT_MODIFIER_AVAILABLE
    VkImageDrmFormatModifierExplicitCreateInfoEXT               drmFormatModifierExplicitCreateInfo;
    VkSubresourceLayout                                         drmFormatSubresourceLayouts [ engine :: vulkan :: config :: imageDrmFormatSubresourceLayoutCount ];
    VkImageDrmFormatModifierListCreateInfoEXT                   drmFormatModifierListCreateInfo;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_DECODE_H264_AVAILABLE
    VkVideoDecodeH264ProfileEXT                                 decodeH264Profile;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_DECODE_H265_AVAILABLE
    VkVideoDecodeH265ProfileEXT                                 decodeH265Profile;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_ENCODE_H264_AVAILABLE
    VkVideoEncodeH264ProfileEXT                                 encodeH264Profile;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_ENCODE_H265_AVAILABLE
    VkVideoEncodeH265ProfileEXT                                 encodeH265Profile;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE
    VkVideoProfileKHR                                           videoProfile;
    VkVideoProfileKHR                                           videoProfilesProfiles [ engine :: vulkan :: config :: videoProfileCount ];
    VkVideoProfilesKHR                                          videoProfiles;
#endif
};

struct GetImageSubresourceLayoutContext {
    CommonItems                                                 common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkImageSubresource                                          subresource;
    VkSubresourceLayout                                         layout;
#endif
};

struct GetImageDrmFormatModifierPropertiesContext {
    CommonItems                                                 common;
#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_DRM_FORMAT_MODIFIER_AVAILABLE
    VkImageDrmFormatModifierPropertiesEXT                       properties;
#endif
};

struct CreateAccelerationStructureKhronosContext {
    CommonItems                                                 common;
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
    VkAccelerationStructureCreateInfoKHR                        createInfo;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE
    VkAccelerationStructureMotionInfoNV                         motionInfo;
#endif
};

struct CreateAccelerationStructureNVidiaContext {
    CommonItems                                                 common;
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
    VkAccelerationStructureCreateInfoNV                         createInfo;
    VkGeometryNV                                                geometries [ engine :: vulkan :: config :: accelerationStructureNVidiaGeometryCount ];
#endif
};

struct GetAccelerationStructureBuildSizesContext {
    CommonItems                                                 common;
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
    VkAccelerationStructureBuildGeometryInfoKHR                 geometryInfo;
    VkAccelerationStructureBuildSizesInfoKHR                    sizesInfo;
    VkAccelerationStructureGeometryKHR                          geometries [ engine :: vulkan :: config :: accelerationStructureGeometryCount ];
    VkAccelerationStructureGeometryKHR const *                  geometryPointers [ engine :: vulkan :: config :: accelerationStructureGeometryCount ];
    VkAccelerationStructureGeometryKHR                       *  pDynamicGeometries;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE
    VkAccelerationStructureGeometryMotionTrianglesDataNV        trianglesData [ engine :: vulkan :: config :: accelerationStructureGeometryCount ];
#endif
};

struct GetAccelerationStructureMemoryRequirementsContext {
    CommonItems                                                 common;
#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    VkMemoryRequirements2                                       requirements2;
    VkMemoryDedicatedRequirements                               dedicatedRequirements;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
    VkAccelerationStructureMemoryRequirementsInfoNV             requirements;
#endif
};

struct BindAccelerationStructureMemoryContext {
    CommonItems                                                 common;
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
    VkBindAccelerationStructureMemoryInfoNV                     infos [ engine :: vulkan :: config :: bindAccelerationStructureCount ];
#endif
};

struct GetAccelerationStructureDeviceAddressContext {
    CommonItems                                                 common;
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
    VkAccelerationStructureDeviceAddressInfoKHR                 info;
#endif
};

struct CreateSamplerContext {
    CommonItems                                                 common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkSamplerCreateInfo                                         createInfo;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_BORDER_COLOR_SWIZZLE_AVAILABLE
    VkSamplerBorderColorComponentMappingCreateInfoEXT           borderColorComponentMappingCreateInfo;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE
    VkSamplerCustomBorderColorCreateInfoEXT                     customBorderColorCreateInfo;
#endif
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    VkSamplerReductionModeCreateInfo                            reductionModeCreateInfo;
#endif
#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    VkSamplerYcbcrConversionInfo                                ycbcrConversionInfo;
    VkSamplerYcbcrConversionCreateInfo                          ycbcrConversionCreateInfo;
#endif
#if __C_ENG_VULKAN_API_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_AVAILABLE
    VkExernalFormatANDROID                                      externalFormat;
#endif
};

struct CreateDescriptorSetLayoutContext {
    CommonItems                                                 common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkDescriptorSetLayoutCreateInfo                             createInfo;
    VkDescriptorSetLayoutBinding                                bindings [ engine :: vulkan :: config :: descriptorSetLayoutBindingCount ];
#endif
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    VkDescriptorSetLayoutBindingFlagsCreateInfo                 bindingFlagsCreateInfo;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE
    VkMutableDescriptorTypeCreateInfoVALVE                      mutableDescriptorTypeCreateInfo;
    VkMutableDescriptorTypeListVALVE                            mutableDescriptorTypeLists [ engine :: vulkan :: config :: descriptorSetMutableDescriptorTypeListCount ];
    VkDescriptorType                                            mutableDescriptorListEntries [ engine :: vulkan :: config :: descriptorSetMutableDescriptorTypeListCount ] [ engine :: vulkan :: config :: descriptorSetMutableDescriptorListItemCount ];
#endif
};

struct GetDescriptorSetLayoutSupportContext {
    CommonItems                                                 common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkDescriptorSetLayoutCreateInfo                             createInfo;
    VkDescriptorSetLayoutBinding                                bindings [ engine :: vulkan :: config :: descriptorSetLayoutBindingCount ];
#endif
#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    VkDescriptorSetLayoutSupport                                support;
#endif
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    VkDescriptorSetLayoutBindingFlagsCreateInfo                 bindingFlagsCreateInfo;
    VkDescriptorSetVariableDescriptorCountLayoutSupport         variableDescriptorCountSupport;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE
    VkMutableDescriptorTypeCreateInfoVALVE                      mutableDescriptorTypeCreateInfo;
    VkMutableDescriptorTypeListVALVE                            mutableDescriptorTypeLists [ engine :: vulkan :: config :: descriptorSetMutableDescriptorTypeListCount ];
    VkDescriptorType                                            mutableDescriptorListEntries [ engine :: vulkan :: config :: descriptorSetMutableDescriptorTypeListCount ] [ engine :: vulkan :: config :: descriptorSetMutableDescriptorListItemCount ];
#endif
};

struct CreatePipelineLayoutContext {
    CommonItems                                                 common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkPipelineLayoutCreateInfo                                  createInfo;
    VkPushConstantRange                                         pushConstantRanges [ engine :: vulkan :: config :: pipelineLayoutPushConstantRangeCount ];
#endif
};

struct CreateDescriptorPoolContext {
    CommonItems                                                 common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkDescriptorPoolCreateInfo                                  createInfo;
    VkDescriptorPoolSize                                        poolSizes [ engine :: vulkan :: config :: descriptorPoolSizeCount ];
#endif
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE
    VkDescriptorPoolInlineUniformBlockCreateInfo_t              inlineUniformBlockCreateInfo;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE
    VkMutableDescriptorTypeCreateInfoVALVE                      mutableDescriptorTypeCreateInfo;
    VkMutableDescriptorTypeListVALVE                            mutableDescriptorTypeLists [ engine :: vulkan :: config :: descriptorSetMutableDescriptorTypeListCount ];
    VkDescriptorType                                            mutableDescriptorListEntries [ engine :: vulkan :: config :: descriptorSetMutableDescriptorTypeListCount ] [ engine :: vulkan :: config :: descriptorSetMutableDescriptorListItemCount ];
#endif
};

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
struct DescriptorSetAllocateInfoSubcontext {
    VkDescriptorSetAllocateInfo info;
};
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
struct DescriptorSetVariableDescriptorCountAllocateInfoSubcontext {
    VkDescriptorSetVariableDescriptorCountAllocateInfo info;
};
#endif

struct AllocateDescriptorSetsContext {
    CommonItems                                                     common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    DescriptorSetAllocateInfoSubcontext                             allocateInfo;
#endif
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    DescriptorSetVariableDescriptorCountAllocateInfoSubcontext      variableDescriptorCount;
#endif
};

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
struct WriteDescriptorSetAccelerationStructureSubcontext {
    VkWriteDescriptorSetAccelerationStructureKHR                    accelerationStructure;
};
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
struct WriteDescriptorSetAccelerationStructureSubcontextNVidia {
    VkWriteDescriptorSetAccelerationStructureNV                     accelerationStructure;
};
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE
struct WriteDescriptorSetInlineUniformBlockSubcontext {
    VkWriteDescriptorSetInlineUniformBlock_t                        inlineUniformBlock;
};
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
struct WriteDescriptorSetSubcontext {
    VkWriteDescriptorSet                                          * pWrite;
    VkDescriptorImageInfo                                           imageInfo;
    VkDescriptorBufferInfo                                          bufferInfo;
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
    WriteDescriptorSetAccelerationStructureSubcontext               writeAccelerationStructure;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
    WriteDescriptorSetAccelerationStructureSubcontextNVidia         writeAccelerationStructureNVidia;
#endif
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE
    WriteDescriptorSetInlineUniformBlockSubcontext                  writeInlineUniformBlock;
#endif
};
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
struct CopyDescriptorSetSubcontext {
    VkCopyDescriptorSet                                           * pCopy;
};
#endif

struct UpdateDescriptorSetsContext {
    CommonItems                                                     common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkWriteDescriptorSet                                            writeInfos [ engine :: vulkan :: config :: updateWriteDescriptorCount ];
    VkCopyDescriptorSet                                             copyInfos [ engine :: vulkan :: config :: updateCopyDescriptorCount ];
    WriteDescriptorSetSubcontext                                    writeSubcontexts [ engine :: vulkan :: config :: updateWriteDescriptorCount ];
    CopyDescriptorSetSubcontext                                     copySubcontexts [ engine :: vulkan :: config :: updateCopyDescriptorCount ];
#endif
};

struct CreateDescriptorUpdateTemplateContext {
    CommonItems                                                     common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkDescriptorUpdateTemplateCreateInfo                            createInfo;
    VkDescriptorUpdateTemplateEntry                                 entries [ engine :: vulkan :: config :: descriptorUpdateTemplateEntryCount ];
#endif
};

struct GetDeviceBufferAddressContext {
    CommonItems                                                     common;
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    VkBufferDeviceAddressInfo                                       info;
#endif
};

struct CreateQueryPoolContext {
    CommonItems                                                     common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkQueryPoolCreateInfo                                           createInfo;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
    VkQueryPoolPerformanceCreateInfoKHR                             performanceQueryCreateInfo;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
    VkQueryPoolPerformanceQueryCreateInfoINTEL                      performanceQueryCreateInfoIntel;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_DECODE_H264_AVAILABLE
    VkVideoDecodeH264ProfileEXT                                     decodeH264Profile;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_DECODE_H265_AVAILABLE
    VkVideoDecodeH265ProfileEXT                                     decodeH265Profile;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_ENCODE_H264_AVAILABLE
    VkVideoEncodeH264ProfileEXT                                     encodeH264Profile;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_ENCODE_H265_AVAILABLE
    VkVideoEncodeH265ProfileEXT                                     encodeH265Profile;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE
    VkVideoProfileKHR                                               videoProfile;
#endif
};

struct ClearColorImageContext {
    CommonItems                                                     common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkClearColorValue                                               color;
    VkImageSubresourceRange                                         ranges [ engine :: vulkan :: config :: clearImageSubresourceRangeCount ];
#endif
};

struct ClearDepthStencilImageContext {
    CommonItems                                                     common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkClearDepthStencilValue                                        depthStencil;
    VkImageSubresourceRange                                         ranges [ engine :: vulkan :: config :: clearImageSubresourceRangeCount ];
#endif
};

struct ClearAttachmentsContext {
    CommonItems                                                     common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkClearAttachment                                               attachments [ engine :: vulkan :: config :: clearAttachmentCount ];
    VkClearRect                                                     rects [ engine :: vulkan :: config :: clearRectCount ];
#endif
};

struct CopyBufferContext {
    CommonItems                                                     common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkBufferCopy                                                    copies [ engine :: vulkan :: config :: bufferCopyCount ];
#endif
};

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
struct CopyBufferInfo2Subcontext {
    VkCopyBufferInfo2_t                                             info;
    VkBufferCopy2_t                                                 copies [ engine :: vulkan :: config :: bufferCopyCount ];
};
#endif

struct CopyBuffer2Context {
    CommonItems                                                     common;
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
    CopyBufferInfo2Subcontext                                       info;
#endif
};

struct CopyImageContext {
    CommonItems                                                     common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkImageCopy                                                     copies [ engine :: vulkan :: config :: imageCopyCount ];
#endif
};

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
struct CopyImageInfo2Subcontext {
    VkCopyImageInfo2_t                                              info;
    VkImageCopy2_t                                                  copies [ engine :: vulkan :: config :: imageCopyCount ];
};
#endif

struct CopyImage2Context {
    CommonItems                                                     common;
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
    CopyImageInfo2Subcontext                                        info;
#endif
};

struct BlitImageContext {
    CommonItems                                                     common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkImageBlit                                                     blits [ engine :: vulkan :: config :: imageBlitCount ];
#endif
};

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
struct BlitImageInfo2Subcontext {
    VkBlitImageInfo2_t                                              info;
    VkImageBlit2_t                                                  blits [ engine :: vulkan :: config :: imageBlitCount ];
#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_ROTATED_COPY_COMMANDS_AVAILABLE
    VkCopyCommandTransformInfoQCOM                                  copyCommandTransforms [ engine :: vulkan :: config :: imageBlitCount ];
#endif
};
#endif

struct BlitImage2Context {
    CommonItems                                                     common;
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
    BlitImageInfo2Subcontext                                        info;
#endif
};

struct CopyBufferToImageOrImageToBufferContext {
    CommonItems                                                     common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkBufferImageCopy                                               copies [ engine :: vulkan :: config :: bufferImageCopyCount ];
#endif
};

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
struct CopyBufferToImageOrImageToBuffer2Subcontext {
    VkCopyBufferToImageInfo2_t                                      bufferToImage;
    VkCopyImageToBufferInfo2_t                                      imageToBuffer;
    VkBufferImageCopy2_t                                            copies [ engine :: vulkan :: config :: imageCopyCount ];
#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_ROTATED_COPY_COMMANDS_AVAILABLE
    VkCopyCommandTransformInfoQCOM                                  copyCommandsTransforms [ engine :: vulkan :: config :: imageCopyCount ];
#endif
};
#endif

struct CopyBufferToImageOrImageToBuffer2Context {
    CommonItems                                                     common;
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
    CopyBufferToImageOrImageToBuffer2Subcontext                     info;
#endif
};

struct ResolveImageContext {
    CommonItems                                                     common;
#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    VkImageResolve                                                  resolves [ engine :: vulkan :: config :: imageResolveCount ];
#endif
};

union GetMemorySharedContext {
    GetMemoryWin32Context                   win32;
    GetMemoryFdContext                      fd;
    GetMemoryPlatformIndependentContext     platformIndependent;
};

union CreateRayTracingPipelineSharedContext {
    CreateRayTracingPipelineNVidiaContext   nVidiaPipeline;
    CreateRayTracingPipelineContext         pipeline;
};

union CreatePipelineSharedContext {
    CreateComputePipelineContext                                        compute;
    CreateGraphicsPipelineContext                                       graphics;
    CreateRayTracingPipelineSharedContext                               rayTracing;
    CreatePipelineCacheContext                                          cache;
    CreatePipelineLayoutContext                                         layout;
};

union EnumerateSharedContext {
    EnumerateLayerPropertiesContext                                     layerProperties;
    EnumerateExtensionPropertiesContext                                 extensionProperties;
    EnumeratePhysicalDevicesContext                                     physicalDevices;
    EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersContext   physicalDeviceQueueFamilyPerformanceQueryCounters;
    EnumeratePhysicalDeviceGroupsContext                                physicalDeviceGroups;
};

union CreateBufferSharedContext {
    CreateBufferContext                                                 buffer;
    CreateBufferViewContext                                             view;
    CreateFrameBufferContext                                            frame;
};

union CreateImageSharedContext {
    CreateImageContext                                                  image;
    CreateImageViewContext                                              view;
};

union CreateAccelerationStructureSharedContext {
    CreateAccelerationStructureKhronosContext                           khronos;
    CreateAccelerationStructureNVidiaContext                            nvidia;
};

union CreateDescriptorSetSharedContext {
    CreateDescriptorSetLayoutContext                                    layout;
};

union CreateDescriptorUpdateSharedContext {
    CreateDescriptorUpdateTemplateContext                               _template;
};

union CreateDescriptorSharedContext {
    CreateDescriptorSetSharedContext                                    set;
    CreateDescriptorPoolContext                                         pool;
    CreateDescriptorUpdateSharedContext                                 update;
};

union CreateSharedContext {
    CreateInstanceContext                                               instance;
    CreateDeviceContext                                                 device;
    CreateSwapChainContext                                              swapChain;
    CreateCommandPoolContext                                            commandPool;
    CreateFenceContext                                                  fence;
    CreateSemaphoreContext                                              semaphore;
    CreateEventContext                                                  event;
    CreateRenderPassContext                                             renderPass;
    CreateRenderPass2Context                                            renderPass2;
    CreateShaderModuleContext                                           shaderModule;
    CreateValidationCacheContext                                        validationCache;
    CreatePipelineSharedContext                                         pipeline;
    CreateBufferSharedContext                                           buffer;
    CreateImageSharedContext                                            image;
    CreateAccelerationStructureSharedContext                            accelerationStructure;
    CreateSamplerContext                                                sampler;
    CreateDescriptorSharedContext                                       descriptor;
    CreateQueryPoolContext                                              queryPool;
};

union GetPipelineSharedContext {
    GetPipelineCommonContext                                            common;
    GetPipelinePropertiesContext                                        properties;
    GetPipelineStatisticsContext                                        statistics;
    GetPipelineInternalRepresentationsContext                           internalRepresentations;
};

union GetPhysicalDeviceSharedContext {
    GetPhysicalDevicePropertiesContext                                  properties;
    GetPhysicalDeviceFeaturesContext                                    features;
    GetPhysicalDeviceQueueFamilyPropertiesContext                       queueFamilyProperties;
    GetPhysicalDeviceCooperativeMatrixPropertiesContext                 cooperativeMatrixProperties;
    GetPhysicalDeviceMemoryPropertiesContext                            memory;
};

union GetImageSharedContext {
    GetImageSubresourceLayoutContext                                    subresourceLayout;
    GetImageDrmFormatModifierPropertiesContext                          drmFormatModifier;
};

union GetAccelerationStructureSharedContext {
    GetAccelerationStructureBuildSizesContext                           buildSizes;
    GetAccelerationStructureMemoryRequirementsContext                   memoryRequirements;
    GetAccelerationStructureDeviceAddressContext                        deviceAddress;
};

union GetDescriptorSetLayoutSharedContext {
    GetDescriptorSetLayoutSupportContext                                support;
};

union GetDescriptorSetSharedContext {
    GetDescriptorSetLayoutSharedContext                                 layout;
};

union GetDescriptorSharedContext {
    GetDescriptorSetSharedContext                                       set;
};

union GetDeviceBufferSharedContext {
    GetDeviceBufferAddressContext                                       address;
};

union GetDeviceSharedContext {
    GetDeviceQueueContext                                               queue;
    GetDeviceBufferSharedContext                                        buffer;
};

union GetSharedContext {
    GetPhysicalDeviceSharedContext                                      physicalDevice;
    GetDeviceSharedContext                                              device;
    GetSurfaceContext                                                   surface;
    GetSwapChainContext                                                 swapChain;
    GetFenceContext                                                     fence;
    GetSemaphoreContext                                                 semaphore;
    GetPipelineSharedContext                                            pipeline;
    GetMemorySharedContext                                              memory;
    GetImageSharedContext                                               image;
    GetAccelerationStructureSharedContext                               accelerationStructure;
    GetDescriptorSharedContext                                          descriptor;
};

union AllocateSharedContext {
    AllocateCommandBuffersContext                                       commandBuffers;
    AllocateMemoryContext                                               memory;
    AllocateDescriptorSetsContext                                       descriptorSets;
};

union BeginSharedContext {
    BeginCommandBufferContext                                           commandBuffer;
    BeginCommandBufferRenderingContext                                  commandBufferRendering;
    BeginRenderPassContext                                              renderPass;
};

union SubmitSharedContext {
    SubmitQueueContext                                                  queue;
};

union OthersSharedContext {
    RegisterEventContext                                                registerEvent;
    NextSubpassContext                                                  nextSubpass;
    FlushMappedMemoryRangesContext                                      flushMappedMemoryRanges;
};

union ImportFenceSharedContext {
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_WIN32_AVAILABLE
    ImportFenceWin32Context                                             win32;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_FD_AVAILABLE
    ImportFenceFdContext                                                fd;
#endif
};

union ImportSemaphoreSharedContext {
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_WIN32_AVAILABLE
    ImportSemaphoreWin32Context                                             win32;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_FD_AVAILABLE
    ImportSemaphoreFdContext                                                fd;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_SEMAPHORE_AVAILABLE
    ImportSemaphoreZirconHandleInfoGoogleContext                            zircon;
#endif
};

union WaitCommandBufferSharedContext {
    WaitCommandBufferEventContext                                       event;
    WaitCommandBufferEvent2Context                                      event2;
};

union ImportSharedContext {
    ImportFenceSharedContext                                            fence;
    ImportSemaphoreSharedContext                                        semaphore;
};

union WaitSharedContext {
    WaitSemaphoreContext                                                semaphore;
    WaitCommandBufferSharedContext                                      commandBuffer;
};

union SignalSharedContext {
    SignalSemaphoreContext                                              semaphore;
};

union SetCommandBufferSharedContext {
    SetCommandBufferEventContext                                        event;
};

union SetSharedContext {
    SetCommandBufferSharedContext                                       commandBuffer;
};

union BindSharedContext {
    BindAccelerationStructureMemoryContext                              accelerationStructureMemory;
};

union UpdateDescriptorSharedContext {
    UpdateDescriptorSetsContext                                         sets;
};

union UpdateSharedContext {
    UpdateDescriptorSharedContext                                       descriptor;
};

union ClearColorSharedContext {
    ClearColorImageContext                                              image;
};

union ClearDepthStencilSharedContext {
    ClearDepthStencilImageContext                                       image;
};

union ClearSharedContext {
    ClearColorSharedContext                                             color;
    ClearDepthStencilSharedContext                                      depthStencil;
    ClearAttachmentsContext                                             attachments;
};

union CopySharedContext {
    CopyBufferContext                                                   buffer;
    CopyBuffer2Context                                                  buffer2;
    CopyImageContext                                                    image;
    CopyImage2Context                                                   image2;
    CopyBufferToImageOrImageToBufferContext                             bufferToImageOrImageToBuffer;
    CopyBufferToImageOrImageToBuffer2Context                            bufferToImageOrImageToBuffer2;
    BlitImageContext                                                    blitImage;
    BlitImage2Context                                                   blitImage2;
    ResolveImageContext                                                 resolveImage;
};

union SharedContext {
    CommonContext                                                       common;
    CreateSharedContext                                                 create;
    EnumerateSharedContext                                              enumerate;
    GetSharedContext                                                    get;
    SetSharedContext                                                    set;
    AllocateSharedContext                                               allocate;
    BeginSharedContext                                                  begin;
    SubmitSharedContext                                                 submit;
    OthersSharedContext                                                 other;
    ImportSharedContext                                                 _import;
    WaitSharedContext                                                   wait;
    SignalSharedContext                                                 signal;
    BindSharedContext                                                   bind;
    UpdateSharedContext                                                 update;
    ClearSharedContext                                                  clear;
    CopySharedContext                                                   copy;
};

constexpr auto toString ( ContextType type ) noexcept -> cds :: StringLiteral {
    switch ( type ) {
        case ContextType :: None:   return "None";
        case ContextType :: Shared: return "Shared";
    }

    return "Unknown";
}

constexpr auto toString ( SharedContextType type ) noexcept -> cds :: StringLiteral {
    switch ( type ) {
        case SharedContextType :: Unknown:                                                    return "Unknown";
        case SharedContextType :: Common:                                                     return "Common";
        case SharedContextType :: CreateInstance:                                             return "CreateInstance";
        case SharedContextType :: EnumerateLayerProperties:                                   return "EnumerateLayerProperties";
        case SharedContextType :: EnumerateExtensionProperties:                               return "EnumerateExtensionProperties";
        case SharedContextType :: EnumeratePhysicalDevices:                                   return "EnumeratePhysicalDevices";
        case SharedContextType :: EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCounters: return "EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCounters";
        case SharedContextType :: EnumeratePhysicalDeviceGroups:                              return "EnumeratePhysicalDeviceGroups";
        case SharedContextType :: CreateDevice:                                               return "CreateDevice";
        case SharedContextType :: GetPhysicalDeviceProperties:                                return "GetPhysicalDeviceProperties";
        case SharedContextType :: GetPhysicalDeviceFeatures:                                  return "GetPhysicalDeviceFeatures";
        case SharedContextType :: GetPhysicalDeviceQueueFamilyProperties:                     return "GetPhysicalDeviceQueueFamilyProperties";
        case SharedContextType :: GetDeviceQueue:                                             return "GetDeviceQueue";
        case SharedContextType :: GetSurface:                                                 return "GetSurface";
        case SharedContextType :: CreateSwapChain:                                            return "CreateSwapChain";
        case SharedContextType :: GetSwapChain:                                               return "GetSwapChain";
        case SharedContextType :: CreateImageView:                                            return "CreateImageView";
        case SharedContextType :: CreateCommandPool:                                          return "CreateCommandPool";
        case SharedContextType :: AllocateCommandBuffers:                                     return "AllocateCommandBuffers";
        case SharedContextType :: BeginCommandBuffer:                                         return "BeginCommandBuffer";
        case SharedContextType :: SubmitQueue:                                                return "SubmitQueue";
        case SharedContextType :: CreateFence:                                                return "CreateFence";
        case SharedContextType :: GetFence:                                                   return "GetFence";
        case SharedContextType :: RegisterEvent:                                              return "RegisterEvent";
        case SharedContextType :: ImportFenceWin32:                                           return "ImportFenceWin32";
        case SharedContextType :: ImportFenceFd:                                              return "ImportFenceFd";
        case SharedContextType :: CreateSemaphore:                                            return "CreateSemaphore";
        case SharedContextType :: GetSemaphore:                                               return "GetSemaphore";
        case SharedContextType :: WaitSemaphore:                                              return "WaitSemaphore";
        case SharedContextType :: SignalSemaphore:                                            return "SignalSemaphore";
        case SharedContextType :: ImportSemaphoreWin32:                                       return "ImportSemaphoreWin32";
        case SharedContextType :: ImportSemaphoreFd:                                          return "ImportSemaphoreFd";
        case SharedContextType :: ImportSemaphoreZirconHandleInfoGoogle:                      return "ImportSemaphoreZirconHandleInfoGoogle";
        case SharedContextType :: CreateEvent:                                                return "CreateEvent";
        case SharedContextType :: SetCommandBufferEvent:                                      return "SetCommandBufferEvent";
        case SharedContextType :: WaitCommandBufferEvent2:                                    return "WaitCommandBufferEvent2";
        case SharedContextType :: WaitCommandBufferEvent:                                     return "WaitCommandBufferEvent";
        case SharedContextType :: BeginCommandBufferRendering:                                return "BeginCommandBufferRendering";
        case SharedContextType :: CreateRenderPass:                                           return "CreateRenderPass";
        case SharedContextType :: CreateRenderPass2:                                          return "CreateRenderPass2";
        case SharedContextType :: CreateFrameBuffer:                                          return "CreateFrameBuffer";
        case SharedContextType :: BeginRenderPass:                                            return "BeginRenderPass";
        case SharedContextType :: NextSubpass:                                                return "NextSubpass";
        case SharedContextType :: CreateShaderModule:                                         return "CreateShaderModule";
        case SharedContextType :: GetPhysicalDeviceCooperativeMatrixProperties:               return "GetPhysicalDeviceCooperativeMatrixProperties";
        case SharedContextType :: CreateValidationCache:                                      return "CreateValidationCache";
        case SharedContextType :: CreateComputePipeline:                                      return "CreateComputePipeline";
        case SharedContextType :: CreateGraphicsPipeline:                                     return "CreateGraphicsPipeline";
        case SharedContextType :: CreateRayTracingPipelineNVidia:                             return "CreateRayTracingPipelineNVidia";
        case SharedContextType :: CreateRayTracingPipeline:                                   return "CreateRayTracingPipeline";
        case SharedContextType :: CreatePipelineCache:                                        return "CreatePipelineCache";
        case SharedContextType :: GetPipelineCommon:                                          return "GetPipelineCommon";
        case SharedContextType :: GetPipelineProperties:                                      return "GetPipelineProperties";
        case SharedContextType :: GetPipelineStatistics:                                      return "GetPipelineStatistics";
        case SharedContextType :: GetPipelineInternalRepresentations:                         return "GetPipelineInternalRepresentations";
        case SharedContextType :: GetPhysicalDeviceMemoryProperties:                          return "GetPhysicalDeviceMemoryProperties";
        case SharedContextType :: AllocateMemory:                                             return "AllocateMemory";
        case SharedContextType :: GetMemoryWin32:                                             return "GetMemoryWin32";
        case SharedContextType :: GetMemoryFd:                                                return "GetMemoryFd";
        case SharedContextType :: GetMemoryPlatformIndependent:                               return "GetMemoryPlatformIndependent";
        case SharedContextType :: FlushMappedMemoryRanges:                                    return "FlushMappedMemoryRanges";
        case SharedContextType :: CreateBuffer:                                               return "CreateBuffer";
        case SharedContextType :: CreateBufferView:                                           return "CreateBufferView";
        case SharedContextType :: CreateImage:                                                return "CreateImage";
        case SharedContextType :: GetImageSubresourceLayout:                                  return "GetImageSubresourceLayout";
        case SharedContextType :: GetImageDrmFormatModifierProperties:                        return "GetImageDrmFormatModifierProperties";
        case SharedContextType :: CreateAccelerationStructureKhronos:                         return "CreateAccelerationStructureKhronos";
        case SharedContextType :: CreateAccelerationStructureNVidia:                          return "CreateAccelerationStructureNVidia";
        case SharedContextType :: GetAccelerationStructureBuildSizes:                         return "GetAccelerationStructureBuildSizes";
        case SharedContextType :: GetAccelerationStructureMemoryRequirements:                 return "GetAccelerationStructureMemoryRequirements";
        case SharedContextType :: BindAccelerationStructureMemory:                            return "BindAccelerationStructureMemory";
        case SharedContextType :: GetAccelerationStructureDeviceAddress:                      return "GetAccelerationStructureDeviceAddress";
        case SharedContextType :: CreateSampler:                                              return "CreateSampler";
        case SharedContextType :: CreateDescriptorSetLayout:                                  return "CreateDescriptorSetLayout";
        case SharedContextType :: GetDescriptorSetLayoutSupport:                              return "GetDescriptorSetLayoutSupport";
        case SharedContextType :: CreatePipelineLayout:                                       return "CreatePipelineLayout";
        case SharedContextType :: CreateDescriptorPool:                                       return "CreateDescriptorPool";
        case SharedContextType :: AllocateDescriptorSets:                                     return "AllocateDescriptorSets";
        case SharedContextType :: UpdateDescriptorSets:                                       return "UpdateDescriptorSets";
        case SharedContextType :: CreateDescriptorUpdateTemplate:                             return "CreateDescriptorUpdateTemplate";
        case SharedContextType :: GetDeviceBufferAddress:                                     return "GetDeviceBufferAddress";
        case SharedContextType :: CreateQueryPool:                                            return "CreateQueryPool";
        case SharedContextType :: ClearColorImage:                                            return "ClearColorImage";
        case SharedContextType :: ClearDepthStencilImage:                                     return "ClearDepthStencilImage";
        case SharedContextType :: ClearAttachments:                                           return "ClearAttachments";
        case SharedContextType :: CopyBuffer:                                                 return "CopyBuffer";
        case SharedContextType :: CopyBuffer2:                                                return "CopyBuffer2";
        case SharedContextType :: CopyImage:                                                  return "CopyImage";
        case SharedContextType :: CopyImage2:                                                 return "CopyImage2";
        case SharedContextType :: CopyBufferToImageOrImageToBuffer:                           return "CopyBufferToImageOrImageToBuffer";
        case SharedContextType :: CopyBufferToImageOrImageToBuffer2:                          return "CopyBufferToImageOrImageToBuffer2";
        case SharedContextType :: BlitImage:                                                  return "BlitImage";
        case SharedContextType :: BlitImage2:                                                 return "BlitImage2";
        case SharedContextType :: ResolveImage:                                               return "ResolveImage";
    }
}


#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif //C_ENG_VULKANAPICALLSTYPES_HPP

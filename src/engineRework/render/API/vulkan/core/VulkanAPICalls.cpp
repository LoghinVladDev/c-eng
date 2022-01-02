//
// Created by loghin on 01.01.2022.
//

#include <VulkanCore.hpp>
#include <VulkanAPICalls.hpp>
#include <VulkanCoreConfig.hpp>


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

static VkValidationFeatureEnableEXT         validationFeatureEnables    [ __C_ENG_VULKAN_CORE_VALIDATION_FEATURE_ENABLE_MAX_COUNT ];
static VkValidationFeatureDisableEXT        validationFeatureDisables   [ __C_ENG_VULKAN_CORE_VALIDATION_FEATURE_DISABLE_MAX_COUNT ];

static VkLayerProperties                    layerProperties             [ __C_ENG_VULKAN_CORE_LAYER_MAX_COUNT ];
static VkExtensionProperties                extensionProperties         [ __C_ENG_VULKAN_CORE_LAYER_EXTENSION_MAX_COUNT ];

static VkPhysicalDevice                     physicalDevices             [ __C_ENG_VULKAN_CORE_PHYSICAL_DEVICE_MAX_COUNT ];


/**
 * ----------------------------------------------
 * ----------------------------------------------
 * -------- Vulkan 1.1 Device Properties --------
 * ----------------------------------------------
 * ----------------------------------------------
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
#endif

/**
 * ----------------------------------------------
 * ----------------------------------------------
 * -------- Vulkan 1.2 Device Properties --------
 * ----------------------------------------------
 * ----------------------------------------------
 */
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
static VkPhysicalDeviceVulkan12Properties                           deviceVulkan12Properties;
static VkPhysicalDeviceDepthStencilResolveProperties                deviceDepthStencilResolveProperties;
static VkPhysicalDeviceDescriptorIndexingProperties                 deviceDescriptorIndexingProperties;
static VkPhysicalDeviceDriverProperties                             deviceDriverProperties;
static VkPhysicalDeviceFloatControlsProperties                      deviceFloatControlsProperties;
static VkPhysicalDeviceSamplerFilterMinmaxProperties                deviceSamplerFilterMinmaxProperties;
static VkPhysicalDeviceTimelineSemaphoreProperties                  deviceTimelineSemaphoreProperties;
#endif


/**
 * ----------------------------------------------
 * ----------------------------------------------
 * ---- Vulkan Extensions Device Properties -----
 * ----------------------------------------------
 * ----------------------------------------------
 */
#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE
static VkPhysicalDeviceBlendOperationAdvancedPropertiesEXT          deviceBlendOperationAdvancedProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONSERVATIVE_RASTERIZATION_AVAILABLE
static VkPhysicalDeviceConservativeRasterizationPropertiesEXT       deviceConservativeRasterizationProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE
static VkPhysicalDeviceCustomBorderColorPropertiesEXT               deviceCustomBorderColorProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISCARD_RECTANGLES_AVAILABLE
static VkPhysicalDeviceDiscardRectanglePropertiesEXT                deviceDiscardRectangleProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTERNAL_MEMORY_HOST_AVAILABLE
static VkPhysicalDeviceExternalMemoryHostPropertiesEXT              deviceExternalMemoryHostProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE
static VkPhysicalDeviceFragmentDensityMapPropertiesEXT              deviceFragmentDensityMapProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE
static VkPhysicalDeviceFragmentDensityMap2PropertiesEXT             deviceFragmentDensityMap2Properties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE
static VkPhysicalDeviceInlineUniformBlockPropertiesEXT              deviceInlineUniformBlockProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE
static VkPhysicalDeviceLineRasterizationPropertiesEXT               deviceLineRasterizationProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE
static VkPhysicalDeviceMultiDrawPropertiesEXT                       deviceMultiDrawProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PCI_BUS_INFO_AVAILABLE
static VkPhysicalDevicePCIBusInfoPropertiesEXT                      devicePciBusInfoProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PHYSICAL_DEVICE_DRM_AVAILABLE
static VkPhysicalDeviceDrmPropertiesEXT                             deviceDrmProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE
static VkPhysicalDeviceProvokingVertexPropertiesEXT                 deviceProvokingVertexProperties;
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
 * -----------------------------------------------------
 * -----------------------------------------------------
 * ---- Vulkan Khronos Extensions Device Properties ----
 * -----------------------------------------------------
 * -----------------------------------------------------
 */
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
static VkPhysicalDeviceAccelerationStructurePropertiesKHR           deviceAccelerationStructureProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE
static VkPhysicalDeviceFragmentShadingRatePropertiesKHR             deviceFragmentShadingRateProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE
static VkPhysicalDeviceMaintenance4PropertiesKHR                    deviceMaintenance4Properties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
static VkPhysicalDevicePerformanceQueryPropertiesKHR                devicePerformanceQueryProperties;
#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE
static VkPhysicalDevicePortabilitySubsetPropertiesKHR               devicePortabilitySubsetProperties;
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
 * ----------------------------------------------------
 * ----------------------------------------------------
 * ---- Vulkan NVidia Extensions Device Properties ----
 * ----------------------------------------------------
 * ----------------------------------------------------
 */
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE
static VkPhysicalDeviceCooperativeMatrixPropertiesNV                deviceCooperativeMatrixProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE
static VkPhysicalDeviceDeviceGeneratedCommandsPropertiesNV          deviceDeviceGeneratedCommandsProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE
static VkPhysicalDeviceFragmentShadingRateEnumsPropertiesNV         deviceFragmentShadingRateEnumsProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE
static VkPhysicalDeviceMeshShaderPropertiesNV                       deviceMeshShaderProperties;
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
 * -------------------------------------------------
 * -------------------------------------------------
 * ---- Vulkan AMD Extensions Device Properties ----
 * -------------------------------------------------
 * -------------------------------------------------
 */
#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_AVAILABLE
static VkPhysicalDeviceShaderCorePropertiesAMD                      deviceShaderCoreProperties;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_2_AVAILABLE
static VkPhysicalDeviceShaderCoreProperties2AMD                     deviceShaderCoreProperties2;
#endif


/**
 * ------------------------------------------------------
 * ------------------------------------------------------
 * ---- Vulkan Qualcomm Extensions Device Properties ----
 * ------------------------------------------------------
 * ------------------------------------------------------
 */
#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE
static VkPhysicalDeviceFragmentDensityMapOffsetPropertiesQCOM       deviceFragmentDensityMapOffsetProperties;
#endif


/**
 * ----------------------------------------------------
 * ----------------------------------------------------
 * ---- Vulkan Huawei Extensions Device Properties ----
 * ----------------------------------------------------
 * ----------------------------------------------------
 */
#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE
static VkPhysicalDeviceSubpassShadingPropertiesHUAWEI               deviceSubpassShadingProperties;
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
            layerProperties // NOLINT(clion-misra-cpp2008-5-2-12)
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

auto vulkan :: enumerateDeviceLayerProperties (
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
            layerProperties // NOLINT(clion-misra-cpp2008-5-2-12)
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
            extensionProperties // NOLINT(clion-misra-cpp2008-5-2-12)
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

            toVulkanFormat ( currentStructure, & validationFeatures ); // NOLINT(clion-misra-cpp2008-5-2-12)
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

    PFN_vkCreateDebugUtilsMessengerEXT  function = nullptr;
    VkAllocationCallbacks             * pUsedAllocationCallbacks = nullptr;

    function = reinterpret_cast < PFN_vkCreateDebugUtilsMessengerEXT > (
            vkGetInstanceProcAddr ( instanceHandle, __C_ENG_VULKAN_CORE_FUNCTION_NAME_CREATE_DEBUG_MESSENGER )
    );

    if ( function == nullptr ) {
        return ResultErrorFunctionHandleNotFound;
    }

    if ( pAllocationCallbacks != nullptr ) {
        pUsedAllocationCallbacks = & allocationCallbacks;
        toVulkanFormat ( pAllocationCallbacks, pUsedAllocationCallbacks );
    }

    toVulkanFormat (
            pMessengerCreateInfo,
            & messengerCreateInfo
    );

    return static_cast < __C_ENG_TYPE ( Result ) > ( function (
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
            physicalDevices // NOLINT(clion-misra-cpp2008-5-2-12)
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

auto vulkan :: getPhysicalDeviceProperties (
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

static auto toVulkanFormat (
        vulkan :: __C_ENG_TYPE ( PhysicalDeviceExtendedProperties ) const * pExtendedProperties
) noexcept -> void {

    if ( pExtendedProperties == nullptr ) {
        return;
    }

    deviceExtendedProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;

    auto currentInChain     = reinterpret_cast < vulkan :: __C_ENG_TYPE ( GenericOutStructure ) const * > ( pExtendedProperties->pNext );
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
                                                                                                                        
            case engine :: vulkan :: StructureTypePhysicalDeviceFragmentShadingRateEnumsPropertiesNVidia:               { currentInVkChain->pNext = reinterpret_cast < VkBaseOutStructure * > ( & deviceFragmentShadingRateEnumsProperties );   break; }
                                                                                                                        
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
    if ( vulkan :: compare ( version, { .variant = 0u, .major = 1u, .minor = 1u, .patch = 0u } ) == CompareResultLess ) { // NOLINT(clion-misra-cpp2008-2-13-4)
        return ResultErrorIncompatibleVersion;
    }

    toVulkanFormat ( pProperties );

    vkGetPhysicalDeviceProperties2 (
        handle,
        & deviceExtendedProperties
    );

    return ResultSuccess;
}
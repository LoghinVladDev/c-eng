//
// Created by loghin on 23.02.2022.
//

#ifndef __C_ENG_VULKAN_API_CALLS_CONVERSION_HPP__
#define __C_ENG_VULKAN_API_CALLS_CONVERSION_HPP__

#include <VulkanAPICallsPrivate.hpp>
#include <VulkanAPICallsTypes.hpp>

#define C_ENG_MAP_START     HEADER
#include <ObjectMapping.hpp>


namespace engine :: vulkan {

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto toVulkanFormat (
            VkAllocationCallbacks               *,
            Type ( AllocationCallbacks )  const *
    ) noexcept -> VkAllocationCallbacks *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_REPORT_AVAILABLE
    extern auto toVulkanFormat (
            VkDebugReportCallbackCreateInfoEXT        *,
            Type ( DebugReportCreateInfo )      const *
    ) noexcept -> VkDebugReportCallbackCreateInfoEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_UTILS_AVAILABLE
    extern auto toVulkanFormat (
            VkDebugUtilsMessengerCreateInfoEXT         *,
            Type ( DebugMessengerCreateInfo )    const *
    ) noexcept -> VkDebugUtilsMessengerCreateInfoEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_FEATURES_AVAILABLE
    extern auto toVulkanFormat (
            VkValidationFeaturesEXT           *,
            Type ( ValidationFeatures ) const *
    ) noexcept -> VkValidationFeaturesEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_FLAGS_AVAILABLE
    extern auto toVulkanFormat (
            VkValidationFlagsEXT              *,
            Type ( ValidationFlags )    const *
    ) noexcept -> VkValidationFlagsEXT *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceProperties )         *,
            VkPhysicalDeviceProperties          const *
    ) noexcept -> Type ( PhysicalDeviceProperties ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceExtendedProperties )         *,
            VkPhysicalDeviceProperties2                 const *
    ) noexcept -> Type ( PhysicalDeviceExtendedProperties ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto toVulkanFormat (
            VkApplicationInfo                 *,
            Type ( ApplicationInfo )    const *
    ) noexcept -> VkApplicationInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto toVulkanFormat (
            VkInstanceCreateInfo              *,
            Type ( InstanceCreateInfo ) const *
    ) noexcept -> VkInstanceCreateInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto prepareContext (
            CreateInstanceContext             *,
            Type ( InstanceCreateInfo ) const *
    ) noexcept -> VkInstanceCreateInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto fromVulkanFormat (
            Type ( LayerProperties )      *,
            VkLayerProperties       const *
    ) noexcept -> Type ( LayerProperties ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto fromVulkanFormat (
            Type ( ExtensionProperties )      *,
            VkExtensionProperties       const *
    ) noexcept -> Type ( ExtensionProperties ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
    auto fromVulkanFormat (
            Type ( PerformanceCounter )         *,
            VkPerformanceCounterKHR       const *
    ) noexcept -> Type ( PerformanceCounter ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
    auto fromVulkanFormat (
            Type ( PerformanceCounterDescription )         *,
            VkPerformanceCounterDescriptionKHR       const *
    ) noexcept -> Type ( PerformanceCounterDescription ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceGroupProperties )        *,
            VkPhysicalDeviceGroupProperties         const *
    ) noexcept -> Type ( PhysicalDeviceGroupProperties ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEVICE_MEMORY_REPORT_AVAILABLE
    extern auto toVulkanFormat (
            VkDeviceDeviceMemoryReportCreateInfoEXT               *,
            Type ( DeviceDeviceMemoryReportCreateInfo )     const *
    ) noexcept -> VkDeviceDeviceMemoryReportCreateInfoEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTICS_CONFIG_AVAILABLE
    extern auto toVulkanFormat (
            VkDeviceDiagnosticsConfigCreateInfoNV                     *,
            Type ( DeviceDiagnosticsConfigCreateInfoNVidia )    const *
    ) noexcept -> VkDeviceDiagnosticsConfigCreateInfoNV *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DEVICE_GROUP_AVAILABLE
    extern auto toVulkanFormat (
            VkDeviceGroupDeviceCreateInfo_t               *,
            Type ( DeviceGroupDeviceCreateInfo )    const *
    ) noexcept -> VkDeviceGroupDeviceCreateInfo_t *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_MEMORY_OVERALLOCATION_BEHAVIOUR_AVAILABLE
    extern auto toVulkanFormat (
            VkDeviceMemoryOverallocationCreateInfoAMD                 *,
            Type ( DeviceMemoryOverallocationCreateInfoAMD )    const *
    ) noexcept -> VkDeviceMemoryOverallocationCreateInfoAMD *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    extern auto toVulkanFormat (
            VkDevicePrivateDataCreateInfo_t               *,
            Type ( DevicePrivateDataCreateInfo )    const *
    ) noexcept -> VkDevicePrivateDataCreateInfo_t *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceFeatures              *,
            Type ( PhysicalDeviceFeatures ) const *
    ) noexcept -> VkPhysicalDeviceFeatures *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceFeatures )       *,
            VkPhysicalDeviceFeatures        const *
    ) noexcept -> Type ( PhysicalDeviceFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceFeatures2                     *,
            Type ( PhysicalDeviceExtendedFeatures ) const *
    ) noexcept -> VkPhysicalDeviceFeatures2 *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceExtendedFeatures )       *,
            VkPhysicalDeviceFeatures2               const *
    ) noexcept -> Type ( PhysicalDeviceExtendedFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceVulkan11Properties ) *,
            VkPhysicalDeviceVulkan11Properties  const *
    ) noexcept -> Type ( PhysicalDeviceVulkan11Properties ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDevice16BitStorageFeatures ) *,
            VkPhysicalDevice16BitStorageFeatures  const *
    ) noexcept -> Type ( PhysicalDevice16BitStorageFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceMultiviewFeatures ) *,
            VkPhysicalDeviceMultiviewFeatures  const *
    ) noexcept -> Type ( PhysicalDeviceMultiviewFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceProtectedMemoryFeatures ) *,
            VkPhysicalDeviceProtectedMemoryFeatures  const *
    ) noexcept -> Type ( PhysicalDeviceProtectedMemoryFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceSamplerYCBCRConversionFeatures ) *,
            VkPhysicalDeviceSamplerYcbcrConversionFeatures  const *
    ) noexcept -> Type ( PhysicalDeviceSamplerYCBCRConversionFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceShaderDrawParametersFeatures ) *,
            VkPhysicalDeviceShaderDrawParametersFeatures  const *
    ) noexcept -> Type ( PhysicalDeviceShaderDrawParametersFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceVariablePointersFeatures ) *,
            VkPhysicalDeviceVariablePointersFeatures  const *
    ) noexcept -> Type ( PhysicalDeviceVariablePointersFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDevicePointClippingProperties ) *,
            VkPhysicalDevicePointClippingProperties  const *
    ) noexcept -> Type ( PhysicalDevicePointClippingProperties ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceSubgroupProperties ) *,
            VkPhysicalDeviceSubgroupProperties  const *
    ) noexcept -> Type ( PhysicalDeviceSubgroupProperties ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceProtectedMemoryProperties ) *,
            VkPhysicalDeviceProtectedMemoryProperties  const *
    ) noexcept -> Type ( PhysicalDeviceProtectedMemoryProperties ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceMaintenanceProperties )  *,
            VkPhysicalDeviceMaintenance3Properties  const *
    ) noexcept -> Type ( PhysicalDeviceMaintenanceProperties ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceMultiviewProperties ) *,
            VkPhysicalDeviceMultiviewProperties  const *
    ) noexcept -> Type ( PhysicalDeviceMultiviewProperties ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceIDProperties ) *,
            VkPhysicalDeviceIDProperties  const *
    ) noexcept -> Type ( PhysicalDeviceIDProperties ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceVulkan11Features ) *,
            VkPhysicalDeviceVulkan11Features  const *
    ) noexcept -> Type ( PhysicalDeviceVulkan11Features ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceVulkan11Features              *,
            Type ( PhysicalDeviceVulkan11Features ) const *
    ) noexcept -> VkPhysicalDeviceVulkan11Features *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceMultiviewFeatures              *,
            Type ( PhysicalDeviceMultiviewFeatures ) const *
    ) noexcept -> VkPhysicalDeviceMultiviewFeatures *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDevice16BitStorageFeatures              *,
            Type ( PhysicalDevice16BitStorageFeatures ) const *
    ) noexcept -> VkPhysicalDevice16BitStorageFeatures *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceProtectedMemoryFeatures              *,
            Type ( PhysicalDeviceProtectedMemoryFeatures ) const *
    ) noexcept -> VkPhysicalDeviceProtectedMemoryFeatures *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceSamplerYcbcrConversionFeatures              *,
            Type ( PhysicalDeviceSamplerYCBCRConversionFeatures ) const *
    ) noexcept -> VkPhysicalDeviceSamplerYcbcrConversionFeatures *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceVariablePointersFeatures              *,
            Type ( PhysicalDeviceVariablePointersFeatures ) const *
    ) noexcept -> VkPhysicalDeviceVariablePointersFeatures *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceShaderDrawParametersFeatures              *,
            Type ( PhysicalDeviceShaderDrawParametersFeatures ) const *
    ) noexcept -> VkPhysicalDeviceShaderDrawParametersFeatures *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( ConformanceVersion )       *,
            VkConformanceVersion        const *
    ) noexcept -> Type ( ConformanceVersion ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceVulkan12Properties )       *,
            VkPhysicalDeviceVulkan12Properties        const *
    ) noexcept -> Type ( PhysicalDeviceVulkan12Properties ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceDepthStencilResolveProperties )       *,
            VkPhysicalDeviceDepthStencilResolveProperties        const *
    ) noexcept -> Type ( PhysicalDeviceDepthStencilResolveProperties ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceDescriptorIndexingProperties )       *,
            VkPhysicalDeviceDescriptorIndexingProperties        const *
    ) noexcept -> Type ( PhysicalDeviceDescriptorIndexingProperties ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceDriverProperties )       *,
            VkPhysicalDeviceDriverProperties        const *
    ) noexcept -> Type ( PhysicalDeviceDriverProperties ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceFloatControlsProperties )       *,
            VkPhysicalDeviceFloatControlsProperties        const *
    ) noexcept -> Type ( PhysicalDeviceFloatControlsProperties ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceSamplerFilterMinmaxProperties )       *,
            VkPhysicalDeviceSamplerFilterMinmaxProperties        const *
    ) noexcept -> Type ( PhysicalDeviceSamplerFilterMinmaxProperties ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceTimelineSemaphoreProperties )       *,
            VkPhysicalDeviceTimelineSemaphoreProperties        const *
    ) noexcept -> Type ( PhysicalDeviceTimelineSemaphoreProperties ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDevice8BitStorageFeatures )       *,
            VkPhysicalDevice8BitStorageFeatures        const *
    ) noexcept -> Type ( PhysicalDevice8BitStorageFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceBufferDeviceAddressFeatures )       *,
            VkPhysicalDeviceBufferDeviceAddressFeatures        const *
    ) noexcept -> Type ( PhysicalDeviceBufferDeviceAddressFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceDescriptorIndexingFeatures )       *,
            VkPhysicalDeviceDescriptorIndexingFeatures        const *
    ) noexcept -> Type ( PhysicalDeviceDescriptorIndexingFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceImagelessFrameBufferFeatures )       *,
            VkPhysicalDeviceImagelessFramebufferFeatures        const *
    ) noexcept -> Type ( PhysicalDeviceImagelessFrameBufferFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceScalarBlockLayoutFeatures )       *,
            VkPhysicalDeviceScalarBlockLayoutFeatures        const *
    ) noexcept -> Type ( PhysicalDeviceScalarBlockLayoutFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceShaderAtomicInt64Features )       *,
            VkPhysicalDeviceShaderAtomicInt64Features        const *
    ) noexcept -> Type ( PhysicalDeviceShaderAtomicInt64Features ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceShaderFloat16Int8Features )       *,
            VkPhysicalDeviceShaderFloat16Int8Features        const *
    ) noexcept -> Type ( PhysicalDeviceShaderFloat16Int8Features ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceShaderSubgroupExtendedTypesFeatures )       *,
            VkPhysicalDeviceShaderSubgroupExtendedTypesFeatures        const *
    ) noexcept -> Type ( PhysicalDeviceShaderSubgroupExtendedTypesFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceUniformBufferStandardLayoutFeatures )       *,
            VkPhysicalDeviceUniformBufferStandardLayoutFeatures        const *
    ) noexcept -> Type ( PhysicalDeviceUniformBufferStandardLayoutFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceVulkanMemoryModelFeatures )       *,
            VkPhysicalDeviceVulkanMemoryModelFeatures        const *
    ) noexcept -> Type ( PhysicalDeviceVulkanMemoryModelFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceVulkan12Features )       *,
            VkPhysicalDeviceVulkan12Features        const *
    ) noexcept -> Type ( PhysicalDeviceVulkan12Features ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceVulkan12Features              *,
            Type ( PhysicalDeviceVulkan12Features ) const *
    ) noexcept -> VkPhysicalDeviceVulkan12Features *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDevice8BitStorageFeatures              *,
            Type ( PhysicalDevice8BitStorageFeatures ) const *
    ) noexcept -> VkPhysicalDevice8BitStorageFeatures *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceBufferDeviceAddressFeatures              *,
            Type ( PhysicalDeviceBufferDeviceAddressFeatures ) const *
    ) noexcept -> VkPhysicalDeviceBufferDeviceAddressFeatures *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceDescriptorIndexingFeatures              *,
            Type ( PhysicalDeviceDescriptorIndexingFeatures ) const *
    ) noexcept -> VkPhysicalDeviceDescriptorIndexingFeatures *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceHostQueryResetFeatures              *,
            Type ( PhysicalDeviceHostQueryResetFeatures ) const *
    ) noexcept -> VkPhysicalDeviceHostQueryResetFeatures *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceImagelessFramebufferFeatures              *,
            Type ( PhysicalDeviceImagelessFrameBufferFeatures ) const *
    ) noexcept -> VkPhysicalDeviceImagelessFramebufferFeatures *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceHostQueryResetFeatures )       *,
            VkPhysicalDeviceHostQueryResetFeatures        const *
    ) noexcept -> Type ( PhysicalDeviceHostQueryResetFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceSeparateDepthStencilLayoutsFeatures )       *,
            VkPhysicalDeviceSeparateDepthStencilLayoutsFeatures        const *
    ) noexcept -> Type ( PhysicalDeviceSeparateDepthStencilLayoutsFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceTimelineSemaphoreFeatures )       *,
            VkPhysicalDeviceTimelineSemaphoreFeatures        const *
    ) noexcept -> Type ( PhysicalDeviceTimelineSemaphoreFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceScalarBlockLayoutFeatures              *,
            Type ( PhysicalDeviceScalarBlockLayoutFeatures ) const *
    ) noexcept -> VkPhysicalDeviceScalarBlockLayoutFeatures *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceSeparateDepthStencilLayoutsFeatures              *,
            Type ( PhysicalDeviceSeparateDepthStencilLayoutsFeatures ) const *
    ) noexcept -> VkPhysicalDeviceSeparateDepthStencilLayoutsFeatures *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceShaderAtomicInt64Features              *,
            Type ( PhysicalDeviceShaderAtomicInt64Features ) const *
    ) noexcept -> VkPhysicalDeviceShaderAtomicInt64Features *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceShaderFloat16Int8Features              *,
            Type ( PhysicalDeviceShaderFloat16Int8Features ) const *
    ) noexcept -> VkPhysicalDeviceShaderFloat16Int8Features *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceShaderSubgroupExtendedTypesFeatures              *,
            Type ( PhysicalDeviceShaderSubgroupExtendedTypesFeatures ) const *
    ) noexcept -> VkPhysicalDeviceShaderSubgroupExtendedTypesFeatures *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceTimelineSemaphoreFeatures              *,
            Type ( PhysicalDeviceTimelineSemaphoreFeatures ) const *
    ) noexcept -> VkPhysicalDeviceTimelineSemaphoreFeatures *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceUniformBufferStandardLayoutFeatures              *,
            Type ( PhysicalDeviceUniformBufferStandardLayoutFeatures ) const *
    ) noexcept -> VkPhysicalDeviceUniformBufferStandardLayoutFeatures *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceVulkanMemoryModelFeatures              *,
            Type ( PhysicalDeviceVulkanMemoryModelFeatures ) const *
    ) noexcept -> VkPhysicalDeviceVulkanMemoryModelFeatures *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceVulkan13Properties )        *,
            VkPhysicalDeviceVulkan13Properties         const *
    ) noexcept -> Type ( PhysicalDeviceVulkan13Properties ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceVulkan13Features )        *,
            VkPhysicalDeviceVulkan13Features         const *
    ) noexcept -> Type ( PhysicalDeviceVulkan13Features ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceBlendOperationAdvancedProperties )           *,
            VkPhysicalDeviceBlendOperationAdvancedPropertiesEXT         const *
    ) noexcept -> Type ( PhysicalDeviceBlendOperationAdvancedProperties ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONSERVATIVE_RASTERIZATION_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceConservativeRasterizationProperties )           *,
            VkPhysicalDeviceConservativeRasterizationPropertiesEXT         const *
    ) noexcept -> Type ( PhysicalDeviceConservativeRasterizationProperties ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceCustomBorderColorProperties )           *,
            VkPhysicalDeviceCustomBorderColorPropertiesEXT         const *
    ) noexcept -> Type ( PhysicalDeviceCustomBorderColorProperties ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISCARD_RECTANGLES_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceDiscardRectangleProperties )           *,
            VkPhysicalDeviceDiscardRectanglePropertiesEXT         const *
    ) noexcept -> Type ( PhysicalDeviceDiscardRectangleProperties ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTERNAL_MEMORY_HOST_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceExternalMemoryHostProperties )           *,
            VkPhysicalDeviceExternalMemoryHostPropertiesEXT         const *
    ) noexcept -> Type ( PhysicalDeviceExternalMemoryHostProperties ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceFragmentDensityMapProperties )           *,
            VkPhysicalDeviceFragmentDensityMapPropertiesEXT         const *
    ) noexcept -> Type ( PhysicalDeviceFragmentDensityMapProperties ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceFragmentDensityMap2Properties )           *,
            VkPhysicalDeviceFragmentDensityMap2PropertiesEXT         const *
    ) noexcept -> Type ( PhysicalDeviceFragmentDensityMap2Properties ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceInlineUniformBlockProperties )           *,
            VkPhysicalDeviceInlineUniformBlockProperties_t          const *
    ) noexcept -> Type ( PhysicalDeviceInlineUniformBlockProperties ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceLineRasterizationProperties )            *,
            VkPhysicalDeviceLineRasterizationPropertiesEXT          const *
    ) noexcept -> Type ( PhysicalDeviceLineRasterizationProperties ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceMultiDrawProperties )            *,
            VkPhysicalDeviceMultiDrawPropertiesEXT          const *
    ) noexcept -> Type ( PhysicalDeviceMultiDrawProperties ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PCI_BUS_INFO_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDevicePCIBusInfoProperties )            *,
            VkPhysicalDevicePCIBusInfoPropertiesEXT          const *
    ) noexcept -> Type ( PhysicalDevicePCIBusInfoProperties ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PHYSICAL_DEVICE_DRM_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceDRMProperties )            *,
            VkPhysicalDeviceDrmPropertiesEXT          const *
    ) noexcept -> Type ( PhysicalDeviceDRMProperties ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceProvokingVertexProperties )            *,
            VkPhysicalDeviceProvokingVertexPropertiesEXT          const *
    ) noexcept -> Type ( PhysicalDeviceProvokingVertexProperties ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceRobustnessProperties )             *,
            VkPhysicalDeviceRobustness2PropertiesEXT          const *
    ) noexcept -> Type ( PhysicalDeviceRobustnessProperties ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceSampleLocationsProperties )            *,
            VkPhysicalDeviceSampleLocationsPropertiesEXT          const *
    ) noexcept -> Type ( PhysicalDeviceSampleLocationsProperties ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceSubgroupSizeControlProperties )            *,
            VkPhysicalDeviceSubgroupSizeControlProperties_t           const *
    ) noexcept -> Type ( PhysicalDeviceSubgroupSizeControlProperties ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceTexelBufferAlignmentProperties )            *,
            VkPhysicalDeviceTexelBufferAlignmentProperties_t           const *
    ) noexcept -> Type ( PhysicalDeviceTexelBufferAlignmentProperties ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceTransformFeedbackProperties )             *,
            VkPhysicalDeviceTransformFeedbackPropertiesEXT           const *
    ) noexcept -> Type ( PhysicalDeviceTransformFeedbackProperties ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceVertexAttributeDivisorProperties )             *,
            VkPhysicalDeviceVertexAttributeDivisorPropertiesEXT           const *
    ) noexcept -> Type ( PhysicalDeviceVertexAttributeDivisorProperties ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceAccelerationStructureProperties )             *,
            VkPhysicalDeviceAccelerationStructurePropertiesKHR           const *
    ) noexcept -> Type ( PhysicalDeviceAccelerationStructureProperties ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceFragmentShadingRateProperties )             *,
            VkPhysicalDeviceFragmentShadingRatePropertiesKHR           const *
    ) noexcept -> Type ( PhysicalDeviceFragmentShadingRateProperties ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceMaintenance4Properties )             *,
            VkPhysicalDeviceMaintenance4Properties_t            const *
    ) noexcept -> Type ( PhysicalDeviceMaintenance4Properties ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDevicePerformanceQueryProperties )              *,
            VkPhysicalDevicePerformanceQueryPropertiesKHR            const *
    ) noexcept -> Type ( PhysicalDevicePerformanceQueryProperties ) *;
#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDevicePortabilitySubsetProperties )              *,
            VkPhysicalDevicePortabilitySubsetPropertiesKHR            const *
    ) noexcept -> Type ( PhysicalDevicePortabilitySubsetProperties ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PUSH_DESCRIPTOR_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDevicePushDescriptorProperties )              *,
            VkPhysicalDevicePushDescriptorPropertiesKHR            const *
    ) noexcept -> Type ( PhysicalDevicePushDescriptorProperties ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceRayTracingPipelineProperties )              *,
            VkPhysicalDeviceRayTracingPipelinePropertiesKHR            const *
    ) noexcept -> Type ( PhysicalDeviceRayTracingPipelineProperties ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceShaderIntegerDotProductProperties )              *,
            VkPhysicalDeviceShaderIntegerDotProductProperties_t             const *
    ) noexcept -> Type ( PhysicalDeviceShaderIntegerDotProductProperties ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceCooperativeMatrixPropertiesNVidia )        *,
            VkPhysicalDeviceCooperativeMatrixPropertiesNV             const *
    ) noexcept -> Type ( PhysicalDeviceCooperativeMatrixPropertiesNVidia ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceDeviceGeneratedCommandsPropertiesNVidia )        *,
            VkPhysicalDeviceDeviceGeneratedCommandsPropertiesNV             const *
    ) noexcept -> Type ( PhysicalDeviceDeviceGeneratedCommandsPropertiesNVidia ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceFragmentShadingRateEnumsPropertiesNVidia )        *,
            VkPhysicalDeviceFragmentShadingRateEnumsPropertiesNV             const *
    ) noexcept -> Type ( PhysicalDeviceFragmentShadingRateEnumsPropertiesNVidia ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceMeshShaderPropertiesNVidia )        *,
            VkPhysicalDeviceMeshShaderPropertiesNV             const *
    ) noexcept -> Type ( PhysicalDeviceMeshShaderPropertiesNVidia ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceRayTracingPropertiesNVidia )        *,
            VkPhysicalDeviceRayTracingPropertiesNV             const *
    ) noexcept -> Type ( PhysicalDeviceRayTracingPropertiesNVidia ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceShaderSMBuiltinsPropertiesNVidia )        *,
            VkPhysicalDeviceShaderSMBuiltinsPropertiesNV             const *
    ) noexcept -> Type ( PhysicalDeviceShaderSMBuiltinsPropertiesNVidia ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceShadingRateImagePropertiesNVidia )        *,
            VkPhysicalDeviceShadingRateImagePropertiesNV             const *
    ) noexcept -> Type ( PhysicalDeviceShadingRateImagePropertiesNVidia ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceMultiviewPerViewAttributesPropertiesNVidia )         *,
            VkPhysicalDeviceMultiviewPerViewAttributesPropertiesNVX             const *
    ) noexcept -> Type ( PhysicalDeviceMultiviewPerViewAttributesPropertiesNVidia ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceShaderCorePropertiesAMD )            *,
            VkPhysicalDeviceShaderCorePropertiesAMD             const *
    ) noexcept -> Type ( PhysicalDeviceShaderCorePropertiesAMD ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_2_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceShaderCoreProperties2AMD )            *,
            VkPhysicalDeviceShaderCoreProperties2AMD             const *
    ) noexcept -> Type ( PhysicalDeviceShaderCoreProperties2AMD ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceFragmentDensityMapOffsetPropertiesQualcomm )            *,
            VkPhysicalDeviceFragmentDensityMapOffsetPropertiesQCOM                 const *
    ) noexcept -> Type ( PhysicalDeviceFragmentDensityMapOffsetPropertiesQualcomm ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceSubpassShadingPropertiesHuawei )                *,
            VkPhysicalDeviceSubpassShadingPropertiesHUAWEI                 const *
    ) noexcept -> Type ( PhysicalDeviceSubpassShadingPropertiesHuawei ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_4444_FORMATS_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDevice4444FormatsFeatures )           *,
            VkPhysicalDevice4444FormatsFeaturesEXT         const *
    ) noexcept -> Type ( PhysicalDevice4444FormatsFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_4444_FORMATS_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDevice4444FormatsFeaturesEXT            *,
            Type ( PhysicalDevice4444FormatsFeatures )  const *
    ) noexcept -> VkPhysicalDevice4444FormatsFeaturesEXT *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceVulkan13Features               *,
            Type ( PhysicalDeviceVulkan13Features )  const *
    ) noexcept -> VkPhysicalDeviceVulkan13Features *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXTURE_COMPRESSION_ASTC_HDR_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceASTCDecodeFeatures )           *,
            VkPhysicalDeviceASTCDecodeFeaturesEXT         const *
    ) noexcept -> Type ( PhysicalDeviceASTCDecodeFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXTURE_COMPRESSION_ASTC_HDR_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceASTCDecodeFeaturesEXT            *,
            Type ( PhysicalDeviceASTCDecodeFeatures )  const *
    ) noexcept -> VkPhysicalDeviceASTCDecodeFeaturesEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceBlendOperationAdvancedFeatures )           *,
            VkPhysicalDeviceBlendOperationAdvancedFeaturesEXT         const *
    ) noexcept -> Type ( PhysicalDeviceBlendOperationAdvancedFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceBlendOperationAdvancedFeaturesEXT            *,
            Type ( PhysicalDeviceBlendOperationAdvancedFeatures )  const *
    ) noexcept -> VkPhysicalDeviceBlendOperationAdvancedFeaturesEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_BORDER_COLOR_SWIZZLE_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceBorderColorSwizzleFeatures )           *,
            VkPhysicalDeviceBorderColorSwizzleFeaturesEXT         const *
    ) noexcept -> Type ( PhysicalDeviceBorderColorSwizzleFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_BORDER_COLOR_SWIZZLE_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceBorderColorSwizzleFeaturesEXT            *,
            Type ( PhysicalDeviceBorderColorSwizzleFeatures )  const *
    ) noexcept -> VkPhysicalDeviceBorderColorSwizzleFeaturesEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_COLOR_WRITE_ENABLE_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceColorWriteEnableFeatures )           *,
            VkPhysicalDeviceColorWriteEnableFeaturesEXT         const *
    ) noexcept -> Type ( PhysicalDeviceColorWriteEnableFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_COLOR_WRITE_ENABLE_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceColorWriteEnableFeaturesEXT            *,
            Type ( PhysicalDeviceColorWriteEnableFeatures )  const *
    ) noexcept -> VkPhysicalDeviceColorWriteEnableFeaturesEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceConditionalRenderingFeatures )           *,
            VkPhysicalDeviceConditionalRenderingFeaturesEXT         const *
    ) noexcept -> Type ( PhysicalDeviceConditionalRenderingFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceConditionalRenderingFeaturesEXT            *,
            Type ( PhysicalDeviceConditionalRenderingFeatures )  const *
    ) noexcept -> VkPhysicalDeviceConditionalRenderingFeaturesEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceCustomBorderColorFeatures )           *,
            VkPhysicalDeviceCustomBorderColorFeaturesEXT         const *
    ) noexcept -> Type ( PhysicalDeviceCustomBorderColorFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceCustomBorderColorFeaturesEXT            *,
            Type ( PhysicalDeviceCustomBorderColorFeatures )  const *
    ) noexcept -> VkPhysicalDeviceCustomBorderColorFeaturesEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_CONTROL_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceDepthClipControlFeatures )           *,
            VkPhysicalDeviceDepthClipControlFeaturesEXT         const *
    ) noexcept -> Type ( PhysicalDeviceDepthClipControlFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_CONTROL_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceDepthClipControlFeaturesEXT            *,
            Type ( PhysicalDeviceDepthClipControlFeatures )  const *
    ) noexcept -> VkPhysicalDeviceDepthClipControlFeaturesEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_ENABLE_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceDepthClipEnableFeatures )           *,
            VkPhysicalDeviceDepthClipEnableFeaturesEXT         const *
    ) noexcept -> Type ( PhysicalDeviceDepthClipEnableFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_ENABLE_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceDepthClipEnableFeaturesEXT            *,
            Type ( PhysicalDeviceDepthClipEnableFeatures )  const *
    ) noexcept -> VkPhysicalDeviceDepthClipEnableFeaturesEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEVICE_MEMORY_REPORT_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceDeviceMemoryReportFeatures )           *,
            VkPhysicalDeviceDeviceMemoryReportFeaturesEXT         const *
    ) noexcept -> Type ( PhysicalDeviceDeviceMemoryReportFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEVICE_MEMORY_REPORT_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceDeviceMemoryReportFeaturesEXT            *,
            Type ( PhysicalDeviceDeviceMemoryReportFeatures )  const *
    ) noexcept -> VkPhysicalDeviceDeviceMemoryReportFeaturesEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceExtendedDynamicStateFeatures )           *,
            VkPhysicalDeviceExtendedDynamicStateFeaturesEXT         const *
    ) noexcept -> Type ( PhysicalDeviceExtendedDynamicStateFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceExtendedDynamicStateFeaturesEXT            *,
            Type ( PhysicalDeviceExtendedDynamicStateFeatures )  const *
    ) noexcept -> VkPhysicalDeviceExtendedDynamicStateFeaturesEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_2_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceExtendedDynamicState2Features )           *,
            VkPhysicalDeviceExtendedDynamicState2FeaturesEXT         const *
    ) noexcept -> Type ( PhysicalDeviceExtendedDynamicState2Features ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_2_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceExtendedDynamicState2FeaturesEXT            *,
            Type ( PhysicalDeviceExtendedDynamicState2Features )  const *
    ) noexcept -> VkPhysicalDeviceExtendedDynamicState2FeaturesEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceFragmentDensityMapFeatures )           *,
            VkPhysicalDeviceFragmentDensityMapFeaturesEXT         const *
    ) noexcept -> Type ( PhysicalDeviceFragmentDensityMapFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceFragmentDensityMapFeaturesEXT            *,
            Type ( PhysicalDeviceFragmentDensityMapFeatures )  const *
    ) noexcept -> VkPhysicalDeviceFragmentDensityMapFeaturesEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceFragmentDensityMap2Features )           *,
            VkPhysicalDeviceFragmentDensityMap2FeaturesEXT         const *
    ) noexcept -> Type ( PhysicalDeviceFragmentDensityMap2Features ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceFragmentDensityMap2FeaturesEXT            *,
            Type ( PhysicalDeviceFragmentDensityMap2Features )  const *
    ) noexcept -> VkPhysicalDeviceFragmentDensityMap2FeaturesEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_SHADER_INTERLOCK_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceFragmentShaderInterlockFeatures )           *,
            VkPhysicalDeviceFragmentShaderInterlockFeaturesEXT         const *
    ) noexcept -> Type ( PhysicalDeviceFragmentShaderInterlockFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_SHADER_INTERLOCK_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceFragmentShaderInterlockFeaturesEXT            *,
            Type ( PhysicalDeviceFragmentShaderInterlockFeatures )  const *
    ) noexcept -> VkPhysicalDeviceFragmentShaderInterlockFeaturesEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceGlobalPriorityQueryFeatures )           *,
            VkPhysicalDeviceGlobalPriorityQueryFeaturesEXT         const *
    ) noexcept -> Type ( PhysicalDeviceGlobalPriorityQueryFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceGlobalPriorityQueryFeaturesEXT            *,
            Type ( PhysicalDeviceGlobalPriorityQueryFeatures )  const *
    ) noexcept -> VkPhysicalDeviceGlobalPriorityQueryFeaturesEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_ROBUSTNESS_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceImageRobustnessFeatures )           *,
            VkPhysicalDeviceImageRobustnessFeatures_t          const *
    ) noexcept -> Type ( PhysicalDeviceImageRobustnessFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_ROBUSTNESS_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceImageRobustnessFeatures_t             *,
            Type ( PhysicalDeviceImageRobustnessFeatures )  const *
    ) noexcept -> VkPhysicalDeviceImageRobustnessFeatures_t *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_VIEW_MIN_LOD_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceImageViewMinLODFeatures )            *,
            VkPhysicalDeviceImageViewMinLodFeaturesEXT          const *
    ) noexcept -> Type ( PhysicalDeviceImageViewMinLODFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_VIEW_MIN_LOD_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceImageViewMinLodFeaturesEXT             *,
            Type ( PhysicalDeviceImageViewMinLODFeatures )   const *
    ) noexcept -> VkPhysicalDeviceImageViewMinLodFeaturesEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INDEX_TYPE_UINT8_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceIndexTypeUInt8Features )            *,
            VkPhysicalDeviceIndexTypeUint8FeaturesEXT          const *
    ) noexcept -> Type ( PhysicalDeviceIndexTypeUInt8Features ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INDEX_TYPE_UINT8_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceIndexTypeUint8FeaturesEXT             *,
            Type ( PhysicalDeviceIndexTypeUInt8Features )   const *
    ) noexcept -> VkPhysicalDeviceIndexTypeUint8FeaturesEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceInlineUniformBlockFeatures )            *,
            VkPhysicalDeviceInlineUniformBlockFeatures_t           const *
    ) noexcept -> Type ( PhysicalDeviceInlineUniformBlockFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceInlineUniformBlockFeatures_t              *,
            Type ( PhysicalDeviceInlineUniformBlockFeatures )   const *
    ) noexcept -> VkPhysicalDeviceInlineUniformBlockFeatures_t *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceLineRasterizationFeatures )             *,
            VkPhysicalDeviceLineRasterizationFeaturesEXT           const *
    ) noexcept -> Type ( PhysicalDeviceLineRasterizationFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceLineRasterizationFeaturesEXT              *,
            Type ( PhysicalDeviceLineRasterizationFeatures )    const *
    ) noexcept -> VkPhysicalDeviceLineRasterizationFeaturesEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PAGEABLE_DEVICE_LOCAL_MEMORY_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDevicePageableDeviceLocalMemoryFeatures )             *,
            VkPhysicalDevicePageableDeviceLocalMemoryFeaturesEXT           const *
    ) noexcept -> Type ( PhysicalDevicePageableDeviceLocalMemoryFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PAGEABLE_DEVICE_LOCAL_MEMORY_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDevicePageableDeviceLocalMemoryFeaturesEXT              *,
            Type ( PhysicalDevicePageableDeviceLocalMemoryFeatures )    const *
    ) noexcept -> VkPhysicalDevicePageableDeviceLocalMemoryFeaturesEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_PRIORITY_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceMemoryPriorityFeatures )             *,
            VkPhysicalDeviceMemoryPriorityFeaturesEXT           const *
    ) noexcept -> Type ( PhysicalDeviceMemoryPriorityFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_PRIORITY_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceMemoryPriorityFeaturesEXT              *,
            Type ( PhysicalDeviceMemoryPriorityFeatures )    const *
    ) noexcept -> VkPhysicalDeviceMemoryPriorityFeaturesEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceMultiDrawFeatures )             *,
            VkPhysicalDeviceMultiDrawFeaturesEXT           const *
    ) noexcept -> Type ( PhysicalDeviceMultiDrawFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_PRIORITY_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceMultiDrawFeaturesEXT              *,
            Type ( PhysicalDeviceMultiDrawFeatures )    const *
    ) noexcept -> VkPhysicalDeviceMultiDrawFeaturesEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDevicePipelineCreationCacheControlFeatures )             *,
            VkPhysicalDevicePipelineCreationCacheControlFeatures_t            const *
    ) noexcept -> Type ( PhysicalDevicePipelineCreationCacheControlFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDevicePipelineCreationCacheControlFeatures_t               *,
            Type ( PhysicalDevicePipelineCreationCacheControlFeatures )    const *
    ) noexcept -> VkPhysicalDevicePipelineCreationCacheControlFeatures_t *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIMITIVE_TOPOLOGY_LIST_RESTART_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDevicePrimitiveTopologyListRestartFeatures )             *,
            VkPhysicalDevicePrimitiveTopologyListRestartFeaturesEXT           const *
    ) noexcept -> Type ( PhysicalDevicePrimitiveTopologyListRestartFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIMITIVE_TOPOLOGY_LIST_RESTART_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDevicePrimitiveTopologyListRestartFeaturesEXT               *,
            Type ( PhysicalDevicePrimitiveTopologyListRestartFeatures )     const *
    ) noexcept -> VkPhysicalDevicePrimitiveTopologyListRestartFeaturesEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDevicePrivateDataFeatures )             *,
            VkPhysicalDevicePrivateDataFeatures_t            const *
    ) noexcept -> Type ( PhysicalDevicePrivateDataFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDevicePrivateDataFeatures_t                *,
            Type ( PhysicalDevicePrivateDataFeatures )     const *
    ) noexcept -> VkPhysicalDevicePrivateDataFeatures_t *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceProvokingVertexFeatures )              *,
            VkPhysicalDeviceProvokingVertexFeaturesEXT            const *
    ) noexcept -> Type ( PhysicalDeviceProvokingVertexFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceProvokingVertexFeaturesEXT                *,
            Type ( PhysicalDeviceProvokingVertexFeatures )      const *
    ) noexcept -> VkPhysicalDeviceProvokingVertexFeaturesEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_RGBA_10_X_6_FORMATS_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceRGBA10x6FormatsFeatures )              *,
            VkPhysicalDeviceRGBA10X6FormatsFeaturesEXT            const *
    ) noexcept -> Type ( PhysicalDeviceRGBA10x6FormatsFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_RGBA_10_X_6_FORMATS_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceRGBA10X6FormatsFeaturesEXT                *,
            Type ( PhysicalDeviceRGBA10x6FormatsFeatures )      const *
    ) noexcept -> VkPhysicalDeviceRGBA10X6FormatsFeaturesEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceRobustnessFeatures )               *,
            VkPhysicalDeviceRobustness2FeaturesEXT            const *
    ) noexcept -> Type ( PhysicalDeviceRobustnessFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceRobustness2FeaturesEXT                *,
            Type ( PhysicalDeviceRobustnessFeatures )       const *
    ) noexcept -> VkPhysicalDeviceRobustness2FeaturesEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceShaderAtomicFloatFeatures )              *,
            VkPhysicalDeviceShaderAtomicFloatFeaturesEXT            const *
    ) noexcept -> Type ( PhysicalDeviceShaderAtomicFloatFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceShaderAtomicFloatFeaturesEXT                 *,
            Type ( PhysicalDeviceShaderAtomicFloatFeatures )       const *
    ) noexcept -> VkPhysicalDeviceShaderAtomicFloatFeaturesEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_2_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceShaderAtomicFloat2Features )              *,
            VkPhysicalDeviceShaderAtomicFloat2FeaturesEXT            const *
    ) noexcept -> Type ( PhysicalDeviceShaderAtomicFloat2Features ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_2_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceShaderAtomicFloat2FeaturesEXT                 *,
            Type ( PhysicalDeviceShaderAtomicFloat2Features )       const *
    ) noexcept -> VkPhysicalDeviceShaderAtomicFloat2FeaturesEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_DEMOTE_TO_HELPER_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceShaderDemoteToHelperInvocationFeatures )              *,
            VkPhysicalDeviceShaderDemoteToHelperInvocationFeatures_t             const *
    ) noexcept -> Type ( PhysicalDeviceShaderDemoteToHelperInvocationFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_DEMOTE_TO_HELPER_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceShaderDemoteToHelperInvocationFeatures_t                  *,
            Type ( PhysicalDeviceShaderDemoteToHelperInvocationFeatures )       const *
    ) noexcept -> VkPhysicalDeviceShaderDemoteToHelperInvocationFeatures_t *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_IMAGE_ATOMIC_INT64_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceShaderImageAtomicInt64Features )               *,
            VkPhysicalDeviceShaderImageAtomicInt64FeaturesEXT             const *
    ) noexcept -> Type ( PhysicalDeviceShaderImageAtomicInt64Features ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_IMAGE_ATOMIC_INT64_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceShaderImageAtomicInt64FeaturesEXT                 *,
            Type ( PhysicalDeviceShaderImageAtomicInt64Features )       const *
    ) noexcept -> VkPhysicalDeviceShaderImageAtomicInt64FeaturesEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceSubgroupSizeControlFeatures )              *,
            VkPhysicalDeviceSubgroupSizeControlFeatures_t             const *
    ) noexcept -> Type ( PhysicalDeviceSubgroupSizeControlFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceSubgroupSizeControlFeatures_t                  *,
            Type ( PhysicalDeviceSubgroupSizeControlFeatures )       const *
    ) noexcept -> VkPhysicalDeviceSubgroupSizeControlFeatures_t *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceTexelBufferAlignmentFeatures )              *,
            VkPhysicalDeviceTexelBufferAlignmentFeatures_t             const *
    ) noexcept -> Type ( PhysicalDeviceTexelBufferAlignmentFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceTexelBufferAlignmentFeatures_t                  *,
            Type ( PhysicalDeviceTexelBufferAlignmentFeatures )       const *
    ) noexcept -> VkPhysicalDeviceTexelBufferAlignmentFeatures_t *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXTURE_COMPRESSION_ASTC_HDR_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceTextureCompressionASTCHDRFeatures )              *,
            VkPhysicalDeviceTextureCompressionASTCHDRFeatures_t             const *
    ) noexcept -> Type ( PhysicalDeviceTextureCompressionASTCHDRFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXTURE_COMPRESSION_ASTC_HDR_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceTextureCompressionASTCHDRFeatures_t                  *,
            Type ( PhysicalDeviceTextureCompressionASTCHDRFeatures )       const *
    ) noexcept -> VkPhysicalDeviceTextureCompressionASTCHDRFeatures_t *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceTransformFeedbackFeatures )               *,
            VkPhysicalDeviceTransformFeedbackFeaturesEXT             const *
    ) noexcept -> Type ( PhysicalDeviceTransformFeedbackFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceTransformFeedbackFeaturesEXT                  *,
            Type ( PhysicalDeviceTransformFeedbackFeatures )        const *
    ) noexcept -> VkPhysicalDeviceTransformFeedbackFeaturesEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceVertexAttributeDivisorFeatures )               *,
            VkPhysicalDeviceVertexAttributeDivisorFeaturesEXT             const *
    ) noexcept -> Type ( PhysicalDeviceVertexAttributeDivisorFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceVertexAttributeDivisorFeaturesEXT                  *,
            Type ( PhysicalDeviceVertexAttributeDivisorFeatures )        const *
    ) noexcept -> VkPhysicalDeviceVertexAttributeDivisorFeaturesEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_INPUT_DYNAMIC_STATE_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceVertexInputDynamicStateFeatures )               *,
            VkPhysicalDeviceVertexInputDynamicStateFeaturesEXT             const *
    ) noexcept -> Type ( PhysicalDeviceVertexInputDynamicStateFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_INPUT_DYNAMIC_STATE_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceVertexInputDynamicStateFeaturesEXT                  *,
            Type ( PhysicalDeviceVertexInputDynamicStateFeatures )        const *
    ) noexcept -> VkPhysicalDeviceVertexInputDynamicStateFeaturesEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_2_PLANE_444_FORMATS_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceYCBCR2Plane444FormatsFeatures )               *,
            VkPhysicalDeviceYcbcr2Plane444FormatsFeaturesEXT             const *
    ) noexcept -> Type ( PhysicalDeviceYCBCR2Plane444FormatsFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_2_PLANE_444_FORMATS_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceYcbcr2Plane444FormatsFeaturesEXT                  *,
            Type ( PhysicalDeviceYCBCR2Plane444FormatsFeatures )        const *
    ) noexcept -> VkPhysicalDeviceYcbcr2Plane444FormatsFeaturesEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_IMAGE_ARRAYS_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceYCBCRImageArraysFeatures )               *,
            VkPhysicalDeviceYcbcrImageArraysFeaturesEXT             const *
    ) noexcept -> Type ( PhysicalDeviceYCBCRImageArraysFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_IMAGE_ARRAYS_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceYcbcrImageArraysFeaturesEXT                  *,
            Type ( PhysicalDeviceYCBCRImageArraysFeatures )        const *
    ) noexcept -> VkPhysicalDeviceYcbcrImageArraysFeaturesEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceAccelerationStructureFeatures )               *,
            VkPhysicalDeviceAccelerationStructureFeaturesKHR             const *
    ) noexcept -> Type ( PhysicalDeviceAccelerationStructureFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceAccelerationStructureFeaturesKHR                  *,
            Type ( PhysicalDeviceAccelerationStructureFeatures )        const *
    ) noexcept -> VkPhysicalDeviceAccelerationStructureFeaturesKHR *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceDynamicRenderingFeatures )               *,
            VkPhysicalDeviceDynamicRenderingFeatures_t              const *
    ) noexcept -> Type ( PhysicalDeviceDynamicRenderingFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceDynamicRenderingFeatures_t                   *,
            Type ( PhysicalDeviceDynamicRenderingFeatures )        const *
    ) noexcept -> VkPhysicalDeviceDynamicRenderingFeatures_t *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceFragmentShadingRateFeatures )                *,
            VkPhysicalDeviceFragmentShadingRateFeaturesKHR              const *
    ) noexcept -> Type ( PhysicalDeviceFragmentShadingRateFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceFragmentShadingRateFeaturesKHR                   *,
            Type ( PhysicalDeviceFragmentShadingRateFeatures )         const *
    ) noexcept -> VkPhysicalDeviceFragmentShadingRateFeaturesKHR *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceMaintenance4Features )                *,
            VkPhysicalDeviceMaintenance4Features_t               const *
    ) noexcept -> Type ( PhysicalDeviceMaintenance4Features ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceMaintenance4Features_t                    *,
            Type ( PhysicalDeviceMaintenance4Features )         const *
    ) noexcept -> VkPhysicalDeviceMaintenance4Features_t *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDevicePerformanceQueryFeatures )                 *,
            VkPhysicalDevicePerformanceQueryFeaturesKHR               const *
    ) noexcept -> Type ( PhysicalDevicePerformanceQueryFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDevicePerformanceQueryFeaturesKHR                    *,
            Type ( PhysicalDevicePerformanceQueryFeatures )          const *
    ) noexcept -> VkPhysicalDevicePerformanceQueryFeaturesKHR *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDevicePipelineExecutablePropertiesFeatures )                 *,
            VkPhysicalDevicePipelineExecutablePropertiesFeaturesKHR               const *
    ) noexcept -> Type ( PhysicalDevicePipelineExecutablePropertiesFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDevicePipelineExecutablePropertiesFeaturesKHR                    *,
            Type ( PhysicalDevicePipelineExecutablePropertiesFeatures )          const *
    ) noexcept -> VkPhysicalDevicePipelineExecutablePropertiesFeaturesKHR *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_ID_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDevicePresentIDFeatures )                 *,
            VkPhysicalDevicePresentIdFeaturesKHR               const *
    ) noexcept -> Type ( PhysicalDevicePresentIDFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_ID_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDevicePresentIdFeaturesKHR                    *,
            Type ( PhysicalDevicePresentIDFeatures )          const *
    ) noexcept -> VkPhysicalDevicePresentIdFeaturesKHR *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_WAIT_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDevicePresentWaitFeatures )                 *,
            VkPhysicalDevicePresentWaitFeaturesKHR               const *
    ) noexcept -> Type ( PhysicalDevicePresentWaitFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_WAIT_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDevicePresentWaitFeaturesKHR                    *,
            Type ( PhysicalDevicePresentWaitFeatures )          const *
    ) noexcept -> VkPhysicalDevicePresentWaitFeaturesKHR *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_QUERY_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceRayQueryFeatures )                 *,
            VkPhysicalDeviceRayQueryFeaturesKHR               const *
    ) noexcept -> Type ( PhysicalDeviceRayQueryFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_QUERY_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceRayQueryFeaturesKHR                    *,
            Type ( PhysicalDeviceRayQueryFeatures )          const *
    ) noexcept -> VkPhysicalDeviceRayQueryFeaturesKHR *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_CLOCK_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceShaderClockFeatures )                 *,
            VkPhysicalDeviceShaderClockFeaturesKHR               const *
    ) noexcept -> Type ( PhysicalDeviceShaderClockFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_CLOCK_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceShaderClockFeaturesKHR                    *,
            Type ( PhysicalDeviceShaderClockFeatures )          const *
    ) noexcept -> VkPhysicalDeviceShaderClockFeaturesKHR *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceRayTracingPipelineFeatures )                 *,
            VkPhysicalDeviceRayTracingPipelineFeaturesKHR               const *
    ) noexcept -> Type ( PhysicalDeviceRayTracingPipelineFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceRayTracingPipelineFeaturesKHR                    *,
            Type ( PhysicalDeviceRayTracingPipelineFeatures )          const *
    ) noexcept -> VkPhysicalDeviceRayTracingPipelineFeaturesKHR *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_SUBGROUP_UNIFORM_CONTROL_FLOW_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceShaderSubgroupUniformControlFlowFeatures )                 *,
            VkPhysicalDeviceShaderSubgroupUniformControlFlowFeaturesKHR               const *
    ) noexcept -> Type ( PhysicalDeviceShaderSubgroupUniformControlFlowFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_SUBGROUP_UNIFORM_CONTROL_FLOW_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceShaderSubgroupUniformControlFlowFeaturesKHR                    *,
            Type ( PhysicalDeviceShaderSubgroupUniformControlFlowFeatures )          const *
    ) noexcept -> VkPhysicalDeviceShaderSubgroupUniformControlFlowFeaturesKHR *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_TERMINATE_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceShaderTerminateInvocationFeatures )                 *,
            VkPhysicalDeviceShaderTerminateInvocationFeatures_t                const *
    ) noexcept -> Type ( PhysicalDeviceShaderTerminateInvocationFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_TERMINATE_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceShaderTerminateInvocationFeatures_t                     *,
            Type ( PhysicalDeviceShaderTerminateInvocationFeatures )          const *
    ) noexcept -> VkPhysicalDeviceShaderTerminateInvocationFeatures_t *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceSynchronizationFeatures )                  *,
            VkPhysicalDeviceSynchronization2Features_t                const *
    ) noexcept -> Type ( PhysicalDeviceSynchronizationFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceSynchronization2Features_t                     *,
            Type ( PhysicalDeviceSynchronizationFeatures )           const *
    ) noexcept -> VkPhysicalDeviceSynchronization2Features_t *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceShaderIntegerDotProductFeatures )                  *,
            VkPhysicalDeviceShaderIntegerDotProductFeatures_t                 const *
    ) noexcept -> Type ( PhysicalDeviceShaderIntegerDotProductFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceShaderIntegerDotProductFeatures_t                      *,
            Type ( PhysicalDeviceShaderIntegerDotProductFeatures )           const *
    ) noexcept -> VkPhysicalDeviceShaderIntegerDotProductFeatures_t *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceWorkgroupMemoryExplicitLayoutFeatures )                   *,
            VkPhysicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR                 const *
    ) noexcept -> Type ( PhysicalDeviceWorkgroupMemoryExplicitLayoutFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR                      *,
            Type ( PhysicalDeviceWorkgroupMemoryExplicitLayoutFeatures )            const *
    ) noexcept -> VkPhysicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ZERO_INITIALIZE_WORKGROUP_MEMORY_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceZeroInitializeWorkgroupMemoryFeatures )                   *,
            VkPhysicalDeviceZeroInitializeWorkgroupMemoryFeatures_t                  const *
    ) noexcept -> Type ( PhysicalDeviceZeroInitializeWorkgroupMemoryFeatures ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ZERO_INITIALIZE_WORKGROUP_MEMORY_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceZeroInitializeWorkgroupMemoryFeatures_t                       *,
            Type ( PhysicalDeviceZeroInitializeWorkgroupMemoryFeatures )            const *
    ) noexcept -> VkPhysicalDeviceZeroInitializeWorkgroupMemoryFeatures_t *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COMPUTE_SHADER_DERIVATIVES_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceComputeShaderDerivativesFeaturesNVidia )             *,
            VkPhysicalDeviceComputeShaderDerivativesFeaturesNV                  const *
    ) noexcept -> Type ( PhysicalDeviceComputeShaderDerivativesFeaturesNVidia ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COMPUTE_SHADER_DERIVATIVES_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceComputeShaderDerivativesFeaturesNV                       *,
            Type ( PhysicalDeviceComputeShaderDerivativesFeaturesNVidia )      const *
    ) noexcept -> VkPhysicalDeviceComputeShaderDerivativesFeaturesNV *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceCooperativeMatrixFeaturesNVidia )             *,
            VkPhysicalDeviceCooperativeMatrixFeaturesNV                  const *
    ) noexcept -> Type ( PhysicalDeviceCooperativeMatrixFeaturesNVidia ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceCooperativeMatrixFeaturesNV                       *,
            Type ( PhysicalDeviceCooperativeMatrixFeaturesNVidia )      const *
    ) noexcept -> VkPhysicalDeviceCooperativeMatrixFeaturesNV *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CORNER_SAMPLED_IMAGE_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceCornerSampledImageFeaturesNVidia )             *,
            VkPhysicalDeviceCornerSampledImageFeaturesNV                  const *
    ) noexcept -> Type ( PhysicalDeviceCornerSampledImageFeaturesNVidia ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CORNER_SAMPLED_IMAGE_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceCornerSampledImageFeaturesNV                       *,
            Type ( PhysicalDeviceCornerSampledImageFeaturesNVidia )      const *
    ) noexcept -> VkPhysicalDeviceCornerSampledImageFeaturesNV *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COVERAGE_REDUCTION_MODE_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceCoverageReductionModeFeaturesNVidia )             *,
            VkPhysicalDeviceCoverageReductionModeFeaturesNV                  const *
    ) noexcept -> Type ( PhysicalDeviceCoverageReductionModeFeaturesNVidia ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COVERAGE_REDUCTION_MODE_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceCoverageReductionModeFeaturesNV                       *,
            Type ( PhysicalDeviceCoverageReductionModeFeaturesNVidia )      const *
    ) noexcept -> VkPhysicalDeviceCoverageReductionModeFeaturesNV *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceDeviceGeneratedCommandsFeaturesNVidia )             *,
            VkPhysicalDeviceDeviceGeneratedCommandsFeaturesNV                  const *
    ) noexcept -> Type ( PhysicalDeviceDeviceGeneratedCommandsFeaturesNVidia ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceDeviceGeneratedCommandsFeaturesNV                       *,
            Type ( PhysicalDeviceDeviceGeneratedCommandsFeaturesNVidia )      const *
    ) noexcept -> VkPhysicalDeviceDeviceGeneratedCommandsFeaturesNV *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_IMAGE_ALIASING_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNVidia )             *,
            VkPhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV                  const *
    ) noexcept -> Type ( PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNVidia ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_IMAGE_ALIASING_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV                       *,
            Type ( PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNVidia )      const *
    ) noexcept -> VkPhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTICS_CONFIG_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceDiagnosticsConfigFeaturesNVidia )             *,
            VkPhysicalDeviceDiagnosticsConfigFeaturesNV                  const *
    ) noexcept -> Type ( PhysicalDeviceDiagnosticsConfigFeaturesNVidia ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTICS_CONFIG_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceDiagnosticsConfigFeaturesNV                       *,
            Type ( PhysicalDeviceDiagnosticsConfigFeaturesNVidia )      const *
    ) noexcept -> VkPhysicalDeviceDiagnosticsConfigFeaturesNV *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SCISSOR_EXCLUSIVE_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceExclusiveScissorFeaturesNVidia )             *,
            VkPhysicalDeviceExclusiveScissorFeaturesNV                  const *
    ) noexcept -> Type ( PhysicalDeviceExclusiveScissorFeaturesNVidia ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SCISSOR_EXCLUSIVE_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceExclusiveScissorFeaturesNV                       *,
            Type ( PhysicalDeviceExclusiveScissorFeaturesNVidia )      const *
    ) noexcept -> VkPhysicalDeviceExclusiveScissorFeaturesNV *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_RDMA_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceExternalMemoryRDMAFeaturesNVidia )             *,
            VkPhysicalDeviceExternalMemoryRDMAFeaturesNV                  const *
    ) noexcept -> Type ( PhysicalDeviceExternalMemoryRDMAFeaturesNVidia ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_RDMA_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceExternalMemoryRDMAFeaturesNV                       *,
            Type ( PhysicalDeviceExternalMemoryRDMAFeaturesNVidia )      const *
    ) noexcept -> VkPhysicalDeviceExternalMemoryRDMAFeaturesNV *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADER_BARYCENTRIC_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceFragmentShaderBarycentricFeaturesNVidia )             *,
            VkPhysicalDeviceFragmentShaderBarycentricFeaturesNV                  const *
    ) noexcept -> Type ( PhysicalDeviceFragmentShaderBarycentricFeaturesNVidia ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADER_BARYCENTRIC_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceFragmentShaderBarycentricFeaturesNV                       *,
            Type ( PhysicalDeviceFragmentShaderBarycentricFeaturesNVidia )      const *
    ) noexcept -> VkPhysicalDeviceFragmentShaderBarycentricFeaturesNV *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceFragmentShadingRateEnumsFeaturesNVidia )             *,
            VkPhysicalDeviceFragmentShadingRateEnumsFeaturesNV                  const *
    ) noexcept -> Type ( PhysicalDeviceFragmentShadingRateEnumsFeaturesNVidia ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceFragmentShadingRateEnumsFeaturesNV                       *,
            Type ( PhysicalDeviceFragmentShadingRateEnumsFeaturesNVidia )      const *
    ) noexcept -> VkPhysicalDeviceFragmentShadingRateEnumsFeaturesNV *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_INHERITED_VIEWPORT_SCISSOR_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceInheritedViewportScissorFeaturesNVidia )             *,
            VkPhysicalDeviceInheritedViewportScissorFeaturesNV                  const *
    ) noexcept -> Type ( PhysicalDeviceInheritedViewportScissorFeaturesNVidia ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_INHERITED_VIEWPORT_SCISSOR_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceInheritedViewportScissorFeaturesNV                       *,
            Type ( PhysicalDeviceInheritedViewportScissorFeaturesNVidia )      const *
    ) noexcept -> VkPhysicalDeviceInheritedViewportScissorFeaturesNV *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_LINEAR_COLOR_ATTACHMENT_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceLinearColorAttachmentFeaturesNVidia )             *,
            VkPhysicalDeviceLinearColorAttachmentFeaturesNV                  const *
    ) noexcept -> Type ( PhysicalDeviceLinearColorAttachmentFeaturesNVidia ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_LINEAR_COLOR_ATTACHMENT_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceLinearColorAttachmentFeaturesNV                       *,
            Type ( PhysicalDeviceLinearColorAttachmentFeaturesNVidia )      const *
    ) noexcept -> VkPhysicalDeviceLinearColorAttachmentFeaturesNV *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceMeshShaderFeaturesNVidia )             *,
            VkPhysicalDeviceMeshShaderFeaturesNV                  const *
    ) noexcept -> Type ( PhysicalDeviceMeshShaderFeaturesNVidia ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceMeshShaderFeaturesNV                       *,
            Type ( PhysicalDeviceMeshShaderFeaturesNVidia )      const *
    ) noexcept -> VkPhysicalDeviceMeshShaderFeaturesNV *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceRayTracingMotionBlurFeaturesNVidia )             *,
            VkPhysicalDeviceRayTracingMotionBlurFeaturesNV                  const *
    ) noexcept -> Type ( PhysicalDeviceRayTracingMotionBlurFeaturesNVidia ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceRayTracingMotionBlurFeaturesNV                       *,
            Type ( PhysicalDeviceRayTracingMotionBlurFeaturesNVidia )      const *
    ) noexcept -> VkPhysicalDeviceRayTracingMotionBlurFeaturesNV *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_REPRESENTATIVE_FRAGMENT_TEST_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceRepresentativeFragmentTestFeaturesNVidia )             *,
            VkPhysicalDeviceRepresentativeFragmentTestFeaturesNV                  const *
    ) noexcept -> Type ( PhysicalDeviceRepresentativeFragmentTestFeaturesNVidia ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_REPRESENTATIVE_FRAGMENT_TEST_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceRepresentativeFragmentTestFeaturesNV                       *,
            Type ( PhysicalDeviceRepresentativeFragmentTestFeaturesNVidia )      const *
    ) noexcept -> VkPhysicalDeviceRepresentativeFragmentTestFeaturesNV *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_IMAGE_FOOTPRINT_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceShaderImageFootprintFeaturesNVidia )             *,
            VkPhysicalDeviceShaderImageFootprintFeaturesNV                  const *
    ) noexcept -> Type ( PhysicalDeviceShaderImageFootprintFeaturesNVidia ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_IMAGE_FOOTPRINT_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceShaderImageFootprintFeaturesNV                       *,
            Type ( PhysicalDeviceShaderImageFootprintFeaturesNVidia )      const *
    ) noexcept -> VkPhysicalDeviceShaderImageFootprintFeaturesNV *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceShaderSMBuiltinsFeaturesNVidia )             *,
            VkPhysicalDeviceShaderSMBuiltinsFeaturesNV                  const *
    ) noexcept -> Type ( PhysicalDeviceShaderSMBuiltinsFeaturesNVidia ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceShaderSMBuiltinsFeaturesNV                       *,
            Type ( PhysicalDeviceShaderSMBuiltinsFeaturesNVidia )      const *
    ) noexcept -> VkPhysicalDeviceShaderSMBuiltinsFeaturesNV *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceShadingRateImageFeaturesNVidia )             *,
            VkPhysicalDeviceShadingRateImageFeaturesNV                  const *
    ) noexcept -> Type ( PhysicalDeviceShadingRateImageFeaturesNVidia ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceShadingRateImageFeaturesNV                       *,
            Type ( PhysicalDeviceShadingRateImageFeaturesNVidia )      const *
    ) noexcept -> VkPhysicalDeviceShadingRateImageFeaturesNV *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_DEVICE_COHERENT_MEMORY_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceCoherentMemoryFeaturesAMD )                 *,
            VkPhysicalDeviceCoherentMemoryFeaturesAMD                  const *
    ) noexcept -> Type ( PhysicalDeviceCoherentMemoryFeaturesAMD ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_DEVICE_COHERENT_MEMORY_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceCoherentMemoryFeaturesAMD                   *,
            Type ( PhysicalDeviceCoherentMemoryFeaturesAMD )      const *
    ) noexcept -> VkPhysicalDeviceCoherentMemoryFeaturesAMD *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceFragmentDensityMapOffsetFeaturesQualcomm )             *,
            VkPhysicalDeviceFragmentDensityMapOffsetFeaturesQCOM                  const *
    ) noexcept -> Type ( PhysicalDeviceFragmentDensityMapOffsetFeaturesQualcomm ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceFragmentDensityMapOffsetFeaturesQCOM                       *,
            Type ( PhysicalDeviceFragmentDensityMapOffsetFeaturesQualcomm )      const *
    ) noexcept -> VkPhysicalDeviceFragmentDensityMapOffsetFeaturesQCOM *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceSubpassShadingFeaturesHuawei )                 *,
            VkPhysicalDeviceSubpassShadingFeaturesHUAWEI                  const *
    ) noexcept -> Type ( PhysicalDeviceSubpassShadingFeaturesHuawei ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceSubpassShadingFeaturesHUAWEI                   *,
            Type ( PhysicalDeviceSubpassShadingFeaturesHuawei )      const *
    ) noexcept -> VkPhysicalDeviceSubpassShadingFeaturesHUAWEI *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_INVOCATION_MASK_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceInvocationMaskFeaturesHuawei )                 *,
            VkPhysicalDeviceInvocationMaskFeaturesHUAWEI                  const *
    ) noexcept -> Type ( PhysicalDeviceInvocationMaskFeaturesHuawei ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_INVOCATION_MASK_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceInvocationMaskFeaturesHUAWEI                   *,
            Type ( PhysicalDeviceInvocationMaskFeaturesHuawei )      const *
    ) noexcept -> VkPhysicalDeviceInvocationMaskFeaturesHUAWEI *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceMutableDescriptorTypeFeaturesValve )                 *,
            VkPhysicalDeviceMutableDescriptorTypeFeaturesVALVE                  const *
    ) noexcept -> Type ( PhysicalDeviceMutableDescriptorTypeFeaturesValve ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceMutableDescriptorTypeFeaturesVALVE                   *,
            Type ( PhysicalDeviceMutableDescriptorTypeFeaturesValve )      const *
    ) noexcept -> VkPhysicalDeviceMutableDescriptorTypeFeaturesVALVE *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_SHADER_INTEGER_FUNCTIONS_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceShaderIntegerFunctionsFeaturesIntel )                  *,
            VkPhysicalDeviceShaderIntegerFunctions2FeaturesINTEL                  const *
    ) noexcept -> Type ( PhysicalDeviceShaderIntegerFunctionsFeaturesIntel ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_SHADER_INTEGER_FUNCTIONS_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceShaderIntegerFunctions2FeaturesINTEL                  *,
            Type ( PhysicalDeviceShaderIntegerFunctionsFeaturesIntel )      const *
    ) noexcept -> VkPhysicalDeviceShaderIntegerFunctions2FeaturesINTEL *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_ARM_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM )                 *,
            VkPhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM                  const *
    ) noexcept -> Type ( PhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_ARM_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_AVAILABLE
    extern auto toVulkanFormat (
            VkPhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM                   *,
            Type ( PhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM )      const *
    ) noexcept -> VkPhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto toVulkanFormat (
            VkDeviceCreateInfo                *,
            Type ( DeviceCreateInfo )   const *
    ) noexcept -> VkDeviceCreateInfo *;

    extern auto featureToVulkanFormat (
            VkBaseOutStructure                *,
            Type ( GenericInStructure ) const *,
            DeviceFeaturesContext             *
    ) noexcept -> void;

    extern auto toVulkanFormat (
            VkDeviceQueueCreateInfo                         *,
            vulkan :: Type ( DeviceQueueCreateInfo )  const *
    ) noexcept -> void;

    extern auto prepareContext (
            CreateDeviceContext             *,
            Type ( DeviceCreateInfo ) const *
    ) noexcept -> VkDeviceCreateInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto prepareContext (
            GetPhysicalDevicePropertiesContext                *,
            Type ( PhysicalDeviceExtendedProperties )   const *
    ) noexcept -> VkPhysicalDeviceProperties2 *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto extractContext (
            Type ( PhysicalDeviceExtendedProperties )       *,
            GetPhysicalDevicePropertiesContext        const *
    ) noexcept -> void;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto prepareContext (
            GetPhysicalDeviceFeaturesContext                *,
            Type ( PhysicalDeviceExtendedFeatures )   const *
    ) noexcept -> VkPhysicalDeviceFeatures2 *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto extractContext (
            Type ( PhysicalDeviceExtendedFeatures )       *,
            GetPhysicalDeviceFeaturesContext        const *
    ) noexcept -> void;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto createChain (
            vulkan :: Type ( PhysicalDeviceDetails )            *,
            vulkan :: Type ( PhysicalDeviceExtendedProperties ) *,
            vulkan :: Type ( PhysicalDeviceExtendedFeatures )   *
    ) noexcept -> void;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( QueueFamilyProperties )        *,
            VkQueueFamilyProperties         const *
    ) noexcept -> Type ( QueueFamilyProperties ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto prepareContext (
            GetPhysicalDeviceQueueFamilyPropertiesContext         *,
            cds :: uint32,
            Type ( QueueFamilyExtendedProperties )          const *
    ) noexcept -> VkQueueFamilyProperties2 *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( QueueFamilyExtendedProperties )        *,
            VkQueueFamilyProperties2                const *
    ) noexcept -> Type ( QueueFamilyExtendedProperties ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTIC_CHECKPOINTS_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( QueueFamilyCheckpointPropertiesNVidia )        *,
            VkQueueFamilyCheckpointPropertiesNV             const *
    ) noexcept -> Type ( QueueFamilyCheckpointPropertiesNVidia ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( QueueFamilyGlobalPriorityProperties )        *,
            VkQueueFamilyGlobalPriorityPropertiesEXT      const *
    ) noexcept -> Type ( QueueFamilyGlobalPriorityProperties ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( QueueFamilyQueryResultStatusProperties )        *,
            VkQueueFamilyQueryResultStatusPropertiesKHR      const *
    ) noexcept -> Type ( QueueFamilyQueryResultStatusProperties ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( VideoQueueFamilyProperties )        *,
            VkVideoQueueFamilyPropertiesKHR      const *
    ) noexcept -> Type ( VideoQueueFamilyProperties ) *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto extractContext (
            cds :: uint32,
            Type ( QueueFamilyExtendedProperties )              *,
            GetPhysicalDeviceQueueFamilyPropertiesContext const *
    ) noexcept -> void;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto createChain (
            cds :: uint32,
            vulkan :: Type ( QueueFamilyDetails )             *,
            vulkan :: Type ( QueueFamilyExtendedProperties )  *
    ) noexcept -> void;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto toVulkanFormat (
            VkDeviceQueueInfo2                *,
            Type ( DeviceQueueInfo )    const *
    ) noexcept -> VkDeviceQueueInfo2 *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( SurfaceCapabilities )      *,
            VkSurfaceCapabilitiesKHR    const *
    ) noexcept -> Type ( SurfaceCapabilities ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( SurfaceFormat )      *,
            VkSurfaceFormatKHR    const *
    ) noexcept -> Type ( SurfaceFormat ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISPLAY_SURFACE_COUNTER_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( SurfaceCapabilities2 )      *,
            VkSurfaceCapabilities2EXT    const *
    ) noexcept -> Type ( SurfaceCapabilities2 ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_GET_SURFACE_CAPABILITIES_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( SurfaceFormat2 )      *,
            VkSurfaceFormat2KHR    const *
    ) noexcept -> Type ( SurfaceFormat2 ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FULL_SCREEN_EXCLUSIVE_AVAILABLE
    extern auto toVulkanFormat (
        VkSurfaceFullScreenExclusiveInfoEXT           *,
        Type ( SurfaceFullScreenExclusiveInfo ) const *
    ) noexcept -> VkSurfaceFullScreenExclusiveInfoEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_GET_SURFACE_CAPABILITIES_AVAILABLE
    extern auto prepareContext (
            GetSurfaceContext                         *,
            Type ( PhysicalDeviceSurfaceInfo )  const *
    ) noexcept -> VkPhysicalDeviceSurfaceInfo2KHR *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE
    extern auto toVulkanFormat (
            VkSwapchainCreateInfoKHR              *,
            Type ( SwapChainCreateInfo )    const *
    ) noexcept -> VkSwapchainCreateInfoKHR *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto toVulkanFormat (
            VkImageFormatListCreateInfo                 *,
            Type ( ImageFormatListCreateInfo )    const *
    ) noexcept -> VkImageFormatListCreateInfo *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WIN32_SURFACE_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_FULL_SCREEN_EXCLUSIVE_AVAILABLE
    extern auto toVulkanFormat (
            VkSurfaceFullScreenExclusiveWin32InfoEXT              *,
            Type ( SurfaceFullScreenExclusiveWin32Info )    const *
    ) noexcept -> VkSurfaceFullScreenExclusiveWin32InfoEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE
    extern auto prepareContext (
            CreateSwapChainContext                *,
            Type ( SwapChainCreateInfo )    const *
    ) noexcept -> VkSwapchainCreateInfoKHR *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto toVulkanFormat (
            VkImageViewCreateInfo                 *,
            Type ( ImageViewCreateInfo )    const *
    ) noexcept -> VkImageViewCreateInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto toVulkanFormat (
            VkImageViewUsageCreateInfo                 *,
            Type ( ImageViewUsageCreateInfo )    const *
    ) noexcept -> VkImageViewUsageCreateInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto toVulkanFormat (
            VkSamplerYcbcrConversionInfo                 *,
            Type ( SamplerYCBCRConversionInfo )    const *
    ) noexcept -> VkSamplerYcbcrConversionInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto prepareContext (
            CreateImageViewContext                *,
            Type ( ImageViewCreateInfo )    const *
    ) noexcept -> VkImageViewCreateInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto toVulkanFormat (
            VkCommandPoolCreateInfo                 *,
            Type ( CommandPoolCreateInfo )    const *
    ) noexcept -> VkCommandPoolCreateInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto toVulkanFormat (
            VkCommandBufferAllocateInfo                 *,
            Type ( CommandBufferAllocateInfo )    const *
    ) noexcept -> VkCommandBufferAllocateInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto toVulkanFormat (
            VkCommandBufferBeginInfo                 *,
            Type ( CommandBufferBeginInfo )    const *
    ) noexcept -> VkCommandBufferBeginInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto toVulkanFormat (
            VkCommandBufferInheritanceInfo                 *,
            Type ( CommandBufferInheritanceInfo )    const *
    ) noexcept -> VkCommandBufferInheritanceInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto toVulkanFormat (
            VkDeviceGroupCommandBufferBeginInfo                 *,
            Type ( DeviceGroupCommandBufferBeginInfo )    const *
    ) noexcept -> VkDeviceGroupCommandBufferBeginInfo *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
    extern auto toVulkanFormat (
            VkCommandBufferInheritanceRenderingInfo_t               *,
            Type ( CommandBufferInheritanceRenderingInfo )    const *
    ) noexcept -> VkCommandBufferInheritanceRenderingInfo_t *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_AMD_MIXED_ATTACHMENT_SAMPLES_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAMEBUFFER_MIXED_SAMPLES_AVAILABLE
    extern auto toVulkanFormat (
            VkAttachmentSampleCountInfoAMD                           *,
            vulkan :: hidden :: __AttachmentSampleCountInfo    const *
    ) noexcept -> VkAttachmentSampleCountInfoAMD *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE
    extern auto toVulkanFormat (
            VkMultiviewPerViewAttributesInfoNVX                   *,
            Type ( MultiviewPerViewAttributesInfoNVidia )   const *
    ) noexcept -> VkMultiviewPerViewAttributesInfoNVX *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE
    extern auto toVulkanFormat (
            VkCommandBufferInheritanceConditionalRenderingInfoEXT             *,
            Type ( CommandBufferInheritanceConditionalRenderingInfo )   const *
    ) noexcept -> VkCommandBufferInheritanceConditionalRenderingInfoEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_RENDER_PASS_TRANSFORM_AVAILABLE
    extern auto toVulkanFormat (
            VkCommandBufferInheritanceRenderPassTransformInfoQCOM                    *,
            Type ( CommandBufferInheritanceRenderPassTransformInfoQualcomm )   const *
    ) noexcept -> VkCommandBufferInheritanceRenderPassTransformInfoQCOM *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto toVulkanFormat (
            VkViewport                *,
            Type ( Viewport )   const *
    ) noexcept -> VkViewport *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_INHERITED_VIEWPORT_SCISSOR_AVAILABLE
    extern auto toVulkanFormat (
            VkCommandBufferInheritanceViewportScissorInfoNV                    *,
            Type ( CommandBufferInheritanceViewportScissorInfoNVidia )   const *
    ) noexcept -> VkCommandBufferInheritanceViewportScissorInfoNV *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto prepareContext (
            BeginCommandBufferContext             *,
            Type ( CommandBufferBeginInfo ) const *
    ) noexcept -> VkCommandBufferBeginInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto toVulkanFormat (
            VkDeviceGroupSubmitInfo               *,
            Type ( DeviceGroupSubmitInfo )  const *
    ) noexcept -> VkDeviceGroupSubmitInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto toVulkanFormat (
            VkProtectedSubmitInfo               *,
            Type ( ProtectedSubmitInfo )  const *
    ) noexcept -> VkProtectedSubmitInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto toVulkanFormat (
            VkTimelineSemaphoreSubmitInfo               *,
            Type ( TimelineSemaphoreSubmitInfo )  const *
    ) noexcept -> VkTimelineSemaphoreSubmitInfo *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
    extern auto toVulkanFormat (
            VkPerformanceQuerySubmitInfoKHR            *,
            Type ( PerformanceQuerySubmitInfo )  const *
    ) noexcept -> VkPerformanceQuerySubmitInfoKHR *;
#endif

#if VK_STRUCTURE_TYPE_PERFORMANCE_QUERY_SUBMIT_INFO_KHR
    extern auto toVulkanFormat (
            VkWin32KeyedMutexAcquireReleaseInfoKHR            *,
            Type ( Win32KeyedMutexAcquireReleaseInfo )  const *
    ) noexcept -> VkWin32KeyedMutexAcquireReleaseInfoKHR *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_WIN32_KEYED_MUTEX_AVAILABLE
    extern auto toVulkanFormat (
            VkWin32KeyedMutexAcquireReleaseInfoNV                   *,
            Type ( Win32KeyedMutexAcquireReleaseInfoNVidia )  const *
    ) noexcept -> VkWin32KeyedMutexAcquireReleaseInfoNV *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_WIN32_AVAILABLE
    extern auto toVulkanFormat (
            VkD3D12FenceSubmitInfoKHR               *,
            Type ( D3D12FenceSubmitInfo )     const *
    ) noexcept -> VkTimelineSemaphoreSubmitInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto toVulkanFormat (
            VkSubmitInfo              *,
            Type ( SubmitInfo ) const *
    ) noexcept -> VkSubmitInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto prepareContext (
            SubmitQueueContext        *,
            cds :: uint32,
            Type ( SubmitInfo ) const *
    ) noexcept -> VkSubmitInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
    extern auto toVulkanFormat (
            VkSubmitInfo2_t            *,
            Type ( SubmitInfo2 ) const *
    ) noexcept -> VkSubmitInfo2_t *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
    extern auto toVulkanFormat (
            VkSemaphoreSubmitInfo_t            *,
            Type ( SemaphoreSubmitInfo ) const *
    ) noexcept -> VkSemaphoreSubmitInfo_t *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
    extern auto toVulkanFormat (
            VkCommandBufferSubmitInfo_t            *,
            Type ( CommandBufferSubmitInfo ) const *
    ) noexcept -> VkCommandBufferSubmitInfo_t *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
    extern auto prepareContext (
            SubmitQueueContext            *,
            cds :: uint32,
            Type ( SubmitInfo2 )    const *
    ) noexcept -> VkSubmitInfo2_t *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto toVulkanFormat (
            VkFenceCreateInfo              *,
            Type ( FenceCreateInfo ) const *
    ) noexcept -> VkFenceCreateInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto toVulkanFormat (
            VkExportFenceCreateInfo              *,
            Type ( ExportFenceCreateInfo ) const *
    ) noexcept -> VkExportFenceCreateInfo *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_WIN32_AVAILABLE
    extern auto toVulkanFormat (
            VkExportFenceWin32HandleInfoKHR           *,
            Type ( ExportFenceWin32HandleInfo ) const *
    ) noexcept -> VkExportFenceWin32HandleInfoKHR *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto prepareContext (
            CreateFenceContext                *,
            Type ( FenceCreateInfo )    const *
    ) noexcept -> VkFenceCreateInfo *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_WIN32_AVAILABLE
    extern auto toVulkanFormat (
            VkFenceGetWin32HandleInfoKHR           *,
            Type ( FenceGetWin32HandleInfo ) const *
    ) noexcept -> VkFenceGetWin32HandleInfoKHR *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_FD_AVAILABLE
    extern auto toVulkanFormat (
            VkFenceGetFdInfoKHR           *,
            Type ( FenceGetFDInfo ) const *
    ) noexcept -> VkFenceGetFdInfoKHR *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISPLAY_CONTROL_AVAILABLE
    extern auto toVulkanFormat (
            VkDeviceEventInfoEXT              *,
            Type ( DeviceEventInfo )    const *
    ) noexcept -> VkDeviceEventInfoEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISPLAY_CONTROL_AVAILABLE
    extern auto toVulkanFormat (
            VkDisplayEventInfoEXT              *,
            Type ( DisplayEventInfo )    const *
    ) noexcept -> VkDisplayEventInfoEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_WIN32_AVAILABLE
    extern auto toVulkanFormat (
            VkImportFenceWin32HandleInfoKHR              *,
            Type ( ImportFenceWin32HandleInfo )    const *
    ) noexcept -> VkImportFenceWin32HandleInfoKHR *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_FD_AVAILABLE
    extern auto toVulkanFormat (
            VkImportFenceFdInfoKHR              *,
            Type ( ImportFenceFdInfo )    const *
    ) noexcept -> VkImportFenceFdInfoKHR *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto prepareContext (
            CreateSemaphoreContext                *,
            Type ( SemaphoreCreateInfo )    const *
    ) noexcept -> VkSemaphoreCreateInfo *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_WIN32_AVAILABLE
    extern auto toVulkanFormat (
            VkSemaphoreGetWin32HandleInfoKHR              *,
            Type ( SemaphoreGetWin32HandleInfo )    const *
    ) noexcept -> VkSemaphoreGetWin32HandleInfoKHR *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_FD_AVAILABLE
    extern auto toVulkanFormat (
            VkSemaphoreGetFdInfoKHR              *,
            Type ( SemaphoreGetFdInfo )    const *
    ) noexcept -> VkSemaphoreGetFdInfoKHR *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_SEMAPHORE_AVAILABLE
    extern auto toVulkanFormat (
            VkSemaphoreGetZirconHandleInfoFUCHSIA                *,
            Type ( SemaphoreGetZirconHandleInfoGoogle )    const *
    ) noexcept -> VkSemaphoreGetZirconHandleInfoFUCHSIA *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto prepareContext (
            WaitSemaphoreContext                *,
            Type ( SemaphoreWaitInfo )    const *
    ) noexcept -> VkSemaphoreWaitInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto toVulkanFormat (
            VkSemaphoreSignalInfo                 *,
            Type ( SemaphoreSignalInfo )    const *
    ) noexcept -> VkSemaphoreSignalInfo *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_WIN32_AVAILABLE
    extern auto toVulkanFormat (
            VkImportSemaphoreWin32HandleInfoKHR              *,
            Type ( ImportSemaphoreWin32HandleInfo )    const *
    ) noexcept -> VkImportSemaphoreWin32HandleInfoKHR *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_FD_AVAILABLE
    extern auto toVulkanFormat (
            VkImportSemaphoreFdInfoKHR              *,
            Type ( ImportSemaphoreFdInfo )    const *
    ) noexcept -> VkImportSemaphoreFdInfoKHR *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_SEMAPHORE_AVAILABLE
    extern auto toVulkanFormat (
            VkImportSemaphoreZirconHandleInfoFUCHSIA                *,
            Type ( ImportSemaphoreZirconHandleInfoGoogle )    const *
    ) noexcept -> VkImportSemaphoreZirconHandleInfoFUCHSIA *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto toVulkanFormat (
            VkEventCreateInfo                 *,
            Type ( EventCreateInfo )    const *
    ) noexcept -> VkEventCreateInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
    extern auto prepareContext (
            SetCommandBufferEventContext     *,
            Type ( DependencyInfo )    const *
    ) noexcept -> VkDependencyInfo_t *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
    extern auto prepareContext (
            WaitCommandBufferEvent2Context   *,
            cds :: uint32,
            Type ( DependencyInfo )    const *
    ) noexcept -> VkDependencyInfo_t *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto prepareContext (
            WaitCommandBufferEventContext         *,
            cds :: uint32,
            Type ( MemoryBarrier )          const *
    ) noexcept -> VkMemoryBarrier *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto prepareContext (
            WaitCommandBufferEventContext         *,
            cds :: uint32,
            Type ( BufferMemoryBarrier )          const *
    ) noexcept -> VkBufferMemoryBarrier *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto prepareContext (
            WaitCommandBufferEventContext         *,
            cds :: uint32,
            Type ( ImageMemoryBarrier )          const *
    ) noexcept -> VkImageMemoryBarrier *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE
    extern auto prepareContext (
            BeginCommandBufferRenderingContext        *,
            Type ( RenderingInfo )              const *
    ) noexcept -> VkRenderingInfo_t *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto prepareContext (
            CreateRenderPassContext               *,
            Type ( RenderPassCreateInfo )   const *
    ) noexcept -> VkRenderPassCreateInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto toVulkanFormat (
            VkRenderPassCreateInfo              *,
            Type ( RenderPassCreateInfo ) const *
    ) noexcept -> VkRenderPassCreateInfo *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE
    extern auto toVulkanFormat (
            VkRenderPassFragmentDensityMapCreateInfoEXT           *,
            Type ( RenderPassFragmentDensityMapCreateInfo ) const *
    ) noexcept -> VkRenderPassFragmentDensityMapCreateInfoEXT *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto toVulkanFormat (
            VkRenderPassInputAttachmentAspectCreateInfo              *,
            Type ( RenderPassInputAttachmentAspectCreateInfo ) const *
    ) noexcept -> VkRenderPassInputAttachmentAspectCreateInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto toVulkanFormat (
            VkInputAttachmentAspectReference              *,
            Type ( InputAttachmentAspectReference ) const *
    ) noexcept -> VkInputAttachmentAspectReference *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto toVulkanFormat (
            VkRenderPassMultiviewCreateInfo              *,
            Type ( RenderPassMultiviewCreateInfo ) const *
    ) noexcept -> VkRenderPassMultiviewCreateInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto toVulkanFormat (
            VkAttachmentDescription              *,
            Type ( AttachmentDescription ) const *
    ) noexcept -> VkAttachmentDescription *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto toVulkanFormat (
            VkSubpassDescription              *,
            Type ( SubpassDescription ) const *
    ) noexcept -> VkSubpassDescription *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto toVulkanFormat (
            VkSubpassDependency              *,
            Type ( SubpassDependency ) const *
    ) noexcept -> VkSubpassDependency *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto toVulkanFormat (
            VkAttachmentReference              *,
            Type ( AttachmentReference ) const *
    ) noexcept -> VkAttachmentReference *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto prepareContext (
            CreateRenderPass2Context              *,
            Type ( RenderPassCreateInfo2 )  const *
    ) noexcept -> VkRenderPassCreateInfo2 *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto toVulkanFormat (
            VkRenderPassCreateInfo2              *,
            Type ( RenderPassCreateInfo2 ) const *
    ) noexcept -> VkRenderPassCreateInfo2 *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto toVulkanFormat (
            VkAttachmentDescription2              *,
            Type ( AttachmentDescription2 ) const *
    ) noexcept -> VkAttachmentDescription2 *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto toVulkanFormat (
            VkAttachmentDescriptionStencilLayout              *,
            Type ( AttachmentDescriptionStencilLayout ) const *
    ) noexcept -> VkAttachmentDescriptionStencilLayout *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto toVulkanFormat (
            VkSubpassDescription2              *,
            Type ( SubpassDescription2 ) const *
    ) noexcept -> VkSubpassDescription2 *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE
    extern auto toVulkanFormat (
            VkFragmentShadingRateAttachmentInfoKHR           *,
            Type ( FragmentShadingRateAttachmentInfo ) const *
    ) noexcept -> VkFragmentShadingRateAttachmentInfoKHR *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto toVulkanFormat (
            VkAttachmentReference2              *,
            Type ( AttachmentReference2 ) const *
    ) noexcept -> VkAttachmentReference2 *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto toVulkanFormat (
            VkSubpassDescriptionDepthStencilResolve              *,
            Type ( SubpassDescriptionDepthStencilResolve ) const *
    ) noexcept -> VkSubpassDescriptionDepthStencilResolve *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto toVulkanFormat (
            VkAttachmentReferenceStencilLayout              *,
            Type ( AttachmentReferenceStencilLayout ) const *
    ) noexcept -> VkAttachmentReferenceStencilLayout *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto toVulkanFormat (
            VkSubpassDependency2              *,
            Type ( SubpassDependency2 ) const *
    ) noexcept -> VkSubpassDependency2 *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto prepareContext (
            CreateFrameBufferContext               *,
            Type ( FrameBufferCreateInfo )   const *
    ) noexcept -> VkFramebufferCreateInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto toVulkanFormat (
            VkFramebufferCreateInfo              *,
            Type ( FrameBufferCreateInfo ) const *
    ) noexcept -> VkFramebufferCreateInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto toVulkanFormat (
            VkFramebufferAttachmentsCreateInfo              *,
            Type ( FrameBufferAttachmentsCreateInfo ) const *
    ) noexcept -> VkFramebufferAttachmentsCreateInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto toVulkanFormat (
            VkFramebufferAttachmentImageInfo              *,
            Type ( FrameBufferAttachmentImageInfo ) const *
    ) noexcept -> VkFramebufferAttachmentImageInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto prepareContext (
            BeginRenderPassContext               *,
            Type ( RenderPassBeginInfo )   const *
    ) noexcept -> VkRenderPassBeginInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto toVulkanFormat (
            VkRenderPassBeginInfo              *,
            Type ( RenderPassBeginInfo ) const *
    ) noexcept -> VkRenderPassBeginInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto toVulkanFormat (
            VkRenderPassAttachmentBeginInfo              *,
            Type ( RenderPassAttachmentBeginInfo ) const *
    ) noexcept -> VkRenderPassAttachmentBeginInfo *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE
    extern auto toVulkanFormat (
            VkRenderPassSampleLocationsBeginInfoEXT           *,
            Type ( RenderPassSampleLocationsBeginInfo ) const *
    ) noexcept -> VkRenderPassSampleLocationsBeginInfoEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE
    extern auto toVulkanFormat (
            VkAttachmentSampleLocationsEXT           *,
            Type ( AttachmentSampleLocations ) const *
    ) noexcept -> VkAttachmentSampleLocationsEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE
    extern auto toVulkanFormat (
            VkSubpassSampleLocationsEXT           *,
            Type ( SubpassSampleLocations ) const *
    ) noexcept -> VkSubpassSampleLocationsEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_RENDER_PASS_TRANSFORM_AVAILABLE
    extern auto toVulkanFormat (
            VkRenderPassTransformBeginInfoQCOM                  *,
            Type ( RenderPassTransformBeginInfoQualcomm ) const *
    ) noexcept -> VkRenderPassTransformBeginInfoQCOM *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto prepareContext (
            BeginRenderPassContext               *,
            Type ( SubpassBeginInfo )      const *
    ) noexcept -> VkSubpassBeginInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto toVulkanFormat (
            VkSubpassBeginInfo              *,
            Type ( SubpassBeginInfo ) const *
    ) noexcept -> VkSubpassBeginInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto prepareContext (
            NextSubpassContext                   *,
            Type ( SubpassBeginInfo )      const *
    ) noexcept -> VkSubpassBeginInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto prepareContext (
            NextSubpassContext                   *,
            Type ( SubpassEndInfo )        const *
    ) noexcept -> VkSubpassEndInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    extern auto toVulkanFormat (
            VkSubpassEndInfo              *,
            Type ( SubpassEndInfo ) const *
    ) noexcept -> VkSubpassEndInfo *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE
    extern auto toVulkanFormat (
            VkSubpassFragmentDensityMapOffsetEndInfoQCOM                  *,
            Type ( SubpassFragmentDensityMapOffsetEndInfoQualcomm ) const *
    ) noexcept -> VkSubpassFragmentDensityMapOffsetEndInfoQCOM *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto prepareContext (
            CreateShaderModuleContext             *,
            Type ( ShaderModuleCreateInfo ) const *
    ) noexcept -> VkShaderModuleCreateInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto toVulkanFormat (
            VkShaderModuleCreateInfo              *,
            Type ( ShaderModuleCreateInfo ) const *
    ) noexcept -> VkShaderModuleCreateInfo *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_CACHE_AVAILABLE
    extern auto toVulkanFormat (
            VkShaderModuleValidationCacheCreateInfoEXT           *,
            Type ( ShaderModuleValidationCacheCreateInfo ) const *
    ) noexcept -> VkShaderModuleValidationCacheCreateInfoEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( CooperativeMatrixPropertiesNVidia )        *,
            VkCooperativeMatrixPropertiesNV             const *
    ) noexcept -> Type ( CooperativeMatrixPropertiesNVidia ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_CACHE_AVAILABLE
    extern auto toVulkanFormat (
            VkValidationCacheCreateInfoEXT           *,
            Type ( ValidationCacheCreateInfo ) const *
    ) noexcept -> VkValidationCacheCreateInfoEXT *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto prepareContext (
            CreateComputePipelineContext             *,
            cds :: uint32,
            Type ( ComputePipelineCreateInfo ) const *
    ) noexcept -> VkComputePipelineCreateInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto extractContext (
            cds :: uint32,
            Type ( ComputePipelineCreateInfo )  const *,
            CreateComputePipelineContext        const *
    ) noexcept -> void;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto toVulkanFormat (
            VkComputePipelineCreateInfo              *,
            Type ( ComputePipelineCreateInfo ) const *
    ) noexcept -> VkComputePipelineCreateInfo *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_PIPELINE_COMPILER_CONTROL_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineCompilerControlCreateInfoAMD              *,
            Type ( PipelineCompilerControlCreateInfoAMD ) const *
    ) noexcept -> VkPipelineCompilerControlCreateInfoAMD *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_FEEDBACK_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineCreationFeedbackCreateInfo_t            *,
            Type ( PipelineCreationFeedbackCreateInfo ) const *
    ) noexcept -> VkPipelineCreationFeedbackCreateInfo_t *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_FEEDBACK_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineCreationFeedback_t            *,
            Type ( PipelineCreationFeedback ) const *
    ) noexcept -> VkPipelineCreationFeedback_t *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_FEEDBACK_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PipelineCreationFeedback )       *,
            VkPipelineCreationFeedback_t      const *
    ) noexcept -> Type ( PipelineCreationFeedback ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE
    extern auto toVulkanFormat (
            VkSubpassShadingPipelineCreateInfoHUAWEI              *,
            Type ( SubpassShadingPipelineCreateInfoHuawei ) const *
    ) noexcept -> VkSubpassShadingPipelineCreateInfoHUAWEI *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineShaderStageCreateInfo              *,
            Type ( PipelineShaderStageCreateInfo ) const *
    ) noexcept -> VkPipelineShaderStageCreateInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineShaderStageRequiredSubgroupSizeCreateInfo_t            *,
            Type ( PipelineShaderStageRequiredSubgroupSizeCreateInfo ) const *
    ) noexcept -> VkPipelineShaderStageRequiredSubgroupSizeCreateInfo_t *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto toVulkanFormat (
            VkSpecializationInfo              *,
            Type ( SpecializationInfo ) const *
    ) noexcept -> VkSpecializationInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto toVulkanFormat (
            VkSpecializationMapEntry              *,
            Type ( SpecializationMapEntry ) const *
    ) noexcept -> VkSpecializationMapEntry *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto prepareContext (
            CreateGraphicsPipelineContext             *,
            cds :: uint32,
            Type ( GraphicsPipelineCreateInfo ) const *
    ) noexcept -> VkGraphicsPipelineCreateInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto extractContext (
            cds :: uint32,
            Type ( GraphicsPipelineCreateInfo )  const *,
            CreateGraphicsPipelineContext        const *
    ) noexcept -> void;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto toVulkanFormat (
            VkGraphicsPipelineCreateInfo              *,
            Type ( GraphicsPipelineCreateInfo ) const *
    ) noexcept -> VkGraphicsPipelineCreateInfo *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE
    extern auto toVulkanFormat (
            VkGraphicsPipelineShaderGroupsCreateInfoNV                  *,
            Type ( GraphicsPipelineShaderGroupsCreateInfoNVidia ) const *
    ) noexcept -> VkGraphicsPipelineShaderGroupsCreateInfoNV *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE
    extern auto toVulkanFormat (
            VkGraphicsShaderGroupCreateInfoNV                  *,
            Type ( GraphicsShaderGroupCreateInfoNVidia ) const *
    ) noexcept -> VkGraphicsShaderGroupCreateInfoNV *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineVertexInputStateCreateInfo              *,
            Type ( PipelineVertexInputStateCreateInfo ) const *
    ) noexcept -> VkPipelineVertexInputStateCreateInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto toVulkanFormat (
            VkVertexInputBindingDescription              *,
            Type ( VertexInputBindingDescription ) const *
    ) noexcept -> VkVertexInputBindingDescription *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto toVulkanFormat (
            VkVertexInputAttributeDescription              *,
            Type ( VertexInputAttributeDescription ) const *
    ) noexcept -> VkVertexInputAttributeDescription *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineVertexInputDivisorStateCreateInfoEXT           *,
            Type ( PipelineVertexInputDivisorStateCreateInfo ) const *
    ) noexcept -> VkPipelineVertexInputDivisorStateCreateInfoEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE
    extern auto toVulkanFormat (
            VkVertexInputBindingDivisorDescriptionEXT           *,
            Type ( VertexInputBindingDivisorDescription ) const *
    ) noexcept -> VkVertexInputBindingDivisorDescriptionEXT *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineTessellationStateCreateInfo              *,
            Type ( PipelineTessellationStateCreateInfo ) const *
    ) noexcept -> VkPipelineTessellationStateCreateInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineTessellationDomainOriginStateCreateInfo              *,
            Type ( PipelineTessellationDomainOriginStateCreateInfo ) const *
    ) noexcept -> VkPipelineTessellationDomainOriginStateCreateInfo *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISCARD_RECTANGLES_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineDiscardRectangleStateCreateInfoEXT           *,
            Type ( PipelineDiscardRectangleStateCreateInfo ) const *
    ) noexcept -> VkPipelineDiscardRectangleStateCreateInfoEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineFragmentShadingRateEnumStateCreateInfoNV                  *,
            Type ( PipelineFragmentShadingRateEnumStateCreateInfoNVidia ) const *
    ) noexcept -> VkPipelineFragmentShadingRateEnumStateCreateInfoNV *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineFragmentShadingRateStateCreateInfoKHR           *,
            Type ( PipelineFragmentShadingRateStateCreateInfo ) const *
    ) noexcept -> VkPipelineFragmentShadingRateStateCreateInfoKHR *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineRenderingCreateInfo_t            *,
            Type ( PipelineRenderingCreateInfo ) const *
    ) noexcept -> VkPipelineRenderingCreateInfo_t *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_REPRESENTATIVE_FRAGMENT_TEST_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineRepresentativeFragmentTestStateCreateInfoNV                  *,
            Type ( PipelineRepresentativeFragmentTestStateCreateInfoNVidia ) const *
    ) noexcept -> VkPipelineRepresentativeFragmentTestStateCreateInfoNV *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineInputAssemblyStateCreateInfo              *,
            Type ( PipelineInputAssemblyStateCreateInfo ) const *
    ) noexcept -> VkPipelineInputAssemblyStateCreateInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineViewportStateCreateInfo              *,
            Type ( PipelineViewportStateCreateInfo ) const *
    ) noexcept -> VkPipelineViewportStateCreateInfo *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineViewportCoarseSampleOrderStateCreateInfoNV                  *,
            Type ( PipelineViewportCoarseSampleOrderStateCreateInfoNVidia ) const *
    ) noexcept -> VkPipelineViewportCoarseSampleOrderStateCreateInfoNV *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE
    extern auto toVulkanFormat (
            VkCoarseSampleOrderCustomNV                  *,
            Type ( CoarseSampleOrderCustomNVidia ) const *
    ) noexcept -> VkCoarseSampleOrderCustomNV *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE
    extern auto toVulkanFormat (
            VkCoarseSampleLocationNV                  *,
            Type ( CoarseSampleLocationNVidia ) const *
    ) noexcept -> VkCoarseSampleLocationNV *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_CONTROL_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineViewportDepthClipControlCreateInfoEXT           *,
            Type ( PipelineViewportDepthClipControlCreateInfo ) const *
    ) noexcept -> VkPipelineViewportDepthClipControlCreateInfoEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SCISSOR_EXCLUSIVE_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineViewportExclusiveScissorStateCreateInfoNV                  *,
            Type ( PipelineViewportExclusiveScissorStateCreateInfoNVidia ) const *
    ) noexcept -> VkPipelineViewportExclusiveScissorStateCreateInfoNV *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineViewportShadingRateImageStateCreateInfoNV                  *,
            Type ( PipelineViewportShadingRateImageStateCreateInfoNVidia ) const *
    ) noexcept -> VkPipelineViewportShadingRateImageStateCreateInfoNV *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE
    extern auto toVulkanFormat (
            VkShadingRatePaletteNV                  *,
            Type ( ShadingRatePaletteNVidia ) const *
    ) noexcept -> VkShadingRatePaletteNV *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_VIEWPORT_SWIZZLE_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineViewportSwizzleStateCreateInfoNV                  *,
            Type ( PipelineViewportSwizzleStateCreateInfoNVidia ) const *
    ) noexcept -> VkPipelineViewportSwizzleStateCreateInfoNV *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_VIEWPORT_SWIZZLE_AVAILABLE
    extern auto toVulkanFormat (
            VkViewportSwizzleNV                  *,
            Type ( ViewportSwizzleNVidia ) const *
    ) noexcept -> VkViewportSwizzleNV *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CLIP_SPACE_W_SCALING_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineViewportWScalingStateCreateInfoNV                  *,
            Type ( PipelineViewportWScalingStateCreateInfoNVidia ) const *
    ) noexcept -> VkPipelineViewportWScalingStateCreateInfoNV *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CLIP_SPACE_W_SCALING_AVAILABLE
    extern auto toVulkanFormat (
            VkViewportWScalingNV                  *,
            Type ( ViewportWScalingNVidia ) const *
    ) noexcept -> VkViewportWScalingNV *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineRasterizationStateCreateInfo              *,
            Type ( PipelineRasterizationStateCreateInfo ) const *
    ) noexcept -> VkPipelineRasterizationStateCreateInfo *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONSERVATIVE_RASTERIZATION_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineRasterizationConservativeStateCreateInfoEXT           *,
            Type ( PipelineRasterizationConservativeStateCreateInfo ) const *
    ) noexcept -> VkPipelineRasterizationConservativeStateCreateInfoEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_ENABLE_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineRasterizationDepthClipStateCreateInfoEXT           *,
            Type ( PipelineRasterizationDepthClipStateCreateInfo ) const *
    ) noexcept -> VkPipelineRasterizationDepthClipStateCreateInfoEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineRasterizationLineStateCreateInfoEXT           *,
            Type ( PipelineRasterizationLineStateCreateInfo ) const *
    ) noexcept -> VkPipelineRasterizationLineStateCreateInfoEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineRasterizationProvokingVertexStateCreateInfoEXT           *,
            Type ( PipelineRasterizationProvokingVertexStateCreateInfo ) const *
    ) noexcept -> VkPipelineRasterizationProvokingVertexStateCreateInfoEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_RASTERIZATION_ORDER_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineRasterizationStateRasterizationOrderAMD              *,
            Type ( PipelineRasterizationStateRasterizationOrderAMD ) const *
    ) noexcept -> VkPipelineRasterizationStateRasterizationOrderAMD *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineRasterizationStateStreamCreateInfoEXT           *,
            Type ( PipelineRasterizationStateStreamCreateInfo ) const *
    ) noexcept -> VkPipelineRasterizationStateStreamCreateInfoEXT *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineMultisampleStateCreateInfo              *,
            Type ( PipelineMultisampleStateCreateInfo ) const *
    ) noexcept -> VkPipelineMultisampleStateCreateInfo *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAMEBUFFER_MIXED_SAMPLES_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineCoverageModulationStateCreateInfoNV                  *,
            Type ( PipelineCoverageModulationStateCreateInfoNVidia ) const *
    ) noexcept -> VkPipelineCoverageModulationStateCreateInfoNV *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COVERAGE_REDUCTION_MODE_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineCoverageReductionStateCreateInfoNV                  *,
            Type ( PipelineCoverageReductionStateCreateInfoNVidia ) const *
    ) noexcept -> VkPipelineCoverageReductionStateCreateInfoNV *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_COVERAGE_TO_COLOR_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineCoverageToColorStateCreateInfoNV                  *,
            Type ( PipelineCoverageToColorStateCreateInfoNVidia ) const *
    ) noexcept -> VkPipelineCoverageToColorStateCreateInfoNV *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineSampleLocationsStateCreateInfoEXT           *,
            Type ( PipelineSampleLocationsStateCreateInfo ) const *
    ) noexcept -> VkPipelineSampleLocationsStateCreateInfoEXT *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineDepthStencilStateCreateInfo              *,
            Type ( PipelineDepthStencilStateCreateInfo ) const *
    ) noexcept -> VkPipelineDepthStencilStateCreateInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineColorBlendStateCreateInfo              *,
            Type ( PipelineColorBlendStateCreateInfo ) const *
    ) noexcept -> VkPipelineColorBlendStateCreateInfo *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineColorBlendAdvancedStateCreateInfoEXT           *,
            Type ( PipelineColorBlendAdvancedStateCreateInfo ) const *
    ) noexcept -> VkPipelineColorBlendAdvancedStateCreateInfoEXT *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_COLOR_WRITE_ENABLE_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineColorWriteCreateInfoEXT           *,
            Type ( PipelineColorWriteCreateInfo ) const *
    ) noexcept -> VkPipelineColorWriteCreateInfoEXT *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineColorBlendAttachmentState              *,
            Type ( PipelineColorBlendAttachmentState ) const *
    ) noexcept -> VkPipelineColorBlendAttachmentState *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineDynamicStateCreateInfo              *,
            Type ( PipelineDynamicStateCreateInfo ) const *
    ) noexcept -> VkPipelineDynamicStateCreateInfo *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
    extern auto prepareContext (
            CreateRayTracingPipelineNVidiaContext             *,
            cds :: uint32,
            Type ( RayTracingPipelineCreateInfoNVidia ) const *
    ) noexcept -> VkRayTracingPipelineCreateInfoNV *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
    extern auto extractContext (
            cds :: uint32,
            Type ( RayTracingPipelineCreateInfoNVidia ) const *,
            CreateRayTracingPipelineNVidiaContext       const *
    ) noexcept -> void;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
    extern auto toVulkanFormat (
            VkRayTracingPipelineCreateInfoNV                  *,
            Type ( RayTracingPipelineCreateInfoNVidia ) const *
    ) noexcept -> VkRayTracingPipelineCreateInfoNV *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
    extern auto toVulkanFormat (
            VkRayTracingShaderGroupCreateInfoNV                  *,
            Type ( RayTracingShaderGroupCreateInfoNVidia ) const *
    ) noexcept -> VkRayTracingShaderGroupCreateInfoNV *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
    extern auto prepareContext (
            CreateRayTracingPipelineContext             *,
            cds :: uint32,
            Type ( RayTracingPipelineCreateInfo ) const *
    ) noexcept -> VkRayTracingPipelineCreateInfoKHR *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
    extern auto extractContext (
            cds :: uint32,
            Type ( RayTracingPipelineCreateInfo ) const *,
            CreateRayTracingPipelineContext       const *
    ) noexcept -> void;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
    extern auto toVulkanFormat (
            VkRayTracingPipelineCreateInfoKHR           *,
            Type ( RayTracingPipelineCreateInfo ) const *
    ) noexcept -> VkRayTracingPipelineCreateInfoKHR *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
    extern auto toVulkanFormat (
            VkRayTracingShaderGroupCreateInfoKHR           *,
            Type ( RayTracingShaderGroupCreateInfo ) const *
    ) noexcept -> VkRayTracingShaderGroupCreateInfoKHR *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineLibraryCreateInfoKHR           *,
            Type ( PipelineLibraryCreateInfo ) const *
    ) noexcept -> VkPipelineLibraryCreateInfoKHR *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
    extern auto toVulkanFormat (
            VkRayTracingPipelineInterfaceCreateInfoKHR           *,
            Type ( RayTracingPipelineInterfaceCreateInfo ) const *
    ) noexcept -> VkRayTracingPipelineInterfaceCreateInfoKHR *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto prepareContext (
            CreatePipelineCacheContext             *,
            Type ( PipelineCacheCreateInfo ) const *
    ) noexcept -> VkPipelineCacheCreateInfo *;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineCacheCreateInfo              *,
            Type ( PipelineCacheCreateInfo ) const *
    ) noexcept -> VkPipelineCacheCreateInfo *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineInfoKHR           *,
            Type ( PipelineInfo ) const *
    ) noexcept -> VkPipelineInfoKHR *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
    extern auto toVulkanFormat (
            VkPipelineExecutableInfoKHR           *,
            Type ( PipelineExecutableInfo ) const *
    ) noexcept -> VkPipelineExecutableInfoKHR *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PipelineExecutableStatistic )         *,
            VkPipelineExecutableStatisticKHR       const *
    ) noexcept -> Type ( PipelineExecutableStatistic ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PipelineExecutableProperties )         *,
            VkPipelineExecutablePropertiesKHR       const *
    ) noexcept -> Type ( PipelineExecutableProperties ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
    extern auto fromVulkanFormat (
            Type ( PipelineExecutableInternalRepresentation )         *,
            VkPipelineExecutableInternalRepresentationKHR       const *
    ) noexcept -> Type ( PipelineExecutableInternalRepresentation ) *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
    extern auto prepareContext (
            GetPipelinePropertiesContext      *,
            Type ( PipelineInfo )       const *
    ) noexcept -> VkPipelineInfoKHR *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
    extern auto prepareContext (
            GetPipelineStatisticsContext          *,
            Type ( PipelineExecutableInfo ) const *
    ) noexcept -> VkPipelineExecutableInfoKHR *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
    extern auto prepareContext (
            GetPipelineInternalRepresentationsContext         *,
            Type ( PipelineExecutableInfo )             const *
    ) noexcept -> VkPipelineExecutableInfoKHR *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
    extern auto prepareContext (
            GetPipelineInternalRepresentationsContext                 *,
            cds :: uint32,
            Type ( PipelineExecutableInternalRepresentation )         *
    ) noexcept -> VkPipelineExecutableInternalRepresentationKHR *;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
    extern auto extractContext (
            cds :: uint32,
            Type ( PipelineExecutableProperties )         *,
            GetPipelinePropertiesContext            const *
    ) noexcept -> void;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
    extern auto extractContext (
            cds :: uint32,
            Type ( PipelineExecutableStatistic )          *,
            GetPipelineStatisticsContext            const *
    ) noexcept -> void;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
    extern auto extractContext (
            cds :: uint32,
            Type ( PipelineExecutableInternalRepresentation )          *,
            GetPipelineInternalRepresentationsContext            const *
    ) noexcept -> void;
#endif

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif //__C_ENG_VULKAN_API_CALLS_CONVERSION_HPP__

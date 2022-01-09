//
// Created by loghin on 26.12.2021.
//

#include "VulkanCore.hpp"

#include <Func.hpp>

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

auto vulkan :: toString (
        vulkan :: __C_ENG_TYPE ( Result ) result
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( result ) {

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultSuccess:                                     { asString = "Success";                                                                                                                                                                                                        break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultNotReady:                                    { asString = "Fence or Query not yet completed";                                                                                                                                                                               break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultTimeout:                                     { asString = "Waiting Operation did not complete in specified time";                                                                                                                                                           break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultEventSet:                                    { asString = "Event Signalled";                                                                                                                                                                                                break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultEventReset:                                  { asString = "Event Unsignalled";                                                                                                                                                                                              break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultIncomplete:                                  { asString = "Result is Incomplete, return array too small";                                                                                                                                                                   break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorOutOfHostMemory:                        { asString = "Host Memory Allocation Failed";                                                                                                                                                                                  break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorOutOfDeviceMemory:                      { asString = "Device Memory Allocation Failed";                                                                                                                                                                                break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorInitializationFailed:                   { asString = "Vulkan Object Initialization could not be completed";                                                                                                                                                            break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorDeviceLost:                             { asString = "Physical/Logical Device Lost. See https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/vkspec.html#devsandqueues-lost-device";                                                                      break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorMemoryMapFailed:                        { asString = "Mapping of a memory object has failed";                                                                                                                                                                          break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorLayerNotPresent:                        { asString = "Requested layer is not present / could not be loaded";                                                                                                                                                           break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorFeatureNotPresent:                      { asString = "Requested feature is not supported";                                                                                                                                                                             break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorIncompatibleDriver:                     { asString = "Requested version of Vulkan is not supported by the driver";                                                                                                                                                     break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorTooManyObjects:                         { asString = "Too many objects of this type have been already created";                                                                                                                                                        break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorFormatNotSupported:                     { asString = "Requested format not supported";                                                                                                                                                                                 break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorFragmentedPool:                         { asString = "Pool Allocation Failed due to Fragmentation of the pool's memory";                                                                                                                                               break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorUnknown:                                { asString = "Unknown Error, invalid input or implementation failure";                                                                                                                                                         break; }

#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorOutOfPoolMemory:                        { asString = "Pool Allocation Failed due to lack of memory";                                                                                                                                                                   break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorInvalidExternalHandle:                  { asString = "External Handle is not a valid Handle of the specified type";                                                                                                                                                    break; }

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorFragmentation:                          { asString = "Descriptor Pool Creation Failed due to Fragmentation";                                                                                                                                                           break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorInvalidOpaqueCaptureAddress:            { asString = "Buffer Creation or Memory Allocation Failed because the requested address is not available. A shader group handle assignment failed because the requested shader group handle information is no longer valid";   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE

        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorSurfaceLost:                            { asString = "Surface is no longer available";                                                                                                                                                                                 break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorNativeWindowInUse:                      { asString = "Requested Window is already in use by Vulkan or another API.";                                                                                                                                                   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DISPLAY_SWAP_CHAIN_AVAILABLE

        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorIncompatibleDisplay:                    { asString = "Display used by a swapchain does not use the same presentable image layout, or is incompatible in a way that prevents image sharing";                                                                            break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DEFERRED_HOST_OPERATIONS_AVAILABLE

        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultThreadIdle:                                  { asString = "Deferred operation is not complete, but there is no work for this thread to do at the time of this call";                                                                                                        break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultThreadDone:                                  { asString = "Deferred operation is not complete, but there is no work remaining to assign to additional threads";                                                                                                             break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultOperationDeferred:                           { asString = "Deferred operation requested and at least some work was deferred";                                                                                                                                               break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultOperationNotDeferred:                        { asString = "Deferred operation requested and no operation was deferred";                                                                                                                                                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_GLSL_SHADER_AVAILABLE

        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorInvalidShader:                          { asString = "One or more shaders failed to compile or link";                                                                                                                                                                  break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_REPORT_AVAILABLE

        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorValidationFailed:                       { asString = "Validation Layer Attachment Failed";                                                                                                                                                                             break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_DRM_FORMAT_MODIFIER_AVAILABLE

        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorInvalidDRMFormatModifierPlaneLayout:    { asString = "Tiling layout provided to application did not match external image layout";                                                                                                                                      break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_AVAILABLE

        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorNotPermitted:                           { asString = "Driver Denied Request due to System Resource Starvation";                                                                                                                                                        break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FULL_SCREEN_EXCLUSIVE_AVAILABLE

        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorFullScreenExclusiveModeLost:            { asString = "Operation Failed due to not having exclusive full-screen access";                                                                                                                                                break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE

        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultPipelineCompileRequired:                     { asString = "Requested Pipeline Creation would have required compilation, but the application requested that compilation not be performed";                                                                                   break; }

#endif

        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorIncompatibleVersion:                    { asString = "API Version does not support call";                                                                                                                                                                              break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorConfigurationArraySizeSmall:            { asString = "Array Size too Small, check 'VulkanCoreConfig.hpp'";                                                                                                                                                             break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorFunctionHandleNotFound:                 { asString = "Function Requested not Present";                                                                                                                                                                                 break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorIllegalArgument:                        { asString = "Illegal Argument Passed to Binding Call";                                                                                                                                                                        break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultUnknown:                                     { asString = "Unknown/Not Documented Result";                                                                                                                                                                                  break; }
    }

    return asString;
}

auto vulkan :: toString (
        __C_ENG_TYPE ( StructureType ) type
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( type ) {

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

        case StructureTypeApplicationInfo:                                                          { asString = "StructureTypeApplicationInfo";                                                    break; }
        case StructureTypeInstanceCreateInfo:                                                       { asString = "StructureTypeInstanceCreateInfo";                                                 break; }
        case StructureTypeDeviceQueueCreateInfo:                                                    { asString = "StructureTypeDeviceQueueCreateInfo";                                              break; }
        case StructureTypeDeviceCreateInfo:                                                         { asString = "StructureTypeDeviceCreateInfo";                                                   break; }
        case StructureTypeSubmitInfo:                                                               { asString = "StructureTypeSubmitInfo";                                                         break; }
        case StructureTypeMemoryAllocateInfo:                                                       { asString = "StructureTypeMemoryAllocateInfo";                                                 break; }
        case StructureTypeMappedMemoryRange:                                                        { asString = "StructureTypeMappedMemoryRange";                                                  break; }
        case StructureTypeBindSparseInfo:                                                           { asString = "StructureTypeBindSparseInfo";                                                     break; }
        case StructureTypeFenceCreateInfo:                                                          { asString = "StructureTypeFenceCreateInfo";                                                    break; }
        case StructureTypeSemaphoreCreateInfo:                                                      { asString = "StructureTypeSemaphoreCreateInfo";                                                break; }
        case StructureTypeEventCreateInfo:                                                          { asString = "StructureTypeEventCreateInfo";                                                    break; }
        case StructureTypeQueryPoolCreateInfo:                                                      { asString = "StructureTypeQueryPoolCreateInfo";                                                break; }
        case StructureTypeBufferCreateInfo:                                                         { asString = "StructureTypeBufferCreateInfo";                                                   break; }
        case StructureTypeBufferViewCreateInfo:                                                     { asString = "StructureTypeBufferViewCreateInfo";                                               break; }
        case StructureTypeImageCreateInfo:                                                          { asString = "StructureTypeImageCreateInfo";                                                    break; }
        case StructureTypeImageViewCreateInfo:                                                      { asString = "StructureTypeImageViewCreateInfo";                                                break; }
        case StructureTypeShaderModuleCreateInfo:                                                   { asString = "StructureTypeShaderModuleCreateInfo";                                             break; }
        case StructureTypePipelineCacheCreateInfo:                                                  { asString = "StructureTypePipelineCacheCreateInfo";                                            break; }
        case StructureTypePipelineShaderStageCreateInfo:                                            { asString = "StructureTypePipelineShaderStageCreateInfo";                                      break; }
        case StructureTypePipelineVertexInputStateCreateInfo:                                       { asString = "StructureTypePipelineVertexInputStateCreateInfo";                                 break; }
        case StructureTypePipelineInputAssemblyStateCreateInfo:                                     { asString = "StructureTypePipelineInputAssemblyStateCreateInfo";                               break; }
        case StructureTypePipelineTesselationStateCreateInfo:                                       { asString = "StructureTypePipelineTesselationStateCreateInfo";                                 break; }
        case StructureTypePipelineViewportStateCreateInfo:                                          { asString = "StructureTypePipelineViewportStateCreateInfo";                                    break; }
        case StructureTypePipelineRasterizationStateCreateInfo:                                     { asString = "StructureTypePipelineRasterizationStateCreateInfo";                               break; }
        case StructureTypePipelineMultisampleStateCreateInfo:                                       { asString = "StructureTypePipelineMultisampleStateCreateInfo";                                 break; }
        case StructureTypePipelineDepthStencilStateCreateInfo:                                      { asString = "StructureTypePipelineDepthStencilStateCreateInfo";                                break; }
        case StructureTypePipelineColorBlendStateCreateInfo:                                        { asString = "StructureTypePipelineColorBlendStateCreateInfo";                                  break; }
        case StructureTypePipelineDynamicStateCreateInfo:                                           { asString = "StructureTypePipelineDynamicStateCreateInfo";                                     break; }
        case StructureTypeGraphicsPipelineCreateInfo:                                               { asString = "StructureTypeGraphicsPipelineCreateInfo";                                         break; }
        case StructureTypeComputePipelineCreateInfo:                                                { asString = "StructureTypeComputePipelineCreateInfo";                                          break; }
        case StructureTypePipelineLayoutCreateInfo:                                                 { asString = "StructureTypePipelineLayoutCreateInfo";                                           break; }
        case StructureTypeSamplerCreateInfo:                                                        { asString = "StructureTypeSamplerCreateInfo";                                                  break; }
        case StructureTypeDescriptorSetLayoutCreateInfo:                                            { asString = "StructureTypeDescriptorSetLayoutCreateInfo";                                      break; }
        case StructureTypeDescriptorPoolCreateInfo:                                                 { asString = "StructureTypeDescriptorPoolCreateInfo";                                           break; }
        case StructureTypeDescriptorSetAllocateInfo:                                                { asString = "StructureTypeDescriptorSetAllocateInfo";                                          break; }
        case StructureTypeWriteDescriptorSet:                                                       { asString = "StructureTypeWriteDescriptorSet";                                                 break; }
        case StructureTypeCopyDescriptorSet:                                                        { asString = "StructureTypeCopyDescriptorSet";                                                  break; }
        case StructureTypeFramebufferCreateInfo:                                                    { asString = "StructureTypeFramebufferCreateInfo";                                              break; }
        case StructureTypeRenderPassCreateInfo:                                                     { asString = "StructureTypeRenderPassCreateInfo";                                               break; }
        case StructureTypeCommandPoolCreateInfo:                                                    { asString = "StructureTypeCommandPoolCreateInfo";                                              break; }
        case StructureTypeCommandBufferAllocateInfo:                                                { asString = "StructureTypeCommandBufferAllocateInfo";                                          break; }
        case StructureTypeCommandBufferInheritanceInfo:                                             { asString = "StructureTypeCommandBufferInheritanceInfo";                                       break; }
        case StructureTypeCommandBufferBeginInfo:                                                   { asString = "StructureTypeCommandBufferBeginInfo";                                             break; }
        case StructureTypeRenderPassBeginInfo:                                                      { asString = "StructureTypeRenderPassBeginInfo";                                                break; }
        case StructureTypeBufferMemoryBarrier:                                                      { asString = "StructureTypeBufferMemoryBarrier";                                                break; }
        case StructureTypeImageMemoryBarrier:                                                       { asString = "StructureTypeImageMemoryBarrier";                                                 break; }
        case StructureTypeMemoryBarrier:                                                            { asString = "StructureTypeMemoryBarrier";                                                      break; }
        case StructureTypeLoaderInstanceCreateInfo:                                                 { asString = "StructureTypeLoaderInstanceCreateInfo";                                           break; }
        case StructureTypeLoaderDeviceCreateInfo:                                                   { asString = "StructureTypeLoaderDeviceCreateInfo";                                             break; }

#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

        case StructureTypePhysicalDeviceSubgroupProperties:                                         { asString = "StructureTypePhysicalDeviceSubgroupProperties";                                   break; }
        case StructureTypeBindBufferMemoryInfo:                                                     { asString = "StructureTypeBindBufferMemoryInfo";                                               break; }
        case StructureTypeBindImageMemoryInfo:                                                      { asString = "StructureTypeBindImageMemoryInfo";                                                break; }
        case StructureTypePhysicalDevice16BitStorageFeatures:                                       { asString = "StructureTypePhysicalDevice16BitStorageFeatures";                                 break; }
        case StructureTypeMemoryDedicatedRequirements:                                              { asString = "StructureTypeMemoryDedicatedRequirements";                                        break; }
        case StructureTypeMemoryDedicatedAllocateInfo:                                              { asString = "StructureTypeMemoryDedicatedAllocateInfo";                                        break; }
        case StructureTypeMemoryAllocateFlagsInfo:                                                  { asString = "StructureTypeMemoryAllocateFlagsInfo";                                            break; }
        case StructureTypeDeviceGroupRenderPassBeginInfo:                                           { asString = "StructureTypeDeviceGroupRenderPassBeginInfo";                                     break; }
        case StructureTypeDeviceGroupCommandBufferBeginInfo:                                        { asString = "StructureTypeDeviceGroupCommandBufferBeginInfo";                                  break; }
        case StructureTypeDeviceGroupSubmitInfo:                                                    { asString = "StructureTypeDeviceGroupSubmitInfo";                                              break; }
        case StructureTypeDeviceGroupBindSparseInfo:                                                { asString = "StructureTypeDeviceGroupBindSparseInfo";                                          break; }
        case StructureTypeBindBufferMemoryDeviceGroupInfo:                                          { asString = "StructureTypeBindBufferMemoryDeviceGroupInfo";                                    break; }
        case StructureTypeBindImageMemoryDeviceGroupInfo:                                           { asString = "StructureTypeBindImageMemoryDeviceGroupInfo";                                     break; }
        case StructureTypePhysicalDeviceGroupProperties:                                            { asString = "StructureTypePhysicalDeviceGroupProperties";                                      break; }
        case StructureTypeDeviceGroupDeviceCreateInfo:                                              { asString = "StructureTypeDeviceGroupDeviceCreateInfo";                                        break; }
        case StructureTypeBufferMemoryRequirementsInfo:                                             { asString = "StructureTypeBufferMemoryRequirementsInfo";                                       break; }
        case StructureTypeImageMemoryRequirementsInfo:                                              { asString = "StructureTypeImageMemoryRequirementsInfo";                                        break; }
        case StructureTypeImageSparseMemoryRequirementsInfo:                                        { asString = "StructureTypeImageSparseMemoryRequirementsInfo";                                  break; }
        case StructureTypeMemoryRequirements:                                                       { asString = "StructureTypeMemoryRequirements";                                                 break; }
        case StructureTypeSparseImageMemoryRequirements:                                            { asString = "StructureTypeSparseImageMemoryRequirements";                                      break; }
        case StructureTypePhysicalDeviceFeatures:                                                   { asString = "StructureTypePhysicalDeviceFeatures";                                             break; }
        case StructureTypePhysicalDeviceProperties:                                                 { asString = "StructureTypePhysicalDeviceProperties";                                           break; }
        case StructureTypeFormatProperties:                                                         { asString = "StructureTypeFormatProperties";                                                   break; }
        case StructureTypeImageFormatProperties:                                                    { asString = "StructureTypeImageFormatProperties";                                              break; }
        case StructureTypePhysicalDeviceImageFormatInfo:                                            { asString = "StructureTypePhysicalDeviceImageFormatInfo";                                      break; }
        case StructureTypeQueueFamilyProperties:                                                    { asString = "StructureTypeQueueFamilyProperties";                                              break; }
        case StructureTypePhysicalDeviceMemoryProperties:                                           { asString = "StructureTypePhysicalDeviceMemoryProperties";                                     break; }
        case StructureTypeSparseImageFormatProperties:                                              { asString = "StructureTypeSparseImageFormatProperties";                                        break; }
        case StructureTypePhysicalDeviceSparseImageFormatInfo:                                      { asString = "StructureTypePhysicalDeviceSparseImageFormatInfo";                                break; }
        case StructureTypePhysicalDevicePointClippingProperties:                                    { asString = "StructureTypePhysicalDevicePointClippingProperties";                              break; }
        case StructureTypeRenderPassInputAttachmentAspectCreateInfo:                                { asString = "StructureTypeRenderPassInputAttachmentAspectCreateInfo";                          break; }
        case StructureTypeImageViewUsageCreateInfo:                                                 { asString = "StructureTypeImageViewUsageCreateInfo";                                           break; }
        case StructureTypePipelineTesselationDomainOriginStateCreateInfo:                           { asString = "StructureTypePipelineTesselationDomainOriginStateCreateInfo";                     break; }
        case StructureTypeRenderPassMultiviewCreateInfo:                                            { asString = "StructureTypeRenderPassMultiviewCreateInfo";                                      break; }
        case StructureTypePhysicalDeviceMultiviewFeatures:                                          { asString = "StructureTypePhysicalDeviceMultiviewFeatures";                                    break; }
        case StructureTypePhysicalDeviceMultiviewProperties:                                        { asString = "StructureTypePhysicalDeviceMultiviewProperties";                                  break; }
        case StructureTypePhysicalDeviceVariablePointersFeatures:                                   { asString = "StructureTypePhysicalDeviceVariablePointersFeatures";                             break; }
        case StructureTypeProtectedSubmitInfo:                                                      { asString = "StructureTypeProtectedSubmitInfo";                                                break; }
        case StructureTypePhysicalDeviceProtectedMemoryFeatures:                                    { asString = "StructureTypePhysicalDeviceProtectedMemoryFeatures";                              break; }
        case StructureTypePhysicalDeviceProtectedMemoryProperties:                                  { asString = "StructureTypePhysicalDeviceProtectedMemoryProperties";                            break; }
        case StructureTypeDeviceQueueInfo:                                                          { asString = "StructureTypeDeviceQueueInfo";                                                    break; }
        case StructureTypeSamplerYCBCRConversionCreateInfo:                                         { asString = "StructureTypeSamplerYCBCRConversionCreateInfo";                                   break; }
        case StructureTypeSamplerYCBCRConversionInfo:                                               { asString = "StructureTypeSamplerYCBCRConversionInfo";                                         break; }
        case StructureTypeBindImagePlaneMemoryInfo:                                                 { asString = "StructureTypeBindImagePlaneMemoryInfo";                                           break; }
        case StructureTypeImagePlaneMemoryRequirementsInfo:                                         { asString = "StructureTypeImagePlaneMemoryRequirementsInfo";                                   break; }
        case StructureTypePhysicalDeviceSamplerYCBCRConversionFeatures:                             { asString = "StructureTypePhysicalDeviceSamplerYCBCRConversionFeatures";                       break; }
        case StructureTypeSamplerYCBCRConversionImageFormatProperties:                              { asString = "StructureTypeSamplerYCBCRConversionImageFormatProperties";                        break; }
        case StructureTypeDescriptorUpdateTemplateCreateInfo:                                       { asString = "StructureTypeDescriptorUpdateTemplateCreateInfo";                                 break; }
        case StructureTypePhysicalDeviceExternalImageFormatInfo:                                    { asString = "StructureTypePhysicalDeviceExternalImageFormatInfo";                              break; }
        case StructureTypeExternalImageFormatProperties:                                            { asString = "StructureTypeExternalImageFormatProperties";                                      break; }
        case StructureTypePhysicalDeviceExternalBufferInfo:                                         { asString = "StructureTypePhysicalDeviceExternalBufferInfo";                                   break; }
        case StructureTypeExternalBufferProperties:                                                 { asString = "StructureTypeExternalBufferProperties";                                           break; }
        case StructureTypePhysicalDeviceIDProperties:                                               { asString = "StructureTypePhysicalDeviceIDProperties";                                         break; }
        case StructureTypeExternalMemoryBufferCreateInfo:                                           { asString = "StructureTypeExternalMemoryBufferCreateInfo";                                     break; }
        case StructureTypeExternalMemoryImageCreateInfo:                                            { asString = "StructureTypeExternalMemoryImageCreateInfo";                                      break; }
        case StructureTypeExportMemoryAllocateInfo:                                                 { asString = "StructureTypeExportMemoryAllocateInfo";                                           break; }
        case StructureTypePhysicalDeviceExternalFenceInfo:                                          { asString = "StructureTypePhysicalDeviceExternalFenceInfo";                                    break; }
        case StructureTypeExternalFenceProperties:                                                  { asString = "StructureTypeExternalFenceProperties";                                            break; }
        case StructureTypeExportFenceCreateInfo:                                                    { asString = "StructureTypeExportFenceCreateInfo";                                              break; }
        case StructureTypeExportSemaphoreCreateInfo:                                                { asString = "StructureTypeExportSemaphoreCreateInfo";                                          break; }
        case StructureTypePhysicalDeviceExternalSempahoreInfo:                                      { asString = "StructureTypePhysicalDeviceExternalSempahoreInfo";                                break; }
        case StructureTypeExternalSemaphoreProperties:                                              { asString = "StructureTypeExternalSemaphoreProperties";                                        break; }
        case StructureTypePhysicalDeviceMaintenanceProperties:                                      { asString = "StructureTypePhysicalDeviceMaintenanceProperties";                                break; }
        case StructureTypeDescriptorSetLayoutSupport:                                               { asString = "StructureTypeDescriptorSetLayoutSupport";                                         break; }
        case StructureTypePhysicalDeviceShaderDrawParametersFeatures:                               { asString = "StructureTypePhysicalDeviceShaderDrawParametersFeatures";                         break; }

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

        case StructureTypePhysicalDeviceVulkan_1_1_Features:                                        { asString = "StructureTypePhysicalDeviceVulkan_1_1_Features";                                  break; }
        case StructureTypePhysicalDeviceVulkan_1_1_Properties:                                      { asString = "StructureTypePhysicalDeviceVulkan_1_1_Properties";                                break; }
        case StructureTypePhysicalDeviceVulkan_1_2_Features:                                        { asString = "StructureTypePhysicalDeviceVulkan_1_2_Features";                                  break; }
        case StructureTypePhysicalDeviceVulkan_1_2_Properties:                                      { asString = "StructureTypePhysicalDeviceVulkan_1_2_Properties";                                break; }
        case StructureTypeImageFormatListCreateInfo:                                                { asString = "StructureTypeImageFormatListCreateInfo";                                          break; }
        case StructureTypeAttachmentDescription:                                                    { asString = "StructureTypeAttachmentDescription";                                              break; }
        case StructureTypeAttachmentReference:                                                      { asString = "StructureTypeAttachmentReference";                                                break; }
        case StructureTypeSubpassDescription:                                                       { asString = "StructureTypeSubpassDescription";                                                 break; }
        case StructureTypeSubpassDependency:                                                        { asString = "StructureTypeSubpassDependency";                                                  break; }
        case StructureTypeRenderPassCreateInfo2:                                                    { asString = "StructureTypeRenderPassCreateInfo2";                                              break; }
        case StructureTypeSubpassBeginInfo:                                                         { asString = "StructureTypeSubpassBeginInfo";                                                   break; }
        case StructureTypeSubpassEndInfo:                                                           { asString = "StructureTypeSubpassEndInfo";                                                     break; }
        case StructureTypePhysicalDevice8BitStorageFeatures:                                        { asString = "StructureTypePhysicalDevice8BitStorageFeatures";                                  break; }
        case StructureTypePhysicalDeviceDriverProperties:                                           { asString = "StructureTypePhysicalDeviceDriverProperties";                                     break; }
        case StructureTypePhysicalDeviceShaderAtomicInt64Features:                                  { asString = "StructureTypePhysicalDeviceShaderAtomicInt64Features";                            break; }
        case StructureTypePhysicalDeviceShaderFloat16Int8Features:                                  { asString = "StructureTypePhysicalDeviceShaderFloat16Int8Features";                            break; }
        case StructureTypePhysicalDeviceFloatControlsProperties:                                    { asString = "StructureTypePhysicalDeviceFloatControlsProperties";                              break; }
        case StructureTypeDescriptorSetLayoutBindingFlagsCreateInfo:                                { asString = "StructureTypeDescriptorSetLayoutBindingFlagsCreateInfo";                          break; }
        case StructureTypePhysicalDeviceDescriptorIndexingFeatures:                                 { asString = "StructureTypePhysicalDeviceDescriptorIndexingFeatures";                           break; }
        case StructureTypePhysicalDeviceDescriptorIndexingProperties:                               { asString = "StructureTypePhysicalDeviceDescriptorIndexingProperties";                         break; }
        case StructureTypeDescriptorSetVariableDescriptorCountAllocateInfo:                         { asString = "StructureTypeDescriptorSetVariableDescriptorCountAllocateInfo";                   break; }
        case StructureTypeDescriptorSetVariableDescriptorCountLayoutSupport:                        { asString = "StructureTypeDescriptorSetVariableDescriptorCountLayoutSupport";                  break; }
        case StructureTypePhysicalDeviceDepthStencilResolveProperties:                              { asString = "StructureTypePhysicalDeviceDepthStencilResolveProperties";                        break; }
        case StructureTypeSubpassDescriptionDepthStencilResolve:                                    { asString = "StructureTypeSubpassDescriptionDepthStencilResolve";                              break; }
        case StructureTypePhysicalDeviceScalarBlockLayoutFeatures:                                  { asString = "StructureTypePhysicalDeviceScalarBlockLayoutFeatures";                            break; }
        case StructureTypeImageStencilUsageCreateInfo:                                              { asString = "StructureTypeImageStencilUsageCreateInfo";                                        break; }
        case StructureTypePhysicalDeviceSamplerFilterMinMaxProperties:                              { asString = "StructureTypePhysicalDeviceSamplerFilterMinMaxProperties";                        break; }
        case StructureTypeSamplerReductionModeCreateInfo:                                           { asString = "StructureTypeSamplerReductionModeCreateInfo";                                     break; }
        case StructureTypePhysicalDeviceVulkanMemoryModelFeatures:                                  { asString = "StructureTypePhysicalDeviceVulkanMemoryModelFeatures";                            break; }
        case StructureTypePhysicalDeviceImagelessFramebufferFeatures:                               { asString = "StructureTypePhysicalDeviceImagelessFramebufferFeatures";                         break; }
        case StructureTypeFramebufferAttachmentsCreateInfo:                                         { asString = "StructureTypeFramebufferAttachmentsCreateInfo";                                   break; }
        case StructureTypeFramebufferAttachmentImageInfo:                                           { asString = "StructureTypeFramebufferAttachmentImageInfo";                                     break; }
        case StructureTypeRenderPassAttachmentBeginInfo:                                            { asString = "StructureTypeRenderPassAttachmentBeginInfo";                                      break; }
        case StructureTypePhysicalDeviceUniformBufferStandardLayoutFeatures:                        { asString = "StructureTypePhysicalDeviceUniformBufferStandardLayoutFeatures";                  break; }
        case StructureTypePhysicalDeviceShaderSubgroupExtendedTypesFeatures:                        { asString = "StructureTypePhysicalDeviceShaderSubgroupExtendedTypesFeatures";                  break; }
        case StructureTypePhysicalDeviceSeparateDepthStencilLayoutsFeatures:                        { asString = "StructureTypePhysicalDeviceSeparateDepthStencilLayoutsFeatures";                  break; }
        case StructureTypeAttachmentReferenceStencilLayout:                                         { asString = "StructureTypeAttachmentReferenceStencilLayout";                                   break; }
        case StructureTypeAttachmentDescriptionStencilLayout:                                       { asString = "StructureTypeAttachmentDescriptionStencilLayout";                                 break; }
        case StructureTypePhysicalDeviceHostQueryResetFeatures:                                     { asString = "StructureTypePhysicalDeviceHostQueryResetFeatures";                               break; }
        case StructureTypePhysicalDeviceTimelineSemaphoreFeatures:                                  { asString = "StructureTypePhysicalDeviceTimelineSemaphoreFeatures";                            break; }
        case StructureTypePhysicalDeviceTimelineSemaphoreProperties:                                { asString = "StructureTypePhysicalDeviceTimelineSemaphoreProperties";                          break; }
        case StructureTypeSemaphoreTypeCreateInfo:                                                  { asString = "StructureTypeSemaphoreTypeCreateInfo";                                            break; }
        case StructureTypeTimelineSemaphoreSubmitInfo:                                              { asString = "StructureTypeTimelineSemaphoreSubmitInfo";                                        break; }
        case StructureTypeSemaphoreWaitInfo:                                                        { asString = "StructureTypeSemaphoreWaitInfo";                                                  break; }
        case StructureTypeSemaphoreSignalInfo:                                                      { asString = "StructureTypeSemaphoreSignalInfo";                                                break; }
        case StructureTypePhysicalDeviceBufferDeviceAddressFeatures:                                { asString = "StructureTypePhysicalDeviceBufferDeviceAddressFeatures";                          break; }
        case StructureTypeBufferDeviceAddressInfo:                                                  { asString = "StructureTypeBufferDeviceAddressInfo";                                            break; }
        case StructureTypeBufferOpaqueCaptureAddressCreateInfo:                                     { asString = "StructureTypeBufferOpaqueCaptureAddressCreateInfo";                               break; }
        case StructureTypeMemoryOpaqueCaptureAddressAllocateInfo:                                   { asString = "StructureTypeMemoryOpaqueCaptureAddressAllocateInfo";                             break; }
        case StructureTypeDeviceMemoryOpaqueCaptureAddressInfo:                                     { asString = "StructureTypeDeviceMemoryOpaqueCaptureAddressInfo";                               break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE

        case StructureTypeSwapchainCreateInfo:                                                      { asString = "StructureTypeSwapchainCreateInfo";                                                break; }
        case StructureTypePresentInfo:                                                              { asString = "StructureTypePresentInfo";                                                        break; }

#endif

#if ( __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE ) || ( __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DEVICE_GROUP_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE )

        case StructureTypeDeviceGroupPresentCapabilities:                                           { asString = "StructureTypeDeviceGroupPresentCapabilities";                                     break; }
        case StructureTypeImageSwapchainCreateInfo:                                                 { asString = "StructureTypeImageSwapchainCreateInfo";                                           break; }
        case StructureTypeBindImageMemorySwapchainInfo:                                             { asString = "StructureTypeBindImageMemorySwapchainInfo";                                       break; }
        case StructureTypeAcquireNextImageInfo:                                                     { asString = "StructureTypeAcquireNextImageInfo";                                               break; }
        case StructureTypeDeviceGroupPresentInfo:                                                   { asString = "StructureTypeDeviceGroupPresentInfo";                                             break; }
        case StructureTypeDeviceGroupSwapchainCreateInfo:                                           { asString = "StructureTypeDeviceGroupSwapchainCreateInfo";                                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DISPLAY_AVAILABLE

        case StructureTypeDisplayModeCreateInfo:                                                    { asString = "StructureTypeDisplayModeCreateInfo";                                              break; }
        case StructureTypeDisplaySurfaceCreateInfo:                                                 { asString = "StructureTypeDisplaySurfaceCreateInfo";                                           break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DISPLAY_SWAP_CHAIN_AVAILABLE

        case StructureTypeDisplayPresentInfo:                                                       { asString = "StructureTypeDisplayPresentInfo";                                                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_XLIB_SURFACE_AVAILABLE

        case StructureTypeXLibSurfaceCreateInfo:                                                    { asString = "StructureTypeXLibSurfaceCreateInfo";                                              break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_XCB_SURFACE_AVAILABLE

        case StructureTypeXcbSurfaceCreateInfo:                                                     { asString = "StructureTypeXcbSurfaceCreateInfo";                                               break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WAYLAND_SURFACE_AVAILABLE

        case StructureTypeWaylandSurfaceCreateInfo:                                                 { asString = "StructureTypeWaylandSurfaceCreateInfo";                                           break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ANDROID_SURFACE_AVAILABLE

        case StructureTypeAndroidSurfaceCreateInfo:                                                 { asString = "StructureTypeAndroidSurfaceCreateInfo";                                           break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WIN32_SURFACE_AVAILABLE

        case StructureTypeWin32SurfaceCreateInfo:                                                   { asString = "StructureTypeWin32SurfaceCreateInfo";                                             break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_REPORT_AVAILABLE

        case StructureTypeDebugReportCallbackCreateInfo:                                            { asString = "StructureTypeDebugReportCallbackCreateInfo";                                      break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_RASTERIZATION_ORDER_AVAILABLE

        case StructureTypePipelineRasterizationStateRasterizationOrderAMD:                          { asString = "StructureTypePipelineRasterizationStateRasterizationOrderAMD";                    break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_MARKER_AVAILABLE

        case StructureTypeDebugMarkerObjectNameInfo:                                                { asString = "StructureTypeDebugMarkerObjectNameInfo";                                          break; }
        case StructureTypeDebugMarkerObjectTagInfo:                                                 { asString = "StructureTypeDebugMarkerObjectTagInfo";                                           break; }
        case StructureTypeDebugMarkerMarkerInfo:                                                    { asString = "StructureTypeDebugMarkerMarkerInfo";                                              break; }

#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE

        case StructureTypeVideoProfile:                                                             { asString = "StructureTypeVideoProfile";                                                       break; }
        case StructureTypeVideoCapabilities:                                                        { asString = "StructureTypeVideoCapabilities";                                                  break; }
        case StructureTypeVideoPictureResource:                                                     { asString = "StructureTypeVideoPictureResource";                                               break; }
        case StructureTypeVideoGetMemoryProperties:                                                 { asString = "StructureTypeVideoGetMemoryProperties";                                           break; }
        case StructureTypeVideoBindMemory:                                                          { asString = "StructureTypeVideoBindMemory";                                                    break; }
        case StructureTypeVideoSessionCreateInfo:                                                   { asString = "StructureTypeVideoSessionCreateInfo";                                             break; }
        case StructureTypeVideoSessionParametersCreateInfo:                                         { asString = "StructureTypeVideoSessionParametersCreateInfo";                                   break; }
        case StructureTypeVideoSessionParametersUpdateInfo:                                         { asString = "StructureTypeVideoSessionParametersUpdateInfo";                                   break; }
        case StructureTypeVideoBeginCodingInfo:                                                     { asString = "StructureTypeVideoBeginCodingInfo";                                               break; }
        case StructureTypeVideoEndCodingInfo:                                                       { asString = "StructureTypeVideoEndCodingInfo";                                                 break; }
        case StructureTypeVideoCodingControlInfo:                                                   { asString = "StructureTypeVideoCodingControlInfo";                                             break; }
        case StructureTypeVideoReferenceSlot:                                                       { asString = "StructureTypeVideoReferenceSlot";                                                 break; }
        case StructureTypeVideoQueueFamilyProperties:                                               { asString = "StructureTypeVideoQueueFamilyProperties";                                         break; }
        case StructureTypeVideoProfiles:                                                            { asString = "StructureTypeVideoProfiles";                                                      break; }
        case StructureTypePhysicalDeviceVideoFormatInfo:                                            { asString = "StructureTypePhysicalDeviceVideoFormatInfo";                                      break; }
        case StructureTypeVideoFormatProperties:                                                    { asString = "StructureTypeVideoFormatProperties";                                              break; }
        case StructureTypeQueueFamilyQueryResultStatusProperties:                                   { asString = "StructureTypeQueueFamilyQueryResultStatusProperties";                             break; }
        case StructureTypeVideoDecodeInfo:                                                          { asString = "StructureTypeVideoDecodeInfo";                                                    break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_AVAILABLE

        case StructureTypeDedicatedAllocationImageCreateInfoNVidia:                              { asString = "StructureTypeDedicatedAllocationImageCreateInfoNVidia";                              break; }
        case StructureTypeDedicatedAllocationBufferCreateInfoNVidia:                             { asString = "StructureTypeDedicatedAllocationBufferCreateInfoNVidia";                             break; }
        case StructureTypeDedicatedAllocationMemoryAllocateInfoNVidia:                           { asString = "StructureTypeDedicatedAllocationMemoryAllocateInfoNVidia";                           break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE

        case StructureTypePhysicalDeviceTransformFeedbackFeatures:                               { asString = "StructureTypePhysicalDeviceTransformFeedbackFeatures";                               break; }
        case StructureTypePhysicalDeviceTransformFeedbackProperties:                             { asString = "StructureTypePhysicalDeviceTransformFeedbackProperties";                             break; }
        case StructureTypePipelineRasterizationStateStreamCreateInfo:                            { asString = "StructureTypePipelineRasterizationStateStreamCreateInfo";                            break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_BINARY_IMPORT_AVAILABLE

        case StructureTypeCudaModuleCreateInfoNVidiaExperimental:                                { asString = "StructureTypeCudaModuleCreateInfoNVidiaExperimental";                                break; }
        case StructureTypeCudaFunctionCreateInfoNVidiaExperimental:                              { asString = "StructureTypeCudaFunctionCreateInfoNVidiaExperimental";                              break; }
        case StructureTypeCudaLaunchInfoNVidiaExperimental:                                      { asString = "StructureTypeCudaLaunchInfoNVidiaExperimental";                                      break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_IMAGE_VIEW_HANDLE_AVAILABLE

        case StructureTypeImageViewHandleInfoNVidiaExperimental:                                 { asString = "StructureTypeImageViewHandleInfoNVidiaExperimental";                                 break; }
        case StructureTypeImageViewAddressPropertiesNVidiaExperimental:                          { asString = "StructureTypeImageViewAddressPropertiesNVidiaExperimental";                          break; }

#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_VIDEO_ENCODE_H264_AVAILABLE

        case StructureTypeVideoEncodeH264Capabilities:                                           { asString = "StructureTypeVideoEncodeH264Capabilities";                                           break; }
        case StructureTypeVideoEncodeH264SessionCreateInfo:                                      { asString = "StructureTypeVideoEncodeH264SessionCreateInfo";                                      break; }
        case StructureTypeVideoEncodeH264SessionParametersCreateInfo:                            { asString = "StructureTypeVideoEncodeH264SessionParametersCreateInfo";                            break; }
        case StructureTypeVideoEncodeH264SessionParametersAddInfo:                               { asString = "StructureTypeVideoEncodeH264SessionParametersAddInfo";                               break; }
        case StructureTypeVideoEncodeH264VCLFrameInfo:                                           { asString = "StructureTypeVideoEncodeH264VCLFrameInfo";                                           break; }
        case StructureTypeVideoEncodeH264DPBSlotInfo:                                            { asString = "StructureTypeVideoEncodeH264DPBSlotInfo";                                            break; }
        case StructureTypeVideoEncodeH264NALUSlice:                                              { asString = "StructureTypeVideoEncodeH264NALUSlice";                                              break; }
        case StructureTypeVideoEncodeH264EmitPictureParameters:                                  { asString = "StructureTypeVideoEncodeH264EmitPictureParameters";                                  break; }
        case StructureTypeVideoEncodeH264Profile:                                                { asString = "StructureTypeVideoEncodeH264Profile";                                                break; }
        case StructureTypeVideoEncodeH264RateControlInfo:                                        { asString = "StructureTypeVideoEncodeH264RateControlInfo";                                        break; }
        case StructureTypeVideoEncodeH264RateControlLayerInfo:                                   { asString = "StructureTypeVideoEncodeH264RateControlLayerInfo";                                   break; }

#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_VIDEO_ENCODE_H265_AVAILABLE

        case StructureTypeVideoEncodeH265Capabilities:                                           { asString = "StructureTypeVideoEncodeH265Capabilities";                                           break; }
        case StructureTypeVideoEncodeH265SessionCreateInfo:                                      { asString = "StructureTypeVideoEncodeH265SessionCreateInfo";                                      break; }
        case StructureTypeVideoEncodeH265SessionParametersCreateInfo:                            { asString = "StructureTypeVideoEncodeH265SessionParametersCreateInfo";                            break; }
        case StructureTypeVideoEncodeH265SessionParametersAddInfo:                               { asString = "StructureTypeVideoEncodeH265SessionParametersAddInfo";                               break; }
        case StructureTypeVideoEncodeH265VCLFrameInfo:                                           { asString = "StructureTypeVideoEncodeH265VCLFrameInfo";                                           break; }
        case StructureTypeVideoEncodeH265DPBSlotInfo:                                            { asString = "StructureTypeVideoEncodeH265DPBSlotInfo";                                            break; }
        case StructureTypeVideoEncodeH265NALUSlice:                                              { asString = "StructureTypeVideoEncodeH265NALUSlice";                                              break; }
        case StructureTypeVideoEncodeH265EmitPictureParameters:                                  { asString = "StructureTypeVideoEncodeH265EmitPictureParameters";                                  break; }
        case StructureTypeVideoEncodeH265Profile:                                                { asString = "StructureTypeVideoEncodeH265Profile";                                                break; }
        case StructureTypeVideoEncodeH265ReferenceLists:                                         { asString = "StructureTypeVideoEncodeH265ReferenceLists";                                         break; }
        case StructureTypeVideoEncodeH265RateControlInfo:                                        { asString = "StructureTypeVideoEncodeH265RateControlInfo";                                        break; }
        case StructureTypeVideoEncodeH265RateControlLayerInfo:                                   { asString = "StructureTypeVideoEncodeH265RateControlLayerInfo";                                   break; }

#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_VIDEO_DECODE_H264_AVAILABLE

        case StructureTypeVideoDecodeH264Capabilities:                                           { asString = "StructureTypeVideoDecodeH264Capabilities";                                           break; }
        case StructureTypeVideoDecodeH264SessionCreateInfo:                                      { asString = "StructureTypeVideoDecodeH264SessionCreateInfo";                                      break; }
        case StructureTypeVideoDecodeH264PictureInfo:                                            { asString = "StructureTypeVideoDecodeH264PictureInfo";                                            break; }
        case StructureTypeVideoDecodeH264MVC:                                                    { asString = "StructureTypeVideoDecodeH264MVC";                                                    break; }
        case StructureTypeVideoDecodeH264Profile:                                                { asString = "StructureTypeVideoDecodeH264Profile";                                                break; }
        case StructureTypeVideoDecodeH264SessionParametersCreateInfo:                            { asString = "StructureTypeVideoDecodeH264SessionParametersCreateInfo";                            break; }
        case StructureTypeVideoDecodeH264SessionParametersAddInfo:                               { asString = "StructureTypeVideoDecodeH264SessionParametersAddInfo";                               break; }
        case StructureTypeVideoDecodeH264DPBSlotInfo:                                            { asString = "StructureTypeVideoDecodeH264DPBSlotInfo";                                            break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_TEXTURE_GATHER_BIAS_LOD_AVAILABLE

        case StructureTypeTextureLODGatherFormatPropertiesAMD:                                   { asString = "StructureTypeTextureLODGatherFormatPropertiesAMD";                                   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE

        case StructureTypeRenderingInfo:                                                         { asString = "StructureTypeRenderingInfo";                                                         break; }
        case StructureTypeRenderingAttachmentInfo:                                               { asString = "StructureTypeRenderingAttachmentInfo";                                               break; }
        case StructureTypePipelineRenderingCreateInfo:                                           { asString = "StructureTypePipelineRenderingCreateInfo";                                           break; }
        case StructureTypePhysicalDeviceDynamicRenderingFeatures:                                { asString = "StructureTypePhysicalDeviceDynamicRenderingFeatures";                                break; }
        case StructureTypeCommandBufferInheritanceRenderingInfo:                                 { asString = "StructureTypeCommandBufferInheritanceRenderingInfo";                                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE

        case StructureTypeRenderingFragmentShadingRateAttachmentInfo:                            { asString = "StructureTypeRenderingFragmentShadingRateAttachmentInfo";                            break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

        case StructureTypeRenderingFragmentDensityMapAttachmentInfo:                             { asString = "StructureTypeRenderingFragmentDensityMapAttachmentInfo";                             break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_AMD_MIXED_ATTACHMENT_SAMPLES_AVAILABLE

        case StructureTypeAttachmentSampleCountInfoAMD:                                          { asString = "StructureTypeAttachmentSampleCountInfoAMD";                                          break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE

        case StructureTypeMutiviewPerViewAttributesInfoNVidiaExperimental:                       { asString = "StructureTypeMutiviewPerViewAttributesInfoNVidiaExperimental";                       break; }
        case StructureTypePhysicalDeviceMultiviewPerViewAttributesPropertiesNVidiaExperimental:  { asString = "StructureTypePhysicalDeviceMultiviewPerViewAttributesPropertiesNVidiaExperimental";  break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_GAMES_PLATFORM_STREAM_DESCRIPTOR_SURFACE_AVAILABLE

        case StructureTypeStreamDescriptorSurfaceCreateInfoGoogle:                               { asString = "StructureTypeStreamDescriptorSurfaceCreateInfoGoogle";                               break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CORNER_SAMPLED_IMAGE_AVAILABLE

        case StructureTypePhysicalDeviceCornerSampledImageFeatures:                              { asString = "StructureTypePhysicalDeviceCornerSampledImageFeatures";                              break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_AVAILABLE

        case StructureTypeExternalMemoryImageCreateInfoNVidia:                                   { asString = "StructureTypeExternalMemoryImageCreateInfoNVidia";                                   break; }
        case StructureTypeExportMemoryAllocateInfoNVidia:                                        { asString = "StructureTypeExportMemoryAllocateInfoNVidia";                                        break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_WIN32_AVAILABLE

        case StructureTypeImportMemoryWin32HandleInfoNVidia:                                     { asString = "StructureTypeImportMemoryWin32HandleInfoNVidia";                                     break; }
        case StructureTypeExportMemoryWin32HandleInfoNVidia:                                     { asString = "StructureTypeExportMemoryWin32HandleInfoNVidia";                                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_WIN32_KEYED_MUTEX_AVAILABLE

        case StructureTypeWin32KeyedMutexAcquireReleaseInfoNVidia:                               { asString = "StructureTypeWin32KeyedMutexAcquireReleaseInfoNVidia";                               break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_FLAGS_AVAILABLE

        case StructureTypeValidationFlags:                                                       { asString = "StructureTypeValidationFlags";                                                       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_NINTENDO_VI_SURFACE_AVAILABLE

        case StructureTypeViSurfaceCreateInfoNVidia:                                             { asString = "StructureTypeViSurfaceCreateInfoNVidia";                                             break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXTURE_COMPRESSION_ASTC_HDR_AVAILABLE

        case StructureTypePhysicalDeviceTextureCompressionASTCHDRFeatures:                       { asString = "StructureTypePhysicalDeviceTextureCompressionASTCHDRFeatures";                       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ASTC_DECODE_MODE_AVAILABLE

        case StructureTypeImageViewASTCDecodeMode:                                               { asString = "StructureTypeImageViewASTCDecodeMode";                                               break; }
        case StructureTypePhysicalDeviceASTCDecodeFeatures:                                      { asString = "StructureTypePhysicalDeviceASTCDecodeFeatures";                                      break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_WIN32_AVAILABLE

        case StructureTypeImportMemoryWin32HandleInfo:                                           { asString = "StructureTypeImportMemoryWin32HandleInfo";                                           break; }
        case StructureTypeExportMemoryWin32HandleInfo:                                           { asString = "StructureTypeExportMemoryWin32HandleInfo";                                           break; }
        case StructureTypeMemoryWin32HandleProperties:                                           { asString = "StructureTypeMemoryWin32HandleProperties";                                           break; }
        case StructureTypeMemoryGetWin32HandleInfo:                                              { asString = "StructureTypeMemoryGetWin32HandleInfo";                                              break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_FD_AVAILABLE

        case StructureTypeImportMemoryFdInfo:                                                    { asString = "StructureTypeImportMemoryFdInfo";                                                    break; }
        case StructureTypeMemoryFdProperties:                                                    { asString = "StructureTypeMemoryFdProperties";                                                    break; }
        case StructureTypeMemoryGetFdInfo:                                                       { asString = "StructureTypeMemoryGetFdInfo";                                                       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WIN32_KEYED_MUTEX_AVAILABLE

        case StructureTypeWin32KeyedMutexAcquireReleaseInfo:                                     { asString = "StructureTypeWin32KeyedMutexAcquireReleaseInfo";                                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_WIN32_AVAILABLE

        case StructureTypeImportSemaphoreWin32HandleInfo:                                        { asString = "StructureTypeImportSemaphoreWin32HandleInfo";                                        break; }
        case StructureTypeExportSemaphoreWin32HandleInfo:                                        { asString = "StructureTypeExportSemaphoreWin32HandleInfo";                                        break; }
        case StructureTypeD3D12FenceSubmitInfo:                                                  { asString = "StructureTypeD3D12FenceSubmitInfo";                                                  break; }
        case StructureTypeSemaphoreGetWin32HandleInfo:                                           { asString = "StructureTypeSemaphoreGetWin32HandleInfo";                                           break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_FD_AVAILABLE

        case StructureTypeImportSemaphoreFdInfo:                                                 { asString = "StructureTypeImportSemaphoreFdInfo";                                                 break; }
        case StructureTypeSemaphoreGetFdInfo:                                                    { asString = "StructureTypeSemaphoreGetFdInfo";                                                    break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PUSH_DESCRIPTOR_AVAILABLE

        case StructureTypePhysicalDevicePushDescriptorProperties:                                { asString = "StructureTypePhysicalDevicePushDescriptorProperties";                                break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE

        case StructureTypeCommandBufferInheritanceConditionalRenderingInfo:                      { asString = "StructureTypeCommandBufferInheritanceConditionalRenderingInfo";                      break; }
        case StructureTypePhysicalDeviceConditionalRenderingFeatures:                            { asString = "StructureTypePhysicalDeviceConditionalRenderingFeatures";                            break; }
        case StructureTypeConditionalRenderingBeginInfo:                                         { asString = "StructureTypeConditionalRenderingBeginInfo";                                         break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_INCREMENTAL_PRESENT_AVAILABLE

        case StructureTypePresentRegions:                                                        { asString = "StructureTypePresentRegions";                                                        break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CLIP_SPACE_W_SCALING_AVAILABLE

        case StructureTypePipelineViewportWScalingStateCreateInfoNVidia:                         { asString = "StructureTypePipelineViewportWScalingStateCreateInfoNVidia";                         break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISPLAY_SURFACE_COUNTER_AVAILABLE

        case StructureTypeSurfaceCapabilities2:                                                  { asString = "StructureTypeSurfaceCapabilities2";                                                  break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISPLAY_CONTROL_AVAILABLE

        case StructureTypeDisplayPowerInfo:                                                      { asString = "StructureTypeDisplayPowerInfo";                                                      break; }
        case StructureTypeDeviceEventInfo:                                                       { asString = "StructureTypeDeviceEventInfo";                                                       break; }
        case StructureTypeDisplayEventInfo:                                                      { asString = "StructureTypeDisplayEventInfo";                                                      break; }
        case StructureTypeSwapchainCounterCreateInfo:                                            { asString = "StructureTypeSwapchainCounterCreateInfo";                                            break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_DISPLAY_TIMING_AVAILABLE

        case StructureTypePresentTimesInfoGoogle:                                                { asString = "StructureTypePresentTimesInfoGoogle";                                                break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_VIEWPORT_SWIZZLE_AVAILABLE

        case StructureTypePipelineViewportSwizzleStateCreateInfoNVidia:                          { asString = "StructureTypePipelineViewportSwizzleStateCreateInfoNVidia";                          break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISCARD_RECTANGLES_AVAILABLE

        case StructureTypePhysicalDeviceDiscardRectangleProperties:                              { asString = "StructureTypePhysicalDeviceDiscardRectangleProperties";                              break; }
        case StructureTypePipelineDiscardRectangleStateCreateInfo:                               { asString = "StructureTypePipelineDiscardRectangleStateCreateInfo";                               break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONSERVATIVE_RASTERIZATION_AVAILABLE

        case StructureTypePhysicalDeviceConservativeRasterizationProperties:                     { asString = "StructureTypePhysicalDeviceConservativeRasterizationProperties";                     break; }
        case StructureTypePipelineRasterizationConservativeStateCreateInfo:                      { asString = "StructureTypePipelineRasterizationConservativeStateCreateInfo";                      break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_ENABLE_AVAILABLE

        case StructureTypePhysicalDeviceDepthClipEnableFeatures:                                 { asString = "StructureTypePhysicalDeviceDepthClipEnableFeatures";                                 break; }
        case StructureTypePipelineRasterizationDepthClipStateCreateInfo:                         { asString = "StructureTypePipelineRasterizationDepthClipStateCreateInfo";                         break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HDR_METADATA_AVAILABLE

        case StructureTypeHDRMetadata:                                                           { asString = "StructureTypeHDRMetadata";                                                           break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHARED_PRESENTABLE_IMAGE_AVAILABLE

        case StructureTypeSharedPresentSurfaceCapabilities:                                      { asString = "StructureTypeSharedPresentSurfaceCapabilities";                                      break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_WIN32_AVAILABLE

        case StructureTypeImportFenceWin32HandleInfo:                                            { asString = "StructureTypeImportFenceWin32HandleInfo";                                            break; }
        case StructureTypeExportFenceWin32HandleInfo:                                            { asString = "StructureTypeExportFenceWin32HandleInfo";                                            break; }
        case StructureTypeFenceGetWin32HandleInfo:                                               { asString = "StructureTypeFenceGetWin32HandleInfo";                                               break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_FD_AVAILABLE

        case StructureTypeImportFenceFdInfo:                                                     { asString = "StructureTypeImportFenceFdInfo";                                                     break; }
        case StructureTypeFenceGetFdInfo:                                                        { asString = "StructureTypeFenceGetFdInfo";                                                        break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

        case StructureTypePhysicalDevicePerformanceQueryFeatures:                                { asString = "StructureTypePhysicalDevicePerformanceQueryFeatures";                                break; }
        case StructureTypePhysicalDevicePerformanceQueryProperties:                              { asString = "StructureTypePhysicalDevicePerformanceQueryProperties";                              break; }
        case StructureTypeQueryPoolPerformanceCreateInfo:                                        { asString = "StructureTypeQueryPoolPerformanceCreateInfo";                                        break; }
        case StructureTypePerformanceQuerySubmitInfo:                                            { asString = "StructureTypePerformanceQuerySubmitInfo";                                            break; }
        case StructureTypeAcquireProfilingLockInfo:                                              { asString = "StructureTypeAcquireProfilingLockInfo";                                              break; }
        case StructureTypePerformanceCounter:                                                    { asString = "StructureTypePerformanceCounter";                                                    break; }
        case StructureTypePerformanceCounterDescription:                                         { asString = "StructureTypePerformanceCounterDescription";                                         break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_GET_SURFACE_CAPABILITIES_AVAILABLE

        case StructureTypePhysicalDeviceSurfaceInfo:                                             { asString = "StructureTypePhysicalDeviceSurfaceInfo";                                             break; }
        case StructureTypeSurfaceCapabilities:                                                   { asString = "StructureTypeSurfaceCapabilities";                                                   break; }
        case StructureTypeSurfaceFormat:                                                         { asString = "StructureTypeSurfaceFormat";                                                         break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_GET_DISPLAY_PROPERTIES_AVAILABLE

        case StructureTypeDisplayProperties:                                                     { asString = "StructureTypeDisplayProperties";                                                     break; }
        case StructureTypeDisplayPlaneProperties:                                                { asString = "StructureTypeDisplayPlaneProperties";                                                break; }
        case StructureTypeDisplayModeProperties:                                                 { asString = "StructureTypeDisplayModeProperties";                                                 break; }
        case StructureTypeDisplayPlaneInfo:                                                      { asString = "StructureTypeDisplayPlaneInfo";                                                      break; }
        case StructureTypeDisplayPlaneCapabilities:                                              { asString = "StructureTypeDisplayPlaneCapabilities";                                              break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_APPLE_MOLTEN_VULKAN_IOS_SURFACE_AVAILABLE

        case StructureTypeIOSSurfaceCreateInfoApple:                                             { asString = "StructureTypeIOSSurfaceCreateInfoApple";                                             break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_APPLE_MOLTEN_VULKAN_MACOS_SURFACE_AVAILABLE

        case StructureTypeMacOSSurfaceCreateInfoApple:                                           { asString = "StructureTypeMacOSSurfaceCreateInfoApple";                                           break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_UTILS_AVAILABLE

        case StructureTypeDebugUtilsObjectNameInfo:                                              { asString = "StructureTypeDebugUtilsObjectNameInfo";                                              break; }
        case StructureTypeDebugUtilsObjectTagInfo:                                               { asString = "StructureTypeDebugUtilsObjectTagInfo";                                               break; }
        case StructureTypeDebugUtilsLabel:                                                       { asString = "StructureTypeDebugUtilsLabel";                                                       break; }
        case StructureTypeDebugUtilsMessengerCallbackData:                                       { asString = "StructureTypeDebugUtilsMessengerCallbackData";                                       break; }
        case StructureTypeDebugUtilsMessengerCreateInfo:                                         { asString = "StructureTypeDebugUtilsMessengerCreateInfo";                                         break; }

#endif

#if __C_ENG_VULKAN_API_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_AVAILABLE

        case StructureTypeAndroidHardwareBufferUsageGoogle:                                      { asString = "StructureTypeAndroidHardwareBufferUsageGoogle";                                      break; }
        case StructureTypeAndroidHardwareBufferPropertiesGoogle:                                 { asString = "StructureTypeAndroidHardwareBufferPropertiesGoogle";                                 break; }
        case StructureTypeAndroidHardwareBufferFormatPropertiesGoogle:                           { asString = "StructureTypeAndroidHardwareBufferFormatPropertiesGoogle";                           break; }
        case StructureTypeImportAndroidHardwareBufferInfoGoogle:                                 { asString = "StructureTypeImportAndroidHardwareBufferInfoGoogle";                                 break; }
        case StructureTypeMemoryGetAndroidHardwareBufferInfoGoogle:                              { asString = "StructureTypeMemoryGetAndroidHardwareBufferInfoGoogle";                              break; }
        case StructureTypeExternalFormatGoogle:                                                  { asString = "StructureTypeExternalFormatGoogle";                                                  break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FORMAT_FEATURE_FLAGS_AVAILABLE && __C_ENG_VULKAN_API_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_AVAILABLE

        case StructureTypeAndroidHardwareBufferFormatPropertiesGoogle:                           { asString = "StructureTypeAndroidHardwareBufferFormatPropertiesGoogle";                           break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE

        case StructureTypePhysicalDeviceInlineUniformBlockFeatures:                              { asString = "StructureTypePhysicalDeviceInlineUniformBlockFeatures";                              break; }
        case StructureTypePhysicalDeviceInlineUniformBlockProperties:                            { asString = "StructureTypePhysicalDeviceInlineUniformBlockProperties";                            break; }
        case StructureTypeWriteDescriptorSetInlineUniformBlock:                                  { asString = "StructureTypeWriteDescriptorSetInlineUniformBlock";                                  break; }
        case StructureTypeDescriptorPoolInlineUniformBlockCreateInfo:                            { asString = "StructureTypeDescriptorPoolInlineUniformBlockCreateInfo";                            break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE

        case StructureTypeSampleLocationsInfo:                                                   { asString = "StructureTypeSampleLocationsInfo";                                                   break; }
        case StructureTypeRenderPassSampleLocationsBeginInfo:                                    { asString = "StructureTypeRenderPassSampleLocationsBeginInfo";                                    break; }
        case StructureTypePipelineSampleLocationsStateCreateInfo:                                { asString = "StructureTypePipelineSampleLocationsStateCreateInfo";                                break; }
        case StructureTypePhysicalDeviceSampleLocationsProperties:                               { asString = "StructureTypePhysicalDeviceSampleLocationsProperties";                               break; }
        case StructureTypeMultisampleProperties:                                                 { asString = "StructureTypeMultisampleProperties";                                                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE

        case StructureTypePhysicalDeviceBlendOperationAdvancedFeatures:                          { asString = "StructureTypePhysicalDeviceBlendOperationAdvancedFeatures";                          break; }
        case StructureTypePhysicalDeviceBlendOperationAdvancedProperties:                        { asString = "StructureTypePhysicalDeviceBlendOperationAdvancedProperties";                        break; }
        case StructureTypePipelineColorBlendAdvancedStateCreateInfo:                             { asString = "StructureTypePipelineColorBlendAdvancedStateCreateInfo";                             break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_COVERAGE_TO_COLOR_AVAILABLE

        case StructureTypePipelineCoverageToColorStateCreateInfoNVidia:                          { asString = "StructureTypePipelineCoverageToColorStateCreateInfoNVidia";                          break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE

        case StructureTypeWriteDescriptorSetAccelerationStructure:                               { asString = "StructureTypeWriteDescriptorSetAccelerationStructure";                               break; }
        case StructureTypeAccelerationStructureBuildGeometryInfo:                                { asString = "StructureTypeAccelerationStructureBuildGeometryInfo";                                break; }
        case StructureTypeAccelerationStructureDeviceAddressInfo:                                { asString = "StructureTypeAccelerationStructureDeviceAddressInfo";                                break; }
        case StructureTypeAccelerationStructureGeometryAABBSData:                                { asString = "StructureTypeAccelerationStructureGeometryAABBSData";                                break; }
        case StructureTypeAccelerationStructureGeometryInstancesData:                            { asString = "StructureTypeAccelerationStructureGeometryInstancesData";                            break; }
        case StructureTypeAccelerationStructureGeometryTrianglesData:                            { asString = "StructureTypeAccelerationStructureGeometryTrianglesData";                            break; }
        case StructureTypeAccelerationStructureGeometry:                                         { asString = "StructureTypeAccelerationStructureGeometry";                                         break; }
        case StructureTypeAccelerationStructureVersionInfo:                                      { asString = "StructureTypeAccelerationStructureVersionInfo";                                      break; }
        case StructureTypeCopyAccelerationStructureInfo:                                         { asString = "StructureTypeCopyAccelerationStructureInfo";                                         break; }
        case StructureTypeCopyAccelerationStructureToMemoryInfo:                                 { asString = "StructureTypeCopyAccelerationStructureToMemoryInfo";                                 break; }
        case StructureTypeCopyMemoryToAccelerationStructureInfo:                                 { asString = "StructureTypeCopyMemoryToAccelerationStructureInfo";                                 break; }
        case StructureTypePhysicalDeviceAccelerationStructureFeatures:                           { asString = "StructureTypePhysicalDeviceAccelerationStructureFeatures";                           break; }
        case StructureTypePhysicalDeviceAccelerationStructureProperties:                         { asString = "StructureTypePhysicalDeviceAccelerationStructureProperties";                         break; }
        case StructureTypeAccelerationStructureCreateInfo:                                       { asString = "StructureTypeAccelerationStructureCreateInfo";                                       break; }
        case StructureTypeAccelerationStructureBuildSizesInfo:                                   { asString = "StructureTypeAccelerationStructureBuildSizesInfo";                                   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE

        case StructureTypePhysicalDeviceRayTracingPipelineFeatures:                              { asString = "StructureTypePhysicalDeviceRayTracingPipelineFeatures";                              break; }
        case StructureTypePhysicalDeviceRayTracingPipelineProperties:                            { asString = "StructureTypePhysicalDeviceRayTracingPipelineProperties";                            break; }
        case StructureTypeRayTracingPipelineCreateInfo:                                          { asString = "StructureTypeRayTracingPipelineCreateInfo";                                          break; }
        case StructureTypeRayTracingShaderGroupCreateInfo:                                       { asString = "StructureTypeRayTracingShaderGroupCreateInfo";                                       break; }
        case StructureTypeRayTracingPipelineInterfaceCreateInfo:                                 { asString = "StructureTypeRayTracingPipelineInterfaceCreateInfo";                                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_QUERY_AVAILABLE

        case StructureTypePhysicalDeviceRayQueryFeatures:                                        { asString = "StructureTypePhysicalDeviceRayQueryFeatures";                                        break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAMEBUFFER_MIXED_SAMPLES_AVAILABLE

        case StructureTypePipelineCoverageModulationStateCreateInfoNVidia:                       { asString = "StructureTypePipelineCoverageModulationStateCreateInfoNVidia";                       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE

        case StructureTypePhysicalDeviceShaderSmBuiltinsFeaturesNVidia:                          { asString = "StructureTypePhysicalDeviceShaderSmBuiltinsFeaturesNVidia";                          break; }
        case StructureTypePhysicalDeviceShaderSmBuiltinsPropertiesNVidia:                        { asString = "StructureTypePhysicalDeviceShaderSmBuiltinsPropertiesNVidia";                        break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_DRM_FORMAT_MODIFIER_AVAILABLE

        case StructureTypeDRMFormatModifierPropertiesList:                                       { asString = "StructureTypeDRMFormatModifierPropertiesList";                                       break; }
        case StructureTypePhysicalDeviceImageDRMFormatModifierInfo:                              { asString = "StructureTypePhysicalDeviceImageDRMFormatModifierInfo";                              break; }
        case StructureTypeImageDRMFormatModifierListCreateInfo:                                  { asString = "StructureTypeImageDRMFormatModifierListCreateInfo";                                  break; }
        case StructureTypeImageDRMFormatModifierExplicitCreateInfo:                              { asString = "StructureTypeImageDRMFormatModifierExplicitCreateInfo";                              break; }
        case StructureTypeImageDRMFormatModifierProperties:                                      { asString = "StructureTypeImageDRMFormatModifierProperties";                                      break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_DRM_FORMAT_MODIFIER_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FORMAT_FEATURE_FLAGS_AVAILABLE

        case StructureTypeDRMFormatModifierPropertiesList2:                                      { asString = "StructureTypeDRMFormatModifierPropertiesList2";                                      break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_CACHE_AVAILABLE

        case StructureTypeValidationCacheCreateInfo:                                             { asString = "StructureTypeValidationCacheCreateInfo";                                             break; }
        case StructureTypeShaderModuleValidationCacheCreateInfo:                                 { asString = "StructureTypeShaderModuleValidationCacheCreateInfo";                                 break; }

#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE

        case StructureTypePhysicalDevicePortabilitySubsetFeatures:                               { asString = "StructureTypePhysicalDevicePortabilitySubsetFeatures";                               break; }
        case StructureTypePhysicalDevicePortabilitySubsetProperties:                             { asString = "StructureTypePhysicalDevicePortabilitySubsetProperties";                             break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE

        case StructureTypePipelineViewportShadingRateImageStateCreateInfoNVidia:                 { asString = "StructureTypePipelineViewportShadingRateImageStateCreateInfoNVidia";                 break; }
        case StructureTypePhysicalDeviceShadingRateImageFeaturesNVidia:                          { asString = "StructureTypePhysicalDeviceShadingRateImageFeaturesNVidia";                          break; }
        case StructureTypePhysicalDeviceShadingRateImagePropertiesNVidia:                        { asString = "StructureTypePhysicalDeviceShadingRateImagePropertiesNVidia";                        break; }
        case StructureTypePipelineViewportCoarseSampleOrderStateCreateInfoNVidia:                { asString = "StructureTypePipelineViewportCoarseSampleOrderStateCreateInfoNVidia";                break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE

        case StructureTypeRayTracingPipelineCreateInfoNVidia:                                    { asString = "StructureTypeRayTracingPipelineCreateInfoNVidia";                                    break; }
        case StructureTypeAccelerationStructureCreateInfoNVidia:                                 { asString = "StructureTypeAccelerationStructureCreateInfoNVidia";                                 break; }
        case StructureTypeGeometryNVidia:                                                        { asString = "StructureTypeGeometryNVidia";                                                        break; }
        case StructureTypeGeometryTrianglesNVidia:                                               { asString = "StructureTypeGeometryTrianglesNVidia";                                               break; }
        case StructureTypeGeometryAABBNVidia:                                                    { asString = "StructureTypeGeometryAABBNVidia";                                                    break; }
        case StructureTypeBindAccelerationStructureMemoryInfoNVidia:                             { asString = "StructureTypeBindAccelerationStructureMemoryInfoNVidia";                             break; }
        case StructureTypeWriteDescriptorSetAccelerationStructureNVidia:                         { asString = "StructureTypeWriteDescriptorSetAccelerationStructureNVidia";                         break; }
        case StructureTypeAccelerationStructureMemoryRequirementsInfoNVidia:                     { asString = "StructureTypeAccelerationStructureMemoryRequirementsInfoNVidia";                     break; }
        case StructureTypePhysicalDeviceRayTracingPropertiesNVidia:                              { asString = "StructureTypePhysicalDeviceRayTracingPropertiesNVidia";                              break; }
        case StructureTypeRayTracingShaderGroupCreateInfoNVidia:                                 { asString = "StructureTypeRayTracingShaderGroupCreateInfoNVidia";                                 break; }
        case StructureTypeAccelerationStructureInfoNVidia:                                       { asString = "StructureTypeAccelerationStructureInfoNVidia";                                       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_REPRESENTATIVE_FRAGMENT_TEST_AVAILABLE

        case StructureTypePhysicalDeviceRepresentativeFragmentTestFeaturesNVidia:                { asString = "StructureTypePhysicalDeviceRepresentativeFragmentTestFeaturesNVidia";                break; }
        case StructureTypePipelineRepresentativeFragmentTestStateCreateInfoNVidia:               { asString = "StructureTypePipelineRepresentativeFragmentTestStateCreateInfoNVidia";               break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FILTER_CUBIC_AVAILABLE

        case StructureTypePhysicalDeviceImageViewImageFormatInfo:                                { asString = "StructureTypePhysicalDeviceImageViewImageFormatInfo";                                break; }
        case StructureTypeFilterCubicImageViewImageFormatProperties:                             { asString = "StructureTypeFilterCubicImageViewImageFormatProperties";                             break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_AVAILABLE

        case StructureTypeDeviceQueueGlobalPriorityCreateInfo:                                   { asString = "StructureTypeDeviceQueueGlobalPriorityCreateInfo";                                   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTERNAL_MEMORY_HOST_AVAILABLE

        case StructureTypeImportMemoryHostPointerInfo:                                           { asString = "StructureTypeImportMemoryHostPointerInfo";                                           break; }
        case StructureTypeMemoryHostPointerProperties:                                           { asString = "StructureTypeMemoryHostPointerProperties";                                           break; }
        case StructureTypePhysicalDeviceExternalMemoryHostProperties:                            { asString = "StructureTypePhysicalDeviceExternalMemoryHostProperties";                            break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_CLOCK_AVAILABLE

        case StructureTypePhysicalDeviceShaderClockFeatures:                                     { asString = "StructureTypePhysicalDeviceShaderClockFeatures";                                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_PIPELINE_COMPILER_CONTROL_AVAILABLE

        case StructureTypePipelineCompilerControlCreateInfoAMD:                                  { asString = "StructureTypePipelineCompilerControlCreateInfoAMD";                                  break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CALIBRATED_TIMESTAMPS_AVAILABLE

        case StructureTypeCalibratedTimestampInfo:                                               { asString = "StructureTypeCalibratedTimestampInfo";                                               break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_AVAILABLE

        case StructureTypePhysicalDeviceShaderCorePropertiesAMD:                                 { asString = "StructureTypePhysicalDeviceShaderCorePropertiesAMD";                                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_2_AVAILABLE

        case StructureTypePhysicalDeviceShaderCoreProperties2AMD:                                { asString = "StructureTypePhysicalDeviceShaderCoreProperties2AMD";                                break; }

#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_VIDEO_DECODE_H265_AVAILABLE

        case StructureTypeVideoDecodeH265Capabilities:                                           { asString = "StructureTypeVideoDecodeH265Capabilities";                                           break; }
        case StructureTypeVideoDecodeH265SessionCreateInfo:                                      { asString = "StructureTypeVideoDecodeH265SessionCreateInfo";                                      break; }
        case StructureTypeVideoDecodeH265SessionParametersCreateInfo:                            { asString = "StructureTypeVideoDecodeH265SessionParametersCreateInfo";                            break; }
        case StructureTypeVideoDecodeH265SessionParametersAddInfo:                               { asString = "StructureTypeVideoDecodeH265SessionParametersAddInfo";                               break; }
        case StructureTypeVideoDecodeH265SessionProfile:                                         { asString = "StructureTypeVideoDecodeH265SessionProfile";                                         break; }
        case StructureTypeVideoDecodeH265SessionPictureInfo:                                     { asString = "StructureTypeVideoDecodeH265SessionPictureInfo";                                     break; }
        case StructureTypeVideoDecodeH265SessionDPBSlotInfo:                                     { asString = "StructureTypeVideoDecodeH265SessionDPBSlotInfo";                                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_MEMORY_OVERALLOCATION_BEHAVIOUR_AVAILABLE

        case StructureTypeDeviceMemoryOverAllocationCreateInfoAMD:                               { asString = "StructureTypeDeviceMemoryOverAllocationCreateInfoAMD";                               break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE

        case StructureTypePhysicalDeviceVertexAttributeDivisorFeatures:                          { asString = "StructureTypePhysicalDeviceVertexAttributeDivisorFeatures";                          break; }
        case StructureTypePhysicalDeviceVertexAttributeDivisorProperties:                        { asString = "StructureTypePhysicalDeviceVertexAttributeDivisorProperties";                        break; }
        case StructureTypePipelineVertexInputDivisorStateCreateInfo:                             { asString = "StructureTypePipelineVertexInputDivisorStateCreateInfo";                             break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_GAMES_PLATFORM_FRAME_TOKEN_AVAILABLE

        case StructureTypePresentFrameTokenGoogle:                                               { asString = "StructureTypePresentFrameTokenGoogle";                                               break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_FEEDBACK_AVAILABLE

        case StructureTypePipelineCreationFeedbackCreateInfo:                                    { asString = "StructureTypePipelineCreationFeedbackCreateInfo";                                    break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COMPUTE_SHADER_DERIVATIVES_AVAILABLE

        case StructureTypePhysicalDeviceComputeShaderDerivativesFeaturesNVidia:                  { asString = "StructureTypePhysicalDeviceComputeShaderDerivativesFeaturesNVidia";                  break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE

        case StructureTypePhysicalDeviceMeshShaderFeaturesNVidia:                                { asString = "StructureTypePhysicalDeviceMeshShaderFeaturesNVidia";                                break; }
        case StructureTypePhysicalDeviceMeshShaderPropertiesNVidia:                              { asString = "StructureTypePhysicalDeviceMeshShaderPropertiesNVidia";                              break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADER_BARYCENTRIC_AVAILABLE

        case StructureTypePhysicalDeviceFragmentShaderBarycentricFeaturesNVidia:                 { asString = "StructureTypePhysicalDeviceFragmentShaderBarycentricFeaturesNVidia";                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_IMAGE_FOOTPRINT_AVAILABLE

        case StructureTypePhysicalDeviceShaderImageFootprintFeaturesNVidia:                      { asString = "StructureTypePhysicalDeviceShaderImageFootprintFeaturesNVidia";                      break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SCISSOR_EXCLUSIVE_AVAILABLE

        case StructureTypePipelineViewportExclusiveScissorStateCreateInfoNVidia:                 { asString = "StructureTypePipelineViewportExclusiveScissorStateCreateInfoNVidia";                 break; }
        case StructureTypePhysicalDeviceExclusiveScissorFeaturesNVidia:                          { asString = "StructureTypePhysicalDeviceExclusiveScissorFeaturesNVidia";                          break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTIC_CHECKPOINTS_AVAILABLE

        case StructureTypeCheckpointDataNVidia:                                                  { asString = "StructureTypeCheckpointDataNVidia";                                                  break; }
        case StructureTypeQueueFamilyCheckpointPropertiesNVidia:                                 { asString = "StructureTypeQueueFamilyCheckpointPropertiesNVidia";                                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_SHADER_INTEGER_FUNCTIONS_AVAILABLE

        case StructureTypePhysicalDeviceShaderIntegerFunctionFeaturesIntel:                      { asString = "StructureTypePhysicalDeviceShaderIntegerFunctionFeaturesIntel";                      break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE

        case StructureTypeQueryPoolPerformanceQueryCreateInfoIntel:                              { asString = "StructureTypeQueryPoolPerformanceQueryCreateInfoIntel";                              break; }
        case StructureTypeInitializePerformanceAPIInfoIntel:                                     { asString = "StructureTypeInitializePerformanceAPIInfoIntel";                                     break; }
        case StructureTypePerformanceMarkerInfoIntel:                                            { asString = "StructureTypePerformanceMarkerInfoIntel";                                            break; }
        case StructureTypePerformanceStreamMarkerInfoIntel:                                      { asString = "StructureTypePerformanceStreamMarkerInfoIntel";                                      break; }
        case StructureTypePerformanceOverrideInfoIntel:                                          { asString = "StructureTypePerformanceOverrideInfoIntel";                                          break; }
        case StructureTypePerformanceConfigurationAcquireInfoIntel:                              { asString = "StructureTypePerformanceConfigurationAcquireInfoIntel";                              break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PCI_BUS_INFO_AVAILABLE

        case StructureTypePhysicalDevicePCIBusInfoProperties:                                    { asString = "StructureTypePhysicalDevicePCIBusInfoProperties";                                    break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_DISPLAY_NATIVE_HDR_AVAILABLE

        case StructureTypeDisplayNativeHDRSurfaceCapabilitiesAMD:                                { asString = "StructureTypeDisplayNativeHDRSurfaceCapabilitiesAMD";                                break; }
        case StructureTypeSwachainDisplayNativeHDRCreateInfoAMD:                                 { asString = "StructureTypeSwachainDisplayNativeHDRCreateInfoAMD";                                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_IMAGEPIPE_SURFACE_AVAILABLE

        case StructureTypeImagepipeSurfaceCreateInfoGoogle:                                      { asString = "StructureTypeImagepipeSurfaceCreateInfoGoogle";                                      break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_TERMINATE_INVOCATION_AVAILABLE

        case StructureTypePhysicalDeviceShaderTerminateInvocationFeatures:                       { asString = "StructureTypePhysicalDeviceShaderTerminateInvocationFeatures";                       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_METAL_SURFACE_AVAILABLE

        case StructureTypeMetalSurfaceCreateInfo:                                                { asString = "StructureTypeMetalSurfaceCreateInfo";                                                break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

        case StructureTypePhysicalDeviceFragmentDensityMapFeatures:                              { asString = "StructureTypePhysicalDeviceFragmentDensityMapFeatures";                              break; }
        case StructureTypePhysicalDeviceFragmentDensityMapProperties:                            { asString = "StructureTypePhysicalDeviceFragmentDensityMapProperties";                            break; }
        case StructureTypeRenderPassFragmentDensityMapCreateInfo:                                { asString = "StructureTypeRenderPassFragmentDensityMapCreateInfo";                                break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE

        case StructureTypePhysicalDeviceSubgroupSizeControlFeatures:                             { asString = "StructureTypePhysicalDeviceSubgroupSizeControlFeatures";                             break; }
        case StructureTypePhysicalDeviceSubgroupSizeControlProperties:                           { asString = "StructureTypePhysicalDeviceSubgroupSizeControlProperties";                           break; }
        case StructureTypePipelineShaderStageRequiredSubgroupSizeCreateInfo:                     { asString = "StructureTypePipelineShaderStageRequiredSubgroupSizeCreateInfo";                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE

        case StructureTypePhysicalDeviceFragmentShadingRateFeatures:                             { asString = "StructureTypePhysicalDeviceFragmentShadingRateFeatures";                             break; }
        case StructureTypePhysicalDeviceFragmentShadingRateProperties:                           { asString = "StructureTypePhysicalDeviceFragmentShadingRateProperties";                           break; }
        case StructureTypePhysicalDeviceFragmentShadingRate:                                     { asString = "StructureTypePhysicalDeviceFragmentShadingRate";                                     break; }
        case StructureTypePipelineFragmentShadingRateStateCreateInfo:                            { asString = "StructureTypePipelineFragmentShadingRateStateCreateInfo";                            break; }
        case StructureTypeFragmentShadingRateAttachmentInfo:                                     { asString = "StructureTypeFragmentShadingRateAttachmentInfo";                                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_DEVICE_COHERENT_MEMORY_AVAILABLE

        case StructureTypePhysicalDeviceCoherentMemoryFeaturesAMD:                               { asString = "StructureTypePhysicalDeviceCoherentMemoryFeaturesAMD";                               break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_BUDGET_AVAILABLE

        case StructureTypePhysicalDeviceMemoryBudgetProperties:                                  { asString = "StructureTypePhysicalDeviceMemoryBudgetProperties";                                  break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_PRIORITY_AVAILABLE

        case StructureTypePhysicalDeviceMemoryPriorityFeatures:                                  { asString = "StructureTypePhysicalDeviceMemoryPriorityFeatures";                                  break; }
        case StructureTypeMemoryPriorityAllocateInfo:                                            { asString = "StructureTypeMemoryPriorityAllocateInfo";                                            break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_PROTECTED_CAPABILITIES_AVAILABLE

        case StructureTypeSurfaceProtectedCapabilities:                                          { asString = "StructureTypeSurfaceProtectedCapabilities";                                          break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_IMAGE_ALIASING_AVAILABLE

        case StructureTypePhysicalDeviceDedicatedAllocationImageAliasingFeaturesNVidia:          { asString = "StructureTypePhysicalDeviceDedicatedAllocationImageAliasingFeaturesNVidia";          break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BUFFER_DEVICE_ADDRESS_AVAILABLE

        case StructureTypePhysicalDeviceBufferDeviceAddressFeaturesExt:                          { asString = "StructureTypePhysicalDeviceBufferDeviceAddressFeaturesExt";                          break; }
        case StructureTypeBufferDeviceAddressCreateInfoExt:                                      { asString = "StructureTypeBufferDeviceAddressCreateInfoExt";                                      break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TOOLING_INFO_AVAILABLE

        case StructureTypePhysicalDeviceToolProperties:                                          { asString = "StructureTypePhysicalDeviceToolProperties";                                          break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_FEATURES_AVAILABLE

        case StructureTypeValidationFeatures:                                                    { asString = "StructureTypeValidationFeatures";                                                    break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_WAIT_AVAILABLE

        case StructureTypePhysicalDevicePresentWaitFeatures:                                     { asString = "StructureTypePhysicalDevicePresentWaitFeatures";                                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE

        case StructureTypePhysicalDeviceCooperativeMatrixFeaturesNVidia:                         { asString = "StructureTypePhysicalDeviceCooperativeMatrixFeaturesNVidia";                         break; }
        case StructureTypePhysicalDeviceCooperativeMatrixPropertiesNVidia:                       { asString = "StructureTypePhysicalDeviceCooperativeMatrixPropertiesNVidia";                       break; }
        case StructureTypeCooperativeMatrixPropertiesNVidia:                                     { asString = "StructureTypeCooperativeMatrixPropertiesNVidia";                                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COVERAGE_REDUCTION_MODE_AVAILABLE

        case StructureTypePhysicalDeviceCoverageReductionModeFeaturesNVidia:                     { asString = "StructureTypePhysicalDeviceCoverageReductionModeFeaturesNVidia";                     break; }
        case StructureTypePipelineCoverageReductionStateCreateInfoNVidia:                        { asString = "StructureTypePipelineCoverageReductionStateCreateInfoNVidia";                        break; }
        case StructureTypeFramebufferMixedSamplesCombinationNVidia:                              { asString = "StructureTypeFramebufferMixedSamplesCombinationNVidia";                              break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_SHADER_INTERLOCK_AVAILABLE

        case StructureTypePhysicalDeviceFragmentShaderInterlockFeatures:                         { asString = "StructureTypePhysicalDeviceFragmentShaderInterlockFeatures";                         break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_IMAGE_ARRAYS_AVAILABLE

        case StructureTypePhysicalDeviceYCBCRImageArraysFeatures:                                { asString = "StructureTypePhysicalDeviceYCBCRImageArraysFeatures";                                break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE

        case StructureTypePhysicalDeviceProvokingVertexFeatures:                                 { asString = "StructureTypePhysicalDeviceProvokingVertexFeatures";                                 break; }
        case StructureTypePhysicalDeviceProvokingVertexProperties:                               { asString = "StructureTypePhysicalDeviceProvokingVertexProperties";                               break; }
        case StructureTypePipelineRasterizationProvokingVertexStateCreateInfo:                   { asString = "StructureTypePipelineRasterizationProvokingVertexStateCreateInfo";                   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FULL_SCREEN_EXCLUSIVE_AVAILABLE

        case StructureTypeSurfaceFullScreenExclusiveInfo:                                        { asString = "StructureTypeSurfaceFullScreenExclusiveInfo";                                        break; }
        case StructureTypeSurfaceCapabilitiesFullScreenExclusive:                                { asString = "StructureTypeSurfaceCapabilitiesFullScreenExclusive";                                break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WIN32_SURFACE_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_FULL_SCREEN_EXCLUSIVE_AVAILABLE

        case StructureTypeSurfaceFullScreenExclusiveWin32Info:                                   { asString = "StructureTypeSurfaceFullScreenExclusiveWin32Info";                                   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HEADLESS_SURFACE_AVAILABLE

        case StructureTypeHeadlessSurfaceCreateInfo:                                             { asString = "StructureTypeHeadlessSurfaceCreateInfo";                                             break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE

        case StructureTypePhysicalDeviceLineRasterizationFeatures:                               { asString = "StructureTypePhysicalDeviceLineRasterizationFeatures";                               break; }
        case StructureTypePhysicalDeviceLineRasterizationProperties:                             { asString = "StructureTypePhysicalDeviceLineRasterizationProperties";                             break; }
        case StructureTypePipelineRasterizationLineStateCreateInfo:                              { asString = "StructureTypePipelineRasterizationLineStateCreateInfo";                              break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_AVAILABLE

        case StructureTypePhysicalDeviceShaderAtomicFloatFeatures:                               { asString = "StructureTypePhysicalDeviceShaderAtomicFloatFeatures";                               break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INDEX_TYPE_UINT8_AVAILABLE

        case StructureTypePhysicalDeviceIndexTypeUInt8Features:                                  { asString = "StructureTypePhysicalDeviceIndexTypeUInt8Features";                                  break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE

        case StructureTypePhysicalDeviceExtendedDynamicStateFeatures:                            { asString = "StructureTypePhysicalDeviceExtendedDynamicStateFeatures";                            break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE

        case StructureTypePhysicalDevicePipelineExecutablePropertiesFeatures:                    { asString = "StructureTypePhysicalDevicePipelineExecutablePropertiesFeatures";                    break; }
        case StructureTypePipelineInfo:                                                          { asString = "StructureTypePipelineInfo";                                                          break; }
        case StructureTypePipelineExecutableProperties:                                          { asString = "StructureTypePipelineExecutableProperties";                                          break; }
        case StructureTypePipelineExecutableInfo:                                                { asString = "StructureTypePipelineExecutableInfo";                                                break; }
        case StructureTypePipelineExecutableStatistic:                                           { asString = "StructureTypePipelineExecutableStatistic";                                           break; }
        case StructureTypePipelineExecutableInternalRepresentation:                              { asString = "StructureTypePipelineExecutableInternalRepresentation";                              break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_2_AVAILABLE

        case StructureTypePhysicalDeviceShaderAtomicFloat2Features:                              { asString = "StructureTypePhysicalDeviceShaderAtomicFloat2Features";                              break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_DEMOTE_TO_HELPER_INVOCATION_AVAILABLE

        case StructureTypePhysicalDeviceShaderDemoteToHelperInvocationFeatures:                  { asString = "StructureTypePhysicalDeviceShaderDemoteToHelperInvocationFeatures";                  break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE

        case StructureTypePhysicalDeviceDeviceGeneratedCommandsPropertiesNVidia:                 { asString = "StructureTypePhysicalDeviceDeviceGeneratedCommandsPropertiesNVidia";                 break; }
        case StructureTypePhysicalDeviceDeviceGeneratedCommandsFeaturesNVidia:                   { asString = "StructureTypePhysicalDeviceDeviceGeneratedCommandsFeaturesNVidia";                   break; }
        case StructureTypeGraphicsShaderGroupCreateInfoNVidia:                                   { asString = "StructureTypeGraphicsShaderGroupCreateInfoNVidia";                                   break; }
        case StructureTypeGraphicsPipelineShaderGroupsCreateInfoNVidia:                          { asString = "StructureTypeGraphicsPipelineShaderGroupsCreateInfoNVidia";                          break; }
        case StructureTypeIndirectCommandsLayoutTokenNVidia:                                     { asString = "StructureTypeIndirectCommandsLayoutTokenNVidia";                                     break; }
        case StructureTypeIndirectCommandsLayoutCreateInfoNVidia:                                { asString = "StructureTypeIndirectCommandsLayoutCreateInfoNVidia";                                break; }
        case StructureTypeGeneratedCommandsInfoNVidia:                                           { asString = "StructureTypeGeneratedCommandsInfoNVidia";                                           break; }
        case StructureTypeGeneratedCommandsMemoryRequirementsInfoNVidia:                         { asString = "StructureTypeGeneratedCommandsMemoryRequirementsInfoNVidia";                         break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_INHERITED_VIEWPORT_SCISSOR_AVAILABLE

        case StructureTypePhysicalDeviceInheritedViewportScissorFeaturesNVidia:                  { asString = "StructureTypePhysicalDeviceInheritedViewportScissorFeaturesNVidia";                  break; }
        case StructureTypeCommandBufferInheritanceViewportScissorInfoNVidia:                     { asString = "StructureTypeCommandBufferInheritanceViewportScissorInfoNVidia";                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE

        case StructureTypePhysicalDeviceShaderIntegerDotProductFeatures:                         { asString = "StructureTypePhysicalDeviceShaderIntegerDotProductFeatures";                         break; }
        case StructureTypePhysicalDeviceShaderIntegerDotProductProperties:                       { asString = "StructureTypePhysicalDeviceShaderIntegerDotProductProperties";                       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE

        case StructureTypePhysicalDeviceTexelBufferAlignmentFeatures:                            { asString = "StructureTypePhysicalDeviceTexelBufferAlignmentFeatures";                            break; }
        case StructureTypePhysicalDeviceTexelBufferAlignmentProperties:                          { asString = "StructureTypePhysicalDeviceTexelBufferAlignmentProperties";                          break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_RENDER_PASS_TRANSFORM_AVAILABLE

        case StructureTypeCommandBufferInheritanceRenderPassTransformInfoQualcomm:               { asString = "StructureTypeCommandBufferInheritanceRenderPassTransformInfoQualcomm";               break; }
        case StructureTypeRenderPassTransformBeginInfoQualcomm:                                  { asString = "StructureTypeRenderPassTransformBeginInfoQualcomm";                                  break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEVICE_MEMORY_REPORT_AVAILABLE

        case StructureTypePhysicalDeviceDeviceMemoryReportFeatures:                              { asString = "StructureTypePhysicalDeviceDeviceMemoryReportFeatures";                              break; }
        case StructureTypeDeviceDeviceMemoryReportCreateInfo:                                    { asString = "StructureTypeDeviceDeviceMemoryReportCreateInfo";                                    break; }
        case StructureTypeDeviceMemoryReportCallbackData:                                        { asString = "StructureTypeDeviceMemoryReportCallbackData";                                        break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE

        case StructureTypePhysicalDeviceRobustnessFeatures:                                      { asString = "StructureTypePhysicalDeviceRobustnessFeatures";                                      break; }
        case StructureTypePhysicalDeviceRobustnessProperties:                                    { asString = "StructureTypePhysicalDeviceRobustnessProperties";                                    break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE

        case StructureTypeSamplerCustomBorderColorCreateInfo:                                    { asString = "StructureTypeSamplerCustomBorderColorCreateInfo";                                    break; }
        case StructureTypePhysicalDeviceCustomBorderColorFeatures:                               { asString = "StructureTypePhysicalDeviceCustomBorderColorFeatures";                               break; }
        case StructureTypePhysicalDeviceCustomBorderColorProperties:                             { asString = "StructureTypePhysicalDeviceCustomBorderColorProperties";                             break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_LIBRARY_AVAILABLE

        case StructureTypePipelineLibraryCreateInfo:                                             { asString = "StructureTypePipelineLibraryCreateInfo";                                             break; }

#endif

#if _C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_ID_AVAILABLE

        case StructureTypePresentID:                                                             { asString = "StructureTypePresentID";                                                             break; }
        case StructureTypePhysicalDevicePresentIDFeatures:                                       { asString = "StructureTypePhysicalDevicePresentIDFeatures";                                       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE

        case StructureTypePhysicalDevicePrivateDataFeatures:                                     { asString = "StructureTypePhysicalDevicePrivateDataFeatures";                                     break; }
        case StructureTypeDevicePrivateDataCreateInfo:                                           { asString = "StructureTypeDevicePrivateDataCreateInfo";                                           break; }
        case StructureTypePrivateDataSlotCreateInfo:                                             { asString = "StructureTypePrivateDataSlotCreateInfo";                                             break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE

        case StructureTypePhysicalDevicePipelineCreationCacheControlFeatures:                    { asString = "StructureTypePhysicalDevicePipelineCreationCacheControlFeatures";                    break; }

#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_ENCODE_QUEUE_AVAILABLE

        case StructureTypeVideoEncodeInfo:                                                       { asString = "StructureTypeVideoEncodeInfo";                                                       break; }
        case StructureTypeVideoEncodeRateControlInfo:                                            { asString = "StructureTypeVideoEncodeRateControlInfo";                                            break; }
        case StructureTypeVideoEncodeRateControlLayerInfo:                                       { asString = "StructureTypeVideoEncodeRateControlLayerInfo";                                       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTICS_CONFIG_AVAILABLE

        case StructureTypePhysicalDeviceDiagnosticsConfigFeaturesNVidia:                         { asString = "StructureTypePhysicalDeviceDiagnosticsConfigFeaturesNVidia";                         break; }
        case StructureTypeDeviceDiagnosticsConfigCreateInfoNVidia:                               { asString = "StructureTypeDeviceDiagnosticsConfigCreateInfoNVidia";                               break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE

        case StructureTypeMemoryBarrier2:                                                        { asString = "StructureTypeMemoryBarrier2";                                                        break; }
        case StructureTypeBufferMemoryBarrier2:                                                  { asString = "StructureTypeBufferMemoryBarrier2";                                                  break; }
        case StructureTypeImageMemoryBarrier2:                                                   { asString = "StructureTypeImageMemoryBarrier2";                                                   break; }
        case StructureTypeDependencryInfo:                                                       { asString = "StructureTypeDependencryInfo";                                                       break; }
        case StructureTypeSubmitInfo2:                                                           { asString = "StructureTypeSubmitInfo2";                                                           break; }
        case StructureTypeSemaphoreSubmitInfo:                                                   { asString = "StructureTypeSemaphoreSubmitInfo";                                                   break; }
        case StructureTypeCommandBufferSubmitInfo:                                               { asString = "StructureTypeCommandBufferSubmitInfo";                                               break; }
        case StructureTypePhysicalDeviceSynchronizationFeatures:                                 { asString = "StructureTypePhysicalDeviceSynchronizationFeatures";                                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTIC_CHECKPOINTS_AVAILABLE

        case StructureTypeQueueFamilyCheckpointProperties2NVidia:                                { asString = "StructureTypeQueueFamilyCheckpointProperties2NVidia";                                break; }
        case StructureTypeCheckpointData2NVidia:                                                 { asString = "StructureTypeCheckpointData2NVidia";                                                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_SUBGROUP_UNIFORM_CONTROL_FLOW_AVAILABLE

        case StructureTypePhysicalDeviceShaderSubgroupUniformControlFlowFeatures:                { asString = "StructureTypePhysicalDeviceShaderSubgroupUniformControlFlowFeatures";                break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ZERO_INITIALIZE_WORKGROUP_MEMORY_AVAILABLE

        case StructureTypePhysicalDeviceZeroInitializeWorkgroupMemoryFeatures:                   { asString = "StructureTypePhysicalDeviceZeroInitializeWorkgroupMemoryFeatures";                   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE

        case StructureTypePhysicalDeviceFragmentShadingRateEnumsFeaturesNVidia:                  { asString = "StructureTypePhysicalDeviceFragmentShadingRateEnumsFeaturesNVidia";                  break; }
        case StructureTypePhysicalDeviceFragmentShadingRateEnumsPropertiesNVidia:                { asString = "StructureTypePhysicalDeviceFragmentShadingRateEnumsPropertiesNVidia";                break; }
        case StructureTypePipelineFragmentShadingRateEnumStateCreateInfoNVidia:                  { asString = "StructureTypePipelineFragmentShadingRateEnumStateCreateInfoNVidia";                  break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE

        case StructureTypeAccelerationStructureGeometryMotionTrianglesDataNVidia:                { asString = "StructureTypeAccelerationStructureGeometryMotionTrianglesDataNVidia";                break; }
        case StructureTypePhysicalDeviceRayTracingMotionBlurFeaturesNVidia:                      { asString = "StructureTypePhysicalDeviceRayTracingMotionBlurFeaturesNVidia";                      break; }
        case StructureTypeAccelerationStructureMotionInfoNVidia:                                 { asString = "StructureTypeAccelerationStructureMotionInfoNVidia";                                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_2_PLANE_444_FORMATS_AVAILABLE

        case StructureTypePhysicalDeviceYCBCR2Plane444FormatsFeatures:                           { asString = "StructureTypePhysicalDeviceYCBCR2Plane444FormatsFeatures";                           break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE

        case StructureTypePhysicalDeviceFragmentDensityMap2Features:                             { asString = "StructureTypePhysicalDeviceFragmentDensityMap2Features";                             break; }
        case StructureTypePhysicalDeviceFragmentDensityMap2Properties:                           { asString = "StructureTypePhysicalDeviceFragmentDensityMap2Properties";                           break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_ROTATED_COPY_COMMANDS_AVAILABLE

        case StructureTypeCopyCommandTransformInfoQualcomm:                                      { asString = "StructureTypeCopyCommandTransformInfoQualcomm";                                      break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_ROBUSTNESS_AVAILABLE

        case StructureTypePhysicalDeviceImageRobustnessFeatures:                                 { asString = "StructureTypePhysicalDeviceImageRobustnessFeatures";                                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_AVAILABLE

        case StructureTypePhysicalDeviceWorkgroupMemoryExplicitLayoutFeatures:                   { asString = "StructureTypePhysicalDeviceWorkgroupMemoryExplicitLayoutFeatures";                   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE

        case StructureTypeCopyBufferInfo:                                                        { asString = "StructureTypeCopyBufferInfo";                                                        break; }
        case StructureTypeCopyImageInfo:                                                         { asString = "StructureTypeCopyImageInfo";                                                         break; }
        case StructureTypeCopyBufferToImageInfo:                                                 { asString = "StructureTypeCopyBufferToImageInfo";                                                 break; }
        case StructureTypeCopyImageToBufferInfo:                                                 { asString = "StructureTypeCopyImageToBufferInfo";                                                 break; }
        case StructureTypeBlitImageInfo:                                                         { asString = "StructureTypeBlitImageInfo";                                                         break; }
        case StructureTypeResolveImageInfo:                                                      { asString = "StructureTypeResolveImageInfo";                                                      break; }
        case StructureTypeBufferCopy:                                                            { asString = "StructureTypeBufferCopy";                                                            break; }
        case StructureTypeImageCopy:                                                             { asString = "StructureTypeImageCopy";                                                             break; }
        case StructureTypeImageBlit:                                                             { asString = "StructureTypeImageBlit";                                                             break; }
        case StructureTypeBufferImageCopy:                                                       { asString = "StructureTypeBufferImageCopy";                                                       break; }
        case StructureTypeImageResolve:                                                          { asString = "StructureTypeImageResolve";                                                          break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_4444_FORMATS_AVAILABLE

        case StructureTypePhysicalDevice4444FormatsFeatures:                                     { asString = "StructureTypePhysicalDevice4444FormatsFeatures";                                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ARM_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_AVAILABLE

        case StructureTypePhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM:           { asString = "StructureTypePhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM";           break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_RGBA_10_X_6_FORMATS_AVAILABLE

        case StructureTypePhysicalDeviceRGBA10x6FormatsFeatures:                                 { asString = "StructureTypePhysicalDeviceRGBA10x6FormatsFeatures";                                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DIRECTFB_SURFACE_AVAILABLE

        case StructureTypeDirectfbSurfaceCreateInfo:                                             { asString = "StructureTypeDirectfbSurfaceCreateInfo";                                             break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE

        case StructureTypePhysicalDeviceMutableDescriptorTypeFeaturesValve:                      { asString = "StructureTypePhysicalDeviceMutableDescriptorTypeFeaturesValve";                      break; }
        case StructureTypeMutableDescriptorTypeCreateInfoValve:                                  { asString = "StructureTypeMutableDescriptorTypeCreateInfoValve";                                  break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_INPUT_DYNAMIC_STATE_AVAILABLE

        case StructureTypePhysicalDeviceVertexInputDynamicStateFeatures:                         { asString = "StructureTypePhysicalDeviceVertexInputDynamicStateFeatures";                         break; }
        case StructureTypeVertexInputBindingDescription:                                         { asString = "StructureTypeVertexInputBindingDescription";                                         break; }
        case StructureTypeVertexInputAttributeDescription:                                       { asString = "StructureTypeVertexInputAttributeDescription";                                       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PHYSICAL_DEVICE_DRM_AVAILABLE

        case StructureTypePhysicalDeviceDRMProperties:                                           { asString = "StructureTypePhysicalDeviceDRMProperties";                                           break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_CONTROL_AVAILABLE

        case StructureTypePhysicalDeviceDepthClipControlFeatures:                                { asString = "StructureTypePhysicalDeviceDepthClipControlFeatures";                                break; }
        case StructureTypePipelineViewportDepthClipControlCreateInfo:                            { asString = "StructureTypePipelineViewportDepthClipControlCreateInfo";                            break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIMITIVE_TOPOLOGY_LIST_RESTART_AVAILABLE

        case StructureTypePhysicalDevicePrimitiveTopologyListRestartFeatures:                    { asString = "StructureTypePhysicalDevicePrimitiveTopologyListRestartFeatures";                    break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FORMAT_FEATURE_FLAGS_AVAILABLE

        case StructureTypeFormatProperties3:                                                     { asString = "StructureTypeFormatProperties3";                                                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_MEMORY_AVAILABLE

        case StructureTypeImportMemoryZirconHandleInfoGoogle:                                    { asString = "StructureTypeImportMemoryZirconHandleInfoGoogle";                                    break; }
        case StructureTypeMemoryZirconHandlePropertiesGoogle:                                    { asString = "StructureTypeMemoryZirconHandlePropertiesGoogle";                                    break; }
        case StructureTypeGetZirconHandleInfo:                                                   { asString = "StructureTypeGetZirconHandleInfo";                                                   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_SEMAPHORE_AVAILABLE

        case StructureTypeImportSemaphoreZirconHandleInfoGoogle:                                 { asString = "StructureTypeImportSemaphoreZirconHandleInfoGoogle";                                 break; }
        case StructureTypeGetZirconHandleInfoGoogle:                                             { asString = "StructureTypeGetZirconHandleInfoGoogle";                                             break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_BUFFER_COLLECTION_AVAILABLE

        case StructureTypeBufferCollectionCreateInfoGoogle:                                      { asString = "StructureTypeBufferCollectionCreateInfoGoogle";                                      break; }
        case StructureTypeImportMemoryBufferCollectionGoogle:                                    { asString = "StructureTypeImportMemoryBufferCollectionGoogle";                                    break; }
        case StructureTypeBufferCollectionImageCreateInfoGoogle:                                 { asString = "StructureTypeBufferCollectionImageCreateInfoGoogle";                                 break; }
        case StructureTypeBufferCollectionPropertiesGoogle:                                      { asString = "StructureTypeBufferCollectionPropertiesGoogle";                                      break; }
        case StructureTypeBufferConstraintsInfoGoogle:                                           { asString = "StructureTypeBufferConstraintsInfoGoogle";                                           break; }
        case StructureTypeBufferCollectionBufferCreateInfoGoogle:                                { asString = "StructureTypeBufferCollectionBufferCreateInfoGoogle";                                break; }
        case StructureTypeImageConstraintsInfoGoogle:                                            { asString = "StructureTypeImageConstraintsInfoGoogle";                                            break; }
        case StructureTypeImageFormatConstraintsInfoGoogle:                                      { asString = "StructureTypeImageFormatConstraintsInfoGoogle";                                      break; }
        case StructureTypeSystemColorSpaceGoogle:                                                { asString = "StructureTypeSystemColorSpaceGoogle";                                                break; }
        case StructureTypeBufferCollectionConstraintsInfoGoogle:                                 { asString = "StructureTypeBufferCollectionConstraintsInfoGoogle";                                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE

        case StructureTypeSubpassShadingPipelineCreateInfoHuawei:                                { asString = "StructureTypeSubpassShadingPipelineCreateInfoHuawei";                                break; }
        case StructureTypePhysicalDeviceSubpassShadingFeaturesHuawei:                            { asString = "StructureTypePhysicalDeviceSubpassShadingFeaturesHuawei";                            break; }
        case StructureTypePhysicalDeviceSubpassShadingPropertiesHuawei:                          { asString = "StructureTypePhysicalDeviceSubpassShadingPropertiesHuawei";                          break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_INVOCATION_MASK_AVAILABLE

        case StructureTypePhysicalDeviceInvocationMaskFeaturesHuawei:                            { asString = "StructureTypePhysicalDeviceInvocationMaskFeaturesHuawei";                            break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_RDMA_AVAILABLE

        case StructureTypeMemoryGetRemoteAddressInfoNVidia:                                      { asString = "StructureTypeMemoryGetRemoteAddressInfoNVidia";                                      break; }
        case StructureTypePhysicalDeviceExternalMemoryRDMAFeaturesNVidia:                        { asString = "StructureTypePhysicalDeviceExternalMemoryRDMAFeaturesNVidia";                        break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_2_AVAILABLE

        case StructureTypePhysicalDeviceExtendedDynamicState2Features:                           { asString = "StructureTypePhysicalDeviceExtendedDynamicState2Features";                           break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLACKBERRY_QNX_SCREEN_SURFACE_AVAILABLE

        case StructureTypeQnxScreenSurfaceCreateInfoBlackberry:                                  { asString = "StructureTypeQnxScreenSurfaceCreateInfoBlackberry";                                  break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_COLOR_WRITE_ENABLE_AVAILABLE

        case StructureTypePhysicalDeviceColorWriteEnableFeatures:                                { asString = "StructureTypePhysicalDeviceColorWriteEnableFeatures";                                break; }
        case StructureTypePipelineColorWriteCreateInfo:                                          { asString = "StructureTypePipelineColorWriteCreateInfo";                                          break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE

        case StructureTypePhysicalDeviceGlobalPriorityQueryFeatures:                             { asString = "StructureTypePhysicalDeviceGlobalPriorityQueryFeatures";                             break; }
        case StructureTypeQueueFamilyGlobalPriorityProperties:                                   { asString = "StructureTypeQueueFamilyGlobalPriorityProperties";                                   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_VIEW_MIN_LOD_AVAILABLE

        case StructureTypePhysicalDeviceImageViewMinLODFeatures:                                 { asString = "StructureTypePhysicalDeviceImageViewMinLODFeatures";                                 break; }
        case StructureTypeImageViewMinLODCreateInfo:                                             { asString = "StructureTypeImageViewMinLODCreateInfo";                                             break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE

        case StructureTypePhysicalDeviceMultiDrawFeatures:                                       { asString = "StructureTypePhysicalDeviceMultiDrawFeatures";                                       break; }
        case StructureTypePhysicalDeviceMultiDrawProperties:                                     { asString = "StructureTypePhysicalDeviceMultiDrawProperties";                                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BORDER_COLOR_SWIZZLE_AVAILABLE

        case StructureTypePhysicalDeviceBorderColorSwizzleFeatures:                              { asString = "StructureTypePhysicalDeviceBorderColorSwizzleFeatures";                              break; }
        case StructureTypeSamplerBorderColorComponentMappingCreateInfo:                          { asString = "StructureTypeSamplerBorderColorComponentMappingCreateInfo";                          break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PAGEABLE_DEVICE_LOCAL_MEMORY_AVAILABLE

        case StructureTypePhysicalDevicePageableDeviceLocalMemoryFeatures:                       { asString = "StructureTypePhysicalDevicePageableDeviceLocalMemoryFeatures";                       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE

        case StructureTypePhysicalDeviceMaintenance4Features:                                    { asString = "StructureTypePhysicalDeviceMaintenance4Features";                                    break; }
        case StructureTypePhysicalDeviceMaintenance4Properties:                                  { asString = "StructureTypePhysicalDeviceMaintenance4Properties";                                  break; }
        case StructureTypePhysicalDeviceBufferMemoryRequirements:                                { asString = "StructureTypePhysicalDeviceBufferMemoryRequirements";                                break; }
        case StructureTypePhysicalDeviceImageMemoryRequirements:                                 { asString = "StructureTypePhysicalDeviceImageMemoryRequirements";                                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE

        case StructureTypePhysicalDeviceFragmentDensityMapOffsetFeaturesQualcomm:                { asString = "StructureTypePhysicalDeviceFragmentDensityMapOffsetFeaturesQualcomm";                break; }
        case StructureTypePhysicalDeviceFragmentDensityMapOffsetPropertiesQualcomm:              { asString = "StructureTypePhysicalDeviceFragmentDensityMapOffsetPropertiesQualcomm";              break; }
        case StructureTypeSubpassFragmentDensityMapOffsetEndInfoQualcomm:                        { asString = "StructureTypeSubpassFragmentDensityMapOffsetEndInfoQualcomm";                        break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_LINEAR_COLOR_ATTACHMENT_AVAILABLE

        case StructureTypePhysicalDeviceLinearColorAttachmentFeaturesNVidia:                     { asString = "StructureTypePhysicalDeviceLinearColorAttachmentFeaturesNVidia";                     break; }

#endif

        case StructureTypeUnknown:                                                               { asString = "StructureTypeUnknown";                                                               break; }

    }

    return asString;
}

auto vulkan :: toString (
        __C_ENG_TYPE ( DebugMessageSeverityFlag ) flag
) noexcept -> StringLiteral {
    StringLiteral asString = "";

    switch ( flag ) {
        case __C_ENG_TYPE ( DebugMessageSeverityFlag ) :: DebugMessageSeverityFlagVerbose:  { asString = "Verbose"; break; }
        case __C_ENG_TYPE ( DebugMessageSeverityFlag ) :: DebugMessageSeverityFlagInfo:     { asString = "Info";    break; }
        case __C_ENG_TYPE ( DebugMessageSeverityFlag ) :: DebugMessageSeverityFlagWarning:  { asString = "Warning"; break; }
        case __C_ENG_TYPE ( DebugMessageSeverityFlag ) :: DebugMessageSeverityFlagError:    { asString = "Error";   break; }
    }

    return asString;
}

auto vulkan :: toString (
        __C_ENG_TYPE ( DebugMessageTypeFlag ) flag
) noexcept -> StringLiteral {
    StringLiteral asString = "";

    switch ( flag ) {
        case __C_ENG_TYPE ( DebugMessageTypeFlag ) :: DebugMessageTypeFlagGeneral:      { asString = "General";     break; }
        case __C_ENG_TYPE ( DebugMessageTypeFlag ) :: DebugMessageTypeFlagValidation:   { asString = "Validation";  break; }
        case __C_ENG_TYPE ( DebugMessageTypeFlag ) :: DebugMessageTypeFlagPerformance:  { asString = "Performance"; break; }
    }

    return asString;
}

auto vulkan :: toString (
        __C_ENG_TYPE ( ValidationFeatureEnable ) flag
) noexcept -> StringLiteral {
    StringLiteral asString = "";

    switch ( flag ) {
        case __C_ENG_TYPE ( ValidationFeatureEnable ) :: ValidationFeatureEnableGpuAssisted:                    { asString = "GPU Assisted Validation";                         break; }
        case __C_ENG_TYPE ( ValidationFeatureEnable ) :: ValidationFeatureEnableGpuAssistedReserveBindingSlot:  { asString = "GPU Assisted Validation Reserved Binding Slot";   break; }
        case __C_ENG_TYPE ( ValidationFeatureEnable ) :: ValidationFeatureEnableBestPractices:                  { asString = "Best Practices";                                  break; }
        case __C_ENG_TYPE ( ValidationFeatureEnable ) :: ValidationFeatureEnableDebugPrintf:                    { asString = "GPU Shader Debug Printf";                         break; }
        case __C_ENG_TYPE ( ValidationFeatureEnable ) :: ValidationFeatureEnableSynchronizationValidation:      { asString = "Synchronization Validation";                      break; }
    }

    return asString;
}

auto vulkan :: toString (
        __C_ENG_TYPE ( ValidationFeatureDisable ) flag
) noexcept -> StringLiteral {
    StringLiteral asString = "";

    switch ( flag ) {
        case __C_ENG_TYPE ( ValidationFeatureDisable ) :: ValidationFeatureDisableAll:                      { asString = "All Validation Features";                     break; }
        case __C_ENG_TYPE ( ValidationFeatureDisable ) :: ValidationFeatureDisableShaders:                  { asString = "Shader Checks";                               break; }
        case __C_ENG_TYPE ( ValidationFeatureDisable ) :: ValidationFeatureDisableThreadSafety:             { asString = "Thread Safety Checks";                        break; }
        case __C_ENG_TYPE ( ValidationFeatureDisable ) :: ValidationFeatureDisableAPIParameters:            { asString = "Parameter Checks";                            break; }
        case __C_ENG_TYPE ( ValidationFeatureDisable ) :: ValidationFeatureDisableObjectLifetimes:          { asString = "Object Lifetime Checks";                      break; }
        case __C_ENG_TYPE ( ValidationFeatureDisable ) :: ValidationFeatureDisableCoreChecks:               { asString = "Core Validation Checks";                      break; }
        case __C_ENG_TYPE ( ValidationFeatureDisable ) :: ValidationFeatureDisableUniqueHandles:            { asString = "Duplicate Non-Dispatchable Handle Checks";    break; }
        case __C_ENG_TYPE ( ValidationFeatureDisable ) :: ValidationFeatureDisableShaderValidationCache:    { asString = "Shader Validation Caching";                   break; }
    }

    return asString;
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceType ) type
) noexcept -> StringLiteral {
    StringLiteral asString = "";

    switch ( type ) {
        case __C_ENG_TYPE ( PhysicalDeviceType ) :: PhysicalDeviceTypeUnknown:          { asString = "Unknown Physical Device Type";    break; }
        case __C_ENG_TYPE ( PhysicalDeviceType ) :: PhysicalDeviceTypeIntegratedGPU:    { asString = "Integrated GPU";                  break; }
        case __C_ENG_TYPE ( PhysicalDeviceType ) :: PhysicalDeviceTypeDedicatedGPU:     { asString = "Dedicated GPU";                   break; }
        case __C_ENG_TYPE ( PhysicalDeviceType ) :: PhysicalDeviceTypeVirtualGPU:       { asString = "Virtual GPU";                     break; }
        case __C_ENG_TYPE ( PhysicalDeviceType ) :: PhysicalDeviceTypeCPU:              { asString = "CPU";                             break; }
    }

    return asString;
}

auto vulkan :: toString (
        __C_ENG_TYPE ( VendorID ) ID
) noexcept -> StringLiteral {
    StringLiteral asString = "";

    switch ( ID ) {
        case __C_ENG_TYPE ( VendorID ) :: VendorIDVIV:          { asString = "VIV";         break; }
        case __C_ENG_TYPE ( VendorID ) :: VendorIDVSI:          { asString = "VSI";         break; }
        case __C_ENG_TYPE ( VendorID ) :: VendorIDKazan:        { asString = "Kazan";       break; }
        case __C_ENG_TYPE ( VendorID ) :: VendorIDCodeplay:     { asString = "Codeplay";    break; }
        case __C_ENG_TYPE ( VendorID ) :: VendorIDMesa:         { asString = "Mesa";        break; }
        case __C_ENG_TYPE ( VendorID ) :: VendorIDPOCL:         { asString = "POCL";        break; }
    }

    return asString;
}

auto vulkan :: toString (
        __C_ENG_TYPE ( SampleCountFlag ) flag
) noexcept -> StringLiteral {
    StringLiteral asString = "";

    switch ( flag ) {
        case __C_ENG_TYPE ( SampleCountFlag ) :: SampleCountFlag1Bit:   { asString = "1 Bit";   break; }
        case __C_ENG_TYPE ( SampleCountFlag ) :: SampleCountFlag2Bit:   { asString = "2 Bits";  break; }
        case __C_ENG_TYPE ( SampleCountFlag ) :: SampleCountFlag4Bit:   { asString = "4 Bits";  break; }
        case __C_ENG_TYPE ( SampleCountFlag ) :: SampleCountFlag8Bit:   { asString = "8 Bits";  break; }
        case __C_ENG_TYPE ( SampleCountFlag ) :: SampleCountFlag16Bit:  { asString = "16 Bits"; break; }
        case __C_ENG_TYPE ( SampleCountFlag ) :: SampleCountFlag32Bit:  { asString = "32 Bits"; break; }
        case __C_ENG_TYPE ( SampleCountFlag ) :: SampleCountFlag64Bit:  { asString = "64 Bits"; break; }
    }

    return asString;
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PointClippingBehavior ) flag
) noexcept -> StringLiteral {
    StringLiteral asString = "";

    switch ( flag ) {
        case __C_ENG_TYPE ( PointClippingBehavior ) :: PointClippingBehaviorAllClipPlanes:      { asString = "All Clip Planes";   break; }
        case __C_ENG_TYPE ( PointClippingBehavior ) :: PointClippingBehaviorUserClipPlanesOnly: { asString = "User Clip Planes";  break; }
    }

    return asString;
}

auto vulkan :: toString (
        __C_ENG_TYPE ( ShaderStageFlag ) flag
) noexcept -> StringLiteral {
    StringLiteral asString = "";

    switch ( flag ) {
        case __C_ENG_TYPE ( ShaderStageFlag ) :: ShaderStageFlagVertex:                 { asString = "Vertex Shader Stage";                     break; }
        case __C_ENG_TYPE ( ShaderStageFlag ) :: ShaderStageFlagTessellationControl:    { asString = "Tessellation Control Shader Stage";       break; }
        case __C_ENG_TYPE ( ShaderStageFlag ) :: ShaderStageFlagTessellationEvaluation: { asString = "Tessellation Evaluation Shader Stage";    break; }
        case __C_ENG_TYPE ( ShaderStageFlag ) :: ShaderStageFlagGeometry:               { asString = "Geometry Shader Stage";                   break; }
        case __C_ENG_TYPE ( ShaderStageFlag ) :: ShaderStageFlagFragment:               { asString = "Fragment Shader Stage";                   break; }
        case __C_ENG_TYPE ( ShaderStageFlag ) :: ShaderStageFlagCompute:                { asString = "Compute Shader Stage";                    break; }
        case __C_ENG_TYPE ( ShaderStageFlag ) :: ShaderStageFlagAllGraphics:            { asString = "All Graphics Shader Stages";              break; }
        case __C_ENG_TYPE ( ShaderStageFlag ) :: ShaderStageFlagAll:                    { asString = "All Shader Stages";                       break; }

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE

        case __C_ENG_TYPE ( ShaderStageFlag ) :: ShaderStageFlagRayGeneration:          { asString = "Ray Generation Shader Stage";             break; }
        case __C_ENG_TYPE ( ShaderStageFlag ) :: ShaderStageFlagRayAnyHit:              { asString = "Ray Any Hit Shader Stage";                break; }
        case __C_ENG_TYPE ( ShaderStageFlag ) :: ShaderStageFlagRayClosestHit:          { asString = "Ray Closest Hit Shader Stage";            break; }
        case __C_ENG_TYPE ( ShaderStageFlag ) :: ShaderStageFlagRayMiss:                { asString = "Ray Miss Shader Stage";                   break; }
        case __C_ENG_TYPE ( ShaderStageFlag ) :: ShaderStageFlagRayIntersection:        { asString = "Ray Intersection Shader Stage";           break; }
        case __C_ENG_TYPE ( ShaderStageFlag ) :: ShaderStageFlagRayCallable:            { asString = "Ray Callable Shader Stage";               break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE

        case __C_ENG_TYPE ( ShaderStageFlag ) :: ShaderStageFlagMeshTaskNVidia:         { asString = "Task Shader Stage";                       break; }
        case __C_ENG_TYPE ( ShaderStageFlag ) :: ShaderStageFlagMeshMeshNVidia:         { asString = "Mesh Shader Stage";                       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE

        case __C_ENG_TYPE ( ShaderStageFlag ) :: ShaderStageFlagSubpassShadingHuawei:   { asString = "Subpass Shading Shader Stage";            break; }

#endif

    }

    return asString;
}

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( SubgroupFeatureFlag ) flag
) noexcept -> StringLiteral {
    StringLiteral asString = "";

    switch ( flag ) {
        case __C_ENG_TYPE ( SubgroupFeatureFlag ) :: SubgroupFeatureFlagBasic:              { asString = "Basic";           break; }
        case __C_ENG_TYPE ( SubgroupFeatureFlag ) :: SubgroupFeatureFlagVote:               { asString = "Vote";            break; }
        case __C_ENG_TYPE ( SubgroupFeatureFlag ) :: SubgroupFeatureFlagArithmetic:         { asString = "Arithmetic";      break; }
        case __C_ENG_TYPE ( SubgroupFeatureFlag ) :: SubgroupFeatureFlagShuffle:            { asString = "Shuffle";         break; }
        case __C_ENG_TYPE ( SubgroupFeatureFlag ) :: SubgroupFeatureFlagShuffleRelative:    { asString = "ShuffleRelative"; break; }
        case __C_ENG_TYPE ( SubgroupFeatureFlag ) :: SubgroupFeatureFlagClustered:          { asString = "Clustered";       break; }
        case __C_ENG_TYPE ( SubgroupFeatureFlag ) :: SubgroupFeatureFlagQuad:               { asString = "Quad";            break; }

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SUBGROUP_PARTITIONED_AVAILABLE

        case __C_ENG_TYPE ( SubgroupFeatureFlag ) :: SubgroupFeatureFlagPartitionedNVidia:  { asString = "Partitioned";     break; }

#endif

    }

    return asString;
}

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( DriverID ) ID
) noexcept -> StringLiteral {
    StringLiteral asString = "";

    switch ( ID ) {
        case __C_ENG_TYPE ( DriverID ) :: DriverIDAMDProprietary:                   { asString = "AMD Proprietary Driver";                      break; }
        case __C_ENG_TYPE ( DriverID ) :: DriverIDAMDOpenSource:                    { asString = "AMD Open Source Driver";                      break; }
        case __C_ENG_TYPE ( DriverID ) :: DriverIDMesaRadV:                         { asString = "Mesa RAD V Driver";                           break; }
        case __C_ENG_TYPE ( DriverID ) :: DriverIDNVidiaProprietary:                { asString = "NVidia Proprietary Driver";                   break; }
        case __C_ENG_TYPE ( DriverID ) :: DriverIDInterProprietaryWindows:          { asString = "Intel Proprietary Windows Driver";            break; }
        case __C_ENG_TYPE ( DriverID ) :: DriverIDIntelOpenSourceMesa:              { asString = "Intel Open Source Mesa Driver";               break; }
        case __C_ENG_TYPE ( DriverID ) :: DriverIDImaginationProprietary:           { asString = "Imagination Proprietary Driver";              break; }
        case __C_ENG_TYPE ( DriverID ) :: DriverIDQualcommProprietary:              { asString = "Qualcomm Proprietary Driver";                 break; }
        case __C_ENG_TYPE ( DriverID ) :: DriverIDARMProprietary:                   { asString = "ARM Proprietary Driver";                      break; }
        case __C_ENG_TYPE ( DriverID ) :: DriverIDGoogleSwiftshader:                { asString = "Google Switfshader Driver";                   break; }
        case __C_ENG_TYPE ( DriverID ) :: DriverIDGoogleGamesPlatformProprietary:   { asString = "Google Games Platform Proprietary Driver";    break; }
        case __C_ENG_TYPE ( DriverID ) :: DriverIDBroadcomProprietary:              { asString = "Broadcom Proprietary Driver";                 break; }
        case __C_ENG_TYPE ( DriverID ) :: DriverIDMesaLLVMPipe:                     { asString = "Mesa LLVM Pipe Driver";                       break; }
        case __C_ENG_TYPE ( DriverID ) :: DriverIDMoltenVulkan:                     { asString = "MoltenVk Driver";                             break; }
        case __C_ENG_TYPE ( DriverID ) :: DriverIDCoreAVIProprietary:               { asString = "Core AVI Proprietary Driver";                 break; }
        case __C_ENG_TYPE ( DriverID ) :: DriverIDJuiceProprietary:                 { asString = "Juice Proprietary Driver";                    break; }
        case __C_ENG_TYPE ( DriverID ) :: DriverIDVeriSiliconProprietary:           { asString = "Veri Silicon Proprietary Driver";             break; }
    }

    return asString;
}

auto vulkan :: toString (
        __C_ENG_TYPE ( ShaderFloatControlsIndependence ) value
) noexcept -> StringLiteral {
    StringLiteral asString = "";

    switch ( value ) {
        case __C_ENG_TYPE ( ShaderFloatControlsIndependence ) :: ShaderFloatControlsIndependence32BitOnly:  { asString = "32 Bit Only"; break; }
        case __C_ENG_TYPE ( ShaderFloatControlsIndependence ) :: ShaderFloatControlsIndependenceAll:        { asString = "All";         break; }
        case __C_ENG_TYPE ( ShaderFloatControlsIndependence ) :: ShaderFloatControlsIndependenceNone:       { asString = "None";        break; }
    }

    return asString;
}

auto vulkan :: toString (
        __C_ENG_TYPE ( ResolveModeFlag ) flag
) noexcept -> StringLiteral {
    StringLiteral asString = "";

    switch ( flag ) {
        case __C_ENG_TYPE ( ResolveModeFlag ) :: ResolveModeFlagNone:       { asString = "No Resolve";          break; }
        case __C_ENG_TYPE ( ResolveModeFlag ) :: ResolveModeFlagSampleZero: { asString = "Resolve by 0 sample"; break; }
        case __C_ENG_TYPE ( ResolveModeFlag ) :: ResolveModeFlagAverage:    { asString = "Resolve by average";  break; }
        case __C_ENG_TYPE ( ResolveModeFlag ) :: ResolveModeFlagMin:        { asString = "Resolve by min";      break; }
        case __C_ENG_TYPE ( ResolveModeFlag ) :: ResolveModeFlagMax:        { asString = "Resolve by max";      break; }
    }

    return asString;
}

#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( QueueFlag ) flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case __C_ENG_TYPE ( QueueFlag ) :: QueueFlagGraphics:       { asString = "Graphics";        break; }
        case __C_ENG_TYPE ( QueueFlag ) :: QueueFlagCompute:        { asString = "Compute";         break; }
        case __C_ENG_TYPE ( QueueFlag ) :: QueueFlagTransfer:       { asString = "Transfer";        break; }
        case __C_ENG_TYPE ( QueueFlag ) :: QueueFlagSparseBinding:  { asString = "Sparse Binding";  break; }
        case __C_ENG_TYPE ( QueueFlag ) :: QueueFlagProtected:      { asString = "Protected";       break; }

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_DECODE_QUEUE_AVAILABLE

        case __C_ENG_TYPE ( QueueFlag ) :: QueueFlagVideoDecode:    { asString = "Video Decode";    break; }

#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_ENCODE_QUEUE_AVAILABLE

        case __C_ENG_TYPE ( QueueFlag ) :: QueueFlagVideoEncode:    { asString = "Video Encode";    break; }

#endif

    }

    return asString;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_2_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( ShaderCorePropertiesFlagAMD ) flag
) noexcept -> StringLiteral {
    StringLiteral asString = "";

    return asString;
}

#endif

#include <CDS/String>

auto vulkan :: toString (
        __C_ENG_TYPE ( Offset2D ) const & offset
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( Offset2D ) ) " "
            "{ x = "_s  + offset.x +
            ", y = "    + offset.y +
            " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( Offset3D ) const & offset
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( Offset3D ) ) " "
            "{ x = "_s  + offset.x +
            ", y = "    + offset.y +
            ", z = "    + offset.z +
            " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( Extent2D ) const & extent
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( Extent2D ) ) " "
            "{ width = "_s  + extent.width +
            ", height = "   + extent.height +
            " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( Extent3D ) const & extent
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( Extent3D ) ) " "
            "{ width = "_s  + extent.width +
            ", height = "   + extent.height +
            ", depth = "    + extent.depth +
            " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( Rect ) const & rect
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( Rect ) ) " "
            "{ offset = "   + toString ( rect.offset ) +
            ", extent = "   + toString ( rect.extent ) +
            " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( Version ) const & version
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( Version ) ) " "
            "{ variant = "_s    + version.variant   +
            ", major = "        + version.major     +
            ", minor = "        + version.minor     +
            ", patch = "        + version.patch     +
            " }";
}

#include <CDS/Long>
auto vulkan :: toString (
        __C_ENG_TYPE ( DeviceSize ) deviceSize
) noexcept -> String {

    return ""_s + static_cast < uint64 > ( deviceSize );
}

auto vulkan :: toString (
        __C_ENG_TYPE ( ApplicationInfo ) const & createInfo
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( ApplicationInfo ) ) " "
            "{ type = "_s           + toString ( createInfo.structureType ) +
            ", next = "             + :: toString ( createInfo.pNext ) +
            ", name = "             + createInfo.name +
            ", version = "          + versionReadableFormat ( createInfo.version ) +
            ", engineName = "       + createInfo.engineName +
            ", engineVersion = "    + versionReadableFormat ( createInfo.engineVersion ) +
            ", apiVersion = "       + versionReadableFormat ( createInfo.apiVersion ) +
            " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( InstanceCreateInfo ) const & createInfo
) noexcept -> String {

    auto stringArrayToString = [] ( StringLiteral const * pLayerNames, uint32 layerCount ) noexcept -> String {
        String asString = "[ ";

        for ( uint32 i = 0U; i < layerCount; ++ i ) {
            asString += pLayerNames[i] + ", "_s;
        }

        return asString.removePrefix(", ") + " ]";
    };

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( InstanceCreateInfo ) ) " "
            "{ type = "_s               + toString ( createInfo.structureType ) +
            ", next = "                 + :: toString ( createInfo.pNext ) +
            ", flags = "                + "0b" + Long ( createInfo.flags ).toString(2) +
            ", applicationInfo = "      + :: toString ( createInfo.pApplicationInfo ) +
            ", enabledLayers = "        + stringArrayToString ( createInfo.pEnabledLayerNames, createInfo.enabledLayerCount ) +
            ", enabledExtensions = "    + stringArrayToString ( createInfo.pEnabledExtensionNames, createInfo.enabledExtensionCount ) +
            " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( DebugMessengerCreateInfo ) const & createInfo
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( DebugMessengerCreateInfo ) ) " "
            "{ type = "_s               + toString ( createInfo.structureType ) +
            ", next = "                 + :: toString ( createInfo.pNext ) +
            ", flags = "                + "0b" + Long ( createInfo.flags ).toString(2) +
            ", messageSeverityFlags = " + "0b" + Long ( createInfo.messageSeverityFlags ).toString(2) +
            ", messageTypeFlags = "     + "0b" + Long ( createInfo.messageTypeFlags ).toString(2) +
            ", callback = "             + :: toString ( createInfo.callback ) +
            ", userData = "             + :: toString ( createInfo.pCallbackUserData ) +
            " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( ValidationFeatures ) const & createInfo
) noexcept -> String {

    auto enabledFeaturesToString = [](
            __C_ENG_TYPE ( ValidationFeatureEnable )    const * pFeatures,
            uint32                                              featureCount
    ) noexcept -> String {
        String asString;

        for ( uint32 i = 0U; i < featureCount; ++ i ) {
            asString += :: toString ( pFeatures[i] ) + ", "_s;
        }

        return asString.removeSuffix(", ");
    };

    auto disabledFeaturesToString = [](
            __C_ENG_TYPE ( ValidationFeatureDisable )   const * pFeatures,
            uint32                                              featureCount
    ) noexcept -> String {
        String asString;

        for ( uint32 i = 0U; i < featureCount; ++ i ) {
            asString += :: toString ( pFeatures[i] ) + ", "_s;
        }

        return asString.removeSuffix(", ");
    };

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( ValidationFeatures ) ) " "
            "{ type = "_s               + toString ( createInfo.structureType ) +
            ", next = "                 + :: toString ( createInfo.pNext ) +
            ", enabledFeatures = "
            "{ count = "                + createInfo.enabledValidationFeatureCount +
            ", features = "             + enabledFeaturesToString ( createInfo.pEnabledValidationFeatures, createInfo.enabledValidationFeatureCount ) +
            " }" +
            ", disabledFeatures = "
            "{ count = "                + createInfo.disabledValidationFeatureCount +
            ", features = "             + disabledFeaturesToString ( createInfo.pDisabledValidationFeatures, createInfo.disabledValidationFeatureCount ) +
            " }"
            " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( LayerProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( LayerProperties ) ) " "
            "{ layerName = "_s      + properties.layerName +
            ", specVersion = "      + versionReadableFormat ( properties.specVersion ) +
            ", version = "          + properties.implementationVersion +
            ", description = "      + properties.description +
            " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( ExtensionProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( ExtensionProperties ) ) " "
            "{ layerName = "_s      + properties.name +
            ", specVersion = "      + properties.specVersion +
            " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( AllocationCallbacks ) const & allocationCallbacks
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( AllocationCallbacks ) ) " "
            "{ allocationCallback = "_s                     + :: toString ( allocationCallbacks.allocationCallback ) +
            ", reallocationCallback = "                     + :: toString ( allocationCallbacks.reallocationCallback ) +
            ", freeCallback = "                             + :: toString ( allocationCallbacks.freeCallback ) +
            ", internalAllocationNotificationCallback = "   + :: toString ( allocationCallbacks.internalAllocationNotificationCallback ) +
            ", internalFreeNotificationCallback = "         + :: toString ( allocationCallbacks.internalFreeNotificationCallback ) +
            " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceLimits ) const &   deviceLimits
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceLimits ) ) " "_s +
            "{ maxImageDimension1D = "                              + deviceLimits.maxImageDimension1D +
            ", maxImageDimension2D = "                              + deviceLimits.maxImageDimension2D +
            ", maxImageDimension3D = "                              + deviceLimits.maxImageDimension3D +
            ", maxImageDimensionCube = "                            + deviceLimits.maxImageDimensionCube +
            ", maxImageArrayLayers = "                              + deviceLimits.maxImageArrayLayers +
            ", maxTexelBufferElements = "                           + deviceLimits.maxTexelBufferElements +
            ", maxUniformBufferRange = "                            + deviceLimits.maxUniformBufferRange +
            ", maxStorageBufferRange = "                            + deviceLimits.maxStorageBufferRange +
            ", maxPushConstantsSize = "                             + deviceLimits.maxPushConstantsSize +
            ", maxMemoryAllocationCount = "                         + deviceLimits.maxMemoryAllocationCount +
            ", maxSamplerAllocationCount = "                        + deviceLimits.maxSamplerAllocationCount +
            ", bufferImageGranularity = "                           + toString ( deviceLimits.bufferImageGranularity ) +
            ", sparseAddressSpaceSize = "                           + toString ( deviceLimits.sparseAddressSpaceSize ) +
            ", maxBoundDescriptorSets = "                           + deviceLimits.maxBoundDescriptorSets +
            ", maxPerStageDescriptorSamplers = "                    + deviceLimits.maxPerStageDescriptorSamplers +
            ", maxPerStageDescriptorUniformBuffers = "              + deviceLimits.maxPerStageDescriptorUniformBuffers +
            ", maxPerStageDescriptorStorageBuffers = "              + deviceLimits.maxPerStageDescriptorStorageBuffers +
            ", maxPerStageDescriptorSampledImages = "               + deviceLimits.maxPerStageDescriptorSampledImages +
            ", maxPerStageDescriptorStorageImages = "               + deviceLimits.maxPerStageDescriptorStorageImages +
            ", maxPerStageDescriptorInputAttachments = "            + deviceLimits.maxPerStageDescriptorInputAttachments +
            ", maxPerStageResources = "                             + deviceLimits.maxPerStageResources +
            ", maxDescriptorSetSamplers = "                         + deviceLimits.maxDescriptorSetSamplers +
            ", maxDescriptorSetUniformBuffers = "                   + deviceLimits.maxDescriptorSetUniformBuffers +
            ", maxDescriptorSetUniformBuffersDynamic = "            + deviceLimits.maxDescriptorSetUniformBuffersDynamic +
            ", maxDescriptorSetStorageBuffers = "                   + deviceLimits.maxDescriptorSetStorageBuffers +
            ", maxDescriptorSetStorageBuffersDynamic = "            + deviceLimits.maxDescriptorSetStorageBuffersDynamic +
            ", maxDescriptorSetSampledImages = "                    + deviceLimits.maxDescriptorSetSampledImages +
            ", maxDescriptorSetStorageImages = "                    + deviceLimits.maxDescriptorSetStorageImages +
            ", maxDescriptorSetInputAttachments = "                 + deviceLimits.maxDescriptorSetInputAttachments +
            ", maxVertexInputAttributes = "                         + deviceLimits.maxVertexInputAttributes +
            ", maxVertexInputBindings = "                           + deviceLimits.maxVertexInputBindings +
            ", maxVertexInputAttributeOffset = "                    + deviceLimits.maxVertexInputAttributeOffset +
            ", maxVertexInputBindingStride = "                      + deviceLimits.maxVertexInputBindingStride +
            ", maxVertexOutputComponents = "                        + deviceLimits.maxVertexOutputComponents +
            ", maxTessellationGenerationLevel = "                   + deviceLimits.maxTessellationGenerationLevel +
            ", maxTessellationPatchSize = "                         + deviceLimits.maxTessellationPatchSize +
            ", maxTessellationControlPerVertexInputComponents = "   + deviceLimits.maxTessellationControlPerVertexInputComponents +
            ", maxTessellationControlPerVertexOutputComponents = "  + deviceLimits.maxTessellationControlPerVertexOutputComponents +
            ", maxTessellationControlPerPatchOutputComponents = "   + deviceLimits.maxTessellationControlPerPatchOutputComponents +
            ", maxTessellationControlTotalOutputComponents = "      + deviceLimits.maxTessellationControlTotalOutputComponents +
            ", maxTessellationEvaluationInputComponents = "         + deviceLimits.maxTessellationEvaluationInputComponents +
            ", maxTessellationEvaluationOutputComponents = "        + deviceLimits.maxTessellationEvaluationOutputComponents +
            ", maxGeometryShaderInvocations = "                     + deviceLimits.maxGeometryShaderInvocations +
            ", maxGeometryInputComponents = "                       + deviceLimits.maxGeometryInputComponents +
            ", maxGeometryOutputComponents = "                      + deviceLimits.maxGeometryOutputComponents +
            ", maxGeometryOutputVertices = "                        + deviceLimits.maxGeometryOutputVertices +
            ", maxGeometryTotalOutputComponents = "                 + deviceLimits.maxGeometryTotalOutputComponents +
            ", maxFragmentInputComponents = "                       + deviceLimits.maxFragmentInputComponents +
            ", maxFragmentOutputAttachments = "                     + deviceLimits.maxFragmentOutputAttachments +
            ", maxFragmentDualSourceAttachments = "                 + deviceLimits.maxFragmentDualSourceAttachments +
            ", maxFragmentCombinedOutputResources = "               + deviceLimits.maxFragmentCombinedOutputResources +
            ", maxComputeSharedMemorySize = "                       + deviceLimits.maxComputeSharedMemorySize +
            ", maxComputeWorkGroupCount = [ "                       + deviceLimits.maxComputeWorkGroupCount[0] + ", " + deviceLimits.maxComputeWorkGroupCount[1] + ", " + deviceLimits.maxComputeWorkGroupCount[2] + " ]" +
            ", maxComputeWorkGroupInvocations = "                   + deviceLimits.maxComputeWorkGroupInvocations +
            ", maxComputeWorkGroupSize = [ "                        + deviceLimits.maxComputeWorkGroupSize[0] + ", " + deviceLimits.maxComputeWorkGroupSize[1] + ", " + deviceLimits.maxComputeWorkGroupSize[2] + " ]" +
            ", subPixelPrecisionBits = "                            + deviceLimits.subPixelPrecisionBits +
            ", subTexelPrecisionBits = "                            + deviceLimits.subTexelPrecisionBits +
            ", mipmapPrecisionBits = "                              + deviceLimits.mipmapPrecisionBits +
            ", maxDrawIndexedIndexValue = "                         + deviceLimits.maxDrawIndexedIndexValue +
            ", maxDrawIndirectCount = "                             + deviceLimits.maxDrawIndirectCount +
            ", maxSamplerLodBias = "                                + deviceLimits.maxSamplerLodBias +
            ", maxSamplerAnisotropy = "                             + deviceLimits.maxSamplerAnisotropy +
            ", maxViewports = "                                     + deviceLimits.maxViewports +
            ", maxViewportDimensions = [ "                          + deviceLimits.maxViewportDimensions[0] + ", " + deviceLimits.maxViewportDimensions[1] + " ]" +
            ", viewportBoundsRange = [ "                            + deviceLimits.viewportBoundsRange[0] + ", " + deviceLimits.viewportBoundsRange[1] + " ]" +
            ", viewportSubPixelBits = "                             + deviceLimits.viewportSubPixelBits +
            ", minMemoryMapAlignment = "                            + deviceLimits.minMemoryMapAlignment +
            ", minTexelBufferOffsetAlignment = "                    + toString ( deviceLimits.minTexelBufferOffsetAlignment ) +
            ", minUniformBufferOffsetAlignment = "                  + toString ( deviceLimits.minUniformBufferOffsetAlignment ) +
            ", minStorageBufferOffsetAlignment = "                  + toString ( deviceLimits.minStorageBufferOffsetAlignment ) +
            ", minTexelOffset = "                                   + deviceLimits.minTexelOffset +
            ", maxTexelOffset = "                                   + deviceLimits.maxTexelOffset +
            ", minTexelGatherOffset = "                             + deviceLimits.minTexelGatherOffset +
            ", maxTexelGatherOffset = "                             + deviceLimits.maxTexelGatherOffset +
            ", minInterpolationOffset = "                           + deviceLimits.minInterpolationOffset +
            ", maxInterpolationOffset = "                           + deviceLimits.maxInterpolationOffset +
            ", subPixelInterpolationOffsetBits = "                  + deviceLimits.subPixelInterpolationOffsetBits +
            ", maxFramebufferWidth = "                              + deviceLimits.maxFramebufferWidth +
            ", maxFramebufferHeight = "                             + deviceLimits.maxFramebufferHeight +
            ", maxFramebufferLayers = "                             + deviceLimits.maxFramebufferLayers +
            ", framebufferColorSampleCounts = "                     + "0b" + Long ( deviceLimits.framebufferColorSampleCounts ).toString(2) +
            ", framebufferDepthSampleCounts = "                     + "0b" + Long ( deviceLimits.framebufferDepthSampleCounts ).toString(2) +
            ", framebufferStencilSampleCounts = "                   + "0b" + Long ( deviceLimits.framebufferStencilSampleCounts ).toString(2) +
            ", framebufferNoAttachmentsSampleCounts = "             + "0b" + Long ( deviceLimits.framebufferNoAttachmentsSampleCounts ).toString(2) +
            ", maxColorAttachments = "                              + deviceLimits.maxColorAttachments +
            ", sampledImageColorSampleCounts = "                    + "0b" + Long ( deviceLimits.sampledImageColorSampleCounts ).toString(2) +
            ", sampledImageIntegerSampleCounts = "                  + "0b" + Long ( deviceLimits.sampledImageIntegerSampleCounts ).toString(2) +
            ", sampledImageDepthSampleCounts = "                    + "0b" + Long ( deviceLimits.sampledImageDepthSampleCounts ).toString(2) +
            ", sampledImageStencilSampleCounts = "                  + "0b" + Long ( deviceLimits.sampledImageStencilSampleCounts ).toString(2) +
            ", storageImageSampleCounts = "                         + "0b" + Long ( deviceLimits.storageImageSampleCounts ).toString(2) +
            ", maxSampleMaskWords = "                               + deviceLimits.maxSampleMaskWords +
            ", timestampComputeAndGraphics = "                      + ( deviceLimits.timestampComputeAndGraphics == VK_TRUE ? "true" : "false" ) +
            ", timestampPeriod = "                                  + deviceLimits.timestampPeriod +
            ", maxClipDistances = "                                 + deviceLimits.maxClipDistances +
            ", maxCullDistances = "                                 + deviceLimits.maxCullDistances +
            ", maxCombinedClipAndCullDistances = "                  + deviceLimits.maxCombinedClipAndCullDistances +
            ", discreteQueuePriorities = "                          + deviceLimits.discreteQueuePriorities +
            ", pointSizeRange = [ "                                 + deviceLimits.pointSizeRange[0] + ", " + deviceLimits.pointSizeRange[1] + " ]" +
            ", lineWidthRange = [ "                                 + deviceLimits.lineWidthRange[0] + ", " + deviceLimits.lineWidthRange[1] + " ]" +
            ", pointSizeGranularity = "                             + deviceLimits.pointSizeGranularity +
            ", lineWidthGranularity = "                             + deviceLimits.lineWidthGranularity +
            ", strictLines = "                                      + ( deviceLimits.strictLines == VK_TRUE ? "true" : "false" ) +
            ", standardSampleLocations = "                          + ( deviceLimits.standardSampleLocations == VK_TRUE ? "true" : "false" ) +
            ", optimalBufferCopyOffsetAlignment = "                 + toString ( deviceLimits.optimalBufferCopyOffsetAlignment ) +
            ", optimalBufferCopyRowPitchAlignment = "               + toString ( deviceLimits.optimalBufferCopyRowPitchAlignment ) +
            ", nonCoherentAtomSize = "                              + toString ( deviceLimits.nonCoherentAtomSize ) +
            " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceSparseProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceSparseProperties ) ) " "
            "{ residencyStandard2DBlockShape = "_s          + properties.residencyStandard2DBlockShape +
            ", residencyStandard2DMultisampleBlockShape = " + properties.residencyStandard2DMultisampleBlockShape +
            ", residencyStandard3DBlockShape = "            + properties.residencyStandard3DBlockShape +
            ", residencyAlignedMipSize = "                  + properties.residencyAlignedMipSize +
            ", residencyNonResidentStrict = "               + properties.residencyNonResidentStrict +
            " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceProperties ) ) " "
            "{ apiVersion = "           + versionReadableFormat ( properties.apiVersion ) +
            ", driverVersion = "        + properties.driverVersion +
            ", vendorID = "             + properties.vendorID +
            ", deviceID = "             + properties.deviceID +
            ", deviceType = "           + toString ( properties.deviceType ) +
            ", deviceName = "           + properties.deviceName +
            ", pipelineCacheUUID = "    + :: toString ( properties.pipelineCacheUUID ) + // NOLINT(clion-misra-cpp2008-5-2-12)
            ", limits = "               + toString ( properties.limits ) +
            ", sparseProperties = "     + toString ( properties.sparseProperties ) +
            " }";
}

static auto deduceAndMoveToNextInPropertiesChain (
        vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * pInStructure
) noexcept -> String {
    if ( pInStructure == nullptr ) {
        return "null";
    }

    return "";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceExtendedProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceExtendedProperties ) ) " "
            "{ type = "_s          + toString ( properties.structureType ) +
            ", baseProperties = "   + toString ( properties.properties ) +
            ", nextInChain = "      + deduceAndMoveToNextInPropertiesChain (
                    reinterpret_cast < __C_ENG_TYPE ( GenericOutStructure ) * > ( properties.pNext )
            ) +
            " }";
}

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceVulkan11Properties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceVulkan11Properties ) ) " "
            "{ type = "_s                               + toString ( properties.structureType ) +
            ", pNext = "                                + :: toString ( properties.pNext ) +
            ", deviceUUID = "                           + :: toString ( properties.deviceUUID ) + // NOLINT(clion-misra-cpp2008-5-2-12)
            ", driverUUID = "                           + :: toString ( properties.driverUUID ) + // NOLINT(clion-misra-cpp2008-5-2-12)
            ", deviceLUID = "                           + :: toString ( properties.deviceLUID ) + // NOLINT(clion-misra-cpp2008-5-2-12)
            ", deviceNodeMask = "                       + properties.deviceNodeMask +
            ", deviceLUIDValid = "                      + ( properties.deviceLUIDValid == VK_TRUE ? "true" : "false" ) +
            ", subgroupSize = "                         + properties.subgroupSize +
            ", subgroupSupportedStages = "              + "0b" + Long ( properties.subgroupSupportedStages ).toString(2) +
            ", subgroupSupportedOperations = "          + "0b" + Long ( properties.subgroupSupportedOperations ).toString(2) +
            ", subgroupQuadOperationsInAllStages = "    + ( properties.subgroupQuadOperationsInAllStages == VK_TRUE ? "true" : "false" ) +
            ", pointClippingBehavior = "                + toString ( properties.pointClippingBehavior ) +
            ", maxMultiviewViewCount = "                + properties.maxMultiviewViewCount +
            ", maxMultiviewInstanceIndex = "            + properties.maxMultiviewInstanceIndex +
            ", protectedNoFault = "                     + ( properties.protectedNoFault == VK_TRUE ? "true" : "false" ) +
            ", maxPerSetDescriptors = "                 + properties.maxPerSetDescriptors +
            ", maxMemoryAllocationSize = "              + toString ( properties.maxMemoryAllocationSize ) +
            " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceIDProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceIDProperties ) ) " "
            "{ type = "_s                               + toString ( properties.structureType ) +
            ", pNext = "                                + :: toString ( properties.pNext ) +
            ", deviceUUID = "                           + :: toString ( properties.deviceUUID ) + // NOLINT(clion-misra-cpp2008-5-2-12)
            ", driverUUID = "                           + :: toString ( properties.driverUUID ) + // NOLINT(clion-misra-cpp2008-5-2-12)
            ", deviceLUID = "                           + :: toString ( properties.deviceLUID ) + // NOLINT(clion-misra-cpp2008-5-2-12)
            ", deviceNodeMask = "                       + properties.deviceNodeMask +
            ", deviceLUIDValid = "                      + ( properties.deviceLUIDValid == VK_TRUE ? "true" : "false" ) +
            " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceMaintenanceProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceMaintenanceProperties ) ) " "
            "{ type = "_s                               + toString ( properties.structureType ) +
            ", pNext = "                                + :: toString ( properties.pNext ) +
            ", maxPerSetDescriptors = "                 + properties.maxPerSetDescriptors +
            ", maxMemoryAllocationSize = "              + toString ( properties.maxMemoryAllocationSize ) +
            " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceMultiviewProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceMultiviewProperties ) ) " "
            "{ type = "_s                               + toString ( properties.structureType ) +
            ", pNext = "                                + :: toString ( properties.pNext ) +
            ", maxMultiviewViewCount = "                + properties.maxMultiviewViewCount +
            ", maxMultiviewInstanceIndex = "            + properties.maxMultiviewInstanceIndex +
            " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDevicePointClippingProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDevicePointClippingProperties ) ) " "
            "{ type = "_s                               + toString ( properties.structureType ) +
            ", pNext = "                                + :: toString ( properties.pNext ) +
            ", pointClippingBehavior = "                + toString ( properties.pointClippingBehavior ) +
            " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceProtectedMemoryProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceProtectedMemoryProperties ) ) " "
            "{ type = "_s                               + toString ( properties.structureType ) +
            ", pNext = "                                + :: toString ( properties.pNext ) +
            ", protectedNoFault = "                     + ( properties.protectedNoFault == VK_TRUE ? "true" : "false" ) +
            " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceSubgroupProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceSubgroupProperties ) ) " "
            "{ type = "_s                               + toString ( properties.structureType ) +
            ", pNext = "                                + :: toString ( properties.pNext ) +
            ", subgroupSize = "                         + properties.subgroupSize +
            ", supportedStages = "                      + "0b" + Long ( properties.supportedStages ).toString(2) +
            ", supportedOperations = "                  + "0b" + Long ( properties.supportedOperations ).toString(2) +
            ", quadOperationsInAllStages = "            + ( properties.quadOperationsInAllStages == VK_TRUE ? "true" : "false" ) +
            " }";
}

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( ConformanceVersion ) const & version
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( ConformanceVersion ) ) " "
            "{ major = "_s      + version.major +
            ", minor = "        + version.minor +
            ", subminor = "     + version.subminor +
            ", patch = "        + version.patch +
            " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceVulkan12Properties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceVulkan12Properties ) ) " "
            "{ type = "_s                                               + toString ( properties.structureType ) +
            ", pNext = "                                                + :: toString ( properties.pNext ) +
            ", driverID = "                                             + toString ( properties.driverID ) +
            ", driverName = "                                           + properties.driverName +
            ", driverInfo = "                                           + properties.driverInfo +
            ", conformanceVersion = "                                   + toString ( properties.conformanceVersion ) +
            ", denormBehaviorIndependence = "                           + toString ( properties.denormBehaviorIndependence ) +
            ", roundingModeIndependence = "                             + toString ( properties.roundingModeIndependence ) +
            ", shaderSignedZeroInfNanPreserveFloat16 = "                + ( properties.shaderSignedZeroInfNanPreserveFloat16 == VK_TRUE ? "true" : "false" ) +
            ", shaderSignedZeroInfNanPreserveFloat32 = "                + ( properties.shaderSignedZeroInfNanPreserveFloat32 == VK_TRUE ? "true" : "false" ) +
            ", shaderSignedZeroInfNanPreserveFloat64 = "                + ( properties.shaderSignedZeroInfNanPreserveFloat64 == VK_TRUE ? "true" : "false" ) +
            ", shaderDenormPreserveFloat16 = "                          + ( properties.shaderDenormPreserveFloat16 == VK_TRUE ? "true" : "false" ) +
            ", shaderDenormPreserveFloat32 = "                          + ( properties.shaderDenormPreserveFloat32 == VK_TRUE ? "true" : "false" ) +
            ", shaderDenormPreserveFloat64 = "                          + ( properties.shaderDenormPreserveFloat64 == VK_TRUE ? "true" : "false" ) +
            ", shaderDenormFlushToZeroFloat16 = "                       + ( properties.shaderDenormFlushToZeroFloat16 == VK_TRUE ? "true" : "false" ) +
            ", shaderDenormFlushToZeroFloat32 = "                       + ( properties.shaderDenormFlushToZeroFloat32 == VK_TRUE ? "true" : "false" ) +
            ", shaderDenormFlushToZeroFloat64 = "                       + ( properties.shaderDenormFlushToZeroFloat64 == VK_TRUE ? "true" : "false" ) +
            ", shaderRoundingModeRTEFloat16 = "                         + ( properties.shaderRoundingModeRTEFloat16 == VK_TRUE ? "true" : "false" ) +
            ", shaderRoundingModeRTEFloat32 = "                         + ( properties.shaderRoundingModeRTEFloat32 == VK_TRUE ? "true" : "false" ) +
            ", shaderRoundingModeRTEFloat64 = "                         + ( properties.shaderRoundingModeRTEFloat64 == VK_TRUE ? "true" : "false" ) +
            ", shaderRoundingModeRTZFloat16 = "                         + ( properties.shaderRoundingModeRTZFloat16 == VK_TRUE ? "true" : "false" ) +
            ", shaderRoundingModeRTZFloat32 = "                         + ( properties.shaderRoundingModeRTZFloat32 == VK_TRUE ? "true" : "false" ) +
            ", shaderRoundingModeRTZFloat64 = "                         + ( properties.shaderRoundingModeRTZFloat64 == VK_TRUE ? "true" : "false" ) +
            ", maxUpdateAfterBindDescriptorsInAllPools = "              + properties.maxUpdateAfterBindDescriptorsInAllPools +
            ", shaderUniformBufferArrayNonUniformIndexingNative = "     + ( properties.shaderUniformBufferArrayNonUniformIndexingNative == VK_TRUE ? "true" : "false" ) +
            ", shaderSampledImageArrayNonUniformIndexingNative = "      + ( properties.shaderSampledImageArrayNonUniformIndexingNative == VK_TRUE ? "true" : "false" ) +
            ", shaderStorageBufferArrayNonUniformIndexingNative = "     + ( properties.shaderStorageBufferArrayNonUniformIndexingNative == VK_TRUE ? "true" : "false" ) +
            ", shaderStorageImageArrayNonUniformIndexingNative = "      + ( properties.shaderStorageImageArrayNonUniformIndexingNative == VK_TRUE ? "true" : "false" ) +
            ", shaderInputAttachmentArrayNonUniformIndexingNative = "   + ( properties.shaderInputAttachmentArrayNonUniformIndexingNative == VK_TRUE ? "true" : "false" ) +
            ", robustBufferAccessUpdateAfterBind = "                    + ( properties.robustBufferAccessUpdateAfterBind == VK_TRUE ? "true" : "false" ) +
            ", quadDivergentImplicitLod = "                             + ( properties.quadDivergentImplicitLod == VK_TRUE ? "true" : "false" ) +
            ", maxPerStageDescriptorUpdateAfterBindSamplers = "         + properties.maxPerStageDescriptorUpdateAfterBindSamplers +
            ", maxPerStageDescriptorUpdateAfterBindUniformBuffers = "   + properties.maxPerStageDescriptorUpdateAfterBindUniformBuffers +
            ", maxPerStageDescriptorUpdateAfterBindStorageBuffers = "   + properties.maxPerStageDescriptorUpdateAfterBindStorageBuffers +
            ", maxPerStageDescriptorUpdateAfterBindSampledImages = "    + properties.maxPerStageDescriptorUpdateAfterBindSampledImages +
            ", maxPerStageDescriptorUpdateAfterBindStoredImages = "     + properties.maxPerStageDescriptorUpdateAfterBindStorageImages +
            ", maxPerStageDescriptorUpdateAfterBindInputAttachments = " + properties.maxPerStageDescriptorUpdateAfterBindInputAttachments +
            ", maxPerStageUpdateAfterBindResources = "                  + properties.maxPerStageUpdateAfterBindResources +
            ", maxDescriptorSetUpdateAfterBindSamplers = "              + properties.maxDescriptorSetUpdateAfterBindSamplers +
            ", maxDescriptorSetUpdateAfterBindUniformBuffers = "        + properties.maxDescriptorSetUpdateAfterBindUniformBuffers +
            ", maxDescriptorSetUpdateAfterBindUniformBuffersDynamic = " + properties.maxDescriptorSetUpdateAfterBindUniformBuffersDynamic +
            ", maxDescriptorSetUpdateAfterBindStorageBuffers = "        + properties.maxDescriptorSetUpdateAfterBindStorageBuffers +
            ", maxDescriptorSetUpdateAfterBindStorageBuffersDynamic = " + properties.maxDescriptorSetUpdateAfterBindStorageBuffersDynamic +
            ", maxDescriptorSetUpdateAfterBindSampledImages = "         + properties.maxDescriptorSetUpdateAfterBindSampledImages +
            ", maxDescriptorSetUpdateAfterBindStorageImages = "         + properties.maxDescriptorSetUpdateAfterBindStorageImages +
            ", maxDescriptorSetUpdateAfterBindBindInputAttachments = "  + properties.maxDescriptorSetUpdateAfterBindInputAttachments +
            ", supportedDepthResolveModes = "                           + toString ( properties.supportedDepthResolveModes ) +
            ", supportedStencilResolveModes = "                         + toString ( properties.supportedStencilResolveModes ) +
            ", independentResolveNone = "                               + ( properties.independentResolveNone == VK_TRUE ? "true" : "false" ) +
            ", independentResolve = "                                   + ( properties.independentResolve == VK_TRUE ? "true" : "false" ) +
            ", filterMinmaxSingleComponentsFormats = "                  + ( properties.filterMinmaxSingleComponentFormats == VK_TRUE ? "true" : "false" ) +
            ", filterMinmaxImageComponentsMapping = "                   + ( properties.filterMinmaxImageComponentMapping == VK_TRUE ? "true" : "false" ) +
            ", maxTimelineSemaphoreValueDifference = "                  + properties.maxTimelineSemaphoreValueDifference +
            ", framebufferIntegerColorSampleCounts = "                  + toString ( properties.framebufferIntegerColorSampleCounts ) +
            " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceDriverProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceDriverProperties ) ) " "
            "{ type = "_s                                               + toString ( properties.structureType ) +
            ", pNext = "                                                + :: toString ( properties.pNext ) +
            ", driverID = "                                             + toString ( properties.driverID ) +
            ", driverName = "                                           + properties.driverName +
            ", driverInfo = "                                           + properties.driverInfo +
            ", conformanceVersion = "                                   + toString ( properties.conformanceVersion ) +
            " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceDepthStencilResolveProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceDepthStencilResolveProperties ) ) " "
            "{ type = "_s                       + toString ( properties.structureType ) +
            ", pNext = "                        + :: toString ( properties.pNext ) +
            ", supportedDepthResolveModes = "   + "0b" + Long ( properties.supportedDepthResolveModes ).toString(2) +
            ", supportedStencilResolveModes = " + "0b" + Long ( properties.supportedStencilResolveModes ).toString(2) +
            ", independentResolveNone = "       + ( properties.independentResolveNone == VK_TRUE ? "true" : "false" ) +
            ", independentResolve = "           + ( properties.independentResolve == VK_TRUE ? "true" : "false" ) +
            " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceDescriptorIndexingProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceDescriptorIndexingProperties ) ) " "
            "{ type = "_s                                               + toString ( properties.structureType ) +
            ", pNext = "                                                + :: toString ( properties.pNext ) +
            ", maxUpdateAfterBindDescriptorsInAllPools = "              + properties.maxUpdateAfterBindDescriptorsInAllPools +
            ", shaderUniformBufferArrayNonUniformIndexingNative = "     + ( properties.shaderUniformBufferArrayNonUniformIndexingNative == VK_TRUE ? "true" : "false" ) +
            ", shaderSampledImageArrayNonUniformIndexingNative = "      + ( properties.shaderSampledImageArrayNonUniformIndexingNative == VK_TRUE ? "true" : "false" ) +
            ", shaderStorageBufferArrayNonUniformIndexingNative = "     + ( properties.shaderStorageBufferArrayNonUniformIndexingNative == VK_TRUE ? "true" : "false" ) +
            ", shaderStorageImageArrayNonUniformIndexingNative = "      + ( properties.shaderStorageImageArrayNonUniformIndexingNative == VK_TRUE ? "true" : "false" ) +
            ", shaderInputAttachmentArrayNonUniformIndexingNative = "   + ( properties.shaderInputAttachmentArrayNonUniformIndexingNative == VK_TRUE ? "true" : "false" ) +
            ", robustBufferAccessUpdateAfterBind = "                    + ( properties.robustBufferAccessUpdateAfterBind == VK_TRUE ? "true" : "false" ) +
            ", quadDivergentImplicitLod = "                             + ( properties.quadDivergentImplicitLod == VK_TRUE ? "true" : "false" ) +
            ", maxPerStageDescriptorUpdateAfterBindSamplers = "         + properties.maxPerStageDescriptorUpdateAfterBindSamplers +
            ", maxPerStageDescriptorUpdateAfterBindUniformBuffers = "   + properties.maxPerStageDescriptorUpdateAfterBindUniformBuffers +
            ", maxPerStageDescriptorUpdateAfterBindStorageBuffers = "   + properties.maxPerStageDescriptorUpdateAfterBindStorageBuffers +
            ", maxPerStageDescriptorUpdateAfterBindSampledImages = "    + properties.maxPerStageDescriptorUpdateAfterBindSampledImages +
            ", maxPerStageDescriptorUpdateAfterBindStorageImages = "    + properties.maxPerStageDescriptorUpdateAfterBindStorageImages +
            ", maxPerStageDescriptorUpdateAfterBindInputAttachments = " + properties.maxPerStageDescriptorUpdateAfterBindInputAttachments +
            ", maxPerStageUpdateAfterBindResources = "                  + properties.maxPerStageUpdateAfterBindResources +
            ", maxDescriptorSetUpdateAfterBindSamplers = "              + properties.maxDescriptorSetUpdateAfterBindSamplers +
            ", maxDescriptorSetUpdateAfterBindUniformBuffers = "        + properties.maxDescriptorSetUpdateAfterBindUniformBuffers +
            ", maxDescriptorSetUpdateAfterBindUniformBuffersDynamic = " + properties.maxDescriptorSetUpdateAfterBindUniformBuffersDynamic +
            ", maxDescriptorSetUpdateAfterBindStorageBuffers = "        + properties.maxDescriptorSetUpdateAfterBindStorageBuffers +
            ", maxDescriptorSetUpdateAfterBindStorageBuffersDynamic = " + properties.maxDescriptorSetUpdateAfterBindStorageBuffersDynamic +
            ", maxDescriptorSetUpdateAfterBindSampledImages = "         + properties.maxDescriptorSetUpdateAfterBindSampledImages +
            ", maxDescriptorSetUpdateAfterBindStorageImages = "         + properties.maxDescriptorSetUpdateAfterBindStorageImages +
            ", maxDescriptorSetUpdateAfterBindInputAttachments = "      + properties.maxDescriptorSetUpdateAfterBindInputAttachments +
            " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceFloatControlsProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceFloatControlsProperties ) ) " "
            "{ type = "_s                                   + toString ( properties.structureType ) +
            ", pNext = "                                    + :: toString ( properties.pNext ) +
            ", denormBehaviorIndependence = "               + "0b" + Long ( properties.denormBehaviorIndependence ).toString(2) +
            ", roundingModeIndependence = "                 + "0b" + Long ( properties.roundingModeIndependence ).toString(2) +
            ", shaderSignedZeroInfNanPreserveFloat16 = "    + ( properties.shaderSignedZeroInfNanPreserveFloat16 == VK_TRUE ? "true" : "false" ) +
            ", shaderSignedZeroInfNanPreserveFloat32 = "    + ( properties.shaderSignedZeroInfNanPreserveFloat32 == VK_TRUE ? "true" : "false" ) +
            ", shaderSignedZeroInfNanPreserveFloat64 = "    + ( properties.shaderSignedZeroInfNanPreserveFloat64 == VK_TRUE ? "true" : "false" ) +
            ", shaderDenormPreserveFloat16 = "              + ( properties.shaderDenormPreserveFloat16 == VK_TRUE ? "true" : "false" ) +
            ", shaderDenormPreserveFloat32 = "              + ( properties.shaderDenormPreserveFloat32 == VK_TRUE ? "true" : "false" ) +
            ", shaderDenormPreserveFloat64 = "              + ( properties.shaderDenormPreserveFloat64 == VK_TRUE ? "true" : "false" ) +
            ", shaderDenormFlushToZeroFloat16 = "           + ( properties.shaderDenormFlushToZeroFloat16 == VK_TRUE ? "true" : "false" ) +
            ", shaderDenormFlushToZeroFloat32 = "           + ( properties.shaderDenormFlushToZeroFloat32 == VK_TRUE ? "true" : "false" ) +
            ", shaderDenormFlushToZeroFloat64 = "           + ( properties.shaderDenormFlushToZeroFloat64 == VK_TRUE ? "true" : "false" ) +
            ", shaderRoundingModeRTEFloat16 = "             + ( properties.shaderRoundingModeRTEFloat16 == VK_TRUE ? "true" : "false" ) +
            ", shaderRoundingModeRTEFloat32 = "             + ( properties.shaderRoundingModeRTEFloat32 == VK_TRUE ? "true" : "false" ) +
            ", shaderRoundingModeRTEFloat64 = "             + ( properties.shaderRoundingModeRTEFloat64 == VK_TRUE ? "true" : "false" ) +
            ", shaderRoundingModeRTZFloat16 = "             + ( properties.shaderRoundingModeRTZFloat16 == VK_TRUE ? "true" : "false" ) +
            ", shaderRoundingModeRTZFloat32 = "             + ( properties.shaderRoundingModeRTZFloat32 == VK_TRUE ? "true" : "false" ) +
            ", shaderRoundingModeRTZFloat64 = "             + ( properties.shaderRoundingModeRTZFloat64 == VK_TRUE ? "true" : "false" ) +
            " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceSamplerFilterMinmaxProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceSamplerFilterMinmaxProperties ) ) " "
            "{ type = "_s                                   + toString ( properties.structureType ) +
            ", pNext = "                                    + :: toString ( properties.pNext ) +
            ", filterMinmaxSingleComponentFormats = "       + ( properties.filterMinmaxSingleComponentFormats == VK_TRUE ? "true" : "false" ) +
            ", filterMinmaxImageComponentMapping = "        + ( properties.filterMinmaxImageComponentMapping == VK_TRUE ? "true" : "false" ) +
            " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceTimelineSemaphoreProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceSamplerFilterMinmaxProperties ) ) " "
            "{ type = "_s                                   + toString ( properties.structureType ) +
            ", pNext = "                                    + :: toString ( properties.pNext ) +
            ", maxTimelineSemaphoreValueDifference = "      + properties.maxTimelineSemaphoreValueDifference +
            " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PCI_BUS_INFO_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDevicePCIBusInfoProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDevicePCIBusInfoProperties ) ) " "
           "{ type = "_s        + toString ( properties.structureType ) +
           ", pNext = "         + :: toString ( properties.pNext ) +
           ", pciDomain = "     + properties.pciDomain+
           ", pciBus = "        + properties.pciBus +
           ", pciDevice = "     + properties.pciDevice +
           ", pciFunction = "   + properties.pciFunction +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PHYSICAL_DEVICE_DRM_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceDRMProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceDRMProperties ) ) " "
           "{ type = "_s        + toString ( properties.structureType ) +
           ", pNext = "         + :: toString ( properties.pNext ) +
           ", hasPrimary = "    + ( properties.hasPrimary == VK_TRUE ? "true" : "false" ) +
           ", hasRender = "     + ( properties.hasRender == VK_TRUE ? "true" : "false" ) +
           ", primaryMajor = "  + properties.primaryMajor +
           ", primaryMinor = "  + properties.primaryMinor +
           ", renderMajor = "   + properties.renderMajor +
           ", renderMinor = "   + properties.renderMinor +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceAccelerationStructureProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceAccelerationStructureProperties ) ) " "
           "{ type = "_s                                                        + toString ( properties.structureType ) +
           ", pNext = "                                                         + :: toString ( properties.pNext ) +
           ", maxGeometryCount = "                                              + properties.maxGeometryCount +
           ", maxInstanceCount = "                                              + properties.maxInstanceCount +
           ", maxPrimitiveCount = "                                             + properties.maxPrimitiveCount +
           ", maxPerStageDescriptorAccelerationStructures = "                   + properties.maxPerStageDescriptorAccelerationStructures +
           ", maxPerStageDescriptorUpdateAfterBindAccelerationStructures = "    + properties.maxPerStageDescriptorUpdateAfterBindAccelerationStructures +
           ", maxDescriptorSetAccelerationStructures = "                        + properties.maxDescriptorSetAccelerationStructures +
           ", maxDescriptorSetUpdateAfterBindAccelerationStructures = "         + properties.maxDescriptorSetUpdateAfterBindAccelerationStructures +
           ", minAccelerationStructureScratchOffsetAlignment = "                + properties.minAccelerationStructureScratchOffsetAlignment +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceBlendOperationAdvancedProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceBlendOperationAdvancedProperties ) ) " "
           "{ type = "_s                                    + toString ( properties.structureType ) +
           ", pNext = "                                     + :: toString ( properties.pNext ) +
           ", advancedBlendMaxColorAttachments = "          + properties.advancedBlendMaxColorAttachments +
           ", advancedBlendIndependentBlend = "             + ( properties.advancedBlendIndependentBlend == VK_TRUE ? "true" : "false" ) +
           ", advancedBlendNonPremultipliedSrcColor = "     + ( properties.advancedBlendNonPremultipliedSrcColor == VK_TRUE ? "true" : "false" ) +
           ", advancedBlendNonPremultipliedDstColor = "     + ( properties.advancedBlendNonPremultipliedDstColor == VK_TRUE ? "true" : "false" ) +
           ", advancedBlendCorrelatedOverlap = "            + ( properties.advancedBlendCorrelatedOverlap == VK_TRUE ? "true" : "false" ) +
           ", advancedBlendAllOperations = "                + ( properties.advancedBlendAllOperations == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONSERVATIVE_RASTERIZATION_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceConservativeRasterizationProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceConservativeRasterizationProperties ) ) " "
           "{ type = "_s                                        + toString ( properties.structureType ) +
           ", pNext = "                                         + :: toString ( properties.pNext ) +
           ", primitiveOverestimationSize = "                   + properties.primitiveOverestimationSize +
           ", maxExtraPrimitiveOverestimationSize = "           + properties.maxExtraPrimitiveOverestimationSize +
           ", extraPrimitiveOverestimationSizeGranularity = "   + properties.extraPrimitiveOverestimationSizeGranularity +
           ", primitiveUnderestimation = "                      + ( properties.primitiveUnderestimation == VK_TRUE ? "true" : "false" ) +
           ", conservativePointAndLineRasterization = "         + ( properties.conservativePointAndLineRasterization == VK_TRUE ? "true" : "false" ) +
           ", degenerateTrianglesRasterized = "                 + ( properties.degenerateTrianglesRasterized == VK_TRUE ? "true" : "false" ) +
           ", degenerateLinesRasterized = "                     + ( properties.degenerateLinesRasterized == VK_TRUE ? "true" : "false" ) +
           ", fullyCoveredFragmentShaderInputVariable = "       + ( properties.fullyCoveredFragmentShaderInputVariable == VK_TRUE ? "true" : "false" ) +
           ", conservativeRasterizationPostDepthCoverage = "    + ( properties.conservativeRasterizationPostDepthCoverage == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceCooperativeMatrixPropertiesNVidia ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceCooperativeMatrixPropertiesNVidia ) ) " "
           "{ type = "_s                                        + toString ( properties.structureType ) +
           ", pNext = "                                         + :: toString ( properties.pNext ) +
           ", cooperativeMatrixSupportedStages = "              + "0b" + Long ( properties.cooperativeMatrixSupportedStages ).toString(2) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceCustomBorderColorProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceCustomBorderColorProperties ) ) " "
           "{ type = "_s                                        + toString ( properties.structureType ) +
           ", pNext = "                                         + :: toString ( properties.pNext ) +
           ", maxCustomBorderColorSamples = "                   + properties.maxCustomBorderColorSamplers +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceDeviceGeneratedCommandsPropertiesNVidia ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceDeviceGeneratedCommandsPropertiesNVidia ) ) " "
           "{ type = "_s                                    + toString ( properties.structureType ) +
           ", pNext = "                                     + :: toString ( properties.pNext ) +
           ", maxGraphicsShaderGroupCount = "               + properties.maxGraphicsShaderGroupCount +
           ", maxIndirectSequenceCount = "                  + properties.maxIndirectSequenceCount +
           ", maxIndirectCommandsTokenCount = "             + properties.maxIndirectCommandsTokenCount +
           ", maxIndirectCommandsStreamCount = "            + properties.maxIndirectCommandsStreamCount +
           ", maxIndirectCommandsTokenOffset = "            + properties.maxIndirectCommandsTokenOffset +
           ", maxIndirectCommandsStreamStride = "           + properties.maxIndirectCommandsStreamStride +
           ", minSequencesCountBufferOffsetAlignment = "    + properties.minSequencesCountBufferOffsetAlignment +
           ", minSequencesIndexBufferOffsetAlignment = "    + properties.minSequencesIndexBufferOffsetAlignment +
           ", minIndirectCommandsBufferOffsetAlignment = "  + properties.minIndirectCommandsBufferOffsetAlignment +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISCARD_RECTANGLES_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceDiscardRectangleProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceDiscardRectangleProperties ) ) " "
           "{ type = "_s                                    + toString ( properties.structureType ) +
           ", pNext = "                                     + :: toString ( properties.pNext ) +
           ", maxDiscardRectangles = "                      + properties.maxDiscardRectangles +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTERNAL_MEMORY_HOST_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceExternalMemoryHostProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceExternalMemoryHostProperties ) ) " "
           "{ type = "_s                                    + toString ( properties.structureType ) +
           ", pNext = "                                     + :: toString ( properties.pNext ) +
           ", minImportedHostPointerAlignment = "           + toString ( properties.minImportedHostPointerAlignment ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMap2Properties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMap2Properties ) ) " "
           "{ type = "_s                                    + toString ( properties.structureType ) +
           ", pNext = "                                     + :: toString ( properties.pNext ) +
           ", subsampledLoads = "                           + ( properties.subsampledLoads == VK_TRUE ? "true" : "false" ) +
           ", subsampledCoarseReconstructionEarlyAccess = " + ( properties.subsampledCoarseReconstructionEarlyAccess == VK_TRUE ? "true" : "false" ) +
           ", maxSubsampledArrayLayers = "                  + properties.maxSubsampledArrayLayers +
           ", maxDescriptorSetSubsampledSamplers = "        + properties.maxDescriptorSetSubsampledSamplers +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMapOffsetPropertiesQualcomm ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMapOffsetPropertiesQualcomm ) ) " "
           "{ type = "_s                                    + toString ( properties.structureType ) +
           ", pNext = "                                     + :: toString ( properties.pNext ) +
           ", fragmentDensityOffsetGranularity = "          + toString ( properties.fragmentDensityOffsetGranularity ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMapProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMapProperties ) ) " "
           "{ type = "_s                        + toString ( properties.structureType ) +
           ", pNext = "                         + :: toString ( properties.pNext ) +
           ", minFragmentDensityTexelSize = "   + toString ( properties.minFragmentDensityTexelSize ) +
           ", maxFragmentDensityTexelSize = "   + toString ( properties.maxFragmentDensityTexelSize ) +
           ", fragmentDensityInvocations = "    + ( properties.fragmentDensityInvocations == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceFragmentShadingRateEnumsPropertiesNVidia ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceFragmentShadingRateEnumsPropertiesNVidia ) ) " "
           "{ type = "_s                                + toString ( properties.structureType ) +
           ", pNext = "                                 + :: toString ( properties.pNext ) +
           ", maxFragmentShadingRateInvocationCount = " + toString ( properties.maxFragmentShadingRateInvocationCount ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceFragmentShadingRateProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceFragmentShadingRateProperties ) ) " "
           "{ type = "_s                                                + toString ( properties.structureType ) +
           ", pNext = "                                                 + :: toString ( properties.pNext ) +
           ", maxFragmentShadingRateAttachmentTexelSize = "             + toString ( properties.maxFragmentShadingRateAttachmentTexelSize ) +
           ", minFragmentShadingRateAttachmentTexelSize = "             + toString ( properties.minFragmentShadingRateAttachmentTexelSize ) +
           ", maxFragmentShadingRateAttachmentTexelSizeAspectRatio = "  + properties.maxFragmentShadingRateAttachmentTexelSizeAspectRatio +
           ", primitiveFragmentShadingRateWithMultipleViewports = "     + ( properties.primitiveFragmentShadingRateWithMultipleViewports == VK_TRUE ? "true" : "false" ) +
           ", layeredShadingRateAttachments = "                         + ( properties.layeredShadingRateAttachments == VK_TRUE ? "true" : "false" ) +
           ", fragmentShadingRateNonTrivialCombinerOps = "              + ( properties.fragmentShadingRateNonTrivialCombinerOps == VK_TRUE ? "true" : "false" ) +
           ", maxFragmentSize = "                                       + toString ( properties.maxFragmentSize ) +
           ", maxFragmentSizeAspectRatio = "                            + properties.maxFragmentSizeAspectRatio +
           ", maxFragmentShadingRateCoverageSamples = "                 + properties.maxFragmentShadingRateCoverageSamples +
           ", maxFragmentShadingRateRasterizationSamples = "            + toString ( properties.maxFragmentShadingRateRasterizationSamples ) +
           ", fragmentShadingRateWithShaderDepthStencilWrites = "       + ( properties.fragmentShadingRateWithShaderDepthStencilWrites == VK_TRUE ? "true" : "false" ) +
           ", fragmentShadingRateWithSampleMask = "                     + ( properties.fragmentShadingRateWithSampleMask == VK_TRUE ? "true" : "false" ) +
           ", fragmentShadingRateWithShaderSampleMask = "               + ( properties.fragmentShadingRateWithShaderSampleMask == VK_TRUE ? "true" : "false" ) +
           ", fragmentShadingRateWithConservativeRasterization = "      + ( properties.fragmentShadingRateWithConservativeRasterization == VK_TRUE ? "true" : "false" ) +
           ", fragmentShadingRateWithFragmentShaderInterlock = "        + ( properties.fragmentShadingRateWithFragmentShaderInterlock == VK_TRUE ? "true" : "false" ) +
           ", fragmentShadingRateWithCustomSampleLocations = "          + ( properties.fragmentShadingRateWithCustomSampleLocations == VK_TRUE ? "true" : "false" ) +
           ", fragmentShadingRateStrictMultiplyCombiner = "             + ( properties.fragmentShadingRateStrictMultiplyCombiner == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceInlineUniformBlockProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceInlineUniformBlockProperties ) ) " "
           "{ type = "_s                                                    + toString ( properties.structureType ) +
           ", pNext = "                                                     + :: toString ( properties.pNext ) +
           ", maxInlineUniformBlockSize = "                                 + properties.maxInlineUniformBlockSize +
           ", maxPerStageDescriptorInlineUniformBlocks = "                  + properties.maxPerStageDescriptorInlineUniformBlocks +
           ", maxPerStageDescriptorUpdateAfterBindInlineUniformBlocks = "   + properties.maxPerStageDescriptorUpdateAfterBindInlineUniformBlocks +
           ", maxDescriptorSetInlineUniformBlocks = "                       + properties.maxDescriptorSetInlineUniformBlocks +
           ", maxDescriptorSetUpdateAfterBindInlineUniformBlocks = "        + properties.maxDescriptorSetUpdateAfterBindInlineUniformBlocks +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceLineRasterizationProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceLineRasterizationProperties ) ) " "
           "{ type = "_s                                                    + toString ( properties.structureType ) +
           ", pNext = "                                                     + :: toString ( properties.pNext ) +
           ", lineSubPixelPrecisionBits = "                                 + properties.lineSubPixelPrecisionBits +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceMaintenance4Properties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceMaintenance4Properties ) ) " "
           "{ type = "_s                                                    + toString ( properties.structureType ) +
           ", pNext = "                                                     + :: toString ( properties.pNext ) +
           ", maxBufferSize = "                                             + toString ( properties.maxBufferSize ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceMeshShaderPropertiesNVidia ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceMeshShaderPropertiesNVidia ) ) " "
           "{ type = "_s                            + toString ( properties.structureType ) +
           ", pNext = "                             + :: toString ( properties.pNext ) +
           ", maxDrawMeshTasksCount = "             + properties.maxDrawMeshTasksCount +
           ", maxTaskWorkGroupInvocations = "       + properties.maxTaskWorkGroupInvocations +
           ", maxTaskWorkGroupSize = [ "            + properties.maxTaskWorkGroupSize[0] + ", " + properties.maxTaskWorkGroupSize[1] + ", " + properties.maxTaskWorkGroupSize[2] + " ]" +
           ", maxTaskTotalMemorySize = "            + properties.maxTaskTotalMemorySize +
           ", maxTaskOutputCount = "                + properties.maxTaskOutputCount +
           ", maxMeshWorkGroupInvocations = "       + properties.maxMeshWorkGroupInvocations +
           ", maxMeshWorkGroupSize = [ "            + properties.maxMeshWorkGroupSize[0] + ", " + properties.maxMeshWorkGroupSize[1] + ", " + properties.maxMeshWorkGroupSize[2] + " ]" +
           ", maxMeshTotalMemorySize = "            + properties.maxMeshTotalMemorySize +
           ", maxMeshOutputVertices = "             + properties.maxMeshOutputVertices +
           ", maxMeshOutputPrimitives = "           + properties.maxMeshOutputPrimitives +
           ", maxMeshMultiviewViewCount = "         + properties.maxMeshMultiviewViewCount +
           ", meshOutputPerVertexGranularity = "    + properties.meshOutputPerVertexGranularity +
           ", meshOutputPerPrimitiveGranularity = " + properties.meshOutputPerPrimitiveGranularity +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceMultiDrawProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceMultiDrawProperties ) ) " "
           "{ type = "_s                            + toString ( properties.structureType ) +
           ", pNext = "                             + :: toString ( properties.pNext ) +
           ", maxMultiDrawCount = "                 + properties.maxMultiDrawCount +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceMultiviewPerViewAttributesPropertiesNVidia ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceMultiviewPerViewAttributesPropertiesNVidia ) ) " "
           "{ type = "_s                            + toString ( properties.structureType ) +
           ", pNext = "                             + :: toString ( properties.pNext ) +
           ", perViewPositionAllComponents = "      + ( properties.perViewPositionAllComponents == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDevicePerformanceQueryProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDevicePerformanceQueryProperties ) ) " "
           "{ type = "_s                            + toString ( properties.structureType ) +
           ", pNext = "                             + :: toString ( properties.pNext ) +
           ", allowCommandBufferQueryCopies = "     + ( properties.allowCommandBufferQueryCopies == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDevicePortabilitySubsetProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDevicePortabilitySubsetProperties ) ) " "
           "{ type = "_s                                + toString ( properties.structureType ) +
           ", pNext = "                                 + :: toString ( properties.pNext ) +
           ", minVertexInputBindingStrideAlignment = "  + properties.minVertexInputBindingStrideAlignment +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceProvokingVertexProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceProvokingVertexProperties ) ) " "
           "{ type = "_s                                                + toString ( properties.structureType ) +
           ", pNext = "                                                 + :: toString ( properties.pNext ) +
           ", provokingVertexModePerPipeline = "                        + ( properties.provokingVertexModePerPipeline == VK_TRUE ? "true" : "false" ) +
           ", transformFeedbackPreservesTriangleFanProvokingVertex = "  + ( properties.transformFeedbackPreservesTriangleFanProvokingVertex == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PUSH_DESCRIPTOR_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDevicePushDescriptorProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDevicePushDescriptorProperties ) ) " "
           "{ type = "_s                + toString ( properties.structureType ) +
           ", pNext = "                 + :: toString ( properties.pNext ) +
           ", maxPushDescriptors = "    + properties.maxPushDescriptors +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceRayTracingPipelineProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDevicePushDescriptorProperties ) ) " "
           "{ type = "_s                                + toString ( properties.structureType ) +
           ", pNext = "                                 + :: toString ( properties.pNext ) +
           ", shaderGroupHandleSize = "                 + properties.shaderGroupHandleSize +
           ", maxRayRecursionDepth = "                  + properties.maxRayRecursionDepth +
           ", maxShaderGroupStride = "                  + properties.maxShaderGroupStride +
           ", shaderGroupBaseAlignment = "              + properties.shaderGroupBaseAlignment +
           ", shaderGroupHandleCaptureReplaySize = "    + properties.shaderGroupHandleCaptureReplaySize +
           ", maxRayDispatchInvocationCount = "         + properties.maxRayDispatchInvocationCount +
           ", shaderGroupHandleAlignment = "            + properties.shaderGroupHandleAlignment +
           ", maxRayHitAttributeSize = "                + properties.maxRayHitAttributeSize +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceRayTracingPropertiesNVidia ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceRayTracingPropertiesNVidia ) ) " "
           "{ type = "_s                                    + toString ( properties.structureType ) +
           ", pNext = "                                     + :: toString ( properties.pNext ) +
           ", shaderGroupHandleSize = "                     + properties.shaderGroupHandleSize +
           ", maxRecursionDepth = "                         + properties.maxRecursionDepth +
           ", maxShaderGroupStride = "                      + properties.maxShaderGroupStride +
           ", shaderGroupBaseAlignment = "                  + properties.shaderGroupBaseAlignment +
           ", maxGeometryCount = "                          + properties.maxGeometryCount +
           ", maxInstanceCount = "                          + properties.maxInstanceCount +
           ", maxTriangleCount = "                          + properties.maxTriangleCount +
           ", maxDescriptorSetAccelerationStructures = "    + properties.maxDescriptorSetAccelerationStructures +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceRobustnessProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceRobustnessProperties ) ) " "
           "{ type = "_s                                    + toString ( properties.structureType ) +
           ", pNext = "                                     + :: toString ( properties.pNext ) +
           ", robustStorageBufferAccessSizeAlignment = "    + toString ( properties.robustStorageBufferAccessSizeAlignment ) +
           ", robustUniformBufferAccessSizeAlignment = "    + toString ( properties.robustUniformBufferAccessSizeAlignment ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceSampleLocationsProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceSampleLocationsProperties ) ) " "
           "{ type = "_s                            + toString ( properties.structureType ) +
           ", pNext = "                             + :: toString ( properties.pNext ) +
           ", sampleLocationSampleCounts = "        + toString ( properties.sampleLocationSampleCounts ) +
           ", maxSampleLocationGridSize = "         + toString ( properties.maxSampleLocationGridSize ) +
           ", sampleLocationCoordinateRange = [ "   + properties.sampleLocationCoordinateRange[0] + ", " + properties.sampleLocationCoordinateRange[1] + " ]" +
           ", sampleLocationSubPixelBits = "        + properties.sampleLocationSubPixelBits +
           ", variableSampleLocations = "           + ( properties.variableSampleLocations == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceShaderCorePropertiesAMD ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceShaderCorePropertiesAMD ) ) " "
           "{ type = "_s                            + toString ( properties.structureType ) +
           ", pNext = "                             + :: toString ( properties.pNext ) +
           ", shaderEngineCount = "                 + properties.shaderEngineCount +
           ", shaderArraysPerEngineCount = "        + properties.shaderArraysPerEngineCount +
           ", computeUnitsPerShaderArray = "        + properties.computeUnitsPerShaderArray +
           ", simdPerComputeUnit = "                + properties.simdPerComputeUnit +
           ", wavefrontsPerSimd = "                 + properties.wavefrontsPerSimd +
           ", wavefrontSize = "                     + properties.wavefrontSize +
           ", sgprsPerSimd = "                      + properties.sgprsPerSimd +
           ", minSgprAllocation = "                 + properties.minSgprAllocation +
           ", maxSgprAllocation = "                 + properties.maxSgprAllocation +
           ", sgprAllocationGranularity = "         + properties.sgprAllocationGranularity +
           ", vgprsPerSimd = "                      + properties.vgprsPerSimd +
           ", minVgprAllocation = "                 + properties.minVgprAllocation +
           ", maxVgprAllocation = "                 + properties.maxVgprAllocation +
           ", vgprAllocationGranularity = "         + properties.vgprAllocationGranularity +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_2_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceShaderCoreProperties2AMD ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceShaderCoreProperties2AMD ) ) " "
           "{ type = "_s                            + toString ( properties.structureType ) +
           ", pNext = "                             + :: toString ( properties.pNext ) +
           ", shaderCoreFeatures = "                + "0b" + Long ( properties.shaderCoreFeatures ).toString(2) +
           ", activeComputeUnitCount = "            + properties.activeComputeUnitCount +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceShaderSMBuiltinsPropertiesNVidia ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceShaderSMBuiltinsPropertiesNVidia ) ) " "
           "{ type = "_s                            + toString ( properties.structureType ) +
           ", pNext = "                             + :: toString ( properties.pNext ) +
           ", shaderSMCount = "                     + properties.shaderSMCount +
           ", shaderWarpsPerSM = "                  + properties.shaderWarpsPerSM +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceShadingRateImagePropertiesNVidia ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceShadingRateImagePropertiesNVidia ) ) " "
           "{ type = "_s                            + toString ( properties.structureType ) +
           ", pNext = "                             + :: toString ( properties.pNext ) +
           ", shadingRateTexelSize = "              + toString ( properties.shadingRateTexelSize ) +
           ", shadingRatePaletteSize = "            + properties.shadingRatePaletteSize +
           ", shadingRateMaxCoarseSamples = "       + properties.shadingRateMaxCoarseSamples +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceSubgroupSizeControlProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceSubgroupSizeControlProperties ) ) " "
           "{ type = "_s                            + toString ( properties.structureType ) +
           ", pNext = "                             + :: toString ( properties.pNext ) +
           ", minSubgroupSize = "                   + properties.minSubgroupSize +
           ", maxSubgroupSize = "                   + properties.maxSubgroupSize +
           ", maxComputeWorkgroupSubgroups = "      + properties.maxComputeWorkgroupSubgroups +
           ", requiredSubgroupSizeStages = "        + "0b" + Long ( properties.requiredSubgroupSizeStages ).toString(2) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceSubpassShadingPropertiesHuawei ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceSubpassShadingPropertiesHuawei ) ) " "
           "{ type = "_s                                    + toString ( properties.structureType ) +
           ", pNext = "                                     + :: toString ( properties.pNext ) +
           ", maxSubpassShadingWorkgroupSizeAspectRatio = " + properties.maxSubpassShadingWorkgroupSizeAspectRatio +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceTexelBufferAlignmentProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceTexelBufferAlignmentProperties ) ) " "
           "{ type = "_s                                        + toString ( properties.structureType ) +
           ", pNext = "                                         + :: toString ( properties.pNext ) +
           ", storageTexelBufferOffsetAlignmentBytes = "        + toString ( properties.storageTexelBufferOffsetAlignmentBytes ) +
           ", storageTexelBufferOffsetSingleTexelAlignment = "  + ( properties.storageTexelBufferOffsetSingleTexelAlignment == VK_TRUE ? "true" : "false" ) +
           ", uniformTexelBufferOffsetAlignmentBytes = "        + toString ( properties.uniformTexelBufferOffsetAlignmentBytes ) +
           ", uniformTexelBufferOffsetSingleTexelAlignment = "  + ( properties.uniformTexelBufferOffsetSingleTexelAlignment == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceTransformFeedbackProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceTransformFeedbackProperties ) ) " "
           "{ type = "_s                                        + toString ( properties.structureType ) +
           ", pNext = "                                         + :: toString ( properties.pNext ) +
           ", maxTransformFeedbackStreams = "                   + properties.maxTransformFeedbackStreams +
           ", maxTransformFeedbackBuffers = "                   + properties.maxTransformFeedbackBuffers +
           ", maxTransformFeedbackBufferSize = "                + toString ( properties.maxTransformFeedbackBufferSize ) +
           ", maxTransformFeedbackStreamDataSize = "            + properties.maxTransformFeedbackStreamDataSize +
           ", maxTransformFeedbackBufferDataSize = "            + properties.maxTransformFeedbackBufferDataSize +
           ", maxTransformFeedbackBufferDataStride = "          + properties.maxTransformFeedbackBufferDataStride +
           ", transformFeedbackQueries = "                      + ( properties.transformFeedbackQueries == VK_TRUE ? "true" : "false" ) +
           ", transformFeedbackStreamsLinesTriangles = "        + ( properties.transformFeedbackStreamsLinesTriangles == VK_TRUE ? "true" : "false" ) +
           ", transformFeedbackRasterizationStreamSelect = "    + ( properties.transformFeedbackRasterizationStreamSelect == VK_TRUE ? "true" : "false" ) +
           ", transformFeedbackDraw = "                         + ( properties.transformFeedbackDraw == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceVertexAttributeDivisorProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceTransformFeedbackProperties ) ) " "
           "{ type = "_s                                        + toString ( properties.structureType ) +
           ", pNext = "                                         + :: toString ( properties.pNext ) +
           ", maxVertexAttribDivisor = "                        + properties.maxVertexAttribDivisor +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceShaderIntegerDotProductProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceShaderIntegerDotProductProperties ) ) " "
           "{ type = "_s                                                                        + toString ( properties.structureType ) +
           ", pNext = "                                                                         + :: toString ( properties.pNext ) +
           ", integerDotProduct8BitUnsignedAccelerated = "                                      + ( properties.integerDotProduct8BitUnsignedAccelerated == VK_TRUE ? "true" : "false" ) +
           ", integerDotProduct8BitSignedAccelerated = "                                        + ( properties.integerDotProduct8BitSignedAccelerated == VK_TRUE ? "true" : "false" ) +
           ", integerDotProduct8BitMixedSignednessAccelerated = "                               + ( properties.integerDotProduct8BitMixedSignednessAccelerated == VK_TRUE ? "true" : "false" ) +
           ", integerDotProduct4x8BitPackedUnsignedAccelerated = "                              + ( properties.integerDotProduct4x8BitPackedUnsignedAccelerated == VK_TRUE ? "true" : "false" ) +
           ", integerDotProduct4x8BitPackedSignedAccelerated = "                                + ( properties.integerDotProduct4x8BitPackedSignedAccelerated == VK_TRUE ? "true" : "false" ) +
           ", integerDotProduct4x8BitPackedMixedSignednessAccelerated = "                       + ( properties.integerDotProduct4x8BitPackedMixedSignednessAccelerated == VK_TRUE ? "true" : "false" ) +
           ", integerDotProduct16BitUnsignedAccelerated = "                                     + ( properties.integerDotProduct16BitUnsignedAccelerated == VK_TRUE ? "true" : "false" ) +
           ", integerDotProduct16BitSignedAccelerated = "                                       + ( properties.integerDotProduct16BitSignedAccelerated == VK_TRUE ? "true" : "false" ) +
           ", integerDotProduct16BitMixedSignednessAccelerated = "                              + ( properties.integerDotProduct16BitMixedSignednessAccelerated == VK_TRUE ? "true" : "false" ) +
           ", integerDotProduct32BitUnsignedAccelerated = "                                     + ( properties.integerDotProduct32BitUnsignedAccelerated == VK_TRUE ? "true" : "false" ) +
           ", integerDotProduct32BitSignedAccelerated = "                                       + ( properties.integerDotProduct32BitSignedAccelerated == VK_TRUE ? "true" : "false" ) +
           ", integerDotProduct32BitMixedSignednessAccelerated = "                              + ( properties.integerDotProduct32BitMixedSignednessAccelerated == VK_TRUE ? "true" : "false" ) +
           ", integerDotProduct64BitUnsignedAccelerated = "                                     + ( properties.integerDotProduct64BitUnsignedAccelerated == VK_TRUE ? "true" : "false" ) +
           ", integerDotProduct64BitSignedAccelerated = "                                       + ( properties.integerDotProduct64BitSignedAccelerated == VK_TRUE ? "true" : "false" ) +
           ", integerDotProduct64BitMixedSignednessAccelerated = "                              + ( properties.integerDotProduct64BitMixedSignednessAccelerated == VK_TRUE ? "true" : "false" ) +
           ", integerDotProductAccumulatingSaturating8BitUnsignedAccelerated = "                + ( properties.integerDotProductAccumulatingSaturating8BitUnsignedAccelerated == VK_TRUE ? "true" : "false" ) +
           ", integerDotProductAccumulatingSaturating8BitSignedAccelerated = "                  + ( properties.integerDotProductAccumulatingSaturating8BitSignedAccelerated == VK_TRUE ? "true" : "false" ) +
           ", integerDotProductAccumulatingSaturating8BitMixedSignednessAccelerated = "         + ( properties.integerDotProductAccumulatingSaturating8BitMixedSignednessAccelerated == VK_TRUE ? "true" : "false" ) +
           ", integerDotProductAccumulatingSaturating4x8BitPackedUnsignedAccelerated = "        + ( properties.integerDotProductAccumulatingSaturating4x8BitPackedUnsignedAccelerated == VK_TRUE ? "true" : "false" ) +
           ", integerDotProductAccumulatingSaturating4x8BitPackedSignedAccelerated = "          + ( properties.integerDotProductAccumulatingSaturating4x8BitPackedSignedAccelerated == VK_TRUE ? "true" : "false" ) +
           ", integerDotProductAccumulatingSaturating4x8BitPackedMixedSignednessAccelerated = " + ( properties.integerDotProductAccumulatingSaturating4x8BitPackedMixedSignednessAccelerated == VK_TRUE ? "true" : "false" ) +
           ", integerDotProductAccumulatingSaturating16BitUnsignedAccelerated = "               + ( properties.integerDotProductAccumulatingSaturating16BitUnsignedAccelerated == VK_TRUE ? "true" : "false" ) +
           ", integerDotProductAccumulatingSaturating16BitSignedAccelerated = "                 + ( properties.integerDotProductAccumulatingSaturating16BitSignedAccelerated == VK_TRUE ? "true" : "false" ) +
           ", integerDotProductAccumulatingSaturating16BitMixedSignednessAccelerated = "        + ( properties.integerDotProductAccumulatingSaturating16BitMixedSignednessAccelerated == VK_TRUE ? "true" : "false" ) +
           ", integerDotProductAccumulatingSaturating32BitUnsignedAccelerated = "               + ( properties.integerDotProductAccumulatingSaturating32BitUnsignedAccelerated == VK_TRUE ? "true" : "false" ) +
           ", integerDotProductAccumulatingSaturating32BitSignedAccelerated = "                 + ( properties.integerDotProductAccumulatingSaturating32BitSignedAccelerated == VK_TRUE ? "true" : "false" ) +
           ", integerDotProductAccumulatingSaturating32BitMixedSignednessAccelerated = "        + ( properties.integerDotProductAccumulatingSaturating32BitMixedSignednessAccelerated == VK_TRUE ? "true" : "false" ) +
           ", integerDotProductAccumulatingSaturating64BitUnsignedAccelerated = "               + ( properties.integerDotProductAccumulatingSaturating64BitUnsignedAccelerated == VK_TRUE ? "true" : "false" ) +
           ", integerDotProductAccumulatingSaturating64BitSignedAccelerated = "                 + ( properties.integerDotProductAccumulatingSaturating64BitSignedAccelerated == VK_TRUE ? "true" : "false" ) +
           ", integerDotProductAccumulatingSaturating64BitMixedSignednessAccelerated = "        + ( properties.integerDotProductAccumulatingSaturating64BitMixedSignednessAccelerated == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceDetails ) const & details
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceDetails ) ) " "
            "{ basicProperties = "                                  + toString ( details.basicProperties ) +

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

            ", vulkan11Properties = "                               + toString ( details.vulkan11Properties ) +
            ", IDProperties = "                                     + toString ( details.IDProperties ) +
            ", maintenanceProperties = "                            + toString ( details.maintenanceProperties ) +
            ", multiviewProperties = "                              + toString ( details.multiviewProperties ) +
            ", pointClippingProperties = "                          + toString ( details.pointClippingProperties ) +
            ", protectedMemoryProperties = "                        + toString ( details.protectedMemoryProperties ) +
            ", subgroupProperties = "                               + toString ( details.subgroupProperties ) +

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

            ", vulkan12Properties = "                               + toString ( details.vulkan12Properties ) +
            ", driverProperties = "                                 + toString ( details.driverProperties ) +
            ", depthStencilResolveProperties = "                    + toString ( details.depthStencilResolveProperties ) +
            ", descriptorIndexingProperties = "                     + toString ( details.descriptorIndexingProperties ) +
            ", deviceFloatControlsProperties = "                    + toString ( details.deviceFloatControlsProperties ) +
            ", samplerFilterMinmaxProperties = "                    + toString ( details.samplerFilterMinmaxProperties ) +
            ", timelineSemaphoreProperties = "                      + toString ( details.timelineSemaphoreProperties ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PCI_BUS_INFO_AVAILABLE

            ", pciBusInfoProperties = "                             + toString ( details.pciBusInfoProperties ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PHYSICAL_DEVICE_DRM_AVAILABLE

            ", DRMProperties = "                                    + toString ( details.DRMProperties ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE

            ", accelerationStructureProperties = "                  + toString ( details.accelerationStructureProperties ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE

            ", blendOperationAdvancedProperties = "                 + toString ( details.blendOperationAdvancedProperties ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONSERVATIVE_RASTERIZATION_AVAILABLE

            ", conservativeRasterizationProperties = "              + toString ( details.conservativeRasterizationProperties ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE

            ", cooperativeMatrixPropertiesNVidia = "                + toString ( details.cooperativeMatrixPropertiesNVidia ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE

            ", customBorderColorProperties = "                      + toString ( details.customBorderColorProperties ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE

            ", deviceGeneratedCommandsProperties = "                + toString ( details.deviceGeneratedCommandsProperties ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISCARD_RECTANGLES_AVAILABLE

            ", discardRectangleProperties = "                       + toString ( details.discardRectangleProperties ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTERNAL_MEMORY_HOST_AVAILABLE

            ", externalMemoryHostProperties = "                     + toString ( details.externalMemoryHostProperties ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE

            ", fragmentDensityMap2Properties = "                    + toString ( details.fragmentDensityMap2Properties ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE

            ", fragmentDensityMapOffsetPropertiesQualcomm = "       + toString ( details.fragmentDensityMapOffsetPropertiesQualcomm ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

            ", fragmentDensityMapProperties = "                     + toString ( details.fragmentDensityMapProperties ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE

            ", fragmentShadingRateEnumsPropertiesNVidia = "         + toString ( details.fragmentShadingRateEnumsPropertiesNVidia ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE

            ", fragmentShadingRateProperties = "                    + toString ( details.fragmentShadingRateProperties ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE

            ", inlineUniformBlockProperties = "                     + toString ( details.inlineUniformBlockProperties ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE

            ", lineRasterizationProperties = "                      + toString ( details.lineRasterizationProperties ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE

            ", maintenance4Properties = "                           + toString ( details.maintenance4Properties ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE

            ", meshShaderPropertiesNVidia = "                       + toString ( details.meshShaderPropertiesNVidia ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE

            ", multiDrawProperties = "                              + toString ( details.multiDrawProperties ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE

            ", multiviewPerViewAttributesPropertiesNVidia = "       + toString ( details.multiviewPerViewAttributesPropertiesNVidia ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

            ", performanceQueryProperties = "                       + toString ( details.performanceQueryProperties ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE

            ", portabilitySubsetProperties = "                      + toString ( details.portabilitySubsetProperties ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE

            ", provokingVertexProperties = "                        + toString ( details.provokingVertexProperties ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PUSH_DESCRIPTOR_AVAILABLE

            ", pushDescriptorProperties = "                         + toString ( details.pushDescriptorProperties ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE

            ", rayTracingPipelineProperties = "                     + toString ( details.rayTracingPipelineProperties ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE

            ", rayTracingPropertiesNVidia = "                       + toString ( details.rayTracingPropertiesNVidia ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE

            ", robustnessProperties = "                             + toString ( details.robustnessProperties ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE

            ", sampleLocationsProperties = "                        + toString ( details.sampleLocationsProperties ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_AVAILABLE

            ", shaderCorePropertiesAMD = "                          + toString ( details.shaderCorePropertiesAMD ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_2_AVAILABLE

            ", shaderCoreProperties2AMD = "                         + toString ( details.shaderCoreProperties2AMD ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE

            ", shaderSmBuiltinsProperties = "                       + toString ( details.shaderSmBuiltinsProperties ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE

            ", shadingRateImagePropertiesNVidia = "                 + toString ( details.shadingRateImagePropertiesNVidia ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE

            ", subgroupSizeControlProperties = "                    + toString ( details.subgroupSizeControlProperties ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE

            ", subpassShadingPropertiesHuawei = "                   + toString ( details.subpassShadingPropertiesHuawei ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE

            ", texelBufferAlignmentProperties = "                   + toString ( details.texelBufferAlignmentProperties ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE

            ", transformFeedbackProperties = "                      + toString ( details.transformFeedbackProperties ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE

            ", vertexAttributeDivisorProperties = "                 + toString ( details.vertexAttributeDivisorProperties ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE

            ", shaderIntegerDotProductProperties = "                + toString ( details.shaderIntegerDotProductProperties ) +

#endif


            " }";
}

#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( QueueFamilyProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( QueueFamilyProperties ) ) " "
            "{ queueFlags = "_s                 + "0b" + Long ( properties.queueFlags ).toString(2) +
            ", queueCount = "                   + properties.queueCount +
            ", timestampValidBits = "           + properties.timestampValidBits +
            ", minImageTransferGranularity = "  + toString ( properties.minImageTransferGranularity ) +
            " }";
}

#endif

auto vulkan :: compare (
        __C_ENG_TYPE ( Version ) const & left,
        __C_ENG_TYPE ( Version ) const & right
) noexcept -> __C_ENG_TYPE ( CompareResult ) {

    __C_ENG_TYPE ( CompareResult ) result;

    result = engine :: compare ( left.variant, right.variant );
    if ( result != __C_ENG_TYPE ( CompareResult ) :: CompareResultEquals ) {
        return result;
    }

    result = engine :: compare ( left.major, right.major );
    if ( result != __C_ENG_TYPE ( CompareResult ) :: CompareResultEquals ) {
        return result;
    }

    result = engine :: compare ( left.minor, right.minor );
    if ( result != __C_ENG_TYPE ( CompareResult ) :: CompareResultEquals ) {
        return result;
    }

    return engine :: compare ( left.patch, right.patch );
}

auto vulkan :: uInt32ToInstanceVersion (
        uint32 rawInstanceVersion
) noexcept -> __C_ENG_TYPE ( Version ) {

    __C_ENG_TYPE ( Version )    instanceVersion {};

    instanceVersion.variant = static_cast < uint8 > ( VK_API_VERSION_VARIANT ( rawInstanceVersion ) ); // NOLINT(clion-misra-cpp2008-5-2-4)
    instanceVersion.major = static_cast < uint8 > ( VK_API_VERSION_MAJOR ( rawInstanceVersion ) ); // NOLINT(clion-misra-cpp2008-5-2-4)
    instanceVersion.minor = static_cast < uint16 > ( VK_API_VERSION_MINOR ( rawInstanceVersion ) ); // NOLINT(clion-misra-cpp2008-5-2-4)
    instanceVersion.patch = static_cast < uint16 > ( VK_API_VERSION_PATCH ( rawInstanceVersion ) ); // NOLINT(clion-misra-cpp2008-5-2-4)

    return instanceVersion;
}

auto vulkan :: instanceVersionToUInt32 (
        __C_ENG_TYPE ( Version ) const & version
) noexcept -> uint32 {
    return VK_MAKE_API_VERSION (  // NOLINT(clion-misra-cpp2008-5-2-4)
            version.variant,
            version.major,
            version.minor,
            version.patch
    );
}

auto vulkan :: versionReadableFormat (
        __C_ENG_TYPE ( Version ) const & version
) noexcept -> cds :: String {
    return String :: f (
            "%d.%d.%d",
            static_cast < sint32 > ( version.major ),
            static_cast < sint32 > ( version.minor ),
            static_cast < sint32 > ( version.patch )
    );
}
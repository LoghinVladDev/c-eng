//
// Created by loghin on 26.12.2021.
//

#include "VulkanCore.hpp"

#include <CDS/String>
#include <Func.hpp>
#include <CDS/Long>

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

#define C_ENG_MAP_START     SOURCE
#include <ObjectMapping.hpp>

template < typename T, typename F >
inline auto flagsToString ( F flags ) noexcept -> String {
    String asString = "0b" + Long ( static_cast < uint64 > ( flags ) ).toString(2) + " = ( ";
    constexpr cds :: uint64 flagMax = 1ULL << 63ULL;

    for ( cds :: uint64 i = 1ULL; true; i <<= 1ULL ) {
        if ( ( i & flags ) != 0ULL ) {
            asString += engine :: vulkan :: toString ( static_cast < T > ( i ) ) + "; "_s;
        }

        if ( i == flagMax ) {
            break;
        }
    }

    return asString.removeSuffix("; ") + " )";
}

template < typename F >
inline auto flagsToString ( F flags ) noexcept -> String {
    return "0b" + Long ( static_cast < uint64 > ( flags ) ).toString(2);
}

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
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

#if __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultPipelineCompileRequired:                     { asString = "Requested Pipeline Creation would have required compilation, but the application requested that compilation not be performed";                                                                                   break; }

#endif

        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorInvalidUsage:                           { asString = "Invalid Usage of Vulkan Function";                                                                                                                                                                               break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorFunctionNotSupportedICD:                { asString = "Vulkan ICD does not support the requested function call";                                                                                                                                                        break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorIncompatibleVersion:                    { asString = "API Version does not support call";                                                                                                                                                                              break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorConfigurationArraySizeSmall:            { asString = "Array Size too Small, check 'VulkanCoreConfig.hpp'";                                                                                                                                                             break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorFunctionHandleNotFound:                 { asString = "Function Requested not Present";                                                                                                                                                                                 break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultErrorIllegalArgument:                        { asString = "Illegal Argument Passed to Binding Call";                                                                                                                                                                        break; }
        case vulkan :: __C_ENG_TYPE ( Result ) :: ResultUnknown:                                     { asString = "Unknown/Not Documented Result";                                                                                                                                                                                  break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
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
        case StructureTypeFrameBufferCreateInfo:                                                    { asString = "StructureTypeFramebufferCreateInfo";                                              break; }
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
        case StructureTypePipelineTessellationDomainOriginStateCreateInfo:                          { asString = "StructureTypePipelineTesselationDomainOriginStateCreateInfo";                     break; }
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
        case StructureTypePhysicalDeviceExternalSemaphoreInfo:                                      { asString = "StructureTypePhysicalDeviceExternalSemaphoreInfo";                                break; }
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
        case StructureTypePhysicalDeviceImagelessFrameBufferFeatures:                               { asString = "StructureTypePhysicalDeviceImagelessFramebufferFeatures";                         break; }
        case StructureTypeFrameBufferAttachmentsCreateInfo:                                         { asString = "StructureTypeFramebufferAttachmentsCreateInfo";                                   break; }
        case StructureTypeFrameBufferAttachmentImageInfo:                                           { asString = "StructureTypeFramebufferAttachmentImageInfo";                                     break; }
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

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        case StructureTypePhysicalDeviceVulkan_1_3_Features:                                        { asString = "StructureTypePhysicalDeviceVulkan_1_3_Features";                                  break; }
        case StructureTypePhysicalDeviceVulkan_1_3_Properties:                                      { asString = "StructureTypePhysicalDeviceVulkan_1_3_Properties";                                break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE

        case StructureTypeSwapChainCreateInfo:                                                      { asString = "StructureTypeSwapChainCreateInfo";                                                break; }
        case StructureTypePresentInfo:                                                              { asString = "StructureTypePresentInfo";                                                        break; }

#endif

#if ( __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE ) || ( __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DEVICE_GROUP_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE )

        case StructureTypeDeviceGroupPresentCapabilities:                                           { asString = "StructureTypeDeviceGroupPresentCapabilities";                                     break; }
        case StructureTypeImageSwapChainCreateInfo:                                                 { asString = "StructureTypeImageSwapChainCreateInfo";                                           break; }
        case StructureTypeBindImageMemorySwapChainInfo:                                             { asString = "StructureTypeBindImageMemorySwapChainInfo";                                       break; }
        case StructureTypeAcquireNextImageInfo:                                                     { asString = "StructureTypeAcquireNextImageInfo";                                               break; }
        case StructureTypeDeviceGroupPresentInfo:                                                   { asString = "StructureTypeDeviceGroupPresentInfo";                                             break; }
        case StructureTypeDeviceGroupSwapChainCreateInfo:                                           { asString = "StructureTypeDeviceGroupSwapChainCreateInfo";                                     break; }

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
        case StructureTypeVideoEncodeH265NALUSliceSegment:                                       { asString = "StructureTypeVideoEncodeH265NALUSlice";                                              break; }
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

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

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

        case StructureTypeMultiviewPerViewAttributesInfoNVidiaExperimental:                      { asString = "StructureTypeMutiviewPerViewAttributesInfoNVidiaExperimental";                       break; }
        case StructureTypePhysicalDeviceMultiviewPerViewAttributesPropertiesNVidiaExperimental:  { asString = "StructureTypePhysicalDeviceMultiviewPerViewAttributesPropertiesNVidiaExperimental";  break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_GAMES_PLATFORM_STREAM_DESCRIPTOR_SURFACE_AVAILABLE

        case StructureTypeStreamDescriptorSurfaceCreateInfoGoogle:                               { asString = "StructureTypeStreamDescriptorSurfaceCreateInfoGoogle";                               break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CORNER_SAMPLED_IMAGE_AVAILABLE

        case StructureTypePhysicalDeviceCornerSampledImageFeaturesNVidia:                        { asString = "StructureTypePhysicalDeviceCornerSampledImageFeatures";                              break; }

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

#if __C_ENG_VULKAN_API_EXTENSION_TEXTURE_COMPRESSION_ASTC_HDR_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

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

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

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
        case StructureTypeVideoDecodeH265Profile:                                                { asString = "StructureTypeVideoDecodeH265Profile";                                                break; }
        case StructureTypeVideoDecodeH265PictureInfo:                                            { asString = "StructureTypeVideoDecodeH265PictureInfo";                                            break; }
        case StructureTypeVideoDecodeH265DPBSlotInfo:                                            { asString = "StructureTypeVideoDecodeH265DPBSlotInfo";                                            break; }

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

#if __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_FEEDBACK_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

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

        case StructureTypePhysicalDeviceShaderIntegerFunctionsFeaturesIntel:                     { asString = "StructureTypePhysicalDeviceShaderIntegerFunctionsFeaturesIntel";                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE

        case StructureTypeQueryPoolPerformanceCreateInfoIntel:                                   { asString = "StructureTypeQueryPoolPerformanceQueryCreateInfoIntel";                              break; }
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

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_TERMINATE_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

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

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

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
        case StructureTypeBufferDeviceAddressCreateInfo:                                         { asString = "StructureTypeBufferDeviceAddressCreateInfo";                                         break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TOOLING_INFO_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        case StructureTypePhysicalDeviceToolProperties:                                          { asString = "StructureTypePhysicalDeviceToolProperties";                                          break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_FEATURES_AVAILABLE

        case StructureTypeValidationFeatures:                                                    { asString = "StructureTypeValidationFeatures";                                                    break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_ID_AVAILABLE

        case StructureTypePhysicalDevicePresentIDFeatures:                                       { asString = "StructureTypePhysicalDevicePresentIDFeatures";                                       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_IMAGE_ATOMIC_INT64_AVAILABLE

        case StructureTypePhysicalDeviceShaderImageAtomicInt64Features:                          { asString = "StructureTypePhysicalDeviceShaderImageAtomicInt64Features";                          break; }

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
        case StructureTypeFrameBufferMixedSamplesCombinationNVidia:                              { asString = "StructureTypeFramebufferMixedSamplesCombinationNVidia";                              break; }

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

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_DEMOTE_TO_HELPER_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

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

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        case StructureTypePhysicalDeviceShaderIntegerDotProductFeatures:                         { asString = "StructureTypePhysicalDeviceShaderIntegerDotProductFeatures";                         break; }
        case StructureTypePhysicalDeviceShaderIntegerDotProductProperties:                       { asString = "StructureTypePhysicalDeviceShaderIntegerDotProductProperties";                       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

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

#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        case StructureTypePhysicalDevicePrivateDataFeatures:                                     { asString = "StructureTypePhysicalDevicePrivateDataFeatures";                                     break; }
        case StructureTypeDevicePrivateDataCreateInfo:                                           { asString = "StructureTypeDevicePrivateDataCreateInfo";                                           break; }
        case StructureTypePrivateDataSlotCreateInfo:                                             { asString = "StructureTypePrivateDataSlotCreateInfo";                                             break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

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

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        case StructureTypeMemoryBarrier2:                                                        { asString = "StructureTypeMemoryBarrier2";                                                        break; }
        case StructureTypeBufferMemoryBarrier2:                                                  { asString = "StructureTypeBufferMemoryBarrier2";                                                  break; }
        case StructureTypeImageMemoryBarrier2:                                                   { asString = "StructureTypeImageMemoryBarrier2";                                                   break; }
        case StructureTypeDependencyInfo:                                                        { asString = "StructureTypeDependencyInfo";                                                       break; }
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

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ZERO_INITIALIZE_WORKGROUP_MEMORY_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

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

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_ROBUSTNESS_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        case StructureTypePhysicalDeviceImageRobustnessFeatures:                                 { asString = "StructureTypePhysicalDeviceImageRobustnessFeatures";                                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_AVAILABLE

        case StructureTypePhysicalDeviceWorkgroupMemoryExplicitLayoutFeatures:                   { asString = "StructureTypePhysicalDeviceWorkgroupMemoryExplicitLayoutFeatures";                   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

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

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FORMAT_FEATURE_FLAGS_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

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

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

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
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_UTILS_AVAILABLE
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
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_FEATURES_AVAILABLE
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
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
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
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
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
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
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
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
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
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
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
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PipelineStageFlag ) stage
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( stage ) {
        case __C_ENG_TYPE ( PipelineStageFlag ) :: PipelineStageFlagTopOfPipe:                      { asString = "Top of Pipe";                         break; }
        case __C_ENG_TYPE ( PipelineStageFlag ) :: PipelineStageFlagDrawIndirect:                   { asString = "Draw Indirect";                       break; }
        case __C_ENG_TYPE ( PipelineStageFlag ) :: PipelineStageFlagVertexInput:                    { asString = "Vertex Input";                        break; }
        case __C_ENG_TYPE ( PipelineStageFlag ) :: PipelineStageFlagVertexShader:                   { asString = "Vertex Shader";                       break; }
        case __C_ENG_TYPE ( PipelineStageFlag ) :: PipelineStageFlagTessellationControlShader:      { asString = "Tessellation Control Shader";         break; }
        case __C_ENG_TYPE ( PipelineStageFlag ) :: PipelineStageFlagTessellationEvaluationShader:   { asString = "Tessellation Evaluation Shader";      break; }
        case __C_ENG_TYPE ( PipelineStageFlag ) :: PipelineStageFlagGeometryShader:                 { asString = "Geometry Shader";                     break; }
        case __C_ENG_TYPE ( PipelineStageFlag ) :: PipelineStageFlagFragmentShader:                 { asString = "Fragment Shader";                     break; }
        case __C_ENG_TYPE ( PipelineStageFlag ) :: PipelineStageFlagEarlyFragmentTests:             { asString = "Early Fragment Tests";                break; }
        case __C_ENG_TYPE ( PipelineStageFlag ) :: PipelineStageFlagLateFragmentTests:              { asString = "Late Fragment Tests";                 break; }
        case __C_ENG_TYPE ( PipelineStageFlag ) :: PipelineStageFlagColorAttachmentOutput:          { asString = "Color Attachment Output";             break; }
        case __C_ENG_TYPE ( PipelineStageFlag ) :: PipelineStageFlagComputeShader:                  { asString = "Compute Shader";                      break; }
        case __C_ENG_TYPE ( PipelineStageFlag ) :: PipelineStageFlagTransfer:                       { asString = "Transfer";                            break; }
        case __C_ENG_TYPE ( PipelineStageFlag ) :: PipelineStageFlagBottomOfPipe:                   { asString = "Bottom Of Pipe";                      break; }
        case __C_ENG_TYPE ( PipelineStageFlag ) :: PipelineStageFlagHost:                           { asString = "Host";                                break; }
        case __C_ENG_TYPE ( PipelineStageFlag ) :: PipelineStageFlagAllGraphics:                    { asString = "All Graphics";                        break; }
        case __C_ENG_TYPE ( PipelineStageFlag ) :: PipelineStageFlagAllCommands:                    { asString = "All Commands";                        break; }

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE

        case __C_ENG_TYPE ( PipelineStageFlag ) :: PipelineStageFlagTransformFeedback:              { asString = "Transform Feedback";                  break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE

        case __C_ENG_TYPE ( PipelineStageFlag ) :: PipelineStageFlagConditionalRendering:           { asString = "Conditional Rendering";               break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE

        case __C_ENG_TYPE ( PipelineStageFlag ) :: PipelineStageFlagAccelerationStructureBuild:     { asString = "Acceleration Structure Build";        break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE

        case __C_ENG_TYPE ( PipelineStageFlag ) :: PipelineStageFlagRayTracingShader:               { asString = "Ray Tracing Shader";                  break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE

        case __C_ENG_TYPE ( PipelineStageFlag ) :: PipelineStageFlagTaskShaderNVidia:               { asString = "Task Shader NVidia";                  break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE

        case __C_ENG_TYPE ( PipelineStageFlag ) :: PipelineStageFlagMeshShaderNVidia:               { asString = "Mesh Shader NVidia";                  break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

        case __C_ENG_TYPE ( PipelineStageFlag ) :: PipelineStageFlagFragmentDensityProcess:         { asString = "Fragment Density Process";            break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE

        case __C_ENG_TYPE ( PipelineStageFlag ) :: PipelineStageFlagFragmentShadingRateAttachment:  { asString = "Fragment Shading Rate Attachment";    break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE

        case __C_ENG_TYPE ( PipelineStageFlag ) :: PipelineStageFlagCommandPreprocessNVidia:        { asString = "Command Preprocess NVidia";           break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE

        case __C_ENG_TYPE ( PipelineStageFlag ) :: PipelineStageFlagNone:                           { asString = "None";                                break; }

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE

        case PipelineStageFlagCopy:                                                                 { asString = "Copy";                                break; }
        case PipelineStageFlagResolve:                                                              { asString = "Resolve";                             break; }
        case PipelineStageFlagBlit:                                                                 { asString = "Blit";                                break; }
        case PipelineStageFlagClear:                                                                { asString = "Clear";                               break; }
        case PipelineStageFlagIndexInput:                                                           { asString = "Index Input";                         break; }
        case PipelineStageFlagVertexAttributeInput:                                                 { asString = "Vertex Attribute Input";              break; }
        case PipelineStageFlagPreRasterizationShaders:                                              { asString = "Pre Rasterization Shaders";           break; }

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE

        case PipelineStageFlagSubpassShadingHuawei:                                                 { asString = "Subpass Shading Huawei";              break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_INVOCATION_MASK_AVAILABLE

        case PipelineStageFlagInvocationMaskHuawei:                                                 { asString = "Invocation Mask Huawei";              break; }

#endif

#endif

    }

    return asString;
}

#endif

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
        case __C_ENG_TYPE ( QueueFlag ) :: QueueFlagPresent:        { asString = "Present";         break; }

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

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( QueueGlobalPriority ) priority
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( priority ) {
        case __C_ENG_TYPE ( QueueGlobalPriority ) :: QueueGlobalPriorityLow:        { asString = "Low";         break; }
        case __C_ENG_TYPE ( QueueGlobalPriority ) :: QueueGlobalPriorityMedium:     { asString = "Medium";      break; }
        case __C_ENG_TYPE ( QueueGlobalPriority ) :: QueueGlobalPriorityHigh:       { asString = "High";        break; }
        case __C_ENG_TYPE ( QueueGlobalPriority ) :: QueueGlobalPriorityRealtime:   { asString = "Realtime";    break; }
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

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PerformanceCounterUnit ) unit
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( unit ) {
        case __C_ENG_TYPE ( PerformanceCounterUnit ) :: PerformanceCounterUnitGeneric:          { asString = "Generic";             break; }
        case __C_ENG_TYPE ( PerformanceCounterUnit ) :: PerformanceCounterUnitPercentage:       { asString = "Percentage";          break; }
        case __C_ENG_TYPE ( PerformanceCounterUnit ) :: PerformanceCounterUnitNanoseconds:      { asString = "Nanoseconds";         break; }
        case __C_ENG_TYPE ( PerformanceCounterUnit ) :: PerformanceCounterUnitBytes:            { asString = "Bytes";               break; }
        case __C_ENG_TYPE ( PerformanceCounterUnit ) :: PerformanceCounterUnitBytesPerSecond:   { asString = "Bytes per Second";    break; }
        case __C_ENG_TYPE ( PerformanceCounterUnit ) :: PerformanceCounterUnitKelvin:           { asString = "Kelvin";              break; }
        case __C_ENG_TYPE ( PerformanceCounterUnit ) :: PerformanceCounterUnitWatts:            { asString = "Watts";               break; }
        case __C_ENG_TYPE ( PerformanceCounterUnit ) :: PerformanceCounterUnitVolts:            { asString = "Volts";               break; }
        case __C_ENG_TYPE ( PerformanceCounterUnit ) :: PerformanceCounterUnitAmps:             { asString = "Amps";                break; }
        case __C_ENG_TYPE ( PerformanceCounterUnit ) :: PerformanceCounterUnitHertz:            { asString = "Hertz";               break; }
        case __C_ENG_TYPE ( PerformanceCounterUnit ) :: PerformanceCounterUnitCycles:           { asString = "Cycles";              break; }
    }

    return asString;
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PerformanceCounterScope ) scope
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( scope ) {
        case __C_ENG_TYPE ( PerformanceCounterScope ) :: PerformanceCounterScopeCommandBuffer:  { asString = "Command Buffer";  break; }
        case __C_ENG_TYPE ( PerformanceCounterScope ) :: PerformanceCounterScopeRenderPass:     { asString = "Render Pass";     break; }
        case __C_ENG_TYPE ( PerformanceCounterScope ) :: PerformanceCounterScopeCommand:        { asString = "Command";         break; }
    }

    return asString;
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PerformanceCounterStorage ) storage
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( storage ) {
        case __C_ENG_TYPE ( PerformanceCounterStorage ) :: PerformanceCounterStorageInt32:      { asString = "SInt32";  break; }
        case __C_ENG_TYPE ( PerformanceCounterStorage ) :: PerformanceCounterStorageInt64:      { asString = "SInt64";  break; }
        case __C_ENG_TYPE ( PerformanceCounterStorage ) :: PerformanceCounterStorageUInt32:     { asString = "UInt32";  break; }
        case __C_ENG_TYPE ( PerformanceCounterStorage ) :: PerformanceCounterStorageUInt64:     { asString = "UInt64";  break; }
        case __C_ENG_TYPE ( PerformanceCounterStorage ) :: PerformanceCounterStorageFloat32:    { asString = "Float32"; break; }
        case __C_ENG_TYPE ( PerformanceCounterStorage ) :: PerformanceCounterStorageFloat64:    { asString = "Float64"; break; }
    }

    return asString;
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PerformanceCounterDescriptionFlag ) flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case __C_ENG_TYPE ( PerformanceCounterDescriptionFlag ) :: PerformanceCounterDescriptionFlagPerformanceImpacting:      { asString = "Performance Impacting";  break; }
        case __C_ENG_TYPE ( PerformanceCounterDescriptionFlag ) :: PerformanceCounterDescriptionFlagConcurrentlyImpacted:      { asString = "Concurrently Impacted";  break; }
    }

    return asString;
}

#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( DeviceQueueCreateFlag ) flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case __C_ENG_TYPE ( DeviceQueueCreateFlag ) :: DeviceQueueCreateFlagProtected:  { asString = "Protected";   break; }
    }

    return asString;
}

#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
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
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
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
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        __C_ENG_TYPE ( DeviceSize ) deviceSize
) noexcept -> String {

    return ""_s + static_cast < uint64 > ( deviceSize );
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
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
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
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
            ", flags = "                + :: flagsToString ( createInfo.flags ) +
            ", applicationInfo = "      + :: toString ( createInfo.pApplicationInfo ) +
            ", enabledLayers = "        + stringArrayToString ( createInfo.pEnabledLayerNames, createInfo.enabledLayerCount ) +
            ", enabledExtensions = "    + stringArrayToString ( createInfo.pEnabledExtensionNames, createInfo.enabledExtensionCount ) +
            " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_UTILS_AVAILABLE
auto vulkan :: toString (
        __C_ENG_TYPE ( DebugMessengerCreateInfo ) const & createInfo
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( DebugMessengerCreateInfo ) ) " "
            "{ type = "_s               + toString ( createInfo.structureType ) +
            ", next = "                 + :: toString ( createInfo.pNext ) +
            ", flags = "                + :: flagsToString ( createInfo.flags ) +
            ", messageSeverityFlags = " + :: flagsToString < Type ( DebugMessageSeverityFlag ) > ( createInfo.messageSeverityFlags ) +
            ", messageTypeFlags = "     + :: flagsToString < Type ( DebugMessageTypeFlag ) > ( createInfo.messageTypeFlags ) +
            ", callback = "             + :: toString ( createInfo.callback ) +
            ", userData = "             + :: toString ( createInfo.pCallbackUserData ) +
            " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_FEATURES_AVAILABLE
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
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
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
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        __C_ENG_TYPE ( ExtensionProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( ExtensionProperties ) ) " "
            "{ layerName = "_s      + properties.name +
            ", specVersion = "      + properties.specVersion +
            " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
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
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
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
            ", framebufferColorSampleCounts = "                     + :: flagsToString < Type ( SampleCountFlag ) > ( deviceLimits.framebufferColorSampleCounts ) +
            ", framebufferDepthSampleCounts = "                     + :: flagsToString < Type ( SampleCountFlag ) > ( deviceLimits.framebufferDepthSampleCounts ) +
            ", framebufferStencilSampleCounts = "                   + :: flagsToString < Type ( SampleCountFlag ) > ( deviceLimits.framebufferStencilSampleCounts ) +
            ", framebufferNoAttachmentsSampleCounts = "             + :: flagsToString < Type ( SampleCountFlag ) > ( deviceLimits.framebufferNoAttachmentsSampleCounts ) +
            ", maxColorAttachments = "                              + deviceLimits.maxColorAttachments +
            ", sampledImageColorSampleCounts = "                    + :: flagsToString < Type ( SampleCountFlag ) > ( deviceLimits.sampledImageColorSampleCounts ) +
            ", sampledImageIntegerSampleCounts = "                  + :: flagsToString < Type ( SampleCountFlag ) > ( deviceLimits.sampledImageIntegerSampleCounts ) +
            ", sampledImageDepthSampleCounts = "                    + :: flagsToString < Type ( SampleCountFlag ) > ( deviceLimits.sampledImageDepthSampleCounts ) +
            ", sampledImageStencilSampleCounts = "                  + :: flagsToString < Type ( SampleCountFlag ) > ( deviceLimits.sampledImageStencilSampleCounts ) +
            ", storageImageSampleCounts = "                         + :: flagsToString < Type ( SampleCountFlag ) > ( deviceLimits.storageImageSampleCounts ) +
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
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
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
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
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
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
static auto deduceAndMoveToNextInPropertiesChain (
        vulkan :: __C_ENG_TYPE ( GenericOutStructure ) * pInStructure
) noexcept -> String {
    if ( pInStructure == nullptr ) {
        return "null";
    }

    return "";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
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
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceExtendedFeatures ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceExtendedFeatures ) ) " "
            "{ type = "_s          + toString ( properties.structureType ) +
            ", pNext = "           + engine :: toString ( properties.pNext ) +
            ", baseFeatures = "    + toString ( properties.features ) +
            " }";
}
#endif

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
            ", subgroupSupportedStages = "              + :: flagsToString < Type ( ShaderStageFlag ) > ( properties.subgroupSupportedStages ) +
            ", subgroupSupportedOperations = "          + :: flagsToString < Type ( SubgroupFeatureFlag ) > ( properties.subgroupSupportedOperations ) +
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
            ", supportedStages = "                      + :: flagsToString < Type ( ShaderStageFlag ) > ( properties.supportedStages ) +
            ", supportedOperations = "                  + :: flagsToString < Type ( SubgroupFeatureFlag ) > ( properties.supportedOperations ) +
            ", quadOperationsInAllStages = "            + ( properties.quadOperationsInAllStages == VK_TRUE ? "true" : "false" ) +
            " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceGroupProperties ) const & properties
) noexcept -> String {

    String devicesAsString = "[ ";
    for ( uint32 i = 0U; i < properties.physicalDeviceCount; ++ i ) {
        devicesAsString += :: toString ( properties.physicalDevices[i] ) + ", ";
    }

    (void) devicesAsString.removeSuffix(", ").append(" ]");

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceSubgroupProperties ) ) " "
            "{ type = "_s                               + toString ( properties.structureType ) +
            ", pNext = "                                + :: toString ( properties.pNext ) +
            ", physicalDeviceCount = "                  + properties.physicalDeviceCount +
            ", physicalDevices = "                      + devicesAsString +
            ", subsetAllocation = "                     + ( properties.subsetAllocation == VK_TRUE ? "true" : "false" ) +
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
            ", supportedDepthResolveModes = "   + :: flagsToString < Type ( ResolveModeFlag ) > ( properties.supportedDepthResolveModes ) +
            ", supportedStencilResolveModes = " + :: flagsToString < Type ( ResolveModeFlag ) > ( properties.supportedStencilResolveModes ) +
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
            ", denormBehaviorIndependence = "               + toString ( properties.denormBehaviorIndependence ) +
            ", roundingModeIndependence = "                 + toString ( properties.roundingModeIndependence ) +
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
           ", cooperativeMatrixSupportedStages = "              + :: flagsToString < Type ( ShaderStageFlag ) > ( properties.cooperativeMatrixSupportedStages ) +
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

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

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

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

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

auto vulkan :: toString (
        __C_ENG_TYPE ( PerformanceCounter ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PerformanceCounter ) ) " "
           "{ type = "_s                            + toString ( properties.structureType ) +
           ", pNext = "                             + :: toString ( properties.pNext ) +
           ", unit = "                              + toString ( properties.unit ) +
           ", scope = "                             + toString ( properties.scope ) +
           ", storage = "                           + toString ( properties.storage ) +
           ", uuid = "                              + :: toString ( & properties.uuid[0] ) +
           " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PerformanceCounterDescription ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PerformanceCounterDescription ) ) " "
           "{ type = "_s                            + toString ( properties.structureType ) +
           ", pNext = "                             + :: toString ( properties.pNext ) +
           ", flags = "                             + :: flagsToString < Type ( PerformanceCounterDescriptionFlag ) > ( properties.flags ) +
           ", name = "                              + properties.name +
           ", category = "                          + properties.category +
           ", description = "                       + properties.description +
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
           ", shaderCoreFeatures = "                + :: flagsToString ( properties.shaderCoreFeatures ) +
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

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceSubgroupSizeControlProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceSubgroupSizeControlProperties ) ) " "
           "{ type = "_s                            + toString ( properties.structureType ) +
           ", pNext = "                             + :: toString ( properties.pNext ) +
           ", minSubgroupSize = "                   + properties.minSubgroupSize +
           ", maxSubgroupSize = "                   + properties.maxSubgroupSize +
           ", maxComputeWorkgroupSubgroups = "      + properties.maxComputeWorkgroupSubgroups +
           ", requiredSubgroupSizeStages = "        + :: flagsToString < Type ( ShaderStageFlag ) > ( properties.requiredSubgroupSizeStages ) +
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

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

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

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

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
        __C_ENG_TYPE ( PhysicalDeviceFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceFeatures ) ) " "
            "{ robustBufferAccess = "_s                                 + ( features.robustBufferAccess == VK_TRUE ? "true" : "false" ) +
            ", fullDrawIndexUint32 = "                                  + ( features.fullDrawIndexUint32 == VK_TRUE ? "true" : "false" ) +
            ", imageCubeArray = "                                       + ( features.imageCubeArray == VK_TRUE ? "true" : "false" ) +
            ", independentBlend = "                                     + ( features.independentBlend == VK_TRUE ? "true" : "false" ) +
            ", geometryShader = "                                       + ( features.geometryShader == VK_TRUE ? "true" : "false" ) +
            ", tessellationShader = "                                   + ( features.tessellationShader == VK_TRUE ? "true" : "false" ) +
            ", sampleRateShading = "                                    + ( features.sampleRateShading == VK_TRUE ? "true" : "false" ) +
            ", dualSrcBlend = "                                         + ( features.dualSrcBlend == VK_TRUE ? "true" : "false" ) +
            ", logicOp = "                                              + ( features.logicOp == VK_TRUE ? "true" : "false" ) +
            ", multiDrawIndirect = "                                    + ( features.multiDrawIndirect == VK_TRUE ? "true" : "false" ) +
            ", drawIndirectFirstInstance = "                            + ( features.drawIndirectFirstInstance == VK_TRUE ? "true" : "false" ) +
            ", depthClamp = "                                           + ( features.depthClamp == VK_TRUE ? "true" : "false" ) +
            ", depthBiasClamp = "                                       + ( features.depthBiasClamp == VK_TRUE ? "true" : "false" ) +
            ", fillModeNonSolid = "                                     + ( features.fillModeNonSolid == VK_TRUE ? "true" : "false" ) +
            ", depthBounds = "                                          + ( features.depthBounds == VK_TRUE ? "true" : "false" ) +
            ", wideLines = "                                            + ( features.wideLines == VK_TRUE ? "true" : "false" ) +
            ", largePoints = "                                          + ( features.largePoints == VK_TRUE ? "true" : "false" ) +
            ", alphaToOne = "                                           + ( features.alphaToOne == VK_TRUE ? "true" : "false" ) +
            ", multiViewport = "                                        + ( features.multiViewport == VK_TRUE ? "true" : "false" ) +
            ", samplerAnisotropy = "                                    + ( features.samplerAnisotropy == VK_TRUE ? "true" : "false" ) +
            ", textureCompressionETC2 = "                               + ( features.textureCompressionETC2 == VK_TRUE ? "true" : "false" ) +
            ", textureCompressionASTC_LDR = "                           + ( features.textureCompressionASTC_LDR == VK_TRUE ? "true" : "false" ) +
            ", textureCompressionBC = "                                 + ( features.textureCompressionBC == VK_TRUE ? "true" : "false" ) +
            ", occlusionQueryPrecise = "                                + ( features.occlusionQueryPrecise == VK_TRUE ? "true" : "false" ) +
            ", pipelineStatisticsQuery = "                              + ( features.pipelineStatisticsQuery == VK_TRUE ? "true" : "false" ) +
            ", vertexPipelineStoresAndAtomics = "                       + ( features.vertexPipelineStoresAndAtomics == VK_TRUE ? "true" : "false" ) +
            ", fragmentStoresAndAtomics = "                             + ( features.fragmentStoresAndAtomics == VK_TRUE ? "true" : "false" ) +
            ", shaderTessellationAndGeometryPointSize = "               + ( features.shaderTessellationAndGeometryPointSize == VK_TRUE ? "true" : "false" ) +
            ", shaderImageGatherExtended = "                            + ( features.shaderImageGatherExtended == VK_TRUE ? "true" : "false" ) +
            ", shaderStorageImageExtendedFormats = "                    + ( features.shaderStorageImageExtendedFormats == VK_TRUE ? "true" : "false" ) +
            ", shaderStorageImageMultisample = "                        + ( features.shaderStorageImageMultisample == VK_TRUE ? "true" : "false" ) +
            ", shaderStorageImageReadWithoutFormat = "                  + ( features.shaderStorageImageReadWithoutFormat == VK_TRUE ? "true" : "false" ) +
            ", shaderStorageImageWriteWithoutFormat = "                 + ( features.shaderStorageImageWriteWithoutFormat == VK_TRUE ? "true" : "false" ) +
            ", shaderUniformBufferArrayDynamicIndexing = "              + ( features.shaderUniformBufferArrayDynamicIndexing == VK_TRUE ? "true" : "false" ) +
            ", shaderSampledImageArrayDynamicIndexing = "               + ( features.shaderSampledImageArrayDynamicIndexing == VK_TRUE ? "true" : "false" ) +
            ", shaderStorageBufferArrayDynamicIndexing = "              + ( features.shaderStorageBufferArrayDynamicIndexing == VK_TRUE ? "true" : "false" ) +
            ", shaderStorageImageArrayDynamicIndexing = "               + ( features.shaderStorageImageArrayDynamicIndexing == VK_TRUE ? "true" : "false" ) +
            ", shaderClipDistance = "                                   + ( features.shaderClipDistance == VK_TRUE ? "true" : "false" ) +
            ", shaderCullDistance = "                                   + ( features.shaderCullDistance == VK_TRUE ? "true" : "false" ) +
            ", shaderFloat64 = "                                        + ( features.shaderFloat64 == VK_TRUE ? "true" : "false" ) +
            ", shaderInt64 = "                                          + ( features.shaderInt64 == VK_TRUE ? "true" : "false" ) +
            ", shaderInt16 = "                                          + ( features.shaderInt16 == VK_TRUE ? "true" : "false" ) +
            ", shaderResourceResidency = "                              + ( features.shaderResourceResidency == VK_TRUE ? "true" : "false" ) +
            ", shaderResourceMinLod = "                                 + ( features.shaderResourceMinLod == VK_TRUE ? "true" : "false" ) +
            ", sparseBinding = "                                        + ( features.sparseBinding == VK_TRUE ? "true" : "false" ) +
            ", sparseResidencyBuffer = "                                + ( features.sparseResidencyBuffer == VK_TRUE ? "true" : "false" ) +
            ", sparseResidencyImage2D = "                               + ( features.sparseResidencyImage2D == VK_TRUE ? "true" : "false" ) +
            ", sparseResidencyImage3D = "                               + ( features.sparseResidencyImage3D == VK_TRUE ? "true" : "false" ) +
            ", sparseResidency2Samples = "                              + ( features.sparseResidency2Samples == VK_TRUE ? "true" : "false" ) +
            ", sparseResidency4Samples = "                              + ( features.sparseResidency4Samples == VK_TRUE ? "true" : "false" ) +
            ", sparseResidency8Samples = "                              + ( features.sparseResidency8Samples == VK_TRUE ? "true" : "false" ) +
            ", sparseResidency16Samples = "                             + ( features.sparseResidency16Samples == VK_TRUE ? "true" : "false" ) +
            ", sparseResidencyAliased = "                               + ( features.sparseResidencyAliased == VK_TRUE ? "true" : "false" ) +
            ", variableMultisampleRate = "                              + ( features.variableMultisampleRate == VK_TRUE ? "true" : "false" ) +
            ", inheritedQueries = "                                     + ( features.inheritedQueries == VK_TRUE ? "true" : "false" ) +
            "}";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceDetails ) const & details
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceDetails ) ) " "
            "{ basicProperties = "                                  + toString ( details.basicProperties ) +
            ", basicFeatures = "                                    + toString ( details.basicFeatures ) +

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

            ", vulkan11Properties = "                               + toString ( details.vulkan11Properties ) +
            ", IDProperties = "                                     + toString ( details.IDProperties ) +
            ", maintenanceProperties = "                            + toString ( details.maintenanceProperties ) +
            ", multiviewProperties = "                              + toString ( details.multiviewProperties ) +
            ", pointClippingProperties = "                          + toString ( details.pointClippingProperties ) +
            ", protectedMemoryProperties = "                        + toString ( details.protectedMemoryProperties ) +
            ", subgroupProperties = "                               + toString ( details.subgroupProperties ) +

            ", vulkan11Features = "                                 + toString ( details.vulkan11Features ) +
            ", 16BitStorageFeatures = "                             + toString ( details._16BitStorageFeatures ) +
            ", multiviewFeatures = "                                + toString ( details.multiviewFeatures ) +
            ", protectedMemoryFeatures = "                          + toString ( details.protectedMemoryFeatures ) +
            ", samplerYCBCRConversionFeatures = "                   + toString ( details.samplerYCBCRConversionFeatures ) +
            ", shaderDrawParametersFeatures = "                     + toString ( details.shaderDrawParametersFeatures ) +
            ", variablePointersFeatures = "                         + toString ( details.variablePointersFeatures ) +

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

            ", vulkan12Properties = "                               + toString ( details.vulkan12Properties ) +
            ", driverProperties = "                                 + toString ( details.driverProperties ) +
            ", depthStencilResolveProperties = "                    + toString ( details.depthStencilResolveProperties ) +
            ", descriptorIndexingProperties = "                     + toString ( details.descriptorIndexingProperties ) +
            ", deviceFloatControlsProperties = "                    + toString ( details.deviceFloatControlsProperties ) +
            ", samplerFilterMinmaxProperties = "                    + toString ( details.samplerFilterMinmaxProperties ) +
            ", timelineSemaphoreProperties = "                      + toString ( details.timelineSemaphoreProperties ) +

            ", vulkan12Features = "                                 + toString ( details.vulkan12Features ) +
            ", 8BitStorageFeatures = "                              + toString ( details._8BitStorageFeatures ) +
            ", bufferDeviceAddressFeatures = "                      + toString ( details.bufferDeviceAddressFeatures ) +
            ", descriptorIndexingFeatures = "                       + toString ( details.descriptorIndexingFeatures ) +
            ", hostQueryResetFeatures = "                           + toString ( details.hostQueryResetFeatures ) +
            ", imagelessFramebufferFeatures = "                     + toString ( details.imagelessFramebufferFeatures ) +
            ", scalarBlockLayoutFeatures = "                        + toString ( details.scalarBlockLayoutFeatures ) +
            ", separateDepthStencilLayoutsFeatures = "              + toString ( details.separateDepthStencilLayoutsFeatures ) +
            ", shaderAtomicInt64Features = "                        + toString ( details.shaderAtomicInt64Features ) +
            ", shaderFloat16Int8Features = "                        + toString ( details.shaderFloat16Int8Features ) +
            ", shaderSubgroupExtendedTypesFeatures = "              + toString ( details.shaderSubgroupExtendedTypesFeatures ) +
            ", timelineSemaphoreFeatures = "                        + toString ( details.timelineSemaphoreFeatures ) +
            ", uniformBufferStandardLayoutFeatures = "              + toString ( details.uniformBufferStandardLayoutFeatures ) +
            ", vulkanMemoryModelFeatures = "                        + toString ( details.vulkanMemoryModelFeatures ) +

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            ", vulkan13Properties = "                               + toString ( details.vulkan13Properties ) +

            ", vulkan13Features = "                                 + toString ( details.vulkan13Features ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_4444_FORMATS_AVAILABLE

            ", 4444FormatsFeatures = "                              + toString ( details._4444FormatsFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ASTC_DECODE_MODE_AVAILABLE

            ", ASTCDecodeFeatures = "                               + toString ( details.ASTCDecodeFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PCI_BUS_INFO_AVAILABLE

            ", pciBusInfoProperties = "                             + toString ( details.pciBusInfoProperties ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PHYSICAL_DEVICE_DRM_AVAILABLE

            ", DRMProperties = "                                    + toString ( details.DRMProperties ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE

            ", accelerationStructureProperties = "                  + toString ( details.accelerationStructureProperties ) +
            ", accelerationStructureFeatures = "                    + toString ( details.accelerationStructureFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE

            ", blendOperationAdvancedProperties = "                 + toString ( details.blendOperationAdvancedProperties ) +
            ", blendOperationAdvancedFeatures = "                   + toString ( details.blendOperationAdvancedFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BORDER_COLOR_SWIZZLE_AVAILABLE

            ", borderColorSwizzleFeatures = "                       + toString ( details.borderColorSwizzleFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_DEVICE_COHERENT_MEMORY_AVAILABLE

            ", coherentMemoryFeaturesAMD = "                        + toString ( details.coherentMemoryFeaturesAMD ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_COLOR_WRITE_ENABLE_AVAILABLE

            ", colorWriteEnabledFeatures = "                        + toString ( details.colorWriteEnabledFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COMPUTE_SHADER_DERIVATIVES_AVAILABLE

            ", computeShaderDerivativesFeaturesNVidia = "           + toString ( details.computeShaderDerivativesFeaturesNVidia ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE

            ", conditionalRenderingFeatures = "                     + toString ( details.conditionalRenderingFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONSERVATIVE_RASTERIZATION_AVAILABLE

            ", conservativeRasterizationProperties = "              + toString ( details.conservativeRasterizationProperties ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE

            ", cooperativeMatrixPropertiesNVidia = "                + toString ( details.cooperativeMatrixPropertiesNVidia ) +
            ", cooperativeMatrixFeaturesNVidia = "                  + toString ( details.cooperativeMatrixFeaturesNVidia ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CORNER_SAMPLED_IMAGE_AVAILABLE

            ", cornerSampledImageFeaturesNVidia = "                 + toString ( details.cornerSampledImageFeaturesNVidia ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COVERAGE_REDUCTION_MODE_AVAILABLE

            ", coverageReductionModeFeaturesNVidia = "              + toString ( details.coverageReductionModeFeaturesNVidia ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE

            ", customBorderColorProperties = "                      + toString ( details.customBorderColorProperties ) +
            ", customBorderColorFeatures = "                        + toString ( details.customBorderColorFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_IMAGE_ALIASING_AVAILABLE

            ", dedicatedAllocationImageAliasingFeaturesNVidia = "   + toString ( details.dedicatedAllocationImageAliasingFeaturesNVidia ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_CONTROL_AVAILABLE

            ", depthClipControlFeatures = "                         + toString ( details.depthClipControlFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_ENABLE_AVAILABLE

            ", depthClipEnableFeatures = "                          + toString ( details.depthClipEnableFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE

            ", deviceGeneratedCommandsProperties = "                + toString ( details.deviceGeneratedCommandsProperties ) +
            ", deviceGeneratedCommandsFeatures = "                  + toString ( details.deviceGeneratedCommandsFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEVICE_MEMORY_REPORT_AVAILABLE

            ", deviceMemoryReportFeatures = "                       + toString ( details.deviceMemoryReportFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTICS_CONFIG_AVAILABLE

            ", diagnosticsConfigFeaturesNVidia = "                  + toString ( details.diagnosticsConfigFeaturesNVidia ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISCARD_RECTANGLES_AVAILABLE

            ", discardRectangleProperties = "                       + toString ( details.discardRectangleProperties ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE

            ", dynamicRenderingFeatures = "                         + toString ( details.dynamicRenderingFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SCISSOR_EXCLUSIVE_AVAILABLE

            ", exclusiveScissorFeaturesNVidia = "                   + toString ( details.exclusiveScissorFeaturesNVidia ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE

            ", extendedDynamicStateFeatures = "                     + toString ( details.extendedDynamicStateFeatures ) +
            ", extendedDynamicState2Features = "                    + toString ( details.extendedDynamicState2Features ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTERNAL_MEMORY_HOST_AVAILABLE

            ", externalMemoryHostProperties = "                     + toString ( details.externalMemoryHostProperties ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_RDMA_AVAILABLE

            ", externalMemoryRDMAFeaturesNVidia = "                 + toString ( details.externalMemoryRDMAFeaturesNVidia ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE

            ", fragmentDensityMap2Properties = "                    + toString ( details.fragmentDensityMap2Properties ) +
            ", fragmentDensityMap2Features = "                      + toString ( details.fragmentDensityMap2Features ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE

            ", fragmentDensityMapOffsetPropertiesQualcomm = "       + toString ( details.fragmentDensityMapOffsetPropertiesQualcomm ) +
            ", fragmentDensityMapOffsetFeaturesQualcomm = "         + toString ( details.fragmentDensityMapOffsetFeaturesQualcomm ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

            ", fragmentDensityMapProperties = "                     + toString ( details.fragmentDensityMapProperties ) +
            ", fragmentDensityMapFeatures = "                       + toString ( details.fragmentDensityMapFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADER_BARYCENTRIC_AVAILABLE

            ", fragmentShaderBarycentricFeaturesNVidia = "          + toString ( details.fragmentShaderBarycentricFeaturesNVidia ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_SHADER_INTERLOCK_AVAILABLE

            ", fragmentShaderInterlockFeatures = "                  + toString ( details.fragmentShaderInterlockFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE

            ", fragmentShadingRateEnumsPropertiesNVidia = "         + toString ( details.fragmentShadingRateEnumsPropertiesNVidia ) +
            ", fragmentShadingRateEnumsFeaturesNVidia = "           + toString ( details.fragmentShadingRateEnumsFeaturesNVidia ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE

            ", fragmentShadingRateProperties = "                    + toString ( details.fragmentShadingRateProperties ) +
            ", fragmentShadingRateFeatures = "                      + toString ( details.fragmentShadingRateFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE

            ", globalPriorityQueryFeatures = "                      + toString ( details.globalPriorityQueryFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_ROBUSTNESS_AVAILABLE

            ", imageRobustnessFeatures = "                          + toString ( details.imageRobustnessFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_VIEW_MIN_LOD_AVAILABLE

            ", imageViewMinLODFeatures = "                          + toString ( details.imageViewMinLODFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INDEX_TYPE_UINT8_AVAILABLE

            ", indexTypeUInt8Features = "                           + toString ( details.indexTypeUInt8Features ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_INHERITED_VIEWPORT_SCISSOR_AVAILABLE

            ", inheritedViewportScissorFeaturesNVidia = "           + toString ( details.inheritedViewportScissorFeaturesNVidia ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE

            ", inlineUniformBlockProperties = "                     + toString ( details.inlineUniformBlockProperties ) +
            ", inlineUniformBlockFeatures = "                       + toString ( details.inlineUniformBlockFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_INVOCATION_MASK_AVAILABLE

            ", invocationMaskFeaturesHuawei = "                     + toString ( details.invocationMaskFeaturesHuawei ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE

            ", lineRasterizationProperties = "                      + toString ( details.lineRasterizationProperties ) +
            ", lineRasterizationFeatures = "                        + toString ( details.lineRasterizationFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_LINEAR_COLOR_ATTACHMENT_AVAILABLE

            ", linearColorAttachmentFeaturesNVidia = "              + toString ( details.linearColorAttachmentFeaturesNVidia ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE

            ", maintenance4Properties = "                           + toString ( details.maintenance4Properties ) +
            ", maintenance4Features = "                             + toString ( details.maintenance4Features ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_PRIORITY_AVAILABLE

            ", memoryPriorityFeatures = "                           + toString ( details.memoryPriorityFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE

            ", meshShaderPropertiesNVidia = "                       + toString ( details.meshShaderPropertiesNVidia ) +
            ", meshShaderFeaturesNVidia = "                         + toString ( details.meshShaderFeaturesNVidia ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE

            ", multiDrawProperties = "                              + toString ( details.multiDrawProperties ) +
            ", multiDrawFeatures = "                                + toString ( details.multiDrawFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE

            ", mutableDescriptorTypeFeaturesValve = "               + toString ( details.mutableDescriptorTypeFeaturesValve ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE

            ", multiviewPerViewAttributesPropertiesNVidia = "       + toString ( details.multiviewPerViewAttributesPropertiesNVidia ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PAGEABLE_DEVICE_LOCAL_MEMORY_AVAILABLE

            ", pageableDeviceLocalMemoryFeatures = "                + toString ( details.pageableDeviceLocalMemoryFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

            ", performanceQueryProperties = "                       + toString ( details.performanceQueryProperties ) +
            ", performanceQueryFeatures = "                         + toString ( details.performanceQueryFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE

            ", pipelineCreationCacheControlFeatures = "             + toString ( details.pipelineCreationCacheControlFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE

            ", pipelineExecutablePropertiesFeatures = "             + toString ( details.pipelineExecutablePropertiesFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE

            ", portabilitySubsetProperties = "                      + toString ( details.portabilitySubsetProperties ) +
            ", portabilitySubsetFeatures = "                        + toString ( details.portabilitySubsetFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_ID_AVAILABLE

            ", presentIDFeatures = "                                + toString ( details.presentIDFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_WAIT_AVAILABLE

            ", presentWaitFeatures = "                              + toString ( details.presentWaitFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIMITIVE_TOPOLOGY_LIST_RESTART_AVAILABLE

            ", primitiveTopologyListRestartFeatures = "             + toString ( details.primitiveTopologyListRestartFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE

            ", privateDataFeatures = "                              + toString ( details.privateDataFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE

            ", provokingVertexProperties = "                        + toString ( details.provokingVertexProperties ) +
            ", provokingVertexFeatures = "                          + toString ( details.provokingVertexFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PUSH_DESCRIPTOR_AVAILABLE

            ", pushDescriptorProperties = "                         + toString ( details.pushDescriptorProperties ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_RGBA_10_X_6_FORMATS_AVAILABLE

            ", RGBA10x6FormatsFeatures = "                          + toString ( details.RGBA10x6FormatsFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ARM_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_AVAILABLE

            ", rasterizationOrderAttachmentAccessFeaturesARM = "    + toString ( details.rasterizationOrderAttachmentAccessFeaturesARM ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_QUERY_AVAILABLE

            ", rayQueryFeatures = "                                 + toString ( details.rayQueryFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE

            ", rayTracingPipelineProperties = "                     + toString ( details.rayTracingPipelineProperties ) +
            ", rayTracingPipelineFeatures = "                       + toString ( details.rayTracingPipelineFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE

            ", rayTracingPropertiesNVidia = "                       + toString ( details.rayTracingPropertiesNVidia ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE

            ", rayTracingMotionBlurFeaturesNVidia = "               + toString ( details.rayTracingMotionBlurFeaturesNVidia ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_REPRESENTATIVE_FRAGMENT_TEST_AVAILABLE

            ", representativeFragmentTestFeaturesNVidia = "         + toString ( details.representativeFragmentTestFeaturesNVidia ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE

            ", robustnessProperties = "                             + toString ( details.robustnessProperties ) +
            ", robustnessFeatures = "                               + toString ( details.robustnessFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE

            ", sampleLocationsProperties = "                        + toString ( details.sampleLocationsProperties ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_AVAILABLE

            ", shaderAtomicFloatFeatures = "                        + toString ( details.shaderAtomicFloatFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_2_AVAILABLE

            ", shaderAtomicFloat2Features = "                       + toString ( details.shaderAtomicFloat2Features ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_AVAILABLE

            ", shaderCorePropertiesAMD = "                          + toString ( details.shaderCorePropertiesAMD ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_2_AVAILABLE

            ", shaderCoreProperties2AMD = "                         + toString ( details.shaderCoreProperties2AMD ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_CLOCK_AVAILABLE

            ", shaderClockFeatures = "                              + toString ( details.shaderClockFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_DEMOTE_TO_HELPER_INVOCATION_AVAILABLE

            ", shaderDemoteToHelperInvocationFeatures = "           + toString ( details.shaderDemoteToHelperInvocationFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_IMAGE_ATOMIC_INT64_AVAILABLE

            ", shaderImageAtomicInt64Features = "                   + toString ( details.shaderImageAtomicInt64Features ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_IMAGE_FOOTPRINT_AVAILABLE

            ", shaderImageFootprintFeaturesNVidia = "               + toString ( details.shaderImageFootprintFeaturesNVidia ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE

            ", shaderSmBuiltinsProperties = "                       + toString ( details.shaderSmBuiltinsPropertiesNVidia ) +
            ", shaderSmBuiltinsFeaturesNVidia = "                   + toString ( details.shaderSmBuiltinsFeaturesNVidia ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_SUBGROUP_UNIFORM_CONTROL_FLOW_AVAILABLE

            ", shaderSubgroupUniformControlFlowFeatures = "         + toString ( details.shaderSubgroupUniformControlFlowFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_TERMINATE_INVOCATION_AVAILABLE

            ", shaderTerminateInvocationFeatures = "                + toString ( details.shaderTerminateInvocationFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE

            ", shadingRateImagePropertiesNVidia = "                 + toString ( details.shadingRateImagePropertiesNVidia ) +
            ", shadingRateImageFeaturesNVidia = "                   + toString ( details.shadingRateImageFeaturesNVidia ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE

            ", subgroupSizeControlProperties = "                    + toString ( details.subgroupSizeControlProperties ) +
            ", subgroupSizeControlFeatures = "                      + toString ( details.subgroupSizeControlFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE

            ", subpassShadingPropertiesHuawei = "                   + toString ( details.subpassShadingPropertiesHuawei ) +
            ", subpassShadingFeaturesHuawei = "                     + toString ( details.subpassShadingFeaturesHuawei ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE

            ", synchronizationFeatures = "                          + toString ( details.synchronizationFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE

            ", texelBufferAlignmentProperties = "                   + toString ( details.texelBufferAlignmentProperties ) +
            ", texelBufferAlignmentFeatures = "                     + toString ( details.texelBufferAlignmentFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXTURE_COMPRESSION_ASTC_HDR_AVAILABLE

            ", textureCompressionASTCHDRFeatures = "                + toString ( details.textureCompressionASTCHDRFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE

            ", transformFeedbackProperties = "                      + toString ( details.transformFeedbackProperties ) +
            ", transformFeedbackFeatures = "                        + toString ( details.transformFeedbackFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE

            ", vertexAttributeDivisorProperties = "                 + toString ( details.vertexAttributeDivisorProperties ) +
            ", vertexAttributeDivisorFeatures = "                   + toString ( details.vertexAttributeDivisorFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_INPUT_DYNAMIC_STATE_AVAILABLE

            ", vertexInputDynamicState = "                          + toString ( details.vertexInputDynamicStateFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE

            ", shaderIntegerDotProductProperties = "                + toString ( details.shaderIntegerDotProductProperties ) +
            ", shaderIntegerDotProductFeatures = "                  + toString ( details.shaderIntegerDotProductFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_SHADER_INTEGER_FUNCTIONS_AVAILABLE

            ", shaderIntegerFunctionsFeaturesIntel = "              + toString ( details.shaderIntegerFunctionsFeaturesIntel ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_AVAILABLE

            ", workgroupMemoryExplicitLayoutFeatures = "            + toString ( details.workgroupMemoryExplicitLayoutFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_2_PLANE_444_FORMATS_AVAILABLE

            ", YCBCR2Plane444FormatFeatures = "                     + toString ( details.YCBCR2Plane444FormatFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_IMAGE_ARRAYS_AVAILABLE

            ", YCBCRImageArraysFeatures = "                         + toString ( details.YCBCRImageArraysFeatures ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ZERO_INITIALIZE_WORKGROUP_MEMORY_AVAILABLE

            ", zeroInitializeWorkgroupMemoryFeatures = "            + toString ( details.zeroInitializeWorkgroupMemoryFeatures ) +

#endif


            " }";
}

#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( QueueFamilyProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( QueueFamilyProperties ) ) " "
            "{ queueFlags = "_s                 + :: flagsToString < Type ( QueueFlag ) > ( properties.queueFlags ) +
            ", queueCount = "                   + properties.queueCount +
            ", timestampValidBits = "           + properties.timestampValidBits +
            ", minImageTransferGranularity = "  + toString ( properties.minImageTransferGranularity ) +
            " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( QueueFamilyExtendedProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( QueueFamilyExtendedProperties ) ) " "
            "{ type = "_s       + toString ( properties.structureType ) +
            ", pNext = "        + :: toString ( properties.pNext ) +
            ", properties = "   + toString ( properties.properties ) +
            " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( QueueFamilyDetails ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( QueueFamilyDetails ) ) " "
            "{ properties = "                   + toString ( properties.properties ) +

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTIC_CHECKPOINTS_AVAILABLE

            ", checkpointProperties = "         + toString ( properties.checkpointPropertiesNVidia ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE

            ", globalPriorityProperties = "     + toString ( properties.globalPriorityProperties ) +

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE

            ", queryResultStatusProperties = "  + toString ( properties.queryResultStatusProperties ) +
            ", videoProperties = "              + toString ( properties.videoProperties ) +

#endif

            " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTIC_CHECKPOINTS_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( QueueFamilyCheckpointPropertiesNVidia ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( QueueFamilyCheckpointPropertiesNVidia ) ) " "
           "{ type = "_s                        + toString ( properties.structureType ) +
           ", pNext = "                         + :: toString ( properties.pNext ) +
           ", checkpointExecutionStageMask = "  + :: flagsToString < Type ( PipelineStageFlag ) > ( properties.checkpointExecutionStageMask ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( QueueFamilyGlobalPriorityProperties ) const & properties
) noexcept -> String {

    String prioritiesAsString = "[ ";
    for ( uint32 i = 0U; i < properties.priorityCount; ++ i ) {
        prioritiesAsString += toString ( static_cast < __C_ENG_TYPE ( QueueGlobalPriority ) > ( properties.priorities[i] ) ) + ", "_s;
    }

    (void) prioritiesAsString.removeSuffix(", ").append(" ]");

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( QueueFamilyGlobalPriorityProperties ) ) " "
            "{ type = "_s               + toString ( properties.structureType ) +
            ", pNext = "                + :: toString ( properties.pNext ) +
            ", priorityCount = "        + properties.priorityCount +
            ", priorities = "           + prioritiesAsString +
            " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( VideoCodecOperationFlag ) operation
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( operation ) {
        case __C_ENG_TYPE ( VideoCodecOperationFlag ) :: VideoCodecOperationFlagInvalid:            { asString = "Invalid";         break; }

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED

        case __C_ENG_TYPE ( VideoCodecOperationFlag ) :: VideoCodecOperationFlagEncodeH264:         { asString = "Encode H264";     break; }
        case __C_ENG_TYPE ( VideoCodecOperationFlag ) :: VideoCodecOperationFlagEncodeH265:         { asString = "Encode H265";     break; }
        case __C_ENG_TYPE ( VideoCodecOperationFlag ) :: VideoCodecOperationFlagDecodeH264:         { asString = "Decode H264";     break; }
        case __C_ENG_TYPE ( VideoCodecOperationFlag ) :: VideoCodecOperationFlagDecodeH265:         { asString = "Decode H265";     break; }

#endif

    }

    return asString;
}

auto vulkan :: toString (
        __C_ENG_TYPE ( QueueFamilyQueryResultStatusProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( QueueFamilyQueryResultStatusProperties ) ) " "
            "{ type = "_s               + toString ( properties.structureType ) +
            ", pNext = "                + :: toString ( properties.pNext ) +
            ", supported = "            + ( properties.supported == VK_TRUE ? "true" : "false" ) +
            " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( VideoQueueFamilyProperties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( VideoQueueFamilyProperties ) ) " "
            "{ type = "_s               + toString ( properties.structureType ) +
            ", pNext = "                + :: toString ( properties.pNext ) +
            ", videoCodecOperations = " + :: flagsToString < Type ( VideoCodecOperationFlag ) > ( properties.videoCodecOperations ) +
            " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( DeviceQueueGlobalPriorityCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( DeviceQueueGlobalPriorityCreateInfo ) ) " "
           "{ type = "_s                + toString ( info.structureType ) +
           ", pNext = "                 + :: toString ( info.pNext ) +
           ", globalPriority = "        + toString ( info.globalPriority ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( DeviceQueueCreateInfo ) const & info
) noexcept -> String {

    String queuePrioritiesAsString = "[ ";
    for ( uint32 i = 0U; i < info.queueCount; ++ i ) {
        queuePrioritiesAsString += info.pQueuePriorities[i] + ", "_s;
    }
    (void) queuePrioritiesAsString.removeSuffix(", ").append(" ]");

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( DeviceQueueCreateInfo ) ) " "
           "{ type = "_s                + toString ( info.structureType ) +
           ", pNext = "                 + :: toString ( info.pNext ) +
           ", flags = "                 + :: flagsToString ( info.flags ) +
           ", queueFamilyIndex = "      + info.queueFamilyIndex +
           ", queueCount = "            + info.queueCount +
           ", pQueuePriorities = "      + queuePrioritiesAsString +
           " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( DeviceCreateInfo ) const & info
) noexcept -> String {

    String queueCreateInfosAsString = "[ ";
    for ( uint32 i = 0U; i < info.queueCreateInfoCount; ++ i ) {
        queueCreateInfosAsString += toString ( info.pQueueCreateInfos[i] ) + ", "_s;
    }
    (void) queueCreateInfosAsString.removeSuffix(", ").append(" ]");

#if ! __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

    String layerNamesAsString = "[ ";
    for ( uint32 i = 0U; i < info.enabledLayerCount; ++ i ) {
        layerNamesAsString += info.pEnabledLayerNames[i] + ", ";
    }
    (void) layerNamesAsString.removeSuffix(", ").append(" ]");

#endif

    String enabledExtensionNames = "[ ";
    for ( uint32 i = 0U; i < info.enabledExtensionCount; ++ i ) {
        enabledExtensionNames += info.pEnabledExtensionNames[i] + ", "_s;
    }
    (void) enabledExtensionNames.removeSuffix(", ").append(" ]");

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( DeviceCreateInfo ) ) " "
           "{ type = "_s                    + toString ( info.structureType ) +
           ", pNext = "                     + :: toString ( info.pNext ) +
           ", flags = "                     + :: flagsToString ( info.flags ) +
           ", queueCreateInfoCount = "      + info.queueCreateInfoCount +
           ", pQueueCreateInfos = "         + queueCreateInfosAsString +

#if ! __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

           ", enabledLayerCount = "         + info.enabledLayerCount +
           ", pEnabledLayerNames = "        + layerNamesAsString +

#endif

           ", enabledExtensionCount = "     + info.enabledExtensionCount +
           ", pEnabledExtensionNames = "    + enabledExtensionNames +
           ", pEnabledFeatures = "          + :: toString ( info.pEnabledFeatures ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( DeviceGroupDeviceCreateInfo ) const & info
) noexcept -> String {

    String physicalDevicesAsString = "[ ";
    for ( uint32 i = 0U; i < info.physicalDeviceCount; ++ i ) {
        physicalDevicesAsString += :: toString ( info.pPhysicalDevices[i] ) + ", "_s;
    }
    (void) physicalDevicesAsString.removeSuffix(", ").append(" ]");

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( DeviceGroupDeviceCreateInfo ) ) " "
           "{ type = "_s                + toString ( info.structureType ) +
           ", pNext = "                 + :: toString ( info.pNext ) +
           ", physicalDeviceCount = "   + info.physicalDeviceCount +
           ", pPhysicalDevices = "      + physicalDevicesAsString +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_MEMORY_OVERALLOCATION_BEHAVIOUR_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( MemoryOverallocationBehaviorAMD ) behavior
) noexcept -> StringLiteral {

    StringLiteral asString = "";
    switch ( behavior ) {
        case __C_ENG_TYPE ( MemoryOverallocationBehaviorAMD ) :: MemoryOverallocationBehaviorAMDDefault:    { asString = "Default";     break; }
        case __C_ENG_TYPE ( MemoryOverallocationBehaviorAMD ) :: MemoryOverallocationBehaviorAMDAllowed:    { asString = "Allowed";     break; }
        case __C_ENG_TYPE ( MemoryOverallocationBehaviorAMD ) :: MemoryOverallocationBehaviorAMDDisallowed: { asString = "Disallowed";  break; }
    }

    return asString;
}

auto vulkan :: toString (
        __C_ENG_TYPE ( DeviceMemoryOverallocationCreateInfoAMD ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( DeviceMemoryOverallocationCreateInfoAMD ) ) " "
           "{ type = "_s                    + toString ( info.structureType ) +
           ", pNext = "                     + :: toString ( info.pNext ) +
           ", overallocationBehavior = "    + toString ( info.overallocationBehavior ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( DevicePrivateDataCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( DevicePrivateDataCreateInfo ) ) " "
           "{ type = "_s                        + toString ( info.structureType ) +
           ", pNext = "                         + :: toString ( info.pNext ) +
           ", privateDataSlotRequestCount = "   + info.privateDataSlotRequestCount +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEVICE_MEMORY_REPORT_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( DeviceMemoryReportFlag ) flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    return asString;
}

auto vulkan :: toString (
        __C_ENG_TYPE ( DeviceMemoryReportEventType ) eventType
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( eventType ) {
        case DeviceMemoryReportEventTypeAllocate:           { asString = "Allocate";            break; }
        case DeviceMemoryReportEventTypeFree:               { asString = "Free";                break; }
        case DeviceMemoryReportEventTypeImport:             { asString = "Import";              break; }
        case DeviceMemoryReportEventTypeUnimport:           { asString = "Unimport";            break; }
        case DeviceMemoryReportEventTypeAllocationFailed:   { asString = "AllocationFailed";    break; }
    }

    return asString;
}

auto vulkan :: toString (
        __C_ENG_TYPE ( DeviceDeviceMemoryReportCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( DeviceDeviceMemoryReportCreateInfo ) ) " "
           "{ type = "_s                        + toString ( info.structureType ) +
           ", pNext = "                         + :: toString ( info.pNext ) +
           ", flags = "                         + :: flagsToString < Type ( DeviceMemoryReportFlag ) > ( info.flags ) +
           ", callback = "                      + :: toString ( info.callback ) +
           ", pUserData = "                     + :: toString ( info.pUserData ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTICS_CONFIG_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( DeviceDiagnosticsConfigFlagNVidia ) flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";
    switch ( flag ) {
        case __C_ENG_TYPE ( DeviceDiagnosticsConfigFlagNVidia ) :: DeviceDiagnosticsConfigFlagNVidiaEnableShaderDebugInfo:      { asString = "Shader Debug Info";       break; }
        case __C_ENG_TYPE ( DeviceDiagnosticsConfigFlagNVidia ) :: DeviceDiagnosticsConfigFlagNVidiaEnableAutomaticCheckpoints: { asString = "Automatic Checkpoints";   break; }
        case __C_ENG_TYPE ( DeviceDiagnosticsConfigFlagNVidia ) :: DeviceDiagnosticsConfigFlagNVidiaEnableResourceTracking:     { asString = "Resource Tracking";       break; }
    }

    return asString;
}

auto vulkan :: toString (
        __C_ENG_TYPE ( DeviceDiagnosticsConfigCreateInfoNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( DeviceDiagnosticsConfigCreateInfoNVidia ) ) " "
           "{ type = "_s                    + toString ( info.structureType ) +
           ", pNext = "                     + :: toString ( info.pNext ) +
           ", flags = "                     + :: flagsToString < Type ( DeviceDiagnosticsConfigFlagNVidia ) > ( info.flags ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDevice16BitStorageFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDevice16BitStorageFeatures ) ) " "
           "{ type = "_s                                    + toString ( features.structureType ) +
           ", pNext = "                                     + :: toString ( features.pNext ) +
           ", storageBuffer16BitAccess = "                  + ( features.storageBuffer16BitAccess == VK_TRUE ? "true" : "false" ) +
           ", uniformAndStorageBuffer16BitAccess = "        + ( features.uniformAndStorageBuffer16BitAccess == VK_TRUE ? "true" : "false" ) +
           ", storagePushConstant16 = "                     + ( features.storagePushConstant16 == VK_TRUE ? "true" : "false" ) +
           ", storageInputOutput16 = "                      + ( features.storageInputOutput16 == VK_TRUE ? "true" : "false" ) +
           " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceMultiviewFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceMultiviewFeatures ) ) " "
           "{ type = "_s                                    + toString ( features.structureType ) +
           ", pNext = "                                     + :: toString ( features.pNext ) +
           ", multiview = "                                 + ( features.multiview == VK_TRUE ? "true" : "false" ) +
           ", multiviewGeometryShader = "                   + ( features.multiviewGeometryShader == VK_TRUE ? "true" : "false" ) +
           ", multiviewTessellationShader = "               + ( features.multiviewTessellationShader == VK_TRUE ? "true" : "false" ) +
           " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceProtectedMemoryFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceProtectedMemoryFeatures ) ) " "
           "{ type = "_s                                    + toString ( features.structureType ) +
           ", pNext = "                                     + :: toString ( features.pNext ) +
           ", protectedMemory = "                           + ( features.protectedMemory == VK_TRUE ? "true" : "false" ) +
           " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceSamplerYCBCRConversionFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceSamplerYCBCRConversionFeatures ) ) " "
           "{ type = "_s                                    + toString ( features.structureType ) +
           ", pNext = "                                     + :: toString ( features.pNext ) +
           ", samplerYCBCRConversion = "                    + ( features.samplerYCBCRConversion == VK_TRUE ? "true" : "false" ) +
           " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceShaderDrawParametersFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceShaderDrawParametersFeatures ) ) " "
           "{ type = "_s                                    + toString ( features.structureType ) +
           ", pNext = "                                     + :: toString ( features.pNext ) +
           ", shaderDrawParameters = "                      + ( features.shaderDrawParameters == VK_TRUE ? "true" : "false" ) +
           " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceVariablePointersFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceVariablePointersFeatures ) ) " "
           "{ type = "_s                                    + toString ( features.structureType ) +
           ", pNext = "                                     + :: toString ( features.pNext ) +
           ", variablePointersStorageBuffer = "             + ( features.variablePointersStorageBuffer == VK_TRUE ? "true" : "false" ) +
           ", variablePointers = "                          + ( features.variablePointers == VK_TRUE ? "true" : "false" ) +
           " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceVulkan11Features ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceVulkan11Features ) ) " "
           "{ type = "_s                                    + toString ( features.structureType ) +
           ", pNext = "                                     + :: toString ( features.pNext ) +
           ", storageBuffer16BitAccess = "                  + ( features.storageBuffer16BitAccess == VK_TRUE ? "true" : "false" ) +
           ", uniformAndStorageBuffer16BitAccess = "        + ( features.uniformAndStorageBuffer16BitAccess == VK_TRUE ? "true" : "false" ) +
           ", storagePushConstant16 = "                     + ( features.storagePushConstant16 == VK_TRUE ? "true" : "false" ) +
           ", storageInputOutput16 = "                      + ( features.storageInputOutput16 == VK_TRUE ? "true" : "false" ) +
           ", multiview = "                                 + ( features.multiview == VK_TRUE ? "true" : "false" ) +
           ", multiviewGeometryShader = "                   + ( features.multiviewGeometryShader == VK_TRUE ? "true" : "false" ) +
           ", multiviewTessellationShader = "               + ( features.multiviewTessellationShader == VK_TRUE ? "true" : "false" ) +
           ", variablePointersStorageBuffer = "             + ( features.variablePointersStorageBuffer == VK_TRUE ? "true" : "false" ) +
           ", variablePointers = "                          + ( features.variablePointers == VK_TRUE ? "true" : "false" ) +
           ", protectedMemory = "                           + ( features.protectedMemory == VK_TRUE ? "true" : "false" ) +
           ", samplerYCBCRConversion = "                    + ( features.samplerYCBCRConversion == VK_TRUE ? "true" : "false" ) +
           ", shaderDrawParameters = "                      + ( features.shaderDrawParameters == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDevice8BitStorageFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDevice8BitStorageFeatures ) ) " "
           "{ type = "_s                                    + toString ( features.structureType ) +
           ", pNext = "                                     + :: toString ( features.pNext ) +
           ", storageBuffer8BitAccess = "                   + ( features.storageBuffer8BitAccess == VK_TRUE ? "true" : "false" ) +
           ", uniformAndStorageBuffer8BitAccess = "         + ( features.uniformAndStorageBuffer8BitAccess == VK_TRUE ? "true" : "false" ) +
           ", storagePushConstant8 = "                      + ( features.storagePushConstant8 == VK_TRUE ? "true" : "false" ) +
           " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceBufferDeviceAddressFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceBufferDeviceAddressFeatures ) ) " "
           "{ type = "_s                                    + toString ( features.structureType ) +
           ", pNext = "                                     + :: toString ( features.pNext ) +
           ", bufferDeviceAddress = "                       + ( features.bufferDeviceAddress == VK_TRUE ? "true" : "false" ) +
           ", bufferDeviceAddressCaptureReplay = "          + ( features.bufferDeviceAddressCaptureReplay == VK_TRUE ? "true" : "false" ) +
           ", bufferDeviceAddressMultiDevice = "            + ( features.bufferDeviceAddressMultiDevice == VK_TRUE ? "true" : "false" ) +
           " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceDescriptorIndexingFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceDescriptorIndexingFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", shaderInputAttachmentArrayDynamicIndexing = "             + ( features.shaderInputAttachmentArrayDynamicIndexing == VK_TRUE ? "true" : "false" ) +
           ", shaderUniformTexelBufferArrayDynamicIndexing = "          + ( features.shaderUniformTexelBufferArrayDynamicIndexing == VK_TRUE ? "true" : "false" ) +
           ", shaderStorageTexelBufferArrayDynamicIndexing = "          + ( features.shaderStorageTexelBufferArrayDynamicIndexing == VK_TRUE ? "true" : "false" ) +
           ", shaderUniformBufferArrayNonUniformIndexing = "            + ( features.shaderUniformBufferArrayNonUniformIndexing == VK_TRUE ? "true" : "false" ) +
           ", shaderSampledImageArrayNonUniformIndexing = "             + ( features.shaderSampledImageArrayNonUniformIndexing == VK_TRUE ? "true" : "false" ) +
           ", shaderStorageBufferArrayNonUniformIndexing = "            + ( features.shaderStorageBufferArrayNonUniformIndexing == VK_TRUE ? "true" : "false" ) +
           ", shaderStorageImageArrayNonUniformIndexing = "             + ( features.shaderStorageImageArrayNonUniformIndexing == VK_TRUE ? "true" : "false" ) +
           ", shaderInputAttachmentArrayNonUniformIndexing = "          + ( features.shaderInputAttachmentArrayNonUniformIndexing == VK_TRUE ? "true" : "false" ) +
           ", shaderUniformTexelBufferArrayNonUniformIndexing = "       + ( features.shaderUniformTexelBufferArrayNonUniformIndexing == VK_TRUE ? "true" : "false" ) +
           ", shaderStorageTexelBufferArrayNonUniformIndexing = "       + ( features.shaderStorageTexelBufferArrayNonUniformIndexing == VK_TRUE ? "true" : "false" ) +
           ", descriptorBindingUniformBufferUpdateAfterBind = "         + ( features.descriptorBindingUniformBufferUpdateAfterBind == VK_TRUE ? "true" : "false" ) +
           ", descriptorBindingSampledImageUpdateAfterBind = "          + ( features.descriptorBindingSampledImageUpdateAfterBind == VK_TRUE ? "true" : "false" ) +
           ", descriptorBindingStorageImageUpdateAfterBind = "          + ( features.descriptorBindingStorageImageUpdateAfterBind == VK_TRUE ? "true" : "false" ) +
           ", descriptorBindingStorageBufferUpdateAfterBind = "         + ( features.descriptorBindingStorageBufferUpdateAfterBind == VK_TRUE ? "true" : "false" ) +
           ", descriptorBindingUniformTexelBufferUpdateAfterBind = "    + ( features.descriptorBindingUniformTexelBufferUpdateAfterBind == VK_TRUE ? "true" : "false" ) +
           ", descriptorBindingStorageTexelBufferUpdateAfterBind = "    + ( features.descriptorBindingStorageTexelBufferUpdateAfterBind == VK_TRUE ? "true" : "false" ) +
           ", descriptorBindingUpdateUnusedWhilePending = "             + ( features.descriptorBindingUpdateUnusedWhilePending == VK_TRUE ? "true" : "false" ) +
           ", descriptorBindingPartiallyBound = "                       + ( features.descriptorBindingPartiallyBound == VK_TRUE ? "true" : "false" ) +
           ", descriptorBindingVariableDescriptorCount = "              + ( features.descriptorBindingVariableDescriptorCount == VK_TRUE ? "true" : "false" ) +
           ", runtimeDescriptorArray = "                                + ( features.runtimeDescriptorArray == VK_TRUE ? "true" : "false" ) +
           " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceHostQueryResetFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceHostQueryResetFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", hostQueryReset = "                                        + ( features.hostQueryReset == VK_TRUE ? "true" : "false" ) +
           " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceImagelessFrameBufferFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceImagelessFrameBufferFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", imagelessFramebuffer = "                                  + ( features.imagelessFramebuffer == VK_TRUE ? "true" : "false" ) +
           " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceScalarBlockLayoutFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceScalarBlockLayoutFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", scalarBlockLayout = "                                     + ( features.scalarBlockLayout == VK_TRUE ? "true" : "false" ) +
           " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceSeparateDepthStencilLayoutsFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceSeparateDepthStencilLayoutsFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", separateDepthStencilLayouts = "                           + ( features.separateDepthStencilLayouts == VK_TRUE ? "true" : "false" ) +
           " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceShaderAtomicInt64Features ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceShaderAtomicInt64Features ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", shaderBufferInt64Atomics = "                              + ( features.shaderBufferInt64Atomics == VK_TRUE ? "true" : "false" ) +
           ", shaderSharedInt64Atomics = "                              + ( features.shaderSharedInt64Atomics == VK_TRUE ? "true" : "false" ) +
           " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceShaderFloat16Int8Features ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceShaderFloat16Int8Features ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", shaderFloat16 = "                                         + ( features.shaderFloat16 == VK_TRUE ? "true" : "false" ) +
           ", shaderInt8 = "                                            + ( features.shaderInt8 == VK_TRUE ? "true" : "false" ) +
           " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceShaderSubgroupExtendedTypesFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceShaderSubgroupExtendedTypesFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", shaderSubgroupExtendedTypes = "                           + ( features.shaderSubgroupExtendedTypes == VK_TRUE ? "true" : "false" ) +
           " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceTimelineSemaphoreFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceTimelineSemaphoreFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", timelineSemaphore = "                                     + ( features.timelineSemaphore == VK_TRUE ? "true" : "false" ) +
           " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceUniformBufferStandardLayoutFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceUniformBufferStandardLayoutFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", uniformBufferStandardLayout = "                           + ( features.uniformBufferStandardLayout == VK_TRUE ? "true" : "false" ) +
           " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceVulkanMemoryModelFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceVulkanMemoryModelFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", vulkanMemoryModel = "                                     + ( features.vulkanMemoryModel == VK_TRUE ? "true" : "false" ) +
           ", vulkanMemoryModelDeviceScope = "                          + ( features.vulkanMemoryModelDeviceScope == VK_TRUE ? "true" : "false" ) +
           ", vulkanMemoryModelAvailabilityVisibilityChains = "         + ( features.vulkanMemoryModelAvailabilityVisibilityChains == VK_TRUE ? "true" : "false" ) +
           " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceVulkan12Features ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceVulkan12Features ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", samplerMirrorClampToEdge = "                              + ( features.samplerMirrorClampToEdge == VK_TRUE ? "true" : "false" ) +
           ", drawIndirectCount = "                                     + ( features.drawIndirectCount == VK_TRUE ? "true" : "false" ) +
           ", storageBuffer8BitAccess = "                               + ( features.storageBuffer8BitAccess == VK_TRUE ? "true" : "false" ) +
           ", uniformAndStorageBuffer8BitAccess = "                     + ( features.uniformAndStorageBuffer8BitAccess == VK_TRUE ? "true" : "false" ) +
           ", storagePushConstant8 = "                                  + ( features.storagePushConstant8 == VK_TRUE ? "true" : "false" ) +
           ", shaderBufferInt64Atomics = "                              + ( features.shaderBufferInt64Atomics == VK_TRUE ? "true" : "false" ) +
           ", shaderSharedInt64Atomics = "                              + ( features.shaderSharedInt64Atomics == VK_TRUE ? "true" : "false" ) +
           ", shaderFloat16 = "                                         + ( features.shaderFloat16 == VK_TRUE ? "true" : "false" ) +
           ", shaderInt8 = "                                            + ( features.shaderInt8 == VK_TRUE ? "true" : "false" ) +
           ", descriptorIndexing = "                                    + ( features.descriptorIndexing == VK_TRUE ? "true" : "false" ) +
           ", shaderInputAttachmentArrayDynamicIndexing = "             + ( features.shaderInputAttachmentArrayDynamicIndexing == VK_TRUE ? "true" : "false" ) +
           ", shaderUniformTexelBufferArrayDynamicIndexing = "          + ( features.shaderUniformTexelBufferArrayDynamicIndexing == VK_TRUE ? "true" : "false" ) +
           ", shaderStorageTexelBufferArrayDynamicIndexing = "          + ( features.shaderStorageTexelBufferArrayDynamicIndexing == VK_TRUE ? "true" : "false" ) +
           ", shaderUniformBufferArrayNonUniformIndexing = "            + ( features.shaderUniformBufferArrayNonUniformIndexing == VK_TRUE ? "true" : "false" ) +
           ", shaderSampledImageArrayNonUniformIndexing = "             + ( features.shaderSampledImageArrayNonUniformIndexing == VK_TRUE ? "true" : "false" ) +
           ", shaderStorageBufferArrayNonUniformIndexing = "            + ( features.shaderStorageBufferArrayNonUniformIndexing == VK_TRUE ? "true" : "false" ) +
           ", shaderStorageImageArrayNonUniformIndexing = "             + ( features.shaderStorageImageArrayNonUniformIndexing == VK_TRUE ? "true" : "false" ) +
           ", shaderInputAttachmentArrayNonUniformIndexing = "          + ( features.shaderInputAttachmentArrayNonUniformIndexing == VK_TRUE ? "true" : "false" ) +
           ", shaderUniformTexelBufferArrayNonUniformIndexing = "       + ( features.shaderUniformTexelBufferArrayNonUniformIndexing == VK_TRUE ? "true" : "false" ) +
           ", shaderStorageTexelBufferArrayNonUniformIndexing = "       + ( features.shaderStorageTexelBufferArrayNonUniformIndexing == VK_TRUE ? "true" : "false" ) +
           ", descriptorBindingUniformBufferUpdateAfterBind = "         + ( features.descriptorBindingUniformBufferUpdateAfterBind == VK_TRUE ? "true" : "false" ) +
           ", descriptorBindingSampledImageUpdateAfterBind = "          + ( features.descriptorBindingSampledImageUpdateAfterBind == VK_TRUE ? "true" : "false" ) +
           ", descriptorBindingStorageImageUpdateAfterBind = "          + ( features.descriptorBindingStorageImageUpdateAfterBind == VK_TRUE ? "true" : "false" ) +
           ", descriptorBindingStorageBufferUpdateAfterBind = "         + ( features.descriptorBindingStorageBufferUpdateAfterBind == VK_TRUE ? "true" : "false" ) +
           ", descriptorBindingUniformTexelBufferUpdateAfterBind = "    + ( features.descriptorBindingUniformTexelBufferUpdateAfterBind == VK_TRUE ? "true" : "false" ) +
           ", descriptorBindingStorageTexelBufferUpdateAfterBind = "    + ( features.descriptorBindingStorageTexelBufferUpdateAfterBind == VK_TRUE ? "true" : "false" ) +
           ", descriptorBindingUpdateUnusedWhilePending = "             + ( features.descriptorBindingUpdateUnusedWhilePending == VK_TRUE ? "true" : "false" ) +
           ", descriptorBindingPartiallyBound = "                       + ( features.descriptorBindingPartiallyBound == VK_TRUE ? "true" : "false" ) +
           ", descriptorBindingVariableDescriptorCount = "              + ( features.descriptorBindingVariableDescriptorCount == VK_TRUE ? "true" : "false" ) +
           ", runtimeDescriptorArray = "                                + ( features.runtimeDescriptorArray == VK_TRUE ? "true" : "false" ) +
           ", samplerFilterMinmax = "                                   + ( features.samplerFilterMinmax == VK_TRUE ? "true" : "false" ) +
           ", scalarBlockLayout = "                                     + ( features.scalarBlockLayout == VK_TRUE ? "true" : "false" ) +
           ", imagelessFramebuffer = "                                  + ( features.imagelessFramebuffer == VK_TRUE ? "true" : "false" ) +
           ", uniformBufferStandardLayout = "                           + ( features.uniformBufferStandardLayout == VK_TRUE ? "true" : "false" ) +
           ", shaderSubgroupExtendedTypes = "                           + ( features.shaderSubgroupExtendedTypes == VK_TRUE ? "true" : "false" ) +
           ", separateDepthStencilLayouts = "                           + ( features.separateDepthStencilLayouts == VK_TRUE ? "true" : "false" ) +
           ", hostQueryReset = "                                        + ( features.hostQueryReset == VK_TRUE ? "true" : "false" ) +
           ", timelineSemaphore = "                                     + ( features.timelineSemaphore == VK_TRUE ? "true" : "false" ) +
           ", bufferDeviceAddress = "                                   + ( features.bufferDeviceAddress == VK_TRUE ? "true" : "false" ) +
           ", bufferDeviceAddressCaptureReplay = "                      + ( features.bufferDeviceAddressCaptureReplay == VK_TRUE ? "true" : "false" ) +
           ", bufferDeviceAddressMultiDevice = "                        + ( features.bufferDeviceAddressMultiDevice == VK_TRUE ? "true" : "false" ) +
           ", vulkanMemoryModel = "                                     + ( features.vulkanMemoryModel == VK_TRUE ? "true" : "false" ) +
           ", vulkanMemoryModelDeviceScope = "                          + ( features.vulkanMemoryModelDeviceScope == VK_TRUE ? "true" : "false" ) +
           ", vulkanMemoryModelAvailabilityVisibilityChains = "         + ( features.vulkanMemoryModelAvailabilityVisibilityChains == VK_TRUE ? "true" : "false" ) +
           ", shaderOutputViewportIndex = "                             + ( features.shaderOutputViewportIndex == VK_TRUE ? "true" : "false" ) +
           ", shaderOutputLayer = "                                     + ( features.shaderOutputLayer == VK_TRUE ? "true" : "false" ) +
           ", subgroupBroadcastDynamicId = "                            + ( features.subgroupBroadcastDynamicId == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_4444_FORMATS_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDevice4444FormatsFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDevice4444FormatsFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", formatA4R4G4B4 = "                                        + ( features.formatA4R4G4B4 == VK_TRUE ? "true" : "false" ) +
           ", formatA4B4G4R4 = "                                        + ( features.formatA4B4G4R4 == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ASTC_DECODE_MODE_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceASTCDecodeFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceASTCDecodeFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", decodeModeSharedExponent = "                              + ( features.decodeModeSharedExponent == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceAccelerationStructureFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceAccelerationStructureFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", accelerationStructure = "                                 + ( features.accelerationStructure == VK_TRUE ? "true" : "false" ) +
           ", accelerationStructureCaptureReplay = "                    + ( features.accelerationStructureCaptureReplay == VK_TRUE ? "true" : "false" ) +
           ", accelerationStructureIndirectBuild = "                    + ( features.accelerationStructureIndirectBuild == VK_TRUE ? "true" : "false" ) +
           ", accelerationStructureHostCommands = "                     + ( features.accelerationStructureHostCommands == VK_TRUE ? "true" : "false" ) +
           ", descriptorBindingAccelerationStructureUpdateAfterBind = " + ( features.descriptorBindingAccelerationStructureUpdateAfterBind == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceBlendOperationAdvancedFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceBlendOperationAdvancedFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", advancedBlendCoherentOperations = "                       + ( features.advancedBlendCoherentOperations == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BORDER_COLOR_SWIZZLE_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceBorderColorSwizzleFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceBorderColorSwizzleFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", borderColorSwizzle = "                                    + ( features.borderColorSwizzle == VK_TRUE ? "true" : "false" ) +
           ", borderColorSwizzleFromImage = "                           + ( features.borderColorSwizzleFromImage == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_DEVICE_COHERENT_MEMORY_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceCoherentMemoryFeaturesAMD ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceCoherentMemoryFeaturesAMD ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", deviceCoherentMemory = "                                  + ( features.deviceCoherentMemory == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_COLOR_WRITE_ENABLE_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceColorWriteEnableFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceColorWriteEnableFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", colorWriteEnable = "                                      + ( features.colorWriteEnable == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COMPUTE_SHADER_DERIVATIVES_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceComputeShaderDerivativesFeaturesNVidia ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceComputeShaderDerivativesFeaturesNVidia ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", computeDerivativeGroupQuads = "                           + ( features.computeDerivativeGroupQuads == VK_TRUE ? "true" : "false" ) +
           ", computeDerivativeGroupLinear = "                          + ( features.computeDerivativeGroupLinear == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceConditionalRenderingFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceConditionalRenderingFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", conditionalRendering = "                                  + ( features.conditionalRendering == VK_TRUE ? "true" : "false" ) +
           ", inheritedConditionalRendering = "                         + ( features.inheritedConditionalRendering == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceCooperativeMatrixFeaturesNVidia ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceCooperativeMatrixFeaturesNVidia ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", cooperativeMatrix = "                                     + ( features.cooperativeMatrix == VK_TRUE ? "true" : "false" ) +
           ", cooperativeMatrixRobustBufferAccess = "                   + ( features.cooperativeMatrixRobustBufferAccess == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CORNER_SAMPLED_IMAGE_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceCornerSampledImageFeaturesNVidia ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceCornerSampledImageFeaturesNVidia ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", cornerSampledImage = "                                    + ( features.cornerSampledImage == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COVERAGE_REDUCTION_MODE_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceCoverageReductionModeFeaturesNVidia ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceCoverageReductionModeFeaturesNVidia ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", coverageReductionMode = "                                 + ( features.coverageReductionMode == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceCustomBorderColorFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceCustomBorderColorFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", customBorderColors = "                                    + ( features.customBorderColors == VK_TRUE ? "true" : "false" ) +
           ", customBorderColorWithoutFormat = "                        + ( features.customBorderColorWithoutFormat == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_IMAGE_ALIASING_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNVidia ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNVidia ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", dedicatedAllocationImageAliasing = "                      + ( features.dedicatedAllocationImageAliasing == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_CONTROL_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceDepthClipControlFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceDepthClipControlFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", depthClipControl = "                                      + ( features.depthClipControl == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_ENABLE_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceDepthClipEnableFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceDepthClipEnableFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", depthClipEnable = "                                       + ( features.depthClipEnable == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceDeviceGeneratedCommandsFeaturesNVidia ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceDeviceGeneratedCommandsFeaturesNVidia ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", deviceGeneratedCommands = "                               + ( features.deviceGeneratedCommands == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEVICE_MEMORY_REPORT_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceDeviceMemoryReportFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceDeviceMemoryReportFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", deviceMemoryReport = "                                    + ( features.deviceMemoryReport == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTICS_CONFIG_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceDiagnosticsConfigFeaturesNVidia ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceDiagnosticsConfigFeaturesNVidia ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", diagnosticsConfig = "                                     + ( features.diagnosticsConfig == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceDynamicRenderingFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceDynamicRenderingFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", dynamicRendering = "                                      + ( features.dynamicRendering == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SCISSOR_EXCLUSIVE_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceExclusiveScissorFeaturesNVidia ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceExclusiveScissorFeaturesNVidia ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", exclusiveScissor = "                                      + ( features.exclusiveScissor == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceExtendedDynamicState2Features ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceExtendedDynamicState2Features ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", extendedDynamicState2 = "                                 + ( features.extendedDynamicState2 == VK_TRUE ? "true" : "false" ) +
           ", extendedDynamicState2LogicOp = "                          + ( features.extendedDynamicState2LogicOp == VK_TRUE ? "true" : "false" ) +
           ", extendedDynamicState2PatchControlPoints = "               + ( features.extendedDynamicState2PatchControlPoints == VK_TRUE ? "true" : "false" ) +
           " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceExtendedDynamicStateFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceExtendedDynamicStateFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", extendedDynamicState = "                                  + ( features.extendedDynamicState == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_RDMA_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceExternalMemoryRDMAFeaturesNVidia ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceExternalMemoryRDMAFeaturesNVidia ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", externalMemoryRDMA = "                                    + ( features.externalMemoryRDMA == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMap2Features ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMap2Features ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", fragmentDensityMapDeferred = "                            + ( features.fragmentDensityMapDeferred == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMapFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMapFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", fragmentDensityMap = "                                    + ( features.fragmentDensityMap == VK_TRUE ? "true" : "false" ) +
           ", fragmentDensityMapDynamic = "                             + ( features.fragmentDensityMapDynamic == VK_TRUE ? "true" : "false" ) +
           ", fragmentDensityMapNonSubsampledImages = "                 + ( features.fragmentDensityMapNonSubsampledImages == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMapOffsetFeaturesQualcomm ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMapOffsetFeaturesQualcomm ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", fragmentDensityMapOffset = "                              + ( features.fragmentDensityMapOffset == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADER_BARYCENTRIC_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceFragmentShaderBarycentricFeaturesNVidia ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceFragmentShaderBarycentricFeaturesNVidia ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", fragmentShaderBarycentric = "                             + ( features.fragmentShaderBarycentric == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_SHADER_INTERLOCK_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceFragmentShaderInterlockFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceFragmentShaderInterlockFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", fragmentShaderSampleInterlock = "                         + ( features.fragmentShaderSampleInterlock == VK_TRUE ? "true" : "false" ) +
           ", fragmentShaderPixelInterlock = "                          + ( features.fragmentShaderPixelInterlock == VK_TRUE ? "true" : "false" ) +
           ", fragmentShaderShadingRateInterlock = "                    + ( features.fragmentShaderShadingRateInterlock == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceFragmentShadingRateEnumsFeaturesNVidia ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceFragmentShadingRateEnumsFeaturesNVidia ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", fragmentShadingRateEnums = "                              + ( features.fragmentShadingRateEnums == VK_TRUE ? "true" : "false" ) +
           ", supersampleFragmentShadingRates = "                       + ( features.supersampleFragmentShadingRates == VK_TRUE ? "true" : "false" ) +
           ", noInvocationFragmentShadingRates = "                      + ( features.noInvocationFragmentShadingRates == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceFragmentShadingRateFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceFragmentShadingRateFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", pipelineFragmentShadingRate = "                           + ( features.pipelineFragmentShadingRate == VK_TRUE ? "true" : "false" ) +
           ", primitiveFragmentShadingRate = "                          + ( features.primitiveFragmentShadingRate == VK_TRUE ? "true" : "false" ) +
           ", attachmentFragmentShadingRate = "                         + ( features.attachmentFragmentShadingRate == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceGlobalPriorityQueryFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceGlobalPriorityQueryFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", globalPriorityQuery = "                                   + ( features.globalPriorityQuery == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_ROBUSTNESS_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceImageRobustnessFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceImageRobustnessFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", robustImageAccess = "                                     + ( features.robustImageAccess == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_VIEW_MIN_LOD_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceImageViewMinLODFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceImageViewMinLODFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", minLOD = "                                                + ( features.minLOD == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INDEX_TYPE_UINT8_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceIndexTypeUInt8Features ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceIndexTypeUInt8Features ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", indexTypeUInt8 = "                                        + ( features.indexTypeUInt8 == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_INHERITED_VIEWPORT_SCISSOR_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceInheritedViewportScissorFeaturesNVidia ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceInheritedViewportScissorFeaturesNVidia ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", inheritedViewportScissor2D = "                            + ( features.inheritedViewportScissor2D == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceInlineUniformBlockFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceInlineUniformBlockFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", inlineUniformBlock = "                                    + ( features.inlineUniformBlock == VK_TRUE ? "true" : "false" ) +
           ", descriptorBindingInlineUniformBlockUpdateAfterBind = "    + ( features.descriptorBindingInlineUniformBlockUpdateAfterBind == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_INVOCATION_MASK_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceInvocationMaskFeaturesHuawei ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceInvocationMaskFeaturesHuawei ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", invocationMask = "                                        + ( features.invocationMask == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceLineRasterizationFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceLineRasterizationFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", rectangularLines = "                                      + ( features.rectangularLines == VK_TRUE ? "true" : "false" ) +
           ", bresenhamLines = "                                        + ( features.bresenhamLines == VK_TRUE ? "true" : "false" ) +
           ", smoothLines = "                                           + ( features.smoothLines == VK_TRUE ? "true" : "false" ) +
           ", stippledRectangularLines = "                              + ( features.stippledRectangularLines == VK_TRUE ? "true" : "false" ) +
           ", stippledBresenhamLines = "                                + ( features.stippledBresenhamLines == VK_TRUE ? "true" : "false" ) +
           ", stippledSmoothLines = "                                   + ( features.stippledSmoothLines == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_LINEAR_COLOR_ATTACHMENT_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceLinearColorAttachmentFeaturesNVidia ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceLinearColorAttachmentFeaturesNVidia ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", linearColorAttachment = "                                 + ( features.linearColorAttachment == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceMaintenance4Features ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceMaintenance4Features ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", maintenance4 = "                                          + ( features.maintenance4 == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_PRIORITY_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceMemoryPriorityFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceMemoryPriorityFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", memoryPriority = "                                        + ( features.memoryPriority == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceMeshShaderFeaturesNVidia ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceMeshShaderFeaturesNVidia ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", taskShader = "                                            + ( features.taskShader == VK_TRUE ? "true" : "false" ) +
           ", meshShader = "                                            + ( features.meshShader == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceMultiDrawFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceMultiDrawFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", multiDraw = "                                             + ( features.multiDraw == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceMutableDescriptorTypeFeaturesValve ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceMutableDescriptorTypeFeaturesValve ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", mutableDescriptorType = "                                 + ( features.mutableDescriptorType == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PAGEABLE_DEVICE_LOCAL_MEMORY_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDevicePageableDeviceLocalMemoryFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDevicePageableDeviceLocalMemoryFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", pageableDeviceLocalMemory = "                             + ( features.pageableDeviceLocalMemory == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDevicePerformanceQueryFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDevicePerformanceQueryFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", performanceCounterQueryPools = "                          + ( features.performanceCounterQueryPools == VK_TRUE ? "true" : "false" ) +
           ", performanceCounterMultipleQueryPools = "                  + ( features.performanceCounterMultipleQueryPools == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDevicePipelineCreationCacheControlFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDevicePipelineCreationCacheControlFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", pipelineCreationCacheControl = "                          + ( features.pipelineCreationCacheControl == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDevicePipelineExecutablePropertiesFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDevicePipelineExecutablePropertiesFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", pipelineExecutableInfo = "                                + ( features.pipelineExecutableInfo == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDevicePortabilitySubsetFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDevicePortabilitySubsetFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", constantAlphaColorBlendFactors = "                        + ( features.constantAlphaColorBlendFactors == VK_TRUE ? "true" : "false" ) +
           ", events = "                                                + ( features.events == VK_TRUE ? "true" : "false" ) +
           ", imageViewFormatReinterpretation = "                       + ( features.imageViewFormatReinterpretation == VK_TRUE ? "true" : "false" ) +
           ", imageViewFormatSwizzle = "                                + ( features.imageViewFormatSwizzle == VK_TRUE ? "true" : "false" ) +
           ", imageView2DOn3DImage = "                                  + ( features.imageView2DOn3DImage == VK_TRUE ? "true" : "false" ) +
           ", multisampleArrayImage = "                                 + ( features.multisampleArrayImage == VK_TRUE ? "true" : "false" ) +
           ", mutableComparisonSamplers = "                             + ( features.mutableComparisonSamplers == VK_TRUE ? "true" : "false" ) +
           ", pointPolygons = "                                         + ( features.pointPolygons == VK_TRUE ? "true" : "false" ) +
           ", samplerMipLodBias = "                                     + ( features.samplerMipLodBias == VK_TRUE ? "true" : "false" ) +
           ", separateStencilMaskRef = "                                + ( features.separateStencilMaskRef == VK_TRUE ? "true" : "false" ) +
           ", shaderSampleRateInterpolationFunctions = "                + ( features.shaderSampleRateInterpolationFunctions == VK_TRUE ? "true" : "false" ) +
           ", tessellationIsolines = "                                  + ( features.tessellationIsolines == VK_TRUE ? "true" : "false" ) +
           ", tessellationPointMode = "                                 + ( features.tessellationPointMode == VK_TRUE ? "true" : "false" ) +
           ", triangleFans = "                                          + ( features.triangleFans == VK_TRUE ? "true" : "false" ) +
           ", vertexAttributeAccessBeyondStride = "                     + ( features.vertexAttributeAccessBeyondStride == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_ID_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDevicePresentIDFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDevicePresentIDFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", presentID = "                                             + ( features.presentID == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_WAIT_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDevicePresentWaitFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDevicePresentWaitFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", presentWait = "                                           + ( features.presentWait == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIMITIVE_TOPOLOGY_LIST_RESTART_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDevicePrimitiveTopologyListRestartFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDevicePrimitiveTopologyListRestartFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", primitiveTopologyListRestart = "                          + ( features.primitiveTopologyListRestart == VK_TRUE ? "true" : "false" ) +
           ", primitiveTopologyPatchListRestart = "                     + ( features.primitiveTopologyPatchListRestart == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDevicePrivateDataFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDevicePrivateDataFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", privateData = "                                           + ( features.privateData == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceProvokingVertexFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceProvokingVertexFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", provokingVertexLast = "                                   + ( features.provokingVertexLast == VK_TRUE ? "true" : "false" ) +
           ", transformFeedbackPreservesProvokingVertex = "             + ( features.transformFeedbackPreservesProvokingVertex == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_RGBA_10_X_6_FORMATS_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceRGBA10x6FormatsFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceRGBA10x6FormatsFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", formatRGBA10x6WithoutYCBCRSampler = "                     + ( features.formatRGBA10x6WithoutYCBCRSampler == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ARM_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", rasterizationOrderColorAttachmentAccess = "               + ( features.rasterizationOrderColorAttachmentAccess == VK_TRUE ? "true" : "false" ) +
           ", rasterizationOrderDepthAttachmentAccess = "               + ( features.rasterizationOrderDepthAttachmentAccess == VK_TRUE ? "true" : "false" ) +
           ", rasterizationOrderStencilAttachmentAccess = "             + ( features.rasterizationOrderStencilAttachmentAccess == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_QUERY_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceRayQueryFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceRayQueryFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", rayQuery = "                                              + ( features.rayQuery == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceRayTracingMotionBlurFeaturesNVidia ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceRayTracingMotionBlurFeaturesNVidia ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", rayTracingMotionBlur = "                                  + ( features.rayTracingMotionBlur == VK_TRUE ? "true" : "false" ) +
           ", rayTracingMotionBlurPipelineTraceRaysIndirect = "         + ( features.rayTracingMotionBlurPipelineTraceRaysIndirect == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceRayTracingPipelineFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceRayTracingPipelineFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", rayTracingPipeline = "                                    + ( features.rayTracingPipeline == VK_TRUE ? "true" : "false" ) +
           ", rayTracingPipelineShaderGroupHandleCaptureReplay = "      + ( features.rayTracingPipelineShaderGroupHandleCaptureReplay == VK_TRUE ? "true" : "false" ) +
           ", rayTracingPipelineShaderGroupHandleCaptureReplayMixed = " + ( features.rayTracingPipelineShaderGroupHandleCaptureReplayMixed == VK_TRUE ? "true" : "false" ) +
           ", rayTracingPipelineTraceRaysIndirect = "                   + ( features.rayTracingPipelineTraceRaysIndirect == VK_TRUE ? "true" : "false" ) +
           ", rayTraversalPrimitiveCulling = "                          + ( features.rayTraversalPrimitiveCulling == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_REPRESENTATIVE_FRAGMENT_TEST_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceRepresentativeFragmentTestFeaturesNVidia ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceRepresentativeFragmentTestFeaturesNVidia ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", representativeFragmentTest = "                            + ( features.representativeFragmentTest == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceRobustnessFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceRobustnessFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", robustBufferAccess = "                                    + ( features.robustBufferAccess == VK_TRUE ? "true" : "false" ) +
           ", robustImageAccess = "                                     + ( features.robustImageAccess == VK_TRUE ? "true" : "false" ) +
           ", nullDescriptor = "                                        + ( features.nullDescriptor == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceShaderAtomicFloatFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceShaderAtomicFloatFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", shaderBufferFloat32Atomics = "                            + ( features.shaderBufferFloat32Atomics == VK_TRUE ? "true" : "false" ) +
           ", shaderBufferFloat32AtomicAdd = "                          + ( features.shaderBufferFloat32AtomicAdd == VK_TRUE ? "true" : "false" ) +
           ", shaderBufferFloat64Atomics = "                            + ( features.shaderBufferFloat64Atomics == VK_TRUE ? "true" : "false" ) +
           ", shaderBufferFloat64AtomicAdd = "                          + ( features.shaderBufferFloat64AtomicAdd == VK_TRUE ? "true" : "false" ) +
           ", shaderSharedFloat32Atomics = "                            + ( features.shaderSharedFloat32Atomics == VK_TRUE ? "true" : "false" ) +
           ", shaderSharedFloat32AtomicAdd = "                          + ( features.shaderSharedFloat32AtomicAdd == VK_TRUE ? "true" : "false" ) +
           ", shaderSharedFloat64Atomics = "                            + ( features.shaderSharedFloat64Atomics == VK_TRUE ? "true" : "false" ) +
           ", shaderSharedFloat64AtomicAdd = "                          + ( features.shaderSharedFloat64AtomicAdd == VK_TRUE ? "true" : "false" ) +
           ", shaderImageFloat32Atomics = "                             + ( features.shaderImageFloat32Atomics == VK_TRUE ? "true" : "false" ) +
           ", shaderImageFloat32AtomicAdd = "                           + ( features.shaderImageFloat32AtomicAdd == VK_TRUE ? "true" : "false" ) +
           ", sparseImageFloat32Atomics = "                             + ( features.sparseImageFloat32Atomics == VK_TRUE ? "true" : "false" ) +
           ", sparseImageFloat32AtomicAdd = "                           + ( features.sparseImageFloat32AtomicAdd == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_2_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceShaderAtomicFloat2Features ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceShaderAtomicFloat2Features ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", shaderBufferFloat16Atomics = "                            + ( features.shaderBufferFloat16Atomics == VK_TRUE ? "true" : "false" ) +
           ", shaderBufferFloat16AtomicAdd = "                          + ( features.shaderBufferFloat16AtomicAdd == VK_TRUE ? "true" : "false" ) +
           ", shaderBufferFloat16AtomicMinMax = "                       + ( features.shaderBufferFloat16AtomicMinMax == VK_TRUE ? "true" : "false" ) +
           ", shaderBufferFloat32AtomicMinMax = "                       + ( features.shaderBufferFloat32AtomicMinMax == VK_TRUE ? "true" : "false" ) +
           ", shaderBufferFloat64AtomicMinMax = "                       + ( features.shaderBufferFloat64AtomicMinMax == VK_TRUE ? "true" : "false" ) +
           ", shaderSharedFloat16Atomics = "                            + ( features.shaderSharedFloat16Atomics == VK_TRUE ? "true" : "false" ) +
           ", shaderSharedFloat16AtomicAdd = "                          + ( features.shaderSharedFloat16AtomicAdd == VK_TRUE ? "true" : "false" ) +
           ", shaderSharedFloat16AtomicMinMax = "                       + ( features.shaderSharedFloat16AtomicMinMax == VK_TRUE ? "true" : "false" ) +
           ", shaderSharedFloat32AtomicMinMax = "                       + ( features.shaderSharedFloat32AtomicMinMax == VK_TRUE ? "true" : "false" ) +
           ", shaderSharedFloat64AtomicMinMax = "                       + ( features.shaderSharedFloat64AtomicMinMax == VK_TRUE ? "true" : "false" ) +
           ", shaderImageFloat32AtomicMinMax = "                        + ( features.shaderImageFloat32AtomicMinMax == VK_TRUE ? "true" : "false" ) +
           ", sparseImageFloat32AtomicMinMax = "                        + ( features.sparseImageFloat32AtomicMinMax == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_CLOCK_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceShaderClockFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceShaderClockFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", shaderSubgroupClock = "                                   + ( features.shaderSubgroupClock == VK_TRUE ? "true" : "false" ) +
           ", shaderDeviceClock = "                                     + ( features.shaderDeviceClock == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_DEMOTE_TO_HELPER_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceShaderDemoteToHelperInvocationFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceShaderDemoteToHelperInvocationFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", shaderSubgroupClock = "                                   + ( features.shaderDemoteToHelperInvocation == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_IMAGE_ATOMIC_INT64_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceShaderImageAtomicInt64Features ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceShaderImageAtomicInt64Features ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", shaderImageInt64Atomics = "                               + ( features.shaderImageInt64Atomics == VK_TRUE ? "true" : "false" ) +
           ", sparseImageInt64Atomics = "                               + ( features.sparseImageInt64Atomics == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_IMAGE_FOOTPRINT_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceShaderImageFootprintFeaturesNVidia ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceShaderImageFootprintFeaturesNVidia ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", imageFootprint = "                                        + ( features.imageFootprint == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceShaderIntegerDotProductFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceShaderIntegerDotProductFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", shaderIntegerDotProduct = "                               + ( features.shaderIntegerDotProduct == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_SHADER_INTEGER_FUNCTIONS_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceShaderIntegerFunctionsFeaturesIntel ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceShaderIntegerFunctionsFeaturesIntel ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", shaderIntegerFunctions = "                                + ( features.shaderIntegerFunctions == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceShaderSMBuiltinsFeaturesNVidia ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceShaderSMBuiltinsFeaturesNVidia ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", shaderSMBuiltins = "                                      + ( features.shaderSMBuiltins == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_SUBGROUP_UNIFORM_CONTROL_FLOW_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceShaderSubgroupUniformControlFlowFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceShaderSubgroupUniformControlFlowFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", shaderSubgroupUniformControlFlow = "                      + ( features.shaderSubgroupUniformControlFlow == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_TERMINATE_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceShaderTerminateInvocationFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceShaderTerminateInvocationFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", shaderTerminateInvocation = "                             + ( features.shaderTerminateInvocation == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceShadingRateImageFeaturesNVidia ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceShadingRateImageFeaturesNVidia ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", shadingRateImage = "                                      + ( features.shadingRateImage == VK_TRUE ? "true" : "false" ) +
           ", shadingRateCoarseSampleOrder = "                          + ( features.shadingRateCoarseSampleOrder == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceSubgroupSizeControlFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceSubgroupSizeControlFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", subgroupSizeControl = "                                   + ( features.subgroupSizeControl == VK_TRUE ? "true" : "false" ) +
           ", computeFullSubgroups = "                                  + ( features.computeFullSubgroups == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceSubpassShadingFeaturesHuawei ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceSubpassShadingFeaturesHuawei ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", subpassShading = "                                        + ( features.subpassShading == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceSynchronizationFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceSynchronizationFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", synchronization = "                                       + ( features.synchronization == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceTexelBufferAlignmentFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceTexelBufferAlignmentFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", texelBufferAlignment = "                                  + ( features.texelBufferAlignment == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXTURE_COMPRESSION_ASTC_HDR_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceTextureCompressionASTCHDRFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceTextureCompressionASTCHDRFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", textureCompressionASTCHDR = "                             + ( features.textureCompressionASTCHDR == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceTransformFeedbackFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceTransformFeedbackFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", transformFeedback = "                                     + ( features.transformFeedback == VK_TRUE ? "true" : "false" ) +
           ", geometryStreams = "                                       + ( features.geometryStreams == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceVertexAttributeDivisorFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceVertexAttributeDivisorFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", vertexAttributeInstanceRateDivisor = "                    + ( features.vertexAttributeInstanceRateDivisor == VK_TRUE ? "true" : "false" ) +
           ", vertexAttributeInstanceRateZeroDivisor = "                + ( features.vertexAttributeInstanceRateZeroDivisor == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_INPUT_DYNAMIC_STATE_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceVertexInputDynamicStateFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceVertexInputDynamicStateFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", vertexInputDynamicState = "                               + ( features.vertexInputDynamicState == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceWorkgroupMemoryExplicitLayoutFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceWorkgroupMemoryExplicitLayoutFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", workgroupMemoryExplicitLayout = "                         + ( features.workgroupMemoryExplicitLayout == VK_TRUE ? "true" : "false" ) +
           ", workgroupMemoryExplicitLayoutScalarBlockLayout = "        + ( features.workgroupMemoryExplicitLayoutScalarBlockLayout == VK_TRUE ? "true" : "false" ) +
           ", workgroupMemoryExplicitLayout8BitAccess = "               + ( features.workgroupMemoryExplicitLayout8BitAccess == VK_TRUE ? "true" : "false" ) +
           ", workgroupMemoryExplicitLayout16BitAccess = "              + ( features.workgroupMemoryExplicitLayout16BitAccess == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_2_PLANE_444_FORMATS_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceYCBCR2Plane444FormatsFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceYCBCR2Plane444FormatsFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", YCBCR2Plane444Formats = "                                 + ( features.YCBCR2Plane444Formats == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_IMAGE_ARRAYS_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceYCBCRImageArraysFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceYCBCRImageArraysFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", YCBCRImageArrays = "                                      + ( features.YCBCRImageArrays == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ZERO_INITIALIZE_WORKGROUP_MEMORY_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceZeroInitializeWorkgroupMemoryFeatures ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceZeroInitializeWorkgroupMemoryFeatures ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", shaderZeroInitializeWorkgroupMemory = "                   + ( features.shaderZeroInitializeWorkgroupMemory == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( ObjectType ) objectType
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( objectType ) {

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

        case ObjectTypeSamplerYCBCRConversion:         { asString = "VkSamplerYcbcrConversion";         break; }
        case ObjectTypeDescriptorUpdateTemplate:       { asString = "VkDescriptorUpdateTemplate";       break; }
        case ObjectTypePrivateDataSlot:                { asString = "VkPrivateDataSlot";                break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE

        case ObjectTypeSurface:                        { asString = "VkSurfaceKHR";                     break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE

        case ObjectTypeSwapchain:                      { asString = "VkSwapchainKHR";                   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DISPLAY_AVAILABLE

        case ObjectTypeDisplay:                        { asString = "VkDisplayKHR";                     break; }
        case ObjectTypeDisplayMode:                    { asString = "VkDisplayModeKHR";                 break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_REPORT_AVAILABLE

        case ObjectTypeDebugReportCallback:            { asString = "VkDebugReportCallbackEXT";         break; }

#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE

        case ObjectTypeVideoSession:                   { asString = "VkVideoSessionKHR";                break; }
        case ObjectTypeVideoSessionParameters:         { asString = "VkVideoSessionParametersKHR";      break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_BINARY_IMPORT_AVAILABLE

        case ObjectTypeCUModuleNVidia:                 { asString = "VkCuModuleNVX";                    break; }
        case ObjectTypeCUFunctionNVidia:               { asString = "VkCuFunctionNVX";                  break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_UTILS_AVAILABLE

        case ObjectTypeDebugUtilsMessenger:            { asString = "VkDebugUtilsMessengerEXT";         break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE

        case ObjectTypeAccelerationStructure:          { asString = "VkAccelerationStructureKHR";       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_CACHE_AVAILABLE

        case ObjectTypeValidationCache:                { asString = "VkValidationCacheEXT";             break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE

        case ObjectTypeAccelerationStructureNVidia:    { asString = "VkAccelerationStructureNV";        break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE

        case ObjectTypePerformanceConfigurationIntel:  { asString = "VkPerformanceConfigurationINTEL";  break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DEFERRED_HOST_OPERATIONS_AVAILABLE

        case ObjectTypeDeferredOperation:              { asString = "VkDeferredOperationKHR";           break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE

        case ObjectTypeIndirectCommandsLayoutNVidia:   { asString = "VkIndirectCommandsLayoutNV";       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_BUFFER_COLLECTION_AVAILABLE

        case ObjectTypeBufferCollectionGoogle:         { asString = "VkBufferCollectionFUCHSIA";        break; }

#endif

        case ObjectTypeUnknown:                        { asString = "Unknown/Undefined Handle";         break; }
        case ObjectTypeInstance:                       { asString = "VkInstance";                       break; }
        case ObjectTypePhysicalDevice:                 { asString = "VkPhysicalDevice";                 break; }
        case ObjectTypeDevice:                         { asString = "VkDevice";                         break; }
        case ObjectTypeQueue:                          { asString = "VkQueue";                          break; }
        case ObjectTypeSemaphore:                      { asString = "VkSemaphore";                      break; }
        case ObjectTypeCommandBuffer:                  { asString = "VkCommandBuffer";                  break; }
        case ObjectTypeFence:                          { asString = "VkFence";                          break; }
        case ObjectTypeDeviceMemory:                   { asString = "VkDeviceMemory";                   break; }
        case ObjectTypeBuffer:                         { asString = "VkBuffer";                         break; }
        case ObjectTypeImage:                          { asString = "VkImage";                          break; }
        case ObjectTypeEvent:                          { asString = "VkEvent";                          break; }
        case ObjectTypeQueryPool:                      { asString = "VkQueryPool";                      break; }
        case ObjectTypeBufferView:                     { asString = "VkBufferView";                     break; }
        case ObjectTypeImageView:                      { asString = "VkImageView";                      break; }
        case ObjectTypeShaderModule:                   { asString = "VkShaderModule";                   break; }
        case ObjectTypePipelineCache:                  { asString = "VkPipelineCache";                  break; }
        case ObjectTypePipelineLayout:                 { asString = "VkPipelineLayout";                 break; }
        case ObjectTypeRenderPass:                     { asString = "VkRenderPass";                     break; }
        case ObjectTypePipeline:                       { asString = "VkPipeline";                       break; }
        case ObjectTypeDescriptorSetLayout:            { asString = "VkDescriptorSetLayout";            break; }
        case ObjectTypeSampler:                        { asString = "VkSampler";                        break; }
        case ObjectTypeDescriptorPool:                 { asString = "VkDescriptorPool";                 break; }
        case ObjectTypeDescriptorSet:                  { asString = "VkDescriptorSet";                  break; }
        case ObjectTypeFrameBuffer:                    { asString = "VkFramebuffer";                    break; }
        case ObjectTypeCommandPool:                    { asString = "VkCommandPool";                    break; }
    }

    return asString;
}

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceVulkan13Properties ) const & properties
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceVulkan13Properties ) ) " "
           "{ type = "_s                                                                        + toString ( properties.structureType ) +
           ", pNext = "                                                                         + :: toString ( properties.pNext ) +
           ", minSubgroupSize = "                                                               + properties.minSubgroupSize +
           ", maxSubgroupSize = "                                                               + properties.maxSubgroupSize +
           ", maxComputeWorkgroupSubgroups = "                                                  + properties.maxComputeWorkgroupSubgroups +
           ", requiredSubgroupSizeStages = "                                                    + :: flagsToString < Type ( ShaderStageFlag ) > ( properties.requiredSubgroupSizeStages ) +
           ", maxInlineUniformBlockSize = "                                                     + properties.maxInlineUniformBlockSize +
           ", maxPerStageDescriptorInlineUniformBlocks = "                                      + properties.maxPerStageDescriptorInlineUniformBlocks +
           ", maxPerStageDescriptorUpdateAfterBindInlineUniformBlocks = "                       + properties.maxPerStageDescriptorUpdateAfterBindInlineUniformBlocks +
           ", maxDescriptorSetInlineUniformBlocks = "                                           + properties.maxDescriptorSetInlineUniformBlocks +
           ", maxDescriptorSetUpdateAfterBindInlineUniformBlocks = "                            + properties.maxDescriptorSetUpdateAfterBindInlineUniformBlocks +
           ", maxInlineUniformTotalSize = "                                                     + properties.maxInlineUniformTotalSize +
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
           ", storageTexelBufferOffsetAlignmentBytes = "                                        + :: toString ( properties.storageTexelBufferOffsetAlignmentBytes ) +
           ", storageTexelBufferOffsetSingleTexelAlignment = "                                  + ( properties.storageTexelBufferOffsetSingleTexelAlignment == VK_TRUE ? "true" : "false" ) +
           ", uniformTexelBufferOffsetAlignmentBytes = "                                        + :: toString ( properties.uniformTexelBufferOffsetAlignmentBytes ) +
           ", uniformTexelBufferOffsetSingleTexelAlignment = "                                  + ( properties.uniformTexelBufferOffsetSingleTexelAlignment == VK_TRUE ? "true" : "false" ) +
           ", maxBufferSize = "                                                                 + :: toString ( properties.maxBufferSize ) +
           " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceVulkan13Features ) const & features
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalDeviceVulkan13Features ) ) " "
           "{ type = "_s                                                + toString ( features.structureType ) +
           ", pNext = "                                                 + :: toString ( features.pNext ) +
           ", robustImageAccess = "                                     + ( features.robustImageAccess == VK_TRUE ? "true" : "false" ) +
           ", inlineUniformBlock = "                                    + ( features.inlineUniformBlock == VK_TRUE ? "true" : "false" ) +
           ", descriptorBindingInlineUniformBlockUpdateAfterBind = "    + ( features.descriptorBindingInlineUniformBlockUpdateAfterBind == VK_TRUE ? "true" : "false" ) +
           ", pipelineCreationCacheControl = "                          + ( features.pipelineCreationCacheControl == VK_TRUE ? "true" : "false" ) +
           ", privateData = "                                           + ( features.privateData == VK_TRUE ? "true" : "false" ) +
           ", shaderDemoteToHelperInvocation = "                        + ( features.shaderDemoteToHelperInvocation == VK_TRUE ? "true" : "false" ) +
           ", shaderTerminateInvocation = "                             + ( features.shaderTerminateInvocation == VK_TRUE ? "true" : "false" ) +
           ", subgroupSizeControl = "                                   + ( features.subgroupSizeControl == VK_TRUE ? "true" : "false" ) +
           ", computeFullSubgroups = "                                  + ( features.computeFullSubgroups == VK_TRUE ? "true" : "false" ) +
           ", synchronization2 = "                                      + ( features.synchronization2 == VK_TRUE ? "true" : "false" ) +
           ", textureCompressionASTC_HDR = "                            + ( features.textureCompressionASTC_HDR == VK_TRUE ? "true" : "false" ) +
           ", shaderZeroInitializeWorkgroupMemory = "                   + ( features.shaderZeroInitializeWorkgroupMemory == VK_TRUE ? "true" : "false" ) +
           ", dynamicRendering = "                                      + ( features.dynamicRendering == VK_TRUE ? "true" : "false" ) +
           ", shaderIntegerDotProduct = "                               + ( features.shaderIntegerDotProduct == VK_TRUE ? "true" : "false" ) +
           ", maintenance4 = "                                          + ( features.maintenance4 == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( DeviceQueueInfo ) const & info
) noexcept -> cds :: String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( DeviceQueueInfo ) ) " "
            "{ type = "_s           + toString ( info.structureType ) +
            ", pNext = "            + :: toString ( info.pNext ) +
            ", flags = "            + :: flagsToString < Type ( DeviceQueueCreateFlag ) > ( info.flags ) +
            ", queueFamilyIndex = " + info.queueFamilyIndex +
            ", queueIndex = "       + info.queueIndex +
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
) noexcept -> String {
    return String :: f (
            "%d.%d.%d",
            static_cast < sint32 > ( version.major ),
            static_cast < sint32 > ( version.minor ),
            static_cast < sint32 > ( version.patch )
    );
}

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( SurfaceTransformFlag ) flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case SurfaceTransformFlagIdentity:          { asString = "Identity";        break; }
        case SurfaceTransformFlagRotate90:          { asString = "Rotate90";        break; }
        case SurfaceTransformFlagRotate180:         { asString = "Rotate180";       break; }
        case SurfaceTransformFlagRotate270:         { asString = "Rotate270";       break; }
        case SurfaceTransformFlagMirror:            { asString = "Mirror";          break; }
        case SurfaceTransformFlagMirrorRotate90:    { asString = "MirrorRotate90";  break; }
        case SurfaceTransformFlagMirrorRotate180:   { asString = "MirrorRotate180"; break; }
        case SurfaceTransformFlagMirrorRotate270:   { asString = "MirrorRotate270"; break; }
        case SurfaceTransformFlagInherit:           { asString = "Inherit";         break; }
    }

    return asString;
}

auto vulkan :: toString (
        __C_ENG_TYPE ( CompositeAlphaFlag ) flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case CompositeAlphaFlagOpaque:          { asString = "Opaque";          break; }
        case CompositeAlphaFlagPreMultiplied:   { asString = "PreMultiplied";   break; }
        case CompositeAlphaFlagPostMultiplied:  { asString = "PostMultiplied";  break; }
        case CompositeAlphaFlagInherit:         { asString = "Inherit";         break; }
    }

    return asString;
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PresentMode ) mode
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( mode ) {
        case PresentModeImmediate:                  { asString = "Immediate";               break; }
        case PresentModeMailbox:                    { asString = "Mailbox";                 break; }
        case PresentModeFifo:                       { asString = "Fifo";                    break; }
        case PresentModeFifoRelaxed:                { asString = "FifoRelaxed";             break; }
        case PresentModeSharedDemandRefresh:        { asString = "SharedDemandRefresh";     break; }
        case PresentModeSharedContinuousRefresh:    { asString = "SharedContinuousRefresh"; break; }
    }

    return asString;
}

auto vulkan :: toString (
        __C_ENG_TYPE ( SurfaceCapabilities ) const & capabilities
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( SurfaceCapabilities ) ) " "
            "{ minImageCount = "_s          + capabilities.minImageCount +
            ", maxImageCount = "            + capabilities.maxImageCount +
            ", currentExtent = "            + toString ( capabilities.currentExtent ) +
            ", minImageExtent = "           + toString ( capabilities.minImageExtent ) +
            ", maxImageExtent = "           + toString ( capabilities.maxImageExtent ) +
            ", maxImageArrayLayers = "      + toString ( capabilities.maxImageArrayLayers ) +
            ", supportedTransforms = "      + :: flagsToString < Type ( SurfaceTransformFlag ) > ( capabilities.supportedTransforms ) +
            ", currentTransform = "         + toString ( capabilities.currentTransform ) +
            ", supportedCompositeAlpha = "  + :: flagsToString < Type ( CompositeAlphaFlag ) > ( capabilities.supportedCompositeAlpha ) +
            ", supportedUsageFlags = "      + :: flagsToString < Type ( ImageUsageFlag ) > ( capabilities.supportedUsageFlags ) +
            " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( ColorSpace ) colorSpace
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( colorSpace ) {
        case ColorSpaceSRGBNonLinear:                   { asString = "SRGB Non Linear";             break; }

#if __C_ENG_VULKAN_API_EXTENSION_SWAP_CHAIN_COLOR_SPACE_AVAILABLE

        case ColorSpaceDisplayP3NonLinear:              { asString = "Display P3 Non Linear";       break; }
        case ColorSpaceExtendedSRGBLinear:              { asString = "Extended SRGB Linear";        break; }
        case ColorSpaceDisplayP3Linear:                 { asString = "Display P3 Linear";           break; }
        case ColorSpaceDCIP3NonLinear:                  { asString = "DCI P3 Non Linear";           break; }
        case ColorSpaceBT709Linear:                     { asString = "BT 709 Linear";               break; }
        case ColorSpaceBT709NonLinear:                  { asString = "BT 709 Non Linear";           break; }
        case ColorSpaceBT2020Linear:                    { asString = "BT 2020 Linear";              break; }
        case ColorSpaceHDR10ST2084:                     { asString = "HDR 10 ST 2084";              break; }
        case ColorSpaceDolbyVision:                     { asString = "Dolby Vision";                break; }
        case ColorSpaceHDR10HLG:                        { asString = "HDR 10 HLG";                  break; }
        case ColorSpaceAdobeRGBLinear:                  { asString = "Adobe RGB Linear";            break; }
        case ColorSpaceAdobeRGBNonLinear:               { asString = "Adobe RGB Non Linear";        break; }
        case ColorSpacePassThrough:                     { asString = "Pass Through";                break; }
        case ColorSpaceExtendedSRGBNonLinear:           { asString = "Extended SRGB Non Linear";    break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_DISPLAY_NATIVE_HDR_AVAILABLE

        case ColorSpaceDisplayNativeAMD:                { asString = "Display Native AMD";          break; }

#endif

    }

    return asString;
}

auto vulkan :: toString (
        __C_ENG_TYPE ( SurfaceFormat ) const & format
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( SurfaceFormat ) ) " "
            "{ format = "_s     + toString ( format.format ) +
            ", colorSpace = "   + toString ( format.colorSpace ) +
            " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISPLAY_SURFACE_COUNTER_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( SurfaceCounterFlag ) flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case SurfaceCounterFlagVBlank:  { asString = "VBlank";  break; }
    }

    return asString;
}

auto vulkan :: toString (
        __C_ENG_TYPE ( SurfaceCapabilities2 ) const & capabilities
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( SurfaceCapabilities2 ) ) " "
           "{ structureType = "_s          + toString ( capabilities.structureType ) +
           ", pNext = "                    + :: toString ( capabilities.pNext ) +
           ", minImageCount = "            + capabilities.minImageCount +
           ", maxImageCount = "            + capabilities.maxImageCount +
           ", currentExtent = "            + toString ( capabilities.currentExtent ) +
           ", minImageExtent = "           + toString ( capabilities.minImageExtent ) +
           ", maxImageExtent = "           + toString ( capabilities.maxImageExtent ) +
           ", maxImageArrayLayers = "      + toString ( capabilities.maxImageArrayLayers ) +
           ", supportedTransforms = "      + :: flagsToString < Type ( SurfaceTransformFlag ) > ( capabilities.supportedTransforms ) +
           ", currentTransform = "         + toString ( capabilities.currentTransform ) +
           ", supportedCompositeAlpha = "  + :: flagsToString < Type ( CompositeAlphaFlag ) > ( capabilities.supportedCompositeAlpha ) +
           ", supportedUsageFlags = "      + :: flagsToString < Type ( ImageUsageFlag ) > ( capabilities.supportedUsageFlags ) +
           ", supportedSurfaceCounters = " + :: flagsToString < Type ( SurfaceCounterFlag ) > ( capabilities.supportedSurfaceCounters ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( Format ) format
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( format ) {
        case FormatUndefined:                                   { asString = "Unspecified Format";                                                                                      break; }
        case Format_R4_G4_UNorm_Pack8:                          { asString = "[[7..4]r[3..0]g]:u,n";                                                                                    break; }
        case Format_R4_G4_B4_A4_UNorm_Pack16:                   { asString = "[[15..12]r[11..8]g[7..4]b[3..0]a]:u,n";                                                                   break; }
        case Format_B4_G4_R4_A4_UNorm_Pack16:                   { asString = "[[15..12]b[11..8]g[7..4]r[3..0]a]:u,n";                                                                   break; }
        case Format_R5_G6_B5_UNorm_Pack16:                      { asString = "[[15..11]r[10..5]g[4..0]b]:u,n";                                                                          break; }
        case Format_B5_G6_R5_UNorm_Pack16:                      { asString = "[[15..11]b[10..5]g[4..0]r]:u,n";                                                                          break; }
        case Format_R5_G5_B5_A1_UNorm_Pack16:                   { asString = "[[15..11]r[10..6]g[5..1]b[0]a]:u,n";                                                                      break; }
        case Format_B5_G5_R5_A1_UNorm_Pack16:                   { asString = "[[15..11]b[10..6]g[5..1]r[0]a]:u,n";                                                                      break; }
        case Format_A1_R5_G5_B5_UNorm_Pack16:                   { asString = "[[15]a[14..10]r[9..5]g[4..0]b]:u,n";                                                                      break; }
        case Format_R8_UNorm:                                   { asString = "[[7..0]r]:u,n";                                                                                           break; }
        case Format_R8_SNorm:                                   { asString = "[[7..0]r]:s,n";                                                                                           break; }
        case Format_R8_UScaled:                                 { asString = "[[7..0]r]:u,s";                                                                                           break; }
        case Format_R8_SScaled:                                 { asString = "[[7..0]r]:s,s";                                                                                           break; }
        case Format_R8_UInt:                                    { asString = "[[7..0]r]:u,i";                                                                                           break; }
        case Format_R8_SInt:                                    { asString = "[[7..0]r]:s,i";                                                                                           break; }
        case Format_R8_SRGB:                                    { asString = "[[7..0]r]:sRGBnl";                                                                                        break; }
        case Format_R8_G8_UNorm:                                { asString = "[[15..8]r[7..0]g]:u,n";                                                                                   break; }
        case Format_R8_G8_SNorm:                                { asString = "[[15..8]r[7..0]g]:s,n";                                                                                   break; }
        case Format_R8_G8_UScaled:                              { asString = "[[15..8]r[7..0]g]:u,s";                                                                                   break; }
        case Format_R8_G8_SScaled:                              { asString = "[[15..8]r[7..0]g]:s,s";                                                                                   break; }
        case Format_R8_G8_UInt:                                 { asString = "[[15..8]r[7..0]g]:u,i";                                                                                   break; }
        case Format_R8_G8_SInt:                                 { asString = "[[15..8]r[7..0]g]:s,i";                                                                                   break; }
        case Format_R8_G8_SRGB:                                 { asString = "[[15..8]r[7..0]g]:sRGBnl";                                                                                break; }
        case Format_R8_G8_B8_UNorm:                             { asString = "[[23..16]r[15..8]g[7..0]b]:u,n";                                                                          break; }
        case Format_R8_G8_B8_SNorm:                             { asString = "[[23..16]r[15..8]g[7..0]b]:s,n";                                                                          break; }
        case Format_R8_G8_B8_UScaled:                           { asString = "[[23..16]r[15..8]g[7..0]b]:u,s";                                                                          break; }
        case Format_R8_G8_B8_SScaled:                           { asString = "[[23..16]r[15..8]g[7..0]b]:s,s";                                                                          break; }
        case Format_R8_G8_B8_UInt:                              { asString = "[[23..16]r[15..8]g[7..0]b]:u,i";                                                                          break; }
        case Format_R8_G8_B8_SInt:                              { asString = "[[23..16]r[15..8]g[7..0]b]:s,i";                                                                          break; }
        case Format_R8_G8_B8_SRGB:                              { asString = "[[23..16]r[15..8]g[7..0]b]:sRGBnl";                                                                       break; }
        case Format_B8_G8_R8_UNorm:                             { asString = "[[23..16]b[15..8]g[7..0]r]:u,n";                                                                          break; }
        case Format_B8_G8_R8_SNorm:                             { asString = "[[23..16]b[15..8]g[7..0]r]:s,n";                                                                          break; }
        case Format_B8_G8_R8_UScaled:                           { asString = "[[23..16]b[15..8]g[7..0]r]:u,s";                                                                          break; }
        case Format_B8_G8_R8_SScaled:                           { asString = "[[23..16]b[15..8]g[7..0]r]:s,s";                                                                          break; }
        case Format_B8_G8_R8_UInt:                              { asString = "[[23..16]b[15..8]g[7..0]r]:u,i";                                                                          break; }
        case Format_B8_G8_R8_SInt:                              { asString = "[[23..16]b[15..8]g[7..0]r]:s,i";                                                                          break; }
        case Format_B8_G8_R8_SRGB:                              { asString = "[[23..16]b[15..8]g[7..0]r]:sRGBnl";                                                                       break; }
        case Format_R8_G8_B8_A8_UNorm:                          { asString = "[[31..24]r[23..16]g[16..8]b[7..0]a]:u,n";                                                                 break; }
        case Format_R8_G8_B8_A8_SNorm:                          { asString = "[[31..24]r[23..16]g[16..8]b[7..0]a]:s,n";                                                                 break; }
        case Format_R8_G8_B8_A8_UScaled:                        { asString = "[[31..24]r[23..16]g[16..8]b[7..0]a]:u,s";                                                                 break; }
        case Format_R8_G8_B8_A8_SScaled:                        { asString = "[[31..24]r[23..16]g[16..8]b[7..0]a]:s,s";                                                                 break; }
        case Format_R8_G8_B8_A8_UInt:                           { asString = "[[31..24]r[23..16]g[16..8]b[7..0]a]:u,i";                                                                 break; }
        case Format_R8_G8_B8_A8_SInt:                           { asString = "[[31..24]r[23..16]g[16..8]b[7..0]a]:s,i";                                                                 break; }
        case Format_R8_G8_B8_A8_SRGB:                           { asString = "[[31..24]r[23..16]g[16..8]b[7..0]a]:sRGBnl";                                                              break; }
        case Format_B8_G8_R8_A8_UNorm:                          { asString = "[[31..24]b[23..16]g[16..8]r[7..0]a]:u,n";                                                                 break; }
        case Format_B8_G8_R8_A8_SNorm:                          { asString = "[[31..24]b[23..16]g[16..8]r[7..0]a]:s,n";                                                                 break; }
        case Format_B8_G8_R8_A8_UScaled:                        { asString = "[[31..24]b[23..16]g[16..8]r[7..0]a]:u,s";                                                                 break; }
        case Format_B8_G8_R8_A8_SScaled:                        { asString = "[[31..24]b[23..16]g[16..8]r[7..0]a]:s,s";                                                                 break; }
        case Format_B8_G8_R8_A8_UInt:                           { asString = "[[31..24]b[23..16]g[16..8]r[7..0]a]:u,i";                                                                 break; }
        case Format_B8_G8_R8_A8_SInt:                           { asString = "[[31..24]b[23..16]g[16..8]r[7..0]a]:s,i";                                                                 break; }
        case Format_B8_G8_R8_A8_SRGB:                           { asString = "[[31..24]b[23..16]g[16..8]r[7..0]a]:sRGBnl";                                                              break; }
        case Format_A8_B8_G8_R8_UNorm_Pack32:                   { asString = "[[31..24]a[23..16]b[16..8]g[7..0]r]:u,n";                                                                 break; }
        case Format_A8_B8_G8_R8_SNorm_Pack32:                   { asString = "[[31..24]a[23..16]b[16..8]g[7..0]r]:s,n";                                                                 break; }
        case Format_A8_B8_G8_R8_UScaled_Pack32:                 { asString = "[[31..24]a[23..16]b[16..8]g[7..0]r]:u,s";                                                                 break; }
        case Format_A8_B8_G8_R8_SScaled_Pack32:                 { asString = "[[31..24]a[23..16]b[16..8]g[7..0]r]:s,s";                                                                 break; }
        case Format_A8_B8_G8_R8_UInt_Pack32:                    { asString = "[[31..24]a[23..16]b[16..8]g[7..0]r]:u,i";                                                                 break; }
        case Format_A8_B8_G8_R8_SInt_Pack32:                    { asString = "[[31..24]a[23..16]b[16..8]g[7..0]r]:s,i";                                                                 break; }
        case Format_A8_B8_G8_R8_SRGB_Pack32:                    { asString = "[[31..24]a[23..16]b[16..8]g[7..0]r]:sRGBnl";                                                              break; }
        case Format_A2_R10_G10_B10_UNorm_Pack32:                { asString = "[[31..30]a[29..20]r[19..10]g[9..0]b]:u,n";                                                                break; }
        case Format_A2_R10_G10_B10_SNorm_Pack32:                { asString = "[[31..30]a[29..20]r[19..10]g[9..0]b]:s,n";                                                                break; }
        case Format_A2_R10_G10_B10_UScaled_Pack32:              { asString = "[[31..30]a[29..20]r[19..10]g[9..0]b]:u,s";                                                                break; }
        case Format_A2_R10_G10_B10_SScaled_Pack32:              { asString = "[[31..30]a[29..20]r[19..10]g[9..0]b]:s,s";                                                                break; }
        case Format_A2_R10_G10_B10_UInt_Pack32:                 { asString = "[[31..30]a[29..20]r[19..10]g[9..0]b]:u,i";                                                                break; }
        case Format_A2_R10_G10_B10_SInt_Pack32:                 { asString = "[[31..30]a[29..20]r[19..10]g[9..0]b]:s,i";                                                                break; }
        case Format_A2_B10_G10_R10_UNorm_Pack32:                { asString = "[[31..30]a[29..20]b[19..10]g[9..0]r]:u,n";                                                                break; }
        case Format_A2_B10_G10_R10_SNorm_Pack32:                { asString = "[[31..30]a[29..20]b[19..10]g[9..0]r]:s,n";                                                                break; }
        case Format_A2_B10_G10_R10_UScaled_Pack32:              { asString = "[[31..30]a[29..20]b[19..10]g[9..0]r]:u,s";                                                                break; }
        case Format_A2_B10_G10_R10_SScaled_Pack32:              { asString = "[[31..30]a[29..20]b[19..10]g[9..0]r]:s,s";                                                                break; }
        case Format_A2_B10_G10_R10_UInt_Pack32:                 { asString = "[[31..30]a[29..20]b[19..10]g[9..0]r]:u,i";                                                                break; }
        case Format_A2_B10_G10_R10_SInt_Pack32:                 { asString = "[[31..30]a[29..20]b[19..10]g[9..0]r]:s,i";                                                                break; }
        case Format_R16_UNorm:                                  { asString = "[[15..0]r]:u,n";                                                                                          break; }
        case Format_R16_SNorm:                                  { asString = "[[15..0]r]:s,n";                                                                                          break; }
        case Format_R16_UScaled:                                { asString = "[[15..0]r]:u,s";                                                                                          break; }
        case Format_R16_SScaled:                                { asString = "[[15..0]r]:s,s";                                                                                          break; }
        case Format_R16_UInt:                                   { asString = "[[15..0]r]:u,i";                                                                                          break; }
        case Format_R16_SInt:                                   { asString = "[[15..0]r]:s,i";                                                                                          break; }
        case Format_R16_SFloat:                                 { asString = "[[15..0]r]:s,f";                                                                                          break; }
        case Format_R16_G16_UNorm:                              { asString = "[[31..16]r[15..0]g]:u,n";                                                                                 break; }
        case Format_R16_G16_SNorm:                              { asString = "[[31..16]r[15..0]g]:s,n";                                                                                 break; }
        case Format_R16_G16_UScaled:                            { asString = "[[31..16]r[15..0]g]:u,s";                                                                                 break; }
        case Format_R16_G16_SScaled:                            { asString = "[[31..16]r[15..0]g]:s,s";                                                                                 break; }
        case Format_R16_G16_UInt:                               { asString = "[[31..16]r[15..0]g]:u,i";                                                                                 break; }
        case Format_R16_G16_SInt:                               { asString = "[[31..16]r[15..0]g]:s,i";                                                                                 break; }
        case Format_R16_G16_SFloat:                             { asString = "[[31..16]r[15..0]g]:s,f";                                                                                 break; }
        case Format_R16_G16_B16_UNorm:                          { asString = "[[47..32]r[31..16]g[15..0]b]:u,n";                                                                        break; }
        case Format_R16_G16_B16_SNorm:                          { asString = "[[47..32]r[31..16]g[15..0]b]:s,n";                                                                        break; }
        case Format_R16_G16_B16_UScaled:                        { asString = "[[47..32]r[31..16]g[15..0]b]:u,s";                                                                        break; }
        case Format_R16_G16_B16_SScaled:                        { asString = "[[47..32]r[31..16]g[15..0]b]:s,s";                                                                        break; }
        case Format_R16_G16_B16_UInt:                           { asString = "[[47..32]r[31..16]g[15..0]b]:u,i";                                                                        break; }
        case Format_R16_G16_B16_SInt:                           { asString = "[[47..32]r[31..16]g[15..0]b]:s,i";                                                                        break; }
        case Format_R16_G16_B16_SFloat:                         { asString = "[[47..32]r[31..16]g[15..0]b]:s,f";                                                                        break; }
        case Format_R16_G16_B16_A16_UNorm:                      { asString = "[[63..48]r[47..32]g[31..16]b[15..0]a]:u,n";                                                               break; }
        case Format_R16_G16_B16_A16_SNorm:                      { asString = "[[63..48]r[47..32]g[31..16]b[15..0]a]:s,n";                                                               break; }
        case Format_R16_G16_B16_A16_UScaled:                    { asString = "[[63..48]r[47..32]g[31..16]b[15..0]a]:u,s";                                                               break; }
        case Format_R16_G16_B16_A16_SScaled:                    { asString = "[[63..48]r[47..32]g[31..16]b[15..0]a]:s,s";                                                               break; }
        case Format_R16_G16_B16_A16_UInt:                       { asString = "[[63..48]r[47..32]g[31..16]b[15..0]a]:u,i";                                                               break; }
        case Format_R16_G16_B16_A16_SInt:                       { asString = "[[63..48]r[47..32]g[31..16]b[15..0]a]:s,i";                                                               break; }
        case Format_R16_G16_B16_A16_SFloat:                     { asString = "[[63..48]r[47..32]g[31..16]b[15..0]a]:s,f";                                                               break; }
        case Format_R32_UInt:                                   { asString = "[[31..0]r]:u,i";                                                                                          break; }
        case Format_R32_SInt:                                   { asString = "[[31..0]r]:s,i";                                                                                          break; }
        case Format_R32_SFloat:                                 { asString = "[[31..0]r]:s,f";                                                                                          break; }
        case Format_R32_G32_UInt:                               { asString = "[[63..32]r[31..0]b]:u,i";                                                                                 break; }
        case Format_R32_G32_SInt:                               { asString = "[[63..32]r[31..0]b]:s,i";                                                                                 break; }
        case Format_R32_G32_SFloat:                             { asString = "[[63..32]r[31..0]b]:s,f";                                                                                 break; }
        case Format_R32_G32_B32_UInt:                           { asString = "[[95..64]r[63..32]g[31..0]b]:u,i";                                                                        break; }
        case Format_R32_G32_B32_SInt:                           { asString = "[[95..64]r[63..32]g[31..0]b]:s,i";                                                                        break; }
        case Format_R32_G32_B32_SFloat:                         { asString = "[[95..64]r[63..32]g[31..0]b]:s,f";                                                                        break; }
        case Format_R32_G32_B32_A32_UInt:                       { asString = "[[127..96]r[95..64]g[63..32]b[31..0]a]:u,i";                                                              break; }
        case Format_R32_G32_B32_A32_SInt:                       { asString = "[[127..96]r[95..64]g[63..32]b[31..0]a]:s,i";                                                              break; }
        case Format_R32_G32_B32_A32_SFloat:                     { asString = "[[127..96]r[95..64]g[63..32]b[31..0]a]:s,f";                                                              break; }
        case Format_R64_UInt:                                   { asString = "[[63..0]r]:u,i";                                                                                          break; }
        case Format_R64_SInt:                                   { asString = "[[63..0]r]:s,i";                                                                                          break; }
        case Format_R64_SFloat:                                 { asString = "[[63..0]r]:s,f";                                                                                          break; }
        case Format_R64_G64_UInt:                               { asString = "[[127..64]r[63..0]b]:u,i";                                                                                break; }
        case Format_R64_G64_SInt:                               { asString = "[[127..64]r[63..0]b]:s,i";                                                                                break; }
        case Format_R64_G64_SFloat:                             { asString = "[[127..64]r[63..0]b]:s,f";                                                                                break; }
        case Format_R64_G64_B64_UInt:                           { asString = "[[191..128]r[127..64]g[63..0]b]:u,i";                                                                     break; }
        case Format_R64_G64_B64_SInt:                           { asString = "[[191..128]r[127..64]g[63..0]b]:s,i";                                                                     break; }
        case Format_R64_G64_B64_SFloat:                         { asString = "[[191..128]r[127..64]g[63..0]b]:s,f";                                                                     break; }
        case Format_R64_G64_B64_A64_UInt:                       { asString = "[[255..192]r[191..128]g[127..64]b[63..0]a]:u,i";                                                          break; }
        case Format_R64_G64_B64_A64_SInt:                       { asString = "[[255..192]r[191..128]g[127..64]b[63..0]a]:s,i";                                                          break; }
        case Format_R64_G64_B64_A64_SFloat:                     { asString = "[[255..192]r[191..128]g[127..64]b[63..0]a]:s,f";                                                          break; }
        case Format_B10_G11_R11_UFloat_Pack32:                  { asString = "[[31..22]b[21..11]g[10..0]r]:u,f";                                                                        break; } // float10, float11 -> https://www.khronos.org/registry/DataFormat/specs/1.3/dataformat.1.3.html
        case Format_E5_B9_G9_R9_UFloat_Pack32:                  { asString = "[[31..27]<exp>[26..18]b<man>[17..9]g<man>[8..0]r<man>:u,f]";                                              break; } // <exp> is shared exponent for all 3 r,g,b mantisas ( <man> )
        case Format_D16_UNorm:                                  { asString = "[[15..0]depth]:u,n";                                                                                      break; }
        case Format_X8_D24_UNorm_Pack32:                        { asString = "[[31..24]unused[23..0]depth]:u,n";                                                                        break; }
        case Format_D32_SFloat:                                 { asString = "[[31..0]depth]:s,f";                                                                                      break; }
        case Format_S8_UInt:                                    { asString = "[[7..0]stencil]:u,i";                                                                                     break; }
        case Format_D16_UNorm_S8_UInt:                          { asString = "[[23..16]depth:u,n[7..0]stencil:u,i]";                                                                    break; }
        case Format_D24_UNorm_S8_UInt:                          { asString = "[[31..16]depth:u,n[7..0]stencil:u,i]";                                                                    break; }
        case Format_D32_SFloat_S8_UInt:                         { asString = "[[63..40]unused[39..8]depth:s,f[7..0]stencil:u,i]";                                                       break; }
        case Format_BC1_RGB_UNorm_Block:                        { asString = "[[191..128]c1[127..64]c2[63..0]c3]:u,nRGB,4x4,BC,t=(c1,c2,c3)";                                           break; }
        case Format_BC1_RGB_SRGB_Block:                         { asString = "[[191..128]c1[127..64]c2[63..0]c3]:u,sRGBnl,4x4,BC,t=(c1,c2,c3)";                                         break; }
        case Format_BC1_RGBA_UNorm_Block:                       { asString = "[[255..192]c1[191..128]c2[127..64]c3[63..0]c4]:u,nRGBA,4x4,BC,t=(c1,c2,c3,c4)";                           break; }
        case Format_BC1_RGBA_SRGB_Block:                        { asString = "[[255..192]c1[191..128]c2[127..64]c3[63..0]c4]:u,sRGBAnl,4x4,BC,t=(c1,c2,c3,c4)";                         break; }
        case Format_BC2_UNorm_Block:
        case Format_BC3_UNorm_Block:                            { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:u,nRGBA,4x4,BC,t=(c1,c2,c3,c4)";                         break; }
        case Format_BC2_SRGB_Block:
        case Format_BC3_SRGB_Block:                             { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:u,sRGBAnl,4x4,BC,t=(c1,c2,c3,c4)";                       break; }
        case Format_BC4_UNorm_Block:                            { asString = "[[63..0]c]:u,nR,4x4,BC,t=(c)";                                                                            break; }
        case Format_BC4_SNorm_Block:                            { asString = "[[63..0]c]:s,nR,4x4,BC,t=(c)";                                                                            break; }
        case Format_BC5_UNorm_Block:                            { asString = "[[255..128]c1[127..0]c2]:u,nRG,4x4,BC,t=(c1,c2)";                                                         break; }
        case Format_BC5_SNorm_Block:                            { asString = "[[255..128]c1[127..0]c2]:s,nRG,4x4,BC,t=(c1,c2)";                                                         break; }
        case Format_BC6H_UFloat_Block:                          { asString = "[[383..256]c1[255..128]c2[127..0]c3]:u,fRGB,4x4,BC,t=(c1,c2,c3)";                                         break; }
        case Format_BC6H_SFloat_Block:                          { asString = "[[383..256]c1[255..128]c2[127..0]c3]:s,fRGB,4x4,BC,t=(c1,c2,c3)";                                         break; }
        case Format_BC7_UNorm_Block:                            { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:u,nRGBA,4x4,BC,t=(c1,c2,c3,c4)";                         break; }
        case Format_BC7_SRGB_Block:                             { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:s,sRGBAnl,4x4,BC,t=(c1,c2,c3,c4)";                       break; }
        case Format_ETC2_R8_G8_B8_UNorm_Block:                  { asString = "[[191..128]c1[127..64]c2[63..0]c3]:u,nRGB,4x4,ETC2,t=(c1,c2,c3)";                                         break; }
        case Format_ETC2_R8_G8_B8_SRGB_Block:                   { asString = "[[191..128]c1[127..64]c2[63..0]c3]:u,sRGBnl,4x4,ETC2,t=(c1,c2,c3)";                                       break; }
        case Format_ETC2_R8_G8_B8_A1_UNorm_Block:               { asString = "[[255..192]c1[191..128]c2[127..64]c3[63..0]c4]:u,nRGB,4x4,ETC2,t=(c1,c2,c3,c4)";                          break; }
        case Format_ETC2_R8_G8_B8_A1_SRGB_Block:                { asString = "[[255..192]c1[191..128]c2[127..64]c3[63..0]c4]:u,sRGBnl,4x4,ETC2,t=(c1,c2,c3,c4)";                        break; }
        case Format_ETC2_R8_G8_B8_A8_UNorm_Block:               { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:u,nRGB,4x4,ETC2,t=(c1,c2,c3,c4)";                        break; }
        case Format_ETC2_R8_G8_B8_A8_SRGB_Block:                { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:u,sRGBnl,4x4,ETC2,t=(c1,c2,c3,c4)";                      break; }
        case Format_EAC_R11_UNorm_Block:                        { asString = "[[63..0]c1]:u,nR,4x4,ETC2,t=(c1)";                                                                        break; }
        case Format_EAC_R11_SNorm_Block:                        { asString = "[[63..0]c1]:u,sR,4x4,ETC2,t=(c1)";                                                                        break; }
        case Format_EAC_R11_G11_UNorm_Block:                    { asString = "[[127..64]c1[63..0]c2]:u,nRG,4x4,ETC2,t=(c1,c2)";                                                         break; }
        case Format_EAC_R11_G11_SNorm_Block:                    { asString = "[[127..64]c1[63..0]c2]:u,sRG,4x4,ETC2,t=(c1,c2)";                                                         break; }
        case Format_ASTC_4x4_UNorm_Block:                       { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:u,nRGBA,4x4,ASTC,t=(c1,c2,c3,c4)";                       break; }
        case Format_ASTC_4x4_SRGB_Block:                        { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:u,sRGBAnl,4x4,ASTC,t=(c1,c2,c3,c4)";                     break; }
        case Format_ASTC_5x4_UNorm_Block:                       { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:u,nRGBA,5x4,ASTC,t=(c1,c2,c3,c4)";                       break; }
        case Format_ASTC_5x4_SRGB_Block:                        { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:u,sRGBAnl,5x4,ASTC,t=(c1,c2,c3,c4)";                     break; }
        case Format_ASTC_5x5_UNorm_Block:                       { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:u,nRGBA,5x5,ASTC,t=(c1,c2,c3,c4)";                       break; }
        case Format_ASTC_5x5_SRGB_Block:                        { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:u,sRGBAnl,5x5,ASTC,t=(c1,c2,c3,c4)";                     break; }
        case Format_ASTC_6x5_UNorm_Block:                       { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:u,nRGBA,6x5,ASTC,t=(c1,c2,c3,c4)";                       break; }
        case Format_ASTC_6x5_SRGB_Block:                        { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:u,sRGBAnl,6x5,ASTC,t=(c1,c2,c3,c4)";                     break; }
        case Format_ASTC_6x6_UNorm_Block:                       { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:u,nRGBA,6x6,ASTC,t=(c1,c2,c3,c4)";                       break; }
        case Format_ASTC_6x6_SRGB_Block:                        { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:u,sRGBAnl,6x6,ASTC,t=(c1,c2,c3,c4)";                     break; }
        case Format_ASTC_8x5_UNorm_Block:                       { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:u,nRGBA,8x5,ASTC,t=(c1,c2,c3,c4)";                       break; }
        case Format_ASTC_8x5_SRGB_Block:                        { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:u,sRGBAnl,8x5,ASTC,t=(c1,c2,c3,c4)";                     break; }
        case Format_ASTC_8x6_UNorm_Block:                       { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:u,nRGBA,8x6,ASTC,t=(c1,c2,c3,c4)";                       break; }
        case Format_ASTC_8x6_SRGB_Block:                        { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:u,sRGBAnl,8x6,ASTC,t=(c1,c2,c3,c4)";                     break; }
        case Format_ASTC_8x8_UNorm_Block:                       { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:u,nRGBA,8x8,ASTC,t=(c1,c2,c3,c4)";                       break; }
        case Format_ASTC_8x8_SRGB_Block:                        { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:u,sRGBAnl,8x8,ASTC,t=(c1,c2,c3,c4)";                     break; }
        case Format_ASTC_10x5_UNorm_Block:                      { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:u,nRGBA,10x5,ASTC,t=(c1,c2,c3,c4)";                      break; }
        case Format_ASTC_10x5_SRGB_Block:                       { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:u,sRGBAnl,10x5,ASTC,t=(c1,c2,c3,c4)";                    break; }
        case Format_ASTC_10x6_UNorm_Block:                      { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:u,nRGBA,10x6,ASTC,t=(c1,c2,c3,c4)";                      break; }
        case Format_ASTC_10x6_SRGB_Block:                       { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:u,sRGBAnl,10x6,ASTC,t=(c1,c2,c3,c4)";                    break; }
        case Format_ASTC_10x8_UNorm_Block:                      { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:u,nRGBA,10x8,ASTC,t=(c1,c2,c3,c4)";                      break; }
        case Format_ASTC_10x8_SRGB_Block:                       { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:u,sRGBAnl,10x8,ASTC,t=(c1,c2,c3,c4)";                    break; }
        case Format_ASTC_10x10_UNorm_Block:                     { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:u,nRGBA,10x10,ASTC,t=(c1,c2,c3,c4)";                     break; }
        case Format_ASTC_10x10_SRGB_Block:                      { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:u,sRGBAnl,10x10,ASTC,t=(c1,c2,c3,c4)";                   break; }
        case Format_ASTC_12x10_UNorm_Block:                     { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:u,nRGBA,12x10,ASTC,t=(c1,c2,c3,c4)";                     break; }
        case Format_ASTC_12x10_SRGB_Block:                      { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:u,sRGBAnl,12x10,ASTC,t=(c1,c2,c3,c4)";                   break; }
        case Format_ASTC_12x12_UNorm_Block:                     { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:u,nRGBA,12x12,ASTC,t=(c1,c2,c3,c4)";                     break; }
        case Format_ASTC_12x12_SRGB_Block:                      { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:u,sRGBAnl,12x12,ASTC,t=(c1,c2,c3,c4)";                   break; }
        case Format_G8_B8_G8_R8_422_UNorm:                      { asString = "[[31..24]g1[23..16]b[15..8]g2[7..0]r]:u,n,g=(g1,g2)";                                                     break; }
        case Format_B8_G8_R8_G8_G22_UNorm:                      { asString = "[[31..24]b[23..16]g1[15..8]r[7..0]g2]:u,n,g=(g1,g2)";                                                     break; }
        case Format_G8_B8_R8_3Plane_422_UNorm:
        case Format_G8_B8_R8_3Plane_420_UNorm:                  { asString = "[[23..16]g[15..8]b[7..0]r]:u,n,plane0=g,plane1=b,plane2=r";                                               break; }
        case Format_G8_B8_R8_3Plane_444_UNorm:
        case Format_G8_B8R8_2Plane_422_UNorm:
        case Format_G8_B8R8_2Plane_420_UNorm:                   { asString = "[[23..16]g[15..8]b[7..0]r]:u,n,plane0=g,plane1=br";                                                       break; }
        case Format_R10x6_UNorm_Pack16:                         { asString = "[[15..10]unused[9..0]r]:u,n";                                                                             break; }
        case Format_R10x6_G10x6_Unorm_2Pack16:                  { asString = "[[31..26]unused[25..16]r[15..10]unused[9..0]g]:u,n";                                                      break; }
        case Format_R10x6_G10x6_B10x6_A10x6_UNorm_4Pack16:      { asString = "[[63..58]unused[57..48]r[47..42]unused[41..32]g[41..26]unused[25..16]r[15..10]unused[9..0]a]:u,n";        break; }
        case Format_G10x6_B10x6_G10x6_R10x6_422_UNorm_4Pack16:  { asString = "[[63..58]unused[57..48]g[47..42]unused[41..32]b[41..26]unused[25..16]g[15..10]unused[9..0]r]:u,n";        break; }
        case Format_B10x6_G10x6_R10x6_G10x6_422_UNorm_4Pack16:  { asString = "[[63..58]unused[57..48]b[47..42]unused[41..32]g[41..26]unused[25..16]r[15..10]unused[9..0]g]:u,n";        break; }
        case Format_G10x6_B10x6_R10x6_3Plane_444_UNorm_3Pack16:
        case Format_G10x6_B10x6_R10x6_3Plane_422_UNorm_3Pack16:
        case Format_G10x6_B10x6_R10x6_3Plane_420_UNorm_3Pack16: { asString = "[[47..42]unused[41..32]g[41..26]unused[25..16]b[15..10]unused[9..0]r]:u,n,plane0=g,plane1=b,plane3=r";    break; }
#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_2_PLANE_444_FORMATS_AVAILABLE
        case Format_G10x6_B10x6R10x6_2Plane_444_UNorm_3Pack16:
#endif
        case Format_G10x6_B10x6R10x6_2Plane_422_UNorm_3Pack16:
        case Format_G10x6_B10x6R10x6_2Plane_420_UNorm_3Pack16:  { asString = "[[47..42]unused[41..32]g[41..26]unused[25..16]b[15..10]unused[9..0]r]:u,n,plane0=g,plane1=br";            break; }
        case Format_R12x4_UNorm_Pack16:                         { asString = "[[15..12]unused[11..0]r]:u,n";                                                                            break; }
        case Format_R12x4_G12x4_UNorm_2Pack16:                  { asString = "[[31..28]unused[27..16]r[15..12]unused[11..0]g]:u,n";                                                     break; }
        case Format_R12x4_G12x4_B12x4_A12x4_UNorm_4Pack16:      { asString = "[[63..60]unused[59..48]r[47..44]unused[43..32]g[41..28]unused[27..16]r[15..12]unused[10..0]a]:u,n";       break; }
        case Format_G12x4_B12x4_G12x4_R12x4_422_UNorm_4Pack16:  { asString = "[[63..60]unused[59..48]g[47..44]unused[43..32]b[41..28]unused[27..16]g[15..12]unused[10..0]r]:u,n";       break; }
        case Format_B12x4_G12x4_R12x4_G12x4_422_UNorm_4Pack16:  { asString = "[[63..60]unused[59..48]b[47..44]unused[43..32]g[41..28]unused[27..16]r[15..12]unused[10..0]g]:u,n";       break; }
        case Format_G12x4_B12x4_R12x4_3Plane_444_UNorm_3Pack16:
        case Format_G12x4_B12x4_R12x4_3Plane_422_UNorm_3Pack16:
        case Format_G12x4_B12x4_R12x4_3Plane_420_UNorm_3Pack16: { asString = "[[47..44]unused[43..32]g[41..28]unused[27..16]b[15..12]unused[11..0]r]:u,n,plane0=g,plane1=b,plane3=r";   break; }
#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_2_PLANE_444_FORMATS_AVAILABLE
        case Format_G12x4_B12x4R12x4_2Plane_444_UNorm_3Pack16:
#endif
        case Format_G12x4_B12x4R12x4_2Plane_422_UNorm_3Pack16:
        case Format_G12x4_B12x4R12x4_2Plane_420_UNorm_3Pack16:  { asString = "[[47..44]unused[43..32]g[41..28]unused[27..16]b[15..12]unused[11..0]r]:u,n,plane0=g,plane1=br";           break; }
        case Format_G16_B16_G16_R16_422_UNorm:                  { asString = "[[63..48]g[47..32]b[41..16]g[15..0]r]:u,n";                                                               break; }
        case Format_B16_G16_R16_G16_422_UNorm:                  { asString = "[[63..48]b[47..32]g[41..16]r[15..0]g]:u,n";                                                               break; }
        case Format_G16_B16_R16_3Plane_444_UNorm:
        case Format_G16_B16_R16_3Plane_422_UNorm:
        case Format_G16_B16_R16_3Plane_420_UNorm:               { asString = "[[47..32]g[41..16]b[15..0]r]:u,n,plane0=g,plane1=b,plane3=r";                                             break; }
#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_2_PLANE_444_FORMATS_AVAILABLE
        case Format_G16_B16R16_2Plane_444_UNorm:
#endif
        case Format_G16_B16R16_2Plane_422_UNorm:
        case Format_G16_B16R16_2Plane_420_UNorm:                { asString = "[[47..32]g[41..16]b[15..0]r]:u,n,plane0=g,plane1=br";                                                     break; }
#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_2_PLANE_444_FORMATS_AVAILABLE
        case Format_G8_B8R8_2Plane_444_UNorm:                   { asString = "[[23..16]g[15..8]b[7..0]r]:u,n,plane0=g,plane1=br";                                                       break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SAMPLER_YCBCR_CONVERSION_AVAILABLE
        case Format_A4_R4_G4_B4_UNorm_Pack16:                   { asString = "[[15..12]a[11..8]r[7..4]g[3..0]b:u,n]";                                                                   break; }
        case Format_A4_B4_G4_R4_UNorm_Pack16:                   { asString = "[[15..12]a[11..8]b[7..4]g[3..0]r:u,n]";                                                                   break; }
        case Format_ASTC_4x4_SFloat_Block:                      { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:s,fRGBA,4x4,ASTC,t=(c1,c2,c3,c4)";                       break; }
        case Format_ASTC_5x4_SFloat_Block:                      { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:s,fRGBA,5x4,ASTC,t=(c1,c2,c3,c4)";                       break; }
        case Format_ASTC_5x5_SFloat_Block:                      { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:s,fRGBA,5x5,ASTC,t=(c1,c2,c3,c4)";                       break; }
        case Format_ASTC_6x5_SFloat_Block:                      { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:s,fRGBA,6x5,ASTC,t=(c1,c2,c3,c4)";                       break; }
        case Format_ASTC_6x6_SFloat_Block:                      { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:s,fRGBA,6x6,ASTC,t=(c1,c2,c3,c4)";                       break; }
        case Format_ASTC_8x5_SFloat_Block:                      { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:s,fRGBA,8x5,ASTC,t=(c1,c2,c3,c4)";                       break; }
        case Format_ASTC_8x6_SFloat_Block:                      { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:s,fRGBA,8x6,ASTC,t=(c1,c2,c3,c4)";                       break; }
        case Format_ASTC_8x8_SFloat_Block:                      { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:s,fRGBA,8x8,ASTC,t=(c1,c2,c3,c4)";                       break; }
        case Format_ASTC_10x5_SFloat_Block:                     { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:s,fRGBA,10x5,ASTC,t=(c1,c2,c3,c4)";                      break; }
        case Format_ASTC_10x6_SFloat_Block:                     { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:s,fRGBA,10x6,ASTC,t=(c1,c2,c3,c4)";                      break; }
        case Format_ASTC_10x8_SFloat_Block:                     { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:s,fRGBA,10x8,ASTC,t=(c1,c2,c3,c4)";                      break; }
        case Format_ASTC_10x10_SFloat_Block:                    { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:s,fRGBA,10x10,ASTC,t=(c1,c2,c3,c4)";                     break; }
        case Format_ASTC_12x10_SFloat_Block:                    { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:s,fRGBA,12x10,ASTC,t=(c1,c2,c3,c4)";                     break; }
        case Format_ASTC_12x12_SFloat_Block:                    { asString = "[[511..384]c1[383..256]c2[255..128]c3[127..0]c4]:s,fRGBA,12x12,ASTC,t=(c1,c2,c3,c4)";                     break; }
#endif
#if __C_ENG_VULKAN_API_POWER_VR_IMAGE_FORMAT_AVAILABLE
        case Format_PVRTC2_2BPP_UNorm_Block_PowerVR:
        case Format_PVRTC1_2BPP_UNorm_Block_PowerVR:            { asString = "[[255..192]c1[192..128]c2[127..64]c3[63..0]c4]:u,nRGBA,8x4,PVRTC,t=(c1,c2,c3,c4)";                        break; }
        case Format_PVRTC2_4BPP_UNorm_Block_PowerVR:
        case Format_PVRTC1_4BPP_UNorm_Block_PowerVR:            { asString = "[[255..192]c1[192..128]c2[127..64]c3[63..0]c4]:u,nRGBA,4x4,PVRTC,t=(c1,c2,c3,c4)";                        break; }
        case Format_PVRTC1_2BPP_SRGB_Block_PowerVR:
        case Format_PVRTC2_2BPP_SRGB_Block_PowerVR:             { asString = "[[255..192]c1[192..128]c2[127..64]c3[63..0]c4]:u,sRGBAnl,8x4,PVRTC,t=(c1,c2,c3,c4)";                      break; }
        case Format_PVRTC1_4BPP_SRGB_Block_PowerVR:
        case Format_PVRTC2_4BPP_SRGB_Block_PowerVR:             { asString = "[[255..192]c1[192..128]c2[127..64]c3[63..0]c4]:u,sRGBAnl,4x4,PVRTC,t=(c1,c2,c3,c4)";                      break; }
#endif
    }

    return asString;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_GET_SURFACE_CAPABILITIES_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( SurfaceFormat2 ) const & format
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( SurfaceFormat2 ) ) " "
            "{ structureType = "_s      + toString ( format.structureType ) +
            ", pNext = "                + :: toString ( format.pNext ) +
            ", surfaceFormat = "        + toString ( format.surfaceFormat ) +
            " }";
}

auto vulkan :: toString (
        __C_ENG_TYPE ( PhysicalDeviceSurfaceInfo ) const & format
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( PhysicalSurfaceSurfaceInfo ) ) " "
            "{ structureType = "_s      + toString ( format.structureType ) +
            ", pNext = "                + :: toString ( format.pNext ) +
            ", surface = "              + :: toString ( format.surface ) +
            " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FULL_SCREEN_EXCLUSIVE_AVAILABLE

auto vulkan :: toString (
        __C_ENG_TYPE ( FullScreenExclusive )    exclusive
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( exclusive ) {
        case FullScreenExclusiveDefault:                { asString = "Default";                 break; }
        case FullScreenExclusiveAllowed:                { asString = "Allowed";                 break; }
        case FullScreenExclusiveDisallowed:             { asString = "Disallowed";              break; }
        case FullScreenExclusiveApplicationControlled:  { asString = "ApplicationControlled";   break; }
    }

    return asString;
}

auto vulkan :: toString (
        __C_ENG_TYPE ( SurfaceFullScreenExclusiveInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( SurfaceFullScreenExclusiveInfo ) ) " "
            "{ structureType = "_s      + toString ( format.structureType ) +
            ", pNext = "                + :: toString ( format.pNext ) +
            ", fullScreenExclusive = "  + toString ( format.fullScreenExclusive ) +
            " }";
}

#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

auto vulkan :: toString (
        Type ( SharingMode ) sharingMode
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( sharingMode ) {
        case SharingModeExclusive:  { asString = "Exclusive";   break; }
        case SharingModeConcurrent: { asString = "Concurrent";  break; }
    }

    return asString;
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE

auto vulkan :: toString (
        Type ( SwapChainCreateFlag ) flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DEVICE_GROUP_AVAILABLE

        case SwapChainCreateFlagSplitInstanceBindRegions:   { asString = "SplitInstanceBindRegions";    break; }

#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

        case SwapChainCreateFlagProtected:                  { asString = "Protected";                   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_MUTABLE_FORMAT_AVAILABLE

        case SwapChainCreateFlagMutableFormat:              { asString = "MutableFormat";               break; }

#endif

    }

    return asString;
}

auto vulkan :: toString (
        Type ( SwapChainCreateInfo ) const & createInfo
) noexcept -> String {

    auto indicesAsString = [] ( uint32 count, uint32 const * pIndices ) {
        String asString = "[ ";
        for ( uint32 i = 0U; i < count; ++ i ) {
            asString += pIndices[i] + ", "_s;
        }
        return asString.removeSuffix(", ") + " ]";
    };

    return __C_ENG_STRINGIFY ( Type ( SwapChainCreateInfo ) ) " "
            "{ structureType = "_s          + toString ( createInfo.structureType ) +
            ", pNext = "                    + :: toString ( createInfo.pNext ) +
            ", flags = "                    + :: flagsToString < Type ( SwapChainCreateFlag ) > ( createInfo.flags ) +
            ", minImageCount = "            + createInfo.minImageCount +
            ", imageFormat = "              + toString ( createInfo.imageFormat ) +
            ", imageColorSpace = "          + toString ( createInfo.imageColorSpace ) +
            ", imageExtent = "              + toString ( createInfo.imageExtent ) +
            ", imageArrayLayers = "         + createInfo.imageArrayLayers +
            ", imageUsage = "               + :: flagsToString < Type ( ImageUsageFlag ) > ( createInfo.imageUsage ) +
            ", imageSharingMode = "         + toString ( createInfo.imageSharingMode ) +
            ", queueFamilyIndexCount = "    + createInfo.queueFamilyIndexCount +
            ", queueFamilyIndices = "       + indicesAsString ( createInfo.queueFamilyIndexCount, createInfo.pQueueFamilyIndices ) +
            ", preTransform = "             + toString ( createInfo.preTransform ) +
            ", compositeAlpha = "           + toString ( createInfo.compositeAlpha ) +
            ", presentMode = "              + toString ( createInfo.presentMode ) +
            ", clipped = "                  + ( createInfo.clipped == VK_TRUE ? "true" : "false" ) +
            ", oldSwapChain = "             + :: toString ( createInfo.oldSwapChain ) +
            " }";
}

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

auto vulkan :: toString (
        Type ( ImageFormatListCreateInfo ) const & createInfo
) noexcept -> String {

    auto formatsAsString = [] ( uint32 count, Type ( Format ) const * pFormats ) {
        String asString = "[ ";
        for ( uint32 i = 0U; i < count; ++ i ) {
            asString += toString ( pFormats[i] ) + ", "_s;
        }
        return asString.removeSuffix(", ") + " ]";
    };

    return __C_ENG_STRINGIFY ( Type ( ImageFormatListCreateInfo ) ) " "
            "{ structureType = "_s          + toString ( createInfo.structureType ) +
            ", pNext = "                    + :: toString ( createInfo.pNext ) +
            ", viewFormatCount = "          + createInfo.viewFormatCount +
            ", viewFormats = "              + formatsAsString ( createInfo.viewFormatCount, createInfo.pViewFormats ) +
            " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WIN32_SURFACE_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_FULL_SCREEN_EXCLUSIVE_AVAILABLE

auto vulkan :: toString (
        Type ( SurfaceFullScreenExclusiveWin32Info ) const & createInfo
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( SurfaceFullScreenExclusiveWin32Info ) ) " "
            "{ structureType = "_s          + toString ( createInfo.structureType ) +
            ", pNext = "                    + :: toString ( createInfo.pNext ) +
            ", monitorHandle = "            + :: toString ( createInfo.monitorHandle ) +
            " }";
}

#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

auto vulkan :: toString (
        Type ( ImageViewCreateFlag ) flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

        case ImageViewCreateFlagFragmentDensityMapDynamic:  { asString = "DensityMapDynamic";   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE

        case ImageViewCreateFlagFragmentDensityMapDeferred: { asString = "DensityMapDeferred";  break; }

#endif

    }

    return asString;
}

auto vulkan :: toString (
        Type ( ImageViewType ) type
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( type ) {
        case ImageViewType1D:           { asString = "1D";          break; }
        case ImageViewType2D:           { asString = "2D";          break; }
        case ImageViewType3D:           { asString = "3D";          break; }
        case ImageViewTypeCube:         { asString = "Cube";        break; }
        case ImageViewType1DArray:      { asString = "1DArray";     break; }
        case ImageViewType2DArray:      { asString = "2DArray";     break; }
        case ImageViewTypeCubeArray:    { asString = "CubeArray";   break; }
    }

    return asString;
}

auto vulkan :: toString (
        Type ( ComponentSwizzle ) swizzle
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( swizzle ) {
        case ComponentSwizzleIdentity:  { asString = "Identity";    break; }
        case ComponentSwizzleZero:      { asString = "Zero";        break; }
        case ComponentSwizzleOne:       { asString = "One";         break; }
        case ComponentSwizzleR:         { asString = "R";           break; }
        case ComponentSwizzleG:         { asString = "G";           break; }
        case ComponentSwizzleB:         { asString = "B";           break; }
        case ComponentSwizzleA:         { asString = "A";           break; }
    }

    return asString;
}

auto vulkan :: toString (
        Type ( ImageAspectFlag ) flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case ImageAspectFlagColor:          { asString = "Color";           break; }
        case ImageAspectFlagDepth:          { asString = "Depth";           break; }
        case ImageAspectFlagStencil:        { asString = "Stencil";         break; }
        case ImageAspectFlagMetadata:       { asString = "Metadata";        break; }

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

        case ImageAspectFlagPlane0:         { asString = "Plane0";          break; }
        case ImageAspectFlagPlane1:         { asString = "Plane1";          break; }
        case ImageAspectFlagPlane2:         { asString = "Plane2";          break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE

        case ImageAspectFlagNone:           { asString = "None";            break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_DRM_FORMAT_MODIFIER_AVAILABLE

        case ImageAspectFlagMemoryPlane0:   { asString = "MemoryPlane0";    break; }
        case ImageAspectFlagMemoryPlane1:   { asString = "MemoryPlane1";    break; }
        case ImageAspectFlagMemoryPlane2:   { asString = "MemoryPlane2";    break; }
        case ImageAspectFlagMemoryPlane3:   { asString = "MemoryPlane3";    break; }

#endif

    }

    return asString;
}

auto vulkan :: toString (
        Type ( ComponentMapping ) const & mapping
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ComponentMapping ) ) ""
            "{ r = "_s  + toString ( mapping.r ) +
            ", g = "    + toString ( mapping.g ) +
            ", b = "    + toString ( mapping.b ) +
            ", a = "    + toString ( mapping.a ) +
            " }";
}

auto vulkan :: toString (
        Type ( ImageSubresourceRange ) const & range
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ImageSubresourceRange ) ) ""
            "{ aspectMask = "_s     + :: flagsToString < Type ( ImageAspectFlag ) > ( range.aspectMask ) +
            ", baseMipLevel = "     + range.baseMipLevel +
            ", levelCount = "       + range.levelCount +
            ", baseArrayLayer = "   + range.baseArrayLayer +
            ", layerCount = "       + range.layerCount +
            " }";
}

auto vulkan :: toString (
        Type ( ImageViewCreateInfo ) const & createInfo
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ImageViewCreateInfo ) ) ""
            "{ structureType = "_s  + toString ( createInfo.structureType ) +
            ", pNext = "            + :: toString ( createInfo.pNext ) +
            ", flags = "            + :: flagsToString < Type ( ImageViewCreateFlag ) > ( createInfo.flags ) +
            ", image = "            + :: toString ( createInfo.image ) +
            ", viewType = "         + toString ( createInfo.viewType ) +
            ", format = "           + toString ( createInfo.format ) +
            ", components = "       + toString ( createInfo.components ) +
            ", subresourceRange = " + toString ( createInfo.subresourceRange ) +
            " }";
}

#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

auto vulkan :: toString (
        Type ( ImageViewUsageCreateInfo ) const & createInfo
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ImageViewUsageCreateInfo ) ) ""
           "{ structureType = "_s  + toString ( createInfo.structureType ) +
           ", pNext = "            + :: toString ( createInfo.pNext ) +
           ", usage = "            + :: flagsToString < Type ( ImageUsageFlag ) > ( createInfo.usage ) +
           " }";
}

auto vulkan :: toString (
        Type ( SamplerYCBCRConversionInfo ) const & createInfo
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( SamplerYCBCRConversionInfo ) ) ""
           "{ structureType = "_s  + toString ( createInfo.structureType ) +
           ", pNext = "            + :: toString ( createInfo.pNext ) +
           ", conversion = "       + :: toString ( createInfo.conversion ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

auto vulkan :: toString (
        Type ( CommandPoolCreateFlag ) flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case CommandPoolCreateFlagTransient:            { asString = "Transient";           break; }
        case CommandPoolCreateFlagResetCommandBuffer:   { asString = "ResetCommandBuffer";  break; }

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

        case CommandPoolCreateFlagProtected:            { asString = "Protected";           break; }

#endif

    }

    return asString;
}

auto vulkan :: toString (
        Type ( CommandBufferLevel ) flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case CommandBufferLevelPrimary:     { asString = "Primary";     break; }
        case CommandBufferLevelSecondary:   { asString = "Secondary";   break; }
    }

    return asString;
}

auto vulkan :: toString (
        Type ( CommandPoolResetFlag ) flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case CommandPoolResetFlagReleaseResources:  { asString = "ReleaseResources";   break; }
    }

    return asString;
}

auto vulkan :: toString (
        Type ( CommandBufferResetFlag ) flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case CommandBufferResetFlagReleaseResources:  { asString = "ReleaseResources";   break; }
    }

    return asString;
}

auto vulkan :: toString (
        Type ( CommandBufferUsageFlag ) flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case CommandBufferUsageFlagOneTimeSubmit:       { asString = "OneTimeSubmit";       break; }
        case CommandBufferUsageFlagRenderPassContinue:  { asString = "RenderPassSubmit";    break; }
        case CommandBufferUsageFlagSimultaneous:        { asString = "Simultaneous";        break; }
    }

    return asString;
}

auto vulkan :: toString (
        Type ( QueryPipelineStatisticFlag ) flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case QueryPipelineStatisticFlagInputAssemblyVertices:                   { asString = "InputAssemblyVertices";                   break; }
        case QueryPipelineStatisticFlagInputAssemblyPrimitives:                 { asString = "InputAssemblyPrimitives";                 break; }
        case QueryPipelineStatisticFlagVertexShaderInvocations:                 { asString = "VertexShaderInvocations";                 break; }
        case QueryPipelineStatisticFlagGeometryShaderInvocations:               { asString = "GeometryShaderInvocations";               break; }
        case QueryPipelineStatisticFlagGeometryShaderPrimitives:                { asString = "GeometryShaderPrimitives";                break; }
        case QueryPipelineStatisticFlagClippingInvocations:                     { asString = "ClippingInvocations";                     break; }
        case QueryPipelineStatisticFlagClippingPrimitives:                      { asString = "ClippingPrimitives";                      break; }
        case QueryPipelineStatisticFlagFragmentShaderInvocations:               { asString = "FragmentShaderInvocations";               break; }
        case QueryPipelineStatisticFlagTessellationControlShaderPatches:        { asString = "TessellationControlShaderPatches";        break; }
        case QueryPipelineStatisticFlagTessellationEvaluationShaderInvocations: { asString = "TessellationEvaluationShaderInvocations"; break; }
        case QueryPipelineStatisticFlagComputeShaderInvocations:                { asString = "ComputeShaderInvocations";                break; }
    }

    return asString;
}

auto vulkan :: toString (
        Type ( QueryControlFlag ) flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case QueryControlFlagPrecise:   { asString = "Precise"; break; }
    }

    return asString;
}

auto vulkan :: toString (
        Type ( CommandPoolCreateInfo ) const & createInfo
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( CommandPoolCreateInfo ) ) " "
            "{ structureType = "_s  + toString ( createInfo.structureType ) +
            ", pNext = "            + :: toString ( createInfo.pNext ) +
            ", flags = "            + :: flagsToString < Type ( CommandPoolCreateFlag ) > ( createInfo.flags ) +
            ", queueFamilyIndex = " + createInfo.queueFamilyIndex +
            " }";
}

auto vulkan :: toString (
        Type ( CommandBufferAllocateInfo ) const & allocateInfo
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( CommandBufferAllocateInfo ) ) " "
            "{ structureType = "_s      + toString ( allocateInfo.structureType ) +
            ", pNext = "                + :: toString ( allocateInfo.pNext ) +
            ", commandPool = "          + :: toString ( allocateInfo.commandPool ) +
            ", level = "                + toString ( allocateInfo.level ) +
            ", commandBufferCount = "   + allocateInfo.commandBufferCount +
            " }";
}

auto vulkan :: toString (
        Type ( CommandBufferBeginInfo ) const & beginInfo
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( CommandBufferBeginInfo ) ) " "
           "{ structureType = "_s      + toString ( beginInfo.structureType ) +
           ", pNext = "                + :: toString ( beginInfo.pNext ) +
           ", flags = "                + :: flagsToString < Type ( CommandBufferUsageFlag ) > ( beginInfo.flags ) +
           ", pInheritanceInfo = "     + :: toString ( beginInfo.pInheritanceInfo ) +
           " }";
}

auto vulkan :: toString (
        Type ( CommandBufferInheritanceInfo ) const & inheritanceInfo
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( CommandBufferBeginInfo ) ) " "
           "{ structureType = "_s      + toString ( inheritanceInfo.structureType ) +
           ", pNext = "                + :: toString ( inheritanceInfo.pNext ) +
           ", renderPass = "           + :: toString ( inheritanceInfo.renderPass ) +
           ", subpass = "              + inheritanceInfo.subpass +
           ", frameBuffer = "          + :: toString ( inheritanceInfo.frameBuffer ) +
           ", occlusionQueryEnable"    + ( inheritanceInfo.occlusionQueryEnable == VK_TRUE ? "true" : "false" ) +
           ", queryFlags = "           + :: flagsToString < Type ( QueryControlFlag ) > ( inheritanceInfo.queryFlags ) +
           ", pipelineStatistics = "   + :: flagsToString < Type ( QueryPipelineStatisticFlag ) > ( inheritanceInfo.pipelineStatistics ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DEVICE_GROUP_AVAILABLE

auto vulkan :: toString (
        Type ( DeviceGroupCommandBufferBeginInfo ) const & beginInfo
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( DeviceGroupCommandBufferBeginInfo ) ) " "
           "{ structureType = "_s      + toString ( beginInfo.structureType ) +
           ", pNext = "                + :: toString ( beginInfo.pNext ) +
           ", deviceMask = "           + beginInfo.deviceMask +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

auto vulkan :: toString (
        Type ( Viewport ) const & viewport
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( Viewport ) ) " "
            "{ x = "_s      + viewport.x +
            ", y = "        + viewport.y +
            ", width = "    + viewport.width +
            ", height = "   + viewport.height +
            ", minDepth = " + viewport.minDepth +
            ", maxDepth = " + viewport.maxDepth +
            " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

auto vulkan :: toString (
        Type ( RenderingFlag ) flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case RenderingFlagContentsSecondayCommandBuffers:   { asString = "ContentsSecondaryCommandBuffers"; break; }
        case RenderingFlagSuspending:                       { asString = "Suspending";                      break; }
        case RenderingFlagResuming:                         { asString = "Resuming";                        break; }
    }

    return asString;
}

auto vulkan :: toString (
        Type ( CommandBufferInheritanceRenderingInfo ) const & info
) noexcept -> String {

    auto formatsToString = []( uint32 count, Type ( Format ) const * pFormats ) {
        String asString = "[ ";
        for ( uint32 i = 0U; i < count; ++ i ) {
            asString += toString ( pFormats[i] ) + ", "_s;
        }
        return asString.removeSuffix(", ") + " ]";
    };

    return __C_ENG_STRINGIFY ( Type ( CommandBufferInheritanceRenderingInfo ) ) " "
           "{ structureType = "_s                  + toString ( info.structureType ) +
           ", pNext = "                            + :: toString ( info.pNext ) +
           ", flags = "                            + :: flagsToString < Type ( RenderingFlag ) > ( info.flags ) +
           ", viewMask = "                         + info.viewMask +
           ", colorAttachmentCount = "             + info.colorAttachmentCount +
           ", colorAttachments = "                 + formatsToString ( info.colorAttachmentCount, info.pColorAttachmentFormats ) +
           ", depthAttachmentFormat = "            + toString ( info.depthAttachmentFormat ) +
           ", stencilAttachmentFormat = "          + toString ( info.stencilAttachmentFormat ) +
           ", rasterizationSamples = "             + toString ( info.rasterizationSamples ) +
           " }";
}

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAMEBUFFER_MIXED_SAMPLES_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_AMD_MIXED_ATTACHMENT_SAMPLES_AVAILABLE

auto vulkan :: toString (
        hidden :: __AttachmentSampleCountInfo const & info
) noexcept -> String {

    auto attachmentsToString = []( uint32 count, Type ( SampleCountFlag ) const * pAttachments ) {
        String asString = "[ ";
        for ( uint32 i = 0U; i < count; ++ i ) {
            asString += toString ( pAttachments[i] ) + ", "_s;
        }
        return asString.removeSuffix(", ") + " ]";
    };

    return __C_ENG_STRINGIFY ( Type ( AttachmentSampleCountInfo ) ) " "
            "{ structureType = "_s                  + toString ( info.structureType ) +
            ", pNext = "                            + :: toString ( info.pNext ) +
            ", colorAttachmentCount = "             + info.colorAttachmentCount +
            ", colorAttachments = "                 + attachmentsToString ( info.colorAttachmentCount, info.pColorAttachmentSamples ) +
            ", depthStencilAttachmentSamples = "    + toString ( info.depthStencilAttachmentSamples ) +
            " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE

auto vulkan :: toString (
        Type ( MultiviewPerViewAttributesInfoNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( MultiviewPerViewAttributesInfoNVidia ) ) " "
           "{ structureType = "_s                  + toString ( info.structureType ) +
           ", pNext = "                            + :: toString ( info.pNext ) +
           ", perViewAttributes = "                + ( info.perViewAttributes == VK_TRUE ? "true" : "false" ) +
           ", perViewAttributesPositionXOnly = "   + ( info.perViewAttributesPositionXOnly == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE

auto vulkan :: toString (
        Type ( CommandBufferInheritanceConditionalRenderingInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( CommandBufferInheritanceConditionalRenderingInfo ) ) " "
           "{ structureType = "_s                  + toString ( info.structureType ) +
           ", pNext = "                            + :: toString ( info.pNext ) +
           ", conditionalRenderingEnable = "       + ( info.conditionalRenderingEnable == VK_TRUE ? "true" : "false" ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_RENDER_PASS_TRANSFORM_AVAILABLE

auto vulkan :: toString (
        Type ( CommandBufferInheritanceRenderPassTransformInfoQualcomm ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( CommandBufferInheritanceRenderPassTransformInfoQualcomm ) ) " "
           "{ structureType = "_s                  + toString ( info.structureType ) +
           ", pNext = "                            + :: toString ( info.pNext ) +
           ", transform = "                        + toString ( info.transform ) +
           ", renderArea = "                       + toString ( info.renderArea ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE

auto vulkan :: toString (
        Type ( SubmitFlag ) flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case SubmitFlagProtected:   { asString = "Protected";   break; }
    }

    return asString;
}

auto vulkan :: toString (
        Type ( SemaphoreSubmitInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( SemaphoreSubmitInfo ) ) " "
            "{ structureType = "_s          + toString ( info.structureType ) +
            ", pNext = "                    + :: toString ( info.pNext ) +
            ", semaphore = "                + :: toString ( info.semaphore ) +
            ", value = "                    + info.value +
            ", stageMask = "                + :: flagsToString < Type ( PipelineStageFlag ) > ( info.stageMask ) +
            ", deviceIndex = "              + info.deviceIndex +
            " }";
}

auto vulkan :: toString (
        Type ( CommandBufferSubmitInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( CommandBufferSubmitInfo ) ) " "
            "{ structureType = "_s          + toString ( info.structureType ) +
            ", pNext = "                    + :: toString ( info.pNext ) +
            ", commandBuffer = "            + :: toString ( info.commandBuffer ) +
            ", deviceMask = "               + info.deviceMask +
            " }";
}

template < typename T >
auto toStringVulkan ( uint32 count, T const * pElements ) noexcept -> String {
    String asString = "[ ";

    for ( uint32 i = 0U; i < count; ++ i ) {
        asString += vulkan :: toString ( pElements[i] ) + ", "_s;
    }

    return asString.removeSuffix(", ") + " ]";
}

template < typename T >
auto toStringEngine ( uint32 count, T const * pElements ) noexcept -> String {
    String asString = "[ ";

    for ( uint32 i = 0U; i < count; ++ i ) {
        asString += engine :: toString ( pElements[i] ) + ", "_s;
    }

    return asString.removeSuffix(", ") + " ]";
}

template < typename T >
auto toStringFlags ( uint32 count, T const * pElements ) noexcept -> String {
    String asString = "[ ";

    for ( uint32 i = 0U; i < count; ++ i ) {
        asString += "0b" + Long ( static_cast < uint64 > ( pElements[i] ) ).toString(2) + ", "_s;
    }

    return asString.removeSuffix(", ") + " ]";
}

template < typename T >
auto toStringRegular ( uint32 count, T const * pElements ) noexcept -> String {
    String asString = "[ ";

    for ( uint32 i = 0U; i < count; ++ i ) {
        asString += String(pElements[i]) + ", "_s;
    }

    return asString.removeSuffix(", ") + " ]";
}

auto vulkan :: toString (
        Type ( SubmitInfo2 ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( SubmitInfo2 ) ) " "
            "{ structureType = "_s          + toString ( info.structureType ) +
            ", pNext = "                    + engine :: toString ( info.pNext ) +
            ", flags = "                    + :: flagsToString < Type ( SubmitFlag ) > ( info.flags ) +
            ", waitSemaphoreInfoCount = "   + info.waitSemaphoreInfoCount +
            ", waitSemaphoreInfos = "       + :: toStringVulkan ( info.waitSemaphoreInfoCount, info.pWaitSemaphoreInfos ) +
            ", commandBufferInfoCount = "   + info.commandBufferInfoCount +
            ", commandBufferInfos = "       + :: toStringVulkan ( info.commandBufferInfoCount, info.pCommandBufferInfos ) +
            ", signalSemaphoreInfoCount = " + info.pSignalSemaphoreInfos +
            ", signalSemaphoreInfos = "     + :: toStringVulkan ( info.signalSemaphoreInfoCount, info.pSignalSemaphoreInfos ) +
            " }";
}

#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

auto vulkan :: toString (
        Type ( SubmitInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( SubmitInfo ) ) " "
            "{ structureType = "_s              + toString ( info.structureType ) +
            ", pNext = "                        + engine :: toString ( info.pNext ) +
            ", waitSemaphoreCount = "           + info.waitSemaphoreCount +
            ", waitSemaphores = "               + :: toStringEngine ( info.waitSemaphoreCount, info.pWaitSemaphores ) +
            ", waitDestinationStageMasks = "    + :: toStringFlags ( info.waitSemaphoreCount, info.pWaitDestinationStageMasks ) +
            ", commandBufferCount = "           + info.commandBufferCount +
            ", commandBuffers = "               + :: toStringEngine ( info.commandBufferCount, info.pCommandBuffers ) +
            ", signalSemaphoreCount = "         + info.signalSemaphoreCount +
            ", signalSemaphores = "             + :: toStringEngine ( info.signalSemaphoreCount, info.pSignalSemaphores ) +
            " }";
}

#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

auto vulkan :: toString (
        Type ( DeviceGroupSubmitInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( DeviceGroupSubmitInfo ) ) " "
            "{ structureType = "_s              + toString ( info.structureType ) +
            ", pNext = "                        + engine :: toString ( info.pNext ) +
            ", waitSemaphoreCount = "           + info.waitSemaphoreCount +
            ", waitSemaphores = "               + :: toStringRegular ( info.waitSemaphoreCount, info.pWaitSemaphoreDeviceIndices ) +
            ", commandBufferCount = "           + info.commandBufferCount +
            ", commandBufferDeviceMasks = "     + :: toStringRegular ( info.commandBufferCount, info.pCommandBufferDeviceMasks ) +
            ", signalSemaphoreCount = "         + info.signalSemaphoreCount +
            ", signalSemaphoreDeviceIndices = " + :: toStringRegular ( info.signalSemaphoreCount, info.pSignalSemaphoreDeviceIndices ) +
            " }";
}

auto vulkan :: toString (
        Type ( ProtectedSubmitInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ProtectedSubmitInfo ) ) " "
            "{ structureType = "_s              + toString ( info.structureType ) +
            ", pNext = "                        + engine :: toString ( info.pNext ) +
            ", protectedSubmit = "              + ( info.protectedSubmit == VK_TRUE ? "true" : "false" ) +
            " }";
}

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

auto vulkan :: toString (
        Type ( TimelineSemaphoreSubmitInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( TimelineSemaphoreSubmitInfo ) ) " "
            "{ structureType = "_s              + toString ( info.structureType ) +
            ", pNext = "                        + engine :: toString ( info.pNext ) +
            ", waitSemaphoreValueCount = "      + info.waitSemaphoreValueCount +
            ", waitSemaphoreValues = "          + :: toStringRegular ( info.waitSemaphoreValueCount, info.pWaitSemaphoreValues ) +
            ", signalSemaphoreValueCount = "    + info.signalSemaphoreValueCount +
            ", signalSemaphoreValues = "        + :: toStringRegular ( info.signalSemaphoreValueCount, info.pSignalSemaphoreValues ) +
            " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

auto vulkan :: toString (
        Type ( PerformanceQuerySubmitInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PerformanceQuerySubmitInfo ) ) " "
            "{ structureType = "_s              + toString ( info.structureType ) +
            ", pNext = "                        + engine :: toString ( info.pNext ) +
            ", counterPassIndex = "             + info.counterPassIndex +
            " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WIN32_KEYED_MUTEX_AVAILABLE

auto vulkan :: toString (
        Type ( Win32KeyedMutexAcquireReleaseInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( Win32KeyedMutexAcquireReleaseInfo ) ) " "
            "{ structureType = "_s              + toString ( info.structureType ) +
            ", pNext = "                        + engine :: toString ( info.pNext ) +
            ", acquireCount = "                 + info.acquireCount +
            ", acquireSyncs = "                 + :: toStringVulkan ( info.acquireCount, info.pAcquireSyncs ) +
            ", acquireKeys = "                  + :: toStringRegular ( info.acquireCount, info.pAcquireKeys ) +
            ", acquireTimeouts = "              + :: toStringRegular ( info.acquireCount, info.pAcquireTimeouts ) +
            ", releaseCount = "                 + info.releaseCount +
            ", releaseSyncs = "                 + :: toStringVulkan ( info.releaseCount, info.pReleaseSyncs ) +
            ", releaseKeys = "                  + :: toStringRegular ( info.releaseCount, info.pReleaseKeys ) +
            " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_WIN32_KEYED_MUTEX_AVAILABLE

auto vulkan :: toString (
        Type ( Win32KeyedMutexAcquireReleaseInfoNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( Win32KeyedMutexAcquireReleaseInfoNVidia ) ) " "
            "{ structureType = "_s              + toString ( info.structureType ) +
            ", pNext = "                        + engine :: toString ( info.pNext ) +
            ", acquireCount = "                 + info.acquireCount +
            ", acquireSyncs = "                 + :: toStringVulkan ( info.acquireCount, info.pAcquireSyncs ) +
            ", acquireKeys = "                  + :: toStringRegular ( info.acquireCount, info.pAcquireKeys ) +
            ", acquireTimeouts (ms) = "         + :: toStringRegular ( info.acquireCount, info.pAcquireTimeoutsMilliseconds ) +
            ", releaseCount = "                 + info.releaseCount +
            ", releaseSyncs = "                 + :: toStringVulkan ( info.releaseCount, info.pReleaseSyncs ) +
            ", releaseKeys = "                  + :: toStringRegular ( info.releaseCount, info.pReleaseKeys ) +
            " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_WIN32_AVAILABLE

auto vulkan :: toString (
        Type ( D3D12FenceSubmitInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( D3D12FenceSubmitInfo ) ) " "
           "{ structureType = "_s              + toString ( info.structureType ) +
           ", pNext = "                        + engine :: toString ( info.pNext ) +
           ", waitSemaphoreValueCount = "      + info.waitSemaphoreValueCount +
           ", waitSemaphoreValues = "          + :: toStringRegular ( info.waitSemaphoreValueCount, info.pWaitSemaphoreValues ) +
           ", signalSemaphoreValueCount = "    + info.signalSemaphoreValueCount +
           ", signalSemaphoreValues = "        + :: toStringRegular ( info.signalSemaphoreValueCount, info.pSignalSemaphoreValues ) +
           " }";
}

#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

auto vulkan :: toString (
        Type ( AccessFlag ) flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case AccessFlagIndirectCommandRead:                 { asString = "IndirectCommandRead";                 break; }
        case AccessFlagIndexRead:                           { asString = "IndexRead";                           break; }
        case AccessFlagVertexAttributeRead:                 { asString = "VertexAttributeRead";                 break; }
        case AccessFlagUniformRead:                         { asString = "UniformRead";                         break; }
        case AccessFlagInputAttachmentRead:                 { asString = "InputAttachmentRead";                 break; }
        case AccessFlagShaderRead:                          { asString = "ShaderRead";                          break; }
        case AccessFlagShaderWrite:                         { asString = "ShaderWrite";                         break; }
        case AccessFlagColorAttachmentRead:                 { asString = "ColorAttachmentRead";                 break; }
        case AccessFlagColorAttachmentWrite:                { asString = "ColorAttachmentWrite";                break; }
        case AccessFlagDepthStencilAttachmentRead:          { asString = "DepthStencilAttachmentRead";          break; }
        case AccessFlagDepthStencilAttachmentWrite:         { asString = "DepthStencilAttachmentWrite";         break; }
        case AccessFlagTransferRead:                        { asString = "TransferRead";                        break; }
        case AccessFlagTransferWrite:                       { asString = "TransferWrite";                       break; }
        case AccessFlagHostRead:                            { asString = "HostRead";                            break; }
        case AccessFlagHostWrite:                           { asString = "HostWrite";                           break; }
        case AccessFlagMemoryRead:                          { asString = "MemoryRead";                          break; }
        case AccessFlagMemoryWrite:                         { asString = "MemoryWrite";                         break; }

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE

        case AccessFlagNone:                                { asString = "None";                                break; }
        case AccessFlagShaderSampledRead:                   { asString = "ShaderSampledRead";                   break; }
        case AccessFlagShaderStorageRead:                   { asString = "ShaderStorageRead";                   break; }
        case AccessFlagShaderStorageWrite:                  { asString = "ShaderStorageWrite";                  break; }

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_DECODE_QUEUE_AVAILABLE

        case AccessFlagVideoDecodeRead:                     { asString = "VideoDecodeRead";                     break; }
        case AccessFlagVideoDecodeWrite:                    { asString = "VideoDecodeWrite";                    break; }

#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_ENCODE_QUEUE_AVAILABLE

        case AccessFlagVideoEncodeRead:                     { asString = "VideoEncodeRead";                     break; }
        case AccessFlagVideoEncodeWrite:                    { asString = "VideoEncodeWrite";                    break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_INVOCATION_MASK_AVAILABLE

        case AccessFlagInvocationMaskReadHuawei:            { asString = "InvocationMaskReadHuawei";            break; }

#endif

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE

        case AccessFlagTransformFeedbackWrite:              { asString = "TransformFeedbackWrite";              break; }
        case AccessFlagTransformFeedbackCounterRead:        { asString = "TransformFeedbackCounterRead";        break; }
        case AccessFlagTransformFeedbackCounterWrite:       { asString = "TransformFeedbackCounterWrite";       break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE

        case AccessFlagConditionalRenderingRead:            { asString = "ConditionalRenderingRead";            break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE

        case AccessFlagColorAttachmentReadNonCoherent:      { asString = "ColorAttachmentReadNonCoherent";      break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE

        case AccessFlagAccelerationStructureRead:           { asString = "AccelerationStructureRead";           break; }
        case AccessFlagAccelerationStructureWrite:          { asString = "AccelerationStructureWrite";          break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

        case AccessFlagFragmentDensityMapRead:              { asString = "FragmentDensityMapRead";              break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE

        case AccessFlagFragmentShadingRateAttachmentRead:   { asString = "FragmentShadingRateAttachmentRead";   break; }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE

        case AccessFlagCommandPreprocessReadNVidia:         { asString = "CommandPreprocessReadNVidia";         break; }
        case AccessFlagCommandPreprocessWriteNVidia:        { asString = "CommandPreprocessWriteNVidia";        break; }

#endif

    }

    return asString;
}

auto vulkan :: toString (
        Type ( FenceCreateFlag ) flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case FenceCreateFlagSignaled:   { asString = "Signaled";    break; }
    }

    return asString;
}

auto vulkan :: toString (
        Type ( FenceCreateInfo ) const & createInfo
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( FenceCreateInfo ) ) " "
            "{ structureType = "_s  + toString ( createInfo.structureType ) +
            ", pNext = "            + engine :: toString ( createInfo.pNext ) +
            ", flags = "            + :: flagsToString < Type ( FenceCreateFlag ) > ( createInfo.flags ) +
            " }";
}

#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

auto vulkan :: toString (
        Type ( ExternalFenceHandleTypeFlag ) flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case ExternalFenceHandleTypeFlagOpaqueFD:       { asString = "OpaqueFD";        break; }
        case ExternalFenceHandleTypeFlagOpaqueWin32:    { asString = "OpaqueWin32";     break; }
        case ExternalFenceHandleTypeFlagOpaqueWin32KMT: { asString = "OpaqueWin32KMT";  break; }
        case ExternalFenceHandleTypeFlagSyncFD:         { asString = "SyncFD";          break; }
    }

    return asString;
}

auto vulkan :: toString (
        Type ( ExportFenceCreateInfo ) const & createInfo
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ExportFenceCreateInfo ) ) " "
            "{ structureType = "_s  + toString ( createInfo.structureType ) +
            ", pNext = "            + engine :: toString ( createInfo.pNext ) +
            ", handleTypes = "      + :: flagsToString < Type ( ExternalFenceHandleTypeFlag ) > ( createInfo.handleTypes ) +
            " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_WIN32_AVAILABLE

auto vulkan :: toString (
        Type ( ExportFenceWin32HandleInfo ) const & createInfo
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ExportFenceWin32HandleInfo ) ) " "
            "{ structureType = "_s  + toString ( createInfo.structureType ) +
            ", pNext = "            + engine :: toString ( createInfo.pNext ) +
            ", pAttributes = "      + engine :: toString ( createInfo.pAttributes ) +
            ", dwAccess = "         + createInfo.dwAccess +
            ", name = "             + createInfo.name +
            " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_FD_AVAILABLE

auto vulkan :: toString (
        Type ( FenceGetFDInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( FenceGetFDInfo ) ) " "
            "{ structureType = "_s  + toString ( info.structureType ) +
            ", pNext = "            + engine :: toString ( info.pNext ) +
            ", fence = "            + engine :: toString ( info.fence ) +
            ", handleType = "       + toString ( info.handleType ) +
            " }";
}

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_REPORT_AVAILABLE
auto vulkan :: toString (
        Type ( DebugReportFlag )    flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case DebugReportFlagInformation:        { asString = "Information";         break; }
        case DebugReportFlagWarning:            { asString = "Warning";             break; }
        case DebugReportFlagPerformanceWarning: { asString = "PerformanceWarning";  break; }
        case DebugReportFlagError:              { asString = "Error";               break; }
        case DebugReportFlagDebug:              { asString = "Debug";               break; }
    }

    return asString;
}

auto vulkan :: toString (
        Type ( DebugReportCreateInfo )  const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( DebugReportCreateInfo ) ) " "
           "{ structureType = "_s  + toString ( info.structureType ) +
           ", pNext = "            + engine :: toString ( info.pNext ) +
           ", flags = "            + :: flagsToString < Type ( DebugReportFlag ) > ( info.flags ) +
           ", callback = "         + engine :: toString ( info.callback ) +
           ", pUserData = "        + engine :: toString ( info.pUserData ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_FLAGS_AVAILABLE
auto vulkan :: toString (
        Type ( ValidationCheck )    check
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( check ) {
        case ValidationCheckAll:        { asString = "All";     break; }
        case ValidationCheckShaders:    { asString = "Shaders"; break; }
    }

    return asString;
}

auto vulkan :: toString (
        Type ( ValidationFlags )    const & flags
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ValidationFlags ) ) " "
           "{ structureType = "_s               + toString ( flags.structureType ) +
           ", pNext = "                         + engine :: toString ( flags.pNext ) +
           ", disabledValidationCheckCount = "  + flags.disabledValidationCheckCount +
           ", disabledValidationChecks = "      + :: toStringVulkan ( flags.disabledValidationCheckCount, flags.pDisabledValidationChecks ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISPLAY_CONTROL_AVAILABLE
auto vulkan :: toString (
        Type ( DeviceEventType )    type
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( type ) {
        case DeviceEventTypeDisplayHotplug: { asString = "Display Hotplug"; break; }
    }

    return asString;
}

auto vulkan :: toString (
        Type ( DeviceEventInfo )    const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( DeviceEventInfo ) ) " "
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", deviceEvent = "                   + toString ( info.deviceEvent ) +
           " }";
}

auto vulkan :: toString (
        Type ( DisplayEventType )   type
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( type ) {
        case DisplayEventTypeFirstPixelOut: { asString = "First Pixel Out"; break; }
    }

    return asString;
}

auto vulkan :: toString (
        Type ( DisplayEventInfo )    const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( DisplayEventInfo ) ) " "
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", displayEvent = "                  + toString ( info.displayEvent ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto vulkan :: toString (
        Type ( FenceImportFlag )    flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case FenceImportFlagTemporary: { asString = "Temporary"; break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_WIN32_AVAILABLE
auto vulkan :: toString (
        Type ( ImportFenceWin32HandleInfo )    const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ImportFenceWin32HandleInfo ) ) " "
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", fence = "                         + engine :: toString ( info.fence ) +
           ", flags = "                         + :: flagsToString < Type ( FenceImportFlag ) > ( info.flags ) +
           ", handleType = "                    + toString ( info.handleType ) +
           ", handle = "                        + engine :: toString ( info.handle ) +
           ", name = "                          + info.name +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_FD_AVAILABLE
auto vulkan :: toString (
        Type ( ImportFenceFdInfo )    const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ImportFenceFdInfo ) ) " "
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", fence = "                         + engine :: toString ( info.fence ) +
           ", flags = "                         + :: flagsToString < Type ( FenceImportFlag ) > ( info.flags ) +
           ", handleType = "                    + toString ( info.handleType ) +
           ", fd = "                            + info.fd +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( SemaphoreCreateInfo )    const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( SemaphoreCreateInfo ) ) " "
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", flags = "                         + :: flagsToString ( info.flags ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto vulkan :: toString (
        Type ( ExternalSemaphoreHandleTypeFlag )    flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case ExternalSemaphoreHandleTypeFlagOpaqueFd:           { asString = "Opaque FD";           break; }
        case ExternalSemaphoreHandleTypeFlagOpaqueWin32:        { asString = "Opaque Win32";        break; }
        case ExternalSemaphoreHandleTypeFlagOpaqueWin32KMT:     { asString = "Opaque Win32 KMT";    break; }
        case ExternalSemaphoreHandleTypeFlagD3D12Fence:         { asString = "D3D12 Fence";         break; }
        case ExternalSemaphoreHandleTypeFlagSyncFd:             { asString = "Sync FD";             break; }
#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_SEMAPHORE_AVAILABLE
        case ExternalSemaphoreHandleTypeFlagZirconEventFuchsia: { asString = "Zircon Event";        break; }
#endif
    }

    return asString;
}

auto vulkan :: toString (
        Type ( ExportSemaphoreCreateInfo )    const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ExportSemaphoreCreateInfo ) ) " "
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", handleTypes = "                   + :: flagsToString < Type ( ExternalSemaphoreHandleTypeFlag ) > ( info.handleTypes ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
auto vulkan :: toString (
        Type ( SemaphoreType ) type
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( type ) {
        case SemaphoreTypeBinary:   { asString = "Binary";      break; }
        case SemaphoreTypeTimeline: { asString = "Timeline";    break; }
    }

    return asString;
}

auto vulkan :: toString (
        Type ( SemaphoreTypeCreateInfo )    const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( SemaphoreTypeCreateInfo ) ) " "
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", semaphoreType = "                 + toString ( info.semaphoreType ) +
           ", initialValue = "                  + info.initialValue +
           " }";
}
auto vulkan :: toString (
        Type ( SemaphoreWaitFlag ) flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case SemaphoreWaitFlagAny:  { asString = "Any";      break; }
    }

    return asString;
}

auto vulkan :: toString (
        Type ( SemaphoreWaitInfo )    const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( SemaphoreWaitInfo ) ) " "
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", flags = "                         + :: flagsToString < Type ( SemaphoreWaitFlag ) > ( info.flags ) +
           ", semaphoreCount = "                + info.semaphoreCount +
           ", pSemaphores = "                   + :: toStringEngine ( info.semaphoreCount, info.pSemaphores ) +
           ", pValues = "                       + :: toStringRegular ( info.semaphoreCount, info.pValues ) +
           " }";
}

auto vulkan :: toString (
        Type ( SemaphoreSignalInfo )    const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( SemaphoreSignalInfo ) ) " "
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", semaphore = "                     + engine :: toString ( info.semaphore ) +
           ", value = "                         + info.value +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_WIN32_AVAILABLE
auto vulkan :: toString (
        Type ( SemaphoreGetWin32HandleInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( SemaphoreGetWin32HandleInfo ) ) " "
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", semaphore = "                     + engine :: toString ( info.semaphore ) +
           ", handleType = "                    + toString ( info.handleType ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_FD_AVAILABLE
auto vulkan :: toString (
        Type ( SemaphoreGetFdInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( SemaphoreGetFdInfo ) ) " "
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", semaphore = "                     + engine :: toString ( info.semaphore ) +
           ", handleType = "                    + toString ( info.handleType ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_SEMAPHORE_AVAILABLE
auto vulkan :: toString (
        Type ( SemaphoreGetZirconHandleInfoGoogle ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( SemaphoreGetZirconHandleInfoGoogle ) ) " "
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", semaphore = "                     + engine :: toString ( info.semaphore ) +
           ", handleType = "                    + toString ( info.handleType ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto vulkan :: toString (
        Type ( SemaphoreImportFlag ) flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case SemaphoreImportFlagTemporary:  { asString = "Temporary";      break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_WIN32_AVAILABLE
auto vulkan :: toString (
        Type ( ImportSemaphoreWin32HandleInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ImportSemaphoreWin32HandleInfo ) ) " "
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", semaphore = "                     + engine :: toString ( info.semaphore ) +
           ", flags = "                         + :: flagsToString < Type ( SemaphoreImportFlag ) > ( info.flags ) +
           ", handleType = "                    + toString ( info.handleType ) +
           ", handle = "                        + engine :: toString ( info.handle ) +
           ", name = "                          + info.name +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_FD_AVAILABLE
auto vulkan :: toString (
        Type ( ImportSemaphoreFdInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ImportSemaphoreFdInfo ) ) " "
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", semaphore = "                     + engine :: toString ( info.semaphore ) +
           ", flags = "                         + :: flagsToString < Type ( SemaphoreImportFlag ) > ( info.flags ) +
           ", handleType = "                    + toString ( info.handleType ) +
           ", fd = "                            + info.fd +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_SEMAPHORE_AVAILABLE
auto vulkan :: toString (
        Type ( ImportSemaphoreZirconHandleInfoGoogle ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ImportSemaphoreZirconHandleInfoGoogle ) ) " "
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", semaphore = "                     + engine :: toString ( info.semaphore ) +
           ", flags = "                         + :: flagsToString < Type ( SemaphoreImportFlag ) > ( info.flags ) +
           ", handleType = "                    + toString ( info.handleType ) +
           ", zirconHandle = "                  + info.zirconHandle +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( EventCreateFlag ) flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case EventCreateFlagDeviceOnly: { asString = "Device Only";      break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( EventCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( EventCreateInfo ) ) " "
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", flags = "                         + :: flagsToString < Type ( EventCreateFlag ) > ( info.flags ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( DependencyFlag ) flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case DependencyFlagByRegion:    { asString = "By Region";       break; }

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
        case DependencyFlagDeviceGroup: { asString = "Device Group";    break; }
        case DependencyFlagViewLocal:   { asString = "View Local";      break; }
#endif
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( ImageLayout ) flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case ImageLayoutUndefined:                            { asString = "Undefined";                             break; }
        case ImageLayoutGeneral:                              { asString = "General";                               break; }
        case ImageLayoutColorttachmentOptimal:                { asString = "ColorttachmentOptimal";                 break; }
        case ImageLayoutDepthStencilAttachmentOptimal:        { asString = "DepthStencilAttachmentOptimal";         break; }
        case ImageLayoutDepthStencilReadOnlyOptimal:          { asString = "DepthStencilReadOnlyOptimal";           break; }
        case ImageLayoutSharedReadOnlyOptimal:                { asString = "SharedReadOnlyOptimal";                 break; }
        case ImageLayoutTransferSourceOptimal:                { asString = "TransferSourceOptimal";                 break; }
        case ImageLayoutTransferDestinationOptimal:           { asString = "TransferDestinationOptimal";            break; }
        case ImageLayoutPreinitialized:                       { asString = "Preinitialized";                        break; }

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
        case ImageLayoutDepthReadOnlyStencilAttachmentOptimal:{ asString = "DepthReadOnlyStencilAttachmentOptimal"; break; }
        case ImageLayoutDepthAttachmentStencilReadOnlyOptimal:{ asString = "DepthAttachmentStencilReadOnlyOptimal"; break; }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
        case ImageLayoutDepthAttachmentOptimal:               { asString = "DepthAttachmentOptimal";                break; }
        case ImageLayoutDepthReadOnlyOptimal:                 { asString = "DepthReadOnlyOptimal";                  break; }
        case ImageLayoutStencilAttachmentOptimal:             { asString = "StencilAttachmentOptimal";              break; }
        case ImageLayoutStencilReadOnlyOptimal:               { asString = "StencilReadOnlyOptimal";                break; }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
        case ImageLayoutReadOnlyOptimal:                      { asString = "ReadOnlyOptimal";                       break; }
        case ImageLayoutAttachmentOptimal:                    { asString = "AttachmentOptimal";                     break; }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE
        case ImageLayoutLayoutPresentSource:                  { asString = "LayoutPresentSource";                   break; }
#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_DECODE_QUEUE_AVAILABLE
        case ImageLayoutVideoDecodeDestination:               { asString = "VideoDecodeDestination";                break; }
        case ImageLayoutVideoDecodeSource:                    { asString = "VideoDecodeSource";                     break; }
        case ImageLayoutVideoDecodeDPB:                       { asString = "VideoDecodeDPB";                        break; }
#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_ENCODE_QUEUE_AVAILABLE
        case ImageLayoutVideoEncodeDestination:               { asString = "VideoEncodeDestination";                break; }
        case ImageLayoutVideoEncodeSource:                    { asString = "VideoEncodeSource";                     break; }
        case ImageLayoutVideoEncodeDPB:                       { asString = "VideoEncodeDPB";                        break; }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHARED_PRESENTABLE_IMAGE_AVAILABLE
        case ImageLayoutSharedPresent:                        { asString = "SharedPresent";                         break; }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE
        case ImageLayoutFragmentDensityMapOptimal:            { asString = "FragmentDensityMapOptimal";             break; }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE
        case ImageLayoutFragmentShadingRateAttachmentOptimal: { asString = "FragmentShadingRateAttachmentOptimal";  break; }
#endif
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
auto vulkan :: toString (
        Type ( MemoryBarrier2 ) const & barrier
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( MemoryBarrier2 ) ) " "
           "{ structureType = "_s               + toString ( barrier.structureType ) +
           ", pNext = "                         + engine :: toString ( barrier.pNext ) +
           ", sourceStageMask = "               + :: flagsToString < Type ( PipelineStageFlag ) > ( barrier.sourceStageMask ) +
           ", sourceAccessMask = "              + :: flagsToString < Type ( AccessFlag ) > ( barrier.sourceAccessMask ) +
           ", destinationStageMask = "          + :: flagsToString < Type ( PipelineStageFlag ) > ( barrier.destinationStageMask ) +
           ", destinationAccessMask = "         + :: flagsToString < Type ( AccessFlag ) > ( barrier.destinationAccessMask ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
auto vulkan :: toString (
        Type ( BufferMemoryBarrier2 ) const & barrier
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( BufferMemoryBarrier2 ) ) " "
           "{ structureType = "_s               + toString ( barrier.structureType ) +
           ", pNext = "                         + engine :: toString ( barrier.pNext ) +
           ", sourceStageMask = "               + :: flagsToString < Type ( PipelineStageFlag ) > ( barrier.sourceStageMask ) +
           ", sourceAccessMask = "              + :: flagsToString < Type ( AccessFlag ) > ( barrier.sourceAccessMask ) +
           ", destinationStageMask = "          + :: flagsToString < Type ( PipelineStageFlag ) > ( barrier.destinationStageMask ) +
           ", destinationAccessMask = "         + :: flagsToString < Type ( AccessFlag ) > ( barrier.destinationAccessMask ) +
           ", sourceQueueFamilyIndex = "        + barrier.sourceQueueFamilyIndex +
           ", destinationQueueFamilyIndex = "   + barrier.destinationQueueFamilyIndex +
           ", buffer = "                        + engine :: toString ( barrier.buffer ) +
           ", offset = "                        + toString ( barrier.offset ) +
           ", size = "                          + toString ( barrier.size ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
auto vulkan :: toString (
        Type ( ImageMemoryBarrier2 ) const & barrier
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ImageMemoryBarrier2 ) ) " "
           "{ structureType = "_s               + toString ( barrier.structureType ) +
           ", pNext = "                         + engine :: toString ( barrier.pNext ) +
           ", sourceStageMask = "               + :: flagsToString < Type ( PipelineStageFlag ) > ( barrier.sourceStageMask ) +
           ", sourceAccessMask = "              + :: flagsToString < Type ( AccessFlag ) > ( barrier.sourceAccessMask ) +
           ", destinationStageMask = "          + :: flagsToString < Type ( PipelineStageFlag ) > ( barrier.destinationStageMask ) +
           ", destinationAccessMask = "         + :: flagsToString < Type ( AccessFlag ) > ( barrier.destinationAccessMask ) +
           ", oldLayout = "                     + toString ( barrier.oldLayout ) +
           ", newLayout = "                     + toString ( barrier.newLayout ) +
           ", sourceQueueFamilyIndex = "        + barrier.sourceQueueFamilyIndex +
           ", destinationQueueFamilyIndex = "   + barrier.destinationQueueFamilyIndex +
           ", image = "                         + engine :: toString ( barrier.image ) +
           ", subresourceRange = "              + toString ( barrier.subresourceRange ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
auto vulkan :: toString (
        Type ( DependencyInfo ) const & barrier
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( DependencyInfo ) ) " "
           "{ structureType = "_s               + toString ( barrier.structureType ) +
           ", pNext = "                         + engine :: toString ( barrier.pNext ) +
           ", dependencyFlags = "               + :: flagsToString < Type ( DependencyFlag ) > ( barrier.dependencyFlags ) +
           ", memoryBarrierCount = "            + barrier.memoryBarrierCount +
           ", memoryBarriers = "                + :: toStringVulkan ( barrier.memoryBarrierCount, barrier.pMemoryBarriers ) +
           ", bufferMemoryBarrierCount = "      + barrier.bufferMemoryBarrierCount +
           ", pBufferMemoryBarriers = "         + :: toStringVulkan ( barrier.bufferMemoryBarrierCount, barrier.pBufferMemoryBarriers ) +
           ", imageMemoryBarrierCount = "       + barrier.imageMemoryBarrierCount +
           ", pImageMemoryBarriers = "          + :: toStringVulkan ( barrier.imageMemoryBarrierCount, barrier.pImageMemoryBarriers ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE
auto vulkan :: toString (
        Type ( SampleLocation ) const & location
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( SampleLocation ) ) " "
           "{ x = "_s   + location.x +
           ", y = "     + location.y +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE
auto vulkan :: toString (
        Type ( SampleLocationsInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( SampleLocationsInfo ) ) " "
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", sampleLocationsPerPixel = "       + toString ( info.sampleLocationsPerPixel ) +
           ", sampleLocationGridSize = "        + toString ( info.sampleLocationGridSize ) +
           ", sampleLocationsCount = "          + toString ( info.sampleLocationsCount ) +
           ", sampleLocations = "               + :: toStringVulkan ( info.sampleLocationsCount, info.pSampleLocations ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( MemoryBarrier ) const & barrier
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( MemoryBarrier ) ) " "
           "{ structureType = "_s               + toString ( barrier.structureType ) +
           ", pNext = "                         + engine :: toString ( barrier.pNext ) +
           ", sourceAccessMask = "              + :: flagsToString < Type ( AccessFlag ) > ( barrier.sourceAccessMask ) +
           ", destinationAccessMask = "         + :: flagsToString < Type ( AccessFlag ) > ( barrier.destinationAccessMask ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( BufferMemoryBarrier ) const & barrier
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( BufferMemoryBarrier ) ) " "
           "{ structureType = "_s               + toString ( barrier.structureType ) +
           ", pNext = "                         + engine :: toString ( barrier.pNext ) +
           ", sourceAccessMask = "              + :: flagsToString < Type ( AccessFlag ) > ( barrier.sourceAccessMask ) +
           ", destinationAccessMask = "         + :: flagsToString < Type ( AccessFlag ) > ( barrier.destinationAccessMask ) +
           ", sourceQueueFamilyIndex = "        + barrier.sourceQueueFamilyIndex +
           ", destinationQueueFamilyIndex = "   + barrier.destinationQueueFamilyIndex +
           ", buffer = "                        + engine :: toString ( barrier.buffer ) +
           ", offset = "                        + toString ( barrier.offset ) +
           ", size = "                          + toString ( barrier.size ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( ImageMemoryBarrier ) const & barrier
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ImageMemoryBarrier2 ) ) " "
           "{ structureType = "_s               + toString ( barrier.structureType ) +
           ", pNext = "                         + engine :: toString ( barrier.pNext ) +
           ", sourceAccessMask = "              + :: flagsToString < Type ( AccessFlag ) > ( barrier.sourceAccessMask ) +
           ", destinationAccessMask = "         + :: flagsToString < Type ( AccessFlag ) > ( barrier.destinationAccessMask ) +
           ", oldLayout = "                     + toString ( barrier.oldLayout ) +
           ", newLayout = "                     + toString ( barrier.newLayout ) +
           ", sourceQueueFamilyIndex = "        + barrier.sourceQueueFamilyIndex +
           ", destinationQueueFamilyIndex = "   + barrier.destinationQueueFamilyIndex +
           ", image = "                         + engine :: toString ( barrier.image ) +
           ", subresourceRange = "              + toString ( barrier.subresourceRange ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CALIBRATED_TIMESTAMPS_AVAILABLE
auto vulkan :: toString (
        Type ( TimeDomain ) domain
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( domain ) {
        case TimeDomainDevice:                  { asString = "Device";                      break; }
        case TimeDomainClockMonotonic:          { asString = "Clock Monotonic";             break; }
        case TimeDomainClockMonotonicRaw:       { asString = "Clock Monotonic Raw";         break; }
        case TimeDomainQueryPerformanceCounter: { asString = "Query Performance Counter";   break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CALIBRATED_TIMESTAMPS_AVAILABLE
auto vulkan :: toString (
        Type ( CalibratedTimestampInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( CalibratedTimestampInfo ) ) " "
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", timeDomain = "                    + toString ( info.timeDomain ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CALIBRATED_TIMESTAMPS_AVAILABLE
auto vulkan :: toString (
        Type ( GetCalibratedTimestamps ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( GetCalibratedTimestamps ) ) " "
           "{ device = "_s               + engine :: toString ( info.device ) +
           ", timestampCount = "         + info.timestampCount +
           ", timestampInfos = "         + :: toStringVulkan ( info.timestampCount, info.pTimestampInfos ) +
           ", timestamps = "             + :: toStringRegular ( info.timestampCount, info.pTimestamps ) +
           ", maxDeviation = "           + engine :: toString ( info.pMaxDeviation ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( AttachmentLoadOperation ) operation
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( operation ) {
        case AttachmentLoadOperationLoad:       { asString = "Load";        break; }
        case AttachmentLoadOperationClear:      { asString = "Clear";       break; }
        case AttachmentLoadOperationDontCare:   { asString = "Don't Care";  break; }
#if __C_ENG_VULKAN_API_EXTENSION_LOAD_STORE_OP_NONE_AVAILABLE
        case AttachmentLoadOperationNone:       { asString = "None";        break; }
#endif
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( AttachmentStoreOperation ) operation
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( operation ) {
        case AttachmentStoreOperationStore:       { asString = "Store";       break; }
        case AttachmentStoreOperationDontCare:    { asString = "Don't Care";  break; }
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_LOAD_STORE_OP_NONE_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_RENDER_PASS_STORE_OPERATIONS_AVAILABLE
        case AttachmentStoreOperationNone:        { asString = "None";        break; }
#endif
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( ClearColorValue ) const & value
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ClearColorValue ) ) " " +
            "{ float32 = "_s    + :: toStringRegular ( 4, & value.float32[0] ) +
            ", int32 = "        + :: toStringRegular ( 4, & value.int32[0] ) +
            ", uint32 = "       + :: toStringRegular ( 4, & value.uint32[0] ) +
            " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( ClearDepthStencilValue ) const & value
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ClearDepthStencilValue ) ) " " +
            "{ depth = "_s      + value.depth +
            ", stencil = "      + value.stencil +
            " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( ClearValue ) const & value
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ClearValue ) ) " " +
            "{ color = "_s          + toString ( value.color ) +
            " OR depthStencil = "   + toString ( value.depthStencil ) +
            " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
auto vulkan :: toString (
        Type ( RenderingAttachmentInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( RenderingAttachmentInfo ) ) " " +
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", imageView = "                     + engine :: toString ( info.imageView ) +
           ", imageLayout = "                   + toString ( info.imageLayout ) +
           ", resolveMode = "                   + toString ( info.resolveMode ) +
           ", resolveImageView = "              + engine :: toString ( info.resolveImageView ) +
           ", resolveImageLayout = "            + toString ( info.resolveImageLayout ) +
           ", loadOperation = "                 + toString ( info.loadOperation ) +
           ", storeOperation = "                + toString ( info.storeOperation ) +
           ", clearValue = "                    + toString ( info.clearValue ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
auto vulkan :: toString (
        Type ( RenderingInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( RenderingInfo ) ) " " +
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", flags = "                         + :: flagsToString < Type ( RenderingFlag ) > ( info.flags ) +
           ", renderArea = "                    + toString ( info.renderArea ) +
           ", layerCount = "                    + info.layerCount +
           ", viewMask = "                      + info.viewMask +
           ", colorAttachmentCount = "          + info.colorAttachmentCount +
           ", colorAttachments = "              + :: toStringVulkan ( info.colorAttachmentCount, info.pColorAttachments ) +
           ", pDepthAttachment = "              + engine :: toString ( info.pDepthAttachment ) +
           ", pStencilAttachment = "            + engine :: toString ( info.pStencilAttachment ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto vulkan :: toString (
        Type ( DeviceGroupRenderPassBeginInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( DeviceGroupRenderPassBeginInfo ) ) " " +
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", deviceMask = "                    + info.deviceMask +
           ", deviceRenderAreaCount = "         + info.deviceRenderAreaCount +
           ", deviceRenderAreas = "             + :: toStringVulkan ( info.deviceRenderAreaCount, info.pDeviceRenderAreas ) +
           " }";
}
#endif

#if ( __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE ) && __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE
auto vulkan :: toString (
        Type ( RenderingFragmentDensityMapAttachmentInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( RenderingFragmentDensityMapAttachmentInfo ) ) " " +
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", imageView = "                     + engine :: toString ( info.imageView ) +
           ", imageLayout = "                   + toString ( info.imageLayout ) +
           " }";
}
#endif

#if ( __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE ) && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE
auto vulkan :: toString (
        Type ( RenderingFragmentShadingRateAttachmentInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( RenderingFragmentShadingRateAttachmentInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", imageView = "                         + engine :: toString ( info.imageView ) +
           ", imageLayout = "                       + toString ( info.imageLayout ) +
           ", shadingRateAttachmentTexelSize = "    + toString ( info.shadingRateAttachmentTexelSize ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( RenderPassCreateFlag ) flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_RENDER_PASS_TRANSFORM_AVAILABLE
        case RenderPassCreateFlagTransformQualcomm: { asString = "Transform";   break; }
#endif
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( AttachmentDescriptionFlag ) flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case AttachmentDescriptionFlagMayAlias: { asString = "May Alias";   break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( SubpassDescriptionFlag ) flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE
        case SubpassDescriptionFlagPerViewAttributesNVidia:                         { asString = "Per View Attributes";                             break; }
        case SubpassDescriptionFlagPerViewPositionXOnlyNVidia:                      { asString = "Per View Position X Only";                        break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE
        case SubpassDescriptionFlagFragmentRegionQualcomm:                          { asString = "Fragment Region";                                 break; }
        case SubpassDescriptionFlagShaderResolveQualcomm:                           { asString = "Shader Resolve";                                  break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_ARM_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_AVAILABLE
        case SubpassDescriptionFlagRasterizationOrderAttachmentColorAccessARM:      { asString = "Rasterization Order Attachment Color Access";     break; }
        case SubpassDescriptionFlagRasterizationOrderAttachmentDepthAccessARM:      { asString = "Rasterization Order Attachment Depth Access";     break; }
        case SubpassDescriptionFlagRasterizationOrderAttachmentStencilAccessARM:    { asString = "Rasterization Order Attachment Stencil Access";   break; }
#endif
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineBindPoint ) flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case PipelineBindPointGraphics:             { asString = "Graphics";        break; }
        case PipelineBindPointCompute:              { asString = "Compute";         break; }
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
        case PipelineBindPointRayTracing:           { asString = "Ray Tracing";     break; }
#elif __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
        case PipelineBindPointRayTracingNVidia:     { asString = "Ray Tracing";     break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE
        case PipelineBindPointSubpassShadingHuawei: { asString = "Subpass Shading"; break; }
#endif
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( AttachmentDescription ) const & description
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( AttachmentDescription ) ) " " +
           "{ flags = "_s                           + :: flagsToString < Type ( AttachmentDescriptionFlag ) > ( description.flags ) +
           ", format = "                            + toString ( description.format ) +
           ", samples = "                           + toString ( description.samples ) +
           ", loadOperation = "                     + toString ( description.loadOperation ) +
           ", storeOperation = "                    + toString ( description.storeOperation ) +
           ", stencilLoadOperation = "              + toString ( description.stencilLoadOperation ) +
           ", stencilStoreOperation = "             + toString ( description.stencilStoreOperation ) +
           ", initialLayout = "                     + toString ( description.initialLayout ) +
           ", finalLayout = "                       + toString ( description.finalLayout ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( AttachmentReference ) const & description
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( AttachmentReference ) ) " " +
           "{ attachment = "_s                      + description.attachment +
           ", layout = "                            + toString ( description.layout ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( SubpassDescription ) const & description
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( SubpassDescription ) ) " " +
           "{ flags = "_s                           + :: flagsToString < Type ( SubpassDescriptionFlag ) > ( description.flags ) +
           ", pipelineBindPoint = "                 + toString ( description.pipelineBindPoint ) +
           ", inputAttachmentCount = "              + description.inputAttachmentCount +
           ", inputAttachments = "                  + :: toStringVulkan ( description.inputAttachmentCount, description.pInputAttachments ) +
           ", colorAttachmentCount = "              + description.colorAttachmentsCount +
           ", colorAttachments = "                  + :: toStringVulkan ( description.colorAttachmentsCount, description.pColorAttachments ) +
           ", resolveAttachments = "                + :: toStringVulkan ( description.colorAttachmentsCount, description.pResolveAttachments ) +
           ", pDepthStencilAttachment = "           + engine :: toString ( description.pDepthStencilAttachment ) +
           ", preserveAttachmentCount = "           + description.preserveAttachmentCount +
           ", preserveAttachments = "               + :: toStringVulkan ( description.preserveAttachmentCount, description.pPreserveAttachments ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( SubpassDependency ) const & dependency
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( SubpassDependency ) ) " " +
           "{ sourceSubpass = "_s       + dependency.sourceSubpass +
           ", destinationSubpass = "    + dependency.destinationSubpass +
           ", sourceStageMask = "       + :: flagsToString < Type ( PipelineStageFlag ) > ( dependency.sourceStageMask ) +
           ", destinationStageMask = "  + :: flagsToString < Type ( PipelineStageFlag ) > ( dependency.destinationStageMask ) +
           ", sourceAccessMask = "      + :: flagsToString < Type ( AccessFlag ) > ( dependency.sourceAccessMask ) +
           ", destinationAccessMask = " + :: flagsToString < Type ( AccessFlag ) > ( dependency.destinationAccessMask ) +
           ", dependencyFlags = "       + :: flagsToString < Type ( DependencyFlag ) > ( dependency.dependencyFlags ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( RenderPassCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( RenderPassCreateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", flags = "                             + :: flagsToString < Type ( RenderPassCreateFlag ) > ( info.flags ) +
           ", attachmentCount = "                   + info.attachmentCount +
           ", attachments = "                       + :: toStringVulkan ( info.attachmentCount, info.pAttachments ) +
           ", subpassCount = "                      + info.subpassCount +
           ", subpasses = "                         + :: toStringVulkan ( info.subpassCount, info.pSubpasses ) +
           ", dependencyCount = "                   + info.dependencyCount +
           ", dependencies = "                      + :: toStringVulkan ( info.dependencyCount, info.pDependencies ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE
auto vulkan :: toString (
        Type ( RenderPassFragmentDensityMapCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( RenderPassFragmentDensityMapCreateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", fragmentDensityMapAttachment = "      + toString ( info.fragmentDensityMapAttachment ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto vulkan :: toString (
        Type ( RenderPassInputAttachmentAspectCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( RenderPassInputAttachmentAspectCreateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", aspectReferenceCount = "              + info.aspectReferenceCount +
           ", aspectReferences = "                  + :: toStringVulkan ( info.aspectReferenceCount, info.pAspectReferences ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto vulkan :: toString (
        Type ( InputAttachmentAspectReference ) const & reference
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( InputAttachmentAspectReference ) ) " " +
           "{ subpass = "_s                     + reference.subpass +
           ", inputAttachmentIndex = "          + reference.inputAttachmentIndex +
           ", aspectMask = "                    + :: flagsToString < Type ( ImageAspectFlag ) > ( reference.aspectMask ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto vulkan :: toString (
        Type ( RenderPassMultiviewCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( RenderPassMultiviewCreateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", subpassCount = "                      + info.subpassCount +
           ", viewMasks = "                         + :: toStringRegular ( info.subpassCount, info.pViewMasks ) +
           ", dependencyCount = "                   + info.dependencyCount +
           ", viewOffsets = "                       + :: toStringRegular ( info.dependencyCount, info.pViewOffsets ) +
           ", correlationMaskCount = "              + info.correlationMaskCount +
           ", correlationMasks = "                  + :: toStringRegular ( info.correlationMaskCount, info.pCorrelationMasks ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
auto vulkan :: toString (
        Type ( AttachmentDescription2 ) const & description
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( AttachmentDescription2 ) ) " " +
           "{ structureType = "_s                   + toString ( description.structureType ) +
           ", pNext = "                             + engine :: toString ( description.pNext ) +
           ", flags = "                             + :: flagsToString < Type ( AttachmentDescriptionFlag ) > ( description.flags ) +
           ", format = "                            + toString ( description.format ) +
           ", samples = "                           + toString ( description.samples ) +
           ", loadOperation = "                     + toString ( description.loadOperation ) +
           ", storeOperation = "                    + toString ( description.storeOperation ) +
           ", stencilLoadOperation = "              + toString ( description.stencilLoadOperation ) +
           ", stencilStoreOperation = "             + toString ( description.stencilStoreOperation ) +
           ", initialLayout = "                     + toString ( description.initialLayout ) +
           ", finalLayout = "                       + toString ( description.finalLayout ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
auto vulkan :: toString (
        Type ( AttachmentDescriptionStencilLayout ) const & layout
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( AttachmentDescriptionStencilLayout ) ) " " +
           "{ structureType = "_s                   + toString ( layout.structureType ) +
           ", pNext = "                             + engine :: toString ( layout.pNext ) +
           ", stencilInitialLayout = "              + toString ( layout.stencilInitialLayout ) +
           ", stencilFinalLayout = "                + toString ( layout.stencilFinalLayout ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
auto vulkan :: toString (
        Type ( AttachmentReferenceStencilLayout ) const & layout
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( AttachmentReferenceStencilLayout ) ) " " +
           "{ structureType = "_s                   + toString ( layout.structureType ) +
           ", pNext = "                             + engine :: toString ( layout.pNext ) +
           ", stencilLayout = "                     + toString ( layout.stencilLayout ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
auto vulkan :: toString (
        Type ( AttachmentReference2 ) const & reference
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( AttachmentReference2 ) ) " " +
           "{ structureType = "_s                   + toString ( reference.structureType ) +
           ", pNext = "                             + engine :: toString ( reference.pNext ) +
           ", attachment = "                        + reference.attachment +
           ", layout = "                            + toString ( reference.layout ) +
           ", aspectMask = "                        + :: flagsToString < Type ( ImageAspectFlag ) > ( reference.aspectMask ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
auto vulkan :: toString (
        Type ( SubpassDescription2 ) const & description
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( SubpassDescription2 ) ) " " +
           "{ structureType = "_s                   + toString ( description.structureType ) +
           ", pNext = "                             + engine :: toString ( description.pNext ) +
           ", flags = "                             + :: flagsToString < Type ( SubpassDescriptionFlag ) > ( description.flags ) +
           ", pipelineBindPoint = "                 + toString ( description.pipelineBindPoint ) +
           ", viewMask = "                          + description.viewMask +
           ", inputAttachmentCount = "              + description.inputAttachmentCount +
           ", inputAttachments = "                  + :: toStringVulkan ( description.inputAttachmentCount, description.pInputAttachments ) +
           ", colorAttachmentCount = "              + description.colorAttachmentsCount +
           ", colorAttachments = "                  + :: toStringVulkan ( description.colorAttachmentsCount, description.pColorAttachments ) +
           ", resolveAttachments = "                + :: toStringVulkan ( description.colorAttachmentsCount, description.pResolveAttachments ) +
           ", pDepthStencilAttachment = "           + engine :: toString ( description.pDepthStencilAttachment ) +
           ", preserveAttachmentCount = "           + description.preserveAttachmentCount +
           ", preserveAttachments = "               + :: toStringVulkan ( description.preserveAttachmentCount, description.pPreserveAttachments ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
auto vulkan :: toString (
        Type ( SubpassDescriptionDepthStencilResolve ) const & resolve
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( SubpassDescriptionDepthStencilResolve ) ) " " +
           "{ structureType = "_s                   + toString ( resolve.structureType ) +
           ", pNext = "                             + engine :: toString ( resolve.pNext ) +
           ", depthResolveMode = "                  + toString ( resolve.depthResolveMode ) +
           ", stencilResolveMode = "                + toString ( resolve.stencilResolveMode ) +
           ", pDepthStencilResolveAttachment = "    + engine :: toString ( resolve.pDepthStencilResolveAttachment ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
auto vulkan :: toString (
        Type ( SubpassDependency2 ) const & dependency
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( SubpassDependency2 ) ) " " +
           "{ structureType = "_s       + toString ( dependency.structureType ) +
           ", pNext = "                 + engine :: toString ( dependency.pNext ) +
           "{ sourceSubpass = "_s       + dependency.sourceSubpass +
           ", destinationSubpass = "    + dependency.destinationSubpass +
           ", sourceStageMask = "       + :: flagsToString < Type ( PipelineStageFlag ) > ( dependency.sourceStageMask ) +
           ", destinationStageMask = "  + :: flagsToString < Type ( PipelineStageFlag ) > ( dependency.destinationStageMask ) +
           ", sourceAccessMask = "      + :: flagsToString < Type ( AccessFlag ) > ( dependency.sourceAccessMask ) +
           ", destinationAccessMask = " + :: flagsToString < Type ( AccessFlag ) > ( dependency.destinationAccessMask ) +
           ", dependencyFlags = "       + :: flagsToString < Type ( DependencyFlag ) > ( dependency.dependencyFlags ) +
           ", viewOffset = "            + dependency.viewOffset +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
auto vulkan :: toString (
        Type ( RenderPassCreateInfo2 ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( RenderPassCreateInfo2 ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", flags = "                             + :: flagsToString < Type ( RenderPassCreateFlag ) > ( info.flags ) +
           ", attachmentCount = "                   + info.attachmentCount +
           ", attachments = "                       + :: toStringVulkan ( info.attachmentCount, info.pAttachments ) +
           ", subpassCount = "                      + info.subpassCount +
           ", subpasses = "                         + :: toStringVulkan ( info.subpassCount, info.pSubpasses ) +
           ", dependencyCount = "                   + info.dependencyCount +
           ", dependencies = "                      + :: toStringVulkan ( info.dependencyCount, info.pDependencies ) +
           ", correlatedViewMaskCount = "           + info.correlatedViewMaskCount +
           ", correlatedViewMasks = "               + :: toStringRegular ( info.correlatedViewMaskCount, info.pCorrelatedViewMasks ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE
auto vulkan :: toString (
        Type ( FragmentShadingRateAttachmentInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( FragmentShadingRateAttachmentInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", pFragmentShadingRateAttachment = "    + engine :: toString ( info.pFragmentShadingRateAttachment ) +
           ", shadingRateAttachmentTexelSize = "    + toString ( info.shadingRateAttachmentTexelSize ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( FrameBufferCreateFlag ) flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_IMAGELESS_FRAME_BUFFER_AVAILABLE
        case FrameBufferCreateFlagImageless: { asString = "Imageless"; break; }
#endif
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( ImageCreateFlag ) flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case ImageCreateFlagSparseBinding:                      { asString = "SparseBinding";                       break; }
        case ImageCreateFlagSparseResidency:                    { asString = "SparseResidency";                     break; }
        case ImageCreateFlagSparseAliased:                      { asString = "SparseAliased";                       break; }
        case ImageCreateFlagMutableFormat:                      { asString = "MutableFormat";                       break; }
        case ImageCreateFlagCubeCompatible:                     { asString = "CubeCompatible";                      break; }

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
        case ImageCreateFlagAlias:                              { asString = "Alias";                               break; }
        case ImageCreateFlagSplitInstanceBindRegions:           { asString = "SplitInstanceBindRegions";            break; }
        case ImageCreateFlag2DArrayCompatible:                  { asString = "2DArrayCompatible";                   break; }
        case ImageCreateFlagBlockTexelViewCompatible:           { asString = "BlockTexelViewCompatible";            break; }
        case ImageCreateFlagExtendedUsage:                      { asString = "ExtendedUsage";                       break; }
        case ImageCreateFlagProtected:                          { asString = "Protected";                           break; }
        case ImageCreateFlagDisjoint:                           { asString = "Disjoint";                            break; }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CORNER_SAMPLED_IMAGE_AVAILABLE
        case ImageCreateFlagCornerSampledNVidia:                { asString = "CornerSampledNVidia";                 break; }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE
        case ImageCreateFlagSampleLocationsCompatibleDepth:     { asString = "SampleLocationsCompatibleDepth";      break; }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE
        case ImageCreateFlagSubsampled:                         { asString = "Subsampled";                          break; }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE
        case ImageCreateFlagFragmentDensityMapOffsetQualcomm:   { asString = "FragmentDensityMapOffsetQualcomm";    break; }
#endif
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( FrameBufferCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( FrameBufferCreateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", flags = "                             + :: flagsToString < Type ( FrameBufferCreateFlag ) > ( info.flags ) +
           ", renderPass = "                        + engine :: toString ( info.renderPass ) +
           ", attachmentCount = "                   + info.attachmentCount +
           ", attachments = "                       + :: toStringEngine ( info.attachmentCount, info.pAttachments ) +
           ", width = "                             + info.width +
           ", height = "                            + info.height +
           ", layers = "                            + info.layers +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
auto vulkan :: toString (
        Type ( FrameBufferAttachmentImageInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( FrameBufferAttachmentImageInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", flags = "                             + :: flagsToString < Type ( ImageCreateFlag ) > ( info.flags ) +
           ", usage = "                             + toString ( info.usage ) +
           ", width = "                             + info.width +
           ", height = "                            + info.height +
           ", layerCount = "                        + info.layerCount +
           ", viewFormatCount = "                   + info.viewFormatCount +
           ", viewFormats = "                       + :: toStringVulkan ( info.viewFormatCount, info.pViewFormats ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
auto vulkan :: toString (
        Type ( FrameBufferAttachmentsCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( FrameBufferAttachmentsCreateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", attachmentImageInfoCount = "          + info.attachmentImageInfoCount +
           ", attachmentImageInfos = "              + :: toStringVulkan ( info.attachmentImageInfoCount, info.pAttachmentImageInfos ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( SubpassContents ) contents
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( contents ) {
        case SubpassContentsInline:                     { asString = "Inline";                      break; }
        case SubpassContentsSecondaryCommandBuffers:    { asString = "Secondary Command Buffers";   break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( RenderPassBeginInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( RenderPassBeginInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", renderPass = "                        + engine :: toString ( info.renderPass ) +
           ", frameBuffer = "                       + engine :: toString ( info.frameBuffer ) +
           ", renderArea = "                        + toString ( info.renderArea ) +
           ", clearValueCount = "                   + info.clearValueCount +
           ", clearValues = "                       + :: toStringVulkan ( info.clearValueCount, info.pClearValues ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
auto vulkan :: toString (
        Type ( RenderPassAttachmentBeginInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( RenderPassAttachmentBeginInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", attachmentCount = "                   + info.attachmentCount +
           ", attachments = "                       + :: toStringEngine ( info.attachmentCount, info.pAttachments ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE
auto vulkan :: toString (
        Type ( AttachmentSampleLocations ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( AttachmentSampleLocations ) ) " " +
           "{ attachmentIndex = "_s     + info.attachmentIndex +
           ", samplelocationsInfo = "   + toString ( info.sampleLocationsInfo ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE
auto vulkan :: toString (
        Type ( SubpassSampleLocations ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( SubpassSampleLocations ) ) " " +
           "{ subpassIndex = "_s        + info.subpassIndex +
           ", sampleLocationsInfo = "   + toString ( info.sampleLocationsInfo ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE
auto vulkan :: toString (
        Type ( RenderPassSampleLocationsBeginInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( RenderPassSampleLocationsBeginInfo ) ) " " +
           "{ structureType = "_s                       + toString ( info.structureType ) +
           ", pNext = "                                 + engine :: toString ( info.pNext ) +
           ", attachmentInitialSampleLocationsCount = " + info.attachmentInitialSampleLocationsCount +
           ", attachmentInitialSampleLocations = "      + :: toStringVulkan ( info.attachmentInitialSampleLocationsCount, info.pAttachmentInitialSampleLocations ) +
           ", postSubpassSampleLocationsCount = "       + info.postSubpassSampleLocationsCount +
           ", postSubpassSampleLocations = "            + :: toStringVulkan ( info.postSubpassSampleLocationsCount, info.pPostSubpassSampleLocations ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_RENDER_PASS_TRANSFORM_AVAILABLE
auto vulkan :: toString (
        Type ( RenderPassTransformBeginInfoQualcomm ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( RenderPassTransformBeginInfoQualcomm ) ) " " +
           "{ structureType = "_s                       + toString ( info.structureType ) +
           ", pNext = "                                 + engine :: toString ( info.pNext ) +
           ", transform = "                             + toString ( info.transform ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
auto vulkan :: toString (
        Type ( SubpassBeginInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( SubpassBeginInfo ) ) " " +
           "{ structureType = "_s                       + toString ( info.structureType ) +
           ", pNext = "                                 + engine :: toString ( info.pNext ) +
           ", contents = "                              + toString ( info.contents ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
auto vulkan :: toString (
        Type ( SubpassEndInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( SubpassEndInfo ) ) " " +
           "{ structureType = "_s                       + toString ( info.structureType ) +
           ", pNext = "                                 + engine :: toString ( info.pNext ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE
auto vulkan :: toString (
        Type ( SubpassFragmentDensityMapOffsetEndInfoQualcomm ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( SubpassFragmentDensityMapOffsetEndInfoQualcomm ) ) " " +
           "{ structureType = "_s                       + toString ( info.structureType ) +
           ", pNext = "                                 + engine :: toString ( info.pNext ) +
           ", fragmentDensityOffsetCount = "            + info.fragmentDensityOffsetCount +
           ", fragmentDensityOffsets = "                + :: toStringVulkan ( info.fragmentDensityOffsetCount, info.pFragmentDensityOffsets ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( ShaderModuleCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ShaderModuleCreateInfo ) ) " " +
           "{ structureType = "_s                       + toString ( info.structureType ) +
           ", pNext = "                                 + engine :: toString ( info.pNext ) +
           ", flags = "                                 + :: flagsToString ( info.flags ) +
           ", codeSize = "                              + info.codeSize +
           ", pCode = "                                 + engine :: toString ( info.pCode ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_CACHE_AVAILABLE
auto vulkan :: toString (
        Type ( ShaderModuleValidationCacheCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ShaderModuleValidationCacheCreateInfo ) ) " " +
           "{ structureType = "_s                       + toString ( info.structureType ) +
           ", pNext = "                                 + engine :: toString ( info.pNext ) +
           ", validationCache = "                       + engine :: toString ( info.validationCache ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE
auto vulkan :: toString (
        Type ( ComponentTypeNVidia ) type
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( type ) {
        case ComponentTypeNVidiaFloat16:    { asString = "Float 16";        break; }
        case ComponentTypeNVidiaFloat32:    { asString = "Float 32";        break; }
        case ComponentTypeNVidiaFloat64:    { asString = "Float 64";        break; }

        case ComponentTypeNVidiaSInt8:      { asString = "Signed Int 8";    break; }
        case ComponentTypeNVidiaSInt16:     { asString = "Signed Int 16";   break; }
        case ComponentTypeNVidiaSInt32:     { asString = "Signed Int 32";   break; }
        case ComponentTypeNVidiaSInt64:     { asString = "Signed Int 64";   break; }

        case ComponentTypeNVidiaUInt8:      { asString = "Unsigned Int 8";  break; }
        case ComponentTypeNVidiaUInt16:     { asString = "Unsigned Int 16"; break; }
        case ComponentTypeNVidiaUInt32:     { asString = "Unsigned Int 32"; break; }
        case ComponentTypeNVidiaUInt64:     { asString = "Unsigned Int 64"; break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE
auto vulkan :: toString (
        Type ( ScopeNVidia ) scope
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( scope ) {
        case ScopeNVidiaDevice:         { asString = "Device";          break; }
        case ScopeNVidiaWorkgroup:      { asString = "Workgroup";       break; }
        case ScopeNVidiaSubgroup:       { asString = "Subgroup";        break; }
        case ScopeNVidiaQueueFamily:    { asString = "Queue Family";    break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE
auto vulkan :: toString (
        Type ( CooperativeMatrixPropertiesNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( CooperativeMatrixPropertiesNVidia ) ) " " +
           "{ structureType = "_s   + toString ( info.structureType ) +
           ", pNext = "             + engine :: toString ( info.pNext ) +
           ", NSize = "             + toString ( info.NSize ) +
           ", MSize = "             + toString ( info.MSize ) +
           ", KSize = "             + toString ( info.KSize ) +
           ", AType = "             + toString ( info.AType ) +
           ", BType = "             + toString ( info.BType ) +
           ", CType = "             + toString ( info.CType ) +
           ", DType = "             + toString ( info.DType ) +
           ", scope = "             + toString ( info.scope ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_CACHE_AVAILABLE
auto vulkan :: toString (
        Type ( ValidationCacheCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ValidationCacheCreateInfo ) ) " " +
           "{ structureType = "_s   + toString ( info.structureType ) +
           ", pNext = "             + engine :: toString ( info.pNext ) +
           ", flags = "             + :: flagsToString ( info.flags ) +
           ", initialDataSize = "   + info.initialDataSize +
           ", pInitialData = "      + engine :: toString ( info.pInitialData ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineCreateFlag ) scope
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( scope ) {
        case PipelineCreateFlagDisableOptimization:                         { asString = "Disable Optimization";                            break; }
        case PipelineCreateFlagAllowDerivatives:                            { asString = "Allow Derivatives";                               break; }
        case PipelineCreateFlagDerivative:                                  { asString = "Derivative";                                      break; }

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
        case PipelineCreateFlagViewIndexFromDeviceIndex:                    { asString = "View Index From Device Index";                    break; }
        case PipelineCreateFlagDispatchBase:                                { asString = "Dispatch Base";                                   break; }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
        case PipelineCreateFlagFailOnPipelineCompileRequired:               { asString = "Fail On Pipeline Compile Required";               break; }
        case PipelineCreateFlagEarlyReturnOnFailure:                        { asString = "Early Return On Failure";                         break; }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE && ( __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE )
        case PipelineCreateFlagRenderingFragmentShadingRateAttachment:      { asString = "Rendering Fragment Shading Rate Attachment";      break; }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE && ( __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE )
        case PipelineCreateFlagRenderingFragmentDensityMapAttachment:       { asString = "Rendering Fragment Density Map Attachment";       break; }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE
        case PipelineCreateFlagRayTracingNoNullAnyHitShaders:               { asString = "Ray Tracing No Null Any Hit Shaders";             break; }
        case PipelineCreateFlagRayTracingNoNullClosestHitShaders:           { asString = "Ray Tracing No Null Closest Hit Shaders";         break; }
        case PipelineCreateFlagRayTracingNoNullMissShaders:                 { asString = "Ray Tracing No Null Miss Shaders";                break; }
        case PipelineCreateFlagRayTracingNoNullIntersectionShaders:         { asString = "Ray Tracing No Null Intersection Shaders";        break; }
        case PipelineCreateFlagRayTracingSkipTriangles:                     { asString = "Ray Tracing Skip Triangles";                      break; }
        case PipelineCreateFlagRayTracingSkipAABBS:                         { asString = "Ray Tracing Skip AABBS";                          break; }
        case PipelineCreateFlagRayTracingShaderGroupHandleCaptureReplay:    { asString = "Ray Tracing Shader Group Handle Capture Replay";  break; }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
        case PipelineCreateFlagDeferCompileNVidia:                          { asString = "Defer Compile NVidia";                            break; }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
        case PipelineCreateFlagCaptureStatistics:                           { asString = "Capture Statistics";                              break; }
        case PipelineCreateFlagCaptureInternalRepresentations:              { asString = "Capture Internal Representations";                break; }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE
        case PipelineCreateFlagIndirectBindableNVidia:                      { asString = "Indirect Bindable NVidia";                        break; }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_LIBRARY_AVAILABLE
        case PipelineCreateFlagLibrary:                                     { asString = "Library";                                         break; }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE
        case PipelineCreateFlagRayTracingAllowMotionNVidia:                 { asString = "Ray Tracing Allow Motion NVidia";                 break; }
#endif

    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineShaderStageCreateFlag ) scope
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( scope ) {
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE
        case PipelineShaderStageCreateFlagAllowVaryingSubgroupSize: { asString = "Allow Varying Subgroup Size"; break; }
        case PipelineShaderStageCreateFlagRequireFullSubgroups:     { asString = "Require Full Subgroups";      break; }
#endif
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( SpecializationMapEntry ) const & entry
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( SpecializationMapEntry ) ) " " +
           "{ constantID = "_s  + entry.constantID +
           ", offset = "        + entry.offset +
           ", size = "          + entry.size +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( SpecializationInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( SpecializationInfo ) ) " " +
           "{ mapEntryCount = "_s   + info.mapEntryCount +
           ", mapEntries = "        + :: toStringVulkan ( info.mapEntryCount, info.pMapEntries ) +
           ", dataSize = "          + info.dataSize +
           ", pData = "             + engine :: toString ( info.pData ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineShaderStageCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineShaderStageCreateInfo ) ) " " +
           "{ structureType = "_s       + toString ( info.structureType ) +
           ", pNext = "                 + engine :: toString ( info.pNext ) +
           ", flags = "                 + :: flagsToString < Type ( PipelineShaderStageCreateFlag ) > ( info.flags ) +
           ", stage = "                 + toString ( info.stage ) +
           ", module = "                + engine :: toString ( info.module ) +
           ", name = "                  + info.pName +
           ", pSpecializationInfo = "   + engine :: toString ( info.pSpecializationInfo ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( ComputePipelineCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ComputePipelineCreateInfo ) ) " " +
           "{ structureType = "_s       + toString ( info.structureType ) +
           ", pNext = "                 + engine :: toString ( info.pNext ) +
           ", flags = "                 + :: flagsToString ( info.flags ) +
           ", stage = "                 + toString ( info.stage ) +
           ", layout = "                + engine :: toString ( info.layout ) +
           ", basePipelineHandle = "    + engine :: toString ( info.basePipelineHandle ) +
           ", basePipelineIndex = "     + info.basePipelineIndex +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_PIPELINE_COMPILER_CONTROL_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineCompilerControlFlagAMD ) flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    (void) flag;

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_PIPELINE_COMPILER_CONTROL_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineCompilerControlCreateInfoAMD ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineCompilerControlCreateInfoAMD ) ) " " +
           "{ structureType = "_s       + toString ( info.structureType ) +
           ", pNext = "                 + engine :: toString ( info.pNext ) +
           ", compilerControlFlags = "  + :: flagsToString < Type ( PipelineCompilerControlFlagAMD ) > ( info.compilerControlFlags ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_FEEDBACK_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineCreationFeedbackFlag ) flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case PipelineCreationFeedbackFlagValid:                     { asString = "Valid";                       break; }
        case PipelineCreationFeedbackFlagApplicationPipelineCache:  { asString = "Application Pipeline Cache";  break; }
        case PipelineCreationFeedbackFlagBasePipelineAcceleration:  { asString = "Base Pipeline Acceleration";  break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_FEEDBACK_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineCreationFeedback ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineCreationFeedback ) ) " " +
           "{ flags = "_s   + :: flagsToString < Type ( PipelineCreationFeedbackFlag ) > ( info.flags ) +
           ", duration = "  + info.duration +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_FEEDBACK_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineCreationFeedbackCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineCreationFeedbackCreateInfo ) ) " " +
           "{ structureType = "_s                       + toString ( info.structureType ) +
           ", pNext = "                                 + engine :: toString ( info.pNext ) +
           ", pPipelineCreationFeedback = "             + engine :: toString ( info.pPipelineCreationFeedback ) +
           ", pipelineStageCreationFeedbackCount = "    + info.pipelineStageCreationFeedbackCount +
           ", pipelineStageCreationFeedbacks = "        + :: toStringVulkan ( info.pipelineStageCreationFeedbackCount, info.pPipelineStageCreationFeedbacks ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE
auto vulkan :: toString (
        Type ( SubpassShadingPipelineCreateInfoHuawei ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( SubpassShadingPipelineCreateInfoHuawei ) ) " " +
           "{ structureType = "_s   + toString ( info.structureType ) +
           ", pNext = "             + engine :: toString ( info.pNext ) +
           ", renderPass = "        + engine :: toString ( info.renderPass ) +
           ", subpass = "           + info.subpass +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineShaderStageRequiredSubgroupSizeCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineShaderStageRequiredSubgroupSizeCreateInfo ) ) " " +
           "{ structureType = "_s       + toString ( info.structureType ) +
           ", pNext = "                 + engine :: toString ( info.pNext ) +
           ", requiredSubgroupSize = "  + info.requiredSubgroupSize +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( VertexInputRate ) rate
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( rate ) {
        case VertexInputRateVertex:     { asString = "Vertex";      break; }
        case VertexInputRateInstance:   { asString = "Instance";    break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISCARD_RECTANGLES_AVAILABLE
auto vulkan :: toString (
        Type ( DiscardRectangleMode ) mode
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( mode ) {
        case DiscardRectangleModeInclusive: { asString = "Inclusive";   break; }
        case DiscardRectangleModeExclusive: { asString = "Exclusive";   break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE
auto vulkan :: toString (
        Type ( FragmentShadingRateNVidia ) rate
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( rate ) {
        case FragmentShadingRateNVidia1InvocationPerPixel:      { asString = "1 Invocation Per Pixel";      break; }
        case FragmentShadingRateNVidia1InvocationPer1x2Pixels:  { asString = "1 Invocation Per 1x2 Pixels"; break; }
        case FragmentShadingRateNVidia1InvocationPer2x1Pixels:  { asString = "1 Invocation Per 2x1 Pixels"; break; }
        case FragmentShadingRateNVidia1InvocationPer2x2Pixels:  { asString = "1 Invocation Per 2x2 Pixels"; break; }
        case FragmentShadingRateNVidia1InvocationPer4x2Pixels:  { asString = "1 Invocation Per 4x2 Pixels"; break; }
        case FragmentShadingRateNVidia1InvocationPer2x4Pixels:  { asString = "1 Invocation Per 2x4 Pixels"; break; }
        case FragmentShadingRateNVidia1InvocationPer4x4Pixels:  { asString = "1 Invocation Per 4x4 Pixels"; break; }
        case FragmentShadingRateNVidia2InvocationsPerPixel:     { asString = "2 Invocations Per Pixel";     break; }
        case FragmentShadingRateNVidia4InvocationsPerPixel:     { asString = "4 Invocations Per Pixel";     break; }
        case FragmentShadingRateNVidia8InvocationsPerPixel:     { asString = "8 Invocations Per Pixel";     break; }
        case FragmentShadingRateNVidia16InvocationsPerPixel:    { asString = "16 Invocations Per Pixel";    break; }
        case FragmentShadingRateNVidiaNoInvocations:            { asString = "No Invocations";              break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE
auto vulkan :: toString (
        Type ( FragmentShadingRateTypeNVidia ) type
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( type ) {
        case FragmentShadingRateTypeNVidiaFragmentSize: { asString = "Fragment Size";   break; }
        case FragmentShadingRateTypeNVidiaEnums:        { asString = "Enums";           break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE
auto vulkan :: toString (
        Type ( FragmentShadingRateCombinerOperation ) operation
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( operation ) {
        case FragmentShadingRateCombinerOperationKeep:      { asString = "Keep";    break; }
        case FragmentShadingRateCombinerOperationReplace:   { asString = "Replace"; break; }
        case FragmentShadingRateCombinerOperationMin:       { asString = "Min";     break; }
        case FragmentShadingRateCombinerOperationMax:       { asString = "Max";     break; }
        case FragmentShadingRateCombinerOperationMul:       { asString = "Mul";     break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( PrimitiveTopology ) topology
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( topology ) {
        case PrimitiveTopologyPointList:                    { asString = "Point List";                      break; }
        case PrimitiveTopologyLineList:                     { asString = "Line List";                       break; }
        case PrimitiveTopologyLineStrip:                    { asString = "Line Strip";                      break; }
        case PrimitiveTopologyTriangleList:                 { asString = "Triangle List";                   break; }
        case PrimitiveTopologyTriangleStrip:                { asString = "Triangle Strip";                  break; }
        case PrimitiveTopologyTriangleFan:                  { asString = "Triangle Fan";                    break; }
        case PrimitiveTopologyLineListWithAdjacency:        { asString = "Line List With Adjacency";        break; }
        case PrimitiveTopologyLineStripWithAdjacency:       { asString = "Line Strip With Adjacency";       break; }
        case PrimitiveTopologyTriangleListWithAdjacency:    { asString = "Triangle List With Adjacency";    break; }
        case PrimitiveTopologyTriangleStripWithAdjacency:   { asString = "Triangle Strip With Adjacency";   break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( PolygonMode ) mode
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( mode ) {
        case PolygonModeFill:                   { asString = "Polygon Mode Fill";           break; }
        case PolygonModeLine:                   { asString = "Polygon Mode Line";           break; }
        case PolygonModePoint:                  { asString = "Polygon Mode Point";          break; }
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FILL_RECTANGLE_AVAILABLE
        case PolygonModeFillRectangleNVidia:    { asString = "Polygon Mode Fill Rectangle"; break; }
#endif
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( CullModeFlag ) flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case CullModeFlagNone:          { asString = "None";            break; }
        case CullModeFlagFront:         { asString = "Front";           break; }
        case CullModeFlagBack:          { asString = "Back";            break; }
        case CullModeFlagFrontAndBack:  { asString = "Front And Back";  break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( FrontFace ) face
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( face ) {
        case FrontFaceClockwise:        { asString = "Clockwise";           break; }
        case FrontFaceCounterClockwise: { asString = "Counter Clockwise";   break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( CompareOperation ) operation
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( operation ) {
        case CompareOperationNever:             { asString = "Never";               break; }
        case CompareOperationLess:              { asString = "Less";                break; }
        case CompareOperationEqual:             { asString = "Equal";               break; }
        case CompareOperationLessOrEqual:       { asString = "Less Or Equal";       break; }
        case CompareOperationGreater:           { asString = "Greater";             break; }
        case CompareOperationNotEqual:          { asString = "Not Equal";           break; }
        case CompareOperationGreaterOrEqual:    { asString = "Greater Or Equal";    break; }
        case CompareOperationAlways:            { asString = "Always";              break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( StencilOperation ) operation
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( operation ) {
        case StencilOperationKeep:              { asString = "Keep";                break; }
        case StencilOperationZero:              { asString = "Zero";                break; }
        case StencilOperationReplace:           { asString = "Replace";             break; }
        case StencilOperationIncrementAndClamp: { asString = "Increment And Clamp"; break; }
        case StencilOperationDecrementAndClamp: { asString = "Decrement And Clamp"; break; }
        case StencilOperationInvert:            { asString = "Invert";              break; }
        case StencilOperationIncrementAndWrap:  { asString = "Increment And Wrap";  break; }
        case StencilOperationDecrementAndWrap:  { asString = "Decrement And Wrap";  break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( LogicOperation ) operation
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( operation ) {
        case LogicOperationClear:           { asString = "Clear";           break; }
        case LogicOperationAnd:             { asString = "And";             break; }
        case LogicOperationAndReverse:      { asString = "AndReverse";      break; }
        case LogicOperationCopy:            { asString = "Copy";            break; }
        case LogicOperationAndInverted:     { asString = "AndInverted";     break; }
        case LogicOperationNoOperation:     { asString = "NoOperation";     break; }
        case LogicOperationXor:             { asString = "Xor";             break; }
        case LogicOperationOr:              { asString = "Or";              break; }
        case LogicOperationNor:             { asString = "Nor";             break; }
        case LogicOperationEquivalent:      { asString = "Equivalent";      break; }
        case LogicOperationInvert:          { asString = "Invert";          break; }
        case LogicOperationOrReverse:       { asString = "OrReverse";       break; }
        case LogicOperationCopyInverted:    { asString = "CopyInverted";    break; }
        case LogicOperationOrInverted:      { asString = "OrInverted";      break; }
        case LogicOperationNand:            { asString = "Nand";            break; }
        case LogicOperationSet:             { asString = "Set";             break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineColorBlendStateCreateFlag ) flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
#if __C_ENG_VULKAN_API_EXTENSION_ARM_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_AVAILABLE
        case PipelineColorBlendStateCreateFlagRasterizationOrderAttachmentAccessARM:    { asString = "Rasterization Order Attachment Access";   break; }
#endif
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( ColorComponentFlag ) flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case ColorComponentFlagR:   { asString = "Red";     break; }
        case ColorComponentFlagG:   { asString = "Green";   break; }
        case ColorComponentFlagB:   { asString = "Blue";    break; }
        case ColorComponentFlagA:   { asString = "Alpha";   break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( BlendFactor ) flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case BlendFactorZero:                       { asString = "Zero";                        break; }
        case BlendFactorOne:                        { asString = "One";                         break; }
        case BlendFactorSourceColor:                { asString = "Source Color";                break; }
        case BlendFactorOneMinusSourceColor:        { asString = "One Minus Source Color";      break; }
        case BlendFactorDestinationColor:           { asString = "Destination Color";           break; }
        case BlendFactorOneMinusDestinationColor:   { asString = "One Minus Destination Color"; break; }
        case BlendFactorSourceAlpha:                { asString = "Source Alpha";                break; }
        case BlendFactorOneMinusSourceAlpha:        { asString = "One Minus Source Alpha";      break; }
        case BlendFactorDestinationAlpha:           { asString = "Destination Alpha";           break; }
        case BlendFactorOneMinusDestinationAlpha:   { asString = "One Minus Destination Alpha"; break; }
        case BlendFactorConstantColor:              { asString = "Constant Color";              break; }
        case BlendFactorOneMinusConstantColor:      { asString = "One Minus Constant Color";    break; }
        case BlendFactorConstantAlpha:              { asString = "Constant Alpha";              break; }
        case BlendFactorOneMinusConstantAlpha:      { asString = "One Minus Constant Alpha";    break; }
        case BlendFactorAlphaSaturate:              { asString = "Alpha Saturate";              break; }
        case BlendFactorSource1Color:               { asString = "Source1 Color";               break; }
        case BlendFactorOneMinusSource1Color:       { asString = "One Minus Source1 Color";     break; }
        case BlendFactorSource1Alpha:               { asString = "Source1 Alpha";               break; }
        case BlendFactorOneMinusSource1Alpha:       { asString = "One Minus Source1 Alpha";     break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( BlendOperation ) operation
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( operation ) {
        case BlendOperationAdd:                 { asString = "Add";                     break; }
        case BlendOperationSubtract:            { asString = "Subtract";                break; }
        case BlendOperationReverseSubtract:     { asString = "Reverse Subtract";        break; }
        case BlendOperationMin:                 { asString = "Min";                     break; }
        case BlendOperationMax:                 { asString = "Max";                     break; }
#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE
        case BlendOperationZero:                { asString = "Zero";                    break; }
        case BlendOperationSource:              { asString = "Source";                  break; }
        case BlendOperationDestination:         { asString = "Destination";             break; }
        case BlendOperationSourceOver:          { asString = "Source Over";             break; }
        case BlendOperationDestinationOver:     { asString = "Destination Over";        break; }
        case BlendOperationSourceIn:            { asString = "Source In";               break; }
        case BlendOperationDestinationIn:       { asString = "Destination In";          break; }
        case BlendOperationSourceOut:           { asString = "Source Out";              break; }
        case BlendOperationDestinationOut:      { asString = "Destination Out";         break; }
        case BlendOperationSourceAtop:          { asString = "Source Atop";             break; }
        case BlendOperationDestinationAtop:     { asString = "Destination Atop";        break; }
        case BlendOperationXor:                 { asString = "Xor";                     break; }
        case BlendOperationMultiply:            { asString = "Multiply";                break; }
        case BlendOperationScreen:              { asString = "Screen";                  break; }
        case BlendOperationOverlay:             { asString = "Overlay";                 break; }
        case BlendOperationDarken:              { asString = "Darken";                  break; }
        case BlendOperationLighten:             { asString = "Lighten";                 break; }
        case BlendOperationColorDodge:          { asString = "Color Dodge";             break; }
        case BlendOperationColorBurn:           { asString = "Color Burn";              break; }
        case BlendOperationHardLight:           { asString = "Hard Light";              break; }
        case BlendOperationSoftLight:           { asString = "Soft Light";              break; }
        case BlendOperationDifference:          { asString = "Difference";              break; }
        case BlendOperationExclusion:           { asString = "Exclusion";               break; }
        case BlendOperationInvert:              { asString = "Invert";                  break; }
        case BlendOperationInvertRGB:           { asString = "Invert RGB";              break; }
        case BlendOperationLinearDodge:         { asString = "Linear Dodge";            break; }
        case BlendOperationLinearBurn:          { asString = "Linear Burn";             break; }
        case BlendOperationVividLight:          { asString = "Vivid Light";             break; }
        case BlendOperationLinearLight:         { asString = "Linear Light";            break; }
        case BlendOperationPinLight:            { asString = "Pin Light";               break; }
        case BlendOperationHardMix:             { asString = "Hard Mix";                break; }
        case BlendOperationHSLHue:              { asString = "HSL Hue";                 break; }
        case BlendOperationHSLSaturation:       { asString = "HSL Saturation";          break; }
        case BlendOperationHSLColor:            { asString = "HSL Color";               break; }
        case BlendOperationHSLLuminosity:       { asString = "HSL Luminosity";          break; }
        case BlendOperationPlus:                { asString = "Plus";                    break; }
        case BlendOperationPlusClamped:         { asString = "Plus Clamped";            break; }
        case BlendOperationPlusClampedAlpha:    { asString = "Plus Clamped Alpha";      break; }
        case BlendOperationPlusDarker:          { asString = "Plus Darker";             break; }
        case BlendOperationMinus:               { asString = "Minus";                   break; }
        case BlendOperationMinusClamped:        { asString = "Minus Clamped";           break; }
        case BlendOperationContrast:            { asString = "Contrast";                break; }
        case BlendOperationInvertedOVG:         { asString = "Inverted OVG";            break; }
        case BlendOperationRed:                 { asString = "Red";                     break; }
        case BlendOperationGreen:               { asString = "Green";                   break; }
        case BlendOperationBlue:                { asString = "Blue";                    break; }
#endif
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( DynamicState ) state
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( state ) {
        case DynamicStateViewport:                          { asString = "Viewport";                        break; }
        case DynamicStateScissor:                           { asString = "Scissor";                         break; }
        case DynamicStateLineWidth:                         { asString = "Line Width";                      break; }
        case DynamicStateDepthBias:                         { asString = "Depth Bias";                      break; }
        case DynamicStateBlendConstants:                    { asString = "Blend Constants";                 break; }
        case DynamicStateDepthBounds:                       { asString = "Depth Bounds";                    break; }
        case DynamicStateCompareMask:                       { asString = "Compare Mask";                    break; }
        case DynamicStateWriteMask:                         { asString = "Write Mask";                      break; }
        case DynamicStateReference:                         { asString = "Reference";                       break; }
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE
        case DynamicStateCullMode:                          { asString = "Cull Mode";                       break; }
        case DynamicStatePrimitiveTopology:                 { asString = "Primitive Topology";              break; }
        case DynamicStateViewportWithCount:                 { asString = "Viewport With Count";             break; }
        case DynamicStateScissorWithCount:                  { asString = "Scissor With Count";              break; }
        case DynamicStateVertexInputBindingString:          { asString = "Vertex Input Binding String";     break; }
        case DynamicStateDepthTestEnable:                   { asString = "Depth Test Enable";               break; }
        case DynamicStateDepthWriteEnable:                  { asString = "Depth Write Enable";              break; }
        case DynamicStateDepthCompareOperation:             { asString = "Depth Compare Operation";         break; }
        case DynamicStateDepthBoundsTestEnable:             { asString = "Depth Bounds Test Enable";        break; }
        case DynamicStateStencilTestEnable:                 { asString = "Stencil Test Enable";             break; }
        case DynamicStateRasterizerDiscardEnable:           { asString = "Rasterizer Discard Enable";       break; }
#endif
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_2_AVAILABLE
        case DynamicStateStencilOperation:                  { asString = "Stencil Operation";               break; }
        case DynamicStateDepthBiasEnable:                   { asString = "Depth Bias Enable";               break; }
        case DynamicStatePrimitiveRestartEnable:            { asString = "Primitive Restart Enable";        break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CLIP_SPACE_W_SCALING_AVAILABLE
        case DynamicStateViewportWScalingNVidia:            { asString = "Viewport W Scaling";              break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_DISCARD_RECTANGLES_AVAILABLE
        case DynamicStateDiscardRectangle:                  { asString = "Discard Rectangle";               break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE
        case DynamicStateSampleLocations:                   { asString = "Sample Locations";                break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
        case DynamicStateRayTracingPipelineStackSize:       { asString = "Ray Tracing Pipeline Stack Size"; break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE
        case DynamicStateViewportShadingRatePaletteNVidia:  { asString = "Viewport Shading Rate Palette";   break; }
        case DynamicStateViewportCoarseSampleOrderNVidia:   { asString = "Viewport Coarse Sample Order";    break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SCISSOR_EXCLUSIVE_AVAILABLE
        case DynamicStateExclusiveScissorNVidia:            { asString = "Exclusive Scissor";               break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE
        case DynamicStateFragmentShadingRate:               { asString = "Fragment Shading Rate";           break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE
        case DynamicStateLineStipple:                       { asString = "Line Stipple";                    break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_INPUT_DYNAMIC_STATE_AVAILABLE
        case DynamicStateVertexInput:                       { asString = "Vertex Input";                    break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_2_AVAILABLE
        case DynamicStatePatchControlPoints:                { asString = "Patch Control Points";            break; }
        case DynamicStateLogicOperation:                    { asString = "Logic Operation";                 break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_COLOR_WRITE_ENABLE_AVAILABLE
        case DynamicStateColorWriteEnable:                  { asString = "Color Write Enable";              break; }
#endif
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto vulkan :: toString (
        Type ( TessellationDomainOrigin ) origin
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( origin ) {
        case TessellationDomainOriginLowerLeft:   { asString = "Lower Left";   break; }
        case TessellationDomainOriginUpperLeft:   { asString = "Upper Left";   break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE
auto vulkan :: toString (
        Type ( CoarseSampleOrderTypeNVidia ) type
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( type ) {
        case CoarseSampleOrderTypeNVidiaCustom:         { asString = "Custom";          break; }
        case CoarseSampleOrderTypeNVidiaDefault:        { asString = "Default";         break; }
        case CoarseSampleOrderTypeNVidiaPixelMajor:     { asString = "Pixel Major";     break; }
        case CoarseSampleOrderTypeNVidiaSampleMajor:    { asString = "Sample Major";    break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE
auto vulkan :: toString (
        Type ( ShadingRatePaletteEntryNVidia ) type
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( type ) {
        case ShadingRatePaletteEntryNVidiaNoInvocations:                { asString = "No Invocations";              break; }
        case ShadingRatePaletteEntryNVidia16InvocationsPerPixel:        { asString = "16 Invocations Per Pixel";    break; }
        case ShadingRatePaletteEntryNVidia8InvocationsPerPixel:         { asString = "8 Invocations Per Pixel";     break; }
        case ShadingRatePaletteEntryNVidia4InvocationsPerPixel:         { asString = "4 Invocations Per Pixel";     break; }
        case ShadingRatePaletteEntryNVidia2InvocationsPerPixel:         { asString = "2 Invocations Per Pixel";     break; }
        case ShadingRatePaletteEntryNVidia1InvocationPerPixel:          { asString = "1 Invocation Per Pixel";      break; }
        case ShadingRatePaletteEntryNVidia1InvocationPer2x1Pixels:      { asString = "1 Invocation Per 2x1 Pixels"; break; }
        case ShadingRatePaletteEntryNVidia1InvocationPer1x2Pixels:      { asString = "1 Invocation Per 1x2 Pixels"; break; }
        case ShadingRatePaletteEntryNVidia1InvocationPer2x2Pixels:      { asString = "1 Invocation Per 2x2 Pixels"; break; }
        case ShadingRatePaletteEntryNVidia1InvocationPer4x2Pixels:      { asString = "1 Invocation Per 4x2 Pixels"; break; }
        case ShadingRatePaletteEntryNVidia1InvocationPer2x4Pixels:      { asString = "1 Invocation Per 2x4 Pixels"; break; }
        case ShadingRatePaletteEntryNVidia1InvocationPer4x4Pixels:      { asString = "1 Invocation Per 4x4 Pixels"; break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_VIEWPORT_SWIZZLE_AVAILABLE
auto vulkan :: toString (
        Type ( ViewportCoordinateSwizzleNVidia ) type
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( type ) {
        case ViewportCoordinateSwizzleNVidiaPositiveX: { asString = "Positive X"; break; }
        case ViewportCoordinateSwizzleNVidiaNegativeX: { asString = "Negative X"; break; }
        case ViewportCoordinateSwizzleNVidiaPositiveY: { asString = "Positive Y"; break; }
        case ViewportCoordinateSwizzleNVidiaNegativeY: { asString = "Negative Y"; break; }
        case ViewportCoordinateSwizzleNVidiaPositiveZ: { asString = "Positive Z"; break; }
        case ViewportCoordinateSwizzleNVidiaNegativeZ: { asString = "Negative Z"; break; }
        case ViewportCoordinateSwizzleNVidiaPositiveW: { asString = "Positive W"; break; }
        case ViewportCoordinateSwizzleNVidiaNegativeW: { asString = "Negative W"; break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONSERVATIVE_RASTERIZATION_AVAILABLE
auto vulkan :: toString (
        Type ( ConservativeRasterizationMode ) mode
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( mode ) {
        case ConservativeRasterizationModeDisabled:         { asString = "Disabled";        break; }
        case ConservativeRasterizationModeOverestimate:     { asString = "Overestimate";    break; }
        case ConservativeRasterizationModeUnderestimate:    { asString = "Underestimate";   break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE
auto vulkan :: toString (
        Type ( LineRasterizationMode ) mode
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( mode ) {
        case LineRasterizationModeDefault:              { asString = "Default";             break; }
        case LineRasterizationModeRectangular:          { asString = "Rectangular";         break; }
        case LineRasterizationModeBresenham:            { asString = "Bresenham";           break; }
        case LineRasterizationModeRectangularSmooth:    { asString = "Rectangular Smooth";  break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE
auto vulkan :: toString (
        Type ( ProvokingVertexMode ) mode
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( mode ) {
        case ProvokingVertexModeFirstVertex:    { asString = "First Vertex";    break; }
        case ProvokingVertexModeLastVertex:     { asString = "Last Vertex";     break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_RASTERIZATION_ORDER_AVAILABLE
auto vulkan :: toString (
        Type ( RasterizationOrderAMD ) mode
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( mode ) {
        case RasterizationOrderAMDRelaxed:    { asString = "Relaxed";    break; }
        case RasterizationOrderAMDStrict:     { asString = "Strict";     break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAMEBUFFER_MIXED_SAMPLES_AVAILABLE
auto vulkan :: toString (
        Type ( CoverageModulationModeNVidia ) mode
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( mode ) {
        case CoverageModulationModeNVidiaNone:  { asString = "None";    break; }
        case CoverageModulationModeNVidiaRGB:   { asString = "RGB";     break; }
        case CoverageModulationModeNVidiaAlpha: { asString = "Alpha";   break; }
        case CoverageModulationModeNVidiaRGBA:  { asString = "RGBA";    break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COVERAGE_REDUCTION_MODE_AVAILABLE
auto vulkan :: toString (
        Type ( CoverageReductionModeNVidia ) mode
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( mode ) {
        case CoverageReductionModeNVidiaMerge:      { asString = "Merge";       break; }
        case CoverageReductionModeNVidiaTruncate:   { asString = "Truncate";    break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE
auto vulkan :: toString (
        Type ( BlendOverlap ) overlap
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( overlap ) {
        case BlendOverlapConjoint:      { asString = "Conjoint";        break; }
        case BlendOverlapDisjoint:      { asString = "Disjoint";        break; }
        case BlendOverlapUncorrelated:  { asString = "Uncorrelated";    break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( VertexInputBindingDescription ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( VertexInputBindingDescription ) ) " " +
           "{ binding = "_s + info.binding +
           ", stride = "    + info.stride +
           ", inputRate = " + toString ( info.inputRate ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( VertexInputAttributeDescription ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( VertexInputAttributeDescription ) ) " " +
           "{ location = "_s    + info.location +
           ", binding = "       + info.binding +
           ", format = "        + toString ( info.format ) +
           ", offset = "        + info.offset +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineVertexInputStateCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineVertexInputStateCreateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", flags = "                             + :: flagsToString ( info.flags ) +
           ", vertexBindingDescriptionCount = "     + info.vertexBindingDescriptionCount +
           ", VertexBindingDescriptions = "         + :: toStringVulkan ( info.vertexBindingDescriptionCount, info.pVertexBindingDescriptions ) +
           ", vertexAttributeDescriptionCount = "   + info.vertexAttributeDescriptionCount +
           ", VertexAttributeDescriptions = "       + :: toStringVulkan ( info.vertexAttributeDescriptionCount, info.pVertexAttributeDescriptions ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineInputAssemblyStateCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineInputAssemblyStateCreateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", flags = "                             + :: flagsToString ( info.flags ) +
           ", topology = "                          + toString ( info.topology ) +
           ", primitiveRestartEnable = "            + ( info.primitiveRestartEnable == VK_TRUE ? "true" : "false" ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineTessellationStateCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineTessellationStateCreateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", flags = "                             + :: flagsToString ( info.flags ) +
           ", patchControlPoints = "                + info.patchControlPoints +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineViewportStateCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineViewportStateCreateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", flags = "                             + :: flagsToString ( info.flags ) +
           ", viewportCount = "                     + info.viewportCount +
           ", viewports = "                         + :: toStringVulkan ( info.viewportCount, info.pViewports ) +
           ", scissorCount = "                      + info.scissorCount +
           ", scissors = "                          + :: toStringVulkan ( info.scissorCount, info.pScissors ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineRasterizationStateCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineRasterizationStateCreateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", flags = "                             + :: flagsToString ( info.flags ) +
           ", depthClampEnable = "                  + ( info.depthClampEnable == VK_TRUE ? "true" : "false" ) +
           ", rasterizerDiscardEnable = "           + ( info.rasterizerDiscardEnable == VK_TRUE ? "true" : "false" ) +
           ", polygonMode = "                       + toString ( info.polygonMode ) +
           ", cullMode = "                          + :: flagsToString < Type ( CullModeFlag ) > ( info.cullMode ) +
           ", frontFace = "                         + toString ( info.frontFace ) +
           ", depthBiasEnable = "                   + ( info.depthBiasEnable == VK_TRUE ? "true" : "false" ) +
           ", depthBiasConstantFactor = "           + info.depthBiasConstantFactor +
           ", depthBiasClamp = "                    + info.depthBiasClamp +
           ", depthBiasSlopeFactor = "              + info.depthBiasSlopeFactor +
           ", lineWidth = "                         + info.lineWidth +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineMultisampleStateCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineMultisampleStateCreateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", flags = "                             + :: flagsToString ( info.flags ) +
           ", rasterizationSamples = "              + toString ( info.rasterizationSamples ) +
           ", sampleShadingEnable = "               + ( info.sampleShadingEnable == VK_TRUE ? "true" : "false" ) +
           ", minSampleShading = "                  + info.minSampleShading +
           ", pSampleMask = "                       + engine :: toString ( info.pSampleMask ) +
           ", alphaToCoverageEnable = "             + ( info.alphaToCoverageEnable == VK_TRUE ? "true" : "false" ) +
           ", alphaToOneEnable = "                  + ( info.alphaToOneEnable == VK_TRUE ? "true" : "false" ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( StencilOperationState ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( StencilOperationState ) ) " " +
           "{ failOperation = "_s       + toString ( info.failOperation ) +
           ", passOperation = "         + toString ( info.passOperation ) +
           ", depthFailOperation = "    + toString ( info.depthFailOperation ) +
           ", compareOperation = "      + toString ( info.compareOperation ) +
           ", compareMask = "           + info.compareMask +
           ", writeMask = "             + info.writeMask +
           ", reference = "             + info.reference +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineDepthStencilStateCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineDepthStencilStateCreateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", flags = "                             + :: flagsToString < Type ( PipelineDepthStencilStateCreateFlag ) > ( info.flags ) +
           ", depthTestEnable = "                   + ( info.depthTestEnable == VK_TRUE ? "true" : "false" ) +
           ", depthWriteEnable = "                  + ( info.depthWriteEnable == VK_TRUE ? "true" : "false" ) +
           ", depthCompareOperation = "             + toString ( info.depthCompareOperation ) +
           ", depthBoundsTestEnable = "             + ( info.depthBoundsTestEnable == VK_TRUE ? "true" : "false" ) +
           ", stencilTestEnable = "                 + ( info.stencilTestEnable == VK_TRUE ? "true" : "false" ) +
           ", front = "                             + toString ( info.front ) +
           ", back = "                              + toString ( info.back ) +
           ", minDepthBounds = "                    + info.minDepthBounds +
           ", maxDepthBounds = "                    + info.maxDepthBounds +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineColorBlendAttachmentState ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineColorBlendAttachmentState ) ) " " +
           "{ blendEnable = "_s                   + ( info.blendEnable == VK_TRUE ? "true" : "false" ) +
           ", sourceColorBlendFactor = "          + toString ( info.sourceColorBlendFactor ) +
           ", destinationColorBlendFactor = "     + toString ( info.destinationColorBlendFactor ) +
           ", colorBlendOperation = "             + toString ( info.colorBlendOperation ) +
           ", sourceAlphaBlendFactor = "          + toString ( info.sourceAlphaBlendFactor ) +
           ", destinationAlphaBlendFactor = "     + toString ( info.destinationAlphaBlendFactor ) +
           ", alphaBlendOperation = "             + toString ( info.alphaBlendOperation ) +
           ", colorWriteMask = "                  + :: flagsToString < Type ( ColorComponentFlag ) > ( info.colorWriteMask ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineColorBlendStateCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineColorBlendStateCreateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", flags = "                             + :: flagsToString < Type ( PipelineColorBlendStateCreateFlag ) > ( info.flags ) +
           ", logicOperationEnable = "              + ( info.logicOperationEnable == VK_TRUE ? "true" : "false" ) +
           ", logicOperation = "                    + toString ( info.logicOperation ) +
           ", attachmentCount = "                   + info.attachmentCount +
           ", attachments = "                       + :: toStringVulkan ( info.attachmentCount, info.pAttachments ) +
           ", blendConstants = "                    + :: toStringRegular ( 4, & info.blendConstants[0] ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineDynamicStateCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineDynamicStateCreateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", flags = "                             + :: flagsToString ( info.flags ) +
           ", dynamicStateCount = "                 + info.dynamicStateCount +
           ", dynamicStates = "                     + :: toStringVulkan ( info.dynamicStateCount, info.pDynamicStates ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( GraphicsPipelineCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( GraphicsPipelineCreateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", flags = "                             + :: flagsToString < Type ( PipelineCreateFlag ) > ( info.flags ) +
           ", stageCount = "                        + info.stageCount +
           ", stages = "                            + :: toStringVulkan ( info.stageCount, info.pStages ) +
           ", pVertexInputState = "                 + engine :: toString ( info.pVertexInputState ) +
           ", pInputAssemblyState = "               + engine :: toString ( info.pInputAssemblyState ) +
           ", pTessellationState = "                + engine :: toString ( info.pTessellationState ) +
           ", pViewportState = "                    + engine :: toString ( info.pViewportState ) +
           ", pRasterizationState = "               + engine :: toString ( info.pRasterizationState ) +
           ", pMultisampleState = "                 + engine :: toString ( info.pMultisampleState ) +
           ", pDepthStencilState = "                + engine :: toString ( info.pDepthStencilState ) +
           ", pColorBlendState = "                  + engine :: toString ( info.pColorBlendState ) +
           ", layout = "                            + engine :: toString ( info.layout ) +
           ", renderPass = "                        + engine :: toString ( info.renderPass ) +
           ", subpass = "                           + info.subpass +
           ", basePipelineHandle = "                + engine :: toString ( info.basePipelineHandle ) +
           ", basePipelineIndex = "                 + info.basePipelineIndex +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE
auto vulkan :: toString (
        Type ( GraphicsShaderGroupCreateInfoNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( GraphicsShaderGroupCreateInfoNVidia ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", stageCount = "                        + info.stageCount +
           ", stages = "                            + :: toStringVulkan ( info.stageCount, info.pStages ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE
auto vulkan :: toString (
        Type ( GraphicsPipelineShaderGroupsCreateInfoNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( GraphicsPipelineShaderGroupsCreateInfoNVidia ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", groupCount = "                        + info.groupCount +
           ", groups = "                            + :: toStringVulkan ( info.groupCount, info.pGroups ) +
           ", pipelineCount = "                     + info.pipelineCount +
           ", pipelines = "                         + :: toStringEngine ( info.pipelineCount, info.pPipelines ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE
auto vulkan :: toString (
        Type ( VertexInputBindingDivisorDescription ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( VertexInputBindingDivisorDescription ) ) " " +
           "{ binding = "_s     + info.binding +
           ", divisor = "       + info.divisor +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineVertexInputDivisorStateCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineVertexInputDivisorStateCreateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", vertexBindingDivisorCount = "         + info.vertexBindingDivisorCount +
           ", vertexBindingDivisors = "             + :: toStringVulkan ( info.vertexBindingDivisorCount, info.pVertexBindingDivisors ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISCARD_RECTANGLES_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineDiscardRectangleStateCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineDiscardRectangleStateCreateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", flags = "                             + :: flagsToString ( info.flags ) +
           ", discardRectangleMode = "              + toString ( info.discardRectangleMode ) +
           ", discardRectangleCount = "             + info.discardRectangleCount +
           ", discardRectangles = "                 + :: toStringVulkan ( info.discardRectangleCount, info.pDiscardRectangles ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineFragmentShadingRateEnumStateCreateInfoNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineFragmentShadingRateEnumStateCreateInfoNVidia ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", shadingRateType = "                   + toString ( info.shadingRateType ) +
           ", shadingRate = "                       + toString ( info.shadingRate ) +
           ", combinerOperations = "                + :: toStringVulkan ( 2, & info.combinerOperations[0] ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineFragmentShadingRateStateCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineFragmentShadingRateStateCreateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", fragmentSize = "                      + toString ( info.fragmentSize ) +
           ", combinerOperations = "                + :: toStringVulkan ( 2, & info.combinerOperations[0] ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineRenderingCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineFragmentShadingRateStateCreateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", viewMask = "                          + info.viewMask +
           ", colorAttachmentCount = "              + info.colorAttachmentCount +
           ", colorAttachmentFormats = "            + :: toStringVulkan ( info.colorAttachmentCount, info.pColorAttachmentFormats ) +
           ", depthAttachmentFormat = "             + toString ( info.depthAttachmentFormat ) +
           ", stencilAttachmentFormat = "           + toString ( info.stencilAttachmentFormat ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_REPRESENTATIVE_FRAGMENT_TEST_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineRepresentativeFragmentTestStateCreateInfoNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineRepresentativeFragmentTestStateCreateInfoNVidia ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", representativeFragmentTestEnable = "  + ( info.representativeFragmentTestEnable == VK_TRUE ? "true" : "false" ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineTessellationDomainOriginStateCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineTessellationDomainOriginStateCreateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", domainOrigin = "                      + toString ( info.domainOrigin ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE
auto vulkan :: toString (
        Type ( CoarseSampleLocationNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( CoarseSampleLocationNVidia ) ) " " +
           "{ pixelX = "_s  + info.pixelX +
           ", pixelY = "    + info.pixelY +
           ", sample = "    + info.sample +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE
auto vulkan :: toString (
        Type ( CoarseSampleOrderCustomNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( CoarseSampleOrderCustomNVidia ) ) " " +
           "{ shadingRate = "_s         + toString ( info.shadingRate ) +
           ", sampleCount = "           + info.sampleCount +
           ", sampleLocationCount = "   + info.sampleLocationCount +
           ", sampleLocations = "       + :: toStringVulkan ( info.sampleLocationCount, info.pSampleLocations ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineViewportCoarseSampleOrderStateCreateInfoNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineViewportCoarseSampleOrderStateCreateInfoNVidia ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", sampleOrderType = "                   + toString ( info.sampleOrderType ) +
           ", customSampleOrderCount = "            + info.customSampleOrderCount +
           ", customSampleOrders = "                + :: toStringVulkan ( info.customSampleOrderCount, info.pCustomSampleOrders ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE
auto vulkan :: toString (
        Type ( ShadingRatePaletteNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ShadingRatePaletteNVidia ) ) " " +
           "{ shadingRatePaletteEntryCount = "_s    + info.shadingRatePaletteEntryCount +
           ", pShadingRatePaletteEntries = "        + :: toStringVulkan ( info.shadingRatePaletteEntryCount, info.pShadingRatePaletteEntries ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineViewportShadingRateImageStateCreateInfoNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineViewportShadingRateImageStateCreateInfoNVidia ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", shadingRateImageEnable = "            + ( info.shadingRateImageEnable == VK_TRUE ? "true" : "false" ) +
           ", viewportCount = "                     + info.viewportCount +
           ", pShadingRatePalettes = "              + :: toStringVulkan ( info.viewportCount, info.pShadingRatePalettes ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_CONTROL_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineViewportDepthClipControlCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineViewportDepthClipControlCreateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", negativeOneToOne = "                  + ( info.negativeOneToOne == VK_TRUE ? "true" : "false" ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SCISSOR_EXCLUSIVE_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineViewportExclusiveScissorStateCreateInfoNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineViewportExclusiveScissorStateCreateInfoNVidia ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", exclusiveScissorCount = "             + info.exclusiveScissorCount +
           ", exclusiveScissors = "                 + :: toStringVulkan ( info.exclusiveScissorCount, info.pExclusiveScissors ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_VIEWPORT_SWIZZLE_AVAILABLE
auto vulkan :: toString (
        Type ( ViewportSwizzleNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ViewportSwizzleNVidia ) ) " " +
           "{ x = "_s   + toString ( info.x ) +
           ", y = "     + toString ( info.y ) +
           ", z = "     + toString ( info.z ) +
           ", w = "     + toString ( info.w ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SCISSOR_EXCLUSIVE_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineViewportSwizzleStateCreateInfoNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineViewportSwizzleStateCreateInfoNVidia ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", flags = "                             + :: flagsToString ( info.flags ) +
           ", viewportCount = "                     + info.viewportCount +
           ", viewportSwizzles = "                  + :: toStringVulkan ( info.viewportCount, info.pViewportSwizzles ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CLIP_SPACE_W_SCALING_AVAILABLE
auto vulkan :: toString (
        Type ( ViewportWScalingNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ViewportSwizzleNVidia ) ) " " +
           "{ xCoefficient = "_s   + info.xCoefficient +
           ", yCoefficient = "     + info.yCoefficient +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CLIP_SPACE_W_SCALING_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineViewportWScalingStateCreateInfoNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineViewportWScalingStateCreateInfoNVidia ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", viewportWScalingEnable = "            + ( info.viewportWScalingEnable == VK_TRUE ? "true" : "false" ) +
           ", viewportCount = "                     + info.viewportCount +
           ", viewportWScalings = "                 + :: toStringVulkan ( info.viewportCount, info.pViewportWScalings ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONSERVATIVE_RASTERIZATION_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineRasterizationConservativeStateCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineRasterizationConservativeStateCreateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", flags = "                             + :: flagsToString ( info.flags ) +
           ", conservativeRasterizationMode = "     + toString ( info.conservativeRasterizationMode ) +
           ", extraPrimitiveOverestimationSize = "  + info.extraPrimitiveOverestimationSize +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_ENABLE_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineRasterizationDepthClipStateCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineRasterizationDepthClipStateCreateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", flags = "                             + :: flagsToString ( info.flags ) +
           ", depthClipEnable = "                   + ( info.depthClipEnable == VK_TRUE ? "true" : "false" ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineRasterizationLineStateCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineRasterizationLineStateCreateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", lineRasterizationMode = "             + toString ( info.lineRasterizationMode ) +
           ", stippledLineEnable = "                + ( info.stippledLineEnable == VK_TRUE ? "true" : "false" ) +
           ", lineStippleFactor = "                 + info.lineStippleFactor +
           ", lineStipplePattern = "                + info.lineStipplePattern +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineRasterizationProvokingVertexStateCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineRasterizationProvokingVertexStateCreateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", provokingVertexMode = "               + toString ( info.provokingVertexMode ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_RASTERIZATION_ORDER_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineRasterizationStateRasterizationOrderAMD ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineRasterizationStateRasterizationOrderAMD ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", rasterizationOrder = "                + toString ( info.rasterizationOrder ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineRasterizationStateStreamCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineRasterizationStateStreamCreateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", flags = "                             + :: flagsToString ( info.flags ) +
           ", rasterizationStream = "               + info.rasterizationStream +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAMEBUFFER_MIXED_SAMPLES_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineCoverageModulationStateCreateInfoNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineCoverageModulationStateCreateInfoNVidia ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", flags = "                             + :: flagsToString ( info.flags ) +
           ", coverageModulationMode = "            + toString ( info.coverageModulationMode ) +
           ", coverageModulationTableEnable = "     + ( info.coverageModulationTableEnable == VK_TRUE ? "true" : "false" ) +
           ", coverageModulationTableCount = "      + info.coverageModulationTableCount +
           ", coverageModulationTable = "           + :: toStringRegular ( info.coverageModulationTableCount, info.pCoverageModulationTable ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COVERAGE_REDUCTION_MODE_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineCoverageReductionStateCreateInfoNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineCoverageReductionStateCreateInfoNVidia ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", flags = "                             + :: flagsToString ( info.flags ) +
           ", coverageReductionMode = "             + toString ( info.coverageReductionMode ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_COVERAGE_TO_COLOR_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineCoverageToColorStateCreateInfoNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineCoverageToColorStateCreateInfoNVidia ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", flags = "                             + :: flagsToString ( info.flags ) +
           ", coverageToColorEnable = "             + ( info.coverageToColorEnable == VK_TRUE ? "true" : "false" ) +
           ", coverageToColorLocation = "           + info.coverageToColorLocation +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineSampleLocationsStateCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineSampleLocationsStateCreateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", sampleLocationsEnable = "             + ( info.sampleLocationsEnable == VK_TRUE ? "true" : "false" ) +
           ", sampleLocationsInfo = "               + toString ( info.sampleLocationsInfo ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineColorBlendAdvancedStateCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineColorBlendAdvancedStateCreateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", sourcePremultiplied = "               + ( info.sourcePremultiplied == VK_TRUE ? "true" : "false" ) +
           ", destinationPremultiplied = "          + ( info.destinationPremultiplied == VK_TRUE ? "true" : "false" ) +
           ", blendOverlap = "                      + toString ( info.blendOverlap ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_COLOR_WRITE_ENABLE_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineColorWriteCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineColorWriteCreateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", attachmentCount = "                   + info.attachmentCount +
           ", colorWriteEnables = "                 + :: toStringRegular ( info.attachmentCount, info.pColorWriteEnables ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
auto vulkan :: toString (
        Type ( RayTracingShaderGroupType )  type
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( type ) {
        case RayTracingShaderGroupTypeGeneral:              { asString = "General";                 break; }
        case RayTracingShaderGroupTypeTrianglesHitGroup:    { asString = "Triangles Hit Group";     break; }
        case RayTracingShaderGroupTypeProceduralHitGroup:   { asString = "Procedural Hit Group";    break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
auto vulkan :: toString (
        Type ( ShaderGroupShader )  type
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( type ) {
        case ShaderGroupShaderGeneral:      { asString = "General";         break; }
        case ShaderGroupShaderAnyHit:       { asString = "Any Hit";         break; }
        case ShaderGroupShaderClosestHit:   { asString = "Closest Hit";     break; }
        case ShaderGroupShaderIntersection: { asString = "Intersection";    break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
auto vulkan :: toString (
        Type ( RayTracingShaderGroupCreateInfoNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( RayTracingShaderGroupCreateInfoNVidia ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", type = "                              + toString ( info.type ) +
           ", generalShader = "                     + info.generalShader +
           ", closestHitShader = "                  + info.closestHitShader +
           ", anyHitShader = "                      + info.anyHitShader +
           ", intersectionShader = "                + info.intersectionShader +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
auto vulkan :: toString (
        Type ( RayTracingPipelineCreateInfoNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( RayTracingPipelineCreateInfoNVidia ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", flags = "                             + :: flagsToString < Type ( PipelineCreateFlag ) > ( info.flags ) +
           ", stageCount = "                        + info.stageCount +
           ", stages = "                            + :: toStringVulkan ( info.stageCount, info.pStages ) +
           ", groupCount = "                        + info.groupCount +
           ", groups = "                            + :: toStringVulkan ( info.groupCount, info.pGroups ) +
           ", maxRecursionDepth = "                 + info.maxRecursionDepth +
           ", layout = "                            + engine :: toString ( info.layout ) +
           ", basePipelineHandle = "                + engine :: toString ( info.basePipelineHandle ) +
           ", basePipelineIndex = "                 + engine :: toString ( info.basePipelineIndex ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
auto vulkan :: toString (
        Type ( RayTracingShaderGroupCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( RayTracingShaderGroupCreateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", type = "                              + toString ( info.type ) +
           ", generalShader = "                     + info.generalShader +
           ", closestHitShader = "                  + info.closestHitShader +
           ", anyHitShader = "                      + info.anyHitShader +
           ", intersectionShader = "                + info.intersectionShader +
           ", pShaderGroupCaptureReplayHandle = "   + engine :: toString ( info.pShaderGroupCaptureReplayHandle ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineLibraryCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineLibraryCreateInfo ) ) " " +
           "{ structureType = "_s   + toString ( info.structureType ) +
           ", pNext = "             + engine :: toString ( info.pNext ) +
           ", libraryCount = "      + info.libraryCount +
           ", libraries = "         + :: toStringEngine ( info.libraryCount, info.pLibraries ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
auto vulkan :: toString (
        Type ( RayTracingPipelineInterfaceCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( RayTracingPipelineInterfaceCreateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", maxPipelineRayPayloadSize = "         + info.maxPipelineRayPayloadSize +
           ", maxPipelineRayHitAttributeSize = "    + info.maxPipelineRayHitAttributeSize +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
auto vulkan :: toString (
        Type ( RayTracingPipelineCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( RayTracingPipelineCreateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", flags = "                             + :: flagsToString < Type ( PipelineCreateFlag ) > ( info.flags ) +
           ", stageCount = "                        + info.stageCount +
           ", stages = "                            + :: toStringVulkan ( info.stageCount, info.pStages ) +
           ", groupCount = "                        + info.groupCount +
           ", groups = "                            + :: toStringVulkan ( info.groupCount, info.pGroups ) +
           ", maxRecursionDepth = "                 + info.maxPipelineRayRecursionDepth +
           ", pLibraryInfo = "                      + engine :: toString ( info.pLibraryInfo ) +
           ", pLibraryInterface = "                 + engine :: toString ( info.pLibraryInterface ) +
           ", pDynamicState = "                     + engine :: toString ( info.pDynamicState ) +
           ", layout = "                            + engine :: toString ( info.layout ) +
           ", basePipelineHandle = "                + engine :: toString ( info.basePipelineHandle ) +
           ", basePipelineIndex = "                 + engine :: toString ( info.basePipelineIndex ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineCacheCreateFlag )  type
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( type ) {
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE
        case PipelineCacheCreateFlagExternallySynchronized: { asString = "Externally Synchronized"; break; }
#endif
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineCacheHeaderVersionValue )  type
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( type ) {
        case PipelineCacheHeaderVersionValueOne:    { asString = "Version One"; break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineCacheCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineCacheCreateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", flags = "                             + :: flagsToString < Type ( PipelineCacheCreateFlag ) > ( info.flags ) +
           ", initialDataSize = "                   + info.initialDataSize +
           ", pInitialData = "                      + engine :: toString ( info.pInitialData ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineCacheHeaderVersionOne ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineCacheHeaderVersionOne ) ) " " +
           "{ headerSize = "_s      + info.headerSize +
           ", headerVersion = "     + toString ( info.headerVersion ) +
           ", vendorID = "          + info.vendorID +
           ", deviceID = "          + info.deviceID +
           ", pipelineCacheUUID = " + :: toStringRegular ( VK_UUID_SIZE, & info.pipelineCacheUUID[0] ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineInfo ) ) " " +
            "{ structureType = "_s                  + toString ( info.structureType ) +
            ", pNext = "                            + engine :: toString ( info.pNext ) +
            ", pipeline = "                         + engine :: toString ( info.pipeline ) +
            " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineExecutableProperties ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineExecutableProperties ) ) " " +
            "{ structureType = "_s                  + toString ( info.structureType ) +
            ", pNext = "                            + engine :: toString ( info.pNext ) +
            ", stages = "                           + :: flagsToString < Type ( ShaderStageFlag ) > ( info.stages ) +
            ", name = "                             + info.name +
            ", description = "                      + info.description +
            ", subgroupSize = "                     + info.subgroupSize +
            " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineExecutableStatisticFormat )  format
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( format ) {
        case PipelineExecutableStatisticFormatBool:     { asString = "Bool";    break; }
        case PipelineExecutableStatisticFormatSInt64:   { asString = "SInt64";  break; }
        case PipelineExecutableStatisticFormatUInt64:   { asString = "UInt64";  break; }
        case PipelineExecutableStatisticFormatFloat64:  { asString = "Float64"; break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineExecutableInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineExecutableInfo ) ) " " +
           "{ structureType = "_s                  + toString ( info.structureType ) +
           ", pNext = "                            + engine :: toString ( info.pNext ) +
           ", pipeline = "                         + engine :: toString ( info.pipeline ) +
           ", executableIndex = "                  + info.executableIndex +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineExecutableStatistic ) const & info
) noexcept -> String {

    auto valueAsString = [] (
            Type ( PipelineExecutableStatisticFormat )  format,
            Type ( PipelineExecutableStatisticValue )   value
    ) -> String {
        switch ( format ) {
            case PipelineExecutableStatisticFormatBool:
                return value.b ? "true" : "false";
            case PipelineExecutableStatisticFormatFloat64:
                return String::f ( "%llf", value.d );
            case PipelineExecutableStatisticFormatSInt64:
                return Long ( value.s64 ).toString();
            case PipelineExecutableStatisticFormatUInt64:
                return String::f ( "%zu", value.u64 );
        }

        return "Undefined";
    };

    return __C_ENG_STRINGIFY ( Type ( PipelineExecutableStatistic ) ) " " +
           "{ structureType = "_s                  + toString ( info.structureType ) +
           ", pNext = "                            + engine :: toString ( info.pNext ) +
           ", name = "                             + info.name +
           ", description = "                      + info.description +
           ", value = "                            + valueAsString ( info.format, info.value ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineExecutableInternalRepresentation ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineExecutableInternalRepresentation ) ) " " +
           "{ structureType = "_s                  + toString ( info.structureType ) +
           ", pNext = "                            + engine :: toString ( info.pNext ) +
           ", name = "                             + info.name +
           ", description = "                      + info.description +
           ", isText = "                           + ( info.isText == VK_TRUE ? "true" : "false" ) +
           ", dataSize = "                         + info.dataSize +
           ", pData = "                            + engine :: toString ( info.pData ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_INFO_AVAILABLE
auto vulkan :: toString (
        Type ( ShaderInfoTypeAMD )  format
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( format ) {
        case ShaderInfoTypeAMDStatistics:   { asString = "Statistics";  break; }
        case ShaderInfoTypeAMDBinary:       { asString = "Binary";      break; }
        case ShaderInfoTypeAMDDisassembly:  { asString = "Disassembly"; break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_INFO_AVAILABLE
auto vulkan :: toString (
        Type ( ShaderResourceUsageAMD ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ShaderResourceUsageAMD ) ) " " +
           "{ numUsedVgrps = "_s                  + info.numUsedVgrps +
           ", numUsedSgrps = "                    + info.numUsedSgrps +
           ", ldsSizePerLogicalWorkGroup = "      + info.ldsSizePerLogicalWorkGroup +
           ", ldsUsageSizeInBytes = "             + info.ldsUsageSizeInBytes +
           ", scratchMemUsageInBytes = "          + info.scratchMemUsageInBytes +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_INFO_AVAILABLE
auto vulkan :: toString (
        Type ( ShaderStatisticsInfoAMD ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ShaderStatisticsInfoAMD ) ) " " +
           "{ shaderStageMask = "_s               + :: flagsToString < Type ( ShaderStageFlag ) > ( info.shaderStageMask ) +
           ", resourceUsage = "                   + toString ( info.resourceUsage ) +
           ", numPhysicalVgrps = "                + info.numPhysicalVgrps +
           ", numPhysicalSgrps = "                + info.numPhysicalSgrps +
           ", numAvailableVgrps = "               + info.numAvailableVgrps +
           ", numAvailableSgrps = "               + info.numAvailableSgrps +
           ", computeWorkgroupSize = "            + :: toStringRegular ( 3, & info.computeWorkGroupSize[0] ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( MemoryPropertyFlag )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case MemoryPropertyFlagDeviceLocal:         { asString = "Device Local";        break; }
        case MemoryPropertyFlagHostVisible:         { asString = "Host Visible";        break; }
        case MemoryPropertyFlagHostCoherent:        { asString = "Host Coherent";       break; }
        case MemoryPropertyFlagHostCached:          { asString = "Host Cached";         break; }
        case MemoryPropertyFlagLazilyAllocated:     { asString = "Lazily Allocated";    break; }
#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
        case MemoryPropertyFlagProtectedBit:        { asString = "Protected Bit";       break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_AMD_DEVICE_COHERENT_MEMORY_AVAILABLE
        case MemoryPropertyFlagDeviceCoherentAMD:   { asString = "Device Coherent AMD"; break; }
        case MemoryPropertyFlagDeviceUncachedAMD:   { asString = "Device Uncached AMD"; break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_RDMA_AVAILABLE
        case MemoryPropertyFlagRDMACapableNVidia:   { asString = "RDMA Capable NVidia"; break; }
#endif
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( MemoryHeapFlag )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case MemoryHeapFlagDeviceLocal:         { asString = "Device Local";        break; }
#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
        case MemoryHeapFlagMultiInstance:       { asString = "Multi Instance";      break; }
#endif
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( MemoryType ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( MemoryType ) ) " " +
           "{ propertyFlags = "_s             + :: flagsToString < Type ( MemoryPropertyFlag ) > ( info.propertyFlags ) +
           ", heapIndex = "                   + info.heapIndex +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( MemoryHeap ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( MemoryHeap ) ) " " +
           "{ size = "_s                + toString ( info.size ) +
           ", flags = "                 + :: flagsToString < Type ( MemoryHeapFlag ) > ( info.flags ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( PhysicalDeviceMemoryProperties ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PhysicalDeviceMemoryProperties ) ) " " +
           "{ memoryTypeCount = "_s + info.memoryTypeCount +
           ", memoryTypes = "       + :: toStringVulkan ( info.memoryTypeCount, & info.memoryTypes[0] ) +
           ", memoryHeapCount = "   + info.memoryHeapCount +
           ", memoryHeaps = "       + :: toStringVulkan ( info.memoryHeapCount, & info.memoryHeaps[0] ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto vulkan :: toString (
        Type ( PhysicalDeviceMemoryProperties2 ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PhysicalDeviceMemoryProperties2 ) ) " " +
           "{ structureType = "_s   + toString ( info.structureType ) +
           ", pNext = "             + engine :: toString ( info.pNext ) +
           ", properties = "        + toString ( info.properties ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_BUDGET_AVAILABLE
auto vulkan :: toString (
        Type ( PhysicalDeviceMemoryBudgetProperties ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PhysicalDeviceMemoryBudgetProperties ) ) " " +
           "{ structureType = "_s   + toString ( info.structureType ) +
           ", pNext = "             + engine :: toString ( info.pNext ) +
           ", heapBudget = "        + :: toStringVulkan ( VK_MAX_MEMORY_HEAPS, & info.heapBudget[0] ) +
           ", heapUsage = "         + :: toStringVulkan ( VK_MAX_MEMORY_HEAPS, & info.heapUsage[0] ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( MemoryAllocateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( MemoryAllocateInfo ) ) " " +
           "{ structureType = "_s   + toString ( info.structureType ) +
           ", pNext = "             + engine :: toString ( info.pNext ) +
           ", allocationSize = "    + engine :: toString ( info.allocationSize ) +
           ", memoryTypeIndex = "   + info.memoryTypeIndex +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto vulkan :: toString (
        Type ( ExternalMemoryHandleTypeFlag )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case ExternalMemoryHandleTypeFlagOpaqueFd:                  { asString = "Opaque Fd";                   break; }
        case ExternalMemoryHandleTypeFlagOpaqueWin32:               { asString = "Opaque Win 32";               break; }
        case ExternalMemoryHandleTypeFlagOpaqueWin32KMT:            { asString = "Opaque Win 32 KMT";           break; }
        case ExternalMemoryHandleTypeFlagD3D11Texture:              { asString = "D3D11 Texture";               break; }
        case ExternalMemoryHandleTypeFlagD3D11TextureKMT:           { asString = "D3D11 Texture KMT";           break; }
        case ExternalMemoryHandleTypeFlagD3D12Heap:                 { asString = "D3D12 Heap";                  break; }
        case ExternalMemoryHandleTypeFlagD3D12Resource:             { asString = "D3D12 Resource";              break; }
#if __C_ENG_VULKAN_API_EXTENSION_EXTERNAL_DMA_BUFFER_AVAILABLE
        case ExternalMemoryHandleTypeFlagDMABuffer:                 { asString = "DMA Buffer";                  break; }
#endif
#if __C_ENG_VULKAN_API_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_AVAILABLE
        case ExternalMemoryHandleTypeFlagHardwareBufferAndroid:     { asString = "Hardware Buffer Android";     break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_EXTERNAL_MEMORY_HOST_AVAILABLE
        case ExternalMemoryHandleTypeFlagHostAllocation:            { asString = "Host Allocation";             break; }
        case ExternalMemoryHandleTypeFlagHostMappedForeignMemory:   { asString = "Host Mapped Foreign Memory";  break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_MEMORY_AVAILABLE
        case ExternalMemoryHandleTypeFlagZirconVMOFuchsia:          { asString = "Zircon VMO Fuchsia";          break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_RDMA_AVAILABLE
        case ExternalMemoryHandleTypeFlagRDMAAddress:               { asString = "RDMA Address";                break; }
#endif
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_AVAILABLE
auto vulkan :: toString (
        Type ( ExternalMemoryHandleTypeFlagNVidia )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case ExternalMemoryHandleTypeFlagNVidiaOpaqueWin32:             { asString = "Opaque Win 32";               break; }
        case ExternalMemoryHandleTypeFlagNVidiaOpaqueWin32KMT:          { asString = "Opaque Win 32 KMT";           break; }
        case ExternalMemoryHandleTypeFlagNVidiaD3D11Image:              { asString = "D3D11 Image";               break; }
        case ExternalMemoryHandleTypeFlagNVidiaD3D11ImageKMT:           { asString = "D3D11 Image KMT";           break; }

    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto vulkan :: toString (
        Type ( MemoryAllocateFlag )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
        case MemoryAllocateFlagDeviceMask:                  { asString = "Device Mask";                     break; }
        case MemoryAllocateFlagDeviceAddress:               { asString = "Device Address";                  break; }
        case MemoryAllocateFlagDeviceAddressCaptureReplay:  { asString = "Device Address Capture Replay";   break; }
#endif
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_AVAILABLE
auto vulkan :: toString (
        Type ( DedicatedAllocationMemoryAllocateInfoNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( DedicatedAllocationMemoryAllocateInfoNVidia ) ) " " +
           "{ structureType = "_s   + toString ( info.structureType ) +
           ", pNext = "             + engine :: toString ( info.pNext ) +
           ", image = "             + engine :: toString ( info.image ) +
           ", buffer = "            + engine :: toString ( info.buffer ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto vulkan :: toString (
        Type ( ExportMemoryAllocateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ExportMemoryAllocateInfo ) ) " " +
           "{ structureType = "_s   + toString ( info.structureType ) +
           ", pNext = "             + engine :: toString ( info.pNext ) +
           ", handleTypes = "       + :: flagsToString < Type ( ExternalMemoryHandleTypeFlag ) > ( info.handleTypes ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_AVAILABLE
auto vulkan :: toString (
        Type ( ExportMemoryAllocateInfoNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ExportMemoryAllocateInfoNVidia ) ) " " +
           "{ structureType = "_s   + toString ( info.structureType ) +
           ", pNext = "             + engine :: toString ( info.pNext ) +
           ", handleTypes = "       + :: flagsToString < Type ( ExternalMemoryHandleTypeFlag ) > ( info.handleTypes ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_WIN32_AVAILABLE
auto vulkan :: toString (
        Type ( ExportMemoryWin32HandleInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ExportMemoryWin32HandleInfo ) ) " " +
           "{ structureType = "_s   + toString ( info.structureType ) +
           ", pNext = "             + engine :: toString ( info.pNext ) +
           ", pAttributes = "       + engine :: toString ( info.pAttributes ) +
           ", dwAccess = "          + info.dwAccess +
           ", name = "              + info.name +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_WIN32_AVAILABLE
auto vulkan :: toString (
        Type ( ExportMemoryWin32HandleInfoNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ExportMemoryWin32HandleInfoNVidia ) ) " " +
           "{ structureType = "_s   + toString ( info.structureType ) +
           ", pNext = "             + engine :: toString ( info.pNext ) +
           ", pAttributes = "       + engine :: toString ( info.pAttributes ) +
           ", dwAccess = "          + info.dwAccess +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_AVAILABLE
auto vulkan :: toString (
        Type ( ImportAndroidHardwareBufferInfoAndroid ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ImportAndroidHardwareBufferInfoAndroid ) ) " " +
           "{ structureType = "_s   + toString ( info.structureType ) +
           ", pNext = "             + engine :: toString ( info.pNext ) +
           ", buffer = "            + engine :: toString ( info.buffer ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_BUFFER_COLLECTION_AVAILABLE
auto vulkan :: toString (
        Type ( ImportMemoryBufferCollectionFuchsia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ImportMemoryBufferCollectionFuchsia ) ) " " +
           "{ structureType = "_s   + toString ( info.structureType ) +
           ", pNext = "             + engine :: toString ( info.pNext ) +
           ", collection = "        + engine :: toString ( info.collection ) +
           ", index = "             + info.index +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_FD_AVAILABLE
auto vulkan :: toString (
        Type ( ImportMemoryFdInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ImportMemoryFdInfo ) ) " " +
           "{ structureType = "_s   + toString ( info.structureType ) +
           ", pNext = "             + engine :: toString ( info.pNext ) +
           ", handleType = "        + toString ( info.handleType ) +
           ", fd = "                + info.fd +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTERNAL_MEMORY_HOST_AVAILABLE
auto vulkan :: toString (
        Type ( ImportMemoryHostPointerInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ImportMemoryHostPointerInfo ) ) " " +
           "{ structureType = "_s   + toString ( info.structureType ) +
           ", pNext = "             + engine :: toString ( info.pNext ) +
           ", handleType = "        + toString ( info.handleType ) +
           ", pHostPointer = "      + engine :: toString ( info.pHostPointer ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_WIN32_AVAILABLE
auto vulkan :: toString (
        Type ( ImportMemoryWin32HandleInfoNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ImportMemoryWin32HandleInfoNVidia ) ) " " +
           "{ structureType = "_s   + toString ( info.structureType ) +
           ", pNext = "             + engine :: toString ( info.pNext ) +
           ", handleType = "        + :: flagsToString < Type ( ExternalMemoryHandleTypeFlag ) > ( info.handleTypes ) +
           ", handle = "            + engine :: toString ( info.handle ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_MEMORY_AVAILABLE
auto vulkan :: toString (
        Type ( ImportMemoryZirconHandleFuchsia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ImportMemoryZirconHandleFuchsia ) ) " " +
           "{ structureType = "_s   + toString ( info.structureType ) +
           ", pNext = "             + engine :: toString ( info.pNext ) +
           ", handleType = "        + engine :: toString ( info.handleType ) +
           ", handle = "            + engine :: toString ( info.handle ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto vulkan :: toString (
        Type ( MemoryAllocateFlagsInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( MemoryAllocateFlagsInfo ) ) " " +
           "{ structureType = "_s   + toString ( info.structureType ) +
           ", pNext = "             + engine :: toString ( info.pNext ) +
           ", flags = "             + :: flagsToString < Type ( MemoryAllocateFlag ) > ( info.flags ) +
           ", deviceMask = "        + info.deviceMask +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto vulkan :: toString (
        Type ( MemoryDedicatedAllocateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( MemoryDedicatedAllocateInfo ) ) " " +
           "{ structureType = "_s   + toString ( info.structureType ) +
           ", pNext = "             + engine :: toString ( info.pNext ) +
           ", image = "             + engine :: toString ( info.image ) +
           ", buffer = "            + engine :: toString ( info.buffer ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
auto vulkan :: toString (
        Type ( MemoryOpaqueCaptureAddressAllocateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( MemoryOpaqueCaptureAddressAllocateInfo ) ) " " +
           "{ structureType = "_s       + toString ( info.structureType ) +
           ", pNext = "                 + engine :: toString ( info.pNext ) +
           ", opaqueCaptureAddress = "  + info.opaqueCaptureAddress +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_PRIORITY_AVAILABLE
auto vulkan :: toString (
        Type ( MemoryPriorityAllocateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( MemoryPriorityAllocateInfo ) ) " " +
           "{ structureType = "_s       + toString ( info.structureType ) +
           ", pNext = "                 + engine :: toString ( info.pNext ) +
           ", priority = "              + info.priority +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_WIN32_AVAILABLE
auto vulkan :: toString (
        Type ( MemoryGetWin32HandleInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( MemoryGetWin32HandleInfo ) ) " " +
           "{ structureType = "_s       + toString ( info.structureType ) +
           ", pNext = "                 + engine :: toString ( info.pNext ) +
           ", memory = "                + engine :: toString ( info.memory ) +
           ", handleType = "            + toString ( info.handleType ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_WIN32_AVAILABLE
auto vulkan :: toString (
        Type ( MemoryWin32HandleProperties ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( MemoryWin32HandleProperties ) ) " " +
           "{ structureType = "_s       + toString ( info.structureType ) +
           ", pNext = "                 + engine :: toString ( info.pNext ) +
           ", memoryTypeBits = "        + info.memoryTypeBits +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_FD_AVAILABLE
auto vulkan :: toString (
        Type ( MemoryGetFdInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( MemoryGetFdInfo ) ) " " +
           "{ structureType = "_s       + toString ( info.structureType ) +
           ", pNext = "                 + engine :: toString ( info.pNext ) +
           ", memory = "                + engine :: toString ( info.memory ) +
           ", handleType = "            + toString ( info.handleType ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_FD_AVAILABLE
auto vulkan :: toString (
        Type ( MemoryFdProperties ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( MemoryFdProperties ) ) " " +
           "{ structureType = "_s       + toString ( info.structureType ) +
           ", pNext = "                 + engine :: toString ( info.pNext ) +
           ", memoryTypeBits = "        + info.memoryTypeBits +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTERNAL_MEMORY_HOST_AVAILABLE
auto vulkan :: toString (
        Type ( MemoryHostPointerProperties ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( MemoryHostPointerProperties ) ) " " +
           "{ structureType = "_s       + toString ( info.structureType ) +
           ", pNext = "                 + engine :: toString ( info.pNext ) +
           ", memoryTypeBits = "        + info.memoryTypeBits +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_RDMA_AVAILABLE
auto vulkan :: toString (
        Type ( MemoryGetRemoteAddressInfoNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( MemoryGetRemoteAddressInfoNVidia ) ) " " +
           "{ structureType = "_s       + toString ( info.structureType ) +
           ", pNext = "                 + engine :: toString ( info.pNext ) +
           ", memory = "                + engine :: toString ( info.memory ) +
           ", handleType = "            + toString ( info.handleType ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( MappedMemoryRange ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( MappedMemoryRange ) ) " " +
           "{ structureType = "_s       + toString ( info.structureType ) +
           ", pNext = "                 + engine :: toString ( info.pNext ) +
           ", memory = "                + engine :: toString ( info.memory ) +
           ", offset = "                + engine :: toString ( info.offset ) +
           ", size = "                  + engine :: toString ( info.size ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto vulkan :: toString (
        Type ( PeerMemoryFeatureFlag )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case PeerMemoryFeatureFlagCopySource:           { asString = "Copy Source";         break; }
        case PeerMemoryFeatureFlagCopyDestination:      { asString = "Copy Destination";    break; }
        case PeerMemoryFeatureFlagGenericSource:        { asString = "Generic Source";      break; }
        case PeerMemoryFeatureFlagGenericDestination:   { asString = "Generic Destination"; break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
auto vulkan :: toString (
        Type ( DeviceMemoryOpaqueCaptureAddressInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( DeviceMemoryOpaqueCaptureAddressInfo ) ) " " +
           "{ structureType = "_s       + toString ( info.structureType ) +
           ", pNext = "                 + engine :: toString ( info.pNext ) +
           ", memory = "                + engine :: toString ( info.memory ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( BufferUsageFlag )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case BufferUsageFlagTransferSource:                             { asString = "Transfer Source";                                 break; }
        case BufferUsageFlagTransferDestination:                        { asString = "Transfer Destination";                            break; }
        case BufferUsageFlagUniformTexelBuffer:                         { asString = "Uniform Texel Buffer";                            break; }
        case BufferUsageFlagStorageTexelBuffer:                         { asString = "Storage Texel Buffer";                            break; }
        case BufferUsageFlagUniformBuffer:                              { asString = "Uniform Buffer";                                  break; }
        case BufferUsageFlagStorageBuffer:                              { asString = "Storage Buffer";                                  break; }
        case BufferUsageFlagIndexBuffer:                                { asString = "Index Buffer";                                    break; }
        case BufferUsageFlagVertexBuffer:                               { asString = "Vertex Buffer";                                   break; }
        case BufferUsageFlagIndirectBuffer:                             { asString = "Indirect Buffer";                                 break; }
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
        case BufferUsageFlagShaderDeviceAddress:                        { asString = "Shader Device Address";                           break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_DECODE_QUEUE_AVAILABLE && __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED
        case BufferUsageFlagVideoDecodeSource:                          { asString = "Video Decode Source";                             break; }
        case BufferUsageFlagVideoDecodeDestination:                     { asString = "Video Decode Destination";                        break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_ENCODE_QUEUE_AVAILABLE && __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED
        case BufferUsageFlagVideoEncodeSource:                          { asString = "Video Encode Source";                             break; }
        case BufferUsageFlagVideoEncodeDestination:                     { asString = "Video Encode Destination";                        break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE
        case BufferUsageFlagTransformFeedbackBuffer:                    { asString = "Transform Feedback Buffer";                       break; }
        case BufferUsageFlagTransformFeedbackCounterBuffer:             { asString = "Transform Feedback Counter Buffer";               break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE
        case BufferUsageFlagConditionalRendering:                       { asString = "Conditional Rendering";                           break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
        case BufferUsageFlagAccelerationStructureBuildInputReadOnly:    { asString = "Acceleration Structure Build Input Read Only";    break; }
        case BufferUsageFlagAccelerationStructureStorage:               { asString = "Acceleration Structure Storage";                  break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
        case BufferUsageFlagShaderBindingTable:                         { asString = "Shader Binding Table";                            break; }
#endif
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( BufferCreateFlag )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case BufferCreateFlagSparseBinding:                 { asString = "Sparse Binding";                  break; }
        case BufferCreateFlagSparseResidency:               { asString = "Sparse Residency";                break; }
        case BufferCreateFlagSparseAliased:                 { asString = "Sparse Aliased";                  break; }
#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
        case BufferCreateFlagProtected:                     { asString = "Protected";                       break; }
#endif
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
        case BufferCreateFlagDeviceAddressCaptureReplay:    { asString = "Device Address Capture Replay";   break; }
#endif
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( BufferCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( BufferCreateInfo ) ) " " +
           "{ structureType = "_s       + toString ( info.structureType ) +
           ", pNext = "                 + engine :: toString ( info.pNext ) +
           ", flags = "                 + :: flagsToString < Type ( BufferCreateFlag ) > ( info.flags ) +
           ", size = "                  + toString ( info.size ) +
           ", usage = "                 + :: flagsToString < Type ( BufferUsageFlag ) > ( info.usage ) +
           ", sharingMode = "           + toString ( info.sharingMode ) +
           ", queueFamilyIndexCount = " + info.queueFamilyIndexCount +
           ", queueFamilyIndices = "    + :: toStringRegular ( info.queueFamilyIndexCount, info.pQueueFamilyIndices ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_DECODE_H264_AVAILABLE
auto vulkan :: toString (
        Type ( VideoDecodeH264PictureLayoutFlag )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case VideoDecodeH264PictureLayoutFlagProgressive:                   { asString = "Progressive";                     break; }
        case VideoDecodeH264PictureLayoutFlagInterlacedInterleavedLines:    { asString = "Interlaced Interleaved Lines";    break; }
        case VideoDecodeH264PictureLayoutFlagInterlacedSeparatePlanes:      { asString = "Interlaced Separate Planes";      break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE
auto vulkan :: toString (
        Type ( VideoChromaSubsamplingFlag )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case VideoChromaSubsamplingFlagInvalid:     { asString = "Invalid";         break; }
        case VideoChromaSubsamplingFlagMonochrome:  { asString = "Monochrome";      break; }
        case VideoChromaSubsamplingFlag420:         { asString = "420";             break; }
        case VideoChromaSubsamplingFlag422:         { asString = "422";             break; }
        case VideoChromaSubsamplingFlag444:         { asString = "444";             break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE
auto vulkan :: toString (
        Type ( VideoComponentBitDepthFlag )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case VideoComponentBitDepthFlagInvalid: { asString = "Invalid"; break; }
        case VideoComponentBitDepthFlag8:       { asString = "8";       break; }
        case VideoComponentBitDepthFlag10:      { asString = "10";      break; }
        case VideoComponentBitDepthFlag12:      { asString = "12";      break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_BUFFER_COLLECTION_AVAILABLE
auto vulkan :: toString (
        Type ( BufferCollectionBufferCreateInfoFuchsia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( BufferCollectionBufferCreateInfoFuchsia ) ) " " +
           "{ structureType = "_s       + toString ( info.structureType ) +
           ", pNext = "                 + engine :: toString ( info.pNext ) +
           ", collection = "            + engine :: toString ( info.collection ) +
           ", index = "                 + info.index +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_BUFFER_DEVICE_ADDRESS_AVAILABLE
auto vulkan :: toString (
        Type ( BufferDeviceAddressCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( BufferDeviceAddressCreateInfo ) ) " " +
           "{ structureType = "_s       + toString ( info.structureType ) +
           ", pNext = "                 + engine :: toString ( info.pNext ) +
           ", collection = "            + engine :: toString ( info.deviceAddress ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
auto vulkan :: toString (
        Type ( BufferOpaqueCaptureAddressCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( BufferOpaqueCaptureAddressCreateInfo ) ) " " +
           "{ structureType = "_s       + toString ( info.structureType ) +
           ", pNext = "                 + engine :: toString ( info.pNext ) +
           ", opaqueCaptureAddress = "  + info.opaqueCaptureAddress +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_AVAILABLE
auto vulkan :: toString (
        Type ( DedicatedAllocationBufferCreateInfoNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( DedicatedAllocationBufferCreateInfoNVidia ) ) " " +
           "{ structureType = "_s       + toString ( info.structureType ) +
           ", pNext = "                 + engine :: toString ( info.pNext ) +
           ", dedicatedAllocation = "   + ( info.dedicatedAllocation == VK_TRUE ? "true" : "false" ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto vulkan :: toString (
        Type ( ExternalMemoryBufferCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ExternalMemoryBufferCreateInfo ) ) " " +
           "{ structureType = "_s       + toString ( info.structureType ) +
           ", pNext = "                 + engine :: toString ( info.pNext ) +
           ", handleTypes = "           + :: flagsToString < Type ( ExternalMemoryHandleTypeFlag ) > ( info.handleTypes ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_DECODE_H264_AVAILABLE
auto vulkan :: toString (
        Type ( VideoDecodeH264Profile ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( VideoDecodeH264Profile ) ) " " +
           "{ structureType = "_s       + toString ( info.structureType ) +
           ", pNext = "                 + engine :: toString ( info.pNext ) +
           ", stdProfileIdc = "         + (int) info.stdProfileIdc +
           ", pictureLayout = "         + toString ( info.pictureLayout ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_DECODE_H265_AVAILABLE
auto vulkan :: toString (
        Type ( VideoDecodeH265Profile ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( VideoDecodeH265Profile ) ) " " +
           "{ structureType = "_s       + toString ( info.structureType ) +
           ", pNext = "                 + engine :: toString ( info.pNext ) +
           ", stdProfileIdc = "         + (int) info.stdProfileIdc +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_ENCODE_H264_AVAILABLE
auto vulkan :: toString (
        Type ( VideoEncodeH264Profile ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( VideoEncodeH264Profile ) ) " " +
           "{ structureType = "_s       + toString ( info.structureType ) +
           ", pNext = "                 + engine :: toString ( info.pNext ) +
           ", stdProfileIdc = "         + (int) info.stdProfileIdc +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_ENCODE_H265_AVAILABLE
auto vulkan :: toString (
        Type ( VideoEncodeH265Profile ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( VideoEncodeH265Profile ) ) " " +
           "{ structureType = "_s       + toString ( info.structureType ) +
           ", pNext = "                 + engine :: toString ( info.pNext ) +
           ", stdProfileIdc = "         + (int) info.stdProfileIdc +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE
auto vulkan :: toString (
        Type ( VideoProfile ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( VideoProfile ) ) " " +
           "{ structureType = "_s       + toString ( info.structureType ) +
           ", pNext = "                 + engine :: toString ( info.pNext ) +
           ", videoCodecOperation = "   + toString ( info.videoCodecOperation ) +
           ", chromaSubsampling = "     + :: flagsToString < Type ( VideoChromaSubsamplingFlag ) > ( info.chromaSubsampling ) +
           ", lumaBitDepth = "          + :: flagsToString < Type ( VideoComponentBitDepthFlag ) > ( info.lumaBitDepth ) +
           ", chromaBitDepth = "        + :: flagsToString < Type ( VideoComponentBitDepthFlag ) > ( info.chromaBitDepth ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE
auto vulkan :: toString (
        Type ( VideoProfiles ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( VideoProfile ) ) " " +
           "{ structureType = "_s       + toString ( info.structureType ) +
           ", pNext = "                 + engine :: toString ( info.pNext ) +
           ", profileCount = "          + info.profileCount +
           ", profiles = "              + :: toStringVulkan ( info.profileCount, info.pProfiles ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( BufferViewCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( BufferViewCreateInfo ) ) " " +
           "{ structureType = "_s       + toString ( info.structureType ) +
           ", pNext = "                 + engine :: toString ( info.pNext ) +
           ", flags = "                 + :: flagsToString ( info.flags ) +
           ", buffer = "                + engine :: toString ( info.buffer ) +
           ", format = "                + toString ( info.format ) +
           ", offset = "                + toString ( info.offset ) +
           ", range = "                 + toString ( info.range ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( ImageType )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case ImageType1D: { asString = "1D"; break; }
        case ImageType2D: { asString = "2D"; break; }
        case ImageType3D: { asString = "3D"; break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( ImageTiling )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case ImageTilingOptimal:            { asString = "Optimal";             break; }
        case ImageTilingLinear:             { asString = "Linear";              break; }
#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_DRM_FORMAT_MODIFIER_AVAILABLE
        case ImageTilingDrmFormatModifier:  { asString = "Drm Format Modifier"; break; }
#endif
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( ImageCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ImageCreateInfo ) ) " " +
           "{ structureType = "_s       + toString ( info.structureType ) +
           ", pNext = "                 + engine :: toString ( info.pNext ) +
           ", flags = "                 + :: flagsToString < Type ( ImageCreateFlag ) > ( info.flags ) +
           ", imageType = "             + toString ( info.imageType ) +
           ", format = "                + toString ( info.format ) +
           ", extent = "                + toString ( info.extent ) +
           ", mipLevels = "             + info.mipLevels +
           ", arrayLayers = "           + info.arrayLayers +
           ", samples = "               + toString ( info.samples ) +
           ", tiling = "                + toString ( info.tiling ) +
           ", usage = "                 + :: flagsToString < Type ( ImageUsageFlag ) > ( info.usage ) +
           ", sharingMode = "           + toString ( info.sharingMode ) +
           ", queueFamilyIndexCount = " + info.queueFamilyIndexCount +
           ", queueFamilyIndices = "    + :: toStringRegular ( info.queueFamilyIndexCount, info.pQueueFamilyIndices ) +
           ", initialLayout = "         + toString ( info.initialLayout ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_BUFFER_COLLECTION_AVAILABLE
auto vulkan :: toString (
        Type ( BufferCollectionImageCreateInfoFuchsia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( BufferCollectionImageCreateInfoFuchsia ) ) " " +
           "{ structureType = "_s       + toString ( info.structureType ) +
           ", pNext = "                 + engine :: toString ( info.pNext ) +
           ", collection = "            + toString ( info.collection ) +
           ", index = "                 + info.index +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_AVAILABLE
auto vulkan :: toString (
        Type ( DedicatedAllocationImageCreateInfoNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( DedicatedAllocationImageCreateInfoNVidia ) ) " " +
           "{ structureType = "_s       + toString ( info.structureType ) +
           ", pNext = "                 + engine :: toString ( info.pNext ) +
           ", dedicatedAllocation = "   + ( info.dedicatedAllocation == VK_TRUE ? "true" : "false" ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_AVAILABLE
auto vulkan :: toString (
        Type ( ExternalFormatAndroid ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ExternalFormatAndroid ) ) " " +
           "{ structureType = "_s       + toString ( info.structureType ) +
           ", pNext = "                 + engine :: toString ( info.pNext ) +
           ", externalFormat = "        + info.externalFormat +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto vulkan :: toString (
        Type ( ExternalMemoryImageCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ExternalMemoryImageCreateInfo ) ) " " +
           "{ structureType = "_s       + toString ( info.structureType ) +
           ", pNext = "                 + engine :: toString ( info.pNext ) +
           ", handleTypes = "           + :: flagsToString < Type ( ExternalMemoryHandleTypeFlag ) > ( info.handleTypes ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_AVAILABLE
auto vulkan :: toString (
        Type ( ExternalMemoryImageCreateInfoNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ExternalMemoryImageCreateInfoNVidia ) ) " " +
           "{ structureType = "_s       + toString ( info.structureType ) +
           ", pNext = "                 + engine :: toString ( info.pNext ) +
           ", handleTypes = "           + :: flagsToString < Type ( ExternalMemoryHandleTypeFlag ) > ( info.handleTypes ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( SubresourceLayout ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( SubresourceLayout ) ) " " +
           "{ offset = "_s          + toString ( info.offset ) +
           ", size = "              + toString ( info.size ) +
           ", rowPitch = "          + toString ( info.rowPitch ) +
           ", arrayPitch = "        + toString ( info.arrayPitch ) +
           ", depthPitch = "        + toString ( info.depthPitch ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_DRM_FORMAT_MODIFIER_AVAILABLE
auto vulkan :: toString (
        Type ( ImageDrmFormatModifierExplicitCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ImageDrmFormatModifierExplicitCreateInfo ) ) " " +
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", drmFormatModifier = "             + info.drmFormatModifier +
           ", drmFormatModifierPlaneCount = "   + info.drmFormatModifierPlaneCount +
           ", planeLayouts = "                  + :: toStringVulkan ( info.drmFormatModifierPlaneCount, info.pPlaneLayouts ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_DRM_FORMAT_MODIFIER_AVAILABLE
auto vulkan :: toString (
        Type ( ImageDrmFormatModifierListCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ImageDrmFormatModifierListCreateInfo ) ) " " +
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", drmFormatModifierCount = "        + info.drmFormatModifierCount +
           ", drmFormatModifiers = "            + :: toStringRegular ( info.drmFormatModifierCount, info.pDrmFormatModifiers ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
auto vulkan :: toString (
        Type ( ImageStencilUsageCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ImageStencilUsageCreateInfo ) ) " " +
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", stencilUsage = "                  + :: flagsToString < Type ( ImageUsageFlag ) > ( info.stencilUsage ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE
auto vulkan :: toString (
        Type ( ImageSwapChainCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ImageStencilUsageCreateInfo ) ) " " +
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", stencilUsage = "                  + engine :: toString ( info.swapchain ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( ImageSubresource ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ImageSubresource ) ) " " +
           "{ aspectMask = "_s  + :: flagsToString < Type ( ImageAspectFlag ) > ( info.aspectMask ) +
           ", mipLevel = "      + info.mipLevel +
           ", arrayLayer = "    + info.arrayLayer +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_ASTC_DECODE_MODE_AVAILABLE
auto vulkan :: toString (
        Type ( ImageViewASTCDecodeMode ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ImageViewASTCDecodeMode ) ) " " +
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", decodeMode = "                    + toString ( info.decodeMode ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_VIEW_MIN_LOD_AVAILABLE
auto vulkan :: toString (
        Type ( ImageViewMinLodCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( ImageViewMinLodCreateInfo ) ) " " +
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", minLod = "                        + info.minLod +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
auto vulkan :: toString (
        Type ( AccelerationStructureType )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case AccelerationStructureTypeTopLevel:     { asString = "Top Level";       break; }
        case AccelerationStructureTypeBottomLevel:  { asString = "Bottom Level";    break; }
        case AccelerationStructureTypeGeneric:      { asString = "Generic";         break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
auto vulkan :: toString (
        Type ( BuildAccelerationStructureFlag )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case BuildAccelerationStructureFlagAllowUpdate:     { asString = "Allow Update";        break; }
        case BuildAccelerationStructureFlagAllowCompaction: { asString = "Allow Compaction";    break; }
        case BuildAccelerationStructureFlagPreferFastTrace: { asString = "Prefer Fast Trace";   break; }
        case BuildAccelerationStructureFlagPreferFastBuild: { asString = "Prefer Fast Build";   break; }
        case BuildAccelerationStructureFlagLowMemory:       { asString = "Low Memory";          break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
auto vulkan :: toString (
        Type ( GeometryType )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case GeometryTypeTriangles: { asString = "Triangles";   break; }
        case GeometryTypeAABBS:     { asString = "AABBS";       break; }
        case GeometryTypeInstances: { asString = "Instances";   break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
auto vulkan :: toString (
        Type ( GeometryFlag )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case GeometryFlagOpaque:                        { asString = "Opaque";                          break; }
        case GeometryFlagNoDuplicateAnyHitInvocation:   { asString = "No Duplicate Any Hit Invocation"; break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
auto vulkan :: toString (
        Type ( AccelerationStructureTypeNVidia )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case AccelerationStructureTypeNVidiaTopLevel:     { asString = "Top Level";       break; }
        case AccelerationStructureTypeNVidiaBottomLevel:  { asString = "Bottom Level";    break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
auto vulkan :: toString (
        Type ( BuildAccelerationStructureFlagNVidia )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case BuildAccelerationStructureFlagNVidiaAllowUpdate:     { asString = "Allow Update";        break; }
        case BuildAccelerationStructureFlagNVidiaAllowCompaction: { asString = "Allow Compaction";    break; }
        case BuildAccelerationStructureFlagNVidiaPreferFastTrace: { asString = "Prefer Fast Trace";   break; }
        case BuildAccelerationStructureFlagNVidiaPreferFastBuild: { asString = "Prefer Fast Build";   break; }
        case BuildAccelerationStructureFlagNVidiaLowMemory:       { asString = "Low Memory";          break; }
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE
        case BuildAccelerationStructureFlagNVidiaMotion:          { asString = "Motion";              break; }
#endif
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
auto vulkan :: toString (
        Type ( GeometryTypeNVidia )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case GeometryTypeNVidiaTriangles: { asString = "Triangles";   break; }
        case GeometryTypeNVidiaAABBS:     { asString = "AABBS";       break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
auto vulkan :: toString (
        Type ( GeometryFlagNVidia )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case GeometryFlagNVidiaOpaque:                        { asString = "Opaque";                          break; }
        case GeometryFlagNVidiaNoDuplicateAnyHitInvocation:   { asString = "No Duplicate Any Hit Invocation"; break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( IndexType )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case IndexTypeUInt16:   { asString = "UInt16";  break; }
        case IndexTypeUInt32:   { asString = "UInt32";  break; }
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
        case IndexTypeNone:     { asString = "None";    break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_INDEX_TYPE_UINT8_AVAILABLE
        case IndexTypeUInt8:    { asString = "UInt8";   break; }
#endif
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
auto vulkan :: toString (
        Type ( GeometryAABBNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( GeometryAABBNVidia ) ) " " +
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", aabbData = "                      + engine :: toString ( info.aabbData ) +
           ", numAABBs = "                      + info.numAABBs +
           ", stride = "                        + info.stride +
           ", offset = "                        + toString ( info.offset ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
auto vulkan :: toString (
        Type ( GeometryTrianglesNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( GeometryTrianglesNVidia ) ) " " +
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", vertexData = "                    + engine :: toString ( info.vertexData ) +
           ", vertexOffset = "                  + toString ( info.vertexOffset ) +
           ", vertexCount = "                   + info.vertexCount +
           ", vertexStride = "                  + toString ( info.vertexStride ) +
           ", vertexFormat = "                  + toString ( info.vertexFormat ) +
           ", indexData = "                     + engine :: toString ( info.indexData ) +
           ", indexOffset = "                   + toString ( info.indexOffset ) +
           ", indexCount = "                    + info.indexCount +
           ", indexType = "                     + toString ( info.indexType ) +
           ", transformData = "                 + engine :: toString ( info.transformData ) +
           ", transformOffset = "               + toString ( info.transformOffset ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
auto vulkan :: toString (
        Type ( GeometryDataNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( GeometryDataNVidia ) ) " " +
           "{ triangles = "_s   + toString ( info.triangles ) +
           ", aabbs = "         + toString ( info.aabbs ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
auto vulkan :: toString (
        Type ( GeometryNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( GeometryNVidia ) ) " " +
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", geometryType = "                  + toString ( info.geometryType ) +
           ", geometry = "                      + toString ( info.geometry ) +
           ", flags = "                         + :: flagsToString < Type ( GeometryFlagNVidia ) > ( info.flags ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
auto vulkan :: toString (
        Type ( AccelerationStructureInfoNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( AccelerationStructureInfoNVidia ) ) " " +
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", type = "                          + toString ( info.type ) +
           ", flags = "                         + :: flagsToString < Type ( BuildAccelerationStructureFlagNVidia ) > ( info.flags ) +
           ", instanceCount = "                 + info.instanceCount +
           ", geometryCount = "                 + info.geometryCount +
           ", geometries = "                    + :: toStringVulkan ( info.geometryCount, info.pGeometries ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
auto vulkan :: toString (
        Type ( AccelerationStructureCreateInfoNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( AccelerationStructureCreateInfoNVidia ) ) " " +
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", compactedSize = "                 + toString ( info.compactedSize ) +
           ", info = "                          + toString ( info.info ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
auto vulkan :: toString (
        Type ( AccelerationStructureCreateFlag )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case AccelerationStructureCreateFlagDeviceAddressCaptureReplay: { asString = "Device Address Capture Replay";   break; }
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE
        case AccelerationStructureCreateFlagMotionNVidia:               { asString = "Motion Blur";                     break; }
#endif
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
auto vulkan :: toString (
        Type ( AccelerationStructureBuildType )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case AccelerationStructureBuildTypeHost:            { asString = "Host";            break; }
        case AccelerationStructureBuildTypeDevice:          { asString = "Device";          break; }
        case AccelerationStructureBuildTypeHostOrDevice:    { asString = "Host or Device";  break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
auto vulkan :: toString (
        Type ( BuildAccelerationStructureMode )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case BuildAccelerationStructureModeBuild:   { asString = "Build";   break; }
        case BuildAccelerationStructureModeUpdate:  { asString = "Update";  break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
auto vulkan :: toString (
        Type ( AccelerationStructureCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( AccelerationStructureCreateInfo ) ) " " +
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", flags = "                         + :: flagsToString < Type ( AccelerationStructureCreateFlag ) > ( info.flags ) +
           ", buffer = "                        + engine :: toString ( info.buffer ) +
           ", offset = "                        + engine :: toString ( info.offset ) +
           ", size = "                          + engine :: toString ( info.size ) +
           ", type = "                          + toString ( info.type ) +
           ", deviceAddress = "                 + toString ( info.deviceAddress ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE
auto vulkan :: toString (
        Type ( AccelerationStructureMotionInfoNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( AccelerationStructureMotionInfoNVidia ) ) " " +
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", maxInstances = "                  + info.maxInstances +
           ", flags = "                         + :: flagsToString ( info.flags )  +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
auto vulkan :: toString (
        Type ( DeviceOrHostAddress ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( DeviceOrHostAddress ) ) " " +
           "{ deviceAddress = "_s   + toString ( info.deviceAddress ) +
           ", hostAddress = "       + engine :: toString ( info.hostAddress ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
auto vulkan :: toString (
        Type ( DeviceOrHostAddressConst ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( DeviceOrHostAddressConst ) ) " " +
           "{ deviceAddress = "_s   + toString ( info.deviceAddress ) +
           ", hostAddress = "       + engine :: toString ( info.hostAddress ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
auto vulkan :: toString (
        Type ( AccelerationStructureGeometryTrianglesData ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( AccelerationStructureGeometryTrianglesData ) ) " " +
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", vertexFormat = "                  + toString ( info.vertexFormat ) +
           ", vertexData = "                    + toString ( info.vertexData ) +
           ", vertexStride = "                  + toString( info.vertexStride ) +
           ", maxVertex = "                     + info.maxVertex +
           ", indexType = "                     + toString ( info.indexType ) +
           ", indexData = "                     + toString ( info.indexData ) +
           ", transformData = "                 + toString ( info.transformData ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
auto vulkan :: toString (
        Type ( AccelerationStructureGeometryAabbsData ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( AccelerationStructureGeometryAabbsData ) ) " " +
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", data = "                          + toString ( info.data ) +
           ", stride = "                        + toString ( info.stride ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
auto vulkan :: toString (
        Type ( AccelerationStructureGeometryInstancesData ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( AccelerationStructureGeometryInstancesData ) ) " " +
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", arrayOfPointers = "               + ( info.arrayOfPointers == VK_TRUE ? "true" : "false" ) +
           ", data = "                          + toString ( info.data ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
auto vulkan :: toString (
        Type ( AccelerationStructureGeometryData ) const & info
) noexcept -> String {

    auto extractFromUnion = [] ( Type ( GenericInStructure ) const * pInfo ) noexcept {
        switch ( pInfo->structureType ) {
            case StructureTypeAccelerationStructureGeometryTrianglesData:
                return toString ( * reinterpret_cast < Type ( AccelerationStructureGeometryTrianglesData ) const * > ( pInfo ) );
            case StructureTypeAccelerationStructureGeometryAABBSData:
                return toString ( * reinterpret_cast < Type ( AccelerationStructureGeometryAabbsData ) const * > ( pInfo ) );
            case StructureTypeAccelerationStructureGeometryInstancesData:
                return toString ( * reinterpret_cast < Type ( AccelerationStructureGeometryInstancesData ) const * > ( pInfo ) );
            default:
                return "Invalid Structure Format"_s;
        }
    };

    return __C_ENG_STRINGIFY ( Type ( AccelerationStructureGeometryData ) ) " -> " +
            extractFromUnion ( reinterpret_cast < Type ( GenericInStructure ) const * > ( & info ) );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
auto vulkan :: toString (
        Type ( AccelerationStructureGeometry ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( AccelerationStructureGeometry ) ) " " +
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", geometryType = "                  + toString ( info.geometryType ) +
           ", geometry = "                      + toString ( info.geometry ) +
           ", flags = "                         + :: flagsToString < Type ( GeometryFlag ) > ( info.flags ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
auto vulkan :: toString (
        Type ( AccelerationStructureBuildGeometryInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( AccelerationStructureBuildGeometryInfo ) ) " " +
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", type = "                          + toString ( info.type ) +
           ", flags = "                         + :: flagsToString < Type ( BuildAccelerationStructureFlag ) > ( info.flags ) +
           ", mode = "                          + toString ( info.mode ) +
           ", source = "                        + engine :: toString ( info.source ) +
           ", destination = "                   + engine :: toString ( info.destination ) +
           ", geometryCount = "                 + info.geometryCount +
           ", pGeometries = "                   + :: toStringVulkan ( info.geometryCount, info.pGeometries ) +
           ", ppGeometries = "                  + :: toStringEngine ( info.geometryCount, info.ppGeometries ) +
           ", scratchData = "                   + toString ( info.scratchData ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
auto vulkan :: toString (
        Type ( AccelerationStructureBuildSizesInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( AccelerationStructureBuildSizesInfo ) ) " " +
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", accelerationStructureSize = "     + toString ( info.accelerationStructureSize ) +
           ", updateScratchSize = "             + toString ( info.updateScratchSize ) +
           ", buildScratchSize = "              + toString ( info.buildScratchSize ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE
auto vulkan :: toString (
        Type ( AccelerationStructureGeometryMotionTrianglesDataNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( AccelerationStructureGeometryMotionTrianglesDataNVidia ) ) " " +
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", vertexData = "                    + toString ( info.vertexData ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
auto vulkan :: toString (
        Type ( AccelerationStructureMemoryRequirementsTypeNVidia )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case AccelerationStructureMemoryRequirementsTypeNVidiaObject:           { asString = "Object";          break; }
        case AccelerationStructureMemoryRequirementsTypeNVidiaBuildScratch:     { asString = "Build Scratch";   break; }
        case AccelerationStructureMemoryRequirementsTypeNVidiaUpdateScratch:    { asString = "Update Scratch";  break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
auto vulkan :: toString (
        Type ( AccelerationStructureMemoryRequirementsInfoNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( AccelerationStructureMemoryRequirementsInfoNVidia ) ) " " +
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", type = "                          + toString ( info.type ) +
           ", accelerationStructure = "         + engine :: toString ( info.accelerationStructure ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( MemoryRequirements ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( MemoryRequirements ) ) " " +
           "{ size = "_s            + toString ( info.size ) +
           ", alignment = "         + toString ( info.alignment ) +
           ", memoryTypeBits = "    + info.memoryTypeBits +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto vulkan :: toString (
        Type ( MemoryRequirements2 ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( MemoryRequirements2 ) ) " " +
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", memoryRequirements = "            + toString ( info.memoryRequirements ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto vulkan :: toString (
        Type ( MemoryDedicatedRequirements ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( MemoryDedicatedRequirements ) ) " " +
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", prefersDedicatedAllocation = "    + ( info.prefersDedicatedAllocation == VK_TRUE ? "true" : "false" ) +
           ", requiresDedicatedAllocation = "   + ( info.requiresDedicatedAllocation == VK_TRUE ? "true" : "false" ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
auto vulkan :: toString (
        Type ( BindAccelerationStructureMemoryInfoNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( BindAccelerationStructureMemoryInfoNVidia ) ) " " +
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", accelerationStructure = "         + engine :: toString ( info.accelerationStructure ) +
           ", memory = "                        + engine :: toString ( info.memory ) +
           ", memoryOffset = "                  + toString ( info.memoryOffset ) +
           ", deviceIndexCount = "              + info.deviceIndexCount +
           ", deviceIndices = "                 + :: toStringRegular ( info.deviceIndexCount, info.pDeviceIndices ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
auto vulkan :: toString (
        Type ( AccelerationStructureDeviceAddressInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( AccelerationStructureDeviceAddressInfo ) ) " " +
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", accelerationStructure = "         + engine :: toString ( info.accelerationStructure ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( SamplerCreateFlag )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE
        case SamplerCreateFlagSubsampled:                       { asString = "Subsampled";                          break; }
        case SamplerCreateFlagSubsampledCoarseReconstruction:   { asString = "Subsampled Coarse Reconstruction";    break; }
#endif
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( Filter )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case FilterNearest: { asString = "Nearest"; break; }
        case FilterLinear:  { asString = "Linear";  break; }
#if __C_ENG_VULKAN_API_EXTENSION_FILTER_CUBIC_AVAILABLE
        case FilterCubic:   { asString = "Cubic";   break; }
#endif
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( SamplerMipmapMode )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case SamplerMipmapModeNearest: { asString = "Nearest"; break; }
        case SamplerMipmapModeLinear:  { asString = "Linear";  break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( SamplerAddressMode )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case SamplerAddressModeRepeat:              { asString = "Repeat";                  break; }
        case SamplerAddressModeMirroredRepeat:      { asString = "Mirrored Repeat";         break; }
        case SamplerAddressModeClampToEdge:         { asString = "Clamp To Edge";           break; }
        case SamplerAddressModeClampToBorder:       { asString = "Clamp To Border";         break; }
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
        case SamplerAddressModeMirrorClampToEdge:   { asString = "Mirror Clamp To Edge";    break; }
#endif
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( BorderColor )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case BorderColorFloatTransparentBlack:  { asString = "Float Transparent Black"; break; }
        case BorderColorIntTransparentBlack:    { asString = "Int Transparent Black";   break; }
        case BorderColorFloatOpaqueBlack:       { asString = "Float Opaque Black";      break; }
        case BorderColorIntOpaqueBlack:         { asString = "Int Opaque Black";        break; }
        case BorderColorFloatOpaqueWhite:       { asString = "Float Opaque White";      break; }
        case BorderColorIntOpaqueWhite:         { asString = "Int Opaque White";        break; }
#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE
        case BorderColorFloatCustom:            { asString = "Float Custom";            break; }
        case BorderColorIntCustom:              { asString = "Int Custom";              break; }
#endif
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
auto vulkan :: toString (
        Type ( SamplerReductionMode )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case SamplerReductionModeWeightedAverage:   { asString = "Weighted Average";    break; }
        case SamplerReductionModeMin:               { asString = "Min";                 break; }
        case SamplerReductionModeMax:               { asString = "Max";                 break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( SamplerCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( SamplerCreateInfo ) ) " " +
           "{ structureType = "_s           + toString ( info.structureType ) +
           ", pNext = "                     + engine :: toString ( info.pNext ) +
           ", flags = "                     + :: flagsToString < Type ( SamplerCreateFlag ) > ( info.flags ) +
           ", magFilter = "                 + toString ( info.magFilter ) +
           ", minFilter = "                 + toString ( info.minFilter ) +
           ", mipmapMode = "                + toString ( info.mipmapMode ) +
           ", addressModeU = "              + toString ( info.addressModeU ) +
           ", addressModeV = "              + toString ( info.addressModeV ) +
           ", addressModeW = "              + toString ( info.addressModeW ) +
           ", mipLodBias = "                + info.mipLodBias +
           ", anisotropyEnable = "          + ( info.anisotropyEnable == VK_TRUE ? "true" : "false" ) +
           ", maxAnisotropy = "             + info.maxAnisotropy +
           ", compareEnable = "             + ( info.compareEnable == VK_TRUE ? "true" : "false" ) +
           ", compareOperation = "          + toString ( info.compareOperation ) +
           ", minLod = "                    + info.minLod +
           ", maxLod = "                    + info.maxLod +
           ", borderColor = "               + toString ( info.borderColor ) +
           ", unnormalizedCoordinates = "   + ( info.unnormalizedCoordinates == VK_TRUE ? "true" : "false" ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_BORDER_COLOR_SWIZZLE_AVAILABLE
auto vulkan :: toString (
        Type ( SamplerBorderColorComponentMappingCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( SamplerBorderColorComponentMappingCreateInfo ) ) " " +
           "{ structureType = "_s           + toString ( info.structureType ) +
           ", pNext = "                     + engine :: toString ( info.pNext ) +
           ", components = "                + toString ( info.components ) +
           ", srgb = "                      + ( info.srgb == VK_TRUE ? "true" : "false" ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE
auto vulkan :: toString (
        Type ( SamplerCustomBorderColorCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( SamplerCustomBorderColorCreateInfo ) ) " " +
           "{ structureType = "_s           + toString ( info.structureType ) +
           ", pNext = "                     + engine :: toString ( info.pNext ) +
           ", customBorderColor = "         + toString ( info.customBorderColor ) +
           ", format = "                    + toString ( info.format ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
auto vulkan :: toString (
        Type ( SamplerReductionModeCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( SamplerReductionModeCreateInfo ) ) " " +
           "{ structureType = "_s           + toString ( info.structureType ) +
           ", pNext = "                     + engine :: toString ( info.pNext ) +
           ", reductionMode = "             + toString ( info.reductionMode ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto vulkan :: toString (
        Type ( SamplerYCBCRModelConversion )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case SamplerYCBCRModelConversionRGBIdentity:    { asString = "RGB Identity";    break; }
        case SamplerYCBCRModelConversionYCBCRIdentity:  { asString = "YCBCR Identity";  break; }
        case SamplerYCBCRModelConversion709:            { asString = "709";             break; }
        case SamplerYCBCRModelConversion601:            { asString = "601";             break; }
        case SamplerYCBCRModelConversion2020:           { asString = "2020";            break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto vulkan :: toString (
        Type ( SamplerYCBCRRange )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case SamplerYCBCRRangeITUFull:    { asString = "ITU Full";    break; }
        case SamplerYCBCRRangeITUNarrow:  { asString = "ITU Narrow";  break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto vulkan :: toString (
        Type ( ChromaLocation )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case ChromaLocationCositedEven:     { asString = "Cosited Even";    break; }
        case ChromaLocationMidpoint:        { asString = "Midpoin";         break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto vulkan :: toString (
        Type ( SamplerYCBCRConversionCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( SamplerYCBCRConversionCreateInfo ) ) " " +
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", format = "                        + toString ( info.format ) +
           ", ycbcrModel = "                    + toString ( info.ycbcrModel ) +
           ", ycbcrRange = "                    + toString ( info.ycbcrRange ) +
           ", components = "                    + toString ( info.components ) +
           ", xChromaOffset = "                 + toString ( info.xChromaOffset ) +
           ", yChromaOffset = "                 + toString ( info.yChromaOffset ) +
           ", chromaFilter = "                  + toString ( info.chromaFilter ) +
           ", forceExplicitReconstruction = "   + ( info.forceExplicitReconstruction == VK_TRUE ? "true" : "false" ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( DescriptorSetLayoutCreateFlag )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
        case DescriptorSetLayoutCreateFlagUpdateAfterBindPool:  { asString = "Update After Bind Pool";  break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PUSH_DESCRIPTOR_AVAILABLE
        case DescriptorSetLayoutCreateFlagPushDescriptor:       { asString = "Push Descriptor";         break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE
        case DescriptorSetLayoutCreateFlagHostOnlyPoolValve:    { asString = "Host Only Pool";          break; }
#endif
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( DescriptorType )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case DescriptorTypeSampler:                     { asString = "Sampler";                         break; }
        case DescriptorTypeCombinedImageSampler:        { asString = "Combined Image Sampler";          break; }
        case DescriptorTypeSampledImage:                { asString = "Sampled Image";                   break; }
        case DescriptorTypeStorageImage:                { asString = "Storage Image";                   break; }
        case DescriptorTypeUniformTexelBuffer:          { asString = "Uniform Texel Buffer";            break; }
        case DescriptorTypeStorageTexelBuffer:          { asString = "Storage Texel Buffer";            break; }
        case DescriptorTypeUniformBuffer:               { asString = "Uniform Buffer";                  break; }
        case DescriptorTypeStorageBuffer:               { asString = "Storage Buffer";                  break; }
        case DescriptorTypeUniformBufferDynamic:        { asString = "Uniform Buffer Dynamic";          break; }
        case DescriptorTypeStorageBufferDynamic:        { asString = "Storage Buffer Dynamic";          break; }
        case DescriptorTypeInputAttachment:             { asString = "Input Attachment";                break; }
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE
        case DescriptorTypeInlineUniformBlock:          { asString = "Inline Uniform Block";            break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
        case DescriptorTypeAccelerationStructure:       { asString = "Acceleration Structure";          break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
        case DescriptorTypeAccelerationStructureNVidia: { asString = "Acceleration Structure NVidia";   break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE
        case DescriptorTypeMutableValve:                { asString = "Mutable Valve";                   break; }
#endif
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
auto vulkan :: toString (
        Type ( DescriptorBindingFlag )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case DescriptorBindingFlagUpdateAfterBind:          { asString = "Update After Bind";           break; }
        case DescriptorBindingFlagUpdateUnusedWhilePending: { asString = "Update Unused While Pending"; break; }
        case DescriptorBindingFlagPartiallyBound:           { asString = "Partially Bound";             break; }
        case DescriptorBindingFlagVariableDescriptorCount:  { asString = "Variable Descriptor Count";   break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( DescriptorSetLayoutBinding ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( DescriptorSetLayoutBinding ) ) " " +
           "{ binding = "_s             + info.binding +
           ", descriptorType = "        + engine :: toString ( info.descriptorType ) +
           ", descriptorCount = "       + info.descriptorCount +
           ", stageFlags = "            + :: flagsToString < Type ( ShaderStageFlag ) > ( info.stageFlags ) +
           ", pImmutableSamplers = "    + engine :: toString ( info.pImmutableSamplers ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( DescriptorSetLayoutCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( DescriptorSetLayoutCreateInfo ) ) " " +
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", flags = "                         + :: flagsToString < Type ( DescriptorSetLayoutCreateFlag ) > ( info.flags ) +
           ", bindingCount = "                  + info.bindingCount +
           ", bindings = "                      + :: toStringVulkan ( info.bindingCount, info.pBindings ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
auto vulkan :: toString (
        Type ( DescriptorSetLayoutBindingFlagsCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( DescriptorSetLayoutBindingFlagsCreateInfo ) ) " " +
           "{ structureType = "_s               + toString ( info.structureType ) +
           ", pNext = "                         + engine :: toString ( info.pNext ) +
           ", bindingCount = "                  + info.bindingCount +
           ", bindingFlags = "                  + :: toStringFlags ( info.bindingCount, info.pBindingFlags ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE
auto vulkan :: toString (
        Type ( MutableDescriptorTypeListValve ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( MutableDescriptorTypeListValve ) ) " " +
           "{ descriptorTypeCount = "_s + info.descriptorTypeCount +
           ", descriptorTypes = "       + :: toStringVulkan ( info.descriptorTypeCount, info.pDescriptorTypes ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE
auto vulkan :: toString (
        Type ( MutableDescriptorTypeCreateInfoValve ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( MutableDescriptorTypeCreateInfoValve ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", mutableDescriptorTypeListCount = "_s  + info.mutableDescriptorTypeListCount +
           ", pMutableDescriptorTypeLists = "       + :: toStringVulkan ( info.mutableDescriptorTypeListCount, info.pMutableDescriptorTypeLists ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto vulkan :: toString (
        Type ( DescriptorSetLayoutSupport ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( DescriptorSetLayoutSupport ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", supported = "                         + ( info.supported == VK_TRUE ? "true" : "false" ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
auto vulkan :: toString (
        Type ( DescriptorSetVariableDescriptorCountLayoutSupport ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( DescriptorSetVariableDescriptorCountLayoutSupport ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", maxVariableDescriptorCount = "        + info.maxVariableDescriptorCount +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( PushConstantRange ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PushConstantRange ) ) " " +
           "{ stageFlags = "_s  + :: flagsToString < Type ( ShaderStageFlag ) > ( info.stageFlags ) +
           ", offset = "        + info.offset +
           ", size = "          + info.size +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineLayoutCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PipelineLayoutCreateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", flags = "                             + :: flagsToString ( info.flags ) +
           ", setLayoutCount = "                    + info.setLayoutCount +
           ", setLayouts = "                        + :: toStringEngine ( info.setLayoutCount, info.pSetLayouts ) +
           ", pushConstantRangeCount = "            + info.pushConstantRangeCount +
           ", pushConstantRanges = "                + :: toStringVulkan ( info.pushConstantRangeCount, info.pPushConstantRanges ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( DescriptorPoolCreateFlag )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case DescriptorPoolCreateFlagFreeDescriptorSet: { asString = "Free Descriptor Set";     break; }
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
        case DescriptorPoolCreateFlagUpdateAfterBind:   { asString = "Update After Bind";       break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE
        case DescriptorPoolCreateFlagHostOnlyValve:     { asString = "Host Only";               break; }
#endif
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( DescriptorPoolCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( DescriptorPoolCreateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", flags = "                             + :: flagsToString < Type ( DescriptorPoolCreateFlag ) > ( info.flags ) +
           ", maxSets = "                           + info.maxSets +
           ", poolSizeCount = "                     + info.poolSizeCount +
           ", poolSizes = "                         + :: toStringVulkan ( info.poolSizeCount, info.pPoolSizes ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( DescriptorPoolSize ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( DescriptorPoolSize ) ) " " +
           "{ type = "_s            + toString ( info.type ) +
           ", descriptorCount = "   + info.descriptorCount +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE
auto vulkan :: toString (
        Type ( DescriptorPoolInlineUniformBlockCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( DescriptorPoolInlineUniformBlockCreateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", maxInlineUniformBlockBindings = "     + info.maxInlineUniformBlockBindings +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( DescriptorSetAllocateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( DescriptorSetAllocateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", descriptorPool = "                    + engine :: toString ( info.descriptorPool ) +
           ", descriptorSetCount = "                + info.descriptorSetCount +
           ", setLayouts = "                        + :: toStringEngine ( info.descriptorSetCount, info.pSetLayouts ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
auto vulkan :: toString (
        Type ( DescriptorSetVariableDescriptorCountAllocateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( DescriptorSetVariableDescriptorCountAllocateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", descriptorSetCount = "                + info.descriptorSetCount +
           ", descriptorCounts = "                  + :: toStringRegular ( info.descriptorSetCount, info.pDescriptorCounts ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( DescriptorBufferInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( DescriptorBufferInfo ) ) " " +
           "{ buffer = "_s  + engine :: toString ( info.buffer ) +
           ", offset = "    + toString ( info.offset ) +
           ", range = "     + toString ( info.range ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( DescriptorImageInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( DescriptorImageInfo ) ) " " +
           "{ sampler = "_s     + engine :: toString ( info.sampler ) +
           ", imageView = "     + engine :: toString ( info.imageView ) +
           ", imageLayout = "   + toString ( info.imageLayout ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( WriteDescriptorSet ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( WriteDescriptorSet ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", destinationSet = "                    + engine :: toString ( info.destinationSet ) +
           ", destinationBinding = "                + info.destinationBinding +
           ", destinationArrayElement = "           + info.destinationArrayElement +
           ", descriptorCount = "                   + info.descriptorCount +
           ", descriptorType = "                    + toString ( info.descriptorType ) +
           ", pImageInfo = "                        + engine :: toString ( info.pImageInfo ) +
           ", pBufferInfo = "                       + engine :: toString ( info.pBufferInfo ) +
           ", pTexelBufferView = "                  + engine :: toString ( info.pTexelBufferView ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
auto vulkan :: toString (
        Type ( WriteDescriptorSetAccelerationStructure ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( WriteDescriptorSetAccelerationStructure ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", accelerationStructureCount = "        + info.accelerationStructureCount +
           ", accelerationStructures = "            + :: toStringEngine ( info.accelerationStructureCount, info.pAccelerationStructures ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
auto vulkan :: toString (
        Type ( WriteDescriptorSetAccelerationStructureNVidia ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( WriteDescriptorSetAccelerationStructureNVidia ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", accelerationStructureCount = "        + info.accelerationStructureCount +
           ", accelerationStructures = "            + :: toStringEngine ( info.accelerationStructureCount, info.pAccelerationStructures ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE
auto vulkan :: toString (
        Type ( WriteDescriptorSetInlineUniformBlock ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( WriteDescriptorSetInlineUniformBlock ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", dataSize = "                          + info.dataSize +
           ", pData = "                             + engine :: toString ( info.pData ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( CopyDescriptorSet ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( CopyDescriptorSet ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", sourceSet = "                         + engine :: toString ( info.sourceSet ) +
           ", sourceBinding = "                     + info.sourceBinding +
           ", sourceArrayElement = "                + info.sourceArrayElement +
           ", destinationSet = "                    + engine :: toString ( info.destinationSet ) +
           ", destinationBinding = "                + info.destinationBinding +
           ", destinationArrayElement = "           + info.destinationArrayElement +
           ", descriptorCount = "                   + info.descriptorCount +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto vulkan :: toString (
        Type ( DescriptorUpdateTemplateType )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case DescriptorUpdateTemplateTypeDescriptorSet:     { asString = "Descriptor Set";      break; }
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PUSH_DESCRIPTOR_AVAILABLE
        case DescriptorUpdateTemplateTypePushDescriptors:   { asString = "Push Descriptors";    break; }
#endif
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto vulkan :: toString (
        Type ( DescriptorUpdateTemplateEntry ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( DescriptorUpdateTemplateEntry ) ) " " +
           "{ destinationBinding = "_s      + info.destinationBinding +
           ", destinationArrayElement = "   + info.destinationArrayElement +
           ", descriptorCount = "           + info.descriptorCount +
           ", descriptorType = "            + toString ( info.descriptorType ) +
           ", offset = "                    + info.offset +
           ", stride = "                    + info.stride +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
auto vulkan :: toString (
        Type ( DescriptorUpdateTemplateCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( DescriptorUpdateTemplateCreateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", flags = "                             + :: flagsToString ( info.flags ) +
           ", descriptorUpdateEntryCount = "        + info.descriptorUpdateEntryCount +
           ", descriptorUpdateEntries = "           + :: toStringVulkan ( info.descriptorUpdateEntryCount, info.pDescriptorUpdateEntries ) +
           ", templateType = "                      + toString ( info.templateType ) +
           ", descriptorSetLayout = "               + engine :: toString ( info.descriptorSetLayout ) +
           ", pipelineBindPoint = "                 + engine :: toString ( info.pipelineBindPoint ) +
           ", pipelineLayout = "                    + engine :: toString ( info.pipelineLayout ) +
           ", set = "                               + info.set +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
auto vulkan :: toString (
        Type ( BufferDeviceAddressInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( BufferDeviceAddressInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", buffer = "                            + engine :: toString ( info.buffer ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( QueryType )  type
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( type ) {
        case QueryTypeOcclusion:                                { asString = "Occlusion";      break; }
        case QueryTypePipelineStatistics:                       { asString = "Pipeline Statistics";      break; }
        case QueryTypeTimestamp:                                { asString = "Timestamp";      break; }
#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE
        case QueryTypeResultStatusOnly:                         { asString = "Result Status Only";      break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE
        case QueryTypeTransformFeedbackStream:                  { asString = "Transform Feedback Stream";      break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
        case QueryTypePerformanceQuery:                         { asString = "Performance Query";      break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
        case QueryTypeAccelerationStructureCompactedSize:       { asString = "Acceleration Structure Compacted Size";      break; }
        case QueryTypeAccelerationStructureSerializationSize:   { asString = "Acceleration Structure Serialization Size";      break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
        case QueryTypeAccelerationStructureCompactedSizeNVidia: { asString = "Acceleration Structure Compacted Size NVidia";      break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
        case QueryTypePerformanceQueryIntel:                    { asString = "PerformanceQueryIntel";      break; }
#endif
#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_ENCODE_QUEUE_AVAILABLE
        case QueryTypeVideoEncodeBitstreamBufferRange:          { asString = "Video Encode Bitstream Buffer Range";      break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_PRIMITIVES_GENERATED_QUERY_AVAILABLE
        case QueryTypePrimitivesGenerated:                      { asString = "Primitives Generated";      break; }
#endif
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( QueryPoolCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( QueryPoolCreateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", flags = "                             + :: flagsToString ( info.flags ) +
           ", queryType = "                         + toString ( info.queryType ) +
           ", queryCount = "                        + info.queryCount +
           ", pipelineStatistics = "                + :: flagsToString < Type ( QueryPipelineStatisticFlag ) > ( info.pipelineStatistics ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
auto vulkan :: toString (
        Type ( QueryPoolSamplingModeIntel )  type
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( type ) {
        case QueryPoolSamplingModeIntelManual:  { asString = "Manual";  break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
auto vulkan :: toString (
        Type ( QueryPoolPerformanceCreateInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( QueryPoolPerformanceCreateInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", queueFamilyIndex = "                  + info.queueFamilyIndex +
           ", counterIndexCount = "                 + info.counterIndexCount +
           ", counterIndices = "                    + :: toStringRegular ( info.counterIndexCount, info.pCounterIndices ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
auto vulkan :: toString (
        Type ( QueryPoolPerformanceCreateInfoIntel ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( QueryPoolPerformanceCreateInfoIntel ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", performanceCountersSampling = "       + toString ( info.performanceCountersSampling ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( QueryResultFlag )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case QueryResultFlag64:                 { asString = "64";                  break; }
        case QueryResultFlagWait:               { asString = "Wait";                break; }
        case QueryResultFlagWithAvailability:   { asString = "With Availability";   break; }
        case QueryResultFlagPartial:            { asString = "Partial";             break; }
        case QueryResultFlagWithStatus:         { asString = "With Status";         break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE
auto vulkan :: toString (
        Type ( QueryResultStatus )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case QueryResultStatusError:      { asString = "Error";      break; }
        case QueryResultStatusNotReady:   { asString = "Not Ready";  break; }
        case QueryResultStatusComplete:   { asString = "Complete";   break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( PipelineDepthStencilStateCreateFlag )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
#if __C_ENG_VULKAN_API_EXTENSION_ARM_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_AVAILABLE
        case PipelineDepthStencilStateCreateFlagRasterizationOrderAttachmentDepthAccess:    { asString = "Rasterization Order Attachment Depth Access";     break; }
        case PipelineDepthStencilStateCreateFlagRasterizationOrderAttachmentStencilAccess:  { asString = "Rasterization Order Attachment Stencil Access";   break; }
#endif
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
auto vulkan :: toString (
        Type ( ImageUsageFlag )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case ImageUsageFlagTransferSource:                  { asString = "Transfer Source";                     break; }
        case ImageUsageFlagTransferDestination:             { asString = "Transfer Destination";                break; }
        case ImageUsageFlagSampled:                         { asString = "Sampled";                             break; }
        case ImageUsageFlagStorage:                         { asString = "Storage";                             break; }
        case ImageUsageFlagColorAttachment:                 { asString = "Color Attachment";                    break; }
        case ImageUsageFlagDepthStencilAttachment:          { asString = "Depth Stencil Attachment";            break; }
        case ImageUsageFlagTransientAttachment:             { asString = "Transient Attachment";                break; }
        case ImageUsageFlagInputAttachment:                 { asString = "Input Attachment";                    break; }
#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_DECODE_QUEUE_AVAILABLE
        case ImageUsageFlagVideoDecodeDestination:          { asString = "Video Decode Destination";            break; }
        case ImageUsageFlagVideoDecodeSource:               { asString = "Video Decode Source";                 break; }
        case ImageUsageFlagVideoDecodeDPB:                  { asString = "Video Decode DPB";                    break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE
        case ImageUsageFlagFragmentDensityMap:              { asString = "Fragment Density Map";                break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE
        case ImageUsageFlagFragmentShadingRateAttachment:   { asString = "Fragment Shading Rate Attachment";    break; }
#endif
#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_ENCODE_QUEUE_AVAILABLE
        case ImageUsageFlagVideoEncodeDestination:          { asString = "Video Encode Destination";            break; }
        case ImageUsageFlagVideoEncodeSource:               { asString = "Video Encode Source";                 break; }
        case ImageUsageFlagVideoEncodeDPB:                  { asString = "Video Encode DPB";                    break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_INVOCATION_MASK_AVAILABLE
        case ImageUsageFlagInvocationMaskHuawei:            { asString = "Invocation Mask Huawei";              break; }
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE && ! __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE
        case ImageUsageFlagShadingRateImageNVidia:          { asString = "Shading Rate Image NVidia";           break; }
#endif
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
auto vulkan :: toString (
        Type ( AcquireProfilingLockInfo ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( AcquireProfilingLockInfo ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", flags = "                             + :: flagsToString ( info.flags ) +
           ", timeout = "                           + info.timeout +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
auto vulkan :: toString (
        Type ( InitializePerformanceAPIInfoIntel ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( InitializePerformanceAPIInfoIntel ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", pUserData = "                         + engine :: toString ( info.pUserData ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
auto vulkan :: toString (
        Type ( PerformanceParameterTypeIntel )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case PerformanceParameterTypeIntelHardwareCounterSupported: { asString = "Hardware Counter Supported";  break; }
        case PerformanceParameterTypeIntelStreamMarkerValidBits:    { asString = "Stream Marker Valid Bits";    break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
auto vulkan :: toString (
        Type ( PerformanceValueTypeIntel )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case PerformanceValueTypeIntelUInt32:   { asString = "UInt32";  break; }
        case PerformanceValueTypeIntelUInt64:   { asString = "UInt64";  break; }
        case PerformanceValueTypeIntelFloat:    { asString = "Float";   break; }
        case PerformanceValueTypeIntelBool:     { asString = "Bool";    break; }
        case PerformanceValueTypeIntelString:   { asString = "String";  break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
auto vulkan :: toString (
        Type ( PerformanceOverrideTypeIntel )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case PerformanceOverrideTypeIntelNullHardware:       { asString = "Null Hardware";       break; }
        case PerformanceOverrideTypeIntelFlushGPUCaches:     { asString = "Flush GPU Caches";    break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
auto vulkan :: toString (
        Type ( PerformanceConfigurationTypeIntel )  flag
) noexcept -> StringLiteral {

    StringLiteral asString = "";

    switch ( flag ) {
        case PerformanceConfigurationTypeIntelCommandQueueMetricsDiscoveryActivated:       { asString = "Command Queue Metrics Discovery Activated";       break; }
    }

    return asString;
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
auto vulkan :: toString (
        Type ( PerformanceValueDataIntel ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PerformanceValueDataIntel ) );
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
auto vulkan :: toString (
        Type ( PerformanceValueIntel ) const & info
) noexcept -> String {

    String asString = __C_ENG_STRINGIFY ( Type ( PerformanceValueIntel ) ) " " +
           "{ type = "_s    + toString ( info.type ) +
           ", value = ";

    switch ( info.type ) {
        case PerformanceValueTypeIntelUInt32:   { asString += info.data.value32;                                    break; }
        case PerformanceValueTypeIntelUInt64:   { asString += info.data.value64;                                    break; }
        case PerformanceValueTypeIntelFloat:    { asString += info.data.valueFloat;                                 break; }
        case PerformanceValueTypeIntelBool:     { asString += (info.data.valueBool == VK_TRUE ? "true" : "false");  break; }
        case PerformanceValueTypeIntelString:   { asString += info.data.valueString;                                break; }
    }

    return asString + " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
auto vulkan :: toString (
        Type ( PerformanceMarkerInfoIntel ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PerformanceMarkerInfoIntel ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", marker = "                            + engine :: toString ( info.marker ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
auto vulkan :: toString (
        Type ( PerformanceStreamMarkerInfoIntel ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PerformanceStreamMarkerInfoIntel ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", marker = "                            + engine :: toString ( info.marker ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
auto vulkan :: toString (
        Type ( PerformanceOverrideInfoIntel ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PerformanceOverrideInfoIntel ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", type = "                              + toString ( info.type ) +
           ", enable = "                            + ( info.enable == VK_TRUE ? "true" : "false" ) +
           ", parameter = "                         + info.parameter +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
auto vulkan :: toString (
        Type ( PerformanceConfigurationAcquireInfoIntel ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( PerformanceConfigurationAcquireInfoIntel ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", type = "                              + toString ( info.type ) +
           " }";
}
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE
auto vulkan :: toString (
        Type ( QueueFamilyQueryResultStatusProperties2 ) const & info
) noexcept -> String {

    return __C_ENG_STRINGIFY ( Type ( QueueFamilyQueryResultStatusProperties2 ) ) " " +
           "{ structureType = "_s                   + toString ( info.structureType ) +
           ", pNext = "                             + engine :: toString ( info.pNext ) +
           ", supported = "                         + ( info.supported == VK_TRUE ? "true" : "false" ) +
           " }";
}
#endif

//
// Created by loghin on 26.12.2021.
//

#ifndef __C_ENG_VULKAN_CORE_HPP__
#define __C_ENG_VULKAN_CORE_HPP__

#include <Preprocess.hpp>
#include <CDS/Limits>

#include <details/VulkanAPIDetails.hpp>

#include <Core.hpp>


namespace cds {
    class String;
}

namespace engine { // NOLINT(modernize-concat-nested-namespaces)
    namespace vulkan {


#define C_ENG_MAP_START     ENUM ( Result, TYPE ( cds :: sint32 ) )
#include <ObjectMapping.hpp>

        Enum {

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

            Field ( Success,                                   VkResult :: VK_SUCCESS ),
            Field ( NotReady,                                  VkResult :: VK_NOT_READY ),
            Field ( Timeout,                                   VkResult :: VK_TIMEOUT ),
            Field ( EventSet,                                  VkResult :: VK_EVENT_SET ),
            Field ( EventReset,                                VkResult :: VK_EVENT_RESET ),
            Field ( Incomplete,                                VkResult :: VK_INCOMPLETE ),
            Field ( ErrorOutOfHostMemory,                      VkResult :: VK_ERROR_OUT_OF_HOST_MEMORY ),
            Field ( ErrorOutOfDeviceMemory,                    VkResult :: VK_ERROR_OUT_OF_DEVICE_MEMORY ),
            Field ( ErrorInitializationFailed,                 VkResult :: VK_ERROR_INITIALIZATION_FAILED ),
            Field ( ErrorDeviceLost,                           VkResult :: VK_ERROR_DEVICE_LOST ),
            Field ( ErrorMemoryMapFailed,                      VkResult :: VK_ERROR_MEMORY_MAP_FAILED ),
            Field ( ErrorLayerNotPresent,                      VkResult :: VK_ERROR_LAYER_NOT_PRESENT ),
            Field ( ErrorExtensionNotPresent,                  VkResult :: VK_ERROR_LAYER_NOT_PRESENT ),
            Field ( ErrorFeatureNotPresent,                    VkResult :: VK_ERROR_FEATURE_NOT_PRESENT ),
            Field ( ErrorIncompatibleDriver,                   VkResult :: VK_ERROR_INCOMPATIBLE_DRIVER ),
            Field ( ErrorTooManyObjects,                       VkResult :: VK_ERROR_TOO_MANY_OBJECTS ),
            Field ( ErrorFormatNotSupported,                   VkResult :: VK_ERROR_FORMAT_NOT_SUPPORTED ),
            Field ( ErrorFragmentedPool,                       VkResult :: VK_ERROR_FRAGMENTED_POOL ),
            Field ( ErrorUnknown,                              VkResult :: VK_ERROR_UNKNOWN ),

#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

            Field ( ErrorOutOfPoolMemory,                      VkResult :: VK_ERROR_OUT_OF_POOL_MEMORY ),
            Field ( ErrorInvalidExternalHandle,                VkResult :: VK_ERROR_INVALID_EXTERNAL_HANDLE ),

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

            Field ( ErrorFragmentation,                        VkResult :: VK_ERROR_FRAGMENTATION ),
            Field ( ErrorInvalidOpaqueCaptureAddress,          VkResult :: VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS ),

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            Field ( PipelineCompileRequired,                   VkResult :: VK_PIPELINE_COMPILE_REQUIRED ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE

            Field ( ErrorSurfaceLost,                          VkResult :: VK_ERROR_SURFACE_LOST_KHR ),
            Field ( ErrorNativeWindowInUse,                    VkResult :: VK_ERROR_NATIVE_WINDOW_IN_USE_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DISPLAY_SWAP_CHAIN_AVAILABLE

            Field ( ErrorIncompatibleDisplay,                  VkResult :: VK_ERROR_INCOMPATIBLE_DISPLAY_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DEFERRED_HOST_OPERATIONS_AVAILABLE

            Field ( ThreadIdle,                                VkResult :: VK_THREAD_IDLE_KHR ),
            Field ( ThreadDone,                                VkResult :: VK_THREAD_DONE_KHR ),
            Field ( OperationDeferred,                         VkResult :: VK_OPERATION_DEFERRED_KHR ),
            Field ( OperationNotDeferred,                      VkResult :: VK_OPERATION_NOT_DEFERRED_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_GLSL_SHADER_AVAILABLE

            Field ( ErrorInvalidShader,                        VkResult :: VK_ERROR_INVALID_SHADER_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_REPORT_AVAILABLE

            Field ( ErrorValidationFailed,                     VkResult :: VK_ERROR_VALIDATION_FAILED_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_DRM_FORMAT_MODIFIER_AVAILABLE

            Field ( ErrorInvalidDRMFormatModifierPlaneLayout,  VkResult :: VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_AVAILABLE

            Field ( ErrorNotPermitted,                         VkResult :: VK_ERROR_NOT_PERMITTED_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FULL_SCREEN_EXCLUSIVE_AVAILABLE

            Field ( ErrorFullScreenExclusiveModeLost,          VkResult :: VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE && ! __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            Field ( PipelineCompileRequired,                   VkResult :: VK_PIPELINE_COMPILE_REQUIRED_EXT ),

#endif

            Field ( ErrorInvalidUsage,                         cds :: limits :: S32_MAX - 6 ),
            Field ( ErrorFunctionNotSupportedICD,              cds :: limits :: S32_MAX - 5 ),
            Field ( ErrorIncompatibleVersion,                  cds :: limits :: S32_MAX - 4 ),
            Field ( ErrorConfigurationArraySizeSmall,          cds :: limits :: S32_MAX - 3 ),
            Field ( ErrorFunctionHandleNotFound,               cds :: limits :: S32_MAX - 2 ),
            Field ( ErrorIllegalArgument,                      cds :: limits :: S32_MAX - 1 ),
            Field ( Unknown,                                   cds :: limits :: S32_MAX )

        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     ENUM ( StructureType, TYPE ( cds :: sint32 ) )
#include <ObjectMapping.hpp>

#ifdef MemoryBarrier
#define __C_ENG_REPLACED_MemoryBarrier
#pragma push_macro("MemoryBarrier")
#undef MemoryBarrier
#endif

        Enum {

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

            Field ( ApplicationInfo,                                                       VkStructureType :: VK_STRUCTURE_TYPE_APPLICATION_INFO ),
            Field ( InstanceCreateInfo,                                                    VkStructureType :: VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO ),
            Field ( DeviceQueueCreateInfo,                                                 VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO ),
            Field ( DeviceCreateInfo,                                                      VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO ),

            Field ( SubmitInfo,                                                            VkStructureType :: VK_STRUCTURE_TYPE_SUBMIT_INFO ),
            Field ( MemoryAllocateInfo,                                                    VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO ),
            Field ( MappedMemoryRange,                                                     VkStructureType :: VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE ),
            Field ( BindSparseInfo,                                                        VkStructureType :: VK_STRUCTURE_TYPE_BIND_SPARSE_INFO ),

            Field ( FenceCreateInfo,                                                       VkStructureType :: VK_STRUCTURE_TYPE_FENCE_CREATE_INFO ),
            Field ( SemaphoreCreateInfo,                                                   VkStructureType :: VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO ),
            Field ( EventCreateInfo,                                                       VkStructureType :: VK_STRUCTURE_TYPE_EVENT_CREATE_INFO ),

            Field ( QueryPoolCreateInfo,                                                   VkStructureType :: VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO ),
            Field ( BufferCreateInfo,                                                      VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO ),
            Field ( BufferViewCreateInfo,                                                  VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO ),
            Field ( ImageCreateInfo,                                                       VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO ),
            Field ( ImageViewCreateInfo,                                                   VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO ),

            Field ( ShaderModuleCreateInfo,                                                VkStructureType :: VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO ),

            Field ( PipelineCacheCreateInfo,                                               VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO ),
            Field ( PipelineShaderStageCreateInfo,                                         VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO ),
            Field ( PipelineVertexInputStateCreateInfo,                                    VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO ),
            Field ( PipelineInputAssemblyStateCreateInfo,                                  VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO ),
            Field ( PipelineTesselationStateCreateInfo,                                    VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO ),
            Field ( PipelineViewportStateCreateInfo,                                       VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO ),
            Field ( PipelineRasterizationStateCreateInfo,                                  VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO ),
            Field ( PipelineMultisampleStateCreateInfo,                                    VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO ),
            Field ( PipelineDepthStencilStateCreateInfo,                                   VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO ),
            Field ( PipelineColorBlendStateCreateInfo,                                     VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO ),
            Field ( PipelineDynamicStateCreateInfo,                                        VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO ),

            Field ( GraphicsPipelineCreateInfo,                                            VkStructureType :: VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO ),
            Field ( ComputePipelineCreateInfo,                                             VkStructureType :: VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO ),
            Field ( PipelineLayoutCreateInfo,                                              VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO ),

            Field ( SamplerCreateInfo,                                                     VkStructureType :: VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO ),

            Field ( DescriptorSetLayoutCreateInfo,                                         VkStructureType :: VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO ),
            Field ( DescriptorPoolCreateInfo,                                              VkStructureType :: VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO ),
            Field ( DescriptorSetAllocateInfo,                                             VkStructureType :: VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO ),
            Field ( WriteDescriptorSet,                                                    VkStructureType :: VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET ),
            Field ( CopyDescriptorSet,                                                     VkStructureType :: VK_STRUCTURE_TYPE_COPY_DESCRIPTOR_SET ),

            Field ( FrameBufferCreateInfo,                                                 VkStructureType :: VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO ),
            Field ( RenderPassCreateInfo,                                                  VkStructureType :: VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO ),

            Field ( CommandPoolCreateInfo,                                                 VkStructureType :: VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO ),
            Field ( CommandBufferAllocateInfo,                                             VkStructureType :: VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO ),
            Field ( CommandBufferInheritanceInfo,                                          VkStructureType :: VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO ),
            Field ( CommandBufferBeginInfo,                                                VkStructureType :: VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO ),

            Field ( RenderPassBeginInfo,                                                   VkStructureType :: VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO ),

            Field ( BufferMemoryBarrier,                                                   VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER ),
            Field ( ImageMemoryBarrier,                                                    VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER ),
            Field ( MemoryBarrier,                                                         VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_BARRIER ),

            Field ( LoaderInstanceCreateInfo,                                              VkStructureType :: VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO ),
            Field ( LoaderDeviceCreateInfo,                                                VkStructureType :: VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO ),

#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

            Field ( PhysicalDeviceSubgroupProperties,                                      VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_PROPERTIES ),

            Field ( BindBufferMemoryInfo,                                                  VkStructureType :: VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO ),
            Field ( BindImageMemoryInfo,                                                   VkStructureType :: VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_INFO ),

            Field ( PhysicalDevice16BitStorageFeatures,                                    VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_16BIT_STORAGE_FEATURES ),

            Field ( MemoryDedicatedRequirements,                                           VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_DEDICATED_REQUIREMENTS ),
            Field ( MemoryDedicatedAllocateInfo,                                           VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_DEDICATED_ALLOCATE_INFO ),
            Field ( MemoryAllocateFlagsInfo,                                               VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO ),

            Field ( DeviceGroupRenderPassBeginInfo,                                        VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_GROUP_RENDER_PASS_BEGIN_INFO ),
            Field ( DeviceGroupCommandBufferBeginInfo,                                     VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_GROUP_COMMAND_BUFFER_BEGIN_INFO ),
            Field ( DeviceGroupSubmitInfo,                                                 VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_GROUP_SUBMIT_INFO ),
            Field ( DeviceGroupBindSparseInfo,                                             VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_GROUP_BIND_SPARSE_INFO ),

            Field ( BindBufferMemoryDeviceGroupInfo,                                       VkStructureType :: VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_DEVICE_GROUP_INFO ),
            Field ( BindImageMemoryDeviceGroupInfo,                                        VkStructureType :: VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_DEVICE_GROUP_INFO ),

            Field ( PhysicalDeviceGroupProperties,                                         VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GROUP_PROPERTIES ),
            Field ( DeviceGroupDeviceCreateInfo,                                           VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_GROUP_DEVICE_CREATE_INFO ),

            Field ( BufferMemoryRequirementsInfo,                                          VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_MEMORY_REQUIREMENTS_INFO_2 ),
            Field ( ImageMemoryRequirementsInfo,                                           VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_MEMORY_REQUIREMENTS_INFO_2 ),
            Field ( ImageSparseMemoryRequirementsInfo,                                     VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_SPARSE_MEMORY_REQUIREMENTS_INFO_2 ),
            Field ( MemoryRequirements,                                                    VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2 ),
            Field ( SparseImageMemoryRequirements,                                         VkStructureType :: VK_STRUCTURE_TYPE_SPARSE_IMAGE_MEMORY_REQUIREMENTS_2 ),

            Field ( PhysicalDeviceFeatures,                                                VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2 ),
            Field ( PhysicalDeviceProperties,                                              VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2 ),

            Field ( FormatProperties,                                                      VkStructureType :: VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_2 ),
            Field ( ImageFormatProperties,                                                 VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2 ),
            Field ( PhysicalDeviceImageFormatInfo,                                         VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_FORMAT_INFO_2 ),

            Field ( QueueFamilyProperties,                                                 VkStructureType :: VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2 ),
            Field ( PhysicalDeviceMemoryProperties,                                        VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PROPERTIES_2 ),
            Field ( SparseImageFormatProperties,                                           VkStructureType :: VK_STRUCTURE_TYPE_SPARSE_IMAGE_FORMAT_PROPERTIES_2 ),
            Field ( PhysicalDeviceSparseImageFormatInfo,                                   VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SPARSE_IMAGE_FORMAT_INFO_2 ),
            Field ( PhysicalDevicePointClippingProperties,                                 VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_POINT_CLIPPING_PROPERTIES ),

            Field ( RenderPassInputAttachmentAspectCreateInfo,                             VkStructureType :: VK_STRUCTURE_TYPE_RENDER_PASS_INPUT_ATTACHMENT_ASPECT_CREATE_INFO ),

            Field ( ImageViewUsageCreateInfo,                                              VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO ),

            Field ( PipelineTessellationDomainOriginStateCreateInfo,                       VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_DOMAIN_ORIGIN_STATE_CREATE_INFO ),

            Field ( RenderPassMultiviewCreateInfo,                                         VkStructureType :: VK_STRUCTURE_TYPE_RENDER_PASS_MULTIVIEW_CREATE_INFO ),
            Field ( PhysicalDeviceMultiviewFeatures,                                       VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_FEATURES ),
            Field ( PhysicalDeviceMultiviewProperties,                                     VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_PROPERTIES ),

            Field ( PhysicalDeviceVariablePointersFeatures,                                VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VARIABLE_POINTERS_FEATURES ),

            Field ( ProtectedSubmitInfo,                                                   VkStructureType :: VK_STRUCTURE_TYPE_PROTECTED_SUBMIT_INFO ),
            Field ( PhysicalDeviceProtectedMemoryFeatures,                                 VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROTECTED_MEMORY_FEATURES ),
            Field ( PhysicalDeviceProtectedMemoryProperties,                               VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROTECTED_MEMORY_PROPERTIES ),

            Field ( DeviceQueueInfo,                                                       VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_QUEUE_INFO_2 ),

            Field ( SamplerYCBCRConversionCreateInfo,                                      VkStructureType :: VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_CREATE_INFO ),
            Field ( SamplerYCBCRConversionInfo,                                            VkStructureType :: VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_INFO ),

            Field ( BindImagePlaneMemoryInfo,                                              VkStructureType :: VK_STRUCTURE_TYPE_BIND_IMAGE_PLANE_MEMORY_INFO ),
            Field ( ImagePlaneMemoryRequirementsInfo,                                      VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_PLANE_MEMORY_REQUIREMENTS_INFO ),

            Field ( PhysicalDeviceSamplerYCBCRConversionFeatures,                          VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLER_YCBCR_CONVERSION_FEATURES ),
            Field ( SamplerYCBCRConversionImageFormatProperties,                           VkStructureType :: VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_IMAGE_FORMAT_PROPERTIES ),

            Field ( DescriptorUpdateTemplateCreateInfo,                                    VkStructureType :: VK_STRUCTURE_TYPE_DESCRIPTOR_UPDATE_TEMPLATE_CREATE_INFO ),

            Field ( PhysicalDeviceExternalImageFormatInfo,                                 VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_IMAGE_FORMAT_INFO ),
            Field ( ExternalImageFormatProperties,                                         VkStructureType :: VK_STRUCTURE_TYPE_EXTERNAL_IMAGE_FORMAT_PROPERTIES ),
            Field ( PhysicalDeviceExternalBufferInfo,                                      VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_BUFFER_INFO ),
            Field ( ExternalBufferProperties,                                              VkStructureType :: VK_STRUCTURE_TYPE_EXTERNAL_BUFFER_PROPERTIES ),

            Field ( PhysicalDeviceIDProperties,                                            VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ID_PROPERTIES ),

            Field ( ExternalMemoryBufferCreateInfo,                                        VkStructureType :: VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_BUFFER_CREATE_INFO ),
            Field ( ExternalMemoryImageCreateInfo,                                         VkStructureType :: VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO ),
            Field ( ExportMemoryAllocateInfo,                                              VkStructureType :: VK_STRUCTURE_TYPE_EXPORT_MEMORY_ALLOCATE_INFO ),

            Field ( PhysicalDeviceExternalFenceInfo,                                       VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_FENCE_INFO ),
            Field ( ExternalFenceProperties,                                               VkStructureType :: VK_STRUCTURE_TYPE_EXTERNAL_FENCE_PROPERTIES ),
            Field ( ExportFenceCreateInfo,                                                 VkStructureType :: VK_STRUCTURE_TYPE_EXPORT_FENCE_CREATE_INFO ),

            Field ( ExportSemaphoreCreateInfo,                                             VkStructureType :: VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_CREATE_INFO ),
            Field ( PhysicalDeviceExternalSemaphoreInfo,                                   VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_SEMAPHORE_INFO ),
            Field ( ExternalSemaphoreProperties,                                           VkStructureType :: VK_STRUCTURE_TYPE_EXTERNAL_SEMAPHORE_PROPERTIES ),

            Field ( PhysicalDeviceMaintenanceProperties,                                   VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_3_PROPERTIES ),

            Field ( DescriptorSetLayoutSupport,                                            VkStructureType :: VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_SUPPORT ),
            Field ( PhysicalDeviceShaderDrawParametersFeatures,                            VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_DRAW_PARAMETERS_FEATURES ),

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

            Field ( PhysicalDeviceVulkan_1_1_Features,                                     VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES ),
            Field ( PhysicalDeviceVulkan_1_1_Properties,                                   VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_PROPERTIES ),
            Field ( PhysicalDeviceVulkan_1_2_Features,                                     VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES ),
            Field ( PhysicalDeviceVulkan_1_2_Properties,                                   VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_PROPERTIES ),

            Field ( ImageFormatListCreateInfo,                                             VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_FORMAT_LIST_CREATE_INFO ),

            Field ( AttachmentDescription,                                                 VkStructureType :: VK_STRUCTURE_TYPE_ATTACHMENT_DESCRIPTION_2 ),
            Field ( AttachmentReference,                                                   VkStructureType :: VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_2 ),
            Field ( SubpassDescription,                                                    VkStructureType :: VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_2 ),
            Field ( SubpassDependency,                                                     VkStructureType :: VK_STRUCTURE_TYPE_SUBPASS_DEPENDENCY_2 ),

            Field ( RenderPassCreateInfo2,                                                 VkStructureType :: VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO_2 ),

            Field ( SubpassBeginInfo,                                                      VkStructureType :: VK_STRUCTURE_TYPE_SUBPASS_BEGIN_INFO ),
            Field ( SubpassEndInfo,                                                        VkStructureType :: VK_STRUCTURE_TYPE_SUBPASS_END_INFO ),

            Field ( PhysicalDevice8BitStorageFeatures,                                     VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_8BIT_STORAGE_FEATURES ),

            Field ( PhysicalDeviceDriverProperties,                                        VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRIVER_PROPERTIES ),

            Field ( PhysicalDeviceShaderAtomicInt64Features,                               VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_INT64_FEATURES ),
            Field ( PhysicalDeviceShaderFloat16Int8Features,                               VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_FLOAT16_INT8_FEATURES ),
            Field ( PhysicalDeviceFloatControlsProperties,                                 VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FLOAT_CONTROLS_PROPERTIES ),

            Field ( DescriptorSetLayoutBindingFlagsCreateInfo,                             VkStructureType :: VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO ),

            Field ( PhysicalDeviceDescriptorIndexingFeatures,                              VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_FEATURES ),
            Field ( PhysicalDeviceDescriptorIndexingProperties,                            VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_PROPERTIES ),

            Field ( DescriptorSetVariableDescriptorCountAllocateInfo,                      VkStructureType :: VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_ALLOCATE_INFO ),
            Field ( DescriptorSetVariableDescriptorCountLayoutSupport,                     VkStructureType :: VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_LAYOUT_SUPPORT ),

            Field ( PhysicalDeviceDepthStencilResolveProperties,                           VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_STENCIL_RESOLVE_PROPERTIES ),
            Field ( SubpassDescriptionDepthStencilResolve,                                 VkStructureType :: VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_DEPTH_STENCIL_RESOLVE ),

            Field ( PhysicalDeviceScalarBlockLayoutFeatures,                               VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SCALAR_BLOCK_LAYOUT_FEATURES ),

            Field ( ImageStencilUsageCreateInfo,                                           VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_STENCIL_USAGE_CREATE_INFO ),

            Field ( PhysicalDeviceSamplerFilterMinMaxProperties,                           VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLER_FILTER_MINMAX_PROPERTIES ),

            Field ( SamplerReductionModeCreateInfo,                                        VkStructureType :: VK_STRUCTURE_TYPE_SAMPLER_REDUCTION_MODE_CREATE_INFO ),

            Field ( PhysicalDeviceVulkanMemoryModelFeatures,                               VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_MEMORY_MODEL_FEATURES ),
            Field ( PhysicalDeviceImagelessFrameBufferFeatures,                            VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGELESS_FRAMEBUFFER_FEATURES ),

            Field ( FrameBufferAttachmentsCreateInfo,                                      VkStructureType :: VK_STRUCTURE_TYPE_FRAMEBUFFER_ATTACHMENTS_CREATE_INFO ),
            Field ( FrameBufferAttachmentImageInfo,                                        VkStructureType :: VK_STRUCTURE_TYPE_FRAMEBUFFER_ATTACHMENT_IMAGE_INFO ),
            Field ( RenderPassAttachmentBeginInfo,                                         VkStructureType :: VK_STRUCTURE_TYPE_RENDER_PASS_ATTACHMENT_BEGIN_INFO ),

            Field ( PhysicalDeviceUniformBufferStandardLayoutFeatures,                     VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_UNIFORM_BUFFER_STANDARD_LAYOUT_FEATURES ),
            Field ( PhysicalDeviceShaderSubgroupExtendedTypesFeatures,                     VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SUBGROUP_EXTENDED_TYPES_FEATURES ),
            Field ( PhysicalDeviceSeparateDepthStencilLayoutsFeatures,                     VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SEPARATE_DEPTH_STENCIL_LAYOUTS_FEATURES ),

            Field ( AttachmentReferenceStencilLayout,                                      VkStructureType :: VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_STENCIL_LAYOUT ),
            Field ( AttachmentDescriptionStencilLayout,                                    VkStructureType :: VK_STRUCTURE_TYPE_ATTACHMENT_DESCRIPTION_STENCIL_LAYOUT ),

            Field ( PhysicalDeviceHostQueryResetFeatures,                                  VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_HOST_QUERY_RESET_FEATURES ),

            Field ( PhysicalDeviceTimelineSemaphoreFeatures,                               VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TIMELINE_SEMAPHORE_FEATURES ),
            Field ( PhysicalDeviceTimelineSemaphoreProperties,                             VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TIMELINE_SEMAPHORE_PROPERTIES ),

            Field ( SemaphoreTypeCreateInfo,                                               VkStructureType :: VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO ),
            Field ( TimelineSemaphoreSubmitInfo,                                           VkStructureType :: VK_STRUCTURE_TYPE_TIMELINE_SEMAPHORE_SUBMIT_INFO ),
            Field ( SemaphoreWaitInfo,                                                     VkStructureType :: VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO ),
            Field ( SemaphoreSignalInfo,                                                   VkStructureType :: VK_STRUCTURE_TYPE_SEMAPHORE_SIGNAL_INFO ),

            Field ( PhysicalDeviceBufferDeviceAddressFeatures,                             VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BUFFER_DEVICE_ADDRESS_FEATURES ),
            Field ( BufferDeviceAddressInfo,                                               VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO ),
            Field ( BufferOpaqueCaptureAddressCreateInfo,                                  VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_OPAQUE_CAPTURE_ADDRESS_CREATE_INFO ),
            Field ( MemoryOpaqueCaptureAddressAllocateInfo,                                VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_OPAQUE_CAPTURE_ADDRESS_ALLOCATE_INFO ),
            Field ( DeviceMemoryOpaqueCaptureAddressInfo,                                  VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_MEMORY_OPAQUE_CAPTURE_ADDRESS_INFO ),

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            Field ( PhysicalDeviceVulkan_1_3_Features,                                     VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES ),
            Field ( PhysicalDeviceVulkan_1_3_Properties,                                   VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_PROPERTIES ),

            Field ( PipelineCreationFeedbackCreateInfo,                                    VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_CREATION_FEEDBACK_CREATE_INFO ),
            Field ( PhysicalDeviceShaderTerminateInvocationFeatures,                       VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_TERMINATE_INVOCATION_FEATURES ),
            Field ( PhysicalDeviceToolProperties,                                          VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TOOL_PROPERTIES ),
            Field ( PhysicalDeviceShaderDemoteToHelperInvocationFeatures,                  VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_DEMOTE_TO_HELPER_INVOCATION_FEATURES ),

            Field ( PhysicalDevicePrivateDataFeatures,                                     VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRIVATE_DATA_FEATURES ),
            Field ( DevicePrivateDataCreateInfo,                                           VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_PRIVATE_DATA_CREATE_INFO ),
            Field ( PrivateDataSlotCreateInfo,                                             VkStructureType :: VK_STRUCTURE_TYPE_PRIVATE_DATA_SLOT_CREATE_INFO ),

            Field ( PhysicalDevicePipelineCreationCacheControlFeatures,                    VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_CREATION_CACHE_CONTROL_FEATURES ),

            Field ( MemoryBarrier2,                                                        VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_BARRIER_2 ),
            Field ( BufferMemoryBarrier2,                                                  VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER_2 ),
            Field ( ImageMemoryBarrier2,                                                   VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2 ),
            Field ( DependencyInfo,                                                        VkStructureType :: VK_STRUCTURE_TYPE_DEPENDENCY_INFO ),
            Field ( SubmitInfo2,                                                           VkStructureType :: VK_STRUCTURE_TYPE_SUBMIT_INFO_2 ),
            Field ( SemaphoreSubmitInfo,                                                   VkStructureType :: VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO ),
            Field ( CommandBufferSubmitInfo,                                               VkStructureType :: VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO ),
            Field ( PhysicalDeviceSynchronizationFeatures,                                 VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SYNCHRONIZATION_2_FEATURES ),

            Field ( PhysicalDeviceZeroInitializeWorkgroupMemoryFeatures,                   VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ZERO_INITIALIZE_WORKGROUP_MEMORY_FEATURES ),

            Field ( PhysicalDeviceImageRobustnessFeatures,                                 VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_ROBUSTNESS_FEATURES ),

            Field ( CopyBufferInfo,                                                        VkStructureType :: VK_STRUCTURE_TYPE_COPY_BUFFER_INFO_2 ),
            Field ( CopyImageInfo,                                                         VkStructureType :: VK_STRUCTURE_TYPE_COPY_IMAGE_INFO_2 ),
            Field ( CopyBufferToImageInfo,                                                 VkStructureType :: VK_STRUCTURE_TYPE_COPY_BUFFER_TO_IMAGE_INFO_2 ),
            Field ( CopyImageToBufferInfo,                                                 VkStructureType :: VK_STRUCTURE_TYPE_COPY_IMAGE_TO_BUFFER_INFO_2 ),
            Field ( BlitImageInfo,                                                         VkStructureType :: VK_STRUCTURE_TYPE_BLIT_IMAGE_INFO_2 ),
            Field ( ResolveImageInfo,                                                      VkStructureType :: VK_STRUCTURE_TYPE_RESOLVE_IMAGE_INFO_2 ),
            Field ( BufferCopy,                                                            VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_COPY_2 ),
            Field ( ImageCopy,                                                             VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_COPY_2 ),
            Field ( ImageBlit,                                                             VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_BLIT_2 ),
            Field ( BufferImageCopy,                                                       VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_IMAGE_COPY_2 ),
            Field ( ImageResolve,                                                          VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_RESOLVE_2 ),

            Field ( PhysicalDeviceSubgroupSizeControlFeatures,                             VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_SIZE_CONTROL_FEATURES ),
            Field ( PhysicalDeviceSubgroupSizeControlProperties,                           VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_SIZE_CONTROL_PROPERTIES ),
            Field ( PipelineShaderStageRequiredSubgroupSizeCreateInfo,                     VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_REQUIRED_SUBGROUP_SIZE_CREATE_INFO ),

            Field ( PhysicalDeviceInlineUniformBlockFeatures,                              VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INLINE_UNIFORM_BLOCK_FEATURES ),
            Field ( PhysicalDeviceInlineUniformBlockProperties,                            VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INLINE_UNIFORM_BLOCK_PROPERTIES ),
            Field ( WriteDescriptorSetInlineUniformBlock,                                  VkStructureType :: VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_INLINE_UNIFORM_BLOCK ),
            Field ( DescriptorPoolInlineUniformBlockCreateInfo,                            VkStructureType :: VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_INLINE_UNIFORM_BLOCK_CREATE_INFO ),

            Field ( PhysicalDeviceTextureCompressionASTCHDRFeatures,                       VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TEXTURE_COMPRESSION_ASTC_HDR_FEATURES ),

            Field ( RenderingInfo,                                                         VkStructureType :: VK_STRUCTURE_TYPE_RENDERING_INFO ),
            Field ( RenderingAttachmentInfo,                                               VkStructureType :: VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO ),
            Field ( PipelineRenderingCreateInfo,                                           VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO ),
            Field ( PhysicalDeviceDynamicRenderingFeatures,                                VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DYNAMIC_RENDERING_FEATURES ),
            Field ( CommandBufferInheritanceRenderingInfo,                                 VkStructureType :: VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_RENDERING_INFO ),

            Field ( PhysicalDeviceShaderIntegerDotProductFeatures,                         VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_INTEGER_DOT_PRODUCT_FEATURES ),
            Field ( PhysicalDeviceShaderIntegerDotProductProperties,                       VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_INTEGER_DOT_PRODUCT_PROPERTIES ),

            Field ( PhysicalDeviceTexelBufferAlignmentFeatures,                            VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TEXEL_BUFFER_ALIGNMENT_FEATURES_EXT ),
            Field ( PhysicalDeviceTexelBufferAlignmentProperties,                          VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TEXEL_BUFFER_ALIGNMENT_PROPERTIES ),

            Field ( FormatProperties3,                                                     VkStructureType :: VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_3 ),

            Field ( PhysicalDeviceMaintenance4Features,                                    VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_4_FEATURES ),
            Field ( PhysicalDeviceMaintenance4Properties,                                  VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_4_PROPERTIES ),
            Field ( PhysicalDeviceBufferMemoryRequirements,                                VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_BUFFER_MEMORY_REQUIREMENTS ),
            Field ( PhysicalDeviceImageMemoryRequirements,                                 VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_IMAGE_MEMORY_REQUIREMENTS ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE

            Field ( SwapChainCreateInfo,                                                   VkStructureType :: VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR ),
            Field ( PresentInfo,                                                           VkStructureType :: VK_STRUCTURE_TYPE_PRESENT_INFO_KHR ),

#endif

#if ( __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE ) || ( __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DEVICE_GROUP_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE )

            Field ( DeviceGroupPresentCapabilities,                                        VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_GROUP_PRESENT_CAPABILITIES_KHR ),

            Field ( ImageSwapChainCreateInfo,                                              VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_SWAPCHAIN_CREATE_INFO_KHR ),

            Field ( BindImageMemorySwapChainInfo,                                          VkStructureType :: VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_SWAPCHAIN_INFO_KHR ),
            Field ( AcquireNextImageInfo,                                                  VkStructureType :: VK_STRUCTURE_TYPE_ACQUIRE_NEXT_IMAGE_INFO_KHR ),

            Field ( DeviceGroupPresentInfo,                                                VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_GROUP_PRESENT_INFO_KHR ),
            Field ( DeviceGroupSwapChainCreateInfo,                                        VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_GROUP_SWAPCHAIN_CREATE_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DISPLAY_AVAILABLE

            Field ( DisplayModeCreateInfo,                                                 VkStructureType :: VK_STRUCTURE_TYPE_DISPLAY_MODE_CREATE_INFO_KHR ),
            Field ( DisplaySurfaceCreateInfo,                                              VkStructureType :: VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DISPLAY_SWAP_CHAIN_AVAILABLE

            Field ( DisplayPresentInfo,                                                    VkStructureType :: VK_STRUCTURE_TYPE_DISPLAY_PRESENT_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_XLIB_SURFACE_AVAILABLE

            Field ( XLibSurfaceCreateInfo,                                                 VkStructureType :: VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_XCB_SURFACE_AVAILABLE

            Field ( XcbSurfaceCreateInfo,                                                  VkStructureType :: VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WAYLAND_SURFACE_AVAILABLE

            Field ( WaylandSurfaceCreateInfo,                                              VkStructureType :: VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ANDROID_SURFACE_AVAILABLE

            Field ( AndroidSurfaceCreateInfo,                                              VkStructureType :: VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WIN32_SURFACE_AVAILABLE

            Field ( Win32SurfaceCreateInfo,                                                VkStructureType :: VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_REPORT_AVAILABLE

            Field ( DebugReportCallbackCreateInfo,                                         VkStructureType :: VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_RASTERIZATION_ORDER_AVAILABLE

            Field ( PipelineRasterizationStateRasterizationOrderAMD,                       VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_RASTERIZATION_ORDER_AMD ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_MARKER_AVAILABLE

            Field ( DebugMarkerObjectNameInfo,                                             VkStructureType :: VK_STRUCTURE_TYPE_DEBUG_MARKER_OBJECT_NAME_INFO_EXT ),
            Field ( DebugMarkerObjectTagInfo,                                              VkStructureType :: VK_STRUCTURE_TYPE_DEBUG_MARKER_OBJECT_TAG_INFO_EXT ),
            Field ( DebugMarkerMarkerInfo,                                                 VkStructureType :: VK_STRUCTURE_TYPE_DEBUG_MARKER_MARKER_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE

            Field ( VideoProfile,                                                          VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_PROFILE_KHR ),
            Field ( VideoCapabilities,                                                     VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_CAPABILITIES_KHR ),
            Field ( VideoPictureResource,                                                  VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_PICTURE_RESOURCE_KHR ),
            Field ( VideoGetMemoryProperties,                                              VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_GET_MEMORY_PROPERTIES_KHR ),
            Field ( VideoBindMemory,                                                       VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_BIND_MEMORY_KHR ),
            Field ( VideoSessionCreateInfo,                                                VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_SESSION_CREATE_INFO_KHR ),
            Field ( VideoSessionParametersCreateInfo,                                      VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_SESSION_PARAMETERS_CREATE_INFO_KHR ),
            Field ( VideoSessionParametersUpdateInfo,                                      VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_SESSION_PARAMETERS_UPDATE_INFO_KHR ),
            Field ( VideoBeginCodingInfo,                                                  VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_BEGIN_CODING_INFO_KHR ),
            Field ( VideoEndCodingInfo,                                                    VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_END_CODING_INFO_KHR ),
            Field ( VideoCodingControlInfo,                                                VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_CODING_CONTROL_INFO_KHR ),
            Field ( VideoReferenceSlot,                                                    VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_REFERENCE_SLOT_KHR ),
            Field ( VideoQueueFamilyProperties,                                            VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_QUEUE_FAMILY_PROPERTIES_2_KHR ),
            Field ( VideoProfiles,                                                         VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_PROFILES_KHR ),

            Field ( PhysicalDeviceVideoFormatInfo,                                         VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_FORMAT_INFO_KHR ),

            Field ( VideoFormatProperties,                                                 VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_FORMAT_PROPERTIES_KHR ),

            Field ( QueueFamilyQueryResultStatusProperties,                                VkStructureType :: VK_STRUCTURE_TYPE_QUEUE_FAMILY_QUERY_RESULT_STATUS_PROPERTIES_2_KHR ),

            Field ( VideoDecodeInfo,                                                       VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_DECODE_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_AVAILABLE

            Field ( DedicatedAllocationImageCreateInfoNVidia,                              VkStructureType :: VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_IMAGE_CREATE_INFO_NV ),
            Field ( DedicatedAllocationBufferCreateInfoNVidia,                             VkStructureType :: VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_BUFFER_CREATE_INFO_NV ),
            Field ( DedicatedAllocationMemoryAllocateInfoNVidia,                           VkStructureType :: VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_MEMORY_ALLOCATE_INFO_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE

            Field ( PhysicalDeviceTransformFeedbackFeatures,                               VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TRANSFORM_FEEDBACK_FEATURES_EXT ),
            Field ( PhysicalDeviceTransformFeedbackProperties,                             VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TRANSFORM_FEEDBACK_PROPERTIES_EXT ),

            Field ( PipelineRasterizationStateStreamCreateInfo,                            VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_STREAM_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_BINARY_IMPORT_AVAILABLE

            Field ( CudaModuleCreateInfoNVidiaExperimental,                                VkStructureType :: VK_STRUCTURE_TYPE_CU_MODULE_CREATE_INFO_NVX ),
            Field ( CudaFunctionCreateInfoNVidiaExperimental,                              VkStructureType :: VK_STRUCTURE_TYPE_CU_FUNCTION_CREATE_INFO_NVX ),
            Field ( CudaLaunchInfoNVidiaExperimental,                                      VkStructureType :: VK_STRUCTURE_TYPE_CU_LAUNCH_INFO_NVX ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_IMAGE_VIEW_HANDLE_AVAILABLE

            Field ( ImageViewHandleInfoNVidiaExperimental,                                 VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_VIEW_HANDLE_INFO_NVX ),
            Field ( ImageViewAddressPropertiesNVidiaExperimental,                          VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_VIEW_ADDRESS_PROPERTIES_NVX ),

#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_VIDEO_ENCODE_H264_AVAILABLE

            Field ( VideoEncodeH264Capabilities,                                           VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_CAPABILITIES_EXT ),
//            Field ( VideoEncodeH264SessionCreateInfo,                                      VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_ ),
            Field ( VideoEncodeH264SessionParametersCreateInfo,                            VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_SESSION_PARAMETERS_CREATE_INFO_EXT ),
            Field ( VideoEncodeH264SessionParametersAddInfo,                               VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_SESSION_PARAMETERS_ADD_INFO_EXT ),
            Field ( VideoEncodeH264VCLFrameInfo,                                           VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_VCL_FRAME_INFO_EXT ),
            Field ( VideoEncodeH264DPBSlotInfo,                                            VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_DPB_SLOT_INFO_EXT ),
            Field ( VideoEncodeH264NALUSlice,                                              VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_NALU_SLICE_EXT ),
            Field ( VideoEncodeH264EmitPictureParameters,                                  VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_EMIT_PICTURE_PARAMETERS_EXT ),
            Field ( VideoEncodeH264Profile,                                                VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_PROFILE_EXT ),
            Field ( VideoEncodeH264RateControlInfo,                                        VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_RATE_CONTROL_INFO_EXT ),
            Field ( VideoEncodeH264RateControlLayerInfo,                                   VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_RATE_CONTROL_LAYER_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_VIDEO_ENCODE_H265_AVAILABLE

            Field ( VideoEncodeH265Capabilities,                                           VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_CAPABILITIES_EXT ),
//            Field ( VideoEncodeH265SessionCreateInfo,                                      VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_SESSION_CREATE_INFO_EXT ),
            Field ( VideoEncodeH265SessionParametersCreateInfo,                            VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_SESSION_PARAMETERS_CREATE_INFO_EXT ),
            Field ( VideoEncodeH265SessionParametersAddInfo,                               VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_SESSION_PARAMETERS_ADD_INFO_EXT ),
            Field ( VideoEncodeH265VCLFrameInfo,                                           VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_VCL_FRAME_INFO_EXT ),
            Field ( VideoEncodeH265DPBSlotInfo,                                            VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_DPB_SLOT_INFO_EXT ),
            Field ( VideoEncodeH265NALUSliceSegment,                                       VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_NALU_SLICE_SEGMENT_EXT ),
            Field ( VideoEncodeH265EmitPictureParameters,                                  VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_EMIT_PICTURE_PARAMETERS_EXT ),
            Field ( VideoEncodeH265Profile,                                                VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_PROFILE_EXT ),
            Field ( VideoEncodeH265ReferenceLists,                                         VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_REFERENCE_LISTS_EXT ),
            Field ( VideoEncodeH265RateControlInfo,                                        VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_RATE_CONTROL_INFO_EXT ),
            Field ( VideoEncodeH265RateControlLayerInfo,                                   VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_RATE_CONTROL_LAYER_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_VIDEO_DECODE_H264_AVAILABLE

            Field ( VideoDecodeH264Capabilities,                                           VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_CAPABILITIES_EXT ),
//            Field ( VideoDecodeH264SessionCreateInfo,                                      VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_SESSION_CREATE_INFO_EXT ),
            Field ( VideoDecodeH264PictureInfo,                                            VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_PICTURE_INFO_EXT ),
            Field ( VideoDecodeH264MVC,                                                    VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_MVC_EXT ),
            Field ( VideoDecodeH264Profile,                                                VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_PROFILE_EXT ),
            Field ( VideoDecodeH264SessionParametersCreateInfo,                            VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_SESSION_PARAMETERS_CREATE_INFO_EXT ),
            Field ( VideoDecodeH264SessionParametersAddInfo,                               VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_SESSION_PARAMETERS_ADD_INFO_EXT ),
            Field ( VideoDecodeH264DPBSlotInfo,                                            VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_DPB_SLOT_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_TEXTURE_GATHER_BIAS_LOD_AVAILABLE

            Field ( TextureLODGatherFormatPropertiesAMD,                                   VkStructureType :: VK_STRUCTURE_TYPE_TEXTURE_LOD_GATHER_FORMAT_PROPERTIES_AMD ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE && ! __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            Field ( RenderingInfo,                                                         VkStructureType :: VK_STRUCTURE_TYPE_RENDERING_INFO_KHR ),
            Field ( RenderingAttachmentInfo,                                               VkStructureType :: VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO_KHR ),
            Field ( PipelineRenderingCreateInfo,                                           VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO_KHR ),
            Field ( PhysicalDeviceDynamicRenderingFeatures,                                VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DYNAMIC_RENDERING_FEATURES_KHR ),
            Field ( CommandBufferInheritanceRenderingInfo,                                 VkStructureType :: VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_RENDERING_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE

            Field ( RenderingFragmentShadingRateAttachmentInfo,                            VkStructureType :: VK_STRUCTURE_TYPE_RENDERING_FRAGMENT_SHADING_RATE_ATTACHMENT_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

            Field ( RenderingFragmentDensityMapAttachmentInfo,                             VkStructureType :: VK_STRUCTURE_TYPE_RENDERING_FRAGMENT_DENSITY_MAP_ATTACHMENT_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_AMD_MIXED_ATTACHMENT_SAMPLES_AVAILABLE

            Field ( AttachmentSampleCountInfoAMD,                                          VkStructureType :: VK_STRUCTURE_TYPE_ATTACHMENT_SAMPLE_COUNT_INFO_AMD ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAMEBUFFER_MIXED_SAMPLES_AVAILABLE

            Field ( AttachmentSampleCountInfoNVidia,                                       VkStructureType :: VK_STRUCTURE_TYPE_ATTACHMENT_SAMPLE_COUNT_INFO_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE

            Field ( MultiviewPerViewAttributesInfoNVidiaExperimental,                      VkStructureType :: VK_STRUCTURE_TYPE_MULTIVIEW_PER_VIEW_ATTRIBUTES_INFO_NVX ),
            Field ( PhysicalDeviceMultiviewPerViewAttributesPropertiesNVidiaExperimental,  VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_PER_VIEW_ATTRIBUTES_PROPERTIES_NVX ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_GAMES_PLATFORM_STREAM_DESCRIPTOR_SURFACE_AVAILABLE

            Field ( StreamDescriptorSurfaceCreateInfoGoogle,                               VkStructureType :: VK_STRUCTURE_TYPE_STREAM_DESCRIPTOR_SURFACE_CREATE_INFO_GGP ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CORNER_SAMPLED_IMAGE_AVAILABLE

            Field ( PhysicalDeviceCornerSampledImageFeaturesNVidia,                        VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CORNER_SAMPLED_IMAGE_FEATURES_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_AVAILABLE

            Field ( ExternalMemoryImageCreateInfoNVidia,                                   VkStructureType :: VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO_NV ),
            Field ( ExportMemoryAllocateInfoNVidia,                                        VkStructureType :: VK_STRUCTURE_TYPE_EXPORT_MEMORY_ALLOCATE_INFO_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_WIN32_AVAILABLE

            Field ( ImportMemoryWin32HandleInfoNVidia,                                     VkStructureType :: VK_STRUCTURE_TYPE_IMPORT_MEMORY_WIN32_HANDLE_INFO_NV ),
            Field ( ExportMemoryWin32HandleInfoNVidia,                                     VkStructureType :: VK_STRUCTURE_TYPE_EXPORT_MEMORY_WIN32_HANDLE_INFO_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_WIN32_KEYED_MUTEX_AVAILABLE

            Field ( Win32KeyedMutexAcquireReleaseInfoNVidia,                               VkStructureType :: VK_STRUCTURE_TYPE_WIN32_KEYED_MUTEX_ACQUIRE_RELEASE_INFO_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_FLAGS_AVAILABLE

            Field ( ValidationFlags,                                                       VkStructureType :: VK_STRUCTURE_TYPE_VALIDATION_FLAGS_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_NINTENDO_VI_SURFACE_AVAILABLE

            Field ( ViSurfaceCreateInfoNVidia,                                             VkStructureType :: VK_STRUCTURE_TYPE_VI_SURFACE_CREATE_INFO_NN ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXTURE_COMPRESSION_ASTC_HDR_AVAILABLE && ! __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            Field ( PhysicalDeviceTextureCompressionASTCHDRFeatures,                       VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TEXTURE_COMPRESSION_ASTC_HDR_FEATURES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ASTC_DECODE_MODE_AVAILABLE

            Field ( ImageViewASTCDecodeMode,                                               VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_VIEW_ASTC_DECODE_MODE_EXT ),
            Field ( PhysicalDeviceASTCDecodeFeatures,                                      VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ASTC_DECODE_FEATURES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_WIN32_AVAILABLE

            Field ( ImportMemoryWin32HandleInfo,                                           VkStructureType :: VK_STRUCTURE_TYPE_IMPORT_MEMORY_WIN32_HANDLE_INFO_KHR ),
            Field ( ExportMemoryWin32HandleInfo,                                           VkStructureType :: VK_STRUCTURE_TYPE_EXPORT_MEMORY_WIN32_HANDLE_INFO_KHR ),
            Field ( MemoryWin32HandleProperties,                                           VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_WIN32_HANDLE_PROPERTIES_KHR ),
            Field ( MemoryGetWin32HandleInfo,                                              VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_GET_WIN32_HANDLE_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_FD_AVAILABLE

            Field ( ImportMemoryFdInfo,                                                    VkStructureType :: VK_STRUCTURE_TYPE_IMPORT_MEMORY_FD_INFO_KHR ),
            Field ( MemoryFdProperties,                                                    VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_FD_PROPERTIES_KHR ),
            Field ( MemoryGetFdInfo,                                                       VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_GET_FD_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WIN32_KEYED_MUTEX_AVAILABLE

            Field ( Win32KeyedMutexAcquireReleaseInfo,                                     VkStructureType :: VK_STRUCTURE_TYPE_WIN32_KEYED_MUTEX_ACQUIRE_RELEASE_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_WIN32_AVAILABLE

            Field ( ImportSemaphoreWin32HandleInfo,                                        VkStructureType :: VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_WIN32_HANDLE_INFO_KHR ),
            Field ( ExportSemaphoreWin32HandleInfo,                                        VkStructureType :: VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_WIN32_HANDLE_INFO_KHR ),
            Field ( D3D12FenceSubmitInfo,                                                  VkStructureType :: VK_STRUCTURE_TYPE_D3D12_FENCE_SUBMIT_INFO_KHR ),
            Field ( SemaphoreGetWin32HandleInfo,                                           VkStructureType :: VK_STRUCTURE_TYPE_SEMAPHORE_GET_WIN32_HANDLE_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_FD_AVAILABLE

            Field ( ImportSemaphoreFdInfo,                                                 VkStructureType :: VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_FD_INFO_KHR ),
            Field ( SemaphoreGetFdInfo,                                                    VkStructureType :: VK_STRUCTURE_TYPE_SEMAPHORE_GET_FD_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PUSH_DESCRIPTOR_AVAILABLE

            Field ( PhysicalDevicePushDescriptorProperties,                                VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PUSH_DESCRIPTOR_PROPERTIES_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE

            Field ( CommandBufferInheritanceConditionalRenderingInfo,                      VkStructureType :: VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_CONDITIONAL_RENDERING_INFO_EXT ),

            Field ( PhysicalDeviceConditionalRenderingFeatures,                            VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CONDITIONAL_RENDERING_FEATURES_EXT ),

            Field ( ConditionalRenderingBeginInfo,                                         VkStructureType :: VK_STRUCTURE_TYPE_CONDITIONAL_RENDERING_BEGIN_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_INCREMENTAL_PRESENT_AVAILABLE

            Field ( PresentRegions,                                                        VkStructureType :: VK_STRUCTURE_TYPE_PRESENT_REGIONS_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CLIP_SPACE_W_SCALING_AVAILABLE

            Field ( PipelineViewportWScalingStateCreateInfoNVidia,                         VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_W_SCALING_STATE_CREATE_INFO_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISPLAY_SURFACE_COUNTER_AVAILABLE

            Field ( SurfaceCapabilities2,                                                  VkStructureType :: VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_2_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISPLAY_CONTROL_AVAILABLE

            Field ( DisplayPowerInfo,                                                      VkStructureType :: VK_STRUCTURE_TYPE_DISPLAY_POWER_INFO_EXT ),
            Field ( DeviceEventInfo,                                                       VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_EVENT_INFO_EXT ),
            Field ( DisplayEventInfo,                                                      VkStructureType :: VK_STRUCTURE_TYPE_DISPLAY_EVENT_INFO_EXT ),
            Field ( SwapchainCounterCreateInfo,                                            VkStructureType :: VK_STRUCTURE_TYPE_SWAPCHAIN_COUNTER_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_DISPLAY_TIMING_AVAILABLE

            Field ( PresentTimesInfoGoogle,                                                VkStructureType :: VK_STRUCTURE_TYPE_PRESENT_TIMES_INFO_GOOGLE ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_VIEWPORT_SWIZZLE_AVAILABLE

            Field ( PipelineViewportSwizzleStateCreateInfoNVidia,                          VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_SWIZZLE_STATE_CREATE_INFO_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISCARD_RECTANGLES_AVAILABLE

            Field ( PhysicalDeviceDiscardRectangleProperties,                              VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DISCARD_RECTANGLE_PROPERTIES_EXT ),
            Field ( PipelineDiscardRectangleStateCreateInfo,                               VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_DISCARD_RECTANGLE_STATE_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONSERVATIVE_RASTERIZATION_AVAILABLE

            Field ( PhysicalDeviceConservativeRasterizationProperties,                     VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CONSERVATIVE_RASTERIZATION_PROPERTIES_EXT ),
            Field ( PipelineRasterizationConservativeStateCreateInfo,                      VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_CONSERVATIVE_STATE_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_ENABLE_AVAILABLE

            Field ( PhysicalDeviceDepthClipEnableFeatures,                                 VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_CLIP_ENABLE_FEATURES_EXT ),
            Field ( PipelineRasterizationDepthClipStateCreateInfo,                         VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_DEPTH_CLIP_STATE_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HDR_METADATA_AVAILABLE

            Field ( HDRMetadata,                                                           VkStructureType :: VK_STRUCTURE_TYPE_HDR_METADATA_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHARED_PRESENTABLE_IMAGE_AVAILABLE

            Field ( SharedPresentSurfaceCapabilities,                                      VkStructureType :: VK_STRUCTURE_TYPE_SHARED_PRESENT_SURFACE_CAPABILITIES_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_WIN32_AVAILABLE

            Field ( ImportFenceWin32HandleInfo,                                            VkStructureType :: VK_STRUCTURE_TYPE_IMPORT_FENCE_WIN32_HANDLE_INFO_KHR ),
            Field ( ExportFenceWin32HandleInfo,                                            VkStructureType :: VK_STRUCTURE_TYPE_EXPORT_FENCE_WIN32_HANDLE_INFO_KHR ),
            Field ( FenceGetWin32HandleInfo,                                               VkStructureType :: VK_STRUCTURE_TYPE_FENCE_GET_WIN32_HANDLE_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_FD_AVAILABLE

            Field ( ImportFenceFdInfo,                                                     VkStructureType :: VK_STRUCTURE_TYPE_IMPORT_FENCE_FD_INFO_KHR ),
            Field ( FenceGetFdInfo,                                                        VkStructureType :: VK_STRUCTURE_TYPE_FENCE_GET_FD_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

            Field ( PhysicalDevicePerformanceQueryFeatures,                                VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PERFORMANCE_QUERY_FEATURES_KHR ),
            Field ( PhysicalDevicePerformanceQueryProperties,                              VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PERFORMANCE_QUERY_PROPERTIES_KHR ),
            Field ( QueryPoolPerformanceCreateInfo,                                        VkStructureType :: VK_STRUCTURE_TYPE_QUERY_POOL_PERFORMANCE_CREATE_INFO_KHR ),
            Field ( PerformanceQuerySubmitInfo,                                            VkStructureType :: VK_STRUCTURE_TYPE_PERFORMANCE_QUERY_SUBMIT_INFO_KHR ),
            Field ( AcquireProfilingLockInfo,                                              VkStructureType :: VK_STRUCTURE_TYPE_ACQUIRE_PROFILING_LOCK_INFO_KHR ),
            Field ( PerformanceCounter,                                                    VkStructureType :: VK_STRUCTURE_TYPE_PERFORMANCE_COUNTER_KHR ),
            Field ( PerformanceCounterDescription,                                         VkStructureType :: VK_STRUCTURE_TYPE_PERFORMANCE_COUNTER_DESCRIPTION_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_GET_SURFACE_CAPABILITIES_AVAILABLE

            Field ( PhysicalDeviceSurfaceInfo,                                             VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SURFACE_INFO_2_KHR ),
            Field ( SurfaceCapabilities,                                                   VkStructureType :: VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_2_KHR ),
            Field ( SurfaceFormat,                                                         VkStructureType :: VK_STRUCTURE_TYPE_SURFACE_FORMAT_2_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_GET_DISPLAY_PROPERTIES_AVAILABLE

            Field ( DisplayProperties,                                                     VkStructureType :: VK_STRUCTURE_TYPE_DISPLAY_PROPERTIES_2_KHR ),
            Field ( DisplayPlaneProperties,                                                VkStructureType :: VK_STRUCTURE_TYPE_DISPLAY_PLANE_PROPERTIES_2_KHR ),
            Field ( DisplayModeProperties,                                                 VkStructureType :: VK_STRUCTURE_TYPE_DISPLAY_MODE_PROPERTIES_2_KHR ),
            Field ( DisplayPlaneInfo,                                                      VkStructureType :: VK_STRUCTURE_TYPE_DISPLAY_PLANE_INFO_2_KHR ),
            Field ( DisplayPlaneCapabilities,                                              VkStructureType :: VK_STRUCTURE_TYPE_DISPLAY_PLANE_CAPABILITIES_2_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_APPLE_MOLTEN_VULKAN_IOS_SURFACE_AVAILABLE

            Field ( IOSSurfaceCreateInfoApple,                                             VkStructureType :: VK_STRUCTURE_TYPE_IOS_SURFACE_CREATE_INFO_MVK ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_APPLE_MOLTEN_VULKAN_MACOS_SURFACE_AVAILABLE

            Field ( MacOSSurfaceCreateInfoApple,                                           VkStructureType :: VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_UTILS_AVAILABLE

            Field ( DebugUtilsObjectNameInfo,                                              VkStructureType :: VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT ),
            Field ( DebugUtilsObjectTagInfo,                                               VkStructureType :: VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_TAG_INFO_EXT ),
            Field ( DebugUtilsLabel,                                                       VkStructureType :: VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT ),
            Field ( DebugUtilsMessengerCallbackData,                                       VkStructureType :: VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CALLBACK_DATA_EXT ),
            Field ( DebugUtilsMessengerCreateInfo,                                         VkStructureType :: VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_AVAILABLE

            Field ( AndroidHardwareBufferUsageGoogle,                                      VkStructureType :: VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_USAGE_ANDROID ),
            Field ( AndroidHardwareBufferPropertiesGoogle,                                 VkStructureType :: VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_PROPERTIES_ANDROID ),
            Field ( AndroidHardwareBufferFormatPropertiesGoogle,                           VkStructureType :: VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_FORMAT_PROPERTIES_ANDROID ),
            Field ( ImportAndroidHardwareBufferInfoGoogle,                                 VkStructureType :: VK_STRUCTURE_TYPE_IMPORT_ANDROID_HARDWARE_BUFFER_INFO_ANDROID ),
            Field ( MemoryGetAndroidHardwareBufferInfoGoogle,                              VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_GET_ANDROID_HARDWARE_BUFFER_INFO_ANDROID ),
            Field ( ExternalFormatGoogle,                                                  VkStructureType :: VK_STRUCTURE_TYPE_EXTERNAL_FORMAT_ANDROID ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FORMAT_FEATURE_FLAGS_AVAILABLE && __C_ENG_VULKAN_API_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_AVAILABLE

            Field ( AndroidHardwareBufferFormatPropertiesGoogle,                           VkStructureType :: VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_FORMAT_PROPERTIES_2_ANDROID ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE && ! __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            Field ( PhysicalDeviceInlineUniformBlockFeatures,                              VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INLINE_UNIFORM_BLOCK_FEATURES_EXT ),
            Field ( PhysicalDeviceInlineUniformBlockProperties,                            VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INLINE_UNIFORM_BLOCK_PROPERTIES_EXT ),
            Field ( WriteDescriptorSetInlineUniformBlock,                                  VkStructureType :: VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_INLINE_UNIFORM_BLOCK_EXT ),
            Field ( DescriptorPoolInlineUniformBlockCreateInfo,                            VkStructureType :: VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_INLINE_UNIFORM_BLOCK_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE

            Field ( SampleLocationsInfo,                                                   VkStructureType :: VK_STRUCTURE_TYPE_SAMPLE_LOCATIONS_INFO_EXT ),
            Field ( RenderPassSampleLocationsBeginInfo,                                    VkStructureType :: VK_STRUCTURE_TYPE_RENDER_PASS_SAMPLE_LOCATIONS_BEGIN_INFO_EXT ),
            Field ( PipelineSampleLocationsStateCreateInfo,                                VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_SAMPLE_LOCATIONS_STATE_CREATE_INFO_EXT ),
            Field ( PhysicalDeviceSampleLocationsProperties,                               VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLE_LOCATIONS_PROPERTIES_EXT ),
            Field ( MultisampleProperties,                                                 VkStructureType :: VK_STRUCTURE_TYPE_MULTISAMPLE_PROPERTIES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE

            Field ( PhysicalDeviceBlendOperationAdvancedFeatures,                          VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BLEND_OPERATION_ADVANCED_FEATURES_EXT ),
            Field ( PhysicalDeviceBlendOperationAdvancedProperties,                        VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BLEND_OPERATION_ADVANCED_PROPERTIES_EXT ),
            Field ( PipelineColorBlendAdvancedStateCreateInfo,                             VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_ADVANCED_STATE_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_COVERAGE_TO_COLOR_AVAILABLE

            Field ( PipelineCoverageToColorStateCreateInfoNVidia,                          VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_COVERAGE_TO_COLOR_STATE_CREATE_INFO_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE

            Field ( WriteDescriptorSetAccelerationStructure,                               VkStructureType :: VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_ACCELERATION_STRUCTURE_KHR ),

            Field ( AccelerationStructureBuildGeometryInfo,                                VkStructureType :: VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR ),
            Field ( AccelerationStructureDeviceAddressInfo,                                VkStructureType :: VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_DEVICE_ADDRESS_INFO_KHR ),
            Field ( AccelerationStructureGeometryAABBSData,                                VkStructureType :: VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_AABBS_DATA_KHR ),
            Field ( AccelerationStructureGeometryInstancesData,                            VkStructureType :: VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_INSTANCES_DATA_KHR ),
            Field ( AccelerationStructureGeometryTrianglesData,                            VkStructureType :: VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR ),
            Field ( AccelerationStructureGeometry,                                         VkStructureType :: VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR ),
            Field ( AccelerationStructureVersionInfo,                                      VkStructureType :: VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_VERSION_INFO_KHR ),

            Field ( CopyAccelerationStructureInfo,                                         VkStructureType :: VK_STRUCTURE_TYPE_COPY_ACCELERATION_STRUCTURE_INFO_KHR ),
            Field ( CopyAccelerationStructureToMemoryInfo,                                 VkStructureType :: VK_STRUCTURE_TYPE_COPY_ACCELERATION_STRUCTURE_TO_MEMORY_INFO_KHR ),
            Field ( CopyMemoryToAccelerationStructureInfo,                                 VkStructureType :: VK_STRUCTURE_TYPE_COPY_MEMORY_TO_ACCELERATION_STRUCTURE_INFO_KHR ),

            Field ( PhysicalDeviceAccelerationStructureFeatures,                           VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_FEATURES_KHR ),
            Field ( PhysicalDeviceAccelerationStructureProperties,                         VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_PROPERTIES_KHR ),

            Field ( AccelerationStructureCreateInfo,                                       VkStructureType :: VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR ),
            Field ( AccelerationStructureBuildSizesInfo,                                   VkStructureType :: VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE

            Field ( PhysicalDeviceRayTracingPipelineFeatures,                              VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_FEATURES_KHR ),
            Field ( PhysicalDeviceRayTracingPipelineProperties,                            VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_PROPERTIES_KHR ),
            Field ( RayTracingPipelineCreateInfo,                                          VkStructureType :: VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_CREATE_INFO_KHR ),
            Field ( RayTracingShaderGroupCreateInfo,                                       VkStructureType :: VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_KHR ),
            Field ( RayTracingPipelineInterfaceCreateInfo,                                 VkStructureType :: VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_INTERFACE_CREATE_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_QUERY_AVAILABLE

            Field ( PhysicalDeviceRayQueryFeatures,                                        VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_QUERY_FEATURES_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAMEBUFFER_MIXED_SAMPLES_AVAILABLE

            Field ( PipelineCoverageModulationStateCreateInfoNVidia,                       VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_COVERAGE_MODULATION_STATE_CREATE_INFO_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE

            Field ( PhysicalDeviceShaderSmBuiltinsFeaturesNVidia,                          VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SM_BUILTINS_FEATURES_NV ),
            Field ( PhysicalDeviceShaderSmBuiltinsPropertiesNVidia,                        VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SM_BUILTINS_PROPERTIES_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_DRM_FORMAT_MODIFIER_AVAILABLE

            Field ( DRMFormatModifierPropertiesList,                                       VkStructureType :: VK_STRUCTURE_TYPE_DRM_FORMAT_MODIFIER_PROPERTIES_LIST_EXT ),

            Field ( PhysicalDeviceImageDRMFormatModifierInfo,                              VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_DRM_FORMAT_MODIFIER_INFO_EXT ),

            Field ( ImageDRMFormatModifierListCreateInfo,                                  VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_LIST_CREATE_INFO_EXT ),
            Field ( ImageDRMFormatModifierExplicitCreateInfo,                              VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_EXPLICIT_CREATE_INFO_EXT ),
            Field ( ImageDRMFormatModifierProperties,                                      VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_PROPERTIES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_DRM_FORMAT_MODIFIER_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FORMAT_FEATURE_FLAGS_AVAILABLE

            Field ( DRMFormatModifierPropertiesList2,                                      VkStructureType :: VK_STRUCTURE_TYPE_DRM_FORMAT_MODIFIER_PROPERTIES_LIST_2_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_CACHE_AVAILABLE

            Field ( ValidationCacheCreateInfo,                                             VkStructureType :: VK_STRUCTURE_TYPE_VALIDATION_CACHE_CREATE_INFO_EXT ),
            Field ( ShaderModuleValidationCacheCreateInfo,                                 VkStructureType :: VK_STRUCTURE_TYPE_SHADER_MODULE_VALIDATION_CACHE_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE

            Field ( PhysicalDevicePortabilitySubsetFeatures,                               VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PORTABILITY_SUBSET_FEATURES_KHR ),
            Field ( PhysicalDevicePortabilitySubsetProperties,                             VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PORTABILITY_SUBSET_PROPERTIES_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE

            Field ( PipelineViewportShadingRateImageStateCreateInfoNVidia,                 VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_SHADING_RATE_IMAGE_STATE_CREATE_INFO_NV ),
            Field ( PhysicalDeviceShadingRateImageFeaturesNVidia,                          VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADING_RATE_IMAGE_FEATURES_NV ),
            Field ( PhysicalDeviceShadingRateImagePropertiesNVidia,                        VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADING_RATE_IMAGE_PROPERTIES_NV ),
            Field ( PipelineViewportCoarseSampleOrderStateCreateInfoNVidia,                VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_COARSE_SAMPLE_ORDER_STATE_CREATE_INFO_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE

            Field ( RayTracingPipelineCreateInfoNVidia,                                    VkStructureType :: VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_CREATE_INFO_NV ),
            Field ( AccelerationStructureCreateInfoNVidia,                                 VkStructureType :: VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_NV ),

            Field ( GeometryNVidia,                                                        VkStructureType :: VK_STRUCTURE_TYPE_GEOMETRY_NV ),
            Field ( GeometryTrianglesNVidia,                                               VkStructureType :: VK_STRUCTURE_TYPE_GEOMETRY_TRIANGLES_NV ),
            Field ( GeometryAABBNVidia,                                                    VkStructureType :: VK_STRUCTURE_TYPE_GEOMETRY_AABB_NV ),

            Field ( BindAccelerationStructureMemoryInfoNVidia,                             VkStructureType :: VK_STRUCTURE_TYPE_BIND_ACCELERATION_STRUCTURE_MEMORY_INFO_NV ),
            Field ( WriteDescriptorSetAccelerationStructureNVidia,                         VkStructureType :: VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_ACCELERATION_STRUCTURE_NV ),
            Field ( AccelerationStructureMemoryRequirementsInfoNVidia,                     VkStructureType :: VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_INFO_NV ),

            Field ( PhysicalDeviceRayTracingPropertiesNVidia,                              VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PROPERTIES_NV ),

            Field ( RayTracingShaderGroupCreateInfoNVidia,                                 VkStructureType :: VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_NV ),
            Field ( AccelerationStructureInfoNVidia,                                       VkStructureType :: VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_INFO_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_REPRESENTATIVE_FRAGMENT_TEST_AVAILABLE

            Field ( PhysicalDeviceRepresentativeFragmentTestFeaturesNVidia,                VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_REPRESENTATIVE_FRAGMENT_TEST_FEATURES_NV ),
            Field ( PipelineRepresentativeFragmentTestStateCreateInfoNVidia,               VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_REPRESENTATIVE_FRAGMENT_TEST_STATE_CREATE_INFO_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FILTER_CUBIC_AVAILABLE

            Field ( PhysicalDeviceImageViewImageFormatInfo,                                VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_VIEW_IMAGE_FORMAT_INFO_EXT ),
            Field ( FilterCubicImageViewImageFormatProperties,                             VkStructureType :: VK_STRUCTURE_TYPE_FILTER_CUBIC_IMAGE_VIEW_IMAGE_FORMAT_PROPERTIES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_AVAILABLE

            Field ( DeviceQueueGlobalPriorityCreateInfo,                                   VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_QUEUE_GLOBAL_PRIORITY_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTERNAL_MEMORY_HOST_AVAILABLE

            Field ( ImportMemoryHostPointerInfo,                                           VkStructureType :: VK_STRUCTURE_TYPE_IMPORT_MEMORY_HOST_POINTER_INFO_EXT ),
            Field ( MemoryHostPointerProperties,                                           VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_HOST_POINTER_PROPERTIES_EXT ),
            Field ( PhysicalDeviceExternalMemoryHostProperties,                            VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_MEMORY_HOST_PROPERTIES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_CLOCK_AVAILABLE

            Field ( PhysicalDeviceShaderClockFeatures,                                     VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CLOCK_FEATURES_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_PIPELINE_COMPILER_CONTROL_AVAILABLE

            Field ( PipelineCompilerControlCreateInfoAMD,                                  VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_COMPILER_CONTROL_CREATE_INFO_AMD ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CALIBRATED_TIMESTAMPS_AVAILABLE

            Field ( CalibratedTimestampInfo,                                               VkStructureType :: VK_STRUCTURE_TYPE_CALIBRATED_TIMESTAMP_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_AVAILABLE

            Field ( PhysicalDeviceShaderCorePropertiesAMD,                                 VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_PROPERTIES_AMD ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_2_AVAILABLE

            Field ( PhysicalDeviceShaderCoreProperties2AMD,                                VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_PROPERTIES_2_AMD ),

#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_VIDEO_DECODE_H265_AVAILABLE

            Field ( VideoDecodeH265Capabilities,                                           VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_CAPABILITIES_EXT ),
//            Field ( VideoDecodeH265SessionCreateInfo,                                      VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_SESSION_CREATE_INFO_EXT ),
            Field ( VideoDecodeH265SessionParametersCreateInfo,                            VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_SESSION_PARAMETERS_CREATE_INFO_EXT ),
            Field ( VideoDecodeH265SessionParametersAddInfo,                               VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_SESSION_PARAMETERS_ADD_INFO_EXT ),
            Field ( VideoDecodeH265Profile,                                                VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_PROFILE_EXT ),
            Field ( VideoDecodeH265PictureInfo,                                            VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_PICTURE_INFO_EXT ),
            Field ( VideoDecodeH265DPBSlotInfo,                                            VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_DPB_SLOT_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_MEMORY_OVERALLOCATION_BEHAVIOUR_AVAILABLE

            Field ( DeviceMemoryOverAllocationCreateInfoAMD,                               VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_MEMORY_OVERALLOCATION_CREATE_INFO_AMD ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE

            Field ( PhysicalDeviceVertexAttributeDivisorFeatures,                          VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VERTEX_ATTRIBUTE_DIVISOR_FEATURES_EXT ),
            Field ( PhysicalDeviceVertexAttributeDivisorProperties,                        VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VERTEX_ATTRIBUTE_DIVISOR_PROPERTIES_EXT ),
            Field ( PipelineVertexInputDivisorStateCreateInfo,                             VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_DIVISOR_STATE_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_GAMES_PLATFORM_FRAME_TOKEN_AVAILABLE

            Field ( PresentFrameTokenGoogle,                                               VkStructureType :: VK_STRUCTURE_TYPE_PRESENT_FRAME_TOKEN_GGP ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_FEEDBACK_AVAILABLE && ! __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            Field ( PipelineCreationFeedbackCreateInfo,                                    VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_CREATION_FEEDBACK_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COMPUTE_SHADER_DERIVATIVES_AVAILABLE

            Field ( PhysicalDeviceComputeShaderDerivativesFeaturesNVidia,                  VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COMPUTE_SHADER_DERIVATIVES_FEATURES_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE

            Field ( PhysicalDeviceMeshShaderFeaturesNVidia,                                VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_FEATURES_NV ),
            Field ( PhysicalDeviceMeshShaderPropertiesNVidia,                              VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_PROPERTIES_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADER_BARYCENTRIC_AVAILABLE

            Field ( PhysicalDeviceFragmentShaderBarycentricFeaturesNVidia,                 VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADER_BARYCENTRIC_FEATURES_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_IMAGE_FOOTPRINT_AVAILABLE

            Field ( PhysicalDeviceShaderImageFootprintFeaturesNVidia,                      VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_IMAGE_FOOTPRINT_FEATURES_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SCISSOR_EXCLUSIVE_AVAILABLE

            Field ( PipelineViewportExclusiveScissorStateCreateInfoNVidia,                 VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_EXCLUSIVE_SCISSOR_STATE_CREATE_INFO_NV ),
            Field ( PhysicalDeviceExclusiveScissorFeaturesNVidia,                          VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXCLUSIVE_SCISSOR_FEATURES_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTIC_CHECKPOINTS_AVAILABLE

            Field ( CheckpointDataNVidia,                                                  VkStructureType :: VK_STRUCTURE_TYPE_CHECKPOINT_DATA_NV ),
            Field ( QueueFamilyCheckpointPropertiesNVidia,                                 VkStructureType :: VK_STRUCTURE_TYPE_QUEUE_FAMILY_CHECKPOINT_PROPERTIES_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_SHADER_INTEGER_FUNCTIONS_AVAILABLE

            Field ( PhysicalDeviceShaderIntegerFunctionsFeaturesIntel,                     VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_INTEGER_FUNCTIONS_2_FEATURES_INTEL ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE

            Field ( QueryPoolPerformanceCreateInfoIntel,                                   VkStructureType :: VK_STRUCTURE_TYPE_QUERY_POOL_PERFORMANCE_QUERY_CREATE_INFO_INTEL ),
            Field ( InitializePerformanceAPIInfoIntel,                                     VkStructureType :: VK_STRUCTURE_TYPE_INITIALIZE_PERFORMANCE_API_INFO_INTEL ),
            Field ( PerformanceMarkerInfoIntel,                                            VkStructureType :: VK_STRUCTURE_TYPE_PERFORMANCE_MARKER_INFO_INTEL ),
            Field ( PerformanceStreamMarkerInfoIntel,                                      VkStructureType :: VK_STRUCTURE_TYPE_PERFORMANCE_STREAM_MARKER_INFO_INTEL ),
            Field ( PerformanceOverrideInfoIntel,                                          VkStructureType :: VK_STRUCTURE_TYPE_PERFORMANCE_OVERRIDE_INFO_INTEL ),
            Field ( PerformanceConfigurationAcquireInfoIntel,                              VkStructureType :: VK_STRUCTURE_TYPE_PERFORMANCE_CONFIGURATION_ACQUIRE_INFO_INTEL ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PCI_BUS_INFO_AVAILABLE

            Field ( PhysicalDevicePCIBusInfoProperties,                                    VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PCI_BUS_INFO_PROPERTIES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_DISPLAY_NATIVE_HDR_AVAILABLE

            Field ( DisplayNativeHDRSurfaceCapabilitiesAMD,                                VkStructureType :: VK_STRUCTURE_TYPE_DISPLAY_NATIVE_HDR_SURFACE_CAPABILITIES_AMD ),
            Field ( SwachainDisplayNativeHDRCreateInfoAMD,                                 VkStructureType :: VK_STRUCTURE_TYPE_SWAPCHAIN_DISPLAY_NATIVE_HDR_CREATE_INFO_AMD ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_IMAGEPIPE_SURFACE_AVAILABLE

            Field ( ImagepipeSurfaceCreateInfoGoogle,                                      VkStructureType :: VK_STRUCTURE_TYPE_IMAGEPIPE_SURFACE_CREATE_INFO_FUCHSIA ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_TERMINATE_INVOCATION_AVAILABLE && ! __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            Field ( PhysicalDeviceShaderTerminateInvocationFeatures,                       VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_TERMINATE_INVOCATION_FEATURES_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_METAL_SURFACE_AVAILABLE

            Field ( MetalSurfaceCreateInfo,                                                VkStructureType :: VK_STRUCTURE_TYPE_METAL_SURFACE_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

            Field ( PhysicalDeviceFragmentDensityMapFeatures,                              VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_FEATURES_EXT ),
            Field ( PhysicalDeviceFragmentDensityMapProperties,                            VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_PROPERTIES_EXT ),
            Field ( RenderPassFragmentDensityMapCreateInfo,                                VkStructureType :: VK_STRUCTURE_TYPE_RENDER_PASS_FRAGMENT_DENSITY_MAP_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE && ! __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            Field ( PhysicalDeviceSubgroupSizeControlFeatures,                             VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_SIZE_CONTROL_FEATURES_EXT ),
            Field ( PhysicalDeviceSubgroupSizeControlProperties,                           VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_SIZE_CONTROL_PROPERTIES_EXT ),
            Field ( PipelineShaderStageRequiredSubgroupSizeCreateInfo,                     VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_REQUIRED_SUBGROUP_SIZE_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE

            Field ( PhysicalDeviceFragmentShadingRateFeatures,                             VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_FEATURES_KHR ),
            Field ( PhysicalDeviceFragmentShadingRateProperties,                           VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_PROPERTIES_KHR ),
            Field ( PhysicalDeviceFragmentShadingRate,                                     VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_KHR ),
            Field ( PipelineFragmentShadingRateStateCreateInfo,                            VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_FRAGMENT_SHADING_RATE_STATE_CREATE_INFO_KHR ),
            Field ( FragmentShadingRateAttachmentInfo,                                     VkStructureType :: VK_STRUCTURE_TYPE_FRAGMENT_SHADING_RATE_ATTACHMENT_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_DEVICE_COHERENT_MEMORY_AVAILABLE

            Field ( PhysicalDeviceCoherentMemoryFeaturesAMD,                               VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COHERENT_MEMORY_FEATURES_AMD ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_BUDGET_AVAILABLE

            Field ( PhysicalDeviceMemoryBudgetProperties,                                  VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_BUDGET_PROPERTIES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_PRIORITY_AVAILABLE

            Field ( PhysicalDeviceMemoryPriorityFeatures,                                  VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PRIORITY_FEATURES_EXT ),
            Field ( MemoryPriorityAllocateInfo,                                            VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_PRIORITY_ALLOCATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_PROTECTED_CAPABILITIES_AVAILABLE

            Field ( SurfaceProtectedCapabilities,                                          VkStructureType :: VK_STRUCTURE_TYPE_SURFACE_PROTECTED_CAPABILITIES_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_IMAGE_ALIASING_AVAILABLE

            Field ( PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNVidia,          VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEDICATED_ALLOCATION_IMAGE_ALIASING_FEATURES_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BUFFER_DEVICE_ADDRESS_AVAILABLE

            Field ( PhysicalDeviceBufferDeviceAddressFeaturesExt,                           VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BUFFER_DEVICE_ADDRESS_FEATURES_EXT ),
            Field ( BufferDeviceAddressCreateInfo,                                          VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TOOLING_INFO_AVAILABLE && ! __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            Field ( PhysicalDeviceToolProperties,                                          VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TOOL_PROPERTIES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_FEATURES_AVAILABLE

            Field ( ValidationFeatures,                                                    VkStructureType :: VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_ID_AVAILABLE

            Field ( PhysicalDevicePresentIDFeatures,                                        VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRESENT_ID_FEATURES_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_WAIT_AVAILABLE

            Field ( PhysicalDevicePresentWaitFeatures,                                     VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRESENT_WAIT_FEATURES_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE

            Field ( PhysicalDeviceCooperativeMatrixFeaturesNVidia,                         VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_FEATURES_NV ),
            Field ( PhysicalDeviceCooperativeMatrixPropertiesNVidia,                       VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_PROPERTIES_NV ),
            Field ( CooperativeMatrixPropertiesNVidia,                                     VkStructureType :: VK_STRUCTURE_TYPE_COOPERATIVE_MATRIX_PROPERTIES_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COVERAGE_REDUCTION_MODE_AVAILABLE

            Field ( PhysicalDeviceCoverageReductionModeFeaturesNVidia,                     VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COVERAGE_REDUCTION_MODE_FEATURES_NV ),
            Field ( PipelineCoverageReductionStateCreateInfoNVidia,                        VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_COVERAGE_REDUCTION_STATE_CREATE_INFO_NV ),
            Field ( FrameBufferMixedSamplesCombinationNVidia,                              VkStructureType :: VK_STRUCTURE_TYPE_FRAMEBUFFER_MIXED_SAMPLES_COMBINATION_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_SHADER_INTERLOCK_AVAILABLE

            Field ( PhysicalDeviceFragmentShaderInterlockFeatures,                         VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADER_INTERLOCK_FEATURES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_IMAGE_ARRAYS_AVAILABLE

            Field ( PhysicalDeviceYCBCRImageArraysFeatures,                                VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_YCBCR_IMAGE_ARRAYS_FEATURES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE

            Field ( PhysicalDeviceProvokingVertexFeatures,                                 VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROVOKING_VERTEX_FEATURES_EXT ),
            Field ( PhysicalDeviceProvokingVertexProperties,                               VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROVOKING_VERTEX_PROPERTIES_EXT ),
            Field ( PipelineRasterizationProvokingVertexStateCreateInfo,                   VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_PROVOKING_VERTEX_STATE_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FULL_SCREEN_EXCLUSIVE_AVAILABLE

            Field ( SurfaceFullScreenExclusiveInfo,                                        VkStructureType :: VK_STRUCTURE_TYPE_SURFACE_FULL_SCREEN_EXCLUSIVE_INFO_EXT ),
            Field ( SurfaceCapabilitiesFullScreenExclusive,                                VkStructureType :: VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_FULL_SCREEN_EXCLUSIVE_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WIN32_SURFACE_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_FULL_SCREEN_EXCLUSIVE_AVAILABLE

            Field ( SurfaceFullScreenExclusiveWin32Info,                                   VkStructureType :: VK_STRUCTURE_TYPE_SURFACE_FULL_SCREEN_EXCLUSIVE_WIN32_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HEADLESS_SURFACE_AVAILABLE

            Field ( HeadlessSurfaceCreateInfo,                                             VkStructureType :: VK_STRUCTURE_TYPE_HEADLESS_SURFACE_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE

            Field ( PhysicalDeviceLineRasterizationFeatures,                               VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_LINE_RASTERIZATION_FEATURES_EXT ),
            Field ( PhysicalDeviceLineRasterizationProperties,                             VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_LINE_RASTERIZATION_PROPERTIES_EXT ),
            Field ( PipelineRasterizationLineStateCreateInfo,                              VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_LINE_STATE_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_AVAILABLE

            Field ( PhysicalDeviceShaderAtomicFloatFeatures,                               VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT_FEATURES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INDEX_TYPE_UINT8_AVAILABLE

            Field ( PhysicalDeviceIndexTypeUInt8Features,                                  VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INDEX_TYPE_UINT8_FEATURES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE

            Field ( PhysicalDeviceExtendedDynamicStateFeatures,                            VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_DYNAMIC_STATE_FEATURES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE

            Field ( PhysicalDevicePipelineExecutablePropertiesFeatures,                    VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_EXECUTABLE_PROPERTIES_FEATURES_KHR ),
            Field ( PipelineInfo,                                                          VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_INFO_KHR ),
            Field ( PipelineExecutableProperties,                                          VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_EXECUTABLE_PROPERTIES_KHR ),
            Field ( PipelineExecutableInfo,                                                VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_EXECUTABLE_INFO_KHR ),
            Field ( PipelineExecutableStatistic,                                           VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_EXECUTABLE_STATISTIC_KHR ),
            Field ( PipelineExecutableInternalRepresentation,                              VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_EXECUTABLE_INTERNAL_REPRESENTATION_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_2_AVAILABLE

            Field ( PhysicalDeviceShaderAtomicFloat2Features,                              VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT_2_FEATURES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_IMAGE_ATOMIC_INT64_AVAILABLE

            Field ( PhysicalDeviceShaderImageAtomicInt64Features,                          VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_IMAGE_ATOMIC_INT64_FEATURES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_DEMOTE_TO_HELPER_INVOCATION_AVAILABLE && ! __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            Field ( PhysicalDeviceShaderDemoteToHelperInvocationFeatures,                  VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_DEMOTE_TO_HELPER_INVOCATION_FEATURES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE

            Field ( PhysicalDeviceDeviceGeneratedCommandsPropertiesNVidia,                 VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEVICE_GENERATED_COMMANDS_PROPERTIES_NV ),
            Field ( PhysicalDeviceDeviceGeneratedCommandsFeaturesNVidia,                   VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEVICE_GENERATED_COMMANDS_FEATURES_NV ),
            Field ( GraphicsShaderGroupCreateInfoNVidia,                                   VkStructureType :: VK_STRUCTURE_TYPE_GRAPHICS_SHADER_GROUP_CREATE_INFO_NV ),
            Field ( GraphicsPipelineShaderGroupsCreateInfoNVidia,                          VkStructureType :: VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_SHADER_GROUPS_CREATE_INFO_NV ),
            Field ( IndirectCommandsLayoutTokenNVidia,                                     VkStructureType :: VK_STRUCTURE_TYPE_INDIRECT_COMMANDS_LAYOUT_TOKEN_NV ),
            Field ( IndirectCommandsLayoutCreateInfoNVidia,                                VkStructureType :: VK_STRUCTURE_TYPE_INDIRECT_COMMANDS_LAYOUT_CREATE_INFO_NV ),
            Field ( GeneratedCommandsInfoNVidia,                                           VkStructureType :: VK_STRUCTURE_TYPE_GENERATED_COMMANDS_INFO_NV ),
            Field ( GeneratedCommandsMemoryRequirementsInfoNVidia,                         VkStructureType :: VK_STRUCTURE_TYPE_GENERATED_COMMANDS_MEMORY_REQUIREMENTS_INFO_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_INHERITED_VIEWPORT_SCISSOR_AVAILABLE

            Field ( PhysicalDeviceInheritedViewportScissorFeaturesNVidia,                  VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INHERITED_VIEWPORT_SCISSOR_FEATURES_NV ),
            Field ( CommandBufferInheritanceViewportScissorInfoNVidia,                     VkStructureType :: VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_VIEWPORT_SCISSOR_INFO_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE && ! __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            Field ( PhysicalDeviceShaderIntegerDotProductFeatures,                         VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_INTEGER_DOT_PRODUCT_FEATURES_KHR ),
            Field ( PhysicalDeviceShaderIntegerDotProductProperties,                       VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_INTEGER_DOT_PRODUCT_PROPERTIES_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE && ! __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            Field ( PhysicalDeviceTexelBufferAlignmentFeatures,                            VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TEXEL_BUFFER_ALIGNMENT_FEATURES_EXT ),
            Field ( PhysicalDeviceTexelBufferAlignmentProperties,                          VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TEXEL_BUFFER_ALIGNMENT_PROPERTIES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_RENDER_PASS_TRANSFORM_AVAILABLE

            Field ( CommandBufferInheritanceRenderPassTransformInfoQualcomm,               VkStructureType :: VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_RENDER_PASS_TRANSFORM_INFO_QCOM ),
            Field ( RenderPassTransformBeginInfoQualcomm,                                  VkStructureType :: VK_STRUCTURE_TYPE_RENDER_PASS_TRANSFORM_BEGIN_INFO_QCOM ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEVICE_MEMORY_REPORT_AVAILABLE

            Field ( PhysicalDeviceDeviceMemoryReportFeatures,                              VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEVICE_MEMORY_REPORT_FEATURES_EXT ),
            Field ( DeviceDeviceMemoryReportCreateInfo,                                    VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_DEVICE_MEMORY_REPORT_CREATE_INFO_EXT ),
            Field ( DeviceMemoryReportCallbackData,                                        VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_MEMORY_REPORT_CALLBACK_DATA_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE

            Field ( PhysicalDeviceRobustnessFeatures,                                      VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ROBUSTNESS_2_FEATURES_EXT ),
            Field ( PhysicalDeviceRobustnessProperties,                                    VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ROBUSTNESS_2_PROPERTIES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE

            Field ( SamplerCustomBorderColorCreateInfo,                                    VkStructureType :: VK_STRUCTURE_TYPE_SAMPLER_CUSTOM_BORDER_COLOR_CREATE_INFO_EXT ),
            Field ( PhysicalDeviceCustomBorderColorFeatures,                               VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CUSTOM_BORDER_COLOR_FEATURES_EXT ),
            Field ( PhysicalDeviceCustomBorderColorProperties,                             VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CUSTOM_BORDER_COLOR_PROPERTIES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_LIBRARY_AVAILABLE

            Field ( PipelineLibraryCreateInfo,                                             VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_LIBRARY_CREATE_INFO_KHR ),

#endif

#if _C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_ID_AVAILABLE

            Field ( PresentID,                                                             VkStructureType :: VK_STRUCTURE_TYPE_PRESENT_ID_KHR ),
            Field ( PhysicalDevicePresentIDFeatures,                                       VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRESENT_ID_FEATURES_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE && ! __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            Field ( PhysicalDevicePrivateDataFeatures,                                     VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRIVATE_DATA_FEATURES_EXT ),
            Field ( DevicePrivateDataCreateInfo,                                           VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_PRIVATE_DATA_CREATE_INFO_EXT ),
            Field ( PrivateDataSlotCreateInfo,                                             VkStructureType :: VK_STRUCTURE_TYPE_PRIVATE_DATA_SLOT_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE && ! __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            Field ( PhysicalDevicePipelineCreationCacheControlFeatures,                    VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_CREATION_CACHE_CONTROL_FEATURES_EXT ),

#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_ENCODE_QUEUE_AVAILABLE

            Field ( VideoEncodeInfo,                                                       VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_INFO_KHR ),
            Field ( VideoEncodeRateControlInfo,                                            VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_RATE_CONTROL_INFO_KHR ),
            Field ( VideoEncodeRateControlLayerInfo,                                       VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_RATE_CONTROL_LAYER_INFO_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTICS_CONFIG_AVAILABLE

            Field ( PhysicalDeviceDiagnosticsConfigFeaturesNVidia,                         VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DIAGNOSTICS_CONFIG_FEATURES_NV ),
            Field ( DeviceDiagnosticsConfigCreateInfoNVidia,                               VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_DIAGNOSTICS_CONFIG_CREATE_INFO_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE && ! __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            Field ( MemoryBarrier2,                                                        VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_BARRIER_2_KHR ),
            Field ( BufferMemoryBarrier2,                                                  VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER_2_KHR ),
            Field ( ImageMemoryBarrier2,                                                   VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2_KHR ),
            Field ( DependencyInfo,                                                        VkStructureType :: VK_STRUCTURE_TYPE_DEPENDENCY_INFO_KHR ),
            Field ( SubmitInfo2,                                                           VkStructureType :: VK_STRUCTURE_TYPE_SUBMIT_INFO_2_KHR ),
            Field ( SemaphoreSubmitInfo,                                                   VkStructureType :: VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO_KHR ),
            Field ( CommandBufferSubmitInfo,                                               VkStructureType :: VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO_KHR ),
            Field ( PhysicalDeviceSynchronizationFeatures,                                 VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SYNCHRONIZATION_2_FEATURES_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTIC_CHECKPOINTS_AVAILABLE

            Field ( QueueFamilyCheckpointProperties2NVidia,                                VkStructureType :: VK_STRUCTURE_TYPE_QUEUE_FAMILY_CHECKPOINT_PROPERTIES_2_NV ),
            Field ( CheckpointData2NVidia,                                                 VkStructureType :: VK_STRUCTURE_TYPE_CHECKPOINT_DATA_2_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_SUBGROUP_UNIFORM_CONTROL_FLOW_AVAILABLE

            Field ( PhysicalDeviceShaderSubgroupUniformControlFlowFeatures,                VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SUBGROUP_UNIFORM_CONTROL_FLOW_FEATURES_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ZERO_INITIALIZE_WORKGROUP_MEMORY_AVAILABLE && ! __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            Field ( PhysicalDeviceZeroInitializeWorkgroupMemoryFeatures,                   VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ZERO_INITIALIZE_WORKGROUP_MEMORY_FEATURES_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE

            Field ( PhysicalDeviceFragmentShadingRateEnumsFeaturesNVidia,                  VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_ENUMS_FEATURES_NV ),
            Field ( PhysicalDeviceFragmentShadingRateEnumsPropertiesNVidia,                VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_ENUMS_PROPERTIES_NV ),
            Field ( PipelineFragmentShadingRateEnumStateCreateInfoNVidia,                  VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_FRAGMENT_SHADING_RATE_ENUM_STATE_CREATE_INFO_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE

            Field ( AccelerationStructureGeometryMotionTrianglesDataNVidia,                VkStructureType :: VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_MOTION_TRIANGLES_DATA_NV ),
            Field ( PhysicalDeviceRayTracingMotionBlurFeaturesNVidia,                      VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_MOTION_BLUR_FEATURES_NV ),
            Field ( AccelerationStructureMotionInfoNVidia,                                 VkStructureType :: VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_MOTION_INFO_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_2_PLANE_444_FORMATS_AVAILABLE

            Field ( PhysicalDeviceYCBCR2Plane444FormatsFeatures,                           VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_YCBCR_2_PLANE_444_FORMATS_FEATURES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE

            Field ( PhysicalDeviceFragmentDensityMap2Features,                             VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_2_FEATURES_EXT ),
            Field ( PhysicalDeviceFragmentDensityMap2Properties,                           VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_2_PROPERTIES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_ROTATED_COPY_COMMANDS_AVAILABLE

            Field ( CopyCommandTransformInfoQualcomm,                                      VkStructureType :: VK_STRUCTURE_TYPE_COPY_COMMAND_TRANSFORM_INFO_QCOM ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_ROBUSTNESS_AVAILABLE && ! __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            Field ( PhysicalDeviceImageRobustnessFeatures,                                 VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_ROBUSTNESS_FEATURES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_AVAILABLE

            Field ( PhysicalDeviceWorkgroupMemoryExplicitLayoutFeatures,                   VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_FEATURES_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE && ! __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            Field ( CopyBufferInfo,                                                        VkStructureType :: VK_STRUCTURE_TYPE_COPY_BUFFER_INFO_2_KHR ),
            Field ( CopyImageInfo,                                                         VkStructureType :: VK_STRUCTURE_TYPE_COPY_IMAGE_INFO_2_KHR ),
            Field ( CopyBufferToImageInfo,                                                 VkStructureType :: VK_STRUCTURE_TYPE_COPY_BUFFER_TO_IMAGE_INFO_2_KHR ),
            Field ( CopyImageToBufferInfo,                                                 VkStructureType :: VK_STRUCTURE_TYPE_COPY_IMAGE_TO_BUFFER_INFO_2_KHR ),
            Field ( BlitImageInfo,                                                         VkStructureType :: VK_STRUCTURE_TYPE_BLIT_IMAGE_INFO_2_KHR ),
            Field ( ResolveImageInfo,                                                      VkStructureType :: VK_STRUCTURE_TYPE_RESOLVE_IMAGE_INFO_2_KHR ),
            Field ( BufferCopy,                                                            VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_COPY_2_KHR ),
            Field ( ImageCopy,                                                             VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_COPY_2_KHR ),
            Field ( ImageBlit,                                                             VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_BLIT_2_KHR ),
            Field ( BufferImageCopy,                                                       VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_IMAGE_COPY_2_KHR ),
            Field ( ImageResolve,                                                          VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_RESOLVE_2_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_4444_FORMATS_AVAILABLE

            Field ( PhysicalDevice4444FormatsFeatures,                                     VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_4444_FORMATS_FEATURES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ARM_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_AVAILABLE

            Field ( PhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM,           VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_FEATURES_ARM ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_RGBA_10_X_6_FORMATS_AVAILABLE

            Field ( PhysicalDeviceRGBA10x6FormatsFeatures,                                 VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RGBA10X6_FORMATS_FEATURES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DIRECTFB_SURFACE_AVAILABLE

            Field ( DirectfbSurfaceCreateInfo,                                             VkStructureType :: VK_STRUCTURE_TYPE_DIRECTFB_SURFACE_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE

            Field ( PhysicalDeviceMutableDescriptorTypeFeaturesValve,                      VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MUTABLE_DESCRIPTOR_TYPE_FEATURES_VALVE ),
            Field ( MutableDescriptorTypeCreateInfoValve,                                  VkStructureType :: VK_STRUCTURE_TYPE_MUTABLE_DESCRIPTOR_TYPE_CREATE_INFO_VALVE ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_INPUT_DYNAMIC_STATE_AVAILABLE

            Field ( PhysicalDeviceVertexInputDynamicStateFeatures,                         VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VERTEX_INPUT_DYNAMIC_STATE_FEATURES_EXT ),
            Field ( VertexInputBindingDescription,                                         VkStructureType :: VK_STRUCTURE_TYPE_VERTEX_INPUT_BINDING_DESCRIPTION_2_EXT ),
            Field ( VertexInputAttributeDescription,                                       VkStructureType :: VK_STRUCTURE_TYPE_VERTEX_INPUT_ATTRIBUTE_DESCRIPTION_2_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PHYSICAL_DEVICE_DRM_AVAILABLE

            Field ( PhysicalDeviceDRMProperties,                                           VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRM_PROPERTIES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_CONTROL_AVAILABLE

            Field ( PhysicalDeviceDepthClipControlFeatures,                                VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_CLIP_CONTROL_FEATURES_EXT ),
            Field ( PipelineViewportDepthClipControlCreateInfo,                            VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_DEPTH_CLIP_CONTROL_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIMITIVE_TOPOLOGY_LIST_RESTART_AVAILABLE

            Field ( PhysicalDevicePrimitiveTopologyListRestartFeatures,                    VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRIMITIVE_TOPOLOGY_LIST_RESTART_FEATURES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FORMAT_FEATURE_FLAGS_AVAILABLE && ! __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            Field ( FormatProperties3,                                                     VkStructureType :: VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_3_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_MEMORY_AVAILABLE

            Field ( ImportMemoryZirconHandleInfoGoogle,                                    VkStructureType :: VK_STRUCTURE_TYPE_IMPORT_MEMORY_ZIRCON_HANDLE_INFO_FUCHSIA ),
            Field ( MemoryZirconHandlePropertiesGoogle,                                    VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_ZIRCON_HANDLE_PROPERTIES_FUCHSIA ),
            Field ( GetZirconHandleInfo,                                                   VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_GET_ZIRCON_HANDLE_INFO_FUCHSIA ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_SEMAPHORE_AVAILABLE

            Field ( ImportSemaphoreZirconHandleInfoGoogle,                                 VkStructureType :: VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_ZIRCON_HANDLE_INFO_FUCHSIA ),
            Field ( GetZirconHandleInfoGoogle,                                             VkStructureType :: VK_STRUCTURE_TYPE_SEMAPHORE_GET_ZIRCON_HANDLE_INFO_FUCHSIA ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_BUFFER_COLLECTION_AVAILABLE

            Field ( BufferCollectionCreateInfoGoogle,                                      VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_COLLECTION_CREATE_INFO_FUCHSIA ),
            Field ( ImportMemoryBufferCollectionGoogle,                                    VkStructureType :: VK_STRUCTURE_TYPE_IMPORT_MEMORY_BUFFER_COLLECTION_FUCHSIA ),
            Field ( BufferCollectionImageCreateInfoGoogle,                                 VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_COLLECTION_IMAGE_CREATE_INFO_FUCHSIA ),
            Field ( BufferCollectionPropertiesGoogle,                                      VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_COLLECTION_PROPERTIES_FUCHSIA ),
            Field ( BufferConstraintsInfoGoogle,                                           VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_CONSTRAINTS_INFO_FUCHSIA ),
            Field ( BufferCollectionBufferCreateInfoGoogle,                                VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_COLLECTION_BUFFER_CREATE_INFO_FUCHSIA ),
            Field ( ImageConstraintsInfoGoogle,                                            VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_CONSTRAINTS_INFO_FUCHSIA ),
            Field ( ImageFormatConstraintsInfoGoogle,                                      VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_FORMAT_CONSTRAINTS_INFO_FUCHSIA ),
            Field ( SystemColorSpaceGoogle,                                                VkStructureType :: VK_STRUCTURE_TYPE_SYSMEM_COLOR_SPACE_FUCHSIA ),
            Field ( BufferCollectionConstraintsInfoGoogle,                                 VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_COLLECTION_CONSTRAINTS_INFO_FUCHSIA ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE

            Field ( SubpassShadingPipelineCreateInfoHuawei,                                VkStructureType :: VK_STRUCTURE_TYPE_SUBPASS_SHADING_PIPELINE_CREATE_INFO_HUAWEI ),
            Field ( PhysicalDeviceSubpassShadingFeaturesHuawei,                            VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBPASS_SHADING_FEATURES_HUAWEI ),
            Field ( PhysicalDeviceSubpassShadingPropertiesHuawei,                          VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBPASS_SHADING_PROPERTIES_HUAWEI ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_INVOCATION_MASK_AVAILABLE

            Field ( PhysicalDeviceInvocationMaskFeaturesHuawei,                            VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INVOCATION_MASK_FEATURES_HUAWEI ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_RDMA_AVAILABLE

            Field ( MemoryGetRemoteAddressInfoNVidia,                                      VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_GET_REMOTE_ADDRESS_INFO_NV ),
            Field ( PhysicalDeviceExternalMemoryRDMAFeaturesNVidia,                        VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_MEMORY_RDMA_FEATURES_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_2_AVAILABLE

            Field ( PhysicalDeviceExtendedDynamicState2Features,                           VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_DYNAMIC_STATE_2_FEATURES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLACKBERRY_QNX_SCREEN_SURFACE_AVAILABLE

            Field ( QnxScreenSurfaceCreateInfoBlackberry,                                  VkStructureType :: VK_STRUCTURE_TYPE_SCREEN_SURFACE_CREATE_INFO_QNX ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_COLOR_WRITE_ENABLE_AVAILABLE

            Field ( PhysicalDeviceColorWriteEnableFeatures,                                VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COLOR_WRITE_ENABLE_FEATURES_EXT ),
            Field ( PipelineColorWriteCreateInfo,                                          VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_COLOR_WRITE_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE

            Field ( PhysicalDeviceGlobalPriorityQueryFeatures,                             VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GLOBAL_PRIORITY_QUERY_FEATURES_EXT ),
            Field ( QueueFamilyGlobalPriorityProperties,                                   VkStructureType :: VK_STRUCTURE_TYPE_QUEUE_FAMILY_GLOBAL_PRIORITY_PROPERTIES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_VIEW_MIN_LOD_AVAILABLE

            Field ( PhysicalDeviceImageViewMinLODFeatures,                                 VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_VIEW_MIN_LOD_FEATURES_EXT ),
            Field ( ImageViewMinLODCreateInfo,                                             VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_VIEW_MIN_LOD_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE

            Field ( PhysicalDeviceMultiDrawFeatures,                                       VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTI_DRAW_FEATURES_EXT ),
            Field ( PhysicalDeviceMultiDrawProperties,                                     VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTI_DRAW_PROPERTIES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BORDER_COLOR_SWIZZLE_AVAILABLE

            Field ( PhysicalDeviceBorderColorSwizzleFeatures,                              VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BORDER_COLOR_SWIZZLE_FEATURES_EXT ),
            Field ( SamplerBorderColorComponentMappingCreateInfo,                          VkStructureType :: VK_STRUCTURE_TYPE_SAMPLER_BORDER_COLOR_COMPONENT_MAPPING_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PAGEABLE_DEVICE_LOCAL_MEMORY_AVAILABLE

            Field ( PhysicalDevicePageableDeviceLocalMemoryFeatures,                       VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PAGEABLE_DEVICE_LOCAL_MEMORY_FEATURES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE && ! __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            Field ( PhysicalDeviceMaintenance4Features,                                    VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_4_FEATURES_KHR ),
            Field ( PhysicalDeviceMaintenance4Properties,                                  VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_4_PROPERTIES_KHR ),
            Field ( PhysicalDeviceBufferMemoryRequirements,                                VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_BUFFER_MEMORY_REQUIREMENTS_KHR ),
            Field ( PhysicalDeviceImageMemoryRequirements,                                 VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_IMAGE_MEMORY_REQUIREMENTS_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE

            Field ( PhysicalDeviceFragmentDensityMapOffsetFeaturesQualcomm,                VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_OFFSET_FEATURES_QCOM ),
            Field ( PhysicalDeviceFragmentDensityMapOffsetPropertiesQualcomm,              VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_OFFSET_PROPERTIES_QCOM ),
            Field ( SubpassFragmentDensityMapOffsetEndInfoQualcomm,                        VkStructureType :: VK_STRUCTURE_TYPE_SUBPASS_FRAGMENT_DENSITY_MAP_OFFSET_END_INFO_QCOM ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_LINEAR_COLOR_ATTACHMENT_AVAILABLE

            Field ( PhysicalDeviceLinearColorAttachmentFeaturesNVidia,                     VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_LINEAR_COLOR_ATTACHMENT_FEATURES_NV ),

#endif

            Field ( Unknown,                                                               cds :: limits :: S32_MAX )

        };

#ifdef __C_ENG_REPLACED_MemoryBarrier
#undef __C_ENG_REPLACED_MemoryBarrier
#pragma pop_macro("MemoryBarrier")
#endif

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     ENUM ( PhysicalDeviceType,  TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Unknown,        VkPhysicalDeviceType :: VK_PHYSICAL_DEVICE_TYPE_OTHER ),
            Field ( IntegratedGPU,  VkPhysicalDeviceType :: VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU ),
            Field ( DedicatedGPU,   VkPhysicalDeviceType :: VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU ),
            Field ( VirtualGPU,     VkPhysicalDeviceType :: VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU ),
            Field ( CPU,            VkPhysicalDeviceType :: VK_PHYSICAL_DEVICE_TYPE_CPU )
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     ENUM ( VendorID,  TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( VIV,        VkVendorId :: VK_VENDOR_ID_VIV ),
            Field ( VSI,        VkVendorId :: VK_VENDOR_ID_VSI ),
            Field ( Kazan,      VkVendorId :: VK_VENDOR_ID_KAZAN ),
            Field ( Codeplay,   VkVendorId :: VK_VENDOR_ID_CODEPLAY ),
            Field ( Mesa,       VkVendorId :: VK_VENDOR_ID_MESA ),
            Field ( POCL,       VkVendorId :: VK_VENDOR_ID_POCL )
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     ENUM ( DebugMessageSeverityFlag,    TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Verbose,    VkDebugUtilsMessageSeverityFlagBitsEXT :: VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT ),
            Field ( Info,       VkDebugUtilsMessageSeverityFlagBitsEXT :: VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT ),
            Field ( Warning,    VkDebugUtilsMessageSeverityFlagBitsEXT :: VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT ),
            Field ( Error,      VkDebugUtilsMessageSeverityFlagBitsEXT :: VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT )
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     ENUM ( DebugMessageTypeFlag,    TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( General,        VkDebugUtilsMessageTypeFlagBitsEXT :: VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT ),
            Field ( Validation,     VkDebugUtilsMessageTypeFlagBitsEXT :: VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT ),
            Field ( Performance,    VkDebugUtilsMessageTypeFlagBitsEXT :: VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT ),
            Field ( MaxValue,       DebugMessageTypeFlagPerformance )
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_REPORT_AVAILABLE
#define C_ENG_MAP_START     ENUM ( DebugReportFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Information,        VkDebugReportFlagBitsEXT :: VK_DEBUG_REPORT_INFORMATION_BIT_EXT ),
            Field ( Warning,            VkDebugReportFlagBitsEXT :: VK_DEBUG_REPORT_WARNING_BIT_EXT ),
            Field ( PerformanceWarning, VkDebugReportFlagBitsEXT :: VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT ),
            Field ( Error,              VkDebugReportFlagBitsEXT :: VK_DEBUG_REPORT_ERROR_BIT_EXT ),
            Field ( Debug,              VkDebugReportFlagBitsEXT :: VK_DEBUG_REPORT_DEBUG_BIT_EXT ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START     ENUM ( ValidationFeatureEnable,    TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( GpuAssisted,                    VkValidationFeatureEnableEXT :: VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_EXT ),
            Field ( GpuAssistedReserveBindingSlot,  VkValidationFeatureEnableEXT :: VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_RESERVE_BINDING_SLOT_EXT ),
            Field ( BestPractices,                  VkValidationFeatureEnableEXT :: VK_VALIDATION_FEATURE_ENABLE_BEST_PRACTICES_EXT ),
            Field ( DebugPrintf,                    VkValidationFeatureEnableEXT :: VK_VALIDATION_FEATURE_ENABLE_DEBUG_PRINTF_EXT ),
            Field ( SynchronizationValidation,      VkValidationFeatureEnableEXT :: VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT )
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START     ENUM ( ValidationFeatureDisable,    TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( All,                    VkValidationFeatureDisableEXT :: VK_VALIDATION_FEATURE_DISABLE_ALL_EXT ),
            Field ( Shaders,                VkValidationFeatureDisableEXT :: VK_VALIDATION_FEATURE_DISABLE_SHADERS_EXT ),
            Field ( ThreadSafety,           VkValidationFeatureDisableEXT :: VK_VALIDATION_FEATURE_DISABLE_THREAD_SAFETY_EXT ),
            Field ( APIParameters,          VkValidationFeatureDisableEXT :: VK_VALIDATION_FEATURE_DISABLE_API_PARAMETERS_EXT ),
            Field ( ObjectLifetimes,        VkValidationFeatureDisableEXT :: VK_VALIDATION_FEATURE_DISABLE_OBJECT_LIFETIMES_EXT ),
            Field ( CoreChecks,             VkValidationFeatureDisableEXT :: VK_VALIDATION_FEATURE_DISABLE_CORE_CHECKS_EXT ),
            Field ( UniqueHandles,          VkValidationFeatureDisableEXT :: VK_VALIDATION_FEATURE_DISABLE_UNIQUE_HANDLES_EXT ),
            Field ( ShaderValidationCache,  VkValidationFeatureDisableEXT :: VK_VALIDATION_FEATURE_DISABLE_SHADER_VALIDATION_CACHE_EXT )
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START     ENUM ( SampleCountFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( 1Bit,   VkSampleCountFlagBits :: VK_SAMPLE_COUNT_1_BIT ),
            Field ( 2Bit,   VkSampleCountFlagBits :: VK_SAMPLE_COUNT_2_BIT ),
            Field ( 4Bit,   VkSampleCountFlagBits :: VK_SAMPLE_COUNT_4_BIT ),
            Field ( 8Bit,   VkSampleCountFlagBits :: VK_SAMPLE_COUNT_8_BIT ),
            Field ( 16Bit,  VkSampleCountFlagBits :: VK_SAMPLE_COUNT_16_BIT ),
            Field ( 32Bit,  VkSampleCountFlagBits :: VK_SAMPLE_COUNT_32_BIT ),
            Field ( 64Bit,  VkSampleCountFlagBits :: VK_SAMPLE_COUNT_64_BIT ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START     ENUM ( PointClippingBehavior, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( AllClipPlanes,      VkPointClippingBehavior :: VK_POINT_CLIPPING_BEHAVIOR_ALL_CLIP_PLANES ),
            Field ( UserClipPlanesOnly, VkPointClippingBehavior :: VK_POINT_CLIPPING_BEHAVIOR_USER_CLIP_PLANES_ONLY )
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START     ENUM ( ShaderStageFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE

            Field ( RayGeneration,          VkShaderStageFlagBits :: VK_SHADER_STAGE_RAYGEN_BIT_KHR ),
            Field ( RayAnyHit,              VkShaderStageFlagBits :: VK_SHADER_STAGE_ANY_HIT_BIT_KHR ),
            Field ( RayClosestHit,          VkShaderStageFlagBits :: VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR ),
            Field ( RayMiss,                VkShaderStageFlagBits :: VK_SHADER_STAGE_MISS_BIT_KHR ),
            Field ( RayIntersection,        VkShaderStageFlagBits :: VK_SHADER_STAGE_INTERSECTION_BIT_KHR ),
            Field ( RayCallable,            VkShaderStageFlagBits :: VK_SHADER_STAGE_CALLABLE_BIT_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE

            Field ( MeshTaskNVidia,         VkShaderStageFlagBits :: VK_SHADER_STAGE_TASK_BIT_NV ),
            Field ( MeshMeshNVidia,         VkShaderStageFlagBits :: VK_SHADER_STAGE_MESH_BIT_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE

            Field ( SubpassShadingHuawei,   VkShaderStageFlagBits :: VK_SHADER_STAGE_SUBPASS_SHADING_BIT_HUAWEI ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE

            Field ( RayGenerationNVidia,    ShaderStageFlagRayGeneration ),
            Field ( RayAnyHitNVidia,        ShaderStageFlagRayAnyHit ),
            Field ( RayClosestHitNVidia,    ShaderStageFlagRayClosestHit ),
            Field ( RayMissNVidia,          ShaderStageFlagRayMiss ),
            Field ( RayIntersectionNVidia,  ShaderStageFlagRayIntersection ),
            Field ( RayCallableNVidia,      ShaderStageFlagRayCallable ),

#endif

            Field ( Vertex,                 VkShaderStageFlagBits :: VK_SHADER_STAGE_VERTEX_BIT ),
            Field ( TessellationControl,    VkShaderStageFlagBits :: VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT ),
            Field ( TessellationEvaluation, VkShaderStageFlagBits :: VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT ),
            Field ( Geometry,               VkShaderStageFlagBits :: VK_SHADER_STAGE_GEOMETRY_BIT ),
            Field ( Fragment,               VkShaderStageFlagBits :: VK_SHADER_STAGE_FRAGMENT_BIT ),
            Field ( Compute,                VkShaderStageFlagBits :: VK_SHADER_STAGE_COMPUTE_BIT ),
            Field ( AllGraphics,            VkShaderStageFlagBits :: VK_SHADER_STAGE_ALL_GRAPHICS ),
            Field ( All,                    VkShaderStageFlagBits :: VK_SHADER_STAGE_ALL )
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START     ENUM ( DeviceQueueCreateFlag,   TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Protected,  VkDeviceQueueCreateFlagBits :: VK_DEVICE_QUEUE_CREATE_PROTECTED_BIT )
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

#define C_ENG_MAP_START     ENUM ( SubgroupFeatureFlag,     TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SUBGROUP_PARTITIONED_AVAILABLE

            Field ( PartitionedNVidia,  VkSubgroupFeatureFlagBits :: VK_SUBGROUP_FEATURE_PARTITIONED_BIT_NV ),

#endif

            Field ( Basic,              VkSubgroupFeatureFlagBits :: VK_SUBGROUP_FEATURE_BASIC_BIT ),
            Field ( Vote,               VkSubgroupFeatureFlagBits :: VK_SUBGROUP_FEATURE_VOTE_BIT ),
            Field ( Arithmetic,         VkSubgroupFeatureFlagBits :: VK_SUBGROUP_FEATURE_ARITHMETIC_BIT ),
            Field ( Shuffle,            VkSubgroupFeatureFlagBits :: VK_SUBGROUP_FEATURE_SHUFFLE_BIT ),
            Field ( ShuffleRelative,    VkSubgroupFeatureFlagBits :: VK_SUBGROUP_FEATURE_SHUFFLE_RELATIVE_BIT ),
            Field ( Clustered,          VkSubgroupFeatureFlagBits :: VK_SUBGROUP_FEATURE_CLUSTERED_BIT ),
            Field ( Quad,               VkSubgroupFeatureFlagBits :: VK_SUBGROUP_FEATURE_QUAD_BIT )
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

#define C_ENG_MAP_START     ENUM ( DriverID,    TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( AMDProprietary,                 VkDriverId :: VK_DRIVER_ID_AMD_PROPRIETARY ),
            Field ( AMDOpenSource,                  VkDriverId :: VK_DRIVER_ID_AMD_OPEN_SOURCE ),
            Field ( MesaRadV,                       VkDriverId :: VK_DRIVER_ID_MESA_RADV ),
            Field ( NVidiaProprietary,              VkDriverId :: VK_DRIVER_ID_NVIDIA_PROPRIETARY ),
            Field ( InterProprietaryWindows,        VkDriverId :: VK_DRIVER_ID_INTEL_PROPRIETARY_WINDOWS ),
            Field ( IntelOpenSourceMesa,            VkDriverId :: VK_DRIVER_ID_INTEL_OPEN_SOURCE_MESA ),
            Field ( ImaginationProprietary,         VkDriverId :: VK_DRIVER_ID_IMAGINATION_PROPRIETARY ),
            Field ( QualcommProprietary,            VkDriverId :: VK_DRIVER_ID_QUALCOMM_PROPRIETARY ),
            Field ( ARMProprietary,                 VkDriverId :: VK_DRIVER_ID_ARM_PROPRIETARY ),
            Field ( GoogleSwiftshader,              VkDriverId :: VK_DRIVER_ID_GOOGLE_SWIFTSHADER ),
            Field ( GoogleGamesPlatformProprietary, VkDriverId :: VK_DRIVER_ID_GGP_PROPRIETARY ),
            Field ( BroadcomProprietary,            VkDriverId :: VK_DRIVER_ID_BROADCOM_PROPRIETARY ),
            Field ( MesaLLVMPipe,                   VkDriverId :: VK_DRIVER_ID_MESA_LLVMPIPE ),
            Field ( MoltenVulkan,                   VkDriverId :: VK_DRIVER_ID_MOLTENVK ),
            Field ( CoreAVIProprietary,             VkDriverId :: VK_DRIVER_ID_COREAVI_PROPRIETARY ),
            Field ( JuiceProprietary,               VkDriverId :: VK_DRIVER_ID_JUICE_PROPRIETARY ),
            Field ( VeriSiliconProprietary,         VkDriverId :: VK_DRIVER_ID_VERISILICON_PROPRIETARY )
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     ENUM ( ShaderFloatControlsIndependence, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( 32BitOnly,  VkShaderFloatControlsIndependence :: VK_SHADER_FLOAT_CONTROLS_INDEPENDENCE_32_BIT_ONLY ),
            Field ( All,        VkShaderFloatControlsIndependence :: VK_SHADER_FLOAT_CONTROLS_INDEPENDENCE_ALL ),
            Field ( None,       VkShaderFloatControlsIndependence :: VK_SHADER_FLOAT_CONTROLS_INDEPENDENCE_NONE )
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     ENUM ( ResolveModeFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( None,       VkResolveModeFlagBits :: VK_RESOLVE_MODE_NONE ),
            Field ( SampleZero, VkResolveModeFlagBits :: VK_RESOLVE_MODE_SAMPLE_ZERO_BIT ),
            Field ( Average,    VkResolveModeFlagBits :: VK_RESOLVE_MODE_AVERAGE_BIT ),
            Field ( Min,        VkResolveModeFlagBits :: VK_RESOLVE_MODE_MIN_BIT ),
            Field ( Max,        VkResolveModeFlagBits :: VK_RESOLVE_MODE_MAX_BIT )
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_2_AVAILABLE

#define C_ENG_MAP_START     ENUM ( ShaderCorePropertiesFlagAMD, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

#define C_ENG_MAP_START     ENUM ( ImageUsageFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( TransferSource,                 VkImageUsageFlagBits :: VK_IMAGE_USAGE_TRANSFER_SRC_BIT ),
            Field ( TransferDestination,            VkImageUsageFlagBits :: VK_IMAGE_USAGE_TRANSFER_DST_BIT ),
            Field ( Sampled,                        VkImageUsageFlagBits :: VK_IMAGE_USAGE_SAMPLED_BIT ),
            Field ( Storage,                        VkImageUsageFlagBits :: VK_IMAGE_USAGE_STORAGE_BIT ),
            Field ( ColorAttachment,                VkImageUsageFlagBits :: VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT ),
            Field ( DepthStencilAttachment,         VkImageUsageFlagBits :: VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT ),
            Field ( TransientAttachment,            VkImageUsageFlagBits :: VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT ),
            Field ( InputAttachment,                VkImageUsageFlagBits :: VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT ),

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_DECODE_QUEUE_AVAILABLE

            Field ( VideoDecodeDestination,         VkImageUsageFlagBits :: VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR ),
            Field ( VideoDecodeSource,              VkImageUsageFlagBits :: VK_IMAGE_USAGE_VIDEO_DECODE_SRC_BIT_KHR ),
            Field ( VideoDecodeDPB,                 VkImageUsageFlagBits :: VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

            Field ( FragmentDensityMap,             VkImageUsageFlagBits :: VK_IMAGE_USAGE_FRAGMENT_DENSITY_MAP_BIT_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE

            Field ( FragmentShadingRateAttachment,  VkImageUsageFlagBits :: VK_IMAGE_USAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR ),

#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_ENCODE_QUEUE_AVAILABLE

            Field ( VideoEncodeDestination,         VkImageUsageFlagBits :: VK_IMAGE_USAGE_VIDEO_ENCODE_DST_BIT_KHR ),
            Field ( VideoEncodeSource,              VkImageUsageFlagBits :: VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR ),
            Field ( VideoEncodeDPB,                 VkImageUsageFlagBits :: VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_BIT_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_INVOCATION_MASK_AVAILABLE

            Field ( InvocationMaskHuawei,           VkImageUsageFlagBits :: VK_IMAGE_USAGE_INVOCATION_MASK_BIT_HUAWEI ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE

            Field ( ShadingRateImageNVidia,         VkImageUsageFlagBits :: VK_IMAGE_USAGE_SHADING_RATE_IMAGE_BIT_NV ),

#endif

        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     ENUM ( Format, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Undefined,                                      VkFormat :: VK_FORMAT_UNDEFINED ),

            Field ( _R4_G4_UNorm_Pack8,                             VkFormat :: VK_FORMAT_R4G4_UNORM_PACK8 ),
            Field ( _R4_G4_B4_A4_UNorm_Pack16,                      VkFormat :: VK_FORMAT_R4G4B4A4_UNORM_PACK16 ),
            Field ( _B4_G4_R4_A4_UNorm_Pack16,                      VkFormat :: VK_FORMAT_B4G4R4A4_UNORM_PACK16 ),
            Field ( _R5_G6_B5_UNorm_Pack16,                         VkFormat :: VK_FORMAT_R5G6B5_UNORM_PACK16 ),
            Field ( _B5_G6_R5_UNorm_Pack16,                         VkFormat :: VK_FORMAT_B5G6R5_UNORM_PACK16 ),
            Field ( _R5_G5_B5_A1_UNorm_Pack16,                      VkFormat :: VK_FORMAT_R5G5B5A1_UNORM_PACK16 ),
            Field ( _B5_G5_R5_A1_UNorm_Pack16,                      VkFormat :: VK_FORMAT_B5G5R5A1_UNORM_PACK16 ),
            Field ( _A1_R5_G5_B5_UNorm_Pack16,                      VkFormat :: VK_FORMAT_A1R5G5B5_UNORM_PACK16 ),

            Field ( _R8_UNorm,                                      VkFormat :: VK_FORMAT_R8_UNORM ),
            Field ( _R8_SNorm,                                      VkFormat :: VK_FORMAT_R8_SNORM ),
            Field ( _R8_UScaled,                                    VkFormat :: VK_FORMAT_R8_USCALED ),
            Field ( _R8_SScaled,                                    VkFormat :: VK_FORMAT_R8_SSCALED ),
            Field ( _R8_UInt,                                       VkFormat :: VK_FORMAT_R8_UINT ),
            Field ( _R8_SInt,                                       VkFormat :: VK_FORMAT_R8_SINT ),
            Field ( _R8_SRGB,                                       VkFormat :: VK_FORMAT_R8_SRGB ),

            Field ( _R8_G8_UNorm,                                   VkFormat :: VK_FORMAT_R8G8_UNORM ),
            Field ( _R8_G8_SNorm,                                   VkFormat :: VK_FORMAT_R8G8_SNORM ),
            Field ( _R8_G8_UScaled,                                 VkFormat :: VK_FORMAT_R8G8_USCALED ),
            Field ( _R8_G8_SScaled,                                 VkFormat :: VK_FORMAT_R8G8_SSCALED ),
            Field ( _R8_G8_UInt,                                    VkFormat :: VK_FORMAT_R8G8_UINT ),
            Field ( _R8_G8_SInt,                                    VkFormat :: VK_FORMAT_R8G8_SINT ),
            Field ( _R8_G8_SRGB,                                    VkFormat :: VK_FORMAT_R8G8_SRGB ),

            Field ( _R8_G8_B8_UNorm,                                VkFormat :: VK_FORMAT_R8G8B8_UNORM ),
            Field ( _R8_G8_B8_SNorm,                                VkFormat :: VK_FORMAT_R8G8B8_SNORM ),
            Field ( _R8_G8_B8_UScaled,                              VkFormat :: VK_FORMAT_R8G8B8_USCALED ),
            Field ( _R8_G8_B8_SScaled,                              VkFormat :: VK_FORMAT_R8G8B8_SSCALED ),
            Field ( _R8_G8_B8_UInt,                                 VkFormat :: VK_FORMAT_R8G8B8_UINT ),
            Field ( _R8_G8_B8_SInt,                                 VkFormat :: VK_FORMAT_R8G8B8_SINT ),
            Field ( _R8_G8_B8_SRGB,                                 VkFormat :: VK_FORMAT_R8G8B8_SRGB ),

            Field ( _B8_G8_R8_UNorm,                                VkFormat :: VK_FORMAT_B8G8R8_UNORM ),
            Field ( _B8_G8_R8_SNorm,                                VkFormat :: VK_FORMAT_B8G8R8_SNORM ),
            Field ( _B8_G8_R8_UScaled,                              VkFormat :: VK_FORMAT_B8G8R8_USCALED ),
            Field ( _B8_G8_R8_SScaled,                              VkFormat :: VK_FORMAT_B8G8R8_SSCALED ),
            Field ( _B8_G8_R8_UInt,                                 VkFormat :: VK_FORMAT_B8G8R8_UINT ),
            Field ( _B8_G8_R8_SInt,                                 VkFormat :: VK_FORMAT_B8G8R8_SINT ),
            Field ( _B8_G8_R8_SRGB,                                 VkFormat :: VK_FORMAT_B8G8R8_SRGB ),

            Field ( _R8_G8_B8_A8_UNorm,                             VkFormat :: VK_FORMAT_R8G8B8A8_UNORM ),
            Field ( _R8_G8_B8_A8_SNorm,                             VkFormat :: VK_FORMAT_R8G8B8A8_SNORM ),
            Field ( _R8_G8_B8_A8_UScaled,                           VkFormat :: VK_FORMAT_R8G8B8A8_USCALED ),
            Field ( _R8_G8_B8_A8_SScaled,                           VkFormat :: VK_FORMAT_R8G8B8A8_SSCALED ),
            Field ( _R8_G8_B8_A8_UInt,                              VkFormat :: VK_FORMAT_R8G8B8A8_UINT ),
            Field ( _R8_G8_B8_A8_SInt,                              VkFormat :: VK_FORMAT_R8G8B8A8_SINT ),
            Field ( _R8_G8_B8_A8_SRGB,                              VkFormat :: VK_FORMAT_R8G8B8A8_SRGB ),

            Field ( _B8_G8_R8_A8_UNorm,                             VkFormat :: VK_FORMAT_B8G8R8A8_UNORM ),
            Field ( _B8_G8_R8_A8_SNorm,                             VkFormat :: VK_FORMAT_B8G8R8A8_SNORM ),
            Field ( _B8_G8_R8_A8_UScaled,                           VkFormat :: VK_FORMAT_B8G8R8A8_USCALED ),
            Field ( _B8_G8_R8_A8_SScaled,                           VkFormat :: VK_FORMAT_B8G8R8A8_SSCALED ),
            Field ( _B8_G8_R8_A8_UInt,                              VkFormat :: VK_FORMAT_B8G8R8A8_UINT ),
            Field ( _B8_G8_R8_A8_SInt,                              VkFormat :: VK_FORMAT_B8G8R8A8_SINT ),
            Field ( _B8_G8_R8_A8_SRGB,                              VkFormat :: VK_FORMAT_B8G8R8A8_SRGB ),

            Field ( _A8_B8_G8_R8_UNorm_Pack32,                      VkFormat :: VK_FORMAT_A8B8G8R8_UNORM_PACK32 ),
            Field ( _A8_B8_G8_R8_SNorm_Pack32,                      VkFormat :: VK_FORMAT_A8B8G8R8_SNORM_PACK32 ),
            Field ( _A8_B8_G8_R8_UScaled_Pack32,                    VkFormat :: VK_FORMAT_A8B8G8R8_USCALED_PACK32 ),
            Field ( _A8_B8_G8_R8_SScaled_Pack32,                    VkFormat :: VK_FORMAT_A8B8G8R8_SSCALED_PACK32 ),
            Field ( _A8_B8_G8_R8_UInt_Pack32,                       VkFormat :: VK_FORMAT_A8B8G8R8_UINT_PACK32 ),
            Field ( _A8_B8_G8_R8_SInt_Pack32,                       VkFormat :: VK_FORMAT_A8B8G8R8_SINT_PACK32 ),
            Field ( _A8_B8_G8_R8_SRGB_Pack32,                       VkFormat :: VK_FORMAT_A8B8G8R8_SRGB_PACK32 ),

            Field ( _A2_R10_G10_B10_UNorm_Pack32,                   VkFormat :: VK_FORMAT_A2R10G10B10_UNORM_PACK32 ),
            Field ( _A2_R10_G10_B10_SNorm_Pack32,                   VkFormat :: VK_FORMAT_A2R10G10B10_SNORM_PACK32 ),
            Field ( _A2_R10_G10_B10_UScaled_Pack32,                 VkFormat :: VK_FORMAT_A2R10G10B10_USCALED_PACK32 ),
            Field ( _A2_R10_G10_B10_SScaled_Pack32,                 VkFormat :: VK_FORMAT_A2R10G10B10_SSCALED_PACK32 ),
            Field ( _A2_R10_G10_B10_UInt_Pack32,                    VkFormat :: VK_FORMAT_A2R10G10B10_UINT_PACK32 ),
            Field ( _A2_R10_G10_B10_SInt_Pack32,                    VkFormat :: VK_FORMAT_A2R10G10B10_SINT_PACK32 ),

            Field ( _A2_B10_G10_R10_UNorm_Pack32,                   VkFormat :: VK_FORMAT_A2B10G10R10_UNORM_PACK32 ),
            Field ( _A2_B10_G10_R10_SNorm_Pack32,                   VkFormat :: VK_FORMAT_A2B10G10R10_SNORM_PACK32 ),
            Field ( _A2_B10_G10_R10_UScaled_Pack32,                 VkFormat :: VK_FORMAT_A2B10G10R10_USCALED_PACK32 ),
            Field ( _A2_B10_G10_R10_SScaled_Pack32,                 VkFormat :: VK_FORMAT_A2B10G10R10_SSCALED_PACK32 ),
            Field ( _A2_B10_G10_R10_UInt_Pack32,                    VkFormat :: VK_FORMAT_A2B10G10R10_UINT_PACK32 ),
            Field ( _A2_B10_G10_R10_SInt_Pack32,                    VkFormat :: VK_FORMAT_A2B10G10R10_SINT_PACK32 ),

            Field ( _R16_UNorm,                                     VkFormat :: VK_FORMAT_R16_UNORM ),
            Field ( _R16_SNorm,                                     VkFormat :: VK_FORMAT_R16_SNORM ),
            Field ( _R16_UScaled,                                   VkFormat :: VK_FORMAT_R16_USCALED ),
            Field ( _R16_SScaled,                                   VkFormat :: VK_FORMAT_R16_SSCALED ),
            Field ( _R16_UInt,                                      VkFormat :: VK_FORMAT_R16_UINT ),
            Field ( _R16_SInt,                                      VkFormat :: VK_FORMAT_R16_SINT ),
            Field ( _R16_SFloat,                                    VkFormat :: VK_FORMAT_R16_SFLOAT ),

            Field ( _R16_G16_UNorm,                                 VkFormat :: VK_FORMAT_R16G16_UNORM ),
            Field ( _R16_G16_SNorm,                                 VkFormat :: VK_FORMAT_R16G16_SNORM ),
            Field ( _R16_G16_UScaled,                               VkFormat :: VK_FORMAT_R16G16_USCALED ),
            Field ( _R16_G16_SScaled,                               VkFormat :: VK_FORMAT_R16G16_SSCALED ),
            Field ( _R16_G16_UInt,                                  VkFormat :: VK_FORMAT_R16G16_UINT ),
            Field ( _R16_G16_SInt,                                  VkFormat :: VK_FORMAT_R16G16_SINT ),
            Field ( _R16_G16_SFloat,                                VkFormat :: VK_FORMAT_R16G16_SFLOAT ),

            Field ( _R16_G16_B16_UNorm,                             VkFormat :: VK_FORMAT_R16G16B16_UNORM ),
            Field ( _R16_G16_B16_SNorm,                             VkFormat :: VK_FORMAT_R16G16B16_SNORM ),
            Field ( _R16_G16_B16_UScaled,                           VkFormat :: VK_FORMAT_R16G16B16_USCALED ),
            Field ( _R16_G16_B16_SScaled,                           VkFormat :: VK_FORMAT_R16G16B16_SSCALED ),
            Field ( _R16_G16_B16_UInt,                              VkFormat :: VK_FORMAT_R16G16B16_UINT ),
            Field ( _R16_G16_B16_SInt,                              VkFormat :: VK_FORMAT_R16G16B16_SINT ),
            Field ( _R16_G16_B16_SFloat,                            VkFormat :: VK_FORMAT_R16G16B16_SFLOAT ),

            Field ( _R16_G16_B16_A16_UNorm,                         VkFormat :: VK_FORMAT_R16G16B16A16_UNORM ),
            Field ( _R16_G16_B16_A16_SNorm,                         VkFormat :: VK_FORMAT_R16G16B16A16_SNORM ),
            Field ( _R16_G16_B16_A16_UScaled,                       VkFormat :: VK_FORMAT_R16G16B16A16_USCALED ),
            Field ( _R16_G16_B16_A16_SScaled,                       VkFormat :: VK_FORMAT_R16G16B16A16_SSCALED ),
            Field ( _R16_G16_B16_A16_UInt,                          VkFormat :: VK_FORMAT_R16G16B16A16_UINT ),
            Field ( _R16_G16_B16_A16_SInt,                          VkFormat :: VK_FORMAT_R16G16B16A16_SINT ),
            Field ( _R16_G16_B16_A16_SFloat,                        VkFormat :: VK_FORMAT_R16G16B16A16_SFLOAT ),

            Field ( _R32_UInt,                                      VkFormat :: VK_FORMAT_R32_UINT ),
            Field ( _R32_SInt,                                      VkFormat :: VK_FORMAT_R32_SINT ),
            Field ( _R32_SFloat,                                    VkFormat :: VK_FORMAT_R32_SFLOAT ),

            Field ( _R32_G32_UInt,                                  VkFormat :: VK_FORMAT_R32G32_UINT ),
            Field ( _R32_G32_SInt,                                  VkFormat :: VK_FORMAT_R32G32_SINT ),
            Field ( _R32_G32_SFloat,                                VkFormat :: VK_FORMAT_R32G32_SFLOAT ),

            Field ( _R32_G32_B32_UInt,                              VkFormat :: VK_FORMAT_R32G32B32_UINT ),
            Field ( _R32_G32_B32_SInt,                              VkFormat :: VK_FORMAT_R32G32B32_SINT ),
            Field ( _R32_G32_B32_SFloat,                            VkFormat :: VK_FORMAT_R32G32B32_SFLOAT ),

            Field ( _R32_G32_B32_A32_UInt,                          VkFormat :: VK_FORMAT_R32G32B32A32_UINT ),
            Field ( _R32_G32_B32_A32_SInt,                          VkFormat :: VK_FORMAT_R32G32B32A32_SINT ),
            Field ( _R32_G32_B32_A32_SFloat,                        VkFormat :: VK_FORMAT_R32G32B32A32_SFLOAT ),

            Field ( _R64_UInt,                                      VkFormat :: VK_FORMAT_R64_UINT ),
            Field ( _R64_SInt,                                      VkFormat :: VK_FORMAT_R64_SINT ),
            Field ( _R64_SFloat,                                    VkFormat :: VK_FORMAT_R64_SFLOAT ),

            Field ( _R64_G64_UInt,                                  VkFormat :: VK_FORMAT_R64G64_UINT ),
            Field ( _R64_G64_SInt,                                  VkFormat :: VK_FORMAT_R64G64_SINT ),
            Field ( _R64_G64_SFloat,                                VkFormat :: VK_FORMAT_R64G64_SFLOAT ),

            Field ( _R64_G64_B64_UInt,                              VkFormat :: VK_FORMAT_R64G64B64_UINT ),
            Field ( _R64_G64_B64_SInt,                              VkFormat :: VK_FORMAT_R64G64B64_SINT ),
            Field ( _R64_G64_B64_SFloat,                            VkFormat :: VK_FORMAT_R64G64B64_SFLOAT ),

            Field ( _R64_G64_B64_A64_UInt,                          VkFormat :: VK_FORMAT_R64G64B64A64_UINT ),
            Field ( _R64_G64_B64_A64_SInt,                          VkFormat :: VK_FORMAT_R64G64B64A64_SINT ),
            Field ( _R64_G64_B64_A64_SFloat,                        VkFormat :: VK_FORMAT_R64G64B64A64_SFLOAT ),

            Field ( _B10_G11_R11_UFloat_Pack32,                     VkFormat :: VK_FORMAT_B10G11R11_UFLOAT_PACK32 ),
            Field ( _E5_B9_G9_R9_UFloat_Pack32,                     VkFormat :: VK_FORMAT_E5B9G9R9_UFLOAT_PACK32 ),

            Field ( _D16_UNorm,                                     VkFormat :: VK_FORMAT_D16_UNORM ),
            Field ( _X8_D24_UNorm_Pack32,                           VkFormat :: VK_FORMAT_X8_D24_UNORM_PACK32 ),
            Field ( _D32_SFloat,                                    VkFormat :: VK_FORMAT_D32_SFLOAT ),
            Field ( _S8_UInt,                                       VkFormat :: VK_FORMAT_S8_UINT ),

            Field ( _D16_UNorm_S8_UInt,                             VkFormat :: VK_FORMAT_D16_UNORM_S8_UINT ),
            Field ( _D24_UNorm_S8_UInt,                             VkFormat :: VK_FORMAT_D24_UNORM_S8_UINT ),
            Field ( _D32_SFloat_S8_UInt,                            VkFormat :: VK_FORMAT_D32_SFLOAT_S8_UINT ),

            Field ( _BC1_RGB_UNorm_Block,                           VkFormat :: VK_FORMAT_BC1_RGB_UNORM_BLOCK ),
            Field ( _BC1_RGB_SRGB_Block,                            VkFormat :: VK_FORMAT_BC1_RGB_SRGB_BLOCK ),
            Field ( _BC1_RGBA_UNorm_Block,                          VkFormat :: VK_FORMAT_BC1_RGBA_UNORM_BLOCK ),
            Field ( _BC1_RGBA_SRGB_Block,                           VkFormat :: VK_FORMAT_BC1_RGBA_SRGB_BLOCK ),

            Field ( _BC2_UNorm_Block,                               VkFormat :: VK_FORMAT_BC2_UNORM_BLOCK ),
            Field ( _BC2_SRGB_Block,                                VkFormat :: VK_FORMAT_BC2_SRGB_BLOCK ),

            Field ( _BC3_UNorm_Block,                               VkFormat :: VK_FORMAT_BC3_UNORM_BLOCK ),
            Field ( _BC3_SRGB_Block,                                VkFormat :: VK_FORMAT_BC3_SRGB_BLOCK ),

            Field ( _BC4_UNorm_Block,                               VkFormat :: VK_FORMAT_BC4_UNORM_BLOCK ),
            Field ( _BC4_SNorm_Block,                               VkFormat :: VK_FORMAT_BC4_SNORM_BLOCK ),

            Field ( _BC5_UNorm_Block,                               VkFormat :: VK_FORMAT_BC5_UNORM_BLOCK ),
            Field ( _BC5_SNorm_Block,                               VkFormat :: VK_FORMAT_BC5_SNORM_BLOCK ),

            Field ( _BC6H_UFloat_Block,                             VkFormat :: VK_FORMAT_BC6H_UFLOAT_BLOCK ),
            Field ( _BC6H_SFloat_Block,                             VkFormat :: VK_FORMAT_BC6H_SFLOAT_BLOCK ),

            Field ( _BC7_UNorm_Block,                               VkFormat :: VK_FORMAT_BC7_UNORM_BLOCK ),
            Field ( _BC7_SRGB_Block,                                VkFormat :: VK_FORMAT_BC7_SRGB_BLOCK ),

            Field ( _ETC2_R8_G8_B8_UNorm_Block,                     VkFormat :: VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK ),
            Field ( _ETC2_R8_G8_B8_SRGB_Block,                      VkFormat :: VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK ),
            Field ( _ETC2_R8_G8_B8_A1_UNorm_Block,                  VkFormat :: VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK ),
            Field ( _ETC2_R8_G8_B8_A1_SRGB_Block,                   VkFormat :: VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK ),
            Field ( _ETC2_R8_G8_B8_A8_UNorm_Block,                  VkFormat :: VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK ),
            Field ( _ETC2_R8_G8_B8_A8_SRGB_Block,                   VkFormat :: VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK ),

            Field ( _EAC_R11_UNorm_Block,                           VkFormat :: VK_FORMAT_EAC_R11_UNORM_BLOCK ),
            Field ( _EAC_R11_SNorm_Block,                           VkFormat :: VK_FORMAT_EAC_R11_SNORM_BLOCK ),
            Field ( _EAC_R11_G11_UNorm_Block,                       VkFormat :: VK_FORMAT_EAC_R11G11_UNORM_BLOCK ),
            Field ( _EAC_R11_G11_SNorm_Block,                       VkFormat :: VK_FORMAT_EAC_R11G11_SNORM_BLOCK ),

            Field ( _ASTC_4x4_UNorm_Block,                          VkFormat :: VK_FORMAT_ASTC_4x4_UNORM_BLOCK ),
            Field ( _ASTC_4x4_SRGB_Block,                           VkFormat :: VK_FORMAT_ASTC_4x4_SRGB_BLOCK ),

            Field ( _ASTC_5x4_UNorm_Block,                          VkFormat :: VK_FORMAT_ASTC_5x4_UNORM_BLOCK ),
            Field ( _ASTC_5x4_SRGB_Block,                           VkFormat :: VK_FORMAT_ASTC_5x4_SRGB_BLOCK ),
            Field ( _ASTC_5x5_UNorm_Block,                          VkFormat :: VK_FORMAT_ASTC_5x5_UNORM_BLOCK ),
            Field ( _ASTC_5x5_SRGB_Block,                           VkFormat :: VK_FORMAT_ASTC_5x5_SRGB_BLOCK ),

            Field ( _ASTC_6x5_UNorm_Block,                          VkFormat :: VK_FORMAT_ASTC_6x5_UNORM_BLOCK ),
            Field ( _ASTC_6x5_SRGB_Block,                           VkFormat :: VK_FORMAT_ASTC_6x5_SRGB_BLOCK ),
            Field ( _ASTC_6x6_UNorm_Block,                          VkFormat :: VK_FORMAT_ASTC_6x6_UNORM_BLOCK ),
            Field ( _ASTC_6x6_SRGB_Block,                           VkFormat :: VK_FORMAT_ASTC_6x6_SRGB_BLOCK ),

            Field ( _ASTC_8x5_UNorm_Block,                          VkFormat :: VK_FORMAT_ASTC_8x5_UNORM_BLOCK ),
            Field ( _ASTC_8x5_SRGB_Block,                           VkFormat :: VK_FORMAT_ASTC_8x5_SRGB_BLOCK ),
            Field ( _ASTC_8x6_UNorm_Block,                          VkFormat :: VK_FORMAT_ASTC_8x6_UNORM_BLOCK ),
            Field ( _ASTC_8x6_SRGB_Block,                           VkFormat :: VK_FORMAT_ASTC_8x6_SRGB_BLOCK ),
            Field ( _ASTC_8x8_UNorm_Block,                          VkFormat :: VK_FORMAT_ASTC_8x8_UNORM_BLOCK ),
            Field ( _ASTC_8x8_SRGB_Block,                           VkFormat :: VK_FORMAT_ASTC_8x8_SRGB_BLOCK ),

            Field ( _ASTC_10x5_UNorm_Block,                         VkFormat :: VK_FORMAT_ASTC_10x5_UNORM_BLOCK ),
            Field ( _ASTC_10x5_SRGB_Block,                          VkFormat :: VK_FORMAT_ASTC_10x5_SRGB_BLOCK ),
            Field ( _ASTC_10x6_UNorm_Block,                         VkFormat :: VK_FORMAT_ASTC_10x6_UNORM_BLOCK ),
            Field ( _ASTC_10x6_SRGB_Block,                          VkFormat :: VK_FORMAT_ASTC_10x6_SRGB_BLOCK ),
            Field ( _ASTC_10x8_UNorm_Block,                         VkFormat :: VK_FORMAT_ASTC_10x8_UNORM_BLOCK ),
            Field ( _ASTC_10x8_SRGB_Block,                          VkFormat :: VK_FORMAT_ASTC_10x8_SRGB_BLOCK ),
            Field ( _ASTC_10x10_UNorm_Block,                        VkFormat :: VK_FORMAT_ASTC_10x10_UNORM_BLOCK ),
            Field ( _ASTC_10x10_SRGB_Block,                         VkFormat :: VK_FORMAT_ASTC_10x10_SRGB_BLOCK ),

            Field ( _ASTC_12x10_UNorm_Block,                        VkFormat :: VK_FORMAT_ASTC_12x10_UNORM_BLOCK ),
            Field ( _ASTC_12x10_SRGB_Block,                         VkFormat :: VK_FORMAT_ASTC_12x10_SRGB_BLOCK ),
            Field ( _ASTC_12x12_UNorm_Block,                        VkFormat :: VK_FORMAT_ASTC_12x12_UNORM_BLOCK ),
            Field ( _ASTC_12x12_SRGB_Block,                         VkFormat :: VK_FORMAT_ASTC_12x12_SRGB_BLOCK ),

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

            Field ( _G8_B8_G8_R8_422_UNorm,                         VkFormat :: VK_FORMAT_G8B8G8R8_422_UNORM ),
            Field ( _B8_G8_R8_G8_G22_UNorm,                         VkFormat :: VK_FORMAT_B8G8R8G8_422_UNORM ),

            Field ( _G8_B8_R8_3Plane_420_UNorm,                     VkFormat :: VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM ),
            Field ( _G8_B8R8_2Plane_420_UNorm,                      VkFormat :: VK_FORMAT_G8_B8R8_2PLANE_420_UNORM ),

            Field ( _G8_B8_R8_3Plane_422_UNorm,                     VkFormat :: VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM ),
            Field ( _G8_B8R8_2Plane_422_UNorm,                      VkFormat :: VK_FORMAT_G8_B8R8_2PLANE_422_UNORM ),

            Field ( _G8_B8_R8_3Plane_444_UNorm,                     VkFormat :: VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM ),

            Field ( _R10x6_UNorm_Pack16,                            VkFormat :: VK_FORMAT_R10X6_UNORM_PACK16 ),
            Field ( _R10x6_G10x6_Unorm_2Pack16,                     VkFormat :: VK_FORMAT_R10X6G10X6_UNORM_2PACK16 ),
            Field ( _R10x6_G10x6_B10x6_A10x6_UNorm_4Pack16,         VkFormat :: VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16 ),

            Field ( _G10x6_B10x6_G10x6_R10x6_422_UNorm_4Pack16,     VkFormat :: VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16 ),
            Field ( _B10x6_G10x6_R10x6_G10x6_422_UNorm_4Pack16,     VkFormat :: VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16 ),

            Field ( _G10x6_B10x6_R10x6_3Plane_420_UNorm_3Pack16,    VkFormat :: VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16 ),
            Field ( _G10x6_B10x6R10x6_2Plane_420_UNorm_3Pack16,     VkFormat :: VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16 ),

            Field ( _G10x6_B10x6_R10x6_3Plane_422_UNorm_3Pack16,    VkFormat :: VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16 ),
            Field ( _G10x6_B10x6R10x6_2Plane_422_UNorm_3Pack16,     VkFormat :: VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16 ),

            Field ( _G10x6_B10x6_R10x6_3Plane_444_UNorm_3Pack16,    VkFormat :: VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16 ),

            Field ( _R12x4_UNorm_Pack16,                            VkFormat :: VK_FORMAT_R12X4_UNORM_PACK16 ),
            Field ( _R12x4_G12x4_UNorm_2Pack16,                     VkFormat :: VK_FORMAT_R12X4G12X4_UNORM_2PACK16 ),
            Field ( _R12x4_G12x4_B12x4_A12x4_UNorm_4Pack16,         VkFormat :: VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16 ),

            Field ( _G12x4_B12x4_G12x4_R12x4_422_UNorm_4Pack16,     VkFormat :: VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16 ),
            Field ( _B12x4_G12x4_R12x4_G12x4_422_UNorm_4Pack16,     VkFormat :: VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16 ),

            Field ( _G12x4_B12x4_R12x4_3Plane_420_UNorm_3Pack16,    VkFormat :: VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16 ),
            Field ( _G12x4_B12x4R12x4_2Plane_420_UNorm_3Pack16,     VkFormat :: VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16 ),

            Field ( _G12x4_B12x4_R12x4_3Plane_422_UNorm_3Pack16,    VkFormat :: VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16 ),
            Field ( _G12x4_B12x4R12x4_2Plane_422_UNorm_3Pack16,     VkFormat :: VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16 ),

            Field ( _G12x4_B12x4_R12x4_3Plane_444_UNorm_3Pack16,    VkFormat :: VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16 ),

            Field ( _G16_B16_G16_R16_422_UNorm,                     VkFormat :: VK_FORMAT_G16B16G16R16_422_UNORM ),
            Field ( _B16_G16_R16_G16_422_UNorm,                     VkFormat :: VK_FORMAT_B16G16R16G16_422_UNORM ),
            Field ( _G16_B16_R16_3Plane_420_UNorm,                  VkFormat :: VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM ),
            Field ( _G16_B16R16_2Plane_420_UNorm,                   VkFormat :: VK_FORMAT_G16_B16R16_2PLANE_420_UNORM ),
            Field ( _G16_B16_R16_3Plane_422_UNorm,                  VkFormat :: VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM ),
            Field ( _G16_B16R16_2Plane_422_UNorm,                   VkFormat :: VK_FORMAT_G16_B16R16_2PLANE_422_UNORM ),
            Field ( _G16_B16_R16_3Plane_444_UNorm,                  VkFormat :: VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_2_PLANE_444_FORMATS_AVAILABLE

            Field ( _G8_B8R8_2Plane_444_UNorm,                      VkFormat :: VK_FORMAT_G8_B8R8_2PLANE_444_UNORM_EXT ),
            Field ( _G10x6_B10x6R10x6_2Plane_444_UNorm_3Pack16,     VkFormat :: VK_FORMAT_G10X6_B10X6R10X6_2PLANE_444_UNORM_3PACK16_EXT ),
            Field ( _G12x4_B12x4R12x4_2Plane_444_UNorm_3Pack16,     VkFormat :: VK_FORMAT_G12X4_B12X4R12X4_2PLANE_444_UNORM_3PACK16_EXT ),
            Field ( _G16_B16R16_2Plane_444_UNorm,                   VkFormat :: VK_FORMAT_G16_B16R16_2PLANE_444_UNORM_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SAMPLER_YCBCR_CONVERSION_AVAILABLE

            Field ( _A4_R4_G4_B4_UNorm_Pack16,                      VkFormat :: VK_FORMAT_A4R4G4B4_UNORM_PACK16_EXT ),
            Field ( _A4_B4_G4_R4_UNorm_Pack16,                      VkFormat :: VK_FORMAT_A4B4G4R4_UNORM_PACK16_EXT ),

            Field ( _ASTC_4x4_SFloat_Block,                         VkFormat :: VK_FORMAT_ASTC_4x4_SFLOAT_BLOCK_EXT ),

            Field ( _ASTC_5x4_SFloat_Block,                         VkFormat :: VK_FORMAT_ASTC_5x4_SFLOAT_BLOCK_EXT ),
            Field ( _ASTC_5x5_SFloat_Block,                         VkFormat :: VK_FORMAT_ASTC_5x5_SFLOAT_BLOCK_EXT ),

            Field ( _ASTC_6x5_SFloat_Block,                         VkFormat :: VK_FORMAT_ASTC_6x5_SFLOAT_BLOCK_EXT ),
            Field ( _ASTC_6x6_SFloat_Block,                         VkFormat :: VK_FORMAT_ASTC_6x6_SFLOAT_BLOCK_EXT ),

            Field ( _ASTC_8x5_SFloat_Block,                         VkFormat :: VK_FORMAT_ASTC_8x5_SFLOAT_BLOCK_EXT ),
            Field ( _ASTC_8x6_SFloat_Block,                         VkFormat :: VK_FORMAT_ASTC_8x6_SFLOAT_BLOCK_EXT ),
            Field ( _ASTC_8x8_SFloat_Block,                         VkFormat :: VK_FORMAT_ASTC_8x8_SFLOAT_BLOCK_EXT ),

            Field ( _ASTC_10x5_SFloat_Block,                        VkFormat :: VK_FORMAT_ASTC_10x5_SFLOAT_BLOCK_EXT ),
            Field ( _ASTC_10x6_SFloat_Block,                        VkFormat :: VK_FORMAT_ASTC_10x6_SFLOAT_BLOCK_EXT ),
            Field ( _ASTC_10x8_SFloat_Block,                        VkFormat :: VK_FORMAT_ASTC_10x8_SFLOAT_BLOCK_EXT ),
            Field ( _ASTC_10x10_SFloat_Block,                       VkFormat :: VK_FORMAT_ASTC_10x10_SFLOAT_BLOCK_EXT ),

            Field ( _ASTC_12x10_SFloat_Block,                       VkFormat :: VK_FORMAT_ASTC_12x10_SFLOAT_BLOCK_EXT ),
            Field ( _ASTC_12x12_SFloat_Block,                       VkFormat :: VK_FORMAT_ASTC_12x12_SFLOAT_BLOCK_EXT ),

#endif

#if __C_ENG_VULKAN_API_POWER_VR_IMAGE_FORMAT_AVAILABLE

            Field ( _PVRTC1_2BPP_UNorm_Block_PowerVR,               VkFormat :: VK_FORMAT_PVRTC1_2BPP_UNORM_BLOCK_IMG ),
            Field ( _PVRTC1_4BPP_UNorm_Block_PowerVR,               VkFormat :: VK_FORMAT_PVRTC1_4BPP_UNORM_BLOCK_IMG ),
            Field ( _PVRTC2_2BPP_UNorm_Block_PowerVR,               VkFormat :: VK_FORMAT_PVRTC2_2BPP_UNORM_BLOCK_IMG ),
            Field ( _PVRTC2_4BPP_UNorm_Block_PowerVR,               VkFormat :: VK_FORMAT_PVRTC2_4BPP_UNORM_BLOCK_IMG ),

            Field ( _PVRTC1_2BPP_SRGB_Block_PowerVR,                VkFormat :: VK_FORMAT_PVRTC1_2BPP_SRGB_BLOCK_IMG ),
            Field ( _PVRTC1_4BPP_SRGB_Block_PowerVR,                VkFormat :: VK_FORMAT_PVRTC1_4BPP_SRGB_BLOCK_IMG ),
            Field ( _PVRTC2_2BPP_SRGB_Block_PowerVR,                VkFormat :: VK_FORMAT_PVRTC2_2BPP_SRGB_BLOCK_IMG ),
            Field ( _PVRTC2_4BPP_SRGB_Block_PowerVR,                VkFormat :: VK_FORMAT_PVRTC2_4BPP_SRGB_BLOCK_IMG ),

#endif

        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     ENUM ( ImageViewCreateFlag,   TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

            Field ( FragmentDensityMapDynamic,  VkImageViewCreateFlagBits :: VK_IMAGE_VIEW_CREATE_FRAGMENT_DENSITY_MAP_DYNAMIC_BIT_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE

            Field ( FragmentDensityMapDeferred, VkImageViewCreateFlagBits :: VK_IMAGE_VIEW_CREATE_FRAGMENT_DENSITY_MAP_DEFERRED_BIT_EXT ),

#endif

        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     ENUM ( ImageViewType,   TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( 1D,         VkImageViewType :: VK_IMAGE_VIEW_TYPE_1D ),
            Field ( 2D,         VkImageViewType :: VK_IMAGE_VIEW_TYPE_2D ),
            Field ( 3D,         VkImageViewType :: VK_IMAGE_VIEW_TYPE_3D ),
            Field ( Cube,       VkImageViewType :: VK_IMAGE_VIEW_TYPE_CUBE ),
            Field ( 1DArray,    VkImageViewType :: VK_IMAGE_VIEW_TYPE_1D_ARRAY ),
            Field ( 2DArray,    VkImageViewType :: VK_IMAGE_VIEW_TYPE_2D_ARRAY ),
            Field ( CubeArray,  VkImageViewType :: VK_IMAGE_VIEW_TYPE_CUBE_ARRAY ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     ENUM ( ComponentSwizzle,   TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Identity,   VkComponentSwizzle :: VK_COMPONENT_SWIZZLE_IDENTITY ),
            Field ( Zero,       VkComponentSwizzle :: VK_COMPONENT_SWIZZLE_ZERO ),
            Field ( One,        VkComponentSwizzle :: VK_COMPONENT_SWIZZLE_ONE ),
            Field ( R,          VkComponentSwizzle :: VK_COMPONENT_SWIZZLE_R ),
            Field ( G,          VkComponentSwizzle :: VK_COMPONENT_SWIZZLE_G ),
            Field ( B,          VkComponentSwizzle :: VK_COMPONENT_SWIZZLE_B ),
            Field ( A,          VkComponentSwizzle :: VK_COMPONENT_SWIZZLE_A ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     ENUM ( ImageAspectFlag,   TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Color,          VkImageAspectFlagBits :: VK_IMAGE_ASPECT_COLOR_BIT ),
            Field ( Depth,          VkImageAspectFlagBits :: VK_IMAGE_ASPECT_DEPTH_BIT ),
            Field ( Stencil,        VkImageAspectFlagBits :: VK_IMAGE_ASPECT_STENCIL_BIT ),
            Field ( Metadata,       VkImageAspectFlagBits :: VK_IMAGE_ASPECT_METADATA_BIT ),

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

            Field ( Plane0,         VkImageAspectFlagBits :: VK_IMAGE_ASPECT_PLANE_0_BIT ),
            Field ( Plane1,         VkImageAspectFlagBits :: VK_IMAGE_ASPECT_PLANE_1_BIT ),
            Field ( Plane2,         VkImageAspectFlagBits :: VK_IMAGE_ASPECT_PLANE_2_BIT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE

#if defined(__CDS_Platform_Microsoft_Windows)
            Field ( None,           0U ),
#else
            Field ( None,           VkImageAspectFlagBits :: VK_IMAGE_ASPECT_NONE_KHR ),
#endif

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_DRM_FORMAT_MODIFIER_AVAILABLE

            Field ( MemoryPlane0,   VkImageAspectFlagBits :: VK_IMAGE_ASPECT_MEMORY_PLANE_0_BIT_EXT ),
            Field ( MemoryPlane1,   VkImageAspectFlagBits :: VK_IMAGE_ASPECT_MEMORY_PLANE_1_BIT_EXT ),
            Field ( MemoryPlane2,   VkImageAspectFlagBits :: VK_IMAGE_ASPECT_MEMORY_PLANE_2_BIT_EXT ),
            Field ( MemoryPlane3,   VkImageAspectFlagBits :: VK_IMAGE_ASPECT_MEMORY_PLANE_3_BIT_EXT ),

#endif

        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

#define C_ENG_MAP_START     ENUM ( QueueFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Graphics,       VkQueueFlagBits :: VK_QUEUE_GRAPHICS_BIT ),
            Field ( Compute,        VkQueueFlagBits :: VK_QUEUE_COMPUTE_BIT ),
            Field ( Transfer,       VkQueueFlagBits :: VK_QUEUE_TRANSFER_BIT ),
            Field ( SparseBinding,  VkQueueFlagBits :: VK_QUEUE_SPARSE_BINDING_BIT ),
            Field ( Protected,      VkQueueFlagBits :: VK_QUEUE_PROTECTED_BIT ),
            Field ( Present,        0x00008000U ), // NOLINT(clion-misra-cpp2008-4-5-2)

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_DECODE_QUEUE_AVAILABLE

            Field ( VideoDecode,    VkQueueFlagBits :: VK_QUEUE_VIDEO_DECODE_BIT_KHR ),

#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_ENCODE_QUEUE_AVAILABLE

            Field ( VideoEncode,    VkQueueFlagBits :: VK_QUEUE_VIDEO_ENCODE_BIT_KHR )

#endif

        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     ENUM ( PipelineStageFlag, TYPE ( cds :: uint64 ) )
#include <ObjectMapping.hpp>

        Enum {

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE

            Field ( TransformFeedback,              VkPipelineStageFlagBits :: VK_PIPELINE_STAGE_TRANSFORM_FEEDBACK_BIT_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE

            Field ( ConditionalRendering,           VkPipelineStageFlagBits :: VK_PIPELINE_STAGE_CONDITIONAL_RENDERING_BIT_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE

            Field ( AccelerationStructureBuild,     VkPipelineStageFlagBits :: VK_PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE

            Field ( RayTracingShader,               VkPipelineStageFlagBits :: VK_PIPELINE_STAGE_RAY_TRACING_SHADER_BIT_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE

            Field ( TaskShaderNVidia,               VkPipelineStageFlagBits :: VK_PIPELINE_STAGE_TASK_SHADER_BIT_NV ),
            Field ( MeshShaderNVidia,               VkPipelineStageFlagBits :: VK_PIPELINE_STAGE_MESH_SHADER_BIT_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

            Field ( FragmentDensityProcess,         VkPipelineStageFlagBits :: VK_PIPELINE_STAGE_FRAGMENT_DENSITY_PROCESS_BIT_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE

            Field ( FragmentShadingRateAttachment,  VkPipelineStageFlagBits :: VK_PIPELINE_STAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE

            Field ( CommandPreprocessNVidia,        VkPipelineStageFlagBits :: VK_PIPELINE_STAGE_COMMAND_PREPROCESS_BIT_NV ),

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            Field ( None,                           VkPipelineStageFlagBits :: VK_PIPELINE_STAGE_NONE ),

#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE

            Field ( None,                           VkPipelineStageFlagBits :: VK_PIPELINE_STAGE_NONE_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE

            Field ( ShadingRateImageNVidia,         VkPipelineStageFlagBits :: VK_PIPELINE_STAGE_SHADING_RATE_IMAGE_BIT_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE

            Field ( RayTracingShaderNVidia,         VkPipelineStageFlagBits :: VK_PIPELINE_STAGE_RAY_TRACING_SHADER_BIT_NV ),

#endif

            Field ( TopOfPipe,                      VkPipelineStageFlagBits :: VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT ),
            Field ( DrawIndirect,                   VkPipelineStageFlagBits :: VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT ),
            Field ( VertexInput,                    VkPipelineStageFlagBits :: VK_PIPELINE_STAGE_VERTEX_INPUT_BIT ),
            Field ( VertexShader,                   VkPipelineStageFlagBits :: VK_PIPELINE_STAGE_VERTEX_SHADER_BIT ),
            Field ( TessellationControlShader,      VkPipelineStageFlagBits :: VK_PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER_BIT ),
            Field ( TessellationEvaluationShader,   VkPipelineStageFlagBits :: VK_PIPELINE_STAGE_TESSELLATION_EVALUATION_SHADER_BIT ),
            Field ( GeometryShader,                 VkPipelineStageFlagBits :: VK_PIPELINE_STAGE_GEOMETRY_SHADER_BIT ),
            Field ( FragmentShader,                 VkPipelineStageFlagBits :: VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT ),
            Field ( EarlyFragmentTests,             VkPipelineStageFlagBits :: VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT ),
            Field ( LateFragmentTests,              VkPipelineStageFlagBits :: VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT ),
            Field ( ColorAttachmentOutput,          VkPipelineStageFlagBits :: VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT ),
            Field ( ComputeShader,                  VkPipelineStageFlagBits :: VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT ),
            Field ( Transfer,                       VkPipelineStageFlagBits :: VK_PIPELINE_STAGE_TRANSFER_BIT ),
            Field ( BottomOfPipe,                   VkPipelineStageFlagBits :: VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT ),
            Field ( Host,                           VkPipelineStageFlagBits :: VK_PIPELINE_STAGE_HOST_BIT ),
            Field ( AllGraphics,                    VkPipelineStageFlagBits :: VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT ),
            Field ( AllCommands,                    VkPipelineStageFlagBits :: VK_PIPELINE_STAGE_ALL_COMMANDS_BIT ),

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            Field ( Copy,                           VK_PIPELINE_STAGE_2_COPY_BIT ),
            Field ( Resolve,                        VK_PIPELINE_STAGE_2_RESOLVE_BIT ),
            Field ( Blit,                           VK_PIPELINE_STAGE_2_BLIT_BIT ),
            Field ( Clear,                          VK_PIPELINE_STAGE_2_CLEAR_BIT ),
            Field ( IndexInput,                     VK_PIPELINE_STAGE_2_INDEX_INPUT_BIT ),
            Field ( VertexAttributeInput,           VK_PIPELINE_STAGE_2_VERTEX_ATTRIBUTE_INPUT_BIT ),
            Field ( PreRasterizationShaders,        VK_PIPELINE_STAGE_2_PRE_RASTERIZATION_SHADERS_BIT ),

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE

            Field ( SubpassShadingHuawei,           VK_PIPELINE_STAGE_2_SUBPASS_SHADING_BIT_HUAWEI ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_INVOCATION_MASK_AVAILABLE

            Field ( InvocationMaskHuawei,           VK_PIPELINE_STAGE_2_INVOCATION_MASK_BIT_HUAWEI ),

#endif

#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE

            Field ( Copy,                           VK_PIPELINE_STAGE_2_COPY_BIT_KHR ),
            Field ( Resolve,                        VK_PIPELINE_STAGE_2_RESOLVE_BIT_KHR ),
            Field ( Blit,                           VK_PIPELINE_STAGE_2_BLIT_BIT_KHR ),
            Field ( Clear,                          VK_PIPELINE_STAGE_2_CLEAR_BIT_KHR ),
            Field ( IndexInput,                     VK_PIPELINE_STAGE_2_INDEX_INPUT_BIT_KHR ),
            Field ( VertexAttributeInput,           VK_PIPELINE_STAGE_2_VERTEX_ATTRIBUTE_INPUT_BIT_KHR ),
            Field ( PreRasterizationShaders,        VK_PIPELINE_STAGE_2_PRE_RASTERIZATION_SHADERS_BIT_KHR ),

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE

            Field ( SubpassShadingHuawei,           VK_PIPELINE_STAGE_2_SUBPASS_SHADING_BIT_HUAWEI ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_INVOCATION_MASK_AVAILABLE

            Field ( InvocationMaskHuawei,           VK_PIPELINE_STAGE_2_INVOCATION_MASK_BIT_HUAWEI ),

#endif

#endif

        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     ENUM ( AccessFlag,  TYPE ( cds :: uint64 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( IndirectCommandRead,                VkAccessFlagBits :: VK_ACCESS_INDIRECT_COMMAND_READ_BIT ),
            Field ( IndexRead,                          VkAccessFlagBits :: VK_ACCESS_INDEX_READ_BIT ),
            Field ( VertexAttributeRead,                VkAccessFlagBits :: VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT ),
            Field ( UniformRead,                        VkAccessFlagBits :: VK_ACCESS_UNIFORM_READ_BIT ),
            Field ( InputAttachmentRead,                VkAccessFlagBits :: VK_ACCESS_INPUT_ATTACHMENT_READ_BIT ),
            Field ( ShaderRead,                         VkAccessFlagBits :: VK_ACCESS_SHADER_READ_BIT ),
            Field ( ShaderWrite,                        VkAccessFlagBits :: VK_ACCESS_SHADER_WRITE_BIT ),
            Field ( ColorAttachmentRead,                VkAccessFlagBits :: VK_ACCESS_COLOR_ATTACHMENT_READ_BIT ),
            Field ( ColorAttachmentWrite,               VkAccessFlagBits :: VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT ),
            Field ( DepthStencilAttachmentRead,         VkAccessFlagBits :: VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT ),
            Field ( DepthStencilAttachmentWrite,        VkAccessFlagBits :: VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT ),
            Field ( TransferRead,                       VkAccessFlagBits :: VK_ACCESS_TRANSFER_READ_BIT ),
            Field ( TransferWrite,                      VkAccessFlagBits :: VK_ACCESS_TRANSFER_WRITE_BIT ),
            Field ( HostRead,                           VkAccessFlagBits :: VK_ACCESS_HOST_READ_BIT ),
            Field ( HostWrite,                          VkAccessFlagBits :: VK_ACCESS_HOST_WRITE_BIT ),
            Field ( MemoryRead,                         VkAccessFlagBits :: VK_ACCESS_MEMORY_READ_BIT ),
            Field ( MemoryWrite,                        VkAccessFlagBits :: VK_ACCESS_MEMORY_WRITE_BIT ),

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            Field ( None,                               VkAccessFlagBits :: VK_ACCESS_NONE ),
            Field ( ShaderSampledRead,                  VK_ACCESS_2_SHADER_SAMPLED_READ_BIT ),
            Field ( ShaderStorageRead,                  VK_ACCESS_2_SHADER_STORAGE_READ_BIT ),
            Field ( ShaderStorageWrite,                 VK_ACCESS_2_SHADER_STORAGE_WRITE_BIT ),

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_DECODE_QUEUE_AVAILABLE

            Field ( VideoDecodeRead,                    VK_ACCESS_2_VIDEO_DECODE_READ_BIT_KHR ),
            Field ( VideoDecodeWrite,                   VK_ACCESS_2_VIDEO_DECODE_WRITE_BIT_KHR ),

#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_ENCODE_QUEUE_AVAILABLE

            Field ( VideoEncodeRead,                    VK_ACCESS_2_VIDEO_ENCODE_READ_BIT_KHR ),
            Field ( VideoEncodeWrite,                   VK_ACCESS_2_VIDEO_ENCODE_WRITE_BIT_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_INVOCATION_MASK_AVAILABLE

            Field ( InvocationMaskReadHuawei,           VK_ACCESS_2_INVOCATION_MASK_READ_BIT_HUAWEI ),

#endif

#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE

            Field ( None,                               VkAccessFlagBits :: VK_ACCESS_NONE_KHR ),
            Field ( ShaderSampledRead,                  VK_ACCESS_2_SHADER_SAMPLED_READ_BIT_KHR ),
            Field ( ShaderStorageRead,                  VK_ACCESS_2_SHADER_STORAGE_READ_BIT_KHR ),
            Field ( ShaderStorageWrite,                 VK_ACCESS_2_SHADER_STORAGE_WRITE_BIT_KHR ),

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_DECODE_QUEUE_AVAILABLE

            Field ( VideoDecodeRead,                    VK_ACCESS_2_VIDEO_DECODE_READ_BIT_KHR ),
            Field ( VideoDecodeWrite,                   VK_ACCESS_2_VIDEO_DECODE_WRITE_BIT_KHR ),

#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_ENCODE_QUEUE_AVAILABLE

            Field ( VideoEncodeRead,                    VK_ACCESS_2_VIDEO_ENCODE_READ_BIT_KHR ),
            Field ( VideoEncodeWrite,                   VK_ACCESS_2_VIDEO_ENCODE_WRITE_BIT_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_INVOCATION_MASK_AVAILABLE

            Field ( InvocationMaskReadHuawei,           VK_ACCESS_2_INVOCATION_MASK_READ_BIT_HUAWEI ),

#endif

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE

            Field ( TransformFeedbackWrite,             VkAccessFlagBits :: VK_ACCESS_TRANSFORM_FEEDBACK_WRITE_BIT_EXT ),
            Field ( TransformFeedbackCounterRead,       VkAccessFlagBits :: VK_ACCESS_TRANSFORM_FEEDBACK_COUNTER_READ_BIT_EXT ),
            Field ( TransformFeedbackCounterWrite,      VkAccessFlagBits :: VK_ACCESS_TRANSFORM_FEEDBACK_COUNTER_WRITE_BIT_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE

            Field ( ConditionalRenderingRead,           VkAccessFlagBits :: VK_ACCESS_CONDITIONAL_RENDERING_READ_BIT_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE

            Field ( ColorAttachmentReadNonCoherent,     VkAccessFlagBits :: VK_ACCESS_COLOR_ATTACHMENT_READ_NONCOHERENT_BIT_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE

            Field ( AccelerationStructureRead,          VkAccessFlagBits :: VK_ACCESS_ACCELERATION_STRUCTURE_READ_BIT_KHR ),
            Field ( AccelerationStructureWrite,         VkAccessFlagBits :: VK_ACCESS_ACCELERATION_STRUCTURE_WRITE_BIT_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

            Field ( FragmentDensityMapRead,             VkAccessFlagBits :: VK_ACCESS_FRAGMENT_DENSITY_MAP_READ_BIT_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE

            Field ( FragmentShadingRateAttachmentRead,  VkAccessFlagBits :: VK_ACCESS_FRAGMENT_SHADING_RATE_ATTACHMENT_READ_BIT_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE

            Field ( CommandPreprocessReadNVidia,        VkAccessFlagBits :: VK_ACCESS_COMMAND_PREPROCESS_READ_BIT_NV ),
            Field ( CommandPreprocessWriteNVidia,       VkAccessFlagBits :: VK_ACCESS_COMMAND_PREPROCESS_WRITE_BIT_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE

            Field ( ShadingRateImageReadNVidia,         VkAccessFlagBits :: VK_ACCESS_SHADING_RATE_IMAGE_READ_BIT_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE

            Field ( AccelerationStructureReadNVidia,    VkAccessFlagBits :: VK_ACCESS_ACCELERATION_STRUCTURE_READ_BIT_NV ),
            Field ( AccelerationStructureWriteNVidia,   VkAccessFlagBits :: VK_ACCESS_ACCELERATION_STRUCTURE_WRITE_BIT_NV ),

#endif

        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_AVAILABLE

#define C_ENG_MAP_START     ENUM ( QueueGlobalPriority, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Low,        VkQueueGlobalPriorityEXT :: VK_QUEUE_GLOBAL_PRIORITY_LOW_EXT ),
            Field ( Medium,     VkQueueGlobalPriorityEXT :: VK_QUEUE_GLOBAL_PRIORITY_MEDIUM_EXT ),
            Field ( High,       VkQueueGlobalPriorityEXT :: VK_QUEUE_GLOBAL_PRIORITY_HIGH_EXT ),
            Field ( Realtime,   VkQueueGlobalPriorityEXT :: VK_QUEUE_GLOBAL_PRIORITY_REALTIME_EXT )
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE

#define C_ENG_MAP_START     ENUM ( VideoCodecOperationFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED

            Field ( EncodeH264, VkVideoCodecOperationFlagBitsKHR :: VK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_EXT ),
            Field ( EncodeH265, VkVideoCodecOperationFlagBitsKHR :: VK_VIDEO_CODEC_OPERATION_ENCODE_H265_BIT_EXT ),
            Field ( DecodeH264, VkVideoCodecOperationFlagBitsKHR :: VK_VIDEO_CODEC_OPERATION_DECODE_H264_BIT_EXT ),
            Field ( DecodeH265, VkVideoCodecOperationFlagBitsKHR :: VK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_EXT ),

#endif

            Field ( Invalid,    VkVideoCodecOperationFlagBitsKHR :: VK_VIDEO_CODEC_OPERATION_INVALID_BIT_KHR )

        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

#define C_ENG_MAP_START     ENUM ( PerformanceCounterUnit,  TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Generic,            VkPerformanceCounterUnitKHR :: VK_PERFORMANCE_COUNTER_UNIT_GENERIC_KHR ),
            Field ( Percentage,         VkPerformanceCounterUnitKHR :: VK_PERFORMANCE_COUNTER_UNIT_PERCENTAGE_KHR ),
            Field ( Nanoseconds,        VkPerformanceCounterUnitKHR :: VK_PERFORMANCE_COUNTER_UNIT_NANOSECONDS_KHR ),
            Field ( Bytes,              VkPerformanceCounterUnitKHR :: VK_PERFORMANCE_COUNTER_UNIT_BYTES_KHR ),
            Field ( BytesPerSecond,     VkPerformanceCounterUnitKHR :: VK_PERFORMANCE_COUNTER_UNIT_BYTES_PER_SECOND_KHR ),
            Field ( Kelvin,             VkPerformanceCounterUnitKHR :: VK_PERFORMANCE_COUNTER_UNIT_KELVIN_KHR ),
            Field ( Watts,              VkPerformanceCounterUnitKHR :: VK_PERFORMANCE_COUNTER_UNIT_WATTS_KHR ),
            Field ( Volts,              VkPerformanceCounterUnitKHR :: VK_PERFORMANCE_COUNTER_UNIT_VOLTS_KHR ),
            Field ( Amps,               VkPerformanceCounterUnitKHR :: VK_PERFORMANCE_COUNTER_UNIT_AMPS_KHR ),
            Field ( Hertz,              VkPerformanceCounterUnitKHR :: VK_PERFORMANCE_COUNTER_UNIT_HERTZ_KHR ),
            Field ( Cycles,             VkPerformanceCounterUnitKHR :: VK_PERFORMANCE_COUNTER_UNIT_CYCLES_KHR )
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     ENUM ( PerformanceCounterScope, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( CommandBuffer,      VkPerformanceCounterScopeKHR :: VK_PERFORMANCE_COUNTER_SCOPE_COMMAND_BUFFER_KHR ),
            Field ( RenderPass,         VkPerformanceCounterScopeKHR :: VK_PERFORMANCE_COUNTER_SCOPE_RENDER_PASS_KHR ),
            Field ( Command,            VkPerformanceCounterScopeKHR :: VK_PERFORMANCE_COUNTER_SCOPE_COMMAND_KHR )
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     ENUM ( PerformanceCounterStorage,   TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Int32,      VkPerformanceCounterStorageKHR :: VK_PERFORMANCE_COUNTER_STORAGE_INT32_KHR ),
            Field ( Int64,      VkPerformanceCounterStorageKHR :: VK_PERFORMANCE_COUNTER_STORAGE_INT64_KHR ),
            Field ( UInt32,     VkPerformanceCounterStorageKHR :: VK_PERFORMANCE_COUNTER_STORAGE_UINT32_KHR ),
            Field ( UInt64,     VkPerformanceCounterStorageKHR :: VK_PERFORMANCE_COUNTER_STORAGE_UINT64_KHR ),
            Field ( Float32,    VkPerformanceCounterStorageKHR :: VK_PERFORMANCE_COUNTER_STORAGE_FLOAT32_KHR ),
            Field ( Float64,    VkPerformanceCounterStorageKHR :: VK_PERFORMANCE_COUNTER_STORAGE_FLOAT64_KHR )
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     ENUM ( PerformanceCounterDescriptionFlag,   TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( PerformanceImpacting,   VkPerformanceCounterDescriptionFlagBitsKHR :: VK_PERFORMANCE_COUNTER_DESCRIPTION_PERFORMANCE_IMPACTING_BIT_KHR ),
            Field ( ConcurrentlyImpacted,   VkPerformanceCounterDescriptionFlagBitsKHR :: VK_PERFORMANCE_COUNTER_DESCRIPTION_CONCURRENTLY_IMPACTED_BIT_KHR )
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

#define C_ENG_MAP_START     ENUM ( ObjectType, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

            Field ( SamplerYCBCRConversion,         VkObjectType :: VK_OBJECT_TYPE_SAMPLER_YCBCR_CONVERSION ),
            Field ( DescriptorUpdateTemplate,       VkObjectType :: VK_OBJECT_TYPE_DESCRIPTOR_UPDATE_TEMPLATE ),
            Field ( PrivateDataSlot,                VkObjectType :: VK_OBJECT_TYPE_PRIVATE_DATA_SLOT_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE

            Field ( Surface,                        VkObjectType :: VK_OBJECT_TYPE_SURFACE_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE

            Field ( Swapchain,                      VkObjectType :: VK_OBJECT_TYPE_SWAPCHAIN_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DISPLAY_AVAILABLE

            Field ( Display,                        VkObjectType :: VK_OBJECT_TYPE_DISPLAY_KHR ),
            Field ( DisplayMode,                    VkObjectType :: VK_OBJECT_TYPE_DISPLAY_MODE_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_REPORT_AVAILABLE

            Field ( DebugReportCallback,            VkObjectType :: VK_OBJECT_TYPE_DEBUG_REPORT_CALLBACK_EXT ),

#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE

            Field ( VideoSession,                   VkObjectType :: VK_OBJECT_TYPE_VIDEO_SESSION_KHR ),
            Field ( VideoSessionParameters,         VkObjectType :: VK_OBJECT_TYPE_VIDEO_SESSION_PARAMETERS_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_BINARY_IMPORT_AVAILABLE

            Field ( CUModuleNVidia,                 VkObjectType :: VK_OBJECT_TYPE_CU_MODULE_NVX ),
            Field ( CUFunctionNVidia,               VkObjectType :: VK_OBJECT_TYPE_CU_FUNCTION_NVX ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_UTILS_AVAILABLE

            Field ( DebugUtilsMessenger,            VkObjectType :: VK_OBJECT_TYPE_DEBUG_UTILS_MESSENGER_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE

            Field ( AccelerationStructure,          VkObjectType :: VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_CACHE_AVAILABLE

            Field ( ValidationCache,                VkObjectType :: VK_OBJECT_TYPE_VALIDATION_CACHE_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE

            Field ( AccelerationStructureNVidia,    VkObjectType :: VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE

            Field ( PerformanceConfigurationIntel,  VkObjectType :: VK_OBJECT_TYPE_PERFORMANCE_CONFIGURATION_INTEL ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DEFERRED_HOST_OPERATIONS_AVAILABLE

            Field ( DeferredOperation,              VkObjectType :: VK_OBJECT_TYPE_DEFERRED_OPERATION_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE

            Field ( IndirectCommandsLayoutNVidia,   VkObjectType :: VK_OBJECT_TYPE_INDIRECT_COMMANDS_LAYOUT_NV ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_BUFFER_COLLECTION_AVAILABLE

            Field ( BufferCollectionGoogle,         VkObjectType :: VK_OBJECT_TYPE_BUFFER_COLLECTION_FUCHSIA ),

#endif

            Field ( Unknown,                        VkObjectType :: VK_OBJECT_TYPE_UNKNOWN ),
            Field ( Instance,                       VkObjectType :: VK_OBJECT_TYPE_INSTANCE ),
            Field ( PhysicalDevice,                 VkObjectType :: VK_OBJECT_TYPE_PHYSICAL_DEVICE ),
            Field ( Device,                         VkObjectType :: VK_OBJECT_TYPE_DEVICE ),
            Field ( Queue,                          VkObjectType :: VK_OBJECT_TYPE_QUEUE ),
            Field ( Semaphore,                      VkObjectType :: VK_OBJECT_TYPE_SEMAPHORE ),
            Field ( CommandBuffer,                  VkObjectType :: VK_OBJECT_TYPE_COMMAND_BUFFER ),
            Field ( Fence,                          VkObjectType :: VK_OBJECT_TYPE_FENCE ),
            Field ( DeviceMemory,                   VkObjectType :: VK_OBJECT_TYPE_DEVICE_MEMORY ),
            Field ( Buffer,                         VkObjectType :: VK_OBJECT_TYPE_BUFFER ),
            Field ( Image,                          VkObjectType :: VK_OBJECT_TYPE_IMAGE ),
            Field ( Event,                          VkObjectType :: VK_OBJECT_TYPE_EVENT ),
            Field ( QueryPool,                      VkObjectType :: VK_OBJECT_TYPE_QUERY_POOL ),
            Field ( BufferView,                     VkObjectType :: VK_OBJECT_TYPE_BUFFER_VIEW ),
            Field ( ImageView,                      VkObjectType :: VK_OBJECT_TYPE_IMAGE_VIEW ),
            Field ( ShaderModule,                   VkObjectType :: VK_OBJECT_TYPE_SHADER_MODULE ),
            Field ( PipelineCache,                  VkObjectType :: VK_OBJECT_TYPE_PIPELINE_CACHE ),
            Field ( PipelineLayout,                 VkObjectType :: VK_OBJECT_TYPE_PIPELINE_LAYOUT ),
            Field ( RenderPass,                     VkObjectType :: VK_OBJECT_TYPE_RENDER_PASS ),
            Field ( Pipeline,                       VkObjectType :: VK_OBJECT_TYPE_PIPELINE ),
            Field ( DescriptorSetLayout,            VkObjectType :: VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT ),
            Field ( Sampler,                        VkObjectType :: VK_OBJECT_TYPE_SAMPLER ),
            Field ( DescriptorPool,                 VkObjectType :: VK_OBJECT_TYPE_DESCRIPTOR_POOL ),
            Field ( DescriptorSet,                  VkObjectType :: VK_OBJECT_TYPE_DESCRIPTOR_SET ),
            Field ( FrameBuffer,                    VkObjectType :: VK_OBJECT_TYPE_FRAMEBUFFER ),
            Field ( CommandPool,                    VkObjectType :: VK_OBJECT_TYPE_COMMAND_POOL )
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

#define C_ENG_MAP_START     ENUM ( SharingMode, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Exclusive,  VkSharingMode :: VK_SHARING_MODE_EXCLUSIVE ),
            Field ( Concurrent, VkSharingMode :: VK_SHARING_MODE_CONCURRENT ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     ENUM ( CommandPoolCreateFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Transient,          VkCommandPoolCreateFlagBits :: VK_COMMAND_POOL_CREATE_TRANSIENT_BIT ),
            Field ( ResetCommandBuffer, VkCommandPoolCreateFlagBits :: VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT ),

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

            Field ( Protected,          VkCommandPoolCreateFlagBits :: VK_COMMAND_POOL_CREATE_PROTECTED_BIT ),

#endif

        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     ENUM ( CommandPoolResetFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( ReleaseResources,   VkCommandPoolResetFlagBits :: VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     ENUM ( CommandBufferResetFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( ReleaseResources,   VkCommandBufferResetFlagBits :: VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     ENUM ( CommandBufferLevel, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Primary,    VkCommandBufferLevel :: VK_COMMAND_BUFFER_LEVEL_PRIMARY ),
            Field ( Secondary,  VkCommandBufferLevel :: VK_COMMAND_BUFFER_LEVEL_SECONDARY ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     ENUM ( CommandBufferUsageFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( OneTimeSubmit,      VkCommandBufferUsageFlagBits :: VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT ),
            Field ( RenderPassContinue, VkCommandBufferUsageFlagBits :: VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT ),
            Field ( Simultaneous,       VkCommandBufferUsageFlagBits :: VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     ENUM ( QueryPipelineStatisticFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( InputAssemblyVertices,                      VkQueryPipelineStatisticFlagBits :: VK_QUERY_PIPELINE_STATISTIC_INPUT_ASSEMBLY_VERTICES_BIT ),
            Field ( InputAssemblyPrimitives,                    VkQueryPipelineStatisticFlagBits :: VK_QUERY_PIPELINE_STATISTIC_INPUT_ASSEMBLY_PRIMITIVES_BIT ),
            Field ( VertexShaderInvocations,                    VkQueryPipelineStatisticFlagBits :: VK_QUERY_PIPELINE_STATISTIC_VERTEX_SHADER_INVOCATIONS_BIT ),
            Field ( GeometryShaderInvocations,                  VkQueryPipelineStatisticFlagBits :: VK_QUERY_PIPELINE_STATISTIC_GEOMETRY_SHADER_INVOCATIONS_BIT ),
            Field ( GeometryShaderPrimitives,                   VkQueryPipelineStatisticFlagBits :: VK_QUERY_PIPELINE_STATISTIC_GEOMETRY_SHADER_PRIMITIVES_BIT ),
            Field ( ClippingInvocations,                        VkQueryPipelineStatisticFlagBits :: VK_QUERY_PIPELINE_STATISTIC_CLIPPING_INVOCATIONS_BIT ),
            Field ( ClippingPrimitives,                         VkQueryPipelineStatisticFlagBits :: VK_QUERY_PIPELINE_STATISTIC_CLIPPING_PRIMITIVES_BIT ),
            Field ( FragmentShaderInvocations,                  VkQueryPipelineStatisticFlagBits :: VK_QUERY_PIPELINE_STATISTIC_FRAGMENT_SHADER_INVOCATIONS_BIT ),
            Field ( TessellationControlShaderPatches,           VkQueryPipelineStatisticFlagBits :: VK_QUERY_PIPELINE_STATISTIC_TESSELLATION_CONTROL_SHADER_PATCHES_BIT ),
            Field ( TessellationEvaluationShaderInvocations,    VkQueryPipelineStatisticFlagBits :: VK_QUERY_PIPELINE_STATISTIC_TESSELLATION_EVALUATION_SHADER_INVOCATIONS_BIT ),
            Field ( ComputeShaderInvocations,                   VkQueryPipelineStatisticFlagBits :: VK_QUERY_PIPELINE_STATISTIC_COMPUTE_SHADER_INVOCATIONS_BIT ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     ENUM ( QueryControlFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Precise,    VkQueryControlFlagBits :: VK_QUERY_CONTROL_PRECISE_BIT ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE

#define C_ENG_MAP_START     ENUM ( ColorSpace,  TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( SRGBNonLinear,              VkColorSpaceKHR :: VK_COLORSPACE_SRGB_NONLINEAR_KHR ),

#if __C_ENG_VULKAN_API_EXTENSION_SWAP_CHAIN_COLOR_SPACE_AVAILABLE

            Field ( DisplayP3NonLinear,         VkColorSpaceKHR :: VK_COLOR_SPACE_DISPLAY_P3_NONLINEAR_EXT ),
            Field ( ExtendedSRGBLinear,         VkColorSpaceKHR :: VK_COLOR_SPACE_EXTENDED_SRGB_LINEAR_EXT ),
            Field ( DisplayP3Linear,            VkColorSpaceKHR :: VK_COLOR_SPACE_DISPLAY_P3_LINEAR_EXT ),
            Field ( DCIP3NonLinear,             VkColorSpaceKHR :: VK_COLOR_SPACE_DCI_P3_NONLINEAR_EXT ),
            Field ( BT709Linear,                VkColorSpaceKHR :: VK_COLOR_SPACE_BT709_LINEAR_EXT ),
            Field ( BT709NonLinear,             VkColorSpaceKHR :: VK_COLOR_SPACE_BT709_NONLINEAR_EXT ),
            Field ( BT2020Linear,               VkColorSpaceKHR :: VK_COLOR_SPACE_BT2020_LINEAR_EXT ),
            Field ( HDR10ST2084,                VkColorSpaceKHR :: VK_COLOR_SPACE_HDR10_ST2084_EXT ),
            Field ( DolbyVision,                VkColorSpaceKHR :: VK_COLOR_SPACE_DOLBYVISION_EXT ),
            Field ( HDR10HLG,                   VkColorSpaceKHR :: VK_COLOR_SPACE_HDR10_HLG_EXT ),
            Field ( AdobeRGBLinear,             VkColorSpaceKHR :: VK_COLOR_SPACE_ADOBERGB_LINEAR_EXT ),
            Field ( AdobeRGBNonLinear,          VkColorSpaceKHR :: VK_COLOR_SPACE_ADOBERGB_NONLINEAR_EXT ),
            Field ( PassThrough,                VkColorSpaceKHR :: VK_COLOR_SPACE_PASS_THROUGH_EXT ),
            Field ( ExtendedSRGBNonLinear,      VkColorSpaceKHR :: VK_COLOR_SPACE_EXTENDED_SRGB_NONLINEAR_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_DISPLAY_NATIVE_HDR_AVAILABLE

            Field ( DisplayNativeAMD,           VkColorSpaceKHR :: VK_COLOR_SPACE_DISPLAY_NATIVE_AMD ),

#endif

        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     ENUM ( SurfaceTransformFlag,    TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Identity,           VkSurfaceTransformFlagBitsKHR :: VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR ),
            Field ( Rotate90,           VkSurfaceTransformFlagBitsKHR :: VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR ),
            Field ( Rotate180,          VkSurfaceTransformFlagBitsKHR :: VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR ),
            Field ( Rotate270,          VkSurfaceTransformFlagBitsKHR :: VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR ),
            Field ( Mirror,             VkSurfaceTransformFlagBitsKHR :: VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_BIT_KHR ),
            Field ( MirrorRotate90,     VkSurfaceTransformFlagBitsKHR :: VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_90_BIT_KHR ),
            Field ( MirrorRotate180,    VkSurfaceTransformFlagBitsKHR :: VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_180_BIT_KHR ),
            Field ( MirrorRotate270,    VkSurfaceTransformFlagBitsKHR :: VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_270_BIT_KHR ),
            Field ( Inherit,            VkSurfaceTransformFlagBitsKHR :: VK_SURFACE_TRANSFORM_INHERIT_BIT_KHR )
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     ENUM ( CompositeAlphaFlag,  TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Opaque,         VkCompositeAlphaFlagBitsKHR :: VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR ),
            Field ( PreMultiplied,  VkCompositeAlphaFlagBitsKHR :: VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR ),
            Field ( PostMultiplied, VkCompositeAlphaFlagBitsKHR :: VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR ),
            Field ( Inherit,        VkCompositeAlphaFlagBitsKHR :: VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR )
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     ENUM ( PresentMode,  TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Immediate,                  VkPresentModeKHR :: VK_PRESENT_MODE_IMMEDIATE_KHR ),
            Field ( Mailbox,                    VkPresentModeKHR :: VK_PRESENT_MODE_MAILBOX_KHR ),
            Field ( Fifo,                       VkPresentModeKHR :: VK_PRESENT_MODE_FIFO_KHR ),
            Field ( FifoRelaxed,                VkPresentModeKHR :: VK_PRESENT_MODE_FIFO_RELAXED_KHR ),

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHARED_PRESENTABLE_IMAGE_AVAILABLE

            Field ( SharedDemandRefresh,        VkPresentModeKHR :: VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR ),
            Field ( SharedContinuousRefresh,    VkPresentModeKHR :: VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR ),

#endif

        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( SurfaceFormat, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( Format )     format;
            Type ( ColorSpace ) colorSpace;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISPLAY_SURFACE_COUNTER_AVAILABLE

#define C_ENG_MAP_START     ENUM ( SurfaceCounterFlag,  TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( VBlank, VkSurfaceCounterFlagBitsEXT :: VK_SURFACE_COUNTER_VBLANK_BIT_EXT )
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

#define C_ENG_MAP_START     ENUM ( RenderingFlag,   TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( ContentsSecondayCommandBuffers,     VkRenderingFlagBits :: VK_RENDERING_CONTENTS_SECONDARY_COMMAND_BUFFERS_BIT ),
            Field ( Suspending,                         VkRenderingFlagBits :: VK_RENDERING_SUSPENDING_BIT ),
            Field ( Resuming,                           VkRenderingFlagBits :: VK_RENDERING_RESUMING_BIT ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE

#define C_ENG_MAP_START     ENUM ( RenderingFlag,   TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( ContentsSecondayCommandBuffers,     VkRenderingFlagBitsKHR :: VK_RENDERING_CONTENTS_SECONDARY_COMMAND_BUFFERS_BIT_KHR ),
            Field ( Suspending,                         VkRenderingFlagBitsKHR :: VK_RENDERING_SUSPENDING_BIT_KHR ),
            Field ( Resuming,                           VkRenderingFlagBitsKHR :: VK_RENDERING_RESUMING_BIT_KHR ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

#define C_ENG_MAP_START     ENUM ( FenceCreateFlag,     TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Signaled,   VkFenceCreateFlagBits :: VK_FENCE_CREATE_SIGNALED_BIT ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     ENUM ( EventCreateFlag,     TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
            Field ( DeviceOnly, VkEventCreateFlagBits :: VK_EVENT_CREATE_DEVICE_ONLY_BIT ),
#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
            Field ( DeviceOnly, VkEventCreateFlagBits :: VK_EVENT_CREATE_DEVICE_ONLY_BIT_KHR ),
#endif
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     ENUM ( ImageLayout,     TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Undefined,                              VkImageLayout :: VK_IMAGE_LAYOUT_UNDEFINED ),
            Field ( General,                                VkImageLayout :: VK_IMAGE_LAYOUT_GENERAL ),
            Field ( ColorttachmentOptimal,                  VkImageLayout :: VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL ),
            Field ( DepthStencilAttachmentOptimal,          VkImageLayout :: VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL ),
            Field ( DepthStencilReadOnlyOptimal,            VkImageLayout :: VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL ),
            Field ( SharedReadOnlyOptimal,                  VkImageLayout :: VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL ),
            Field ( TransferSourceOptimal,                  VkImageLayout :: VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL ),
            Field ( TransferDestinationOptimal,             VkImageLayout :: VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL ),
            Field ( Preinitialized,                         VkImageLayout :: VK_IMAGE_LAYOUT_PREINITIALIZED ),

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
            Field ( DepthReadOnlyStencilAttachmentOptimal,  VkImageLayout :: VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL ),
            Field ( DepthAttachmentStencilReadOnlyOptimal,  VkImageLayout :: VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL ),
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
            Field ( DepthAttachmentOptimal,                 VkImageLayout :: VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL ),
            Field ( DepthReadOnlyOptimal,                   VkImageLayout :: VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL ),
            Field ( StencilAttachmentOptimal,               VkImageLayout :: VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL ),
            Field ( StencilReadOnlyOptimal,                 VkImageLayout :: VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL ),
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
            Field ( ReadOnlyOptimal,                        VkImageLayout :: VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL ),
            Field ( AttachmentOptimal,                      VkImageLayout :: VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL ),
#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
            Field ( ReadOnlyOptimal,                        VkImageLayout :: VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL_KHR ),
            Field ( AttachmentOptimal,                      VkImageLayout :: VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL_KHR ),
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE
            Field ( LayoutPresentSource,                    VkImageLayout :: VK_IMAGE_LAYOUT_PRESENT_SRC_KHR ),
#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_DECODE_QUEUE_AVAILABLE
            Field ( VideoDecodeDestination,                 VkImageLayout :: VK_IMAGE_LAYOUT_VIDEO_DECODE_DST_KHR ),
            Field ( VideoDecodeSource,                      VkImageLayout :: VK_IMAGE_LAYOUT_VIDEO_DECODE_SRC_KHR ),
            Field ( VideoDecodeDPB,                         VkImageLayout :: VK_IMAGE_LAYOUT_VIDEO_DECODE_DPB_KHR ),
#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_ENCODE_QUEUE_AVAILABLE
            Field ( VideoEncodeDestination,                 VkImageLayout :: VK_IMAGE_LAYOUT_VIDEO_ENCODE_DST_KHR ),
            Field ( VideoEncodeSource,                      VkImageLayout :: VK_IMAGE_LAYOUT_VIDEO_ENCODE_SRC_KHR ),
            Field ( VideoEncodeDPB,                         VkImageLayout :: VK_IMAGE_LAYOUT_VIDEO_ENCODE_DPB_KHR ),
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHARED_PRESENTABLE_IMAGE_AVAILABLE
            Field ( SharedPresent,                          VkImageLayout :: VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR ),
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE
            Field ( FragmentDensityMapOptimal,              VkImageLayout :: VK_IMAGE_LAYOUT_FRAGMENT_DENSITY_MAP_OPTIMAL_EXT ),
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE
            Field ( FragmentShadingRateAttachmentOptimal,   VkImageLayout :: VK_IMAGE_LAYOUT_FRAGMENT_SHADING_RATE_ATTACHMENT_OPTIMAL_KHR ),
#endif
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

#define C_ENG_MAP_START     ENUM ( ExternalFenceHandleTypeFlag,     TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( OpaqueFD,       VkExternalFenceHandleTypeFlagBits :: VK_EXTERNAL_FENCE_HANDLE_TYPE_OPAQUE_FD_BIT ),
            Field ( OpaqueWin32,    VkExternalFenceHandleTypeFlagBits :: VK_EXTERNAL_FENCE_HANDLE_TYPE_OPAQUE_WIN32_BIT ),
            Field ( OpaqueWin32KMT, VkExternalFenceHandleTypeFlagBits :: VK_EXTERNAL_FENCE_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT ),
            Field ( SyncFD,         VkExternalFenceHandleTypeFlagBits :: VK_EXTERNAL_FENCE_HANDLE_TYPE_SYNC_FD_BIT ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
#define C_ENG_MAP_START ENUM ( SemaphoreType, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Binary,     VkSemaphoreType :: VK_SEMAPHORE_TYPE_BINARY ),
            Field ( Timeline,   VkSemaphoreType :: VK_SEMAPHORE_TYPE_TIMELINE ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define C_ENG_MAP_START ENUM ( ExternalSemaphoreHandleTypeFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( OpaqueFd,           VkExternalSemaphoreHandleTypeFlagBits :: VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_FD_BIT ),
            Field ( OpaqueWin32,        VkExternalSemaphoreHandleTypeFlagBits :: VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_BIT ),
            Field ( OpaqueWin32KMT,     VkExternalSemaphoreHandleTypeFlagBits :: VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT ),
            Field ( D3D12Fence,         VkExternalSemaphoreHandleTypeFlagBits :: VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_D3D12_FENCE_BIT ),
            Field ( SyncFd,             VkExternalSemaphoreHandleTypeFlagBits :: VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_SYNC_FD_BIT ),

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_SEMAPHORE_AVAILABLE
            Field ( ZirconEventGoogle,  VkExternalSemaphoreHandleTypeFlagBits :: VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_ZIRCON_EVENT_BIT_FUCHSIA ),
#endif
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_DISPLAY_CONTROL_AVAILABLE

#define C_ENG_MAP_START     ENUM ( DeviceEventType,     TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( DisplayHotplug, VkDeviceEventTypeEXT :: VK_DEVICE_EVENT_TYPE_DISPLAY_HOTPLUG_EXT ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     ENUM ( DisplayEventType,     TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( FirstPixelOut, VkDisplayEventTypeEXT :: VK_DISPLAY_EVENT_TYPE_FIRST_PIXEL_OUT_EXT ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

#define C_ENG_MAP_START ENUM ( FenceImportFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Temporary,  VkFenceImportFlagBits :: VK_FENCE_IMPORT_TEMPORARY_BIT ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START ENUM ( SemaphoreImportFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Temporary,  VkSemaphoreImportFlagBits :: VK_SEMAPHORE_IMPORT_TEMPORARY_BIT ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
#define C_ENG_MAP_START ENUM ( SemaphoreWaitFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Any, VkSemaphoreWaitFlagBits :: VK_SEMAPHORE_WAIT_ANY_BIT ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START ENUM ( DependencyFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( ByRegion,       VkDependencyFlagBits :: VK_DEPENDENCY_BY_REGION_BIT ),

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
            Field ( DeviceGroup,    VkDependencyFlagBits :: VK_DEPENDENCY_DEVICE_GROUP_BIT ),
            Field ( ViewLocal,      VkDependencyFlagBits :: VK_DEPENDENCY_VIEW_LOCAL_BIT ),
#endif

        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START ENUM ( RenderPassCreateFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_RENDER_PASS_TRANSFORM_AVAILABLE
            Field ( TransformQualcomm,  VkRenderPassCreateFlagBits :: VK_RENDER_PASS_CREATE_TRANSFORM_BIT_QCOM ),
#endif
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START ENUM ( AttachmentDescriptionFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( MayAlias,  VkAttachmentDescriptionFlagBits :: VK_ATTACHMENT_DESCRIPTION_MAY_ALIAS_BIT ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START ENUM ( SubpassDescriptionFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE
            Field ( PerViewAttributesNVidia,                        VkSubpassDescriptionFlagBits :: VK_SUBPASS_DESCRIPTION_PER_VIEW_ATTRIBUTES_BIT_NVX ),
            Field ( PerViewPositionXOnlyNVidia,                     VkSubpassDescriptionFlagBits :: VK_SUBPASS_DESCRIPTION_PER_VIEW_POSITION_X_ONLY_BIT_NVX ),
#endif
#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_RENDER_PASS_SHADER_RESOLVE_AVAILABLE
            Field ( FragmentRegionQualcomm,                         VkSubpassDescriptionFlagBits :: VK_SUBPASS_DESCRIPTION_FRAGMENT_REGION_BIT_QCOM ),
            Field ( ShaderResolveQualcomm,                          VkSubpassDescriptionFlagBits :: VK_SUBPASS_DESCRIPTION_SHADER_RESOLVE_BIT_QCOM ),
#endif
#if __C_ENG_VULKAN_API_EXTENSION_ARM_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_AVAILABLE
            Field ( RasterizationOrderAttachmentColorAccessARM,     VkSubpassDescriptionFlagBits :: VK_SUBPASS_DESCRIPTION_RASTERIZATION_ORDER_ATTACHMENT_COLOR_ACCESS_BIT_ARM ),
            Field ( RasterizationOrderAttachmentDepthAccessARM,     VkSubpassDescriptionFlagBits :: VK_SUBPASS_DESCRIPTION_RASTERIZATION_ORDER_ATTACHMENT_DEPTH_ACCESS_BIT_ARM ),
            Field ( RasterizationOrderAttachmentStencilAccessARM,   VkSubpassDescriptionFlagBits :: VK_SUBPASS_DESCRIPTION_RASTERIZATION_ORDER_ATTACHMENT_STENCIL_ACCESS_BIT_ARM ),
#endif
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START ENUM ( PipelineBindPoint, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Graphics,               VkPipelineBindPoint :: VK_PIPELINE_BIND_POINT_GRAPHICS ),
            Field ( Compute,                VkPipelineBindPoint :: VK_PIPELINE_BIND_POINT_COMPUTE ),
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
            Field ( RayTracing,             VkPipelineBindPoint :: VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR ),
#endif
#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE
            Field ( SubpassShadingHuawei,   VkPipelineBindPoint :: VK_PIPELINE_BIND_POINT_SUBPASS_SHADING_HUAWEI ),
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
            Field ( RayTracingNVidia,       VkPipelineBindPoint :: VK_PIPELINE_BIND_POINT_RAY_TRACING_NV ),
#endif
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START ENUM ( FrameBufferCreateFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
            Field ( Imageless,  VkFramebufferCreateFlagBits :: VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT ),
#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_IMAGELESS_FRAME_BUFFER_AVAILABLE
            Field ( Imageless,  VkFramebufferCreateFlagBits :: VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT_KHR ),
#endif
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START ENUM ( ImageCreateFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( SparseBinding,                      VkImageCreateFlagBits :: VK_IMAGE_CREATE_SPARSE_BINDING_BIT ),
            Field ( SparseResidency,                    VkImageCreateFlagBits :: VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT ),
            Field ( SparseAliased,                      VkImageCreateFlagBits :: VK_IMAGE_CREATE_SPARSE_ALIASED_BIT ),
            Field ( MutableFormat,                      VkImageCreateFlagBits :: VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT ),
            Field ( CubeCompatible,                     VkImageCreateFlagBits :: VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT ),

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
            Field ( Alias,                              VkImageCreateFlagBits :: VK_IMAGE_CREATE_ALIAS_BIT ),
            Field ( SplitInstanceBindRegions,           VkImageCreateFlagBits :: VK_IMAGE_CREATE_SPLIT_INSTANCE_BIND_REGIONS_BIT ),
            Field ( 2DArrayCompatible,                  VkImageCreateFlagBits :: VK_IMAGE_CREATE_2D_ARRAY_COMPATIBLE_BIT ),
            Field ( BlockTexelViewCompatible,           VkImageCreateFlagBits :: VK_IMAGE_CREATE_BLOCK_TEXEL_VIEW_COMPATIBLE_BIT ),
            Field ( ExtendedUsage,                      VkImageCreateFlagBits :: VK_IMAGE_CREATE_EXTENDED_USAGE_BIT ),
            Field ( Protected,                          VkImageCreateFlagBits :: VK_IMAGE_CREATE_PROTECTED_BIT ),
            Field ( Disjoint,                           VkImageCreateFlagBits :: VK_IMAGE_CREATE_DISJOINT_BIT ),
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CORNER_SAMPLED_IMAGE_AVAILABLE
            Field ( CornerSampledNVidia,                VkImageCreateFlagBits :: VK_IMAGE_CREATE_CORNER_SAMPLED_BIT_NV ),
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE
            Field ( SampleLocationsCompatibleDepth,     VkImageCreateFlagBits :: VK_IMAGE_CREATE_SAMPLE_LOCATIONS_COMPATIBLE_DEPTH_BIT_EXT ),
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE
            Field ( Subsampled,                         VkImageCreateFlagBits :: VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT ),
#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE
            Field ( FragmentDensityMapOffsetQualcomm,   VkImageCreateFlagBits :: VK_IMAGE_CREATE_FRAGMENT_DENSITY_MAP_OFFSET_BIT_QCOM ),
#endif

        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START ENUM ( SubpassContents, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Inline,                     VkSubpassContents :: VK_SUBPASS_CONTENTS_INLINE ),
            Field ( SecondaryCommandBuffers,    VkSubpassContents :: VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE
#define C_ENG_MAP_START ENUM ( ComponentTypeNVidia, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Float16,    VkComponentTypeNV :: VK_COMPONENT_TYPE_FLOAT16_NV ),
            Field ( Float32,    VkComponentTypeNV :: VK_COMPONENT_TYPE_FLOAT32_NV ),
            Field ( Float64,    VkComponentTypeNV :: VK_COMPONENT_TYPE_FLOAT64_NV ),

            Field ( SInt8,      VkComponentTypeNV :: VK_COMPONENT_TYPE_SINT8_NV ),
            Field ( SInt16,     VkComponentTypeNV :: VK_COMPONENT_TYPE_SINT16_NV ),
            Field ( SInt32,     VkComponentTypeNV :: VK_COMPONENT_TYPE_SINT32_NV ),
            Field ( SInt64,     VkComponentTypeNV :: VK_COMPONENT_TYPE_SINT64_NV ),

            Field ( UInt8,      VkComponentTypeNV :: VK_COMPONENT_TYPE_UINT8_NV ),
            Field ( UInt16,     VkComponentTypeNV :: VK_COMPONENT_TYPE_UINT16_NV ),
            Field ( UInt32,     VkComponentTypeNV :: VK_COMPONENT_TYPE_UINT32_NV ),
            Field ( UInt64,     VkComponentTypeNV :: VK_COMPONENT_TYPE_UINT64_NV ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START ENUM ( ScopeNVidia, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Device,         VkScopeNV :: VK_SCOPE_DEVICE_NV ),
            Field ( Workgroup,      VkScopeNV :: VK_SCOPE_WORKGROUP_NV ),
            Field ( Subgroup,       VkScopeNV :: VK_SCOPE_SUBGROUP_NV ),
            Field ( QueueFamily,    VkScopeNV :: VK_SCOPE_QUEUE_FAMILY_NV ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START ENUM ( PipelineCreateFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( DisableOptimization,                        VkPipelineCreateFlagBits :: VK_PIPELINE_CREATE_DISABLE_OPTIMIZATION_BIT ),
            Field ( AllowDerivatives,                           VkPipelineCreateFlagBits :: VK_PIPELINE_CREATE_ALLOW_DERIVATIVES_BIT ),
            Field ( Derivative,                                 VkPipelineCreateFlagBits :: VK_PIPELINE_CREATE_DERIVATIVE_BIT ),

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
            Field ( ViewIndexFromDeviceIndex,                   VkPipelineCreateFlagBits :: VK_PIPELINE_CREATE_VIEW_INDEX_FROM_DEVICE_INDEX_BIT ),
            Field ( DispatchBase,                               VkPipelineCreateFlagBits :: VK_PIPELINE_CREATE_DISPATCH_BASE_BIT ),
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
            Field ( FailOnPipelineCompileRequired,              VkPipelineCreateFlagBits :: VK_PIPELINE_CREATE_FAIL_ON_PIPELINE_COMPILE_REQUIRED_BIT ),
            Field ( EarlyReturnOnFailure,                       VkPipelineCreateFlagBits :: VK_PIPELINE_CREATE_EARLY_RETURN_ON_FAILURE_BIT ),
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE && ( __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE )
            Field ( RenderingFragmentShadingRateAttachment,     VkPipelineCreateFlagBits :: VK_PIPELINE_RASTERIZATION_STATE_CREATE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR    ),
#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE && ( __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE )
            Field ( RenderingFragmentDensityMapAttachment,      VkPipelineCreateFlagBits :: VK_PIPELINE_RASTERIZATION_STATE_CREATE_FRAGMENT_DENSITY_MAP_ATTACHMENT_BIT_EXT  ),
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
            Field ( RayTracingNoNullAnyHitShaders,              VkPipelineCreateFlagBits :: VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_ANY_HIT_SHADERS_BIT_KHR ),
            Field ( RayTracingNoNullClosestHitShaders,          VkPipelineCreateFlagBits :: VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_CLOSEST_HIT_SHADERS_BIT_KHR ),
            Field ( RayTracingNoNullMissShaders,                VkPipelineCreateFlagBits :: VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_MISS_SHADERS_BIT_KHR ),
            Field ( RayTracingNoNullIntersectionShaders,        VkPipelineCreateFlagBits :: VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_INTERSECTION_SHADERS_BIT_KHR ),
            Field ( RayTracingSkipTriangles,                    VkPipelineCreateFlagBits :: VK_PIPELINE_CREATE_RAY_TRACING_SKIP_TRIANGLES_BIT_KHR ),
            Field ( RayTracingSkipAABBS,                        VkPipelineCreateFlagBits :: VK_PIPELINE_CREATE_RAY_TRACING_SKIP_AABBS_BIT_KHR ),
            Field ( RayTracingShaderGroupHandleCaptureReplay,   VkPipelineCreateFlagBits :: VK_PIPELINE_CREATE_RAY_TRACING_SHADER_GROUP_HANDLE_CAPTURE_REPLAY_BIT_KHR ),
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
            Field ( DeferCompileNVidia,                         VkPipelineCreateFlagBits :: VK_PIPELINE_CREATE_DEFER_COMPILE_BIT_NV ),
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
            Field ( CaptureStatistics,                          VkPipelineCreateFlagBits :: VK_PIPELINE_CREATE_CAPTURE_STATISTICS_BIT_KHR ),
            Field ( CaptureInternalRepresentations,             VkPipelineCreateFlagBits :: VK_PIPELINE_CREATE_CAPTURE_INTERNAL_REPRESENTATIONS_BIT_KHR ),
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE
            Field ( IndirectBindableNVidia,                     VkPipelineCreateFlagBits :: VK_PIPELINE_CREATE_INDIRECT_BINDABLE_BIT_NV ),
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_LIBRARY_AVAILABLE
            Field ( Library,                                    VkPipelineCreateFlagBits :: VK_PIPELINE_CREATE_LIBRARY_BIT_KHR ),
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE
            Field ( RayTracingAllowMotionNVidia,                VkPipelineCreateFlagBits :: VK_PIPELINE_CREATE_RAY_TRACING_ALLOW_MOTION_BIT_NV ),
#endif

        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START ENUM ( PipelineShaderStageCreateFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
            Field ( AllowVaryingSubgroupSize, VkPipelineShaderStageCreateFlagBits :: VK_PIPELINE_SHADER_STAGE_CREATE_ALLOW_VARYING_SUBGROUP_SIZE_BIT ),
            Field ( RequireFullSubgroups,     VkPipelineShaderStageCreateFlagBits :: VK_PIPELINE_SHADER_STAGE_CREATE_REQUIRE_FULL_SUBGROUPS_BIT ),
#elif __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE
            Field ( AllowVaryingSubgroupSize, VkPipelineShaderStageCreateFlagBits :: VK_PIPELINE_SHADER_STAGE_CREATE_ALLOW_VARYING_SUBGROUP_SIZE_BIT_EXT ),
            Field ( RequireFullSubgroups,     VkPipelineShaderStageCreateFlagBits :: VK_PIPELINE_SHADER_STAGE_CREATE_REQUIRE_FULL_SUBGROUPS_BIT_EXT ),
#endif
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_AMD_PIPELINE_COMPILER_CONTROL_AVAILABLE
#define C_ENG_MAP_START ENUM ( PipelineCompilerControlFlagAMD, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum { };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_FEEDBACK_AVAILABLE
#define C_ENG_MAP_START ENUM ( PipelineCreationFeedbackFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
            Field ( Valid,                      VkPipelineCreationFeedbackFlagBits :: VK_PIPELINE_CREATION_FEEDBACK_VALID_BIT ),
            Field ( ApplicationPipelineCache,   VkPipelineCreationFeedbackFlagBits :: VK_PIPELINE_CREATION_FEEDBACK_APPLICATION_PIPELINE_CACHE_HIT_BIT ),
            Field ( BasePipelineAcceleration,   VkPipelineCreationFeedbackFlagBits :: VK_PIPELINE_CREATION_FEEDBACK_BASE_PIPELINE_ACCELERATION_BIT ),
#else
            Field ( Valid,                      VkPipelineCreationFeedbackFlagBitsEXT :: VK_PIPELINE_CREATION_FEEDBACK_VALID_BIT_EXT ),
            Field ( ApplicationPipelineCache,   VkPipelineCreationFeedbackFlagBitsEXT :: VK_PIPELINE_CREATION_FEEDBACK_APPLICATION_PIPELINE_CACHE_HIT_BIT_EXT ),
            Field ( BasePipelineAcceleration,   VkPipelineCreationFeedbackFlagBitsEXT :: VK_PIPELINE_CREATION_FEEDBACK_BASE_PIPELINE_ACCELERATION_BIT_EXT ),
#endif
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START ENUM ( VertexInputRate, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Vertex,     VkVertexInputRate :: VK_VERTEX_INPUT_RATE_VERTEX ),
            Field ( Instance,   VkVertexInputRate :: VK_VERTEX_INPUT_RATE_INSTANCE ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_DISCARD_RECTANGLES_AVAILABLE
#define C_ENG_MAP_START ENUM ( DiscardRectangleMode, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Inclusive,  VkDiscardRectangleModeEXT :: VK_DISCARD_RECTANGLE_MODE_INCLUSIVE_EXT ),
            Field ( Exclusive,  VkDiscardRectangleModeEXT :: VK_DISCARD_RECTANGLE_MODE_EXCLUSIVE_EXT ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE
#define C_ENG_MAP_START ENUM ( FragmentShadingRateNVidia, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( 1InvocationPerPixel,        VkFragmentShadingRateNV :: VK_FRAGMENT_SHADING_RATE_1_INVOCATION_PER_PIXEL_NV ),
            Field ( 1InvocationPer1x2Pixels,    VkFragmentShadingRateNV :: VK_FRAGMENT_SHADING_RATE_1_INVOCATION_PER_1X2_PIXELS_NV ),
            Field ( 1InvocationPer2x1Pixels,    VkFragmentShadingRateNV :: VK_FRAGMENT_SHADING_RATE_1_INVOCATION_PER_2X1_PIXELS_NV ),
            Field ( 1InvocationPer2x2Pixels,    VkFragmentShadingRateNV :: VK_FRAGMENT_SHADING_RATE_1_INVOCATION_PER_2X2_PIXELS_NV ),
            Field ( 1InvocationPer2x4Pixels,    VkFragmentShadingRateNV :: VK_FRAGMENT_SHADING_RATE_1_INVOCATION_PER_2X4_PIXELS_NV ),
            Field ( 1InvocationPer4x2Pixels,    VkFragmentShadingRateNV :: VK_FRAGMENT_SHADING_RATE_1_INVOCATION_PER_4X2_PIXELS_NV ),
            Field ( 1InvocationPer4x4Pixels,    VkFragmentShadingRateNV :: VK_FRAGMENT_SHADING_RATE_1_INVOCATION_PER_4X4_PIXELS_NV ),
            Field ( 2InvocationsPerPixel,       VkFragmentShadingRateNV :: VK_FRAGMENT_SHADING_RATE_2_INVOCATIONS_PER_PIXEL_NV ),
            Field ( 4InvocationsPerPixel,       VkFragmentShadingRateNV :: VK_FRAGMENT_SHADING_RATE_4_INVOCATIONS_PER_PIXEL_NV ),
            Field ( 8InvocationsPerPixel,       VkFragmentShadingRateNV :: VK_FRAGMENT_SHADING_RATE_8_INVOCATIONS_PER_PIXEL_NV ),
            Field ( 16InvocationsPerPixel,      VkFragmentShadingRateNV :: VK_FRAGMENT_SHADING_RATE_16_INVOCATIONS_PER_PIXEL_NV ),
            Field ( NoInvocations,              VkFragmentShadingRateNV :: VK_FRAGMENT_SHADING_RATE_NO_INVOCATIONS_NV ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START ENUM ( FragmentShadingRateTypeNVidia, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( FragmentSize,   VkFragmentShadingRateTypeNV :: VK_FRAGMENT_SHADING_RATE_TYPE_FRAGMENT_SIZE_NV ),
            Field ( Enums,          VkFragmentShadingRateTypeNV :: VK_FRAGMENT_SHADING_RATE_TYPE_ENUMS_NV ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE
#define C_ENG_MAP_START ENUM ( FragmentShadingRateCombinerOperation, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Keep,       VkFragmentShadingRateCombinerOpKHR :: VK_FRAGMENT_SHADING_RATE_COMBINER_OP_KEEP_KHR ),
            Field ( Replace,    VkFragmentShadingRateCombinerOpKHR :: VK_FRAGMENT_SHADING_RATE_COMBINER_OP_REPLACE_KHR ),
            Field ( Min,        VkFragmentShadingRateCombinerOpKHR :: VK_FRAGMENT_SHADING_RATE_COMBINER_OP_MIN_KHR ),
            Field ( Max,        VkFragmentShadingRateCombinerOpKHR :: VK_FRAGMENT_SHADING_RATE_COMBINER_OP_MAX_KHR ),
            Field ( Mul,        VkFragmentShadingRateCombinerOpKHR :: VK_FRAGMENT_SHADING_RATE_COMBINER_OP_MUL_KHR ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START ENUM ( PrimitiveTopology, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( PointList,                  VkPrimitiveTopology :: VK_PRIMITIVE_TOPOLOGY_POINT_LIST ),
            Field ( LineList,                   VkPrimitiveTopology :: VK_PRIMITIVE_TOPOLOGY_LINE_LIST ),
            Field ( LineStrip,                  VkPrimitiveTopology :: VK_PRIMITIVE_TOPOLOGY_LINE_STRIP ),
            Field ( TriangleList,               VkPrimitiveTopology :: VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST ),
            Field ( TriangleStrip,              VkPrimitiveTopology :: VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP ),
            Field ( TriangleFan,                VkPrimitiveTopology :: VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN ),
            Field ( LineListWithAdjacency,      VkPrimitiveTopology :: VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY ),
            Field ( LineStripWithAdjacency,     VkPrimitiveTopology :: VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY ),
            Field ( TriangleListWithAdjacency,  VkPrimitiveTopology :: VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY ),
            Field ( TriangleStripWithAdjacency, VkPrimitiveTopology :: VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START ENUM ( PolygonMode, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Fill,                   VkPolygonMode :: VK_POLYGON_MODE_FILL ),
            Field ( Line,                   VkPolygonMode :: VK_POLYGON_MODE_LINE ),
            Field ( Point,                  VkPolygonMode :: VK_POLYGON_MODE_POINT ),
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FILL_RECTANGLE_AVAILABLE
            Field ( FillRectangleNVidia,    VkPolygonMode :: VK_POLYGON_MODE_FILL_RECTANGLE_NV ),
#endif
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START ENUM ( CullModeFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( None,           VkCullModeFlagBits :: VK_CULL_MODE_NONE ),
            Field ( Front,          VkCullModeFlagBits :: VK_CULL_MODE_FRONT_BIT ),
            Field ( Back,           VkCullModeFlagBits :: VK_CULL_MODE_BACK_BIT ),
            Field ( FrontAndBack,   VkCullModeFlagBits :: VK_CULL_MODE_FRONT_AND_BACK ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START ENUM ( FrontFace, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( CounterClockwise,   VkFrontFace :: VK_FRONT_FACE_COUNTER_CLOCKWISE ),
            Field ( Clockwise,          VkFrontFace :: VK_FRONT_FACE_CLOCKWISE ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START ENUM ( CompareOperation, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Never,          VkCompareOp :: VK_COMPARE_OP_NEVER ),
            Field ( Less,           VkCompareOp :: VK_COMPARE_OP_LESS ),
            Field ( Equal,          VkCompareOp :: VK_COMPARE_OP_EQUAL ),
            Field ( LessOrEqual,    VkCompareOp :: VK_COMPARE_OP_LESS_OR_EQUAL ),
            Field ( Greater,        VkCompareOp :: VK_COMPARE_OP_GREATER ),
            Field ( NotEqual,       VkCompareOp :: VK_COMPARE_OP_NOT_EQUAL ),
            Field ( GreaterOrEqual, VkCompareOp :: VK_COMPARE_OP_GREATER_OR_EQUAL ),
            Field ( Always,         VkCompareOp :: VK_COMPARE_OP_ALWAYS ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START ENUM ( StencilOperation, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Keep,               VkStencilOp :: VK_STENCIL_OP_KEEP ),
            Field ( Zero,               VkStencilOp :: VK_STENCIL_OP_ZERO ),
            Field ( Replace,            VkStencilOp :: VK_STENCIL_OP_REPLACE ),
            Field ( IncrementAndClamp,  VkStencilOp :: VK_STENCIL_OP_INCREMENT_AND_CLAMP ),
            Field ( DecrementAndClamp,  VkStencilOp :: VK_STENCIL_OP_DECREMENT_AND_CLAMP ),
            Field ( Invert,             VkStencilOp :: VK_STENCIL_OP_INVERT ),
            Field ( IncrementAndWrap,   VkStencilOp :: VK_STENCIL_OP_INCREMENT_AND_WRAP ),
            Field ( DecrementAndWrap,   VkStencilOp :: VK_STENCIL_OP_DECREMENT_AND_WRAP ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START ENUM ( LogicOperation, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Clear,          VkLogicOp :: VK_LOGIC_OP_CLEAR ),
            Field ( And,            VkLogicOp :: VK_LOGIC_OP_AND ),
            Field ( AndReverse,     VkLogicOp :: VK_LOGIC_OP_AND_REVERSE ),
            Field ( Copy,           VkLogicOp :: VK_LOGIC_OP_COPY ),
            Field ( AndInverted,    VkLogicOp :: VK_LOGIC_OP_AND_INVERTED ),
            Field ( NoOperation,    VkLogicOp :: VK_LOGIC_OP_NO_OP ),
            Field ( Xor,            VkLogicOp :: VK_LOGIC_OP_XOR ),
            Field ( Or,             VkLogicOp :: VK_LOGIC_OP_OR ),
            Field ( Nor,            VkLogicOp :: VK_LOGIC_OP_NOR ),
            Field ( Equivalent,     VkLogicOp :: VK_LOGIC_OP_EQUIVALENT ),
            Field ( Invert,         VkLogicOp :: VK_LOGIC_OP_INVERT ),
            Field ( OrReverse,      VkLogicOp :: VK_LOGIC_OP_OR_REVERSE ),
            Field ( CopyInverted,   VkLogicOp :: VK_LOGIC_OP_COPY_INVERTED ),
            Field ( OrInverted,     VkLogicOp :: VK_LOGIC_OP_OR_INVERTED ),
            Field ( Nand,           VkLogicOp :: VK_LOGIC_OP_NAND ),
            Field ( Set,            VkLogicOp :: VK_LOGIC_OP_SET ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START ENUM ( PipelineColorBlendStateCreateFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
#if __C_ENG_VULKAN_API_EXTENSION_ARM_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_AVAILABLE
            Field ( RasterizationOrderAttachmentAccessARM,  VkPipelineColorBlendStateCreateFlagBits :: VK_PIPELINE_COLOR_BLEND_STATE_CREATE_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_BIT_ARM ),
#endif
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START ENUM ( ColorComponentFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( R,  VkColorComponentFlagBits :: VK_COLOR_COMPONENT_R_BIT ),
            Field ( G,  VkColorComponentFlagBits :: VK_COLOR_COMPONENT_G_BIT ),
            Field ( B,  VkColorComponentFlagBits :: VK_COLOR_COMPONENT_B_BIT ),
            Field ( A,  VkColorComponentFlagBits :: VK_COLOR_COMPONENT_A_BIT ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START ENUM ( BlendFactor, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Zero,                       VkBlendFactor :: VK_BLEND_FACTOR_ZERO ),
            Field ( One,                        VkBlendFactor :: VK_BLEND_FACTOR_ONE ),
            Field ( SourceColor,                VkBlendFactor :: VK_BLEND_FACTOR_SRC_COLOR ),
            Field ( OneMinusSourceColor,        VkBlendFactor :: VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR ),
            Field ( DestinationColor,           VkBlendFactor :: VK_BLEND_FACTOR_DST_COLOR ),
            Field ( OneMinusDestinationColor,   VkBlendFactor :: VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR ),
            Field ( SourceAlpha,                VkBlendFactor :: VK_BLEND_FACTOR_SRC_ALPHA ),
            Field ( OneMinusSourceAlpha,        VkBlendFactor :: VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA ),
            Field ( DestinationAlpha,           VkBlendFactor :: VK_BLEND_FACTOR_DST_ALPHA ),
            Field ( OneMinusDestinationAlpha,   VkBlendFactor :: VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA ),
            Field ( ConstantColor,              VkBlendFactor :: VK_BLEND_FACTOR_CONSTANT_COLOR ),
            Field ( OneMinusConstantColor,      VkBlendFactor :: VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR ),
            Field ( ConstantAlpha,              VkBlendFactor :: VK_BLEND_FACTOR_CONSTANT_ALPHA ),
            Field ( OneMinusConstantAlpha,      VkBlendFactor :: VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA ),
            Field ( AlphaSaturate,              VkBlendFactor :: VK_BLEND_FACTOR_SRC_ALPHA_SATURATE ),
            Field ( Source1Color,               VkBlendFactor :: VK_BLEND_FACTOR_SRC1_COLOR ),
            Field ( OneMinusSource1Color,       VkBlendFactor :: VK_BLEND_FACTOR_ONE_MINUS_SRC1_COLOR ),
            Field ( Source1Alpha,               VkBlendFactor :: VK_BLEND_FACTOR_SRC1_ALPHA ),
            Field ( OneMinusSource1Alpha,       VkBlendFactor :: VK_BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START ENUM ( BlendOperation, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Add,                VkBlendOp :: VK_BLEND_OP_ADD ),
            Field ( Subtract,           VkBlendOp :: VK_BLEND_OP_SUBTRACT ),
            Field ( ReverseSubtract,    VkBlendOp :: VK_BLEND_OP_REVERSE_SUBTRACT ),
            Field ( Min,                VkBlendOp :: VK_BLEND_OP_MIN ),
            Field ( Max,                VkBlendOp :: VK_BLEND_OP_MAX ),
#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE
            Field ( Zero,               VkBlendOp :: VK_BLEND_OP_ZERO_EXT ),
            Field ( Source,             VkBlendOp :: VK_BLEND_OP_SRC_EXT ),
            Field ( Destination,        VkBlendOp :: VK_BLEND_OP_DST_EXT ),
            Field ( SourceOver,         VkBlendOp :: VK_BLEND_OP_SRC_OVER_EXT ),
            Field ( DestinationOver,    VkBlendOp :: VK_BLEND_OP_DST_OVER_EXT ),
            Field ( SourceIn,           VkBlendOp :: VK_BLEND_OP_SRC_IN_EXT ),
            Field ( DestinationIn,      VkBlendOp :: VK_BLEND_OP_DST_IN_EXT ),
            Field ( SourceOut,          VkBlendOp :: VK_BLEND_OP_SRC_OUT_EXT ),
            Field ( DestinationOut,     VkBlendOp :: VK_BLEND_OP_DST_OUT_EXT ),
            Field ( SourceAtop,         VkBlendOp :: VK_BLEND_OP_SRC_ATOP_EXT ),
            Field ( DestinationAtop,    VkBlendOp :: VK_BLEND_OP_DST_ATOP_EXT ),
            Field ( Xor,                VkBlendOp :: VK_BLEND_OP_XOR_EXT ),
            Field ( Multiply,           VkBlendOp :: VK_BLEND_OP_MULTIPLY_EXT ),
            Field ( Screen,             VkBlendOp :: VK_BLEND_OP_SCREEN_EXT ),
            Field ( Overlay,            VkBlendOp :: VK_BLEND_OP_OVERLAY_EXT ),
            Field ( Darken,             VkBlendOp :: VK_BLEND_OP_DARKEN_EXT ),
            Field ( Lighten,            VkBlendOp :: VK_BLEND_OP_LIGHTEN_EXT ),
            Field ( ColorDodge,         VkBlendOp :: VK_BLEND_OP_COLORDODGE_EXT ),
            Field ( ColorBurn,          VkBlendOp :: VK_BLEND_OP_COLORBURN_EXT ),
            Field ( HardLight,          VkBlendOp :: VK_BLEND_OP_HARDLIGHT_EXT ),
            Field ( SoftLight,          VkBlendOp :: VK_BLEND_OP_SOFTLIGHT_EXT ),
            Field ( Difference,         VkBlendOp :: VK_BLEND_OP_DIFFERENCE_EXT ),
            Field ( Exclusion,          VkBlendOp :: VK_BLEND_OP_EXCLUSION_EXT ),
            Field ( Invert,             VkBlendOp :: VK_BLEND_OP_INVERT_EXT ),
            Field ( InvertRGB,          VkBlendOp :: VK_BLEND_OP_INVERT_RGB_EXT ),
            Field ( LinearDodge,        VkBlendOp :: VK_BLEND_OP_LINEARDODGE_EXT ),
            Field ( LinearBurn,         VkBlendOp :: VK_BLEND_OP_LINEARBURN_EXT ),
            Field ( VividLight,         VkBlendOp :: VK_BLEND_OP_VIVIDLIGHT_EXT ),
            Field ( LinearLight,        VkBlendOp :: VK_BLEND_OP_LINEARLIGHT_EXT ),
            Field ( PinLight,           VkBlendOp :: VK_BLEND_OP_PINLIGHT_EXT ),
            Field ( HardMix,            VkBlendOp :: VK_BLEND_OP_HARDMIX_EXT ),
            Field ( HSLHue,             VkBlendOp :: VK_BLEND_OP_HSL_HUE_EXT ),
            Field ( HSLSaturation,      VkBlendOp :: VK_BLEND_OP_HSL_SATURATION_EXT ),
            Field ( HSLColor,           VkBlendOp :: VK_BLEND_OP_HSL_COLOR_EXT ),
            Field ( HSLLuminosity,      VkBlendOp :: VK_BLEND_OP_HSL_LUMINOSITY_EXT ),
            Field ( Plus,               VkBlendOp :: VK_BLEND_OP_PLUS_EXT ),
            Field ( PlusClamped,        VkBlendOp :: VK_BLEND_OP_PLUS_CLAMPED_EXT ),
            Field ( PlusClampedAlpha,   VkBlendOp :: VK_BLEND_OP_PLUS_CLAMPED_ALPHA_EXT ),
            Field ( PlusDarker,         VkBlendOp :: VK_BLEND_OP_PLUS_DARKER_EXT ),
            Field ( Minus,              VkBlendOp :: VK_BLEND_OP_MINUS_EXT ),
            Field ( MinusClamped,       VkBlendOp :: VK_BLEND_OP_MINUS_CLAMPED_EXT ),
            Field ( Contrast,           VkBlendOp :: VK_BLEND_OP_CONTRAST_EXT ),
            Field ( InvertedOVG,        VkBlendOp :: VK_BLEND_OP_INVERT_OVG_EXT ),
            Field ( Red,                VkBlendOp :: VK_BLEND_OP_RED_EXT ),
            Field ( Green,              VkBlendOp :: VK_BLEND_OP_GREEN_EXT ),
            Field ( Blue,               VkBlendOp :: VK_BLEND_OP_BLUE_EXT ),
#endif
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START ENUM ( DynamicState, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Viewport,                           VkDynamicState :: VK_DYNAMIC_STATE_VIEWPORT ),
            Field ( Scissor,                            VkDynamicState :: VK_DYNAMIC_STATE_SCISSOR ),
            Field ( LineWidth,                          VkDynamicState :: VK_DYNAMIC_STATE_LINE_WIDTH ),
            Field ( DepthBias,                          VkDynamicState :: VK_DYNAMIC_STATE_DEPTH_BIAS ),
            Field ( BlendConstants,                     VkDynamicState :: VK_DYNAMIC_STATE_BLEND_CONSTANTS ),
            Field ( DepthBounds,                        VkDynamicState :: VK_DYNAMIC_STATE_DEPTH_BOUNDS ),
            Field ( CompareMask,                        VkDynamicState :: VK_DYNAMIC_STATE_STENCIL_COMPARE_MASK ),
            Field ( WriteMask,                          VkDynamicState :: VK_DYNAMIC_STATE_STENCIL_WRITE_MASK ),
            Field ( Reference,                          VkDynamicState :: VK_DYNAMIC_STATE_STENCIL_REFERENCE ),
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
            Field ( CullMode,                           VkDynamicState :: VK_DYNAMIC_STATE_CULL_MODE ),
            Field ( PrimitiveTopology,                  VkDynamicState :: VK_DYNAMIC_STATE_PRIMITIVE_TOPOLOGY ),
            Field ( ViewportWithCount,                  VkDynamicState :: VK_DYNAMIC_STATE_VIEWPORT_WITH_COUNT ),
            Field ( ScissorWithCount,                   VkDynamicState :: VK_DYNAMIC_STATE_SCISSOR_WITH_COUNT ),
            Field ( VertexInputBindingString,           VkDynamicState :: VK_DYNAMIC_STATE_VERTEX_INPUT_BINDING_STRIDE ),
            Field ( DepthTestEnable,                    VkDynamicState :: VK_DYNAMIC_STATE_DEPTH_TEST_ENABLE ),
            Field ( DepthWriteEnable,                   VkDynamicState :: VK_DYNAMIC_STATE_DEPTH_WRITE_ENABLE ),
            Field ( DepthCompareOperation,              VkDynamicState :: VK_DYNAMIC_STATE_DEPTH_COMPARE_OP ),
            Field ( DepthBoundsTestEnable,              VkDynamicState :: VK_DYNAMIC_STATE_DEPTH_BOUNDS_TEST_ENABLE ),
            Field ( StencilTestEnable,                  VkDynamicState :: VK_DYNAMIC_STATE_STENCIL_TEST_ENABLE ),
            Field ( StencilOperation,                   VkDynamicState :: VK_DYNAMIC_STATE_STENCIL_OP ),
            Field ( RasterizerDiscardEnable,            VkDynamicState :: VK_DYNAMIC_STATE_RASTERIZER_DISCARD_ENABLE ),
            Field ( DepthBiasEnable,                    VkDynamicState :: VK_DYNAMIC_STATE_DEPTH_BIAS_ENABLE ),
            Field ( PrimitiveRestartEnable,             VkDynamicState :: VK_DYNAMIC_STATE_PRIMITIVE_RESTART_ENABLE ),
#else
#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE
            Field ( CullMode,                           VkDynamicState :: VK_DYNAMIC_STATE_CULL_MODE_EXT ),
            Field ( PrimitiveTopology,                  VkDynamicState :: VK_DYNAMIC_STATE_PRIMITIVE_TOPOLOGY_EXT ),
            Field ( ViewportWithCount,                  VkDynamicState :: VK_DYNAMIC_STATE_VIEWPORT_WITH_COUNT_EXT ),
            Field ( ScissorWithCount,                   VkDynamicState :: VK_DYNAMIC_STATE_SCISSOR_WITH_COUNT_EXT ),
            Field ( VertexInputBindingString,           VkDynamicState :: VK_DYNAMIC_STATE_VERTEX_INPUT_BINDING_STRIDE_EXT ),
            Field ( DepthTestEnable,                    VkDynamicState :: VK_DYNAMIC_STATE_DEPTH_TEST_ENABLE_EXT ),
            Field ( DepthWriteEnable,                   VkDynamicState :: VK_DYNAMIC_STATE_DEPTH_WRITE_ENABLE_EXT ),
            Field ( DepthCompareOperation,              VkDynamicState :: VK_DYNAMIC_STATE_DEPTH_COMPARE_OP_EXT ),
            Field ( DepthBoundsTestEnable,              VkDynamicState :: VK_DYNAMIC_STATE_DEPTH_BOUNDS_TEST_ENABLE_EXT ),
            Field ( StencilTestEnable,                  VkDynamicState :: VK_DYNAMIC_STATE_STENCIL_TEST_ENABLE_EXT ),
            Field ( StencilOperation,                   VkDynamicState :: VK_DYNAMIC_STATE_STENCIL_OP_EXT ),
#endif
#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_2_AVAILABLE
            Field ( RasterizerDiscardEnable,            VkDynamicState :: VK_DYNAMIC_STATE_RASTERIZER_DISCARD_ENABLE_EXT ),
            Field ( DepthBiasEnable,                    VkDynamicState :: VK_DYNAMIC_STATE_DEPTH_BIAS_ENABLE_EXT ),
            Field ( PrimitiveRestartEnable,             VkDynamicState :: VK_DYNAMIC_STATE_PRIMITIVE_RESTART_ENABLE_EXT ),
#endif
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CLIP_SPACE_W_SCALING_AVAILABLE
            Field ( ViewportWScalingNVidia,             VkDynamicState :: VK_DYNAMIC_STATE_VIEWPORT_W_SCALING_NV ),
#endif
#if __C_ENG_VULKAN_API_EXTENSION_DISCARD_RECTANGLES_AVAILABLE
            Field ( DiscardRectangle,                   VkDynamicState :: VK_DYNAMIC_STATE_DISCARD_RECTANGLE_EXT ),
#endif
#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE
            Field ( SampleLocations,                    VkDynamicState :: VK_DYNAMIC_STATE_SAMPLE_LOCATIONS_EXT ),
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
            Field ( RayTracingPipelineStackSize,        VkDynamicState :: VK_DYNAMIC_STATE_RAY_TRACING_PIPELINE_STACK_SIZE_KHR ),
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE
            Field ( ViewportShadingRatePaletteNVidia,   VkDynamicState :: VK_DYNAMIC_STATE_VIEWPORT_SHADING_RATE_PALETTE_NV ),
            Field ( ViewportCoarseSampleOrderNVidia,    VkDynamicState :: VK_DYNAMIC_STATE_VIEWPORT_COARSE_SAMPLE_ORDER_NV ),
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SCISSOR_EXCLUSIVE_AVAILABLE
            Field ( ExclusiveScissorNVidia,             VkDynamicState :: VK_DYNAMIC_STATE_EXCLUSIVE_SCISSOR_NV ),
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE
            Field ( FragmentShadingRate,                VkDynamicState :: VK_DYNAMIC_STATE_FRAGMENT_SHADING_RATE_KHR ),
#endif
#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE
            Field ( LineStipple,                        VkDynamicState :: VK_DYNAMIC_STATE_LINE_STIPPLE_EXT ),
#endif
#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_INPUT_DYNAMIC_STATE_AVAILABLE
            Field ( VertexInput,                        VkDynamicState :: VK_DYNAMIC_STATE_VERTEX_INPUT_EXT ),
#endif
#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_2_AVAILABLE
            Field ( PatchControlPoints,                 VkDynamicState :: VK_DYNAMIC_STATE_PATCH_CONTROL_POINTS_EXT ),
            Field ( LogicOperation,                     VkDynamicState :: VK_DYNAMIC_STATE_LOGIC_OP_EXT ),
#endif
#if __C_ENG_VULKAN_API_EXTENSION_COLOR_WRITE_ENABLE_AVAILABLE
            Field ( ColorWriteEnable,                   VkDynamicState :: VK_DYNAMIC_STATE_COLOR_WRITE_ENABLE_EXT ),
#endif
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define C_ENG_MAP_START ENUM ( TessellationDomainOrigin,    TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( UpperLeft,  VkTessellationDomainOrigin :: VK_TESSELLATION_DOMAIN_ORIGIN_UPPER_LEFT ),
            Field ( LowerLeft,  VkTessellationDomainOrigin :: VK_TESSELLATION_DOMAIN_ORIGIN_LOWER_LEFT ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE
#define C_ENG_MAP_START ENUM ( CoarseSampleOrderTypeNVidia,    TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Default,        VkCoarseSampleOrderTypeNV :: VK_COARSE_SAMPLE_ORDER_TYPE_DEFAULT_NV ),
            Field ( Custom,         VkCoarseSampleOrderTypeNV :: VK_COARSE_SAMPLE_ORDER_TYPE_CUSTOM_NV ),
            Field ( PixelMajor,     VkCoarseSampleOrderTypeNV :: VK_COARSE_SAMPLE_ORDER_TYPE_PIXEL_MAJOR_NV ),
            Field ( SampleMajor,    VkCoarseSampleOrderTypeNV :: VK_COARSE_SAMPLE_ORDER_TYPE_SAMPLE_MAJOR_NV ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START ENUM ( ShadingRatePaletteEntryNVidia,    TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( NoInvocations,              VkShadingRatePaletteEntryNV :: VK_SHADING_RATE_PALETTE_ENTRY_NO_INVOCATIONS_NV ),
            Field ( 16InvocationsPerPixel,      VkShadingRatePaletteEntryNV :: VK_SHADING_RATE_PALETTE_ENTRY_16_INVOCATIONS_PER_PIXEL_NV ),
            Field ( 8InvocationsPerPixel,       VkShadingRatePaletteEntryNV :: VK_SHADING_RATE_PALETTE_ENTRY_8_INVOCATIONS_PER_PIXEL_NV ),
            Field ( 4InvocationsPerPixel,       VkShadingRatePaletteEntryNV :: VK_SHADING_RATE_PALETTE_ENTRY_4_INVOCATIONS_PER_PIXEL_NV ),
            Field ( 2InvocationsPerPixel,       VkShadingRatePaletteEntryNV :: VK_SHADING_RATE_PALETTE_ENTRY_2_INVOCATIONS_PER_PIXEL_NV ),
            Field ( 1InvocationPerPixel,        VkShadingRatePaletteEntryNV :: VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_PIXEL_NV ),
            Field ( 1InvocationPer2x1Pixels,    VkShadingRatePaletteEntryNV :: VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_2X1_PIXELS_NV ),
            Field ( 1InvocationPer1x2Pixels,    VkShadingRatePaletteEntryNV :: VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_1X2_PIXELS_NV ),
            Field ( 1InvocationPer2x2Pixels,    VkShadingRatePaletteEntryNV :: VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_2X2_PIXELS_NV ),
            Field ( 1InvocationPer4x2Pixels,    VkShadingRatePaletteEntryNV :: VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_4X2_PIXELS_NV ),
            Field ( 1InvocationPer2x4Pixels,    VkShadingRatePaletteEntryNV :: VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_2X4_PIXELS_NV ),
            Field ( 1InvocationPer4x4Pixels,    VkShadingRatePaletteEntryNV :: VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_4X4_PIXELS_NV ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_VIEWPORT_SWIZZLE_AVAILABLE
#define C_ENG_MAP_START ENUM ( ViewportCoordinateSwizzleNVidia,    TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( PositiveX,  VkViewportCoordinateSwizzleNV :: VK_VIEWPORT_COORDINATE_SWIZZLE_POSITIVE_X_NV ),
            Field ( NegativeX,  VkViewportCoordinateSwizzleNV :: VK_VIEWPORT_COORDINATE_SWIZZLE_NEGATIVE_X_NV ),
            Field ( PositiveY,  VkViewportCoordinateSwizzleNV :: VK_VIEWPORT_COORDINATE_SWIZZLE_POSITIVE_Y_NV ),
            Field ( NegativeY,  VkViewportCoordinateSwizzleNV :: VK_VIEWPORT_COORDINATE_SWIZZLE_NEGATIVE_Y_NV ),
            Field ( PositiveZ,  VkViewportCoordinateSwizzleNV :: VK_VIEWPORT_COORDINATE_SWIZZLE_POSITIVE_Z_NV ),
            Field ( NegativeZ,  VkViewportCoordinateSwizzleNV :: VK_VIEWPORT_COORDINATE_SWIZZLE_NEGATIVE_Z_NV ),
            Field ( PositiveW,  VkViewportCoordinateSwizzleNV :: VK_VIEWPORT_COORDINATE_SWIZZLE_POSITIVE_W_NV ),
            Field ( NegativeW,  VkViewportCoordinateSwizzleNV :: VK_VIEWPORT_COORDINATE_SWIZZLE_NEGATIVE_W_NV ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONSERVATIVE_RASTERIZATION_AVAILABLE
#define C_ENG_MAP_START ENUM ( ConservativeRasterizationMode,    TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Disabled,       VkConservativeRasterizationModeEXT :: VK_CONSERVATIVE_RASTERIZATION_MODE_DISABLED_EXT ),
            Field ( Overestimate,   VkConservativeRasterizationModeEXT :: VK_CONSERVATIVE_RASTERIZATION_MODE_OVERESTIMATE_EXT ),
            Field ( Underestimate,  VkConservativeRasterizationModeEXT :: VK_CONSERVATIVE_RASTERIZATION_MODE_UNDERESTIMATE_EXT ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE
#define C_ENG_MAP_START ENUM ( LineRasterizationMode,    TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Default,            VkLineRasterizationModeEXT :: VK_LINE_RASTERIZATION_MODE_DEFAULT_EXT ),
            Field ( Rectangular,        VkLineRasterizationModeEXT :: VK_LINE_RASTERIZATION_MODE_RECTANGULAR_EXT ),
            Field ( Bresenham,          VkLineRasterizationModeEXT :: VK_LINE_RASTERIZATION_MODE_BRESENHAM_EXT ),
            Field ( RectangularSmooth,  VkLineRasterizationModeEXT :: VK_LINE_RASTERIZATION_MODE_RECTANGULAR_SMOOTH_EXT ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE
#define C_ENG_MAP_START ENUM ( ProvokingVertexMode, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( FirstVertex,    VkProvokingVertexModeEXT :: VK_PROVOKING_VERTEX_MODE_FIRST_VERTEX_EXT ),
            Field ( LastVertex,     VkProvokingVertexModeEXT :: VK_PROVOKING_VERTEX_MODE_LAST_VERTEX_EXT ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_RASTERIZATION_ORDER_AVAILABLE
#define C_ENG_MAP_START ENUM ( RasterizationOrderAMD, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Strict,     VkRasterizationOrderAMD :: VK_RASTERIZATION_ORDER_STRICT_AMD ),
            Field ( Relaxed,    VkRasterizationOrderAMD :: VK_RASTERIZATION_ORDER_RELAXED_AMD ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAMEBUFFER_MIXED_SAMPLES_AVAILABLE
#define C_ENG_MAP_START ENUM ( CoverageModulationModeNVidia, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( None,   VkCoverageModulationModeNV :: VK_COVERAGE_MODULATION_MODE_NONE_NV ),
            Field ( RGB,    VkCoverageModulationModeNV :: VK_COVERAGE_MODULATION_MODE_RGB_NV ),
            Field ( Alpha,  VkCoverageModulationModeNV :: VK_COVERAGE_MODULATION_MODE_ALPHA_NV ),
            Field ( RGBA,   VkCoverageModulationModeNV :: VK_COVERAGE_MODULATION_MODE_RGBA_NV ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COVERAGE_REDUCTION_MODE_AVAILABLE
#define C_ENG_MAP_START ENUM ( CoverageReductionModeNVidia, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Merge,      VkCoverageReductionModeNV :: VK_COVERAGE_REDUCTION_MODE_MERGE_NV ),
            Field ( Truncate,   VkCoverageReductionModeNV :: VK_COVERAGE_REDUCTION_MODE_TRUNCATE_NV ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE
#define C_ENG_MAP_START ENUM ( BlendOverlap, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Uncorrelated,   VkBlendOverlapEXT :: VK_BLEND_OVERLAP_UNCORRELATED_EXT ),
            Field ( Disjoint,       VkBlendOverlapEXT :: VK_BLEND_OVERLAP_DISJOINT_EXT ),
            Field ( Conjoint,       VkBlendOverlapEXT :: VK_BLEND_OVERLAP_CONJOINT_EXT ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
#define C_ENG_MAP_START ENUM ( RayTracingShaderGroupType, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( General,            VkRayTracingShaderGroupTypeKHR :: VK_RAY_TRACING_SHADER_GROUP_TYPE_GENERAL_KHR ),
            Field ( TrianglesHitGroup,  VkRayTracingShaderGroupTypeKHR :: VK_RAY_TRACING_SHADER_GROUP_TYPE_TRIANGLES_HIT_GROUP_KHR ),
            Field ( ProceduralHitGroup, VkRayTracingShaderGroupTypeKHR :: VK_RAY_TRACING_SHADER_GROUP_TYPE_PROCEDURAL_HIT_GROUP_KHR ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
#define C_ENG_MAP_START ENUM ( ShaderGroupShader, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( General,        VkShaderGroupShaderKHR :: VK_SHADER_GROUP_SHADER_GENERAL_KHR ),
            Field ( ClosestHit,     VkShaderGroupShaderKHR :: VK_SHADER_GROUP_SHADER_CLOSEST_HIT_KHR ),
            Field ( AnyHit,         VkShaderGroupShaderKHR :: VK_SHADER_GROUP_SHADER_ANY_HIT_KHR ),
            Field ( Intersection,   VkShaderGroupShaderKHR :: VK_SHADER_GROUP_SHADER_INTERSECTION_KHR ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START ENUM ( PipelineCacheCreateFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
            Field ( ExternallySynchronized,     VkPipelineCacheCreateFlagBits :: VK_PIPELINE_CACHE_CREATE_EXTERNALLY_SYNCHRONIZED_BIT ),
#elif __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE
            Field ( ExternallySynchronized,     VkPipelineCacheCreateFlagBits :: VK_PIPELINE_CACHE_CREATE_EXTERNALLY_SYNCHRONIZED_BIT_EXT ),
#endif
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START ENUM ( PipelineCacheHeaderVersionValue, NO_TYPE )
#include <ObjectMapping.hpp>

        Enum {
            Field ( One,    VkPipelineCacheHeaderVersion :: VK_PIPELINE_CACHE_HEADER_VERSION_ONE ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
#define C_ENG_MAP_START ENUM ( PipelineExecutableStatisticFormat, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Bool,       VkPipelineExecutableStatisticFormatKHR :: VK_PIPELINE_EXECUTABLE_STATISTIC_FORMAT_BOOL32_KHR ),
            Field ( SInt64,     VkPipelineExecutableStatisticFormatKHR :: VK_PIPELINE_EXECUTABLE_STATISTIC_FORMAT_INT64_KHR ),
            Field ( UInt64,     VkPipelineExecutableStatisticFormatKHR :: VK_PIPELINE_EXECUTABLE_STATISTIC_FORMAT_UINT64_KHR ),
            Field ( Float64,    VkPipelineExecutableStatisticFormatKHR :: VK_PIPELINE_EXECUTABLE_STATISTIC_FORMAT_FLOAT64_KHR ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_INFO_AVAILABLE
#define C_ENG_MAP_START ENUM ( ShaderInfoTypeAMD, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Statistics,     VkShaderInfoTypeAMD :: VK_SHADER_INFO_TYPE_STATISTICS_AMD ),
            Field ( Binary,         VkShaderInfoTypeAMD :: VK_SHADER_INFO_TYPE_BINARY_AMD ),
            Field ( Disassembly,    VkShaderInfoTypeAMD :: VK_SHADER_INFO_TYPE_DISASSEMBLY_AMD ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START ENUM ( MemoryPropertyFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( DeviceLocal,        VkMemoryPropertyFlagBits :: VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT ),
            Field ( HostVisible,        VkMemoryPropertyFlagBits :: VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT ),
            Field ( HostCoherent,       VkMemoryPropertyFlagBits :: VK_MEMORY_PROPERTY_HOST_COHERENT_BIT ),
            Field ( HostCached,         VkMemoryPropertyFlagBits :: VK_MEMORY_PROPERTY_HOST_CACHED_BIT ),
            Field ( LazilyAllocated,    VkMemoryPropertyFlagBits :: VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT ),
#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
            Field ( ProtectedBit,       VkMemoryPropertyFlagBits :: VK_MEMORY_PROPERTY_PROTECTED_BIT ),
#endif
#if __C_ENG_VULKAN_API_EXTENSION_AMD_DEVICE_COHERENT_MEMORY_AVAILABLE
            Field ( DeviceCoherentAMD,  VkMemoryPropertyFlagBits :: VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD ),
            Field ( DeviceUncachedAMD,  VkMemoryPropertyFlagBits :: VK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD ),
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_RDMA_AVAILABLE
            Field ( RDMACapableNVidia,  VkMemoryPropertyFlagBits :: VK_MEMORY_PROPERTY_RDMA_CAPABLE_BIT_NV ),
#endif
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START ENUM ( MemoryHeapFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( DeviceLocal,        VkMemoryHeapFlagBits :: VK_MEMORY_HEAP_DEVICE_LOCAL_BIT ),
#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
            Field ( MultiInstance,      VkMemoryHeapFlagBits :: VK_MEMORY_HEAP_MULTI_INSTANCE_BIT ),
#endif
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define C_ENG_MAP_START ENUM ( ExternalMemoryHandleTypeFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( OpaqueFd,                   VkExternalMemoryHandleTypeFlagBits :: VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT ),
            Field ( OpaqueWin32,                VkExternalMemoryHandleTypeFlagBits :: VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT ),
            Field ( OpaqueWin32KMT,             VkExternalMemoryHandleTypeFlagBits :: VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT ),
            Field ( D3D11Texture,               VkExternalMemoryHandleTypeFlagBits :: VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_TEXTURE_BIT ),
            Field ( D3D11TextureKMT,            VkExternalMemoryHandleTypeFlagBits :: VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_TEXTURE_KMT_BIT ),
            Field ( D3D12Heap,                  VkExternalMemoryHandleTypeFlagBits :: VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D12_HEAP_BIT ),
            Field ( D3D12Resource,              VkExternalMemoryHandleTypeFlagBits :: VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D12_RESOURCE_BIT ),
#if __C_ENG_VULKAN_API_EXTENSION_EXTERNAL_DMA_BUFFER_AVAILABLE
            Field ( DMABuffer,                  VkExternalMemoryHandleTypeFlagBits :: VK_EXTERNAL_MEMORY_HANDLE_TYPE_DMA_BUF_BIT_EXT ),
#endif
#if __C_ENG_VULKAN_API_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_AVAILABLE
            Field ( HardwareBufferAndroid,      VkExternalMemoryHandleTypeFlagBits :: VK_EXTERNAL_MEMORY_HANDLE_TYPE_ANDROID_HARDWARE_BUFFER_BIT_ANDROID ),
#endif
#if __C_ENG_VULKAN_API_EXTENSION_EXTERNAL_MEMORY_HOST_AVAILABLE
            Field ( HostAllocation,             VkExternalMemoryHandleTypeFlagBits :: VK_EXTERNAL_MEMORY_HANDLE_TYPE_HOST_ALLOCATION_BIT_EXT ),
            Field ( HostMappedForeignMemory,    VkExternalMemoryHandleTypeFlagBits :: VK_EXTERNAL_MEMORY_HANDLE_TYPE_HOST_MAPPED_FOREIGN_MEMORY_BIT_EXT ),
#endif
#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_MEMORY_AVAILABLE
            Field ( ZirconVMOFuchsia,           VkExternalMemoryHandleTypeFlagBits :: VK_EXTERNAL_MEMORY_HANDLE_TYPE_ZIRCON_VMO_BIT_FUCHSIA ),
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_RDMA_AVAILABLE
            Field ( RDMAAddress,                VkExternalMemoryHandleTypeFlagBits :: VK_EXTERNAL_MEMORY_HANDLE_TYPE_RDMA_ADDRESS_BIT_NV ),
#endif
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_AVAILABLE
#define C_ENG_MAP_START ENUM ( ExternalMemoryHandleTypeFlagNVidia, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( OpaqueWin32,                VkExternalMemoryHandleTypeFlagBitsNV :: VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT_NV ),
            Field ( OpaqueWin32KMT,             VkExternalMemoryHandleTypeFlagBitsNV :: VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT_NV ),
            Field ( D3D11Image,                 VkExternalMemoryHandleTypeFlagBitsNV :: VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_IMAGE_BIT_NV ),
            Field ( D3D11ImageKMT,              VkExternalMemoryHandleTypeFlagBitsNV :: VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_IMAGE_KMT_BIT_NV ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define C_ENG_MAP_START ENUM ( MemoryAllocateFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
            Field ( DeviceMask,                 VkMemoryAllocateFlagBits :: VK_MEMORY_ALLOCATE_DEVICE_MASK_BIT ),
            Field ( DeviceAddress,              VkMemoryAllocateFlagBits :: VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT ),
            Field ( DeviceAddressCaptureReplay, VkMemoryAllocateFlagBits :: VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT ),
#endif
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define C_ENG_MAP_START ENUM ( PeerMemoryFeatureFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( CopySource,         VkPeerMemoryFeatureFlagBits :: VK_PEER_MEMORY_FEATURE_COPY_SRC_BIT ),
            Field ( CopyDestination,    VkPeerMemoryFeatureFlagBits :: VK_PEER_MEMORY_FEATURE_COPY_DST_BIT ),
            Field ( GenericSource,      VkPeerMemoryFeatureFlagBits :: VK_PEER_MEMORY_FEATURE_GENERIC_SRC_BIT ),
            Field ( GenericDestination, VkPeerMemoryFeatureFlagBits :: VK_PEER_MEMORY_FEATURE_GENERIC_DST_BIT ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START ENUM ( BufferCreateFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( SparseBinding,              VkBufferCreateFlagBits :: VK_BUFFER_CREATE_SPARSE_BINDING_BIT ),
            Field ( SparseResidency,            VkBufferCreateFlagBits :: VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT ),
            Field ( SparseAliased,              VkBufferCreateFlagBits :: VK_BUFFER_CREATE_SPARSE_ALIASED_BIT ),
#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
            Field ( Protected,                  VkBufferCreateFlagBits :: VK_BUFFER_CREATE_PROTECTED_BIT ),
#endif
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
            Field ( DeviceAddressCaptureReplay, VkBufferCreateFlagBits :: VK_BUFFER_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT ),
#endif
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START ENUM ( BufferUsageFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( TransferSource,                             VkBufferUsageFlagBits :: VK_BUFFER_USAGE_TRANSFER_SRC_BIT ),
            Field ( TransferDestination,                        VkBufferUsageFlagBits :: VK_BUFFER_USAGE_TRANSFER_DST_BIT ),
            Field ( UniformTexelBuffer,                         VkBufferUsageFlagBits :: VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT ),
            Field ( StorageTexelBuffer,                         VkBufferUsageFlagBits :: VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT ),
            Field ( UniformBuffer,                              VkBufferUsageFlagBits :: VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT ),
            Field ( StorageBuffer,                              VkBufferUsageFlagBits :: VK_BUFFER_USAGE_STORAGE_BUFFER_BIT ),
            Field ( IndexBuffer,                                VkBufferUsageFlagBits :: VK_BUFFER_USAGE_INDEX_BUFFER_BIT ),
            Field ( VertexBuffer,                               VkBufferUsageFlagBits :: VK_BUFFER_USAGE_VERTEX_BUFFER_BIT ),
            Field ( IndirectBuffer,                             VkBufferUsageFlagBits :: VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT ),
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
            Field ( ShaderDeviceAddress,                        VkBufferUsageFlagBits :: VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT ),
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_DECODE_QUEUE_AVAILABLE && __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED
            Field ( VideoDecodeSource,                          VkBufferUsageFlagBits :: VK_BUFFER_USAGE_VIDEO_DECODE_SRC_BIT_KHR ),
            Field ( VideoDecodeDestination,                     VkBufferUsageFlagBits :: VK_BUFFER_USAGE_VIDEO_DECODE_DST_BIT_KHR ),
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_ENCODE_QUEUE_AVAILABLE && __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED
            Field ( VideoEncodeSource,                          VkBufferUsageFlagBits :: VK_BUFFER_USAGE_VIDEO_ENCODE_SRC_BIT_KHR ),
            Field ( VideoEncodeDestination,                     VkBufferUsageFlagBits :: VK_BUFFER_USAGE_VIDEO_ENCODE_DST_BIT_KHR ),
#endif
#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE
            Field ( TransformFeedbackBuffer,                    VkBufferUsageFlagBits :: VK_BUFFER_USAGE_TRANSFORM_FEEDBACK_BUFFER_BIT_EXT ),
            Field ( TransformFeedbackCounterBuffer,             VkBufferUsageFlagBits :: VK_BUFFER_USAGE_TRANSFORM_FEEDBACK_COUNTER_BUFFER_BIT_EXT ),
#endif
#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE
            Field ( ConditionalRendering,                       VkBufferUsageFlagBits :: VK_BUFFER_USAGE_CONDITIONAL_RENDERING_BIT_EXT ),
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
            Field ( AccelerationStructureBuildInputReadOnly,    VkBufferUsageFlagBits :: VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR ),
            Field ( AccelerationStructureStorage,               VkBufferUsageFlagBits :: VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR ),
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
            Field ( ShaderBindingTable,                         VkBufferUsageFlagBits :: VK_BUFFER_USAGE_SHADER_BINDING_TABLE_BIT_KHR ),
#endif
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_DECODE_H264_AVAILABLE
#define C_ENG_MAP_START ENUM ( VideoDecodeH264PictureLayoutFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Progressive,                VkVideoDecodeH264PictureLayoutFlagBitsEXT :: VK_VIDEO_DECODE_H264_PICTURE_LAYOUT_PROGRESSIVE_EXT ),
            Field ( InterlacedInterleavedLines, VkVideoDecodeH264PictureLayoutFlagBitsEXT :: VK_VIDEO_DECODE_H264_PICTURE_LAYOUT_INTERLACED_INTERLEAVED_LINES_BIT_EXT ),
            Field ( InterlacedSeparatePlanes,   VkVideoDecodeH264PictureLayoutFlagBitsEXT :: VK_VIDEO_DECODE_H264_PICTURE_LAYOUT_INTERLACED_SEPARATE_PLANES_BIT_EXT ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE
#define C_ENG_MAP_START ENUM ( VideoChromaSubsamplingFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Invalid,    VkVideoChromaSubsamplingFlagBitsKHR :: VK_VIDEO_CHROMA_SUBSAMPLING_INVALID_BIT_KHR ),
            Field ( Monochrome, VkVideoChromaSubsamplingFlagBitsKHR :: VK_VIDEO_CHROMA_SUBSAMPLING_MONOCHROME_BIT_KHR ),
            Field ( 420,        VkVideoChromaSubsamplingFlagBitsKHR :: VK_VIDEO_CHROMA_SUBSAMPLING_420_BIT_KHR ),
            Field ( 422,        VkVideoChromaSubsamplingFlagBitsKHR :: VK_VIDEO_CHROMA_SUBSAMPLING_422_BIT_KHR ),
            Field ( 444,        VkVideoChromaSubsamplingFlagBitsKHR :: VK_VIDEO_CHROMA_SUBSAMPLING_444_BIT_KHR ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE
#define C_ENG_MAP_START ENUM ( VideoComponentBitDepthFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Invalid,    VkVideoComponentBitDepthFlagBitsKHR :: VK_VIDEO_COMPONENT_BIT_DEPTH_INVALID_KHR ),
            Field ( 8,          VkVideoComponentBitDepthFlagBitsKHR :: VK_VIDEO_COMPONENT_BIT_DEPTH_8_BIT_KHR ),
            Field ( 10,         VkVideoComponentBitDepthFlagBitsKHR :: VK_VIDEO_COMPONENT_BIT_DEPTH_10_BIT_KHR ),
            Field ( 12,         VkVideoComponentBitDepthFlagBitsKHR :: VK_VIDEO_COMPONENT_BIT_DEPTH_12_BIT_KHR ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START ENUM ( ImageType, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( 1D, VkImageType :: VK_IMAGE_TYPE_1D ),
            Field ( 2D, VkImageType :: VK_IMAGE_TYPE_2D ),
            Field ( 3D, VkImageType :: VK_IMAGE_TYPE_3D ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START ENUM ( ImageTiling, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Optimal,            VkImageTiling :: VK_IMAGE_TILING_OPTIMAL ),
            Field ( Linear,             VkImageTiling :: VK_IMAGE_TILING_LINEAR ),
#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_DRM_FORMAT_MODIFIER_AVAILABLE
            Field ( DrmFormatModifier,  VkImageTiling :: VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT ),
#endif
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
#define C_ENG_MAP_START ENUM ( AccelerationStructureType, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( TopLevel,       VkAccelerationStructureTypeKHR :: VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR ),
            Field ( BottomLevel,    VkAccelerationStructureTypeKHR :: VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR ),
            Field ( Generic,        VkAccelerationStructureTypeKHR :: VK_ACCELERATION_STRUCTURE_TYPE_GENERIC_KHR ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START ENUM ( BuildAccelerationStructureFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( AllowUpdate,        VkBuildAccelerationStructureFlagBitsKHR :: VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR ),
            Field ( AllowCompaction,    VkBuildAccelerationStructureFlagBitsKHR :: VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR ),
            Field ( PreferFastTrace,    VkBuildAccelerationStructureFlagBitsKHR :: VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR ),
            Field ( PreferFastBuild,    VkBuildAccelerationStructureFlagBitsKHR :: VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_BUILD_BIT_KHR ),
            Field ( LowMemory,          VkBuildAccelerationStructureFlagBitsKHR :: VK_BUILD_ACCELERATION_STRUCTURE_LOW_MEMORY_BIT_KHR ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START ENUM ( GeometryType, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Triangles,  VkGeometryTypeKHR :: VK_GEOMETRY_TYPE_TRIANGLES_KHR ),
            Field ( AABBS,      VkGeometryTypeKHR :: VK_GEOMETRY_TYPE_AABBS_KHR ),
            Field ( Instances,  VkGeometryTypeKHR :: VK_GEOMETRY_TYPE_INSTANCES_KHR ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START ENUM ( GeometryFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Opaque,                         VkGeometryFlagBitsKHR :: VK_GEOMETRY_OPAQUE_BIT_KHR ),
            Field ( NoDuplicateAnyHitInvocation,    VkGeometryFlagBitsKHR :: VK_GEOMETRY_NO_DUPLICATE_ANY_HIT_INVOCATION_BIT_KHR ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
#define C_ENG_MAP_START ENUM ( AccelerationStructureTypeNVidia, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( TopLevel,       VkAccelerationStructureTypeNV :: VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_NV ),
            Field ( BottomLevel,    VkAccelerationStructureTypeNV :: VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_NV ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START ENUM ( BuildAccelerationStructureFlagNVidia, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( AllowUpdate,        VkBuildAccelerationStructureFlagBitsNV :: VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_NV ),
            Field ( AllowCompaction,    VkBuildAccelerationStructureFlagBitsNV :: VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_NV ),
            Field ( PreferFastTrace,    VkBuildAccelerationStructureFlagBitsNV :: VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_NV ),
            Field ( PreferFastBuild,    VkBuildAccelerationStructureFlagBitsNV :: VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_BUILD_BIT_NV ),
            Field ( LowMemory,          VkBuildAccelerationStructureFlagBitsNV :: VK_BUILD_ACCELERATION_STRUCTURE_LOW_MEMORY_BIT_NV ),
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE
            Field ( Motion,             VkBuildAccelerationStructureFlagBitsNV :: VK_BUILD_ACCELERATION_STRUCTURE_MOTION_BIT_NV ),
#endif
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START ENUM ( GeometryTypeNVidia, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Triangles,  VkGeometryTypeNV :: VK_GEOMETRY_TYPE_TRIANGLES_NV ),
            Field ( AABBS,      VkGeometryTypeNV :: VK_GEOMETRY_TYPE_AABBS_NV ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START ENUM ( GeometryFlagNVidia, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Opaque,                         VkGeometryFlagBitsNV :: VK_GEOMETRY_OPAQUE_BIT_NV ),
            Field ( NoDuplicateAnyHitInvocation,    VkGeometryFlagBitsNV :: VK_GEOMETRY_NO_DUPLICATE_ANY_HIT_INVOCATION_BIT_NV ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START ENUM ( IndexType, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( UInt16,      VkIndexType :: VK_INDEX_TYPE_UINT16 ),
            Field ( UInt32,      VkIndexType :: VK_INDEX_TYPE_UINT32 ),
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
            Field ( None,        VkIndexType :: VK_INDEX_TYPE_NONE_KHR ),
#elif __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
            Field ( None,        VkIndexType :: VK_INDEX_TYPE_NONE_NV ),
#endif
#if __C_ENG_VULKAN_API_EXTENSION_INDEX_TYPE_UINT8_AVAILABLE
            Field ( UInt8,       VkIndexType :: VK_INDEX_TYPE_UINT8_EXT ),
#endif
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
#define C_ENG_MAP_START ENUM ( AccelerationStructureCreateFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( DeviceAddressCaptureReplay, VkAccelerationStructureCreateFlagBitsKHR :: VK_ACCELERATION_STRUCTURE_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT_KHR ),
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE
            Field ( MotionNVidia,               VkAccelerationStructureCreateFlagBitsKHR :: VK_ACCELERATION_STRUCTURE_CREATE_MOTION_BIT_NV ),
#endif
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
#define C_ENG_MAP_START ENUM ( AccelerationStructureBuildType, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Host,           VkAccelerationStructureBuildTypeKHR :: VK_ACCELERATION_STRUCTURE_BUILD_TYPE_HOST_KHR ),
            Field ( Device,         VkAccelerationStructureBuildTypeKHR :: VK_ACCELERATION_STRUCTURE_BUILD_TYPE_DEVICE_KHR ),
            Field ( HostOrDevice,   VkAccelerationStructureBuildTypeKHR :: VK_ACCELERATION_STRUCTURE_BUILD_TYPE_HOST_OR_DEVICE_KHR ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
#define C_ENG_MAP_START ENUM ( BuildAccelerationStructureMode, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Build,  VkBuildAccelerationStructureModeKHR :: VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR ),
            Field ( Update, VkBuildAccelerationStructureModeKHR :: VK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
#define C_ENG_MAP_START ENUM ( AccelerationStructureMemoryRequirementsTypeNVidia, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Object,         VkAccelerationStructureMemoryRequirementsTypeNV :: VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_OBJECT_NV ),
            Field ( BuildScratch,   VkAccelerationStructureMemoryRequirementsTypeNV :: VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_BUILD_SCRATCH_NV ),
            Field ( UpdateScratch,  VkAccelerationStructureMemoryRequirementsTypeNV :: VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_UPDATE_SCRATCH_NV ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START ENUM ( SamplerCreateFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE
            Field ( Subsampled,                     VkSamplerCreateFlagBits :: VK_SAMPLER_CREATE_SUBSAMPLED_BIT_EXT ),
            Field ( SubsampledCoarseReconstruction, VkSamplerCreateFlagBits :: VK_SAMPLER_CREATE_SUBSAMPLED_COARSE_RECONSTRUCTION_BIT_EXT ),
#endif
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START ENUM ( Filter, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Nearest,    VkFilter :: VK_FILTER_NEAREST ),
            Field ( Linear,     VkFilter :: VK_FILTER_LINEAR ),
#if __C_ENG_VULKAN_API_EXTENSION_FILTER_CUBIC_AVAILABLE
            Field ( Cubic,      VkFilter :: VK_FILTER_CUBIC_EXT ),
#endif
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START ENUM ( SamplerMipmapMode, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Nearest,    VkSamplerMipmapMode :: VK_SAMPLER_MIPMAP_MODE_NEAREST ),
            Field ( Linear,     VkSamplerMipmapMode :: VK_SAMPLER_MIPMAP_MODE_LINEAR ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START ENUM ( SamplerAddressMode, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Repeat,             VkSamplerAddressMode :: VK_SAMPLER_ADDRESS_MODE_REPEAT ),
            Field ( MirroredRepeat,     VkSamplerAddressMode :: VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT ),
            Field ( ClampToEdge,        VkSamplerAddressMode :: VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE ),
            Field ( ClampToBorder,      VkSamplerAddressMode :: VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER ),
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
            Field ( MirrorClampToEdge,  VkSamplerAddressMode :: VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE ),
#endif
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START ENUM ( BorderColor, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( FloatTransparentBlack,  VkBorderColor :: VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK ),
            Field ( IntTransparentBlack,    VkBorderColor :: VK_BORDER_COLOR_INT_TRANSPARENT_BLACK ),
            Field ( FloatOpaqueBlack,       VkBorderColor :: VK_BORDER_COLOR_FLOAT_OPAQUE_BLACK ),
            Field ( IntOpaqueBlack,         VkBorderColor :: VK_BORDER_COLOR_INT_OPAQUE_BLACK ),
            Field ( FloatOpaqueWhite,       VkBorderColor :: VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE ),
            Field ( IntOpaqueWhite,         VkBorderColor :: VK_BORDER_COLOR_INT_OPAQUE_WHITE ),
#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE
            Field ( FloatCustom,            VkBorderColor :: VK_BORDER_COLOR_FLOAT_CUSTOM_EXT ),
            Field ( IntCustom,              VkBorderColor :: VK_BORDER_COLOR_INT_CUSTOM_EXT ),
#endif
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
#define C_ENG_MAP_START ENUM ( SamplerReductionMode, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( WeightedAverage,    VkSamplerReductionMode :: VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE ),
            Field ( Min,                VkSamplerReductionMode :: VK_SAMPLER_REDUCTION_MODE_MIN ),
            Field ( Max,                VkSamplerReductionMode :: VK_SAMPLER_REDUCTION_MODE_MAX ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define C_ENG_MAP_START ENUM ( SamplerYCBCRModelConversion, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( RGBIdentity,    VkSamplerYcbcrModelConversion :: VK_SAMPLER_YCBCR_MODEL_CONVERSION_RGB_IDENTITY ),
            Field ( YCBCRIdentity,  VkSamplerYcbcrModelConversion :: VK_SAMPLER_YCBCR_MODEL_CONVERSION_YCBCR_IDENTITY ),
            Field ( 709,            VkSamplerYcbcrModelConversion :: VK_SAMPLER_YCBCR_MODEL_CONVERSION_YCBCR_709 ),
            Field ( 601,            VkSamplerYcbcrModelConversion :: VK_SAMPLER_YCBCR_MODEL_CONVERSION_YCBCR_601 ),
            Field ( 2020,           VkSamplerYcbcrModelConversion :: VK_SAMPLER_YCBCR_MODEL_CONVERSION_YCBCR_2020 ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define C_ENG_MAP_START ENUM ( SamplerYCBCRRange, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( ITUFull,    VkSamplerYcbcrRange :: VK_SAMPLER_YCBCR_RANGE_ITU_FULL ),
            Field ( ITUNarrow,  VkSamplerYcbcrRange :: VK_SAMPLER_YCBCR_RANGE_ITU_NARROW ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define C_ENG_MAP_START ENUM ( ChromaLocation, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( CositedEven,    VkChromaLocation :: VK_CHROMA_LOCATION_COSITED_EVEN ),
            Field ( Midpoint,       VkChromaLocation :: VK_CHROMA_LOCATION_MIDPOINT ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START ENUM ( DescriptorSetLayoutCreateFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
            Field ( UpdateAfterBindPool,    VkDescriptorSetLayoutCreateFlagBits :: VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT ),
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PUSH_DESCRIPTOR_AVAILABLE
            Field ( PushDescriptor,         VkDescriptorSetLayoutCreateFlagBits :: VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT_KHR ),
#endif
#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE
            Field ( HostOnlyPoolValve,      VkDescriptorSetLayoutCreateFlagBits :: VK_DESCRIPTOR_SET_LAYOUT_CREATE_HOST_ONLY_POOL_BIT_VALVE ),
#endif
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START ENUM ( DescriptorType, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Sampler,                        VkDescriptorType :: VK_DESCRIPTOR_TYPE_SAMPLER ),
            Field ( CombinedImageSampler,           VkDescriptorType :: VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER ),
            Field ( SampledImage,                   VkDescriptorType :: VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE ),
            Field ( StorageImage,                   VkDescriptorType :: VK_DESCRIPTOR_TYPE_STORAGE_IMAGE ),
            Field ( UniformTexelBuffer,             VkDescriptorType :: VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER ),
            Field ( StorageTexelBuffer,             VkDescriptorType :: VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER ),
            Field ( UniformBuffer,                  VkDescriptorType :: VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER ),
            Field ( StorageBuffer,                  VkDescriptorType :: VK_DESCRIPTOR_TYPE_STORAGE_BUFFER ),
            Field ( UniformBufferDynamic,           VkDescriptorType :: VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC ),
            Field ( StorageBufferDynamic,           VkDescriptorType :: VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC ),
            Field ( InputAttachment,                VkDescriptorType :: VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT ),
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
            Field ( InlineUniformBlock,             VkDescriptorType :: VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK ),
#elif __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE
            Field ( InlineUniformBlock,             VkDescriptorType :: VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK_EXT ),
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
            Field ( AccelerationStructure,          VkDescriptorType :: VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR ),
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
            Field ( AccelerationStructureNVidia,    VkDescriptorType :: VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV ),
#endif
#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE
            Field ( MutableValve,                   VkDescriptorType :: VK_DESCRIPTOR_TYPE_MUTABLE_VALVE ),
#endif
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
#define C_ENG_MAP_START ENUM ( DescriptorBindingFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( UpdateAfterBind,            VkDescriptorBindingFlagBits :: VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT ),
            Field ( UpdateUnusedWhilePending,   VkDescriptorBindingFlagBits :: VK_DESCRIPTOR_BINDING_UPDATE_UNUSED_WHILE_PENDING_BIT ),
            Field ( PartiallyBound,             VkDescriptorBindingFlagBits :: VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT ),
            Field ( VariableDescriptorCount,    VkDescriptorBindingFlagBits :: VK_DESCRIPTOR_BINDING_VARIABLE_DESCRIPTOR_COUNT_BIT ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START ENUM ( DescriptorPoolCreateFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( FreeDescriptorSet,  VkDescriptorPoolCreateFlagBits :: VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT ),
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
            Field ( UpdateAfterBind,    VkDescriptorPoolCreateFlagBits :: VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT ),
#endif
#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE
            Field ( HostOnlyValve,      VkDescriptorPoolCreateFlagBits :: VK_DESCRIPTOR_POOL_CREATE_HOST_ONLY_BIT_VALVE ),
#endif
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define C_ENG_MAP_START ENUM ( DescriptorUpdateTemplateType, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( DescriptorSet,      VkDescriptorUpdateTemplateType :: VK_DESCRIPTOR_UPDATE_TEMPLATE_TYPE_DESCRIPTOR_SET ),
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PUSH_DESCRIPTOR_AVAILABLE
            Field ( PushDescriptors,    VkDescriptorUpdateTemplateType :: VK_DESCRIPTOR_UPDATE_TEMPLATE_TYPE_PUSH_DESCRIPTORS_KHR ),
#endif
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START ENUM ( QueryType, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Occlusion,                                  VkQueryType :: VK_QUERY_TYPE_OCCLUSION ),
            Field ( PipelineStatistics,                         VkQueryType :: VK_QUERY_TYPE_PIPELINE_STATISTICS ),
            Field ( Timestamp,                                  VkQueryType :: VK_QUERY_TYPE_TIMESTAMP ),
#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE
            Field ( ResultStatusOnly,                           VkQueryType :: VK_QUERY_TYPE_RESULT_STATUS_ONLY_KHR ),
#endif
#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE
            Field ( TransformFeedbackStream,                    VkQueryType :: VK_QUERY_TYPE_TRANSFORM_FEEDBACK_STREAM_EXT ),
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
            Field ( PerformanceQuery,                           VkQueryType :: VK_QUERY_TYPE_PERFORMANCE_QUERY_KHR ),
#endif
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
            Field ( AccelerationStructureCompactedSize,         VkQueryType :: VK_QUERY_TYPE_ACCELERATION_STRUCTURE_COMPACTED_SIZE_KHR ),
            Field ( AccelerationStructureSerializationSize,     VkQueryType :: VK_QUERY_TYPE_ACCELERATION_STRUCTURE_SERIALIZATION_SIZE_KHR ),
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
            Field ( AccelerationStructureCompactedSizeNVidia,   VkQueryType :: VK_QUERY_TYPE_ACCELERATION_STRUCTURE_COMPACTED_SIZE_NV ),
#endif
#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
            Field ( PerformanceQueryIntel,                      VkQueryType :: VK_QUERY_TYPE_PERFORMANCE_QUERY_INTEL ),
#endif
#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_ENCODE_QUEUE_AVAILABLE
            Field ( VideoEncodeBitstreamBufferRange,            VkQueryType :: VK_QUERY_TYPE_VIDEO_ENCODE_BITSTREAM_BUFFER_RANGE_KHR ),
#endif
#if __C_ENG_VULKAN_API_EXTENSION_PRIMITIVES_GENERATED_QUERY_AVAILABLE
            Field ( PrimitivesGenerated,                        VkQueryType :: VK_QUERY_TYPE_PRIMITIVES_GENERATED_EXT ),
#endif
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
#define C_ENG_MAP_START ENUM ( QueryPoolSamplingModeIntel, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Manual,  VkQueryPoolSamplingModeINTEL :: VK_QUERY_POOL_SAMPLING_MODE_MANUAL_INTEL ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START ENUM ( QueryResultFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( 64,                 VkQueryResultFlagBits :: VK_QUERY_RESULT_64_BIT ),
            Field ( Wait,               VkQueryResultFlagBits :: VK_QUERY_RESULT_WAIT_BIT ),
            Field ( WithAvailability,   VkQueryResultFlagBits :: VK_QUERY_RESULT_WITH_AVAILABILITY_BIT ),
            Field ( Partial,            VkQueryResultFlagBits :: VK_QUERY_RESULT_PARTIAL_BIT ),
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE
            Field ( WithStatus,         VkQueryResultFlagBits :: VK_QUERY_RESULT_WITH_STATUS_BIT_KHR ),
#endif
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE
#define C_ENG_MAP_START ENUM ( QueryResultStatus, TYPE ( cds :: sint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Error,      VkQueryResultStatusKHR :: VK_QUERY_RESULT_STATUS_ERROR_KHR ),
            Field ( NotReady,   VkQueryResultStatusKHR :: VK_QUERY_RESULT_STATUS_NOT_READY_KHR ),
            Field ( Complete,   VkQueryResultStatusKHR :: VK_QUERY_RESULT_STATUS_COMPLETE_KHR ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START ENUM ( PipelineDepthStencilStateCreateFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
#if __C_ENG_VULKAN_API_EXTENSION_ARM_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_AVAILABLE
            Field ( RasterizationOrderAttachmentDepthAccess,    VkPipelineDepthStencilStateCreateFlagBits :: VK_PIPELINE_DEPTH_STENCIL_STATE_CREATE_RASTERIZATION_ORDER_ATTACHMENT_DEPTH_ACCESS_BIT_ARM ),
            Field ( RasterizationOrderAttachmentStencilAccess,  VkPipelineDepthStencilStateCreateFlagBits :: VK_PIPELINE_DEPTH_STENCIL_STATE_CREATE_RASTERIZATION_ORDER_ATTACHMENT_STENCIL_ACCESS_BIT_ARM ),
#endif
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
#define C_ENG_MAP_START ENUM ( PerformanceParameterTypeIntel, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( HardwareCounterSupported,   VkPerformanceParameterTypeINTEL :: VK_PERFORMANCE_PARAMETER_TYPE_HW_COUNTERS_SUPPORTED_INTEL ),
            Field ( StreamMarkerValidBits,      VkPerformanceParameterTypeINTEL :: VK_PERFORMANCE_PARAMETER_TYPE_STREAM_MARKER_VALID_BITS_INTEL ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
#define C_ENG_MAP_START ENUM ( PerformanceValueTypeIntel, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( UInt32, VkPerformanceValueTypeINTEL :: VK_PERFORMANCE_VALUE_TYPE_UINT32_INTEL ),
            Field ( UInt64, VkPerformanceValueTypeINTEL :: VK_PERFORMANCE_VALUE_TYPE_UINT64_INTEL ),
            Field ( Float,  VkPerformanceValueTypeINTEL :: VK_PERFORMANCE_VALUE_TYPE_FLOAT_INTEL ),
            Field ( Bool,   VkPerformanceValueTypeINTEL :: VK_PERFORMANCE_VALUE_TYPE_BOOL_INTEL ),
            Field ( String, VkPerformanceValueTypeINTEL :: VK_PERFORMANCE_VALUE_TYPE_STRING_INTEL ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
#define C_ENG_MAP_START ENUM ( PerformanceOverrideTypeIntel, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( NullHardware,   VkPerformanceOverrideTypeINTEL :: VK_PERFORMANCE_OVERRIDE_TYPE_NULL_HARDWARE_INTEL ),
            Field ( FlushGPUCaches, VkPerformanceOverrideTypeINTEL :: VK_PERFORMANCE_OVERRIDE_TYPE_FLUSH_GPU_CACHES_INTEL ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
#define C_ENG_MAP_START ENUM ( PerformanceConfigurationTypeIntel, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( CommandQueueMetricsDiscoveryActivated,   VkPerformanceConfigurationTypeINTEL :: VK_PERFORMANCE_CONFIGURATION_TYPE_COMMAND_QUEUE_METRICS_DISCOVERY_ACTIVATED_INTEL ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

        __C_ENG_ALIAS ( Offset2D,   VkOffset2D );
        __C_ENG_ALIAS ( Offset3D,   VkOffset3D );

        __C_ENG_ALIAS ( Extent2D,   VkExtent2D );
        __C_ENG_ALIAS ( Extent3D,   VkExtent3D );

        __C_ENG_ALIAS ( Rect,       VkRect2D );

        __C_ENG_ALIAS ( DeviceSize, VkDeviceSize );
        __C_ENG_ALIAS ( Bool,       VkBool32 );

        __C_ENG_ALIAS ( SampleMask, VkSampleMask );

        __C_ENG_ALIAS ( GenericStructure, void );

        __C_ENG_ALIAS ( DeviceAddress,                          VkDeviceAddress );

        __C_ENG_ALIAS ( InstanceHandle,                         VkInstance );
        __C_ENG_ALIAS ( PhysicalDeviceHandle,                   VkPhysicalDevice );
        __C_ENG_ALIAS ( DeviceHandle,                           VkDevice );
        __C_ENG_ALIAS ( QueueHandle,                            VkQueue );
        __C_ENG_ALIAS ( ImageHandle,                            VkImage );
        __C_ENG_ALIAS ( ImageViewHandle,                        VkImageView );
        __C_ENG_ALIAS ( CommandBufferHandle,                    VkCommandBuffer );
        __C_ENG_ALIAS ( CommandPoolHandle,                      VkCommandPool );
        __C_ENG_ALIAS ( FrameBufferHandle,                      VkFramebuffer );
        __C_ENG_ALIAS ( RenderPassHandle,                       VkRenderPass );
        __C_ENG_ALIAS ( SemaphoreHandle,                        VkSemaphore );
        __C_ENG_ALIAS ( FenceHandle,                            VkFence );
        __C_ENG_ALIAS ( EventHandle,                            VkEvent );
        __C_ENG_ALIAS ( BufferHandle,                           VkBuffer );
        __C_ENG_ALIAS ( ShaderModuleHandle,                     VkShaderModule );
        __C_ENG_ALIAS ( PipelineCacheHandle,                    VkPipelineCache );
        __C_ENG_ALIAS ( PipelineHandle,                         VkPipeline );
        __C_ENG_ALIAS ( PipelineLayoutHandle,                   VkPipelineLayout );
        __C_ENG_ALIAS ( DeviceMemoryHandle,                     VkDeviceMemory );
        __C_ENG_ALIAS ( BufferViewHandle,                       VkBufferView );
        __C_ENG_ALIAS ( SamplerHandle,                          VkSampler );
        __C_ENG_ALIAS ( DescriptorSetLayoutHandle,              VkDescriptorSetLayout );
        __C_ENG_ALIAS ( DescriptorPoolHandle,                   VkDescriptorPool );
        __C_ENG_ALIAS ( DescriptorSetHandle,                    VkDescriptorSet );
        __C_ENG_ALIAS ( QueryPoolHandle,                        VkQueryPool );

        __C_ENG_ALIAS ( InstanceCreateFlags,                    VkInstanceCreateFlags );
        __C_ENG_ALIAS ( DebugMessengerCreateFlags,              VkDebugUtilsMessengerCreateFlagsEXT );
        __C_ENG_ALIAS ( DeviceCreateFlags,                      VkDeviceCreateFlags );
        __C_ENG_ALIAS ( DeviceQueueCreateFlags,                 VkDeviceQueueCreateFlags );
        __C_ENG_ALIAS ( SampleCountFlags,                       VkSampleCountFlags );
        __C_ENG_ALIAS ( ShaderStageFlags,                       VkShaderStageFlags );
        __C_ENG_ALIAS ( QueueFlags,                             VkQueueFlags );
        __C_ENG_ALIAS ( PipelineStageFlags,                     VkFlags64 );
        __C_ENG_ALIAS ( AccessFlags,                            VkFlags64 );
        __C_ENG_ALIAS ( ImageUsageFlags,                        VkImageUsageFlags );
        __C_ENG_ALIAS ( ImageViewCreateFlags,                   VkImageViewCreateFlags );
        __C_ENG_ALIAS ( ImageAspectFlags,                       VkImageAspectFlags );
        __C_ENG_ALIAS ( CommandPoolCreateFlags,                 VkCommandPoolCreateFlags );
        __C_ENG_ALIAS ( CommandPoolResetFlags,                  VkCommandPoolResetFlags );
        __C_ENG_ALIAS ( CommandBufferResetFlags,                VkCommandBufferResetFlags );
        __C_ENG_ALIAS ( CommandBufferUsageFlags,                VkCommandBufferUsageFlags );
        __C_ENG_ALIAS ( QueryControlFlags,                      VkQueryControlFlags );
        __C_ENG_ALIAS ( QueryPipelineStatisticFlags,            VkQueryPipelineStatisticFlags );
        __C_ENG_ALIAS ( QueryPoolCreateFlags,                   VkQueryPoolCreateFlags );
        __C_ENG_ALIAS ( FenceCreateFlags,                       VkFenceCreateFlags );
        __C_ENG_ALIAS ( SemaphoreCreateFlags,                   VkSemaphoreCreateFlags );
        __C_ENG_ALIAS ( EventCreateFlags,                       VkEventCreateFlags );
        __C_ENG_ALIAS ( RenderPassCreateFlags,                  VkRenderPassCreateFlags );
        __C_ENG_ALIAS ( AttachmentDescriptionFlags,             VkAttachmentDescriptionFlags );
        __C_ENG_ALIAS ( SubpassDescriptionFlags,                VkSubpassDescriptionFlags );
        __C_ENG_ALIAS ( FrameBufferCreateFlags,                 VkFramebufferCreateFlags );
        __C_ENG_ALIAS ( ImageCreateFlags,                       VkImageCreateFlags );
        __C_ENG_ALIAS ( ShaderModuleCreateFlags,                VkShaderModuleCreateFlags );
        __C_ENG_ALIAS ( PipelineCreateFlags,                    VkPipelineCreateFlags );
        __C_ENG_ALIAS ( PipelineShaderStageCreateFlags,         VkPipelineShaderStageCreateFlags );
        __C_ENG_ALIAS ( PipelineVertexInputStateCreateFlags,    VkPipelineVertexInputStateCreateFlags );
        __C_ENG_ALIAS ( PipelineInputAssemblyStateCreateFlags,  VkPipelineInputAssemblyStateCreateFlags );
        __C_ENG_ALIAS ( PipelineTessellationStateCreateFlags,   VkPipelineTessellationStateCreateFlags );
        __C_ENG_ALIAS ( PipelineViewportStateCreateFlags,       VkPipelineViewportStateCreateFlags );
        __C_ENG_ALIAS ( PipelineRasterizationStateCreateFlags,  VkPipelineRasterizationStateCreateFlags );
        __C_ENG_ALIAS ( PipelineMultisampleStateCreateFlags,    VkPipelineMultisampleStateCreateFlags );
        __C_ENG_ALIAS ( PipelineDepthStencilStateCreateFlags,   VkPipelineDepthStencilStateCreateFlags );
        __C_ENG_ALIAS ( PipelineColorBlendStateCreateFlags,     VkPipelineColorBlendStateCreateFlags );
        __C_ENG_ALIAS ( ColorComponentFlags,                    VkColorComponentFlags );
        __C_ENG_ALIAS ( PipelineDynamicStateCreateFlags,        VkPipelineDynamicStateCreateFlags );
        __C_ENG_ALIAS ( PipelineCacheCreateFlags,               VkPipelineCacheCreateFlags );
        __C_ENG_ALIAS ( MemoryPropertyFlags,                    VkMemoryPropertyFlags );
        __C_ENG_ALIAS ( MemoryHeapFlags,                        VkMemoryHeapFlags );
        __C_ENG_ALIAS ( CullModeFlags,                          VkCullModeFlags );
        __C_ENG_ALIAS ( MemoryMapFlags,                         VkMemoryMapFlags );
        __C_ENG_ALIAS ( BufferCreateFlags,                      VkBufferCreateFlags );
        __C_ENG_ALIAS ( BufferUsageFlags,                       VkBufferUsageFlags );
        __C_ENG_ALIAS ( BufferViewCreateFlags,                  VkBufferViewCreateFlags );
        __C_ENG_ALIAS ( SamplerCreateFlags,                     VkSamplerCreateFlags );
        __C_ENG_ALIAS ( DependencyFlags,                        VkDependencyFlags );
        __C_ENG_ALIAS ( DescriptorSetLayoutCreateFlags,         VkDescriptorSetLayoutCreateFlags );
        __C_ENG_ALIAS ( PipelineLayoutCreateFlags,              VkPipelineLayoutCreateFlags );
        __C_ENG_ALIAS ( DescriptorPoolCreateFlags,              VkDescriptorPoolCreateFlags );
        __C_ENG_ALIAS ( DescriptorPoolResetFlags,               VkDescriptorPoolResetFlags );
        __C_ENG_ALIAS ( QueryResultFlags,                       VkQueryResultFlags );

        __C_ENG_ALIAS ( AllocationFunction,                     PFN_vkAllocationFunction );
        __C_ENG_ALIAS ( ReallocationFunction,                   PFN_vkReallocationFunction );
        __C_ENG_ALIAS ( FreeFunction,                           PFN_vkFreeFunction );
        __C_ENG_ALIAS ( InternalAllocationNotification,         PFN_vkInternalAllocationNotification );
        __C_ENG_ALIAS ( InternalFreeNotification,               PFN_vkInternalFreeNotification );

#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

        __C_ENG_ALIAS ( SamplerYCBCRConversionHandle,           VkSamplerYcbcrConversion );
        __C_ENG_ALIAS ( CommandPoolTrimFlags,                   VkCommandPoolTrimFlags );
        __C_ENG_ALIAS ( ExternalFenceHandleTypeFlags,           VkExternalFenceHandleTypeFlags );
        __C_ENG_ALIAS ( FenceImportFlags,                       VkFenceImportFlags );
        __C_ENG_ALIAS ( SemaphoreImportFlags,                   VkSemaphoreImportFlags );
        __C_ENG_ALIAS ( ExternalSemaphoreHandleTypeFlags,       VkExternalSemaphoreHandleTypeFlags );
        __C_ENG_ALIAS ( ExternalMemoryHandleTypeFlags,          VkExternalMemoryHandleTypeFlags );
        __C_ENG_ALIAS ( MemoryAllocateFlags,                    VkMemoryAllocateFlags );
        __C_ENG_ALIAS ( PeerMemoryFeatureFlags,                 VkPeerMemoryFeatureFlags );
        __C_ENG_ALIAS ( DescriptorUpdateTemplateHandle,         VkDescriptorUpdateTemplate );
        __C_ENG_ALIAS ( DescriptorUpdateTemplateCreateFlags,    VkDescriptorUpdateTemplateCreateFlags );


#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
        __C_ENG_ALIAS ( SemaphoreWaitFlags,                 VkSemaphoreWaitFlags );
        __C_ENG_ALIAS ( DescriptorBindingFlags,             VkDescriptorBindingFlags );
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
        __C_ENG_ALIAS ( PipelineCreationFeedbackFlags,      VkPipelineCreationFeedbackFlags );
#elif __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_FEEDBACK_AVAILABLE
        __C_ENG_ALIAS ( PipelineCreationFeedbackFlags,      VkPipelineCreationFeedbackFlagsEXT );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
        __C_ENG_ALIAS ( AcquireProfilingLockFlags,          VkAcquireProfilingLockFlagsKHR );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
        __C_ENG_ALIAS ( PerformanceConfigurationHandleIntel,    VkPerformanceConfigurationINTEL );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
        __C_ENG_ALIAS ( BuildAccelerationStructureFlags,    VkBuildAccelerationStructureFlagsKHR );
        __C_ENG_ALIAS ( AccelerationStructureHandle,        VkAccelerationStructureKHR );
        __C_ENG_ALIAS ( GeometryFlags,                      VkGeometryFlagsKHR );
        __C_ENG_ALIAS ( AccelerationStructureCreateFlags,   VkAccelerationStructureCreateFlagsKHR );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
        __C_ENG_ALIAS ( BuildAccelerationStructureFlagsNVidia,  VkBuildAccelerationStructureFlagsNV );
        __C_ENG_ALIAS ( AccelerationStructureHandleNVidia,      VkAccelerationStructureNV );
        __C_ENG_ALIAS ( GeometryFlagsNVidia,                    VkGeometryFlagsNV );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE
        __C_ENG_ALIAS ( AccelerationStructureMotionInfoFlagsNVidia,  VkAccelerationStructureMotionInfoFlagsNV );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DEFERRED_HOST_OPERATIONS_AVAILABLE
        __C_ENG_ALIAS ( DeferredOperationHandle,  VkDeferredOperationKHR );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_DECODE_H264_AVAILABLE
        __C_ENG_ALIAS ( VideoDecodeH264PictureLayoutFlags, VkVideoDecodeH264PictureLayoutFlagsEXT );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE
        __C_ENG_ALIAS ( VideoChromaSubsamplingFlags, VkVideoChromaSubsamplingFlagsKHR );
        __C_ENG_ALIAS ( VideoComponentBitDepthFlags, VkVideoComponentBitDepthFlagsKHR );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_AVAILABLE
        __C_ENG_ALIAS ( ExternalMemoryHandleTypeFlagsNVidia,  VkExternalMemoryHandleTypeFlagsNV );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAMEBUFFER_MIXED_SAMPLES_AVAILABLE
        __C_ENG_ALIAS ( PipelineCoverageModulationStateCreateFlagsNVidia,  VkPipelineCoverageModulationStateCreateFlagsNV );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_RDMA_AVAILABLE
        __C_ENG_ALIAS ( RemoteAddressNVidia,  VkRemoteAddressNV );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_COVERAGE_TO_COLOR_AVAILABLE
        __C_ENG_ALIAS ( PipelineCoverageToColorStateCreateFlagsNVidia,  VkPipelineCoverageToColorStateCreateFlagsNV );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COVERAGE_REDUCTION_MODE_AVAILABLE
        __C_ENG_ALIAS ( PipelineCoverageReductionStateCreateFlagsNVidia,  VkPipelineCoverageReductionStateCreateFlagsNV );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE
        __C_ENG_ALIAS ( PipelineRasterizationStateStreamCreateFlags,  VkPipelineRasterizationStateStreamCreateFlagsEXT );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONSERVATIVE_RASTERIZATION_AVAILABLE
        __C_ENG_ALIAS ( PipelineRasterizationConservativeStateCreateFlags,  VkPipelineRasterizationConservativeStateCreateFlagsEXT );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_ENABLE_AVAILABLE
        __C_ENG_ALIAS ( PipelineRasterizationDepthClipStateCreateFlags,  VkPipelineRasterizationDepthClipStateCreateFlagsEXT );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_PIPELINE_COMPILER_CONTROL_AVAILABLE
        __C_ENG_ALIAS ( PipelineCompilerControlFlagsAMD,    VkPipelineCompilerControlFlagsAMD );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_VIEWPORT_SWIZZLE_AVAILABLE
        __C_ENG_ALIAS ( PipelineViewportSwizzleStateCreateFlagsNVidia,  VkPipelineViewportSwizzleStateCreateFlagsNV );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISCARD_RECTANGLES_AVAILABLE
        __C_ENG_ALIAS ( PipelineDiscardRectangleStateCreateFlags,   VkPipelineDiscardRectangleStateCreateFlagsEXT );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_CACHE_AVAILABLE
        __C_ENG_ALIAS ( ValidationCacheHandle,              VkValidationCacheEXT );
        __C_ENG_ALIAS ( ValidationCacheCreateFlags,         VkValidationCacheCreateFlagsEXT );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_REPORT_AVAILABLE
        __C_ENG_ALIAS ( DebugReportFlags,               VkDebugReportFlagsEXT );
        __C_ENG_ALIAS ( DebugReportCallback,            PFN_vkDebugReportCallbackEXT );
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_AVAILABLE && ! __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

        __C_ENG_ALIAS ( CommandPoolTrimFlags,           VkCommandPoolTrimFlagsKHR );

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        __C_ENG_ALIAS ( RenderingFlags,                 VkRenderingFlags );

#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE

        __C_ENG_ALIAS ( RenderingFlags,                 VkRenderingFlagsKHR );

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DISPLAY_AVAILABLE

        __C_ENG_ALIAS ( DisplayHandle,                  VkDisplayKHR );

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_UTILS_AVAILABLE

        __C_ENG_ALIAS ( DebugMessengerHandle,           VkDebugUtilsMessengerEXT );

        __C_ENG_ALIAS ( DebugMessageSeverityFlags,      VkDebugUtilsMessageSeverityFlagsEXT );
        __C_ENG_ALIAS ( DebugMessageTypeFlags,          VkDebugUtilsMessageTypeFlagsEXT );
        __C_ENG_ALIAS ( DebugMessengerCallback,         PFN_vkDebugUtilsMessengerCallbackEXT );

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE

        __C_ENG_ALIAS ( SurfaceHandle,                  VkSurfaceKHR );
        __C_ENG_ALIAS ( SurfaceTransformFlags,          VkSurfaceTransformFlagsKHR );
        __C_ENG_ALIAS ( CompositeAlphaFlags,            VkCompositeAlphaFlagsKHR );

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISPLAY_SURFACE_COUNTER_AVAILABLE

        __C_ENG_ALIAS ( SurfaceCounterFlags,            VkSurfaceCounterFlagsEXT );

#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

        __C_ENG_ALIAS ( SubgroupFeatureFlags,           VkSubgroupFeatureFlags );

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

        __C_ENG_ALIAS ( ResolveModeFlags,               VkResolveModeFlags );

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_2_AVAILABLE

        __C_ENG_ALIAS ( ShaderCorePropertiesFlagsAMD,   VkShaderCorePropertiesFlagsAMD );

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE

        __C_ENG_ALIAS ( VideoCodecOperationFlags,       VkVideoCodecOperationFlagsKHR );

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

        __C_ENG_ALIAS ( PerformanceCounterDescriptionFlags, VkPerformanceCounterDescriptionFlagsKHR );

#endif

        __C_ENG_ALIAS ( DebugMessengerBasicNotifyCallback,  void (*) () );

#if __C_ENG_VULKAN_API_EXTENSION_DEVICE_MEMORY_REPORT_AVAILABLE

        __C_ENG_ALIAS ( DeviceMemoryReportFlags,    VkDeviceMemoryReportFlagsEXT );
        __C_ENG_ALIAS ( DeviceMemoryReportCallback, PFN_vkDeviceMemoryReportCallbackEXT );

#endif


#define C_ENG_MAP_START     STRUCT ( Version, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            cds :: uint8    variant;
            cds :: uint8    major;
            cds :: uint16   minor;
            cds :: uint16   patch;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( Viewport,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            float   x;
            float   y;
            float   width;
            float   height;
            float   minDepth;
            float   maxDepth;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( ApplicationInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )      structureType;
            Type ( GenericStructure ) * pNext;

            cds :: StringLiteral        name;
            Type ( Version )            version;

            cds :: StringLiteral        engineName;
            Type ( Version )            engineVersion;

            Type ( Version )            apiVersion;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( LayerProperties, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            char                layerName [ VK_MAX_EXTENSION_NAME_SIZE ];
            Type ( Version )    specVersion;
            cds :: uint32       implementationVersion;
            char                description [ VK_MAX_DESCRIPTION_SIZE ];
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( ExtensionProperties, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            char            name [ VK_MAX_EXTENSION_NAME_SIZE ];
            cds :: uint32   specVersion;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_REPORT_AVAILABLE
#define C_ENG_MAP_START     STRUCT ( DebugReportCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( DebugReportFlags )           flags;
            Type ( DebugReportCallback )        callback;
            void                              * pUserData;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_UTILS_AVAILABLE
#define C_ENG_MAP_START     STRUCT ( DebugMessengerCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                  structureType;
            Type ( GenericStructure )       const * pNext;
            Type ( DebugMessengerCreateFlags )      flags;
            Type ( DebugMessageSeverityFlags )      messageSeverityFlags;
            Type ( DebugMessageTypeFlags )          messageTypeFlags;
            Type ( DebugMessengerCallback )         callback;
            void                                  * pCallbackUserData;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#define C_ENG_MAP_START     STRUCT ( InstanceCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                  structureType;
            Type ( GenericStructure )             * pNext;
            Type ( InstanceCreateFlags )            flags;
            Type ( ApplicationInfo )        const * pApplicationInfo;

            cds :: uint32                           enabledLayerCount;
            cds :: StringLiteral            const * pEnabledLayerNames;

            cds :: uint32                           enabledExtensionCount;
            cds :: StringLiteral            const * pEnabledExtensionNames;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( AllocationCallbacks, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            void                                      * pUserData;
            Type ( AllocationFunction )                 allocationCallback;
            Type ( ReallocationFunction )               reallocationCallback;
            Type ( FreeFunction )                       freeCallback;
            Type ( InternalAllocationNotification )     internalAllocationNotificationCallback;
            Type ( InternalFreeNotification )           internalFreeNotificationCallback;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_FLAGS_AVAILABLE
#define C_ENG_MAP_START ENUM ( ValidationCheck, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( All,        VkValidationCheckEXT :: VK_VALIDATION_CHECK_ALL_EXT ),
            Field ( Shaders,    VkValidationCheckEXT :: VK_VALIDATION_CHECK_SHADERS_EXT ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( ValidationFlags, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            cds :: uint32                       disabledValidationCheckCount;
            Type ( ValidationCheck )    const * pDisabledValidationChecks;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#define C_ENG_MAP_START     STRUCT ( ValidationFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            cds :: uint32                               enabledValidationFeatureCount;
            Type ( ValidationFeatureEnable )    const * pEnabledValidationFeatures;
            cds :: uint32                               disabledValidationFeatureCount;
            Type ( ValidationFeatureDisable )   const * pDisabledValidationFeatures;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceLimits, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            /// largest guaranteed width to be supported by all images created of type VK_IMAGE_TYPE_1D
            cds :: uint32                       maxImageDimension1D;
            /// largest guaranteed dimension ( width / height ) to be supported by all images created of type VK_IMAGE_TYPE_2D, without VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT
            cds :: uint32                       maxImageDimension2D;
            /// largest guaranteed dimension ( width / height / depth ) to be supported by all images created of type VK_IMAGE_TYPE_3D
            cds :: uint32                       maxImageDimension3D;
            /// largest guaranteed dimension ( width / height ) to be supported by all images created of type VK_IMAGE_TYPE_2D with VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT
            cds :: uint32                       maxImageDimensionCube;
            /// max number of layers for an image
            cds :: uint32                       maxImageArrayLayers;

            /// max number of addressable texels for a buffer view created with  VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT or VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT
            cds :: uint32                       maxTexelBufferElements;

            /// max value that can be specified in the range member of a VkDescriptorBufferInfo passed to vkUpdateDescriptorSets of type VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER or VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC
            cds :: uint32                       maxUniformBufferRange;
            cds :: uint32                       maxStorageBufferRange;

            cds :: uint32                       maxPushConstantsSize;

            cds :: uint32                       maxMemoryAllocationCount;
            cds :: uint32                       maxSamplerAllocationCount;

            Type ( DeviceSize )                 bufferImageGranularity;
            Type ( DeviceSize )                 sparseAddressSpaceSize;

            cds :: uint32                       maxBoundDescriptorSets;

            cds :: uint32                       maxPerStageDescriptorSamplers;
            cds :: uint32                       maxPerStageDescriptorUniformBuffers;
            cds :: uint32                       maxPerStageDescriptorStorageBuffers;
            cds :: uint32                       maxPerStageDescriptorSampledImages;
            cds :: uint32                       maxPerStageDescriptorStorageImages;
            cds :: uint32                       maxPerStageDescriptorInputAttachments;
            cds :: uint32                       maxPerStageResources;

            cds :: uint32                       maxDescriptorSetSamplers;
            cds :: uint32                       maxDescriptorSetUniformBuffers;
            cds :: uint32                       maxDescriptorSetUniformBuffersDynamic;
            cds :: uint32                       maxDescriptorSetStorageBuffers;
            cds :: uint32                       maxDescriptorSetStorageBuffersDynamic;
            cds :: uint32                       maxDescriptorSetSampledImages;
            cds :: uint32                       maxDescriptorSetStorageImages;
            cds :: uint32                       maxDescriptorSetInputAttachments;

            cds :: uint32                       maxVertexInputAttributes;
            cds :: uint32                       maxVertexInputBindings;
            cds :: uint32                       maxVertexInputAttributeOffset;
            cds :: uint32                       maxVertexInputBindingStride;
            cds :: uint32                       maxVertexOutputComponents;

            cds :: uint32                       maxTessellationGenerationLevel;
            cds :: uint32                       maxTessellationPatchSize;
            cds :: uint32                       maxTessellationControlPerVertexInputComponents;
            cds :: uint32                       maxTessellationControlPerVertexOutputComponents;
            cds :: uint32                       maxTessellationControlPerPatchOutputComponents;
            cds :: uint32                       maxTessellationControlTotalOutputComponents;
            cds :: uint32                       maxTessellationEvaluationInputComponents;
            cds :: uint32                       maxTessellationEvaluationOutputComponents;

            cds :: uint32                       maxGeometryShaderInvocations;
            cds :: uint32                       maxGeometryInputComponents;
            cds :: uint32                       maxGeometryOutputComponents;
            cds :: uint32                       maxGeometryOutputVertices;
            cds :: uint32                       maxGeometryTotalOutputComponents;

            cds :: uint32                       maxFragmentInputComponents;
            cds :: uint32                       maxFragmentOutputAttachments;
            cds :: uint32                       maxFragmentDualSourceAttachments;
            cds :: uint32                       maxFragmentCombinedOutputResources;

            cds :: uint32                       maxComputeSharedMemorySize;
            cds :: uint32                       maxComputeWorkGroupCount[3];
            cds :: uint32                       maxComputeWorkGroupInvocations;
            cds :: uint32                       maxComputeWorkGroupSize[3];

            cds :: uint32                       subPixelPrecisionBits;
            cds :: uint32                       subTexelPrecisionBits;

            cds :: uint32                       mipmapPrecisionBits;

            cds :: uint32                       maxDrawIndexedIndexValue;
            cds :: uint32                       maxDrawIndirectCount;

            float                               maxSamplerLodBias;
            float                               maxSamplerAnisotropy;

            cds :: uint32                       maxViewports;
            cds :: uint32                       maxViewportDimensions[2];
            float                               viewportBoundsRange[2];
            cds :: uint32                       viewportSubPixelBits;

            cds :: Size                         minMemoryMapAlignment;

            Type ( DeviceSize )                 minTexelBufferOffsetAlignment;
            Type ( DeviceSize )                 minUniformBufferOffsetAlignment;
            Type ( DeviceSize )                 minStorageBufferOffsetAlignment;

            cds :: sint32                       minTexelOffset;
            cds :: uint32                       maxTexelOffset;
            cds :: sint32                       minTexelGatherOffset;
            cds :: uint32                       maxTexelGatherOffset;

            float                               minInterpolationOffset;
            float                               maxInterpolationOffset;
            cds :: uint32                       subPixelInterpolationOffsetBits;

            cds :: uint32                       maxFramebufferWidth;
            cds :: uint32                       maxFramebufferHeight;
            cds :: uint32                       maxFramebufferLayers;

            Type ( SampleCountFlags )           framebufferColorSampleCounts;
            Type ( SampleCountFlags )           framebufferDepthSampleCounts;
            Type ( SampleCountFlags )           framebufferStencilSampleCounts;
            Type ( SampleCountFlags )           framebufferNoAttachmentsSampleCounts;

            cds :: uint32                       maxColorAttachments;

            Type ( SampleCountFlags )           sampledImageColorSampleCounts;
            Type ( SampleCountFlags )           sampledImageIntegerSampleCounts;
            Type ( SampleCountFlags )           sampledImageDepthSampleCounts;
            Type ( SampleCountFlags )           sampledImageStencilSampleCounts;
            Type ( SampleCountFlags )           storageImageSampleCounts;

            cds :: uint32                       maxSampleMaskWords;

            Type ( Bool )                       timestampComputeAndGraphics;
            float                               timestampPeriod;

            cds :: uint32                       maxClipDistances;
            cds :: uint32                       maxCullDistances;
            cds :: uint32                       maxCombinedClipAndCullDistances;

            cds :: uint32                       discreteQueuePriorities;

            float                               pointSizeRange[2];
            float                               lineWidthRange[2];
            float                               pointSizeGranularity;
            float                               lineWidthGranularity;
            Type ( Bool )                       strictLines;

            Type ( Bool )                       standardSampleLocations;

            Type ( DeviceSize )                 optimalBufferCopyOffsetAlignment;
            Type ( DeviceSize )                 optimalBufferCopyRowPitchAlignment;

            Type ( DeviceSize )                 nonCoherentAtomSize;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceSparseProperties,    NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( Bool ) residencyStandard2DBlockShape;
            Type ( Bool ) residencyStandard2DMultisampleBlockShape;
            Type ( Bool ) residencyStandard3DBlockShape;
            Type ( Bool ) residencyAlignedMipSize;
            Type ( Bool ) residencyNonResidentStrict;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceProperties,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( Version )                        apiVersion;
            cds :: uint32                           driverVersion;
            cds :: uint32                           vendorID;
            cds :: uint32                           deviceID;
            Type ( PhysicalDeviceType )             deviceType;
            char                                    deviceName [ VK_MAX_PHYSICAL_DEVICE_NAME_SIZE ];
            cds :: uint8                            pipelineCacheUUID [ VK_UUID_SIZE ];
            Type ( PhysicalDeviceLimits )           limits;
            Type ( PhysicalDeviceSparseProperties ) sparseProperties;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceExtendedProperties,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                  structureType;
            Type ( GenericStructure )             * pNext;
            Type ( PhysicalDeviceProperties )       properties;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( GenericInStructure,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericInStructure )         const * pNext;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( GenericOutStructure,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericOutStructure )              * pNext;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( CommandPoolCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( CommandPoolCreateFlags )     flags;
            cds :: uint32                       queueFamilyIndex;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( CommandBufferAllocateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( CommandPoolHandle )          commandPool;
            Type ( CommandBufferLevel )         level;
            cds :: uint32                       commandBufferCount;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( CommandBufferInheritanceInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            Type ( RenderPassHandle )                       renderPass;
            cds :: uint32                                   subpass;
            Type ( FrameBufferHandle )                      frameBuffer;
            Type ( Bool )                                   occlusionQueryEnable;
            Type ( QueryControlFlags )                      queryFlags;
            Type ( QueryPipelineStatisticFlags )            pipelineStatistics;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( CommandBufferBeginInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            Type ( CommandBufferUsageFlags )                flags;
            Type ( CommandBufferInheritanceInfo )   const * pInheritanceInfo;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DEVICE_GROUP_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( DeviceGroupCommandBufferBeginInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            cds :: uint32                       deviceMask;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_GET_SURFACE_CAPABILITIES_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( SurfaceFormat2,    NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )      structureType;
            Type ( GenericStructure ) * pNext;
            Type ( SurfaceFormat )      surfaceFormat;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceSurfaceInfo,    NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( SurfaceHandle )              surface;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_FULL_SCREEN_EXCLUSIVE_AVAILABLE

#define C_ENG_MAP_START     ENUM ( FullScreenExclusive,    TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Default,                VkFullScreenExclusiveEXT :: VK_FULL_SCREEN_EXCLUSIVE_DEFAULT_EXT ),
            Field ( Allowed,                VkFullScreenExclusiveEXT :: VK_FULL_SCREEN_EXCLUSIVE_ALLOWED_EXT ),
            Field ( Disallowed,             VkFullScreenExclusiveEXT :: VK_FULL_SCREEN_EXCLUSIVE_DISALLOWED_EXT ),
            Field ( ApplicationControlled,  VkFullScreenExclusiveEXT :: VK_FULL_SCREEN_EXCLUSIVE_APPLICATION_CONTROLLED_EXT ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( SurfaceFullScreenExclusiveInfo,    NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( FullScreenExclusive )        fullScreenExclusive
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( DeviceQueueGlobalPriorityCreateInfo,   NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( QueueGlobalPriority )                globalPriority;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( DeviceQueueCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( DeviceQueueCreateFlags )             flags;
            cds :: uint32                                       queueFamilyIndex;
            cds :: uint32                                       queueCount;
            float                                       const * pQueuePriorities;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceFeatures,    NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( Bool )   robustBufferAccess;
            __C_ENG_TYPE ( Bool )   fullDrawIndexUint32;
            __C_ENG_TYPE ( Bool )   imageCubeArray;
            __C_ENG_TYPE ( Bool )   independentBlend;
            __C_ENG_TYPE ( Bool )   geometryShader;
            __C_ENG_TYPE ( Bool )   tessellationShader;
            __C_ENG_TYPE ( Bool )   sampleRateShading;
            __C_ENG_TYPE ( Bool )   dualSrcBlend;
            __C_ENG_TYPE ( Bool )   logicOp;
            __C_ENG_TYPE ( Bool )   multiDrawIndirect;
            __C_ENG_TYPE ( Bool )   drawIndirectFirstInstance;
            __C_ENG_TYPE ( Bool )   depthClamp;
            __C_ENG_TYPE ( Bool )   depthBiasClamp;
            __C_ENG_TYPE ( Bool )   fillModeNonSolid;
            __C_ENG_TYPE ( Bool )   depthBounds;
            __C_ENG_TYPE ( Bool )   wideLines;
            __C_ENG_TYPE ( Bool )   largePoints;
            __C_ENG_TYPE ( Bool )   alphaToOne;
            __C_ENG_TYPE ( Bool )   multiViewport;
            __C_ENG_TYPE ( Bool )   samplerAnisotropy;
            __C_ENG_TYPE ( Bool )   textureCompressionETC2;
            __C_ENG_TYPE ( Bool )   textureCompressionASTC_LDR;
            __C_ENG_TYPE ( Bool )   textureCompressionBC;
            __C_ENG_TYPE ( Bool )   occlusionQueryPrecise;
            __C_ENG_TYPE ( Bool )   pipelineStatisticsQuery;
            __C_ENG_TYPE ( Bool )   vertexPipelineStoresAndAtomics;
            __C_ENG_TYPE ( Bool )   fragmentStoresAndAtomics;
            __C_ENG_TYPE ( Bool )   shaderTessellationAndGeometryPointSize;
            __C_ENG_TYPE ( Bool )   shaderImageGatherExtended;
            __C_ENG_TYPE ( Bool )   shaderStorageImageExtendedFormats;
            __C_ENG_TYPE ( Bool )   shaderStorageImageMultisample;
            __C_ENG_TYPE ( Bool )   shaderStorageImageReadWithoutFormat;
            __C_ENG_TYPE ( Bool )   shaderStorageImageWriteWithoutFormat;
            __C_ENG_TYPE ( Bool )   shaderUniformBufferArrayDynamicIndexing;
            __C_ENG_TYPE ( Bool )   shaderSampledImageArrayDynamicIndexing;
            __C_ENG_TYPE ( Bool )   shaderStorageBufferArrayDynamicIndexing;
            __C_ENG_TYPE ( Bool )   shaderStorageImageArrayDynamicIndexing;
            __C_ENG_TYPE ( Bool )   shaderClipDistance;
            __C_ENG_TYPE ( Bool )   shaderCullDistance;
            __C_ENG_TYPE ( Bool )   shaderFloat64;
            __C_ENG_TYPE ( Bool )   shaderInt64;
            __C_ENG_TYPE ( Bool )   shaderInt16;
            __C_ENG_TYPE ( Bool )   shaderResourceResidency;
            __C_ENG_TYPE ( Bool )   shaderResourceMinLod;
            __C_ENG_TYPE ( Bool )   sparseBinding;
            __C_ENG_TYPE ( Bool )   sparseResidencyBuffer;
            __C_ENG_TYPE ( Bool )   sparseResidencyImage2D;
            __C_ENG_TYPE ( Bool )   sparseResidencyImage3D;
            __C_ENG_TYPE ( Bool )   sparseResidency2Samples;
            __C_ENG_TYPE ( Bool )   sparseResidency4Samples;
            __C_ENG_TYPE ( Bool )   sparseResidency8Samples;
            __C_ENG_TYPE ( Bool )   sparseResidency16Samples;
            __C_ENG_TYPE ( Bool )   sparseResidencyAliased;
            __C_ENG_TYPE ( Bool )   variableMultisampleRate;
            __C_ENG_TYPE ( Bool )   inheritedQueries;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( DeviceCreateInfo,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )           const * pNext;
            __C_ENG_TYPE ( DeviceCreateFlags )                  flags;
            cds :: uint32                                       queueCreateInfoCount;
            __C_ENG_TYPE ( DeviceQueueCreateInfo )      const * pQueueCreateInfos;

#if ! __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

            cds :: uint32                                       enabledLayerCount;
            cds :: StringLiteral                        const * pEnabledLayerNames;

#endif

            cds :: uint32                                       enabledExtensionCount;
            cds :: StringLiteral                        const * pEnabledExtensionNames;
            __C_ENG_TYPE ( PhysicalDeviceFeatures )     const * pEnabledFeatures;

        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE


#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceExtendedFeatures,    NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )          structureType;
            __C_ENG_TYPE ( GenericStructure )     * pNext;
            __C_ENG_TYPE ( PhysicalDeviceFeatures ) features;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceVulkan11Properties,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )          structureType;
            __C_ENG_TYPE ( GenericStructure )     * pNext;
            cds :: uint8                            deviceUUID [ VK_UUID_SIZE ];
            cds :: uint8                            driverUUID [ VK_UUID_SIZE ];
            cds :: uint8                            deviceLUID [ VK_LUID_SIZE ];
            cds :: uint32                           deviceNodeMask;
            __C_ENG_TYPE ( Bool )                   deviceLUIDValid;
            cds :: uint32                           subgroupSize;
            __C_ENG_TYPE ( ShaderStageFlags )       subgroupSupportedStages;
            __C_ENG_TYPE ( SubgroupFeatureFlags )   subgroupSupportedOperations;
            __C_ENG_TYPE ( Bool )                   subgroupQuadOperationsInAllStages;
            __C_ENG_TYPE ( PointClippingBehavior )  pointClippingBehavior;
            cds :: uint32                           maxMultiviewViewCount;
            cds :: uint32                           maxMultiviewInstanceIndex;
            __C_ENG_TYPE ( Bool )                   protectedNoFault;
            cds :: uint32                           maxPerSetDescriptors;
            __C_ENG_TYPE ( DeviceSize )             maxMemoryAllocationSize;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceIDProperties,    NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )          structureType;
            __C_ENG_TYPE ( GenericStructure )     * pNext;
            cds :: uint8                            deviceUUID [ VK_UUID_SIZE ];
            cds :: uint8                            driverUUID [ VK_UUID_SIZE ];
            cds :: uint8                            deviceLUID [ VK_LUID_SIZE ];
            cds :: uint32                           deviceNodeMask;
            __C_ENG_TYPE ( Bool )                   deviceLUIDValid;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceMaintenanceProperties,    NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )          structureType;
            __C_ENG_TYPE ( GenericStructure )     * pNext;
            cds :: uint32                           maxPerSetDescriptors;
            __C_ENG_TYPE ( DeviceSize )             maxMemoryAllocationSize;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceMultiviewProperties,    NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )          structureType;
            __C_ENG_TYPE ( GenericStructure )     * pNext;
            cds :: uint32                           maxMultiviewViewCount;
            cds :: uint32                           maxMultiviewInstanceIndex;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( PhysicalDevicePointClippingProperties,    NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )          structureType;
            __C_ENG_TYPE ( GenericStructure )     * pNext;
            __C_ENG_TYPE ( PointClippingBehavior )  pointClippingBehavior;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceProtectedMemoryProperties,    NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )          structureType;
            __C_ENG_TYPE ( GenericStructure )     * pNext;
            __C_ENG_TYPE ( Bool )                   protectedNoFault;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceSubgroupProperties,    NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )          structureType;
            __C_ENG_TYPE ( GenericStructure )     * pNext;
            cds :: uint32                           subgroupSize;
            __C_ENG_TYPE ( ShaderStageFlags )       supportedStages;
            __C_ENG_TYPE ( SubgroupFeatureFlags )   supportedOperations;
            __C_ENG_TYPE ( Bool )                   quadOperationsInAllStages;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceGroupProperties, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )          structureType;
            __C_ENG_TYPE ( GenericStructure )     * pNext;
            cds :: uint32                           physicalDeviceCount;
            __C_ENG_TYPE ( PhysicalDeviceHandle )   physicalDevices [ VK_MAX_DEVICE_GROUP_SIZE ];
            __C_ENG_TYPE ( Bool )                   subsetAllocation;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( ConformanceVersion,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            cds :: uint8    major;
            cds :: uint8    minor;
            cds :: uint8    subminor;
            cds :: uint8    patch;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceVulkan12Properties,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;

            __C_ENG_TYPE ( DriverID )                           driverID;
            char                                                driverName [ VK_MAX_DRIVER_NAME_SIZE ];
            char                                                driverInfo [ VK_MAX_DRIVER_INFO_SIZE ];
            __C_ENG_TYPE ( ConformanceVersion )                 conformanceVersion;

            __C_ENG_TYPE ( ShaderFloatControlsIndependence )    denormBehaviorIndependence;
            __C_ENG_TYPE ( ShaderFloatControlsIndependence )    roundingModeIndependence;

            __C_ENG_TYPE ( Bool )                               shaderSignedZeroInfNanPreserveFloat16;
            __C_ENG_TYPE ( Bool )                               shaderSignedZeroInfNanPreserveFloat32;
            __C_ENG_TYPE ( Bool )                               shaderSignedZeroInfNanPreserveFloat64;

            __C_ENG_TYPE ( Bool )                               shaderDenormPreserveFloat16;
            __C_ENG_TYPE ( Bool )                               shaderDenormPreserveFloat32;
            __C_ENG_TYPE ( Bool )                               shaderDenormPreserveFloat64;
            __C_ENG_TYPE ( Bool )                               shaderDenormFlushToZeroFloat16;
            __C_ENG_TYPE ( Bool )                               shaderDenormFlushToZeroFloat32;
            __C_ENG_TYPE ( Bool )                               shaderDenormFlushToZeroFloat64;

            __C_ENG_TYPE ( Bool )                               shaderRoundingModeRTEFloat16;
            __C_ENG_TYPE ( Bool )                               shaderRoundingModeRTEFloat32;
            __C_ENG_TYPE ( Bool )                               shaderRoundingModeRTEFloat64;
            __C_ENG_TYPE ( Bool )                               shaderRoundingModeRTZFloat16;
            __C_ENG_TYPE ( Bool )                               shaderRoundingModeRTZFloat32;
            __C_ENG_TYPE ( Bool )                               shaderRoundingModeRTZFloat64;

            cds :: uint32                                       maxUpdateAfterBindDescriptorsInAllPools;

            __C_ENG_TYPE ( Bool )                               shaderUniformBufferArrayNonUniformIndexingNative;
            __C_ENG_TYPE ( Bool )                               shaderSampledImageArrayNonUniformIndexingNative;
            __C_ENG_TYPE ( Bool )                               shaderStorageBufferArrayNonUniformIndexingNative;
            __C_ENG_TYPE ( Bool )                               shaderStorageImageArrayNonUniformIndexingNative;
            __C_ENG_TYPE ( Bool )                               shaderInputAttachmentArrayNonUniformIndexingNative;

            __C_ENG_TYPE ( Bool )                               robustBufferAccessUpdateAfterBind;

            __C_ENG_TYPE ( Bool )                               quadDivergentImplicitLod;

            cds :: uint32                                       maxPerStageDescriptorUpdateAfterBindSamplers;
            cds :: uint32                                       maxPerStageDescriptorUpdateAfterBindUniformBuffers;
            cds :: uint32                                       maxPerStageDescriptorUpdateAfterBindStorageBuffers;
            cds :: uint32                                       maxPerStageDescriptorUpdateAfterBindSampledImages;
            cds :: uint32                                       maxPerStageDescriptorUpdateAfterBindStorageImages;
            cds :: uint32                                       maxPerStageDescriptorUpdateAfterBindInputAttachments;

            cds :: uint32                                       maxPerStageUpdateAfterBindResources;

            cds :: uint32                                       maxDescriptorSetUpdateAfterBindSamplers;
            cds :: uint32                                       maxDescriptorSetUpdateAfterBindUniformBuffers;
            cds :: uint32                                       maxDescriptorSetUpdateAfterBindUniformBuffersDynamic;
            cds :: uint32                                       maxDescriptorSetUpdateAfterBindStorageBuffers;
            cds :: uint32                                       maxDescriptorSetUpdateAfterBindStorageBuffersDynamic;
            cds :: uint32                                       maxDescriptorSetUpdateAfterBindSampledImages;
            cds :: uint32                                       maxDescriptorSetUpdateAfterBindStorageImages;
            cds :: uint32                                       maxDescriptorSetUpdateAfterBindInputAttachments;

            __C_ENG_TYPE ( ResolveModeFlags )                   supportedDepthResolveModes;
            __C_ENG_TYPE ( ResolveModeFlags )                   supportedStencilResolveModes;

            __C_ENG_TYPE ( Bool )                               independentResolveNone;
            __C_ENG_TYPE ( Bool )                               independentResolve;

            __C_ENG_TYPE ( Bool )                               filterMinmaxSingleComponentFormats;
            __C_ENG_TYPE ( Bool )                               filterMinmaxImageComponentMapping;

            cds :: uint64                                       maxTimelineSemaphoreValueDifference;

            __C_ENG_TYPE ( SampleCountFlags )                   framebufferIntegerColorSampleCounts;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceDriverProperties,    NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;

            __C_ENG_TYPE ( DriverID )                           driverID;
            char                                                driverName [ VK_MAX_DRIVER_NAME_SIZE ];
            char                                                driverInfo [ VK_MAX_DRIVER_INFO_SIZE ];
            __C_ENG_TYPE ( ConformanceVersion )                 conformanceVersion;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceDepthStencilResolveProperties,   NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;

            __C_ENG_TYPE ( ResolveModeFlags )                   supportedDepthResolveModes;
            __C_ENG_TYPE ( ResolveModeFlags )                   supportedStencilResolveModes;
            __C_ENG_TYPE ( Bool )                               independentResolveNone;
            __C_ENG_TYPE ( Bool )                               independentResolve;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceDescriptorIndexingProperties,   NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )      structureType;
            __C_ENG_TYPE ( GenericStructure ) * pNext;

            cds :: uint32                       maxUpdateAfterBindDescriptorsInAllPools;

            __C_ENG_TYPE ( Bool )               shaderUniformBufferArrayNonUniformIndexingNative;
            __C_ENG_TYPE ( Bool )               shaderSampledImageArrayNonUniformIndexingNative;
            __C_ENG_TYPE ( Bool )               shaderStorageBufferArrayNonUniformIndexingNative;
            __C_ENG_TYPE ( Bool )               shaderStorageImageArrayNonUniformIndexingNative;
            __C_ENG_TYPE ( Bool )               shaderInputAttachmentArrayNonUniformIndexingNative;

            __C_ENG_TYPE ( Bool )               robustBufferAccessUpdateAfterBind;

            __C_ENG_TYPE ( Bool )               quadDivergentImplicitLod;

            cds :: uint32                       maxPerStageDescriptorUpdateAfterBindSamplers;
            cds :: uint32                       maxPerStageDescriptorUpdateAfterBindUniformBuffers;
            cds :: uint32                       maxPerStageDescriptorUpdateAfterBindStorageBuffers;
            cds :: uint32                       maxPerStageDescriptorUpdateAfterBindSampledImages;
            cds :: uint32                       maxPerStageDescriptorUpdateAfterBindStorageImages;
            cds :: uint32                       maxPerStageDescriptorUpdateAfterBindInputAttachments;

            cds :: uint32                       maxPerStageUpdateAfterBindResources;

            cds :: uint32                       maxDescriptorSetUpdateAfterBindSamplers;
            cds :: uint32                       maxDescriptorSetUpdateAfterBindUniformBuffers;
            cds :: uint32                       maxDescriptorSetUpdateAfterBindUniformBuffersDynamic;
            cds :: uint32                       maxDescriptorSetUpdateAfterBindStorageBuffers;
            cds :: uint32                       maxDescriptorSetUpdateAfterBindStorageBuffersDynamic;
            cds :: uint32                       maxDescriptorSetUpdateAfterBindSampledImages;
            cds :: uint32                       maxDescriptorSetUpdateAfterBindStorageImages;
            cds :: uint32                       maxDescriptorSetUpdateAfterBindInputAttachments;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceFloatControlsProperties,   NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;

            __C_ENG_TYPE ( ShaderFloatControlsIndependence )    denormBehaviorIndependence;
            __C_ENG_TYPE ( ShaderFloatControlsIndependence )    roundingModeIndependence;

            __C_ENG_TYPE ( Bool )                               shaderSignedZeroInfNanPreserveFloat16;
            __C_ENG_TYPE ( Bool )                               shaderSignedZeroInfNanPreserveFloat32;
            __C_ENG_TYPE ( Bool )                               shaderSignedZeroInfNanPreserveFloat64;

            __C_ENG_TYPE ( Bool )                               shaderDenormPreserveFloat16;
            __C_ENG_TYPE ( Bool )                               shaderDenormPreserveFloat32;
            __C_ENG_TYPE ( Bool )                               shaderDenormPreserveFloat64;
            __C_ENG_TYPE ( Bool )                               shaderDenormFlushToZeroFloat16;
            __C_ENG_TYPE ( Bool )                               shaderDenormFlushToZeroFloat32;
            __C_ENG_TYPE ( Bool )                               shaderDenormFlushToZeroFloat64;

            __C_ENG_TYPE ( Bool )                               shaderRoundingModeRTEFloat16;
            __C_ENG_TYPE ( Bool )                               shaderRoundingModeRTEFloat32;
            __C_ENG_TYPE ( Bool )                               shaderRoundingModeRTEFloat64;
            __C_ENG_TYPE ( Bool )                               shaderRoundingModeRTZFloat16;
            __C_ENG_TYPE ( Bool )                               shaderRoundingModeRTZFloat32;
            __C_ENG_TYPE ( Bool )                               shaderRoundingModeRTZFloat64;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceSamplerFilterMinmaxProperties,   NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               filterMinmaxSingleComponentFormats;
            __C_ENG_TYPE ( Bool )                               filterMinmaxImageComponentMapping;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceTimelineSemaphoreProperties,   NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            cds :: uint64                                       maxTimelineSemaphoreValueDifference;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceVulkan13Properties,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )      structureType;
            __C_ENG_TYPE ( GenericStructure ) * pNext;
            cds :: uint32                       minSubgroupSize;
            cds :: uint32                       maxSubgroupSize;
            cds :: uint32                       maxComputeWorkgroupSubgroups;
            __C_ENG_TYPE ( ShaderStageFlags )   requiredSubgroupSizeStages;
            cds :: uint32                       maxInlineUniformBlockSize;
            cds :: uint32                       maxPerStageDescriptorInlineUniformBlocks;
            cds :: uint32                       maxPerStageDescriptorUpdateAfterBindInlineUniformBlocks;
            cds :: uint32                       maxDescriptorSetInlineUniformBlocks;
            cds :: uint32                       maxDescriptorSetUpdateAfterBindInlineUniformBlocks;
            cds :: uint32                       maxInlineUniformTotalSize;
            __C_ENG_TYPE ( Bool )               integerDotProduct8BitUnsignedAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProduct8BitSignedAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProduct8BitMixedSignednessAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProduct4x8BitPackedUnsignedAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProduct4x8BitPackedSignedAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProduct4x8BitPackedMixedSignednessAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProduct16BitUnsignedAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProduct16BitSignedAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProduct16BitMixedSignednessAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProduct32BitUnsignedAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProduct32BitSignedAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProduct32BitMixedSignednessAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProduct64BitUnsignedAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProduct64BitSignedAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProduct64BitMixedSignednessAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProductAccumulatingSaturating8BitUnsignedAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProductAccumulatingSaturating8BitSignedAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProductAccumulatingSaturating8BitMixedSignednessAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProductAccumulatingSaturating4x8BitPackedUnsignedAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProductAccumulatingSaturating4x8BitPackedSignedAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProductAccumulatingSaturating4x8BitPackedMixedSignednessAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProductAccumulatingSaturating16BitUnsignedAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProductAccumulatingSaturating16BitSignedAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProductAccumulatingSaturating16BitMixedSignednessAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProductAccumulatingSaturating32BitUnsignedAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProductAccumulatingSaturating32BitSignedAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProductAccumulatingSaturating32BitMixedSignednessAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProductAccumulatingSaturating64BitUnsignedAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProductAccumulatingSaturating64BitSignedAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProductAccumulatingSaturating64BitMixedSignednessAccelerated;
            __C_ENG_TYPE ( DeviceSize )         storageTexelBufferOffsetAlignmentBytes;
            __C_ENG_TYPE ( Bool )               storageTexelBufferOffsetSingleTexelAlignment;
            __C_ENG_TYPE ( DeviceSize )         uniformTexelBufferOffsetAlignmentBytes;
            __C_ENG_TYPE ( Bool )               uniformTexelBufferOffsetSingleTexelAlignment;
            __C_ENG_TYPE ( DeviceSize )         maxBufferSize;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceVulkan13Features,    NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )      structureType;
            __C_ENG_TYPE ( GenericStructure ) * pNext;
            __C_ENG_TYPE ( Bool )               robustImageAccess;
            __C_ENG_TYPE ( Bool )               inlineUniformBlock;
            __C_ENG_TYPE ( Bool )               descriptorBindingInlineUniformBlockUpdateAfterBind;
            __C_ENG_TYPE ( Bool )               pipelineCreationCacheControl;
            __C_ENG_TYPE ( Bool )               privateData;
            __C_ENG_TYPE ( Bool )               shaderDemoteToHelperInvocation;
            __C_ENG_TYPE ( Bool )               shaderTerminateInvocation;
            __C_ENG_TYPE ( Bool )               subgroupSizeControl;
            __C_ENG_TYPE ( Bool )               computeFullSubgroups;
            __C_ENG_TYPE ( Bool )               synchronization2;
            __C_ENG_TYPE ( Bool )               textureCompressionASTC_HDR;
            __C_ENG_TYPE ( Bool )               shaderZeroInitializeWorkgroupMemory;
            __C_ENG_TYPE ( Bool )               dynamicRendering;
            __C_ENG_TYPE ( Bool )               shaderIntegerDotProduct;
            __C_ENG_TYPE ( Bool )               maintenance4;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( SurfaceCapabilities,   NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            cds :: uint32                   minImageCount;
            cds :: uint32                   maxImageCount;
            Type ( Extent2D )               currentExtent;
            Type ( Extent2D )               minImageExtent;
            Type ( Extent2D )               maxImageExtent;
            cds :: uint32                   maxImageArrayLayers;
            Type ( SurfaceTransformFlags )  supportedTransforms;
            Type ( SurfaceTransformFlag )   currentTransform;
            Type ( CompositeAlphaFlags )    supportedCompositeAlpha;
            Type ( ImageUsageFlags )        supportedUsageFlags;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE

        __C_ENG_ALIAS ( SwapChainHandle,        VkSwapchainKHR );
        __C_ENG_ALIAS ( SwapChainCreateFlags,   VkSwapchainCreateFlagsKHR );

#define C_ENG_MAP_START     ENUM ( SwapChainCreateFlag,     TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DEVICE_GROUP_AVAILABLE

            Field ( SplitInstanceBindRegions,   VkSwapchainCreateFlagBitsKHR :: VK_SWAPCHAIN_CREATE_SPLIT_INSTANCE_BIND_REGIONS_BIT_KHR ),

#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

            Field ( Protected,                  VkSwapchainCreateFlagBitsKHR :: VK_SWAPCHAIN_CREATE_PROTECTED_BIT_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_MUTABLE_FORMAT_AVAILABLE

            Field ( MutableFormat,              VkSwapchainCreateFlagBitsKHR :: VK_SWAPCHAIN_CREATE_MUTABLE_FORMAT_BIT_KHR ),

#endif

        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( SwapChainCreateInfo,   NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( SwapChainCreateFlags )       flags;
            Type ( SurfaceHandle )              surface;

            cds :: uint32                       minImageCount;
            Type ( Format )                     imageFormat;
            Type ( ColorSpace )                 imageColorSpace;
            Type ( Extent2D )                   imageExtent;
            cds :: uint32                       imageArrayLayers;
            Type ( ImageUsageFlags )            imageUsage;
            Type ( SharingMode )                imageSharingMode;

            cds :: uint32                       queueFamilyIndexCount;
            cds :: uint32               const * pQueueFamilyIndices;

            Type ( SurfaceTransformFlag )       preTransform;
            Type ( CompositeAlphaFlag )         compositeAlpha;
            Type ( PresentMode )                presentMode;

            Type ( Bool )                       clipped;
            Type ( SwapChainHandle )            oldSwapChain;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISPLAY_SURFACE_COUNTER_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( SurfaceCapabilities2,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )          structureType;
            Type ( GenericStructure )     * pNext;
            cds :: uint32                   minImageCount;
            cds :: uint32                   maxImageCount;
            Type ( Extent2D )               currentExtent;
            Type ( Extent2D )               minImageExtent;
            Type ( Extent2D )               maxImageExtent;
            cds :: uint32                   maxImageArrayLayers;
            Type ( SurfaceTransformFlags )  supportedTransforms;
            Type ( SurfaceTransformFlag )   currentTransform;
            Type ( CompositeAlphaFlags )    supportedCompositeAlpha;
            Type ( ImageUsageFlags )        supportedUsageFlags;
            Type ( SurfaceCounterFlags )    supportedSurfaceCounters;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_PCI_BUS_INFO_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDevicePCIBusInfoProperties,    NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;

            cds :: uint32                                       pciDomain;
            cds :: uint32                                       pciBus;
            cds :: uint32                                       pciDevice;
            cds :: uint32                                       pciFunction;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_PHYSICAL_DEVICE_DRM_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceDRMProperties,    NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )      structureType;
            __C_ENG_TYPE ( GenericStructure ) * pNext;

            __C_ENG_TYPE ( Bool )               hasPrimary;
            __C_ENG_TYPE ( Bool )               hasRender;

            cds :: sint64                       primaryMajor;
            cds :: sint64                       primaryMinor;
            cds :: sint64                       renderMajor;
            cds :: sint64                       renderMinor;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceAccelerationStructureProperties, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )      structureType;
            __C_ENG_TYPE ( GenericStructure ) * pNext;

            cds :: uint64                       maxGeometryCount;
            cds :: uint64                       maxInstanceCount;
            cds :: uint64                       maxPrimitiveCount;
            cds :: uint32                       maxPerStageDescriptorAccelerationStructures;
            cds :: uint32                       maxPerStageDescriptorUpdateAfterBindAccelerationStructures;
            cds :: uint32                       maxDescriptorSetAccelerationStructures;
            cds :: uint32                       maxDescriptorSetUpdateAfterBindAccelerationStructures;
            cds :: uint32                       minAccelerationStructureScratchOffsetAlignment;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceBlendOperationAdvancedProperties, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )      structureType;
            __C_ENG_TYPE ( GenericStructure ) * pNext;

            cds :: uint32                       advancedBlendMaxColorAttachments;
            __C_ENG_TYPE ( Bool )               advancedBlendIndependentBlend;
            __C_ENG_TYPE ( Bool )               advancedBlendNonPremultipliedSrcColor;
            __C_ENG_TYPE ( Bool )               advancedBlendNonPremultipliedDstColor;
            __C_ENG_TYPE ( Bool )               advancedBlendCorrelatedOverlap;
            __C_ENG_TYPE ( Bool )               advancedBlendAllOperations;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_CONSERVATIVE_RASTERIZATION_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceConservativeRasterizationProperties, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )      structureType;
            __C_ENG_TYPE ( GenericStructure ) * pNext;

            float                               primitiveOverestimationSize;
            float                               maxExtraPrimitiveOverestimationSize;
            float                               extraPrimitiveOverestimationSizeGranularity;
            __C_ENG_TYPE ( Bool )               primitiveUnderestimation;
            __C_ENG_TYPE ( Bool )               conservativePointAndLineRasterization;
            __C_ENG_TYPE ( Bool )               degenerateTrianglesRasterized;
            __C_ENG_TYPE ( Bool )               degenerateLinesRasterized;
            __C_ENG_TYPE ( Bool )               fullyCoveredFragmentShaderInputVariable;
            __C_ENG_TYPE ( Bool )               conservativeRasterizationPostDepthCoverage;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceCooperativeMatrixPropertiesNVidia,   NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )      structureType;
            __C_ENG_TYPE ( GenericStructure ) * pNext;
            __C_ENG_TYPE ( ShaderStageFlags )   cooperativeMatrixSupportedStages;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceCustomBorderColorProperties, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )      structureType;
            __C_ENG_TYPE ( GenericStructure ) * pNext;
            cds :: uint32                       maxCustomBorderColorSamplers;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceDeviceGeneratedCommandsPropertiesNVidia,   NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )      structureType;
            __C_ENG_TYPE ( GenericStructure ) * pNext;
            cds :: uint32                       maxGraphicsShaderGroupCount;
            cds :: uint32                       maxIndirectSequenceCount;
            cds :: uint32                       maxIndirectCommandsTokenCount;
            cds :: uint32                       maxIndirectCommandsStreamCount;
            cds :: uint32                       maxIndirectCommandsTokenOffset;
            cds :: uint32                       maxIndirectCommandsStreamStride;
            cds :: uint32                       minSequencesCountBufferOffsetAlignment;
            cds :: uint32                       minSequencesIndexBufferOffsetAlignment;
            cds :: uint32                       minIndirectCommandsBufferOffsetAlignment;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_DISCARD_RECTANGLES_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceDiscardRectangleProperties,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )      structureType;
            __C_ENG_TYPE ( GenericStructure ) * pNext;
            cds :: uint32                       maxDiscardRectangles;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_EXTERNAL_MEMORY_HOST_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceExternalMemoryHostProperties,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )      structureType;
            __C_ENG_TYPE ( GenericStructure ) * pNext;
            __C_ENG_TYPE ( DeviceSize )         minImportedHostPointerAlignment;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceFragmentDensityMap2Properties,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )      structureType;
            __C_ENG_TYPE ( GenericStructure ) * pNext;
            __C_ENG_TYPE ( Bool )               subsampledLoads;
            __C_ENG_TYPE ( Bool )               subsampledCoarseReconstructionEarlyAccess;
            cds :: uint32                       maxSubsampledArrayLayers;
            cds :: uint32                       maxDescriptorSetSubsampledSamplers;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceFragmentDensityMapOffsetPropertiesQualcomm,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )      structureType;
            __C_ENG_TYPE ( GenericStructure ) * pNext;
            __C_ENG_TYPE ( Extent2D )           fragmentDensityOffsetGranularity;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceFragmentDensityMapProperties,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )      structureType;
            __C_ENG_TYPE ( GenericStructure ) * pNext;
            __C_ENG_TYPE ( Extent2D )           minFragmentDensityTexelSize;
            __C_ENG_TYPE ( Extent2D )           maxFragmentDensityTexelSize;
            __C_ENG_TYPE ( Bool )               fragmentDensityInvocations;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceFragmentShadingRateEnumsPropertiesNVidia,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )      structureType;
            __C_ENG_TYPE ( GenericStructure ) * pNext;
            __C_ENG_TYPE ( SampleCountFlag )    maxFragmentShadingRateInvocationCount;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceFragmentShadingRateProperties,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )      structureType;
            __C_ENG_TYPE ( GenericStructure ) * pNext;
            __C_ENG_TYPE ( Extent2D )           maxFragmentShadingRateAttachmentTexelSize;
            __C_ENG_TYPE ( Extent2D )           minFragmentShadingRateAttachmentTexelSize;
            cds :: uint32                       maxFragmentShadingRateAttachmentTexelSizeAspectRatio;
            __C_ENG_TYPE ( Bool )               primitiveFragmentShadingRateWithMultipleViewports;
            __C_ENG_TYPE ( Bool )               layeredShadingRateAttachments;
            __C_ENG_TYPE ( Bool )               fragmentShadingRateNonTrivialCombinerOps;
            __C_ENG_TYPE ( Extent2D )           maxFragmentSize;
            cds :: uint32                       maxFragmentSizeAspectRatio;
            cds :: uint32                       maxFragmentShadingRateCoverageSamples;
            __C_ENG_TYPE ( SampleCountFlag )    maxFragmentShadingRateRasterizationSamples;
            __C_ENG_TYPE ( Bool )               fragmentShadingRateWithShaderDepthStencilWrites;
            __C_ENG_TYPE ( Bool )               fragmentShadingRateWithSampleMask;
            __C_ENG_TYPE ( Bool )               fragmentShadingRateWithShaderSampleMask;
            __C_ENG_TYPE ( Bool )               fragmentShadingRateWithConservativeRasterization;
            __C_ENG_TYPE ( Bool )               fragmentShadingRateWithFragmentShaderInterlock;
            __C_ENG_TYPE ( Bool )               fragmentShadingRateWithCustomSampleLocations;
            __C_ENG_TYPE ( Bool )               fragmentShadingRateStrictMultiplyCombiner;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceInlineUniformBlockProperties,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )      structureType;
            __C_ENG_TYPE ( GenericStructure ) * pNext;
            cds :: uint32                       maxInlineUniformBlockSize;
            cds :: uint32                       maxPerStageDescriptorInlineUniformBlocks;
            cds :: uint32                       maxPerStageDescriptorUpdateAfterBindInlineUniformBlocks;
            cds :: uint32                       maxDescriptorSetInlineUniformBlocks;
            cds :: uint32                       maxDescriptorSetUpdateAfterBindInlineUniformBlocks;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceLineRasterizationProperties,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )      structureType;
            __C_ENG_TYPE ( GenericStructure ) * pNext;
            cds :: uint32                       lineSubPixelPrecisionBits;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceMaintenance4Properties,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )      structureType;
            __C_ENG_TYPE ( GenericStructure ) * pNext;
            __C_ENG_TYPE ( DeviceSize )         maxBufferSize;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceMeshShaderPropertiesNVidia,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )      structureType;
            __C_ENG_TYPE ( GenericStructure ) * pNext;
            cds :: uint32                       maxDrawMeshTasksCount;
            cds :: uint32                       maxTaskWorkGroupInvocations;
            cds :: uint32                       maxTaskWorkGroupSize[3];
            cds :: uint32                       maxTaskTotalMemorySize;
            cds :: uint32                       maxTaskOutputCount;
            cds :: uint32                       maxMeshWorkGroupInvocations;
            cds :: uint32                       maxMeshWorkGroupSize[3];
            cds :: uint32                       maxMeshTotalMemorySize;
            cds :: uint32                       maxMeshOutputVertices;
            cds :: uint32                       maxMeshOutputPrimitives;
            cds :: uint32                       maxMeshMultiviewViewCount;
            cds :: uint32                       meshOutputPerVertexGranularity;
            cds :: uint32                       meshOutputPerPrimitiveGranularity;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceMultiDrawProperties,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )      structureType;
            __C_ENG_TYPE ( GenericStructure ) * pNext;
            cds :: uint32                       maxMultiDrawCount;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceMultiviewPerViewAttributesPropertiesNVidia,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )      structureType;
            __C_ENG_TYPE ( GenericStructure ) * pNext;
            __C_ENG_TYPE ( Bool )               perViewPositionAllComponents;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDevicePerformanceQueryProperties,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )      structureType;
            __C_ENG_TYPE ( GenericStructure ) * pNext;
            __C_ENG_TYPE ( Bool )               allowCommandBufferQueryCopies;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( PerformanceCounter,    NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )              structureType;
            __C_ENG_TYPE ( GenericStructure )         * pNext;
            __C_ENG_TYPE ( PerformanceCounterUnit )     unit;
            __C_ENG_TYPE ( PerformanceCounterScope )    scope;
            __C_ENG_TYPE ( PerformanceCounterStorage )  storage;
            cds :: uint8                                uuid [ VK_UUID_SIZE ];
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( PerformanceCounterDescription,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( PerformanceCounterDescriptionFlags ) flags;
            char                                                name [ VK_MAX_DESCRIPTION_SIZE ];
            char                                                category [ VK_MAX_DESCRIPTION_SIZE ];
            char                                                description [ VK_MAX_DESCRIPTION_SIZE ];
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDevicePortabilitySubsetProperties,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )      structureType;
            __C_ENG_TYPE ( GenericStructure ) * pNext;
            cds :: uint32                       minVertexInputBindingStrideAlignment;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceProvokingVertexProperties,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )      structureType;
            __C_ENG_TYPE ( GenericStructure ) * pNext;
            __C_ENG_TYPE ( Bool )               provokingVertexModePerPipeline;
            __C_ENG_TYPE ( Bool )               transformFeedbackPreservesTriangleFanProvokingVertex;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PUSH_DESCRIPTOR_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDevicePushDescriptorProperties,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )      structureType;
            __C_ENG_TYPE ( GenericStructure ) * pNext;
            cds :: uint32                       maxPushDescriptors;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceRayTracingPipelineProperties,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )      structureType;
            __C_ENG_TYPE ( GenericStructure ) * pNext;
            cds :: uint32                       shaderGroupHandleSize;
            cds :: uint32                       maxRayRecursionDepth;
            cds :: uint32                       maxShaderGroupStride;
            cds :: uint32                       shaderGroupBaseAlignment;
            cds :: uint32                       shaderGroupHandleCaptureReplaySize;
            cds :: uint32                       maxRayDispatchInvocationCount;
            cds :: uint32                       shaderGroupHandleAlignment;
            cds :: uint32                       maxRayHitAttributeSize;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceRayTracingPropertiesNVidia,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )      structureType;
            __C_ENG_TYPE ( GenericStructure ) * pNext;
            cds :: uint32                       shaderGroupHandleSize;
            cds :: uint32                       maxRecursionDepth;
            cds :: uint32                       maxShaderGroupStride;
            cds :: uint32                       shaderGroupBaseAlignment;
            cds :: uint64                       maxGeometryCount;
            cds :: uint64                       maxInstanceCount;
            cds :: uint64                       maxTriangleCount;
            cds :: uint32                       maxDescriptorSetAccelerationStructures;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceRobustnessProperties,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )      structureType;
            __C_ENG_TYPE ( GenericStructure ) * pNext;
            __C_ENG_TYPE ( DeviceSize )         robustStorageBufferAccessSizeAlignment;
            __C_ENG_TYPE ( DeviceSize )         robustUniformBufferAccessSizeAlignment;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceSampleLocationsProperties,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )      structureType;
            __C_ENG_TYPE ( GenericStructure ) * pNext;
            __C_ENG_TYPE ( SampleCountFlags )   sampleLocationSampleCounts;
            __C_ENG_TYPE ( Extent2D )           maxSampleLocationGridSize;
            float                               sampleLocationCoordinateRange[2];
            cds :: uint32                       sampleLocationSubPixelBits;
            __C_ENG_TYPE ( Bool )               variableSampleLocations;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceShaderCorePropertiesAMD,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )      structureType;
            __C_ENG_TYPE ( GenericStructure ) * pNext;
            cds :: uint32                       shaderEngineCount;
            cds :: uint32                       shaderArraysPerEngineCount;
            cds :: uint32                       computeUnitsPerShaderArray;
            cds :: uint32                       simdPerComputeUnit;
            cds :: uint32                       wavefrontsPerSimd;
            cds :: uint32                       wavefrontSize;
            cds :: uint32                       sgprsPerSimd;
            cds :: uint32                       minSgprAllocation;
            cds :: uint32                       maxSgprAllocation;
            cds :: uint32                       sgprAllocationGranularity;
            cds :: uint32                       vgprsPerSimd;
            cds :: uint32                       minVgprAllocation;
            cds :: uint32                       maxVgprAllocation;
            cds :: uint32                       vgprAllocationGranularity;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_2_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceShaderCoreProperties2AMD,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                  structureType;
            __C_ENG_TYPE ( GenericStructure )             * pNext;
            __C_ENG_TYPE ( ShaderCorePropertiesFlagsAMD )   shaderCoreFeatures;
            cds :: uint32                                   activeComputeUnitCount;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceShaderSMBuiltinsPropertiesNVidia,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                  structureType;
            __C_ENG_TYPE ( GenericStructure )             * pNext;
            cds :: uint32                                   shaderSMCount;
            cds :: uint32                                   shaderWarpsPerSM;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceShadingRateImagePropertiesNVidia,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                  structureType;
            __C_ENG_TYPE ( GenericStructure )             * pNext;
            __C_ENG_TYPE ( Extent2D )                       shadingRateTexelSize;
            cds :: uint32                                   shadingRatePaletteSize;
            cds :: uint32                                   shadingRateMaxCoarseSamples;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceSubgroupSizeControlProperties,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                  structureType;
            __C_ENG_TYPE ( GenericStructure )             * pNext;
            cds :: uint32                                   minSubgroupSize;
            cds :: uint32                                   maxSubgroupSize;
            cds :: uint32                                   maxComputeWorkgroupSubgroups;
            __C_ENG_TYPE ( ShaderStageFlags )               requiredSubgroupSizeStages;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceSubpassShadingPropertiesHuawei,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                  structureType;
            __C_ENG_TYPE ( GenericStructure )             * pNext;
            cds :: uint32                                   maxSubpassShadingWorkgroupSizeAspectRatio;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceTexelBufferAlignmentProperties,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                  structureType;
            __C_ENG_TYPE ( GenericStructure )             * pNext;
            __C_ENG_TYPE ( DeviceSize )                     storageTexelBufferOffsetAlignmentBytes;
            __C_ENG_TYPE ( Bool )                           storageTexelBufferOffsetSingleTexelAlignment;
            __C_ENG_TYPE ( DeviceSize )                     uniformTexelBufferOffsetAlignmentBytes;
            __C_ENG_TYPE ( Bool )                           uniformTexelBufferOffsetSingleTexelAlignment;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceTransformFeedbackProperties,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                  structureType;
            __C_ENG_TYPE ( GenericStructure )             * pNext;
            cds :: uint32                                   maxTransformFeedbackStreams;
            cds :: uint32                                   maxTransformFeedbackBuffers;
            __C_ENG_TYPE ( DeviceSize )                     maxTransformFeedbackBufferSize;
            cds :: uint32                                   maxTransformFeedbackStreamDataSize;
            cds :: uint32                                   maxTransformFeedbackBufferDataSize;
            cds :: uint32                                   maxTransformFeedbackBufferDataStride;
            __C_ENG_TYPE ( Bool )                           transformFeedbackQueries;
            __C_ENG_TYPE ( Bool )                           transformFeedbackStreamsLinesTriangles;
            __C_ENG_TYPE ( Bool )                           transformFeedbackRasterizationStreamSelect;
            __C_ENG_TYPE ( Bool )                           transformFeedbackDraw;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceVertexAttributeDivisorProperties,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                  structureType;
            __C_ENG_TYPE ( GenericStructure )             * pNext;
            cds :: uint32                                   maxVertexAttribDivisor;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceShaderIntegerDotProductProperties,   NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )      structureType;
            __C_ENG_TYPE ( GenericStructure ) * pNext;

            __C_ENG_TYPE ( Bool )               integerDotProduct8BitUnsignedAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProduct8BitSignedAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProduct8BitMixedSignednessAccelerated;

            __C_ENG_TYPE ( Bool )               integerDotProduct4x8BitPackedUnsignedAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProduct4x8BitPackedSignedAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProduct4x8BitPackedMixedSignednessAccelerated;

            __C_ENG_TYPE ( Bool )               integerDotProduct16BitUnsignedAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProduct16BitSignedAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProduct16BitMixedSignednessAccelerated;

            __C_ENG_TYPE ( Bool )               integerDotProduct32BitUnsignedAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProduct32BitSignedAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProduct32BitMixedSignednessAccelerated;

            __C_ENG_TYPE ( Bool )               integerDotProduct64BitUnsignedAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProduct64BitSignedAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProduct64BitMixedSignednessAccelerated;

            __C_ENG_TYPE ( Bool )               integerDotProductAccumulatingSaturating8BitUnsignedAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProductAccumulatingSaturating8BitSignedAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProductAccumulatingSaturating8BitMixedSignednessAccelerated;

            __C_ENG_TYPE ( Bool )               integerDotProductAccumulatingSaturating4x8BitPackedUnsignedAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProductAccumulatingSaturating4x8BitPackedSignedAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProductAccumulatingSaturating4x8BitPackedMixedSignednessAccelerated;

            __C_ENG_TYPE ( Bool )               integerDotProductAccumulatingSaturating16BitUnsignedAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProductAccumulatingSaturating16BitSignedAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProductAccumulatingSaturating16BitMixedSignednessAccelerated;

            __C_ENG_TYPE ( Bool )               integerDotProductAccumulatingSaturating32BitUnsignedAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProductAccumulatingSaturating32BitSignedAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProductAccumulatingSaturating32BitMixedSignednessAccelerated;

            __C_ENG_TYPE ( Bool )               integerDotProductAccumulatingSaturating64BitUnsignedAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProductAccumulatingSaturating64BitSignedAccelerated;
            __C_ENG_TYPE ( Bool )               integerDotProductAccumulatingSaturating64BitMixedSignednessAccelerated;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( QueueFamilyProperties, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {

            /// bitmask of QueueFlag indicating capabilities of queues of this family
            __C_ENG_TYPE ( QueueFlags ) queueFlags;

            /// number of queues in this family
            cds :: uint32               queueCount;

            /// number of meaningful bits in the timestamps written via commandWriteTimestamp. Valid range for count
            /// is 36..64 bits, or 0 ( no support for timestamps ). Bits outside the range are guaranteed to be 0
            cds :: uint32               timestampValidBits;

            /// minimum granularity supported for image transfer on this queue family
            /// (0,0,0) = only whole mip levels must be transferred using image transfer operations, as in
            ///     any image's offset must be x=0,y=0,z=0
            ///     any image's extent must match the width, height, depth of the image subresource
            /// (A, B, C), where A, B and C are 2^n, restrictions:
            ///     offset must be x = A * a, B * b, C * c, where a, b, c are int
            ///     width of extent must be width = A * a, where a is int, or x + width = width of image subresource
            ///     height of extent must be height = B * b, where b is int, or y + height = height of image subresource
            ///     depth of extent must be depth = C * c, where c is int, or z + depth = depth of image subresource
            __C_ENG_TYPE ( Extent3D )   minImageTransferGranularity;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( QueueFamilyExtendedProperties, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )              structureType;
            __C_ENG_TYPE ( GenericStructure )         * pNext;
            __C_ENG_TYPE ( QueueFamilyProperties )      properties;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTIC_CHECKPOINTS_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( QueueFamilyCheckpointPropertiesNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )      structureType;
            __C_ENG_TYPE ( GenericStructure ) * pNext;
            __C_ENG_TYPE ( PipelineStageFlags ) checkpointExecutionStageMask;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( QueueFamilyGlobalPriorityProperties, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )          structureType;
            __C_ENG_TYPE ( GenericStructure )     * pNext;
            cds :: uint32                           priorityCount;
            __C_ENG_TYPE ( QueueGlobalPriority )    priorities [ VK_MAX_GLOBAL_PRIORITY_SIZE_EXT ];
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( QueueFamilyQueryResultStatusProperties, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )          structureType;
            __C_ENG_TYPE ( GenericStructure )     * pNext;
            __C_ENG_TYPE ( Bool )                   supported;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( VideoQueueFamilyProperties, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )              structureType;
            __C_ENG_TYPE ( GenericStructure )         * pNext;
            __C_ENG_TYPE ( VideoCodecOperationFlags )   videoCodecOperations;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( QueueFamilyDetails,    NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( QueueFamilyProperties )                      properties;

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTIC_CHECKPOINTS_AVAILABLE

            __C_ENG_TYPE ( QueueFamilyCheckpointPropertiesNVidia )      checkpointPropertiesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE

            __C_ENG_TYPE ( QueueFamilyGlobalPriorityProperties )        globalPriorityProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE

            __C_ENG_TYPE ( QueueFamilyQueryResultStatusProperties )     queryResultStatusProperties;
            __C_ENG_TYPE ( VideoQueueFamilyProperties )                 videoProperties;

#endif

        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_DEVICE_MEMORY_REPORT_AVAILABLE

#define C_ENG_MAP_START     ENUM ( DeviceMemoryReportFlag,  TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {

        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     ENUM ( DeviceMemoryReportEventType,  TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Allocate,           VkDeviceMemoryReportEventTypeEXT :: VK_DEVICE_MEMORY_REPORT_EVENT_TYPE_ALLOCATE_EXT ),
            Field ( Free,               VkDeviceMemoryReportEventTypeEXT :: VK_DEVICE_MEMORY_REPORT_EVENT_TYPE_FREE_EXT ),
            Field ( Import,             VkDeviceMemoryReportEventTypeEXT :: VK_DEVICE_MEMORY_REPORT_EVENT_TYPE_IMPORT_EXT ),
            Field ( Unimport,           VkDeviceMemoryReportEventTypeEXT :: VK_DEVICE_MEMORY_REPORT_EVENT_TYPE_UNIMPORT_EXT ),
            Field ( AllocationFailed,   VkDeviceMemoryReportEventTypeEXT :: VK_DEVICE_MEMORY_REPORT_EVENT_TYPE_ALLOCATION_FAILED_EXT )
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( DeviceDeviceMemoryReportCreateInfo,    NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )           const * pNext;
            __C_ENG_TYPE ( DeviceMemoryReportFlags )            flags;
            __C_ENG_TYPE ( DeviceMemoryReportCallback )         callback;
            void                                              * pUserData;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTICS_CONFIG_AVAILABLE

#define C_ENG_MAP_START     ENUM ( DeviceDiagnosticsConfigFlagNVidia, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( EnableShaderDebugInfo,      VkDeviceDiagnosticsConfigFlagBitsNV :: VK_DEVICE_DIAGNOSTICS_CONFIG_ENABLE_SHADER_DEBUG_INFO_BIT_NV ),
            Field ( EnableResourceTracking,     VkDeviceDiagnosticsConfigFlagBitsNV :: VK_DEVICE_DIAGNOSTICS_CONFIG_ENABLE_RESOURCE_TRACKING_BIT_NV ),
            Field ( EnableAutomaticCheckpoints, VkDeviceDiagnosticsConfigFlagBitsNV :: VK_DEVICE_DIAGNOSTICS_CONFIG_ENABLE_AUTOMATIC_CHECKPOINTS_BIT_NV )
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

        __C_ENG_ALIAS ( DeviceDiagnosticsConfigFlagsNVidia, VkDeviceDiagnosticsConfigFlagsNV );

#define C_ENG_MAP_START     STRUCT ( DeviceDiagnosticsConfigCreateInfoNVidia,   NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )           const * pNext;
            __C_ENG_TYPE ( DeviceDiagnosticsConfigFlagsNVidia ) flags;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( DeviceGroupDeviceCreateInfo,   NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )           const * pNext;
            cds :: uint32                                       physicalDeviceCount;
            __C_ENG_TYPE ( PhysicalDeviceHandle )       const * pPhysicalDevices;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_AMD_MEMORY_OVERALLOCATION_BEHAVIOUR_AVAILABLE

#define C_ENG_MAP_START     ENUM ( MemoryOverallocationBehaviorAMD, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Default,        VkMemoryOverallocationBehaviorAMD :: VK_MEMORY_OVERALLOCATION_BEHAVIOR_DEFAULT_AMD ),
            Field ( Allowed,        VkMemoryOverallocationBehaviorAMD :: VK_MEMORY_OVERALLOCATION_BEHAVIOR_ALLOWED_AMD ),
            Field ( Disallowed,     VkMemoryOverallocationBehaviorAMD :: VK_MEMORY_OVERALLOCATION_BEHAVIOR_DISALLOWED_AMD )
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( DeviceMemoryOverallocationCreateInfoAMD, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )           const * pNext;
            __C_ENG_TYPE ( MemoryOverallocationBehaviorAMD )    overallocationBehavior;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( DevicePrivateDataCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )           const * pNext;
            cds :: uint32                                       privateDataSlotRequestCount;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDevice16BitStorageFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               storageBuffer16BitAccess;
            __C_ENG_TYPE ( Bool )                               uniformAndStorageBuffer16BitAccess;
            __C_ENG_TYPE ( Bool )                               storagePushConstant16;
            __C_ENG_TYPE ( Bool )                               storageInputOutput16;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceMultiviewFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               multiview;
            __C_ENG_TYPE ( Bool )                               multiviewGeometryShader;
            __C_ENG_TYPE ( Bool )                               multiviewTessellationShader;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceProtectedMemoryFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               protectedMemory;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceSamplerYCBCRConversionFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               samplerYCBCRConversion;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceShaderDrawParametersFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               shaderDrawParameters;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceVariablePointersFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               variablePointersStorageBuffer;
            __C_ENG_TYPE ( Bool )                               variablePointers;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceVulkan11Features, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               storageBuffer16BitAccess;
            __C_ENG_TYPE ( Bool )                               uniformAndStorageBuffer16BitAccess;
            __C_ENG_TYPE ( Bool )                               storagePushConstant16;
            __C_ENG_TYPE ( Bool )                               storageInputOutput16;
            __C_ENG_TYPE ( Bool )                               multiview;
            __C_ENG_TYPE ( Bool )                               multiviewGeometryShader;
            __C_ENG_TYPE ( Bool )                               multiviewTessellationShader;
            __C_ENG_TYPE ( Bool )                               variablePointersStorageBuffer;
            __C_ENG_TYPE ( Bool )                               variablePointers;
            __C_ENG_TYPE ( Bool )                               protectedMemory;
            __C_ENG_TYPE ( Bool )                               samplerYCBCRConversion;
            __C_ENG_TYPE ( Bool )                               shaderDrawParameters;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WIN32_SURFACE_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_FULL_SCREEN_EXCLUSIVE_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( SurfaceFullScreenExclusiveWin32Info )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            HMONITOR                            monitorHandle;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( ImageFormatListCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            cds :: uint32                       viewFormatCount;
            Type ( Format )             const * pViewFormats;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( PhysicalDevice8BitStorageFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               storageBuffer8BitAccess;
            __C_ENG_TYPE ( Bool )                               uniformAndStorageBuffer8BitAccess;
            __C_ENG_TYPE ( Bool )                               storagePushConstant8;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceBufferDeviceAddressFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               bufferDeviceAddress;
            __C_ENG_TYPE ( Bool )                               bufferDeviceAddressCaptureReplay;
            __C_ENG_TYPE ( Bool )                               bufferDeviceAddressMultiDevice;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceDescriptorIndexingFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               shaderInputAttachmentArrayDynamicIndexing;
            __C_ENG_TYPE ( Bool )                               shaderUniformTexelBufferArrayDynamicIndexing;
            __C_ENG_TYPE ( Bool )                               shaderStorageTexelBufferArrayDynamicIndexing;
            __C_ENG_TYPE ( Bool )                               shaderUniformBufferArrayNonUniformIndexing;
            __C_ENG_TYPE ( Bool )                               shaderSampledImageArrayNonUniformIndexing;
            __C_ENG_TYPE ( Bool )                               shaderStorageBufferArrayNonUniformIndexing;
            __C_ENG_TYPE ( Bool )                               shaderStorageImageArrayNonUniformIndexing;
            __C_ENG_TYPE ( Bool )                               shaderInputAttachmentArrayNonUniformIndexing;
            __C_ENG_TYPE ( Bool )                               shaderUniformTexelBufferArrayNonUniformIndexing;
            __C_ENG_TYPE ( Bool )                               shaderStorageTexelBufferArrayNonUniformIndexing;
            __C_ENG_TYPE ( Bool )                               descriptorBindingUniformBufferUpdateAfterBind;
            __C_ENG_TYPE ( Bool )                               descriptorBindingSampledImageUpdateAfterBind;
            __C_ENG_TYPE ( Bool )                               descriptorBindingStorageImageUpdateAfterBind;
            __C_ENG_TYPE ( Bool )                               descriptorBindingStorageBufferUpdateAfterBind;
            __C_ENG_TYPE ( Bool )                               descriptorBindingUniformTexelBufferUpdateAfterBind;
            __C_ENG_TYPE ( Bool )                               descriptorBindingStorageTexelBufferUpdateAfterBind;
            __C_ENG_TYPE ( Bool )                               descriptorBindingUpdateUnusedWhilePending;
            __C_ENG_TYPE ( Bool )                               descriptorBindingPartiallyBound;
            __C_ENG_TYPE ( Bool )                               descriptorBindingVariableDescriptorCount;
            __C_ENG_TYPE ( Bool )                               runtimeDescriptorArray;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceHostQueryResetFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               hostQueryReset;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceImagelessFrameBufferFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               imagelessFramebuffer;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceScalarBlockLayoutFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               scalarBlockLayout;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceSeparateDepthStencilLayoutsFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               separateDepthStencilLayouts;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceShaderAtomicInt64Features, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               shaderBufferInt64Atomics;
            __C_ENG_TYPE ( Bool )                               shaderSharedInt64Atomics;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceShaderFloat16Int8Features, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               shaderFloat16;
            __C_ENG_TYPE ( Bool )                               shaderInt8;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceShaderSubgroupExtendedTypesFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               shaderSubgroupExtendedTypes;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceTimelineSemaphoreFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               timelineSemaphore;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceUniformBufferStandardLayoutFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               uniformBufferStandardLayout;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceVulkanMemoryModelFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               vulkanMemoryModel;
            __C_ENG_TYPE ( Bool )                               vulkanMemoryModelDeviceScope;
            __C_ENG_TYPE ( Bool )                               vulkanMemoryModelAvailabilityVisibilityChains;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceVulkan12Features, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               samplerMirrorClampToEdge;
            __C_ENG_TYPE ( Bool )                               drawIndirectCount;
            __C_ENG_TYPE ( Bool )                               storageBuffer8BitAccess;
            __C_ENG_TYPE ( Bool )                               uniformAndStorageBuffer8BitAccess;
            __C_ENG_TYPE ( Bool )                               storagePushConstant8;
            __C_ENG_TYPE ( Bool )                               shaderBufferInt64Atomics;
            __C_ENG_TYPE ( Bool )                               shaderSharedInt64Atomics;
            __C_ENG_TYPE ( Bool )                               shaderFloat16;
            __C_ENG_TYPE ( Bool )                               shaderInt8;
            __C_ENG_TYPE ( Bool )                               descriptorIndexing;
            __C_ENG_TYPE ( Bool )                               shaderInputAttachmentArrayDynamicIndexing;
            __C_ENG_TYPE ( Bool )                               shaderUniformTexelBufferArrayDynamicIndexing;
            __C_ENG_TYPE ( Bool )                               shaderStorageTexelBufferArrayDynamicIndexing;
            __C_ENG_TYPE ( Bool )                               shaderUniformBufferArrayNonUniformIndexing;
            __C_ENG_TYPE ( Bool )                               shaderSampledImageArrayNonUniformIndexing;
            __C_ENG_TYPE ( Bool )                               shaderStorageBufferArrayNonUniformIndexing;
            __C_ENG_TYPE ( Bool )                               shaderStorageImageArrayNonUniformIndexing;
            __C_ENG_TYPE ( Bool )                               shaderInputAttachmentArrayNonUniformIndexing;
            __C_ENG_TYPE ( Bool )                               shaderUniformTexelBufferArrayNonUniformIndexing;
            __C_ENG_TYPE ( Bool )                               shaderStorageTexelBufferArrayNonUniformIndexing;
            __C_ENG_TYPE ( Bool )                               descriptorBindingUniformBufferUpdateAfterBind;
            __C_ENG_TYPE ( Bool )                               descriptorBindingSampledImageUpdateAfterBind;
            __C_ENG_TYPE ( Bool )                               descriptorBindingStorageImageUpdateAfterBind;
            __C_ENG_TYPE ( Bool )                               descriptorBindingStorageBufferUpdateAfterBind;
            __C_ENG_TYPE ( Bool )                               descriptorBindingUniformTexelBufferUpdateAfterBind;
            __C_ENG_TYPE ( Bool )                               descriptorBindingStorageTexelBufferUpdateAfterBind;
            __C_ENG_TYPE ( Bool )                               descriptorBindingUpdateUnusedWhilePending;
            __C_ENG_TYPE ( Bool )                               descriptorBindingPartiallyBound;
            __C_ENG_TYPE ( Bool )                               descriptorBindingVariableDescriptorCount;
            __C_ENG_TYPE ( Bool )                               runtimeDescriptorArray;
            __C_ENG_TYPE ( Bool )                               samplerFilterMinmax;
            __C_ENG_TYPE ( Bool )                               scalarBlockLayout;
            __C_ENG_TYPE ( Bool )                               imagelessFramebuffer;
            __C_ENG_TYPE ( Bool )                               uniformBufferStandardLayout;
            __C_ENG_TYPE ( Bool )                               shaderSubgroupExtendedTypes;
            __C_ENG_TYPE ( Bool )                               separateDepthStencilLayouts;
            __C_ENG_TYPE ( Bool )                               hostQueryReset;
            __C_ENG_TYPE ( Bool )                               timelineSemaphore;
            __C_ENG_TYPE ( Bool )                               bufferDeviceAddress;
            __C_ENG_TYPE ( Bool )                               bufferDeviceAddressCaptureReplay;
            __C_ENG_TYPE ( Bool )                               bufferDeviceAddressMultiDevice;
            __C_ENG_TYPE ( Bool )                               vulkanMemoryModel;
            __C_ENG_TYPE ( Bool )                               vulkanMemoryModelDeviceScope;
            __C_ENG_TYPE ( Bool )                               vulkanMemoryModelAvailabilityVisibilityChains;
            __C_ENG_TYPE ( Bool )                               shaderOutputViewportIndex;
            __C_ENG_TYPE ( Bool )                               shaderOutputLayer;
            __C_ENG_TYPE ( Bool )                               subgroupBroadcastDynamicId;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_4444_FORMATS_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDevice4444FormatsFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               formatA4R4G4B4;
            __C_ENG_TYPE ( Bool )                               formatA4B4G4R4;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_ASTC_DECODE_MODE_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceASTCDecodeFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               decodeModeSharedExponent;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceAccelerationStructureFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               accelerationStructure;
            __C_ENG_TYPE ( Bool )                               accelerationStructureCaptureReplay;
            __C_ENG_TYPE ( Bool )                               accelerationStructureIndirectBuild;
            __C_ENG_TYPE ( Bool )                               accelerationStructureHostCommands;
            __C_ENG_TYPE ( Bool )                               descriptorBindingAccelerationStructureUpdateAfterBind;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceBlendOperationAdvancedFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               advancedBlendCoherentOperations;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_BORDER_COLOR_SWIZZLE_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceBorderColorSwizzleFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               borderColorSwizzle;
            __C_ENG_TYPE ( Bool )                               borderColorSwizzleFromImage;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_AMD_DEVICE_COHERENT_MEMORY_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceCoherentMemoryFeaturesAMD, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               deviceCoherentMemory;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_COLOR_WRITE_ENABLE_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceColorWriteEnableFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               colorWriteEnable;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COMPUTE_SHADER_DERIVATIVES_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceComputeShaderDerivativesFeaturesNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               computeDerivativeGroupQuads;
            __C_ENG_TYPE ( Bool )                               computeDerivativeGroupLinear;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceConditionalRenderingFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               conditionalRendering;
            __C_ENG_TYPE ( Bool )                               inheritedConditionalRendering;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceCooperativeMatrixFeaturesNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               cooperativeMatrix;
            __C_ENG_TYPE ( Bool )                               cooperativeMatrixRobustBufferAccess;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CORNER_SAMPLED_IMAGE_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceCornerSampledImageFeaturesNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               cornerSampledImage;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COVERAGE_REDUCTION_MODE_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceCoverageReductionModeFeaturesNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               coverageReductionMode;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceCustomBorderColorFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               customBorderColors;
            __C_ENG_TYPE ( Bool )                               customBorderColorWithoutFormat;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_IMAGE_ALIASING_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               dedicatedAllocationImageAliasing;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_CONTROL_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceDepthClipControlFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               depthClipControl;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_ENABLE_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceDepthClipEnableFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               depthClipEnable;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceDeviceGeneratedCommandsFeaturesNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               deviceGeneratedCommands;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_DEVICE_MEMORY_REPORT_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceDeviceMemoryReportFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               deviceMemoryReport;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTICS_CONFIG_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceDiagnosticsConfigFeaturesNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               diagnosticsConfig;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceDynamicRenderingFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               dynamicRendering;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SCISSOR_EXCLUSIVE_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceExclusiveScissorFeaturesNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               exclusiveScissor;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceExtendedDynamicState2Features, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               extendedDynamicState2;
            __C_ENG_TYPE ( Bool )                               extendedDynamicState2LogicOp;
            __C_ENG_TYPE ( Bool )                               extendedDynamicState2PatchControlPoints;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceExtendedDynamicStateFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               extendedDynamicState;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_RDMA_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceExternalMemoryRDMAFeaturesNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               externalMemoryRDMA;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceFragmentDensityMap2Features, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               fragmentDensityMapDeferred;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceFragmentDensityMapFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               fragmentDensityMap;
            __C_ENG_TYPE ( Bool )                               fragmentDensityMapDynamic;
            __C_ENG_TYPE ( Bool )                               fragmentDensityMapNonSubsampledImages;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceFragmentDensityMapOffsetFeaturesQualcomm, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               fragmentDensityMapOffset;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADER_BARYCENTRIC_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceFragmentShaderBarycentricFeaturesNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               fragmentShaderBarycentric;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_SHADER_INTERLOCK_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceFragmentShaderInterlockFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               fragmentShaderSampleInterlock;
            __C_ENG_TYPE ( Bool )                               fragmentShaderPixelInterlock;
            __C_ENG_TYPE ( Bool )                               fragmentShaderShadingRateInterlock;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceFragmentShadingRateEnumsFeaturesNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               fragmentShadingRateEnums;
            __C_ENG_TYPE ( Bool )                               supersampleFragmentShadingRates;
            __C_ENG_TYPE ( Bool )                               noInvocationFragmentShadingRates;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceFragmentShadingRateFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               pipelineFragmentShadingRate;
            __C_ENG_TYPE ( Bool )                               primitiveFragmentShadingRate;
            __C_ENG_TYPE ( Bool )                               attachmentFragmentShadingRate;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceGlobalPriorityQueryFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               globalPriorityQuery;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_ROBUSTNESS_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceImageRobustnessFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               robustImageAccess;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_VIEW_MIN_LOD_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceImageViewMinLODFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               minLOD;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_INDEX_TYPE_UINT8_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceIndexTypeUInt8Features, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               indexTypeUInt8;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_INHERITED_VIEWPORT_SCISSOR_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceInheritedViewportScissorFeaturesNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               inheritedViewportScissor2D;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceInlineUniformBlockFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               inlineUniformBlock;
            __C_ENG_TYPE ( Bool )                               descriptorBindingInlineUniformBlockUpdateAfterBind;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_INVOCATION_MASK_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceInvocationMaskFeaturesHuawei, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               invocationMask;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceLineRasterizationFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               rectangularLines;
            __C_ENG_TYPE ( Bool )                               bresenhamLines;
            __C_ENG_TYPE ( Bool )                               smoothLines;
            __C_ENG_TYPE ( Bool )                               stippledRectangularLines;
            __C_ENG_TYPE ( Bool )                               stippledBresenhamLines;
            __C_ENG_TYPE ( Bool )                               stippledSmoothLines;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_LINEAR_COLOR_ATTACHMENT_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceLinearColorAttachmentFeaturesNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               linearColorAttachment;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceMaintenance4Features, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               maintenance4;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_PRIORITY_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceMemoryPriorityFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               memoryPriority;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceMeshShaderFeaturesNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               taskShader;
            __C_ENG_TYPE ( Bool )                               meshShader;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceMultiDrawFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               multiDraw;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceMutableDescriptorTypeFeaturesValve, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               mutableDescriptorType;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_PAGEABLE_DEVICE_LOCAL_MEMORY_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDevicePageableDeviceLocalMemoryFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               pageableDeviceLocalMemory;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDevicePerformanceQueryFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               performanceCounterQueryPools;
            __C_ENG_TYPE ( Bool )                               performanceCounterMultipleQueryPools;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDevicePipelineCreationCacheControlFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               pipelineCreationCacheControl;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDevicePipelineExecutablePropertiesFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               pipelineExecutableInfo;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDevicePortabilitySubsetFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               constantAlphaColorBlendFactors;
            __C_ENG_TYPE ( Bool )                               events;
            __C_ENG_TYPE ( Bool )                               imageViewFormatReinterpretation;
            __C_ENG_TYPE ( Bool )                               imageViewFormatSwizzle;
            __C_ENG_TYPE ( Bool )                               imageView2DOn3DImage;
            __C_ENG_TYPE ( Bool )                               multisampleArrayImage;
            __C_ENG_TYPE ( Bool )                               mutableComparisonSamplers;
            __C_ENG_TYPE ( Bool )                               pointPolygons;
            __C_ENG_TYPE ( Bool )                               samplerMipLodBias;
            __C_ENG_TYPE ( Bool )                               separateStencilMaskRef;
            __C_ENG_TYPE ( Bool )                               shaderSampleRateInterpolationFunctions;
            __C_ENG_TYPE ( Bool )                               tessellationIsolines;
            __C_ENG_TYPE ( Bool )                               tessellationPointMode;
            __C_ENG_TYPE ( Bool )                               triangleFans;
            __C_ENG_TYPE ( Bool )                               vertexAttributeAccessBeyondStride;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_ID_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDevicePresentIDFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               presentID;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_WAIT_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDevicePresentWaitFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               presentWait;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_PRIMITIVE_TOPOLOGY_LIST_RESTART_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDevicePrimitiveTopologyListRestartFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               primitiveTopologyListRestart;
            __C_ENG_TYPE ( Bool )                               primitiveTopologyPatchListRestart;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDevicePrivateDataFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               privateData;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceProvokingVertexFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               provokingVertexLast;
            __C_ENG_TYPE ( Bool )                               transformFeedbackPreservesProvokingVertex;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_RGBA_10_X_6_FORMATS_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceRGBA10x6FormatsFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               formatRGBA10x6WithoutYCBCRSampler;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_ARM_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               rasterizationOrderColorAttachmentAccess;
            __C_ENG_TYPE ( Bool )                               rasterizationOrderDepthAttachmentAccess;
            __C_ENG_TYPE ( Bool )                               rasterizationOrderStencilAttachmentAccess;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_QUERY_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceRayQueryFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               rayQuery;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceRayTracingMotionBlurFeaturesNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               rayTracingMotionBlur;
            __C_ENG_TYPE ( Bool )                               rayTracingMotionBlurPipelineTraceRaysIndirect;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceRayTracingPipelineFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               rayTracingPipeline;
            __C_ENG_TYPE ( Bool )                               rayTracingPipelineShaderGroupHandleCaptureReplay;
            __C_ENG_TYPE ( Bool )                               rayTracingPipelineShaderGroupHandleCaptureReplayMixed;
            __C_ENG_TYPE ( Bool )                               rayTracingPipelineTraceRaysIndirect;
            __C_ENG_TYPE ( Bool )                               rayTraversalPrimitiveCulling;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_REPRESENTATIVE_FRAGMENT_TEST_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceRepresentativeFragmentTestFeaturesNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               representativeFragmentTest;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceRobustnessFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               robustBufferAccess;
            __C_ENG_TYPE ( Bool )                               robustImageAccess;
            __C_ENG_TYPE ( Bool )                               nullDescriptor;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceShaderAtomicFloatFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               shaderBufferFloat32Atomics;
            __C_ENG_TYPE ( Bool )                               shaderBufferFloat32AtomicAdd;
            __C_ENG_TYPE ( Bool )                               shaderBufferFloat64Atomics;
            __C_ENG_TYPE ( Bool )                               shaderBufferFloat64AtomicAdd;
            __C_ENG_TYPE ( Bool )                               shaderSharedFloat32Atomics;
            __C_ENG_TYPE ( Bool )                               shaderSharedFloat32AtomicAdd;
            __C_ENG_TYPE ( Bool )                               shaderSharedFloat64Atomics;
            __C_ENG_TYPE ( Bool )                               shaderSharedFloat64AtomicAdd;
            __C_ENG_TYPE ( Bool )                               shaderImageFloat32Atomics;
            __C_ENG_TYPE ( Bool )                               shaderImageFloat32AtomicAdd;
            __C_ENG_TYPE ( Bool )                               sparseImageFloat32Atomics;
            __C_ENG_TYPE ( Bool )                               sparseImageFloat32AtomicAdd;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_2_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceShaderAtomicFloat2Features, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               shaderBufferFloat16Atomics;
            __C_ENG_TYPE ( Bool )                               shaderBufferFloat16AtomicAdd;
            __C_ENG_TYPE ( Bool )                               shaderBufferFloat16AtomicMinMax;
            __C_ENG_TYPE ( Bool )                               shaderBufferFloat32AtomicMinMax;
            __C_ENG_TYPE ( Bool )                               shaderBufferFloat64AtomicMinMax;
            __C_ENG_TYPE ( Bool )                               shaderSharedFloat16Atomics;
            __C_ENG_TYPE ( Bool )                               shaderSharedFloat16AtomicAdd;
            __C_ENG_TYPE ( Bool )                               shaderSharedFloat16AtomicMinMax;
            __C_ENG_TYPE ( Bool )                               shaderSharedFloat32AtomicMinMax;
            __C_ENG_TYPE ( Bool )                               shaderSharedFloat64AtomicMinMax;
            __C_ENG_TYPE ( Bool )                               shaderImageFloat32AtomicMinMax;
            __C_ENG_TYPE ( Bool )                               sparseImageFloat32AtomicMinMax;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_CLOCK_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceShaderClockFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               shaderSubgroupClock;
            __C_ENG_TYPE ( Bool )                               shaderDeviceClock;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_SHADER_DEMOTE_TO_HELPER_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceShaderDemoteToHelperInvocationFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               shaderDemoteToHelperInvocation;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_SHADER_IMAGE_ATOMIC_INT64_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceShaderImageAtomicInt64Features, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               shaderImageInt64Atomics;
            __C_ENG_TYPE ( Bool )                               sparseImageInt64Atomics;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_IMAGE_FOOTPRINT_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceShaderImageFootprintFeaturesNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               imageFootprint;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceShaderIntegerDotProductFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               shaderIntegerDotProduct;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_INTEL_SHADER_INTEGER_FUNCTIONS_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceShaderIntegerFunctionsFeaturesIntel, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               shaderIntegerFunctions;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceShaderSMBuiltinsFeaturesNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               shaderSMBuiltins;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_SUBGROUP_UNIFORM_CONTROL_FLOW_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceShaderSubgroupUniformControlFlowFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               shaderSubgroupUniformControlFlow;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_TERMINATE_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceShaderTerminateInvocationFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               shaderTerminateInvocation;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceShadingRateImageFeaturesNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               shadingRateImage;
            __C_ENG_TYPE ( Bool )                               shadingRateCoarseSampleOrder;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceSubgroupSizeControlFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               subgroupSizeControl;
            __C_ENG_TYPE ( Bool )                               computeFullSubgroups;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceSubpassShadingFeaturesHuawei, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               subpassShading;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceSynchronizationFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               synchronization;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceTexelBufferAlignmentFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               texelBufferAlignment;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_TEXTURE_COMPRESSION_ASTC_HDR_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceTextureCompressionASTCHDRFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               textureCompressionASTCHDR;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceTransformFeedbackFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               transformFeedback;
            __C_ENG_TYPE ( Bool )                               geometryStreams;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceVertexAttributeDivisorFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               vertexAttributeInstanceRateDivisor;
            __C_ENG_TYPE ( Bool )                               vertexAttributeInstanceRateZeroDivisor;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_INPUT_DYNAMIC_STATE_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceVertexInputDynamicStateFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               vertexInputDynamicState;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceWorkgroupMemoryExplicitLayoutFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               workgroupMemoryExplicitLayout;
            __C_ENG_TYPE ( Bool )                               workgroupMemoryExplicitLayoutScalarBlockLayout;
            __C_ENG_TYPE ( Bool )                               workgroupMemoryExplicitLayout8BitAccess;
            __C_ENG_TYPE ( Bool )                               workgroupMemoryExplicitLayout16BitAccess;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_2_PLANE_444_FORMATS_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceYCBCR2Plane444FormatsFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               YCBCR2Plane444Formats;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_IMAGE_ARRAYS_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceYCBCRImageArraysFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               YCBCRImageArrays;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ZERO_INITIALIZE_WORKGROUP_MEMORY_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceZeroInitializeWorkgroupMemoryFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            __C_ENG_TYPE ( Bool )                               shaderZeroInitializeWorkgroupMemory;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceDetails,     NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {

            __C_ENG_TYPE ( PhysicalDeviceProperties )                                       basicProperties;
            __C_ENG_TYPE ( PhysicalDeviceFeatures )                                         basicFeatures;

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceVulkan11Properties )                               vulkan11Properties;
            __C_ENG_TYPE ( PhysicalDeviceIDProperties )                                     IDProperties;
            __C_ENG_TYPE ( PhysicalDeviceMaintenanceProperties )                            maintenanceProperties;
            __C_ENG_TYPE ( PhysicalDeviceMultiviewProperties )                              multiviewProperties;
            __C_ENG_TYPE ( PhysicalDevicePointClippingProperties )                          pointClippingProperties;
            __C_ENG_TYPE ( PhysicalDeviceProtectedMemoryProperties )                        protectedMemoryProperties;
            __C_ENG_TYPE ( PhysicalDeviceSubgroupProperties )                               subgroupProperties;

            __C_ENG_TYPE ( PhysicalDeviceVulkan11Features )                                 vulkan11Features;
            __C_ENG_TYPE ( PhysicalDevice16BitStorageFeatures )                             _16BitStorageFeatures;
            __C_ENG_TYPE ( PhysicalDeviceMultiviewFeatures )                                multiviewFeatures;
            __C_ENG_TYPE ( PhysicalDeviceProtectedMemoryFeatures )                          protectedMemoryFeatures;
            __C_ENG_TYPE ( PhysicalDeviceSamplerYCBCRConversionFeatures )                   samplerYCBCRConversionFeatures;
            __C_ENG_TYPE ( PhysicalDeviceShaderDrawParametersFeatures )                     shaderDrawParametersFeatures;
            __C_ENG_TYPE ( PhysicalDeviceVariablePointersFeatures )                         variablePointersFeatures;

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceVulkan12Properties )                               vulkan12Properties;
            __C_ENG_TYPE ( PhysicalDeviceDriverProperties )                                 driverProperties;
            __C_ENG_TYPE ( PhysicalDeviceDepthStencilResolveProperties )                    depthStencilResolveProperties;
            __C_ENG_TYPE ( PhysicalDeviceDescriptorIndexingProperties )                     descriptorIndexingProperties;
            __C_ENG_TYPE ( PhysicalDeviceFloatControlsProperties )                          deviceFloatControlsProperties;
            __C_ENG_TYPE ( PhysicalDeviceSamplerFilterMinmaxProperties )                    samplerFilterMinmaxProperties;
            __C_ENG_TYPE ( PhysicalDeviceTimelineSemaphoreProperties )                      timelineSemaphoreProperties;

            __C_ENG_TYPE ( PhysicalDeviceVulkan12Features )                                 vulkan12Features;
            __C_ENG_TYPE ( PhysicalDevice8BitStorageFeatures )                              _8BitStorageFeatures;
            __C_ENG_TYPE ( PhysicalDeviceBufferDeviceAddressFeatures )                      bufferDeviceAddressFeatures;
            __C_ENG_TYPE ( PhysicalDeviceDescriptorIndexingFeatures )                       descriptorIndexingFeatures;
            __C_ENG_TYPE ( PhysicalDeviceHostQueryResetFeatures )                           hostQueryResetFeatures;
            __C_ENG_TYPE ( PhysicalDeviceImagelessFrameBufferFeatures )                     imagelessFramebufferFeatures;
            __C_ENG_TYPE ( PhysicalDeviceScalarBlockLayoutFeatures )                        scalarBlockLayoutFeatures;
            __C_ENG_TYPE ( PhysicalDeviceSeparateDepthStencilLayoutsFeatures )              separateDepthStencilLayoutsFeatures;
            __C_ENG_TYPE ( PhysicalDeviceShaderAtomicInt64Features )                        shaderAtomicInt64Features;
            __C_ENG_TYPE ( PhysicalDeviceShaderFloat16Int8Features )                        shaderFloat16Int8Features;
            __C_ENG_TYPE ( PhysicalDeviceShaderSubgroupExtendedTypesFeatures )              shaderSubgroupExtendedTypesFeatures;
            __C_ENG_TYPE ( PhysicalDeviceTimelineSemaphoreFeatures )                        timelineSemaphoreFeatures;
            __C_ENG_TYPE ( PhysicalDeviceUniformBufferStandardLayoutFeatures )              uniformBufferStandardLayoutFeatures;
            __C_ENG_TYPE ( PhysicalDeviceVulkanMemoryModelFeatures )                        vulkanMemoryModelFeatures;

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceVulkan13Properties )                               vulkan13Properties;

            __C_ENG_TYPE ( PhysicalDeviceVulkan13Features )                                 vulkan13Features;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_4444_FORMATS_AVAILABLE

            __C_ENG_TYPE ( PhysicalDevice4444FormatsFeatures )                              _4444FormatsFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ASTC_DECODE_MODE_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceASTCDecodeFeatures )                               ASTCDecodeFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PCI_BUS_INFO_AVAILABLE

            __C_ENG_TYPE ( PhysicalDevicePCIBusInfoProperties )                             pciBusInfoProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PHYSICAL_DEVICE_DRM_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceDRMProperties )                                    DRMProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceAccelerationStructureProperties )                  accelerationStructureProperties;
            __C_ENG_TYPE ( PhysicalDeviceAccelerationStructureFeatures )                    accelerationStructureFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceBlendOperationAdvancedProperties )                 blendOperationAdvancedProperties;
            __C_ENG_TYPE ( PhysicalDeviceBlendOperationAdvancedFeatures )                   blendOperationAdvancedFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BORDER_COLOR_SWIZZLE_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceBorderColorSwizzleFeatures )                       borderColorSwizzleFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_DEVICE_COHERENT_MEMORY_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceCoherentMemoryFeaturesAMD )                        coherentMemoryFeaturesAMD;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_COLOR_WRITE_ENABLE_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceColorWriteEnableFeatures )                         colorWriteEnabledFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COMPUTE_SHADER_DERIVATIVES_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceComputeShaderDerivativesFeaturesNVidia )           computeShaderDerivativesFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceConditionalRenderingFeatures )                     conditionalRenderingFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONSERVATIVE_RASTERIZATION_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceConservativeRasterizationProperties )              conservativeRasterizationProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceCooperativeMatrixPropertiesNVidia )                cooperativeMatrixPropertiesNVidia;
            __C_ENG_TYPE ( PhysicalDeviceCooperativeMatrixFeaturesNVidia )                  cooperativeMatrixFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CORNER_SAMPLED_IMAGE_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceCornerSampledImageFeaturesNVidia )                 cornerSampledImageFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COVERAGE_REDUCTION_MODE_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceCoverageReductionModeFeaturesNVidia )              coverageReductionModeFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceCustomBorderColorProperties )                      customBorderColorProperties;
            __C_ENG_TYPE ( PhysicalDeviceCustomBorderColorFeatures )                        customBorderColorFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_IMAGE_ALIASING_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNVidia )   dedicatedAllocationImageAliasingFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_CONTROL_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceDepthClipControlFeatures )                         depthClipControlFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_ENABLE_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceDepthClipEnableFeatures )                          depthClipEnableFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceDeviceGeneratedCommandsPropertiesNVidia )          deviceGeneratedCommandsProperties;
            __C_ENG_TYPE ( PhysicalDeviceDeviceGeneratedCommandsFeaturesNVidia )            deviceGeneratedCommandsFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEVICE_MEMORY_REPORT_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceDeviceMemoryReportFeatures )                       deviceMemoryReportFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTICS_CONFIG_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceDiagnosticsConfigFeaturesNVidia )                  diagnosticsConfigFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISCARD_RECTANGLES_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceDiscardRectangleProperties )                       discardRectangleProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceDynamicRenderingFeatures )                         dynamicRenderingFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SCISSOR_EXCLUSIVE_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceExclusiveScissorFeaturesNVidia )                   exclusiveScissorFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceExtendedDynamicStateFeatures )                     extendedDynamicStateFeatures;
            __C_ENG_TYPE ( PhysicalDeviceExtendedDynamicState2Features )                    extendedDynamicState2Features;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTERNAL_MEMORY_HOST_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceExternalMemoryHostProperties )                     externalMemoryHostProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_RDMA_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceExternalMemoryRDMAFeaturesNVidia )                 externalMemoryRDMAFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMapFeatures )                       fragmentDensityMapFeatures;
            __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMapProperties )                     fragmentDensityMapProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMap2Features )                      fragmentDensityMap2Features;
            __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMap2Properties )                    fragmentDensityMap2Properties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMapOffsetFeaturesQualcomm )         fragmentDensityMapOffsetFeaturesQualcomm;
            __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMapOffsetPropertiesQualcomm )       fragmentDensityMapOffsetPropertiesQualcomm;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADER_BARYCENTRIC_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceFragmentShaderBarycentricFeaturesNVidia )          fragmentShaderBarycentricFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_SHADER_INTERLOCK_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceFragmentShaderInterlockFeatures )                  fragmentShaderInterlockFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceFragmentShadingRateEnumsFeaturesNVidia )           fragmentShadingRateEnumsFeaturesNVidia;
            __C_ENG_TYPE ( PhysicalDeviceFragmentShadingRateEnumsPropertiesNVidia )         fragmentShadingRateEnumsPropertiesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceFragmentShadingRateFeatures )                      fragmentShadingRateFeatures;
            __C_ENG_TYPE ( PhysicalDeviceFragmentShadingRateProperties )                    fragmentShadingRateProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceGlobalPriorityQueryFeatures )                      globalPriorityQueryFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_ROBUSTNESS_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceImageRobustnessFeatures )                          imageRobustnessFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_VIEW_MIN_LOD_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceImageViewMinLODFeatures )                          imageViewMinLODFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INDEX_TYPE_UINT8_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceIndexTypeUInt8Features )                           indexTypeUInt8Features;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_INHERITED_VIEWPORT_SCISSOR_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceInheritedViewportScissorFeaturesNVidia )           inheritedViewportScissorFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceInlineUniformBlockProperties )                     inlineUniformBlockProperties;
            __C_ENG_TYPE ( PhysicalDeviceInlineUniformBlockFeatures )                       inlineUniformBlockFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_INVOCATION_MASK_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceInvocationMaskFeaturesHuawei )                     invocationMaskFeaturesHuawei;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceLineRasterizationProperties )                      lineRasterizationProperties;
            __C_ENG_TYPE ( PhysicalDeviceLineRasterizationFeatures )                        lineRasterizationFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_LINEAR_COLOR_ATTACHMENT_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceLinearColorAttachmentFeaturesNVidia )              linearColorAttachmentFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceMaintenance4Properties )                           maintenance4Properties;
            __C_ENG_TYPE ( PhysicalDeviceMaintenance4Features )                             maintenance4Features;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_PRIORITY_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceMemoryPriorityFeatures )                           memoryPriorityFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceMeshShaderPropertiesNVidia )                       meshShaderPropertiesNVidia;
            __C_ENG_TYPE ( PhysicalDeviceMeshShaderFeaturesNVidia )                         meshShaderFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceMultiDrawProperties )                              multiDrawProperties;
            __C_ENG_TYPE ( PhysicalDeviceMultiDrawFeatures )                                multiDrawFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceMutableDescriptorTypeFeaturesValve )               mutableDescriptorTypeFeaturesValve;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceMultiviewPerViewAttributesPropertiesNVidia )       multiviewPerViewAttributesPropertiesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PAGEABLE_DEVICE_LOCAL_MEMORY_AVAILABLE

            __C_ENG_TYPE ( PhysicalDevicePageableDeviceLocalMemoryFeatures )                pageableDeviceLocalMemoryFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

            __C_ENG_TYPE ( PhysicalDevicePerformanceQueryProperties )                       performanceQueryProperties;
            __C_ENG_TYPE ( PhysicalDevicePerformanceQueryFeatures )                         performanceQueryFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            __C_ENG_TYPE ( PhysicalDevicePipelineCreationCacheControlFeatures )             pipelineCreationCacheControlFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE

            __C_ENG_TYPE ( PhysicalDevicePipelineExecutablePropertiesFeatures )             pipelineExecutablePropertiesFeatures;

#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE

            __C_ENG_TYPE ( PhysicalDevicePortabilitySubsetProperties )                      portabilitySubsetProperties;
            __C_ENG_TYPE ( PhysicalDevicePortabilitySubsetFeatures )                        portabilitySubsetFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_ID_AVAILABLE

            __C_ENG_TYPE ( PhysicalDevicePresentIDFeatures )                                presentIDFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_WAIT_AVAILABLE

            __C_ENG_TYPE ( PhysicalDevicePresentWaitFeatures )                              presentWaitFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIMITIVE_TOPOLOGY_LIST_RESTART_AVAILABLE

            __C_ENG_TYPE ( PhysicalDevicePrimitiveTopologyListRestartFeatures )             primitiveTopologyListRestartFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            __C_ENG_TYPE ( PhysicalDevicePrivateDataFeatures )                              privateDataFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceProvokingVertexProperties )                        provokingVertexProperties;
            __C_ENG_TYPE ( PhysicalDeviceProvokingVertexFeatures )                          provokingVertexFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PUSH_DESCRIPTOR_AVAILABLE

            __C_ENG_TYPE ( PhysicalDevicePushDescriptorProperties )                         pushDescriptorProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_RGBA_10_X_6_FORMATS_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceRGBA10x6FormatsFeatures )                          RGBA10x6FormatsFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ARM_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM )    rasterizationOrderAttachmentAccessFeaturesARM;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_QUERY_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceRayQueryFeatures )                                 rayQueryFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceRayTracingPropertiesNVidia )                       rayTracingPropertiesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceRayTracingMotionBlurFeaturesNVidia )               rayTracingMotionBlurFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceRayTracingPipelineProperties )                     rayTracingPipelineProperties;
            __C_ENG_TYPE ( PhysicalDeviceRayTracingPipelineFeatures )                       rayTracingPipelineFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_REPRESENTATIVE_FRAGMENT_TEST_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceRepresentativeFragmentTestFeaturesNVidia )         representativeFragmentTestFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceRobustnessProperties )                             robustnessProperties;
            __C_ENG_TYPE ( PhysicalDeviceRobustnessFeatures )                               robustnessFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceSampleLocationsProperties )                        sampleLocationsProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceShaderAtomicFloatFeatures )                        shaderAtomicFloatFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_2_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceShaderAtomicFloat2Features )                       shaderAtomicFloat2Features;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceShaderCorePropertiesAMD )                          shaderCorePropertiesAMD;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_2_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceShaderCoreProperties2AMD )                         shaderCoreProperties2AMD;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_CLOCK_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceShaderClockFeatures )                              shaderClockFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_DEMOTE_TO_HELPER_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceShaderDemoteToHelperInvocationFeatures )           shaderDemoteToHelperInvocationFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_IMAGE_ATOMIC_INT64_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceShaderImageAtomicInt64Features )                   shaderImageAtomicInt64Features;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_IMAGE_FOOTPRINT_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceShaderImageFootprintFeaturesNVidia )               shaderImageFootprintFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceShaderSMBuiltinsPropertiesNVidia )                 shaderSmBuiltinsPropertiesNVidia;
            __C_ENG_TYPE ( PhysicalDeviceShaderSMBuiltinsFeaturesNVidia )                   shaderSmBuiltinsFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_SUBGROUP_UNIFORM_CONTROL_FLOW_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceShaderSubgroupUniformControlFlowFeatures )         shaderSubgroupUniformControlFlowFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_TERMINATE_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceShaderTerminateInvocationFeatures )                shaderTerminateInvocationFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceShadingRateImagePropertiesNVidia )                 shadingRateImagePropertiesNVidia;
            __C_ENG_TYPE ( PhysicalDeviceShadingRateImageFeaturesNVidia )                   shadingRateImageFeaturesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceSubgroupSizeControlProperties )                    subgroupSizeControlProperties;
            __C_ENG_TYPE ( PhysicalDeviceSubgroupSizeControlFeatures )                      subgroupSizeControlFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceSubpassShadingPropertiesHuawei )                   subpassShadingPropertiesHuawei;
            __C_ENG_TYPE ( PhysicalDeviceSubpassShadingFeaturesHuawei )                     subpassShadingFeaturesHuawei;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceSynchronizationFeatures )                          synchronizationFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceTexelBufferAlignmentProperties )                   texelBufferAlignmentProperties;
            __C_ENG_TYPE ( PhysicalDeviceTexelBufferAlignmentFeatures )                     texelBufferAlignmentFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXTURE_COMPRESSION_ASTC_HDR_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceTextureCompressionASTCHDRFeatures )                textureCompressionASTCHDRFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceTransformFeedbackProperties )                      transformFeedbackProperties;
            __C_ENG_TYPE ( PhysicalDeviceTransformFeedbackFeatures )                        transformFeedbackFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceVertexAttributeDivisorProperties )                 vertexAttributeDivisorProperties;
            __C_ENG_TYPE ( PhysicalDeviceVertexAttributeDivisorFeatures )                   vertexAttributeDivisorFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_INPUT_DYNAMIC_STATE_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceVertexInputDynamicStateFeatures )                  vertexInputDynamicStateFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceShaderIntegerDotProductProperties )                shaderIntegerDotProductProperties;
            __C_ENG_TYPE ( PhysicalDeviceShaderIntegerDotProductFeatures )                  shaderIntegerDotProductFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_SHADER_INTEGER_FUNCTIONS_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceShaderIntegerFunctionsFeaturesIntel )              shaderIntegerFunctionsFeaturesIntel;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceWorkgroupMemoryExplicitLayoutFeatures )            workgroupMemoryExplicitLayoutFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_2_PLANE_444_FORMATS_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceYCBCR2Plane444FormatsFeatures )                    YCBCR2Plane444FormatFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_IMAGE_ARRAYS_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceYCBCRImageArraysFeatures )                         YCBCRImageArraysFeatures;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ZERO_INITIALIZE_WORKGROUP_MEMORY_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceZeroInitializeWorkgroupMemoryFeatures )            zeroInitializeWorkgroupMemoryFeatures;

#endif

        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( ComponentMapping,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( ComponentSwizzle )   r;
            Type ( ComponentSwizzle )   g;
            Type ( ComponentSwizzle )   b;
            Type ( ComponentSwizzle )   a;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( ImageSubresourceRange,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( ImageAspectFlags )   aspectMask;
            cds :: uint32               baseMipLevel;
            cds :: uint32               levelCount;
            cds :: uint32               baseArrayLayer;
            cds :: uint32               layerCount;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( ImageViewCreateInfo,   NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( ImageViewCreateFlags )       flags;
            Type ( ImageHandle )                image;
            Type ( ImageViewType )              viewType;
            Type ( Format )                     format;
            Type ( ComponentMapping )           components;
            Type ( ImageSubresourceRange )      subresourceRange;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( DeviceQueueInfo,   NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )              structureType;
            __C_ENG_TYPE ( GenericStructure )         * pNext;
            __C_ENG_TYPE ( DeviceQueueCreateFlags )     flags;
            cds :: uint32                               queueFamilyIndex;
            cds :: uint32                               queueIndex;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( ImageViewUsageCreateInfo,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( ImageUsageFlags )            usage;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( SamplerYCBCRConversionInfo,    NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            Type ( SamplerYCBCRConversionHandle )           conversion;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAMEBUFFER_MIXED_SAMPLES_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_AMD_MIXED_ATTACHMENT_SAMPLES_AVAILABLE

        namespace hidden {

            struct __AttachmentSampleCountInfo { // NOLINT(bugprone-reserved-identifier)
                __C_ENG_TYPE ( StructureType )              structureType;
                __C_ENG_TYPE ( GenericStructure )   const * pNext;
                cds :: uint32                               colorAttachmentCount;
                __C_ENG_TYPE ( SampleCountFlag )    const * pColorAttachmentSamples;
                __C_ENG_TYPE ( SampleCountFlag )            depthStencilAttachmentSamples;
            };

        }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAMEBUFFER_MIXED_SAMPLES_AVAILABLE

        __C_ENG_ALIAS ( AttachmentSampleCountInfoNVidia,    hidden :: __AttachmentSampleCountInfo );

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_MIXED_ATTACHMENT_SAMPLES_AVAILABLE

        __C_ENG_ALIAS ( AttachmentSampleCountInfoAMD,       hidden :: __AttachmentSampleCountInfo );

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( MultiviewPerViewAttributesInfoNVidia,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( Bool )                       perViewAttributes;
            Type ( Bool )                       perViewAttributesPositionXOnly;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif

#endif


#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( CommandBufferInheritanceConditionalRenderingInfo,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( Bool )                       conditionalRenderingEnable;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_RENDER_PASS_TRANSFORM_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( CommandBufferInheritanceRenderPassTransformInfoQualcomm,   NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( SurfaceTransformFlag )       transform;
            Type ( Rect )                       renderArea;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( CommandBufferInheritanceRenderingInfo,   NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( RenderingFlags )             flags;
            cds :: uint32                       viewMask;
            cds :: uint32                       colorAttachmentCount;
            Type ( Format )             const * pColorAttachmentFormats;
            Type ( Format )                     depthAttachmentFormat;
            Type ( Format )                     stencilAttachmentFormat;
            Type ( SampleCountFlag )            rasterizationSamples;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_INHERITED_VIEWPORT_SCISSOR_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( CommandBufferInheritanceViewportScissorInfoNVidia,   NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( Bool )                       viewportScissor2D;
            cds :: uint32                       viewportDepthCount;
            Type ( Viewport )           const * pViewportDepths;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

#define C_ENG_MAP_START     ENUM ( SubmitFlag,  TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Protected, VkSubmitFlagBits :: VK_SUBMIT_PROTECTED_BIT ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

        __C_ENG_ALIAS ( SubmitFlags,    VkSubmitFlags );

#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE

#define C_ENG_MAP_START     ENUM ( SubmitFlag,  TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Protected, VkSubmitFlagBitsKHR :: VK_SUBMIT_PROTECTED_BIT_KHR ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

        __C_ENG_ALIAS ( SubmitFlags,    VkSubmitFlagsKHR );

#endif


#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( SemaphoreSubmitInfo,   NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            Type ( SemaphoreHandle )                    semaphore;
            cds :: uint64                               value;
            Type ( PipelineStageFlags )                 stageMask;
            cds :: uint32                               deviceIndex;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( CommandBufferSubmitInfo,   NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            Type ( CommandBufferHandle )                commandBuffer;
            cds :: uint32                               deviceMask;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( SubmitInfo2,    NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            Type ( SubmitFlags )                        flags;
            cds :: uint32                               waitSemaphoreInfoCount;
            Type ( SemaphoreSubmitInfo )        const * pWaitSemaphoreInfos;
            cds :: uint32                               commandBufferInfoCount;
            Type ( CommandBufferSubmitInfo )    const * pCommandBufferInfos;
            cds :: uint32                               signalSemaphoreInfoCount;
            Type ( SemaphoreSubmitInfo )        const * pSignalSemaphoreInfos;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( SubmitInfo,    NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            cds :: uint32                               waitSemaphoreCount;
            Type ( SemaphoreHandle )            const * pWaitSemaphores;
            Type ( PipelineStageFlags )         const * pWaitDestinationStageMasks;
            cds :: uint32                               commandBufferCount;
            Type ( CommandBufferHandle )        const * pCommandBuffers;
            cds :: uint32                               signalSemaphoreCount;
            Type ( SemaphoreHandle )            const * pSignalSemaphores;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( DeviceGroupSubmitInfo,    NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            cds :: uint32                       waitSemaphoreCount;
            cds :: uint32               const * pWaitSemaphoreDeviceIndices;
            cds :: uint32                       commandBufferCount;
            cds :: uint32               const * pCommandBufferDeviceMasks;
            cds :: uint32                       signalSemaphoreCount;
            cds :: uint32               const * pSignalSemaphoreDeviceIndices;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( ProtectedSubmitInfo,    NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( Bool )                       protectedSubmit;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( TimelineSemaphoreSubmitInfo,    NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            cds :: uint32                       waitSemaphoreValueCount;
            cds :: uint64               const * pWaitSemaphoreValues;
            cds :: uint32                       signalSemaphoreValueCount;
            cds :: uint64               const * pSignalSemaphoreValues;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( PerformanceQuerySubmitInfo,    NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            cds :: uint32                       counterPassIndex;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WIN32_KEYED_MUTEX_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( Win32KeyedMutexAcquireReleaseInfo,    NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            cds :: uint32                       acquireCount;
            Type ( DeviceMemory )       const * pAcquireSyncs;
            cds :: uint64               const * pAcquireKeys;
            cds :: uint32               const * pAcquireTimeouts;
            cds :: uint32                       releaseCount;
            Type ( DeviceMemory )       const * pReleaseSyncs;
            cds :: uint64               const * pReleaseKeys;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_WIN32_KEYED_MUTEX_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( Win32KeyedMutexAcquireReleaseInfoNVidia,    NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            cds :: uint32                       acquireCount;
            Type ( DeviceMemory )       const * pAcquireSyncs;
            cds :: uint64               const * pAcquireKeys;
            cds :: uint32               const * pAcquireTimeoutsMilliseconds;
            cds :: uint32                       releaseCount;
            Type ( DeviceMemory )       const * pReleaseSyncs;
            cds :: uint64               const * pReleaseKeys;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_WIN32_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( D3D12FenceSubmitInfo,    NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            cds :: uint32                       waitSemaphoreValuesCount;
            cds :: uint64               const * pWaitSemaphoreValues;
            cds :: uint32                       signalSemaphoreValuesCount;
            cds :: uint64               const * pSignalSemaphoreValues;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( FenceCreateInfo,   NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( FenceCreateFlags )           flags;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( ExportFenceCreateInfo,   NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                  structureType;
            Type ( GenericStructure )       const * pNext;
            Type ( ExternalFenceHandleTypeFlags )   handleTypes;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_WIN32_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( ExportFenceWin32HandleInfo,   NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                  structureType;
            Type ( GenericStructure )       const * pNext;
            SECURITY_ATTRIBUTES             const * pAttributes;
            DWORD                                   dwAccess;
            LPCWSTR                                 name;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_FD_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( FenceGetFDInfo,    NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                  structureType;
            Type ( GenericStructure )       const * pNext;
            Type ( FenceHandle )                    fence;
            Type ( ExternalFenceHandleTypeFlag )    handleType;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISPLAY_CONTROL_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( DeviceEventInfo,    NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                  structureType;
            Type ( GenericStructure )       const * pNext;
            Type ( DeviceEventType )                deviceEvent;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( DisplayEventInfo,    NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                  structureType;
            Type ( GenericStructure )       const * pNext;
            Type ( DisplayEventType )               displayEvent;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_WIN32_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( ImportFenceWin32HandleInfo,    NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                  structureType;
            Type ( GenericStructure )       const * pNext;
            Type ( FenceHandle )                    fence;
            Type ( FenceImportFlags )               flags;
            Type ( ExternalFenceHandleTypeFlag )    handleType;
            HANDLE                                  handle;
            LPCWSTR                                 name;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_FENCE_FD_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( ImportFenceFdInfo,    NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                  structureType;
            Type ( GenericStructure )       const * pNext;
            Type ( FenceHandle )                    fence;
            Type ( FenceImportFlags )               flags;
            Type ( ExternalFenceHandleTypeFlag )    handleType;
            int                                     fd;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

#define C_ENG_MAP_START STRUCT ( SemaphoreCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                  structureType;
            Type ( GenericStructure )       const * pNext;
            Type ( SemaphoreCreateFlags )           flags;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

#define C_ENG_MAP_START STRUCT ( ExportSemaphoreCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                              structureType;
            Type ( GenericStructure )                   const * pNext;
            Type ( ExternalSemaphoreHandleTypeFlags )           handleTypes;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

#define C_ENG_MAP_START STRUCT ( SemaphoreTypeCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                              structureType;
            Type ( GenericStructure )                   const * pNext;
            Type ( SemaphoreType )                              semaphoreType;
            cds :: uint64                                       initialValue;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_WIN32_AVAILABLE

#define C_ENG_MAP_START STRUCT ( SemaphoreGetWin32HandleInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                              structureType;
            Type ( GenericStructure )                   const * pNext;
            Type ( SemaphoreHandle )                            semaphore;
            Type ( ExternalSemaphoreHandleTypeFlag )            handleType;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( ImportSemaphoreWin32HandleInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                              structureType;
            Type ( GenericStructure )                   const * pNext;
            Type ( SemaphoreHandle )                            semaphore;
            Type ( SemaphoreImportFlags )                       flags;
            Type ( ExternalSemaphoreHandleTypeFlag )            handleType;
            HANDLE                                              handle;
            LPCWSTR                                             name;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_SEMAPHORE_FD_AVAILABLE

#define C_ENG_MAP_START STRUCT ( SemaphoreGetFdInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                              structureType;
            Type ( GenericStructure )                   const * pNext;
            Type ( SemaphoreHandle )                            semaphore;
            Type ( ExternalSemaphoreHandleTypeFlag )            handleType;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( ImportSemaphoreFdInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                              structureType;
            Type ( GenericStructure )                   const * pNext;
            Type ( SemaphoreHandle )                            semaphore;
            Type ( SemaphoreImportFlags )                       flags;
            Type ( ExternalSemaphoreHandleTypeFlag )            handleType;
            int                                                 fd;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_SEMAPHORE_AVAILABLE

#define C_ENG_MAP_START STRUCT ( SemaphoreGetZirconHandleInfoGoogle, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                              structureType;
            Type ( GenericStructure )                   const * pNext;
            Type ( SemaphoreHandle )                            semaphore;
            Type ( ExternalSemaphoreHandleTypeFlag )            handleType;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( ImportSemaphoreZirconHandleInfoGoogle, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                              structureType;
            Type ( GenericStructure )                   const * pNext;
            Type ( SemaphoreHandle )                            semaphore;
            Type ( SemaphoreImportFlags )                       flags;
            Type ( ExternalSemaphoreHandleTypeFlag )            handleType;
            zx_handle_t                                         zirconHandle;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START STRUCT ( EventCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                              structureType;
            Type ( GenericStructure )                   const * pNext;
            Type ( EventCreateFlags )                           flags;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

#define C_ENG_MAP_START STRUCT ( SemaphoreWaitInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                              structureType;
            Type ( GenericStructure )                   const * pNext;
            Type ( SemaphoreWaitFlags )                         flags;
            cds :: uint32                                       semaphoreCount;
            Type ( SemaphoreHandle )                    const * pSemaphores;
            cds :: uint64                               const * pValues;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( SemaphoreSignalInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                              structureType;
            Type ( GenericStructure )                   const * pNext;
            Type ( SemaphoreHandle )                            semaphore;
            cds :: uint64                                       value;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
#define C_ENG_MAP_START STRUCT ( MemoryBarrier2, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                              structureType;
            Type ( GenericStructure )                   const * pNext;
            Type ( PipelineStageFlags )                         sourceStageMask;
            Type ( AccessFlags )                                sourceAccessMask;
            Type ( PipelineStageFlags )                         destinationStageMask;
            Type ( AccessFlags )                                destinationAccessMask;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( BufferMemoryBarrier2, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                              structureType;
            Type ( GenericStructure )                   const * pNext;
            Type ( PipelineStageFlags )                         sourceStageMask;
            Type ( AccessFlags )                                sourceAccessMask;
            Type ( PipelineStageFlags )                         destinationStageMask;
            Type ( AccessFlags )                                destinationAccessMask;
            cds :: uint32                                       sourceQueueFamilyIndex;
            cds :: uint32                                       destinationQueueFamilyIndex;
            Type ( BufferHandle )                               buffer;
            Type ( DeviceSize )                                 offset;
            Type ( DeviceSize )                                 size;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( ImageMemoryBarrier2, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                              structureType;
            Type ( GenericStructure )                   const * pNext;
            Type ( PipelineStageFlags )                         sourceStageMask;
            Type ( AccessFlags )                                sourceAccessMask;
            Type ( PipelineStageFlags )                         destinationStageMask;
            Type ( AccessFlags )                                destinationAccessMask;
            Type ( ImageLayout )                                oldLayout;
            Type ( ImageLayout )                                newLayout;
            cds :: uint32                                       sourceQueueFamilyIndex;
            cds :: uint32                                       destinationQueueFamilyIndex;
            Type ( ImageHandle )                                image;
            Type ( ImageSubresourceRange )                      subresourceRange;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( DependencyInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                              structureType;
            Type ( GenericStructure )                   const * pNext;
            Type ( DependencyFlags )                            dependencyFlags;
            cds :: uint32                                       memoryBarrierCount;
            Type ( MemoryBarrier2 )                     const * pMemoryBarriers;
            cds :: uint32                                       bufferMemoryBarrierCount;
            Type ( BufferMemoryBarrier2 )               const * pBufferMemoryBarriers;
            cds :: uint32                                       imageMemoryBarrierCount;
            Type ( ImageMemoryBarrier2 )                const * pImageMemoryBarriers;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE
#define C_ENG_MAP_START STRUCT ( SampleLocation, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            float x;
            float y;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( SampleLocationsInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                              structureType;
            Type ( GenericStructure )                   const * pNext;
            Type ( SampleCountFlag )                            sampleLocationsPerPixel;
            Type ( Extent2D )                                   sampleLocationGridSize;
            cds :: uint32                                       sampleLocationsCount;
            Type ( SampleLocation )                     const * pSampleLocations;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START STRUCT ( MemoryBarrier, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( AccessFlags )                sourceAccessMask;
            Type ( AccessFlags )                destinationAccessMask;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( BufferMemoryBarrier, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( AccessFlags )                sourceAccessMask;
            Type ( AccessFlags )                destinationAccessMask;
            cds :: uint32                       sourceQueueFamilyIndex;
            cds :: uint32                       destinationQueueFamilyIndex;
            Type ( BufferHandle )               buffer;
            Type ( DeviceSize )                 offset;
            Type ( DeviceSize )                 size;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( ImageMemoryBarrier, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( AccessFlags )                sourceAccessMask;
            Type ( AccessFlags )                destinationAccessMask;
            Type ( ImageLayout )                oldLayout;
            Type ( ImageLayout )                newLayout;
            cds :: uint32                       sourceQueueFamilyIndex;
            cds :: uint32                       destinationQueueFamilyIndex;
            Type ( ImageHandle )                image;
            Type ( ImageSubresourceRange )      subresourceRange;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_CALIBRATED_TIMESTAMPS_AVAILABLE
#define C_ENG_MAP_START ENUM ( TimeDomain,  TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Device,                     VkTimeDomainEXT :: VK_TIME_DOMAIN_DEVICE_EXT ),
            Field ( ClockMonotonic,             VkTimeDomainEXT :: VK_TIME_DOMAIN_CLOCK_MONOTONIC_EXT ),
            Field ( ClockMonotonicRaw,          VkTimeDomainEXT :: VK_TIME_DOMAIN_CLOCK_MONOTONIC_RAW_EXT ),
            Field ( QueryPerformanceCounter,    VkTimeDomainEXT :: VK_TIME_DOMAIN_QUERY_PERFORMANCE_COUNTER_EXT ),
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( CalibratedTimestampInfo,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( TimeDomain )                 timeDomain;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( GetCalibratedTimestamps,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( DeviceHandle )                       device;
            cds :: uint32                               timestampCount;
            Type ( CalibratedTimestampInfo )    const * pTimestampInfos;
            cds :: uint64                             * pTimestamps;
            cds :: uint64                             * pMaxDeviation;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START ENUM ( AttachmentLoadOperation, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Load,       VkAttachmentLoadOp :: VK_ATTACHMENT_LOAD_OP_LOAD ),
            Field ( Clear,      VkAttachmentLoadOp :: VK_ATTACHMENT_LOAD_OP_CLEAR ),
            Field ( DontCare,   VkAttachmentLoadOp :: VK_ATTACHMENT_LOAD_OP_DONT_CARE ),

#if __C_ENG_VULKAN_API_EXTENSION_LOAD_STORE_OP_NONE_AVAILABLE
            Field ( None,       VkAttachmentLoadOp :: VK_ATTACHMENT_LOAD_OP_NONE_EXT ),
#endif
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START ENUM ( AttachmentStoreOperation, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Store,      VkAttachmentStoreOp :: VK_ATTACHMENT_STORE_OP_STORE ),
            Field ( DontCare,   VkAttachmentStoreOp :: VK_ATTACHMENT_STORE_OP_DONT_CARE ),

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
            Field ( None,       VkAttachmentStoreOp :: VK_ATTACHMENT_STORE_OP_NONE ),
#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE
            Field ( None,       VkAttachmentStoreOp :: VK_ATTACHMENT_STORE_OP_NONE_KHR ),
#elif __C_ENG_VULKAN_API_EXTENSION_LOAD_STORE_OP_NONE_AVAILABLE
            Field ( None,       VkAttachmentStoreOp :: VK_ATTACHMENT_STORE_OP_NONE_EXT ),
#elif __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_RENDER_PASS_STORE_OPERATIONS_AVAILABLE
            Field ( None,       VkAttachmentStoreOp :: VK_ATTACHMENT_STORE_OP_NONE_QCOM ),
#endif
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START UNION ( ClearColorValue,  NO_PARENT )
#include <ObjectMapping.hpp>

        Union {
            float           float32[4];
            cds :: sint32   int32[4];
            cds :: uint32   uint32[4];
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( ClearDepthStencilValue,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            float           depth;
            cds :: uint32   stencil;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START UNION ( ClearValue,  NO_PARENT )
#include <ObjectMapping.hpp>

        Union {
            Type ( ClearColorValue )        color;
            Type ( ClearDepthStencilValue ) depthStencil;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
#define C_ENG_MAP_START STRUCT ( RenderingAttachmentInfo,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            Type ( ImageViewHandle )                    imageView;
            Type ( ImageLayout )                        imageLayout;
            Type ( ResolveModeFlag )                    resolveMode;
            Type ( ImageViewHandle )                    resolveImageView;
            Type ( ImageLayout )                        resolveImageLayout;
            Type ( AttachmentLoadOperation )            loadOperation;
            Type ( AttachmentStoreOperation )           storeOperation;
            Type ( ClearValue )                         clearValue;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( RenderingInfo,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            Type ( RenderingFlags )                     flags;
            Type ( Rect )                               renderArea;
            cds :: uint32                               layerCount;
            cds :: uint32                               viewMask;
            cds :: uint32                               colorAttachmentCount;
            Type ( RenderingAttachmentInfo )    const * pColorAttachments;
            Type ( RenderingAttachmentInfo )    const * pDepthAttachment;
            Type ( RenderingAttachmentInfo )    const * pStencilAttachment;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define C_ENG_MAP_START STRUCT ( DeviceGroupRenderPassBeginInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            cds :: uint32                               deviceMask;
            cds :: uint32                               deviceRenderAreaCount;
            Type ( Rect )                       const * pDeviceRenderAreas;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if ( __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE ) && __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE
#define C_ENG_MAP_START STRUCT ( RenderingFragmentDensityMapAttachmentInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            Type ( ImageViewHandle )                    imageView;
            Type ( ImageLayout )                        imageLayout;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if ( __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE ) && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE
#define C_ENG_MAP_START STRUCT ( RenderingFragmentShadingRateAttachmentInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            Type ( ImageViewHandle )                    imageView;
            Type ( ImageLayout )                        imageLayout;
            Type ( Extent2D )                           shadingRateAttachmentTexelSize;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START STRUCT ( AttachmentDescription, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( AttachmentDescriptionFlags ) flags;
            Type ( Format )                     format;
            Type ( SampleCountFlag )            samples;
            Type ( AttachmentLoadOperation )    loadOperation;
            Type ( AttachmentStoreOperation )   storeOperation;
            Type ( AttachmentLoadOperation )    stencilLoadOperation;
            Type ( AttachmentStoreOperation )   stencilStoreOperation;
            Type ( ImageLayout )                initialLayout;
            Type ( ImageLayout )                finalLayout;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( AttachmentReference, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            cds :: uint32           attachment;
            Type ( ImageLayout )    layout;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( SubpassDescription, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( SubpassDescriptionFlags )        flags;
            Type ( PipelineBindPoint )              pipelineBindPoint;
            cds :: uint32                           inputAttachmentCount;
            Type ( AttachmentReference )    const * pInputAttachments;
            cds :: uint32                           colorAttachmentsCount;
            Type ( AttachmentReference )    const * pColorAttachments;
            Type ( AttachmentReference )    const * pResolveAttachments;
            Type ( AttachmentReference )    const * pDepthStencilAttachment;
            cds :: uint32                           preserveAttachmentCount;
            cds :: uint32                   const * pPreserveAttachments;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( SubpassDependency, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            cds :: uint32               sourceSubpass;
            cds :: uint32               destinationSubpass;
            Type ( PipelineStageFlags ) sourceStageMask;
            Type ( PipelineStageFlags ) destinationStageMask;
            Type ( AccessFlags )        sourceAccessMask;
            Type ( AccessFlags )        destinationAccessMask;
            Type ( DependencyFlags )    dependencyFlags;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( RenderPassCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            Type ( RenderPassCreateFlags )              flags;
            cds :: uint32                               attachmentCount;
            Type ( AttachmentDescription )      const * pAttachments;
            cds :: uint32                               subpassCount;
            Type ( SubpassDescription )         const * pSubpasses;
            cds :: uint32                               dependencyCount;
            Type ( SubpassDependency )          const * pDependencies;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
#define C_ENG_MAP_START STRUCT ( AttachmentDescription2, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( AttachmentDescriptionFlags ) flags;
            Type ( Format )                     format;
            Type ( SampleCountFlag )            samples;
            Type ( AttachmentLoadOperation )    loadOperation;
            Type ( AttachmentStoreOperation )   storeOperation;
            Type ( AttachmentLoadOperation )    stencilLoadOperation;
            Type ( AttachmentStoreOperation )   stencilStoreOperation;
            Type ( ImageLayout )                initialLayout;
            Type ( ImageLayout )                finalLayout;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( AttachmentDescriptionStencilLayout, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( ImageLayout )                stencilInitialLayout;
            Type ( ImageLayout )                stencilFinalLayout;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( AttachmentReferenceStencilLayout, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( ImageLayout )                stencilLayout;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( AttachmentReference2, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            cds :: uint32                       attachment;
            Type ( ImageLayout )                layout;
            Type ( ImageAspectFlags )           aspectMask;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( SubpassDescription2, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                  structureType;
            Type ( GenericStructure )       const * pNext;
            Type ( SubpassDescriptionFlags )        flags;
            Type ( PipelineBindPoint )              pipelineBindPoint;
            cds :: uint32                           viewMask;
            cds :: uint32                           inputAttachmentCount;
            Type ( AttachmentReference2 )   const * pInputAttachments;
            cds :: uint32                           colorAttachmentsCount;
            Type ( AttachmentReference2 )   const * pColorAttachments;
            Type ( AttachmentReference2 )   const * pResolveAttachments;
            Type ( AttachmentReference2 )   const * pDepthStencilAttachment;
            cds :: uint32                           preserveAttachmentCount;
            cds :: uint32                   const * pPreserveAttachments;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( SubpassDescriptionDepthStencilResolve, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                  structureType;
            Type ( GenericStructure )       const * pNext;
            Type ( ResolveModeFlag )                depthResolveMode;
            Type ( ResolveModeFlag )                stencilResolveMode;
            Type ( AttachmentReference2 )   const * pDepthStencilResolveAttachment;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( SubpassDependency2, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                  structureType;
            Type ( GenericStructure )       const * pNext;
            cds :: uint32                           sourceSubpass;
            cds :: uint32                           destinationSubpass;
            Type ( PipelineStageFlags )             sourceStageMask;
            Type ( PipelineStageFlags )             destinationStageMask;
            Type ( AccessFlags )                    sourceAccessMask;
            Type ( AccessFlags )                    destinationAccessMask;
            Type ( DependencyFlags )                dependencyFlags;
            cds :: sint32                           viewOffset;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( RenderPassCreateInfo2, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            Type ( RenderPassCreateFlags )              flags;
            cds :: uint32                               attachmentCount;
            Type ( AttachmentDescription2 )     const * pAttachments;
            cds :: uint32                               subpassCount;
            Type ( SubpassDescription2 )        const * pSubpasses;
            cds :: uint32                               dependencyCount;
            Type ( SubpassDependency2 )         const * pDependencies;
            cds :: uint32                               correlatedViewMaskCount;
            cds :: uint32                       const * pCorrelatedViewMasks;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE
#define C_ENG_MAP_START STRUCT ( FragmentShadingRateAttachmentInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            Type ( AttachmentReference2 )       const * pFragmentShadingRateAttachment;
            Type ( Extent2D )                           shadingRateAttachmentTexelSize;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE
#define C_ENG_MAP_START STRUCT ( RenderPassFragmentDensityMapCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            Type ( AttachmentReference )                fragmentDensityMapAttachment;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define C_ENG_MAP_START STRUCT ( InputAttachmentAspectReference, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            cds :: uint32               subpass;
            cds :: uint32               inputAttachmentIndex;
            Type ( ImageAspectFlags )   aspectMask;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( RenderPassInputAttachmentAspectCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            cds :: uint32                                   aspectReferenceCount;
            Type ( InputAttachmentAspectReference ) const * pAspectReferences;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( RenderPassMultiviewCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            cds :: uint32                                   subpassCount;
            cds :: uint32                           const * pViewMasks;
            cds :: uint32                                   dependencyCount;
            cds :: sint32                           const * pViewOffsets;
            cds :: uint32                                   correlationMaskCount;
            cds :: uint32                           const * pCorrelationMasks;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START STRUCT ( FrameBufferCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( FrameBufferCreateFlags )     flags;
            Type ( RenderPassHandle )           renderPass;
            cds :: uint32                       attachmentCount;
            Type ( ImageViewHandle )    const * pAttachments;
            cds :: uint32                       width;
            cds :: uint32                       height;
            cds :: uint32                       layers;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
#define C_ENG_MAP_START STRUCT ( FrameBufferAttachmentImageInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            Type ( ImageCreateFlags )                       flags;
            Type ( ImageUsageFlags )                        usage;
            cds :: uint32                                   width;
            cds :: uint32                                   height;
            cds :: uint32                                   layerCount;
            cds :: uint32                                   viewFormatCount;
            Type ( Format )                         const * pViewFormats;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( FrameBufferAttachmentsCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            cds :: uint32                                   attachmentImageInfoCount;
            Type ( FrameBufferAttachmentImageInfo ) const * pAttachmentImageInfos;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START STRUCT ( RenderPassBeginInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( RenderPassHandle )           renderPass;
            Type ( FrameBufferHandle )          frameBuffer;
            Type ( Rect )                       renderArea;
            cds :: uint32                       clearValueCount;
            Type ( ClearValue )         const * pClearValues;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
#define C_ENG_MAP_START STRUCT ( RenderPassAttachmentBeginInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            cds :: uint32                       attachmentCount;
            Type ( ImageViewHandle )    const * pAttachments;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE
#define C_ENG_MAP_START STRUCT ( AttachmentSampleLocations, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            cds :: uint32                   attachmentIndex;
            Type ( SampleLocationsInfo )    sampleLocationsInfo;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( SubpassSampleLocations, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            cds :: uint32                   subpassIndex;
            Type ( SampleLocationsInfo )    sampleLocationsInfo;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( RenderPassSampleLocationsBeginInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            cds :: uint32                               attachmentInitialSampleLocationsCount;
            Type ( AttachmentSampleLocations )  const * pAttachmentInitialSampleLocations;
            cds :: uint32                               postSubpassSampleLocationsCount;
            Type ( SubpassSampleLocations )     const * pPostSubpassSampleLocations;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_RENDER_PASS_TRANSFORM_AVAILABLE
#define C_ENG_MAP_START STRUCT ( RenderPassTransformBeginInfoQualcomm, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( SurfaceTransformFlag )       transform;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
#define C_ENG_MAP_START STRUCT ( SubpassBeginInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( SubpassContents )            contents;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
#define C_ENG_MAP_START STRUCT ( SubpassEndInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE
#define C_ENG_MAP_START STRUCT ( SubpassFragmentDensityMapOffsetEndInfoQualcomm, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            cds :: uint32                       fragmentDensityOffsetCount;
            Type ( Offset2D )           const * pFragmentDensityOffsets;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START STRUCT ( ShaderModuleCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( ShaderModuleCreateFlags )    flags;
            cds :: uint64                       codeSize;
            cds :: uint32               const * pCode;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_CACHE_AVAILABLE
#define C_ENG_MAP_START STRUCT ( ShaderModuleValidationCacheCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( ValidationCacheHandle )      validationCache;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE
#define C_ENG_MAP_START STRUCT ( CooperativeMatrixPropertiesNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            cds :: uint32                       MSize;
            cds :: uint32                       NSize;
            cds :: uint32                       KSize;
            Type ( ComponentTypeNVidia )        AType;
            Type ( ComponentTypeNVidia )        BType;
            Type ( ComponentTypeNVidia )        CType;
            Type ( ComponentTypeNVidia )        DType;
            Type ( ScopeNVidia )                scope;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_CACHE_AVAILABLE
#define C_ENG_MAP_START STRUCT ( ValidationCacheCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( ValidationCacheCreateFlags ) flags;
            cds :: uint64                       initialDataSize;
            void                        const * pInitialData;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START STRUCT ( SpecializationMapEntry, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            cds :: uint32   constantID;
            cds :: uint32   offset;
            cds :: uint32   size;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( SpecializationInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            cds :: uint32                           mapEntryCount;
            Type ( SpecializationMapEntry ) const * pMapEntries;
            cds :: uint64                           dataSize;
            void                            const * pData;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( PipelineShaderStageCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            Type ( PipelineShaderStageCreateFlags )         flags;
            Type ( ShaderStageFlag )                        stage;
            Type ( ShaderModuleHandle )                     module;
            char                                    const * pName;
            Type ( SpecializationInfo )             const * pSpecializationInfo;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( ComputePipelineCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            Type ( PipelineCreateFlags )                    flags;
            Type ( PipelineShaderStageCreateInfo )          stage;
            Type ( PipelineLayoutHandle )                   layout;
            Type ( PipelineHandle )                         basePipelineHandle;
            cds :: sint32                                   basePipelineIndex;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_AMD_PIPELINE_COMPILER_CONTROL_AVAILABLE
#define C_ENG_MAP_START STRUCT ( PipelineCompilerControlCreateInfoAMD, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            Type ( PipelineCompilerControlFlagsAMD )        compilerControlFlags;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_FEEDBACK_AVAILABLE
#define C_ENG_MAP_START STRUCT ( PipelineCreationFeedback, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( PipelineCreationFeedbackFlags )  flags;
            cds :: uint64                           duration;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( PipelineCreationFeedbackCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            Type ( PipelineCreationFeedback )             * pPipelineCreationFeedback;
            cds :: uint32                                   pipelineStageCreationFeedbackCount;
            Type ( PipelineCreationFeedback )             * pPipelineStageCreationFeedbacks;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE
#define C_ENG_MAP_START STRUCT ( SubpassShadingPipelineCreateInfoHuawei, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( RenderPassHandle )           renderPass;
            cds :: uint32                       subpass;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE
#define C_ENG_MAP_START STRUCT ( PipelineShaderStageRequiredSubgroupSizeCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            cds :: uint32                       requiredSubgroupSize;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START STRUCT ( VertexInputBindingDescription, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            cds :: uint32               binding;
            cds :: uint32               stride;
            Type ( VertexInputRate )    inputRate;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( VertexInputAttributeDescription, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            cds :: uint32               location;
            cds :: uint32               binding;
            Type ( Format )             format;
            cds :: uint32               offset;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( PipelineVertexInputStateCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                                  structureType;
            Type ( GenericStructure )                       const * pNext;
            Type ( PipelineVertexInputStateCreateFlags )            flags;
            cds :: uint32                                           vertexBindingDescriptionCount;
            Type ( VertexInputBindingDescription )          const * pVertexBindingDescriptions;
            cds :: uint32                                           vertexAttributeDescriptionCount;
            Type ( VertexInputAttributeDescription )        const * pVertexAttributeDescriptions;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( PipelineInputAssemblyStateCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                                  structureType;
            Type ( GenericStructure )                       const * pNext;
            Type ( PipelineInputAssemblyStateCreateFlags )          flags;
            Type ( PrimitiveTopology )                              topology;
            Type ( Bool )                                           primitiveRestartEnable;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( PipelineTessellationStateCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                                  structureType;
            Type ( GenericStructure )                       const * pNext;
            Type ( PipelineTessellationStateCreateFlags )           flags;
            cds :: uint32                                           patchControlPoints;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( PipelineViewportStateCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                              structureType;
            Type ( GenericStructure )                   const * pNext;
            Type ( PipelineViewportStateCreateFlags )           flags;
            cds :: uint32                                       viewportCount;
            Type ( Viewport )                           const * pViewports;
            cds :: uint32                                       scissorCount;
            Type ( Rect )                               const * pScissors;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( PipelineRasterizationStateCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                              structureType;
            Type ( GenericStructure )                   const * pNext;
            Type ( PipelineRasterizationStateCreateFlags )      flags;
            Type ( Bool )                                       depthClampEnable;
            Type ( Bool )                                       rasterizerDiscardEnable;
            Type ( PolygonMode )                                polygonMode;
            Type ( CullModeFlags )                              cullMode;
            Type ( FrontFace )                                  frontFace;
            Type ( Bool )                                       depthBiasEnable;
            float                                               depthBiasConstantFactor;
            float                                               depthBiasClamp;
            float                                               depthBiasSlopeFactor;
            float                                               lineWidth;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( PipelineMultisampleStateCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                              structureType;
            Type ( GenericStructure )                   const * pNext;
            Type ( PipelineMultisampleStateCreateFlags )        flags;
            Type ( SampleCountFlag )                            rasterizationSamples;
            Type ( Bool )                                       sampleShadingEnable;
            float                                               minSampleShading;
            Type ( SampleMask )                         const * pSampleMask;
            Type ( Bool )                                       alphaToCoverageEnable;
            Type ( Bool )                                       alphaToOneEnable;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( StencilOperationState, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StencilOperation )   failOperation;
            Type ( StencilOperation )   passOperation;
            Type ( StencilOperation )   depthFailOperation;
            Type ( CompareOperation )   compareOperation;
            cds :: uint32               compareMask;
            cds :: uint32               writeMask;
            cds :: uint32               reference;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( PipelineDepthStencilStateCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                              structureType;
            Type ( GenericStructure )                   const * pNext;
            Type ( PipelineDepthStencilStateCreateFlags )       flags;
            Type ( Bool )                                       depthTestEnable;
            Type ( Bool )                                       depthWriteEnable;
            Type ( CompareOperation )                           depthCompareOperation;
            Type ( Bool )                                       depthBoundsTestEnable;
            Type ( Bool )                                       stencilTestEnable;
            Type ( StencilOperationState )                      front;
            Type ( StencilOperationState )                      back;
            float                                               minDepthBounds;
            float                                               maxDepthBounds;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( PipelineColorBlendAttachmentState, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( Bool )                   blendEnable;
            Type ( BlendFactor )            sourceColorBlendFactor;
            Type ( BlendFactor )            destinationColorBlendFactor;
            Type ( BlendOperation )         colorBlendOperation;
            Type ( BlendFactor )            sourceAlphaBlendFactor;
            Type ( BlendFactor )            destinationAlphaBlendFactor;
            Type ( BlendOperation )         alphaBlendOperation;
            Type ( ColorComponentFlags )    colorWriteMask;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( PipelineColorBlendStateCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                              structureType;
            Type ( GenericStructure )                   const * pNext;
            Type ( PipelineColorBlendStateCreateFlags )         flags;
            Type ( Bool )                                       logicOperationEnable;
            Type ( LogicOperation )                             logicOperation;
            cds :: uint32                                       attachmentCount;
            Type ( PipelineColorBlendAttachmentState )  const * pAttachments;
            float                                               blendConstants[4];
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( PipelineDynamicStateCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                              structureType;
            Type ( GenericStructure )                   const * pNext;
            Type ( PipelineDynamicStateCreateFlags )            flags;
            cds :: uint32                                       dynamicStateCount;
            Type ( DynamicState )                       const * pDynamicStates;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( GraphicsPipelineCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                                  structureType;
            Type ( GenericStructure )                       const * pNext;
            Type ( PipelineCreateFlags )                            flags;
            cds :: uint32                                           stageCount;
            Type ( PipelineShaderStageCreateInfo )          const * pStages;
            Type ( PipelineVertexInputStateCreateInfo )     const * pVertexInputState;
            Type ( PipelineInputAssemblyStateCreateInfo )   const * pInputAssemblyState;
            Type ( PipelineTessellationStateCreateInfo )    const * pTessellationState;
            Type ( PipelineViewportStateCreateInfo )        const * pViewportState;
            Type ( PipelineRasterizationStateCreateInfo )   const * pRasterizationState;
            Type ( PipelineMultisampleStateCreateInfo )     const * pMultisampleState;
            Type ( PipelineDepthStencilStateCreateInfo )    const * pDepthStencilState;
            Type ( PipelineColorBlendStateCreateInfo )      const * pColorBlendState;
            Type ( PipelineDynamicStateCreateInfo )         const * pDynamicState;
            Type ( PipelineLayoutHandle )                           layout;
            Type ( RenderPassHandle )                               renderPass;
            cds :: uint32                                           subpass;
            Type ( PipelineHandle )                                 basePipelineHandle;
            cds :: sint32                                           basePipelineIndex;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE
#define C_ENG_MAP_START STRUCT ( GraphicsShaderGroupCreateInfoNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                                  structureType;
            Type ( GenericStructure )                       const * pNext;
            cds :: uint32                                           stageCount;
            Type ( PipelineShaderStageCreateInfo )          const * pStages;
            Type ( PipelineVertexInputStateCreateInfo )     const * pVertexInputState;
            Type ( PipelineTessellationStateCreateInfo )    const * pTessellationState;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( GraphicsPipelineShaderGroupsCreateInfoNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                                  structureType;
            Type ( GenericStructure )                       const * pNext;
            cds :: uint32                                           groupCount;
            Type ( GraphicsShaderGroupCreateInfoNVidia )    const * pGroups;
            cds :: uint32                                           pipelineCount;
            Type ( PipelineHandle )                         const * pPipelines;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE
#define C_ENG_MAP_START STRUCT ( VertexInputBindingDivisorDescription, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            cds :: uint32   binding;
            cds :: uint32   divisor;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( PipelineVertexInputDivisorStateCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                                  structureType;
            Type ( GenericStructure )                       const * pNext;
            cds :: uint32                                           vertexBindingDivisorCount;
            Type ( VertexInputBindingDivisorDescription )   const * pVertexBindingDivisors;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_DISCARD_RECTANGLES_AVAILABLE
#define C_ENG_MAP_START STRUCT ( PipelineDiscardRectangleStateCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                                  structureType;
            Type ( GenericStructure )                       const * pNext;
            Type ( PipelineDiscardRectangleStateCreateFlags )       flags;
            Type ( DiscardRectangleMode )                           discardRectangleMode;
            cds :: uint32                                           discardRectangleCount;
            Type ( Rect )                                   const * pDiscardRectangles;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE
#define C_ENG_MAP_START STRUCT ( PipelineFragmentShadingRateEnumStateCreateInfoNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                                  structureType;
            Type ( GenericStructure )                       const * pNext;
            Type ( FragmentShadingRateTypeNVidia )                  shadingRateType;
            Type ( FragmentShadingRateNVidia )                      shadingRate;
            Type ( FragmentShadingRateCombinerOperation )           combinerOperations[2];
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE
#define C_ENG_MAP_START STRUCT ( PipelineFragmentShadingRateStateCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                                  structureType;
            Type ( GenericStructure )                       const * pNext;
            Type ( Extent2D )                                       fragmentSize;
            Type ( FragmentShadingRateCombinerOperation )           combinerOperations[2];
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE
#define C_ENG_MAP_START STRUCT ( PipelineRenderingCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            cds :: uint32                       viewMask;
            cds :: uint32                       colorAttachmentCount;
            Type ( Format )             const * pColorAttachmentFormats;
            Type ( Format )                     depthAttachmentFormat;
            Type ( Format )                     stencilAttachmentFormat;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_REPRESENTATIVE_FRAGMENT_TEST_AVAILABLE
#define C_ENG_MAP_START STRUCT ( PipelineRepresentativeFragmentTestStateCreateInfoNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( Bool )                       representativeFragmentTestEnable;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define C_ENG_MAP_START STRUCT ( PipelineTessellationDomainOriginStateCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( TessellationDomainOrigin )   domainOrigin;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE
#define C_ENG_MAP_START STRUCT ( CoarseSampleLocationNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            cds :: uint32   pixelX;
            cds :: uint32   pixelY;
            cds :: uint32   sample;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( CoarseSampleOrderCustomNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( ShadingRatePaletteEntryNVidia )      shadingRate;
            cds :: uint32                               sampleCount;
            cds :: uint32                               sampleLocationCount;
            Type ( CoarseSampleLocationNVidia ) const * pSampleLocations;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( PipelineViewportCoarseSampleOrderStateCreateInfoNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            Type ( CoarseSampleOrderTypeNVidia )            sampleOrderType;
            cds :: uint32                                   customSampleOrderCount;
            Type ( CoarseSampleOrderCustomNVidia )  const * pCustomSampleOrders;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( ShadingRatePaletteNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            cds :: uint32                                   shadingRatePaletteEntryCount;
            Type ( ShadingRatePaletteEntryNVidia )  const * pShadingRatePaletteEntries;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( PipelineViewportShadingRateImageStateCreateInfoNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            Type ( Bool )                                   shadingRateImageEnable;
            cds :: uint32                                   viewportCount;
            Type ( ShadingRatePaletteNVidia )       const * pShadingRatePalettes;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_CONTROL_AVAILABLE
#define C_ENG_MAP_START STRUCT ( PipelineViewportDepthClipControlCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( Bool )                       negativeOneToOne;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SCISSOR_EXCLUSIVE_AVAILABLE
#define C_ENG_MAP_START STRUCT ( PipelineViewportExclusiveScissorStateCreateInfoNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            cds :: uint32                       exclusiveScissorCount;
            Type ( Rect )               const * pExclusiveScissors;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_VIEWPORT_SWIZZLE_AVAILABLE
#define C_ENG_MAP_START STRUCT ( ViewportSwizzleNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( ViewportCoordinateSwizzleNVidia )    x;
            Type ( ViewportCoordinateSwizzleNVidia )    y;
            Type ( ViewportCoordinateSwizzleNVidia )    z;
            Type ( ViewportCoordinateSwizzleNVidia )    w;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( PipelineViewportSwizzleStateCreateInfoNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                                          structureType;
            Type ( GenericStructure )                               const * pNext;
            Type ( PipelineViewportSwizzleStateCreateFlagsNVidia )          flags;
            cds :: uint32                                                   viewportCount;
            Type ( ViewportSwizzleNVidia )                          const * pViewportSwizzles;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CLIP_SPACE_W_SCALING_AVAILABLE
#define C_ENG_MAP_START STRUCT ( ViewportWScalingNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            float xCoefficient;
            float yCoefficient;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( PipelineViewportWScalingStateCreateInfoNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                  structureType;
            Type ( GenericStructure )       const * pNext;
            Type ( Bool )                           viewportWScalingEnable;
            cds :: uint32                           viewportCount;
            Type ( ViewportWScalingNVidia ) const * pViewportWScalings;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_CONSERVATIVE_RASTERIZATION_AVAILABLE
#define C_ENG_MAP_START STRUCT ( PipelineRasterizationConservativeStateCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                                              structureType;
            Type ( GenericStructure )                                   const * pNext;
            Type ( PipelineRasterizationConservativeStateCreateFlags )          flags;
            Type ( ConservativeRasterizationMode )                              conservativeRasterizationMode;
            float                                                               extraPrimitiveOverestimationSize;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_ENABLE_AVAILABLE
#define C_ENG_MAP_START STRUCT ( PipelineRasterizationDepthClipStateCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                                              structureType;
            Type ( GenericStructure )                                   const * pNext;
            Type ( PipelineRasterizationDepthClipStateCreateFlags )             flags;
            Type ( Bool )                                                       depthClipEnable;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE
#define C_ENG_MAP_START STRUCT ( PipelineRasterizationLineStateCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                  structureType;
            Type ( GenericStructure )       const * pNext;
            Type ( LineRasterizationMode )          lineRasterizationMode;
            Type ( Bool )                           stippledLineEnable;
            cds :: uint32                           lineStippleFactor;
            cds :: uint16                           lineStipplePattern;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE
#define C_ENG_MAP_START STRUCT ( PipelineRasterizationProvokingVertexStateCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                  structureType;
            Type ( GenericStructure )       const * pNext;
            Type ( ProvokingVertexMode )            provokingVertexMode;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_AMD_RASTERIZATION_ORDER_AVAILABLE
#define C_ENG_MAP_START STRUCT ( PipelineRasterizationStateRasterizationOrderAMD, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                  structureType;
            Type ( GenericStructure )       const * pNext;
            Type ( RasterizationOrderAMD )          rasterizationOrder;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE
#define C_ENG_MAP_START STRUCT ( PipelineRasterizationStateStreamCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                                      structureType;
            Type ( GenericStructure )                           const * pNext;
            Type ( PipelineRasterizationStateStreamCreateFlags )        flags;
            cds :: uint32                                               rasterizationStream;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAMEBUFFER_MIXED_SAMPLES_AVAILABLE
#define C_ENG_MAP_START STRUCT ( PipelineCoverageModulationStateCreateInfoNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                                      structureType;
            Type ( GenericStructure )                           const * pNext;
            Type ( PipelineCoverageModulationStateCreateFlagsNVidia )   flags;
            Type ( CoverageModulationModeNVidia )                       coverageModulationMode;
            Type ( Bool )                                               coverageModulationTableEnable;
            cds :: uint32                                               coverageModulationTableCount;
            float                                               const * pCoverageModulationTable;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COVERAGE_REDUCTION_MODE_AVAILABLE
#define C_ENG_MAP_START STRUCT ( PipelineCoverageReductionStateCreateInfoNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                                      structureType;
            Type ( GenericStructure )                           const * pNext;
            Type ( PipelineCoverageReductionStateCreateFlagsNVidia )    flags;
            Type ( CoverageReductionModeNVidia )                        coverageReductionMode;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_COVERAGE_TO_COLOR_AVAILABLE
#define C_ENG_MAP_START STRUCT ( PipelineCoverageToColorStateCreateInfoNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                                      structureType;
            Type ( GenericStructure )                           const * pNext;
            Type ( PipelineCoverageToColorStateCreateFlagsNVidia )      flags;
            Type ( Bool )                                               coverageToColorEnable;
            cds :: uint32                                               coverageToColorLocation;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE
#define C_ENG_MAP_START STRUCT ( PipelineSampleLocationsStateCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                                      structureType;
            Type ( GenericStructure )                           const * pNext;
            Type ( Bool )                                               sampleLocationsEnable;
            Type ( SampleLocationsInfo )                                sampleLocationsInfo;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE
#define C_ENG_MAP_START STRUCT ( PipelineColorBlendAdvancedStateCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                                      structureType;
            Type ( GenericStructure )                           const * pNext;
            Type ( Bool )                                               sourcePremultiplied;
            Type ( Bool )                                               destinationPremultiplied;
            Type ( BlendOverlap )                                       blendOverlap;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_COLOR_WRITE_ENABLE_AVAILABLE
#define C_ENG_MAP_START STRUCT ( PipelineColorWriteCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                                      structureType;
            Type ( GenericStructure )                           const * pNext;
            cds :: uint32                                               attachmentCount;
            Type ( Bool )                                       const * pColorWriteEnables;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
#define C_ENG_MAP_START STRUCT ( RayTracingShaderGroupCreateInfoNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                                      structureType;
            Type ( GenericStructure )                           const * pNext;
            Type ( RayTracingShaderGroupType )                          type;
            cds :: uint32                                               generalShader;
            cds :: uint32                                               closestHitShader;
            cds :: uint32                                               anyHitShader;
            cds :: uint32                                               intersectionShader;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( RayTracingPipelineCreateInfoNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                                      structureType;
            Type ( GenericStructure )                           const * pNext;
            Type ( PipelineCreateFlags )                                flags;
            cds :: uint32                                               stageCount;
            Type ( PipelineShaderStageCreateInfo )              const * pStages;
            cds :: uint32                                               groupCount;
            Type ( RayTracingShaderGroupCreateInfoNVidia )      const * pGroups;
            cds :: uint32                                               maxRecursionDepth;
            Type ( PipelineLayoutHandle )                               layout;
            Type ( PipelineHandle )                                     basePipelineHandle;
            cds :: sint32                                               basePipelineIndex;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
#define C_ENG_MAP_START STRUCT ( RayTracingShaderGroupCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                                      structureType;
            Type ( GenericStructure )                           const * pNext;
            Type ( RayTracingShaderGroupType )                          type;
            cds :: uint32                                               generalShader;
            cds :: uint32                                               closestHitShader;
            cds :: uint32                                               anyHitShader;
            cds :: uint32                                               intersectionShader;
            void                                                const * pShaderGroupCaptureReplayHandle;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( PipelineLibraryCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                                      structureType;
            Type ( GenericStructure )                           const * pNext;
            cds :: uint32                                               libraryCount;
            Type ( PipelineHandle )                             const * pLibraries;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( RayTracingPipelineInterfaceCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                                      structureType;
            Type ( GenericStructure )                           const * pNext;
            cds :: uint32                                               maxPipelineRayPayloadSize;
            cds :: uint32                                               maxPipelineRayHitAttributeSize;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( RayTracingPipelineCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                                      structureType;
            Type ( GenericStructure )                           const * pNext;
            Type ( PipelineCreateFlags )                                flags;
            cds :: uint32                                               stageCount;
            Type ( PipelineShaderStageCreateInfo )              const * pStages;
            cds :: uint32                                               groupCount;
            Type ( RayTracingShaderGroupCreateInfo )            const * pGroups;
            cds :: uint32                                               maxPipelineRayRecursionDepth;
            Type ( PipelineLibraryCreateInfo )                  const * pLibraryInfo;
            Type ( RayTracingPipelineInterfaceCreateInfo )      const * pLibraryInterface;
            Type ( PipelineDynamicStateCreateInfo )             const * pDynamicState;
            Type ( PipelineLayoutHandle )                               layout;
            Type ( PipelineHandle )                                     basePipelineHandle;
            cds :: sint32                                               basePipelineIndex;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START STRUCT ( PipelineCacheCreateInfo,   NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( PipelineCacheCreateFlags )   flags;
            cds :: uint64                       initialDataSize;
            void                        const * pInitialData;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START STRUCT ( PipelineCacheHeaderVersionOne,   NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            cds :: uint32                               headerSize;
            Type ( PipelineCacheHeaderVersionValue )    headerVersion;
            cds :: uint32                               vendorID;
            cds :: uint32                               deviceID;
            cds :: uint8                                pipelineCacheUUID [ VK_UUID_SIZE ];
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
#define C_ENG_MAP_START STRUCT ( PipelineInfo,   NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( PipelineHandle )             pipeline;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( PipelineExecutableProperties,   NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( ShaderStageFlags )           stages;
            char                                name [ VK_MAX_DESCRIPTION_SIZE ];
            char                                description [ VK_MAX_DESCRIPTION_SIZE ];
            cds :: uint32                       subgroupSize;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START UNION ( PipelineExecutableStatisticValue,   NO_PARENT )
#include <ObjectMapping.hpp>

        Union {
            bool        b;

            cds :: sint64   s64;
            cds :: uint64   u64;

            double      f64;
            double      d;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( PipelineExecutableStatistic,   NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            char                                        name [ VK_MAX_DESCRIPTION_SIZE ];
            char                                        description [ VK_MAX_DESCRIPTION_SIZE ];
            Type ( PipelineExecutableStatisticFormat )  format;
            Type ( PipelineExecutableStatisticValue )   value;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( PipelineExecutableInfo,   NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            Type ( PipelineHandle )                     pipeline;
            cds :: uint32                               executableIndex;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( PipelineExecutableInternalRepresentation,   NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            char                                        name [ VK_MAX_DESCRIPTION_SIZE ];
            char                                        description [ VK_MAX_DESCRIPTION_SIZE ];
            Type ( Bool )                               isText;
            cds :: uint64                               dataSize;
            void                                      * pData;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_INFO_AVAILABLE
#define C_ENG_MAP_START STRUCT ( ShaderResourceUsageAMD,   NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            cds :: uint32   numUsedVgrps;
            cds :: uint32   numUsedSgrps;
            cds :: uint32   ldsSizePerLogicalWorkGroup;
            cds :: uint64   ldsUsageSizeInBytes;
            cds :: uint64   scratchMemUsageInBytes;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( ShaderStatisticsInfoAMD,   NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( ShaderStageFlags )       shaderStageMask;
            Type ( ShaderResourceUsageAMD ) resourceUsage;
            cds :: uint32                   numPhysicalVgrps;
            cds :: uint32                   numPhysicalSgrps;
            cds :: uint32                   numAvailableVgrps;
            cds :: uint32                   numAvailableSgrps;
            cds :: uint32                   computeWorkGroupSize[3];
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START STRUCT ( MemoryType, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( MemoryPropertyFlags )    propertyFlags;
            cds :: uint32                   heapIndex;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( MemoryHeap, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( DeviceSize )         size;
            Type ( MemoryHeapFlags )    flags;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( PhysicalDeviceMemoryProperties, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            cds :: uint32       memoryTypeCount;
            Type ( MemoryType ) memoryTypes [ VK_MAX_MEMORY_TYPES ];
            cds :: uint32       memoryHeapCount;
            Type ( MemoryHeap ) memoryHeaps [ VK_MAX_MEMORY_HEAPS ];
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define C_ENG_MAP_START STRUCT ( PhysicalDeviceMemoryProperties2, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                  structureType;
            Type ( GenericStructure )             * pNext;
            Type ( PhysicalDeviceMemoryProperties ) properties;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_BUDGET_AVAILABLE
#define C_ENG_MAP_START STRUCT ( PhysicalDeviceMemoryBudgetProperties, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                  structureType;
            Type ( GenericStructure )             * pNext;
            Type ( DeviceSize )                     heapBudget [ VK_MAX_MEMORY_HEAPS ];
            Type ( DeviceSize )                     heapUsage [ VK_MAX_MEMORY_HEAPS ];
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START STRUCT ( MemoryAllocateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( DeviceSize )                 allocationSize;
            cds :: uint32                       memoryTypeIndex;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_AVAILABLE
#define C_ENG_MAP_START STRUCT ( DedicatedAllocationMemoryAllocateInfoNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( ImageHandle )                image;
            Type ( BufferHandle )               buffer;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define C_ENG_MAP_START STRUCT ( ExportMemoryAllocateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            Type ( ExternalMemoryHandleTypeFlags )          handleTypes;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_AVAILABLE
#define C_ENG_MAP_START STRUCT ( ExportMemoryAllocateInfoNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            Type ( ExternalMemoryHandleTypeFlagsNVidia )    handleTypes;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_WIN32_AVAILABLE
#define C_ENG_MAP_START STRUCT ( ExportMemoryWin32HandleInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            SECURITY_ATTRIBUTES                     const * pAttributes;
            DWORD                                           dwAccess;
            LPCWSTR                                         name;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_WIN32_AVAILABLE
#define C_ENG_MAP_START STRUCT ( MemoryGetWin32HandleInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            Type ( DeviceMemoryHandle )                     memory;
            Type ( ExternalMemoryHandleTypeFlag )           handleType;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_WIN32_AVAILABLE
#define C_ENG_MAP_START STRUCT ( ExportMemoryWin32HandleInfoNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            SECURITY_ATTRIBUTES                     const * pAttributes;
            DWORD                                           dwAccess;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_AVAILABLE
#define C_ENG_MAP_START STRUCT ( ImportAndroidHardwareBufferInfoAndroid, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            AHardwareBuffer                   * buffer;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_BUFFER_COLLECTION_AVAILABLE
#define C_ENG_MAP_START STRUCT ( ImportMemoryBufferCollectionFuchsia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            Type ( BufferCollectionFuchsiaHandle )      collection;
            cds :: uint32                               index;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_FD_AVAILABLE
#define C_ENG_MAP_START STRUCT ( ImportMemoryFdInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            Type ( ExternalMemoryHandleTypeFlag )       handleType;
            int                                         fd;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTERNAL_MEMORY_HOST_AVAILABLE
#define C_ENG_MAP_START STRUCT ( ImportMemoryHostPointerInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            Type ( ExternalMemoryHandleTypeFlag )       handleType;
            void                                      * pHostPointer;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_WIN32_AVAILABLE
#define C_ENG_MAP_START STRUCT ( ImportMemoryWin32HandleInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            Type ( ExternalMemoryHandleTypeFlag )       handleType;
            HANDLE                                      handle;
            LPCWSTR                                     name;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START STRUCT ( MemoryWin32HandleProperties, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )                 * pNext;
            cds :: uint32                               memoryTypeBits;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_WIN32_AVAILABLE
#define C_ENG_MAP_START STRUCT ( ImportMemoryWin32HandleInfoNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            Type ( ExternalMemoryHandleTypeFlagsNVidia )    handleType;
            HANDLE                                          handle;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_MEMORY_AVAILABLE
#define C_ENG_MAP_START STRUCT ( ImportMemoryZirconHandleFuchsia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            Type ( ExternalMemoryHandleTypeFlag )       handleType;
            zx_handle_t                                 handle;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define C_ENG_MAP_START STRUCT ( MemoryAllocateFlagsInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            Type ( MemoryAllocateFlags )                flags;
            cds :: uint32                               deviceMask;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define C_ENG_MAP_START STRUCT ( MemoryDedicatedAllocateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            Type ( ImageHandle )                        image;
            Type ( BufferHandle )                       buffer;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
#define C_ENG_MAP_START STRUCT ( MemoryOpaqueCaptureAddressAllocateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            cds :: uint64                               opaqueCaptureAddress;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_PRIORITY_AVAILABLE
#define C_ENG_MAP_START STRUCT ( MemoryPriorityAllocateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            float                                       priority;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_FD_AVAILABLE
#define C_ENG_MAP_START STRUCT ( MemoryGetFdInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            Type ( DeviceMemoryHandle )                 memory;
            Type ( ExternalMemoryHandleTypeFlag )       handleType;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_FD_AVAILABLE
#define C_ENG_MAP_START STRUCT ( MemoryFdProperties, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )                 * pNext;
            cds :: uint32                               memoryTypeBits;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTERNAL_MEMORY_HOST_AVAILABLE
#define C_ENG_MAP_START STRUCT ( MemoryHostPointerProperties, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )                 * pNext;
            cds :: uint32                               memoryTypeBits;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_RDMA_AVAILABLE
#define C_ENG_MAP_START STRUCT ( MemoryGetRemoteAddressInfoNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            Type ( DeviceMemoryHandle )                 memory;
            Type ( ExternalMemoryHandleTypeFlag )       handleType;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START STRUCT ( MappedMemoryRange, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            Type ( DeviceMemoryHandle )                 memory;
            Type ( DeviceSize )                         offset;
            Type ( DeviceSize )                         size;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
#define C_ENG_MAP_START STRUCT ( DeviceMemoryOpaqueCaptureAddressInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            Type ( DeviceMemoryHandle )                 memory;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START STRUCT ( BufferCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( BufferCreateFlags )          flags;
            Type ( DeviceSize )                 size;
            Type ( BufferUsageFlags )           usage;
            Type ( SharingMode )                sharingMode;
            cds :: uint32                       queueFamilyIndexCount;
            cds :: uint32               const * pQueueFamilyIndices;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_BUFFER_COLLECTION_AVAILABLE
#define C_ENG_MAP_START STRUCT ( BufferCollectionBufferCreateInfoFuchsia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            Type ( BufferCollectionHandleFuchsia )          collection;
            cds :: uint32                                   index;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_BUFFER_DEVICE_ADDRESS_AVAILABLE
#define C_ENG_MAP_START STRUCT ( BufferDeviceAddressCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            Type ( DeviceAddress )                          deviceAddress;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
#define C_ENG_MAP_START STRUCT ( BufferOpaqueCaptureAddressCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            cds :: uint64                                   opaqueCaptureAddress;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_AVAILABLE
#define C_ENG_MAP_START STRUCT ( DedicatedAllocationBufferCreateInfoNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            Type ( Bool )                                   dedicatedAllocation;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define C_ENG_MAP_START STRUCT ( ExternalMemoryBufferCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            Type ( ExternalMemoryHandleTypeFlags )          handleTypes;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_DECODE_H264_AVAILABLE
#define C_ENG_MAP_START STRUCT ( VideoDecodeH264Profile, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            StdVideoH264ProfileIdc                          stdProfileIdc;
            Type ( VideoDecodeH264PictureLayoutFlags )      pictureLayout;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_DECODE_H265_AVAILABLE
#define C_ENG_MAP_START STRUCT ( VideoDecodeH265Profile, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            StdVideoH265ProfileIdc                          stdProfileIdc;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_ENCODE_H264_AVAILABLE
#define C_ENG_MAP_START STRUCT ( VideoEncodeH264Profile, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            StdVideoH264ProfileIdc                          stdProfileIdc;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_ENCODE_H265_AVAILABLE
#define C_ENG_MAP_START STRUCT ( VideoEncodeH265Profile, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            StdVideoH265ProfileIdc                          stdProfileIdc;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE
#define C_ENG_MAP_START STRUCT ( VideoProfile, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            Type ( VideoCodecOperationFlag )                videoCodecOperation;
            Type ( VideoChromaSubsamplingFlags )            chromaSubsampling;
            Type ( VideoComponentBitDepthFlags )            lumaBitDepth;
            Type ( VideoComponentBitDepthFlags )            chromaBitDepth;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE
#define C_ENG_MAP_START STRUCT ( VideoProfiles, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            cds :: uint32                                   profileCount;
            Type ( VideoProfile )                   const * pProfiles;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START STRUCT ( BufferViewCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                  structureType;
            Type ( GenericStructure )       const * pNext;
            Type ( BufferViewCreateFlags )          flags;
            Type ( BufferHandle )                   buffer;
            Type ( Format )                         format;
            Type ( DeviceSize )                     offset;
            Type ( DeviceSize )                     range;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START STRUCT ( ImageCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                  structureType;
            Type ( GenericStructure )       const * pNext;
            Type ( ImageCreateFlags )               flags;
            Type ( ImageType )                      imageType;
            Type ( Format )                         format;
            Type ( Extent3D )                       extent;
            cds :: uint32                           mipLevels;
            cds :: uint32                           arrayLayers;
            Type ( SampleCountFlag )                samples;
            Type ( ImageTiling )                    tiling;
            Type ( ImageUsageFlags )                usage;
            Type ( SharingMode )                    sharingMode;
            cds :: uint32                           queueFamilyIndexCount;
            cds :: uint32                   const * pQueueFamilyIndices;
            Type ( ImageLayout )                    initialLayout;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_BUFFER_COLLECTION_AVAILABLE
#define C_ENG_MAP_START STRUCT ( BufferCollectionImageCreateInfoFuchsia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                  structureType;
            Type ( GenericStructure )       const * pNext;
            Type ( BufferCollectionHandleFuchsia )  collection;
            cds :: uint32                           index;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_AVAILABLE
#define C_ENG_MAP_START STRUCT ( DedicatedAllocationImageCreateInfoNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                  structureType;
            Type ( GenericStructure )       const * pNext;
            Type ( Bool )                           dedicatedAllocation;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_AVAILABLE
#define C_ENG_MAP_START STRUCT ( ExternalFormatAndroid, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                  structureType;
            Type ( GenericStructure )       const * pNext;
            cds :: uint64                           externalFormat;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define C_ENG_MAP_START STRUCT ( ExternalMemoryImageCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                  structureType;
            Type ( GenericStructure )       const * pNext;
            Type ( ExternalMemoryHandleTypeFlags )  handleTypes;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_AVAILABLE
#define C_ENG_MAP_START STRUCT ( ExternalMemoryImageCreateInfoNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            Type ( ExternalMemoryHandleTypeFlagsNVidia )    handleTypes;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START STRUCT ( SubresourceLayout, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( DeviceSize ) offset;
            Type ( DeviceSize ) size;
            Type ( DeviceSize ) rowPitch;
            Type ( DeviceSize ) arrayPitch;
            Type ( DeviceSize ) depthPitch;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_DRM_FORMAT_MODIFIER_AVAILABLE
#define C_ENG_MAP_START STRUCT ( ImageDrmFormatModifierExplicitCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            cds :: uint64                                   drmFormatModifier;
            cds :: uint32                                   drmFormatModifierPlaneCount;
            Type ( SubresourceLayout )              const * pPlaneLayouts;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_DRM_FORMAT_MODIFIER_AVAILABLE
#define C_ENG_MAP_START STRUCT ( ImageDrmFormatModifierListCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            cds :: uint32                                   drmFormatModifierCount;
            cds :: uint64                           const * pDrmFormatModifiers;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
#define C_ENG_MAP_START STRUCT ( ImageStencilUsageCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            Type ( ImageUsageFlags )                        stencilUsage;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE
#define C_ENG_MAP_START STRUCT ( ImageSwapChainCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            Type ( SwapChainHandle )                        swapchain;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START STRUCT ( ImageSubresource, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( ImageAspectFlags )   aspectMask;
            cds :: uint32               mipLevel;
            cds :: uint32               arrayLayer;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_DRM_FORMAT_MODIFIER_AVAILABLE
#define C_ENG_MAP_START STRUCT ( ImageDrmFormatModifierProperties, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )         * pNext;
            cds :: uint64                       drmFormatModifier;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_ASTC_DECODE_MODE_AVAILABLE
#define C_ENG_MAP_START STRUCT ( ImageViewASTCDecodeMode, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )         * pNext;
            Type ( Format )                     decodeMode;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_VIEW_MIN_LOD_AVAILABLE
#define C_ENG_MAP_START STRUCT ( ImageViewMinLodCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )         * pNext;
            float                               minLod;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
#define C_ENG_MAP_START STRUCT ( GeometryAABBNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( BufferHandle )               aabbData;
            cds :: uint32                       numAABBs;
            cds :: uint32                       stride;
            Type ( DeviceSize )                 offset;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
#define C_ENG_MAP_START STRUCT ( GeometryTrianglesNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( BufferHandle )               vertexData;
            Type ( DeviceSize )                 vertexOffset;
            cds :: uint32                       vertexCount;
            Type ( DeviceSize )                 vertexStride;
            Type ( Format )                     vertexFormat;
            Type ( BufferHandle )               indexData;
            Type ( DeviceSize )                 indexOffset;
            cds :: uint32                       indexCount;
            Type ( IndexType )                  indexType;
            Type ( BufferHandle )               transformData;
            Type ( DeviceSize )                 transformOffset;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
#define C_ENG_MAP_START STRUCT ( GeometryDataNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( GeometryTrianglesNVidia )    triangles;
            Type ( GeometryAABBNVidia )         aabbs;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
#define C_ENG_MAP_START STRUCT ( GeometryNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                              structureType;
            Type ( GenericStructure )                   const * pNext;
            Type ( GeometryTypeNVidia )                         geometryType;
            Type ( GeometryDataNVidia )                         geometry;
            Type ( GeometryFlagsNVidia )                        flags;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
#define C_ENG_MAP_START STRUCT ( AccelerationStructureInfoNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                              structureType;
            Type ( GenericStructure )                   const * pNext;
            Type ( AccelerationStructureTypeNVidia )            type;
            Type ( BuildAccelerationStructureFlagsNVidia )      flags;
            cds :: uint32                                       instanceCount;
            cds :: uint32                                       geometryCount;
            Type ( GeometryNVidia )                     const * pGeometries;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
#define C_ENG_MAP_START STRUCT ( AccelerationStructureCreateInfoNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            Type ( DeviceSize )                         compactedSize;
            Type ( AccelerationStructureInfoNVidia )    info;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
#define C_ENG_MAP_START STRUCT ( AccelerationStructureCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            Type ( AccelerationStructureCreateFlags )   flags;
            Type ( BufferHandle )                       buffer;
            Type ( DeviceSize )                         offset;
            Type ( DeviceSize )                         size;
            Type ( AccelerationStructureType )          type;
            Type ( DeviceAddress )                      deviceAddress;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE
#define C_ENG_MAP_START STRUCT ( AccelerationStructureMotionInfoNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                                  structureType;
            Type ( GenericStructure )                       const * pNext;
            cds :: uint32                                           maxInstances;
            Type ( AccelerationStructureMotionInfoFlagsNVidia )     flags;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
#define C_ENG_MAP_START UNION ( DeviceOrHostAddress, NO_PARENT )
#include <ObjectMapping.hpp>

        Union {
            Type ( DeviceAddress )  deviceAddress;
            void                  * hostAddress;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
#define C_ENG_MAP_START UNION ( DeviceOrHostAddressConst, NO_PARENT )
#include <ObjectMapping.hpp>

        Union {
            Type ( DeviceAddress )  deviceAddress;
            void            const * hostAddress;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
#define C_ENG_MAP_START STRUCT ( AccelerationStructureGeometryTrianglesData, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                                  structureType;
            Type ( GenericStructure )                       const * pNext;
            Type ( Format )                                         vertexFormat;
            Type ( DeviceOrHostAddressConst )                       vertexData;
            Type ( DeviceSize )                                     vertexStride;
            cds :: uint32                                           maxVertex;
            Type ( IndexType )                                      indexType;
            Type ( DeviceOrHostAddressConst )                       indexData;
            Type ( DeviceOrHostAddressConst )                       transformData;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
#define C_ENG_MAP_START STRUCT ( AccelerationStructureGeometryAabbsData, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                                  structureType;
            Type ( GenericStructure )                       const * pNext;
            Type ( DeviceOrHostAddressConst )                       data;
            Type ( DeviceSize )                                     stride;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
#define C_ENG_MAP_START STRUCT ( AccelerationStructureGeometryInstancesData, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                                  structureType;
            Type ( GenericStructure )                       const * pNext;
            Type ( Bool )                                           arrayOfPointers;
            Type ( DeviceOrHostAddressConst )                       data;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
#define C_ENG_MAP_START UNION ( AccelerationStructureGeometryData, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( AccelerationStructureGeometryTrianglesData ) triangles;
            Type ( AccelerationStructureGeometryAabbsData )     aabbs;
            Type ( AccelerationStructureGeometryInstancesData ) instances;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
#define C_ENG_MAP_START STRUCT ( AccelerationStructureGeometry, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                                  structureType;
            Type ( GenericStructure )                       const * pNext;
            Type ( GeometryType )                                   geometryType;
            Type ( AccelerationStructureGeometryData )              geometry;
            Type ( GeometryFlags )                                  flags;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
#define C_ENG_MAP_START STRUCT ( AccelerationStructureBuildGeometryInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                                  structureType;
            Type ( GenericStructure )                       const * pNext;
            Type ( AccelerationStructureType )                      type;
            Type ( BuildAccelerationStructureFlags )                flags;
            Type ( BuildAccelerationStructureMode )                 mode;
            Type ( AccelerationStructureHandle )                    source;
            Type ( AccelerationStructureHandle )                    destination;
            cds :: uint32                                           geometryCount;
            Type ( AccelerationStructureGeometry )          const * pGeometries;
            Type ( AccelerationStructureGeometry )  const * const * ppGeometries;
            Type ( DeviceOrHostAddress )                            scratchData;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
#define C_ENG_MAP_START STRUCT ( AccelerationStructureBuildSizesInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                                  structureType;
            Type ( GenericStructure )                       const * pNext;
            Type ( DeviceSize )                                     accelerationStructureSize;
            Type ( DeviceSize )                                     updateScratchSize;
            Type ( DeviceSize )                                     buildScratchSize;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE
#define C_ENG_MAP_START STRUCT ( AccelerationStructureGeometryMotionTrianglesDataNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                                  structureType;
            Type ( GenericStructure )                       const * pNext;
            Type ( DeviceOrHostAddressConst )                       vertexData;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
#define C_ENG_MAP_START STRUCT ( AccelerationStructureMemoryRequirementsInfoNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                                              structureType;
            Type ( GenericStructure )                                   const * pNext;
            Type ( AccelerationStructureMemoryRequirementsTypeNVidia )          type;
            Type ( AccelerationStructureHandleNVidia )                          accelerationStructure;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START STRUCT ( MemoryRequirements, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( DeviceSize ) size;
            Type ( DeviceSize ) alignment;
            cds :: uint32       memoryTypeBits;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define C_ENG_MAP_START STRUCT ( MemoryRequirements2, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )      structureType;
            Type ( GenericStructure ) * pNext;
            Type ( MemoryRequirements ) memoryRequirements;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define C_ENG_MAP_START STRUCT ( MemoryDedicatedRequirements, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )      structureType;
            Type ( GenericStructure ) * pNext;
            Type ( Bool )               prefersDedicatedAllocation;
            Type ( Bool )               requiresDedicatedAllocation;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
#define C_ENG_MAP_START STRUCT ( BindAccelerationStructureMemoryInfoNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                              structureType;
            Type ( GenericStructure )                   const * pNext;
            Type ( AccelerationStructureHandleNVidia )          accelerationStructure;
            Type ( DeviceMemoryHandle )                         memory;
            Type ( DeviceSize )                                 memoryOffset;
            cds :: uint32                                       deviceIndexCount;
            cds :: uint32                               const * pDeviceIndices;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
#define C_ENG_MAP_START STRUCT ( AccelerationStructureDeviceAddressInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                              structureType;
            Type ( GenericStructure )                   const * pNext;
            Type ( AccelerationStructureHandle )                accelerationStructure;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START STRUCT ( SamplerCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( SamplerCreateFlags )         flags;
            Type ( Filter )                     magFilter;
            Type ( Filter )                     minFilter;
            Type ( SamplerMipmapMode )          mipmapMode;
            Type ( SamplerAddressMode )         addressModeU;
            Type ( SamplerAddressMode )         addressModeV;
            Type ( SamplerAddressMode )         addressModeW;
            float                               mipLodBias;
            Type ( Bool )                       anisotropyEnable;
            float                               maxAnisotropy;
            Type ( Bool )                       compareEnable;
            Type ( CompareOperation )           compareOperation;
            float                               minLod;
            float                               maxLod;
            Type ( BorderColor )                borderColor;
            Type ( Bool )                       unnormalizedCoordinates;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_BORDER_COLOR_SWIZZLE_AVAILABLE
#define C_ENG_MAP_START STRUCT ( SamplerBorderColorComponentMappingCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( ComponentMapping )           components;
            Type ( Bool )                       srgb;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE
#define C_ENG_MAP_START STRUCT ( SamplerCustomBorderColorCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( ClearColorValue )            customBorderColor;
            Type ( Format )                     format;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
#define C_ENG_MAP_START STRUCT ( SamplerReductionModeCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( SamplerReductionMode )       reductionMode;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define C_ENG_MAP_START STRUCT ( SamplerYCBCRConversionCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            Type ( Format )                             format;
            Type ( SamplerYCBCRModelConversion )        ycbcrModel;
            Type ( SamplerYCBCRRange )                  ycbcrRange;
            Type ( ComponentMapping )                   components;
            Type ( ChromaLocation )                     xChromaOffset;
            Type ( ChromaLocation )                     yChromaOffset;
            Type ( Filter )                             chromaFilter;
            Type ( Bool )                               forceExplicitReconstruction;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START STRUCT ( DescriptorSetLayoutBinding, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            cds :: uint32                       binding;
            Type ( DescriptorType )             descriptorType;
            cds :: uint32                       descriptorCount;
            Type ( ShaderStageFlags )           stageFlags;
            Type ( SamplerHandle )      const * pImmutableSamplers;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START STRUCT ( DescriptorSetLayoutCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            Type ( DescriptorSetLayoutCreateFlags )     flags;
            cds :: uint32                               bindingCount;
            Type ( DescriptorSetLayoutBinding ) const * pBindings;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
#define C_ENG_MAP_START STRUCT ( DescriptorSetLayoutBindingFlagsCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            cds :: uint32                               bindingCount;
            Type ( DescriptorBindingFlags )     const * pBindingFlags;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE
#define C_ENG_MAP_START STRUCT ( MutableDescriptorTypeListValve, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            cds :: uint32                       descriptorTypeCount;
            Type ( DescriptorType )     const * pDescriptorTypes;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define C_ENG_MAP_START STRUCT ( DescriptorSetLayoutSupport, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            Type ( Bool )                               supported;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
#define C_ENG_MAP_START STRUCT ( DescriptorSetVariableDescriptorCountLayoutSupport, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            cds :: uint32                               maxVariableDescriptorCount;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE
#define C_ENG_MAP_START STRUCT ( MutableDescriptorTypeCreateInfoValve, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            cds :: uint32                                   mutableDescriptorTypeListCount;
            Type ( MutableDescriptorTypeListValve ) const * pMutableDescriptorTypeLists;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START STRUCT ( PushConstantRange, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( ShaderStageFlags )   stageFlags;
            cds :: uint32               offset;
            cds :: uint32               size;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START STRUCT ( PipelineLayoutCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            Type ( PipelineLayoutCreateFlags )              flags;
            cds :: uint32                                   setLayoutCount;
            Type ( DescriptorSetLayoutHandle )      const * pSetLayouts;
            cds :: uint32                                   pushConstantRangeCount;
            Type ( PushConstantRange )              const * pPushConstantRanges;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START STRUCT ( DescriptorPoolSize, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( DescriptorType ) type;
            cds :: uint32           descriptorCount;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START STRUCT ( DescriptorPoolCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            Type ( DescriptorPoolCreateFlags )              flags;
            cds :: uint32                                   maxSets;
            cds :: uint32                                   poolSizeCount;
            Type ( DescriptorPoolSize )             const * pPoolSizes;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE
#define C_ENG_MAP_START STRUCT ( DescriptorPoolInlineUniformBlockCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            cds :: uint32                                   maxInlineUniformBlockBindings;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START STRUCT ( DescriptorSetAllocateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            Type ( DescriptorPoolHandle )                   descriptorPool;
            cds :: uint32                                   descriptorSetCount;
            Type ( DescriptorSetLayoutHandle )      const * pSetLayouts;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
#define C_ENG_MAP_START STRUCT ( DescriptorSetVariableDescriptorCountAllocateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            cds :: uint32                                   descriptorSetCount;
            cds :: uint32                           const * pDescriptorCounts;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START STRUCT ( DescriptorBufferInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( BufferHandle )   buffer;
            Type ( DeviceSize )     offset;
            Type ( DeviceSize )     range;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START STRUCT ( DescriptorImageInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( SamplerHandle )      sampler;
            Type ( ImageViewHandle )    imageView;
            Type ( ImageLayout )        imageLayout;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START STRUCT ( WriteDescriptorSet, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            Type ( DescriptorSetHandle )                    destinationSet;
            cds :: uint32                                   destinationBinding;
            cds :: uint32                                   destinationArrayElement;
            cds :: uint32                                   descriptorCount;
            Type ( DescriptorType )                         descriptorType;
            Type ( DescriptorImageInfo )            const * pImageInfo;
            Type ( DescriptorBufferInfo )           const * pBufferInfo;
            Type ( BufferViewHandle )               const * pTexelBufferView;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
#define C_ENG_MAP_START STRUCT ( WriteDescriptorSetAccelerationStructure, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                          structureType;
            Type ( GenericStructure )               const * pNext;
            cds :: uint32                                   accelerationStructureCount;
            Type ( AccelerationStructureHandle )    const * pAccelerationStructures;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
#define C_ENG_MAP_START STRUCT ( WriteDescriptorSetAccelerationStructureNVidia, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                              structureType;
            Type ( GenericStructure )                   const * pNext;
            cds :: uint32                                       accelerationStructureCount;
            Type ( AccelerationStructureHandleNVidia )  const * pAccelerationStructures;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE
#define C_ENG_MAP_START STRUCT ( WriteDescriptorSetInlineUniformBlock, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                              structureType;
            Type ( GenericStructure )                   const * pNext;
            cds :: uint32                                       dataSize;
            void                                        const * pData;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START STRUCT ( CopyDescriptorSet, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( DescriptorSetHandle )        sourceSet;
            cds :: uint32                       sourceBinding;
            cds :: uint32                       sourceArrayElement;
            Type ( DescriptorSetHandle )        destinationSet;
            cds :: uint32                       destinationBinding;
            cds :: uint32                       destinationArrayElement;
            cds :: uint32                       descriptorCount;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define C_ENG_MAP_START STRUCT ( DescriptorUpdateTemplateEntry, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            cds :: uint32           destinationBinding;
            cds :: uint32           destinationArrayElement;
            cds :: uint32           descriptorCount;
            Type ( DescriptorType ) descriptorType;
            cds :: uint64           offset;
            cds :: uint64           stride;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define C_ENG_MAP_START STRUCT ( DescriptorUpdateTemplateCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                              structureType;
            Type ( GenericStructure )                   const * pNext;
            Type ( DescriptorUpdateTemplateCreateFlags )        flags;
            cds :: uint32                                       descriptorUpdateEntryCount;
            Type ( DescriptorUpdateTemplateEntry )      const * pDescriptorUpdateEntries;
            Type ( DescriptorUpdateTemplateType )               templateType;
            Type ( DescriptorSetLayoutHandle )                  descriptorSetLayout;
            Type ( PipelineBindPoint )                          pipelineBindPoint;
            Type ( PipelineLayoutHandle )                       pipelineLayout;
            cds :: uint32                                       set;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
#define C_ENG_MAP_START STRUCT ( BufferDeviceAddressInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                              structureType;
            Type ( GenericStructure )                   const * pNext;
            Type ( BufferHandle )                               buffer;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START STRUCT ( QueryPoolCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                              structureType;
            Type ( GenericStructure )                   const * pNext;
            Type ( QueryPoolCreateFlags )                       flags;
            Type ( QueryType )                                  queryType;
            cds :: uint32                                       queryCount;
            Type ( QueryPipelineStatisticFlags )                pipelineStatistics;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
#define C_ENG_MAP_START STRUCT ( QueryPoolPerformanceCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                              structureType;
            Type ( GenericStructure )                   const * pNext;
            cds :: uint32                                       queueFamilyIndex;
            cds :: uint32                                       counterIndexCount;
            cds :: uint32                               const * pCounterIndices;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
#define C_ENG_MAP_START STRUCT ( QueryPoolPerformanceCreateInfoIntel, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                              structureType;
            Type ( GenericStructure )                   const * pNext;
            Type ( QueryPoolSamplingModeIntel )                 performanceCountersSampling;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
#define C_ENG_MAP_START STRUCT ( AcquireProfilingLockInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                              structureType;
            Type ( GenericStructure )                   const * pNext;
            Type ( AcquireProfilingLockFlags )                  flags;
            cds :: uint64                                       timeout;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
#define C_ENG_MAP_START STRUCT ( InitializePerformanceAPIInfoIntel, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                              structureType;
            Type ( GenericStructure )                   const * pNext;
            void                                              * pUserData;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
#define C_ENG_MAP_START UNION ( PerformanceValueDataIntel, NO_PARENT )
#include <ObjectMapping.hpp>

        Union {
            cds :: uint32           value32;
            cds :: uint64           value64;
            float                   valueFloat;
            Type ( Bool )           valueBool;
            cds :: StringLiteral    valueString;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
#define C_ENG_MAP_START STRUCT ( PerformanceValueIntel, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( PerformanceValueTypeIntel )  type;
            Type ( PerformanceValueDataIntel )  data;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
#define C_ENG_MAP_START STRUCT ( PerformanceMarkerInfoIntel, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            cds :: uint64                       marker;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
#define C_ENG_MAP_START STRUCT ( PerformanceStreamMarkerInfoIntel, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            cds :: uint32                       marker;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
#define C_ENG_MAP_START STRUCT ( PerformanceOverrideInfoIntel, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            Type ( PerformanceOverrideTypeIntel )       type;
            Type ( Bool )                               enable;
            cds :: uint64                               parameter;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
#define C_ENG_MAP_START STRUCT ( PerformanceConfigurationAcquireInfoIntel, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            Type ( PerformanceConfigurationTypeIntel )  type;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE
#define C_ENG_MAP_START STRUCT ( QueueFamilyQueryResultStatusProperties2, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            Type ( Bool )                               supported;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START STRUCT ( ClearAttachment, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( ImageAspectFlags )   aspectMask;
            cds :: uint32               colorAttachment;
            Type ( ClearValue )         clearValue;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START STRUCT ( ClearRect, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( Rect )   rect;
            cds :: uint32   baseArrayLayer;
            cds :: uint32   layerCount;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START STRUCT ( BufferCopy, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( DeviceSize ) sourceOffset;
            Type ( DeviceSize ) destinationOffset;
            Type ( DeviceSize ) size;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
#define C_ENG_MAP_START STRUCT ( BufferCopy2, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            Type ( DeviceSize )                         sourceOffset;
            Type ( DeviceSize )                         destinationOffset;
            Type ( DeviceSize )                         size;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
#define C_ENG_MAP_START STRUCT ( CopyBufferInfo2, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            Type ( BufferHandle )                       sourceBuffer;
            Type ( BufferHandle )                       destinationBuffer;
            cds :: uint32                               regionCount;
            Type ( BufferCopy2 )                const * pRegions;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START STRUCT ( ImageSubresourceLayers, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( ImageAspectFlags )   aspectMask;
            cds :: uint32               mipLevel;
            cds :: uint32               baseArrayLayer;
            cds :: uint32               layerCount;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START STRUCT ( ImageCopy, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( ImageSubresourceLayers ) sourceSubresource;
            Type ( Offset3D )               sourceOffset;
            Type ( ImageSubresourceLayers ) destinationSubresource;
            Type ( Offset3D )               destinationOffset;
            Type ( Extent3D )               extent;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
#define C_ENG_MAP_START STRUCT ( ImageCopy2, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            Type ( ImageSubresourceLayers )             sourceSubresource;
            Type ( Offset3D )                           sourceOffset;
            Type ( ImageSubresourceLayers )             destinationSubresource;
            Type ( Offset3D )                           destinationOffset;
            Type ( Extent3D )                           extent;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
#define C_ENG_MAP_START STRUCT ( CopyImageInfo2, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )                      structureType;
            Type ( GenericStructure )           const * pNext;
            Type ( ImageHandle )                        sourceImage;
            Type ( ImageLayout )                        sourceImageLayout;
            Type ( ImageHandle )                        destinationImage;
            Type ( ImageLayout )                        destinationImageLayout;
            cds :: uint32                               regionCount;
            Type ( ImageCopy2 )                 const * pRegions;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START STRUCT ( BufferImageCopy, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( DeviceSize )             bufferOffset;
            cds :: uint32                   bufferRowLength;
            cds :: uint32                   bufferImageHeight;
            Type ( ImageSubresourceLayers ) imageSubresource;
            Type ( Offset3D )               imageOffset;
            Type ( Extent3D )               imageExtent;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
#define C_ENG_MAP_START STRUCT ( BufferImageCopy2, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( DeviceSize )                 bufferOffset;
            cds :: uint32                       bufferRowLength;
            cds :: uint32                       bufferImageHeight;
            Type ( ImageSubresourceLayers )     imageSubresource;
            Type ( Offset3D )                   imageOffset;
            Type ( Extent3D )                   imageExtent;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
#define C_ENG_MAP_START STRUCT ( CopyBufferToImageInfo2, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( BufferHandle )               sourceBuffer;
            Type ( ImageHandle )                destinationImage;
            Type ( ImageLayout )                destinationImageLayout;
            cds :: uint32                       regionCount;
            Type ( BufferImageCopy2 )   const * pRegions;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
#define C_ENG_MAP_START STRUCT ( CopyImageToBufferInfo2, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( ImageHandle )                sourceImage;
            Type ( ImageLayout )                sourceImageLayout;
            Type ( BufferHandle )               destinationBuffer;
            cds :: uint32                       regionCount;
            Type ( BufferImageCopy2 )   const * pRegions;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_ROTATED_COPY_COMMANDS_AVAILABLE
#define C_ENG_MAP_START STRUCT ( CopyCommandTransformInfoQualcomm, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( SurfaceTransformFlag )       transform;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START STRUCT ( ImageBlit, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( ImageSubresourceLayers ) sourceSubresource;
            Type ( Offset3D )               sourceOffsets [2];
            Type ( ImageSubresourceLayers ) destinationSubresource;
            Type ( Offset3D )               destinationOffsets [2];
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
#define C_ENG_MAP_START STRUCT ( ImageBlit2, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( ImageSubresourceLayers )     sourceSubresource;
            Type ( Offset3D )                   sourceOffsets [2];
            Type ( ImageSubresourceLayers )     destinationSubresource;
            Type ( Offset3D )                   destinationOffsets [2];
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
#define C_ENG_MAP_START STRUCT ( BlitImageInfo2, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( StructureType )              structureType;
            Type ( GenericStructure )   const * pNext;
            Type ( ImageHandle )                sourceImage;
            Type ( ImageLayout )                sourceImageLayout;
            Type ( ImageHandle )                destinationImage;
            Type ( ImageLayout )                destinationImageLayout;
            cds :: uint32                       regionCount;
            Type ( ImageBlit2 )         const * pRegions;
            Type ( Filter )                     filter;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START STRUCT ( ImageResolve, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            Type ( ImageSubresourceLayers ) sourceSubresource;
            Type ( Offset3D )               sourceOffset;
            Type ( ImageSubresourceLayers ) destinationSubresource;
            Type ( Offset3D )               destinationOffset;
            Type ( Extent3D )               extent;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#define C_ENG_MAP_START     HEADER
#include <ObjectMapping.hpp>


#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        NoDiscard MaybeUnused auto toString ( Type ( Offset2D ) const & ) noexcept -> cds :: String;
        NoDiscard MaybeUnused auto toString ( Type ( Offset3D ) const & ) noexcept -> cds :: String;
        NoDiscard MaybeUnused auto toString ( Type ( Extent2D ) const & ) noexcept -> cds :: String;
        NoDiscard MaybeUnused auto toString ( Type ( Extent3D ) const & ) noexcept -> cds :: String;
        NoDiscard MaybeUnused auto toString ( Type ( Rect ) const & ) noexcept -> cds :: String;
        NoDiscard MaybeUnused auto toString ( Type ( DeviceSize ) ) noexcept -> cds :: String;
#endif
#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAMEBUFFER_MIXED_SAMPLES_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_AMD_MIXED_ATTACHMENT_SAMPLES_AVAILABLE
        NoDiscard MaybeUnused auto toString ( hidden :: __AttachmentSampleCountInfo const & ) noexcept -> cds :: String;
#endif

        NoDiscard auto compare ( Type ( Version ) const &, Type ( Version ) const & ) noexcept -> __C_ENG_TYPE ( CompareResult );

        NoDiscard auto uInt32ToInstanceVersion ( cds :: uint32 ) noexcept -> Type ( Version );
        NoDiscard auto instanceVersionToUInt32 ( Type ( Version ) const & ) noexcept -> cds :: uint32;
        NoDiscard auto versionReadableFormat ( Type ( Version ) const & ) noexcept -> cds :: String;

        namespace versionConstants {

            constexpr static Type ( Version ) const nullVersion             = { .variant = 0U, .major = 0U, .minor = 0U, .patch = 0U };
            constexpr static Type ( Version ) const version10   MaybeUnused = { .variant = 0U, .major = 1U, .minor = 0U, .patch = 0U };
            constexpr static Type ( Version ) const version11               = { .variant = 0U, .major = 1U, .minor = 1U, .patch = 0U };
            constexpr static Type ( Version ) const version12   MaybeUnused = { .variant = 0U, .major = 1U, .minor = 2U, .patch = 0U };

        }

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

    }
}


#endif //__C_ENG_VULKAN_CORE_HPP__

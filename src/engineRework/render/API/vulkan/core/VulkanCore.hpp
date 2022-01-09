//
// Created by loghin on 26.12.2021.
//

#ifndef __C_ENG_VULKANCORE_HPP
#define __C_ENG_VULKANCORE_HPP

#include <Preprocess.hpp>
#include <CDS/Types>
#include <CDS/Limits>
#include <CDS/Exception>

#include <VulkanAPIDetails.hpp>

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

#if __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE

            Field ( PipelineCompileRequired,                   VkResult :: VK_PIPELINE_COMPILE_REQUIRED_EXT ),

#endif

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

            Field ( FramebufferCreateInfo,                                                 VkStructureType :: VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO ),
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

            Field ( PipelineTesselationDomainOriginStateCreateInfo,                        VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_DOMAIN_ORIGIN_STATE_CREATE_INFO ),

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
            Field ( PhysicalDeviceExternalSempahoreInfo,                                   VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_SEMAPHORE_INFO ),
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
            Field ( PhysicalDeviceImagelessFramebufferFeatures,                            VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGELESS_FRAMEBUFFER_FEATURES ),

            Field ( FramebufferAttachmentsCreateInfo,                                      VkStructureType :: VK_STRUCTURE_TYPE_FRAMEBUFFER_ATTACHMENTS_CREATE_INFO ),
            Field ( FramebufferAttachmentImageInfo,                                        VkStructureType :: VK_STRUCTURE_TYPE_FRAMEBUFFER_ATTACHMENT_IMAGE_INFO ),
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

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE

            Field ( SwapchainCreateInfo,                                                   VkStructureType :: VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR ),
            Field ( PresentInfo,                                                           VkStructureType :: VK_STRUCTURE_TYPE_PRESENT_INFO_KHR ),

#endif

#if ( __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE ) || ( __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DEVICE_GROUP_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE )

            Field ( DeviceGroupPresentCapabilities,                                        VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_GROUP_PRESENT_CAPABILITIES_KHR ),

            Field ( ImageSwapchainCreateInfo,                                              VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_SWAPCHAIN_CREATE_INFO_KHR ),

            Field ( BindImageMemorySwapchainInfo,                                          VkStructureType :: VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_SWAPCHAIN_INFO_KHR ),
            Field ( AcquireNextImageInfo,                                                  VkStructureType :: VK_STRUCTURE_TYPE_ACQUIRE_NEXT_IMAGE_INFO_KHR ),

            Field ( DeviceGroupPresentInfo,                                                VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_GROUP_PRESENT_INFO_KHR ),
            Field ( DeviceGroupSwapchainCreateInfo,                                        VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_GROUP_SWAPCHAIN_CREATE_INFO_KHR ),

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
            Field ( VideoPictureResource,                                                  VkStructureType :: VK_STRUCTURE_VIDEO_PICTURE_RESOURCE_KHR ),
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
            Field ( VideoEncodeH264SessionCreateInfo,                                      VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_SESSION_CREATE_INFO_EXT ),
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
            Field ( VideoEncodeH265SessionCreateInfo,                                      VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_SESSION_CREATE_INFO_EXT ),
            Field ( VideoEncodeH265SessionParametersCreateInfo,                            VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_SESSION_PARAMETERS_CREATE_INFO_EXT ),
            Field ( VideoEncodeH265SessionParametersAddInfo,                               VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_SESSION_PARAMETERS_ADD_INFO_EXT ),
            Field ( VideoEncodeH265VCLFrameInfo,                                           VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_VCL_FRAME_INFO_EXT ),
            Field ( VideoEncodeH265DPBSlotInfo,                                            VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_DPB_SLOT_INFO_EXT ),
            Field ( VideoEncodeH265NALUSlice,                                              VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_NALU_SLICE_EXT ),
            Field ( VideoEncodeH265EmitPictureParameters,                                  VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_EMIT_PICTURE_PARAMETERS_EXT ),
            Field ( VideoEncodeH265Profile,                                                VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_PROFILE_EXT ),
            Field ( VideoEncodeH265ReferenceLists,                                         VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_REFERENCE_LISTS_EXT ),
            Field ( VideoEncodeH265RateControlInfo,                                        VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_RATE_CONTROL_INFO_EXT ),
            Field ( VideoEncodeH265RateControlLayerInfo,                                   VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_RATE_CONTROL_LAYER_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_VIDEO_DECODE_H264_AVAILABLE

            Field ( VideoDecodeH264Capabilities,                                           VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_CAPABILITIES_EXT ),
            Field ( VideoDecodeH264SessionCreateInfo,                                      VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_SESSION_CREATE_INFO_EXT ),
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

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE

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

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE

            Field ( MutiviewPerViewAttributesInfoNVidiaExperimental,                       VkStructureType :: VK_STRUCTURE_TYPE_MULTIVIEW_PER_VIEW_ATTRIBUTES_INFO_NVX ),
            Field ( PhysicalDeviceMultiviewPerViewAttributesPropertiesNVidiaExperimental,  VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_PER_VIEW_ATTRIBUTES_PROPERTIES_NVX ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_GAMES_PLATFORM_STREAM_DESCRIPTOR_SURFACE_AVAILABLE

            Field ( StreamDescriptorSurfaceCreateInfoGoogle,                               VkStructureType :: VK_STRUCTURE_TYPE_STREAM_DESCRIPTOR_SURFACE_CREATE_INFO_GGP ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CORNER_SAMPLED_IMAGE_AVAILABLE

            Field ( PhysicalDeviceCornerSampledImageFeatures,                              VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CORNER_SAMPLED_IMAGE_FEATURES_NV ),

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

#if __C_ENG_VULKAN_API_EXTENSION_TEXTURE_COMPRESSION_ASTC_HDR_AVAILABLE

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

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE

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
            Field ( VideoDecodeH265SessionCreateInfo,                                      VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_SESSION_CREATE_INFO_EXT ),
            Field ( VideoDecodeH265SessionParametersCreateInfo,                            VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_SESSION_PARAMETERS_CREATE_INFO_EXT ),
            Field ( VideoDecodeH265SessionParametersAddInfo,                               VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_SESSION_PARAMETERS_ADD_INFO_EXT ),
            Field ( VideoDecodeH265SessionProfile,                                         VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_PROFILE_EXT ),
            Field ( VideoDecodeH265SessionPictureInfo,                                     VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_PICTURE_INFO_EXT ),
            Field ( VideoDecodeH265SessionDPBSlotInfo,                                     VkStructureType :: VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_DPB_SLOT_INFO_EXT ),

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

#if __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_FEEDBACK_AVAILABLE

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

            Field ( PhysicalDeviceShaderIntegerFunctionFeaturesIntel,                      VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_INTEGER_FUNCTIONS_2_FEATURES_INTEL ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE

            Field ( QueryPoolPerformanceQueryCreateInfoIntel,                              VkStructureType :: VK_STRUCTURE_TYPE_QUERY_POOL_PERFORMANCE_QUERY_CREATE_INFO_INTEL ),
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

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_TERMINATE_INVOCATION_AVAILABLE

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

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE

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

            Field ( PhysicalDeviceBufferDeviceAddressFeaturesExt,                          VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BUFFER_DEVICE_ADDRESS_FEATURES_EXT ),
            Field ( BufferDeviceAddressCreateInfoExt,                                      VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TOOLING_INFO_AVAILABLE

            Field ( PhysicalDeviceToolProperties,                                          VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TOOL_PROPERTIES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_FEATURES_AVAILABLE

            Field ( ValidationFeatures,                                                    VkStructureType :: VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT ),

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
            Field ( FramebufferMixedSamplesCombinationNVidia,                              VkStructureType :: VK_STRUCTURE_TYPE_FRAMEBUFFER_MIXED_SAMPLES_COMBINATION_NV ),

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

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_DEMOTE_TO_HELPER_INVOCATION_AVAILABLE

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

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE

            Field ( PhysicalDeviceShaderIntegerDotProductFeatures,                         VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_INTEGER_DOT_PRODUCT_FEATURES_KHR ),
            Field ( PhysicalDeviceShaderIntegerDotProductProperties,                       VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_INTEGER_DOT_PRODUCT_PROPERTIES_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE

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

#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE

            Field ( PhysicalDevicePrivateDataFeatures,                                     VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRIVATE_DATA_FEATURES_EXT ),
            Field ( DevicePrivateDataCreateInfo,                                           VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_PRIVATE_DATA_CREATE_INFO_EXT ),
            Field ( PrivateDataSlotCreateInfo,                                             VkStructureType :: VK_STRUCTURE_TYPE_PRIVATE_DATA_SLOT_CREATE_INFO_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE

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

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE

            Field ( MemoryBarrier2,                                                        VkStructureType :: VK_STRUCTURE_TYPE_MEMORY_BARRIER_2_KHR ),
            Field ( BufferMemoryBarrier2,                                                  VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER_2_KHR ),
            Field ( ImageMemoryBarrier2,                                                   VkStructureType :: VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2_KHR ),
            Field ( DependencryInfo,                                                       VkStructureType :: VK_STRUCTURE_TYPE_DEPENDENCY_INFO_KHR ),
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

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ZERO_INITIALIZE_WORKGROUP_MEMORY_AVAILABLE

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

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_ROBUSTNESS_AVAILABLE

            Field ( PhysicalDeviceImageRobustnessFeatures,                                 VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_ROBUSTNESS_FEATURES_EXT ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_AVAILABLE

            Field ( PhysicalDeviceWorkgroupMemoryExplicitLayoutFeatures,                   VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_FEATURES_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE

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

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FORMAT_FEATURE_FLAGS_AVAILABLE

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

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE

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

#define C_ENG_MAP_START     ENUM ( PointClippingBehavior, TYPE ( cds :: uint8 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( AllClipPlanes,      VkPointClippingBehavior :: VK_POINT_CLIPPING_BEHAVIOR_ALL_CLIP_PLANES ),
            Field ( UserClipPlanesOnly, VkPointClippingBehavior :: VK_POINT_CLIPPING_BEHAVIOR_USER_CLIP_PLANES_ONLY )
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

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

#define C_ENG_MAP_START     ENUM ( QueueFlag, TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Graphics,       VkQueueFlagBits :: VK_QUEUE_GRAPHICS_BIT ),
            Field ( Compute,        VkQueueFlagBits :: VK_QUEUE_COMPUTE_BIT ),
            Field ( Transfer,       VkQueueFlagBits :: VK_QUEUE_TRANSFER_BIT ),
            Field ( SparseBinding,  VkQueueFlagBits :: VK_QUEUE_SPARSE_BINDING_BIT ),
            Field ( Protected,      VkQueueFlagBits :: VK_QUEUE_PROTECTED_BIT ),

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_DECODE_QUEUE_AVAILABLE

            Field ( VideoDecode,    VkQueueFlagBits :: VK_QUEUE_VIDEO_DECODE_BIT_KHR ),

#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_ENCODE_QUEUE_AVAILABLE

            Field ( VideoEncode,    VkQueueFlagBits :: VK_QUEUE_VIDEO_ENCODE_BIT_KHR )

#endif

        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     ENUM ( PipelineStageFlag, TYPE ( cds :: uint32 ) )
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

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE

            Field ( None,                           VkPipelineStageFlagBits :: VK_PIPELINE_STAGE_NONE_KHR ),

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE

            Field ( ShadingRateImage,               VkPipelineStageFlagBits :: VK_PIPELINE_STAGE_SHADING_RATE_IMAGE_BIT_NV ),

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
            Field ( AllCommands,                    VkPipelineStageFlagBits :: VK_PIPELINE_STAGE_ALL_COMMANDS_BIT )
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_AVAILABLE

#define C_ENG_MAP_START     ENUM ( GlobalQueuePriority, TYPE ( cds :: uint32 ) )
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
            Field ( EncodeH265, VkVideoCodecOperationFlagBitsKHR :: VK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_EXT ),
            Field ( DecodeH264, VkVideoCodecOperationFlagBitsKHR :: VK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_EXT ),
            Field ( DecodeH265, VkVideoCodecOperationFlagBitsKHR :: VK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_EXT ),

#endif

            Field ( Invalid,    VkVideoCodecOperationFlagBitsKHR :: VK_VIDEO_CODEC_OPERATION_INVALID_BIT_KHR )

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

        __C_ENG_ALIAS ( GenericStructure, void );

        __C_ENG_ALIAS ( InstanceHandle,                 VkInstance );
        __C_ENG_ALIAS ( DebugMessengerHandle,           VkDebugUtilsMessengerEXT );
        __C_ENG_ALIAS ( PhysicalDeviceHandle,           VkPhysicalDevice );
        __C_ENG_ALIAS ( SurfaceHandle,                  VkSurfaceKHR );

        __C_ENG_ALIAS ( InstanceCreateFlags,            VkInstanceCreateFlags );
        __C_ENG_ALIAS ( DebugMessengerCreateFlags,      VkDebugUtilsMessengerCreateFlagsEXT );
        __C_ENG_ALIAS ( SampleCountFlags,               VkSampleCountFlags );
        __C_ENG_ALIAS ( ShaderStageFlags,               VkShaderStageFlags );
        __C_ENG_ALIAS ( QueueFlags,                     VkQueueFlags );
        __C_ENG_ALIAS ( PipelineStageFlags,             VkPipelineStageFlags );

        __C_ENG_ALIAS ( DebugMessageSeverityFlags,      VkDebugUtilsMessageSeverityFlagsEXT );
        __C_ENG_ALIAS ( DebugMessageTypeFlags,          VkDebugUtilsMessageTypeFlagsEXT );
        __C_ENG_ALIAS ( DebugMessengerCallback,         PFN_vkDebugUtilsMessengerCallbackEXT );

        __C_ENG_ALIAS ( AllocationFunction,             PFN_vkAllocationFunction );
        __C_ENG_ALIAS ( ReallocationFunction,           PFN_vkReallocationFunction );
        __C_ENG_ALIAS ( FreeFunction,                   PFN_vkFreeFunction );
        __C_ENG_ALIAS ( InternalAllocationNotification, PFN_vkInternalAllocationNotification );
        __C_ENG_ALIAS ( InternalFreeNotification,       PFN_vkInternalFreeNotification );

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


#define C_ENG_MAP_START     STRUCT ( Version, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            cds :: uint8    variant;
            cds :: uint8    major;
            cds :: uint16   minor;
            cds :: uint16   patch;
        };

        constexpr const Self nullVersion = {
                .variant    = static_cast < cds :: uint8 > ( 0 ),
                .major      = static_cast < cds :: uint8 > ( 0 ),
                .minor      = static_cast < cds :: uint8 > ( 0 ),
                .patch      = static_cast < cds :: uint8 > ( 0 )
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( ApplicationInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                  structureType;
            __C_ENG_TYPE ( GenericStructure )             * pNext;

            cds :: StringLiteral                            name;
            __C_ENG_TYPE ( Version )                        version;

            cds :: StringLiteral                            engineName;
            __C_ENG_TYPE ( Version )                        engineVersion;

            __C_ENG_TYPE ( Version )                        apiVersion;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( LayerProperties, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            char                        layerName [ VK_MAX_EXTENSION_NAME_SIZE ];
            __C_ENG_TYPE ( Version )    specVersion;
            cds :: uint32               implementationVersion;
            char                        description [ VK_MAX_DESCRIPTION_SIZE ];
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( ExtensionProperties, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            char                        name [ VK_MAX_EXTENSION_NAME_SIZE ];
            cds :: uint32               specVersion;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( DebugMessengerCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                  structureType;
            __C_ENG_TYPE ( GenericStructure )             * pNext;
            __C_ENG_TYPE ( DebugMessengerCreateFlags )      flags;
            __C_ENG_TYPE ( DebugMessageSeverityFlags )      messageSeverityFlags;
            __C_ENG_TYPE ( DebugMessageTypeFlags )          messageTypeFlags;
            __C_ENG_TYPE ( DebugMessengerCallback )         callback;
            void                                          * pCallbackUserData;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( InstanceCreateInfo, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                  structureType;
            __C_ENG_TYPE ( GenericStructure )             * pNext;
            __C_ENG_TYPE ( InstanceCreateFlags )            flags;
            __C_ENG_TYPE ( ApplicationInfo )        const * pApplicationInfo;

            cds :: uint32                                   enabledLayerCount;
            cds :: StringLiteral                    const * pEnabledLayerNames;

            cds :: uint32                                   enabledExtensionCount;
            cds :: StringLiteral                    const * pEnabledExtensionNames;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( AllocationCallbacks, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            void                                              * pUserData;
            __C_ENG_TYPE ( AllocationFunction )                 allocationCallback;
            __C_ENG_TYPE ( ReallocationFunction )               reallocationCallback;
            __C_ENG_TYPE ( FreeFunction )                       freeCallback;
            __C_ENG_TYPE ( InternalAllocationNotification )     internalAllocationNotificationCallback;
            __C_ENG_TYPE ( InternalFreeNotification )           internalFreeNotificationCallback;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( ValidationFeatures, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericStructure )                 * pNext;
            cds :: uint32                                       enabledValidationFeatureCount;
            __C_ENG_TYPE ( ValidationFeatureEnable )    const * pEnabledValidationFeatures;
            cds :: uint32                                       disabledValidationFeatureCount;
            __C_ENG_TYPE ( ValidationFeatureDisable )   const * pDisabledValidationFeatures;
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

            __C_ENG_TYPE ( DeviceSize )         bufferImageGranularity;
            __C_ENG_TYPE ( DeviceSize )         sparseAddressSpaceSize;

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

            __C_ENG_TYPE ( DeviceSize )         minTexelBufferOffsetAlignment;
            __C_ENG_TYPE ( DeviceSize )         minUniformBufferOffsetAlignment;
            __C_ENG_TYPE ( DeviceSize )         minStorageBufferOffsetAlignment;

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

            __C_ENG_TYPE ( SampleCountFlags )   framebufferColorSampleCounts;
            __C_ENG_TYPE ( SampleCountFlags )   framebufferDepthSampleCounts;
            __C_ENG_TYPE ( SampleCountFlags )   framebufferStencilSampleCounts;
            __C_ENG_TYPE ( SampleCountFlags )   framebufferNoAttachmentsSampleCounts;

            cds :: uint32                       maxColorAttachments;

            __C_ENG_TYPE ( SampleCountFlags )   sampledImageColorSampleCounts;
            __C_ENG_TYPE ( SampleCountFlags )   sampledImageIntegerSampleCounts;
            __C_ENG_TYPE ( SampleCountFlags )   sampledImageDepthSampleCounts;
            __C_ENG_TYPE ( SampleCountFlags )   sampledImageStencilSampleCounts;
            __C_ENG_TYPE ( SampleCountFlags )   storageImageSampleCounts;

            cds :: uint32                       maxSampleMaskWords;

            __C_ENG_TYPE ( Bool )               timestampComputeAndGraphics;
            float                               timestampPeriod;

            cds :: uint32                       maxClipDistances;
            cds :: uint32                       maxCullDistances;
            cds :: uint32                       maxCombinedClipAndCullDistances;

            cds :: uint32                       discreteQueuePriorities;

            float                               pointSizeRange[2];
            float                               lineWidthRange[2];
            float                               pointSizeGranularity;
            float                               lineWidthGranularity;
            __C_ENG_TYPE ( Bool )               strictLines;

            __C_ENG_TYPE ( Bool )               standardSampleLocations;

            __C_ENG_TYPE ( DeviceSize )         optimalBufferCopyOffsetAlignment;
            __C_ENG_TYPE ( DeviceSize )         optimalBufferCopyRowPitchAlignment;

            __C_ENG_TYPE ( DeviceSize )         nonCoherentAtomSize;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceSparseProperties,    NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( Bool ) residencyStandard2DBlockShape;
            __C_ENG_TYPE ( Bool ) residencyStandard2DMultisampleBlockShape;
            __C_ENG_TYPE ( Bool ) residencyStandard3DBlockShape;
            __C_ENG_TYPE ( Bool ) residencyAlignedMipSize;
            __C_ENG_TYPE ( Bool ) residencyNonResidentStrict;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceProperties,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( Version )                        apiVersion;
            cds :: uint32                                   driverVersion;
            cds :: uint32                                   vendorID;
            cds :: uint32                                   deviceID;
            __C_ENG_TYPE ( PhysicalDeviceType )             deviceType;
            char                                            deviceName [ VK_MAX_PHYSICAL_DEVICE_NAME_SIZE ];
            cds :: uint8                                    pipelineCacheUUID [ VK_UUID_SIZE ];
            __C_ENG_TYPE ( PhysicalDeviceLimits )           limits;
            __C_ENG_TYPE ( PhysicalDeviceSparseProperties ) sparseProperties;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceExtendedProperties,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                  structureType;
            __C_ENG_TYPE ( GenericStructure )             * pNext;
            __C_ENG_TYPE ( PhysicalDeviceProperties )       properties;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( GenericInStructure,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericInStructure )         const * pNext;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     STRUCT ( GenericOutStructure,  NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )                      structureType;
            __C_ENG_TYPE ( GenericOutStructure )              * pNext;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

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


#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE

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


#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE

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


#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE

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


#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE

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


#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE

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

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceDetails,     NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {

            __C_ENG_TYPE ( PhysicalDeviceProperties )                                       basicProperties;

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceVulkan11Properties )                               vulkan11Properties;
            __C_ENG_TYPE ( PhysicalDeviceIDProperties )                                     IDProperties;
            __C_ENG_TYPE ( PhysicalDeviceMaintenanceProperties )                            maintenanceProperties;
            __C_ENG_TYPE ( PhysicalDeviceMultiviewProperties )                              multiviewProperties;
            __C_ENG_TYPE ( PhysicalDevicePointClippingProperties )                          pointClippingProperties;
            __C_ENG_TYPE ( PhysicalDeviceProtectedMemoryProperties )                        protectedMemoryProperties;
            __C_ENG_TYPE ( PhysicalDeviceSubgroupProperties )                               subgroupProperties;
                                                                                            
#endif                                                                                      
                                                                                            
#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE                                                

            __C_ENG_TYPE ( PhysicalDeviceVulkan12Properties )                               vulkan12Properties;
            __C_ENG_TYPE ( PhysicalDeviceDriverProperties )                                 driverProperties;
            __C_ENG_TYPE ( PhysicalDeviceDepthStencilResolveProperties )                    depthStencilResolveProperties;
            __C_ENG_TYPE ( PhysicalDeviceDescriptorIndexingProperties )                     descriptorIndexingProperties;
            __C_ENG_TYPE ( PhysicalDeviceFloatControlsProperties )                          deviceFloatControlsProperties;
            __C_ENG_TYPE ( PhysicalDeviceSamplerFilterMinmaxProperties )                    samplerFilterMinmaxProperties;
            __C_ENG_TYPE ( PhysicalDeviceTimelineSemaphoreProperties )                      timelineSemaphoreProperties;
                                                                                            
#endif                                                                                      
                                                                                            
#if __C_ENG_VULKAN_API_EXTENSION_PCI_BUS_INFO_AVAILABLE                                     
                                                                                            
            __C_ENG_TYPE ( PhysicalDevicePCIBusInfoProperties )                             pciBusInfoProperties;
                                                                                            
#endif                                                                                      
                                                                                            
#if __C_ENG_VULKAN_API_EXTENSION_PHYSICAL_DEVICE_DRM_AVAILABLE                              
                                                                                            
            __C_ENG_TYPE ( PhysicalDeviceDRMProperties )                                    DRMProperties;
                                                                                            
#endif                                                                                      
                                                                                            
#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE                   
                                                                                            
            __C_ENG_TYPE ( PhysicalDeviceAccelerationStructureProperties )                  accelerationStructureProperties;
                                                                                            
#endif                                                                                      
                                                                                            
#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE                         
                                                                                            
            __C_ENG_TYPE ( PhysicalDeviceBlendOperationAdvancedProperties )                 blendOperationAdvancedProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONSERVATIVE_RASTERIZATION_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceConservativeRasterizationProperties )              conservativeRasterizationProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceCooperativeMatrixPropertiesNVidia )                cooperativeMatrixPropertiesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceCustomBorderColorProperties )                      customBorderColorProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceDeviceGeneratedCommandsPropertiesNVidia )          deviceGeneratedCommandsProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISCARD_RECTANGLES_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceDiscardRectangleProperties )                       discardRectangleProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTERNAL_MEMORY_HOST_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceExternalMemoryHostProperties )                     externalMemoryHostProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMap2Properties )                    fragmentDensityMap2Properties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMapOffsetPropertiesQualcomm )       fragmentDensityMapOffsetPropertiesQualcomm;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMapProperties )                     fragmentDensityMapProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceFragmentShadingRateEnumsPropertiesNVidia )         fragmentShadingRateEnumsPropertiesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceFragmentShadingRateProperties )                    fragmentShadingRateProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceInlineUniformBlockProperties )                     inlineUniformBlockProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceLineRasterizationProperties )                      lineRasterizationProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceMaintenance4Properties )                           maintenance4Properties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceMeshShaderPropertiesNVidia )                       meshShaderPropertiesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceMultiDrawProperties )                              multiDrawProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceMultiviewPerViewAttributesPropertiesNVidia )       multiviewPerViewAttributesPropertiesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

            __C_ENG_TYPE ( PhysicalDevicePerformanceQueryProperties )                       performanceQueryProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE

            __C_ENG_TYPE ( PhysicalDevicePortabilitySubsetProperties )                      portabilitySubsetProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceProvokingVertexProperties )                        provokingVertexProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PUSH_DESCRIPTOR_AVAILABLE

            __C_ENG_TYPE ( PhysicalDevicePushDescriptorProperties )                         pushDescriptorProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceRayTracingPipelineProperties )                     rayTracingPipelineProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceRayTracingPropertiesNVidia )                       rayTracingPropertiesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceRobustnessProperties )                             robustnessProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceSampleLocationsProperties )                        sampleLocationsProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceShaderCorePropertiesAMD )                          shaderCorePropertiesAMD;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_2_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceShaderCoreProperties2AMD )                         shaderCoreProperties2AMD;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceShaderSMBuiltinsPropertiesNVidia )                 shaderSmBuiltinsProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceShadingRateImagePropertiesNVidia )                 shadingRateImagePropertiesNVidia;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceSubgroupSizeControlProperties )                    subgroupSizeControlProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceSubpassShadingPropertiesHuawei )                   subpassShadingPropertiesHuawei;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceTexelBufferAlignmentProperties )                   texelBufferAlignmentProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceTransformFeedbackProperties )                      transformFeedbackProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceVertexAttributeDivisorProperties )                 vertexAttributeDivisorProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE

            __C_ENG_TYPE ( PhysicalDeviceShaderIntegerDotProductProperties )                shaderIntegerDotProductProperties;

#endif

        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


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

#define C_ENG_MAP_START     STRUCT ( QueueFamilyExtendedProperties, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )              type;
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
            __C_ENG_TYPE ( StructureType )      type;
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
            __C_ENG_TYPE ( StructureType )          type;
            __C_ENG_TYPE ( GenericStructure )     * pNext;
            cds :: uint32                           priorityCount;
            __C_ENG_TYPE ( GlobalQueuePriority )    priorities [ VK_MAX_GLOBAL_PRIORITY_SIZE_EXT ];
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE

#define C_ENG_MAP_START     STRUCT ( QueueFamilyQueryResultStatusProperties, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )          type;
            __C_ENG_TYPE ( GenericStructure )     * pNext;
            __C_ENG_TYPE ( Bool )                   supported;
        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#define C_ENG_MAP_START     STRUCT ( VideoQueueFamilyProperties, NO_PARENT )
#include <ObjectMapping.hpp>

        Struct {
            __C_ENG_TYPE ( StructureType )              type;
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
            __C_ENG_TYPE ( StructureType )                              structureType;
            __C_ENG_TYPE ( GenericStructure )                         * pNext;

            __C_ENG_TYPE ( QueueFamilyProperties )                      properties;

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTIC_CHECKPOINTS_AVAILABLE

            __C_ENG_TYPE ( QueueFamilyCheckpointPropertiesNVidia )      checkpointProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE

            __C_ENG_TYPE ( QueueFamilyGlobalPriorityProperties )        globalPriorityProperties;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE

            __C_ENG_TYPE ( QueueFamilyQueryResultStatusProperties )     queryResultStatusProperties;

#endif

        };

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif


#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( Result ) ) noexcept -> cds :: StringLiteral;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( StructureType ) ) noexcept -> cds :: StringLiteral;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( DebugMessageSeverityFlag ) ) noexcept -> cds :: StringLiteral;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( DebugMessageTypeFlag ) ) noexcept -> cds :: StringLiteral;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( ValidationFeatureEnable ) ) noexcept -> cds :: StringLiteral;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( ValidationFeatureDisable ) ) noexcept -> cds :: StringLiteral;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceType ) ) noexcept -> cds :: StringLiteral;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( VendorID ) ) noexcept -> cds :: StringLiteral;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( SampleCountFlag ) ) noexcept -> cds :: StringLiteral;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PointClippingBehavior ) ) noexcept -> cds :: StringLiteral;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( ShaderStageFlag ) ) noexcept -> cds :: StringLiteral;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( QueueFlag ) ) noexcept -> cds :: StringLiteral;

#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( SubgroupFeatureFlag ) ) noexcept -> cds :: StringLiteral;

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( DriverID ) ) noexcept -> cds :: StringLiteral;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( ShaderFloatControlsIndependence ) ) noexcept -> cds :: StringLiteral;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( ResolveModeFlag ) ) noexcept -> cds :: StringLiteral;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_2_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( ShaderCorePropertiesFlagAMD ) ) noexcept -> cds :: StringLiteral;

#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( Offset2D ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( Offset3D ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( Extent2D ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( Extent3D ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( Rect ) const & ) noexcept -> cds :: String;

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( Version ) const & ) noexcept -> cds :: String;

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( DeviceSize ) ) noexcept -> cds :: String;

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( ApplicationInfo ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( InstanceCreateInfo ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( DebugMessengerCreateInfo ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( LayerProperties ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( ExtensionProperties ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( AllocationCallbacks ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( ValidationFeatures ) const & ) noexcept -> cds :: String;

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceLimits ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceSparseProperties ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceProperties ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceExtendedProperties ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceDetails ) const & ) noexcept -> cds :: String;

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( QueueFamilyProperties ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceVulkan11Properties ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceIDProperties ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceMaintenanceProperties ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceMultiviewProperties ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDevicePointClippingProperties ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceProtectedMemoryProperties ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceSubgroupProperties ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( ConformanceVersion ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceVulkan12Properties ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceDriverProperties ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceDepthStencilResolveProperties ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceDescriptorIndexingProperties ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceFloatControlsProperties ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceSamplerFilterMinmaxProperties ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceTimelineSemaphoreProperties ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PCI_BUS_INFO_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDevicePCIBusInfoProperties ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PHYSICAL_DEVICE_DRM_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceDRMProperties ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceAccelerationStructureProperties ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceBlendOperationAdvancedProperties ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONSERVATIVE_RASTERIZATION_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceConservativeRasterizationProperties ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceCooperativeMatrixPropertiesNVidia ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceCustomBorderColorProperties ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceDeviceGeneratedCommandsPropertiesNVidia ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISCARD_RECTANGLES_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceDiscardRectangleProperties ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTERNAL_MEMORY_HOST_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceExternalMemoryHostProperties ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMap2Properties ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMapOffsetPropertiesQualcomm ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMapProperties ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceFragmentShadingRateEnumsPropertiesNVidia ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceFragmentShadingRateProperties ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceInlineUniformBlockProperties ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceLineRasterizationProperties ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceMaintenance4Properties ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceMeshShaderPropertiesNVidia ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceMultiDrawProperties ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceMultiviewPerViewAttributesPropertiesNVidia ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDevicePortabilitySubsetProperties ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceProvokingVertexProperties ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PUSH_DESCRIPTOR_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDevicePushDescriptorProperties ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceRayTracingPipelineProperties ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceRayTracingPropertiesNVidia ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceRobustnessProperties ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceSampleLocationsProperties ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceShaderCorePropertiesAMD ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_SHADER_CORE_PROPERTIES_2_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceShaderCoreProperties2AMD ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceShaderSMBuiltinsPropertiesNVidia ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceShadingRateImagePropertiesNVidia ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceSubgroupSizeControlProperties ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceSubpassShadingPropertiesHuawei ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceTexelBufferAlignmentProperties ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceTransformFeedbackProperties ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceVertexAttributeDivisorProperties ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceShaderIntegerDotProductProperties ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDevicePerformanceQueryProperties ) const & ) noexcept -> cds :: String;

#endif

        __C_ENG_NO_DISCARD auto compare ( __C_ENG_TYPE ( Version ) const &, __C_ENG_TYPE ( Version ) const & ) noexcept -> __C_ENG_TYPE ( CompareResult );

        __C_ENG_NO_DISCARD auto uInt32ToInstanceVersion ( cds :: uint32 ) noexcept -> __C_ENG_TYPE ( Version );
        __C_ENG_NO_DISCARD auto instanceVersionToUInt32 ( __C_ENG_TYPE ( Version ) const & ) noexcept -> cds :: uint32;
        __C_ENG_NO_DISCARD auto versionReadableFormat ( __C_ENG_TYPE ( Version ) const & ) noexcept -> cds :: String;

    }
}

#include <VulkanAPICalls.hpp>

#endif //__C_ENG_VULKANCORE_HPP

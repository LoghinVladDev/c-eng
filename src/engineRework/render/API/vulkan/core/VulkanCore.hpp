//
// Created by loghin on 26.12.2021.
//

#ifndef __C_ENG_VULKAN_CORE_HPP__
#define __C_ENG_VULKAN_CORE_HPP__

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

            Field ( PhysicalDeviceSubgroupSizeControlFeatures,                             VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_SIZE_CONTROL_PROPERTIES ),
            Field ( PhysicalDeviceSubgroupSizeControlProperties,                           VkStructureType :: VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_REQUIRED_SUBGROUP_SIZE_CREATE_INFO ),
            Field ( PipelineShaderStageRequiredSubgroupSizeCreateInfo,                     VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_SIZE_CONTROL_FEATURES ),

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

            Field ( PhysicalDeviceTexelBufferAlignmentFeatures,                            VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TEXEL_BUFFER_ALIGNMENT_FEATURES ),
            Field ( PhysicalDeviceTexelBufferAlignmentProperties,                          VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TEXEL_BUFFER_ALIGNMENT_PROPERTIES ),

            Field ( FormatProperties3,                                                     VkStructureType :: VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_3 ),

            Field ( PhysicalDeviceMaintenance4Features,                                    VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_4_FEATURES ),
            Field ( PhysicalDeviceMaintenance4Properties,                                  VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_4_PROPERTIES ),
            Field ( PhysicalDeviceBufferMemoryRequirements,                                VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_BUFFER_MEMORY_REQUIREMENTS ),
            Field ( PhysicalDeviceImageMemoryRequirements,                                 VkStructureType :: VK_STRUCTURE_TYPE_DEVICE_IMAGE_MEMORY_REQUIREMENTS ),

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

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE

            Field ( MutiviewPerViewAttributesInfoNVidiaExperimental,                       VkStructureType :: VK_STRUCTURE_TYPE_MULTIVIEW_PER_VIEW_ATTRIBUTES_INFO_NVX ),
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

            Field ( PhysicalDeviceBufferDeviceAddressFeaturesExt,                          VkStructureType :: VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BUFFER_DEVICE_ADDRESS_FEATURES_EXT ),
            Field ( BufferDeviceAddressCreateInfoExt,                                      VkStructureType :: VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_CREATE_INFO_EXT ),

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


#define C_ENG_MAP_START     ENUM ( DeviceQueueCreateFlag,   TYPE ( cds :: uint32 ) )
#include <ObjectMapping.hpp>

        Enum {
            Field ( Protected,  VkDeviceQueueCreateFlagBits :: VK_DEVICE_QUEUE_CREATE_PROTECTED_BIT )
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
            Field ( Present,        VkQueueFlagBits :: VK_QUEUE_PROTECTED_BIT * 2U ), // NOLINT(clion-misra-cpp2008-4-5-2)

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
            Field ( AllCommands,                    VkPipelineStageFlagBits :: VK_PIPELINE_STAGE_ALL_COMMANDS_BIT )
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
            Field ( EncodeH265, VkVideoCodecOperationFlagBitsKHR :: VK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_EXT ),
            Field ( DecodeH264, VkVideoCodecOperationFlagBitsKHR :: VK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_EXT ),
            Field ( DecodeH265, VkVideoCodecOperationFlagBitsKHR :: VK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_EXT ),

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
            Field ( Framebuffer,                    VkObjectType :: VK_OBJECT_TYPE_FRAMEBUFFER ),
            Field ( CommandPool,                    VkObjectType :: VK_OBJECT_TYPE_COMMAND_POOL )
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
        __C_ENG_ALIAS ( DeviceHandle,                   VkDevice );
        __C_ENG_ALIAS ( QueueHandle,                    VkQueue );

        __C_ENG_ALIAS ( InstanceCreateFlags,            VkInstanceCreateFlags );
        __C_ENG_ALIAS ( DebugMessengerCreateFlags,      VkDebugUtilsMessengerCreateFlagsEXT );
        __C_ENG_ALIAS ( DeviceCreateFlags,              VkDeviceCreateFlags );
        __C_ENG_ALIAS ( DeviceQueueCreateFlags,         VkDeviceQueueCreateFlags );
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


#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

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

#define C_ENG_MAP_START     STRUCT ( PhysicalDeviceImagelessFramebufferFeatures, NO_PARENT )
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
            __C_ENG_TYPE ( PhysicalDeviceImagelessFramebufferFeatures )                     imagelessFramebufferFeatures;
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
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PipelineStageFlag ) ) noexcept -> cds :: StringLiteral;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( DeviceQueueCreateFlag ) ) noexcept -> cds :: StringLiteral;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( ObjectType ) ) noexcept -> cds :: StringLiteral;

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

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( QueueGlobalPriority ) ) noexcept -> cds :: StringLiteral;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( VideoCodecOperationFlag ) ) noexcept -> cds :: StringLiteral;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PerformanceCounterUnit ) ) noexcept -> cds :: StringLiteral;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PerformanceCounterScope ) ) noexcept -> cds :: StringLiteral;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PerformanceCounterStorage ) ) noexcept -> cds :: StringLiteral;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PerformanceCounterDescriptionFlag ) ) noexcept -> cds :: StringLiteral;

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
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceFeatures ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceDetails ) const & ) noexcept -> cds :: String;

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( QueueFamilyProperties ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( QueueFamilyExtendedProperties ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( QueueFamilyDetails ) const & ) noexcept -> cds :: String;

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( DeviceCreateInfo ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( DeviceQueueCreateInfo ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceExtendedProperties ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceVulkan11Properties ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceIDProperties ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceMaintenanceProperties ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceMultiviewProperties ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDevicePointClippingProperties ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceProtectedMemoryProperties ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceSubgroupProperties ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceGroupProperties ) const & ) noexcept -> cds :: String;

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceExtendedFeatures ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceVulkan11Features ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDevice16BitStorageFeatures ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceMultiviewFeatures ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceProtectedMemoryFeatures ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceSamplerYCBCRConversionFeatures ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceShaderDrawParametersFeatures ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceVariablePointersFeatures ) const & ) noexcept -> cds :: String;

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( DeviceGroupDeviceCreateInfo ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( DeviceQueueInfo ) const & ) noexcept -> cds :: String;

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

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDevice8BitStorageFeatures ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceVulkan12Features ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceBufferDeviceAddressFeatures ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceDescriptorIndexingFeatures ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceHostQueryResetFeatures ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceImagelessFramebufferFeatures ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceScalarBlockLayoutFeatures ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceSeparateDepthStencilLayoutsFeatures ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceShaderAtomicInt64Features ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceShaderFloat16Int8Features ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceShaderSubgroupExtendedTypesFeatures ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceTimelineSemaphoreFeatures ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceUniformBufferStandardLayoutFeatures ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceVulkanMemoryModelFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceVulkan13Properties ) const & ) noexcept -> cds :: String;

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceVulkan13Features ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PCI_BUS_INFO_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDevicePCIBusInfoProperties ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PHYSICAL_DEVICE_DRM_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceDRMProperties ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceAccelerationStructureProperties ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceAccelerationStructureFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceBlendOperationAdvancedProperties ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceBlendOperationAdvancedFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONSERVATIVE_RASTERIZATION_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceConservativeRasterizationProperties ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COOPERATIVE_MATRIX_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceCooperativeMatrixPropertiesNVidia ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceCooperativeMatrixFeaturesNVidia ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceCustomBorderColorProperties ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceDeviceGeneratedCommandsPropertiesNVidia ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceDeviceGeneratedCommandsFeaturesNVidia ) const & ) noexcept -> cds :: String;

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

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

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

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE

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

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceSubgroupSizeControlProperties ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceSubpassShadingPropertiesHuawei ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceTexelBufferAlignmentProperties ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceTransformFeedbackProperties ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceVertexAttributeDivisorProperties ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceShaderIntegerDotProductProperties ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDevicePerformanceQueryProperties ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PerformanceCounter ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PerformanceCounterDescription ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTIC_CHECKPOINTS_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( QueueFamilyCheckpointPropertiesNVidia ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( DeviceQueueGlobalPriorityCreateInfo ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( QueueFamilyGlobalPriorityProperties ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( QueueFamilyQueryResultStatusProperties ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( VideoQueueFamilyProperties ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTICS_CONFIG_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( DeviceDiagnosticsConfigFlagNVidia ) ) noexcept -> cds :: StringLiteral;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( DeviceDiagnosticsConfigCreateInfoNVidia ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_MEMORY_OVERALLOCATION_BEHAVIOUR_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( MemoryOverallocationBehaviorAMD ) ) noexcept -> cds :: StringLiteral;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( DeviceMemoryOverallocationCreateInfoAMD ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( DevicePrivateDataCreateInfo ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_4444_FORMATS_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDevice4444FormatsFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ASTC_DECODE_MODE_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceASTCDecodeFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BORDER_COLOR_SWIZZLE_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceBorderColorSwizzleFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_DEVICE_COHERENT_MEMORY_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceCoherentMemoryFeaturesAMD ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_COLOR_WRITE_ENABLE_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceColorWriteEnableFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COMPUTE_SHADER_DERIVATIVES_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceComputeShaderDerivativesFeaturesNVidia ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONDITIONAL_RENDERING_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceConditionalRenderingFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CORNER_SAMPLED_IMAGE_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceCornerSampledImageFeaturesNVidia ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COVERAGE_REDUCTION_MODE_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceCoverageReductionModeFeaturesNVidia ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceCustomBorderColorFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_IMAGE_ALIASING_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNVidia ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_CONTROL_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceDepthClipControlFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_ENABLE_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceDepthClipEnableFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEVICE_MEMORY_REPORT_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceDeviceMemoryReportFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_DIAGNOSTICS_CONFIG_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceDiagnosticsConfigFeaturesNVidia ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceDynamicRenderingFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SCISSOR_EXCLUSIVE_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceExclusiveScissorFeaturesNVidia ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceExtendedDynamicStateFeatures ) const & ) noexcept -> cds :: String;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceExtendedDynamicState2Features ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTENDED_DYNAMIC_STATE_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceExternalMemoryRDMAFeaturesNVidia ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_2_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMap2Features ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_DENSITY_MAP_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMapFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_FRAGMENT_DENSITY_MAP_OFFSET_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceFragmentDensityMapOffsetFeaturesQualcomm ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADER_BARYCENTRIC_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceFragmentShaderBarycentricFeaturesNVidia ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_FRAGMENT_SHADER_INTERLOCK_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceFragmentShaderInterlockFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceFragmentShadingRateEnumsFeaturesNVidia ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceFragmentShadingRateFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GLOBAL_PRIORITY_QUERY_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceGlobalPriorityQueryFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_ROBUSTNESS_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceImageRobustnessFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_VIEW_MIN_LOD_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceImageViewMinLODFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INDEX_TYPE_UINT8_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceIndexTypeUInt8Features ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_INHERITED_VIEWPORT_SCISSOR_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceInheritedViewportScissorFeaturesNVidia ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceInlineUniformBlockFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_INVOCATION_MASK_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceInvocationMaskFeaturesHuawei ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceLineRasterizationFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_LINEAR_COLOR_ATTACHMENT_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceLinearColorAttachmentFeaturesNVidia ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceMaintenance4Features ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_PRIORITY_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceMemoryPriorityFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_MESH_SHADER_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceMeshShaderFeaturesNVidia ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MULTI_DRAW_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceMultiDrawFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceMutableDescriptorTypeFeaturesValve ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PAGEABLE_DEVICE_LOCAL_MEMORY_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDevicePageableDeviceLocalMemoryFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDevicePerformanceQueryFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDevicePipelineCreationCacheControlFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDevicePipelineExecutablePropertiesFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PORTABILITY_SUBSET_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDevicePortabilitySubsetFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_ID_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDevicePresentIDFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PRESENT_WAIT_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDevicePresentWaitFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIMITIVE_TOPOLOGY_LIST_RESTART_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDevicePrimitiveTopologyListRestartFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDevicePrivateDataFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceProvokingVertexFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_RGBA_10_X_6_FORMATS_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceRGBA10x6FormatsFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ARM_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_QUERY_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceRayQueryFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceRayTracingMotionBlurFeaturesNVidia ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceRayTracingPipelineFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_REPRESENTATIVE_FRAGMENT_TEST_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceRepresentativeFragmentTestFeaturesNVidia ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_ROBUSTNESS_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceRobustnessFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceShaderAtomicFloatFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_ATOMIC_FLOAT_2_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceShaderAtomicFloat2Features ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_CLOCK_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceShaderClockFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_DEMOTE_TO_HELPER_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceShaderDemoteToHelperInvocationFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SHADER_IMAGE_ATOMIC_INT64_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceShaderImageAtomicInt64Features ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_IMAGE_FOOTPRINT_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceShaderImageFootprintFeaturesNVidia ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceShaderIntegerDotProductFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_SHADER_INTEGER_FUNCTIONS_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceShaderIntegerFunctionsFeaturesIntel ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADER_SM_BUILTINS_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceShaderSMBuiltinsFeaturesNVidia ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_SUBGROUP_UNIFORM_CONTROL_FLOW_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceShaderSubgroupUniformControlFlowFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_TERMINATE_INVOCATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceShaderTerminateInvocationFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceShadingRateImageFeaturesNVidia ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceSubgroupSizeControlFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceSubpassShadingFeaturesHuawei ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceSynchronizationFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceTexelBufferAlignmentFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TEXTURE_COMPRESSION_ASTC_HDR_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceTextureCompressionASTCHDRFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceTransformFeedbackFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceVertexAttributeDivisorFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_INPUT_DYNAMIC_STATE_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceVertexInputDynamicStateFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceWorkgroupMemoryExplicitLayoutFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_2_PLANE_444_FORMATS_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceYCBCR2Plane444FormatsFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_YCBCR_IMAGE_ARRAYS_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceYCBCRImageArraysFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ZERO_INITIALIZE_WORKGROUP_MEMORY_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( PhysicalDeviceZeroInitializeWorkgroupMemoryFeatures ) const & ) noexcept -> cds :: String;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEVICE_MEMORY_REPORT_AVAILABLE

        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( DeviceMemoryReportFlag ) ) noexcept -> cds :: StringLiteral;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( DeviceMemoryReportEventType ) ) noexcept -> cds :: StringLiteral;
        __C_ENG_NO_DISCARD auto toString ( __C_ENG_TYPE ( DeviceDeviceMemoryReportCreateInfo ) const & ) noexcept -> cds :: String;

#endif

        __C_ENG_NO_DISCARD auto compare ( __C_ENG_TYPE ( Version ) const &, __C_ENG_TYPE ( Version ) const & ) noexcept -> __C_ENG_TYPE ( CompareResult );

        __C_ENG_NO_DISCARD auto uInt32ToInstanceVersion ( cds :: uint32 ) noexcept -> __C_ENG_TYPE ( Version );
        __C_ENG_NO_DISCARD auto instanceVersionToUInt32 ( __C_ENG_TYPE ( Version ) const & ) noexcept -> cds :: uint32;
        __C_ENG_NO_DISCARD auto versionReadableFormat ( __C_ENG_TYPE ( Version ) const & ) noexcept -> cds :: String;

        namespace versionConstants {

            constexpr static __C_ENG_TYPE ( Version ) const nullVersion                         = { .variant = 0U, .major = 0U, .minor = 0U, .patch = 0U };
            constexpr static __C_ENG_TYPE ( Version ) const version10      __C_ENG_MAYBE_UNUSED = { .variant = 0U, .major = 1U, .minor = 0U, .patch = 0U };
            constexpr static __C_ENG_TYPE ( Version ) const version11                           = { .variant = 0U, .major = 1U, .minor = 1U, .patch = 0U };
            constexpr static __C_ENG_TYPE ( Version ) const version12      __C_ENG_MAYBE_UNUSED = { .variant = 0U, .major = 1U, .minor = 2U, .patch = 0U };

        }

    }
}

#endif //__C_ENG_VULKAN_CORE_HPP__

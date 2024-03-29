//
// Created by loghin on 16.02.2022.
//

#ifndef C_ENG_VULKANAPICALLSPRIVATE_HPP
#define C_ENG_VULKANAPICALLSPRIVATE_HPP

#include <calls/VulkanAPICalls.hpp>
#include <VulkanCoreConfig.hpp>


using FunctionHandleAddress = void **;


#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkDevicePrivateDataCreateInfo_t   = VkDevicePrivateDataCreateInfo;
#elif __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE
using VkDevicePrivateDataCreateInfo_t   = VkDevicePrivateDataCreateInfoEXT;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDeviceDynamicRenderingFeatures_t    = VkPhysicalDeviceDynamicRenderingFeatures;
#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE
using VkPhysicalDeviceDynamicRenderingFeatures_t    = VkPhysicalDeviceDynamicRenderingFeaturesKHR;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDeviceImageRobustnessFeatures_t     = VkPhysicalDeviceImageRobustnessFeatures;
#elif __C_ENG_VULKAN_API_EXTENSION_IMAGE_ROBUSTNESS_AVAILABLE
using VkPhysicalDeviceImageRobustnessFeatures_t     = VkPhysicalDeviceImageRobustnessFeaturesEXT;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDeviceInlineUniformBlockFeatures_t      = VkPhysicalDeviceInlineUniformBlockFeatures;
using VkPhysicalDeviceInlineUniformBlockProperties_t    = VkPhysicalDeviceInlineUniformBlockProperties;
using VkDescriptorPoolInlineUniformBlockCreateInfo_t    = VkDescriptorPoolInlineUniformBlockCreateInfo;
using VkWriteDescriptorSetInlineUniformBlock_t          = VkWriteDescriptorSetInlineUniformBlock;
#elif __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE
using VkPhysicalDeviceInlineUniformBlockFeatures_t      = VkPhysicalDeviceInlineUniformBlockFeaturesEXT;
using VkPhysicalDeviceInlineUniformBlockProperties_t    = VkPhysicalDeviceInlineUniformBlockPropertiesEXT;
using VkDescriptorPoolInlineUniformBlockCreateInfo_t    = VkDescriptorPoolInlineUniformBlockCreateInfoEXT;
using VkWriteDescriptorSetInlineUniformBlock_t          = VkWriteDescriptorSetInlineUniformBlockEXT;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDeviceMaintenance4Features_t        = VkPhysicalDeviceMaintenance4Features;
using VkPhysicalDeviceMaintenance4Properties_t      = VkPhysicalDeviceMaintenance4Properties;
#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_MAINTENANCE_4_AVAILABLE
using VkPhysicalDeviceMaintenance4Features_t        = VkPhysicalDeviceMaintenance4FeaturesKHR;
using VkPhysicalDeviceMaintenance4Properties_t      = VkPhysicalDeviceMaintenance4PropertiesKHR;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDevicePipelineCreationCacheControlFeatures_t    = VkPhysicalDevicePipelineCreationCacheControlFeatures;
#elif __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_CACHE_CONTROL_AVAILABLE
using VkPhysicalDevicePipelineCreationCacheControlFeatures_t    = VkPhysicalDevicePipelineCreationCacheControlFeaturesEXT;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPipelineCreationFeedback_t                              = VkPipelineCreationFeedback;
using VkPipelineCreationFeedbackCreateInfo_t                    = VkPipelineCreationFeedbackCreateInfo;
#elif __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_FEEDBACK_AVAILABLE
using VkPipelineCreationFeedback_t                              = VkPipelineCreationFeedbackEXT;
using VkPipelineCreationFeedbackCreateInfo_t                    = VkPipelineCreationFeedbackCreateInfoEXT;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDevicePrivateDataFeatures_t                     = VkPhysicalDevicePrivateDataFeatures;
#elif __C_ENG_VULKAN_API_EXTENSION_PRIVATE_DATA_AVAILABLE
using VkPhysicalDevicePrivateDataFeatures_t                     = VkPhysicalDevicePrivateDataFeaturesEXT;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDeviceShaderDemoteToHelperInvocationFeatures_t  = VkPhysicalDeviceShaderDemoteToHelperInvocationFeatures;
#elif __C_ENG_VULKAN_API_EXTENSION_SHADER_DEMOTE_TO_HELPER_INVOCATION_AVAILABLE
using VkPhysicalDeviceShaderDemoteToHelperInvocationFeatures_t  = VkPhysicalDeviceShaderDemoteToHelperInvocationFeaturesEXT;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDeviceShaderTerminateInvocationFeatures_t       = VkPhysicalDeviceShaderTerminateInvocationFeatures;
#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_TERMINATE_INVOCATION_AVAILABLE
using VkPhysicalDeviceShaderTerminateInvocationFeatures_t       = VkPhysicalDeviceShaderTerminateInvocationFeaturesKHR;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDeviceSubgroupSizeControlFeatures_t             = VkPhysicalDeviceSubgroupSizeControlFeatures;
using VkPhysicalDeviceSubgroupSizeControlProperties_t           = VkPhysicalDeviceSubgroupSizeControlProperties;
using VkPipelineShaderStageRequiredSubgroupSizeCreateInfo_t     = VkPipelineShaderStageRequiredSubgroupSizeCreateInfo;
#elif __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE
using VkPhysicalDeviceSubgroupSizeControlFeatures_t             = VkPhysicalDeviceSubgroupSizeControlFeaturesEXT;
using VkPhysicalDeviceSubgroupSizeControlProperties_t           = VkPhysicalDeviceSubgroupSizeControlPropertiesEXT;
using VkPipelineShaderStageRequiredSubgroupSizeCreateInfo_t     = VkPipelineShaderStageRequiredSubgroupSizeCreateInfoEXT;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDeviceSynchronization2Features_t                = VkPhysicalDeviceSynchronization2Features;
using VkSubmitInfo2_t                                           = VkSubmitInfo2;
using VkSemaphoreSubmitInfo_t                                   = VkSemaphoreSubmitInfo;
using VkCommandBufferSubmitInfo_t                               = VkCommandBufferSubmitInfo;
using VkDependencyInfo_t                                        = VkDependencyInfo;
using VkMemoryBarrier2_t                                        = VkMemoryBarrier2;
using VkBufferMemoryBarrier2_t                                  = VkBufferMemoryBarrier2;
using VkImageMemoryBarrier2_t                                   = VkImageMemoryBarrier2;
#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SYNCHRONIZATION_AVAILABLE
using VkPhysicalDeviceSynchronization2Features_t                = VkPhysicalDeviceSynchronization2FeaturesKHR;
using VkSubmitInfo2_t                                           = VkSubmitInfo2KHR;
using VkSemaphoreSubmitInfo_t                                   = VkSemaphoreSubmitInfoKHR;
using VkCommandBufferSubmitInfo_t                               = VkCommandBufferSubmitInfoKHR;
using VkDependencyInfo_t                                        = VkDependencyInfoKHR;
using VkMemoryBarrier2_t                                        = VkMemoryBarrier2KHR;
using VkBufferMemoryBarrier2_t                                  = VkBufferMemoryBarrier2KHR;
using VkImageMemoryBarrier2_t                                   = VkImageMemoryBarrier2KHR;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDeviceTexelBufferAlignmentFeatures_t            = VkPhysicalDeviceTexelBufferAlignmentFeaturesEXT;
using VkPhysicalDeviceTexelBufferAlignmentProperties_t          = VkPhysicalDeviceTexelBufferAlignmentProperties;
#elif __C_ENG_VULKAN_API_EXTENSION_TEXEL_BUFFER_ALIGNMENT_AVAILABLE
using VkPhysicalDeviceTexelBufferAlignmentFeatures_t            = VkPhysicalDeviceTexelBufferAlignmentFeaturesEXT;
using VkPhysicalDeviceTexelBufferAlignmentProperties_t          = VkPhysicalDeviceTexelBufferAlignmentPropertiesEXT;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDeviceTextureCompressionASTCHDRFeatures_t       = VkPhysicalDeviceTextureCompressionASTCHDRFeatures;
#elif __C_ENG_VULKAN_API_EXTENSION_TEXTURE_COMPRESSION_ASTC_HDR_AVAILABLE
using VkPhysicalDeviceTextureCompressionASTCHDRFeatures_t       = VkPhysicalDeviceTextureCompressionASTCHDRFeaturesEXT;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDeviceShaderIntegerDotProductFeatures_t         = VkPhysicalDeviceShaderIntegerDotProductFeatures;
using VkPhysicalDeviceShaderIntegerDotProductProperties_t       = VkPhysicalDeviceShaderIntegerDotProductProperties;
#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SHADER_INTEGER_DOT_PRODUCT_AVAILABLE
using VkPhysicalDeviceShaderIntegerDotProductFeatures_t         = VkPhysicalDeviceShaderIntegerDotProductFeaturesKHR;
using VkPhysicalDeviceShaderIntegerDotProductProperties_t       = VkPhysicalDeviceShaderIntegerDotProductPropertiesKHR;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkPhysicalDeviceZeroInitializeWorkgroupMemoryFeatures_t   = VkPhysicalDeviceZeroInitializeWorkgroupMemoryFeatures;
#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ZERO_INITIALIZE_WORKGROUP_MEMORY_AVAILABLE
using VkPhysicalDeviceZeroInitializeWorkgroupMemoryFeatures_t   = VkPhysicalDeviceZeroInitializeWorkgroupMemoryFeaturesKHR;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkCommandBufferInheritanceRenderingInfo_t                 = VkCommandBufferInheritanceRenderingInfo;
using VkRenderingInfo_t                                         = VkRenderingInfo;
using VkRenderingAttachmentInfo_t                               = VkRenderingAttachmentInfo;
using VkPipelineRenderingCreateInfo_t                           = VkPipelineRenderingCreateInfo;
#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE
using VkCommandBufferInheritanceRenderingInfo_t                 = VkCommandBufferInheritanceRenderingInfoKHR;
using VkRenderingInfo_t                                         = VkRenderingInfoKHR;
using VkRenderingAttachmentInfo_t                               = VkRenderingAttachmentInfoKHR;
using VkPipelineRenderingCreateInfo_t                           = VkPipelineRenderingCreateInfoKHR;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
using VkDeviceGroupDeviceCreateInfo_t                           = VkDeviceGroupDeviceCreateInfo;
#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DEVICE_GROUP_AVAILABLE
using VkDeviceGroupDeviceCreateInfo_t                           = VkDeviceGroupDeviceCreateInfoKHR;
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
using VkCopyBufferInfo2_t           = VkCopyBufferInfo2;
using VkBufferCopy2_t               = VkBufferCopy2;
using VkCopyImageInfo2_t            = VkCopyImageInfo2;
using VkImageCopy2_t                = VkImageCopy2;
using VkBlitImageInfo2_t            = VkBlitImageInfo2;
using VkImageBlit2_t                = VkImageBlit2;
using VkCopyBufferToImageInfo2_t    = VkCopyBufferToImageInfo2;
using VkCopyImageToBufferInfo2_t    = VkCopyImageToBufferInfo2;
using VkBufferImageCopy2_t          = VkBufferImageCopy2;
#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
using VkCopyBufferInfo2_t           = VkCopyBufferInfo2KHR;
using VkBufferCopy2_t               = VkBufferCopy2KHR;
using VkCopyImageInfo2_t            = VkCopyImageInfo2KHR;
using VkImageCopy2_t                = VkImageCopy2KHR;
using VkBlitImageInfo2_t            = VkBlitImageInfo2KHR;
using VkImageBlit2_t                = VkImageBlit2KHR;
using VkCopyBufferToImageInfo2_t    = VkCopyBufferToImageInfo2KHR;
using VkCopyImageToBufferInfo2_t    = VkCopyImageToBufferInfo2KHR;
using VkBufferImageCopy2_t          = VkBufferImageCopy2KHR;
#endif


#endif //C_ENG_VULKANAPICALLSPRIVATE_HPP

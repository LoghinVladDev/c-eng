//
// Created by vladl on 05/08/2020.
//

#ifndef ENG1_VULKANEXPLICITTYPES_H
#define ENG1_VULKANEXPLICITTYPES_H

#include <engineVulkanPreproc.hpp>
#include <CDS/Types>

/**
 * Header used to Label Vulkan Data Types Explicitly to avoid confusion with internal naming of objects
 */

namespace engine {

    using VulkanStructureType                                       = VkStructureType;

    using VulkanSurfaceKhronos                                      = VkSurfaceKHR;

    using VulkanFlags                                               = VkFlags;
    using VulkanQueueFlags                                          = VkQueueFlags;

    using VulkanPhysicalDevice                                      = VkPhysicalDevice;
    using VulkanPhysicalDeviceType                                  = VkPhysicalDeviceType;
    using VulkanPhysicalDeviceProperties                            = VkPhysicalDeviceProperties;
    using VulkanPhysicalDeviceFeatures                              = VkPhysicalDeviceFeatures;
    using VulkanPhysicalDeviceSparseProperties                      = VkPhysicalDeviceSparseProperties;
    using VulkanPhysicalDeviceLimits                                = VkPhysicalDeviceLimits;
    using VulkanPhysicalDeviceFeatures                              = VkPhysicalDeviceFeatures;
    using VulkanQueueFamilyProperties                               = VkQueueFamilyProperties;
    using VulkanDevice                                              = VkDevice;
    using VulkanQueue                                               = VkQueue;

    using VulkanDeviceQueueCreateInfo                               = VkDeviceQueueCreateInfo;
    using VulkanDeviceCreateInfo                                    = VkDeviceCreateInfo;

    using VulkanBool32                                              = VkBool32;

    using VulkanInstance                                            = VkInstance;
    using VulkanApplicationInfo                                     = VkApplicationInfo;
    using VulkanInstanceCreateInfo                                  = VkInstanceCreateInfo;

    using VulkanResult                                              = VkResult;

    using VulkanExtensionProperties                                 = VkExtensionProperties;

    using VulkanLayerProperties                                     = VkLayerProperties;


    using GLFWExtensionLiteral                                      = cds :: StringLiteral;
    using GLFWExtensionLiteralArray                                 = GLFWExtensionLiteral const *;


    using VulkanDebugMessengerCreateInfo                            = VkDebugUtilsMessengerCreateInfoEXT;
    using VulkanAllocationCallbacks                                 = VkAllocationCallbacks;
    using VulkanDebugMessenger                                      = VkDebugUtilsMessengerEXT;

    using VulkanDebugMessageSeverityFlagBits                        = VkDebugUtilsMessageSeverityFlagBitsEXT;
    using VulkanDebugMessageSeverityFlags         __CDS_MaybeUnused = VkDebugUtilsMessageSeverityFlagsEXT;

    using VulkanDebugMessageTypeFlagBits          __CDS_MaybeUnused = VkDebugUtilsMessageTypeFlagBitsEXT;
    using VulkanDebugMessageTypeFlags                               = VkDebugUtilsMessageTypeFlagsEXT;

    using VulkanDebugMessengerCallbackData                          = VkDebugUtilsMessengerCallbackDataEXT;
    using VulkanDebugMessengerCallbackDataFlags   __CDS_MaybeUnused = VkDebugUtilsMessengerCallbackDataFlagsEXT;

    using VulkanFlags                                               = VkFlags;

    using VulkanSurfaceCapabilitiesKhronos                          = VkSurfaceCapabilitiesKHR;
    using VulkanSurfaceFormatKhronos                                = VkSurfaceFormatKHR;
    using VulkanPresentModeKhronos                                  = VkPresentModeKHR;
    using VulkanExtent2D                                            = VkExtent2D;
    using VulkanExtent3D                                            = VkExtent3D;
    using VulkanOffset2D                          __CDS_MaybeUnused = VkOffset2D;
    using VulkanOffset3D                                            = VkOffset3D;
    using VulkanSwapChainKhronos                                    = VkSwapchainKHR;
    using VulkanSwapChainCreateInfoKhronos                          = VkSwapchainCreateInfoKHR;
    using VulkanImage                                               = VkImage;
    using VulkanFormat                                              = VkFormat;

    using VulkanPrimitiveTopology                                   = VkPrimitiveTopology;
    using VulkanPolygonMode                                         = VkPolygonMode;
    using VulkanCullModeFlagBits                                    = VkCullModeFlagBits;
    using VulkanFrontFace                                           = VkFrontFace;
    using VulkanLogicOperation                                      = VkLogicOp;

    using VulkanComponentMapping                                    = VkComponentMapping;

    using VulkanImageViewCreateInfo                                 = VkImageViewCreateInfo;

    using VulkanImageView                                           = VkImageView;
    using VulkanImageViewType                                       = VkImageViewType;
    using VulkanComponentSwizzle                                    = VkComponentSwizzle;

    using VulkanShaderModule                                        = VkShaderModule;
    using VulkanShaderModuleCreateInfo                              = VkShaderModuleCreateInfo;

    using VulkanPipelineShaderStageCreateInfo                       = VkPipelineShaderStageCreateInfo;
    using VulkanShaderStageFlagBits                                 = VkShaderStageFlagBits;

    using VulkanPipelineVertexInputStateCreateInfo                  = VkPipelineVertexInputStateCreateInfo;
    using VulkanPipelineInputAssemblyStateCreateInfo                = VkPipelineInputAssemblyStateCreateInfo;
    using VulkanViewport                                            = VkViewport;
    using VulkanRectangle2D                                         = VkRect2D;
    using VulkanPipelineViewportStateCreateInfo                     = VkPipelineViewportStateCreateInfo;
    using VulkanPipelineRasterizationStateCreateInfo                = VkPipelineRasterizationStateCreateInfo;
    using VulkanPipelineMultisampleStateCreateInfo                  = VkPipelineMultisampleStateCreateInfo;
    using VulkanPipelineColorBlendAttachmentState                   = VkPipelineColorBlendAttachmentState;
    using VulkanPipelineColorBlendStateCreateInfo                   = VkPipelineColorBlendStateCreateInfo;
    using VulkanDynamicState                                        = VkDynamicState;
    using VulkanPipelineDynamicStateCreateInfo                      = VkPipelineDynamicStateCreateInfo;
    using VulkanPipelineLayout                                      = VkPipelineLayout;
    using VulkanPipelineLayoutCreateInfo                            = VkPipelineLayoutCreateInfo;
    using VulkanPipelineDepthStencilStateCreateInfo                 = VkPipelineDepthStencilStateCreateInfo;
    using VulkanPipelineDepthStencilStateCreateFlags                = VkPipelineDepthStencilStateCreateFlags;

    using VulkanAttachmentDescription                               = VkAttachmentDescription;
    using VulkanAttachmentReference                                 = VkAttachmentReference;
    using VulkanSubpassDescription                                  = VkSubpassDescription;
    using VulkanRenderPass                                          = VkRenderPass;
    using VulkanRenderPassCreateInfo                                = VkRenderPassCreateInfo;

    using VulkanGraphicsPipelineCreateInfo                          = VkGraphicsPipelineCreateInfo;
    using VulkanGraphicsPipeline                                    = VkPipeline;

    using VulkanFrameBufferCreateInfo                               = VkFramebufferCreateInfo;
    using VulkanFrameBuffer                                         = VkFramebuffer;

    using VulkanCommandPool                                         = VkCommandPool;
    using VulkanCommandPoolCreateInfo                               = VkCommandPoolCreateInfo;
    using VulkanCommandBuffer                                       = VkCommandBuffer;
    using VulkanCommandBufferAllocateInfo                           = VkCommandBufferAllocateInfo;
    using VulkanCommandBufferBeginInfo                              = VkCommandBufferBeginInfo;
    using VulkanRenderPassBeginInfo                                 = VkRenderPassBeginInfo;
    using VulkanClearValue                                          = VkClearValue;
    using VulkanCommandBufferLevel                                  = VkCommandBufferLevel;

    using VulkanSemaphore                                           = VkSemaphore;
    using VulkanSemaphoreCreateInfo                                 = VkSemaphoreCreateInfo;
    using VulkanFence                                               = VkFence;
    using VulkanFenceCreateInfo                                     = VkFenceCreateInfo;
    using VulkanFenceCreateFlags                                    = VkFenceCreateFlags;
    using VulkanFenceCreateFlagBits                                 = VkFenceCreateFlagBits;
    using VulkanPipelineStageFlags                                  = VkPipelineStageFlags;
    using VulkanPipelineStageFlagBits                               = VkPipelineStageFlagBits;
    using VulkanSubmitInfo                                          = VkSubmitInfo;

    using VulkanSubpassDependency                                   = VkSubpassDependency;
    using VulkanPresentInfoKhronos                                  = VkPresentInfoKHR;

    using VulkanVertexInputBindingDescription                       = VkVertexInputBindingDescription;
    using VulkanVertexInputAttributeDescription                     = VkVertexInputAttributeDescription;
    using VulkanVertexInputRate                                     = VkVertexInputRate;
    using VulkanBufferCreateInfo                                    = VkBufferCreateInfo;
    using VulkanBuffer                                              = VkBuffer;
    using VulkanSharingMode                                         = VkSharingMode;
    using VulkanBufferUsageFlags                                    = VkBufferUsageFlags;
    using VulkanBufferUsageFlagBits                                 = VkBufferUsageFlagBits;

    using VulkanMemoryRequirements                                  = VkMemoryRequirements;
    using VulkanPhysicalDeviceMemoryProperties                      = VkPhysicalDeviceMemoryProperties;
    using VulkanMemoryAllocateInfo                                  = VkMemoryAllocateInfo;
    using VulkanDeviceMemory                                        = VkDeviceMemory;
    using VulkanMemoryPropertyFlags                                 = VkMemoryPropertyFlags;
    using VulkanMemoryPropertyFlagBits                              = VkMemoryPropertyFlagBits;
    using VulkanDeviceSize                                          = VkDeviceSize;

    using VulkanBlendOperation                                      = VkBlendOp;
    using VulkanBlendFactor                                         = VkBlendFactor;
    using VulkanAccessFlagBits                                      = VkAccessFlagBits;
    using VulkanAccessFlags                                         = VkAccessFlags;
    using VulkanCommandBufferUsageFlagBits                          = VkCommandBufferUsageFlagBits;
    using VulkanBufferCopy                                          = VkBufferCopy;
    using VulkanIndexType                                           = VkIndexType;

    using VulkanDescriptorSetLayoutBinding                          = VkDescriptorSetLayoutBinding;
    using VulkanDescriptorSetLayout                                 = VkDescriptorSetLayout;
    using VulkanDescriptorSetLayoutCreateInfo                       = VkDescriptorSetLayoutCreateInfo;
    using VulkanDescriptorType                                      = VkDescriptorType;

    using VulkanDescriptorPool                                      = VkDescriptorPool;
    using VulkanDescriptorPoolCreateInfo                            = VkDescriptorPoolCreateInfo;
    using VulkanDescriptorPoolCreateFlags         __CDS_MaybeUnused = VkDescriptorPoolCreateFlags;
    using VulkanDescriptorPoolCreateFlagBits      __CDS_MaybeUnused = VkDescriptorPoolCreateFlagBits;
    using VulkanDescriptorPoolSize                                  = VkDescriptorPoolSize;

    using VulkanDescriptorSetAllocateInfo                           = VkDescriptorSetAllocateInfo;
    using VulkanDescriptorSet                                       = VkDescriptorSet;
    using VulkanDescriptorBufferInfo                                = VkDescriptorBufferInfo;
    using VulkanCopyDescriptorSet                 __CDS_MaybeUnused = VkCopyDescriptorSet;
    using VulkanWriteDescriptorSet                                  = VkWriteDescriptorSet;

    using VulkanImageCreateInfo                                     = VkImageCreateInfo;
    using VulkanImageType                                           = VkImageType;
    using VulkanImageLayout                                         = VkImageLayout;
    using VulkanImageUsageFlagBits                                  = VkImageUsageFlagBits;
    using VulkanImageUsageFlags                                     = VkImageUsageFlags;
    using VulkanSampleCountFlagBits                                 = VkSampleCountFlagBits;
    using VulkanSampleCountFlags                  __CDS_MaybeUnused = VkSampleCountFlags;

    using VulkanImageMemoryBarrier                                  = VkImageMemoryBarrier;
    using VulkanImageSubresourceRange                               = VkImageSubresourceRange;
    using VulkanImageAspectFlags                                    = VkImageAspectFlags;
    using VulkanImageAspectFlagBits                                 = VkImageAspectFlagBits;
    using VulkanBufferImageCopy                                     = VkBufferImageCopy;
    using VulkanImageSubresourceLayers                              = VkImageSubresourceLayers;

    using VulkanImageTiling                                         = VkImageTiling;

    using VulkanSamplerCreateInfo                                   = VkSamplerCreateInfo;
    using VulkanSampler                                             = VkSampler;
    using VulkanFilter                                              = VkFilter;
    using VulkanSamplerMipmapMode                                   = VkSamplerMipmapMode;
    using VulkanSamplerAddressMode                                  = VkSamplerAddressMode;
    using VulkanCompareOp                                           = VkCompareOp;
    using VulkanBorderColor                                         = VkBorderColor;
    using VulkanDescriptorImageInfo                                 = VkDescriptorImageInfo;

    using VulkanFormatFeatureFlags                                  = VkFormatFeatureFlags;
    using VulkanFormatFeatureFlagBits                               = VkFormatFeatureFlagBits;
    using VulkanFormatProperties                                    = VkFormatProperties;
    using VulkanAttachmentDescriptionFlags                          = VkAttachmentDescriptionFlags;
    using VulkanAttachmentLoadOp                                    = VkAttachmentLoadOp;
    using VulkanAttachmentStoreOp                                   = VkAttachmentStoreOp;

    using VulkanSubpassDescriptionFlags                             = VkSubpassDescriptionFlags;
    using VulkanSubpassDescriptionFlagBits        __CDS_MaybeUnused = VkSubpassDescriptionFlagBits;
    using VulkanPipelineBindPoint                                   = VkPipelineBindPoint;
    using VulkanStencilOpState                                      = VkStencilOpState;
    using VulkanStencilOp                                           = VkStencilOp;

    constexpr VulkanFlags VULKAN_NULL_FLAGS = 0U;

}

#if defined(ENGINE_OS_WINDOWS_32_64)

namespace engine {

    using VulkanSurfaceCreateInfoKhronos                            = VkWin32SurfaceCreateInfoKHR;

}

extern engine :: VulkanResult ( * vkCreateSurfaceKhronos) (
        engine :: VulkanInstance,
        engine :: VulkanSurfaceCreateInfoKhronos const *,
        engine :: VulkanAllocationCallbacks const *,
        engine :: VulkanSurfaceKhronos *
);

#elif defined(ENGINE_OS_LINUX)

namespace engine {

    using VulkanSurfaceCreateInfoKhronos                            = VkXcbSurfaceCreateInfoKHR;

}

extern engine :: VulkanResult ( * vkCreateSurfaceKhronos ) (
        engine :: VulkanInstance,
        engine :: VulkanSurfaceCreateInfoKhronos const *,
        engine :: VulkanAllocationCallbacks const *,
        engine :: VulkanSurfaceKhronos *
);

#elif defined(ENGINE_OS_MAC_OS_X)

#endif

#endif //ENG1_VULKANEXPLICITTYPES_H

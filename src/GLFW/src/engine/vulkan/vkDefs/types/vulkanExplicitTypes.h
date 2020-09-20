//
// Created by vladl on 05/08/2020.
//

#ifndef ENG1_VULKANEXPLICITTYPES_H
#define ENG1_VULKANEXPLICITTYPES_H

#include <engineVulkanPreproc.h>
typedef VkStructureType                             VulkanStructureType;

typedef VkSurfaceKHR                                VulkanSurfaceKhronos;

typedef VkFlags                                     VulkanFlags;
typedef VkQueueFlags                                VulkanQueueFlags;

typedef VkPhysicalDevice                            VulkanPhysicalDevice;
typedef VkPhysicalDeviceType                        VulkanPhysicalDeviceType;
typedef VkPhysicalDeviceProperties                  VulkanPhysicalDeviceProperties;
typedef VkPhysicalDeviceFeatures                    VulkanPhysicalDeviceFeatures;
typedef VkPhysicalDeviceSparseProperties            VulkanPhysicalDeviceSparseProperties;
typedef VkPhysicalDeviceLimits                      VulkanPhysicalDeviceLimits;
typedef VkPhysicalDeviceFeatures                    VulkanPhysicalDeviceFeatures;
typedef VkQueueFamilyProperties                     VulkanQueueFamilyProperties;
typedef VkDevice                                    VulkanDevice;
typedef VkQueue                                     VulkanQueue;

typedef VkDeviceQueueCreateInfo                     VulkanDeviceQueueCreateInfo;
typedef VkDeviceCreateInfo                          VulkanDeviceCreateInfo;

typedef VkBool32                                    VulkanBool32;

typedef VkInstance                                  VulkanInstance;
typedef VkApplicationInfo                           VulkanApplicationInfo;
typedef VkInstanceCreateInfo                        VulkanInstanceCreateInfo;

typedef VkResult                                    VulkanResult;

typedef VkExtensionProperties                       VulkanExtensionProperties;

typedef VkLayerProperties                           VulkanLayerProperties;


typedef const int8 *                                GLFWExtensionLiteral;
typedef const int8 **                               GLFWExtensionLiteralArray;


typedef VkDebugUtilsMessengerCreateInfoEXT          VulkanDebugMessengerCreateInfo;
typedef VkAllocationCallbacks                       VulkanAllocationCallbacks;
typedef VkDebugUtilsMessengerEXT                    VulkanDebugMessenger;

typedef VkDebugUtilsMessageSeverityFlagBitsEXT      VulkanDebugMessageSeverityFlagBits;
typedef VkDebugUtilsMessageSeverityFlagsEXT         VulkanDebugMessageSeverityFlags;

typedef VkDebugUtilsMessageTypeFlagBitsEXT          VulkanDebugMessageTypeFlagBits;
typedef VkDebugUtilsMessageTypeFlagsEXT             VulkanDebugMessageTypeFlags;

typedef VkDebugUtilsMessengerCallbackDataEXT        VulkanDebugMessengerCallbackData;
typedef VkDebugUtilsMessengerCallbackDataFlagsEXT   VulkanDebugMessengerCallbackDataFlags;

typedef VkFlags                                     VulkanFlags;

typedef VkSurfaceCapabilitiesKHR                    VulkanSurfaceCapabilitiesKhronos;
typedef VkSurfaceFormatKHR                          VulkanSurfaceFormatKhronos;
typedef VkPresentModeKHR                            VulkanPresentModeKhronos;
typedef VkExtent2D                                  VulkanExtent2D;
typedef VkExtent3D                                  VulkanExtent3D;
typedef VkOffset2D                                  VulkanOffset2D;
typedef VkOffset3D                                  VulkanOffset3D;
typedef VkSwapchainKHR                              VulkanSwapChainKhronos;
typedef VkSwapchainCreateInfoKHR                    VulkanSwapChainCreateInfoKhronos;
typedef VkImage                                     VulkanImage;
typedef VkFormat                                    VulkanFormat;

typedef VkImageViewCreateInfo                       VulkanImageViewCreateInfo;

typedef VkImageView                                 VulkanImageView;

typedef VkShaderModule                              VulkanShaderModule;
typedef VkShaderModuleCreateInfo                    VulkanShaderModuleCreateInfo;

typedef VkPipelineShaderStageCreateInfo             VulkanPipelineShaderStageCreateInfo;
typedef VkShaderStageFlagBits                       VulkanShaderStageFlagBits;

typedef VkPipelineVertexInputStateCreateInfo        VulkanPipelineVertexInputStateCreateInfo;
typedef VkPipelineInputAssemblyStateCreateInfo      VulkanPipelineInputAssemblyStateCreateInfo;
typedef VkViewport                                  VulkanViewport;
typedef VkRect2D                                    VulkanRectangle2D;
typedef VkPipelineViewportStateCreateInfo           VulkanPipelineViewportStateCreateInfo;
typedef VkPipelineRasterizationStateCreateInfo      VulkanPipelineRasterizationStateCreateInfo;
typedef VkPipelineMultisampleStateCreateInfo        VulkanPipelineMultisampleStateCreateInfo;
typedef VkPipelineColorBlendAttachmentState         VulkanPipelineColorBlendAttachmentState;
typedef VkPipelineColorBlendStateCreateInfo         VulkanPipelineColorBlendStateCreateInfo;
typedef VkDynamicState                              VulkanDynamicState;
typedef VkPipelineDynamicStateCreateInfo            VulkanPipelineDynamicStateCreateInfo;
typedef VkPipelineLayout                            VulkanPipelineLayout;
typedef VkPipelineLayoutCreateInfo                  VulkanPipelineLayoutCreateInfo;
typedef VkPipelineDepthStencilStateCreateInfo       VulkanPipelineDepthStencilStateCreateInfo;

typedef VkAttachmentDescription                     VulkanAttachmentDescription;
typedef VkAttachmentReference                       VulkanAttachmentReference;
typedef VkSubpassDescription                        VulkanSubpassDescription;
typedef VkRenderPass                                VulkanRenderPass;
typedef VkRenderPassCreateInfo                      VulkanRenderPassCreateInfo;

typedef VkGraphicsPipelineCreateInfo                VulkanGraphicsPipelineCreateInfo;
typedef VkPipeline                                  VulkanGraphicsPipeline;

typedef VkFramebufferCreateInfo                     VulkanFrameBufferCreateInfo;
typedef VkFramebuffer                               VulkanFrameBuffer;

typedef VkCommandPool                               VulkanCommandPool;
typedef VkCommandPoolCreateInfo                     VulkanCommandPoolCreateInfo;
typedef VkCommandBuffer                             VulkanCommandBuffer;
typedef VkCommandBufferAllocateInfo                 VulkanCommandBufferAllocateInfo;
typedef VkCommandBufferBeginInfo                    VulkanCommandBufferBeginInfo;
typedef VkRenderPassBeginInfo                       VulkanRenderPassBeginInfo;
typedef VkClearValue                                VulkanClearValue;
typedef VkCommandBufferLevel                        VulkanCommandBufferLevel;

typedef VkSemaphore                                 VulkanSemaphore;
typedef VkSemaphoreCreateInfo                       VulkanSemaphoreCreateInfo;
typedef VkFence                                     VulkanFence;
typedef VkFenceCreateInfo                           VulkanFenceCreateInfo;
typedef VkFenceCreateFlags                          VulkanFenceCreateFlags;
typedef VkFenceCreateFlagBits                       VulkanFenceCreateFlagBits;
typedef VkPipelineStageFlags                        VulkanPipelineStageFlags;
typedef VkPipelineStageFlagBits                     VulkanPipelineStageFlagBits;
typedef VkSubmitInfo                                VulkanSubmitInfo;

typedef VkSubpassDependency                         VulkanSubpassDependency;
typedef VkPresentInfoKHR                            VulkanPresentInfoKhronos;

typedef VkVertexInputBindingDescription             VulkanVertexInputBindingDescription;
typedef VkVertexInputAttributeDescription           VulkanVertexInputAttributeDescription;
typedef VkVertexInputRate                           VulkanVertexInputRate;
typedef VkBufferCreateInfo                          VulkanBufferCreateInfo;
typedef VkBuffer                                    VulkanBuffer;
typedef VkSharingMode                               VulkanSharingMode;
typedef VkBufferUsageFlags                          VulkanBufferUsageFlags;
typedef VkBufferUsageFlagBits                       VulkanBufferUsageFlagBits;

typedef VkMemoryRequirements                        VulkanMemoryRequirements;
typedef VkPhysicalDeviceMemoryProperties            VulkanPhysicalDeviceMemoryProperties;
typedef VkMemoryAllocateInfo                        VulkanMemoryAllocateInfo;
typedef VkDeviceMemory                              VulkanDeviceMemory;
typedef VkMemoryPropertyFlags                       VulkanMemoryPropertyFlags;
typedef VkMemoryPropertyFlagBits                    VulkanMemoryPropertyFlagBits;
typedef VkDeviceSize                                VulkanDeviceSize;

typedef VkBlendOp                                   VulkanBlendOperation;
typedef VkBlendFactor                               VulkanBlendFactor;
typedef VkAccessFlagBits                            VulkanAccessFlagBits;
typedef VkAccessFlags                               VulkanAccessFlags;
typedef VkCommandBufferUsageFlagBits                VulkanCommandBufferUsageFlagBits;
typedef VkBufferCopy                                VulkanBufferCopy;
typedef VkIndexType                                 VulkanIndexType;

typedef VkDescriptorSetLayoutBinding                VulkanDescriptorSetLayoutBinding;
typedef VkDescriptorSetLayout                       VulkanDescriptorSetLayout;
typedef VkDescriptorSetLayoutCreateInfo             VulkanDescriptorSetLayoutCreateInfo;
typedef VkDescriptorType                            VulkanDescriptorType;

typedef VkDescriptorPool                            VulkanDescriptorPool;
typedef VkDescriptorPoolCreateInfo                  VulkanDescriptorPoolCreateInfo;
typedef VkDescriptorPoolCreateFlags                 VulkanDescriptorPoolCreateFlags;
typedef VkDescriptorPoolCreateFlagBits              VulkanDescriptorPoolCreateFlagBits;
typedef VkDescriptorPoolSize                        VulkanDescriptorPoolSize;

typedef VkDescriptorSetAllocateInfo                 VulkanDescriptorSetAllocateInfo;
typedef VkDescriptorSet                             VulkanDescriptorSet;
typedef VkDescriptorBufferInfo                      VulkanDescriptorBufferInfo;
typedef VkCopyDescriptorSet                         VulkanCopyDescriptorSet;
typedef VkWriteDescriptorSet                        VulkanWriteDescriptorSet;

typedef VkImageCreateInfo                           VulkanImageCreateInfo;
typedef VkImageType                                 VulkanImageType;
typedef VkImageLayout                               VulkanImageLayout;
typedef VkImageUsageFlagBits                        VulkanImageUsageFlagBits;
typedef VkImageUsageFlags                           VulkanImageUsageFlags;
typedef VkSampleCountFlagBits                       VulkanSampleCountFlagBits;
typedef VkSampleCountFlags                          VulkanSampleCountFlags;

typedef VkImageMemoryBarrier                        VulkanImageMemoryBarrier;
typedef VkImageSubresourceRange                     VulkanImageSubresourceRange;
typedef VkImageAspectFlags                          VulkanImageAspectFlags;
typedef VkImageAspectFlagBits                       VulkanImageAspectFlagBits;
typedef VkBufferImageCopy                           VulkanBufferImageCopy;
typedef VkImageSubresourceLayers                    VulkanImageSubresourceLayers;

typedef VkImageTiling                               VulkanImageTiling;

typedef VkSamplerCreateInfo                         VulkanSamplerCreateInfo;
typedef VkSampler                                   VulkanSampler;
typedef VkFilter                                    VulkanFilter;
typedef VkSamplerMipmapMode                         VulkanSamplerMipmapMode;
typedef VkSamplerAddressMode                        VulkanSamplerAddressMode;
typedef VkCompareOp                                 VulkanCompareOp;
typedef VkBorderColor                               VulkanBorderColor;
typedef VkDescriptorImageInfo                       VulkanDescriptorImageInfo;

constexpr VulkanFlags VULKAN_NULL_FLAGS = 0;

#if defined(ENGINE_OS_WINDOWS_32_64)

typedef VkWin32SurfaceCreateInfoKHR                 VulkanSurfaceCreateInfoKhronos;

extern VulkanResult (* vkCreateSurfaceKhronos) (VulkanInstance, const VulkanSurfaceCreateInfoKhronos *, const VkAllocationCallbacks *, VulkanSurfaceKhronos *);

#elif defined(ENGINE_OS_LINUX)

typedef VkXcbSurfaceCreateInfoKHR                   VulkanSurfaceCreateInfoKhronos;

extern VulkanResult (* vkCreateSurfaceKhronos ) (VulkanInstance, const VulkanSurfaceCreateInfoKhronos *, const VkAllocationCallbacks *, VulkanSurfaceKhronos *);

#elif defined(ENGINE_OS_MAC_OS_X)

#endif

#endif //ENG1_VULKANEXPLICITTYPES_H

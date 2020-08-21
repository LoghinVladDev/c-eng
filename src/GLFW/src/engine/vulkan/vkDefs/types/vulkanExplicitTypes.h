//
// Created by vladl on 05/08/2020.
//

#ifndef ENG1_VULKANEXPLICITTYPES_H
#define ENG1_VULKANEXPLICITTYPES_H

#include <engineVulkanPreproc.h>

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
typedef VkPipelineStageFlags                        VulkanPipelineStageFlags;
typedef VkSubmitInfo                                VulkanSubmitInfo;

typedef VkSubpassDependency                         VulkanSubpassDependency;
typedef VkPresentInfoKHR                            VulkanPresentInfoKhronos;


#if defined(ENGINE_OS_WINDOWS_32_64)

typedef VkWin32SurfaceCreateInfoKHR                 VulkanSurfaceCreateInfoKhronos;

extern VulkanResult (* vkCreateSurfaceKhronos) (VulkanInstance, const VulkanSurfaceCreateInfoKhronos *, const VkAllocationCallbacks *, VulkanSurfaceKhronos *);

#elif defined(ENGINE_OS_LINUX)
#elif defined(ENGINE_OS_MAC_OS_X)
#endif

#endif //ENG1_VULKANEXPLICITTYPES_H

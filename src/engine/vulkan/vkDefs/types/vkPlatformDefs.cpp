        //
// Created by Vlad on 12/08/2020.
//

#include <vkDefs/types/vulkanExplicitTypes.h>

/// address of the surface creation for platform independence
#if defined(ENGINE_OS_WINDOWS_32_64)
VulkanResult (* vkCreateSurfaceKhronos) (VulkanInstance, const VulkanSurfaceCreateInfoKhronos *, const VkAllocationCallbacks *, VulkanSurfaceKhronos *) = vkCreateWin32SurfaceKHR;
#elif defined(ENGINE_OS_LINUX)
VulkanResult (* vkCreateSurfaceKhronos) (VulkanInstance, const VulkanSurfaceCreateInfoKhronos *, const VkAllocationCallbacks *, VulkanSurfaceKhronos *) = vkCreateXcbSurfaceKHR;
#elif defined(ENGINE_OS_MAC_OS_X)
#endif
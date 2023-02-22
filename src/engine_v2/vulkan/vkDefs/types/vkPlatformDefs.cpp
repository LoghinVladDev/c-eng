        //
// Created by Vlad on 12/08/2020.
//

#include <vkDefs/types/vulkanExplicitTypes.h>

/// address of the surface creation for platform independence
#if defined(ENGINE_OS_WINDOWS_32_64)

engine :: VulkanResult ( * vkCreateSurfaceKhronos ) (
        engine :: VulkanInstance,
        engine :: VulkanSurfaceCreateInfoKhronos const *,
        engine :: VulkanAllocationCallbacks const *,
        engine :: VulkanSurfaceKhronos *
) = & vkCreateWin32SurfaceKHR;

#elif defined(ENGINE_OS_LINUX)

engine :: VulkanResult ( * vkCreateSurfaceKhronos ) (
        engine :: VulkanInstance,
        engine :: VulkanSurfaceCreateInfoKhronos const *,
        engine :: VulkanAllocationCallbacks const *,
        engine :: VulkanSurfaceKhronos *
) = & vkCreateXcbSurfaceKHR;

#elif defined(ENGINE_OS_MAC_OS_X)
#endif
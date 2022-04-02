//
// Created by loghin on 28.12.2021.
//

#ifndef __C_ENG_VULKAN_API_APPLE_EXTENSION_DETAILS_HPP__
#define __C_ENG_VULKAN_API_APPLE_EXTENSION_DETAILS_HPP__


#define __C_ENG_VULKAN_API_EXTENSION_APPLE_MOLTEN_VULKAN_IOS_SURFACE_AVAILABLE false
#define __C_ENG_VULKAN_API_EXTENSION_APPLE_MOLTEN_VULKAN_MACOS_SURFACE_AVAILABLE false

#if !defined(__C_ENG_VULKAN_ALL_APPLE_EXTENSIONS_DISABLED)

#if defined(VK_MVK_ios_surface)

#undef __C_ENG_VULKAN_API_EXTENSION_APPLE_MOLTEN_VULKAN_IOS_SURFACE_AVAILABLE
#define __C_ENG_VULKAN_API_EXTENSION_APPLE_MOLTEN_VULKAN_IOS_SURFACE_AVAILABLE true

#endif


#if defined(VK_MVK_macos_surface)

#undef __C_ENG_VULKAN_API_EXTENSION_APPLE_MOLTEN_VULKAN_MACOS_SURFACE_AVAILABLE
#define __C_ENG_VULKAN_API_EXTENSION_APPLE_MOLTEN_VULKAN_MACOS_SURFACE_AVAILABLE true

#endif

#endif


#endif //__C_ENG_VULKAN_API_APPLE_EXTENSION_DETAILS_HPP__

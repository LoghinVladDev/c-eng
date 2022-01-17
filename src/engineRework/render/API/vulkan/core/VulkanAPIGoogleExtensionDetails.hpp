//
// Created by loghin on 27.12.2021.
//

#ifndef __C_ENG_VULKAN_API_GOOGLE_EXTENSION_DETAILS_HPP__
#define __C_ENG_VULKAN_API_GOOGLE_EXTENSION_DETAILS_HPP__

#define __C_ENG_VULKAN_API_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_AVAILABLE false

#define __C_ENG_VULKAN_API_EXTENSION_GOOGLE_DISPLAY_TIMING_AVAILABLE false

#define __C_ENG_VULKAN_API_EXTENSION_GOOGLE_GAMES_PLATFORM_STREAM_DESCRIPTOR_SURFACE_AVAILABLE false
#define __C_ENG_VULKAN_API_EXTENSION_GOOGLE_GAMES_PLATFORM_FRAME_TOKEN_AVAILABLE false

#define __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_BUFFER_COLLECTION_AVAILABLE false
#define __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_MEMORY_AVAILABLE false
#define __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_SEMAPHORE_AVAILABLE false
#define __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_IMAGEPIPE_SURFACE_AVAILABLE false


#if defined(VK_GGP_stream_descriptor_surface)

#undef __C_ENG_VULKAN_API_EXTENSION_GOOGLE_GAMES_PLATFORM_STREAM_DESCRIPTOR_SURFACE_AVAILABLE
#define __C_ENG_VULKAN_API_EXTENSION_GOOGLE_GAMES_PLATFORM_STREAM_DESCRIPTOR_SURFACE_AVAILABLE true

#endif


#if defined(VK_GGP_frame_token)

#undef __C_ENG_VULKAN_API_EXTENSION_GOOGLE_GAMES_PLATFORM_FRAME_TOKEN_AVAILABLE
#define __C_ENG_VULKAN_API_EXTENSION_GOOGLE_GAMES_PLATFORM_FRAME_TOKEN_AVAILABLE true

#endif


#if defined(VK_GOOGLE_display_timing)

#undef __C_ENG_VULKAN_API_EXTENSION_GOOGLE_DISPLAY_TIMING_AVAILABLE
#define __C_ENG_VULKAN_API_EXTENSION_GOOGLE_DISPLAY_TIMING_AVAILABLE true

#endif


#if defined(VK_ANDROID_external_memory_android_hardware_buffer)

#undef __C_ENG_VULKAN_API_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_AVAILABLE
#define __C_ENG_VULKAN_API_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_AVAILABLE true

#endif


#if defined(VK_FUCHSIA_imagepipe_surface)

#undef __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_IMAGEPIPE_SURFACE_AVAILABLE
#define __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_IMAGEPIPE_SURFACE_AVAILABLE true

#endif


#if defined(VK_FUCHSIA_buffer_collection)

#undef __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_BUFFER_COLLECTION_AVAILABLE
#define __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_BUFFER_COLLECTION_AVAILABLE false

#endif


#if defined(VK_FUCHSIA_external_memory)

#undef __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_MEMORY_AVAILABLE
#define __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_MEMORY_AVAILABLE false

#endif


#if defined(VK_FUCHSIA_external_semaphore)

#undef __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_SEMAPHORE_AVAILABLE
#define __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_SEMAPHORE_AVAILABLE false

#endif


#endif //__C_ENG_VULKAN_API_GOOGLE_EXTENSION_DETAILS_HPP__

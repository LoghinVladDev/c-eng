//
// Created by loghin on 27.12.2021.
//

#ifndef __C_ENG_VULKANAPIDETAILS_HPP
#define __C_ENG_VULKANAPIDETAILS_HPP


#define __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED false

#if defined ( VK_ENABLE_BETA_EXTENSIONS )

#undef __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED
#define __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED true

#endif


#define __C_ENG_VULKAN_API_AVAILABLE false
#define __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE false
#define __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE false
#define __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE false


#if defined ( VK_VERSION_1_0 )

#undef  __C_ENG_VULKAN_API_AVAILABLE
#define __C_ENG_VULKAN_API_AVAILABLE true

#undef  __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE true

#endif


#if defined ( VK_VERSION_1_1 )

#undef  __C_ENG_VULKAN_API_AVAILABLE
#define __C_ENG_VULKAN_API_AVAILABLE true

#undef  __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE true

#undef  __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE true

#endif


#if defined ( VK_VERSION_1_2 )

#undef  __C_ENG_VULKAN_API_AVAILABLE
#define __C_ENG_VULKAN_API_AVAILABLE true

#undef  __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE true

#undef  __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE true

#undef  __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
#define __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE true

#endif


#endif //__C_ENG_VULKANAPIDETAILS_HPP

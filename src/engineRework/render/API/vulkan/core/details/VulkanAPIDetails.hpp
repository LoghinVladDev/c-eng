//
// Created by loghin on 27.12.2021.
//

#ifndef __C_ENG_VULKAN_API_DETAILS_HPP__
#define __C_ENG_VULKAN_API_DETAILS_HPP__


#define __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED false

#if defined ( VK_ENABLE_BETA_EXTENSIONS )

#undef __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED
#define __C_ENG_VULKAN_BETA_EXTENSIONS_ENABLED true

#endif


#define __C_ENG_VULKAN_API_AVAILABLE false
#define __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE false
#define __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE false
#define __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE false
#define __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE false


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


#if defined ( VK_VERSION_1_3 )

#undef  __C_ENG_VULKAN_API_AVAILABLE
#define __C_ENG_VULKAN_API_AVAILABLE true

#undef  __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE true

#undef  __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
#define __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE true

#undef  __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
#define __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE true

#undef  __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
#define __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE true

#endif


#include <details/VulkanAPIExtensionDetails.hpp>
#include <details/VulkanAPIKhronosExtensionDetails.hpp>
#include <details/VulkanAPIAMDExtensionDetails.hpp>
#include <details/VulkanAPINVidiaExtensionDetails.hpp>
#include <details/VulkanAPIGoogleExtensionDetails.hpp>
#include <details/VulkanAPIAppleExtensionDetails.hpp>
#include <details/VulkanAPIIntelExtensionDetails.hpp>
#include <details/VulkanAPIQualcommExtensionDetails.hpp>
#include <details/VulkanAPIARMExtensionDetails.hpp>
#include <details/VulkanAPIValveExtensionDetails.hpp>
#include <details/VulkanAPIHuaweiExtensionDetails.hpp>
#include <details/VulkanAPIBlackberryExtensionDetails.hpp>
#include <details/VulkanAPIPowerVRExtensionDetails.hpp>


#endif //__C_ENG_VULKAN_API_DETAILS_HPP__

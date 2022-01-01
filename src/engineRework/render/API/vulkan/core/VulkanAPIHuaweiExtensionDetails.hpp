//
// Created by loghin on 28.12.2021.
//

#ifndef __C_ENG_VULKANAPIHUAWEIEXTENSIONDETAILS_HPP
#define __C_ENG_VULKANAPIHUAWEIEXTENSIONDETAILS_HPP


#define __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE false
#define __C_ENG_VULKAN_API_EXTENSION_HUAWEI_INVOCATION_MASK_AVAILABLE false


#if defined(VK_HUAWEI_subpass_shading)

#undef __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE
#define __C_ENG_VULKAN_API_EXTENSION_HUAWEI_SUBPASS_SHADING_AVAILABLE true

#endif


#if defined(VK_HUAWEI_invocation_mask)

#undef __C_ENG_VULKAN_API_EXTENSION_HUAWEI_INVOCATION_MASK_AVAILABLE
#define __C_ENG_VULKAN_API_EXTENSION_HUAWEI_INVOCATION_MASK_AVAILABLE true

#endif


#endif //__C_ENG_VULKANAPIHUAWEIEXTENSIONDETAILS_HPP
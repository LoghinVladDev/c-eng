//
// Created by loghin on 28.12.2021.
//

#ifndef __C_ENG_VULKAN_API_VALVE_EXTENSION_DETAILS_HPP__
#define __C_ENG_VULKAN_API_VALVE_EXTENSION_DETAILS_HPP__


#define __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE false


#if !defined(__C_ENG_VULKAN_ALL_VALVE_EXTENSIONS_DISABLED)

#if defined(VK_VALVE_mutable_descriptor_type)

#undef __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE
#define __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE true

#endif

#endif


#endif //__C_ENG_VULKAN_API_VALVE_EXTENSION_DETAILS_HPP__
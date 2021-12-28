//
// Created by loghin on 28.12.2021.
//

#ifndef C_ENG_VULKANAPIINTELEXTENSIONDETAILS_HPP
#define C_ENG_VULKANAPIINTELEXTENSIONDETAILS_HPP


#define __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE false
#define __C_ENG_VULKAN_API_EXTENSION_INTEL_SHADER_INTEGER_FUNCTIONS_AVAILABLE false


#if defined(VK_INTEL_performance_query)

#undef __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
#define __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE true

#endif


#if defined(VK_INTEL_shader_integer_functions2)

#undef __C_ENG_VULKAN_API_EXTENSION_INTEL_SHADER_INTEGER_FUNCTIONS_AVAILABLE
#define __C_ENG_VULKAN_API_EXTENSION_INTEL_SHADER_INTEGER_FUNCTIONS_AVAILABLE true

#endif


#endif //C_ENG_VULKANAPIINTELEXTENSIONDETAILS_HPP

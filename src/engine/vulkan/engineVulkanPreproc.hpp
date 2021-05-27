//
// Created by vladl on 05/08/2020.
//

#ifndef ENG1_ENGINEVULKANPREPROC_HPP
#define ENG1_ENGINEVULKANPREPROC_HPP

#include <vkDefs/vkPlatformDefs.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#define GLM_FORCE_RADIANS
#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#include <glm/gtc/vec1.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

//#include <types.h>
#include <dataTypes.h>

#include <vkDefs/types/vulkanExplicitTypes.h>

#include <iostream>
#include <stb_image.h>

#define CDS_GLM

#endif //ENG1_ENGINEVULKANPREPROC_HPP

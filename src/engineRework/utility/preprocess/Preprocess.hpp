//
// Created by loghin on 18.12.2021.
//

#ifndef C_ENG_PREPROCESS_H
#define C_ENG_PREPROCESS_H

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

#ifndef C_ENG_DEFAULT_NAMING_PREFIX
#define C_ENG_DEFAULT_NAMING_PREFIX V
#endif

#include <Naming.hpp>
#include <Compiler.hpp>

#endif //C_ENG_PREPROCESS_H

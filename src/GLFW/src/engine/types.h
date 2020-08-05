
//
// Created by vladl on 09/07/2020.
//

#ifndef ENG1_TYPES_H
#define ENG1_TYPES_H

//#ifndef _glfw3_h_
//#include <GL/freeglut_std.h>
//#endif

#include <glm/glm.hpp>

#include <engStdDefs.h>

#ifndef ENG_VK
#ifndef _glfw3_h_
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#endif
#endif

#ifdef ENG_VK

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#endif

#ifndef ENG1_VECTOR_H
#include <obj/util/geom/Vector.h>
#endif

#ifndef ENG1_VECTOR4_H
#include <obj/util/geom/Vector4.h>
#endif

#include <string>
#include <cmath>

[[maybe_unused]] typedef unsigned char uint8;
[[maybe_unused]] typedef unsigned short uint16;
[[maybe_unused]] typedef unsigned int uint32;
[[maybe_unused]] typedef unsigned long int uint64;

[[maybe_unused]] typedef char int8;
[[maybe_unused]] typedef short int16;
[[maybe_unused]] typedef int int32;
[[maybe_unused]] typedef long long int64;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-signed-bitwise"

constexpr uint8 MODIFIER_ACTIVE_NONE                = (uint8) 0x00;
constexpr uint8 MODIFIER_ACTIVE_SHIFT               = (uint8) GLFW_MOD_SHIFT;
constexpr uint8 MODIFIER_ACTIVE_CTRL                = (uint8) GLFW_MOD_CONTROL;
constexpr uint8 MODIFIER_ACTIVE_ALT                 = (uint8) GLFW_MOD_ALT;
constexpr uint8 MODIFIER_ACTIVE_CTRL_SHIFT          = (uint8) GLFW_MOD_CONTROL  | (uint8) GLFW_MOD_SHIFT;
constexpr uint8 MODIFIER_ACTIVE_CTRL_ALT            = (uint8) GLFW_MOD_CONTROL  | (uint8) GLFW_MOD_ALT;
constexpr uint8 MODIFIER_ACTIVE_ALT_SHIFT           = (uint8) GLFW_MOD_ALT      | (uint8) GLFW_MOD_SHIFT;
constexpr uint8 MODIFIER_ACTIVE_CTRL_ALT_SHIFT      = ( (uint8) GLFW_MOD_CONTROL ) | ( (uint8) GLFW_MOD_ALT ) | ( (uint8) GLFW_MOD_SHIFT );

constexpr uint32 ENG_BUFFER_CLEAR_MASK              = (uint32) GL_COLOR_BUFFER_BIT | (uint32) GL_DEPTH_BUFFER_BIT;

#pragma clang diagnostic pop

#include "typesExtension/mats.h"
#include "typesExtension/lights.h"
#include "obj/util/struct/meshStructs.h"

#endif //ENG1_TYPES_H

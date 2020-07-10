#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-signed-bitwise"
//
// Created by vladl on 09/07/2020.
//

#ifndef ENG1_TYPES_H
#define ENG1_TYPES_H

//#ifndef _glfw3_h_
//#include <GL/freeglut_std.h>
//#endif

#ifndef _glfw3_h_
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#endif

#include <cmath>

[[maybe_unused]] typedef unsigned char uint8;
[[maybe_unused]] typedef unsigned short uint16;
[[maybe_unused]] typedef unsigned int uint32;
[[maybe_unused]] typedef unsigned long int uint64;

[[maybe_unused]] typedef char int8;
[[maybe_unused]] typedef short int16;
[[maybe_unused]] typedef int int32;
[[maybe_unused]] typedef long long int64;

#define KEY_ESCAPE 27

#ifndef UINT8_MAX
#define UINT8_MAX 0xFFU
#endif

#ifndef UINT8_MIN
#define UINT8_MIN 0x00U;
#endif

#ifdef ENG1_VECTOR_H
#ifndef nullvec
#define nullvec VectorF::nullVector
#endif
#endif

#ifndef _GL_MIN_VER
#define _GL_MIN_VER 0.0f
#endif

#ifndef _GL_MAX_VER
#define _GL_MAX_VER 2.0f
#endif

//[[maybe_unused]] constexpr uint16 KEY_A             = ( 'a' );
//[[maybe_unused]] constexpr uint16 KEY_D             = ( 'd' );
//[[maybe_unused]] constexpr uint16 KEY_S             = ( 's' );
//[[maybe_unused]] constexpr uint16 KEY_W             = ( 'w' );
//
//[[maybe_unused]] constexpr uint16 KEY_F1            = ( GLUT_KEY_F1         + UINT8_MAX );
//[[maybe_unused]] constexpr uint16 KEY_F2            = ( GLUT_KEY_F2         + UINT8_MAX );
//[[maybe_unused]] constexpr uint16 KEY_F3            = ( GLUT_KEY_F3         + UINT8_MAX );
//[[maybe_unused]] constexpr uint16 KEY_F4            = ( GLUT_KEY_F4         + UINT8_MAX );
//[[maybe_unused]] constexpr uint16 KEY_F5            = ( GLUT_KEY_F5         + UINT8_MAX );
//[[maybe_unused]] constexpr uint16 KEY_F6            = ( GLUT_KEY_F6         + UINT8_MAX );
//[[maybe_unused]] constexpr uint16 KEY_F7            = ( GLUT_KEY_F7         + UINT8_MAX );
//[[maybe_unused]] constexpr uint16 KEY_F8            = ( GLUT_KEY_F8         + UINT8_MAX );
//[[maybe_unused]] constexpr uint16 KEY_F9            = ( GLUT_KEY_F9         + UINT8_MAX );
//[[maybe_unused]] constexpr uint16 KEY_F10           = ( GLUT_KEY_F10        + UINT8_MAX );
//[[maybe_unused]] constexpr uint16 KEY_F11           = ( GLUT_KEY_F11        + UINT8_MAX );
//[[maybe_unused]] constexpr uint16 KEY_F12           = ( GLUT_KEY_F12        + UINT8_MAX );
//
//[[maybe_unused]] constexpr uint16 KEY_LEFT_ARROW    = ( GLUT_KEY_LEFT       + UINT8_MAX );
//[[maybe_unused]] constexpr uint16 KEY_RIGHT_ARROW   = ( GLUT_KEY_RIGHT      + UINT8_MAX );
//[[maybe_unused]] constexpr uint16 KEY_DOWN_ARROW    = ( GLUT_KEY_DOWN       + UINT8_MAX );
//[[maybe_unused]] constexpr uint16 KEY_UP_ARROW      = ( GLUT_KEY_UP         + UINT8_MAX );
//
//[[maybe_unused]] constexpr uint16 KEY_PAGE_UP       = ( GLUT_KEY_PAGE_UP    + UINT8_MAX );
//[[maybe_unused]] constexpr uint16 KEY_PAGE_DOWN     = ( GLUT_KEY_PAGE_DOWN  + UINT8_MAX );
//[[maybe_unused]] constexpr uint16 KEY_PAGE_HOME     = ( GLUT_KEY_HOME       + UINT8_MAX );
//[[maybe_unused]] constexpr uint16 KEY_PAGE_END      = ( GLUT_KEY_END        + UINT8_MAX );
//[[maybe_unused]] constexpr uint16 KEY_PAGE_INSERT   = ( GLUT_KEY_INSERT     + UINT8_MAX );
//
constexpr uint8 MODIFIER_ACTIVE_NONE                = (uint8) 0x00;
constexpr uint8 MODIFIER_ACTIVE_SHIFT               = (uint8) GLFW_MOD_SHIFT;
constexpr uint8 MODIFIER_ACTIVE_CTRL                = (uint8) GLFW_MOD_CONTROL;
constexpr uint8 MODIFIER_ACTIVE_ALT                 = (uint8) GLFW_MOD_ALT;
constexpr uint8 MODIFIER_ACTIVE_CTRL_SHIFT          = (uint8) GLFW_MOD_CONTROL  | (uint8) GLFW_MOD_SHIFT;
constexpr uint8 MODIFIER_ACTIVE_CTRL_ALT            = (uint8) GLFW_MOD_CONTROL  | (uint8) GLFW_MOD_ALT;
constexpr uint8 MODIFIER_ACTIVE_ALT_SHIFT           = (uint8) GLFW_MOD_ALT      | (uint8) GLFW_MOD_SHIFT;
constexpr uint8 MODIFIER_ACTIVE_CTRL_ALT_SHIFT      = ( (uint8) GLFW_MOD_CONTROL ) | ( (uint8) GLFW_MOD_ALT ) | ( (uint8) GLFW_MOD_SHIFT );

#pragma clang diagnostic pop

#endif //ENG1_TYPES_H

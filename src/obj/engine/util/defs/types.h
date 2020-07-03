//
// Created by Vlad on 03/07/2020.
//

#pragma once

#ifndef ENG1_TYPES_H
#define ENG1_TYPES_H

#include <GL/freeglut_std.h>

[[maybe_unused]] typedef unsigned char uint8;
[[maybe_unused]] typedef unsigned short uint16;
[[maybe_unused]] typedef unsigned int uint32;
[[maybe_unused]] typedef unsigned long int uint64;

#define KEY_ESCAPE 27

[[maybe_unused]] constexpr uint16 KEY_F1 = (GLUT_KEY_F1 + sizeof(uint8) );
[[maybe_unused]] constexpr uint16 KEY_F2 = (GLUT_KEY_F2 + sizeof(uint8) );
[[maybe_unused]] constexpr uint16 KEY_F3 = (GLUT_KEY_F3 + sizeof(uint8) );
[[maybe_unused]] constexpr uint16 KEY_F4 = (GLUT_KEY_F4 + sizeof(uint8) );
[[maybe_unused]] constexpr uint16 KEY_F5 = (GLUT_KEY_F5 + sizeof(uint8) );
[[maybe_unused]] constexpr uint16 KEY_F6 = (GLUT_KEY_F6 + sizeof(uint8) );
[[maybe_unused]] constexpr uint16 KEY_F7 = (GLUT_KEY_F7 + sizeof(uint8) );
[[maybe_unused]] constexpr uint16 KEY_F8 = (GLUT_KEY_F8 + sizeof(uint8) );
[[maybe_unused]] constexpr uint16 KEY_F9 = (GLUT_KEY_F9 + sizeof(uint8) );
[[maybe_unused]] constexpr uint16 KEY_F10 = (GLUT_KEY_F10 + sizeof(uint8) );
[[maybe_unused]] constexpr uint16 KEY_F11 = (GLUT_KEY_F11 + sizeof(uint8) );
[[maybe_unused]] constexpr uint16 KEY_F12 = (GLUT_KEY_F12 + sizeof(uint8) );

[[maybe_unused]] constexpr uint16 KEY_LEFT_ARROW = (GLUT_KEY_LEFT + sizeof(uint8) );
[[maybe_unused]] constexpr uint16 KEY_RIGHT_ARROW = (GLUT_KEY_RIGHT + sizeof(uint8) );
[[maybe_unused]] constexpr uint16 KEY_DOWN_ARROW = (GLUT_KEY_DOWN + sizeof(uint8) );
[[maybe_unused]] constexpr uint16 KEY_UP_ARROW = (GLUT_KEY_UP + sizeof(uint8) );

[[maybe_unused]] constexpr uint16 KEY_PAGE_UP = (GLUT_KEY_PAGE_UP + sizeof(uint8) );
[[maybe_unused]] constexpr uint16 KEY_PAGE_DOWN = (GLUT_KEY_PAGE_DOWN + sizeof(uint8) );
[[maybe_unused]] constexpr uint16 KEY_PAGE_HOME = (GLUT_KEY_HOME + sizeof(uint8) );
[[maybe_unused]] constexpr uint16 KEY_PAGE_END = (GLUT_KEY_END + sizeof(uint8) );
[[maybe_unused]] constexpr uint16 KEY_PAGE_INSERT = (GLUT_KEY_INSERT + sizeof(uint8) );

constexpr uint8 MODIFIER_ACTIVE_NONE             = (uint8) 0x00;
constexpr uint8 MODIFIER_ACTIVE_SHIFT            = (uint8) GLUT_ACTIVE_SHIFT;
constexpr uint8 MODIFIER_ACTIVE_CTRL             = (uint8) GLUT_ACTIVE_CTRL;
constexpr uint8 MODIFIER_ACTIVE_ALT              = (uint8) GLUT_ACTIVE_ALT;
constexpr uint8 MODIFIER_ACTIVE_CTRL_SHIFT       = (uint8) GLUT_ACTIVE_CTRL | GLUT_ACTIVE_SHIFT;
constexpr uint8 MODIFIER_ACTIVE_CTRL_ALT         = (uint8) GLUT_ACTIVE_CTRL | GLUT_ACTIVE_ALT;
constexpr uint8 MODIFIER_ACTIVE_ALT_SHIFT        = (uint8) GLUT_ACTIVE_ALT  | GLUT_ACTIVE_SHIFT;
constexpr uint8 MODIFIER_ACTIVE_CTRL_ALT_SHIFT   = (uint8) GLUT_ACTIVE_CTRL | GLUT_ACTIVE_ALT | GLUT_ACTIVE_SHIFT;

#endif //ENG1_TYPES_H

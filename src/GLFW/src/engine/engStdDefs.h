//
// Created by vladl on 04/08/2020.
//

#ifndef ENG1_ENGSTDDEFS_H
#define ENG1_ENGSTDDEFS_H

#define __WINDOW_INIT_FAIL_CODE 1
#define __GLAD_INIT_FAIL_CODE   2

#ifndef KEY_ESCAPE
#define KEY_ESCAPE 27
#endif

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
#define _GL_MIN_VER 3
#endif

#ifndef _GL_MAX_VER
#define _GL_MAX_VER 3
#endif

#ifndef __PROJ_PATHS__

[[maybe_unused]] constexpr const char* __PROJECT_PATH__ = "./../";                  // NOLINT(bugprone-reserved-identifier)
constexpr const char* __SHADERS_PATH__                  = "./../data/shaders/";     // NOLINT(bugprone-reserved-identifier)
constexpr const char* __TEXTURES_PATH__                 = "./../data/textures/";    // NOLINT(bugprone-reserved-identifier)

constexpr const char* __NO_PATH_GIVEN__                 = "./";                     // NOLINT(bugprone-reserved-identifier)
constexpr const char* __ASSETS_PATH__                   = "./../data/assets/";      // NOLINT(bugprone-reserved-identifier)


#define __PROJ_PATHS__
#endif

#ifndef ENG_SET_VERSION_LIMITATION
#define ENG_SET_VERSION_LIMITATION(_minVer,_maxVer) \
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, _minVer); \
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, _maxVer); \
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE)
#endif

#ifndef ENG_WINDOW_CREATE_WINDOW
#include <iostream>
#define ENG_WINDOW_CREATE_WINDOW(_windowPtr, _width, _height) \
    _windowPtr = glfwCreateWindow(_width, _height, "c-eng", nullptr, nullptr); \
    if(window == nullptr) {                                   \
        std::cout << "Window Init Fail\n";                    \
        glfwTerminate();                                      \
        exit(__WINDOW_INIT_FAIL_CODE);                        \
    }                                                           \
    glfwMakeContextCurrent(_windowPtr)
#endif

#ifndef ENG_WINDOW_SET_CALLBACKS
#define ENG_WINDOW_SET_CALLBACKS(_windowPtr, _fBufCB, _mouseCB, _scrCB) \
    glfwSetFramebufferSizeCallback(_windowPtr, _fBufCB);                \
    glfwSetCursorPosCallback(_windowPtr, _mouseCB);                     \
    glfwSetScrollCallback(_windowPtr, _scrCB);                          \
    glfwSetInputMode(_windowPtr, GLFW_CURSOR, GLFW_CURSOR_DISABLED)
#endif

/**
 * don't ask.
 */
#ifndef ENG_GLAD_INIT
#define ENG_GLAD_INIT() \
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){ \
        std::cout << "GLAD Init Fail\n";                     \
        exit(__GLAD_INIT_FAIL_CODE);                         \
    }                                                        \
    do{                                                     \
        break;                                              \
    } while(true)
#endif

#ifndef ENG_CLEAR_FRAME
#define ENG_CLEAR_FRAME() \
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f); \
    glClear(ENG_BUFFER_CLEAR_MASK)
#endif

#ifndef ENG_FINISH_FRAME
#define ENG_FINISH_FRAME(_windowPtr) \
    glfwSwapBuffers(_windowPtr); \
    glfwPollEvents()
#endif

#endif //ENG1_ENGSTDDEFS_H
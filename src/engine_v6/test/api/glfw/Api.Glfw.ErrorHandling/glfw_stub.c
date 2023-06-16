//
// Created by Vlad-Andrei Loghin on 16.06.23.
//

#include "GLFW/glfw3.h"

static int error = GLFW_NO_ERROR;
static inline char const * pMockMessage(int err) {
  switch (err) {
    case GLFW_NOT_INITIALIZED: return "testDesc1";
    case GLFW_NO_CURRENT_CONTEXT: return "testDesc2";
    case GLFW_INVALID_ENUM: return "testDesc3";
    case GLFW_INVALID_VALUE: return "testDesc4";
    case GLFW_OUT_OF_MEMORY: return "testDesc5";
    case GLFW_API_UNAVAILABLE: return "testDesc6";
    case GLFW_VERSION_UNAVAILABLE: return "testDesc7";
    case GLFW_PLATFORM_ERROR: return "testDesc8";
    case GLFW_FORMAT_UNAVAILABLE: return "testDesc9";
    default:                   return "";
  }
}

GLFWAPI int glfwGetError(char const** ppString) {
  *ppString = pMockMessage(error);
  return error;
}

GLFWAPI void glfwGetVersion(int* ma, int* mi, int* pa) {
  *ma = GLFW_VERSION_MAJOR;
  *mi = GLFW_VERSION_MINOR;
  *pa = GLFW_VERSION_REVISION;
}

GLFWerrorfun errcbk;
static inline void err(int errCode) {
  error = errCode;
  errcbk(errCode, pMockMessage(errCode));
}


GLFWAPI int glfwInit() {
  static int initCnt = 0;
  ++ initCnt;
  if (initCnt == 1) {
    return GLFW_TRUE;
  }

  if (initCnt == 2) {
    return GLFW_FALSE;
  }

  errcbk(GLFW_NO_ERROR, "invalid msg");
  return GLFW_TRUE;
}

GLFWAPI void glfwTerminate() {
  err(GLFW_NOT_INITIALIZED);
  err(GLFW_NO_CURRENT_CONTEXT);
  err(GLFW_INVALID_ENUM);
  err(GLFW_INVALID_VALUE);
  err(GLFW_OUT_OF_MEMORY);
  err(GLFW_API_UNAVAILABLE);
  err(GLFW_VERSION_UNAVAILABLE);
  err(GLFW_PLATFORM_ERROR);
  err(GLFW_FORMAT_UNAVAILABLE);
}

GLFWAPI GLFWerrorfun glfwSetErrorCallback(GLFWerrorfun cbk) {
  GLFWerrorfun o = errcbk;
  errcbk = cbk;
  return o;
}

static GLFWmonitorfun mfcbk = NULL;
GLFWAPI GLFWmonitorfun glfwSetMonitorCallback(GLFWmonitorfun f) {
  GLFWmonitorfun o = mfcbk;
  mfcbk = f;
  return o;
}

void simulateInvalid() {
  err(GLFW_NO_ERROR);
}

void mockMonitorCallback() {
  mfcbk(NULL, 0);
}


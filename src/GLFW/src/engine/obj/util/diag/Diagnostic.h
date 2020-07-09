//
// Created by vladl on 09/07/2020.
//

#ifndef ENG1_DIAGNOSTIC_H
#define ENG1_DIAGNOSTIC_H

#include "../../../enginePreprocessHeaders.h"
#include <cstdio>

typedef void (*DIAG_CALLBACK) (int, const char* );

namespace Engine {

    class Diagnostic {
    public:

        [[maybe_unused]] constexpr static bool DIAG_INIT_SUCCESS = GLFW_TRUE;
        [[maybe_unused]] constexpr static bool DIAG_INIT_FAIL = GLFW_FALSE;

        struct DiagnosticResultStructure {
            bool initializeResult{GLFW_FALSE};
        };
    private:
        static DiagnosticResultStructure diagStr;
    public:
        Diagnostic() = delete;

        [[maybe_unused]] static void initTest() noexcept {
            Diagnostic::diagStr.initializeResult = glfwInit();
        }

        [[maybe_unused]] static DiagnosticResultStructure getDiagnosticResult() {
            return Diagnostic::diagStr;
        }

        [[maybe_unused]] static void GLFWErrorCallback(int error, const char* description) {
            std::fprintf(stderr, "[Error] [Number : %d] Description : %s]\n", error, description);
        }
    private:
        static void (*_errorCallbackPtr) (int, const char*);
    public:
        [[maybe_unused]] static DIAG_CALLBACK getErrorCallbackDiagFunc() {
            return Diagnostic::_errorCallbackPtr;
        }
    };

}

#endif //ENG1_DIAGNOSTIC_H

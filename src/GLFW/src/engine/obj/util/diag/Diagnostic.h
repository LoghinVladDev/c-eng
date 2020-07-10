//
// Created by vladl on 09/07/2020.
//

#ifndef ENG1_DIAGNOSTIC_H
#define ENG1_DIAGNOSTIC_H

#include "../../../enginePreproc.h"
#include <cstdio>
#include <obj/util/event/KeyListener.h>

typedef void (*DIAG_CALLBACK) (int, const char* );

namespace engine {

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

        [[maybe_unused]] [[nodiscard]] static std::string modifierToString( engine::InputListener::KeyModifier keyListenerModifier ) noexcept  {
            switch ( keyListenerModifier ) {
                case InputListener::NONE            : return " KEY_MODIFIER : { none }";
                case InputListener::SHIFT           : return " KEY_MODIFIER : { shift }";
                case InputListener::CTRL            : return " KEY_MODIFIER : { control }";
                case InputListener::ALT             : return " KEY_MODIFIER : { alt }";
                case InputListener::CTRL_SHIFT      : return " KEY_MODIFIER : { control-shift }";
                case InputListener::CTRL_ALT        : return " KEY_MODIFIER : { control-alt }";
                case InputListener::ALT_SHIFT       : return " KEY_MODIFIER : { alt-shift }";
                case InputListener::CTRL_ALT_SHIFT  : return " KEY_MODIFIER : { control-alt-shift }";
                default                             : return " KEY_MODIFIER : { unknown }";
            }
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

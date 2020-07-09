//
// Created by vladl on 09/07/2020.
//

#include "Diagnostic.h"

Engine::Diagnostic::DiagnosticResultStructure Engine::Diagnostic::diagStr;
void (* Engine::Diagnostic::_errorCallbackPtr) (int, const char *) = Engine::Diagnostic::GLFWErrorCallback;

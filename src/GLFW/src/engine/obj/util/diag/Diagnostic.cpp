//
// Created by vladl on 09/07/2020.
//

#include "Diagnostic.h"
#include <obj/util/event/InputListener.h>

engine::Diagnostic::DiagnosticResultStructure engine::Diagnostic::diagStr;
void (* engine::Diagnostic::_errorCallbackPtr) (int, const char *) = engine::Diagnostic::GLFWErrorCallback;

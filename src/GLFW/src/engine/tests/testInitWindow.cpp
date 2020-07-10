//
// Created by vladl on 09/07/2020.
//

#include "../enginePreproc.h"
#include "../obj//util/diag//Diagnostic.h"

using namespace Engine;

int main(int argc, char **argv){
    Engine::Diagnostic::initTest();
    glfwSetErrorCallback(Engine::Diagnostic::getErrorCallbackDiagFunc());

    glfwTerminate();

    printf(
            "[GLFW Status : %s]\n",
            Engine::Diagnostic::getDiagnosticResult().initializeResult == Engine::Diagnostic::DIAG_INIT_SUCCESS
            ? "success" : "failure"
    );


}


//
// Created by vladl on 09/07/2020.
//
#include <enginePreprocessHeaders.h>
#include <obj/util/diag/Diagnostic.h>
#include <src/GLFW/src/engine/obj/window/Window.h>

//#ifndef __gl_h_
//#include <src/glfw_src/deps/glad/gl.h>
//#endif


using namespace Engine;

int main(int argc, char** argv) {
    if ( ! glfwInit() ) {
        std::fprintf(stderr, "init error\n");
        exit(1);
    }

    glfwSetErrorCallback( Diagnostic::GLFWErrorCallback );

    Window* window;

    try {
        window = new Window(1280, 720, 0, 0, "GLFW");
    }
    catch( WindowCreateNullException& except ){
        std::fprintf(stderr, "Engine Error : %s\n", except.what());
        exit(2);
    }

    window->grabFocus();

    gladLoadGLLoader( (GLADloadproc) glfwGetProcAddress );

    window->run( argc, argv );

    int width, height;

    while( ! window->willClose() ){
//        glfwGetFramebufferSize(window->getGLFWWindow(), &width, &height);
    }

    delete window;
}
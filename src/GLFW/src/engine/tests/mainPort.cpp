//
// Created by vladl on 09/07/2020.
//
#include <enginePreproc.h>
#include <obj/util/diag/Diagnostic.h>
#include <Engine.h>
#include <iostream>

//#ifndef __gl_h_
//#include <src/glfw_src/deps/glad/gl.h>
//#endif

#include <obj/util/event/KeyListener.h>

using namespace engine;

class DerivedKeyListener : public KeyListener{
    void keyPressed(int key, int scanCode, KeyListener::KeyModifier mods) noexcept override {
        fprintf(stdout, "[%lld Listener notified of press] [key : %d] [scanCode : %d] [mods : %s]\n", this, key, scanCode, Diagnostic::modifierToString(mods).c_str());
    }

    void keyReleased(int key, int scanCode, KeyListener::KeyModifier mods) noexcept override {
        fprintf(stdout, "[%lld Listener notified of release] [key : %d] [scanCode : %d] [mods : %s]\n", this, key, scanCode, Diagnostic::modifierToString(mods).c_str());
    }

    void keyHeld(int key, int scanCode, KeyListener::KeyModifier mods) noexcept override {
        fprintf(stdout, "[%lld Listener notified of hold] [key : %d] [scanCode : %d] [mods : %s]\n", this, key, scanCode, Diagnostic::modifierToString(mods).c_str());
    }
};

int main(int argc, char** argv) {
    if ( ! glfwInit() ) {
        std::fprintf(stderr, "init error\n");
        exit(1);
    }

    glfwSetErrorCallback( Diagnostic::GLFWErrorCallback );

    auto* eng = Engine::EngineBuilder()
            .withMainWindowResolution(1280, 720)
            .withMainWindowTitle("GLFWPort")
            .build();

    eng->getMainWindow()->enableRawMouseInput();
    eng->getMainWindow()->disableMouseCursor();

    eng->addKeyListener(new DerivedKeyListener);
    eng->addMouseListener(new MouseListener);

    eng->start(argc, argv);

    delete eng;

    return 0;

//    Window* window;

//    try {
//        window = new Window(1280, 720, 0, 0, "GLFW");
//    }
//    catch( WindowCreateNullException& except ){
//        std::fprintf(stderr, "Engine Error : %s\n", except.what());
//        exit(2);
//    }

//    std::cout << 0;

//    window->run( argc, argv );
//    window->grabFocus();
//    gladLoadGLLoader( (GLADloadproc) glfwGetProcAddress );
//
//    std::cout << 0;

//    int width, height;
//
//    float ratio;
//
//    while( ! window->willClose() ){
//        glfwGetFramebufferSize(window->getGLFWWindow(), &width, &height);
//        glViewport(0, 0, width, height);
//
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        glMatrixMode(GL_PROJECTION);
//        glLoadIdentity();
//        glColor3f( 0.5f, 0.5f, 0.5f );
//        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
//        glMatrixMode(GL_MODELVIEW);
//        glLoadIdentity();
//        glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
//        glBegin(GL_TRIANGLES);
//        glColor3f(1.f, 0.f, 0.f);
//        glVertex3f(-0.6f, -0.4f, 0.f);
//        glColor3f(0.f, 1.f, 0.f);
//        glVertex3f(0.6f, -0.4f, 0.f);
//        glColor3f(0.f, 0.f, 1.f);
//        glVertex3f(0.f, 0.6f, 0.f);
//        glEnd();
//        glfwSwapBuffers(window->getGLFWWindow());
//        glfwPollEvents();
//    }

//    delete window;
}
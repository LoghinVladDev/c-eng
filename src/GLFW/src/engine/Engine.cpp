//
// Created by vladl on 10/07/2020.
//

#include "Engine.h"
#include <obj/util/diag/Diagnostic.h>

engine::Engine *engine::Engine::_instance = nullptr;

engine::Engine::Engine() noexcept {
    this->_ptrToInputAxisStr = getInputAxisVar();
//    fprintf(stdout, "addr of str : %lld\n", this->_ptrToInputAxisStr);
}

[[maybe_unused]] [[nodiscard]] engine::Engine *engine::Engine::getInstance() noexcept {
    if( Engine::Engine::_instance == nullptr )
        Engine::Engine::_instance = new Engine();
    return Engine::Engine::_instance;
}

void engine::Engine::start(int argc, char **argv) noexcept {
    this->mainWindow->run(argc, argv);
    this->mainWindow->grabFocus();

    gladLoadGLLoader( (GLADloadproc) glfwGetProcAddress );

    while(!this->mainWindow->willClose()){
        this->update();
        this->render();
    }
}

engine::Engine::~Engine() noexcept {
    fprintf(stdout, "[Engine shutting down...]");
    delete this->mainWindow;

    glfwTerminate();
}

void engine::Engine::update() noexcept {

//    fprintf(stdout, "input axis : x = %d, y = %d\n", engine::Engine::getInstance()->getInputAxisStructure()->xAxis, engine::Engine::getInstance()->getInputAxisStructure()->yAxis);

}

void engine::Engine::render() noexcept {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

//    double ratio = (double)this->mainWindow->getViewportWidth() / this->mainWindow->getViewportHeight();
//
//    glLoadIdentity();
//    glColor3f( 0.5f, 0.5f, 0.5f );
//    glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
//    glBegin(GL_TRIANGLES);
//    glColor3f(1.f, 0.f, 0.f);
//    glVertex3f(-0.6f, -0.4f, 0.f);
//    glColor3f(0.f, 1.f, 0.f);
//    glVertex3f(0.6f, -0.4f, 0.f);
//    glColor3f(0.f, 0.f, 1.f);
//    glVertex3f(0.f, 0.6f, 0.f);
//    glEnd();

    glfwSwapBuffers(this->mainWindow->getGLFWWindow());
    glfwPollEvents();
//    glfwWaitEventsTimeout(0.7);
}

engine::Engine* engine::Engine::EngineBuilder::build() noexcept(false) {

    if (glfwInit() == engine::Diagnostic::DIAG_INIT_FAIL){
        throw EngineGLFWInitFailure();
    }

    glfwSetErrorCallback( Diagnostic::GLFWErrorCallback );

    Engine* instance = Engine::getInstance();

    try {
        instance->mainWindow = new Window(this->mainWindowResolution, this->mainWindowLocation, this->mainWindowTitle);
    } catch (WindowCreateNullException& exception) {
        std::fprintf(stderr, "[Window creation error : %s]\n", exception.what());
    }

    return instance;
}
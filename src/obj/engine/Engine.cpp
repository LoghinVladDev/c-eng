//
// Created by Vlad on 03/07/2020.
//

#include "Engine.h"
#include <time.h>

Engine* Engine::_instance = nullptr;

Engine::Engine() noexcept = default;

/**
 * might become problematic
 */
Engine::~Engine() noexcept {
    this->mainWindow.~Window();
}

[[maybe_unused]] void Engine::start(int argc, char** argv) noexcept {
    this->mainWindow.run(argc, argv);
}

[[maybe_unused]] inline Window& Engine::getMainWindow() noexcept {
    return this->mainWindow;
}

[[maybe_unused]] [[nodiscard]] inline Engine* Engine::getInstance() noexcept {
    if( Engine::_instance == nullptr )
        Engine::_instance = new Engine();
    return Engine::_instance;
}

void Engine::update() noexcept {
    for(GameObject* obj : Engine::getInstance()->getAllGameObjects()){
        obj->realUpdate();
    }

    Engine::render();
}

static VectorF colorsArr[100];
int someOtherCntVar = 0;

void drawSpheresBeta(){

//    std::cout << red << ' ' << green << ' ' << blue << '\n';
    glColor3f(colorsArr[someOtherCntVar].getX(),colorsArr[someOtherCntVar].getY(), colorsArr[someOtherCntVar++].getZ());

    glTranslatef(0.0f, 0.75f, 0.0f);
    glutSolidSphere(0.75f, 20, 20);
}

void Engine::render() noexcept {
    glClear( DEFAULT_CLEAR_MASK_FLAGS );
    glLoadIdentity();

    for(GameObject* obj : Engine::getInstance()->getAllGameObjects()) {
        obj->draw();
    }

    glColor3f( 0.9f, 0.9f, 0.9f );

    glBegin(GL_QUADS);
    glVertex3f( -100.0f, 0.0f, -100.0f );
    glVertex3f( -100.0f, 0.0f, 100.0f );
    glVertex3f( 100.0f, 0.0f, 100.0f );
    glVertex3f( 100.0f, 0.0f, -100.0f );
    glEnd();

    someOtherCntVar = 0;

    for(int i = -3; i < 3; i++)
        for(int j = -3; j < 3; j++){
            glPushMatrix();
            glTranslatef(i * 10.0f, 0, j * 10.0f);
            drawSpheresBeta();
            glPopMatrix();
        }

    glutSwapBuffers();
}

[[maybe_unused]] [[nodiscard]] std::list<GameObject *> &Engine::getAllGameObjects() noexcept {
    return this->_allGameObjects;
}

[[maybe_unused]] void Engine::addGameObject(GameObject * obj) noexcept {
    this->_allGameObjects.push_back(obj);
}

void Engine::renderOnce() noexcept {

    Engine::render();
}


Engine *Engine::EngineBuilder::build() noexcept {
    Engine* instance = Engine::getInstance();int someIndex = 0;

    for(int i = -3; i < 3; i++)
        for(int j = -3; j < 3; j++){
            float red = ( (float) ( rand() % 100 ) ) / 100.0f;
            float green = ( (float) ( rand() % 100 ) ) / 100.0f;
            float blue = ( (float) ( rand() % 100 ) ) / 100.0f;

            colorsArr[ someIndex++ ] = VectorF( red, green, blue );
        }

    instance->mainWindow.setSize(this->mainWindowResolution);
    instance->mainWindow.setPosition(this->mainWindowLocation);
    instance->mainWindow.setTitle(this->mainWindowTitle);

    instance->mainWindow.setDisplayFunctionCallback(Engine::renderOnce);
    instance->mainWindow.setRedrawFunctionCallback(Engine::update);

    return instance;
}

//
// Created by Vlad on 03/07/2020.
//
#include "Engine.h"
#include "util/obj/standardObj/Camera.h"

Engine* Engine::_instance = nullptr;

Engine::Engine() noexcept = default;

/**
 * might become problematic
 */
Engine::~Engine() noexcept {
    this->mainWindow.~Window();
}

void Engine::_sortObjectsByDrawPriority() noexcept {
    this->_allGameObjects.sort();
}

[[maybe_unused]] void Engine::start(int argc, char** argv) noexcept {
    this->_sortObjectsByDrawPriority();
    this->mainWindow.run(argc, argv);
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

void Engine::render() noexcept {
    Engine* instance = Engine::getInstance();

    glClear( DEFAULT_CLEAR_MASK_FLAGS );
    glLoadIdentity();

    instance->_activeCamera->realUpdate();

    glColor3f( 0.9f, 0.9f, 0.9f );
//
    glBegin(GL_QUADS);
    glVertex3f( -100.0f, 0.0f, -100.0f );
    glVertex3f( -100.0f, 0.0f, 100.0f );
    glVertex3f( 100.0f, 0.0f, 100.0f );
    glVertex3f( 100.0f, 0.0f, -100.0f );
    glEnd();

    for(GameObject* obj : Engine::getInstance()->getAllGameObjects()) {
        obj->draw();
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
    Engine* instance = Engine::getInstance();

    instance->mainWindow.setSize(this->mainWindowResolution);
    instance->mainWindow.setPosition(this->mainWindowLocation);
    instance->mainWindow.setTitle(this->mainWindowTitle);

    instance->mainWindow.setDisplayFunctionCallback(Engine::renderOnce);
    instance->mainWindow.setRedrawFunctionCallback(Engine::update);

    return instance;
}

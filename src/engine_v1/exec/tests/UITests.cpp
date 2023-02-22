//
// Created by vladl on 07/07/2020.
//

#include <ctime>
#include <iostream>
#include "src/obj/engine/Engine.h"
#include "src/obj/engine/util/obj/standardObj/Camera.h"
#include "src/obj/engine/util/obj/standardObj/Sphere.h"

class ACamera : public Camera{
private:
    int xOrigin = -1;
public:
    void keyPressed(uint16 keyCode) noexcept {
        switch ( keyCode ) {
            case KEY_W : case KEY_UP_ARROW :
                deltaMove = deltaMove + 0.5f;       break;
            case KEY_S : case KEY_DOWN_ARROW :
                deltaMove = deltaMove -0.5f;        break;
            default:
                break;
        }
    }

    void keyReleased(uint16 keyCode) noexcept {
//        std::cout << "released\n";
        switch ( keyCode ) {
            case KEY_W : case KEY_UP_ARROW :
                deltaMove = deltaMove - 0.5f;       break;
            case KEY_S : case KEY_DOWN_ARROW :
                deltaMove = deltaMove + 0.5f;        break;
            default:
                break;
        }
    }

    void mouseMove(int x,int y) noexcept {
        if(xOrigin == -1)
            xOrigin = x;
        this->deltaAngle = (float)(x - xOrigin) * 0.003f;

        xOrigin = x;
    }

    void mouseClick(uint16 button, uint16 state, int x, int y){

    }
};

class MouseTestListener : public MouseListener {
private:
    ACamera* __parent {nullptr};
public:
    MouseTestListener() = delete;
    explicit MouseTestListener(ACamera* obj) : MouseListener() { __parent = obj; }

    void buttonPressed(uint16 button, uint16 status, int x, int y) noexcept override {

        if(this->__parent != nullptr)
            this->__parent->mouseClick(button, status, x, y);
    }

    void moveEvent(int x, int y) noexcept override {

        if(this->__parent != nullptr)
            this->__parent->mouseMove(x, y);
    }
};

class TestInputListener : public KeyListener {
private:
    ACamera* __parent {nullptr};
public:
    TestInputListener() = delete;
    explicit TestInputListener(ACamera* obj) : KeyListener() { __parent = obj; }

    void keyPressed(uint16 keyCode) noexcept override{

        if(this->__parent != nullptr){
            this->__parent->keyPressed(keyCode);
        }
    }

    void keyReleased(uint16 keyCode) noexcept override{

        if(this->__parent != nullptr){
            this->__parent->keyReleased(keyCode);
        }
    }
};

int main(int argc, char** argv) {
    srand(time(nullptr));

    Engine *eng = Engine::EngineBuilder()
            .withMainWindowLocation(120, 50)
            .withMainWindowResolution(Size(1600, 900))
            .build();

    auto *camera = new ACamera;

    camera->addKeyListener(new TestInputListener(camera));
    camera->addMouseListener(new MouseTestListener(camera));

    for(int i = -3; i < 3; i++)
        for(int j = -3; j < 3; j++){
            auto* sphere = new Sphere;

            if(i == 2 && j == 2)
                sphere->setDebugTrackObject(true);

            sphere->getTransform().setLocation(VectorF(i * 10.0f, 1.0f, j * 10.0f));
            sphere->setColor(Color(rand() % 256, rand() %256, rand()% 256));
            eng->addGameObject(sphere);
        }

    eng->addGameObject(camera);
    eng->setActiveCamera(camera);
    eng->start(argc, argv);

    delete camera;
    return 0;
}
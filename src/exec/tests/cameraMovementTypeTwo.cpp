//
// Created by vladl on 07/07/2020.
//

#include <iostream>
#include <list>
#include "../../obj/engine/Engine.h"
#include "../../obj/engine/util/obj/standardObj/Camera.h"
#include <cmath>
#include <ctime>

class ACamera : public Camera{
public:
    void keyPressed(uint16 keyCode) noexcept {
        std::cout << "pressed\n";
        switch ( keyCode ) {
        case KEY_A : case KEY_LEFT_ARROW :
            deltaAngle = deltaAngle - 0.01f;    break;
        case KEY_D : case KEY_RIGHT_ARROW :
            deltaAngle = deltaAngle + 0.01f;    break;
        case KEY_W : case KEY_UP_ARROW :
            deltaMove = deltaMove + 0.5f;       break;
        case KEY_S : case KEY_DOWN_ARROW :
            deltaMove = deltaMove -0.5f;        break;
        default:
            break;
        }
    }

    void keyReleased(uint16 keyCode) noexcept {
        std::cout << "released\n";
        switch ( keyCode ) {
            case KEY_A : case KEY_LEFT_ARROW :
                deltaAngle = deltaAngle + 0.01f;    break;
            case KEY_D : case KEY_RIGHT_ARROW :
                deltaAngle = deltaAngle - 0.01f;    break;
            case KEY_W : case KEY_UP_ARROW :
                deltaMove = deltaMove - 0.5f;       break;
            case KEY_S : case KEY_DOWN_ARROW :
                deltaMove = deltaMove + 0.5f;        break;
            default:
                break;
        }
    }
};

class TestInputListener : public BoundKeyListener {
public:
    TestInputListener() = delete;
    explicit TestInputListener(GameObject* obj) : BoundKeyListener(obj) {  }

    void keyPressed(uint16 keyCode) noexcept override{
        auto* obj = dynamic_cast<ACamera*>(this->__parentReceiver);

        if(obj != nullptr){
            obj->keyPressed(keyCode);
        }
    }

    void keyReleased(uint16 keyCode) noexcept override{
        auto* obj = dynamic_cast<ACamera*>(this->__parentReceiver);

        if(obj != nullptr){
            obj->keyReleased(keyCode);
        }
    }
};

int main(int argc, char** argv) {
    srand(time(0));

    Engine *eng = Engine::EngineBuilder()
            .withMainWindowLocation(50, 50)
            .withMainWindowResolution(Size(1280, 720))
            .build();


    Camera *camera = new ACamera;

    camera->addKeyListener(new TestInputListener(camera));

    eng->addGameObject(camera);

    eng->start(argc, argv);
}
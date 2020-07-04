//
// Created by vladl on 04/07/2020.
//

#include <iostream>
#include "../../obj/engine/Engine.h"
#include <cmath>

float angle = 0.0f;
float rx = 0.0f;
float rz = -1.0f;
float x = 0.0f;
float z = 0.0f;

float deltaAngle = 0.0f;
float deltaMove = 0.0f;

void drawSnowMan(){
    glColor3f(1.0f, 1.0f, 1.0f);

    glTranslatef(0.0f, 0.75f, 0.0f);
    glutSolidSphere(0.75f, 20, 20);

//    glTranslatef(0.0f, 1.0f, 0.0f);
//    glutSolidSphere(0.25f, 20, 20);
//
//    glPushMatrix();
//    glColor3f(0.0f, 0.0f, 0.0f);
//    glTranslatef(0.05, 0.10f, 0.18f);
//
//    glutSolidSphere(0.05f, 10, 10);
//
//    glTranslatef(-0.1f, 0.0f, 0.0f);
//    glutSolidSphere(0.05f, 10, 10);
//    glPopMatrix();
//
//    glColor3f(1.0f, 0.5f, 0.5f);
//    glutSolidCone(0.08f, 0.5f, 10, 2);
}

void computePos(float deltaMove){
    x += deltaMove * rx * 0.1f;
    z += deltaMove * rz * 0.1f;
}

void computeDir(float deltaAngle){
    angle += deltaAngle;
    rx = sin(angle);
    rz = -cos(angle);
}

void renderScene() {
    if(deltaMove)
        computePos(deltaMove);

    if(deltaAngle)
        computeDir(deltaAngle);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(
        x, 1.0f, z,
        x + rx, 1.0f, z + rz,
        0.0f, 1.0f, 0.0f
    );

    glColor3f( 0.9f, 0.9f, 0.9f );

    glBegin(GL_QUADS);
    glVertex3f( -100.0f, 0.0f, -100.0f );
    glVertex3f( -100.0f, 0.0f, 100.0f );
    glVertex3f( 100.0f, 0.0f, 100.0f );
    glVertex3f( 100.0f, 0.0f, -100.0f );
    glEnd();

    for(int i = -3; i < 3; i++)
        for(int j = -3; j < 3; j++){
            glPushMatrix();
            glTranslatef(i * 10.0f, 0, j * 10.0f);
            drawSnowMan();
            glPopMatrix();
        }

    glutSwapBuffers();
}

constexpr float fraction = 0.5f;

class TestInput : public KeyListener {
    void keyPressed(uint16 keyCode) noexcept override {
        KeyListener::keyPressed(keyCode);

        switch(keyCode) {
            case KEY_LEFT_ARROW :
                deltaAngle = -0.01f;
                break;
            case KEY_RIGHT_ARROW :
                deltaAngle = 0.01f;
                break;
            case KEY_UP_ARROW :
                deltaMove = 0.5f;
                break;
            case KEY_DOWN_ARROW :
                deltaMove = -0.5f;
                break;
            default:
                break;
        }
    }
    void keyReleased(uint16 keyCode) noexcept override {
        KeyListener::keyReleased(keyCode);

        switch (keyCode) {
            case KEY_LEFT_ARROW :
            case KEY_RIGHT_ARROW :
                deltaAngle = 0.0f;
                break;
            case KEY_UP_ARROW :
            case KEY_DOWN_ARROW :
                deltaMove = 0.0f;
                break;
            default:
                break;
        }
    }
};

int main(int argc, char** argv) {
//    auto* window = new Window();

    Engine eng = Engine::EngineBuilder()
            .withMainWindowLocation(50, 50)
            .withMainWindowResolution(Size(1280, 720))
            .build();

    eng.getMainWindow().setDisplayFunctionCallback(renderScene);
    eng.getMainWindow().setRedrawFunctionCallback(renderScene);

    eng.addKeyListener(new TestInput);

    eng.start();

//    window->setReshapeFunctionCallback(reshapeFunction);
//    window->setDisplayFunctionCallback(renderScene);
//    window->setRedrawFunctionCallback(renderScene);

//    window->setKeyHandlerCallback(normalKey);
//    window->setSpecialKeyHandlerCallback(specialKey);


//    window->addKeyListener(new TestInput);

//    Window::disableKeyRepeats();
//    window->run(argc, argv);
}
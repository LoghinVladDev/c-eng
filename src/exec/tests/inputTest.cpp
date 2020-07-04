//
// Created by Vlad on 03/07/2020.
//

//
// Created by Vlad on 03/07/2020.
//

#include <iostream>
#include "../../obj/engine/window/Window.h"

float angle = 0.0f;

float rotateX = 0.0f;
float rotateY = 0.0f;
float rotateZ = 0.0f;

float red = 0.0f;
float green = 0.0f;
float blue = 0.0f;

void displayFunction() {
    glClear(DEFAULT_CLEAR_MASK_FLAGS);
    glLoadIdentity();
    gluLookAt(
            0.0f, 0.0f, 10.0f,
            0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f
    );

    glRotatef(angle, rotateX, rotateY, rotateZ);

    glColor3f(red, green, blue);

    glBegin(GL_TRIANGLES);
    glVertex3f(-2.0f,-2.0f, 0.0f);
    glVertex3f( 2.0f, 0.0f, 0.0);
    glVertex3f( 0.0f, 2.0f, 0.0);
    glEnd();

    angle += 0.1f;

    glutSwapBuffers();
}

void reshapeFunction(int newWidth, int newHeight){
    if( newHeight == 0 )
        newHeight = 1;

    float aspectRatio = (float)newWidth / (float)newHeight;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, newWidth, newHeight);
    gluPerspective(45, aspectRatio, 1, 100);
    glMatrixMode(GL_MODELVIEW);
}

class TestInput : public KeyListener {
    void keyPressed(uint16 keyCode) noexcept override {
        KeyListener::keyPressed(keyCode);
        std::cout << "key = " << keyCode << " pressed, modifier : " << this->getKeyModifier() << '\n';

        if(keyCode == KEY_ESCAPE){
            exit(0);
        }

        switch(keyCode){
            case KEY_F1 :
                red = 1.0f;
                green = 0.0f;
                blue = 0.0f;
                break;
            case KEY_F2 :
                red = 0.0f;
                green = 1.0f;
                blue = 0.0f;
                break;
            case KEY_F3:
                red = 0.0f;
                green = 0.0f;
                blue = 1.0f;
                break;
            default:
                red = 0.0f;
                green = 0.0f;
                blue = 0.0f;
        }
    }
    void keyReleased(uint16 keyCode) noexcept override {
        KeyListener::keyReleased(keyCode);
        std::cout << "key = " << keyCode << " released, modifier : " << this->getKeyModifier() << '\n';
    }
};

TestInput *testInput;

int main(int argc, char** argv){
    auto* window = new Window();

    rotateX = 1.0f;
    rotateY = 0.0f;
    rotateZ = 0.0f;

    testInput = new TestInput;

    window->setReshapeFunctionCallback(reshapeFunction);
    window->setDisplayFunctionCallback(displayFunction);
    window->setRedrawFunctionCallback(displayFunction);

//    window->setKeyHandlerCallback(normalKey);
//    window->setSpecialKeyHandlerCallback(specialKey);

    window->addKeyListener(new TestInput);

    window->run(argc, argv);

    delete testInput;
}
//
// Created by Vlad on 03/07/2020.
//

#include "../../obj/engine/window/Window.h"

float angle = 0.0f;

float rotateX = 0.0f;
float rotateY = 0.0f;
float rotateZ = 0.0f;

void displayFunction() {
    glClear(DEFAULT_CLEAR_MASK_FLAGS);
    glLoadIdentity();
    gluLookAt(
            0.0f, 0.0f, 10.0f,
            0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f
    );

    glRotatef(angle, rotateX, rotateY, rotateZ);

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

int main(int argc, char** argv){
    auto* window = new Window();

    rotateX = 1.0f;
    rotateY = 0.0f;
    rotateZ = 0.0f;

    window->setReshapeFunctionCallback(reshapeFunction);
    window->setDisplayFunctionCallback(displayFunction);
    window->setRedrawFunctionCallback(displayFunction);

    window->run(argc, argv);
}
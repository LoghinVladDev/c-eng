#include "src/obj/engine/window/Window.h"


void displayFunction() {
    glClear(DEFAULT_CLEAR_MASK_FLAGS);

    glBegin(GL_TRIANGLES);
//    glVertex3f(-2,-2,-5.0);
//    glVertex3f(2,0.0,-5.0);
//    glVertex3f(0.0,2,-5.0);

    glVertex3f(-0.5f, -0.5f, -5.0f);
    glVertex3f(0.5f, -0.5f, -5.0f);
    glVertex3f(0.5f, 0.5f, -5.0f);
//    glVertex3f(-0.5f, 0.5f, -5.0f);

    glEnd();

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
    window->setSize(1366, 768);
    window->setTitle("simple Test");

    window->setReshapeFunctionCallback(reshapeFunction);
    window->setDisplayFunctionCallback(displayFunction);

    window->run(argc, argv);
}
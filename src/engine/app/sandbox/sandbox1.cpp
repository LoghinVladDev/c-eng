//
// Created by loghin on 04.03.2021.
//
#include <iostream>
#include <ecm/VEntity.h>
#include <ecm/VComponent.h>
#include <VGameObject.h>
#include <transform/VTransform.h>

using namespace engine;

int main () {
    VGameObject o;

    o.addComponent(new VTransform(
        glm::vec3(1.0f, 0.5f, 0.75f),
        VRotor(200.0f, 150.0f, 20.0f),
        glm::vec3(1.0f, 1.0f, 1.0f)
    ));

    std::cout << o << '\n';
}
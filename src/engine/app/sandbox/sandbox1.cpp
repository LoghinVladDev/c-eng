//
// Created by loghin on 04.03.2021.
//
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#undef STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <ecm/VEntity.h>
#include <ecm/VComponent.h>
#include <VGameObject.h>
#include <transform/VTransform.h>
#include <model/VMesh.h>
#include <model/VMeshRenderer.h>


using namespace engine;

int main () {
    VGameObject o;

    o.addComponent(new VTransform(
        glm::vec3(1.0f, 0.5f, 0.75f),
        VRotor(200.0f, 150.0f, 20.0f),
        glm::vec3(1.0f, 1.0f, 1.0f)
    ));
    o.addComponent(new VMesh());
    o.addComponent(new VMeshRenderer());

    auto child1 = new VGameObject();
    auto child2 = new VGameObject();

    child1->addComponent(new VTransform(glm::vec3(1.0f, 0.2f, 0.3f)));

    child2->addComponent(new VTransform(3.0f, 5.0f, 1.0f));
    child2->addComponent(new VMesh());
    child2->addComponent(new VMeshRenderer());

    o.addChild(child1);
    o.addChild(child2);

    std::cout << o << '\n';

    std::cout << o.getComponentByClassName("VTransform")->toString() << '\n';
}
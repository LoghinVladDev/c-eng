//
// Created by loghin on 04.03.2021.
//

/**
 * Test Source 1
 */

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
#include <scene/VScene.h>

using namespace engine;



int main () {
    VScene s;

    auto o = new VGameObject();

    o->add(new VTransform(
        glm::vec3(1.0f, 0.5f, 0.75f),
        VRotor(200.0f, 150.0f, 20.0f),
        glm::vec3(1.0f, 1.0f, 1.0f)
    ));
    o->add(new VMesh());
    o->add(new VMeshRenderer());

    auto child1 = new VGameObject();
    auto child2 = new VGameObject();

    child1->add(new VTransform(glm::vec3(1.0f, 0.2f, 0.3f)));

    child2->add(new VTransform(3.0f, 5.0f, 1.0f));
    child2->add(new VMesh());
    child2->add(new VMeshRenderer());

    o->add(child1);
    o->add(child2);

//    std::cout << o << '\n';

    s.add(o);

//    std::cout << o->getComponentByClassName("VTransform")->toString() << '\n';

    std::cout << s << '\n';

    o->remove(child2);

    std::cout << s << '\n';

    o->add(child2);

    std::cout << s << '\n';

    std::cout << s.getComponentByID(5)->toString() << '\n';

    for( auto * pTransform : s.componentsOfClass("VMesh") ) {
        std::cout << pTransform->toString() << '\n';
    }

    std::cout << s.entitiesOfClass("VGameObject") << '\n';
}
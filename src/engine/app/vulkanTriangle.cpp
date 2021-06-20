//
// Created by vladl on 05/08/2020.
//

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#undef STB_IMAGE_IMPLEMENTATION

#include <iostream>

#include <src/engine/obj/util/proto/VulkanTriangleApplication.hpp>
#include <tools/loader/VMeshLoader.hpp>

/**
 * Base Prototype Application
 */

using namespace engine;
/**
 * Vertices of a star, with colors
 */
const std::vector < engine::VVertex > starVertices = {

        { { -0.2f, -0.2f, 0.0f }, {0.0f, 0.0f, 0.0f} },
        { {  0.2f, -0.2f, 0.0f }, {0.0f, 0.0f, 0.0f} },
        { {  0.3f,  0.1f, 0.0f }, {0.0f, 0.0f, 0.0f} },
        { {  0.0f,  0.3f, 0.0f }, {0.0f, 0.0f, 0.0f} },
        { { -0.3f,  0.1f, 0.0f }, {0.0f, 0.0f, 0.0f} },

        { { 0.0f, -0.6f, 0.0f }, {1.0f, 0.0f, 0.0f} },
        { { 0.6f, -0.2f, 0.0f }, {0.0f, 1.0f, 0.0f} },
        { { 0.4f,  0.55f, 0.0f }, {0.0f, 0.0f, 1.0f} },
        { {-0.4f,  0.55f, 0.0f }, {0.0f, 1.0f, 1.0f} },
        { {-0.6f, -0.2f, 0.0f }, {1.0f, 1.0f, 0.3f} },
};

/**
 * Indices of the star object, triangles, in draw order CCW
 */
const std::vector < uint16 > starIndices = {

        0, 1, 4,
        1, 3, 4,
        1, 2, 3,

        0, 5, 1,
        1, 6, 2,
        2, 7, 3,
        3, 8, 4,
        4, 9, 0,
};

/**
 * Cube Vertices, with color ( 1.0, 1.0, 1.0 = no color modif. ), texture coords
 */
const std::vector < engine::VVertex > cubeVertices = {


        {{-0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
        {{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},

        {{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
        {{ 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
        {{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},

        {{ 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
        {{ 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},

        {{-0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},  // 2
        {{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}, // 3
        {{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}}, // 0
        {{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}}, // 1
};

/**
 * order of drawing, CCW, triangles
 */
const std::vector < uint16 > cubeIndices = {

        0,   1,  2,  2,  3,  0,
        1,   0,  5,  4,  5,  0,
        9,   8,  10, 10, 11, 9,
        3,   2,  7,  6,  7,  2,
        12,  13, 14, 15, 14, 13,
        4,   6,  5,  7,  6,  4
};

auto addObjects (VulkanTriangleApplication & a) {
    auto teapot = new VGameObject("teapot");
    teapot->add(new VTransform);
    teapot->add(new VMesh);
    teapot->add(new VMeshRenderer);

    teapot->transform()->location().x -= 5.0f;

    auto pumpkin = new VGameObject("pumpkin");
    pumpkin->add(new VTransform);
    pumpkin->add(new VMesh);
    pumpkin->add(new VMeshRenderer);


    teapot->add(pumpkin);
    teapot->transform()->scale() = {0.2f, 0.2f, 0.2f};
    pumpkin->transform()->scale() = {0.02f, 0.02f, 0.02f};
    pumpkin->transform()->location().x += 4.0f;

    auto cow = new VGameObject ("cow");
    cow->add(new VTransform);
    cow->add(new VMesh);
    cow->add(new VMeshRenderer);

    cow->transform()->location().z += 5.0f;

    auto cube = new VGameObject("cube");
    VMeshLoader loader;
    loader.requestModelLoad("../data/models/teapot.obj", [& a, & teapot, &cube](VMeshLoader::RawMesh const & mesh){
        a.objectVertices()[teapot] = & mesh.demoVertices();
        a.objectIndices()[teapot] = & mesh.demoIndices();
        a.objectTextureNames()[teapot] = "none.png";
//        a.scene().add(teapot);
        cube->add(teapot);
    });

    loader.requestModelLoad("../data/models/pumpkin.obj", [&a, &pumpkin](VMeshLoader::RawMesh const & rm) {
        a.objectVertices()[pumpkin] = & rm.demoVertices();
        a.objectIndices()[pumpkin] = & rm.demoIndices();
        a.objectTextureNames()[pumpkin] = "none.png";

    });

    loader.requestModelLoad("../data/models/cow.obj", [& a, & cow](VMeshLoader::RawMesh const & rm){
        a.objectVertices()[cow] = & rm.demoVertices();
        a.objectIndices()[cow] = & rm.demoIndices();
        a.objectTextureNames()[cow] = "none.png";
        a.scene().add(cow);
    });

    /// region hardcoded obj
    cube->add(new VTransform());
    cube->add(new VMesh());
    cube->add(new VMeshRenderer());

    auto cube2 = new VGameObject("cube2");
    cube2->add(new VTransform());
    cube2->add(new VMesh());
    cube2->add(new VMeshRenderer());

    auto cube3 = new VGameObject ("cube3");

    cube3->add(new VTransform());
    cube3->add(new VMesh());
    cube3->add(new VMeshRenderer());

    auto star = new VGameObject("star");
    star->add(new VTransform());
    star->add(new VMesh());
    star->add(new VMeshRenderer());

    auto cube4 = new VGameObject("cube4");
    cube4->add(new VTransform());
    cube4->add(new VMesh());
    cube4->add(new VMeshRenderer());

    auto plane = new VGameObject("plane");
    plane->add(new VTransform);
    plane->add(new VMesh);
    plane->add(new VMeshRenderer);

    plane->transform()->location().y -= 2.1f;

    plane->transform()->scale() = { 50.0f, 0.2f, 50.0f };
//
//    star->transform()->location().x -= 2.0f;
//    star->transform()->location().z += 1.0f;
//    star->transform()->location().y += 1.0f;

    cube4->transform()->location().x += 0.4f;

    /// endregion

    a.objectVertices()[cube] = & cubeVertices;
    a.objectVertices()[cube2] = & cubeVertices;
    a.objectVertices()[cube3] = & cubeVertices;
    a.objectVertices()[cube4] = & cubeVertices;
    a.objectVertices()[plane] = & cubeVertices;

    a.objectIndices()[cube] = & cubeIndices;
    a.objectIndices()[cube2] = & cubeIndices;
    a.objectIndices()[cube3] = & cubeIndices;
    a.objectIndices()[cube4] = & cubeIndices;
    a.objectIndices()[plane] = & cubeIndices;

    a.objectVertices()[star] = & starVertices;
    a.objectIndices()[star] = & starIndices;

    a.objectTextureNames()[cube] = "container.jpg";
    a.objectTextureNames()[cube2] = "container2.png";
    a.objectTextureNames()[cube3] = "container3.jpg";
    a.objectTextureNames()[star] = "none.png";
    a.objectTextureNames()[cube4] = "container.jpg";
    plane->transform()->rotation().roll() += 180.0f;
//    a.objectTextureNames()[plane] = "container2.png";

//    star->add(cube);
    cube->add(cube2);
    cube2->add(cube3);
    cube3->add(star);

    star->add(cube4);

    cube4->transform()->scale() = {0.15f, 0.15f, 0.15f};

    cube->transform()->location().x += 0.5f;
    cube->transform()->location().y -= 0.5f;
    cube->transform()->location().z -= 0.5f;

    cube2->transform()->location().x += 1.0f;
    cube2->transform()->location().y += 0.0f;
    cube2->transform()->location().z += 0.0f;

    cube3->transform()->scale() = {0.3f, 0.3f, 0.3f};
    cube3->transform()->location() = {0.0f, 0.65f, 0.0f};

//    a.scene().add(star); /// Add object to scene
    a.scene().add(cube);
    a.scene().add(cube3);
    a.scene().add(plane);
    a.scene().setActiveCamera(new VCamera({0.0f, 0.0f, 3.0f}));
}

int main() {
    VulkanTriangleApplication app(1366, 768);

    addObjects(app);

    app.setMouseCursorEnabled(false);
//    app.scene().setImmediateCachingEnabled(true);
//    app.scene().setPeriodicCachingEnabled(true);
    app.scene().setPeriodicCacheReconstructionInterval(2048);
//    app.enableShowFPS();

    app.setFOV(80.0f);
    app.setDrawDistance(200.0f);

    try{
        /**
         * Enable validation layers if in debug
         */
#ifndef NDEBUG
        app.addValidationLayer( VValidationLayer::KHRONOS_VALIDATION );
#endif
        app.run();
    } catch (std::exception const & e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
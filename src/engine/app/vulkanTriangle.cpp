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

using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)

/**
 * Vertices of a star, with colors
 */
const std::vector < engine::VVertex > starVertices = { // NOLINT(cert-err58-cpp)

        { { -0.2F, -0.2F, 0.0F }, {0.0F, 0.0F, 0.0F} },
        { {  0.2F, -0.2F, 0.0F }, {0.0F, 0.0F, 0.0F} },
        { {  0.3F,  0.1F, 0.0F }, {0.0F, 0.0F, 0.0F} },
        { {  0.0F,  0.3F, 0.0F }, {0.0F, 0.0F, 0.0F} },
        { { -0.3F,  0.1F, 0.0F }, {0.0F, 0.0F, 0.0F} },

        { { 0.0F, -0.6F, 0.0F }, {1.0F, 0.0F, 0.0F} },
        { { 0.6F, -0.2F, 0.0F }, {0.0F, 1.0F, 0.0F} },
        { { 0.4F,  0.55F, 0.0F }, {0.0F, 0.0F, 1.0F} },
        { {-0.4F,  0.55F, 0.0F }, {0.0F, 1.0F, 1.0F} },
        { {-0.6F, -0.2F, 0.0F }, {1.0F, 1.0F, 0.3F} },
};

/**
 * Indices of the star object, triangles, in draw order CCW
 */
const std::vector < uint16 > starIndices = { // NOLINT(cert-err58-cpp)

        0U, 1U, 4U,
        1U, 3U, 4U,
        1U, 2U, 3U,

        0U, 5U, 1U,
        1U, 6U, 2U,
        2U, 7U, 3U,
        3U, 8U, 4U,
        4U, 9U, 0U,
};

/**
 * Cube Vertices, with color ( 1.0, 1.0, 1.0 = no color modif. ), texture coords
 */
const std::vector < engine::VVertex > cubeVertices = { // NOLINT(cert-err58-cpp)


        {{-0.5F, -0.5F,  0.5F}, {1.0F, 1.0F, 1.0F}, {0.0F, 0.0F}},
        {{ 0.5F, -0.5F,  0.5F}, {1.0F, 1.0F, 1.0F}, {1.0F, 0.0F}},
        {{ 0.5F,  0.5F,  0.5F}, {1.0F, 1.0F, 1.0F}, {1.0F, 1.0F}},
        {{-0.5F,  0.5F,  0.5F}, {1.0F, 1.0F, 1.0F}, {0.0F, 1.0F}},

        {{-0.5F, -0.5F, -0.5F}, {1.0F, 1.0F, 1.0F}, {0.0F, 1.0F}},
        {{ 0.5F, -0.5F, -0.5F}, {1.0F, 1.0F, 1.0F}, {1.0F, 1.0F}},
        {{ 0.5F,  0.5F, -0.5F}, {1.0F, 1.0F, 1.0F}, {1.0F, 0.0F}},
        {{-0.5F,  0.5F, -0.5F}, {1.0F, 1.0F, 1.0F}, {0.0F, 0.0F}},

        {{ 0.5F, -0.5F,  0.5F}, {1.0F, 1.0F, 1.0F}, {0.0F, 0.0F}},
        {{ 0.5F,  0.5F,  0.5F}, {1.0F, 1.0F, 1.0F}, {1.0F, 0.0F}},
        {{ 0.5F, -0.5F, -0.5F}, {1.0F, 1.0F, 1.0F}, {0.0F, 1.0F}},
        {{ 0.5F,  0.5F, -0.5F}, {1.0F, 1.0F, 1.0F}, {1.0F, 1.0F}},

        {{-0.5F, -0.5F,  0.5F}, {1.0F, 1.0F, 1.0F}, {0.0F, 1.0F}},  // 2
        {{-0.5F,  0.5F,  0.5F}, {1.0F, 1.0F, 1.0F}, {1.0F, 1.0F}}, // 3
        {{-0.5F, -0.5F, -0.5F}, {1.0F, 1.0F, 1.0F}, {0.0F, 0.0F}}, // 0
        {{-0.5F,  0.5F, -0.5F}, {1.0F, 1.0F, 1.0F}, {1.0F, 0.0F}}, // 1
};

/**
 * order of drawing, CCW, triangles
 */
const std::vector < uint16 > cubeIndices = { // NOLINT(cert-err58-cpp)

        0U,   1U,  2U,  2U,  3U,  0U,
        1U,   0U,  5U,  4U,  5U,  0U,
        9U,   8U,  10U, 10U, 11U, 9U,
        3U,   2U,  7U,  6U,  7U,  2U,
        12U,  13U, 14U, 15U, 14U, 13U,
        4U,   6U,  5U,  7U,  6U,  4U
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
    (void) a.scene().setActiveCamera(new VCamera({0.0F, 0.0F, 3.0F}));
}

int main() {
    VulkanTriangleApplication app(1366, 768);

    addObjects(app);

    app.setMouseCursorEnabled(false);
//    app.scene().setImmediateCachingEnabled(true);
//    app.scene().setPeriodicCachingEnabled(true);
    app.scene().setPeriodicCacheReconstructionInterval(2048);
//    app.enableShowFPS();

    app.setFOV(80.0F);
    app.setDrawDistance(200.0F);

    try{
        /**
         * Enable validation layers if in debug
         */
#ifndef NDEBUG
        (void) app.addValidationLayer( VValidationLayer::KHRONOS_VALIDATION );
#endif
        app.run();
    } catch (std::exception const & e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
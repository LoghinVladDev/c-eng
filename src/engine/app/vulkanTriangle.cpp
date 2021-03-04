//
// Created by vladl on 05/08/2020.
//

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#undef STB_IMAGE_IMPLEMENTATION

#include <iostream>

#include <src/engine/obj/util/proto/VulkanTriangleApplication.h>


using namespace engine;

int main() {
    VulkanTriangleApplication app(1024, 768);

    try{
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
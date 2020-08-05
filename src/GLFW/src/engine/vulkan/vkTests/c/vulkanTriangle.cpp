//
// Created by vladl on 05/08/2020.
//

#include <iostream>
#include <vkTests/obj/VulkanTriangleApplication.h>
#include <cstring>
using namespace engine;

int main() {
    VulkanTriangleApplication app(1024, 768);

    try{
        ValidationLayer khronosValidationLayer;
        khronosValidationLayer.setLayerType( ValidationLayer::KHRONOS_VALIDATION );

        app.addValidationLayer( khronosValidationLayer );
        app.run();
    } catch (std::exception const & e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
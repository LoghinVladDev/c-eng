//
// Created by vladl on 05/08/2020.
//

#include "VulkanInitTests.h"
#include <engineVulkanPreproc.h>

inline void engine::VulkanInitTests::glfwInitTest() {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    GLFWwindow * window = glfwCreateWindow(800, 600, "Vulkan Window", nullptr, nullptr);

    uint32 extensionsCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, nullptr);

    std::cout << extensionsCount << " extensions supported\n";

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
}

inline void engine::VulkanInitTests::glmInitTest() {
    glm::mat4 matrix;
    glm::vec4 vector;

    auto test = matrix * vector;
}
/*
 * Created by loghin on 27/12/22.
 */

#include <GLFW/glfw3.h>

int main () {

    glfwInit();
    auto p = glfwCreateWindow(800, 600, "test", nullptr, nullptr);
    while ( ! glfwWindowShouldClose(p)) {
glfwPollEvents();
    }
    glfwTerminate();
}
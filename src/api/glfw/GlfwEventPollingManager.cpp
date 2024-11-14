//
// Created by loghin on 11/9/24.
//

#include "GlfwEventPollingManager.hpp"
#include <GLFW/glfw3.h>

namespace c_eng::api::detail {
auto GlfwEventPollingManager::poll() noexcept -> void {
  glfwPollEvents();
}
} // namespace c_eng::api::detail

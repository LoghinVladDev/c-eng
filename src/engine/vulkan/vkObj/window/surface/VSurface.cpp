//
// Created by Vlad on 12/08/2020.
//

#include "VSurface.h"

static inline void populateSurfaceCreateInfo ( VulkanSurfaceCreateInfoKhronos * createInfo, GLFWwindow* window ) noexcept {
    if( createInfo == nullptr )
        return;

    * createInfo = {};

#if     defined(ENGINE_OS_WINDOWS_32_64)

    createInfo->sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    createInfo->hwnd = glfwGetWin32Window( window );
    createInfo->hinstance = GetModuleHandle ( nullptr );

#elif   defined(ENGINE_OS_LINUX)

    //createInfo->sType = ... let glfw do the work

#elif   defined(ENGINE_OS_MAC_OS_X)

    //createInfo->sType = ...

#endif

}

VulkanResult engine::VSurface::setup(GLFWwindow * window, const VInstance& instance) noexcept {
    this->_instance = & instance;

#if defined(ENGINE_OS_WINDOWS_32_64)
    VulkanSurfaceCreateInfoKhronos createInfo {};
    populateSurfaceCreateInfo( & createInfo, window );

    return vkCreateSurfaceKhronos( instance.data(), & createInfo, nullptr, & this->_surface );
#elif defined(ENGINE_OS_LINUX)
    return glfwCreateWindowSurface( instance.data(), window, nullptr, & this->_surface );
#endif
}

void engine::VSurface::clean() noexcept {
    vkDestroySurfaceKHR( this->_instance->data(), this->_surface, nullptr );
}
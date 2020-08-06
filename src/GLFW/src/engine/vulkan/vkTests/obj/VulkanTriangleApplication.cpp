//
// Created by vladl on 05/08/2020.
//

#include "VulkanTriangleApplication.h"
#include <src/GLFW/src/engine/vulkan/vkObj/instance/extension/VExtension.h>
#include <src/GLFW/src/engine/vulkan/vkUtils/VStdUtils.h>
#include <vkObj/instance/device/VPhysicalDevice.h>

const char* engine::VulkanTriangleApplication::DEFAULT_TITLE = "Vulkan Application";

engine::VulkanTriangleApplication::VulkanTriangleApplication(uint32 width, uint32 height) noexcept :
    _width(width),
    _height(height){

}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"
#pragma ide diagnostic ignored "UnreachableCode"
void engine::VulkanTriangleApplication::setupDebugMessenger() noexcept (false) {

    if ( ! enableValidationLayers ) return;

    VulkanResult res;

    if( ( res = this->_vulkanMessenger.setup ( & this->_vulkanInstance ) ) != VK_SUCCESS ) {
        throw std::runtime_error("debug messenger setup failure : " + engine::VStandardUtils::to_string(res));
    }
}
#pragma clang diagnostic pop

void engine::VulkanTriangleApplication::run() noexcept (false) {
    this->initWindow();
    this->initVulkan();
    this->mainLoop();
    this->cleanup();
}

inline void engine::VulkanTriangleApplication::initWindow() noexcept (false) {
    if(glfwInit() == GLFW_FALSE) {
        throw engine::EngineVulkanTestException("GLFW Init failure");
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    this->_window = glfwCreateWindow(
        this->_width,
        this->_height,
        VulkanTriangleApplication::DEFAULT_TITLE,
        nullptr,
        nullptr
    );
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"
#pragma ide diagnostic ignored "UnreachableCode"
inline void engine::VulkanTriangleApplication::initVulkan() noexcept (false) {
    if( VulkanTriangleApplication::VULKAN_EXT_CHECK ) {
        VExtension::printExtensions(std::cout);
    }

    if( enableValidationLayers ) {
        VValidationLayer::debugPrintAvailableValidationLayers(std::cout);

        std::cout << "\nRequested Validation Layers : \n";

        for( const auto & layer : this->_vulkanValidationLayerCollection.getValidationLayers() ) {
            std::cout << '\t' << layer.getLiteral() << '\n';
        }

        if( ! VValidationLayer::checkValidationLayerSupport(this->_vulkanValidationLayerCollection) ) {
            throw std::runtime_error("requested validation layers are not available!");
        }

        std::cout << "\nRequested Layers are available!\n";

        if ( this->_vulkanInstance.setup( this->_vulkanValidationLayerCollection ) != VK_SUCCESS ) {
            throw std::runtime_error ("failed to create Vulkan instance");
        }
    } else
    {
        if ( this->_vulkanInstance.setup() != VK_SUCCESS )
            throw std::runtime_error ("failed to create Vulkan instance");
    }


    this->setupDebugMessenger();
    this->pickPhysicalDevice();
}
#pragma clang diagnostic pop

void engine::VulkanTriangleApplication::mainLoop() noexcept (false) {

}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"
void engine::VulkanTriangleApplication::cleanup() noexcept (false) {
    if( enableValidationLayers )
        this->_vulkanMessenger.clean();

    this->_vulkanInstance.clean();

    glfwDestroyWindow(this->_window);

    glfwTerminate();
}

void engine::VulkanTriangleApplication::pickPhysicalDevice() noexcept(false) {
    VPhysicalDevice::debugPrintAvailablePhysicalDevices( this->_vulkanInstance, std::cout );
}

#pragma clang diagnostic pop
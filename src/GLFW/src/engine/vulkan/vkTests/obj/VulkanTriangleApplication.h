//
// Created by vladl on 05/08/2020.
//


#ifndef ENG1_VULKANTRIANGLEAPPLICATION_H
#define ENG1_VULKANTRIANGLEAPPLICATION_H

#define VK_CHECK_EXT

#ifdef VK_CHECK_EXT
#define _VK_CHECK_EXT true
#endif

#ifndef VK_CHECK_EXT
#define _VK_CHECK_EXT false
#endif

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vector>
#include <src/GLFW/src/engine/vulkan/vkObj/instance/validationLayer/VValidationLayer.h>
#include <src/GLFW/src/engine/vulkan/vkObj/instance/VInstance.h>
#include <src/GLFW/src/engine/vulkan/vkObj/instance/messenger/VMessenger.h>
#include <vkObj/instance/device/VPhysicalDevice.h>
#include <src/GLFW/src/engine/vulkan/vkObj/instance/device/VLogicalDevice.h>
#include <src/GLFW/src/engine/vulkan/vkObj/window/surface/VSurface.h>

namespace engine {

    class EngineVulkanTestException : public std::exception {
    private:
        std::string message = "Exception thrown!";
    public:
        [[maybe_unused]] explicit EngineVulkanTestException(std::string const & msg) noexcept {
            this->message = msg;
        }

        [[nodiscard]] const char * what() const noexcept override {
            return this->message.c_str();
        }
    };

    class VulkanTriangleApplication {
    private:
        //// private_vars
        uint32                      _width          {VulkanTriangleApplication::DEFAULT_WIDTH};
        uint32                      _height         {VulkanTriangleApplication::DEFAULT_HEIGHT};

        GLFWwindow *                _window         {nullptr};

        VMessenger                  _vulkanMessenger;
        VValidationLayerCollection  _vulkanValidationLayerCollection;
        VInstance                   _vulkanInstance;
        VSurface                    _vulkanSurface;
        VPhysicalDevice             _vulkanPhysicalDevice;

        VQueueFamilyCollection    * _vulkanQueueFamilyCollection        {nullptr};
        VLogicalDevice            * _vulkanLogicalDevice                {nullptr};

        //// private_functions
        void initWindow() noexcept(false);
        void initVulkan() noexcept(false);
        void mainLoop() noexcept(false);
        void cleanup() noexcept(false);

        void createSurface() noexcept (false);
        void setupDebugMessenger() noexcept (false);
        void autoPickPhysicalDevice() noexcept (false);
    public:
        //// public_vars
        constexpr static uint32 DEFAULT_WIDTH       = 800U;
        constexpr static uint32 DEFAULT_HEIGHT      = 600U;
        constexpr static bool   VULKAN_EXT_CHECK    = _VK_CHECK_EXT;

        static const int8*      DEFAULT_TITLE;

        //// public_functions
        VulkanTriangleApplication() noexcept = default;
        explicit VulkanTriangleApplication(uint32, uint32) noexcept;

        [[nodiscard]] VValidationLayerCollection & getValidationLayerCollection() noexcept {
            return this->_vulkanValidationLayerCollection;
        }

        VulkanTriangleApplication & addValidationLayer ( const engine::VValidationLayer & layer ) noexcept {
            this->_vulkanValidationLayerCollection.addValidationLayer(layer );
            return *this;
        }

        VulkanTriangleApplication & addValidationLayer ( engine::VValidationLayer::VulkanValidationLayer layerType ) noexcept {
            this->_vulkanValidationLayerCollection.addValidationLayer( engine::VValidationLayer().setLayerType(layerType) );
            return *this;
        }

        VulkanTriangleApplication & addValidationLayers( const engine::VValidationLayerCollection & layerCollection ) noexcept {
            for( const auto & layer : layerCollection.getValidationLayers() ) {
                this->_vulkanValidationLayerCollection.addValidationLayer(layer );
            }
            return *this;
        }

        VulkanTriangleApplication & clearValidationLayers() noexcept {
            this->_vulkanValidationLayerCollection.clear();
            return *this;
        }

        void run() noexcept (false);
    };

}


#endif //ENG1_VULKANTRIANGLEAPPLICATION_H

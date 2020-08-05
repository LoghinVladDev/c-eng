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
#include <src/GLFW/src/engine/vulkan/vkObj/validationLayer/ValidationLayer.h>

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
        uint32                                                          _width          {VulkanTriangleApplication::DEFAULT_WIDTH};
        uint32                                                          _height         {VulkanTriangleApplication::DEFAULT_HEIGHT};

        GLFWwindow *                                                    _window         {nullptr};
        VulkanInstance                                                  _instance       {nullptr};
        VulkanDebugMessenger                                            _debugMessenger {nullptr};

        std::vector < VulkanExtensionProperties > *                     _extensionsPtr  {nullptr};

        ValidationLayerCollection                                       _validationLayerCollection;

        //// private_functions
        void initWindow() noexcept(false);
        void initVulkan() noexcept(false);
        void mainLoop() noexcept(false);
        void cleanup() noexcept(false);

        void setupDebugMessenger() noexcept (false);

        VulkanResult createVulkanInstance() noexcept;

        void printExtensions() const noexcept;
        void checkExtensions() noexcept;
        [[nodiscard]] const std::vector < VulkanExtensionProperties > * getVulkanExtensions() const noexcept;
    public:
        //// public_vars
        constexpr static uint32 DEFAULT_WIDTH       = 800U;
        constexpr static uint32 DEFAULT_HEIGHT      = 600U;
        constexpr static bool   VULKAN_EXT_CHECK    = _VK_CHECK_EXT;

        static const int8*      DEFAULT_TITLE;

        constexpr static VulkanFlags DEFAULT_DEBUG_MESSAGE_SEVERITY =
                (VulkanFlags) VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                (VulkanFlags) VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                (VulkanFlags) VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

        constexpr static VulkanFlags DEFAULT_DEBUG_MESSAGE_TYPE =
                (VulkanFlags) VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                (VulkanFlags) VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                (VulkanFlags) VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

        //// public_functions
        VulkanTriangleApplication() noexcept = default;
        explicit VulkanTriangleApplication(uint32, uint32) noexcept;

        [[nodiscard]] ValidationLayerCollection & getValidationLayerCollection() noexcept {
            return this->_validationLayerCollection;
        }

        VulkanTriangleApplication & addValidationLayer ( const engine::ValidationLayer & layer ) noexcept {
            this->_validationLayerCollection.addValidationLayer(layer );
            return *this;
        }

        VulkanTriangleApplication & addValidationLayers( const engine::ValidationLayerCollection & layerCollection ) noexcept {
            for( const auto & layer : layerCollection.getValidationLayers() ) {
                this->_validationLayerCollection.addValidationLayer(layer );
            }
            return *this;
        }

        VulkanTriangleApplication & clearValidationLayers() noexcept {
            this->_validationLayerCollection.clear();
            return *this;
        }

        void run() noexcept (false);
    };

}


#endif //ENG1_VULKANTRIANGLEAPPLICATION_H

//
// Created by vladl on 05/08/2020.
//


#ifndef ENG1_VULKANTRIANGLEAPPLICATION_H
#define ENG1_VULKANTRIANGLEAPPLICATION_H

#define VK_CHECK_EXT

#ifdef VK_CHECK_EXT
#define _VK_CHECK_EXT true // NOLINT(bugprone-reserved-identifier)
#endif

#ifndef VK_CHECK_EXT
#define _VK_CHECK_EXT false // NOLINT(bugprone-reserved-identifier)
#endif

#define __SHOW_FPS_EVERY_S 0.100 // NOLINT(bugprone-reserved-identifier)

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/instance/validationLayer/VValidationLayer.h>
#include <vkObj/instance/VInstance.h>
#include <vkObj/instance/messenger/VMessenger.h>
#include <vkObj/instance/device/VPhysicalDevice.h>
#include <vkObj/instance/device/VLogicalDevice.h>
#include <vkObj/window/surface/VSurface.h>
#include <vkObj/instance/pipeline/VFrameBuffer.h>
#include <vkObj/instance/pipeline/command/VCommandBuffer.h>
#include <vkObj/instance/pipeline/synchronization/VSemaphore.h>
#include <vkObj/instance/pipeline/synchronization/VFence.h>
#include <vkObj/instance/pipeline/shader/input/VVertex.h>
#include <vkObj/instance/pipeline/shader/input/VUniformBuffer.h>
#include <vkObj/instance/pipeline/shader/input/VDescriptorPool.h>
#include <vkObj/instance/pipeline/shader/input/VDescriptorSet.h>
#include <src/engine/gobj/model/VMesh.h>
#include <VTexture.h>
#include <VTextureSampler.h>
#include <VDepthBuffer.h>
#include <src/engine/gobj/shader/VShader.h>

#include <vector>
#include <src/engine/gobj/model/VMeshRenderer.h>


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
        uint32                      _width                              {VulkanTriangleApplication::DEFAULT_WIDTH};
        uint32                      _height                             {VulkanTriangleApplication::DEFAULT_HEIGHT};

        GLFWwindow *                _window                             {nullptr};

        VMessenger                  _vulkanMessenger;
        VValidationLayerCollection  _vulkanValidationLayerCollection;
        VInstance                   _vulkanInstance;
        VSurface                    _vulkanSurface;
        VPhysicalDevice             _vulkanPhysicalDevice;

        VQueueFamilyCollection    * _vulkanQueueFamilyCollection        {nullptr};
        VLogicalDevice              _vulkanLogicalDevice;

        std::vector <VQueueFamily>  _graphicsCapableQueueFamily;

        VShader                     _objectShader;

        VFrameBufferCollection      _frameBufferCollection;

        VCommandPool                _commandPool;
        VCommandPool                _transferCommandPool;
        VCommandBufferCollection    _drawCommandBufferCollection;

        VSemaphoreCollection        _imageAvailableSemaphores;
        VSemaphoreCollection        _renderFinishedSemaphores;

        VFenceCollection            _inFlightFences;
        VFenceCollection            _imagesInFlight;

        VMesh                       _cubeMesh;
        VMesh                       _starMesh;

        VulkanDescriptorSetLayout   _descriptorSetLayoutSampler {};

        VDescriptorPool             _descriptorPool;

        VTextureSampler             _textureSampler;

        VDepthBuffer                _depthBuffer;

        glm::mat4                   _cubeModel  { glm::mat4( 0.0f ) };
        glm::mat4                   _starModel  { glm::mat4( 0.0f ) };

        glm::mat4                   _projection { glm::mat4( 0.0f ) };
        glm::mat4                   _view       { glm::mat4( 0.0f ) };

        VMeshRenderer               _cubeMeshRenderer;
        VMeshRenderer               _starMeshRenderer;

        double                      _fpsTimer = 0.0;
        double                      _fpsRefreshTimer = __SHOW_FPS_EVERY_S;
        double                      _deltaTime {0.0f};

        bool _framebufferResized {false};

        //// private_functions
        void initSettings() const noexcept;
        void initWindow() noexcept(false);
        void initVulkan() noexcept(false);
        void mainLoop() noexcept(false);
        void cleanup() noexcept(false);
        void update() noexcept(false);
        void drawImage() noexcept (false);

        void createShaderModules () noexcept (false);

        void createCommandPool() noexcept (false);
        void createCommandBuffers() noexcept (false);

        void createSynchronizationElements () noexcept (false);

        void createFrameBuffers () noexcept (false);
        void createDescriptorSetLayout() noexcept (false);
        void createGraphicsPipeline() noexcept (false);
        void createSurface() noexcept (false);
        void createTextures() noexcept (false);
        void setupDebugMessenger() noexcept (false);
        void autoPickPhysicalDevice() noexcept (false);

        void recreateSwapChain () noexcept (false);

        void createDepthBuffer () noexcept (false);
        void createBuffers () noexcept (false);
        void createExclusiveBuffers () noexcept (false);
        void createConcurrentBuffers () noexcept (false);
        void createUniformBuffers () noexcept (false);
        void createDescriptorPool() noexcept (false);
        void createDescriptorSets() noexcept (false);
        void updateUniformBuffer  ( uint32 ) noexcept (false);

        void freeStagingBuffers () noexcept (false);

        void cleanupSwapChain () noexcept (false);

        void updateResolutionSettings() noexcept;

        static void frameBufferResizeCallback ( GLFWwindow*, [[maybe_unused]] int32, int32 );
    public:
        //// public_vars
        constexpr static uint32 DEFAULT_WIDTH       = 800U;
        constexpr static uint32 DEFAULT_HEIGHT      = 600U;
        constexpr static bool   VULKAN_EXT_CHECK    = _VK_CHECK_EXT;
        constexpr static bool   SHOW_FPS_CONSOLE    = true;

        static const char *     DEFAULT_TITLE;

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

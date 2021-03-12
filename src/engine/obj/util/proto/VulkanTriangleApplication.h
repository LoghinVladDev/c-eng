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
//#include <src/engine/gobj/model/VMesh.h>
#include <VTexture.h>
#include <VTextureSampler.h>
#include <VDepthBuffer.h>
#include <src/engine/gobj/shader/VShader.h>

#include <vector>
//#include <src/engine/gobj/model/VMeshRenderer.h>

#include <VGameObject.h>

#include <scene/VScene.h>

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

    /**
     * @class Vulkan Prototype Engine Class
     *
     * To be Split Into VWindow
     *                  VEngine
     *
     */
    class VulkanTriangleApplication {
    private:
        //// private_vars

        //// window width
        uint32                      _width                              {VulkanTriangleApplication::DEFAULT_WIDTH};
        //// window height
        uint32                      _height                             {VulkanTriangleApplication::DEFAULT_HEIGHT};

        //// window address
        GLFWwindow *                _window                             {nullptr};

        //// error callback messenger for GPU errors
        VMessenger                  _vulkanMessenger;
        //// collection of multiple validation layers
        VValidationLayerCollection  _vulkanValidationLayerCollection;
        //// vulkan instance
        VInstance                   _vulkanInstance;
        //// surface to print GPU images on
        VSurface                    _vulkanSurface;
        //// GPU handle and interfaces
        VPhysicalDevice             _vulkanPhysicalDevice;

        //// Address of Queue Families
        VQueueFamilyCollection    * _vulkanQueueFamilyCollection        {nullptr};
        //// GPU + CPU-GPU buses used + GPU-surface bus used interface
        VLogicalDevice              _vulkanLogicalDevice;

        //// Shader used for all objects
        VShader                     _objectShader;

        //// Frame Buffers used to draw on
        VFrameBufferCollection      _frameBufferCollection;

        //// Command Pool for Draw Commands
        VCommandPool                _commandPool;
        //// Command Pool for Transfer from GPU to Surface
        VCommandPool                _transferCommandPool;
        //// Command Buffer Storage
        VCommandBufferCollection    _drawCommandBufferCollection;

        //// All semaphores signaling image availability finish per image
        VSemaphoreCollection        _imageAvailableSemaphores;
        //// All semaphores signaling render finish of images per image
        VSemaphoreCollection        _renderFinishedSemaphores;

        //// Fences synchronising semaphores for image swapping and semaphore sync
        VFenceCollection            _inFlightFences;
        //// Fences synchronising semaphores for image swapping and semaphore sync
        VFenceCollection            _imagesInFlight;

        //// Descriptor Pool for Allocation of Descriptors ( Locations ) for Buffers on GPU and shared CPU-GPU Buffers
        VDescriptorPool             _descriptorPool;

        //// Texture Sampler Object.
        VTextureSampler             _textureSampler;
        //// Depth Buffer Object. Does depth testing - draws objects closer to the camera over objects further away
        VDepthBuffer                _depthBuffer;

        //// Active Scene - Hierarchy of Entities
        VScene                      _activeScene;

        //// Current FPS
        double                      _fpsTimer = 0.0;
        //// Show FPS every .... seconds
        double                      _fpsRefreshTimer = __SHOW_FPS_EVERY_S;
        //// Time Between start of draw and end of draw for last image
        double                      _deltaTime {0.0f};

        //// Used to recreate all resources using surface resolution when window is resized
        bool _framebufferResized {false};

        //// private_functions
        void initSettings() const noexcept; //// initialisation of settings ( resolution ... )
        void initWindow() noexcept(false);  //// creation of window context
        void initVulkan() noexcept(false);  //// creation of vulkan instance
        void mainLoop() noexcept(false);    //// start of MVC application
        void cleanup() noexcept(false);     //// cleanup of all data created
        void update() noexcept(false);      //// Periodic call per frame for each object
        void drawImage() noexcept (false);  //// Periodic call to draw a free image

        void createShaderModules () noexcept (false); //// creation of shaders - Deprecated. Will be built by Precompiler

        void createCommandPool() noexcept (false);    //// creation of command pool - any draw commands, allocated from a pool ( cached on gpu )
        void createCommandBuffers() noexcept (false); //// creation of command buffers - GPU draw commands, pre-recorder for optimisation

        void createSynchronizationElements () noexcept (false); //// creation of CPU-GPU sync elements - semaphores, fences, barriers

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

        auto createGameObjects () noexcept -> void;
    public:
        //// public_vars
        constexpr static uint32 DEFAULT_WIDTH       = 1024U;
        constexpr static uint32 DEFAULT_HEIGHT      = 768U;
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

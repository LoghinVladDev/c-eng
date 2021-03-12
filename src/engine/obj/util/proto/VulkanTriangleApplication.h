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
#include <vulkanExplicitTypes.h>
#include <VValidationLayer.h>
#include <VInstance.h>
#include <VMessenger.h>
#include <VPhysicalDevice.h>
#include <VLogicalDevice.h>
#include <VSurface.h>
#include <VFrameBuffer.h>
#include <VCommandBuffer.h>
#include <VSemaphore.h>
#include <VFence.h>
#include <VVertex.h>
#include <VUniformBuffer.h>
#include <VDescriptorPool.h>
#include <VDescriptorSet.h>
#include <VTexture.h>
#include <VTextureSampler.h>
#include <VDepthBuffer.h>
#include <shader/VShader.h>

#include <vector>

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
        /// private_vars

        /// window width
        uint32                      _width                              {VulkanTriangleApplication::DEFAULT_WIDTH};
        /// window height
        uint32                      _height                             {VulkanTriangleApplication::DEFAULT_HEIGHT};

        /// window address
        GLFWwindow *                _window                             {nullptr};

        /// error callback messenger for GPU errors
        VMessenger                  _vulkanMessenger;
        /// collection of multiple validation layers
        VValidationLayerCollection  _vulkanValidationLayerCollection;
        /// vulkan instance
        VInstance                   _vulkanInstance;
        /// surface to print GPU images on
        VSurface                    _vulkanSurface;
        /// GPU handle and interfaces
        VPhysicalDevice             _vulkanPhysicalDevice;

        /// Address of Queue Families
        VQueueFamilyCollection    * _vulkanQueueFamilyCollection        {nullptr};
        /// GPU + CPU-GPU buses used + GPU-surface bus used interface
        VLogicalDevice              _vulkanLogicalDevice;

        /// Shader used for all objects
        VShader                     _objectShader;

        /// Frame Buffers used to draw on
        VFrameBufferCollection      _frameBufferCollection;

        /// Command Pool for Draw Commands
        VCommandPool                _commandPool;
        /// Command Pool for Transfer from GPU to Surface
        VCommandPool                _transferCommandPool;
        /// Command Buffer Storage
        VCommandBufferCollection    _drawCommandBufferCollection;

        /// All semaphores signaling image availability finish per image
        VSemaphoreCollection        _imageAvailableSemaphores;
        /// All semaphores signaling render finish of images per image
        VSemaphoreCollection        _renderFinishedSemaphores;

        /// Fences synchronising semaphores for image swapping and semaphore sync
        VFenceCollection            _inFlightFences;
        /// Fences synchronising semaphores for image swapping and semaphore sync
        VFenceCollection            _imagesInFlight;

        /// Descriptor Pool for Allocation of Descriptors ( Locations ) for Buffers on GPU and shared CPU-GPU Buffers
        VDescriptorPool             _descriptorPool;

        /// Texture Sampler Object.
        VTextureSampler             _textureSampler;
        /// Depth Buffer Object. Does depth testing - draws objects closer to the camera over objects further away
        VDepthBuffer                _depthBuffer;

        /// Active Scene - Hierarchy of Entities
        VScene                      _activeScene;

        /// Current FPS
        double                      _fpsTimer = 0.0;
        /// Show FPS every .... seconds
        double                      _fpsRefreshTimer = __SHOW_FPS_EVERY_S;
        /// Time Between start of draw and end of draw for last image
        double                      _deltaTime {0.0f};

        /// Used to recreate all resources using surface resolution when window is resized
        bool _framebufferResized {false};

        /// private_functions

        /**
         * @brief initialisation of settings ( resolution ... )
         * @exceptsafe
         */
        void initSettings() const noexcept;

        /**
         * @brief creation of window context
         * @throws engine::EngineVulkanTestException
         */
        void initWindow() noexcept(false);

        /**
         * @brief creation of vulkan instance
         * @throws std::runtime_error
         */
        void initVulkan() noexcept(false);

        /**
         * @brief start of MVC application
         * @brief std::runtime_error
         */
        void mainLoop() noexcept(false);

        /**
         * @brief cleanup of all data created
         * @exceptsafe
         */
        void cleanup() noexcept;

        /**
         * @brief Periodic call per frame for each object
         * @exceptsafe
         */
        void update() noexcept;

        /**
         * @brief Periodic call to draw a free image
         * @throws std::runtime_error
         */
        void drawImage() noexcept (false);

        /**
         * @brief creation of shaders - Deprecated. Will be built by Precompiler
         * @deprecated
         * @exceptsafe
         */
        inline void createShaderModules () noexcept {}

        /**
         * @brief creation of command pool - any draw commands, allocated from a pool ( cached on gpu )
         * @throws std::runtime_error
         */
        void createCommandPool() noexcept(false);

        /**
         * @brief  creation of command buffers - GPU draw commands, pre-recorder for optimisation
         * @throws std::runtime_error
         */
        void createCommandBuffers() noexcept (false);

        /**
         * @brief creation of CPU-GPU sync elements - semaphores, fences, barriers
         * @throws std::runtime_error
         */
        void createSynchronizationElements () noexcept (false);

        /**
         * @brief creation of frame buffers - drawable buffers
         * @throws std::runtime_error
         */
        void createFrameBuffers () noexcept (false);

        /**
         * @deprecated
         * @brief creation of layout of descriptors for CPU-GPU data - Deprecated. Will be build by Precompiler
         * @exceptsafe
         */
        inline void createDescriptorSetLayout() noexcept {}

        /**
         * @brief creation of graphical pipeline - A single Shader - ( GPU - queue - swapchain - screen )
         * @throws std::runtime_error
         */
        void createGraphicsPipeline() noexcept (false);

        /**
         * @brief Create a printable surface on the window for FrameBuffers
         * @throws std::runtime_error
         */
        void createSurface() noexcept (false);

        /**
         * @brief creation of texture objects - GPU data
         * @throws std::runtime_error
         */
        void createTextures() noexcept (false);

        /**
         * @brief Setup a Validation Layer Violation Error Callback
         * @throws std::runtime_error
         */
        void setupDebugMessenger() noexcept (false);

        /**
         * @brief Select Best GPU for the Engine
         * @throws std::runtime_error
         */
        void autoPickPhysicalDevice() noexcept (false);

        /**
         * @brief Will recreate swapchain for GPU
         * Recreation Occurs each time it is required
         * Recreation Triggers : Initial Creation, Window Resized, Pipeline Changed
         * @throws std::runtime_error
         */
        void recreateSwapChain () noexcept (false);

        /**
         * @brief creation of depth buffer
         * Depth Buffering/Testing - objects do not overlap. Objects closer to the camera will be rendered first
         * @throws std::runtime_error
         */
        void createDepthBuffer () noexcept (false);

        /**
         * @brief creation of Data Buffers - GPU - Vertex + Index + Uniform
         * @throws std::runtime_error
         */
        void createBuffers () noexcept (false);

        /**
         * @brief creation of Data Buffers with Exclusive Memory Usage
         * Used when one Queue Family is available capable of both Graphic and Present Transportation
         * @throws std::runtime_error
         */
        void createExclusiveBuffers () noexcept (false);

        /**
         * @brief  creation of Data Buffers with Concurrent Memory Usage
         * Used when multiple Queue Families are used, each capable of a different task - need access to same memory
         * @throws std::runtime_error
         */
        void createConcurrentBuffers () noexcept (false);

        /**
         * @brief creation of Data Buffers with CPU-GPU memory sharing
         * Examples : Model View Projection Matrix, Texture
         * @throws std::runtime_error
         */
        void createUniformBuffers () noexcept (false);

        /**
         * @brief creation of Descriptor Pool
         * Memory Area for Bindings and Location for Buffers sent to GPU
         * @throws std::runtime_error
         */
        void createDescriptorPool() noexcept (false);

        /**
         * @brief creation of Descriptor Sets
         * Bindings for one Object's Data sent to GPU
         * @throws std::runtime_error
         */
        void createDescriptorSets() noexcept (false);

        /**
         * @brief update of Uniform Buffer assigned for current image with object data
         * @param uniformBufferIndex : uint32 = index of assigned UniformBuffer for FrameBuffer
         * @exceptsafe
         */
        void updateUniformBuffer  ( uint32 ) noexcept;

        /**
         * @brief free of staging buffers - copy buffers for CPU-GPU. Deprecated
         * @deprecated
         * @exceptsafe
         */
        inline void freeStagingBuffers () noexcept {}

        /**
         * @brief cleanup of swapchain elements.
         * used when recreating swapchain, to clean previous swapchain
         * @exceptsafe
         */
        void cleanupSwapChain () noexcept;

        /**
         * @brief update of global resolution when window is resized
         * @exceptsafe
         */
        void updateResolutionSettings() noexcept;

        /**
         * @brief callback for window resize
         * @param pWindow : GLFWwindow * = address of the window that was resized
         * @param width : int32 = new width
         * @param height : int32 = new height
         * @exceptsafe
         */
        static void frameBufferResizeCallback ( GLFWwindow*, [[maybe_unused]] int32, int32 ) noexcept;

        /**
         * @brief creation of EC Game Object
         * @exceptsafe
         */
        auto createGameObjects () noexcept -> void;
    public:
        //// public_vars
        constexpr static uint32 DEFAULT_WIDTH       = 1024U;    //// starting width
        constexpr static uint32 DEFAULT_HEIGHT      = 768U;     //// starting height
        //// check extensions toggle
        constexpr static bool   VULKAN_EXT_CHECK    = _VK_CHECK_EXT;
        //// fps show toggle
        constexpr static bool   SHOW_FPS_CONSOLE    = true;

        //// default window title
        static const char *     DEFAULT_TITLE;

        //// public_functions

        /**
         * @brief Default Constructor
         * @exceptsafe
         */
        VulkanTriangleApplication() noexcept = default;
        /**
         * @brief Constructor with Window Width + Height
         * @exceptsafe
         */
        explicit VulkanTriangleApplication(uint32, uint32) noexcept;

        /**
         * @brief Getter for Validation Layer Collection
         * @exceptsafe
         * @return VValidationLayerCollection ref
         */
        [[nodiscard]] VValidationLayerCollection & getValidationLayerCollection() noexcept {
            return this->_vulkanValidationLayerCollection;
        }

        /**
         * @brief Function used to add a Validation Layer to the used Layers
         * @param layer : engine::VValidationLayer cref = constant reference to the layer to be added
         * @exceptsafe
         * @return VulkanTriangleApplication ref = reference to this object
         */
        VulkanTriangleApplication & addValidationLayer ( const engine::VValidationLayer & layer ) noexcept {
            this->_vulkanValidationLayerCollection.addValidationLayer(layer );
            return *this;
        }

        /**
         * @brief Function used to add a Validation Layer to the used Layers
         * @param layerType : engine::VValidationLayer::VulkanValidationLayer = layer type to add
         * @exceptsafe
         * @return VulkanTriangleApplication ref = reference to this object
         */
        VulkanTriangleApplication & addValidationLayer ( engine::VValidationLayer::VulkanValidationLayer layerType ) noexcept {
            this->_vulkanValidationLayerCollection.addValidationLayer( engine::VValidationLayer().setLayerType(layerType) );
            return *this;
        }

        /**
         * @brief Function used to add Validation Layers to the used Layers
         * @param layerCollection : engine::VValidationLayerCollection cref = layer collection to add
         * @exceptsafe
         * @retrun VulkanTriangleApplication ref = reference to object
         */
        VulkanTriangleApplication & addValidationLayers( const engine::VValidationLayerCollection & layerCollection ) noexcept {
            for( const auto & layer : layerCollection.getValidationLayers() ) {
                this->_vulkanValidationLayerCollection.addValidationLayer(layer );
            }
            return *this;
        }

        /**
         * @brief Clears Validation Layers
         * @exceptsafe
         * @return VulkanTriangleApplication ref = reference to object
         */
        VulkanTriangleApplication & clearValidationLayers() noexcept {
            this->_vulkanValidationLayerCollection.clear();
            return *this;
        }

        /**
         * @brief Starts the engine, giving control to the VulkanTriangleApplication instance
         * @throws std::runtime_error
         */
        void run() noexcept (false);
    };

}


#endif //ENG1_VULKANTRIANGLEAPPLICATION_H

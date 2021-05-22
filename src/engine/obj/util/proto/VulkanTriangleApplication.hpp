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

#include <engineVulkanPreproc.hpp>
#include <vulkanExplicitTypes.h>
#include <VValidationLayer.hpp>
#include <VInstance.hpp>
#include <VMessenger.hpp>
#include <VPhysicalDevice.hpp>
#include <VLogicalDevice.hpp>
#include <VSurface.hpp>
#include <VFrameBuffer.hpp>
#include <VCommandBuffer.hpp>
#include <VSemaphore.hpp>
#include <VFence.hpp>
#include <VVertex.hpp>
#include <VUniformBuffer.hpp>
#include <VDescriptorPool.hpp>
#include <VDescriptorSet.hpp>
#include <VTexture.hpp>
#include <VTextureSampler.hpp>
#include <VDepthBuffer.hpp>
#include <shader/VShader.hpp>

#include <vector>

#include <VGameObject.hpp>

#include <scene/VScene.hpp>

namespace engine {

    /**
     * @class engine::EngineVulkanTestException, inherits std::exception
     *
     * @brief Exception type thrown when an engine internal test fails
     */
    class EngineVulkanTestException : public std::exception {
    private:
        /// Exception message
        std::string message = "Exception thrown!";
    public:
        /**
         * @brief Constructor with message
         *
         * @param msg : std::string cref = message to be attached to exception
         *
         * @exceptsafe
         */
        [[maybe_unused]] explicit EngineVulkanTestException(std::string const & msg) noexcept {
            this->message = msg;
        }

        /**
         * @brief getter for the Exception Message
         *
         * @exceptsafe
         *
         * @return StringLiteral = Exception Message
         */
        [[nodiscard]] auto what() const noexcept -> StringLiteral override {
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


        HashMap < VGameObject *, std::vector < VVertex > const * >  _objectVertices;
        HashMap < VGameObject *, std::vector < uint16 > const * >   _objectIndices;
        HashMap < VGameObject *, String >                           _objectTextureNames;

        bool                        _mouseCursorEnabled = false;

        /// Current FPS
        double                      _fpsTimer = 0.0;
        /// Show FPS every .... seconds
        double                      _fpsRefreshTimer = __SHOW_FPS_EVERY_S;
        /// Time Between start of draw and end of draw for last image
        double                      _deltaTime {0.0f};

        bool                        _showFPS {false};

        /// Used to recreate all resources using surface resolution when window is resized
        bool                        _framebufferResized {false};

        /// private_functions

        /**
         * @brief initialisation of settings ( resolution ... )
         *
         * @exceptsafe
         */
        auto initSettings() const noexcept -> void;

        /**
         * @brief creation of window context
         *
         * @throws engine::EngineVulkanTestException if GLFW could not initialise
         */
        auto initWindow() noexcept(false) -> void;

        /**
         * @brief creation of vulkan instance
         *
         * @throws std::runtime_error if
         *      enableValidationLayers == true AND (
         *          requested layers are not available OR
         *          failed to create vulkan instance with layers
         *      ) OR
         *      failed to create vulkan instance without layers
         */
        auto initVulkan() noexcept(false) -> void;

        /**
         * @brief start of MVC application
         *
         * @throws std::runtime_error if
         *      drawImage throws exception
         */
        auto mainLoop() noexcept(false) -> void;

        /**
         * @brief cleanup of all data created
         *
         * @exceptsafe
         */
        auto cleanup() noexcept -> void;

        /**
         * @brief Periodic call per frame for each object
         *
         * @exceptsafe
         */
        auto update() noexcept -> void;

        /**
         * @brief Periodic call to draw a free image
         *
         * @throws std::runtime_error if
         *      Cannot Acquire Image from SwapChain OR
         *      Submit Draw Command to GPU fails OR
         *      Image Present to Surface fails
         */
        auto drawImage() noexcept (false) -> void;

        /**
         * @brief creation of shaders - Deprecated. Will be built by Precompiler
         *
         * @deprecated
         *
         * @exceptsafe
         */
        inline auto createShaderModules () noexcept -> void {}

        /**
         * @brief creation of command pool - any draw commands, allocated from a pool ( cached on gpu )
         *
         * @throws std::runtime_error if
         *      Command Pool cannot be created
         *      Command Pool Dedicated for transfers cannot be created
         */
        auto createCommandPool() noexcept(false) -> void;

        /**
         * @brief  creation of command buffers - GPU draw commands, pre-recorder for optimisation
         *
         * One Draw Command is Ideally created for one Shader Pipeline, containing all objects
         * rendered with that Shader
         *
         * Worst case : one Draw Buffer per Object
         *
         * @throws std::runtime_error if
         *      Cannot allocate Command Buffers in Command Pool
         *      Cannot record Command Buffers
         */
        auto createCommandBuffers() noexcept (false) -> void;

        /**
         * @brief creation of CPU-GPU sync elements - semaphores, fences, barriers
         *
         * @throws std::runtime_error if
         *      Semaphore Collection creation for Image Availability fails OR
         *      Semaphore Collection creation for Render Finishing fails OR
         *      Fence Collection creation for in flight fences fails
         */
        auto createSynchronizationElements () noexcept (false) -> void;

        /**
         * @brief creation of frame buffers - drawable buffers
         *
         * @throws std::runtime_error if
         *      Frame Buffers cannot be created
         */
        auto createFrameBuffers () noexcept (false) -> void;

        /**
         * @deprecated
         *
         * @brief creation of layout of descriptors for CPU-GPU data - Deprecated. Will be build by Precompiler
         *
         * @exceptsafe
         */
        inline auto createDescriptorSetLayout() noexcept -> void {}

        /**
         * @brief creation of graphical pipeline - A single Shader - ( GPU - queue - swapchain - screen )
         *
         * @throws std::runtime_error if
         *      Shader Creation fails
         */
        auto createGraphicsPipeline() noexcept (false) -> void;

        /**
         * @brief Create a printable surface on the window for FrameBuffers
         *
         * @throws std::runtime_error if
         *      Surface could not be created
         */
        auto createSurface() noexcept (false) -> void;

        /**
         * @brief creation of texture sampler - GPU filter and acquisition tool for images
         *
         * @throws std::runtime_error if
         *      Texture Sampler fails to create
         */
        auto createTextureSampler () noexcept (false) -> void;

        /**
         * @brief Setup a Validation Layer Violation Error Callback
         *
         * @throws std::runtime_error if
         *      Messenger Creation Fails
         */
        auto setupDebugMessenger() noexcept (false) -> void;

        /**
         * @brief Select Best GPU for the Engine
         *
         * @throws std::runtime_error if
         *      no GPU than can support Vulkan is found
         */
        auto autoPickPhysicalDevice() noexcept (false) -> void;

        /**
         * @brief Will recreate swapchain for GPU
         *
         * Recreation Occurs each time it is required
         * Recreation Triggers : Initial Creation, Window Resized, Pipeline Changed
         *
         * @throws std::runtime_error if
         *      SwapChain on GPU could not recreate itself OR
         *      shader and pipeline recreation fails OR
         *      recreation of depth buffer fails OR
         *      recreation of frame buffers fails OR
         *      recreation of descriptors fails OR
         *      recreation of command buffers fails
         */
        auto recreateSwapChain () noexcept (false) -> void;

        /**
         * @brief creation of depth buffer
         *
         * Depth Buffering/Testing - objects do not overlap. Objects closer to the camera will be rendered first
         *
         * @throws std::runtime_error if
         *      Depth Buffer Creation Fails
         */
        auto createDepthBuffer () noexcept (false) -> void;

        /**
         * @brief creation of Data Buffers - GPU - Vertex + Index + Uniform
         *
         * @throws std::runtime_error if
         *      createExclusiveBuffers() throws OR
         *      createConcurrentBuffers() throws
         */
        auto createBuffers () noexcept (false) -> void;

        /**
         * @brief creation of Data Buffers with Exclusive Memory Usage
         *
         * Used when one Queue Family is available capable of both Graphic and Present Transportation
         *
         * @throws std::runtime_error
         *      always. Not Implemented
         */
        auto createExclusiveBuffers () noexcept (false) -> void;

        /**
         * @brief  creation of Data Buffers with Concurrent Memory Usage
         *
         * Used when multiple Queue Families are used, each capable of a different task - need access to same memory
         *
         * @throws std::runtime_error if
         *      A Mesh fails to be loaded onto GPU
         */
        auto createConcurrentBuffers () noexcept (false) -> void;

        /**
         * @brief creation of Data Buffers with CPU-GPU memory sharing
         *
         * Examples : Model View Projection Matrix, Texture
         *
         * @throws std::runtime_error if
         *      createDescriptorPool () throws OR
         *      createDescriptorSets () throws
         */
        auto createUniformBuffers () noexcept (false) -> void;

        /**
         * @brief creation of Descriptor Pool
         *
         * Memory Area for Bindings and Location for Buffers sent to GPU
         *
         * @throws std::runtime_error if
         *      Descriptor Pool fails to create
         */
        auto createDescriptorPool() noexcept (false) -> void;

        /**
         * @brief creation of Descriptor Sets
         *
         * Bindings for one Object's Data sent to GPU
         *
         * @throws std::runtime_error if
         *      One Mesh Renderer fails to create
         */
        auto createDescriptorSets() noexcept (false) -> void;

        /**
         * @brief update of Uniform Buffer assigned for current image with object data
         *
         * @param uniformBufferIndex : uint32 = index of assigned UniformBuffer for FrameBuffer
         *
         * @exceptsafe
         */
        auto updateUniformBuffer  ( uint32 ) noexcept -> void;

        /**
         * @brief free of staging buffers - copy buffers for CPU-GPU. Deprecated
         *
         * @deprecated
         *
         * @exceptsafe
         */
        inline auto freeStagingBuffers () noexcept -> void {}

        /**
         * @brief cleanup of swapchain elements.
         *
         * used when recreating swapchain, to clean previous swapchain
         *
         * @exceptsafe
         */
        auto cleanupSwapChain () noexcept -> void;

        /**
         * @brief update of global resolution when window is resized
         *
         * @exceptsafe
         */
        auto updateResolutionSettings() noexcept -> void;

        /**
         * @brief callback for window resize
         *
         * @param pWindow : GLFWwindow * = address of the window that was resized
         * @param width : int32 = new width
         * @param height : int32 = new height
         *
         * @static
         *
         * @exceptsafe
         */
        static auto frameBufferResizeCallback ( GLFWwindow*, [[maybe_unused]] int32, int32 ) noexcept -> void;

        /**
         * @brief creation of EC Game Object
         *
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
//        constexpr static bool   SHOW_FPS_CONSOLE    = false;

        //// default window title
        static const char *     DEFAULT_TITLE;

        //// public_functions

        /**
         * @brief Default Constructor
         *
         * @exceptsafe
         */
        VulkanTriangleApplication() noexcept = default;
        /**
         * @brief Constructor with Window Width + Height
         *
         * @exceptsafe
         */
        explicit VulkanTriangleApplication(uint32, uint32) noexcept;

        /**
         * @brief Getter for Validation Layer Collection
         *
         * @exceptsafe
         *
         * @return VValidationLayerCollection ref
         */
        [[nodiscard]] auto getValidationLayerCollection() noexcept -> VValidationLayerCollection & {
            return this->_vulkanValidationLayerCollection;
        }

        /**
         * @brief Function used to add a Validation Layer to the used Layers
         *
         * @param layer : engine::VValidationLayer cref = constant reference to the layer to be added
         *
         * @exceptsafe
         *
         * @return VulkanTriangleApplication ref = reference to this object
         */
        auto addValidationLayer ( engine::VValidationLayer const & layer ) noexcept -> VulkanTriangleApplication & {
            this->_vulkanValidationLayerCollection.addValidationLayer(layer );
            return *this;
        }

        /**
         * @brief Function used to add a Validation Layer to the used Layers
         *
         * @param layerType : engine::VValidationLayer::VulkanValidationLayer = layer type to add
         *
         * @exceptsafe
         *
         * @return VulkanTriangleApplication ref = reference to this object
         */
        auto addValidationLayer ( engine::VValidationLayer::VulkanValidationLayer layerType ) noexcept -> VulkanTriangleApplication & {
            this->_vulkanValidationLayerCollection.addValidationLayer( engine::VValidationLayer().setLayerType(layerType) );
            return *this;
        }

        /**
         * @brief Function used to add Validation Layers to the used Layers
         *
         * @param layerCollection : engine::VValidationLayerCollection cref = layer collection to add
         *
         * @exceptsafe
         *
         * @retrun VulkanTriangleApplication ref = reference to object
         */
        auto addValidationLayers( const engine::VValidationLayerCollection & layerCollection ) noexcept -> VulkanTriangleApplication & {
            for( const auto & layer : layerCollection.getValidationLayers() ) {
                this->_vulkanValidationLayerCollection.addValidationLayer(layer );
            }
            return *this;
        }

        /**
         * @brief Clears Validation Layers
         *
         * @exceptsafe
         *
         * @return VulkanTriangleApplication ref = reference to object
         */
        auto clearValidationLayers() noexcept -> VulkanTriangleApplication & {
            this->_vulkanValidationLayerCollection.clear();
            return *this;
        }

        /**
         * @brief Starts the engine, giving control to the VulkanTriangleApplication instance
         *
         * Function should not return until game window is closed
         *
         * @throws std::runtime_error if
         *      initWindow () throws                    OR
         *      initVulkan () throws                    OR
         *      createGraphicsPipeline () throws        OR
         *      createCommandPool () throws             OR
         *      createDepthBuffer () throws             OR
         *      createFrameBuffers () throws            OR
         *      createTextureSampler () throws          OR
         *      createBuffers () throws                 OR
         *      createCommandBuffers () throws          OR
         *      createSynchronizationElements () throws OR
         *      mainLoop () throws
         */
        auto run() noexcept (false) -> void;

        constexpr auto scene() noexcept -> VScene & { return this->_activeScene; }

        constexpr auto objectVertices () noexcept -> HashMap < VGameObject *, std::vector < VVertex > const * > & { return this->_objectVertices; }
        constexpr auto objectIndices () noexcept -> HashMap < VGameObject *, std::vector < uint16 > const * > & { return this->_objectIndices; }
        constexpr auto objectTextureNames () noexcept -> HashMap < VGameObject *, String > & { return this->_objectTextureNames; }

        constexpr auto setMouseCursorEnabled (bool toggle) noexcept -> void { this->_mouseCursorEnabled = toggle; }

        constexpr auto setShowFPSEnabled (bool toggle) noexcept -> void { this->_showFPS = toggle; }
        constexpr auto enableShowFPS () noexcept -> void { this->setShowFPSEnabled(true); }
        constexpr auto disableShowFPS () noexcept -> void { this->setShowFPSEnabled(false); }
        constexpr auto isFPSShown () const noexcept -> bool { return this->_showFPS; }
    };

}


#endif //ENG1_VULKANTRIANGLEAPPLICATION_H

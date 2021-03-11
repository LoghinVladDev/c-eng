//
// Created by vladl on 05/08/2020.
//

#include "VulkanTriangleApplication.h"
#include <VStdUtils.h>
#include <VStdUtilsDefs.h>
#include <map>
#include <SettingsSharedContainer.h>
#include <SettingOptionGraphics.h>

constexpr uint32 MAX_FRAMES_IN_FLIGHT = 2U;
const char* engine::VulkanTriangleApplication::DEFAULT_TITLE = "Vulkan Application";

uint32 currentFrame = 0U;

engine::VulkanTriangleApplication::VulkanTriangleApplication(uint32 width, uint32 height) noexcept :
    _width(width),
    _height(height){

}

static void queueFamilyTests ( const engine::VQueueFamilyCollection & collection ) noexcept {
    std::cout << "Available Queue Families : \n";

#ifndef NDEBUG
    collection.debugPrintQueueFamilies( std::cout, "\t" );
#endif

    std::cout << "Graphics Capable Queue Families on Device : \n";

#ifndef NDEBUG
    for ( const auto & queueFamily : collection.getGraphicsCapableQueueFamilies() ) {
        queueFamily->debugPrintQueueFamily(std::cout, "\t");
    }
#endif

#ifndef NDEBUG
    collection.debugPrintQueueFamiliesReservations( std::cout );
#endif

    for ( const auto & queueFamily : collection.getQueueFamilies() ) {
        uint32 reservationTarget = 4U;
        uint32 reservations = queueFamily.reserveQueues(reservationTarget);

        std::cout << "Managed to reserve " << reservations << " out of " << reservationTarget << " requested\n";
    }

#ifndef NDEBUG
    collection.debugPrintQueueFamiliesReservations( std::cout );
#endif

    const auto & selectedQueueFamily = collection.getQueueFamilies()[0];

    uint32 queuesToFree = 2U;

    std::cout << "Attempting to free " << queuesToFree << " queues from family with index " << selectedQueueFamily.getQueueFamilyIndex() << '\n';
    selectedQueueFamily.freeQueues(queuesToFree);

    for ( const auto & queueFamily : collection.getQueueFamilies()){
        uint32 reservationTarget = 8U;
        uint32 reservations = queueFamily.reserveQueues(reservationTarget);

        std::cout << "Managed to reserve " << reservations << " out of " << reservationTarget << " requested\n";
    }

    std::cout << "Freeing back all queues :\n";
    for ( const auto & queueFamily : collection.getQueueFamilies() ) {
        queueFamily.freeQueues( queueFamily.getQueueCount() );
    }

#ifndef NDEBUG
    collection.debugPrintQueueFamiliesReservations( std::cout );
#endif
}

#if !defined(_MSC_VER)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"
#pragma ide diagnostic ignored "UnreachableCode"
#endif
void engine::VulkanTriangleApplication::setupDebugMessenger() noexcept (false) {

    if ( ! enableValidationLayers ) return;

    VulkanResult res;

    if( ( res = this->_vulkanMessenger.setup ( & this->_vulkanInstance ) ) != VK_SUCCESS ) {
        throw std::runtime_error("debug messenger setup failure : " + engine::VStandardUtils::to_string(res));
    }
}
#if !defined(_MSC_VER)
#pragma clang diagnostic pop
#endif

void engine::VulkanTriangleApplication::initSettings() const noexcept {
    auto resolution = engine::ResolutionSetting( this->_width, this->_height ); //// Create Resolution Setting based on current resolution from Class Variables

    engine::SettingsSharedContainer::getInstance().put( & resolution ); //// Save Resolution for reuse later in other classes
}

void engine::VulkanTriangleApplication::updateResolutionSettings() noexcept {
    int width = 0, height = 0;
    glfwGetFramebufferSize( this->_window, & width, & height );
    while ( width == 0 || height == 0 ) {
        glfwGetFramebufferSize( this->_window, & width, & height );
        glfwWaitEvents();
    }

    auto resolution = engine::ResolutionSetting( width, height );

    engine::SettingsSharedContainer::getInstance().put( & resolution );
}

void engine::VulkanTriangleApplication::createDescriptorSetLayout() noexcept(false) {
}

void engine::VulkanTriangleApplication::run() noexcept (false) {
    this->initSettings();                   //// initialisation of settings ( resolution ... )
    this->initWindow();                     //// creation of window context
    this->initVulkan();                     //// creation of vulkan instance
    this->createShaderModules();            //// creation of shaders - Deprecated. Will be built by Precompiler
    this->createDescriptorSetLayout();      //// creation of layout of descriptors for CPU-GPU data - Deprecated. Will be build by Precompiler
    this->createGraphicsPipeline();         //// creation of graphical pipeline - A single Shader - ( GPU - queue - swapchain - screen )
    this->createCommandPool();              //// creation of command pool - any draw commands, allocated from a pool ( cached on gpu )
    this->createDepthBuffer();              //// creation of depth buffer - so that objects do not overlap. Objects closer to the camera will be rendered first
    this->createFrameBuffers();             //// creation of frame buffers - drawable buffers
    this->createTextures();                 //// creation of texture objects - GPU data
    this->createGameObjects();              //// creation of EC Game Objects
    this->createBuffers();                  //// creation of Data Buffers - GPU - Vertex + Index + Uniform.
    this->createCommandBuffers();           //// creation of command buffers - GPU draw commands, pre-recorder for optimisation
    this->freeStagingBuffers();             //// free of staging buffers - copy buffers for CPU-GPU. Deprecated
    this->createSynchronizationElements();  //// creation of CPU-GPU sync elements - semaphores, fences, barriers
    this->mainLoop();                       //// start of MVC application
    this->cleanup();                        //// cleanup of all data created
}

void processInputCallback (GLFWwindow*, int, int, int, int);

inline void engine::VulkanTriangleApplication::initWindow() noexcept (false) {
    if(glfwInit() == GLFW_FALSE) {
        throw engine::EngineVulkanTestException("GLFW Init failure"); //// if GLFW could not initialise, we cannot draw on a window
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); //// No OpenGL API, Vulkan is not self-configurable

    this->_window = glfwCreateWindow( //// Create Window from GLFW
        this->_width,
        this->_height,
        VulkanTriangleApplication::DEFAULT_TITLE,
        nullptr,
        nullptr
    );

    glfwSetWindowUserPointer( this->_window, this ); //// Enable Cursor Interaction
    glfwSetFramebufferSizeCallback( this->_window, engine::VulkanTriangleApplication::frameBufferResizeCallback ); //// Set Window Resize Callback
    glfwSetKeyCallback( this->_window, processInputCallback ); //// Set Keyboard Callback
}

void engine::VulkanTriangleApplication::createSurface() noexcept(false) {
    if( this->_vulkanSurface.setup(this->_window, this->_vulkanInstance) != VK_SUCCESS )
        throw std::runtime_error("failed to create vulkan surface");
}

static inline std::vector < const engine::VQueueFamily* > internalGatherGraphicsAndPresentQueueFamilies( const engine::VQueueFamilyCollection& collection ) noexcept {
    auto queueFamilies = collection.getFlagsCapableQueueFamilies( engine::VQueueFamily::GRAPHICS_FLAG | engine::VQueueFamily::PRESENT_FLAG | engine::VQueueFamily::TRANSFER_FLAG );

    if( queueFamilies.empty() ) {

        queueFamilies.push_back( collection.getGraphicsCapableQueueFamilies()[0] );
        queueFamilies.push_back( collection.getPresentCapableQueueFamilies()[0] );
    }

    return queueFamilies;
}

#if !defined(_MSC_VER)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"
#pragma ide diagnostic ignored "UnreachableCode"
#endif
inline void engine::VulkanTriangleApplication::initVulkan() noexcept (false) {
    VExtensionCollection availableExtensions = VExtensionCollection::getAllAvailableExtensions(); //// Acquire supported Vulkan SDK Extensions

#ifndef NDEBUG
    if( VulkanTriangleApplication::VULKAN_EXT_CHECK ) // in debug, print extensions
        availableExtensions.debugPrint(std::cout );
#endif

    if( enableValidationLayers ) { // enabled in debug, disabled in release
        VValidationLayer::debugPrintAvailableValidationLayers(std::cout);

        std::cout << "\nRequested Validation Layers : \n";

        for( const auto & layer : this->_vulkanValidationLayerCollection.getValidationLayers() ) {
            std::cout << '\t' << layer.getLiteral() << '\n';
        }

        if( ! VValidationLayer::checkValidationLayerSupport(this->_vulkanValidationLayerCollection) ) {
            throw std::runtime_error("requested validation layers are not available!");
        }

        std::cout << "\nRequested Layers are available!\n";

        /// Initialise Vulkan WITH Validation Layers
        if ( this->_vulkanInstance.setup( this->_vulkanValidationLayerCollection ) != VK_SUCCESS ) {
            throw std::runtime_error ("failed to create Vulkan instance");
        }
    } else {
        /// Initialise Vulkan WITHOUT Validation Layers
        if ( this->_vulkanInstance.setup() != VK_SUCCESS )
            throw std::runtime_error ("failed to create Vulkan instance");
    }


    this->setupDebugMessenger(); //// Setup a Validation Layer Violation Error Callback
    this->createSurface();  //// Create a printable surface on the window for ImageBuffers
    this->autoPickPhysicalDevice(); //// Select Best GPU for the Engine

    std::cout << "Most Suitable GPU : \n";

#ifndef NDEBUG
    this->_vulkanPhysicalDevice.debugPrintPhysicalDeviceProperties( std::cout, true, "\t"); /// In debug, print best GPU
#endif

    /// Acquire Queue Families
    this->_vulkanQueueFamilyCollection = new VQueueFamilyCollection ( this->_vulkanPhysicalDevice, &this->_vulkanSurface );

    //// Do basic tests for Queue Allocation
    queueFamilyTests( * this->_vulkanQueueFamilyCollection );

    engine::VLogicalDevice::VLogicalDeviceFactory::enableExceptions();
    engine::VLogicalDevice::VLogicalDeviceFactory deviceFactory; /// Factory For Logical Device. Logical Device =
    ////                                              Physical Device (GPU) +
    ////                                              Queues Interface (CPU-GPU buses)
    ////                                              Swapchain Interface (GPU - Surface buses)

    //// If using validationLayers, build Logical Device + Validation Layers. We need the callbacks on the GPU
    if( enableValidationLayers )
        deviceFactory.withValidationLayers( this->_vulkanValidationLayerCollection );

    //// Gather CPU-GPU Buses capable of
    ///         Graphic Transfers ( Vertex, Index, Texture, Compression etc )
    ///         Present Transfers ( GPU Image -> Window Surface )
    auto queues = internalGatherGraphicsAndPresentQueueFamilies ( * this->_vulkanQueueFamilyCollection );

    if( queues.size() == 1 ) { // graphics & present queues in same family
    //// if only one queue capable of Graphics + Present, use exclusivity of memory for one queue family
        deviceFactory.addQueue(*queues[0], 1.0f);
        deviceFactory.addQueue(* this->_vulkanQueueFamilyCollection->getTransferCapableQueueFamilies()[0], 1.0f);
    }
    else {
    //// if one graphics and one present queue have been found, use concurrency of memory for both queue families
        deviceFactory.addQueue( * queues[0], 1.0f );
        deviceFactory.addQueue( * queues[1], 1.0f );
        deviceFactory.addQueue(* this->_vulkanQueueFamilyCollection->getTransferCapableQueueFamilies()[0], 1.0f);
    }

    //// Link to-be-created SwapChain to the Surface Created Previously
    deviceFactory.createSwapChainToSurface( & this->_vulkanSurface );
//
    this->_vulkanLogicalDevice = deviceFactory.build( this->_vulkanPhysicalDevice ); /// Build Logical Device
    std::cout << "Logical Device Handle : " << this->_vulkanLogicalDevice.data() << '\n';
//
//
    std::cout << "Queues : \n";
    for(const auto & queue : this->_vulkanLogicalDevice.getQueues()) {
        std::cout << "\tQueue :\n";
        std::cout << "\t\tHandler : " << queue.data() << "\n";
        std::cout << "\t\tFamily index : " << queue.getQueueFamily()->getQueueFamilyIndex() << '\n';
        std::cout << "\t\tIndex in Family : " << queue.getIndex() << '\n';
        std::cout << "\t\tPriority : " << queue.getPriority() << '\n';
    }

    std::cout << "Device Capable of Swapchain Ext : " << this->_vulkanPhysicalDevice.supportsExtension ( VExtension( VExtension::KHRONOS_SWAPCHAIN ) ) << '\n';

    std::cout << "Logical Device Capable of Swap Chain : " << this->_vulkanLogicalDevice.isSwapChainAdequate() << '\n';

    auto setting = engine::SettingsSharedContainer::getInstance().get(engine::SettingOption::RESOLUTION);

    if(setting != nullptr ) {
        auto resolution = dynamic_cast < const engine::ResolutionSetting* > ( setting );

        if ( resolution != nullptr ) {
            std::cout << "Saved res : " << resolution->getWidth() << ',' << resolution->getHeight() << '\n';
        }
    }
}

void engine::VulkanTriangleApplication::freeStagingBuffers() noexcept(false) {

}

void engine::VulkanTriangleApplication::createSynchronizationElements() noexcept(false) {
    //// A semaphore for image draw finish per frame buffer
    if ( this->_imageAvailableSemaphores.setup( this->_vulkanLogicalDevice, MAX_FRAMES_IN_FLIGHT ) != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ( "Semaphore Creation Failure : Image Availability" );
    //// A semaphore for each render on surface per each frame buffer
    if ( this->_renderFinishedSemaphores.setup( this->_vulkanLogicalDevice, MAX_FRAMES_IN_FLIGHT ) != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ( "Semaphore Creation Failure : Render Finish" );

    //// Fences for synchronising semaphores and Logical Device busy scheduling. One per frame
    if ( this->_inFlightFences.setup( this->_vulkanLogicalDevice, MAX_FRAMES_IN_FLIGHT, engine::VFence::START_SIGNALED ) != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ( "Fence Creation Failure" );
    this->_imagesInFlight.resize( static_cast<uint32>(this->_vulkanLogicalDevice.getSwapChain()->getImages().size()) );
}

#if !defined(_MSC_VER)
#pragma clang diagnostic pop
#endif

auto engine::VulkanTriangleApplication::createGameObjects() noexcept -> void {
    /***
     * Create Two Objects and Add them to the Active Scene
     * Will be loaded later from configurations - Saved Scenes -> json containing hierarchical data
     */

    auto cube = new VGameObject("cube");
    cube->add(new VTransform());
    cube->add(new VMesh());
    cube->add(new VMeshRenderer());

    auto star = new VGameObject("star");
    star->add(new VTransform());
    star->add(new VMesh());
    star->add(new VMeshRenderer());

    /// Move the star a bit above and to the left
    star->transformPtr()->getLocation().x += 1.0f;
    star->transformPtr()->getLocation().z += 1.0f;

    this->_activeScene.add(cube);
    this->_activeScene.add(star); /// Add object to scene
}

/**
 * Will recreate in flight
 */
void engine::VulkanTriangleApplication::recreateSwapChain() noexcept(false) {
    vkDeviceWaitIdle( this->_vulkanLogicalDevice.data() );

    this->cleanupSwapChain();

    this->updateResolutionSettings();

    if ( this->_vulkanLogicalDevice.recreateSwapChain() != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ( "Swap Chain Recreation Error" );

    ENG_THROW_IF_NOT_SUCCESS (
            this->_objectShader.recreateShader(),
            ENG_STD_THROW( "shader recreation failure" )
    )


    this->createDepthBuffer();
    this->createFrameBuffers();

    this->createDescriptorPool();

    for ( auto * pComponent : this->_activeScene.componentsOfClass("VMeshRenderer") )
        dynamic_cast<VMeshRenderer *>(pComponent)->recreate();

    this->createCommandBuffers();
}

void engine::VulkanTriangleApplication::cleanupSwapChain() noexcept(false) {
    this->_depthBuffer.cleanup();
    this->_frameBufferCollection.cleanup();
    this->_drawCommandBufferCollection.free();

    for ( auto * pComponent : this->_activeScene.componentsOfClass("VMeshRenderer") )
        dynamic_cast<VMeshRenderer *>(pComponent)->cleanupUniformBuffers();

    this->_descriptorPool.cleanup();

    this->_objectShader.getPipeline().cleanup();

    this->_vulkanLogicalDevice.cleanupSwapChain();
}



void engine::VulkanTriangleApplication::frameBufferResizeCallback(GLFWwindow * pWindow, [[maybe_unused]] int32 width, [[maybe_unused]] int32 height) {
    auto * baseObj = reinterpret_cast< engine::VulkanTriangleApplication * > ( glfwGetWindowUserPointer( pWindow ) );
    baseObj->_framebufferResized = true;
}

void engine::VulkanTriangleApplication::drawImage () noexcept (false) {
    vkWaitForFences(
        this->_vulkanLogicalDevice.data(),
        1U,
        & this->_inFlightFences[ currentFrame ].data(),
        VK_TRUE,
        UINT64_MAX
    );

    uint32 imageIndex;
    VulkanResult acquireImageResult = vkAcquireNextImageKHR(
        this->_vulkanLogicalDevice.data(),
        this->_vulkanLogicalDevice.getSwapChain()->data(),
        UINT64_MAX,
        this->_imageAvailableSemaphores[ currentFrame ].data(),
        VK_NULL_HANDLE,
        & imageIndex
    );

    if ( acquireImageResult == VulkanResult::VK_ERROR_OUT_OF_DATE_KHR ) {
        this->recreateSwapChain();
        return;
    } else if ( acquireImageResult != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ( "Image Acquisition Failure" );

    if ( ! this->_imagesInFlight [ imageIndex ].empty() ) {
        vkWaitForFences(
            this->_vulkanLogicalDevice.data(),
            1U,
            & this->_imagesInFlight[ imageIndex ].data(),
            VK_TRUE,
            UINT64_MAX
        );
    }

    this->updateUniformBuffer( imageIndex );

    this->_imagesInFlight[ imageIndex ] = this->_inFlightFences [ currentFrame ];

    VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

    if ( this->_drawCommandBufferCollection.getCommandBuffers()[ imageIndex ].submit(
            waitStages,
            & this->_imageAvailableSemaphores[ currentFrame ],
            1U,
            & this->_renderFinishedSemaphores[ currentFrame ],
            1U,
            & this->_inFlightFences[ currentFrame ]
        ) != VulkanResult::VK_SUCCESS
    )
        throw std::runtime_error ( "Command Buffer Submit Failure" );

    VulkanResult presentResult = this->_vulkanLogicalDevice.getSwapChain()->present(
            & this->_renderFinishedSemaphores[ currentFrame ],
            1U, imageIndex
    );

    if (
        presentResult == VulkanResult::VK_ERROR_OUT_OF_DATE_KHR ||
        presentResult == VulkanResult::VK_SUBOPTIMAL_KHR ||
        this->_framebufferResized
    ) {
        this->_framebufferResized = false;
        this->recreateSwapChain();
    }
    else if ( presentResult != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ( "Swap Chain Present Failure" );

    currentFrame = ( currentFrame + 1 ) % MAX_FRAMES_IN_FLIGHT;
}

const std::vector < engine::VVertex > starVertices = {

        { { -0.2f, -0.2f, 0.0f }, {0.3f, 0.3f, 0.3f} },
        { {  0.2f, -0.2f, 0.0f }, {0.3f, 0.3f, 0.3f} },
        { {  0.3f,  0.1f, 0.0f }, {0.3f, 0.3f, 0.3f} },
        { {  0.0f,  0.3f, 0.0f }, {0.3f, 0.3f, 0.3f} },
        { { -0.3f,  0.1f, 0.0f }, {0.3f, 0.3f, 0.3f} },

        { { 0.0f, -0.6f, 0.0f }, {1.0f, 0.0f, 0.0f} },
        { { 0.6f, -0.2f, 0.0f }, {0.0f, 1.0f, 0.0f} },
        { { 0.4f,  0.55f, 0.0f }, {0.0f, 0.0f, 1.0f} },
        { {-0.4f,  0.55f, 0.0f }, {0.0f, 1.0f, 1.0f} },
        { {-0.6f, -0.2f, 0.0f }, {1.0f, 1.0f, 0.3f} },
};

const std::vector < uint16 > starIndices = {

        0, 1, 4,
        1, 3, 4,
        1, 2, 3,

        0, 5, 1,
        1, 6, 2,
        2, 7, 3,
        3, 8, 4,
        4, 9, 0,
};

const std::vector < engine::VVertex > cubeVertices = {


        {{-0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
        {{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},

        {{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
        {{ 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
        {{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},

        {{ 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
        {{ 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},

        {{-0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},  // 2
        {{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}, // 3
        {{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}}, // 0
        {{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}}, // 1
};

const std::vector < uint16 > cubeIndices = {

        0,   1,  2,  2,  3,  0,
        1,   0,  5,  4,  5,  0,
        9,   8,  10, 10, 11, 9,
        3,   2,  7,  6,  7,  2,
        12,  13, 14, 15, 14, 13,
        4,   6,  5,  7,  6,  4
};

bool left = false;
bool right = false;
bool up = false;
bool down = false;

#include <chrono>
#include <glm/gtc/matrix_transform.hpp>
void engine::VulkanTriangleApplication::updateUniformBuffer(uint32 uniformBufferIndex) noexcept(false) {
    static float FOV = 45.0f;

    auto view = glm::lookAt(
            glm::vec3(2.0f, 2.0f, 2.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, 1.0f)
    );

    auto projection = glm::perspective (
            glm::radians ( FOV ),
            this->_vulkanLogicalDevice.getSwapChain()->getImagesInfo().extent.width /
            (float) this->_vulkanLogicalDevice.getSwapChain()->getImagesInfo().extent.height,
            0.1f,
            10.0f
    );

    glm::mat4 baseLocation (1.0f);

    for ( auto * pEntity : this->_activeScene.entitiesOfClass("VGameObject") ) {
        auto pGameObject = dynamic_cast < VGameObject * > (pEntity);
        engine::SUniformBufferObject UBO {
            .model = glm::rotate(
                glm::rotate (
                    glm::rotate(
                        glm::scale(
                            glm::translate(baseLocation, pGameObject->transformPtr()->getLocation() ),
                            pGameObject->transformPtr()->getScale()
                        ),
                        glm::radians(pGameObject->transformPtr()->getRotation().yaw()), glm::vec3(1.0f, 0.0f, 0.0f)
                    ),
                    glm::radians(pGameObject->transformPtr()->getRotation().pitch()), glm::vec3(0.0f, 1.0f, 0.0f)
                ),
                glm::radians(pGameObject->transformPtr()->getRotation().roll()), glm::vec3(0.0f, 0.0f, 1.0f)
            ),
            .view       = view,
            .projection = projection
        };

        UBO.projection[1][1] *= -1;

        auto & currentBuffer = pGameObject->meshRendererPtr()->getMVPDescriptorBuffers()[ uniformBufferIndex ];
        currentBuffer.load( & UBO, 1U );
    }
}

void processInputCallback (GLFWwindow* window, int key, int scanCode, int action, int mods) {
    if ( action == GLFW_PRESS ) {
        if ( key == GLFW_KEY_A ) {
            left = true;
        }
        if ( key == GLFW_KEY_D ) {
            right = true;
        }

        if ( key == GLFW_KEY_W )
            up = true;

        if ( key == GLFW_KEY_S )
            down = true;
    } else if ( action == GLFW_RELEASE ) {
        if ( key == GLFW_KEY_A ) {
            left = false;
        }
        if ( key == GLFW_KEY_D ) {
            right = false;
        }

        if ( key == GLFW_KEY_W )
            up = false;

        if ( key == GLFW_KEY_S )
            down = false;
    }
}

void engine::VulkanTriangleApplication::update() noexcept(false) {
    auto pCube = dynamic_cast<VGameObject *>(this->_activeScene.getGameObjectByName("cube"));
    if ( pCube == nullptr ) return;

    if ( left )
        pCube->transformPtr()->getRotation().rotate(VRotor::ROLL, 90.0f * static_cast<float>(this->_deltaTime));

    if ( right )
        pCube->transformPtr()->getRotation().rotate(VRotor::ROLL, - 90.0f * static_cast<float>(this->_deltaTime));


    if ( up )
        pCube->transformPtr()->getRotation().rotate(VRotor::PITCH, 90.0f * static_cast<float>(this->_deltaTime));

    if ( down )
        pCube->transformPtr()->getRotation().rotate(VRotor::PITCH, - 90.0f * static_cast<float>(this->_deltaTime));

    auto pStar = dynamic_cast<VGameObject *>(this->_activeScene.getGameObjectByName("star"));

    pStar->transformPtr()->getRotation().rotate(VRotor::ROLL, 180.0f * static_cast<float>(this->_deltaTime));
}

void engine::VulkanTriangleApplication::mainLoop() noexcept (false) {
    while ( ! glfwWindowShouldClose( this->_window ) ) { /// while window is active
        double startFrameTime = glfwGetTime(); /// get current time accurately

        glfwPollEvents(); /// poll all interrupting events - Window Minimise, Window Resize, Key Press etc.
        this->update(); /// Periodic call per frame for each object
        this->drawImage(); /// Periodic call to draw a free image

        this->_deltaTime = ( glfwGetTime() - startFrameTime ); /// Calculate frame time

        this->_fpsTimer += this->_deltaTime;

        if ( this->_fpsTimer >= this->_fpsRefreshTimer ) {
            if ( VulkanTriangleApplication::SHOW_FPS_CONSOLE )
                std::cout << "FPS : " << (1.0 / this->_deltaTime) << '\n';
            this->_fpsTimer = 0.0;
        }
    }
    vkDeviceWaitIdle( this->_vulkanLogicalDevice.data() ); //// Wait until GPU draw Task is finished before closing
}

void engine::VulkanTriangleApplication::createBuffers() noexcept(false) {
    /**
     * Based on configuration on logical device, we use memory exclusivity if only one graphics queue
     * has been found for Graphics and Present Transfers.
     * Otherwise, we use concurrency
     */
    if ( this->_vulkanQueueFamilyCollection->getQueueFamilies().size() == 1 ) {
        this->createExclusiveBuffers();
    } else if ( this->_vulkanQueueFamilyCollection->getQueueFamilies().size() > 1 ) {
        this->createConcurrentBuffers();
    }
}

void engine::VulkanTriangleApplication::createDepthBuffer() noexcept(false) {
    /// Create Depth Buffer, Deciding which object prints first. Requires Queue Family Indices
    auto queueFamilyIndices = this->_vulkanQueueFamilyCollection->getQueueFamilyIndices();
    ENG_THROW_IF_NOT_SUCCESS(
            this->_depthBuffer.setup(
                    this->_transferCommandPool,
                    queueFamilyIndices.data(),
                    static_cast<uint32>(queueFamilyIndices.size())
            ),
            std::runtime_error("depth buffer create failure")
    )
}


void engine::VulkanTriangleApplication::createConcurrentBuffers() noexcept(false) {
    auto * pCube = this->_activeScene.getGameObjectByName("cube");
    auto * pStar = this->_activeScene.getGameObjectByName("star");

    if ( pCube != nullptr )
        ENG_THROW_IF_NOT_SUCCESS (
            pCube->meshPtr()->setup(
                this->_transferCommandPool,
                * this->_vulkanQueueFamilyCollection,
                cubeVertices,
                cubeIndices
            ),
            ENG_STD_THROW("Cube Mesh Setup Error")
      )

    if ( pStar != nullptr )
        ENG_THROW_IF_NOT_SUCCESS(
            pStar->meshPtr()->setup(
                this->_transferCommandPool,
                * this->_vulkanQueueFamilyCollection,
                starVertices,
                starIndices
            ),
            ENG_STD_THROW ("Star Mesh Setup Error")
        )

    this->createUniformBuffers();
}

void engine::VulkanTriangleApplication::createTextures() noexcept(false) {
    /// Create and Load Texture Sampler. Use Default Anisotropy = 16. Configurable Later
    auto anisotropyLevel = 16.0f;

    ENG_THROW_IF_NOT_SUCCESS(
            this->_textureSampler.setup(
                this->_vulkanLogicalDevice,
                true,
                anisotropyLevel
            ),
            std::runtime_error("sampler create error")
    )
}

void engine::VulkanTriangleApplication::createDescriptorSets() noexcept(false) {
    auto * pCube = this->_activeScene.getGameObjectByName("cube");
    auto * pStar = this->_activeScene.getGameObjectByName("star");

    if ( pCube != nullptr )
        ENG_THROW_IF_NOT_SUCCESS(
            pCube->meshRendererPtr()->setup(
                    this->_transferCommandPool,
                    this->_descriptorPool,
                    this->_objectShader,
                    std::string(__TEXTURES_PATH__).append("container.jpg").c_str(),
                    this->_textureSampler,
                    * this->_vulkanQueueFamilyCollection
            ),
            ENG_STD_THROW("Mesh Renderer Create Failure")
        )

    if ( pStar != nullptr )
        ENG_THROW_IF_NOT_SUCCESS(
            pStar->meshRendererPtr()->setup(
                    this->_transferCommandPool,
                    this->_descriptorPool,
                    this->_objectShader,
                    std::string(__TEXTURES_PATH__).append("container3.jpg").c_str(),
                    this->_textureSampler,
                    * this->_vulkanQueueFamilyCollection
            ),
            ENG_STD_THROW("Mesh Renderer Create Failure")
        )
}

void engine::VulkanTriangleApplication::createDescriptorPool() noexcept(false) {
    std::vector < VulkanDescriptorType > descriptorTypes;

    for ( const auto & type : this->_objectShader.getDescriptorTypeLayout() ) {
        descriptorTypes.push_back( type );
    }

    uint32 objectCount = static_cast<uint32>(this->_activeScene.entitiesOfClass("VGameObject").size());

    ENG_THROW_IF_NOT_SUCCESS (
        this->_descriptorPool.setup (
            this->_vulkanLogicalDevice,
            descriptorTypes.data(),
            static_cast < uint32 > (descriptorTypes.size()),
            objectCount
        ),
        std::runtime_error ( "Descriptor Pool Creation Failure" )
    )

}

void engine::VulkanTriangleApplication::createUniformBuffers() noexcept(false) {
    this->createDescriptorPool();
    this->createDescriptorSets();
}

void engine::VulkanTriangleApplication::createExclusiveBuffers() noexcept(false) {
    this->createUniformBuffers();
}

#if !defined(_MSC_VER)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"
#endif
void engine::VulkanTriangleApplication::cleanup() noexcept (false) {
    /**
     * Free and cleanup objects in reverse allocation + creation order
     */

    this->_imageAvailableSemaphores.cleanup();
    this->_renderFinishedSemaphores.cleanup();
    this->_inFlightFences.cleanup();

    this->_commandPool.cleanup();
    this->_transferCommandPool.cleanup();

    this->_depthBuffer.cleanup();
    this->_frameBufferCollection.cleanup();

    for ( auto * pComponent : this->_activeScene.componentsOfClass("VMeshRenderer") )
        dynamic_cast<VMeshRenderer *>(pComponent)->cleanup();

    this->_textureSampler.cleanup();
    this->_descriptorPool.cleanup();
    this->_objectShader.cleanup();

    for ( auto * pComponent : this->_activeScene.componentsOfClass("VMesh") ) {
        auto * pMesh = dynamic_cast<VMesh *>(pComponent);

        pMesh->free();
        pMesh->cleanup();
    }

    this->_vulkanLogicalDevice.cleanup();

    delete this->_vulkanQueueFamilyCollection;

    if( enableValidationLayers )
        this->_vulkanMessenger.clean();

    this->_vulkanSurface.clean();
    this->_vulkanInstance.clean();

    glfwDestroyWindow(this->_window);

    glfwTerminate();
}

void engine::VulkanTriangleApplication::createCommandPool() noexcept(false) {
    //// Create Two Command Pools. One for Drawing, One for Transfer to Screen
    if ( this->_commandPool.setup( this->_vulkanLogicalDevice ) != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ( "Command Pool Creation Error" );
    if ( this->_transferCommandPool.setup( this->_vulkanLogicalDevice, this->_vulkanLogicalDevice.getFirstTransferQueuePtr()->getQueueFamily() ) != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ( "Transfer Command Pool Creation Error" );
}

/// Reminder : objects of same type, store in same buffer !
void engine::VulkanTriangleApplication::createCommandBuffers() noexcept(false) {
    /**
     * Creation of Command Buffers - Draw Commands
     *
     * First they are allocated onto the Frame Buffers, give an Output
     * Allocated from a Pool
     */
    if ( this->_drawCommandBufferCollection.allocate( this->_commandPool, this->_frameBufferCollection ) != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ( "Command Buffers Allocation Error" );

    VulkanDeviceSize offsets [] = { 0 };

    auto gameObjects = this->_activeScene.entitiesOfClass("VGameObject");

    //// Input Data
    /**
     * Vertices of Objects - vertexBuffers
     * Indices of Vertices - Order of line drawing. - indexBuffers
     * layout of vertices, indices, model view projection matrix, textures on the CPU-GPU bus ( queue ) - object descriptor handles
     */
    auto vertexBuffers              = new VVertexBuffer[gameObjects.size()];
    auto indexBuffers               = new VIndexBuffer[gameObjects.size()];
    auto objectDescriptorSetHandles = new std::vector < VulkanDescriptorSet > [gameObjects.size()];

    Index i = 0;
    for ( auto * o : gameObjects ) {
        auto * pGameObject = dynamic_cast<VGameObject *>(o);

        vertexBuffers[i]                = pGameObject->meshPtr()->getVertexBuffer();
        indexBuffers[i]                 = pGameObject->meshPtr()->getIndexBuffer();
        objectDescriptorSetHandles[i]   = pGameObject->meshRendererPtr()->getDescriptorSets().getDescriptorSetHandles();

        i++;
    }

    /**
     * Same handles as above, but rearranged as follows :
     * Previous Arrangement : Array of [FrameBufferCount] Array per Object
     * Current Arrangement : Array of Object Descriptor Set Array per Frame Buffer Image
     */
    std::vector < VulkanDescriptorSet * > descriptorSetHandles ( this->_drawCommandBufferCollection.getCommandBuffers().size());
    for ( uint32 i = 0; i < descriptorSetHandles.size(); i++ ) {
        descriptorSetHandles[i]     = new VulkanDescriptorSet[gameObjects.size()];
        for ( Index j = 0; j < gameObjects.size(); j++ )
            descriptorSetHandles[i][j] = objectDescriptorSetHandles[j][i];
    }

    /**
     * Create Drawing Buffer for each FrameBuffer
     */
    if ( this->_drawCommandBufferCollection.startRecord(
            this->_objectShader.getPipeline(),
            vertexBuffers,
            indexBuffers,
            gameObjects.size(),
            offsets,
            1U,
            descriptorSetHandles.data(),
            static_cast < uint32 > ( descriptorSetHandles.size() )
        ) != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ( "Command Buffers Record Error" );

    for ( auto & handles : descriptorSetHandles )
        delete [] handles;

    delete [] vertexBuffers;
    delete [] indexBuffers;
    delete [] objectDescriptorSetHandles;
}

void engine::VulkanTriangleApplication::autoPickPhysicalDevice() noexcept(false) {
    auto devices = VPhysicalDevice::getAvailablePhysicalDevices( this->_vulkanInstance );
    const VPhysicalDevice * bestDevice = nullptr;
    uint32 maxDeviceRating = 0U;

    for ( const auto & device : devices ) {
        uint32 rating = device.getPhysicalDeviceRenderRating();
        if( rating > maxDeviceRating ) {
            maxDeviceRating = rating;
            bestDevice = & device;
        }
    }

    if( bestDevice == nullptr )
        throw std::runtime_error ( "failed to find a suitable GPU" );

    this->_vulkanPhysicalDevice = ( * bestDevice );
}

void engine::VulkanTriangleApplication::createShaderModules() noexcept(false) {

}

void engine::VulkanTriangleApplication::createGraphicsPipeline() noexcept(false) {
    VShaderCompiler compiler; /// Create a Precompiler

    /// Use JSON Configuration for shader data
    compiler.setConfigurationFileJSON( std::string(__VULKAN_SHADERS_PATH__).append("/config/vkTriangleShaderComp.json") );
    compiler.build(); /// Build Shaders in outputs mentioned in JSON Configuration
    ENG_THROW_IF_NOT_SUCCESS (
            this->_objectShader.setup(  ///Setup Shader for GPU
                    this->_vulkanLogicalDevice,
                    compiler,
                    "defObj"
            ),
            ENG_STD_THROW("shader creation error")
    )

}

void engine::VulkanTriangleApplication::createFrameBuffers() noexcept(false) {
    //// Create Frame Buffers - Images that will be swapped in flight, used by Double or Triple Buffering ( currently enabled - Triple )
    if ( this->_frameBufferCollection.setup ( this->_objectShader.getRenderPassPtr(), & this->_depthBuffer ) != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ( "Frame Buffers Creation Failure" );
}

#if !defined(_MSC_VER)
#pragma clang diagnostic pop
#endif
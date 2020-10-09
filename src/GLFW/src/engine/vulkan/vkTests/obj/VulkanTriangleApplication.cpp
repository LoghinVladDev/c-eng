//
// Created by vladl on 05/08/2020.
//

#include "VulkanTriangleApplication.h"
#include <src/GLFW/src/engine/vulkan/vkUtils/VStdUtils.h>
#include <src/GLFW/src/engine/vulkan/vkUtils/VStdUtilsDefs.h>
#include <map>
#include <obj/util/settings/SettingsSharedContainer.h>
#include <obj/util/settings/SettingOptionGraphics.h>

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

void engine::VulkanTriangleApplication::initSettings() const noexcept {
    auto resolution = engine::ResolutionSetting( this->_width, this->_height );

    engine::SettingsSharedContainer::getInstance().put( & resolution );
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
    auto cubeUniformBufferObjectBinding = VulkanDescriptorSetLayoutBinding {
        .binding            = 0U,
        .descriptorType     = VulkanDescriptorType::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
        .descriptorCount    = 1U,
        .stageFlags         = VulkanShaderStageFlagBits::VK_SHADER_STAGE_VERTEX_BIT,
        .pImmutableSamplers = nullptr
    };

    auto cubeSamplerObjectBinding = VulkanDescriptorSetLayoutBinding {
        .binding            = 1U,
        .descriptorType     = VulkanDescriptorType::VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
        .descriptorCount    = 1U,
        .stageFlags         = VulkanShaderStageFlagBits::VK_SHADER_STAGE_FRAGMENT_BIT,
        .pImmutableSamplers = nullptr
    };

    std::array < VulkanDescriptorSetLayoutBinding, 2 > cubeBindings = {
            cubeUniformBufferObjectBinding,
            cubeSamplerObjectBinding
//            starUnfiromBufferObjectBinding,
//            starSamplerObjectBinding
    };

    VulkanDescriptorSetLayoutCreateInfo cubeCreateInfo {
        .sType              = VulkanStructureType::VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        .pNext              = nullptr,
        .flags              = 0U,
        .bindingCount       = static_cast < uint32 > ( cubeBindings.size() ),
        .pBindings          = cubeBindings.data()
    };

    if (vkCreateDescriptorSetLayout( this->_vulkanLogicalDevice.data(), & cubeCreateInfo, nullptr, & this->_descriptorSetLayout ) != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ("failed to create descriptor set layout");
}

void engine::VulkanTriangleApplication::run() noexcept (false) {
    this->initSettings();
    this->initWindow();
    this->initVulkan();
    this->createShaderModules();
    this->createDescriptorSetLayout();
    this->createGraphicsPipeline();
    this->createCommandPool();
    this->createDepthBuffer();
    this->createFrameBuffers();
    this->createTextures();
    this->createBuffers();
    this->createCommandBuffers();
    this->freeStagingBuffers();
    this->createSynchronizationElements();
    this->mainLoop();
    this->cleanup();
}

void processInputCallback (GLFWwindow*, int, int, int, int);

inline void engine::VulkanTriangleApplication::initWindow() noexcept (false) {
    if(glfwInit() == GLFW_FALSE) {
        throw engine::EngineVulkanTestException("GLFW Init failure");
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
//    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    this->_window = glfwCreateWindow(
        this->_width,
        this->_height,
        VulkanTriangleApplication::DEFAULT_TITLE,
        nullptr,
        nullptr
    );

    glfwSetWindowUserPointer( this->_window, this );
    glfwSetFramebufferSizeCallback( this->_window, engine::VulkanTriangleApplication::frameBufferResizeCallback );
    glfwSetKeyCallback( this->_window, processInputCallback );
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

#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"
#pragma ide diagnostic ignored "UnreachableCode"
inline void engine::VulkanTriangleApplication::initVulkan() noexcept (false) {
    VExtensionCollection availableExtensions = VExtensionCollection::getAllAvailableExtensions();

#ifndef NDEBUG
    if( VulkanTriangleApplication::VULKAN_EXT_CHECK )
        availableExtensions.debugPrint(std::cout );
#endif

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
    this->createSurface();
    this->autoPickPhysicalDevice();

    std::cout << "Most Suitable GPU : \n";

#ifndef NDEBUG
    this->_vulkanPhysicalDevice.debugPrintPhysicalDeviceProperties( std::cout, true, "\t");
#endif

    this->_vulkanQueueFamilyCollection = new VQueueFamilyCollection ( this->_vulkanPhysicalDevice, &this->_vulkanSurface );

    queueFamilyTests( * this->_vulkanQueueFamilyCollection );

    engine::VLogicalDevice::VLogicalDeviceFactory::enableExceptions();
    engine::VLogicalDevice::VLogicalDeviceFactory deviceFactory;

    if( enableValidationLayers )
        deviceFactory.withValidationLayers( this->_vulkanValidationLayerCollection );

    auto queues = internalGatherGraphicsAndPresentQueueFamilies ( * this->_vulkanQueueFamilyCollection );

    if( queues.size() == 1 ) { // graphics & present queues in same family
        deviceFactory.addQueue(*queues[0], 1.0f);
        deviceFactory.addQueue(* this->_vulkanQueueFamilyCollection->getTransferCapableQueueFamilies()[0], 1.0f);
    }
    else {
        deviceFactory.addQueue( * queues[0], 1.0f );
        deviceFactory.addQueue( * queues[1], 1.0f );
        deviceFactory.addQueue(* this->_vulkanQueueFamilyCollection->getTransferCapableQueueFamilies()[0], 1.0f);
    }

    deviceFactory.createSwapChainToSurface( & this->_vulkanSurface );
//
    this->_vulkanLogicalDevice = deviceFactory.build( this->_vulkanPhysicalDevice );
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
    if ( this->_imageAvailableSemaphores.setup( this->_vulkanLogicalDevice, MAX_FRAMES_IN_FLIGHT ) != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ( "Semaphore Creation Failure : Image Availability" );
    if ( this->_renderFinishedSemaphores.setup( this->_vulkanLogicalDevice, MAX_FRAMES_IN_FLIGHT ) != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ( "Semaphore Creation Failure : Render Finish" );

    if ( this->_inFlightFences.setup( this->_vulkanLogicalDevice, MAX_FRAMES_IN_FLIGHT, engine::VFence::START_SIGNALED ) != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ( "Fence Creation Failure" );
    this->_imagesInFlight.resize( this->_vulkanLogicalDevice.getSwapChain()->getImages().size() );
}

#pragma clang diagnostic pop


/**
 * Will recreate in flight
 */
void engine::VulkanTriangleApplication::recreateSwapChain() noexcept(false) {
    vkDeviceWaitIdle( this->_vulkanLogicalDevice.data() );

    this->cleanupSwapChain();

    this->updateResolutionSettings();

    if ( this->_vulkanLogicalDevice.recreateSwapChain() != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ( "Swap Chain Recreation Error" );

    this->createGraphicsPipeline();
    this->createDepthBuffer();
    this->createFrameBuffers();
    this->createUniformBuffers();
    this->createCommandBuffers();
}

void engine::VulkanTriangleApplication::cleanupSwapChain() noexcept(false) {
    this->_depthBuffer.cleanup();
    this->_frameBufferCollection.cleanup();
    this->_drawCommandBufferCollection.free();

    for ( auto & uniformBuffer : this->_cubeUniformBuffers ) {
        uniformBuffer.free();
        uniformBuffer.cleanup();
    }

    for ( auto & uniformBuffer : this->_starUniformBuffers ) {
        uniformBuffer.free();
        uniformBuffer.cleanup();
    }

    this->_descriptorPool.cleanup();

    this->_graphicsPipeline.cleanup();
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

float xRotateValue = 0.0f;
float yRotateValue = 0.0f;
bool left = false;
bool right = false;
bool up = false;
bool down = false;

#include <chrono>
#include <glm/gtc/matrix_transform.hpp>
void engine::VulkanTriangleApplication::updateUniformBuffer(uint32 uniformBufferIndex) noexcept(false) {
    auto & cubeCurrentBuffer = this->_cubeUniformBuffers[ uniformBufferIndex ];

    static auto startTime = std::chrono::high_resolution_clock::now();
    auto currentTime = std::chrono::high_resolution_clock::now();

    double scaleFactor = 1.3f;

    static float FOV = 45.0f;
    engine::SUniformBufferObject UBO {
        .model = glm::rotate (
                glm::rotate (
                    glm::scale (
                        glm::translate (
                                glm::mat4 ( 1.0f ),
                                glm::vec3 (0.0f, 0.0f, 0.0f)
                            ),
                            glm::vec3 ( scaleFactor, scaleFactor, scaleFactor )
                ),
                    xRotateValue * glm::radians (90.0f ),
                    glm::vec3 ( 0.0f, 0.0f, 1.0f )
            ),
            yRotateValue * glm::radians ( 90.0f ),
            glm::vec3 ( 0.0f, 1.0f, 0.0f )
        ),
//        .model = glm::rotate( glm::translate ( glm::mat4 ( 1.0f ), glm::vec3 ( std::sin ( time ) , 0.0f, 0.0f ) ), time * glm::radians ( 90.0f ), glm::vec3 (0.5f, 0.0f, 0.5f) ),
        .view  = glm::lookAt( glm::vec3 ( 2.0f, 2.0f, 2.0f ) , glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3 (0.0f, 0.0f, 1.0f) ),
        .projection = glm::perspective (
                glm::radians ( FOV ),
                this->_vulkanLogicalDevice.getSwapChain()->getImagesInfo().extent.width /
                (float) this->_vulkanLogicalDevice.getSwapChain()->getImagesInfo().extent.height,
                0.1f,
                10.0f
        )
    };

    UBO.projection[1][1] *= -1; /// OPENGL - VULKAN diff

    cubeCurrentBuffer.load( & UBO, 1U );

    auto & starBuffer = this->_starUniformBuffers[ uniformBufferIndex ];

    engine::SUniformBufferObject starUBO {
        .model = glm::rotate( glm::scale (
                glm::translate(
                        glm::mat4 ( 1.0f ),
                        glm::vec3 (0.0f, 1.0f, 0.0f)
                ),
                glm::vec3 ( 1.5f, 1.5f, 1.5f )
                  ), (float) glfwGetTime() * glm::radians( 90.0f ), glm::vec3 ( 1.0f, 0.0f, 0.0f )
        ),
        .view  = glm::lookAt( glm::vec3 ( 2.0f, 2.0f, 2.0f ) , glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3 (0.0f, 0.0f, 1.0f) ),
        .projection = glm::perspective (
                glm::radians ( FOV ),
                this->_vulkanLogicalDevice.getSwapChain()->getImagesInfo().extent.width /
                (float) this->_vulkanLogicalDevice.getSwapChain()->getImagesInfo().extent.height,
                0.1f,
                10.0f
        )
    };

    starUBO.projection[1][1] *= -1;
    starBuffer.load( & starUBO, 1U );
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
    if ( left )
        xRotateValue -= static_cast < float > (2.0 * this->_deltaTime);
    if ( right )
        xRotateValue += static_cast < float > (2.0 * this->_deltaTime);

    if ( up )
        yRotateValue -= static_cast < float > (2.0 * this->_deltaTime);
    if ( down )
        yRotateValue += static_cast < float > (2.0 * this->_deltaTime);
}

void engine::VulkanTriangleApplication::mainLoop() noexcept (false) {
    while ( ! glfwWindowShouldClose( this->_window ) ) {
        double startFrameTime = glfwGetTime();

        glfwPollEvents();
        this->update();
        this->drawImage();

        this->_deltaTime = ( glfwGetTime() - startFrameTime );

        this->_fpsTimer += this->_deltaTime;

        if ( this->_fpsTimer >= this->_fpsRefreshTimer ) {
            if ( VulkanTriangleApplication::SHOW_FPS_CONSOLE )
                std::cout << "FPS : " << (1.0 / this->_deltaTime) << '\n';
            this->_fpsTimer = 0.0;
        }
    }
    vkDeviceWaitIdle( this->_vulkanLogicalDevice.data() );
}

void engine::VulkanTriangleApplication::createBuffers() noexcept(false) {
    if ( this->_vulkanQueueFamilyCollection->getQueueFamilies().size() == 1 ) {
        this->createExclusiveBuffers();
    } else if ( this->_vulkanQueueFamilyCollection->getQueueFamilies().size() > 1 ) {
        this->createConcurrentBuffers();
    }
}

void engine::VulkanTriangleApplication::createDepthBuffer() noexcept(false) {
    auto queueFamilyIndices = this->_vulkanQueueFamilyCollection->getQueueFamilyIndices();
    ENG_THROW_IF_NOT_SUCCESS(
            this->_depthBuffer.setup(
                    this->_transferCommandPool,
                    queueFamilyIndices.data(),
                    queueFamilyIndices.size()
            ),
            std::runtime_error("depth buffer create failure")
    )
}


void engine::VulkanTriangleApplication::createConcurrentBuffers() noexcept(false) {
    ENG_THROW_IF_NOT_SUCCESS (
        this->_cubeMesh.setup(
            this->_transferCommandPool,
            * this->_vulkanQueueFamilyCollection,
            cubeVertices,
            cubeIndices
        ),
        ENG_STD_THROW("Cube Mesh Setup Error")
    )

    ENG_THROW_IF_NOT_SUCCESS(
        this->_starMesh.setup(
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
    ENG_THROW_IF_NOT_SUCCESS(
            this->_textureSampler.setup(
                this->_vulkanLogicalDevice,
                true,
                16.0f
            ),
            std::runtime_error("sampler create error")
    )

    auto queueFamilyIndices = this->_vulkanQueueFamilyCollection->getQueueFamilyIndices();

    ENG_THROW_IF_NOT_SUCCESS(
            this->_cubeTexture.setup(
                    std::string(__TEXTURES_PATH__).append("container.jpg").c_str(),
                    this->_transferCommandPool,
                    queueFamilyIndices.data(),
                    queueFamilyIndices.size()
            ),
            std::runtime_error("Texture Creation Failure")
    )

    ENG_THROW_IF_NOT_SUCCESS(
            this->_starTexture.setup(
                    std::string(__TEXTURES_PATH__).append("container2.png").c_str(),
                    this->_transferCommandPool,
                    queueFamilyIndices.data(),
                    queueFamilyIndices.size()
            ),
            std::runtime_error("Star Texture Creation Failure")
    )
}

void engine::VulkanTriangleApplication::createDescriptorSets() noexcept(false) {
    if ( this->_cubeDescriptorSetCollection.allocate(
        this->_descriptorPool,
        this->_descriptorSetLayout
    ) != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ("Descriptor Set Allocate Error");

    this->_cubeDescriptorSetCollection.configure(this->_cubeUniformBuffers, 0U);
    this->_cubeDescriptorSetCollection.configure(this->_cubeTexture, this->_textureSampler, 1U);

    ENG_THROW_IF_NOT_SUCCESS(
        this->_starDescriptorSetCollection.allocate(
            this->_descriptorPool,
            this->_descriptorSetLayout
        ),
        ENG_STD_THROW( "Star descriptor set alloc error" )
    )

    this->_starDescriptorSetCollection.configure( this->_starUniformBuffers, 0U);
    this->_starDescriptorSetCollection.configure( this->_starTexture, this->_textureSampler, 1U );
}

void engine::VulkanTriangleApplication::createDescriptorPool() noexcept(false) {
    std::array < VulkanDescriptorType, 4 > descriptorTypes = {
            VulkanDescriptorType::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
            VulkanDescriptorType::VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
            VulkanDescriptorType::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
            VulkanDescriptorType::VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
    };

    uint32 objectCount = 2U; // star + cube

    ENG_THROW_IF_NOT_SUCCESS (
        this->_descriptorPool.setup (
            this->_vulkanLogicalDevice,
            descriptorTypes.data(),
            static_cast < uint32 > (descriptorTypes.size()),
            objectCount
        ),
        std::runtime_error ( "Descriptor Pool Creation Failure" )
    )

    this->createDescriptorSets();
}

void engine::VulkanTriangleApplication::createUniformBuffers() noexcept(false) {
    this->_cubeUniformBuffers.resize( this->_vulkanLogicalDevice.getSwapChain()->getImages().size() );
    for ( auto & uniformBuffer : this->_cubeUniformBuffers ) {
        if (  uniformBuffer.setup(
            this->_vulkanLogicalDevice,
            1U
        ) != VulkanResult::VK_SUCCESS )
            throw std::runtime_error ("Uniform Buffer Creation Failure");

        if ( uniformBuffer.allocateMemory() != VulkanResult::VK_SUCCESS )
            throw std::runtime_error ("Uniform Buffer Allocate Memory Failure");
    }

    this->_starUniformBuffers.resize( this->_vulkanLogicalDevice.getSwapChain()->getImages().size() );
    for ( auto & uniformBuffer : this->_starUniformBuffers ) {
        ENG_THROW_IF_NOT_SUCCESS (
            uniformBuffer.setup (
                this->_vulkanLogicalDevice,
                1U
            ),
            std::runtime_error ( "Star Uniform Buffer Creation Failure" )
        )

        ENG_THROW_IF_NOT_SUCCESS (
            uniformBuffer.allocateMemory(),
            std::runtime_error ("Star Uniform Buffer Alloc Failure")
        )
    }

    this->createDescriptorPool();
}

void engine::VulkanTriangleApplication::createExclusiveBuffers() noexcept(false) {
    this->createUniformBuffers();
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"
void engine::VulkanTriangleApplication::cleanup() noexcept (false) {
    this->_imageAvailableSemaphores.cleanup();
    this->_renderFinishedSemaphores.cleanup();
    this->_inFlightFences.cleanup();

    this->_commandPool.cleanup();
    this->_transferCommandPool.cleanup();

    this->_depthBuffer.cleanup();
    this->_frameBufferCollection.cleanup();

    for ( auto & buffer : this->_cubeUniformBuffers ) {
        buffer.free();
        buffer.cleanup();
    }

    for ( auto & buffer : this->_starUniformBuffers ) {
        buffer.free();
        buffer.cleanup();
    }

    this->_cubeTexture.cleanup();
    this->_starTexture.cleanup();
    this->_textureSampler.cleanup();

    this->_descriptorPool.cleanup();

    this->_graphicsPipeline.cleanup();

    vkDestroyDescriptorSetLayout(this->_vulkanLogicalDevice.data(), this->_descriptorSetLayout, nullptr );

    this->_vertexShader.cleanup();
    this->_fragmentShader.cleanup();

    this->_cubeMesh.free();
    this->_cubeMesh.cleanup();
    this->_starMesh.free();
    this->_starMesh.cleanup();

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
    if ( this->_commandPool.setup( this->_vulkanLogicalDevice ) != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ( "Command Pool Creation Error" );
    if ( this->_transferCommandPool.setup( this->_vulkanLogicalDevice, this->_vulkanLogicalDevice.getFirstTransferQueuePtr()->getQueueFamily() ) != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ( "Transfer Command Pool Creation Error" );
}

/// Reminder : objects of same type, store in same buffer !
void engine::VulkanTriangleApplication::createCommandBuffers() noexcept(false) {
    if ( this->_drawCommandBufferCollection.allocate( this->_commandPool, this->_frameBufferCollection ) != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ( "Command Buffers Allocation Error" );

    VulkanDeviceSize offsets [] = { 0 };

    VVertexBuffer vertexBuffers [] = {
            this->_cubeMesh.getVertexBuffer(),
            this->_starMesh.getVertexBuffer()
    };

    VIndexBuffer indexBuffers [] = {
            this->_cubeMesh.getIndexBuffer(),
            this->_starMesh.getIndexBuffer()
    };

    std::array < std::vector < VulkanDescriptorSet >, 2 > objectDescriptorSetHandles = {
            this->_cubeDescriptorSetCollection.getDescriptorSetHandles(),
            this->_starDescriptorSetCollection.getDescriptorSetHandles()
    };

    std::vector < VulkanDescriptorSet * > descriptorSetHandles ( this->_drawCommandBufferCollection.getCommandBuffers().size());
    for ( uint32 i = 0; i < descriptorSetHandles.size(); i++ ) {
        descriptorSetHandles[i]     = new VulkanDescriptorSet[2];
        descriptorSetHandles[i][0]  = objectDescriptorSetHandles[0][i];
        descriptorSetHandles[i][1]  = objectDescriptorSetHandles[1][i];
    }

    if ( this->_drawCommandBufferCollection.startRecord(
            this->_graphicsPipeline,
            vertexBuffers,
            indexBuffers,
            2U,
            offsets,
            1U,
            descriptorSetHandles.data(),
            static_cast < uint32 > ( descriptorSetHandles.size() )
        ) != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ( "Command Buffers Record Error" );

    for ( auto & handles : descriptorSetHandles )
        delete [] handles;
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
    VShaderCompiler compiler;

    compiler.setConfigurationFileJSON( std::string(__VULKAN_SHADERS_PATH__).append("/config/vkTriangleShaderComp.json") );
    compiler.build();

    for ( const auto & target : compiler.getTargets() ) {
        if ( target.getTag () == "defObj" ) {
            if (target.getType() == VShaderModule::VERTEX) {

                this->_vertexShader.setType(VShaderModule::VERTEX);
                if (this->_vertexShader.setup(target.getCompiledPath(), this->_vulkanLogicalDevice) !=
                    VulkanResult::VK_SUCCESS)
                    throw std::runtime_error("Shader module initialization failed");
            } else if (target.getType() == VShaderModule::FRAGMENT) {

                this->_fragmentShader.setType(VShaderModule::FRAGMENT);
                if (this->_fragmentShader.setup(target.getCompiledPath(), this->_vulkanLogicalDevice) !=
                    VulkanResult::VK_SUCCESS)
                    throw std::runtime_error("Shader module initialization failed");
            }
        }
    }
}

void engine::VulkanTriangleApplication::createGraphicsPipeline() noexcept(false) {
    VulkanPipelineShaderStageCreateInfo shaderStages [] = {
        this->_vertexShader.getShaderStageInfo(),
        this->_fragmentShader.getShaderStageInfo()
    };

    auto bindingDescription = VVertex::getBindingDescription();
    auto attributeDescriptions = VVertex::getAttributeDescriptions();

    std::array < VkDescriptorSetLayout, 1 > descriptorSetLayouts = {
            this->_descriptorSetLayout
    };

    if ( this->_graphicsPipeline.setup (
            this->_vulkanLogicalDevice,
            shaderStages,
            2,
            & bindingDescription,
            1U,
            attributeDescriptions.data(),
            static_cast < uint32 > ( attributeDescriptions.size() ),
            descriptorSetLayouts.data(),
            static_cast < uint32 > ( descriptorSetLayouts.size() )
        ) != VulkanResult::VK_SUCCESS
    )
        throw std::runtime_error ("Graphics Pipeline initialization failed");

    this->_renderPass = this->_graphicsPipeline.getRenderPassPtr();

}

void engine::VulkanTriangleApplication::createFrameBuffers() noexcept(false) {
    if ( this->_frameBufferCollection.setup ( this->_renderPass, & this->_depthBuffer ) != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ( "Frame Buffers Creation Failure" );
}

#pragma clang diagnostic pop

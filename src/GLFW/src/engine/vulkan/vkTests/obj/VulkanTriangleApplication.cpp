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
    collection.debugPrintQueueFamilies( std::cout, "\t" );

    std::cout << "Graphics Capable Queue Families on Device : \n";

    for ( const auto & queueFamily : collection.getGraphicsCapableQueueFamilies() ) {
        queueFamily->debugPrintQueueFamily(std::cout, "\t");
    }

    collection.debugPrintQueueFamiliesReservations( std::cout );

    for ( const auto & queueFamily : collection.getQueueFamilies() ) {
        uint32 reservationTarget = 4U;
        uint32 reservations = queueFamily.reserveQueues(reservationTarget);

        std::cout << "Managed to reserve " << reservations << " out of " << reservationTarget << " requested\n";
    }

    collection.debugPrintQueueFamiliesReservations( std::cout );

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

    collection.debugPrintQueueFamiliesReservations( std::cout );

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
    auto uniformBufferObjectBinding = VulkanDescriptorSetLayoutBinding {
        .binding            = 0,
        .descriptorType     = VulkanDescriptorType::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
        .descriptorCount    = 1U,
        .stageFlags         = VulkanShaderStageFlagBits::VK_SHADER_STAGE_VERTEX_BIT,
        .pImmutableSamplers = nullptr
    };

    VulkanDescriptorSetLayoutCreateInfo createInfo {
        .sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        .pNext              = nullptr,
        .flags              = 0U,
        .bindingCount       = 1U,
        .pBindings          = & uniformBufferObjectBinding
    };

    if ( vkCreateDescriptorSetLayout( this->_vulkanLogicalDevice.data(), & createInfo, nullptr, & this->_descriptorSetLayoutUBO ) != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ("failed to create descriptor set layout");
}

void engine::VulkanTriangleApplication::run() noexcept (false) {
    this->initSettings();
    this->initWindow();
    this->initVulkan();
    this->createShaderModules();
    this->createDescriptorSetLayout();
    this->createGraphicsPipeline();
    this->createFrameBuffers();
    this->createCommandPool();
    this->createBuffers();
    this->createCommandBuffers();
    this->createTextures();
    this->freeStagingBuffers();
    this->createSynchronizationElements();
    this->mainLoop();
    this->cleanup();
}

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

    if( VulkanTriangleApplication::VULKAN_EXT_CHECK )
        availableExtensions.debugPrint(std::cout );

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

    this->_vulkanPhysicalDevice.debugPrintPhysicalDeviceProperties( std::cout, true, "\t");

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
    this->createFrameBuffers();
    this->createUniformBuffers();
    this->createCommandBuffers();
}

void engine::VulkanTriangleApplication::cleanupSwapChain() noexcept(false) {
    this->_frameBufferCollection.cleanup();
    this->_commandBufferCollection.free();

    for ( auto & uniformBuffer : this->_uniformBuffers ) {
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

    if ( this->_commandBufferCollection.getCommandBuffers()[ imageIndex ].submit(
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

const std::vector < engine::VVertex > vertices = {
        {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
        {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
        {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
        {{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
};

const std::vector < uint16 > indices = {
        0, 1, 2, 2, 3, 0
};

#include <chrono>
#include <glm/gtc/matrix_transform.hpp>
void engine::VulkanTriangleApplication::updateUniformBuffer(uint32 uniformBufferIndex) noexcept(false) {
    auto & currentBuffer = this->_uniformBuffers[ uniformBufferIndex ];

    static auto startTime = std::chrono::high_resolution_clock::now();
    auto currentTime = std::chrono::high_resolution_clock::now();

    float time = std::chrono::duration < float , std::chrono::seconds::period > ( currentTime - startTime ).count();
    static float FOV = 45.0f;

    engine::SUniformBufferObject UBO {
        .model = glm::rotate( glm::translate ( glm::mat4 ( 1.0f ), glm::vec3 ( std::sin ( time ) , 0.0f, 0.0f ) ), time * glm::radians ( 90.0f ), glm::vec3 (0.5f, 0.0f, 0.5f) ),
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

    currentBuffer.load( & UBO, 1U );
}

void engine::VulkanTriangleApplication::update() noexcept(false) {
}

void engine::VulkanTriangleApplication::mainLoop() noexcept (false) {
    while ( ! glfwWindowShouldClose( this->_window ) ) {
        double startFrameTime = glfwGetTime();
        static double deltaTime = 0.0;

        glfwPollEvents();
        this->update();
        this->drawImage();

        deltaTime = ( glfwGetTime() - startFrameTime );

        this->_fpsTimer += deltaTime;

        if ( this->_fpsTimer >= this->_fpsRefreshTimer ) {
            if ( VulkanTriangleApplication::SHOW_FPS_CONSOLE )
                std::cout << "FPS : " << (1.0 / deltaTime) << '\n';
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

void engine::VulkanTriangleApplication::createConcurrentBuffers() noexcept(false) {
    auto queueFamilyIndices = this->_vulkanQueueFamilyCollection->getQueueFamilyIndices();

    VulkanResult statusResult;
    if (( statusResult = this->_vertexBuffer.setup(
            this->_vulkanLogicalDevice,
            vertices,
            & this->_transferCommandPool,
            queueFamilyIndices.data(),
            queueFamilyIndices.size()
        )) != VulkanResult::VK_SUCCESS
    ) {
        std::cerr << VStandardUtils::to_string(statusResult) << '\n';
        throw std::runtime_error("Vertex Buffer Initialization failure");
    }

    if ( this->_vertexBuffer.allocateMemory() != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ( "Vertex Buffer Allocation failure" );

    if (( statusResult = this->_indexBuffer.setup(
            this->_vulkanLogicalDevice,
            indices,
            & this->_transferCommandPool,
            queueFamilyIndices.data(),
            queueFamilyIndices.size()
        )) != VulkanResult::VK_SUCCESS
    ) {
        std::cerr << VStandardUtils::to_string(statusResult) << '\n';
        throw std::runtime_error("Index Buffer Initialization failure");
    }

    if ( this->_indexBuffer.allocateMemory() != VulkanResult::VK_SUCCESS )
        throw std::runtime_error("Index Buffer Allocation failure");

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
            this->_texture.setup(
                    std::string(__TEXTURES_PATH__).append("statue.jpg").c_str(),
                    this->_transferCommandPool,
                    queueFamilyIndices.data(),
                    queueFamilyIndices.size()
            ),
            std::runtime_error("Texture Creation Failure")
    )
}

void engine::VulkanTriangleApplication::createDescriptorSets() noexcept(false) {
    if ( this->_descriptorSetCollection.allocate(
        this->_descriptorPool,
        this->_descriptorSetLayoutUBO
    ) != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ("Descriptor Set Allocate Error");

    this->_descriptorSetCollection.configure(this->_uniformBuffers);
}

void engine::VulkanTriangleApplication::createDescriptorPool() noexcept(false) {
    if ( this->_descriptorPool.setup( this->_vulkanLogicalDevice ) != VulkanResult::VK_SUCCESS )
        throw std::runtime_error("Descriptor Pool Creation Failure");

    this->createDescriptorSets();
}

void engine::VulkanTriangleApplication::createUniformBuffers() noexcept(false) {
    this->_uniformBuffers.resize( this->_vulkanLogicalDevice.getSwapChain()->getImages().size() );
    for ( auto & uniformBuffer : this->_uniformBuffers ) {
        if (  uniformBuffer.setup(
            this->_vulkanLogicalDevice,
            1U
        ) != VulkanResult::VK_SUCCESS )
            throw std::runtime_error ("Uniform Buffer Creation Failure");

        if ( uniformBuffer.allocateMemory() != VulkanResult::VK_SUCCESS )
            throw std::runtime_error ("Uniform Buffer Allocate Memory Failure");
    }

    this->createDescriptorPool();
}

void engine::VulkanTriangleApplication::createExclusiveBuffers() noexcept(false) {
    VulkanResult statusResult;
    if (( statusResult = this->_vertexBuffer.setup(
            this->_vulkanLogicalDevice,
            vertices,
            & this->_transferCommandPool
    )) != VulkanResult::VK_SUCCESS
            ) {
        std::cerr << VStandardUtils::to_string(statusResult) << '\n';
        throw std::runtime_error("Vertex Buffer Initialization failure");
    }

    if ( this->_vertexBuffer.allocateMemory() != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ( "Vertex Buffer Allocation failure" );

    if (( statusResult = this->_indexBuffer.setup(
            this->_vulkanLogicalDevice,
            indices.size(),
            & this->_transferCommandPool
    )) != VulkanResult::VK_SUCCESS
            ) {
        std::cerr << VStandardUtils::to_string(statusResult) << '\n';
        throw std::runtime_error("Index Buffer Initialization failure");
    }

    if ( this->_indexBuffer.allocateMemory() != VulkanResult::VK_SUCCESS )
        throw std::runtime_error("Index Buffer Allocation failure");

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

    this->_frameBufferCollection.cleanup();

    for ( auto & buffer : this->_uniformBuffers ) {
        buffer.free();
        buffer.cleanup();
    }

    this->_texture.cleanup();
    this->_textureSampler.cleanup();

    this->_descriptorPool.cleanup();

    this->_graphicsPipeline.cleanup();

    vkDestroyDescriptorSetLayout( this->_vulkanLogicalDevice.data(), _descriptorSetLayoutUBO, nullptr );

    this->_vertexShader.cleanup();
    this->_fragmentShader.cleanup();

    this->_vertexBuffer.free();
    this->_vertexBuffer.cleanup();
    this->_indexBuffer.free();
    this->_indexBuffer.cleanup();

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

void engine::VulkanTriangleApplication::createCommandBuffers() noexcept(false) {
    if ( this->_commandBufferCollection.allocate( this->_commandPool, this->_frameBufferCollection ) != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ( "Command Buffers Allocation Error" );

    VulkanDeviceSize offsets [] = { 0 };

    auto descriptorSetHandles = this->_descriptorSetCollection.getDescriptorSetHandles();

    if ( this->_commandBufferCollection.startRecord(
            this->_graphicsPipeline,
            & this->_vertexBuffer,
            offsets,
            1U,
            & this->_indexBuffer,
            descriptorSetHandles.data(),
            descriptorSetHandles.size()
        ) != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ( "Command Buffers Record Error" );
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
        if ( target.getType() == VShaderModule::VERTEX ) {
            this->_vertexShader.setType( VShaderModule::VERTEX );
            if ( this->_vertexShader.setup ( target.getCompiledPath(), this->_vulkanLogicalDevice ) != VulkanResult::VK_SUCCESS )
                throw std::runtime_error ("Shader module initialization failed");
        } else if ( target.getType() == VShaderModule::FRAGMENT ) {
            this->_fragmentShader.setType( VShaderModule::FRAGMENT );
            if ( this->_fragmentShader.setup ( target.getCompiledPath(), this->_vulkanLogicalDevice ) != VulkanResult::VK_SUCCESS )
                throw std::runtime_error ("Shader module initialization failed");
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

    if ( this->_graphicsPipeline.setup (
            this->_vulkanLogicalDevice,
            shaderStages,
            2,
            & bindingDescription,
            1U,
            attributeDescriptions.data(),
            static_cast < uint32 > ( attributeDescriptions.size() ),
            & this->_descriptorSetLayoutUBO,
            1U
        ) != VulkanResult::VK_SUCCESS
    )
        throw std::runtime_error ("Graphics Pipeline initialization failed");

    this->_renderPass = this->_graphicsPipeline.getRenderPassPtr();

}

void engine::VulkanTriangleApplication::createFrameBuffers() noexcept(false) {
    if ( this->_frameBufferCollection.setup ( this->_renderPass ) != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ( "Frame Buffers Creation Failure" );
}

#pragma clang diagnostic pop

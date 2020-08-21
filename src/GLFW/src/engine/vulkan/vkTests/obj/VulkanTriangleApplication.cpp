//
// Created by vladl on 05/08/2020.
//

#include "VulkanTriangleApplication.h"
#include <src/GLFW/src/engine/vulkan/vkUtils/VStdUtils.h>
#include <map>
#include <obj/util/settings/SettingsSharedContainer.h>
#include <obj/util/settings/SettingOptionGraphics.h>

const char* engine::VulkanTriangleApplication::DEFAULT_TITLE = "Vulkan Application";

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
    auto resolution = new engine::ResolutionSetting( this->_width, this->_height );

    SettingsSharedContainer::getInstance().put( resolution );

    delete resolution;
}

void engine::VulkanTriangleApplication::run() noexcept (false) {
    this->initSettings();
    this->initWindow();
    this->initVulkan();
    this->createGraphicsPipeline();
    this->createFrameBuffers();
    this->createCommandPoolsAndBuffers();
    this->createSynchronizationElements();
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

void engine::VulkanTriangleApplication::createSurface() noexcept(false) {
    if( this->_vulkanSurface.setup(this->_window, this->_vulkanInstance) != VK_SUCCESS )
        throw std::runtime_error("failed to create vulkan surface");
}

static inline std::vector < const engine::VQueueFamily* > internalGatherGraphicsAndPresentQueueFamilies( const engine::VQueueFamilyCollection& collection ) noexcept {

//    for( const auto & queueFamily : collection.getQueueFamilies() )
//        std::cout << "FIndex : " << queueFamily.getQueueFamilyIndex() << ", present : " << queueFamily.isPresentCapable() << '\n';

    auto queueFamilies = collection.getFlagsCapableQueueFamilies( engine::VQueueFamily::GRAPHICS_FLAG | engine::VQueueFamily::PRESENT_FLAG );

//    std::cout << "Found " << queueFamilies.size() << " graphics and present capable queue families";

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
//    if( VulkanTriangleApplication::VULKAN_EXT_CHECK ) {
//        VExtension::printExtensions(std::cout);
//    }

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

    if( queues.size() == 1 ) // graphics & present queues in same family
        deviceFactory.addQueue( * queues[0], 1.0f );
    else {
        deviceFactory.addQueue( * queues[0], 1.0f );
        deviceFactory.addQueue( * queues[1], 1.0f );
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

void engine::VulkanTriangleApplication::createSynchronizationElements() noexcept(false) {
    this->_imageAvailableSemaphore.setup( this->_vulkanLogicalDevice );
    this->_renderFinishedSemaphore.setup( this->_vulkanLogicalDevice );
}

#pragma clang diagnostic pop

void engine::VulkanTriangleApplication::mainLoop() noexcept (false) {
    uint32 imageIndex;
    vkAcquireNextImageKHR( this->_vulkanLogicalDevice.data(), this->_vulkanLogicalDevice.getSwapChain()->data(), UINT64_MAX, this->_imageAvailableSemaphore.data(), VK_NULL_HANDLE, & imageIndex );

    static VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

    if ( this->_commandBufferCollection.getCommandBuffers()[ imageIndex ].submit(
            waitStages,
            & this->_imageAvailableSemaphore,
            1U,
            & this->_renderFinishedSemaphore,
            1U
        ) != VulkanResult::VK_SUCCESS
    )
        throw std::runtime_error ( "Command Buffer Submit Failure" );

}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"
void engine::VulkanTriangleApplication::cleanup() noexcept (false) {

    this->_imageAvailableSemaphore.cleanup();
    this->_renderFinishedSemaphore.cleanup();

    this->_commandPool.cleanup();

    this->_frameBufferCollection.cleanup();

    this->_graphicsPipeline.cleanup();

//    this->_renderPass.cleanup(); happens in graphics pipeline cleanup

    this->_vertexShader.cleanup();
    this->_fragmentShader.cleanup();

    this->_vulkanLogicalDevice.cleanup();

    delete this->_vulkanQueueFamilyCollection;

    if( enableValidationLayers )
        this->_vulkanMessenger.clean();

    this->_vulkanSurface.clean();
    this->_vulkanInstance.clean();

    glfwDestroyWindow(this->_window);

    glfwTerminate();
}

void engine::VulkanTriangleApplication::createCommandPoolsAndBuffers() noexcept(false) {
    this->_commandPool.setup( this->_vulkanLogicalDevice );

    if ( this->_commandBufferCollection.allocate( this->_commandPool, this->_frameBufferCollection ) != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ( "Command Buffers Allocation Error" );

    if ( this->_commandBufferCollection.startRecord( this->_graphicsPipeline ) != VulkanResult::VK_SUCCESS )
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

void engine::VulkanTriangleApplication::createGraphicsPipeline() noexcept(false) {
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

    VulkanPipelineShaderStageCreateInfo shaderStages [] = {
        this->_vertexShader.getShaderStageInfo(),
        this->_fragmentShader.getShaderStageInfo()
    };

    // happens in pipeline setup
//    if ( this->_renderPass.setup( this->_vulkanLogicalDevice ) != VulkanResult::VK_SUCCESS )
//        throw std::runtime_error ("Render Pass initialization failed");

    if ( this->_graphicsPipeline.setup( shaderStages, 2, this->_vulkanLogicalDevice ) != VulkanResult::VK_SUCCESS )
        throw std::runtime_error ("Graphics Pipeline initialization failed");

    this->_renderPass = this->_graphicsPipeline.getRenderPassPtr();

}

void engine::VulkanTriangleApplication::createFrameBuffers() noexcept(false) {
    this->_frameBufferCollection.setup ( this->_renderPass );
}

#pragma clang diagnostic pop
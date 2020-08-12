//
// Created by vladl on 05/08/2020.
//

#include "VulkanTriangleApplication.h"
#include <src/GLFW/src/engine/vulkan/vkObj/instance/extension/VExtension.h>
#include <src/GLFW/src/engine/vulkan/vkUtils/VStdUtils.h>
//#include <vkObj/instance/device/VPhysicalDevice.h>
#include <map>
#include <vkObj/instance/device/queue/VQueueFamily.h>
#include <vkObj/instance/device/VLogicalDevice.h>

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
        queueFamily.debugPrintQueueFamily(std::cout, "\t");
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

void engine::VulkanTriangleApplication::run() noexcept (false) {
    this->initWindow();
    this->initVulkan();
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

    testSurfaceCheckPhysicalDeviceSupport( this->_vulkanSurface, this-> );
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"
#pragma ide diagnostic ignored "UnreachableCode"
inline void engine::VulkanTriangleApplication::initVulkan() noexcept (false) {
    if( VulkanTriangleApplication::VULKAN_EXT_CHECK ) {
        VExtension::printExtensions(std::cout);
    }

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

//    engine::VQueueFamilyCollection queueFamilyCollection( this->_vulkanPhysicalDevice ) ;
    this->_vulkanQueueFamilyCollection = new VQueueFamilyCollection ( this->_vulkanPhysicalDevice );

    queueFamilyTests( * this->_vulkanQueueFamilyCollection );

    engine::VLogicalDevice::VLogicalDeviceFactory deviceFactory;

    deviceFactory
        .withQueueCount(1U)
        .setPriorityForQueue(1.0f, 0U);

    if ( enableValidationLayers )
        deviceFactory.withValidationLayers( this->_vulkanValidationLayerCollection );

//    auto logicalDevice = deviceFactory.build(queueFamilyCollection.getGraphicsCapableQueueFamilies()[0]);

//    std::cout << logicalDevice.data() << '\n';
//    for( const auto & queue : logicalDevice.getQueues() )
//        std::cout << queue.getQueueHandler() << '\n';

    this->_vulkanLogicalDevice = deviceFactory.build(this->_vulkanQueueFamilyCollection->getGraphicsCapableQueueFamilies()[0]);

    std::cout << this->_vulkanLogicalDevice->data() << '\n';
    for( const auto & queue : this->_vulkanLogicalDevice->getQueues() )
        std::cout << queue.getQueueHandler() << '\n';
}
#pragma clang diagnostic pop

void engine::VulkanTriangleApplication::mainLoop() noexcept (false) {

}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"
void engine::VulkanTriangleApplication::cleanup() noexcept (false) {
    delete this->_vulkanQueueFamilyCollection;
    delete this->_vulkanLogicalDevice;

    if( enableValidationLayers )
        this->_vulkanMessenger.clean();

    this->_vulkanSurface.clean();
    this->_vulkanInstance.clean();

    glfwDestroyWindow(this->_window);

    glfwTerminate();
}

void engine::VulkanTriangleApplication::autoPickPhysicalDevice() noexcept(false) {
//    VPhysicalDevice::debugPrintAvailablePhysicalDevices( this->_vulkanInstance, std::cout );
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

#pragma clang diagnostic pop
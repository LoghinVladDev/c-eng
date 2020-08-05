//
// Created by vladl on 05/08/2020.
//

#include "VulkanTriangleApplication.h"
#include <vkDefs/vkDefinitions.h>

const char* engine::VulkanTriangleApplication::DEFAULT_TITLE = "Vulkan Application";

engine::VulkanTriangleApplication::VulkanTriangleApplication(uint32 width, uint32 height) noexcept :
    _width(width),
    _height(height){

}

[[nodiscard]] static VulkanResult createDebugMessengerExtension (
    VulkanInstance                         instance,
    const VulkanDebugMessengerCreateInfo * createInfoPtr,
    const VulkanAllocationCallbacks      * allocatorPtr,
    VulkanDebugMessenger                 * messengerPtr
) noexcept {
    auto function = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, __VULKAN_INSTANCE_PROC_ADDRESS_CREATE_DEBUG_UTIL_MESSENGER_EXT);

    if( function == nullptr )
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    return function( instance, createInfoPtr, allocatorPtr, messengerPtr );
}

void destroyDebugMessengerExtension (
    VulkanInstance                         instance,
    VulkanDebugMessenger                   debugMessenger,
    const VulkanAllocationCallbacks      * allocatorPtr
) noexcept {
    auto function = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr( instance, __VULKAN_INSTANCE_PROC_ADDRESS_DESTROY_DEBUG_UTIL_MESSENGER_EXT );

    if( function == nullptr )
        return;
    function( instance, debugMessenger, allocatorPtr );
}

static void populateDebugMessengerCreateInfo ( VulkanDebugMessengerCreateInfo * createInfo ) {
    *createInfo = {};

    createInfo->sType            = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo->messageSeverity  = engine::VulkanTriangleApplication::DEFAULT_DEBUG_MESSAGE_SEVERITY;
    createInfo->messageType      = engine::VulkanTriangleApplication::DEFAULT_DEBUG_MESSAGE_TYPE;
    createInfo->pfnUserCallback  = engine::ValidationLayer::getValidationLayerDebugCallbackFunctionPointer();
    createInfo->pUserData        = nullptr;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"
void engine::VulkanTriangleApplication::setupDebugMessenger() noexcept (false) {

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnreachableCode"

    if ( ! enableValidationLayers ) return;

#pragma clang diagnostic pop

    VulkanDebugMessengerCreateInfo createInfo {};
    populateDebugMessengerCreateInfo( & createInfo );

    if ( createDebugMessengerExtension( this->_instance, &createInfo, nullptr, & this->_debugMessenger ) != VK_SUCCESS )
        throw std::runtime_error("debug messenger setup failure");
}
#pragma clang diagnostic pop

[[nodiscard]] const std::vector < VulkanExtensionProperties > * engine::VulkanTriangleApplication::getVulkanExtensions() const noexcept {
    return this->_extensionsPtr;
}

void engine::VulkanTriangleApplication::checkExtensions() noexcept {
    uint32 extensionCount = 0;
    vkEnumerateInstanceExtensionProperties( nullptr, & extensionCount, nullptr );

    this->_extensionsPtr = new std::vector < VulkanExtensionProperties > ( extensionCount );

    vkEnumerateInstanceExtensionProperties( nullptr, & extensionCount, this->_extensionsPtr->data() );

    this->printExtensions();
}

void engine::VulkanTriangleApplication::printExtensions() const noexcept {
    if(this->_extensionsPtr == nullptr) {
        std::cout << "Extensions not queried!\n";
    } else {
        std::cout << "Extensions : \n";
        for( const auto & extension : *this->_extensionsPtr ) {
            std::cout << '\t' << extension.extensionName << '\n';
        }
    }
}

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

#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"
[[nodiscard]] static inline std::vector < GLFWExtensionLiteral > getRequiredExtensions() noexcept {
    uint32                      glfwExtensionCount = 0U;
    GLFWExtensionLiteralArray   glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions( & glfwExtensionCount );

    std::vector < GLFWExtensionLiteral > extensions ( glfwExtensions, glfwExtensions + glfwExtensionCount );

    if( enableValidationLayers ) {
        extensions.push_back( VK_EXT_DEBUG_UTILS_EXTENSION_NAME );
    }

    return extensions;
}
#pragma clang diagnostic pop

#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"
inline VulkanResult engine::VulkanTriangleApplication::createVulkanInstance() noexcept {
    VulkanApplicationInfo           applicationInfo{};
    VulkanInstanceCreateInfo        createInfo{};
    VulkanDebugMessengerCreateInfo  debugCreateInfo{};

    applicationInfo.sType               = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    applicationInfo.pApplicationName    = VulkanTriangleApplication::DEFAULT_TITLE;
    applicationInfo.applicationVersion  = VK_MAKE_VERSION(1U, 0U, 0U);  // NOLINT(hicpp-signed-bitwise)
    applicationInfo.pEngineName         = "No Engine";
    applicationInfo.engineVersion       = VK_MAKE_VERSION(1U, 0U, 0U);  // NOLINT(hicpp-signed-bitwise)
    applicationInfo.apiVersion          = VK_API_VERSION_1_0;                               // NOLINT(hicpp-signed-bitwise)

    createInfo.sType                    = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo         = ( & applicationInfo );

    if( enableValidationLayers ) {
        static auto _persistent_validationLayerLiterals = this->_validationLayerCollection.getValidationLayerLiterals();

        populateDebugMessengerCreateInfo( & debugCreateInfo );

        createInfo.enabledLayerCount                    = static_cast< uint32 > ( _persistent_validationLayerLiterals.size() );
        createInfo.ppEnabledLayerNames                  = _persistent_validationLayerLiterals.data();
        createInfo.pNext                                = (VulkanDebugMessengerCreateInfo * ) & debugCreateInfo;

    } else {

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnreachableCode"

        createInfo.enabledLayerCount                    = VULKAN_LAYERS_NONE;
        createInfo.pNext                                = nullptr;

#pragma clang diagnostic pop

    }

    auto extensions = getRequiredExtensions();
    createInfo.enabledExtensionCount    = static_cast< uint32 > ( extensions.size() );
    createInfo.ppEnabledExtensionNames  = extensions.data();

    return vkCreateInstance( & createInfo, nullptr, & this->_instance );
}
#pragma clang diagnostic pop

#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"
inline void engine::VulkanTriangleApplication::initVulkan() noexcept (false) {
    if( VulkanTriangleApplication::VULKAN_EXT_CHECK ) {
        this->checkExtensions();

        std::cout << "\n\n";
    }

    if( enableValidationLayers ) {
        ValidationLayer::debugPrintAvailableValidationLayers();

        std::cout << "\nRequested Validation Layers : \n";

        for( const auto & layer : this->_validationLayerCollection.getValidationLayers() ) {
            std::cout << '\t' << layer.getLiteral() << '\n';
        }

        if( ! ValidationLayer::checkValidationLayerSupport(this->_validationLayerCollection) ) {
            throw std::runtime_error("requested validation layers are not available!");
        }

        std::cout << "\nRequested Layers are available!\n";
    }

    if( this->createVulkanInstance() != VK_SUCCESS ) {
        throw std::runtime_error("failed to create Vulkan instance");
    }

    this->setupDebugMessenger();
}
#pragma clang diagnostic pop

void engine::VulkanTriangleApplication::mainLoop() noexcept (false) {

}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"
void engine::VulkanTriangleApplication::cleanup() noexcept (false) {
    delete this->_extensionsPtr;

    if( enableValidationLayers )
        destroyDebugMessengerExtension( this->_instance, this->_debugMessenger, nullptr );

    vkDestroyInstance(this->_instance, nullptr);

    glfwDestroyWindow(this->_window);

    glfwTerminate();
}
#pragma clang diagnostic pop
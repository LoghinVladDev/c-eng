//
// Created by vladl on 06/08/2020.
//

#include "VExtension.h"

bool engine::VExtension::_extensionsQueried = false;
std::vector < VulkanExtensionProperties > engine::VExtension::_extensions = std::vector < VulkanExtensionProperties > ();

void engine::VExtension::queryExtensions() noexcept {
    if( VExtension::_extensionsQueried )
        return;

    uint32 extensionCount = 0;
    vkEnumerateInstanceExtensionProperties( nullptr, & extensionCount, nullptr );

    VExtension::_extensions = std::vector < VulkanExtensionProperties > ( extensionCount );

    vkEnumerateInstanceExtensionProperties( nullptr, & extensionCount, VExtension::_extensions.data() );
}

void engine::VExtension::printExtensions(std::ostream& outputBuffer) noexcept {
    if ( ! VExtension::_extensionsQueried )
        VExtension::queryExtensions();

    outputBuffer << "\nExtensions : \n";
    for(const auto & extension : VExtension::_extensions) {
        outputBuffer << "\t" << extension.extensionName << '\n';
    }
}

const std::vector < VulkanExtensionProperties > & engine::VExtension::getAvailableExtensions() noexcept {
    if( ! VExtension::_extensionsQueried )
        VExtension::queryExtensions();

    return VExtension::_extensions;
}

std::vector < GLFWExtensionLiteral > engine::VExtension::getGLFWRequiredExtensions(bool enableValidationLayers) noexcept {
    uint32                      glfwExtensionsCount = 0U;
    GLFWExtensionLiteralArray   glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions( & glfwExtensionsCount );
    std::vector < GLFWExtensionLiteral > extensions ( glfwExtensions, glfwExtensions + glfwExtensionsCount );

    if( enableValidationLayers )
        extensions.push_back( VK_EXT_DEBUG_UTILS_EXTENSION_NAME );

    return extensions;
}
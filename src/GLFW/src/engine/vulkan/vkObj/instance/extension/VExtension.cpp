//
// Created by vladl on 06/08/2020.
//

#include "VExtension.h"
//
//bool engine::VExtension::_extensionsQueried = false;
//std::vector < VulkanExtensionProperties > engine::VExtension::_extensions = std::vector < VulkanExtensionProperties > ();
//
//void engine::VExtension::queryExtensions() noexcept {
//    if( VExtension::_extensionsQueried )
//        return;
//
//    uint32 extensionCount = 0;
//    vkEnumerateInstanceExtensionProperties( nullptr, & extensionCount, nullptr );
//
//    VExtension::_extensions = std::vector < VulkanExtensionProperties > ( extensionCount );
//
//    vkEnumerateInstanceExtensionProperties( nullptr, & extensionCount, VExtension::_extensions.data() );
//}
//

engine::VExtensionCollection engine::VExtensionCollection::getAllAvailableExtensions() noexcept {
    VExtensionCollection collection;

    uint32 extensionCount = 0U;
    vkEnumerateInstanceExtensionProperties( nullptr, & extensionCount, nullptr );

    std::vector < VulkanExtensionProperties > extensionsProperties (extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, & extensionCount, extensionsProperties.data() );

    for( const auto & extensionProperties : extensionsProperties ) {
        collection._extensions.emplace_back( extensionProperties );
    }

    return collection;
}

#ifndef NDEBUG

void engine::VExtension::debugPrint(std::ostream & buffer, const char * prefix) const noexcept {
    buffer << prefix << "Extension : \n";
    buffer << prefix << "\tName : " << this->_extensionProperties.extensionName << '\n';
    buffer << prefix << "\tSpec Version : " << this->_extensionProperties.specVersion << '\n';
}

#endif

#ifndef NDEBUG

void engine::VExtensionCollection::debugPrint(std::ostream & buffer, const char* prefix) const noexcept {
    buffer << prefix << "Extension Collection : \n";

    if ( this->_extensions.empty() )
        buffer << prefix << "\t" << "<empty>\n";

    for( const auto& extension : this->_extensions )
        extension.debugPrint( buffer, std::string(prefix).append("\t").c_str() );
}

bool engine::VExtensionCollection::contains(const engine::VExtensionCollection & otherCollection) const noexcept {
    for ( const auto& otherCollectionExtension : otherCollection._extensions ) {
        if ( this->contains( otherCollectionExtension ) )
            return true;
    }
    return false;
}

#endif

//void engine::VExtension::printExtensions(std::ostream& outputBuffer) noexcept {
//    if ( ! VExtension::_extensionsQueried )
//        VExtension::queryExtensions();
//
//    outputBuffer << "\nExtensions : \n";
//    for(const auto & extension : VExtension::_extensions) {
//        outputBuffer << "\t" << extension.extensionName << '\n';
//    }
//}
//
//const std::vector < VulkanExtensionProperties > & engine::VExtension::getAvailableExtensions() noexcept {
//    if( ! VExtension::_extensionsQueried )
//        VExtension::queryExtensions();
//
//    return VExtension::_extensions;
//}
//
//std::vector < GLFWExtensionLiteral > engine::VExtension::getGLFWRequiredExtensions(bool enableValidationLayers) noexcept {
//    uint32                      glfwExtensionsCount = 0U;
//    GLFWExtensionLiteralArray   glfwExtensions;
//
//    glfwExtensions = glfwGetRequiredInstanceExtensions( & glfwExtensionsCount );
//    std::vector < GLFWExtensionLiteral > extensions ( glfwExtensions, glfwExtensions + glfwExtensionsCount );
//
//    if( enableValidationLayers )
//        extensions.push_back( VK_EXT_DEBUG_UTILS_EXTENSION_NAME );
//
//    return extensions;
//}

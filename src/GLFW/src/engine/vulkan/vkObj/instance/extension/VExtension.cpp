//
// Created by vladl on 06/08/2020.
//

#include "VExtension.h"
#include "VExtensionDefs.h"

[[nodiscard]] static inline VExtensionLiteral getLiteralByType ( engine::VExtension::VExtensionType type ) noexcept (false) {
    switch ( type ) {
        case engine::VExtension::VExtensionType::KHRONOS_SWAPCHAIN : return ( __V_EXTENSION_TYPE_KHR_SWAPCHAIN );
        
        default : throw engine::EngineVExtensionUnknownType();
    }
}  

engine::VExtension::VExtension( engine::VExtension::VExtensionType type ) noexcept (false) {
    std::strcpy( this->_extensionProperties.extensionName, getLiteralByType ( type ) );
}

[[nodiscard]] bool engine::VExtensionCollection::contains ( engine::VExtension::VExtensionType type ) const noexcept {
    for ( const auto & extension : this->_extensions ) // NOLINT(readability-use-anyofallof)
        if ( std::strcmp ( extension.getName(), getLiteralByType( type ) ) == 0 )
            return true;
    return false;
}

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

engine::VExtensionCollection engine::VExtensionCollection::getPhysicalDeviceAvailableExtensions( const VPhysicalDevice & device ) noexcept {
    VExtensionCollection collection;

    uint32 extensionCount = 0U;
    vkEnumerateDeviceExtensionProperties( device.data(), nullptr, &extensionCount, nullptr );

    std::vector < VulkanExtensionProperties > extensionsProperties ( extensionCount );
    vkEnumerateDeviceExtensionProperties( device.data(), nullptr, &extensionCount, extensionsProperties.data() );

    for ( const auto& extensionProperties : extensionsProperties ) {
        collection._extensions.emplace_back( extensionProperties );
    }

    return collection;
}

[[nodiscard]] std::vector < VulkanExtensionProperties > engine::VExtensionCollection::getExtensionsProperties () const noexcept {
    std::vector < VulkanExtensionProperties > extensionsProperties ( this->_extensions.size() );

    for ( const auto & extension : this->_extensions )
        extensionsProperties.emplace_back ( extension.data() );

    return extensionsProperties;
}


[[nodiscard]] std::vector < const char * > engine::VExtensionCollection::getExtensionNames () const noexcept {
    std::vector < const char * > extensionNames ;

    for ( const auto & extension : this->_extensions ) {
        extensionNames.push_back(extension.data().extensionName);
    }

    return extensionNames;
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
    for ( const auto& otherCollectionExtension : otherCollection._extensions ) { // NOLINT(readability-use-anyofallof)
        if ( this->contains( otherCollectionExtension ) )
            return true;
    }
    return false;
}

#endif

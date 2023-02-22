//
// Created by vladl on 06/08/2020.
//

#include "VExtension.hpp"
#include "VExtensionDefs.h"

#include <VPhysicalDevice.hpp>

/**
 * @brief internal function used to get Extension Literal from Extension Type
 *
 * @param type : engine::VExtension::Type = type of extension
 *
 * @throws engine::EngineVExtensionUnknownType if
 *      given type of extension that does not exist
 *
 * @return VExtensionLiteral = Literal of Extension ( StringLiteral )
 */
[[nodiscard]] static inline VExtensionLiteral getLiteralByType ( engine::VExtension::Type type ) noexcept (false) {
    switch ( type ) { // NOLINT(hicpp-multiway-paths-covered)
        case engine::VExtension::Type::KHRONOS_SWAPCHAIN : return ( __V_EXTENSION_TYPE_KHR_SWAPCHAIN );
        
        default : throw engine::EngineVExtensionUnknownType();
    }
}  

engine::VExtension::VExtension( engine::VExtension::Type type ) noexcept (false) : VRenderObject() {
#if !defined(_MSC_VER)
    std::strcpy( this->_extensionProperties.extensionName, getLiteralByType ( type ) );
#else
    strcpy_s( this->_extensionProperties.extensionName, 256, getLiteralByType(type) );
#endif
}

auto engine::VExtensionCollection::contains ( engine::VExtension::Type type ) const noexcept -> bool {
    for ( const auto & extension : this->_extensions ) // NOLINT(readability-use-anyofallof)
        if ( std::strcmp ( extension.getName(), getLiteralByType( type ) ) == 0 )
            return true;
    return false;
}

auto engine::VExtensionCollection::getAllAvailableExtensions() noexcept -> engine::VExtensionCollection {
    VExtensionCollection collection;

    uint32 extensionCount = 0U; /// query number of extensions first
    vkEnumerateInstanceExtensionProperties( nullptr, & extensionCount, nullptr );

    /// query all extension properties
    std::vector < VulkanExtensionProperties > extensionsProperties (extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, & extensionCount, extensionsProperties.data() );

    for( const auto & extensionProperties : extensionsProperties ) {
        collection._extensions.emplace_back( extensionProperties ); /// emplace extensions from properties
    }

    return collection;
}

auto engine::VExtensionCollection::getPhysicalDeviceAvailableExtensions(
        VPhysicalDevice const & device
) noexcept -> engine::VExtensionCollection {
    VExtensionCollection collection;

    uint32 extensionCount = 0U; /// acquire count first
    vkEnumerateDeviceExtensionProperties( device.data(), nullptr, &extensionCount, nullptr );

    /// acquire properties of extensions supported by device
    std::vector < VulkanExtensionProperties > extensionsProperties ( extensionCount );
    vkEnumerateDeviceExtensionProperties( device.data(), nullptr, &extensionCount, extensionsProperties.data() );

    for ( const auto& extensionProperties : extensionsProperties ) {
        collection._extensions.emplace_back( extensionProperties ); /// emplace
    }

    return collection;
}

auto engine::VExtensionCollection::getExtensionsProperties () const noexcept -> std::vector < VulkanExtensionProperties > {
    std::vector < VulkanExtensionProperties > extensionsProperties ( this->_extensions.size() );

    for ( const auto & extension : this->_extensions )
        extensionsProperties.emplace_back ( extension.data() );

    return extensionsProperties;
}

auto engine::VExtensionCollection::getExtensionNames () const noexcept -> std::vector < StringLiteral > {
    std::vector < const char * > extensionNames ;

    for ( const auto & extension : this->_extensions ) {
        extensionNames.push_back(extension.data().extensionName);
    }

    return extensionNames;
}

#ifndef NDEBUG

auto engine::VExtension::debugPrint(
        std::ostream & buffer,
        StringLiteral prefix
) const noexcept -> void {
    buffer << prefix << "Extension : \n";
    buffer << prefix << "\tName : " << this->_extensionProperties.extensionName << '\n';
    buffer << prefix << "\tSpec Version : " << this->_extensionProperties.specVersion << '\n';
}

#endif

#ifndef NDEBUG

auto engine::VExtensionCollection::debugPrint(
        std::ostream & buffer,
        StringLiteral prefix
) const noexcept -> void {
    buffer << prefix << "Extension Collection : \n";

    if ( this->_extensions.empty() )
        buffer << prefix << "\t" << "<empty>\n";

    for( const auto& extension : this->_extensions )
        extension.debugPrint( buffer, std::string(prefix).append("\t").c_str() );
}

#endif

auto engine::VExtensionCollection::contains(engine::VExtensionCollection const & otherCollection) const noexcept -> bool {
    for ( const auto& otherCollectionExtension : otherCollection._extensions ) { // NOLINT(readability-use-anyofallof)
        if ( this->contains( otherCollectionExtension ) )
            return true;
    }
    return false;
}

#include <sstream>
auto engine::VExtensionCollection::toString() const noexcept -> String {
    std::stringstream oss;

    oss << "VExtensionCollection { extensions = [ ";
    for (auto const & item : this->_extensions)
        oss << item.toString() << ", ";

    auto s = oss.str();
    return s.substr(s.size() - 2).append(" ]}");
}
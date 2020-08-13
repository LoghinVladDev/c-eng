//
// Created by vladl on 06/08/2020.
//

#ifndef ENG1_VEXTENSION_H
#define ENG1_VEXTENSION_H
#include <engineVulkanPreproc.h>
#include <vkDefs/vkDefinitions.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <algorithm>
#include <vector>
#include <cstring>

namespace engine {

    class VExtension {
    private:
        //// private variables
        VulkanExtensionProperties _extensionProperties {};

        //// private functions

    public:
        //// public variables
        VExtension ( ) noexcept = default;

        explicit VExtension ( const VulkanExtensionProperties& properties) noexcept {
            this->_extensionProperties = properties;
        }

        explicit VExtension ( const char* literal ) noexcept {
            std::strncpy( this->_extensionProperties.extensionName, literal, 0x100 );
        }

        //// public functions

        [[nodiscard]] const VulkanExtensionProperties & data() const noexcept {
            return this->_extensionProperties;
        }

        [[nodiscard]] const char* getName() const noexcept {
            return this->_extensionProperties.extensionName;
        }

        [[nodiscard]] uint32 getSpecVersion () const noexcept {
            return this->_extensionProperties.specVersion;
        }

#ifndef NDEBUG
    void debugPrint ( std::ostream&, const char* = "" ) const noexcept;
#endif
    };

    class VExtensionCollection {
    private:
        //// private variables
        std::vector < VExtension > _extensions;

        //// private functions

    public:
        //// public variables

        //// public functions

        VExtensionCollection() noexcept = default;

//        void query () noexcept;

        [[nodiscard]] const std::vector < VExtension > & getExtensions () const noexcept {
            return this->_extensions;
        }

        [[nodiscard]] bool contains ( const VExtension& obj ) const noexcept {

//            return std::ranges::any_of (); windows is always behind
            for( const auto & extension : this->_extensions ) // NOLINT(readability-use-anyofallof)
                if ( std::strcmp( extension.getName(), obj.getName() ) == 0 )
                    return true;
            return false;
        }

        [[nodiscard]] bool contains ( const VExtensionCollection & ) const noexcept;

        void addExtension ( const VExtension& extension ) noexcept {
            if( this->contains(extension) )
                return;
            this->_extensions.push_back( extension );
        }

        void addExtensions ( const VExtensionCollection& extensionCollection ) noexcept {
            for( const auto & extension : extensionCollection._extensions ) {
                if ( this->contains( extension ) )
                    continue;
                this->_extensions.push_back( extension );
            }
        }

        static VExtensionCollection getAllAvailableExtensions () noexcept;

#ifndef NDEBUG
        void debugPrint ( std::ostream&, const char * = "" ) const noexcept;
#endif
    };

//
//    class VExtension {
//    private:
//        //// private variables
//        static bool                                        _extensionsQueried;
//        static std::vector < VulkanExtensionProperties >   _extensions;
//
//        //// private functions
//
//    public:
//        //// public variables
//
//        //// public functions
//        static void queryExtensions() noexcept;
//        static void printExtensions(std::ostream&) noexcept;
//        static const std::vector < VulkanExtensionProperties > & getAvailableExtensions() noexcept;
//        static std::vector < GLFWExtensionLiteral > getGLFWRequiredExtensions(bool = false) noexcept;
//    };

}


#endif //ENG1_VEXTENSION_H

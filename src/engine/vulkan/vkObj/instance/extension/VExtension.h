//
// Created by vladl on 06/08/2020.
//


#ifndef ENG1_VEXTENSION_H
#define ENG1_VEXTENSION_H
#include <engineVulkanPreproc.h>
#include <vkDefinitions.h>
#include <vulkanExplicitTypes.h>
#include <algorithm>
#include <vector>
#include <cstring>
#include <VPhysicalDevice.h>

namespace engine {

    class EngineVExtensionUnknownType : public std::exception {
    public:
        [[nodiscard]] const char * what() const noexcept override {
            return "Unknown Extension Type given";
        } 
    };

    class VPhysicalDevice;

    class VExtension {
    private:
        //// private variables
        VulkanExtensionProperties _extensionProperties {};

        //// private functions

    public:
        typedef enum : uint8 {
            KHRONOS_SWAPCHAIN
        } VExtensionType;

        //// public variables
        VExtension ( ) noexcept = default;

        explicit VExtension ( const VulkanExtensionProperties& properties) noexcept {
            this->_extensionProperties = properties;
        }

        // explicit VExtension ( const char* literal ) noexcept {
        //     std::strncpy( this->_extensionProperties.extensionName, literal, 0x100 );
        // }

        explicit VExtension ( VExtensionType ) noexcept (false);

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

        [[nodiscard]] bool empty() const noexcept {
            return this->_extensions.empty();
        }

        [[nodiscard]] uint32 size() const noexcept {
            return static_cast<uint32>(this->_extensions.size());
        }

        [[nodiscard]] const std::vector < VExtension > & getExtensions () const noexcept {
            return this->_extensions;
        }

        [[nodiscard]] std::vector < VulkanExtensionProperties > getExtensionsProperties () const noexcept;
        [[nodiscard]] std::vector < const char * > getExtensionNames() const noexcept;

        [[nodiscard]] bool contains ( const VExtension& obj ) const noexcept {
//            return std::ranges::any_of (); windows is always behind
            for( const auto & extension : this->_extensions ) // NOLINT(readability-use-anyofallof)
                if ( std::strcmp( extension.getName(), obj.getName() ) == 0 )
                    return true;
            return false;
        }

        [[nodiscard]] bool contains ( VExtension::VExtensionType ) const noexcept;

        [[nodiscard]] bool contains ( const VExtensionCollection & ) const noexcept;

        void add ( const VExtension& extension ) noexcept {
            if( this->contains(extension) )
                return;
            this->_extensions.push_back( extension );
        }

        void add ( const VExtensionCollection& extensionCollection ) noexcept {
            for( const auto & extension : extensionCollection._extensions ) {
                if ( this->contains( extension ) )
                    continue;
                this->_extensions.push_back( extension );
            }
        }

        void emplace ( VExtension::VExtensionType type ) noexcept {
            if ( this->contains( type ) )
                return;
            this->_extensions.emplace_back( type );
        }

        [[nodiscard]] static VExtensionCollection getAllAvailableExtensions () noexcept;
        [[nodiscard]] static VExtensionCollection getPhysicalDeviceAvailableExtensions ( const VPhysicalDevice & ) noexcept;

#ifndef NDEBUG
        void debugPrint ( std::ostream&, const char * = "" ) const noexcept;
#endif
    };

}


#endif //ENG1_VEXTENSION_H

//
// Created by vladl on 06/08/2020.
//


#ifndef ENG1_VEXTENSION_HPP
#define ENG1_VEXTENSION_HPP
#include <engineVulkanPreproc.hpp>
#include <vkDefinitions.h>
#include <vulkanExplicitTypes.h>
#include <algorithm>
#include <vector>
#include <cstring>
//#include <VPhysicalDevice.h>
#include <CDS/String>

namespace engine {

    /**
     * @class engine::EngineVExtensionUnknownType, inherits std::exception
     *
     * @brief Exception thrown when creating/using an exception that does not exist
     */
    class EngineVExtensionUnknownType : public std::exception {
    public:

        /**
         * @brief getter function for the exception message
         *
         * @exceptsafe
         *
         * @return StringLiteral = Exception Message
         */
        [[nodiscard]] auto what() const noexcept -> StringLiteral override {
            return "Unknown Extension Type given";
        } 
    };

    /// Pre-Declaration of class to avoid circular / recursive includes
    class VPhysicalDevice;

    /**
     * @class engine::VExtension
     *
     * @brief represents an extension to the Vulkan Core API to avoid using literal values
     */
    class VExtension {
    private:
        //// private variables

        /// Structure containing extension details - version
        VulkanExtensionProperties _extensionProperties {};

        //// private functions

    public:

        /**
         * @enum engine::VExtension::Type
         *
         * @brief represents the extensions documented and supported by VExtension
         */
        typedef enum : uint8 {
            KHRONOS_SWAPCHAIN /// GPU - surface Image Swapping Object
        } Type;

        //// public variables

        /**
         * @brief Default Constructor
         *
         * @exceptsafe
         */
        VExtension ( ) noexcept = default;

        /**
         * @brief Constructor based on properties structure
         *
         * @param properties VulkanExtensionProperties cref = Constant Reference to Properties Structure
         *
         * @exceptsafe
         */
        explicit VExtension ( VulkanExtensionProperties const & properties) noexcept {
            this->_extensionProperties = properties;
        }

        /**
         * @brief Constructor based on extension type
         *
         * @param type : engine::VExtension::Type = type of extension to create
         *
         * @throws engine::EngineVExtensionUnknownType if
         *      given a type that is not supported
         */
        explicit VExtension (Type ) noexcept (false);

        //// public functions

        /**
         * @brief Getter Function for the Extension's Properties Structure
         *
         * @exceptsafe
         *
         * @return VulkanExtensionProperties cref = Constant Reference to Properties Structure
         */
        [[nodiscard]] auto data() const noexcept -> VulkanExtensionProperties const & {
            return this->_extensionProperties;
        }

        /**
         * @brief Getter Function for the Extension's Name
         *
         * @exceptsafe
         *
         * @return StringLiteral = Name of the Extension
         */
        [[nodiscard]] auto getName() const noexcept -> StringLiteral {
            return this->_extensionProperties.extensionName;
        }

        /**
         * @brief Getter Function for the Extension's Specification Version
         *
         * @exceptsafe
         *
         * @return uint32 = Spec Version of the Extension
         */
        [[nodiscard]] auto getSpecVersion () const noexcept -> uint32 {
            return this->_extensionProperties.specVersion;
        }

#ifndef NDEBUG

        /**
         * @brief Debug Function for Printing Extension Information
         *
         * @param buffer : std::ostream & = Reference to Output Buffer to put the data in
         * @param prefix : StringLiteral = string to print before each line ( ex. no. of tabs )
         *
         * @exceptsafe
         */
        auto debugPrint ( std::ostream &, StringLiteral = "" ) const noexcept -> void;
#endif
    };

    /**
     * @class engine::VExtensionCollection
     *
     * @brief represents a set/collection of Extensions
     */
    class VExtensionCollection {
    private:
        //// private variables

        /// vector of extensions
        std::vector < VExtension > _extensions;

        //// private functions

    public:
        //// public variables

        //// public functions

        /**
         * @brief Default Constructor
         *
         * @exceptsafe
         */
        VExtensionCollection() noexcept = default;

        /**
         * @brief Function checking if collection is empty
         *
         * @exceptsafe
         *
         * @return true if collection is empty, false otherwise
         */
        [[nodiscard]] auto empty() const noexcept -> bool {
            return this->_extensions.empty();
        }

        /**
         * @brief Getter function for the number of extensions in the collection
         *
         * @exceptsafe
         *
         * @return uint32 = Number of extensions in the collection
         */
        [[nodiscard]] uint32 size() const noexcept {
            return static_cast<uint32>(this->_extensions.size());
        }

        /**
         * @brief Getter function for the array of extensions in the collection
         *
         * @exceptsafe
         *
         * @return std::vector < engine::VExtension > cref = Constant Reference to a vector with Extensions
         */
        [[nodiscard]] auto getExtensions () const noexcept -> std::vector < VExtension > const & {
            return this->_extensions;
        }

        /**
         * @brief Getter for Vector of Extension Properties. Contains all Properties of contained Extensions
         *
         * @exceptsafe
         *
         * @return std::vector < VulkanExtensionProperties > = vector of Extension Properties
         */
        [[nodiscard]] auto getExtensionsProperties () const noexcept -> std::vector < VulkanExtensionProperties >;

        /**
         * @brief Getter for Vector of Extension Names. Contains all Names of contained Extensions
         *
         * @exceptsafe
         *
         * @return std::vector < StringLiteral > = vector of Extension Names
         */
        [[nodiscard]] auto getExtensionNames() const noexcept -> std::vector < StringLiteral >;

        /**
         * @brief Function checks if Extension is part of Collection
         *
         * @param obj engine::VExtension cref = Constant Reference to Extension to check
         *
         * @exceptsafe
         *
         * @return bool = true if Extension is in Collection, false otherwise
         */
        [[nodiscard]] auto contains ( VExtension const & obj ) const noexcept -> bool {
            for( const auto & extension : this->_extensions ) // NOLINT(readability-use-anyofallof)
                if ( std::strcmp( extension.getName(), obj.getName() ) == 0 )
                    return true;
            return false;
        }

        /**
         * @brief Function checks if an Extension of Type is part of Collection
         *
         * @param type : engine::VExtension::Type = Type of Extension
         *
         * @exceptsafe
         *
         * @return bool = true if collection contains extension of given type, false otherwise
         */
        [[nodiscard]] auto contains ( VExtension::Type ) const noexcept -> bool;

        /**
         * @brief Function checks if all Extensions in a given Collection are part of this Collection
         *
         * @param otherCollection : engine::VExtensionCollection cref = Constant Reference to a Collection to check all Extensions from
         *
         * @exceptsafe
         *
         * @return bool = true if collection contains all extensions from given collection, false otherwise
         */
        [[nodiscard]] auto contains ( VExtensionCollection const & ) const noexcept -> bool;

        /**
         * @brief Function adds an Extension to this Collection
         *
         * @param extension : engine::VExtension cref = Constant Reference to the Extension to be added
         *
         * @exceptsafe
         */
        auto add ( VExtension const & extension ) noexcept -> void {
            if( this->contains(extension) )
                return;
            this->_extensions.push_back( extension );
        }

        /**
         * @brief Function adds all Extensions from a given Collection to this Collection
         *
         * @param extension : engine::VExtensionCollection cref = Constant Reference to the Collection to add Extensions from
         *
         * @exceptsafe
         */
        void add ( const VExtensionCollection& extensionCollection ) noexcept {
            for( const auto & extension : extensionCollection._extensions ) {
                if ( this->contains( extension ) )
                    continue;
                this->_extensions.push_back( extension );
            }
        }

        /**
         * @brief Function emplaces new Extension based on type from Collection
         *
         * @param type : engine::VExtension::Type = type of extension to emplace
         *
         * @excetpsafe
         */
        void emplace ( VExtension::Type type ) noexcept {
            if ( this->contains( type ) )
                return;
            this->_extensions.emplace_back( type );
        }

        /**
         * @brief Function returns a Collection containing all detected extensions
         *
         * @static
         *
         * @exceptsafe
         *
         * @return engine::VExtensionCollection = Collection of all detected extensions
         */
        [[nodiscard]] static auto getAllAvailableExtensions () noexcept -> VExtensionCollection;

        /**
         * @brief Function returns a Collection containing extensions that a Physical Device can support
         *
         * @param device : engine::VPhysicalDevice cref = Constant Reference to a Physical Device to acquire Extensions supported for
         *
         * @static
         *
         * @exceptsafe
         *
         * @return engine::VExtensionCollection = Collection of Extensions that are supported by Device
         */
        [[nodiscard]] static auto getPhysicalDeviceAvailableExtensions ( const VPhysicalDevice & ) noexcept -> VExtensionCollection;

#ifndef NDEBUG

        /**
         * @brief Debug Function that prints Extension Collection Data
         *
         * @param buffer : std::ostream ref = Reference to an Output Buffer to put the data in
         * @param prefix : StringLiteral = String to be printed before each line ( eg. no. of tabs )
         *
         * @exceptsafe
         */
        auto debugPrint ( std::ostream&, StringLiteral = "" ) const noexcept -> void;
#endif
    };

}


#endif //ENG1_VEXTENSION_HPP

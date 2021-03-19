//
// Created by vladl on 07/08/2020.
//

#ifndef ENG1_VPHYSICALDEVICE_HPP
#define ENG1_VPHYSICALDEVICE_HPP

#include <engineVulkanPreproc.hpp>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/instance/VInstance.hpp>
#include <vkObj/instance/extension/VExtension.hpp>
#include <vkObj/window/surface/VSurface.hpp>
#include <vector>

#include <CDS/String>

namespace engine {

    /**
     * @class engine::EngineNullVPhysicalDevice, inherits std::exception
     *
     * @brief Exception thrown when a Physical Device is used without initialisation based on an existing Physical Device ( GPU )
     */
    class EngineNullVPhysicalDevice : public std::exception{
    public:

        /**
         * @brief getter function for the exception message
         *
         * @exceptsafe
         *
         * @return StringLiteral = Exception Message
         */
        [[nodiscard]] auto what() const noexcept -> StringLiteral override {
            return "Physical Device Attached has a VK_NULL_HANDLE physical handle";
        }
    };

    /// class pre-declarations to avoid circular / recursive includes
    class VExtension;
    class VExtensionCollection;

    /**
     * @class engine::VPhysicalDevice
     *
     * @brief Object Describes a Physical Device ( a GPU ), it is a wrapper around Vulkan's Physical Device Handling and other Physical Device Related Features
     */
    class VPhysicalDevice {
    private:
        //// private variables

        /// status variable related to query of available physical devices. Once queried, do not re-query. Not likely to
        static bool                                 _physicalDevicesQueried;

        /// vector of available Physical Device Handles
        static std::vector < VulkanPhysicalDevice > _availablePhysicalDeviceHandles;

        /// vector of available Physical Device Objects
        static std::vector < VPhysicalDevice >      _availablePhysicalDevices;


        /// handle of the contained Physical Device
        VulkanPhysicalDevice                        _physicalDeviceHandle = VK_NULL_HANDLE;

        /// properties of the contained Physical Device
        VulkanPhysicalDeviceProperties              _physicalDeviceProperties {};

        /// features of the contained Physical Device
        VulkanPhysicalDeviceFeatures                _physicalDeviceFeatures {};

        //// private functions

        /**
         * @brief Internal Function for Querying Vulkan-Capable Available Physical Devices
         *
         * @param engine::VInstance cref = Constant Reference to an initialised Vulkan Instance
         *
         * @static
         *
         * @throws std::runtime_error if
         *      no Physical Devices found capable of Vulkan Support
         */
        static auto queryAvailablePhysicalDevices( VInstance const & ) noexcept (false) -> void;
    public:

        /**
         * @struct engine::VPhysicalDevice::SwapChainSupportDetails
         *
         * @brief Container for Physical Device Swap Chain Support Details
         *
         * Contains Features supported by Physical Device regarding Swap Chain Support
         */
        typedef struct {
            /// capabilities related to Khronos Tools ( Swap Chain is Khronos-Built )
            VulkanSurfaceCapabilitiesKhronos            capabilities;
            /// formats supported for surfaces
            std::vector < VulkanSurfaceFormatKhronos >  formats;
            /// present modes to surfaces
            std::vector < VulkanPresentModeKhronos >    presentModes;
        } SwapChainSupportDetails;

        //// public variables

        //// public functions

        /**
         * @brief Default Constructor
         *
         * @exceptsafe
         */
        VPhysicalDevice() noexcept = default;

        /**
         * @brief Copy Constructor
         *
         * @param obj : engine::VPhysicalDevice cref = Object to Copy
         *
         * @exceptsafe
         */
        VPhysicalDevice( VPhysicalDevice const & obj ) noexcept {
            this->_physicalDeviceHandle     = obj._physicalDeviceHandle;
            this->_physicalDeviceProperties = obj._physicalDeviceProperties;
            this->_physicalDeviceFeatures   = obj._physicalDeviceFeatures;
        }

        /**
         * @brief "Copy" Constructor, Creates object based on Physical Device Vulkan Handle
         *
         * Acquires required features and properties
         *
         * @param deviceHandle : VulkanPhysicalDevice cref = Constant Reference to a Vulkan Physical Device Handle
         *
         * @exceptsafe
         */
        explicit VPhysicalDevice ( VulkanPhysicalDevice const & deviceHandle ) noexcept :
            _physicalDeviceHandle( deviceHandle ) {

            /// acquire properties for device
            vkGetPhysicalDeviceProperties   ( this->_physicalDeviceHandle, & this->_physicalDeviceProperties );

            /// acquire features for device
            vkGetPhysicalDeviceFeatures     ( this->_physicalDeviceHandle, & this->_physicalDeviceFeatures );
        }

        /**
         * @brief Getter for Device Properties Structure
         *
         * @exceptsafe
         *
         * @return VulkanPhysicalDeviceProperties cref = Constant Reference to Physical Device Properties Structure
         */
        [[nodiscard]] auto getPhysicalDeviceProperties () const noexcept -> VulkanPhysicalDeviceProperties const & {
            return this->_physicalDeviceProperties;
        }

        /**
         * @brief Getter for Physical Device Features Structure
         *
         * @exceptsafe
         *
         * @return VulkanPhysicalDeviceFeatures cref = Constant Reference to Physical Device Properties
         */
        [[nodiscard]] auto getPhysicalDeviceFeatures () const noexcept -> VulkanPhysicalDeviceFeatures const & {
            return this->_physicalDeviceFeatures;
        }

        /**
         * @brief Function checks if Device supports anisotropy sampling
         *
         * @exceptsafe
         *
         * @return bool = true if Device support anisotropy filtering, false otherwise
         */
        [[nodiscard]] constexpr auto anisotropySamplerSupported () const noexcept -> bool {
            return this->_physicalDeviceFeatures.samplerAnisotropy;
        }

        /**
         * @brief Function Returns a score for the Physical Device, representing Vulkan API processing power
         *
         * Calculus is heavily biased towards Dedicated GPUs
         *
         * @exceptsafe
         *
         * @return uint32 = Score of Physical Device in regards to Vulkan Calculations
         */
        [[nodiscard]] auto getPhysicalDeviceRenderRating() const noexcept -> uint32;

        /**
         * @brief Getter for Vulkan Physical Device Handler
         *
         * @exceptsafe
         *
         * @return VulkanPhysicalDevice cref = Constant Reference to Physical Device Handle
         */
        [[nodiscard]] auto data() const noexcept -> VulkanPhysicalDevice const & {
            return this->_physicalDeviceHandle;
        }

        /**
         * @brief Getter for Physical Device Memory Properties
         *
         * @exceptsafe
         *
         * @return VulkanPhysicalDeviceMemoryProperties = Structure of Memory Properties of Physical Device
         */
        [[nodiscard]] auto getMemoryProperties () const noexcept -> VulkanPhysicalDeviceMemoryProperties {
            VulkanPhysicalDeviceMemoryProperties properties;
            vkGetPhysicalDeviceMemoryProperties ( this->_physicalDeviceHandle, & properties );
            return properties;
        }

        /**
         * @brief Function Returns Capabilities of Physical Device in sustaining a Swap Chain to a Surface
         *
         * @param surface : engine::VSurface cptr = Address to Constant Surface Object
         *
         * @exceptsafe
         *
         * @return engine::VPhysicalDevice::SwapChainSupportDetails = Structure of Details regarding Swap Chain support on the given Surface
         */
        [[nodiscard]] auto querySwapChainOnSurfaceSupport ( VSurface const * ) const noexcept -> SwapChainSupportDetails;

        /**
         * @brief Function returns Physical Devices detected by a Vulkan Instance given as parameter
         *
         * @param instance : engine::VInstance cref = Constant Reference to the Instance
         *
         * @static
         *
         * @throws std::runtime_error if
         *      no Physical Devices ( GPUs ) were found supporting Vulkan
         *
         * @return std::vector < engine::VPhysicalDevice > cref = Constant Reference to the vector containing the detected Physical Devices
         */
        [[nodiscard]] static auto getAvailablePhysicalDevices ( const VInstance & instance ) noexcept (false) -> std::vector < VPhysicalDevice > const & {
            VPhysicalDevice::queryAvailablePhysicalDevices( instance );
            return VPhysicalDevice::_availablePhysicalDevices;
        }

        /**
         * @brief Function returns Physical Device Handles detected by a Vulkan Instance given as parameter
         *
         * @param instance : engine::VInstance cref = Constant Reference to the Instance
         *
         * @static
         *
         * @throws std::runtime_error if
         *      no Physical Devices ( GPUs ) were found supporting Vulkan
         *
         * @return std::vector < VulkanPhysicalDevice > cref = Constant Reference to the vector containing Physical Device Handles detected by the Instance
         */
        [[nodiscard]] static auto getAvailablePhysicalDevicesHandles ( const VInstance& instance ) noexcept -> std::vector < VulkanPhysicalDevice > const & {
            VPhysicalDevice::queryAvailablePhysicalDevices( instance );
            return VPhysicalDevice::_availablePhysicalDeviceHandles;
        }

        /**
         * @brief Function checks if Device supports given Extension
         *
         * @param extension : engine::VExtension cref = Constant Reference to Extension to check support for
         *
         * @exceptsafe
         *
         * @return bool = true if Device supports Extension, false otherwise
         */
        [[nodiscard]] auto supportsExtension  ( VExtension const & extension ) const noexcept -> bool;

        /**
         * @brief Function checks if Device supports given Extensions
         *
         * @param collection : engine::VExtensionCollection cref = Constant Reference to Collection of Extensions to check support for
         *
         * @exceptsafe
         *
         * @return bool = true if Device supports all Extensions in Collection, false otherwise
         */
        [[nodiscard]] auto supportsExtensions ( VExtensionCollection const & collection ) const noexcept -> bool;

#ifndef NDEBUG
        /**
         * @brief Function prints to buffer this Device's Properties
         *
         * @param buffer : std::ostream ref = Reference to the Output Stream to print the data in
         * @param detailedDebug : bool = if true, prints extra details
         * @param prefix : StringLiteral = prefix to be printed before each line ( ex. no. of tabs )
         *
         * @exceptsafe
         */
        auto debugPrintPhysicalDeviceProperties ( std::ostream &, bool = false, StringLiteral = "" ) const noexcept -> void;

        /**
         * @brief Function prints to buffer this Device's Sparse Properties
         *
         * @param buffer : std::ostream ref = Reference to the Output Stream to print the data in
         * @param prefix : StringLiteral = prefix to be printed before each line ( ex. no. of tabs )
         *
         * @exceptsafe
         */
        auto debugPrintPhysicalDeviceSparseProperties ( std::ostream &, StringLiteral = "") const noexcept -> void;

        /**
         * @brief Function prints to buffer this Device's Limits
         *
         * @param buffer : std::ostream ref = Reference to the Output Stream to print the data in
         * @param prefix : StringLiteral = prefix to be printed before each line ( ex. no. of tabs )
         *
         * @exceptsafe
         */
        auto debugPrintPhysicalDeviceLimits ( std::ostream&, StringLiteral = "" ) const noexcept -> void;

        /**
         * @brief Function prints to buffer this Device's Features
         *
         * @param buffer : std::ostream ref = Reference to the Output Stream to print the data in
         * @param prefix : StringLiteral = prefix to be printed before each line ( ex. no. of tabs )
         *
         * @exceptsafe
         */
        auto debugPrintPhysicalDeviceFeatures ( std::ostream &, StringLiteral = "" ) const noexcept -> void;
#endif

#ifndef NDEBUG
        /**
         * @brief Function prints all Physical Devices Detected to the buffer given
         *
         * @param instance : engine::VInstance cref = Constant Reference to the Instance that will detect the Physical Devices
         * @param buffer : std::ostream ref = Reference to the Output Buffer to put the data in
         *
         * @static
         *
         * @throws std::runtime_error if
         *      queryAvailablePhysicalDevices throws - no GPUs with Vulkan Support Found
         */
        static auto debugPrintAvailablePhysicalDevices( VInstance const &, std::ostream & ) noexcept (false) -> void;
#endif

#ifndef NDEBUG

        /**
         * @brief Function prints to buffer this Device's Basic Properties
         *
         * @param properties : VulkanPhysicalDeviceProperties cref = Constant Reference to a Physical Device Properties Structure
         * @param buffer : std::ostream ref = Reference to the Output Stream to print the data in
         * @param prefix : StringLiteral = prefix to be printed before each line ( ex. no. of tabs )
         *
         * @static
         *
         * @exceptsafe
         */
        static auto debugPrintPhysicalDeviceBasicPropertiesStructure    ( VulkanPhysicalDeviceProperties const &,       std::ostream &, StringLiteral = "" ) noexcept -> void;

        /**
         * @brief Function prints to buffer this Device's Sparse Properties
         *
         * @param sparseProperties : VulkanPhysicalDeviceSparseProperties cref = Constant Reference to a Physical Device Sparse Properties Structure
         * @param buffer : std::ostream ref = Reference to the Output Stream to print the data in
         * @param prefix : StringLiteral = prefix to be printed before each line ( ex. no. of tabs )
         *
         * @static
         *
         * @exceptsafe
         */
        static auto debugPrintPhysicalDeviceSparsePropertiesStructure   ( VulkanPhysicalDeviceSparseProperties const &, std::ostream &, StringLiteral = "" ) noexcept -> void;

        /**
         * @brief Function prints to buffer this Device's Limits
         *
         * @param properties : VulkanPhysicalDeviceProperties cref = Constant Reference to a Physical Device Limits Structure
         * @param buffer : std::ostream ref = Reference to the Output Stream to print the data in
         * @param prefix : StringLiteral = prefix to be printed before each line ( ex. no. of tabs )
         *
         * @static
         *
         * @exceptsafe
         */
        static auto debugPrintPhysicalDeviceLimitsStructure             ( VulkanPhysicalDeviceLimits const &,           std::ostream &, StringLiteral = "" ) noexcept -> void;

        /**
         * @brief Function prints to buffer this Device's Features
         *
         * @param properties : VulkanPhysicalDeviceProperties cref = Constant Reference to a Physical Device Features Structure
         * @param buffer : std::ostream ref = Reference to the Output Stream to print the data in
         * @param prefix : StringLiteral = prefix to be printed before each line ( ex. no. of tabs )
         *
         * @static
         *
         * @exceptsafe
         */
        static auto debugPrintPhysicalDeviceFeaturesStructure           ( VulkanPhysicalDeviceFeatures const &,         std::ostream &, StringLiteral = "" ) noexcept -> void;
#endif

    };




}

#endif //ENG1_VPHYSICALDEVICE_HPP

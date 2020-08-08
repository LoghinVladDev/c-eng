//
// Created by vladl on 07/08/2020.
//

#ifndef ENG1_VPHYSICALDEVICE_H
#define ENG1_VPHYSICALDEVICE_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/instance/VInstance.h>
#include <vector>
namespace engine {

    class VPhysicalDevice {
    private:
        //// private variables
        static bool                                 _physicalDevicesQueried;
        static std::vector < VulkanPhysicalDevice > _availablePhysicalDeviceHandles;
        static std::vector < VPhysicalDevice >      _availablePhysicalDevices;

        VulkanPhysicalDevice                        _physicalDeviceHandle = VK_NULL_HANDLE;
        VulkanPhysicalDeviceProperties              _physicalDeviceProperties {};
        VulkanPhysicalDeviceFeatures                _physicalDeviceFeatures {};

        //// private functions
//        VPhysicalDevice() noexcept = default;

        static void queryAvailablePhysicalDevices( const VInstance& ) noexcept (false);
//        static bool isDeviceVulkanCompatible( const VInstance&, const VPhysicalDevice & ) noexcept (false);

    public:
        //// public variables

        //// public functions
        VPhysicalDevice() noexcept = default;
        VPhysicalDevice(const VPhysicalDevice& obj) noexcept {
            this->_physicalDeviceHandle     = obj._physicalDeviceHandle;
            this->_physicalDeviceProperties = obj._physicalDeviceProperties;
            this->_physicalDeviceFeatures   = obj._physicalDeviceFeatures;
        }

        explicit VPhysicalDevice ( const VulkanPhysicalDevice& deviceHandle ) noexcept :
            _physicalDeviceHandle( deviceHandle ) {
            vkGetPhysicalDeviceProperties   ( this->_physicalDeviceHandle, & this->_physicalDeviceProperties );
            vkGetPhysicalDeviceFeatures     ( this->_physicalDeviceHandle, & this->_physicalDeviceFeatures );
        }

        [[nodiscard]] const VulkanPhysicalDeviceProperties & getPhysicalDeviceProperties () const noexcept {
            return this->_physicalDeviceProperties;
        }

        [[nodiscard]] const VulkanPhysicalDeviceFeatures & getPhysicalDeviceFeatures () const noexcept {
            return this->_physicalDeviceFeatures;
        }

        [[nodiscard]] uint32 getPhysicalDeviceRenderRating() const noexcept;

        [[nodiscard]] const VulkanPhysicalDevice & data() const noexcept {
            return this->_physicalDeviceHandle;
        }

        [[nodiscard]] static const std::vector < VPhysicalDevice > & getAvailablePhysicalDevices ( const VInstance & instance ) noexcept {
            VPhysicalDevice::queryAvailablePhysicalDevices( instance );
            return VPhysicalDevice::_availablePhysicalDevices;
        }

        [[nodiscard]] static const std::vector < VulkanPhysicalDevice > & getAvailablePhysicalDevicesHandles ( const VInstance& instance ) noexcept {
            VPhysicalDevice::queryAvailablePhysicalDevices( instance );
            return VPhysicalDevice::_availablePhysicalDeviceHandles;
        }

#ifndef NDEBUG
        void debugPrintPhysicalDeviceProperties ( std::ostream&,  bool = false, const char* = "" ) const noexcept;
        void debugPrintPhysicalDeviceSparseProperties ( std::ostream&, const char* = "") const noexcept;
        void debugPrintPhysicalDeviceLimits ( std::ostream&, const char* = "" ) const noexcept;
        void debugPrintPhysicalDeviceFeatures ( std::ostream&, const char* = "" ) const noexcept;
#endif
#ifndef NDEBUG
        static void debugPrintAvailablePhysicalDevices( const VInstance&, std::ostream& ) noexcept;
#endif

#ifndef NDEBUG
        static void debugPrintPhysicalDeviceBasicPropertiesStructure    ( const VulkanPhysicalDeviceProperties &,       std::ostream&, const char* = "" ) noexcept;
        static void debugPrintPhysicalDeviceSparsePropertiesStructure   ( const VulkanPhysicalDeviceSparseProperties &, std::ostream&, const char* = "" ) noexcept;
        static void debugPrintPhysicalDeviceLimitsStructure             ( const VulkanPhysicalDeviceLimits &,           std::ostream&, const char * = "" ) noexcept;
        static void debugPrintPhysicalDeviceFeaturesStructure           ( const VulkanPhysicalDeviceFeatures &,         std::ostream&, const char* = "" ) noexcept;
#endif

    };




}

#endif //ENG1_VPHYSICALDEVICE_H

//
// Created by vladl on 07/08/2020.
//

#include "VPhysicalDevice.h"

bool engine::VPhysicalDevice::_physicalDevicesQueried = false;
std::vector < VulkanPhysicalDevice > engine::VPhysicalDevice::_availablePhysicalDevices = std::vector < VulkanPhysicalDevice > ();

void engine::VPhysicalDevice::queryAvailablePhysicalDevices(const engine::VInstance & instance) noexcept (false) {
    if( VPhysicalDevice::_physicalDevicesQueried )
        return;

    uint32 deviceCount = 0U;

    vkEnumeratePhysicalDevices( instance.data(), & deviceCount, nullptr );

    if(deviceCount == 0U)
        throw std::runtime_error ( "failed to find Vulkan supported GPUS" );

    VPhysicalDevice::_availablePhysicalDevices = std::vector < VulkanPhysicalDevice > ( deviceCount );
    vkEnumeratePhysicalDevices( instance.data(), & deviceCount, VPhysicalDevice::_availablePhysicalDevices.data() );

    VPhysicalDevice::_physicalDevicesQueried = true;
}

void engine::VPhysicalDevice::debugPrintAvailablePhysicalDevices(const VInstance & instance, std::ostream& buffer) noexcept {
    VPhysicalDevice::queryAvailablePhysicalDevices( instance );

    buffer << "Vulkan Supported Physical Devices : \n";

    for( const auto & physicalDevice : VPhysicalDevice::_availablePhysicalDevices ) {
        // TODO : implement buffer output function for deviceProperties :: limits
        // TODO : implement buffer output function for deviceFeatures :: bitwise
        VulkanPhysicalDeviceProperties  deviceProperties;
        VulkanPhysicalDeviceFeatures    deviceFeatures;

        vkGetPhysicalDeviceProperties   ( physicalDevice, & deviceProperties );
        vkGetPhysicalDeviceFeatures     ( physicalDevice, & deviceFeatures );

        buffer << "\tDevice Properties : \n";

        buffer << "\t\tName : "                    << deviceProperties.deviceName << "\n";
        buffer << "\t\t\tDevice ID : "             << deviceProperties.deviceID << "\n";
        buffer << "\t\t\tDevice Type : "           << deviceProperties.deviceType << "\n";
        buffer << "\t\t\tAPI Version : "           << deviceProperties.apiVersion << "\n";
        buffer << "\t\t\tDriver Version : "        << deviceProperties.driverVersion << "\n";
        buffer << "\t\t\tVendor ID : "             << deviceProperties.vendorID << "\n";

//        buffer << "\t\t\tPipeline Cache UUID : "   << deviceProperties.pipelineCacheUUID << "\n"; // for some reason output in console prints weird stuff
//        buffer << "\t\t : "                      << deviceProperties.limits. << "\n";    // Structure too big
//        buffer << "\t\tDevice Sparse Properties : " << deviceProperties.sparseProperties << "\n"; // Structure private

//        buffer << "\tDevice Features : \n"; // functions in struct
    }
}
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
        static std::vector < VulkanPhysicalDevice > _availablePhysicalDevices;

        VulkanPhysicalDevice                        _physicalDevice = VK_NULL_HANDLE;

        //// private functions
        static void queryAvailablePhysicalDevices( const VInstance& ) noexcept (false);
//        static bool isDeviceVulkanCompatible( const VInstance&, const VPhysicalDevice & ) noexcept (false);

    public:
        //// public variables
        [[nodiscard]] const VulkanPhysicalDevice & data() const noexcept {
            return this->_physicalDevice;
        }

        //// public functions
        [[nodiscard]] static const std::vector < VulkanPhysicalDevice > & getAvailablePhysicalDevices ( const VInstance& instance ) noexcept {
            VPhysicalDevice::queryAvailablePhysicalDevices( instance );
            return VPhysicalDevice::_availablePhysicalDevices;
        }

        static void debugPrintAvailablePhysicalDevices( const VInstance&, std::ostream& ) noexcept;
    };

}


#endif //ENG1_VPHYSICALDEVICE_H

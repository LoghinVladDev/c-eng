//
// Created by Vlad on 07/09/2020.
//

#ifndef ENG1_VDESCRIPTORPOOL_H
#define ENG1_VDESCRIPTORPOOL_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/instance/device/VLogicalDevice.h>

namespace engine {

    class VDescriptorPool {
    private:
        //// private variables
        VulkanDescriptorPool    _handle         {VK_NULL_HANDLE};
        const VLogicalDevice  * _pLogicalDevice {nullptr};

        //// private functions

    public:
        //// public variables

        //// public functions
        VDescriptorPool() noexcept = default;

        VulkanResult setup ( const VLogicalDevice & ) noexcept;
        void cleanup() noexcept;

        [[nodiscard]] const VulkanDescriptorPool & data () const noexcept {
            return this->_handle;
        }

        [[nodiscard]] const VLogicalDevice * getLogicalDevicePtr () const noexcept {
            return this->_pLogicalDevice;
        }
    };

}


#endif //ENG1_VDESCRIPTORPOOL_H

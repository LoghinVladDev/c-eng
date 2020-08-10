//
// Created by Vlad on 10/08/2020.
//

#ifndef ENG1_VQUEUE_H
#define ENG1_VQUEUE_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/instance/device/VLogicalDevice.h>

namespace engine {

    class VQueue {
    private:
        //// private variables
        VulkanQueue         _queueHandler           {};
        VLogicalDevice *    _parentLogicalDevice    {nullptr};

        //// private functions

    public:
        //// public variables

        VQueue() noexcept = delete;
        explicit VQueue(const VLogicalDevice& logicalDevice, uint32 index) noexcept {
            vkGetDeviceQueue( logicalDevice.data(), logicalDevice.getQueueFamilyIndex(), index, & this->_queueHandler );
        }
        //// public functions

        //// TODO : destroy individual queues upon destruction
//        ~VQueue() noexcept {
//
//        }

    };

}


#endif //ENG1_VQUEUE_H

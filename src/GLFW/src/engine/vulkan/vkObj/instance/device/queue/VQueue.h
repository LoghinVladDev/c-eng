//
// Created by Vlad on 10/08/2020.
//

#ifndef ENG1_VQUEUE_H
#define ENG1_VQUEUE_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/instance/device/VLogicalDevice.h>

namespace engine {

    class VLogicalDevice;

    class VQueue {
    private:
        //// private variables
        VulkanQueue             _queueHandler           {};
        const VLogicalDevice *  _parentLogicalDevice    {nullptr};

        //// private functions

    public:
        //// public variables

        //// public functions

        VQueue() noexcept = delete;
        explicit VQueue(const engine::VLogicalDevice & logicalDevice, uint32 index) noexcept;

        [[nodiscard]] const VLogicalDevice & getLogicalDevice () const noexcept {
            return *this->_parentLogicalDevice;
        }

        [[nodiscard]] const VulkanQueue & getQueueHandler () const noexcept {
            return this->_queueHandler;
        }

    };

}


#endif //ENG1_VQUEUE_H

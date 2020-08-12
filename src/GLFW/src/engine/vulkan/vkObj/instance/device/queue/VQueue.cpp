//
// Created by Vlad on 10/08/2020.
//

#include "VQueue.h"

engine::VQueue::VQueue(const engine::VLogicalDevice & logicalDevice, uint32 index) noexcept
    : _parentLogicalDevice( & logicalDevice ){
    vkGetDeviceQueue( logicalDevice.data(), logicalDevice.getQueueFamily()->getQueueFamilyIndex(), index, & this->_queueHandler );
}

//
// Created by Vlad on 10/08/2020.
//

#include "VQueue.h"

engine::VQueue::VQueue(const engine::VQueueFamily& family, float priority) noexcept :
    _parentFamily( & family ),
    _priority( priority ) {
//    vkGetDeviceQueue( logicalDevice.data(), logicalDevice.getQueueFamily()->getQueueFamilyIndex(), index, & this->_queueHandler );
}

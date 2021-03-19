//
// Created by Vlad on 10/08/2020.
//

#include "VQueue.hpp"

engine::VQueue::VQueue(const engine::VQueueFamily& family, float priority) noexcept :
    _parentFamily( & family ),
    _priority( priority ){
}

auto engine::VQueue::setup ( const VLogicalDevice& logicalDevice, uint32 index ) noexcept -> void {
    this->_parentLogicalDevice = ( & logicalDevice );
    this->_queueIndex = index;
    vkGetDeviceQueue( logicalDevice.data(), this->_parentFamily->getQueueFamilyIndex(), index, & this->_queueHandler );
}

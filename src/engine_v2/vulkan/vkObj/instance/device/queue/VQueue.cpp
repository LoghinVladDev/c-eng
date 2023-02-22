//
// Created by Vlad on 10/08/2020.
//

#include "VQueue.hpp"

engine::VQueue::VQueue(engine::VQueueFamily const & family, float priority) noexcept :
    VRenderObject(),
    _parentFamily( & family ),
    _priority( priority ){
}

auto engine::VQueue::setup ( VLogicalDevice const & logicalDevice, uint32 index ) noexcept -> void {
    this->_parentLogicalDevice = ( & logicalDevice );
    this->_queueIndex = index;
    vkGetDeviceQueue( logicalDevice.data(), this->_parentFamily->getQueueFamilyIndex(), index, & this->_handle );
}

#include <sstream>

auto engine::VQueue::toString() const noexcept -> String {
    std::stringstream oss;

    oss << "VQueue " <<
        "{ handle = 0x" << std::hex << reinterpret_cast<AddressValueType>(this->_handle) <<
        ", pParentFamily = 0x" << reinterpret_cast<AddressValueType>(this->_parentFamily) <<
        ", pParentLogicalDevice = 0x" << reinterpret_cast<AddressValueType>(this->_parentLogicalDevice) <<
        ", priority = " << std::dec << this->_priority <<
        ", index = " << this->_queueIndex << " }";

    return oss.str();
}
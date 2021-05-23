//
// Created by Vlad on 21/08/2020.
//

#include "VSemaphore.hpp"

inline static auto populateSemaphoreCreateInfo (
    VulkanSemaphoreCreateInfo * createInfo
) noexcept -> void {
    if ( createInfo == nullptr )
        return;

    * createInfo = { };

    createInfo->sType =VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
}

auto engine::VSemaphore::setup(VLogicalDevice const & logicalDevice) noexcept -> VulkanResult {
    this->_pLogicalDevice = & logicalDevice;

    VulkanSemaphoreCreateInfo createInfo { };

    populateSemaphoreCreateInfo( & createInfo );

    return vkCreateSemaphore( this->_pLogicalDevice->data(), & createInfo, nullptr, & this->_handle );
}

auto engine::VSemaphore::clear() noexcept -> void {
    vkDestroySemaphore( this->_pLogicalDevice->data(), this->_handle, nullptr );
}

auto engine::VSemaphoreCollection::setup(VLogicalDevice const & device, uint32 semaphoreCount) noexcept -> VulkanResult {
    this->_semaphores.resize( semaphoreCount );
    this->_pLogicalDevice = & device;

    for ( auto & semaphore : this->_semaphores ) {
        VulkanResult result = semaphore.setup( device );
        if ( result != VulkanResult::VK_SUCCESS )
            return result;
    }

    return VulkanResult::VK_SUCCESS;
}

auto engine::VSemaphoreCollection::resize(VLogicalDevice const & device, uint32 semaphoreCount) noexcept -> VulkanResult {
    this->cleanup();
    return this->setup( device, semaphoreCount );
}

auto engine::VSemaphoreCollection::cleanup() noexcept -> void {
    for ( auto & semaphore : this->_semaphores )
        semaphore.clear();
}

#include <sstream>
auto engine::VSemaphoreCollection::toString() const noexcept -> String {
    std::stringstream oss;
    oss << "VSemaphoreCollection { pLogicalDevice = " << std::hex <<
            reinterpret_cast < AddressValueType > (this->_pLogicalDevice) <<
            ", semaphores = [ " << std::dec;

    for (auto const & item : this->_semaphores)
        oss << item.toString() << ", ";

    auto s = oss.str();
    return s.substr(s.size() - 2).append(" ]}");
}

auto engine::VSemaphore::toString () const noexcept -> String {
    std::stringstream oss;
    oss <<"VSemaphore { " << "handle = 0x" << std::hex <<
        reinterpret_cast < AddressValueType > ( this->_handle ) <<
        ", pLogicalDevice = 0x" <<
        reinterpret_cast < AddressValueType > ( this->_pLogicalDevice ) << " }";

    return oss.str();
}
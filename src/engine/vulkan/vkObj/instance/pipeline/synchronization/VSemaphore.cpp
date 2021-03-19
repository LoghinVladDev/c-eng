//
// Created by Vlad on 21/08/2020.
//

#include "VSemaphore.hpp"

inline static void populateSemaphoreCreateInfo (
    VulkanSemaphoreCreateInfo * createInfo
) noexcept {
    if ( createInfo == nullptr )
        return;

    * createInfo = { };

    createInfo->sType =VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
}

VulkanResult engine::VSemaphore::setup(const VLogicalDevice & logicalDevice) noexcept {
    this->_pLogicalDevice = & logicalDevice;

    VulkanSemaphoreCreateInfo createInfo { };

    populateSemaphoreCreateInfo( & createInfo );

    return vkCreateSemaphore( this->_pLogicalDevice->data(), & createInfo, nullptr, & this->_handle );
}

void engine::VSemaphore::cleanup() noexcept {
    vkDestroySemaphore( this->_pLogicalDevice->data(), this->_handle, nullptr );
}

VulkanResult engine::VSemaphoreCollection::setup(const VLogicalDevice & device, uint32 semaphoreCount) noexcept {
    this->_semaphores.resize( semaphoreCount );
    this->_pLogicalDevice = & device;

    for ( auto & semaphore : this->_semaphores ) {
        VulkanResult result = semaphore.setup( device );
        if ( result != VulkanResult::VK_SUCCESS )
            return result;
    }

    return VulkanResult::VK_SUCCESS;
}

VulkanResult engine::VSemaphoreCollection::resize(const VLogicalDevice & device, uint32 semaphoreCount) noexcept {
    this->cleanup();
    return this->setup( device, semaphoreCount );
}

void engine::VSemaphoreCollection::cleanup() noexcept {
    for ( auto & semaphore : this->_semaphores )
        semaphore.cleanup();
}
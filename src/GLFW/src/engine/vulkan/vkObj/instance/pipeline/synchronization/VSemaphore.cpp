//
// Created by Vlad on 21/08/2020.
//

#include "VSemaphore.h"

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
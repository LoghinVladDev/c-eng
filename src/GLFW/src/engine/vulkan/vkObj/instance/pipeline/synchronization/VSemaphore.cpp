//
// Created by vladl on 20/08/2020.
//

#include "VSemaphore.h"

inline static void populateSemaphoreCreateInfo (
    VulkanSemaphoreCreateInfo * createInfo
) noexcept {
    if ( createInfo == nullptr )
        return;

    * createInfo = { };
    createInfo->sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
}

VulkanResult engine::VSemaphore::setup(const engine::VLogicalDevice & device) noexcept {
    this->_pLogicalDevice = & device;

    VulkanSemaphoreCreateInfo createInfo { };

    populateSemaphoreCreateInfo( & createInfo );

    return vkCreateSemaphore( this->_pLogicalDevice->data(), & createInfo, nullptr, & this->_handle );
}

void engine::VSemaphore::cleanup() noexcept {
    vkDestroySemaphore( this->_pLogicalDevice->data(), this->_handle, nullptr );
}
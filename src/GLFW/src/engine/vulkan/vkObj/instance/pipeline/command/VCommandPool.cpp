//
// Created by Vlad on 19/08/2020.
//

#include "VCommandPool.h"

inline static void populateCommandPoolCreateInfo (
    VulkanCommandPoolCreateInfo * createInfo,
    uint32 queueFamilyIndex
) noexcept {
    if ( createInfo == nullptr )
        return;

    * createInfo = { };

    createInfo->sType               = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    createInfo->queueFamilyIndex    = queueFamilyIndex;
    createInfo->flags               = 0U;
}

VulkanResult engine::VCommandPool::setup(const VLogicalDevice & device) noexcept {
    this->_pLogicalDevice = & device;
    const engine::VQueueFamily * pQueueFamily = nullptr;

    for ( const auto * pDeviceQueueFamily : this->_pLogicalDevice->getQueueFamilies() ) {
        if ( pDeviceQueueFamily->isGraphicsCapable() ) {
            pQueueFamily = pDeviceQueueFamily;
            break;
        }
    }

    if ( pQueueFamily == nullptr )
        return VulkanResult::VK_ERROR_INITIALIZATION_FAILED;

    VulkanCommandPoolCreateInfo createInfo { };

    populateCommandPoolCreateInfo( & createInfo, static_cast < uint32 > ( pQueueFamily->getQueueFamilyIndex() ) );

    return vkCreateCommandPool ( this->_pLogicalDevice->data(), & createInfo, nullptr, & this->_handle );
}

void engine::VCommandPool::cleanup() noexcept {
    vkDestroyCommandPool ( this->_pLogicalDevice->data(), this->_handle, nullptr );
}
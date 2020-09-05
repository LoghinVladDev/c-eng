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

VulkanResult engine::VCommandPool::setup(const VLogicalDevice & device, const VQueueFamily * pQueueFamily) noexcept {
    this->_pLogicalDevice = & device;

    if ( pQueueFamily == nullptr ) {
        pQueueFamily = this->_pLogicalDevice->getFirstGraphicsQueuePtr()->getQueueFamily();

        if (pQueueFamily == nullptr)
            return VulkanResult::VK_ERROR_INITIALIZATION_FAILED;
    }

    this->_optimizedForTransfers = pQueueFamily->isTransferCapable();

    VulkanCommandPoolCreateInfo createInfo { };

    populateCommandPoolCreateInfo( & createInfo, static_cast < uint32 > ( pQueueFamily->getQueueFamilyIndex() ) );

    return vkCreateCommandPool ( this->_pLogicalDevice->data(), & createInfo, nullptr, & this->_handle );
}

void engine::VCommandPool::cleanup() noexcept {
    vkDestroyCommandPool ( this->_pLogicalDevice->data(), this->_handle, nullptr );
}

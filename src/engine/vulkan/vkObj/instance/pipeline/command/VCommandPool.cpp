//
// Created by Vlad on 19/08/2020.
//

#include "VCommandPool.hpp"

/**
 * @brief internal function used to populate Command Pool Create Info Structure
 *
 * @param createInfo : VulkanCommandPoolCreateInfo ptr = structure to populate
 * @param queueFamilyIndex : uint32 = Index of the Queue Family to use for Command Buffers inside Pool
 *
 * @exceptsafe
 */
inline static auto populateCommandPoolCreateInfo (
    VulkanCommandPoolCreateInfo * createInfo,
    uint32 queueFamilyIndex
) noexcept -> void {
    if ( createInfo == nullptr )
        return;

    * createInfo = {
        .sType              = VulkanStructureType::VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
        .pNext              = nullptr,
        .flags              = 0U,
        .queueFamilyIndex   = queueFamilyIndex,
    };
}

auto engine::VCommandPool::setup(
        VLogicalDevice  const & device,
        VQueueFamily    const * pQueueFamily
) noexcept -> VulkanResult {
    this->_pLogicalDevice = & device; /// save device

    if ( pQueueFamily == nullptr ) { /// if no queue family given, acquire graphics queue family from logical device
        pQueueFamily = this->_pLogicalDevice->getFirstGraphicsQueuePtr()->getQueueFamily();

        if (pQueueFamily == nullptr) /// if no queue family could be acquired, error
            return VulkanResult::VK_ERROR_INITIALIZATION_FAILED;
    }

    this->_optimizedForTransfers = pQueueFamily->isTransferCapable(); /// if queue family transfer capable, pool is optimised for transfers

    VulkanCommandPoolCreateInfo createInfo { };

    populateCommandPoolCreateInfo( & createInfo, static_cast < uint32 > ( pQueueFamily->getQueueFamilyIndex() ) );

    /// create command pool
    return vkCreateCommandPool ( this->_pLogicalDevice->data(), & createInfo, nullptr, & this->_handle );
}

auto engine::VCommandPool::cleanup() noexcept -> void {
    /// cleanup command pool
    vkDestroyCommandPool ( this->_pLogicalDevice->data(), this->_handle, nullptr );
}

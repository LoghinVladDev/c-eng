//
// Created by Vlad on 21/08/2020.
//

#include "VFence.h"

static inline void populateFenceCreateInfo (
    VulkanFenceCreateInfo * createInfo,
    VulkanFenceCreateFlags flags = engine::VFence::NO_FLAGS
) noexcept {
    if ( createInfo == nullptr )
        return;

    * createInfo = VulkanFenceCreateInfo {
        .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
        .pNext = nullptr,
        .flags = flags
    };
}

VulkanResult engine::VFence::setup(const engine::VLogicalDevice & device, VulkanFenceCreateFlags flags) noexcept {
    this->_pLogicalDevice = & device;

    VulkanFenceCreateInfo createInfo { };
    populateFenceCreateInfo( & createInfo, flags );

    return vkCreateFence( this->_pLogicalDevice->data(), & createInfo, nullptr, & this->_handle );
}

void engine::VFence::cleanup() noexcept {
    vkDestroyFence( this->_pLogicalDevice->data(), this->_handle, nullptr );
}

VulkanResult engine::VFenceCollection::setup(const VLogicalDevice & device, uint32 fenceCount, VulkanFenceCreateFlags flags) noexcept {
    this->_fences.resize( fenceCount );
    this->_pLogicalDevice = & device;

    for ( auto & fence : this->_fences ) {
        VulkanResult result = fence.setup( device, flags );
        if ( result != VulkanResult::VK_SUCCESS )
            return result;
    }

    return VulkanResult::VK_SUCCESS;
}

void engine::VFenceCollection::cleanup() noexcept {
    for ( auto & fence : this->_fences )
        fence.cleanup();
}

VulkanResult engine::VFenceCollection::resize(const VLogicalDevice & device, uint32 fenceCount, VulkanFenceCreateFlags flags) noexcept {
    this->cleanup();
    return this->setup( device, fenceCount, flags );
}

VulkanResult engine::VFenceCollection::resize(uint32 fenceCount) {
    this->_fences.resize( fenceCount );
    return VulkanResult::VK_SUCCESS;
}

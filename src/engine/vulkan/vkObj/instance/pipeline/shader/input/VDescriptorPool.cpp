//
// Created by Vlad on 07/09/2020.
//

#include "VDescriptorPool.h"

inline static void populateDescriptorPoolCreateInfo (
    VulkanDescriptorPoolCreateInfo  * pCreateInfo,
    VulkanDescriptorPoolSize        * pDescriptorPoolSizes,
    uint32                            descriptorPoolSizeCount,
    uint32                            maxSetCount
) noexcept {
    if ( pCreateInfo == nullptr )
        return;

    * pCreateInfo = VulkanDescriptorPoolCreateInfo {
        .sType          = VulkanStructureType::VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
        .pNext          = nullptr,
        .flags          = VULKAN_NULL_FLAGS,
        .maxSets        = maxSetCount,
        .poolSizeCount  = descriptorPoolSizeCount,
        .pPoolSizes     = pDescriptorPoolSizes,
    };
}

VulkanResult engine::VDescriptorPool::setup(const VLogicalDevice & device, const VulkanDescriptorType * pDescriptorTypes, uint32 descriptorTypeCount, uint32 objectCount) noexcept {
    this->_pLogicalDevice = & device;
    auto swapChainImageCount = static_cast < uint32 > ( this->_pLogicalDevice->getSwapChain()->getImages().size() );
    VulkanDescriptorPoolCreateInfo createInfo {};

    std::vector < VulkanDescriptorPoolSize > poolSizes (descriptorTypeCount);

    for ( uint32 descriptorTypeIndex = 0U; descriptorTypeIndex < descriptorTypeCount; descriptorTypeIndex++ ) {
        poolSizes[ descriptorTypeIndex ] = VulkanDescriptorPoolSize {
            .type               = pDescriptorTypes[ descriptorTypeIndex ],
            .descriptorCount    = swapChainImageCount
        };
    }

    populateDescriptorPoolCreateInfo(
        & createInfo,
        poolSizes.data(),
        static_cast < uint32 > ( poolSizes.size() ),
        swapChainImageCount * objectCount
    );

    return vkCreateDescriptorPool( this->_pLogicalDevice->data(), & createInfo, nullptr, & this->_handle );
}

void engine::VDescriptorPool::cleanup() noexcept {
    vkDestroyDescriptorPool( this->_pLogicalDevice->data(), this->_handle, nullptr );
}
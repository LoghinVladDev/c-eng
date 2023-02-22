//
// Created by Vlad on 07/09/2020.
//

#include "VDescriptorPool.hpp"

/**
 * @brief Internal Function used to populate Descriptor Pool Create Info Structure
 *
 * @param pCreateInfo : VulkanDescriptorPoolCreateInfo ptr = Address to Structure to populate
 * @param pDescriptorPoolSizes : VulkanDescriptorPoolSize cptr = Address to one / an array of Descriptor Pool Sizes, representing the size of individual Descriptors used by one Shader Computation in a Layout / Object
 * @param descriptorPoolSizeCount : uint32 = Number of Sizes in the array above
 * @param maxSetCount : uint32 = Max Size to be allocated. Usually no. of objects * number of frame buffers in swapchain
 *
 * @exceptsafe
 */
inline static auto populateDescriptorPoolCreateInfo (
    VulkanDescriptorPoolCreateInfo        * pCreateInfo,
    VulkanDescriptorPoolSize        const * pDescriptorPoolSizes,
    uint32                                  descriptorPoolSizeCount,
    uint32                                  maxSetCount
) noexcept -> void {
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

#include <VSwapChain.hpp>
auto engine::VDescriptorPool::setup(
        VLogicalDevice          const & device,
        VulkanDescriptorType    const * pDescriptorTypes,
        uint32                          descriptorTypeCount,
        uint32                          objectCount
) noexcept -> VulkanResult {
    this->_pLogicalDevice = & device;
    auto swapChainImageCount = static_cast < uint32 > ( this->_pLogicalDevice->getSwapChain()->getImages().size() );
    VulkanDescriptorPoolCreateInfo createInfo {};

    std::vector < VulkanDescriptorPoolSize > poolSizes (descriptorTypeCount);

    for ( uint32 descriptorTypeIndex = 0U; descriptorTypeIndex < descriptorTypeCount; descriptorTypeIndex++ ) {
        poolSizes[ descriptorTypeIndex ] = VulkanDescriptorPoolSize { /// populate pool sizes = type * number to be allocated per object
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

    /// create pool
    return vkCreateDescriptorPool( this->_pLogicalDevice->data(), & createInfo, nullptr, & this->_handle );
}

auto engine::VDescriptorPool::clear() noexcept -> void {
    vkDestroyDescriptorPool( this->_pLogicalDevice->data(), this->_handle, nullptr );
}

#include <sstream>

auto engine::VDescriptorPool::toString() const noexcept -> String {
    std::stringstream oss;

    oss << "VDescriptorPool " <<
        "{ handle = 0x" << std::hex << reinterpret_cast<AddressValueType>(this->_handle) <<
        ", pLogicalDevice = 0x" << reinterpret_cast<AddressValueType>(this->_pLogicalDevice) << " }";

    return oss.str();
}
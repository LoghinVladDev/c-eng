//
// Created by Vlad on 21/08/2020.
//

#include "VFence.hpp"

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

void engine::VFence::clear() noexcept {
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

void engine::VFenceCollection::clear() noexcept {
    for ( auto & fence : this->_fences )
        fence.clear();
}

VulkanResult engine::VFenceCollection::resize(const VLogicalDevice & device, uint32 fenceCount, VulkanFenceCreateFlags flags) noexcept {
    this->clear();
    return this->setup( device, fenceCount, flags );
}

VulkanResult engine::VFenceCollection::resize(uint32 fenceCount) {
    this->_fences.resize( fenceCount );
    return VulkanResult::VK_SUCCESS;
}

#include <sstream>
auto engine::VFence::toString() const noexcept -> String {
    std::stringstream oss;

    oss << "VFence { handle = 0x" <<
        std::hex << reinterpret_cast < AddressValueType > (this->_handle) <<
        ", pLogicalDevice = 0x" << reinterpret_cast < AddressValueType > (this->_pLogicalDevice) << " }";

    return oss.str();
}

auto engine::VFenceCollection::toString() const noexcept -> String {
    std::stringstream oss;

    oss << "VFenceCollection { pLogicalDevice = 0x" << std::hex <<
        this->_pLogicalDevice << ", fences = [ ";

    for (auto const & item : this->_fences)
        oss << item.toString() << ", ";

    auto s = oss.str();
    return s.substr(s.size() - 2).append(" ]}");
}
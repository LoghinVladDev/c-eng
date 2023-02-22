//
// Created by loghin on 9/20/20.
//

#include "VTextureSampler.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

inline static auto populateSamplerCreateInfo (
        VulkanSamplerCreateInfo   * pCreateInfo,
        bool                        enableAnisotropy,
        float                       maxAnisotropy
) noexcept -> void {

    if ( pCreateInfo == nullptr ) {
        return;
    }

    * pCreateInfo = VulkanSamplerCreateInfo {
        .sType                      = VulkanStructureType :: VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
        .pNext                      = nullptr,
        .flags                      = VULKAN_NULL_FLAGS,
        .magFilter                  = VulkanFilter :: VK_FILTER_LINEAR,
        .minFilter                  = VulkanFilter :: VK_FILTER_LINEAR,
        .mipmapMode                 = VulkanSamplerMipmapMode :: VK_SAMPLER_MIPMAP_MODE_LINEAR,
        .addressModeU               = VulkanSamplerAddressMode :: VK_SAMPLER_ADDRESS_MODE_REPEAT,
        .addressModeV               = VulkanSamplerAddressMode :: VK_SAMPLER_ADDRESS_MODE_REPEAT,
        .addressModeW               = VulkanSamplerAddressMode :: VK_SAMPLER_ADDRESS_MODE_REPEAT,
        .mipLodBias                 = 0.0F,
        .anisotropyEnable           = static_cast < VulkanBool32 > ( enableAnisotropy ),
        .maxAnisotropy              = maxAnisotropy,
        .compareEnable              = VULKAN_FALSE,
        .compareOp                  = VulkanCompareOp :: VK_COMPARE_OP_ALWAYS,
        .minLod                     = 0.0F,
        .maxLod                     = 0.0F,
        .borderColor                = VulkanBorderColor :: VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK,
        .unnormalizedCoordinates    = VULKAN_FALSE
    };
}

auto VTextureSampler :: setup (
        VLogicalDevice  const & device,
        bool                    anisotropyEnable,
        float                   anisotropyValue
) noexcept -> VulkanResult {

    this->_pLogicalDevice = & device;

    VulkanSamplerCreateInfo createInfo {};
    populateSamplerCreateInfo(
        & createInfo,
        this->_pLogicalDevice->getBasePhysicalDevice()->anisotropySamplerSupported() && anisotropyEnable,
        anisotropyValue
    );

    return vkCreateSampler ( this->_pLogicalDevice->data(), & createInfo, nullptr, & this->_handle );
}

auto VTextureSampler :: clear() noexcept -> void {
    vkDestroySampler( this->_pLogicalDevice->data(), this->_handle, nullptr );
}


#include <sstream>
auto VTextureSampler :: toString() const noexcept -> String {
    std::stringstream oss;

    oss <<"VTextureSampler { " <<
           "handle = 0x" << std::hex << reinterpret_cast < AddressValueType > (this->_handle) <<
           ", pLogicalDevice = 0x" << reinterpret_cast < AddressValueType const > (this->_pLogicalDevice) << " }";

    return oss.str();
}
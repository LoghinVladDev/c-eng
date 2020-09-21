//
// Created by loghin on 9/20/20.
//

#include "VTextureSampler.h"

inline static void populateSamplerCreateInfo (
        VulkanSamplerCreateInfo * pCreateInfo,
        bool enableAnisotropy,
        float maxAnisotropy
) noexcept {
    if ( pCreateInfo == nullptr )
        return;

    * pCreateInfo = VulkanSamplerCreateInfo {
        .sType                      = VulkanStructureType::VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
        .pNext                      = nullptr,
        .flags                      = (VulkanFlags) 0U,
        .magFilter                  = VulkanFilter::VK_FILTER_LINEAR,
        .minFilter                  = VulkanFilter::VK_FILTER_LINEAR,
        .mipmapMode                 = VulkanSamplerMipmapMode::VK_SAMPLER_MIPMAP_MODE_LINEAR,
        .addressModeU               = VulkanSamplerAddressMode::VK_SAMPLER_ADDRESS_MODE_REPEAT,
        .addressModeV               = VulkanSamplerAddressMode::VK_SAMPLER_ADDRESS_MODE_REPEAT,
        .addressModeW               = VulkanSamplerAddressMode::VK_SAMPLER_ADDRESS_MODE_REPEAT,
        .mipLodBias                 = 0.0f,
        .anisotropyEnable           = (VkBool32) enableAnisotropy,
        .maxAnisotropy              = maxAnisotropy,
        .compareEnable              = VK_FALSE,
        .compareOp                  = VulkanCompareOp::VK_COMPARE_OP_ALWAYS,
        .minLod                     = 0.0f,
        .maxLod                     = 0.0f,
        .borderColor                = VulkanBorderColor::VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK,
        .unnormalizedCoordinates    = VK_FALSE
    };
}

VulkanResult engine::VTextureSampler::setup(const VLogicalDevice & device, bool anisotropyEnable, float anisotropyValue) noexcept {
    this->_pLogicalDevice = & device;

    VulkanSamplerCreateInfo createInfo {};
    populateSamplerCreateInfo(
        & createInfo,
        this->_pLogicalDevice->getBasePhysicalDevice()->anisotropySamplerSupported() && anisotropyEnable,
        anisotropyValue
    );

    return vkCreateSampler ( this->_pLogicalDevice->data(), & createInfo, nullptr, & this->_handle );
}

void engine::VTextureSampler::cleanup() noexcept {
    vkDestroySampler( this->_pLogicalDevice->data(), this->_handle, nullptr );
}
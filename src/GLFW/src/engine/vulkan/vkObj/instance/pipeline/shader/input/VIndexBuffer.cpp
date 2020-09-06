//
// Created by vladl on 9/5/2020.
//

#include "VIndexBuffer.h"

VulkanResult engine::VIndexBuffer::setup(
    const VLogicalDevice    & device,
    std::size_t               size,
    VulkanSharingMode         sharingMode,
    const uint32            * pQueueFamilyIndices,
    uint32                    queueFamilyIndexCount
) noexcept {
    return VBuffer::setup(
        device,
        size,
        VBuffer::INDEX_BUFFER_GPU_LOCAL,
        sharingMode,
        pQueueFamilyIndices,
        queueFamilyIndexCount
    );
}

VulkanResult engine::VIndexBuffer::allocateMemory() noexcept {
    return VBuffer::allocateMemory( VBuffer::MEMORY_GPU_LOCAL );
}

void engine::VIndexBuffer::cleanup() noexcept {
    return VBuffer::cleanup();
}

void engine::VIndexBuffer::free() noexcept {
    return VBuffer::free();
}
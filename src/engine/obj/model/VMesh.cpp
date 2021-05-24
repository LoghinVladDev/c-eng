//
// Created by vladl on 10/5/2020.
//

#include "VMesh.hpp"
#include <vkUtils/VStdUtilsDefs.h>

const engine::VMesh engine::VMesh::EMPTY = VMesh(UINT64_MAX);

auto engine::VMesh::setup(
        engine::VCommandPool            const & transferCommandPool,
        engine::VQueueFamilyCollection  const & queueFamilyCollection,
        std::vector<engine::VVertex>    const & vertices,
        std::vector<uint16>             const & indices
) noexcept -> VulkanResult {
    this->_pCommandPool = & transferCommandPool;
    this->_pQueueFamilyCollection = & queueFamilyCollection;

    auto queueFamilyIndices = this->_pQueueFamilyCollection->getQueueFamilyIndices();

    ENG_RETURN_IF_NOT_SUCCESS(
        this->_vertexBuffer.setup(
            * this->_pCommandPool->getLogicalDevicePtr(),
            vertices,
            this->_pCommandPool,
            queueFamilyIndices.data(),
            static_cast < uint32 > ( queueFamilyIndices.size() )
        )
    )

    ENG_RETURN_IF_NOT_SUCCESS(this->_vertexBuffer.allocateMemory())
    ENG_RETURN_IF_NOT_SUCCESS(
        this->_indexBuffer.setup(
            * this->_pCommandPool->getLogicalDevicePtr(),
            indices,
            this->_pCommandPool,
            queueFamilyIndices.data(),
            static_cast<uint32>(queueFamilyIndices.size())
        )
    )

    ENG_RETURN_IF_NOT_SUCCESS(this->_indexBuffer.allocateMemory())

    return VulkanResult::VK_SUCCESS;
}

auto engine::VMesh::free() noexcept -> void {
    this->_vertexBuffer.free();
    this->_indexBuffer.free();
}

auto engine::VMesh::clear() noexcept -> void {
    this->_vertexBuffer.clear();
    this->_indexBuffer.clear();
}

//
// Created by vladl on 10/5/2020.
//

#include "VMesh.h"
#include <vkUtils/VStdUtilsDefs.h>

VulkanResult engine::VMesh::setup(
        const engine::VCommandPool              & transferCommandPool,
        const engine::VQueueFamilyCollection    & queueFamilyCollection,
        const std::vector<engine::VVertex>      & vertices,
        const std::vector<uint16>               & indices
) noexcept {
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

void engine::VMesh::free() {
    this->_vertexBuffer.free();
    this->_indexBuffer.free();
}

void engine::VMesh::cleanup() {
    this->_vertexBuffer.cleanup();
    this->_indexBuffer.cleanup();
}

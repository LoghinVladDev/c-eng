//
// Created by vladl on 8/30/2020.
//

#ifndef ENG1_VVERTEXBUFFER_H
#define ENG1_VVERTEXBUFFER_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/instance/device/VLogicalDevice.h>
#include <vkObj/instance/pipeline/shader/input/VVertex.h>

namespace engine {


    class VVertexBuffer {
    private:
        //// private variables
        VulkanBuffer                            _handle         {VK_NULL_HANDLE};
        VkDeviceMemory                          _memoryHandle   {VK_NULL_HANDLE};
        VulkanDeviceSize                        _memorySize     {0ULL};
        uint32                                  _vertexCount    {0U};
        const VLogicalDevice                  * _pLogicalDevice {nullptr};
        const std::vector < engine::VVertex > * _pVertices      {nullptr};

        //// private functions

    public:
        //// public variables
        constexpr static VulkanMemoryPropertyFlagBits MEMORY_HOST_COHERENT = VulkanMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
        constexpr static VulkanMemoryPropertyFlagBits MEMORY_CPU_WRITEABLE = VulkanMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;

        constexpr static VulkanMemoryPropertyFlags MEMORY_CPU_BUFFER_FLAGS =
            VVertexBuffer::MEMORY_HOST_COHERENT |
            VVertexBuffer::MEMORY_CPU_WRITEABLE;

        //// public functions
        VVertexBuffer () noexcept = default;

        [[nodiscard]] const VulkanBuffer & data () const noexcept {
            return this->_handle;
        }

        VulkanResult setup (
            const VLogicalDevice &,
            const std::vector < VVertex > &,
            VulkanBufferUsageFlags = VulkanBufferUsageFlagBits::VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
            VulkanSharingMode = VulkanSharingMode::VK_SHARING_MODE_EXCLUSIVE
        ) noexcept;

        VulkanResult allocateMemory (
            VulkanMemoryPropertyFlags = VVertexBuffer::MEMORY_CPU_BUFFER_FLAGS
        ) noexcept;

        [[nodiscard]] uint32 getVertexCount () const noexcept {
            return this->_vertexCount;
        }

        void free () noexcept;
        void cleanup () noexcept;
    };


}


#endif //ENG1_VVERTEXBUFFER_H

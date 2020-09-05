//
// Created by vladl on 8/30/2020.
//

#ifndef ENG1_VVERTEXBUFFER_H
#define ENG1_VVERTEXBUFFER_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/instance/device/VLogicalDevice.h>
#include <vkObj/instance/pipeline/shader/input/VVertex.h>
#include <vkObj/instance/pipeline/shader/input/VBuffer.h>

namespace engine {


    class VVertexBuffer : public VBuffer {
    private:
        //// private variables
//        uint32                                          _vertexCount    {0U};
        const std::vector < engine::VVertex > *         _pVertices      {nullptr};

        std::vector < engine::VVertex::SVertexPack >    _packedVertices;

        //// private functions

    public:
        //// public variables
        //// public functions
        VVertexBuffer () noexcept = default;

        VulkanResult setup (
            const VLogicalDevice &,
            std::size_t,
            VulkanSharingMode = VulkanSharingMode::VK_SHARING_MODE_EXCLUSIVE,
            uint32 = 0U,
            const uint32 * = nullptr
        ) noexcept;

        VulkanResult setup (
            const VLogicalDevice &,
            const std::vector < VVertex > &,
            VulkanSharingMode = VulkanSharingMode::VK_SHARING_MODE_EXCLUSIVE,
            uint32 = 0U,
            const uint32 * = nullptr
        ) noexcept;

        VulkanResult allocateMemory () noexcept;

        VulkanResult allocateMemory (
            VulkanMemoryPropertyFlags
        ) noexcept override;

//        [[nodiscard]] uint32 getVertexCount () const noexcept {
//            return this->_vertexCount;
//        }

        void free () noexcept override;
        void cleanup () noexcept override;
    };


}


#endif //ENG1_VVERTEXBUFFER_H

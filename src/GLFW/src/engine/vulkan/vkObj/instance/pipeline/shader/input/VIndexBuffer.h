//
// Created by vladl on 9/5/2020.
//

#ifndef ENG1_VINDEXBUFFER_H
#define ENG1_VINDEXBUFFER_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/instance/device/VLogicalDevice.h>
#include <vkObj/instance/pipeline/shader/input/VVertex.h>
#include <vkObj/instance/pipeline/shader/input/VBuffer.h>

namespace engine {

    class VIndexBuffer : public VBuffer {
    private:
        //// private variables
        VulkanIndexType _indexType {VIndexBuffer::TYPE_16_BIT};

        //// private functions

    public:
        //// public variables
        constexpr static VulkanIndexType TYPE_16_BIT = VulkanIndexType::VK_INDEX_TYPE_UINT16;
        constexpr static VulkanIndexType TYPE_32_BIT = VulkanIndexType::VK_INDEX_TYPE_UINT32;

        //// public functions
        VIndexBuffer () noexcept = default;

        VulkanResult setup (
            const VLogicalDevice &,
            std::size_t,
            VulkanSharingMode = VulkanSharingMode::VK_SHARING_MODE_EXCLUSIVE,
            const uint32 * = nullptr,
            uint32 = 0U,
            VulkanIndexType = VIndexBuffer::TYPE_16_BIT
        ) noexcept;

        [[nodiscard]] VulkanIndexType getIndexType () const noexcept {
            return this->_indexType;
        }

        VulkanResult allocateMemory () noexcept;

        void free () noexcept override;
        void cleanup () noexcept override;
    };

}


#endif //ENG1_VINDEXBUFFER_H

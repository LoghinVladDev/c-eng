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

        //// private functions

    public:
        //// public variables

        //// public functions
        VIndexBuffer () noexcept = default;

        VulkanResult setup (
                const VLogicalDevice &,
                std::size_t,
                VulkanSharingMode = VulkanSharingMode::VK_SHARING_MODE_EXCLUSIVE,
                const uint32 * = nullptr,
                uint32 = 0U
        ) noexcept;

        VulkanResult allocateMemory () noexcept;

        void free () noexcept override;
        void cleanup () noexcept override;
    };

}


#endif //ENG1_VINDEXBUFFER_H

//
// Created by Vlad on 19/08/2020.
//

#ifndef ENG1_VCOMMANDBUFFER_H
#define ENG1_VCOMMANDBUFFER_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include "VCommandPool.h"
#include <vkObj/instance/pipeline/VFrameBuffer.h>
#include <src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/VPipeline.h>
#include <src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/synchronization/VSemaphore.h>
#include <src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/synchronization/VFence.h>
#include <vkObj/instance/pipeline/shader/input/VVertex.h>
#include <vkObj/instance/pipeline/shader/input/VVertexBuffer.h>
#include <vkObj/instance/pipeline/shader/input/VIndexBuffer.h>

namespace engine {

    class VCommandBuffer {
    private:
        friend class VCommandBufferCollection;
        //// private variables
        VulkanCommandBuffer     _handle         {nullptr};
        const VFrameBuffer    * _pFrameBuffer   {nullptr};

        //// private functions

    public:
        //// public variables
        constexpr static VulkanCommandBufferLevel PRIMARY_LEVEL     = VulkanCommandBufferLevel::VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        constexpr static VulkanCommandBufferLevel SECONDARY_LEVEL   = VulkanCommandBufferLevel::VK_COMMAND_BUFFER_LEVEL_SECONDARY;

        //// public functions
        VCommandBuffer() noexcept = delete;
        explicit VCommandBuffer ( const VulkanCommandBuffer & handle, const VFrameBuffer * pFrameBuffer = nullptr ) noexcept :
            _handle ( handle ),
            _pFrameBuffer ( pFrameBuffer ){

        }

        VulkanResult submit (
            const VulkanPipelineStageFlags *,
            const VSemaphore *,
            uint32,
            const VSemaphore *,
            uint32,
            const VFence * = nullptr
        ) const noexcept;

        VulkanResult submit (
            const VQueue *
        ) const noexcept ;

        VulkanResult startRecord (
            const VPipeline&,
            const VBuffer * = nullptr,
            const VulkanDeviceSize * = nullptr,
            uint32 = 0U,
            const VIndexBuffer * = nullptr,
            const VulkanDescriptorSet * = nullptr,
            uint32 = 0U
        ) noexcept;

        VulkanResult startRecord (
            const VBuffer &,
            const VBuffer &,
            uint32
        ) const noexcept;

        [[nodiscard]] const VulkanCommandBuffer & data () const noexcept {
            return this->_handle;
        }
    };

    class VCommandBufferCollection {
    private:
        //// private variables
        std::vector < VCommandBuffer > _commandBuffers;
        const VCommandPool           * _pCommandPool    {nullptr};

        //// private functions

    public:
        //// public variables

        //// public functions
        VCommandBufferCollection() noexcept = default;

        VulkanResult allocate ( const engine::VCommandPool &, const engine::VFrameBufferCollection & ) noexcept;
        VulkanResult allocate ( const engine::VCommandPool &, uint32 ) noexcept;
        VulkanResult startRecord (
            const VPipeline&,
            const VBuffer * = nullptr,
            const VulkanDeviceSize * = nullptr,
            uint32 = 0U,
            const VIndexBuffer * = nullptr,
            const VulkanDescriptorSet * = nullptr,
            uint32 = 0U
        ) noexcept;

        VulkanResult startRecord (
            const VBuffer &,
            const VBuffer &,
            uint32
        ) const noexcept;

        VulkanResult submit (
            const VQueue *
        ) const noexcept ;

        [[nodiscard]] const std::vector < VCommandBuffer > & getCommandBuffers () const noexcept {
            return this->_commandBuffers;
        }

        void free () noexcept;
    };

}


#endif //ENG1_VCOMMANDBUFFER_H

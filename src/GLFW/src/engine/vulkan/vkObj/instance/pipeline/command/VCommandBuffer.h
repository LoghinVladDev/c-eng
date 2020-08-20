//
// Created by Vlad on 19/08/2020.
//

#ifndef ENG1_VCOMMANDBUFFER_H
#define ENG1_VCOMMANDBUFFER_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include "VCommandPool.h"
#include <vkObj/instance/pipeline/VFrameBuffer.h>
#include <vkObj/instance/pipeline/VPipeline.h>
#include <vkObj/instance/pipeline/synchronization/VSemaphore.h>

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
        explicit VCommandBuffer ( const VulkanCommandBuffer & handle, const VFrameBuffer * pFrameBuffer ) noexcept :
            _handle ( handle ),
            _pFrameBuffer ( pFrameBuffer ){

        }

        VulkanResult submit ( const VulkanPipelineStageFlags *, const engine::VSemaphore *, uint32, const engine::VSemaphore *, uint32 ) noexcept;

        VulkanResult submit ( const std::vector < VulkanPipelineStageFlags > & waitStages,  const std::vector < VSemaphore > & currentSemaphores, const std::vector < VSemaphore > & semaphoresToSignal ) noexcept {
            return this->submit (
                    waitStages.data(),
                    currentSemaphores.data(),
                    static_cast < uint32 > ( currentSemaphores.size() ),
                    semaphoresToSignal.data(),
                    static_cast < uint32 > ( semaphoresToSignal.size() )
            );
        }

        VulkanResult startRecord ( const VPipeline& ) noexcept;
    };

    class VCommandBufferCollection {
    private:
        //// private variables
        std::vector < VCommandBuffer > _commandBuffers;

        //// private functions

    public:
        //// public variables

        //// public functions
        VCommandBufferCollection() noexcept = default;

        VulkanResult allocate ( const engine::VCommandPool &, const engine::VFrameBufferCollection & );
        VulkanResult startRecord ( const VPipeline& ) noexcept;
        VulkanResult submit ( const VulkanPipelineStageFlags * pStageFlagMasks, const engine::VSemaphore * pWaitSemaphores, uint32 waitSemaphoreCount, const engine::VSemaphore * pSignalSemaphores, uint32 signalSemaphoreCount, uint32 imageIndex) noexcept {
            return this->_commandBuffers[imageIndex].submit( pStageFlagMasks, pWaitSemaphores, waitSemaphoreCount, pSignalSemaphores, signalSemaphoreCount );
        }

        VulkanResult submit ( const std::vector < VulkanPipelineStageFlags > & waitStages,  const std::vector < VSemaphore > & currentSemaphores, const std::vector < VSemaphore > & semaphoresToSignal, uint32 imageIndex ) noexcept {
            return this->submit (
                waitStages.data(),
                currentSemaphores.data(),
                static_cast < uint32 > ( currentSemaphores.size() ),
                semaphoresToSignal.data(),
                static_cast < uint32 > ( semaphoresToSignal.size() ),
                imageIndex
            );
        }

        [[nodiscard]] const std::vector < VCommandBuffer > & getCommandBuffers () const noexcept {
            return this->_commandBuffers;
        }
    };

}


#endif //ENG1_VCOMMANDBUFFER_H

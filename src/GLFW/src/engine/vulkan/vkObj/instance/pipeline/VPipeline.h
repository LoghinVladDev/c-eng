//
// Created by Vlad on 19/08/2020.
//

#ifndef ENG1_VPIPELINE_H
#define ENG1_VPIPELINE_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>

#include <vector>
#include <src/GLFW/src/engine/vulkan/vkObj/instance/device/VLogicalDevice.h>
#include "VRenderPass.h"

namespace engine {

    //// TODO : DEFINITELY IMPLEMENT BUILDER!!
    class VPipeline {
    private:
        //// private variables
        VulkanPipelineLayout    _layoutHandle   {nullptr};
        VulkanGraphicsPipeline  _handle         {nullptr};

        const VLogicalDevice  * _pLogicalDevice {nullptr};

        VRenderPass             _renderPass;

        //// private functions

        void createRenderPass() noexcept (false);
    public:
        //// public variables

        //// public functions
        VPipeline() noexcept = default;

        [[nodiscard]] const VulkanGraphicsPipeline & data () const noexcept {
            return this->_handle;
        }

        [[nodiscard]] const VRenderPass * getRenderPassPtr () const noexcept {
            return & this->_renderPass;
        }

        VulkanResult setup ( const VulkanPipelineShaderStageCreateInfo*, uint32, const engine::VLogicalDevice& ) noexcept (false);
        VulkanResult setup ( const std::vector < VulkanPipelineShaderStageCreateInfo > & shaderStages, const engine::VLogicalDevice& device ) noexcept (false) {
            return this->setup ( shaderStages.data(), static_cast < uint32 > ( shaderStages.size() ), device );
        }

        void cleanup () noexcept;
    };

}


#endif //ENG1_VPIPELINE_H
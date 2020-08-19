//
// Created by Vlad on 19/08/2020.
//

#ifndef ENG1_VPIPELINE_H
#define ENG1_VPIPELINE_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>

#include <vector>
#include <src/GLFW/src/engine/vulkan/vkObj/instance/device/VLogicalDevice.h>


namespace engine {

    //// TODO : DEFINITELY IMPLEMENT BUILDER!!
    class VPipeline {
    private:
        //// private variables
        VulkanPipelineLayout    _layoutHandle   {nullptr};
        const VLogicalDevice  * _pLogicalDevice {nullptr};

        //// private functions

    public:
        //// public variables

        //// public functions
        VPipeline() noexcept = default;

        VulkanResult setup ( const std::vector < VulkanPipelineShaderStageCreateInfo > &, const engine::VLogicalDevice& ) noexcept (false);

        void cleanup () noexcept;
    };

}


#endif //ENG1_VPIPELINE_H

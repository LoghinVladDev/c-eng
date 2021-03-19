//
// Created by Vlad on 19/08/2020.
//

#ifndef ENG1_VPIPELINE_HPP
#define ENG1_VPIPELINE_HPP

#include <engineVulkanPreproc.hpp>
#include <vulkanExplicitTypes.h>

#include <vector>
#include <VLogicalDevice.hpp>
#include "VRenderPass.hpp"

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

        [[nodiscard]] const VulkanPipelineLayout & layout() const noexcept {
            return this->_layoutHandle;
        }

        [[nodiscard]] const VRenderPass * getRenderPassPtr () const noexcept {
            return & this->_renderPass;
        }

        VulkanResult setup (
            const engine::VLogicalDevice&,
            const VulkanPipelineShaderStageCreateInfo *,
            uint32,
            const VulkanVertexInputBindingDescription *     = nullptr,
            uint32                                          = 0U,
            const VulkanVertexInputAttributeDescription *   = nullptr,
            uint32                                          = 0U,
            const VulkanDescriptorSetLayout *               = nullptr,
            uint32                                          = 0U
        ) noexcept (false);
        VulkanResult setup (
            const engine::VLogicalDevice& device,
            const std::vector < VulkanPipelineShaderStageCreateInfo > & shaderStages,
            const std::vector < VulkanVertexInputBindingDescription > & bindingDescriptions,
            const std::vector < VulkanVertexInputAttributeDescription > & attributeDescriptions
        ) noexcept (false) {
            return this->setup (
                device,
                shaderStages.data(),
                static_cast < uint32 > ( shaderStages.size() ),
                bindingDescriptions.data(),
                static_cast < uint32 > ( bindingDescriptions.size() ),
                attributeDescriptions.data(),
                static_cast < uint32 > ( attributeDescriptions.size() )
            );
        }

        void cleanup () noexcept;
    };

}


#endif //ENG1_VPIPELINE_HPP

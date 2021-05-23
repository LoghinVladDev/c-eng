//
// Created by Vlad on 19/08/2020.
//

#ifndef ENG1_VPIPELINE_HPP
#define ENG1_VPIPELINE_HPP

#include <VRenderObject.hpp>

#include <vector>
#include <VLogicalDevice.hpp>
#include <VRenderPass.hpp>

namespace engine {

    //// TODO : DEFINITELY IMPLEMENT BUILDER!!
    //// maybe later
    class VPipeline : public VRenderObject {
    private:
        //// private variables
        VulkanPipelineLayout    _layoutHandle   {nullptr};
        VulkanGraphicsPipeline  _handle         {nullptr};

        VLogicalDevice  const * _pLogicalDevice {nullptr};

        VRenderPass             _renderPass;

        //// private functions

        auto createRenderPass() noexcept (false) -> void;
    public:
        //// public variables

        //// public functions
        VPipeline() noexcept = default;
        ~VPipeline() noexcept override = default;

        [[nodiscard]] constexpr auto data () const noexcept -> VulkanGraphicsPipeline const & {
            return this->_handle;
        }

        [[nodiscard]] constexpr auto layout() const noexcept -> VulkanPipelineLayout const & {
            return this->_layoutHandle;
        }

        [[nodiscard]] constexpr auto getRenderPassPtr () const noexcept -> VRenderPass const * {
            return & this->_renderPass;
        }

        auto setup (
            engine::VLogicalDevice                  const &,
            VulkanPipelineShaderStageCreateInfo     const *,
            uint32,
            VulkanVertexInputBindingDescription     const * = nullptr,
            uint32                                          = 0U,
            VulkanVertexInputAttributeDescription   const * = nullptr,
            uint32                                          = 0U,
            VulkanDescriptorSetLayout               const * = nullptr,
            uint32                                          = 0U
        ) noexcept (false) -> VulkanResult;

        inline auto setup (
            engine::VLogicalDevice                                  const & device,
            std::vector < VulkanPipelineShaderStageCreateInfo >     const & shaderStages,
            std::vector < VulkanVertexInputBindingDescription >     const & bindingDescriptions,
            std::vector < VulkanVertexInputAttributeDescription >   const & attributeDescriptions
        ) noexcept (false) -> VulkanResult {
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

        auto clear () noexcept -> void override;

        [[nodiscard]] auto toString () const noexcept -> String override;

        [[nodiscard]] auto operator == (Object const & o) const noexcept -> bool override {
            if ( this == & o ) return true;
            auto p = dynamic_cast < decltype(this) > (& o);
            if ( p == nullptr ) return false;

            return this->_handle == p->_handle;
        }

        [[nodiscard]] auto copy () const noexcept -> VPipeline * override {
            return new VPipeline(* this);
        }

        [[nodiscard]] auto hash () const noexcept -> Index override {
            return dataTypes::hash(reinterpret_cast<AddressValueType>(this->_handle));
        }
    };

}


#endif //ENG1_VPIPELINE_HPP

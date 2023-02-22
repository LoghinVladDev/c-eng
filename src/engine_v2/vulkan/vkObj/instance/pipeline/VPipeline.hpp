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

        auto createRenderPass () noexcept (false) -> void;
    public:
        //// public variables

        //// public functions
        VPipeline() noexcept = default;
        ~VPipeline() noexcept override = default;

        __CDS_NoDiscard constexpr auto data () const noexcept -> VulkanGraphicsPipeline const & {
            return this->_handle;
        }

        __CDS_NoDiscard constexpr auto layout() const noexcept -> VulkanPipelineLayout const & {
            return this->_layoutHandle;
        }

        __CDS_NoDiscard constexpr auto getRenderPassPtr () const noexcept -> VRenderPass const * {
            return & this->_renderPass;
        }

        auto setup (
            VLogicalDevice                          const &,
            VulkanPipelineShaderStageCreateInfo     const *,
            cds :: uint32,
            VulkanVertexInputBindingDescription     const * = nullptr,
            cds :: uint32                                   = 0U,
            VulkanVertexInputAttributeDescription   const * = nullptr,
            cds :: uint32                                   = 0U,
            VulkanDescriptorSetLayout               const * = nullptr,
            cds :: uint32                                   = 0U
        ) noexcept (false) -> VulkanResult;

        inline auto setup (
            VLogicalDevice                                          const & device,
            std :: vector < VulkanPipelineShaderStageCreateInfo >   const & shaderStages,
            std :: vector < VulkanVertexInputBindingDescription >   const & bindingDescriptions,
            std :: vector < VulkanVertexInputAttributeDescription > const & attributeDescriptions
        ) noexcept (false) -> VulkanResult {
            return this->setup (
                device,
                shaderStages.data(),
                static_cast < cds :: uint32 > ( shaderStages.size() ),
                bindingDescriptions.data(),
                static_cast < cds :: uint32 > ( bindingDescriptions.size() ),
                attributeDescriptions.data(),
                static_cast < cds :: uint32 > ( attributeDescriptions.size() )
            );
        }

        auto clear () noexcept -> void override;

        __CDS_NoDiscard auto toString () const noexcept -> cds :: String override;

        __CDS_NoDiscard auto operator == (VPipeline const & o) const noexcept -> bool {
            if ( this == & o ) {
                return true;
            }

            return this->_handle == o._handle;
        }

        __CDS_NoDiscard auto equals (Object const & o) const noexcept -> bool override {
            if ( this == & o ) {
                return true;
            }

            auto p = dynamic_cast < decltype(this) > (& o);
            if ( p == nullptr ) {
                return false;
            }

            return this->operator==(*p);
        }

        __CDS_NoDiscard auto copy () const noexcept -> VPipeline * override {
            return new VPipeline(* this);
        }

        __CDS_NoDiscard auto hash () const noexcept -> cds :: Index override {
            return cds :: hash ( reinterpret_cast < cds :: AddressValueType const > (this->_handle) );
        }
    };

}


#endif //ENG1_VPIPELINE_HPP

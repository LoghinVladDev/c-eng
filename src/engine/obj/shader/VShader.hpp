//
// Created by vladl on 10/9/2020.
//

#ifndef ENG1_VSHADER_H
#define ENG1_VSHADER_H

#include <VRenderObject.hpp>
#include <VLogicalDevice.hpp>
#include <VPipeline.hpp>
#include <VShaderModule.hpp>
#include <VShaderCompiler.hpp>

namespace engine {

    /**
     * todo : make this a VComponent
     */
    class VShader : public VRenderObject {
    private:
        //// private variables
        VLogicalDevice                              const * _pLogicalDevice         {nullptr};
        VPipeline                                           _pipeline;

        VShaderModule                                       _vertexShader;
        VShaderModule                                       _fragmentShader;

        std::vector < VulkanPipelineShaderStageCreateInfo > _shaderStages;
        VulkanDescriptorSetLayout                           _descriptorSetLayout    {VK_NULL_HANDLE};

        std::vector < VulkanDescriptorSetLayoutBinding >    _descriptorSetLayoutBindings;

        //// private functions

    public:
        //// public variables

        //// public functions
        VShader() noexcept = default;
        ~VShader() noexcept override = default;

        [[nodiscard]] constexpr auto getPipeline () const noexcept -> VPipeline const & {
            return this->_pipeline;
        }

        [[nodiscard]] constexpr auto getPipeline () noexcept -> VPipeline & {
            return this->_pipeline;
        }

        [[nodiscard]] constexpr auto getVertexShaderModule () const noexcept -> VShaderModule const & {
            return this->_vertexShader;
        }

        [[nodiscard]] constexpr auto getVertexShaderModule () noexcept -> VShaderModule & {
            return this->_vertexShader;
        }

        [[nodiscard]] constexpr auto getFragmentShaderModule () const noexcept -> VShaderModule const & {
            return this->_fragmentShader;
        }

        [[nodiscard]] constexpr auto getFragmentShaderModule () noexcept -> VShaderModule & {
            return this->_fragmentShader;
        }

        [[nodiscard]] constexpr auto getRenderPassPtr () const noexcept -> VRenderPass const * {
            return this->_pipeline.getRenderPassPtr();
        }

        [[nodiscard]] constexpr auto getDescriptorSetLayout () const noexcept -> VulkanDescriptorSetLayout const & {
            return this->_descriptorSetLayout;
        }

        [[nodiscard]] constexpr auto getDescriptorSetLayout () noexcept -> VulkanDescriptorSetLayout & {
            return this->_descriptorSetLayout;
        }

        [[nodiscard]] constexpr auto getDescriptorSetLayoutBindings () const noexcept -> std::vector < VulkanDescriptorSetLayoutBinding > const & {
            return this->_descriptorSetLayoutBindings;
        }

        [[nodiscard]] constexpr auto getDescriptorSetLayoutBindings () noexcept -> std::vector < VulkanDescriptorSetLayoutBinding > & {
            return this->_descriptorSetLayoutBindings;
        }

        [[nodiscard]] auto getDescriptorTypeLayout () const noexcept -> std::vector < VulkanDescriptorType > {
            std::vector < VulkanDescriptorType > descriptorTypes;

            for ( const auto & binding : this->_descriptorSetLayoutBindings ) {
                descriptorTypes.push_back( binding.descriptorType );
            }

            return descriptorTypes;
        }

        auto setup (
            VLogicalDevice  const &,
            VShaderCompiler const &,
            std::string     const &
        ) noexcept -> VulkanResult;

        auto recreateShader () noexcept -> VulkanResult ;

        auto clear() noexcept -> void override;

        [[nodiscard]] auto toString () const noexcept -> String override;
        [[nodiscard]] auto copy () const noexcept -> VShader * override {
            return new VShader(*this);
        }

        [[nodiscard]] auto hash () const noexcept -> Index override {
            return this->_pipeline.hash() + this->_vertexShader.hash() + this->_fragmentShader.hash();
        }

        [[nodiscard]] auto operator == (Object const & o) const noexcept -> bool override {
            if ( this == & o ) return true;
            auto p = dynamic_cast < decltype ( this ) > ( & o );
            if ( p == nullptr ) return false;

            return this->_vertexShader == p->_vertexShader && this->_fragmentShader == p->_fragmentShader;
        }
    };

}


#endif //ENG1_VSHADER_H

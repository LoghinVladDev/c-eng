//
// Created by vladl on 10/10/2020.
//

#ifndef ENG1_VMESHRENDERER_H
#define ENG1_VMESHRENDERER_H

#include <engineVulkanPreproc.hpp>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <VLogicalDevice.hpp>
#include <VDescriptorSet.hpp>
#include <src/engine/obj/shader/VShader.hpp>
#include <VCommandPool.hpp>

#include <ecm/VComponent.hpp>

namespace engine {

    class VMeshRenderer : public VComponent {
    private:
        //// private variables
        VLogicalDevice                                          const * _pLogicalDevice       {nullptr};
        VTextureSampler                                         const * _pTextureSampler      {nullptr};
        VShader                                                 const * _pShader              {nullptr};
        VDescriptorPool                                         const * _pDescriptorPool      {nullptr};
        VCommandPool                                            const * _pCommandPool         {nullptr};

        VTexture                                                        _texture;

        VDescriptorSetCollection < engine::SUniformBufferObject >       _descriptorSets;     // NOLINT(bugprone-reserved-identifier)
        std::vector < VUniformBuffer < engine::SUniformBufferObject > > _MVPDescriptorBuffers;  // NOLINT(bugprone-reserved-identifier)

        //// private functions

        explicit VMeshRenderer ( uint64 ignoredIDConstructor ) noexcept : VComponent( VComponent::DISTINCT | VComponent::HAS_DEPENDENCY, ignoredIDConstructor ) { }

#if __cpp_constexpr >= 201907
        [[nodiscard]] constexpr auto typeFlag () const noexcept -> TypeFlag override { return VComponent::TypeFlag::V_MESH_RENDERER; }
#else
        [[nodiscard]] inline auto typeFlag () const noexcept -> TypeFlag override { return VComponent::TypeFlag::V_MESH_RENDERER; }
#endif
    public:
        //// public variables
        const static VMeshRenderer EMPTY;

        //// public functions
//        VMeshRenderer () noexcept = default;

        [[nodiscard]] auto className() const noexcept -> ClassName override {
            return "VMeshRenderer";
        }

        explicit VMeshRenderer (VEntity * pParent = nullptr) noexcept :
            VComponent(VComponent::Tag::DISTINCT | VComponent::Tag::HAS_DEPENDENCY, pParent) {

        }

        ~VMeshRenderer() noexcept override = default;

        [[nodiscard]] auto toString () const noexcept -> String override {
            return String().append("VMeshRenderer {\n")
                .append("\tlogicalDevice address = ").append(reinterpret_cast<uint64>(this->_pLogicalDevice)).append("\n")
                .append("\ttextureSampler address = ").append(reinterpret_cast<uint64>(this->_pTextureSampler)).append("\n")
                .append("\tshader address = ").append(reinterpret_cast<uint64>(this->_pShader)).append("\n")
                .append("\tdescriptorPool address = ").append(reinterpret_cast<uint64>(this->_pDescriptorPool)).append("\n")
                .append("\tcommandPool address = ").append(reinterpret_cast<uint64>(this->_pCommandPool)).append("\n")
                .append("\ttexture = ").append(this->_texture.toString()).append("\n")
                .append("\tdescriptorSets = ").append(this->_descriptorSets.toString()).append("\n")
                .append("\tmodelViewProjectionDescriptorBuffers").append("<?stl_object?>").append("\n")
                .append("}");
        }

        [[nodiscard]] constexpr auto getLogicalDevicePtr () const noexcept -> VLogicalDevice const * {
            return this->_pLogicalDevice;
        }

        [[nodiscard]] constexpr auto getTextureSamplerPtr () const noexcept -> VTextureSampler const * {
            return this->_pTextureSampler;
        }

        [[nodiscard]] constexpr auto getTexture () const noexcept -> VTexture const & {
            return this->_texture;
        }

        [[nodiscard]] constexpr auto getTexture () noexcept -> VTexture & {
            return this->_texture;
        }

        [[nodiscard]] constexpr auto getDescriptorSets () const noexcept -> VDescriptorSetCollection < engine::SUniformBufferObject > const & {
            return this->_descriptorSets;
        }

        [[nodiscard]] constexpr auto getDescriptorSets () noexcept -> VDescriptorSetCollection < engine::SUniformBufferObject > & {
            return this->_descriptorSets;
        }

        [[nodiscard]] constexpr auto getMVPDescriptorBuffers () const noexcept -> std::vector < VUniformBuffer < engine::SUniformBufferObject >> const & {
            return this->_MVPDescriptorBuffers;
        }

        [[nodiscard]] constexpr auto getMVPDescriptorBuffers () noexcept -> std::vector < VUniformBuffer < engine::SUniformBufferObject >> & {
            return this->_MVPDescriptorBuffers;
        }

        auto clear() noexcept -> void;
        auto clearUniformBuffers () noexcept -> void;

        auto recreateUniformBuffers () noexcept -> VulkanResult;
        auto recreateDescriptorSets () noexcept -> VulkanResult;
        auto recreate() noexcept -> VulkanResult;

        auto setup (
                VCommandPool            const &,
                VDescriptorPool         const &,
                VShader                 const &,
                std::string             const &,
                VTextureSampler         const &,
                VQueueFamilyCollection  const &
        ) noexcept -> VulkanResult;

        [[nodiscard]] auto copy () const noexcept -> VMeshRenderer * override {
            return new VMeshRenderer(* this);
        }

        [[nodiscard]] auto hash () const noexcept -> Index override {
            return this->_descriptorSets.hash() + this->_texture.hash();
        }

        [[nodiscard]] auto operator == (VMeshRenderer const & o) const noexcept -> bool {
            if ( this == & o ) return true;

            return this->_texture == o._texture && this->_descriptorSets == o._descriptorSets;
        }

        [[nodiscard]] auto equals (Object const & o) const noexcept -> bool override {
            if ( this == & o ) return true;
            auto p = dynamic_cast < decltype (this) > ( & o );
            if ( p == nullptr ) return false;

            return this->operator==(* p);
        }
    };

}


#endif //ENG1_VMESHRENDERER_H

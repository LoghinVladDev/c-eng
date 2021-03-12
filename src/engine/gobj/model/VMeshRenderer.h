//
// Created by vladl on 10/10/2020.
//

#ifndef ENG1_VMESHRENDERER_H
#define ENG1_VMESHRENDERER_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <VLogicalDevice.h>
#include <VDescriptorSet.h>
#include <src/engine/gobj/shader/VShader.h>
#include <VCommandPool.h>

#include <ecm/VComponent.h>

namespace engine {

    class VMeshRenderer : public VComponent {
    private:
        //// private variables
        const VLogicalDevice                                          * _pLogicalDevice       {nullptr};
        const VTextureSampler                                         * _pTextureSampler      {nullptr};
        const VShader                                                 * _pShader              {nullptr};
        const VDescriptorPool                                         * _pDescriptorPool      {nullptr};
        const VCommandPool                                            * _pCommandPool         {nullptr};

        VTexture                                                        _texture;

        VDescriptorSetCollection < engine::SUniformBufferObject >       _descriptorSets;     // NOLINT(bugprone-reserved-identifier)
        std::vector < VUniformBuffer < engine::SUniformBufferObject > > _MVPDescriptorBuffers;  // NOLINT(bugprone-reserved-identifier)

        //// private functions

        explicit VMeshRenderer ( uint64 ignoredIDConstructor ) noexcept : VComponent( VComponent::DISTINCT | VComponent::HAS_DEPENDENCY, ignoredIDConstructor ) { }
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
                .append("\ttexture = ").append("<?>").append("\n")
                .append("\tdescriptorSets = ").append("<?>").append("\n")
                .append("\tmodelViewProjectionDescriptorBuffers").append("<?>").append("\n")
                .append("}");
        }

        [[nodiscard]] const VLogicalDevice * getLogicalDevicePtr () const noexcept {
            return this->_pLogicalDevice;
        }

        [[nodiscard]] const VTextureSampler * getTextureSamplerPtr () const noexcept {
            return this->_pTextureSampler;
        }

        [[nodiscard]] const VTexture & getTexture () const noexcept {
            return this->_texture;
        }

        [[nodiscard]] VTexture & getTexture () noexcept {
            return this->_texture;
        }

        [[nodiscard]] const VDescriptorSetCollection < engine::SUniformBufferObject > & getDescriptorSets () const noexcept {
            return this->_descriptorSets;
        }

        [[nodiscard]] VDescriptorSetCollection < engine::SUniformBufferObject > & getDescriptorSets () noexcept {
            return this->_descriptorSets;
        }

        [[nodiscard]] const std::vector < VUniformBuffer < engine::SUniformBufferObject >> & getMVPDescriptorBuffers () const noexcept {
            return this->_MVPDescriptorBuffers;
        }

        [[nodiscard]] std::vector < VUniformBuffer < engine::SUniformBufferObject >> & getMVPDescriptorBuffers () noexcept {
            return this->_MVPDescriptorBuffers;
        }

        void cleanup() noexcept;

        void cleanupUniformBuffers () noexcept;
        VulkanResult recreateUniformBuffers () noexcept;
        VulkanResult recreateDescriptorSets () noexcept;
        VulkanResult recreate() noexcept;

        VulkanResult setup (
                const VCommandPool &,
                const VDescriptorPool &,
                const VShader &,
                const std::string &,
                const VTextureSampler &,
                const VQueueFamilyCollection &
        ) noexcept;
    };

}


#endif //ENG1_VMESHRENDERER_H

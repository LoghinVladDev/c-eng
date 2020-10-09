//
// Created by vladl on 10/9/2020.
//

#ifndef ENG1_VSHADER_H
#define ENG1_VSHADER_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/instance/device/VLogicalDevice.h>
#include <vkObj/instance/pipeline/VPipeline.h>
#include <vkObj/instance/pipeline/shader/VShaderModule.h>
#include <vkObj/instance/pipeline/shader/VShaderCompiler.h>

namespace engine {

    class VShader {
    private:
        //// private variables
        const VLogicalDevice  * _pLogicalDevice {nullptr};
        VPipeline               _pipeline;

        VShaderModule           _vertexShader;
        VShaderModule           _fragmentShader;

        //// private functions

    public:
        //// public variables

        //// public functions
        VShader() noexcept = default;

        [[nodiscard]] const VPipeline & getPipeline () const noexcept {
            return this->_pipeline;
        }

        [[nodiscard]] VPipeline & getPipeline () noexcept {
            return this->_pipeline;
        }

        [[nodiscard]] const VShaderModule & getVertexShaderModule () const noexcept {
            return this->_vertexShader;
        }

        [[nodiscard]] VShaderModule & getVertexShaderModule () noexcept {
            return this->_vertexShader;
        }

        [[nodiscard]] const VShaderModule & getFragmentShaderModule () const noexcept {
            return this->_fragmentShader;
        }

        [[nodiscard]] VShaderModule & getFragmentShaderModule () noexcept {
            return this->_fragmentShader;
        }

        VulkanResult setup (
            const VLogicalDevice &,
            const VShaderCompiler &,
            const std::string &
        ) noexcept;

        void cleanup() noexcept;

    };

}


#endif //ENG1_VSHADER_H

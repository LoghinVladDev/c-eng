//
// Created by Vlad on 19/08/2020.
//

#ifndef ENG1_VRENDERPASS_HPP
#define ENG1_VRENDERPASS_HPP


#include <engineVulkanPreproc.hpp>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/instance/device/VLogicalDevice.hpp>

namespace engine {

    class EngineVRenderPassDeviceInvalidSwapChain : public std::exception {
    public:
        [[nodiscard]] const char * what() const noexcept override {
            return "Passed VLogicalDevice has invalid / non-existent swap chain";
        }
    };

    class VRenderPass {
    private:
        //// private variables
        const VLogicalDevice    *   _pLogicalDevice {nullptr};
        VulkanRenderPass            _handle         {nullptr};

        //// private functions

    public:
        //// public variables

        //// public functions
        VRenderPass () noexcept = default;

        [[nodiscard]] const VulkanRenderPass & data () const noexcept {
            return this->_handle;
        }

        [[nodiscard]] const VLogicalDevice * getLogicalDevicePtr () const noexcept {
            return this->_pLogicalDevice;
        }

        VulkanResult setup (
            const engine::VLogicalDevice & ,
            const VulkanSubpassDependency * = nullptr,
            uint32 = 0U
        ) noexcept (false) ;

        void cleanup () noexcept;
    };

}


#endif //ENG1_VRENDERPASS_HPP

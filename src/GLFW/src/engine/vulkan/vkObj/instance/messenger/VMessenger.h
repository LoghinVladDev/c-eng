//
// Created by vladl on 06/08/2020.
//

#ifndef ENG1_VMESSENGER_H
#define ENG1_VMESSENGER_H


#include <src/GLFW/src/engine/vulkan/vkObj/instance/VInstance.h>
#include <exception>

namespace engine {

    class VInstance;

    class EngineVMessengerProvideVInstance : public std::exception {
    public:
        [[nodiscard]] const char * what() const noexcept override {
            return "A VInstance must be provided to the messenger, either on construct or by passing in setInstance";
        };
    };

    class VMessenger {
    private:
        //// private variables
        VulkanDebugMessenger    _debugMessenger {nullptr};
        engine::VInstance      * _vulkanInstance {nullptr};

        //// private functions

    public:
        //// public variables
        VMessenger() noexcept = default;

        explicit VMessenger( engine::VInstance * instance ) noexcept {
            this->_vulkanInstance = instance;
        }

        VMessenger& setInstance( engine::VInstance * instance ) noexcept {
            this->_vulkanInstance = instance;
            return * this;
        }

        VulkanResult setup ( engine::VInstance * = nullptr ) noexcept (false);

        [[nodiscard]] const VulkanDebugMessenger& data() const noexcept {
            return this->_debugMessenger;
        }

        constexpr static VulkanFlags DEFAULT_DEBUG_MESSAGE_SEVERITY =
                (VulkanFlags) VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                (VulkanFlags) VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                (VulkanFlags) VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

        constexpr static VulkanFlags DEFAULT_DEBUG_MESSAGE_TYPE =
                (VulkanFlags) VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                (VulkanFlags) VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                (VulkanFlags) VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        //// public functions

        void clean() noexcept;
    };

}


#endif //ENG1_VMESSENGER_H

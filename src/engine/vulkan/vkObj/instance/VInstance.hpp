//
// Created by vladl on 06/08/2020.
//

#ifndef ENG1_VINSTANCE_HPP
#define ENG1_VINSTANCE_HPP
#include <vulkan/engineVulkanPreproc.hpp>
#include <vulkan/vkDefs/types/vulkanExplicitTypes.h>
#include <vulkan/vkObj/instance/validationLayer/VValidationLayer.hpp>

#include <utility>
namespace engine {

    class VInstance {
    private:
        //// private variables
        VulkanInstance _instance {nullptr};
        std::string    _name;

        //// private functions

    public:
        //// public variables
        [[maybe_unused]] static const char* DEFAULT_VULKAN_INSTANCE_TITLE;

        //// public functions
        VInstance() noexcept = default;
        explicit VInstance(std::string appTitle) noexcept : _name(std::move(appTitle)) { }

        VInstance& setTitle(std::string appTitle) noexcept {
            this->_name = std::move(appTitle);
            return *this;
        }

        VulkanResult setup() noexcept;
        VulkanResult setup( const VValidationLayerCollection &) noexcept;

        void clean() noexcept;

        [[nodiscard]] const VulkanInstance & data() const noexcept {
            return this->_instance;
        }

    };

}


#endif //ENG1_VINSTANCE_HPP

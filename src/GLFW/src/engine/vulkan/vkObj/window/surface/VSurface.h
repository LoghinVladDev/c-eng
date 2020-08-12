//
// Created by Vlad on 12/08/2020.
//

#ifndef ENG1_VSURFACE_H
#define ENG1_VSURFACE_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/instance/VInstance.h>

namespace engine {

    class VSurface {
    private:
        //// private variables
        VulkanSurfaceKhronos    _surface {};
        const VInstance *       _instance {nullptr};

        //// private functions

    public:
        //// public functions

        //// public variables
        VSurface( ) noexcept = default;
        explicit VSurface( GLFWwindow* window, const VInstance & instance) noexcept {
            this->setup(window, instance);
        }

        VulkanResult setup ( GLFWwindow*, const VInstance& ) noexcept;

        void clean () noexcept;
    };

}


#endif //ENG1_VSURFACE_H

//
// Created by vladl on 06/08/2020.
//

#ifndef ENG1_VEXTENSION_H
#define ENG1_VEXTENSION_H
#include <engineVulkanPreproc.h>
#include <vkDefs/vkDefinitions.h>
#include <vkDefs/types/vulkanExplicitTypes.h>

#include <vector>

namespace engine {

    class VExtension {
    private:
        //// private variables
        static bool                                        _extensionsQueried;
        static std::vector < VulkanExtensionProperties >   _extensions;

        //// private functions

    public:
        //// public variables

        //// public functions
        static void queryExtensions() noexcept;
        static void printExtensions(std::ostream&) noexcept;
        static const std::vector < VulkanExtensionProperties > & getAvailableExtensions() noexcept;
        static std::vector < GLFWExtensionLiteral > getGLFWRequiredExtensions(bool = false) noexcept;
    };

}


#endif //ENG1_VEXTENSION_H

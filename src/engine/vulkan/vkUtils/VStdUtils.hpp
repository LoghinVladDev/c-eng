//
// Created by vladl on 07/08/2020.
//

#ifndef ENG1_VSTDUTILS_HPP
#define ENG1_VSTDUTILS_HPP
#include <VObject.hpp>
#include <string>
#include <vector>

namespace engine {

    class VStandardUtils {
    private:
        //// private variables

        //// private functions

    public:
        //// public variables

        //// public functions
        VStandardUtils() = delete;

        static std::string to_string ( VulkanResult ) noexcept;
        static std::string to_string ( VulkanPhysicalDeviceType ) noexcept;

        constexpr static const char * boolAlpha (bool value ) noexcept {
            return value ? "true" : "false";
        }

        static std::vector < GLFWExtensionLiteral > getGLFWRequiredExtensions (bool = false) noexcept;
    };

}


#endif //ENG1_VSTDUTILS_HPP

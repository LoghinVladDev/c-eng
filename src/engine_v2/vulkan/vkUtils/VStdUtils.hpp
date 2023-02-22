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

        __CDS_NoDiscard static auto toString ( VulkanResult ) noexcept -> cds :: String;
        __CDS_NoDiscard static auto toString ( VulkanPhysicalDeviceType ) noexcept -> cds :: String;

        __CDS_NoDiscard constexpr static auto boolAlpha ( bool value ) noexcept -> cds :: StringLiteral {
            return value ? "true" : "false";
        }

        __CDS_NoDiscard static auto getGLFWRequiredExtensions ( bool = false ) noexcept -> std :: vector < GLFWExtensionLiteral >;
    };

}


#endif //ENG1_VSTDUTILS_HPP

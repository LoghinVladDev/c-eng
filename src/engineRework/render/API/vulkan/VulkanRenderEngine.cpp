//
// Created by loghin on 28.12.2021.
//

#include "VulkanRenderEngine.hpp"
#include <VulkanAPIExceptions.hpp>
#include <Logger.hpp>

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)


#define C_ENG_MAP_START     CLASS ( VulkanRenderEngine, ENGINE_PARENT ( RenderEngine ) )
#include <ObjectMapping.hpp>

auto vulkan :: Self :: init () noexcept (false) -> Self & {
    auto suitableVersion = this->acquireSuitableAPIVersion();

    (void) __C_ENG_TYPE ( Logger ) :: instance().info (
            String :: f (
                    "Vulkan API Version %s initializing...",
                    versionReadableFormat ( suitableVersion ).cStr()
            )
    );

    this->_instance = __C_ENG_TYPE ( Instance ) :: Builder ()
            .setVersion ( suitableVersion )
            .build ();

    (void) this->_instance.init();

    return * this;
}

auto vulkan :: Self :: acquireSuitableAPIVersion() const noexcept (false) -> __C_ENG_TYPE ( Version ) {
    __C_ENG_TYPE ( Version ) chosenVersion = nullVersion;

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

    auto greatestVersion = __C_ENG_TYPE ( Instance ) :: supportedVulkanVersion();

#elif __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

    auto greatestVersion = __C_ENG_TYPE ( Version ) {
        .variant    = static_cast < cds :: uint8 > ( 0 ),
        .major      = static_cast < cds :: uint8 > ( 1 ),
        .minor      = static_cast < cds :: uint8 > ( 0 ),
        .patch      = static_cast < cds :: uint8 > ( 0 )
    }

#else

    auto greatestVersion = nullVersion;

#endif

    if (
            compare ( this->desiredVersion(), nullVersion ) == CompareResultEquals ||
            compare ( this->desiredVersion(), greatestVersion ) == CompareResultGreater
    ) {
        chosenVersion = greatestVersion;
    } else {
        chosenVersion = this->desiredVersion();
    }

    if ( compare ( chosenVersion, nullVersion ) == CompareResultEquals ) {
        throw __C_ENG_TYPE ( VulkanAPIException ) ( "No suitable vulkan version found" );
    }

    return chosenVersion;
}
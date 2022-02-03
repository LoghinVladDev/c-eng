//
// Created by loghin on 28.12.2021.
//

#include "VulkanRenderEngine.hpp"
#include <Logger.hpp>
#include <PhysicalDevice.hpp>
#include <Device.hpp>
#include <VulkanAPI.hpp>

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

    if ( this->renderInstanceSurfaceCallbacks().attachCallback == nullptr ) {
        (void) __C_ENG_TYPE ( Logger ) :: instance().error ( "No Instance Surface Attach Callback Present. Cannot bind window surface to render API" );
    } else {
        __C_ENG_TYPE ( RenderInstanceSurfaceAttachData ) callbackData {
                .renderAPIType  = RenderAPITypeVulkan,
                .pAPIData       = this->instance().handle(),
                .pSurfaceHandle = & this->_surfaceHandle,
                .pUserData      = this->renderInstanceSurfaceCallbacks().pUserData
        };

        if ( ! this->renderInstanceSurfaceCallbacks().attachCallback ( & callbackData ) ) {
            (void) __C_ENG_TYPE ( Logger ) :: instance().warning ( "Instance Surface Attach Callback returned error value." );
        }
    }

    __C_ENG_TYPE ( PhysicalDevice ) const * pPhysicalDeviceToUse = nullptr;
    uint32 maxPhysicalDeviceScore = 0U;

    /// insert logic to use last physical device used later

    for ( auto & physicalDevice : __C_ENG_TYPE ( PhysicalDevice ) :: physicalDevices ( & this->_instance ) ) {
        auto currentDeviceScore = physicalDevice.renderScore();
        if ( currentDeviceScore > maxPhysicalDeviceScore ) {
            pPhysicalDeviceToUse = & physicalDevice;
            maxPhysicalDeviceScore = currentDeviceScore;
        }
    }

    Type ( Device ) :: Builder deviceBuilder;

    this->_device = deviceBuilder
        .fromDevice ( pPhysicalDeviceToUse )
        .toSurface ( this->_surfaceHandle )
        .build();

    return * this;
}

auto vulkan :: Self :: clear () noexcept (false) -> Self & {

    (void) this->_device.clear();

    if ( this->_surfaceHandle != nullptr ) {

        if ( this->renderInstanceSurfaceCallbacks().detachCallback == nullptr ) {
            (void) __C_ENG_TYPE ( Logger ) :: instance().warning ( "No Instance Surface Detach Callback Present. Cannot bind window surface to render API" );
        } else {
            __C_ENG_TYPE ( RenderInstanceSurfaceDetachData ) callbackData {
                    .renderAPIType  = RenderAPITypeVulkan,
                    .pAPIData       = this->instance().handle(),
                    .pSurfaceHandle = this->_surfaceHandle,
                    .pUserData      = this->renderInstanceSurfaceCallbacks().pUserData
            };

            if ( ! this->renderInstanceSurfaceCallbacks().detachCallback ( & callbackData ) ) {
                (void) __C_ENG_TYPE ( Logger ) :: instance().warning ( "Instance Surface Detach Callback returned error value." );
            } else {
                this->_surfaceHandle = nullptr;
            }
        }
    }

    (void) this->_instance.clear();

    return * this;
}

vulkan :: Self :: Destructor() noexcept {
    (void) this -> Self :: clear();
}

auto vulkan :: Self :: acquireSuitableAPIVersion() const noexcept (false) -> __C_ENG_TYPE ( Version ) {
    __C_ENG_TYPE ( Version ) chosenVersion = versionConstants :: nullVersion;

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
            compare ( this->desiredVersion(), versionConstants :: nullVersion ) == CompareResultEquals ||
            compare ( this->desiredVersion(), greatestVersion ) == CompareResultGreater
    ) {
        chosenVersion = greatestVersion;
    } else {
        chosenVersion = this->desiredVersion();
    }

    if ( compare ( chosenVersion, versionConstants :: nullVersion ) == CompareResultEquals ) {
        throw __C_ENG_TYPE ( VulkanAPIException ) ( "No suitable vulkan version found" );
    }

    return chosenVersion;
}
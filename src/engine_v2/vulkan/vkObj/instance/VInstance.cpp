//
// Created by vladl on 06/08/2020.
//

#include "VInstance.hpp"
#include <vkDefs/VInstanceDefinitions.h>
#include <vkUtils/VStdUtils.hpp>

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

__CDS_MaybeUnused StringLiteral VInstance :: defaultVulkanInstanceTitle = __VULKAN_INSTANCE_DEFAULT_TITLE; // NOLINT(clion-misra-cpp2008-8-0-1)

extern auto populateDebugMessengerCreateInfo (
        VulkanDebugMessengerCreateInfo *
) noexcept -> void;

inline static auto populateApplicationInfoStructure(
        VulkanApplicationInfo * applicationInfo,
        cds :: StringLiteral    applicationName
) noexcept -> void {

    if(applicationInfo == nullptr) {
        return;
    }

#if !defined(_MSC_VER)

    * applicationInfo = (VulkanApplicationInfo) {
        .sType              = VulkanStructureType :: VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName   = applicationName,
        .applicationVersion = VInstance :: defaultVulkanApplicationVersion,
        .pEngineName        = __VULKAN_INSTANCE_APP_INFO_ENGINE_NO_ENGINE,
        .engineVersion      = VInstance :: defaultVulkanEngineVersion,
        .apiVersion         = VInstance :: defaultVulkanAPIVersion,
    };

#else

    applicationInfo->sType              = VulkanStructureType :: VK_STRUCTURE_TYPE_APPLICATION_INFO;
    applicationInfo->pApplicationName   = VInstance :: DEFAULT_VULKAN_INSTANCE_TITLE;
    applicationInfo->applicationVersion = VK_MAKE_VERSION(1U, 2U, 0U);  // NOLINT(hicpp-signed-bitwise)
    applicationInfo->pEngineName        = __VULKAN_INSTANCE_APP_INFO_ENGINE_NO_ENGINE;
    applicationInfo->engineVersion      = VK_MAKE_VERSION(1U, 2U, 0U);  // NOLINT(hicpp-signed-bitwise)
    applicationInfo->apiVersion         = VK_API_VERSION_1_2;                               // NOLINT(hicpp-signed-bitwise)

#endif

}

inline static auto populateInstanceCreateInfo (
        VulkanInstanceCreateInfo                                  * pCreateInfo,
        VulkanApplicationInfo                               const * pApplicationInfo,
        uint32                                                      enabledExtensionCount,
        GLFWExtensionLiteral                                const * pEnabledExtensions,
        uint32                                                      enabledValidationLayerCount     = 0U,
        VValidationLayer :: VulkanValidationLayerLiteral    const * pValidationLayers               = nullptr,
        void                                                const * pNext                           = nullptr
) noexcept -> void {
    if ( pCreateInfo == nullptr ) {
        return;
    }

    * pCreateInfo = ( VulkanInstanceCreateInfo ) {
        .sType                      = VulkanStructureType  :: VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pNext                      = pNext,
        .flags                      = VULKAN_NULL_FLAGS,
        .pApplicationInfo           = pApplicationInfo,
        .enabledLayerCount          = enabledValidationLayerCount,
        .ppEnabledLayerNames        = pValidationLayers,
        .enabledExtensionCount      = enabledExtensionCount,
        .ppEnabledExtensionNames    = pEnabledExtensions
    };
}

auto VInstance :: setup() noexcept -> VulkanResult {
    VulkanApplicationInfo       applicationInfo {};
    VulkanInstanceCreateInfo    createInfo      {};
    auto                        extensions      = VStandardUtils::getGLFWRequiredExtensions(false);

    populateApplicationInfoStructure (
            & applicationInfo,
            this->_name.c_str()
    );

    populateInstanceCreateInfo (
            & createInfo,
            & applicationInfo,
            static_cast < uint32 > ( extensions.size() ),
            extensions.data()
    );

    return vkCreateInstance( & createInfo, nullptr, & this->_instance );
}

auto VInstance :: setup (
        VValidationLayerCollection const & layerCollection
) noexcept -> VulkanResult {

    VulkanApplicationInfo           applicationInfo {};
    VulkanInstanceCreateInfo        createInfo      {};
    VulkanDebugMessengerCreateInfo  debugCreateInfo {};

    auto                        extensions                          = VStandardUtils::getGLFWRequiredExtensions(true);
    static auto                 _persistent_validationLayerLiterals = layerCollection.getValidationLayerLiterals();

    populateApplicationInfoStructure( & applicationInfo, this->_name.c_str() );
    populateDebugMessengerCreateInfo( & debugCreateInfo );

    populateInstanceCreateInfo(
            & createInfo,
            & applicationInfo,
            static_cast < uint32 > ( extensions.size() ),
            extensions.data(),
            static_cast < uint32 > ( _persistent_validationLayerLiterals.size() ),
            _persistent_validationLayerLiterals.data(),
            reinterpret_cast < void const * > ( & debugCreateInfo )
    );

    return vkCreateInstance( & createInfo, nullptr, & this->_instance );
}

auto VInstance :: clear() noexcept -> void {

    vkDestroyInstance( this->_instance, nullptr );
}

#include <sstream>
auto VInstance :: toString() const noexcept -> String {

    std::stringstream oss;

    oss << "VInstance { " <<
        "handle = 0x" << reinterpret_cast < AddressValueType > (this->_instance) <<
        ", name = " << this->_name << " }";

    return oss.str();
}


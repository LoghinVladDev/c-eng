//
// Created by vladl on 06/08/2020.
//

#include "VInstance.h"
#include <vkDefs/VInstanceDefinitions.h>
#include <vkUtils/VStdUtils.h>

[[maybe_unused]] const char* engine::VInstance::DEFAULT_VULKAN_INSTANCE_TITLE = __VULKAN_INSTANCE_DEFAULT_TITLE;

extern void populateDebugMessengerCreateInfo ( VulkanDebugMessengerCreateInfo * ) noexcept;

inline static void populateApplicationInfoStructure( VulkanApplicationInfo * applicationInfo ) noexcept {
    if(applicationInfo == nullptr)
        return;

#if !defined(_MSC_VER)
    *applicationInfo = (VulkanApplicationInfo){
        .sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName   = engine::VInstance::DEFAULT_VULKAN_INSTANCE_TITLE,
        .applicationVersion = VK_MAKE_VERSION(1U, 2U, 0U),  // NOLINT(hicpp-signed-bitwise)
        .pEngineName        = __VULKAN_INSTANCE_APP_INFO_ENGINE_NO_ENGINE,
        .engineVersion      = VK_MAKE_VERSION(1U, 2U, 0U),  // NOLINT(hicpp-signed-bitwise)
        .apiVersion         = VK_API_VERSION_1_2                               // NOLINT(hicpp-signed-bitwise)
    };
#else
    applicationInfo->sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    applicationInfo->pApplicationName   = engine::VInstance::DEFAULT_VULKAN_INSTANCE_TITLE;
    applicationInfo->applicationVersion = VK_MAKE_VERSION(1U, 2U, 0U);  // NOLINT(hicpp-signed-bitwise)
    applicationInfo->pEngineName        = __VULKAN_INSTANCE_APP_INFO_ENGINE_NO_ENGINE;
    applicationInfo->engineVersion      = VK_MAKE_VERSION(1U, 2U, 0U);  // NOLINT(hicpp-signed-bitwise)
    applicationInfo->apiVersion         = VK_API_VERSION_1_2;                               // NOLINT(hicpp-signed-bitwise)

#endif

}

VulkanResult engine::VInstance::setup() noexcept {
    VulkanApplicationInfo       applicationInfo {};
    VulkanInstanceCreateInfo    createInfo      {};
    auto                        extensions      = VStandardUtils::getGLFWRequiredExtensions(false);

    populateApplicationInfoStructure( & applicationInfo );

    applicationInfo.pApplicationName    = this->_name.c_str();

    createInfo.sType                    = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo         = ( & applicationInfo );
    createInfo.enabledExtensionCount    = VULKAN_LAYERS_NONE;
    createInfo.pNext                    = nullptr;
    createInfo.enabledExtensionCount    = static_cast < uint32 > ( extensions.size() );
    createInfo.ppEnabledExtensionNames  = extensions.data();

    return vkCreateInstance( & createInfo, nullptr, & this->_instance );
}

VulkanResult engine::VInstance::setup(const VValidationLayerCollection & layerCollection) noexcept {
    VulkanApplicationInfo           applicationInfo {};
    VulkanInstanceCreateInfo        createInfo      {};
    VulkanDebugMessengerCreateInfo  debugCreateInfo {};

    auto                        extensions                          = VStandardUtils::getGLFWRequiredExtensions(true);
    static auto                 _persistent_validationLayerLiterals = layerCollection.getValidationLayerLiterals();

    populateApplicationInfoStructure( & applicationInfo );
    populateDebugMessengerCreateInfo( & debugCreateInfo );

    applicationInfo.pApplicationName    = this->_name.c_str();

    createInfo.sType                    = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo         = ( & applicationInfo );
    createInfo.enabledLayerCount        = static_cast < uint32 > ( _persistent_validationLayerLiterals.size() );
    createInfo.ppEnabledLayerNames      = _persistent_validationLayerLiterals.data();
    createInfo.pNext                    = ( VulkanDebugMessengerCreateInfo * ) & debugCreateInfo;
    createInfo.enabledExtensionCount    = static_cast < uint32 > ( extensions.size() );
    createInfo.ppEnabledExtensionNames  = extensions.data();

    return vkCreateInstance( & createInfo, nullptr, & this->_instance );
}

void engine::VInstance::clean() noexcept {
    vkDestroyInstance( this->_instance, nullptr );
}
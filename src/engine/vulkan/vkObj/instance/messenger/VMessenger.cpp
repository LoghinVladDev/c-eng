//
// Created by vladl on 06/08/2020.
//

#include <vulkanExplicitTypes.h>
#include <VValidationLayer.h>
#include <vkDefinitions.h>
#include "VMessenger.h"
#include <VInstanceDefinitions.h>

static VULKAN_API_ATTRIBUTE VulkanBool32 VULKAN_API_CALL staticMessengerDebugCallback (
        VulkanDebugMessageSeverityFlagBits              messageSeverity,
        [[maybe_unused]] VulkanDebugMessageTypeFlags    messageType,
        const VulkanDebugMessengerCallbackData        * callbackDataPtr,
        [[maybe_unused]] void                         * userDataPtr
) noexcept {

    if( messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT ) {
        std::cerr << "[LAYER DEBUG CALLBACK] validation layer: " << callbackDataPtr->pMessage << '\n';
        std::cerr.flush();
    }

    return VULKAN_FALSE;
}

[[nodiscard]] static VulkanResult createDebugMessengerExtension (
        VulkanInstance                         instance,
        const VulkanDebugMessengerCreateInfo * createInfoPtr,
        const VulkanAllocationCallbacks      * allocatorPtr,
        VulkanDebugMessenger                 * messengerPtr
) noexcept {
    auto function = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, __VULKAN_INSTANCE_PROC_ADDRESS_CREATE_DEBUG_UTIL_MESSENGER_EXT);

    if( function == nullptr )
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    return function( instance, createInfoPtr, allocatorPtr, messengerPtr );
}

static void destroyDebugMessengerExtension (
        VulkanInstance                         instance,
        VulkanDebugMessenger                   debugMessenger,
        const VulkanAllocationCallbacks      * allocatorPtr
) noexcept {
    auto function = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr( instance, __VULKAN_INSTANCE_PROC_ADDRESS_DESTROY_DEBUG_UTIL_MESSENGER_EXT );

    if( function == nullptr )
        return;
    function( instance, debugMessenger, allocatorPtr );
}

void populateDebugMessengerCreateInfo ( VulkanDebugMessengerCreateInfo * createInfo ) noexcept {
    if( createInfo == nullptr )
        return;

    *createInfo = {};

    createInfo->sType            = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo->messageSeverity  = engine::VMessenger::DEFAULT_DEBUG_MESSAGE_SEVERITY;
    createInfo->messageType      = engine::VMessenger::DEFAULT_DEBUG_MESSAGE_TYPE;
    createInfo->pfnUserCallback  = staticMessengerDebugCallback;
    createInfo->pUserData        = nullptr;
}

VulkanResult engine::VMessenger::setup(engine::VInstance * givenInstance) noexcept (false) {

    if( givenInstance == nullptr && this->_vulkanInstance == nullptr )
        throw engine::EngineVMessengerProvideVInstance();

    if( givenInstance != nullptr )
        this->_vulkanInstance = givenInstance;

    VulkanDebugMessengerCreateInfo createInfo {};
    populateDebugMessengerCreateInfo( & createInfo );

    return createDebugMessengerExtension( this->_vulkanInstance->data(), & createInfo, nullptr, & this->_debugMessenger );
}

void engine::VMessenger::clean() noexcept {
    destroyDebugMessengerExtension( this->_vulkanInstance->data(), this->_debugMessenger, nullptr );
}
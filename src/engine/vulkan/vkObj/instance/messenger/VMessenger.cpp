//
// Created by vladl on 06/08/2020.
//

#include <vulkanExplicitTypes.h>
#include <VValidationLayer.h>
#include <vkDefinitions.h>
#include "VMessenger.h"
#include <VInstanceDefinitions.h>

/**
 * @brief Internal Function representing the default messenger callback
 *
 * Will be expanded to a observer-notifier pattern
 *
 * @param messageSeverity : VulkanDebugMessageSeverityFlagBits = Severity of current message
 * @param messageType : VulkanDebugMessageTypeFlags = Message Type ( can be of multiple types, bitmask )
 * @param callbackDataPtr : VulkanDebugMessengerCallbackData cptr = Structure containing current message and several Debug Information values
 * @param userDataPtr : void ptr = Address that the user has bound to always be sent. Will include the VMessenger address.
 *
 * @exceptsafe
 *
 * @return VulkanBool32 = VULKAN_FALSE
 */
static VULKAN_API_ATTRIBUTE auto VULKAN_API_CALL staticMessengerDebugCallback (
        VulkanDebugMessageSeverityFlagBits              messageSeverity,
        [[maybe_unused]] VulkanDebugMessageTypeFlags    messageType,
        VulkanDebugMessengerCallbackData        const * callbackDataPtr,
        [[maybe_unused]] void                         * userDataPtr
) noexcept -> VulkanBool32 {

    if( messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT ) { /// only print warnings
        std::cerr << "[LAYER DEBUG CALLBACK] validation layer: " << callbackDataPtr->pMessage << '\n';
        std::cerr.flush(); // warning: causes gcov to go crazy
    }

    return VULKAN_FALSE;
}

/**
 * @brief Function is an interface to the acquisition and call of the Messenger Creation Function
 *
 * @param instance : VulkanInstance = Vulkan Instance Handle
 * @param createInfoPtr : VulkanDebugMessengerCreateInfo cptr = Address to the Structure containing Creation Parameters
 * @param allocatorPtr : VulkanAllocationCallbacks cptr = Address to the Allocator Callback, or nullptr if not using custom allocator
 * @param messengerPtr : VulkanDebugMessenger ptr = Address to save the Messenger Handle in
 *
 * @exceptsafe
 *
 * @return VulkanResult =
 *      VulkanResult::VK_SUCCESS if Messenger was created OK OR
 *      VulkanResult::VK_ERROR_EXTENSION_NOT_PRESENT if Messenger Extension does not exist
 */
[[nodiscard]] static auto createDebugMessengerExtension (
        VulkanInstance                         instance,
        VulkanDebugMessengerCreateInfo const * createInfoPtr,
        VulkanAllocationCallbacks      const * allocatorPtr,
        VulkanDebugMessenger                 * messengerPtr
) noexcept -> VulkanResult {
    /// since Vulkan Messenger is an Utility Exception, get Function Address from Library
    auto function = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, __VULKAN_INSTANCE_PROC_ADDRESS_CREATE_DEBUG_UTIL_MESSENGER_EXT);

    if( function == nullptr )
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    return function( instance, createInfoPtr, allocatorPtr, messengerPtr );
}

/**
 * @brief Function is an interface to the acquisition and call of the Messenger Destruction Function
 *
 * @param instance : VulkanInstance = Vulkan Instance Handle
 * @param debugMessenger : VulkanDebugMessenger = Messenger Handle to Destroy
 * @param allocatorPtr : VulkanAllocationCallbacks = Address of De-Allocator Used, if custom allocation was used. nullptr if none used
 *
 * @exceptsafe
 */
static auto destroyDebugMessengerExtension (
        VulkanInstance                         instance,
        VulkanDebugMessenger                   debugMessenger,
        VulkanAllocationCallbacks      const * allocatorPtr
) noexcept -> void {
    auto function = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr( instance, __VULKAN_INSTANCE_PROC_ADDRESS_DESTROY_DEBUG_UTIL_MESSENGER_EXT );

    if( function == nullptr )
        return;
    function( instance, debugMessenger, allocatorPtr );
}

/**
 * @brief Internal and Externally Imported Function ( used in Instance Creation ) used to populate Debug Messenger Create Info
 *
 * @param createInfo : VulkanDebugMessengerCreateInfo ptr = Address to the structure to populate
 *
 * @exceptsafe
 */
auto populateDebugMessengerCreateInfo ( VulkanDebugMessengerCreateInfo * createInfo ) noexcept -> void {
    if( createInfo == nullptr )
        return;

    * createInfo = {
        .sType            = VulkanStructureType::VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
        .messageSeverity  = engine::VMessenger::DEFAULT_DEBUG_MESSAGE_SEVERITY, /// filter for severity
        .messageType      = engine::VMessenger::DEFAULT_DEBUG_MESSAGE_TYPE, /// filter for types
        .pfnUserCallback  = staticMessengerDebugCallback, /// callback for errors
        .pUserData        = nullptr /// passed data
    };
}

auto engine::VMessenger::setup(engine::VInstance * givenInstance) noexcept (false) -> VulkanResult {
    if( givenInstance == nullptr && this->_vulkanInstance == nullptr )
        throw engine::EngineVMessengerProvideVInstance();

    if( givenInstance != nullptr )
        this->_vulkanInstance = givenInstance;

    VulkanDebugMessengerCreateInfo createInfo {};
    populateDebugMessengerCreateInfo( & createInfo );

    return createDebugMessengerExtension(
            this->_vulkanInstance->data(), /// bind to instance
            & createInfo, /// with these parameters
            nullptr, /// no custom allocation
            & this->_debugMessenger /// save handle here
    );
}

void engine::VMessenger::clean() noexcept {
    destroyDebugMessengerExtension(
            this->_vulkanInstance->data(),
            this->_debugMessenger,
            nullptr
    );
}
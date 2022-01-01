//
// Created by loghin on 28.12.2021.
//

#ifndef __C_ENG_VULKANAPICALLS_HPP
#define __C_ENG_VULKANAPICALLS_HPP

#include <VulkanCoreConfig.hpp>

namespace engine { // NOLINT(modernize-concat-nested-namespaces)

    namespace vulkan {

        inline static auto toVulkanFormat (
                __C_ENG_TYPE ( ApplicationInfo )    const * pApplicationInfo,
                VkApplicationInfo                         * pVkApplicationInfo
        ) noexcept -> void {

            if ( pApplicationInfo == nullptr || pVkApplicationInfo == nullptr ) {
                return;
            }

            * pVkApplicationInfo = {
                    .sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO,
                    .pNext              = nullptr,
                    .pApplicationName   = pApplicationInfo->name,
                    .applicationVersion = instanceVersionToUInt32 ( pApplicationInfo->version ),
                    .pEngineName        = pApplicationInfo->engineName,
                    .engineVersion      = instanceVersionToUInt32 ( pApplicationInfo->engineVersion ),
                    .apiVersion         = instanceVersionToUInt32 ( pApplicationInfo->apiVersion )
            };
        }

        inline static auto toVulkanFormat (
                __C_ENG_TYPE ( AllocationCallbacks )    const * pAllocationCallbacks,
                VkAllocationCallbacks                         * pVkAllocationCallbacks
        ) noexcept -> void {

            if ( pAllocationCallbacks == nullptr || pVkAllocationCallbacks == nullptr ) {
                return;
            }

            * pVkAllocationCallbacks = {
                    .pUserData              = pAllocationCallbacks->pUserData,
                    .pfnAllocation          = pAllocationCallbacks->allocationCallback,
                    .pfnReallocation        = pAllocationCallbacks->reallocationCallback,
                    .pfnFree                = pAllocationCallbacks->freeCallback,
                    .pfnInternalAllocation  = pAllocationCallbacks->internalAllocationNotificationCallback,
                    .pfnInternalFree        = pAllocationCallbacks->internalFreeNotificationCallback
            };
        }

        inline static auto toVulkanFormat (
                __C_ENG_TYPE ( InstanceCreateInfo )     const * pCreateInfo,
                VkInstanceCreateInfo                          * pVkCreateInfo,
                VkApplicationInfo                       const * pVkApplicationInfo,
                void                                    const * pNext
        ) noexcept -> void {

            if ( pCreateInfo == nullptr || pVkCreateInfo == nullptr ) {
                return;
            }

            * pVkCreateInfo = {
                    .sType                      = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
                    .pNext                      = pNext,
                    .flags                      = pCreateInfo->flags,
                    .pApplicationInfo           = pVkApplicationInfo,
                    .enabledLayerCount          = pCreateInfo->enabledLayerCount,
                    .ppEnabledLayerNames        = pCreateInfo->pEnabledLayerNames,
                    .enabledExtensionCount      = pCreateInfo->enabledExtensionCount,
                    .ppEnabledExtensionNames    = pCreateInfo->pEnabledExtensionNames
            };
        }

        inline static auto toVulkanFormat (
                __C_ENG_TYPE ( DebugMessengerCreateInfo )   const * pCreateInfo,
                VkDebugUtilsMessengerCreateInfoEXT                * pVkCreateInfo
        ) noexcept -> void {

            if ( pCreateInfo == nullptr || pVkCreateInfo == nullptr ) {
                return;
            }

            * pVkCreateInfo = {
                    .sType                  = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
                    .pNext                  = nullptr,
                    .flags                  = pCreateInfo->flags,
                    .messageSeverity        = pCreateInfo->messageSeverityFlags,
                    .messageType            = pCreateInfo->messageTypeFlags,
                    .pfnUserCallback        = pCreateInfo->callback,
                    .pUserData              = pCreateInfo->pCallbackUserData
            };
        }

        inline static auto toVulkanFormat (
                __C_ENG_TYPE ( ValidationFeatures ) const * pValidationFeatures,
                VkValidationFeaturesEXT                   * pVkValidationFeatures,
                VkValidationFeatureEnableEXT              * pEnableFeatures,
                VkValidationFeatureDisableEXT             * pDisableFeatures
        ) noexcept -> void {

            if ( pValidationFeatures == nullptr || pVkValidationFeatures == nullptr ) {
                return;
            }

            for ( cds :: uint32 i = 0U; i < pValidationFeatures->enabledValidationFeatureCount; ++ i ) {
                pEnableFeatures[i] = static_cast < VkValidationFeatureEnableEXT > ( pValidationFeatures->pEnabledValidationFeatures[i] );
            }

            for ( cds :: uint32 i = 0U; i < pValidationFeatures->disabledValidationFeatureCount; ++ i ) {
                pDisableFeatures[i] = static_cast < VkValidationFeatureDisableEXT > ( pValidationFeatures->pDisabledValidationFeatures[i] );
            }

            * pVkValidationFeatures = {
                    .sType                          = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT,
                    .pNext                          = nullptr,
                    .enabledValidationFeatureCount  = pValidationFeatures->enabledValidationFeatureCount,
                    .pEnabledValidationFeatures     = pEnableFeatures,
                    .disabledValidationFeatureCount = pValidationFeatures->disabledValidationFeatureCount,
                    .pDisabledValidationFeatures    = pDisableFeatures
            };
        }

        __C_ENG_NO_DISCARD inline static auto enumerateInstanceVersion (
                cds :: uint32 * pOutRawVersion
        ) noexcept -> __C_ENG_TYPE ( Result ) {

            return static_cast < __C_ENG_TYPE ( Result ) > ( vkEnumerateInstanceVersion ( pOutRawVersion ) );
        }

        __C_ENG_NO_DISCARD inline static auto enumerateInstanceLayerProperties (
                cds :: uint32                       * pLayerPropertiesCount,
                __C_ENG_TYPE ( LayerProperties )    * pProperties           = nullptr
        ) noexcept -> __C_ENG_TYPE ( Result ) {

            if ( pLayerPropertiesCount == nullptr ) {
                return __C_ENG_TYPE ( Result ) :: ResultErrorIllegalArgument;
            }

            if ( pProperties == nullptr ) {
                return static_cast < __C_ENG_TYPE ( Result ) > ( vkEnumerateInstanceLayerProperties (
                            pLayerPropertiesCount,
                            nullptr
                    ));
            }

            auto pRawLayerProperties = new VkLayerProperties [ * pLayerPropertiesCount ];
            auto result = vkEnumerateInstanceLayerProperties (
                        pLayerPropertiesCount,
                        pRawLayerProperties
                );

            if ( result != VkResult :: VK_SUCCESS ) {
                delete [] pRawLayerProperties;
                return static_cast < __C_ENG_TYPE ( Result ) > ( result );
            }

            for ( cds :: uint32 i = 0U; i < * pLayerPropertiesCount; ++ i ) {
                (void) std :: memcpy ( pProperties[i].layerName,   pRawLayerProperties[i].layerName,   VK_MAX_EXTENSION_NAME_SIZE ); // NOLINT(clion-misra-cpp2008-5-2-12)
                (void) std :: memcpy ( pProperties[i].description, pRawLayerProperties[i].description, VK_MAX_DESCRIPTION_SIZE ); // NOLINT(clion-misra-cpp2008-5-2-12)
                pProperties[i].implementationVersion    = pRawLayerProperties[i].implementationVersion;
                pProperties[i].specVersion              = uInt32ToInstanceVersion ( pRawLayerProperties[i].specVersion );
            }

            delete[] pRawLayerProperties;
            return __C_ENG_TYPE ( Result ) :: ResultSuccess;
        }

        __C_ENG_NO_DISCARD inline static auto enumerateDeviceLayerProperties (
                __C_ENG_TYPE ( PhysicalDeviceHandle )   handle,
                cds :: uint32                         * pLayerPropertiesCount,
                __C_ENG_TYPE ( LayerProperties )      * pProperties             = nullptr
        ) noexcept -> __C_ENG_TYPE ( Result ) {

            if (
                    handle                  == nullptr ||
                    pLayerPropertiesCount   == nullptr
            ) {
                return __C_ENG_TYPE ( Result ) :: ResultErrorIllegalArgument;
            }

            if ( pProperties == nullptr ) {
                return static_cast < __C_ENG_TYPE ( Result ) > (
                        vkEnumerateDeviceLayerProperties (
                                handle,
                                pLayerPropertiesCount,
                                nullptr
                        ));
            }

            auto pRawLayerProperties = new VkLayerProperties [ * pLayerPropertiesCount ];
            auto result = vkEnumerateDeviceLayerProperties (
                        handle,
                        pLayerPropertiesCount,
                        pRawLayerProperties
                );

            if ( result != VkResult :: VK_SUCCESS ) {
                delete [] pRawLayerProperties;
                return static_cast < __C_ENG_TYPE ( Result ) > ( result );
            }

            for ( cds :: uint32 i = 0U; i < * pLayerPropertiesCount; ++ i ) {
                (void) std :: memcpy ( pProperties[i].layerName,   pRawLayerProperties[i].layerName,   VK_MAX_EXTENSION_NAME_SIZE ); // NOLINT(clion-misra-cpp2008-5-2-12)
                (void) std :: memcpy ( pProperties[i].description, pRawLayerProperties[i].description, VK_MAX_DESCRIPTION_SIZE ); // NOLINT(clion-misra-cpp2008-5-2-12)
                pProperties[i].implementationVersion    = pRawLayerProperties[i].implementationVersion;
                pProperties[i].specVersion              = uInt32ToInstanceVersion ( pRawLayerProperties[i].specVersion );
            }

            delete[] pRawLayerProperties;
            return __C_ENG_TYPE ( Result ) :: ResultSuccess;
        }

        __C_ENG_NO_DISCARD inline static auto enumerateInstanceExtensionProperties (
                cds :: StringLiteral                    layerName,
                cds :: uint32                         * pPropertyCount,
                __C_ENG_TYPE ( ExtensionProperties )  * pProperties     = nullptr
        ) noexcept -> __C_ENG_TYPE ( Result ) {

            if ( pPropertyCount == nullptr ) {
                return ResultErrorIllegalArgument;
            }

            if ( pProperties == nullptr ) {
                return static_cast < __C_ENG_TYPE ( Result ) > ( vkEnumerateInstanceExtensionProperties (
                            layerName,
                            pPropertyCount,
                            nullptr
                    ));
            }

            auto pRawExtensionProperties = new VkExtensionProperties [ * pPropertyCount ];
            auto result = vkEnumerateInstanceExtensionProperties(
                        layerName,
                        pPropertyCount,
                        pRawExtensionProperties
                );

            if ( result != VkResult :: VK_SUCCESS ) {
                delete[] pRawExtensionProperties;
                return static_cast < __C_ENG_TYPE ( Result ) > ( result );
            }

            for ( cds :: uint32 i = 0U; i < * pPropertyCount; ++ i ) {
                (void) std :: memcpy ( pProperties[i].name, pRawExtensionProperties[i].extensionName, VK_MAX_EXTENSION_NAME_SIZE ); // NOLINT(clion-misra-cpp2008-5-2-12)
                pProperties[i].specVersion = pRawExtensionProperties[i].specVersion;
            }

            delete[] pRawExtensionProperties;
            return ResultSuccess;
        }

        __C_ENG_NO_DISCARD static inline auto createInstance (
                __C_ENG_TYPE ( InstanceCreateInfo )     const * pCreateInfo,
                __C_ENG_TYPE ( AllocationCallbacks )    const * pAllocationCallbacks,
                __C_ENG_TYPE ( InstanceHandle )               * pInstanceHandle
        ) noexcept -> __C_ENG_TYPE ( Result ) {

            if (
                    pCreateInfo     == nullptr ||
                    pInstanceHandle == nullptr
            ) {
                return ResultErrorIllegalArgument;
            }

            VkDebugUtilsMessengerCreateInfoEXT  messengerCreateInfo {};
            VkAllocationCallbacks               allocationCallbacks {};
            VkApplicationInfo                   applicationInfo {};
            VkInstanceCreateInfo                instanceCreateInfo {};
            VkValidationFeaturesEXT             validationFeatures {};

            VkValidationFeatureEnableEXT       validationFeatureEnableArray     [__C_ENG_VULKAN_CORE_VALIDATION_FEATURE_ENABLE_MAX_COUNT];
            VkValidationFeatureDisableEXT      validationFeatureDisableArray    [__C_ENG_VULKAN_CORE_VALIDATION_FEATURE_DISABLE_MAX_COUNT];

            VkAllocationCallbacks       const * pUsedAllocationCallbacks = nullptr;

            VkBaseInStructure                 * pPreviousInChain = nullptr;

            void                        const * pInstanceNext = nullptr;

            if ( pAllocationCallbacks != nullptr ) {
                pUsedAllocationCallbacks = & allocationCallbacks;
                toVulkanFormat ( pAllocationCallbacks, & allocationCallbacks );
            }

            auto currentGenericStructure = reinterpret_cast < __C_ENG_TYPE ( BaseInStructure ) const * > ( pCreateInfo->pNext );

            while ( currentGenericStructure != nullptr ) {
                VkBaseInStructure * pCurrentInChain = nullptr;

                if ( currentGenericStructure->structureType == StructureTypeDebugUtilsMessengerCreateInfo ) {
                    auto currentStructure = reinterpret_cast < __C_ENG_TYPE ( DebugMessengerCreateInfo ) const * > ( currentGenericStructure );
                    toVulkanFormat ( currentStructure, & messengerCreateInfo );
                    pCurrentInChain = reinterpret_cast < VkBaseInStructure * > ( & messengerCreateInfo );
                }

                if ( currentGenericStructure->structureType == StructureTypeValidationFeatures ) {
                    auto currentStructure = reinterpret_cast < __C_ENG_TYPE ( ValidationFeatures ) const * > ( currentGenericStructure );
                    toVulkanFormat ( currentStructure, & validationFeatures, validationFeatureEnableArray, validationFeatureDisableArray ); // NOLINT(clion-misra-cpp2008-5-2-12)
                    pCurrentInChain = reinterpret_cast < VkBaseInStructure * > ( & validationFeatures );
                }

                if ( pInstanceNext == nullptr ) {
                    pInstanceNext = pCurrentInChain;
                }

                if ( pPreviousInChain != nullptr ) {
                    pPreviousInChain->pNext = pCurrentInChain;
                }

                pPreviousInChain = pCurrentInChain;
                currentGenericStructure = reinterpret_cast < __C_ENG_TYPE ( BaseInStructure ) const * > ( currentGenericStructure->pNext );
            }

            toVulkanFormat ( pCreateInfo->pApplicationInfo, & applicationInfo );
            toVulkanFormat ( pCreateInfo, & instanceCreateInfo, & applicationInfo, pInstanceNext );

            return static_cast < __C_ENG_TYPE ( Result ) > (
                    vkCreateInstance (
                        & instanceCreateInfo,
                        pUsedAllocationCallbacks,
                        pInstanceHandle
                    )
            );
        }

        static inline auto destroyInstance (
                __C_ENG_TYPE ( InstanceHandle )                 handle,
                __C_ENG_TYPE ( AllocationCallbacks )    const * pAllocatorCallbacks
        ) noexcept -> __C_ENG_TYPE ( Result ) {

            if ( handle == nullptr ) {
                return ResultErrorIllegalArgument;
            }

            VkAllocationCallbacks vkCallbacks {};
            VkAllocationCallbacks * pUsedCallbacks = nullptr;

            if ( pAllocatorCallbacks != nullptr ) {
                pUsedCallbacks = & vkCallbacks;
                toVulkanFormat ( pAllocatorCallbacks, & vkCallbacks );
            }

            vkDestroyInstance ( handle, pUsedCallbacks );
            return ResultSuccess;
        }

        static inline auto createDebugMessenger (
                __C_ENG_TYPE ( InstanceHandle )                     instanceHandle,
                __C_ENG_TYPE ( DebugMessengerCreateInfo )   const * pMessengerCreateInfo,
                __C_ENG_TYPE ( AllocationCallbacks )        const * pAllocationCallbacks,
                __C_ENG_TYPE ( DebugMessengerHandle )             * pHandle
        ) noexcept -> __C_ENG_TYPE ( Result ) {

            if ( pMessengerCreateInfo == nullptr || pHandle == nullptr || instanceHandle == nullptr ) {
                return ResultErrorIllegalArgument;
            }

            PFN_vkCreateDebugUtilsMessengerEXT  function = nullptr;

            VkDebugUtilsMessengerCreateInfoEXT  debugMessengerCreateInfo {};
            VkAllocationCallbacks               allocationCallbacks {};

            VkAllocationCallbacks             * pUsedAllocationCallbacks = nullptr;

            function = reinterpret_cast < PFN_vkCreateDebugUtilsMessengerEXT > (
                    vkGetInstanceProcAddr ( instanceHandle, __C_ENG_VULKAN_CORE_FUNCTION_NAME_CREATE_DEBUG_MESSENGER )
            );

            if ( function == nullptr ) {
                return ResultErrorFunctionHandleNotFound;
            }

            if ( pAllocationCallbacks != nullptr ) {
                pUsedAllocationCallbacks = & allocationCallbacks;
                toVulkanFormat ( pAllocationCallbacks, & allocationCallbacks );
            }

            toVulkanFormat (
                    pMessengerCreateInfo,
                    & debugMessengerCreateInfo
            );

            return static_cast < __C_ENG_TYPE ( Result ) > ( function (
                    instanceHandle,
                    & debugMessengerCreateInfo,
                    pUsedAllocationCallbacks,
                    pHandle
            ));
        }

        static inline auto destroyDebugMessenger (
                __C_ENG_TYPE ( InstanceHandle )                 instanceHandle,
                __C_ENG_TYPE ( DebugMessengerHandle )           debugMessengerHandle,
                __C_ENG_TYPE ( AllocationCallbacks )    const * pAllocationCallbacks
        ) noexcept -> __C_ENG_TYPE ( Result ) {

            if ( instanceHandle == nullptr || debugMessengerHandle == nullptr ) {
                return ResultErrorIllegalArgument;
            }

            PFN_vkDestroyDebugUtilsMessengerEXT function = nullptr;

            VkAllocationCallbacks               allocationCallbacks {};
            VkAllocationCallbacks             * pUsedCallbacks = nullptr;

            function = reinterpret_cast < PFN_vkDestroyDebugUtilsMessengerEXT > (
                    vkGetInstanceProcAddr ( instanceHandle, __C_ENG_VULKAN_CORE_FUNCTION_NAME_DESTROY_DEBUG_MESSENGER )
            );

            if ( function == nullptr ) {
                return ResultErrorFunctionHandleNotFound;
            }

            if ( pAllocationCallbacks != nullptr ) {
                pUsedCallbacks = & allocationCallbacks;
                toVulkanFormat ( pAllocationCallbacks, & allocationCallbacks );
            }

            function ( instanceHandle, debugMessengerHandle, pUsedCallbacks );
            return ResultSuccess;
        }

    }

}

#endif //__C_ENG_VULKANAPICALLS_HPP

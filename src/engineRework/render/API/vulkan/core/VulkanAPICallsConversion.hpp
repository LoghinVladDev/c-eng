//
// Created by loghin on 16.02.2022.
//

#ifndef C_ENG_VULKANAPICALLSCONVERSION_HPP
#define C_ENG_VULKANAPICALLSCONVERSION_HPP

#include <VulkanAPICallsPrivate.hpp>
#include <VulkanAPICallsTypes.hpp>

#define C_ENG_MAP_START     HEADER
#include <ObjectMapping.hpp>


namespace engine :: vulkan {

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        static inline auto toVulkanFormat (
                VkAllocationCallbacks                 * pDestination,
                Type ( AllocationCallbacks )    const * pSource
        ) noexcept -> VkAllocationCallbacks * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

            if ( pDestination == nullptr || pSource == nullptr ) {
                return nullptr;
            }

#endif

            * pDestination = {
                    .pUserData              = pSource->pUserData,
                    .pfnAllocation          = pSource->allocationCallback,
                    .pfnReallocation        = pSource->reallocationCallback,
                    .pfnFree                = pSource->freeCallback,
                    .pfnInternalAllocation  = pSource->internalAllocationNotificationCallback,
                    .pfnInternalFree        = pSource->internalFreeNotificationCallback
            };

            return pDestination;
        }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_REPORT_AVAILABLE
        static inline auto toVulkanFormat (
                VkDebugReportCallbackCreateInfoEXT        * pDestination,
                Type ( DebugReportCreateInfo )      const * pSource
        ) noexcept -> VkDebugReportCallbackCreateInfoEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

            if ( pDestination == nullptr || pSource == nullptr ) {
                return nullptr;
            }

#endif

            * pDestination = {
                    .sType          = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT,
                    .pNext          = nullptr,
                    .flags          = pSource->flags,
                    .pfnCallback    = pSource->callback,
                    .pUserData      = pSource->pUserData
            };

            return pDestination;
        }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_UTILS_AVAILABLE
        static inline auto toVulkanFormat (
                VkDebugUtilsMessengerCreateInfoEXT         * pDestination,
                Type ( DebugMessengerCreateInfo )    const * pSource
        ) noexcept -> VkDebugUtilsMessengerCreateInfoEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

            if ( pDestination == nullptr || pSource == nullptr ) {
                return nullptr;
            }

#endif

            * pDestination = {
                    .sType                  = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
                    .pNext                  = nullptr,
                    .flags                  = pSource->flags,
                    .messageSeverity        = pSource->messageSeverityFlags,
                    .messageType            = pSource->messageTypeFlags,
                    .pfnUserCallback        = pSource->callback,
                    .pUserData              = pSource->pCallbackUserData
            };

            return pDestination;
        }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_FEATURES_AVAILABLE
        static inline auto toVulkanFormat (
                VkValidationFeaturesEXT           * pDestination,
                Type ( ValidationFeatures ) const * pSource
        ) noexcept -> VkValidationFeaturesEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

            if ( pDestination == nullptr || pSource == nullptr ) {
                return nullptr;
            }

#endif

            * pDestination = {
                    .sType                          = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT,
                    .pNext                          = nullptr,
                    .enabledValidationFeatureCount  = pSource->enabledValidationFeatureCount,
                    .pEnabledValidationFeatures     = nullptr,
                    .disabledValidationFeatureCount = pSource->disabledValidationFeatureCount,
                    .pDisabledValidationFeatures    = nullptr
            };

            return pDestination;
        }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_FLAGS_AVAILABLE
        static inline auto toVulkanFormat (
                VkValidationFlagsEXT              * pDestination,
                Type ( ValidationFlags )    const * pSource
        ) noexcept -> VkValidationFlagsEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

            if ( pDestination == nullptr || pSource == nullptr ) {
                return nullptr;
            }

#endif

            * pDestination = {
                    .sType                          = VK_STRUCTURE_TYPE_VALIDATION_FLAGS_EXT,
                    .pNext                          = nullptr,
                    .disabledValidationCheckCount   = pSource->disabledValidationCheckCount,
                    .pDisabledValidationChecks      = nullptr
            };

            return pDestination;
        }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        static inline auto toVulkanFormat (
                VkApplicationInfo                 * pDestination,
                Type ( ApplicationInfo )    const * pSource
        ) noexcept -> VkApplicationInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

            if ( pDestination == nullptr ) {
                return nullptr;
            }

#endif

            if ( pSource == nullptr ) {
                return nullptr;
            }

            * pDestination = {
                    .sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO,
                    .pNext              = nullptr,
                    .pApplicationName   = pSource->name,
                    .applicationVersion = instanceVersionToUInt32 ( pSource->version ),
                    .pEngineName        = pSource->engineName,
                    .engineVersion      = instanceVersionToUInt32 ( pSource->engineVersion ),
                    .apiVersion         = instanceVersionToUInt32 ( pSource->apiVersion )
            };

            return pDestination;
        }

        static inline auto toVulkanFormat (
                VkInstanceCreateInfo              * pDestination,
                Type ( InstanceCreateInfo ) const * pSource
        ) noexcept -> VkInstanceCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

            if (
                    pDestination    == nullptr ||
                    pSource         == nullptr
            ) {
                return nullptr;
            }

#endif

            * pDestination = {
                    .sType                      = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
                    .pNext                      = nullptr,
                    .flags                      = pSource->flags,
                    .pApplicationInfo           = pDestination->pApplicationInfo,
                    .enabledLayerCount          = pSource->enabledLayerCount,
                    .ppEnabledLayerNames        = pSource->pEnabledLayerNames,
                    .enabledExtensionCount      = pSource->enabledExtensionCount,
                    .ppEnabledExtensionNames    = pSource->pEnabledExtensionNames
            };

            return pDestination;
        }

        static inline auto prepareContext (
                CreateInstanceContext             * pContext,
                Type ( InstanceCreateInfo ) const * pSource
        ) noexcept -> VkInstanceCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

            if ( pContext == nullptr || pSource == nullptr ) {
                return nullptr;
            }

#endif

            pContext->instance.pApplicationInfo = toVulkanFormat ( & pContext->applicationInfo, pSource->pApplicationInfo );

            auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource );
            auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->instance, pSource ) );

            while ( pCurrent != nullptr ) {

                switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_REPORT_AVAILABLE
                    case StructureTypeDebugReportCallbackCreateInfo:
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->debugReport,
                                        reinterpret_cast < Type ( DebugReportCreateInfo ) const * > ( pCurrent )
                                )
                        );
                        break;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEBUG_UTILS_AVAILABLE
                    case StructureTypeDebugUtilsMessengerCreateInfo:
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->debugMessenger,
                                        reinterpret_cast < Type ( DebugMessengerCreateInfo ) const * > ( pCurrent )
                                )
                        );
                        break;
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_FEATURES_AVAILABLE
                    case StructureTypeValidationFeatures: {

                        auto pValidationFeatures = reinterpret_cast < Type ( ValidationFeatures ) const * > ( pCurrent );
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->validationFeatures,
                                        pValidationFeatures
                                )
                        );

                        if ( pContext->validationFeatures.enabledValidationFeatureCount > __C_ENG_VULKAN_CORE_VALIDATION_FEATURE_ENABLE_MAX_COUNT ) {
                            pContext->validationFeatures.enabledValidationFeatureCount = __C_ENG_VULKAN_CORE_VALIDATION_FEATURE_ENABLE_MAX_COUNT;
                            pContext->error = ResultErrorConfigurationArraySizeSmall;
                        }

                        for ( cds :: uint32 i = 0U; i < pContext->validationFeatures.enabledValidationFeatureCount; ++ i ) {
                            pContext->validationFeatureEnables[i] = static_cast < VkValidationFeatureEnableEXT > ( pValidationFeatures->pEnabledValidationFeatures[i] );
                        }

                        pContext->validationFeatures.pEnabledValidationFeatures = & pContext->validationFeatureEnables[0];

                        if ( pContext->validationFeatures.disabledValidationFeatureCount > __C_ENG_VULKAN_CORE_VALIDATION_FEATURE_DISABLE_MAX_COUNT ) {
                            pContext->validationFeatures.disabledValidationFeatureCount = __C_ENG_VULKAN_CORE_VALIDATION_FEATURE_DISABLE_MAX_COUNT;
                            pContext->error = ResultErrorConfigurationArraySizeSmall;
                        }

                        for ( cds :: uint32 i = 0U; i < pContext->validationFeatures.disabledValidationFeatureCount; ++ i ) {
                            pContext->validationFeatureDisables[i] = static_cast < VkValidationFeatureDisableEXT > ( pValidationFeatures->pDisabledValidationFeatures[i] );
                        }

                        pContext->validationFeatures.pDisabledValidationFeatures = & pContext->validationFeatureDisables[0];

                        break;
                    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALIDATION_FLAGS_AVAILABLE
                    case StructureTypeValidationFlags: {

                        auto pValidationFlags = reinterpret_cast < Type ( ValidationFlags ) const * > ( pCurrent );
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->validationFlags,
                                        pValidationFlags
                                )
                        );

                        if ( pValidationFlags->disabledValidationCheckCount > __C_ENG_VULKAN_CORE_VALIDATION_CHECK_MAX_COUNT ) {
                            pContext->validationFlags.disabledValidationCheckCount = __C_ENG_VULKAN_CORE_VALIDATION_CHECK_MAX_COUNT;
                            pContext->error = ResultErrorConfigurationArraySizeSmall;
                        }

                        for ( cds :: uint32 i = 0U; i < pContext->validationFlags.disabledValidationCheckCount; ++ i ) {
                            pContext->validationChecks[i] = static_cast <VkValidationCheckEXT > ( pValidationFlags->pDisabledValidationChecks[i] );
                        }

                        pContext->validationFlags.pDisabledValidationChecks = & pContext->validationChecks[0];

                        break;
                    }
#endif

                    default:
                        break;
                }

                pCurrentVk  = pCurrentVk->pNext != nullptr ? pCurrentVk->pNext : pCurrentVk;
                pCurrent    = pCurrent->pNext;
            }

            pCurrentVk->pNext = nullptr;

            return & pContext->instance;
        }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        auto fromVulkanFormat (
                Type ( LayerProperties )      * pDestination,
                VkLayerProperties       const * pSource
        ) noexcept -> Type ( LayerProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

            if ( pDestination == nullptr || pSource == nullptr ) {
                return nullptr;
            }

#endif

            (void) std :: memcpy ( & pDestination->layerName[0],    & pSource->layerName[0],    VK_MAX_EXTENSION_NAME_SIZE );
            (void) std :: memcpy ( & pDestination->description[0],  & pSource->description[0],  VK_MAX_DESCRIPTION_SIZE );
            pDestination->implementationVersion = pSource->implementationVersion;
            pDestination->specVersion           = uInt32ToInstanceVersion ( pSource->specVersion );

            return pDestination;
        }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
        auto fromVulkanFormat (
                Type ( ExtensionProperties )      * pDestination,
                VkExtensionProperties       const * pSource
        ) noexcept -> Type ( ExtensionProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

            if ( pDestination == nullptr || pSource == nullptr ) {
                return nullptr;
            }

#endif
            (void) std :: memcpy ( & pDestination->name[0], & pSource->extensionName[0], VK_MAX_EXTENSION_NAME_SIZE );
            pDestination->specVersion = pSource->specVersion;

            return pDestination;
        }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
        auto fromVulkanFormat (
                Type ( PerformanceCounter )         * pDestination,
                VkPerformanceCounterKHR       const * pSource
        ) noexcept -> Type ( PerformanceCounter ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

            if ( pDestination == nullptr || pSource == nullptr ) {
                return nullptr;
            }

#endif

            pDestination->structureType = StructureTypePerformanceCounter;
            pDestination->pNext         = nullptr;
            pDestination->unit          = static_cast < Type ( PerformanceCounterUnit ) > ( pSource->unit );
            pDestination->scope         = static_cast < Type ( PerformanceCounterScope ) > ( pSource->scope );
            pDestination->storage       = static_cast < Type ( PerformanceCounterStorage ) > ( pSource->storage );
            (void) std :: memcpy ( & pDestination->uuid[0], & pSource->uuid[0], sizeof ( pDestination->uuid[0] ) * VK_UUID_SIZE );

            return pDestination;
        }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
        auto fromVulkanFormat (
                Type ( PerformanceCounterDescription )         * pDestination,
                VkPerformanceCounterDescriptionKHR       const * pSource
        ) noexcept -> Type ( PerformanceCounterDescription ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

            if ( pDestination == nullptr || pSource == nullptr ) {
                return nullptr;
            }

#endif

            pDestination->structureType = StructureTypePerformanceCounterDescription;
            pDestination->pNext         = nullptr;
            pDestination->flags         = static_cast < Type ( PerformanceCounterDescriptionFlags ) > ( pSource->flags );
            (void) std :: memcpy ( & pDestination->name[0],         & pSource->name[0],         sizeof ( pDestination->name[0] ) * VK_MAX_DESCRIPTION_SIZE );
            (void) std :: memcpy ( & pDestination->category[0],     & pSource->category[0],     sizeof ( pDestination->category[0] ) * VK_MAX_DESCRIPTION_SIZE );
            (void) std :: memcpy ( & pDestination->description[0],  & pSource->description[0],  sizeof ( pDestination->description[0] ) * VK_MAX_DESCRIPTION_SIZE );

            return pDestination;
        }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

    static inline auto fromVulkanFormat (
            Type ( PhysicalDeviceGroupProperties )        * pDestination,
            VkPhysicalDeviceGroupProperties         const * pSource
    ) noexcept -> Type ( PhysicalDeviceGroupProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType         = vulkan :: StructureTypePhysicalDeviceGroupProperties;
        pDestination->pNext                 = nullptr;
        pDestination->physicalDeviceCount   = pSource->physicalDeviceCount;
        pDestination->subsetAllocation      = pSource->subsetAllocation;

        (void) std :: memcpy ( & pDestination->physicalDevices[0], & pSource->physicalDevices[0], sizeof ( pSource->physicalDevices[0] ) * VK_MAX_DEVICE_GROUP_SIZE ); // NOLINT(bugprone-sizeof-expression)

        return pDestination;
    }
#endif

}


#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif //C_ENG_VULKANAPICALLSCONVERSION_HPP

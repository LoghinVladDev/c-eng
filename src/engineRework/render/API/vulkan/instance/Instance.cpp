//
// Created by loghin on 28.12.2021.
//

#include "Instance.hpp"
#include <VulkanAPIExceptions.hpp>
#include <Logger.hpp>
#include <VulkanCore.hpp>
#include <Engine.hpp>
#include <Allocator.hpp>


using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)


static VKAPI_ATTR auto VKAPI_CALL debugMessengerCallback (
        VkDebugUtilsMessageSeverityFlagBitsEXT          messageSeverityFlags,
        VkDebugUtilsMessageTypeFlagsEXT                 messageTypeFlags,
        VkDebugUtilsMessengerCallbackDataEXT    const * pCallbackData,
        void                                          * pUserData
) noexcept -> VkBool32 {

    __C_ENG_TYPE ( LogLevel ) logLevel;

    if ( messageSeverityFlags == VkDebugUtilsMessageSeverityFlagBitsEXT :: VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT ) {
        logLevel = engine :: LogLevelInfo;
    }

    if ( messageSeverityFlags == VkDebugUtilsMessageSeverityFlagBitsEXT :: VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT ) {
        logLevel = engine :: LogLevelDebug;
    }

    if ( messageSeverityFlags == VkDebugUtilsMessageSeverityFlagBitsEXT :: VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT ) {
        logLevel = engine :: LogLevelWarning;
    }

    if ( messageSeverityFlags == VkDebugUtilsMessageSeverityFlagBitsEXT :: VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT ) {
        logLevel = engine :: LogLevelError;
    }

    auto typeFlagsToString = []( VkDebugUtilsMessageTypeFlagsEXT flags ) noexcept -> String {
        String asString = "";

        for ( uint32 f = 1U; true; f <<= 1 ) { // NOLINT(clion-misra-cpp2008-6-5-1)
            if ( ( f & flags ) != 0U ) {
                asString += engine :: vulkan :: toString ( static_cast < engine :: vulkan :: __C_ENG_TYPE ( DebugMessageTypeFlag ) > ( f ) ) + ", "_s;
            }

            if ( static_cast < engine :: vulkan :: __C_ENG_TYPE ( DebugMessageTypeFlag ) > ( f ) == engine :: vulkan :: DebugMessageTypeFlagMaxValue ) {
                break;
            }
        }

        return asString.removeSuffix(", ");
    };

    (void) __C_ENG_TYPE ( Logger ) :: instance().info (
            String :: f (
                    "[LAYER CALLBACK][type = %s] : %s",
                    typeFlagsToString ( messageTypeFlags ).cStr(),
                    pCallbackData->pMessage
            )
    );

    return VK_FALSE;
}

static inline auto populateDebugMessengerCreateInfo (
        vulkan :: __C_ENG_TYPE ( DebugMessengerCreateInfo )   * pCreateInfo,
        vulkan :: __C_ENG_TYPE ( DebugMessageSeverityFlags )    messageSeverityFlags,
        vulkan :: __C_ENG_TYPE ( DebugMessageTypeFlags )        messageTypeFlags,
        vulkan :: __C_ENG_TYPE ( DebugMessengerCallback )       callback,
        void                                            const * pNext
) noexcept -> void {

    if ( pCreateInfo == nullptr ) {
        return;
    }

    * pCreateInfo = {
            .structureType          = engine :: vulkan :: StructureTypeDebugUtilsMessengerCreateInfo,
            .pNext                  = pNext,
            .flags                  = 0U,
            .messageSeverityFlags   = messageSeverityFlags,
            .messageTypeFlags       = messageTypeFlags,
            .callback               = callback,
            .pCallbackUserData      = nullptr
    };
}

static inline auto populateApplicationInfo (
        vulkan :: __C_ENG_TYPE ( ApplicationInfo )    * pApplicationInfo,
        StringLiteral                                   applicationName,
        vulkan :: __C_ENG_TYPE ( Version )              applicationVersion,
        StringLiteral                                   engineName,
        vulkan :: __C_ENG_TYPE ( Version )              engineVersion,
        vulkan :: __C_ENG_TYPE ( Version )              vulkanAPIVersion
) noexcept -> void {

    if ( pApplicationInfo == nullptr ) {
        return;
    }

    * pApplicationInfo = {
            .structureType  = engine :: vulkan :: StructureTypeApplicationInfo,
            .pNext          = nullptr,
            .name           = applicationName,
            .version        = applicationVersion,
            .engineName     = engineName,
            .engineVersion  = engineVersion,
            .apiVersion     = vulkanAPIVersion
    };
}

static inline auto populateInstanceCreateInfo (
        vulkan :: __C_ENG_TYPE ( InstanceCreateInfo )             * pCreateInfo,
        vulkan :: __C_ENG_TYPE ( ApplicationInfo )                * pApplicationInfo,
        vulkan :: __C_ENG_TYPE ( LayerHandler ) :: LayerNames     * pEnabledLayerNames,
        vulkan :: __C_ENG_TYPE ( LayerHandler ) :: ExtensionNames * pEnabledExtensionNames,
        void                                                const * pNext
) noexcept -> void {

    if ( pCreateInfo == nullptr ) {
        return;
    }

    * pCreateInfo = {
            .structureType          = engine :: vulkan :: StructureTypeInstanceCreateInfo,
            .pNext                  = pNext,
            .flags                  = 0U,
            .pApplicationInfo       = pApplicationInfo,
            .enabledLayerCount      = pEnabledLayerNames->count,
            .pEnabledLayerNames     = pEnabledLayerNames->names,
            .enabledExtensionCount  = pEnabledExtensionNames->count,
            .pEnabledExtensionNames = pEnabledExtensionNames->names
    };
}

static inline auto populateValidationFeatures (
        vulkan :: __C_ENG_TYPE ( ValidationFeatures )                                 * pValidationFeatures,
        vulkan :: __C_ENG_TYPE ( LayerHandler ) :: ValidationEnabledFeatures    const * pEnabledFeatures,
        vulkan :: __C_ENG_TYPE ( LayerHandler ) :: ValidationDisabledFeatures   const * pDisabledFeatures,
        void                                                                    const * pNext
) noexcept -> void {

    if ( pValidationFeatures == nullptr ) {
        return;
    }

    * pValidationFeatures = {
            .structureType                  = engine :: vulkan :: StructureTypeValidationFeatures,
            .pNext                          = pNext,
            .enabledValidationFeatureCount  = pEnabledFeatures->count,
            .pEnabledValidationFeatures     = pEnabledFeatures->pFeatures,
            .disabledValidationFeatureCount = pDisabledFeatures->count,
            .pDisabledValidationFeatures    = pDisabledFeatures->pFeatures
    };
}

#define C_ENG_MAP_START     CLASS ( Instance, EXTERNAL_PARENT ( Object ) )
#include <ObjectMapping.hpp>

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

auto vulkan :: Self :: supportedVulkanVersion () noexcept (false) -> __C_ENG_TYPE ( Version ) {
    uint32                      rawInstanceVersion;

    auto result = enumerateInstanceVersion( & rawInstanceVersion );
    if ( result != ResultSuccess ) {
        __C_ENG_LOG_AND_THROW_DETAILED_API_CALL_EXCEPTION(warning, "enumerateInstanceVersion", result);
    }

    return uInt32ToInstanceVersion ( rawInstanceVersion );
}

#endif

auto vulkan :: Self :: init () noexcept (false) -> Self & {
    if ( compare ( this->version(), nullVersion ) == CompareResultEquals ) {

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

        this->_version = this->supportedVulkanVersion();

#elif __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

        this->_version = __C_ENG_TYPE ( Version ) {
            .variant    = static_cast < uint8 > ( 0 ),
            .major      = static_cast < uint8 > ( 1 ),
            .minor      = static_cast < uint8 > ( 0 ),
            .patch      = static_cast < uint8 > ( 0 )
        }

#endif

        (void) __C_ENG_TYPE ( Logger ) :: instance ().warning (
                String :: f (
                        "No Vulkan Version chosen upon instance creation. Choosing highest available : %s",
                        versionReadableFormat ( this->_version ).cStr()
                )
        );
    }

    (void) this->_layerHandler.init();

    auto layers = this->_layerHandler.enabledLayerNames();
    auto extensions = this->_layerHandler.enabledExtensionNames();

    __C_ENG_TYPE ( DebugMessengerCreateInfo )   debugMessengerCreateInfo {};
    __C_ENG_TYPE ( ApplicationInfo )            applicationInfo {};
    __C_ENG_TYPE ( InstanceCreateInfo )         instanceCreateInfo {};
    __C_ENG_TYPE ( ValidationFeatures )         validationFeatures {};

    __C_ENG_TYPE ( ValidationFeatureEnable )    enabledValidationFeatures   [ __C_ENG_VULKAN_CORE_VALIDATION_FEATURE_ENABLE_MAX_COUNT ];
    __C_ENG_TYPE ( ValidationFeatureDisable )   disabledValidationFeatures  [ __C_ENG_VULKAN_CORE_VALIDATION_FEATURE_DISABLE_MAX_COUNT ];

    __C_ENG_TYPE ( LayerHandler ) :: ValidationEnabledFeatures  enabledFeatures {};
    __C_ENG_TYPE ( LayerHandler ) :: ValidationDisabledFeatures disabledFeatures {};

    void                                const * pNext = nullptr;

    if ( this->layerHandler().debugLayerEnabled() ) {

        for ( uint32 i = 0U; i < this->enabledValidationFeatures().size(); ++ i ) {
            enabledValidationFeatures[i] = this->enabledValidationFeatures()[static_cast < sint32 > ( i )];
        }

        enabledFeatures = {
                .pFeatures  = enabledValidationFeatures,
                .count      = static_cast < cds :: uint32 > ( this->enabledValidationFeatures().size() )
        };

        for ( uint32 i = 0U; i < this->disabledValidationFeatures().size(); ++ i ) {
            disabledValidationFeatures[i] = this->disabledValidationFeatures()[static_cast < sint32 > ( i )];
        }

        disabledFeatures = {
                .pFeatures  = disabledValidationFeatures,
                .count      = static_cast < cds :: uint32 > ( this->disabledValidationFeatures().size() )
        };

        pNext = & debugMessengerCreateInfo;

        populateDebugMessengerCreateInfo(
                & debugMessengerCreateInfo,
                this->debugMessageSeverityFlags(),
                this->debugMessageTypeFlags(),
                & debugMessengerCallback,
                & validationFeatures
        );

        populateValidationFeatures (
                & validationFeatures,
                & enabledFeatures,
                & disabledFeatures,
                nullptr
        );
    }

    populateApplicationInfo (
            & applicationInfo,
            "Engine Sample Application",
            nullVersion,
            "c-eng", {
                .variant    = __C_ENG_TYPE ( Engine ) :: versionVariant,
                .major      = __C_ENG_TYPE ( Engine ) :: versionMajor,
                .minor      = __C_ENG_TYPE ( Engine ) :: versionMinor,
                .patch      = __C_ENG_TYPE ( Engine ) :: versionPatch
            }, this->version()
    );

    populateInstanceCreateInfo (
            & instanceCreateInfo,
            & applicationInfo,
            & layers,
            & extensions,
            pNext
    );

    auto result = vulkan :: createInstance (
            & instanceCreateInfo,
            __C_ENG_TYPE ( Allocator ) :: instance().callbacks(),
            & this->_handle
    );

    if ( result != ResultSuccess ) {
        __C_ENG_LOG_AND_THROW_DETAILED_API_CALL_EXCEPTION ( critical, "createInstance", result );
    }

    (void) __C_ENG_TYPE ( Logger ) :: instance().info (
            "Vulkan instance with handle " +
            :: toString ( this->handle() ) +
            " created"
    );

    if ( this->layerHandler().debugLayerEnabled() ) {

        result = vulkan::createDebugMessenger(
                this->handle(),
                & debugMessengerCreateInfo,
                __C_ENG_TYPE (Allocator)::instance().callbacks(),
                & this->_debugMessengerHandle
        );
    }

    return * this;
}

auto vulkan :: Self :: clear () noexcept (false) -> Self & {
    if ( this->_debugMessengerHandle != nullptr ) {

        auto result = vulkan :: destroyDebugMessenger (
                this->handle(),
                this->debugMessengerHandle(),
                __C_ENG_TYPE ( Allocator ) :: instance().callbacks()
        );

        if ( result != ResultSuccess ) {
            __C_ENG_LOG_DETAILED_API_CALL_EXCEPTION (warning, "destroyDebugMessenger", result);
        }

        this->_debugMessengerHandle = nullptr;
    }

    if ( this->_handle != nullptr ) {

        auto result = vulkan :: destroyInstance (
                this->handle(),
                __C_ENG_TYPE ( Allocator ) :: instance().callbacks()
        );

        if ( result != ResultSuccess ) {
            __C_ENG_LOG_DETAILED_API_CALL_EXCEPTION (warning, "destroyInstance", result);
        }

        this->_handle = nullptr;
    }

    return * this;
}

vulkan :: Self :: Destructor () noexcept {
    (void) this->clear();
}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     NESTED_CLASS ( Builder, ENGINE_TYPE ( Instance ), PARENT ( Object ) )
#include <ObjectMapping.hpp>

auto vulkan :: Self :: build () noexcept -> Nester {
    Nester builtObject;

    builtObject._version                    = this->_version;
    builtObject._debugMessageSeverityFlags  = this->_debugMessageSeverityFlags;
    builtObject._debugMessageTypeFlags      = this->_debugMessageTypeFlags;
    builtObject._enabledValidationFeatures  = std :: move ( this->_enabledValidationFeatures );
    builtObject._disabledValidationFeatures = std :: move ( this->_disabledValidationFeatures );

    return builtObject;
}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
//
// Created by loghin on 28.12.2021.
//

#ifndef __C_ENG_INSTANCE_HPP__
#define __C_ENG_INSTANCE_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#include <Preprocess.hpp>
#include <VulkanRenderObject.hpp>

#include <VulkanCore.hpp>
#include <LayerHandler.hpp>
#include <CDS/Array>


#define C_ENG_MAP_START     CLASS ( Instance, ENGINE_PARENT ( VulkanRenderObject ) )
#include <ObjectMapping.hpp>

namespace engine { // NOLINT(modernize-concat-nested-namespaces)

    namespace vulkan {

        Class {

#ifndef NDEBUG

            Const ( ENGINE_TYPE ( DebugMessageSeverityFlags ),   defaultMessageSeverityFlags,    VALUE (
                    DebugMessageSeverityFlagVerbose |
                    DebugMessageSeverityFlagInfo |
                    DebugMessageSeverityFlagWarning |
                    DebugMessageSeverityFlagError
            ))

            Const ( ENGINE_TYPE ( DebugMessageTypeFlags ),      defaultMessageTypeFlags,    VALUE (
                    DebugMessageTypeFlagGeneral |
                    DebugMessageTypeFlagValidation |
                    DebugMessageTypeFlagPerformance
            ))

            Const ( TYPE ( cds :: Array < Type ( ValidationFeatureEnable ) > ),     defaultEnabledValidationFeatures,   VALUE ({
                    ValidationFeatureEnableGpuAssisted,
                    ValidationFeatureEnableGpuAssistedReserveBindingSlot,
                    ValidationFeatureEnableBestPractices,
//                    ValidationFeatureEnableDebugPrintf, https://vulkan.lunarg.com/doc/view/1.2.189.0/linux/1.2-extensions/vkspec.html#VUID-VkValidationFeaturesEXT-pEnabledValidationFeatures-02968
                    ValidationFeatureEnableSynchronizationValidation
            }))

            Const ( TYPE ( cds :: Array < __C_ENG_TYPE ( ValidationFeatureDisable ) > ),    defaultDisabledValidationFeatures, VALUE ({}) )

#else

            Const ( ENGINE_TYPE ( DebugMessageSeverityFlags ),   defaultMessageSeverityFlags,    VALUE ( 0U ) )
            Const ( ENGINE_TYPE ( DebugMessageTypeFlags ),      defaultMessageTypeFlags,    VALUE ( 0U ) )
            Const ( TYPE ( cds :: Array < Type ( ValidationFeatureEnable ) > ),     defaultEnabledValidationFeatures,   VALUE ({}))
            Const ( TYPE ( cds :: Array < __C_ENG_TYPE ( ValidationFeatureDisable ) > ),    defaultDisabledValidationFeatures, VALUE ({ ValidationFeatureDisableAll }) )

#endif

            Field ( ENGINE_TYPE ( Version ),                                                version,                    DEFAULT_VALUE ( versionConstants :: nullVersion ),  GET_DEFAULT, SET_NONE )
            Field ( ENGINE_TYPE ( LayerHandler ),                                           layerHandler,               NO_INIT,                                            GET_DEFAULT, SET_NONE )
            Field ( ENGINE_TYPE ( DebugMessageSeverityFlags ),                              debugMessageSeverityFlags,  DEFAULT_VALUE ( defaultMessageSeverityFlags ),      GET_DEFAULT, SET_NONE )
            Field ( ENGINE_TYPE ( DebugMessageTypeFlags ),                                  debugMessageTypeFlags,      DEFAULT_VALUE ( defaultMessageTypeFlags ),          GET_DEFAULT, SET_NONE )

            Field ( ENGINE_TYPE ( InstanceHandle ),                                         handle,                     DEFAULT_VALUE ( nullptr ),                          GET_DEFAULT, SET_NONE )
            Field ( ENGINE_TYPE ( DebugMessengerHandle ),                                   debugMessengerHandle,       DEFAULT_VALUE ( nullptr ),                          GET_DEFAULT, SET_NONE )

            Field ( TYPE ( cds :: Array < __C_ENG_TYPE ( ValidationFeatureEnable ) > ),     enabledValidationFeatures,  NO_INIT,                                            GET_DEFAULT, SET_NONE )
            Field ( TYPE ( cds :: Array < __C_ENG_TYPE ( ValidationFeatureDisable ) > ),    disabledValidationFeatures, NO_INIT,                                            GET_DEFAULT, SET_NONE )

        public:
            class Builder;

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

            static auto supportedVulkanVersion () noexcept (false) -> __C_ENG_TYPE ( Version );

#endif

            auto init () noexcept (false) -> Self &;
            auto clear () noexcept (false) -> Self & override;
            Constructor () noexcept = default;
            Destructor () noexcept override;

        };

    }

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     NESTED_CLASS ( Builder, ENGINE_TYPE ( Instance ), PARENT ( cds :: Object ) )
#include <ObjectMapping.hpp>

namespace engine { // NOLINT(modernize-concat-nested-namespaces)

    namespace vulkan {

        Class {
            Field ( ENGINE_TYPE ( Version ),                                                version,                    DEFAULT_VALUE ( versionConstants :: nullVersion ),      GET_NONE, SET_INLINE ( setVersion ) )
            Field ( ENGINE_TYPE ( DebugMessageSeverityFlags ),                              debugMessageSeverityFlags,  DEFAULT_VALUE ( defaultMessageSeverityFlags ),          GET_NONE, SET_INLINE ( setDebugMessageSeverityFlags ) )
            Field ( ENGINE_TYPE ( DebugMessageTypeFlags ),                                  debugMessageTypeFlags,      DEFAULT_VALUE ( defaultMessageTypeFlags ),              GET_NONE, SET_INLINE ( setDebugMessageTypeFlags ) )

            Field ( TYPE ( cds :: Array < __C_ENG_TYPE ( ValidationFeatureEnable ) > ),     enabledValidationFeatures,  DEFAULT_VALUE ( defaultEnabledValidationFeatures ),     GET_NONE, SET_INLINE ( setEnabledValidationFeatures ) )
            Field ( TYPE ( cds :: Array < __C_ENG_TYPE ( ValidationFeatureDisable ) > ),    disabledValidationFeatures, DEFAULT_VALUE ( defaultDisabledValidationFeatures ),    GET_NONE, SET_INLINE ( setDisabledValidationFeatures ) )

        public:
            __C_ENG_NO_DISCARD auto build () noexcept -> Nester;
        };

    }

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif // __C_ENG_INSTANCE_HPP__

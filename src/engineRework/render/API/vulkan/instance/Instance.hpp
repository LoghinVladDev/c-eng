//
// Created by loghin on 28.12.2021.
//

#ifndef __C_ENG_INSTANCE_HPP
#define __C_ENG_INSTANCE_HPP

#include <Preprocess.hpp>
#include <CDS/Object>

#include <VulkanCore.hpp>
#include <LayerHandler.hpp>
#include <CDS/Array>


#define C_ENG_MAP_START     CLASS ( Instance, PARENT ( cds :: Object ) )
#include <ObjectMapping.hpp>

namespace engine { // NOLINT(modernize-concat-nested-namespaces)

    namespace vulkan {

        Class {
            Const ( ENGINE_TYPE ( DebugMessageSeverityFlags ),  defaultMessageSeverityFlags, VALUE ( // NOLINT(clion-misra-cpp2008-4-5-2)

#ifdef NDEBUG

                    0U

#else

                    DebugMessageSeverityFlagVerbose |
                    DebugMessageSeverityFlagInfo    |
                    DebugMessageSeverityFlagWarning |
                    DebugMessageSeverityFlagError

#endif

            ))

            Const ( ENGINE_TYPE ( DebugMessageTypeFlags ),      defaultMessageTypeFlags,    VALUE ( // NOLINT(clion-misra-cpp2008-4-5-2)

#ifdef NDEBUG

                    0U

#else

                    DebugMessageTypeFlagGeneral     |
                    DebugMessageTypeFlagValidation  |
                    DebugMessageTypeFlagPerformance

#endif

            ))

            Const ( TYPE ( cds :: Array < __C_ENG_TYPE ( ValidationFeatureEnable ) > ),     defaultEnabledValidationFeatures, VALUE ({

#ifdef NDEBUG

#else

                ValidationFeatureEnableGpuAssisted,
                ValidationFeatureEnableGpuAssistedReserveBindingSlot,
                ValidationFeatureEnableBestPractices,
                ValidationFeatureEnableDebugPrintf,
                ValidationFeatureEnableSynchronizationValidation

#endif

            }))

            Const ( TYPE ( cds :: Array < __C_ENG_TYPE ( ValidationFeatureDisable ) > ),    defaultDisabledValidationFeatures, VALUE ({

#ifndef NDEBUG

#else

                ValidationFeatureDisableAll

#endif

            }))

            Field ( ENGINE_TYPE ( Version ),                                                version,                    DEFAULT_VALUE ( nullVersion ),                  GET_DEFAULT, SET_NONE )
            Field ( ENGINE_TYPE ( LayerHandler ),                                           layerHandler,               NO_INIT,                                        GET_DEFAULT, SET_NONE )
            Field ( ENGINE_TYPE ( DebugMessageSeverityFlags ),                              debugMessageSeverityFlags,  DEFAULT_VALUE ( defaultMessageSeverityFlags ),  GET_DEFAULT, SET_NONE )
            Field ( ENGINE_TYPE ( DebugMessageTypeFlags ),                                  debugMessageTypeFlags,      DEFAULT_VALUE ( defaultMessageTypeFlags ),      GET_DEFAULT, SET_NONE )

            Field ( ENGINE_TYPE ( InstanceHandle ),                                         handle,                     DEFAULT_VALUE ( nullptr ),                      GET_DEFAULT, SET_NONE )

            Field ( TYPE ( cds :: Array < __C_ENG_TYPE ( ValidationFeatureEnable ) > ),     enabledValidationFeatures,  NO_INIT,                                        GET_DEFAULT, SET_NONE )
            Field ( TYPE ( cds :: Array < __C_ENG_TYPE ( ValidationFeatureDisable ) > ),    disabledValidationFeatures, NO_INIT,                                        GET_DEFAULT, SET_NONE )

        public:
            class Builder;

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

            static auto supportedVulkanVersion () noexcept (false) -> __C_ENG_TYPE ( Version );

#endif

            auto init () noexcept (false) -> Self &;
            auto clean () noexcept (false) -> Self &;
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
            Field ( ENGINE_TYPE ( Version ),                                                version,                    DEFAULT_VALUE ( nullVersion ),                          GET_NONE, SET_INLINE ( setVersion ) )
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


#endif // __C_ENG_INSTANCE_HPP

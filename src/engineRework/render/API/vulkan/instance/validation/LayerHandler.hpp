//
// Created by loghin on 30.12.2021.
//

#ifndef C_ENG_LAYERHANDLER_HPP
#define C_ENG_LAYERHANDLER_HPP

#include <Preprocess.hpp>
#include <CDS/Array>
#include <VulkanCore.hpp>


#define C_ENG_MAP_START     CLASS ( LayerHandler, PARENT ( cds :: Object ) )
#include <ObjectMapping.hpp>

namespace engine { // NOLINT(modernize-concat-nested-namespaces)
    namespace vulkan {

        Class {
            struct LayerExtension {
                __C_ENG_TYPE ( ExtensionProperties )    properties;
                bool                                    enabled;
            };

            struct Layer {
                __C_ENG_TYPE ( LayerProperties )    properties;
                bool                                enabled;

                LayerExtension                    * pExtensions;
                cds :: uint32                       extensionCount;
            };

            Const ( PRIMITIVE_TYPE ( cds :: StringLiteral ),    validationLayerName,                VALUE ( "VK_LAYER_KHRONOS_validation" ) )
            Const ( PRIMITIVE_TYPE ( cds :: StringLiteral ),    validationRequiredExtensionName,    VALUE ( "VK_EXT_debug_utils" ) )

            Field ( TYPE ( cds :: Array < Layer > ),            layers,                 NO_INIT,                    GET_DEFAULT,    SET_NONE )

            Field ( PRIMITIVE_TYPE ( cds :: StringLiteral * ),  enabledLayerNames,      DEFAULT_VALUE ( nullptr ),  GET_NONE,       SET_NONE )
            Field ( PRIMITIVE_TYPE ( cds :: uint32 ),           enabledLayerCount,      DEFAULT_VALUE ( 0 ),        GET_NONE,       SET_NONE )

            Field ( PRIMITIVE_TYPE ( cds :: StringLiteral * ),  enabledExtensionNames,  DEFAULT_VALUE ( nullptr ),  GET_NONE,       SET_NONE )
            Field ( PRIMITIVE_TYPE ( cds :: uint32 ),           enabledExtensionCount,  DEFAULT_VALUE ( 0 ),        GET_NONE,       SET_NONE )

            Field ( PRIMITIVE_TYPE ( bool ),                    debugLayerEnabled,      DEFAULT_VALUE ( false ),    GET_DEFAULT,    SET_NONE )

        public:
            struct LayerNames {
                cds :: StringLiteral  * names;
                cds :: uint32           count;
            };

            struct ExtensionNames {
                cds :: StringLiteral  * names;
                cds :: uint32           count;
            };

            struct ValidationEnabledFeatures {
                __C_ENG_TYPE ( ValidationFeatureEnable )    const * pFeatures;
                cds :: uint32                                       count;
            };

            struct ValidationDisabledFeatures {
                __C_ENG_TYPE ( ValidationFeatureDisable )   const * pFeatures;
                cds :: uint32                                       count;
            };

            auto init () noexcept (false) -> Self &;
            auto refreshLayers () noexcept (false) -> Self &;
            auto enabledLayerNames () noexcept -> LayerNames;
            auto enabledExtensionNames () noexcept -> ExtensionNames;

            Destructor () noexcept;
        };

    }
}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //C_ENG_LAYERHANDLER_HPP

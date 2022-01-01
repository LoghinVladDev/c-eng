//
// Created by loghin on 30.12.2021.
//

#include "LayerHandler.hpp"
#include <Settings.hpp>
#include <Logger.hpp>
#include <VulkanCore.hpp>
#include <VulkanAPIExceptions.hpp>
#include <Window.hpp>


using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)


#define C_ENG_MAP_START     CLASS ( LayerHandler, PARENT ( cds :: Object ) )
#include <ObjectMapping.hpp>

auto vulkan :: Self :: refreshLayers() noexcept (false) -> Self & {
    __C_ENG_TYPE ( LayerProperties ) *  pLayerProperties            = nullptr;
    cds :: StringLiteral *              newEnabledExtensionNames    = nullptr;
    cds :: StringLiteral *              newEnabledLayerNames        = nullptr;

    try {
        uint32                              layerPropertiesCount;
        uint32                              newEnabledLayerCount = 0U;
        uint32                              newEnabledExtensionCount = 0U;
        bool                                newDebugLayerEnabled = false;

        Array < Layer >                     newLayers = this->layers();

        auto result = vulkan :: enumerateInstanceLayerProperties ( & layerPropertiesCount );
        if ( result != ResultSuccess ) {
            __C_ENG_LOG_AND_THROW_DETAILED_API_CALL_EXCEPTION(warning, "enumerateInstanceLayerProperties", result);
        }

        pLayerProperties = new __C_ENG_TYPE ( LayerProperties ) [ layerPropertiesCount ];
        result = vulkan ::enumerateInstanceLayerProperties ( & layerPropertiesCount, pLayerProperties );
        if ( result != ResultSuccess ) {
            __C_ENG_LOG_AND_THROW_DETAILED_API_CALL_EXCEPTION(warning, "enumerateInstanceLayerProperties", result);
        }

        newLayers.resize ( layerPropertiesCount );
        for ( sint32 layerIndex = 0; layerIndex < static_cast < sint32 > ( layerPropertiesCount ); ++ layerIndex ) {

            (void) std :: memcpy (
                    & newLayers[layerIndex].properties,
                    & pLayerProperties[layerIndex],
                    sizeof ( __C_ENG_TYPE (LayerProperties ) )
            );

            newLayers[layerIndex].enabled = __C_ENG_TYPE (Settings ) :: instance().get (
                    ("Validation_Layer_"_s + newLayers[layerIndex].properties.layerName + "_enabled").cStr()
            );

            if ( newLayers[layerIndex].enabled ) {
                ++ newEnabledLayerCount;
            }

            newLayers[layerIndex].extensionCount = 0U;
            newLayers[layerIndex].pExtensions = nullptr;

            __C_ENG_TYPE ( ExtensionProperties )  * pLayerExtensionProperties = nullptr;

            try {
                uint32              layerExtensionPropertiesCount   = 0U;
                LayerExtension    * pNewExtensions;
                uint32              newExtensionCount;

                result = vulkan :: enumerateInstanceExtensionProperties (
                            newLayers[layerIndex].properties.layerName,
                            & layerExtensionPropertiesCount
                    );

                if ( result != ResultSuccess ) {
                    __C_ENG_LOG_AND_THROW_DETAILED_API_CALL_EXCEPTION ( warning, "enumerateInstanceExtensionProperties", result );
                }

                pLayerExtensionProperties = new __C_ENG_TYPE (ExtensionProperties) [ layerExtensionPropertiesCount ];

                result = vulkan :: enumerateInstanceExtensionProperties (
                        newLayers[layerIndex].properties.layerName,
                        & layerExtensionPropertiesCount,
                        pLayerExtensionProperties
                );

                if ( result != ResultSuccess ) {
                    __C_ENG_LOG_AND_THROW_DETAILED_API_CALL_EXCEPTION ( warning, "enumerateInstanceExtensionProperties", result );
                }

                newExtensionCount   = layerExtensionPropertiesCount;
                pNewExtensions      = new LayerExtension [ layerExtensionPropertiesCount ];

                for ( uint32 extensionIndex = 0U; extensionIndex < layerExtensionPropertiesCount; ++ extensionIndex ) {
                    (void) std :: memcpy (
                            & pNewExtensions[extensionIndex].properties,
                            & pLayerExtensionProperties[ extensionIndex ],
                            sizeof ( __C_ENG_TYPE ( ExtensionProperties ) )
                    );

                    pNewExtensions[extensionIndex].enabled =
                            __C_ENG_TYPE ( Settings ) :: instance().get (
                                    (
                                            "Validation_Layer_"_s + newLayers[layerIndex].properties.layerName +
                                            "_Extension_" + pNewExtensions[ extensionIndex ].properties.name +
                                            "_enabled"
                                    ).cStr()
                            );

                    if (
                            newLayers[layerIndex].enabled &&
                            std :: strcmp ( newLayers[layerIndex].properties.layerName, validationLayerName ) == 0 && // NOLINT(clion-misra-cpp2008-5-2-12)
                            std :: strcmp ( pNewExtensions[extensionIndex].properties.name, validationRequiredExtensionName ) == 0 // NOLINT(clion-misra-cpp2008-5-2-12)
                    ) {
                        newDebugLayerEnabled                    = true;

                        if ( ! pNewExtensions[extensionIndex].enabled ) {

                            pNewExtensions[extensionIndex].enabled  = true;
                            (void) __C_ENG_TYPE ( Settings ) :: instance().set (
                                        (
                                                "Validation_Layer_"_s + newLayers[layerIndex].properties.layerName +
                                                "_Extension_" + pNewExtensions[ extensionIndex ].properties.name +
                                                "_enabled"
                                        ).cStr(),
                                        1U
                            );
                        }
                    }

                    if ( pNewExtensions[extensionIndex].enabled ) {
                        ++ newEnabledExtensionCount;
                    }
                }

                delete [] pLayerExtensionProperties;

                newLayers[layerIndex].pExtensions = pNewExtensions;
                newLayers[layerIndex].extensionCount = newExtensionCount;

            } catch ( ... ) {
                delete [] pLayerExtensionProperties;
                throw;
            }
        }

        delete [] pLayerProperties;


        this->_layers = std :: move ( newLayers );

        auto windowRequiredExtensions = __C_ENG_TYPE ( Window ) :: vulkanRequiredExtensionNames();

        newEnabledLayerNames = new cds :: StringLiteral [ newEnabledLayerCount ];
        newEnabledExtensionNames = new StringLiteral [ newEnabledExtensionCount + windowRequiredExtensions.count ];
        newEnabledExtensionCount = 0U;

        for (sint32 layerIndex = 0, j = 0; layerIndex < static_cast < sint32 > ( layerPropertiesCount ); ++ layerIndex ) { // NOLINT(clion-misra-cpp2008-8-0-1)
            if ( this->layers()[layerIndex].enabled ) {
                newEnabledLayerNames[j++] = this->layers()[layerIndex].properties.layerName;
            }

            for ( uint32 extensionIndex = 0U; extensionIndex < this->layers()[layerIndex].extensionCount; ++ extensionIndex ) { // NOLINT(clion-misra-cpp2008-8-0-1)
                if ( this->layers()[layerIndex].pExtensions[extensionIndex].enabled ) {
                    newEnabledExtensionNames[newEnabledExtensionCount ++] = this->layers()[layerIndex].pExtensions[extensionIndex].properties.name;
                }
            }
        }

        for ( uint32 reqExtIndex = 0U; reqExtIndex < windowRequiredExtensions.count; ++ reqExtIndex ) {

            bool toAdd = true;
            for (uint32 i = 0U; i < newEnabledExtensionCount; ++i) {
                if ( std :: strcmp ( newEnabledExtensionNames[i], windowRequiredExtensions.names[reqExtIndex] ) == 0 ) {
                    toAdd = false;
                    break;
                }
            }

            if ( toAdd ) {
                newEnabledExtensionNames[ newEnabledExtensionCount ++ ] = windowRequiredExtensions.names[reqExtIndex];
            }
        }

        delete[] cds :: exchange ( this->_enabledLayerNames,        newEnabledLayerNames );
        delete[] cds :: exchange ( this->_enabledExtensionNames,    newEnabledExtensionNames );
        this->_enabledLayerCount        = newEnabledLayerCount;
        this->_enabledExtensionCount    = newEnabledExtensionCount;
        this->_debugLayerEnabled        = newDebugLayerEnabled;

    } catch (...) {
        delete [] pLayerProperties;
        throw;
    }

    return * this;
}

auto vulkan :: Self :: init () noexcept (false) -> Self & {
    return this->refreshLayers();
}

auto vulkan :: Self :: enabledLayerNames() noexcept -> LayerNames {
    return { this->_enabledLayerNames, this->_enabledLayerCount };
}

auto vulkan :: Self :: enabledExtensionNames() noexcept -> ExtensionNames {
    return { this->_enabledExtensionNames, this->_enabledExtensionCount };
}

vulkan :: Self :: Destructor () noexcept {
    for ( auto & l : this->layers() ) {
        delete[] l.pExtensions;
    }

    delete [] this->_enabledLayerNames;
    delete [] this->_enabledExtensionNames;
}
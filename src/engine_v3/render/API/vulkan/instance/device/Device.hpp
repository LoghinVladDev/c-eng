//
// Created by loghin on 30.01.2022.
//

#ifndef __C_ENG_DEVICE_HPP__
#define __C_ENG_DEVICE_HPP__

#include <Preprocess.hpp>
#include <VulkanRenderObject.hpp>
#include <VulkanCore.hpp>
#include <CDS/HashSet>
#include <CDS/Pair>
#include <CDS/Array>
#include <CDS/Path>
#include <Queue.hpp>
#include <ValidationCache.hpp>


#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START     CLASS ( Device, ENGINE_PARENT ( VulkanRenderObject ) )
#include <ObjectMapping.hpp>

namespace engine { // NOLINT(modernize-concat-nested-namespaces)
    namespace vulkan {

        __C_ENG_PRE_DECLARE_CLASS ( Instance );
        __C_ENG_PRE_DECLARE_CLASS ( PhysicalDevice );
        __C_ENG_PRE_DECLARE_CLASS ( PhysicalDeviceGroup );

        Class {
            Field ( ENGINE_PRIMITIVE_TYPE ( DeviceHandle ),             handle,                 DEFAULT_VALUE ( nullptr ),  GET_DEFAULT,    SET_NONE )

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE
            Field ( ENGINE_PRIMITIVE_TYPE ( SurfaceHandle ),            surfaceHandle,          DEFAULT_VALUE ( nullptr ),  GET_DEFAULT,    SET_NONE )
#endif

            Field ( ENGINE_TYPE ( PhysicalDevice const * ),             physicalDevice,         DEFAULT_VALUE ( nullptr ),  GET_DEFAULT,    SET_NONE )
            Field ( TYPE ( cds :: Array < Type ( Queue ) > ),           queues,                 NO_INIT,                    GET_DEFAULT,    SET_NONE )
            Field ( ENGINE_TYPE ( ValidationCache ),                    validationCache,        NO_INIT,                    GET_DEFAULT,    SET_NONE )

        public:
            class Builder;

            Constructor () noexcept = default;
            Constructor ( Self && ) noexcept;

            auto operator = ( Self const & ) noexcept -> Self & = delete;
            auto operator = ( Self && ) noexcept -> Self &;

            auto clear () noexcept (false) -> Self & override;
            Destructor () noexcept override;
        };

    }
}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     NESTED_CLASS ( Builder, ENGINE_TYPE ( Device ), PARENT ( cds :: Object ) )
#include <ObjectMapping.hpp>

namespace engine { // NOLINT(modernize-concat-nested-namespaces)
    namespace vulkan {

        Class {
            Field ( ENGINE_PRIMITIVE_TYPE ( PhysicalDevice const * ),                   physicalDevice,                 DEFAULT_VALUE ( nullptr ),      GET_NONE,   SET_INLINE ( fromDevice ) )
            Field ( ENGINE_PRIMITIVE_TYPE ( PhysicalDeviceGroup const * ),              physicalDeviceGroup,            DEFAULT_VALUE ( nullptr ),      GET_NONE,   SET_INLINE ( fromDeviceGroup ) )

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE
            Field ( ENGINE_PRIMITIVE_TYPE ( SurfaceHandle ),                            surfaceHandle,                  DEFAULT_VALUE ( nullptr ),      GET_NONE,   SET_INLINE ( toSurface ) )
#endif

            Field ( PRIMITIVE_TYPE ( bool ),                                            preferExclusiveOperations,      DEFAULT_VALUE ( false ),        GET_NONE,   SET_INLINE ( setPreferExclusiveOperations ) )
            Field ( PRIMITIVE_TYPE ( float ),                                           maxQueuePriority,               DEFAULT_VALUE ( 1.0f ),         GET_NONE,   SET_INLINE ( setMaxQueuePriority ) )
            Field ( PRIMITIVE_TYPE ( float ),                                           minQueuePriority,               DEFAULT_VALUE ( 1.0f ),         GET_NONE,   SET_INLINE ( setMinQueuePriority ) )

            Field ( PRIMITIVE_TYPE ( cds :: uint32 ),                                   graphicsQueueCount,             DEFAULT_VALUE ( 4U ),           GET_NONE,   SET_INLINE ( setGraphicsQueueCount ) )
            Field ( PRIMITIVE_TYPE ( cds :: uint32 ),                                   presentQueueCount,              DEFAULT_VALUE ( 1U ),           GET_NONE,   SET_INLINE ( setPresentQueueCount ) )
            Field ( PRIMITIVE_TYPE ( cds :: uint32 ),                                   transferQueueCount,             DEFAULT_VALUE ( 2U ),           GET_NONE,   SET_INLINE ( setTransferQueueCount ) )

            Field ( TYPE ( cds :: HashSet < cds :: String > ),                          extensionNames,                 NO_INIT,                        GET_NONE,   SET_INLINE ( setExtensionNames ) )
            Field ( PRIMITIVE_TYPE ( bool ),                                            useImplicitExtensions,          DEFAULT_VALUE ( true ),         GET_NONE,   SET_INLINE ( useImplicitExtensions ) )

            Field ( PRIMITIVE_TYPE ( bool ),                                            onlyBasicFeatures,              DEFAULT_VALUE ( true ),         GET_NONE,   SET_INLINE ( setUseOnlyBasicFeatures ) )
            Field ( PRIMITIVE_TYPE ( bool ),                                            allFeatures,                    DEFAULT_VALUE ( false ),        GET_NONE,   SET_INLINE ( setUseAllFeatures ) )
            Field ( TYPE ( cds :: HashSet < Type ( GenericInStructure const * ) > ),    featureSets,                    NO_INIT,                        GET_NONE,   SET_INLINE ( setFeatureSets ) )

            Field ( PRIMITIVE_TYPE ( bool ),                                            createValidationCache,          DEFAULT_VALUE ( false ),        GET_NONE,   SET_NONE )
            Field ( TYPE ( cds :: Path ),                                               validationCachePath,            NO_INIT,                        GET_NONE,   SET_NONE )


        private:
            auto deviceCreateInfoAddQueueCreateInfos (
                    Type ( DeviceCreateInfo )   *,
                    bool,
                    bool
            ) noexcept (false) -> Self &;

            auto deviceCreateInfoAddFeatures ( Type ( DeviceCreateInfo ) *, bool * ) noexcept (false) -> Self &;
            auto deviceCreateInfoAddExtensions ( Type ( DeviceCreateInfo ) * ) noexcept (false) -> Self &;

            NoDiscard auto buildSingleDeviceToSurface () noexcept (false) -> Nester;

            auto addImplicitDeviceExtensions () noexcept (false) -> Self &;
            auto filterUnsupportedExtensions ( cds :: Collection < cds :: String > const & = cds :: HashSet < cds :: String > () ) noexcept (false) -> Self &;

        public:
            NoDiscard auto build () noexcept (false) -> Nester;

            auto useValidationCache ( cds :: Path path = cds :: Path :: CWD ) noexcept -> Self &;
        };

    }
}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#endif //__C_ENG_DEVICE_HPP__

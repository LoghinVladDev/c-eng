//
// Created by loghin on 30.01.2022.
//

#ifndef __C_ENG_DEVICE_HPP__
#define __C_ENG_DEVICE_HPP__

#include <Preprocess.hpp>
#include <VulkanRenderObject.hpp>
#include <VulkanCore.hpp>
#include <CDS/Array>


#define C_ENG_MAP_START     CLASS ( Device, ENGINE_PARENT ( VulkanRenderObject ) )
#include <ObjectMapping.hpp>

namespace engine { // NOLINT(modernize-concat-nested-namespaces)
    namespace vulkan {

        __C_ENG_PRE_DECLARE_CLASS ( Instance );
        __C_ENG_PRE_DECLARE_CLASS ( PhysicalDevice );
        __C_ENG_PRE_DECLARE_CLASS ( PhysicalDeviceGroup );

        Class {
            Field ( ENGINE_PRIMITIVE_TYPE ( DeviceHandle ),     handle,         DEFAULT_VALUE ( nullptr ),  GET_DEFAULT,    SET_NONE )

            Field ( ENGINE_PRIMITIVE_TYPE ( SurfaceHandle ),    surfaceHandle,  DEFAULT_VALUE ( nullptr ),  GET_DEFAULT,    SET_NONE )
            Field ( ENGINE_TYPE ( PhysicalDevice const * ),     physicalDevice, DEFAULT_VALUE ( nullptr ),  GET_DEFAULT,    SET_NONE )

        public:
            class Builder;

            Constructor () noexcept = default;
            Constructor ( Self && ) noexcept;

            auto operator = ( Self const & ) noexcept -> Self & = delete;
            auto operator = ( Self && ) noexcept -> Self &;

            auto clear () noexcept -> Self & override;
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
            Field ( ENGINE_PRIMITIVE_TYPE ( PhysicalDevice const * ),               physicalDevice,                 DEFAULT_VALUE ( nullptr ),      GET_NONE,   SET_INLINE ( fromDevice ) )
            Field ( ENGINE_PRIMITIVE_TYPE ( PhysicalDeviceGroup const * ),          physicalDeviceGroup,            DEFAULT_VALUE ( nullptr ),      GET_NONE,   SET_INLINE ( fromDeviceGroup ) )
            Field ( ENGINE_PRIMITIVE_TYPE ( SurfaceHandle ),                        surfaceHandle,                  DEFAULT_VALUE ( nullptr ),      GET_NONE,   SET_INLINE ( toSurface ) )

            Field ( PRIMITIVE_TYPE ( bool ),                                        preferExclusiveOperations,      DEFAULT_VALUE ( false ),        GET_NONE,   SET_INLINE ( setPreferExclusiveOperations ) )
            Field ( PRIMITIVE_TYPE ( float ),                                       maxQueuePriority,               DEFAULT_VALUE ( 1.0f ),         GET_NONE,   SET_INLINE ( setMaxQueuePriority ) )
            Field ( PRIMITIVE_TYPE ( float ),                                       minQueuePriority,               DEFAULT_VALUE ( 1.0f ),         GET_NONE,   SET_INLINE ( setMinQueuePriority ) )
            Field ( PRIMITIVE_TYPE ( cds :: uint32 ),                               queueOperatingGroupCount,       DEFAULT_VALUE ( 1U ),           GET_NONE,   SET_INLINE ( setPreferredNumberOfQueues ) )
            Field ( PRIMITIVE_TYPE ( float ),                                       queueOperatingGroupPercentage,  DEFAULT_VALUE ( 0.0f ),         GET_NONE,   SET_INLINE ( setPreferredPercentageOfQueues ) )

            Field ( TYPE ( cds :: Array < cds :: String > ),                        extensionNames,                 NO_INIT,                        GET_NONE,   SET_INLINE ( setExtensionNames ) )
            Field ( PRIMITIVE_TYPE ( bool ),                                        onlyBasicFeatures,              DEFAULT_VALUE ( true ),         GET_NONE,   SET_INLINE ( setUseOnlyBasicFeatures ) )
            Field ( PRIMITIVE_TYPE ( bool ),                                        allFeatures,                    DEFAULT_VALUE ( false ),        GET_NONE,   SET_INLINE ( setUseAllFeatures ) )
            Field ( TYPE ( cds :: Array < Type ( GenericInStructure const * ) > ),  featureSets,                    NO_INIT,                        GET_NONE,   SET_INLINE ( setFeatureSets ) )

        private:
            __C_ENG_NO_DISCARD auto buildSingleDeviceToSurface () noexcept (false) -> Nester;

        public:
            __C_ENG_NO_DISCARD auto build () noexcept (false) -> Nester;
        };

    }
}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //__C_ENG_DEVICE_HPP__

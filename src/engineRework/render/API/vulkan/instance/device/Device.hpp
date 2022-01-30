//
// Created by loghin on 30.01.2022.
//

#ifndef C_ENG_DEVICE_HPP
#define C_ENG_DEVICE_HPP

#include <Preprocess.hpp>
#include <CDS/Object>
#include <VulkanCore.hpp>


#define C_ENG_MAP_START     CLASS ( Device, PARENT ( cds :: Object ) )
#include <ObjectMapping.hpp>

namespace engine { // NOLINT(modernize-concat-nested-namespaces)
    namespace vulkan {

        Class {
        public:
            class Builder;
        };

    }
}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     NESTED_CLASS ( Builder, ENGINE_TYPE ( Device ), PARENT ( cds :: Object ) )
#include <ObjectMapping.hpp>

namespace engine { // NOLINT(modernize-concat-nested-namespaces)
    namespace vulkan {

        __C_ENG_PRE_DECLARE_CLASS ( Instance );
        __C_ENG_PRE_DECLARE_CLASS ( PhysicalDevice );

        Class {
            Field ( ENGINE_PRIMITIVE_TYPE ( Instance const * ),         instance,                   DEFAULT_VALUE ( nullptr ),      GET_NONE,   SET_INLINE ( usingInstance ) )
            Field ( ENGINE_PRIMITIVE_TYPE ( PhysicalDevice const * ),   physicalDevice,             DEFAULT_VALUE ( nullptr ),      GET_NONE,   SET_INLINE ( fromDevice ) )
            Field ( ENGINE_PRIMITIVE_TYPE ( SurfaceHandle const * ),    surfaceHandle,              DEFAULT_VALUE ( nullptr ),      GET_NONE,   SET_INLINE ( toSurface ) )
            Field ( PRIMITIVE_TYPE ( bool ),                            preferExclusiveOperations,  DEFAULT_VALUE ( false ),        GET_NONE,   SET_INLINE ( setPreferExclusiveOperations ) )
            Field ( PRIMITIVE_TYPE ( float ),                           maxQueuePriority,           DEFAULT_VALUE ( 1.0f ),         GET_NONE,   SET_INLINE ( setMaxQueuePriority ) )
            Field ( PRIMITIVE_TYPE ( float ),                           minQueuePriority,           DEFAULT_VALUE ( 1.0f ),         GET_NONE,   SET_INLINE ( setMinQueuePriority ) )
            Field ( PRIMITIVE_TYPE ( cds :: uint32 ),                   queueOperatingGroupCount,   DEFAULT_VALUE ( 1U ),           GET_NONE,   SET_INLINE ( setQueueOperatingGroupCount ) )

        public:
            __C_ENG_NO_DISCARD auto build () noexcept (false) -> Nester;
        };

    }
}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //C_ENG_DEVICE_HPP

//
// Created by loghin on 16.01.2022.
//

#ifndef __C_ENG_QUEUE_FAMILY_HPP__
#define __C_ENG_QUEUE_FAMILY_HPP__

#include <Preprocess.hpp>
#include <VulkanCore.hpp>
#include <CDS/Array>

#define C_ENG_MAP_START     CLASS ( QueueFamily,    PARENT ( cds :: Object ) )
#include <ObjectMapping.hpp>

namespace engine { // NOLINT(modernize-concat-nested-namespaces)
    namespace vulkan {

        __C_ENG_PRE_DECLARE_CLASS ( PhysicalDevice );

        Class {
            struct PerformanceCounterProperties {
                __C_ENG_TYPE ( PerformanceCounter )             counter;
                __C_ENG_TYPE ( PerformanceCounterDescription )  description;
            };

            Field ( ENGINE_TYPE ( QueueFamilyDetails ),                     details,                        NO_INIT,                            GET_DEFAULT, SET_NONE )
            Field ( TYPE ( cds :: Array < PerformanceCounterProperties > ), performanceCounterProperties,   NO_INIT,                            GET_DEFAULT, SET_NONE )

            Field ( PRIMITIVE_TYPE ( cds :: uint32 ),                       familyIndex,                    DEFAULT_VALUE ( 0U ),               GET_DEFAULT, SET_NONE )
            Field ( ENGINE_PRIMITIVE_TYPE ( PhysicalDevice const * ),             physicalDevice,                 DEFAULT_VALUE ( nullptr ),    GET_DEFAULT, SET_NONE )

        public:
            auto init ( __C_ENG_TYPE ( PhysicalDevice ) const *, cds :: uint32, __C_ENG_TYPE ( QueueFamilyDetails ) const & ) noexcept (false) -> Self &;
        };

    }
}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif //__C_ENG_QUEUE_FAMILY_HPP__

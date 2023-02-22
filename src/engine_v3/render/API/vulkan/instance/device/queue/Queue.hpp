#ifndef __C_ENG_QUEUE_HPP__
#define __C_ENG_QUEUE_HPP__

#include <Preprocess.hpp>
#include <VulkanRenderObject.hpp>
#include <VulkanCore.hpp>


#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START     CLASS ( Queue, ENGINE_PARENT ( VulkanRenderObject ) )
#include <ObjectMapping.hpp>

namespace engine { // NOLINT(modernize-concat-nested-namespaces)
    namespace vulkan {

        __C_ENG_PRE_DECLARE_CLASS ( Device );
        __C_ENG_PRE_DECLARE_CLASS ( QueueFamily );

        Class {
            Field ( ENGINE_PRIMITIVE_TYPE ( QueueHandle ),          handle,         DEFAULT_VALUE ( nullptr ),  GET_DEFAULT, SET_NONE )
            Field ( ENGINE_PRIMITIVE_TYPE ( QueueFamily const * ),  queueFamily,    DEFAULT_VALUE ( nullptr ),  GET_DEFAULT, SET_NONE )
            Field ( PRIMITIVE_TYPE ( cds :: uint32 ),               index,          DEFAULT_VALUE ( 0U ),       GET_DEFAULT, SET_NONE )
            Field ( ENGINE_PRIMITIVE_TYPE ( QueueFlag ),            type,           NO_INIT,                    GET_DEFAULT, SET_NONE )

        public:
            auto init ( 
                Type ( Device )         const *, 
                Type ( QueueFamily )    const *,
                cds :: uint32,
                Type ( QueueFlag )
            ) noexcept (false) -> Self &;

            auto clear () noexcept -> Self & override;
        };

    }
}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#endif // __C_ENG_QUEUE_HPP__
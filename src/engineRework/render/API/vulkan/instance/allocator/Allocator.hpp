//
// Created by loghin on 31.12.2021.
//

#ifndef C_ENG_ALLOCATOR_HPP
#define C_ENG_ALLOCATOR_HPP

#include <Preprocess.hpp>
#include <CDS/Object>
#include <VulkanCore.hpp>


#define C_ENG_MAP_START     CLASS ( Allocator,  PARENT ( cds :: Object ) )
#include <ObjectMapping.hpp>

namespace engine { // NOLINT(modernize-concat-nested-namespaces)
    namespace vulkan {

        Class {
            Field ( ENGINE_TYPE ( AllocationCallbacks * ), callbacks, DEFAULT_VALUE ( nullptr ), GET_DEFAULT, SET_NONE )

        private:
            Constructor () noexcept = default;

        public:
            static auto instance () noexcept -> Self &;
        };

    }
}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //C_ENG_ALLOCATOR_HPP
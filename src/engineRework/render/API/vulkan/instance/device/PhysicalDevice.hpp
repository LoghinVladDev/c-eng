//
// Created by loghin on 01.01.2022.
//

#ifndef C_ENG_PHYSICALDEVICE_HPP
#define C_ENG_PHYSICALDEVICE_HPP

#include <Preprocess.hpp>
#include <CDS/Object>
#include <VulkanCore.hpp>


namespace cds {
    template < typename T >
    class Array;
}

#define C_ENG_MAP_START     CLASS ( PhysicalDevice,     PARENT ( cds :: Object ) )
#include <ObjectMapping.hpp>

namespace engine { // NOLINT(modernize-concat-nested-namespaces)
    namespace vulkan {

        __C_ENG_PRE_DECLARE_CLASS ( Instance );

        Class {
            Field ( ENGINE_PRIMITIVE_TYPE ( PhysicalDeviceHandle ), handle, DEFAULT_VALUE ( nullptr ),  GET_DEFAULT,    SET_NONE )

        private:
            Constructor () noexcept = default;

        public:
            static auto refreshPhysicalDevices ( __C_ENG_TYPE ( Instance ) const * ) noexcept (false) -> void;
            static auto physicalDevices ( __C_ENG_TYPE ( Instance ) const * = nullptr ) noexcept (false) -> cds :: Array < Self const > const &;
        };

    }
}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //C_ENG_PHYSICALDEVICE_HPP

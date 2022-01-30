//
// Created by loghin on 01.01.2022.
//

#ifndef __C_ENG_PHYSICAL_DEVICE_HPP__
#define __C_ENG_PHYSICAL_DEVICE_HPP__

#include <Preprocess.hpp>
#include <CDS/Array>
#include <VulkanCore.hpp>
#include <QueueFamily.hpp>
#include <VulkanRenderObject.hpp>

#define C_ENG_MAP_START     CLASS ( PhysicalDevice,     ENGINE_PARENT ( VulkanRenderObject ) )
#include <ObjectMapping.hpp>

namespace engine { // NOLINT(modernize-concat-nested-namespaces)
    namespace vulkan {

        __C_ENG_PRE_DECLARE_CLASS ( Instance );

        Class { // NOLINT(cppcoreguidelines-pro-type-member-init)
            Const ( PRIMITIVE_TYPE ( cds :: uint32 ),                               dedicatedGPUBias,   VALUE ( 10000U ) )

            Field ( ENGINE_PRIMITIVE_TYPE ( PhysicalDeviceHandle ),                 handle,             DEFAULT_VALUE ( nullptr ),  GET_DEFAULT,    SET_NONE )
            Field ( ENGINE_TYPE ( PhysicalDeviceDetails ),                          details,            NO_INIT,                    GET_DEFAULT,    SET_NONE )
            Field ( TYPE ( cds :: Array < __C_ENG_TYPE ( QueueFamily ) > ),         queueFamilies,      NO_INIT,                    GET_DEFAULT,    SET_NONE )
            Field ( ENGINE_PRIMITIVE_TYPE ( Instance const * ),                     instance,           DEFAULT_VALUE ( nullptr ),  GET_DEFAULT,    SET_NONE )

        private:
            Constructor () noexcept = default;

            auto refreshQueueFamilies () noexcept (false) -> Self &;

        public:
            static auto refreshPhysicalDevices ( __C_ENG_TYPE ( Instance ) const * ) noexcept (false) -> void;
            static auto physicalDevices ( __C_ENG_TYPE ( Instance ) const * = nullptr ) noexcept (false) -> cds :: Array < Self > const &;

            __C_ENG_NO_DISCARD auto renderScore () const noexcept -> cds :: uint32;

            auto clear () noexcept -> Self & override {
                return * this;
            }
        };

    }
}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //__C_ENG_PHYSICAL_DEVICE_HPP__

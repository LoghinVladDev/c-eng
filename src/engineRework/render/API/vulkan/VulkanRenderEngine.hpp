//
// Created by loghin on 28.12.2021.
//

#ifndef __C_ENG_VULKAN_RENDER_ENGINE_HPP__
#define __C_ENG_VULKAN_RENDER_ENGINE_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#include <RenderEngine.hpp>
#include <Instance.hpp>
#include <Device.hpp>
#include <PresentHandler.hpp>


#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START     CLASS ( VulkanRenderEngine, ENGINE_PARENT ( RenderEngine ) )
#include <ObjectMapping.hpp>

namespace engine { // NOLINT(modernize-concat-nested-namespaces)
    namespace vulkan {

        Class {
            Field ( ENGINE_TYPE ( Version ),                                    desiredVersion, DEFAULT_VALUE ( versionConstants :: nullVersion ),  GET_DEFAULT, SET_INLINE ( setDesiredVersion ) ) // NOLINT(clion-misra-cpp2008-5-0-4,clion-misra-cpp2008-5-0-6)

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SURFACE_AVAILABLE
            Field ( ENGINE_PRIMITIVE_TYPE ( SurfaceHandle ),                    surfaceHandle,  DEFAULT_VALUE ( nullptr ),                          GET_DEFAULT, SET_NONE )
#endif

            Field ( ENGINE_TYPE ( Instance ),                                   instance,       NO_INIT,                                            GET_DEFAULT, SET_NONE )
            Field ( ENGINE_TYPE ( Device ),                                     device,         NO_INIT,                                            GET_DEFAULT, SET_NONE )
            Field ( TYPE ( cds :: UniquePointer < Type ( PresentHandler ) > ),  presentHandler, NO_INIT,                                            GET_DEFAULT, SET_NONE )

        private:
            __C_ENG_NO_DISCARD auto acquireSuitableAPIVersion () const noexcept (false) -> __C_ENG_TYPE ( Version );

        public:
            __C_ENG_NO_DISCARD constexpr auto name () const noexcept -> cds :: StringLiteral override {
                return "Vulkan";
            }

            auto init () noexcept (false) -> Self & override;
            auto clear () noexcept (false) -> Self & override;
            Destructor () noexcept override;
        };
    }
}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif


#endif //__C_ENG_VULKAN_RENDER_ENGINE_HPP__

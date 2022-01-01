//
// Created by loghin on 28.12.2021.
//

#ifndef C_ENG_VULKANRENDERAPI_HPP
#define C_ENG_VULKANRENDERAPI_HPP

#include <RenderEngine.hpp>
#include <Instance.hpp>


#define C_ENG_MAP_START     CLASS ( VulkanRenderEngine, ENGINE_PARENT ( RenderEngine ) )
#include <ObjectMapping.hpp>

namespace engine { // NOLINT(modernize-concat-nested-namespaces)
    namespace vulkan {

        Class {
            Field ( ENGINE_TYPE ( Version ),    desiredVersion, DEFAULT_VALUE ( nullVersion ),  GET_DEFAULT, SET_INLINE ( setDesiredVersion ) ) // NOLINT(clion-misra-cpp2008-5-0-4,clion-misra-cpp2008-5-0-6)
            Field ( ENGINE_TYPE ( Instance ),   instance,       NO_INIT,                        GET_DEFAULT, SET_NONE )

        private:
            __C_ENG_NO_DISCARD auto acquireSuitableAPIVersion () const noexcept (false) -> __C_ENG_TYPE ( Version );

        public:
            __C_ENG_NO_DISCARD constexpr auto name () const noexcept -> cds :: StringLiteral override {
                return "Vulkan";
            }

            auto init () noexcept (false) -> Self & override;
        };
    }
}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //C_ENG_VULKANRENDERAPI_HPP
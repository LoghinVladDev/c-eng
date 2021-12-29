//
// Created by loghin on 28.12.2021.
//

#ifndef C_ENG_VULKANRENDERAPI_HPP
#define C_ENG_VULKANRENDERAPI_HPP

#include <RenderEngine.hpp>


#define C_ENG_MAP_START     CLASS ( VulkanRenderEngine, ENGINE_PARENT ( RenderEngine ) )
#include <ObjectMapping.hpp>

namespace engine { // NOLINT(modernize-concat-nested-namespaces)
    namespace vulkan {

        Class {
        public:
            __C_ENG_NO_DISCARD constexpr auto name () const noexcept -> cds :: StringLiteral override {
                return "Vulkan";
            }

            auto init () noexcept (false) -> Self & override {
                return * this;
            }

        };
    }
}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //C_ENG_VULKANRENDERAPI_HPP

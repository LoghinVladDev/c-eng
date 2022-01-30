//
// Created by loghin on 30.01.2022.
//

#ifndef __C_ENG_VULKAN_RENDER_OBJECT_HPP__
#define __C_ENG_VULKAN_RENDER_OBJECT_HPP__

#include <Preprocess.hpp>
#include <RenderObject.hpp>

#define C_ENG_MAP_START     CLASS ( VulkanRenderObject, ENGINE_PARENT ( RenderObject ) )
#include <ObjectMapping.hpp>


namespace engine { // NOLINT(modernize-concat-nested-namespaces)
    namespace vulkan {

        Class {
        public:
            auto clear () noexcept (false) -> Self & override = 0;
            Destructor () noexcept override = default;
        };

    }
}


#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif //__C_ENG_VULKAN_RENDER_OBJECT_HPP__

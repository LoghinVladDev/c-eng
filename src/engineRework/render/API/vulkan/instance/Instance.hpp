//
// Created by loghin on 28.12.2021.
//

#ifndef __C_ENG_INSTANCE_HPP
#define __C_ENG_INSTANCE_HPP

#include <Preprocess.hpp>
#include <CDS/Object>

#include <VulkanCore.hpp>


#define C_ENG_MAP_START     CLASS ( Instance, PARENT ( cds :: Object ) )
#include <ObjectMapping.hpp>

namespace engine { // NOLINT(modernize-concat-nested-namespaces)

    namespace vulkan {

        Class {
        public:
            class Builder;

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

            static auto supportedVulkanVersion () noexcept (false) -> __C_ENG_TYPE ( Version );

#endif

        };

        class Self :: Builder : public cds :: Object {

        };

    }

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif // __C_ENG_INSTANCE_HPP

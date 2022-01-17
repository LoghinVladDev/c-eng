//
// Created by loghin on 17.01.2022.
//

#ifndef __C_ENG_VULKAN_API_CALLS_VALID_USAGE_HPP__
#define __C_ENG_VULKAN_API_CALLS_VALID_USAGE_HPP__

namespace engine { // NOLINT(modernize-concat-nested-namespaces)
    namespace vulkan {

        static inline auto validate (
            __C_ENG_TYPE ( DeviceCreateInfo ) const * pCreateInfo
        ) noexcept -> bool {

#ifdef NDEBUG
            return true;
#endif

            return true;

        }

    }
}

#endif //__C_ENG_VULKAN_API_CALLS_VALID_USAGE_HPP__

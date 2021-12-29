//
// Created by loghin on 28.12.2021.
//

#ifndef __C_ENG_VULKANAPICALLS_HPP
#define __C_ENG_VULKANAPICALLS_HPP

namespace engine { // NOLINT(modernize-concat-nested-namespaces)

    namespace vulkan {

        __C_ENG_NO_DISCARD inline static auto enumerateInstanceVersion (
                cds :: uint32 * pOutRawVersion
        ) noexcept -> __C_ENG_TYPE ( Result ) {

            return static_cast < __C_ENG_TYPE ( Result ) > ( vkEnumerateInstanceVersion ( pOutRawVersion ) );
        }

    }

}

#endif //__C_ENG_VULKANAPICALLS_HPP

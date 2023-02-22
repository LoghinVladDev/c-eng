//
// Created by loghin on 08.03.2022.
//

#ifndef __C_ENG_LAST_CREATED_INSTANCE_HPP__
#define __C_ENG_LAST_CREATED_INSTANCE_HPP__

#include <CDS/Mutex>
#include <CDS/LockGuard>

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
#define C_ENG_MAP_START HEADER
#include <ObjectMapping.hpp>

class LastCreatedInstance {
private:
    static inline engine :: vulkan :: Type ( InstanceHandle ) instance;
    static inline cds :: Mutex lock;

public:
    static inline auto acquire () noexcept -> engine :: vulkan :: Type ( InstanceHandle ) {
            /* read lock might be irrelevant, guarding against incomplete pointers to instance
             * a null instance / a valid instance = OK */
            cds :: LockGuard guard ( lock );
            return instance;
    }

    static inline auto set ( engine :: vulkan :: Type ( InstanceHandle ) handle ) noexcept -> void {
        cds :: LockGuard guard ( lock );
        instance = handle;
    }
};

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>
#endif

#endif //__C_ENG_LAST_CREATED_INSTANCE_HPP__

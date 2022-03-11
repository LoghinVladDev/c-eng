//
// Created by loghin on 08.03.2022.
//

#ifndef __C_ENG_ALLOCATION_HANDLER_HPP__
#define __C_ENG_ALLOCATION_HANDLER_HPP__

#include <CDS/Mutex>
#include <CDS/LockGuard>
#include <VulkanCore.hpp>

#define C_ENG_MAP_START HEADER
#include <ObjectMapping.hpp>

class AllocatorHandler {
private:
    static inline VkAllocationCallbacks                                     callbacks {};
    static inline engine :: vulkan :: Type ( AllocationCallbacks )  const * pApplicationAllocationCallbacks { nullptr };
    static inline cds :: Mutex                                              lock;

public:
    static inline auto apply (
            engine :: vulkan :: Type ( AllocationCallbacks ) const * pAllocationCallbacks
    ) noexcept -> VkAllocationCallbacks const * {
        if ( pAllocationCallbacks == nullptr ) {
            return nullptr;
        }

        if ( pApplicationAllocationCallbacks == pAllocationCallbacks ) {
            return & callbacks;
        }

        cds :: LockGuard guard ( lock );
        pApplicationAllocationCallbacks = pAllocationCallbacks;
        return toVulkanFormat ( & callbacks, pApplicationAllocationCallbacks );
    }
};

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif //__C_ENG_ALLOCATION_HANDLER_HPP__

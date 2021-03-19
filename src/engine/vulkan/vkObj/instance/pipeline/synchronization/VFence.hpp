//
// Created by Vlad on 21/08/2020.
//

#ifndef ENG1_VFENCE_HPP
#define ENG1_VFENCE_HPP

#include <engineVulkanPreproc.hpp>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/instance/device/VLogicalDevice.hpp>
#include <vector>
namespace engine {

    class VFence {
    private:
        //// private variables
        VulkanFence             _handle         {VK_NULL_HANDLE};
        const VLogicalDevice  * _pLogicalDevice {nullptr};

        //// private functions

    public:
        //// public variables
        constexpr static VulkanFenceCreateFlags     NO_FLAGS        = 0U;
        constexpr static VulkanFenceCreateFlagBits  START_SIGNALED  = VulkanFenceCreateFlagBits::VK_FENCE_CREATE_SIGNALED_BIT;

        //// public functions
        VFence () noexcept = default;

        [[nodiscard]] const VulkanFence & data () const noexcept {
            return this->_handle;
        }

        [[nodiscard]] bool empty () const noexcept {
            return this->_handle == VK_NULL_HANDLE;
        }

        VulkanResult setup ( const VLogicalDevice &, VulkanFenceCreateFlags = NO_FLAGS ) noexcept;
        void cleanup () noexcept;
    };

    class VFenceCollection {
    private:
        //// private variables
        std::vector < VFence >  _fences;
        const VLogicalDevice  * _pLogicalDevice {nullptr};

        //// private functions

    public:
        //// public variables

        //// public functions
        VFenceCollection () noexcept = default;

        [[nodiscard]] const std::vector < VFence > & getFences () const noexcept {
            return this->_fences;
        }

        [[nodiscard]] const VLogicalDevice * getLogicalDevicePtr () const noexcept {
            return this->_pLogicalDevice;
        }

        [[nodiscard]] uint32 size () const noexcept {
            return static_cast<uint32>(this->_fences.size());
        }

        [[nodiscard]] const VFence & operator [] ( uint32 index ) const noexcept {
            return this->_fences[ index ];
        }

        [[nodiscard]] VFence & operator [] ( uint32 index ) noexcept {
            return this->_fences[ index ];
        }

        VulkanResult setup ( const VLogicalDevice &, uint32, VulkanFenceCreateFlags = VFence::NO_FLAGS ) noexcept;
        VulkanResult resize ( const VLogicalDevice &, uint32, VulkanFenceCreateFlags = VFence::NO_FLAGS ) noexcept;
        VulkanResult resize ( uint32 );
        void cleanup () noexcept;
    };

}


#endif //ENG1_VFENCE_HPP

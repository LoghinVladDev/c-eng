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

    class VFence : public VRenderObject {
    private:
        //// private variables
        VulkanFence             _handle         {VK_NULL_HANDLE};
        VLogicalDevice  const * _pLogicalDevice {nullptr};

        //// private functions

    public:
        //// public variables
        constexpr static VulkanFenceCreateFlags     NO_FLAGS        = 0U;
        constexpr static VulkanFenceCreateFlagBits  START_SIGNALED  = VulkanFenceCreateFlagBits::VK_FENCE_CREATE_SIGNALED_BIT;

        //// public functions
        VFence () noexcept = default;
        ~VFence () noexcept override = default;

        [[nodiscard]] constexpr auto data () const noexcept -> VulkanFence const & {
            return this->_handle;
        }

        [[nodiscard]] constexpr auto empty () const noexcept -> bool {
            return this->_handle == VK_NULL_HANDLE;
        }

        auto setup ( VLogicalDevice const &, VulkanFenceCreateFlags = NO_FLAGS ) noexcept -> VulkanResult;
        auto clear () noexcept -> void override;

        [[nodiscard]] auto toString () const noexcept -> String override;

        [[nodiscard]] auto operator == (Object const & o) const noexcept -> bool override {
            if ( this == & o ) return true;
            auto p = dynamic_cast < decltype(this) > (& o);
            if ( p == nullptr ) return false;

            return this->_handle == p->_handle;
        }

        [[nodiscard]] auto copy () const noexcept -> VFence * override {
            return new VFence(*this);
        }

        [[nodiscard]] auto hash () const noexcept -> Index override {
            return dataTypes::hash(reinterpret_cast<AddressValueType >(this->_handle));
        }
    };

    class VFenceCollection : public VRenderObject {
    private:
        //// private variables
        std::vector < VFence >  _fences;
        VLogicalDevice  const * _pLogicalDevice {nullptr};

        //// private functions

    public:
        //// public variables

        //// public functions
        VFenceCollection () noexcept = default;
        ~VFenceCollection() noexcept override = default;

        [[nodiscard]] constexpr auto getFences () const noexcept -> std::vector < VFence > const & {
            return this->_fences;
        }

        [[nodiscard]] constexpr auto getLogicalDevicePtr () const noexcept -> VLogicalDevice const * {
            return this->_pLogicalDevice;
        }

        [[nodiscard]] inline auto size () const noexcept -> uint32 {
            return static_cast<uint32>(this->_fences.size());
        }

        [[nodiscard]] inline auto operator [] ( uint32 index ) const noexcept -> VFence const & {
            return this->_fences[ index ];
        }

        [[nodiscard]] inline auto operator [] ( uint32 index ) noexcept -> VFence & {
            return this->_fences[ index ];
        }

        auto setup ( VLogicalDevice const &, uint32, VulkanFenceCreateFlags = VFence::NO_FLAGS ) noexcept -> VulkanResult;
        auto resize ( VLogicalDevice const &, uint32, VulkanFenceCreateFlags = VFence::NO_FLAGS ) noexcept -> VulkanResult;
        auto resize ( uint32 ) noexcept -> VulkanResult;
        auto clear () noexcept -> void override;

        [[nodiscard]] auto toString () const noexcept -> String override;

        [[nodiscard]] auto operator == (Object const & o) const noexcept -> bool override {
            if ( this == & o ) return true;
            auto p = dynamic_cast < decltype (this) > (& o);
            if ( p == nullptr ) return false;

            return this->_fences == p->_fences;
        }

        [[nodiscard]] auto copy () const noexcept -> VFenceCollection * override {
            return new VFenceCollection(*this);
        }

        [[nodiscard]] auto hash () const noexcept -> Index override {
            Index hashSum = 0;
            std::for_each(this->_fences.begin(), this->_fences.end(), [& hashSum](auto const & f){hashSum += f.hash();});
            return hashSum;
        }
    };

}


#endif //ENG1_VFENCE_HPP

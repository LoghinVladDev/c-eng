//
// Created by Vlad on 19/08/2020.
//

#ifndef ENG1_VRENDERPASS_HPP
#define ENG1_VRENDERPASS_HPP

#include <VRenderObject.hpp>
#include <VLogicalDevice.hpp>

namespace engine {

    class EngineVRenderPassDeviceInvalidSwapChain : public std::exception {
    public:
        [[nodiscard]] auto what() const noexcept -> StringLiteral override {
            return "Passed VLogicalDevice has invalid / non-existent swap chain";
        }
    };

    class VRenderPass : public VRenderObject {
    private:
        //// private variables
        VLogicalDevice    const *   _pLogicalDevice {nullptr};
        VulkanRenderPass            _handle         {nullptr};

        //// private functions

    public:
        //// public variables

        //// public functions
        VRenderPass () noexcept = default;
        ~VRenderPass() noexcept override = default;

        [[nodiscard]] constexpr auto data () const noexcept -> VulkanRenderPass const & {
            return this->_handle;
        }

        [[nodiscard]] constexpr auto getLogicalDevicePtr () const noexcept -> VLogicalDevice const * {
            return this->_pLogicalDevice;
        }

        auto setup (
            engine::VLogicalDevice const & ,
            VulkanSubpassDependency const * = nullptr,
            uint32 = 0U
        ) noexcept (false) -> VulkanResult;

        auto clear () noexcept -> void override;

        [[nodiscard]] auto toString () const noexcept -> String override;

        [[nodiscard]] auto operator == (VRenderPass const & o) const noexcept -> bool {
            if ( this == & o ) return true;

            return this->_handle == o._handle;
        }

        [[nodiscard]] auto equals (Object const & o) const noexcept -> bool override {
            if ( this == & o ) return true;
            auto p = dynamic_cast < decltype(this) > (& o);
            if ( p == nullptr ) return false;

            return this->operator==(*p);
        }

        [[nodiscard]] auto copy () const noexcept -> VRenderPass * override {
            return new VRenderPass(* this);
        }

        [[nodiscard]] auto hash () const noexcept -> Index override {
            return dataTypes::hash(reinterpret_cast<AddressValueType>(this->_handle));
        }
    };

}


#endif //ENG1_VRENDERPASS_HPP
